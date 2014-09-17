/**
  ******************************************************************************
  * @文件    stm32f10x_rcc.c
  * @作者    MCD 應用程序組
  * @版本    V3.1.0
  * @日期    06/19/2009
  * @brief   這個文件 提供所有 RCC 固件函數.
  * @翻譯    ANSON/sweet1985 Email:airanson110@126.com
  * @日期    03/07/2009
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
#include "stm32f10x_rcc.h"

/* 自用類型 --------------------------------------------------------------*/
/* 自用定義 --------------------------------------------------------------*/

/* ------------ RCC registers bit address in the alias region ----------- */
#define RCC_OFFSET                (RCC_BASE - PERIPH_BASE)

/* --- CR 寄存器 ---*/

/* Alias word address of HSION bit */
#define CR_OFFSET                 (RCC_OFFSET + 0x00)
#define HSION_BitNumber           0x00
#define CR_HSION_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (HSION_BitNumber * 4))

/* Alias word address of PLLON bit */
#define PLLON_BitNumber           0x18
#define CR_PLLON_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PLLON_BitNumber * 4))

#ifdef STM32F10X_CL
 /* Alias word address of PLL2ON bit */
 #define PLL2ON_BitNumber          0x1A
 #define CR_PLL2ON_BB              (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PLL2ON_BitNumber * 4))

 /* Alias word address of PLL3ON bit */
 #define PLL3ON_BitNumber          0x1C
 #define CR_PLL3ON_BB              (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PLL3ON_BitNumber * 4))
#endif /* STM32F10X_CL */ 

/* Alias word address of CSSON bit */
#define CSSON_BitNumber           0x13
#define CR_CSSON_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (CSSON_BitNumber * 4))

/* --- CFGR 寄存器 ---*/

/* Alias word address of USBPRE bit */
#define CFGR_OFFSET               (RCC_OFFSET + 0x04)

#ifndef STM32F10X_CL
 #define USBPRE_BitNumber          0x16
 #define CFGR_USBPRE_BB            (PERIPH_BB_BASE + (CFGR_OFFSET * 32) + (USBPRE_BitNumber * 4))
#else
 #define OTGFSPRE_BitNumber        0x16
 #define CFGR_OTGFSPRE_BB          (PERIPH_BB_BASE + (CFGR_OFFSET * 32) + (OTGFSPRE_BitNumber * 4))
#endif /* STM32F10X_CL */ 

/* --- BDCR 寄存器 ---*/

/* Alias word address of RTCEN bit */
#define BDCR_OFFSET               (RCC_OFFSET + 0x20)
#define RTCEN_BitNumber           0x0F
#define BDCR_RTCEN_BB             (PERIPH_BB_BASE + (BDCR_OFFSET * 32) + (RTCEN_BitNumber * 4))

/* Alias word address of BDRST bit */
#define BDRST_BitNumber           0x10
#define BDCR_BDRST_BB             (PERIPH_BB_BASE + (BDCR_OFFSET * 32) + (BDRST_BitNumber * 4))

/* --- CSR 寄存器 ---*/

/* Alias word address of LSION bit */
#define CSR_OFFSET                (RCC_OFFSET + 0x24)
#define LSION_BitNumber           0x00
#define CSR_LSION_BB              (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (LSION_BitNumber * 4))

#ifdef STM32F10X_CL
/* --- CFGR2 寄存器 ---*/

 /* Alias word address of I2S2SRC bit */
 #define CFGR2_OFFSET              (RCC_OFFSET + 0x2C)
 #define I2S2SRC_BitNumber         0x11
 #define CFGR2_I2S2SRC_BB          (PERIPH_BB_BASE + (CFGR2_OFFSET * 32) + (I2S2SRC_BitNumber * 4))

 /* Alias word address of I2S3SRC bit */
 #define I2S3SRC_BitNumber         0x12
 #define CFGR2_I2S3SRC_BB          (PERIPH_BB_BASE + (CFGR2_OFFSET * 32) + (I2S3SRC_BitNumber * 4))
#endif /* STM32F10X_CL */

/* ---------------------- RCC 寄存器 bit mask ------------------------ */

/* CR register bit mask */
#define CR_HSEBYP_Reset           ((uint32_t)0xFFFBFFFF)
#define CR_HSEBYP_Set             ((uint32_t)0x00040000)
#define CR_HSEON_Reset            ((uint32_t)0xFFFEFFFF)
#define CR_HSEON_Set              ((uint32_t)0x00010000)
#define CR_HSITRIM_Mask           ((uint32_t)0xFFFFFF07)

/* CFGR register bit mask */
#ifndef STM32F10X_CL
 #define CFGR_PLL_Mask            ((uint32_t)0xFFC0FFFF)
#else
 #define CFGR_PLL_Mask           ((uint32_t)0xFFC2FFFF)
#endif /* STM32F10X_CL */ 

#define CFGR_PLLMull_Mask         ((uint32_t)0x003C0000)
#define CFGR_PLLSRC_Mask          ((uint32_t)0x00010000)
#define CFGR_PLLXTPRE_Mask        ((uint32_t)0x00020000)
#define CFGR_SWS_Mask             ((uint32_t)0x0000000C)
#define CFGR_SW_Mask              ((uint32_t)0xFFFFFFFC)
#define CFGR_HPRE_Reset_Mask      ((uint32_t)0xFFFFFF0F)
#define CFGR_HPRE_Set_Mask        ((uint32_t)0x000000F0)
#define CFGR_PPRE1_Reset_Mask     ((uint32_t)0xFFFFF8FF)
#define CFGR_PPRE1_Set_Mask       ((uint32_t)0x00000700)
#define CFGR_PPRE2_Reset_Mask     ((uint32_t)0xFFFFC7FF)
#define CFGR_PPRE2_Set_Mask       ((uint32_t)0x00003800)
#define CFGR_ADCPRE_Reset_Mask    ((uint32_t)0xFFFF3FFF)
#define CFGR_ADCPRE_Set_Mask      ((uint32_t)0x0000C000)

/* CSR register bit mask */
#define CSR_RMVF_Set              ((uint32_t)0x01000000)

#ifdef STM32F10X_CL
/* CFGR2 register bit mask */
 #define CFGR2_PREDIV1SRC         ((uint32_t)0x00010000)
 #define CFGR2_PREDIV1            ((uint32_t)0x0000000F)
 #define CFGR2_PREDIV2            ((uint32_t)0x000000F0)
 #define CFGR2_PLL2MUL            ((uint32_t)0x00000F00)
 #define CFGR2_PLL3MUL            ((uint32_t)0x0000F000)
#endif /* STM32F10X_CL */ 

/* RCC Flag Mask */
#define FLAG_Mask                 ((uint8_t)0x1F)

#ifndef HSI_Value
/* Typical Value of the HSI in Hz */
 #define HSI_Value                 ((uint32_t)8000000)
#endif /* HSI_Value */

/* CIR register byte 2 (Bits[15:8]) base address */
#define CIR_BYTE2_ADDRESS         ((uint32_t)0x40021009)

/* CIR register byte 3 (Bits[23:16]) base address */
#define CIR_BYTE3_ADDRESS         ((uint32_t)0x4002100A)

/* CFGR register byte 4 (Bits[31:24]) base address */
#define CFGR_BYTE4_ADDRESS        ((uint32_t)0x40021007)

/* BDCR register base address */
#define BDCR_ADDRESS              (PERIPH_BASE + BDCR_OFFSET)

#ifndef HSEStartUp_TimeOut
/* Time out for HSE start up */
 #define HSEStartUp_TimeOut        ((uint16_t)0x0500)
