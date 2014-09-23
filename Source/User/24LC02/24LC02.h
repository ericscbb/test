#ifndef __I2C_H
#define __I2C_H

#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	    8191
#define AT24C128	16383
#define AT24C256	32767  
//啟航號開發板使用的是24c02，所以定義EE_TYPE為AT24C02
#define EE_TYPE AT24C02
					  
uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr);							//指定地址讀取一個字節
void AT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite);		//指定地址寫入一個字節
void AT24CXX_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len);//指定地址開始寫入指定長度的數據
uint32_t AT24CXX_ReadLenByte(uint16_t ReadAddr,uint8_t Len);					//指定地址開始讀取指定長度數據
void AT24CXX_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite);	//從指定地址開始寫入指定長度的數據
void AT24CXX_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead);   	//從指定地址開始讀出指定長度的數據

uint8_t AT24CXX_Check(void);  //檢查器件
void AT24CXX_Init(void); //初始化IIC


//IO方向設置
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=0x80000000;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=0x30000000;}		  //0x3000000:50MHz;0x1000000:10MHz;0x2000000:2MHz

//IO操作函數	 
#define IIC_SCL    PBout(6) //SCL
#define IIC_SDA    PBout(7) //SDA	 
#define READ_SDA   PBin(7)  //輸入SDA 

//IIC所有操作函數
void Init_IIC(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//發送IIC開始信號
void IIC_Stop(void);	  			//發送IIC停止信號
void IIC_Send_Byte(uint8_t txd);			//IIC發送一個字節
uint8_t IIC_Read_Byte(unsigned char ack);//IIC讀取一個字節
uint8_t IIC_Wait_Ack(void); 				//IIC等待ACK信號
void IIC_Ack(void);					//IIC發送ACK信號
void IIC_NAck(void);				//IIC不發送ACK信號

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	 
#endif

/*********************************************************************************************************
** End of File
*********************************************************************************************************/
