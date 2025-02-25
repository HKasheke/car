#ifndef MOVEMENT_H
#define MOVEMENT_H

#define STAY  0
#define FORWARD 1
#define BACKWARD 2
#define RIGHT 3
#define LEFT 4

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
public:
    void Dependencies(int latchPin, int clockPin, int dataPin);
    virtual void Go();
};

class Forward: public Movement {
public:
    void Go();
};

class Backward: public Movement {
public:    
    void Go();
};

class Right: public Movement {
public:
    void Go();
};

class Left: public Movement {
public:
    void Go();
};


#endif
