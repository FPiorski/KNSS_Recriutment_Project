#include <string.h>
#include "stm32f1xx_hal.h"
#include "errors.h"

UART_HandleTypeDef uart2;

void InitUART(void)
{
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef gpio;
	gpio.Pin   = GPIO_PIN_2;	// PA2 == USART2_TX
	gpio.Mode  = GPIO_MODE_AF_PP;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &gpio);
	gpio.Pin   = GPIO_PIN_3;	// PA3 == USART2_RX
	gpio.Mode  = GPIO_MODE_INPUT;
	gpio.Pull  = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &gpio);

	uart2.Instance          = USART2;
	uart2.Init.BaudRate     = 115200;
	uart2.Init.WordLength   = UART_WORDLENGTH_8B;
	uart2.Init.StopBits     = UART_STOPBITS_1;
	uart2.Init.Parity       = UART_PARITY_NONE;
	uart2.Init.Mode         = UART_MODE_TX_RX;
	uart2.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
	uart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&uart2) != HAL_OK)
		HandleError();
}

void UART_SendString(char* s, uint32_t timeout)	//Blocking
{
	HAL_UART_Transmit(&uart2, (uint8_t*)s, strlen(s), timeout);
}
