/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
**	Main Function
**  版本：Rev1.0
**  日期：2012-01-01
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

//頭文件調用
#include "usually.h"
#include "usart.h"
#include "LCD_Drive.h"
#include "sdcard.h"
#include "ff.h"
#include "24LC02.h"
#include "iic.h"
#include "rtc.h"
#include "rmi.h"


//聲明外部變量
//extern  uint8_t    gImage_rainbow[];

//聲明變量
uint8_t I2C_Address;
uint8_t I2C_Write[]= {"ERIC:I2C Test!"};
uint8_t I2C_NULL[]= {"                                   "};
#define  Lenth  sizeof(I2C_Write)
uint8_t  I2C_Read[Lenth];
uint16_t  TIM_Count;	//定時器計數
extern  struct    Data_Time  timer;
uint16_t  SendBuff[5200];
const  uint8_t TEXT_TO_SEND[]= {"DMA USART TEST....\r\n"};
long  counter=0;

SD_CardInfo  SDCardInfo;
SD_Error  SD_Status = SD_OK;
float  SD_SIZE;

FATFS file;
FIL fsrc, fdst;      // file objects
FRESULT res;
BYTE buff_filename[9][13];	//最多只能讀9個文件，保存9個文件名,文件名採用短文件名，最多13個字符

DMA_InitTypeDef DMA_InitStructure;									//定義DMA初始化結構體

//函數申明
void Init_LED(void);
void Init_NVIC(void);
void Init_KEY(void);
void Init_ATTN(void);
uint8_t KEY_Scan(void);
void Delay_Ms(uint16_t time);
void Delay_Us(uint16_t time);
uint8_t Stringcopy(BYTE *buff_to,BYTE *buff_from);
void Init_TIMER(void);
void TIM_Delay(uint16_t time);
void Init_DMA(void);


