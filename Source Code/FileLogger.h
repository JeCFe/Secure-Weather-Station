#pragma once
#include "BaseLogger.h"
#include <iostream>
class FileLogger : public BaseLogger
{
public:
    void log(string msg, string fileName) override; //overrides virtual base logger log
};