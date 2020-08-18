/*
*
* Team id : #1349
* Auther List : Amoghavarsha S.G
* Filename : main.ino
* Theme : Construct-O-Bot -- Specified to eYRC
* Functions : void go_till(int node), is_node(), void follow_line(), void edge_turn(bool DIC), void get_sensor_data(), void M1_encode(), void M2_encode(),
* 			  void cross_turn(bool DIR), void setup(), void loop();
* Global Variables : M1_Shaft_counter = 0, M2_Shaft_counter = 0, TURN_LEN, I_Lmin, I_Mmin, I_Rmin, I_Lmax, I_Mmax, I_Rmax, Lmin, Mmin, Rmin, Lmax, Mmax, Rmax,
* 					CUTOFF_L, CUTOFF_M, CUTOFF_R, left_sen_data, middle_sen_data, right_sen_data, data, sensor_data[3], FIRST_RUN, node_width, baseSpeed, K, 
* 					MODE, error, prevError, p, pd, d, lastTime, currentTime, cross_turn_flag, prev_left;
* 					
 */


#include "main.h"

/*
 * Configs
 */
 int house_state[5] = {0, 1, 1, 0, 0};
 int cmt_supply[10] = {E, P, C, G, P, S, B, G, S, B};


volatile int M1_Shaft_counter = 0, M2_Shaft_counter = 0;
int I_Lmin = 190, I_Mmin = 350, I_Rmin = 200, I_Lmax = 530, I_Mmax = 650, I_Rmax = 450;
int Lmin = I_Lmin, Mmin = I_Mmin, Rmin = I_Rmin, Lmax = I_Lmax, Mmax = I_Mmax, Rmax = I_Rmax; // these values gets calibrated as the bot moves around the arena
int CUTOFF_L = 400, CUTOFF_M = 450, CUTOFF_R = 400;
int left_sen_data, middle_sen_data, right_sen_data, data, sensor_data[3], NODE_WIDTH = 3, TURN_LEN = 100;
int baseSpeed = 85, K = 10, MODE = BLACK, error, prevError, p, pd; float d;
unsigned long int lastTime = 0, currentTime = 0;
bool cross_turn_flag = 0, prev_left = 0, zig_zag = 0;
int cm_p;
unsigned long int too_long = 0;

const int W_near_start[6] = {B, G, C, S, E, P};
const int W_near_H1[6]    = {B, C, E, G, S, P};
const int W_near_H2[6]    = {G, S, P, B, C, E};
const int W_near_H3[6]    = {E, C, B, P, S, G};
const int W_near_H4[6]    = {P, S, G, E, C, B};
const int W_near_H5[6]    = {E, P, C, S, B, G};
const int H_near_W1_2[6]  = {H1, H3, H2, H4, H5};
const int H_near_W3_4[6]  = {H2, H4, H1, H3, H5};
const int H_near_W5_6[6]  = {H3, H1, H4, H2, H5};
const int H_near_W7_8[6]  = {H4, H2, H3, H1, H5};
const int H_near_W9_10[6]  = {H3, H1, H4, H2, H5};
const int H_near_W11_12[6] = {H4, H2, H3, H1, H5};


/*
*
* Function Name: setup
* Input: void
* Output: void
* Logic: runs only once and sets the pins as input or output
* Example Call:
*/
void setup() {
	pinMode(ENA, OUTPUT);
	pinMode(ENB, OUTPUT);
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(IN3, OUTPUT);
	pinMode(IN4, OUTPUT);
	pinMode(BURZER, OUTPUT);
	digitalWrite(BURZER, HIGH);
	pinMode(LEFT_SENSOR, INPUT);
	pinMode(MIDDLE_SENSOR, INPUT);
	pinMode(RIGHT_SENSOR, INPUT);
	pinMode(M1_ENCODER_CLK, INPUT);
	pinMode(M1_ENCODER_DT, INPUT);
	pinMode(M2_ENCODER_CLK, INPUT);
	pinMode(M2_ENCODER_DT, INPUT);
	position_servos();
}

