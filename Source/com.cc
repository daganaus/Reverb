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
   // int test = 3;   // make_gui =  HS(ZC, 0, 10) texxt ="test:"    help ="test"
   p_com->Manager_test_text = new juce::Label();
   p_com->Manager_test_text->setText("test:", juce::dontSendNotification);
   addAndMakeVisible (p_com->Manager_test_text);
   p_com->Manager_test = new juce::Slider(juce::Slider::LinearHorizontal,  Slider::TextBoxRight);
   p_com->Manager_test->setValue(3);
   p_com->Manager_test->setTextBoxStyle(Slider::TextBoxRight, true, 50, 20); // false: no editable
   p_com->Manager_test->setRange (0, 10, 1);
   p_com->Manager_test->onValueChange = [this] { p_com->Process_message_Manager_test(); }; // callback
   p_com->Manager_test->setTooltip("test");
   addAndMakeVisible (p_com->Manager_test);
   p_com->Manager_test_texte = new juce::Label();
   p_com->Manager_test_texte->setText("", juce::dontSendNotification);
   addAndMakeVisible (p_com->Manager_test_texte);
   if(p_com->verbose >= 1 )
     cout<<"end of Page_ZT_0()"<<endl;

}

//====  Destructor =========================================
Page_ZT_0::~Page_ZT_0()
{

   delete p_com->Manager_test_text;
   delete p_com->Manager_test;
   delete p_com->Manager_test_texte;
}

//=============================================
// resized() that is called once at the initialisation of the window and every time the window is resized by the user (if resizing is enabled). This is a good place to set the size and position of widgets so they can be positioned relative to the window bounds.
void Page_ZT_0::resized()
{

   p_com->Manager_test_text->setBounds(12, 10, 40, 20 ); //  (x, y, width, height)
   p_com->Manager_test->setBounds(52, 10, 120, 20 ); //  (x, y, width, height)
   p_com->Manager_test_texte->setBounds(172, 10, 12, 20 ); //  (x, y, width, height)
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
   Met_a_jour_Manager_test();
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
   p_e->setSize (196, 100); // resize the main window
}
//=============
void Com::timerCallback(int ID)
{
   if(ID == 0)
        p_Manager->Loop_manager(); // call the function
}
//===================
// function to transfert c++ variable -> widget variable
// will call Process_Manager_test()
void Com::Met_a_jour_Manager_test()
{
	if( Manager_test == nullptr)
		return;
    if(p_Manager->test != 	Manager_test->getValue())
	    Manager_test->setValue(p_Manager->test);
}
//===================
// function to transfert widget variable -> c++ variable -> parameter
void Com::Process_message_Manager_test()
{
    if(p_Manager->test != 	Manager_test->getValue())
    {
       p_Manager->test = 	Manager_test->getValue();
    }
}
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

	//... parameters of user's objects
	xml->setAttribute("Manager_test",   p_Manager->test);
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


	//... parameters of user's objects
	     p_Manager->test  = xmlState->getIntAttribute ("Manager_test", 3); // name, default value if not found
		     if(processor->p_com != nullptr)
		   	    processor->p_com->Met_a_jour_Manager_test(); // -> widget variable
        //cout<<"      load     value   p_Manager->test   = "<<   p_Manager->test <<endl;
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

