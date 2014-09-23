/**
  ******************************************************************************
  * @文件    stm32f10x_bkp.c
  * @作者    MCD 應用程序組
  * @版本    V3.1.0
  * @日期    06/19/2009
  * @簡述    這個文件提供了所有 BKP 固件函數.
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
#include "stm32f10x_bkp.h"
#include "stm32f10x_rcc.h"

/* 自用類型 --------------------------------------------------------------*/
/* 自用定義 --------------------------------------------------------------*/

/* ------------ BKP registers bit address in the alias region --------------- */
#define BKP_OFFSET        (BKP_BASE - PERIPH_BASE)

/* --- CR Register ----*/

/* Alias word address of TPAL bit */
#define CR_OFFSET         (BKP_OFFSET + 0x30)
#define TPAL_BitNumber    0x01
#define CR_TPAL_BB        (PERIPH_BB_BASE + (CR_OFFSET * 32) + (TPAL_BitNumber * 4))

/* Alias word address of TPE bit */
#define TPE_BitNumber     0x00
#define CR_TPE_BB         (PERIPH_BB_BASE + (CR_OFFSET * 32) + (TPE_BitNumber * 4))

/* --- CSR Register ---*/

/* Alias word address of TPIE bit */
#define CSR_OFFSET        (BKP_OFFSET + 0x34)
#define TPIE_BitNumber    0x02
#define CSR_TPIE_BB       (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (TPIE_BitNumber * 4))

/* Alias word address of TIF bit */
#define TIF_BitNumber     0x09
#define CSR_TIF_BB        (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (TIF_BitNumber * 4))

/* Alias word address of TEF bit */
#define TEF_BitNumber     0x08
#define CSR_TEF_BB        (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (TEF_BitNumber * 4))

/* ---------------------- BKP registers bit mask ------------------------ */

/* RTCCR register bit mask */
#define RTCCR_CAL_Mask    ((uint16_t)0xFF80)
#define RTCCR_Mask        ((uint16_t)0xFC7F)

/* CSR register bit mask */
#define CSR_CTE_Set       ((uint16_t)0x0001)
#define CSR_CTI_Set       ((uint16_t)0x0002)

/* 自用宏 -------------------------------------------------------------*/
/* 自用變量 -----------------------------------------------------------*/
/* 自用函數原型 -------------------------------------------------------*/
/* 自用函數 -----------------------------------------------------------*/

/**
  * @簡述  將 BKP 外設寄存器復位到它們的默認值.
  * @參數  沒有
  * @返回  沒有
  */
void BKP_DeInit(void)
{
  RCC_BackupResetCmd(ENABLE);
  RCC_BackupResetCmd(DISABLE);
}

/**
  * @簡述  設置侵入檢測管腳的有效電平.
  * @參數  BKP_TamperPinLevel: 侵入檢測管腳的有效電平.
  *                            這個參數可以取下面中的一個:
  *                            BKP_TamperPinLevel_High: 侵入檢測管腳高電平有效
  *                            BKP_TamperPinLevel_Low:  侵入檢測管腳低電平有效
  * @返回  沒有
  */
void BKP_TamperPinLevelConfig(uint16_t BKP_TamperPinLevel)
{
  /* 檢查參數 */
  assert_param(IS_BKP_TAMPER_PIN_LEVEL(BKP_TamperPinLevel));
  *(__IO uint32_t *) CR_TPAL_BB = BKP_TamperPinLevel;
}

/**
  * @簡述  使能或失能侵入檢測管腳.
  * @參數  NewState: 侵入檢測管腳的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void BKP_TamperPinCmd(FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CR_TPE_BB = (uint32_t)NewState;
}

/**
  * @簡述  使能或失能侵入檢測管腳的中斷.
  * @參數  NewState: 侵入檢測管腳的中斷的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void BKP_ITConfig(FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CSR_TPIE_BB = (uint32_t)NewState;
}

/**
  * @簡述  選擇在侵入檢測管腳上輸出的 RTC 時鐘源.
  * @參數  BKP_RTCOutputSource: 指定 RTC 輸出的來源.
  *                             這個參數可以取下面中的一個:
  *            BKP_RTCOutputSource_None: 侵入檢測管腳上沒有實時時鐘輸出.
  *            BKP_RTCOutputSource_CalibClock: 侵入檢測管腳上輸出實時時鐘告警脈衝上輸出的實時時鐘等於頻率除以64.
  *            BKP_RTCOutputSource_Alarm: 侵入檢測管腳上輸出實時時鐘告警脈衝.
  *            BKP_RTCOutputSource_Second: 侵入檢測管腳上輸出實時時鐘秒脈衝.  
  * @返回  沒有
  */
