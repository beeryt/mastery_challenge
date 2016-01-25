#ifndef SLAVE_H
#define SLAVE_H

#include <WString.h>
#include "device.h"

/**
 * @brief      { class_description }
 */
class Slave  : public Device
{
private:
  int instruction; // instruction:addr
  Device master;
  int numDevices;
  Device *deviceList;
public:
  Slave(const Device &t, const Device &m, const Device *l, const int n) : Device(t) {
    master = m;
    numDevices = n;
    deviceList = new Device [numDevices];
    for (int i = 0; i < numDevices; ++i)
      deviceList[i] = l[i];
  }
  ~Slave(){
    delete [] deviceList;
    deviceList = NULL;
    numDevices = 0;
  }

  uint8_t run();
  String processInstruction();
  void requestHandler();
  void receiveHandler(int numBytes);
  
};

#endif
