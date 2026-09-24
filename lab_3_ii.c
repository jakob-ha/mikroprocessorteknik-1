//#include "hd44780.h"
#include <LiquidCrystal.h>
#include <stdio.h>

LiquidCrystal lcd(3, 2, 4, 5, 6, 7);

char buffer[20];

void setup() {
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  //lcd_init();
  
  ADMUX = (1 << REFS0);
  ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0));
  ADCSRA = (1 << ADEN)  | // Enable ADC
           (1 << ADPS2) | // Prescaler Bit 2
           (1 << ADPS1) | // Prescaler Bit 1
           (1 << ADPS0);  // Prescaler Bit 0
}

void loop() {
  ADCSRA |= (1 << ADSC);
  int adcValue = ADC;
  snprintf(buffer, sizeof(buffer), "%d", adcValue);
  lcd.clear();
  //lcd_clrscr();
  lcd.setCursor(0, 0);
  //lcd_goto(0x00);
  lcd.print("Pot. Value:");
  //lcd_puts("Pot. Value:");
  lcd.setCursor(0, 1);
  //lcd_goto(0x40);
  lcd.print(buffer);
  //lcd_puts(buffer);
  delay(200);
}
