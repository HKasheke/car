#include <nRF24L01.h>
#include <RF24.h>
#include "movement.h"

void Movement::Dependencies(int latchPin, int clockPin, int dataPin){
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
  
void Movement::Go() {
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, LSBFIRST, direct[STAY]);
    //return the latch pin high to signal chip that it
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
}

void Forward::Go() {
  //ground latchPin and hold low for as long as you are transmitting
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, LSBFIRST, direct[FORWARD]);
  //return the latch pin high to signal chip that it
  //no longer needs to listen for information
  digitalWrite(latchPin, 1);
}

void Backward::Go(){
  //Shift Register code two change the Hbridge for dynamic movement
  //ground latchPin and hold low for as long as you are transmitting
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, LSBFIRST, direct[LEFT]);
  //return the latch pin high to signal chip that it
  //no longer needs to listen for information
  digitalWrite(latchPin, 1);
}

void Right::Go() {
  //ground latchPin and hold low for as long as you are transmitting
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, LSBFIRST, direct[RIGHT]);
  //return the latch pin high to signal chip that it
  //no longer needs to listen for information
  digitalWrite(latchPin, 1);
}

void Left::Go() {
    //Shift Register code two change the Hbridge for dynamic movement
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, LSBFIRST, direct[LEFT]);
    //return the latch pin high to signal chip that it
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
}

void movement ()
{

  if (Y_axis > 121){
    dirction = FORWARD;
    forward.Go();  
    } 
    else if (Y_axis < 121){
        dirction = BACKWARD;
      backward.Go();    
    }else if ((Y_axis == 121)&&(X_axis == 125)){
        dirction = STAY;
        stay.Go();
        }

  if (X_axis < 125)
  {
    dirction = RIGHT;
    right.Go();
  } 
    else if (X_axis > 125)
    {
      dirction = LEFT;
      left.Go();
    }else if((Y_axis == 121)&&(X_axis == 125)){
        dirction = STAY;
        stay.Go();
        }
        
  switch (dirction)
  {
    case STAY:

        analogWrite (right_wheels, 0);
        analogWrite(left_wheels, 0);      
        
        break;
        
    case FORWARD:

        while (Y_axis > 121)
        {
          
          R_speed = map(Y_axis, 121, 255, 0, 255);
          L_speed = R_speed;
          
          analogWrite (right_wheels, R_speed);
          analogWrite(left_wheels, L_speed);

          parseData();
        }
        break;
        
    case BACKWARD:

        while (Y_axis < 121)
        {
          R_speed = map(Y_axis, 121, 0, 0, 255);
          L_speed = R_speed;
          
          analogWrite (right_wheels, R_speed);
          analogWrite(left_wheels, L_speed); 

          parseData();
        }
        break;

    case RIGHT:

        while (X_axis < 125)
        {
          R_speed = map(X_axis, 125, 0, 0, 255);
          L_speed = R_speed;
          
          analogWrite (right_wheels, R_speed);
          analogWrite(left_wheels, L_speed);

          parseData();
        }
        break;

    case LEFT:

        while (X_axis > 125)
        {
          R_speed = map(X_axis, 125, 255, 0, 255);
          L_speed = R_speed;
          
          analogWrite (right_wheels, R_speed);
          analogWrite(left_wheels, L_speed);
          
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
    X_axis = atoi(strtokIndx); // convert this part to an integer puts in X_axis

    strtokIndx = strtok(NULL, ",>"); // this continues where the previous call left off from ',' to '>'
    Y_axis = atoi(strtokIndx);     // convert this part to an integer puts in Y_axis
    
    }
  }
}