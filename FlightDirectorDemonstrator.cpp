#include "GenericUsbClient.h"

void setOutputBit(transfer_object_t value, uint8 bit) {
	digitalWrite(bit, value.asInt > 0);
}

const dataref_subscription_t SUBSCRIPTIONS[] = {
		{"laminar/B738/autopilot/master_capt_status", INT_4BYTES, setOutputBit, LED_BUILTIN}
};

const uint8 SUBSCRIPTIONS_LENGTH = length(SUBSCRIPTIONS);


