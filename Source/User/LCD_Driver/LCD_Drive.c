/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
**  �ү踹�}�o�O
**	LCD���h�X�ʵ{��
**  �����GRev1.0
**  ����G2011-6-20
**	�׾¡Gwww.openmcu.com
**	�^�_�Ghttp://shop36995246.taobao.com/
**  �޳N����s�G153631682 	 �޳NQQ�G77642732
**  Copyright(c)@���_�q�l	Dream_etd@163.com
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
//�Y���ե�
#include "usually.h"
#include "usart.h"
#include "LCD_Drive.h"
#include "hz16.h"
#include "font.h"

static uint16_t DeviceID;			//�w�qLCD�]��ID

uint16_t TextColor = BLUE , BlackColor = BLACK;

#define LCD_RAM    *(__IO uint16_t *) ((uint32_t)0x60020000)    	//�a�}�H�s��
#define LCD_REG    *(__IO uint16_t *) ((uint32_t)0x60000000)	 	//���O�H�s��

uint16_t Read_LCDReg(uint16_t LCD_Reg)
{
  uint16_t temp;

  LCD_REG= LCD_Reg;

  temp= LCD_RAM;

  return temp;
}
void Write_LCDReg(uint16_t LCD_Reg,uint16_t LCD_Dat)
{
  LCD_REG= LCD_Reg;	 		//�����O�H�s���g���O

  LCD_RAM= LCD_Dat; 			//���ƾڱH�s���g�ƾ�
}

void FSMC_LCDInit()
{
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;	   	//�w�q�@��NOR��l�Ƶ��c��
  FSMC_NORSRAMTimingInitTypeDef  p;						//�w�q�@��NOR�ɧǪ�l�Ƶ��c��

  p.FSMC_AddressSetupTime = 0x02;							//�a�}�إ߮ɶ��G0x1
  p.FSMC_AddressHoldTime = 0x00;							//�a�}�O���ɶ��G0x00
  p.FSMC_DataSetupTime = 0x05;							//�ƾګإ߮ɶ��G0x2
  p.FSMC_BusTurnAroundDuration = 0x00;
  p.FSMC_CLKDivision = 0x00;
  p.FSMC_DataLatency = 0x00;
  p.FSMC_AccessMode = FSMC_AccessMode_B;

  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;	   	//�X�iNOR BANK ����1�ӤlBANK
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  //���ϥ��`�u�_��
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;//�X�i������NOR FLASH
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  //�X�i�`�u�e�׬�16��
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

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 							//�ھګ��w�Ѽƪ�l�Ƶ��c��

  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE); 							//�ϯ�FSMC_Bank1_NORSRAM1 ���s

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);						//�ϯ�FSMC�`�u����
}
void GPIO_LCDInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO
                         ,ENABLE);										//�ϯ�U�Ӻݤf����

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
                                GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                                GPIO_Pin_11 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;						//�̤j��X50Mhz
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;						   	//�_�Υ\���X����
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                                GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |
                                GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;					   //�̤j��X50Mhz
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;						   //�_�Υ\���X����
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void Init_LCD(void)
{
  FSMC_LCDInit();									//LCD������FSMC���f��l��
  GPIO_LCDInit();								    //LCD������IO���f��l��
  DeviceID = Read_LCDReg(0x0000);					//Ū��LCD��ID�G�����ڭ�1289���̪�ID�O0x8999
  printf("DeviceID=0x%x\r\n",DeviceID);			//�H�Q���i��覡��XLCDŪ����ID
  if(DeviceID == 0x8999)
  {
    //************* Start Initial Sequence **********//
    Write_LCDReg(0x00, 0x0001); // �}�Ҥ�������
#if	 	LCD_ID_AM == 110
    Write_LCDReg(0x01, 0x3B3F); //��X�X�ʱ���: RL=0;REV=1;GD=1;BGR=0;SM=0;TB=1
#elif  	LCD_ID_AM == 001
    Write_LCDReg(0x01, 0x7B3F); //��X�X�ʱ���:RL=1;REV=1;GD=1;BGR=0;SM=0;TB=1
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
    Write_LCDReg(0x11, 0x6840); //262K��m  ������V�e�ƾ�,�����M������V�a�}����

#elif	LCD_ID_AM == 010
    Write_LCDReg(0x11, 0x6850); //262K��m  Entry mode setup. 262K type B, take care on the data bus with 16it only

#elif	LCD_ID_AM == 100
    Write_LCDReg(0x11, 0x6860); //262K��m  Entry mode setup. 262K type B, take care on the data bus with 16it only

#elif	LCD_ID_AM == 110
    Write_LCDReg(0x11, 0x6870); //262K��m  Entry mode setup. 262K type B, take care on the data bus with 16it only

#elif	LCD_ID_AM == 001
    Write_LCDReg(0x11, 0x6848); //262K��m  Entry mode setup. 262K type B, take care on the data bus with 16it only

#elif	LCD_ID_AM == 011
    Write_LCDReg(0x11, 0x6858); //262K��m  Entry mode setup. 262K type B, take care on the data bus with 16it only

#elif	LCD_ID_AM == 101
    Write_LCDReg(0x11, 0x6868); //262K��m  Entry mode setup. 262K type B, take care on the data bus with 16it only

#elif	LCD_ID_AM == 111
    Write_LCDReg(0x11, 0x6878); //262K��m  Entry mode setup. 262K type B, take care on the data bus with 16it only
#endif
    Write_LCDReg(0x07, 0x0033); // Display ON	*/
  }
  Clear_LCD(BLACK);
}
void Clear_LCD(uint16_t Color)
{
  uint32_t i;
  Set_LCDCorsor(0,0);								//�]�m���а_�l�a�}
  LCD_REG = 0x22;									//�ǳƼgRAM
  for(i=0; i<LCD_H_MAX*LCD_V_MAX; i++)				//240*320=76800����
  {
    LCD_RAM = Color;							//�V�ƾڱH�s���g�ƾ�
  }
}


