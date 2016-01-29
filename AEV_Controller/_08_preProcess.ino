void preProcess()
{
  //------------------------------------------------------------------------
  // preProcess();
  //
  // Perform battery check and wait for user to start run or connect 
  // with Matlab
  //
  // Input: None
  //
  // Output: None
  //-------------------------------------------------------------------------
  
  // Wait for user to start--------------------------------------------------

  digitalWrite(yellowLedPin,HIGH); // Turn on LED 
  
  while (digitalRead(buttonBypass)==HIGH) // While button is not pressed
  {
    if (establishContact()) // Check for contact with Matlab
    {
      sendArduino2Matlab(); // Send Arduino data to Matlab     
    }
  } 
  //-------------------------------------------------------------------------
  
  // Perform Battery Voltage Check-------------------------------------------

  int bVolts=getSamples(batVoltsPin,100,'d');     // Get voltage counts
  float batVolts=3.0*defRef*(float)bVolts/1024.0; // Compute voltage

  // Catch a very low battery voltage and stop the run!
  // Never want a single cell to go lower than 3 volts
  if (batVolts < lowVolts)
  {
    // loop forever if battery voltage is too low
    while(1)
    {
      ledFlash(1,200,200);
      Serial.print("Run had to stop due to low battery voltage = ");
      Serial.println(batVolts,DEC);
    }
  } 
  //-------------------------------------------------------------------------
  
  // Prepare to start run----------------------------------------------------
  
  // Nominal voltage for the Li-Po batteries we use is 7.4 volts
  // Compute ratio to adjust power to get close to actual percent power
  powerAdjustment = 7.4/batVolts;
  
  // Give 4 second delay until start - Flash LED 4 times
  ledFlash(4,500,500);                       
  
  // Clear first 10 bytes of internal eeprom
  for(byte q=0;q<10;q++) EEPROM.write(q,0);   
  
  // Do a base current usage check with all motors braked
  brake(4); cVolt1 = getSamples(curSensePin,200,'e');
    
  // Write the base current (in raw counts) to internal eeprom addresses 8 and 9
  EEPROM.write(8, highByte((int)cVolt1));
  EEPROM.write(9, lowByte((int)cVolt1));
  
  // Initialize quadrature encoder variables to 0
  encoderPos     = 0;
  encoderTotal   = 0;
  encoderForSum  = 0;
  encoderBackSum = 0;
  
  // Get Actual start time
  startTime      = millis();
  
  // Get first reading
  recordData(0); // Input is 0 for first reading
  //-------------------------------------------------------------------------
  
  
}
