/**
  ******************************************************************************
  * @���    stm32f10x_iwdg.c
  * @�@��    MCD ���ε{�ǲ�
  * @����    V3.1.0
  * @���    06/19/2009
  * @²�z    �o�Ӥ�� ���ѩҦ� IWDG �T����.
  * @½Ķ    ANSON/sweet1985 Email:airanson110@126.com
  * @���    09/07/2009
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
#include "stm32f10x_iwdg.h"

/* �ۥ����� --------------------------------------------------------------*/
/* �ۥΩw�q --------------------------------------------------------------*/

/* ---------------------- IWDG registers bit mask ----------------------------*/

/* KR register bit mask */
#define KR_KEY_Reload    ((uint16_t)0xAAAA)
#define KR_KEY_Enable    ((uint16_t)0xCCCC)

/* �ۥΧ� -------------------------------------------------------------*/
/* �ۥ��ܶq -----------------------------------------------------------*/
/* �ۥΨ�ƭ쫬 -------------------------------------------------------*/
/* �ۥΨ�� -----------------------------------------------------------*/


/**
  * @²�z  �ϯ�Ϊ̥����H�s�� IWDG_PR �M IWDG_RLR ���g�ާ@.
  * @�Ѽ�  IWDG_WriteAccess: �� IWDG_PR �M IWDG_RLR �H�s�����g�X�ݪ��s�����A.
  *                          �o�ӰѼƥi�H�O�U�����Ȥ��@:
  *                          IWDG_WriteAccess_Enable:  �ϯ��H�s�� IWDG_PR �M IWDG_RLR ���g�ާ@
  *                          IWDG_WriteAccess_Disable: �����H�s�� IWDG_PR �M IWDG_RLR ���g�ާ@
  * @��^  �S��
  */
void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_IWDG_WRITE_ACCESS(IWDG_WriteAccess));
  IWDG->KR = IWDG_WriteAccess;
}

/**
  * @²�z  �]�m IWDG �w���W��.
  * @�Ѽ�  IWDG_Prescaler: ���w IWDG �w���W��.
  *                        �o�ӰѼƥi�H�O�U�����Ȥ��@:
  *                        IWDG_Prescaler_4:   �]�mIWDG�w���W�Ȭ� 4
  *                        IWDG_Prescaler_8:   �]�mIWDG�w���W�Ȭ� 8
  *                        IWDG_Prescaler_16:  �]�mIWDG�w���W�Ȭ� 16
  *                        IWDG_Prescaler_32:  �]�mIWDG�w���W�Ȭ� 32
  *                        IWDG_Prescaler_64:  �]�mIWDG�w���W�Ȭ� 64
  *                        IWDG_Prescaler_128: �]�mIWDG�w���W�Ȭ� 128
  *                        IWDG_Prescaler_256: �]�mIWDG�w���W�Ȭ� 256
  * @��^  �S��
  */
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_IWDG_PRESCALER(IWDG_Prescaler));
  IWDG->PR = IWDG_Prescaler;
}

/**
  * @²�z  �]�m IWDG ���˸���.
  * @�Ѽ�  Reload: ���w IWDG ���˸���.
  *                �o�ӰѼƤ@�w�O�b'0'��'0x0FFF'��������.
  * @��^  �S��
  */
void IWDG_SetReload(uint16_t Reload)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_IWDG_RELOAD(Reload));
  IWDG->RLR = Reload;
}

/**
  * @²�z  ���� IWDG ���˸��H�s�����ȭ��˸� IWDG �p�ƾ�
  *        (�� IWDG_PR �M IWDG_RLR �H�s�����g�X�ݳQ�T��).
  * @�Ѽ�  �S��
  * @��^  �S��
  */
void IWDG_ReloadCounter(void)
{
  IWDG->KR = KR_KEY_Reload;
}

/**
  * @²�z  �ϯ� IWDG (�� IWDG_PR �M IWDG_RLR �H�s�����g�X�ݳQ�T��).
  * @�Ѽ�  �S��
  * @��^  �S��
  */
void IWDG_Enable(void)
{
  IWDG->KR = KR_KEY_Enable;
}

/**
  * @²�z  �ˬd���w�� IWDG �лx��Q�]�m�P�_.
  * @�Ѽ�  IWDG_FLAG: �n�ˬd���лx.
  *                   �o�ӰѼƥi�H�O�U�����Ȥ��@:
  *                   IWDG_FLAG_PVU: �w���W�]�l�ȧ�s�F
  *                   IWDG_FLAG_RVU: �����ȧ�s�F
  * @��^  IWDG_FLAG ���s���A (SET �� RESET).
  */
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* �ˬd�Ѽ� */
  assert_param(IS_IWDG_FLAG(IWDG_FLAG));
  if ((IWDG->SR & IWDG_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* ��^�лx���A */
  return bitstatus;
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
