/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#define NUM_SERVOS 4

#include "poses.h"
#include "myservo.h"

MyServo fingers[NUM_SERVOS];

int pos = 0;    // variable to store the servo position
long lastTime = 0;

float *activePose = pOPEN; // Pointer to array of length NUM_SERVOS

const int PERIOD = 4000;

void setup() {
  Serial.begin(9600);

  fingers[0].attach(2);
  fingers[0].calibrate(70,110);

  fingers[1].attach(3);
  fingers[1].calibrate(70,130);

  fingers[2].attach(4);
  fingers[2].calibrate(110,70);

  fingers[3].attach(5);
  fingers[3].calibrate(90,90);

  lastTime = millis();

  setupPoses();
}

void activatePose(float *pose){
  for (int i = 0; i < NUM_SERVOS; i++){
    fingers[i].write(pose[i]);
  }
}

void handleSerial(){
  while (Serial.available() > 0){
    byte b = Serial.read();
    int id = -1;

    if (b == 'o'){
      activePose = pOPEN;
    }
    else if (b == 'c'){
      activePose = pCLOSED;
    }
    else if (b == 'g'){
      activePose = pGUN;
    }else{
      continue;
    }

    activatePose(activePose);
    lastTime = millis();
  }
}

void loop() {
  handleSerial();
  
  int t = millis() - lastTime;
  //lastTime = millis();

  if (t > PERIOD){
    activePose = pOPEN;
  }
  
  activatePose(activePose);

  delay(1);
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

