/*
*
* Team id : #1349
* Auther List : Amoghavarsha S.G
* Filename : main.ino
* Theme : Construct-O-Bot -- Specified to eYRC
* Functions : W1_W2_path(void), W3_W4_path(void),  W5_W6_path(void), W7_W8_path(void),W9_W10_path(void), W11_W12_path(void), H1_path(void), 
* 			  H2_path(void), H3_path(void), H4_path(void), H5_path(void), supply(int cm, int home).
* Global variables : flag_B, flag_G, flag_C,flag_zig_zag, flag_S, flag_E, flag_P
 */


#include <Arduino.h>
#include "main.h"

int flag_B = 0, flag_G = 0, flag_C = 0, flag_S = 0, flag_E = 0, flag_P = 0;
int position_H = START, position_W = 0, bot_direction = DOWN;
extern int NODE_WIDTH;

void supply(int cm, int home) {
	switch (cm)
	{
	case B:
		position_W = B;
		W1_W2_path();
		flag_B++;
		break;
	case G:
		position_W = G;
		W3_W4_path();
		flag_G++;
		break;
	case C:
		position_W = C;
		W5_W6_path();
		flag_C++;
		break;
	case S:
		position_W = S;
		W7_W8_path();
		flag_S++;
		break;
	case E:
		position_W = E;
		W9_W10_path();
		flag_E++;
		break;
	case P:
		position_W = P;
		W11_W12_path();
		flag_P++;
		break;
	default:
		break;
	}
	
	switch (home)
	{
	case H1:
		position_H = H1;
		H1_path();
		break;
	case H2:
		position_H = H2;
		H2_path();
		break;
	case H3:
		position_H = H3;
		H3_path();
		break;
	case H4:
		position_H = H4;
		H4_path();
		break;
	case H5:
		position_H = H5;
		H5_path();
		break;
	default:
		break;
	}

}

/*
*
* Function Name: W1_W2_path
* Input: void
* Output: void
* Logic: This function is used to store the path of warehouse 1 and 2 from any house
* Example Call: W1_W2_path();
*/
void W1_W2_path() {
	if (position_H == START) {
		go_till(1);
		edge_turn(R);
		NODE_WIDTH = 2;
		go_till(1);
		edge_turn(R);
		go_till(1);
		pick(L);
		bot_direction = UP;
	}
	if (position_H == H1) {
		cross_turn(R);
		go_till(1);
		if (!flag_B)
			pick(R);
		else
			pick(L);
		bot_direction = DOWN;
	}
	else if (position_H == H2) {
		cross_turn(L);
		NODE_WIDTH = 2;
		go_till(2);
		edge_turn(R);
		NODE_WIDTH = 2;
		go_till(2);
		edge_turn(R);
		go_till(1);
		if (!flag_B)
			pick(L);
		else
			pick(R);
		bot_direction = UP;
	}
	else if (position_H == H3) {
		cross_turn(R);
		go_till(3);
		if (!flag_B)
			pick(R);
		else
			pick(L);
		bot_direction = DOWN;
	}
	else if (position_H == H4) {
		zig_zag = 1;
		go_till(1);
		zig_zag = 0;
		cross_turn(L);
		go_till(3);
		if (!flag_B)
			pick(R);
		else
			pick(L);
		bot_direction = DOWN;
	}
	else if (position_H == H5) {
		backward(baseSpeed, baseSpeed);
		delay(50);
		edge_turn(L);
		NODE_WIDTH = 2;
		M2_Shaft_counter = 1;
		TURN_LEN = 1000;
		attachInterrupt(digitalPinToInterrupt(M2_ENCODER_CLK), M2_encode, FALLING);
		while(M2_Shaft_counter)
			follow_line();
		go_till(1);
		edge_turn(L);
		go_till(5);
		if (!flag_C)
			pick(R);
		else
			pick(L);
		bot_direction = DOWN;
	}
}

