/*
 * Common.h
 *
 *  Created on: Dec 21, 2019
 *      Author: New User
 */

#ifndef COMMON_H_
#define COMMON_H_


/************************************************************************/
/*                   typedefs for standard types                        */
/************************************************************************/

#define NULL	((void *)0)

typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long int uint32;
typedef unsigned long long uint64;
typedef signed char sint8;
typedef signed int sint16;
typedef signed long int sint32;
typedef signed long long sint64;
typedef volatile uint8* const reg_type8;
typedef volatile uint16* const reg_type16;
typedef float float32;


/************************************************************************/
/*				 		defining error status                         */
/************************************************************************/
#define ERROR_STATUS	 	uint8
#define E_OK				0
#define E_NOK				1


/************************************************************************/
/*				 		defining bool values                            */
/************************************************************************/
typedef uint8 bool;
#define FALSE 	0
#define TRUE 	1


/************************************************************************/
/*						 LOW/HIGH defines                               */
/************************************************************************/
#define LOW  0
#define HIGH 0xFF


/************************************************************************/
/*						 BIT_MATH defines                               */
/************************************************************************/

/* Set VARiable's Certin BIT High */
#define SET_BIT(VAR,BIT_NB) 		(VAR)|=(BIT_NB)

/* Set VARiable's Certin BIT Low */
#define CLR_BIT(VAR,BIT_NB) 		(VAR)&=~(BIT_NB)

/* Toggle VARiable's Certin BIT */
#define TOGGLE_BIT(VAR,BIT_NB) 		(VAR)^=(BIT_NB)

/* Assign VARiable's Certin BIT by a Certin VALue */
#define ASSIGN_BIT(VAR,BIT_NB,VAL)  (VAR)=((VAR&(~(BIT_NB)))|(VAL&BIT_NB))

/* Get VARiable's Certin BIT Value */
#define GET_BIT(VAR,BIT_NB) 		(((VAR)&(BIT_NB))/(BIT_NB))




#endif /* COMMON_H_ */
