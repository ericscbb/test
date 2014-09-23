/**
  ******************************************************************************
  * @文件    stm32f10x_usart.c
  * @作者    MCD 應用程序組
  * @版本    V3.1.0
  * @日期    06/19/2009
  * @簡述    這個文件 提供所有 USART 固件函數.
  * @翻譯    ANSON/sweet1985 Email:airanson110@126.com
  * @日期    14/07/2009
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
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"

/* 自用類型 --------------------------------------------------------------*/
/* 自用定義 --------------------------------------------------------------*/

#define CR1_UE_Set                ((uint16_t)0x2000)  /*!< USART Enable Mask */
#define CR1_UE_Reset              ((uint16_t)0xDFFF)  /*!< USART Disable Mask */

#define CR1_WAKE_Mask             ((uint16_t)0xF7FF)  /*!< USART WakeUp Method Mask */

#define CR1_RWU_Set               ((uint16_t)0x0002)  /*!< USART mute mode Enable Mask */
#define CR1_RWU_Reset             ((uint16_t)0xFFFD)  /*!< USART mute mode Enable Mask */
#define CR1_SBK_Set               ((uint16_t)0x0001)  /*!< USART Break Character send Mask */
#define CR1_CLEAR_Mask            ((uint16_t)0xE9F3)  /*!< USART CR1 Mask */
#define CR2_Address_Mask          ((uint16_t)0xFFF0)  /*!< USART address Mask */

#define CR2_LINEN_Set              ((uint16_t)0x4000)  /*!< USART LIN Enable Mask */
#define CR2_LINEN_Reset            ((uint16_t)0xBFFF)  /*!< USART LIN Disable Mask */

#define CR2_LBDL_Mask             ((uint16_t)0xFFDF)  /*!< USART LIN Break detection Mask */
#define CR2_STOP_CLEAR_Mask       ((uint16_t)0xCFFF)  /*!< USART CR2 STOP Bits Mask */
#define CR2_CLOCK_CLEAR_Mask      ((uint16_t)0xF0FF)  /*!< USART CR2 Clock Mask */

#define CR3_SCEN_Set              ((uint16_t)0x0020)  /*!< USART SC Enable Mask */
#define CR3_SCEN_Reset            ((uint16_t)0xFFDF)  /*!< USART SC Disable Mask */

#define CR3_NACK_Set              ((uint16_t)0x0010)  /*!< USART SC NACK Enable Mask */
#define CR3_NACK_Reset            ((uint16_t)0xFFEF)  /*!< USART SC NACK Disable Mask */

#define CR3_HDSEL_Set             ((uint16_t)0x0008)  /*!< USART Half-Duplex Enable Mask */
#define CR3_HDSEL_Reset           ((uint16_t)0xFFF7)  /*!< USART Half-Duplex Disable Mask */

#define CR3_IRLP_Mask             ((uint16_t)0xFFFB)  /*!< USART IrDA LowPower mode Mask */
#define CR3_CLEAR_Mask            ((uint16_t)0xFCFF)  /*!< USART CR3 Mask */

#define CR3_IREN_Set              ((uint16_t)0x0002)  /*!< USART IrDA Enable Mask */
#define CR3_IREN_Reset            ((uint16_t)0xFFFD)  /*!< USART IrDA Disable Mask */
#define GTPR_LSB_Mask             ((uint16_t)0x00FF)  /*!< Guard Time Register LSB Mask */
#define GTPR_MSB_Mask             ((uint16_t)0xFF00)  /*!< Guard Time Register MSB Mask */
#define IT_Mask                   ((uint16_t)0x001F)  /*!< USART Interrupt Mask */

/* 自用宏 -------------------------------------------------------------*/
/* 自用變量 -----------------------------------------------------------*/
/* 自用函數原型 -------------------------------------------------------*/
/* 自用函數 -----------------------------------------------------------*/

/**
  * @簡述  將外設 USARTx 寄存器重設為缺省值.
  * @參數  USARTx: 選擇 USART 外圍設備. 
  *                這個參數可以取下列值之一: USART1, USART2, USART3, UART4 或 UART5.
  * @返回  沒有
  */
void USART_DeInit(USART_TypeDef* USARTx)
{
  /* 檢查參數 */
  assert_param(IS_USART_ALL_PERIPH(USARTx));

  if (USARTx == USART1)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, DISABLE);
  }
  else if (USARTx == USART2)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, DISABLE);
  }
  else if (USARTx == USART3)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, DISABLE);
  }    
  else if (USARTx == UART4)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4, DISABLE);
  }    
  else
  {
    if (USARTx == UART5)
    { 
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5, ENABLE);
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5, DISABLE);
    }
  }
}