#endif /* HSEStartUp_TimeOut */

/* 自用宏 ------------------------------------------------------------*/
/* 自用變量 ----------------------------------------------------------*/

static __I uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};
static __I uint8_t ADCPrescTable[4] = {2, 4, 6, 8};

/* 自用函數原型 ------------------------------------------------------*/
/* 自用函數 ----------------------------------------------------------*/


/**
  * @簡述  將外設RCC寄存器重設為缺省值.
  * @參數  沒有
  * @返回  沒有
  */
void RCC_DeInit(void)
{
  /* 置位HSION (內部<8MHz>高速時鐘使能) */
  RCC->CR |= (uint32_t)0x00000001;

  /* 復位 SW, HPRE, PPRE1, PPRE2, ADCPRE , MCO 位 */
  /* (HIS被選作系統時鐘，HSI振蕩器被用作系統時鐘，SYSCLK未被分頻，HCLK未被分頻，
     ADC預分頻器<PLCK2>被2分頻，HSI振蕩器時鐘/2被選作PLL輸入時鐘)，微控制器無時鐘輸出 */
#ifndef STM32F10X_CL
  RCC->CFGR &= (uint32_t)0xF8FF0000;   /* ?在保留區置1 */
#else
  RCC->CFGR &= (uint32_t)0xF0FF0000;   /* ?在保留區清0 */
#endif /* STM32F10X_CL */   
  
  /* 復位 HSEON, CSSON, PLLON 位 (PLL禁用，時鐘檢測器禁用，HSE振蕩器禁用) */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* 復位 HSEBYP 位 (外部1~25MHz振蕩器未被旁路) */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* 復位 PLLSRC, PLLXTPRE, PLLMUL , USBPRE/OTGFSPRE 位 */
  /*(USB預分頻器為PLL時鐘1.5分頻，PLL倍頻參數X2，HSE未被分頻作為PLL輸入，HSI振蕩器時鐘/2被當作PLL輸入) */
  RCC->CFGR &= (uint32_t)0xFF80FFFF;

#ifndef STM32F10X_CL
  /* 使所有時鐘中斷失能 */
  RCC->CIR = 0x009F0000;
#else
  /* 復位 PLL2ON , PLL3ON 位 () */
  RCC->CR &= (uint32_t)0xEBFFFFFF;

  /* 使所有時鐘中斷失能  */
  RCC->CIR = 0x00FF0000;

  /* 復位 CFGR2 寄存器 */
  RCC->CFGR2 = 0x00000000;
#endif /* STM32F10X_CL */
}

/**
  * @簡述  配置外部高速振蕩器 (HSE).
  * @註解  如果 HSE 被直接使用或者通過 PLL 作為系統時鐘，則它不能停止.
  * @參數  RCC_HSE: 指定 HSE 新的狀態.
  *                 這個參數可以選擇下面的一項:
  *             RCC_HSE_OFF: HSE 振蕩器 OFF
  *             RCC_HSE_ON : HSE 振蕩器 ON
  *             RCC_HSE_Bypass: HSE 振蕩器旁路使用外部時鐘
  * @返回  沒有
  */
void RCC_HSEConfig(uint32_t RCC_HSE)
{
  /* 檢查參數 */
  assert_param(IS_RCC_HSE(RCC_HSE));
  /* 復位 HSEON , HSEBYP 位 在配置 HSE 以前 ------------------*/
  /* Reset HSEON bit (禁用 HSE 振蕩器)*/
  RCC->CR &= CR_HSEON_Reset;
  /* Reset HSEBYP bit (外部1~25MHz振蕩器未被旁路)*/
  RCC->CR &= CR_HSEBYP_Reset;
  /* 配置 HSE (RCC_HSE_OFF 已經被code核心代碼覆蓋了) */
  switch(RCC_HSE)
  {
    case RCC_HSE_ON:
      /* Set HSEON bit (打開 HSE 振蕩器)*/
      RCC->CR |= CR_HSEON_Set;
      break;
      
    case RCC_HSE_Bypass:
      /* Set HSEBYP and HSEON bits (禁用 HSE 振蕩器被外部1~25MHz振蕩器和外部時鐘旁路)*/
      RCC->CR |= CR_HSEBYP_Set | CR_HSEON_Set;
      break;
      
    default:
      break;
  }
}

/**
  * @簡述  等待 HSE 啟動.
  * @參數  沒有
  * @返回  一個ErrorStatus枚舉值:
  *        SUCCESS: HSE 振蕩器已經穩定並且可以使用
  *        ERROR  : HSE 振蕩器尚未準備好
  */
ErrorStatus RCC_WaitForHSEStartUp(void)
{
  __IO uint32_t StartUpCounter = 0;
  ErrorStatus status = ERROR;
  FlagStatus HSEStatus = RESET;
  
  /* 等待 HSE 準備好和超時的時間到來 */
  do
  {
    HSEStatus = RCC_GetFlagStatus(RCC_FLAG_HSERDY);
    StartUpCounter++;  
  } while((StartUpCounter != HSEStartUp_TimeOut) && (HSEStatus == RESET));
  
  if (RCC_GetFlagStatus(RCC_FLAG_HSERDY) != RESET)
  {
    status = SUCCESS;
  }
  else
  {
    status = ERROR;
  }  
  return (status);
}

/**
  * @簡述  調整內部高速振蕩器 (HSI) 標度值.
  * @參數  HSICalibrationValue: 校正標度值，這個參數一定是在0到0x1F之間的值.
  * @返回  沒有
  */
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue)
{
  uint32_t tmpreg = 0;
  /* 檢查參數 */
  assert_param(IS_RCC_CALIBRATION_VALUE(HSICalibrationValue));
  tmpreg = RCC->CR;
  /* 清除 HSITRIM[4:0] 位 (默認值是16使 HIS 嚴格工作在8MHz) */
  tmpreg &= CR_HSITRIM_Mask;
  /* 設置 HSITRIM[4:0] 位，根據 HSICalibrationValue 的值 */
  tmpreg |= (uint32_t)HSICalibrationValue << 3;
  /* 存儲新的值 */
  RCC->CR = tmpreg;
}

/**
  * @簡述  使能或失能內部高速振蕩器 (HSI).
  * @註解  如果 HSE 被直接使用或者通過 PLL 作為系統時鐘，則它不能停止.
  * @參數  NewState: HSI 的新狀態. 
  *                 這個參數可取: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void RCC_HSICmd(FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CR_HSION_BB = (uint32_t)NewState;
}

/**
  * @簡述  設置PLL時鐘源及倍頻係數.
  * @註解  這個函數僅僅應用在 PLL 被禁止的時候.
  * @參數  RCC_PLLSource: 指定進入 PLL 的時鐘源.
  *                       STM32_互聯繫列微處理器, 這個參數可取下列的值:
  *                                      RCC_PLLSource_HSI_Div2: PLL 時鐘輸入等於 HSI 振蕩器時鐘二分頻
  *                                      RCC_PLLSource_PREDIV1: PREDIV1 clock selected as PLL clock entry
  *                       其它_STM32_微處理器, 這個參數可取下列的值:
  *                                      RCC_PLLSource_HSI_Div2: PLL 時鐘輸入等於 HSI 振蕩器時鐘二分頻
  *                                      RCC_PLLSource_HSE_Div1: PLL 時鐘輸入等於 HSE 振蕩器時鐘
  *                                      RCC_PLLSource_HSE_Div2: PLL 時鐘輸入等於 HSE 振蕩器時鐘二分頻
  * @參數  RCC_PLLMul: 指定 PLL 倍頻係數.
  *                    STM32_Connectivity_line_devices, 這個參數可以是 RCC_PLLMul_x x可以取{[4,9], 6_5}
  *                    other_STM32_devices, 這個參數可以是 RCC_PLLMul_x x可以取:[2,16]
  * @返回  沒有
  */
