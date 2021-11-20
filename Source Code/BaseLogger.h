#pragma once
#include <string>
using namespace std;


class BaseLogger
{
public:

	virtual void log(string msg, string fileName = "") = 0; //virtual logger
	virtual ~BaseLogger() = default; //default deconstructor
};