/**
  ******************************************************************************
  * @文件    stm32f10x_rtc.c
  * @作者    MCD 應用程序組
  * @版本    V3.1.0
  * @日期    06/19/2009
  * @簡述    這個文件 提供所有 RTC 固件函數.
  * @翻譯    ANSON/sweet1985 Email:airanson110@126.com
  * @日期    08/07/2009
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
#include "stm32f10x_rtc.h"

/* 自用類型 --------------------------------------------------------------*/
/* 自用定義 --------------------------------------------------------------*/
#define CRL_CNF_Set      ((uint16_t)0x0010)      /*!< Configuration Flag Enable Mask */
#define CRL_CNF_Reset    ((uint16_t)0xFFEF)      /*!< Configuration Flag Disable Mask */
#define RTC_LSB_Mask     ((uint32_t)0x0000FFFF)  /*!< RTC LSB Mask */
#define PRLH_MSB_Mask    ((uint32_t)0x000F0000)  /*!< RTC Prescaler MSB Mask */

/* 自用宏 -----------------------------------------------------------------*/
/* 自用變量 ---------------------------------------------------------------*/
/* 自用函數原型 -----------------------------------------------------------*/
/* 自用函數 ---------------------------------------------------------------*/

/**
  * @簡述  使能或失能指定的 RTC 中斷.
  * @參數  RTC_IT: 要使能或失能指定的 RTC 中斷.
  *                這個參數可以是下面值的任意組合:
  *                RTC_IT_OW:  溢出中斷
  *                RTC_IT_ALR: 警報中斷
  *                RTC_IT_SEC: 秒中斷
  * @參數  NewState: 指定 RTC 中斷的新的狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void RTC_ITConfig(uint16_t RTC_IT, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_RTC_IT(RTC_IT));  
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    RTC->CRH |= RTC_IT;
  }
  else
  {
    RTC->CRH &= (uint16_t)~RTC_IT;
  }
}

/**
  * @簡述  進入 RTC 配置模式.
  * @參數  沒有
  * @返回  沒有
  */
void RTC_EnterConfigMode(void)
{
  /* 設置 CNF 標誌進入配置模式 */
  RTC->CRL |= CRL_CNF_Set;
}

/**
  * @簡述  退出 RTC 配置模式.
  * @參數  沒有
  * @返回  沒有
  */
void RTC_ExitConfigMode(void)
{
  /* 復位 CNF 標誌退出配置模式 */
  RTC->CRL &= CRL_CNF_Reset;
}

/**
  * @簡述  獲得 RTC 計數器值.
  * @參數  沒有
  * @返回  RTC 計數器值.
  */
uint32_t RTC_GetCounter(void)
{
  uint16_t tmp = 0;
  tmp = RTC->CNTL;
  return (((uint32_t)RTC->CNTH << 16 ) | tmp) ;
}

/**
  * @簡述  設置 RTC 計數器值.
  * @參數  CounterValue: RTC 計數器的新值.
  * @返回  沒有
  */
void RTC_SetCounter(uint32_t CounterValue)
{ 
  RTC_EnterConfigMode();
  /* 設置 RTC 計數器高位字 */
  RTC->CNTH = CounterValue >> 16;
  /* 設置 RTC 計數器低位字 */
  RTC->CNTL = (CounterValue & RTC_LSB_Mask);
  RTC_ExitConfigMode();
}

/**
  * @簡述  設置 RTC 預分頻裝在寄存器的值.
  * @參數  PrescalerValue: RTC 預分頻裝在寄存器的新值.
  * @返回  沒有
  */
void RTC_SetPrescaler(uint32_t PrescalerValue)
{
  /* 檢查參數 */
  assert_param(IS_RTC_PRESCALER(PrescalerValue));
  
  RTC_EnterConfigMode();
  /* 設置 RTC 預分頻裝在寄存器高位字 */
  RTC->PRLH = (PrescalerValue & PRLH_MSB_Mask) >> 16;
  /* 設置 RTC 預分頻裝在寄存器低位字 */
  RTC->PRLL = (PrescalerValue & RTC_LSB_Mask);
  RTC_ExitConfigMode();
}

/**
  * @簡述  設置 RTC 報警寄存器的值.
  * @參數  AlarmValue: RTC 報警寄存器的新值.
  * @返回  沒有
  */
void RTC_SetAlarm(uint32_t AlarmValue)
{  
  RTC_EnterConfigMode();
  /* 設置報警寄存器高位字 */
  RTC->ALRH = AlarmValue >> 16;
  /* 設置報警寄存器低位字 */
  RTC->ALRL = (AlarmValue & RTC_LSB_Mask);
  RTC_ExitConfigMode();
}

/**
  * @簡述  獲取 RTC 預分頻分頻因子的值.
  * @參數  沒有
  * @返回  RTC 預分頻分頻因子的值.
  */
