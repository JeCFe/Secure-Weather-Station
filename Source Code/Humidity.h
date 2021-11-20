
#pragma once
#include<inttypes.h>
#include "State.h"
#include <string>
using namespace std;
class Humidity
{
	uint16_t humidity{ 80 };
	uint16_t maxHumidity{ 100 };
	State ONorOFF = State::OFF;
	string const name = "Hunidity Sensor";
public:
	Humidity() = default;
	uint16_t read(void)const noexcept;
	void write(uint16_t t) noexcept;
	void configure(void) noexcept;
	string getName() const;

	void on() noexcept;
	void off() noexcept;


	State getState() noexcept;
	Humidity(const Humidity&) = delete;
	Humidity& operator=(const Humidity&) = delete;
};