/*
*
* Function Name: W5_W6_path
* Input: void
* Output: void
* Logic: This function is used to store the path of warehouse 5 and 6 from any house
* Example Call: W5_W6_path();
*/
void W5_W6_path() {
	if (position_H == START) {
		go_till(1);
		edge_turn(R);
		NODE_WIDTH = 2;
		go_till(1);
		edge_turn(R);
		go_till(3);
		pick(L);
		bot_direction = UP;
	}
	else if (position_H == H1) {
		cross_turn(L);
		go_till(1);
		if (!flag_C)
			pick(L);
		else
			pick(R);
		bot_direction = UP;
	}
	else if (position_H == H2) {
		cross_turn(L);
		go_till(2);
		edge_turn(R);
		go_till(2);
		edge_turn(R);
		go_till(3);
		if (!flag_C)
			pick(L);
		else
			pick(R);
		bot_direction = UP;
	}
	else if (position_H == H3) {
		cross_turn(R);
		go_till(1);
		if (!flag_C)
			pick(R);
		else
			pick(L);
		bot_direction = DOWN;
	}
	else if (position_H == H4) {
		zig_zag = 1;
		go_till(1);
		zig_zag = 0;
		cross_turn(L);
		go_till(1);
		if (!flag_C)
			pick(L);
		else
			pick(R);
		bot_direction = DOWN;
	}
	else if (position_H == H5) {
		backward(baseSpeed, baseSpeed);
		delay(50);
		edge_turn(L);
		NODE_WIDTH = 2;
		M2_Shaft_counter = 1;
		TURN_LEN = 1000;
		attachInterrupt(digitalPinToInterrupt(M2_ENCODER_CLK), M2_encode, FALLING);
		while(M2_Shaft_counter)
			follow_line();
		go_till(1);
		edge_turn(R);
		go_till(3);
		if (!flag_C)
			pick(R);
		else
			pick(L);
		bot_direction = DOWN;
	}
}

/*
*
* Function Name: W9_W10_path
* Input: void
* Output: void
* Logic: This function is used to store the path of warehouse 9 and 10 from any house
* Example Call: W9_W10_path();
*/
void W9_W10_path() {
	if (position_H == START) {
		go_till(1);
		edge_turn(R);
		NODE_WIDTH = 2;
		go_till(1);
		edge_turn(R);
		go_till(5);
		pick(L);
		bot_direction = UP;
	}
	else if (position_H == H1) {
		cross_turn(L);
		go_till(3);
		if (!flag_E)
			pick(L);
		else
			pick(R);
		bot_direction = UP;
	}
	else if (position_H == H2) {
		cross_turn(R);
		go_till(2);
		cross_turn(L);
		zig_zag = 1;
		go_till(1);
		zig_zag = 0;
		cross_turn(R);
		go_till(1);
		if (!flag_E)
			pick(L);
		else
			pick(R);
		bot_direction = UP;	
	}
	else if (position_H == H3) {
		cross_turn(L);
		go_till(1);
		if (!flag_E)
			pick(L);
		else
			pick(R);
		bot_direction = UP;
	}
	else if (position_H == H4) {
		go_till(1);
		zig_zag = 1;
		go_till(1);
		zig_zag = 0;
		cross_turn(R);
		go_till(1);
		if (!flag_E)
			pick(L);
		else
			pick(R);
		bot_direction = UP;
	}
	else if (position_H == H5) {
		backward(baseSpeed, baseSpeed);
		delay(50);
		edge_turn(L);
		NODE_WIDTH = 2;
		M2_Shaft_counter = 1;
		TURN_LEN = 1000;
		attachInterrupt(digitalPinToInterrupt(M2_ENCODER_CLK), M2_encode, FALLING);
		while(M2_Shaft_counter)
			follow_line();
		go_till(1);
		edge_turn(R);
		go_till(1);
		if (!flag_E)
			pick(L);
		else
			pick(R);
		bot_direction = DOWN;
	}
}