/*
*
* Function Name: loop
* Input: void
* Output: void
* Logic: contains the path boot needs to follow
* Example Call:
*/
void loop(){
	if(supply_all()){
	digitalWrite(BURZER, LOW);
	delay(5000);
	digitalWrite(BURZER, HIGH);
		while(1)
			haltBot();
	}
//	follow_line();
} 

int supply_all(){
	int house;
	cm_p = w_near_h();
	if(cm_p == -1)
		return 1;
	house = h_near_cm(cm_p);
	supply(cmt_supply[cm_p], house);
	cmt_supply[cm_p] = 0;
	return 0;
}

int cm_pth(int _cm){
	if(_cm == 0 || _cm == 1)
		return H1;
	if(_cm == 2 || _cm == 3)
		return H2;
	if(_cm == 4 || _cm == 5)
		return H3;
	if(_cm == 6 || _cm == 7)
		return H4;
	if(_cm == 8 || _cm == 9)
		return H5;
}

int h_near_cm(int cm_p1){
	int cm = cmt_supply[cm_p1];
	int cm_p2 = cm_p1;
	for(; cm_p2<= 8;){
		if(cmt_supply[++cm_p2] == cmt_supply[cm_p1])
			break;
	}
	if(cm_p2 == cm_p1 || (cm_pth(cm_p1) == cm_pth(cm_p2)))
		return cm_pth(cm_p1);
		
	for(int j = 0; j <= 5; j++){
		switch(cm){
			case B:
				if(H_near_W1_2[j] == cm_pth(cm_p1)){
					cm_p = cm_p1;
					return H_near_W1_2[j];
				}
				else if(H_near_W1_2[j] == cm_pth(cm_p2)){
					cm_p = cm_p2;
					return H_near_W1_2[j];
				}
				break;
			case G:
				if(H_near_W3_4[j] == cm_pth(cm_p1)){
					cm_p = cm_p1;
					return H_near_W3_4[j];
				}
				else if(H_near_W3_4[j] == cm_pth(cm_p2)){
					cm_p = cm_p2;
					return H_near_W3_4[j];
				}
				break;
			case C:
				if(H_near_W5_6[j] == cm_pth(cm_p1)){
					cm_p = cm_p1;
					return H_near_W5_6[j];
				}
				else if(H_near_W5_6[j] == cm_pth(cm_p2)){
					cm_p = cm_p2;
					return H_near_W5_6[j];
				}
				break;
			case S:
				if(H_near_W7_8[j] == cm_pth(cm_p1)){
					cm_p = cm_p1;
					return H_near_W7_8[j];
				}
				else if(H_near_W7_8[j] == cm_pth(cm_p2)){
					cm_p = cm_p2;
					return H_near_W7_8[j];
				}
				break;
			case E:
				if(H_near_W9_10[j] == cm_pth(cm_p1)){
					cm_p = cm_p1;
					return H_near_W9_10[j];
				}
				else if(H_near_W9_10[j] == cm_pth(cm_p2)){
					cm_p = cm_p2;
					return H_near_W9_10[j];
				}
				break;
			case P:
				if(H_near_W11_12[j] == cm_pth(cm_p1)){
					cm_p = cm_p1;
					return H_near_W11_12[j];
				}
				else if(H_near_W11_12[j] == cm_pth(cm_p2)){
					cm_p = cm_p2;
					return H_near_W11_12[j];
				}
				break;
		} 
	}	
}

int w_near_h(){
	for(int i = 0; i <= 5; i++){
		for(int j = 0; j <= 9; j++){
			if(cmt_supply[j] == 0)
				continue;
			switch(position_H){
				case START:
					if(W_near_start[i] == cmt_supply[j])
						return j;
					break;
				case H1:
					if(W_near_H1[i] == cmt_supply[j])
						return j;
					break;
				case H2:
					if(W_near_H2[i] == cmt_supply[j])
						return j;
					break;
				case H3:
					if(W_near_H3[i] == cmt_supply[j])
						return j;
					break;
				case H4:
					if(W_near_H4[i] == cmt_supply[j])
						return j;
					break;
				case H5:
					if(W_near_H5[i] == cmt_supply[j])
						return j;
					break;
			}
		}
	}
	return -1;
}


