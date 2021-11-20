#pragma once

#include "AuthenticationInfo.h" 
#include "User.h" 
#include "ProofID.h"

using namespace std;

class Authenticator
{
	AuthenticationInfo ainfo;
	string encryptDecrypt(string toEncrypt);
	
public:


	string initalise();
	string toEncrypt(string encyrpt);
	string dataDecrypt(string toDecrypt);
	ProofofID authenticateUser(User &s);

	void removeUser(string id);
	void addUser(string id, string pass);
}; 

