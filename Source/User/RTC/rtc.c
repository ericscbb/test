/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
**  啟航號開發板
**	RTC時鐘配置
**  版本：Rev1.0 
**  日期：2011-6-20
**	論壇：www.openmcu.com
**	淘寶：http://shop36995246.taobao.com/   
**  技術支持群：153631682 	 技術QQ：77642732 
**  Copyright(c)@旺寶電子	Dream_etd@163.com	
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
#include "usually.h"
#include "usart.h"
#include "rtc.h"

struct Data_Time  timer;  //定義一個時間結構體變量
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: Init_RTC
** 功能描述: ADC1初始化
				配置為DMA通道1
** 參數描述：無
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
uint8_t Init_RTC(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
																	//使能PWR和BKP外設時鐘   		
	PWR_BackupAccessCmd(ENABLE);									//使能RTC和後備寄存器訪問 
	
	if(BKP_ReadBackupRegister(BKP_DR1)!=0x5555)						//從指定的後備寄存器中讀出數據，判斷是否為第一次配置
	{	
      	printf("時鐘配置。。。\r\n");																
		BKP_DeInit();												//將外設BKP的全部寄存器重設為缺省值 	
		RCC_LSEConfig(RCC_LSE_ON);									//使能外部低速時鐘 32.768KHz
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)			//檢查指定的RCC標誌位設置與否,等待低速晶振就緒
  		{}
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);						//設置RTC時鐘(RTCCLK),選擇LSE作為RTC時鐘    
		RCC_RTCCLKCmd(ENABLE);										//使能RTC時鐘  
		RTC_WaitForSynchro();										//等待RTC寄存器(RTC_CNT,RTC_ALR和RTC_PRL)與RTC APB時鐘同步
		RTC_WaitForLastTask();										//等待最近一次對RTC寄存器的寫操作完成
		RTC_ITConfig(RTC_IT_SEC, ENABLE);							//使能RTC秒中斷
		RTC_WaitForLastTask();										//等待最近一次對RTC寄存器的寫操作完成
		RTC_SetPrescaler(32767); 									//設置RTC預分頻的值  RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1)
		RTC_WaitForLastTask();										//等待最近一次對RTC寄存器的寫操作完成
		Time_Set();													//時間設置	
    	BKP_WriteBackupRegister(BKP_DR1, 0x5555);					//向指定的後備寄存器中寫入用戶程序數據0X5555做判斷標誌										
	}																 	
	else															//不是第一次配置 繼續計時
	{
		if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)			//檢查指定的RCC標誌位設置與否:POR/PDR復位
		{
      		printf("上電復位。。。\r\n");
		}											
		else if(RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)		//檢查指定的RCC標誌位設置與否:管腳復位
		{
      		printf("外部復位....\r\n");
		}
    	printf("RTC no calibration needed!\r\n");
		
		RTC_WaitForSynchro();										//等待最近一次對RTC寄存器的寫操作完成
		
		RTC_ITConfig(RTC_IT_SEC, ENABLE);							//使能RTC秒中斷

		RTC_WaitForLastTask();										//等待最近一次對RTC寄存器的寫操作完成
	}		    				     
	Time_Get();														//更新時間 
	
	RCC_ClearFlag();												//清除RCC的復位標誌位
	
	return 0; //ok		
}
//設置時鐘
//把輸入的時鐘轉換為秒鐘
//以1970年1月1日為基準
//1970~2099年為合法年份
//返回值:0,成功;其他:錯誤代碼.
//月份數據表											 
uint8_t const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; 			//月修正數據表	  

const uint8_t mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};	//平年的月份日期表

