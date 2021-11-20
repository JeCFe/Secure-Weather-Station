#include <string>
#include <iostream>
#include <vector>
#include<fstream>
#include <thread>         
#include <stdio.h>
#include<gsl.h>
#include "Controller.h"
#include "Choice.h"
#include "LogChoice.h"
#include "Authenticator.h" 
#include "FileLogger.h"
#include "ConsoleLogger.h"
#include "UnsignedOperations.h"
#include "SignedOperations.h"
using namespace std;


void Controller::run(void) {
	User user; //Current user
	vector<User> users; //Holds data from all known users
	Authenticator authenticate; //handles loggin in
	ProofofID proofOfID; //sys proofofID seperate from user

	initalise(authenticate, users);

	Choice choice = Choice::Login;
	while (choice != Choice::Quit) {	
		system("cls");
		choice = view.mainMenu(user);

		switch (choice) {

		case Choice::Information: //Model deatils	
			singleReading();
			view.printModelDetails(model); //displays the device details 
			break;

		case Choice::Login: 
			if (!logged) //If someone has already logged in
			{
				logged = login(user, authenticate, proofOfID, users); //Returns true if someone has logged in 
			}
			else
				view.message("User already logged in");
			break;

		case Choice::Read: 
			takeReadings(); //Takes reading
			break;

		case Choice::Logs:
			if (logged && (user.getProofOfID() == proofOfID.getproofID())) //If someone has logged in, and if the user proof of id and system proof of id are the same
			{
				viewLogs(); //Views log menu
			}
			else
			{
				view.message("You must be logged in to access logs");
			}

			break;
		case Choice::Device_Logs:
			if (logged && (user.getProofOfID() == proofOfID.getproofID())) //If someone has logged in, and if the user proof of id and system proof of id are the same
			{
				displayDeviceLogs();
			}
			else
			{
				view.message("You must be logged in to access logs");
			}
			break;

		case Choice::Sensor_Control:
			if (logged && user.getPrivilageLevel() == 1 && (user.getProofOfID() == proofOfID.getproofID()))//If someone has logged in, and if the user proof of id and system proof of id are the same
			{
				sensorControlMenu();//Loads sensor control menu
			}
			else view.message("You must be logged in as an admin to access sensors");
			break;

		case Choice::Configure:
			if (logged && user.getPrivilageLevel() == 1 && (user.getProofOfID() == proofOfID.getproofID())) //If someone has logged in, and if the user proof of id and system proof of id are the same
			{ 
				configureSensor(); //Configures sensor
			}
			else view.message("You have to be logged to configure sensor");
			break;

		case Choice::Add_User:
			if (logged && user.getPrivilageLevel() == 1 && (user.getProofOfID() == proofOfID.getproofID())) //If someone has logged in, and if the user proof of id and system proof of id are the same
			{
				addUser(users, authenticate); //Loads add newuser function
			}
			else{ view.message("You are not logged in, or you have the incorrect privilage level"); }
			break;


		case Choice::Remove_User:
			if (logged && user.getPrivilageLevel() == 1 && (user.getProofOfID() == proofOfID.getproofID())) //If someone has logged in, and if the user proof of id and system proof of id are the same
			{
				removeUser(users, authenticate, user); //Loads remove user function
			}
			else { view.message("You are not logged in, or you have the incorrect privilage level"); }
			break;
		case Choice::Log_Out:
			if (logged && (user.getProofOfID() == proofOfID.getproofID()))//If someone has logged in, and if the user proof of id and system proof of id are the same
			{
				user.setProofOfID("INVALID"); //removes users proof of if
				user.enterFirstName("");
				user.enterLastName("");
				logged = false; //sets logged to false
			}
			else
			{
				view.message("You must be logged in to log out");
			}
			break;
		case Choice::Quit:
			break;

		default:
			break;
		}
		system("pause");
	}
}

void Controller::singleReading()
{
	model.setTemperature((rand() % 40 + 1) - 10); //Generate random temp between -10 and 30
	model.setHumidity(rand() % 100); //generates random humidity between 0 - 99
	model.setWindSpeed(rand() % 70); //generates random windspeed between 0 - 69
	decideActuation(); //Decides whether the wind sensor gets actutated
	int const state = static_cast<int>(model.getOperatingState()); //Gets the current wind sensor operating state
	string strState = "";
	if (state == 0) { strState = "Spinning"; } //labeles the operating state
	else { strState = "Netural"; }

	//99 in the hour slot refers to a manual updating of the sensors 
	//Pass data to be saved to a file
	model.saveToFile(99, model.getTemperature(), model.getTempConvert(), model.getHumidity(), model.getWindSpeed(), model.getWindSpeedMPH(), strState);
}

