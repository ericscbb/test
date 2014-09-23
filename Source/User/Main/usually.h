#ifndef __USUALLY_H
#define __USUALLY_H

//�Y���ե�
#include "stm32f10x.h"
#include "hardware.h"
#include <stdio.h>

//LED�޸}�w�q
#define LED1 PDout(6)	   	//�O�l�W������LD1
#define LED2 PDout(12)	   	//�O�l�W������LD2
#define LED3 PDout(13)	   	//�O�l�W������LD3

//����޸}�w�q
#define KEY_USER  PCin(13) 	//�O�l�W���������USER
#define KEY_S  PEin(0)  	//�O�l�W���������JOY-SEN
#define KEY_D  PEin(1)  	//�O�l�W���������JOY-DOWN
#define KEY_L  PEin(2)  	//�O�l�W���������JOY-LEFT
#define KEY_R  PEin(3)  	//�O�l�W���������JOY-RIGHT
#define KEY_U  PEin(4)  	//�O�l�W���������JOY-UP

//�n���@�ӪT�|
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
	//�������~�P
	uint16_t w_year;
	uint8_t  w_month;
	uint8_t  w_date;
	uint8_t  week;
};
        

extern void Delay_Ms(uint16_t time);  	 //�n���~�����ɨ��
extern void Delay_Us(uint16_t time); 	 //�n���~�����ɨ��

#endif