//�b���w�ϰ줺��R���w�C��
//�ϰ�j�p:
//  (xend-xsta)*(yend-ysta)
void LCD_FulfillArea(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t Color)
{
  uint16_t i;
  uint16_t j;

  //�]�m�Ϥ���ܵ��f�j�p
  Write_LCDReg(0x44,xsta|(xsta+xend-1)<<8); //�]�m������VGRAM�_�l�a�}(�C�r�`���_�l�a�}�A���r�`�������a�})
  Write_LCDReg(0x45,ysta);				  	//�]�m���f��Y��V���}�l��m
  Write_LCDReg(0x46,ysta+yend-1);			//�]�m���f��Y��V��������m

  for(i=xsta; i<xend; i++)
    for(j=ysta; j<yend; j++)
    {
      Write_LCDReg(0x4E, i);							//�w�qx���_�l����
      Write_LCDReg(0x4F, j);							//�w�qy���_�l����
      LCD_REG = 0x22;    									//�ǳƼgRAM
      LCD_RAM= Color; 			//���ƾڱH�s���g�ƾ�
    }

  //�^�_���f
  Write_LCDReg(0x44,0|239<<8); 			//�]�m���f��X��V�}�l��m�M������m
  Write_LCDReg(0x45,0);				  		//�]�m���f��Y��V���}�l��m
  Write_LCDReg(0x46,319);			  	//�]�m���f��Y��V��������m

}

void LCD_FillRectangle(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t Color)
{
  uint16_t i;
  uint16_t j;

  //�]�m�Ϥ���ܵ��f�j�p
  Write_LCDReg(0x44,xsta|(xsta+xend-1)<<8); //�]�m������VGRAM�_�l�a�}(�C�r�`���_�l�a�}�A���r�`�������a�})
  Write_LCDReg(0x45,ysta);				  	//�]�m���f��Y��V���}�l��m
  Write_LCDReg(0x46,ysta+yend-1);			//�]�m���f��Y��V��������m

  for(j=0; j<yend-ysta; j++)				//240*320=76800����
  {
    Set_LCDCorsor(xsta,ysta+j);			//�]�m���а_�l�a�}
    LCD_REG = 0x22;						//�ǳƼgRAM
    for(i=0; i<yend-ysta; i++)				//240*320=76800����
    {
      LCD_RAM = Color;						//�V�ƾڱH�s���g�ƾ�
    }
  }

  //�^�_���f
  Write_LCDReg(0x44,0|239<<8); 			//�]�m���f��X��V�}�l��m�M������m
  Write_LCDReg(0x45,0);				  		//�]�m���f��Y��V���}�l��m
  Write_LCDReg(0x46,319);			  	//�]�m���f��Y��V��������m

  /*
  for(i=xsta; i<xend; i++)
    for(j=ysta; j<yend; j++)
    {
      Write_LCDReg(0x4E, i);							//�w�qx���_�l����
      Write_LCDReg(0x4F, j);							//�w�qy���_�l����
      LCD_REG = 0x22;    									//�ǳƼgRAM
      LCD_RAM= Color; 			//���ƾڱH�s���g�ƾ�
    }
  */
  //				RMI_LCDDispPoint(i,j,Color);

}

