/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
**  啟航號開發板
**	LCD底層驅動程序
**  版本：Rev1.0
**  日期：2011-6-20
**	論壇：www.openmcu.com
**	淘寶：http://shop36995246.taobao.com/
**  技術支持群：153631682 	 技術QQ：77642732
**  Copyright(c)@旺寶電子	Dream_etd@163.com
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
//頭文件調用
#include "usually.h"
#include "usart.h"
#include "LCD_Drive.h"
#include "hz16.h"
#include "font.h"

static uint16_t DeviceID;			//定義LCD設備ID

uint16_t TextColor = BLUE , BlackColor = BLACK;

#define LCD_RAM    *(__IO uint16_t *) ((uint32_t)0x60020000)    	//地址寄存器
#define LCD_REG    *(__IO uint16_t *) ((uint32_t)0x60000000)	 	//指令寄存器

uint16_t Read_LCDReg(uint16_t LCD_Reg)
{
  uint16_t temp;

  LCD_REG= LCD_Reg;

  temp= LCD_RAM;

  return temp;
}
void Write_LCDReg(uint16_t LCD_Reg,uint16_t LCD_Dat)
{
  LCD_REG= LCD_Reg;	 		//往指令寄存器寫指令

  LCD_RAM= LCD_Dat; 			//往數據寄存器寫數據
}