void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul)
{
  uint32_t tmpreg = 0;

  /* 檢查參數 */
  assert_param(IS_RCC_PLL_SOURCE(RCC_PLLSource));
  assert_param(IS_RCC_PLL_MUL(RCC_PLLMul));

  tmpreg = RCC->CFGR;
  /* 清 PLLSRC, PLLXTPRE , PLLMUL[3:0] 位 */
  tmpreg &= CFGR_PLL_Mask;
  /* 設置 PLL 配置位 */
  tmpreg |= RCC_PLLSource | RCC_PLLMul;
  /* 存儲新值 */
  RCC->CFGR = tmpreg;
}

/**
  * @簡述  使能或失能 PLL.
  * @註解  如果 PLL 作為系統時鐘，則它不能停止.
  * @參數  NewState: PLL 的新狀態. 這個參數可以取: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void RCC_PLLCmd(FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) CR_PLLON_BB = (uint32_t)NewState;
}

#ifdef STM32F10X_CL
/**
  * @簡述  配置 PREDIV1 分頻參數.
  * @註解 
  *   - 這個函數僅僅應用在 PLL 被禁止的時候.
  *   - 這個函數僅僅應用在 STM32 互聯繫列微處理器.
  * @參數  RCC_PREDIV1_Source: 指定 PREDIV1 時鐘源.
  *                            這個參數可以取下列值中的一個:
  *                            RCC_PREDIV1_Source_HSE: HSE 作為 PREDIV1 時鐘
  *                            RCC_PREDIV1_Source_PLL2: PLL2 作為 PREDIV1 時鐘
  * @參數  RCC_PREDIV1_Div: 選定 PREDIV1 分頻係數.
  *                         這個參數 RCC_PREDIV1_Divx 中 x可以取:[1,16]
  * @返回  沒有
  */
void RCC_PREDIV1Config(uint32_t RCC_PREDIV1_Source, uint32_t RCC_PREDIV1_Div)
{
  uint32_t tmpreg = 0;
  
  /* 檢查參數 */
  assert_param(IS_RCC_PREDIV1_SOURCE(RCC_PREDIV1_Source));
  assert_param(IS_RCC_PREDIV1(RCC_PREDIV1_Div));

  tmpreg = RCC->CFGR2;
  /* 清 PREDIV1[3:0] 和 PREDIV1SRC 位 */
  tmpreg &= ~(CFGR2_PREDIV1 | CFGR2_PREDIV1SRC);
  /* Set the PREDIV1 clock source and division factor */
  tmpreg |= RCC_PREDIV1_Source | RCC_PREDIV1_Div ;
  /* 存儲新值 */
  RCC->CFGR2 = tmpreg;
}


/**
  * @簡述  配置 PREDIV2 分頻參數.
  * @註解 
  *   - 這個函數僅僅應用在 PLL2,PLL3 被禁止的時候.
  *   - 這個函數僅僅應用在 STM32 互聯繫列微處理器.
  * @參數  RCC_PREDIV2_Div: 選定 PREDIV2 分頻係數.
  *                         這個參數 RCC_PREDIV2_Divx 中 x可以取:[1,16]
  * @返回  沒有
  */
void RCC_PREDIV2Config(uint32_t RCC_PREDIV2_Div)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RCC_PREDIV2(RCC_PREDIV2_Div));

  tmpreg = RCC->CFGR2;
  /* Clear PREDIV2[3:0] bits */
  tmpreg &= ~CFGR2_PREDIV2;
  /* Set the PREDIV2 division factor */
  tmpreg |= RCC_PREDIV2_Div;
  /* Store the new value */
  RCC->CFGR2 = tmpreg;
}

/**
  * @簡述  配置 PLL2 倍頻係數.
  * @註解
  *   - 這個函數僅僅應用在 PLL2 被禁止的時候.
  *   - 這個函數僅僅應用在 STM32 互聯繫列微處理器.
  * @參數  RCC_PLL2Mul: 指定 PLL2 倍頻係數.
  *                     這個參數 RCC_PLL2Mul_x 中 x可以取:{[8,14], 16, 20}
  * @返回  沒有
  */
void RCC_PLL2Config(uint32_t RCC_PLL2Mul)
{
  uint32_t tmpreg = 0;

  /* 檢查參數 */
  assert_param(IS_RCC_PLL2_MUL(RCC_PLL2Mul));

  tmpreg = RCC->CFGR2;
  /* 清 PLL2Mul[3:0] 位 */
  tmpreg &= ~CFGR2_PLL2MUL;
  /* 設置 PLL2 配置位 */
  tmpreg |= RCC_PLL2Mul;
  /* 存儲參數 */
  RCC->CFGR2 = tmpreg;
}


/**
  * @簡述  使能或失能 PLL2.
  * @註解 
  *   - 如果 PLL2 被用做系統時鐘，它就不能被禁止
  *     (i.e.它被用作 PLL 時鐘輸入源，就是說被用作系統時鐘).
  *   - 這個函數僅僅應用在 STM32 互聯繫列微處理器.
  * @參數  NewState: PLL2 新的狀態. 這個參數可以取: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void RCC_PLL2Cmd(FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) CR_PLL2ON_BB = (uint32_t)NewState;
}


/**
  * @簡述  配置 PLL3 倍頻係數.
  * @註解
  *   - 這個函數僅僅應用在 PLL3 被禁止的時候.
  *   - 這個函數僅僅應用在 STM32 互聯繫列微處理器.
  * @參數  RCC_PLL3Mul: 指定 PLL3 倍頻係數.
  *                     這個參數 RCC_PLL3Mul_x 中 x可以取:{[8,14], 16, 20}
  * @返回  沒有
  */
void RCC_PLL3Config(uint32_t RCC_PLL3Mul)
{
  uint32_t tmpreg = 0;

  /* 檢查參數 */
  assert_param(IS_RCC_PLL3_MUL(RCC_PLL3Mul));

  tmpreg = RCC->CFGR2;
  /* 清 PLL3Mul[3:0] 位 */
  tmpreg &= ~CFGR2_PLL3MUL;
  /* 設置 PLL3 配置位 */
  tmpreg |= RCC_PLL3Mul;
  /* 存儲新值 */
  RCC->CFGR2 = tmpreg;
}


/**
  * @簡述  使能或失能 PLL3.
  * @註解  這個函數僅僅應用在 STM32 互聯繫列微處理器.
  * @參數  NewState: PLL3 新的狀態. 這個參數可以取: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void RCC_PLL3Cmd(FunctionalState NewState)
{
  /* Check the parameters */

  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CR_PLL3ON_BB = (uint32_t)NewState;
}
#endif /* STM32F10X_CL */

/**
  * @簡述  配置系統時鐘 (SYSCLK).
  * @參數  RCC_SYSCLKSource: 指定作為系統時鐘的時鐘源.
  *                          這個參數可以選擇下列中的一個:
  *                          RCC_SYSCLKSource_HSI:   選定 HSI 作為系統時鐘
  *                          RCC_SYSCLKSource_HSE:   選定 HSE 作為系統時鐘
  *                          RCC_SYSCLKSource_PLLCLK:選定 PLL 作為系統時鐘
  * @返回  沒有
  */
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource)
{
  uint32_t tmpreg = 0;
  /* 檢查參數 */
  assert_param(IS_RCC_SYSCLK_SOURCE(RCC_SYSCLKSource));
  tmpreg = RCC->CFGR;
  /* 清 SW[1:0] 位  */
  tmpreg &= CFGR_SW_Mask;
  /* 設置 SW[1:0] 位為 RCC_SYSCLKSource 的值 */
  tmpreg |= RCC_SYSCLKSource;
  /* 存儲新值 */
  RCC->CFGR = tmpreg;
}

