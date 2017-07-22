/**
******************************************************************************
* Ten Tep          :     user_usart.c
* Tac Gia          :     Nguyen Quy Nhat
* Cong Ty          :     MinhHaGroup
* Website          :     MinhHaGroup.com
* Phien Ban        :     V1.0.0
* Ngay             :     31-07-2012
* Tom Tat          :     Dinh nghia cac ham duoc su dung de dieu khien khoi USART.					          			
*           				
*
******************************************************************************
* Chu Y						 :				
*										+ Tuy theo muc dich su dung ma lua chon cac cau hinh cho 			
*											phu hop.
*										+ Phai cau hinh GPIO la cac chan USART tuong ung tai 
*											file user_gpio.c
*										+ Neu su dung them cac chuc nang interrupt, dma...
*											thi ta phai cau hinh cho cac chuc nang do dua vao
*											cac file tuong ung can su dung (user_nvic, user_interrupt
*                     , user_dma.....);
*										+ Mot so cau hinh, chuc nang co the khong duoc su dung trong
*											mot bo USART, de biet chi tiet xem tai file stm32f10x_usart.c
*										+ file nay cau hinh cho USART 1,2,3. Neu su dung cac USART
*											khac ta se khai bao, dinh nghia tuong tu cac ham dua theo 
*                     cac USART tuong ung.
*
*
* 
******************************************************************************
*/
#include "user_usart.h"

void USART1_Configuration(void)									
{
  USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO;	
	
	GPIO.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO.GPIO_Mode=GPIO_Mode_IN_FLOATING;
  GPIO.GPIO_Pin=GPIO_Pin_10;
  GPIO_Init(GPIOA,&GPIO); 
	
  GPIO.GPIO_Mode=GPIO_Mode_AF_PP;
  GPIO.GPIO_Pin=GPIO_Pin_9;
  GPIO_Init(GPIOA,&GPIO);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = 115200;				  //Chon phuong thuc truyen nhan
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//
  USART_Init(USART1, &USART_InitStructure);											 //
  //Cau hinh ngat nhan du lieu
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  
  //Cau hinh ngat truyen du lieu
  //USART_ITConfig(USART1, USART_IT_TXE, ENABLE);						//
  //Kich hoat hoat dong cua USART
  USART_Cmd(USART1, ENABLE);	
}
void USART2_Configuration(void)									
{
  USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO;
 	GPIO.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO.GPIO_Mode=GPIO_Mode_IN_FLOATING;
  GPIO.GPIO_Pin=GPIO_Pin_3;
  GPIO_Init(GPIOA,&GPIO); 
	
  GPIO.GPIO_Mode=GPIO_Mode_AF_PP;
  GPIO.GPIO_Pin=GPIO_Pin_2;
  GPIO_Init(GPIOA,&GPIO); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = 115200;		
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//
  
  /* Configure USARTx */
  USART_Init(USART2, &USART_InitStructure);							//  
  /* Enable USARTx Receive and Transmit interrupts */
	//  USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);       
	//  USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);			
  
  /* Enable the USARTx */
  USART_Cmd(USART2, ENABLE);	
}

void USART_SendString(USART_TypeDef* USARTx, char*str)
{
  while (*str)
  {
		while (USART_GetFlagStatus(USARTx , USART_FLAG_TXE) == RESET){}
    //USART_SendData(USARTx,*str); 
		USARTx ->DR = (*str & 0xff);
    str++;
  }
}
//------------------------------------------------------------------------// 
void USART_OUT(USART_TypeDef* USARTx, char *Data,...){ 
  const char *s;
  int d;
  double f;
  char buf[16];
  va_list ap;
  va_start(ap, Data);
  
  while(*Data!=0){				                          //
    if(*Data==0x5c){									  //'\'
      switch (*++Data){
      case 'r':							          //
        USART_SendData(USARTx, 0x0d);	   
        
        Data++;
        break;
      case 'n':							          //
        USART_SendData(USARTx, 0x0a);	
        Data++;
        break;
        
      default:
        Data++;
        break;
      }		 
    }
    else if(*Data=='%'){									  //
      switch (*++Data){				
      case 's':										  //
        s = va_arg(ap, const char *);
        for ( ; *s; s++) {
          USART_SendData(USARTx,*s);
          while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
        }
        Data++;
        break;
      case 'd':									  //
        d = va_arg(ap, int);
        itoa(d, buf, 10);
        for (s = buf; *s; s++) {
          USART_SendData(USARTx,*s);
          while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
        }
        Data++;
        break;
      case 'f':									  //
        f = va_arg(ap, double);
        itoa(f, buf, 10);
        for (s = buf; *s; s++) {
          USART_SendData(USARTx,*s);
          while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
        }
        Data++;
        break;
      default:
        Data++;
        break;
      }		 
    }
    else USART_SendData(USARTx, *Data++);
    while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
  }
}

//------------------------------------------------------------------------// 
char *itoa(int value, char *string, int radix)
{
  int     i, d;
  int     flag = 0;
  char    *ptr = string;
  
  /* This implementation only works for decimal numbers. */
  if (radix != 10)
  {
    *ptr = 0;
    return string;
  }
  
  if (!value)
  {
    *ptr++ = 0x30;
    *ptr = 0;
    return string;
  }
  
  /* if this is a negative value insert the minus sign. */
  if (value < 0)
  {
    *ptr++ = '-';
    
    /* Make the value positive. */
    value *= -1;
  }
  
  for (i = 10000; i > 0; i /= 10)
  {
    d = value / i;
    
    if (d || flag)
    {
      *ptr++ = (char)(d + 0x30);
      value -= (d * i);
      flag = 1;
    }
  }
  
  /* Null terminate the string. */
  *ptr = 0;
  
  return string;
  
} /* NCL_Itoa */
