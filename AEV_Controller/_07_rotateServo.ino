void rotateServo(float angle)
{
  //--------------------------------------------------------------
  // rotateServo(angle);
  //
  // Rotates servo
  //
  // Input: angle        : servo angle (0 - 180 degrees).
  //
  // Output: none
  //--------------------------------------------------------------
  
  // Check motor input. If incorrect, display error in serial port for user.
  if(angle < 0.00) angle = 0.00;
  if(angle > 180.00) angle = 180.00;
   
  // Map out the angle provided by the user
  int ms = map(angle,0.00,180.00,544,2400);
 
  // Rotate servo
  aevServo.writeMicroseconds(ms);
  
}
