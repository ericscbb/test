/*******************************************************************************
* Description        : This file provides RMI4 functions
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "iic.h"
#include "rmi.h"
#include "LCD_Drive.h"
#include "usually.h"
#include "math.h"

//Function 01
u8 F01_RMI_Query0_20 = 0;

u8 F01_RMI_Ctrl0 = 0;

u8 F01_RMI_Data0 = 0;
//u8 F01_RMI_Data1 = 0;
u8 F01_RMI_Cmd0 = 0;

//Function 05
u8 F05_IMG_Query0_5 = 0;
u8 F05_IMG_Ctrl0_5 = 0;
u8 F05_IMG_Data0_1 = 0;
u8 F05_IMG_Data2 = 0;
u8 F05_IMG_Cmd0 = 0;

//Function 11
u8 F11_2D_Query0 = 0;
//u8 F11_2D_Query1 = 0;
//u8 F11_2D_Query2 = 0;
//u8 F11_2D_Query3 = 0;
//u8 F11_2D_Query4 = 0;
//u8 F11_2D_Query5 = 0;
u8 F11_2D_Query6 = 0;
u8 F11_2D_Query7 = 0;
u8 F11_2D_Query8 = 0;
u8 F11_2D_Query9 = 0;
u8 F11_2D_Query10 = 0;
u8 F11_2D_Query11 = 0;
u8 F11_2D_Query12 = 0;
u8 F11_2D_Query13 = 0;

u8 F11_2D_Ctrl0_9 = 0;

//u8 F11_2D_Ctrl0 = 0;
//u8 F11_2D_Ctrl1 = 0;
//u8 F11_2D_Ctrl2 = 0;
//u8 F11_2D_Ctrl3 = 0;
//u8 F11_2D_Ctrl4 = 0;
//u8 F11_2D_Ctrl5 = 0;
//u8 F11_2D_Ctrl6 = 0;
//u8 F11_2D_Ctrl7 = 0;
//u8 F11_2D_Ctrl8 = 0;
//u8 F11_2D_Ctrl9 = 0;

//2D Pen Enable
u8 F11_2D_Ctrl10_19 =0;
u8 F11_2D_Ctrl20 = 0;
//Proximity Ctrl
//u8 F11_2D_Ctrl22 = 0;
//u8 F11_2D_Ctrl23 = 0;
//u8 F11_2D_Ctrl24 = 0;
//u8 F11_2D_Ctrl25 = 0;
//u8 F11_2D_Ctrl26 = 0;
//Palm Detect Ctrl
//u8 F11_2D_Ctrl27 = 0;
//MF Ctrol
//u8 F11_2D_Ctrl28 = 0;
//u8 F11_2D_Ctrl29 = 0;

u8 F11_2D_Data0 = 0;


u8 F11_2D_Data0_0 = 0;
u8 F11_2D_Data0_1 = 0;
u8 F11_2D_Data0_2 = 0;

//u8 F11_2D_Data1_5 = 0;
//u8 F11_2D_Data6_7 = 0;
//u8 F11_2D_Data8 = 0;
//u8 F11_2D_Data9 = 0;
//u8 F11_2D_Data10 = 0;
//u8 F11_2D_Data12 = 0;
u8 F11_2D_Data1_0 = 0;
u8 F11_2D_Data1_1 = 0;
u8 F11_2D_Data1_2 = 0;
u8 F11_2D_Data1_3 = 0;
u8 F11_2D_Data1_4 = 0;
u8 F11_2D_Data1_5 = 0;
u8 F11_2D_Data1_6 = 0;
u8 F11_2D_Data1_7 = 0;
u8 F11_2D_Data1_8 = 0;
u8 F11_2D_Data1_9 = 0;

//Relative data
u8 F11_2D_Data6_0 = 0;
u8 F11_2D_Data7_0 = 0;
u8 F11_2D_Data6_1 = 0;
u8 F11_2D_Data7_1 = 0;
//Gesture data
u8 F11_2D_Data8 = 0;
u8 F11_2D_Data9 = 0;
u8 F11_2D_Data10 = 0;
u8 F11_2D_Data11 = 0;
u8 F11_2D_Data12 = 0;
//Touch Shape
u8 F11_2D_Data13_0 = 0;
u8 F11_2D_Data13_1 = 0;
//MF scroll
u8 F11_2D_Data14 = 0;
u8 F11_2D_Data15 = 0;
u8 F11_2D_Data16 = 0;
u8 F11_2D_Data17 = 0;
//Contact Geometry
u8 F11_2D_Data18_0 = 0;
u8 F11_2D_Data19_0= 0;
u8 F11_2D_Data20_0 = 0;
u8 F11_2D_Data21_0 = 0;
u8 F11_2D_Data22_0 = 0;
u8 F11_2D_Data23_0= 0;
u8 F11_2D_Data24_0 = 0;
u8 F11_2D_Data25_0 = 0;
u8 F11_2D_Data26_0 = 0;
u8 F11_2D_Data27_0 = 0;
u8 F11_2D_Data18_1 = 0;
u8 F11_2D_Data19_1= 0;
u8 F11_2D_Data20_1 = 0;
u8 F11_2D_Data21_1 = 0;
u8 F11_2D_Data22_1 = 0;
u8 F11_2D_Data23_1= 0;
u8 F11_2D_Data24_1 = 0;
u8 F11_2D_Data25_1 = 0;
u8 F11_2D_Data26_1 = 0;
u8 F11_2D_Data27_1 = 0;
//2D Extended Status
u8 F11_2D_Data28 = 0;
//Cxy LSB
u8 F11_2D_Data29 = 0;
//Cxy MSB
u8 F11_2D_Data30 = 0;
//Pen Z
u8 F11_2D_Data31 = 0;
//u8 F11_2D_Data32 = 0;
//u8 F11_2D_Data33 = 0;
//u8 F11_2D_Data34 = 0;
//2D Wy/Wx High
u8 F11_2D_Data35_0 = 0;
u8 F11_2D_Data35_1 = 0;
u8 F11_2D_Data35_2 = 0;
u8 F11_2D_Data35_3 = 0;
u8 F11_2D_Data35_4 = 0;
u8 F11_2D_Data35_5 = 0;
u8 F11_2D_Data35_6 = 0;
u8 F11_2D_Data35_7 = 0;
u8 F11_2D_Data35_8 = 0;
u8 F11_2D_Data35_9 = 0;


u8 F11_2D_Cmd0 = 0;

//Func54
u8 F54_Query_Base = 0;
u8 F54_Control_Base = 0;
u8 F54_Data_Base = 0;
u8 F54_Command_Base = 0;

//S3200
u8 F54_ANALOG_CTRL15_18	=0;
u8 F54_ANALOG_CTRL16_0	=0;

u8 F54_ANALOG_CTRL36_18=0;
//S3201
//u8 F54_ANALOG_CTRL15_17=0;
u8 F54_ANALOG_CTRL16_11 = 0;
//S3203
u8 F54_ANALOG_CTRL15_19=0;
u8 F54_ANALOG_CTRL15_20=0;
u8 F54_ANALOG_CTRL15_21=0;
u8 F54_ANALOG_CTRL15_22=0;
u8 F54_ANALOG_CTRL16_12 = 0;

u8 F54_ANALOG_CTRL36_19=0;
u8 F54_ANALOG_CTRL36_20=0;
u8 F54_ANALOG_CTRL36_21=0;
u8 F54_ANALOG_CTRL36_22=0;

//S3202
u8 F54_ANALOG_CTRL15_23=0;
u8 F54_ANALOG_CTRL15_24=0;
u8 F54_ANALOG_CTRL15_25=0;
u8 F54_ANALOG_CTRL15_26=0;
u8 F54_ANALOG_CTRL15_27=0;

u8 F54_ANALOG_CTRL16_13 = 0;
u8 F54_ANALOG_CTRL16_14 = 0;
u8 F54_ANALOG_CTRL16_15 = 0;

u8 F54_ANALOG_CTRL36_23=0;
u8 F54_ANALOG_CTRL36_24=0;
u8 F54_ANALOG_CTRL36_25=0;
u8 F54_ANALOG_CTRL36_26=0;
u8 F54_ANALOG_CTRL36_27=0;
//S7300
u8 F54_ANALOG_CTRL15_44=0;
u8 F54_ANALOG_CTRL15_45=0;
u8 F54_ANALOG_CTRL15_46=0;

u8 F54_ANALOG_CTRL16_27 = 0;
u8 F54_ANALOG_CTRL16_28 = 0;
u8 F54_ANALOG_CTRL16_29 = 0;

u8 F54_ANALOG_CTRL36_44=0;
u8 F54_ANALOG_CTRL36_45=0;
u8 F54_ANALOG_CTRL36_46=0;
//S7301
u8 F54_ANALOG_CTRL15_28=0;
u8 F54_ANALOG_CTRL15_29=0;
u8 F54_ANALOG_CTRL15_30=0;
u8 F54_ANALOG_CTRL15_31=0;
u8 F54_ANALOG_CTRL15_32=0;
u8 F54_ANALOG_CTRL15_33=0;
u8 F54_ANALOG_CTRL15_34=0;
u8 F54_ANALOG_CTRL15_35=0;
u8 F54_ANALOG_CTRL15_36=0;
u8 F54_ANALOG_CTRL15_37=0;
u8 F54_ANALOG_CTRL15_38=0;
u8 F54_ANALOG_CTRL15_39=0;
u8 F54_ANALOG_CTRL15_40=0;
u8 F54_ANALOG_CTRL15_41=0;
u8 F54_ANALOG_CTRL15_42=0;
u8 F54_ANALOG_CTRL15_43=0;

u8 F54_ANALOG_CTRL16_16 = 0;
u8 F54_ANALOG_CTRL16_17 = 0;
u8 F54_ANALOG_CTRL16_18 = 0;
u8 F54_ANALOG_CTRL16_19 = 0;
u8 F54_ANALOG_CTRL16_20 = 0;
u8 F54_ANALOG_CTRL16_21 = 0;
u8 F54_ANALOG_CTRL16_22 = 0;
u8 F54_ANALOG_CTRL16_23 = 0;
u8 F54_ANALOG_CTRL16_24 = 0;
u8 F54_ANALOG_CTRL16_25 = 0;
u8 F54_ANALOG_CTRL16_26 = 0;

u8 F54_ANALOG_CTRL17 = 0;

u8 F54_ANALOG_CTRL36_28=0;
u8 F54_ANALOG_CTRL36_29=0;
u8 F54_ANALOG_CTRL36_30=0;
u8 F54_ANALOG_CTRL36_31=0;
u8 F54_ANALOG_CTRL36_32=0;
u8 F54_ANALOG_CTRL36_33=0;
u8 F54_ANALOG_CTRL36_34=0;
u8 F54_ANALOG_CTRL36_35=0;
u8 F54_ANALOG_CTRL36_36=0;
u8 F54_ANALOG_CTRL36_37=0;
u8 F54_ANALOG_CTRL36_38=0;
u8 F54_ANALOG_CTRL36_39=0;
u8 F54_ANALOG_CTRL36_40=0;
u8 F54_ANALOG_CTRL36_41=0;
u8 F54_ANALOG_CTRL36_42=0;
u8 F54_ANALOG_CTRL36_43=0;

//Axis 2 compensation
//u8 F54_ANALOG_CTRL37 = 0;
u8 F54_ANALOG_CTRL38 = 0;

//Func34
u8 F34_FLASH_QUERY_BASE = 0;
u8 F34_FLASH_COMMAND_BASE = 0;
u8 F34_FLASH_CONTROL_BASE = 0;
u8 F34_FLASH_DATA_BASE = 0;

//Function 1A - 0D button
u8 F1A_0D_QUERY_BASE = 0;
u8 F1A_0D_COMMAND_BASE = 0;
u8 F1A_0D_CONTROL_BASE = 0;
u8 F1A_0D_CTRL3_0 = 0;
u8 F1A_0D_CTRL4_0 = 0;
u8 F1A_0D_CTRL3_1 = 0;
u8 F1A_0D_CTRL4_1 = 0;
u8 F1A_0D_CTRL3_2 = 0;
u8 F1A_0D_CTRL4_2 = 0;
u8 F1A_0D_CTRL3_3 = 0;
u8 F1A_0D_CTRL4_3 = 0;
u8 F1A_0D_CTRL5_0 = 0;
u8 F1A_0D_CTRL5_1 = 0;
u8 F1A_0D_CTRL5_2 = 0;
u8 F1A_0D_CTRL5_3 = 0;

u8 F1A_0D_CTRL06 = 0;


u8 F1A_0D_DATA_BASE = 0;
//Function 31 - LED
u8 F31_LED_QUERY_BASE = 0;
u8 F31_LED_COMMAND_BASE = 0;
u8 F31_LED_CONTROL_BASE = 0;
u8 F31_LED_DATA_BASE = 0;

/*
//Function 09
u8 F09_Data_base_address=0;
u8 F09_Ctrl_base_address=0;
u8 F09_Cmd_base_address=0;
u8 F09_Query_base_address=0;

//Function 19
u8 F19_Data_base_address=0;
u8 F19_Ctrl_base_address=0;
u8 F19_Cmd_base_address=0;
u8 F19_Query_base_address=0;
*/

u8 NumOfFingers_Reporting=0;
u8 F11_2D_Data0_registerCount=0;
u8 MaxButtonCount=0;

