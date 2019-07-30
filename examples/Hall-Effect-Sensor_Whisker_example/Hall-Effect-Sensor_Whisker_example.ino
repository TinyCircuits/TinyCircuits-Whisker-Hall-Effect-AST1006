/*************************************************************************
 * A1454 WhiskerBoard Test Code - 
 * This program will show the basic method of interfacing with the sensor 
 * by printing out the Analog values (readings from 0 to 4096 (12-bit)) on
 * a TinyScreen+ and the Serial Monitor.
 * 
 * Hardware by: TinyCircuits
 * Written by: Laverena Wienclaw for TinyCircuits
 * 
 * Initiated: Mon. 6/20/2018
 * Updated: Tue. 07/03/2018
 ************************************************************************/
#include <Wire.h>               // For I2C communication
#include <TinyScreen.h>         // For the TinyScreen+
#include "TinyCircuits_A1454.h" // For the sensor

// Variables the for the TinyScreen+ and its background
TinyScreen display = TinyScreen(TinyScreenPlus);
int background = TS_16b_Black;

// A sensor object, the methods will be used to interface with the A1454
TinyCircuits_A1454 hall = TinyCircuits_A1454();

// The power pin for the 
const int powerPin = 4;

void setup() {
  // Begin communication 
  SerialUSB.begin(9600);
  SerialUSB.println("HALL LIBRARY TEST CODE");
  Wire.begin();
  
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, HIGH);

  // Setup and style for TinyScreen+
  display.begin();
  display.setFlip(true);
  display.setBrightness(15);
  display.setFont(thinPixel7_10ptFontInfo);

  selectPort(0); // This must match the port the Whisker is connected to 
                 // on the Adapter board
  hall.begin();
//  hall.wake(); 
}

void loop() {
  long mag = hall.readMag();
  long temp = hall.readTemp();
  long mode = hall.readMode();

  if (mode == 0) SerialUSB.print("AWAKE\t\t");
  else if (mode == 1) SerialUSB.print("SLEEPING\t\t");

  SerialUSB.print("Mag: ");
  SerialUSB.println(mag);
  SerialUSB.print("mW");
  SerialUSB.print('\t');

  SerialUSB.print("TempF: ");
  int tempF = ((temp * 1.8) + 32);
  SerialUSB.print(tempF);
  SerialUSB.print("°F");
  SerialUSB.print('\t');

  SerialUSB.print("TempC: ");
  SerialUSB.print(temp);
  SerialUSB.println("°C");
//  hall.sleep();
 // delay(100);

  printToScreen(mag, temp, mode);
  //updateLeds(mag);
}

// **This function is necessary for all Whisker boards attached through an Adapter board**
// Selects the correct address of the port being used in the Adapter board
void selectPort(int port) {
  Wire.beginTransmission(0x70);
  Wire.write(0x04 + port);
  Wire.endTransmission();
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
