/**
  ******************************************************************************
  * @���    misc.c
  * @�@��    MCD ���ε{�ǲ�
  * @����    V3.1.0
  * @���    06/19/2009
  * @²�z    �o�Ӥ�󴣨ѵ��Ҧ���L���T���� (�l�[ CMSIS<�L����n�󱵤f�з�> ���).
  * @½Ķ    ANSON/sweet1985 Email:airanson110@126.com
  * @���    02/07/2009
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
#include "misc.h"

/* �ۥ����� --------------------------------------------------------------*/
/* �ۥΩw�q --------------------------------------------------------------*/

#define AIRCR_VECTKEY_MASK    ((uint32_t)0x05FA0000)

/* �ۥΧ� ------------------------------------------------------------*/
/* �ۥ��ܶq ----------------------------------------------------------*/

/* �ۥΨ�ƭ쫬 ------------------------------------------------------*/
/* �ۥΨ�� ----------------------------------------------------------*/


/**
  * @²�z  �]�m�u���Ť��աG�����u���ũM�q�u����.
  * @�Ѽ�  NVIC_PriorityGroup: �u���Ť��զ����. 
  *                            �o�ӰѼƥi�H���U�C�Ȥ����@��:
  *          NVIC_PriorityGroup_0: �����u����0��
  *                                �q�u����4��
  *          NVIC_PriorityGroup_1: �����u����1��
  *                                �q�u����3��
  *          NVIC_PriorityGroup_2: �����u����2��
  *                                �q�u����2��
  *          NVIC_PriorityGroup_3: �����u����3��
  *                                �q�u����1��
  *          NVIC_PriorityGroup_4: �����u����4��
  *                                �q�u����0��
  * @��^  �S��
  */
void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_NVIC_PRIORITY_GROUP(NVIC_PriorityGroup));
  
  /* �̷�NVIC_PriorityGroup���ȳ]�mPRIGROUP[10:8]���� */
  SCB->AIRCR = AIRCR_VECTKEY_MASK | NVIC_PriorityGroup;
}

/**
  * @²�z  �q�LNVIC_InitStruct�������w�ѼƨӪ�l�ƥ~��]��.
  * @�Ѽ�  NVIC_InitStruct: �@�ӫ��V�]�t���w NVIC �~��]�ưt�m�H���� NVIC_InitTypeDef ���c�����w.
  * @��^  �S��
  */
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct)
{
  uint32_t tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;
  
  /* �ˬd�Ѽ� */
  assert_param(IS_FUNCTIONAL_STATE(NVIC_InitStruct->NVIC_IRQChannelCmd));
  assert_param(IS_NVIC_PREEMPTION_PRIORITY(NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority));  
  assert_param(IS_NVIC_SUB_PRIORITY(NVIC_InitStruct->NVIC_IRQChannelSubPriority));
    
  if (NVIC_InitStruct->NVIC_IRQChannelCmd != DISABLE)
  {
    /* �p��ŦX IRQ(���_�ШD) �u���v --------------------------------*/    
    tmppriority = (0x700 - ((SCB->AIRCR) & (uint32_t)0x700))>> 0x08;
    tmppre = (0x4 - tmppriority);
    tmpsub = tmpsub >> tmppriority;

    tmppriority = (uint32_t)NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority << tmppre;
    tmppriority |=  NVIC_InitStruct->NVIC_IRQChannelSubPriority & tmpsub;
    tmppriority = tmppriority << 0x04;
        
    NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel] = tmppriority;
    
    /* �ϯ��ܪ� IRQ(���_�ШD) �q�D --------------------------------------*/
    NVIC->ISER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
      (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
  else
  {
    /* �����ܪ� IRQ(���_�ШD) �q�D -------------------------------------*/
    NVIC->ICER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
      (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
}

/**
  * @²�z  �]�m�V�q����m�M�����q.
  * @�Ѽ�  NVIC_VectTab: ���w�V�q��b RAM �� FLASH .
  *                      �o�ӰѼƥi�H���U�C�Ȥ����@��:
  *                      NVIC_VectTab_RAM
  *                      NVIC_VectTab_FLASH
  * @�Ѽ�  Offset: �V�q���a�}�������q. �o�ӭȥ����O 0x100 ���㭿��.
  * @��^  �S��
  */
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset)
{ 
  /* �ˬd�Ѽ� */
  assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
  assert_param(IS_NVIC_OFFSET(Offset));  
   
  SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
}

/**
  * @²�z  ��ܨt�ζi�J�C�\�ӼҦ�������.
  * @�Ѽ�  LowPowerMode: �t�ά��i�J�C�\�ӼҦ����s�Ҧ�.
  *                      �o�ӰѼƥi�H���U�����Ȥ��@:
  *                      NVIC_LP_SEVONPEND
  *                      NVIC_LP_SLEEPDEEP
  *                      NVIC_LP_SLEEPONEXIT
  * @�Ѽ�  NewState: LP ���󪺷s���A.�o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
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
  * @²�z  �]�m SysTick ������.
  * @�Ѽ�  SysTick_CLKSource: ���w SysTick ������.
  *                           �o�ӰѼƥi�H���U�����Ȥ��@:
  *          SysTick_CLKSource_HCLK_Div8: SysTick ��������AHB������1/8.
  *          SysTick_CLKSource_HCLK:      SysTick ��������AHB����.
  * @��^  �S��
  */
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource)
{
  /* �ˬd�Ѽ� */
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
