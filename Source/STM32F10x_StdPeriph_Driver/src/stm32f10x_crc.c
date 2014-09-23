/**
  ******************************************************************************
  * @文件    stm32f10x_crc.c
  * @作者    MCD 應用程序組
  * @版本    V3.1.0
  * @日期    06/19/2009
  * @簡述    這個文件 提供所有 CRC 固件函數.
  * @翻譯    ANSON/sweet1985 Email:airanson110@126.com
  * @日期    21/07/2009
  ******************************************************************************
  * @復件
  *
  * 這個固件僅僅是提供給客戶作為設計產品而編寫程序的參考目的使客戶節約時間。由於
  * 客戶使用本固件在開發產品編程上產生的結果意法半導體公司不承擔任何直接的和間接
  * 的責任，也不承擔任何損害而引起的賠償。
  *
  * <h2><center>&複製; 版權所有 2009 意法半導體公司</center></h2>
  * 翻譯版本僅供學習，如與英文原版有出入應以英文原版為準。
  */ 

/* 包含 ------------------------------------------------------------------*/
#include "stm32f10x_crc.h"

/* 自用類型 --------------------------------------------------------------*/
/* 自用定義 --------------------------------------------------------------*/

/* CR register bit mask */

#define CR_RESET_Set    ((uint32_t)0x00000001)

/* 自用宏 -------------------------------------------------------------*/
/* 自用變量 -----------------------------------------------------------*/
/* 自用函數原型 -------------------------------------------------------*/
/* 自用函數 -----------------------------------------------------------*/


/**
  * @簡述  復位 CRC 數據寄存器 (DR).
  * @參數  沒有
  * @返回  沒有
  */
void CRC_ResetDR(void)
{
  /* 復位 CRC 發生器 */
  CRC->CR = CR_RESET_Set;
}

/**
  * @簡述  計算已知字的32位 CRC (32-bit).
  * @參數  Data: 待計算 CRC 的數據字
  * @返回  32位 CRC 碼
  */
uint32_t CRC_CalcCRC(uint32_t Data)
{
  CRC->DR = Data;
  
  return (CRC->DR);
}

/**
  * @簡述  計算一個緩衝區的數據的32位 CRC (32-bit).
  * @參數  pBuffer: 指向包含需要計算數據的緩衝區的指針
  * @參數  BufferLength: 待計算的緩衝區的長度					
  * @返回  32位 CRC 碼
  */
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength)
{
  uint32_t index = 0;
  
  for(index = 0; index < BufferLength; index++)
  {
    CRC->DR = pBuffer[index];
  }
  return (CRC->DR);
}

/**
  * @簡述  返回當前的 CRC 的值.
  * @參數  沒有
  * @返回  32位 CRC 碼
  */
uint32_t CRC_GetCRC(void)
{
  return (CRC->DR);
}

/**
  * @簡述  在獨立的數據寄存器中保存一個8位的數據.
  * @參數  IDValue: 等待保存到獨立的數據寄存器中8位的數據值					
  * @返回  沒有
  */
void CRC_SetIDRegister(uint8_t IDValue)
{
  CRC->IDR = IDValue;
}

/**
  * @簡述  返回保存到獨立的數據寄存器中8位的數據
  * @參數  沒有
  * @返回  獨立的數據寄存器的8位數值 
  */
uint8_t CRC_GetIDRegister(void)
{
  return (CRC->IDR);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
