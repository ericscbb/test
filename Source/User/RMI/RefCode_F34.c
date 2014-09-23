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

// SynaFirmwareImage.h contains the data for both the entire image and the config block
#include "SynaFirmwareImage.h"
#include "DS4_config.h"

/* Variables for F34 functionality */
unsigned short SynaF34DataBase;
unsigned short SynaF34QueryBase;
unsigned short SynaF01DataBase;
unsigned short SynaF01CommandBase;

unsigned short SynaF34Reflash_BlockNum;
unsigned short SynaF34Reflash_BlockData;
unsigned short SynaF34ReflashQuery_BootID;
unsigned short SynaF34ReflashQuery_FlashPropertyQuery;
unsigned short SynaF34ReflashQuery_FirmwareBlockSize;
unsigned short SynaF34ReflashQuery_FirmwareBlockCount;
unsigned short SynaF34ReflashQuery_ConfigBlockSize;
unsigned short SynaF34ReflashQuery_ConfigBlockCount;

unsigned short SynaFirmwareBlockSize;
unsigned short SynaFirmwareBlockCount;
unsigned long SynaImageSize;

unsigned short SynaConfigBlockSize;
unsigned short SynaConfigBlockCount;
unsigned long SynaConfigImageSize;

unsigned short SynaBootloadID;

unsigned short SynaF34_FlashControl;

unsigned char *SynafirmwareImgData;
unsigned char *SynaconfigImgData;
unsigned char *SynalockImgData;
unsigned int SynafirmwareImgVersion;

unsigned char ConfigBlock[];

/* End: Variables for F34 functionality */

/* CompleteReflash reflashes the entire user image, including the configuration block and firmware
*/
void CompleteReflash()
{   
    SynaInitialize();
	
	SynaReadConfigInfo();
	
	SynaReadFirmwareInfo();
	
	SynaF34_FlashControl = SynaF34DataBase + SynaFirmwareBlockSize + 2;
    
	SynaEnableFlashing();

	SynaProgramFirmware();

	SynaProgramConfiguration();

	SynaFinalizeReflash();
}

/* SynaSetup scans the Page Description Table (PDT) and sets up the necessary variables
 * for the reflash process. This function is a "slim" version of the PDT scan function in 
 * in PDT.c, since only F34 and F01 are needed for reflash.
 */
void SynaSetup()
{
    unsigned char address;
    unsigned char buffer[6];

	for (address = 0xe9; address > 0xc0; address = address - 6)
	{
    	readRMI(address, &buffer, 6);

		switch (buffer[5])
		{
			case 0x34:
				SynaF34DataBase = buffer[3];
				SynaF34QueryBase = buffer[0];
				break;
			case 0x01:
				SynaF01DataBase = buffer[3];
				SynaF01CommandBase = buffer[1];
				break;
		}
	}

    SynaF34Reflash_BlockNum = SynaF34DataBase;
	SynaF34Reflash_BlockData = SynaF34DataBase + 2;
	SynaF34ReflashQuery_BootID = SynaF34QueryBase;
	SynaF34ReflashQuery_FlashPropertyQuery = SynaF34QueryBase + 2;
	SynaF34ReflashQuery_FirmwareBlockSize = SynaF34QueryBase + 3;
	SynaF34ReflashQuery_FirmwareBlockCount = SynaF34QueryBase +5;
	SynaF34ReflashQuery_ConfigBlockSize = SynaF34QueryBase + 3;
	SynaF34ReflashQuery_ConfigBlockCount = SynaF34QueryBase + 7;

	SynafirmwareImgData = (unsigned char *)((&SynaFirmware[0])+0x100);
    SynaconfigImgData   = (unsigned char *)(SynafirmwareImgData+SynaImageSize);
    SynafirmwareImgVersion = (unsigned int)(SynaFirmware[7]);

	switch (SynafirmwareImgVersion)
	{
	   case 2: 
	       SynalockImgData = (unsigned char *)((&SynaFirmware[0]) + 0xD0);
		   break;
       case 3:
	       SynalockImgData = (unsigned char *)((&SynaFirmware[0]) + 0xC0);
		   break;
       default: break;
	}
}

/* SynaInitialize sets up the reflahs process
 */
void SynaInitialize()
{	
	unsigned char uData[2];
	unsigned char uStatus;

    printf("\nInitializing Reflash Process...");

	readRMI(0xff, 0x00, 1);

	do {
		readRMI(0, &uStatus, 1);

		if (uStatus & 0x80)
		{
			break;
		}
	} while (uStatus & 0x40);

	SynaSetup();

	SynafirmwareImgData = 0;

	SynaconfigImgData = 0 ;

	readRMI(SynaF34ReflashQuery_FirmwareBlockSize, &uData[0], 2);

	SynaFirmwareBlockSize = uData[0] | (uData[1] << 8);
}

/* SynaReadFirmwareInfo reads the F34 query registers and retrieves the block size and count
 * of the firmware section of the image to be reflashed 
 */
