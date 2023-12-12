/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "Source/processor/PluginProcessor.h"
#include "Source/editor/PluginEditor.h"
#include "Source/editor/manager.h"
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
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif

{

	manager = new Manager();
	manager->process = this;

//---- Parameters -----
   	params = new Parameters(manager); // declared in com.h, look to respect the order
	params->Add_Automation_Parameters(this); //in com.cc


//------------
	Mes.reserve(10);
}

//==============================================================================
Processor::~Processor()
{

   //.... for the thread GUI ...
	delete params;
	params = nullptr;

}

//==============================================================================
const juce::String Processor::getName() const
{
    return JucePlugin_Name;
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

}
//==============================================================================
const juce::String Processor::getProgramName (int index)
{
    return {};
}
//==============================================================================
void Processor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Processor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	t0 = high_resolution_clock::now(); // mesure du "time point 0"
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
    return true;
	
}
#endif

//========================
double 	Processor::Date_from_start_in_s()
{
	auto t2 = high_resolution_clock::now(); // measure of time 
	return 		duration_cast<duration<double>>(t2 - t0).count(); // duration in sec.
}


//==============================================================================
/*
 Warning with JUCE, MIDI channel is in [1,16]
 but in our code we decide to keep: ch in [0,15]
So beware of this +/-1 shift.

Rem: this function is in the Processor Thread.

 */
void Processor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	//---- measures time and latency
	double t_begin = Date_from_start_in_s(); // time , begin of block process
	
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
	params->Save_parameters(this, destData); // in com.cc
}
//==============================================================================
void Processor::setStateInformation (const void* data, int sizeInBytes)
{
	params->Load_parameters(this, data, sizeInBytes); // in com.cc
}


//==================================
/*
This function is called if a parameter is changed: from automation or by the plugin.
 */
void  Processor::parameterValueChanged (int parameterIndex, float newValue) 
{
	params->Transmit_Automation_Parameters(this, parameterIndex); // in com.cc
}

//=======================
void  Processor::parameterGestureChanged(int parameterIndex, bool gestureIsStarting)
{
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Processor();
}
