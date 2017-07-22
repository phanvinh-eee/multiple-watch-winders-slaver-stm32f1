#ifndef __USER_RCC_H
#define __USER_RCC_H
#include <stm32f10x_it.h>
#define SYSCLK_FREQ_24MHz
	ErrorStatus HSEStartUpStatus;
#if !defined STM32F10X_LD && !defined STM32F10X_MD && !defined STM32F10X_HD
  //#define SYSCLK_FREQ_36MHz
  //#define SYSCLK_FREQ_48MHz
  //#define SYSCLK_FREQ_56MHz
  #define SYSCLK_FREQ_72MHz	
#endif
void SetSysClockToHSE(void);
void SetSysClockTo24(void);
void SetSysClockTo36(void);
void SetSysClockTo48(void);
void SetSysClockTo56(void);
void SetSysClockTo72(void);
#endif
