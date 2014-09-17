/**
  ******************************************************************************
  * @���    stm32f10x_flash.c
  * @�@��    MCD ���ε{�ǲ�
  * @����    V3.1.0
  * @���    06/19/2009
  * @²�z    �o�Ӥ�� ���ѩҦ� FLASH �T����.
  * @½Ķ    ANSON/sweet1985 Email:airanson110@126.com
  * @���    23/07/2009
  ******************************************************************************
  * @�_��
  *
  * �o�өT��ȶȬO���ѵ��Ȥ�@���]�p���~�ӽs�g�{�Ǫ��Ѧҥت��ϫȤ�`���ɶ��C�ѩ�
  * �Ȥ�ϥΥ��T��b�}�o���~�s�{�W���ͪ����G�N�k�b���餽�q���Ӿ���󪽱����M����
  * ���d���A�]���Ӿ����l�`�Ӥް_�����v�C
  *
  * <h2><center>&�ƻs; ���v�Ҧ� 2009 �N�k�b���餽�q</center></h2>
  * ½Ķ�����ȨѾǲߡA�p�P�^��쪩���X�J���H�^��쪩���ǡC
  */ 

/* �]�t ------------------------------------------------------------------*/
#include "stm32f10x_flash.h"

/* �ۥ����� --------------------------------------------------------------*/
/* �ۥΩw�q --------------------------------------------------------------*/ 

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

/* �ۥΧ� -------------------------------------------------------------*/
/* �ۥ��ܶq -----------------------------------------------------------*/
/* �ۥΨ�ƭ쫬 -------------------------------------------------------*/
/* �ۥΨ�� -----------------------------------------------------------*/
static void delay(void);
/**
  * @²�z  �]�m�N�X���ɭ�.
  * @�Ѽ�  FLASH_Latency: ���w�� FLASH ���ɭ�.
  *          �o�ӰѼƥi�H�O�U�����Ȥ��@:
  *          FLASH_Latency_0: FLASH 0�ө��ɶg��
  *          FLASH_Latency_1: FLASH 1�ө��ɶg��
  *          FLASH_Latency_2: FLASH 2�ө��ɶg��
  * @��^  �S��
  */
void FLASH_SetLatency(uint32_t FLASH_Latency)
{
  uint32_t tmpreg = 0;
  
  /* �ˬd�Ѽ� */
  assert_param(IS_FLASH_LATENCY(FLASH_Latency));
  
  /* Ū ACR �H�s�� */
  tmpreg = FLASH->ACR;  
  
  /* �]�m���ɭ� */
  tmpreg &= ACR_LATENCY_Mask;
  tmpreg |= FLASH_Latency;
  
  /* �g ACR �H�s�� */
  FLASH->ACR = tmpreg;
}

/**
  * @²�z  �ϯ�Ϊ̥��� FLASH �b�g���X��.
  * @�Ѽ�  FLASH_HalfCycleAccess: ���w�� FLASH �b�g���X�ݼҦ�.
  *          �o�ӰѼƥi�H�O�U�����Ȥ��@:
  *          FLASH_HalfCycleAccess_Enable:  �b�g���X�ݨϯ�
  *          FLASH_HalfCycleAccess_Disable: �b�g���X�ݥ���
  * @��^  �S��
  */
void FLASH_HalfCycleAccessCmd(uint32_t FLASH_HalfCycleAccess)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_FLASH_HALFCYCLEACCESS_STATE(FLASH_HalfCycleAccess));
  
  /* �ϯ�Ϊ̥���b�g���X�� */
  FLASH->ACR &= ACR_HLFCYA_Mask;
  FLASH->ACR |= FLASH_HalfCycleAccess;
}

/**
  * @²�z  �ϯ�Ϊ̥���w���w�s.
  * @�Ѽ�  FLASH_PrefetchBuffer: ���w���w���w�s���A.
  *          �o�ӰѼƥi�H�O�U�����Ȥ��@:
  *          FLASH_PrefetchBuffer_Enable:  �ϯ�w�����w�s
  *          FLASH_PrefetchBuffer_Disable: ����w�����w�s
  * @��^  �S��
  */
