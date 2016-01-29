//--------------------------------------------------------------------------
// Matlab <-> Arduino Communication Library
//
// Consist of a library of routines that are used in data transfer. 
// The following subroutines are contained in this library:
// 
// (1) establishContact
// (2) sendArduino2Matlab
//
//--------------------------------------------------------------------------

// (1) Establish contact with Matlab****************************************

boolean establishContact() 
{    
  //------------------------------------------------------------------------
  // establishContact();
  //
  // Send 1's to serial port for establishing constact with Matlab.
  //
  // Input: None
  //
  // Output: None
  //-------------------------------------------------------------------------
  
  // Initialize flag
  boolean flag=false;
  
  // Set timer flag
  unsigned long timer1 = millis();
  
  // Check connection for 500 milliseconds
  while (millis()-timer1 < 500)  
  {
    if (Serial.available() <= 0) // If serial is not available
    {
      Serial.println(1, DEC);    // Try sending a number
      delay(50);
    }
    else                         // else, we're connected! 
    {
      flag=true;
      break;
    }
  }
  return flag;
}
//**************************************************************************

// Send arduino data to Matlab via serial communication*********************

void sendArduino2Matlab()
{ 
  //------------------------------------------------------------------------
  // sendArduino2Matlab();
  //
  // Transfer data from Arduino to Matlab.
  //
  // Input: None
  //
  // Output: None
  //-------------------------------------------------------------------------
  
  int del = 5; // Initialize delay time
  
  // Get total number of bytes stored in eeprom
  byte a = EEPROM.read(0);
  byte b = EEPROM.read(1);
  int number=word(a,b);

  // Send total number of elements for Matlab to read
  long total_elements = (number/16)*5;
  Serial.println(total_elements); 

  // eeprom external storage bytes used
  // send seven after run battery life calcs
  // some may be zero - depends on how long they left unit powered on after run
  for (b=2;b<8;b++)
  {
    a = EEPROM.read(b);
    //Serial.println(a,DEC);
  }
  
  // Send the motor zero current state
  a = EEPROM.read(8);
  b = EEPROM.read(9);
  int number1 = word(a,b);
  //Serial.println(number1,DEC);

  // Send data stored as bytes in external eeprom
  // time, current, voltage, cumulative marks, position
  for (int j=0;j<number;j=j+16)
  {   
    // Read data set j
    eeRead(j,configuration);
    delay(del);

    // Send time
    Serial.println(configuration.time);
    delay(del);
    
    // Send current counts
    Serial.println(configuration.cvolts);
    delay(del);
    
    // Send voltage counts
    Serial.println(configuration.bvolts);
    delay(del);
    
    // Send cumulative marks
    Serial.println(configuration.tMarks);
    delay(del);
    
    // Send position marks
    Serial.println(configuration.pMarks);
    delay(del);
  }
  delay(25);
  
}
//**************************************************************************
