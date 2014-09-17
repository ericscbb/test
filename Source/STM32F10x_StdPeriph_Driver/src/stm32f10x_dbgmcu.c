/**
  ******************************************************************************
  * @���    stm32f10x_dbgmcu.c
  * @�@��    MCD ���ε{�ǲ�
  * @����    V3.1.0
  * @���    06/19/2009
  * @²�z    �o�Ӥ�� ���ѩҦ� DBGMCU �T����.
  * @½Ķ    ANSON/sweet1985 Email:airanson110@126.com
  * @���    21/07/2009
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
#include "stm32f10x_dbgmcu.h"

/* �ۥ����� --------------------------------------------------------------*/
/* �ۥΩw�q --------------------------------------------------------------*/

#define IDCODE_DEVID_Mask    ((uint32_t)0x00000FFF)

/* �ۥΧ� -------------------------------------------------------------*/
/* �ۥ��ܶq -----------------------------------------------------------*/
/* �ۥΨ�ƭ쫬 -------------------------------------------------------*/
/* �ۥΨ�� -----------------------------------------------------------*/

/**
  * @²�z  ��^�]�ƪ��ե��Хܲ�.
  * @�Ѽ�  None
  * @��^  �]�ƪ��ե��Хܲ�
  */
uint32_t DBGMCU_GetREVID(void)
{
   return(DBGMCU->IDCODE >> 16);
}

/**
  * @²�z  ��^�]�ƪ��Хܲ�.
  * @�Ѽ�  �S��
  * @��^  �]�ƪ��Хܲ�
  */
uint32_t DBGMCU_GetDEVID(void)
{
   return(DBGMCU->IDCODE & IDCODE_DEVID_Mask);
}

/**
  * @²�z  �t�mMCU�b�ոռҦ��U���w�~�]�M�C�\�ӼҦ����A.
  * @�Ѽ�  DBGMCU_Periph: ���w���~�]�M�C�\�ӼҦ�.
  *          �i�H�ϥΤU�z���N�Ȫ��զX:
  *          DBGMCU_SLEEP:     �b�ίv�Ҧ��O���ով����s��              
  *          DBGMCU_STOP:      �b����Ҧ��O���ով����s��               
  *          DBGMCU_STANDBY:   �b�ݾ��Ҧ��O���ով����s��            
  *          DBGMCU_IWDG_STOP: ���ְ���ɰ���ո� IWDG          
  *          DBGMCU_WWDG_STOP: ���ְ���ɰ���ո� WWDG          
  *          DBGMCU_TIM1_STOP: ���ְ���ɰ��� TIM1 �p�ƾ�          
  *          DBGMCU_TIM2_STOP: ���ְ���ɰ��� TIM2 �p�ƾ�         
  *          DBGMCU_TIM3_STOP: ���ְ���ɰ��� TIM3 �p�ƾ�         
  *          DBGMCU_TIM4_STOP: ���ְ���ɰ��� TIM4 �p�ƾ�        
  *          DBGMCU_CAN1_STOP: ���ְ���ɰ���ո� CAN1 
  *          DBGMCU_I2C1_SMBUS_TIMEOUT: ���ְ���ɰ��� I2C1 �`�u�W�ɼҦ�
  *          DBGMCU_I2C2_SMBUS_TIMEOUT: ���ְ���ɰ��� I2C2 �`�u�W�ɼҦ�
  *          DBGMCU_TIM5_STOP: ���ְ���ɰ��� TIM5 �p�ƾ�          
  *          DBGMCU_TIM6_STOP: ���ְ���ɰ��� TIM6 �p�ƾ�         
  *          DBGMCU_TIM7_STOP: ���ְ���ɰ��� TIM7 �p�ƾ�         
  *          DBGMCU_TIM8_STOP: ���ְ���ɰ��� TIM8 �p�ƾ�
  *          DBGMCU_CAN2_STOP: ���ְ���ɰ���ո� CAN2  
  * @�Ѽ�  NewState: ���w���~�]�b�C�\�ӼҦ����s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_DBGMCU_PERIPH(DBGMCU_Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    DBGMCU->CR |= DBGMCU_Periph;
  }
  else
  {
    DBGMCU->CR &= ~DBGMCU_Periph;
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