/**
  * @簡述  獲得用作系統時鐘的時鐘源.
  * @參數  沒有
  * @返回  作為系統時鐘的時鐘源. 
  *        這個返回值可以是下列之中的一個:
  *        0x00: HSI 被用作系統時鐘
  *        0x04: HSE 被用作系統時鐘
  *        0x08: PLL 被用作系統時鐘
  */
uint8_t RCC_GetSYSCLKSource(void)
{
  return ((uint8_t)(RCC->CFGR & CFGR_SWS_Mask));
}

/**
  * @簡述  配置 AHB 時鐘 (HCLK).
  * @參數  RCC_SYSCLK: 定義 AHB 時鐘分頻. 這個時鐘來源於系統時鐘
  *                    這個參數可以取下列值中的一個:
  *                    RCC_SYSCLK_Div1: AHB clock = SYSCLK
  *                    RCC_SYSCLK_Div2: AHB clock = SYSCLK/2
  *                    RCC_SYSCLK_Div4: AHB clock = SYSCLK/4
  *                    RCC_SYSCLK_Div8: AHB clock = SYSCLK/8
  *                    RCC_SYSCLK_Div16: AHB clock = SYSCLK/16
  *                    RCC_SYSCLK_Div64: AHB clock = SYSCLK/64
  *                    RCC_SYSCLK_Div128: AHB clock = SYSCLK/128
  *                    RCC_SYSCLK_Div256: AHB clock = SYSCLK/256
  *                    RCC_SYSCLK_Div512: AHB clock = SYSCLK/512
  * @返回  沒有
  */
void RCC_HCLKConfig(uint32_t RCC_SYSCLK)
{
  uint32_t tmpreg = 0;
  /* 檢查參數 */
  assert_param(IS_RCC_HCLK(RCC_SYSCLK));
  tmpreg = RCC->CFGR;
  /* 清 HPRE[3:0] 位 */
  tmpreg &= CFGR_HPRE_Reset_Mask;
  /* 設置 HPRE[3:0] 位為 RCC_SYSCLK 的值 */
  tmpreg |= RCC_SYSCLK;
  /* 存儲新值 */
  RCC->CFGR = tmpreg;
}

/**
  * @簡述  配置低速 APB 時鐘 (PCLK1).
  * @參數  RCC_HCLK: 配置 APB1 時鐘分頻. 這個時鐘來源於 AHB 時鐘 (HCLK).
  *                  這個參數可以取下列值中的一個:
  *                  RCC_HCLK_Div1: APB1 clock = HCLK
  *                  RCC_HCLK_Div2: APB1 clock = HCLK/2
  *                  RCC_HCLK_Div4: APB1 clock = HCLK/4
  *                  RCC_HCLK_Div8: APB1 clock = HCLK/8
  *                  RCC_HCLK_Div16: APB1 clock = HCLK/16
  * @返回  沒有
  */
void RCC_PCLK1Config(uint32_t RCC_HCLK)
{
  uint32_t tmpreg = 0;
  /* 檢查參數 */
  assert_param(IS_RCC_PCLK(RCC_HCLK));
  tmpreg = RCC->CFGR;
  /* 清 PPRE1[2:0] 位 */
  tmpreg &= CFGR_PPRE1_Reset_Mask;
  /* 設置 PPRE1[2:0] 位為 RCC_HCLK 的值 */
  tmpreg |= RCC_HCLK;
  /* 存儲新值 */
  RCC->CFGR = tmpreg;
}

/**
  * @簡述  配置高速 APB 時鐘 (PCLK2).
  * @參數  RCC_HCLK: 配置 APB2 時鐘分頻. 這個時鐘來源於 AHB 時鐘 (HCLK).
  *                  這個參數可以取下列值中的一個:
  *                  RCC_HCLK_Div1: APB1 clock = HCLK
  *                  RCC_HCLK_Div2: APB1 clock = HCLK/2
  *                  RCC_HCLK_Div4: APB1 clock = HCLK/4
  *                  RCC_HCLK_Div8: APB1 clock = HCLK/8
  *                  RCC_HCLK_Div16: APB1 clock = HCLK/16
  * @返回  沒有
  */
void RCC_PCLK2Config(uint32_t RCC_HCLK)
{
  uint32_t tmpreg = 0;
  /* 檢查參數 */
  assert_param(IS_RCC_PCLK(RCC_HCLK));
  tmpreg = RCC->CFGR;
  /* 清 PPRE2[2:0] 位 */
  tmpreg &= CFGR_PPRE2_Reset_Mask;
  /* 設置 PPRE2[2:0] 位為 RCC_HCLK 的值 */
  tmpreg |= RCC_HCLK << 3;
  /* 存儲新值 */
  RCC->CFGR = tmpreg;
}

/**
  * @簡述  使能或失能指定的 RCC 中斷.
  * @參數  RCC_IT: 待使能或者失能的RCC中斷源.
  * 
  *                 STM32_互聯繫列微處理器, 這個參數可以取下列值中的一個:      
  *                                         RCC_IT_LSIRDY: LSI 準備中斷
  *                                         RCC_IT_LSERDY: LSE 準備中斷
  *                                         RCC_IT_HSIRDY: HSI 準備中斷
  *                                         RCC_IT_HSERDY: HSE 準備中斷
  *                                         RCC_IT_PLLRDY: PLL 準備中斷
  *                                         RCC_IT_PLL2RDY: PLL2 準備中斷
  *                                         RCC_IT_PLL3RDY: PLL3 準備中斷
  * 
  *                    其它_STM32_微處理器, 這個參數可以取下列值中的一個:      
  *                                         RCC_IT_LSIRDY: LSI 準備中斷
  *                                         RCC_IT_LSERDY: LSE 準備中斷
  *                                         RCC_IT_HSIRDY: HSI 準備中斷
  *                                         RCC_IT_HSERDY: HSE 準備中斷
  *                                         RCC_IT_PLLRDY: PLL 準備中斷
  *       
  * @參數  NewState: RCC 中斷新的狀態.
  *                   這個參數可以取: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_RCC_IT(RCC_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* 執行RCC_CIR[12:8]位的字節存取來使能選擇的中斷s */
    *(__IO uint8_t *) CIR_BYTE2_ADDRESS |= RCC_IT;
  }
  else
  {
    /* 執行RCC_CIR[12:8]位的字節存取來禁止選擇的中斷 */
    *(__IO uint8_t *) CIR_BYTE2_ADDRESS &= (uint8_t)~RCC_IT;
  }
}

#ifndef STM32F10X_CL
/**
  * @簡述  配置 USB 時鐘 (USBCLK).
  * @參數  RCC_USBCLKSource: 指定 USB 的時鐘源. 這個時鐘來源於 PLL 輸出.
  *                          這個參數可以取下列值中的一個:
  *                          RCC_USBCLKSource_PLLCLK_1Div5: PLL 時鐘的1.5分頻用作 USB 時鐘源
  *                          RCC_USBCLKSource_PLLCLK_Div1:  PLL 時鐘用作 USB 時鐘源
  * @返回  沒有
  */
