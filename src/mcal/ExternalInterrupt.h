/*
 * file: externalInterrupt.h
 * Author: Hassan and Ghanem.
 * version: 1.0.0 


#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_


/************************************************************************/
/*				 		      INCLUDES                                  */
/************************************************************************/
#include "Common.h"
#include "registers.h"
#include "interrupt.h"
/************************************************************************/
/*				 		       Defines                                  */
/************************************************************************/

#define EXTRN_INT_0    0
#define EXTRN_INT_1    1
#define EXTRN_INT_2    2

#define LOW_LEVEL      0
#define LOGICAL_CHANGE 1
#define FALLING_EDGE   2
#define RISING_EDGE    3


#define INTERRUPT      0
#define POLLING        1

/************************************************************************/
/*				 		           Types                                */
/************************************************************************/

typedef struct ExternInt_Cfg_s{
	
	uint8 ExternInt_No,
	uint8 ExternInt_Event,
	uint8 ExternInt_Mode
}ExternInt_Cfg_s;

/************************************************************************/
/*				 		Functions ProtoTypes                            */
/************************************************************************/

/*
 * Function: ExternInt_Init 
 * Inputs:	ExternIntCfg -> pointer of type ExternInt_Cfg_s which points to struchure that contain the initialized data. 
 * Outputs: 
 * In Out: 
 * Return: ERROR_STATUS -> check if there any error occures, would return E_NOK else it would return E_OK.
 * Description: Initiate the required external interrupt configration as it specify 
 *	event of interrupt and mode if polling or Interrupt.
 */
ERROR_STATUS ExternInt_Init(ExternInt_Cfg_s *ExternIntCfg);

/*
 * Function: ExternInt_Enable
 * Inputs: ExternInt_No -> Specify one of the external interrupt (INT_0, INT_1, INT2).
 * Outputs:
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occures, would return E_NOK else it would return E_OK.
 * Description: Enable the required external interrupt.
 */
ERROR_STATUS ExternInt_Enable(uint8 ExternInt_No);

/*
 * Function: ExternInt_GetStatus
 * Inputs: ExternInt_No -> Specify one of the external interrupt (INT_0, INT_1, INT2).
 * Outputs: *status -> points to the value of selected interrupt flag.
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occures, would return E_NOK else it would return E_OK.
 * Description: function is used to get flag of required interrupt status. 
 * 				note: usually used to poll on the flag.
 */
ERROR_STATUS ExternInt_GetStatus(uint8 ExternInt_No,uint8 *Status);
/*
 * Function: ExternInt_Disable
 * Inputs: ExternInt_No -> Specify one of the external interrupt (INT_0, INT_1, INT2)
 * Outputs:
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occures, would return E_NOK else it would return E_OK.
 * Description: Disable the required external interrupt.
 */
ERROR_STATUS ExternInt_Disable(uint8 ExternInt_No);


#endif /*EXTERNAL_INTERRUPT_H_*/