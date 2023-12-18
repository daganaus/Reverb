//This code  C++ com.cc is written automatically by: makef.cc, so do write in it. It concerns a Plugin in JUCE. 
//=========================================================================================

#include "Source/JuceHeader.h"
using namespace juce;
#include "Source/processor/PluginProcessor.h"
#include "Source/editor/PluginEditor.h"
#include "Source/com.h"

#include "Source/editor/manager.h"

//-- Below is the list of 2 windows for each tab window + ZC, named: Page_ZT_j, with j=0->0


//====Constructor =========================================
Page_ZT_0::Page_ZT_0(Com *p_i)
{
   p_com = p_i;
   p_com->p_Tab_ZC = this;
   if(p_com->verbose >= 1 )
     cout<<"Page_ZT_0()"<<endl;


   //-- from the instruction of class: Manager: 
   // string s_MM = "abc"; // make_gui =  nl Editor(ZC, "Midi messages")

   p_com->Manager_s_MM_text = new juce::Label();
   p_com->Manager_s_MM_text->setText("", juce::dontSendNotification);
   addAndMakeVisible (p_com->Manager_s_MM_text);

   p_com->Manager_s_MM_button = new juce::TextButton();
   p_com->Manager_s_MM_button->setButtonText("Show Midi messages");
   p_com->Manager_s_MM_button->onClick = [this] { p_com->Process_message_Manager_s_MM(); }; // callback
   addAndMakeVisible (p_com->Manager_s_MM_button);

   //-- from the instruction of class: Manager: 
   // int opt_sound = 0; //  make_gui =  C(ZC) texxt ="opt_sound:"    help ="1: create a sound, 0: silence"

   p_com->Manager_opt_sound_text = new juce::Label();
   p_com->Manager_opt_sound_text->setText("opt_sound:", juce::dontSendNotification);
   addAndMakeVisible (p_com->Manager_opt_sound_text);

	p_com->Manager_opt_sound = new juce::ToggleButton();
   p_com->Manager_opt_sound->onClick = [this] { p_com->Process_message_Manager_opt_sound(); }; // callback
   p_com->Manager_opt_sound->setToggleState(false, juce::dontSendNotification);
   p_com->Manager_opt_sound->setTooltip("1: create a sound, 0: silence");
   addAndMakeVisible (p_com->Manager_opt_sound);

   p_com->Manager_opt_sound_texte = new juce::Label();
   p_com->Manager_opt_sound_texte->setText("", juce::dontSendNotification);
   addAndMakeVisible (p_com->Manager_opt_sound_texte);
   if(p_com->verbose >= 1 )
     cout<<"end of Page_ZT_0()"<<endl;

}

//====  Destructor =========================================
Page_ZT_0::~Page_ZT_0()
{

   delete p_com->Manager_s_MM_text;
   delete p_com->Manager_s_MM_button;
   if(p_com->Manager_s_MM != nullptr)
     delete p_com->Manager_s_MM;
   delete p_com->Manager_opt_sound_text;
   delete p_com->Manager_opt_sound;
   delete p_com->Manager_opt_sound_texte;
}

//=============================================
// resized() that is called once at the initialisation of the window and every time the window is resized by the user (if resizing is enabled). This is a good place to set the size and position of widgets so they can be positioned relative to the window bounds.
void Page_ZT_0::resized()
{

   p_com->Manager_s_MM_text->setBounds(12, 10, 0, 20 ); //  (x, y, width, height)
   p_com->Manager_s_MM_button->setBounds(12, 10, 136, 20 ); //  (x, y, width, height)

   p_com->Manager_opt_sound_text->setBounds(172, 10, 80, 20 ); //  (x, y, width, height)
   p_com->Manager_opt_sound->setBounds(252, 10, 30, 20 ); //  (x, y, width, height)
   p_com->Manager_opt_sound_texte->setBounds(282, 10, 12, 20 ); //  (x, y, width, height)
}

