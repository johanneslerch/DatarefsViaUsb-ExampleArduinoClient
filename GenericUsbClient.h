#ifndef _UsbExample_H_
#define _UsbExample_H_
#include "Arduino.h"

typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long uint32;
typedef signed long sint32;
typedef double float32;

#define BUFFER_SIZE 256u
#define MAX_DATAREF_LABEL_LENGTH 128u

#define TRANSFER_VALUE_SIZE 4

#define length(arr) (sizeof(arr)/sizeof(*arr))

typedef union {
	float32 asFloat;
	sint32 asInt;
} transfer_object_t;

typedef enum {
	INT_4BYTES,
	FLOAT_4BYTES
} datatype_t;

typedef enum {
	INIT, //no additional information in message
	UPDATE // messages must be followed by 1 byte representing the index of the dataref (order of subscriptions), then sizeof(datarefValue_t) bytes representing the value of the dataref
} messageToClient_t;

typedef enum {
	SUBSCRIBE, //messages must be followed by 1 byte representing the datatype_t, then a string representing the name of the dataref
	COMMAND, //messages must be followed by string representing the name of the command
	SET_DATAREF //messages must be followed by 1 byte representing the datatype_t, sizeof(datarefValue_t) bytes representing the new value, then a string representing the name of the dataref
} messageFromClient_t;

typedef struct {
	char label[MAX_DATAREF_LABEL_LENGTH];
	datatype_t type;
	void (* callback)(transfer_object_t, uint8);
	uint8 configData;
} dataref_subscription_t;


extern const dataref_subscription_t SUBSCRIPTIONS[];
extern const uint8 SUBSCRIPTIONS_LENGTH;

#endif /* _UsbExample_H_ */
