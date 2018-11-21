#define MAX(a,b) ((a>b)?(a):(b))
#define MIN(a,b) ((a>b)?(b):(a))

#include "stm32f1xx.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "errors.h"
#include "clocks.h"
#include "uart.h"
#include "dma.h"
#include "adc.h"

#define AVER_N  20
#define BUFSIZE 2000
uint16_t dmabuf[BUFSIZE];
uint32_t avgbuf[BUFSIZE];

uint16_t trigger(uint16_t *buf, uint16_t avg);
void PeriodToString(char *buf, uint16_t period);
void VppToString(char *buf, uint16_t Vpp);

int main(void)
{
	HAL_Init();
	ConfigSystemClock();
	InitUART();
	InitDMA();
	InitADC();
	ConfigureADCDMA();

	while (1) {

		for (uint16_t i=0; i<BUFSIZE; ++i)
			avgbuf[i] = 0;

		CaptureADC(dmabuf, BUFSIZE);	// 0th capture for estimating the DC Offset
		HAL_DMA_PollForTransfer(&dma_adc1, HAL_DMA_FULL_TRANSFER, 100);

		uint32_t sum = 0;
		for (uint16_t i=0; i<BUFSIZE; ++i)
			sum += dmabuf[i];
		uint16_t dcbias = sum / BUFSIZE; //initial guess for triggering

		for (uint8_t i=0; i<AVER_N; ++i) {
			CaptureADC(dmabuf, BUFSIZE);
			HAL_DMA_PollForTransfer(&dma_adc1, HAL_DMA_FULL_TRANSFER, 100);
			uint16_t j = trigger(dmabuf, dcbias);
			for (uint16_t k = 0; j<BUFSIZE;)
				avgbuf[k++] += dmabuf[j++];
		}

		for (uint16_t i=0; i<BUFSIZE; ++i)
			dmabuf[i] = avgbuf[i] / AVER_N;

		uint16_t period = trigger(dmabuf + BUFSIZE/10, dcbias) + BUFSIZE/10;

		uint32_t real_dcbias = 0;
		for (uint16_t i=0; i<period; ++i)
			real_dcbias += dmabuf[i];
		real_dcbias /= period;

		uint16_t inf = -1, sup = 0;
		for (uint16_t i=0; i<period; ++i) {
			inf = MIN(inf, dmabuf[i]);
			sup = MAX(sup, dmabuf[i]);
		}

		uint16_t Vpp = sup - inf;

		char cbuf[20];
		PeriodToString(cbuf, period);
		HAL_UART_Transmit(&uart2, (uint8_t *) cbuf, strlen(cbuf), 1000);
		VppToString(cbuf, Vpp);
		HAL_UART_Transmit(&uart2, (uint8_t *) cbuf, strlen(cbuf), 1000);

		HAL_Delay(100);
	}

	return 0;
}

uint16_t trigger(uint16_t* buf, uint16_t avg)
{
	uint16_t it = 0;
	while ((buf[it] > avg) && it < BUFSIZE-1)
		++it;
	it+=5;
	while ((buf[it] < avg) && it < BUFSIZE-1)
		++it;
	return it;
}

void PeriodToString(char *buf, uint16_t period)
{
	float f = 600.0f / period;
	int k = f * 10000;
	buf[0] = ((k/10000)%10) + '0';
	buf[1] = '.';
	buf[2] = ((k/1000)%10) + '0';
	buf[3] = ((k/100)%10) + '0';
	buf[4] = ((k/10)%10) + '0';
	buf[5] = 'k';
	buf[6] = 'H';
	buf[7] = 'z';
	buf[8] = ' ';
	buf[9] = 0;
}

void VppToString(char *buf, uint16_t Vpp)
{
	float f = Vpp * 3.3f / 4096.0f;
	int k = f * 10000;
	buf[0] = ((k/10000)%10) + '0';
	buf[1] = '.';
	buf[2] = ((k/1000)%10) + '0';
	buf[3] = ((k/100)%10) + '0';
	buf[4] = ((k/10)%10) + '0';
	buf[5] = 'V';
	buf[6] = 'p';
	buf[7] = 'p';
	buf[8] = '\r';
	buf[9] = '\n';
	buf[10] = 0;
}
