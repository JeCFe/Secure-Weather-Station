#pragma once
#include "BaseLogger.h"
#include <iostream>
using namespace std;
class LoggerDecorator : public BaseLogger {
	unique_ptr<BaseLogger> contents; //Creates a unique pointer for base logger
	uint16_t formatType;
	void log(string s, string fileName = "") override; //Override BaseLogger log
public:
	LoggerDecorator(unique_ptr<BaseLogger> contents, uint16_t formatType) noexcept; //Constructer for logger decorator 
	virtual string formatMessage(string msg); //Formats message

	//Destructors 
	LoggerDecorator(const LoggerDecorator&) = delete;
	LoggerDecorator& operator=(const LoggerDecorator&) = delete;
	LoggerDecorator() = delete;
	bool operator==(const LoggerDecorator&) = delete;
};