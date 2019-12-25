/*
 * PWM.c
 *
 *  Created on: Dec 23, 2019
 *      Author: Omar Zayed
 */

#include "PWM.h"
#include "std_types.h"
#include "registers.h"

#define Sys_Freq 										(16000000)
#define PWM_Max											(100)
#define Rising_And_Falling								(2)

#define Timer0_Clr_Mask									(0x00)
#define Timer0_PhaseCorrect_Mode_Mask					(0x40)
#define Timer0_ClrOnCmp_Mode_Mask						(0x20)
#define Timer0_ICR_TopValue								(255)


#define Timer1_Clr_Mask									(0x0000)
#define Timer1_PhaseAndFreqCorrect_Mode_Mask			(0x0010)
#define Timer1_CHA_ClrOnCmp_Mode_Mask					(0x8000)
#define Timer1_CHB_ClrOnCmp_Mode_Mask					(0x2000)


#define Timer2_Clr_Mask									(0x00)
#define Timer2_PhaseCorrect_Mode_Mask					(0x40)
#define Timer2_ClrOnCmp_Mode_Mask						(0x20)
#define Timer2_ICR_TopValue								(255)


#define		TIMER0_NO_CLOCK								(0x00)
#define		TIMER0_PRESCALER_NO							(0x01)
#define		TIMER0_PRESCALER_8							(0x02)
#define		TIMER0_PRESCALER_64							(0x03)
#define		TIMER0_PRESCALER_128						(0x04)
#define		TIMER0_PRESCALER_1024						(0x05)


#define		TIMER1_NO_CLOCK								(0x0000)
#define		TIMER1_PRESCALER_NO							(0x0001)
#define		TIMER1_PRESCALER_8							(0x0002)
#define		TIMER1_PRESCALER_64							(0x0003)
#define		TIMER1_PRESCALER_128						(0x0004)
#define		TIMER1_PRESCALER_1024						(0x0005)


#define		TIMER2_NO_CLOCK								(0x00)
#define		TIMER2_PRESCALER_NO							(0x01)
#define		TIMER2_PRESCALER_8							(0x02)
#define		TIMER2_PRESCALER_32							(0x03)
#define		TIMER2_PRESCALER_64							(0x04)
#define		TIMER2_PRESCALER_128						(0x05)
#define		TIMER2_PRESCALER_256						(0x06)
#define		TIMER2_PRESCALER_1024						(0x07)



static uint16 Timer_Lookup_Cfg[4][7] = 	{

											{TIMER0_PRESCALER_NO, TIMER0_PRESCALER_8, TIMER0_NO_CLOCK, TIMER0_PRESCALER_64, TIMER0_PRESCALER_128, TIMER0_NO_CLOCK, TIMER0_PRESCALER_1024},
											{TIMER1_PRESCALER_NO, TIMER1_PRESCALER_8, TIMER1_NO_CLOCK, TIMER1_PRESCALER_64, TIMER1_PRESCALER_128, TIMER1_NO_CLOCK, TIMER1_PRESCALER_1024},
											{TIMER1_PRESCALER_NO, TIMER1_PRESCALER_8, TIMER1_NO_CLOCK, TIMER1_PRESCALER_64, TIMER1_PRESCALER_128, TIMER1_NO_CLOCK, TIMER1_PRESCALER_1024},
											{TIMER2_PRESCALER_NO, TIMER2_PRESCALER_8, TIMER2_PRESCALER_32, TIMER2_PRESCALER_64, TIMER2_PRESCALER_128, TIMER2_PRESCALER_256, TIMER2_PRESCALER_1024}
													};

static uint16 Timer1_Prescaler = 0;