/**
  * @簡述  根據 USART_InitStruct 中指定的參數初始化外設 USARTx 寄存器.
  * @參數  USARTx: 選擇 USART 外圍設備. 
  *                這個參數可以取下列值之一: USART1, USART2, USART3, UART4 或 UART5.
  * @參數  USART_InitStruct: 指向結構 USART_InitTypeDef 的指針，包含了外設 USART 的配置信息.
  * @返回  沒有
  */
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct)
{
  uint32_t tmpreg = 0x00, apbclock = 0x00;
  uint32_t integerdivider = 0x00;
  uint32_t fractionaldivider = 0x00;
  uint32_t usartxbase = 0;
  RCC_ClocksTypeDef RCC_ClocksStatus;
  /* 檢查參數 */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_BAUDRATE(USART_InitStruct->USART_BaudRate));  
  assert_param(IS_USART_WORD_LENGTH(USART_InitStruct->USART_WordLength));
  assert_param(IS_USART_STOPBITS(USART_InitStruct->USART_StopBits));
  assert_param(IS_USART_PARITY(USART_InitStruct->USART_Parity));
  assert_param(IS_USART_MODE(USART_InitStruct->USART_Mode));
  assert_param(IS_USART_HARDWARE_FLOW_CONTROL(USART_InitStruct->USART_HardwareFlowControl));
  /* The hardware flow control is available only for USART1, USART2 and USART3 */
  if (USART_InitStruct->USART_HardwareFlowControl != USART_HardwareFlowControl_None)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  }

  usartxbase = (uint32_t)USARTx;

/*---------------------------- USART CR2 Configuration -----------------------*/
  tmpreg = USARTx->CR2;
  /* 清除 STOP[13:12] 位 */
  tmpreg &= CR2_STOP_CLEAR_Mask;
  /* 配置 USART 結束位, 時鐘, 時鐘極性, 時鐘相位 和 末位 ------------*/
  /* 設置 STOP[13:12] 位，按照 USART_StopBits 的值 */
  tmpreg |= (uint32_t)USART_InitStruct->USART_StopBits;
  
  /* 寫 USART CR2 */
  USARTx->CR2 = (uint16_t)tmpreg;

/*---------------------------- USART CR1 Configuration -----------------------*/
  tmpreg = USARTx->CR1;
  /* 清除 M, PCE, PS, TE 和 RE 位 */
  tmpreg &= CR1_CLEAR_Mask;
  /* 配置 USART 字長, 奇偶 和 模式 ----------------------- */
  /* 設置 M   位，按照 USART_WordLength 的值 */
  /* 設置 PCE 和 PS 位，按照 USART_Parity 的值 */
  /* 設置 TE  和 RE 位，按照 USART_Mode 的值 */
  tmpreg |= (uint32_t)USART_InitStruct->USART_WordLength | USART_InitStruct->USART_Parity |
            USART_InitStruct->USART_Mode;
  /* 寫 USART CR1 */
  USARTx->CR1 = (uint16_t)tmpreg;

/*---------------------------- USART CR3 Configuration -----------------------*/  
  tmpreg = USARTx->CR3;
  /* 清除 CTSE 和 RTSE 位 */
  tmpreg &= CR3_CLEAR_Mask;
  /* 配置 USART HFC -------------------------------------------------*/
  /* 設置 CTSE 和 RTSE 位，按照 USART_HardwareFlowControl 的值 */
  tmpreg |= USART_InitStruct->USART_HardwareFlowControl;
  /* 寫 USART CR3 */
  USARTx->CR3 = (uint16_t)tmpreg;

/*---------------------------- USART BRR Configuration -----------------------*/
  /* 配置 USART 波特率 -------------------------------------------*/
  RCC_GetClocksFreq(&RCC_ClocksStatus);
  if (usartxbase == USART1_BASE)
  {
    apbclock = RCC_ClocksStatus.PCLK2_Frequency;
  }
  else
  {
    apbclock = RCC_ClocksStatus.PCLK1_Frequency;
  }
  /* 確定整數部分 */
  integerdivider = ((0x19 * apbclock) / (0x04 * (USART_InitStruct->USART_BaudRate)));
  tmpreg = (integerdivider / 0x64) << 0x04;
  /* 確定分數部分 */
  fractionaldivider = integerdivider - (0x64 * (tmpreg >> 0x04));
  tmpreg |= ((((fractionaldivider * 0x10) + 0x32) / 0x64)) & ((uint8_t)0x0F);
  /* 寫 USART BRR */
  USARTx->BRR = (uint16_t)tmpreg;
}

