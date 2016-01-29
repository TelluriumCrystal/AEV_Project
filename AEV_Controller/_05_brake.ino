void brake(byte motor)
{
  //--------------------------------------------------------------
  // brakeMotor(motor);
  //
  // Brakes motor.
  //
  // Input: motor: Motor Number (1-3, 4 = All Motors).
  //
  // Output: none
  //
  // Note: Setting the motor pin to 0 is not a TRUE motor stop. A 
  // true motor stop requires that we set both reverse pins on 
  // the motor to LOW and set the motor pin to high. This essentially
  // locks the motor spindle in place and prevents the motor from spinning
  // acting as a true stop. For the motors we use we can set the motor 
  // pin to zero and the motor will stop due to the internal friction of
  // the motor. This is also more efficient since we're not requiring large 
  // amounts of current to stop the motor and keep the spindle from spinning. 
  //--------------------------------------------------------------
  
  // Determine which motor to cut off power to.
  switch (motor) 
  {    
  // Stop motor 1.  
  case 1:
    analogWrite(pwmPin1,0);
    break;
  
  // Stop motor 2.     
  case 2:
    analogWrite(pwmPin2,0);
    break;
 
  // Stop motor 3.       
  case 3:
    analogWrite(pwmPin3,0);
    break;
 
  // Stop all motors.       
  default: 
    analogWrite(pwmPin1,0);
    analogWrite(pwmPin2,0);
    analogWrite(pwmPin3,0);
  }
}

