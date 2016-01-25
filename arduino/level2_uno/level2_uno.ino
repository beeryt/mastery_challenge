#include <Wire.h>

#define RPI 0x42
#define UNO 0x10
#define TNY 0x20

#define DEVICE UNO
//#define VCC 3.3
#define VCC 5.0

/* Schematic
 *
 * **I2C** 
 * A5(SCL)
 * A4(SDA)
 * 
 */

const byte NOCMD   = 0x00;  // No Command
const byte DS18B20 = 0x01;  // Teensy Temperature
const byte RPITEMP = 0x02;  // Raspberry Pi Temperature
const byte RPITIME = 0x03;  // Raspberry Pi Time
const byte UNOADC0 = 0xA0;  // Uno ADC's span 0-5?
const byte UNOADC1 = 0xA1;
const byte UNOADC2 = 0xA2;
const byte UNOADC3 = 0xA3;
const byte TNYADC0 = 0xF0;  // Teensy ADC's span 0-A in hex
const byte TNYADC4 = 0xF4;
const byte TNYADCA = 0xFA;
// ...
const byte TNYBDCT = 0xFF;  // Teensy Broadcast

String broadcast = "";
String serialString = "";
boolean serialComplete = false;
byte command;

void setup() {
  // Start and wait for USART
  Serial.begin(115200);
  while (!Serial);
  Serial.print("Device 0x");
  Serial.print(DEVICE, HEX);
  Serial.println(" ready...");
  

  Wire.begin(DEVICE);
  Wire.onReceive(receiveHandler);
  Wire.onRequest(requestHandler);

  /* Initialize variables */
  serialString.reserve(100);
  command = NOCMD;
}

void loop() {
  if (serialComplete) {
    // Split into command, arg
    byte indexArg = serialString.indexOf('(');
    String strCmd = serialString.substring(0,indexArg);
    String strArg = serialString.substring(indexArg + 1, serialString.length() - 1);
    strCmd.toLowerCase();
    strArg.toLowerCase();

    boolean invalid = false; // whether command is invalid or not

//    Serial.print("Command: ");
//    Serial.println(strCmd);
//    Serial.print("Argument: ");
//    Serial.println(strArg);
    
    /* getTemp(x) command */
    if (strCmd == "gettemp") {
      if (strArg == "pi")
        command = RPITEMP;
      else if (strArg == "")
        command = DS18B20;
      else
        invalid = true;
    }
    /* unoADC(x) command */
    else if (strCmd == "unoadc") {
      command = NOCMD; // No need to send a command when this is a local request!!
      byte i = strArg.toInt();
      if (i)
        Serial.println(readADC(i));
      else
        invalid = true;
    }
    /* tnyADC(x) command */
    else if (strCmd == "tnyadc") {
      byte i = strArg.toInt();
      // doesn't catch invalid str because 0 is used
      command = TNYADC0;
      if (i <= 10)
        command += i;
      else {
        command = NOCMD;
        invalid = true;
      }
    }
    /* broadcast */
    else if (strCmd == "broadcast") {
      String device = String(DEVICE, HEX);
      broadcast = "";
      broadcast = "Broadcast from " + device + ": " + strArg;
      command = TNYBDCT;
    }
    /* Debug */
    else if (strCmd == "debug") {
      command = strArg.toInt();
    }
    /* No valid command */
    else {
      command = NOCMD;
      Serial.print("Unrecognized command: ");
      Serial.println(serialString);
    }
    /* Invalid argument */
    if (invalid) {
      command = NOCMD;
      Serial.print("Unrecognized arg: ");
      Serial.println(serialString);
    }
    /* Clear the string */
    serialString = "";
    serialComplete = false;
  }
  
  delay(100);
}

void receiveHandler(int numBytes) {
  Serial.print("Recieving ");
  Serial.print(numBytes);
  Serial.println(" Bytes...");

  while (Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.println();
}

void requestHandler() {
  if (command)
   Serial.println(command, HEX);
  Wire.write(command);
  command = NOCMD;
}

void serialEvent() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c != '\n')
      serialString += c;
  }
  serialComplete = true;
}

String readADC(byte i) {
  // Read the specified pin
  int val = analogRead(i);
  // map the 10-bit reading to VCC (mV)
  val = map(val,0,1023,0,VCC * 1000);

  // Format a string
  String str = "";
  str += "Pin A";
  str += i;
  str += " reads... ";
  str += val;
  str += " mV";
  
  return str;
  
}

