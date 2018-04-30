#include <MIDI.h>
// Serial included by default, as well.

int stepLength = 250; // default, in milliseconds.
int ledPins[4] = {0, 1, 2, 3}; // not including ground.
int currentStep; // 0-3 (4 steps)
int lastStep;

// specific analog reading row pins
int potMatrixPins[4][5] =
{
  {A0, A1, A2, A3, A4},
  {A5, A6, A7, A8, A9},
  {A13, A14, A15, A16, A17},
  {A18, A19, A20, A21, A22},
};// possibly reverse orders within each row?????

int potMatrix[4][5];

int rowPowerPins[4] = {12, 11, 10, 9}; // not including ground

int currentMIDI[5];
int lastMIDI[5];

int modeState = 1;

void setup()
{


  for (int i = 0; i < 4; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }

  for (int i = 0; i < 4; i++)
  {
    pinMode(rowPowerPins[i], OUTPUT);
  }



  //Serial.begin(9600);

  //Serial.begin(31250);

  // needs debugging

  Serial.begin(115200);
  usbMIDI.setHandleNoteOn(myNoteOn);
  usbMIDI.setHandleNoteOff(myNoteOff);

  //  Serial.println("Input or output mode? (type i or o)");
  //  while (Serial.available() == 0) {} // wait for user input.
  //  char c = Serial.read();
  //  if (c == 'i')
  //  {
  //    modeState = 1;
  //
  //    // debug
  //    Serial.println("Success, inputMode activated");
  //    //inputMode();
  //  }
  //  if (c == 'o')
  //  {
  //    modeState = 2;
  //    //outputMode();
  //  }
}

void loop()
{
  if (modeState == 1)
  {

    inputMode();
  }

  if (modeState == 2) outputMode();
}


// six values: step #, pot values 1-5.
// variables: a,b,c,d,e,f.
// a should correspond to the step (in this case, the row of the array)
void transmitSerial()
{
  Serial.write(currentStep);
  for (int i = 0; i < 5; i++) // it's 5, not 6!!!
  {
    Serial.write(potMatrix[currentStep][i]);
  }
}