void Set_LCDCorsor(uint16_t x,uint16_t y)
{
#if	 	LCD_ID_AM == DsipV_ENABLE
  Write_LCDReg(0x4E, x);							//�w�qx���_�l����
  Write_LCDReg(0x4F, y);							//�w�qy���_�l����

#elif  	LCD_ID_AM == DsipH_ENABLE
  Write_LCDReg(0x4E, 239-y);						//�w�qx���_�l����
  Write_LCDReg(0x4F, 319-x);						//�w�qy���_�l����
#endif
}

uint8_t Disp_LCDChar(uint16_t x,uint16_t y,uint8_t star)
{
  uint8_t temp;
  uint16_t i,j;
  uint16_t y0;

  y0 = y;
  for(i=0; i<16; i++)								//�`��16�� �r�Ŭ�8*16 ��16
  {
    Set_LCDCorsor(x,y0);						//�]�m���а_�l��m
    LCD_REG = 0x22;								//�ǳƼgRAM
    temp = ASCII_1608[star-0x20][i];			//�ե�1608�r�Ůw
    for(j=0; j<8; j++)							//�`��8�� �r�Ŭ�8*16  �e8
    {
      if((temp<<j)&0x80)						//���ǰ���
      {
        LCD_RAM = TextColor;				//��1�h�I�G
      }
      else
      {
        LCD_RAM = BlackColor;				//��0�h�S�I���C��
      }
    }
    y0++;										//Y��V�a�}�[1
  }
  return (8);								  		//��^�r�Ť��������Z
}
/*****************************************************************************
** ��ƦW��: DisplayOneHzChar
** �\��y�z: ��ܤ@�ӫ��w�j�p���~�r
** �@  �@��: Dream
** ��@  ��: 2010�~12��06��
*****************************************************************************/
uint16_t Disp_LCDHz(uint16_t x,uint16_t y,uint8_t *pucMsk)
{
  uint16_t i,j;
  uint16_t mod[16];                                      /* ��e�r�� */
  uint16_t *pusMsk;                                      /* ��e�r�w�a�} */
  uint16_t y0;

  pusMsk = (uint16_t *)pucMsk;
  for(i=0; i<16; i++)                                    /* �O�s��e�~�r�I�}���r�� */
  {
    mod[i] = *pusMsk++;                                /* ���o��e�r�ҡA�b�r����X��*/
    mod[i] = ((mod[i] & 0xff00) >> 8) | ((mod[i] & 0x00ff) << 8);/* �r�ҥ洫���C�r�`�]���F��� */
    /* �ݭn�^ */
  }
  y0 = y;
  for(i=0; i<16; i++)                                    /* 16�� */
  {
    /* ������� */

    Set_LCDCorsor(x,y0);								//�]�m���а_�l��m
    LCD_REG = 0x22;										//�ǳƼgGRAM
    for(j=0; j<16; j++)                                /* 16�C       */
    {
      if((mod[i] << j)& 0x8000)                     /* ��ܦr��  */
      {
        LCD_RAM= TextColor;
      }
      else
      {
        LCD_RAM= BlackColor;                     /* ��Ū�覡���L�g�ť��I������*/
      }
    }
    y0++;
  }
  return (16);                                          /* ��^16��C�e */
}
void Disp_LCDString(uint16_t x,uint16_t y,uint8_t* p)
{
  uint16_t HzIndex;
  uint8_t Width=0;
  FNT_GB16 *ptGb16 = 0;

  ptGb16 = (FNT_GB16 *)GBHZ_16;

  while(1)
  {
    x=x+Width;								  	//X��V�[�r�Ū��e��
    if(*p=='\0') break;							//�P�_�r�Ŧ�O���O����
    if(*p > 0x80)								//�P�_���~�r
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
      HzIndex = findHzIndex(p);				//�j���~�r
      Width = Disp_LCDHz(x,y,(uint8_t *)&(ptGb16[HzIndex].Msk[0]));
      //��ܺ~�r
      p += 2;									//�~�r�a�}�[2
    }											//�P�_���D�~�r
    else
    {
      if (*p == '\r')                         //����
      {
        y = y + 16;                         //������ܧ���
        if(y > LCD_H_MAX)                   //�a���жW�X
        {
          y = 0;
        }
        p++;
        Width = 0;
        continue;
      }
      else if (*p == '\n')                    //�����_�I
      {
        x = 0;
        p++;
        Width = 0;
        continue;
      }
      if(x>LCD_H_MAX-8)						//�P�_������V�O�_�W�X�d��
      {
        x=0;
        y=y+16;
        if(y>LCD_V_MAX-16)
        {
          y=x=0;
          Clear_LCD(WHITE);
        }
        //�P�_������V�O�_�W�X�d��
      }
      Width = Disp_LCDChar(x,y,*p);			//��ܳ�Ӧr��
      p++;									//�r�Ŧa�}�[1
    }
  }
}

