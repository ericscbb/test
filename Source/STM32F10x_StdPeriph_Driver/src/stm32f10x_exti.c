/**
  ******************************************************************************
  * @文件    stm32f10x_exti.c
  * @作者    MCD 應用程序組
  * @版本    V3.1.0
  * @日期    06/19/2009
  * @簡述    這個文件提供全部 EXTI 固件函數.
  * @翻譯    ANSON/sweet1985 Email:airanson110@126.com
  * @日期    06/07/2009
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
#include "stm32f10x_exti.h"

/* 自用類型 ------------------------------------------------------------*/
/* 自用定義 ------------------------------------------------------------*/

#define EXTI_LineNone    ((uint32_t)0x00000)  /* No interrupt selected */

/* 自用宏 --------------------------------------------------------------*/
/* 自用變量 ------------------------------------------------------------*/
/* 自用函數原型 --------------------------------------------------------*/
/* 自用函數 ------------------------------------------------------------*/

/**
  * @簡述  將 EXTI 外設寄存器復位到默認值.
  * @參數  沒有
  * @返回  沒有
  */
void EXTI_DeInit(void)
{
  EXTI->IMR = 0x00000000;
  EXTI->EMR = 0x00000000;
  EXTI->RTSR = 0x00000000; 
  EXTI->FTSR = 0x00000000; 
  EXTI->PR = 0x000FFFFF;
}

/**
  * @簡述  根據EXIT_InitStruct中指定的參數初始化 EXTI 外設.
  * @參數  EXTI_InitStruct: 指向 EXTI_InitTypeDef 的結構，它包含特定EXTI的配置信息.
  * @返回  沒有
  */
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct)
{
  uint32_t tmp = 0;

  /* 檢查參數 */
  assert_param(IS_EXTI_MODE(EXTI_InitStruct->EXTI_Mode));
  assert_param(IS_EXTI_TRIGGER(EXTI_InitStruct->EXTI_Trigger));
  assert_param(IS_EXTI_LINE(EXTI_InitStruct->EXTI_Line));  
  assert_param(IS_FUNCTIONAL_STATE(EXTI_InitStruct->EXTI_LineCmd));

  tmp = (uint32_t)EXTI_BASE;
     
  if (EXTI_InitStruct->EXTI_LineCmd != DISABLE)
  {
    /* 清除 EXTI 外部中斷線配置 */
    EXTI->IMR &= ~EXTI_InitStruct->EXTI_Line;
    EXTI->EMR &= ~EXTI_InitStruct->EXTI_Line;
    
    tmp += EXTI_InitStruct->EXTI_Mode;

    *(__IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;

    /* 清除上升沿下降沿邊沿配置 */
    EXTI->RTSR &= ~EXTI_InitStruct->EXTI_Line;
    EXTI->FTSR &= ~EXTI_InitStruct->EXTI_Line;
    
    /* 為選定的外部中斷選擇觸發(事件) */
    if (EXTI_InitStruct->EXTI_Trigger == EXTI_Trigger_Rising_Falling)
    {
      /* 上升沿下降沿 */
      EXTI->RTSR |= EXTI_InitStruct->EXTI_Line;
      EXTI->FTSR |= EXTI_InitStruct->EXTI_Line;
    }
    else
    {
      tmp = (uint32_t)EXTI_BASE;
      tmp += EXTI_InitStruct->EXTI_Trigger;

      *(__IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;
    }
  }
  else
  {
    tmp += EXTI_InitStruct->EXTI_Mode;

    /* 禁止選中的外部中斷線 */
    *(__IO uint32_t *) tmp &= ~EXTI_InitStruct->EXTI_Line;
  }
}

/**
  * @簡述  將EXTI_InitStruct成員置為默認值.
  * @參數  EXTI_InitStruct: 指向EXTI_InitTypeDef結構，該結構將被初始化.
  * @返回  沒有
  */
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct)
{
  EXTI_InitStruct->EXTI_Line = EXTI_LineNone;
  EXTI_InitStruct->EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStruct->EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStruct->EXTI_LineCmd = DISABLE;
}

/**
  * @簡述  產生一個軟件中斷.
  * @參數  EXTI_Line: 指定 EXTI 線激活或禁止.
  *                   這個參數可以任意組合 EXTI_Linex 中 x可以取(0..19).
  * @返回  沒有
  */
void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line)
{
  /* 檢查參數 */
  assert_param(IS_EXTI_LINE(EXTI_Line));
  
  EXTI->SWIER |= EXTI_Line;
}

/**
  * @簡述  檢查特定的 EXTI 線標誌是否被置位.
  * @參數  EXTI_Line: 特定的 EXTI 線標誌.
  *                   這個參數可以是:
  *                                  EXTI_Linex: 外部中斷線 x可以取(0..19)
  * @返回  EXTI_Line 的新狀態 (SET 或 RESET).
  */
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line)
{
  FlagStatus bitstatus = RESET;
  /* 檢查參數 */
  assert_param(IS_GET_EXTI_LINE(EXTI_Line));
  
  if ((EXTI->PR & EXTI_Line) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @簡述  清除 EXTI 線的掛起標誌.
  * @參數  EXTI_Line: 指定要清除標誌的 EXTI 線.
  *                   這個參數可以是任意EXTI_Linex組合，x可以是(0..19).
  * @返回  沒有
  */
void EXTI_ClearFlag(uint32_t EXTI_Line)
{
  /* 檢查參數 */
  assert_param(IS_EXTI_LINE(EXTI_Line));
  
  EXTI->PR = EXTI_Line;
}

/**
  * @簡述  檢查指定的 EXTI 線路觸發請求發生與否.
  * @參數  EXTI_Line: 待檢查 EXTI 線路的掛起位.
  *                   這個參數可以是:
  *                                  EXTI_Linex: 外部中斷線 x可以是(0..19)
  * @返回  EXTI_Line 的新狀態 (SET 或 RESET).
  */
ITStatus EXTI_GetITStatus(uint32_t EXTI_Line)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;
  /* 檢查參數 */
  assert_param(IS_GET_EXTI_LINE(EXTI_Line));
  
  enablestatus =  EXTI->IMR & EXTI_Line;
  if (((EXTI->PR & EXTI_Line) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @簡述  清除EXTI線路掛起位.
  * @參數  EXTI_Line: 待清除EXTI線路的掛起位.
  *                    這個參數可以是任意 EXTI_Linex 組合， x可以是(0..19).
  * @返回  沒有
  */
void EXTI_ClearITPendingBit(uint32_t EXTI_Line)
{
  /* 檢查參數 */
  assert_param(IS_EXTI_LINE(EXTI_Line));
  
  EXTI->PR = EXTI_Line;
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