void FLASH_PrefetchBufferCmd(uint32_t FLASH_PrefetchBuffer)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_FLASH_PREFETCHBUFFER_STATE(FLASH_PrefetchBuffer));
  
  /* �ϯ�Ϊ̥���w���w�s */
  FLASH->ACR &= ACR_PRFTBE_Mask;
  FLASH->ACR |= FLASH_PrefetchBuffer;
}

/**
  * @²�z  ���� FLASH �s�g�������.
  * @�Ѽ�  �S��
  * @��^  �S��
  */
void FLASH_Unlock(void)
{
  /* ���v FPEC �s�� */
  FLASH->KEYR = FLASH_KEY1;
  FLASH->KEYR = FLASH_KEY2;
}

/**
  * @²�z  ��w FLASH �s�g�������.
  * @�Ѽ�  �S��
  * @��^  �S��
  */
void FLASH_Lock(void)
{
  /* �]�m��w�����w FPEC �M FCR */
  FLASH->CR |= CR_LOCK_Set;
}

/**
  * @²�z  �����@�� FLASH ����.
  * @�Ѽ�  Page_Address: �ݭn��������.
  * @��^  FLASH ���A: ��^�ȥi�H�O: FLASH_BUSY, FLASH_ERROR_PG,
  *                    FLASH_ERROR_WRP, FLASH_COMPLETE �� FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ErasePage(uint32_t Page_Address)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* �ˬd�Ѽ� */
  assert_param(IS_FLASH_ADDRESS(Page_Address));
  /* ���ݳ̫�@�Ӿާ@���� */
  status = FLASH_WaitForLastOperation(EraseTimeout);
  
  if(status == FLASH_COMPLETE)
  { 
    /* �p�G�e�@�Ӿާ@�w�g���� */
    FLASH->CR|= CR_PER_Set;
    FLASH->AR = Page_Address; 
    FLASH->CR|= CR_STRT_Set;
    
    /* ���ݳ̫�@�Ӿާ@���� */
    status = FLASH_WaitForLastOperation(EraseTimeout);
    if(status != FLASH_TIMEOUT)
    {
      /* �p�G�����ާ@�����A���� PER �� */
      FLASH->CR &= CR_PER_Reset;
    }
  }
  /* ��^�������A */
  return status;
}

/**
  * @²�z  �������� FLASH ����.
  * @�Ѽ�  �S��
  * @��^  FLASH ���A: ��^�ȥi�H�O: FLASH_ERROR_PG, FLASH_ERROR_WRP, 
  *                    FLASH_COMPLETE �� FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EraseAllPages(void)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* ���ݳ̫�@�Ӿާ@���� */
  status = FLASH_WaitForLastOperation(EraseTimeout);
  
  if(status == FLASH_COMPLETE)
  {
    /* �p�G�e�@�Ӿާ@�w�g�����A�����Ҧ����� */
     FLASH->CR |= CR_MER_Set;
     FLASH->CR |= CR_STRT_Set;
    
    /* ���ݳ̫�@�Ӿާ@���� */
    status = FLASH_WaitForLastOperation(EraseTimeout);
    if(status != FLASH_TIMEOUT)
    {
      /* �p�G�����ާ@�����A���� MER �� */
      FLASH->CR &= CR_MER_Reset;
    }
  }	   
  /* ��^�������A */
  return status;
}

