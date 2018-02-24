#define  F_CPU 1000000UL // defines the clock frequency as 1 MHz (unsigned long)
#include "cube.h"


void testMethode(){

	

	SETON(layer_matrix[0][0], layer_matrix[0][1]);
	TOGGLE(led1_port, led1_pin);
	/*
	int i,j;
	for (i = 0 ; i < LAYER_SIZE; i++){
		TOGGLE(layer_matrix[i].port, layer_matrix[i].pin);
		for (j = 0 ; j < LED_SIZE; j++){
			TOGGLE(led_matrix[j].port, led_matrix[j].pin);
		}
		TOGGLE(layer_matrix[i].port, layer_matrix[i].pin);
	}
	*/
}

void initCube(){

	DDRD = 0b11111111;
	DDRB = 0b11110000;

	layer_matrix[0][0] = PORTB;
	layer_matrix[0][1] = PB1;
	pritnf("sss");

	/* led_matrix[0][0] = led1_port;
	led_matrix[0][1] = led1_pin;
	led_matrix[1][0] = led2_port;
	led_matrix[1][1] = led2_pin;  
	led_matrix[2][0] = led3_port;
	led_matrix[2][1] = led3_pin;  
	led_matrix[3][0] = led4_port;
	led_matrix[3][1] = led4_pin;  
	led_matrix[4][0] = led5_port;
	led_matrix[4][1] = led5_pin;  
	led_matrix[5][0] = led6_port;
	led_matrix[5][1] = led6_pin;  
	led_matrix[6][0] = led7_port;
	led_matrix[6][1] = led7_pin;  
	led_matrix[7][0] = led8_port;
	led_matrix[7][1] = led8_pin;  
	led_matrix[8][0] = led9_port;
	led_matrix[8][1] = led9_pin;

	layer_matrix[0][0] = layer1_port;
	layer_matrix[0][1] = layer1_pin;  
	layer_matrix[1][0] = layer2_port;
	layer_matrix[1][1] = layer2_pin;  
	layer_matrix[2][0] = layer3_port;
	layer_matrix[2][1] = layer3_pin;   */

	 
    /* led_matrix[0].port = led1_port;
	led_matrix[0].pin = led1_pin;
	led_matrix[1].port = led2_port;
	led_matrix[1].pin = led2_pin;  
	led_matrix[2].port = led3_port;
	led_matrix[2].pin = led3_pin;  
	led_matrix[3].port = led4_port;
	led_matrix[3].pin = led4_pin;  
	led_matrix[4].port = led5_port;
	led_matrix[4].pin = led5_pin;  
	led_matrix[5].port = led6_port;
	led_matrix[5].pin = led6_pin;  
	led_matrix[6].port = led7_port;
	led_matrix[6].pin = led7_pin;  
	led_matrix[7].port = led8_port;
	led_matrix[7].pin = led8_pin;  
	led_matrix[8].port = led9_port;
	led_matrix[8].pin = led9_pin;

	layer_matrix[0].port = layer1_port;
	layer_matrix[0].pin = layer1_pin;        
	layer_matrix[1].port = layer2_port;
	layer_matrix[1].pin = layer2_pin;            
	layer_matrix[2].port = layer3_port;
	layer_matrix[2].pin = layer3_pin;              */

}
