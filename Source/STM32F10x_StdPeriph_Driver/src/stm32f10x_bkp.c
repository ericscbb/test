/**
  ******************************************************************************
  * @���    stm32f10x_bkp.c
  * @�@��    MCD ���ε{�ǲ�
  * @����    V3.1.0
  * @���    06/19/2009
  * @²�z    �o�Ӥ�󴣨ѤF�Ҧ� BKP �T����.
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
#include "stm32f10x_bkp.h"
#include "stm32f10x_rcc.h"

/* �ۥ����� --------------------------------------------------------------*/
/* �ۥΩw�q --------------------------------------------------------------*/

/* ------------ BKP registers bit address in the alias region --------------- */
#define BKP_OFFSET        (BKP_BASE - PERIPH_BASE)

/* --- CR Register ----*/

/* Alias word address of TPAL bit */
#define CR_OFFSET         (BKP_OFFSET + 0x30)
#define TPAL_BitNumber    0x01
#define CR_TPAL_BB        (PERIPH_BB_BASE + (CR_OFFSET * 32) + (TPAL_BitNumber * 4))

/* Alias word address of TPE bit */
#define TPE_BitNumber     0x00
#define CR_TPE_BB         (PERIPH_BB_BASE + (CR_OFFSET * 32) + (TPE_BitNumber * 4))

/* --- CSR Register ---*/

/* Alias word address of TPIE bit */
#define CSR_OFFSET        (BKP_OFFSET + 0x34)
#define TPIE_BitNumber    0x02
#define CSR_TPIE_BB       (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (TPIE_BitNumber * 4))

/* Alias word address of TIF bit */
#define TIF_BitNumber     0x09
#define CSR_TIF_BB        (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (TIF_BitNumber * 4))

/* Alias word address of TEF bit */
#define TEF_BitNumber     0x08
#define CSR_TEF_BB        (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (TEF_BitNumber * 4))

/* ---------------------- BKP registers bit mask ------------------------ */

/* RTCCR register bit mask */
#define RTCCR_CAL_Mask    ((uint16_t)0xFF80)
#define RTCCR_Mask        ((uint16_t)0xFC7F)

/* CSR register bit mask */
#define CSR_CTE_Set       ((uint16_t)0x0001)
#define CSR_CTI_Set       ((uint16_t)0x0002)

/* �ۥΧ� -------------------------------------------------------------*/
/* �ۥ��ܶq -----------------------------------------------------------*/
/* �ۥΨ�ƭ쫬 -------------------------------------------------------*/
/* �ۥΨ�� -----------------------------------------------------------*/

/**
  * @²�z  �N BKP �~�]�H�s���_��쥦�̪��q�{��.
  * @�Ѽ�  �S��
  * @��^  �S��
  */
void BKP_DeInit(void)
{
  RCC_BackupResetCmd(ENABLE);
  RCC_BackupResetCmd(DISABLE);
}

/**
  * @²�z  �]�m�I�J�˴��޸}�����Ĺq��.
  * @�Ѽ�  BKP_TamperPinLevel: �I�J�˴��޸}�����Ĺq��.
  *                            �o�ӰѼƥi�H���U�������@��:
  *                            BKP_TamperPinLevel_High: �I�J�˴��޸}���q������
  *                            BKP_TamperPinLevel_Low:  �I�J�˴��޸}�C�q������
  * @��^  �S��
  */
void BKP_TamperPinLevelConfig(uint16_t BKP_TamperPinLevel)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_BKP_TAMPER_PIN_LEVEL(BKP_TamperPinLevel));
  *(__IO uint32_t *) CR_TPAL_BB = BKP_TamperPinLevel;
}

/**
  * @²�z  �ϯ�Υ���I�J�˴��޸}.
  * @�Ѽ�  NewState: �I�J�˴��޸}���s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void BKP_TamperPinCmd(FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CR_TPE_BB = (uint32_t)NewState;
}

/**
  * @²�z  �ϯ�Υ���I�J�˴��޸}�����_.
  * @�Ѽ�  NewState: �I�J�˴��޸}�����_���s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void BKP_ITConfig(FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CSR_TPIE_BB = (uint32_t)NewState;
}

/**
  * @²�z  ��ܦb�I�J�˴��޸}�W��X�� RTC ������.
  * @�Ѽ�  BKP_RTCOutputSource: ���w RTC ��X���ӷ�.
  *                             �o�ӰѼƥi�H���U�������@��:
  *            BKP_RTCOutputSource_None: �I�J�˴��޸}�W�S����ɮ�����X.
  *            BKP_RTCOutputSource_CalibClock: �I�J�˴��޸}�W��X��ɮ����iĵ�߽ĤW��X����ɮ��������W�v���H64.
  *            BKP_RTCOutputSource_Alarm: �I�J�˴��޸}�W��X��ɮ����iĵ�߽�.
  *            BKP_RTCOutputSource_Second: �I�J�˴��޸}�W��X��ɮ�����߽�.  
  * @��^  �S��
  */
