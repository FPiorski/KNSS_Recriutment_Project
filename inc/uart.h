#ifndef __UART_H_INCLUDED
#define __UART_H_INCLUDED

extern UART_HandleTypeDef uart2;	//So that we can access it in main.c

void InitUART(void);
void UART_SendString(char* s, uint32_t timeout);

#endif
