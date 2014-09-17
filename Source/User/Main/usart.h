#ifndef __USART_H
#define __USART_H

//頭文件包含
#include "stdio.h"	 
#include <string.h>

//函數聲明
void USART1_Send_Byte(u16 dat);
uint8_t USART1_Receive_Byte(void);
void Init_Usart(void);
void Usart_Configure(uint32_t BaudRate); 

#endif
