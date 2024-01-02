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
	string s_MM; // make_gui =  nl Editor(ZC, "Midi messages")
	mutex mtx_s_MM; // because s_MM is shared between process and GUI
	atomic<bool> changes_MM = false; // 1: ask to refresh display

	//---
	int opt_sound = 0; //  make_gui =  C(ZC) texxt ="sound:"    help ="1: create a sound, 0: silence"

	
	
	
//-- constructeur ------------------------
	Manager();
	~Manager();

	
//... fonction qui sera lancee toutes les  100 ms  par dans le thread  GUI
	void Loop_manager();  // make_gui = TT(100)
	

	//--- latency of the processor
	double latency = 0; // make_gui = nl PB(ZT("Monitor"), 0, 1.)  texxt="latency max:"   help = "Maximum latency of the last events, percentage of available time for the processor"

	int T_latency = 10; // period (number of cycles) for display latency in manager.cc,  


	double latency_mean = 0; // make_gui =  PB(ZT("Monitor"), 0, 1.)  texxt="latency mean:"   help = "Mean latency of the last events, averaged over the last 1000 blocks"
	int N_latency = 0; 
	double  S_latency = 0; 


	
//----To detect leak memory---------------
	JUCE_LEAK_DETECTOR (Manager)
};