/**
  * @簡述  把 USART_InitStruct 中的每一個參數按缺省值填入.
  * @參數  USART_InitStruct: 指向結構 USART_InitTypeDef 的指針，待初始化.
  * @返回  沒有
  */
void USART_StructInit(USART_InitTypeDef* USART_InitStruct)
{
  /* USART_InitStruct 結構體的缺省值 */
  USART_InitStruct->USART_BaudRate = 9600;
  USART_InitStruct->USART_WordLength = USART_WordLength_8b;
  USART_InitStruct->USART_StopBits = USART_StopBits_1;
  USART_InitStruct->USART_Parity = USART_Parity_No ;
  USART_InitStruct->USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct->USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
}

/**
  * @簡述  初始化 USARTx 外圍時鐘，按照 USART_ClockInitStruct 內的參數.
  * @參數  USARTx: 這裡x可以取 1, 2, 3 來選擇 USART 外圍設備.
  * @參數  USART_ClockInitStruct: 指向 USART_ClockInitTypeDef 的指針，包含了外設 USART 的配置信息.  
  * @註解  這個智能卡模式不能應用於 UART4 和 UART5.
  * @返回  沒有
  */
void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct)
{
  uint32_t tmpreg = 0x00;
  /* 檢查參數 */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_USART_CLOCK(USART_ClockInitStruct->USART_Clock));
  assert_param(IS_USART_CPOL(USART_ClockInitStruct->USART_CPOL));
  assert_param(IS_USART_CPHA(USART_ClockInitStruct->USART_CPHA));
  assert_param(IS_USART_LASTBIT(USART_ClockInitStruct->USART_LastBit));
  
/*---------------------------- USART CR2 Configuration -----------------------*/
  tmpreg = USARTx->CR2;
  /* 清除 CLKEN, CPOL, CPHA 和 LBCL 位 */
  tmpreg &= CR2_CLOCK_CLEAR_Mask;
  /* 配置 USART Clock, CPOL, CPHA and LastBit ------------*/
  /* 設置 CLKEN 位，按照 USART_Clock 的值 */
  /* 設置 CPOL  位，按照 USART_CPOL 的值 */
  /* 設置 CPHA  位，按照 USART_CPHA 的值 */
  /* 設置 LBCL  位，按照 USART_LastBit 的值 */
  tmpreg |= (uint32_t)USART_ClockInitStruct->USART_Clock | USART_ClockInitStruct->USART_CPOL | 
                 USART_ClockInitStruct->USART_CPHA | USART_ClockInitStruct->USART_LastBit;
  /* 寫 USART CR2 */
  USARTx->CR2 = (uint16_t)tmpreg;
}

/**
  * @簡述  用默認值填充每一個 USART_ClockInitStruct 的成員.
  * @參數  USART_ClockInitStruct: 指向 USART_ClockInitTypeDef 結構的指針，用於初始化.
  * @返回  沒有
  */
void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct)
{
  /* USART_ClockInitStruct 結構體的缺省值 */
  USART_ClockInitStruct->USART_Clock = USART_Clock_Disable;
  USART_ClockInitStruct->USART_CPOL = USART_CPOL_Low;
  USART_ClockInitStruct->USART_CPHA = USART_CPHA_1Edge;
  USART_ClockInitStruct->USART_LastBit = USART_LastBit_Disable;
}

/**
  * @簡述  使能或者失能 USART 外設.
  * @參數  USARTx: 選擇 USART 或者 UART 的外圍設備. 
  *                這個參數可以是下面的值之一 : USART1, USART2, USART3, UART4 或 UART5.
  * @參數  NewState: USARTx 外圍設備的新狀態.
  *                  這個參數可以是: ENABLE or DISABLE.
  * @返回  沒有
  */
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected USART by setting the UE bit in the CR1 register */
    USARTx->CR1 |= CR1_UE_Set;
  }
  else
  {
    /* Disable the selected USART by clearing the UE bit in the CR1 register */
    USARTx->CR1 &= CR1_UE_Reset;
  }
}

