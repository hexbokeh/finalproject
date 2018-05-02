// Use external (incoming) MIDI values for control
void inputMode()
{
  usbMIDI.read(); // call incoming MIDI-on event handler (myNoteOn())

  // Not yet used; for later implementation.
  // usbMIDI.setHandleControlChange(myControlChange);
}

// Use internal pot values for MIDI control.
void outputMode()
{

  // Turning on power. to LEDs and pots.
  digitalWrite(rowPowerPins[currentStep], HIGH);
  digitalWrite(ledPins[currentStep], HIGH);

  // Read pot values for the row.
  // If you make this a double for-loop,
  // you will always be reading zero values on the other rows!
  readPotValues();

  //Serial data to be sent to Processing (or elsewhere).
  // Transmit MIDI to DAW or other compatible instrument.
  //******** Where the magic happens.
  transmitSerial();
  txMIDI();

  stepLength = map(potMatrix[currentStep][4], 20, 255, 1, 750); // 20 seems to be as low as they go.
  delay(stepLength);

  // Turning off power to LEDs and step/column of pots.
  digitalWrite(rowPowerPins[currentStep], LOW);
  digitalWrite(ledPins[currentStep], LOW);

  // Iterate step (within range 0-3).
  currentStep ++;
  currentStep %= 4;
}

// Analog-read the pot values for the current powered-up step.
void readPotValues()
{
  for (int j = 0; j < 5; j++)
  {
    potMatrix[currentStep][j] = 1023 - analogRead(potMatrixPins[currentStep][j]);
    // map them from 10-bit values to 8-bit values (bytes).
    potMatrix[currentStep][j] = map(potMatrix[currentStep][j], 0, 1023, 0, 255);
  }
}

