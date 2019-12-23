/*
 * Timer.c
 *
 *  Created on: Dec 22, 2019
 *      Author: Omar Zayed
 */



#include "Timer.h"
#include "DIO.h"
#include "registers.h"
#include "common_macros.h"


#define 	Timer0_CMP_Mask						0x08
#define 	Timer0_TCNT_INIT_Mask				0x00
#define 	Timer0_Int_CLR_Mask					0b11111100
#define 	Timer0_Polling_Int_Mask				0b00000000
#define 	Timer0_Interrupt_Int_Mask			0b00000010
#define 	Timer0_TIFR_OCBit					BIT1

#define 	Timer1_CMP_Mask						0x0008
#define 	Timer1_TCNT_INIT_Mask				0x0000
#define 	Timer1_Int_CLR_Mask					0b11000011
#define 	Timer1_Polling_Int_Mask				0b00000000
#define 	Timer1_Interrupt_Int_Mask			0b00010000
#define 	Timer1_TIFR_OCBit					BIT4


#define 	Timer2_CMP_Mask						0x08
#define 	Timer2_TCNT_INIT_Mask				0x00
#define 	Timer2_Int_CLR_Mask					0b00111111
#define 	Timer2_Polling_Int_Mask				0b00000000
#define 	Timer2_Interrupt_Int_Mask			0b10000000
#define 	Timer2_TIFR_OCBit					BIT7


#define		TIMER0_NO_CLOCK						0x00
#define		TIMER0_PRESCALER_NO					0x01
#define		TIMER0_PRESCALER_8					0x02
#define		TIMER0_PRESCALER_64					0x03
#define		TIMER0_PRESCALER_128				0x04
#define		TIMER0_PRESCALER_1024				0x05
#define		TIMER0_COUNTER_FALLING				0X06
#define		TIMER0_COUNTER_RISING				0X07


#define		TIMER1_NO_CLOCK						0x0000
#define		TIMER1_PRESCALER_NO					0x0001
#define		TIMER1_PRESCALER_8					0x0002
#define		TIMER1_PRESCALER_64					0x0003
#define		TIMER1_PRESCALER_128				0x0004
#define		TIMER1_PRESCALER_1024				0x0005
#define		TIMER1_COUNTER_FALLING				0X0006
#define		TIMER1_COUNTER_RISING				0X0007


#define		TIMER2_NO_CLOCK						0x00
#define		TIMER2_PRESCALER_NO					0x01
#define		TIMER2_PRESCALER_8					0x02
#define		TIMER2_PRESCALER_32					0x03
#define		TIMER2_PRESCALER_64					0x04
#define		TIMER2_PRESCALER_128				0x05
#define		TIMER2_PRESCALER_256				0x06
#define		TIMER2_PRESCALER_1024				0x07

uint8 Timer0_Prescaler;
uint16 Timer1_Prescaler;
uint8 Timer2_Prescaler;





/**
 * Input: Pointer to a structure contains the information needed to initialize the timer.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Initiates the module.
 *
 */
