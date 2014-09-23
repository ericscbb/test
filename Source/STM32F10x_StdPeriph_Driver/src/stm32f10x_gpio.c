/**
  ******************************************************************************
  * @文件    stm32f10x_gpio.c
  * @作者    MCD 應用程序組
  * @版本    V3.1.0
  * @日期    06/19/2009
  * @簡述    這個文件 提供所有 GPIO 固件函數.
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
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

/* 自用類型 -----------------------------------------------------------*/
/* 自用定義 ------------------------------------------------------------*/

/* ------------ RCC registers bit address in the alias region ----------------*/
#define AFIO_OFFSET                 (AFIO_BASE - PERIPH_BASE)

/* --- EVENTCR Register -----*/

/* Alias word address of EVOE bit */
#define EVCR_OFFSET                 (AFIO_OFFSET + 0x00)
#define EVOE_BitNumber              ((uint8_t)0x07)
#define EVCR_EVOE_BB                (PERIPH_BB_BASE + (EVCR_OFFSET * 32) + (EVOE_BitNumber * 4))


/* ---  MAPR Register ---*/ 
/* Alias word address of MII_RMII_SEL bit */ 
#define MAPR_OFFSET                 (AFIO_OFFSET + 0x04) 
#define MII_RMII_SEL_BitNumber      ((u8)0x17) 
#define MAPR_MII_RMII_SEL_BB        (PERIPH_BB_BASE + (MAPR_OFFSET * 32) + (MII_RMII_SEL_BitNumber * 4))


#define EVCR_PORTPINCONFIG_MASK     ((uint16_t)0xFF80)
#define LSB_MASK                    ((uint16_t)0xFFFF)
#define DBGAFR_POSITION_MASK        ((uint32_t)0x000F0000)
#define DBGAFR_SWJCFG_MASK          ((uint32_t)0xF0FFFFFF)
#define DBGAFR_LOCATION_MASK        ((uint32_t)0x00200000)
#define DBGAFR_NUMBITS_MASK         ((uint32_t)0x00100000)

/* 自用宏 -------------------------------------------------------------*/
/* 自用變量 ---------------------------------------------------------*/
/* 自用函數原型 -----------------------------------------------*/
/* 自用函數 ---------------------------------------------------------*/

/**
  * @簡述   將GPIO部件的寄存器復位為默認值
  * @參數   GPIOx：x可為A到G來選擇特定的GPIO設備
  * @返回   沒有
  */
void GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
  /* 檢查核對參數*/
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  
  if (GPIOx == GPIOA)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA, DISABLE);
  }
  else if (GPIOx == GPIOB)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOB, DISABLE);
  }
  else if (GPIOx == GPIOC)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOC, DISABLE);
  }
  else if (GPIOx == GPIOD)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOD, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOD, DISABLE);
  }    
  else if (GPIOx == GPIOE)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOE, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOE, DISABLE);
  } 
  else if (GPIOx == GPIOF)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOF, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOF, DISABLE);
  }
  else
  {
    if (GPIOx == GPIOG)
    {
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOG, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOG, DISABLE);
    }
  }
}

/**
  * @簡述  將備用功能（重映射，事件控制及EXTI配置）寄存器復位為默認值
  * @參數  沒有
  * @返回  沒有
  */
void GPIO_AFIODeInit(void)
{
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_AFIO, DISABLE);
}

/**
  * @簡述  按照GPIO_InitStruct(結構體)的特定參數初始化GPIO部件
  * @參數  GPIOx：x可為A到G來選擇特定的GPIO設備，
  *        GPIO_InitStruct: 指向GPIO_InitTypeDef結構的指針，它包含特定GPIO部件的配置信息.
  * @返回  沒有
  */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
  uint32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
  uint32_t tmpreg = 0x00, pinmask = 0x00;
  /* 檢查參數 */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
  assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));  
  
/*---------------------------- GPIO 模式配置 --------------------------------*/
  currentmode = ((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x0F);
  if ((((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x10)) != 0x00)
  { 
    /* Check the parameters */
    assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));
    /* Output mode */
    currentmode |= (uint32_t)GPIO_InitStruct->GPIO_Speed;
  }