/**
  * @簡述  使能或者失能指定的 USART 中斷.
  * @參數  USARTx: 選擇 USART 或者 UART 的外圍設備. 
  *                這個參數可以是下面的值之一 : USART1, USART2, USART3, UART4 or UART5.
  * @參數  USART_IT: 指定要使能或失能的 USART 中斷源.
  *          這個參數可以是下面的值之一 :
  *          USART_IT_CTS:  CTS 改變中斷 (不能應用於 UART4 和 UART5)
  *          USART_IT_LBD:  LIN 間隔偵測中斷
  *          USART_IT_TXE:  傳輸數據寄存器空中斷
  *          USART_IT_TC:   傳輸完成中斷
  *          USART_IT_RXNE: 接收數據寄存器不為空中斷
  *          USART_IT_IDLE: 空閒總線中斷
  *          USART_IT_PE:   奇偶錯誤中斷
  *          USART_IT_ERR:  錯誤中斷(楨錯誤, 噪聲錯誤, 溢出錯誤)
  * @參數  NewState: 指定的 USARTx 中斷的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState)
{
  uint32_t usartreg = 0x00, itpos = 0x00, itmask = 0x00;
  uint32_t usartxbase = 0x00;
  /* 檢查參數 */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CONFIG_IT(USART_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  /* CTS 中斷不能應用於 UART4 和 UART5 */
  if (USART_IT == USART_IT_CTS)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  }   
  
  usartxbase = (uint32_t)USARTx;

  /* 得到 USART 寄存器變址 */
  usartreg = (((uint8_t)USART_IT) >> 0x05);

  /* 得到中斷位置 */
  itpos = USART_IT & IT_Mask;
  itmask = (((uint32_t)0x01) << itpos);
    
  if (usartreg == 0x01) /* The IT is in CR1 register */
  {
    usartxbase += 0x0C;
  }
  else if (usartreg == 0x02) /* The IT is in CR2 register */
  {
    usartxbase += 0x10;
  }
  else /* The IT is in CR3 register */
  {
    usartxbase += 0x14; 
  }
  if (NewState != DISABLE)
  {
    *(__IO uint32_t*)usartxbase  |= itmask;
  }
  else
  {
    *(__IO uint32_t*)usartxbase &= ~itmask;
  }
}

/**
  * @簡述  使能或者失能指定 USART 的 DMA 請求.
  * @參數  USARTx: 選擇 USART 或者 UART 的外圍設備. 
  *                這個參數可以是下面的值之一 : USART1, USART2, USART3 or UART4.  
  * @參數  USART_DMAReq:指定 DMA 請求.
  *          這個參數可以是下面任意值的組合:
  *          USART_DMAReq_Tx: USART DMA 傳輸請求
  *          USART_DMAReq_Rx: USART DMA 接收請求
  * @參數  NewState: DMA 請求源的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @註解  DMA 模式不能應用於 UART5.  
  * @返回  沒有
  */
void USART_DMACmd(USART_TypeDef* USARTx, uint16_t USART_DMAReq, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_USART_1234_PERIPH(USARTx));
  assert_param(IS_USART_DMAREQ(USART_DMAReq));  
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 
  if (NewState != DISABLE)
  {
    /* 通過設置USART CR3 寄存器的DMAT、DMAT位組合,來使能選擇DMA傳輸請求 */
    USARTx->CR3 |= USART_DMAReq;
  }
  else
  {
    /* 通過設置USART CR3 寄存器的DMAT、DMAT位組合,來失能選擇DMA傳輸請求 */
    USARTx->CR3 &= (uint16_t)~USART_DMAReq;
  }
}

/**
  * @簡述  設置 USART 節點的地址.
  * @參數  USARTx: 選擇 USART 或者 UART 的外圍設備. 
  *                這個參數可以是下面的值之一 : USART1, USART2, USART3, UART4 or UART5.
  * @參數  USART_Address: 設置 USART 節點的地址.
  * @返回  沒有
  */ 
void USART_SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address)
{
  /* 檢查參數 */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_ADDRESS(USART_Address)); 
    
  /* 清除 USART 地址 */
  USARTx->CR2 &= CR2_Address_Mask;
  /* 設置 USART 節點的地址 */
  USARTx->CR2 |= USART_Address;
}