//handles secure logging in
bool Controller::login(User& user, Authenticator& authenticate, ProofofID& proofOfID, vector<User>& users)
{
	string tmpProofIdHold = "";
	uint16_t userExisted = 1;
	while (userExisted)
	{
		user.enterId();//Takes in user ID
		proofOfID = authenticate.authenticateUser(user); //Defines the proofOfID value

		if (proofOfID.getproofID() != "")//ensure log in was accurate
		{
		for (uint16_t i = 0; i < users.size(); i++)
		{

				if (users.at(i).getId() == user.getId()) //if the user ID matches
				{
					tmpProofIdHold = user.getProofOfID(); //creates a temp proofOFID
					user = users.at(i); //Sets the loggin in user
					user.setProofOfID(tmpProofIdHold); //Set the user proof of id
					tmpProofIdHold = ""; //Formats the proof of id
				}
			}
		}
		if ((!proofOfID.getproofID().empty()) & (proofOfID.getproofID() == user.getProofOfID())) //IF the correct user has logged in
		{
			userExisted = 0;
			model.deviceLog(user.getPrivilageRole() + " has logged in"); //Logs who logged in
			return true;
		}
		else
		{
			cout << "You cannot access this content\n"; //if incorrect details entered
			return false;
		}
	}
	return false;
}

//Takes Readings and work out averages
void Controller::takeReadings(void) {
	vector<int> tempAverage;
	vector<uint16_t> humAverage;
	vector < uint16_t> windSpeedAverage;
	system("cls");
	srand(time(nullptr)); //Creates random seed for rand()
	view.understandingData(); //Displays data explaination
	cout << endl;
	view.displayHeader(); //speed gets too high fan turns off
	if (model.getOperatingState() == operatingState::NETURAL) //tests whether the wind sensor is spinning
	{
		view.message("Wind sensor is currently in netural, please actuate before readings can be taken");
	}
	else
	{
		for (int i = 1; i <= 24; i++) {
			if (model.getOperatingState() == operatingState::NETURAL) //If the wind sensor is netural
			{
				model.sensorActuate(); //Actutate wind sensor
			}
			model.setTemperature((rand() % 40 + 1) - 10); //Generate random temp between -10 and 30
			model.setHumidity(rand() % 100); //generates random humidity between 0 - 99
			model.setWindSpeed(rand() % 70); //generates random windspeed between 0 - 69

			decideActuation(); //Decides whether the wind sensor gets actutated

			int const state = static_cast<int>(model.getOperatingState()); //Gets the current wind sensor operating state
			string strState = "";
			if (state == 0) { strState = "Spinning"; } //labeles the operating state
			else { strState = "Netural"; }

			//Vectors used for calculating averages
			tempAverage.push_back(model.getTemperature()); //pushes back temp
			humAverage.push_back(model.getHumidity()); //pushes back humidity
			windSpeedAverage.push_back(model.getWindSpeed()); //pushes back wind speed

			//Displays sensor reading
			view.displayData(to_string(i), to_string(model.getTemperature()), to_string(model.getTempConvert()), 
				to_string(model.getHumidity()), to_string(model.getWindSpeed()), to_string(model.getWindSpeedMPH()), strState);

			//Pass data to be saved to a file
			model.saveToFile(i, model.getTemperature(), model.getTempConvert(), model.getHumidity(), model.getWindSpeed(), model.getWindSpeedMPH(), strState);

			//used to delay program 
			std::this_thread::sleep_for(std::chrono::milliseconds(model.getSampling()));
		}
		//Used to calculate readings 
		averageReadings(tempAverage, humAverage, windSpeedAverage);
	}
}

//Configure sampling 
void Controller::configureSensor(void){
	int samplingPeriod = model.getSampling(); //Gets current sampeling size
	view.message("\nCurrent sampling Period [ms]:");
	view.message(std::to_string(samplingPeriod));
	view.message("\nEnter new sampling Period [ms]:");
	cin >> samplingPeriod;
	model.setSampling(samplingPeriod); //Sets new sampling size
}

