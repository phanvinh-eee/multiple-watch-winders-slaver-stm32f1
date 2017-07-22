#include "lcd_led.h"
#include "main.h"
uint8_t digits[]={0xaf, 0xa0, 0x6d, 0xe9, 0xe2,0xcb,0xcf,0xa1,0xef,0xeb,0x00};
uint8_t area[]={8,4,2,1,0};
uint8_t DIR[]={0,0,0,0,0,0};
uint32_t tim_s[]={0,0,0,0,0,0};
extern uint8_t mLine,mArea,mDir,mMCH;
extern uint16_t mTPD;
extern Motor_Typedef Mo[];
extern uint8_t mNum;
extern MCH_Typedef MCH_Set[];
extern uint16_t TPD_Speed[];
extern uint16_t TPD_Delay[];
extern __IO uint8_t RxCounter;

void motor_res(uint8_t mo)
{
	tim_s[mo]=0;
	if(Mo[mo].Di==BOTH)
		DIR[mo]=1-DIR[mo];
	else
		DIR[mo]=Mo[mo].Di;
	motor_run(mo,DIR[mo],CCR4_Val);
}
void motor_run(uint8_t mo, uint8_t dir, uint16_t ccr)
{
	uint16_t ccr1;
	uint16_t ccr2;
	if(dir==1){
		ccr1=(uint16_t)ccr;
		ccr2=(uint16_t)CCR2_Val;
	}
	else{
		ccr1=CCR2_Val;
		ccr2=ccr;		
	}
switch(mo){  
	case 0:		
		TIM3->CCR3=ccr1;
		TIM3->CCR4=ccr2;
		break;
	case 1:		
		TIM3->CCR1=ccr1;
		TIM3->CCR2=ccr2;	
		break;	
	case 2:		
		TIM2->CCR1=ccr1;
		TIM2->CCR2=ccr2;		
		break;
	case 3:
		TIM4->CCR3=ccr1;
		TIM4->CCR4=ccr2;	
		break;
	case 4:
		TIM4->CCR1=ccr1;
		TIM4->CCR2=ccr2;	
		break;
	case 5:
		TIM1->CCR1=ccr1;
		TIM1->CCR2=ccr2;		
		break;
	default:break;
}
	}
	
