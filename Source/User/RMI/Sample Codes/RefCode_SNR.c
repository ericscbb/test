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

#include "math.h"

// The following #defines are just needed to define an Image Report Buffer in memory
#define  CFG_SNR_TXCOUNT              0xFF           // Number of Transmitters on device under test
#define  CFG_SNR_RXCOUNT              0xFF           // Number of Receivers    on device under test
                                                     
#define  IMAGE_SIZE                   (CFG_SNR_RXCOUNT * CFG_SNR_TXCOUNT)


// Struct for the linked list that contains the image data
// 1000 samples of image data are needed for the calculation
// Linked list is used for resource optimization only.
struct list_signal {
		int count;
	    unsigned int Signal[CFG_SNR_TXCOUNT][CFG_SNR_RXCOUNT];
	    struct list_signal * next;
};

typedef struct list_signal ImageSignal;


static void executeCommand()
{
// This function declares, allocates and accesses data structures for the SNR calculation.
// This function also calculates the SNR with the declared data structure.
// It is strongly recommended to read the ClearPad 3000 Pltaform Datasheet prior to moving on
// reading the remaining section of the code, in order to understand the calculation code.
   unsigned short numberOfRows;
   unsigned short numberOfColumns;
   unsigned short has16Bit;
   unsigned int counter;
   unsigned int  tempValue;
   
   int i, j;
   int n, tempColumns;

   unsigned int ImageArray[CFG_SNR_TXCOUNT][CFG_SNR_RXCOUNT] ;
   unsigned int SNR[CFG_SNR_TXCOUNT][CFG_SNR_RXCOUNT];
   unsigned int UnTouchedAverage[CFG_SNR_TXCOUNT][CFG_SNR_RXCOUNT];
   unsigned int TouchedAverage[CFG_SNR_TXCOUNT][CFG_SNR_RXCOUNT];
   unsigned int NoiseTouchedRMS[CFG_SNR_TXCOUNT][CFG_SNR_RXCOUNT];
   unsigned int TouchStrength[CFG_SNR_TXCOUNT][CFG_SNR_RXCOUNT];
   unsigned short ImageBuffer[CFG_SNR_RXCOUNT*2];

   ImageSignal * curr, * head;

   unsigned short command;

   U32     time;
   int loopCount;
   char key;
   
   readRMI(F54_IMG_Query3, &has16Bit, 1);
   has16Bit = has16Bit >> 7;
   readRMI(F54_IMG_Query0, &numberOfColumns, 1);
   readRMI(F54_IMG_Query1, &numberOfRows, 1);
   tempColumns = numberOfColumns * 2;

   head = NULL;

   for (i = 0; i < numberOfRows; i++)
   {
	   for (j = 0, n = 0; j < numberOfColumns; j++)
	   {
	   		UnTouchedAverage[i][j] = 0;
			TouchStrength[i][j] = 0;
			NoiseTouchedRMS[i][j] = 0;
	   }
   }

   // Setting the NoSleep bit
   readRMI(F01_RMI_Ctrl0, &command, 1);
   command = command | 0x04;

   writeRMI(F01_RMI_Ctrl0, &command, 1);

   // Enabling only the F$54 image reporting interrupt, and turn off the rest
   command = 0x08;
   writeRMI(F01_RMI_Ctrl1, &command, 1);

   printf("Reading image data when untocuhed.\n");
 
   // Read the image 1000 times; Untouched
   for (counter = 0; counter < 1000; counter++)
   {
       printf(".");
       // Set report mode to read 16bit image
	   command = 0x02;
	   writeRMI(F54_IMG_Data1, &command, 1);

	   // Set the GetImage bit to acquire an image
	   command = 0x01;
	   writeRMI(F54_IMG_Cmd0, &command, 1);

	   // Wait until the command is completed
	   do {
	      readRMI(F54_IMG_Cmd0, &command, 1);
	   } while (command == 0x01);

	   for (i = 0; i < numberOfRows; i++)
	   {
			for (j = 0, j < numberOfColumns; j++)
			{
				readRMI(F54_IMG_Data3, &ImageBuffer[0], 1);
				UnTouchedAverage[i][j] = ImageBuffer[0];

				readRMI(F54_IMG_Data3, &ImageBuffer[0], 1);
				UnTouchedAverage[i][j] = (UnTouchedAverage[i][j]|(ImageBuffer[0] << 8)) + UnTouchedAverage[i][j];
			}
	   }
   }

   printf("\n");

   // Compute the UnTouchedAverage1000
   for (i = 0; i < numberOfRows; i++)
   {
	   for (j = 0; j < numberOfColumns; j++)
	   {
		   UnTouchedAverage[i][j] = UnTouchedAverage[i][j] / 1000;
	   }
   }

   printf("Reading image data when tocuhed. Hit any key when slug is readily placed on sensor.\n");

   while (!getch());

   // Read it touched
   for (counter = 0; counter < 1000; counter++)
   {
       printf(".");
       // Set report mode to read 16bit image
	   command = 0x02;
	   writeRMI(F54_IMG_Data1, &command, 1);

	   // Set the GetImage bit to acquire an image
	   command = 0x01;
	   writeRMI(F54_IMG_Cmd0, &command, 1);

	   // Wait until the command is completed
	   do {
	      readRMI(F54_IMG_Cmd0, &command, 1);
	   } while (command == 0x01);


       // A linked list is created for the 1000 samples of image data when the sensor 
	   // is touched, since all individual samples are needed to be retained for further 
	   // calculation
       curr = (ImageSignal *)malloc(sizeof(ImageSignal));
	   curr->count = counter;

	    for (i = 0; i < numberOfRows; i++)
	   {
			for (j = 0, j < numberOfColumns; j++)
			{
				readRMI(F54_IMG_Data3, &ImageBuffer[0], 1);
				tempValue = ImageBuffer[0];
				readRMI(F54_IMG_Data3, &ImageBuffer[0], 1);
                tempValue = tempValue | (ImageBuffer[0] << 8);
				curr->Signal[i][j] = tempValue;
				TouchedAverage[i][j] = tempValue + TouchedAverage[i][j];
			}
	   }
	   curr->next  = head;
	   head = curr;
	   
   }
   printf("\n");
   

   // Compute the TouchedAverage1000
   for (i = 0; i < numberOfRows; i++)
   {
	   for (j = 0; j < numberOfColumns; j++)
	   {
		   TouchedAverage[i][j] = TouchedAverage[i][j] / 1000;
	   }
   }

   // Compute NoiseTouchedRMS and TouchStrength and SNR
   for (i = 0; i < numberOfRows; i++)
   {
	   for (j = 0; j < numberOfColumns; j++)
	   {
	       curr = head;
	       for (counter = 0; counter < 1000; counter++)
           {
		       tempValue = curr->Signal[i][j] - TouchedAverage[i][j];
			   tempValue = tempValue * tempValue;
		       NoiseTouchedRMS[i][j] = tempValue + NoiseTouchedRMS[i][j];
			   if (curr->next != NULL)
			   	   curr = curr->next;
		   }
		   NoiseTouchedRMS[i][j] = sqrt((double)NoiseTouchedRMS[i][j] / 1000);
		   
		   TouchStrength[i][j] = TouchedAverage[i][j] - UnTouchedAverage[i][j];
		  
		   // Take care of a possible Dividons by Zero case
		   if (NoiseTouchedRMS[i][j] == 0)
		   		SNR[i][j] = 9999;
		   else SNR[i][j] = 20 * log10((double)(TouchStrength[i][j] / NoiseTouchedRMS[i][j]));
	   }
   }
   

   printf("\nThe SNR:\n");
   for (i = 0; i < numberOfRows; i++)
   {   
       printf("[ ");
	   for (j = 0; j < numberOfColumns; j++)
	   {
	   		printf("%2d ", SNR[i][j]);
	   }
	   printf("]\n");
   }
}
