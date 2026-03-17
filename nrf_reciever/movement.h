#ifndef MOVEMENT_H
#define MOVEMENT_H
#include <nRF24L01.h>
#include <RF24.h>
#include "car.h"

RF24 radio(7, 8);

class Movement{
private:
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

  void parseData();
  
public:
  void run();
};

#endif