uint32_t RTC_GetDivider(void)
{
  uint32_t tmp = 0x00;
  tmp = ((uint32_t)RTC->DIVH & (uint32_t)0x000F) << 16;
  tmp |= RTC->DIVL;
  return tmp;
}

/**
  * @簡述  等待最近一次對RTC寄存器的寫操作完成.
  * @註解  這個函數一定要在任何對RTC寄存器寫操作之前調用.
  * @參數  沒有
  * @返回  沒有
  */
void RTC_WaitForLastTask(void)
{
  /* 循環直到 RTOFF 標誌置位 */
  while ((RTC->CRL & RTC_FLAG_RTOFF) == (uint16_t)RESET)
  {
  }
}

/**
  * @簡述  等待RTC寄存器(RTC_CNT,RTC_ALR和RTC_PRL)與RTC APB時鐘同步.
  * @註解  這個函數一定要在任何對APB復位或APB時鐘停止後的寫操作之前調用.
  * @參數  沒有
  * @返回  沒有
  */
void RTC_WaitForSynchro(void)
{
  /* 清除 RSF 標誌 */
  RTC->CRL &= (uint16_t)~RTC_FLAG_RSF;
  /* 循環直到 RSF 標誌置位 */
  while ((RTC->CRL & RTC_FLAG_RSF) == (uint16_t)RESET)
  {
  }
}

/**
  * @簡述  檢查指定的 RTC 標誌設置與否.
  * @參數  RTC_FLAG: 指定要檢查的標誌.
  *                  這個參數可以選下面的值之一:
  *                  RTC_FLAG_RTOFF: RTC 操作關閉標誌
  *                  RTC_FLAG_RSF:   寄存器同步標誌
  *                  RTC_FLAG_OW:    溢出中斷標誌
  *                  RTC_FLAG_ALR:   警報中斷標誌
  *                  RTC_FLAG_SEC:   秒中斷標誌
  * @返回  RTC_FLAG 的新狀態 (SET 或 RESET).
  */
FlagStatus RTC_GetFlagStatus(uint16_t RTC_FLAG)
{
  FlagStatus bitstatus = RESET;
  
  /* 檢查參數 */
  assert_param(IS_RTC_GET_FLAG(RTC_FLAG)); 
  
  if ((RTC->CRL & RTC_FLAG) != (uint16_t)RESET)
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
  * @簡述  清除 RTC 掛起標誌.
  * @參數  RTC_FLAG: 指定被清除的標誌.
  *                  這個參數可以是下面值的任意組合:
  *                  RTC_FLAG_RSF: 同步寄存器標誌. 只有在SPB復位或APB時鐘停止之後清除.
  *                  RTC_FLAG_OW:  溢出中斷標誌
  *                  RTC_FLAG_ALR: 報警中斷標誌
  *                  RTC_FLAG_SEC: 秒中斷標誌
  * @返回  沒有
  */
void RTC_ClearFlag(uint16_t RTC_FLAG)
{
  /* 檢查參數 */
  assert_param(IS_RTC_CLEAR_FLAG(RTC_FLAG)); 
    
  /* 清除 RTC 掛起標誌 */
  RTC->CRL &= (uint16_t)~RTC_FLAG;
}

/**
  * @簡述  檢查指定的 RTC 中斷發生與否.
  * @param  RTC_IT: 要檢查的RTC中斷源.
  *                 這個參數可以選下面的值之一:
  *                 RTC_IT_OW:  溢出中斷
  *                 RTC_IT_ALR: 報警中斷
  *                 RTC_IT_SEC: 秒中斷
  * @返回  RTC_IT 的新狀態 (SET 或 RESET).
  */
ITStatus RTC_GetITStatus(uint16_t RTC_IT)
{
  ITStatus bitstatus = RESET;
  /* 檢查參數 */
  assert_param(IS_RTC_GET_IT(RTC_IT)); 
  
  bitstatus = (ITStatus)(RTC->CRL & RTC_IT);
  if (((RTC->CRH & RTC_IT) != (uint16_t)RESET) && (bitstatus != (uint16_t)RESET))
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
  * @簡述  清除 RTC 的中斷待處理位.
  * @參數  RTC_IT: 待清除的 RTC 中斷待處理位.
  *                這個參數可以是下面值的任意組合:
  *                RTC_IT_OW:  溢出中斷
  *                RTC_IT_ALR: 報警中斷
  *                RTC_IT_SEC: 秒中斷
  * @返回  沒有
  */
void RTC_ClearITPendingBit(uint16_t RTC_IT)
{
  /* 檢查參數 */
  assert_param(IS_RTC_IT(RTC_IT));  
  
  /* 清除 RTC 掛起標誌 */
  RTC->CRL &= (uint16_t)~RTC_IT;
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
