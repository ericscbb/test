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

/**************************************************************
 *** BE SURE TO ADD YOUR NEW COMMAND TO CommandProcessor.c, ***
 **************************************************************/

// Struct for SoftButtons
typedef struct 
{
    // X, Y for the coordinates of the top left corner of the button
	// ID for the unique button ID
	int X;
	int Y;
	int ID;
} Button;


// Predefined set of buttons
Button Buttons[4] =
{
	{100, 300, 1},
	{320, 300, 2},
	{540, 300, 3},
	{860, 300, 4},
};

// Predefined width and height of buttons
int buttonWidth = 120;

void executeCommand()
{
   int regBlocks, numFingers, fRegs, tmp8, *u8ptr, nfd = 1, prevStat = 0;
   int prevRM, xgest = false;
   int X, Y, rates[10], xmax, ymax;
   int ButtonPressed;
   int i, j;
   int cnt, totATTN, curRate = 0;
   float freq;

   if(NumberOfFingers == 5) {
     numFingers = 10;
   } else {
     numFingers = NumberOfFingers + 1;
   }

   fRegs = (int)ceil((double)numFingers/4);

   readRMI(F11_2D_Ctrl6, tmpBuf, 4);
   xmax = tmpBuf[1] << 8 | tmpBuf[0];
   ymax = tmpBuf[3] << 8 | tmpBuf[2];
   printf("0x%04X: (xmax, ymax) = (%i, %i)\n", F11_2D_Ctrl6, xmax, ymax);

   printf("\nStatus    ");
   if(numFingers > 6) {
      for(i = 0; i <= numFingers - 6; i++) {
          printf(" ");
      }
   }
   for(i = 0; i < nfd; i++) {
  	  printf("F%d <x, y, z, wx, wy>\t", i);
   }
        
   printf("\n-------");
       
   if(numFingers > 6) {
      for(i = 0; i <= numFingers - 6; i++) {
       printf("-");
      }
   }

   do {
	  if(!poll) {
	     while(!ATTN()); // wait for ATTN to assert
	   } 

       // Read all finger data
       readRMI(F11_2D_Data0, tmpBuf, fRegs + 5*numFingers + 2);
	   u8ptr = tmpBuf + fRegs;

        
       for(j = 0; j < fRegs; j++) {
          for(i = 0; i < 4; i++) {
             if(((j+1)*4 + i - 3) <= numFingers) {
                printf("%d", (tmpBuf[j] >> i*2) & 0x03);
             } else {
			    break;
		     }
          }
       }
       if(numFingers > 6) {
          printf("  ");
       } else {
          for(i = 0; i <= 6 - numFingers; i++){
             printf(" ");
          }
       }
            
       for(i = 0; i < nfd; i++) {
          X = (u8ptr[0] << 4) | (u8ptr[2]);
          Y = (u8ptr[1] << 4) | (u8ptr[2] >> 4);
          ButtonPressed = checkButtonPressed((int)X, (int)Y);
		 
		   if (ButtonPressed != 0)
		  	 printf("Button %d pressed\t | ", ButtonPressed);
		   else	 printf("<%4d, %4d, %3d, %2d, %2d>\t", X, Y, u8ptr[4], u8ptr[3] & 0x0F, u8ptr[3] >> 4);
          u8ptr += 5;
       }
			
       readRMI(F01_RMI_Data1, tmpBuf, 1);    // Read reg to clear attn
      
    } while(1); 
}

// A simple routine to check if finger landed within the area of a certain button
int checkButtonPressed(int X, int Y)
{
	int i;

	for (i = 0; i < 4; i++)
	{
		if ((X >= Buttons[i].X) && (Y >= Buttons[i].Y))
		{
			if ((X <= (Buttons[i].X+buttonWidth)) && (Y <= (Buttons[i].Y+buttonWidth)))
				return Buttons[i].ID;
		}
	}
	return 0;
}