void BKP_RTCOutputConfig(uint16_t BKP_RTCOutputSource)
{
  uint16_t tmpreg = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_BKP_RTC_OUTPUT_SOURCE(BKP_RTCOutputSource));
  tmpreg = BKP->RTCCR;
  /* �M�� CCO, ASOE �M ASOS �� */
  tmpreg &= RTCCR_Mask;
  
  /* �]�m CCO, ASOE �M ASOS ��A���� BKP_RTCOutputSource ���� */
  tmpreg |= BKP_RTCOutputSource;
  /* �s�x�s�� */
  BKP->RTCCR = tmpreg;
}

/**
  * @²�z  �]�m RTC �����շǭ�.
  * @�Ѽ�  CalibrationValue: ���w RTC �������շǭ�.
  *                          �o�ӰѼƥ����b 0 �M 0x7F ����.
  * @��^  �S��
  */
void BKP_SetRTCCalibrationValue(uint8_t CalibrationValue)
{
  uint16_t tmpreg = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_BKP_CALIBRATION_VALUE(CalibrationValue));
  tmpreg = BKP->RTCCR;
  /* �M�� CAL[6:0] �� */
  tmpreg &= RTCCR_CAL_Mask;
  /* �]�m CAL[6:0] ��A���� CalibrationValue ���� */
  tmpreg |= CalibrationValue;
  /* �s�x�s�� */
  BKP->RTCCR = tmpreg;
}

/**
  * @²�z  �V���w����ƱH�s�����g�J�Τ�{�Ǽƾ�.
  * @�Ѽ�  BKP_DR: ���w����ƱH�s��.
  *                �o�ӰѼ� BKP_DRx ��x�i�H��[1, 42]
  * @�Ѽ�  Data: �ݭn�g�J���ƾ�
  * @��^  �S��
  */
void BKP_WriteBackupRegister(uint16_t BKP_DR, uint16_t Data)
{
  __IO uint32_t tmp = 0;

  /* �ˬd�Ѽ� */
  assert_param(IS_BKP_DR(BKP_DR));

  tmp = (uint32_t)BKP_BASE; 
  tmp += BKP_DR;

  *(__IO uint32_t *) tmp = Data;
}

/**
  * @²�z  �q���w���ƾڳƥ��H�s����Ū�X�ƾ�.
  * @�Ѽ�  BKP_DR: ���w���ƾڳƥ��H�s��.
  *                �o�ӰѼ� BKP_DRx ��x�i�H��[1, 42]
  * @��^  ���w���ƾڳƥ��H�s�������e
  */
uint16_t BKP_ReadBackupRegister(uint16_t BKP_DR)
{
  __IO uint32_t tmp = 0;

  /* �ˬd�Ѽ� */
  assert_param(IS_BKP_DR(BKP_DR));

  tmp = (uint32_t)BKP_BASE; 
  tmp += BKP_DR;

  return (*(__IO uint16_t *) tmp);
}

/**
  * @²�z  �ˬd�I�J�˴��޸}�ƥ󪺼лx��Q�]�m�P�_ ��.
  * @�Ѽ�  �S��
  * @��^  �I�J�˴��޸}�ƥ󪺼лx���s���A (SET �� RESET).
  */
FlagStatus BKP_GetFlagStatus(void)
{
  return (FlagStatus)(*(__IO uint32_t *) CSR_TEF_BB);
}

/**
  * @²�z  �M���I�J�˴��޸}�ƥ󪺫ݳB�z�лx��.
  * @�Ѽ�  �S��
  * @��^  �S��
  */
void BKP_ClearFlag(void)
{
  /* �]�m CTE ��A�M���I�J�˴��޸}�ƥ󪺫ݳB�z�лx�� */
  BKP->CSR |= CSR_CTE_Set;
}

/**
  * @²�z  �ˬd�I�J�˴����_�o�ͻP�_.
  * @�Ѽ�  �S��
  * @��^  �I�J�˴����_�лx�쪺�s���A (SET �� RESET).
  */
ITStatus BKP_GetITStatus(void)
{
  return (ITStatus)(*(__IO uint32_t *) CSR_TIF_BB);
}

/**
  * @²�z  �M���I�I�J�˴����_���ݳB�z��.
  * @�Ѽ�  �S��
  * @��^  �S��
  */
void BKP_ClearITPendingBit(void)
{
  /* �]�m CTI ��A �M���I�I�J�˴����_���ݳB�z�� */
  BKP->CSR |= CSR_CTI_Set;
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
