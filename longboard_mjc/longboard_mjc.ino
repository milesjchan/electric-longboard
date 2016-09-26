/*
 * Miles Chan Electric Longboard Code
 * 
 * Helpful Information:
 * https://www.arduino.cc/en/Main/ArduinoBoardNano
 */

#include <Wire.h>
#include <ArduinoNunchuk.h>
#include <Servo.h>

#define BAUDRATE 19200
#define LOOP_DELAY 40

#define MAX 2000
#define MIN 1000
#define NEUTRAL 1500
#define CHUCK_MAX 255
#define CHUCK_MIN 0
#define CHUCK_NEUTRAL 128

int throttle = 0;

ArduinoNunchuk nunchuk = ArduinoNunchuk();
Servo esc1;

#define pwm1 5

void setup() {
  delay(10000); // give esc time to boot up
  Serial.begin(BAUDRATE);
  esc1.attach(pwm1);
  pinMode(13, OUTPUT);

  esc1.writeMicroseconds(NEUTRAL);
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  
  nunchuk.init();
}

void loop() {
  nunchuk.update();
  int y = nunchuk.analogY;
/*
  Serial.print("Throttle: ");
  Serial.println(y);
  Serial.print("cButton: ");
  Serial.println(nunchuk.cButton);
  Serial.print("zButton; ");
  Serial.println(nunchuk.zButton);
  */

  if (nunchuk.cButton == 1) {
    throttle = NEUTRAL;
  } else if (y > 115 && y < 135) {
    throttle = NEUTRAL;
  } else if (nunchuk.zButton == 1) {
    throttle = map(y, CHUCK_MIN, CHUCK_MAX, MIN, MAX);    
  }

  esc1.writeMicroseconds(throttle);
  
}
