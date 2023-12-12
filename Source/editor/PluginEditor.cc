/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "Source/processor/PluginProcessor.h"
#include "Source/editor/PluginEditor.h"

#include "Source/com.h" // commands GUI


//==============================================================================
Editor::Editor (Processor& p)
    : AudioProcessorEditor (&p), processor (p) 
{

	//..... construct the object p_com that contains the GUI
   	p_com = new Com(this, processor.manager); // declared in com.h, look in com.h to respect the order
	processor.p_com = p_com;
	processor.params->p_com = p_com;

	
	setSize(300, 200); // size a priori


}
//=========================
Editor::~Editor()
{
	
	processor.p_com = nullptr; // to signal the end
		
	delete p_com;
	p_com = nullptr;
}

//==============================================================================
void Editor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
}
//==============================================================================
void Editor::resized()
{
	p_com->resized();

}

