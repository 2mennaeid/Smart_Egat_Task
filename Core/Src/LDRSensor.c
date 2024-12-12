#include "LDRSensor.h"
extern ADC_HandleTypeDef hadc1;

void LDR_Init()
{
	   ADC_ChannelConfTypeDef sConfig = {0};
		sConfig.Channel = ADC_CHANNEL_1;
		sConfig.Rank = ADC_REGULAR_RANK_1;
		sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
		HAL_ADC_ConfigChannel(&hadc1, &sConfig);
}
float LDR_ReadValue(void)
{
	   LDR_Init();
	   uint16_t ldr_value ;
	   HAL_ADC_Start(&hadc1);
	   if(HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY)==HAL_OK)
	   {
		   ldr_value = HAL_ADC_GetValue(&hadc1);
	   }
	   HAL_ADC_Stop(&hadc1);
	   float brightness = (ldr_value * 3.3 / 4095.0); // Brightness in volts
	   return brightness;


}
