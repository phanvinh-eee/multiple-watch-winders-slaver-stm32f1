/**
******************************************************************************
* Ten Tep		:		    user_timer.c
* Tac Gia		:	  		Nguyen Quy Nhat
* Cong Ty		:			MinhHaGroup
*	Website 	:			MinhHaGroup.com
* Phien Ban	:			V1.0.0
* Ngay		:    		31-07-2012
* Tom Tat   	:       	Dinh nghia cac ham cau hinh cho Timer.           			
*           
*
******************************************************************************
* Chu Y		:			Disable cac ham khong su dung den.
*							Cac timer co cac chuc nang ho tro va cau hinh khac nhau,
*							xem chi tiet tai stm32f10x_tim.c va stm32f10x_tim.h
*							TIM_CounterMode:
- TIM_CounterMode_Up				--> 
- TIM_CounterMode_Down				-->
- TIM_CounterMode_CenterAligned1	-->
- TIM_CounterMode_CenterAligned2	-->
- TIM_CounterMode_CenterAligned3	-->
TIM_ClockDivision
- TIM_CKD_DIV1						-->
- TIM_CKD_DIV2						-->
- TIM_CKD_DIV4						-->
*							
*
*
* 
******************************************************************************
*/
#include "user_timer.h"
uint16_t Channel1Pulse=0;
extern  GPIO_InitTypeDef GPIO;
TIM_OCInitTypeDef  TIM1_OCInitStructure;
TIM_OCInitTypeDef  TIM2_OCInitStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
void  TIMER1_Configuration(void)
{

  TIM_TimeBaseInitTypeDef  TIM1_TimeBaseStructure;
  uint16_t TimerPeriod;
	uint16_t PrescalerValue = 0;
	
  GPIO_InitTypeDef GPIO;
	GPIO.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14;
	GPIO_Init(GPIOB,&GPIO);

  //	TIM_BDTRInitTypeDef TIM3_BDTRInitStructure;
  /*-------------------------------------------------------------------*/	
  PrescalerValue = (uint16_t) (SystemCoreClock / 125000) - 1;
  TimerPeriod = 1249;
  //Chon gia tri chia tan so 0x0001 - 0x000ff
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
  //Chon gia tri chia tan so 0x0001 - 0x000ff	
	TIM_TimeBaseStructInit(&TIM1_TimeBaseStructure);
  TIM1_TimeBaseStructure.TIM_Prescaler = PrescalerValue;						
  //Chon che do dem
  TIM1_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	
  // Chon chu ky 
  TIM1_TimeBaseStructure.TIM_Period =TimerPeriod;
  //Chon gia tri chia clock
  TIM1_TimeBaseStructure.TIM_ClockDivision = 0;
  
  TIM1_TimeBaseStructure.TIM_RepetitionCounter = 0;
  // Cau hinh
  TIM_TimeBaseInit(TIM1,&TIM1_TimeBaseStructure);				
  //++++++++++++++++++++Cau Hinh Output Compare++++++++++++++++++++++++++++ 
  TIM_PrescalerConfig(TIM1, PrescalerValue, TIM_PSCReloadMode_Immediate);
  // che do output_compare

  TIM1_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  
  TIM1_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM1_OCInitStructure.TIM_Pulse = Channel1Pulse;	
  TIM1_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM1_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

  TIM_OC1Init(TIM1, &TIM1_OCInitStructure);
  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
  TIM_OC2Init(TIM1, &TIM1_OCInitStructure);  
  TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(TIM1, ENABLE);
  //TIM_ITConfig(TIM1, TIM_IT_Update,ENABLE);
  /* TIM1 counter enable */
  TIM_Cmd(TIM1, ENABLE);
  
  /* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void  TIMER2_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM2_TimeBaseStructure;
  uint16_t TimerPeriod, PrescalerValue=0;
	
  GPIO_InitTypeDef GPIO;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	GPIO.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO.GPIO_Mode=GPIO_Mode_AF_PP;	
  //timer2
  GPIO.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Init(GPIOA,&GPIO);	
  //	TIM_BDTRInitTypeDef TIM3_BDTRInitStructure;
  /*-------------------------------------------------------------------*/	
  TimerPeriod = 1249;
  PrescalerValue=(uint16_t)((SystemCoreClock)/125000)-1;
  //Chon gia tri chia tan so 0x0001 - 0x000ff	
  TIM2_TimeBaseStructure.TIM_Prescaler = PrescalerValue;						
  //Chon che do dem
  TIM2_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	
  // Chon chu ky 
  TIM2_TimeBaseStructure.TIM_Period =TimerPeriod;
  //Chon gia tri chia clock
  TIM2_TimeBaseStructure.TIM_ClockDivision = 0;
  
     TIM2_TimeBaseStructure.TIM_RepetitionCounter = 0;
  // Cau hinh
  TIM_TimeBaseInit(TIM2,&TIM2_TimeBaseStructure);				
	//  //++++++++++++++++++++Cau Hinh Output Compare++++++++++++++++++++++++++++ 
  TIM_PrescalerConfig(TIM2, PrescalerValue, TIM_PSCReloadMode_Immediate);
	//  che do output_compare
	
  TIM2_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  //Enable Output
  TIM2_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  //Do rong xung
  TIM2_OCInitStructure.TIM_Pulse =Channel1Pulse;						 
  // Chon muc do uu tien 																	
  TIM2_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;		
	TIM2_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  //Cau hinh OC2

  TIM_OC1Init(TIM2, &TIM2_OCInitStructure);
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
  TIM_OC2Init(TIM2, &TIM2_OCInitStructure);
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
//  TIM_OC3Init(TIM2, &TIM2_OCInitStructure);
//  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
//  TIM_OC4Init(TIM2, &TIM2_OCInitStructure);
//  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);	
  TIM_ARRPreloadConfig(TIM2, ENABLE);
  TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE);
  /* TIM1 counter enable */
  TIM_Cmd(TIM2, ENABLE);
  
  /* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM2, ENABLE);
}

void  TIMER3_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  uint16_t TimerPeriod=0,PrescalerValue=0;
	
  //	TIM_BDTRInitTypeDef TIM3_BDTRInitStructure;
  /*-------------------------------------------------------------------*/	
  GPIO_InitTypeDef GPIO;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	GPIO.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO.GPIO_Mode=GPIO_Mode_AF_PP;
	
	GPIO.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init(GPIOA,&GPIO);
	GPIO.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Init(GPIOB,&GPIO);	
  TimerPeriod = 1249;
  PrescalerValue=(uint16_t)(SystemCoreClock/125000)-1;
  //Chon gia tri chia tan so 0x0001 - 0x000ff	
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;						
  //Chon che do dem
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	
  // Chon chu ky 
  TIM_TimeBaseStructure.TIM_Period =TimerPeriod;//1249
  //Chon gia tri chia clock
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  // Cau hinh
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);				
  //++++++++++++++++++++Cau Hinh Output Compare++++++++++++++++++++++++++++ 
  TIM_PrescalerConfig(TIM3, PrescalerValue, TIM_PSCReloadMode_Immediate);
  // che do output_compare
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1 ;	
  // TIM3_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  //Enable Output
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  //Do rong xung
  TIM_OCInitStructure.TIM_Pulse =Channel1Pulse;						 
  // Chon muc do uu tien 																	
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;		
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  //Cau hinh OC2
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC4Init(TIM3, &TIM_OCInitStructure); 
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);	
	TIM_ARRPreloadConfig(TIM3, ENABLE);
  //TIM_ITConfig(TIMx, TIM_IT_Update,ENABLE);
  /* TIM1 counter enable */
  TIM_Cmd(TIM3, ENABLE);
  
  /* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM3, ENABLE);
}

void  TIMER4_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  uint16_t TimerPeriod=0,PrescalerValue=0;
	
  //	TIM_BDTRInitTypeDef TIM3_BDTRInitStructure;
  /*-------------------------------------------------------------------*/	
  GPIO_InitTypeDef GPIO;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	GPIO.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO.GPIO_Mode=GPIO_Mode_AF_PP;
	
	GPIO.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
  GPIO_Init(GPIOB,&GPIO);	
  TimerPeriod = 1249;
  PrescalerValue=(uint16_t)(SystemCoreClock/125000)-1;
  //Chon gia tri chia tan so 0x0001 - 0x000ff	
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;						
  //Chon che do dem
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	
  // Chon chu ky 
  TIM_TimeBaseStructure.TIM_Period =TimerPeriod;//1249
  //Chon gia tri chia clock
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  // Cau hinh
  TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);				
  //++++++++++++++++++++Cau Hinh Output Compare++++++++++++++++++++++++++++ 
  TIM_PrescalerConfig(TIM4, PrescalerValue, TIM_PSCReloadMode_Immediate);
  // che do output_compare
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1 ;	
  // TIM4_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  //Enable Output
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  //Do rong xung
  TIM_OCInitStructure.TIM_Pulse =Channel1Pulse;						 
  // Chon muc do uu tien 																	
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;		
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  //Cau hinh OC2
  TIM_OC1Init(TIM4, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
  TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
  TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
  TIM_OC4Init(TIM4, &TIM_OCInitStructure); 
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);	
	TIM_ARRPreloadConfig(TIM4, ENABLE);
  //TIM_ITConfig(TIMx, TIM_IT_Update,ENABLE);
  /* TIM1 counter enable */
  TIM_Cmd(TIM4, ENABLE);
  
  /* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM4, ENABLE);
}
void  TIMER15_Configuration()
{
  TIM_OCInitTypeDef  TIM15_OCInitStructure;
  TIM_TimeBaseInitTypeDef  TIM15_TimeBaseStructure;
  uint16_t TimerPeriod;
  //	TIM_BDTRInitTypeDef TIM3_BDTRInitStructure;
  /*-------------------------------------------------------------------*/	
  uint16_t PrescalerValue = 0;
  PrescalerValue = (uint16_t) (SystemCoreClock / 125000) - 1;
  TimerPeriod = 1249;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15, ENABLE); 
  //Chon gia tri chia tan so 0x0001 - 0x000ff	
  TIM15_TimeBaseStructure.TIM_Prescaler = PrescalerValue;						
  //Chon che do dem
  TIM15_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	
  // Chon chu ky 
  TIM15_TimeBaseStructure.TIM_Period =TimerPeriod;
  //Chon gia tri chia clock
  TIM15_TimeBaseStructure.TIM_ClockDivision = 0;
  
  TIM15_TimeBaseStructure.TIM_RepetitionCounter = 0;
  // Cau hinh
  TIM_TimeBaseInit(TIM15,&TIM15_TimeBaseStructure);				
  //++++++++++++++++++++Cau Hinh Output Compare++++++++++++++++++++++++++++ 
  TIM_PrescalerConfig(TIM15, PrescalerValue, TIM_PSCReloadMode_Immediate);
  // che do output_compare

  TIM15_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM15_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM15_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	
  TIM15_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	
  TIM_OC2Init(TIM15, &TIM15_OCInitStructure);  
  TIM_OC2PreloadConfig(TIM15, TIM_OCPreload_Enable);	
  TIM_ARRPreloadConfig(TIM15, ENABLE);
  //TIM_ITConfig(TIM1, TIM_IT_Update,ENABLE);
  /* TIM1 counter enable */
  TIM_Cmd(TIM15, ENABLE);
  
  /* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM15, ENABLE);
}
