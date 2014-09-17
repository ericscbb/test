/**
  ******************************************************************************
  * @文件    stm32f10x_dma.c
  * @作者    MCD 應用程序組
  * @版本    V3.1.0
  * @日期    06/19/2009
  * @簡述    這個文件 提供所有 DMA 固件函數.
  * @翻譯    ANSON/sweet1985 Email:airanson110@126.com
  * @日期    18/07/2009
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
#include "stm32f10x_dma.h"
#include "stm32f10x_rcc.h"

/* 自用類型 --------------------------------------------------------------*/
/* 自用定義 --------------------------------------------------------------*/

/* DMA ENABLE mask */
#define CCR_ENABLE_Set          ((uint32_t)0x00000001)
#define CCR_ENABLE_Reset        ((uint32_t)0xFFFFFFFE)

/* DMA1 Channelx interrupt pending bit masks */
#define DMA1_Channel1_IT_Mask    ((uint32_t)0x0000000F)
#define DMA1_Channel2_IT_Mask    ((uint32_t)0x000000F0)
#define DMA1_Channel3_IT_Mask    ((uint32_t)0x00000F00)
#define DMA1_Channel4_IT_Mask    ((uint32_t)0x0000F000)
#define DMA1_Channel5_IT_Mask    ((uint32_t)0x000F0000)
#define DMA1_Channel6_IT_Mask    ((uint32_t)0x00F00000)
#define DMA1_Channel7_IT_Mask    ((uint32_t)0x0F000000)

/* DMA2 Channelx interrupt pending bit masks */
#define DMA2_Channel1_IT_Mask    ((uint32_t)0x0000000F)
#define DMA2_Channel2_IT_Mask    ((uint32_t)0x000000F0)
#define DMA2_Channel3_IT_Mask    ((uint32_t)0x00000F00)
#define DMA2_Channel4_IT_Mask    ((uint32_t)0x0000F000)
#define DMA2_Channel5_IT_Mask    ((uint32_t)0x000F0000)

/* DMA2 FLAG mask */
#define FLAG_Mask                ((uint32_t)0x10000000)

/* DMA registers Masks */
#define CCR_CLEAR_Mask           ((uint32_t)0xFFFF800F)

/* 自用宏 -------------------------------------------------------------*/
/* 自用變量 -----------------------------------------------------------*/
/* 自用函數原型 -------------------------------------------------------*/
/* 自用函數 -----------------------------------------------------------*/

/**
  * @簡述  將 DM A的通道x 寄存器重設為缺省值.
  * @參數  DMAy_Channelx: y 可以是1 或者2，DMA1的x可以是1 到7 和 DMA2 的x 可以是1 到5 來選擇各通道.
  * @返回  沒有
  */
void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx)
{
  /* 檢查參數 */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  /* 失能選定的 DMA y 通道 x */
  DMAy_Channelx->CCR &= CCR_ENABLE_Reset;
  /* 復位 DMA y 通道 x 控制寄存器 */
  DMAy_Channelx->CCR  = 0;
  
  /* 復位 DMA y 通道 x 剩餘字節寄存器 */
  DMAy_Channelx->CNDTR = 0;
  
  /* 復位 DMA y 通道x 外圍設備地址寄存器 */
  DMAy_Channelx->CPAR  = 0;
  
  /* 復位 DMA y 通道 x 內存地址寄存器 */
  DMAy_Channelx->CMAR = 0;
  
  if (DMAy_Channelx == DMA1_Channel1)
  {
    /* 復位 DMA1 通道1 中斷掛起位 */
    DMA1->IFCR |= DMA1_Channel1_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel2)
  {
    /* 復位 DMA1 通道2 中斷掛起位 */
    DMA1->IFCR |= DMA1_Channel2_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel3)
  {
    /* 復位 DMA1 通道3 中斷掛起位 */
    DMA1->IFCR |= DMA1_Channel3_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel4)
  {
    /* 復位 DMA1 通道4 中斷掛起位 */
    DMA1->IFCR |= DMA1_Channel4_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel5)
  {
    /* 復位 DMA1 通道5 中斷掛起位 */
    DMA1->IFCR |= DMA1_Channel5_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel6)
  {
    /* 復位 DMA1 通道6 中斷掛起位 */
    DMA1->IFCR |= DMA1_Channel6_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel7)
  {
    /* 復位 DMA1 通道7 中斷掛起位 */
    DMA1->IFCR |= DMA1_Channel7_IT_Mask;
  }
  else if (DMAy_Channelx == DMA2_Channel1)
  {
    /* 復位 DMA2 通道1 中斷掛起位 */
    DMA2->IFCR |= DMA2_Channel1_IT_Mask;
  }
  else if (DMAy_Channelx == DMA2_Channel2)
  {
    /* 復位 DMA2 通道2 中斷掛起位 */
    DMA2->IFCR |= DMA2_Channel2_IT_Mask;
  }
  else if (DMAy_Channelx == DMA2_Channel3)
  {
    /* 復位 DMA2 通道3 中斷掛起位 */
    DMA2->IFCR |= DMA2_Channel3_IT_Mask;
  }
  else if (DMAy_Channelx == DMA2_Channel4)
  {
    /* 復位 DMA2 通道4 中斷掛起位 */
    DMA2->IFCR |= DMA2_Channel4_IT_Mask;
  }
  else
  { 
    if (DMAy_Channelx == DMA2_Channel5)
    {
      /* 復位 DMA2 通道5 中斷掛起位 */
      DMA2->IFCR |= DMA2_Channel5_IT_Mask;
    }
  }
}

