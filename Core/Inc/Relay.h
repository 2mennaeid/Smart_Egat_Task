/*
 * Relay.h
 *
 *  Created on: Dec 7, 2024
 *      Author: Menna Eid
 */

#ifndef INC_RELAY_H_
#define INC_RELAY_H_

#include "stm32f1xx_hal.h"
void Relay_Init(void);
void Relay_SetState(uint8_t state);
uint8_t Relay_GetState();


#endif /* INC_RELAY_H_ */
