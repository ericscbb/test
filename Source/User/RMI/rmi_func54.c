/*
   +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   Copyright (c) 2011 Synaptics, Inc.

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
/*
Function 54
ReportType (F54_AD_Data0)
Specifies the type of data that will be collected and reported in the FIFOData register when the GetReport bit (F54_AD_Cmd0 bit 0) is set.
ReportType = 0: Reserved
ReportType = 1: Normalized 8-Bit Image Report
ReportType = 2: Normalized 16-Bit Image Report
ReportType = 3: Raw 16-Bit Image Report
ReportType = 4: Transmitter-to-Transmitter Report
ReportType = 5: Transmitter-to-Transmitter Short (No Sensor) Report
ReportType = 6: Transmitter Open (No Sensor) Report
ReportType = 7: Receiver-to-Receiver Report
ReportType = 8: Receiver Open (No Sensor) Report
ReportType = 9: High-Resistance Report
ReportType = 10: TX_GND Report
ReportType = 11-255: Reserved
*/

#include "usually.h"
#include "rmi.h"

u8 command;
u8 page;
u8 tmp2bufs[2];


u8 ReceiverElectrodeCount;
u8 TransmitterElectrodeCount;
u8 RXMAP_Num;
u8 TXMAP_Num;
u16 length;
u16 IM,RR,BM;
//u16 color_bar[10]= {WHITE,RED, ORANGE, YELLOW, GREEN, BLUE, DARKBLUE,BRRED, GRAY,BRED};
u16 color_bar[10]= {WHITE, GREEN,YELLOW, CYAN, BLUE, DARKBLUE,MAGENTA, ORANGE,MAROON,RED};



extern u8 F54_Query_Base;
extern u8 F54_Data_Base;
extern u8 F01_RMI_Ctrl0;
extern u8 F54_Command_Base;


float LowerLimit[20][28] =
{
  {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3,0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3},
  {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3,0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3},
  {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3,0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3},
  {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3,0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3},
  {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3,0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3},
  {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3,0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3},
  {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3,0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3},
  {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3,0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3},
  {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3,0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3},
  {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3,0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3},
  {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3,0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3},
  {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3,0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3},
  {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3,0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3},
  {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3,0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3},
  {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3,0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3},
  {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3,0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3},
  {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3,0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3},
  {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3,0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3},
  {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3,0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3},
  {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3,0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3},

};

float UpperLimit[20][28] =
{
  {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5,5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5},
  {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5,5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5},
  {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5,5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5},
  {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5,5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5},
  {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5,5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5},
  {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5,5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5},
  {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5,5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5},
  {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5,5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5},
  {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5,5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5},
  {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5,5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5},
  {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5,5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5},
  {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5,5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5},
  {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5,5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5},
  {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5,5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5},
  {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5,5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5},
  {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5,5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5},
  {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5,5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5},
  {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5,5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5},
  {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5,5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5},
  {5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5,5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5, 5.5}
};


char Result[20][28];


//------
void f54_ForceCal(void)
{
  command = 0x02;
  writeRMI(F54_Command_Base, &command, 1);
}

void f54_ForceUpdate(void)
{
  // Under normal circumstances, the analog settings are read from the F54 control registers at
  // startup and propagated into the Touch Controller circuits.  Changing these settings while
  // the system is running can be very disruptive to the data being gathered.  As a result,
  // updates to the analog control registers will only be processed after the ForceUpdate
  // register is set to ‘1’.  The ForceUpdate command bit will clear once the changes are updated.
  // The next frame of data to be acquired after the command bit clears will have been acquired
  // using the new settings.

  // ForceUpdate is at bit 2 of the F$54 command register.

  command = 0x04;
  writeRMI(F54_Command_Base, &command, 1);
}


void f54_SetCapacitanceImageReport(void)
{

  printf("Starting setting CapacitanceImageReport.....\r\n");

  // Page 0  & Enabling only the analog image reporting interrupt, and turn off the rest
  command = 0x08;
  page = 0;

  writeRMI(Page_Select_register, &page, 1);
  writeRMI(F01_RMI_Ctrl1, &command, 1);

  // Page 1 & Set report mode to to run the AutoScan
  page = 1;
  command = 0x03;

  writeRMI(Page_Select_register, &page, 1);
  writeRMI(F54_Data_Base, &command, 1);

  command = 0x00;
  writeRMI(F54_Data_LowIndex, &command, 1);
  writeRMI(F54_Data_HighIndex, &command, 1);


  // Set the GetReport bit to run the AutoScan
  command = 0x01;
  writeRMI(F54_Command_Base, &command, 1);

}