/**
  * @簡述  根據 DMA_InitStruct 中指定的參數初始化 DMA 的通道x 寄存器.
  * @參數  DMAy_Channelx: y 可以是1 或者2 ，DMA1 的x 可以是 1到 7 和DMA2 的x 可以是1 到5 來選擇各通道.
  * @參數  DMA_InitStruct: 指向 DMA_InitTypeDef 的結構體，它包含特定 DMA 通道的配置信息.
  * @返回  沒有
  */
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct)
{
  uint32_t tmpreg = 0;

  /* 檢查參數 */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  assert_param(IS_DMA_DIR(DMA_InitStruct->DMA_DIR));
  assert_param(IS_DMA_BUFFER_SIZE(DMA_InitStruct->DMA_BufferSize));
  assert_param(IS_DMA_PERIPHERAL_INC_STATE(DMA_InitStruct->DMA_PeripheralInc));
  assert_param(IS_DMA_MEMORY_INC_STATE(DMA_InitStruct->DMA_MemoryInc));   
  assert_param(IS_DMA_PERIPHERAL_DATA_SIZE(DMA_InitStruct->DMA_PeripheralDataSize));
  assert_param(IS_DMA_MEMORY_DATA_SIZE(DMA_InitStruct->DMA_MemoryDataSize));
  assert_param(IS_DMA_MODE(DMA_InitStruct->DMA_Mode));
  assert_param(IS_DMA_PRIORITY(DMA_InitStruct->DMA_Priority));
  assert_param(IS_DMA_M2M_STATE(DMA_InitStruct->DMA_M2M));

/*--------------------------- DMAy Channelx CCR Configuration -----------------*/
  /* Get the DMAy_Channelx CCR value */
  tmpreg = DMAy_Channelx->CCR;
  /* Clear MEM2MEM, PL, MSIZE, PSIZE, MINC, PINC, CIRC and DIR bits */
  tmpreg &= CCR_CLEAR_Mask;
  /* Configure DMAy Channelx: data transfer, data size, priority level and mode */
  /* Set DIR bit according to DMA_DIR value */
  /* Set CIRC bit according to DMA_Mode value */
  /* Set PINC bit according to DMA_PeripheralInc value */
  /* Set MINC bit according to DMA_MemoryInc value */
  /* Set PSIZE bits according to DMA_PeripheralDataSize value */
  /* Set MSIZE bits according to DMA_MemoryDataSize value */
  /* Set PL bits according to DMA_Priority value */
  /* Set the MEM2MEM bit according to DMA_M2M value */
  tmpreg |= DMA_InitStruct->DMA_DIR | DMA_InitStruct->DMA_Mode |
            DMA_InitStruct->DMA_PeripheralInc | DMA_InitStruct->DMA_MemoryInc |
            DMA_InitStruct->DMA_PeripheralDataSize | DMA_InitStruct->DMA_MemoryDataSize |
            DMA_InitStruct->DMA_Priority | DMA_InitStruct->DMA_M2M;

  /* Write to DMAy Channelx CCR */
  DMAy_Channelx->CCR = tmpreg;

/*--------------------------- DMAy Channelx CNDTR Configuration ---------------*/
  /* Write to DMAy Channelx CNDTR */
  DMAy_Channelx->CNDTR = DMA_InitStruct->DMA_BufferSize;

/*--------------------------- DMAy Channelx CPAR Configuration ----------------*/
  /* Write to DMAy Channelx CPAR */
  DMAy_Channelx->CPAR = DMA_InitStruct->DMA_PeripheralBaseAddr;

/*--------------------------- DMAy Channelx CMAR Configuration ----------------*/
  /* Write to DMAy Channelx CMAR */
  DMAy_Channelx->CMAR = DMA_InitStruct->DMA_MemoryBaseAddr;
}

