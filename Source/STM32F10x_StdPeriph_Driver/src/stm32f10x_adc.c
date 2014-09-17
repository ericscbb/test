/**
  ******************************************************************************
  * @文件    stm32f10x_adc.c
  * @作者    MCD 應用程序組
  * @版本    V3.1.0
  * @日期    06/19/2009
  * @簡述    這個文件 提供所有 ADC 固件函數.
  * @翻譯    ANSON/sweet1985 Email:airanson110@126.com
  * @日期    17/07/2009
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
#include "stm32f10x_adc.h"
#include "stm32f10x_rcc.h"

/* 自用類型 --------------------------------------------------------------*/
/* 自用定義 --------------------------------------------------------------*/

/* ADC DISCNUM mask */
#define CR1_DISCNUM_Reset           ((uint32_t)0xFFFF1FFF)

/* ADC DISCEN mask */
#define CR1_DISCEN_Set              ((uint32_t)0x00000800)
#define CR1_DISCEN_Reset            ((uint32_t)0xFFFFF7FF)

/* ADC JAUTO mask */
#define CR1_JAUTO_Set               ((uint32_t)0x00000400)
#define CR1_JAUTO_Reset             ((uint32_t)0xFFFFFBFF)

/* ADC JDISCEN mask */
#define CR1_JDISCEN_Set             ((uint32_t)0x00001000)
#define CR1_JDISCEN_Reset           ((uint32_t)0xFFFFEFFF)

/* ADC AWDCH mask */
#define CR1_AWDCH_Reset             ((uint32_t)0xFFFFFFE0)

/* ADC Analog watchdog enable mode mask */
#define CR1_AWDMode_Reset           ((uint32_t)0xFF3FFDFF)

/* CR1 register Mask */
#define CR1_CLEAR_Mask              ((uint32_t)0xFFF0FEFF)

/* ADC ADON mask */
#define CR2_ADON_Set                ((uint32_t)0x00000001)
#define CR2_ADON_Reset              ((uint32_t)0xFFFFFFFE)

/* ADC DMA mask */
#define CR2_DMA_Set                 ((uint32_t)0x00000100)
#define CR2_DMA_Reset               ((uint32_t)0xFFFFFEFF)

/* ADC RSTCAL mask */
#define CR2_RSTCAL_Set              ((uint32_t)0x00000008)

/* ADC CAL mask */
#define CR2_CAL_Set                 ((uint32_t)0x00000004)

/* ADC SWSTART mask */
#define CR2_SWSTART_Set             ((uint32_t)0x00400000)

/* ADC EXTTRIG mask */
#define CR2_EXTTRIG_Set             ((uint32_t)0x00100000)
#define CR2_EXTTRIG_Reset           ((uint32_t)0xFFEFFFFF)

/* ADC Software start mask */
#define CR2_EXTTRIG_SWSTART_Set     ((uint32_t)0x00500000)
#define CR2_EXTTRIG_SWSTART_Reset   ((uint32_t)0xFFAFFFFF)

/* ADC JEXTSEL mask */
#define CR2_JEXTSEL_Reset           ((uint32_t)0xFFFF8FFF)

/* ADC JEXTTRIG mask */
#define CR2_JEXTTRIG_Set            ((uint32_t)0x00008000)
#define CR2_JEXTTRIG_Reset          ((uint32_t)0xFFFF7FFF)

/* ADC JSWSTART mask */
#define CR2_JSWSTART_Set            ((uint32_t)0x00200000)

/* ADC injected software start mask */
#define CR2_JEXTTRIG_JSWSTART_Set   ((uint32_t)0x00208000)
#define CR2_JEXTTRIG_JSWSTART_Reset ((uint32_t)0xFFDF7FFF)

/* ADC TSPD mask */
#define CR2_TSVREFE_Set             ((uint32_t)0x00800000)
#define CR2_TSVREFE_Reset           ((uint32_t)0xFF7FFFFF)

/* CR2 register Mask */
#define CR2_CLEAR_Mask              ((uint32_t)0xFFF1F7FD)

/* ADC SQx mask */
#define SQR3_SQ_Set                 ((uint32_t)0x0000001F)
#define SQR2_SQ_Set                 ((uint32_t)0x0000001F)
#define SQR1_SQ_Set                 ((uint32_t)0x0000001F)

/* SQR1 register Mask */
#define SQR1_CLEAR_Mask             ((uint32_t)0xFF0FFFFF)

/* ADC JSQx mask */
#define JSQR_JSQ_Set                ((uint32_t)0x0000001F)

/* ADC JL mask */
#define JSQR_JL_Set                 ((uint32_t)0x00300000)
#define JSQR_JL_Reset               ((uint32_t)0xFFCFFFFF)

/* ADC SMPx mask */
#define SMPR1_SMP_Set               ((uint32_t)0x00000007)
#define SMPR2_SMP_Set               ((uint32_t)0x00000007)

/* ADC JDRx registers offset */
#define JDR_Offset                  ((uint8_t)0x28)

/* ADC1 DR register base address */
#define DR_ADDRESS                  ((uint32_t)0x4001244C)

/* 自用宏 -------------------------------------------------------------*/
/* 自用變量 -----------------------------------------------------------*/
/* 自用函數原型 -------------------------------------------------------*/
/* 自用函數 -----------------------------------------------------------*/

/**
  * @簡述  將外設 ADCx 的全部寄存器重設為缺省值.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @返回  沒有
  */
void ADC_DeInit(ADC_TypeDef* ADCx)
{
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  
  if (ADCx == ADC1)
  {
    /* 使能 ADC1 復位狀態 */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);
    /* 從復位狀態釋放 ADC1  */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);
  }
  else if (ADCx == ADC2)
  {
    /* 使能 ADC2 復位狀態 */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2, ENABLE);
    /* 從復位狀態釋放 ADC2 */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2, DISABLE);
  }
  else
  {
    if (ADCx == ADC3)
    {
      /* 使能 ADC3 復位狀態 */
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3, ENABLE);
      /* 從復位狀態釋放 ADC3 */
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3, DISABLE);
    }
  }
}