//RMI
#define MAXPAGE	3
u8 StatusCode=0;
u8 tmpBuf[4];
extern u8 totalInts;
extern u8 F01_RMI_Data0;
void CheckIntSource(u8 intval);
extern u8 F01_RMI_Ctrl0;
bool LimitCheck;
bool b_infinite = FALSE;

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: main
** 功能描述: 主函數入口
** 參數描述：	不支持文件名漢字顯示
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
int main(void)
{
  u32 Dev_Serial0, Dev_Serial1, Dev_Serial2;
  u8 test[20];

  uint8_t Key;
//	uint16_t i=0;
  uint8_t t=0;
  uint8_t	pn=0;
//	uint8_t j,mask=0;
//	u8 tmpBuf[5];

//  	FILINFO finfo;
//  	DIR dirs;
//  	char path[50]={"0:/"};
//	uint8_t i_name =0;

  Dev_Serial0 = *(vu32 *)(0x1FFFF7E8);
  Dev_Serial1 = *(vu32 *)(0x1FFFF7EC);
  Dev_Serial2 = *(vu32 *)(0x1FFFF7F0);

  SystemInit();				//系統時鐘配置

  Init_NVIC();				//中斷向量表註冊函數

  Init_Usart();				//串口引腳配置
  Usart_Configure(115200);	//串口配置 設置波特率為115200
  Init_LED();					//LED初始化
  Init_KEY();					//按鍵初始化

  Init_DMA();						//DMA串口初始化

  Init_IIC();					//24LC02初始化

  Init_TIMER();				//定時器初始化

  Init_LCD();	   				//LCD初始化

  Init_ATTN();

  TextColor = GREEN; 			//賦予文本顏色為BLUE
  BlackColor = BLACK;			//賦予背景顏色為BLACK
//  Disp_LCDBmp(0,0,55,41,gImage_rainbow);   							//顯示一張大小99*97的圖片

  printf("<-----  STM32 EVB TEST  ----->\r\n");
  printf("Unique Device ID, 96 Bit: %08X,%08X,%08X.\r\n",Dev_Serial0,Dev_Serial1,Dev_Serial2);

//	Disp_LCDString(80,120,"2011-12-20");
  Disp_LCDString(60,0,"<STM32>");
//	Disp_LCDString(0,80,"SD: .  GByte");

  Init_RTC();					//內部RTC初始化


  I2C_Int_Set(0);

//	Disp_LCDString(60,300,"Time Set OK!!!    ");
  Disp_LCDString(124,0,"    年  月  日");  //顯示年月日
  Disp_LCDString(170,15,"  :  :  ");		  //顯示時分秒

  LCD_ShowString(0,30,"IM:",GREEN);
  LCD_ShowString(72,30,"RR:",GREEN);
  LCD_ShowString(148,30,"BM:",GREEN);

  LCD_ShowString(0,44,"F0<X,Y,Z>:    ,    ,",YELLOW);

  LED3=1;

//<----		  RMI4 Data
  
  I2C_Address = find_CP_IIC_address();
//  I2C_Address = 0x20;

  if(I2C_Address)
  {
    printf("I2C Address: 0x%x\r\n",I2C_Address);
  }
  else
  {
    printf("Error: I2C Address not found!!!\r\n");
    Disp_LCDString(0,280,"No CP!!!");
    while(1);
  }

  
//	RMI_Reset(I2C_Address);
//
//	read_all_reg();
//	printf("packrat high byte : 0x%x\r\n",I2C_RMI_BufferRead_cont(I2C_Address,0xbe,3));
  for(pn=0; pn<MAXPAGE; pn++)
  {
    printf("PaGe : %d\r\n",pn);
    I2C_RMI_BufferWrite(I2C_Address,Page_Select_register,pn);
    PDT_scan();
  }

//Back to default page
  I2C_RMI_BufferWrite(I2C_Address,Page_Select_register,0);
//  read_all_reg();

  printf("constructFunc11 run!\r\n");
  constructFunc11();
  printf("constructFunc01 run!\r\n");
  constructFunc01();
  printf("constructFunc34 run!\r\n");
  constructFunc34();
  printf("constructFunc54 run!\r\n");
  constructFunc54();
  printf("constructFunc1A run!\r\n");
  constructFunc1A();
  printf("constructFunc31 run!\r\n");
  constructFunc31();


//Back to default page
  I2C_RMI_BufferWrite(I2C_Address,Page_Select_register,0);

  CheckReportMode();
  Get_RMI_MaxPos();

//  I2C_RMI_BufferWrite(I2C_Address,F01_RMI_Ctrl0,1);

//Back to default page
  I2C_RMI_BufferWrite(I2C_Address,Page_Select_register,0);
//  read_all_reg();

// read_attn_reg();
  I2C_Int_Set(1);
  RMI_Reset();
  Clean_RMI_Reset();

 // readRMI(0x9A,test,4);
 // printf("REG 0x9A cont. read 0x%x, 0x%x,read 0x%x, 0x%x.\r\n",test[0],test[1],test[2],test[3]);

  readRMI(0xC6,test,16);
  printf("REG 0xC6 cont. read 0x%x, 0x%x,read 0x%x, 0x%x.\r\n",test[0],test[1],test[2],test[3]);
  printf("REG 0xC6 cont. read 0x%x, 0x%x,read 0x%x, 0x%x.\r\n",test[4],test[5],test[6],test[7]);
  printf("REG 0xC6 cont. read 0x%x, 0x%x,read 0x%x, 0x%x.\r\n",test[8],test[9],test[10],test[11]);
  printf("REG 0xC6 cont. read 0x%x, 0x%x,read 0x%x, 0x%x.\r\n",test[12],test[13],test[14],test[15]);

  printf("Func01 Query: Firmware Revision ID:%s  \r\n",test);
//2D
  RMI_LCDDrawRectangle(0,60,190,310,WHITE);

//B0
  RMI_LCDDrawRectangle(200,60,220,80,WHITE);
  Disp_LCDString(222,60,"B0");
//B1
  RMI_LCDDrawRectangle(200,100,220,120,WHITE);
  Disp_LCDString(222,100,"B1");
//B2
  RMI_LCDDrawRectangle(200,140,220,160,WHITE);
  Disp_LCDString(222,140,"B2");
//B3
  RMI_LCDDrawRectangle(200,180,220,200,WHITE);
  Disp_LCDString(222,180,"B3");

  Disp_LCDString(200,250,"F_#");

//Test
//  LCD_FulfillArea(200,220,220,240,RED);

//Set fast relax rate to 0xFF
//Page 1
//  I2C_RMI_BufferWrite(I2C_Address,Page_Select_register,1);
//    I2C_RMI_BufferWrite(I2C_Address,F54_ANALOG_CTRL13,0xFF);
//	 	 Set_ForceUpdate();
// printf("Fast relax rate:%d\r\n",I2C_RMI_BufferRead(I2C_Address,F54_ANALOG_CTRL13));

//85Hz report rate
//Back to default page
//  I2C_RMI_BufferWrite(I2C_Address,Page_Select_register,0);
//     I2C_RMI_BufferWrite(I2C_Address,0xF8,0x55);

//printf("Report rate:%d\r\n",I2C_RMI_BufferRead(I2C_Address,0xF8));
//--------RMI

  while(1)
  {
    if(t!=timer.sec)
    {
      TextColor = WHITE; 			//賦予文本顏色為BLUE

      t=timer.sec;
      LCD_ShowNum(124,0,timer.w_year,4);
      LCD_ShowNum(172,0,timer.w_month,2);
      LCD_ShowNum(204,0,timer.w_date,2);

      switch(timer.week)
      {
        case 0:
          Disp_LCDString(133,15,"Sun.");
          break;
        case 1:
          Disp_LCDString(133,15,"Mon.");
          break;
        case 2:
          Disp_LCDString(133,15,"Tue.");
          break;
        case 3:
          Disp_LCDString(133,15,"Wed.");
          break;
        case 4:
          Disp_LCDString(133,15,"Thu.");
          break;
        case 5:
          Disp_LCDString(133,15,"Fri.");
          break;
        case 6:
          Disp_LCDString(133,15,"Sat.");
          break;
      }
      LCD_ShowNum(170,15,timer.hour,2);
      LCD_ShowNum(194,15,timer.min,2);
      LCD_ShowNum(218,15,timer.sec,2);
      LED1=~LED1;										//LED1閃爍，程序在運行
    }

    Key = KEY_Scan();

    if(Key==USER)
    {
      printf("Key_User is pressed!!!RMI_Reset() & Clean RMI_Reset().\r\n");

      b_infinite = FALSE;
 //     RMI_Reset();
//      Clean_RMI_Reset();
      SynaReadBootloadID();
      SynaReadFirmwareInfo();
      SynaReadConfigInfo();
      CompleteReflash();
    }
    else if(Key==UP)
    {
      printf("Key_UP is pressed!!!\r\n");

      LimitCheck = TRUE;
      f54_SetCapacitanceImageReport();
    }
    else if(Key==DOWN)
    {
      printf("Key_DOWN is pressed!!!\r\n");
      LimitCheck = FALSE;
      b_infinite = TRUE;

      f54_Set16BitImageReading();
    }
    else if(Key==LEFT)
    {
      printf("Key_LEFT is pressed!!!\r\n");

//default page
      printf("Register Data of Page 0.\r\n");

      I2C_RMI_BufferWrite(I2C_Address,Page_Select_register,0);
      read_all_reg();

      printf("\r\n");
//page 1
      printf("\r\nRegister Data of Page 1.\r\n");
      I2C_RMI_BufferWrite(I2C_Address,Page_Select_register,1);
      read_all_reg();

      printf("\r\n");
//page 2
      printf("\r\nRegister Data of Page 2.\r\n");
      I2C_RMI_BufferWrite(I2C_Address,Page_Select_register,2);
      read_all_reg();

      printf("\r\n");

  SynaInitialize();
  SynaReadConfigInfo();
  SynaReadFirmwareInfo();
  SynaEnableFlashing();
	  SynaBootloaderLock();
	    SynaFinalizeReflash();
    }

    else if(Key==RIGHT)
    {
      printf("Key_RIGHT is pressed!!!\r\n");

      LCD_FillRectangle(3,63,187,307,BLACK);
      RMI_DispClorebar();


//Set fast relax rate to 0
//Page 1
      I2C_RMI_BufferWrite(I2C_Address,Page_Select_register,1);
      I2C_RMI_BufferWrite(I2C_Address,F54_ANALOG_CTRL12,1);
      I2C_RMI_BufferWrite(I2C_Address,F54_ANALOG_CTRL13,1);
      Set_ForceUpdate();
      printf("Fast relax rate:%d\r\n",I2C_RMI_BufferRead(I2C_Address,F54_ANALOG_CTRL13));
//Set rezero
//Back to default page
      I2C_RMI_BufferWrite(I2C_Address,Page_Select_register,0);
      Set_F11_Rezero();


    }

  }
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: stringcopy
** 功能描述: 複製功能
** 參數描述：將buff_from複製到 buff_to
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
uint8_t Stringcopy(BYTE *buff_to,BYTE *buff_from)
{
  u8 i=0;
  for(i=0; i<13; i++)
    buff_to[i] = buff_from[i];
  return 1;
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: LED_Init
** 功能描述: LED IO引腳配置
** 參數描述：無
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Init_LED(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;											//定義一個GPIO結構體變量

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD |RCC_APB2Periph_AFIO,ENABLE);	//使能各個端口時鐘，重要！！！

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_12 | GPIO_Pin_13; 		//配置LED端口掛接到6、12、13端口
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	   	//通用輸出開漏
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   	//配置端口速度為50M
  GPIO_Init(GPIOD, &GPIO_InitStructure);				   	//將端口GPIOD進行初始化配置
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: Init_DMA
** 功能描述: MDA寄存器配置
				配置為DMA通道1
** 參數描述：無
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Init_DMA(void)
{
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	 				//使能DMA1時鐘

  DMA_DeInit(DMA1_Channel4);											//復位DMA1 6通道
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;	//DMA外設地址為串口數據寄存器
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SendBuff;			//存儲器地址
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;			 		//存儲器為傳輸源地址  從存儲器讀
  DMA_InitStructure.DMA_BufferSize = sizeof(SendBuff);				//緩存大小
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	//外設地址不變
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;				//存儲器地址遞增
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  //數據寬度為8位
  DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;	//存儲器數據寬度為8位
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;						//工作在正常緩存模式
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;					//中斷優先級高
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;						//DMA通道x沒有設置為內存到內存傳輸
  DMA_Init(DMA1_Channel4, &DMA_InitStructure);						//根據參數初始化DMA寄存器
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: Init_ATTN
** 功能描述: I2C 中斷配置
** 參數描述：無
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Init_ATTN(void)
{
  EXTI_InitTypeDef  EXTI_InitStructure;					//定義一個EXTI結構體變量

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO,ENABLE);		//使能IO復用功能，使用中斷功能重要！！！

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource0);
  //配置端口E的0引腳為中斷源	  重要！！
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;//中斷線源
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//中斷模式為中斷模式
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	//下降沿出發
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//使能中斷線
  EXTI_Init(&EXTI_InitStructure);							//根據參數初始化中斷寄存器


  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);		//使能IO復用功能，使用中斷功能重要！！！

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);	 //配置端口PB5引腳為中斷源	  重要！！

  EXTI_InitStructure.EXTI_Line = EXTI_Line5;				//中斷線源為5
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//中斷模式為中斷模式
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	//下降沿出發
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//使能中斷線
  EXTI_Init(&EXTI_InitStructure);							//根據參數初始化中斷寄存器

}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: TIMER_Init
** 功能描述: 定時器2初始化配置
** 參數描述：無
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Init_TIMER(void)
{
  TIM_TimeBaseInitTypeDef	 TIM_BaseInitStructure;			//定義一個定時器結構體變量

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);   	//使能定時器2，重要！！

  TIM_DeInit( TIM2);                              		//將IM2定時器初始化位復位值

  TIM_InternalClockConfig(TIM2); 							//配置 TIM2 內部時鐘

  TIM_BaseInitStructure.TIM_Period = 1000; 				//設置自動重載寄存器值為最大值	0~65535之間  1000000/1000=1000us=1ms
  //TIM_Period（TIM1_ARR）=1000，計數器向上計數到1000後產生更新事件，
  //計數值歸零 也就是 1MS產生更新事件一次
  TIM_BaseInitStructure.TIM_Prescaler = 71;  				//自定義預分頻係數，提供給定時器的時鐘	0~65535之間
  //設置預分頻器分頻係數71，即APB2=72M, TIM1_CLK=72/72=1MHz
  TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //時鐘分割為0
  TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  //TIM向上計數模式 從0開始向上計數，計數到1000後產生更新事件
