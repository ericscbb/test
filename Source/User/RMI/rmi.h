/*******************************************************************************
* File Name          : rmi.h
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Header for rmi.c module
*******************************************************************************/
/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef __RMI_H
#define __RMI_H

#include "stm32f10x.h"
#include "LCD_Drive.h"

//Registrue structure
typedef struct
{
  uint8_t Query_Base;
  uint8_t Cmd_Base;
  uint8_t Ctrl_Base;
  uint8_t Data_Base;
  uint8_t Int_num;
  uint8_t Fun_Exist;
} Rmi_register_type;
//extern Rmi_register_type PDT_Reg_type;

typedef struct
{
  u16 pos_x;
  u16 pos_y;
  uint8_t pos_z;
  uint8_t pos_wx;
  uint8_t pos_wy;
} finger_info_structure;

typedef struct
{
  bool HasRel;
  bool HasAbs;
  bool HasGesture;
  bool HasSensitivityAdjust;
  bool Configurable;
} sensor_general_info;

typedef struct
{
  bool hasEgrPinch;
  bool hasEgrPress;
  bool hasEgrFlick;
  bool hasEgrEarlyTap;
  bool hasEgrDoubleTap;
  bool hasEgrTapAndHold;
  bool hasEgrSingleTap;
  bool hasEgrIndividualScrollZones;
  bool hasEgrscrollZones;
  bool hasEgrTouchShapes;
  bool hasEgrRotate;
  bool hasEgrPalmDetect;
  bool hasMiscLargeObjectSensitivity;
  bool hasMiscFingerProximity;
  bool hasMiscPen;
} rmi4_gesture;


/*******************************************************************************
* RMI4 Function base address
******************************************************************************/
//Func01
extern u8 F01_RMI_Query0_20;
#define F01_RMI_Query0      F01_RMI_Query0_20
#define F01_RMI_Query1      F01_RMI_Query0_20 + 1
#define F01_RMI_Query2      F01_RMI_Query0_20 + 2
#define F01_RMI_Query3      F01_RMI_Query0_20 + 3
#define F01_RMI_Query4      F01_RMI_Query0_20 + 4
#define F01_RMI_Query5      F01_RMI_Query0_20 + 5
#define F01_RMI_Query6      F01_RMI_Query0_20 + 6
#define F01_RMI_Query7      F01_RMI_Query0_20 + 7
#define F01_RMI_Query8      F01_RMI_Query0_20 + 8
#define F01_RMI_Query9      F01_RMI_Query0_20 + 9
#define F01_RMI_Query10     F01_RMI_Query0_20 + 10
#define F01_RMI_Query11     F01_RMI_Query0_20 + 11
#define F01_RMI_Query12     F01_RMI_Query0_20 + 12
#define F01_RMI_Query13     F01_RMI_Query0_20 + 13
#define F01_RMI_Query14     F01_RMI_Query0_20 + 14
#define F01_RMI_Query15     F01_RMI_Query0_20 + 15
#define F01_RMI_Query16     F01_RMI_Query0_20 + 16
#define F01_RMI_Query17     F01_RMI_Query0_20 + 17
#define F01_RMI_Query18     F01_RMI_Query0_20 + 18
#define F01_RMI_Query19     F01_RMI_Query0_20 + 19
#define F01_RMI_Query20     F01_RMI_Query0_20 + 20

#define F01_RMI_QUERY42	    F01_RMI_Query0_20 + 21
#define F01_RMI_QUERY43_0   F01_RMI_Query0_20 + 22
#define F01_RMI_QUERY43_1   F01_RMI_Query0_20 + 23
#define F01_RMI_QUERY43_2   F01_RMI_Query0_20 + 24
#define F01_RMI_QUERY44   	F01_RMI_Query0_20 + 25

extern u8 F01_RMI_Data0;
#define	F01_RMI_Data1 			F01_RMI_Data0 + 1

#define	F01_RMI_Ctrl1 			F01_RMI_Ctrl0 + 1
#define	F01_RMI_Ctrl2			F01_RMI_Ctrl0 + 2
#define	F01_RMI_Ctrl3 			F01_RMI_Ctrl0 + 3
#define	F01_RMI_Ctrl4			F01_RMI_Ctrl0 + 4
#define	F01_RMI_Ctrl5 			F01_RMI_Ctrl0 + 5
#define	F01_RMI_Ctrl6			F01_RMI_Ctrl0 + 6

