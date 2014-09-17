/**
  ******************************************************************************
  * @文件    stm32f10x_spi.c
  * @作者    MCD Application Team
  * @版本    V3.1.0
  * @日期    06/19/2009
  * @簡述    這個文件 提供所有 SPI 固件函數.
  * @翻譯    ANSON/sweet1985 Email:airanson110@126.com
  * @日期    25/07/2009
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
#include "stm32f10x_spi.h"
#include "stm32f10x_rcc.h"

/* 自用類型 --------------------------------------------------------------*/
/* 自用定義 --------------------------------------------------------------*/

/* SPI SPE mask */
#define CR1_SPE_Set          ((uint16_t)0x0040)
#define CR1_SPE_Reset        ((uint16_t)0xFFBF)

/* I2S I2SE mask */
#define I2SCFGR_I2SE_Set     ((uint16_t)0x0400)
#define I2SCFGR_I2SE_Reset   ((uint16_t)0xFBFF)

/* SPI CRCNext mask */
#define CR1_CRCNext_Set      ((uint16_t)0x1000)

/* SPI CRCEN mask */
#define CR1_CRCEN_Set        ((uint16_t)0x2000)
#define CR1_CRCEN_Reset      ((uint16_t)0xDFFF)

/* SPI SSOE mask */
#define CR2_SSOE_Set         ((uint16_t)0x0004)
#define CR2_SSOE_Reset       ((uint16_t)0xFFFB)

/* SPI registers Masks */
#define CR1_CLEAR_Mask       ((uint16_t)0x3040)
#define I2SCFGR_CLEAR_Mask   ((uint16_t)0xF040)

/* SPI or I2S mode selection masks */
#define SPI_Mode_Select      ((uint16_t)0xF7FF)
#define I2S_Mode_Select      ((uint16_t)0x0800) 

/* I2S clock source selection masks */
#define I2S2_CLOCK_SRC       ((u32)(0x00020000))
#define I2S3_CLOCK_SRC       ((u32)(0x00040000))
#define I2S_MUL_MASK         ((u32)(0x0000F000))
#define I2S_DIV_MASK         ((u32)(0x000000F0))

/* 自用宏 -------------------------------------------------------------*/
/* 自用變量 -----------------------------------------------------------*/
/* 自用函數原型 -------------------------------------------------------*/
/* 自用函數 -----------------------------------------------------------*/

/**
  * @簡述  將外設 SPIx 寄存器重設為缺省值 (也作用 I2Ss).
  * @參數  SPIx: x為1，2或3用於選定 SPI 外設.
  * @返回  沒有
  */
void SPI_I2S_DeInit(SPI_TypeDef* SPIx)
{
  /* 檢查參數 */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  if (SPIx == SPI1)
  {
    /* 使能 SPI1 復位狀態 */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, ENABLE);
    /* 釋放 SPI1 從復位狀態 */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, DISABLE);
  }
  else if (SPIx == SPI2)
  {
    /* 使能 SPI2 復位狀態 */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, ENABLE);
    /* 釋放 SPI2 從復位狀態 */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, DISABLE);
  }
  else
  {
    if (SPIx == SPI3)
    {
      /* 使能 SPI3 復位狀態 */
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, ENABLE);
      /* 釋放 SPI3 從復位狀態 */
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, DISABLE);
    }
  }
}