/**
  * @²�z  ���� FLASH ��ܦr�`.
  * @�Ѽ�  �S��
  * @��^  FLASH Status: ��^�ȥi�H�O: FLASH_ERROR_PG, FLASH_ERROR_WRP, 
  *                      FLASH_COMPLETE �� FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EraseOptionBytes(void)
{
  FLASH_Status status = FLASH_COMPLETE;
  
  /* ���ݳ̫�@�Ӿާ@���� */
  status = FLASH_WaitForLastOperation(EraseTimeout);
  if(status == FLASH_COMPLETE)
  {
    /* ���v�p�H�����s�{ */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    
    /* �p�G�e�@�Ӿާ@�����A�����ﶵ�r�` */
    FLASH->CR |= CR_OPTER_Set;
    FLASH->CR |= CR_STRT_Set;
    /* ���ݳ̫�@�Ӿާ@���� */
    status = FLASH_WaitForLastOperation(EraseTimeout);
    
    if(status == FLASH_COMPLETE)
    {
      /* �p�G�����ާ@�����A���� OPTER �� */
      FLASH->CR &= CR_OPTER_Reset;
       
      /* �ϯ�r�`�s�{�ާ@�ﶵ */
      FLASH->CR |= CR_OPTPG_Set;
      /* �ϯ�Ū�X�X�� */
      OB->RDP= RDP_Key; 
      /* ���ݳ̫�@�Ӿާ@���� */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
 
      if(status != FLASH_TIMEOUT)
      {
        /* �p�G�s�{�ާ@�����A���� OPTPG �� */
        FLASH->CR &= CR_OPTPG_Reset;
      }
    }
    else
    {
      if (status != FLASH_TIMEOUT)
      {
        /* ���� OPTPG �� */
        FLASH->CR &= CR_OPTPG_Reset;
      }
    }  
  }
  /* ��^�������A */
  return status;
}

/**
  * @²�z  �b���w�a�}�s�g�@�Ӧr.
  * @�Ѽ�  Address: �N�n�s�{���a�}.
  * @�Ѽ�  Data: ���w�Q�s�{���ƾ�.
  * @��^  FLASH Status: ��^�ȥi�H�O: FLASH_ERROR_PG, FLASH_ERROR_WRP, 
  *                      FLASH_COMPLETE �� FLASH_TIMEOUT. 
  */
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
  FLASH_Status status = FLASH_COMPLETE;
  __IO uint32_t tmp = 0;

  /* �ˬd�Ѽ� */
  assert_param(IS_FLASH_ADDRESS(Address));
  /* ���ݳ̫�@�Ӿާ@���� */
  status = FLASH_WaitForLastOperation(ProgramTimeout);
  
  if(status == FLASH_COMPLETE)
  {
    /* �p�G�e�@�Ӿާ@�����A�s�{�s���Ĥ@�ӥb�r */
    FLASH->CR |= CR_PG_Set;
  
    *(__IO uint16_t*)Address = (uint16_t)Data;
    /* ���ݳ̫�@�Ӿާ@���� */
    status = FLASH_WaitForLastOperation(ProgramTimeout);
 
    if(status == FLASH_COMPLETE)
    {
      /* �p�G�e�@�Ӿާ@�����A�s�{�s���ĤG�ӥb�r */
      tmp = Address + 2;

      *(__IO uint16_t*) tmp = Data >> 16;
    
      /* ���ݳ̫�@�Ӿާ@���� */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
        
      if(status != FLASH_TIMEOUT)
      {
        /* ���� PG �� */
        FLASH->CR &= CR_PG_Reset;
      }
    }
    else
    {
      if (status != FLASH_TIMEOUT)
      {
        /* ���� PG �� */
        FLASH->CR &= CR_PG_Reset;
      }
     }
  }
  /* ��^�s�{���A */
  return status;
}

/**
  * @²�z  �b�S�w�a�}�s�{�@�ӥb�r.
  * @�Ѽ�  Address: �Q�s�{���a�}.
  * @�Ѽ�  Data: ���w�Q�s�{���b�r�ƾ�.
  * @��^  FLASH Status: ��^�ȥi�H�O: FLASH_ERROR_PG, FLASH_ERROR_WRP, 
  *                      FLASH_COMPLETE �� FLASH_TIMEOUT. 
  */
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* �ˬd�Ѽ� */
  assert_param(IS_FLASH_ADDRESS(Address));
  /* ���ݳ̫�@�Ӿާ@���� */
  status = FLASH_WaitForLastOperation(ProgramTimeout);
  
  if(status == FLASH_COMPLETE)
  {
    /* �p�G�e�@�Ӿާ@�����A�s�{�s���ƾ� */
    FLASH->CR |= CR_PG_Set;
  
    *(__IO uint16_t*)Address = Data;
    /* ���ݳ̫�@�Ӿާ@���� */
    status = FLASH_WaitForLastOperation(ProgramTimeout);
    if(status != FLASH_TIMEOUT)
    {
      /* �p�G�s�{�ާ@�����A���� PG �� */
      FLASH->CR &= CR_PG_Reset;
    }
  } 
  /* ��^�s�{���A */
  return status;
}

