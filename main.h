/*
*
* Team id : #1349
* Auther List : Amoghavarsha S.G
* Filename : main.h
* Theme : Construct-O-Bot -- Specified to eYRC
* Functions : void go_till(int node), is_node(), void follow_line(), void edge_turn(bool DIC), void get_sensor_data(), void M1_encode(), void M2_encode(),
* 			  void cross_turn(bool DIR), void setup(), void loop();
* Global Variables : M1_Shaft_counter = 0, M2_Shaft_counter = 0, TURN_LEN, I_Lmin, I_Mmin, I_Rmin, I_Lmax, I_Mmax, I_Rmax, Lmin, Mmin, Rmin, Lmax, Mmax, Rmax,
* 					CUTOFF_L, CUTOFF_M, CUTOFF_R, left_sen_data, middle_sen_data, right_sen_data, data, sensor_data[3], FIRST_RUN, node_width, baseSpeed, K, 
* 					MODE, error, prevError, p, pd, d, lastTime, currentTime, cross_turn_flag, prev_left;
* 					
 */
 
#include "pick_place.h"
#include "motor.h"
#include "paths.h"
#pragma GCC optimize ("-Os")

extern int house_state[5];
extern int position_H , position_W, bot_direction;
extern bool zig_zag;
extern int TURN_LEN, baseSpeed, MODE;
extern volatile int M2_Shaft_counter;

#define ENA 6     // Pin H3
#define IN1 22    // Pin A0
#define IN2 23    // Pin A1
#define ENB 7     // Pin H4
#define IN3 24    // Pin A2
#define IN4 25    // Pin A3
#define BASE 44	  // Pin L5	   ;Since Servo library uses TIMER5 and pins L3, L4, L5(44 - 46) also use TIMER5 to generate PWM,
#define ELBOW 45  // Pin L4    ;motors or other task requiring PWM cannot be connected to these pins so Servo's are connected to these pins
#define GRABER 46 // Pin L3 
#define BURZER 15 //Pin J0
#define M1_ENCODER_DT 19  //INT2, Pin D2
#define M1_ENCODER_CLK 18 // INT3, Pin D3
#define M2_ENCODER_DT 2   //INT4, Pin E4
#define M2_ENCODER_CLK 3  //INT5, Pin E5
#define LEFT_SENSOR A1    // Pin F1 (Analog pin)
#define MIDDLE_SENSOR A2  // Pin F2 (Analog pin)
#define RIGHT_SENSOR A3   // Pin F3 (Analog pin)
#define SHARP_LEFT A8	  // Pin K0 (Analog pin)
#define SHARP_RIGHT A9	  // Pin K1 (Analog pin)
#define BLACK 1
#define WHITE 0
#define DEBUG 0
#define UP 1
#define DOWN 0
#define Kp 3
#define Kd 1.5
#define NODE_LEN 200
#define R 1
#define L 0
#define B 1		// Brick
#define G 2		// Gravel
#define C 3		// Cement
#define S 4		// Sand
#define E 5		// Electrial fittings
#define P 6		// Paint
#define START -1
#define H1 0	// House 1
#define H2 1	// House 2
#define H3 2	// House 3
#define H4 3	// House 4
#define H5 4	// House 5

void go_till(int node);
void get_sensor_data();
void edge_turn(bool DIR);
void cross_turn(bool DIR);
void H5_turn(bool DIR);
void M1_encode();
void M2_encode();
void follow_line();
