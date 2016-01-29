void goFor(float numOfSeconds)
{
  //--------------------------------------------------------------
  // goFor(numOfSeconds);
  //
  // Continue statement(s) previous to "goFor" for "numOfSeconds".
  //
  // Input: numOfSeconds: Time frame, in seconds.
  //
  // Output: none
  //--------------------------------------------------------------
 
  // Compute metro timer input in milliseconds
  unsigned long numOfMillis = numOfSeconds*1000;

  // Reset metro timer 
  metroTimer.interval(numOfMillis);
  metroTimer.reset();
 
  // Enter while loop until time input has passed
  do
  { 
    // Every loop call recordData 
    recordData(minTimeLapse);
  } 
  while (!metroTimer.check()==1);
}
