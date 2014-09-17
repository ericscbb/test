/**
  ******************************************************************************
  * @文件    stm32f10x_tim.c
  * @作者    MCD 應用程序組
  * @版本    V3.1.0
  * @日期    06/19/2009
  * @簡述    這個文件 提供所有 TIM 固件函數.
  * @翻譯    ANSON/sweet1985 Email:airanson110@126.com
  * @日期    10/07/2009
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
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"

/* 自用類型 --------------------------------------------------------------*/
/* 自用定義 --------------------------------------------------------------*/

/* ---------------------- TIM registers bit mask ------------------------ */
#define CR1_CEN_Set                 ((uint16_t)0x0001)
#define CR1_CEN_Reset               ((uint16_t)0x03FE)
#define CR1_UDIS_Set                ((uint16_t)0x0002)
#define CR1_UDIS_Reset              ((uint16_t)0x03FD)
#define CR1_URS_Set                 ((uint16_t)0x0004)
#define CR1_URS_Reset               ((uint16_t)0x03FB)
#define CR1_OPM_Reset               ((uint16_t)0x03F7)
#define CR1_CounterMode_Mask        ((uint16_t)0x038F)
#define CR1_ARPE_Set                ((uint16_t)0x0080)
#define CR1_ARPE_Reset              ((uint16_t)0x037F)
#define CR1_CKD_Mask                ((uint16_t)0x00FF)
#define CR2_CCPC_Set                ((uint16_t)0x0001)
#define CR2_CCPC_Reset              ((uint16_t)0xFFFE)
#define CR2_CCUS_Set                ((uint16_t)0x0004)
#define CR2_CCUS_Reset              ((uint16_t)0xFFFB)
#define CR2_CCDS_Set                ((uint16_t)0x0008)
#define CR2_CCDS_Reset              ((uint16_t)0xFFF7)
#define CR2_MMS_Mask                ((uint16_t)0xFF8F)
#define CR2_TI1S_Set                ((uint16_t)0x0080)
#define CR2_TI1S_Reset              ((uint16_t)0xFF7F)
#define CR2_OIS1_Reset              ((uint16_t)0x7EFF)
#define CR2_OIS1N_Reset             ((uint16_t)0x7DFF)
#define CR2_OIS2_Reset              ((uint16_t)0x7BFF)
#define CR2_OIS2N_Reset             ((uint16_t)0x77FF)
#define CR2_OIS3_Reset              ((uint16_t)0x6FFF)
#define CR2_OIS3N_Reset             ((uint16_t)0x5FFF)
#define CR2_OIS4_Reset              ((uint16_t)0x3FFF)
#define SMCR_SMS_Mask               ((uint16_t)0xFFF8)
#define SMCR_ETR_Mask               ((uint16_t)0x00FF)
#define SMCR_TS_Mask                ((uint16_t)0xFF8F)
#define SMCR_MSM_Reset              ((uint16_t)0xFF7F)
#define SMCR_ECE_Set                ((uint16_t)0x4000)
#define CCMR_CC13S_Mask             ((uint16_t)0xFFFC)
#define CCMR_CC24S_Mask             ((uint16_t)0xFCFF)
#define CCMR_TI13Direct_Set         ((uint16_t)0x0001)
#define CCMR_TI24Direct_Set         ((uint16_t)0x0100)
#define CCMR_OC13FE_Reset           ((uint16_t)0xFFFB)
#define CCMR_OC24FE_Reset           ((uint16_t)0xFBFF)
#define CCMR_OC13PE_Reset           ((uint16_t)0xFFF7)
#define CCMR_OC24PE_Reset           ((uint16_t)0xF7FF)
#define CCMR_OC13M_Mask             ((uint16_t)0xFF8F)
#define CCMR_OC24M_Mask             ((uint16_t)0x8FFF) 
#define CCMR_OC13CE_Reset           ((uint16_t)0xFF7F)
#define CCMR_OC24CE_Reset           ((uint16_t)0x7FFF)
#define CCMR_IC13PSC_Mask           ((uint16_t)0xFFF3)
#define CCMR_IC24PSC_Mask           ((uint16_t)0xF3FF)
#define CCMR_IC13F_Mask             ((uint16_t)0xFF0F)
#define CCMR_IC24F_Mask             ((uint16_t)0x0FFF)
#define CCMR_Offset                 ((uint16_t)0x0018)
#define CCER_CCE_Set                ((uint16_t)0x0001)
#define	CCER_CCNE_Set               ((uint16_t)0x0004)
#define CCER_CC1P_Reset             ((uint16_t)0xFFFD)
#define CCER_CC2P_Reset             ((uint16_t)0xFFDF)
#define CCER_CC3P_Reset             ((uint16_t)0xFDFF)
#define CCER_CC4P_Reset             ((uint16_t)0xDFFF)
#define CCER_CC1NP_Reset            ((uint16_t)0xFFF7)
#define CCER_CC2NP_Reset            ((uint16_t)0xFF7F)
#define CCER_CC3NP_Reset            ((uint16_t)0xF7FF)
#define CCER_CC1E_Set               ((uint16_t)0x0001)
#define CCER_CC1E_Reset             ((uint16_t)0xFFFE)
#define CCER_CC1NE_Reset            ((uint16_t)0xFFFB)
#define CCER_CC2E_Set               ((uint16_t)0x0010)
#define CCER_CC2E_Reset             ((uint16_t)0xFFEF)
#define CCER_CC2NE_Reset            ((uint16_t)0xFFBF)
#define CCER_CC3E_Set               ((uint16_t)0x0100)
#define CCER_CC3E_Reset             ((uint16_t)0xFEFF)
#define CCER_CC3NE_Reset            ((uint16_t)0xFBFF)
#define CCER_CC4E_Set               ((uint16_t)0x1000)
#define CCER_CC4E_Reset             ((uint16_t)0xEFFF)
#define BDTR_MOE_Set                ((uint16_t)0x8000)
#define BDTR_MOE_Reset              ((uint16_t)0x7FFF)

/* 自用宏 -------------------------------------------------------------*/
/* 自用變量 -----------------------------------------------------------*/
/* 自用函數原型 -------------------------------------------------------*/

static void TI1_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter);
static void TI2_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter);
static void TI3_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter);
static void TI4_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter);

/* 自用函數 -----------------------------------------------------------*/

/**
  * @簡述  將外設 TIMx 寄存器重設為缺省值.
  * @參數  TIMx: 此處x可以是1到8以選擇外設.
  * @返回  沒有
  */
void TIM_DeInit(TIM_TypeDef* TIMx)
{
  /* 檢查參數 */
  assert_param(IS_TIM_ALL_PERIPH(TIMx)); 
 
  if (TIMx == TIM1)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, DISABLE);  
  }     
  else if (TIMx == TIM2)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2, DISABLE);
  }
  else if (TIMx == TIM3)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM3, DISABLE);
  }
  else if (TIMx == TIM4)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4, DISABLE);
  } 
  else if (TIMx == TIM5)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM5, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM5, DISABLE);
  } 
  else if (TIMx == TIM6)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, DISABLE);
  } 
  else if (TIMx == TIM7)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM7, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM7, DISABLE);
  } 
  else
  {
    if (TIMx == TIM8)
    {
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM8, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM8, DISABLE);
    }  
  }
}

/**
  * @簡述  根據 TIM_TimeBaseInitStruct 中指定的參數初始化 TIMx 的時間基數單位.
  * @參數  TIMx: 這裡 x 可以是 1, 2, 3, 4, 5 或 8 設定 TIM 外設.
  * @參數  TIM_TimeBaseInitStruct: 指向一個包含 TIM 時間基配置信息的 TIM_BaseInitTypeDef 結構的指針.
  * @返回  沒有
  */
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct)
{
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx)); 
  assert_param(IS_TIM_COUNTER_MODE(TIM_TimeBaseInitStruct->TIM_CounterMode));
  assert_param(IS_TIM_CKD_DIV(TIM_TimeBaseInitStruct->TIM_ClockDivision));
  /* 選擇計數器模式 ，設置時鐘頻率 */
  TIMx->CR1 &= CR1_CKD_Mask & CR1_CounterMode_Mask;
  TIMx->CR1 |= (uint32_t)TIM_TimeBaseInitStruct->TIM_ClockDivision |
                TIM_TimeBaseInitStruct->TIM_CounterMode;
  
  /* 設置自動裝載值 */
  TIMx->ARR = TIM_TimeBaseInitStruct->TIM_Period ;
 
  /* 設置預分頻器值 */
  TIMx->PSC = TIM_TimeBaseInitStruct->TIM_Prescaler;
    
  if ((((uint32_t) TIMx) == TIM1_BASE) || (((uint32_t) TIMx) == TIM8_BASE))  
  {
    /* 設置重複計數器值 */
    TIMx->RCR = TIM_TimeBaseInitStruct->TIM_RepetitionCounter;
  }

  /* 產生一個更新事件立即重新裝載預分頻器值 */
  TIMx->EGR = TIM_PSCReloadMode_Immediate;          
}

/**
  * @簡述  根據 TIM_OCInitStruct 中的特定參數初始化TIMx通道1.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_OCInitStruct: 指向一個包含特定TIMx外設的配置信息的 TIM_OCInitTypeDef 結構的指針.
  * @返回  沒有
  */
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
   
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx)); 
  assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
  assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));   
  /* 失能通道 1: 復位 CC1E 位 */
  TIMx->CCER &= CCER_CC1E_Reset;
  
  /* 得到 TIMx CCER(捕獲/比較使能) 寄存器的值 */
  tmpccer = TIMx->CCER;
  /* 得到 TIMx CR2(控制寄存器2) 寄存器的值 */
  tmpcr2 =  TIMx->CR2;
  
  /* 得到 TIMx CCMR1(捕獲/比較模式) 寄存器的值 */
  tmpccmrx = TIMx->CCMR1;
    
  /* 復位輸出比較模式位 */
  tmpccmrx &= CCMR_OC13M_Mask;
  
  /* 選擇輸出比較模式 */
  tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;
  
  /* 復位輸出極性等級 */
  tmpccer &= CCER_CC1P_Reset;
  /* 設置輸出比較極性 */
  tmpccer |= TIM_OCInitStruct->TIM_OCPolarity;
  
  /* 設置輸出狀態 */
  tmpccer |= TIM_OCInitStruct->TIM_OutputState;
  
  /* 設置捕獲比較寄存器值 */
  TIMx->CCR1 = TIM_OCInitStruct->TIM_Pulse;
  
  if(((uint32_t) TIMx == TIM1_BASE) || ((uint32_t) TIMx == TIM8_BASE))
  {
    assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
    assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
    
    /* 復位輸出 N 極性等級 */
    tmpccer &= CCER_CC1NP_Reset;
    /* 設置輸出 N 極性 */
    tmpccer |= TIM_OCInitStruct->TIM_OCNPolarity;
    /* 復位輸出 N 狀態 */
    tmpccer &= CCER_CC1NE_Reset;
    
    /* 設置輸出 N 狀態 */
    tmpccer |= TIM_OCInitStruct->TIM_OutputNState;
    /* 復位輸出比較，輸出比較 N 空閒狀態 */
    tmpcr2 &= CR2_OIS1_Reset;
    tmpcr2 &= CR2_OIS1N_Reset;
    /* 設置輸出空閒狀態 */
    tmpcr2 |= TIM_OCInitStruct->TIM_OCIdleState;
    /* 設置輸出 N 空閒狀態 */
    tmpcr2 |= TIM_OCInitStruct->TIM_OCNIdleState;
  }
  /* 寫 TIMx CR2(控制寄存器2) */
  TIMx->CR2 = tmpcr2;
  
  /* 寫 TIMx CCMR1(捕獲/比較模式寄存器1) */
  TIMx->CCMR1 = tmpccmrx;
  
  /* 寫 TIMx CCER(捕獲/比較使能寄存器) */
  TIMx->CCER = tmpccer;
}