/*
*
* Function Name: go_till
* Input: int node
* Output: void
* Logic: Uses white line sensors to go forward by the number of nodes specified
* Example Call: go_till(1); goes forward by 1 node
*/
void go_till(int node){
	cross_turn_flag = 0;
	while(node){
		if(node == 1)
			baseSpeed -= K;
		while(!is_node())
			follow_line();
		node--;
	}
	baseSpeed += K;
}


/*
*
* Function Name: is_node
* Input: void
* Output: 1 or 0
* Logic: Uses white line sensors and encoders to detect the nodes and returns 1 if it is a node
* Example Call: is_node(); 
*
*/
int is_node(){
	get_sensor_data();
/*
	* There is would have been no reason to define 2 contitions for node since when node was detected 
	* 2 senser's detected black and other detected white and in between nodes there is no such condition
	* But at some places while printing the flex there was some ink spreed which is significant enough to cause false node detection so.. , whatever
	*/
	if(NODE_WIDTH == 2){
		if(!((left_sen_data == !MODE && middle_sen_data == MODE && right_sen_data == MODE) || (left_sen_data == MODE && middle_sen_data == MODE && right_sen_data == !MODE))){
			if(!(left_sen_data == MODE && middle_sen_data == MODE && right_sen_data == MODE))
				return 0;
		}
	}
	else{
		if(!(left_sen_data == MODE && middle_sen_data == MODE && right_sen_data == MODE))
			return 0;
	}
	if(M1_Shaft_counter == 0){
		attachInterrupt(digitalPinToInterrupt(M1_ENCODER_CLK), M1_encode, FALLING);
		return 1; 
	}
	return 0;
}


/*
*
* Function Name: follow_line()
* Input: void
* Output: void
* Logic: Uses white line sensors to follow black or white line
* Example Call: follow_line();
*
*/
void follow_line(){
	get_sensor_data();
	
	if(M1_Shaft_counter)
		forward(baseSpeed, baseSpeed);
	/*
		* Since the number of available sensors are less and the line width is less than the gap between any two white line sensors,
		* If we compare them digitally as just White or Black there will be only be 3 errors and we will not know the positon of bot when all sensors are on white
		* Taking decesion based on just 3 errors means bot will not be stable   
		* 
		* So we calculate the error by using weighted average method where each sensors are given certain weightage
		* (15 in this case for right and -15 for left sensor and 0 for middle sensor)
		* 
		* if the bot is at middle, value of left sensor and the right sensor will be same and the error will be 0 
		* (or in provided sensor if it is black line both left and right sensors will output 0 for white and the error will be zero)
		* 
		* if the left sensor is closer to line then error will be -ve and -15 will be the maximum error 
		* if the right sensor is closer to line then error will be +ve and 15 will be the maximum error
		* these errors change relative to position of bot and also gives the positon of bot when all sensors would have given White.
		* So this provides more information on the position of bot to control it 
	*/
//	if(!(zig_zag && left_sen_data == !MODE && middle_sen_data == !MODE && right_sen_data == !MODE))
	error = ( (15 * sensor_data[2]) - (15 * sensor_data[0]) ) / (sensor_data[0] + sensor_data[1] + sensor_data[2]);
	

	// When MODE is BLACK errors will be +ve when bot have to turn right 
	// But when MODE is WHITE, error will be -ve so we multiply by -1 so all other logic need not to be changed
	error = MODE ? error : (-1 * error);

	if(zig_zag){
		if(left_sen_data == !MODE && middle_sen_data == !MODE && right_sen_data == !MODE){
			too_long++;
			
			if(prevError < -3)
				error = - 8;
			else if(prevError > 3)
				error = 8;
			
			else{
				if(too_long > 300)
					error = (prevError * 3);
//					if(error == 0){
//						error = 10;
//					}
				}
			if(too_long > 1500){
					error *= -2;
			}
			if(too_long > 5000){
				digitalWrite(BURZER, LOW);
				haltBot();
				delay(5000);
				digitalWrite(BURZER, HIGH);
			}
		}
		else
			too_long = 0;
	}
	// controls bot by using pd algo
	currentTime = millis();
	if(!zig_zag)
		d = ((float)(error - prevError)) / ((float)(currentTime - lastTime)); // rate of change of error
	else
		d = 0;
	p = error;
	pd = (Kp * p) + (int)(Kd * d);
	pd = (pd > baseSpeed) ? baseSpeed : pd;
	forward(baseSpeed + pd, baseSpeed - pd);
	if(prevError != error){
		prevError = error;
		lastTime = currentTime;
	}
}