//SPI Ctrl
//#define	F01_RMI_Ctrl7				F01_RMI_Ctrl0 + 6
#define	F01_RMI_Ctrl8				F01_RMI_Ctrl0 + 7
//Func11
#define F11_2D_Query1      F11_2D_Query0 + 1
#define F11_2D_Query2      F11_2D_Query0 + 2
#define F11_2D_Query3      F11_2D_Query0 + 3
#define F11_2D_Query4      F11_2D_Query0 + 4
#define F11_2D_Query5      F11_2D_Query0 + 5

//extern u8 F11_2D_Ctrl0_9;
#define F11_2D_Ctrl0     F11_2D_Ctrl0_9
#define F11_2D_Ctrl1     F11_2D_Ctrl0_9 + 1
#define F11_2D_Ctrl2     F11_2D_Ctrl0_9 + 2
#define F11_2D_Ctrl3     F11_2D_Ctrl0_9 + 3
#define F11_2D_Ctrl4     F11_2D_Ctrl0_9 + 4
#define F11_2D_Ctrl5     F11_2D_Ctrl0_9 + 5
#define F11_2D_Ctrl6     F11_2D_Ctrl0_9 + 6
#define F11_2D_Ctrl7     F11_2D_Ctrl0_9 + 7
#define F11_2D_Ctrl8     F11_2D_Ctrl0_9 + 8
#define F11_2D_Ctrl9     F11_2D_Ctrl0_9 + 9

//Gesture Ctrl
#define F11_2D_Ctrl10     F11_2D_Ctrl10_19
#define F11_2D_Ctrl11     F11_2D_Ctrl10_19 + 1
//Func Ctrl 12/13 are not for Func11 v1
//#define F11_2D_Ctrl12     F11_2D_Ctrl10_19 + 2
//#define F11_2D_Ctrl13     F11_2D_Ctrl10_19 + 3
#define F11_2D_Ctrl14     F11_2D_Ctrl10_19 + 2
#define F11_2D_Ctrl15     F11_2D_Ctrl10_19 + 3
#define F11_2D_Ctrl16     F11_2D_Ctrl10_19 + 4
#define F11_2D_Ctrl17     F11_2D_Ctrl10_19 + 5
#define F11_2D_Ctrl18     F11_2D_Ctrl10_19 + 6
#define F11_2D_Ctrl19     F11_2D_Ctrl10_19 + 7

#define F11_2D_Ctrl21     F11_2D_Ctrl20 + 1

