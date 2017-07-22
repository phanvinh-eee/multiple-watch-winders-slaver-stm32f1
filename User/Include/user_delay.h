/**
  ******************************************************************************
  * Ten Tep		:		    user_delay.h
  * Tac Gia		:	  		Nguyen Quy Nhat
  * Cong Ty		:			MinhHaGroup
  *	Website 	:			MinhHaGroup.com
  * Phien Ban	:			V1.0.0
  * Ngay		:    		31-07-2012
  * Tom Tat   	:	        Khai bao cac ham su dung de tao tre.
  *             			
  *           
  *
  ******************************************************************************
  * Chu Y			:				
  *
  *
  * 
  ******************************************************************************
  */
#ifndef __USER_DELAY_H
#define __USER_DELAY_H

#include "stm32f10x.h"	
/***************************************************************/ 
void TimingDelayDecrement(void);
//Phai goi ham nay truoc khi su dung cac ham delay khac
void delay_init(void);
//Tao tre ms
void delay_ms(uint16_t nms);
//Tao tre us
void delay_20us(uint16_t nus);
void delay_s(uint8_t s);
void SetSysClockTo24(void);
/**************************************************************/
#endif





























