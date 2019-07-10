#include "Pot.h"
#include <lpc17xx.h>
#include "type_declarations.h"

void Pot_Task(void*arg){
	LPC_PINCON -> PINSEL1 &= ~(0x03<<18);
	LPC_PINCON -> PINSEL1 |= (0x01<<18);
	LPC_SC->PCONP |= (0x1000);
	LPC_ADC->ADCR = (1<<2) | (4<<8) | (1<<21);

	LPC_ADC->ADCR |= (1<<24);
	
	while (!(LPC_ADC->ADGDR & 0x80000000))
	{
	}
	osMutexAcquire(pot_val_id, osWaitForever);
	pot_val = (LPC_ADC->ADGDR & 0xFFF0) >> 4;
	osMutexRelease(pot_val_id);
}