/**
  * @簡述  根據 ADC_InitStruct 中指定的參數初始化外設 ADCx 的寄存器.
  * @參數  ADCx: 其中x 可以是1 2或3，用來選擇ADC 外圍模塊.
  * @參數  ADC_InitStruct: 指向結構體 ADC_InitTypeDef 的指針,該結構包括了指定ADC外圍模塊的配置信息.
  * @返回  沒有
  */
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct)
{
  uint32_t tmpreg1 = 0;
  uint8_t tmpreg2 = 0;
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_MODE(ADC_InitStruct->ADC_Mode));
  assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_ScanConvMode));
  assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_ContinuousConvMode));
  assert_param(IS_ADC_EXT_TRIG(ADC_InitStruct->ADC_ExternalTrigConv));   
  assert_param(IS_ADC_DATA_ALIGN(ADC_InitStruct->ADC_DataAlign)); 
  assert_param(IS_ADC_REGULAR_LENGTH(ADC_InitStruct->ADC_NbrOfChannel));

  /*---------------------------- ADCx CR1 Configuration -----------------*/
  /* 得到 ADCx CR1 的值 */
  tmpreg1 = ADCx->CR1;
  /* 清除 DUALMOD 和 SCAN 位 */
  tmpreg1 &= CR1_CLEAR_Mask;
  /* 配置 ADCx: 雙重模式和掃瞄轉換模式 */
  /* 設置 DUALMOD 位， 按照 ADC_Mode 的值 */
  /* 設置 SCAN 位，按照 ADC_ScanConvMode 的值 */
  tmpreg1 |= (uint32_t)(ADC_InitStruct->ADC_Mode | ((uint32_t)ADC_InitStruct->ADC_ScanConvMode << 8));
  /* 寫 ADCx CR1 */
  ADCx->CR1 = tmpreg1;

  /*---------------------------- ADCx CR2 Configuration -----------------*/
  /* 得到 ADCx CR2 的值 */
  tmpreg1 = ADCx->CR2;
  /* 清除 CONT, ALIGN 和 EXTSEL 位 */
  tmpreg1 &= CR2_CLEAR_Mask;
  /* 配置 ADCx: 外觸發事件和連續轉換模式 */
  /* 設置 ALIGN 位，按照 ADC_DataAlign 的值 */
  /* 設置 EXTSEL 位，按照 ADC_ExternalTrigConv 的值 */
  /* 設置 CONT 位，按照 ADC_ContinuousConvMode 的值 */
  tmpreg1 |= (uint32_t)(ADC_InitStruct->ADC_DataAlign | ADC_InitStruct->ADC_ExternalTrigConv |
            ((uint32_t)ADC_InitStruct->ADC_ContinuousConvMode << 1));
  /* 寫 ADCx CR2 */
  ADCx->CR2 = tmpreg1;

  /*---------------------------- ADCx SQR1 Configuration -----------------*/
  /* 得到 ADCx SQR1 的值 */
  tmpreg1 = ADCx->SQR1;
  /* 清除 L 位 */
  tmpreg1 &= SQR1_CLEAR_Mask;
  /* 配置 ADCx: 規則信道長度 */
  /* 設置 L 位，按照 ADC_NbrOfChannel 的值 */
  tmpreg2 |= (uint8_t) (ADC_InitStruct->ADC_NbrOfChannel - (uint8_t)1);
  tmpreg1 |= (uint32_t)tmpreg2 << 20;
  /* 寫 ADCx SQR1 */
  ADCx->SQR1 = tmpreg1;
}

/**
  * @簡述  把 ADC_InitStruct 中的每一個參數按缺省值填入.
  * @參數  ADC_InitStruct : 指向結構體 ADC_InitTypeDef 的指針，用來初始化.
  * @返回  沒有
  */
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)
{
  /* 復位 ADC 初始結構變量 */
  /* 初始化 ADC_Mode 成員 */
  ADC_InitStruct->ADC_Mode = ADC_Mode_Independent;
  /* 初始化 ADC_ScanConvMode 成員 */
  ADC_InitStruct->ADC_ScanConvMode = DISABLE;
  /* 初始化 ADC_ContinuousConvMode 成員 */
  ADC_InitStruct->ADC_ContinuousConvMode = DISABLE;
  /* 初始化 ADC_ExternalTrigConv 成員 */
  ADC_InitStruct->ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  /* 初始化 ADC_DataAlign 成員 */
  ADC_InitStruct->ADC_DataAlign = ADC_DataAlign_Right;
  /* 初始化 ADC_NbrOfChannel 成員 */
  ADC_InitStruct->ADC_NbrOfChannel = 1;
}

/**
  * @簡述  使能或者失能指定的 ADC .
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @參數  NewState: ADCx 設備的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 設置 ADON 位，從省電模式下喚醒ADC */
    ADCx->CR2 |= CR2_ADON_Set;
  }
  else
  {
    /* 失能指定的 ADC 設備 */
    ADCx->CR2 &= CR2_ADON_Reset;
  }
}

/**
  * @簡述  使能或失能指定的 ADC DMA 請求.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  *        註解: ADC2 沒有 DMA 能力.
  * @參數  NewState: 選定的 ADC DMA 轉移器的新狀態.
  *        這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_ADC_DMA_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 使能選定的 ADC DMA 請求 */
    ADCx->CR2 |= CR2_DMA_Set;
  }
  else
  {
    /* 失能選定的 ADC DMA 請求 */
    ADCx->CR2 &= CR2_DMA_Reset;
  }
}

