//#include <Wire.h>
//#include <SPI.h>
//#include <OneWire.h>
////OneWire ds(4);
//
//
//#include "constants.h"
//
///********************************************
// * 
// * Device Specific
// * 
// ********************************************/
//
////const int numSlaves = 2;
////const struct device slave[] = {
//////  RPI,
////  UNO
////};
//
//typedef uint8_t bytse;
//
//bytse adsf = 0;
//
///*void setup() {
//  Serial.begin(9600);
//  pinMode(11,OUTPUT);
//  digitalWrite(11,HIGH);
//  
//  Wire.begin(DEVICE.addr);
//}
//
//void loop() {
//  checkSlaves();
//  delay(100);
//}
//
//void checkSlaves() {
//  for (int i = 0; i < numSlaves; ++i) {
//    struct device s = slave[i];
//    byte inst, data;
//    inst = data = 0x00;
//
//    getInstruction(s, &inst, &data);
//    String r = processInstruction(inst,data);
//    sendResponse(s, r);
//  }
//}
//*/
//String processInstruction(byte inst, byte addr) {
//  String response = "";
//  response.reserve(BUFFER);
//
//  /* Get the command type */
//  byte type = inst >> 8; // shift out low nibble
//  type <<= 8;           // shift in 0 nibble
//  /* Get the pin */
//  byte pin = inst << 8; // shift out the high nibble
//  pin >>= 8;           // shift back to regular
//
//  switch (type) {
//    case cmdTMP:
//      response += getTemp(inst, addr);
//      break;
//    case cmdADC:
//      response += getADC(inst, addr);
//      break;
//    case cmdPWM:
//      response += setPWM(inst, addr);
//      break;
//    case cmdBRD:
////      String message = getMessage(addr);
////      response += broadcast(message);
//      break;
//    default:
//      response += who(DEVICE) + ": Unrecognized command: 0x" + String(inst,HEX);
//      break;
//  }
//}
//
//
//
//
//String getTemp(byte i, byte a) {
//  String r = "";
//  if (a == DEVICE.addr && !DEVICE.temp) {
//    r += who(DEVICE) + "Does not have a temperature sensor!\n";
//  }
//  else if (a != DEVICE.addr) {
//    r += who(DEVICE) + "Sending command to " + who(a) + "...\n";
//    r += pass(i,a);
//  }
//  else if (DEVICE.temp) {
//    String res = who(DEVICE) + "Accessing OneWire Device...\n";
//    byte addr[8];
//    int i = 0;
//    ds.reset_search();
//    while (ds.search(addr)) {
//      ++i;
//      ds.reset();
//      ds.select(addr);
//      ds.write(0x4E); // configuration
//      ds.write(0x00);
//      ds.write(0x00);
//      ds.write(0x3F); // resolution
//      ds.reset();
//      ds.select(addr);
//      ds.write(0x44, 1); //convert parasitic
//      delay(1000);
//      ds.reset();
//      ds.select(addr);
//      ds.write(0xBE); // read scratchpad
//      byte data[9];
//      for (int i = 0; i < 9; ++i)
//        data[i] = ds.read();
//      int TReading = (data[1] << 8) + data[0];
//      if (TReading & 0x8000)
//        TReading = (TReading ^ 0xFFFF) + 1;
//      int Tc = (6 * TReading) + TReading / 4;
//      int Tf = Tc * 1.8 + 3200;
//
//      /* Format string */
//      // who: TempX: 65.64 F\n
//      res += who(DEVICE) + "Temp" + i;
//      res += ": " + Tf/100;
//      res += ".";
//      int dec = Tf%100;
//      if (dec < 10)
//        res += "0";
//      res += dec + " F\n";
//    }
//    return res;
//  }
//  else
//    r += who(DEVICE) + "getTemp(): Critical Error!\n";
//}
//
//String getADC(byte i, byte a) {
//  String r = "";
//  if (a == DEVICE.addr && !DEVICE.temp) {
//    r += who(DEVICE) + "Does not have an ADC!\n";
//  }
//  else if (a != DEVICE.addr) {
//    r += who(DEVICE) + "Sending command to " + who(a) + "...\n";
//    r += pass(i,a);
//  }
//  else if (DEVICE.temp) {
//    String res = who(DEVICE) + "Checking the voltage at pin A" + i + "...\n";
//  
//    /* Read the specified pin */
//    int val = analogRead(i);
//    val = map(val, 0, 1023, 0, VCC * 1000); // map the 10-bit value to VCC in mV
//    /* Format the output string */
//    res += who(DEVICE) + "Pin A" + i + ": ";
//    /* Split the number into whole... */
//    res += ": " + val/100;
//    res += ".";
//    /* and decimal parts */
//    int dec = val%100;
//    if (dec < 10) // don't forget leading zero!
//      res += "0";
//    res += dec + " V\n"; // and units!
//  
//    return res;
//  }
//  else
//    r += who(DEVICE) + "getADC(): Critical Error!\n";
//}
//
//String setPWM(byte i, byte a) {
//  String r = "";
//  if (a == DEVICE.addr && !DEVICE.temp) {
//    r += who(DEVICE) + "Does not have a PWM!\n";
//  }
//  else if (a != DEVICE.addr) {
//    r += who(DEVICE) + "Sending command to " + who(a) + "...\n";
//    r += pass(i,a);
//  }
//  else if (DEVICE.temp) {
//    // local
//  }
//  else
//    r += who(DEVICE) + "setPWM(): Critical Error!\n";
//}
//
//
//void getInstruction(struct device s, byte *i, byte* d) {
//  switch (s.protocol) {
//    case protoSPI: {
//      break;
//    }
//    case protoI2C: {
//      int numBytes = Wire.requestFrom(s.addr, (byte)2);
//      if (numBytes == 2) {
//        *i = Wire.read();
//        *d = Wire.read();
//      }
//      break;
//    }
//    case proUSART: {
//      break;
//    }
//    default:
//      break;
//  }
//}
//
///********************************************
// * 
// * Communications
// * 
// ********************************************/
//
//void sendResponse(struct device s, String response) {
//  switch (s.protocol) {
//    case protoSPI: {
//      break;
//    }
//    case protoI2C: {
//      Wire.beginTransmission(s.addr);
//      Wire.write(response.c_str());
//      Wire.endTransmission();
//      break;
//    }
//    case proUSART: {
//      Serial.println(response);
//      break;
//    }
//    default:
//      break;
//  }
//}
//
//String pass(byte i, byte a) {
//  struct device d = getDevice(a);
//  switch (d.protocol) {
//    case protoSPI: {
//      break;
//    }
//    case protoI2C: {
//      Wire.beginTransmission(d.addr);
//      Wire.write(0x00);
//      Wire.endTransmission();
//      int numBytes = Wire.requestFrom(d.addr, PASS);
//      String r = "";
//      while (Wire.available()) {
//        r += Wire.read();
//      }
//      return r;
//    }
//    case proUSART: {
//      break;
//    }
//    default:
//      break;
//  }
//}
//
///********************************************
// * 
// * Getting what we want
// * 
// ********************************************/
//
//String who(struct device d) {
//  String ret = "0x" + String(d.addr,HEX) + ": ";
//  return ret;
//}
//
//String who(byte addr) {
//  String ret = "0x" + String(addr,HEX) + ": ";
//  return ret;
//}
//
//struct device getDevice(byte a) {
//}
//
//
////String serialString = "";
////boolean serialComplete = false;
//
////void serialEvent() {
////  while (Serial.available()) {
////    char c = Serial.read();
////    if (c != '\n')
////      serialString += c;
////  }
////  serialComplete = true;
////}
//
//

