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
#include "PWM.h"

ERROR_STATUS Exti_Try(void);


void trials(void)
{
	DIO_Cfg_s DIO_Cfg = {GPIOB, 0xFF, OUTPUT};
	DIO_init(&DIO_Cfg);
	//Timer_cfg_s Timer_cfg = {TIMER_CH2, TIMER_MODE, TIMER_INTERRUPT_MODE, TIMER_PRESCALER_64};
	//Timer_Init(&Timer_cfg);
	//ExternInt_Cfg_s Extern_Cfg = {EXTRN_INT_2, RISING_EDGE, Exti_Try};
	//ExternInt_Init(&Extern_Cfg);
	//ExternInt_Enable(EXTRN_INT_2);
	//Timer_Start(Timer_cfg.Timer_CH_NO, 250);
	Pwm_Cfg_s_t Pwm_Cfg = {PWM_CH0, PWM_PRESCALER_NO};
	Pwm_Init(&Pwm_Cfg);
	Pwm_Start(PWM_CH0, 50, 5000);
	//sei();


	while(1)
	{
		//SwDelay_ms(10);
		//DIO_Toggle(GPIOB, 0b00010110);

	}

}

ERROR_STATUS Exti_Try(void)
{
	//DIO_Toggle(GPIOB, 0b00010010);
	return E_OK;
}

ISR(TIMER2_COMP_vect)
{
	//DIO_Toggle(GPIOB, 0xFF);
}
