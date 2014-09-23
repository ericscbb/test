/**
  ******************************************************************************
  * @文件    stm32f10x_flash.c
  * @作者    MCD 應用程序組
  * @版本    V3.1.0
  * @日期    06/19/2009
  * @簡述    這個文件 提供所有 FLASH 固件函數.
  * @翻譯    ANSON/sweet1985 Email:airanson110@126.com
  * @日期    23/07/2009
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
#include "stm32f10x_flash.h"

/* 自用類型 --------------------------------------------------------------*/
/* 自用定義 --------------------------------------------------------------*/ 

/* Flash Access Control Register bits */
#define ACR_LATENCY_Mask         ((uint32_t)0x00000038)
#define ACR_HLFCYA_Mask          ((uint32_t)0xFFFFFFF7)
#define ACR_PRFTBE_Mask          ((uint32_t)0xFFFFFFEF)

/* Flash Access Control Register bits */
#define ACR_PRFTBS_Mask          ((uint32_t)0x00000020) 

/* Flash Control Register bits */
#define CR_PG_Set                ((uint32_t)0x00000001)
#define CR_PG_Reset              ((uint32_t)0x00001FFE) 
#define CR_PER_Set               ((uint32_t)0x00000002)
#define CR_PER_Reset             ((uint32_t)0x00001FFD)
#define CR_MER_Set               ((uint32_t)0x00000004)
#define CR_MER_Reset             ((uint32_t)0x00001FFB)
#define CR_OPTPG_Set             ((uint32_t)0x00000010)
#define CR_OPTPG_Reset           ((uint32_t)0x00001FEF)
#define CR_OPTER_Set             ((uint32_t)0x00000020)
#define CR_OPTER_Reset           ((uint32_t)0x00001FDF)
#define CR_STRT_Set              ((uint32_t)0x00000040)
#define CR_LOCK_Set              ((uint32_t)0x00000080)

/* FLASH Mask */
#define RDPRT_Mask               ((uint32_t)0x00000002)
#define WRP0_Mask                ((uint32_t)0x000000FF)
#define WRP1_Mask                ((uint32_t)0x0000FF00)
#define WRP2_Mask                ((uint32_t)0x00FF0000)
#define WRP3_Mask                ((uint32_t)0xFF000000)

/* FLASH Keys */
#define RDP_Key                  ((uint16_t)0x00A5)
#define FLASH_KEY1               ((uint32_t)0x45670123)
#define FLASH_KEY2               ((uint32_t)0xCDEF89AB)

/* Delay definition */   
#define EraseTimeout             ((uint32_t)0x00000FFF)
#define ProgramTimeout           ((uint32_t)0x0000000F)

/* 自用宏 -------------------------------------------------------------*/
/* 自用變量 -----------------------------------------------------------*/
/* 自用函數原型 -------------------------------------------------------*/
/* 自用函數 -----------------------------------------------------------*/
static void delay(void);
/**
  * @簡述  設置代碼延時值.
  * @參數  FLASH_Latency: 指定的 FLASH 延時值.
  *          這個參數可以是下面的值之一:
  *          FLASH_Latency_0: FLASH 0個延時週期
  *          FLASH_Latency_1: FLASH 1個延時週期
  *          FLASH_Latency_2: FLASH 2個延時週期
  * @返回  沒有
  */
void FLASH_SetLatency(uint32_t FLASH_Latency)
{
  uint32_t tmpreg = 0;
  
  /* 檢查參數 */
  assert_param(IS_FLASH_LATENCY(FLASH_Latency));
  
  /* 讀 ACR 寄存器 */
  tmpreg = FLASH->ACR;  
  
  /* 設置延時值 */
  tmpreg &= ACR_LATENCY_Mask;
  tmpreg |= FLASH_Latency;
  
  /* 寫 ACR 寄存器 */
  FLASH->ACR = tmpreg;
}

/**
  * @簡述  使能或者失能 FLASH 半週期訪問.
  * @參數  FLASH_HalfCycleAccess: 指定的 FLASH 半週期訪問模式.
  *          這個參數可以是下面的值之一:
  *          FLASH_HalfCycleAccess_Enable:  半週期訪問使能
  *          FLASH_HalfCycleAccess_Disable: 半週期訪問失能
  * @返回  沒有
  */
