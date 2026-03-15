#ifndef CAR_H
#define CAR_H

class Car{
private:
  const unsigned short int _STAY = 0;
  const unsigned short int _FORWARD = 1;
  const unsigned short int _BACKWARD = 2;
  const unsigned short int _RIGHT = 3;
  const unsigned short int _LEFT = 4;
  
public:
  void dependencies(int latchPin, int clockPin, int dataPin);
  void movement();
  void stay();
  void forward();
  void backward();
  void left();
  void right();

};

#endif