//	TIM_BaseInitStructure.TIM_RepetitionCounter = 0; 		//此參數只適合於TIM1和TIM8
  TIM_TimeBaseInit(TIM2, &TIM_BaseInitStructure); 		//根據指定參數初始化TIM時間基數寄存器

  TIM_ClearFlag(TIM2, TIM_FLAG_Update); 					//清中斷，以免一啟用中斷後立即產生中斷

  TIM_ARRPreloadConfig(TIM2, DISABLE);					//禁止ARR 預裝載緩衝器

  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); 				//使能TIM2中斷源
  TIM_Cmd(TIM2, ENABLE); 									//TIM2總開關：開啟

}
/*****************************************************************************
** 函數名稱: TIM2_IRQHandler
** 功能描述: 定時器2中斷處理函數
				1ms的中斷更新
** 參數描述：無
** 作  　者: Dream
** 日　  期: 2011年6月20日
*****************************************************************************/
void TIM2_IRQHandler(void)
{
  static uint16_t count=0;
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 		//判斷中斷標誌位是否為1；為1則中斷響應啦，0則沒有
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);       	//清楚中斷掛起位
    count++;
    TIM_Count--;										//定時延時變量減1
    if(count==500)										//計數到500MS，1MS*500
    {
      LED2 =~LED2;									//以0.5秒得週期閃爍
      count=0;	    								//計數清零
    }
  }
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: TIM_Delay
** 功能描述: 利用定時器延時
** 參數描述： 		延時時間T = time*1(MS)
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void TIM_Delay(uint16_t time)  //延時函數
{
  TIM_Count = time;
  while(TIM_Count);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: KEY_Init
** 功能描述: 按鍵 IO引腳配置
** 參數描述：無
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Init_KEY()
{
  GPIO_InitTypeDef GPIO_InitStructure;					//定義一個GPIO結構體變量
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOE,ENABLE);	//使能各個端口時鐘，重要！！！

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				//配置PB5
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //GPIO_Mode_IN_FLOATING; //GPIO_Mode_Out_OD //GPIO_Mode_IPU;//上拉輸入 //GPIO_Mode_IPD;//下拉輸入
  GPIO_Init(GPIOB	,&GPIO_InitStructure);				   	//將端口GPIOB進行初始化配置

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				//配置按鍵USER掛接到13端口
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	   		//配置成上拉輸入
  GPIO_Init(GPIOC	,&GPIO_InitStructure);				   	//將端口GPIOC進行初始化配置

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2
                                | GPIO_Pin_3 | GPIO_Pin_4;								//配置五項搖桿按鍵掛接到0、1、2、3、4端口
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	   		//配置成上拉輸入
  GPIO_Init(GPIOE,&GPIO_InitStructure);				   	//將端口GPIOE進行初始化配置

}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: KEY_Scan
** 功能描述: 按鍵掃瞄程序
** 參數描述：KEY_Status標誌位
				返回的值分別對應按鍵值
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
uint8_t KEY_Scan(void)
{
  static uint8_t KEY_Status =1; //定義一個按鍵標誌位
  if(KEY_Status&&(KEY_USER==0||KEY_S==0||KEY_D==0||KEY_L==0||KEY_R==0||KEY_U==0))//判斷是否有按鍵按下
  {
    Delay_Ms(10);//去抖動
    KEY_Status =0;
    if(KEY_USER==0) return 1;	  //按鍵USER按下返回1
    else if(KEY_S==0) return 2;	  //按鍵JOY-SEN按下返回1
    else if(KEY_D==0) return 3;	  //按鍵JOY-DOWN按下返回1
    else if(KEY_L==0) return 4;	  //按鍵JOY-LEFT按下返回1
    else if(KEY_R==0) return 5;	  //按鍵JOY-RIGHT按下返回1
    else if(KEY_U==0) return 6;	  //按鍵JOY-DOWN按下返回1
  }
  else if(KEY_USER==1&&KEY_S==1&&KEY_D==1&&KEY_L==1&&KEY_R==1&&KEY_U==1)KEY_Status=1;
  return 0;						  //無按鍵按下返回0
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: NVIC_Configuration
** 功能描述: 系統中斷配置
** 參數描述：無
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Init_NVIC(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

#ifdef  VECT_TAB_RAM  									//向量表基地址選擇

  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);  			//將0x20000000地址作為向量表基地址(RAM)
#else

  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0); 		//將0x08000000地址作為向量表基地址(FLASH)
