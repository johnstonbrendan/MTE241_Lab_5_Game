#include "Joy.h"

void Joy_Task (void*arg){
	uint8_t joystickValues = 0x0;

	// x j1 j2 j3 j4 x x button
	joystickValues |= ((LPC_GPIO1 -> FIOPIN) & 0x7900000) >> 20;
	osMutexAcquire(joy_val_id,osWaitForever);
	if(!(joystickValues & 0x40)) { 
		joy_in->left++;
	} 
	else if(!(joystickValues & 0x20)) { 
		joy_in->down++;
	} 
	else if(!(joystickValues & 0x10)) { 
		joy_in->right++;
	} 
	else if(!(joystickValues & 0x08)) { 
		joy_in->up++;
	}
	osMutexRelease(joy_val_id);
}