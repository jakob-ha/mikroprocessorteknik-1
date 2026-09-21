
#define MCU __AVR_ATmega328P__
#define F_CPU 16000000UL

#include <avr/io.h>

int main(void) {
  // Set DDRB bit 5
  // This causes Arduino pin D13 to be an output
  DDRB = 0x20;
  ADMUX = (1 << REFS0);
  ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0));
  ADCSRA = (1 << ADEN)  | // Enable ADC
           (1 << ADPS2) | // Prescaler Bit 2
           (1 << ADPS1) | // Prescaler Bit 1
           (1 << ADPS0);  // Prescaler Bit 0

  while (1) {
     ADCSRA |= (1 << ADSC);
    uint16_t adcValue = ADC;
    for (uint16_t i = 0; i < adcValue; i++)
    {_delay_us(1000);}
    PORTB ^= 0x20;
  }
}