void sort(int ir_values[], int size) {
    for(int i=0; i<(size-1); i++) {
        bool done = true;
        for(int o=0; o<(size-(i+1)); o++) {
            if(ir_values[o] > ir_values[o+1]) {
                int t = ir_values[o];
                ir_values[o] = ir_values[o+1];
                ir_values[o+1] = t;
                done = false;
            }
        }
        if (done) // the array has been sorted
        	break;
    }
}

int distance_fmw(int ir_pin){
	int no_of_samples = 1;
	int ir_val[no_of_samples];
	int distance;
    for (int i=0; i<no_of_samples; i++){
        ir_val[i] = analogRead(ir_pin);
    }
    sort(ir_val, no_of_samples);
//    distance = 29.988 * pow(map(ir_val[no_of_samples / 2], 0, 1023, 0, 5000)/1000.0, -1.173);
	distance = 27.0/(map(ir_val[no_of_samples / 2], 0, 1023, 0, 5000)/1000.0); // take the middle value in sorted list (avg) and convert it to distance in cm
    return distance;
}

void follow_wall(){
	
	baseSpeed -=  25;
	int distance_left = 12;
	int distance_right = 12;
	int error;
	while(distance_left > 11 && distance_right > 11){
		distance_left = distance_fmw(SHARP_LEFT);
		distance_right = distance_fmw(SHARP_RIGHT);
		follow_line();
	}
	left_sen_data == !MODE; middle_sen_data == !MODE; right_sen_data == !MODE;
	M2_Shaft_counter = 1;
	TURN_LEN = 30;
	attachInterrupt(digitalPinToInterrupt(M2_ENCODER_CLK), M2_encode, FALLING);
	while(left_sen_data == !MODE && middle_sen_data == !MODE && right_sen_data == !MODE){
		distance_left = distance_fmw(SHARP_LEFT);
		distance_right = distance_fmw(SHARP_RIGHT);
		error = 10 * (distance_left - distance_right);
		forward(baseSpeed - error, baseSpeed + error);
		if(!M2_Shaft_counter)
			get_sensor_data;
	}
	baseSpeed +=  25;
	go_till(1);
}


/*
*
* Function Name: edge_turn
* Input: int DIR
* Output: void
* Logic: Uses white line sensors to turn specified direction at the edge of black line until line is detected
* Example Call: edge_turn(1); //turns right  
*
*/
void edge_turn(bool DIR){
	while(left_sen_data == MODE || middle_sen_data == MODE || right_sen_data == MODE){
		forward(baseSpeed, baseSpeed);
		get_sensor_data();
	}
	haltBot();
	while(1){
		motorB(!DIR, baseSpeed);
		motorA(DIR, baseSpeed);
		get_sensor_data();
		if(left_sen_data == !MODE && middle_sen_data == MODE && right_sen_data == !MODE)
			break;
	}
	haltBot();
	NODE_WIDTH = 3;
}