/**
  * @簡述  根據 SPI_InitStruct 中指定的參數初始化外設 SPIx 寄存器.
  * @參數  SPIx: x 為1，2或3用於選定 SPI 外設.
  * @參數  SPI_InitStruct: 指向一個包含特定 SPI 外設配置信息的 SPI_InitTypeDef 結構體的指針.
  * @返回  沒有
  */
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct)
{
  uint16_t tmpreg = 0;
  
  /* 檢查參數 */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));   
  
  /* 檢查 SPI 的參數 */
  assert_param(IS_SPI_DIRECTION_MODE(SPI_InitStruct->SPI_Direction));
  assert_param(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
  assert_param(IS_SPI_DATASIZE(SPI_InitStruct->SPI_DataSize));
  assert_param(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
  assert_param(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
  assert_param(IS_SPI_NSS(SPI_InitStruct->SPI_NSS));
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_InitStruct->SPI_BaudRatePrescaler));
  assert_param(IS_SPI_FIRST_BIT(SPI_InitStruct->SPI_FirstBit));
  assert_param(IS_SPI_CRC_POLYNOMIAL(SPI_InitStruct->SPI_CRCPolynomial));

/*---------------------------- SPIx CR1 配置 ------------------------*/
  /* 得到 SPIx CR1 的值 */
  tmpreg = SPIx->CR1;
  /* 清除 BIDIMode, BIDIOE, RxONLY, SSM, SSI, LSBFirst, BR, MSTR, CPOL 和 CPHA 位 */
  tmpreg &= CR1_CLEAR_Mask;
  /* 配置 SPIx: direction(方向), NSS management(NSS管理), first transmitted bit(第一個發送位), BaudRate prescaler(波特率預分頻)
     master/salve mode(主/從模式), CPOL(時鐘極性) 和 CPHA(時鐘相位) */
  /* 設置 BIDImode, BIDIOE 和 RxONLY 位，按照 SPI_Direction 的值 */
  /* 設置 SSM, SSI and MSTR 位，按照 SPI_Mode 和 SPI_NSS 的值 */
  /* 設置 LSBFirst 位，按照 SPI_FirstBit 的值 */
  /* 設置 BR 位，按照 SPI_BaudRatePrescaler 的值 */
  /* 設置 CPOL 位，按照 SPI_CPOL 的值 */
  /* 設置 CPHA 位，按照 SPI_CPHA 的值 */
  tmpreg |= (uint16_t)((uint32_t)SPI_InitStruct->SPI_Direction | SPI_InitStruct->SPI_Mode |
                  SPI_InitStruct->SPI_DataSize | SPI_InitStruct->SPI_CPOL |  
                  SPI_InitStruct->SPI_CPHA | SPI_InitStruct->SPI_NSS |  
                  SPI_InitStruct->SPI_BaudRatePrescaler | SPI_InitStruct->SPI_FirstBit);
  /* 寫 SPIx CR1 */
  SPIx->CR1 = tmpreg;
  
  /* 激活 SPI 模式 (復位 I2SMOD 位，在 I2SCFGR 寄存器) */
  SPIx->I2SCFGR &= SPI_Mode_Select;		

/*---------------------------- SPIx CRCPOLY 配置 --------------------*/
  /* 寫 SPIx CRCPOLY */
  SPIx->CRCPR = SPI_InitStruct->SPI_CRCPolynomial;
}

/**
  * @簡述  根據 SPI_InitStruct 中的特定參數初始化 SPIx 外設.
  * @參數  SPIx: x為1，2或3用於選定SPI外設 (配置 I2S 模式).
  * @參數  I2S_InitStruct: 指向一個在模式 I2S 包含特定 SPI 外設配置信息的 SPI_InitTypeDef 結構體的指針.
  * @註解
  *  The function calculates the optimal prescaler needed to obtain the most 
  *  accurate audio frequency (depending on the I2S clock source, the PLL values 
  *  and the product configuration). But in case the prescaler value is greater 
  *  than 511, the default value (0x02) will be configured instead.  *    
  * @返回  沒有
  */
