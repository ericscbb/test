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
   PDT.c

   Page Description Table (PDT). This reads the PDT and constructs the RMI register
   map from it. A bitmask for each function is created for interrupts (Functions $01).
*/

#include "math.h"

unsigned int F01_RMI_Query0_20 = 0;
unsigned int F01_RMI_Ctrl0 = 0;
unsigned int F01_RMI_Ctrl1 = 0;
unsigned int F01_RMI_Ctrl2 = 0;
unsigned int F01_RMI_Data0 = 0;
unsigned int F01_RMI_Data1 = 0;
unsigned int F01_RMI_Cmd0 = 0;

unsigned int F05_IMG_Query0_5 = 0;
unsigned int F05_IMG_Ctrl0_5 = 0;
unsigned int F05_IMG_Data0_1 = 0;
unsigned int F05_IMG_Data2 = 0;
unsigned int F05_IMG_Cmd0 = 0;

unsigned int F11_2D_Query0 = 0;
unsigned int F11_2D_Query1_4 = 0;
unsigned int F11_2D_Query5 = 0;
unsigned int F11_2D_Query6 = 0;
unsigned int F11_2D_Query7_8 = 0;
unsigned int F11_2D_Ctrl0_9 = 0;
unsigned int F11_2D_Ctrl10 = 0;
unsigned int F11_2D_Ctrl11 = 0;
unsigned int F11_2D_Ctrl12 = 0;
unsigned int F11_2D_Ctrl13 = 0;
unsigned int F11_2D_Ctrl14 = 0;
unsigned int F11_2D_Ctrl15 = 0;
unsigned int F11_2D_Ctrl16 = 0;
unsigned int F11_2D_Ctrl17 = 0;
unsigned int F11_2D_Ctrl18 = 0;
unsigned int F11_2D_Ctrl19 = 0;
unsigned int F11_2D_Data0 = 0;
unsigned int F11_2D_Data1_5 = 0;
unsigned int F11_2D_Data6_7 = 0;
unsigned int F11_2D_Data8 = 0;
unsigned int F11_2D_Data9 = 0;
unsigned int F11_2D_Data10 = 0;
unsigned int F11_2D_Data11 = 0;
unsigned int F11_2D_Data12 = 0;
unsigned int F11_2D_Cmd0 = 0;

unsigned int F54_Query_Base = 0;
unsigned int F54_Control_Base = 0;
unsigned int F54_Data_Base = 0;
unsigned int F54_Command_Base = 0;

unsigned short RMI_Query_Regs[NUM_QUERY_REGS];

unsigned short numInts = 0;

intSrc intMask[NUM_RMI_FUNCS];
int pageNum[NUM_RMI_FUNCS];

intSrc intEnable[NUM_RMI_FUNCS];
intSrc intStatus[NUM_RMI_FUNCS];

unsigned short mask[9] = { 0, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF };
unsigned short currPage = 0;

void constructF01(void);
void constructPublicRegs(void); 

void buildInterruptMask(unsigned short funcNum, unsigned short num);

/* constructRMI
 * Construct the RMI register map based on the Page Description
 * Tables. This will initialize the register address arrays and
 * interrupt masks
 *
 * First, finds Function 01 addresses to build 
 * interrupt masks, then builds other functions' addresses
 */