void RCC_USBCLKConfig(uint32_t RCC_USBCLKSource)
{
  /* 檢查參數 */
  assert_param(IS_RCC_USBCLK_SOURCE(RCC_USBCLKSource));

  *(__IO uint32_t *) CFGR_USBPRE_BB = RCC_USBCLKSource;
}
#else
/**
  * @簡述  配置 USB OTG FS 時鐘 (OTGFSCLK).
  *        這個函數僅僅應用在 STM32 互聯繫列微處理器.
  * @參數  RCC_OTGFSCLKSource: 指定 USB OTG FS 時鐘源.
  *                            這個時鐘來源於 PLL 的輸出.
  *                            這個參數可以取下列值中的一個:
  *                            RCC_OTGFSCLKSource_PLLVCO_Div3: PLL VCO clock divided by 2 selected as USB OTG FS clock source
  *                            RCC_OTGFSCLKSource_PLLVCO_Div2: PLL VCO clock divided by 2 selected as USB OTG FS clock source
  * @返回  沒有
  */
void RCC_OTGFSCLKConfig(uint32_t RCC_OTGFSCLKSource)
{
  /* 檢查參數 */
  assert_param(IS_RCC_OTGFSCLK_SOURCE(RCC_OTGFSCLKSource));

  *(__IO uint32_t *) CFGR_OTGFSPRE_BB = RCC_OTGFSCLKSource;
}
#endif /* STM32F10X_CL */ 

/**
  * @簡述  配置 ADC 時鐘 (ADCCLK).
  * @參數  RCC_PCLK2: 定義 ADC 時鐘分頻. 這個時鐘來源於 APB2 時鐘 (PCLK2).
  *                                      這個參數可以取下列值中的一個:
  *                                      RCC_PCLK2_Div2: ADC clock = PCLK2/2
  *                                      RCC_PCLK2_Div4: ADC clock = PCLK2/4
  *                                      RCC_PCLK2_Div6: ADC clock = PCLK2/6
  *                                      RCC_PCLK2_Div8: ADC clock = PCLK2/8
  * @返回  沒有
  */
void RCC_ADCCLKConfig(uint32_t RCC_PCLK2)
{
  uint32_t tmpreg = 0;
  /* 檢查參數 */
  assert_param(IS_RCC_ADCCLK(RCC_PCLK2));
  tmpreg = RCC->CFGR;
  /* 清 ADCPRE[1:0] 位 */
  tmpreg &= CFGR_ADCPRE_Reset_Mask;
  /* 設置 ADCPRE[1:0] 位取決於 RCC_PCLK2 的值 */
  tmpreg |= RCC_PCLK2;
  /* 存儲新值 */
  RCC->CFGR = tmpreg;
}

#ifdef STM32F10X_CL
/**
  * @簡述  配置 I2S2 時鐘源(I2S2CLK).
  * @註解
  *   - 這個函數必須在使能I2S2 APB時鐘之前調用.
  *   - 這個函數僅僅應用在 STM32 互聯繫列微處理器.
  * @參數  RCC_I2S2CLKSource: 指定 I2S2 時鐘源.
  *                           這個參數可以取下列值中的一個:
  *                           RCC_I2S2CLKSource_SYSCLK: 系統時鐘作為 I2S2 時鐘源
  *                           RCC_I2S2CLKSource_PLL3_VCO: PLL3 VCO 作為 I2S2 時鐘源
  * @返回  沒有
  */
void RCC_I2S2CLKConfig(uint32_t RCC_I2S2CLKSource)
{
  /* 檢查參數 */
  assert_param(IS_RCC_I2S2CLK_SOURCE(RCC_I2S2CLKSource));

  *(__IO uint32_t *) CFGR2_I2S2SRC_BB = RCC_I2S2CLKSource;
}

/**
  * @簡述  配置 I2S3 時鐘源(I2S2CLK).
  * @註解
  *   - 這個函數必須在使能I2S3 APB時鐘之前調用.
  *   - 這個函數僅僅應用在 STM32 互聯繫列微處理器.
  * @參數  RCC_I2S3CLKSource: 指定 I2S3 時鐘源.
  *                           這個參數可以取下列值中的一個:
  *                           RCC_I2S2CLKSource_SYSCLK: 系統時鐘作為 I2S3 時鐘源
  *                           RCC_I2S2CLKSource_PLL3_VCO: PLL3 VCO 作為 I2S3 時鐘源
  * @返回  沒有
  */
void RCC_I2S3CLKConfig(uint32_t RCC_I2S3CLKSource)
{
  /* 指定參數 */
  assert_param(IS_RCC_I2S3CLK_SOURCE(RCC_I2S3CLKSource));

  *(__IO uint32_t *) CFGR2_I2S3SRC_BB = RCC_I2S3CLKSource;
}
#endif /* STM32F10X_CL */

/**
  * @簡述  配置外部低速振蕩器 (LSE).
  * @參數  RCC_LSE: 指定 LSE 的新狀態.
  *                 這個參數可以取下列值中的一個:
  *                 RCC_LSE_OFF: LSE 振蕩器 OFF
  *                 RCC_LSE_ON: LSE 振蕩器 ON
  *                 RCC_LSE_Bypass: LSE 振蕩器與外部時鐘旁路
  * @返回  沒有
  */
void RCC_LSEConfig(uint8_t RCC_LSE)
{
  /* 檢查參數 */
  assert_param(IS_RCC_LSE(RCC_LSE));
  /* Reset LSEON and LSEBYP bits before configuring the LSE ------------------*/
  /* 復位 LSEON 位 */
  *(__IO uint8_t *) BDCR_ADDRESS = RCC_LSE_OFF;
  /* 復位 LSEBYP 位 */
  *(__IO uint8_t *) BDCR_ADDRESS = RCC_LSE_OFF;
  /* Configure LSE (RCC_LSE_OFF 已經在 code 代碼部分被覆蓋) */
  switch(RCC_LSE)
  {
    case RCC_LSE_ON:
      /* 設置 LSEON 位 */
      *(__IO uint8_t *) BDCR_ADDRESS = RCC_LSE_ON;
      break;
      
    case RCC_LSE_Bypass:
      /* 設置 LSEBYP , LSEON 位 */
      *(__IO uint8_t *) BDCR_ADDRESS = RCC_LSE_Bypass | RCC_LSE_ON;
      break;            
      
    default:
      break;      
  }
}

/**
  * @簡述  使能或失能內部低速振蕩器 (LSI).
  * @註解  如果 IWDG 正在運行，LSI 就不能被禁用.
  * @參數  NewState: LSI 新的狀態. 這個參數可以取: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void RCC_LSICmd(FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CSR_LSION_BB = (uint32_t)NewState;
}

/**
  * @簡述  配置 RTC 時鐘 (RTCCLK).
  * @註解  只要選擇了 RTC 時鐘,RTC時鐘就不能改變直到備份域復位.
  * @參數  RCC_RTCCLKSource: 指定 RTC 時鐘源.
  *                          這個參數可以取下列值中的一個:
  *                          RCC_RTCCLKSource_LSE: LSE 作為 RTC 時鐘
  *                          RCC_RTCCLKSource_LSI: LSI 作為 RTC 時鐘
  *                          RCC_RTCCLKSource_HSE_Div128: HSE 時鐘的 128 分頻作為 RTC 時鐘
  * @返回  沒有
  */
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource)
{
  /* 檢查參數 */
  assert_param(IS_RCC_RTCCLK_SOURCE(RCC_RTCCLKSource));
  /* 指定 RTC 時鐘源 */
  RCC->BDCR |= RCC_RTCCLKSource;
}