void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct)
{
  uint16_t tmpreg = 0, i2sdiv = 2, i2sodd = 0, packetlength = 1;
  uint32_t tmp = 0;
  RCC_ClocksTypeDef RCC_Clocks;
  uint32_t sourceclock = 0;
  
  /* 檢查 I2S 參數 */
  assert_param(IS_SPI_23_PERIPH(SPIx));
  assert_param(IS_I2S_MODE(I2S_InitStruct->I2S_Mode));
  assert_param(IS_I2S_STANDARD(I2S_InitStruct->I2S_Standard));
  assert_param(IS_I2S_DATA_FORMAT(I2S_InitStruct->I2S_DataFormat));
  assert_param(IS_I2S_MCLK_OUTPUT(I2S_InitStruct->I2S_MCLKOutput));
  assert_param(IS_I2S_AUDIO_FREQ(I2S_InitStruct->I2S_AudioFreq));
  assert_param(IS_I2S_CPOL(I2S_InitStruct->I2S_CPOL));  

/*----------------------- SPIx I2SCFGR & I2SPR 配置 -----------------*/
  /* 清除 I2SMOD, I2SE, I2SCFG, PCMSYNC, I2SSTD, CKPOL, DATLEN 和 CHLEN 位 */
  SPIx->I2SCFGR &= I2SCFGR_CLEAR_Mask; 
  SPIx->I2SPR = 0x0002;
  
  /* 得到 I2SCFGR 寄存器的值 */
  tmpreg = SPIx->I2SCFGR;
  
  /* 如果默認值已經寫了，重新初始化 i2sdiv 和 i2sodd */
  if(I2S_InitStruct->I2S_AudioFreq == I2S_AudioFreq_Default)
  {
    i2sodd = (uint16_t)0;
    i2sdiv = (uint16_t)2;   
  }
  /* 如果請求的的音頻不是默認值，計算預分頻 */
  else
  {
    /* 檢查禎長(計算預分頻器) */
    if(I2S_InitStruct->I2S_DataFormat == I2S_DataFormat_16b)
    {
      /* 包的長度16位 */
      packetlength = 1;
    }
    else
    {
      /* 包的長度32位 */
      packetlength = 2;
    }

    /* 取得 I2S 系統時鐘頻率 */
    if(((uint32_t)SPIx) == SPI2_BASE)
    {
      /* I2S2 */
      tmp = I2S2_CLOCK_SRC;
    }
    else 
    {
      /* I2S3 */      
      tmp = I2S3_CLOCK_SRC;
    }

    /* 檢查 I2S 時鐘脈衝源: 僅僅是通用性設備有 PLL3 VCO 時鐘 */
#ifdef STM32F10X_CL
    if((RCC->CFGR2 & tmp) != 0)
    {
      /* 得到 RCC PLL3 倍增值的配置位 */
      tmp = (uint32_t)((RCC->CFGR2 & I2S_MUL_MASK) >> 12);

      /* 得到 PLL3 倍增器的值 */      
      if((tmp > 5) && (tmp < 15))
      {
        /* 倍增值在 8 和 14 之間 (禁止 15 ) */
        tmp += 2;
      }
      else
      {
        if (tmp == 15)
        {
          /* 倍增數是 20 */
          tmp = 20;
        }
      }      
      /* 得到 PREDIV2 的值 */
      sourceclock = (uint32_t)(((RCC->CFGR2 & I2S_DIV_MASK) >> 4) + 1);
      
      /* 計算時鐘頻率，根據 PLL3 和 PREDIV2 的值 */
      sourceclock = (uint32_t) ((HSE_Value / sourceclock) * tmp * 2); 
    }
    else
    {
      /* I2S 時鐘是系統時鐘: 得到系統時鐘頻率 */
      RCC_GetClocksFreq(&RCC_Clocks);      
      
      /* 得到來源時鐘的值: 根據系統時鐘的值 */
      sourceclock = RCC_Clocks.SYSCLK_Frequency;
    }        
#else /* STM32F10X_HD */
    /* I2S 時鐘源是系統時鐘: 得到系統時鐘頻率 */
    RCC_GetClocksFreq(&RCC_Clocks);      
      
    /* 得到來源時鐘的值: 根據系統時鐘的值 */
    sourceclock = RCC_Clocks.SYSCLK_Frequency;    
#endif /* STM32F10X_CL */    

    /* 用浮點指針根據MCLK輸出狀態計算真實分割器 */
    if(I2S_InitStruct->I2S_MCLKOutput == I2S_MCLKOutput_Enable)
    {
      /* MCLK輸出使能 */
      tmp = (uint16_t)(((((sourceclock / 256) * 10) / I2S_InitStruct->I2S_AudioFreq)) + 5);
    }
    else
    {
      /* MCLK輸出失能 */
      tmp = (uint16_t)(((((sourceclock / (32 * packetlength)) *10 ) / I2S_InitStruct->I2S_AudioFreq)) + 5);
    }
    
    /* 刪除浮點指針 */
    tmp = tmp / 10;  
      
    /* 檢查除數的奇偶 */
    i2sodd = (uint16_t)(tmp & (u16)0x0001);
   
    /* 計算i2sdiv預分頻器 */
    i2sdiv = (uint16_t)((tmp - i2sodd) / 2);
   
    /* 取得(SPI_I2SPR[8])寄存器舊的標誌位 */
    i2sodd = (uint16_t) (i2sodd << 8);
  }
  
  /* 測試除數是1還是0 或大於 0xFF */
  if ((i2sdiv < 2) || (i2sdiv > 0xFF))
  {
    /* 設置缺省值 */
    i2sdiv = 2;
    i2sodd = 0;
  }

  /* 寫 SPIx I2SPR 寄存器的計算值 */
  SPIx->I2SPR = (uint16_t)(i2sdiv | (uint16_t)(i2sodd | (uint16_t)I2S_InitStruct->I2S_MCLKOutput));  
 
  /* 用 SPI_InitStruct 的值，配置 I2S  */
  tmpreg |= (uint16_t)(I2S_Mode_Select | (uint16_t)(I2S_InitStruct->I2S_Mode | \
                  (uint16_t)(I2S_InitStruct->I2S_Standard | (uint16_t)(I2S_InitStruct->I2S_DataFormat | \
                  (uint16_t)I2S_InitStruct->I2S_CPOL))));
 
  /* 寫 SPIx I2SCFGR */  
  SPIx->I2SCFGR = tmpreg;   
}

