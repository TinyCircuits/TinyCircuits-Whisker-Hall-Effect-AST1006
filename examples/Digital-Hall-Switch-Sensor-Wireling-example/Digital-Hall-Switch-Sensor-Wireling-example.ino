/*************************************************************************
 * TCS40 Hall Switch  Sensor Wireling Tutorial:
 * This program prints the status of a magnet detected or not using a 
 * TCS40 Digital Hall Switch Wireling.
 * 
 * Hardware by: TinyCircuits
 * Code by: Laverena Wienclaw for TinyCircuits
 *
 * Initiated: Fri. 09/27/2019
 * Updated: 
 ************************************************************************/

// Hall Sensor variables
#define magPin A0        // Corresponds to PORT# of Wireling used (Do not use A0)
const int powerPin = 4;  // Power to Wireling
bool hallOutput = 0;     // What is directly output from Wireling
bool magnetDetected = 0; // Make sense of output 

// Make Serial Monitor compatible for all TinyCircuits processors
#if defined(ARDUINO_ARCH_AVR)
  #define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
  #define SerialMonitorInterface SerialUSB
#endif


void setup() {
  // Power Wireling
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, HIGH);

  // Set Hall Switch Pin to input
  pinMode(magPin, INPUT);
}

void loop() {
  hallOutput = digitalRead(magPin); // If no magnet, hallOutput == 1
  magnetDetected = !hallOutput; // Flip the hallOutput so magnetDetected == 1 when there is a magnet
  
  SerialMonitorInterface.println(magnetDetected);
}
