// --------------------------------------
// SoftI2C_Scanner
// By Shervin Emami (http://shervinemami.info/), Jan 2017.
// Based on version 6 of I2C_Scanner sample code, taken from November 27, 2015.
//
// This sketch tests the standard 7-bit addresses, using software I2C bit-banging,
// instead of the standard Wire Arduino library that can make use of I2C hardware.
// Devices with higher addresses than 127 won't be seen properly.
// This program is useful for ATtiny microcontrollers that don't have full I2C hardware.
//

// I2C library:
#include "SoftI2CMaster.h"
const int sdaPin = 4; // Arduino GPIO 4 is physical pin 7 of ATtiny841.
const int sclPin = 6; // Arduino GPIO 6 is physical pin 9 of ATtiny841.
SoftI2CMaster i2c = SoftI2CMaster( sclPin, sdaPin, 0 );

// Default of 9600 bps can be too slow to show all the data we want, so 115200 might be better.
#define SERIAL_BAUD_RATE  9600


void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);
  delay(1000);  // Wait for 1 second before starting the program.
  Serial.println();
  Serial.println("Starting the Soft I2C Scanner.");
}
 
 
void loop()
{
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // Use the return value of i2c.beginTransmission to see if
    // a device did acknowledge to the address.
    // Note that when using the standard Arduino Wire library you would check Wire.endTransmission.
    error = i2c.beginTransmission(address);
    i2c.endTransmission();

    // If no error was reported, show the device we found!
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println(" !");
 
      nDevices++;
    }
  }
  
  if (nDevices == 0)
  {
    Serial.println("No I2C devices found.\n");
  }
  else
  {
    Serial.print("Found ");
    Serial.print(nDevices);
    Serial.println(" devices!\n");
  }
 
  delay(5000);           // wait 5 seconds for next scan
}
