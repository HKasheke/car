#include <nRF24L01.h>
#include <RF24.h>
#include "movement.h"

RF24 radio(7, 8);

const byte MaxDataChars = 32;
const byte address[6] = "00001";

constexpr int left_wheels = 9;
constexpr int right_wheels = 10;

int X_axis = 0;
int Y_axis = 0;
int dirction = 0;
int L_speed = 0;
int R_speed = 0;

char tempChars[MaxDataChars];

//classs--Object
Movement movement;


void setup() {
  Serial.begin (9600);
  pinMode(left_wheels, OUTPUT);
  pinMode(right_wheels, OUTPUT);
  movement.Dependencies(latchPin, clockPin, dataPin);
  
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.openReadingPipe(1, address);
  radio.startListening();
  movement.stay(); 
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
