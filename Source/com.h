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

//==============================================================================
// A Window
class TCanvas_Manager_s_MM : public juce::DocumentWindow
{
public:	
    Com * p_com = nullptr;
    CodeEditorComponent *p_editor = nullptr;
	TCanvas_Manager_s_MM(Com *p_i, const juce::String &name, juce::Colour backgroundColour, int requiredButtons, bool addToDesktop=true);
	~TCanvas_Manager_s_MM() override;

    int status = 0; //0 : internal, 1: external
	void resized() override;
	void moved() override;
	void paint(juce::Graphics& g) override;
	void closeButtonPressed();

//----To detect leak memory : Put class name---------------
	JUCE_LEAK_DETECTOR (TCanvas_Manager_s_MM)
};

//-- Below is the list of 3 windows for each tab window + ZC.


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

//=============================================
class Page_ZT_1 : public juce::Component 
{
 public:
   Page_ZT_1(Com *p_i);
   ~Page_ZT_1();

    // resized() that is called once at the initialisation of the window and every time the window is resized by the user (if resizing is enabled).
    void resized() override;
    void paint(juce::Graphics& g) override;
    Com *p_com = nullptr;
    int ZC_size = 20; // vertical size of zone above tabs


    //------------
    juce::TabbedComponent *tab;
    CustomTabLookAndFeel customLookAndFeel;

//----To detect leak memory---------------
JUCE_LEAK_DETECTOR (Page_ZT_1)
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
	Page_ZT_1  * p_Tab_Monitor;

  //--- list of objects in this zone

	//-- from the instruction of class: Manager: 
    // string s_MM; // make_gui =  nl Editor(ZC, "Midi messages")
    juce::TextButton *Manager_s_MM_button;
    juce::Label *Manager_s_MM_text;
    TCanvas_Manager_s_MM *Manager_s_MM = nullptr;
    void Show_Hide_Window_Manager_s_MM();
    CodeDocument Manager_s_MM_code;

	//-- from the instruction of class: Manager: 
    // int opt_sound = 0; //  make_gui =  C(ZC) texxt ="opt_sound:"    help ="1: create a sound, 0: silence"
    juce::ToggleButton *Manager_opt_sound;
    juce::Label *Manager_opt_sound_text;
    juce::Label *Manager_opt_sound_texte;

	//-- from the instruction of class: Manager: 
    // void Loop_manager();  // make_gui = TT(100)

	//-- from the instruction of class: Manager: 
    // double latency = 0; // make_gui = nl PB(ZT("Monitor"), 0, 1.)  texxt="latency max:"   help = "Maximum latency of the last events, percentage of available time for the processor"
    juce::ProgressBar *Manager_latency;
    double Manager_latency_x = 0; // value of the ProgressBar
    juce::Label *Manager_latency_text;
    juce::Label *Manager_latency_texte;

	//-- from the instruction of class: Manager: 
    // double latency_mean = 0; // make_gui =  PB(ZT("Monitor"), 0, 1.)  texxt="latency mean:"   help = "Mean latency of the last events, averaged over the last 1000 blocks"
    juce::ProgressBar *Manager_latency_mean;
    double Manager_latency_mean_x = 0; // value of the ProgressBar
    juce::Label *Manager_latency_mean_text;
    juce::Label *Manager_latency_mean_texte;

	//-- transfert of values --------
    void Met_a_jour_Manager_s_MM();  //  c++ value --> widget value
    void Process_message_Manager_s_MM();  //  widget value --> c++ value
    void Met_a_jour_Manager_opt_sound();  //  c++ value --> widget value
    void Process_message_Manager_opt_sound();  //  widget value --> c++ value
    void Met_a_jour_Manager_latency();  //  c++ value --> widget value
    void Process_message_Manager_latency();  //  widget value --> c++ value
    void Met_a_jour_Manager_latency_mean();  //  c++ value --> widget value
    void Process_message_Manager_latency_mean();  //  widget value --> c++ value

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
	int Manager_s_MM_cx = 20, Manager_s_MM_cy = 20, Manager_s_MM_wx = 600,  Manager_s_MM_wy = 600;

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
