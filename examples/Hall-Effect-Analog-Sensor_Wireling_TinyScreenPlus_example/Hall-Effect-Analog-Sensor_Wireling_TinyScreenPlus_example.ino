/*************************************************************************
 * A1454 Hall Effect Wireling Test Code - 
 * This program will show the basic method of interfacing with the sensor 
 * by printing out the Analog values (readings from 0 to 4096 (12-bit)) on
 * a TinyScreen+ and the Serial Monitor.
 * 
 * Hardware by: TinyCircuits
 * Written by: Laveréna Wienclaw for TinyCircuits
 * 
 * Initiated: 6/20/2018
 * Updated: 12/04/2019
 ************************************************************************/
 
#include <Wire.h>               // For I2C communication
#include <Wireling.h>           // For Interfacing with Wirelings
#include <TinyScreen.h>         // For the TinyScreen+
#include "TinyCircuits_A1454.h" // For the sensor

// Variables the for the TinyScreen+ and its background
TinyScreen display = TinyScreen(TinyScreenPlus);
int background = TS_16b_Black;

// A sensor object, the methods will be used to interface with the A1454
TinyCircuits_A1454 hall = TinyCircuits_A1454();

// Make Serial Monitor compatible for all TinyCircuits processors
#if defined(ARDUINO_ARCH_AVR)
  #define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
  #define SerialMonitorInterface SerialUSB
#endif

void setup() {
  // Begin communication 
  SerialMonitorInterface.begin(9600);
  SerialMonitorInterface.println("HALL LIBRARY TEST CODE");
  Wire.begin();
  
  // Enable & Power Wireling
  Wireling.begin();
  Wireling.selectPort(0); // This must match the port the Wireling is connected to 
                          // on the Adapter board

  // Setup and style for TinyScreen+
  display.begin();
  display.setFlip(true);
  display.setBrightness(15);
  display.setFont(thinPixel7_10ptFontInfo);
  
  hall.begin();
//  hall.wake(); 
}

void loop() {
  long mag = hall.readMag();
  long temp = hall.readTemp();
  long mode = hall.readMode();

  if (mode == 0) SerialMonitorInterface.print("AWAKE\t\t");
  else if (mode == 1) SerialMonitorInterface.print("SLEEPING\t\t");

  SerialMonitorInterface.print("Mag: ");
  SerialMonitorInterface.print(mag);
  SerialMonitorInterface.print("mW");
  SerialMonitorInterface.print('\t');

  SerialMonitorInterface.print("TempF: ");
  int tempF = ((temp * 1.8) + 32);
  SerialMonitorInterface.print(tempF);
  SerialMonitorInterface.print("°F");
  SerialMonitorInterface.print('\t');

  SerialMonitorInterface.print("TempC: ");
  SerialMonitorInterface.print(temp);
  SerialMonitorInterface.println("°C");
//  hall.sleep();
  delay(250); // Makes TinyScreen+ updates prettier

  printToScreen(mag, temp, mode);
  //updateLeds(mag);
}

// Prints the hall sensor values to the TinyScreen+
void printToScreen(int mag, int temp, int mode) {
  // This will make the screen look a little unsteady but is needed in order
  // to clear old values 
  display.clearScreen();

  display.fontColor(TS_8b_White, background);
  display.setCursor((48 - (display.getPrintWidth("Linear Hall Test")) / 2), 0);
  display.print("Linear Hall Test");
  
  display.fontColor(TS_8b_Blue, background);
  display.setCursor(0, 16);
  display.print("Mag = ");
  display.print(mag);

  display.fontColor(TS_8b_Red, background);
  display.setCursor(0, 28);
  display.print("TempC = ");
  display.print(temp);

  display.fontColor(TS_8b_Green, background);
  display.setCursor(0, 40);
  display.print("Mode = ");
  display.print(mode);
}