void SynaReadFirmwareInfo()
{
	unsigned char uData[2];

    printf("\nRead Firmware Info");

	readRMI(SynaF34ReflashQuery_FirmwareBlockSize, &uData[0], 2);
	SynaFirmwareBlockSize = uData[0] | (uData[1] << 8);

	readRMI(SynaF34ReflashQuery_FirmwareBlockCount, &uData[0], 2);
	SynaFirmwareBlockCount = uData[0] | (uData[1] << 8);
	SynaImageSize = SynaFirmwareBlockCount * SynaFirmwareBlockSize;
}

/* SynaReadConfigInfo reads the F34 query registers and retrieves the block size and count
 * of the configuration section of the image to be reflashed 
 */
void SynaReadConfigInfo()
{
	unsigned char uData[2];

    printf("\nRead Config Info");

	readRMI(SynaF34ReflashQuery_ConfigBlockSize, &uData[0], 2);
	SynaConfigBlockSize = uData[0] | (uData[1] << 8);

	readRMI(SynaF34ReflashQuery_ConfigBlockCount, &uData[0], 2);
	SynaConfigBlockCount = uData[0] | (uData[1] << 8);
	SynaConfigImageSize = SynaConfigBlockCount * SynaConfigBlockSize;
}


/* SynaReadBootloadID reads the F34 query registers and retrieves the bootloader ID of the firmware
 */
void SynaReadBootloadID()
{
	unsigned char uData[2];

	readRMI(SynaF34ReflashQuery_BootID, &uData[0], 2);
	SynaBootloadID = uData[0] + uData[1] * 0x100;
}

/* SynaWriteBootloadID writes the bootloader ID to the F34 data register to unlock the reflash process
 */
void SynaWriteBootloadID()
{
	unsigned char uData[2];

	uData[0] = SynaBootloadID % 0x100;
	uData[1] = SynaBootloadID / 0x100;

	writeRMI(SynaF34Reflash_BlockData, &uData[0], 2);
}

/* SynaEnableFlashing kicks off the reflash process
 */
void SynaEnableFlashing()
{
	unsigned char uData;
	unsigned char uStatus;

    printf("\nEnable Reflash...");
    
	// Reflash is enabled by first reading the bootloader ID from the firmware and write it back
	SynaReadBootloadID();
	SynaWriteBootloadID();

	// Make sure Reflash is not already enabled
	do {
		readRMI(SynaF34_FlashControl, &uData, 1);
	} while (((uData & 0x0f) != 0x00));

	// Clear ATTN
    readRMI (SynaF01DataBase, &uStatus, 1);

	if ((uStatus &0x40) == 0)
	{
		// Write the "Enable Flash Programming command to F34 Control register
		// Wait for ATTN and then clear the ATTN.
		uData = 0x0f;
		writeRMI(SynaF34_FlashControl, &uData, 1);
		SynaWaitForATTN();
		readRMI((SynaF01DataBase + 1), &uStatus, 1);
	
		// Scan the PDT again to ensure all register offsets are correct
		SynaSetup();
		
		// Read the "Program Enabled" bit of the F34 Control register, and proceed only if the 
		// bit is set.
		readRMI(SynaF34_FlashControl, &uData, 1);

		while (uData != 0x80)
		{
			// In practice, if uData!=0x80 happens for multiple counts, it indicates reflash 
			// is failed to be enabled, and program should quit
			;
		}
	}
}

/* SynaWaitForATTN waits for ATTN to be asserted within a certain time threshold.
 */
void SynaWaitForATTN()
{
    unsigned int error;

	error = waitATTN(ASSERT, 300);
}

/* SynaWaitATTN waits for ATTN to be asserted within a certain time threshold.
 * The function also checks for the F34 "Program Enabled" bit and clear ATTN accordingly.
 */
void SynaWaitATTN()
{
	unsigned char uData;
	unsigned char uStatus;

	waitATTN(ASSERT, 300);

	do {
 		readRMI(SynaF34_FlashControl, &uData, 1);
		readRMI((SynaF01DataBase + 1), &uStatus, 1);
	} while (uData!= 0x80);
}

/* SynaProgramConfiguration writes the configuration section of the image block by block
 */
void SynaProgramConfiguration()
{
	unsigned char uData[2];
	unsigned char *puData = ConfigBlockData;
	unsigned short blockNum;

    printf("\nProgram Configuration Section...");

	for (blockNum = 0; blockNum < SynaConfigBlockCount; blockNum++)
	{
	    uData[0] = blockNum & 0xff;
		uData[1] = (blockNum & 0xff00) >> 8;

		//Block by blcok, write the block number and data to the corresponding F34 data registers
		writeRMI(SynaF34Reflash_BlockNum, &uData[0], 2);
		writeRMI(SynaF34Reflash_BlockData, puData, SynaConfigBlockSize);
		puData += SynaConfigBlockSize;

		// Issue the "Write Configuration Block" command
		uData[0] = 0x06;
		writeRMI(SynaF34_FlashControl, &uData[0], 1);
		SynaWaitATTN();
		printf(".");
	}
}

/* SynaFinalizeReflash finalizes the reflash process
 */