/**
  * @簡述  使用缺省值填充 SPI_InitStruct 每一個成員.
  * @參數  SPI_InitStruct : 指向一個將被初始化的 SPI_InitTypeDef 結構的指針.
  * @返回  沒有
  */
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)
{
/*--------------- 重置 SPI I初始化結構參數值 -----------------*/
  /* 初始化 SPI_Direction 成員 */
  SPI_InitStruct->SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  /* 初始化 SPI_Mode 成員 */
  SPI_InitStruct->SPI_Mode = SPI_Mode_Slave;
  /* 初始化 SPI_DataSize 成員 */
  SPI_InitStruct->SPI_DataSize = SPI_DataSize_8b;
  /* 初始化 SPI_CPOL 成員 */
  SPI_InitStruct->SPI_CPOL = SPI_CPOL_Low;
  /* 初始化 SPI_CPHA 成員 */
  SPI_InitStruct->SPI_CPHA = SPI_CPHA_1Edge;
  /* 初始化 SPI_NSS 成員 */
  SPI_InitStruct->SPI_NSS = SPI_NSS_Hard;
  /* 初始化 SPI_BaudRatePrescaler 成員 */
  SPI_InitStruct->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
  /* 初始化 SPI_FirstBit 成員 */
  SPI_InitStruct->SPI_FirstBit = SPI_FirstBit_MSB;
  /* 初始化 SPI_CRCPolynomial 成員 */
  SPI_InitStruct->SPI_CRCPolynomial = 7;
}

/**
  * @簡述  用默認值填充每個 I2S_InitStruct 結構成員.
  * @參數  I2S_InitStruct : 指向將要被初始化的I2S_InitTypeDef 結構指針.
  * @返回  沒有
  */
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct)
{
/*--------------- 重置 I2S 初始化結構參數值 -----------------*/
  /* 初始化 I2S_Mode 成員 */
  I2S_InitStruct->I2S_Mode = I2S_Mode_SlaveTx;
  
  /* 初始化 I2S_Standard 成員 */
  I2S_InitStruct->I2S_Standard = I2S_Standard_Phillips;
  
  /* 初始化 I2S_DataFormat 成員 */
  I2S_InitStruct->I2S_DataFormat = I2S_DataFormat_16b;
  
  /* 初始化 I2S_MCLKOutput 成員 */
  I2S_InitStruct->I2S_MCLKOutput = I2S_MCLKOutput_Disable;
  
  /* 初始化 I2S_AudioFreq 成員 */
  I2S_InitStruct->I2S_AudioFreq = I2S_AudioFreq_Default;
  
  /* 初始化 I2S_CPOL 成員 */
  I2S_InitStruct->I2S_CPOL = I2S_CPOL_Low;
}

/**
  * @簡述  使能或者失能 SPI 外設.
  * @參數  SPIx: x 為1，2或3用於選定 SPI 外設.
  * @參數  NewState: SPIx 外圍設備的新狀態. 
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 使能 SPI 外設 */
    SPIx->CR1 |= CR1_SPE_Set;
  }
  else
  {
    /* 失能 SPI 外設 */
    SPIx->CR1 &= CR1_SPE_Reset;
  }
}