//Initialises all required components
void Controller::initalise(Authenticator& auth, vector<User>& users) {

	view.message("Initalising authorisation");
	view.message(auth.initalise()); //Sets ainfo data
	view.message("Initalising users");
	view.message(UsersInitalise(users)); //sets users
	view.message("Initalising Sensor");
	model.configureHumidity(); //configgures sensors
	model.configureTemp();
	model.configureWind();
	view.message("Sensors initalisied");

	system("pause");
}

//Adds users to a vector
string Controller::UsersInitalise(vector<User>& users)
{
	string str;
	try
	{
		//open and set exceptions for userData 
		ifstream readFile("userData.txt");

		readFile.exceptions(ifstream::failbit | ifstream::badbit);
		while (readFile.peek() != EOF) //Ensures not reading from EOF
		{
			//Gather user data and save to a user object
			User user;
			getline(readFile, str);
			user.enterId(str);
			getline(readFile, str);
			user.enterFirstName(str);
			getline(readFile, str);
			user.enterLastName(str);
			getline(readFile, str);
			user.setPrivilageLevel(stoi(str));
			users.push_back(user);

		}
		readFile.close(); //close file
		return to_string(users.size()) + " users added"; //return the amount of users added
	}
	catch (exception e) //Checks for exceptions thrown
	{
		if (strstr(e.what(), "eofbit") != nullptr)
		{
			return "EOF FILE ERROR";
		}
		else
		{
			return "File error occurred";
		}
	}
}

//determines if the wind sensor has to be actuated
void Controller::decideActuation() 
{
	uint16_t const windSpeed = model.getWindSpeed();
	if (windSpeed > model.getMaxSpeed()) //if wind speeds are too high for sensor to handle
	{
		model.sensorActuate(); //change sensor to netural
		model.setWindSpeed(0); // Set wind speed to 0 
	}
	if (windSpeed == 0) //if there is no wind speed
	{
		model.sensorActuate(); //actuate sensor
	}
}

//Adds user to software
void Controller::addUser(vector<User>& users, Authenticator& auth) {

	model.addUser(users, auth);	
}

//Allows to remove user from program
void Controller::removeUser(vector<User>& users, Authenticator& auth, User user) {
	uint16_t count = 0;
	uint16_t userChoice = 0;
	system("cls");
	cout << "You are currently logged in as: " << user.getFirstName() << " " << user.getLastName() << endl;
	cout << "Please select the following user to delete from the system ( please note, you are unable to remove yourself) : " << endl;
	for (uint16_t i = 0; i < users.size(); i++)
	{
		cout << "[" << i + 1 << "] " << users.at(i).getId() << " -> " << users.at(i).getLastName() << endl; //displays all users
		count = i + 1;
	}
	count++;
	cout << "[" << count << "] Return" << endl;
	bool endLoop = false;
	do
	{
		cout << "Please enter user to remove: ";
		cin >> userChoice;
		userChoice = userChoice - 1;

		if (userChoice == count - 1)
		{
			endLoop = true;
		}
		else if (userChoice+1 <=0 || userChoice+1 > users.size()) //ensure choice is in bounds
		{
			cout << "Input value out of bounds, try again" << endl;
		}
		else if (users.at(userChoice).getId() == user.getId()) //Checks that you havent selected yourself
		{
			cout << "You cannot remove yourself" << endl;
		}
		else
		{
			endLoop = true;
		}

	} while (!endLoop);
	if (userChoice == count - 1) 
	{
		cout << "Returning to menu" << endl << endl;
	}
	else
	{
		auth.removeUser(users.at(userChoice).getId()); //removes user and password from authernticator
		if (users.size() > 0) //ensure users is not empty
		{
			users.erase(users.begin() + userChoice); //removes user from users
		}
		model.writeUsersToFile(users); //override current users in a file
	}
}

//Seperates each word from the string by detecting blank spaces
void Controller::wordExtractor(string word) {

	vector<string> organisedData;
	const int strLength = word.size();
	string newWord = "";
	for (uint16_t j = 0; j < strLength; j++)
	{
		if (word.at(j) == ' ') //If space then save word 
		{
			organisedData.push_back(newWord);
			newWord = "";
		}
		else
		{
			newWord = newWord + word.at(j); //Add char to word
		}
	}
	organisedData.push_back(newWord);
	view.displayData(organisedData.at(0), organisedData.at(1), organisedData.at(2), organisedData.at(3), organisedData.at(4), organisedData.at(5), organisedData.at(6)); //Displays all the data onto the screen
	organisedData.clear(); //clears array

}

