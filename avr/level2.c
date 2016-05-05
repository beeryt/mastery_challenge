
/*
This code will read a button from I/O, then write to I/O to
turn on an LED.

PORT MAP
Port B, Pin 4 -> Output -> Green LED
Port D, Pin 0 -> Input -> Push Button
*/

#define F_CPU 16000000
#include <avr/io.h> 
#include <util/delay.h> 

/* Variable and constant declarations */
#define BTNR 0			// Right button input bit
#define BTNL 2			// Left button input bit
#define START 4			// Starting LED bit

/* Useful macros */
#define BTN_MASK (PIND & (1<<BTNL|1<<BTNR))

int main(void)
{
	/* Initialize Ports */
	DDRB = 0xFF;	// Set Port B DDR to output
	PORTB = 0x00;	// Initialize all Port B outputs to low
	DDRD = 0x00;	// Set Port D DDR to input
	PORTD = 0xFF;	// Initialize Port D inputs to tri-state

	/* State variables */
	uint8_t LED = START;

	/* Set initial state */
	PORTB |= (1<<LED);

	/* Main Loop */
	while (1)
	{
		PORTB |= (1<<LED);
		_delay_ms(100);

		switch (BTN_MASK)
		{
			case (1<<BTNL):
				PORTB &= ~(1<<LED--);
				LED %= 8;
				break;
			case (1<<BTNR):
				PORTB &= ~(1<<LED++);
				LED %= 8;
				break;
			default:
				break;
		}
	}
}
