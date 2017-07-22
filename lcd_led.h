#ifndef __LCD_LED_H
#define __LCD_LED_H
#include "main.h"
#define cs         GPIOA,GPIO_Pin_8 
#define wr         GPIOB,GPIO_Pin_15 
#define dat        GPIOB,GPIO_Pin_12 
#define CCR1_Val (uint16_t)600
#define CCR2_Val (uint16_t)0
#define CCR4_Val (uint16_t)1249
#define bias            0x56
#define system          0x02 
#define lcdon           0x06 
#define output_low(d) GPIO_ResetBits(d)
#define output_high(d) GPIO_SetBits(d)
void printnum(uint8_t num, uint8_t pos_led, uint8_t dp);
void print_screen(uint8_t area,uint8_t line, uint8_t mch, uint16_t tpd, uint8_t dir,uint8_t pow);
void sendbit_1621(uint8_t data,uint8_t cnt);
void senddatabit_1621(uint8_t data,uint8_t cnt);
void lcd1621_init(void);
void sendcmd(uint8_t command);
void write_1621(uint8_t addr,uint8_t data);
void writeall_1621(unsigned char addr,unsigned char *p,unsigned char cnt);
void lcd_clear(void);
void control(void);
void motor_res(uint8_t mo);
void motor_run(uint8_t mo, uint8_t dir, uint16_t ccr);
#endif
