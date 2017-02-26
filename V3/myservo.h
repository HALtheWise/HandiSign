#include <Servo.h>

class MyServo
{
  public:
    MyServo(){
    }

    void calibrate(int minpos, int maxpos){
      _minpos = minpos;
      _maxpos = maxpos;
    }

    void attach(int pin){
      _pin = pin;
      servo.attach(pin);
    }

    int _pin;
    int _minpos = 0;
    int _maxpos = 0;
    Servo servo;

    void write(float fraction){
      servo.write(_minpos + fraction * (_maxpos - _minpos));
    }

    void update(){
      
    }
  
};

