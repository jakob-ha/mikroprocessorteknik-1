#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

int number = 2345;

int main(void) {  
  // Set lower 7 pins of PORTD (PD0 to PD6) as OUTPUT
  DDRD = 0b01111111;
  DDRB = 0b00001111;

  const unsigned char n = 16;
  const unsigned char m = 4;

  unsigned char numeralArray[16] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111, // 9
    0b01110111, // A 
    0b01111100, // b 
    0b00111001, // C 
    0b01011110, // d 
    0b01111001, // E 
    0b01110001  // F 
  };
  unsigned char displayArray[m] = {
    0b00000111,
    0b00001011,
    0b00001101,
    0b00001110,
  };

  while (1) {
    for (unsigned char j = 0; j < m; j++)
    { 
      int digit = number / pow(10, j);
      lit(displayArray[j], numeralArray[digit]);
      _delay_ms(50);
  	}
    _delay_ms(50);
  }
}

void lit(char display, char numeral){
	PORTB = ~display;
  	PORTD = ~numeral;
}
