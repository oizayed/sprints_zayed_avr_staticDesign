/*
 * ExternalInterrupt.c
 *
 *  Created on: Dec 23, 2019
 *      Author: Omar Zayed
 */


#include "ExternalInterrupt.h"
#include "common_macros.h"
#include "../DIO/DIO.h"
#include "../../mcal/registers.h"
#include "interrupts.h"

static volatile ERROR_STATUS (*ExternalInterrupt_CBK_Ptr[3])(void) = {NULL, NULL, NULL};


/*
 * Function: ExternInt_Init
 * Inputs:	ExternIntCfg -> pointer of type ExternInt_Cfg_s which points to structure that contain the initialized data.
 * Outputs:
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * Description: Initiate the required external interrupt configuration as it specify
 *	event of interrupt and mode if polling or Interrupt.
 */
ERROR_STATUS ExternInt_Init(ExternInt_Cfg_s* ExternIntCfg)
{
	ERROR_STATUS errorStatus = E_NOK;
	DIO_Cfg_s DIO_Cfg;

	if(ExternIntCfg != NULL)
	{
			switch(ExternIntCfg->ExternInt_No)
			{
			case EXTRN_INT_0 :


				switch(ExternIntCfg->ExternInt_Event)
				{
				case LOW_LEVEL :

					CLR_BIT(MCUCR, BIT0);
					CLR_BIT(MCUCR, BIT1);
					errorStatus = E_OK;
					break;

				case LOGICAL_CHANGE :

					SET_BIT(MCUCR, BIT0);
					CLR_BIT(MCUCR, BIT1);
					errorStatus = E_OK;
					break;

				case FALLING_EDGE :

					CLR_BIT(MCUCR, BIT0);
					SET_BIT(MCUCR, BIT1);
					errorStatus = E_OK;
					break;
				case RISING_EDGE :

					SET_BIT(MCUCR, BIT0);
					SET_BIT(MCUCR, BIT1);
					errorStatus = E_OK;
					break;

				default :
					errorStatus = E_NOK;
					break;
				}

				break;


		case EXTRN_INT_1 :

			switch(ExternIntCfg->ExternInt_Event)
			{
			case LOW_LEVEL :

				CLR_BIT(MCUCR, BIT2);
				CLR_BIT(MCUCR, BIT3);
				errorStatus = E_OK;
				break;

			case LOGICAL_CHANGE :

				SET_BIT(MCUCR, BIT2);
				CLR_BIT(MCUCR, BIT3);
				errorStatus = E_OK;
				break;

			case FALLING_EDGE :

				CLR_BIT(MCUCR, BIT2);
				SET_BIT(MCUCR, BIT3);
				errorStatus = E_OK;
				break;
			case RISING_EDGE :

				SET_BIT(MCUCR, BIT2);
				SET_BIT(MCUCR, BIT3);
				errorStatus = E_OK;
				break;

			default :
				errorStatus = E_NOK;
				break;
			}

			break;

		case EXTRN_INT_2 :

			switch(ExternIntCfg->ExternInt_Event)
			{
			case LOW_LEVEL :

				errorStatus = E_NOK;
				break;

			case LOGICAL_CHANGE :

				errorStatus = E_NOK;
				break;

			case FALLING_EDGE :

				CLR_BIT(MCUCSR, BIT6);
				errorStatus = E_OK;
				break;
			case RISING_EDGE :

				SET_BIT(MCUCSR, BIT6);
				errorStatus = E_OK;
				break;

			default :
				errorStatus = E_NOK;
				break;
			}

			break;

		default :

			errorStatus = E_NOK;
			break;
			}




			if(errorStatus == E_OK)
			{
				switch(ExternIntCfg->ExternInt_No)
				{

				case EXTRN_INT_0 :
					ExternalInterrupt_CBK_Ptr[0] = ExternIntCfg->ExternInt_CBF_Ptr;
					DIO_Cfg.GPIO = GPIOD;
					DIO_Cfg.pins = PIN2;
					DIO_Cfg.dir = INPUT;
					DIO_init(&DIO_Cfg);
					break;


				case EXTRN_INT_1 :
					ExternalInterrupt_CBK_Ptr[1] = ExternIntCfg->ExternInt_CBF_Ptr;
					DIO_Cfg.GPIO = GPIOD;
					DIO_Cfg.pins = PIN3;
					DIO_Cfg.dir = INPUT;
					DIO_init(&DIO_Cfg);
					break;

				case EXTRN_INT_2 :
					ExternalInterrupt_CBK_Ptr[2] = ExternIntCfg->ExternInt_CBF_Ptr;
					DIO_Cfg.GPIO = GPIOB;
					DIO_Cfg.pins = PIN2;
					DIO_Cfg.dir = INPUT;
					DIO_init(&DIO_Cfg);
					break;

				default :

					errorStatus = E_NOK;
					break;
			}
		}

	}
	else
	{
		errorStatus = E_NOK;
	}

	return errorStatus;
}


