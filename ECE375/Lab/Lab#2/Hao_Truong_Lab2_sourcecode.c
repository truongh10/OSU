/*
 * Hao_Truong_Lab2_sourcecode.c
 *
 * Created: 10/8/2021 2:39:51 PM
 * Author : Hao Truong
 */ 


/*
This code will cause a TekBot connected to the AVR board to
move forward and when it touches an obstacle, it will reverse
and turn away from the obstacle and resume forward motion.

PORT MAP
Port B, Pin 4 -> Output -> Right Motor Enable
Port B, Pin 5 -> Output -> Right Motor Direction
Port B, Pin 7 -> Output -> Left Motor Enable
Port B, Pin 6 -> Output -> Left Motor Direction
Port D, Pin 1 -> Input -> Left Whisker
Port D, Pin 0 -> Input -> Right Whisker
*/

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>


// Function prototypes
void HitRight();
void HitLeft();
void HitBoth();

int main(void)
{
	// Initialize relevant I/O Ports
	DDRB = 0b11110000;	// Set 7-4th bits as outputs
	PORTB = 0b01100000;	// Turn on 6-5th LEDs
	
	DDRD = 0b00000000;	// Set 7-0th bits as inputs
	PORTD = 0b11111111;	// Enable pull up resisters
	
	

	while (1) // loop forever
	{
		// Your code goes here
		if (PIND == 0b11111110) {	// if right whisker was hit
			HitRight();				// do HitRight function
		}
		if (PIND == 0b11111101) {	// if left whisker was hit
			HitLeft();					// do HitLeft function
		}
		if (PIND == 0b11111100) {	// if both whiskers are triggered
			HitRight();				// do as HitRight
		}
	}
}

void HitRight() {
	// reverse for a second
	PORTB = 0b00000000;
	_delay_ms(1000);
	
	// turn left for a second
	PORTB = 0b00100000;
	_delay_ms(1000);
	
	// move forward again
	PORTB = 0b01100000;
}

void HitLeft() {
	// move backwards for a second
	PORTB = 0b00000000;
	_delay_ms(1000);
	
	// turn right for a second
	PORTB = 0b01000000;
	_delay_ms(1000);
	
	// move forward again
	PORTB = 0b01100000;
}


