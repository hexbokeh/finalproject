void calculateMIDI()
{
  for (int j = 0; j < 5; j++)
  {
    midiValues[j] = map(potMatrix[currentStep][j], 0, 255, 24, 108);
  }
}

void txMIDI()
{
  calculateMIDI();

}