/**
  * @簡述  使能或失能 RTC 時鐘.
  * @註解  僅當使用 RCC_RTCCLKConfig 函數選擇 RTC 時鐘後,才使用這個函數.
  * @參數  NewState: RTC 時鐘的新狀態. 這個參數可以取: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void RCC_RTCCLKCmd(FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) BDCR_RTCEN_BB = (uint32_t)NewState;
}

/**
  * @簡述  返回片上時鐘的不同頻率.
  * @參數  RCC_Clocks: 指向包括時鐘頻率的 RCC_ClocksTypeDef 結構的指針.
  * @返回  沒有
  */
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks)
{
  uint32_t tmp = 0, pllmull = 0, pllsource = 0, presc = 0;

#ifdef  STM32F10X_CL
  uint32_t prediv1source = 0, prediv1factor = 0, prediv2factor = 0, pll2mull = 0;
#endif /* STM32F10X_CL */
    
  /* 得到系統時鐘源 -------------------------------------------------------*/
  tmp = RCC->CFGR & CFGR_SWS_Mask;
  
  switch (tmp)
  {
    case 0x00:  /* HSI used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSI_Value;
      break;
    case 0x04:  /* HSE used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSE_Value;
      break;
    case 0x08:  /* PLL used as system clock */

      /* 得到 PLL 時鐘源和倍頻因數 ----------------------*/
      pllmull = RCC->CFGR & CFGR_PLLMull_Mask;
      pllsource = RCC->CFGR & CFGR_PLLSRC_Mask;
      
#ifndef STM32F10X_CL      
      pllmull = ( pllmull >> 18) + 2;
      
      if (pllsource == 0x00)
      {/* HSI 振蕩時鐘的2分頻作為 PLL 時鐘源 */
        RCC_Clocks->SYSCLK_Frequency = (HSI_Value >> 1) * pllmull;
      }
      else
      {/* HSE 作為 PLL 時鐘源 */
        if ((RCC->CFGR & CFGR_PLLXTPRE_Mask) != (uint32_t)RESET)
        {/* HSE 振蕩時鐘被2分頻 */
          RCC_Clocks->SYSCLK_Frequency = (HSE_Value >> 1) * pllmull;
        }
        else
        {
          RCC_Clocks->SYSCLK_Frequency = HSE_Value * pllmull;
        }
      }
#else
      pllmull = pllmull >> 18;
      
      if (pllmull != 0x0D)
      {
         pllmull += 2;
      }
      else
      { /* PLL 倍頻因數 = PLL 輸入時鐘 * 6.5 */
        pllmull = 13 / 2; 
      }
            
      if (pllsource == 0x00)
      {/* HSI 振蕩時鐘被2分頻作為 PLL 時鐘源 */
        RCC_Clocks->SYSCLK_Frequency = (HSI_Value >> 1) * pllmull;
      }
      else
      {/* PREDIV1 作為 PLL 時鐘源 */
        
        /* 指定 PREDIV1 時鐘源和分頻係數 */
        prediv1source = RCC->CFGR2 & CFGR2_PREDIV1SRC;
        prediv1factor = (RCC->CFGR2 & CFGR2_PREDIV1) + 1;
        
        if (prediv1source == 0)
        { /* HSE 振蕩時鐘被選定作為 PREDIV1 時鐘源 */
          RCC_Clocks->SYSCLK_Frequency = (HSE_Value / prediv1factor) * pllmull;          
        }
        else
        {/* PLL2 時鐘作為 PREDIV1 時鐘源 */
          
          /* 指定 PREDIV2 分頻係數 和 PLL2 倍頻係數 */
          prediv2factor = ((RCC->CFGR2 & CFGR2_PREDIV2) >> 4) + 1;
          pll2mull = ((RCC->CFGR2 & CFGR2_PLL2MUL) >> 8 ) + 2; 
          RCC_Clocks->SYSCLK_Frequency = (((HSE_Value / prediv2factor) * pll2mull) / prediv1factor) * pllmull;                         
        }
      }
#endif /* STM32F10X_CL */ 
      break;

    default:
      RCC_Clocks->SYSCLK_Frequency = HSI_Value;
      break;
  }

  /* 計算 HCLK, PCLK1, PCLK2 , ADCCLK 時鐘頻率 ----------------*/
  /* 得到 HCLK 預分頻器 */
  tmp = RCC->CFGR & CFGR_HPRE_Set_Mask;
  tmp = tmp >> 4;
  presc = APBAHBPrescTable[tmp];
  /* HCLK 時鐘頻率 */
  RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> presc;
  /* 得到 PCLK1 預分頻器 */
  tmp = RCC->CFGR & CFGR_PPRE1_Set_Mask;
  tmp = tmp >> 8;
  presc = APBAHBPrescTable[tmp];
  /* PCLK1 時鐘頻率 */
  RCC_Clocks->PCLK1_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
  /* 得到 PCLK2 預分頻器 */
  tmp = RCC->CFGR & CFGR_PPRE2_Set_Mask;
  tmp = tmp >> 11;
  presc = APBAHBPrescTable[tmp];
  /* PCLK2 時鐘頻率 */
  RCC_Clocks->PCLK2_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
  /* 得到 ADCCLK 預分頻器 */
  tmp = RCC->CFGR & CFGR_ADCPRE_Set_Mask;
  tmp = tmp >> 14;
  presc = ADCPrescTable[tmp];
  /* ADCCLK 時鐘頻率 */
  RCC_Clocks->ADCCLK_Frequency = RCC_Clocks->PCLK2_Frequency / presc;
}