/**
  * @²�z  �b���w���ﶵ�r�`�ƾڦa�}�W�s�g�@�ӥb�r.
  * @�Ѽ�  Address: �Q�s�{���a�}.
  *                 �o�ӰѼƥi�H�O 0x1FFFF804 �� 0x1FFFF806. 
  * @�Ѽ�  Data: �Q�s�g���ƾ�.
  * @��^  FLASH Status: ��^�ȥi�H�O: FLASH_ERROR_PG, FLASH_ERROR_WRP, 
  *                      FLASH_COMPLETE �� FLASH_TIMEOUT. 
  */
FLASH_Status FLASH_ProgramOptionByteData(uint32_t Address, uint8_t Data)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* �ˬd�Ѽ� */
  assert_param(IS_OB_DATA_ADDRESS(Address));
  status = FLASH_WaitForLastOperation(ProgramTimeout);
  if(status == FLASH_COMPLETE)
  {
    /* ���v�p�H�����s�{ */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    /* �ϯ�r�`�s�{�ާ@�ﶵ */
    FLASH->CR |= CR_OPTPG_Set; 
    *(__IO uint16_t*)Address = Data;
    
    /* ���ݳ̫�@�Ӿާ@���� */
    status = FLASH_WaitForLastOperation(ProgramTimeout);
    if(status != FLASH_TIMEOUT)
    {
      /* �p�G�s�{�ާ@�����A���� OPTPG �� */
      FLASH->CR &= CR_OPTPG_Reset;
    }
  }    
  /* ��^�ﶵ�r�`�ƾڪ��s�{���A */
  return status;
}

/**
  * @²�z  ����檺�����g�O�@
  * @�Ѽ�  FLASH_Pages: �ݼg�O�@�������a�}.
  *                 �o�ӰѼƥi�H�O:
  *                 STM32_�C�K�׳B�z��: value between FLASH_WRProt_Pages0to3 �M FLASH_WRProt_Pages28to31  
  *                 STM32_���K�׳B�z��: value between FLASH_WRProt_Pages0to3 �M FLASH_WRProt_Pages124to127
  *                 STM32_���K�׳B�z��: value between FLASH_WRProt_Pages0to1 �M FLASH_WRProt_Pages60to61 �� FLASH_WRProt_Pages62to255
  *                 STM32_�s�q�ʳB�z��: value between FLASH_WRProt_Pages0to1 �M FLASH_WRProt_Pages60to61 �� FLASH_WRProt_Pages62to127    
  *                 FLASH_WRProt_AllPages
  * @��^  FLASH Status: ��^�ȥi�H�O: FLASH_ERROR_PG, FLASH_ERROR_WRP, 
  *                      FLASH_COMPLETE �� FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EnableWriteProtection(uint32_t FLASH_Pages)
{
  uint16_t WRP0_Data = 0xFFFF, WRP1_Data = 0xFFFF, WRP2_Data = 0xFFFF, WRP3_Data = 0xFFFF;
  
  FLASH_Status status = FLASH_COMPLETE;
  
  /* �ˬd�Ѽ� */
  assert_param(IS_FLASH_WRPROT_PAGE(FLASH_Pages));
  
  FLASH_Pages = (uint32_t)(~FLASH_Pages);
  WRP0_Data = (uint16_t)(FLASH_Pages & WRP0_Mask);
  WRP1_Data = (uint16_t)((FLASH_Pages & WRP1_Mask) >> 8);
  WRP2_Data = (uint16_t)((FLASH_Pages & WRP2_Mask) >> 16);
  WRP3_Data = (uint16_t)((FLASH_Pages & WRP3_Mask) >> 24);
  
  /* ���ݳ̫�@�Ӿާ@���� */
  status = FLASH_WaitForLastOperation(ProgramTimeout);
  
  if(status == FLASH_COMPLETE)
  {
    /* ���v�p�H�����s�{ */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    FLASH->CR |= CR_OPTPG_Set;
    if(WRP0_Data != 0xFF)
    {
      OB->WRP0 = WRP0_Data;
      
      /* ���ݳ̫�@�Ӿާ@���� */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
    }
    if((status == FLASH_COMPLETE) && (WRP1_Data != 0xFF))
    {
      OB->WRP1 = WRP1_Data;
      
      /* ���ݳ̫�@�Ӿާ@���� */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
    }
    if((status == FLASH_COMPLETE) && (WRP2_Data != 0xFF))
    {
      OB->WRP2 = WRP2_Data;
      
      /* ���ݳ̫�@�Ӿާ@���� */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
    }
    
    if((status == FLASH_COMPLETE)&& (WRP3_Data != 0xFF))
    {
      OB->WRP3 = WRP3_Data;
     
      /* ���ݳ̫�@�Ӿާ@���� */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
    }
          
    if(status != FLASH_TIMEOUT)
    {
      /* �p�G�s�{�ާ@�����A���� OPTPG �� */
      FLASH->CR &= CR_OPTPG_Reset;
    }
  } 
  /* ��^�g�O�@�ާ@���A */
  return status;       
}

