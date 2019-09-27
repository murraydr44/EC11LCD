/*
** Rotary Encoder Example
** Use the Sparkfun Rotary Encoder to vary brightness of LED
**
** Sample the encoder at 200Hz using the millis() function
*/

int brightness = 128;    // how bright the LED is, start at half brightness
int fadeAmount = 16;    // how many points to fade the LED by
unsigned long currentTime;
unsigned long loopTime;
const int pin_A = 12;  // pin 12 / PB4
const int pin_B = 11;  // pin 11 / PB3
const int pin_C = 9;  // pin 9 / PB1
unsigned char encoder_A;
unsigned char encoder_B;
unsigned char encoder_A_prev=0;

//Libraries 
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address, if it's not working try 0x27.


void setup()  {
  // declare pin_C to be an output:
  pinMode(pin_C, OUTPUT);
  pinMode(pin_A, INPUT);
  pinMode(pin_B, INPUT);
  currentTime = millis();
  loopTime = currentTime; 

  lcd.begin(16,2);   // iInit the LCD for 16 chars 2 lines
  lcd.backlight();   // Turn on the backligt (try lcd.noBaklight() to turn it off)
  lcd.setCursor(0,0); //First line
  lcd.print("EC11 PB1 pin9");
//  lcd.setCursor(0,1); //Second line
 // lcd.print("*Ardumotive.com*");


} 

void loop()  {
  // get the current elapsed time
  currentTime = millis();
  if(currentTime >= (loopTime + 4)){
    // 4ms since last check of encoder = 250Hz  
    encoder_A = digitalRead(pin_A);    // Read encoder pins
    encoder_B = digitalRead(pin_B);   
    if((!encoder_A) && (encoder_A_prev)){
      // A has gone from high to low 
      if(encoder_B) {
        // B is high so clockwise
        // increase the brightness, dont go over 240
        if(brightness + fadeAmount <= 240) brightness += fadeAmount;               
      }   
      else {
        // B is low so counter-clockwise      
        // decrease the brightness, dont go below 0
        if(brightness - fadeAmount >= 0) brightness -= fadeAmount;               
      }   

    }   
    encoder_A_prev = encoder_A;     // Store value of A for next time    
    
    // set the brightness of pin_C:
    analogWrite(pin_C, brightness);   
    lcd.setCursor(0,1); //Second line
    lcd.print(brightness);
    lcd.print("   ");

    loopTime = currentTime;  // Updates loopTime
  }
  // Other processing can be done here
                           
}