/*
*
* Function Name: get_sensor_data
* Input: void
* Output: void
* Logic: gets the white line sensor data and calibrates it self as it moves around the arena
* Example Call: get_sensor_data();
*
*/
void get_sensor_data(){
	data = analogRead(LEFT_SENSOR);
	Lmin = data < Lmin ? data : Lmin; // on the fly calibrattion :)
	Lmax = data > Lmax ? data : Lmax;
	sensor_data[0] = map(data, Lmin, Lmax, 0, 1000);
	if((Lmax - I_Lmax) > 35)
		CUTOFF_L = (Lmax + Lmin) / 1.7;
	left_sen_data = data > CUTOFF_L ? 1 : 0;

	data = analogRead(MIDDLE_SENSOR);
	Mmin = data < Mmin ? data : Mmin;
	Mmax = data > Mmax ? data : Mmax;
	sensor_data[1] = map(data, Mmin, Mmax, 0, 1000);
	if((Mmax - I_Mmax) > 35)
		CUTOFF_M = (Mmax + Mmin)/ 1.7;
	middle_sen_data = data > CUTOFF_M ? 1 : 0;

	data = analogRead(RIGHT_SENSOR);
	Rmin = data < Rmin ? data : Rmin;
	Rmax = data > Rmax ? data : Rmax;
	if((Rmax - I_Rmax) > 35)
		CUTOFF_R = (Rmax + Rmin) / 1.7;
	sensor_data[2] = map(data, Rmin, Rmax, 0, 1000);
	right_sen_data = data > CUTOFF_R ? 1 : 0;
	if(left_sen_data == 0 && middle_sen_data == 1 && right_sen_data == 0)
		MODE = BLACK;
	if(left_sen_data == 1 && middle_sen_data == 0 && right_sen_data == 1)
		MODE = WHITE;
}


/*
*
* Function Name: M1_encode
* Input: void
* Output: void
* Logic: increments the counter variable as the left motor turns its called automatically when inturupt is sent by left motor 
* Example Call:
*
*/
void M1_encode(){
	M1_Shaft_counter++;
	if(M1_Shaft_counter >= NODE_LEN){
		detachInterrupt(digitalPinToInterrupt(M1_ENCODER_CLK));
		M1_Shaft_counter = 0;
	}
}


/*
*
* Function Name: M2_encode
* Input: void
* Output: void
* Logic: increments the counter variable as the right motor turns its called automatically when inturupt is sent by right motor 
* Example Call:
*
*/
void M2_encode(){	
	M2_Shaft_counter++;
	if(M2_Shaft_counter >= TURN_LEN){
		detachInterrupt(digitalPinToInterrupt(M2_ENCODER_CLK));
		M2_Shaft_counter = 0;
	}
}




/*
*
* Function Name: cross_turn
* Input: bool DIR
* Output: void
* Logic: turns left or right before or after placeing the CM
* Example Call: cross_turn(1) // turns right untill line is detected
*
*/
void cross_turn(bool DIR){
	if(!cross_turn_flag){
		forward(baseSpeed, baseSpeed);
		delay(220);
	}
	else{
		if(prev_left){
			backward(baseSpeed, baseSpeed);
			delay(300);
		}
	}
	motorB(!DIR, baseSpeed);
	motorA(DIR, baseSpeed);
	delay(450);
	while(1){
		get_sensor_data();
		if( (left_sen_data == !MODE && middle_sen_data == MODE && right_sen_data == !MODE))
			break;
	}
	haltBot();
	delay(50);
	prev_left = !DIR;

	cross_turn_flag = 1;
	NODE_WIDTH = 3;
}
void H5_turn(bool DIR){
	motorB(!DIR, baseSpeed);
	motorA(DIR, baseSpeed);
	M2_Shaft_counter = 1;
	TURN_LEN = 80;
	attachInterrupt(digitalPinToInterrupt(M2_ENCODER_CLK), M2_encode, FALLING);
	while(M2_Shaft_counter);
	haltBot();
}
