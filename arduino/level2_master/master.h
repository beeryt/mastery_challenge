#ifndef MASTER_H
#define MASTER_H

#include <WString.h>
#include "device.h"

class Master: public Device
{
private:
  int numSlaves;
  Device *slaveList;
public:
  Master(const Device &m, const Device *s, const int n) : Device(m) {
    numSlaves = n;
    slaveList = new Device [numSlaves];
    for (int i = 0; i < numSlaves; ++i)
      slaveList[i] = s[i];
  }
  ~Master(){
    delete [] slaveList;
    slaveList = NULL;
    numSlaves = 0;
  }
  uint8_t run(){}
  uint8_t getInstructions(){}
  String  processInstruction(){}
  uint8_t sendResponse(){}


};

#endif
