#include <Wire.h>

#define RPI 0x42
#define BUF 32

/*    Schematic
 * Teensy -- Arduino
 * 
 *    I2C
 * PD0(SCL)   A5(SCL)
 * PD1(SDA)   A4(SDA)
 * 
 *    Power
 * VCC   <--  5V
 * GND        GND
 * 
 * Teensy -- Rasperry
 */

void setup() {
  Wire.begin(); // no address for master
  Serial.begin(115200);

  while (!Serial);

  /* Say Hello */
  Serial.println("Initializing I2C communications...");
  Serial.print ("Master: Hello 0x");
  Serial.println(RPI, HEX);
  /* Request Response */
  Wire.requestFrom(RPI,BUF);
  /* Begin Formatting Response */
  Serial.print("0x");
  Serial.print(RPI, HEX);
  Serial.print(": ");
  /* Retrieve Response */
  while (Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.println();

//  Wire.beginTransmission(RPI);
//  Wire.write("Initializing i2c communications...");
//  Wire.write("Hello ");
//  Wire.write(RPI);
//  Wire.write("!\n");
//  Wire.endTransmission();
}

void loop() {
  
}
