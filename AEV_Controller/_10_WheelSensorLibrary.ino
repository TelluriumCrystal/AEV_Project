//--------------------------------------------------------------------------
// Reflectance Sensor Functions
//
// Consist of a library of routines that can be used for enhanced AEV coding
// development. The use of these routines in your code is your decision and 
// therefore your responsibilty in terms of debugging and use. The following 
// subroutines are contained in this library:
// 
// (01) getVehiclePostion
// (02) getTotalMarks
// (03) getBackwardsTotal
// (04) getForwardsTotal
// (05) getVehicleDirection
// (06) goToRelativePosition
// (07) goToAbsolutePosition
// (08) quadEncoderA
// (09) quadEncoderB
// (10) Reflectance Sensor Test
//
//--------------------------------------------------------------------------

//**************************************************************************
// (1) Get Absolute Vehicle Position

int getVehiclePostion()
{
  //------------------------------------------------------------------------
  // getVehiclePostion();
  //
  // Returns absolute AEV position.
  //
  // Example Call on Routine: 
  // int absolutePostion = getVehiclePostion();
  //
  // Input: none
  //
  // Output: none
  //-------------------------------------------------------------------------
  
  // Return global variable used in quadrature encoder
  return encoderPos;
}
//**************************************************************************

//**************************************************************************
// (2) Get Total Marks Traveled

 int getTotalMarks()
{
  //------------------------------------------------------------------------
  // getTotalMarks();
  //
  // Returns total marks AEV has traveled.
  //
  // Example Call on Routine: 
  // int totalMarks = getTotalMarks();
  //
  // Input: none
  //
  // Output: none
  //-------------------------------------------------------------------------
  
  // Return global variable used in quadrature encoder
  return encoderTotal;
}
//**************************************************************************

//**************************************************************************
// (3) Get Total Backward Marks Traveled

int getBackwardsTotal()
{
  //------------------------------------------------------------------------
  // getBackwardsTotal();
  //
  // Returns total number of marks AEV has traveled in the reverse direction.
  //
  // Example Call on Routine: 
  // int backwardTotal = getBackwardsTotal();
  //
  // Input: none
  //
  // Output: none
  //-------------------------------------------------------------------------
  
  // Return global variable used in quadrature encoder
  return encoderBackSum;
}
//**************************************************************************

//**************************************************************************
// (4) Get Total Forward Marks Traveled

int getForwardsTotal()
{
  //------------------------------------------------------------------------
  // getForwardsTotal();
  //
  // Returns total number of marks AEV has traveled in the forward direction.
  //
  // Example Call on Routine: 
  // int forwardTotal = getForwardsTotal();
  //
  // Input: none
  //
  // Output: none
  //-------------------------------------------------------------------------
  
  // Return global variable used in quadrature encoder
  return encoderForSum;
}
//**************************************************************************

//**************************************************************************
// (5) Get Vehicle Direction

int getVehicleDirection()
{
  //------------------------------------------------------------------------
  // getVehicleDirection();
  //
  // Returns a flag specifying the direction the vehicle is traveling. 
  // 1 = forward, 0 = backward.
  //
  // Example Call on Routine: 
  // int direction = getVehicleDirection();
  //
  // Input: none
  //
  // Output: none
  //-------------------------------------------------------------------------
  
  // Return global variable used in quadrature encoder
  return dir;
}
//**************************************************************************

//**************************************************************************
// (6) Go to Relative Position

void goToRelativePosition(int numOfMarks)
{
  //------------------------------------------------------------------------
  // goToRelativePosition(numOfMarks);
  //
  // Continues the previous statement until the vehicle has traveled 
  // "numOfMarks" from the current position.
  //
  // Example Call on Routine: 
  // motorSpeed(1,23);
  // goToRelativePosition(130);
  //
  // Input: numOfMarks: Number of marks to travel from current position.
  //
  // Output: none
  //-------------------------------------------------------------------------

  // Compute end mark to travel to.
  int endMark = encoderPos + numOfMarks;
  //int endMark = numOfMarks + encoderTotal;
  
  Serial.println(endMark,DEC);
  
  // If the end mark is greater than the current position
  if(endMark > encoderPos)
  {
    do
    {
      // Every loop call recordData 
      recordData(minTimeLapse);
      Serial.println(encoderPos,DEC);
      
    }
    while(encoderPos < endMark);
    
  }
  else // Else, if the the end mark is less than the current position
  {
    do
    {
      // Every loop call recordData 
      recordData(minTimeLapse);
      Serial.println(encoderPos,DEC);
    }
    while(encoderPos > endMark); 
  }
    
}
//**************************************************************************