void FLASH_HalfCycleAccessCmd(uint32_t FLASH_HalfCycleAccess)
{
  /* 檢查參數 */
  assert_param(IS_FLASH_HALFCYCLEACCESS_STATE(FLASH_HalfCycleAccess));
  
  /* 使能或者失能半週期訪問 */
  FLASH->ACR &= ACR_HLFCYA_Mask;
  FLASH->ACR |= FLASH_HalfCycleAccess;
}

/**
  * @簡述  使能或者失能預取緩存.
  * @參數  FLASH_PrefetchBuffer: 指定的預取緩存狀態.
  *          這個參數可以是下面的值之一:
  *          FLASH_PrefetchBuffer_Enable:  使能預取指緩存
  *          FLASH_PrefetchBuffer_Disable: 失能預取指緩存
  * @返回  沒有
  */
void FLASH_PrefetchBufferCmd(uint32_t FLASH_PrefetchBuffer)
{
  /* 檢查參數 */
  assert_param(IS_FLASH_PREFETCHBUFFER_STATE(FLASH_PrefetchBuffer));
  
  /* 使能或者失能預取緩存 */
  FLASH->ACR &= ACR_PRFTBE_Mask;
  FLASH->ACR |= FLASH_PrefetchBuffer;
}

/**
  * @簡述  解鎖 FLASH 編寫擦除控制器.
  * @參數  沒有
  * @返回  沒有
  */
void FLASH_Unlock(void)
{
  /* 授權 FPEC 存取 */
  FLASH->KEYR = FLASH_KEY1;
  FLASH->KEYR = FLASH_KEY2;
}

/**
  * @簡述  鎖定 FLASH 編寫擦除控制器.
  * @參數  沒有
  * @返回  沒有
  */
void FLASH_Lock(void)
{
  /* 設置鎖定位來鎖定 FPEC 和 FCR */
  FLASH->CR |= CR_LOCK_Set;
}

/**
  * @簡述  擦除一個 FLASH 頁面.
  * @參數  Page_Address: 需要擦除的頁.
  * @返回  FLASH 狀態: 返回值可以是: FLASH_BUSY, FLASH_ERROR_PG,
  *                    FLASH_ERROR_WRP, FLASH_COMPLETE 或 FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ErasePage(uint32_t Page_Address)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* 檢查參數 */
  assert_param(IS_FLASH_ADDRESS(Page_Address));
  /* 等待最後一個操作完成 */
  status = FLASH_WaitForLastOperation(EraseTimeout);
  
  if(status == FLASH_COMPLETE)
  { 
    /* 如果前一個操作已經完成 */
    FLASH->CR|= CR_PER_Set;
    FLASH->AR = Page_Address; 
    FLASH->CR|= CR_STRT_Set;
    
    /* 等待最後一個操作完成 */
    status = FLASH_WaitForLastOperation(EraseTimeout);
    if(status != FLASH_TIMEOUT)
    {
      /* 如果擦除操作完成，失能 PER 位 */
      FLASH->CR &= CR_PER_Reset;
    }
  }
  /* 返回擦除狀態 */
  return status;
}

/**
  * @簡述  擦除全部 FLASH 頁面.
  * @參數  沒有
  * @返回  FLASH 狀態: 返回值可以是: FLASH_ERROR_PG, FLASH_ERROR_WRP, 
  *                    FLASH_COMPLETE 或 FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EraseAllPages(void)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* 等待最後一個操作完成 */
  status = FLASH_WaitForLastOperation(EraseTimeout);
  
  if(status == FLASH_COMPLETE)
  {
    /* 如果前一個操作已經完成，擦除所有的頁 */
     FLASH->CR |= CR_MER_Set;
     FLASH->CR |= CR_STRT_Set;
    
    /* 等待最後一個操作完成 */
    status = FLASH_WaitForLastOperation(EraseTimeout);
    if(status != FLASH_TIMEOUT)
    {
      /* 如果擦除操作完成，失能 MER 位 */
      FLASH->CR &= CR_MER_Reset;
    }
  }	   
  /* 返回擦除狀態 */
  return status;
}

