#ifndef MASTER_H
#define MASTER_H

#incldue <WString.h>

void checkSlaves();

uint8_t getInstructions(struct device device, uint8_t &instruction, uint8_t &data);

String processInstruction(uint8_t instruction, uint8_t data);

int sendResponse(struct device device, String response);

class Device
{
  String name;
  uint8_t id;
  uint8_t addr;
  uint8_t protocol;
public:
  Device();
  Device(String,uint8_t,uint8_t,uint8_t);
  ~Device();
  
};

class Master: public Device
{
private:
  
public:
  Master();
  ~Master();
  uint8_t checkSlaves();
  uint8_t getInstructions();
  String  processInstruction();
  uint8_t sendResponse();

};

class Slave: public Device
{
private:
public:
  Slave();
  ~Slave();
  
};

#endif