/*
*
* Function Name: W3_W4_path
* Input: void
* Output: void
* Logic: This function is used to store the path of warehouse 3 and 4 from any house
* Example Call: W7_W8_path();
*/
void W3_W4_path() {
	if (position_H == START) {
		go_till(1);
		edge_turn(L);
		NODE_WIDTH = 2;
		go_till(1);
		edge_turn(L);
		go_till(1);
		pick(R);
		bot_direction = UP;
	}
	else if (position_H == H1) {
		cross_turn(R);
		NODE_WIDTH = 2;
		go_till(2);
		edge_turn(L);
		NODE_WIDTH = 2;
		go_till(2);
		edge_turn(L);
		go_till(1);
		if (!flag_G)
			pick(R);
		else
			pick(L);
		bot_direction = UP;
	}
	else if (position_H == H2) {
		cross_turn(L);
		go_till(1);
		if (!flag_G)
			pick(L);
		else
			pick(R);
		bot_direction = DOWN;
}
	else if (position_H == H3) {
		zig_zag = 1;
		go_till(1);
		zig_zag = 0;
		cross_turn(R);
		go_till(3);
		if (!flag_G)
			pick(L);
		else
			pick(L);
		bot_direction = DOWN;
	}
	else if (position_H == H4) {
		cross_turn(L);
		go_till(3);
		if (!flag_G)
			pick(L);
		else
			pick(R);
		bot_direction = DOWN;
	}
	else if (position_H == H5) {
		backward(baseSpeed, baseSpeed);
		delay(50);
		edge_turn(R);
		NODE_WIDTH = 2;
		M2_Shaft_counter = 1;
		TURN_LEN = 1000;
		attachInterrupt(digitalPinToInterrupt(M2_ENCODER_CLK), M2_encode, FALLING);
		while(M2_Shaft_counter)
			follow_line();
		go_till(1);
		edge_turn(R);
		go_till(5);
		if (!flag_G)
			pick(L);
		else
			pick(R);
		bot_direction = DOWN;
	}
}

/*
*
* Function Name: W7_W8_path
* Input: void
* Output: void
* Logic: This function is used to store the path of warehouse 7 and 8 from any house
* Example Call: W9_W10_path();
*/
void W7_W8_path() {
	if (position_H == START) {
		go_till(1);
		edge_turn(L);
		NODE_WIDTH = 2;
		go_till(1);
		edge_turn(L);
		go_till(3);
		pick(R);
		bot_direction = UP;
	}
	else if (position_H == H1) {
		cross_turn(L);
		go_till(2);
		cross_turn(R);
		zig_zag = 1;
		go_till(1);
		zig_zag = 0;
		cross_turn(R);
		go_till(1);
		if (!flag_S)
			pick(L);
		else
			pick(R);
		bot_direction = DOWN;
	}
	else if (position_H == H2) {
		cross_turn(R);
		go_till(1);
		if (!flag_S)
			pick(R);
		else
			pick(L);
		bot_direction = UP;
	}
	else if (position_H == H3) {
		zig_zag = 1;
		go_till(1);
		zig_zag = 0;
		cross_turn(R);
		go_till(1);
		if (!flag_S)
			pick(L);
		else
			pick(R);
		bot_direction = DOWN;
	}
	else if (position_H == H4) {
		cross_turn(L);
		go_till(1);
		if (!flag_S)
			pick(L);
		else
			pick(R);
		bot_direction = DOWN;
	}
	else if (position_H == H5) {
		backward(baseSpeed, baseSpeed);
		delay(50);
		edge_turn(R);
		NODE_WIDTH = 2;
		M2_Shaft_counter = 1;
		TURN_LEN = 1000;
		attachInterrupt(digitalPinToInterrupt(M2_ENCODER_CLK), M2_encode, FALLING);
		while(M2_Shaft_counter)
			follow_line();
		go_till(1);
		edge_turn(R);
		go_till(3);
		if (!flag_S)
			pick(L);
		else
			pick(R);
		bot_direction = DOWN;
	}
}

