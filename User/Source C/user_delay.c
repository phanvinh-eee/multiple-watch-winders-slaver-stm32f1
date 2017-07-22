/**
  ******************************************************************************
  * Ten Tep		:		    user_delay.c
  * Tac Gia		:	  		Nguyen Quy Nhat
  * Cong Ty		:			MinhHaGroup
  * Website 	:			MinhHaGroup.com
  * Phien Ban	:			V1.0.0
  * Ngay		:    		31-07-2012
  * Tom Tat   	:       	Dinh nghia cac ham su dung de tao tre.
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
#include "user_delay.h"
 
__IO uint32_t Timer;

void TimingDelayDecrement(void){
  if(Timer!=0x00)
  Timer--;
}
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  TimingDelayDecrement();
}

void delay_init()
{
  if(SysTick_Config(SystemCoreClock/50000))
    while(1);
}								    
void delay_20us(u16 nTime)
{	 		  	  
  Timer=nTime;
  while(Timer!=0);
}   	    								   
void delay_ms(u16 mTime)
{			
  while(mTime--){
    delay_20us(50);
  }
}
void delay_s(u8 second){
  uint32_t sTimer;
  sTimer=second*1000;
  delay_ms(sTimer);
}
void SetSysClockTo24(void){
  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------*/    
  /* RCC system reset(for debug purpose) */ 
	uint8_t HSEStartUpStatus; 
  RCC_DeInit(); 

  /* Enable HSE */ 
  RCC_HSEConfig(RCC_HSE_ON); 
 
  /* Wait till HSE is ready */ 
  HSEStartUpStatus = RCC_WaitForHSEStartUp(); 
 
  if (HSEStartUpStatus == SUCCESS) 
  { 
    /* Flash 0 wait state */ 
    FLASH_SetLatency(FLASH_Latency_0); 
    /* HCLK = SYSCLK */ 
    RCC_HCLKConfig(RCC_SYSCLK_Div1);  
   
    /* PCLK2 = HCLK */ 
    RCC_PCLK2Config(RCC_HCLK_Div1);  
 
    /* PCLK1 = HCLK */ 
    RCC_PCLK1Config(RCC_HCLK_Div1); 
     
    /* PLLCLK = (8MHz) * 3 = 24 MHz */ 
    RCC_PREDIV1Config(RCC_PREDIV1_Source_HSE, RCC_PREDIV1_Div1); 
    RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_3); 
 
    /* Enable PLL */  
    RCC_PLLCmd(ENABLE); 
 
    /* Wait till PLL is ready */ 
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) 
    { 
    } 
 
    /* Select PLL as system clock source */ 
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); 
 
    /* Wait till PLL is used as system clock source */ 
    while (RCC_GetSYSCLKSource() != 0x08) 
    { 
    } 
  } 	
}



