void FSMC_LCDInit()
{
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;	   	//定義一個NOR初始化結構體
  FSMC_NORSRAMTimingInitTypeDef  p;						//定義一個NOR時序初始化結構體

  p.FSMC_AddressSetupTime = 0x02;							//地址建立時間：0x1
  p.FSMC_AddressHoldTime = 0x00;							//地址保持時間：0x00
  p.FSMC_DataSetupTime = 0x05;							//數據建立時間：0x2
  p.FSMC_BusTurnAroundDuration = 0x00;
  p.FSMC_CLKDivision = 0x00;
  p.FSMC_DataLatency = 0x00;
  p.FSMC_AccessMode = FSMC_AccessMode_B;

  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;	   	//擴展NOR BANK 的第1個子BANK
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  //不使用總線復用
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;//擴展類型為NOR FLASH
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  //擴展總線寬度為16位
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  //
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  //
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;//
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 							//根據指定參數初始化結構體

  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE); 							//使能FSMC_Bank1_NORSRAM1 內存

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);						//使能FSMC總線時鐘
}
void GPIO_LCDInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO
                         ,ENABLE);										//使能各個端口時鐘

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
                                GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                                GPIO_Pin_11 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;						//最大輸出50Mhz
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;						   	//復用功能輸出推挽
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                                GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |
                                GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;					   //最大輸出50Mhz
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;						   //復用功能輸出推挽
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void Init_LCD(void)
{
  FSMC_LCDInit();									//LCD對應的FSMC接口初始化
  GPIO_LCDInit();								    //LCD對應的IO接口初始化
  DeviceID = Read_LCDReg(0x0000);					//讀取LCD的ID：對應我們1289的屏的ID是0x8999
  printf("DeviceID=0x%x\r\n",DeviceID);			//以十六進制方式輸出LCD讀取的ID
  if(DeviceID == 0x8999)
  {
    //************* Start Initial Sequence **********//
    Write_LCDReg(0x00, 0x0001); // 開啟內部時鐘
#if	 	LCD_ID_AM == 110
    Write_LCDReg(0x01, 0x3B3F); //輸出驅動控制: RL=0;REV=1;GD=1;BGR=0;SM=0;TB=1
#elif  	LCD_ID_AM == 001
    Write_LCDReg(0x01, 0x7B3F); //輸出驅動控制:RL=1;REV=1;GD=1;BGR=0;SM=0;TB=1
#endif
    Write_LCDReg(0x02, 0x0600); //set 1 line inversion
    //************* Power control setup ************/
    Write_LCDReg(0x0C, 0x0007); // Adjust VCIX2 output voltage
    Write_LCDReg(0x0D, 0x0006); // Set amplitude magnification of VLCD63
    Write_LCDReg(0x0E, 0x3200); // Set alternating amplitude of VCOM
    Write_LCDReg(0x1E, 0x00BB); // Set VcomH voltage
    Write_LCDReg(0x03, 0x6A64); // Step-up factor/cycle setting
    //************ RAM position control **********/
    Write_LCDReg(0x0F, 0x0000); // Gate scan position start at G0.
    Write_LCDReg(0x44, 0xEF00); // Horizontal RAM address position
    Write_LCDReg(0x45, 0x0000); // Vertical RAM address start position
    Write_LCDReg(0x46, 0x013F); // Vertical RAM address end position
    // ----------- Adjust the Gamma Curve ----------//
    Write_LCDReg(0x30, 0x0000);
    Write_LCDReg(0x31, 0x0706);
    Write_LCDReg(0x32, 0x0206);
    Write_LCDReg(0x33, 0x0300);
    Write_LCDReg(0x34, 0x0002);
    Write_LCDReg(0x35, 0x0000);
    Write_LCDReg(0x36, 0x0707);
    Write_LCDReg(0x37, 0x0200);
    Write_LCDReg(0x3A, 0x0908);
    Write_LCDReg(0x3B, 0x0F0D);
    //************* Special command **************/
    Write_LCDReg(0x28, 0x0006); // Enable test command
    Write_LCDReg(0x2F, 0x12EB); // RAM speed tuning
    Write_LCDReg(0x26, 0x7000); // Internal Bandgap strength
    Write_LCDReg(0x20, 0xB0E3); // Internal Vcom strength
    Write_LCDReg(0x27, 0x0044); // Internal Vcomh/VcomL timing
    Write_LCDReg(0x2E, 0x7E45); // VCOM charge sharing time
    //************* Turn On display ******************/
    Write_LCDReg(0x10, 0x0000); // Sleep mode off.
    Delay_Ms(3); // Wait 30mS
#if  	LCD_ID_AM == 000
    Write_LCDReg(0x11, 0x6840); //262K色彩  水平方向送數據,水平和垂直方向地址遞減

#elif	LCD_ID_AM == 010
    Write_LCDReg(0x11, 0x6850); //262K色彩  Entry mode setup. 262K type B, take care on the data bus with 16it only

#elif	LCD_ID_AM == 100
    Write_LCDReg(0x11, 0x6860); //262K色彩  Entry mode setup. 262K type B, take care on the data bus with 16it only

#elif	LCD_ID_AM == 110
    Write_LCDReg(0x11, 0x6870); //262K色彩  Entry mode setup. 262K type B, take care on the data bus with 16it only

#elif	LCD_ID_AM == 001
    Write_LCDReg(0x11, 0x6848); //262K色彩  Entry mode setup. 262K type B, take care on the data bus with 16it only

#elif	LCD_ID_AM == 011
    Write_LCDReg(0x11, 0x6858); //262K色彩  Entry mode setup. 262K type B, take care on the data bus with 16it only

#elif	LCD_ID_AM == 101
    Write_LCDReg(0x11, 0x6868); //262K色彩  Entry mode setup. 262K type B, take care on the data bus with 16it only

#elif	LCD_ID_AM == 111
    Write_LCDReg(0x11, 0x6878); //262K色彩  Entry mode setup. 262K type B, take care on the data bus with 16it only
#endif
    Write_LCDReg(0x07, 0x0033); // Display ON	*/
  }
  Clear_LCD(BLACK);
}
void Clear_LCD(uint16_t Color)
{
  uint32_t i;
  Set_LCDCorsor(0,0);								//設置坐標起始地址
  LCD_REG = 0x22;									//準備寫RAM
  for(i=0; i<LCD_H_MAX*LCD_V_MAX; i++)				//240*320=76800像素
  {
    LCD_RAM = Color;							//向數據寄存器寫數據
  }
}


