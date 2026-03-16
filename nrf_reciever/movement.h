#ifndef MOVEMENT_H
#define MOVEMENT_H
#include <nRF24L01.h>
#include <RF24.h>
#include "car.h"

RF24 radio(7, 8);

const byte MaxDataChars = 32;
const byte address[6] = "00001";

constexpr unsigned short int left_wheels = 9;
constexpr unsigned short int right_wheels = 10;

int x_axis = 0;
int y_axis = 0;
int dirction = 0;
int left_speed = 0;
int right_speed = 0;

char tempChars[MaxDataChars];

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

class Movement{
private:
  const unsigned short int _STAY = 0;
  const unsigned short int _FORWARD = 1;
  const unsigned short int _BACKWARD = 2;
  const unsigned short int _RIGHT = 3;
  const unsigned short int _LEFT = 4;
  void parseData();
  
public:
  void dependencies(int latchPin, int clockPin, int dataPin);
  void run();
};

#endif
