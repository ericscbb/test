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

// The following #defines are just needed to define an Image Report BUffer in memory
#define  CFG_F54_TXCOUNT              0xFF           // Number of Transmitters on device under test
#define  CFG_F54_RXCOUNT              0xFF           // Number of Receivers    on device under test
                                                     
#define  IMAGE_SIZE                   (CFG_F54_TXCOUNT * CFG_F54_TXCOUNT)

float Limit[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

char Result[20][20];

static void executeCommand()
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
   do {
      readRMI(F54_Command_Base, &command, 1);
   } while (command == 0x01);

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
		    if ((ImageArray[i][j] == Limit[j]) &&
	   			Result[i][j] = "P" /*Pass*/
			else
			    Result[i][j] = "F" /*Fail*/
			printf("%c, ", Result[i][j]);
	   }
	   printf("]\n");
   }
}