bool HasFlashInt;
bool HasStatusInt;
bool HasAbs0Int;
bool HasAbs1Int;
bool HasButtonInt;
bool HasBistInt;
bool HasAnalogInt;

sensor_general_info sensor;

extern void Delay_Ms(uint16_t time);  //���ɨ��
extern void Delay_Us(uint16_t time);  //���ɨ��

extern uint8_t I2C_Address;

bool F01_exist=FALSE;
bool F11_exist=FALSE;
bool F34_exist=FALSE;
bool F54_exist=FALSE;
bool F1A_exist=FALSE;
bool F31_exist=FALSE;

//Fun11 Query
bool HasQuery9= FALSE;
bool HasQuery11= FALSE;
bool HasQuery12= FALSE;
bool HasSensitivityAdjust= FALSE;
bool HasGestures = FALSE;
bool HasAbsMode= FALSE;
bool HasRelMode= FALSE;

u8 nfsg; //num of finger status registers
char ProductID[10];
u16 Package_ID;
u16 Package_ID_Rev;
u32 Packrat_Num;
u8 totalInts=0;

bool b_Has8bitW;

//char month[12]={"January","February","March","April","May","June","July","August","September","October","November","December"};
//String[] Month= {"January", "February", "March", "April", "May","June", "July", "August", "September", "October", "November","December"};
//typedef enum {All, January, February, March, April,May, June, July, August, September, October, September, December} month;

//------------------------------------------------
// Fun: Find CP I2C address
//------------------------------------------------
u8 find_CP_IIC_address(void)
{
  u16 tmp;
  for(tmp=0; tmp<=255; tmp++)
  {
    I2C_RMI_BufferWrite(tmp,Page_Select_register,0x01);
    if(I2C_RMI_BufferRead(tmp,Page_Select_register) && (I2C_RMI_BufferRead(tmp,PdtCheck_Start) == 0x54))
    {
      I2C_RMI_BufferWrite(tmp,Page_Select_register,0x00);
      return tmp;
    }
  }
  return 0;
}

void read_all_reg(void)
{
  u16 tmp;
//	for(tmp=0x14;tmp<0x4b;tmp++) printf("REG 0x%x : 0x%x \r\n",tmp,I2C_RMI_BufferRead(I2C_Address,tmp));
  for(tmp=0x00; tmp<=0xff; tmp++)
  {
    printf("REG 0x%x: 0x%x.",tmp,I2C_RMI_BufferRead(I2C_Address,tmp));
    if ((tmp>0) && (((tmp+1) % 5) == 0)) 	printf("\r\n");
  }

}

void read_attn_reg(void)
{
  u16 tmp;
//	for(tmp=0x14;tmp<0x4b;tmp++) printf("REG 0x%x : 0x%x \r\n",tmp,I2C_RMI_BufferRead(I2C_Address,tmp));
  for(tmp=0x14; tmp<=0x57; tmp++) printf("REG 0x%x : 0x%x.\r\n",tmp,I2C_RMI_BufferRead(I2C_Address,tmp));

}
void PDT_scan(void)
{
  Rmi_register_type pdt_reg,next_pdt_reg;
  u8 next_start_addr=0;

  pdt_reg.Fun_Exist = I2C_RMI_BufferRead(I2C_Address,PdtCheck_Start);

  if(pdt_reg.Fun_Exist != 0)
  {
    printf("PDT Search Start...\r\n");

    pdt_reg.Int_num    =	I2C_RMI_BufferRead(I2C_Address,PdtCheck_Start-1);
    pdt_reg.Data_Base  =	I2C_RMI_BufferRead(I2C_Address,PdtCheck_Start-2);
    pdt_reg.Ctrl_Base  =	I2C_RMI_BufferRead(I2C_Address,PdtCheck_Start-3);
    pdt_reg.Cmd_Base   =	I2C_RMI_BufferRead(I2C_Address,PdtCheck_Start-4);
    pdt_reg.Query_Base =	I2C_RMI_BufferRead(I2C_Address,PdtCheck_Start-5);

    totalInts += pdt_reg.Int_num  & 0x07;

    if (pdt_reg.Fun_Exist == 0x34)
    {
      printf("Fun34(Page0) exists.\r\n");
      F34_exist = TRUE;
      F34_FLASH_DATA_BASE  = pdt_reg.Data_Base;
      F34_FLASH_CONTROL_BASE  = pdt_reg.Ctrl_Base;
      F34_FLASH_COMMAND_BASE   = pdt_reg.Cmd_Base;
      F34_FLASH_QUERY_BASE = pdt_reg.Query_Base;
      if(F34_exist)		printf("F34_FLASH_QUERY_BASE:0x%x,F34_FLASH_COMMAND_BASE:0x%x,F34_FLASH_CONTROL_BASE:0x%x,F34_FLASH_DATA_BASE:0x%x.F34_FLASH_DATA02_15:0x%x.\r\n",F34_FLASH_QUERY_BASE,F34_FLASH_COMMAND_BASE,F34_FLASH_CONTROL_BASE,F34_FLASH_DATA_BASE,F34_FLASH_DATA02_15);

    }
    else if	(pdt_reg.Fun_Exist == 0x54)
    {
      printf("Fun54(Page1) exists.\r\n");
      F54_exist = TRUE;
      F54_Data_Base  = pdt_reg.Data_Base;
      F54_Control_Base  = pdt_reg.Ctrl_Base;
      F54_Command_Base   = pdt_reg.Cmd_Base;
      F54_Query_Base = pdt_reg.Query_Base;
      if(F54_exist)		printf("F54_Query_Base:0x%x,F54_Control_Base:0x%x,F54_Data_Base:0x%x,F54_Command_Base:0x%x.\r\n",F54_Query_Base,F54_Control_Base,F54_Data_Base,F54_Command_Base);

    }
    else if	(pdt_reg.Fun_Exist == 0x31)
    {
      printf("Fun31(Page2) exists.\r\n");
      F31_exist = TRUE;
      F31_LED_DATA_BASE  	= pdt_reg.Data_Base;
      F31_LED_CONTROL_BASE  	= pdt_reg.Ctrl_Base;
      F31_LED_COMMAND_BASE   = pdt_reg.Cmd_Base;
      F31_LED_QUERY_BASE 	= pdt_reg.Query_Base;
      if(F54_exist)		printf("F31_LED_QUERY_BASE:0x%x,F31_LED_CONTROL_BASE:0x%x,F31_LED_DATA_BASE:0x%x,F31_LED_COMMAND_BASE:0x%x.\r\n",F31_LED_QUERY_BASE,F31_LED_CONTROL_BASE,F31_LED_DATA_BASE,F31_LED_COMMAND_BASE);

    }
  }//if pdt_reg

  next_start_addr = PdtCheck_Start - 6;
//   	printf("next_start_addr:0x%x.\r\n",next_start_addr);
//    printf("next_start_reg_value:0x%x.\r\n",I2C_RMI_BufferRead(addr,next_start_addr));

  for(;;)
  {
    next_pdt_reg.Fun_Exist=I2C_RMI_BufferRead(I2C_Address,next_start_addr);

    if(next_pdt_reg.Fun_Exist !=0)
    {
      next_pdt_reg.Int_num    =	I2C_RMI_BufferRead(I2C_Address,next_start_addr-1);
      next_pdt_reg.Data_Base  =	I2C_RMI_BufferRead(I2C_Address,next_start_addr-2);
      next_pdt_reg.Ctrl_Base  =	I2C_RMI_BufferRead(I2C_Address,next_start_addr-3);
      next_pdt_reg.Cmd_Base   =	I2C_RMI_BufferRead(I2C_Address,next_start_addr-4);
      next_pdt_reg.Query_Base =	I2C_RMI_BufferRead(I2C_Address,next_start_addr-5);

      totalInts += (next_pdt_reg.Int_num  & 0x07);
//		printf("next_pdt_reg.Fun_Exist:0x%x.\r\n",next_pdt_reg.Fun_Exist);


      switch (next_pdt_reg.Fun_Exist)
      {
        case 0x01:
          printf("Fun01 exists.\r\n");
          F01_exist = TRUE;

          F01_RMI_Data0  = next_pdt_reg.Data_Base;
          F01_RMI_Ctrl0  = next_pdt_reg.Ctrl_Base;
          F01_RMI_Cmd0   = next_pdt_reg.Cmd_Base;
          F01_RMI_Query0_20 = next_pdt_reg.Query_Base;
          if(F01_exist)		printf("F01_RMI_Query0_20:0x%x,F01_RMI_Ctrl0:0x%x,F01_RMI_Data0:0x%x,F01_RMI_Cmd0:0x%x.\r\n",F01_RMI_Query0_20,F01_RMI_Ctrl0,F01_RMI_Data0,F01_RMI_Cmd0);
          break;
        case 0x11:
          printf("Fun11 exists.\r\n");
          F11_exist = TRUE;

          F11_2D_Data0  = next_pdt_reg.Data_Base;
          F11_2D_Ctrl0_9  = next_pdt_reg.Ctrl_Base;
          F11_2D_Cmd0   = next_pdt_reg.Cmd_Base;
          F11_2D_Query0 = next_pdt_reg.Query_Base;
          if(F11_exist)		printf("F11_2D_Query0:0x%x,F11_2D_Ctrl0_9:0x%x,F11_2D_Data0:0x%x,F11_2D_Cmd0:0x%x.\r\n",F11_2D_Query0,F11_2D_Ctrl0_9,F11_2D_Data0,F11_2D_Cmd0);
          break;

        case 0x1A:
          printf("Fun1A exists.\r\n");
          F1A_exist = TRUE;

          F1A_0D_DATA_BASE  		= next_pdt_reg.Data_Base;
          F1A_0D_CONTROL_BASE 	= next_pdt_reg.Ctrl_Base;
          F1A_0D_COMMAND_BASE   	= next_pdt_reg.Cmd_Base;
          F1A_0D_QUERY_BASE 		= next_pdt_reg.Query_Base;
          if(F11_exist)		printf("F1A_0D_QUERY_BASE:0x%x,F1A_0D_CONTROL_BASE:0x%x,F1A_0D_DATA_BASE:0x%x,F1A_0D_COMMAND_BASE:0x%x.\r\n",F1A_0D_QUERY_BASE,F1A_0D_CONTROL_BASE,F1A_0D_DATA_BASE,F1A_0D_COMMAND_BASE);
          break;
      }

      next_start_addr = next_start_addr - 6;
//			printf("next_start_addr:0x%x.\r\n",next_start_addr);
    } //if
    else
    {
      printf("Func Exist = 0!\r\n");
      goto EXIT;
    }
  } //for(;;)
EXIT:

  printf("Func Exist = 0 . PDT Search Done!\r\n");

}

