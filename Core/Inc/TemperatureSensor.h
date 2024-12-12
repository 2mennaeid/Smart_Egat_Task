/*
 * TemperatureSensor.h
 *
 *  Created on: Dec 7, 2024
 *      Author: Menna Eid
 */

#ifndef INC_TEMPERATURESENSOR_H_
#define INC_TEMPERATURESENSOR_H_

#include "stm32f1xx_hal.h"

void LM35_Init();
float LM35_ReadTemperature(void);

#endif /* INC_TEMPERATURESENSOR_H_ */
