#include "car.h"

enum direction {
  _STAY,
  _FORWARD,
  _BACKWARD,
  _LEFT,
  _RIGHT
 };

Car::Car() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  //ground latchPin and hold low for as long as you are transmitting
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, LSBFIRST, direct[_STAY]);
  //return the latch pin high to signal chip that it
  //no longer needs to listen for information
  digitalWrite(latchPin, 1);
}

void Car::stay() {
  //ground latchPin and hold low for as long as you are transmitting
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, LSBFIRST, direct[_STAY]);
  //return the latch pin high to signal chip that it
  //no longer needs to listen for information
  digitalWrite(latchPin, 1);
}

void Car::forward() {
  //ground latchPin and hold low for as long as you are transmitting
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, LSBFIRST, direct[_FORWARD]);
  //return the latch pin high to signal chip that it
  //no longer needs to listen for information
  digitalWrite(latchPin, 1);
}

void Car::backward(){
  //Shift Register code two change the Hbridge for dynamic movement
  //ground latchPin and hold low for as long as you are transmitting
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, LSBFIRST, direct[_BACKWARD]);
  //return the latch pin high to signal chip that it
  //no longer needs to listen for information
  digitalWrite(latchPin, 1);
}

void Car::left() {
    //Shift Register code two change the Hbridge for dynamic movement
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, LSBFIRST, direct[_LEFT]);
    //return the latch pin high to signal chip that it
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
}

void Car::right() {
  //ground latchPin and hold low for as long as you are transmitting
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, LSBFIRST, direct[_RIGHT]);
  //return the latch pin high to signal chip that it
  //no longer needs to listen for information
  digitalWrite(latchPin, 1);
}

