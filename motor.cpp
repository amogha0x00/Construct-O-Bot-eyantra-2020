/*
*
* Team id : #1349
* Auther List : Amoghavarsha S.G
* Filename : main.ino
* Theme : Construct-O-Bot -- Specified to eYRC
* Functions : void motorA(int dic, int speed),void motorB(int dic, int speed), void forward(int motorASpeed, int motorBSpeed), void backward(), void haltBot()
* 
 */


#include <Arduino.h>
#include "main.h"
/*
*
* Function Name: motorA
* Input: bool DIR, int speed
* Output: void
* Logic: takes direction and speed and turns the left motor
* Example Call: motorA(1, 255); // turns left motor forwards at max speed  
*/
void motorA(bool DIR, int speed){
	digitalWrite(IN1, !DIR);
	digitalWrite(IN2, DIR);
	analogWrite(ENA, speed);
}


/*
*
* Function Name: motorB
* Input: bool DIR, int speed
* Output: void
* Logic: takes direction and speed and turns the right motor
* Example Call: motorB(1, 255); // turns right motor forwards at max speed  
*/
void motorB(int dic, int speed){
	digitalWrite(IN3, !dic);
	digitalWrite(IN4, dic);
	analogWrite(ENB, speed);
}


/*
*
* Function Name: forward
* Input: int motorASpeed, int motorBSpeed
* Output: void
* Logic: takes speed of left and right motors and turns them forwards
* Example Call: forward(100, 255); // turns left motor at 100 and right motor forwards at max speed  
*/
void forward(int motorASpeed, int motorBSpeed){
	motorA(1, motorASpeed);
	motorB(1, motorBSpeed);
}


/*
* Function Name: backward
* Input: void
* Output: void
* Logic: turns left and right motors backwards at const speed
* Example Call: backward(100, 255);  
*/
void backward(int motorASpeed, int motorBSpeed){
	motorA(0, motorASpeed);
	motorB(0, motorBSpeed);
}


/*
*
* Function Name: haltBot
* Input: void
* Output: void
* Logic: stops both the motors
* Example haltBot();  
*/
void haltBot(){
	digitalWrite(IN1, 0);
	digitalWrite(IN2, 0);
	digitalWrite(IN3, 0);
	digitalWrite(IN4, 0);
}