#endif

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//先佔優先級1位,從優先級3位

  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;		//設定中斷源為PB5
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//中斷佔優先級為2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//副優先級為0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//使能中斷
  NVIC_Init(&NVIC_InitStructure);							   	//根據參數初始化中斷寄存器

  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//設定中斷源為PC13
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//中斷佔優先級為1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//副優先級為0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//使能中斷
  NVIC_Init(&NVIC_InitStructure);							   	//根據參數初始化中斷寄存器

  NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 			//中斷事件為TIM2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	//搶佔優先級0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;      	//響應優先級1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         	//允許中斷
  NVIC_Init(&NVIC_InitStructure);                         	//根據指定參數初始化中斷寄存器

  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;				//RTC全局中斷
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//先佔優先級1位,從優先級3位
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//先佔優先級0位,從優先級4位
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//使能該通道中斷
  NVIC_Init(&NVIC_InitStructure);								//根據NVIC_InitStruct中指定的參數初始化外設NVIC寄存器


}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: EXTI0_IRQHandler
** 功能描述: 中斷0入口函數
** 參數描述：無
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void EXTI0_IRQHandler(void)
{
  extern bool b_infinite;

  if(EXTI_GetITStatus(EXTI_Line0)!= RESET)	 //判斷是否發生中斷，發生則中斷標誌置1
  {
//		Delay_Ms(10);							 //用延時來消除抖動
    EXTI_ClearITPendingBit(EXTI_Line0);		//清楚中斷掛起位，重要！！
    printf("EXTI0_IRQHandler assert!!\r\n");
    b_infinite = FALSE;
    RMI_Reset();
    Clean_RMI_Reset();

  }
//	EXTI_ClearITPendingBit(EXTI_Line0);		//清楚中斷掛起位，重要！！
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: EXTI5_IRQHandler
** 功能描述: 中斷0入口函數
** 參數描述：無
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void EXTI9_5_IRQHandler(void)
{
  u8 int_status;
  extern u8 F54_Command_Base;
  extern bool b_infinite;

//extern u8 totalInts;
//DS4 V3
  u8 Flash_mask 		= 0x01;
  u8 Status_mask 	= 0x02;
  u8 Abs0_mask 		= 0x04;
  u8 Analog_mask 	= 0x08;
  u8 Led_mask 		= 0x10;
  u8 Button_mask 	= 0x20;

  LED3 = 0;
  if(EXTI_GetITStatus(EXTI_Line5)!= RESET)	 //判斷是否發生中斷，發生則中斷標誌置1
  {
    EXTI_ClearITPendingBit(EXTI_Line5);		//清楚中斷掛起位，重要！！

    LED3 =1;

    printf("EXTI9_5_IRQHandler_ATTN assert!! %d\r\n",counter++);

//Back to default page always
    I2C_RMI_BufferWrite(I2C_Address,Page_Select_register,0);

    StatusCode = CP_RMI_Read(F01_RMI_Data0) & 0x0F;
    if(StatusCode != 0) printf("F01_RMI_Data0:0x%x, Status Code:0x%x.\r\n",F01_RMI_Data0,StatusCode);
//   printf("F01_RMI_Ctrl1: 0x%x = 0x%x.",F01_RMI_Ctrl1,I2C_RMI_BufferRead(I2C_Address,F01_RMI_Ctrl1));

//	read_attn_reg();
    int_status = CP_RMI_Read(F01_RMI_Data1) & 0x3F;

    printf("F01_RMI_Data1:0x%x, int_status:0x%x.\r\n",F01_RMI_Data1,int_status);

    if(int_status & Flash_mask)
    {
      printf("Int source: Flash.\r\n");
    }
    if(int_status & Status_mask)
    {
      printf("Int source: Status.\r\n");
    }
    if(int_status & Abs0_mask)
    {
      printf("Int source: Abs0.   ");
      read_func11();
    }
    if(int_status & Analog_mask)
    {

//Change to Page 1
      I2C_RMI_BufferWrite(I2C_Address,Page_Select_register,1);

      printf("Int source: Analog.\r\n");

//      f54_CheckImageReportData();
      f54_CheckPhyImgData();
    }

    if(int_status & Led_mask)
    {
      printf("Int source: Led.\r\n");
    }
    if(int_status & Button_mask)
    {
//Change to Page 2
      I2C_RMI_BufferWrite(I2C_Address,Page_Select_register,2);

      printf("Int source: Button.\r\n");
      read_func1A();
    }

    check_IMBM();
    LED3=0;

//totalInts = 6 for DS4 v3
//	CheckIntSource(int_status);
//    LED3 = ~LED3;
  }
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: Delay_Ms_Ms
** 功能描述: 延時1MS (可通過仿真來判斷他的準確度)
** 參數描述：time (ms) 注意time<65535
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Delay_Ms(uint16_t time)  //延時函數
{
  uint16_t i,j;
  for(i=0; i<time; i++)
    for(j=0; j<10260; j++);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: Delay_Ms_Us
** 功能描述: 延時1us (可通過仿真來判斷他的準確度)
** 參數描述：time (us) 注意time<65535
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Delay_Us(uint16_t time)  //延時函數
{
  uint16_t i,j;
  for(i=0; i<time; i++)
    for(j=0; j<9; j++);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** Function: CheckIntSource
** Input: Int values
** Output:
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void CheckIntSource(u8 intval)
{




}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
End:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
