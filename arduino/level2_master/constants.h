#include <Arduino.h>
#ifndef CONSTANT_H
#define CONSTANT_H

#define BUFFER 0xFF
/* Command list */      // When applicable, the lower nibble holds the pin number
#define cmdNOP 0x00 // No command
#define cmdADC 0xA0 // also needs addr
#define cmdPWM 0x50 // also needs addr
#define cmdTMP 0xC0 // also needs addr
#define cmdBRD 0xF0 // Always broadcasts through master

const byte PASS = 0;

#define protoSPI 1
#define protoI2C 2
#define proUSART 3

struct device {
  byte addr;
  byte protocol;
  bool adc;
  bool pwm;
  bool temp;
  bool brdcst;
};

//struct device RPI = {
//  0x42,
//  protoSPI,
//  false,
//  false,
//  true,
//  false
//};
//struct device UNO = {
//  0x10,
//  protoI2C,
//  true,
//  true,
//  false,
//  false
//};
//struct device TNY = {
//  0x20,
//  proUSART,
//  true,
//  true,
//  true,
//  true
//};
#define DEVICE TNY
#define VCC 5.0

#endif
