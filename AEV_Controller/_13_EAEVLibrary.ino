//------------------------------------------------------------------------------------------
// Extended AEV Library
//
// An add-on library that adds additional functionality to the existing AEV programming
// suite.
// 
// Methods in this library:
// 
// (1) calculateVelocity
// (2) calculateAcceleration
// (2) grabPositionTimeData
// (3) smartGoToAbsolutePosition
//
//------------------------------------------------------------------------------------------

// (1) Calculate velocity

void calculateVelocity()
{
  // Calculate both velocities from position data using integral calculus
  velocities[1] = ((float)positions[2] - (float)positions[1])/((float)times[2]-(float)times[1]);
  velocities[2] = ((float)positions[3] - (float)positions[2])/((float)times[3]-(float)times[2]);
}

// (2) Calculate acceleration

void calculateAcceleration()
{

// Calculate acceleration from velocity data using integral calculus
  acceleration = (velocities[2] - velocities[1])/((float)times[4]-(float)times[1]);
}

// (2) Cycle the position and time data and add a new value to the end of the arrays

void grabPositionTimeData()
{
  // Cycle position data
  positions[4] = positions[3];
  positions[3] = positions[2];
  positions[2] = positions[1];

  // Grab newest position data
  positions[1] = encoderPos;

  // Cycle time data
  times[4] = times[3];
  times[3] = times[2];
  times[2] = times[1];

  // Grab current time
  times[1] = timeNow();
}

// (3) Move to the specified absolute position using the specified motor precentage

// Key for motor value:
// 1 = only motor 1
// 2 = only motor 2
// 3 = only motor 3
// 4 = all motors
// 5 = motors 1 & 2
// 6 = motors 1 & 3
// 7 = motors 2 & 3

void smartGoToAbsolutePosition(byte motor, byte mSpeed, byte correctionSpeed, int absolutePosition)
{
  // Note that unlike goFor, goToAbsolutePosition, and goToRelativePosition, it is not necessary to
  // use motorSpeed before running smartGoToAbsolutePosition
  //
  // CAUTION: This method may not work as intended if the AEV is already in motion!
  //
  // This method works by using pre-calculated deceleration data to accelerate the AEV to a speed
  // that will allow it to coast the rest of the way to the target position. There are three main
  // "phases": Acceleration, Coasting, and Correction. The first two are self-explanitory, and the
  // last one only takes effect if the AEV determines it will be more than 10% off of the target
  // position. In this case, it will run the engines at the correction speed to try and correct for
  // the inaccuracy. For this reason it is important to pick a small correction speed.

  // Prevent error if motor value is out of range
  if(motor < 1) motor = 1;
  if(motor > 7) motor = 7;

  // Start motors in indicated configuration
  switch(motor)
  {
    case 1 : motorSpeed(1,mSpeed); break;
    case 2 : motorSpeed(2,mSpeed); break;
    case 3 : motorSpeed(3,mSpeed); break;
    case 4 : motorSpeed(4,mSpeed); break;
    case 5 : motorSpeed(1,mSpeed); motorSpeed(2,mSpeed); break;
    case 6 : motorSpeed(2,mSpeed); motorSpeed(3,mSpeed); break;
    case 7 : motorSpeed(1,mSpeed); motorSpeed(3,mSpeed); break;
  }

  // Determine required direction of travel to reach aboslutePosition
  if(absolutePosition > encoderPos) dir = 1;
  else dir = 0;

  // Create a marker to mark the current movement phase (1 = acceleration, 2 = coasting, 3 = acceleration correction, 4 = deceleration correction)
  byte currentPhase = 1;

  // Begin loop until the AEV reaches its target position
  do
  {
    // Inject a new value into the position-time arrays and calculate velocities
    grabPositionTimeData();
    calculateVelocity();
    
    if(currentPhase == 1)
    {
      // Determine velocity needed to coast to the target position from the current position
      // using v^2 = vo^2+2a(x-xo)
      float vel = sqrt((-2)*deceleration*(float)abs(encoderPos-absolutePosition));

      // Stop accelerating when the required speed is reached
      if(vel < abs(velocities[1]))
      {
        brake(4);
        currentPhase = 2;
      }
    }
    else if(currentPhase == 2)
    {
      // Estimate final position based on current speed and position using v^2 = vo^2+2a(x-xo)
      float endpos = (-pow(velocities[1],2))/(2*deceleration);
      
      // Determine if estimate falls within acceptable range, and go to a correction phase if not
      if(endpos < ((float)absolutePosition + (float)absolutePosition*0.1) && abs(endpos - absolutePosition) > 1)
      {
        currentPhase = 3;
      }
      else if(endpos > ((float)absolutePosition - (float)absolutePosition*0.1) && abs(endpos - absolutePosition) > 1)
      {
        currentPhase = 4;
      }
    }
    else if(currentPhase == 3)
    {
      // Add code to calculate and execute an accelration here
    }
    else if(currentPhase == 3)
    {
      // Add code to calculate and execute an decelration here
    }
    
    // Call recordData to log mandatory eeprom data
    recordData(minTimeLapse);
  }
  while(dir == 1 && absolutePosition > encoderPos || dir == 0 && absolutePosition < encoderPos );
}