/**
  * @簡述  選擇 USART 的喚醒方式.
  * @參數  USARTx: 選擇 USART 或者 UART 的外圍設備. 
  *                這個參數可以是下面的值之一 : USART1, USART2, USART3, UART4 or UART5.
  * @參數  USART_WakeUp: 指定 USART 的喚醒方式.
  *          這個參數可以是下面的值之一 :
  *          USART_WakeUp_IdleLine:    空閒總線喚醒
  *          USART_WakeUp_AddressMark: 地址標記喚醒
  * @返回  沒有
  */
void USART_WakeUpConfig(USART_TypeDef* USARTx, uint16_t USART_WakeUp)
{
  /* 檢查參數 */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_WAKEUP(USART_WakeUp));
  
  USARTx->CR1 &= CR1_WAKE_Mask;
  USARTx->CR1 |= USART_WakeUp;
}

/**
  * @簡述  檢查 USART 是否處於靜默模式.
  * @參數  USARTx: 選擇 USART 或者 UART 的外圍設備. 
  *                這個參數可以是下面的值之一 : USART1, USART2, USART3, UART4 or UART5.
  * @參數  NewState: USART 靜默模式的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void USART_ReceiverWakeUpCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 
  
  if (NewState != DISABLE)
  {
    /* 通過置位CR1寄存器的RWU位使能USART靜音模式 */
    USARTx->CR1 |= CR1_RWU_Set;
  }
  else
  {
    /* 通過清零CR1寄存器的RWU位失能USART靜音模式 */
    USARTx->CR1 &= CR1_RWU_Reset;
  }
}

/**
  * @簡述  設置 USART LIN 中斷檢測長度.
  * @參數  USARTx: 選擇 USART 或者 UART 的外圍設備. 
  *                這個參數可以是下面的值之一 : USART1, USART2, USART3, UART4 或 UART5.
  * @參數  USART_LINBreakDetectLength: LIN 中斷檢測長度.
  *          這個參數可以是下面的值之一 :
  *          USART_LINBreakDetectLength_10b: 10位間斷檢測
  *          USART_LINBreakDetectLength_11b: 11位間斷檢測
  * @返回  沒有
  */
void USART_LINBreakDetectLengthConfig(USART_TypeDef* USARTx, uint16_t USART_LINBreakDetectLength)
{
  /* 檢查參數 */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_LIN_BREAK_DETECT_LENGTH(USART_LINBreakDetectLength));
  
  USARTx->CR2 &= CR2_LBDL_Mask;
  USARTx->CR2 |= USART_LINBreakDetectLength;  
}

/**
  * @簡述  使能或者失能 USARTx 的 LIN 模式.
  * @參數  USARTx: 選擇 USART 或者 UART 的外圍設備. 
  *                這個參數可以是下面的值之一 : USART1, USART2, USART3, UART4 or UART5.
  * @參數  NewState: USART LIN 模式的新狀態.
  *                  這個參數可以是: ENABLE or DISABLE.
  * @返回  沒有
  */
void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* 通過置位CR2寄存器的LINEN位使能LIN模式 */
    USARTx->CR2 |= CR2_LINEN_Set;
  }
  else
  {
    /* 通過清零CR2寄存器的LINEN位失能LIN模式 */
    USARTx->CR2 &= CR2_LINEN_Reset;
  }
}

/**
  * @簡述  通過外設 USARTx 發送單個數據.
  * @參數  USARTx: 選擇 USART 或者 UART 的外圍設備.
  *                這個參數可以是下面的值之一 : USART1, USART2, USART3, UART4 或 UART5.
  * @參數  Data: 要發送的數據.
  * @返回  沒有
  */
void USART_SendData(USART_TypeDef* USARTx, uint16_t Data)
{
  /* 檢查參數 */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DATA(Data)); 
    
  /* 發送數據 */
  USARTx->DR = (Data & (uint16_t)0x01FF);
}

/**
  * @簡述  返回 USARTx 最近接收到的數據.
  * @參數  USARTx: 選擇 USART 或者 UART 的外圍設備.
  *                這個參數可以是下面的值之一 : USART1, USART2, USART3, UART4 或 UART5.
  * @返回  接收數據.
  */
uint16_t USART_ReceiveData(USART_TypeDef* USARTx)
{
  /* 檢查參數 */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  
  /* 接收數據 */
  return (uint16_t)(USARTx->DR & (uint16_t)0x01FF);
}

/**
  * @簡述  發送中斷字.
  * @參數  USARTx: 選擇 USART 或者 UART 的外圍設備. 
  *                這個參數可以是下面的值之一 : USART1, USART2, USART3, UART4 或 UART5.
  * @返回  沒有
  */
