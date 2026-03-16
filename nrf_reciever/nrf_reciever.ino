#include "movement.h"

//classs--Object
Movement movement;

void setup() {
  Serial.begin (9600);
  pinMode(left_wheels, OUTPUT);
  pinMode(right_wheels, OUTPUT);
  move.dependencies(latchPin, clockPin, dataPin);
  
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.openReadingPipe(1, address);
  radio.startListening();
}

void loop() 
{
  /*if (radio.available())
  {*/
    movement.run();
  /*}else
    {
        analogWrite (right_wheels, 0);
        analogWrite(left_wheels, 0);
    }*/
}
