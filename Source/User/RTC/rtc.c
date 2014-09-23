/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
**  �ү踹�}�o�O
**	RTC�����t�m
**  �����GRev1.0 
**  ����G2011-6-20
**	�׾¡Gwww.openmcu.com
**	�^�_�Ghttp://shop36995246.taobao.com/   
**  �޳N����s�G153631682 	 �޳NQQ�G77642732 
**  Copyright(c)@���_�q�l	Dream_etd@163.com	
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
#include "usually.h"
#include "usart.h"
#include "rtc.h"

struct Data_Time  timer;  //�w�q�@�Ӯɶ����c���ܶq
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��ƦW��: Init_RTC
** �\��y�z: ADC1��l��
				�t�m��DMA�q�D1
** �Ѽƴy�z�G�L
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
uint8_t Init_RTC(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
																	//�ϯ�PWR�MBKP�~�]����   		
	PWR_BackupAccessCmd(ENABLE);									//�ϯ�RTC�M��ƱH�s���X�� 
	
	if(BKP_ReadBackupRegister(BKP_DR1)!=0x5555)						//�q���w����ƱH�s����Ū�X�ƾڡA�P�_�O�_���Ĥ@���t�m
	{	
      	printf("�����t�m�C�C�C\r\n");																
		BKP_DeInit();												//�N�~�]BKP�������H�s�����]���ʬ٭� 	
		RCC_LSEConfig(RCC_LSE_ON);									//�ϯ�~���C�t���� 32.768KHz
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)			//�ˬd���w��RCC�лx��]�m�P�_,���ݧC�t�����N��
  		{}
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);						//�]�mRTC����(RTCCLK),���LSE�@��RTC����    
		RCC_RTCCLKCmd(ENABLE);										//�ϯ�RTC����  
		RTC_WaitForSynchro();										//����RTC�H�s��(RTC_CNT,RTC_ALR�MRTC_PRL)�PRTC APB�����P�B
		RTC_WaitForLastTask();										//���ݳ̪�@����RTC�H�s�����g�ާ@����
		RTC_ITConfig(RTC_IT_SEC, ENABLE);							//�ϯ�RTC���_
		RTC_WaitForLastTask();										//���ݳ̪�@����RTC�H�s�����g�ާ@����
		RTC_SetPrescaler(32767); 									//�]�mRTC�w���W����  RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1)
		RTC_WaitForLastTask();										//���ݳ̪�@����RTC�H�s�����g�ާ@����
		Time_Set();													//�ɶ��]�m	
    	BKP_WriteBackupRegister(BKP_DR1, 0x5555);					//�V���w����ƱH�s�����g�J�Τ�{�Ǽƾ�0X5555���P�_�лx										
	}																 	
	else															//���O�Ĥ@���t�m �~��p��
	{
		if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)			//�ˬd���w��RCC�лx��]�m�P�_:POR/PDR�_��
		{
      		printf("�W�q�_��C�C�C\r\n");
		}											
		else if(RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)		//�ˬd���w��RCC�лx��]�m�P�_:�޸}�_��
		{
      		printf("�~���_��....\r\n");
		}
    	printf("RTC no calibration needed!\r\n");
		
		RTC_WaitForSynchro();										//���ݳ̪�@����RTC�H�s�����g�ާ@����
		
		RTC_ITConfig(RTC_IT_SEC, ENABLE);							//�ϯ�RTC���_

		RTC_WaitForLastTask();										//���ݳ̪�@����RTC�H�s�����g�ާ@����
	}		    				     
	Time_Get();														//��s�ɶ� 
	
	RCC_ClearFlag();												//�M��RCC���_��лx��
	
	return 0; //ok		
}
//�]�m����
//���J�������ഫ������
//�H1970�~1��1�鬰���
//1970~2099�~���X�k�~��
//��^��:0,���\;��L:���~�N�X.
//����ƾڪ�											 
uint8_t const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; 			//��ץ��ƾڪ�	  

const uint8_t mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};	//���~����������

uint8_t Time_Update(uint16_t syear,uint8_t smon,uint8_t sday,uint8_t hour,uint8_t min,uint8_t sec)
{
	uint16_t t;
	uint32_t seccount=0;
	if(syear<1970||syear>2099)return 1;	   
	for(t=1970;t<syear;t++)											//��Ҧ��~���������ۥ[
		{
		if(Is_Leap_Year(t))seccount+=31622400;						//�|�~��������
		else seccount+=31536000;			  						//���~��������
		}
	smon-=1;
	for(t=0;t<smon;t++)	   											//��e������������Ƭۥ[
		{
		seccount+=(uint32_t)mon_table[t]*86400;						//��������Ƭۥ[
		if(Is_Leap_Year(syear)&&t==1)seccount+=86400;				//�|�~2����W�[�@�Ѫ�������	   
		}
	seccount+=(uint32_t)(sday-1)*86400;								//��e������������Ƭۥ[ 
	seccount+=(uint32_t)hour*3600;									//�p�ɬ�����
	seccount+=(uint32_t)min*60;	 									//����������
	seccount+=sec;													//�̫᪺�����[�W�h
											    
	RTC_WaitForLastTask();											//���ݳ̪�@����RTC�H�s�����g�ާ@����
	RTC_SetCounter(seccount);										//�]�mRTC�p�ƾ�����
	RTC_WaitForLastTask();											//���ݳ̪�@����RTC�H�s�����g�ާ@����  	
	return 0;		
}
//�o���e���ɶ�
//��^��:0,���\;��L:���~�N�X.
uint8_t Time_Get(void)
{
	static uint16_t daycnt=0;
	uint32_t timecount=0; 
	uint32_t temp=0;
	uint16_t temp1=0;	  
	 
	timecount = RTC_GetCounter();									//��o RTC �p�ƾ���(������)			 
	temp=timecount/86400;   //�o��Ѽ�(�����ƹ�����)
	if(daycnt!=temp)//�W�L�@�ѤF
	{	  
		daycnt=temp;
		temp1=1970;	//�q1970�~�}�l
		while(temp>=365)
		{				 
			if(Is_Leap_Year(temp1))//�O�|�~
			{
				if(temp>=366)temp-=366;//�|�~��������
				else {temp1++;break;}  
			}
			else temp-=365;	  //���~ 
			temp1++;  
		}   
		timer.w_year=temp1;//�o��~��
		temp1=0;
		while(temp>=28)//�W�L�F�@�Ӥ�
		{
			if(Is_Leap_Year(timer.w_year)&&temp1==1)//��~�O���O�|�~/2���
			{
				if(temp>=29)temp-=29;//�|�~��������
				else break; 
			}
			else 
			{
				if(temp>=mon_table[temp1])temp-=mon_table[temp1];//���~
				else break;
			}
			temp1++;  
		}
		timer.w_month=temp1+1;//�o����
		timer.w_date=temp+1;  //�o���� 
	}
	temp=timecount%86400;     //�o�������   	   
	timer.hour=temp/3600;     //�p��
	timer.min=(temp%3600)/60; //����	
	timer.sec=(temp%3600)%60; //����
	timer.week=RTC_Get_Week(timer.w_year,timer.w_month,timer.w_date);//����P��   
	return 0;
}
//��o�{�b�O�P���X
//�\��y�z:��J��������o��P��(�u���\1901-2099�~)
//��J�ѼơG�����~��� 
//��^�ȡG�P����																						 
uint8_t RTC_Get_Week(uint16_t year,uint8_t month,uint8_t day)
{	
	uint16_t temp2;
	uint8_t yearH,yearL;
	
	yearH=year/100;	yearL=year%100; 	 
	if (yearH>19)yearL+=100;// �p�G��21�@��,�~���ƥ[100 
  
	temp2=yearL+yearL/4;  	// �ҹL�|�~�ƥu��1900�~���᪺
	temp2=temp2%7; 
	temp2=temp2+day+table_week[month-1];
	if (yearL%4==0&&month<3)temp2--;
	return(temp2%7);
} 
//�P�_�O�_�O�|�~���
//���   1  2  3  4  5  6  7  8  9  10 11 12
//�|�~   31 29 31 30 31 30 31 31 30 31 30 31
//�D�|�~ 31 28 31 30 31 30 31 31 30 31 30 31
//��J:�~��
//��X:�Ӧ~���O���O�|�~.1,�O.0,���O
uint8_t Is_Leap_Year(uint16_t year)
{			  
	if(year%4==0) //������Q4�㰣
	{ 
		if(year%100==0) 
		{ 
			if(year%400==0)return 1;//�p�G�H00����,�٭n��Q400�㰣 	   
			else return 0;   
		}else return 1;   
	}else return 0;	
}
/*****************************************************************************
** ��ƦW��: RTC_IRQHandler
** �\��y�z: RTC���_�A�Ȩ��
				�C��Ĳ�o�@��  
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
*****************************************************************************/
void RTC_IRQHandler(void)
{							    
	if(RTC_GetITStatus(RTC_IT_SEC))			//�������_
	{							
		Time_Get();							//��s�ɶ� 	 
	}
	if(RTC_GetITStatus(RTC_IT_ALR))			//�x�����_
	{
		RTC_ClearITPendingBit(RTC_IT_ALR);	//�M�x�����_		  								 				
	}
	RTC_ClearITPendingBit(RTC_IT_SEC);		//�M�����X�A�������_�лx		  								 
	RTC_WaitForLastTask();					//����RTC�H�s���ާ@����
}
/*****************************************************************************
** ��ƦW��: Time_Set
** �\��y�z: �q�L��L�]�m�ɶ�
					�]�A�~���ɤ���
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
*****************************************************************************/
void Time_Set(void)
{
	uint16_t Data[6];	
	printf("�п�J�~���ɤ���A��p�G20110708103029\r\n");
	Data[0]= Usart_Scanf(2099,4);printf("%d�~\r\n",Data[0]);	
	Data[1]= Usart_Scanf(12,2);  printf("%d��\r\n",Data[1]);
	Data[2]= Usart_Scanf(31,2);  printf("%d��\r\n",Data[2]);
	Data[3]= Usart_Scanf(24,2);	 printf("%d�I\r\n",Data[3]);
	Data[4]= Usart_Scanf(60,2);	 printf("%d��\r\n",Data[4]);
	Data[5]= Usart_Scanf(60,2);	 printf("%d��\r\n",Data[5]);

	printf("%d�~%d��%d��%d�I%d��%d��\r\n",Data[0],Data[1],Data[2],Data[3],Data[4],Data[5]);

  	Time_Update(Data[0],Data[1],Data[2],Data[3],Data[4],Data[5]);
}
/*****************************************************************************
** ��ƦW��: Usart_Scanf
** �\��y�z: ��L��J���
					�]�A�~���ɶ�
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
*****************************************************************************/
uint16_t Usart_Scanf(uint32_t value,uint8_t count)
{
  	uint32_t index = 0;
  	uint32_t tmp[4] = {0, 0, 0, 0};

DATA_TIME :

  	while (index < count)
  	{
    	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
    	{}
    	tmp[index++] = (USART_ReceiveData(USART1));
    	if ((tmp[index - 1] < 0x30) || (tmp[index - 1] > 0x39))
    	{
      		printf("Please enter valid number between 0 and 9\n\r");
      		index--;
    	}
  	}
	if(count<3){index = (tmp[1] - 0x30) + ((tmp[0] - 0x30) * 10);}	
	else {index = (tmp[3] - 0x30) + ((tmp[2] - 0x30) * 10) + ((tmp[1] - 0x30) * 100) + ((tmp[0] - 0x30) * 1000);}
	
  	if (index > value)
  	{
    	printf("Please enter valid number between 0 and %d\n\r", value);
		index = 0;
		goto  DATA_TIME;
  	}
  	return index;
}
