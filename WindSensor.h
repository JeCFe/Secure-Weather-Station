#pragma once
#include <string>
#include "UnsignedOperations.h"
#include "State.h"
using namespace std;
enum class operatingState{SPINNING, NETURAL};

class WindSensor
{
	uint16_t speed = 0;
	float mphSpeed = 0;
	uint16_t maxToleratbleSpeed = 60;
	operatingState opState = operatingState::NETURAL; //Sets operating state to NETURAL on creation
	State ONorOFF = State::OFF; //Ensure sensor is switch off on creation
	string const name = "Wind Sensor";
	void convertSpeed() noexcept;

public:
	void actuate() noexcept;
	operatingState getOpState() const noexcept;
	void config() noexcept;
	void write(uint16_t windSpeed) noexcept;
	uint16_t read() const noexcept;
	float getmphSpeed() const noexcept;
	uint16_t getMxTolSpeed() noexcept;
	string getName() const ;
	void on() noexcept;
	void off() noexcept;
	State getState() noexcept;

	//Destructors
	WindSensor() = default;
	WindSensor(const WindSensor&) = delete;                        //comapiler flag
	WindSensor& operator=(const WindSensor&) = delete;
};