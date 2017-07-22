#include "main.h"
#include <stdio.h>

typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;
uint32_t TPD_Speed[4]={650,950,1250,1850};
uint16_t TPD_Delay[4]={798,546,415,280};
MCH_Typedef MCH_Set[4];//luu tru cau hinh
Motor_Typedef Mo[6];
uint8_t mNum=0;
uint8_t minute=0,second=0;

#define TxBufferSize   (countof(TxBuffer)-1)
#define RxBufferSize   10

/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))
/* Private function prototypes -----------------------------------------------*/

//#ifdef __GNUC__
///* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
//set to 'Yes') calls __io_putchar() */
//#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
//#else
//#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
//#endif /* __GNUC__ */
char RxBuffer[RxBufferSize+1];
__IO uint8_t RxCounter = 0x00; 
uint8_t NbrOfDataToRead = RxBufferSize;
__IO TestStatus TransferStatus = FAILED; 
uint8_t mLine=0,mArea=0,mDir=0,mMCH=0;
uint8_t mTPD=0;
	GPIO_InitTypeDef GPIO;
uint8_t m=0;
int main(){	  
//	static uint8_t bit=0;		
	
//	uint8_t i=0;
//  uint8_t str2[20];
	SetSysClockTo24();
	SystemCoreClockUpdate();
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);
	
  GPIO_Configuration();
  NVIC_Configuration(); 
	TIMER1_Configuration();
	TIMER2_Configuration();
	TIMER3_Configuration();
	TIMER4_Configuration();
	USART1_Configuration();
	USART2_Configuration();
  Motor_Init();
	delay_init();
	RxInit();
  while(1){
		if(RxCounter!=0){			
			slave_processing();
			RxInit();
		}
		delay_ms(80);
//		USART_SendString(USART1,RxBuffer);
//		RxInit();
//		delay_ms(1000);
//		USART_SendString(USART1,"RxBuffer");
//		delay_ms(100);
  }
}
void Motor_Init(){
	uint8_t i=0;
	for(i=0;i<4;i++){
		MCH_Set[i].Di=RIGHT;
		MCH_Set[i].Speed=mTPD;
	}
  for(i=0;i<6;i++){
		Mo[i].Pow=SLEEP;
		Mo[i].Di=MCH_Set[mMCH].Di;
		Mo[i].Speed=MCH_Set[mMCH].Speed;
		Mo[i].MCH=mMCH;
  }
	//USART_SendString(USART2,"reset");
}


//PUTCHAR_PROTOTYPE
//{	
//  /* Place your implementation of fputc here */
//  /* e.g. write a character to the USART */
//  USART_SendData(USART1, (uint8_t) ch);
//  
//  //  /* Loop until the end of transmission */
//  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
//  {}
//  
//  return ch;
//}
#ifdef USE_FULL_ASSERT
void assert_failed(*uint8_t file, uint32_t line){
  while(1);
}
#endif
