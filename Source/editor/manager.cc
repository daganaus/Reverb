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


//===================
void Manager::Loop_manager()
{

	if(changes_MM.load()  == true)  // ask to refresh display
	{
		//	cout<<"ask to refresh s_MM"<<endl;
		p_com->Met_a_jour_Manager_s_MM(); // refresh display
//		p_com->Manager_s_MM_code.moveCaretToEnd(true);
		changes_MM.store(false); // done

	}


}


