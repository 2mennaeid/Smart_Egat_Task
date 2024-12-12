/*
 * MCAL_Init.h
 *
 *  Created on: Dec 7, 2024
 *      Author: Menna Eid
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#include "stm32f1xx_hal.h"

void SystemClock_Config(void);
void ADC1_Init(void);
void USART1_UART_Init(void);
void sendJSON(char *jsonMessage);
void receiveJSON(char *buffer, uint16_t bufferSize);
#endif /* INC_CONFIG_H_ */
