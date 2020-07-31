/*
*
* Team id : #1349
* Auther List : Amoghavarsha S.G
* Filename : main.ino
* Theme : Construct-O-Bot -- Specified to eYRC
* Functions : void pick(bool DIR), void pick(int h_state), void position_servos(), void base_servo_write(int angle), void elbow_servo_write(int angle), 
* 			  void graber_servo_write(int angle), 
 */
 
void base_servo_write(int angle);
void elbow_servo_write(int angle);
void graber_servo_write(int angle);
void position_servos();
void pick(bool DIR);
void place(bool DIR);
void servo_debug();
