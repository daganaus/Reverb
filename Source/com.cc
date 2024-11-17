//This code  C++ com.cc is written automatically by: makef.cc, so do write in it. It concerns a Plugin in JUCE. 
//=========================================================================================

#include "Source/JuceHeader.h"
using namespace juce;
#include "Source/processor/PluginProcessor.h"
#include "Source/editor/PluginEditor.h"
#include "Source/com.h"

#include "Source/editor/manager.h"

//#################################################
//  petite routine qui va pointer apres le prochain caractere '='
int prochaine(istream & fich)
{
	char caract;
	while(fich>>caract)
	{
		if(caract == '=')
			break;
	}
	if (fich.eof()) 
		return 0;
	else
		return 1;
}

//-- Below is the list of 3 windows for each tab window + ZC, named: Page_ZT_j, with j=0->1


//====Constructor =========================================
Page_ZT_0::Page_ZT_0(Com *p_i)
{
   p_com = p_i;
   p_com->p_Tab_ZC = this;
   if(p_com->verbose >= 1 )
     cout<<"Page_ZT_0()"<<endl;


   //-- from the instruction of class: Manager: 
   // string s_MM; // make_gui =  nl Editor(ZC, "Midi messages")

   p_com->Manager_s_MM_text = new juce::Label();
   p_com->Manager_s_MM_text->setText("", juce::dontSendNotification);
   addAndMakeVisible (p_com->Manager_s_MM_text);

   p_com->Manager_s_MM_button = new juce::TextButton();
   p_com->Manager_s_MM_button->setButtonText("Show Midi messages");
   p_com->Manager_s_MM_button->onClick = [this] { p_com->Process_message_Manager_s_MM(); }; // callback
   addAndMakeVisible (p_com->Manager_s_MM_button);

   //-- from the instruction of class: Manager: 
   // int opt_sound = 0; //  make_gui =  C(ZC) texxt ="sound:"    help ="1: create a sound, 0: silence"

   p_com->Manager_opt_sound_text = new juce::Label();
   p_com->Manager_opt_sound_text->setText("sound:", juce::dontSendNotification);
   addAndMakeVisible (p_com->Manager_opt_sound_text);

	p_com->Manager_opt_sound = new juce::ToggleButton();
   p_com->Manager_opt_sound->onClick = [this] { p_com->Process_message_Manager_opt_sound(); }; // callback
   p_com->Manager_opt_sound->setToggleState(false, juce::dontSendNotification);
   p_com->Manager_opt_sound->setTooltip("1: create a sound, 0: silence");
   addAndMakeVisible (p_com->Manager_opt_sound);

   p_com->Manager_opt_sound_texte = new juce::Label();
   p_com->Manager_opt_sound_texte->setText("", juce::dontSendNotification);
   addAndMakeVisible (p_com->Manager_opt_sound_texte);

   //-- from the instruction of class: Manager: 
   // void Display1(juce::Graphics& g); // make_gui = nl  Window(ZC, "Display1")

   p_com->Manager_Display1_text = new juce::Label();
   p_com->Manager_Display1_text->setText("", juce::dontSendNotification);
   addAndMakeVisible (p_com->Manager_Display1_text);

   p_com->Manager_Display1_button = new juce::TextButton();
   p_com->Manager_Display1_button->setButtonText("Show Display1");
   p_com->Manager_Display1_button->onClick = [this] { p_com->Process_message_Manager_Display1(); }; // callback
   addAndMakeVisible (p_com->Manager_Display1_button);

   //-- from the instruction of class: Manager: 
   // void Display2(juce::Graphics& g); // make_gui =   Window2(ZC, "Display2", 200, 200)

   p_com->Manager_Display2_text = new juce::Label();
   p_com->Manager_Display2_text->setText("", juce::dontSendNotification);
   addAndMakeVisible (p_com->Manager_Display2_text);

   p_com->Manager_Display2_button = new juce::TextButton();
   p_com->Manager_Display2_button->setButtonText("External Display2");
   p_com->Manager_Display2_button->onClick = [this] { p_com->Process_message_Manager_Display2(); }; // callback
   addAndMakeVisible (p_com->Manager_Display2_button);
   p_com->Manager_Display2 = new TCanvas_Manager_Display2(p_i, "Display2", juce::Colour(), 7); // 7:all buttons
   p_com->Manager_Display2->status = 0; //embeded
   addAndMakeVisible(p_com->Manager_Display2);

   tab = 	new juce::TabbedComponent(juce::TabbedButtonBar::TabsAtTop);
   auto colour = findColour (ResizableWindow::backgroundColourId);
   tab->addTab("Monitor", colour, new Page_ZT_1(p_com), true);
   tab->setLookAndFeel(&customLookAndFeel);
   addAndMakeVisible (tab);

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
   delete p_com->Manager_Display1_text;
   delete p_com->Manager_Display1_button;
   if(p_com->Manager_Display1 != nullptr)
     delete p_com->Manager_Display1;
   delete p_com->Manager_Display2_text;
   delete p_com->Manager_Display2_button;
   if(p_com->Manager_Display2 != nullptr)
     delete p_com->Manager_Display2;

   delete tab;

}