#define F11_2D_Ctrl29     F11_2D_Ctrl21 + 1
#define F11_2D_Ctrl30     F11_2D_Ctrl29 + 1
#define F11_2D_Ctrl31     F11_2D_Ctrl30 + 1
#define F11_2D_Ctrl32_0   F11_2D_Ctrl31 + 1
#define F11_2D_Ctrl32_1   F11_2D_Ctrl32_0 + 1
#define F11_2D_Ctrl33_0   F11_2D_Ctrl32_1 + 1
#define F11_2D_Ctrl33_1   F11_2D_Ctrl33_0 + 1
#define F11_2D_Ctrl34     F11_2D_Ctrl33_1 + 1
#define F11_2D_Ctrl35     F11_2D_Ctrl34 + 1
#define F11_2D_Ctrl36     F11_2D_Ctrl35 + 1
#define F11_2D_Ctrl37     F11_2D_Ctrl36 + 1
#define F11_2D_Ctrl38     F11_2D_Ctrl37 + 1
#define F11_2D_Ctrl39     F11_2D_Ctrl38 + 1
#define F11_2D_Ctrl40_0   F11_2D_Ctrl39 + 1
#define F11_2D_Ctrl40_1   F11_2D_Ctrl40_0 + 1
#define F11_2D_Ctrl41_0   F11_2D_Ctrl40_1 + 1
#define F11_2D_Ctrl41_1   F11_2D_Ctrl41_0 + 1
#define F11_2D_Ctrl42_0   F11_2D_Ctrl41_1 + 1
#define F11_2D_Ctrl42_1   F11_2D_Ctrl42_0 + 1
#define F11_2D_Ctrl43_0   F11_2D_Ctrl42_1 + 1
#define F11_2D_Ctrl43_1   F11_2D_Ctrl43_0 + 1
#define F11_2D_Ctrl45     F11_2D_Ctrl43_1 + 1
#define F11_2D_Ctrl46     F11_2D_Ctrl45 + 1
#define F11_2D_Ctrl47     F11_2D_Ctrl46 + 1
#define F11_2D_Ctrl48     F11_2D_Ctrl47 + 1
#define F11_2D_Ctrl49     F11_2D_Ctrl48 + 1
#define F11_2D_Ctrl50     F11_2D_Ctrl49 + 1
#define F11_2D_Ctrl51     F11_2D_Ctrl50 + 1
//Bending
//#define F11_2D_Ctrl52
//#define F11_2D_Ctrl53
//#define F11_2D_Ctrl54
//#define F11_2D_Ctrl55
//#define F11_2D_Ctrl56
//#define F11_2D_Ctrl57
#define F11_2D_Ctrl58 		F11_2D_Ctrl51 + 1
//Temporary placeholder
//#define F11_2D_Ctrl59
//#define F11_2D_Ctrl60
//#define F11_2D_Ctrl61
//#define F11_2D_Ctrl62
//#define F11_2D_Ctrl63
//#define F11_2D_Ctrl64
//#define F11_2D_Ctrl65
//#define F11_2D_Ctrl66
//#define F11_2D_Ctrl67
#define F11_2D_Ctrl68_0 		F11_2D_Ctrl58 + 1
#define F11_2D_Ctrl68_1 		F11_2D_Ctrl68_0 + 1
#define F11_2D_Ctrl68_2 		F11_2D_Ctrl68_1 + 1
#define F11_2D_Ctrl68_3 		F11_2D_Ctrl68_2 + 1
#define F11_2D_Ctrl68_4 		F11_2D_Ctrl68_3 + 1
#define F11_2D_Ctrl68_5 		F11_2D_Ctrl68_4 + 1
#define F11_2D_Ctrl69 			F11_2D_Ctrl68_5 + 1
#define F11_2D_Ctrl70 			F11_2D_Ctrl69 + 1
#define F11_2D_Ctrl71 			F11_2D_Ctrl70 + 1
#define F11_2D_Ctrl72 			F11_2D_Ctrl71 + 1
#define F11_2D_Ctrl73 			F11_2D_Ctrl72 + 1
#define F11_2D_Ctrl74 			F11_2D_Ctrl73 + 1
#define F11_2D_Ctrl75_0 		F11_2D_Ctrl74 + 1
#define F11_2D_Ctrl75_1 		F11_2D_Ctrl75_0 + 1
#define F11_2D_Ctrl75_2 		F11_2D_Ctrl75_1 + 1
#define F11_2D_Ctrl76_0 		F11_2D_Ctrl75_2 + 1
#define F11_2D_Ctrl76_1 		F11_2D_Ctrl68_5 + 1
#define F11_2D_Ctrl76_2 		F11_2D_Ctrl76_1 + 1
#define F11_2D_Ctrl77 			F11_2D_Ctrl76_2 + 1
#define F11_2D_Ctrl78 			F11_2D_Ctrl77 + 1	//Done for Func11 Ctrl of DS4 v3


//extern u8 F11_2D_Data0_1;
//extern u8 F11_2D_Data0_2;


//#define F11_2D_Data1     F11_2D_Data0_2 + 1
//#define F11_2D_Data2     F11_2D_Data1_5 + 1
//#define F11_2D_Data3     F11_2D_Data1_5 + 2
//#define F11_2D_Data4     F11_2D_Data1_5 + 3
//#define F11_2D_Data5     F11_2D_Data1_5 + 4
//#define F11_2D_Data6     F11_2D_Data6_7
//#define F11_2D_Data7     F11_2D_Data6_7 + 1


//Func34
//unsigned int F34_FLASH_QUERY_BASE = 0;
//unsigned int F34_FLASH_COMMAND_BASE = 0;
//unsigned int F34_FLASH_CONTROL_BASE = 0;
extern u8 F34_FLASH_DATA_BASE;
#define F34_FLASH_DATA00				F34_FLASH_DATA_BASE
#define F34_FLASH_DATA01				F34_FLASH_DATA_BASE	+ 0x01
#define F34_FLASH_DATA02_15			F34_FLASH_DATA_BASE	+ 0x02
#define F34_FLASH_DATA2_0				F34_FLASH_DATA02_15
#define F34_FLASH_DATA2_1				F34_FLASH_DATA02_15 + 1
#define F34_FLASH_DATA2_2				F34_FLASH_DATA02_15 + 2
#define F34_FLASH_DATA2_3				F34_FLASH_DATA02_15 + 3
#define F34_FLASH_DATA2_4				F34_FLASH_DATA02_15 + 4
#define F34_FLASH_DATA2_5				F34_FLASH_DATA02_15 + 5
#define F34_FLASH_DATA2_6				F34_FLASH_DATA02_15 + 6
#define F34_FLASH_DATA2_7				F34_FLASH_DATA02_15 + 7
#define F34_FLASH_DATA2_8				F34_FLASH_DATA02_15 + 8
#define F34_FLASH_DATA2_9				F34_FLASH_DATA02_15 + 9
#define F34_FLASH_DATA2_10			F34_FLASH_DATA02_15 + 10
#define F34_FLASH_DATA2_11			F34_FLASH_DATA02_15 + 11
#define F34_FLASH_DATA2_12			F34_FLASH_DATA02_15 + 12
#define F34_FLASH_DATA2_13			F34_FLASH_DATA02_15 + 13
#define F34_FLASH_DATA2_14			F34_FLASH_DATA02_15 + 14
#define F34_FLASH_DATA2_15			F34_FLASH_DATA02_15 + 15
#define F34_FLASH_DATA03				F34_FLASH_DATA_BASE	+ 0x12

