/*
 * trials.c
 *
 *  Created on: Dec 22, 2019
 *      Author: Omar Zayed
 */

#include "../mcal/DIO/DIO.h"
#include "../common/softwareDelay/softwareDelay.h"
#include "../mcal/Timer/Timer.h"
#include "../common/interrupts.h"
#include "ExternalInterrupt.h"

ERROR_STATUS Exti_Try(void);


void trials(void)
{
	DIO_Cfg_s s1;
	s1.GPIO = GPIOB;
	s1.dir = OUTPUT;
	s1.pins = 0b00010010;
	DIO_init(&s1);
	Timer_cfg_s t0;
	t0.Timer_CH_NO = TIMER_CH2;
	t0.Timer_Mode = TIMER_MODE;
	t0.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;
	t0.Timer_Prescaler = TIMER_PRESCALER_64;
	ExternInt_Cfg_s Extern_Cfg = {EXTRN_INT_2, RISING_EDGE, Exti_Try};
	ExternInt_Init(&Extern_Cfg);
	ExternInt_Enable(EXTRN_INT_2);
	//Timer_Init(&t0);
	//Timer_Start(t0.Timer_CH_NO, 250);
	sei();


	while(1)
	{
		//SwDelay_ms(10);
		//DIO_Toggle(GPIOB, 0b00010110);

	}

}

ERROR_STATUS Exti_Try(void)
{
	DIO_Toggle(GPIOB, 0b00010010);
	return E_OK;
}

ISR(TIMER2_COMP_vect)
{
	//DIO_Toggle(GPIOB, 0b00010110);
}
