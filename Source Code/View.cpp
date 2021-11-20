#include <string>
#include <iostream>
#include <iomanip>
#include "View.h"
#include "Choice.h" 
#include "LogChoice.h"
#include <gsl_util.h>

using namespace std;

//Displays details about the sensors, their names and their current relevant data
void View::printModelDetails(const Model& m) const {
	system("cls");
	cout << "**************************************" << endl;
	cout << "Device Name: " << m.getHumidityName() << endl;
	cout << "Temperature: " << m.getHumidity() << " %" << endl;
	cout << "**************************************" << endl;
	cout << "Device Name: " << m.getThermometerName() << endl;
	cout << "Temperature: " << m.getTemperature() << " C" << endl;
	cout << "**************************************" << endl;
	cout << "Device Name: " << m.getWindName() << endl;
	cout << "Temperature: " << m.getWindSpeed() << " KPH" << endl;
	cout << "Operating state: " << static_cast<int>(m.getOperatingState()) << " [SPINNING/NETURAL]" << endl;
	cout << "**************************************" << endl;
}

//displays header information when displaying data, and a consistant format
void View::displayHeader(void) {
	cout << " Time" << setw(10) <<"Temp" <<setw(10)<<"Temp"<<setw(10)<<"Humditiy"<< setw(12) << "Wind Speed" << setw(12) <<"Wind Speed" << setw(10) << "State"<< endl;
	cout << "[Hour]" << setw(8) << " [C]" << setw(10) << " [F]"<<setw(10) << " [%]" << setw(12) <<"[KPH]" << setw(12) << "[MPH]" << setw(13) << "[Spinning / Netural]"<<endl;
}

//Displays sensor readings and wind sensor state in a constistant format
void View::displayData(string hour, string temp, string tempConvert, string hum, string speed, string mphSpeed, string state) {
	ios init(nullptr);
	init.copyfmt(cout);
	cout << setfill('0') << setw(2) << hour; //Sets a fill to ensure a consistant width from a the left hand side
	cout.copyfmt(init);
	cout << setw(10) << temp << setw(10) << tempConvert << setw(10) << hum << setw(12) << speed << setw(12) << setprecision(2) <<mphSpeed << setw(10) << state << endl;
}

//Displays a message onto the console
void View::message(std::string s) {
	cout << s << endl;
}

//Displays sensor commands menu
SensorCommands View::sensorCommands(int specialCommands) { //Special commands to indicate if the menu is wind sensor or otherwise
	string input = "";
	string max_value = "";
	if (specialCommands == 1) { max_value = 5; } //If wind sensor is using this menu then there will be more available options
	else { max_value = 4; }
	do
	{
		cout << "Choose sensor command" << endl;
		cout << "---------------------" << endl;
		cout << static_cast<int>(SensorCommands::On) << ": On" << endl; //Takes data from ENUM CLASS 
		cout << static_cast<int>(SensorCommands::Off) << ": Off" << endl;
		cout << static_cast<int>(SensorCommands::Configure) << ": Configure" << endl;
		if (specialCommands == 1) { cout << static_cast<int>(SensorCommands::Actuate) << ": Actuate" << endl; } //if menu for wind sensor is being used
		cout << static_cast<int>(SensorCommands::Back) << ": back" << endl;
		cout << "Your choice: " << endl;
		cin >> input;
	} while (!intTest((input)) || ((input.size() >= 2)));//ensure input data is an int and between expected values

	return static_cast<SensorCommands>(stoi(input)); //Returns the ENUM Selected
}

//Displays sensor menu
SensorChoice View::sensorMenu() {
	string input = "";
	do
	{
		cout << "Choose which sensor you will to control" << endl;
		cout << "----------------------------------------" << endl;
		cout << static_cast<int>(SensorChoice::Thermometer) << ": Thermal sensor" << endl; //Takes menu choices from SensorChoice
		cout << static_cast<int>(SensorChoice::Humidity) << ": Humidity sensor" << endl;
		cout << static_cast<int>(SensorChoice::Wind) << ": Wind sensor" << endl;
		cout << static_cast<int>(SensorChoice::All) << ": All sensors" << endl;
		cout << static_cast<int>(SensorChoice::Back) << ": Back" << endl;
		cout << "Your choice: ";
		cin >> input;
	} while (!intTest((input)) || ((input.size() >= 2))); //ensures input data is an int and betweeen expected values

	return static_cast<SensorChoice>(stoi(input)); //Returns chosen SensorChoice
}

