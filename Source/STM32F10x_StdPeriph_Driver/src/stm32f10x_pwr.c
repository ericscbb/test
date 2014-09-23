/**
  ******************************************************************************
  * @file    stm32f10x_pwr.c
  * @author  MCD ���ε{�ǲ�
  * @version V3.1.0
  * @date    06/19/2009
  * @brief   �o�Ӥ�� ���ѩҦ� PWR �T����.
  * @½Ķ    ANSON/sweet1985 Email:airanson110@126.com
  * @���    07/07/2009
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
#include "stm32f10x_pwr.h"
#include "stm32f10x_rcc.h"

/* �ۥ����� ------------------------------------------------------------*/
/* �ۥΩw�q ------------------------------------------------------------*/

/* --------- PWR registers bit address in the alias region ------------ */
#define PWR_OFFSET               (PWR_BASE - PERIPH_BASE)

/* --- CR �H�s�� ---*/

/* Alias word address of DBP bit */
#define CR_OFFSET                (PWR_OFFSET + 0x00)
#define DBP_BitNumber            0x08
#define CR_DBP_BB                (PERIPH_BB_BASE + (CR_OFFSET * 32) + (DBP_BitNumber * 4))

/* Alias word address of PVDE bit */
#define PVDE_BitNumber           0x04
#define CR_PVDE_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PVDE_BitNumber * 4))

/* --- CSR �H�s�� ---*/

/* Alias word address of EWUP bit */
#define CSR_OFFSET               (PWR_OFFSET + 0x04)
#define EWUP_BitNumber           0x08
#define CSR_EWUP_BB              (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (EWUP_BitNumber * 4))

/* ------------------ PWR �H�s����̽� ------------------------ */

/* CR register bit mask */
#define CR_PDDS_Set              ((uint32_t)0x00000002)
#define CR_DS_Mask               ((uint32_t)0xFFFFFFFC)
#define CR_CWUF_Set              ((uint32_t)0x00000004)
#define CR_PLS_Mask              ((uint32_t)0xFFFFFF1F)

/* --------- Cortex �t�α���H�s����̽� ---------------------- */

/* Cortex �t�α���H�s���a�} */
#define SCB_SysCtrl              ((uint32_t)0xE000ED10)

/* SLEEPDEEP ��̽� */
#define SysCtrl_SLEEPDEEP_Set    ((uint32_t)0x00000004)

/* �ۥΧ� -------------------------------------------------------------*/
/* �ۥ��ܶq -----------------------------------------------------------*/
/* �ۥΨ�ƭ쫬 -------------------------------------------------------*/
/* �ۥΨ�� -----------------------------------------------------------*/

/**
  * @²�z  �_�� PWR �~��H�s�����q�{�_���.
  * @�Ѽ�  �S��
  * @��^  �S��
  */
void PWR_DeInit(void)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, DISABLE);
}

/**
  * @²�z  �ϯ�Ϊ̥��� RTC �M��ƱH�s���X��.
  * @�Ѽ�  NewState: �X�� RTC �M�ƥ��H�s�����s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void PWR_BackupAccessCmd(FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CR_DBP_BB = (uint32_t)NewState;
}

/**
  * @²�z  �ϯ�Ϊ̥���i�s�{�q�������� (PVD).
  * @�Ѽ�  NewState: PVD ���s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void PWR_PVDCmd(FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CR_PVDE_BB = (uint32_t)NewState;
}

/**
  * @²�z  �]�m PVD �������q���H�� (PVD).
  * @�Ѽ�  PWR_PVDLevel: PVD �������q���H��
  *                      �o�ӰѼƥi�H�O�U�C�Ȥ����@��:
  *          PWR_PVDLevel_2V2: PVD �����q���H�� 2.2V
  *          PWR_PVDLevel_2V3: PVD �����q���H�� 2.3V
  *          PWR_PVDLevel_2V4: PVD �����q���H�� 2.4V
  *          PWR_PVDLevel_2V5: PVD �����q���H�� 2.5V
  *          PWR_PVDLevel_2V6: PVD �����q���H�� 2.6V
  *          PWR_PVDLevel_2V7: PVD �����q���H�� 2.7V
  *          PWR_PVDLevel_2V8: PVD �����q���H�� 2.8V
  *          PWR_PVDLevel_2V9: PVD �����q���H�� 2.9V
  * @��^  �S��
  */
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel)
{
  uint32_t tmpreg = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_PWR_PVD_LEVEL(PWR_PVDLevel));
  tmpreg = PWR->CR;
  /* �M�� PLS[7:5] �� */
  tmpreg &= CR_PLS_Mask;
  /* �]�m PLS[7:5] �� ���� PWR_PVDLevel ���� */
  tmpreg |= PWR_PVDLevel;
  /* �s�x�s�� */
  PWR->CR = tmpreg;
}

