/*
 * TemperatureSensor.c
 *
 *  Created on: Dec 7, 2024
 *      Author: Menna Eid
 */


#include "TemperatureSensor.h"
extern ADC_HandleTypeDef hadc1;
void LM35_Init()
{
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_2;
	sConfig.Rank = ADC_REGULAR_RANK_2;
	sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);
}
float LM35_ReadTemperature(void)
{
   LM35_Init();
   HAL_ADC_Start(&hadc1);
   uint16_t temp_value = HAL_ADC_GetValue(&hadc1);
   HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
   HAL_ADC_Stop(&hadc1);
   float temperature = (temp_value * 3.3 / 4095.0) * 100.0;
   return temperature;

}
