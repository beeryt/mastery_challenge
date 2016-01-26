#include <OneWire.h>
#include <Wire.h>/* Arbitrary device addresses for I2C */
#define DEVICE1 0x33
#define DEVICE2 0x44

#define DSPIN 3

OneWire ds(DSPIN);

String command = "";
int temp = 0;

void setup() {
  /* Turn on I2C interface */
  Wire.begin(DEVICE2);
  Serial.begin(115200);

  /* Attach handles */
  Wire.onRequest(requestHandler);
  Wire.onReceive(receiveHandler);
}

void loop() {
  delay(100);
}

void requestHandler() {
  if (command == "TEMP")
    temp = getTemp();
  command = "";
  Serial.println(temp);
  byte templo = (temp<<8)>>8;
  byte temphi = (temp>>8)<<8;
  Wire.write(templo);
  Wire.write(temphi);
}

void receiveHandler(int numBytes) {
  command = "";
  while (Wire.available())
    command += (char)Wire.read();  
  Serial.println(command);
}

int getTemp() {
  // Poll each sensor
  byte addr[8];
  ds.reset_search();
  while (ds.search(addr))
  {
    // Test power mode
    ds.reset();
    ds.select(addr);
    ds.write(0xB4);
    byte mode = ds.read();
    Serial.print("The mode: ");
    Serial.println(mode);
    // Start Conversion
    ds.reset();
    ds.select(addr);
    ds.write(0x44,1); // Using parasitic power
    // Wait for conversion
    delay(1000); // Parasitic power requires sequential conversions
    // Read data
    ds.reset();
    ds.select(addr);
    ds.write(0xBE);
    byte data[9];
    for (int i = 0; i < 9; ++i)
      data[i] = ds.read();
    //Convert data
    int TReading = (data[1] << 8) + data[0];
    if (TReading & 0x8000) // if negative
      TReading = (TReading ^ 0xFFFF) + 1; // Two's Complement
    int Tc_100 = (6 * TReading) + TReading / 4;

    return Tc_100 * 1.8 + 3200; // Temperature Farenheight
  }
}