/**
  * @簡述  使能或禁止指定的 I2S 外設 (在 I2S 模式).
  * @參數  SPIx: x為1，2或3用於選定 SPI 外設.
  * @參數  NewState: SPIx 外圍設備的新狀態. 
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_SPI_23_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 使能選定的 SPI 外設 (在 I2S 模式) */
    SPIx->I2SCFGR |= I2SCFGR_I2SE_Set;
  }
  else
  {
    /* 失能選定的 SPI 外設 (在 I2S 模式) */
    SPIx->I2SCFGR &= I2SCFGR_I2SE_Reset;
  }
}

/**
  * @簡述  使能或者失能指定的 SPI/I2S 中斷.
  * @參數  SPIx: x 可以是
  *            - 1, 2 或 3 在 SPI 模式 
  *            - 2 或 3 在 I2S 模式
  * @參數  SPI_I2S_IT: 指定的中斷源. 
  *          這個參數可以是下面的值之一:
  *          SPI_I2S_IT_TXE:  發送緩存空中斷
  *          SPI_I2S_IT_RXNE: 接收緩存非空中斷
  *          SPI_I2S_IT_ERR:  錯誤中斷
  * @參數  NewState: 指定的 SPI/I2S 中斷的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @retval None
  */
void SPI_I2S_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState)
{
  uint16_t itpos = 0, itmask = 0 ;
  /* 檢查參數 */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_SPI_I2S_CONFIG_IT(SPI_I2S_IT));

  /* 得到 SPI/I2S 中斷索引 */
  itpos = SPI_I2S_IT >> 4;

  /* 設置 IT */
  itmask = (uint16_t)1 << (uint16_t)itpos;

  if (NewState != DISABLE)
  {
    /* 使能 SPI/I2S 中斷 */
    SPIx->CR2 |= itmask;
  }
  else
  {
    /* 失能 SPI/I2S 中斷 */
    SPIx->CR2 &= (uint16_t)~itmask;
  }
}

/**
  * @簡述  使能或者失能指定 SPIx/I2Sx 的DMA請求.
  * @參數  SPIx: x 可以是
  *             - 1, 2 或 3 在 SPI 模式 
  *             - 2 或 3 在 I2S 模式
  * @參數  SPI_I2S_DMAReq: 指定的 SPI/I2S DMA 請求. 
  *          這個參數可以是下面任意值的組合:
  *          SPI_I2S_DMAReq_Tx: 發送緩衝 DMA 傳輸請求
  *          SPI_I2S_DMAReq_Rx: 接收緩衝 DMA 傳輸請求
  * @參數  NewState: 選定的 SPI/I2S DMA 請求的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @retval None
  */
void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_SPI_I2S_DMAREQ(SPI_I2S_DMAReq));
  if (NewState != DISABLE)
  {
    /* 使能選定的 SPI/I2S DMA 請求 */
    SPIx->CR2 |= SPI_I2S_DMAReq;
  }
  else
  {
    /* 失能選定的 SPI/I2S DMA 請求 */
    SPIx->CR2 &= (uint16_t)~SPI_I2S_DMAReq;
  }
}

/**
  * @簡述  通過 SPIx/I2Sx 外設發送數據.
  * @參數  SPIx: x 可以是
  *            - 1, 2 或 3 在 SPI 模式 
  *            - 2 or 3 在 I2S 模式
  * @參數  Data : 待發送的數據.
  * @返回  沒有
  */
void SPI_I2S_SendData(SPI_TypeDef* SPIx, uint16_t Data)
{
  /* 檢查參數 */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  
  /* 把數據寫入 DR 寄存器發送 */
  SPIx->DR = Data;
}

/**
  * @簡述  返回最近從 SPIx/I2Sx 外部設備接收的數據. 
  * @參數  SPIx: x 可以是
  *            - 1, 2 或 3 在 SPI 模式 
  *            - 2 或 3 在 I2S 模式
  * @返回  接收的數據.
  */