uint8_t Time_Update(uint16_t syear,uint8_t smon,uint8_t sday,uint8_t hour,uint8_t min,uint8_t sec)
{
	uint16_t t;
	uint32_t seccount=0;
	if(syear<1970||syear>2099)return 1;	   
	for(t=1970;t<syear;t++)											//把所有年份的秒鐘相加
		{
		if(Is_Leap_Year(t))seccount+=31622400;						//閏年的秒鐘數
		else seccount+=31536000;			  						//平年的秒鐘數
		}
	smon-=1;
	for(t=0;t<smon;t++)	   											//把前面月份的秒鐘數相加
		{
		seccount+=(uint32_t)mon_table[t]*86400;						//月份秒鐘數相加
		if(Is_Leap_Year(syear)&&t==1)seccount+=86400;				//閏年2月份增加一天的秒鐘數	   
		}
	seccount+=(uint32_t)(sday-1)*86400;								//把前面日期的秒鐘數相加 
	seccount+=(uint32_t)hour*3600;									//小時秒鐘數
	seccount+=(uint32_t)min*60;	 									//分鐘秒鐘數
	seccount+=sec;													//最後的秒鐘加上去
											    
	RTC_WaitForLastTask();											//等待最近一次對RTC寄存器的寫操作完成
	RTC_SetCounter(seccount);										//設置RTC計數器的值
	RTC_WaitForLastTask();											//等待最近一次對RTC寄存器的寫操作完成  	
	return 0;		
}
//得到當前的時間
//返回值:0,成功;其他:錯誤代碼.
uint8_t Time_Get(void)
{
	static uint16_t daycnt=0;
	uint32_t timecount=0; 
	uint32_t temp=0;
	uint16_t temp1=0;	  
	 
	timecount = RTC_GetCounter();									//獲得 RTC 計數器值(秒鐘數)			 
	temp=timecount/86400;   //得到天數(秒鐘數對應的)
	if(daycnt!=temp)//超過一天了
	{	  
		daycnt=temp;
		temp1=1970;	//從1970年開始
		while(temp>=365)
		{				 
			if(Is_Leap_Year(temp1))//是閏年
			{
				if(temp>=366)temp-=366;//閏年的秒鐘數
				else {temp1++;break;}  
			}
			else temp-=365;	  //平年 
			temp1++;  
		}   
		timer.w_year=temp1;//得到年份
		temp1=0;
		while(temp>=28)//超過了一個月
		{
			if(Is_Leap_Year(timer.w_year)&&temp1==1)//當年是不是閏年/2月份
			{
				if(temp>=29)temp-=29;//閏年的秒鐘數
				else break; 
			}
			else 
			{
				if(temp>=mon_table[temp1])temp-=mon_table[temp1];//平年
				else break;
			}
			temp1++;  
		}
		timer.w_month=temp1+1;//得到月份
		timer.w_date=temp+1;  //得到日期 
	}
	temp=timecount%86400;     //得到秒鐘數   	   
	timer.hour=temp/3600;     //小時
	timer.min=(temp%3600)/60; //分鐘	
	timer.sec=(temp%3600)%60; //秒鐘
	timer.week=RTC_Get_Week(timer.w_year,timer.w_month,timer.w_date);//獲取星期   
	return 0;
}
//獲得現在是星期幾
//功能描述:輸入公歷日期得到星期(只允許1901-2099年)
//輸入參數：公歷年月日 
//返回值：星期號																						 
uint8_t RTC_Get_Week(uint16_t year,uint8_t month,uint8_t day)
{	
	uint16_t temp2;
	uint8_t yearH,yearL;
	
	yearH=year/100;	yearL=year%100; 	 
	if (yearH>19)yearL+=100;// 如果為21世紀,年份數加100 
  
	temp2=yearL+yearL/4;  	// 所過閏年數只算1900年之後的
	temp2=temp2%7; 
	temp2=temp2+day+table_week[month-1];
	if (yearL%4==0&&month<3)temp2--;
	return(temp2%7);
} 
//判斷是否是閏年函數
//月份   1  2  3  4  5  6  7  8  9  10 11 12
//閏年   31 29 31 30 31 30 31 31 30 31 30 31
//非閏年 31 28 31 30 31 30 31 31 30 31 30 31
//輸入:年份
//輸出:該年份是不是閏年.1,是.0,不是
uint8_t Is_Leap_Year(uint16_t year)
{			  
	if(year%4==0) //必須能被4整除
	{ 
		if(year%100==0) 
		{ 
			if(year%400==0)return 1;//如果以00結尾,還要能被400整除 	   
			else return 0;   
		}else return 1;   
	}else return 0;	
}
/*****************************************************************************
** 函數名稱: RTC_IRQHandler
** 功能描述: RTC中斷服務函數
				每秒觸發一次  
** 作  　者: Dream
** 日　  期: 2011年6月20日
*****************************************************************************/
void RTC_IRQHandler(void)
{							    
	if(RTC_GetITStatus(RTC_IT_SEC))			//秒鐘中斷
	{							
		Time_Get();							//更新時間 	 
	}
	if(RTC_GetITStatus(RTC_IT_ALR))			//鬧鐘中斷
	{
		RTC_ClearITPendingBit(RTC_IT_ALR);	//清鬧鐘中斷		  								 				
	}
	RTC_ClearITPendingBit(RTC_IT_SEC);		//清除溢出，秒鐘中斷標誌		  								 
	RTC_WaitForLastTask();					//等待RTC寄存器操作完成
}
/*****************************************************************************
** 函數名稱: Time_Set
** 功能描述: 通過鍵盤設置時間
					包括年月日時分秒
** 作  　者: Dream
** 日　  期: 2011年6月20日
*****************************************************************************/
void Time_Set(void)
{
	uint16_t Data[6];	
	printf("請輸入年月日時分秒，比如：20110708103029\r\n");
	Data[0]= Usart_Scanf(2099,4);printf("%d年\r\n",Data[0]);	
	Data[1]= Usart_Scanf(12,2);  printf("%d月\r\n",Data[1]);
	Data[2]= Usart_Scanf(31,2);  printf("%d日\r\n",Data[2]);
	Data[3]= Usart_Scanf(24,2);	 printf("%d點\r\n",Data[3]);
	Data[4]= Usart_Scanf(60,2);	 printf("%d分\r\n",Data[4]);
	Data[5]= Usart_Scanf(60,2);	 printf("%d秒\r\n",Data[5]);

	printf("%d年%d月%d日%d點%d分%d秒\r\n",Data[0],Data[1],Data[2],Data[3],Data[4],Data[5]);

  	Time_Update(Data[0],Data[1],Data[2],Data[3],Data[4],Data[5]);
}
/*****************************************************************************
** 函數名稱: Usart_Scanf
** 功能描述: 鍵盤輸入函數
					包括年月日時間
** 作  　者: Dream
** 日　  期: 2011年6月20日
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