#define F34_FLASH_CTRL0_0				F34_FLASH_CONTROL_BASE
#define F34_FLASH_CTRL0_1				F34_FLASH_CONTROL_BASE + 1
#define F34_FLASH_CTRL0_2				F34_FLASH_CONTROL_BASE + 2
#define F34_FLASH_CTRL0_3				F34_FLASH_CONTROL_BASE + 3

extern u8 F34_FLASH_QUERY_BASE;
#define F34_FLASH_QUERY0				F34_FLASH_QUERY_BASE
#define F34_FLASH_QUERY1    		F34_FLASH_QUERY_BASE + 1
#define F34_FLASH_QUERY2				F34_FLASH_QUERY_BASE + 2
#define F34_FLASH_QUERY3    		F34_FLASH_QUERY_BASE + 3
#define F34_FLASH_QUERY4				F34_FLASH_QUERY_BASE + 4
#define F34_FLASH_QUERY5    		F34_FLASH_QUERY_BASE + 5
#define F34_FLASH_QUERY6				F34_FLASH_QUERY_BASE + 6
#define F34_FLASH_QUERY7    		F34_FLASH_QUERY_BASE + 7
#define F34_FLASH_QUERY8				F34_FLASH_QUERY_BASE + 8

//Func54 Query Reg
#define F54_Query0 							F54_Query_Base
#define F54_Query1    					F54_Query_Base + 1
#define F54_Query2    					F54_Query_Base + 2
#define F54_Query3_0  	  			F54_Query_Base + 3
#define F54_Query3_1  	  			F54_Query_Base + 4
#define F54_Query4    					F54_Query_Base + 5
#define F54_Query5    					F54_Query_Base + 6
#define F54_Query6    					F54_Query_Base + 7
#define F54_Query7    					F54_Query_Base + 8
#define F54_Query8    					F54_Query_Base + 9
#define F54_Query9    					F54_Query_Base + 10
#define F54_Query10   	 				F54_Query_Base + 11
#define F54_Query11   	 				F54_Query_Base + 12
#define F54_Query12   	 				F54_Query_Base + 13
#define F54_Query13   	 				F54_Query_Base + 14

//Func54 Data Reg
#define F54_ANALOG_DATA0				F54_Data_Base
#define F54_ANALOG_DATA1				F54_Data_Base + 1
#define F54_Data_LowIndex				F54_ANALOG_DATA1
#define F54_ANALOG_DATA2				F54_Data_Base + 2
#define F54_Data_HighIndex				F54_ANALOG_DATA2
#define F54_ANALOG_DATA3				F54_Data_Base + 3
#define F54_Data_Buffer					F54_ANALOG_DATA3
#define F54_ANALOG_DATA4				F54_Data_Base + 4
//Reserved
//#define F54_ANALOG_DATA5
#define F54_ANALOG_DATA6_0			F54_Data_Base + 5
#define F54_ANALOG_DATA6_1			F54_Data_Base + 6
#define F54_ANALOG_DATA7_0			F54_Data_Base + 7
#define F54_ANALOG_DATA7_1			F54_Data_Base + 8
#define F54_ANALOG_DATA8_0			F54_Data_Base + 9
#define F54_ANALOG_DATA8_1			F54_Data_Base + 10