/**
  * @簡述  根據 TIM_OCInitStruct 中的特定參數初始化TIMx通道2.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_OCInitStruct: 指向一個包含特定TIMx外設的配置信息的 TIM_OCInitTypeDef 結構的指針.
  * @返回  沒有
  */
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
   
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx)); 
  assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
  assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));   
  /* 失能通道 2: 復位 CC2E 位 */
  TIMx->CCER &= CCER_CC2E_Reset;
  
  /* 得到 TIMx CCER(捕獲/比較使能) 寄存器的值 */  
  tmpccer = TIMx->CCER;
  /* 得到 TIMx CR2(控制寄存器2) 寄存器的值 */
  tmpcr2 =  TIMx->CR2;
  
  /* 得到 TIMx CCMR1(捕獲/比較模式) 寄存器的值 */
  tmpccmrx = TIMx->CCMR1;
    
  /* 復位輸出比較模式位 */
  tmpccmrx &= CCMR_OC24M_Mask;
  
  /* 選擇輸出比較模式 */
  tmpccmrx |= (uint16_t)(TIM_OCInitStruct->TIM_OCMode << 8);
  
  /* 復位輸出極性等級 */
  tmpccer &= CCER_CC2P_Reset;
  /* 設置輸出比較極性 */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCPolarity << 4);
  
  /* 設置輸出狀態 */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputState << 4);
  
  /* 設置捕獲比較寄存器值 */
  TIMx->CCR2 = TIM_OCInitStruct->TIM_Pulse;
  
  if(((uint32_t) TIMx == TIM1_BASE) || ((uint32_t) TIMx == TIM8_BASE))
  {
    assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
    assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
    
    /* 復位輸出 N 極性等級 */
    tmpccer &= CCER_CC2NP_Reset;
    /* 設置輸出 N 極性 */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCNPolarity << 4);
    /* 復位輸出 N 狀態 */
    tmpccer &= CCER_CC2NE_Reset;
    
    /* 設置輸出 N 狀態 */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputNState << 4);
    /* 復位輸出比較，輸出比較 N 空閒狀態 */
    tmpcr2 &= CR2_OIS2_Reset;
    tmpcr2 &= CR2_OIS2N_Reset;
    /* 設置輸出空閒狀態 */
    tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCIdleState << 2);
    /* 設置輸出 N 空閒狀態 */
    tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCNIdleState << 2);
  }
  /* 寫 TIMx CR2(控制寄存器2) */
  TIMx->CR2 = tmpcr2;
  
  /* 寫 TIMx CCMR1(捕獲/比較模式寄存器1) */
  TIMx->CCMR1 = tmpccmrx;
  
  /* 寫 TIMx CCER(捕獲/比較使能寄存器) */
  TIMx->CCER = tmpccer;
}

/**
  * @簡述  根據 TIM_OCInitStruct 中的特定參數初始化TIMx通道3.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_OCInitStruct: 指向一個包含特定TIMx外設的配置信息的 TIM_OCInitTypeDef 結構的指針.
  * @返回  沒有
  */
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
   
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx)); 
  assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
  assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));   
  /* 失能 3: 復位 CC3E 位 */
  TIMx->CCER &= CCER_CC3E_Reset;
  
  /* 得到 TIMx CCER(捕獲/比較使能) 寄存器的值 */
  tmpccer = TIMx->CCER;
  /* 得到 TIMx CR2(控制寄存器2) 寄存器的值 */
  tmpcr2 =  TIMx->CR2;
  
  /* 得到 TIMx CCMR2(捕獲/比較模式) 寄存器的值 */
  tmpccmrx = TIMx->CCMR2;
    
  /* 復位輸出比較模式位 */
  tmpccmrx &= CCMR_OC13M_Mask;
  
  /* 選擇輸出比較模式 */
  tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;
  
  /* 復位輸出極性等級 */
  tmpccer &= CCER_CC3P_Reset;
  /* 設置輸出比較極性 */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCPolarity << 8);
  
  /* 設置輸出狀態 */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputState << 8);
  
  /* 設置捕獲比較寄存器值 */
  TIMx->CCR3 = TIM_OCInitStruct->TIM_Pulse;
  
  if(((uint32_t) TIMx == TIM1_BASE) || ((uint32_t) TIMx == TIM8_BASE))
  {
    assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
    assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
    
    /* 復位輸出 N 極性等級 */
    tmpccer &= CCER_CC3NP_Reset;
    /* 設置輸出 N 極性 */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCNPolarity << 8);
    /* 復位輸出 N 狀態 */
    tmpccer &= CCER_CC3NE_Reset;
    
    /* 設置輸出 N 狀態 */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputNState << 8);
    /* 復位輸出比較，輸出比較 N 空閒狀態 */
    tmpcr2 &= CR2_OIS3_Reset;
    tmpcr2 &= CR2_OIS3N_Reset;
    /* 設置輸出空閒狀態 */
    tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCIdleState << 4);
    /* 設置輸出 N 空閒狀態 */
    tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCNIdleState << 4);
  }
  /* 寫 TIMx CR2(控制寄存器2) */
  TIMx->CR2 = tmpcr2;
  
  /* 寫 TIMx CCMR2(捕獲/比較模式寄存器2) */
  TIMx->CCMR2 = tmpccmrx;
  
  /* 寫 TIMx CCER(捕獲/比較使能寄存器) */
  TIMx->CCER = tmpccer;
}

/**
  * @簡述  根據 TIM_OCInitStruct 中的特定參數初始化TIMx通道4.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_OCInitStruct: 指向一個包含特定TIMx外設的配置信息的 TIM_OCInitTypeDef 結構的指針.
  * @返回  沒有
  */
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
   
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx)); 
  assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
  assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));   
  /* 失能通道 4: 復位 CC4E 位 */
  TIMx->CCER &= CCER_CC4E_Reset;
  
  /* 得到 TIMx CCER(捕獲/比較使能) 寄存器的值 */
  tmpccer = TIMx->CCER;
  /* 得到 TIMx CR2(控制寄存器2) 寄存器的值 */
  tmpcr2 =  TIMx->CR2;
  
  /* 得到 TIMx CCMR2(捕獲/比較模式) 寄存器的值 */
  tmpccmrx = TIMx->CCMR2;
    
  /* 復位輸出比較模式位 */
  tmpccmrx &= CCMR_OC24M_Mask;
  
  /* 選擇輸出比較模式 */
  tmpccmrx |= (uint16_t)(TIM_OCInitStruct->TIM_OCMode << 8);
  
  /* 復位輸出極性等級 */
  tmpccer &= CCER_CC4P_Reset;
  /* 設置輸出比較極性 */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCPolarity << 12);
  
  /* 設置輸出狀態 */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputState << 12);
  
  /* 設置捕獲比較寄存器值 */
  TIMx->CCR4 = TIM_OCInitStruct->TIM_Pulse;
  
  if(((uint32_t) TIMx == TIM1_BASE) || ((uint32_t) TIMx == TIM8_BASE))
  {
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
    /* 復位輸出比較空閒狀態 */
    tmpcr2 &= CR2_OIS4_Reset;
    /* 設置輸出空閒狀態 */
    tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCIdleState << 6);
  }
  /* 寫 TIMx CR2(控制寄存器2) */
  TIMx->CR2 = tmpcr2;
  
  /* 寫 TIMx CCMR2(捕獲/比較模式寄存器2) */  
  TIMx->CCMR2 = tmpccmrx;
  
  /* 寫 TIMx CCER(捕獲/比較使能寄存器) */
  TIMx->CCER = tmpccer;
}

/**
  * @簡述  根據 TIM_ ICInitStruct 中的特定參數初始化 TIMx.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_ICInitStruct: 指向一個包含特定 TIMx 外設的配置信息的 TIM_OCInitTypeDef 結構的指針.
  * @返回  沒有
  */
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct)
{
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_CHANNEL(TIM_ICInitStruct->TIM_Channel));
  assert_param(IS_TIM_IC_POLARITY(TIM_ICInitStruct->TIM_ICPolarity));
  assert_param(IS_TIM_IC_SELECTION(TIM_ICInitStruct->TIM_ICSelection));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICInitStruct->TIM_ICPrescaler));
  assert_param(IS_TIM_IC_FILTER(TIM_ICInitStruct->TIM_ICFilter));
  
  if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_1)
  {
    /* TI1 配置 */
    TI1_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* 設置輸入捕捉預分頻器值 */
    TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
  else if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_2)
  {
    /* TI2 配置 */
    TI2_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* 設置輸入捕捉預分頻器值 */
    TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
  else if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_3)
  {
    /* TI3 配置 */
    TI3_Config(TIMx,  TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* 設置輸入捕捉預分頻器值 */
    TIM_SetIC3Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
  else
  {
    /* TI4 配置 */
    TI4_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* 設置輸入捕捉預分頻器值 */
    TIM_SetIC4Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
}

/**
  * @簡述  依照TIM_ICInitStruct指定的參數設置TIM設備去配置外部的PWM信號.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_ICInitStruct: 指向一個包含特定 TIMx 外設的配置信息的 TIM_ICInitTypeDef 結構的指針.
  * @返回  沒有
  */
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct)
{
  uint16_t icoppositepolarity = TIM_ICPolarity_Rising;
  uint16_t icoppositeselection = TIM_ICSelection_DirectTI;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  /* 選擇相反的輸入極性 */
  if (TIM_ICInitStruct->TIM_ICPolarity == TIM_ICPolarity_Rising)
  {
    icoppositepolarity = TIM_ICPolarity_Falling;
  }
  else
  {
    icoppositepolarity = TIM_ICPolarity_Rising;
  }
  /* 選擇相反的輸入 */
  if (TIM_ICInitStruct->TIM_ICSelection == TIM_ICSelection_DirectTI)
  {
    icoppositeselection = TIM_ICSelection_IndirectTI;
  }
  else
  {
    icoppositeselection = TIM_ICSelection_DirectTI;
  }
  if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_1)
  {
    /* TI1 配置 */
    TI1_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity, TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* 設置輸入捕捉預分頻器值 */
    TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    /* TI2 配置 */
    TI2_Config(TIMx, icoppositepolarity, icoppositeselection, TIM_ICInitStruct->TIM_ICFilter);
    /* 設置輸入捕捉預分頻器值 */
    TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
  else
  { 
    /* TI2 配置 */
    TI2_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity, TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* 設置輸入捕捉預分頻器值 */
    TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    /* TI1 配置 */
    TI1_Config(TIMx, icoppositepolarity, icoppositeselection, TIM_ICInitStruct->TIM_ICFilter);
    /* 設置輸入捕捉預分頻器值 */
    TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
}

/**
  * @簡述  配置: 設置剎車特性，死區時間，鎖電平，OSSI，OSSR狀態和AOE(自動輸出使能).
  * @參數  TIMx: 此處x可以是1到8以選擇外設
  * @參數  TIM_BDTRInitStruct: 指向一個包含特定 TIMx 外設的配置信息的 TIM_BDTRInitTypeDef 結構的指針.
  * @返回  沒有
  */
void TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct)
{
  /* 檢查參數 */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_TIM_OSSR_STATE(TIM_BDTRInitStruct->TIM_OSSRState));
  assert_param(IS_TIM_OSSI_STATE(TIM_BDTRInitStruct->TIM_OSSIState));
  assert_param(IS_TIM_LOCK_LEVEL(TIM_BDTRInitStruct->TIM_LOCKLevel));
  assert_param(IS_TIM_BREAK_STATE(TIM_BDTRInitStruct->TIM_Break));
  assert_param(IS_TIM_BREAK_POLARITY(TIM_BDTRInitStruct->TIM_BreakPolarity));
  assert_param(IS_TIM_AUTOMATIC_OUTPUT_STATE(TIM_BDTRInitStruct->TIM_AutomaticOutput));
  /* 配置：鎖電平級別，間斷允許位和極性，OSSR狀態，OSSI狀態，滯後時間和自動輸出使能位 */
  TIMx->BDTR = (uint32_t)TIM_BDTRInitStruct->TIM_OSSRState | TIM_BDTRInitStruct->TIM_OSSIState |
             TIM_BDTRInitStruct->TIM_LOCKLevel | TIM_BDTRInitStruct->TIM_DeadTime |
             TIM_BDTRInitStruct->TIM_Break | TIM_BDTRInitStruct->TIM_BreakPolarity |
             TIM_BDTRInitStruct->TIM_AutomaticOutput;
}

/**
  * @簡述  把 TIM1_TimeBaseInitStruct 中的每一個參數按缺省值填入.
  * @參數  TIM_TimeBaseInitStruct : 指向一個將被初始化的 TIM_TimeBaseInitTypeDef 結構的指針.
  * @返回  沒有
  */
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct)
{
  /* 設置成默認配置 */
  TIM_TimeBaseInitStruct->TIM_Period = 0xFFFF;
  TIM_TimeBaseInitStruct->TIM_Prescaler = 0x0000;
  TIM_TimeBaseInitStruct->TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStruct->TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct->TIM_RepetitionCounter = 0x0000;
}

