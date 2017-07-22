/**
******************************************************************************
* @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
* @author  MCD Application Team
* @version V3.5.0
* @date    08-April-2011
* @brief   Main Interrupt Service Routines.
*          This file provides template for all exceptions handler and 
*          peripherals interrupt service routine.
******************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "stm32f10x_gpio.h"
/** @addtogroup STM32F10x_StdPeriph_Template
* @{
*/

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

extern uint8_t RxBuffer[];
extern __IO uint8_t RxCounter; 
extern uint8_t NbrOfDataToRead;
extern uint8_t minute,second;

extern uint8_t mLine,mArea,mDir,mMCH;
extern uint16_t mTPD;
extern Motor_Typedef Mo[];
extern uint8_t mNum;
extern MCH_Typedef MCH_Set[];
extern uint16_t TPD_Speed[];
extern uint16_t TPD_Delay[];
extern uint8_t DIR[];
extern uint32_t tim_s[];
/**
* @brief  This function handles NMI exception.
* @param  None
* @retval None
*/
void NMI_Handler(void)
{
}

/**
* @brief  This function handles Hard Fault exception.
* @param  None
* @retval None
*/
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
* @brief  This function handles Memory Manage exception.
* @param  None
* @retval None
*/
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
* @brief  This function handles Bus Fault exception.
* @param  None
* @retval None
*/
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
* @brief  This function handles Usage Fault exception.
* @param  None
* @retval None
*/
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
* @brief  This function handles SVCall exception.
* @param  None
* @retval None
*/
void SVC_Handler(void)
{
}

/**
* @brief  This function handles Debug Monitor exception.
* @param  None
* @retval None
*/
void DebugMon_Handler(void)
{
}

/**
* @brief  This function handles PendSVC exception.
* @param  None
* @retval None
*/
void PendSV_Handler(void)
{
}

void USART1_IRQHandler(void)
{
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
    /* Read one byte from the receive data register */    
    if(RxCounter < NbrOfDataToRead-1)
    {
			RxBuffer[RxCounter++] = USART_ReceiveData(USART1);
			RxBuffer[RxCounter]=0;
    }
  }
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}
void TIM2_IRQHandler(void)
{
  static uint32_t time=0;  
  static uint8_t m=0;
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {   
    if(++time>=100)
    {
      time = 0;
      for(m=0;m<6;m++){        
				if(Mo[m].Pow==RUN){
					tim_s[m]++;
					if(tim_s[m]==1)				
						motor_run(m,DIR[m],CCR1_Val);											
					if(tim_s[m]==60)
						motor_run(m,0,CCR2_Val);               
					if(tim_s[m]>=TPD_Delay[Mo[m].Speed]){          
						motor_res(m);
					}
				}
				else if(Mo[m].Pow==SLEEP){
					Mo[m].Pow=STOP;
					motor_run(m,0,CCR2_Val);
					tim_s[m]=0;
				}
      }
//      GPIO_WriteBit(GPIOC,GPIO_Pin_13,(bit2)?Bit_SET:Bit_RESET);
//      bit2=1-bit2;			
    }
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  }
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
* @brief  This function handles PPP interrupt request.
* @param  None
* @retval None
*/
/*void PPP_IRQHandler(void)
{
}*/

/**
* @}
*/ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