void constructFunc11(void)
{
  u8 NumberOfSensors;
  u8 NumOfFingers;
  u8 tmp;
  u8 NumberOfXElectrodes,NumberOfYElectrodes,MaximumElectrodes;
  u8 AbsDataSize;
  bool b_HasJitterFilter;
  bool b_HasLargeObjectSuppression;
  bool b_HasBendingCorrection;
  bool b_HasDribble;
  bool b_HasAdjHyst;
  bool b_AnchoredFinger;
  bool b_HasNewPenRegisters;
  bool b_HasPenHoverDiscrimination;
  bool b_HasTwoPenThresholds;
  bool b_HasSuppressOnPalmDetect;
  bool b_HasLargeObjectSensitivity;
  bool b_HasFingerProximity;
  bool b_HasPen;
  bool b_HasDrummingCorrection;
  bool b_HasTxRxClip;
  bool b_HasSegmentationAggressiveness;
  bool b_HasDefaultFingerWidth;
  bool b_HasPitchInfo;
  bool b_HasWTuning;
  bool b_HasPositionInterpolationTuning;
  bool b_HasZTuning;
  bool b_Has2DAdjustableMapping;
//	bool b_Has8bitW;
  u8 JitterFilterType;
  u8 JitterAverageWindowSize;

//Func 11 Query for DS4 v3
  tmp = I2C_RMI_BufferRead(I2C_Address,F11_2D_Query0);
  NumberOfSensors = (tmp & 0x07) + 1;
  //printf("Func11 Query: I2C_Address:0x%x,F11_2D_Query0:0x%x,tmp:0x%x...\r\n",I2C_Address,F11_2D_Query0,tmp);
  printf("Func11 Query: NumberOfSensors:%d.\r\n",NumberOfSensors);

  if(tmp & 0x08)
  {
    HasQuery9 = TRUE;
    printf("Func11 Query: F11_2D_Query9 register exists.\r\n");
  }
  else		HasQuery9 = FALSE;

  if(tmp & 0x10)
  {
    HasQuery11 = TRUE;
    printf("Func11 Query: F11_2D_Query11 register exists.\r\n");
  }
  else		HasQuery11 = FALSE;

  if(tmp & 0x20)
  {
    HasQuery12 = TRUE;
    printf("Func11 Query: F11_2D_Query12 register exists.\r\n");
  }
  else		HasQuery12 = FALSE;

  tmp = I2C_RMI_BufferRead(I2C_Address,F11_2D_Query1);
//			printf("I2C_Address:0x%x,F11_2D_Query1:0x%x,tmp:0x%x...\r\n",I2C_Address,F11_2D_Query1,tmp);
  NumOfFingers = 	tmp & 0x07;
  printf("NumOfFingers: 0x%x.\r\n",NumOfFingers);

  if(tmp & 0x40)
  {
    HasSensitivityAdjust = TRUE;
    printf("Func11 Query: Has Sensitivity Adjust.\r\n");
  }
  else		HasSensitivityAdjust = FALSE;

  if(tmp & 0x20)
  {
    HasGestures = TRUE;
    printf("Func11 Query: Critial error ::: DS4 v3??\r\n");
  }
  else		HasGestures = FALSE;

  if(tmp & 0x10)
  {
    HasAbsMode = TRUE;
    printf("Func11 Query: Has AbsMode.\r\n");
  }
  else		HasAbsMode = FALSE;

  if(tmp & 0x08)
  {
    HasRelMode = TRUE;
    printf("Func11 Query: Has RelMode.\r\n");
  }
  else		HasRelMode = FALSE;

  NumberOfXElectrodes = I2C_RMI_BufferRead(I2C_Address,F11_2D_Query2) & 0x7F;
  NumberOfYElectrodes = I2C_RMI_BufferRead(I2C_Address,F11_2D_Query3)	& 0x7F;
  MaximumElectrodes = I2C_RMI_BufferRead(I2C_Address,F11_2D_Query4)	& 0x7F;
  printf("Func11 Query: NumberOfXElectrodes:%d,NumberOfYElectrodes:%d,MaximumElectrodes:%d.\r\n",NumberOfXElectrodes,NumberOfYElectrodes,MaximumElectrodes);

  tmp = I2C_RMI_BufferRead(I2C_Address,F11_2D_Query5);
  AbsDataSize = tmp & 0x03;
  printf("Func11 Query: Absolute Data Size:0x%x.\r\n",AbsDataSize);

  if(tmp & 0x04)
  {
    b_AnchoredFinger = TRUE;
    printf("Func11 Query: Has AnchoredFinger.\r\n");
  }
  else		b_AnchoredFinger = FALSE;

  if(tmp & 0x08)
  {
    b_HasAdjHyst = TRUE;
    printf("Func11 Query: Z hysteresis.\r\n");
  }
  else		b_HasAdjHyst = FALSE;

  if(tmp & 0x10)
  {
    b_HasDribble = TRUE;
    printf("Func11 Query: Supports generation of dribble interrupts.\r\n");
  }
  else		b_HasDribble = FALSE;

  if(tmp & 0x20)
  {
    b_HasBendingCorrection = TRUE;
    printf("Func11 Query: Supports Bending Correction.\r\n");
  }
  else		b_HasBendingCorrection = FALSE;

  if(tmp & 0x40)
  {
    b_HasLargeObjectSuppression = TRUE;
    printf("Func11 Query: Has LargeObjectSuppression(F11_2D_Ctrl58 and F11_2D_Data28 exist).\r\n");
  }
  else		b_HasLargeObjectSuppression = FALSE;

  if(tmp & 0x80)
  {
    b_HasJitterFilter = TRUE;
    printf("Func11 Query: Has Jitter Filter(F11_2D_Query13 and F11_2D_Ctrl73 through F11_2D_Ctrl76.* exist).\r\n");
  }
  else		b_HasJitterFilter = FALSE;

//F11_2D_Query7,F11_2D_Query8 for gesture
//			tmp = I2C_RMI_BufferRead(I2C_Address,F11_2D_Query7);
//			tmp = I2C_RMI_BufferRead(I2C_Address,F11_2D_Query8);

  tmp = I2C_RMI_BufferRead(I2C_Address,F11_2D_Query9);

  if(tmp & 0x01)
  {
    b_HasPen = TRUE;
    printf("Func11 Query: Supports detection of a stylus(pen.F11_2D_Ctrl20 and F11_2D_Ctrl21 exist).\r\n");
  }
  else		b_HasPen = FALSE;

  if(tmp & 0x02)
  {
    b_HasFingerProximity = TRUE;
    printf("Func11 Query: Supports detection of fingers near the sensor(F11_2D_Ctrl22 through F11_2D_Ctrl26 exist).\r\n");
  }
  else		b_HasFingerProximity = FALSE;

  if(tmp & 0x04)
  {
    b_HasLargeObjectSensitivity = TRUE;
    printf("Func11 Query: Supports the palm(large object) detect sensitivity(F11_2D_Ctrl27 exists).\r\n");
  }
  else		b_HasLargeObjectSensitivity = FALSE;

  if(tmp & 0x08)
  {
    b_HasSuppressOnPalmDetect = TRUE;
    printf("Func11 Query: Supports the palm detect suppression feature.\r\n");
  }
  else		b_HasSuppressOnPalmDetect = FALSE;

  if(tmp & 0x10)
  {
    b_HasTwoPenThresholds = TRUE;
    printf("Func11 Query: Has TwoPenThresholds.\r\n");
  }
  else		b_HasTwoPenThresholds = FALSE;

  if(tmp & 0x40)
  {
    b_HasPenHoverDiscrimination = TRUE;
    printf("Func11 Query: Has PenHoverDiscrimination.\r\n");
  }
  else		b_HasPenHoverDiscrimination = FALSE;

  if(tmp & 0x80)
  {
    b_HasNewPenRegisters = TRUE;
    printf("Func11 Query: Has NewPenRegisters.\r\n");
  }
  else		b_HasNewPenRegisters = FALSE;

  tmp = I2C_RMI_BufferRead(I2C_Address,F11_2D_Query11);

  if(tmp & 0x01)
  {
    b_HasZTuning = TRUE;
    printf("Func11 Query: Supports Z tuning(F11_2D_Ctrl29 through F11_2D_Ctrl33).\r\n");
  }
  else		b_HasZTuning = FALSE;

  if(tmp & 0x02)
  {
    b_HasPositionInterpolationTuning = TRUE;
    printf("Func11 Query: Supports configuration of the position-interpolation and post-correction algorithm(F11_2D_Ctrl34 exists).\r\n");
  }
  else		b_HasPositionInterpolationTuning = FALSE;

  if(tmp & 0x04)
  {
    b_HasWTuning = TRUE;
    printf("Func11 Query: Supports Wx and Wy scaling(F11_2D_Ctrl36 through F11_2D_Ctrl39 exist).\r\n");
  }
  else		b_HasWTuning = FALSE;

  if(tmp & 0x08)
  {
    b_HasPitchInfo = TRUE;
    printf("Func11 Query: Supports configurable X and Y pitches of the sensor electrodes feature(F11_2D_Ctrl40 and F11_2D_Ctrl41).\r\n");
  }
  else		b_HasPitchInfo = FALSE;

  if(tmp & 0x10)
  {
    b_HasDefaultFingerWidth = TRUE;
    printf("Func11 Query: Supports configurable default finger width settings for the sensor(F11_2D_Ctrl42 through F11_2D_Ctrl44 exist).\r\n");
  }
  else		b_HasDefaultFingerWidth = FALSE;

  if(tmp & 0x20)
  {
    b_HasSegmentationAggressiveness = TRUE;
    printf("Func11 Query: Supports configurable distinguish multiple objects close together(F11_2D_Ctrl45 exists).\r\n");
  }
  else		b_HasSegmentationAggressiveness = FALSE;

  if(tmp & 0x40)
  {
    b_HasTxRxClip = TRUE;
    printf("Func11 Query: Supports configurable inactive outside borders of the sensor(F11_2D_Ctrl46 through F11_2D_Ctrl49).\r\n");
  }
  else		b_HasTxRxClip = FALSE;

  if(tmp & 0x80)
  {
    b_HasDrummingCorrection = TRUE;
    printf("Func11 Query: Has Drumming Correction.\r\n");
  }
  else		b_HasDrummingCorrection = FALSE;

  tmp = I2C_RMI_BufferRead(I2C_Address,F11_2D_Query12);

  if( tmp && 0x04)
  {
    b_Has8bitW = TRUE;
    printf("Func11 Query: Supports 8-bit W value(F11_2D_Data35.*).\r\n");
  }
  else		b_Has8bitW = FALSE;

  if( tmp && 0x08)
  {
    b_Has2DAdjustableMapping = TRUE;
    printf("Func11 Query: F11_2D_Ctrl77 and F11_2D_Ctrl78 exist and replace F11_2D_Query2 through F11_2D_Query4.\r\n");
    NumberOfXElectrodes = I2C_RMI_BufferRead(I2C_Address,F11_2D_Ctrl77);
    NumberOfYElectrodes = I2C_RMI_BufferRead(I2C_Address,F11_2D_Ctrl78);
    printf("Func11 Query: RX Number(NumberOfXElectrodes):%d,TX Number(NumberOfYElectrodes):%d.\r\n",NumberOfXElectrodes,NumberOfYElectrodes);
  }
  else		b_Has2DAdjustableMapping = FALSE;

  tmp = I2C_RMI_BufferRead(I2C_Address,F11_2D_Query13);
  JitterFilterType = tmp & 0x60;
  JitterAverageWindowSize = tmp & 0x1F;
  printf("Func11 Query: Jitter Filter Type:0x%x,Jitter Average Window Size:0x%x.\r\n",JitterFilterType,JitterAverageWindowSize);


//  F11_2D_Query6 == 0
  if(HasRelMode)
  {
    F11_2D_Query7 = F11_2D_Query5 + 1;
    F11_2D_Query8 = F11_2D_Query7 + 1;
    if(HasQuery9)	F11_2D_Query9 = F11_2D_Query8 + 1;
    F11_2D_Query10	=	0;
  }
  else
  {
    F11_2D_Query7 = 0;
    F11_2D_Query8 = 0;
    if(HasQuery9)	F11_2D_Query9 = F11_2D_Query5 + 1;
    F11_2D_Query10 = 0;
  }
//	F11_2D_Query10 == 0	for Touch Shape

  F11_2D_Query11 =  F11_2D_Query9 + 1;
  F11_2D_Query12 =  F11_2D_Query11 + 1;
  F11_2D_Query13 =  F11_2D_Query12 + 1;


//Func 11 Data for DS4 v3
  if(NumOfFingers <= 4)	 NumOfFingers_Reporting = NumOfFingers+ 1;
  else 					 NumOfFingers_Reporting = 10;

  nfsg = (u8)ceil((double)(NumOfFingers_Reporting + 1)/4);

  if (nfsg == 1)
  {
    F11_2D_Data0_0    = F11_2D_Data0;
    F11_2D_Data0_1	  = 0;
    F11_2D_Data0_2    = 0;
  }
  else if (nfsg == 2)
  {
    F11_2D_Data0_0 =  F11_2D_Data0;
    F11_2D_Data0_1	= F11_2D_Data0_0 + 1;
    F11_2D_Data0_2 = 0;
  }
  else if (nfsg == 3)
  {
    F11_2D_Data0_0 =   F11_2D_Data0;
    F11_2D_Data0_1 =	 F11_2D_Data0_0 + 1;
    F11_2D_Data0_2 =	 F11_2D_Data0_1 + 1;
  }


  switch (NumOfFingers_Reporting)
  {
    case 0x01:
      F11_2D_Data1_0 = F11_2D_Data0_0 + 1;
      F11_2D_Data1_1 = 0;
      F11_2D_Data1_2 = 0;
      F11_2D_Data1_3 = 0;
      F11_2D_Data1_4 = 0;
      F11_2D_Data1_5 = 0;
      F11_2D_Data1_6 = 0;
      F11_2D_Data1_7 = 0;
      F11_2D_Data1_8 = 0;
      F11_2D_Data1_9 = 0;
      break;
    case 0x02:
      F11_2D_Data1_0 = F11_2D_Data0_0 + 1;
      F11_2D_Data1_1 = F11_2D_Data1_0 + Finger_Reg_Size;
      F11_2D_Data1_2 = 0;
      F11_2D_Data1_3 = 0;
      F11_2D_Data1_4 = 0;
      F11_2D_Data1_5 = 0;
      F11_2D_Data1_6 = 0;
      F11_2D_Data1_7 = 0;
      F11_2D_Data1_8 = 0;
      F11_2D_Data1_9 = 0;
      break;
    case 0x03:
      F11_2D_Data1_0 = F11_2D_Data0_0 + 1;
      F11_2D_Data1_1 = F11_2D_Data1_0 + Finger_Reg_Size;
      F11_2D_Data1_2 = F11_2D_Data1_1 + Finger_Reg_Size;
      F11_2D_Data1_3 = 0;
      F11_2D_Data1_4 = 0;
      F11_2D_Data1_5 = 0;
      F11_2D_Data1_6 = 0;
      F11_2D_Data1_7 = 0;
      F11_2D_Data1_8 = 0;
      F11_2D_Data1_9 = 0;
      break;
    case 0x04:
      F11_2D_Data1_0 = F11_2D_Data0_0 + 1;
      F11_2D_Data1_1 = F11_2D_Data1_0 + Finger_Reg_Size;
      F11_2D_Data1_2 = F11_2D_Data1_1 + Finger_Reg_Size;
      F11_2D_Data1_3 = F11_2D_Data1_2 + Finger_Reg_Size;
      F11_2D_Data1_4 = 0;
      F11_2D_Data1_5 = 0;
      F11_2D_Data1_6 = 0;
      F11_2D_Data1_7 = 0;
      F11_2D_Data1_8 = 0;
      F11_2D_Data1_9 = 0;
      break;
    case 0x05:
      F11_2D_Data1_0 = F11_2D_Data0_1 + 1;
      F11_2D_Data1_1 = F11_2D_Data1_0 + Finger_Reg_Size;
      F11_2D_Data1_2 = F11_2D_Data1_1 + Finger_Reg_Size;
      F11_2D_Data1_3 = F11_2D_Data1_2 + Finger_Reg_Size;
      F11_2D_Data1_4 = F11_2D_Data1_3 + Finger_Reg_Size;
      F11_2D_Data1_5 = 0;
      F11_2D_Data1_6 = 0;
      F11_2D_Data1_7 = 0;
      F11_2D_Data1_8 = 0;
      F11_2D_Data1_9 = 0;
      break;
    case 0x06:
      F11_2D_Data1_0 = F11_2D_Data0_1 + 1;
      F11_2D_Data1_1 = F11_2D_Data1_0 + Finger_Reg_Size;
      F11_2D_Data1_2 = F11_2D_Data1_1 + Finger_Reg_Size;
      F11_2D_Data1_3 = F11_2D_Data1_2 + Finger_Reg_Size;
      F11_2D_Data1_4 = F11_2D_Data1_3 + Finger_Reg_Size;
      F11_2D_Data1_5 = F11_2D_Data1_4 + Finger_Reg_Size;
      F11_2D_Data1_6 = 0;
      F11_2D_Data1_7 = 0;
      F11_2D_Data1_8 = 0;
      F11_2D_Data1_9 = 0;
      break;
    case 0x07:
      F11_2D_Data1_0 = F11_2D_Data0_1 + 1;
      F11_2D_Data1_1 = F11_2D_Data1_0 + Finger_Reg_Size;
      F11_2D_Data1_2 = F11_2D_Data1_1 + Finger_Reg_Size;
      F11_2D_Data1_3 = F11_2D_Data1_2 + Finger_Reg_Size;
      F11_2D_Data1_4 = F11_2D_Data1_3 + Finger_Reg_Size;
      F11_2D_Data1_5 = F11_2D_Data1_4 + Finger_Reg_Size;
      F11_2D_Data1_6 = F11_2D_Data1_5 + Finger_Reg_Size;
      F11_2D_Data1_7 = 0;
      F11_2D_Data1_8 = 0;
      F11_2D_Data1_9 = 0;
      break;
    case 0x08:
      F11_2D_Data1_0 = F11_2D_Data0_1 + 1;
      F11_2D_Data1_1 = F11_2D_Data1_0 + Finger_Reg_Size;
      F11_2D_Data1_2 = F11_2D_Data1_1 + Finger_Reg_Size;
      F11_2D_Data1_3 = F11_2D_Data1_2 + Finger_Reg_Size;
      F11_2D_Data1_4 = F11_2D_Data1_3 + Finger_Reg_Size;
      F11_2D_Data1_5 = F11_2D_Data1_4 + Finger_Reg_Size;
      F11_2D_Data1_6 = F11_2D_Data1_5 + Finger_Reg_Size;
      F11_2D_Data1_7 = F11_2D_Data1_6 + Finger_Reg_Size;
      F11_2D_Data1_8 = 0;
      F11_2D_Data1_9 = 0;
      break;
    case 0x09:
      F11_2D_Data1_0 = F11_2D_Data0_2 + 1;
      F11_2D_Data1_1 = F11_2D_Data1_0 + Finger_Reg_Size;
      F11_2D_Data1_2 = F11_2D_Data1_1 + Finger_Reg_Size;
      F11_2D_Data1_3 = F11_2D_Data1_2 + Finger_Reg_Size;
      F11_2D_Data1_4 = F11_2D_Data1_3 + Finger_Reg_Size;
      F11_2D_Data1_5 = F11_2D_Data1_4 + Finger_Reg_Size;
      F11_2D_Data1_6 = F11_2D_Data1_5 + Finger_Reg_Size;
      F11_2D_Data1_7 = F11_2D_Data1_6 + Finger_Reg_Size;
      F11_2D_Data1_8 = F11_2D_Data1_7 + Finger_Reg_Size;;
      F11_2D_Data1_9 = 0;
      break;
    case 0x0A:
      F11_2D_Data1_0 = F11_2D_Data0_2 + 1;
      F11_2D_Data1_1 = F11_2D_Data1_0 + Finger_Reg_Size;
      F11_2D_Data1_2 = F11_2D_Data1_1 + Finger_Reg_Size;
      F11_2D_Data1_3 = F11_2D_Data1_2 + Finger_Reg_Size;
      F11_2D_Data1_4 = F11_2D_Data1_3 + Finger_Reg_Size;
      F11_2D_Data1_5 = F11_2D_Data1_4 + Finger_Reg_Size;
      F11_2D_Data1_6 = F11_2D_Data1_5 + Finger_Reg_Size;
      F11_2D_Data1_7 = F11_2D_Data1_6 + Finger_Reg_Size;
      F11_2D_Data1_8 = F11_2D_Data1_7 + Finger_Reg_Size;
      F11_2D_Data1_9 = F11_2D_Data1_8 + Finger_Reg_Size;
      break;
  }

  F11_2D_Data28 = F11_2D_Data1_9 + Finger_Reg_Size;
  F11_2D_Data29 = F11_2D_Data28 + 1;
  F11_2D_Data30 = F11_2D_Data28 + 2;
  F11_2D_Data31 = F11_2D_Data28 + 3;

//		F11_2D_Data32 = F11_2D_Data28 + 4; //Reserved
//		F11_2D_Data33 = F11_2D_Data28 + 5; //Reserved
//		F11_2D_Data34 = F11_2D_Data28 + 6; //Reserved

  if(b_Has8bitW)
  {
    F11_2D_Data35_0 = F11_2D_Data28 + 4;
    F11_2D_Data35_1 = F11_2D_Data28 + 5;
    F11_2D_Data35_2 = F11_2D_Data28 + 6;
    F11_2D_Data35_3 = F11_2D_Data28 + 7;
    F11_2D_Data35_4 = F11_2D_Data28 + 8;
    F11_2D_Data35_5 = F11_2D_Data28 + 9;
    F11_2D_Data35_6 = F11_2D_Data28 + 10;
    F11_2D_Data35_7 = F11_2D_Data28 + 11;
    F11_2D_Data35_8 = F11_2D_Data28 + 12;
    F11_2D_Data35_9 = F11_2D_Data28 + 13;
  }

//Func11 Control Reg for DS4 V3
  if(HasGestures)
  {
    F11_2D_Ctrl10_19 = F11_2D_Ctrl0_9 + 10;
    F11_2D_Ctrl20 = F11_2D_Ctrl10_19 + 11;
  }
  else
  {
    F11_2D_Ctrl10_19 = 0;
    F11_2D_Ctrl20 = F11_2D_Ctrl0_9 + 10;
  }

//Func11 CMD Reg for DS4 V3

}

