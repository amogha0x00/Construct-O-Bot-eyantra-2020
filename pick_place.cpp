/*
*
* Team id : #1349
* Auther List : Amoghavarsha S.G
* Filename : main.ino
* Theme : Construct-O-Bot -- Specified to eYRC
* Functions : void pick(bool DIR), void pick(int h_state), void position_servos(), void base_servo_write(int angle), void elbow_servo_write(int angle), 
* 			  void graber_servo_write(int angle), 
* Global Variables : FIRST_RUN
 */

#include <Arduino.h>
#include "Servo.h"
#include "main.h"

Servo base_servo;
Servo elbow_servo;
Servo graber_servo;

int FIRST_RUN = 1;
extern int house_state[5];
/*
*
* Function Name: base_servo_write
* Input: int angle
* Output: void
* Logic: turns base servo at specified angle slowly
* Example base_servo_write(90);
*/
void base_servo_write(int angle){
	int current_angle = base_servo.read();
	if(current_angle == angle)
		return;
	if(current_angle > angle){
		for( ; current_angle > angle ; current_angle--){
			base_servo.write(current_angle);
			delay(20);
		}
	}
	else{
		for( ; current_angle < angle ; current_angle++){
			base_servo.write(current_angle);
			delay(20);
		}
	}
}

/*
*
* Function Name: elbow_servo_write
* Input: int angle
* Output: void
* Logic: turns elbow servo at specified angle slowly
* Example elbow_servo_write(0);
*/
void elbow_servo_write(int angle){
	int current_angle = elbow_servo.read();
	if(current_angle == angle)
		return;
	if(current_angle > angle){
		for( ; current_angle > angle ; current_angle--){
			elbow_servo.write(current_angle);
			delay(20);
		}
	}
	else{
		for( ; current_angle < angle ; current_angle++){
			elbow_servo.write(current_angle);
			delay(20);
		}
	}
}


/*
*
* Function Name: graber_servo_write
* Input: int angle
* Output: void
* Logic: turns graber servo at specified angle slowly
* Example graber_servo_write(10);
*/
void graber_servo_write(int angle){
	graber_servo.write(angle);
	delay(500);
}


/*
*
* Function Name: position_servos
* Input: void
* Output: void
* Logic: positions the servo to correct position 
* Example Call: position_servos();
*
*/
void position_servos(){
	if(FIRST_RUN){
		elbow_servo.attach(ELBOW);
	   	elbow_servo.write(0);
		delay(500);
		base_servo.attach(BASE);
		base_servo.write(72);
    	delay(500);
    	base_servo.detach();
		FIRST_RUN = 0;
	}
	else{
   		elbow_servo_write(0);
		delay(100);
		base_servo.attach(BASE);
		base_servo_write(72);
    	delay(100);
    	base_servo.detach();
	}
}


/*
*
* Function Name: pick
* Input: bool DIR
* Output: void
* Logic: picks the CM from left or right
* Example Call: pick(1) // picks up the CM from right
*
*/
void pick(bool DIR){
	int base_angle = DIR ? 2 : 178;
	haltBot();
	delay(1000);
	base_servo.attach(BASE);
	base_servo_write(base_angle);
    base_servo.detach();
	graber_servo.attach(GRABER);
	graber_servo_write(0);
    elbow_servo_write(76);
	graber_servo_write(100);
	position_servos();
}


/*
*
* Function Name: place
* Input: int h_state
* Output: void
* Logic: places the CM in low raise or high raise house
* Example Call: place(1) // places the CM in high raise house
*
*/
void place(bool DIR){
	if(position_H == H5)
		H5_turn(!DIR);
	else
		cross_turn(!DIR);
	forward(baseSpeed, baseSpeed);
	delay(50);
	haltBot();
	int h_state = house_state[position_H];
	h_state = h_state ? 40 : 55;
	delay(1000);
	base_servo.attach(BASE);

	if(DIR)
		base_servo_write(105);
//	else
//		base_servo_write(105);

    base_servo.detach();
    elbow_servo_write(h_state);
	graber_servo_write(10);
	graber_servo.detach();
	position_servos();
	backward(baseSpeed, baseSpeed);
	delay(50);
	haltBot();
}

//void servo_debug(){
//	String str_angle;int angle;char c;
//	base_servo.attach(BASE);
//	while (Serial.available()) {
//    	c = Serial.read();
//    	str_angle += c;
//    	delay(2);
//  }
//
//	if (str_angle.length() >0) {
//		Serial.println(str_angle);
//		angle = str_angle.toInt();
//		Serial.print("writing Angle: ");
//		Serial.println(angle);
//		base_servo.write(angle);
//	}
//	str_angle="";
//}
