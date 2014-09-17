/**
  ******************************************************************************
  * @文件    stm32f10x_dbgmcu.c
  * @作者    MCD 應用程序組
  * @版本    V3.1.0
  * @日期    06/19/2009
  * @簡述    這個文件 提供所有 DBGMCU 固件函數.
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
#include "stm32f10x_dbgmcu.h"

/* 自用類型 --------------------------------------------------------------*/
/* 自用定義 --------------------------------------------------------------*/

#define IDCODE_DEVID_Mask    ((uint32_t)0x00000FFF)

/* 自用宏 -------------------------------------------------------------*/
/* 自用變量 -----------------------------------------------------------*/
/* 自用函數原型 -------------------------------------------------------*/
/* 自用函數 -----------------------------------------------------------*/

/**
  * @簡述  返回設備的校正標示符.
  * @參數  None
  * @返回  設備的校正標示符
  */
uint32_t DBGMCU_GetREVID(void)
{
   return(DBGMCU->IDCODE >> 16);
}

/**
  * @簡述  返回設備的標示符.
  * @參數  沒有
  * @返回  設備的標示符
  */
uint32_t DBGMCU_GetDEVID(void)
{
   return(DBGMCU->IDCODE & IDCODE_DEVID_Mask);
}

/**
  * @簡述  配置MCU在調試模式下指定外設和低功耗模式狀態.
  * @參數  DBGMCU_Periph: 指定的外設和低功耗模式.
  *          可以使用下述任意值的組合:
  *          DBGMCU_SLEEP:     在睡眠模式保持調試器的連接              
  *          DBGMCU_STOP:      在停止模式保持調試器的連接               
  *          DBGMCU_STANDBY:   在待機模式保持調試器的連接            
  *          DBGMCU_IWDG_STOP: 當內核停止時停止調試 IWDG          
  *          DBGMCU_WWDG_STOP: 當內核停止時停止調試 WWDG          
  *          DBGMCU_TIM1_STOP: 當內核停止時停止 TIM1 計數器          
  *          DBGMCU_TIM2_STOP: 當內核停止時停止 TIM2 計數器         
  *          DBGMCU_TIM3_STOP: 當內核停止時停止 TIM3 計數器         
  *          DBGMCU_TIM4_STOP: 當內核停止時停止 TIM4 計數器        
  *          DBGMCU_CAN1_STOP: 當內核停止時停止調試 CAN1 
  *          DBGMCU_I2C1_SMBUS_TIMEOUT: 當內核停止時停止 I2C1 總線超時模式
  *          DBGMCU_I2C2_SMBUS_TIMEOUT: 當內核停止時停止 I2C2 總線超時模式
  *          DBGMCU_TIM5_STOP: 當內核停止時停止 TIM5 計數器          
  *          DBGMCU_TIM6_STOP: 當內核停止時停止 TIM6 計數器         
  *          DBGMCU_TIM7_STOP: 當內核停止時停止 TIM7 計數器         
  *          DBGMCU_TIM8_STOP: 當內核停止時停止 TIM8 計數器
  *          DBGMCU_CAN2_STOP: 當內核停止時停止調試 CAN2  
  * @參數  NewState: 指定的外設在低功耗模式的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_DBGMCU_PERIPH(DBGMCU_Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    DBGMCU->CR |= DBGMCU_Periph;
  }
  else
  {
    DBGMCU->CR &= ~DBGMCU_Periph;
  }
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