/**
  * @簡述  把 TIM1_OCInitStruct 中的每一個參數按缺省值填入.
  * @參數  TIM_OCInitStruct : 指向一個將被初始化的 TIM_OCInitStruct 結構的指針.
  * @返回  沒有
  */
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  /* 設置成默認配置 */
  TIM_OCInitStruct->TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStruct->TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStruct->TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStruct->TIM_Pulse = 0x0000;
  TIM_OCInitStruct->TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStruct->TIM_OCNPolarity = TIM_OCPolarity_High;
  TIM_OCInitStruct->TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStruct->TIM_OCNIdleState = TIM_OCNIdleState_Reset;
}

/**
  * @簡述  把 TIM1_ICInitStruct 中的每一個參數按缺省值填入.
  * @參數  TIM_ICInitStruct : 指向一個將被初始化的 TIM_ICInitStruct 結構的指針.
  * @返回  沒有
  */
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct)
{
  /* 設置成默認配置 */
  TIM_ICInitStruct->TIM_Channel = TIM_Channel_1;
  TIM_ICInitStruct->TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStruct->TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStruct->TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStruct->TIM_ICFilter = 0x00;
}

/**
  * @簡述  把 TIM1_BDTRInitStruct 中的每一個參數按缺省值填入.
  * @參數  TIM_BDTRInitStruct: 指向一個將被初始化的 TIM1_BDTRInitStruct 結構體.
  * @返回  沒有
  */
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct)
{
  /* 設置成默認配置 */
  TIM_BDTRInitStruct->TIM_OSSRState = TIM_OSSRState_Disable;
  TIM_BDTRInitStruct->TIM_OSSIState = TIM_OSSIState_Disable;
  TIM_BDTRInitStruct->TIM_LOCKLevel = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStruct->TIM_DeadTime = 0x00;
  TIM_BDTRInitStruct->TIM_Break = TIM_Break_Disable;
  TIM_BDTRInitStruct->TIM_BreakPolarity = TIM_BreakPolarity_Low;
  TIM_BDTRInitStruct->TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
}

/**
  * @簡述  使能或者失能指定的 TIM 外設.
  * @參數  TIMx: 此處x可以是1到8以選擇外設.
  * @參數  NewState: TIMx 外設的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* 使能 TIM 計數器 */
    TIMx->CR1 |= CR1_CEN_Set;
  }
  else
  {
    /* 失能 TIM 計數器 */
    TIMx->CR1 &= CR1_CEN_Reset;
  }
}

/**
  * @簡述  使能或失能 TIM 外圍主輸出.
  * @參數  TIMx: 此處x可以是1到8以選擇外設.
  * @參數  NewState: TIM 外圍主輸出的新狀態.
  *                  這個參數可以是: ENABLE or DISABLE.
  * @返回  沒有
  */
void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 使能 TIM 主輸出 */
    TIMx->BDTR |= BDTR_MOE_Set;
  }
  else
  {
    /* 失能 TIM 主輸出 */
    TIMx->BDTR &= BDTR_MOE_Reset;
  }  
}

/**
  * @簡述  使能或失能指定的 TIM 中斷.
  * @參數  TIMx: 此處x可以是1到8以選擇外設.
  * @參數  TIM_IT: 將被使能或失能的 TIM 中斷源.
  *                這個參數可以取下列值之一:
  *                TIM_IT_Update:  TIM 更新中斷源
  *                TIM_IT_CC1:     TIM 獲/比較 1 中斷源
  *                TIM_IT_CC2:     TIM 獲/比較 2 中斷源
  *                TIM_IT_CC3:     TIM 獲/比較 3 中斷源
  *                TIM_IT_CC4:     TIM 獲/比較 4 中斷源
  *                TIM_IT_COM:     TIM COM中斷源
  *                TIM_IT_Trigger: TIM 觸發中斷源
  *                TIM_IT_Break:   TIM 剎車中斷源
  * @註解 
  *   - TIM6 和 TIM7 只能產生校正中斷. 
  *   - TIM_IT_COM 和 TIM_IT_Break 只能和 TIM1 和 TIM8 一起使用.  
  * @參數  NewState: TIM 中斷的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState)
{  
  /* 檢查參數s */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_IT(TIM_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* 使能中斷源 */
    TIMx->DIER |= TIM_IT;
  }
  else
  {
    /* 失能中斷源 */
    TIMx->DIER &= (uint16_t)~TIM_IT;
  }
}

/**
  * @簡述  配置將由軟件引發的 TIM 事件.
  * @參數  TIMx: 此處x可以是1到8以選擇外設.
  * @參數  TIM_EventSource: 指定事件源.
  *                         這個參數可以取下列一個或更多的值:	   
  *          TIM_EventSource_Update: 定時器更新事件源
  *          TIM_EventSource_CC1:     定時器捕捉比較 1 事件源
  *          TIM_EventSource_CC2:     定時器捕捉比較 2 事件源
  *          TIM_EventSource_CC3:     定時器捕捉比較 3 事件源
  *          TIM_EventSource_CC4:     定時器捕捉比較 4 事件源
  *          TIM_EventSource_COM:     定時器 COM 事件源  
  *          TIM_EventSource_Trigger: 定時器觸發器事件源
  *          TIM_EventSource_Break:   定時器剎車事件源
  * @註解 
  *   - TIM6 和 TIM7 只能產生校正中斷. 
  *   - TIM_IT_COM 和 TIM_IT_Break 只能和 TIM1 和 TIM8 一起使用. 
  * @返回  沒有
  */
void TIM_GenerateEvent(TIM_TypeDef* TIMx, uint16_t TIM_EventSource)
{ 
  /* 檢查參數 */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_EVENT_SOURCE(TIM_EventSource));
  
  /* 設置事件源 */
  TIMx->EGR = TIM_EventSource;
}

/**
  * @簡述  配置 TIMx 的DMA接口.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_DMABase: DMA 基地址.
  *                     這個參數可以取下面的值之一:
  *   TIM_DMABase_CR, TIM_DMABase_CR2, TIM_DMABase_SMCR,
  *   TIM_DMABase_DIER, TIM1_DMABase_SR, TIM_DMABase_EGR,
  *   TIM_DMABase_CCMR1, TIM_DMABase_CCMR2, TIM_DMABase_CCER,
  *   TIM_DMABase_CNT, TIM_DMABase_PSC, TIM_DMABase_ARR,
  *   TIM_DMABase_RCR, TIM_DMABase_CCR1, TIM_DMABase_CCR2,
  *   TIM_DMABase_CCR3, TIM_DMABase_CCR4, TIM_DMABase_BDTR,
  *   TIM_DMABase_DCR.
  * @參數  TIM_DMABurstLength: DMA 脈衝串長度.
  *                            這個參數可以取下面兩個值之一:
  *        TIM_DMABurstLength_1Byte 和 TIM_DMABurstLength_18Bytes.
  * @返回  沒有
  */
void TIM_DMAConfig(TIM_TypeDef* TIMx, uint16_t TIM_DMABase, uint16_t TIM_DMABurstLength)
{
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_DMA_BASE(TIM_DMABase));
  assert_param(IS_TIM_DMA_LENGTH(TIM_DMABurstLength));
  /* 設置 DMA 基地址和 DMA 脈衝串長度 */
  TIMx->DCR = TIM_DMABase | TIM_DMABurstLength;
}

/**
  * @簡述  使能或失能 TIMx 的 DMA 請求.
  * @參數  TIMx: 此處x可以是1到8以選擇外設. 
  * @參數  TIM_DMASource: 指定 DMA 請求來源.
  *                       這個參數可以是下面任何值的組合:
  *                       TIM_DMA_Update:  TIM 更新中斷源
  *                       TIM_DMA_CC1:     TIM 捕獲比較 1 DMA 源
  *                       TIM_DMA_CC2:     TIM 捕獲比較 2 DMA 源
  *                       TIM_DMA_CC3:     TIM 捕獲比較 3 DMA 源
  *                       TIM_DMA_CC4:     TIM 捕獲比較 4 DMA 源
  *                       TIM_DMA_COM:     TIM COM DMA 源
  *                       TIM_DMA_Trigger: TIM 觸發 DMA 源
  * @參數  NewState: DMA 請求新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void TIM_DMACmd(TIM_TypeDef* TIMx, uint16_t TIM_DMASource, FunctionalState NewState)
{ 
  /* 檢查參數 */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_DMA_SOURCE(TIM_DMASource));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* 使能 DMA 源 */
    TIMx->DIER |= TIM_DMASource; 
  }
  else
  {
    /* 失能 DMA 源 */
    TIMx->DIER &= (uint16_t)~TIM_DMASource;
  }
}

/**
  * @簡述  配置 TIMx 內部時鐘
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @返回  沒有
  */
void TIM_InternalClockConfig(TIM_TypeDef* TIMx)
{
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  /* 失能內部時鐘預分頻器從模式 */
  TIMx->SMCR &=  SMCR_SMS_Mask;
}

/**
  * @簡述  配置 TIMx 內部觸發器為外部時鐘模式
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_ITRSource: 觸發器.
  *                       這個參數可以取下面的值之一:
  *                       TIM_TS_ITR0: 內部觸發器 0
  *                       TIM_TS_ITR1: 內部觸發器 1
  *                       TIM_TS_ITR2: 內部觸發器 2
  *                       TIM_TS_ITR3: 內部觸發器 3
  * @返回  沒有
  */
void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource)
{
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_INTERNAL_TRIGGER_SELECTION(TIM_InputTriggerSource));
  /* 選擇內部觸發器 */
  TIM_SelectInputTrigger(TIMx, TIM_InputTriggerSource);
  /* 選擇外部時鐘模式1 */
  TIMx->SMCR |= TIM_SlaveMode_External1;
}

/**
  * @簡述  設置 TIMx 觸發為外部時鐘
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_TIxExternalCLKSource: 觸發器.
  *          這個參數可以取下面的值之一:
  *          TIM_TIxExternalCLK1Source_TI1ED: TI1 邊緣檢測器
  *          TIM_TIxExternalCLK1Source_TI1: 已篩選的定時器輸入 1
  *          TIM_TIxExternalCLK1Source_TI2: 已篩選的定時器輸入 2
  * @參數  TIM_ICPolarity: 指定 TIx 極性.
  *          這個參數可以取下面的值之一:
  *          TIM_ICPolarity_Rising
  *          TIM_ICPolarity_Falling
  * @參數  ICFilter : 指定輸入捕獲過濾器.
  *                   該參數可以是0x0到0xF之間的值.
  * @返回  沒有
  */
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_TIxExternalCLKSource,
                                uint16_t TIM_ICPolarity, uint16_t ICFilter)
{
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_TIXCLK_SOURCE(TIM_TIxExternalCLKSource));
  assert_param(IS_TIM_IC_POLARITY(TIM_ICPolarity));
  assert_param(IS_TIM_IC_FILTER(ICFilter));
  /* 配置定時器輸入時鐘源 */
  if (TIM_TIxExternalCLKSource == TIM_TIxExternalCLK1Source_TI2)
  {
    TI2_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
  }
  else
  {
    TI1_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
  }
  /* 選擇觸發器 */
  TIM_SelectInputTrigger(TIMx, TIM_TIxExternalCLKSource);
  /* 選擇外部時鐘模式1 */
  TIMx->SMCR |= TIM_SlaveMode_External1;
}