void USART_SendBreak(USART_TypeDef* USARTx)
{
  /* 檢查參數 */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  
  /* 發送中斷字 */
  USARTx->CR1 |= CR1_SBK_Set;
}

/**
  * @簡述  設置指定的 USART 保護時間.
  * @參數  USARTx: x可以為1,2或3以選擇USART的外圍設備.
  * @參數  USART_GuardTime: 指定的保護時間.
  * @註解  這個保護時間位不能應用於 UART4 和 UART5.   
  * @返回  沒有
  */
void USART_SetGuardTime(USART_TypeDef* USARTx, uint8_t USART_GuardTime)
{    
  /* 檢查參數 */
  assert_param(IS_USART_123_PERIPH(USARTx));
  
  /* 清除 USART 保護時間 */
  USARTx->GTPR &= GTPR_LSB_Mask;
  /* 設置 USART 保護時間 */
  USARTx->GTPR |= (uint16_t)((uint16_t)USART_GuardTime << 0x08);
}

/**
  * @簡述  設置 USART 時鐘預分頻.
  * @參數  USARTx: 選擇 USART 或者 UART 的外圍設備. 
  *                這個參數可以是下面的值之一 : USART1, USART2, USART3, UART4 or UART5.
  * @參數  USART_Prescaler: 指定預分頻器.  
  * @註解  這個函數是用於 UART4 和 UART5 的 IrDA 模式.
  * @返回  沒有
  */
void USART_SetPrescaler(USART_TypeDef* USARTx, uint8_t USART_Prescaler)
{ 
  /* 檢查參數 */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  
  /* 清除 USART 預分頻器 */
  USARTx->GTPR &= GTPR_MSB_Mask;
  /* 設置 USART 預分頻器 */
  USARTx->GTPR |= USART_Prescaler;
}

/**
  * @簡述  使能或者失能指定 USART 的智能卡模式.
  * @參數  USARTx: x可以為1,2或3以選擇USART的外圍設備.
  * @參數  NewState: USART 智能卡模式的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.     
  * @註解  這個智能卡模式不能應用於 UART4 和 UART5 . 
  * @返回  沒有
  */
void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 通過置位CR3寄存器的SCEN位使能SC模式 */
    USARTx->CR3 |= CR3_SCEN_Set;
  }
  else
  {
    /* 通過清零CR3寄存器的SCEN位失能SC模式 */
    USARTx->CR3 &= CR3_SCEN_Reset;
  }
}

/**
  * @簡述  使能或者失能 NACK 傳輸.
  * @參數  USARTx: x可以為1,2或3以選擇USART的外圍設備. 
  * @參數  NewState: NACK 傳輸的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.  
  * @註解  這個智能卡模式不能應用於 UART4 和 UART5 .
  * @返回  沒有
  */
void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_USART_123_PERIPH(USARTx));  
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 通過置位CR3寄存器的NACK位使能NACK傳輸 */
    USARTx->CR3 |= CR3_NACK_Set;
  }
  else
  {
    /* 通過清零CR3寄存器的NACK位失能NACK傳輸 */
    USARTx->CR3 &= CR3_NACK_Reset;
  }
}

/**
  * @簡述  使能或者失能 USART 半雙工模式.
  * @參數  USARTx: 選擇 USART 或者 UART 的外圍設備. 
  *                這個參數可以是下面的值之一 : USART1, USART2, USART3, UART4 or UART5.
  * @參數  NewState: USART 半雙工模式的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* 通過置位CR3寄存器的HDSEL位使能Half-Duplex模式 */
    USARTx->CR3 |= CR3_HDSEL_Set;
  }
  else
  {
    /* 通過清零CR3寄存器的HDSEL位失能Half-Duplex模式 */
    USARTx->CR3 &= CR3_HDSEL_Reset;
  }
}

/**
  * @簡述  設置 USART IrDA 模式.
  * @參數  USARTx: 選擇 USART 或者 UART 的外圍設備. 
  *                這個參數可以是下面的值之一 : USART1, USART2, USART3, UART4 或 UART5.
  * @參數  USART_IrDAMode: 指定 IrDA 模式.
  *                        這個參數可以是下面的值之一 :
  *                        USART_IrDAMode_LowPower: 低功耗模式
  *                        USART_IrDAMode_Normal  : 正常模式
  * @返回  沒有
  */