/**
  * @brief  Fills each DMA_InitStruct member with its default value.
  * @param  DMA_InitStruct : pointer to a DMA_InitTypeDef structure which will
  *   be initialized.
  * @retval None
  */
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct)
{
/*-------------- Reset DMA init structure parameters values ------------------*/
  /* 初始化 DMA_PeripheralBaseAddr 成員 */
  DMA_InitStruct->DMA_PeripheralBaseAddr = 0;
  /* 初始化 DMA_MemoryBaseAddr 成員 */
  DMA_InitStruct->DMA_MemoryBaseAddr = 0;
  /* 初始化 DMA_DIR 成員 */
  DMA_InitStruct->DMA_DIR = DMA_DIR_PeripheralSRC;
  /* 初始化 DMA_BufferSize 成員 */
  DMA_InitStruct->DMA_BufferSize = 0;
  /* 初始化 DMA_PeripheralInc 成員 */
  DMA_InitStruct->DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  /* 初始化 DMA_MemoryInc 成員 */
  DMA_InitStruct->DMA_MemoryInc = DMA_MemoryInc_Disable;
  /* 初始化 DMA_PeripheralDataSize 成員 */
  DMA_InitStruct->DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  /* 初始化 DMA_MemoryDataSize 成員 */
  DMA_InitStruct->DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  /* 初始化 DMA_Mode 成員 */
  DMA_InitStruct->DMA_Mode = DMA_Mode_Normal;
  /* 初始化 DMA_Priority 成員 */
  DMA_InitStruct->DMA_Priority = DMA_Priority_Low;
  /* 初始化 DMA_M2M 成員 */
  DMA_InitStruct->DMA_M2M = DMA_M2M_Disable;
}

/**
  * @簡述  使能或失能指定的 DMA y 通道 x.
  * @參數  DMAy_Channelx: y 可以是1 或者2 ，DMA1 的x 可以是1 到7 和DMA2 的x 可以是1 到5 來選擇各通道.
  * @參數  NewState: DMA y 通道x 的新狀態. 
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* 使能指定的 DMA y 通道 x */
    DMAy_Channelx->CCR |= CCR_ENABLE_Set;
  }
  else
  {
    /* 失能指定的 DMA y 通道 x */
    DMAy_Channelx->CCR &= CCR_ENABLE_Reset;
  }
}

/**
  * @簡述  使能或失能指定的 DMA y 通道 x 中斷.
  * @參數  DMAy_Channelx: y 可以是1 或者2 ，DMA1 的x 可以是1 到7 和DMA2 的x 可以是1 到5 來選擇各通道.
  * @參數  DMA_IT: 指定 DMA 的中斷. 
  *            這個參數可以是下面值的任意組合:
  *            DMA_IT_TC:  傳輸完成中斷屏蔽
  *            DMA_IT_HT:  傳輸過半中斷屏蔽
  *            DMA_IT_TE:  傳輸錯誤中斷屏蔽
  * @參數  NewState: 指定的 DMA 中斷的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void DMA_ITConfig(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t DMA_IT, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  assert_param(IS_DMA_CONFIG_IT(DMA_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 使能指定的 DMA 中斷 */
    DMAy_Channelx->CCR |= DMA_IT;
  }
  else
  {
    /* 失能指定的 DMA 中斷 */
    DMAy_Channelx->CCR &= ~DMA_IT;
  }
}