/*-------------------- GPIO CRL(端口控制寄存器低字節) 配置 -------------------*/
  /* 配置低8位端口管腳 */
  if (((uint32_t)GPIO_InitStruct->GPIO_Pin & ((uint32_t)0x00FF)) != 0x00)
  {
    tmpreg = GPIOx->CRL;
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = ((uint32_t)0x01) << pinpos;
      /* 取得端口引腳的位置 */
      currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
      if (currentpin == pos)
      {
        pos = pinpos << 2;
        /* 清空相應的低位控制寄存器 */
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        /* 寫相應的模式配置位 */
        tmpreg |= (currentmode << pos);
        /* 復位相應的輸出數據寄存器 (ODR) 位 */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          GPIOx->BRR = (((uint32_t)0x01) << pinpos);
        }
        else
        {
          /* 置位相應的輸出數據寄存器 (ODR) 位 */
          if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
          {
            GPIOx->BSRR = (((uint32_t)0x01) << pinpos);
          }
        }
      }
    }
    GPIOx->CRL = tmpreg;
  }
/*-------------------- GPIO CRH(端口控制寄存器高字節) 配置 -------------------*/
  /* 配置高8位端口引腳 */
  if (GPIO_InitStruct->GPIO_Pin > 0x00FF)
  {
    tmpreg = GPIOx->CRH;
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = (((uint32_t)0x01) << (pinpos + 0x08));
      /* 取得端口引腳的位置 */
      currentpin = ((GPIO_InitStruct->GPIO_Pin) & pos);
      if (currentpin == pos)
      {
        pos = pinpos << 2;
        /* 清空相應的低位控制寄存器 */
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        /* 寫相應的模式配置位 */
        tmpreg |= (currentmode << pos);
        /* 復位相應的輸出數據寄存器 (ODR) 位 */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          GPIOx->BRR = (((uint32_t)0x01) << (pinpos + 0x08));
        }
        /* 置位相應的輸出數據寄存器 (ODR) 位 */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
        {
          GPIOx->BSRR = (((uint32_t)0x01) << (pinpos + 0x08));
        }
      }
    }
    GPIOx->CRH = tmpreg;
  }
}

/**
  * @簡述  把GPIO_InitStruct中的每一個參數按缺省值填入.
  * @參數  GPIO_InitStruct : 指向GPIO_InitTypeDef結構，該結構將被初始化
  * @返回  沒有
  */
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
  /* 復位GPIO初始化結構參數值 */
  GPIO_InitStruct->GPIO_Pin  = GPIO_Pin_All;
  GPIO_InitStruct->GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN_FLOATING;
}

/**
  * @簡述  讀取指定端口管腳的輸入.
  * @參數  GPIOx: x可為A到G來選擇特定的GPIO設備.
  *        GPIO_Pin:  被讀取的引腳位.
  *                   這個參數GPIO_Pin_x可以選擇0至15.
  * @返回  指定端口管腳的輸入值.
  */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;
  
  /* 檢查參數 */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin)); 
  
  if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

/**
  * @簡述  從特定的GPIO輸入數據端口讀取.
  * @參數  GPIOx: x可為A到G來選擇特定的GPIO設備.
  * @返回  指定的 GPIO 端口管腳的輸入值.
  */
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
{
  /* 檢查參數 */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  
  return ((uint16_t)GPIOx->IDR);
}

/**
  * @簡述  讀取指定端口管腳的輸出(位).
  * @參數  GPIOx: x可為A到G來選擇特定的GPIO設備.
  *        GPIO_Pin: 需要讀取的端口位.
  *                  這個參數GPIO_Pin_x可以選擇0至15.
  * @返回  輸出端口的輸出值.
  */
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;
  /* 檢查參數 */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin)); 
  
  if ((GPIOx->ODR & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

/**
  * @簡述  讀取指定的GPIO端口輸出.
  * @參數  GPIOx: x可為A到G來選擇特定的GPIO設備.
  * @返回  指定 GPIO 輸出數據端口值.
  */
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    
  return ((uint16_t)GPIOx->ODR);
}

/**
  * @簡述  設置指定的數據端口位.
  * @參數  x可為A到G來選擇特定的GPIO設備.
  *        GPIO_Pin: 確定端口位.
  *                  該參數可為GPIO_Pin_x的任意組合,其中x為0到15.
  * @返回  沒有
  */
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* 檢查參數 */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  
  GPIOx->BSRR = GPIO_Pin;
}

/**
  * @簡述  清除指定的數據端口位.
  * @參數  x可為A到G來選擇特定的GPIO設備.
  *        GPIO_Pin: 確定端口位.
  *                  該參數可為GPIO_Pin_x的任意組合,其中x為0到15.
  * @返回  沒有
  */
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* 檢查參數 */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  
  GPIOx->BRR = GPIO_Pin;
}

