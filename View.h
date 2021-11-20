#pragma once
#include <string>
#include "Model.h"
#include "Choice.h" 
#include "LogChoice.h"
#include "User.h"
#include "SensorChoice.h"
#include "SensorCommands.h"

class View {
public:
	void printModelDetails(const Model &m) const;
	Choice mainMenu(User& user);
	void displayData(string hour, string temp, string tempConvert, string hum, string speed, string mphSpeed, string state);
	void displayHeader(void);
	void understandLog();
	void message(std::string s);
	LogChoice logMenu();
	SensorChoice sensorMenu();
	SensorCommands sensorCommands(int specialCommands = 0);
	void understandingData();
	void displayAverage(int avTemps, uint16_t avHums, uint16_t avWinds);
	//input validation
	bool intTest(string inpID);


};