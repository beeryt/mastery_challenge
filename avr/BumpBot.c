
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

/* Determines whether to use switch logic vs. if/else logic */
#define SWITCH

/* Variable and constant declarations */
#define WskrR 0					// Right whisker input bit
#define WskrL 1					// Left  whisker input bit
#define EngEnR 4				// Right engine enable bit
#define EngEnL 7				// Left  engine enable bit
#define EngDirR 5				// Right engine direction bit
#define EngDirL 6				// Left  engine direction bit

#define MovFwd (1<<EngDirR|1<<EngDirL)	// Move forward command
#define MovBck 0x00						// Move backward command
#define TurnR (1<<EngDirL)				// Turn right command
#define TurnL (1<<EngDirR)				// Turn left command
#define Halt (1<<EngEnR|1<<EngEnL)		// Halt command

void HitRight();
void HitLeft();

int main(void)
{

	/* Initialize Port B for output */
	DDRB = 0xFF;	// Set Port B DDR to output
	PORTB = 0x00;	// Initialize all Port B outputs to low

	/* Initialize Port D for input */
	DDRD = 0x00;	// Set Port D DDR to input
	// PORTD = 0xFF;	// Initialize Port D inputs to tri-state

	/* Initialize TekBot forward movement */
	PORTB = MovFwd;

	/* Main Loop */
	while (1)
	{
	#ifdef SWITCH
		switch (PIND & (1<<WskrR|1<<WskrL))	// Get whisker input from Port D
		{
			case (1 << WskrL):	// Right whisker hit (Active Low)
				HitRight();
				break;
			case (1 << WskrR):	// Left whisker hit (Active Low)
				HitLeft();
				break;
			default:
				break;			// The default is to do nothing
		}
	#else
		uint8_t mpr = PIND & (1<<WskrR|1<<WskrL); // Get input from Port D
		if (mpr == (1<<WskrL))	// Right whisker hit (Active Low)
			HitLeft();			// Call the HitLeft function
		else if (mpr == (1<<WskrR))	// Left whisker hit
			HitRight();			// Call the HitRight function
		else
			;					// The default is to do nothing
	#endif
	}
}

void HitRight()
{
	_delay_ms(1000);
	PORTB = MovBck;		// Load the move backward command
	_delay_ms(500);		// Wait for 2 seconds
	PORTB = TurnR;		// Load the turn left command
	_delay_ms(1000);	// Wait for 1 second
	PORTB = MovFwd;		// Load move forward command
}

void HitLeft()
{
	_delay_ms(1000);
	PORTB = MovBck;		// Load the move backward command
	_delay_ms(500);	// Wait for 2 seconds
	PORTB = TurnL;		// Load the turn left command
	_delay_ms(1000);	// Wait for 1 second
	PORTB = MovFwd;		// Load move forward command
}