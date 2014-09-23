/**
  ******************************************************************************
  * @文件    misc.c
  * @作者    MCD 應用程序組
  * @版本    V3.1.0
  * @日期    06/19/2009
  * @簡述    這個文件提供給所有其他的固件函數 (追加 CMSIS<微控制器軟件接口標準> 函數).
  * @翻譯    ANSON/sweet1985 Email:airanson110@126.com
  * @日期    02/07/2009
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
#include "misc.h"

/* 自用類型 --------------------------------------------------------------*/
/* 自用定義 --------------------------------------------------------------*/

#define AIRCR_VECTKEY_MASK    ((uint32_t)0x05FA0000)

/* 自用宏 ------------------------------------------------------------*/
/* 自用變量 ----------------------------------------------------------*/

/* 自用函數原型 ------------------------------------------------------*/
/* 自用函數 ----------------------------------------------------------*/


/**
  * @簡述  設置優先級分組：先佔優先級和從優先級.
  * @參數  NVIC_PriorityGroup: 優先級分組位長度. 
  *                            這個參數可以取下列值中的一個:
  *          NVIC_PriorityGroup_0: 先佔優先級0位
  *                                從優先級4位
  *          NVIC_PriorityGroup_1: 先佔優先級1位
  *                                從優先級3位
  *          NVIC_PriorityGroup_2: 先佔優先級2位
  *                                從優先級2位
  *          NVIC_PriorityGroup_3: 先佔優先級3位
  *                                從優先級1位
  *          NVIC_PriorityGroup_4: 先佔優先級4位
  *                                從優先級0位
  * @返回  沒有
  */
void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup)
{
  /* 檢查參數 */
  assert_param(IS_NVIC_PRIORITY_GROUP(NVIC_PriorityGroup));
  
  /* 依照NVIC_PriorityGroup的值設置PRIGROUP[10:8]的位 */
  SCB->AIRCR = AIRCR_VECTKEY_MASK | NVIC_PriorityGroup;
}

/**
  * @簡述  通過NVIC_InitStruct中的指定參數來初始化外圍設備.
  * @參數  NVIC_InitStruct: 一個指向包含指定 NVIC 外圍設備配置信息的 NVIC_InitTypeDef 結構的指針.
  * @返回  沒有
  */
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct)
{
  uint32_t tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;
  
  /* 檢查參數 */
  assert_param(IS_FUNCTIONAL_STATE(NVIC_InitStruct->NVIC_IRQChannelCmd));
  assert_param(IS_NVIC_PREEMPTION_PRIORITY(NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority));  
  assert_param(IS_NVIC_SUB_PRIORITY(NVIC_InitStruct->NVIC_IRQChannelSubPriority));
    
  if (NVIC_InitStruct->NVIC_IRQChannelCmd != DISABLE)
  {
    /* 計算符合 IRQ(中斷請求) 優先權 --------------------------------*/    
    tmppriority = (0x700 - ((SCB->AIRCR) & (uint32_t)0x700))>> 0x08;
    tmppre = (0x4 - tmppriority);
    tmpsub = tmpsub >> tmppriority;

    tmppriority = (uint32_t)NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority << tmppre;
    tmppriority |=  NVIC_InitStruct->NVIC_IRQChannelSubPriority & tmpsub;
    tmppriority = tmppriority << 0x04;
        
    NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel] = tmppriority;
    
    /* 使能選擇的 IRQ(中斷請求) 通道 --------------------------------------*/
    NVIC->ISER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
      (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
  else
  {
    /* 失能選擇的 IRQ(中斷請求) 通道 -------------------------------------*/
    NVIC->ICER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
      (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
}

/**
  * @簡述  設置向量表的位置和偏移量.
  * @參數  NVIC_VectTab: 指定向量表在 RAM 或 FLASH .
  *                      這個參數可以取下列值中的一個:
  *                      NVIC_VectTab_RAM
  *                      NVIC_VectTab_FLASH
  * @參數  Offset: 向量表基地址的偏移量. 這個值必須是 0x100 的整倍數.
  * @返回  沒有
  */
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset)
{ 
  /* 檢查參數 */
  assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
  assert_param(IS_NVIC_OFFSET(Offset));  
   
  SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
}

/**
  * @簡述  選擇系統進入低功耗模式的條件.
  * @參數  LowPowerMode: 系統為進入低功耗模式的新模式.
  *                      這個參數可以取下面的值之一:
  *                      NVIC_LP_SEVONPEND
  *                      NVIC_LP_SLEEPDEEP
  *                      NVIC_LP_SLEEPONEXIT
  * @參數  NewState: LP 條件的新狀態.這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_NVIC_LP(LowPowerMode));
  assert_param(IS_FUNCTIONAL_STATE(NewState));  
  
  if (NewState != DISABLE)
  {
    SCB->SCR |= LowPowerMode;
  }
  else
  {
    SCB->SCR &= (uint32_t)(~(uint32_t)LowPowerMode);
  }
}

/**
  * @簡述  設置 SysTick 時鐘源.
  * @參數  SysTick_CLKSource: 指定 SysTick 時鐘源.
  *                           這個參數可以取下面的值之一:
  *          SysTick_CLKSource_HCLK_Div8: SysTick 時鐘源為AHB時鐘的1/8.
  *          SysTick_CLKSource_HCLK:      SysTick 時鐘源為AHB時鐘.
  * @返回  沒有
  */
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource)
{
  /* 檢查參數 */
  assert_param(IS_SYSTICK_CLK_SOURCE(SysTick_CLKSource));
  if (SysTick_CLKSource == SysTick_CLKSource_HCLK)
  {
    SysTick->CTRL |= SysTick_CLKSource_HCLK;
  }
  else
  {
    SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;
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
