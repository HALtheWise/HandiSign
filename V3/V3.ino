/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include "myservo.h"


MyServo fingers[4];
// twelve servo objects can be created on most boards

MyServo *activeServo;

int pos = 0;    // variable to store the servo position
long startTime = 0;

const int PERIOD = 4000;

void setup() {
  fingers[0].attach(2);
  fingers[0].calibrate(90,10);

  fingers[1].attach(3);
  fingers[1].calibrate(90,10);

  fingers[2].attach(4);
  fingers[2].calibrate(90,10);

  fingers[3].attach(5);
  fingers[3].calibrate(90,10);

  startTime = millis();

  activeServo = &fingers[0];

  Serial.begin(9600);
}

void handleSerial(){
  while (Serial.available() > 0){
    byte b = Serial.read();
    int id = -1;

    if (b == '0'){
      id = 0;
    }
    else if (b == '1'){
      id = 1;
    }
    else if (b == '2'){
      id = 2;
    }
    else if (b == '3'){
      id = 3;
    }else{
      continue;
    }

    activeServo = &fingers[id];
    startTime = millis();
  }
}

void loop() {
  handleSerial();
  
  int t = millis() - startTime;
  //startTime = millis();

  float pos = 0.0;

  if ((t % PERIOD)> PERIOD / 2){
    pos = 1.0;
  }
  
  activeServo->write(pos);
  delay(1);
  Serial.println(pos);
//  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
//  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
}

