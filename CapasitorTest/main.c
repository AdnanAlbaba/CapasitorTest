/*
ATmega8, 48, 88, 168, 328

/Reset PC6|1   28|PC5
PD0|2   27|PC4
PD1|3   26|PC3
PD2|4   25|PC2
PD3|5   24|PC1
PD4|6   23|PC0
Vcc|7   22|Gnd
Gnd|8   21|Aref
PB6|9   20|AVcc
PB7|10  19|PB5 SCK
PD5|11  18|PB4 MISO
PD6|12  17|PB3 MOSI
PD7|13  16|PB2
LED    PB0|14  15|PB1
*/

#define  F_CPU 1000000UL // defines the clock frequency as 1 MHz (unsigned long)

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "lcd.h"

#define resistorValue 1000.0F

// define a global variable for the timer ticks in TIMER1
volatile uint16_t timer1_ticks = 0;

#define SET_BIT(byte, bit) (byte |=(1<<bit))
#define CLEAR_BIT(byte, bit) (byte &= ~(1<<bit))

void init_display(){
	
	lcd_init(LCD_DISP_ON);
}

void init (void)
{
	DDRB = 0x01;         // pin 0 of PORTB as output charge pin
	DDRC = 0;         // all pins of PORTC as input analogRead
	
	// ADC init
	//  reference voltage: supply AVCC
	//  channel ADC0
	//  clock: f_cpu/8  (=125kHz)
	//  right-aligned result
	ADMUX  = (0 << REFS1) | (1 << REFS0) | (0 << ADLAR)
	| (0 << MUX3)  | (0 << MUX2)  | (0 << MUX1) | (0 << MUX0);
	//ADCSRA = (1 << ADEN) | (1 << ADSC)  | (1 << ADATE)
	//| (0 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADIE);
	/*
	bit          7           6            5          4          3            2           1           0
	name        ADEN        ADSC        ADATE       ADIF       ADIE        ADPS2       ADPS1       ADPS0
	set to       1           0            1          0          1            0           1           1
	
	ADEN = 1     enable ADC
	ADSC = 0     don't start ADC yet
	ADATE = 1    enable ADC auto trigger (i.e. use free running mode)
	ADIF = 0     don't set ADC interrupt flag
	ADIE = 1     enable ADC interrupt
	
	ADPS2 = 0
	ADPS1 = 1    1 MHz clock / 8 = 125 kHz ADC clock
	ADPS0 = 1
	*/
	ADCSRA = 0b10101011;
	
	// run 16-bit TIMER on f_cpu
	// no prescaler, normal operation
	// 1 MHz gives 15.3 overflows per second
	// i.e. 62500 clicks in 1/16 s
	TCCR1A = (0 << COM1A1) | (0 << COM1A0)
	| (0 << COM1B1) | (0 << COM1B0)
	| (0 << WGM11)  | (0 << WGM10);                   // set mode
	TCCR1B = (0 << WGM12)  | (0 << WGM13)
	| (1 << CS22)   | (0 << CS21)   | (1 << CS20);    // set prescaler clk/1024
	init_display();
	ADCSRA |= (1 << ADSC); // start the ADC
	
}

void ADCRead(){
	ADCSRA |= (1 << ADSC);         // start conversion
	while (ADCSRA & (1 << ADSC)) ; //wait for the ADC to ready
}

volatile uint16_t adcValue;
int main (void)
{
	uint16_t elapsedTime;
	float microFarads;
	float nanoFarads;
	char c[20];
	init();
	sei();
	while (1)            // infinite main loop
	{
		PORTB = 0x01;      // switch PB0 to 1 charge pin
		TCNT1 = 0;         // restart TIMER1 from zero
		//ADCRead(); no need free run adc enabled
		while (adcValue < 648)
		{
			//ADCRead();
			elapsedTime = TCNT1;
			microFarads = ((float)elapsedTime / resistorValue) * 1000;
			
			if (microFarads > 1)
			{
				lcd_clrscr();
				lcd_gotoxy(0,0);
				lcd_puts(strcat(utoa(microFarads, c, 10), " Micro farad\n"));
			}
			else
			{
				// if value is smaller than one microFarad, convert to nanoFarads (10^-9 Farad).
				// This is  a workaround because Serial.print will not print floats
				nanoFarads = microFarads * 1000000.0;      // multiply by 1000 to convert to nanoFarads (10^-9 Farads)
				lcd_clrscr();
				lcd_gotoxy(0,0);
				lcd_puts(strcat(utoa(nanoFarads, c, 10), " Nano farad\n"));
			}
		}
		
		PORTB = 0x00;      // switch PB0 to 0 charge pin
		DDRD = 0x01;       // pin 0 of PORTD as output discharge pin
		PORTD = 0x00;      // switch PB0 to 0 discharge pin
		while (adcValue > 0)
		{
			/*
			wait for the capacitor to discharged.
			*/
			//ADCRead();// no need free runn adc enabled
		}
		DDRD = 0x00;       // pin 0 of PORTD as input discharge pin
		_delay_ms(100);
	}
	
}

ISR(ADC_vect){
	adcValue = ADC;
}
