#include <nRF24L01.h>
#include <RF24.h>
#include "movement.h"

void Movement::dependencies(int latchPin, int clockPin, int dataPin){
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
  
Movement::Movement() {
  //ground latchPin and hold low for as long as you are transmitting
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, LSBFIRST, direct[_STAY]);
  //return the latch pin high to signal chip that it
  //no longer needs to listen for information
  digitalWrite(latchPin, 1);
}

void Movement::stay() {
  //ground latchPin and hold low for as long as you are transmitting
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, LSBFIRST, direct[_STAY]);
  //return the latch pin high to signal chip that it
  //no longer needs to listen for information
  digitalWrite(latchPin, 1);
}

void Movement::forward() {
  //ground latchPin and hold low for as long as you are transmitting
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, LSBFIRST, direct[_FORWARD]);
  //return the latch pin high to signal chip that it
  //no longer needs to listen for information
  digitalWrite(latchPin, 1);
}

void Movement::backward(){
  //Shift Register code two change the Hbridge for dynamic movement
  //ground latchPin and hold low for as long as you are transmitting
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, LSBFIRST, direct[_BACKWARD]);
  //return the latch pin high to signal chip that it
  //no longer needs to listen for information
  digitalWrite(latchPin, 1);
}

void Movement::right() {
  //ground latchPin and hold low for as long as you are transmitting
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, LSBFIRST, direct[_RIGHT]);
  //return the latch pin high to signal chip that it
  //no longer needs to listen for information
  digitalWrite(latchPin, 1);
}

void Movement::left() {
    //Shift Register code two change the Hbridge for dynamic movement
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, LSBFIRST, direct[_LEFT]);
    //return the latch pin high to signal chip that it
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
}

void Movement::movement ()
{

  if (y_axis > 121){
    dirction = _FORWARD;
    forward();  
    } 
    else if (y_axis < 121){
        dirction = _BACKWARD;
      backward();    
    }else if ((y_axis == 121)&&(x_axis == 125)){
        dirction = _STAY;
        stay();
        }

  if (x_axis < 125)
  {
    dirction = _RIGHT;
    right();
  } 
    else if (x_axis > 125)
    {
      dirction = _LEFT;
      left();
    }else if((y_axis == 121)&&(x_axis == 125)){
        dirction = _STAY;
        stay();
        }
        
  switch (dirction)
  {
    case _STAY:

        analogWrite (right_wheels, 0);
        analogWrite(left_wheels, 0);      
        
        break;
        
    case _FORWARD:

        while (y_axis > 121)
        {
          
          right_speed = map(y_axis, 121, 255, 0, 255);
          left_speed = right_speed;
          
          analogWrite (right_wheels, right_speed);
          analogWrite(left_wheels, left_speed);

          parseData();
        }
        break;
        
    case _BACKWARD:

        while (y_axis < 121)
        {
          right_speed = map(y_axis, 121, 0, 0, 255);
          left_speed = right_speed;
          
          analogWrite (right_wheels, right_speed);
          analogWrite(left_wheels, left_speed); 

          parseData();
        }
        break;

    case _RIGHT:

        while (x_axis < 125)
        {
          right_speed = map(x_axis, 125, 0, 0, 255);
          left_speed = right_speed;
          
          analogWrite (right_wheels, right_speed);
          analogWrite(left_wheels, left_speed);

          parseData();
        }
        break;

    case _LEFT:

        while (x_axis > 125)
        {
          right_speed = map(x_axis, 125, 255, 0, 255);
          left_speed = right_speed;
          
          analogWrite (right_wheels, right_speed);
          analogWrite(left_wheels, left_speed);
          
          parseData();          
        }
        break;
  }  
}

void parseData()
{
int len =0;
if (radio.available())
  {  
    while (radio.available())
    {
      //Serial.print ("Receiving");
      len = radio.getDynamicPayloadSize();
      radio.read(&tempChars, len);
      Serial.print (tempChars);
    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,"<,");      // get the first part - the string between '<' and ','
    x_axis = atoi(strtokIndx); // convert this part to an integer puts in x_axis

    strtokIndx = strtok(NULL, ",>"); // this continues where the previous call left off from ',' to '>'
    y_axis = atoi(strtokIndx);     // convert this part to an integer puts in y_axis
    
    }
  }
}
