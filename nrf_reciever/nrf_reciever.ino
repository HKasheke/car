#include <nRF24L01.h>
#include <RF24.h>
#include "movement.h"

RF24 radio(7, 8);

const byte MaxDataChars = 32;
const byte address[6] = "00001";

const int left_wheels = 9;
const int right_wheels = 10;

int X_axis = 0;
int Y_axis = 0;
int dirction = 0;
int L_speed = 0;
int R_speed = 0;

char tempChars[MaxDataChars];

//classs--Object
Movement stay;
Forward forward;
Backward backward;
Left left;
Right right;

void setup() {
  Serial.begin (9600);
  pinMode(left_wheels, OUTPUT);
  pinMode(right_wheels, OUTPUT);
  stay.Dependencies(latchPin, clockPin, dataPin);
  
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  //radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, address);
  radio.startListening();
  stay.Go(); 
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