/**
  * @²�z  �ϯ�Ϊ̥���Ū�X�O�@.
  * @����   �p�G�b�եγo�Ө�Ƥ��e�ϥΪ̤w�g�s�{�F�䥦���ﶵ�r�`�A�b�o��
  *         ��������Ҧ����ﶵ�r�`�H��L�������s�s�{���ǿﶵ�r�`.
  * @�Ѽ�  Newstate: Ū�X�O�@���s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  FLASH Status: ��^�ȥi�H�O: FLASH_ERROR_PG, FLASH_ERROR_WRP, 
  *                      FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ReadOutProtection(FunctionalState NewState)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* �ˬd�Ѽ� */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  status = FLASH_WaitForLastOperation(EraseTimeout);
  if(status == FLASH_COMPLETE)
  {
    /* ���v�p�H�����s�{ */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    FLASH->CR |= CR_OPTER_Set;
    FLASH->CR |= CR_STRT_Set;
    /* ���ݳ̫�@�Ӿާ@���� */
    status = FLASH_WaitForLastOperation(EraseTimeout);
    if(status == FLASH_COMPLETE)
    {
      /* �p�G�����ާ@�����A���� OPTER �� */
      FLASH->CR &= CR_OPTER_Reset;
      /* �ϯ�r�`�s�{�ާ@�ﶵ */
      FLASH->CR |= CR_OPTPG_Set; 
      if(NewState != DISABLE)
      {
        OB->RDP = 0x00;
      }
      else
      {
        OB->RDP = RDP_Key;  
      }
      /* ���ݳ̫�@�Ӿާ@���� */
      status = FLASH_WaitForLastOperation(EraseTimeout); 
    
      if(status != FLASH_TIMEOUT)
      {
        /* �p�G�s�{�ާ@�����A���� OPTPG �� */
        FLASH->CR &= CR_OPTPG_Reset;
      }
    }
    else 
    {
      if(status != FLASH_TIMEOUT)
      {
        /* ���� OPTER �� */
        FLASH->CR &= CR_OPTER_Reset;
      }
    }
  }
  /* ��^�g�O�@�ާ@���A */
  return status;      
}

