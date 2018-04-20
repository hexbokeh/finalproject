#include <MIDI.h>
// Serial included by default, as well.

int stepLength = 250; // default, in milliseconds.
int ledPins[4] = {0, 1, 2, 3}; // not including ground.
int currentStep; // 0-3 (4 steps)

int potMatrixPins[4][5] =
{
  {A0, A1, A2, A3, A4},
  {A5, A6, A7, A8, A9},
  {A13, A14, A15, A16, A17},
  {A18, A19, A20, A21, A22},
}

int potMatrix[4][5];

int rowPowerPins[4] = {8, 9, 10, 11}; // not including ground


// specific analog reading row pins



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

  //read pot values for the row.
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      potMatrix[i][j] = analogRead(potMatrixPins[i][j]);
    }
  }

  delay(stepLength);

  // turning off power.
  digitalWrite(rowPowerPins[currentStep], LOW);
  digitalWrite(ledPins[currentStep], LOW);
  currentStep ++;
  currentStep %= 4;
}
