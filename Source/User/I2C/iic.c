#include "iic.h"
#include "24LC02.h"
#include "usually.h"

//STM32�n�����IIC
u8 Data[24];

extern void Delay_Ms(uint16_t time); //���ɨ��
extern void Delay_Us(uint16_t time); //���ɨ��

extern u8 I2C_Address;


void CP_IIC_delay(void)
{

#if 1
//  u16 i=450; //G2
  uint8_t i = 40; //210	//�o�̥i�H�u�Ƴt��        �A�g���ճ̧C��150�ٯ�g�J
  while (i)
  {
    __nop();
    i--;
  }

#endif
//  Delay_Us(4); //smallest 11

}

///<-----Port
//����IIC�_�l�H��
void CP_IIC_Start(void)
{
  SDA_OUT(); //sda�u��X
  IIC_SDA = 1;
  IIC_SCL = 1;
  CP_IIC_delay(); //delay_us(4);
  IIC_SDA = 0; //START:when CLK is high,DATA change form high to low
  CP_IIC_delay(); //delay_us(4);
  IIC_SCL = 0; //�X��I2C�`�u�A�ǳƵo�e�α����ƾ�
}

//����IIC����H��
void CP_IIC_Stop(void)
{
  SDA_OUT(); //sda�u��X
  IIC_SCL = 0;
  IIC_SDA = 0; //STOP:when CLK is high DATA change form low to high
  CP_IIC_delay(); //delay_us(4);
  IIC_SCL = 1;
  IIC_SDA = 1; //�o�eI2C�`�u�����H��
  CP_IIC_delay(); //delay_us(4);
}

//���������H�����
//��^�ȡGFALSE�A������������
//        TRUE�A�����������\
bool CP_IIC_Wait_Ack(void)
{
  u8 ucErrTime = 0;
  SDA_IN(); //SDA�]�m����J
  IIC_SDA = 1;
  CP_IIC_delay(); //Delay_Us(1);
  IIC_SCL = 1;
  CP_IIC_delay(); //Delay_Us(1);
  while (READ_SDA)
//	if(READ_SDA)
  {
    ucErrTime++;
    if (ucErrTime > 5)
    {
      IIC_SCL = 0; //������X0
      IIC_Stop();
      return FALSE;
    }
  }
  IIC_SCL = 0; //������X0
  return TRUE;
}

//����ACK����
void CP_IIC_Ack(void)
{
  IIC_SCL = 0;
  SDA_OUT();
  IIC_SDA = 0;
  CP_IIC_delay(); //delay_us(2);
  IIC_SCL = 1;
  CP_IIC_delay(); //delay_us(2);
  IIC_SCL = 0;
}

//������ACK����
void CP_IIC_NAck(void)
{
  IIC_SCL = 0;
  SDA_OUT();
  IIC_SDA = 1;
  CP_IIC_delay(); //delay_us(2);
  IIC_SCL = 1;
  CP_IIC_delay(); //delay_us(2);
  IIC_SCL = 0;
}

//IIC�o�e�@�Ӧr�`
//��^�q�����L����
//1�A������
//0�A�L����
void CP_IIC_Send_Byte(u8 txd)
{
  u8 t;
  SDA_OUT();
  IIC_SCL = 0; //�ԧC�����}�l�ƾڶǿ�
  for (t = 0; t < 8; t++)
  {
//IIC_SDA=(txd&0x80)>>7;
    if ((txd &0x80) >> 7)
      IIC_SDA = 1;
    else
      IIC_SDA = 0;
    txd <<= 1;
    CP_IIC_delay(); //delay_us(2);   //��TEA5767�o�T�ө��ɳ��O������
    IIC_SCL = 1;
    CP_IIC_delay(); //delay_us(2);
    IIC_SCL = 0;
//		IIC_delay();//delay_us(2);
  }
}