/**
  * @²�z  �ϯ�Ϊ̥������޸}�\��.
  * @�Ѽ�  NewState: ����޸}�\�઺�s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void PWR_WakeUpPinCmd(FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CSR_EWUP_BB = (uint32_t)NewState;
}

/**
  * @²�z  �i�J����(STOP)�Ҧ�.
  * @�Ѽ�  PWR_Regulator: �q���ഫ���b����Ҧ��U�����A.
  *                       �o�ӰѼƥi�H�O�U�C�Ȥ����@��:
  *                       PWR_Regulator_ON: ����Ҧ��U�q���ഫ�� ON
  *                       PWR_Regulator_LowPower: ����Ҧ��U�q���ഫ���i�J�C�\�ӼҦ�
  * @�Ѽ�  PWR_STOPEntry: ��ܨϥΫ��O WFE �٬O WFI �Ӷi�J����Ҧ�.
  *                       �o�ӰѼƥi�H�O�U�C�Ȥ����@��:
  *                       PWR_STOPEntry_WFI: �ϥΫ��O WFI �Ӷi�J����Ҧ�
  *                       PWR_STOPEntry_WFE: �ϥΫ��O WFE �Ӷi�J����Ҧ�
  * @��^  �S��
  */
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry)
{
  uint32_t tmpreg = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_PWR_REGULATOR(PWR_Regulator));
  assert_param(IS_PWR_STOP_ENTRY(PWR_STOPEntry));
  
  /* �b����Ҧ���ܮշǪ��A ---------------------------------*/
  tmpreg = PWR->CR;
  /* �M PDDS �M LPDS �� */
  tmpreg &= CR_DS_Mask;
  /* �̷� PWR_Regulator �ȸm�� LPDS */
  tmpreg |= PWR_Regulator;
  /* �O�s�s���� */
  PWR->CR = tmpreg;
  /* �]�m SLEEPDEEP ����� Cortex �t�α���H�s�� */
  *(__IO uint32_t *) SCB_SysCtrl |= SysCtrl_SLEEPDEEP_Set;
  
  /* ��ܰ���Ҧ��i�J --------------------------------------------------*/
  if(PWR_STOPEntry == PWR_STOPEntry_WFI)
  {   
    /* �ШD���ݤ��_ */
    __WFI();
  }
  else
  {
    /* �ШD���ݨƥ� */
    __WFE();
  }
}

/**
  * @²�z  �i�J�ݾ�(STANDBY)�Ҧ�.
  * @�Ѽ�  �S��
  * @��^  �S��
  */
void PWR_EnterSTANDBYMode(void)
{
  /* �M�� Wake-up �лx */
  PWR->CR |= CR_CWUF_Set;
  /* ��� STANDBY �Ҧ� */
  PWR->CR |= CR_PDDS_Set;
  /* �m�� Cortex �t�Ϊ�����H�s�� SLEEPDEEP �� */
  *(__IO uint32_t *) SCB_SysCtrl |= SysCtrl_SLEEPDEEP_Set;
/* �o�ӿ�ܱ`�`�O�T�w�s�x�ާ@�w���� */
#if defined ( __CC_ARM   )
  __force_stores();
#endif
  /* �ШD���ݤ��_ */
  __WFI();
}

/**
  * @²�z  �ˬd���w�� PWR �лx��]�m�P�_.
  * @�Ѽ�  PWR_FLAG: �n�ˬd���лx.
  *                  �o�ӰѼƥi�H�O�U�����Ȥ��@:
  *                  PWR_FLAG_WU: ����лx
  *                  PWR_FLAG_SB: �ݩR�лx
  *                  PWR_FLAG_PVDO: PVD ��X
  * @��^  PWR_FLAG ���s���A (SET or RESET).
  */
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* �ˬd�Ѽ� */
  assert_param(IS_PWR_GET_FLAG(PWR_FLAG));
  
  if ((PWR->CSR & PWR_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* ��^���A�лx */
  return bitstatus;
}

/**
  * @²�z  �M�� PWR ���_�лx��.
  * @�Ѽ�  PWR_FLAG: �n�M�Ū��лx.
  *                  �o�ӰѼƥi�H�O�U�����Ȥ��@:
  *                  PWR_FLAG_WU: ����лx
  *                  PWR_FLAG_SB: �ݩR�лx
  * @��^  �S��
  */
void PWR_ClearFlag(uint32_t PWR_FLAG)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_PWR_CLEAR_FLAG(PWR_FLAG));
         
  PWR->CR |=  PWR_FLAG << 2;
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
