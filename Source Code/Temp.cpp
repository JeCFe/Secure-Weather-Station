#include"temp.h"

//Returns temp
int Temp::read(void)const noexcept {
	return temp;
}
//Save reading data
void Temp::write(int t) {
	if (ONorOFF == State::OFF) //if thermometer is off
	{
		temp = 0; //sets temp to 0
		convert();//converts temp
	}
	else
	{
		temp = t; //saves temp
		convert();//converts temp
	}
}

//Configures thermometer
void Temp::configure() noexcept {
	temp = 0; //Sets temp to 0
	maxTemp = 100; //Sets max temp
	ONorOFF = State::ON; //turns thermometer on
}

//Converts from C to F
 void Temp::convert() {

	 bool overFlowError = false;
	 if (temp == 0) {
		 farTemp = 32;
	 }
	 else{
		 if (!SO.Mulplication(temp, 9)){ //test if multiplation can happen
			 overFlowError = true;
		 }
		 else{
			 farTemp = temp * 9;
			 if (!SO.Division(farTemp, 5))  {//tests if division can happen
				 overFlowError = true;
			 }
			 else {
				 farTemp = farTemp / 5;
				 if (!SO.Addition(farTemp, 32)) {//tests if addition can happen
					 overFlowError = true;
				 }
				 else { farTemp = farTemp + 32; }
			 }
			 if (overFlowError)
			 {
				 std::cout << "OVERFLOW ERROR OCCURRED";
			 }

		 }
	 }
}

 //returns temp in F
 int Temp::getFarTemp() noexcept {
	 return farTemp;
 }

 //return name
 string  Temp::getName() const {
	 return name;
 }

 //Turns on thermometer
 void Temp::on() noexcept {
	 ONorOFF = State::ON;
 } 

 //turns off thermometer
 void Temp::off() noexcept {
	 ONorOFF = State::OFF;
 }

 //returns if thermometer is on or off 
 State Temp::getState() noexcept {
	 return ONorOFF;
 }