uint16_t SPI_I2S_ReceiveData(SPI_TypeDef* SPIx)
{
  /* 檢查參數 */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  
  /* 返回 DR 寄存器的數據 */
  return SPIx->DR;
}

/**
  * @簡述  為選定的 SPI 軟件配置內部 NSS 管腳.
  * @參數  SPIx: x 為1，2或3用於選定SPI外設.
  * @參數  SPI_NSSInternalSoft: 指定的 SPI NSS 內部狀態.
  *          這個參數可以是下面的值之一:
  *          SPI_NSSInternalSoft_Set:   設置 NSS 內部引腳
  *          SPI_NSSInternalSoft_Reset: 復位 NSS 內部引腳
  * @返回  沒有
  */
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft)
{
  /* 檢查參數 */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_NSS_INTERNAL(SPI_NSSInternalSoft));
  if (SPI_NSSInternalSoft != SPI_NSSInternalSoft_Reset)
  {
    /* 軟件設置 NSS 內部引腳 */
    SPIx->CR1 |= SPI_NSSInternalSoft_Set;
  }
  else
  {
    /* 軟件復位 NSS 內部引腳 */
    SPIx->CR1 &= SPI_NSSInternalSoft_Reset;
  }
}

/**
  * @簡述  使能或者失能指定的 SPI SS 輸出.
  * @參數  SPIx: x 為1，2或3用於選定 SPI 外設.
  * @參數  NewState: 選定的 SPI SS 輸出的新狀態. 
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 使能指定的 SPI SS 輸出 */
    SPIx->CR2 |= CR2_SSOE_Set;
  }
  else
  {
    /* 失能指定的 SPI SS 輸出 */
    SPIx->CR2 &= CR2_SSOE_Reset;
  }
}

/**
  * @簡述  設置選定的 SPI 數據大小.
  * @參數  SPIx: x 為1，2或3用於選定 SPI 外設.
  * @參數  SPI_DataSize: 指定的 SPI 數據大小.
  *          這個參數可以是下面的值之一:
  *          SPI_DataSize_16b: 設置數據大小為16位
  *          SPI_DataSize_8b:  設置數據大小為 8位
  * @返回  沒有
  */
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize)
{
  /* 檢查參數 */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_DATASIZE(SPI_DataSize));
  /* 清除 DFF 位 */
  SPIx->CR1 &= (uint16_t)~SPI_DataSize_16b;
  /* 設置新的 DFF 位的值 */
  SPIx->CR1 |= SPI_DataSize;
}

/**
  * @簡述  傳送某個 SPI 的 CRC 校驗值.
  * @參數  SPIx: x 為1，2或3用於選定SPI外設.
  * @返回  沒有
  */
void SPI_TransmitCRC(SPI_TypeDef* SPIx)
{
  /* 檢查參數 */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  
  /* 使能選中的 SPI CRC 發送 */
  SPIx->CR1 |= CR1_CRCNext_Set;
}

/**
  * @簡述  使能或者失能指定 SPI 的傳輸字 CRC 值計算.
  * @參數  SPIx: x 為1，2或3用於選定SPI外設.
  * @參數  NewState: 選定 SPI 接口的 CRC 計算的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 使能選定的 SPI CRC 計算 */
    SPIx->CR1 |= CR1_CRCEN_Set;
  }
  else
  {
    /* 失能選定的 SPI CRC 計算 */
    SPIx->CR1 &= CR1_CRCEN_Reset;
  }
}

/**
  * @簡述  返回指定 SPI 發送或接收的 CRC 值.
  * @參數  SPIx: x 為1，2或3用於選定 SPI 外設.
  * @參數  SPI_CRC: 將被讀取的 CRC 寄存器.
  *          這個參數可以是下面的值之一:
  *          SPI_CRC_Tx: 選擇 Tx CRC 寄存器
  *          SPI_CRC_Rx: 選擇 Rx CRC 寄存器
  * @返回  選定的 CRC 寄存器的值.
  */
uint16_t SPI_GetCRC(SPI_TypeDef* SPIx, uint8_t SPI_CRC)
{
  uint16_t crcreg = 0;
  /* 檢查參數 */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_CRC(SPI_CRC));
  if (SPI_CRC != SPI_CRC_Rx)
  {
    /* 得到 Tx CRC 寄存器的值 */
    crcreg = SPIx->TXCRCR;
  }
  else
  {
    /* 得到 Rx CRC 寄存器的值 */
    crcreg = SPIx->RXCRCR;
  }
  /* 返回指定的 CRC 寄存器的值 */
  return crcreg;
}

