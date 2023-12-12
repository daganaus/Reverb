#include "Source/editor/manager.h" 
#include "Source/com.h" // commands GUI
#include "Source/processor/PluginProcessor.h"
#include "Source/editor/PluginEditor.h"

#include <sstream>


/*!=========================
 * Constructeur
 */
Manager::Manager()
{
}


//================
Manager::~Manager()
{
}


//========================
double 	Manager::Date_from_start() //date from t0 in sec.
{
	auto t2 = high_resolution_clock::now(); // measure of time 
	return 		duration_cast<duration<double>>(t2 - t0).count(); // duration in sec.
}

//===================
void Manager::Loop_manager()
{

	cpt_loop++;

		
	//----- Some initializations
	if(cpt_loop == 1)
		t0 = high_resolution_clock::now(); // mesure du "time point 0"
		

	//--- lecture  changements   process  to manager 
	if(changes_to_manager  >= 1) // if needed
	{
		Data_process_to_manager(); // transfer data tun to tun with a mutex.
	}
	
	//--- lecture si il y a des changements manager -> process
	if(changes_to_process >= 1)
	{
		Data_manager_to_process();
		changes_to_process = 0; // done
	}

}



//========================================
// transfer data process->tun to manager->tun with try_lock().
//  Output:  0 if done OK. 1, if not done
void Manager::Data_process_to_manager()
{
	//cout<<"Manager::Data_process_to_manager()"<<endl;

	process->mtx.lock();

	changes_to_manager = 0; // transfer has been done

	//------------------------
	process->mtx.unlock();

}



//========================================
// transfer data tun to tun with a mutex. Output:  0 if OK. 1, if not
void Manager::Data_manager_to_process()
{
	//cout<<"Manager::Data_manager_to_process(), changes_to_process="<<changes_to_process<<endl;

	process->mtx.lock();

	process->mtx.unlock();

}

