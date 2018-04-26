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
  //  for (int i = 0; i<5; i++)
  //  {
  //
  //  }

  if (lastMIDI[0] != currentMIDI[0])
  {
    // turn off previous note
    usbMIDI.sendNoteOff(lastMIDI[1], 0, 1);
    // turn on next note
    usbMIDI.sendNoteOn(currentMIDI[1], 100, 1);
  }

}