void f54_CheckImageReportData(void)
{
  u16 i, j, k;
  s16 ImageArray[CFG_F54_RXCOUNT][CFG_F54_TXCOUNT];
  u8 ImageBuffer[CFG_F54_RXCOUNT*CFG_F54_TXCOUNT*2];
  extern bool LimitCheck;

  for (i = 0; i < CFG_F54_RXCOUNT; i++)
  {
    for (j = 0; j < CFG_F54_TXCOUNT; j++)
    {
      ImageArray[i][j] = 0;
    }
  }

  for (i = 0; i < CFG_F54_RXCOUNT*CFG_F54_TXCOUNT*2; i++)
  {
    ImageBuffer[i] = 0;
  }

  // Page 1
  //page = 1;
  //writeRMI(Page_Select_register, &page, 1);

  /*
  	   do {
  	      readRMI(F54_Command_Base, &command, 1);

  		  //printf("Waiting for report ready!!!....command:0x%x\r\n",command);
  	   } while (command == 0x01);
  */

  k = 0;
  printf("Read F54_Data_Buffer(0x%x). k:%d, length:%d\r\n",F54_Data_Buffer,k,length);

  readRMI(F54_Data_Buffer, ImageBuffer, length);
  printf("ImageBuffer[0]:0x%x,ImageBuffer[1]:0x%x,ImageBuffer[10]:0x%x.\r\n",ImageBuffer[0],ImageBuffer[1],ImageBuffer[10]);

  printf("ReceiverElectrodeCount:%d, TransmitterElectrodeCount:%d, length:%d.\r\n",ReceiverElectrodeCount,TransmitterElectrodeCount,length);

  for (j = 0; j < TXMAP_Num ; j++)
  {
    for (i = 0; i < RXMAP_Num; i++)
    {
      ImageArray[i][j] = (ImageBuffer[k] | ((s16)ImageBuffer[k+1] << 8));
      k = k + 2;
    }
  }

  printf("ImageArray[0 - %d][0 - %d] \r\n",ReceiverElectrodeCount-1, TransmitterElectrodeCount-1);

  for (i = 0; i < RXMAP_Num; i++)
  {
    for (j = 0; j < TXMAP_Num ; j++)
    {
      printf("%ld	",ImageArray[i][j]);
      k = k + 2;
    }
    printf("\r\n");
  }
  printf("\r\n");
  //printf("ImageArray[0][0]:%d 0.0009768 * ImageArray[0][0] = %f.\r\n",ImageArray[0][0],(float)ImageArray[0][0] * 0.0009768);

  // Check against test limits
  if(LimitCheck)
  {
    printf("\nThe test result:\r\n");

    for (i = 0; i < RXMAP_Num; i++)
    {
      printf("[ ");
      for (j = 0; j < TXMAP_Num; j++)
      {
        if ((( (float)ImageArray[i][j] * 0.0009768) < 5.5) && (( (float)ImageArray[i][j] * 0.0009768) > 0.3))
          Result[i][j] = 'P'; //Pass
        else
        {
          Result[i][j] = 'F'; //Fail
          //printf("(float)UpperLimit[%d][%d]: %f",i,j,(float)UpperLimit[i][j]);
          //printf("(float)LowerLimit[%d][%d]: %f",i,j,(float)LowerLimit[i][j]);
        }

//        printf("%c (%e), ", Result[i][j], ((float)ImageArray[i][j] * 0.0009768));
        printf("%c, ", Result[i][j]);
      }
      printf("]\r\n");
    }
  }
}

//-----------------------------
// Return physical image data format
//-----------------------------
void f54_CheckPhyImgData(void)
{
  u16 i, j, k;
  s16 ImageArray[CFG_F54_RXCOUNT][CFG_F54_TXCOUNT];
  s8 IMG_Window[CFG_F54_RXCOUNT][CFG_F54_TXCOUNT];
  u8 ImageBuffer[CFG_F54_RXCOUNT*CFG_F54_TXCOUNT*2];
  extern bool LimitCheck;
  extern u16 fig_color[10];

  k = 0;
//  printf("Read F54_Data_Buffer(0x%x). k:%d, length:%d\r\n",F54_Data_Buffer,k,length);

  readRMI(F54_Data_Buffer, ImageBuffer, length);
//  printf("ImageBuffer[0]:0x%x,ImageBuffer[1]:0x%x,ImageBuffer[10]:0x%x.\r\n",ImageBuffer[0],ImageBuffer[1],ImageBuffer[10]);

//  printf("ReceiverElectrodeCount:%d, TransmitterElectrodeCount:%d, length:%d.\r\n",ReceiverElectrodeCount,TransmitterElectrodeCount,length);

  for (j = 0; j < TXMAP_Num ; j++)
  {
    for (i = 0; i < RXMAP_Num; i++)
    {
      ImageArray[i][j] = (ImageBuffer[k] | ((s16)ImageBuffer[k+1] << 8));
      if(ImageArray[i][j] >= 0) IMG_Window[i][j]=	  (u8)((u16) (ImageArray[i][j]/30) + 1);
      else IMG_Window[i][j] = 0;

      k = k + 2;
    }
  }

  printf("ImageArray[0 - %d][0 - %d] = { \r\n",RXMAP_Num-1, TXMAP_Num-1);

  for (i = 0; i < RXMAP_Num; i++)
  {
    for (j = 0; j < TXMAP_Num ; j++)
    {
      printf("%ld	",ImageArray[i][j]);
//      LCD_FillRectangle(5+i*IMG_Window_size,60+5+j*IMG_Window_size,5+(i+1)*IMG_Window_size,60+5+(j+1)*IMG_Window_size,fig_color[(IMG_Window[i][j])]);
      LCD_FillRectangle(5+j*IMG_Window_size,60+5+i*IMG_Window_size,5+(j+1)*IMG_Window_size,60+5+(i+1)*IMG_Window_size,color_bar[(IMG_Window[i][j])]);

    }
    printf("\r\n");
  }
  printf("}\r\n");

}