//**************************************************************************
// (7) Go to Absolute Position

void goToAbsolutePosition(int positionMark)
{
  //------------------------------------------------------------------------
  // goToAbsolutePosition(positionMark);
  //
  // Continues the previous statement until the vehicle has traveled 
  // to "positionMark" relative to the starting position of the vehicle.
  //
  // Example Call on Routine: 
  // motorSpeed(1,23);
  // goToAbsolutePosition(350);
  //
  // Input: positionMark: Number of marks to travel from starting position.
  //
  // Output: none
  //-------------------------------------------------------------------------
  
  // Compare input to current position. Are we going forward or reverse?
  
  if(positionMark < encoderPos) // Going back toward start point
  {
    // Enter while loop until encoderPos reaches positionMark.
    do
    {
      // Every loop call recordData 
      recordData(minTimeLapse);
      Serial.println(encoderPos,DEC);
    }
    while(encoderPos > positionMark); 
  }
  else // Going toward the end point
  {
    // Enter while loop until encoderPos reaches positionMark.
    do
    {
      // Every loop call recordData 
      recordData(minTimeLapse);
      Serial.println(encoderPos,DEC);
    }
    while(encoderPos < positionMark);
  }
  
}
//**************************************************************************

//**************************************************************************
// Quadrature Encoder: It is strongly recommended you don't mess with the 
// following subroutines
//**************************************************************************

// (8) Interrupt on A changing state
void quadEncoderA()
{
  // Test transition
  encoderSetA = (digitalRead(encoderPinA) == HIGH);
  
  // Adjust counter + if A leads B
  // If encoderSetA is not equal to encoderSetB, add 1, else subtract 1
  encoderPos += (encoderSetA != encoderSetB) ? + 1 : -1;
  
  // Cumulative sum
  // Add one to current sum
  encoderTotal += 1;
  
  // Forward sum
  // If encoderSetA is not equal to encoderSetB, add 1, else add 0
  encoderForSum += (encoderSetA != encoderSetB) ? + 1 : 0;
  
  // Backward sum
  // If encoderSetA is not equal to encoderSetB, add 0, else subtract 1
  encoderBackSum += (encoderSetA != encoderSetB) ? 0 : -1;
  
  // Adjust direction
  // If encoderSetA is not equal to encoderSetB, 1 (forward), else 0 (reverse)
  dir = (encoderSetA != encoderSetB) ? 1 : 0;
  //Serial.print("Position: ");
  //Serial.println(encoderTotal);
  //delay(1); 
}

// (9) Interrupt on B changing state
void quadEncoderB()
{
  // Test transition
  encoderSetB = (digitalRead(encoderPinB) == HIGH);
  
  // Adjust counter + if B follows A
  // If encoderSetA is equal to encoderSetB, add 1, else subtract 1
  encoderPos += (encoderSetA == encoderSetB) ? +1 : -1;
  
  // Cumulative sum
  // Add one to current sum
  encoderTotal += 1;
  
  // Forward sum
  // If encoderSetA is equal to encoderSetB, add 1, else add 0
  encoderForSum += (encoderSetA == encoderSetB) ? + 1 : 0;
  
  // Backward sum
  // If encoderSetA is equal to encoderSetB, add 0, else subtract 1
  encoderBackSum += (encoderSetA == encoderSetB) ? 0 : -1;
  
  // Adjust direction
  // If encoderSetA is equal to encoderSetB, 1 (forward), else 0 (reverse)
  dir = (encoderSetA == encoderSetB) ? 1 : 0;

}

// (10) Reflectance Sensor test
void reflectanceSensorTest()
{
  //------------------------------------------------------------------------
  // reflectanceSensorTest();
  //
  // Tests wheel count sensors
  //
  //
  // Input: none
  //
  // Output: none
  //------------------------------------------------------------------------- 
  
  // Enter while loop and print encorder variables to serial moniter
  do
  {
    
    while(dir == 2) // Wait until we start spinning the wheel
    {
    }; 
    
    // Print total counts
    Serial.print("Total Count: "); Serial.print(encoderTotal);
    
    // Print position
    Serial.print("; Position: "); Serial.print(encoderPos);
    
    // Print direction
    if(dir == 1) Serial.println("; Direction: Forward");
    if(dir == 0) Serial.println("; Direction: Reverse");
    
    // Put a delay in to avoid freeze
    delay(50);
    
  }
  while(1);
  
  
}
