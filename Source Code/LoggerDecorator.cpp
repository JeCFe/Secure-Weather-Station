#include"LoggerDecorator.h"

LoggerDecorator::LoggerDecorator(unique_ptr<BaseLogger> logger, uint16_t aformatType) noexcept
	:contents{ move(logger) }, formatType(aformatType){}

void LoggerDecorator::log(string msg, string fileName) {
	msg = formatMessage(msg); //Formats message
	contents->log(msg, fileName); //passes messages to relevent logger to be logged
}

string LoggerDecorator::formatMessage(string msg) { //sets formatting
	switch (formatType)
	{
	case 1:
		return msg; //No formatting
	case 2:
		return"<HTML><BODY> <b>" + msg + "</b></BODY></HTML>"; //HTML formatting
	default:
		return msg;
		break;
	}
}