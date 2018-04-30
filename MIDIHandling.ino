void calculateMIDI()
{
  for (int j = 0; j < 5; j++)
  {
    lastMIDI[j] = currentMIDI[j];
    currentMIDI[j] = map(potMatrix[currentStep][j], 0, 255, 24, 108);
  }
}

void txMIDI()
{
  calculateMIDI();

  if (lastMIDI[0] != currentMIDI[0])
    //  if (lastStep != currentStep)
  {
    // turn off previous note
    usbMIDI.sendNoteOff(lastMIDI[0], 0, 1);

    // control change
    usbMIDI.sendControlChange(10, currentMIDI[2], 1);

    // turn on next note
    usbMIDI.sendNoteOn(currentMIDI[0], 100, 1);
  }

}


void myNoteOn(byte channel, byte note, byte velocity)
{
  //Serial.println("successful on");
  digitalWrite(rowPowerPins[currentStep], HIGH);
  digitalWrite(ledPins[currentStep], HIGH);

  readPotValues();
  transmitSerial();


  // debug
  
}

void myNoteOff(byte channel, byte note, byte velocity)
{
  digitalWrite(rowPowerPins[currentStep], LOW);
  digitalWrite(ledPins[currentStep], LOW);
  currentStep ++;
  currentStep %= 4;
  
  // debug
  //Serial.println("successful off");
}


//void myControlChange(byte channel, byte control, byte value)


