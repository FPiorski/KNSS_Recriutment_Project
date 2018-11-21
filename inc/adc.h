#ifndef __ADC_H_INCLUDED
#define __ADC_H_INCLUDED

extern ADC_HandleTypeDef adc1;

void InitADC(void);
void ConfigureADCDMA(void);
void CaptureADC(uint16_t *buf, uint32_t bufsize);

#endif
