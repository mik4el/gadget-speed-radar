#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <FreqMeasure.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define DOPPLER_SHIFT_CONSTANT 19.49
#define LCD_ADDRESS 0x27
#define CLEAN_SCREEN_INTERVAL 5000L
#define MINIMUM_SPEED 0.3 
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

double freq_sum = 0;
int freq_count = 0;
unsigned long time_since_reading = 0;

void loop() {
  if (FreqMeasure.available()) {
    
    // average several reading together
    freq_sum = freq_sum + FreqMeasure.read();
    freq_count++;
    
    unsigned long currentMillis = millis();

    // print speed when enough samples
    if (freq_count > 30) {
      float frequency = FreqMeasure.countToFrequency(freq_sum / freq_count);
      lcd.setCursor (0,1);        // go to start of 2nd line
      float speed = frequency/DOPPLER_SHIFT_CONSTANT;
      if (speed > MINIMUM_SPEED) {
        lcd.print(speed);
        lcd.print(" km/h     ");      
        time_since_reading = currentMillis;
      } 
      freq_sum = 0;
      freq_count = 0;
    }
    
    // show no speed if no new reading in last 5s
    if (currentMillis - time_since_reading >= CLEAN_SCREEN_INTERVAL) {
      lcd.setCursor (0,1);        // go to start of 2nd line
      lcd.print("...        ");
      time_since_reading = currentMillis;      
    }
    
  }
}