//Func54 CTRL Reg
extern u8 								F54_Control_Base;
#define F54_ANALOG_CTRL0				F54_Control_Base
#define F54_ANALOG_CTRL1				F54_Control_Base + 1
#define F54_ANALOG_CTRL2_0			F54_Control_Base + 2
#define F54_ANALOG_CTRL2_1			F54_Control_Base + 3
#define F54_ANALOG_CTRL3				F54_Control_Base + 4
#define F54_ANALOG_CTRL4				F54_Control_Base + 5
#define F54_ANALOG_CTRL5				F54_Control_Base + 6
#define F54_ANALOG_CTRL6				F54_Control_Base + 7
#define F54_ANALOG_CTRL7				F54_Control_Base + 8
#define F54_ANALOG_CTRL8_0			F54_Control_Base + 9
#define F54_ANALOG_CTRL8_1			F54_Control_Base + 10
#define F54_ANALOG_CTRL9				F54_Control_Base + 11
#define F54_ANALOG_CTRL10				F54_Control_Base + 12
#define F54_ANALOG_CTRL11_0			F54_Control_Base + 13
#define F54_ANALOG_CTRL11_1			F54_Control_Base + 14
#define F54_ANALOG_CTRL12				F54_Control_Base + 15
#define F54_ANALOG_CTRL13				F54_Control_Base + 16
#define F54_ANALOG_CTRL14				F54_Control_Base + 17

#define F54_ANALOG_CTRL15_0			F54_Control_Base + 18
#define F54_ANALOG_CTRL15_1			F54_Control_Base + 19
#define F54_ANALOG_CTRL15_2			F54_Control_Base + 20
#define F54_ANALOG_CTRL15_3			F54_Control_Base + 21
#define F54_ANALOG_CTRL15_4			F54_Control_Base + 22
#define F54_ANALOG_CTRL15_5			F54_Control_Base + 23
#define F54_ANALOG_CTRL15_6			F54_Control_Base + 24
#define F54_ANALOG_CTRL15_7			F54_Control_Base + 25
#define F54_ANALOG_CTRL15_8			F54_Control_Base + 26
#define F54_ANALOG_CTRL15_9			F54_Control_Base + 27
#define F54_ANALOG_CTRL15_10		F54_Control_Base + 28
#define F54_ANALOG_CTRL15_11		F54_Control_Base + 29
#define F54_ANALOG_CTRL15_12		F54_Control_Base + 30
#define F54_ANALOG_CTRL15_13		F54_Control_Base + 31
#define F54_ANALOG_CTRL15_14		F54_Control_Base + 32
#define F54_ANALOG_CTRL15_15		F54_Control_Base + 33
#define F54_ANALOG_CTRL15_16		F54_Control_Base + 34
#define F54_ANALOG_CTRL15_17		F54_Control_Base + 35 //S3201

#define F54_ANALOG_CTRL16_1  		F54_ANALOG_CTRL16_0 + 1
#define F54_ANALOG_CTRL16_2  		F54_ANALOG_CTRL16_0 + 2
#define F54_ANALOG_CTRL16_3  		F54_ANALOG_CTRL16_0 + 3
#define F54_ANALOG_CTRL16_4  		F54_ANALOG_CTRL16_0 + 4
#define F54_ANALOG_CTRL16_5  		F54_ANALOG_CTRL16_0 + 5
#define F54_ANALOG_CTRL16_6  		F54_ANALOG_CTRL16_0 + 6
#define F54_ANALOG_CTRL16_7  		F54_ANALOG_CTRL16_0 + 7
#define F54_ANALOG_CTRL16_8  		F54_ANALOG_CTRL16_0 + 8
#define F54_ANALOG_CTRL16_9  		F54_ANALOG_CTRL16_0 + 9
#define F54_ANALOG_CTRL16_10 		F54_ANALOG_CTRL16_0 + 10

#define F54_ANALOG_CTRL17_0 		F54_ANALOG_CTRL17
#define F54_ANALOG_CTRL17_1 		F54_ANALOG_CTRL17_0 + 1
#define F54_ANALOG_CTRL17_2 		F54_ANALOG_CTRL17_0 + 2
#define F54_ANALOG_CTRL17_3 		F54_ANALOG_CTRL17_0 + 3
#define F54_ANALOG_CTRL17_4 		F54_ANALOG_CTRL17_0 + 4
#define F54_ANALOG_CTRL17_5 		F54_ANALOG_CTRL17_0 + 5
#define F54_ANALOG_CTRL17_6 		F54_ANALOG_CTRL17_0 + 6
#define F54_ANALOG_CTRL17_7 		F54_ANALOG_CTRL17_0 + 7

#define F54_ANALOG_CTRL18_0 		F54_ANALOG_CTRL17_7 + 1
#define F54_ANALOG_CTRL18_1 		F54_ANALOG_CTRL18_0 + 1
#define F54_ANALOG_CTRL18_2 		F54_ANALOG_CTRL18_0 + 2
#define F54_ANALOG_CTRL18_3 		F54_ANALOG_CTRL18_0 + 3
#define F54_ANALOG_CTRL18_4 		F54_ANALOG_CTRL18_0 + 4
#define F54_ANALOG_CTRL18_5 		F54_ANALOG_CTRL18_0 + 5
#define F54_ANALOG_CTRL18_6 		F54_ANALOG_CTRL18_0 + 6
#define F54_ANALOG_CTRL18_7 		F54_ANALOG_CTRL18_0 + 7