//在指定區域內填充指定顏色
//區域大小:
//  (xend-xsta)*(yend-ysta)
void LCD_FulfillArea(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t Color)
{
  uint16_t i;
  uint16_t j;

  //設置圖片顯示窗口大小
  Write_LCDReg(0x44,xsta|(xsta+xend-1)<<8); //設置水平方向GRAM起始地址(低字節為起始地址，高字節為結束地址)
  Write_LCDReg(0x45,ysta);				  	//設置窗口的Y方向的開始位置
  Write_LCDReg(0x46,ysta+yend-1);			//設置窗口的Y方向的結束位置

  for(i=xsta; i<xend; i++)
    for(j=ysta; j<yend; j++)
    {
      Write_LCDReg(0x4E, i);							//定義x的起始坐標
      Write_LCDReg(0x4F, j);							//定義y的起始坐標
      LCD_REG = 0x22;    									//準備寫RAM
      LCD_RAM= Color; 			//往數據寄存器寫數據
    }

  //回復窗口
  Write_LCDReg(0x44,0|239<<8); 			//設置窗口的X方向開始位置和結束位置
  Write_LCDReg(0x45,0);				  		//設置窗口的Y方向的開始位置
  Write_LCDReg(0x46,319);			  	//設置窗口的Y方向的結束位置

}

void LCD_FillRectangle(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t Color)
{
  uint16_t i;
  uint16_t j;

  //設置圖片顯示窗口大小
  Write_LCDReg(0x44,xsta|(xsta+xend-1)<<8); //設置水平方向GRAM起始地址(低字節為起始地址，高字節為結束地址)
  Write_LCDReg(0x45,ysta);				  	//設置窗口的Y方向的開始位置
  Write_LCDReg(0x46,ysta+yend-1);			//設置窗口的Y方向的結束位置

  for(j=0; j<yend-ysta; j++)				//240*320=76800像素
  {
    Set_LCDCorsor(xsta,ysta+j);			//設置坐標起始地址
    LCD_REG = 0x22;						//準備寫RAM
    for(i=0; i<yend-ysta; i++)				//240*320=76800像素
    {
      LCD_RAM = Color;						//向數據寄存器寫數據
    }
  }

  //回復窗口
  Write_LCDReg(0x44,0|239<<8); 			//設置窗口的X方向開始位置和結束位置
  Write_LCDReg(0x45,0);				  		//設置窗口的Y方向的開始位置
  Write_LCDReg(0x46,319);			  	//設置窗口的Y方向的結束位置

  /*
  for(i=xsta; i<xend; i++)
    for(j=ysta; j<yend; j++)
    {
      Write_LCDReg(0x4E, i);							//定義x的起始坐標
      Write_LCDReg(0x4F, j);							//定義y的起始坐標
      LCD_REG = 0x22;    									//準備寫RAM
      LCD_RAM= Color; 			//往數據寄存器寫數據
    }
  */
  //				RMI_LCDDispPoint(i,j,Color);

}

void Set_LCDCorsor(uint16_t x,uint16_t y)
{
#if	 	LCD_ID_AM == DsipV_ENABLE
  Write_LCDReg(0x4E, x);							//定義x的起始坐標
  Write_LCDReg(0x4F, y);							//定義y的起始坐標

#elif  	LCD_ID_AM == DsipH_ENABLE
  Write_LCDReg(0x4E, 239-y);						//定義x的起始坐標
  Write_LCDReg(0x4F, 319-x);						//定義y的起始坐標
#endif
}