/**
  * @簡述  使能或者失能指定的ADC的中斷.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @參數  ADC_IT: 指定的 ADC 中斷源. 
  *          可以使用下述值的一個或者幾個值的組合:
  *          ADC_IT_EOC:  換算結束中斷屏蔽
  *          ADC_IT_AWD:  模擬看門狗中斷屏蔽
  *          ADC_IT_JEOC: 注入通道完成中斷屏蔽
  * @參數  NewState: 指定的 ADC 中斷的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void ADC_ITConfig(ADC_TypeDef* ADCx, uint16_t ADC_IT, FunctionalState NewState)
{
  uint8_t itmask = 0;
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_ADC_IT(ADC_IT));
  /* 得到 ADC IT 中斷號 */
  itmask = (uint8_t)ADC_IT;
  if (NewState != DISABLE)
  {
    /* 使能選定的 ADC 中斷 */
    ADCx->CR1 |= itmask;
  }
  else
  {
    /* 失能指定的 ADC 中斷 */
    ADCx->CR1 &= (~(uint32_t)itmask);
  }
}

/**
  * @簡述  重置指定的ADC的校準寄存器.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @返回  沒有
  */
void ADC_ResetCalibration(ADC_TypeDef* ADCx)
{
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* 重置指定的ADC的校準寄存器 */  
  ADCx->CR2 |= CR2_RSTCAL_Set;
}

/**
  * @簡述  獲取ADC重置校準寄存器的狀態.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @返回  ADC重置校準寄存器的新狀態 (SET 或 RESET).
  */
FlagStatus ADC_GetResetCalibrationStatus(ADC_TypeDef* ADCx)
{
  FlagStatus bitstatus = RESET;
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* 檢查 RSTCAL 位的狀態 */
  if ((ADCx->CR2 & CR2_RSTCAL_Set) != (uint32_t)RESET)
  {
    /* 設置 RSTCAL 位 */
    bitstatus = SET;
  }
  else
  {
    /* 復位 RSTCAL 位 */
    bitstatus = RESET;
  }
  /* 返回 RSTCAL 位的狀態 */
  return  bitstatus;
}

/**
  * @簡述  開始指定ADC的校準狀態.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @返回  沒有
  */
void ADC_StartCalibration(ADC_TypeDef* ADCx)
{
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* 使能選定的 ADC 校準處理 */  
  ADCx->CR2 |= CR2_CAL_Set;
}

/**
  * @簡述  獲取指定ADC的校準狀態.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @返回  指定ADC的校準的新狀態 (SET 或 RESET).
  */
FlagStatus ADC_GetCalibrationStatus(ADC_TypeDef* ADCx)
{
  FlagStatus bitstatus = RESET;
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* 檢查 CAL 位的狀態 */
  if ((ADCx->CR2 & CR2_CAL_Set) != (uint32_t)RESET)
  {
    /* 設置 CAL 位: 較準進行中 */
    bitstatus = SET;
  }
  else
  {
    /* 復位 CAL 位: 校準結束 */
    bitstatus = RESET;
  }
  /* 返回 CAL 位的狀態 */
  return  bitstatus;
}

/**
  * @簡述  使能或者失能指定的ADC的軟件轉換啟動功能.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @參數  NewState: 選中的由軟件發出開始信號的ADC的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void ADC_SoftwareStartConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 允許選擇的ADC轉換外部事件和啟動選擇的ADC轉換 */
    ADCx->CR2 |= CR2_EXTTRIG_SWSTART_Set;
  }
  else
  {
    /* 禁止選擇的ADC轉換外部事件和停止選擇的ADC轉換 */
    ADCx->CR2 &= CR2_EXTTRIG_SWSTART_Reset;
  }
}

/**
  * @簡述  獲取ADC軟件轉換啟動狀態.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @返回  ADC軟件開始轉換的新狀態 (SET 或 RESET).
  */
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef* ADCx)
{
  FlagStatus bitstatus = RESET;
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* 檢查 SWSTART 位的新狀態 */
  if ((ADCx->CR2 & CR2_SWSTART_Set) != (uint32_t)RESET)
  {
    /* 設置 SWSTART 位 */
    bitstatus = SET;
  }
  else
  {
    /* 復位 SWSTART 位 */
    bitstatus = RESET;
  }
  /* 返回 SWSTART 位的狀態 */
  return  bitstatus;
}

/**
  * @簡述  對ADC規則組通道配置間斷模式.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @參數  Number: 模式下常規信道計數值，該值範圍為1－8. 
  * @返回  沒有
  */
void ADC_DiscModeChannelCountConfig(ADC_TypeDef* ADCx, uint8_t Number)
{
  uint32_t tmpreg1 = 0;
  uint32_t tmpreg2 = 0;
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_REGULAR_DISC_NUMBER(Number));
  /* 得到過去的寄存器值 */
  tmpreg1 = ADCx->CR1;
  /* 清除過去的不間斷模式通道計數器 */
  tmpreg1 &= CR1_DISCNUM_Reset;
  /* 設置間斷模式通道計數器 */
  tmpreg2 = Number - 1;
  tmpreg1 |= tmpreg2 << 13;
  /* 存儲寄存器的新值 */
  ADCx->CR1 = tmpreg1;
}

/**
  * @簡述  使能或者失能指定的ADC規則組通道的間斷模式.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @參數  NewState: 指定的ADC規則組通道的間斷模式的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void ADC_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 使能指定的ADC規則組通道的間斷模式 */
    ADCx->CR1 |= CR1_DISCEN_Set;
  }
  else
  {
    /* 失能指定的ADC規則組通道的間斷模式 */
    ADCx->CR1 &= CR1_DISCEN_Reset;
  }
}