/**
  * @簡述  返回指定 SPI 的 CRC 多項式寄存器值.
  * @參數  SPIx: x 為1，2或3用於選定SPI外設.
  * @返回  指定的 CRC 多項式寄存器值.
  */
uint16_t SPI_GetCRCPolynomial(SPI_TypeDef* SPIx)
{
  /* 檢查參數 */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  
  /* 返回指定 CRC 多項式寄存器值 */
  return SPIx->CRCPR;
}

/**
  * @簡述  選擇指定 SPI 在雙向模式下的數據傳輸方向.
  * @參數  SPIx: x 為1，2或3用於選定SPI外設.
  * @參數  SPI_Direction: 在雙向模式中的數據傳輸方向. 
  *          這個參數可以是下面的值之一:
  *          SPI_Direction_Tx: 選擇 Tx 傳送方向
  *          SPI_Direction_Rx: 選擇 Rx 接收方向
  * @返回  沒有
  */
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction)
{
  /* 檢查參數 */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_DIRECTION(SPI_Direction));
  if (SPI_Direction == SPI_Direction_Tx)
  {
    /* 設置只發送模式 */
    SPIx->CR1 |= SPI_Direction_Tx;
  }
  else
  {
    /* 設置只接收模式 */
    SPIx->CR1 &= SPI_Direction_Rx;
  }
}

/**
  * @簡述  檢查指定的 SPI/I2S 標記是否被置位.
  * @參數  SPIx: x 可以是
  *            - 1, 2 或 3 在 SPI 模式 
  *            - 2 或 3 在 I2S 模式
  * @參數  SPI_I2S_FLAG: 指定的 SPI/I2S 標誌. 
  *          這個參數可以是下面的值之一:
  *          SPI_I2S_FLAG_TXE:  傳輸緩衝為空標誌.
  *          SPI_I2S_FLAG_RXNE: 接收緩衝不空標誌.
  *          SPI_I2S_FLAG_BSY:  忙標誌.
  *          SPI_I2S_FLAG_OVR:  溢出標誌.
  *          SPI_FLAG_MODF:     模式錯誤標誌.
  *          SPI_FLAG_CRCERR:   CRC 校驗錯誤標誌.
  *          I2S_FLAG_UDR:      空棧讀出錯標誌.
  *          I2S_FLAG_CHSIDE:   通道邊界標誌.
  * @返回  SPI_I2S_FLAG 的新狀態 (SET 或 RESET).
  */
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* 檢查參數 */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_I2S_GET_FLAG(SPI_I2S_FLAG));
  /* 檢查指定的 SPI/I2S 標誌狀態 */
  if ((SPIx->SR & SPI_I2S_FLAG) != (uint16_t)RESET)
  {
    /* 設置 SPI_I2S_FLAG */
    bitstatus = SET;
  }
  else
  {
    /* 復位 SPI_I2S_FLAG */
    bitstatus = RESET;
  }
  /* 返回 SPI_I2S_FLAG 狀態 */
  return  bitstatus;
}

/**
  * @簡述  清除 SPIx CRC 錯誤 (CRCERR) 標誌.
  * @參數  SPIx: x 可以是
  *            - 1, 2 或 3 在 SPI 模式 
  * @參數  SPI_I2S_FLAG: 指定要清除的 SPI 標誌. 
  *           這個函數僅僅用於清除 CRCERR 標誌.
  * @註解
*        - OVR (過速錯誤)中斷掛起位可以被軟件按順序清除: 一個讀  
*          SPI_DR寄存器操作 (SPI_I2S_ReceiveData()) 跟著一個讀  
*          SPI_SR寄存器操作 (SPI_I2S_GetITStatus()).
*        - UDR (空棧讀錯誤) 中斷掛起位可以被一個讀SPI_SR寄存器操
*          作清除(SPI_I2S_GetITStatus())。
*        - MODF (模式錯誤) 中斷掛起位被軟件按順序清除:一個讀/寫 
*          SPI_SR寄存器操作(SPI_I2S_GetITStatus())跟著一個寫SPI_CR1 
*          寄存器操作 (SPI_Cmd() 使能 SPI).  
  * @返回  沒有
  */