#define F54_ANALOG_CTRL19_0 		F54_ANALOG_CTRL18_7 + 1
#define F54_ANALOG_CTRL19_1 		F54_ANALOG_CTRL19_0 + 1
#define F54_ANALOG_CTRL19_2 		F54_ANALOG_CTRL19_0 + 2
#define F54_ANALOG_CTRL19_3 		F54_ANALOG_CTRL19_0 + 3
#define F54_ANALOG_CTRL19_4 		F54_ANALOG_CTRL19_0 + 4
#define F54_ANALOG_CTRL19_5 		F54_ANALOG_CTRL19_0 + 5
#define F54_ANALOG_CTRL19_6 		F54_ANALOG_CTRL19_0 + 6
#define F54_ANALOG_CTRL19_7 		F54_ANALOG_CTRL19_0 + 7

#define F54_ANALOG_CTRL20 			F54_ANALOG_CTRL19_7 + 1
#define F54_ANALOG_CTRL21_0 		F54_ANALOG_CTRL20 + 1
#define F54_ANALOG_CTRL21_1			F54_ANALOG_CTRL20 + 2
#define F54_ANALOG_CTRL22 			F54_ANALOG_CTRL21_1 + 1
#define F54_ANALOG_CTRL23_0 		F54_ANALOG_CTRL22 + 1
#define F54_ANALOG_CTRL23_1			F54_ANALOG_CTRL22 + 2
#define F54_ANALOG_CTRL24_0 		F54_ANALOG_CTRL22 + 3
#define F54_ANALOG_CTRL24_1			F54_ANALOG_CTRL22 + 4
#define F54_ANALOG_CTRL25 			F54_ANALOG_CTRL24_1 + 1
#define F54_ANALOG_CTRL26 			F54_ANALOG_CTRL25 + 1
#define F54_ANALOG_CTRL27 			F54_ANALOG_CTRL26 + 1
#define F54_ANALOG_CTRL28_0 		F54_ANALOG_CTRL27 + 1
#define F54_ANALOG_CTRL28_1			F54_ANALOG_CTRL27 + 2
#define F54_ANALOG_CTRL29 			F54_ANALOG_CTRL28_1 + 1
#define F54_ANALOG_CTRL30 			F54_ANALOG_CTRL29 + 1
#define F54_ANALOG_CTRL31 			F54_ANALOG_CTRL30 + 1
#define F54_ANALOG_CTRL32_0 		F54_ANALOG_CTRL31 + 1
#define F54_ANALOG_CTRL32_1			F54_ANALOG_CTRL31 + 2
#define F54_ANALOG_CTRL33_0 		F54_ANALOG_CTRL31 + 3
#define F54_ANALOG_CTRL33_1			F54_ANALOG_CTRL31 + 4
#define F54_ANALOG_CTRL34_0 		F54_ANALOG_CTRL31 + 5
#define F54_ANALOG_CTRL34_1			F54_ANALOG_CTRL31 + 6
#define F54_ANALOG_CTRL35_0 		F54_ANALOG_CTRL31 + 7
#define F54_ANALOG_CTRL35_1			F54_ANALOG_CTRL31 + 8


#define F54_ANALOG_CTRL36_0   	F54_ANALOG_CTRL35_1 + 1
#define F54_ANALOG_CTRL36_1   	F54_ANALOG_CTRL36_0 + 1
#define F54_ANALOG_CTRL36_2   	F54_ANALOG_CTRL36_1 + 1
#define F54_ANALOG_CTRL36_3   	F54_ANALOG_CTRL36_2 + 1
#define F54_ANALOG_CTRL36_4   	F54_ANALOG_CTRL36_3 + 1
#define F54_ANALOG_CTRL36_5   	F54_ANALOG_CTRL36_4 + 1
#define F54_ANALOG_CTRL36_6   	F54_ANALOG_CTRL36_5 + 1
#define F54_ANALOG_CTRL36_7   	F54_ANALOG_CTRL36_6 + 1
#define F54_ANALOG_CTRL36_8   	F54_ANALOG_CTRL36_7 + 1
#define F54_ANALOG_CTRL36_9   	F54_ANALOG_CTRL36_8 + 1
#define F54_ANALOG_CTRL36_10  	F54_ANALOG_CTRL36_9 + 1
#define F54_ANALOG_CTRL36_11  	F54_ANALOG_CTRL36_10 + 1
#define F54_ANALOG_CTRL36_12  	F54_ANALOG_CTRL36_11 + 1
#define F54_ANALOG_CTRL36_13  	F54_ANALOG_CTRL36_12 + 1
#define F54_ANALOG_CTRL36_14  	F54_ANALOG_CTRL36_13 + 1
#define F54_ANALOG_CTRL36_15  	F54_ANALOG_CTRL36_14 + 1
#define F54_ANALOG_CTRL36_16  	F54_ANALOG_CTRL36_15 + 1
#define F54_ANALOG_CTRL36_17  	F54_ANALOG_CTRL36_16 + 1

