/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
**  啟航號開發板
**	24LC02底層驅動 這裡模擬I2C
**  版本：Rev1.0 
**  日期：2011-6-20
**	論壇：www.openmcu.com
**	淘寶：http://shop36995246.taobao.com/   
**  技術支持群：153631682 	 技術QQ：77642732 
**  Copyright(c)@旺寶電子	Dream_etd@163.com	
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

/* Includes ------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
#include "usually.h"
#include "24LC02.h" 

extern void Delay_Ms(uint16_t time);  //延時函數
extern void Delay_Us(uint16_t time);  //延時函數

//在AT24CXX指定地址讀出一個數據
//ReadAddr:開始讀數的地址  
//返回值  :讀到的數據
uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr)
{				  
	uint8_t temp=0;		  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	   //發送寫命令
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr>>8);//發送高地址
		IIC_Wait_Ack();		 
	}else IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   //發送器件地址0XA0,寫數據 	 

	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr%256);   //發送低地址
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);           //進入接收模式			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//產生一個停止條件	    
	return temp;
}
//在AT24CXX指定地址寫入一個數據
//WriteAddr  :寫入數據的目的地址    
//DataToWrite:要寫入的數據
void AT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite)
{				   	  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	    //發送寫命令
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr>>8);//發送高地址
		IIC_Wait_Ack();		 
	}else
	{
		IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   //發送器件地址0XA0,寫數據 
	}	 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr%256);   //發送低地址
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);     //發送字節							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//產生一個停止條件 
	Delay_Ms(10);	 
}
//在AT24CXX裡面的指定地址開始寫入長度為Len的數據
//該函數用於寫入16bit或者32bit的數據.
//WriteAddr  :開始寫入的地址  
//DataToWrite:數據數組首地址
//Len        :要寫入數據的長度2,4
void AT24CXX_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len)
{  	
	uint8_t t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

//在AT24CXX裡面的指定地址開始讀出長度為Len的數據
//該函數用於讀出16bit或者32bit的數據.
//ReadAddr   :開始讀出的地址 
//返回值     :數據
//Len        :要讀出數據的長度2,4
uint32_t AT24CXX_ReadLenByte(uint16_t ReadAddr,uint8_t Len)
{  	
	uint8_t t;
	uint32_t temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}
//檢查AT24CXX是否正常
//這裡用了24XX的最後一個地址(255)來存儲標誌字.
//如果用其他24C系列,這個地址要修改
//返回1:檢測失敗
//返回0:檢測成功
uint8_t AT24CXX_Check(void)
{
	uint8_t temp;
	temp=AT24CXX_ReadOneByte(255);//避免每次開機都寫AT24CXX			   
	if(temp==0X55)return 0;		   
	else//排除第一次初始化的情況
	{
		AT24CXX_WriteOneByte(255,0X55);
	    temp=AT24CXX_ReadOneByte(255);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

//在AT24CXX裡面的指定地址開始讀出指定個數的數據
//ReadAddr :開始讀出的地址 對24c02為0~255
//pBuffer  :數據數組首地址
//NumToRead:要讀出數據的個數
void AT24CXX_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  
//在AT24CXX裡面的指定地址開始寫入指定個數的數據
//WriteAddr :開始寫入的地址 對24c02為0~255
//pBuffer   :數據數組首地址
//NumToWrite:要寫入數據的個數
void AT24CXX_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}
void Init_IIC(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;					//定義一個GPIO結構體變量
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//使能各個端口時鐘，重要！！！

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;  //配置LED端口掛接到6、12、13端口
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	   	//通用輸出開漏
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   	//配置端口速度為50M
  	GPIO_Init(GPIOB, &GPIO_InitStructure);				   	//將端口GPIOD進行初始化配置
}
//產生IIC起始信號
void IIC_Start(void)
{
	SDA_OUT();     //sda線輸出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	Delay_Us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	Delay_Us(4);
	IIC_SCL=0;//鉗住I2C總線，準備發送或接收數據 
}	  
//產生IIC停止信號
void IIC_Stop(void)
{
	SDA_OUT();//sda線輸出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	Delay_Us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//發送I2C總線結束信號
	Delay_Us(4);							   	
}
//等待應答信號到來
//返回值：1，接收應答失敗
//        0，接收應答成功
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA_IN();      //SDA設置為輸入  
	IIC_SDA=1;Delay_Us(1);	   
	IIC_SCL=1;Delay_Us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//時鐘輸出0 	   
	return 0;  
} 
//產生ACK應答
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	Delay_Us(2);
	IIC_SCL=1;
	Delay_Us(2);
	IIC_SCL=0;
}
//不產生ACK應答		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	Delay_Us(2);
	IIC_SCL=1;
	Delay_Us(2);
	IIC_SCL=0;
}					 				     
//IIC發送一個字節
//返回從機有無應答
//1，有應答
//0，無應答			  
void IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//拉低時鐘開始數據傳輸
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		Delay_Us(2);   //對TEA5767這三個延時都是必須的
		IIC_SCL=1;
		Delay_Us(2); 
		IIC_SCL=0;	
		Delay_Us(2);
    }	 
} 	    
//讀1個字節，ack=1時，發送ACK，ack=0，發送nACK   
uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA設置為輸入
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        Delay_Us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		Delay_Us(1); 
    }					 
    if (!ack)
        IIC_NAck();//發送nACK
    else
        IIC_Ack(); //發送ACK   
    return receive;
} 
/*********************************************************************************************************
** End of File
*********************************************************************************************************/