/*
 * Function: ExternInt_Enable
 * Inputs: ExternInt_No -> Specify one of the external interrupt (INT_0, INT_1, INT2).
 * Outputs:
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * Description: Enable the required external interrupt from GICR but to allow the interrupt global interrupt must be set.
 */
ERROR_STATUS ExternInt_Enable(uint8 ExternInt_No)
{
	ERROR_STATUS errorStatus = E_NOK;

	switch(ExternInt_No)
	{
	case EXTRN_INT_0 :

		SET_BIT(GICR, BIT6);
		errorStatus = E_OK;
		break;

	case EXTRN_INT_1 :

		SET_BIT(GICR, BIT7);
		errorStatus = E_OK;
		break;

	case EXTRN_INT_2 :

		SET_BIT(GICR, BIT5);
		errorStatus = E_OK;
		break;

	default :
		errorStatus = E_NOK;
		break;

	}

		return errorStatus;

}



/*
 * Function: ExternInt_SetEvent
 * Inputs: ExternInt_No -> Specify one of the external interrupt (INT_0, INT_1, INT2).
 * 	       InterruptEvent -> indicate required event for INT0 and INT1 there are 4 events to check (RISING_EDGE,FALLING_EDGE,LOW_LEVEL,LOGICAL_CHANGE).
							  But for Interrupt 2 there are only Two cases (Rising,Falling)
 * Outputs:
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * Description: function is used to set event of required external interrupt.
 * 				note: usually used to poll on the flag.
 */
ERROR_STATUS ExternInt_SetEvent(uint8 ExternInt_No,uint8 InterruptEvent)
{
	ERROR_STATUS errorStatus = E_NOK;

	switch(ExternInt_No)
	{
	case EXTRN_INT_0 :

		switch(InterruptEvent)
		{
		case LOW_LEVEL :

			CLR_BIT(MCUCR, BIT0);
			CLR_BIT(MCUCR, BIT1);
			errorStatus = E_OK;
			break;

		case LOGICAL_CHANGE :

			SET_BIT(MCUCR, BIT0);
			CLR_BIT(MCUCR, BIT1);
			errorStatus = E_OK;
			break;

		case FALLING_EDGE :

			CLR_BIT(MCUCR, BIT0);
			SET_BIT(MCUCR, BIT1);
			errorStatus = E_OK;
			break;
		case RISING_EDGE :

			SET_BIT(MCUCR, BIT0);
			SET_BIT(MCUCR, BIT1);
			errorStatus = E_OK;
			break;

		default :
			errorStatus = E_NOK;
			break;
		}

		break;


	case EXTRN_INT_1 :

		switch(InterruptEvent)
		{
		case LOW_LEVEL :

			CLR_BIT(MCUCR, BIT2);
			CLR_BIT(MCUCR, BIT3);
			errorStatus = E_OK;
			break;

		case LOGICAL_CHANGE :

			SET_BIT(MCUCR, BIT2);
			CLR_BIT(MCUCR, BIT3);
			errorStatus = E_OK;
			break;

		case FALLING_EDGE :

			CLR_BIT(MCUCR, BIT2);
			SET_BIT(MCUCR, BIT3);
			errorStatus = E_OK;
			break;
		case RISING_EDGE :

			SET_BIT(MCUCR, BIT2);
			SET_BIT(MCUCR, BIT3);
			errorStatus = E_OK;
			break;

		default :
			errorStatus = E_NOK;
			break;
		}

		break;

	case EXTRN_INT_2 :

		switch(InterruptEvent)
		{
		case LOW_LEVEL :

			errorStatus = E_NOK;
			break;

		case LOGICAL_CHANGE :

			errorStatus = E_NOK;
			break;

		case FALLING_EDGE :

			CLR_BIT(MCUCSR, BIT6);
			errorStatus = E_OK;
			break;
		case RISING_EDGE :

			SET_BIT(MCUCSR, BIT6);
			errorStatus = E_OK;
			break;

		default :
			errorStatus = E_NOK;
			break;
		}

		break;

	default :

		errorStatus = E_NOK;
		break;
	}

	return errorStatus;
}


