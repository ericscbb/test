/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
**  �ү踹�}�o�O
**	24LC02���h�X�� �o�̼���I2C
**  �����GRev1.0 
**  ����G2011-6-20
**	�׾¡Gwww.openmcu.com
**	�^�_�Ghttp://shop36995246.taobao.com/   
**  �޳N����s�G153631682 	 �޳NQQ�G77642732 
**  Copyright(c)@���_�q�l	Dream_etd@163.com	
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

/* Includes ------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
#include "usually.h"
#include "24LC02.h" 

extern void Delay_Ms(uint16_t time);  //���ɨ��
extern void Delay_Us(uint16_t time);  //���ɨ��

//�bAT24CXX���w�a�}Ū�X�@�Ӽƾ�
//ReadAddr:�}�lŪ�ƪ��a�}  
//��^��  :Ū�쪺�ƾ�
uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr)
{				  
	uint8_t temp=0;		  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	   //�o�e�g�R�O
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr>>8);//�o�e���a�}
		IIC_Wait_Ack();		 
	}else IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   //�o�e����a�}0XA0,�g�ƾ� 	 

	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr%256);   //�o�e�C�a�}
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);           //�i�J�����Ҧ�			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//���ͤ@�Ӱ������	    
	return temp;
}
//�bAT24CXX���w�a�}�g�J�@�Ӽƾ�
//WriteAddr  :�g�J�ƾڪ��ت��a�}    
//DataToWrite:�n�g�J���ƾ�
void AT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite)
{				   	  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	    //�o�e�g�R�O
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr>>8);//�o�e���a�}
		IIC_Wait_Ack();		 
	}else
	{
		IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   //�o�e����a�}0XA0,�g�ƾ� 
	}	 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr%256);   //�o�e�C�a�}
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);     //�o�e�r�`							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//���ͤ@�Ӱ������ 
	Delay_Ms(10);	 
}
//�bAT24CXX�̭������w�a�}�}�l�g�J���׬�Len���ƾ�
//�Ө�ƥΩ�g�J16bit�Ϊ�32bit���ƾ�.
//WriteAddr  :�}�l�g�J���a�}  
//DataToWrite:�ƾڼƲխ��a�}
//Len        :�n�g�J�ƾڪ�����2,4
void AT24CXX_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len)
{  	
	uint8_t t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

//�bAT24CXX�̭������w�a�}�}�lŪ�X���׬�Len���ƾ�
//�Ө�ƥΩ�Ū�X16bit�Ϊ�32bit���ƾ�.
//ReadAddr   :�}�lŪ�X���a�} 
//��^��     :�ƾ�
//Len        :�nŪ�X�ƾڪ�����2,4
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
//�ˬdAT24CXX�O�_���`
//�o�̥ΤF24XX���̫�@�Ӧa�}(255)�Ӧs�x�лx�r.
//�p�G�Ψ�L24C�t�C,�o�Ӧa�}�n�ק�
//��^1:�˴�����
//��^0:�˴����\
uint8_t AT24CXX_Check(void)
{
	uint8_t temp;
	temp=AT24CXX_ReadOneByte(255);//�קK�C���}�����gAT24CXX			   
	if(temp==0X55)return 0;		   
	else//�ư��Ĥ@����l�ƪ����p
	{
		AT24CXX_WriteOneByte(255,0X55);
	    temp=AT24CXX_ReadOneByte(255);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

//�bAT24CXX�̭������w�a�}�}�lŪ�X���w�Ӽƪ��ƾ�
//ReadAddr :�}�lŪ�X���a�} ��24c02��0~255
//pBuffer  :�ƾڼƲխ��a�}
//NumToRead:�nŪ�X�ƾڪ��Ӽ�
void AT24CXX_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  
//�bAT24CXX�̭������w�a�}�}�l�g�J���w�Ӽƪ��ƾ�
//WriteAddr :�}�l�g�J���a�} ��24c02��0~255
//pBuffer   :�ƾڼƲխ��a�}
//NumToWrite:�n�g�J�ƾڪ��Ӽ�
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
	GPIO_InitTypeDef GPIO_InitStructure;					//�w�q�@��GPIO���c���ܶq
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//�ϯ�U�Ӻݤf�����A���n�I�I�I

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;  //�t�mLED�ݤf������6�B12�B13�ݤf
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	   	//�q�ο�X�}�|
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   	//�t�m�ݤf�t�׬�50M
  	GPIO_Init(GPIOB, &GPIO_InitStructure);				   	//�N�ݤfGPIOD�i���l�ưt�m
}
//����IIC�_�l�H��
void IIC_Start(void)
{
	SDA_OUT();     //sda�u��X
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	Delay_Us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	Delay_Us(4);
	IIC_SCL=0;//�X��I2C�`�u�A�ǳƵo�e�α����ƾ� 
}	  
//����IIC����H��
void IIC_Stop(void)
{
	SDA_OUT();//sda�u��X
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	Delay_Us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//�o�eI2C�`�u�����H��
	Delay_Us(4);							   	
}
//���������H�����
//��^�ȡG1�A������������
//        0�A�����������\
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA_IN();      //SDA�]�m����J  
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
	IIC_SCL=0;//������X0 	   
	return 0;  
} 
//����ACK����
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
//������ACK����		    
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
//IIC�o�e�@�Ӧr�`
//��^�q�����L����
//1�A������
//0�A�L����			  
void IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//�ԧC�����}�l�ƾڶǿ�
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		Delay_Us(2);   //��TEA5767�o�T�ө��ɳ��O������
		IIC_SCL=1;
		Delay_Us(2); 
		IIC_SCL=0;	
		Delay_Us(2);
    }	 
} 	    
//Ū1�Ӧr�`�Aack=1�ɡA�o�eACK�Aack=0�A�o�enACK   
uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA�]�m����J
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
        IIC_NAck();//�o�enACK
    else
        IIC_Ack(); //�o�eACK   
    return receive;
} 
/*********************************************************************************************************
** End of File
*********************************************************************************************************/