/**
  * @簡述  使能或失能 AHB 外圍設備時鐘.
  * @參數  RCC_AHBPeriph: 用於門控時鐘的 AHB 外圍設備.
  *   
  *        STM32_互聯繫列微處理器, 這個參數可以取下列值中的一個:      
  *                                RCC_AHBPeriph_DMA1
  *                                RCC_AHBPeriph_DMA2
  *                                RCC_AHBPeriph_SRAM
  *                                RCC_AHBPeriph_FLITF
  *                                RCC_AHBPeriph_CRC
  *                                RCC_AHBPeriph_OTG_FS    
  *                                RCC_AHBPeriph_ETH_MAC   
  *                                RCC_AHBPeriph_ETH_MAC_Tx
  *                                RCC_AHBPeriph_ETH_MAC_Rx
  * 
  *           其它_STM32_微處理器, 這個參數可以取下列值中的一個:         
  *                                RCC_AHBPeriph_DMA1
  *                                RCC_AHBPeriph_DMA2
  *                                RCC_AHBPeriph_SRAM
  *                                RCC_AHBPeriph_FLITF
  *                                RCC_AHBPeriph_CRC
  *                                RCC_AHBPeriph_FSMC
  *                                RCC_AHBPeriph_SDIO
  *   
  * @註解  SRAM 和 FLITF 時鐘只有在睡眠的模式下可以無效.
  * @參數  NewState: 指定外圍設備時鐘新的狀態.
  *                  這個參數可以取: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_RCC_AHB_PERIPH(RCC_AHBPeriph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->AHBENR |= RCC_AHBPeriph;
  }
  else
  {
    RCC->AHBENR &= ~RCC_AHBPeriph;
  }
}

/**
  * @簡述  使能或失能高速 APB (APB2) 外圍設備時鐘.
  * @參數  RCC_APB2Periph: 用於門控時鐘的 AHB2 外圍設備.
  *                        這個參數可以是下面任意值的組合:
  *          RCC_APB2Periph_AFIO, RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB,
  *          RCC_APB2Periph_GPIOC, RCC_APB2Periph_GPIOD, RCC_APB2Periph_GPIOE,
  *          RCC_APB2Periph_GPIOF, RCC_APB2Periph_GPIOG, RCC_APB2Periph_ADC1,
  *          RCC_APB2Periph_ADC2, RCC_APB2Periph_TIM1, RCC_APB2Periph_SPI1,
  *          RCC_APB2Periph_TIM8, RCC_APB2Periph_USART1, RCC_APB2Periph_ADC3
  * @參數  NewState: 指定外圍設備時鐘的新狀態.
  *                  這個參數可以取: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    RCC->APB2ENR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2ENR &= ~RCC_APB2Periph;
  }
}

/**
  * @簡述  使能或失能低速 APB (APB1) 外圍設備時鐘.
  * @參數  RCC_APB1Periph: 用於門控時鐘的 APB1 外圍設備.
  *                        這個參數可以是下面任意值的組合:
  *          RCC_APB1Periph_TIM2, RCC_APB1Periph_TIM3, RCC_APB1Periph_TIM4,
  *          RCC_APB1Periph_TIM5, RCC_APB1Periph_TIM6, RCC_APB1Periph_TIM7,
  *          RCC_APB1Periph_WWDG, RCC_APB1Periph_SPI2, RCC_APB1Periph_SPI3,
  *          RCC_APB1Periph_USART2, RCC_APB1Periph_USART3, RCC_APB1Periph_USART4, 
  *          RCC_APB1Periph_USART5, RCC_APB1Periph_I2C1, RCC_APB1Periph_I2C2,
  *          RCC_APB1Periph_USB, RCC_APB1Periph_CAN1, RCC_APB1Periph_BKP,
  *          RCC_APB1Periph_PWR, RCC_APB1Periph_DAC
  * @參數  NewState: 指定外圍設備時鐘的新狀態.
  *                  這個參數可以取: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    RCC->APB1ENR |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1ENR &= ~RCC_APB1Periph;
  }
}

#ifdef STM32F10X_CL
/**
  * @簡述  控制或釋放 AHB 外圍設備復位.
  * @註解  這個函數僅僅應用在 STM32 互聯繫列微處理器.
  * @參數  RCC_AHBPeriph: 指定復位的外圍設備.
  *                       這個參數可以是下面任意值的組合:
  *                       RCC_AHBPeriph_OTG_FS 
  *                       RCC_AHBPeriph_ETH_MAC
  * @參數  NewState: 指定外圍設備復位的新狀態.
  *                  這個參數可以取: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_RCC_AHB_PERIPH_RESET(RCC_AHBPeriph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->AHBRSTR |= RCC_AHBPeriph;
  }
  else
  {
    RCC->AHBRSTR &= ~RCC_AHBPeriph;
  }
}
#endif /* STM32F10X_CL */ 

/**
  * @簡述  控制或釋放高速 APB(APB2) 外圍設備復位.
  * @參數  RCC_APB2Periph: 指定復位的 APB2 外圍設備.
  *                        這個參數可以是下面任意值的組合:
  *          RCC_APB2Periph_AFIO, RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB,
  *          RCC_APB2Periph_GPIOC, RCC_APB2Periph_GPIOD, RCC_APB2Periph_GPIOE,
  *          RCC_APB2Periph_GPIOF, RCC_APB2Periph_GPIOG, RCC_APB2Periph_ADC1,
  *          RCC_APB2Periph_ADC2, RCC_APB2Periph_TIM1, RCC_APB2Periph_SPI1,
  *          RCC_APB2Periph_TIM8, RCC_APB2Periph_USART1, RCC_APB2Periph_ADC3
  * @參數  NewState: 指定外圍設備復位的新狀態.
  *                  這個參數可以取: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    RCC->APB2RSTR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2RSTR &= ~RCC_APB2Periph;
  }
}

/**
  * @簡述  控制或釋放低速 APB(APB1) 外圍設備復位.
  * @參數  RCC_APB1Periph: 指定復位的 APB1 外圍設備.
  *                        這個參數可以是下面任意值的組合:
  *          RCC_APB1Periph_TIM2, RCC_APB1Periph_TIM3, RCC_APB1Periph_TIM4,
  *          RCC_APB1Periph_TIM5, RCC_APB1Periph_TIM6, RCC_APB1Periph_TIM7,
  *          RCC_APB1Periph_WWDG, RCC_APB1Periph_SPI2, RCC_APB1Periph_SPI3,
  *          RCC_APB1Periph_USART2, RCC_APB1Periph_USART3, RCC_APB1Periph_USART4, 
  *          RCC_APB1Periph_USART5, RCC_APB1Periph_I2C1, RCC_APB1Periph_I2C2,
  *          RCC_APB1Periph_USB, RCC_APB1Periph_CAN1, RCC_APB1Periph_BKP,
  *          RCC_APB1Periph_PWR, RCC_APB1Periph_DAC
  * @參數  NewState: 指定外圍設備復位的新狀態.
  *                  這個參數可以取: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    RCC->APB1RSTR |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1RSTR &= ~RCC_APB1Periph;
  }
}

/**
  * @簡述  控制或釋放備份域復位.
  * @參數  NewState: 備份域復位的新狀態.
  *                  這個參數可以取: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void RCC_BackupResetCmd(FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) BDCR_BDRST_BB = (uint32_t)NewState;
}

/**
  * @簡述  使能或失能時鐘安全系統.
  * @參數  NewState: 時鐘安全系統的新狀態.
  *                  這個參數可以取: ENABLE 或 DISABLE.
  * @返回  沒有
  */
void RCC_ClockSecuritySystemCmd(FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CR_CSSON_BB = (uint32_t)NewState;
}

/**
  * @簡述  選擇 MCO 引腳上的輸出時鐘源.
  * @參數  RCC_MCO: 指定要輸出的時鐘源.
  *   
  *        STM32_互聯繫列微處理器, 這個參數可以取下列值中的一個:      
  *                                RCC_MCO_NoClock:      沒有選擇時鐘
  *                                RCC_MCO_SYSCLK:       選擇系統時鐘
  *                                RCC_MCO_HSI:          選擇HIS振蕩時鐘
  *                                RCC_MCO_HSE:          選擇HSE振蕩時鐘
  *                                RCC_MCO_PLLCLK_Div2:  選擇PLL時鐘兩分頻
  *                                RCC_MCO_PLL2CLK:      選擇PLL2振蕩時鐘                    
  *                                RCC_MCO_PLL3CLK_Div2: 選擇PLL3時鐘兩分頻   
  *                                RCC_MCO_XT1:          選擇外部 3-25 MHz 振蕩時鐘  
  *                                RCC_MCO_PLL3CLK:      選擇PLL3振蕩時鐘 
  * 
  *           其它_STM32_微處理器, 這個參數可以取下列值中的一個:        
  *                                RCC_MCO_NoClock:      沒有選擇時鐘
  *                                RCC_MCO_SYSCLK:       選擇系統時鐘
  *                                RCC_MCO_HSI:          選擇HIS振蕩時鐘
  *                                RCC_MCO_HSE:          選擇HSE振蕩時鐘
  *                                RCC_MCO_PLLCLK_Div2:  選擇PLL時鐘兩分頻
  *   
  * @返回  沒有
  */
void RCC_MCOConfig(uint8_t RCC_MCO)
{
  /* 檢查參數 */
  assert_param(IS_RCC_MCO(RCC_MCO));

  /* 執行MCO[2:0]位的字節存取來選擇MCO源 */
  *(__IO uint8_t *) CFGR_BYTE4_ADDRESS = RCC_MCO;
}

