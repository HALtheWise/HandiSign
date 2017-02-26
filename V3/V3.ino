/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#define NUM_SERVOS 8

#include "poses.h"
#include "myservo.h"
#include "alphabet.h"
#include "helloworld.h"

MyServo fingers[NUM_SERVOS];

long lastTime = 0;

Pose *activePose = 0; 
Stage *activeStage = 0;

const int TIMEOUT = 4000;

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

void activatePose(Pose *pose){
  for (int i = 0; i < NUM_SERVOS; i++){
    fingers[i].write(pose->positions[i]);
  }
}

void handleSerial(){
  while (Serial.available() > 0){
    byte b = Serial.read();
    int id = -1;

    if (b == 'o'){
      activePose = &pOPEN;
    }
    else if (b == 'c'){
      activePose = &pCLOSED;
    }
    else if (b == 'g'){
      activePose = &pGUN;
    }else{
      continue;
    }

    activatePose(activePose);
    lastTime = millis();
  }
}

void activateStage(Stage *stage){
  activatePose(stage->pose);
}

void loop() {
  handleSerial();
  
  int t = millis() - lastTime;
  //lastTime = millis();

  if (t > TIMEOUT){
    activePose = &pOPEN;
  }
  if (activePose){  
    activatePose(activePose);
  }
  else if (activeStage){
    activateStage(activeStage);

    if (t > activeStage->holdDuration * 1000){
      // Stage is done
      if (activeStage->successor){
        activeStage = activeStage->successor;
      } else {
        activeStage = 0;
      }
    }
  }else{
    activePose = &pOPEN;
  }

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