uint8_t Disp_LCDChar(uint16_t x,uint16_t y,uint8_t star)
{
  uint8_t temp;
  uint16_t i,j;
  uint16_t y0;

  y0 = y;
  for(i=0; i<16; i++)								//循環16次 字符為8*16 高16
  {
    Set_LCDCorsor(x,y0);						//設置坐標起始位置
    LCD_REG = 0x22;								//準備寫RAM
    temp = ASCII_1608[star-0x20][i];			//調用1608字符庫
    for(j=0; j<8; j++)							//循環8次 字符為8*16  寬8
    {
      if((temp<<j)&0x80)						//先傳高位
      {
        LCD_RAM = TextColor;				//為1則點亮
      }
      else
      {
        LCD_RAM = BlackColor;				//為0則沒背景顏色
      }
    }
    y0++;										//Y方向地址加1
  }
  return (8);								  		//返回字符之間的間距
}
/*****************************************************************************
** 函數名稱: DisplayOneHzChar
** 功能描述: 顯示一個指定大小的漢字
** 作  　者: Dream
** 日　  期: 2010年12月06日
*****************************************************************************/
uint16_t Disp_LCDHz(uint16_t x,uint16_t y,uint8_t *pucMsk)
{
  uint16_t i,j;
  uint16_t mod[16];                                      /* 當前字模 */
  uint16_t *pusMsk;                                      /* 當前字庫地址 */
  uint16_t y0;

  pusMsk = (uint16_t *)pucMsk;
  for(i=0; i<16; i++)                                    /* 保存當前漢字點陣式字模 */
  {
    mod[i] = *pusMsk++;                                /* 取得當前字模，半字對齊訪問*/
    mod[i] = ((mod[i] & 0xff00) >> 8) | ((mod[i] & 0x00ff) << 8);/* 字模交換高低字節（為了顯示 */
    /* 需要） */
  }
  y0 = y;
  for(i=0; i<16; i++)                                    /* 16行 */
  {
    /* 直接顯示 */

    Set_LCDCorsor(x,y0);								//設置坐標起始位置
    LCD_REG = 0x22;										//準備寫GRAM
    for(j=0; j<16; j++)                                /* 16列       */
    {
      if((mod[i] << j)& 0x8000)                     /* 顯示字模  */
      {
        LCD_RAM= TextColor;
      }
      else
      {
        LCD_RAM= BlackColor;                     /* 用讀方式跳過寫空白點的像素*/
      }
    }
    y0++;
  }
  return (16);                                          /* 返回16位列寬 */
}
void Disp_LCDString(uint16_t x,uint16_t y,uint8_t* p)
{
  uint16_t HzIndex;
  uint8_t Width=0;
  FNT_GB16 *ptGb16 = 0;

  ptGb16 = (FNT_GB16 *)GBHZ_16;

  while(1)
  {
    x=x+Width;								  	//X方向加字符的寬度
    if(*p=='\0') break;							//判斷字符串是不是結束
    if(*p > 0x80)								//判斷為漢字
    {
      if((x+16)>LCD_H_MAX)
      {
        x=0;
        y=y+16;
        if(y>LCD_V_MAX)
        {
          y=x=0;
          Clear_LCD(WHITE);
        }
      }
      HzIndex = findHzIndex(p);				//搜索漢字
      Width = Disp_LCDHz(x,y,(uint8_t *)&(ptGb16[HzIndex].Msk[0]));
      //顯示漢字
      p += 2;									//漢字地址加2
    }											//判斷為非漢字
    else
    {
      if (*p == '\r')                         //換行
      {
        y = y + 16;                         //改變顯示坐標
        if(y > LCD_H_MAX)                   //縱坐標超出
        {
          y = 0;
        }
        p++;
        Width = 0;
        continue;
      }
      else if (*p == '\n')                    //對齊到起點
      {
        x = 0;
        p++;
        Width = 0;
        continue;
      }
      if(x>LCD_H_MAX-8)						//判斷水平方向是否超出範圍
      {
        x=0;
        y=y+16;
        if(y>LCD_V_MAX-16)
        {
          y=x=0;
          Clear_LCD(WHITE);
        }
        //判斷垂直方向是否超出範圍
      }
      Width = Disp_LCDChar(x,y,*p);			//顯示單個字符
      p++;									//字符地址加1
    }
  }
}

