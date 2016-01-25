#ifndef DEVICE_H
#define DEVICE_H

#include <WString.h>

/**
 * @brief      The base Device class
 */
class Device
{
  String name;
  uint8_t id;

  String serialString;
  bool serialComplete = false;
  
public:
  Device(){}
  Device(const Device&){}
  Device(String,uint8_t){}
  ~Device(){}
  void init(){}
  
  uint8_t getName(){}
  uint8_t getProtocol(){}
  uint8_t getID(){}
  void serialHandler(){}
};

#endif
