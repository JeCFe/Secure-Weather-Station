#pragma once
#include "Model.h"
#include "View.h"
#include "Authenticator.h"
#include <vector>

class Controller {
	Model model;
	View view;
	bool logged{ false };
public:
	Controller() = default;
	void singleReading();
	void configureSensor(void);
	void takeReadings(void);
	void run(void);
	void initalise(Authenticator& auth, vector<User>& users);
	string UsersInitalise(vector<User>& users);
	bool login(User& user, Authenticator& authenticate, ProofofID& proofOfID, vector<User>& users);
	void decideActuation() ;
	void actuateWindSensor();
	void addUser(vector<User>& users, Authenticator& auth);
	void removeUser(vector<User>& users, Authenticator& auth, User user);
	void viewLogs();
	void wordExtractor(string word);
	void sensorControlMenu();

	void thermometerControl();
	void windControl();
	void humidityControl();
	void allControl();

	void displayDeviceLogs();
	void averageReadings(vector<int> temps, vector<uint16_t> hums, vector<uint16_t> winds);

	//Destructors 
	Controller(const Controller&) = delete;
	Controller& operator=(const Controller&) = delete;

};