//function to view logs
void Controller::viewLogs() {

	vector<string> rawData = model.retriveDataFromDatabase("historicData.txt"); //Gets vector of data from historicData file
	bool userExisted = false;
	uint16_t dataSize = 0;
	while (!userExisted)
	{
		system("cls");
		LogChoice const userChoice = view.logMenu(); //Displays the log menu
		system("cls");
		switch (userChoice)
		{
		case LogChoice::Back:
			userExisted = true;
			break;
		case LogChoice::All:
			cout << "Historic Log Data: " << endl;
			view.understandLog();
			view.understandingData(); //Displays data explaination
			view.displayHeader(); //displays log header
			for (uint16_t i = 0; i < rawData.size(); i++)
			{
				string wordFromRawData = rawData.at(i); //gets the current string in the vector
				wordExtractor(wordFromRawData); //Function to seperate each word in the string
			}
			system("pause");
			break;
		case LogChoice::Most_Recent: //Similar process to above, yet limits to the first 24
			cout << "Historic Log Data: " << endl;
			view.understandLog();
			view.understandingData(); //Displays data explaination

			view.displayHeader();
			dataSize = gsl::narrow_cast<int>(rawData.size());
			for (uint16_t i = (dataSize - 1); i > rawData.size() - 25; i--)
			{
				string wordFromRawData = rawData.at(i);
				wordExtractor(wordFromRawData);
			}
			system("pause");
			break;
		case LogChoice::Least_Recent: //Similar to last yet limits to last 24
			cout << "Historic Log Data: " << endl;
			view.understandLog();
			view.understandingData(); //Displays data explaination
			view.displayHeader();
			for (uint16_t i = 0; i < 22; i++)
			{
				string wordFromRawData = rawData.at(i);
				wordExtractor(wordFromRawData);
			}
			system("pause");
			break;
		default:
			break;
		}
	}
}

//The next 4 fuctions handle the individual behaviours of the sensors, or control collectively
void Controller::thermometerControl() {
	SensorCommands choice;
	do
	{
		system("cls");
		view.message("Thermometer state (0 - ON | 1 - OFF): " + to_string(static_cast<int>(model.getTemperatureState())));
		choice = view.sensorCommands();
		switch (choice)
		{
		case SensorCommands::On:
			model.tempatureOn();
			break;
		case SensorCommands::Off:
			model.temperatureOff();
			break;
		case SensorCommands::Configure:
			model.configureTemp();
			break;
		case SensorCommands::Actuate:
			break;
		case SensorCommands::Back:
			break;
		default:
			break;
		}
	} while (choice != SensorCommands::Back);
}
void Controller::windControl() {
	SensorCommands choice;
	do
	{
		system("cls");
		view.message("Wind sensor state (0 - ON | 1 - OFF): " + to_string(static_cast<int>(model.getWindSensorState())));
		view.message("Wind sensor operating state (0 - Spinning | 1- Netural): " + to_string(static_cast<int>(model.getOperatingState())));
		choice = view.sensorCommands(1);
		switch (choice)
		{
		case SensorCommands::On:
			model.windSensorOn();
			break;
		case SensorCommands::Off:
			model.windSensorOff();
			break;
		case SensorCommands::Configure:
			model.configureWind();
			break;
		case SensorCommands::Actuate:
			model.sensorActuate();
			break;
		case SensorCommands::Back:
			break;
		default:
			break;
		}
	} while (choice != SensorCommands::Back);
}
void Controller::humidityControl() {
	SensorCommands choice;

	do
	{
		system("cls");

		view.message("Humidity state (0 - ON | 1 - OFF): " + to_string(static_cast<int>(model.getHumidityState())));
		choice = view.sensorCommands();
		switch (choice)
		{
		case SensorCommands::On:
			model.humidityOn();
			break;
		case SensorCommands::Off:
			model.humidityOff();
			break;
		case SensorCommands::Configure:
			model.configureHumidity();
			break;
		case SensorCommands::Actuate:
			break;
		case SensorCommands::Back:
			break;
		
		default:
			break;
		}
	} while (choice != SensorCommands::Back);

}
void Controller::allControl() {
	SensorCommands choice;

	do
	{
		system("cls");
		//gets all the relvelant states
		view.message("Humidity state (0 - ON | 1 - OFF): " + to_string(static_cast<int>(model.getHumidityState())));
		view.message("Thermometer state (0 - ON | 1 - OFF): " + to_string(static_cast<int>(model.getTemperatureState())));
		view.message("Wind sensor state (0 - ON | 1 - OFF): " + to_string(static_cast<int>(model.getWindSensorState())));
		view.message("Wind sensor operating state (0 - Spinning | 1- Netural): " + to_string(static_cast<int>(model.getOperatingState())));
		choice = view.sensorCommands(1); //deisplays sensor menu
		switch (choice)
		{
		case SensorCommands::On: //Turns all on
			model.humidityOn();
			model.tempatureOn();
			model.windSensorOn();
			break;
		case SensorCommands::Off: //Turns all off
			model.humidityOff();
			model.temperatureOff();
			model.windSensorOff();
			break;
		case SensorCommands::Configure: //Configures all sensors
			model.configureHumidity();
			model.configureTemp();
			model.configureWind();
			break;
		case SensorCommands::Actuate: //Actuates sensor
			model.sensorActuate();
			break;
		case SensorCommands::Back:
			break;

		default:
			break;
		}
	} while (choice != SensorCommands::Back);
}

