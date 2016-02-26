/*
   AEV sketchbook version 7nA===============================================================
 
 - A list of available function call are listed in detail under tab "_00_AEV_key_words".
 
 - The main programming is done under tab "_01_myCode".
 
 - NOTE: This software is open source. Any modifications made by the user to subroutines 
 is at the risk of the user. 
 
 =========================================================================================
 AEV007nA
 
 n version communicates with Matlab 
 date May 01,2014
 
 changes:
 - changed pin assignment to match AEV6 SMC
 
 date Nov.12,2013
 - Re-commented to organize code
 - Removed timer for automatic start
 
 date Jan.08,2014
 - changed order of battery check and delay start so matlab can read without battery 
 attached
 
 date April 30, 2014
 - sketchbook re-write
 - Voltage regulation - new power adjust function
 - Updated quadrature encoder for wheel count tracking
 - Reduced time increment between data recording
 
 date December 21, 2014 
 - Fixed bug regarding variable types mismatch in encoder subroutines  
 goToRelativePostion & goToAbsolutePosition
 */

// ---------------------------------------------------------------------------
// Include Libraries 
// ---------------------------------------------------------------------------
#include <EEPROM.h>      // Writes to internal 1K byte eeprom storage
#include <Wire.h>        // Writes to external 32K byte external eeprom  
#include <EEPROMI2C.h>   // Writes to external 32K byte external eeprom
#include <Metro.h>       // use metro for timing events
#include <Servo.h>       // use servo library -for servo operations

// ---------------------------------------------------------------------------
// Pin definitions (revised pin definitions for AEV6 generation)
// ---------------------------------------------------------------------------
const byte pwmPin1       =  5; // Motor 1 pwm pin
const byte hblogic1a     =  7; // Motor 1 direction pin A
const byte hblogic1b     =  8; // Motor 1 direction pin B
const byte pwmPin2       =  6; // Motor 2 pwm pin
const byte hblogic2a     = 16; // Motor 2 direction pin A
const byte hblogic2b     = 17; // Motor 2 direction pin B
const byte pwmPin3       = 11; // Motor 3 pwm pin (optional)
const byte hblogic3a     = 10; // Motor 3 direction pin A
const byte hblogic3b     = 12; // Motor 3 direction pin B
const byte servoPin      =  9; // Servo pin declaration
const byte buttonBypass  =  4; // Program start button
const byte curSensePin   = A7; // Current is sensed on analog 7
const byte batVoltsPin   = A6; // Voltage is sensed on analog 6
const byte yellowLedPin  = 13; // Pretty yellow LED, IT'S NOT AN ARDUINO WITHOUT AN LED!
const byte encoderPinA   =  2; // pin 2 (interrupt 0) used for wheel counts 
const byte encoderPinB   =  3; // pin 3 (interrupt 1) used for wheel counts

// ---------------------------------------------------------------------------
// Variable Declarations 
// ---------------------------------------------------------------------------

// Motor speed power adjustment
float powerAdjustment                = 1.00;      // Factor for handling battery power reduction.

// Voltage & Current Reference
const float extRef                   = 2.46;      // External reference voltage
const float defRef                   = 5.0;       // Default reference voltage
const float lowVolts                 = 6.75;      // Minimum voltage required for AEV operation
int cVolt1                           = 0;         // Initiate the no motor(s) running current variable

// Timing
Metro metroTimer                     = Metro();   // Initialize metro timer
unsigned long startTime              =    0;      // Reference for actual vehicle start time
unsigned long lastRecordedTime       =    0;      // Used for ensuring record times to do not occur under "minTimeLapse"
unsigned long minTimeLapse           =   60;      // Threshold for recording data (milliseconds) 

// EEprom storage
int nBytes                           = 0;         // Number of bytes EEProm recorded

