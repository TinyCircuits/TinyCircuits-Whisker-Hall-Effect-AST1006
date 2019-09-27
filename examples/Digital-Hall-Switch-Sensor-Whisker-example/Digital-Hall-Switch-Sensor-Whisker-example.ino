/*************************************************************************
 * TCS40 Hall Switch  Sensor Whisker Tutorial:
 * This program prints the status of a magnet detected or not using a 
 * TCS40 Digital Hall Switch Whisker.
 * 
 * Hardware by: TinyCircuits
 * Code by: Laverena Wienclaw for TinyCircuits
 *
 * Initiated: Fri. 09/27/2019
 * Updated: 
 ************************************************************************/

// Hall Sensor variables
#define magPin A1        // Corresponds to PORT# of Whisker used (Do not use A0)
const int powerPin = 4;  // Power to Whisker
bool hallOutput = 0;     // What is directly output from Whisker
bool magnetDetected = 0; // Make sense of output 

void setup() {
  // Power Whisker
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, HIGH);

  // Set Hall Switch Pin to input
  pinMode(magPin, INPUT);
}

void loop() {
  hallOutput = digitalRead(magPin); // If no magnet, hallOutput == 1
  magnetDetected = !hallOutput; // Flip the hallOutput so magnetDetected == 1 when there is a magnet
  
  SerialUSB.println(magnetDetected);
}
