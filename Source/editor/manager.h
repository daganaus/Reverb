/*
  ==============================================================================
    manager.h
    Created: 19 Jan 2023 3:22:59pm
    Author:  faure
    
    
    There is an object manager from Class Manager,
    for each Editor (one for each Plugin).
    
    It contains:
     Loop_manager() : a function that is called periodically to refresh the window and communicate changes with the process
=================================
*/


#pragma once


#include "Source/JuceHeader.h"

#include <iostream>
using namespace std;


#include <chrono>
using namespace std::chrono; 

#include "Source/processor/PluginProcessor.h"

class Processor;

//===============================
class Manager
{
public:

//----- some pointors to access objects---------------------------
	Com     * p_com = nullptr;
    Processor *process = nullptr;
    

	
	//-- GUI editor to display the messages: 
	string s_MM = "abc"; // make_gui =  nl Editor(ZC, "Midi messages")
	mutex mtx_s_MM; // because s_MM is shared between process and GUI
	atomic<bool> changes_MM = false; // 1: ask to refresh display

	//---
	int opt_sound = 0; //  make_gui =  C(ZC) texxt ="opt_sound:"    help ="1: create a sound, 0: silence"

	
	
   //----------
	// transfer data tun to tun with a mutex. Output:  0 if OK. 1, if not
	void Data_process_to_manager();
	void Data_manager_to_process();
	
//-- constructeur ------------------------
	Manager();
	~Manager();

	
//... fonction qui sera lancee toutes les  100 ms  par dans le thread  GUI
	void Loop_manager();  // make_gui = TT(100)
	int cpt_loop =0; // counter 
	
	int changes_to_process = 0; // 1 si il y a eu des chgts a transmettre a manager->process. 0 sinon.
	int changes_to_manager = 0; // 1 si il y a eu des chgts a transmettre a process->manager. 0 sinon.
	
	high_resolution_clock::time_point t0; // initial time point, for use of  precise timing. Set in manager.cc

	double 	Date_from_start_in_sec(); //date from t0 in sec. 
	


	
	
//----To detect leak memory---------------
	JUCE_LEAK_DETECTOR (Manager)
};



