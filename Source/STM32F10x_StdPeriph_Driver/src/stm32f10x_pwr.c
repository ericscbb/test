/**
  ******************************************************************************
  * @file    stm32f10x_pwr.c
  * @author  MCD 應用程序組
  * @version V3.1.0
  * @date    06/19/2009
  * @brief   這個文件 提供所有 PWR 固件函數.
  * @翻譯    ANSON/sweet1985 Email:airanson110@126.com
  * @日期    07/07/2009
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
#include "stm32f10x_pwr.h"
#include "stm32f10x_rcc.h"

/* 自用類型 ------------------------------------------------------------*/
/* 自用定義 ------------------------------------------------------------*/

/* --------- PWR registers bit address in the alias region ------------ */
#define PWR_OFFSET               (PWR_BASE - PERIPH_BASE)

/* --- CR 寄存器 ---*/

/* Alias word address of DBP bit */
#define CR_OFFSET                (PWR_OFFSET + 0x00)
#define DBP_BitNumber            0x08
#define CR_DBP_BB                (PERIPH_BB_BASE + (CR_OFFSET * 32) + (DBP_BitNumber * 4))

/* Alias word address of PVDE bit */
#define PVDE_BitNumber           0x04
#define CR_PVDE_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PVDE_BitNumber * 4))

/* --- CSR 寄存器 ---*/

/* Alias word address of EWUP bit */
#define CSR_OFFSET               (PWR_OFFSET + 0x04)
#define EWUP_BitNumber           0x08
#define CSR_EWUP_BB              (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (EWUP_BitNumber * 4))

/* ------------------ PWR 寄存器位屏蔽 ------------------------ */

/* CR register bit mask */
#define CR_PDDS_Set              ((uint32_t)0x00000002)
#define CR_DS_Mask               ((uint32_t)0xFFFFFFFC)
#define CR_CWUF_Set              ((uint32_t)0x00000004)
#define CR_PLS_Mask              ((uint32_t)0xFFFFFF1F)

/* --------- Cortex 系統控制寄存器位屏蔽 ---------------------- */

/* Cortex 系統控制寄存器地址 */
#define SCB_SysCtrl              ((uint32_t)0xE000ED10)

/* SLEEPDEEP 位屏蔽 */
#define SysCtrl_SLEEPDEEP_Set    ((uint32_t)0x00000004)

/* 自用宏 -------------------------------------------------------------*/
/* 自用變量 -----------------------------------------------------------*/
/* 自用函數原型 -------------------------------------------------------*/
/* 自用函數 -----------------------------------------------------------*/

/**
  * @簡述  復位 PWR 外圍寄存器為默認復位值.
  * @參數  沒有
  * @返回  沒有
  */
void PWR_DeInit(void)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, DISABLE);
}

/**
  * @簡述  使能或者失能 RTC 和後備寄存器訪問.
  * @參數  NewState: 訪問 RTC 和備份寄存器的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void PWR_BackupAccessCmd(FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CR_DBP_BB = (uint32_t)NewState;
}

/**
  * @簡述  使能或者失能可編程電壓探測器 (PVD).
  * @參數  NewState: PVD 的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void PWR_PVDCmd(FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CR_PVDE_BB = (uint32_t)NewState;
}

/**
  * @簡述  設置 PVD 的探測電壓閾值 (PVD).
  * @參數  PWR_PVDLevel: PVD 的探測電壓閾值
  *                      這個參數可以是下列值中的一個:
  *          PWR_PVDLevel_2V2: PVD 探測電壓閾值 2.2V
  *          PWR_PVDLevel_2V3: PVD 探測電壓閾值 2.3V
  *          PWR_PVDLevel_2V4: PVD 探測電壓閾值 2.4V
  *          PWR_PVDLevel_2V5: PVD 探測電壓閾值 2.5V
  *          PWR_PVDLevel_2V6: PVD 探測電壓閾值 2.6V
  *          PWR_PVDLevel_2V7: PVD 探測電壓閾值 2.7V
  *          PWR_PVDLevel_2V8: PVD 探測電壓閾值 2.8V
  *          PWR_PVDLevel_2V9: PVD 探測電壓閾值 2.9V
  * @返回  沒有
  */
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel)
{
  uint32_t tmpreg = 0;
  /* 檢查參數 */
  assert_param(IS_PWR_PVD_LEVEL(PWR_PVDLevel));
  tmpreg = PWR->CR;
  /* 清除 PLS[7:5] 位 */
  tmpreg &= CR_PLS_Mask;
  /* 設置 PLS[7:5] 位 按照 PWR_PVDLevel 的值 */
  tmpreg |= PWR_PVDLevel;
  /* 存儲新值 */
  PWR->CR = tmpreg;
}

