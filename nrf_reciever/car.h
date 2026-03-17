#ifndef CAR_H
#define CAR_H

class Car{
private:
  //Pin connected to ST_CP of 74HC595 Pin 12
  constexpr unsigned int latchPin = 2;
  //Pin connected to SH_CP of 74HC595 Pin 11
  constexpr unsigned int clockPin = 4;
  ////Pin connected to DS of 74HC595 Pin 14
  constexpr unsigned int dataPin = 5;

  //Used for double H-Bridge being controller by a serial to parallel chip
  const byte direct[5] = {
  B00001010,  //Default/Stay
  B00001010,  //Forward
  B00000101,  //Backwards
  B00100110,  //Left
  B00001001}; //Right
  
public:
  void stay();
  void forward();
  void backward();
  void left();
  void right();
};

#endif