void constructRMI()
{
	unsigned short j, tmp = 255;
	unsigned short FUNC_EXISTS = 0;
	unsigned short in[10];	
	int i, tmp16, l, m;
    int numRegs = 0;

    numInts = 0;

    for(i = 1; i < NUM_RMI_FUNCS; i++) 
	{
      pageNum[i] = -1;
	}

	i = 0;

    constructF01();

	do {
			    
	   readRMI((i << 8) | PDT_ADDR, &tmp, 1);

       if(tmp & 0x40) 
	   {
           printf("\nNon-Standard Page Description Table not supported\n");
           return;
       }

       // reset flag
       FUNC_EXISTS = 0;
	   // reset func addr info index	
	   j = 1;			

       while(1) 
	   {
           //printf("Reading PDT on Page %02X...", i);
           readRMI((i << 8) | (PDT_ADDR - PDT_SIZE*j), in, 6);
      	   readRMI((i << 8) | 0xFF, &tmp, 1);
           
		   j++;

		   if(in[5] == 0x00) 
		   {   // No more functions on this page
			   if(FUNC_EXISTS == 0) 
			   {
			       constructPublicRegs();
                   return;
			   } else {
					i++;
               }
			   break;
		   } else if(in[5] == 0x01) {	   
		       // Function01
               readRMI(F01_RMI_Query0, &RMI_Query_Regs[F01_Q], NUM_F01_Q);
               buildInterruptMask(F01_INDX, in[4] & 0x07);
		   } else if (in[5] == 0x54) {
		   		F54_Query_Base = (i << 8) | in[0];
				F54_Command_Base = (i << 8) | in[1];
				F54_Control_Base = (i << 8) | in[2];
				F54_Data_Base = (i << 8) | in[3];
		  } else if(in[5] == 0x11) {		
		        // Function11
				F11_2D_Query0 = (i << 8) | in[0];
				F11_2D_Cmd0 = (i << 8) | in[1];
				F11_2D_Ctrl0_9 = (i << 8) | in[2];
				F11_2D_Data0 = (i << 8) | in[3];
                pageNum[F11_INDX] = i;
                readRMI(F11_2D_Query0, &RMI_Query_Regs[F11_Q], NUM_F11_Q);
                buildInterruptMask(F11_INDX, in[4] & 0x07);
		  } else {
				printf("\n-- RMI Function $%02X not supported --\n", in[5]);
                numInts += in[4] & 0x07;
          }
		  FUNC_EXISTS = 1;
      }
   } while(FUNC_EXISTS == 1);
}

/* constructF01()
 * finds Function $01's addresses
 * to help build interrupt masks
 */
void constructF01(void)
{
   unsigned short j, tmp = 255;
   unsigned short FUNC_EXISTS = 0;
   unsigned short in[10];	
   unsigned int i, tmp16, l, m;
   unsigned int numRegs = 0;

   numInts = 0;

   for(i = 1; i < NUM_RMI_FUNCS; i++) 
   {
      pageNum[i] = -1;
   }

   i = 0;

   for(i = 0; i <= 0xFF;) 
   {
      // reset flag 
      FUNC_EXISTS = 0;	
	  // reset func addr info index
	  j = 1;				

      while(1) 
	  {
         readRMI((i << 8) | (PDT_ADDR - PDT_SIZE*j), in, 6);

         j++;

   		 if(in[5] == 0x00) 
		 {	// No more functions on this page
   			if(FUNC_EXISTS == 0) 
			{
               if(i < 0x80) 
			   {
                  printf("\nDidn't find Function $01!!\n");
               }
               return;
   			}
            i++;
   			break;
   	    } else if(in[5] == 0x01) {
		    // Function01	   
            F01_RMI_Data0 = (i << 8) | in[3];
   			F01_RMI_Query0_20 = (i << 8) | in[0];
   			F01_RMI_Cmd0 = (i << 8) | in[1];
   			F01_RMI_Ctrl0 = (i << 8) | in[2];
            pageNum[F01_INDX] = i;
            tmp = 0x00;
			// Clear reset status
            writeRMI(F01_RMI_Ctrl0, &tmp, 1);   
            i = 0x80;
            break;
		}
        FUNC_EXISTS = 1;
      }
   }
}