void f54_Set16BitImageReading(void)
{
  extern bool LimitCheck;
  extern bool b_infinite;
  extern u8  I2C_Address;

//  LimitCheck = FALSE;

  printf("Starting 16Bit Image Reading.....\r\n");

  // Page 0  & Enabling only the analog image reporting interrupt, and turn off the rest
  command = 0x08;
  page = 0;

  writeRMI(Page_Select_register, &page, 1);
//  printf("16Bit Image check:F01_RMI_Ctrl1:0x%x. \r\n",F01_RMI_Ctrl1);
  writeRMI(F01_RMI_Ctrl1, &command, 1);
//  printf("F01_RMI_Ctrl1: 0x%x = 0x%x.",F01_RMI_Ctrl1,I2C_RMI_BufferRead(I2C_Address,F01_RMI_Ctrl1));

  // Page 1 & Set report mode to read normalized 16-Bit image
  page = 1;
  command = 0x02;

  writeRMI(Page_Select_register, &page, 1);
  writeRMI(F54_Data_Base, &command, 1);

//  Set_ForceUpdate();

  while(b_infinite)
  {

    command = 0x00;
    writeRMI(F54_Data_LowIndex, &command, 1);
    writeRMI(F54_Data_HighIndex, &command, 1);

    // Set GetReport bit to acquire an image
    command = 0x01;
    writeRMI(F54_Command_Base, &command, 1);

    do
    {
      readRMI(F54_Command_Base, &command, 1);

      //printf("Waiting for report ready!!!....command:0x%x\r\n",command);
    }
    while (command == 0x01);

  }
}

//---------------
// Read Full ASIC RX/TX electroid Count
//---------------
void Check_RXTX_Count(void)
{

// Page 1 - Func54 find RX/TX num
  page = 1;
  writeRMI(Page_Select_register, &page, 1);

  readRMI(F54_Query0, &ReceiverElectrodeCount, 1);
  readRMI(F54_Query1, &TransmitterElectrodeCount, 1);

  length = ReceiverElectrodeCount * TransmitterElectrodeCount * 2;
  printf("Full ASIC Receiver Electrode Count:%d, Transmitter Electrode Count:%d, length:%d.\r\n",ReceiverElectrodeCount,TransmitterElectrodeCount,length);



}
//---------------
// Find RX order
//---------------
void fulfill_RX_tbl(void)
{
  u8 i;
  u8 rx_tbl[CFG_F54_RXCOUNT];
  extern u8 F54_Control_Base;

//  printf("F54 Ctrl: Receiver Electrode Count:%d , F54_ANALOG_CTRL15_0:0x%x.\r\n",ReceiverElectrodeCount,F54_ANALOG_CTRL15_0);

  readRMI(F54_ANALOG_CTRL15_0, &rx_tbl, ReceiverElectrodeCount);
  RXMAP_Num = ReceiverElectrodeCount;

  printf("RX order : [ ");
  for(i=0; i<ReceiverElectrodeCount; i++)	
  {
    if(rx_tbl[i] == 0xFF)  	 { RXMAP_Num = i;	break;}
    else printf("R%d ",rx_tbl[i]);
  }
  printf("].\r\n");
  printf("F54 Ctrl: RX Mapping Number:%d , F54_ANALOG_CTRL15_0:0x%x.\r\n",RXMAP_Num,F54_ANALOG_CTRL15_0);

}


