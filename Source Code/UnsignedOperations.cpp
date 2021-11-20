#include "UnsignedOperations.h"

//Determins if the unsigned additon can happen without wrapping
bool UnsignedOperation::Addition(uint16_t a, uint16_t b) noexcept {
	if (UINT_MAX - a < b)
	{
		return false;
	}
	else
	{
		return true;
	}
}
//Determins if the unsigned subtraction can happen without wrapping
bool UnsignedOperation::Substraction(uint16_t a, uint16_t b) noexcept {
	if (a < b)
	{
		return false;
	}
	else
	{
		return true;
	}

}
