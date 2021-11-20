#include"Humidity.h"

//Returns humidity
uint16_t Humidity::read(void)const noexcept {
	return humidity;
}

//Saves humidity reading
void Humidity::write(uint16_t h)noexcept {
	if (ONorOFF == State::OFF) //If sensor is turned off
	{
		humidity = 0; //sets humidity to 0
	}
	else
	{
		humidity = h; //sets humidity
	}
}

//configures sensor
void Humidity::configure() noexcept
{
	humidity = 0; //sets humidity to 0
	maxHumidity = 100; // max humidity to 100
	ONorOFF = State::ON;//turns on sensor
}

//turns on sensor
void Humidity::on() noexcept {
	ONorOFF = State::ON;
}

//turns off sensor
void Humidity::off() noexcept {
	ONorOFF = State::OFF;
}

//returns if sensor is on or off 
State Humidity::getState() noexcept {
	return ONorOFF;
}

//returns name
string Humidity::getName() const{
	return name;
}