/**
  * @簡述  擦除 FLASH 選擇字節.
  * @參數  沒有
  * @返回  FLASH Status: 返回值可以是: FLASH_ERROR_PG, FLASH_ERROR_WRP, 
  *                      FLASH_COMPLETE 或 FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EraseOptionBytes(void)
{
  FLASH_Status status = FLASH_COMPLETE;
  
  /* 等待最後一個操作完成 */
  status = FLASH_WaitForLastOperation(EraseTimeout);
  if(status == FLASH_COMPLETE)
  {
    /* 授權小信息塊編程 */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    
    /* 如果前一個操作完成，擦除選項字節 */
    FLASH->CR |= CR_OPTER_Set;
    FLASH->CR |= CR_STRT_Set;
    /* 等待最後一個操作完成 */
    status = FLASH_WaitForLastOperation(EraseTimeout);
    
    if(status == FLASH_COMPLETE)
    {
      /* 如果擦除操作完成，失能 OPTER 位 */
      FLASH->CR &= CR_OPTER_Reset;
       
      /* 使能字節編程操作選項 */
      FLASH->CR |= CR_OPTPG_Set;
      /* 使能讀出訪問 */
      OB->RDP= RDP_Key; 
      /* 等待最後一個操作完成 */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
 
      if(status != FLASH_TIMEOUT)
      {
        /* 如果編程操作完成，失能 OPTPG 位 */
        FLASH->CR &= CR_OPTPG_Reset;
      }
    }
    else
    {
      if (status != FLASH_TIMEOUT)
      {
        /* 失能 OPTPG 位 */
        FLASH->CR &= CR_OPTPG_Reset;
      }
    }  
  }
  /* 返回擦除狀態 */
  return status;
}

/**
  * @簡述  在指定地址編寫一個字.
  * @參數  Address: 將要編程的地址.
  * @參數  Data: 指定被編程的數據.
  * @返回  FLASH Status: 返回值可以是: FLASH_ERROR_PG, FLASH_ERROR_WRP, 
  *                      FLASH_COMPLETE 或 FLASH_TIMEOUT. 
  */
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
  FLASH_Status status = FLASH_COMPLETE;
  __IO uint32_t tmp = 0;

  /* 檢查參數 */
  assert_param(IS_FLASH_ADDRESS(Address));
  /* 等待最後一個操作完成 */
  status = FLASH_WaitForLastOperation(ProgramTimeout);
  
  if(status == FLASH_COMPLETE)
  {
    /* 如果前一個操作完成，編程新的第一個半字 */
    FLASH->CR |= CR_PG_Set;
  
    *(__IO uint16_t*)Address = (uint16_t)Data;
    /* 等待最後一個操作完成 */
    status = FLASH_WaitForLastOperation(ProgramTimeout);
 
    if(status == FLASH_COMPLETE)
    {
      /* 如果前一個操作完成，編程新的第二個半字 */
      tmp = Address + 2;

      *(__IO uint16_t*) tmp = Data >> 16;
    
      /* 等待最後一個操作完成 */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
        
      if(status != FLASH_TIMEOUT)
      {
        /* 失能 PG 位 */
        FLASH->CR &= CR_PG_Reset;
      }
    }
    else
    {
      if (status != FLASH_TIMEOUT)
      {
        /* 失能 PG 位 */
        FLASH->CR &= CR_PG_Reset;
      }
     }
  }
  /* 返回編程狀態 */
  return status;
}

/**
  * @簡述  在特定地址編程一個半字.
  * @參數  Address: 被編程的地址.
  * @參數  Data: 指定被編程的半字數據.
  * @返回  FLASH Status: 返回值可以是: FLASH_ERROR_PG, FLASH_ERROR_WRP, 
  *                      FLASH_COMPLETE 或 FLASH_TIMEOUT. 
  */
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* 檢查參數 */
  assert_param(IS_FLASH_ADDRESS(Address));
  /* 等待最後一個操作完成 */
  status = FLASH_WaitForLastOperation(ProgramTimeout);
  
  if(status == FLASH_COMPLETE)
  {
    /* 如果前一個操作完成，編程新的數據 */
    FLASH->CR |= CR_PG_Set;
  
    *(__IO uint16_t*)Address = Data;
    /* 等待最後一個操作完成 */
    status = FLASH_WaitForLastOperation(ProgramTimeout);
    if(status != FLASH_TIMEOUT)
    {
      /* 如果編程操作完成，失能 PG 位 */
      FLASH->CR &= CR_PG_Reset;
    }
  } 
  /* 返回編程狀態 */
  return status;
}

