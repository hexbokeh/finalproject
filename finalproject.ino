#include <MIDI.h>


int stepLength = 250; // default, in milliseconds.
int ledPins[4] = {0, 1, 2, 3}; // not including ground.
int currentStep; // 0-3 (4 steps)
int potMatrix[4][5];
int rowPowerPins[4] = {8, 9, 10, 11}; // not including ground


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

  // six values: step #, pot values 1-5.
  // variables: a,b,c,d,e,f.
  // a should correspond to the step (in this case, the row of the array)

  // debug
  Serial.print("current power pin: ");
  Serial.print(rowPowerPins[currentStep]);
  Serial.print(" currentStep = ");
  Serial.println(currentStep);




  // turning on power.
  digitalWrite(rowPowerPins[currentStep], HIGH);
  digitalWrite(ledPins[currentStep], HIGH);

  delay(stepLength);

  // turning off power.
  digitalWrite(rowPowerPins[currentStep], LOW);
  digitalWrite(ledPins[currentStep], LOW);
  currentStep ++;
  currentStep %= 4;
}
