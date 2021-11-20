
#include "User.h" 
#include <iostream> 
#include<vector>
#include<gsl.h>


//This function is used to check fro int inputs 
bool intTest(string inpID)
{
	for (size_t i = 0; i < inpID.size(); i++) 
	{
		if (inpID.at(i) >= '0' && inpID.at(i) <= '9') { } 
		else //If any char is not an int then returns false
		{
			return false;
		}
	}
	return true; //IOf no chars are non int values returns true
}
bool strTest(string testString)
{
	for (size_t i = 0; i < testString.size(); i++)
	{
		testString.at(i) = gsl::narrow_cast<char>(toupper(testString.at(i))); //Converts each char to the upper case equivelent 
		if (testString.at(i) < 'A' || testString.at(i) > 'Z') //If any chars are not strings then returns false
		{
			return false;
		}
	}
	return true; //If all chars are string chars then returns true
}

User::User(string firstN, string lastN) 
	: firstName(firstN) , lastName(lastN) {
}

void User::enterId() {
	string input = "abc";
	do
	{
		cout << "\nEnter UserID :";
		cin >> input;
	} while (!intTest(input)); //ensures that input is an int, else the user must reenter value
	id = input;

}

//Allows to input new ID value
void User::newID(vector<User>& users) {
	string input = "abc";
	bool idNotIntUse = true; //if the ID is currently being used it cant be reassigned
	do
	{
		 input = "abc";
		 idNotIntUse = true; //if the ID is currently being used it cant be reassigned
		do
		{
			cout << "\nEnter UserID :";
			cin >> input;
		} while (!intTest(input)); //ensures that input is an int, else the user must reenter value

		for (size_t i = 0; i < users.size(); i++)
		{
			if (users.at(i).getId() == input)
			{
				idNotIntUse = false;
			}
		}
	} while (!idNotIntUse); //if the ID is being used then it cannot be reassigned
	id = input; 
}

//Allows first name entry
void User::enterFirstName(void) {
	string input = "-1";
	do
	{
		cout << "\nEnter First name :";
		cin >> input;
	} while (!strTest(input)); //Ensures that input is a string
	firstName = input;
}

//Allows last name entry
void User::enterLastName(void) {
	string input = "-1";
	do
	{
		cout << "\nEnter last name :";
		cin >> input;
	} while (!strTest(input)); //Ensures entry is string 
	lastName = input;
}

//Sets the privilage level 
void User::setPrivilageLevel(void) {

	int level = -1;
	do
	{
		cout << "[1] Admin\n[2] User" << endl;
		cout << "\nEnter privilage level: ";
		cin >> level;
		if (level != 1 && level != 2) //ensure that only 1 or 2 is enetered
		{
			level = -1;
			cout << "Bad input, try again" << endl;
		}
	} while (level == -1); //Keeps asking untile level = 1 or 2
	privilageLevel = level;
}

//Returns first name
string User::getFirstName(void) {
	return firstName;
};
//returns last name
string User::getLastName(void) {
	return lastName;
};

//returns ID
string User::getId(void) { 
	return id; 
};
//Sets user proof of ID, this is done automatically when a user logs in
void User::setProofOfID(string proof) {
	proofID = proof;
}

//Retuns proof of id
string User::getProofOfID() {
	return proofID;
}

//Sets privilageRole
void User::setPrivilageLevel(uint16_t pLevel) {
	if (pLevel == 1)
	{
		privilageRole = "Admin";
	}
	if (pLevel == 2)
	{
		privilageRole = "User";
	}
	privilageLevel = pLevel;
}

//Returns privilage level
uint16_t User::getPrivilageLevel() noexcept {
	return privilageLevel;
}

//Allows new ID to be set - FROM FILE
void User::enterId(string ID) {
	id = ID;
}
//Allows new ID to be set FROM FILE
void User::enterFirstName(string fname) {
	firstName = fname;
}

//Allows new last name ot be added FROM FILE
void User::enterLastName(string lName) {
	lastName = lName;
}

//Returns privilage role
string User::getPrivilageRole() {
	return privilageRole;
}