void constructPublicRegs(void)
{
	unsigned short tmp = 255;
	unsigned int tmp16;
    unsigned int  numRegs = 0;

	if(pageNum[F01_INDX] >= 0) 
	{  
	  // Function01
      numRegs += 24;

      F01_RMI_Ctrl1 = F01_RMI_Ctrl0 + 1;
      F01_RMI_Data1 = F01_RMI_Data0 + 1;
      
      tmp = (unsigned short)ceil((double)numInts/8);
      numRegs += 2*tmp;
   }
   if(pageNum[F11_INDX] >= 0) 
   {		
      // Function11
      numRegs += 1;

      F11_2D_Query1_4 = F11_2D_Query0 + 1;

      if(NumberOfSensors > 0) 
	  {
         printf("More than 1 sensor not yet supported\n");
         return;
      }

      if(HasAbs) 
	  {
         F11_2D_Query5 = F11_2D_Query1_4 + 4;
      } else {
         F11_2D_Query5 = F11_2D_Query1_4 + 3;
      }

      if(HasRel)
	  {
         F11_2D_Query6 = F11_2D_Query5 + 1;
      } else {
         F11_2D_Query6 = F11_2D_Query5;
      }

      if(HasGestures) 
	  {
         F11_2D_Query7_8 = F11_2D_Query6 + 1;
         numRegs += F11_2D_Query7_8 - F11_2D_Query0 + 2;
     
      } else {
         F11_2D_Query7_8 = F11_2D_Query6;
         numRegs += F11_2D_Query7_8 - F11_2D_Query0;
      }

      // Initialize Control Register Addresses based on
      // Query Register values
      F11_2D_Ctrl10 = F11_2D_Ctrl0_9 + 10;
      F11_2D_Ctrl11 = F11_2D_Ctrl10 + (RMI_Query_Regs[F11_Q + 7] > 0 ? 1 : 0);
      F11_2D_Ctrl12 = F11_2D_Ctrl11 + (RMI_Query_Regs[F11_Q + 8] > 0 ? 1 : 0);
      F11_2D_Ctrl13 = F11_2D_Ctrl12 + MaximumElectrodes;
      F11_2D_Ctrl14 = F11_2D_Ctrl13 + MaximumElectrodes;

      F11_2D_Ctrl15 = F11_2D_Ctrl14 + HasSensitivityAdjust;

      // Initialize Data Register Addresses based on
      // Query Register values
      if(NumberOfFingers >= 5) 
	  {
         tmp = 3;
         tmp16 = 10;
      } else {
         tmp = (U08)ceil((double)(NumberOfFingers + 1)/4);
         tmp16 = NumberOfFingers + 1;
      }
      F11_2D_Data1_5 = F11_2D_Data0 + tmp;

      if(HasAbs && AbsDataSize == 0) 
	  {
         F11_2D_Data6_7 = F11_2D_Data1_5 + 5 * tmp16;
      } else if (AbsDataSize != 0) {
         printf("Abs Data Size != 0 not supported: 0x%02X\n", AbsDataSize);
         return;
      } else {
         F11_2D_Data6_7 = F11_2D_Data1_5;               
      }
      F11_2D_Data8 = F11_2D_Data6_7 + (HasRel ? 3 : 0);
    }
}

/* buildInterruptMask
 */
void buildInterruptMask(unsigned short funcNum, unsigned short num)
{
   unsigned short numIntFields;
   unsigned short totInts; 
   int i;
   
   if(num == 7) 
   {
      printf("\nInterrupt count >= 7 per function not supported.\n");
      return;
   }

   totInts = numInts;

   if(totInts + num == 0)
   {
      numIntFields = 1;
   } else {
      numIntFields = (unsigned short)ceil((double)(totInts + num)/8);
   }

   intMask[funcNum].mask[0] = mask[num] << totInts%16;
   for(i = 0; i < num; i++) 
   {
      intMask[funcNum].mask[i + 1] = 0x01 << (totInts%16 + i);
   }

   if(numIntFields > 1 && ((totInts%8 + num) > 8)) 
   {
      intMask[funcNum].numRegs = 2;
   } else if(numIntFields > 0) {
      intMask[funcNum].numRegs = 1;
   } else {
      intMask[funcNum].numRegs = 0;
   }
   
   totInts += (unsigned short)num;

   numInts = totInts;
   intMask[funcNum].status = F01_RMI_Data1 + numIntFields - intMask[funcNum].numRegs;
   intMask[funcNum].enable = F01_RMI_Ctrl1 + numIntFields - intMask[funcNum].numRegs;
}

