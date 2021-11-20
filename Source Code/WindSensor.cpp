#include "WindSensor.h"

//Configures wind sensor
void WindSensor::config() noexcept
{
	speed = 0;
	opState = operatingState::SPINNING; //changes operating state
	ONorOFF = State::ON; //Turns sensor on
}

//Used to take reading of wind sensor
void WindSensor::write(uint16_t windspeed) noexcept
{
	if (ONorOFF == State::OFF) //If the sensor is off then the speeds will be 0
	{
		speed = 0;
		mphSpeed = 0;
	}
	else //if there wind speed is higher than 0 
	{
		speed = windspeed;
		convertSpeed(); //Convert from KPH to MPH
	}
}

//Returns wind speed
uint16_t WindSensor::read()const  noexcept {
	return speed;
}


//Toggles operating state of wind sensor
void WindSensor::actuate() noexcept {
	if (opState == operatingState::NETURAL)
	{
		opState = operatingState::SPINNING;
	}
	else
	{
		opState = operatingState::NETURAL;
	}
}

//Return operating state
operatingState WindSensor::getOpState() const noexcept {
	return opState;
}

//Returns speed in MPH
float WindSensor::getmphSpeed() const noexcept {
	return mphSpeed;
}

//Convert from KPH to MPH
void WindSensor::convertSpeed() noexcept
{
	mphSpeed = 0;
	if (speed != 0)
	{
		mphSpeed = speed / 1.6f; //Converstion, no protections needed as division doesnt cause overflow in uint16
	}
}

//retruns max speed
uint16_t WindSensor::getMxTolSpeed() noexcept {
	return maxToleratbleSpeed;
}

//returns name
string WindSensor::getName() const  {
	return name;
}

//turns sensor on
void WindSensor::on() noexcept {
	ONorOFF = State::ON;
}
//turns sensor off
void WindSensor::off() noexcept {
	ONorOFF = State::OFF;
}
//returns if the sensor is on or off
State WindSensor::getState() noexcept {
	return ONorOFF;
}