/**
  * @簡述  設置指定ADC的規則組通道，設置它們的轉化順序和採樣時間.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @參數  ADC_Channel: 配置 ADC 通道. 
  *          這個參數可以使用下述值的一個:
  *          ADC_Channel_0:  選擇ADC通道0  
  *          ADC_Channel_1:  選擇ADC通道1  
  *          ADC_Channel_2:  選擇ADC通道2  
  *          ADC_Channel_3:  選擇ADC通道3  
  *          ADC_Channel_4:  選擇ADC通道4  
  *          ADC_Channel_5:  選擇ADC通道5  
  *          ADC_Channel_6:  選擇ADC通道6  
  *          ADC_Channel_7:  選擇ADC通道7  
  *          ADC_Channel_8:  選擇ADC通道8  
  *          ADC_Channel_9:  選擇ADC通道9  
  *          ADC_Channel_10: 選擇ADC通道10  
  *          ADC_Channel_11: 選擇ADC通道11  
  *          ADC_Channel_12: 選擇ADC通道12  
  *          ADC_Channel_13: 選擇ADC通道13  
  *          ADC_Channel_14: 選擇ADC通道14  
  *          ADC_Channel_15: 選擇ADC通道15  
  *          ADC_Channel_16: 選擇ADC通道16  
  *          ADC_Channel_17: 選擇ADC通道17  
  * @參數  Rank: 規則組採樣順序. 取值範圍1到16.
  * @參數  ADC_SampleTime: 指定ADC通道的採樣時間值. 
  *          這個參數可以使用下述值的一個:
  *          ADC_SampleTime_1Cycles5:   採樣時間等於 1.5   週期
  *          ADC_SampleTime_7Cycles5:   採樣時間等於 7.5   週期
  *          ADC_SampleTime_13Cycles5:  採樣時間等於 13.5  週期
  *          ADC_SampleTime_28Cycles5:  採樣時間等於 28.5  週期	
  *          ADC_SampleTime_41Cycles5:  採樣時間等於 41.5  週期	
  *          ADC_SampleTime_55Cycles5:  採樣時間等於 55.5  週期	
  *          ADC_SampleTime_71Cycles5:  採樣時間等於 71.5  週期	
  *          ADC_SampleTime_239Cycles5: 採樣時間等於 239.5 週期	
  * @返回  沒有
  */
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
{
  uint32_t tmpreg1 = 0, tmpreg2 = 0;
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  assert_param(IS_ADC_REGULAR_RANK(Rank));
  assert_param(IS_ADC_SAMPLE_TIME(ADC_SampleTime));
  /* 如果選定 ADC_Channel_10 ... ADC_Channel_17 */
  if (ADC_Channel > ADC_Channel_9)
  {
    /* 得到舊的寄存器的值 */
    tmpreg1 = ADCx->SMPR1;
    /* 計算需要清除的標誌 */
    tmpreg2 = SMPR1_SMP_Set << (3 * (ADC_Channel - 10));
    /* 清除舊的通道採樣時間 */
    tmpreg1 &= ~tmpreg2;
    /* 計算需要置位的標誌 */
    tmpreg2 = (uint32_t)ADC_SampleTime << (3 * (ADC_Channel - 10));
    /* 設置新的通道採樣時間 */
    tmpreg1 |= tmpreg2;
    /* 存儲新的寄存器的值 */
    ADCx->SMPR1 = tmpreg1;
  }
  else /* ADC_Channel include in ADC_Channel_[0..9] */
  {
    /* 得到舊的寄存器的值 */
    tmpreg1 = ADCx->SMPR2;
    /* 計算需要清除的標誌 */
    tmpreg2 = SMPR2_SMP_Set << (3 * ADC_Channel);
    /* 清除舊的通道採樣時間 */
    tmpreg1 &= ~tmpreg2;
    /* 計算需要置位的標誌 */
    tmpreg2 = (uint32_t)ADC_SampleTime << (3 * ADC_Channel);
    /* 設置新的通道採樣時間 */
    tmpreg1 |= tmpreg2;
    /* 存儲新的寄存器的值 */
    ADCx->SMPR2 = tmpreg1;
  }
  /* For Rank 1 to 6 */
  if (Rank < 7)
  {
    /* 得到舊的寄存器的值 */
    tmpreg1 = ADCx->SQR3;
    /* 計算需要清除的標誌 */
    tmpreg2 = SQR3_SQ_Set << (5 * (Rank - 1));
    /* 根據選擇的序列清除舊的 SQx 位 */
    tmpreg1 &= ~tmpreg2;
    /* 計算需要置位的標誌 */
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 1));
    /* 根據選擇的序列設置新的 SQx 位 */
    tmpreg1 |= tmpreg2;
    /* 存儲新的寄存器的值 */
    ADCx->SQR3 = tmpreg1;
  }
  /* For Rank 7 to 12 */
  else if (Rank < 13)
  {
    /* 得到舊的寄存器的值 */
    tmpreg1 = ADCx->SQR2;
    /* 計算需要清除的標誌 */
    tmpreg2 = SQR2_SQ_Set << (5 * (Rank - 7));
    /* 根據選擇的序列清除舊的 SQx 位 */
    tmpreg1 &= ~tmpreg2;
    /* 計算需要置位的標誌 */
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 7));
    /* 根據選擇的序列設置新的 SQx 位 */
    tmpreg1 |= tmpreg2;
    /* 存儲新的寄存器的值 */
    ADCx->SQR2 = tmpreg1;
  }
  /* For Rank 13 to 16 */
  else
  {
    /* 得到舊的寄存器的值 */
    tmpreg1 = ADCx->SQR1;
    /* 計算需要清除的標誌 */
    tmpreg2 = SQR1_SQ_Set << (5 * (Rank - 13));
    /* 根據選擇的序列清除舊的 SQx 位 */
    tmpreg1 &= ~tmpreg2;
    /* 計算需要置位的標誌 */
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 13));
    /* 根據選擇的序列設置新的 SQx 位 */
    tmpreg1 |= tmpreg2;
    /* 存儲新的寄存器的值 */
    ADCx->SQR1 = tmpreg1;
  }
}

/**
  * @簡述  使能或者失能 ADCx 的經外部觸發啟動轉換功能.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @參數  NewState: 選定的 ADCx 的經外部觸發啟動轉換功能的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void ADC_ExternalTrigConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 使能 ADCx 的經外部觸發啟動轉換功能 */
    ADCx->CR2 |= CR2_EXTTRIG_Set;
  }
  else
  {
    /* 失能 ADCx 的經外部觸發啟動轉換功能 */
    ADCx->CR2 &= CR2_EXTTRIG_Reset;
  }
}