/*
*
* Function Name: W11_W12_path
* Input: void
* Output: void
* Logic: This function is used to store the path of warehouse 11 and 12 from any house
* Example Call: W11_W12_path();
*/
void W11_W12_path() {
	if (position_H == START) {
		go_till(1);
		edge_turn(L);
		NODE_WIDTH = 2;
		go_till(1);
		edge_turn(L);
		go_till(5);
		pick(L);
		bot_direction = UP;
	}
	else if (position_H == H1) {
		cross_turn(L);
		go_till(2);
		cross_turn(R);
		zig_zag = 1;
		go_till(1);
		zig_zag = 0;
		cross_turn(L);
		go_till(1);
		if (!flag_P)
			pick(L);
		else
			pick(R);
		bot_direction = UP;
	}
	else if (position_H == H2) {
		cross_turn(R);
		go_till(3);
		if (!flag_P)
			pick(L);
		else
			pick(R);
		bot_direction = UP;
	}
	else if (position_H == H3) {
		zig_zag = 1;
		go_till(1);
		zig_zag = 0;
		cross_turn(L);
		go_till(1);
		if (!flag_P)
			pick(L);
		else
			pick(R);
		bot_direction = UP;
	}
	else if (position_H == H4) {
		cross_turn(R);
		go_till(1);
		if (!flag_P)
			pick(L);
		else
			pick(R);
		bot_direction = UP;
	}
	else if (position_H == H5) {
		backward(baseSpeed, baseSpeed);
		delay(50);
		edge_turn(R);
		NODE_WIDTH = 2;
		M2_Shaft_counter = 1;
		TURN_LEN = 1500;
		attachInterrupt(digitalPinToInterrupt(M2_ENCODER_CLK), M2_encode, FALLING);
		while(M2_Shaft_counter)
			follow_line();
		go_till(1);
		edge_turn(R);
		go_till(1);
		if (!flag_P)
			pick(L);
		else
			pick(R);
		bot_direction = DOWN;
	}
}

/*
*
* Function Name: H1_path
* Input: void
* Output: void
* Logic: This function is used to store the path of house 1 from any warehouse
* Example Call: H1_path();
*/
void H1_path() {
	if(position_W == B){
		if (bot_direction == DOWN) {
			cross_turn(R);
			cross_turn(R);
		}
		go_till(1);
		place(L);
	}
	else if(position_W == C){
		if (bot_direction == UP) {
			cross_turn(R);
			cross_turn(R);
		}
		go_till(1);
		place(R);
	}
	else if(position_W == E){
		if (bot_direction == UP) {
			cross_turn(R);
			cross_turn(R);
		}
		go_till(3);
		place(R);
	}
	else if(position_W == G){
		if (bot_direction == UP) {
			cross_turn(R);
			cross_turn(R);
		}
		NODE_WIDTH = 2;
		go_till(1);
		edge_turn(R);
		NODE_WIDTH = 2;
		go_till(2);
		edge_turn(R);
		go_till(2);
		place(L);
	}
	else if(position_W == S){
		if (bot_direction == DOWN) {
			cross_turn(R);
			cross_turn(R);
		}
		go_till(1);
		cross_turn(L);
		zig_zag = 1;
		go_till(1);
		zig_zag = 0;
		cross_turn(L);
		go_till(2);
		place(R);
	}
	else if(position_W == P){
		if (bot_direction == UP) {
			cross_turn(R);
			cross_turn(R);
		}
		go_till(1);
		cross_turn(R);
		zig_zag = 1;
		go_till(1);
		zig_zag = 0;
		cross_turn(L);
		go_till(2);
		place(R);
	}
}