//=============================================
// resized() that is called once at the initialisation of the window and every time the window is resized by the user (if resizing is enabled). This is a good place to set the size and position of widgets so they can be positioned relative to the window bounds.
void Page_ZT_0::resized()
{

   p_com->Manager_s_MM_text->setBounds(12, 10, 0, 20 ); //  (x, y, width, height)
   p_com->Manager_s_MM_button->setBounds(12, 10, 136, 20 ); //  (x, y, width, height)

   p_com->Manager_opt_sound_text->setBounds(172, 10, 48, 20 ); //  (x, y, width, height)
   p_com->Manager_opt_sound->setBounds(220, 10, 30, 20 ); //  (x, y, width, height)
   p_com->Manager_opt_sound_texte->setBounds(250, 10, 12, 20 ); //  (x, y, width, height)

   p_com->Manager_Display1_text->setBounds(12, 40, 0, 20 ); //  (x, y, width, height)
   p_com->Manager_Display1_button->setBounds(12, 40, 96, 20 ); //  (x, y, width, height)

   p_com->Manager_Display2_text->setBounds(132, 40, 0, 20 ); //  (x, y, width, height)
   p_com->Manager_Display2_button->setBounds(132, 40, 96, 20 ); //  (x, y, width, height)
   p_com->Manager_Display2->setBounds(132, 60, 200, 200 ); //  (x, y, width, height)

   tab->setBounds(0, 270, 512, 65);// x,y,w,h

}

//=============================================
// paint() function is where all custom shapes and GUI elements are drawn to the window.
void Page_ZT_0::paint(juce::Graphics& g)
{
}

//====Constructor =========================================
Page_ZT_1::Page_ZT_1(Com *p_i)
{
   p_com = p_i;
   p_com->p_Tab_Monitor = this;
   if(p_com->verbose >= 1 )
     cout<<"Page_ZT_1()"<<endl;


   //-- from the instruction of class: Manager: 
   // double latency = 0; // make_gui = nl PB(ZT("Monitor"), 0, 1.)  texxt="latency max:"   help = "Maximum latency of the last events, percentage of available time for the processor"
   p_com->Manager_latency_text = new juce::Label();
   p_com->Manager_latency_text->setText("latency max:", juce::dontSendNotification);
   addAndMakeVisible (p_com->Manager_latency_text);
   p_com->Manager_latency_x = 0;
   p_com->Manager_latency = new juce::ProgressBar(p_com->Manager_latency_x);
   p_com->Manager_latency->setTooltip("Maximum latency of the last events, percentage of available time for the processor");
   addAndMakeVisible (p_com->Manager_latency);
   p_com->Manager_latency_texte = new juce::Label();
   p_com->Manager_latency_texte->setText("", juce::dontSendNotification);
   addAndMakeVisible (p_com->Manager_latency_texte);

   //-- from the instruction of class: Manager: 
   // double latency_mean = 0; // make_gui =  PB(ZT("Monitor"), 0, 1.)  texxt="latency mean:"   help = "Mean latency of the last events, averaged over the last 1000 blocks"
   p_com->Manager_latency_mean_text = new juce::Label();
   p_com->Manager_latency_mean_text->setText("latency mean:", juce::dontSendNotification);
   addAndMakeVisible (p_com->Manager_latency_mean_text);
   p_com->Manager_latency_mean_x = 0;
   p_com->Manager_latency_mean = new juce::ProgressBar(p_com->Manager_latency_mean_x);
   p_com->Manager_latency_mean->setTooltip("Mean latency of the last events, averaged over the last 1000 blocks");
   addAndMakeVisible (p_com->Manager_latency_mean);
   p_com->Manager_latency_mean_texte = new juce::Label();
   p_com->Manager_latency_mean_texte->setText("", juce::dontSendNotification);
   addAndMakeVisible (p_com->Manager_latency_mean_texte);
   if(p_com->verbose >= 1 )
     cout<<"end of Page_ZT_1()"<<endl;

}

