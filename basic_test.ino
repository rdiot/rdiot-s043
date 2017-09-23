/* Rotation Encoder Module (KY-040) [S043] : http://rdiot.tistory.com/125 [RDIoT Demo] */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x27,20,4);  // LCD2004

int encoderPin1 = 2; // (CLK)
int encoderPin2 = 3; // (DT)
int encoderSwitchPin = 4; //push button switch (SW)
 
volatile int lastEncoded = 0;
volatile long encoderValue = 0;
 
long lastencoderValue = 0;
 
int lastMSB = 0;
int lastLSB = 0;
 
void setup()
{
  lcd.init();  // initialize the lcd 
  lcd.backlight();
  lcd.print("start LCD2004");
 
  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);
 
  pinMode(encoderSwitchPin, INPUT);
 
  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on
 
  digitalWrite(encoderSwitchPin, HIGH); //turn pullup resistor on
 
  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);
 
  delay(1000);
 
  lcd.clear();
}
 
int nowCnt = 0;
 
void loop()
{
 
  lcd.setCursor(0,0);
  lcd.print("S043:RotationEncoder");
 
  //Do stuff here
  if(digitalRead(encoderSwitchPin)){
     lcd.setCursor(0,1);
     lcd.print("button not pushed"); 
    //button is not being pushed
  }else{
     lcd.setCursor(0,1);
     lcd.print("button pushed     "); 
  }
 
  //Serial.println(encoderValue);
  lcd.setCursor(0,2);
  lcd.print("encoderValue="+(String)encoderValue+"   "); 
 
  lcd.setCursor(0,3);
  lcd.print("DT="+(String)digitalRead(encoderPin2)+" CLK="+(String)digitalRead(encoderPin1)+" "); 
 
  delay(100); 
}
 
 
void updateEncoder(){
  int MSB = digitalRead(encoderPin1); //MSB 
  int LSB = digitalRead(encoderPin2); //LSB 
 
  int encoded = (MSB << 1) LSB; 
  int sum  = (lastEncoded << 2) encoded; 
 
  if(sum == 0b1101 sum == 0b0100 sum == 0b0010 sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 sum == 0b0111 sum == 0b0001 sum == 0b1000) encoderValue --;
 
  lastEncoded = encoded; //store this value for next time
}
