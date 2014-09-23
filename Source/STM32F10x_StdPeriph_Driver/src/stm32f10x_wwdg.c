/**
  ******************************************************************************
  * @文件    stm32f10x_wwdg.c
  * @作者    MCD 應用程序組
  * @版本    V3.1.0
  * @日期    06/19/2009
  * @簡述    這個文件 提供所有 WWDG 固件函數.
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_wwdg.h"
#include "stm32f10x_rcc.h"

/* 自用類型 --------------------------------------------------------------*/
/* 自用定義 --------------------------------------------------------------*/

/* ----------- WWDG registers bit address in the alias region ----------- */
#define WWDG_OFFSET       (WWDG_BASE - PERIPH_BASE)

/* Alias word address of EWI bit */
#define CFR_OFFSET        (WWDG_OFFSET + 0x04)
#define EWI_BitNumber     0x09
#define CFR_EWI_BB        (PERIPH_BB_BASE + (CFR_OFFSET * 32) + (EWI_BitNumber * 4))

/* --------------------- WWDG registers bit mask ------------------------ */

/* CR register bit mask */
#define CR_WDGA_Set       ((uint32_t)0x00000080)

/* CFR register bit mask */
#define CFR_WDGTB_Mask    ((uint32_t)0xFFFFFE7F)
#define CFR_W_Mask        ((uint32_t)0xFFFFFF80)
#define BIT_Mask          ((uint8_t)0x7F)

/* 自用宏 -------------------------------------------------------------*/
/* 自用變量 -----------------------------------------------------------*/
/* 自用函數原型 -------------------------------------------------------*/
/* 自用函數 -----------------------------------------------------------*/

/**
  * @簡述  將外設 WWDG 寄存器重設為缺省值.
  * @參數  沒有
  * @返回  沒有
  */
void WWDG_DeInit(void)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, DISABLE);
}

/**
  * @簡述  設置 WWDG 預分頻值.
  * @參數  WWDG_Prescaler: 指定 WWDG 預分頻值.
  *                        這個參數可以是下面的值之一:
  *                        WWDG_Prescaler_1: WWDG 計數器時鐘 = (PCLK1/4096)/1
  *                        WWDG_Prescaler_2: WWDG 計數器時鐘 = (PCLK1/4096)/2
  *                        WWDG_Prescaler_4: WWDG 計數器時鐘 = (PCLK1/4096)/4
  *                        WWDG_Prescaler_8: WWDG 計數器時鐘 = (PCLK1/4096)/8
  * @返回  沒有
  */
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler)
{
  uint32_t tmpreg = 0;
  /* 檢查參數 */
  assert_param(IS_WWDG_PRESCALER(WWDG_Prescaler));
  /* 清除 WDGTB[1:0] 位 */
  tmpreg = WWDG->CFR & CFR_WDGTB_Mask;
  /* 設置 WDGTB[1:0] 位，按照 WWDG_Prescaler 的值 */
  tmpreg |= WWDG_Prescaler;
  /* 存儲新值 */
  WWDG->CFR = tmpreg;
}

/**
  * @簡述  設置 WWDG 窗口值.
  * @參數  指明要和倒計數器比較的窗口值.
  *        這個個參數的值必須小於0x80.
  * @返回  沒有
  */
void WWDG_SetWindowValue(uint8_t WindowValue)
{
  __IO uint32_t tmpreg = 0;

  /* 檢查參數 */
  assert_param(IS_WWDG_WINDOW_VALUE(WindowValue));
  /* 清除 W[6:0] 位 */

  tmpreg = WWDG->CFR & CFR_W_Mask;

  /* 依照窗口值的值設置 W[6:0] 位 */
  tmpreg |= WindowValue & (uint32_t) BIT_Mask;

  /* 存儲新值 */
  WWDG->CFR = tmpreg;
}

/**
  * @簡述  使能 WWDG 早期喚醒中斷 (EWI).
  * @參數  沒有
  * @返回  沒有
  */
void WWDG_EnableIT(void)
{
  *(__IO uint32_t *) CFR_EWI_BB = (uint32_t)ENABLE;
}

/**
  * @簡述  設置 WWDG 計數器值.
  * @參數  Counter: 指定看門狗計數器值.
  *                 該參數取值必須在0x40與0x7F之間.
  * @返回  沒有
  */
void WWDG_SetCounter(uint8_t Counter)
{
  /* 檢查參數 */
  assert_param(IS_WWDG_COUNTER(Counter));
  /* 為配置計數器的值寫 T[6:0]位，除了寫0到WDG A位沒有意義 */
  WWDG->CR = Counter & BIT_Mask;
}

/**
  * @簡述  使能 WWDG 和載入計數器的值.                  
  * @參數  Counter: 指定看門狗載入計數器的值.
  *                 這個參數必須是0x40到0x7F之間的一個數.
  * @返回  沒有
  */
void WWDG_Enable(uint8_t Counter)
{
  /* 檢查參數 */
  assert_param(IS_WWDG_COUNTER(Counter));
  WWDG->CR = CR_WDGA_Set | Counter;
}

/**
  * @簡述  檢查 WWDG 早期喚醒中斷標誌位被設置與否.
  * @參數  沒有
  * @返回  早期喚醒中斷標誌位的新狀態 (SET 或 RESET)
  */
FlagStatus WWDG_GetFlagStatus(void)
{
  return (FlagStatus)(WWDG->SR);
}

/**
  * @簡述  清除早期喚醒中斷標誌位.
  * @參數  沒有
  * @返回  沒有
  */
void WWDG_ClearFlag(void)
{
  WWDG->SR = (uint32_t)RESET;
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