/**
  * @簡述  返回最近一次 ADCx 規則組的轉換結果.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @返回  轉換結果.
  */
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx)
{
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* 返回最近一次 ADCx 規則組的轉換結果 */
  return (uint16_t) ADCx->DR;
}

/**
  * @簡述  返回最近一次雙 ADC 模式下的 ADC1 和 ADC2 轉換結果.
  * @retval 轉換結果.
  */
uint32_t ADC_GetDualModeConversionValue(void)
{
  /* 返回雙轉換下的轉換結果 */
  return (*(__IO uint32_t *) DR_ADDRESS);
}

/**
  * @簡述  使能或者失能指定 ADC 在規則組轉化後自動開始注入組轉換.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @參數  NewState: 選中的進行自動注入轉換的ADC新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void ADC_AutoInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 使能指定 ADC 在規則組轉化後自動開始注入組轉換 */
    ADCx->CR1 |= CR1_JAUTO_Set;
  }
  else
  {
    /* 失能指定 ADC 在規則組轉化後自動開始注入組轉換 */
    ADCx->CR1 &= CR1_JAUTO_Reset;
  }
}

/**
  * @簡述  使能或者失能指定 ADC 的注入組間斷模式
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @參數  NewState: ADC 注入組通道上間斷模式的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void ADC_InjectedDiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 失能指定 ADC 的注入組間斷模式 */
    ADCx->CR1 |= CR1_JDISCEN_Set;
  }
  else
  {
    /* 失能指定 ADC 的注入組間斷模式 */
    ADCx->CR1 &= CR1_JDISCEN_Reset;
  }
}

/**
  * @簡述  配置 ADCx 的外部觸發啟動注入組轉換功能.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @參數  ADC_ExternalTrigInjecConv: 開始注入轉換的ADC觸發器. 
  *          這個參數可以取下列值之一:
  *          ADC_ExternalTrigInjecConv_T1_TRGO: 選擇定時器1的TRGO作為注入轉換外部觸發 (for ADC1, ADC2 and ADC3)
  *          ADC_ExternalTrigInjecConv_T1_CC4:  選擇定時器1的捕獲比較4作為注入轉換外部觸發 (for ADC1, ADC2 and ADC3)
  *          ADC_ExternalTrigInjecConv_T2_TRGO: 選擇定時器2的 TRGO 作為注入轉換外部觸發 (for ADC1 and ADC2)
  *          ADC_ExternalTrigInjecConv_T2_CC1:  選擇定時器2的捕獲比較1作為注入轉換外部觸發 (for ADC1 and ADC2)
  *          ADC_ExternalTrigInjecConv_T3_CC4:  選擇定時器3的捕獲比較4作為注入轉換外部觸發 (for ADC1 and ADC2)
  *          ADC_ExternalTrigInjecConv_T4_TRGO: 選擇定時器4的TRGO作為注入轉換外部觸發 (for ADC1 and ADC2)
  *          ADC_ExternalTrigInjecConv_Ext_IT15_TIM8_CC4: 外部中斷15或者timer8比較事件作為注入轉換的外部觸發器 (for ADC1 and ADC2)                       
  *          ADC_ExternalTrigInjecConv_T4_CC3:  選擇定時器4捕獲比較3 (for ADC3 only)
  *          ADC_ExternalTrigInjecConv_T8_CC2:  選擇定時器8捕獲比較2 (for ADC3 only)                         
  *          ADC_ExternalTrigInjecConv_T8_CC4:  選擇定時器8捕獲比較4 (for ADC3 only)
  *          ADC_ExternalTrigInjecConv_T5_TRGO: 選擇定時器5觸發事件 (for ADC3 only)                         
  *          ADC_ExternalTrigInjecConv_T5_CC4:  選擇定時器5捕獲比較4 (for ADC3 only)                        
  *          ADC_ExternalTrigInjecConv_None:    注入轉換由軟件啟動，而不是由外部觸發器啟動 (for ADC1, ADC2 and ADC3)
  * @返回  沒有
  */
void ADC_ExternalTrigInjectedConvConfig(ADC_TypeDef* ADCx, uint32_t ADC_ExternalTrigInjecConv)
{
  uint32_t tmpreg = 0;
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_EXT_INJEC_TRIG(ADC_ExternalTrigInjecConv));
  /* 得到舊的寄存器的值 */
  tmpreg = ADCx->CR2;
  /* 清除選擇的注入通道群的外部觸發事件 */
  tmpreg &= CR2_JEXTSEL_Reset;
  /* 設置選擇的注入通道群的外部觸發事件 */
  tmpreg |= ADC_ExternalTrigInjecConv;
  /* 存儲新的寄存器的值 */
  ADCx->CR2 = tmpreg;
}

/**
  * @簡述  使能或者失能 ADCx 的經外部觸發啟動注入組轉換功能.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @參數  NewState: 指定ADC外部觸發啟動注入轉換的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void ADC_ExternalTrigInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 使能 ADCx 的經外部觸發啟動注入組轉換功能 */
    ADCx->CR2 |= CR2_JEXTTRIG_Set;
  }
  else
  {
    /* 失能 ADCx 的經外部觸發啟動注入組轉換功能 */
    ADCx->CR2 &= CR2_JEXTTRIG_Reset;
  }
}

/**
  * @簡述  使能或者失能 ADCx 軟件啟動注入組轉換功能.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @參數  NewState: 指定 ADC 軟件觸發啟動注入轉換的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void ADC_SoftwareStartInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 使能 ADCx 軟件啟動注入組轉換功能並且啟動注入選擇 */
    ADCx->CR2 |= CR2_JEXTTRIG_JSWSTART_Set;
  }
  else
  {
    /* 失能 ADCx 軟件啟動注入組轉換功能並且啟動注入選擇 */
    ADCx->CR2 &= CR2_JEXTTRIG_JSWSTART_Reset;
  }
}

