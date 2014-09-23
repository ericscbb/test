/**
  ******************************************************************************
  * @���    stm32f10x_wwdg.c
  * @�@��    MCD ���ε{�ǲ�
  * @����    V3.1.0
  * @���    06/19/2009
  * @²�z    �o�Ӥ�� ���ѩҦ� WWDG �T����.
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_wwdg.h"
#include "stm32f10x_rcc.h"

/* �ۥ����� --------------------------------------------------------------*/
/* �ۥΩw�q --------------------------------------------------------------*/

/* ----------- WWDG registers bit address in the alias region ----------- */
#define WWDG_OFFSET       (WWDG_BASE - PERIPH_BASE)

/* Alias word address of EWI bit */
#define CFR_OFFSET        (WWDG_OFFSET + 0x04)
#define EWI_BitNumber     0x09
#define CFR_EWI_BB        (PERIPH_BB_BASE + (CFR_OFFSET * 32) + (EWI_BitNumber * 4))

/* --------------------- WWDG registers bit mask ------------------------ */

/* CR register bit mask */
#define CR_WDGA_Set       ((uint32_t)0x00000080)

/* CFR register bit mask */
#define CFR_WDGTB_Mask    ((uint32_t)0xFFFFFE7F)
#define CFR_W_Mask        ((uint32_t)0xFFFFFF80)
#define BIT_Mask          ((uint8_t)0x7F)

/* �ۥΧ� -------------------------------------------------------------*/
/* �ۥ��ܶq -----------------------------------------------------------*/
/* �ۥΨ�ƭ쫬 -------------------------------------------------------*/
/* �ۥΨ�� -----------------------------------------------------------*/

/**
  * @²�z  �N�~�] WWDG �H�s�����]���ʬ٭�.
  * @�Ѽ�  �S��
  * @��^  �S��
  */
void WWDG_DeInit(void)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, DISABLE);
}

/**
  * @²�z  �]�m WWDG �w���W��.
  * @�Ѽ�  WWDG_Prescaler: ���w WWDG �w���W��.
  *                        �o�ӰѼƥi�H�O�U�����Ȥ��@:
  *                        WWDG_Prescaler_1: WWDG �p�ƾ����� = (PCLK1/4096)/1
  *                        WWDG_Prescaler_2: WWDG �p�ƾ����� = (PCLK1/4096)/2
  *                        WWDG_Prescaler_4: WWDG �p�ƾ����� = (PCLK1/4096)/4
  *                        WWDG_Prescaler_8: WWDG �p�ƾ����� = (PCLK1/4096)/8
  * @��^  �S��
  */
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler)
{
  uint32_t tmpreg = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_WWDG_PRESCALER(WWDG_Prescaler));
  /* �M�� WDGTB[1:0] �� */
  tmpreg = WWDG->CFR & CFR_WDGTB_Mask;
  /* �]�m WDGTB[1:0] ��A���� WWDG_Prescaler ���� */
  tmpreg |= WWDG_Prescaler;
  /* �s�x�s�� */
  WWDG->CFR = tmpreg;
}

/**
  * @²�z  �]�m WWDG ���f��.
  * @�Ѽ�  �����n�M�˭p�ƾ���������f��.
  *        �o�ӭӰѼƪ��ȥ����p��0x80.
  * @��^  �S��
  */
void WWDG_SetWindowValue(uint8_t WindowValue)
{
  __IO uint32_t tmpreg = 0;

  /* �ˬd�Ѽ� */
  assert_param(IS_WWDG_WINDOW_VALUE(WindowValue));
  /* �M�� W[6:0] �� */

  tmpreg = WWDG->CFR & CFR_W_Mask;

  /* �̷ӵ��f�Ȫ��ȳ]�m W[6:0] �� */
  tmpreg |= WindowValue & (uint32_t) BIT_Mask;

  /* �s�x�s�� */
  WWDG->CFR = tmpreg;
}

/**
  * @²�z  �ϯ� WWDG ����������_ (EWI).
  * @�Ѽ�  �S��
  * @��^  �S��
  */
void WWDG_EnableIT(void)
{
  *(__IO uint32_t *) CFR_EWI_BB = (uint32_t)ENABLE;
}

/**
  * @²�z  �]�m WWDG �p�ƾ���.
  * @�Ѽ�  Counter: ���w�ݪ����p�ƾ���.
  *                 �ӰѼƨ��ȥ����b0x40�P0x7F����.
  * @��^  �S��
  */
void WWDG_SetCounter(uint8_t Counter)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_WWDG_COUNTER(Counter));
  /* ���t�m�p�ƾ����ȼg T[6:0]��A���F�g0��WDG A��S���N�q */
  WWDG->CR = Counter & BIT_Mask;
}

/**
  * @²�z  �ϯ� WWDG �M���J�p�ƾ�����.                  
  * @�Ѽ�  Counter: ���w�ݪ������J�p�ƾ�����.
  *                 �o�ӰѼƥ����O0x40��0x7F�������@�Ӽ�.
  * @��^  �S��
  */
void WWDG_Enable(uint8_t Counter)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_WWDG_COUNTER(Counter));
  WWDG->CR = CR_WDGA_Set | Counter;
}

/**
  * @²�z  �ˬd WWDG ����������_�лx��Q�]�m�P�_.
  * @�Ѽ�  �S��
  * @��^  ����������_�лx�쪺�s���A (SET �� RESET)
  */
FlagStatus WWDG_GetFlagStatus(void)
{
  return (FlagStatus)(WWDG->SR);
}

/**
  * @²�z  �M������������_�лx��.
  * @�Ѽ�  �S��
  * @��^  �S��
  */
void WWDG_ClearFlag(void)
{
  WWDG->SR = (uint32_t)RESET;
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