/**
  * @簡述  在指定的選項字節數據地址上編寫一個半字.
  * @參數  Address: 被編程的地址.
  *                 這個參數可以是 0x1FFFF804 或 0x1FFFF806. 
  * @參數  Data: 被編寫的數據.
  * @返回  FLASH Status: 返回值可以是: FLASH_ERROR_PG, FLASH_ERROR_WRP, 
  *                      FLASH_COMPLETE 或 FLASH_TIMEOUT. 
  */
FLASH_Status FLASH_ProgramOptionByteData(uint32_t Address, uint8_t Data)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* 檢查參數 */
  assert_param(IS_OB_DATA_ADDRESS(Address));
  status = FLASH_WaitForLastOperation(ProgramTimeout);
  if(status == FLASH_COMPLETE)
  {
    /* 授權小信息塊編程 */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    /* 使能字節編程操作選項 */
    FLASH->CR |= CR_OPTPG_Set; 
    *(__IO uint16_t*)Address = Data;
    
    /* 等待最後一個操作完成 */
    status = FLASH_WaitForLastOperation(ProgramTimeout);
    if(status != FLASH_TIMEOUT)
    {
      /* 如果編程操作完成，失能 OPTPG 位 */
      FLASH->CR &= CR_OPTPG_Reset;
    }
  }    
  /* 返回選項字節數據的編程狀態 */
  return status;
}

/**
  * @簡述  對期望的頁面寫保護
  * @參數  FLASH_Pages: 待寫保護頁面的地址.
  *                 這個參數可以是:
  *                 STM32_低密度處理器: value between FLASH_WRProt_Pages0to3 和 FLASH_WRProt_Pages28to31  
  *                 STM32_中密度處理器: value between FLASH_WRProt_Pages0to3 和 FLASH_WRProt_Pages124to127
  *                 STM32_高密度處理器: value between FLASH_WRProt_Pages0to1 和 FLASH_WRProt_Pages60to61 或 FLASH_WRProt_Pages62to255
  *                 STM32_連通性處理器: value between FLASH_WRProt_Pages0to1 和 FLASH_WRProt_Pages60to61 或 FLASH_WRProt_Pages62to127    
  *                 FLASH_WRProt_AllPages
  * @返回  FLASH Status: 返回值可以是: FLASH_ERROR_PG, FLASH_ERROR_WRP, 
  *                      FLASH_COMPLETE 或 FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EnableWriteProtection(uint32_t FLASH_Pages)
{
  uint16_t WRP0_Data = 0xFFFF, WRP1_Data = 0xFFFF, WRP2_Data = 0xFFFF, WRP3_Data = 0xFFFF;
  
  FLASH_Status status = FLASH_COMPLETE;
  
  /* 檢查參數 */
  assert_param(IS_FLASH_WRPROT_PAGE(FLASH_Pages));
  
  FLASH_Pages = (uint32_t)(~FLASH_Pages);
  WRP0_Data = (uint16_t)(FLASH_Pages & WRP0_Mask);
  WRP1_Data = (uint16_t)((FLASH_Pages & WRP1_Mask) >> 8);
  WRP2_Data = (uint16_t)((FLASH_Pages & WRP2_Mask) >> 16);
  WRP3_Data = (uint16_t)((FLASH_Pages & WRP3_Mask) >> 24);
  
  /* 等待最後一個操作完成 */
  status = FLASH_WaitForLastOperation(ProgramTimeout);
  
  if(status == FLASH_COMPLETE)
  {
    /* 授權小信息塊編程 */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    FLASH->CR |= CR_OPTPG_Set;
    if(WRP0_Data != 0xFF)
    {
      OB->WRP0 = WRP0_Data;
      
      /* 等待最後一個操作完成 */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
    }
    if((status == FLASH_COMPLETE) && (WRP1_Data != 0xFF))
    {
      OB->WRP1 = WRP1_Data;
      
      /* 等待最後一個操作完成 */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
    }
    if((status == FLASH_COMPLETE) && (WRP2_Data != 0xFF))
    {
      OB->WRP2 = WRP2_Data;
      
      /* 等待最後一個操作完成 */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
    }
    
    if((status == FLASH_COMPLETE)&& (WRP3_Data != 0xFF))
    {
      OB->WRP3 = WRP3_Data;
     
      /* 等待最後一個操作完成 */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
    }
          
    if(status != FLASH_TIMEOUT)
    {
      /* 如果編程操作完成，失能 OPTPG 位 */
      FLASH->CR &= CR_OPTPG_Reset;
    }
  } 
  /* 返回寫保護操作狀態 */
  return status;       
}