/**
  * @簡述  使能或者失能喚醒管腳功能.
  * @參數  NewState: 喚醒管腳功能的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void PWR_WakeUpPinCmd(FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CSR_EWUP_BB = (uint32_t)NewState;
}

/**
  * @簡述  進入停止(STOP)模式.
  * @參數  PWR_Regulator: 電壓轉換器在停止模式下的狀態.
  *                       這個參數可以是下列值中的一個:
  *                       PWR_Regulator_ON: 停止模式下電壓轉換器 ON
  *                       PWR_Regulator_LowPower: 停止模式下電壓轉換器進入低功耗模式
  * @參數  PWR_STOPEntry: 選擇使用指令 WFE 還是 WFI 來進入停止模式.
  *                       這個參數可以是下列值中的一個:
  *                       PWR_STOPEntry_WFI: 使用指令 WFI 來進入停止模式
  *                       PWR_STOPEntry_WFE: 使用指令 WFE 來進入停止模式
  * @返回  沒有
  */
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry)
{
  uint32_t tmpreg = 0;
  /* 檢查參數 */
  assert_param(IS_PWR_REGULATOR(PWR_Regulator));
  assert_param(IS_PWR_STOP_ENTRY(PWR_STOPEntry));
  
  /* 在停止模式選擇校準狀態 ---------------------------------*/
  tmpreg = PWR->CR;
  /* 清 PDDS 和 LPDS 位 */
  tmpreg &= CR_DS_Mask;
  /* 依照 PWR_Regulator 值置位 LPDS */
  tmpreg |= PWR_Regulator;
  /* 保存新的值 */
  PWR->CR = tmpreg;
  /* 設置 SLEEPDEEP 位按照 Cortex 系統控制寄存器 */
  *(__IO uint32_t *) SCB_SysCtrl |= SysCtrl_SLEEPDEEP_Set;
  
  /* 選擇停止模式進入 --------------------------------------------------*/
  if(PWR_STOPEntry == PWR_STOPEntry_WFI)
  {   
    /* 請求等待中斷 */
    __WFI();
  }
  else
  {
    /* 請求等待事件 */
    __WFE();
  }
}

/**
  * @簡述  進入待機(STANDBY)模式.
  * @參數  沒有
  * @返回  沒有
  */
void PWR_EnterSTANDBYMode(void)
{
  /* 清除 Wake-up 標誌 */
  PWR->CR |= CR_CWUF_Set;
  /* 選擇 STANDBY 模式 */
  PWR->CR |= CR_PDDS_Set;
  /* 置位 Cortex 系統的控制寄存器 SLEEPDEEP 位 */
  *(__IO uint32_t *) SCB_SysCtrl |= SysCtrl_SLEEPDEEP_Set;
/* 這個選擇常常是確定存儲操作已完成 */
#if defined ( __CC_ARM   )
  __force_stores();
#endif
  /* 請求等待中斷 */
  __WFI();
}

/**
  * @簡述  檢查指定的 PWR 標誌位設置與否.
  * @參數  PWR_FLAG: 要檢查的標誌.
  *                  這個參數可以是下面的值之一:
  *                  PWR_FLAG_WU: 喚醒標誌
  *                  PWR_FLAG_SB: 待命標誌
  *                  PWR_FLAG_PVDO: PVD 輸出
  * @返回  PWR_FLAG 的新狀態 (SET or RESET).
  */
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* 檢查參數 */
  assert_param(IS_PWR_GET_FLAG(PWR_FLAG));
  
  if ((PWR->CSR & PWR_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* 返回狀態標誌 */
  return bitstatus;
}

/**
  * @簡述  清空 PWR 掛起標誌位.
  * @參數  PWR_FLAG: 要清空的標誌.
  *                  這個參數可以是下面的值之一:
  *                  PWR_FLAG_WU: 喚醒標誌
  *                  PWR_FLAG_SB: 待命標誌
  * @返回  沒有
  */
void PWR_ClearFlag(uint32_t PWR_FLAG)
{
  /* 檢查參數 */
  assert_param(IS_PWR_CLEAR_FLAG(PWR_FLAG));
         
  PWR->CR |=  PWR_FLAG << 2;
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
