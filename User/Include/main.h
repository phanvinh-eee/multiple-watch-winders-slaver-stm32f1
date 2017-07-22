/**
  ******************************************************************************
  * Ten Tep		:		    Main.h
  * Tac Gia		:	  		Nguyen Quy Nhat
  * Cong Ty		:			  MinhHaGroup
  *	Website 	:			  MinhHaGroup.com
  * Phien Ban	:			  V1.0.0
  * Ngay		  :    		31-07-2012
  * Tom Tat   :       	Khai bao cac thu vien su dung.
  *							Dinh nghia mot so chuc nang.
  *           
  *
  ******************************************************************************
  * Chu Y		:
  *							 
  ******************************************************************************
  */		
#ifndef __MAIN_H
#define	__MAIN_H
//#define USE_STDPERIPH_DRIVER
//#define STM32F10X_HD
/************************INCLUDE FILE********************************/
/*++++++++++++STANDAR C++++++++++++++*/
#include  <stdarg.h>
#include  <string.h>
#include  <ctype.h>
#include  <stdlib.h>
#include <stdio.h>
/*++++++++++++DRIVER++++++++++++++++*/
#include "DEF_STM32.h"
#include "stm32f10x.h"	   
//#include "stm32f10x_adc.h"
//#include "stm32f10x_dma.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_exti.h"
//#include "misc.h"	
/*+++++++++++++USER+++++++++++++++++*/
#include "user_delay.h"
#include "user_gpio.h"
#include "user_usart.h"
#include "user_nvic.h"
#include "user_exti.h"
#include "user_timer.h"
#include "lcd_led.h"
#include "uart_string.h"
//typedef enum {RIGHT=0x00, LEFT=0x01, BOTH=0x02} mDirection;
//typedef enum {STOP=0x00,RUN=0x01} mOnOff;
//typedef enum {Slow=0x00, Normal=0x01, Fast=0x02, Fastest=0x03} mSpeed;
#define RUN 1
#define SLEEP 2
#define STOP 0
#define Slow 0
#define Normal 1
#define Fast 2
#define Fastest 3
#define RIGHT 0
#define LEFT 1
#define BOTH 2
typedef struct {
  uint8_t Pow;
  uint8_t Di;
  uint8_t Speed;
  uint8_t MCH;
}Motor_Typedef;
typedef struct{
  uint8_t Di;
  uint8_t Speed;
}MCH_Typedef;
void Motor_Init(void);
/**************************DEFINE********************************/ 
//+++++++++++++++++++++++++DEFINE PORTA+++++++++++++++++++++++++++

#define   LCD_D4       PORTA_7
#define   LCD_D5       PORTA_11
#define   LCD_D6       PORTA_12
#define   LCD_D7       PORTA_13

#define   LED1				 PORTC_13
#define   LED2				 PORTA_4
#define   LED3				 PORTA_5
#define   LED4				 PORTA_6

#define   BUTTON1      PINA_8
#define   BUTTON2      PINB_13
#define   BUTTON3      PINB_14
#define   BUTTON4      PINB_15
#define 	USART1_TX		 PINA_9
#define 	USART1_RX		 PINA_10

#define 	USART2_TX		 PINA_2
#define 	USART2_RX		 PINA_3

#define 	USART3_TX		 PINB_10
#define 	USART3_RX		 PINB_11

#define 	SPI1_SCK 		 PINA_5
#define 	SPI1_MISO 	 PINA_6
#define 	SPI1_MOSI		 PINA_7

#define 	SPI2_SCK 		 PINB_13
#define 	SPI2_MISO 	 PINB_14
#define 	SPI2_MOSI		 PINB_15

#define 	TFT_BKL			 PINA_1
#define 	TFT_RESET		 PINC_1
#define 	TFT_RS			 PINC_2
#define 	TFT_LCD_CS	 PINC_0
#define 	TFT_SD_CS		 PINC_6

#define 	I2C1_SDA 		 PINB_7
#define 	I2C1_SCL 		 PINB_6

#define 	I2C2_SDA 		 PINB_11
#define 	I2C2_SCL 		 PINB_10

//+++++++++++++++++++++++++DEFINE PORTB+++++++++++++++++++++++++++

#define   LCD_RS           PORTB_5
#define   LCD_RW           PORTB_6
#define   LCD_EN           PORTB_7


//+++++++++++++++++++++++++DEFINE PORTC+++++++++++++++++++++++++++
//+++++++++++++++++++++++++DEFINE PORTD+++++++++++++++++++++++++++
//+++++++++++++++++++++++++DEFINE PORTE+++++++++++++++++++++++++++
//+++++++++++++++++++++++++DEFINE PORTF+++++++++++++++++++++++++++
//+++++++++++++++++++++++++DEFINE PORTG+++++++++++++++++++++++++++

#endif
