#include "uart_string.h"
#include "main.h"
extern uint8_t RxBuffer[];
extern __IO uint8_t RxCounter; 
extern uint8_t NbrOfDataToRead;
const char mch[]="mch";
const char tpd[]="tpd";
const char dir[]="dir";
const char poo[]="poo";
const char res[]="reset";
uint8_t lch=0;
uint8_t ldv=0;
extern uint8_t mLine,mArea,mDir,mMCH;
extern uint8_t mTPD;
uint8_t mPow=0;
extern Motor_Typedef Mo[];
extern MCH_Typedef MCH_Set[];
char str[20];
uint8_t i=0;
uint8_t gsmchr(uint8_t str[],uint8_t size,uint8_t ch, uint8_t num){
	uint8_t t=0,i=0;
	for(i=0;i<size;i++){
		if(str[i]==ch)t++;
		if(t==num)return i;
	}
	return 0;
}

void RxInit(){
//	uint8_t i=0;
	RxCounter=0;
	RxBuffer[0]=0;
}
uint8_t char2num(char ch){
	uint8_t num=0;
	switch(ch){
		case '0':num=0;
		break;
		case '1':num=1;
		break;
		case '2':num=2;
		break;
		case '3':num=3;
		break;
		case '4':num=4;
		break;
		case '5':num=5;
		break;
		case '6':num=6;
		break;
		case '7':num=7;
		break;
		case '8':num=8;
		break;
		default:num=9;
		break;
	}
	return num;
}
uint8_t read_buffer(){  
	if(strstr((char*)RxBuffer,res)!=0){
		Motor_Init();
		return 4;
	}  	
	lch=char2num(RxBuffer[3]);
	ldv=char2num(RxBuffer[4]);
	mLine=lch*10+ldv;
	mMCH=char2num(RxBuffer[5]);
	mTPD=char2num(RxBuffer[6]);
	mDir=char2num(RxBuffer[7]);
	mPow=char2num(RxBuffer[8]);
	if(strstr((char*)RxBuffer,poo)!=0){
		return 3;
	}
	else if(strstr((char*)RxBuffer,mch)!=0){
		return 0;
	}
	else if(strstr((char*)RxBuffer,tpd)!=0){
		return 1;
	}
	else if(strstr((char*)RxBuffer,dir)!=0){
		return 2;
	}
	return 4;
}
void slave_processing(){
	switch(read_buffer()){
		case 0:
			if(mLine>5){
				sprintf(str,"mch%02d%d%d%d%d",mLine-6,mMCH,mTPD,mDir,mPow);
				USART_SendString(USART2,str);
			}
			else {
				Mo[mLine].MCH=mMCH;
				Mo[mLine].Speed=MCH_Set[mMCH].Speed;
				Mo[mLine].Di=MCH_Set[mMCH].Di;					
				if(Mo[mLine].Pow==RUN)
					Mo[mLine].Pow=SLEEP;
			}
			break;
		case 1:
			if(mLine>5 && mLine<24){
				sprintf(str,"tpd%02d%d%d%d%d",mLine-6,mMCH,mTPD,mDir,mPow);								
			}
			if(mLine==99){
				sprintf(str,"tpd99%d%d%d%d",mMCH,mTPD,mDir,mPow);	
			}			
			else{			
				if(Mo[mLine].Pow==RUN)
					Mo[mLine].Pow=SLEEP;
				sprintf(str,"tpd99%d%d%d%d",mMCH,mTPD,mDir,mPow);	
			}	
			MCH_Set[mMCH].Speed=mTPD;
			USART_SendString(USART2,str);	
			for(i=0;i<6;i++)
				if(Mo[i].MCH==mMCH){
					Mo[i].Speed=mTPD;
				}
			break;
		case 2:
			if(mLine>5 && mLine<24){
				sprintf(str,"dir%02d%d%d%d%d",mLine-6,mMCH,mTPD,mDir,mPow);
				USART_SendString(USART2,str);				
			}
			if(mLine==99){
				sprintf(str,"dir99%d%d%d%d",mMCH,mTPD,mDir,mPow);	
			}			
			else{			
				if(Mo[mLine].Pow==RUN)
					Mo[mLine].Pow=SLEEP;
				sprintf(str,"dir99%d%d%d%d",mMCH,mTPD,mDir,mPow);	
			}
			MCH_Set[mMCH].Di=mDir;
			for(i=0;i<6;i++)
				if(Mo[i].MCH==mMCH){
					Mo[i].Di=mDir;		
				}
			break;
		case 3:
			if(mLine>5 && mLine<24){
				sprintf(str,"poo%02d%d%d%d%d",mLine-6,mMCH,mTPD,mDir,mPow);	
				USART_SendString(USART2,str);					
			}
			else if(mLine<6){
				Mo[mLine].Pow=mPow;
				Mo[mLine].MCH=mMCH;	
				if(mPow==RUN)
				motor_res(mLine);
			}					
			break;
		default:
			break;
	}	
}
