#ifndef MOVEMENT_H
#define MOVEMENT_H

//Pin connected to ST_CP of 74HC595 Pin 12
const int latchPin = 2;
//Pin connected to SH_CP of 74HC595 Pin 11
const int clockPin = 4;
////Pin connected to DS of 74HC595 Pin 14
const int dataPin = 5;

//Used for double H-Bridge being controller by a serial to parallel chip
const byte direct[5] = {
  B00001010,  //Default/Stay
  B00001010,  //Forward
  B00000101,  //Backwards
  B00100110,  //Left
  B00001001}; //Right

void movement ();
void parseData();

class Movement{
private:
  constexpr STAY  0;
  constexpr FORWARD 1;
  constexpr BACKWARD 2;
  constexpr RIGHT 3;
  constexpr LEFT 4;

  
public:
  void Dependencies(int latchPin, int clockPin, int dataPin);
  void stay();
  void forward();
  void backward();
  void right();
  void left();
};

#endif