void constructFunc01(void)
{
//Func01 Query for DS4 v3
//Query0 ~ 20@#define of rmi.h
  u8 ManufacturerID; //Always 1 for Synaptics device
  u8 tmp;
  u8 tmpBuf[4];
  bool b_HasProductProperties2;
  bool b_HasAdjDozeHoldoff;
  bool b_HasAdjustableDoze;
  bool b_HasFastRead;
  bool b_HasSensorID;
  bool b_HasInitReflash;
  bool b_NonCompliant;
  bool b_CustomMap;
  u8 CustomerFamily,FirmwareRev;
  u8 tmp1,tmp2;
  u16 year;
  char *month;
  u8 date;
  u8 i;
  bool b_HasDS4Queries;
  bool b_hasMaskRevQuery;
  bool b_hasResetQuery;
  bool b_hasPackratQuery;
  bool b_hasPackageIdQuery;
  bool b_hasAttnControl;
  bool b_hasSpiControl;
  bool b_hasI2cControl;
  u8 length;
  u8 ResetpinNum;
  bool b_Pullupenabled;
  bool b_ResetPol;
  bool b_Resetenabled;


  ManufacturerID= I2C_RMI_BufferRead(I2C_Address,F01_RMI_Query0);
  printf("Func01 Query: ManufacturerID:0x%x.(Should be 1 for Synaptics device always.)\r\n",ManufacturerID);

  tmp = I2C_RMI_BufferRead(I2C_Address,F01_RMI_Query1);

  if(tmp & 0x01)
  {
    b_CustomMap = TRUE;
    printf("Func01 Query: Has Custom Map.\r\n");
  }
  else 	b_CustomMap = FALSE;
  if(tmp & 0x02)
  {
    b_NonCompliant = TRUE;
    printf("Func01 Query: Has Non Compliant Register Map.\r\n");
  }
  else 	b_NonCompliant = FALSE;
  if(tmp & 0x04)
  {
    b_HasInitReflash = TRUE;
    printf("Func01 Query: HasInitReflash.\r\n");
  }
  else 	b_HasInitReflash = FALSE;
  if(tmp & 0x08)
  {
    b_HasSensorID = TRUE;
    printf("Func01 Query: Has SensorID,SensorID query register (F01_RMI_Query22) exists.\r\n");
  }
  else 	b_HasSensorID = FALSE;

  if(tmp & 0x10)
  {
    b_HasFastRead = TRUE;
    printf("Func01 Query: Has FastRead.\r\n");
  }
  else 	b_HasFastRead = FALSE;

  if(tmp & 0x20)
  {
    b_HasAdjustableDoze = TRUE;
    printf("Func01 Query: Has Adjustable Doze(F01_RMI_Ctrl2/F01_RMI_Ctrl3 exist).\r\n");
  }
  else 	b_HasAdjustableDoze = FALSE;
  if(tmp & 0x40)
  {
    b_HasAdjDozeHoldoff = TRUE;
    printf("Func01 Query: Has AdjDozeHoldoff(F01_RMI_Ctrl0,bit5 ChargerConnected bit exist)).\r\n");
  }
  else 	b_HasAdjDozeHoldoff = FALSE;
  if(tmp & 0x80)
  {
    b_HasProductProperties2 = TRUE;
    printf("Func01 Query: Has ProductProperties2(F01_RMI_Query42 exists).\r\n");
  }
  else 	b_HasProductProperties2 = FALSE;

  CustomerFamily = I2C_RMI_BufferRead(I2C_Address,F01_RMI_Query2);
  FirmwareRev = I2C_RMI_BufferRead(I2C_Address,F01_RMI_Query3);
  printf("Func01 Query: Customer Family:0x%x, Firmware Revision:0x%x.\r\n",CustomerFamily,FirmwareRev);

  tmp1 = I2C_RMI_BufferRead(I2C_Address,F01_RMI_Query2);
  year = (tmp1 & 0x1F) + 2000;

  switch( ((tmp1 & 0xE0) >> 5) + (((tmp2) &0x01) >> 3) )
  {
    case 1:
      month = "January";
      break;
    case 2:
      month = "February";
      break;
    case 3:
      month = "March";
      break;
    case 4:
      month = "April";
      break;
    case 5:
      month = "May";
      break;
    case 6:
      month = "June";
      break;
    case 7:
      month = "July";
      break;
    case 8:
      month = "August";
      break;
    case 9:
      month = "September";
      break;
    case 10:
      month = "October";
      break;
    case 11:
      month = "September";
      break;
    case 12:
      month = "December";
      break;
    default:
      month = "Unknown";
      break;
  }

  tmp2 = I2C_RMI_BufferRead(I2C_Address,F01_RMI_Query3);
  date = (tmp2 & 0x3E) >> 1;
  printf("Func01 Query: Manufacture year:0x%d, Month:%s, date:%d.\r\n",year,month,date);

  printf("Func01 Query: Wafer Lot ID 0:0x%4x,Wafer Lot ID 1:0x%4x, Wafer Lot ID 2:0x%x.\r\n",I2C_RMI_BufferRead(I2C_Address,F01_RMI_Query7)<< 8 + I2C_RMI_BufferRead(I2C_Address,F01_RMI_Query6),I2C_RMI_BufferRead(I2C_Address,F01_RMI_Query9)<< 8 +I2C_RMI_BufferRead(I2C_Address,F01_RMI_Query8),I2C_RMI_BufferRead(I2C_Address,F01_RMI_Query10));

//	readRMI(F01_RMI_Query11,ProductID,10);
  for(i=0; i<10; i++) ProductID[i]= I2C_RMI_BufferRead(I2C_Address,F01_RMI_Query11 + i);
  printf("Func01 Query: ProductID:%s.\r\n",ProductID);

  tmp = I2C_RMI_BufferRead(I2C_Address,F01_RMI_QUERY42);
  length = I2C_RMI_BufferRead(I2C_Address,F01_RMI_QUERY43_0) & 0x0F;

  if(tmp & 0x01)
  {
    b_HasDS4Queries = TRUE;
    printf("Func01 Query: Has DS4Queries.\r\n");
  }
  else 	b_HasDS4Queries = FALSE;

  tmp = I2C_RMI_BufferRead(I2C_Address,F01_RMI_QUERY43_1);
  if(tmp & 0x01)
  {
    b_hasPackageIdQuery = TRUE;
    printf("Func01 Query: Has PackageIdQuery.\r\n");

    //Package_ID
    readRMI(F01_RMI_Query17,tmpBuf,4);
    Package_ID = tmpBuf[0] + (tmpBuf[1] << 8);
    printf("Func01 Query: Package_ID:%d.\r\n",Package_ID);
    //Package_ID_Rev
    Package_ID_Rev = tmpBuf[2] + (tmpBuf[3] << 8);
    printf("Func01 Query: Package_ID_Rev:%d.\r\n",Package_ID_Rev);
  }
  else 	b_hasPackageIdQuery = FALSE;

  if(tmp & 0x02)
  {
    b_hasPackratQuery = TRUE;
    printf("Func01 Query: Has Non Compliant Register Map.\r\n");

    //Packrat_Num
    readRMI(F01_RMI_Query18,tmpBuf,3);
    Packrat_Num = tmpBuf[0] + (tmpBuf[1] << 8) + (tmpBuf[2] << 16);
    printf("Func01 Query: F01_RMI_Query18:0x%x , Packrat_Num: %u.\r\n",F01_RMI_Query18,Packrat_Num);
  }
  else 	b_hasPackratQuery = FALSE;
  if(tmp & 0x04)
  {
    b_hasResetQuery = TRUE;
    printf("Func01 Query: Has ResetQuery(F01_RMI_Query44 exists).\r\n");
  }
  else 	b_hasResetQuery = FALSE;
  if(tmp & 0x08)
  {
    b_hasMaskRevQuery = TRUE;
    printf("Func01 Query: Has MaskRevQuery.\r\n");
  }
  else 	b_hasMaskRevQuery = FALSE;

  tmp = I2C_RMI_BufferRead(I2C_Address,F01_RMI_QUERY43_2);

  if(tmp & 0x01)
  {
    b_hasI2cControl = TRUE;
    printf("Func01 Query: Has I2cControl(F01_RMI_Ctrl6 exists).\r\n");
  }
  else	b_hasI2cControl = FALSE;

  if(tmp & 0x02)
  {
    b_hasSpiControl = TRUE;
    printf("Func01 Query: Has SpiControl(F01_RMI_Ctrl7 exists).\r\n");

  }
  else	b_hasSpiControl = FALSE;

  if(tmp & 0x04)
  {
    b_hasAttnControl = TRUE;
    printf("Func01 Query: Has AttnControl(F01_RMI_Ctrl8 exists).\r\n");

  }
  else	b_hasAttnControl = FALSE;

  if(b_hasResetQuery)
  {
    tmp = I2C_RMI_BufferRead(I2C_Address,F01_RMI_QUERY44);

    ResetpinNum = tmp & 0x0F;

    if(tmp & 0x01)
    {
      b_Resetenabled = TRUE;
      printf("Func01 Query: Hardware reset pin functionality has been enabled.\r\n");
    }
    else
    {
      b_Resetenabled = FALSE;
    }

    if(tmp & 0x02)
    {
      b_ResetPol = TRUE;
      printf("Func01 Query: Reset polarity is active high.\r\n");

    }
    else
    {
      b_ResetPol = FALSE;
      printf("Func01 Query: Reset polarity is active low.\r\n");
    }

    if(tmp & 0x04)
    {
      b_Pullupenabled = TRUE;
      printf("Func01 Query: Built-in weak pull up has been enabled.\r\n");

    }
    else
    {
      b_Pullupenabled = FALSE;
      printf("Func01 Query: no pull-up is present.\r\n");
    }
  }


//Func01 Data for DS4 v3
//Data1@#define of rmi.h

//Func01 Control Reg for DS4 V3

//Func01 CMD Reg for DS4 V3

}


