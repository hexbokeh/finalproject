#include <MIDI.h>


int ledPin = 13;
int currentStep; // 0-3 (4 steps)
int potMatrix[4][5];

int stepDuration = 100;
int rowPowerPins[4] = {3,4,5,6};


void setup() 
{
  pinMode(ledPin, OUTPUT);
}

void loop() 
{
  digitalWrite(ledPin, HIGH);
}
