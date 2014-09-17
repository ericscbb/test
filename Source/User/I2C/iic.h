#ifndef __IIC_H
#define __IIC_H

#include "stm32f10x.h"

//Mini STM32開發板
//IIC 驅動函數


//IIC所有操作函數
uint8_t CP_RMI_Read(u8 Regaddr);
bool CP_RMI_Write(u8 Regaddr,unsigned char REG_VAL);
void CP_IIC_Start(void);
void CP_IIC_Stop(void);
bool CP_IIC_Wait_Ack(void);
void CP_IIC_Ack(void);
void CP_IIC_NAck(void);
void CP_IIC_Send_Byte(u8 txd);


//-----------------------------------------------------------------------------
// I2C Defines
//-----------------------------------------------------------------------------
#define I2C_READ	1
#define I2C_WRITE	0

uint8_t I2C_RMI_BufferRead(unsigned char RMI_Device_Addr,unsigned char Regaddr);
bool I2C_RMI_BufferWrite(unsigned char RMI_Device_Addr,unsigned char REG_ADDR,unsigned char REG_VAL);
uint8_t I2C_RMI_BufferRead_cont(unsigned char RMI_Device_Addr,unsigned char Regaddr,uint8_t NumByteToRead);
void readRMI(u8 reg_addr, u8 *data, u16 num);
int writeRMI(u8 reg_addr, u8 *data, u16 num);
uint8_t CP_BL_Read(u8 BL_I2C_ADDR,u8 Regaddr);

void I2C_Int_Set(u8 en);
#endif
