/*
*
* Function Name: H2_path
* Input: void
* Output: void
* Logic: This function is used to store the path of house 2 from any warehouse
* Example Call: H2_path();
*/
void H2_path() {
	if(position_W == B){
		if (bot_direction == UP) {
			cross_turn(R);
			cross_turn(R);
		}
		NODE_WIDTH = 2;
		go_till(1);
		edge_turn(L);
		NODE_WIDTH = 2;
		go_till(2);
		edge_turn(L);
		go_till(2);
		place(R);
	}
	else if(position_W == C){
		if (bot_direction == DOWN) {
			cross_turn(R);
			cross_turn(R);
		}
		go_till(1);
		cross_turn(R);
		zig_zag = 1;
		go_till(1);
		zig_zag = 0;
		cross_turn(R);
		go_till(2);
		place(L);
	}
	else if(position_W == E){
		if (bot_direction == UP) {
			cross_turn(R);
			cross_turn(R);
		}
		go_till(1);
		cross_turn(L);
		zig_zag = 1;
		go_till(1);
		zig_zag = 0;
		cross_turn(R);
		go_till(2);
		place(L);
	}
	else if(position_W == S){
		if (bot_direction == DOWN) {
			cross_turn(R);
			cross_turn(R);
		}
		go_till(1);
		place(L);
	}
	else if(position_W == G){
		if (bot_direction == DOWN) {
			cross_turn(R);
			cross_turn(R);
		}
		go_till(1);
		place(R);
	}
	else if(position_W == P){
		if (bot_direction == UP) {
			cross_turn(R);
			cross_turn(R);
		}
		go_till(3);
		place(L);
	}
}

/*
*
* Function Name: H3_path
* Input: void
* Output: void
* Logic: This function is used to store the path of house 3 from any warehouse
* Example Call: H3_path();
*/
void H3_path() {
	if(position_W == B){
		if (bot_direction == DOWN) {
			cross_turn(R);
			cross_turn(R);
		}
		go_till(3);
		place(L);
	}
	else if(position_W == C){
		if (bot_direction == DOWN) {
			cross_turn(R);
			cross_turn(R);
		}
		go_till(1);
		place(L);
	}
	else if(position_W == E){
		if (bot_direction == UP) {
			cross_turn(R);
			cross_turn(R);
		}
		go_till(1);
		place(R);
	}
	else if(position_W == S){
		if (bot_direction == DOWN) {
			cross_turn(R);
			cross_turn(R);
		}
		go_till(1);
		cross_turn(L);
		zig_zag = 1;
		go_till(1);
		zig_zag = 0;
		cross_turn(R);
		place(L);
	}
	else if(position_W == G){
		if (bot_direction == DOWN) {
			cross_turn(R);
			cross_turn(R);
		}
		go_till(3);
		cross_turn(L);
		zig_zag = 1;
		go_till(1);
		zig_zag = 0;
		cross_turn(R);
		place(L);
	}
	else if(position_W == P){
		if (bot_direction == UP) {
			cross_turn(R);
			cross_turn(R);
		}
		go_till(1);
		cross_turn(R);
		zig_zag = 1;
		go_till(1);
		zig_zag = 0;
		cross_turn(R);
		place(L);
	}
}

