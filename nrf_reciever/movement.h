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

const byte direct[5] = {
  B00001010,  //Default/Stay
  B00001010,  //Forward
  B00000101,  //Backwards
  B00100110,  //Left
  B00001001}; //Right

class Movement{
public:
    void Dependencies(int latchPin, int clockPin, int dataPin)
    {
      pinMode(latchPin, OUTPUT);
      pinMode(clockPin, OUTPUT);
      pinMode(dataPin, OUTPUT);
    }
  
    virtual void Go() 
    {
        //ground latchPin and hold low for as long as you are transmitting
        digitalWrite(latchPin, 0);
        shiftOut(dataPin, clockPin, LSBFIRST, direct[STAY]);
        //return the latch pin high to signal chip that it
        //no longer needs to listen for information
        digitalWrite(latchPin, 1);
    }
};

class Forward: public Movement {
public:
    void Go()
    {
        //ground latchPin and hold low for as long as you are transmitting
        digitalWrite(latchPin, 0);
        shiftOut(dataPin, clockPin, LSBFIRST, direct[FORWARD]);
        //return the latch pin high to signal chip that it
        //no longer needs to listen for information
        digitalWrite(latchPin, 1);
    }
};

class Backward: public Movement {
public:    
    void Go() 
    {
        //ground latchPin and hold low for as long as you are transmitting
        digitalWrite(latchPin, 0);
        shiftOut(dataPin, clockPin, LSBFIRST, direct[BACKWARD]);
        //return the latch pin high to signal chip that it
        //no longer needs to listen for information
        digitalWrite(latchPin, 1);
    }
};

class Right: public Movement {
public:
    void Go() 
    {
        //ground latchPin and hold low for as long as you are transmitting
        digitalWrite(latchPin, 0);
        shiftOut(dataPin, clockPin, LSBFIRST, direct[RIGHT]);
        //return the latch pin high to signal chip that it
        //no longer needs to listen for information
        digitalWrite(latchPin, 1);
    }
};

class Left: public Movement {
public:
    void Go() 
    {
        //Shift Register code two change the Hbridge for dynamic movement
        //ground latchPin and hold low for as long as you are transmitting
        digitalWrite(latchPin, 0);
        shiftOut(dataPin, clockPin, LSBFIRST, direct[LEFT]);
        //return the latch pin high to signal chip that it
        //no longer needs to listen for information
        digitalWrite(latchPin, 1);
    }
};