void constructFunc34(void)
{
//Func34 Query for DS4 v3
//Query0 ~ 8@#define of rmi.h
  char BootloaderID[2];
  bool b_unlocked;
  bool b_HasConfigID;
  u16 Img_BlockSize,Img_BlockCount,Config_BlockCount;

  BootloaderID[0]= I2C_RMI_BufferRead(I2C_Address,F34_FLASH_QUERY0);
  BootloaderID[1]= I2C_RMI_BufferRead(I2C_Address,F34_FLASH_QUERY1);

  printf("Func34 Query: Bootloader ID: %s\r\n",BootloaderID);

  if(I2C_RMI_BufferRead(I2C_Address,F34_FLASH_QUERY2) & 0x02) b_unlocked = TRUE;
  else																												b_unlocked = FALSE;
  if(b_unlocked)	printf("Func34 Query: unlocked state.\r\n");

  if(I2C_RMI_BufferRead(I2C_Address,F34_FLASH_QUERY2) & 0x04) b_HasConfigID = TRUE;
  else																												b_HasConfigID = FALSE;
  if(b_HasConfigID)	printf("Func34 Query: HasConfigID.\r\n");

  Img_BlockSize  		= ((u16)I2C_RMI_BufferRead(I2C_Address,F34_FLASH_QUERY4) << 8) + I2C_RMI_BufferRead(I2C_Address,F34_FLASH_QUERY3);
  Img_BlockCount 		= ((u16)I2C_RMI_BufferRead(I2C_Address,F34_FLASH_QUERY6) << 8) + I2C_RMI_BufferRead(I2C_Address,F34_FLASH_QUERY5);
  Config_BlockCount = ((u16)I2C_RMI_BufferRead(I2C_Address,F34_FLASH_QUERY8) << 8) + I2C_RMI_BufferRead(I2C_Address,F34_FLASH_QUERY7);
  printf("Func34 Query: Image Block size:%u, Block Count:%u, Configuration Block Count:%u.\r\n",Img_BlockSize,Img_BlockCount,Config_BlockCount);


//Func34 Data for DS4 v3
//Data0 ~ 3 @#define of rmi.h

//Func34 Control Reg for DS4 V3

//Func34 CMD Reg for DS4 V3
//None
}

