#include "stm32f1xx_hal.h"
#include "errors.h"
#include "dma.h"

ADC_HandleTypeDef adc1;

void InitADC(void)
{
	__HAL_RCC_ADC1_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef gpio;
	gpio.Pin  = GPIO_PIN_0;	// ADC1 Channel 0 In == PA0
	gpio.Mode = GPIO_MODE_ANALOG;
	gpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &gpio);

	adc1.Instance                   = ADC1;
	adc1.Init.ScanConvMode          = ADC_SCAN_DISABLE;
	adc1.Init.ContinuousConvMode    = ENABLE;
	adc1.Init.DiscontinuousConvMode = DISABLE;
	adc1.Init.ExternalTrigConv      = ADC_SOFTWARE_START;
	adc1.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
	adc1.Init.NbrOfConversion       = 1;
	if (HAL_ADC_Init(&adc1) != HAL_OK)
		HandleError();

	ADC_ChannelConfTypeDef adc_ch;
	adc_ch.Channel      = ADC_CHANNEL_0;
	adc_ch.Rank         = ADC_REGULAR_RANK_1;
	adc_ch.SamplingTime = ADC_SAMPLETIME_7CYCLES_5;
	HAL_ADC_ConfigChannel(&adc1, &adc_ch);

	while (HAL_ADCEx_Calibration_Start(&adc1) != HAL_OK)
		;

}

void ConfigureADCDMA(void)
{
	dma_adc1.Instance                 = DMA1_Channel1;
	dma_adc1.Init.Direction           = DMA_PERIPH_TO_MEMORY;
	dma_adc1.Init.PeriphInc           = DMA_PINC_DISABLE;
	dma_adc1.Init.MemInc              = DMA_MINC_ENABLE;
	dma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	dma_adc1.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
	dma_adc1.Init.Mode                = DMA_NORMAL;
	dma_adc1.Init.Priority            = DMA_PRIORITY_HIGH;
	if (HAL_DMA_Init(&dma_adc1) != HAL_OK)
		HandleError();
	__HAL_LINKDMA(&adc1, DMA_Handle, dma_adc1);
}

void CaptureADC(uint16_t *buf, uint32_t bufsize)
{
	HAL_ADC_Start_DMA(&adc1, (uint32_t*)buf, bufsize);
}
