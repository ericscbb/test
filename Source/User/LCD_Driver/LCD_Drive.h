#ifndef LCD_DRIVE_H
#define LCD_DRIVE_H

//頭文件調用
#include "stm32f10x.h"
#include "hardware.h"

/***********************************************************************************
設置顏色宏定義
***********************************************************************************/
#define   BLACK        	0x0000                    // 黑色： 0, 0, 0              
#define   NAVY         	0x000F                    // 深藍色： 0, 0, 128          
#define   DGREEN       	0x03E0                    // 深綠色： 0, 128, 0          
#define   DCYAN        	0x03EF                    // 深青色： 0, 128, 128        
#define   MAROON       	0x7800                    // 深紅色：128, 0, 0           
#define   PURPLE       	0x780F                    // 紫色： 128, 0, 128          
#define   OLIVE        	0x7BE0                    // 橄欖綠：128, 128, 0         
#define   LGRAY        	0xC618                    // 灰白色：192, 192, 192        
#define   DGRAY        	0x7BEF                    // 深灰色：128, 128, 128        
#define   BLUE         	0x001F                    // 藍色： 0, 0, 255            
#define   GREEN        	0x07E0                 	 // 綠色： 0, 255, 0             
#define   CYAN         	0x07FF                    // 青色： 0, 255, 255           
#define   RED          	0xF800                    // 紅色： 255, 0, 0             
#define   MAGENTA     	0xF81F                    // 品紅： 255, 0, 255          
#define   YELLOW       	0xFFE0                    // 黃色： 255, 255, 0           
#define   WHITE        	0xFFFF                    // 白色： 255, 255, 255 
#define   BRED             0XF81F	 
#define   GRED 		0XFFE0
#define   GBLUE		0X07FF
#define   BROWN 		0XBC40                    //棕色
#define   BRRED 		0XFC07                     //棕紅色
#define   GRAY  		0X8430                    //灰色
#define   ORANGE 	0XFCA0                     //RGB:0XFFA500 //橙
#define   INDIGO 		0X2841                     //RGB:0X4B0082 //靛
#define   DARKBLUE     0X01CF                    //深藍色
#define   LIGHTBLUE    0X7D7C                    //淺藍色  
#define   GRAYBLUE     0X5458                    //灰藍色
#define 	LIGHTGREEN 0X841F                    //淺綠色
#define 	LIGHTGRAY   0XEF5B                    //淺灰色(PANNEL)

#define 	LGRAYBLUE   0XA651                     //淺灰藍色(中間層顏色)
#define 	LBBLUE         	0X2B12                     //淺棕藍色(選擇條目的反色)

extern u16 BACK_COLOR, POINT_COLOR ;

#define  LCD_ID_AM  DsipV_ENABLE //定義屏顯示方式	改變此參數就可以切換橫豎屏顯示
//AM=0：
//LCD_ID_AM=000：水平方向送數據,水平和垂直方向地址遞減
//LCD_ID_AM=010：水平方向送數據,水平方向遞增、垂直方向地址遞減
//LCD_ID_AM=100：水平方向送數據,水平方向遞減、垂直方向地址遞增
//LCD_ID_AM=110：水平方向送數據,水平和垂直方向地址遞增
//AM=1：
//LCD_ID_AM=001：垂直方向送數據,水平和垂直方向地址遞減
//LCD_ID_AM=011：垂直方向送數據,水平方向遞增、垂直方向地址遞減
//LCD_ID_AM=101：垂直方向送數據,水平方向遞減、垂直方向地址遞增
//LCD_ID_AM=111：垂直方向送數據,水平和垂直方向地址遞增
//LCD_ID_AM=110: 豎屏顯示；  LCD_ID_AM = 001：橫屏顯示

#define  DsipH_ENABLE  001 	  	 //定義橫屏顯示
#define	 DsipV_ENABLE  110	  	 //定義豎屏顯示

#if    LCD_ID_AM == DsipH_ENABLE
#define LCD_H_MAX	320		 //定義屏的水平方向大小
#define LCD_V_MAX	240		 //定義屏的垂直方向大小

#elif  LCD_ID_AM == DsipV_ENABLE

#define LCD_H_MAX	240			//定義屏的水平方向大小
#define LCD_V_MAX	320			//定義屏的垂直方向大小
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