/**
  * @²�z  �s�gFLASH�Τ��ܦr�`: IWDG_SW / RST_STOP / RST_STDBY.
  * @�Ѽ�  OB_IWDG: ��� IWDG �Ҧ�
  *          �o�ӰѼƥi�H�O�U�����Ȥ��@:
  *          OB_IWDG_SW: ��ܳn��W�߬ݪ���
  *          OB_IWDG_HW: ��ܵw��W�߬ݪ���
  * @�Ѽ�  OB_STOP: ��i�J STOP �Ҧ����ʹ_��ƥ�.
  *          �o�ӰѼƥi�H�O�U�����Ȥ��@:
  *          OB_STOP_NoRST: �i�J STOP �Ҧ������ʹ_��
  *          OB_STOP_RST:   �i�J STOP �Ҧ����ʹ_��
  * @�Ѽ�  OB_STDBY: ��i�J Standby �Ҧ����ʹ_��ƥ�.
  *          �o�ӰѼƥi�H�O�U�����Ȥ��@:
  *          OB_STDBY_NoRST: �i�J Standby �Ҧ������ʹ_��
  *          OB_STDBY_RST:   �i�J Standby �Ҧ������ʹ_��
  * @��^  FLASH Status: ��^�ȥi�H�O: FLASH_ERROR_PG, FLASH_ERROR_WRP, 
  *                      FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_UserOptionByteConfig(uint16_t OB_IWDG, uint16_t OB_STOP, uint16_t OB_STDBY)
{
  FLASH_Status status = FLASH_COMPLETE; 

  /* �ˬd�Ѽ� */
  assert_param(IS_OB_IWDG_SOURCE(OB_IWDG));
  assert_param(IS_OB_STOP_SOURCE(OB_STOP));
  assert_param(IS_OB_STDBY_SOURCE(OB_STDBY));

  /* ���v�p�H�����s�{ */
  FLASH->OPTKEYR = FLASH_KEY1;
  FLASH->OPTKEYR = FLASH_KEY2;
  
  /* ���ݳ̫�@�Ӿާ@���� */
  status = FLASH_WaitForLastOperation(ProgramTimeout);
  
  if(status == FLASH_COMPLETE)
  {  
    /* �ϯ�r�`�s�{�ާ@�ﶵ */
    FLASH->CR |= CR_OPTPG_Set; 
           
    OB->USER = OB_IWDG | (uint16_t)(OB_STOP | (uint16_t)(OB_STDBY | ((uint16_t)0xF8))); 
  
    /* ���ݳ̫�@�Ӿާ@���� */
    status = FLASH_WaitForLastOperation(ProgramTimeout);
    if(status != FLASH_TIMEOUT)
    {
      /* �p�G�s�{�ާ@�����A���� OPTPG �� */
      FLASH->CR &= CR_OPTPG_Reset;
    }
  }    
  /* ��^�ﶵ�r�`�s�{���A */
  return status;
}

/**
  * @²�z  ��^ FLASH �Τ��ܦr�`����.
  * @�Ѽ�  �S��
  * @��^  FLASH �Τ��ܦr�`����:IWDG_SW(Bit0), RST_STOP(Bit1) �M RST_STDBY(Bit2).
  */
uint32_t FLASH_GetUserOptionByte(void)
{
  /* ��^�Τ�ﶵ�r�`�� */
  return (uint32_t)(FLASH->OBR >> 2);
}

/**
  * @²�z  ��^ FLASH �g�O�@��ܦr�`�H�s������.
  * @�Ѽ�  �S��
  * @��^  FLASH �g�O�@�ﶵ�r�`�H�s����
  */
uint32_t FLASH_GetWriteProtectionOptionByte(void)
{
  /* ��^ FLASH �g�O�@�H�s���� */
  return (uint32_t)(FLASH->WRPR);
}

/**
  * @²�z  �ˬd FLASH Ū�X�O�@�]�m�P�_.
  * @�Ѽ�  �S��
  * @��^  FLASH Ū�X�O�@�����A (SET �� RESET)
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
  * @²�z  �ˬd FLASH �w�����w�s�]�m�P�_.
  * @�Ѽ�  �S��
  * @��^  FLASH �w���w�İϪ����A (SET �� RESET).
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
  /* �ˬd FLASH �w�����w�s�]�m�P�_ (SET �� RESET) */
  return bitstatus; 
}

