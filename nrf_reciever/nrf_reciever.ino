#include <nRF24L01.h>
#include <RF24.h>
#include "movement.h"

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

//classs--Object
Movement move;

void setup() {
  Serial.begin (9600);
  pinMode(left_wheels, OUTPUT);
  pinMode(right_wheels, OUTPUT);
  move.dependencies(latchPin, clockPin, dataPin);
  
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.openReadingPipe(1, address);
  radio.startListening();
  //move.stay(); 
}

void loop() 
{
  /*if (radio.available())
  {*/
    parseData();
    movement();
  /*}else
    {
        analogWrite (right_wheels, 0);
        analogWrite(left_wheels, 0);
    }*/
}