/*********************************************************************************/
/* Function: Error_State Pwm_Init(Pwm_Cfg_s_t *Pwm_Cfg);                         */
/* Type: public                                                                  */
/* Input parameters: Pwm_Cfg Structure (channel number, Prescaler)               */
/* Return type : void                                                            */
/*                                                                               */
/* Description: initialize the PWM configuration                                 */
/*********************************************************************************/
ERROR_STATUS Pwm_Init(Pwm_Cfg_s_t *Pwm_Cfg)
{
	ERROR_STATUS errorStatus = E_NOK;

	if(Pwm_Cfg != NULL)
	{
		switch(Pwm_Cfg->Channel)
		{
		case PWM_CH0 :

			TCCR0 &= Timer0_Clr_Mask;
			TCCR0 |= Timer0_PhaseCorrect_Mode_Mask;
			TCCR0 |= Timer_Lookup_Cfg[PWM_CH0][Pwm_Cfg->Prescaler];
			errorStatus = E_OK;
			break;

		case PWM_CH1A :

			TCCR1 &= Timer1_Clr_Mask;
			TCCR1 |= Timer1_PhaseAndFreqCorrect_Mode_Mask;
			Timer1_Prescaler = Timer_Lookup_Cfg[PWM_CH1A][Pwm_Cfg->Prescaler];
			TCCR1 |= Timer_Lookup_Cfg[PWM_CH1A][Pwm_Cfg->Prescaler];
			errorStatus = E_OK;
			break;

		case PWM_CH1B :

			TCCR1 &= Timer1_Clr_Mask;
			TCCR1 |= Timer1_PhaseAndFreqCorrect_Mode_Mask;
			Timer1_Prescaler = Timer_Lookup_Cfg[PWM_CH1B][Pwm_Cfg->Prescaler];
			TCCR1 |= Timer_Lookup_Cfg[PWM_CH1B][Pwm_Cfg->Prescaler];
			errorStatus = E_OK;
			break;

		case PWM_CH2 :

			TCCR2 &= Timer2_Clr_Mask;
			TCCR2 |= Timer2_PhaseCorrect_Mode_Mask;
			TCCR2 |= Timer_Lookup_Cfg[PWM_CH2][Pwm_Cfg->Prescaler];
			errorStatus = E_OK;
			break;

		default :

			errorStatus = E_NOK;
			break;
		}
	}
	else
	{
		errorStatus = E_NOK;
	}

	return errorStatus;

}

/*********************************************************************************/
/* Function: Error_State Pwm_Start(uint8_t channel,uint8_t Duty);                */
/* Type: public                                                                  */
/* Input parameters: Channel ID, Duty cycle(0:100)                               */
/* Return type : Error State                                                     */
/*                                                                               */
/* Description: starts the PWM on the dedicated channel with the required duty   */
/*				cycle and frequency                                              */
/*-------------------------------------------------------                        */
/*(IN timer 0) there are only 5 available Frequencies:                           */
/*-------------------------------------------------------                        */
/*Frequency (NO-Prescaler) --> 31,372HZ                                          */
/*Frequency (Prescaler 8) --> 3,921HZ                                            */
/*Frequency (Prescaler 64) --> 490HZ                                             */
/*Frequency (Prescaler 256) --> 122HZ                                            */
/*Frequency (Prescaler 1024) --> 31HZ                                            */
/*--------------------------------------------------------                       */
/*(IN timer 2) there are only 7 available Frequencies:                           */
/*-------------------------------------------------------                        */
/*Frequency (NO-Prescaler) --> 31,372HZ                                          */
/*Frequency (Prescaler 8) --> 3,921HZ                                            */
/*Frequency (Prescaler 32) --> 980HZ                                             */
/*Frequency (Prescaler 64) --> 490HZ                                             */
/*Frequency (Prescaler 128) --> 245HZ                                            */
/*Frequency (Prescaler 256) --> 122HZ                                            */
/*Frequency (Prescaler 1024) --> 31HZ                                            */
/*-------------------------------------------------------                        */
/*((all this calculations are for phase correct mode))                           */
/*all this calculation for F_CPU 16MHz                                           */
/*********************************************************************************/
ERROR_STATUS Pwm_Start(uint8 Channel,uint8 Duty,uint32 Frequncy)
{
	ERROR_STATUS errorStatus = E_NOK;
	switch(Channel)
	{
	case PWM_CH0 :

		OCR0 = (Duty * Timer0_ICR_TopValue) / PWM_Max ;
		TCCR0 |= Timer0_ClrOnCmp_Mode_Mask;
		errorStatus = E_OK;

		break;

	case PWM_CH1A :

		ICR1 = Sys_Freq / (Rising_And_Falling * Timer1_Prescaler * Frequncy);
		OCR1A = (Duty * Sys_Freq) / (PWM_Max * Rising_And_Falling * Timer1_Prescaler * Frequncy);
		TCCR1 |= Timer1_CHA_ClrOnCmp_Mode_Mask;
		errorStatus = E_OK;

		break;

	case PWM_CH1B :

		ICR1 = Sys_Freq / (Rising_And_Falling * Timer1_Prescaler * Frequncy);
		OCR1B = (Duty * Sys_Freq) / (PWM_Max * Rising_And_Falling * Timer1_Prescaler * Frequncy);
		TCCR1 |= Timer1_CHB_ClrOnCmp_Mode_Mask;
		errorStatus = E_OK;

		break;

	case PWM_CH2 :

		OCR2 = (Duty * Timer2_ICR_TopValue) / PWM_Max ;
		TCCR2 |= Timer2_ClrOnCmp_Mode_Mask;
		errorStatus = E_OK;

		break;

	default :

		errorStatus = E_NOK;
		break;
	}

		return errorStatus;

}

