/*
 * LDRSensor.h
 *
 *  Created on: Dec 7, 2024
 *      Author: Menna Eid
 */

#ifndef INC_LDRSENSOR_H_
#define INC_LDRSENSOR_H_

#include "stm32f1xx_hal.h"

void LDR_Init();
float LDR_ReadValue(void);

#endif /* INC_LDRSENSOR_H_ */