//顯示字符串
//x,y:起點坐標
//*p:字符串起始地址
//用16字體
void LCD_ShowString(uint16_t x,uint16_t y,uint8_t* p,u16 color)
{
  uint16_t HzIndex;
  uint8_t Width=0;
  FNT_GB16 *ptGb16 = 0;

  ptGb16 = (FNT_GB16 *)GBHZ_16;

  while(1)
  {
    x=x+Width;								  	//X方向加字符的寬度
    if(*p=='\0') break;							//判斷字符串是不是結束
    if(*p > 0x80)								//判斷為漢字
    {
      if((x+16)>LCD_H_MAX)
      {
        x=0;
        y=y+16;
        if(y>LCD_V_MAX)
        {
          y=x=0;
          Clear_LCD(WHITE);
        }
      }
      HzIndex = findHzIndex(p);				//搜索漢字
      Width = Disp_LCDHz(x,y,(uint8_t *)&(ptGb16[HzIndex].Msk[0]));
      //顯示漢字
      p += 2;									//漢字地址加2
    }											//判斷為非漢字
    else
    {
      if (*p == '\r')                         //換行
      {
        y = y + 16;                         //改變顯示坐標
        if(y > LCD_H_MAX)                   //縱坐標超出
        {
          y = 0;
        }
        p++;
        Width = 0;
        continue;
      }
      else if (*p == '\n')                    //對齊到起點
      {
        x = 0;
        p++;
        Width = 0;
        continue;
      }
      if(x>LCD_H_MAX-8)						//判斷水平方向是否超出範圍
      {
        x=0;
        y=y+16;
        if(y>LCD_V_MAX-16)
        {
          y=x=0;
          Clear_LCD(WHITE);
        }
        //判斷垂直方向是否超出範圍
      }
      TextColor = color;

      Width = Disp_LCDChar(x,y,*p);			//顯示單個字符
      p++;									//字符地址加1
    }
  }


}