void BKP_RTCOutputConfig(uint16_t BKP_RTCOutputSource)
{
  uint16_t tmpreg = 0;
  /* 檢查參數 */
  assert_param(IS_BKP_RTC_OUTPUT_SOURCE(BKP_RTCOutputSource));
  tmpreg = BKP->RTCCR;
  /* 清除 CCO, ASOE 和 ASOS 位 */
  tmpreg &= RTCCR_Mask;
  
  /* 設置 CCO, ASOE 和 ASOS 位，按照 BKP_RTCOutputSource 的值 */
  tmpreg |= BKP_RTCOutputSource;
  /* 存儲新值 */
  BKP->RTCCR = tmpreg;
}

/**
  * @簡述  設置 RTC 時鐘校準值.
  * @參數  CalibrationValue: 指定 RTC 時鐘的校準值.
  *                          這個參數必須在 0 和 0x7F 之間.
  * @返回  沒有
  */
void BKP_SetRTCCalibrationValue(uint8_t CalibrationValue)
{
  uint16_t tmpreg = 0;
  /* 檢查參數 */
  assert_param(IS_BKP_CALIBRATION_VALUE(CalibrationValue));
  tmpreg = BKP->RTCCR;
  /* 清除 CAL[6:0] 位 */
  tmpreg &= RTCCR_CAL_Mask;
  /* 設置 CAL[6:0] 位，按照 CalibrationValue 的值 */
  tmpreg |= CalibrationValue;
  /* 存儲新值 */
  BKP->RTCCR = tmpreg;
}

/**
  * @簡述  向指定的後備寄存器中寫入用戶程序數據.
  * @參數  BKP_DR: 指定的後備寄存器.
  *                這個參數 BKP_DRx 中x可以取[1, 42]
  * @參數  Data: 需要寫入的數據
  * @返回  沒有
  */
void BKP_WriteBackupRegister(uint16_t BKP_DR, uint16_t Data)
{
  __IO uint32_t tmp = 0;

  /* 檢查參數 */
  assert_param(IS_BKP_DR(BKP_DR));

  tmp = (uint32_t)BKP_BASE; 
  tmp += BKP_DR;

  *(__IO uint32_t *) tmp = Data;
}

/**
  * @簡述  從指定的數據備份寄存器中讀出數據.
  * @參數  BKP_DR: 指定的數據備份寄存器.
  *                這個參數 BKP_DRx 中x可以取[1, 42]
  * @返回  指定的數據備份寄存器的內容
  */
uint16_t BKP_ReadBackupRegister(uint16_t BKP_DR)
{
  __IO uint32_t tmp = 0;

  /* 檢查參數 */
  assert_param(IS_BKP_DR(BKP_DR));

  tmp = (uint32_t)BKP_BASE; 
  tmp += BKP_DR;

  return (*(__IO uint16_t *) tmp);
}

/**
  * @簡述  檢查侵入檢測管腳事件的標誌位被設置與否 輸.
  * @參數  沒有
  * @返回  侵入檢測管腳事件的標誌的新狀態 (SET 或 RESET).
  */
FlagStatus BKP_GetFlagStatus(void)
{
  return (FlagStatus)(*(__IO uint32_t *) CSR_TEF_BB);
}

/**
  * @簡述  清除侵入檢測管腳事件的待處理標誌位.
  * @參數  沒有
  * @返回  沒有
  */
void BKP_ClearFlag(void)
{
  /* 設置 CTE 位，清除侵入檢測管腳事件的待處理標誌位 */
  BKP->CSR |= CSR_CTE_Set;
}

/**
  * @簡述  檢查侵入檢測中斷發生與否.
  * @參數  沒有
  * @返回  侵入檢測中斷標誌位的新狀態 (SET 或 RESET).
  */
ITStatus BKP_GetITStatus(void)
{
  return (ITStatus)(*(__IO uint32_t *) CSR_TIF_BB);
}

/**
  * @簡述  清除侵侵入檢測中斷的待處理位.
  * @參數  沒有
  * @返回  沒有
  */
void BKP_ClearITPendingBit(void)
{
  /* 設置 CTI 位， 清除侵侵入檢測中斷的待處理位 */
  BKP->CSR |= CSR_CTI_Set;
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
