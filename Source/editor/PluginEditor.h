#pragma once

#include "Source/JuceHeader.h"
#include "Source/processor/PluginProcessor.h"


using namespace juce;

//==============================================================================
/*
This class concerns the GUI (widgets)
 */
class Editor  : public juce::AudioProcessorEditor
{
public:
	Com *p_com = nullptr; // declared in com.h
	Processor& processor; // in PluginProcessor.h


	
	Editor (Processor&);
    ~Editor() override;

	
	juce::SharedResourcePointer<juce::TooltipWindow> tooltipWindow; // used to show tip text
	
	
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Editor)
};
