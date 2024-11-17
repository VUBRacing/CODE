#ifndef CAN_LIBRARY
#define CAN_LIBRARY

#include "Arduino.h"
#include <vector>

struct Message {
	uint8_t id;
	uint16_t packet_size;
	std::vector<uint8_t> data_field;
};

class CANLibrary {
public:

	virtual bool init();
	virtual void send(Message message);
	virtual Message read();


};

#endif