#pragma once
#include <string>
#include<vector>
#include "temp.h"
#include "Humidity.h"
#include "WindSensor.h"
#include<memory>
#include "FileLogger.h"
#include"Authenticator.h"
#include <fstream>
#include "User.h"
#include<iostream>
#include"LoggerDecorator.h"

using namespace std;
class Model {

		Temp temp;
		Humidity humidity;
		WindSensor windSensor;

		int samplingPeriod {500};
		const unique_ptr<BaseLogger> fileLogger; //Creates const unique pointer for a logger

		vector<int> historicData; //Every 4 is a new data set in order, temp, hum, windspeed, state
	public:
		Model(void);

		int getTemperature(void) const noexcept;
		int	getHumidity(void) const noexcept;
		float getWindSpeedMPH() noexcept;
		uint16_t getWindSpeed() const noexcept;
		int getTempConvert()noexcept;
		string getThermometerName() const;
		string getHumidityName() const;
		string getWindName() const;
		int getSampling(void) noexcept;
		uint16_t getMaxSpeed()noexcept;

		void setTemperature(const int temp) ;
		void setHumidity(const uint16_t h) ;
		void setWindSpeed(uint16_t speed) ;
		void setSampling(const int sampling) ;

		void configureTemp() ;
		void configureHumidity() ;
		void configureWind();


		State getTemperatureState() noexcept;
		State getHumidityState() noexcept;
		State getWindSensorState() noexcept;

		void tempatureOn() ;
		void windSensorOn() ;
		void humidityOn() ;

		void temperatureOff() ;
		void windSensorOff() ;
		void humidityOff() ;


		void saveToFile(int hour, int temp, int tempConvert, uint16_t hum, uint16_t speed, float mphSpeed, string state);
		void writeUsersToFile(vector<User>& users);
		vector<string> retriveDataFromDatabase(string fileName);
		void addUser(vector<User>& users, Authenticator& auth);
		void sensorActuate();
		operatingState getOperatingState() const noexcept;
		void deviceLog(string s);

		//Destructors 
		Model(const Model&) = delete;
		Model& operator=(const Model&) = delete;
		
};