void constructFunc54(void)
{
  u8 tmp;
  bool b_HasImage16;
  bool b_HasImage8;
  bool b_HasBaseLine;
  u16 ClockRate;
  bool b_HasPixelTouchThresholdTuning;
  bool b_HasRelaxationCtrl;
  bool b_HasOneByteReportRateReporting;
  bool b_HasTwoByteReportRateReporting;
  bool b_HasLowPowerCtrl;
  bool b_HasFirmwareNoiseMitigation;
  bool b_HasSenseFrequencyControl;
  bool b_HasInterferenceMetric;
  bool b_HasArbitrarySensorAssignment;
  u8 AxisCompensationMode;
  bool b_HasPerFrequencyNoiseControl;
  bool b_HasEdgeCompensation;
  bool b_HasPixelThresholdHysteresis;
  bool b_HasCMNCapScaleFactor;
  bool b_HasCMNRemoval;
  bool b_HasIIRFilter;
  bool b_Has0DAcquisitionCtrl;
  bool b_Has0DRelaxationCtrl;
  bool b_HasVarianceMetric;
  bool b_HasCDM4;
  bool b_HasMMStateMitigation;
  bool b_HasForceFastRelaxation;
  u8 Maxnumofsensingfrequencies;
  u8 Burstspercluster;

//Change to Page1
  I2C_RMI_BufferWrite(I2C_Address,Page_Select_register,1);

//Func54 Query for DS4 v3
//Query0 ~ 13@#define of rmi.h
  printf("Func54 Query: Available receiver Electrode Count:%u, available transmitter Electrode Count:%u.\r\n",I2C_RMI_BufferRead(I2C_Address,F54_Query0),I2C_RMI_BufferRead(I2C_Address,F54_Query1));

  tmp = I2C_RMI_BufferRead(I2C_Address,F54_Query2);
  if(tmp & 0x04)
  {
    b_HasBaseLine = TRUE;
    printf("Func54 Query: Supports background capacitance baseline reporting.\r\n");
  }
  else		b_HasBaseLine = FALSE;

  if(tmp & 0x08)
  {
    b_HasImage8 = TRUE;
    printf("Func54 Query: Supports reporting 8-bit capacitive image data.\r\n");
  }
  else		b_HasImage8 = FALSE;

  if(tmp & 0x40)
  {
    b_HasImage16 = TRUE;
    printf("Func54 Query: Supports reporting 16-bit capacitive image data.\r\n");
  }
  else		b_HasImage16 = FALSE;

  ClockRate = (((u16)I2C_RMI_BufferRead(I2C_Address,F54_Query3_1) << 8) + I2C_RMI_BufferRead(I2C_Address,F54_Query3_0) ) * 10;
  printf("Func54 Query: Clock rate:%u kHz.\r\n",ClockRate);

  printf("Func54 Query: Analog Hardware Family:0x%x.\r\n",I2C_RMI_BufferRead(I2C_Address,F54_Query4));

  if(I2C_RMI_BufferRead(I2C_Address,F54_Query5) & 0x01)
  {
    b_HasPixelTouchThresholdTuning = TRUE;
    printf("Func54 Query: Has Pixel TouchThreshold Tuning.\r\n");
  }
  else		b_HasPixelTouchThresholdTuning = FALSE;

  tmp = I2C_RMI_BufferRead(I2C_Address,F54_Query6);

  if(tmp & 0x01)
  {
    b_HasArbitrarySensorAssignment = TRUE;
    printf("Func54 Query: Supports mechanism for specifying the number and arrangement of transmitter and receiver electrodes.\r\n");
  }
  else		b_HasArbitrarySensorAssignment = FALSE;

  if(tmp & 0x02)
  {
    b_HasInterferenceMetric = TRUE;
    printf("Func54 Query: Supports noise amount presence.\r\n");
  }
  else		b_HasInterferenceMetric = FALSE;

  if(tmp & 0x04)
  {
    b_HasSenseFrequencyControl = TRUE;
    printf("Func54 Query: Supports changing the sensing frequency in order to avoid narrow-band noise sources.\r\n");
  }
  else		b_HasSenseFrequencyControl = FALSE;

  if(tmp & 0x08)
  {
    b_HasFirmwareNoiseMitigation = TRUE;
    printf("Func54 Query: Supports firmware-based mechanism to mitigate the effects of environmental noise.\r\n");
  }
  else		b_HasFirmwareNoiseMitigation = FALSE;

  if(tmp & 0x10)
  {
    b_HasLowPowerCtrl = TRUE;
    printf("Func54 Query: Supports LowPower Control.\r\n");
  }
  else		b_HasLowPowerCtrl = FALSE;

  if(tmp & 0x20)
  {
    b_HasTwoByteReportRateReporting = TRUE;
    printf("Func54 Query: Supports TwoByte ReportRate(16-Bit F54_AD_Data7.0 and F54_AD_Data7.1 exist).\r\n");
  }
  else		b_HasTwoByteReportRateReporting = FALSE;

  if(tmp & 0x40)
  {
    b_HasOneByteReportRateReporting = TRUE;
    printf("Func54 Query: Supports OneByte ReportRate(8-Bit F54_AD_Data7.0 exists only).\r\n");
  }
  else		b_HasOneByteReportRateReporting = FALSE;

  if(tmp & 0x80)
  {
    b_HasRelaxationCtrl = TRUE;
    printf("Func54 Query: Supports compensate for thermal effects in the system(F54_AD_Ctrl12 and F54_AD_Ctrl13 exist).\r\n");
  }
  else		b_HasRelaxationCtrl = FALSE;

  AxisCompensationMode = I2C_RMI_BufferRead(I2C_Address,F54_Query7) & 0x03;
  switch(AxisCompensationMode)
  {
    case 0:
      printf("Func54 Query: No curve compensation.\r\n");
      break;
    case 1:
      printf("Func54 Query: Single-axis curve compensation.\r\n");
      break;
    case 2:
      printf("Func54 Query: Dual-axis curve compensation.\r\n");
      break;
    case 3:
      printf("Func54 Query: Reserved for curved lens compensation.\r\n");
      break;
  }

  tmp = I2C_RMI_BufferRead(I2C_Address,F54_Query8);

  if(tmp & 0x02)
  {
    b_HasIIRFilter = TRUE;
    printf("Func54 Query: Supports IIR filter that is applied to every sampled image before it is processed.\r\n");
  }
  else		b_HasIIRFilter = FALSE;

  if(tmp & 0x04)
  {
    b_HasCMNRemoval = TRUE;
    printf("Func54 Query: Supports remove common-mode noise.\r\n");
  }
  else		b_HasCMNRemoval = FALSE;

  if(tmp & 0x08)
  {
    b_HasCMNCapScaleFactor = TRUE;
    printf("Func54 Query: Supports adjustable Common Mode Noise cap.\r\n");
  }
  else		b_HasCMNCapScaleFactor = FALSE;

  if(tmp & 0x10)
  {
    b_HasPixelThresholdHysteresis = TRUE;
    printf("Func54 Query: Supports Pixel Threshold hysteresis.\r\n");
  }
  else		b_HasPixelThresholdHysteresis = FALSE;

  if(tmp & 0x20)
  {
    b_HasEdgeCompensation = TRUE;
    printf("Func54 Query: Supports the mechanism for boosting the capacitive signal on the edges of the sensor.\r\n");
  }
  else		b_HasEdgeCompensation = FALSE;

  if(tmp & 0x40)
  {
    b_HasPerFrequencyNoiseControl = TRUE;
    printf("Func54 Query: Supports Noise Control(F54_AD_Ctrl38.*, F54_AD_Ctrl39.*, and F54_AD_Ctrl40.* exist).\r\n");
  }
  else		b_HasPerFrequencyNoiseControl = FALSE;

  tmp = I2C_RMI_BufferRead(I2C_Address,F54_Query9);

  if(tmp & 0x01)
  {
    b_HasForceFastRelaxation = TRUE;
    printf("Func54 Query: Supports ForceFastRelaxation (F54_AD_Ctrl0, bit 2) exists.\r\n");
  }
  else		b_HasForceFastRelaxation = FALSE;

  if(tmp & 0x02)
  {
    b_HasMMStateMitigation = TRUE;
    printf("Func54 Query: Supports MultiMetricStateMachine (F54_AD_Ctrl43 through F54_AD_Ctrl54, F54_AD_Data9, and F54_AD_Data10 exist).\r\n");
  }
  else		b_HasMMStateMitigation = FALSE;

  if(tmp & 0x04)
  {
    b_HasCDM4 = TRUE;
    printf("Func54 Query: Supports CDM4.\r\n");
  }
  else		b_HasCDM4 = FALSE;

  if(tmp & 0x08)
  {
    b_HasVarianceMetric = TRUE;
    printf("Func54 Query: Supports Variance Metric.\r\n");
  }
  else		b_HasVarianceMetric = FALSE;

  if(tmp & 0x10)
  {
    b_Has0DRelaxationCtrl = TRUE;
    printf("Func54 Query: Supports 0D Relaxation Ctrl.\r\n");
  }
  else		b_Has0DRelaxationCtrl = FALSE;

  if(tmp & 0x20)
  {
    b_Has0DAcquisitionCtrl = TRUE;
    printf("Func54 Query: Supports 0D Acquisition Ctrl.\r\n");
  }
  else		b_Has0DAcquisitionCtrl = FALSE;

  Maxnumofsensingfrequencies = I2C_RMI_BufferRead(I2C_Address,F54_Query12) & 0x0F;
  Burstspercluster = I2C_RMI_BufferRead(I2C_Address,F54_Query13) & 0x0F;
  printf("Func54 Query: Max num of sensing frequencies: %d, Bursts per cluster: %d.\r\n",Maxnumofsensingfrequencies,Burstspercluster);


//Func54 Data for DS4 v3
//Data0 ~ 3 @#define of rmi.h

//Func54 Control Reg for DS4 V3
  if(Package_ID == 0x0c80)    //S3200
  {
    F54_ANALOG_CTRL15_18 = F54_Control_Base + 36;
    F54_ANALOG_CTRL16_0 = F54_ANALOG_CTRL15_18 + 1;

    F54_ANALOG_CTRL17 = F54_ANALOG_CTRL16_10 + 1;
    F54_ANALOG_CTRL36_18 = F54_ANALOG_CTRL36_17 + 1	;

    F54_ANALOG_CTRL38 = F54_ANALOG_CTRL36_18 + 1;
  }
  else if(Package_ID == 0x0c81)   		//S3201
  {
    F54_ANALOG_CTRL16_0 = F54_ANALOG_CTRL15_17 + 1;

    F54_ANALOG_CTRL16_11 = F54_ANALOG_CTRL16_0 + 11;
    F54_ANALOG_CTRL17 = F54_ANALOG_CTRL16_11 + 1;

    F54_ANALOG_CTRL38 = F54_ANALOG_CTRL36_17 + 1;

  }
  else if(Package_ID == 0x0c82)   		//S3202
  {
    F54_ANALOG_CTRL15_18 = F54_Control_Base + 35;
    F54_ANALOG_CTRL15_19 = F54_Control_Base + 36;
    F54_ANALOG_CTRL15_20 = F54_Control_Base + 37;
    F54_ANALOG_CTRL15_21 = F54_Control_Base + 38;
    F54_ANALOG_CTRL15_22 = F54_Control_Base + 39;
    F54_ANALOG_CTRL15_23 = F54_Control_Base + 40;
    F54_ANALOG_CTRL15_24 = F54_Control_Base + 41;
    F54_ANALOG_CTRL15_25 = F54_Control_Base + 42;
    F54_ANALOG_CTRL15_26 = F54_Control_Base + 43;
    F54_ANALOG_CTRL15_27 = F54_Control_Base + 44;

    F54_ANALOG_CTRL16_0 = F54_ANALOG_CTRL15_27 + 1;

    F54_ANALOG_CTRL16_11 = F54_ANALOG_CTRL16_0 + 11;
    F54_ANALOG_CTRL16_12 = F54_ANALOG_CTRL16_0 + 12;
    F54_ANALOG_CTRL16_13 = F54_ANALOG_CTRL16_0 + 13;
    F54_ANALOG_CTRL16_14 = F54_ANALOG_CTRL16_0 + 14;
    F54_ANALOG_CTRL16_15 = F54_ANALOG_CTRL16_0 + 15;

    F54_ANALOG_CTRL17 = F54_ANALOG_CTRL16_15 + 1;

    F54_ANALOG_CTRL36_18 = F54_ANALOG_CTRL36_17 + 1;
    F54_ANALOG_CTRL36_19 = F54_ANALOG_CTRL36_18 + 1;
    F54_ANALOG_CTRL36_20 = F54_ANALOG_CTRL36_19 + 1;
    F54_ANALOG_CTRL36_21 = F54_ANALOG_CTRL36_20 + 1;
    F54_ANALOG_CTRL36_22 = F54_ANALOG_CTRL36_21 + 1;
    F54_ANALOG_CTRL36_23 = F54_ANALOG_CTRL36_22 + 1;
    F54_ANALOG_CTRL36_24 = F54_ANALOG_CTRL36_23 + 1;
    F54_ANALOG_CTRL36_25 = F54_ANALOG_CTRL36_24 + 1;
    F54_ANALOG_CTRL36_26 = F54_ANALOG_CTRL36_25 + 1;
    F54_ANALOG_CTRL36_27 = F54_ANALOG_CTRL36_26 + 1;

    F54_ANALOG_CTRL38 =F54_ANALOG_CTRL36_27 + 1;

  }
  else if (Package_ID == 0x0c83)   		//S3203
  {
    F54_ANALOG_CTRL15_18 = F54_Control_Base + 36;
    F54_ANALOG_CTRL15_19 = F54_Control_Base + 37;
    F54_ANALOG_CTRL15_20 = F54_Control_Base + 38;
    F54_ANALOG_CTRL15_21 = F54_Control_Base + 39;
    F54_ANALOG_CTRL15_22 = F54_Control_Base + 40;

    F54_ANALOG_CTRL16_0 = F54_ANALOG_CTRL15_22 + 1;
    F54_ANALOG_CTRL16_11 = F54_ANALOG_CTRL16_0 + 11;
    F54_ANALOG_CTRL16_12 = F54_ANALOG_CTRL16_0 + 12;

    F54_ANALOG_CTRL17 = F54_ANALOG_CTRL16_12 + 1;

    F54_ANALOG_CTRL36_18 = F54_ANALOG_CTRL36_17 + 1;
    F54_ANALOG_CTRL36_19 = F54_ANALOG_CTRL36_18 + 1;
    F54_ANALOG_CTRL36_20 = F54_ANALOG_CTRL36_18 + 1;
    F54_ANALOG_CTRL36_21 = F54_ANALOG_CTRL36_18 + 1;
    F54_ANALOG_CTRL36_22 = F54_ANALOG_CTRL36_18 + 1;

    F54_ANALOG_CTRL38 = F54_ANALOG_CTRL36_22 + 1;
  }
  else if (Package_ID == 0x1c85)   		//S7301
  {
    F54_ANALOG_CTRL15_18 = F54_Control_Base + 36;
    F54_ANALOG_CTRL15_19 = F54_Control_Base + 37;
    F54_ANALOG_CTRL15_20 = F54_Control_Base + 38;
    F54_ANALOG_CTRL15_21 = F54_Control_Base + 39;
    F54_ANALOG_CTRL15_22 = F54_Control_Base + 40;
    F54_ANALOG_CTRL15_23 = F54_Control_Base + 41;
    F54_ANALOG_CTRL15_24 = F54_Control_Base + 42;
    F54_ANALOG_CTRL15_25 = F54_Control_Base + 43;
    F54_ANALOG_CTRL15_26 = F54_Control_Base + 44;
    F54_ANALOG_CTRL15_27 = F54_Control_Base + 45;

    F54_ANALOG_CTRL15_28 = F54_Control_Base + 45;
    F54_ANALOG_CTRL15_29 = F54_Control_Base + 46;
    F54_ANALOG_CTRL15_30 = F54_Control_Base + 47;
    F54_ANALOG_CTRL15_31 = F54_Control_Base + 48;
    F54_ANALOG_CTRL15_32 = F54_Control_Base + 49;
    F54_ANALOG_CTRL15_33 = F54_Control_Base + 50;
    F54_ANALOG_CTRL15_34 = F54_Control_Base + 51;
    F54_ANALOG_CTRL15_35 = F54_Control_Base + 52;
    F54_ANALOG_CTRL15_36 = F54_Control_Base + 53;
    F54_ANALOG_CTRL15_37 = F54_Control_Base + 54;
    F54_ANALOG_CTRL15_38 = F54_Control_Base + 55;
    F54_ANALOG_CTRL15_39 = F54_Control_Base + 56;
    F54_ANALOG_CTRL15_40 = F54_Control_Base + 57;
    F54_ANALOG_CTRL15_41 = F54_Control_Base + 58;
    F54_ANALOG_CTRL15_42 = F54_Control_Base + 59;
    F54_ANALOG_CTRL15_43 = F54_Control_Base + 60;

    F54_ANALOG_CTRL16_0 = F54_ANALOG_CTRL15_43 + 1;

    F54_ANALOG_CTRL16_11 = F54_ANALOG_CTRL16_0 + 11;
    F54_ANALOG_CTRL16_12 = F54_ANALOG_CTRL16_0 + 12;
    F54_ANALOG_CTRL16_13 = F54_ANALOG_CTRL16_0 + 13;
    F54_ANALOG_CTRL16_14 = F54_ANALOG_CTRL16_0 + 14;
    F54_ANALOG_CTRL16_15 = F54_ANALOG_CTRL16_0 + 15;
    F54_ANALOG_CTRL16_16 = F54_ANALOG_CTRL16_0 + 16;
    F54_ANALOG_CTRL16_17 = F54_ANALOG_CTRL16_0 + 17;
    F54_ANALOG_CTRL16_18 = F54_ANALOG_CTRL16_0 + 18;
    F54_ANALOG_CTRL16_19 = F54_ANALOG_CTRL16_0 + 19;
    F54_ANALOG_CTRL16_20 = F54_ANALOG_CTRL16_0 + 20;
    F54_ANALOG_CTRL16_21 = F54_ANALOG_CTRL16_0 + 21;
    F54_ANALOG_CTRL16_22 = F54_ANALOG_CTRL16_0 + 22;
    F54_ANALOG_CTRL16_23 = F54_ANALOG_CTRL16_0 + 23;
    F54_ANALOG_CTRL16_24 = F54_ANALOG_CTRL16_0 + 24;
    F54_ANALOG_CTRL16_25 = F54_ANALOG_CTRL16_0 + 25;
    F54_ANALOG_CTRL16_26 = F54_ANALOG_CTRL16_0 + 26;

    F54_ANALOG_CTRL17 = F54_ANALOG_CTRL16_26 + 1;

    F54_ANALOG_CTRL36_18 = F54_ANALOG_CTRL36_17 + 1;
    F54_ANALOG_CTRL36_19 = F54_ANALOG_CTRL36_18 + 1;
    F54_ANALOG_CTRL36_20 = F54_ANALOG_CTRL36_19 + 1;
    F54_ANALOG_CTRL36_21 = F54_ANALOG_CTRL36_20 + 1;
    F54_ANALOG_CTRL36_22 = F54_ANALOG_CTRL36_21 + 1;
    F54_ANALOG_CTRL36_23 = F54_ANALOG_CTRL36_22 + 1;
    F54_ANALOG_CTRL36_24 = F54_ANALOG_CTRL36_23 + 1;
    F54_ANALOG_CTRL36_25 = F54_ANALOG_CTRL36_24 + 1;
    F54_ANALOG_CTRL36_26 = F54_ANALOG_CTRL36_25 + 1;
    F54_ANALOG_CTRL36_27 = F54_ANALOG_CTRL36_26 + 1;

    F54_ANALOG_CTRL36_28 = F54_ANALOG_CTRL36_27 + 1;
    F54_ANALOG_CTRL36_29 = F54_ANALOG_CTRL36_28 + 1;
    F54_ANALOG_CTRL36_30 = F54_ANALOG_CTRL36_29 + 1;
    F54_ANALOG_CTRL36_31 = F54_ANALOG_CTRL36_30 + 1;
    F54_ANALOG_CTRL36_32 = F54_ANALOG_CTRL36_31 + 1;
    F54_ANALOG_CTRL36_33 = F54_ANALOG_CTRL36_32 + 1;
    F54_ANALOG_CTRL36_34 = F54_ANALOG_CTRL36_33 + 1;
    F54_ANALOG_CTRL36_35 = F54_ANALOG_CTRL36_34 + 1;
    F54_ANALOG_CTRL36_36 = F54_ANALOG_CTRL36_35 + 1;
    F54_ANALOG_CTRL36_37 = F54_ANALOG_CTRL36_36 + 1;
    F54_ANALOG_CTRL36_38 = F54_ANALOG_CTRL36_37 + 1;
    F54_ANALOG_CTRL36_39 = F54_ANALOG_CTRL36_38 + 1;
    F54_ANALOG_CTRL36_40 = F54_ANALOG_CTRL36_39 + 1;
    F54_ANALOG_CTRL36_41 = F54_ANALOG_CTRL36_40 + 1;
    F54_ANALOG_CTRL36_42 = F54_ANALOG_CTRL36_41 + 1;
    F54_ANALOG_CTRL36_43 = F54_ANALOG_CTRL36_42 + 1;

    F54_ANALOG_CTRL38 = F54_ANALOG_CTRL36_43 + 1;
  }
  else if (Package_ID == 0x1c84)   			//S7300
  {
    F54_ANALOG_CTRL15_18 = F54_Control_Base + 36;
    F54_ANALOG_CTRL15_19 = F54_Control_Base + 37;
    F54_ANALOG_CTRL15_20 = F54_Control_Base + 38;
    F54_ANALOG_CTRL15_21 = F54_Control_Base + 39;
    F54_ANALOG_CTRL15_22 = F54_Control_Base + 40;
    F54_ANALOG_CTRL15_23 = F54_Control_Base + 41;
    F54_ANALOG_CTRL15_24 = F54_Control_Base + 42;
    F54_ANALOG_CTRL15_25 = F54_Control_Base + 43;
    F54_ANALOG_CTRL15_26 = F54_Control_Base + 44;
    F54_ANALOG_CTRL15_27 = F54_Control_Base + 45;

    F54_ANALOG_CTRL15_28 = F54_Control_Base + 45;
    F54_ANALOG_CTRL15_29 = F54_Control_Base + 46;
    F54_ANALOG_CTRL15_30 = F54_Control_Base + 47;
    F54_ANALOG_CTRL15_31 = F54_Control_Base + 48;
    F54_ANALOG_CTRL15_32 = F54_Control_Base + 49;
    F54_ANALOG_CTRL15_33 = F54_Control_Base + 50;
    F54_ANALOG_CTRL15_34 = F54_Control_Base + 51;
    F54_ANALOG_CTRL15_35 = F54_Control_Base + 52;
    F54_ANALOG_CTRL15_36 = F54_Control_Base + 53;
    F54_ANALOG_CTRL15_37 = F54_Control_Base + 54;
    F54_ANALOG_CTRL15_38 = F54_Control_Base + 55;
    F54_ANALOG_CTRL15_39 = F54_Control_Base + 56;
    F54_ANALOG_CTRL15_40 = F54_Control_Base + 57;
    F54_ANALOG_CTRL15_41 = F54_Control_Base + 58;
    F54_ANALOG_CTRL15_42 = F54_Control_Base + 59;
    F54_ANALOG_CTRL15_43 = F54_Control_Base + 60;

    F54_ANALOG_CTRL15_44 = F54_Control_Base + 61;
    F54_ANALOG_CTRL15_45 = F54_Control_Base + 62;
    F54_ANALOG_CTRL15_46 = F54_Control_Base + 63;

    F54_ANALOG_CTRL16_0 = F54_ANALOG_CTRL15_46 + 1;

    F54_ANALOG_CTRL16_11 = F54_ANALOG_CTRL16_0 + 11;
    F54_ANALOG_CTRL16_12 = F54_ANALOG_CTRL16_0 + 12;
    F54_ANALOG_CTRL16_13 = F54_ANALOG_CTRL16_0 + 13;
    F54_ANALOG_CTRL16_14 = F54_ANALOG_CTRL16_0 + 14;
    F54_ANALOG_CTRL16_15 = F54_ANALOG_CTRL16_0 + 15;
    F54_ANALOG_CTRL16_16 = F54_ANALOG_CTRL16_0 + 16;
    F54_ANALOG_CTRL16_17 = F54_ANALOG_CTRL16_0 + 17;
    F54_ANALOG_CTRL16_18 = F54_ANALOG_CTRL16_0 + 18;
    F54_ANALOG_CTRL16_19 = F54_ANALOG_CTRL16_0 + 19;
    F54_ANALOG_CTRL16_20 = F54_ANALOG_CTRL16_0 + 20;
    F54_ANALOG_CTRL16_21 = F54_ANALOG_CTRL16_0 + 21;
    F54_ANALOG_CTRL16_22 = F54_ANALOG_CTRL16_0 + 22;
    F54_ANALOG_CTRL16_23 = F54_ANALOG_CTRL16_0 + 23;
    F54_ANALOG_CTRL16_24 = F54_ANALOG_CTRL16_0 + 24;
    F54_ANALOG_CTRL16_25 = F54_ANALOG_CTRL16_0 + 25;
    F54_ANALOG_CTRL16_26 = F54_ANALOG_CTRL16_0 + 26;
    F54_ANALOG_CTRL16_27 = F54_ANALOG_CTRL16_0 + 27;
    F54_ANALOG_CTRL16_28 = F54_ANALOG_CTRL16_0 + 28;
    F54_ANALOG_CTRL16_29 = F54_ANALOG_CTRL16_0 + 29;

    F54_ANALOG_CTRL17 = F54_ANALOG_CTRL16_29 + 1;

    F54_ANALOG_CTRL36_18 = F54_ANALOG_CTRL36_17 + 1;
    F54_ANALOG_CTRL36_19 = F54_ANALOG_CTRL36_18 + 1;
    F54_ANALOG_CTRL36_20 = F54_ANALOG_CTRL36_19 + 1;
    F54_ANALOG_CTRL36_21 = F54_ANALOG_CTRL36_20 + 1;
    F54_ANALOG_CTRL36_22 = F54_ANALOG_CTRL36_21 + 1;
    F54_ANALOG_CTRL36_23 = F54_ANALOG_CTRL36_22 + 1;
    F54_ANALOG_CTRL36_24 = F54_ANALOG_CTRL36_23 + 1;
    F54_ANALOG_CTRL36_25 = F54_ANALOG_CTRL36_24 + 1;
    F54_ANALOG_CTRL36_26 = F54_ANALOG_CTRL36_25 + 1;
    F54_ANALOG_CTRL36_27 = F54_ANALOG_CTRL36_26 + 1;

    F54_ANALOG_CTRL36_28 = F54_ANALOG_CTRL36_27 + 1;
    F54_ANALOG_CTRL36_29 = F54_ANALOG_CTRL36_28 + 1;
    F54_ANALOG_CTRL36_30 = F54_ANALOG_CTRL36_29 + 1;
    F54_ANALOG_CTRL36_31 = F54_ANALOG_CTRL36_30 + 1;
    F54_ANALOG_CTRL36_32 = F54_ANALOG_CTRL36_31 + 1;
    F54_ANALOG_CTRL36_33 = F54_ANALOG_CTRL36_32 + 1;
    F54_ANALOG_CTRL36_34 = F54_ANALOG_CTRL36_33 + 1;
    F54_ANALOG_CTRL36_35 = F54_ANALOG_CTRL36_34 + 1;
    F54_ANALOG_CTRL36_36 = F54_ANALOG_CTRL36_35 + 1;
    F54_ANALOG_CTRL36_37 = F54_ANALOG_CTRL36_36 + 1;
    F54_ANALOG_CTRL36_38 = F54_ANALOG_CTRL36_37 + 1;
    F54_ANALOG_CTRL36_39 = F54_ANALOG_CTRL36_38 + 1;
    F54_ANALOG_CTRL36_40 = F54_ANALOG_CTRL36_39 + 1;
    F54_ANALOG_CTRL36_41 = F54_ANALOG_CTRL36_40 + 1;
    F54_ANALOG_CTRL36_42 = F54_ANALOG_CTRL36_41 + 1;
    F54_ANALOG_CTRL36_43 = F54_ANALOG_CTRL36_42 + 1;

    F54_ANALOG_CTRL36_44 = F54_ANALOG_CTRL36_43 + 61;
    F54_ANALOG_CTRL36_45 = F54_ANALOG_CTRL36_44 + 62;
    F54_ANALOG_CTRL36_46 = F54_ANALOG_CTRL36_45 + 63;

    F54_ANALOG_CTRL38 = F54_ANALOG_CTRL36_46 + 1;
  }

  Check_RXTX_Count();
  fulfill_RX_tbl();
  fulfill_TX_tbl();
//Func54 CMD Reg for DS4 V3
//None

//Change to Page0
  I2C_RMI_BufferWrite(I2C_Address,Page_Select_register,0);
}

