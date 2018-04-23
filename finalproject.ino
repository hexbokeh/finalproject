#include <MIDI.h>
// Serial included by default, as well.

int stepLength = 250; // default, in milliseconds.
int ledPins[4] = {0, 1, 2, 3}; // not including ground.
int currentStep; // 0-3 (4 steps)

// specific analog reading row pins
int potMatrixPins[4][5] =
{
  {A4, A3, A2, A1, A0},
  {A9, A8, A7, A6, A5},
  {A13, A14, A15, A16, A17},
  {A18, A19, A20, A21, A22},
};// possibly reverse orders within each row?????

int potMatrix[4][5];

int rowPowerPins[4] = {12, 11, 10, 9}; // not including ground

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
  //  Serial.print("current power pin: ");
  //  Serial.print(rowPowerPins[currentStep]);
  Serial.print(" currentStep = ");
  Serial.print(currentStep);
  Serial.print(" ");

  // turning on power.
  digitalWrite(rowPowerPins[currentStep], HIGH);
  digitalWrite(ledPins[currentStep], HIGH);

  //read pot values for the row.
  // If you make this a double for loop,
  // you will always be reading zero values on the other rows!
  for (int j = 0; j < 5; j++)
  {
    potMatrix[currentStep][j] = analogRead(potMatrixPins[currentStep][j]);
  }

  // debug
  //  for (int j = 0; j < 5; j++)
  //  {
  //    Serial.print("pot # ");
  //    Serial.print(j);
  //    Serial.print(" = ");
  //    Serial.print(potMatrix[currentStep][j]);
  //    Serial.print(" ");
  //  }

  Serial.println(1023 - analogRead(potMatrixPins[currentStep][4]));
  Serial.println();

  // debug
  //  if((currentStep == 3 || currentStep == 4) && digitalRead(rowPowerPins[currentStep]))
  //  {
  //    Serial.println("It's working!");
  //  }

  delay(stepLength);

  // turning off power.
  digitalWrite(rowPowerPins[currentStep], LOW);
  digitalWrite(ledPins[currentStep], LOW);
  currentStep ++;
  currentStep %= 4;
}
