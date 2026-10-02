#include <LiquidCrystal.h>
#include <stdio.h>

LiquidCrystal lcd(3, 2, 4, 5, 6, 7);

char buffer[12];

const unsigned char n = 40;
volatile unsigned int adcValues[n] = {};

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
     
  ADMUX = (1 << REFS0);
  
  ADCSRA = (1 << ADEN)  |  
           (1 << ADIE)  | 
           (1 << ADPS2) | 
           (1 << ADPS1) | 
           (1 << ADPS0);

  sei();
  
  ADCSRA |= (1 << ADSC);
  
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");
}

void loop() {
  int adcAverage = ave();
  
  int temperature = ((5000L * adcAverage)/ 1023L) - 500;
  
  char rawNumBuffer[8];
  snprintf(rawNumBuffer, sizeof(rawNumBuffer), "%d", (int)temperature);

  int len = strlen(rawNumBuffer);
  
  for (int i = 0; i < len - 1; i++) {
    buffer[i] = rawNumBuffer[i];
  }
  
  buffer[len - 1] = '.';
  buffer[len]     = rawNumBuffer[len - 1];
  buffer[len + 1] = (char)176;
  buffer[len + 2] = 'C';
  
  buffer[len + 3] = ' ';
  buffer[len + 4] = ' ';
  buffer[len + 5] = ' ';
  buffer[len + 6] = '\0';
  
  lcd.setCursor(0, 1);
  lcd.print(buffer);
  
  
  delay(5);
}

ISR(ADC_vect) {
  static unsigned char x = 0;
  adcValues[x] = ADC;
  x++;
  if (x == n) {
    x = 0;
  }
  ADCSRA |= (1 << ADSC);
}

int ave(){
  int sum = 0;  
  for (unsigned char i = 0; i < n; i++) {
    sum += adcValues[i];
  }
  
  return sum / n;
}
