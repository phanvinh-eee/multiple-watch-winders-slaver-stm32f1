#ifndef __UART_STRING_H
#define __UART_STRING_H
#include <string.h>
#include <stdint.h>
//#include <stm32f10x.h>
uint8_t read_buffer(void);
void slave_processing(void);
void RxInit(void);
#endif
