void celerate(byte motor, byte startSpeed, byte endSpeed, float numOfSeconds)
{
  //----------------------------------------------------------------------------------------
  // celerate(motor, startSpeed, endSpeed, seconds);
  //
  // Accelerate/Decelerate motor(s) from startSpeed to endSpeed in
  // numOfSeconds seconds.
  //
  // Input: motor        : Motor Number (1-3, 4 = All Motors).
  //        startSpeed   : Percent power. 0-100%
  //        endSpeed     : Percent power. 0-100%  
  //        numOfSeconds : Time frame to go from startSpeed-endSpeed
  //
  // Output: none
  //---------------------------------------------------------------------------------------- 
    
  // Enforce limits------------------------------------------------------------------------- 
  
  // Starting & ending power constraints
  if (startSpeed<0)   startSpeed=0;
  if (startSpeed>100) startSpeed=100;
  if (endSpeed<0)     endSpeed=0;
  if (endSpeed>100)   endSpeed=100;
  
  // Time period constraints
  if (numOfSeconds < 1.0)   numOfSeconds = 1.0;
  if (numOfSeconds > 10.0)  numOfSeconds = 10.0;
  
  // Motor constraints
  if (motor<1) motor=1;
  if (motor>4) motor=4;
  
  //----------------------------------------------------------------------------------------
  
  // Set up timing variables----------------------------------------------------------------
  
  // Compute metro timer input in milliseconds
  unsigned long numOfMillis = numOfSeconds*1000;
  
  // Compute timestep 
  unsigned long tStep = (numOfMillis)/abs(startSpeed - endSpeed);

  // Initialize motor step (for accelerating or decelerating)
  int stepper = (startSpeed > endSpeed) ? -1 : 1;
  
  // Reset metro timer 
  metroTimer.interval(numOfMillis); // Start timer 
  metroTimer.reset();               // Reset metro timer 
  
  // Initialize timing flag
  unsigned long t1 = millis();

  //----------------------------------------------------------------------------------------
  
  // Set initial motor speeds---------------------------------------------------------------
  byte celerateSpeed = startSpeed;
  motorSpeed(motor,celerateSpeed);
  //----------------------------------------------------------------------------------------
    
  // Enter timing loop----------------------------------------------------------------------
  do
  {
    // Record AEV data
    recordData(minTimeLapse);
    
    if(((millis() - t1) >= tStep)) // If the difference in time lapse is g.t.e. to our time step
    {
      t1 = millis(); // Reassign timing flag  
     
      celerateSpeed = celerateSpeed + stepper; // Accelerate motor to next step
      
      // Set motor speeds
      motorSpeed(motor,celerateSpeed);      
    }
    else
    {
      continue; 
    }
  }
  while (!metroTimer.check()==1);
  
  // Set final motor speeds--------------------------------------------------------
  // Enforce ending speed (The time step equation works perfectly without the 
  // "recordData();" function call. Since we need to use "recordData();" this takes 
  // up ~36-40 milliseconds every ~60 milliseconds it records data. So the ending 
  // speed may be a few short. Simply enforce the ending speed.  
  motorSpeed(motor,endSpeed);
  //----------------------------------------------------------------

}
//--------------------------------------------------------------------
