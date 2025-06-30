/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "Source/processor/PluginProcessor.h"
#include "Source/editor/PluginEditor.h"
#include "Source/editor/manager.h"
#include <juce_dsp/juce_dsp.h>
using namespace juce;



#include <chrono>
using namespace std::chrono;
#include <thread>
using namespace std::this_thread; 


//======================================================
Processor::Processor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::mono(), true) // @@ put stereo or  mono?
//					   .withInput("Sidechain", AudioChannelSet::mono(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::mono(), true)
                     #endif
                       )
#endif

{
	dryWetParam = new juce::AudioParameterFloat("dryWet", "Dry/Wet", 0.0f, 1.0f, 0.005f);
	addParameter(dryWetParam);
	manager = new Manager();
	manager->process = this;

//---- Parameters -----
   	params = new Parameters(manager); // declared in com.h, look to respect the order
	params->Add_Automation_Parameters(this); //in com.cc


//------------
	Mes.reserve(10);
	t0 = high_resolution_clock::now(); // measure of time 
}

//==============================================================================
Processor::~Processor()
{
	//---- delete the manager, which contains the GUI
    delete manager;
    manager = nullptr;
   //.... for the thread GUI ...
	delete params;
	params = nullptr;

}

//==============================================================================
const juce::String Processor::getName() const
{
    return "Reverb";
}

//==============================================================================
bool Processor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

//==============================================================================
bool Processor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}
//==============================================================================
bool Processor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}
//==============================================================================
double Processor::getTailLengthSeconds() const
{
    return 0.0;
}
//==============================================================================
int Processor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}
//==============================================================================
int Processor::getCurrentProgram()
{
    return 0;
}
//==============================================================================
void Processor::setCurrentProgram (int index)
{
	(void) index; // avoid unused parameter warning
	// NB: some hosts don't cope very well if you tell them there are 0 programs,
	// so this should be at least 1, even if you're not really implementing programs.
}
//==============================================================================
const juce::String Processor::getProgramName (int index)
{
    (void) index;
	return {};
}
//==============================================================================
void Processor::changeProgramName (int index, const juce::String& newName)
{
	(void) index;
	(void) newName;
}

//==============================================================================
void Processor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	//(void)samplesPerBlock; // avoid unused parameter warning
	//(void)sampleRate; // avoid unused parameter warning
	t0 = high_resolution_clock::now(); // mesure du "time point 0"
    //Création de l'arrete avec une taille de buffer circulaire de 1024 samples
	if (edge != nullptr)
    	delete edge;
	edge = new Edge(44100);
	std::cout << "Processor::prepareToPlay: sampleRate=" << sampleRate << " samplesPerBlock=" << samplesPerBlock << std::endl;
	std::cout << "delay time = " << edge->getLength()/sampleRate << std::endl;


	/*
	juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32>(samplesPerBlock);
	spec.numChannels = static_cast<juce::uint32>(getTotalNumOutputChannels());
    delayLine.prepare(spec);
    delayLine.setMaximumDelayInSamples((int) (sampleRate * 2.0)); // 2 secondes max
    delayLine.setDelay(sampleRate * 1.0); // 1 seconde de délai par défaut
    delayLine.reset();
	*/
}
//==============================================================================
void Processor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}
//==============================================================================
// ref: https://docs.juce.com/master/tutorial_audio_bus_layouts.html
#ifndef JucePlugin_PreferredChannelConfigurations
bool Processor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    (void)layouts;
    return true;	
}
#endif


//==================================
void   Processor::Print_Midi_Messages(MidiBuffer&  midi_buf)
{
	if(midi_buf.getNumEvents() == 0)
		return;
	
	if(manager == nullptr)
		return;

	//------------- prepare the output
	
	ostringstream s;
	s<<"----------------------\n"<<endl;
	s<<"list of "<< midi_buf.getNumEvents() <<" messages:"<<endl;


	for (const MidiMessageMetadata &metadata : midi_buf) // loop on input midi messages
	{
		MidiMessage mes = metadata.getMessage();
//		s<<"mes.getDescription ()="<<mes.getDescription()<<endl;
//		s<<"mes.size ="<<mes.getRawDataSize()<<endl;

		const uint8* p_mes =  mes.getRawData();
		Mes.assign(p_mes, p_mes + mes.getRawDataSize());
		for(size_t i=0; i<Mes.size(); i++)
			//s<< hex << setw(2) << setfill('0')<<Mes[i]<<",";
			s<< hex <<(int)Mes[i]<<",";
		//double t = mes.getTimeStamp();
		double t_start = Date_from_start_in_sec();

		s<<"\tt="<< t_start; // time from start 
		s<<endl;
	
	}

//	cout<<s.str(); 
	
	if(manager->mtx_s_MM.try_lock())
	{
		size_t N = manager->s_MM.size();
		if(N > 10000) // if string too large,
			manager->s_MM.erase(0, N - 9000);  // we let the last 9000
			
		manager->s_MM.append(s.str());
		manager->changes_MM.store(true);  // ask to refresh display in manager.cc
		manager->mtx_s_MM.unlock();
	}
	
}


