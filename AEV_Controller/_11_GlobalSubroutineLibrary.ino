//------------------------------------------------------------------------------------------
// Global Subroutine Library
//
// Consist of a library of routines that are used in multiple subroutines. The following 
// subroutines are contained in this library:
// 
// (1) recordData
// (2) timeNow
// (3) getSamples
// (4) ledFlash
//
//------------------------------------------------------------------------------------------

//******************************************************************************************
// (1) recordData 

void recordData(unsigned long numOfMillisLapsed)
{
  //----------------------------------------------------------------------------------------
  // recordData(numOfMillisLapsed);
  //
  // Record time,current,voltage,total marks and postion to external eeprom
  //
  // Input: numOfMillisLapsed : Time frame to lapse before recording data.
  //
  // Output: none
  //
  // Data Recording information:
  //   The 32K eeprom can record 4096 data sets (4 integers in a set, 2 bytes per integer 
  //   or 32768/8). What's this telling us? Well, for example for a maximum length run of 
  //   120 seconds then only 34 sets per second are allowed or approximately 1 every 30 ms 
  //   Currently 60 ms is the time lapse.
  //---------------------------------------------------------------------------------------- 
  
  // Get time
  unsigned long theTime = timeNow();
  
  // Check if the difference from the last time stamp is less than 
  // the minimum time gap we allow to record data
  if((theTime - lastRecordedTime) < numOfMillisLapsed)
  {
    return;
  }
  
  // Store the recorded time for the next check
  lastRecordedTime = theTime;
  
  // Get current counts
  int cVolts=getSamples(curSensePin,200,'e');
     
  // Get voltage counts       
  int bVolts=getSamples(batVoltsPin,100,'d');
            
  // Store data in struct
  configuration.time         = theTime;
  configuration.cvolts       = cVolts;
  configuration.bvolts       = bVolts;
  configuration.tMarks       = encoderTotal;
  configuration.pMarks       = encoderPos;
    
  // Write to EEprom  
  eeWrite(nBytes,configuration);
  delay(5);
  
  // Increase the number of bytes    
  nBytes = nBytes + 16;

}
//******************************************************************************************

//******************************************************************************************
// (2) timeNow 

unsigned long timeNow()
{
  //----------------------------------------------------------------------------------------
  // timeNow();
  //
  // Returns current time referenced from the start time of the program
  //
  // Input: none
  //
  // Output: currentTime
  //---------------------------------------------------------------------------------------- 

  unsigned long currentTime = (millis()-startTime);
  
  return currentTime;
}
//******************************************************************************************

//******************************************************************************************
// (3) getSamples

int getSamples(byte pin, int numOfSamples, char type)
{
  //--------------------------------------------------------------
  // getSamples(pin, numOfSamples, type);
  //
  // Returns voltage or current counts.
  //
  // Input: pin          : Pin to read from.
  //        numOfSamples : Number of samples to take.
  //        type('e'/'d'): String specifying type of reading.   
  //
  // Output: valueOut    : Sampled voltage or current counts
  //--------------------------------------------------------------
  
  // Determine analog type
  if (type=='e') // Take current reading
  {
    analogReference(EXTERNAL); // When taking current data us EXTERNAL (2.46 volts)
  }
  else // Take voltage reading
  {
    analogReference(DEFAULT); // When taking voltage data use DEFAULT (5.00 volts)
  }
  
  // Initialize average value
  long sampleAvg=0; 
  
  // get numOfSamples samples
  for (byte j = 0; j < (numOfSamples + 2); j++)
  {
    // oddly, the first two values are considerably off 
    if (j < 2)
    {
      analogRead(pin); // Throw away value
    }
    else 
    {
      // Cumulative sum
      sampleAvg = sampleAvg + analogRead(pin);
    }
  }
      
  //  Compute average output
  int valueOut = (int)(sampleAvg/numOfSamples);
  
  // Post process current reading
  if (type=='e') // Take current reading
  {
    // Post process current count
    valueOut = valueOut - cVolt1;
    valueOut = (valueOut < 1) ? 0 : valueOut;
  }
  
  return valueOut;       
}
//******************************************************************************************

//******************************************************************************************
// ledFlash

void ledFlash(byte numOfTimes, int flashDuration, int timeBetweenFlashes)
{
  //------------------------------------------------------------------------
  // ledFlash(numOfTimes, flashDuration, timeBetweenFlashes);
  //
  // Flashes Arduino LED a sepcified number of times.
  //
  // Input: numOfTimes        : Number of times to flash LED.
  //        flashDuration     : Length of time to keep LED on.
  //        timeBetweenFlashes: Time between flashes.
  //
  // Output: None
  //-------------------------------------------------------------------------
  
  // Turn LED off
  digitalWrite(yellowLedPin,LOW);
      
  // Enter while loop
  do
  { 
    // Turn LED on
    digitalWrite(yellowLedPin,HIGH);
        
    // Keep LED on for ''flashduration''
    delay(flashDuration);

    // Turn LED off
    digitalWrite(yellowLedPin,LOW);

    // Keep LED on for ''flashduration''
    delay(timeBetweenFlashes);
    
    // Decrease number of iterations
    numOfTimes--;
    
  } 
  while (numOfTimes>0);
}
//******************************************************************************************
