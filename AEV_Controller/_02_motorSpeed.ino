void motorSpeed(byte motor, byte percentSpeed)
{
  //--------------------------------------------------------------
  // motorSpeed(motor, percentSpeed);
  //
  // Initialize motor at percentSpeed.
  //
  // Input: motor        : Motor Number (1-3, 4 = All Motors).
  //        percentSpeed : Percent power. 0-100%
  //
  // Output: none
  //--------------------------------------------------------------
  
  // Check motor input. If incorrect, display error in serial port for user.
  if(motor < 1) motor = 1;
  if(motor > 4) motor = 4;
  
  // Computer % speed with power adjustment
  percentSpeed = percentSpeed * powerAdjustment;
  
  // Check percentSpeed input.
  if(percentSpeed < 0)   percentSpeed = 0;
  if(percentSpeed > 100) percentSpeed = 100;
   
  // Map out the percent speed provided by the user
  byte s = map(percentSpeed,0,100,0,255); 

  // Determine which motor to apply power to.
  switch (motor) 
  {   
    
  // Initializes motor 1.  
  case 1:

    analogWrite(pwmPin1,s); break;
    
  // Initializes motor 2.  
  case 2:

    analogWrite(pwmPin2,s); break;
    
  // Initializes motor 3. 
  case 3:

    analogWrite(pwmPin3,s); break;
  
  // Initializes all motors.      
  default: 

    analogWrite(pwmPin1,s); // motor 1
    analogWrite(pwmPin2,s); // motor 2
    analogWrite(pwmPin3,s); // motor 3
    
  }
}

////--------------------------------------------------------------
//// powerAdjust - motorSpeed subroutine
////--------------------------------------------------------------
//float powerAdjust()
//{
//  //--------------------------------------------------------------
//  // powerAdjust();
//  //
//  // Returns a ratio to multiply percentSpeed by to handle battery
//  // power reduction as the battery is used.
//  //
//  // Input: none
//  //
//  // Output: none
//  //--------------------------------------------------------------
//  
//  // Get voltage count
//  int bVolts=getSamples(batVoltsPin,100,'d');
//  
//  // Compute battery voltage
//  float batVolts = 3.0*defRef*(float)bVolts/1024.0;
//  
//  // catch a very low battery voltage and stop the run!
//  if (batVolts < lowVolts)
//  {
//    // loop forever if battery voltage is too low
//    // (do not allow the run to take place)
//    while(1)
//    {
//      // set rapid flash if volts to low for run
//      ledFlash(1,200,200);
//      Serial.print("Run had to stop due to low battery voltage = ");
//      Serial.println(batVolts,DEC);
//    }
//  } 
//  
//  // Nominal voltage for the Li-Po batteries we use is 7.4 volts
//  // Compute ratio to adjust power to get close to actual percent power
//  
//  float powerAdjustment = 7.4/batVolts;
//  
//  return powerAdjustment;
//  
//}

