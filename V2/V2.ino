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
String readString;

int pos = 0;    // variable to store the servo position
long startTime = 0;

const int PERIOD = 4000;

void setup() {
  int fingerNum = 0;
  int notCalib = 1;
  
  Serial.begin(9600);
  delay(2);
  
  for (fingerNum = 0; fingerNum <= 3; fingerNum++){
    calibration(fingerNum, notCalib);
  }
  
//  fingers[0].attach(2);
//  fingers[0].calibrate(90,10);
//
//  fingers[1].attach(3);
//  fingers[1].calibrate(90,10);
//
//  fingers[2].attach(4);
//  fingers[2].calibrate(90,10);
//
//  fingers[3].attach(5);
//  fingers[3].calibrate(90,10);

  startTime = millis();

  activeServo = &fingers[0];
}

void calibration(int motor_id, int notCalib ){
  Serial.print("Calibrating motor ");
  Serial.println(motor_id);
  Serial.println(notCalib);
//  Serial.println(Serial.available());
  
  fingers[motor_id].attach(motor_id+2); //Checks motors sequentially
  
  while (Serial.available() && (notCalib == 1)) {
    char userInput = Serial.read();  //gets one byte from serial buffer
    readString += userInput; //makes the string readString
    delay(2);  //slow looping to allow buffer to fill with next character

    if (readString.length() >0) {
      if(readString.indexOf('x') >0) { 
        pos = readString.toInt();
      }
    
      if(readString =="k"){
        (pos=pos-1); //use larger numbers for larger increments
        if(pos<0) (pos=0); //prevent negative number
        Serial.println(pos);
      }
      else if (readString =="l"){
        (pos=pos+1);
        Serial.println(pos);
      }
      else if (readString =="o"){
        int minCalib = pos;
        Serial.println("Minimum Calibration is");
        Serial.print(minCalib);
      }
      else if (readString =="p"){
        int maxCalib = pos;
        Serial.println("Maximum Calibration is");
        Serial.print(maxCalib);
      }
      else if (readString =="q"){
        notCalib = 0;
        Serial.println("Exiting calibration mode");
        break;
      }
      else{
        Serial.println("Hoi");
      }
    
      if(pos >= 400) //determine servo write method
      {
        Serial.println(pos);
        fingers[motor_id].write(pos);
      }
      else
      {   
        Serial.println(pos);
        fingers[motor_id].write(pos); 
      }
    }
    else{
        Serial.println("No input");
    }
  readString=""; //empty for next input
  }

  Serial.println("No serial input");
  
  fingers[motor_id].calibrate(90,10);
  
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
//  Serial.println(pos);
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