//��ܦr�Ŧ�
//x,y:�_�I����
//*p:�r�Ŧ�_�l�a�}
//��16�r��
void LCD_ShowString(uint16_t x,uint16_t y,uint8_t* p,u16 color)
{
  uint16_t HzIndex;
  uint8_t Width=0;
  FNT_GB16 *ptGb16 = 0;

  ptGb16 = (FNT_GB16 *)GBHZ_16;

  while(1)
  {
    x=x+Width;								  	//X��V�[�r�Ū��e��
    if(*p=='\0') break;							//�P�_�r�Ŧ�O���O����
    if(*p > 0x80)								//�P�_���~�r
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
      HzIndex = findHzIndex(p);				//�j���~�r
      Width = Disp_LCDHz(x,y,(uint8_t *)&(ptGb16[HzIndex].Msk[0]));
      //��ܺ~�r
      p += 2;									//�~�r�a�}�[2
    }											//�P�_���D�~�r
    else
    {
      if (*p == '\r')                         //����
      {
        y = y + 16;                         //������ܧ���
        if(y > LCD_H_MAX)                   //�a���жW�X
        {
          y = 0;
        }
        p++;
        Width = 0;
        continue;
      }
      else if (*p == '\n')                    //�����_�I
      {
        x = 0;
        p++;
        Width = 0;
        continue;
      }
      if(x>LCD_H_MAX-8)						//�P�_������V�O�_�W�X�d��
      {
        x=0;
        y=y+16;
        if(y>LCD_V_MAX-16)
        {
          y=x=0;
          Clear_LCD(WHITE);
        }
        //�P�_������V�O�_�W�X�d��
      }
      TextColor = color;

      Width = Disp_LCDChar(x,y,*p);			//��ܳ�Ӧr��
      p++;									//�r�Ŧa�}�[1
    }
  }


}

