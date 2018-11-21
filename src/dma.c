#include "stm32f1xx_hal.h"

DMA_HandleTypeDef dma_adc1;

void InitDMA(void)
{
	__HAL_RCC_DMA1_CLK_ENABLE();
}
