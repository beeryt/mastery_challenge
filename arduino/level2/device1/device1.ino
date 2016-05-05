#include <Wire.h>
/* Arbitrary device addresses for I2C */
#define DEVICE1 0x33
#define DEVICE2 0x44

#define LOTEMP 6500
#define HITEMP 8000

#define LEDPIN 11

void setup() {
  /* Initialize the USART serial interface */
	Serial.begin(115200); // I like it fast!
 /* Wait for the computer to connect */
 while (!Serial);

 /* Turn on I2C interface */
  Wire.begin(DEVICE1);
}

void loop() {
	delay(100);
}

/**
 * Do something when we receive a serial command
 */
void serialEvent() {
  String command = "";
  
  while (Serial.available())
    command += (char)Serial.read();

  /* Get command vs data */
    
  if (command == "PWM" && command.length() == 4) {
    byte val = command[3];
    if (val > 255 || val < 0)
      Serial.println("Value out of range?");
    analogWrite(LEDPIN, val);
  }
  else if (command == "TEMP") {
    /* Get temp from Device 2 */
    int data = getTemp();
    /* Format response string */
    Serial.print("The temperature is ");
    Serial.print(data/100); // whole number
    byte dec = data%100;    // decimal
    if (dec < 10)
      Serial.print("0");    // leading zero
    Serial.println(dec);
  }
  else if (command == "PWMTEMP") {
    /* Get temp from Device 2 */
    int temp = getTemp();
    /* remap value to pwm range */
    int val = map(temp, LOTEMP, HITEMP, 0, 255);
    /* send new value to pwm */
    analogWrite(LEDPIN, val);

    Serial.print("The temperature is ");
    Serial.print(temp/100);
    byte dec = temp%100;
    if (dec < 10)
      Serial.print("0");
    Serial.println(dec);
  }
  else {
    Serial.print("Unrecognized command: ");
    Serial.println(command);
  }
}

int getTemp() {
  /* Let Device 2 know a temp conversion is starting */
  Wire.beginTransmission(DEVICE2);
  Wire.write("TEMP");
  Wire.endTransmission();

  /* Get the temp data from Device 2 */
  int data = 0;
  Wire.requestFrom(DEVICE2, sizeof(data));
  data += (byte) Wire.read();    // lo byte
  Serial.println(data);
  data += (byte) Wire.read()<<8; // hi byte
  Serial.println(data);
  return data;
}

