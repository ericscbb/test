/**
  ******************************************************************************
  * @���    stm32f10x_rtc.c
  * @�@��    MCD ���ε{�ǲ�
  * @����    V3.1.0
  * @���    06/19/2009
  * @²�z    �o�Ӥ�� ���ѩҦ� RTC �T����.
  * @½Ķ    ANSON/sweet1985 Email:airanson110@126.com
  * @���    08/07/2009
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
#include "stm32f10x_rtc.h"

/* �ۥ����� --------------------------------------------------------------*/
/* �ۥΩw�q --------------------------------------------------------------*/
#define CRL_CNF_Set      ((uint16_t)0x0010)      /*!< Configuration Flag Enable Mask */
#define CRL_CNF_Reset    ((uint16_t)0xFFEF)      /*!< Configuration Flag Disable Mask */
#define RTC_LSB_Mask     ((uint32_t)0x0000FFFF)  /*!< RTC LSB Mask */
#define PRLH_MSB_Mask    ((uint32_t)0x000F0000)  /*!< RTC Prescaler MSB Mask */

/* �ۥΧ� -----------------------------------------------------------------*/
/* �ۥ��ܶq ---------------------------------------------------------------*/
/* �ۥΨ�ƭ쫬 -----------------------------------------------------------*/
/* �ۥΨ�� ---------------------------------------------------------------*/

/**
  * @²�z  �ϯ�Υ�����w�� RTC ���_.
  * @�Ѽ�  RTC_IT: �n�ϯ�Υ�����w�� RTC ���_.
  *                �o�ӰѼƥi�H�O�U���Ȫ����N�զX:
  *                RTC_IT_OW:  ���X���_
  *                RTC_IT_ALR: ĵ�����_
  *                RTC_IT_SEC: ���_
  * @�Ѽ�  NewState: ���w RTC ���_���s�����A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void RTC_ITConfig(uint16_t RTC_IT, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_RTC_IT(RTC_IT));  
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    RTC->CRH |= RTC_IT;
  }
  else
  {
    RTC->CRH &= (uint16_t)~RTC_IT;
  }
}

/**
  * @²�z  �i�J RTC �t�m�Ҧ�.
  * @�Ѽ�  �S��
  * @��^  �S��
  */
void RTC_EnterConfigMode(void)
{
  /* �]�m CNF �лx�i�J�t�m�Ҧ� */
  RTC->CRL |= CRL_CNF_Set;
}

/**
  * @²�z  �h�X RTC �t�m�Ҧ�.
  * @�Ѽ�  �S��
  * @��^  �S��
  */
void RTC_ExitConfigMode(void)
{
  /* �_�� CNF �лx�h�X�t�m�Ҧ� */
  RTC->CRL &= CRL_CNF_Reset;
}

/**
  * @²�z  ��o RTC �p�ƾ���.
  * @�Ѽ�  �S��
  * @��^  RTC �p�ƾ���.
  */
uint32_t RTC_GetCounter(void)
{
  uint16_t tmp = 0;
  tmp = RTC->CNTL;
  return (((uint32_t)RTC->CNTH << 16 ) | tmp) ;
}

/**
  * @²�z  �]�m RTC �p�ƾ���.
  * @�Ѽ�  CounterValue: RTC �p�ƾ����s��.
  * @��^  �S��
  */
void RTC_SetCounter(uint32_t CounterValue)
{ 
  RTC_EnterConfigMode();
  /* �]�m RTC �p�ƾ�����r */
  RTC->CNTH = CounterValue >> 16;
  /* �]�m RTC �p�ƾ��C��r */
  RTC->CNTL = (CounterValue & RTC_LSB_Mask);
  RTC_ExitConfigMode();
}

/**
  * @²�z  �]�m RTC �w���W�˦b�H�s������.
  * @�Ѽ�  PrescalerValue: RTC �w���W�˦b�H�s�����s��.
  * @��^  �S��
  */
void RTC_SetPrescaler(uint32_t PrescalerValue)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_RTC_PRESCALER(PrescalerValue));
  
  RTC_EnterConfigMode();
  /* �]�m RTC �w���W�˦b�H�s������r */
  RTC->PRLH = (PrescalerValue & PRLH_MSB_Mask) >> 16;
  /* �]�m RTC �w���W�˦b�H�s���C��r */
  RTC->PRLL = (PrescalerValue & RTC_LSB_Mask);
  RTC_ExitConfigMode();
}

/**
  * @²�z  �]�m RTC ��ĵ�H�s������.
  * @�Ѽ�  AlarmValue: RTC ��ĵ�H�s�����s��.
  * @��^  �S��
  */
void RTC_SetAlarm(uint32_t AlarmValue)
{  
  RTC_EnterConfigMode();
  /* �]�m��ĵ�H�s������r */
  RTC->ALRH = AlarmValue >> 16;
  /* �]�m��ĵ�H�s���C��r */
  RTC->ALRL = (AlarmValue & RTC_LSB_Mask);
  RTC_ExitConfigMode();
}

