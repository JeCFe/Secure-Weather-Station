#pragma once
#include <string>
#include<vector>
using namespace std;
class User {

	string id;
	string firstName;
	string lastName;
	string proofID;
	uint16_t privilageLevel = 2;
	string privilageRole;

public:
	User(string firstN ="", string lastN="");
	string getId(void);
	void newID(vector<User>& users);
	void enterId(string ID);
	void enterFirstName(void);
	void enterFirstName(string firstName);
	string getFirstName(void);
	string getLastName(void);
	void enterLastName(string lastName);
	void enterLastName(void);
	string getProofOfID(void);
	void setProofOfID(string proof);
	void setPrivilageLevel(uint16_t privilageLevel);
	void setPrivilageLevel(void);
	uint16_t getPrivilageLevel() noexcept;
	string getPrivilageRole();
	void enterId();
};





