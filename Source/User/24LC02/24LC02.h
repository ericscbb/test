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
//�ү踹�}�o�O�ϥΪ��O24c02�A�ҥH�w�qEE_TYPE��AT24C02
#define EE_TYPE AT24C02
					  
uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr);							//���w�a�}Ū���@�Ӧr�`
void AT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite);		//���w�a�}�g�J�@�Ӧr�`
void AT24CXX_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len);//���w�a�}�}�l�g�J���w���ת��ƾ�
uint32_t AT24CXX_ReadLenByte(uint16_t ReadAddr,uint8_t Len);					//���w�a�}�}�lŪ�����w���׼ƾ�
void AT24CXX_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite);	//�q���w�a�}�}�l�g�J���w���ת��ƾ�
void AT24CXX_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead);   	//�q���w�a�}�}�lŪ�X���w���ת��ƾ�

uint8_t AT24CXX_Check(void);  //�ˬd����
void AT24CXX_Init(void); //��l��IIC


//IO��V�]�m
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=0x80000000;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=0x30000000;}		  //0x3000000:50MHz;0x1000000:10MHz;0x2000000:2MHz

//IO�ާ@���	 
#define IIC_SCL    PBout(6) //SCL
#define IIC_SDA    PBout(7) //SDA	 
#define READ_SDA   PBin(7)  //��JSDA 

//IIC�Ҧ��ާ@���
void Init_IIC(void);                //��l��IIC��IO�f				 
void IIC_Start(void);				//�o�eIIC�}�l�H��
void IIC_Stop(void);	  			//�o�eIIC����H��
void IIC_Send_Byte(uint8_t txd);			//IIC�o�e�@�Ӧr�`
uint8_t IIC_Read_Byte(unsigned char ack);//IICŪ���@�Ӧr�`
uint8_t IIC_Wait_Ack(void); 				//IIC����ACK�H��
void IIC_Ack(void);					//IIC�o�eACK�H��
void IIC_NAck(void);				//IIC���o�eACK�H��

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	 
#endif

/*********************************************************************************************************
** End of File
*********************************************************************************************************/