//====  Destructor =========================================
Page_ZT_1::~Page_ZT_1()
{

   delete p_com->Manager_latency_text;
   delete p_com->Manager_latency;
   delete p_com->Manager_latency_texte;
   delete p_com->Manager_latency_mean_text;
   delete p_com->Manager_latency_mean;
   delete p_com->Manager_latency_mean_texte;
}

//=============================================
// resized() that is called once at the initialisation of the window and every time the window is resized by the user (if resizing is enabled). This is a good place to set the size and position of widgets so they can be positioned relative to the window bounds.
void Page_ZT_1::resized()
{

   p_com->Manager_latency_text->setBounds(12, 10, 96, 20 ); //  (x, y, width, height)
   p_com->Manager_latency->setBounds(108, 10, 120, 20 ); //  (x, y, width, height)
   p_com->Manager_latency_texte->setBounds(228, 10, 12, 20 ); //  (x, y, width, height)

   p_com->Manager_latency_mean_text->setBounds(264, 10, 104, 20 ); //  (x, y, width, height)
   p_com->Manager_latency_mean->setBounds(368, 10, 120, 20 ); //  (x, y, width, height)
   p_com->Manager_latency_mean_texte->setBounds(488, 10, 12, 20 ); //  (x, y, width, height)
}

//=============================================
// paint() function is where all custom shapes and GUI elements are drawn to the window.
void Page_ZT_1::paint(juce::Graphics& g)
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
   Met_a_jour_Manager_Display1();
   Met_a_jour_Manager_Display2();
   Met_a_jour_Manager_latency();
   Met_a_jour_Manager_latency_mean();
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
   p_e->setSize (512, 335); // resize the main window
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
// function to transfert c++ variable -> widget variable
// will call Process_Manager_Display1()
void Com::Met_a_jour_Manager_Display1()
{
	if( Manager_Display1 == nullptr)
		return;
}
//===================
// function to transfert c++ variable -> widget variable
// will call Process_Manager_Display2()
void Com::Met_a_jour_Manager_Display2()
{
	if( Manager_Display2 == nullptr)
		return;
}
//===================
// function to transfert c++ variable -> widget variable
// will call Process_Manager_latency()
void Com::Met_a_jour_Manager_latency()
{
	if( Manager_latency == nullptr)
		return;
	double x = 0; //in [0,1];
	x = (p_Manager->latency - 0) / double(1);
	if(x>1)
	   x=1;
	if(x<0)
	   x=0;
	Manager_latency_x = x;
}
//===================
// function to transfert c++ variable -> widget variable
// will call Process_Manager_latency_mean()
void Com::Met_a_jour_Manager_latency_mean()
{
	if( Manager_latency_mean == nullptr)
		return;
	double x = 0; //in [0,1];
	x = (p_Manager->latency_mean - 0) / double(1);
	if(x>1)
	   x=1;
	if(x<0)
	   x=0;
	Manager_latency_mean_x = x;
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
// function to transfert widget variable -> c++ variable -> parameter
void Com::Process_message_Manager_Display1()
{
     Show_Hide_Window_Manager_Display1();
}
//===================
// function to transfert widget variable -> c++ variable -> parameter
void Com::Process_message_Manager_Display2()
{
     Show_Hide_Window_Manager_Display2();
}
//===================
// function to transfert widget variable -> c++ variable -> parameter
void Com::Process_message_Manager_latency()
{
	double x = 	Manager_latency_x; //in [0,1];
	x = x* 1 + 0;
	Manager_latency_x = x;

}
//===================
// function to transfert widget variable -> c++ variable -> parameter
void Com::Process_message_Manager_latency_mean()
{
	double x = 	Manager_latency_mean_x; //in [0,1];
	x = x* 1 + 0;
	Manager_latency_mean_x = x;

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
		Met_a_jour_Manager_s_MM(); // refresh display
	}
	//---- close window 
	else
	{
		delete Manager_s_MM;
		Manager_s_MM = nullptr;
		Manager_s_MM_button->setButtonText("Show Midi messages");
	}
}
//===================
// function to show/hide a window
void Com::Show_Hide_Window_Manager_Display1()
{
	//---- open window 
	if(Manager_Display1 == nullptr)
	{
		Manager_Display1 =  new TCanvas_Manager_Display1(this, "Display1", juce::Colour(), 1);
		auto p = p_e->processor.params; // pointer
		juce::Rectangle<int> r (p->Manager_Display1_cx , p->Manager_Display1_cy ,p->Manager_Display1_wx ,p->Manager_Display1_wy);
		Manager_Display1->setBoundsConstrained(r);
		Manager_Display1->setResizable(true, true);
		Manager_Display1->setVisible(true);
		Manager_Display1->setAlwaysOnTop(true);
		Manager_Display1_button->setButtonText("Close Display1");
		Met_a_jour_Manager_Display1(); // refresh display
	}
	//---- close window 
	else
	{
		delete Manager_Display1;
		Manager_Display1 = nullptr;
		Manager_Display1_button->setButtonText("Show Display1");
	}
}
//===================
// function to show/hide a window
// we shift: delete -> internal -> external -> delete
void Com::Show_Hide_Window_Manager_Display2()
{
	//---- open window 
	if(Manager_Display2 == nullptr)  // deleted -> internal
	{
	  Manager_Display2 = new TCanvas_Manager_Display2(this, "Display2", juce::Colour(), 7); // 7:all buttons
	  p_Tab_ZC->addAndMakeVisible(Manager_Display2);
	  Manager_Display2->setBounds( 132, 60, 200, 200); // x,y,w,h
	  Manager_Display2->status = 0; //internal
	  Manager_Display2_button->setButtonText("External Display2");
	}
	//----
	else if(Manager_Display2 != nullptr != 0 && Manager_Display2->status == 0) // internal -> external
	{
	  delete Manager_Display2;
	  Manager_Display2 = nullptr;
	
	  //............
	  Manager_Display2 =  new TCanvas_Manager_Display2(this, "Display2", juce::Colour(), 7);
	  auto p = p_e->processor.params; // pointer
	  juce::Rectangle<int> r (p->Manager_Display2_cx , p->Manager_Display2_cy ,p->Manager_Display2_wx ,p->Manager_Display2_wy);
	  Manager_Display2->setBoundsConstrained(r);
	  Manager_Display2->setResizable(true, true);
	  Manager_Display2->setVisible(true);
	  Manager_Display2->setAlwaysOnTop(true);
	
	  Manager_Display2->status = 1; //external
	  Manager_Display2_button->setButtonText("Delete Display2");
	}
	//----
	else if(Manager_Display2 != nullptr != 0 && Manager_Display2->status == 1) // external -> delete
	{
	  delete Manager_Display2;
	  Manager_Display2 = nullptr;
	  Manager_Display2_button->setButtonText("Internal Display2");
	}
}
//===================================
// from line:string s_MM; // make_gui =  nl Editor(ZC, "Midi messages")
TCanvas_Manager_s_MM::TCanvas_Manager_s_MM(Com *p_i, const juce::String &name, juce::Colour backgroundColour, int requiredButtons, bool addToDesktop) : juce::DocumentWindow(name, juce::Colours::lightgrey, DocumentWindow::allButtons)
{
    p_com = p_i;
    setResizable(true, true);
    auto p = p_com->p_e->processor.params;
    setBounds(p->Manager_s_MM_cx, p->Manager_s_MM_cy, p->Manager_s_MM_wx, p->Manager_s_MM_wy);
    setUsingNativeTitleBar (true);
    setVisible (true);
    p_editor = new CodeEditorComponent(p_com->Manager_s_MM_code,  nullptr);
    p_editor->loadContent ("\nEmpty for the moment\n");
    //.... for scrolling properties
    viewport.setViewedComponent(p_editor, true);
    addAndMakeVisible(&viewport);
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
   g.fillAll(juce::Colours::lightgrey);
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
  {
      p_editor->setBounds(0, 0,  getWidth(), getHeight());
      viewport.setBounds(getLocalBounds());
  }
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
//===================================
// from line:void Display1(juce::Graphics& g); // make_gui = nl  Window(ZC, "Display1")
TCanvas_Manager_Display1::TCanvas_Manager_Display1(Com *p_i, const juce::String &name, juce::Colour backgroundColour, int requiredButtons, bool addToDesktop) : juce::DocumentWindow(name, juce::Colours::lightgrey, DocumentWindow::allButtons)
{
    p_com = p_i;
    setResizable(true, true);
    auto p = p_com->p_e->processor.params;
    setBounds(p->Manager_Display1_cx, p->Manager_Display1_cy, p->Manager_Display1_wx, p->Manager_Display1_wy);
    setUsingNativeTitleBar (true);
    setVisible (true);
}

//===================================
TCanvas_Manager_Display1::~TCanvas_Manager_Display1()
{
}

//===================================
void TCanvas_Manager_Display1::paint(juce::Graphics& g)
{
   p_com->p_Manager->Display1(g);
}
//==================
void TCanvas_Manager_Display1::resized()
{
	auto p = p_com->p_e->processor.params;
	// rem: tests are due to initial call with small width (128)??
    if(getWidth() >= 200)
       p->Manager_Display1_wx = getWidth();
    if(getHeight() >= 200)
       p->Manager_Display1_wy = getHeight();
}
//==================
void TCanvas_Manager_Display1::moved()
{
	auto p = p_com->p_e->processor.params;
    p->Manager_Display1_cx = getX();
    p->Manager_Display1_cy = getY();
}
//==================
void TCanvas_Manager_Display1::closeButtonPressed()
{
  if(p_com != nullptr)
     p_com->Show_Hide_Window_Manager_Display1();
}
//==================
//===================================
// from line:void Display2(juce::Graphics& g); // make_gui =   Window2(ZC, "Display2", 200, 200)
TCanvas_Manager_Display2::TCanvas_Manager_Display2(Com *p_i, const juce::String &name, juce::Colour backgroundColour, int requiredButtons, bool addToDesktop) : juce::DocumentWindow(name, juce::Colours::lightgrey, DocumentWindow::allButtons)
{
    p_com = p_i;
    setResizable(true, true);
    auto p = p_com->p_e->processor.params;
    setBounds(p->Manager_Display2_cx, p->Manager_Display2_cy, p->Manager_Display2_wx, p->Manager_Display2_wy);
    setUsingNativeTitleBar (true);
    setVisible (true);
}

//===================================
TCanvas_Manager_Display2::~TCanvas_Manager_Display2()
{
}

//===================================
void TCanvas_Manager_Display2::paint(juce::Graphics& g)
{
   p_com->p_Manager->Display2(g);
}
//==================
void TCanvas_Manager_Display2::resized()
{
	auto p = p_com->p_e->processor.params;
	// rem: tests are due to initial call with small width (128)??
    if(getWidth() >= 200)
       p->Manager_Display2_wx = getWidth();
    if(getHeight() >= 200)
       p->Manager_Display2_wy = getHeight();
}
//==================
void TCanvas_Manager_Display2::moved()
{
	auto p = p_com->p_e->processor.params;
    p->Manager_Display2_cx = getX();
    p->Manager_Display2_cy = getY();
}
//==================
void TCanvas_Manager_Display2::closeButtonPressed()
{
  if(p_com != nullptr)
     p_com->Show_Hide_Window_Manager_Display2();
}
//==================



//---- Some functions useful below
//===================================
// remplace 'search' par 'replace' partout dans la chaine 'subject'. Output:  'subject'
void ReplaceStringInPlace(string& subject, const string& search, const string& replace)
{
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != string::npos)
	{
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}

//==========================
template <typename T>
ostream & operator <<(ostream & s,  const vector<T> & l)
{
	
	s<<"vector<T>, size="<<l.size()<<endl;

	for(auto n: l)	
    {
    	if constexpr(is_same<T, string>::value) // si type string
    					{
    						cout<<"<< string"<<endl;
    						ReplaceStringInPlace(n, " ","'"); // replace " " by "'"
    						ReplaceStringInPlace(n, "\n","~"); // replace "\n" by "~"
    					}
    	s<<n<<endl;
    }

	return s;
}

//==========================
template <typename T>
istream & operator >>(istream & s,  vector<T> & l)
{

	int size;
	prochaine(s);   	s>>size;
	l.clear();

	for(int i=0; i<size; i++)
	{
		T n;
		s>>n;
			if constexpr(is_same<T, string>::value) // si type string
							{
								cout<<">> string"<<endl;
								ReplaceStringInPlace(n, "'"," "); // replace "'" by " "
								ReplaceStringInPlace(n, "~","\n"); // replace "~" by "\n"
							}
		l.push_back(n);
	}

	return s;
}

//==========================
template <typename T>
void Transfer(const string &s, vector<T> & l)
{
	//cout<<"Transfer file -> string ->  object"<<endl;

	istringstream ss(s);
	int size = 0;
	int res = prochaine(ss);
	if(res == 1)
	{
		ss>>size;

		l.clear();

		for(int i=0; i<size; i++)
		{
			T n;
			ss >> n;
      	    if constexpr(is_same<T, string>::value) // si type string
             {
		      ReplaceStringInPlace(n, "'"," "); // replace "'" by " "
		      ReplaceStringInPlace(n, "~","\n"); // replace "~" by "\n"
             }
		    l.push_back(n);
		}
	}
	//cout<<"res="<<res<<" size="<<size<<endl;
}

//=========================
template <typename T>
void Transfer(const vector<T> & l, string &s)
{
	//cout<<"Transfer object -> string ->  file"<<endl;

	ostringstream ss;
	ss<<"vector<int>, size="<<l.size()<<endl;

	for(auto n: l)
    {
    	if constexpr(is_same<T, string>::value) // si type string
         {
		   ReplaceStringInPlace(n, " ","'"); // replace " " by "'"
		   ReplaceStringInPlace(n, "\n","~"); // replace "\n" by "~"
         }
		ss << n << endl;
    }

	s = ss.str();
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
void Parameters::Save_parameters(string name_params, Processor * processor, MemoryBlock& destData)
{
	//cout<<"-----------"<<endl;
	//cout<<"Parameters::Save"<<endl;
//	mtx_params.lock();

    std::unique_ptr<juce::XmlElement> xml (new juce::XmlElement (name_params.c_str())); // name of the XML file 

	//... first some automatic parameters of com.h
	xml->setAttribute("Manager_s_MM_cx", Manager_s_MM_cx);
	xml->setAttribute("Manager_s_MM_cy", Manager_s_MM_cy);
	xml->setAttribute("Manager_s_MM_wx", Manager_s_MM_wx);
	xml->setAttribute("Manager_s_MM_wy", Manager_s_MM_wy);
	xml->setAttribute("Manager_Display1_cx", Manager_Display1_cx);
	xml->setAttribute("Manager_Display1_cy", Manager_Display1_cy);
	xml->setAttribute("Manager_Display1_wx", Manager_Display1_wx);
	xml->setAttribute("Manager_Display1_wy", Manager_Display1_wy);
	xml->setAttribute("Manager_Display2_cx", Manager_Display2_cx);
	xml->setAttribute("Manager_Display2_cy", Manager_Display2_cy);
	xml->setAttribute("Manager_Display2_wx", Manager_Display2_wx);
	xml->setAttribute("Manager_Display2_wy", Manager_Display2_wy);


    //.. some automatic parameters related to objects, command S()
    // in case of compilation error, check if you need to add a function operator << or >> above
	//... parameters of user's objects
	xml->setAttribute("Manager_opt_sound",   p_Manager->opt_sound);
	xml->setAttribute("Manager_latency",   p_Manager->latency);
	xml->setAttribute("Manager_latency_mean",   p_Manager->latency_mean);
	processor->copyXmlToBinary(*xml, destData);

//	mtx_params.unlock();
}

//==================
// To Load the state of the plugin
// i.e. DAW ->   c++ variable ->  widget variables -> parameters
void Parameters::Load_parameters(string name_params, Processor * processor, const void* data, int sizeInBytes)
{
	//cout<<"-----------"<<endl;
	//cout<<"Parameters::Load"<<endl;
//	mtx_params.lock();

    std::unique_ptr<juce::XmlElement> xmlState (processor->getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr)
      if (xmlState->hasTagName (name_params.c_str()))  // name of the XML file
      {
	//... first some automatic parameters of com.h
	Manager_s_MM_cx  =  xmlState->getIntAttribute ("Manager_s_MM_cx", 0); // name, default value if not found
	Manager_s_MM_cy  =  xmlState->getIntAttribute ("Manager_s_MM_cy", 0); // name, default value if not found
	Manager_s_MM_wx  =  xmlState->getIntAttribute ("Manager_s_MM_wx", 300); // name, default value if not found
	Manager_s_MM_wy  =  xmlState->getIntAttribute ("Manager_s_MM_wy", 300); // name, default value if not found
	if(processor->p_com != nullptr && 	p_com->Manager_s_MM != nullptr)
		p_com->Manager_s_MM->setBounds(Manager_s_MM_cx, Manager_s_MM_cy, Manager_s_MM_wx, Manager_s_MM_wy);
	Manager_Display1_cx  =  xmlState->getIntAttribute ("Manager_Display1_cx", 0); // name, default value if not found
	Manager_Display1_cy  =  xmlState->getIntAttribute ("Manager_Display1_cy", 0); // name, default value if not found
	Manager_Display1_wx  =  xmlState->getIntAttribute ("Manager_Display1_wx", 300); // name, default value if not found
	Manager_Display1_wy  =  xmlState->getIntAttribute ("Manager_Display1_wy", 300); // name, default value if not found
	if(processor->p_com != nullptr && 	p_com->Manager_Display1 != nullptr)
		p_com->Manager_Display1->setBounds(Manager_Display1_cx, Manager_Display1_cy, Manager_Display1_wx, Manager_Display1_wy);
	Manager_Display2_cx  =  xmlState->getIntAttribute ("Manager_Display2_cx", 0); // name, default value if not found
	Manager_Display2_cy  =  xmlState->getIntAttribute ("Manager_Display2_cy", 0); // name, default value if not found
	Manager_Display2_wx  =  xmlState->getIntAttribute ("Manager_Display2_wx", 300); // name, default value if not found
	Manager_Display2_wy  =  xmlState->getIntAttribute ("Manager_Display2_wy", 300); // name, default value if not found
	if(processor->p_com != nullptr && 	p_com->Manager_Display2 != nullptr)
		p_com->Manager_Display2->setBounds(Manager_Display2_cx, Manager_Display2_cy, Manager_Display2_wx, Manager_Display2_wy);


	//.. some automatic parameters related to objects, command S()
	//... parameters of user's objects
	     p_Manager->opt_sound  = xmlState->getIntAttribute ("Manager_opt_sound", 0); // name, default value if not found
		     if(processor->p_com != nullptr)
		   	    processor->p_com->Met_a_jour_Manager_opt_sound(); // -> widget variable
        //cout<<"      load     value   p_Manager->opt_sound   = "<<   p_Manager->opt_sound <<endl;
	   p_Manager->latency  =  xmlState->getDoubleAttribute ("Manager_latency", 0); // name, default value if not found
	   if(processor->p_com != nullptr)
		   processor->p_com->Met_a_jour_Manager_latency(); // -> widget variable
        //cout<<"      load     value   p_Manager->latency   = "<<   p_Manager->latency <<endl;
	   p_Manager->latency_mean  =  xmlState->getDoubleAttribute ("Manager_latency_mean", 0); // name, default value if not found
	   if(processor->p_com != nullptr)
		   processor->p_com->Met_a_jour_Manager_latency_mean(); // -> widget variable
        //cout<<"      load     value   p_Manager->latency_mean   = "<<   p_Manager->latency_mean <<endl;
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

