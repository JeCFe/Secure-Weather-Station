#include "ConsoleLogger.h"
#include "FileLogger.h"
#include "AuthenticationInfo.h" 
#include"Authenticator.h"
#include <iostream> 
#include<fstream>

using namespace std;

AuthenticationInfo::AuthenticationInfo(void) noexcept{};

string AuthenticationInfo::Initalise() 
{ 
    string str;
    string id;
    string pass;
    string strRet = "";
    Authenticator auth;
    try
    {
        ifstream readFile("ainfoData.txt"); //Opens file ainfoData
        readFile.exceptions(ifstream::failbit | ifstream::badbit); //sets exceptions for the file to be open
        if (readFile.is_open())
        {
            while (readFile.peek() != EOF) //ensure the next char read is not EOF
            {
                getline(readFile, str); //Gets the next line from the file and outputs to the str
                id = auth.dataDecrypt(str);//Decrypts ID
                getline(readFile, str);
                pass = auth.dataDecrypt(str);//Decrypts Password
                Users.insert(pair<string, string>(id, pass)); //Adds the user and password to the map
            }
            readFile.close(); //Closes file
            strRet = "Authorisation initalised";
            return strRet; //returns that Authorisation initalised 
        }
        else
        {
            return "File could not open"; //Returns if file could not open
        }
    }
    catch (exception e) //Catches when exceptions are thrown
    {

            strRet = "Authorisation error has occured ";
            cout << strRet << e.what() << endl;
            return strRet;
        
    }
}

//This function is used to write the ainfo data is writtien to a file 
void AuthenticationInfo::writeToFile()
{
    Authenticator auth;
    map<string, string>::iterator it; //Creates a map with can be iterated 

    it = Users.begin(); //defines the begining of the iterator 
    try
    {
        ofstream writeFile("ainfoData.txt", ofstream::out, ofstream::trunc); //opens file to write too
        writeFile.exceptions(ofstream::eofbit | ofstream::failbit | ofstream::badbit); //Sets exceptions
            while (it != Users.end())
            {
                string id = auth.toEncrypt(it->first.data()); //encrypts id from map
                string pass = auth.toEncrypt(it->second.data()); //encrypts pass from map

                writeFile << id << endl; //writes to file
                writeFile << pass << endl; //writes to file
                it++;
            }
            writeFile.close(); //closes file
    }

    catch (exception e)
    {
        if (strstr(e.what(), "eofbit") != nullptr) { cout << "LOG: END OF FILE REACHED" << endl; }
        else { cout << "LOG: There was an error: " << e.what() << endl; }
    }
}


 //determines whether a user-specified PIN matches PIN in Account
bool AuthenticationInfo::validateUser(string ID, string pass)
{
	bool validUser = false;
	map<string, string>::iterator it; //Iterator to search for user
	it = Users.find(ID);
	if (it != Users.end())
	{
		if (!(it->second.compare(pass))) //If ID and Pass match then user found
		{
			validUser = true;
		}
	}
	return validUser;
} 

//When a new user has been add their detials are added to the pair list, and then writtien to a file
void AuthenticationInfo::addUser(string username, string password)
{
    Users.insert(pair<string, string>(username, password)); //Adds user to map
    writeToFile(); //Writes user ainfo to file
}

//When removing a user thier details are found in the map, then removed, the new map is writtien to a file
void AuthenticationInfo::removeUser(string id)
{
    map<string, string>::iterator it; //iterator to search for user to remove
    it = Users.find(id);
    Users.erase(it); //removes user from map
    writeToFile();
}