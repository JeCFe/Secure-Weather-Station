#include "ProofID.h"
#include <iostream>

//Retursn sys proof of ID
std::string ProofofID::getproofID(void) 
{
	return proofID;
}
//Sets proof of ID
void ProofofID::setproofID(std::string aproofID) {
	proofID = aproofID;
}

//Constructer that sets proof of id 
ProofofID::ProofofID(std::string aproofID) 
	: proofID(aproofID) {};
