void inputMode()
{
  digitalWrite(rowPowerPins[currentStep], HIGH);
  digitalWrite(ledPins[currentStep], HIGH);

  readPotValues();

  transmitSerial();

  digitalWrite(rowPowerPins[currentStep], LOW);
  digitalWrite(ledPins[currentStep], LOW);
  currentStep ++;
  currentStep %= 4;
}

void inputSetup()
{
  Serial.begin(31250);
  usbMIDI.setHandleNoteOn(myNoteOn);
  usbMIDI.setHandleNoteOff(myNoteOff);
  usbMIDI.setHandleControlChange(myControlChange);
}


void outputMode()
{
  // six values: step #, pot values 1-5.
  // variables: a,b,c,d,e,f.
  // a should correspond to the step (in this case, the row of the array)

  // debug
  //  Serial.print("current power pin: ");
  //  Serial.print(rowPowerPins[currentStep]);
  //    Serial.print(" currentStep = ");
  //    Serial.print(currentStep);
  //    Serial.print(" ");

  // turning on power.
  digitalWrite(rowPowerPins[currentStep], HIGH);
  digitalWrite(ledPins[currentStep], HIGH);

  //read pot values for the row.
  // If you make this a double for loop,
  // you will always be reading zero values on the other rows!
  readPotValues();


  // debug
  //  if (currentStep == 2)
  //  {
  //    for (int j = 0; j < 5; j++)
  //    {
  //      Serial.print("pot # ");
  //      Serial.print(j);
  //      Serial.print(" = ");
  //      Serial.print(potMatrix[currentStep][j]);
  //      Serial.print(" ");
  //    }
  //  }
  //
  //  //  Serial.println(potMatrix[currentStep][4]);
  //  Serial.println();

  // Serial send!!!
  // currentStep and pot values transmitted all at once.


  transmitSerial(); //******** Where the magic happens.
  txMIDI();

  // debug
  //  if((currentStep == 3 || currentStep == 4) && digitalRead(rowPowerPins[currentStep]))
  //  {
  //    Serial.println("It's working!");
  //  }

  stepLength = map(potMatrix[currentStep][4], 20, 255, 1, 750); // 20 seems to be as low as they go.
  delay(stepLength);

  // turning off power.
  digitalWrite(rowPowerPins[currentStep], LOW);
  digitalWrite(ledPins[currentStep], LOW);
  currentStep ++;
  currentStep %= 4;
  // debug
  // currentStep = 0;
}

void readPotValues()
{
  for (int j = 0; j < 5; j++)
  {
    potMatrix[currentStep][j] = 1023 - analogRead(potMatrixPins[currentStep][j]);
    potMatrix[currentStep][j] = map(potMatrix[currentStep][j], 0, 1023, 0, 255);
  }
}