void Disp_LCDBmp(uint16_t Xstar,uint16_t Ystar,uint16_t Xend,uint16_t Yend,uint8_t* bmp)
{
  static	uint16_t i=0,j=0;
  uint16_t *bitbmp = (uint16_t *)bmp;

#if	 	LCD_ID_AM == DsipH_ENABLE	 //將X方向和Y方向互換
  uint16_t XY_Switch;
  XY_Switch = Xend;
  Xend = Yend;
  Yend = XY_Switch;
#endif

  //設置圖片顯示窗口大小
  Write_LCDReg(0x44,Xstar|(Xstar+Xend-1)<<8); //設置水平方向GRAM起始地址(低字節為起始地址，高字節為結束地址)
  Write_LCDReg(0x45,Ystar);				  	//設置窗口的Y方向的開始位置
  Write_LCDReg(0x46,Ystar+Yend-1);			//設置窗口的Y方向的結束位置

#if	 	LCD_ID_AM == DsipV_ENABLE
  Write_LCDReg(0x4E, Xstar);							//定義x的起始坐標
  Write_LCDReg(0x4F, Ystar);							//定義y的起始坐標
#elif  	LCD_ID_AM == DsipH_ENABLE
  Write_LCDReg(0x4E, Xstar);						//定義x的起始坐標
  Write_LCDReg(0x4F, Ystar);						//定義y的起始坐標
#endif

  LCD_REG = 0x22;							  	//準備寫數據到GRAM
  for(i=0; i<Yend; i++)
  {
    for(j=0; j<Xend; j++)LCD_RAM = *bitbmp++; //Delay_Ms(10);}
  }
  //回復窗口
  Write_LCDReg(0x44,0|239<<8); 			//設置窗口的X方向開始位置和結束位置
  Write_LCDReg(0x45,0);				  		//設置窗口的Y方向的開始位置
  Write_LCDReg(0x46,319);			  	//設置窗口的Y方向的結束位置
}
/*****************************************************************************
** 函數名稱: Num_power
** 功能描述: M的N次方
** 作  　者: Dream
** 日　  期: 2010年12月06日
*****************************************************************************/
uint32_t Num_power(uint8_t m,uint8_t n)
{
  u32 result=1;
  while(n--)result*=m;
  return result;
}
/*****************************************************************************
** 函數名稱: LCD_ShowNum
** 功能描述: 在指定位置顯示一串數字
				num:數值(0~4294967295);
** 作  　者: Dream
** 日　  期: 2010年12月06日
*****************************************************************************/
void LCD_ShowNum(uint8_t x,uint16_t y,u32 num,uint8_t len)
{
  uint8_t t,temp;
  uint8_t enshow=0;
  for(t=0; t<len; t++)
  {
    temp=(num/Num_power(10,len-t-1))%10;
    if(enshow==0&&t<(len-1))
    {
      if(temp==0)
      {
        Disp_LCDChar(x+8*t,y,' ');
        continue;
      }
      else enshow=1;

    }
    Disp_LCDChar(x+8*t,y,temp+0x30);
  }
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: Write_LCDRAM_Prepare
** 功能描述: LCD窗口設置
** 參數描述：x、y為顯示的坐標
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Write_LCDRAM_Prepare(void)
{
  LCD_REG = 0x22;									//準備寫RAM
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: Read_LCDReg
** 功能描述: 讀寄存器
** 參數描述：無
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Write_LCDRam(uint16_t LCD_Dat)
{
  LCD_RAM= LCD_Dat; 			//往數據寄存器寫數據
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: Disp_LCDPoint
** 功能描述: 顯示一個點
** 參數描述：x、y為字符顯示的位置
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Disp_LCDPoint(uint16_t x,uint16_t y)
{
  Set_LCDCorsor(x,y);
  Write_LCDRAM_Prepare();
  Write_LCDRam(TextColor);
}
void RMI_LCDDispPoint(uint16_t x,uint16_t y,uint16_t color)
{
  Set_LCDCorsor(x,y);
  Write_LCDRAM_Prepare();
  Write_LCDRam(color);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: Disp_LCDLine
** 功能描述: 畫線
** 參數描述: 在指定的兩側位置畫一條線
**				x1,y1:起點坐標度  x2,y2:終點坐標
** 作  　者: Dream
** 日　  期: 2010年12月06日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Disp_LCDLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
  uint16_t t;
  int xerr=0,yerr=0,delta_x,delta_y,distance;
  int incx,incy,uRow,uCol;

  delta_x=x2-x1; 				//計算坐標增量
  delta_y=y2-y1;
  uRow=x1;
  uCol=y1;
  if(delta_x>0)incx=1; 		//設置單步方向
  else if(delta_x==0)incx=0;	//垂直線
  else
  {
    incx=-1;
    delta_x=-delta_x;
  }
  if(delta_y>0)incy=1;
  else if(delta_y==0)incy=0;	//水平線
  else
  {
    incy=-1;
    delta_y=-delta_y;
  }
  if( delta_x>delta_y)distance=delta_x; //選取基本增量坐標軸
  else distance=delta_y;
  for(t=0; t<=distance+1; t++ )	//畫線輸出
  {
    Disp_LCDPoint(uRow,uCol);//畫點
    xerr+=delta_x ;
    yerr+=delta_y ;
    if(xerr>distance)
    {
      xerr-=distance;
      uRow+=incx;
    }
    if(yerr>distance)
    {
      yerr-=distance;
      uCol+=incy;
    }
  }
}

void RMI_DispLCDLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color )
{
  uint16_t t;
  int xerr=0,yerr=0,delta_x,delta_y,distance;
  int incx,incy,uRow,uCol;

  delta_x=x2-x1; 				//計算坐標增量
  delta_y=y2-y1;
  uRow=x1;
  uCol=y1;
  if(delta_x>0)incx=1; 		//設置單步方向
  else if(delta_x==0)incx=0;	//垂直線
  else
  {
    incx=-1;
    delta_x=-delta_x;
  }
  if(delta_y>0)incy=1;
  else if(delta_y==0)incy=0;	//水平線
  else
  {
    incy=-1;
    delta_y=-delta_y;
  }
  if( delta_x>delta_y)distance=delta_x; //選取基本增量坐標軸
  else distance=delta_y;
  for(t=0; t<=distance+1; t++ )	//畫線輸出
  {
    RMI_LCDDispPoint(uRow,uCol,color);//畫點
    xerr+=delta_x ;
    yerr+=delta_y ;
    if(xerr>distance)
    {
      xerr-=distance;
      uRow+=incx;
    }
    if(yerr>distance)
    {
      yerr-=distance;
      uCol+=incy;
    }
  }
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: LCD_DrawLine
** 功能描述: 在指定位置畫一個指定大小的圓
				(x,y):中心點 	 r    :半徑
** 作  　者: Dream
** 日　  期: 2010年12月06日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Disp_LCDCircle(uint8_t x0,uint16_t y0,uint8_t r)
{
  int a,b;
  int di;
  a=0;
  b=r;
  di=3-(r<<1);             //判斷下個點位置的標誌
  while(a<=b)
  {
    Disp_LCDPoint(x0-b,y0-a);             //3
    Disp_LCDPoint(x0+b,y0-a);             //0
    Disp_LCDPoint(x0-a,y0+b);             //1
    Disp_LCDPoint(x0-b,y0-a);             //7
    Disp_LCDPoint(x0-a,y0-b);             //2
    Disp_LCDPoint(x0+b,y0+a);             //4
    Disp_LCDPoint(x0+a,y0-b);             //5
    Disp_LCDPoint(x0+a,y0+b);             //6
    Disp_LCDPoint(x0-b,y0+a);
    a++;
    //使用Bresenham算法畫圓
    if(di<0)di +=4*a+6;
    else
    {
      di+=10+4*(a-b);
      b--;
    }
    Disp_LCDPoint(x0+a,y0+b);
  }
}

void RMI_LCDDrawColorPoint(uint8_t x0,uint16_t y0,uint8_t r,uint16_t color)
{

  uint16_t xsta, ysta, xend, yend;

  xsta  = x0 -r;
  xend = x0 +r;
  ysta  = y0 - r;
  yend = y0 + r;

  LCD_FulfillArea(xsta,ysta,xend,yend,color);

}
void RMI_DispLCDCircle(uint8_t x0,uint16_t y0,uint8_t r,uint16_t color)
{
  int a,b;
  int di;
  a=0;
  b=r;
  di=3-(r<<1);             //判斷下個點位置的標誌
  while(a<=b)
  {
    RMI_LCDDispPoint(x0-b,y0-a,color);             //3
    RMI_LCDDispPoint(x0+b,y0-a,color);             //0
    RMI_LCDDispPoint(x0-a,y0+b,color);             //1
    RMI_LCDDispPoint(x0-b,y0-a,color);             //7
    RMI_LCDDispPoint(x0-a,y0-b,color);             //2
    RMI_LCDDispPoint(x0+b,y0+a,color);             //4
    RMI_LCDDispPoint(x0+a,y0-b,color);             //5
    RMI_LCDDispPoint(x0+a,y0+b,color);             //6
    RMI_LCDDispPoint(x0-b,y0+a,color);
    a++;
    //使用Bresenham算法畫圓
    if(di<0)di +=4*a+6;
    else
    {
      di+=10+4*(a-b);
      b--;
    }
    RMI_LCDDispPoint(x0+a,y0+b,color);
  }
}


//畫矩形
void LCD_DrawRectangle(u8 x1, u16 y1, u8 x2, u16 y2)
{
  Disp_LCDLine(x1,y1,x2,y1);
  Disp_LCDLine(x1,y1,x1,y2);
  Disp_LCDLine(x1,y2,x2,y2);
  Disp_LCDLine(x2,y1,x2,y2);
}

void RMI_LCDDrawRectangle(u8 x1, u16 y1, u8 x2, u16 y2,uint16_t color)
{
  RMI_DispLCDLine(x1,y1,x2,y1,color);
  RMI_DispLCDLine(x1,y1,x1,y2,color);
  RMI_DispLCDLine(x1,y2,x2,y2,color);
  RMI_DispLCDLine(x2,y1,x2,y2,color);
}

void RMI_DispClorebar(void)
{
  u8 i;
  extern u16 color_bar[11];

  for(i=0; i<10; i++)  LCD_FulfillArea(210,310-(i+1)*8,220,310-i*8,color_bar[i]);

  Disp_LCDString(202,288,"0");
  Disp_LCDString(222,298,"-");
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
End:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