/*
 * Function: ExternInt_GetStatus
 * Inputs: ExternInt_No -> Specify one of the external interrupt (INT_0, INT_1, INT2).
 * Outputs: *status -> points to the value of selected interrupt flag.
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * Description: function is used to get flag of required interrupt status.
 * 				note: usually used to poll on the flag.
 */
ERROR_STATUS ExternInt_GetStatus(uint8 ExternInt_No,uint8 *Status)
{
	ERROR_STATUS errorStatus = E_NOK;

	switch(ExternInt_No)
	{
	case EXTRN_INT_0 :


		if(GET_BIT(GIFR, BIT6) == 1)
		{
			*Status = HIGH;
		}
		else
		{
			*Status = LOW;
		}
		errorStatus = E_OK;
		break;

	case EXTRN_INT_1 :

		if(GET_BIT(GIFR, BIT7) == 1)
		{
			*Status = HIGH;
		}
		else
		{
			*Status = LOW;
		}
		errorStatus = E_OK;
		break;

	case EXTRN_INT_2 :

		if(GET_BIT(GIFR, BIT5) == 1)
		{
			*Status = HIGH;
		}
		else
		{
			*Status = LOW;
		}
		errorStatus = E_OK;
		break;

	default :
		errorStatus = E_NOK;
		break;

	}

		return errorStatus;

}


/*
 * Function: ExternInt_Disable
 * Inputs: ExternInt_No -> Specify one of the external interrupt (INT_0, INT_1, INT2)
 * Outputs:
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * Description: Disable the required external interrupt.
 */
ERROR_STATUS ExternInt_Disable(uint8 ExternInt_No)
{
	ERROR_STATUS errorStatus = E_NOK;

	switch(ExternInt_No)
		{
		case EXTRN_INT_0 :

			CLR_BIT(GICR, BIT6);
			errorStatus = E_OK;
			break;

		case EXTRN_INT_1 :

			CLR_BIT(GICR, BIT7);
			errorStatus = E_OK;
			break;

		case EXTRN_INT_2 :

			CLR_BIT(GICR, BIT5);
			errorStatus = E_OK;
			break;

		default :
			errorStatus = E_NOK;
			break;

		}

	return errorStatus;

}

ISR(INT0_vect)
{
	if(NULL != ExternalInterrupt_CBK_Ptr[0])
	{
		ExternalInterrupt_CBK_Ptr[0]();
	}
}

ISR(INT1_vect)
{
	if(NULL != ExternalInterrupt_CBK_Ptr[1])
	{
		ExternalInterrupt_CBK_Ptr[1]();
	}
}

ISR(INT2_vect)
{
	if(NULL != ExternalInterrupt_CBK_Ptr[2])
	{
		ExternalInterrupt_CBK_Ptr[2]();
	}
}
