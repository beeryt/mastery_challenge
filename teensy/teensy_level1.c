#include "teensy.h"
#include <avr/io.h>
#include <util/delay.h>

int main() {
  // Setup output LED
  // Configure ADC Hardware
  ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // Set the pre-scaler bits
  ADMUX |= (1<<REFS0);  // Set the reference voltage
  /*Select ADC9*/
  ADCSRA |= (1<<ADATE); // Auto Trigger Enable
  ADCSRA |= (0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0); // Free-running trigger
  ADMUX |= (1<<ADLAR); // Left align the register
  // Enable ADC
  ADCSRA |= (1<<ADEN); // Enable the ADC
  ADCSRA |= (1<<ADSC); // Continuous conversions
  // Start A2D Conversions

  while (1) {
    if (ADCH < 128) {
      PORTC |= (1<<PC7);
    }
    else {
      PORTC &= (0<<PC7);
    }
    _delay_ms(100);
  }

  return 0;
}