/**
  * @簡述  檢查指定的 RCC 標誌設置與否.
  * @參數  RCC_FLAG: 指定要檢查的標誌.
  *   
  *        STM32_互聯繫列微處理器, 這個參數可以取下列值中的一個: 
  *                                RCC_FLAG_HSIRDY:  HSI 振蕩時鐘就緒
  *                                RCC_FLAG_HSERDY:  HSE 振蕩時鐘就緒
  *                                RCC_FLAG_PLLRDY:  PLL 時鐘就緒
  *                                RCC_FLAG_PLL2RDY: PLL2 時鐘就緒    
  *                                RCC_FLAG_PLL3RDY: PLL3 時鐘就緒                          
  *                                RCC_FLAG_LSERDY:  LSE 振蕩時鐘就緒
  *                                RCC_FLAG_LSIRDY:  LSI 振蕩時鐘就緒
  *                                RCC_FLAG_PINRST:  引腳復位
  *                                RCC_FLAG_PORRST:  POR/PDR復位
  *                                RCC_FLAG_SFTRST:  軟件復位
  *                                RCC_FLAG_IWDGRST: 獨立看門狗復位
  *                                RCC_FLAG_WWDGRST: 窗口看門狗復位
  *                                RCC_FLAG_LPWRRST: 低電量復位
  * 
  *           其它_STM32_微處理器, 這個參數可以取下列值中的一個:            
  *                                RCC_FLAG_HSIRDY:  HSI 振蕩時鐘就緒
  *                                RCC_FLAG_HSERDY:  HSE 振蕩時鐘就緒
  *                                RCC_FLAG_PLLRDY:  PLL 時鐘就緒
  *                                RCC_FLAG_LSERDY:  LSE 振蕩時鐘就緒
  *                                RCC_FLAG_LSIRDY:  LSI 振蕩時鐘就緒
  *                                RCC_FLAG_PINRST:  引腳復位
  *                                RCC_FLAG_PORRST:  POR/PDR復位
  *                                RCC_FLAG_SFTRST:  軟件復位
  *                                RCC_FLAG_IWDGRST: 獨立看門狗復位
  *                                RCC_FLAG_WWDGRST: 窗口看門狗復位
  *                                RCC_FLAG_LPWRRST: 低電量復位
  *   
  * @返回  RCC_FLAG 的新狀態(SET或RESET).
  */
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG)
{
  uint32_t tmp = 0;
  uint32_t statusreg = 0;
  FlagStatus bitstatus = RESET;
  /* 檢查參數 */
  assert_param(IS_RCC_FLAG(RCC_FLAG));

  /* 取得 RCC 寄存器引索 */
  tmp = RCC_FLAG >> 5;
  if (tmp == 1)               /* CR 寄存器中的檢查標誌 */
  {
    statusreg = RCC->CR;
  }
  else if (tmp == 2)          /* BDCR 寄存器中的檢查標誌 */
  {
    statusreg = RCC->BDCR;
  }
  else                       /* CSR 寄存器中的檢查標誌 */
  {
    statusreg = RCC->CSR;
  }

  /* 取得標誌的位置 */
  tmp = RCC_FLAG & FLAG_Mask;
  if ((statusreg & ((uint32_t)1 << tmp)) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  /* 返回標誌的狀態 */
  return bitstatus;
}

/**
  * @簡述  清除 RCC 復位標誌.
  * @註解   這些復位標誌是: RCC_FLAG_PINRST, RCC_FLAG_PORRST, RCC_FLAG_SFTRST,
  *                         RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST, RCC_FLAG_LPWRRST
  * @參數  沒有
  * @返回  沒有
  */
void RCC_ClearFlag(void)
{
  /* 通過置位 RMVF 位來清除復位標誌 */
  RCC->CSR |= CSR_RMVF_Set;
}

/**
  * @簡述  檢查指定的 RCC 中斷是否發生.
  * @參數  RCC_IT: 指定檢查 RCC 中斷源.
  *   
  *        STM32_互聯繫列微處理器, 這個參數可以取下列值中的一個: 
  *                                RCC_IT_LSIRDY:  LSI 就緒中斷
  *                                RCC_IT_LSERDY:  LSE 就緒中斷
  *                                RCC_IT_HSIRDY:  HSI 就緒中斷
  *                                RCC_IT_HSERDY:  HSE 就緒中斷
  *                                RCC_IT_PLLRDY:  PLL 就緒中斷
  *                                RCC_IT_PLL2RDY: PLL2 就緒中斷 
  *                                RCC_IT_PLL3RDY: PLL3 就緒中斷                    
  *                                RCC_IT_CSS:     時鐘安全系統中斷
  * 
  *           其它_STM32_微處理器, 這個參數可以取下列值中的一個:      
  *                                RCC_IT_LSIRDY: LSI 就緒中斷
  *                                RCC_IT_LSERDY: LSE 就緒中斷
  *                                RCC_IT_HSIRDY: HSI 就緒中斷
  *                                RCC_IT_HSERDY: HSE 就緒中斷
  *                                RCC_IT_PLLRDY: PLL 就緒中斷
  *                                RCC_IT_CSS:    時鐘安全系統中斷
  *   
  * @返回  RCC_IT 的新狀態(SETorRESET).
  */
ITStatus RCC_GetITStatus(uint8_t RCC_IT)
{
  ITStatus bitstatus = RESET;
  /* 檢查參數 */
  assert_param(IS_RCC_GET_IT(RCC_IT));

  /* 檢查指定的 RCC 中斷狀態 */
  if ((RCC->CIR & RCC_IT) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  /* 返回 RCC_IT 狀態 */
  return  bitstatus;
}

/**
  * @簡述  清除 RCC 中斷掛起位.
  * @參數  RCC_IT: 指定要清除的中斷掛起位.
  *   
  *        STM32_互聯繫列微處理器, 這個參數可以取下列值中的一個: 
  *                                RCC_IT_LSIRDY:  LSI 就緒中斷
  *                                RCC_IT_LSERDY:  LSE 就緒中斷
  *                                RCC_IT_HSIRDY:  HSI 就緒中斷
  *                                RCC_IT_HSERDY:  HSE 就緒中斷
  *                                RCC_IT_PLLRDY:  PLL 就緒中斷
  *                                RCC_IT_PLL2RDY: PLL2 就緒中斷
  *                                RCC_IT_PLL3RDY: PLL3 就緒中斷                      
  *                                RCC_IT_CSS:     時鐘安全系統中斷
  * 
  *           其它_STM32_微處理器, 這個參數可以取下列值中的一個:           
  *                                RCC_IT_LSIRDY:  LSI 就緒中斷
  *                                RCC_IT_LSERDY:  LSE 就緒中斷
  *                                RCC_IT_HSIRDY:  HSI 就緒中斷
  *                                RCC_IT_HSERDY:  HSE 就緒中斷
  *                                RCC_IT_PLLRDY:  PLL 就緒中斷
  *                                RCC_IT_CSS:     時鐘安全系統中斷
  * @返回  沒有
  */
void RCC_ClearITPendingBit(uint8_t RCC_IT)
{
  /* 檢查參數 */
  assert_param(IS_RCC_CLEAR_IT(RCC_IT));

  /* 執行 RCC_CIR[23:16] 位的字節存取來清除選擇的中斷掛起位*/
  *(__IO uint8_t *) CIR_BYTE3_ADDRESS = RCC_IT;
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