void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG)
{
  /* 檢查參數 */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_I2S_CLEAR_FLAG(SPI_I2S_FLAG));
    
    /* 清除選擇的 SPI CRC 錯誤 (CRCERR) 標誌 */
    SPIx->SR = (uint16_t)~SPI_I2S_FLAG;
}

/**
  * @簡述  檢查指定的的 SPI/I2S 中斷是否發生了.
  * @參數  SPIx: x 可以是
  *            - 1, 2 或 3 在 SPI 模式 
  *            - 2 或 3 在 I2S 模式
  * @參數  SPI_I2S_IT: 待檢查的 SPI/I2S 中斷源. 
  *          這個參數可以是下面的值之一:
  *          SPI_I2S_IT_TXE:  傳輸緩衝為空中斷.
  *          SPI_I2S_IT_RXNE: 接收緩衝不空中斷.
  *          SPI_I2S_IT_OVR:  溢出中斷.
  *          SPI_IT_MODF:     模式錯誤中斷.
  *          SPI_IT_CRCERR:   CRC 校驗錯誤中斷.
  *          I2S_IT_UDR:      空棧讀錯誤中斷.
  * @返回  SPI_I2S_IT 的新狀態 (SET 或 RESET).
  */
ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT)
{
  ITStatus bitstatus = RESET;
  uint16_t itpos = 0, itmask = 0, enablestatus = 0;

  /* 檢查參數 */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_I2S_GET_IT(SPI_I2S_IT));

  /* 得到 SPI/I2S 中斷索引 */
  itpos = 0x01 << (SPI_I2S_IT & 0x0F);

  /* 得到 SPI/I2S 中斷號 */
  itmask = SPI_I2S_IT >> 4;

  /* 設置中斷號 */
  itmask = 0x01 << itmask;

  /* 取得 SPI_I2S_IT 使能狀態位 */
  enablestatus = (SPIx->CR2 & itmask) ;

  /* 檢查指定的 SPI/I2S 中斷狀態 */
  if (((SPIx->SR & itpos) != (uint16_t)RESET) && enablestatus)
  {
    /* 設置 SPI_I2S_IT */
    bitstatus = SET;
  }
  else
  {
    /* 復位 SPI_I2S_IT */
    bitstatus = RESET;
  }
  /* 返回 SPI_I2S_IT 狀態 */
  return bitstatus;
}

/**
  * @簡述  清除指定的 SPI CRC 錯誤 (CRCERR) 中斷掛起位.
  * @參數  SPIx: x 可以是
  *            - 1, 2 或 3 在 SPI 模式 
  * @參數  SPI_I2S_IT: 清除指定的中斷掛起位.
  *           這個函數只清除 CRCERR 中斷掛起位.   
  * @note
*          - OVR (過速錯誤)中斷掛起位可以被軟件按順序清除: 一個讀  
*            SPI_DR寄存器操作 (SPI_I2S_ReceiveData()) 跟著一個讀  
*            SPI_SR寄存器操作 (SPI_I2S_GetITStatus()).
*          - UDR (空棧讀錯誤) 中斷掛起位可以被一個讀SPI_SR寄存器操
*            作清除(SPI_I2S_GetITStatus())。
*          - MODF (模式錯誤) 中斷掛起位被軟件按順序清除:一個讀/寫 
*            SPI_SR寄存器操作(SPI_I2S_GetITStatus())跟著一個寫SPI_CR1 
*            寄存器操作 (SPI_Cmd() 使能 SPI).  
  * @返回  沒有
  */
void SPI_I2S_ClearITPendingBit(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT)
{
  uint16_t itpos = 0;
  /* 檢查參數 */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_I2S_CLEAR_IT(SPI_I2S_IT));

  /* 得到 SPI 中斷索引 */
  itpos = 0x01 << (SPI_I2S_IT & 0x0F);

  /* 清除指定的 SPI CRC 錯誤 (CRCERR) 中斷掛起位 */
  SPIx->SR = (uint16_t)~itpos;
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
