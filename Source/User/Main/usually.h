#ifndef __USUALLY_H
#define __USUALLY_H

//頭文件調用
#include "stm32f10x.h"
#include "hardware.h"
#include <stdio.h>

//LED引腳定義
#define LED1 PDout(6)	   	//板子上對應於LD1
#define LED2 PDout(12)	   	//板子上對應於LD2
#define LED3 PDout(13)	   	//板子上對應於LD3

//按鍵引腳定義
#define KEY_USER  PCin(13) 	//板子上對應於按鍵USER
#define KEY_S  PEin(0)  	//板子上對應於按鍵JOY-SEN
#define KEY_D  PEin(1)  	//板子上對應於按鍵JOY-DOWN
#define KEY_L  PEin(2)  	//板子上對應於按鍵JOY-LEFT
#define KEY_R  PEin(3)  	//板子上對應於按鍵JOY-RIGHT
#define KEY_U  PEin(4)  	//板子上對應於按鍵JOY-UP

//聲明一個枚舉
enum  						
{							
	 USER=1,				//1
	 SEN,					//2
	 DOWN,					//3
	 LEFT,					//4
	 RIGHT,					//5
	 UP						//6
};
struct Data_Time
{
	uint8_t hour;
	uint8_t min;
	uint8_t sec;			
	//公歷日月年周
	uint16_t w_year;
	uint8_t  w_month;
	uint8_t  w_date;
	uint8_t  week;
};
        

extern void Delay_Ms(uint16_t time);  	 //聲明外部延時函數
extern void Delay_Us(uint16_t time); 	 //聲明外部延時函數

#endif
