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
                                                     
#define  IMAGE_SIZE                   (CFG_F54_RXCOUNT * CFG_F54_TXCOUNT)


static void executeCommand()
{
   unsigned short numberOfRows;
   unsigned short numberOfColumns;
   int i, j, k;
   int length;

   int ImageArray[CFG_F54_TXCOUNT] [CFG_F54_RXCOUNT] ;

   int ImageBuffer[CFG_F54_TXCOUNT*CFG_F54_RXCOUNT];

   unsigned short command;

   readRMI(F54_Query_Base, &numberOfColumns, 1);
   readRMI(F54_Query_1, &numberOfRows, 1);
   length = numberOfRows * numberOfColumns;

   // Enabling only the analog image reporting interrupt, and turn off the rest
   command = 0x08;
   writeRMI(F01_RMI_Ctrl1, &command, 1);
   
   k = 0;       
   // Set report mode to read 8-bit image
   command = 0x01;
   writeRMI(F54_Data_Base, &command, 1);

   command = 0x00;
   writeRMI(F54_Data_LowIndex, &command, 1);
   writeRMI(F54_Data_HighIndex, &command, 1);

   // Set the GetReport bit to acquire an image
   command = 0x01;
   writeRMI(F54_Command_Base, &command, 1);

   // Wait until the command is completed
   do {
      readRMI(F54_Command_Base, &command, 1);
   } while (command == 0x01);

   readRMI(F54_Data_Buffer, &ImageBuffer[0], length);

   for (i = 0; i < numberOfRows; i++)
   {
       for (j = 0; j < numberOfColumns; j++)
	   {
		 ImageArray[i][j] = (int)ImageBuffer[k];
		 k++;
	   }  	  
   }

   // Display the image
   printf("\nThe 16-bit image:\n");
   for (i = 0; i < numberOfRows; i++)
   {   
       printf("[ ");
	   for (j = 0; j < numberOfColumns; j++)
	   {
	   		printf("%2d ", ImageArray[i][j]);
	   }
	   printf("]\n");
   }
}