//Displays main menu
Choice View::mainMenu(User& user) {
	string input = "";
	do
	{
	system("cls");
	if (user.getFirstName() != "")
	{
		cout << "WELCOME! " << user.getFirstName() << " " << user.getLastName() << endl;
	}
	cout << "\nWelcome to the device simulation\n";
	cout << "Select from the following options\n";
	cout << "---------------------------------\n";
	cout << static_cast<int>(Choice::Information) << ": Display and update sensors\n";
	cout << static_cast<int>(Choice::Login) << ": Log in \n"; //take menu options from Choices ENUM
	cout << static_cast<int>(Choice::Read) << ": Read data\n";
	cout << static_cast<int>(Choice::Logs) << ": View Logs" << setw(40) << "[USERS / ADMIN]\n";
	cout << static_cast<int>(Choice::Device_Logs) << ": View device logs" << setw(33) << "[USERS / ADMIN]\n";
	cout << static_cast<int>(Choice::Sensor_Control) << ": Sensor Controls" << setw(26) << "[ADMIN]\n";
	cout << static_cast<int>(Choice::Configure) << ": Configure Sampling" << setw(23) << "[ADMIN]\n";
	cout << static_cast<int>(Choice::Add_User) << ": Add user" << setw(33) << "[ADMIN]\n";
	cout << static_cast<int>(Choice::Remove_User) << ": Remove user" << setw(30) << "[ADMIN]\n";
	cout << static_cast<int>(Choice::Log_Out) << ": Log out\n";
	cout << static_cast<int>(Choice::Quit) << ": Quit\n";
	cout << "Your choice :";
	cin >> input;
	} while (!intTest((input)) || ((input.size() >= 2) && input != "10"));//ugly user input protections, ensure is an int, that the string is not more than 2 chars, and checks if the int is 10. Not ideal way of testing
	return static_cast<Choice>(stoi(input)); //Returns Choice from Choice ENUM
}

//Display log menu
LogChoice View::logMenu() {
	 
	string input = ""; //Takes input as string to ensure no overflow, and can easily be converted to an int if required
	do
	{
		cout << "Select from the following menu options" << endl;
		cout << "-----------------------------------------" << endl;
		cout << static_cast<int>(LogChoice::All) << ": View all available logs" << endl; //Uses LogChoice ENUM to help displays menu
		cout << static_cast<int>(LogChoice::Most_Recent) << ": 24 of most recent" << endl;
		cout << static_cast<int>(LogChoice::Least_Recent) << ": 24 of least recent" << endl;
		cout << static_cast<int>(LogChoice::Back) << ": Return" << endl;
		cout << "Your Choice: " << endl;
		cin >> input;
	} while (!intTest((input)) || ((input.size() >= 2))); //ensure input data is an int and between expected values 

	return static_cast<LogChoice>(stoi(input)); //returns LogChoice 
}

//Displays data to better understand the readings presented on screen
void View::understandingData() {
	cout << "--------------------------------------------------------------------------------------------------------\n";
	cout << "Thermometer: \n";
	cout << "	If all data is [0] this indicates the sensor is currently switched off\n\n";
	cout << "Humidity Sensor: \n";
	cout << "	If all data is [0] this indicates the sensor is currently switched off\n\n";
	cout << "Wind Sensor: \n";
	cout << "	If all data is [0] this indicates that sensor is currently switched off\n";
	cout << "	If some data is switched off this means a storm surges as caused the turbine to stop spinning\n";
	cout << "	The sensor does this to protect the gears from damage\n\n";
	cout << "Wind Sensor Status:\n";
	cout << "	Netural: This means the turbine is not spinning, and no data is being recorded\n";
	cout << "	Spinning: This means the turbine is spinning, and taking in data\n\n";	
	cout << "--------------------------------------------------------------------------------------------------------\n";
}

void View::understandLog() {
	cout << "--------------------------------------------------------------------------------------------------------\n";
	cout << "Readings with hour slot 99 indicate manually updated sensors - \n";
	cout << "Readings with hour slots between 1 - 24 indicate the hours in which these readings were taken\n";
}

//Displays each sensor average data
void View::displayAverage(int avTemps, uint16_t avHums, uint16_t avWinds) {
	cout << "-------------------------------------------------" << endl;
	cout << "Average readings over a period of 24 hours: " << endl;
	cout << "Temperature: " << avTemps << " C" << endl;
	cout << "Humidity: " << avHums << " %" << endl;
	cout << "Wind speed: " << avWinds << " KPH" << endl;
	cout << "-------------------------------------------------" << endl;
}

bool View::intTest(string inpID)
{
	for (size_t i = 0; i < inpID.size(); i++)
	{
		if (inpID.at(i) >= '0' && inpID.at(i) <= '9') {}
		else //If any char is not an int then returns false
		{
			return false;
		}
	}
	return true; //IOf no chars are non int values returns true
}