void SynaFinalizeReflash()
{
	unsigned char uData;
	unsigned char uStatus;

	printf("\nFinalizing Reflash...");

	// Issue the "Reset" command to F01 command register to reset the chip
	// This command will also test the new firmware image and check if its is valid
	uData = 1;
	writeRMI(SynaF01CommandBase, &uData, 1);

	SynaWaitForATTN();
	readRMI(SynaF01DataBase, &uData, 1);
	
	// Sanity check that the reflash process is still enabled
	do {
	   readRMI(SynaF34_FlashControl, &uStatus, 1);
	} while ((uStatus & 0x0f) != 0x00);
	readRMI((SynaF01DataBase + 1), &uStatus, 1);
	
	SynaSetup();

    uData = 0;

	// Check if the "Program Enabled" bit in F01 data register is cleared
	// Reflash is completed, and the image passes testing when the bit is cleared
	do {
		readRMI(SynaF01DataBase, &uData, 1);
	} while ((uData & 0x40) != 0);

	// Rescan PDT the update any changed register offsets
	SynaSetup();

	printf("\nReflash Completed. Please reboot.");
}

/* SynaFlashFirmwareWrite writes the firmware section of the image block by block
 */
void SynaFlashFirmwareWrite()
{
	unsigned char *puFirmwareData = SynafirmwareImgData;
	unsigned char uData[2];
	unsigned short i, blockNum;

	for (blockNum = 0; blockNum < SynaFirmwareBlockCount; ++blockNum)
	{
		//Block by blcok, write the block number and data to the corresponding F34 data registers
	    uData[0] = blockNum & 0xff;
		uData[1] = (blockNum & 0xff00) >> 8;
		writeRMI(SynaF34Reflash_BlockNum, &uData[0], 2);

		writeRMI(SynaF34Reflash_BlockData, puFirmwareData, SynaFirmwareBlockSize);
		puFirmwareData += SynaFirmwareBlockSize;

		// Issue the "Write Firmware Block" command
		uData[0] = 2;
		writeRMI(SynaF34_FlashControl, &uData[0], 1);
		
	    SynaWaitATTN();
	}

}

/* SynaProgramFirmware prepares the firmware writing process
 */
void SynaProgramFirmware()
{
    unsigned char uData;    

	printf("\nProgram Firmware Section...");

    SynaReadBootloadID();

	SynaWriteBootloadID();

	uData = 3; 
	writeRMI(SynaF34_FlashControl, &uData, 1);

	SynaWaitATTN();

	SynaFlashFirmwareWrite();
}


/* ConfigBlockReflash reflashes the config block only
*/
void ConfigBlockReflash()
{
    unsigned char uData[2];

    SynaInitialize();
	
	SynaReadConfigInfo();
	
	SynaReadFirmwareInfo();

	SynaF34_FlashControl = SynaF34DataBase + SynaFirmwareBlockSize + 2;

	SynaEnableFlashing();
	
    // Check if device is in unlocked state
	readRMI((SynaF34QueryBase + 2), &uData[0], 1);
 
	//Device is unlocked
    if (uData[0] & 0x02)
	{ 
	   SynaFinalizeReflash();
	   return;
	   // Do not reflash config block if not locked.
	}

    eraseConfigBlock();
    SynaconfigImgData = (unsigned char *)ConfigBlockData;

    SynaProgramConfiguration();

    SynaFinalizeReflash();
}

/* eraseConfigBlock erases the config block
*/
void eraseConfigBlock()
{
	unsigned char uData;    

	// Erase of config block is done by first entering into bootloader mode
    SynaReadBootloadID();
	SynaWriteBootloadID();

	// Command 7 to erase config block
	uData = 7; 
	writeRMI(SynaF34_FlashControl, &uData, 1);

	SynaWaitATTN();
}

// This function is intended to convert the config data struct output by DS4 (read DS4_config.h) into an array that
// the reflash code uses (read SynaFirmwareImage.h)
// DS4 will output the array format in the next release and this function will not be necessary
void convertConfigBlockData()
{
	for (int i = 0; value[i]!=NULL; i++)
	{
		ConfigBlock[i] = value[i].Value;
	}
}


// CRC_Calculate illustates how to calculate a checksum from the config block data.
// With DS4, the config block checksum is calculated and applies towards the end of 
// the config block data automatically
// Variable data to this function represents the data only portion of the config block
// Varaible len represents the length of the variable data.
void unsigned long CRC_Calculate(unsigned short [] data, unsigned short len)
{
    unsigned long Data_CRC = 0xffffffff;
    unsigned long sum1 = (unsigned long)(Data_CRC & 0xFFFF);
    unsigned long sum2 = (unsigned long)(Data_CRC >> 16);

    for (short i = 0; i < len; i++)
    {
        unsigned long temp = data[i];
        sum1 += temp;
        sum2 += sum1;
        sum1 = (unsigned long)((sum1 & 0xffff) + (sum1 >> 16));
        sum2 = (unsigned long)((sum2 & 0xffff) + (sum2 >> 16));
    }

    Data_CRC = (unsigned long)(sum2 << 16 | sum1);
    return Bootloader_incrementalCrc;
}
