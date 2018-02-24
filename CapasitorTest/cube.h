#ifndef CUBE_H
#define CUBE_H

/*
 * nessecary library include 
*/
#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>

/*
 * constants for the cube size
*/
#define LED_SIZE 9
#define LAYER_SIZE 3
#define CUBE_SIZE LED_ZIZE * LAYER_SIZE

/*
 * define control port and pin for leds in single layer    
*/
#define led1_port PORTD
#define led1_pin PD0 
#define led2_port PORTD
#define led2_pin PD1  
#define led3_port PORTD
#define led3_pin PD2  
#define led4_port PORTD
#define led4_pin PD3  
#define led5_port PORTD
#define led5_pin PD4  
#define led6_port PORTD
#define led6_pin PD5  
#define led7_port PORTD
#define led7_pin PD6 
#define led8_port PORTD
#define led8_pin PD7  
#define led9_port PORTB
#define led9_pin PB0

/*
 * define controll port and pin for layers 
*/
#define layer1_port PORTB
#define layer1_pin PB1
#define layer2_port PORTB
#define layer2_pin PB2
#define layer3_port PORTB
#define layer3_pin PB3

/*
 * define macros for bit manipulation
*/
#define DDR(x) (*(&x - 1))
#define SETON(port, pin) (port |= (1 << pin))
#define SETOFF(port, pin) (port &= (1 << pin))
#define TOGGLE(port, pin) (port ^= (1 << pin))

/*
 * define led type
*/
typedef struct {
    uint16_t port;
    uint16_t pin;
}led;

typedef struct {
    uint16_t port;
    uint16_t pin;
}layer;

//index 0 for port, index 1 for pin
uint16_t* led_matrix [LED_SIZE][2];
uint16_t* layer_matrix [LAYER_SIZE];

void initCube();

void testMethode();


#endif