/**
  * @簡述  返回當前 DMA y 通道x 剩餘的待傳輸數據數目.
  * @參數  DMAy_Channelx: y 可以是1 或者2 ，DMA1 的x 可以是1 到7 和DMA2 的x 可以是1 到5 來選擇各通道.
  * @返回  當前 DMA y 通道x 傳輸中剩餘的數據單元的數量.
  */
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx)
{
  /* 檢查參數 */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  /* 返回 DMA y 通道x 傳輸中剩餘的數據單元的數量 */
  return ((uint16_t)(DMAy_Channelx->CNDTR));
}

/**
  * @簡述  檢查指定的 DMA y 通道 x 標誌位設置與否.
  * @參數  DMA_FLAG: 指定的標誌.
  *          這個參數可以是下面的值之一:
*            DMA1_FLAG_GL1: DMA1通道1全局標誌
*            DMA1_FLAG_TC1: DMA1通道1傳輸結束標誌
*            DMA1_FLAG_HT1: DMA1通道1半傳輸標誌
*            DMA1_FLAG_TE1: DMA1通道1傳輸錯誤標誌
*            DMA1_FLAG_GL2: DMA1 通道2 全局標誌.
*            DMA1_FLAG_TC2: DMA1 通道2 傳輸結束標誌.
*            DMA1_FLAG_HT2: DMA1 通道2 半傳輸標誌.
*            DMA1_FLAG_TE2: DMA1 通道2 傳輸錯誤標誌.
*            DMA1_FLAG_GL3: DMA1 通道3 全局標誌.
*            DMA1_FLAG_TC3: DMA1 通道3 傳輸結束標誌.
*            DMA1_FLAG_HT3: DMA1 通道3 半傳輸標誌.
*            DMA1_FLAG_TE3: DMA1 通道3 傳輸錯誤標誌.
*            DMA1_FLAG_GL4: DMA1 通道4 全局標誌.
*            DMA1_FLAG_TC4: DMA1 通道4 傳輸結束標誌.
*            DMA1_FLAG_HT4: DMA1 通道4 半傳輸標誌.
*            DMA1_FLAG_TE4: DMA1 通道4 傳輸錯誤標誌.
*            DMA1_FLAG_GL5: DMA1 通道5 全局標誌.
*            DMA1_FLAG_TC5: DMA1 通道5 傳輸結束標誌.
*            DMA1_FLAG_HT5: DMA1 通道5 半傳輸標誌.
*            DMA1_FLAG_TE5: DMA1 通道5 傳輸錯誤標誌.
*            DMA1_FLAG_GL6: DMA1 通道6 全局標誌.
*            DMA1_FLAG_TC6: DMA1 通道6 傳輸結束標誌.
*            DMA1_FLAG_HT6: DMA1 通道6 半傳輸標誌.
*            DMA1_FLAG_TE6: DMA1 通道6 傳輸錯誤標誌.
*            DMA1_FLAG_GL7: DMA1 通道7 全局標誌.
*            DMA1_FLAG_TC7: DMA1 通道7 傳輸結束標誌.
*            DMA1_FLAG_HT7: DMA1 通道7 半傳輸標誌.
*            DMA1_FLAG_TE7: DMA1 通道7 傳輸錯誤標誌.
*            DMA2_FLAG_GL1: DMA2 通道1 全局標誌.
*            DMA2_FLAG_TC1: DMA2 通道1 傳輸結束標誌.
*            DMA2_FLAG_HT1: DMA2 通道1 半傳輸標誌.
*            DMA2_FLAG_TE1: DMA2 通道1 傳輸錯誤標誌.
*            DMA2_FLAG_GL2: DMA2 通道2 全局標誌.
*            DMA2_FLAG_TC2: DMA2 通道2 傳輸結束標誌.
*            DMA2_FLAG_HT2: DMA2 通道2 半傳輸標誌.
*            DMA2_FLAG_TE2: DMA2 通道2 傳輸錯誤標誌.
*            DMA2_FLAG_GL3: DMA2 通道3 全局標誌.
*            DMA2_FLAG_TC3: DMA2 通道3 傳輸結束標誌.
*            DMA2_FLAG_HT3: DMA2 通道3 半傳輸標誌.
*            DMA2_FLAG_TE3: DMA2 通道3 傳輸錯誤標誌.
*            DMA2_FLAG_GL4: DMA2 通道4 全局標誌.
*            DMA2_FLAG_TC4: DMA2 通道4 傳輸結束標誌.
*            DMA2_FLAG_HT4: DMA2 通道4 半傳輸標誌.
*            DMA2_FLAG_TE4: DMA2 通道4 傳輸錯誤標誌.
*            DMA2_FLAG_GL5: DMA2 通道5 全局標誌.
*            DMA2_FLAG_TC5: DMA2 通道5 傳輸結束標誌.
*            DMA2_FLAG_HT5: DMA2 通道5 半傳輸標誌.
*            DMA2_FLAG_TE5: DMA2 通道5 傳輸錯誤標誌.
  * @返回  DMA_FLAG 的新狀態 (SET 或 RESET).
  */
