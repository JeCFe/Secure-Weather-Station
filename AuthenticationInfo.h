#pragma once
#include <utility>
#include <sstream>
#include <string>
#include <map>

using namespace std;

class AuthenticationInfo
{
	map<string, string> Users; //Creates a map of users 
	void writeToFile(void);
public:
	AuthenticationInfo(void) noexcept; // constructor sets attributes 
	string Initalise(void);
	void addUser(string username, string password);
	void removeUser(string id);
	bool validateUser(string id, string pass);
};



