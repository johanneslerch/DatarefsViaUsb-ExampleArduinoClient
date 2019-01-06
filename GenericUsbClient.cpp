#include "GenericUsbClient.h"

uint8 buffer[BUFFER_SIZE];
uint8 buffer_usage = 0u;


void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(128000);
}

static void registerDatarefSubscriptions() {
	for(uint8 i=0; i < SUBSCRIPTIONS_LENGTH; i++) {
		uint8 data[BUFFER_SIZE] = {0};
		data[0] = SUBSCRIBE;
		data[1] = SUBSCRIPTIONS[i].type;
		strcpy((char*)&data[2], SUBSCRIPTIONS[i].label);
		Serial.write(data, 2 + strlen(SUBSCRIPTIONS[i].label));
	}
}

void loop()
{
	while(Serial.available()) {
		buffer[buffer_usage] = Serial.read();
		buffer_usage++;

		switch(buffer[0]) {
		case INIT:
			registerDatarefSubscriptions();
			buffer_usage = 0;
			break;
		case UPDATE:
			if(buffer_usage == 2+TRANSFER_VALUE_SIZE) {
				uint8 index = buffer[1];
				transfer_object_t value = {0};
				memcpy(&value, &buffer[2], TRANSFER_VALUE_SIZE);
				SUBSCRIPTIONS[index].callback(value, SUBSCRIPTIONS[index].configData);
				buffer_usage = 0;
			}
			break;
		default:
			buffer_usage = 0;
		}
	}
}