FlagStatus DMA_GetFlagStatus(uint32_t DMA_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint32_t tmpreg = 0;
  /* 檢查參數 */
  assert_param(IS_DMA_GET_FLAG(DMA_FLAG));

  /* 計算使用的 DMA */
  if ((DMA_FLAG & FLAG_Mask) != (uint32_t)RESET)
  {
    /* 得到 DMA2 ISR 寄存器的值 */
    tmpreg = DMA2->ISR ;
  }
  else
  {
    /* 得到 DMA1 ISR 寄存器的值 */
    tmpreg = DMA1->ISR ;
  }

  /* 檢查指定的 DMA 標誌的新狀態 */
  if ((tmpreg & DMA_FLAG) != (uint32_t)RESET)
  {
    /* 設置 DMA_FLAG */
    bitstatus = SET;
  }
  else
  {
    /* 復位 DMA_FLAG */
    bitstatus = RESET;
  }
  
  /* 返回 DMA_FLAG 狀態 */
  return  bitstatus;
}

/**
  * @簡述  清除定的 DMA y 通道 x 待處理標誌位.
  * @參數  DMA_FLAG: 指定的待處理標誌位.
  *          這個參數可以是下面值的任意組合 (對於同一個 DMA) :
*            DMA1_FLAG_GL1: DMA1通道1全局標誌
*            DMA1_FLAG_TC1: DMA1通道1傳輸結束標誌
*            DMA1_FLAG_HT1: DMA1通道1半傳輸標誌
*            DMA1_FLAG_TE1: DMA1通道1傳輸錯誤標誌
*            DMA1_FLAG_GL2: DMA1 通道2 全局標誌.
*            DMA1_FLAG_TC2: DMA1 通道2 傳輸結束標誌.
*            DMA1_FLAG_HT2: DMA1 通道2 半傳輸標誌.
*            DMA1_FLAG_TE2: DMA1 通道2 傳輸錯誤標誌.
*            DMA1_FLAG_GL3: DMA1 通道3 全局標誌.
*            DMA1_FLAG_TC3: DMA1 通道3 傳輸結束標誌.
*            DMA1_FLAG_HT3: DMA1 通道3 半傳輸標誌.
*            DMA1_FLAG_TE3: DMA1 通道3 傳輸錯誤標誌.
*            DMA1_FLAG_GL4: DMA1 通道4 全局標誌.
*            DMA1_FLAG_TC4: DMA1 通道4 傳輸結束標誌.
*            DMA1_FLAG_HT4: DMA1 通道4 半傳輸標誌.
*            DMA1_FLAG_TE4: DMA1 通道4 傳輸錯誤標誌.
*            DMA1_FLAG_GL5: DMA1 通道5 全局標誌.
*            DMA1_FLAG_TC5: DMA1 通道5 傳輸結束標誌.
*            DMA1_FLAG_HT5: DMA1 通道5 半傳輸標誌.
*            DMA1_FLAG_TE5: DMA1 通道5 傳輸錯誤標誌.
*            DMA1_FLAG_GL6: DMA1 通道6 全局標誌.
*            DMA1_FLAG_TC6: DMA1 通道6 傳輸結束標誌.
*            DMA1_FLAG_HT6: DMA1 通道6 半傳輸標誌.
*            DMA1_FLAG_TE6: DMA1 通道6 傳輸錯誤標誌.
*            DMA1_FLAG_GL7: DMA1 通道7 全局標誌.
*            DMA1_FLAG_TC7: DMA1 通道7 傳輸結束標誌.
*            DMA1_FLAG_HT7: DMA1 通道7 半傳輸標誌.
*            DMA1_FLAG_TE7: DMA1 通道7 傳輸錯誤標誌.
*            DMA2_FLAG_GL1: DMA2 通道1 全局標誌.
*            DMA2_FLAG_TC1: DMA2 通道1 傳輸結束標誌.
*            DMA2_FLAG_HT1: DMA2 通道1 半傳輸標誌.
*            DMA2_FLAG_TE1: DMA2 通道1 傳輸錯誤標誌.
*            DMA2_FLAG_GL2: DMA2 通道2 全局標誌.
*            DMA2_FLAG_TC2: DMA2 通道2 傳輸結束標誌.
*            DMA2_FLAG_HT2: DMA2 通道2 半傳輸標誌.
*            DMA2_FLAG_TE2: DMA2 通道2 傳輸錯誤標誌.
*            DMA2_FLAG_GL3: DMA2 通道3 全局標誌.
*            DMA2_FLAG_TC3: DMA2 通道3 傳輸結束標誌.
*            DMA2_FLAG_HT3: DMA2 通道3 半傳輸標誌.
*            DMA2_FLAG_TE3: DMA2 通道3 傳輸錯誤標誌.
*            DMA2_FLAG_GL4: DMA2 通道4 全局標誌.
*            DMA2_FLAG_TC4: DMA2 通道4 傳輸結束標誌.
*            DMA2_FLAG_HT4: DMA2 通道4 半傳輸標誌.
*            DMA2_FLAG_TE4: DMA2 通道4 傳輸錯誤標誌.
*            DMA2_FLAG_GL5: DMA2 通道5 全局標誌.
*            DMA2_FLAG_TC5: DMA2 通道5 傳輸結束標誌.
*            DMA2_FLAG_HT5: DMA2 通道5 半傳輸標誌.
*            DMA2_FLAG_TE5: DMA2 通道5 傳輸錯誤標誌.
  * @返回  沒有
  */
