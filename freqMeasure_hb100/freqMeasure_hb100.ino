#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <FreqMeasure.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define DOPPLER_SHIFT_CONSTANT 19.49
#define LCD_ADDRESS 0x27
 
LiquidCrystal_I2C  lcd(LCD_ADDRESS,2,1,0,4,5,6,7);

void setup() {
  Serial.begin(57600);
  FreqMeasure.begin();
  // activate LCD module
  lcd.begin (16,2); // for 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home(); // set cursor to 0,0
  lcd.print("Speed radar:"); 
  lcd.setCursor (0,1);        // go to start of 2nd line
  lcd.print("Started"); 
}

double sum=0;
int count=0;

void loop() {
  if (FreqMeasure.available()) {
    // average several reading together
    sum = sum + FreqMeasure.read();
    count = count + 1;
    if (count > 30) {
      float frequency = FreqMeasure.countToFrequency(sum / count);
      lcd.setCursor (0,1);        // go to start of 2nd line
      lcd.print(frequency/DOPPLER_SHIFT_CONSTANT);
      lcd.print(" km/h");      
      sum = 0;
      count = 0;
    }
  }
}

