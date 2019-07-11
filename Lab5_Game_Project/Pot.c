#include <lpc17xx.h>
#include "Pot.h"
#include "type_declarations.h"
#include <stdbool.h>
#include <cmsis_os2.h>

uint32_t pot_val;
osMutexId_t pot_val_id;


void Pot_Task(void*arg){
	while(true)
	{
		// perhaps use event flag or something to block this when pot input not needed?
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
		osThreadYield();
		//osDelay(osKernelGetSysTimerFreq() / EXEC_FREQ);
	}
}