/*************************************************************************
 * TCS40 Hall Switch Sensor Wireling Tutorial:
 * This program prints the status of a magnet detected or not using a 
 * TCS40 Digital Hall Switch Wireling.
 * 
 * Hardware by: TinyCircuits
 * Code by: Laveréna Wienclaw for TinyCircuits
 *
 * Initiated: 09/27/2019
 * Updated: 12/04/2019
 ************************************************************************/

#include <Wireling.h> // For interfacing with Wirelings

// Hall Sensor variables
#define magPin A0        // Corresponds to PORT# of Wireling used (Do not use A0)
bool hallOutput = 0;     // What is directly output from Wireling
bool magnetDetected = 0; // Make sense of output 

// Make Serial Monitor compatible for all TinyCircuits processors
#if defined(ARDUINO_ARCH_AVR)
  #define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
  #define SerialMonitorInterface SerialUSB
#endif

void setup() {
  SerialMonitorInterface.begin(9600);
  
  // Enable & power Wireling
  Wireling.begin();

  // Set Hall Switch Pin to input
  pinMode(magPin, INPUT);
}

void loop() {
  hallOutput = digitalRead(magPin); // If no magnet, hallOutput == 1
  magnetDetected = !hallOutput; // Flip the hallOutput so magnetDetected == 1 when there is a magnet
  
  SerialMonitorInterface.println(magnetDetected);
}