/**
  * @簡述  使能或者失能讀出保護.
  * @註解   如果在調用這個函數之前使用者已經編程了其它的選項字節，在這個
  *         函數擦除所有的選項字節以後他必須重新編程那些選項字節.
  * @參數  Newstate: 讀出保護的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.
  * @返回  FLASH Status: 返回值可以是: FLASH_ERROR_PG, FLASH_ERROR_WRP, 
  *                      FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ReadOutProtection(FunctionalState NewState)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* 檢查參數 */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  status = FLASH_WaitForLastOperation(EraseTimeout);
  if(status == FLASH_COMPLETE)
  {
    /* 授權小信息塊編程 */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    FLASH->CR |= CR_OPTER_Set;
    FLASH->CR |= CR_STRT_Set;
    /* 等待最後一個操作完成 */
    status = FLASH_WaitForLastOperation(EraseTimeout);
    if(status == FLASH_COMPLETE)
    {
      /* 如果擦除操作完成，失能 OPTER 位 */
      FLASH->CR &= CR_OPTER_Reset;
      /* 使能字節編程操作選項 */
      FLASH->CR |= CR_OPTPG_Set; 
      if(NewState != DISABLE)
      {
        OB->RDP = 0x00;
      }
      else
      {
        OB->RDP = RDP_Key;  
      }
      /* 等待最後一個操作完成 */
      status = FLASH_WaitForLastOperation(EraseTimeout); 
    
      if(status != FLASH_TIMEOUT)
      {
        /* 如果編程操作完成，失能 OPTPG 位 */
        FLASH->CR &= CR_OPTPG_Reset;
      }
    }
    else 
    {
      if(status != FLASH_TIMEOUT)
      {
        /* 失能 OPTER 位 */
        FLASH->CR &= CR_OPTER_Reset;
      }
    }
  }
  /* 返回寫保護操作狀態 */
  return status;      
}

/**
  * @簡述  編寫FLASH用戶選擇字節: IWDG_SW / RST_STOP / RST_STDBY.
  * @參數  OB_IWDG: 選擇 IWDG 模式
  *          這個參數可以是下面的值之一:
  *          OB_IWDG_SW: 選擇軟件獨立看門狗
  *          OB_IWDG_HW: 選擇硬件獨立看門狗
  * @參數  OB_STOP: 當進入 STOP 模式產生復位事件.
  *          這個參數可以是下面的值之一:
  *          OB_STOP_NoRST: 進入 STOP 模式不產生復位
  *          OB_STOP_RST:   進入 STOP 模式產生復位
  * @參數  OB_STDBY: 當進入 Standby 模式產生復位事件.
  *          這個參數可以是下面的值之一:
  *          OB_STDBY_NoRST: 進入 Standby 模式不產生復位
  *          OB_STDBY_RST:   進入 Standby 模式不產生復位
  * @返回  FLASH Status: 返回值可以是: FLASH_ERROR_PG, FLASH_ERROR_WRP, 
  *                      FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_UserOptionByteConfig(uint16_t OB_IWDG, uint16_t OB_STOP, uint16_t OB_STDBY)
{
  FLASH_Status status = FLASH_COMPLETE; 

  /* 檢查參數 */
  assert_param(IS_OB_IWDG_SOURCE(OB_IWDG));
  assert_param(IS_OB_STOP_SOURCE(OB_STOP));
  assert_param(IS_OB_STDBY_SOURCE(OB_STDBY));

  /* 授權小信息塊編程 */
  FLASH->OPTKEYR = FLASH_KEY1;
  FLASH->OPTKEYR = FLASH_KEY2;
  
  /* 等待最後一個操作完成 */
  status = FLASH_WaitForLastOperation(ProgramTimeout);
  
  if(status == FLASH_COMPLETE)
  {  
    /* 使能字節編程操作選項 */
    FLASH->CR |= CR_OPTPG_Set; 
           
    OB->USER = OB_IWDG | (uint16_t)(OB_STOP | (uint16_t)(OB_STDBY | ((uint16_t)0xF8))); 
  
    /* 等待最後一個操作完成 */
    status = FLASH_WaitForLastOperation(ProgramTimeout);
    if(status != FLASH_TIMEOUT)
    {
      /* 如果編程操作完成，失能 OPTPG 位 */
      FLASH->CR &= CR_OPTPG_Reset;
    }
  }    
  /* 返回選項字節編程狀態 */
  return status;
}

