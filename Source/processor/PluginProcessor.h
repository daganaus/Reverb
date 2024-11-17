/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once



#define _USE_MATH_DEFINES // for windows VS
#include <math.h>


#include "Source/JuceHeader.h"
#include "Source/com.h"

#include <iostream> // to use in out messages
using namespace std;


#include <chrono> // to use time functions
using namespace std::chrono;


#include <mutex> // to use with threads

//==============================================================================
/*
This class concerns the plugin.

It has a special function: 
   processBlock() that runs in a separated thread (faster)

It creates the object Editor() for GUI.

*/
class Processor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
				   ,  public juce::AudioProcessorParameter::Listener
{
public:

	double t = 0;
	
	Com *p_com = nullptr;   // in com.h. Set in the  editor constructor

	Manager *manager = nullptr;
	

	mutex mtx;  //mutex for communications process <-> editor. For each plugin. Taken by each midi_event thread.

	int opt_sound = 0; // copy of a variable in manager.h


	
	vector<uint8> Mes; // use to construct many midi messages. We reserve some memory.
	

		//...........
	high_resolution_clock::time_point t0; // initial time point, for use of  precise timing. Set in manager.cc
	double 	Date_from_start_in_sec(); //date from t0 in sec.

	
	void   Print_Midi_Messages(MidiBuffer&  midi_buf);

	

	//---- parameters, saved by the DAW.
	string name_params = "params_2024_11_17"; // xml name. Change name if you need. 
	Parameters *params = nullptr; // in com.h and com.cc. Set in the processor constructor
    void parameterValueChanged (int parameterIndex, float newValue) override;
	void parameterGestureChanged(int parameterIndex, bool gestureIsStarting) override;

	
    //==============================================================================
    Processor();
    ~Processor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif
	//==============================================================================
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

	void Transfer_L_midi_messages_to_midiMessages(	vector<vector< uint8_t>> & L_midi_messages, MidiBuffer&  midiMessages);
	void  Print_Midi_Messages( MidiBuffer&  midi_buf, string text);
	void  Print_Midi_Messages(vector<vector< uint8_t>> & L_midi_messages, string text);
	int index_of_plugin();
	
    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

//===============
	void  Convert_Ln_to_SysEx(vector<int> &L_n, int ch_out, vector<uint8> &L_sysex);
	void Add_STM_message_note_on(vector<vector< uint8_t>> &L_midi_messages, int ch_out, int key_out, int vel_out, vector<int> &L_n, double dx);
	void Add_STM_message_note_on(vector<vector< uint8_t>> &L_midi_messages, int vel_out, vector<int> &L_n, double dx_add = 0);
	//===============
	int verbose = 0;

	
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Processor)
};