/**
  * @簡述  配置外部時鐘模式1
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_ExtTRGPrescaler: 外部觸發器預分頻數.
  *          這個參數可以取下面的值之一:
  *          TIM_ExtTRGPSC_OFF:  ETRP 預分頻器 關.
  *          TIM_ExtTRGPSC_DIV2: ETRP 頻率除以 2.
  *          TIM_ExtTRGPSC_DIV4: ETRP 頻率除以 4.
  *          TIM_ExtTRGPSC_DIV8: ETRP 頻率除以 8.
  * @參數  TIM_ExtTRGPolarity: 外部觸發器極性.
  *          這個參數可以取下面的值之一:
  *          TIM_ExtTRGPolarity_Inverted:    低電平或下降沿.
  *          TIM_ExtTRGPolarity_NonInverted: 高電平或上升沿.
  * @參數  ExtTRGFilter: 外部觸發器過濾器.
  *          該參數可以是0x0到0xF之間的值
  * @返回  沒有
  */ 
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                             uint16_t ExtTRGFilter)
{
  uint16_t tmpsmcr = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
  assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
  assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));
  /* 配置 ETR 時鐘源 */
  TIM_ETRConfig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);
  
  /* 得到 TIMx SMCR(從模式控制) 寄存器的值 */
  tmpsmcr = TIMx->SMCR;
  /* 復位 SMS(從模式選擇) 位 */
  tmpsmcr &= SMCR_SMS_Mask;
  /* 選擇外部時鐘模式1 */
  tmpsmcr |= TIM_SlaveMode_External1;
  /* 選擇觸發器 ，選擇 : ETRF */
  tmpsmcr &= SMCR_TS_Mask;
  tmpsmcr |= TIM_TS_ETRF;
  /* 寫 TIMx SMCR */
  TIMx->SMCR = tmpsmcr;
}

/**
  * @簡述  配置外部時鐘模式2
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_ExtTRGPrescaler: 外部觸發器預分頻數.
  *          它可以是下面的值之一:
  *          TIM_ExtTRGPSC_OFF:  ETRP 預分頻器 關.
  *          TIM_ExtTRGPSC_DIV2: ETRP 頻率除以 2.
  *          TIM_ExtTRGPSC_DIV4: ETRP 頻率除以 4.
  *          TIM_ExtTRGPSC_DIV8: ETRP 頻率除以 8.
  * @參數  TIM_ExtTRGPolarity: 外部觸發器極性.
  *          它可以是下面的值之一:
  *          TIM_ExtTRGPolarity_Inverted:    低電平或下降沿.
  *          TIM_ExtTRGPolarity_NonInverted: 高電平或上升沿.
  * @參數  ExtTRGFilter: 外部觸發器過濾器.
  *          該參數可以是0x0到0xF之間的值
  * @返回  沒有
  */
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, 
                             uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter)
{
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
  assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
  assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));
  /* 配置 ETR 時鐘源 */
  TIM_ETRConfig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);
  /* 使能外部時鐘模式2 */
  TIMx->SMCR |= SMCR_ECE_Set;
}

/**
  * @簡述  配置 TIMx 外部觸發 (ETR).
  * @簡述  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_ExtTRGPrescaler: 外部觸發器預分頻數.
  *          它可以是下面的值之一:
  *          TIM_ExtTRGPSC_OFF:  ETRP 預分頻器 關.
  *          TIM_ExtTRGPSC_DIV2: ETRP 頻率除以 2.
  *          TIM_ExtTRGPSC_DIV4: ETRP 頻率除以 4.
  *          TIM_ExtTRGPSC_DIV8: ETRP 頻率除以 8.
  * @參數  TIM_ExtTRGPolarity: 外部觸發器極性.
  *          它可以是下面的值之一:
  *          TIM_ExtTRGPolarity_Inverted:    低電平或下降沿.
  *          TIM_ExtTRGPolarity_NonInverted: 高電平或上升沿.
  * @參數  ExtTRGFilter: 外部觸發器過濾器.
  *          該參數可以是0x0到0xF之間的值
  * @返回  沒有
  */
void TIM_ETRConfig(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                   uint16_t ExtTRGFilter)
{
  uint16_t tmpsmcr = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
  assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
  assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));
  tmpsmcr = TIMx->SMCR;
  /* 復位 ETR 位 */
  tmpsmcr &= SMCR_ETR_Mask;
  /* 設置預分頻器，過濾器值和極性 */
  tmpsmcr |= (uint16_t)(TIM_ExtTRGPrescaler | (uint16_t)(TIM_ExtTRGPolarity | (uint16_t)(ExtTRGFilter << (uint16_t)8)));
  /* 寫TIMx SMCR */
  TIMx->SMCR = tmpsmcr;
}

/**
  * @簡述  配置 TIMx 預分頻器.
  * @參數  TIMx: 此處x可以是1到8以選擇外設.
  * @參數  Prescaler: 指定預分頻數的新值
  * @參數  TIM_PSCReloadMode: 指定預分頻數重載模式
  *          這個參數可以取下面的值之一:
  *          TIM_PSCReloadMode_Update:    TIM 預分頻值在更新事件裝入.
  *          TIM_PSCReloadMode_Immediate: TIM 預分頻值即時裝入.
  * @返回  沒有
  */
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode)
{
  /* 檢查參數 */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_PRESCALER_RELOAD(TIM_PSCReloadMode));
  /* 設置預分頻器值 */
  TIMx->PSC = Prescaler;
  /* 設置 或 復位 UG 位 */
  TIMx->EGR = TIM_PSCReloadMode;
}

/**
  * @簡述  指定 TIMx 計數器模式.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_CounterMode: 待使用的計數器模式
  *          這個參數可以取下面的值之一:
  *          TIM_CounterMode_Up:             TIM 向上計數模式
  *          TIM_CounterMode_Down:           TIM 向下計數模式
  *          TIM_CounterMode_CenterAligned1: TIM 中心對齊模式1
  *          TIM_CounterMode_CenterAligned2: TIM 中心對齊模式2
  *          TIM_CounterMode_CenterAligned3: TIM 中心對齊模式3
  * @返回  沒有
  */
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint16_t TIM_CounterMode)
{
  uint16_t tmpcr1 = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_COUNTER_MODE(TIM_CounterMode));
  tmpcr1 = TIMx->CR1;
  /* 復位 CMS 和 DIR 位 */
  tmpcr1 &= CR1_CounterMode_Mask;
  /* 設置計數模式 */
  tmpcr1 |= TIM_CounterMode;
  /* 寫 TIMx CR1 寄存器 */
  TIMx->CR1 = tmpcr1;
}

/**
  * @簡述  選擇輸入觸發源
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_InputTriggerSource: 輸入觸發源.
  *          這個參數可以取下面的值之一:
  *          TIM_TS_ITR0:    內部觸發器 0
  *          TIM_TS_ITR1:    內部觸發器 1
  *          TIM_TS_ITR2:    內部觸發器 2
  *          TIM_TS_ITR3:    內部觸發器 3
  *          TIM_TS_TI1F_ED: TI1 邊緣檢測其
  *          TIM_TS_TI1FP1:  過濾器時鐘輸入 1
  *          TIM_TS_TI2FP2:  過濾器時鐘輸入 2
  *          TIM_TS_ETRF:    外部觸發輸入
  * @返回  沒有
  */
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource)
{
  uint16_t tmpsmcr = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_TRIGGER_SELECTION(TIM_InputTriggerSource));
  /* 得到 TIMx SMCR 寄存器值 */
  tmpsmcr = TIMx->SMCR;
  /* 復位 TS 位 */
  tmpsmcr &= SMCR_TS_Mask;
  /* 設置輸入觸發源 */
  tmpsmcr |= TIM_InputTriggerSource;
  /* 寫 TIMx SMCR */
  TIMx->SMCR = tmpsmcr;
}

/**
  * @簡述  配置 TIMx 編碼器界面.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_EncoderMode: 指定 TIMx 編碼器模式.
  *          這個參數可以取下面的值之一:
  *          TIM_EncoderMode_TI1:  TIM編碼器使用模式1.
  *          TIM_EncoderMode_TI2:  TIM編碼器使用模式2.
  *          TIM_EncoderMode_TI12: TIM編碼器使用模式3.
  * @參數  TIM_IC1Polarity: 指定 IC1 極性
  *          這個參數可以取下面的值之一:
  *          TIM_ICPolarity_Falling: IC 下降沿.
  *          TIM_ICPolarity_Rising:  IC 上升沿.
  * @參數  TIM_IC2Polarity: 指定 IC2 極性
  *          這個參數可以取下面的值之一:
  *          TIM_ICPolarity_Falling: IC 下降沿.
  *          TIM_ICPolarity_Rising:  IC 上升沿.
  * @返回  沒有
  */
void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, uint16_t TIM_EncoderMode,
                                uint16_t TIM_IC1Polarity, uint16_t TIM_IC2Polarity)
{
  uint16_t tmpsmcr = 0;
  uint16_t tmpccmr1 = 0;
  uint16_t tmpccer = 0;
    
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_ENCODER_MODE(TIM_EncoderMode));
  assert_param(IS_TIM_IC_POLARITY(TIM_IC1Polarity));
  assert_param(IS_TIM_IC_POLARITY(TIM_IC2Polarity));

  /* 得到 TIMx SMCR 寄存器的值 */
  tmpsmcr = TIMx->SMCR;

  /* 得到 TIMx CCMR1 寄存器的值 */
  tmpccmr1 = TIMx->CCMR1;

  /* 得到 TIMx CCER 寄存器的值 */
  tmpccer = TIMx->CCER;

  /* 設置編碼器模式 */
  tmpsmcr &= SMCR_SMS_Mask;
  tmpsmcr |= TIM_EncoderMode;

  /* 選擇捕獲比較 1 和捕獲比較 2 作為輸入 */
  tmpccmr1 &= CCMR_CC13S_Mask & CCMR_CC24S_Mask;
  tmpccmr1 |= CCMR_TI13Direct_Set | CCMR_TI24Direct_Set;

  /* 設置 TI1 和 TI2 極性 */
  tmpccer &= CCER_CC1P_Reset & CCER_CC2P_Reset;
  tmpccer |= (uint16_t)(TIM_IC1Polarity | (uint16_t)(TIM_IC2Polarity << (uint16_t)4));

  /* 寫 TIMx SMCR */
  TIMx->SMCR = tmpsmcr;

  /* 寫 TIMx CCMR1 */
  TIMx->CCMR1 = tmpccmr1;

  /* 寫 TIMx CCER */
  TIMx->CCER = tmpccer;
}

/**
  * @簡述  置 TIMx 輸出1為活動或者非活動電平.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_ForcedAction: 輸出信號的設置動作.
  *          這個參數可以取下面的值之一:
  *          TIM_ForcedAction_Active:   強制OCxREF為有效電平
  *          TIM_ForcedAction_InActive: 強制OCxREF為無效電平
  * @返回  沒有
  */
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction)
{
  uint16_t tmpccmr1 = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
  tmpccmr1 = TIMx->CCMR1;
  /* 復位 OC1M 位 */
  tmpccmr1 &= CCMR_OC13M_Mask;
  /* 配置強制輸出模式 */
  tmpccmr1 |= TIM_ForcedAction;
  /* 寫 TIMx CCMR1 寄存器 */
  TIMx->CCMR1 = tmpccmr1;
}

/**
  * @簡述  置 TIMx 輸出2為活動或者非活動電平.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_ForcedAction: 輸出信號的設置動作.
  *          這個參數可以取下面的值之一:
  *          TIM_ForcedAction_Active:   強制OCxREF為有效電平
  *          TIM_ForcedAction_InActive: 強制OCxREF為無效電平
  * @返回  沒有
  */
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction)
{
  uint16_t tmpccmr1 = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
  tmpccmr1 = TIMx->CCMR1;
  /* 復位 OC2M 位 */
  tmpccmr1 &= CCMR_OC24M_Mask;
  /* 配置強制輸出模式 */
  tmpccmr1 |= (uint16_t)(TIM_ForcedAction << 8);
  /* 寫 TIMx CCMR1 寄存器 */
  TIMx->CCMR1 = tmpccmr1;
}

/**
  * @簡述  置 TIMx 輸出3為活動或者非活動電平.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_ForcedAction: 輸出信號的設置動作.
  *          這個參數可以取下面的值之一:
  *          TIM_ForcedAction_Active:   強制OCxREF為有效電平
  *          TIM_ForcedAction_InActive: 強制OCxREF為無效電平
  * @返回  沒有
  */
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction)
{
  uint16_t tmpccmr2 = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
  tmpccmr2 = TIMx->CCMR2;
  /* 復位 OC1M 位 */
  tmpccmr2 &= CCMR_OC13M_Mask;
  /* 配置強制輸出模式 */
  tmpccmr2 |= TIM_ForcedAction;
  /* 寫 TIMx CCMR2 寄存器 */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @簡述  置 TIMx 輸出4為活動或者非活動電平.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_ForcedAction: 輸出信號的設置動作.
  *          這個參數可以取下面的值之一:
  *          TIM_ForcedAction_Active:   強制OCxREF為有效電平
  *          TIM_ForcedAction_InActive: 強制OCxREF為無效電平
  * @返回  沒有
  */
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction)
{
  uint16_t tmpccmr2 = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
  tmpccmr2 = TIMx->CCMR2;
  /* 復位 OC2M 位 */
  tmpccmr2 &= CCMR_OC24M_Mask;
  /* 配置強制輸出模式 */
  tmpccmr2 |= (uint16_t)(TIM_ForcedAction << 8);
  /* 寫 TIMx CCMR2 寄存器 */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @簡述  使能或者失能 TIMx 在 ARR 上的預裝載寄存器.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  NewState: 在TIM1_CR1寄存器中的ARPE位的新狀態
  *                  這個參數可以是: ENABLE or DISABLE.
  * @返回  沒有
  */
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 設置 ARR 的預裝載位 */
    TIMx->CR1 |= CR1_ARPE_Set;
  }
  else
  {
    /* 復位 ARR 的預裝載位 */
    TIMx->CR1 &= CR1_ARPE_Reset;
  }
}

