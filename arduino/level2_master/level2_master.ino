#include <Wire.h>
#include <SPI.h>
#include <OneWire.h>
#include "master.h"

#define TEENSY_ADDR 0x01
#define SENSOR_PIN 0x04

/*
 *           00xxyyyy
 * protocol----^^
 * device#-------^^^^
 * address---^^^^^^^^
 * 
 */

#define MASTER
//#define SLAVE

#define UNO_NAME "Arduino Uno"
#define UNO_ID 0x21 // I2C device 1
#define TNY_NAME "Teensy 2.0"
#define TNY_ID 0x11 // USART device 1
#define RPI_NAME "Raspberry Pi 2"
#define RPI_ID 0x31 // SPI device 1

const Device RPI(RPI_NAME, RPI_ID);
const Device UNO(UNO_NAME, UNO_ID);
const Device TNY(TNY_NAME, TNY_ID);
//const Device SER(SER_NAME, SER_ID);

const int numSlaves = 2;
const Device slaves[] = {RPI,UNO};

#ifdef MASTER
Master device(TNY,slaves,numSlaves);
#elif SLAVE
Slave device(UNO,TNY,slaves,numSlaves);
#endif

OneWire ds(SENSOR_PIN);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  SPI.begin();

  device.init();
}

void loop() {
  delay(100);
  device.run();
}

void serialEvent() {
  device.serialHandler();
}



