#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);

const byte address[6] = "00001";
const byte MaxDataChars = 9;

const char startMarker [2] = {'<'};
const char comma [2]= {','};
const char endMarker[2] = {'>'};

int raw_X_axis = 0;
int raw_Y_axis = 0;
int X_axis = 8;
int Y_axis = 7;

char Xaxis [4];
char Yaxis [4];

void setup() {
  Serial.begin (9600);
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.openWritingPipe(address);
}

void loop() {
  char transmitChars [MaxDataChars] = {'\0'};
  //Analog stick values are mapped to be able to send
  raw_X_axis = analogRead(A0);
  X_axis = map(raw_X_axis, 0, 1023, 0, 255);
  delay(2);
  raw_Y_axis = analogRead(A1);
  Y_axis = map(raw_Y_axis, 0, 1023, 0, 255);
  delay(2);
  itoa(X_axis, Xaxis, 10); //turns the integer values into arrays
  delay(2);
  itoa(Y_axis, Yaxis, 10);

  //Bellow puts the values into one array called transmitChars
  strcat(transmitChars,startMarker);
  strcat(transmitChars, Xaxis);
  strcat(transmitChars,comma);
  strcat(transmitChars,Yaxis);
  strcat(transmitChars,endMarker);

  radio.write(&transmitChars, sizeof(transmitChars)); //Sends the array
  delay(2000);
  
}
