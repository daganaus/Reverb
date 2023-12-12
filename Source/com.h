//This code  C++ com.h is written automatically by: makef.cc, so do write in it. It concerns a Plugin in JUCE. 
//=========================================================================================
#pragma once
#include "Source/JuceHeader.h"
using namespace std;
using namespace juce;
//============
// declared below
class Editor;
class Com;
class ColourChangeButton;

//============
// object declared in com.cc
//extern Com *p_com;
//extern mutex *mtx_com;

class Manager;

//===============================
// override  design

class CustomTabLookAndFeel : public LookAndFeel_V4
{
public:
    CustomTabLookAndFeel()
		{
			//setColour(TabbedButtonBar::ColourIds::frontTextColourId, Colours::yellow); // Couleur du texte du tab sélectionné
			setColour(TabbedButtonBar::ColourIds::frontTextColourId, Colour(0xb5, 0x89, 0x00) ); // kyellow: Color of selected tab
			setColour(Slider::ColourIds::thumbColourId, Colour(0xcb, 0x4b, 0x16) ); // korange: color of sliders
		}

    void drawTabButton (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown) override
		{
			LookAndFeel_V4::drawTabButton(button, g, isMouseOver, isMouseDown);
			// Ajoutez ici un code personnalisé pour dessiner les onglets si nécessaire
		}
};


//-- Below is the list of 2 windows for each tab window + ZC.


//=============================================
class Page_ZT_0 : public juce::Component 
{
 public:
   Page_ZT_0(Com *p_i);
   ~Page_ZT_0();

    // resized() that is called once at the initialisation of the window and every time the window is resized by the user (if resizing is enabled).
    void resized() override;
    void paint(juce::Graphics& g) override;
    Com *p_com = nullptr;
    int ZC_size = 20; // vertical size of zone above tabs


    //------------
    juce::TabbedComponent *tab;
    CustomTabLookAndFeel customLookAndFeel;

//----To detect leak memory---------------
JUCE_LEAK_DETECTOR (Page_ZT_0)
};

//=====================
// Main class for widgets

class Com   : public juce::MultiTimer
{
public:
    int verbose = 0; // 1: used for debug
    string window_title = ""; // name of the main window 

    Com(Editor *p_i, Manager *pManager);
	~Com();

    Manager *p_Manager;

	void resized();
    void timerCallback(int ID); // derived from class MultiTimer

	//-----------
	Editor *p_e = nullptr;

   //some pointers for easer access to tabs by their full name
	Page_ZT_0  * p_Tab_ZC;

  //--- list of objects in this zone

	//-- from the instruction of class: Manager: 
    // int test = 3;   // make_gui =  HS(ZC, 0, 10) texxt ="test:"    help ="test"
    juce::Slider *Manager_test;
    juce::Label *Manager_test_text;
    juce::Label *Manager_test_texte;

	//-- from the instruction of class: Manager: 
    // void Loop_manager();  // make_gui = TT(100)

	//-- transfert of values --------
    void Met_a_jour_Manager_test();  //  c++ value --> widget value
    void Process_message_Manager_test();  //  widget value --> c++ value

//----To detect leak memory---------------
JUCE_LEAK_DETECTOR (Com)

};
//==========================================================
/*
Parameters of the plugin
*/

class Processor; 

class Parameters
{
public:
   Parameters(Manager *pManager);
	~Parameters();
	mutex mtx_params;  // used to access Parameters
	Com *p_com = nullptr;

	//.... parameters of objects in com.h

//........
    Manager *p_Manager;

//........

	void Save_parameters(Processor * processor, MemoryBlock& destData);
	void Load_parameters(Processor * processor, const void* data, int sizeInBytes);

	void Add_Automation_Parameters(Processor * processor);
	void Transmit_Automation_Parameters(Processor * processor, int parameterIndex);
//----To detect leak memory---------------
JUCE_LEAK_DETECTOR (Parameters)

};
