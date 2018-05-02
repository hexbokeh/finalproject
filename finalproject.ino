#include <MIDI.h> // invoking MIDI library.
// Serial included by default, as well.

int stepLength = 250; // default, in milliseconds.
int ledPins[4] = {0, 1, 2, 3}; // not including ground.
int currentStep; // 0-3 (4 steps)
int lastStep; // for comparison purposes

int switchPin = 28; // for changing modes

// specific analog reading row pins
int potMatrixPins[4][5] =
{
  {A0, A1, A2, A3, A4},
  {A5, A6, A7, A8, A9},
  {A13, A14, A15, A16, A17},
  {A18, A19, A20, A21, A22},
}; // all the attachments of pots to the analog pins.

int potMatrix[4][5]; // stored values from analogRead()s

int rowPowerPins[4] = {12, 11, 10, 9}; // not including ground

int currentMIDI[5]; // outputed/read MIDI per step
int lastMIDI[5]; // for comparison purposes

void setup() // configuring the Teensy for proper functionality.
{

  pinMode(switchPin, INPUT); // Sets up pin that changes between inputMode() and outputMode()

  for (int i = 0; i < 4; i++) // Setting up pins for lighting up LEDs
  {
    pinMode(ledPins[i], OUTPUT);
  }

  for (int i = 0; i < 4; i++) // Setting up pins for powering columns (steps) of pots.
  {
    pinMode(rowPowerPins[i], OUTPUT);
  }

  Serial.begin(115200); // Establishing baud rate for Serial
  usbMIDI.setHandleNoteOn(myNoteOn); // Establishing which function is called (myNoteOn()) when a note-on MIDI signal is detected
  usbMIDI.setHandleNoteOff(myNoteOff); // Establishing which function is called (myNoteOff()) when a note-off MIDI signal is detected.
}

void loop() // continuously runs during program execution
{
  if (digitalRead(switchPin)) // If the switch is set to on/HIGH, go into input mode.
  {
    inputMode();
  }

  else // If the switch is set to off/LOW, go into output mode.
  {
    outputMode();
  }
}


// six values: step #, pot values 1-5.
// The first should correspond to the step (in this case, the row of the array).
// The others should correspond to the analog read values for the 5 respective pots.
void transmitSerial()
{
  Serial.write(currentStep); // Transmission of first value
  for (int i = 0; i < 5; i++) // it's 5, not 6!!!
  {
    Serial.write(potMatrix[currentStep][i]); // Transmitting pot values.
  }
}

