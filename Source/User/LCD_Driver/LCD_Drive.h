#ifndef LCD_DRIVE_H
#define LCD_DRIVE_H

//�Y���ե�
#include "stm32f10x.h"
#include "hardware.h"

/***********************************************************************************
�]�m�C�⧻�w�q
***********************************************************************************/
#define   BLACK        	0x0000                    // �¦�G 0, 0, 0              
#define   NAVY         	0x000F                    // �`�Ŧ�G 0, 0, 128          
#define   DGREEN       	0x03E0                    // �`���G 0, 128, 0          
#define   DCYAN        	0x03EF                    // �`�C��G 0, 128, 128        
#define   MAROON       	0x7800                    // �`����G128, 0, 0           
#define   PURPLE       	0x780F                    // ����G 128, 0, 128          
#define   OLIVE        	0x7BE0                    // ���V��G128, 128, 0         
#define   LGRAY        	0xC618                    // �ǥզ�G192, 192, 192        
#define   DGRAY        	0x7BEF                    // �`�Ǧ�G128, 128, 128        
#define   BLUE         	0x001F                    // �Ŧ�G 0, 0, 255            
#define   GREEN        	0x07E0                 	 // ���G 0, 255, 0             
#define   CYAN         	0x07FF                    // �C��G 0, 255, 255           
#define   RED          	0xF800                    // ����G 255, 0, 0             
#define   MAGENTA     	0xF81F                    // �~���G 255, 0, 255          
#define   YELLOW       	0xFFE0                    // ����G 255, 255, 0           
#define   WHITE        	0xFFFF                    // �զ�G 255, 255, 255 
#define   BRED             0XF81F	 
#define   GRED 		0XFFE0
#define   GBLUE		0X07FF
#define   BROWN 		0XBC40                    //�Ħ�
#define   BRRED 		0XFC07                     //�Ĭ���
#define   GRAY  		0X8430                    //�Ǧ�
#define   ORANGE 	0XFCA0                     //RGB:0XFFA500 //��
#define   INDIGO 		0X2841                     //RGB:0X4B0082 //�Q
#define   DARKBLUE     0X01CF                    //�`�Ŧ�
#define   LIGHTBLUE    0X7D7C                    //�L�Ŧ�  
#define   GRAYBLUE     0X5458                    //���Ŧ�
#define 	LIGHTGREEN 0X841F                    //�L���
#define 	LIGHTGRAY   0XEF5B                    //�L�Ǧ�(PANNEL)

#define 	LGRAYBLUE   0XA651                     //�L���Ŧ�(�����h�C��)
#define 	LBBLUE         	0X2B12                     //�L���Ŧ�(��ܱ��ت��Ϧ�)

extern u16 BACK_COLOR, POINT_COLOR ;

#define  LCD_ID_AM  DsipV_ENABLE //�w�q����ܤ覡	���ܦ��ѼƴN�i�H������ݫ����
//AM=0�G
//LCD_ID_AM=000�G������V�e�ƾ�,�����M������V�a�}����
//LCD_ID_AM=010�G������V�e�ƾ�,������V���W�B������V�a�}����
//LCD_ID_AM=100�G������V�e�ƾ�,������V����B������V�a�}���W
//LCD_ID_AM=110�G������V�e�ƾ�,�����M������V�a�}���W
//AM=1�G
//LCD_ID_AM=001�G������V�e�ƾ�,�����M������V�a�}����
//LCD_ID_AM=011�G������V�e�ƾ�,������V���W�B������V�a�}����
//LCD_ID_AM=101�G������V�e�ƾ�,������V����B������V�a�}���W
//LCD_ID_AM=111�G������V�e�ƾ�,�����M������V�a�}���W
//LCD_ID_AM=110: �ݫ���ܡF  LCD_ID_AM = 001�G������

#define  DsipH_ENABLE  001 	  	 //�w�q������
#define	 DsipV_ENABLE  110	  	 //�w�q�ݫ����

#if    LCD_ID_AM == DsipH_ENABLE
#define LCD_H_MAX	320		 //�w�q�̪�������V�j�p
#define LCD_V_MAX	240		 //�w�q�̪�������V�j�p

#elif  LCD_ID_AM == DsipV_ENABLE

#define LCD_H_MAX	240			//�w�q�̪�������V�j�p
#define LCD_V_MAX	320			//�w�q�̪�������V�j�p
#endif

extern uint16_t TextColor , BlackColor;

void Init_LCD(void);
void Clear_LCD(uint16_t Color);
void Set_LCDCorsor(uint16_t x,uint16_t y);
uint8_t Disp_LCDChar(uint16_t x,uint16_t y,uint8_t star);
void Disp_LCDString(uint16_t x,uint16_t y,uint8_t* p);
void Disp_LCDBmp(uint16_t Xstar,uint16_t Ystar,uint16_t Xend,uint16_t Yend,uint8_t* bmp);
void LCD_ShowNum(uint8_t x,uint16_t y,u32 num,uint8_t len);
void Write_LCDRAM_Prepare(void);
void Write_LCDRam(uint16_t LCD_Dat);
void Disp_LCDPoint(uint16_t x,uint16_t y);
void Disp_LCDLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void Disp_LCDCircle(uint8_t x0,uint16_t y0,uint8_t r);
void LCD_DrawRectangle(u8 x1, u16 y1, u8 x2, u16 y2);
void LCD_FillRectangle(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t Color);
void LCD_FulfillArea(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t Color);
void RMI_LCDDrawColorPoint(uint8_t x0,uint16_t y0,uint8_t r,uint16_t color);
void LCD_ShowString(uint16_t x,uint16_t y,uint8_t* p,u16 color);


//RMI
void RMI_LCDDispPoint(uint16_t x,uint16_t y,uint16_t color);
void RMI_DispLCDLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color );
void RMI_LCDDrawRectangle(u8 x1, u16 y1, u8 x2, u16 y2,uint16_t color);
void RMI_DispLCDCircle(uint8_t x0,uint16_t y0,uint8_t r,uint16_t color);
void RMI_DispClorebar(void);


#endif

