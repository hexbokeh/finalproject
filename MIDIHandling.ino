// mapping range of Serial values to MIDI note values.
void calculateMIDI()
{
  for (int j = 0; j < 5; j++)
  {
    lastMIDI[j] = currentMIDI[j]; // Priming for later comparisons.
    currentMIDI[j] = map(potMatrix[currentStep][j], 0, 255, 24, 108); // Conversion from Serial to MIDI.
  }
}

void txMIDI()
{
  // We need to send out usable MIDI values to other places,
  // so we first have to "convert" from Serial values to MIDI values.
  calculateMIDI();

  if (lastMIDI[0] != currentMIDI[0]) // detection of change in MIDI note
  {
    // Turn off previous note
    usbMIDI.sendNoteOff(lastMIDI[0], 0, 1);

    // Control change
    usbMIDI.sendControlChange(10, currentMIDI[2], 1);

    // Turn on next note
    usbMIDI.sendNoteOn(currentMIDI[0], 100, 1);
  }
}

// Event handler for when incoming MIDI note detected
void myNoteOn(byte channel, byte note, byte velocity)
{
  // turn on both LED indicator and power to column of pots.
  digitalWrite(rowPowerPins[currentStep], HIGH);
  digitalWrite(ledPins[currentStep], HIGH);

  // Once pots are powered, read analog values.
  readPotValues();
  // Send them out (to processing or elsewhere).
  transmitSerial();
}

// Event handler for when incoming MIDI off signal detected
void myNoteOff(byte channel, byte note, byte velocity)
{
  // Cut power to LED indicator and respective column/step of pots.
  digitalWrite(rowPowerPins[currentStep], LOW);
  digitalWrite(ledPins[currentStep], LOW);

  // increment currentStep value (remain within 0-3)
  currentStep ++;
  currentStep %= 4;
}

// Not yet used; for later implementation.
// Void myControlChange(byte channel, byte control, byte value)
