#pragma once
#include "BaseLogger.h"

class ConsoleLogger : public BaseLogger
{
public:
	void log(string msg, string fileName) override;//override base logger log


};