/**
  * @簡述  設置或者清除指定的數據端口位.
  * @參數  GPIOx: x可為A到G來選擇特定的GPIO設備.
  *        GPIO_Pin: 指定被寫入的端口位.
  *                  該參數可為GPIO_Pin_x的任意組合,其中x為0到15.
  *        BitVal:   該參數指定被寫入到選定位.
  *                  BitVal必須為BitAction枚舉類型值: 
  *                  @arg Bit_RESET:清除端口引腳，
  *                  @arg Bit_SET:置位端口引腳
  * @返回  沒有
  */
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
  /* 檢查參數 */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_BIT_ACTION(BitVal)); 
  
  if (BitVal != Bit_RESET)
  {
    GPIOx->BSRR = GPIO_Pin;
  }
  else
  {
    GPIOx->BRR = GPIO_Pin;
  }
}

/**
  * @簡述  向指定GPIO數據端口寫入數據.
  * @參數  GPIOx: x可為A到G來選擇特定的GPIO設備.
  *        PortVal: 寫入到數據端口寄存器的值.
  * @返回  沒有
  */
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal)
{
  /* 檢查參數 */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  
  GPIOx->ODR = PortVal;
}

/**
  * @簡述  鎖定GPIO引腳配置寄存器.
  * @參數  GPIOx: x可為A到G來選擇特定的GPIO設備.
  *        GPIO_Pin:指定被寫入的端口位.
  *                 該參數可為GPIO_Pin_x的任意組合,其中x為0到15.
  * @返回  沒有
  */
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint32_t tmp = 0x00010000;
  
  /* 檢查參數 */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  
  tmp |= GPIO_Pin;
  /* Set LCKK bit */
  GPIOx->LCKR = tmp;
  /* Reset LCKK bit */
  GPIOx->LCKR =  GPIO_Pin;
  /* Set LCKK bit */
  GPIOx->LCKR = tmp;
  /* Read LCKK bit*/
  tmp = GPIOx->LCKR;
  /* Read LCKK bit*/
  tmp = GPIOx->LCKR;
}

/**
  * @簡述  選擇 GPIO 管腳用作事件輸出.
  * @參數  GPIO_PortSource: 選擇用作事件輸出的GPIO端口
  *                         GPIOx:x可為A到E來選擇特定的GPIO設備.
  *        GPIO_PinSource: 事件輸出的管腳.
  *                        該參數可為GPIO_PinSourcex,這裡x可為0到15.
  * @返回  沒有
  */
void GPIO_EventOutputConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource)
{
  uint32_t tmpreg = 0x00;
  /* 檢查參數 */
  assert_param(IS_GPIO_EVENTOUT_PORT_SOURCE(GPIO_PortSource));
  assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));
    
  tmpreg = AFIO->EVCR;
  /* Clear the PORT[6:4] and PIN[3:0] bits */
  tmpreg &= EVCR_PORTPINCONFIG_MASK;
  tmpreg |= (uint32_t)GPIO_PortSource << 0x04;
  tmpreg |= GPIO_PinSource;
  AFIO->EVCR = tmpreg;
}

/**
  * @簡述  使能或者失能事件輸出.
  * @參數  NewState: 事件輸出的新狀態.
  *                  這個參數可以取：ENABLE或者DISABLE.
  * @返回  沒有
  */
void GPIO_EventOutputCmd(FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  *(__IO uint32_t *) EVCR_EVOE_BB = (uint32_t)NewState;
}

/**
  * @簡述  改變指定管腳的映射.
  * @參數  GPIO_Remap: 選擇重映射的管腳.
  *                    GPIO_Remap 用來改變備用功能映射,它的可用值:
  *     @arg GPIO_Remap_SPI1
  *     @arg GPIO_Remap_I2C1
  *     @arg GPIO_Remap_USART1
  *     @arg GPIO_Remap_USART2
  *     @arg GPIO_PartialRemap_USART3
  *     @arg GPIO_FullRemap_USART3
  *     @arg GPIO_PartialRemap_TIM1
  *     @arg GPIO_FullRemap_TIM1
  *     @arg GPIO_PartialRemap1_TIM2
  *     @arg GPIO_PartialRemap2_TIM2
  *     @arg GPIO_FullRemap_TIM2
  *     @arg GPIO_PartialRemap_TIM3
  *     @arg GPIO_FullRemap_TIM3
  *     @arg GPIO_Remap_TIM4
  *     @arg GPIO_Remap1_CAN1
  *     @arg GPIO_Remap2_CAN1
  *     @arg GPIO_Remap_PD01
  *     @arg GPIO_Remap_TIM5CH4_LSI
  *     @arg GPIO_Remap_ADC1_ETRGINJ
  *     @arg GPIO_Remap_ADC1_ETRGREG
  *     @arg GPIO_Remap_ADC2_ETRGINJ
  *     @arg GPIO_Remap_ADC2_ETRGREG
  *     @arg GPIO_Remap_ETH
  *     @arg GPIO_Remap_CAN2  
  *     @arg GPIO_Remap_SWJ_NoJTRST
  *     @arg GPIO_Remap_SWJ_JTAGDisable
  *     @arg GPIO_Remap_SWJ_Disable
  *     @arg GPIO_Remap_SPI3
  *     @arg GPIO_Remap_TIM2ITR1_PTP_SOF
  *     @arg GPIO_Remap_PTP_PPS  
  * @註解  如果 GPIO_Remap_TIM2ITR1_PTP_SOF 被激活  TIM2 ITR1 連接到以太網 PTP 輸出
  *        當復位的時候 TIM2 ITR1 連接到 USB OTG SOF 輸出.       
  * @參數  NewState: 端口引腳重映射的新狀態.
  *                  該參數可為：ENABLE或DISABLE.
  * @返回  沒有
  */