/**
  * @²�z  �ϯ�Ϊ̥�����w FLASH ���_.
  * @�Ѽ�  FLASH_IT: �ݨϯ�Ϊ̥��઺���w FLASH ���_��.
  *          �o�ӰѼƥi�H�O�U���Ȫ����N�զX:
  *          FLASH_IT_ERROR: FLASH ���~���_��
  *          FLASH_IT_EOP:   FLASH �ާ@�������_��
  * @�Ѽ�  NewState: ���w�� FLASH ���_���s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.      
  * @��^  �S�� 
  */
void FLASH_ITConfig(uint16_t FLASH_IT, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_FLASH_IT(FLASH_IT)); 
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if(NewState != DISABLE)
  {
    /* �ϯत�_�� */
    FLASH->CR |= FLASH_IT;
  }
  else
  {
    /* ���त�_�� */
    FLASH->CR &= ~(uint32_t)FLASH_IT;
  }
}

/**
  * @²�z  �ˬd���w�� FLASH �лx��]�m�P�_.
  * @�Ѽ�  FLASH_FLAG: �ݭn�ˬd���лx.
  *          �o�ӰѼƥi�H�O�U�����Ȥ��@:
  *          FLASH_FLAG_BSY:      FLASH ���лx           
  *          FLASH_FLAG_PGERR:    FLASH �{�ǿ��~�лx       
  *          FLASH_FLAG_WRPRTERR: FLASH �����g�O�@���~�лx    
  *          FLASH_FLAG_EOP:      FLASH �ާ@�����лx          
  *          FLASH_FLAG_OPTERR:   FLASH �ﶵ�r�`���~�лx   
  * @��^  FLASH_FLAG ���s���A (SET �� RESET).
  */
FlagStatus FLASH_GetFlagStatus(uint16_t FLASH_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* �ˬd�Ѽ� */
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
  /* ��^ FLASH_FLAG ���s���A (SET or RESET) */
  return bitstatus;
}

/**
  * @²�z  �M�� FLASH �ݳB�z�лx��.
  * @�Ѽ�  FLASH_FLAG: �ݭn�M�����лx.
  *          �o�ӰѼƥi�H�O�U���Ȫ����N�զX:        
  *          FLASH_FLAG_PGERR:    FLASH �{�ǿ��~�лx       
  *          FLASH_FLAG_WRPRTERR: FLASH W�����g�O�@���~�лx      
  *          FLASH_FLAG_EOP:      FLASH �ާ@�������лx          
  * @��^  �S��
  */
void FLASH_ClearFlag(uint16_t FLASH_FLAG)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_FLASH_CLEAR_FLAG(FLASH_FLAG)) ;
  
  /* �M���лx */
  FLASH->SR = FLASH_FLAG;
}

/**
  * @²�z  ��^ FLASH ���A.
  * @�Ѽ�  �S��
  * @��^  FLASH ���A: ��^�ȥi�H�O: FLASH_BUSY, FLASH_ERROR_PG,
  *                    FLASH_ERROR_WRP �� FLASH_COMPLETE
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
  /* ��^ FLASH ���A */
  return flashstatus;
}

/**
  * @²�z  ���ݤ@�� Flash �ާ@�ӵ����Τ@�� TIMEOUT �ƥ�o��.
  * @�Ѽ�  Timeout: FLASH �s�{�W�ɮɶ�
  * @��^  FLASH Status: ��^�ȥi�H�O: FLASH_ERROR_PG, FLASH_ERROR_WRP, 
  *                      FLASH_COMPLETE �� FLASH_TIMEOUT.
  */
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout)
{ 
  FLASH_Status status = FLASH_COMPLETE;
   
  /* �ˬd FLASH ���A */
  status = FLASH_GetStatus();
  /* ���� FLASH �ާ@�����Ϊ̵o�ͶW�� */
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
  /* ��^�ާ@���A */
  return status;
}

/**
  * @²�z  ���J�@�ө���.
  * @�Ѽ�  �S��
  * @��^  �S��
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
