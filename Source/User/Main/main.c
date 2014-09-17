/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
**	Main Function
**  �����GRev1.0
**  ����G2012-01-01
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

//�Y���ե�
#include "usually.h"
#include "usart.h"
#include "LCD_Drive.h"
#include "sdcard.h"
#include "ff.h"
#include "24LC02.h"
#include "iic.h"
#include "rtc.h"
#include "rmi.h"


//�n���~���ܶq
//extern  uint8_t    gImage_rainbow[];

//�n���ܶq
uint8_t I2C_Address;
uint8_t I2C_Write[]= {"ERIC:I2C Test!"};
uint8_t I2C_NULL[]= {"                                   "};
#define  Lenth  sizeof(I2C_Write)
uint8_t  I2C_Read[Lenth];
uint16_t  TIM_Count;	//�w�ɾ��p��
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
BYTE buff_filename[9][13];	//�̦h�u��Ū9�Ӥ��A�O�s9�Ӥ��W,���W�ĥεu���W�A�̦h13�Ӧr��

DMA_InitTypeDef DMA_InitStructure;									//�w�qDMA��l�Ƶ��c��

//��ƥө�
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
** ��ƦW��: main
** �\��y�z: �D��ƤJ�f
** �Ѽƴy�z�G	��������W�~�r���
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
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

  SystemInit();				//�t�ή����t�m

  Init_NVIC();				//���_�V�q����U���

  Init_Usart();				//��f�޸}�t�m
  Usart_Configure(115200);	//��f�t�m �]�m�i�S�v��115200
  Init_LED();					//LED��l��
  Init_KEY();					//�����l��

  Init_DMA();						//DMA��f��l��

  Init_IIC();					//24LC02��l��

  Init_TIMER();				//�w�ɾ���l��

  Init_LCD();	   				//LCD��l��

  Init_ATTN();

  TextColor = GREEN; 			//�ᤩ�奻�C�⬰BLUE
  BlackColor = BLACK;			//�ᤩ�I���C�⬰BLACK
//  Disp_LCDBmp(0,0,55,41,gImage_rainbow);   							//��ܤ@�i�j�p99*97���Ϥ�

  printf("<-----  STM32 EVB TEST  ----->\r\n");
  printf("Unique Device ID, 96 Bit: %08X,%08X,%08X.\r\n",Dev_Serial0,Dev_Serial1,Dev_Serial2);

//	Disp_LCDString(80,120,"2011-12-20");
  Disp_LCDString(60,0,"<STM32>");
//	Disp_LCDString(0,80,"SD: .  GByte");

  Init_RTC();					//����RTC��l��


  I2C_Int_Set(0);

//	Disp_LCDString(60,300,"Time Set OK!!!    ");
  Disp_LCDString(124,0,"    �~  ��  ��");  //��ܦ~���
  Disp_LCDString(170,15,"  :  :  ");		  //��ܮɤ���

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
      TextColor = WHITE; 			//�ᤩ�奻�C�⬰BLUE

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
      LED1=~LED1;										//LED1�{�{�A�{�Ǧb�B��
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
** ��ƦW��: stringcopy
** �\��y�z: �ƻs�\��
** �Ѽƴy�z�G�Nbuff_from�ƻs�� buff_to
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
uint8_t Stringcopy(BYTE *buff_to,BYTE *buff_from)
{
  u8 i=0;
  for(i=0; i<13; i++)
    buff_to[i] = buff_from[i];
  return 1;
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��ƦW��: LED_Init
** �\��y�z: LED IO�޸}�t�m
** �Ѽƴy�z�G�L
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Init_LED(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;											//�w�q�@��GPIO���c���ܶq

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD |RCC_APB2Periph_AFIO,ENABLE);	//�ϯ�U�Ӻݤf�����A���n�I�I�I

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_12 | GPIO_Pin_13; 		//�t�mLED�ݤf������6�B12�B13�ݤf
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	   	//�q�ο�X�}�|
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   	//�t�m�ݤf�t�׬�50M
  GPIO_Init(GPIOD, &GPIO_InitStructure);				   	//�N�ݤfGPIOD�i���l�ưt�m
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��ƦW��: Init_DMA
** �\��y�z: MDA�H�s���t�m
				�t�m��DMA�q�D1