/**
  * @簡述  返回 FLASH 用戶選擇字節的值.
  * @參數  沒有
  * @返回  FLASH 用戶選擇字節的值:IWDG_SW(Bit0), RST_STOP(Bit1) 和 RST_STDBY(Bit2).
  */
uint32_t FLASH_GetUserOptionByte(void)
{
  /* 返回用戶選項字節值 */
  return (uint32_t)(FLASH->OBR >> 2);
}

/**
  * @簡述  返回 FLASH 寫保護選擇字節寄存器的值.
  * @參數  沒有
  * @返回  FLASH 寫保護選項字節寄存器值
  */
uint32_t FLASH_GetWriteProtectionOptionByte(void)
{
  /* 返回 FLASH 寫保護寄存器值 */
  return (uint32_t)(FLASH->WRPR);
}

/**
  * @簡述  檢查 FLASH 讀出保護設置與否.
  * @參數  沒有
  * @返回  FLASH 讀出保護的狀態 (SET 或 RESET)
  */
FlagStatus FLASH_GetReadOutProtectionStatus(void)
{
  FlagStatus readoutstatus = RESET;
  if ((FLASH->OBR & RDPRT_Mask) != (uint32_t)RESET)
  {
    readoutstatus = SET;
  }
  else
  {
    readoutstatus = RESET;
  }
  return readoutstatus;
}

/**
  * @簡述  檢查 FLASH 預取指緩存設置與否.
  * @參數  沒有
  * @返回  FLASH 預取緩衝區的狀態 (SET 或 RESET).
  */
