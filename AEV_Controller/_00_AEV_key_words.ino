//=============================================================================================================
//Available keywords (Functions):
//=============================================================================================================
//  (a) brake
//  (b) celerate
//  (c) goFor
//  (d) goToRelativePosition
//  (e) goToAbsolutePosition
//  (f) motorSpeed
//  (g) reverse
//  (h) rotateServo
//  (i) getVehiclePostion
//  (j) getTotalMarks
//  (k) getForwardsTotal
//  (l) getBackwardsTotal
//  (m) aevDirection
//=============================================================================================================   
//   KEYWORD DETAILS:
//=============================================================================================================   
//   
//**********************************************************************************************************
//  (a) brake(x); --> 1 argument: 
//          x = motor number 1,2,3 or use 4 for all
//               
//          example call:
//            brake(2); // fully brake motor 2 
//            (note: brake invokes a motor controller standby state that minimizes current draw)
//**********************************************************************************************************
//   
//**********************************************************************************************************
//  (b) celerate(m,x,y,z); --> 4 arguments: 
//          m = motor number 1,2,3, or 4 for all;
//          x = start speed in % (0 to 100);
//          y = end speed in percent (0 to 100);
//          z = time in seconds (1 to 10) 
//               
//          example calls:
//            celerate(4,20,50,7)  //will accelerate all motors from 20% to 50% power in 7 seconds
//            celerate(2,100,20,1) //will deaccelerate motor 2 from 100% to 20% in 1 second 
//            (note 1: no goFor or goToMark is required after this call, but if used, it will
//            continue with the final motorspeed as set in the celerate command)
//**********************************************************************************************************
//   
//**********************************************************************************************************
//  (c) goFor(t); --> 1 argument:
//          t = time in seconds
//              
//          example call:
//            goFor(2.5); // continues with the last set of commands for 2.5 seconds 
//**********************************************************************************************************
//   
//**********************************************************************************************************
//  (d) goToRelativePosition(m); --> 1 argument:
//          m =  wheel count number (8 per wheel revolution; 3.9 inch diameter wheel; 0.4875 inches/mark)
//
//          The goToRelativePosition continues the previous command for "m" marks from the vehicles 
//          current position. "m" can be a positive or negative value. A positive value indicates the 
//          vehicle is moving forward from it's current position. A negative value indicates the 
//          vehicle is moving backward from it's current position. 
//
//          Example scenerio 1: Your vehicle has already traveled 200 marks from the starting point on the 
//                              track and is stopped at this position. The next lines in the code are:
//
//                              motorSpeed(4,20);
//                              goToRelativePosition(30);
//
//                              The above statements will set all motors to 20% power and run the motors
//                              until the vehicle reaches 230 marks.  
//
//          Example scenerio 2: Your vehicle has already traveled 200 marks from the starting point on the 
//                              track and is stopped at this position. The next lines in the code are:
//
//                              reverse(4);
//                              motorSpeed(4,20);
//                              goToRelativePosition(-30);
//
//                              The above statements will reverse all motors, set all motors to 20% power 
//                              and run the motors until the vehicle reaches 170 marks. 
//                        
//**********************************************************************************************************
//   
//**********************************************************************************************************
//  (e) goToAbsolutePosition(m); --> 1 argument:
//          m =  wheel count number (8 per wheel revolution)
//
//          The goToAbsolutePosition function continues the previous set of commands until the vehicle has 
//          traveled to input ("m") relative to the starting position of the vehicle.
//
//          Example scenerio 1: Your vehicle has already traveled 200 marks from the starting point on the 
//                              track and is stopped at this position. The next lines in the code are:
//
//                              motorSpeed(4,20);
//                              goToAbsolutePosition(300);
//
//                              The above statements will set all motors to 20% power and run the motors
//                              until the vehicle reaches 3000 marks from the starting point. The equivalant 
//                              of this using goToRelativePosition is:
//                              motorSpeed(4,20);
//                              goToRelativePosition(100);
//
//          Example scenerio 2: Your vehicle has already traveled 200 marks from the starting point on the 
//                              track and is stopped at this position. The next lines in the code are:
//
//                              reverse(4);
//                              motorSpeed(4,20);
//                              goToAbsolutePosition(0);
//
//                              The above statements willreverse all motors set all motors to 20% power and 
//                              run the motors until the vehicle reaches 0 marks (starting point). The 
//                              equivalant of this using goToRelativePosition is:
//
//                              reverse(4);
//                              motorSpeed(4,20);
//                              goToRelativePosition(-200);
//**********************************************************************************************************
//   
//**********************************************************************************************************
//  (f) motorSpeed(m,p); --> 2 arguments:
//          m = motor number 1,2,3,or use 4 for all
//          p = speed in percent, 0 to 100
//          
//          example call:
//            motorSpeed(2,67);  //set motor 2 speed to 67% of full power 
//            (note: a goFor, goToRelativePosition, goToAbsolutePosition command must follow this command)
//**********************************************************************************************************
//        
//**********************************************************************************************************
//  (g) reverse(m); --> 1 argument: 
//          m = motor number 1,2,3,or use 4 for all
//          
//          example call:
//            reverse(1); // reverses motor 1
//**********************************************************************************************************
//   
//**********************************************************************************************************
//  (h) rotateServo(a); --> 1 argument 
//          a = angle of rotation for servo. a = 0.00 to 180.00 degrees
//   
//          example call:
//            rotateServo(10.00);   // Initialize servo and set to 10 degrees
//            rotateServo(170.00);  // Rotate servo to 170 degrees
//            
//            Note: The limits, 0 & 180 degrees, are not nesecarily what will you see when you set your servo
//                  to these values. The Tower Pro SG92R servos will get close to 0 or 180 degrees but not exact.
//**********************************************************************************************************
//
//**********************************************************************************************************
//  (i) getVehiclePostion();--> no arguments -  returns the AEV's position.
//  
//          example call:
//            int absolutePostion = getVehiclePostion();
//            Note: If you travel 50 marks forwards and 20 marks backwards, then the number returned
//            from this function will be 30. In this case, absolutePostion = 30.
//**********************************************************************************************************
//   
//**********************************************************************************************************
//   (j) getTotalMarks(); --> no arguments - returns total marks AEV has traveled.
//   
//          example call:
//            int totalMartks = getTotalMarks();
//            Note: If you travel 50 marks forwards and 20 marks backwards, then the number returned
//            from this function will be 70. In this case, totalMarks = 70.
//**********************************************************************************************************
//   
//**********************************************************************************************************
//  (k) getForwardsTotal(); --> no arguments - Returns total number of marks AEV has traveled in the forward 
//                                              direction.
//   
//          example call:
//            int fMarks = getForwardsTotal();
//            Note: If you travel 50 marks forwards and 20 marks backwards, then the number returned
//            from this function will be 50. In this case, fMarks = 50.
//**********************************************************************************************************
//   
//**********************************************************************************************************
//  (l) getBackwardsTotal(); --> no arguments - returns total number of marks AEV has traveled in the reverse 
//                                               direction.
//   
//          example call:
//            int bMarks = getBackwardsTotal();
//            Note: If you travel 50 marks forwards and 20 marks backwards, then the number returned
//            from this function will be 20. In this case, bMarks = 20.
//**********************************************************************************************************
//   
//**********************************************************************************************************
//  (m) getVehicleDirection(); --> no arguments - returns direction of AEV.
//   
//          example call:
//            int aevDir = getVehicleDirection(); // Check aev direction.
//            Note: If aevDir == 1, vehicle is moving forward. 
//                  If aevDir == 0, vehicle is moving in reverse.
//                  If aevDir == 2, no direction detected.
//**********************************************************************************************************



  