ERROR_STATUS Timer_Init(Timer_cfg_s* Timer_cfg)
{
	ERROR_STATUS errorStatus = E_NOK;
	if(Timer_cfg != NULL)
	{
		switch(Timer_cfg->Timer_CH_NO)
		{
		case TIMER_CH0 :

			TCCR0 = Timer0_CMP_Mask;
			TCNT0 = Timer0_TCNT_INIT_Mask;
			TIMSK &= Timer0_Int_CLR_Mask;

			switch(Timer_cfg->Timer_Polling_Or_Interrupt)
			{
			case TIMER_POLLING_MODE :

					TIMSK |= Timer0_Polling_Int_Mask;
					errorStatus = E_OK;
				break;
			case TIMER_INTERRUPT_MODE :

					TIMSK |= Timer0_Interrupt_Int_Mask;
					errorStatus = E_OK;
				break;
			default :
				errorStatus = E_NOK;
				break;
			}


			switch(Timer_cfg->Timer_Mode)
			{
			case TIMER_MODE :

				switch(Timer_cfg->Timer_Prescaler)
				{
				case TIMER_NO_CLOCK :

					Timer0_Prescaler = TIMER0_NO_CLOCK;
					errorStatus = E_OK;
					break;

				case TIMER_PRESCALER_8 :

					Timer0_Prescaler = TIMER0_PRESCALER_8;
					errorStatus = E_OK;
					break;

				case TIMER_PRESCALER_32 :

					Timer0_Prescaler = TIMER0_NO_CLOCK;
					errorStatus = E_NOK;
					break;

				case TIMER_PRESCALER_64 :

					Timer0_Prescaler = TIMER0_PRESCALER_64;
					errorStatus = E_OK;
					break;

				case TIMER_PRESCALER_128 :

					Timer0_Prescaler = TIMER0_PRESCALER_128;
					errorStatus = E_OK;
					break;

				case TIMER_PRESCALER_256 :

					Timer0_Prescaler = TIMER0_NO_CLOCK;
					errorStatus = E_NOK;
					break;


				case TIMER_PRESCALER_1024 :

					Timer0_Prescaler = TIMER0_PRESCALER_1024;
					errorStatus = E_OK;
					break;

				default :
					Timer0_Prescaler = TIMER0_NO_CLOCK;
					errorStatus = E_NOK;
					break;
				}

				break;


			case COUNTER_UP_MODE :
				Timer0_Prescaler = TIMER0_COUNTER_RISING;
				errorStatus = E_OK;
				break;

			case COUNTER_DOWN_MODE :
				Timer0_Prescaler = TIMER0_COUNTER_FALLING;
				errorStatus = E_OK;
				break;


			default :
				Timer0_Prescaler = TIMER0_NO_CLOCK;
				errorStatus = E_NOK;
				break;
			}

			break;


		case TIMER_CH1 :

			TCCR1 = Timer1_CMP_Mask;
			TCNT1 = Timer1_TCNT_INIT_Mask;
			TIMSK &= Timer1_Int_CLR_Mask;


			switch(Timer_cfg->Timer_Polling_Or_Interrupt)
			{
			case TIMER_POLLING_MODE :

				TIMSK |= Timer1_Polling_Int_Mask;
				errorStatus = E_OK;
				break;
			case TIMER_INTERRUPT_MODE :

				TIMSK |= Timer1_Interrupt_Int_Mask;
				errorStatus = E_OK;
				break;
			default :
				errorStatus = E_NOK;
				break;
			}

			switch(Timer_cfg->Timer_Mode)
			{
			case TIMER_MODE :

				switch(Timer_cfg->Timer_Prescaler)
				{
				case TIMER_NO_CLOCK :

					Timer1_Prescaler = TIMER1_NO_CLOCK;
					errorStatus = E_OK;
					break;

				case TIMER_PRESCALER_8 :

					Timer1_Prescaler = TIMER1_PRESCALER_8;
					errorStatus = E_OK;
					break;

				case TIMER_PRESCALER_32 :

					Timer1_Prescaler = TIMER1_NO_CLOCK;
					errorStatus = E_NOK;
					break;

				case TIMER_PRESCALER_64 :

					Timer1_Prescaler = TIMER1_PRESCALER_64;
					errorStatus = E_OK;
					break;

				case TIMER_PRESCALER_128 :

					Timer1_Prescaler = TIMER1_PRESCALER_128;
					errorStatus = E_OK;
					break;

				case TIMER_PRESCALER_256 :

					Timer1_Prescaler = TIMER1_NO_CLOCK;
					errorStatus = E_NOK;
					break;


				case TIMER_PRESCALER_1024 :

					Timer1_Prescaler = TIMER1_PRESCALER_1024;
					errorStatus = E_OK;
					break;

				default :
					Timer1_Prescaler = TIMER1_NO_CLOCK;
					errorStatus = E_NOK;
					break;
				}

				break;


			case COUNTER_UP_MODE :
				Timer1_Prescaler = TIMER1_COUNTER_RISING;
				errorStatus = E_OK;
				break;

			case COUNTER_DOWN_MODE :
				Timer1_Prescaler = TIMER1_COUNTER_FALLING;
				errorStatus = E_OK;
				break;


			default :
				Timer1_Prescaler = TIMER1_NO_CLOCK;
				errorStatus = E_NOK;
				break;
			}

			break;

		case TIMER_CH2 :

			TCCR2 = Timer2_CMP_Mask;
			TCNT2 = Timer2_TCNT_INIT_Mask;
			TIMSK &= Timer1_Int_CLR_Mask;

			switch(Timer_cfg->Timer_Polling_Or_Interrupt)
			{
			case TIMER_POLLING_MODE :

				TIMSK |= Timer2_Polling_Int_Mask;
				errorStatus = E_OK;
				break;
			case TIMER_INTERRUPT_MODE :

				TIMSK |= Timer2_Interrupt_Int_Mask;
				errorStatus = E_OK;
				break;
			default :
				errorStatus = E_NOK;
				break;
			}

			switch(Timer_cfg->Timer_Mode)
			{
			case TIMER_MODE :

				switch(Timer_cfg->Timer_Prescaler)
				{
				case TIMER_NO_CLOCK :

					Timer2_Prescaler = TIMER2_NO_CLOCK;
					errorStatus = E_OK;
					break;

				case TIMER_PRESCALER_8 :

					Timer2_Prescaler = TIMER2_PRESCALER_8;
					errorStatus = E_OK;
					break;

				case TIMER_PRESCALER_32 :

					Timer2_Prescaler = TIMER2_PRESCALER_32;
					errorStatus = E_OK;
					break;

				case TIMER_PRESCALER_64 :

					Timer2_Prescaler = TIMER2_PRESCALER_64;
					errorStatus = E_OK;
					break;

				case TIMER_PRESCALER_128 :

					Timer2_Prescaler = TIMER2_PRESCALER_128;
					errorStatus = E_OK;
					break;

				case TIMER_PRESCALER_256 :

					Timer2_Prescaler = TIMER2_PRESCALER_256;
					errorStatus = E_OK;
					break;


				case TIMER_PRESCALER_1024 :

					Timer2_Prescaler = TIMER2_PRESCALER_1024;
					errorStatus = E_OK;
					break;

				default :
					Timer2_Prescaler = TIMER2_NO_CLOCK;
					errorStatus = E_NOK;
					break;
				}

				break;


			default :
				Timer2_Prescaler = TIMER2_NO_CLOCK;
				errorStatus = E_NOK;
				break;
			}

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

/**
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to be started.
 *	Timer_Count: The start value of the timer.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: This function strats the needed timer.
 *
 */
ERROR_STATUS Timer_Start(uint8 Timer_CH_NO, uint16 Timer_Count)
{
	ERROR_STATUS errorStatus = E_NOK;

	switch(Timer_CH_NO)
	{
	case TIMER_CH0 :

		if(Timer_Count < 256)
		{
			OCR0 = Timer_Count;
			TCCR0 |= Timer0_Prescaler;
			errorStatus = E_OK;
		}
		else
		{
			errorStatus = E_NOK;
		}

		break;

	case TIMER_CH1 :

		OCR1A = Timer_Count;
		TCCR1 |= Timer1_Prescaler;
		errorStatus = E_OK;
		break;

	case TIMER_CH2 :
		if(Timer_Count < 256)
		{
			OCR2 = Timer_Count;
			TCCR2 |= Timer2_Prescaler;
			errorStatus = E_OK;
		}
		else
		{
			errorStatus = E_NOK;
		}

		break;

	default :
		errorStatus = E_NOK;
		break;
	}

	return errorStatus;
}

/**
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to be stopped.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: This function stops the needed timer.
 *
 */
ERROR_STATUS Timer_Stop(uint8 Timer_CH_NO)
{
	ERROR_STATUS errorStatus = E_NOK;

	switch(Timer_CH_NO)
	{
	case TIMER_CH0 :


		TCCR0 |= TIMER0_PRESCALER_NO;
		errorStatus = E_OK;
		break;

	case TIMER_CH1 :

		TCCR1 |= TIMER1_PRESCALER_NO;
		errorStatus = E_OK;
		break;

	case TIMER_CH2 :
		TCCR2 |= TIMER2_PRESCALER_NO;
		errorStatus = E_OK;
		break;

	default :
		errorStatus = E_NOK;
		break;
	}

	return errorStatus;
}

/**
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to get its status.
 * Output:
 * 	Data: A variable of type bool returns if the flag of the timer is raised or not.
 * In/Out:
 * Return: The error status of the function.
 * Description: This function is used to return if the flag of the timer is raised or not.
 *
 */
ERROR_STATUS Timer_GetStatus(uint8 Timer_CH_NO, bool* Data)
{
	ERROR_STATUS errorStatus = E_NOK;

	if(Data != NULL)
	{
		switch(Timer_CH_NO)
		{
		case TIMER_CH0 :


			ASSIGN_BIT(*Data, Timer0_TIFR_OCBit, TIFR);
			errorStatus = E_OK;
			break;

		case TIMER_CH1 :

			ASSIGN_BIT(*Data, Timer1_TIFR_OCBit, TIFR);
			errorStatus = E_OK;
			break;

		case TIMER_CH2 :

			ASSIGN_BIT(*Data, Timer2_TIFR_OCBit, TIFR);
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

/**
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to get its value.
 * Output:
 * 	Data: This is the output variable of the function which holds the value of the timer.
 * In/Out:
 * Return: The error status of the function.
 * Description: This function is used to return the value of the timer.
 *
 */
ERROR_STATUS Timer_GetValue(uint8 Timer_CH_NO, uint16* Data)
{
	ERROR_STATUS errorStatus = E_NOK;

	if(Data != NULL)
	{
		switch(Timer_CH_NO)
		{
		case TIMER_CH0 :
			*Data = OCR0;
			errorStatus = E_OK;
			break;

		case TIMER_CH1 :
			*Data = OCR1A;
			errorStatus = E_OK;
			break;

		case TIMER_CH2 :
			*Data = OCR2;
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
