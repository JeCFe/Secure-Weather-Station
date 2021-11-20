#pragma once 
#include <iostream>
#include "SignedOperations.h"
#include <string>
#include "State.h"
using namespace std;

class Temp
{
	SignedOperations SO;
	int totalTemps = 0;
	int temp = 0;
	int maxTemp = 100;
	int farTemp = 32;
	string const name = "Thermometer";
	State ONorOFF = State::OFF; //Ensure sensor is switch off 
	void convert();

public:
	int read(void)const noexcept;
	void write(int t);
	void configure(void) noexcept;
	int getFarTemp() noexcept;
	string getName() const;
	void on() noexcept;
	void off() noexcept;
	State getState() noexcept;

	//Destructors 
	Temp() = default;
	Temp(const Temp&) = delete;                        
	Temp& operator=(const Temp&) = delete;
};