void USART_IrDAConfig(USART_TypeDef* USARTx, uint16_t USART_IrDAMode)
{
  /* 檢查參數 */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_IRDA_MODE(USART_IrDAMode));
    
  USARTx->CR3 &= CR3_IRLP_Mask;
  USARTx->CR3 |= USART_IrDAMode;
}

/**
  * @簡述  使能或者失能 USART IrDA 模式.
  * @參數  USARTx: 選擇 USART 或者 UART 的外圍設備.
  *                這個參數可以是下面的值之一 : USART1, USART2, USART3, UART4 或 UART5.
  * @參數  NewState: IrDA 模式的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
    
  if (NewState != DISABLE)
  {
    /* 通過置位CR3寄存器的IREN位使能IrDA模式 */
    USARTx->CR3 |= CR3_IREN_Set;
  }
  else
  {
    /* 通過清零CR3寄存器的IREN位失能IrDA模式 */
    USARTx->CR3 &= CR3_IREN_Reset;
  }
}

/**
  * @簡述  檢查指定的 USART 標誌位設置與否.
  * @參數  USARTx: 選擇 USART 或者 UART 的外圍設備. 
  *                這個參數可以是下面的值之一 : USART1, USART2, USART3, UART4 or UART5.
  * @參數  USART_FLAG: 指定要檢測的標記.
  *          這個參數可以是下面的值之一 :
  *          USART_FLAG_CTS:  CTS 改變標誌 (不能應用於 UART4 和 UART5)
  *          USART_FLAG_LBD:  LIN 間隔偵測標誌
  *          USART_FLAG_TXE:  發送數據寄存器為空標誌
  *          USART_FLAG_TC:   傳輸完成標誌
  *          USART_FLAG_RXNE: 接收數據寄存器不為空標誌
  *          USART_FLAG_IDLE: 空閒總線標誌
  *          USART_FLAG_ORE:  溢出錯誤標誌
  *          USART_FLAG_NE:   噪聲錯誤標誌
  *          USART_FLAG_FE:   幀錯誤標誌
  *          USART_FLAG_PE:   奇偶錯誤標誌
  * @retval  USART_FLAG 的新狀態(SET 或 RESET).
  */
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* 檢查參數 */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_FLAG(USART_FLAG));
  /* CTS 標誌不能應用於 UART4 和 UART5 */
  if (USART_FLAG == USART_FLAG_CTS)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  }  
  
  if ((USARTx->SR & USART_FLAG) != (uint16_t)RESET)
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
  * @簡述  清除 USARTx 的待處理標誌位.
  * @參數  USARTx: 選擇 USART 或者 UART 的外圍設備.
  *                這個參數可以是下面的值之一 : USART1, USART2, USART3, UART4 or UART5.
  * @參數  USART_FLAG: 指定要被清除的標記.
  *          這個參數可以是下面的值的任意組合:
  *          USART_FLAG_CTS:  CTS 改變標誌 (不能應用於 UART4 和 UART5).
  *          USART_FLAG_LBD:  LIN 間隔偵測標誌.
  *          USART_FLAG_TC:   傳輸完成標誌.
  *          USART_FLAG_RXNE: 接收數據寄存器不為空標誌.
  *   
  * @註解
*          - PE (奇偶校驗錯誤), FE (楨錯誤), NE (噪聲錯誤),
*            ORE (過速錯誤) 和 IDLE (找到空閒線) 標誌標誌被軟件按順序清除:
*            一個讀USART_SR寄存器操作（USART_GetFlagStatus()）
*            接著一個讀USART_DR寄存器操作(USART_ReceiveData()).
*          - RXNE標誌也可以被一個讀USART_DR寄存器操作清除(USART_ReceiveData()).
*          - TC標誌標誌被軟件按順序清除: 一個讀USART_SR寄存器操作（USART_GetFlagStatus()）
*            接著一個讀USART_DR寄存器操作(USART_ReceiveData()).                                                      
*          - TXE標誌只能靠寫USART_DR寄存器清除(USART_SendData()).     
  * @返回  沒有
  */
void USART_ClearFlag(USART_TypeDef* USARTx, uint16_t USART_FLAG)
{
  /* 檢查參數 */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CLEAR_FLAG(USART_FLAG));
  /* CTS 標誌不能應用於 UART4 和 UART5 */
  if ((USART_FLAG & USART_FLAG_CTS) == USART_FLAG_CTS)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  } 
   
  USARTx->SR = (uint16_t)~USART_FLAG;
}

