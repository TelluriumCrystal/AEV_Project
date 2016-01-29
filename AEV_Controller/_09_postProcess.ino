void postProcess()
{
  
  //unsigned int eepromAddress = 0;  // eeprom address 
  //byte rl                    = 2;  // Starting address to store bat life to int eeprom

   // Run is over stop all motors
  brake(4);
  
  // Collect data for an additional 3 seconds
  goFor(3);
  
  // shut everything down
  // store number of data bytes collected to eeprom
  // Serial.println(eepromAddress,DEC);
  EEPROM.write(0, highByte((int) nBytes));
  EEPROM.write(1, lowByte( (int) nBytes));
  
  byte a = EEPROM.read(0);
  byte b = EEPROM.read(1);
  
  int number=word(a,b); 
  
  // Give 10 second delay until end. Allow battery to return back to normal state
  ledFlash(10,500,500); 
  
  digitalWrite(yellowLedPin,HIGH); // Turn yellow LED on.

}