/**
  * @簡述  選擇 TIM 外設的通訊事件.
  * @參數  TIMx: 此處x可以是1到8以選擇外設
  * @參數  NewState: 通訊事件的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void TIM_SelectCOM(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 設置 COM 位 */
    TIMx->CR2 |= CR2_CCUS_Set;
  }
  else
  {
    /* 復位 COM 位 */
    TIMx->CR2 &= CR2_CCUS_Reset;
  }
}

/**
  * @簡述  選擇 TIMx 外設的捕獲比較 DMA 源.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  NewState: 捕獲比較 DMA 源的新狀態
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void TIM_SelectCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 設置 CCDS 位 */
    TIMx->CR2 |= CR2_CCDS_Set;
  }
  else
  {
    /* 復位 CCDS 位 */
    TIMx->CR2 &= CR2_CCDS_Reset;
  }
}

/**
  * @簡述  設置或者復位 TIMx 捕獲比較控制位.
  * @參數  TIMx: 此處x可以是1到8以選擇外設
  * @參數  NewState: 捕獲比較預載控制位的新狀態
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void TIM_CCPreloadControl(TIM_TypeDef* TIMx, FunctionalState NewState)
{ 
  /* 檢查參數 */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 設置 CCPC 位 */
    TIMx->CR2 |= CR2_CCPC_Set;
  }
  else
  {
    /* 復位 CCPC 位 */
    TIMx->CR2 &= CR2_CCPC_Reset;
  }
}

/**
  * @簡述  使能或者失能 TIMx 在 CCR1 上的預裝載寄存器.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_OCPreload: 輸出比較預裝載狀態
  *                       這個參數可以取下面的值之一:
  *                       TIM_OCPreload_Enable
  *                       TIM_OCPreload_Disable
  * @返回  沒有
  */
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload)
{
  uint16_t tmpccmr1 = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));
  tmpccmr1 = TIMx->CCMR1;
  /* 復位 OC1PE 位 */
  tmpccmr1 &= CCMR_OC13PE_Reset;
  /* 使能或者失能預裝載寄存器 */
  tmpccmr1 |= TIM_OCPreload;
  /* 寫 TIMx CCMR1 寄存器 */
  TIMx->CCMR1 = tmpccmr1;
}

/**
  * @簡述  使能或者失能 TIMx 在 CCR2 上的預裝載寄存器.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_OCPreload: 輸出比較預裝載狀態
  *                       這個參數可以取下面的值之一:
  *                       TIM_OCPreload_Enable
  *                       TIM_OCPreload_Disable
  * @返回  沒有
  */
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload)
{
  uint16_t tmpccmr1 = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));
  tmpccmr1 = TIMx->CCMR1;
  /* 復位 OC2PE 位 */
  tmpccmr1 &= CCMR_OC24PE_Reset;
  /* 使能或者失能預裝載寄存器 */
  tmpccmr1 |= (uint16_t)(TIM_OCPreload << 8);
  /* 寫 TIMx CCMR1 寄存器 */
  TIMx->CCMR1 = tmpccmr1;
}

/**
  * @簡述  使能或者失能 TIMx 在 CCR3 上的預裝載寄存器.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_OCPreload: 輸出比較預裝載狀態
  *                       這個參數可以取下面的值之一:
  *                       TIM_OCPreload_Enable
  *                       TIM_OCPreload_Disable
  * @返回  沒有
  */
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload)
{
  uint16_t tmpccmr2 = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));
  tmpccmr2 = TIMx->CCMR2;
  /* 復位 OC3PE 位 */
  tmpccmr2 &= CCMR_OC13PE_Reset;
  /* 使能或者失能預裝載寄存器 */
  tmpccmr2 |= TIM_OCPreload;
  /* 寫 TIMx CCMR2 寄存器 */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @簡述  使能或者失能 TIMx 在 CCR4 上的預裝載寄存器.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_OCPreload: 輸出比較預裝載狀態
  *                       這個參數可以取下面的值之一:
  *                       TIM_OCPreload_Enable
  *                       TIM_OCPreload_Disable
  * @返回  沒有
  */
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload)
{
  uint16_t tmpccmr2 = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));
  tmpccmr2 = TIMx->CCMR2;
  /* 復位 OC4PE 位 */
  tmpccmr2 &= CCMR_OC24PE_Reset;
  /* 使能或者失能預裝載寄存器 */
  tmpccmr2 |= (uint16_t)(TIM_OCPreload << 8);
  /* 寫 TIMx CCMR2 寄存器 */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @簡述  設置 TIMx 捕獲比較1快速特徵.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_OCFast: 輸出比較快速特性新狀態.
  *                    這個參數可以取下面的值之一:
  *                    TIM_OCFast_Enable:  TIM 輸出比較快速性能使能
  *                    TIM_OCFast_Disable: TIM 輸出比較快速性能失能
  * @返回  沒有
  */
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast)
{
  uint16_t tmpccmr1 = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));
  /* 得到 TIMx CCMR1 寄存器的值 */
  tmpccmr1 = TIMx->CCMR1;
  /* 復位 OC1FE 位 */
  tmpccmr1 &= CCMR_OC13FE_Reset;
  /* 使能或失能捕獲比較快速特徵 */
  tmpccmr1 |= TIM_OCFast;
  /* 寫 TIMx CCMR1 */
  TIMx->CCMR1 = tmpccmr1;
}

/**
  * @簡述  設置 TIMx 捕獲比較2快速特徵.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_OCFast: 輸出比較快速特性新狀態.
  *                    這個參數可以取下面的值之一:
  *                    TIM_OCFast_Enable:  TIM 輸出比較快速性能使能
  *                    TIM_OCFast_Disable: TIM 輸出比較快速性能失能
  * @返回  沒有
  */
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast)
{
  uint16_t tmpccmr1 = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));
  /* 得到 TIMx CCMR1 寄存器的值 */
  tmpccmr1 = TIMx->CCMR1;
  /* 復位 OC2FE 位 */
  tmpccmr1 &= CCMR_OC24FE_Reset;
  /* 使能或失能捕獲比較快速特徵 */
  tmpccmr1 |= (uint16_t)(TIM_OCFast << 8);
  /* 寫 TIMx CCMR1 */
  TIMx->CCMR1 = tmpccmr1;
}

/**
  * @簡述  設置 TIMx 捕獲比較3快速特徵.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_OCFast: 輸出比較快速特性新狀態.
  *                    這個參數可以取下面的值之一:
  *                    TIM_OCFast_Enable:  TIM 輸出比較快速性能使能
  *                    TIM_OCFast_Disable: TIM 輸出比較快速性能失能
  * @返回  沒有
  */
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast)
{
  uint16_t tmpccmr2 = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));
  /* 得到 TIMx CCMR2 寄存器的值 */
  tmpccmr2 = TIMx->CCMR2;
  /* 復位 OC3FE 位 */
  tmpccmr2 &= CCMR_OC13FE_Reset;
  /* 使能或失能捕獲比較快速特徵 */
  tmpccmr2 |= TIM_OCFast;
  /* 寫 TIMx CCMR2 */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @簡述  設置 TIMx 捕獲比較4快速特徵.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_OCFast: 輸出比較快速特性新狀態.
  *                    這個參數可以取下面的值之一:
  *                    TIM_OCFast_Enable:  TIM 輸出比較快速性能使能
  *                    TIM_OCFast_Disable: TIM 輸出比較快速性能失能
  * @返回  沒有
  */
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast)
{
  uint16_t tmpccmr2 = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));
  /* 得到 TIMx CCMR2 寄存器的值 */
  tmpccmr2 = TIMx->CCMR2;
  /* 復位 OC4FE 位 */
  tmpccmr2 &= CCMR_OC24FE_Reset;
  /* 使能或失能捕獲比較快速特徵 */
  tmpccmr2 |= (uint16_t)(TIM_OCFast << 8);
  /* 寫 TIMx CCMR2 */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @簡述  在一個外部事件時清除或者保持 OCREF1 信號
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_OCClear: 輸出比較清除使能位的新狀態.
  *                     這個參數可以取下面的值之一:
  *                     TIM_OCClear_Enable:  TIM 輸出比較清除使能
  *                     TIM_OCClear_Disable: TIM 輸出比較清除失能
  * @返回  沒有
  */
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear)
{
  uint16_t tmpccmr1 = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));
  tmpccmr1 = TIMx->CCMR1;
  /* 復位 OC1CE 位 */
  tmpccmr1 &= CCMR_OC13CE_Reset;
  /* 使能或失能輸出比較清除位 */
  tmpccmr1 |= TIM_OCClear;
  /* 寫 TIMx CCMR1 寄存器 */
  TIMx->CCMR1 = tmpccmr1;
}

/**
  * @簡述  在一個外部事件時清除或者保持 OCREF2 信號
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_OCClear: 輸出比較清除使能位的新狀態.
  *                     這個參數可以取下面的值之一:
  *                     TIM_OCClear_Enable:  TIM 輸出比較清除使能
  *                     TIM_OCClear_Disable: TIM 輸出比較清除失能
  * @返回  沒有
  */
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear)
{
  uint16_t tmpccmr1 = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));
  tmpccmr1 = TIMx->CCMR1;
  /* 復位 OC2CE 位 */
  tmpccmr1 &= CCMR_OC24CE_Reset;
  /* 使能或失能輸出比較清除位 */
  tmpccmr1 |= (uint16_t)(TIM_OCClear << 8);
  /* 寫 TIMx CCMR1 寄存器 */
  TIMx->CCMR1 = tmpccmr1;
}

/**
  * @簡述  在一個外部事件時清除或者保持 OCREF3 信號
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_OCClear: 輸出比較清除使能位的新狀態.
  *                     這個參數可以取下面的值之一:
  *                     TIM_OCClear_Enable:  TIM 輸出比較清除使能
  *                     TIM_OCClear_Disable: TIM 輸出比較清除失能
  * @返回  沒有
  */
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear)
{
  uint16_t tmpccmr2 = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));
  tmpccmr2 = TIMx->CCMR2;
  /* 復位 OC3CE 位 */
  tmpccmr2 &= CCMR_OC13CE_Reset;
  /* 使能或失能輸出比較清除位 */
  tmpccmr2 |= TIM_OCClear;
  /* 寫 TIMx CCMR2 寄存器 */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @簡述  在一個外部事件時清除或者保持 OCREF4 信號
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_OCClear: 輸出比較清除使能位的新狀態.
  *                     這個參數可以取下面的值之一:
  *                     TIM_OCClear_Enable:  TIM 輸出比較清除使能
  *                     TIM_OCClear_Disable: TIM 輸出比較清除失能
  * @返回  沒有
  */
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear)
{
  uint16_t tmpccmr2 = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));
  tmpccmr2 = TIMx->CCMR2;
  /* 復位 OC4CE 位 */
  tmpccmr2 &= CCMR_OC24CE_Reset;
  /* 使能或失能輸出比較清除位 */
  tmpccmr2 |= (uint16_t)(TIM_OCClear << 8);
  /* 寫 TIMx CCMR2 寄存器 */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @簡述  設置 TIMx 通道1極性.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_OCPolarity: 指定的 OC1 極性
  *                        這個參數可以取下面的值之一:
  *                        TIM_OCPolarity_High: 輸出比較極性高
  *                        TIM_OCPolarity_Low:  輸出比較極性低
  * @返回  沒有
  */
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity)
{
  uint16_t tmpccer = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));
  tmpccer = TIMx->CCER;
  /* 設置或復位 CC1P 位 */
  tmpccer &= CCER_CC1P_Reset;
  tmpccer |= TIM_OCPolarity;
  /* 寫 TIMx CCER 寄存器 */
  TIMx->CCER = tmpccer;
}