/*********************************************************************************/
/* Function: Error_State Pwm_Start(uint8_t channel,uint8_t Duty);                */
/* Type: public                                                                  */
/* Input parameters: Channel ID, Duty cycle(0:100)                               */
/* Return type : Error State                                                     */
/*                                                                               */
/* Description: updates the duty cycle and frequency of the dedicated channel    */
/*********************************************************************************/
ERROR_STATUS Pwm_Update(uint8 Channel,uint8 Duty,uint32 Frequncy)
{
	ERROR_STATUS errorStatus = E_NOK;

		switch(Channel)
		{
		case PWM_CH0 :

			OCR0 = Duty / (PWM_Max * Timer0_ICR_TopValue);
			errorStatus = E_OK;

			break;

		case PWM_CH1A :

			ICR1 = Sys_Freq / (Rising_And_Falling * Timer1_Prescaler * Frequncy);
			OCR1A = Duty / (PWM_Max * ICR1);
			errorStatus = E_OK;

			break;

		case PWM_CH1B :

			ICR1 = Sys_Freq / (Rising_And_Falling * Timer1_Prescaler * Frequncy);
			OCR1B = Duty / (PWM_Max * ICR1);
			errorStatus = E_OK;

			break;

		case PWM_CH2 :

			OCR2 = Duty / (PWM_Max * Timer2_ICR_TopValue);
			errorStatus = E_OK;

			break;

		default :

			errorStatus = E_NOK;
			break;
		}

			return errorStatus;

}

/*********************************************************************************/
/* Function: Error_State Pwm_Stop(uint8_t channel);                              */
/* Type: public                                                                  */
/* Input parameters: channel ID                                                  */
/* Return type : Error state                                                     */
/*                                                                               */
/* Description: responsible of Stopping the PWM by clearing the prescaler		 */
/*				of the corresponding channel                                     */
/*********************************************************************************/
ERROR_STATUS Pwm_Stop(uint8 Channel)
{
	ERROR_STATUS errorStatus = E_NOK;

		switch(Channel)
		{
		case PWM_CH0 :

			TCCR0 &= ~Timer0_ClrOnCmp_Mode_Mask;
			errorStatus = E_OK;

			break;

		case PWM_CH1A :

			TCCR1 &= ~Timer1_CHA_ClrOnCmp_Mode_Mask;
			errorStatus = E_OK;

			break;

		case PWM_CH1B :

			TCCR1 &= ~Timer1_CHB_ClrOnCmp_Mode_Mask;
			errorStatus = E_OK;

			break;

		case PWM_CH2 :

			TCCR2 &= ~Timer2_ClrOnCmp_Mode_Mask;
			errorStatus = E_OK;

			break;

		default :

			errorStatus = E_NOK;
			break;
		}

			return errorStatus;

}