void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState)
{
  uint32_t tmp = 0x00, tmp1 = 0x00, tmpreg = 0x00, tmpmask = 0x00;

  /* 檢查參數 */
  assert_param(IS_GPIO_REMAP(GPIO_Remap));
  assert_param(IS_FUNCTIONAL_STATE(NewState));  
  
  tmpreg = AFIO->MAPR;

  tmpmask = (GPIO_Remap & DBGAFR_POSITION_MASK) >> 0x10;
  tmp = GPIO_Remap & LSB_MASK;

  if ((GPIO_Remap & (DBGAFR_LOCATION_MASK | DBGAFR_NUMBITS_MASK)) == (DBGAFR_LOCATION_MASK | DBGAFR_NUMBITS_MASK))
  {
    tmpreg &= DBGAFR_SWJCFG_MASK;
    AFIO->MAPR &= DBGAFR_SWJCFG_MASK;
  }
  else if ((GPIO_Remap & DBGAFR_NUMBITS_MASK) == DBGAFR_NUMBITS_MASK)
  {
    tmp1 = ((uint32_t)0x03) << tmpmask;
    tmpreg &= ~tmp1;
    tmpreg |= ~DBGAFR_SWJCFG_MASK;
  }
  else
  {
    tmpreg &= ~(tmp << ((GPIO_Remap >> 0x15)*0x10));
    tmpreg |= ~DBGAFR_SWJCFG_MASK;
  }

  if (NewState != DISABLE)
  {
    tmpreg |= (tmp << ((GPIO_Remap >> 0x15)*0x10));
  }

  AFIO->MAPR = tmpreg;
}

/**
  * @簡述  選擇GPIO引腳作為 EXTI 線.
  * @參數  GPIO_PortSource: 選擇將要用作 EXTI 線的源的 GPIO 口.
  *                         GPIOx:x可為A到G來選擇特定的GPIO設備.
  *        GPIO_PinSource:  指定需要配置的EXTI線.
  *                         這個參數可以是GPIO_PinSourcex,其中x為0到15.
  * @返回  沒有
  */
void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource)
{
  uint32_t tmp = 0x00;
  /* 檢查參數 */
  assert_param(IS_GPIO_EXTI_PORT_SOURCE(GPIO_PortSource));
  assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));
  
  tmp = ((uint32_t)0x0F) << (0x04 * (GPIO_PinSource & (uint8_t)0x03));
  AFIO->EXTICR[GPIO_PinSource >> 0x02] &= ~tmp;
  AFIO->EXTICR[GPIO_PinSource >> 0x02] |= (((uint32_t)GPIO_PortSource) << (0x04 * (GPIO_PinSource & (uint8_t)0x03)));
}

/**
  * @簡述  指定以太網接口.
  * @註解  此功能僅適用於STM32連接線配置.  
  * @參數  GPIO_ETH_MediaInterface: 指定接口模式.
  *                                 這個參數可以選擇:
  *                                 GPIO_ETH_MediaInterface_MII: MII mode    ->獨立接口
  *                                 GPIO_ETH_MediaInterface_RMII: RMII mode  ->精簡獨立接口  
  * @返回  沒有
  */
void GPIO_ETH_MediaInterfaceConfig(uint32_t GPIO_ETH_MediaInterface) 
{ 
  assert_param(IS_GPIO_ETH_MEDIA_INTERFACE(GPIO_ETH_MediaInterface)); 

  /* 配置 MII_RMII 選擇位 */ 
  *(__IO uint32_t *) MAPR_MII_RMII_SEL_BB = GPIO_ETH_MediaInterface; 
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