//=============================================
// paint() function is where all custom shapes and GUI elements are drawn to the window.
void Page_ZT_0::paint(juce::Graphics& g)
{
}
//======================
Com::Com(Editor *p_i, Manager *pManager)
{
   //cout<<"Com::Com()"<<endl;

   p_Manager = pManager;
   p_Manager->p_com = this;


   p_e = p_i;
   p_Tab_ZC = new Page_ZT_0(this);//main page
   p_e->addAndMakeVisible(p_Tab_ZC);

// ---- periodic call of function	Com::timerCallback(int ID) below
   startTimer(0, 100); // ID, period in ms
   //.....  c++ variables -> widget
   Met_a_jour_Manager_s_MM();
   Met_a_jour_Manager_opt_sound();
}
//===========
Com::~Com()
{
   p_Manager->p_com = nullptr;
   delete p_Tab_ZC;
}
//=============
void Com::resized()
{
   p_Tab_ZC->setBounds(0, 0, p_e->getWidth(), p_e->getHeight());
   p_e->setSize (326, 100); // resize the main window
}
//=============
void Com::timerCallback(int ID)
{
   if(ID == 0)
        p_Manager->Loop_manager(); // call the function
}
//===================
// function to transfert c++ variable -> widget variable
// will call Process_Manager_s_MM()
void Com::Met_a_jour_Manager_s_MM()
{
	if( Manager_s_MM == nullptr)
		return;
     Manager_s_MM_code.replaceAllContent(p_Manager->s_MM);
}
//===================
// function to transfert c++ variable -> widget variable
// will call Process_Manager_opt_sound()
void Com::Met_a_jour_Manager_opt_sound()
{
	if( Manager_opt_sound == nullptr)
		return;
    if(p_Manager->opt_sound)
       	Manager_opt_sound->setToggleState(true, juce::dontSendNotification);
    else
       	Manager_opt_sound->setToggleState(false, juce::dontSendNotification);
}
//===================
// function to transfert widget variable -> c++ variable -> parameter
void Com::Process_message_Manager_s_MM()
{
     Show_Hide_Window_Manager_s_MM();
}
//===================
// function to transfert widget variable -> c++ variable -> parameter
void Com::Process_message_Manager_opt_sound()
{
         if(Manager_opt_sound->getToggleState())
            	p_Manager->opt_sound = 1;
         else
            	p_Manager->opt_sound = 0;
}
//===================
// function to show/hide a window
void Com::Show_Hide_Window_Manager_s_MM()
{
	//---- open window 
	if(Manager_s_MM == nullptr)
	{
		Manager_s_MM =  new TCanvas_Manager_s_MM(this, "Midi messages", juce::Colour(), 1);
		auto p = p_e->processor.params; // pointer
		juce::Rectangle<int> r (p->Manager_s_MM_cx , p->Manager_s_MM_cy ,p->Manager_s_MM_wx ,p->Manager_s_MM_wy);
		Manager_s_MM->setBoundsConstrained(r);
		Manager_s_MM->setResizable(true, true);
		Manager_s_MM->setVisible(true);
		Manager_s_MM->setAlwaysOnTop(true);
		Manager_s_MM_button->setButtonText("Close Midi messages");
	}
	//---- close window 
	else
	{
		delete Manager_s_MM;
		Manager_s_MM = nullptr;
		Manager_s_MM_button->setButtonText("Show Midi messages");
	}
}
//===================================
// from line:string s_MM = "abc"; // make_gui =  nl Editor(ZC, "Midi messages")
TCanvas_Manager_s_MM::TCanvas_Manager_s_MM(Com *p_i, const juce::String &name, juce::Colour backgroundColour, int requiredButtons, bool addToDesktop) : juce::DocumentWindow(name, juce::Colours::lightgrey, DocumentWindow::allButtons)
{
    p_com = p_i;
    setResizable(true, true);
    auto p = p_com->p_e->processor.params;
    setBounds(p->Manager_s_MM_cx, p->Manager_s_MM_cy, p->Manager_s_MM_wx, p->Manager_s_MM_wy);
    setUsingNativeTitleBar (true);
    setVisible (true);
    p_editor = new CodeEditorComponent(p_com->Manager_s_MM_code,  nullptr);
    p_editor->loadContent ("\nCode Editor\n");
    addAndMakeVisible(p_editor);
}

//===================================
TCanvas_Manager_s_MM::~TCanvas_Manager_s_MM()
{
  delete p_editor;
  p_editor = nullptr;
}