#define F54_ANALOG_CTRL38_0 		F54_ANALOG_CTRL38
#define F54_ANALOG_CTRL38_1 		F54_ANALOG_CTRL38_0 + 1
#define F54_ANALOG_CTRL38_2 		F54_ANALOG_CTRL38_0 + 2
#define F54_ANALOG_CTRL38_3 		F54_ANALOG_CTRL38_0 + 3
#define F54_ANALOG_CTRL38_4 		F54_ANALOG_CTRL38_0 + 4
#define F54_ANALOG_CTRL38_5 		F54_ANALOG_CTRL38_0 + 5
#define F54_ANALOG_CTRL38_6 		F54_ANALOG_CTRL38_0 + 6
#define F54_ANALOG_CTRL38_7 		F54_ANALOG_CTRL38_0 + 7

#define F54_ANALOG_CTRL39_0 		F54_ANALOG_CTRL38_7 + 1
#define F54_ANALOG_CTRL39_1 		F54_ANALOG_CTRL39_0 + 1
#define F54_ANALOG_CTRL39_2 		F54_ANALOG_CTRL39_0 + 2
#define F54_ANALOG_CTRL39_3 		F54_ANALOG_CTRL39_0 + 3
#define F54_ANALOG_CTRL39_4 		F54_ANALOG_CTRL39_0 + 4
#define F54_ANALOG_CTRL39_5 		F54_ANALOG_CTRL39_0 + 5
#define F54_ANALOG_CTRL39_6 		F54_ANALOG_CTRL39_0 + 6
#define F54_ANALOG_CTRL39_7 		F54_ANALOG_CTRL39_0 + 7

#define F54_ANALOG_CTRL40_0 		F54_ANALOG_CTRL39_7 + 1
#define F54_ANALOG_CTRL40_1 		F54_ANALOG_CTRL40_0 + 1
#define F54_ANALOG_CTRL40_2 		F54_ANALOG_CTRL40_0 + 2
#define F54_ANALOG_CTRL40_3 		F54_ANALOG_CTRL40_0 + 3
#define F54_ANALOG_CTRL40_4 		F54_ANALOG_CTRL40_0 + 4
#define F54_ANALOG_CTRL40_5 		F54_ANALOG_CTRL40_0 + 5
#define F54_ANALOG_CTRL40_6 		F54_ANALOG_CTRL40_0 + 6
#define F54_ANALOG_CTRL40_7 		F54_ANALOG_CTRL40_0 + 7


#define F54_ANALOG_CTRL41    		F54_ANALOG_CTRL40_7 + 1
#define F54_ANALOG_CTRL42_0			F54_ANALOG_CTRL41 + 1
#define F54_ANALOG_CTRL42_1			F54_ANALOG_CTRL41 + 2


//#define F54_ANALOG_CTRL43
//#define F54_ANALOG_CTRL44
//#define F54_ANALOG_CTRL45
//#define F54_ANALOG_CTRL46
//#define F54_ANALOG_CTRL47
//#define F54_ANALOG_CTRL48
//#define F54_ANALOG_CTRL49
//#define F54_ANALOG_CTRL50
//#define F54_ANALOG_CTRL51
//#define F54_ANALOG_CTRL52
//#define F54_ANALOG_CTRL53
//#define F54_ANALOG_CTRL54

#define F54_ANALOG_CTRL55			F54_ANALOG_CTRL42_1 + 1
#define F54_ANALOG_CTRL56			F54_ANALOG_CTRL55 + 1
#define F54_ANALOG_CTRL57			F54_ANALOG_CTRL56 + 1
#define F54_ANALOG_CTRL58			F54_ANALOG_CTRL57 + 1