/**
  * @簡述  獲取指定 ADC 的軟件啟動注入組轉換狀態.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @返回  指定的 ADC 軟件觸發啟動注入轉換的新狀態 (SET 或 RESET).
  */
FlagStatus ADC_GetSoftwareStartInjectedConvCmdStatus(ADC_TypeDef* ADCx)
{
  FlagStatus bitstatus = RESET;
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* 檢查 JSWSTART 位的狀態 */
  if ((ADCx->CR2 & CR2_JSWSTART_Set) != (uint32_t)RESET)
  {
    /* 設置 JSWSTART 位 */
    bitstatus = SET;
  }
  else
  {
    /* 復位 JSWSTART 位 */
    bitstatus = RESET;
  }
  /* 返回 JSWSTART 位的狀態 */
  return  bitstatus;
}

/**
  * @簡述  設置指定 ADC 的注入組通道，設置它們的轉化順序和採樣時間.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @參數  ADC_Channel: 被設置的ADC通道. 
  *          這個參數可以取下列值之一:
  *          ADC_Channel_0:  選擇ADC通道0  
  *          ADC_Channel_1:  選擇ADC通道1  
  *          ADC_Channel_2:  選擇ADC通道2  
  *          ADC_Channel_3:  選擇ADC通道3  
  *          ADC_Channel_4:  選擇ADC通道4  
  *          ADC_Channel_5:  選擇ADC通道5  
  *          ADC_Channel_6:  選擇ADC通道6  
  *          ADC_Channel_7:  選擇ADC通道7  
  *          ADC_Channel_8:  選擇ADC通道8  
  *          ADC_Channel_9:  選擇ADC通道9  
  *          ADC_Channel_10: 選擇ADC通道10  
  *          ADC_Channel_11: 選擇ADC通道11  
  *          ADC_Channel_12: 選擇ADC通道12  
  *          ADC_Channel_13: 選擇ADC通道13  
  *          ADC_Channel_14: 選擇ADC通道14  
  *          ADC_Channel_15: 選擇ADC通道15  
  *          ADC_Channel_16: 選擇ADC通道16  
  *          ADC_Channel_17: 選擇ADC通道17 
  * @參數  Rank: 規則組採樣順序.取值範圍1到4.
  * @參數  ADC_SampleTime: 指定ADC通道的採樣時間值. 
  *          這個參數可以使用下述值的一個:
  *          ADC_SampleTime_1Cycles5:   採樣時間等於 1.5   週期
  *          ADC_SampleTime_7Cycles5:   採樣時間等於 7.5   週期
  *          ADC_SampleTime_13Cycles5:  採樣時間等於 13.5  週期
  *          ADC_SampleTime_28Cycles5:  採樣時間等於 28.5  週期	
  *          ADC_SampleTime_41Cycles5:  採樣時間等於 41.5  週期	
  *          ADC_SampleTime_55Cycles5:  採樣時間等於 55.5  週期	
  *          ADC_SampleTime_71Cycles5:  採樣時間等於 71.5  週期	
  *          ADC_SampleTime_239Cycles5: 採樣時間等於 239.5 週期		
  * @返回  沒有
  */
void ADC_InjectedChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
{
  uint32_t tmpreg1 = 0, tmpreg2 = 0, tmpreg3 = 0;
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  assert_param(IS_ADC_INJECTED_RANK(Rank));
  assert_param(IS_ADC_SAMPLE_TIME(ADC_SampleTime));
  /* 如果選擇 ADC_Channel_10 ... ADC_Channel_17 */
  if (ADC_Channel > ADC_Channel_9)
  {
    /* 得到舊的寄存器的值 */
    tmpreg1 = ADCx->SMPR1;
    /* 計算需要清除的標誌 */
    tmpreg2 = SMPR1_SMP_Set << (3*(ADC_Channel - 10));
    /* 清除舊的通道採樣時間 */
    tmpreg1 &= ~tmpreg2;
    /* 計算需要置位的標誌 */
    tmpreg2 = (uint32_t)ADC_SampleTime << (3*(ADC_Channel - 10));
    /* 設置新的通道採樣時間 */
    tmpreg1 |= tmpreg2;
    /* 存儲新的寄存器的值 */
    ADCx->SMPR1 = tmpreg1;
  }
  else /* ADC_Channel include in ADC_Channel_[0..9] */
  {
    /* 得到舊的寄存器的值 */
    tmpreg1 = ADCx->SMPR2;
    /* 計算需要清除的標誌 */
    tmpreg2 = SMPR2_SMP_Set << (3 * ADC_Channel);
    /* 清除舊的通道採樣時間 */
    tmpreg1 &= ~tmpreg2;
    /* 計算需要置位的標誌 */
    tmpreg2 = (uint32_t)ADC_SampleTime << (3 * ADC_Channel);
    /* 設置新的通道採樣時間 */
    tmpreg1 |= tmpreg2;
    /* 存儲新的寄存器的值 */
    ADCx->SMPR2 = tmpreg1;
  }
  /* 配置 Rank 規則組採樣順序 */
  /* 得到舊的寄存器的值 */
  tmpreg1 = ADCx->JSQR;
  /* 得到 JL 的值: Number = JL+1 */
  tmpreg3 =  (tmpreg1 & JSQR_JL_Set)>> 20;
  /* 計算需要清除的標誌: ((Rank-1)+(4-JL-1)) */
  tmpreg2 = JSQR_JSQ_Set << (5 * (uint8_t)((Rank + 3) - (tmpreg3 + 1)));
  /* 清除選中序列 JSQx 位 */
  tmpreg1 &= ~tmpreg2;
  /* 計算需要置位的標誌: ((Rank-1)+(4-JL-1)) */
  tmpreg2 = (uint32_t)ADC_Channel << (5 * (uint8_t)((Rank + 3) - (tmpreg3 + 1)));
  /* 置位選中序列舊的 JSQx 位 */
  tmpreg1 |= tmpreg2;
  /* 存儲新的寄存器的值 */
  ADCx->JSQR = tmpreg1;
}

