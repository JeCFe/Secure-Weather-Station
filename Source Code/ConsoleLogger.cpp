#include <iostream>
#include "ConsoleLogger.h"


//Function used to display log to screen
void ConsoleLogger::log(string msg, string fileName = "") 
{
	cout << "LOG: " << msg << endl;
}