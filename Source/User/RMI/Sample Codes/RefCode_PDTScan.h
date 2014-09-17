/*
   +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   Copyright (c) 2008 Synaptics, Inc.
   
   Permission is hereby granted, free of charge, to any person obtaining a copy of 
   this software and associated documentation files (the "Software"), to deal in 
   the Software without restriction, including without limitation the rights to use, 
   copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
   Software, and to permit persons to whom the Software is furnished to do so, 
   subject to the following conditions:
   
   The above copyright notice and this permission notice shall be included in all 
   copies or substantial portions of the Software.
   
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
   SOFTWARE.
  
   +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#ifndef __PDT_H__
#define __PDT_H__

#define PDT_ADDR		  0xEF
#define PDT_SIZE		  6
#define NUM_RMI_FUNCS	  17
#define NUM_QUERY_REGS    78
#define NUM_F01_Q    	  21
#define NUM_F11_Q	      10

#define TOT_INDX  0
#define F01_INDX	1
#define F11_INDX	5

#define F01_Q	   0
#define F11_Q	   F19_Q + NUM_F01_Q

#define ReportMode               (tmpBuf[F11_2D_Ctrl0_9 & 0xFF] & 0x03)

#define ManufacturerID           (RMI_Query_Regs[F01_Q + 0])
#define NonCompliant             (RMI_Query_Regs[F01_Q + 1] & 0x02)
#define CustomMap                (RMI_Query_Regs[F01_Q + 1] & 0x02)
#define ProductInfo1             (RMI_Query_Regs[F01_Q + 2] & 0x7F)
#define ProductInfo2             (RMI_Query_Regs[F01_Q + 3] & 0x7F)
#define DateCodeYear             (RMI_Query_Regs[F01_Q + 4] & 0x1F)
#define DateCodeMonth            (RMI_Query_Regs[F01_Q + 5] & 0x0F)
#define DateCodeDay              (RMI_Query_Regs[F01_Q + 6] & 0x1F)
#define TesterID14_7             (RMI_Query_Regs[F01_Q + 7] & 0x7F)
#define TesterID6_0              (RMI_Query_Regs[F01_Q + 8] & 0x7F)
#define SerialNumber14_7         (RMI_Query_Regs[F01_Q + 9] & 0x7F)
#define SerialNumber6_0          (RMI_Query_Regs[F01_Q + 10] & 0x7F)
#define ProductID                (RMI_Query_Regs[F01_Q + 11])

#define NumberOfSensors          (RMI_Query_Regs[F11_Q + 0] & 0x07)
#define Configurable             (RMI_Query_Regs[F11_Q + 1] & 0x80)
#define HasSensitivityAdjust     (RMI_Query_Regs[F11_Q + 1] & 0x40)
#define HasGestures              (RMI_Query_Regs[F11_Q + 1] & 0x20)
#define HasAbs                   (RMI_Query_Regs[F11_Q + 1] & 0x10)
#define HasRel                   (RMI_Query_Regs[F11_Q + 1] & 0x08)
#define NumberOfFingers          (RMI_Query_Regs[F11_Q + 1] & 0x07)
#define NumberOfXElectrodes      (RMI_Query_Regs[F11_Q + 2] & 0x1F)
#define NumberOfYElectrodes      (RMI_Query_Regs[F11_Q + 3] & 0x1F)
#define MaximumElectrodes        (RMI_Query_Regs[F11_Q + 4] & 0x1F)
#define HasAnchoredFinger        (RMI_Query_Regs[F11_Q + 5] & 0x04)
#define AbsDataSize              (RMI_Query_Regs[F11_Q + 5] & 0x05)

extern unsigned short F01_RMI_Query0_20;
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
extern unsigned short F01_RMI_Ctrl0;
extern unsigned short F01_RMI_Ctrl1;
extern unsigned short F01_RMI_Ctrl2;
extern unsigned short F01_RMI_Data0;
extern unsigned short F01_RMI_Data1;
extern unsigned short F01_RMI_Cmd0;

extern unsigned short F54_Query_Base;
#define F54_Query_1    F54_Query_Base + 1
#define F54_Query_3    F54_Query_Base + 3
#define F54_Query_4    F54_Query_Base + 4
extern unsigned short F54_Control_Base;
extern unsigned short F54_Data_Base;
#define F54_Data_LowIndex F54_Data_Base + 1
#define F54_Data_HighIndex F54_Data_Base + 2
#define F54_Data_Buffer F54_Data_Base + 3
extern unsigned short F54_Command_Base;

extern unsigned short F11_2D_Query0;
extern unsigned short F11_2D_Query1_4;
#define F11_2D_Query1      F11_2D_Query1_4
#define F11_2D_Query2      F11_2D_Query1_4 + 1
#define F11_2D_Query3      F11_2D_Query1_4 + 2
#define F11_2D_Query4      F11_2D_Query1_4 + 3
extern unsigned short F11_2D_Query5;
extern unsigned short F11_2D_Query6;
extern unsigned short F11_2D_Query7_8;
#define F11_2D_Query7      F11_2D_Query7_8
#define F11_2D_Query8      F11_2D_Query7_8 + 1
extern unsigned short F11_2D_Ctrl0_9;
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
extern unsigned short F11_2D_Ctrl10;
extern unsigned short F11_2D_Ctrl11;
extern unsigned short F11_2D_Ctrl12;
extern unsigned short F11_2D_Ctrl13;
extern unsigned short F11_2D_Ctrl14;
extern unsigned short F11_2D_Ctrl15;
extern unsigned short F11_2D_Ctrl16;
extern unsigned short F11_2D_Ctrl17;
extern unsigned short F11_2D_Ctrl18;
extern unsigned short F11_2D_Ctrl19;
extern unsigned short F11_2D_Data0;
extern unsigned short F11_2D_Data1_5;
#define F11_2D_Data1     F11_2D_Data1_5
#define F11_2D_Data2     F11_2D_Data1_5 + 1
#define F11_2D_Data3     F11_2D_Data1_5 + 2
#define F11_2D_Data4     F11_2D_Data1_5 + 3
#define F11_2D_Data5     F11_2D_Data1_5 + 4
extern unsigned short F11_2D_Data6_7;
#define F11_2D_Data6     F11_2D_Data6_7
#define F11_2D_Data7     F11_2D_Data6_7 + 1
extern unsigned short F11_2D_Data8;
extern unsigned short F11_2D_Data9;
extern unsigned short F11_2D_Data10;
extern unsigned short F11_2D_Data11;
extern unsigned short F11_2D_Data12;
extern unsigned short F11_2D_Cmd0;



typedef struct {
   U16 status;
   U16 enable;
   U16 numRegs;
   U16 mask[7];
} intSrc;

extern unsigned short numInts;
extern unsigned short currPage;
extern int pageNum[NUM_RMI_FUNCS];
extern intSrc intMask[NUM_RMI_FUNCS];
extern unsigned int RMI_Query_Regs[NUM_QUERY_REGS];

void constructRMI();
void printRMI4Addresses(unsigned short viewPublic);

#endif

