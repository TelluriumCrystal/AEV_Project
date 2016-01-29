void reverse(byte motor)
{
  //--------------------------------------------------------------
  // revers(motor);
  //
  // Reverse direction of motor.
  //
  // Input: motor: Motor Number (1-3, 4 = All Motors).
  //
  // Output: none
  //--------------------------------------------------------------
  
  // Check input 
  if(motor < 1) motor = 1;
  if(motor > 4) motor = 4;
    
  // Determine which motor to reverse.
  switch (motor) 
  {   
  
  // Reverse motor 1.      
  case 1:
    
    // Set motor power to 0 before reversing
    analogWrite(pwmPin1,0);
    
    // Reverse motor direction
    digitalWrite(hblogic1a, !digitalRead(hblogic1a) );
    digitalWrite(hblogic1b, !digitalRead(hblogic1b) );
            
    break;
     
  // Reverse motor 2.        
  case 2:
  
    // Set motor power to 0 before reversing
    analogWrite(pwmPin2,0);
    
    // Reverse motor direction
    digitalWrite(hblogic2a, !digitalRead(hblogic2a) );
    digitalWrite(hblogic2b, !digitalRead(hblogic2b) );
  
    break;
      
  // Reverse motor 3.        
  case 3:

    // Set motor power to 0 before reversing
    analogWrite(pwmPin3,0);
    
    // Reverse motor direction
    digitalWrite(hblogic3a, !digitalRead(hblogic3a) );
    digitalWrite(hblogic3b, !digitalRead(hblogic3b) );
    
    break;
      
  // Reverse all motors.       
  default: 
  
    // Set motor power to 0 before reversing
    analogWrite(pwmPin1,0); // motor 1
    analogWrite(pwmPin2,0); // motor 2
    analogWrite(pwmPin3,0); // motor 3
    
    // Reverse motor direction
    digitalWrite(hblogic1a, !digitalRead(hblogic1a) ); // motor 1
    digitalWrite(hblogic1b, !digitalRead(hblogic1b) ); // motor 1
    digitalWrite(hblogic2a, !digitalRead(hblogic2a) ); // motor 2
    digitalWrite(hblogic2b, !digitalRead(hblogic2b) ); // motor 2
    digitalWrite(hblogic3a, !digitalRead(hblogic3a) ); // motor 3
    digitalWrite(hblogic3b, !digitalRead(hblogic3b) ); // motor 3
    
  }
}
