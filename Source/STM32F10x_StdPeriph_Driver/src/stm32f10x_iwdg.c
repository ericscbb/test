/**
  ******************************************************************************
  * @文件    stm32f10x_iwdg.c
  * @作者    MCD 應用程序組
  * @版本    V3.1.0
  * @日期    06/19/2009
  * @簡述    這個文件 提供所有 IWDG 固件函數.
  * @翻譯    ANSON/sweet1985 Email:airanson110@126.com
  * @日期    09/07/2009
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
#include "stm32f10x_iwdg.h"

/* 自用類型 --------------------------------------------------------------*/
/* 自用定義 --------------------------------------------------------------*/

/* ---------------------- IWDG registers bit mask ----------------------------*/

/* KR register bit mask */
#define KR_KEY_Reload    ((uint16_t)0xAAAA)
#define KR_KEY_Enable    ((uint16_t)0xCCCC)

/* 自用宏 -------------------------------------------------------------*/
/* 自用變量 -----------------------------------------------------------*/
/* 自用函數原型 -------------------------------------------------------*/
/* 自用函數 -----------------------------------------------------------*/


/**
  * @簡述  使能或者失能對寄存器 IWDG_PR 和 IWDG_RLR 的寫操作.
  * @參數  IWDG_WriteAccess: 對 IWDG_PR 和 IWDG_RLR 寄存器的寫訪問的新的狀態.
  *                          這個參數可以是下面的值之一:
  *                          IWDG_WriteAccess_Enable:  使能對寄存器 IWDG_PR 和 IWDG_RLR 的寫操作
  *                          IWDG_WriteAccess_Disable: 失能對寄存器 IWDG_PR 和 IWDG_RLR 的寫操作
  * @返回  沒有
  */
void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess)
{
  /* 檢查參數 */
  assert_param(IS_IWDG_WRITE_ACCESS(IWDG_WriteAccess));
  IWDG->KR = IWDG_WriteAccess;
}

/**
  * @簡述  設置 IWDG 預分頻值.
  * @參數  IWDG_Prescaler: 指定 IWDG 預分頻值.
  *                        這個參數可以是下面的值之一:
  *                        IWDG_Prescaler_4:   設置IWDG預分頻值為 4
  *                        IWDG_Prescaler_8:   設置IWDG預分頻值為 8
  *                        IWDG_Prescaler_16:  設置IWDG預分頻值為 16
  *                        IWDG_Prescaler_32:  設置IWDG預分頻值為 32
  *                        IWDG_Prescaler_64:  設置IWDG預分頻值為 64
  *                        IWDG_Prescaler_128: 設置IWDG預分頻值為 128
  *                        IWDG_Prescaler_256: 設置IWDG預分頻值為 256
  * @返回  沒有
  */
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler)
{
  /* 檢查參數 */
  assert_param(IS_IWDG_PRESCALER(IWDG_Prescaler));
  IWDG->PR = IWDG_Prescaler;
}

/**
  * @簡述  設置 IWDG 重裝載值.
  * @參數  Reload: 指定 IWDG 重裝載值.
  *                這個參數一定是在'0'到'0x0FFF'之間的數.
  * @返回  沒有
  */
void IWDG_SetReload(uint16_t Reload)
{
  /* 檢查參數 */
  assert_param(IS_IWDG_RELOAD(Reload));
  IWDG->RLR = Reload;
}

/**
  * @簡述  按照 IWDG 重裝載寄存器的值重裝載 IWDG 計數器
  *        (對 IWDG_PR 和 IWDG_RLR 寄存器的寫訪問被禁能).
  * @參數  沒有
  * @返回  沒有
  */
void IWDG_ReloadCounter(void)
{
  IWDG->KR = KR_KEY_Reload;
}

/**
  * @簡述  使能 IWDG (對 IWDG_PR 和 IWDG_RLR 寄存器的寫訪問被禁能).
  * @參數  沒有
  * @返回  沒有
  */
void IWDG_Enable(void)
{
  IWDG->KR = KR_KEY_Enable;
}

/**
  * @簡述  檢查指定的 IWDG 標誌位被設置與否.
  * @參數  IWDG_FLAG: 要檢查的標誌.
  *                   這個參數可以是下面的值之一:
  *                   IWDG_FLAG_PVU: 預分頻因子值更新了
  *                   IWDG_FLAG_RVU: 重載值更新了
  * @返回  IWDG_FLAG 的新狀態 (SET 或 RESET).
  */
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* 檢查參數 */
  assert_param(IS_IWDG_FLAG(IWDG_FLAG));
  if ((IWDG->SR & IWDG_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* 返回標誌狀態 */
  return bitstatus;
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
