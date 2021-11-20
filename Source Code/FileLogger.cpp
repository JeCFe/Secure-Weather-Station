#include "FileLogger.h"
#include <iostream>
#include <fstream>
#include <ctime>

//This function is used to log data to a specified file
void FileLogger::log(string msg, string fileName) 
{
	try
	{
        ofstream writeFile(fileName,ofstream::app); //Opens up the file to be appended to
        writeFile.exceptions(ofstream::eofbit | ofstream::failbit | ofstream::badbit); //Sets exceptions
        if (writeFile.is_open())
        {
            writeFile << msg << endl; //Write message to file
        }
        else
        {
            cout << "File cannot be opened" << endl; //Shows if the file could not open
            
        }
        writeFile.close(); //Closes file
	}

    catch (exception e) //Following happens if any exceptions are thrown
    {
        // strstr: finds out if 2nd string is contained within 1st string.
        // Returns a pointer to occurrence of 2nd string in 1st string

        if (strstr(e.what(), "goodbit") != nullptr)
        {
            cout << "File Writtien" << endl;
        }
        else
        {
            cout << "Error Here" << endl;
            cout << "There was an error: " << e.what() << endl;
        }
    }
}