/**
  * @簡述  配置 TIMx 通道 1N 極性.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_OCNPolarity: 指定 OC1N 極性
  *                         這個參數可以取下面的值之一:
  *                         TIM_OCNPolarity_High: 輸出比較極性高
  *                         TIM_OCNPolarity_Low:  輸出比較極性低
  * @返回  沒有
  */
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity)
{
  uint16_t tmpccer = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));
   
  tmpccer = TIMx->CCER;
  /* 設置或復位 CC1NP 位 */
  tmpccer &= CCER_CC1NP_Reset;
  tmpccer |= TIM_OCNPolarity;
  /* 寫 TIMx CCER 寄存器 */
  TIMx->CCER = tmpccer;
}

/**
  * @簡述  設置 TIMx 通道2極性.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_OCPolarity: 指定的 OC2 極性
  *                        這個參數可以取下面的值之一:
  *                        TIM_OCPolarity_High: 輸出比較極性高
  *                        TIM_OCPolarity_Low:  輸出比較極性低
  * @返回  沒有
  */
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity)
{
  uint16_t tmpccer = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));
  tmpccer = TIMx->CCER;
  /* 設置或復位 CC2P 位 */
  tmpccer &= CCER_CC2P_Reset;
  tmpccer |= (uint16_t)(TIM_OCPolarity << 4);
  /* 寫 TIMx CCER 寄存器 */
  TIMx->CCER = tmpccer;
}

/**
  * @簡述  配置 TIMx 通道 2N 極性.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_OCNPolarity: 指定 OC2N 極性
  *                         這個參數可以取下面的值之一:
  *                         TIM_OCNPolarity_High: 輸出比較極性高
  *                         TIM_OCNPolarity_Low:  輸出比較極性低
  * @返回  沒有
  */
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity)
{
  uint16_t tmpccer = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));
  
  tmpccer = TIMx->CCER;
  /* 設置或復位 CC2NP 位 */
  tmpccer &= CCER_CC2NP_Reset;
  tmpccer |= (uint16_t)(TIM_OCNPolarity << 4);
  /* 寫 TIMx CCER 寄存器 */
  TIMx->CCER = tmpccer;
}

/**
  * @簡述  設置 TIMx 通道3極性.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_OCPolarity: 指定的 OC3 極性
  *                        這個參數可以取下面的值之一:
  *                        TIM_OCPolarity_High: 輸出比較極性高
  *                        TIM_OCPolarity_Low:  輸出比較極性低
  * @返回  沒有
  */
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity)
{
  uint16_t tmpccer = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));
  tmpccer = TIMx->CCER;
  /* 設置或復位 CC3P 位 */
  tmpccer &= CCER_CC3P_Reset;
  tmpccer |= (uint16_t)(TIM_OCPolarity << 8);
  /* 寫 TIMx CCER 寄存器 */
  TIMx->CCER = tmpccer;
}

/**
  * @簡述  配置 TIMx 通道 3N 極性.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_OCNPolarity: 指定 OC3N 極性
  *                         這個參數可以取下面的值之一:
  *                         TIM_OCNPolarity_High: 輸出比較極性高
  *                         TIM_OCNPolarity_Low:  輸出比較極性低
  * @返回  沒有
  */
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity)
{
  uint16_t tmpccer = 0;
 
  /* 檢查參數 */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));
    
  tmpccer = TIMx->CCER;
  /* 設置或復位 CC3NP 位 */
  tmpccer &= CCER_CC3NP_Reset;
  tmpccer |= (uint16_t)(TIM_OCNPolarity << 8);
  /* 寫 TIMx CCER 寄存器 */
  TIMx->CCER = tmpccer;
}

/**
  * @簡述  設置 TIMx 通道4極性.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_OCPolarity: 指定的 OC4 極性
  *                        這個參數可以取下面的值之一:
  *                        TIM_OCPolarity_High: 輸出比較極性高
  *                        TIM_OCPolarity_Low:  輸出比較極性低
  * @返回  沒有
  */
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity)
{
  uint16_t tmpccer = 0;
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));
  tmpccer = TIMx->CCER;
  /* 設置或復位 CC4P 位 */
  tmpccer &= CCER_CC4P_Reset;
  tmpccer |= (uint16_t)(TIM_OCPolarity << 12);
  /* 寫 TIMx CCER 寄存器 */
  TIMx->CCER = tmpccer;
}

/**
  * @簡述  使能或失能 TIM 捕獲比較通道 x.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_Channel: 指定的 TIM 通道
  *          這個參數可以取下面的值之一:
  *          TIM_Channel_1: TIM 通道 1
  *          TIM_Channel_2: TIM 通道 2
  *          TIM_Channel_3: TIM 通道 3
  *          TIM_Channel_4: TIM 通道 4
  * @參數  TIM_CCx: 指定 TIM 通道 CCxE 位的新狀態.
  *                 這個參數可以是: TIM_CCx_Enable 或 TIM_CCx_Disable. 
  * @返回  沒有
  */
void TIM_CCxCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCx)
{
  uint16_t tmp = 0;

  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_CHANNEL(TIM_Channel));
  assert_param(IS_TIM_CCX(TIM_CCx));

  tmp = CCER_CCE_Set << TIM_Channel;

  /* 復位 CCxE 位 */
  TIMx->CCER &= (uint16_t)~ tmp;

  /* 設置或復位 CCxE 位 */ 
  TIMx->CCER |=  (uint16_t)(TIM_CCx << TIM_Channel);
}

/**
  * @簡述  使能或失能 TIM 捕獲比較通道 xN.
  * @參數  TIMx: 此處x可以是1到8以選擇外設.
  * @參數  TIM_Channel: 指定 TIM 通道
  *          這個參數可以取下面的值之一:
  *          TIM_Channel_1: TIM 通道 1
  *          TIM_Channel_2: TIM 通道 2
  *          TIM_Channel_3: TIM 通道 3
  * @參數  TIM_CCxN: 指定 TIM 通道 CCxNE 位的新狀態.
  *                  這個參數可以是: TIM_CCxN_Enable 或 TIM_CCxN_Disable. 
  * @返回  沒有
  */
void TIM_CCxNCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCxN)
{
  uint16_t tmp = 0;

  /* 檢查參數 */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_TIM_COMPLEMENTARY_CHANNEL(TIM_Channel));
  assert_param(IS_TIM_CCXN(TIM_CCxN));

  tmp = CCER_CCNE_Set << TIM_Channel;

  /* 復位 CCxNE 位 */
  TIMx->CCER &= (uint16_t) ~tmp;

  /* 設置或復位 CCxNE 位 */ 
  TIMx->CCER |=  (uint16_t)(TIM_CCxN << TIM_Channel);
}

/**
  * @簡述  選擇 TIM 輸出比較模式.
  * @註解   在改變輸出比較模式之前，該函數失能選擇的通道.
  *         用戶需要使用 TIM1_CCxCmd 和 TIM1_CCxNCmd 函數使能通道.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_Channel: 指定的 TIM 通道
  *          這個參數可以取下面的值之一:
  *          TIM_Channel_1: TIM 通道 1
  *          TIM_Channel_2: TIM 通道 2
  *          TIM_Channel_3: TIM 通道 3
  *          TIM_Channel_4: TIM 通道 4
  * @參數  TIM_OCMode: 指定 TIM 輸出比較模式.
  *          這個參數可以取下面的值之一:
  *          TIM_OCMode_Timing
  *          TIM_OCMode_Active
  *          TIM_OCMode_Toggle
  *          TIM_OCMode_PWM1
  *          TIM_OCMode_PWM2
  *          TIM_ForcedAction_Active
  *          TIM_ForcedAction_InActive
  * @返回  沒有
  */
void TIM_SelectOCxM(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_OCMode)
{
  uint32_t tmp = 0;
  uint16_t tmp1 = 0;

  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_CHANNEL(TIM_Channel));
  assert_param(IS_TIM_OCM(TIM_OCMode));

  tmp = (uint32_t) TIMx;
  tmp += CCMR_Offset;

  tmp1 = CCER_CCE_Set << (uint16_t)TIM_Channel;

  /* 失能通道: 復位 CCxE 位 */
  TIMx->CCER &= (uint16_t) ~tmp1;

  if((TIM_Channel == TIM_Channel_1) ||(TIM_Channel == TIM_Channel_3))
  {
    tmp += (TIM_Channel>>1);

    /* 復位 OCxM 位，在 CCMRx 寄存器裡 */
    *(__IO uint32_t *) tmp &= CCMR_OC13M_Mask;
   
    /* 配置 OCxM 位，在 CCMRx 寄存器裡 */
    *(__IO uint32_t *) tmp |= TIM_OCMode;
  }
  else
  {
    tmp += (uint16_t)(TIM_Channel - (uint16_t)4)>> (uint16_t)1;

    /* 復位 OCxM 位，在 CCMRx 寄存器裡 */
    *(__IO uint32_t *) tmp &= CCMR_OC24M_Mask;
    
    /* 配置 OCxM 位，在 CCMRx 寄存器裡 */
    *(__IO uint32_t *) tmp |= (uint16_t)(TIM_OCMode << 8);
  }
}

/**
  * @簡述  使能或者失能 TIM 更新事件.
  * @參數  TIMx: 此處x可以是1到8以選擇外設.
  * @參數  NewState: TIM1_CR1寄存器UDIS位的新狀態
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void TIM_UpdateDisableConfig(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 設置更新失能位 */
    TIMx->CR1 |= CR1_UDIS_Set;
  }
  else
  {
    /* 復位更新失能位 */
    TIMx->CR1 &= CR1_UDIS_Reset;
  }
}

/**
  * @簡述  配置 TIMx 更新請求源.
  * @參數  TIMx: 此處x可以是1到8以選擇外設.
  * @參數  TIM_UpdateSource: 指定更新來源.
  *          這個參數可以取下面的值之一:
  *          TIM_UpdateSource_Regular: 生成重複的脈衝：在更新事件時計數器不停止.
  *          TIM_UpdateSource_Global:  生成單一的脈衝：計數器在下一個更新事件停止.
  * @返回  沒有
  */
void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, uint16_t TIM_UpdateSource)
{
  /* 檢查參數 */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_UPDATE_SOURCE(TIM_UpdateSource));
  if (TIM_UpdateSource != TIM_UpdateSource_Global)
  {
    /* 設置 URS 位 */
    TIMx->CR1 |= CR1_URS_Set;
  }
  else
  {
    /* 復位 URS 位 */
    TIMx->CR1 &= CR1_URS_Reset;
  }
}

/**
  * @簡述  使能或者失能 TIM 霍爾傳感器接口.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  NewState: 霍爾感應器的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 設置 TI1S 位 */
    TIMx->CR2 |= CR2_TI1S_Set;
  }
  else
  {
    /* 復位 TI1S 位 */
    TIMx->CR2 &= CR2_TI1S_Reset;
  }
}

/**
  * @簡述  設置 TIM 單脈衝模式.
  * @參數  TIMx: 此處x可以是1到8以選擇外設.
  * @參數  TIM_OPMode: 指定 OPM 模式.
  *                    這個參數可以取下面的值之一:
  *                    TIM_OPMode_Single
  *                    TIM_OPMode_Repetitive
  * @返回  沒有
  */
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, uint16_t TIM_OPMode)
{
  /* 檢查參數 */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_OPM_MODE(TIM_OPMode));
  /* 復位 OPM 位 */
  TIMx->CR1 &= CR1_OPM_Reset;
  /* 配置 OPM 模式 */
  TIMx->CR1 |= TIM_OPMode;
}