/**
  * @簡述  設置注入組通道的轉換序列長度
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @參數  Length: 轉換序列長度. 
  *                這個參數必須是 1 到 4 之間的值.
  * @返回  沒有
  */
void ADC_InjectedSequencerLengthConfig(ADC_TypeDef* ADCx, uint8_t Length)
{
  uint32_t tmpreg1 = 0;
  uint32_t tmpreg2 = 0;
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_INJECTED_LENGTH(Length));
  
  /* 得到舊的寄存器的值 */
  tmpreg1 = ADCx->JSQR;
  /* 清除注入信道音序器的長度 JL 位 */
  tmpreg1 &= JSQR_JL_Reset;
  /* 置位注入信道音序器的長度 JL 位 */
  tmpreg2 = Length - 1; 
  tmpreg1 |= tmpreg2 << 20;
  /* 存儲新的寄存器的值 */
  ADCx->JSQR = tmpreg1;
}

/**
  * @簡述  設置注入組通道的轉換偏移值
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @參數  ADC_InjectedChannel: 需要設置偏移值的ADC注入信道. 
  *          這個參數可以使用下述值的一個:
  *          ADC_InjectedChannel_1: 選擇注入通道1 
  *          ADC_InjectedChannel_2: 選擇注入通道2 
  *          ADC_InjectedChannel_3: 選擇注入通道3 
  *          ADC_InjectedChannel_4: 選擇注入通道4 
  * @參數  Offset: 選中的ADC注入信道的偏移值，該參數是一個12位值.
  * @返回  沒有
  */
void ADC_SetInjectedOffset(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel, uint16_t Offset)
{
  __IO uint32_t tmp = 0;
  
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_INJECTED_CHANNEL(ADC_InjectedChannel));
  assert_param(IS_ADC_OFFSET(Offset));  
  
  tmp = (uint32_t)ADCx;
  tmp += ADC_InjectedChannel;
  
  /* 設置選定的注入通道的數據偏移量 */
  *(__IO uint32_t *) tmp = (uint32_t)Offset;
}

/**
  * @簡述  返回 ADC 指定注入通道的轉換結果
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @參數  ADC_InjectedChannel: 指定注入通道.
  *          這個參數可以使用下述值的一個:
  *          ADC_InjectedChannel_1: 選定注入通道1 
  *          ADC_InjectedChannel_2: 選定注入通道2
  *          ADC_InjectedChannel_3: 選定注入通道3
  *          ADC_InjectedChannel_4: 選定注入通道4
  * @返回  轉換結果.
  */
uint16_t ADC_GetInjectedConversionValue(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel)
{
  __IO uint32_t tmp = 0;
  
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_INJECTED_CHANNEL(ADC_InjectedChannel));

  tmp = (uint32_t)ADCx;
  tmp += ADC_InjectedChannel + JDR_Offset;
  
  /* 返回 ADC 指定注入通道的轉換結果 */
  return (uint16_t) (*(__IO uint32_t*)  tmp);   
}

/**
  * @簡述  使能或者失能指定單個/全體，規則/注入組通道上的模擬看門狗
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @參數  ADC_AnalogWatchdog: ADC模擬看門狗配置.
  *          這個參數可以使用下述值的一個:
  *          ADC_AnalogWatchdog_SingleRegEnable:        單個規則通道上設置模擬看門狗
  *          ADC_AnalogWatchdog_SingleInjecEnable:      單個注入通道上設置模擬看門狗
  *          ADC_AnalogWatchdog_SingleRegOrInjecEnable: 單個規則通道或者注入通道上設置模擬看門狗
  *          ADC_AnalogWatchdog_AllRegEnable:           所有規則通道上設置模擬看門狗
  *          ADC_AnalogWatchdog_AllInjecEnable:         所有注入通道上設置模擬看門狗
  *          ADC_AnalogWatchdog_AllRegAllInjecEnable:   所有規則通道和所有注入通道上上設置模擬看門狗
  *          ADC_AnalogWatchdog_None:                   不設置模擬看門狗
  * @返回  沒有	  
  */
void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, uint32_t ADC_AnalogWatchdog)
{
  uint32_t tmpreg = 0;
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_ANALOG_WATCHDOG(ADC_AnalogWatchdog));
  /* 得到舊的寄存器的值 */
  tmpreg = ADCx->CR1;
  /* 清除 AWDEN, AWDENJ 和 AWDSGL 位 */
  tmpreg &= CR1_AWDMode_Reset;
  /* 設置模擬看門狗允許模式 */
  tmpreg |= ADC_AnalogWatchdog;
  /* 存儲新的寄存器的值 */
  ADCx->CR1 = tmpreg;
}

/**
  * @簡述  設置模擬看門狗的高/低閾值.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @參數  HighThreshold: 模擬看門狗的高閾值.
  *                       這個參數是一個12位的值.
  * @參數  LowThreshold:  模擬看門狗的低閾值.
  *                       這個參數是一個12位的值.
  * @返回  沒有
  */
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* ADCx, uint16_t HighThreshold,
                                        uint16_t LowThreshold)
{
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_THRESHOLD(HighThreshold));
  assert_param(IS_ADC_THRESHOLD(LowThreshold));
  /* 設置模擬看門狗的高閾值 */
  ADCx->HTR = HighThreshold;
  /* 設置模擬看門狗的低閾值 */
  ADCx->LTR = LowThreshold;
}