//===================================
void TCanvas_Manager_s_MM::paint(juce::Graphics& g)
{
}
//==================
void TCanvas_Manager_s_MM::resized()
{
	auto p = p_com->p_e->processor.params;
	// rem: tests are due to initial call with small width (128)??
    if(getWidth() >= 200)
       p->Manager_s_MM_wx = getWidth();
    if(getHeight() >= 200)
       p->Manager_s_MM_wy = getHeight();
  if(p_editor != nullptr)
      p_editor->setBounds(0, 0,  getWidth(), getHeight());
}
//==================
void TCanvas_Manager_s_MM::moved()
{
	auto p = p_com->p_e->processor.params;
    p->Manager_s_MM_cx = getX();
    p->Manager_s_MM_cy = getY();
}
//==================
void TCanvas_Manager_s_MM::closeButtonPressed()
{
  if(p_com != nullptr)
     p_com->Show_Hide_Window_Manager_s_MM();
}
//==================
//==================
Parameters::Parameters(Manager *pManager)
{

    p_Manager =  pManager;

}
//=====================
Parameters::~Parameters()
{
}

//==================
// rem:  id_number >=0 in ParameterID below: order  is important, this is the number parameterIndex = 0,1,2,.. in  Processor::parameterValueChanged ()
void Parameters::Add_Automation_Parameters(Processor * processor)
{

}

//rem: there are 0 parameters, indexed from 0->-1

//==================
// To Save the state of the plugin
// c++ variables -> Save to DAW
void Parameters::Save_parameters(Processor * processor, MemoryBlock& destData)
{
	//cout<<"-----------"<<endl;
	//cout<<"Parameters::Save"<<endl;
//	mtx_params.lock();

    std::unique_ptr<juce::XmlElement> xml (new juce::XmlElement ("Params")); // name of the XML file 
	//... first some automatic parameters of com.h
	xml->setAttribute("Manager_s_MM_cx", Manager_s_MM_cx);
	xml->setAttribute("Manager_s_MM_cy", Manager_s_MM_cy);
	xml->setAttribute("Manager_s_MM_wx", Manager_s_MM_wx);
	xml->setAttribute("Manager_s_MM_wy", Manager_s_MM_wy);

	//... parameters of user's objects
	xml->setAttribute("Manager_opt_sound",   p_Manager->opt_sound);
	processor->copyXmlToBinary(*xml, destData);

//	mtx_params.unlock();
}

//==================
// To Load the state of the plugin
// i.e. DAW ->   c++ variable ->  widget variables -> parameters
void Parameters::Load_parameters(Processor * processor, const void* data, int sizeInBytes)
{
	//cout<<"-----------"<<endl;
	//cout<<"Parameters::Load"<<endl;
//	mtx_params.lock();

    std::unique_ptr<juce::XmlElement> xmlState (processor->getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr)
      if (xmlState->hasTagName ("Params"))  // name of the XML file
      {
	//... first some automatic parameters of com.h
	Manager_s_MM_cx  =  xmlState->getIntAttribute ("Manager_s_MM_cx", 0); // name, default value if not found
	Manager_s_MM_cy  =  xmlState->getIntAttribute ("Manager_s_MM_cy", 0); // name, default value if not found
	Manager_s_MM_wx  =  xmlState->getIntAttribute ("Manager_s_MM_wx", 300); // name, default value if not found
	Manager_s_MM_wy  =  xmlState->getIntAttribute ("Manager_s_MM_wy", 300); // name, default value if not found
	if(processor->p_com != nullptr)
		p_com->Manager_s_MM->setBounds(Manager_s_MM_cx, Manager_s_MM_cy, Manager_s_MM_wx, Manager_s_MM_wy);


	//... parameters of user's objects
	     p_Manager->opt_sound  = xmlState->getIntAttribute ("Manager_opt_sound", 0); // name, default value if not found
		     if(processor->p_com != nullptr)
		   	    processor->p_com->Met_a_jour_Manager_opt_sound(); // -> widget variable
        //cout<<"      load     value   p_Manager->opt_sound   = "<<   p_Manager->opt_sound <<endl;
        }// if xmlState

//	mtx_params.unlock();

}

//==================
// This function is called if a automation parameter is changed.
// i.e.  parameters ->  c++ variable ->  widget variables
//  Warning:   c++ variable and widget variable are accessed with the GUI thread, using a Async lambda function.
void Parameters::Transmit_Automation_Parameters(Processor * processor, int parameterIndex)
{
	//cout<<"-----------"<<endl;
	//cout<<"Parameters::Transmit"<<endl;

	if(mtx_params.try_lock())
    {
			mtx_params.unlock();
	} // try_lock
}

