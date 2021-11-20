#include "Model.h"
#include <string>

Model::Model() 
	: fileLogger(make_unique<LoggerDecorator>(make_unique<FileLogger>(),
		static_cast<uint16_t>(1))) //Creates a FileLogger, sets this as a no format LoggerDectorator 
{ }


	//Getters
	int Model::getTemperature(void) const noexcept  { return temp.read(); }
	int Model::getHumidity(void) const noexcept { return humidity.read(); }
	int Model::getTempConvert() noexcept { return temp.getFarTemp(); }
	float Model::getWindSpeedMPH() noexcept { return windSensor.getmphSpeed(); }
	uint16_t Model::getWindSpeed() const noexcept { return windSensor.read(); }
	uint16_t Model::getMaxSpeed() noexcept { return windSensor.getMxTolSpeed(); }
	int Model::getSampling(void) noexcept { return samplingPeriod; }
	operatingState Model::getOperatingState() const noexcept { return windSensor.getOpState(); }
	string Model::getThermometerName() const { return temp.getName(); }
	string Model::getHumidityName() const { return humidity.getName(); }
	string Model::getWindName() const { return windSensor.getName(); }


	//Sets the sampeling size
	void Model::setSampling(const int sampling) { samplingPeriod = sampling; deviceLog("Sampling changed to" + to_string(sampling)); }

	void Model::setHumidity(const uint16_t h)  { humidity.write(h); deviceLog("Humiditiy reading taken");}

	//Actuates wind sensor, and writes this to device log
	void Model::sensorActuate()  { windSensor.actuate(); deviceLog("Wind sensor actuated"); }

	void Model::setTemperature(const int t) { temp.write(t); deviceLog("Thermometer reading taken"); }
	void Model::setWindSpeed(uint16_t speed)  { windSensor.write(speed); deviceLog("Wind recording taken"); }

	//Conifgures for each of the 3 sensors
	void Model::configureTemp()  { temp.configure(); deviceLog("Thermometer configured"); }
	void Model::configureHumidity()  { humidity.configure(); deviceLog("Humidity configured"); }
	void Model::configureWind()  { windSensor.config(); deviceLog("Wind sensor configured"); }

	//Returns if the sensors are on or off 
	State Model::getTemperatureState() noexcept { return temp.getState(); }
	State Model::getHumidityState() noexcept { return humidity.getState(); }
	State Model::getWindSensorState() noexcept { return windSensor.getState(); }

	//Turn on functions for each of the
	void Model::tempatureOn()  { temp.on(); deviceLog("Thermometer switched on");}
	void Model::windSensorOn()  { windSensor.on(); deviceLog("Wind sensor switched on");}
	void Model::humidityOn()  { humidity.on(); deviceLog("Humidity sensor switched on"); }

	//Turns off the sensors
	void Model::temperatureOff()  { temp.off(); deviceLog("Thermomter sensor switched off"); }
	void Model::windSensorOff()  { windSensor.off(); deviceLog("wind sensor sensor switched off"); }
	void Model::humidityOff()  { humidity.off(); deviceLog("Humidity sensor switched off"); }

	//Functions used to write sensor data to a file
	void Model::saveToFile(int hour, int temperature, int tempConvert, uint16_t hum, uint16_t speed, float mphSpeed, string state)
	{
		//Creates a string using all the sensor data
		string fileOutput = to_string(hour) + " " + to_string(temperature) + " " + to_string(tempConvert) + " " + to_string(hum) + " " + to_string(speed) + " " + to_string(mphSpeed) + " " + state;
		if (fileLogger!=nullptr) //If fileLogger is not a nullptr
		{
			fileLogger->log(fileOutput, "historicData.txt"); //Write the string using the loggerto a file
		}
	}

	//Adds a new user
	void Model::addUser(vector<User>& users, Authenticator& auth) {
		//Obtains all the required information to creata new user
		User newUser;
		newUser.enterFirstName();
		newUser.enterLastName();
		newUser.newID(users);
		newUser.setPrivilageLevel();
		string password = "";
		cout << "Please enter user password: " << endl;
		cin >> password;
		auth.addUser(newUser.getId(), password); //Creates a new entry in ainfo
		users.push_back(newUser); //Adds the user to the users vector
		cout << "User: " << newUser.getFirstName() << " " << newUser.getLastName() << endl; //Show who was added
		writeUsersToFile(users); //Write the users to the file
		deviceLog("User added");//Log that users were added
	}

	//Saved users to file
	void Model::writeUsersToFile(vector<User>& users ) {
		try
		{
			//Opens up a file, sets the conditions to out and to added to the end of the file
			ofstream writeFile("userData.txt", ofstream::out, ofstream::trunc);
			writeFile.exceptions(ofstream::eofbit | ofstream::failbit | ofstream::badbit | ofstream::goodbit); //Sets exceptions
			if (writeFile.is_open())
			{
				for (size_t i = 0; i < users.size(); i++) //for loops through users
				{
					writeFile << users.at(i).getId() << endl; //Write ID
					writeFile << users.at(i).getFirstName() << endl; //Writes first name
					writeFile << users.at(i).getLastName() << endl; //write last name
					writeFile << to_string(users.at(i).getPrivilageLevel()) << endl; //Write privilage level
				}
				writeFile.close(); //closes file
			}
		}
		catch (exception e) //Catches any exceptions 
		{
			//If theres an errors the following happens
			if (strstr(e.what(), "goodbit") != nullptr) { cout << "File Writtien" << endl; }
			else { cout << "There was an error: " << e.what() << endl; }
		}
	}

	//retrieves data from a file
	vector<string> Model::retriveDataFromDatabase(string fileName) {
		vector<string> databaseData;
		string str;
		try
		{
			//opens designated file using fileName
			ifstream readFile(fileName);
			readFile.exceptions(ifstream::failbit | ifstream::badbit); //Sets exceptions 
			if (readFile.is_open()) //Checks if the file is open
			{
				while (readFile.peek() != EOF) //checks if the next char is EOF if not loop continues
				{
					getline(readFile, str); //gets the line from the file and saves it to str
					databaseData.push_back(str); //pushes the str to the databaseData vector
				}
				readFile.close();//closes file
				return databaseData;//returns the databaseData vector
			}
			else
			{
				cout << "File could not open" << endl;
			}
		}
		catch (exception e) //catches exceptions 
		{
			string strRet = "";
			strRet = "Data retrival failed";
			cout << strRet << e.what() << endl;
			databaseData.clear(); //clears the databaseData
			return databaseData;
		}
		return databaseData;
				
	}

	//uses fileLogger to log data using a string
	void Model::deviceLog(string s) {
		fileLogger->log(s, "deviceLog.txt");
	}