void DMA_ClearFlag(uint32_t DMA_FLAG)
{
  /* 檢查參數 */
  assert_param(IS_DMA_CLEAR_FLAG(DMA_FLAG));
  /* 計算使用的 DMA */

  if ((DMA_FLAG & FLAG_Mask) != (uint32_t)RESET)
  {
    /* 清除選定的 DMA 標誌 */
    DMA2->IFCR = DMA_FLAG;
  }
  else
  {
    /* 清除選定的 DMA 標誌 */
    DMA1->IFCR = DMA_FLAG;
  }
}

/**
  * @簡述  檢查指定的 DMA y 通道 x 中斷發生與否.
  * @參數  DMA_IT: 指定的 DMA 中斷源. 
*             這個參數可以是下面的值之一:
*             DMA1_IT_GL1: DMA1 通道1 全局中斷.
*             DMA1_IT_TC1: DMA1 通道1 傳輸完成中斷.
*             DMA1_IT_HT1: DMA1 通道1 半傳輸中斷.
*             DMA1_IT_TE1: DMA1 通道1 傳輸錯誤中斷.
*             DMA1_IT_GL2: DMA1 通道2 全局中斷.
*             DMA1_IT_TC2: DMA1 通道2 傳輸完成中斷.
*             DMA1_IT_HT2: DMA1 通道2 半傳輸中斷.
*             DMA1_IT_TE2: DMA1 通道2 傳輸錯誤中斷.
*             DMA1_IT_GL3: DMA1 通道3 全局中斷.
*             DMA1_IT_TC3: DMA1 通道3 傳輸完成中斷.
*             DMA1_IT_HT3: DMA1 通道3 半傳輸中斷.
*             DMA1_IT_TE3: DMA1 通道3 傳輸錯誤中斷.
*             DMA1_IT_GL4: DMA1 通道4 全局中斷.
*             DMA1_IT_TC4: DMA1 通道4 傳輸完成中斷.
*             DMA1_IT_HT4: DMA1 通道4 半傳輸中斷.
*             DMA1_IT_TE4: DMA1 通道4 傳輸錯誤中斷.
*             DMA1_IT_GL5: DMA1 通道5 全局中斷.
*             DMA1_IT_TC5: DMA1 通道5 傳輸完成中斷.
*             DMA1_IT_HT5: DMA1 通道5 半傳輸中斷.
*             DMA1_IT_TE5: DMA1 通道5 傳輸錯誤中斷.
*             DMA1_IT_GL6: DMA1 通道6 全局中斷.
*             DMA1_IT_TC6: DMA1 通道6 傳輸完成中斷.
*             DMA1_IT_HT6: DMA1 通道6 半傳輸中斷.
*             DMA1_IT_TE6: DMA1 通道6 傳輸錯誤中斷.
*             DMA1_IT_GL7: DMA1 通道7 全局中斷.
*             DMA1_IT_TC7: DMA1 通道7 傳輸完成中斷.
*             DMA1_IT_HT7: DMA1 通道7 半傳輸中斷.
*             DMA1_IT_TE7: DMA1 通道7 傳輸錯誤中斷.
*             DMA2_IT_GL1: DMA2 通道1 全局中斷.
*             DMA2_IT_TC1: DMA2 通道1 傳輸完成中斷.
*             DMA2_IT_HT1: DMA2 通道1 半傳輸中斷.
*             DMA2_IT_TE1: DMA2 通道1 傳輸錯誤中斷.
*             DMA2_IT_GL2: DMA2 通道2 全局中斷.
*             DMA2_IT_TC2: DMA2 通道2 傳輸完成中斷.
*             DMA2_IT_HT2: DMA2 通道2 半傳輸中斷.
*             DMA2_IT_TE2: DMA2 通道2 傳輸錯誤中斷.
*             DMA2_IT_GL3: DMA2 通道3 全局中斷.
*             DMA2_IT_TC3: DMA2 通道3 傳輸完成中斷.
*             DMA2_IT_HT3: DMA2 通道3 半傳輸中斷.
*             DMA2_IT_TE3: DMA2 通道3 傳輸錯誤中斷.
*             DMA2_IT_GL4: DMA2 通道4 全局中斷.
*             DMA2_IT_TC4: DMA2 通道4 傳輸完成中斷.
*             DMA2_IT_HT4: DMA2 通道4 半傳輸中斷.
*             DMA2_IT_TE4: DMA2 通道4 傳輸錯誤中斷.
*             DMA2_IT_GL5: DMA2 通道5 全局中斷.
*             DMA2_IT_TC5: DMA2 通道5 傳輸完成中斷.
*             DMA2_IT_HT5: DMA2 通道5 半傳輸中斷.
*             DMA2_IT_TE5: DMA2 通道5 傳輸錯誤中斷.
  * @返回  DMA_IT 的新狀態 (SET 或 RESET).
  */