void constructFunc1A(void)
{
  u8 tmp;
  bool b_HasFilterStrength;
  bool b_HasStrongestButtonHysteresis;
  bool b_HasReleaseThreshold;
  bool b_HasPerButtonThreshold;
  bool b_HasTxRxMapping;
  bool b_HasMultiButtonSelect;
  bool b_HasInterruptEnable;
  bool b_HasGeneralControl;
//Func1A Query for DS4 v3
//Query0 ~ 8@#define of rmi.h

//Change to Page2
  I2C_RMI_BufferWrite(I2C_Address,Page_Select_register,2);

  MaxButtonCount = I2C_RMI_BufferRead(I2C_Address,F1A_0D_QUERY0) + 1;
  printf("Func1A Query: maximum number of buttons supported:%d.\r\n",MaxButtonCount);

  tmp = I2C_RMI_BufferRead(I2C_Address,F1A_0D_QUERY0) + 1;

  if(tmp & 0x01)
  {
    b_HasGeneralControl = TRUE;
    printf("Func1A Query: Has General Control. F1A_0D_Ctrl0 exists.\r\n");
  }
  else		b_HasGeneralControl = FALSE;

  if(tmp & 0x02)
  {
    b_HasInterruptEnable = TRUE;
    printf("Func1A Query: Has InterruptEnable. F1A_0D_Ctrl1.* exist.\r\n");
  }
  else		b_HasInterruptEnable = FALSE;

  if(tmp & 0x04)
  {
    b_HasMultiButtonSelect = TRUE;
    printf("Func1A Query: Has MultiButtonSelect. F1A_0D_Ctrl2.* exists.\r\n");
  }
  else		b_HasMultiButtonSelect = FALSE;

  if(tmp & 0x08)
  {
    b_HasTxRxMapping = TRUE;
    printf("Func1A Query: Has TxRxMapping. F1A_0D_Ctrl3.* and F1A_0D_Ctrl4.* exist.\r\n");
  }
  else		b_HasTxRxMapping = FALSE;

  if(tmp & 0x10)
  {
    b_HasPerButtonThreshold = TRUE;
    printf("Func1A Query: Has PerButtonThreshold. F1A_0D_Ctrl5.* exists.\r\n");
  }
  else		b_HasPerButtonThreshold = FALSE;

  if(tmp & 0x20)
  {
    b_HasReleaseThreshold = TRUE;
    printf("Func1A Query: Has ReleaseThreshold. F1A_0D_Ctrl6 exists.\r\n");
  }
  else		b_HasReleaseThreshold = FALSE;

  if(tmp & 0x40)
  {
    b_HasStrongestButtonHysteresis = TRUE;
    printf("Func1A Query: Has StrongestButtonHysteresis. F1A_0D_Ctrl7 exists.\r\n");
  }
  else		b_HasStrongestButtonHysteresis = FALSE;

  if(tmp & 0x80)
  {
    b_HasFilterStrength = TRUE;
    printf("Func1A Query: Has FilterStrength. F1A_0D_Ctrl8 exists.\r\n");
  }
  else		b_HasFilterStrength = FALSE;


//Func1A Data for DS4 v3
//Data0 ~ 3 @#define of rmi.h

//Func1A Control Reg for DS4 V3
  switch(MaxButtonCount)
  {
    case 0x04:
      F1A_0D_CTRL3_0 = F1A_0D_CTRL2 + 1;
      F1A_0D_CTRL4_0 = F1A_0D_CTRL2 + 2;
      F1A_0D_CTRL3_1 = F1A_0D_CTRL2 + 3;
      F1A_0D_CTRL4_1 = F1A_0D_CTRL2 + 4;
      F1A_0D_CTRL3_2 = F1A_0D_CTRL2 + 5;
      F1A_0D_CTRL4_2 = F1A_0D_CTRL2 + 6;
      F1A_0D_CTRL3_3 = F1A_0D_CTRL2 + 7;
      F1A_0D_CTRL4_3 = F1A_0D_CTRL2 + 8;
      F1A_0D_CTRL5_0 = F1A_0D_CTRL2 + 9;
      F1A_0D_CTRL5_1 = F1A_0D_CTRL2 + 10;
      F1A_0D_CTRL5_2 = F1A_0D_CTRL2 + 11;
      F1A_0D_CTRL5_3 = F1A_0D_CTRL2 + 12;

      F1A_0D_CTRL06  = F1A_0D_CTRL5_3 + 1;
      break;
    default:
      printf("MaxButtonCount is not 4.\r\n");
      break;

  }
//Func1A CMD Reg for DS4 V3
//None
//Back to default page
  I2C_RMI_BufferWrite(I2C_Address,Page_Select_register,0);

}

void constructFunc31(void)
{
  u8 tmp;
  bool b_HasBrightness;
  u8 NumberofLEDs;
//Func31 Query for DS4 v3
//Query0 ~ 1@#define of rmi.h
//Change to Page2
  I2C_RMI_BufferWrite(I2C_Address,Page_Select_register,2);

  if(I2C_RMI_BufferRead(I2C_Address,F31_LED_QUERY0) & 0x01)
  {
    b_HasBrightness = TRUE;
    printf("Func31 Query: Has Brightness. F31_LED_Ctrl0.* exist.\r\n");
  }
  else		b_HasBrightness = FALSE;

  NumberofLEDs = I2C_RMI_BufferRead(I2C_Address,F31_LED_QUERY1) & 0x0F;
  printf("Func31 Query: Number of LED outputs: %d.\r\n",NumberofLEDs);
//Func31 Data for DS4 v3
//None

//Func31 Control Reg for DS4 V3
//Ctrl0 ~ 7 @#define of rmi.h

//Func31 CMD Reg for DS4 V3
//None

//Back to default page
  I2C_RMI_BufferWrite(I2C_Address,Page_Select_register,0);
}

#if 0