/**
  * @簡述  選擇 TIM 觸發輸出模式.
  * @參數  TIMx: 此處x可以是1到8以選擇外設.
  * @參數  TIM_TRGOSource: 指定的觸發輸出模式.
  *                        這個參數可以是下面的值:
  *
  *  - 對於所有的 TIMx
  *          TIM_TRGOSource_Reset:  使用寄存器TIM1_EGR的UG位作為觸發輸出 (TRGO).
  *          TIM_TRGOSource_Enable: 使用計數器使能CEN作為觸發輸出 (TRGO).
  *          TIM_TRGOSource_Update: 使用更新事件作為觸發輸出 (TRGO).
  *
  *  - 對於所有的 TIMx 除了 TIM6 和 TIM7
  *          TIM_TRGOSource_OC1:    一旦捕獲或者比較匹配發生，當標誌位CC1F被設置時觸發輸出發送一個肯定脈衝 (TRGO).
  *          TIM_TRGOSource_OC1Ref: 使用 OC1REF 作為觸發輸出 (TRGO).
  *          TIM_TRGOSource_OC2Ref: 使用 OC2REF 作為觸發輸出 (TRGO).
  *          TIM_TRGOSource_OC3Ref: 使用 OC3REF 作為觸發輸出 (TRGO).
  *          TIM_TRGOSource_OC4Ref: 使用 OC4REF 作為觸發輸出 (TRGO).
  *
  * @返回  沒有
  */
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_TRGOSource)
{
  /* 檢查參數 */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_TRGO_SOURCE(TIM_TRGOSource));
  /* 復位 MMS 位 */
  TIMx->CR2 &= CR2_MMS_Mask;
  /* 選擇 TRGO 的來源 */
  TIMx->CR2 |=  TIM_TRGOSource;
}

/**
  * @簡述  選擇 TIMx 從模式.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_SlaveMode: 指定定時器從模式.
  *          這個參數可以取下面的值之一:
  *          TIM_SlaveMode_Reset:     選中觸發信號 (TRGI) 的上升沿重初始化計數器並觸發寄存器的更新.
  *          TIM_SlaveMode_Gated:     當觸發信號 (TRGI) 為高電平計數器時鐘使能.
  *          TIM_SlaveMode_Trigger:   計數器在觸發 (TRGI) 的上升沿開始.
  *          TIM_SlaveMode_External1: 選中觸發 (TRGI) 的上升沿作為計數器時鐘.
  * @返回  沒有
  */
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_SlaveMode)
{
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_SLAVE_MODE(TIM_SlaveMode));
  /* 復位 SMS 位 */
  TIMx->SMCR &= SMCR_SMS_Mask;
  /* 選擇從模式 */
  TIMx->SMCR |= TIM_SlaveMode;
}

/**
  * @簡述  設置或復位 TIMx 主/從模式.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_MasterSlaveMode: 定時器主/從模式.
  *          這個參數可以取下面的值之一:
  *          TIM_MasterSlaveMode_Enable:  主/從模式使能.
  *          TIM_MasterSlaveMode_Disable: 主/從模式失能
  * @返回  沒有
  */
void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_MasterSlaveMode)
{
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_MSM_STATE(TIM_MasterSlaveMode));
  /* 復位 MSM 位 */
  TIMx->SMCR &= SMCR_MSM_Reset;
  
  /* 設置或復位 MSM 位 */
  TIMx->SMCR |= TIM_MasterSlaveMode;
}

/**
  * @簡述  設置 TIMx 計數寄存器的值
  * @參數  TIMx: 此處x可以是1到8以選擇外設.
  * @參數  Counter: 指定計數寄存器的新值.
  * @返回  沒有
  */
void TIM_SetCounter(TIM_TypeDef* TIMx, uint16_t Counter)
{
  /* 檢查參數 */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  /* 設置計數寄存器的值 */
  TIMx->CNT = Counter;
}

/**
  * @簡述  設置 TIMx 自動重裝載寄存器值
  * @參數  TIMx: 此處x可以是1到8以選擇外設.
  * @參數  Autoreload: 指定自動重裝載寄存器新值.
  * @返回  沒有
  */
void TIM_SetAutoreload(TIM_TypeDef* TIMx, uint16_t Autoreload)
{
  /* 檢查參數 */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  /* 設置自動重裝載寄存器值 */
  TIMx->ARR = Autoreload;
}

/**
  * @簡述  設置 TIMx 捕獲比較1寄存器值
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  Compare1: 捕獲比較1寄存器新值.
  * @返回  沒有
  */
void TIM_SetCompare1(TIM_TypeDef* TIMx, uint16_t Compare1)
{
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  /* 設置捕獲比較1寄存器值 */
  TIMx->CCR1 = Compare1;
}

/**
  * @簡述  設置 TIMx 捕獲比較2寄存器值
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  Compare2: 捕獲比較2寄存器新值.
  * @返回  沒有
  */
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint16_t Compare2)
{
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  /* 設置捕獲比較2寄存器值 */
  TIMx->CCR2 = Compare2;
}

/**
  * @簡述  設置 TIMx 捕獲比較3寄存器值
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  Compare3: 捕獲比較3寄存器新值.
  * @返回  沒有
  */
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint16_t Compare3)
{
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  /* 設置捕獲比較3寄存器值 */
  TIMx->CCR3 = Compare3;
}

/**
  * @簡述  設置 TIMx 捕獲比較4寄存器值
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  Compare4: 捕獲比較4寄存器新值.
  * @返回  沒有
  */
void TIM_SetCompare4(TIM_TypeDef* TIMx, uint16_t Compare4)
{
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  /* 設置捕獲比較4寄存器值 */
  TIMx->CCR4 = Compare4;
}

/**
  * @簡述  設置 TIMx 輸入捕獲1預分頻.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_ICPSC: 輸入捕獲1預分頻的新值.
  *          這個參數可以取下面的值之一:
  *          TIM_ICPSC_DIV1: 沒有預分頻數
  *          TIM_ICPSC_DIV2: 每2次事件TIM捕獲執行一次
  *          TIM_ICPSC_DIV4: 每4次事件TIM捕獲執行一次
  *          TIM_ICPSC_DIV8: 每8次事件TIM捕獲執行一次
  * @返回  沒有
  */
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC)
{
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));
  /* 復位 IC1PSC 位 */
  TIMx->CCMR1 &= CCMR_IC13PSC_Mask;
  /* 設置 IC1PSC 的值 */
  TIMx->CCMR1 |= TIM_ICPSC;
}

/**
  * @簡述  設置 TIMx 輸入捕獲2預分頻.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_ICPSC: 輸入捕獲2預分頻的新值.
  *          這個參數可以取下面的值之一:
  *          TIM_ICPSC_DIV1: 沒有預分頻數
  *          TIM_ICPSC_DIV2: 每2次事件TIM捕獲執行一次
  *          TIM_ICPSC_DIV4: 每4次事件TIM捕獲執行一次
  *          TIM_ICPSC_DIV8: 每8次事件TIM捕獲執行一次
  * @返回  沒有
  */
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC)
{
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));
  /* 復位 IC2PSC 位 */
  TIMx->CCMR1 &= CCMR_IC24PSC_Mask;
  /* 設置 IC2PSC 的值 */
  TIMx->CCMR1 |= (uint16_t)(TIM_ICPSC << 8);
}

/**
  * @簡述  設置 TIMx 輸入捕獲3預分頻.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_ICPSC: 輸入捕獲3預分頻的新值.
  *          這個參數可以取下面的值之一:
  *          TIM_ICPSC_DIV1: 沒有預分頻數
  *          TIM_ICPSC_DIV2: 每2次事件TIM捕獲執行一次
  *          TIM_ICPSC_DIV4: 每4次事件TIM捕獲執行一次
  *          TIM_ICPSC_DIV8: 每8次事件TIM捕獲執行一次
  * @返回  沒有
  */
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC)
{
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));
  /* 復位 IC3PSC 位 */
  TIMx->CCMR2 &= CCMR_IC13PSC_Mask;
  /* 設置 IC3PSC 的值 */
  TIMx->CCMR2 |= TIM_ICPSC;
}

/**
  * @簡述  設置 TIMx 輸入捕獲4預分頻.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_ICPSC: 輸入捕獲4預分頻的新值.
  *          這個參數可以取下面的值之一:
  *          TIM_ICPSC_DIV1: 沒有預分頻數
  *          TIM_ICPSC_DIV2: 每2次事件TIM捕獲執行一次
  *          TIM_ICPSC_DIV4: 每4次事件TIM捕獲執行一次
  *          TIM_ICPSC_DIV8: 每8次事件TIM捕獲執行一次
  * @返回  沒有
  */
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC)
{  
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));
  /* 復位 IC4PSC 位 */
  TIMx->CCMR2 &= CCMR_IC24PSC_Mask;
  /* 設置 IC4PSC 的值 */
  TIMx->CCMR2 |= (uint16_t)(TIM_ICPSC << 8);
}

/**
  * @簡述  設置 TIMx 的時鐘分割值.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_CKD: 時鐘分割值.
  *          這個參數可以取下面的值之一:
  *          TIM_CKD_DIV1: TDTS = Tck_tim
  *          TIM_CKD_DIV2: TDTS = 2*Tck_tim
  *          TIM_CKD_DIV4: TDTS = 4*Tck_tim
  * @返回  沒有
  */
void TIM_SetClockDivision(TIM_TypeDef* TIMx, uint16_t TIM_CKD)
{
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_CKD_DIV(TIM_CKD));
  /* 復位 CKD 位 */
  TIMx->CR1 &= CR1_CKD_Mask;
  /* 設置 CKD 的值 */
  TIMx->CR1 |= TIM_CKD;
}

/**
  * @簡述  獲得 TIMx 輸入捕獲1的值.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @返回  獲得輸入捕獲1的值.
  */
uint16_t TIM_GetCapture1(TIM_TypeDef* TIMx)
{
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  /* 獲得輸入捕獲1的值 */
  return TIMx->CCR1;
}

/**
  * @簡述  獲得 TIMx 輸入捕獲2的值.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @返回  獲得輸入捕獲2的值.
  */
uint16_t TIM_GetCapture2(TIM_TypeDef* TIMx)
{
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  /* 獲得輸入捕獲2的值 */
  return TIMx->CCR2;
}

/**
  * @簡述  獲得 TIMx 輸入捕獲3的值.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @返回  獲得輸入捕獲3的值.
  */
uint16_t TIM_GetCapture3(TIM_TypeDef* TIMx)
{
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx)); 
  /* 獲得輸入捕獲3的值 */
  return TIMx->CCR3;
}

/**
  * @簡述  獲得 TIMx 輸入捕獲4的值.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @返回  獲得輸入捕獲4的值.
  */
uint16_t TIM_GetCapture4(TIM_TypeDef* TIMx)
{
  /* 檢查參數 */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  /* 獲得輸入捕獲4的值 */
  return TIMx->CCR4;
}

/**
  * @簡述  獲得 TIMx 計數器的值.
  * @參數  TIMx: 此處x可以是1到8以選擇外設.
  * @返回  計數器的值.
  */
uint16_t TIM_GetCounter(TIM_TypeDef* TIMx)
{
  /* 檢查參數 */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  /* 獲得計數器的值 */
  return TIMx->CNT;
}

/**
  * @簡述  獲得 TIMx 預分頻值.
  * @參數  TIMx: 此處x可以是1到8以選擇外設.
  * @返回  預分頻的值.
  */
uint16_t TIM_GetPrescaler(TIM_TypeDef* TIMx)
{
  /* 檢查參數 */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  /* 獲得預分頻的值 */
  return TIMx->PSC;
}