ITStatus DMA_GetITStatus(uint32_t DMA_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t tmpreg = 0;
  /* 檢查參數 */
  assert_param(IS_DMA_GET_IT(DMA_IT));

  /* 計算使用的 DMA */
  if ((DMA_IT & FLAG_Mask) != (uint32_t)RESET)
  {
    /* 得到 DMA2 ISR 寄存器的值 */
    tmpreg = DMA2->ISR ;
  }
  else
  {
    /* 得到 DMA1 ISR 寄存器的值 */
    tmpreg = DMA1->ISR ;
  }

  /* 檢查指定的 DMA 中斷 */
  if ((tmpreg & DMA_IT) != (uint32_t)RESET)
  {
    /* 設置 DMA_IT */
    bitstatus = SET;
  }
  else
  {
    /* 復位 DMA_IT */
    bitstatus = RESET;
  }
  /* 返回 DMA_IT 狀態 */
  return  bitstatus;
}

/**
  * @簡述  清除 DMA y 通道 x 中斷待處理標誌位.
  * @參數  DMA_IT: 指定的 DMA 中斷掛起位.
*             這個參數可以是下面的值之一:
*             DMA1_IT_GL1: DMA1 通道1 全局中斷.
*             DMA1_IT_TC1: DMA1 通道1 傳輸完成中斷.
*             DMA1_IT_HT1: DMA1 通道1 半傳輸中斷.
*             DMA1_IT_TE1: DMA1 通道1 傳輸錯誤中斷.
*             DMA1_IT_GL2: DMA1 通道2 全局中斷.
*             DMA1_IT_TC2: DMA1 通道2 傳輸完成中斷.
*             DMA1_IT_HT2: DMA1 通道2 半傳輸中斷.
*             DMA1_IT_TE2: DMA1 通道2 傳輸錯誤中斷.
*             DMA1_IT_GL3: DMA1 通道3 全局中斷.
*             DMA1_IT_TC3: DMA1 通道3 傳輸完成中斷.
*             DMA1_IT_HT3: DMA1 通道3 半傳輸中斷.
*             DMA1_IT_TE3: DMA1 通道3 傳輸錯誤中斷.
*             DMA1_IT_GL4: DMA1 通道4 全局中斷.
*             DMA1_IT_TC4: DMA1 通道4 傳輸完成中斷.
*             DMA1_IT_HT4: DMA1 通道4 半傳輸中斷.
*             DMA1_IT_TE4: DMA1 通道4 傳輸錯誤中斷.
*             DMA1_IT_GL5: DMA1 通道5 全局中斷.
*             DMA1_IT_TC5: DMA1 通道5 傳輸完成中斷.
*             DMA1_IT_HT5: DMA1 通道5 半傳輸中斷.
*             DMA1_IT_TE5: DMA1 通道5 傳輸錯誤中斷.
*             DMA1_IT_GL6: DMA1 通道6 全局中斷.
*             DMA1_IT_TC6: DMA1 通道6 傳輸完成中斷.
*             DMA1_IT_HT6: DMA1 通道6 半傳輸中斷.
*             DMA1_IT_TE6: DMA1 通道6 傳輸錯誤中斷.
*             DMA1_IT_GL7: DMA1 通道7 全局中斷.
*             DMA1_IT_TC7: DMA1 通道7 傳輸完成中斷.
*             DMA1_IT_HT7: DMA1 通道7 半傳輸中斷.
*             DMA1_IT_TE7: DMA1 通道7 傳輸錯誤中斷.
*             DMA2_IT_GL1: DMA2 通道1 全局中斷.
*             DMA2_IT_TC1: DMA2 通道1 傳輸完成中斷.
*             DMA2_IT_HT1: DMA2 通道1 半傳輸中斷.
*             DMA2_IT_TE1: DMA2 通道1 傳輸錯誤中斷.
*             DMA2_IT_GL2: DMA2 通道2 全局中斷.
*             DMA2_IT_TC2: DMA2 通道2 傳輸完成中斷.
*             DMA2_IT_HT2: DMA2 通道2 半傳輸中斷.
*             DMA2_IT_TE2: DMA2 通道2 傳輸錯誤中斷.
*             DMA2_IT_GL3: DMA2 通道3 全局中斷.
*             DMA2_IT_TC3: DMA2 通道3 傳輸完成中斷.
*             DMA2_IT_HT3: DMA2 通道3 半傳輸中斷.
*             DMA2_IT_TE3: DMA2 通道3 傳輸錯誤中斷.
*             DMA2_IT_GL4: DMA2 通道4 全局中斷.
*             DMA2_IT_TC4: DMA2 通道4 傳輸完成中斷.
*             DMA2_IT_HT4: DMA2 通道4 半傳輸中斷.
*             DMA2_IT_TE4: DMA2 通道4 傳輸錯誤中斷.
*             DMA2_IT_GL5: DMA2 通道5 全局中斷.
*             DMA2_IT_TC5: DMA2 通道5 傳輸完成中斷.
*             DMA2_IT_HT5: DMA2 通道5 半傳輸中斷.
*             DMA2_IT_TE5: DMA2 通道5 傳輸錯誤中斷.
  * @返回  沒有
  */
void DMA_ClearITPendingBit(uint32_t DMA_IT)
{
  /* 檢查參數 */
  assert_param(IS_DMA_CLEAR_IT(DMA_IT));

  /* 計算使用的 DMA */
  if ((DMA_IT & FLAG_Mask) != (uint32_t)RESET)
  {
    /* 清除選擇的DMA中斷掛起位 */
    DMA2->IFCR = DMA_IT;
  }
  else
  {
    /* 清除選擇的DMA中斷掛起位 */
    DMA1->IFCR = DMA_IT;
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