//---------------
// Find TX order
//---------------
void fulfill_TX_tbl(void)
{
  u8 i;
  u8 tx_tbl[CFG_F54_TXCOUNT];
  extern u8 F54_Control_Base;
  extern u8 F54_ANALOG_CTRL16_0;

//  printf("F54 Ctrl: Transmitter Electrode Count:%d , F54_ANALOG_CTRL16_0:0x%x.\r\n",TransmitterElectrodeCount,F54_ANALOG_CTRL16_0);

  readRMI(F54_ANALOG_CTRL16_0, &tx_tbl, TransmitterElectrodeCount);
  TXMAP_Num = TransmitterElectrodeCount;

  printf("TX order : [ ");
  for(i=0; i<TransmitterElectrodeCount; i++)	
  {
    if(tx_tbl[i] == 0xFF)  	 { TXMAP_Num = i;	break;}
	else printf("T%d ",tx_tbl[i]);
  }
  printf("].\r\n");
  printf("F54 Ctrl: TX Mapping Number:%d , F54_ANALOG_CTRL15_0:0x%x.\r\n",TXMAP_Num,F54_ANALOG_CTRL16_0);
}

//---------------
// ForceUpdate
//---------------
void Set_ForceUpdate(void)
{
// Page 1 - Func54 find RX/TX num
  page = 1;
  command = 0x04;

  printf("F54 Cmd: Set_ForceUpdate.\r\n");
  writeRMI(Page_Select_register, &page, 1);
  writeRMI(F54_Data_Base, &command, 1);

  do
  {
    readRMI(F54_Command_Base, &command, 1);

    printf("Waiting for ForceUpdate ready!!!....command:0x%x\r\n",command);
  }
  while ((command & 0x04));
}

//---------------
// ForceCal
//---------------
void Set_ForceCal(void)
{
// Page 1 - Func54 find RX/TX num
  page = 1;
  command = 0x02;

  printf("F54 Cmd: Set_ForceCal.\r\n");
  writeRMI(Page_Select_register, &page, 1);
  writeRMI(F54_Data_Base, &command, 1);
}


//------------------------------
// Return IM & Burst span Metric value
//------------------------------
void check_IMBM(void)
{
// Page 1 - Func54 find IM

  page = 1;
  writeRMI(Page_Select_register, &page, 1);

  readRMI(F54_ANALOG_DATA6_0, tmp2bufs, 2);

  IM = ((u16)tmp2bufs[1] << 8) + tmp2bufs[0];
//  printf("F54 Data: IM:%u.\r\n",IM);
  LCD_ShowNum(24,30,IM,5);

  readRMI(F54_ANALOG_DATA7_0, tmp2bufs, 2);

  RR= ((u16)tmp2bufs[1] << 8) + tmp2bufs[0];
//  printf("F54 Data: Report rate:%d.\r\n",RR);
  LCD_ShowNum(100,30,RR,4);


  readRMI(F54_ANALOG_DATA8_0, tmp2bufs, 2);

  BM = ((u16)tmp2bufs[1] << 8) + tmp2bufs[0];
//  printf("F54 Data: BM:%u.\r\n",BM);
  LCD_ShowNum(170,30,BM,5);


}
#if 0

void f54_TransmitterToTransmitterReport(void)
{
  unsigned short numberOfRows;
  unsigned short numberOfColumns;
  int i, j, k;
  int length;

  int ImageArray[CFG_F54_TXCOUNT] [CFG_F54_TXCOUNT] ;

  int ImageBuffer[CFG_F54_TXCOUNT*CFG_F54_TXCOUNT];

  unsigned short command;

  readRMI(F54_Query_1, &numberOfRows, 1);
  length = numberOfRows * numberOfRows;

  // Enabling only the analog image reporting interrupt, and turn off the rest
  command = 0x08;
  writeRMI(F01_RMI_Ctrl1, &command, 1);

  k = 0;
  // Set report mode to run Tx-to-Tx
  command = 0x04;
  writeRMI(F54_Data_Base, &command, 1);

  command = 0x00;
  writeRMI(F54_Data_LowIndex, &command, 1);
  writeRMI(F54_Data_HighIndex, &command, 1);

  // Set the GetReport bit to run Tx-to-Tx
  command = 0x01;
  writeRMI(F54_Command_Base, &command, 1);

  // Wait until the command is completed
  do
  {
    readRMI(F54_Command_Base, &command, 1);
  }
  while (command == 0x01);

  readRMI(F54_Data_Buffer, &ImageBuffer[0], length);

  for (i = 0; i < numberOfRows; i++)
  {
    for (j = 0; j < numberOfRows; j++)
    {
      ImageArray[i][j] = (int)ImageBuffer[k];
      k++;
    }
  }

  // Check against test limits
  printf("\nThe test result:\n");
  for (i = 0; i < 20; i++)
  {
    printf("[ ");
    for (j = 0; j < 20; j++)
    {
      if (ImageArray[i][j] == Limit[j]) &&
        Result[i][j] = "P" /*Pass*/
                       else
                         Result[i][j] = "F" /*Fail*/
                                        printf("%c, ", Result[i][j]);
    }
    printf("]\n");
  }
}
#endif