/**
  * @簡述  檢查指定的 TIM 標誌位設置與否.
  * @參數  TIMx: 此處x可以是1到8以選擇外設.
  * @參數  TIM_FLAG: 待檢查的 TIM 標誌位.
  *          這個參數可以取下面的值之一:
  *          TIM_FLAG_Update: TIM 更新標誌
  *          TIM_FLAG_CC1: TIM 捕獲/比較 1 標誌位
  *          TIM_FLAG_CC2: TIM 捕獲/比較 2 標誌位
  *          TIM_FLAG_CC3: TIM 捕獲/比較 3 標誌位
  *          TIM_FLAG_CC4: TIM 捕獲/比較 4 標誌位
  *          TIM_FLAG_COM: TIM Com標誌
  *          TIM_FLAG_Trigger: TIM 觸發標誌位
  *          TIM_FLAG_Break: TIM 休息標誌
  *          TIM_FLAG_CC1OF: TIM 捕獲/比較 1 溢出標誌位
  *          TIM_FLAG_CC2OF: TIM 捕獲/比較 2 溢出標誌位
  *          TIM_FLAG_CC3OF: TIM 捕獲/比較 3 溢出標誌位
  *          TIM_FLAG_CC4OF: TIM 捕獲/比較 4 溢出標誌位
  * @註解
  *   - TIM6 和 TIM7 僅僅有一個更新中斷. 
  *   - TIM_FLAG_COM 和 TIM_FLAG_Break 僅僅可以和 TIM1 和 TIM8 一起使用.    
  * @返回  TIM_FLAG 的新狀態(SET 或 RESET).
  */
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, uint16_t TIM_FLAG)
{ 
  ITStatus bitstatus = RESET;  
  /* 檢查參數 */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_GET_FLAG(TIM_FLAG));
  
  if ((TIMx->SR & TIM_FLAG) != (uint16_t)RESET)
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
  * @簡述  清除 TIMx 的待處理標誌位.
  * @參數  TIMx: 此處x可以是1到8以選擇外設.
  * @參數  TIM_FLAG: 用於清除的標記.
  *          這個參數可以是下面值的任意組合:
  *          TIM_FLAG_Update: TIM 更新標誌
  *          TIM_FLAG_CC1: TIM 捕獲/比較 1 標誌位
  *          TIM_FLAG_CC2: TIM 捕獲/比較 2 標誌位
  *          TIM_FLAG_CC3: TIM 捕獲/比較 3 標誌位
  *          TIM_FLAG_CC4: TIM 捕獲/比較 4 標誌位
  *          TIM_FLAG_COM: TIM Com標誌
  *          TIM_FLAG_Trigger: TIM 觸發標誌位
  *          TIM_FLAG_Break: TIM 中斷標誌
  *          TIM_FLAG_CC1OF: TIM 捕獲/比較 1 溢出標誌位
  *          TIM_FLAG_CC2OF: TIM 捕獲/比較 2 溢出標誌位
  *          TIM_FLAG_CC3OF: TIM 捕獲/比較 3 溢出標誌位
  *          TIM_FLAG_CC4OF: TIM 捕獲/比較 4 溢出標誌位
  * @註解
  *   - TIM6 和 TIM7 僅僅有一個更新中斷. 
  *   - TIM_FLAG_COM 和 TIM_FLAG_Break 僅僅可以和 TIM1 和 TIM8 一起使用.    
  * @返回  沒有.
  */
void TIM_ClearFlag(TIM_TypeDef* TIMx, uint16_t TIM_FLAG)
{  
  /* 檢查參數 */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_CLEAR_FLAG(TIM_FLAG));
   
  /* 清除標誌位 */
  TIMx->SR = (uint16_t)~TIM_FLAG;
}

/**
  * @簡述  檢查指定的 TIM 中斷發生與否.
  * @參數  TIMx: 此處x可以是1到8以選擇外設.
  * @參數  TIM_IT: 待檢查的 TIM 中斷源.
  *          這個參數可以取下面的值之一:
  *          TIM_IT_Update: TIM 更新中斷源
  *          TIM_IT_CC1: TIM 捕獲/比較 1 中斷源
  *          TIM_IT_CC2: TIM 捕獲/比較 2 中斷源
  *          TIM_IT_CC3: TIM 捕獲/比較 3 中斷源
  *          TIM_IT_CC4: TIM 捕獲/比較 4 中斷源
  *          TIM_IT_COM: TIM Com 中斷源
  *          TIM_IT_Trigger: TIM 觸發中斷源
  *          TIM_IT_Break: TIM 休息中斷源
  * @註解
  *   - TIM6 和 TIM7 僅僅有一個更新中斷. 
  *   - TIM_FLAG_COM 和 TIM_FLAG_Break 僅僅可以和 TIM1 和 TIM8 一起使用.   
  * @返回  TIM_IT 的新狀態(SET 或 RESET).
  */
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint16_t TIM_IT)
{
  ITStatus bitstatus = RESET;  
  uint16_t itstatus = 0x0, itenable = 0x0;
  /* 檢查參數 */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_GET_IT(TIM_IT));
   
  itstatus = TIMx->SR & TIM_IT;
  
  itenable = TIMx->DIER & TIM_IT;
  if ((itstatus != (uint16_t)RESET) && (itenable != (uint16_t)RESET))
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
  * @簡述  清除 TIMx 的中斷待處理位.
  * @參數  TIMx: 此處x可以是1到8以選擇外設.
  * @參數  TIM_IT: 指定中斷待處理位.
  *          這個參數可以是下面值的任意組合:
  *          TIM_IT_Update: TIM 更新中斷源
  *          TIM_IT_CC1: TIM 捕獲/比較 1 中斷源
  *          TIM_IT_CC2: TIM 捕獲/比較 2 中斷源
  *          TIM_IT_CC3: TIM 捕獲/比較 3 中斷源
  *          TIM_IT_CC4: TIM 捕獲/比較 4 中斷源
  *          TIM_IT_COM: TIM Com 中斷源
  *          TIM_IT_Trigger: TIM 觸發中斷源
  *          TIM_IT_Break: TIM 休息中斷源
  * @註解
  *   - TIM6 和 TIM7 僅僅有一個更新中斷. 
  *   - TIM_FLAG_COM 和 TIM_FLAG_Break 僅僅可以和 TIM1 和 TIM8 一起使用.  
  * @返回  沒有
  */
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT)
{
  /* 檢查參數 */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_IT(TIM_IT));
  /* 清除 TIMx 的中斷待處理位 */
  TIMx->SR = (uint16_t)~TIM_IT;
}

/**
  * @簡述  配置 TI1 作為輸入.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_ICPolarity : 輸入極性.
  *          這個參數可以取下面的值之一:
  *          TIM_ICPolarity_Rising
  *          TIM_ICPolarity_Falling
  * @參數  TIM_ICSelection: 使用指定的輸入.
  *          這個參數可以取下面的值之一:
  *          TIM_ICSelection_DirectTI:   選擇TIM 輸入1連接IC1.
  *          TIM_ICSelection_IndirectTI: 選擇TIM 輸入1連接IC2.
  *          TIM_ICSelection_TRC:        選擇TIM 輸入1連接TRC.
  * @參數  TIM_ICFilter: 指定的輸入捕獲濾波器.
  *                      這個參數的值必須在 0x00 和 0x0F之間.
  * @返回  沒有
  */
static void TI1_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter)
{
  uint16_t tmpccmr1 = 0, tmpccer = 0;
  /* 失能通道 1: 復位 CC1E 位 */
  TIMx->CCER &= CCER_CC1E_Reset;
  tmpccmr1 = TIMx->CCMR1;
  tmpccer = TIMx->CCER;
  /* 選擇輸入和濾波器 */
  tmpccmr1 &= CCMR_CC13S_Mask & CCMR_IC13F_Mask;
  tmpccmr1 |= (uint16_t)(TIM_ICSelection | (uint16_t)(TIM_ICFilter << (uint16_t)4));
  /* 選擇極性和置位CC1E */
  tmpccer &= CCER_CC1P_Reset;
  tmpccer |= (uint16_t)(TIM_ICPolarity | (uint16_t)CCER_CC1E_Set);
  /* 寫TIMx CCMR1和CCER寄存器 */
  TIMx->CCMR1 = tmpccmr1;
  TIMx->CCER = tmpccer;
}

/**
  * @簡述  配置 TI2 作為輸入.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_ICPolarity : 輸入極性.
  *          這個參數可以取下面的值之一:
  *          TIM_ICPolarity_Rising
  *          TIM_ICPolarity_Falling
  * @參數  TIM_ICSelection: 使用指定的輸入.
  *          這個參數可以取下面的值之一:
  *          TIM_ICSelection_DirectTI:   選擇TIM 輸入2連接IC2.
  *          TIM_ICSelection_IndirectTI: 選擇TIM 輸入2連接IC1.
  *          TIM_ICSelection_TRC:        選擇TIM 輸入2連接TRC.
  * @參數  TIM_ICFilter: 指定的輸入捕獲濾波器.
  *                      這個參數的值必須在 0x00 和 0x0F之間.
  * @返回  沒有
  */
static void TI2_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter)
{
  uint16_t tmpccmr1 = 0, tmpccer = 0, tmp = 0;
  /* 失能通道 2: 復位 CC2E 位 */
  TIMx->CCER &= CCER_CC2E_Reset;
  tmpccmr1 = TIMx->CCMR1;
  tmpccer = TIMx->CCER;
  tmp = (uint16_t)(TIM_ICPolarity << 4);
  /* 選擇輸入和濾波器 */
  tmpccmr1 &= CCMR_CC24S_Mask & CCMR_IC24F_Mask;
  tmpccmr1 |= (uint16_t)(TIM_ICFilter << 12);
  tmpccmr1 |= (uint16_t)(TIM_ICSelection << 8);
  /* 選擇極性和置位CC2E */
  tmpccer &= CCER_CC2P_Reset;
  tmpccer |=  (uint16_t)(tmp | (uint16_t)CCER_CC2E_Set);
  /* 寫TIMx CCMR1和CCER寄存器 */
  TIMx->CCMR1 = tmpccmr1 ;
  TIMx->CCER = tmpccer;
}

/**
  * @簡述  配置 TI3 作為輸入.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_ICPolarity : 輸入極性.
  *          這個參數可以取下面的值之一:
  *          TIM_ICPolarity_Rising
  *          TIM_ICPolarity_Falling
  * @參數  TIM_ICSelection: 使用指定的輸入.
  *          這個參數可以取下面的值之一:
  *          TIM_ICSelection_DirectTI:   選擇TIM 輸入3連接IC3.
  *          TIM_ICSelection_IndirectTI: 選擇TIM 輸入3連接IC4.
  *          TIM_ICSelection_TRC:        選擇TIM 輸入3連接TRC.
  * @參數  TIM_ICFilter: 指定的輸入捕獲濾波器.
  *                      這個參數的值必須在 0x00 和 0x0F之間.
  * @返回  沒有
  */
static void TI3_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter)
{
  uint16_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;
  /* 失能通道 3: 復位 CC3E 位 */
  TIMx->CCER &= CCER_CC3E_Reset;
  tmpccmr2 = TIMx->CCMR2;
  tmpccer = TIMx->CCER;
  tmp = (uint16_t)(TIM_ICPolarity << 8);
  /* 選擇輸入和濾波器 */
  tmpccmr2 &= CCMR_CC13S_Mask & CCMR_IC13F_Mask;
  tmpccmr2 |= (uint16_t)(TIM_ICSelection | (uint16_t)(TIM_ICFilter << (uint16_t)4));
  /* 選擇極性和置位CC3E */
  tmpccer &= CCER_CC3P_Reset;
  tmpccer |= (uint16_t)(tmp | (uint16_t)CCER_CC3E_Set);
  /* 寫TIMx CCMR2和CCER寄存器 */
  TIMx->CCMR2 = tmpccmr2;
  TIMx->CCER = tmpccer;
}

/**
  * @簡述  配置 TI4 作為輸入.
  * @參數  TIMx: 此處x可以是1,2,3,4,5或8以選擇外設.
  * @參數  TIM_ICPolarity : 輸入極性.
  *          這個參數可以取下面的值之一:
  *          TIM_ICPolarity_Rising
  *          TIM_ICPolarity_Falling
  * @參數  TIM_ICSelection: 使用指定的輸入.
  *          這個參數可以取下面的值之一:
  *          TIM_ICSelection_DirectTI:   選擇TIM 輸入3連接IC4.
  *          TIM_ICSelection_IndirectTI: 選擇TIM 輸入3連接IC3.
  *          TIM_ICSelection_TRC:        選擇TIM 輸入3連接TRC.
  * @參數  TIM_ICFilter: 指定的輸入捕獲濾波器.
  *                      這個參數的值必須在 0x00 和 0x0F之間.
  * @返回  沒有
  */
static void TI4_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter)
{
  uint16_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;

  /* 失能通道 4: 復位 CC4E 位 */
  TIMx->CCER &= CCER_CC4E_Reset;
  tmpccmr2 = TIMx->CCMR2;
  tmpccer = TIMx->CCER;
  tmp = (uint16_t)(TIM_ICPolarity << 12);

  /* 選擇輸入和設置過濾器 */
  tmpccmr2 &= CCMR_CC24S_Mask & CCMR_IC24F_Mask;
  tmpccmr2 |= (uint16_t)(TIM_ICSelection << 8);
  tmpccmr2 |= (uint16_t)(TIM_ICFilter << 12);

  /* 選擇極性和置位CC4E */
  tmpccer &= CCER_CC4P_Reset;
  tmpccer |= (uint16_t)(tmp | (uint16_t)CCER_CC4E_Set);
  /* 寫TIMx CCMR2和CCER寄存器 */
  TIMx->CCMR2 = tmpccmr2;
  TIMx->CCER = tmpccer ;
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