//Func1A Query Reg
#define F1A_0D_QUERY0					F1A_0D_QUERY_BASE
#define F1A_0D_QUERY1					F1A_0D_QUERY1 + 1
//Func1A Data Reg
#define F1A_0D_DATA0					F1A_0D_DATA_BASE
//Func1A Ctrl Reg
#define F1A_0D_CTRL0					F1A_0D_CONTROL_BASE
#define F1A_0D_CTRL1					F1A_0D_CTRL0 + 1
#define F1A_0D_CTRL2					F1A_0D_CTRL1 + 1

#define F1A_0D_CTRL7					F1A_0D_CTRL6 + 1
#define F1A_0D_CTRL8					F1A_0D_CTRL7 + 1

//Func31 Query Reg
#define F31_LED_QUERY0				F31_LED_QUERY_BASE
#define F31_LED_QUERY1				F31_LED_QUERY0 + 1
//Func31 Data Reg
//None
//Func31 Ctrl Reg
#define F31_LED_CTRL0_0					F31_LED_CONTROL_BASE
#define F31_LED_CTRL0_1					F31_LED_CTRL0_0  + 1
#define F31_LED_CTRL0_2					F31_LED_CTRL0_1  + 1
#define F31_LED_CTRL0_3					F31_LED_CTRL0_2  + 1
#define F31_LED_CTRL0_4					F31_LED_CTRL0_3  + 1
#define F31_LED_CTRL0_5					F31_LED_CTRL0_4  + 1
#define F31_LED_CTRL0_6					F31_LED_CTRL0_5  + 1
#define F31_LED_CTRL0_7					F31_LED_CTRL0_6  + 1


//------------------
u8 find_CP_IIC_address(void);
void read_all_reg(void);
void read_attn_reg(void);
void PDT_scan(void);
void constructFunc11(void);
void constructFunc01(void);
void constructFunc34(void);
void constructFunc54(void);
void constructFunc1A(void);
void constructFunc31(void);

//Function of Func11
void read_func11(void);
void CheckReportMode(void);
void Get_RMI_MaxPos(void);
void RMI_Reset(void);
void Clean_RMI_Reset(void);
void Set_F11_Rezero(void);

uint8_t convPosX2LCD(uint16_t fig_x);
uint16_t convPosY2LCD(uint16_t fig_y);


//Functions of Func54
// The following #defines are just needed to define an Image Report BUffer in memory
#define  CFG_F54_TXCOUNT              0x30           // Number of Transmitters on device under test
#define  CFG_F54_RXCOUNT              0x30           // Number of Receivers    on device under test

void f54_ForceCal(void);
void f54_ForceUpdate(void);
void f54_SetCapacitanceImageReport(void);
void f54_Set16BitImageReading(void);
void f54_TransmitterToTransmitterReport(void);
void f54_CheckImageReportData(void);
void f54_CheckPhyImgData(void);
void Check_RXTX_Count(void);
void fulfill_RX_tbl(void);
void fulfill_TX_tbl(void);
void Set_ForceUpdate(void);
void Set_ForceCal(void);
void check_IMBM(void);


//Function call - Func1A
void Ctrl_F1A_RM(u8 btnmode);
void Ctrl_F1A_FilterMode(u8 btnfiltermode);
void read_func1A(void);

//Function of Func34
void SynaReadBootloadID(void);
void SynaWriteBootloadID(void);
void SynaReadConfigInfo(void);
void SynaReadFirmwareInfo(void);
void SynaWaitForATTN(void);
void SynaWaitATTN(void);

void SynaEnableFlashing(void);
void SynaFinalizeReflash(void);

void SynaInitialize(void);
void eraseConfigBlock(void);
void SynaProgramConfiguration(void);
void ConfigBlockReflash(void);
void SynaFlashFirmwareWrite(void);
void SynaProgramFirmware(void);
void CompleteReflash(void);
bool fimrwareRevisionCheck(void);
void SynaBootloaderLock(void);

unsigned long CRC_Calculate(unsigned short *data, unsigned short len);


//Global definition
#define	Page_Select_register		0xFF
#define	PdtTop									0xEF
#define	PdtCheck_Start					0xEE

#define F81_RMI_QUERY_bass			0x84
#define Finger_Reg_Size					5
#define IMG_Window_size				8

#define RMI_Default_PAGE				0x00
#define RMI_F05_PAGE						0x01

extern bool HasFlashInt;
extern bool HasStatusInt;
extern bool HasAbs0Int;
extern bool HasAbs1Int;
extern bool HasButtonInt;
extern bool HasBistInt;
extern bool HasAnalogInt;


#endif
/* __RMI_H */