void CheckIntNum(void)
{
  u8 tmp=0;

  tmp = I2C_RMI_BufferRead(addr,F01_Ctrl_base_address+1);
//   printf("CheckIntNum:Interrupt Enable 0:0x%x\r\n",tmp);

  switch(tmp)
  {
    case 0x01:
      HasFlashInt = TRUE;
      HasStatusInt = FALSE;
      HasAbs0Int = FALSE;
      HasAbs1Int = FALSE;
      HasButtonInt = FALSE;
      HasBistInt = FALSE;

      printf("CheckIntNum: HasFlashInt.\r\n");

      break;
    case 0x03:
      HasFlashInt = TRUE;
      HasStatusInt = TRUE;
      HasAbs0Int = FALSE;
      HasAbs1Int = FALSE;
      HasButtonInt = FALSE;
      HasBistInt = FALSE;

      printf("CheckIntNum: HasFlashInt ,HasStatusInt.\r\n");
      break;
    case 0x07:
      HasFlashInt = TRUE;
      HasStatusInt = TRUE;
      printf("CheckIntNum: HasFlashInt ,HasStatusInt.");

      if(F11_Data_base_address !=0) HasAbs0Int = TRUE; //printf(" HasAbs0Int.\r\n");
      HasAbs1Int = FALSE;
      HasButtonInt = FALSE;
      HasBistInt = FALSE;


      break;
    case 0x0F:
      HasFlashInt = TRUE;
      HasStatusInt = TRUE;
      printf("CheckIntNum: HasFlashInt ,HasStatusInt.");

      if(F11_Data_base_address !=0)
      {
        HasAbs0Int = TRUE;
        printf(" HasAbs0Int.");
      }
      HasAbs1Int = FALSE;
      if(F19_Data_base_address !=0)
      {
        HasButtonInt = TRUE;
        printf(" HasButtonInt.");
      }
      else 						   HasButtonInt = FALSE;
      if(F09_Data_base_address !=0)
      {
        HasBistInt = TRUE;
        printf(" HasBistInt.");
      }
      else						   HasBistInt = FALSE;
      printf("\r\n");
      break;
    case 0x1F:
      HasFlashInt = TRUE;
      HasStatusInt = TRUE;
      HasAbs0Int = TRUE;
      HasAbs1Int = FALSE;

      printf("CheckIntNum: HasFlashInt ,HasStatusInt.");

      if(F19_Data_base_address !=0)
      {
        HasButtonInt = TRUE;
        printf(" HasButtonInt.");
      }
      else 						   HasButtonInt = FALSE;
      if(F09_Data_base_address !=0)
      {
        HasBistInt = TRUE;
        printf(" HasBistInt.");
      }
      else						   HasBistInt = FALSE;
      printf("\r\n");
      break;
    case 0x3F:
      HasFlashInt = TRUE;
      HasStatusInt = TRUE;
      HasAbs0Int = TRUE;
      HasAbs1Int = FALSE;
      HasButtonInt = TRUE;
      printf("CheckIntNum: HasFlashInt ,HasStatusInt, HasButtonInt");

      if(F09_Data_base_address !=0)
      {
        HasBistInt = TRUE;
        printf(" HasBistInt.");
      }
      else						   HasBistInt = FALSE;
      printf("\r\n");
      break;
    case 0x7F:
      HasFlashInt = TRUE;
      HasStatusInt = TRUE;
      HasAbs0Int = TRUE;
      HasAbs1Int = FALSE;
      HasButtonInt = TRUE;
      HasBistInt = TRUE;
      printf("CheckIntNum: HasFlashInt ,HasStatusInt, HasButtonInt, HasBistInt.\r\n");
      break;
    case 0xFF:
      HasFlashInt = TRUE;
      HasStatusInt = TRUE;
      HasAbs0Int = TRUE;
      HasAbs1Int = FALSE;
      HasButtonInt = TRUE;
      HasBistInt = TRUE;
      break;
  }
}


void Read_Product_ID(unsigned char addr)
{
  u8 index;
  u8 TM[10];

//	printf("F01_Query_base_address:0x%x \r\n",F01_Query_base_address);

  for(index=0; index<10; index++)
  {
    TM[index]=I2C_RMI_BufferRead(addr,F01_Query_base_address+11+index);
  }

  printf("Model ID:%s \r\n",TM);
  Disp_LCDString(100,200,TM);
}

void Check_Sensor_Info(unsigned char addr)
{
//	sensor_general_info sensor;
  u8 tmp;

  tmp=I2C_RMI_BufferRead(addr,F11_Query_base_address+1);

//	printf("F11_Query_base_address:0x%x ,tmp:0x%x\r\n",F11_Query_base_address,tmp);

  if(tmp & 0x08)
  {
    sensor.HasRel = TRUE;
    printf("General Sensor Info:Relative Mode Enable, ");
  }
  else
  {
    sensor.HasRel = FALSE;
    printf("General Sensor Info:Relative Mode Disable, ");
  }

  if(tmp & 0x10)
  {
    sensor.HasAbs = TRUE;
    printf("Absolute Mode Enable , ");
  }
  else
  {
    sensor.HasAbs = FALSE;
    printf("Absolute Mode Disable ,");
  }

  if(tmp & 0x20)
  {
    sensor.HasGesture = TRUE;
    printf("Has Gesture support , ");
  }
  else
  {
    sensor.HasGesture = FALSE;
    printf("No Gesture support ,");
  }

  if(tmp & 0x40)
  {
    sensor.HasSensitivityAdjust = TRUE;
    printf("Has Adjustable Sensitivity , ");
  }
  else
  {
    sensor.HasSensitivityAdjust = FALSE;
    printf("No Adjustable Sensitivity , ");
  }

  if(tmp & 0x80)
  {
    sensor.Configurable = TRUE;
    printf("Configurable.\r\n");
  }
  else
  {
    sensor.Configurable = FALSE;
    printf("Not Configurable.\r\n");
  }

}

void Read_F11_Gestures(unsigned char addr)
{
  rmi4_gesture f11_egr;
  u8 tmp;

  if(F11_2D_Data8)
  {
    tmp = I2C_RMI_BufferRead(addr,F11_2D_Data8);
    printf("F11_2D_Data8:0x%x\r\n", tmp);
//pinch
    if(sensor.HasGesture && (tmp & 0x40) )
    {
      printf("f11 gesture: tap.\r\n");
      f11_egr.hasEgrPinch = TRUE;
    }
    else										  f11_egr.hasEgrPinch = FALSE;
//press
    if(sensor.HasGesture && (tmp & 0x20) )
    {
      printf("f11 gesture: press.\r\n");
      f11_egr.hasEgrPress = TRUE;
    }
    else										   f11_egr.hasEgrPress = FALSE;
//flick
    if(sensor.HasGesture && (tmp & 0x10) )
    {
      printf("f11 gesture: flick.\r\n");
      f11_egr.hasEgrFlick = TRUE;
    }
    else										   f11_egr.hasEgrFlick = FALSE;
//early tap
    if(sensor.HasGesture && (tmp & 0x08) )
    {
      printf("f11 gesture: early tap.\r\n");
      f11_egr.hasEgrEarlyTap = TRUE;
    }
    else										   		f11_egr.hasEgrEarlyTap = FALSE;
//double tap
    if(sensor.HasGesture && (tmp & 0x04) )
    {
      printf("f11 gesture: double tap.\r\n");
      f11_egr.hasEgrDoubleTap = TRUE;
    }
    else										   f11_egr.hasEgrDoubleTap = FALSE;
//tap&hold
    if(sensor.HasGesture && (tmp & 0x02) )
    {
      printf("f11 gesture: tap&hold.\r\n");
      f11_egr.hasEgrTapAndHold = TRUE;
    }
    else										   f11_egr.hasEgrTapAndHold = FALSE;
//singal tap
    if(sensor.HasGesture && (tmp & 0x10) )
    {
      printf("f11 gesture: singal tap.\r\n");
      f11_egr.hasEgrSingleTap = TRUE;
    }
    else										   f11_egr.hasEgrSingleTap = FALSE;


  }
  else if(F11_2D_Data9)
  {

    tmp = I2C_RMI_BufferRead(addr,F11_2D_Data9);
    printf("F11_2D_Data9:0x%x\r\n",tmp);
//Individal scroll zone
    if(sensor.HasGesture && (tmp & 0x10) )
    {
      printf("f11 gesture: Individal scroll zone.\r\n");
      f11_egr.hasEgrIndividualScrollZones = TRUE;
    }
    else										   					f11_egr.hasEgrIndividualScrollZones = FALSE;
//scroll zone
    if(sensor.HasGesture && (tmp & 0x08) )
    {
      printf("f11 gesture: scroll zone.\r\n");
      f11_egr.hasEgrscrollZones = TRUE;
    }
    else										   f11_egr.hasEgrscrollZones = FALSE;
//touch shape
    if(sensor.HasGesture && (tmp & 0x04) )
    {
      printf("f11 gesture: touch shape.\r\n");
      f11_egr.hasEgrTouchShapes = TRUE;
    }
    else										   f11_egr.hasEgrTouchShapes = FALSE;
//rotate
    if(sensor.HasGesture && (tmp & 0x02) )
    {
      printf("f11 gesture: rotate.\r\n");
      f11_egr.hasEgrRotate = TRUE;
    }
    else										   f11_egr.hasEgrRotate = FALSE;
//palm detect
    if(sensor.HasGesture && (tmp & 0x01) )
    {
      printf("f11 gesture: palm detect.\r\n");
      f11_egr.hasEgrPalmDetect = TRUE;
    }
    else										   f11_egr.hasEgrPalmDetect = FALSE;
  }
  /*
  else if(F11_2D_Data9)
  //large object
  	if(sensor.HasGesture && (tmp & 0x04) ) { printf("f11 gesture: large object sensitivity.\r\n"); f11_egr.hasMiscLargeObjectSensitivity = TRUE; }
  	else										   f11_egr.hasMiscLargeObjectSensitivity = FALSE;
  //finger proximity
  	if(sensor.HasGesture && (tmp & 0x02) ) { printf("f11 gesture: finger proximity.\r\n"); f11_egr.hasMiscFingerProximity = TRUE; }
  	else										   f11_egr.hasMiscFingerProximity = FALSE;
  //pen
  	if(sensor.HasGesture && (tmp & 0x01) ) { printf("f11 gesture: pen.\r\n"); f11_egr.hasMiscPen = TRUE; }
  	else										   f11_egr.hasMiscPen = FALSE;
  */


}
void Check_F11_Gestures_support(unsigned char addr)
{

  u8 f11_egr_q1,f11_egr_q2,f11_egr_q3;

  f11_egr_q1 = I2C_RMI_BufferRead(addr,F11_Query_base_address+6);
  f11_egr_q2 = I2C_RMI_BufferRead(addr,F11_Query_base_address+7);
  f11_egr_q3 = I2C_RMI_BufferRead(addr,F11_Query_base_address+8);

  if(f11_egr_q1)  F11_2D_Data8 = 	F11_Data_base_address+F11_2D_Data0_registerCount+Finger_Data_Size*supportfingers+4+1;
  else 			F11_2D_Data8 = 0;

  printf("f11_egr_q1: 0x%x ,F11_Data_base_address: 0x%x ,F11_2D_Data0_registerCount: 0x%x\r\n",f11_egr_q1,F11_Data_base_address,F11_2D_Data0_registerCount);
  printf("Finger_Data_Size: 0x%x ,supportfingers: 0x%x \r\n",Finger_Data_Size,supportfingers);

  printf("F11_2D_Data8: 0x%x\r\n",F11_2D_Data8);

  if((f11_egr_q1 || f11_egr_q2))
  {
    if(F11_2D_Data8)	F11_2D_Data9 = F11_Data_base_address+F11_2D_Data0_registerCount+Finger_Data_Size*supportfingers+ 1;
    else 				F11_2D_Data9 = F11_Data_base_address+F11_2D_Data0_registerCount+Finger_Data_Size*supportfingers;
  }
  else 			F11_2D_Data9 = 0;

  printf("F11_2D_Data9: 0x%x\r\n",F11_2D_Data9);




}

void Check_XY_Electrodes(unsigned char addr)
{
  u8 X_Electrodes=0,Y_Electrodes=0,Max_Electrodes;

  X_Electrodes=I2C_RMI_BufferRead(addr,F11_Query_base_address+2);
  Y_Electrodes=I2C_RMI_BufferRead(addr,F11_Query_base_address+3);
  Max_Electrodes=I2C_RMI_BufferRead(addr,F11_Query_base_address+4);

  printf("X Electrodes:%d. Y Electrodes:%d. Max Electrodes:%d.\r\n",X_Electrodes,Y_Electrodes,Max_Electrodes);

}

void Check_Button_Status(unsigned char addr)
{
  u8 button_status;
  u8 i=0;

  button_status=I2C_RMI_BufferRead(addr,F19_Data_base_address);
  printf("button_status:0x%0x.",button_status);
  LCD_RMI_Button(button_status);

  if(button_status ==0) printf(" Button released.\r\n");
  else
  {
    for(i=0; i<8; i++)
    {
      if(button_status & 0x01)  	printf(" Button %d ON.\r\n",i);
      button_status=button_status>>1;
    }
  }
}


void Read_Finger_Data(unsigned char addr,unsigned char finger_num)
{

}
#endif
/*----------------------------------------------------------*\
 | END OF FILE                                              |
\*----------------------------------------------------------*/
