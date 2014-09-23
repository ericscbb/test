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
#include "config.h"

/* Variables for F34 functionality */
unsigned short SynaF34DataBase;
unsigned short SynaF34QueryBase;
unsigned short SynaF01DataBase;
unsigned short SynaF01CommandBase;
unsigned short SynaF01QueryBase;

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

	if (TouchControllerTypeCheck())
	{
		SynaF34_FlashControl = SynaF34DataBase + SynaFirmwareBlockSize + 2;
	    
		SynaEnableFlashing();

	    if (fimrwareRevisionCheck()
		{
			SynaBootloaderLock();

			SynaProgramConfiguration();
		}
		
		SynaProgramFirmware();

		SynaFinalizeReflash();
	}
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
				SynaF01QueryBase = buffer[0];
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
	   case 4:
	       SynalockImgData = (unsigned char *)((&SynaFirmware[0]) + 0xC0);
		   break;
	   case 5:
		   SynalockImgData = (unsigned char *)((&SynaFirmware[0]) + 0xB0);	
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

/* SynaBootloaderLock locks down the bootloader
*/
void SynaBootloaderLock()
{
	unsigned short lockBlockCount;
    unsigned char *puFirmwareData = SynalockImgData;
    unsigned char uData[2];
    unsigned short i, uBlockNum;

	// Check if device is in unlocked state
	readRMI((SynaF34QueryBase+ 2), &uData[0], 1);
 
	//Device is unlocked
    if (uData[0] & 0x02)
	{ 
		printf("Device unlocked. Lock it first...\n");
		// Different bootloader version has different block count for the lockdown data
		// Need to check the bootloader version from the image file being reflashed
		switch (SynafirmwareImgVersion)
		{
			case 2:
				lockBlockCount = 3;
				break;
			case 3:
			case 4:
				lockBlockCount = 4;
				break;
			case 5:
				lockBlockCount = 5;
				break;
			default:
				lockBlockCount = 0;
				break;
		}

		// Write the lockdown info block by block
		// This reference code of lockdown process does not check for bootloader version
		// currently programmed on the ASIC against the bootloader version of the image to 
		// be reflashed. Such case should not happen in practice. Reflashing cross different 
		// bootloader versions is not supported.
		for (uBlockNum = 0; uBlockNum < lockBlockCount; ++uBlockNum)
		{
			uData[0] = uBlockNum & 0xff;
			uData[1] = (uBlockNum & 0xff00) >> 8;

			/* Write Block Number */
			readRMI(SynaF34Reflash_BlockNum, &uData[0], 2);

			/* Write Data Block */
			writeRMI(SynaF34Reflash_BlockData, puFirmwareData, SynaFirmwareBlockSize);

			/* Move to next data block */
			puFirmwareData += SynaFirmwareBlockSize;

			/* Issue Write Lockdown Block command */
			uData[0] = 4;
			writeRMI(SynaF34_FlashControl, &uData[0], 1);

			/* Wait ATTN until device is done writing the block and is ready for the next. */
			SynaWaitATTN();
		}
		printf("Device locking done.\n");
		
		// Enable reflash again to finish the lockdown process.
		// Since this lockdown process is part of the reflash process, we are enabling 
		// reflash instead, rather than resetting the device to finish the unlock procedure.
		SynaEnableFlashing();
	}
	else printf("Device already locked.\n");
}

/* ConfigBlockReflash reflashes the config block only
*/
void ConfigBlockReflash()
{
    unsigned char uData[2];

	convertConfigBlockData();

    SynaInitialize();
	
	SynaReadConfigInfo();
	
	SynaReadFirmwareInfo();

	SynaF34_FlashControl = SynaF34DataBase + SynaFirmwareBlockSize + 2;

	SynaEnableFlashing();
	
	SynaBootloaderLock();

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
    SynaconfigImgData = (unsigned char *)ConfigBlock;

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

// This function is intended to convert the config data struct output by DS4 (read config.h) into an array that
// the reflash code uses (read SynaFirmwareImage.h)
// DS4 will output the array format in the next release and this function will not be necessary
void convertConfigBlockData()
{
	for (int i = 0; value[i]!=NULL; i++)
	{
		ConfigBlock[i] = value[i].Value;
	}
}

// This function is to check the touch controller type of the touch controller matches with the firmware image
bool TouchControllerTypeCheck()
{
	unsigned char uData[4];
	char buffer[4];

	char controllerType[20];

    int ID;
	int revision;

	readRMI((SynaF01QueryBase + 43), &uData[0], 1);

	if ((uData[0] & 0x0f) > 0)
	{
		readRMI((SynaF01QueryBase + 44), &uData[0], 1);
		if (uData[0] & 0x01)
		{
			readRMI((SynaF01QueryBase + 17), &uData[0], 2);

			ID = (int)(uData[1] & (uData[0] << 8));
			sprintf(buffer, "%d", ID);

			if ((strstr(controllerType, TOUCH_CONTROLLER) != 0) return true
				return false;
		}
		else return false;
	}
	else return false;
}

bool fimrwareRevisionCheck()
{
	unsigned char uData[10];
	char buffer[10];

	char revision[10];

	readRMI((SynaF01QueryBase + 11), &uData[0], 10);

    for (int i = 0; i < 0; i++)
	{
		while (uData[i] != NULL)
		{
			revision[i] = char(uData[0]);
		}
	}

	if (strcmp(revision, FW_REVISION) == 0) return true;
		return false;

}