** �Ѽƴy�z�G�L
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Init_DMA(void)
{
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	 				//�ϯ�DMA1����

  DMA_DeInit(DMA1_Channel4);											//�_��DMA1 6�q�D
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;	//DMA�~�]�a�}����f�ƾڱH�s��
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SendBuff;			//�s�x���a�}
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;			 		//�s�x�����ǿ鷽�a�}  �q�s�x��Ū
  DMA_InitStructure.DMA_BufferSize = sizeof(SendBuff);				//�w�s�j�p
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	//�~�]�a�}����
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;				//�s�x���a�}���W
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  //�ƾڼe�׬�8��
  DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;	//�s�x���ƾڼe�׬�8��
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;						//�u�@�b���`�w�s�Ҧ�
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;					//���_�u���Ű�
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;						//DMA�q�Dx�S���]�m�����s�줺�s�ǿ�
  DMA_Init(DMA1_Channel4, &DMA_InitStructure);						//�ھڰѼƪ�l��DMA�H�s��
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��ƦW��: Init_ATTN
** �\��y�z: I2C ���_�t�m
** �Ѽƴy�z�G�L
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Init_ATTN(void)
{
  EXTI_InitTypeDef  EXTI_InitStructure;					//�w�q�@��EXTI���c���ܶq

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO,ENABLE);		//�ϯ�IO�_�Υ\��A�ϥΤ��_�\�୫�n�I�I�I

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource0);
  //�t�m�ݤfE��0�޸}�����_��	  ���n�I�I
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;//���_�u��
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//���_�Ҧ������_�Ҧ�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	//�U���u�X�o
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//�ϯत�_�u
  EXTI_Init(&EXTI_InitStructure);							//�ھڰѼƪ�l�Ƥ��_�H�s��


  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);		//�ϯ�IO�_�Υ\��A�ϥΤ��_�\�୫�n�I�I�I

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);	 //�t�m�ݤfPB5�޸}�����_��	  ���n�I�I

  EXTI_InitStructure.EXTI_Line = EXTI_Line5;				//���_�u����5
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//���_�Ҧ������_�Ҧ�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	//�U���u�X�o
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//�ϯत�_�u
  EXTI_Init(&EXTI_InitStructure);							//�ھڰѼƪ�l�Ƥ��_�H�s��

}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��ƦW��: TIMER_Init
** �\��y�z: �w�ɾ�2��l�ưt�m
** �Ѽƴy�z�G�L
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Init_TIMER(void)
{
  TIM_TimeBaseInitTypeDef	 TIM_BaseInitStructure;			//�w�q�@�өw�ɾ����c���ܶq

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);   	//�ϯ�w�ɾ�2�A���n�I�I

  TIM_DeInit( TIM2);                              		//�NIM2�w�ɾ���l�Ʀ�_���

  TIM_InternalClockConfig(TIM2); 							//�t�m TIM2 ��������

  TIM_BaseInitStructure.TIM_Period = 1000; 				//�]�m�۰ʭ����H�s���Ȭ��̤j��	0~65535����  1000000/1000=1000us=1ms
  //TIM_Period�]TIM1_ARR�^=1000�A�p�ƾ��V�W�p�ƨ�1000�Უ�ͧ�s�ƥ�A
  //�p�ƭ��k�s �]�N�O 1MS���ͧ�s�ƥ�@��
  TIM_BaseInitStructure.TIM_Prescaler = 71;  				//�۩w�q�w���W�Y�ơA���ѵ��w�ɾ�������	0~65535����
  //�]�m�w���W�����W�Y��71�A�YAPB2=72M, TIM1_CLK=72/72=1MHz
  TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //�������ά�0
  TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  //TIM�V�W�p�ƼҦ� �q0�}�l�V�W�p�ơA�p�ƨ�1000�Უ�ͧ�s�ƥ�
//	TIM_BaseInitStructure.TIM_RepetitionCounter = 0; 		//���Ѽƥu�A�X��TIM1�MTIM8
  TIM_TimeBaseInit(TIM2, &TIM_BaseInitStructure); 		//�ھګ��w�Ѽƪ�l��TIM�ɶ���ƱH�s��

  TIM_ClearFlag(TIM2, TIM_FLAG_Update); 					//�M���_�A�H�K�@�ҥΤ��_��ߧY���ͤ��_

  TIM_ARRPreloadConfig(TIM2, DISABLE);					//�T��ARR �w�˸��w�ľ�

  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); 				//�ϯ�TIM2���_��
  TIM_Cmd(TIM2, ENABLE); 									//TIM2�`�}���G�}��

}
/*****************************************************************************
** ��ƦW��: TIM2_IRQHandler
** �\��y�z: �w�ɾ�2���_�B�z���
				1ms�����_��s
** �Ѽƴy�z�G�L
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
*****************************************************************************/
void TIM2_IRQHandler(void)
{
  static uint16_t count=0;
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 		//�P�_���_�лx��O�_��1�F��1�h���_�T���աA0�h�S��
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);       	//�M�����_���_��
    count++;
    TIM_Count--;										//�w�ɩ����ܶq��1
    if(count==500)										//�p�ƨ�500MS�A1MS*500
    {
      LED2 =~LED2;									//�H0.5��o�g���{�{
      count=0;	    								//�p�ƲM�s
    }
  }
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��ƦW��: TIM_Delay
** �\��y�z: �Q�Ωw�ɾ�����
** �Ѽƴy�z�G 		���ɮɶ�T = time*1(MS)
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void TIM_Delay(uint16_t time)  //���ɨ��
{
  TIM_Count = time;
  while(TIM_Count);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��ƦW��: KEY_Init
** �\��y�z: ���� IO�޸}�t�m
** �Ѽƴy�z�G�L
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Init_KEY()
{
  GPIO_InitTypeDef GPIO_InitStructure;					//�w�q�@��GPIO���c���ܶq
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOE,ENABLE);	//�ϯ�U�Ӻݤf�����A���n�I�I�I

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				//�t�mPB5
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //GPIO_Mode_IN_FLOATING; //GPIO_Mode_Out_OD //GPIO_Mode_IPU;//�W�Կ�J //GPIO_Mode_IPD;//�U�Կ�J
  GPIO_Init(GPIOB	,&GPIO_InitStructure);				   	//�N�ݤfGPIOB�i���l�ưt�m

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				//�t�m����USER������13�ݤf
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	   		//�t�m���W�Կ�J
  GPIO_Init(GPIOC	,&GPIO_InitStructure);				   	//�N�ݤfGPIOC�i���l�ưt�m

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2
                                | GPIO_Pin_3 | GPIO_Pin_4;								//�t�m�����n����䱾����0�B1�B2�B3�B4�ݤf
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	   		//�t�m���W�Կ�J
  GPIO_Init(GPIOE,&GPIO_InitStructure);				   	//�N�ݤfGPIOE�i���l�ưt�m

}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��ƦW��: KEY_Scan
** �\��y�z: ���䱽�˵{��
** �Ѽƴy�z�GKEY_Status�лx��
				��^���Ȥ��O���������
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
uint8_t KEY_Scan(void)
{
  static uint8_t KEY_Status =1; //�w�q�@�ӫ���лx��
  if(KEY_Status&&(KEY_USER==0||KEY_S==0||KEY_D==0||KEY_L==0||KEY_R==0||KEY_U==0))//�P�_�O�_��������U
  {
    Delay_Ms(10);//�h�ݰ�
    KEY_Status =0;
    if(KEY_USER==0) return 1;	  //����USER���U��^1
    else if(KEY_S==0) return 2;	  //����JOY-SEN���U��^1
    else if(KEY_D==0) return 3;	  //����JOY-DOWN���U��^1
    else if(KEY_L==0) return 4;	  //����JOY-LEFT���U��^1
    else if(KEY_R==0) return 5;	  //����JOY-RIGHT���U��^1
    else if(KEY_U==0) return 6;	  //����JOY-DOWN���U��^1
  }
  else if(KEY_USER==1&&KEY_S==1&&KEY_D==1&&KEY_L==1&&KEY_R==1&&KEY_U==1)KEY_Status=1;
  return 0;						  //�L������U��^0
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��ƦW��: NVIC_Configuration
** �\��y�z: �t�Τ��_�t�m
** �Ѽƴy�z�G�L
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Init_NVIC(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

#ifdef  VECT_TAB_RAM  									//�V�q���a�}���

  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);  			//�N0x20000000�a�}�@���V�q���a�}(RAM)
#else

  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0); 		//�N0x08000000�a�}�@���V�q���a�}(FLASH)
#endif

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//�����u����1��,�q�u����3��

  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;		//�]�w���_����PB5
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//���_���u���Ŭ�2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//���u���Ŭ�0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//�ϯत�_
  NVIC_Init(&NVIC_InitStructure);							   	//�ھڰѼƪ�l�Ƥ��_�H�s��

  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//�]�w���_����PC13
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//���_���u���Ŭ�1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//���u���Ŭ�0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//�ϯत�_
  NVIC_Init(&NVIC_InitStructure);							   	//�ھڰѼƪ�l�Ƥ��_�H�s��

  NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 			//���_�ƥ�TIM2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	//�m���u����0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;      	//�T���u����1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         	//���\���_
  NVIC_Init(&NVIC_InitStructure);                         	//�ھګ��w�Ѽƪ�l�Ƥ��_�H�s��

  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;				//RTC�������_
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//�����u����1��,�q�u����3��
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//�����u����0��,�q�u����4��
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//�ϯ�ӳq�D���_
  NVIC_Init(&NVIC_InitStructure);								//�ھ�NVIC_InitStruct�����w���Ѽƪ�l�ƥ~�]NVIC�H�s��


}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��ƦW��: EXTI0_IRQHandler
** �\��y�z: ���_0�J�f���
** �Ѽƴy�z�G�L
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void EXTI0_IRQHandler(void)
{
  extern bool b_infinite;

  if(EXTI_GetITStatus(EXTI_Line0)!= RESET)	 //�P�_�O�_�o�ͤ��_�A�o�ͫh���_�лx�m1
  {
//		Delay_Ms(10);							 //�Ω��ɨӮ����ݰ�
    EXTI_ClearITPendingBit(EXTI_Line0);		//�M�����_���_��A���n�I�I
    printf("EXTI0_IRQHandler assert!!\r\n");
    b_infinite = FALSE;
    RMI_Reset();
    Clean_RMI_Reset();

  }
//	EXTI_ClearITPendingBit(EXTI_Line0);		//�M�����_���_��A���n�I�I
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��ƦW��: EXTI5_IRQHandler
** �\��y�z: ���_0�J�f���
** �Ѽƴy�z�G�L
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
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
  if(EXTI_GetITStatus(EXTI_Line5)!= RESET)	 //�P�_�O�_�o�ͤ��_�A�o�ͫh���_�лx�m1
  {
    EXTI_ClearITPendingBit(EXTI_Line5);		//�M�����_���_��A���n�I�I

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
** ��ƦW��: Delay_Ms_Ms
** �\��y�z: ����1MS (�i�q�L��u�ӧP�_�L���ǽT��)
** �Ѽƴy�z�Gtime (ms) �`�Ntime<65535
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Delay_Ms(uint16_t time)  //���ɨ��
{
  uint16_t i,j;
  for(i=0; i<time; i++)
    for(j=0; j<10260; j++);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��ƦW��: Delay_Ms_Us
** �\��y�z: ����1us (�i�q�L��u�ӧP�_�L���ǽT��)
** �Ѽƴy�z�Gtime (us) �`�Ntime<65535
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Delay_Us(uint16_t time)  //���ɨ��
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