FlagStatus FLASH_GetPrefetchBufferStatus(void)
{
  FlagStatus bitstatus = RESET;
  
  if ((FLASH->ACR & ACR_PRFTBS_Mask) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* 檢查 FLASH 預取指緩存設置與否 (SET 或 RESET) */
  return bitstatus; 
}

/**
  * @簡述  使能或者失能指定 FLASH 中斷.
  * @參數  FLASH_IT: 待使能或者失能的指定 FLASH 中斷源.
  *          這個參數可以是下面值的任意組合:
  *          FLASH_IT_ERROR: FLASH 錯誤中斷源
  *          FLASH_IT_EOP:   FLASH 操作結束中斷源
  * @參數  NewState: 指定的 FLASH 中斷的新狀態.
  *                  這個參數可以是: ENABLE 或 DISABLE.      
  * @返回  沒有 
  */
void FLASH_ITConfig(uint16_t FLASH_IT, FunctionalState NewState)
{
  /* 檢查參數 */
  assert_param(IS_FLASH_IT(FLASH_IT)); 
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if(NewState != DISABLE)
  {
    /* 使能中斷源 */
    FLASH->CR |= FLASH_IT;
  }
  else
  {
    /* 失能中斷源 */
    FLASH->CR &= ~(uint32_t)FLASH_IT;
  }
}

/**
  * @簡述  檢查指定的 FLASH 標誌位設置與否.
  * @參數  FLASH_FLAG: 需要檢查的標誌.
  *          這個參數可以是下面的值之一:
  *          FLASH_FLAG_BSY:      FLASH 忙標誌           
  *          FLASH_FLAG_PGERR:    FLASH 程序錯誤標誌       
  *          FLASH_FLAG_WRPRTERR: FLASH 頁面寫保護錯誤標誌    
  *          FLASH_FLAG_EOP:      FLASH 操作結束標誌          
  *          FLASH_FLAG_OPTERR:   FLASH 選項字節錯誤標誌   
  * @返回  FLASH_FLAG 的新狀態 (SET 或 RESET).
  */
FlagStatus FLASH_GetFlagStatus(uint16_t FLASH_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* 檢查參數 */
  assert_param(IS_FLASH_GET_FLAG(FLASH_FLAG)) ;
  if(FLASH_FLAG == FLASH_FLAG_OPTERR) 
  {
    if((FLASH->OBR & FLASH_FLAG_OPTERR) != (uint32_t)RESET)
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }
  else
  {
   if((FLASH->SR & FLASH_FLAG) != (uint32_t)RESET)
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }
  /* 返回 FLASH_FLAG 的新狀態 (SET or RESET) */
  return bitstatus;
}

/**
  * @簡述  清除 FLASH 待處理標誌位.
  * @參數  FLASH_FLAG: 需要清除的標誌.
  *          這個參數可以是下面值的任意組合:        
  *          FLASH_FLAG_PGERR:    FLASH 程序錯誤標誌       
  *          FLASH_FLAG_WRPRTERR: FLASH W頁面寫保護錯誤標誌      
  *          FLASH_FLAG_EOP:      FLASH 操作結束的標誌          
  * @返回  沒有
  */
void FLASH_ClearFlag(uint16_t FLASH_FLAG)
{
  /* 檢查參數 */
  assert_param(IS_FLASH_CLEAR_FLAG(FLASH_FLAG)) ;
  
  /* 清除標誌 */
  FLASH->SR = FLASH_FLAG;
}

/**
  * @簡述  返回 FLASH 狀態.
  * @參數  沒有
  * @返回  FLASH 狀態: 返回值可以是: FLASH_BUSY, FLASH_ERROR_PG,
  *                    FLASH_ERROR_WRP 或 FLASH_COMPLETE
  */
FLASH_Status FLASH_GetStatus(void)
{
  FLASH_Status flashstatus = FLASH_COMPLETE;
  
  if((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY) 
  {
    flashstatus = FLASH_BUSY;
  }
  else 
  {  
    if((FLASH->SR & FLASH_FLAG_PGERR) != 0)
    { 
      flashstatus = FLASH_ERROR_PG;
    }
    else 
    {
      if((FLASH->SR & FLASH_FLAG_WRPRTERR) != 0 )
      {
        flashstatus = FLASH_ERROR_WRP;
      }
      else
      {
        flashstatus = FLASH_COMPLETE;
      }
    }
  }
  /* 返回 FLASH 狀態 */
  return flashstatus;
}

/**
  * @簡述  等待一個 Flash 操作來結束或一個 TIMEOUT 事件發生.
  * @參數  Timeout: FLASH 編程超時時間
  * @返回  FLASH Status: 返回值可以是: FLASH_ERROR_PG, FLASH_ERROR_WRP, 
  *                      FLASH_COMPLETE 或 FLASH_TIMEOUT.
  */
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout)
{ 
  FLASH_Status status = FLASH_COMPLETE;
   
  /* 檢查 FLASH 狀態 */
  status = FLASH_GetStatus();
  /* 等待 FLASH 操作完成或者發生超時 */
  while((status == FLASH_BUSY) && (Timeout != 0x00))
  {
    delay();
    status = FLASH_GetStatus();
    Timeout--;
  }
  if(Timeout == 0x00 )
  {
    status = FLASH_TIMEOUT;
  }
  /* 返回操作狀態 */
  return status;
}

/**
  * @簡述  插入一個延時.
  * @參數  沒有
  * @返回  沒有
  */
static void delay(void)
{
  __IO uint32_t i = 0;
  for(i = 0xFF; i != 0; i--)
  {
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
