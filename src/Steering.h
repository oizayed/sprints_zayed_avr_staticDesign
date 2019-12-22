/*
 * Steering.h
 *
 *  Created on: Dec 21, 2019
 *      Author: New User
 */

#ifndef STEERING_H_
#define STEERING_H_

#include "Common.h"

/*
 *  include motor header here
 */


#define		CAR_STOP		0
#define		CAR_FORWARD		1
#define		CAR_BACKWARD	2
#define		CAR_RIGHT		3
#define		CAR_LEFT		4

ERROR_STATUS Steering_Init(void);
ERROR_STATUS Steering_SteerCar(uint8 carDirection, uint8 speed);





#endif /* STEERING_H_ */
