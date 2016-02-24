void myCode()
{
  //----------------------------------------------------------------------------------------
  // myCode();
  //
  // This is the tab where the programming of your vehicle operation is done.
  // Tab _00_AEV_key_words contains a compiled list of functions/subroutines used for vehicle
  // operation. 
  //
  // Note:
  // (1) After running your AEV do not turn the AEV off, connect the AEV to a computer, or 
  //     push the reset button on the Arduino. There is a 13 second processing period. In 
  //     post processing, data is stored and battery recuperation takes place. 
  // (2) Time, current, voltage, total marks, position traveled are recorded approximately 
  //     every 60 milliseconds. This may vary depending on the vehicles operational tasks. 
  //     It takes approximately 35-40 milliseconds for each recording. Thus when programming,
  //     code complexity may not be beneficial. 
  // (3) Always comment your code. Debugging will be quicker and easier to do and will 
  //     especially aid the instructional team in helping you. 
  //---------------------------------------------------------------------------------------- 

  // Program between here-------------------------------------------------------------------
  
  /* List of valid functions:

     celerate(m,p1,p2,t);
     Accelerates or decelerates the specified motor from one speed to another over a specified length of time
     m  = motor number (4 for all motors)
     p1 = start power percent
     p2 = end power percent
     t  = time (seconds) to go from p1 to p2

     motorSpeed(m,p);
     Sets the specified motor to the specified speed (requires a goFor() to execute)
     m = motor number (4 for all motors)
     p = power percent

     brake(m);
     Commands the specified motor to stop
     m = motor number (4 for all motors)

     reverse(m);
     Reverses the polarity of the power provided to the specified motor
     m = motor number (4 for all motors)

     goFor(t);
     Continues the last command for the specified time
     t = time (seconds)

     reflectanceSensorTest();
     Initiates the reflectance sensor serial readout

     goToRelativePosition(m);
     Continues the last command for the specified number of marks from the current position
     m = marks

     goToAbsolutePosition(m);
     Continues the last command for the specified number of marks from the starting position
     m = marks

  */
  
  // Reverse motors to make AEV go forward
  reverse(4);
  
  // Main code
  motorSpeed(4,20);
  goFor(2);
  motorSpeed(4,15);
  goToAbsolutePosition(758);
  reverse(4);
  motorSpeed(4,15);
  goFor(1);
  brake(4);
  
  // And here--------------------------------------------------------------------------------

} // DO NOT REMOVE. end of void myCode()




