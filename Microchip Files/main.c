/*******************************************
 Message Project
 Name: Logan Dukes

 MessageProject.c

 Created: 8/8/2024 8:17:22 PM
 Author: Logan
 Description: This program will use a clock to continuously loop a digital
			  signal that feeds to a PLD in order to display a message.

*****************************************/
// INCLUDES
#include <avr/io.h>
#include <avr/interrupt.h>
// END OF INCLUDES
/******************************************/
// MACROS
uint8_t PIN543210 = 0b00111111;
uint8_t HI = 0b00010001;
uint8_t blankI = 0b00010000;
uint8_t LO = 0b00100011;
uint8_t VE = 0b00110101;
uint8_t YO = 0b00100111;
uint8_t Ublank = 0b00000101;
volatile uint8_t next_letters_flag = 0;
// END OF MACROS
/******************************************/


int main(void)
{
	PORTJ.DIRSET = PIN543210;
	PORTJ.OUTCLR = 0xFF;
	
	// Set prescaler to DIV1024
	TCC0.CTRLA = TC_CLKSEL_DIV1024_gc;
	
	// Set top val for 1 Hz
	// 1 / (2 MHz / 1024) = 0.000512
	// Top val is 1.5 / 0.000512 = 2929.6875
	TCC0.PER = 2930;
	
	// For using interrupts, level low
	TCC0.INTCTRLA = TC_OVFINTLVL_LO_gc;
	
	// Enable low level interrupts
	PMIC.CTRL = PMIC_LOLVLEN_bm;
	
	// Enable global interrupts
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
		// wait for timer overflow
		while (next_letters_flag == 0);
		// clear flag
		next_letters_flag = 0;
		
		// set letters to H and I
		PORTJ.OUT = HI;
		
		// wait for timer overflow
		while (next_letters_flag == 0);
		// clear flag
		next_letters_flag = 0;
		
		// set letters to blank and I
		PORTJ.OUT = blankI;
		
		// wait for timer overflow
		while (next_letters_flag == 0);
		// clear flag
		next_letters_flag = 0;
		
		// set letters to L and O
		PORTJ.OUT = LO;
		
		// wait for timer overflow
		while (next_letters_flag == 0);
		// clear flag
		next_letters_flag = 0;
		
		// set letters to V and E
		PORTJ.OUT = VE;
		
		// wait for timer overflow
		while (next_letters_flag == 0);
		// clear flag
		next_letters_flag = 0;
		
		// set letters to Y and O
		PORTJ.OUT = YO;
		
		// wait for timer overflow
		while (next_letters_flag == 0);
		// clear flag
		next_letters_flag = 0;
		
		// set letters to U and blank
		PORTJ.OUT = Ublank;
		
		// wait for timer overflow
		while (next_letters_flag == 0);
		// clear flag
		next_letters_flag = 0;
		
		// set letters to H and I
		PORTJ.OUT = HI;
    }
}


/*------------------------------------------------------------------------------
  ISR TCC0_OVF -- 
  
  Description: 
    This interrupt triggers when TCC0 overflows to update the set next_letters_flag

  Input(s): Timer overflow flag
  Output(s): Sets next_letters_flag
------------------------------------------------------------------------------*/
ISR(TCC0_OVF_vect) {
	next_letters_flag =  1;
}

