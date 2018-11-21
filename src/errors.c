#include "stm32f1xx.h"
#include "errors.h"

void FP_Error_Handler(char *file, int line) //Blink S-O-S in Morse code
{
	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_InitTypeDef gpio;
	gpio.Pin = GPIO_PIN_13;
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &gpio);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);

	while(1) {
		for (int i=0; i<3; ++i){
			for (int j=0; j<6; ++j) {
				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
				HAL_Delay(200 + 400 * (i == 1));
			}
			HAL_Delay(300);
		}
		HAL_Delay(1000);
	}
}