//funstion to calcualte reading
void Controller::averageReadings(vector<int> temps, vector<uint16_t> hums, vector<uint16_t> winds) {
	UnsignedOperation UO; //Creates UnsignedOperations object
	SignedOperations SO; //Creates SigedOperation object
	int averageTemp = 0; 
	uint16_t averageHum = 0;
	uint16_t averageWinds = 0;
	for (size_t i = 0; i < temps.size(); i++) //Goes though data length
	{
		if (SO.Addition(averageTemp, temps.at(i))) //ensures overflow calcaultion would not occur
		{
			averageTemp = averageTemp + temps.at(i); //If it would not overflow, then the calcualtion can go ahead
		}
		if (UO.Addition(averageHum, hums.at(i))) //ensures that no wrapping would occur 
		{
			averageHum = averageHum + hums.at(i); //Do no wrapping then the calculation can go ahead
		}
		if (UO.Addition(averageWinds, winds.at(i)))
		{
			averageWinds = averageWinds + winds.at(i);
		}
	}
	if (SO.Division(averageTemp, 24)) //ensure that the value can be divided without overflowing 
	{
		averageTemp = averageTemp / 24; //does calculation 
	}
	averageHum = averageHum / 24; //as uint16_t face no issues with division no protection would be needed
	averageWinds = averageWinds / 24;
	view.displayAverage(averageTemp, averageHum, averageWinds); //displays averages
}

//Handles the displaying of log data onto the screen
void Controller::displayDeviceLogs() {
	system("cls");
	vector<string> data = model.retriveDataFromDatabase("deviceLog.txt"); //uses model to read data from deviceLogs
	view.message("--------------------------------------------------");
	view.message("Device Log");
	view.message("--------------------------------------------------");
	for (size_t i = 0; i < data.size(); i++)
	{
		view.message(data.at(i)); //Displays this data to screen
	}
	system("pause");
}

//Actuates wind sensor
void Controller::actuateWindSensor() {
	model.sensorActuate();//Actuates sensor
	if ((int)model.getOperatingState() == 0) //determines the operating state of the wind sensors
	{
		view.message("Wind sensor is now freely spinning");
	}
	else { view.message("Wind sensor is now in netural"); }
}

//displays sensor menu
void Controller::sensorControlMenu() {
	SensorChoice choice;
	do
	{
		system("cls");
		choice = view.sensorMenu(); //displays sensor info

		//Depending on the input value the following occurs. 
		switch (choice)
		{
		case SensorChoice::Back:
			break;
		case SensorChoice::Thermometer:
			thermometerControl();
			break;
		case SensorChoice::Humidity:
			humidityControl();
			break;
		case SensorChoice::Wind:
			windControl();
			break;
		case SensorChoice::All:
			allControl();
			break;
		default:
			break;
		}

	} while (choice != SensorChoice::Back);

}