/**
  * @²�z  ��� RTC �w���W���W�]�l����.
  * @�Ѽ�  �S��
  * @��^  RTC �w���W���W�]�l����.
  */
uint32_t RTC_GetDivider(void)
{
  uint32_t tmp = 0x00;
  tmp = ((uint32_t)RTC->DIVH & (uint32_t)0x000F) << 16;
  tmp |= RTC->DIVL;
  return tmp;
}

/**
  * @²�z  ���ݳ̪�@����RTC�H�s�����g�ާ@����.
  * @����  �o�Ө�Ƥ@�w�n�b�����RTC�H�s���g�ާ@���e�ե�.
  * @�Ѽ�  �S��
  * @��^  �S��
  */
void RTC_WaitForLastTask(void)
{
  /* �`������ RTOFF �лx�m�� */
  while ((RTC->CRL & RTC_FLAG_RTOFF) == (uint16_t)RESET)
  {
  }
}

/**
  * @²�z  ����RTC�H�s��(RTC_CNT,RTC_ALR�MRTC_PRL)�PRTC APB�����P�B.
  * @����  �o�Ө�Ƥ@�w�n�b�����APB�_���APB��������᪺�g�ާ@���e�ե�.
  * @�Ѽ�  �S��
  * @��^  �S��
  */
void RTC_WaitForSynchro(void)
{
  /* �M�� RSF �лx */
  RTC->CRL &= (uint16_t)~RTC_FLAG_RSF;
  /* �`������ RSF �лx�m�� */
  while ((RTC->CRL & RTC_FLAG_RSF) == (uint16_t)RESET)
  {
  }
}

/**
  * @²�z  �ˬd���w�� RTC �лx�]�m�P�_.
  * @�Ѽ�  RTC_FLAG: ���w�n�ˬd���лx.
  *                  �o�ӰѼƥi�H��U�����Ȥ��@:
  *                  RTC_FLAG_RTOFF: RTC �ާ@�����лx
  *                  RTC_FLAG_RSF:   �H�s���P�B�лx
  *                  RTC_FLAG_OW:    ���X���_�лx
  *                  RTC_FLAG_ALR:   ĵ�����_�лx
  *                  RTC_FLAG_SEC:   ���_�лx
  * @��^  RTC_FLAG ���s���A (SET �� RESET).
  */
FlagStatus RTC_GetFlagStatus(uint16_t RTC_FLAG)
{
  FlagStatus bitstatus = RESET;
  
  /* �ˬd�Ѽ� */
  assert_param(IS_RTC_GET_FLAG(RTC_FLAG)); 
  
  if ((RTC->CRL & RTC_FLAG) != (uint16_t)RESET)
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
  * @²�z  �M�� RTC ���_�лx.
  * @�Ѽ�  RTC_FLAG: ���w�Q�M�����лx.
  *                  �o�ӰѼƥi�H�O�U���Ȫ����N�զX:
  *                  RTC_FLAG_RSF: �P�B�H�s���лx. �u���bSPB�_���APB���������M��.
  *                  RTC_FLAG_OW:  ���X���_�лx
  *                  RTC_FLAG_ALR: ��ĵ���_�лx
  *                  RTC_FLAG_SEC: ���_�лx
  * @��^  �S��
  */
void RTC_ClearFlag(uint16_t RTC_FLAG)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_RTC_CLEAR_FLAG(RTC_FLAG)); 
    
  /* �M�� RTC ���_�лx */
  RTC->CRL &= (uint16_t)~RTC_FLAG;
}

/**
  * @²�z  �ˬd���w�� RTC ���_�o�ͻP�_.
  * @param  RTC_IT: �n�ˬd��RTC���_��.
  *                 �o�ӰѼƥi�H��U�����Ȥ��@:
  *                 RTC_IT_OW:  ���X���_
  *                 RTC_IT_ALR: ��ĵ���_
  *                 RTC_IT_SEC: ���_
  * @��^  RTC_IT ���s���A (SET �� RESET).
  */
ITStatus RTC_GetITStatus(uint16_t RTC_IT)
{
  ITStatus bitstatus = RESET;
  /* �ˬd�Ѽ� */
  assert_param(IS_RTC_GET_IT(RTC_IT)); 
  
  bitstatus = (ITStatus)(RTC->CRL & RTC_IT);
  if (((RTC->CRH & RTC_IT) != (uint16_t)RESET) && (bitstatus != (uint16_t)RESET))
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
  * @²�z  �M�� RTC �����_�ݳB�z��.
  * @�Ѽ�  RTC_IT: �ݲM���� RTC ���_�ݳB�z��.
  *                �o�ӰѼƥi�H�O�U���Ȫ����N�զX:
  *                RTC_IT_OW:  ���X���_
  *                RTC_IT_ALR: ��ĵ���_
  *                RTC_IT_SEC: ���_
  * @��^  �S��
  */
void RTC_ClearITPendingBit(uint16_t RTC_IT)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_RTC_IT(RTC_IT));  
  
  /* �M�� RTC ���_�лx */
  RTC->CRL &= (uint16_t)~RTC_IT;
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