/**
  * @簡述  對單個ADC通道設置模擬看門狗
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @參數  ADC_Channel: 將要為其配置模擬看門狗的信道. 
  *          這個參數可以使用下述值的一個:
  *          ADC_Channel_0:  選擇ADC通道0  
  *          ADC_Channel_1:  選擇ADC通道1  
  *          ADC_Channel_2:  選擇ADC通道2  
  *          ADC_Channel_3:  選擇ADC通道3  
  *          ADC_Channel_4:  選擇ADC通道4  
  *          ADC_Channel_5:  選擇ADC通道5  
  *          ADC_Channel_6:  選擇ADC通道6  
  *          ADC_Channel_7:  選擇ADC通道7  
  *          ADC_Channel_8:  選擇ADC通道8  
  *          ADC_Channel_9:  選擇ADC通道9  
  *          ADC_Channel_10: 選擇ADC通道10  
  *          ADC_Channel_11: 選擇ADC通道11  
  *          ADC_Channel_12: 選擇ADC通道12  
  *          ADC_Channel_13: 選擇ADC通道13  
  *          ADC_Channel_14: 選擇ADC通道14  
  *          ADC_Channel_15: 選擇ADC通道15  
  *          ADC_Channel_16: 選擇ADC通道16  
  *          ADC_Channel_17: 選擇ADC通道17 
  * @返回  沒有
  */
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel)
{
  uint32_t tmpreg = 0;
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  /* 得到舊的寄存器的值 */
  tmpreg = ADCx->CR1;
  /* 清除模擬看門狗通道選擇位 */
  tmpreg &= CR1_AWDCH_Reset;
  /* 設置模擬看門狗通道選擇位 */
  tmpreg |= ADC_Channel;
  /* 存儲寄存器的新值 */
  ADCx->CR1 = tmpreg;
}

/**
  * @簡述  使能或者失能溫度傳感器和內部參考電壓通道.
  * @參數  NewState: 溫度傳感器和內部參考電壓通道的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void ADC_TempSensorVrefintCmd(FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 使能溫度傳感器和內部參考電壓通道 */
    ADC1->CR2 |= CR2_TSVREFE_Set;
  }
  else
  {
    /* 失能溫度傳感器和內部參考電壓通道 */
    ADC1->CR2 &= CR2_TSVREFE_Reset;
  }
}

/**
  * @簡述  檢查制定 ADC 標誌位置1與否.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @參數  ADC_FLAG: 指定需要檢查的標誌. 
  *          這個參數可以使用下述值的一個:
  *          ADC_FLAG_AWD:   模擬看門狗標誌位
  *          ADC_FLAG_EOC:   轉換結束標誌位
  *          ADC_FLAG_JEOC:  注入組轉換結束標誌位
  *          ADC_FLAG_JSTRT: 注入組轉換開始標誌位
  *          ADC_FLAG_STRT:  規則組轉換開始標誌位
  * @返回  ADC_FLAG 的新狀態 (SET 或 RESET).
  */
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint8_t ADC_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_GET_FLAG(ADC_FLAG));
  /* 檢查指定ADC狀態位 */
  if ((ADCx->SR & ADC_FLAG) != (uint8_t)RESET)
  {
    /* 設置 ADC_FLAG 位 */
    bitstatus = SET;
  }
  else
  {
    /* 復位 ADC_FLAG 位 */
    bitstatus = RESET;
  }
  /* 返回 ADC_FLAG 的狀態 */
  return  bitstatus;
}

/**
  * @簡述  清除 ADCx 的待處理標誌位.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @參數  ADC_FLAG: 待處理的標誌位. 
  *          這個參數可以是下列值的組合:
  *          ADC_FLAG_AWD:   模擬看門狗標誌位
  *          ADC_FLAG_EOC:   轉換結束標誌位
  *          ADC_FLAG_JEOC:  注入組轉換結束標誌位
  *          ADC_FLAG_JSTRT: 注入組轉換開始標誌位
  *          ADC_FLAG_STRT:  規則組轉換開始標誌位
  * @返回  沒有
  */
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint8_t ADC_FLAG)
{
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CLEAR_FLAG(ADC_FLAG));
  /* 清除指定的 ADC 標誌 */
  ADCx->SR = ~(uint32_t)ADC_FLAG;
}

/**
  * @簡述  檢查指定的ADC中斷是否發生.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @參數  ADC_IT: 需要檢查的ADC中斷源. 
  *          這個參數可以使用下述值的一個:
  *          ADC_IT_EOC:  轉換結束中斷屏蔽
  *          ADC_IT_AWD:  模擬看門狗中斷屏蔽
  *          ADC_IT_JEOC: 注入組轉換結束中斷屏蔽
  * @返回  ADC_IT 的新狀態 (SET 或 RESET).
  */
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint16_t ADC_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t itmask = 0, enablestatus = 0;
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_GET_IT(ADC_IT));
  /* 得到 ADC IT 中斷號 */
  itmask = ADC_IT >> 8;
  /* 設置 ADC_IT 允許位狀態 */
  enablestatus = (ADCx->CR1 & (uint8_t)ADC_IT) ;
  /* 檢查指定的 ADC 中斷 */
  if (((ADCx->SR & itmask) != (uint32_t)RESET) && enablestatus)
  {
    /* 設置 ADC_IT */
    bitstatus = SET;
  }
  else
  {
    /* 復位 ADC_IT */
    bitstatus = RESET;
  }
  /* 返回 ADC_IT 的狀態 */
  return  bitstatus;
}

/**
  * @簡述  清除 ADCx 的中斷待處理位.
  * @參數  ADCx: 其中x可以是1、2或3，用來選擇ADC外圍模塊.
  * @參數  ADC_IT: 帶清除的 ADC 中斷待處理位.
  *          可以使用下述值的一個或者幾個值的組合:
  *          ADC_IT_EOC:  轉換結束中斷
  *          ADC_IT_AWD:  模擬看門狗中斷
  *          ADC_IT_JEOC: 注入組轉換結束中斷
  * @返回  沒有
  */
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint16_t ADC_IT)
{
  uint8_t itmask = 0;
  /* 檢查參數 */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_IT(ADC_IT));
  /* 得到 ADC IT 中斷號 */
  itmask = (uint8_t)(ADC_IT >> 8);
  /* 清除選擇的ADC中斷掛起位 */
  ADCx->SR = ~(uint32_t)itmask;
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
