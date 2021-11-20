
#include "Authenticator.h" 
#include <time.h>  
#include <string>
#include <iostream> 


string Authenticator::initalise() {
	return ainfo.Initalise();
}
//AUtherticates user, ensurs that user name and password is correct then assigned the user and sys a proof of ID 
ProofofID Authenticator::authenticateUser(User& user)
{
	ProofofID proofofID;
	string Id = user.getId(); //gets users id
	string pass;
	string token;
	cout << "\nEnter password: ";
	cin >> pass;
	if (ainfo.validateUser(Id, pass)) //Functions tests if the password matches the username 
	{
		cout << "\nWelcome!";
		cout << "\nAuthorised!\n";
		token = encryptDecrypt(Id + pass); //Proof of ID is the encrytped username and pasword combinded. 
		proofofID = ProofofID(token); //sets sys proof of it
		user.setProofOfID(token); //sets users proof of it
		//IF SYS AND USER PROOF OF ID MATCH THIS MEANS THE CORRECT USER HAS LOGGED IN
	}
	else
	{
		cout << "Invalid user ID or password. Please try again. ";
	}
	return proofofID; //returns proof of id
}

//Encryption method is XOR, this means the data can be encrypted and decrypted in the same method
string Authenticator::encryptDecrypt(string toEncryptDecrypt)
{
	char key = 'B'; //Special encryption/decryption key
	string output = toEncryptDecrypt; 
	for (uint16_t i = 0; i < toEncryptDecrypt.size(); i++)
	{
		output.at(i) = toEncryptDecrypt.at(i) ^ key; //Encryots each char by the key
	}
	return output; //returns the encrypted string
}

//Decrypts by using encryptDecrypt and then returns the string
string Authenticator::dataDecrypt(string toDecrypt)
{
	toDecrypt = Authenticator::encryptDecrypt(toDecrypt);
	return toDecrypt;
}

//encrypts by using encrytpDecrypt and returns the string
string Authenticator::toEncrypt(string toencrypt)
{
	string data = Authenticator::encryptDecrypt(toencrypt);
	return data;
}

void Authenticator::removeUser(string id) {
	ainfo.removeUser(id);
}
void Authenticator::addUser(string id, string pass) {
	ainfo.addUser(id, pass);
}