//-------->Port
//Ū1�Ӧr�`�Aack=1�ɡA�o�eACK�Aack=0�A�o�enACK
uint8_t CP_IIC_Read_Byte(void)
{
  unsigned char i, receive = 0;
  SDA_IN(); //SDA�]�m����J
  for (i = 0; i < 8; i++)
  {
    IIC_SCL = 0;
    CP_IIC_delay(); //delay_us(2);
    IIC_SCL = 1;
    receive <<= 1;
    if (READ_SDA)
      receive++;
    CP_IIC_delay(); //delay_us(1);
  }
  return receive;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

uint8_t I2C_RMI_BufferRead(unsigned char RMI_Device_Addr, unsigned char Regaddr)
{
  unsigned char Regvalue;
  unsigned char RMI_Write_DeviceAddress, RMI_Read_DeviceAddress;
  uint8_t NumByteToRead = 1;

  RMI_Write_DeviceAddress = (RMI_Device_Addr << 1) | I2C_WRITE;
  RMI_Read_DeviceAddress = (RMI_Device_Addr << 1) | I2C_READ;

  CP_IIC_Start();

  CP_IIC_Send_Byte(RMI_Write_DeviceAddress);

  if (!CP_IIC_Wait_Ack())
  {
    CP_IIC_Stop();
    return FALSE;
  }

  CP_IIC_Send_Byte(Regaddr);
  if (!CP_IIC_Wait_Ack())
  {
    CP_IIC_Stop();
    return FALSE;
  }

  CP_IIC_Start();
  CP_IIC_Send_Byte(RMI_Read_DeviceAddress);
  if (!CP_IIC_Wait_Ack())
  {
    CP_IIC_Stop();
    return FALSE;
  }

  while (NumByteToRead)
  {
    Regvalue = CP_IIC_Read_Byte();
    if (NumByteToRead == 1)
      CP_IIC_NAck();
    else
      CP_IIC_Ack();
    NumByteToRead--;
  }
  CP_IIC_Stop();
  return Regvalue;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

bool I2C_RMI_BufferWrite(unsigned char RMI_Device_Addr, unsigned char REG_ADDR, unsigned char REG_VAL)
{
  unsigned char RMI_Write_DeviceAddress;
  u8 NumByteToWrite = 1;

  RMI_Write_DeviceAddress = (RMI_Device_Addr << 1) | I2C_WRITE;

  CP_IIC_Start();

  CP_IIC_Send_Byte(RMI_Write_DeviceAddress); //�]�m����a�}+�q�a�}
  if (!CP_IIC_Wait_Ack())
  {
    CP_IIC_Stop();
    return FALSE;
  }
  CP_IIC_Send_Byte(REG_ADDR); //�]�m�q���a�}
  if (!CP_IIC_Wait_Ack())
  {
    CP_IIC_Stop();
    return FALSE;
  }

  while (NumByteToWrite--)
  {
    CP_IIC_Send_Byte(REG_VAL);
    if (!CP_IIC_Wait_Ack())
    {
      CP_IIC_Stop();
      return FALSE;
    }
  }
  CP_IIC_Stop();
//�`�N�G�]���o�̭n����EEPROM�g���A�i�H�ĥάd�ߩΩ��ɤ覡(10ms)
//Systick_Delay_1ms(10);

  return TRUE;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

u8 I2C_RMI_BufferRead_cont(unsigned char RMI_Device_Addr, unsigned char Regaddr, u8 NumByteToRead)
{
  unsigned char Regvalue;
  unsigned char RMI_Write_DeviceAddress, RMI_Read_DeviceAddress;

  RMI_Write_DeviceAddress = (RMI_Device_Addr << 1) | I2C_WRITE;
  RMI_Read_DeviceAddress = (RMI_Device_Addr << 1) | I2C_READ;

  CP_IIC_Start();

  CP_IIC_Send_Byte(RMI_Write_DeviceAddress);

  if (!CP_IIC_Wait_Ack())
  {
    CP_IIC_Stop();
    return FALSE;
  }

  CP_IIC_Send_Byte(Regaddr);
  if (!CP_IIC_Wait_Ack())
  {
    CP_IIC_Stop();
    return FALSE;
  }

  CP_IIC_Send_Byte(0x00);
  if (!CP_IIC_Wait_Ack())
  {
    CP_IIC_Stop();
    return FALSE;
  }

  CP_IIC_Start();
  CP_IIC_Send_Byte(RMI_Read_DeviceAddress);
  if (!CP_IIC_Wait_Ack())
  {
    CP_IIC_Stop();
    return FALSE;
  }

  while (NumByteToRead)
  {
    Regvalue = CP_IIC_Read_Byte();
    if (NumByteToRead == 1)
      CP_IIC_NAck();
    else
      CP_IIC_Ack();
    NumByteToRead--;
  }
  CP_IIC_Stop();
  return Regvalue;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

uint8_t CP_RMI_Read(u8 Regaddr)
{
  unsigned char Regvalue;
  unsigned char RMI_Write_DeviceAddress, RMI_Read_DeviceAddress;

  RMI_Write_DeviceAddress = (I2C_Address << 1) | I2C_WRITE;
  RMI_Read_DeviceAddress = (I2C_Address << 1) | I2C_READ;

  CP_IIC_Start();

  CP_IIC_Send_Byte(RMI_Write_DeviceAddress);

  if (!CP_IIC_Wait_Ack())
  {
    CP_IIC_Stop();
    return FALSE;
  }

  CP_IIC_Send_Byte(Regaddr);
  if (!CP_IIC_Wait_Ack())
  {
    CP_IIC_Stop();
    return FALSE;
  }

  CP_IIC_Start();
  CP_IIC_Send_Byte(RMI_Read_DeviceAddress);
  if (!CP_IIC_Wait_Ack())
  {
    CP_IIC_Stop();
    return FALSE;
  }

  Regvalue = CP_IIC_Read_Byte();
  CP_IIC_NAck();

  CP_IIC_Stop();
  return Regvalue;
}


//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

uint8_t CP_BL_Read(u8 BL_I2C_ADDR,u8 Regaddr)
{
  unsigned char Regvalue;
  unsigned char RMI_Write_DeviceAddress, RMI_Read_DeviceAddress;

  RMI_Write_DeviceAddress = (BL_I2C_ADDR << 1) | I2C_WRITE;
  RMI_Read_DeviceAddress = (BL_I2C_ADDR << 1) | I2C_READ;

  CP_IIC_Start();

  CP_IIC_Send_Byte(RMI_Write_DeviceAddress);

  if (!CP_IIC_Wait_Ack())
  {
    CP_IIC_Stop();
    return FALSE;
  }

  CP_IIC_Send_Byte(Regaddr);
  if (!CP_IIC_Wait_Ack())
  {
    CP_IIC_Stop();
    return FALSE;
  }

  CP_IIC_Start();
  CP_IIC_Send_Byte(RMI_Read_DeviceAddress);
  if (!CP_IIC_Wait_Ack())
  {
    CP_IIC_Stop();
    return FALSE;
  }

  Regvalue = CP_IIC_Read_Byte();
  CP_IIC_NAck();

  CP_IIC_Stop();
  return Regvalue;
}
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

bool CP_RMI_Write(u8 Regaddr, unsigned char REG_VAL)
{
  unsigned char RMI_Write_DeviceAddress; //,RMI_Read_DeviceAddress;
  u8 NumByteToWrite = 1;

  RMI_Write_DeviceAddress = (I2C_Address << 1) | I2C_WRITE;
//	RMI_Read_DeviceAddress = (I2C_Address << 1) | I2C_READ;

  CP_IIC_Start();

  CP_IIC_Send_Byte(RMI_Write_DeviceAddress); //�]�m����a�}+�q�a�}
  if (!CP_IIC_Wait_Ack())
  {
    CP_IIC_Stop();
    return FALSE;
  }
  CP_IIC_Send_Byte(Regaddr);
  if (!CP_IIC_Wait_Ack())
  {
    CP_IIC_Stop();
    return FALSE;
  }

  while (NumByteToWrite--)
  {
    CP_IIC_Send_Byte(REG_VAL);
    if (!CP_IIC_Wait_Ack())
    {
      CP_IIC_Stop();
      return FALSE;
    }
  }
  CP_IIC_Stop();
//�`�N�G�]���o�̭n����EEPROM�g���A�i�H�ĥάd�ߩΩ��ɤ覡(10ms)
//Systick_Delay_1ms(10);

  return TRUE;
}

// User-supplied functions required to run this code sample:
//
// S32 readRMI(U16 addr, U08 *data, U16 num)
//      This function is used to read from the RMI registers of an attached Synaptics device.
//      The first parameter, addr, is the RMI address to read from.
//      The second parameter, data, is a pointer to the location of where to store the bytes read.
//      The final parameter is the number of consecutive bytes (RMI registers) to read.
//      The return value is the number of bytes successfully read.
//      If a read error occurs during the transfer, the function immediately returns with a value < 0.
//      Note! Return parameter is ignored in this sample code.
void readRMI(u8 reg_addr, u8 *data, u16 num)
{
//	u16 i;
  u8 tmp = 0;
  unsigned char RMI_Write_DeviceAddress, RMI_Read_DeviceAddress;

  RMI_Write_DeviceAddress = (I2C_Address << 1) | I2C_WRITE;
  RMI_Read_DeviceAddress = (I2C_Address << 1) | I2C_READ;

  CP_IIC_Start();

  CP_IIC_Send_Byte(RMI_Write_DeviceAddress);

  if (!CP_IIC_Wait_Ack())
  {
    CP_IIC_Stop();
//                return FALSE;
  }

  CP_IIC_Send_Byte(reg_addr);
  if (!CP_IIC_Wait_Ack())
  {
    CP_IIC_Stop();
//                return FALSE;
  }


  CP_IIC_Start();
  CP_IIC_Send_Byte(RMI_Read_DeviceAddress);
  if (!CP_IIC_Wait_Ack())
  {
    CP_IIC_Stop();
//                return FALSE;
  }

  while (num)
  {
    tmp = CP_IIC_Read_Byte();
    *data = tmp;
    data++;
    if (num == 1)
      CP_IIC_NAck();
    else
      CP_IIC_Ack();
    num--;
  }
  CP_IIC_Stop();

//	return sizeof(data)/sizeof(char);

}


//I2C���_�]�m
void I2C_Int_Set(u8 en)
{
  if(en)
  {
    EXTI->IMR|=1<<5;   //�}��line5�W�����_
    printf("I2C Interrupt ENABLE.\r\n");
  }
  else
  {
    EXTI->IMR&=~(1<<5); //����line5�W�����_
    printf("I2C Interrupt DISABLE.\r\n");
  }
}

//
// S32 writeRMI(U16 addr, U08 *data, U16 num)
//      This function is used to write to the RMI registers of an attached Synaptics device.
//      The first parameter, addr, is the RMI address to write to.
//      The second parameter, data, is a pointer to the location of the data to write.
//      The final parameter is the number of consecutive bytes (RMI registers) to write.
//      The return value is the number of bytes successfully written.
//      If a write error occurs during the transfer, the function immediately returns with a value < 0.
//      Note! Return parameter is ignored in this sample code.
int writeRMI(u8 reg_addr, u8 *data, u16 num)
{
  unsigned char RMI_Write_DeviceAddress;

  RMI_Write_DeviceAddress = (I2C_Address << 1) | I2C_WRITE;

  CP_IIC_Start();

  CP_IIC_Send_Byte(RMI_Write_DeviceAddress); //�]�m����a�}+�q�a�}
  if (!CP_IIC_Wait_Ack())
  {
    CP_IIC_Stop();
    return  - 1;
  }
  CP_IIC_Send_Byte(reg_addr); //�]�m�q���a�}
  if (!CP_IIC_Wait_Ack())
  {
    CP_IIC_Stop();
    return  - 1;
  }

  while (num--)
  {
    CP_IIC_Send_Byte(*data);
    data++;

    if (!CP_IIC_Wait_Ack())
    {
      CP_IIC_Stop();
      return  - 1;
    }
  }
  CP_IIC_Stop();
//�`�N�G�]���o�̭n����EEPROM�g���A�i�H�ĥάd�ߩΩ��ɤ覡(10ms)
//Systick_Delay_1ms(10);

  return 1;

}