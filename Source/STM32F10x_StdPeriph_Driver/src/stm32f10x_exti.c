/**
  ******************************************************************************
  * @���    stm32f10x_exti.c
  * @�@��    MCD ���ε{�ǲ�
  * @����    V3.1.0
  * @���    06/19/2009
  * @²�z    �o�Ӥ�󴣨ѥ��� EXTI �T����.
  * @½Ķ    ANSON/sweet1985 Email:airanson110@126.com
  * @���    06/07/2009
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
#include "stm32f10x_exti.h"

/* �ۥ����� ------------------------------------------------------------*/
/* �ۥΩw�q ------------------------------------------------------------*/

#define EXTI_LineNone    ((uint32_t)0x00000)  /* No interrupt selected */

/* �ۥΧ� --------------------------------------------------------------*/
/* �ۥ��ܶq ------------------------------------------------------------*/
/* �ۥΨ�ƭ쫬 --------------------------------------------------------*/
/* �ۥΨ�� ------------------------------------------------------------*/

/**
  * @²�z  �N EXTI �~�]�H�s���_����q�{��.
  * @�Ѽ�  �S��
  * @��^  �S��
  */
void EXTI_DeInit(void)
{
  EXTI->IMR = 0x00000000;
  EXTI->EMR = 0x00000000;
  EXTI->RTSR = 0x00000000; 
  EXTI->FTSR = 0x00000000; 
  EXTI->PR = 0x000FFFFF;
}

/**
  * @²�z  �ھ�EXIT_InitStruct�����w���Ѽƪ�l�� EXTI �~�].
  * @�Ѽ�  EXTI_InitStruct: ���V EXTI_InitTypeDef �����c�A���]�t�S�wEXTI���t�m�H��.
  * @��^  �S��
  */
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct)
{
  uint32_t tmp = 0;

  /* �ˬd�Ѽ� */
  assert_param(IS_EXTI_MODE(EXTI_InitStruct->EXTI_Mode));
  assert_param(IS_EXTI_TRIGGER(EXTI_InitStruct->EXTI_Trigger));
  assert_param(IS_EXTI_LINE(EXTI_InitStruct->EXTI_Line));  
  assert_param(IS_FUNCTIONAL_STATE(EXTI_InitStruct->EXTI_LineCmd));

  tmp = (uint32_t)EXTI_BASE;
     
  if (EXTI_InitStruct->EXTI_LineCmd != DISABLE)
  {
    /* �M�� EXTI �~�����_�u�t�m */
    EXTI->IMR &= ~EXTI_InitStruct->EXTI_Line;
    EXTI->EMR &= ~EXTI_InitStruct->EXTI_Line;
    
    tmp += EXTI_InitStruct->EXTI_Mode;

    *(__IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;

    /* �M���W�ɪu�U���u��u�t�m */
    EXTI->RTSR &= ~EXTI_InitStruct->EXTI_Line;
    EXTI->FTSR &= ~EXTI_InitStruct->EXTI_Line;
    
    /* ����w���~�����_���Ĳ�o(�ƥ�) */
    if (EXTI_InitStruct->EXTI_Trigger == EXTI_Trigger_Rising_Falling)
    {
      /* �W�ɪu�U���u */
      EXTI->RTSR |= EXTI_InitStruct->EXTI_Line;
      EXTI->FTSR |= EXTI_InitStruct->EXTI_Line;
    }
    else
    {
      tmp = (uint32_t)EXTI_BASE;
      tmp += EXTI_InitStruct->EXTI_Trigger;

      *(__IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;
    }
  }
  else
  {
    tmp += EXTI_InitStruct->EXTI_Mode;

    /* �T��襤���~�����_�u */
    *(__IO uint32_t *) tmp &= ~EXTI_InitStruct->EXTI_Line;
  }
}

/**
  * @²�z  �NEXTI_InitStruct�����m���q�{��.
  * @�Ѽ�  EXTI_InitStruct: ���VEXTI_InitTypeDef���c�A�ӵ��c�N�Q��l��.
  * @��^  �S��
  */
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct)
{
  EXTI_InitStruct->EXTI_Line = EXTI_LineNone;
  EXTI_InitStruct->EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStruct->EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStruct->EXTI_LineCmd = DISABLE;
}

/**
  * @²�z  ���ͤ@�ӳn���_.
  * @�Ѽ�  EXTI_Line: ���w EXTI �u�E���θT��.
  *                   �o�ӰѼƥi�H���N�զX EXTI_Linex �� x�i�H��(0..19).
  * @��^  �S��
  */
void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_EXTI_LINE(EXTI_Line));
  
  EXTI->SWIER |= EXTI_Line;
}

/**
  * @²�z  �ˬd�S�w�� EXTI �u�лx�O�_�Q�m��.
  * @�Ѽ�  EXTI_Line: �S�w�� EXTI �u�лx.
  *                   �o�ӰѼƥi�H�O:
  *                                  EXTI_Linex: �~�����_�u x�i�H��(0..19)
  * @��^  EXTI_Line ���s���A (SET �� RESET).
  */
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line)
{
  FlagStatus bitstatus = RESET;
  /* �ˬd�Ѽ� */
  assert_param(IS_GET_EXTI_LINE(EXTI_Line));
  
  if ((EXTI->PR & EXTI_Line) != (uint32_t)RESET)
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
  * @²�z  �M�� EXTI �u�����_�лx.
  * @�Ѽ�  EXTI_Line: ���w�n�M���лx�� EXTI �u.
  *                   �o�ӰѼƥi�H�O���NEXTI_Linex�զX�Ax�i�H�O(0..19).
  * @��^  �S��
  */
void EXTI_ClearFlag(uint32_t EXTI_Line)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_EXTI_LINE(EXTI_Line));
  
  EXTI->PR = EXTI_Line;
}

/**
  * @²�z  �ˬd���w�� EXTI �u��Ĳ�o�ШD�o�ͻP�_.
  * @�Ѽ�  EXTI_Line: ���ˬd EXTI �u�������_��.
  *                   �o�ӰѼƥi�H�O:
  *                                  EXTI_Linex: �~�����_�u x�i�H�O(0..19)
  * @��^  EXTI_Line ���s���A (SET �� RESET).
  */
ITStatus EXTI_GetITStatus(uint32_t EXTI_Line)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_GET_EXTI_LINE(EXTI_Line));
  
  enablestatus =  EXTI->IMR & EXTI_Line;
  if (((EXTI->PR & EXTI_Line) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
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
  * @²�z  �M��EXTI�u�����_��.
  * @�Ѽ�  EXTI_Line: �ݲM��EXTI�u�������_��.
  *                    �o�ӰѼƥi�H�O���N EXTI_Linex �զX�A x�i�H�O(0..19).
  * @��^  �S��
  */
void EXTI_ClearITPendingBit(uint32_t EXTI_Line)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_EXTI_LINE(EXTI_Line));
  
  EXTI->PR = EXTI_Line;
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