// Quadrature Encoder
boolean encoderSetA                  = false;     // Boolean quadrature encoder for sensor A
boolean encoderSetB                  = false;     // Boolean quadrature encoder for sensor B
volatile int encoderPos              =     0;     // Position
volatile unsigned int encoderTotal   =     0;     // Total accumulation of marks
volatile unsigned int encoderForSum  =     0;     // Forward sum
volatile int encoderBackSum          =     0;     // Backward sum
volatile byte dir                    =     2;     // Direction: 1 = Forward; 0 = Reverse, 2 = No Direction.

// AEV Servo
Servo aevServo;

// Data collection variable structure - 16 bytes
struct config_t
{
  unsigned long time;       // Time recorded, in milliseconds
  int cvolts;               // current counts
  int bvolts;               // voltage counts
  unsigned int tMarks;      // Total marks during AEV run. (Cumulative Count)
  int pMarks;               // Position of AEV, in marks.   
} 
configuration;

// ---------------------------------------------------------------------------
// Enter setup
// ---------------------------------------------------------------------------
void setup()   
{ 
  // Serial is used for Matlab detection-------------------------------------- 
  Serial.begin(115200);
  // -------------------------------------------------------------------------

  // Initiate the Wire library and join the I2C bus--------------------------- 
  Wire.begin(80);
  // -------------------------------------------------------------------------

  // Motor Pin Setup----------------------------------------------------------
  pinMode(pwmPin1,OUTPUT);       // Set Motor 1 mode
  pinMode(hblogic1a,OUTPUT);     // Set Motor 1 direction pin A mode
  pinMode(hblogic1b,OUTPUT);     // Set Motor 1 direction pin B mode
  digitalWrite(hblogic1a,HIGH);  // Set Motor 1 direction pin A HIGH
  digitalWrite(hblogic1b,LOW);   // Set Motor 1 direction pin B LOW

  pinMode(pwmPin2,OUTPUT);       // Set Motor 2 mode
  pinMode(hblogic2a,OUTPUT);     // Set Motor 2 direction pin A mode
  pinMode(hblogic2b,OUTPUT);     // Set Motor 2 direction pin B mode
  digitalWrite(hblogic2a,HIGH);  // Set Motor 2 direction pin A HIGH
  digitalWrite(hblogic2b,LOW);   // Set Motor 2 direction pin B LOW

  pinMode(pwmPin3,OUTPUT);       // Set Motor 3 mode (optional)
  pinMode(hblogic3a,OUTPUT);     // Set Motor 3 direction pin A mode
  pinMode(hblogic3b,OUTPUT);     // Set Motor 3 direction pin B mode
  digitalWrite(hblogic3a,HIGH);  // Set Motor 3 direction pin A HIGH
  digitalWrite(hblogic3b,LOW);   // Set Motor 3 direction pin B LOW
  // --------------------------------------------------------------------------

  // Quadrature Encoder Setup--------------------------------------------------
  pinMode(encoderPinA,INPUT_PULLUP);      // Set encoderPinA mode
  pinMode(encoderPinB,INPUT_PULLUP);      // Set encoderPinB mode
  attachInterrupt(1,quadEncoderA,CHANGE); // Attach interrupt to A (pin 3 == 1)
  attachInterrupt(0,quadEncoderB,CHANGE); // Attach interrupt to B (pin 2 == 0)
  // --------------------------------------------------------------------------

  // Yellow LED Pin & Button Bypass--------------------------------------------
  pinMode(yellowLedPin,OUTPUT);
  digitalWrite(yellowLedPin,LOW);
  pinMode(buttonBypass,INPUT_PULLUP);
  // --------------------------------------------------------------------------

  // Servo Pin-----------------------------------------------------------------
  aevServo.attach(9); 
  rotateServo(0); // Initialize servo to 0 degrees
  // --------------------------------------------------------------------------

  // --------------------------------------------------------------------------
  // Pre-Run Subroutine
  preProcess();
  // --------------------------------------------------------------------------

  // -------------------------------------------------------------------------
  // Execute myCode
  myCode();
  // ------------------------------------------------------------------------- 

  // -------------------------------------------------------------------------
  // Post-Run Subroutine
  postProcess();
  // -------------------------------------------------------------------------

}

void loop()                     
{  
}