/*
*
* Function Name: H4_path
* Input: void
* Output: void
* Logic: This function is used to store the path of house 4 from any ware house
* Example Call: H4_path();
*/
void H4_path() {
	if(position_W == B){
		if (bot_direction == DOWN) {
			cross_turn(R);
			cross_turn(R);
		}
		go_till(3);
		cross_turn(R);
		zig_zag = 1;
		go_till(1);
		zig_zag = 0;
		cross_turn(R);
		place(L);
	}
	else if(position_W == C){
		if (bot_direction == DOWN) {
			cross_turn(R);
			cross_turn(R);
		}
		go_till(1);
		cross_turn(R);
		zig_zag = 1;
		go_till(1);
		zig_zag = 0;
		cross_turn(R);
		place(L);
	}
	else if(position_W == E){
		if (bot_direction == UP) {
			cross_turn(R);
			cross_turn(R);
		}
		go_till(1);
		cross_turn(L);
		zig_zag = 1;
		go_till(1);
		zig_zag = 0;
		cross_turn(R);
		place(L);
	}
	else if(position_W == S){
		if (bot_direction == DOWN) {
			cross_turn(R);
			cross_turn(R);
		}
		go_till(1);
		place(R);
	}
	else if(position_W == G){
		if (bot_direction == DOWN) {
			cross_turn(R);
			cross_turn(R);
		}
		go_till(3);
		place(R);
	}
	else if(position_W == P ){
		if (bot_direction == UP) {
			cross_turn(R);
			cross_turn(R);
		}
		go_till(1);
		place(L);
	}
}

/*
*
* Function Name: H5_path
* Input: void
* Output: void
* Logic: This function is used to store the path of house 5 from any ware house
* Example Call: H5_path();
*/
void H5_path() {
	if (bot_direction == DOWN){
		cross_turn(R);
		cross_turn(R);
	}
	if(position_W == B) {
		go_till(4);
		NODE_WIDTH = 2;
		go_till(1);
		edge_turn(R);
		NODE_WIDTH = 2;
		M2_Shaft_counter = 1;
		TURN_LEN = 35;
		attachInterrupt(digitalPinToInterrupt(M2_ENCODER_CLK), M2_encode, FALLING);
		while(M2_Shaft_counter)
			follow_line();
		MODE = WHITE;
		go_till(1);
		place(R);
	}
	else if(position_W == C) {
		go_till(2);
		NODE_WIDTH = 2;
		go_till(1);
		edge_turn(R);
		NODE_WIDTH = 2;
		M2_Shaft_counter = 1;
		TURN_LEN = 200;
		attachInterrupt(digitalPinToInterrupt(M2_ENCODER_CLK), M2_encode, FALLING);
		while(M2_Shaft_counter)
			follow_line();
		go_till(1);
		place(R);
	}
	else if(position_W == E) {
		NODE_WIDTH = 2;
		go_till(1);
		edge_turn(R);
		NODE_WIDTH = 2;
		M2_Shaft_counter = 1;
		TURN_LEN = 200;
		attachInterrupt(digitalPinToInterrupt(M2_ENCODER_CLK), M2_encode, FALLING);
		while(M2_Shaft_counter)
			follow_line();
		go_till(1);
		place(R);
	}
	else if(position_W == S) {
		go_till(2);
		NODE_WIDTH = 2;
		go_till(1);
		edge_turn(L);
		NODE_WIDTH = 2;
		M2_Shaft_counter = 1;
		TURN_LEN = 200;
		attachInterrupt(digitalPinToInterrupt(M2_ENCODER_CLK), M2_encode, FALLING);
		while(M2_Shaft_counter)
			follow_line();
		go_till(1);
		place(L);
	}
	else if(position_W == G) {
		go_till(4);
		NODE_WIDTH = 2;
		go_till(1);
		edge_turn(L);
		NODE_WIDTH = 2;
		M2_Shaft_counter = 1;
		TURN_LEN = 200;
		attachInterrupt(digitalPinToInterrupt(M2_ENCODER_CLK), M2_encode, FALLING);
		while(M2_Shaft_counter)
			follow_line();
		go_till(1);
		place(L);
	}
	else if(position_W == P) {
		NODE_WIDTH = 2;
		go_till(1);
		edge_turn(L);
		NODE_WIDTH = 2;
		M2_Shaft_counter = 1;
		TURN_LEN = 200;
		attachInterrupt(digitalPinToInterrupt(M2_ENCODER_CLK), M2_encode, FALLING);
		while(M2_Shaft_counter)
			follow_line();
		go_till(1);
		place(L);
	}
}
