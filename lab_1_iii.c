

#define MCU __AVR_ATmega328P__
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  // this section of code will execute once
  // Set DDRD bit 7
  // This causes Arduino pin D7 to be an output
  // This pin is connected to the LED
  DDRD = 0b11111100;

  while (1) {

    PORTD |= 0b10000100;
    PORTD &= 0b10000100;
    _delay_ms(5000);
    PORTD |= 0b10001100;
    PORTD &= 0b10001100;
    _delay_ms(2000);
    PORTD |= 0b00110000;
    PORTD &= 0b00110000;
    _delay_ms(5000);
    PORTD |= 0b01110000;
    PORTD &= 0b01110000;
	_delay_ms(2000);  
  }
}