void Disp_LCDBmp(uint16_t Xstar,uint16_t Ystar,uint16_t Xend,uint16_t Yend,uint8_t* bmp)
{
  static	uint16_t i=0,j=0;
  uint16_t *bitbmp = (uint16_t *)bmp;

#if	 	LCD_ID_AM == DsipH_ENABLE	 //�NX��V�MY��V����
  uint16_t XY_Switch;
  XY_Switch = Xend;
  Xend = Yend;
  Yend = XY_Switch;
#endif

  //�]�m�Ϥ���ܵ��f�j�p
  Write_LCDReg(0x44,Xstar|(Xstar+Xend-1)<<8); //�]�m������VGRAM�_�l�a�}(�C�r�`���_�l�a�}�A���r�`�������a�})
  Write_LCDReg(0x45,Ystar);				  	//�]�m���f��Y��V���}�l��m
  Write_LCDReg(0x46,Ystar+Yend-1);			//�]�m���f��Y��V��������m

#if	 	LCD_ID_AM == DsipV_ENABLE
  Write_LCDReg(0x4E, Xstar);							//�w�qx���_�l����
  Write_LCDReg(0x4F, Ystar);							//�w�qy���_�l����
#elif  	LCD_ID_AM == DsipH_ENABLE
  Write_LCDReg(0x4E, Xstar);						//�w�qx���_�l����
  Write_LCDReg(0x4F, Ystar);						//�w�qy���_�l����
#endif

  LCD_REG = 0x22;							  	//�ǳƼg�ƾڨ�GRAM
  for(i=0; i<Yend; i++)
  {
    for(j=0; j<Xend; j++)LCD_RAM = *bitbmp++; //Delay_Ms(10);}
  }
  //�^�_���f
  Write_LCDReg(0x44,0|239<<8); 			//�]�m���f��X��V�}�l��m�M������m
  Write_LCDReg(0x45,0);				  		//�]�m���f��Y��V���}�l��m
  Write_LCDReg(0x46,319);			  	//�]�m���f��Y��V��������m
}
/*****************************************************************************
** ��ƦW��: Num_power
** �\��y�z: M��N����
** �@  �@��: Dream
** ��@  ��: 2010�~12��06��
*****************************************************************************/
uint32_t Num_power(uint8_t m,uint8_t n)
{
  u32 result=1;
  while(n--)result*=m;
  return result;
}
/*****************************************************************************
** ��ƦW��: LCD_ShowNum
** �\��y�z: �b���w��m��ܤ@��Ʀr
				num:�ƭ�(0~4294967295);
** �@  �@��: Dream
** ��@  ��: 2010�~12��06��
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
** ��ƦW��: Write_LCDRAM_Prepare
** �\��y�z: LCD���f�]�m
** �Ѽƴy�z�Gx�By����ܪ�����
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Write_LCDRAM_Prepare(void)
{
  LCD_REG = 0x22;									//�ǳƼgRAM
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��ƦW��: Read_LCDReg
** �\��y�z: Ū�H�s��
** �Ѽƴy�z�G�L
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Write_LCDRam(uint16_t LCD_Dat)
{
  LCD_RAM= LCD_Dat; 			//���ƾڱH�s���g�ƾ�
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��ƦW��: Disp_LCDPoint
** �\��y�z: ��ܤ@���I
** �Ѽƴy�z�Gx�By���r����ܪ���m
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
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
** ��ƦW��: Disp_LCDLine
** �\��y�z: �e�u
** �Ѽƴy�z: �b���w���ⰼ��m�e�@���u
**				x1,y1:�_�I���Ы�  x2,y2:���I����
** �@  �@��: Dream
** ��@  ��: 2010�~12��06��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Disp_LCDLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
  uint16_t t;
  int xerr=0,yerr=0,delta_x,delta_y,distance;
  int incx,incy,uRow,uCol;

  delta_x=x2-x1; 				//�p�⧤�мW�q
  delta_y=y2-y1;
  uRow=x1;
  uCol=y1;
  if(delta_x>0)incx=1; 		//�]�m��B��V
  else if(delta_x==0)incx=0;	//�����u
  else
  {
    incx=-1;
    delta_x=-delta_x;
  }
  if(delta_y>0)incy=1;
  else if(delta_y==0)incy=0;	//�����u
  else
  {
    incy=-1;
    delta_y=-delta_y;
  }
  if( delta_x>delta_y)distance=delta_x; //����򥻼W�q���жb
  else distance=delta_y;
  for(t=0; t<=distance+1; t++ )	//�e�u��X
  {
    Disp_LCDPoint(uRow,uCol);//�e�I
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

  delta_x=x2-x1; 				//�p�⧤�мW�q
  delta_y=y2-y1;
  uRow=x1;
  uCol=y1;
  if(delta_x>0)incx=1; 		//�]�m��B��V
  else if(delta_x==0)incx=0;	//�����u
  else
  {
    incx=-1;
    delta_x=-delta_x;
  }
  if(delta_y>0)incy=1;
  else if(delta_y==0)incy=0;	//�����u
  else
  {
    incy=-1;
    delta_y=-delta_y;
  }
  if( delta_x>delta_y)distance=delta_x; //����򥻼W�q���жb
  else distance=delta_y;
  for(t=0; t<=distance+1; t++ )	//�e�u��X
  {
    RMI_LCDDispPoint(uRow,uCol,color);//�e�I
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
** ��ƦW��: LCD_DrawLine
** �\��y�z: �b���w��m�e�@�ӫ��w�j�p����
				(x,y):�����I 	 r    :�b�|
** �@  �@��: Dream
** ��@  ��: 2010�~12��06��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Disp_LCDCircle(uint8_t x0,uint16_t y0,uint8_t r)
{
  int a,b;
  int di;
  a=0;
  b=r;
  di=3-(r<<1);             //�P�_�U���I��m���лx
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
    //�ϥ�Bresenham��k�e��
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
  di=3-(r<<1);             //�P�_�U���I��m���лx
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
    //�ϥ�Bresenham��k�e��
    if(di<0)di +=4*a+6;
    else
    {
      di+=10+4*(a-b);
      b--;
    }
    RMI_LCDDispPoint(x0+a,y0+b,color);
  }
}


//�e�x��
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