//==============================================================================
/*
 Warning with JUCE, MIDI channel is in [1,16]
 but in our code we decide to keep: ch in [0,15]
So beware of this +/-1 shift.

Rem: this function is in the Processor Thread.

 */
float Processor::Graph(float dry, float gain)
{
	if(manager == nullptr)
		return dry;

	float wet = edge->getSample(edge->getLength()); // récupère le dernière échantillon de l'arrete

	// Envoie le dry signal dans l'arrete
	edge->pushSample(dry); //après getsample car push fait avancer le buffer

	// Applique un gain pour éviter la saturation
	return gain*wet;
}


void Processor::processBlock(AudioBuffer<float>& audio_buffer, MidiBuffer& midi_buffer)
{
	//---- affiche midi messages
	Print_Midi_Messages(midi_buffer);
	//---- measures time and latency
	double t_begin = Date_from_start_in_sec(); // time , begin of block process

	//--- delay line
	if(manager != nullptr && manager->opt_sound == 1)
	{
		float dryWetValue = dryWetParam->get(); // get the dry/wet value from the manager
		int N = getSampleRate(); // nombre echantillons / sec.
		int n = audio_buffer.getNumSamples(); // nombre echantillons dans le buffer
		int nchan = audio_buffer.getNumChannels(); // 1: mono, 2: stereo
//	cout<<" nchan="<<nchan<<" N="<<N<<" n="<<n<<endl;

	
		for (int ch = 0; ch < nchan; ch++)
		{
			// Récupérer le pointeur d'écriture pour le canal spécifié
			float* bufferPtr = audio_buffer.getWritePointer(ch);
		
			for (int i = 0; i< n; i++)
			{
			    // échantillon d'entrée
				float dry = bufferPtr[i]; 

            	// Récupère la sortie retardée et la place dans le buffer
				float wet = Graph(dry, 1.0f); // appel de la fonction Graph pour obtenir le signal traité

				// Applique un gain pour éviter la saturation
				//cout << "dryWetValue=" << dryWetValue << endl;
				bufferPtr[i] = (1.0f - dryWetValue) * dry + dryWetValue * wet;
			
				// Incrémente le temps
				t += 1.0 / N;
			}
			
		}

	}
	


	

	//====  measures time and latency ===================

	double t_end = Date_from_start_in_sec(); // time , end of block process

	double dt = audio_buffer.getNumSamples() / double( getSampleRate());  // mean duration of a block


	//... max  latency ....
	double latency =  (t_end - t_begin) / dt; // ratio

	if(manager != nullptr && mtx.try_lock())
	{

		if(latency > manager->latency)
			manager->latency = latency;

		//... mean latency
		manager->N_latency++;
		manager->S_latency += (t_end - t_begin);
	
		if(manager->N_latency >= 1000)
		{
			manager->latency_mean =  manager->S_latency / (1000. * dt);
			manager->N_latency = 0;
			manager->S_latency = 0;
		}
		mtx.unlock();
	}
}

void Processor::processBlock (juce::AudioBuffer<double>& audio_buffer, juce::MidiBuffer& midi_buffer) // Ce buffer est INTERNE, il ne SORT PAS du standalone !
{
    // Convertit le buffer double en float, puis appelle la version float
    juce::AudioBuffer<float> tmp(audio_buffer.getNumChannels(), audio_buffer.getNumSamples());
    for (int ch = 0; ch < audio_buffer.getNumChannels(); ++ch)
        for (int s = 0; s < audio_buffer.getNumSamples(); ++s)
            tmp.setSample(ch, s, static_cast<float>(audio_buffer.getSample(ch, s)));
    processBlock(tmp, midi_buffer);
}




//==============================================================================
bool Processor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}
//==============================================================================
juce::AudioProcessorEditor*  Processor::createEditor()
{
    return new Editor (*this);
}

//==============================================================================
void Processor::getStateInformation (MemoryBlock& destData)
{
	params->Save_parameters( name_params, this, destData); // in com.cc
}
//==============================================================================
void Processor::setStateInformation (const void* data, int sizeInBytes)
{
	params->Load_parameters( name_params, this, data, sizeInBytes); // in com.cc
}


//==================================
/*
This function is called if a parameter is changed: from automation or by the plugin.
 */
void  Processor::parameterValueChanged (int parameterIndex, float newValue) 
{
	(void)newValue;
	params->Transmit_Automation_Parameters(this, parameterIndex); // in com.cc

}

//=======================
void  Processor::parameterGestureChanged(int parameterIndex, bool gestureIsStarting)
{
	(void)parameterIndex;
    (void)gestureIsStarting;
}


//========================
double 	Processor::Date_from_start_in_sec() //date from t0 in sec.
{
	auto t2 = high_resolution_clock::now(); // measure of time 
	return 		duration_cast<duration<double>>(t2 - t0).count(); // duration in sec.
}


//==============================================================================


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Processor();
}

//==============================================================================