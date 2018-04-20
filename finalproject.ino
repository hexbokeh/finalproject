#include <MIDI.h>


int stepLength = 250; // default, in milliseconds.
int ledPins[4] = {0, 1, 2, 3};
int currentStep; // 0-3 (4 steps)
int potMatrix[4][5];

int stepDuration = 100;
int rowPowerPins[4] = {9, 10, 11, 12};


void setup()
{
  Serial.begin(9600);

  for (int i = 0; i < 4; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }

  for (int i = 0; i < 4; i++)
  {
    pinMode(rowPowerPins[i], OUTPUT);
  }
}

void loop()
{

  // debug
  Serial.print("current power pin: ");
  Serial.print(rowPowerPins[currentStep]);
  Serial.print(" currentStep = ");
  Serial.println(currentStep);

  // turning on power.
  digitalWrite(rowPowerPins[currentStep], HIGH);

  delay(stepDuration);

  digitalWrite(rowPowerPins[currentStep], LOW);
  currentStep ++;
  currentStep %= 4;
}
