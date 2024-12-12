/*
 * Relay.c
 *
 *  Created on: Dec 7, 2024
 *      Author: Menna Eid
 *
 *  Description:
 *      This file provides the implementation for initializing and controlling a relay using GPIO.
 */

#include "Relay.h"

/**
 * @brief Initialize the GPIO pin used for the relay.
 */
void Relay_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable the GPIOB clock
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // Ensure the relay is initially off
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);

    // Configure GPIO pin PB8 as output, push-pull, no pull-up/down
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Turn off the relay by default
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
}

/**
 * @brief Set the state of the relay.
 * @param state: Set to 1 to turn on the relay, or 0 to turn it off.
 */
void Relay_SetState(uint8_t state)
{
    if (state)
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET); // Turn on the relay
    }
    else
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET); // Turn off the relay
    }
}

/**
 * @brief Get the current state of the relay.
 * @retval 1 if the relay is on, 0 if it is off.
 */
uint8_t Relay_GetState(void)
{
    return (uint8_t)HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8);
}