/**
  * @簡述  檢查指定的 USART 中斷發生與否.
  * @參數  USARTx: 選擇 USART 或者 UART 的外圍設備. 
  *                這個參數可以是下面的值之一 : USART1, USART2, USART3, UART4 or UART5.
  * @參數  USART_IT: 指定要檢測的USART中斷源.
  *          這個參數可以是下面的值之一 :
  *          USART_IT_CTS:  CTS 改變中斷 (不能應用於 UART4 和 UART5)
  *          USART_IT_LBD:  LIN 間隔偵測中斷
  *          USART_IT_TXE:  發送數據寄存器為空中斷
  *          USART_IT_TC:   傳輸完成中斷
  *          USART_IT_RXNE: 接收數據寄存器不為空中斷
  *          USART_IT_IDLE: 空閒總線中斷
  *          USART_IT_ORE:  溢出錯誤中斷
  *          USART_IT_NE:   噪聲錯誤中斷
  *          USART_IT_FE:   幀錯誤中斷
  *          USART_IT_PE:   奇偶錯誤中斷
  * @返回  USART_IT 的新狀態 (SET 或 RESET).
  */
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint16_t USART_IT)
{
  uint32_t bitpos = 0x00, itmask = 0x00, usartreg = 0x00;
  ITStatus bitstatus = RESET;
  /* 檢查參數 */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_GET_IT(USART_IT));
  /* CTS 中斷不能應用於 UART4 和 UART5 */ 
  if (USART_IT == USART_IT_CTS)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  }   
  
  /* 得到 USART 寄存器引索 */
  usartreg = (((uint8_t)USART_IT) >> 0x05);
  /*得到中斷位置 */
  itmask = USART_IT & IT_Mask;
  itmask = (uint32_t)0x01 << itmask;
  
  if (usartreg == 0x01) /* The IT  is in CR1 register */
  {
    itmask &= USARTx->CR1;
  }
  else if (usartreg == 0x02) /* The IT  is in CR2 register */
  {
    itmask &= USARTx->CR2;
  }
  else /* The IT  is in CR3 register */
  {
    itmask &= USARTx->CR3;
  }
  
  bitpos = USART_IT >> 0x08;
  bitpos = (uint32_t)0x01 << bitpos;
  bitpos &= USARTx->SR;
  if ((itmask != (uint16_t)RESET)&&(bitpos != (uint16_t)RESET))
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
  * @簡述  清除 USARTx 的中斷待處理位.
  * @返回  USARTx: 選擇 USART 或者 UART 的外圍設備. 
  *                這個參數可以是下面的值之一 : USART1, USART2, USART3, UART4 or UART5.
  * @參數  USART_IT: 指定要被清除的中斷掛起位.
  *          這個參數可以是下面的值之一:
  *          USART_IT_CTS:  CTS 改變中斷 (不能應用於 UART4 和 UART5)
  *          USART_IT_LBD:  LIN 間隔偵測中斷
  *          USART_IT_TC:   發送完成中斷
  *          USART_IT_RXNE: 接收數據寄存器不為空中斷
  *   
  * @註解
*          - PE (奇偶校驗錯誤), FE (楨錯誤), NE (噪聲錯誤),
*            ORE (過速錯誤) 和 IDLE (找到空閒線)掛起位 
*            被軟件按順序清除: 一個讀USART_SR寄存器操作（USART_GetFlagStatus()）
*            接著一個讀USART_DR寄存器操作(USART_ReceiveData()).
*          - RXNE掛起位也可以被一個讀USART_DR寄存器操作清除(USART_ReceiveData()).
*          - TC掛起位也可以被軟件按順序清除: 一個讀USART_SR寄存器操作（USART_GetFlagStatus()）
*            接著一個讀USART_DR寄存器操作(USART_ReceiveData()).                                                      
*          - TXE掛起位置可以被一個寫USART_DR寄存器清除(USART_SendData()).  
  * @返回  沒有
  */
void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT)
{
  uint16_t bitpos = 0x00, itmask = 0x00;
  /* 檢查參數 */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CLEAR_IT(USART_IT));
  /* CTS 中斷不能應用於 UART4 和 UART5 */
  if (USART_IT == USART_IT_CTS)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  }   
  
  bitpos = USART_IT >> 0x08;
  itmask = ((uint16_t)0x01 << (uint16_t)bitpos);
  USARTx->SR = (uint16_t)~itmask;
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
