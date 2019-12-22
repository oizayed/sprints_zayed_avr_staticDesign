/*
 * Timer.h
 *
 *  Created on: Dec 21, 2019
 *      Author: New User
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "Common.h"


#define		TIMER_CH0					0
#define		TIMER_CH1					1
#define		TIMER_CH2					2

#define		TIMER_MODE					0
#define		COUNTER_UP_MODE				1
#define		COUNTER_DOWN_MODE			2

#define		TIMER_POLLING_MODE			0
#define		TIMER_INTERRUPT_MODE		1

#define		TIMER_NO_CLOCK				0
#define		TIMER_PRESCALER_NO			1
#define		TIMER_PRESCALER_8			2
#define		TIMER_PRESCALER_32			3
#define		TIMER_PRESCALER_64			4
#define		TIMER_PRESCALER_128			5
#define		TIMER_PRESCALER_256			6
#define		TIMER_PRESCALER_1024		7



typedef struct Timer_cfg_s
{
	uint8 Timer_CH_NO;
	uint8 Timer_Mode;
	uint8 Timer_Polling_Or_Interrupt;
	uint8 Timer_Prescaler;

}Timer_cfg_s;


ERROR_STATUS Timer_Init(Timer_cfg_s* Timer_cfg);
ERROR_STATUS Timer_Start(uint8 Timer_CH_NO, uint16 Timer_Count);
ERROR_STATUS Timer_Stop(uint8 Timer_CH_NO);
ERROR_STATUS Timer_GetStatus(uint8 Timer_CH_NO, bool* Data);
ERROR_STATUS Timer_GetValue(uint8 Timer_CH_NO, uint16* Data);









#endif /* TIMER_H_ */
