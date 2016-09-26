/*
 * Personal Calibration Sketch - MJC
 * 
 * 1000 - 2000 microsecond pulses correspond to 0 - 180 degrees of movement
 * 1500us / 90deg is neutral
 */

#include <Wire.h>
#include <ArduinoNunchuk.h>
#include <Servo.h> 
 
Servo esc1, esc2;  // create servo object to control a servo 

#define BAUDRATE 19200
#define MAX 2000  // 180 deg
#define MIN 1000  // 0 deg
#define NEUTRAL 1500  // 90 deg

ArduinoNunchuk nunchuk = ArduinoNunchuk();

void setup()
{
  Serial.begin(BAUDRATE);
  esc1.attach(5);
  // esc2.attach(6);
  nunchuk.init();
  esc1.writeMicroseconds(NEUTRAL);
  pinMode(13, OUTPUT);
}

void loop()
{

  nunchuk.update();

  int y = nunchuk.analogY;
  
  Serial.print('\t');
  Serial.println(y);
  if(y > 128 + 30) {
     esc1.writeMicroseconds(MAX);
     // esc2.writeMicroseconds(MAX);
     Serial.println(MAX);
     digitalWrite(13, HIGH);
  } else if (y < 128 - 30){
     esc1.writeMicroseconds(MIN); 
     // esc2.writeMicroseconds(MIN);
     Serial.println(MIN);
     digitalWrite(13, HIGH);
  } else {
     esc1.writeMicroseconds(NEUTRAL);
     // esc2.writeMicroseconds(NEUTRAL); 
     Serial.println(NEUTRAL);
     digitalWrite(13, LOW);
  }
}
