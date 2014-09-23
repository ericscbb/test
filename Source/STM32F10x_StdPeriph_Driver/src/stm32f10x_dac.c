/**
  ******************************************************************************
  * @���    stm32f10x_dac.c
  * @�@��    MCD ���ε{�ǲ�
  * @����    V3.1.0
  * @���    06/19/2009
  * @²�z    �o�Ӥ�� ���ѩҦ� DAC �T����.
  * @½Ķ    ANSON/sweet1985 Email:airanson110@126.com
  * @���    18/07/2009
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
#include "stm32f10x_dac.h"
#include "stm32f10x_rcc.h"

/* �ۥ����� --------------------------------------------------------------*/
/* �ۥΩw�q --------------------------------------------------------------*/

/* DAC EN mask */
#define CR_EN_Set                  ((uint32_t)0x00000001)

/* DAC DMAEN mask */
#define CR_DMAEN_Set               ((uint32_t)0x00001000)

/* CR register Mask */
#define CR_CLEAR_Mask              ((uint32_t)0x00000FFE)

/* DAC SWTRIG mask */
#define SWTRIGR_SWTRIG_Set         ((uint32_t)0x00000001)

/* DAC Dual Channels SWTRIG masks */
#define DUAL_SWTRIG_Set            ((uint32_t)0x00000003)
#define DUAL_SWTRIG_Reset          ((uint32_t)0xFFFFFFFC)

/* DHR registers offsets */
#define DHR12R1_Offset             ((uint32_t)0x00000008)
#define DHR12R2_Offset             ((uint32_t)0x00000014)
#define DHR12RD_Offset             ((uint32_t)0x00000020)

/* DOR register offset */
#define DOR_Offset                 ((uint32_t)0x0000002C)

/* �ۥΧ� -------------------------------------------------------------*/
/* �ۥ��ܶq -----------------------------------------------------------*/
/* �ۥΨ�ƭ쫬 -------------------------------------------------------*/
/* �ۥΨ�� -----------------------------------------------------------*/

/**
  * @²�z  �N DAC ���󪺱H�s���_�쬰�q�{��
  * @�Ѽ�  �S��
  * @��^  �S��
  */
void DAC_DeInit(void)
{
  /* �ϯ� DAC �_�쪬�A */
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_DAC, ENABLE);
  /* ���� DAC �_�쪬�A */
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_DAC, DISABLE);
}

/**
  * @²�z  �̷� DAC_InitStruct ���w���Ѽƪ�l�� DAC �~���]��.
  * @�Ѽ�  DAC_Channel: ��w�� DAC �q�D. 
  *          �o�ӰѼƥi�H�O�U�C�Ȥ��@:
  *          DAC_Channel_1: ��w DAC �q�D1
  *          DAC_Channel_2: ��w DAC �q�D2
  * @�Ѽ�  DAC_InitStruct: ���V�]�t�F���w DAC �q�D�t�m�H���� DAC_InitTypeDef ���c���w.
  * @��^  �S��
  */
void DAC_Init(uint32_t DAC_Channel, DAC_InitTypeDef* DAC_InitStruct)
{
  uint32_t tmpreg1 = 0, tmpreg2 = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_DAC_TRIGGER(DAC_InitStruct->DAC_Trigger));
  assert_param(IS_DAC_GENERATE_WAVE(DAC_InitStruct->DAC_WaveGeneration));
  assert_param(IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude));
  assert_param(IS_DAC_OUTPUT_BUFFER_STATE(DAC_InitStruct->DAC_OutputBuffer));
/*---------------------------- DAC CR Configuration --------------------------*/
  /* �o�� DAC CR ���� */
  tmpreg1 = DAC->CR;
  /* �M�� BOFFx, TENx, TSELx, WAVEx �M MAMPx �� */
  tmpreg1 &= ~(CR_CLEAR_Mask << DAC_Channel);
  /* �t�m��w�� DAC �q�D: �w�Ŀ�X, Ĳ�o��, �i�ΫH���o�;�,�i�ΫH���o�;����ɼ�/���T */
  /* �]�m TSELx �M TENx ��A���� DAC_Trigger ���� */
  /* �]�m WAVEx ��A���� DAC_WaveGeneration ���� */
  /* �]�m MAMPx ��A���� DAC_LFSRUnmask_TriangleAmplitude ���� */ 
  /* �]�m BOFFx ��A���� DAC_OutputBuffer ���� */   
  tmpreg2 = (DAC_InitStruct->DAC_Trigger | DAC_InitStruct->DAC_WaveGeneration |
             DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude | DAC_InitStruct->DAC_OutputBuffer);
  /* �ھ�DAC_Channel�p��CR�H�s���� */
  tmpreg1 |= tmpreg2 << DAC_Channel;
  /* �g DAC CR */
  DAC->CR = tmpreg1;
}

/**
  * @²�z  ���q�{�ȶ�R DAC_InitStruct ���c���C�@�Ӧ���.
  * @�Ѽ�  DAC_InitStruct : ���V�N�n�Q��l�ƪ� DAC_InitTypeDef ���c���w.
  * @��^  �S��
  */
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct)
{
/*--------------- Reset DAC init structure parameters values -----------------*/
  /* ��l�� DAC_Trigger ���� */
  DAC_InitStruct->DAC_Trigger = DAC_Trigger_None;
  /* ��l�� DAC_WaveGeneration ���� */
  DAC_InitStruct->DAC_WaveGeneration = DAC_WaveGeneration_None;
  /* ��l�� DAC_LFSRUnmask_TriangleAmplitude ���� */
  DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
  /* ��l�� DAC_OutputBuffer ���� */
  DAC_InitStruct->DAC_OutputBuffer = DAC_OutputBuffer_Enable;
}

/**
  * @²�z  �ϯ�Υ�����w�� DAC �q�D.
  * @�Ѽ�  DAC_Channel: ��w DAC �q�D. 
  *          �o�ӰѼƥi�H�O�U�C�Ȥ��@:
  *          DAC_Channel_1: ��w DAC �q�D1 
  *          DAC_Channel_2: ��w DAC �q�D2  
  * @�Ѽ�  NewState: DAC �q�D���s���A. 
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void DAC_Cmd(uint32_t DAC_Channel, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �ϯ���w�� DAC �q�D */
    DAC->CR |= CR_EN_Set << DAC_Channel;
  }
  else
  {
    /* ������w�� DAC �q�D */
    DAC->CR &= ~(CR_EN_Set << DAC_Channel);
  }
}

/**
  * @²�z  �ϯ�Υ�����w�� DAC �q�D DMA �ШD.
  * @�Ѽ�  DAC_Channel: ��w�� DAC �q�D. 
  *          �o�ӰѼƥi�H�O�U�C�Ȥ��@:
  *          DAC_Channel_1: ��w DAC �q�D1 
  *          DAC_Channel_2: ��w DAC �q�D2  
  * @�Ѽ�  NewState: ���w�� DAC �q�D DMA �ШD���s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void DAC_DMACmd(uint32_t DAC_Channel, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �ϯ���w�� DAC �q�D DMA �ШD */
    DAC->CR |= CR_DMAEN_Set << DAC_Channel;
  }
  else
  {
    /* ������w�� DAC �q�D DMA �ШD */
    DAC->CR &= ~(CR_DMAEN_Set << DAC_Channel);
  }
}

/**
  * @²�z  �ϯ�Υ����ܪ� DAC �q�D�n��Ĳ�o.
  * @�Ѽ�  DAC_Channel: ��w�� DAC �q�D. 
  *          �o�ӰѼƥi�H�O�U�C�Ȥ��@:
  *          DAC_Channel_1: ��w DAC �q�D1 
  *          DAC_Channel_2: ��w DAC �q�D2  
  * @�Ѽ�  NewState: ��ܪ� DAC �q�D�n��Ĳ�o���s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void DAC_SoftwareTriggerCmd(uint32_t DAC_Channel, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �ϯ��ܪ� DAC �q�D�n��Ĳ�o */
    DAC->SWTRIGR |= SWTRIGR_SWTRIG_Set << (DAC_Channel >> 4);
  }
  else
  {
    /* �����ܪ� DAC �q�D�n��Ĳ�o */
    DAC->SWTRIGR &= ~(SWTRIGR_SWTRIG_Set << (DAC_Channel >> 4));
  }
}

/**
  * @²�z  �ϯ�Υ����� DAC �q�D�P�B�n��Ĳ�o.
  * @�Ѽ�  NewState: ��� DAC �q�D�P�B�n��Ĳ�o���s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void DAC_DualSoftwareTriggerCmd(FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �ϯ��� DAC �q�D�P�B�n��Ĳ�o */
    DAC->SWTRIGR |= DUAL_SWTRIG_Set ;
  }
  else
  {
    /* ������ DAC �q�D�P�B�n��Ĳ�o */
    DAC->SWTRIGR &= DUAL_SWTRIG_Reset;
  }
}

/**
  * @²�z  �ϯ�Υ����ܪ� DAC �q�D�i�εo��.
  * @�Ѽ�  DAC_Channel: ��w�� DAC �q�D. 
  *          �o�ӰѼƥi�H�O�U�C�Ȥ��@:
  *          DAC_Channel_1: ��w DAC �q�D1 
  *          DAC_Channel_2: ��w DAC �q�D2 
  * @�Ѽ�  DAC_Wave: ���w���i������.
  *          �o�ӰѼƥi�H�O�U�C�Ȥ��@:
  *          DAC_Wave_Noise:    �����i�εo��
  *          DAC_Wave_Triangle: �T���i�εo��
  * @�Ѽ�  NewState: ��ܪ� DAC �q�D�i�εo�ͪ��s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void DAC_WaveGenerationCmd(uint32_t DAC_Channel, uint32_t DAC_Wave, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_WAVE(DAC_Wave)); 
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �ϯ��ܪ� DAC �q�D��ܪ��i�� */
    DAC->CR |= DAC_Wave << DAC_Channel;
  }
  else
  {
    /* �����ܪ� DAC �q�D��ܪ��i�� */
    DAC->CR &= ~(DAC_Wave << DAC_Channel);
  }
}

/**
  * @²�z  �]�m DAC �q�D1 ��w���ƾګO���H�s����.
  * @�Ѽ�  DAC_Align: DAC �q�D1 ���w���ƾڹ��.
  *          �o�ӰѼƥi�H�O�U�C�Ȥ��@:
  *          DAC_Align_8b_R:  ���8��ƾڥk���
  *          DAC_Align_12b_L: ���12��ƾڥ����
  *          DAC_Align_12b_R: ���12��ƾڥk���
  * @�Ѽ�  Data : �ˤJ��ܪ��ƾګO���H�s�����ƾ�.
  * @��^  �S��
  */
void DAC_SetChannel1Data(uint32_t DAC_Align, uint16_t Data)
{  
  __IO uint32_t tmp = 0;
  
  /* �ˬd�Ѽ� */
  assert_param(IS_DAC_ALIGN(DAC_Align));
  assert_param(IS_DAC_DATA(Data));
  
  tmp = (uint32_t)DAC_BASE; 
  tmp += DHR12R1_Offset + DAC_Align;

  /* �]�m DAC �q�D1 ��w���ƾګO���H�s���� */
  *(__IO uint32_t *) tmp = Data;
}

/**
  * @²�z  �]�m DAC �q�D2 ��w���ƾګO���H�s����.
  * @�Ѽ�  DAC_Align: DAC �q�D2 ���w���ƾڹ��.
  *          �o�ӰѼƥi�H�O�U�C�Ȥ��@:
  *          DAC_Align_8b_R:  ���8��ƾڥk���
  *          DAC_Align_12b_L: ���12��ƾڥ����
  *          DAC_Align_12b_R: ���12��ƾڥk���
  * @�Ѽ�  Data : �ˤJ��ܪ��ƾګO���H�s�����ƾ�.
  * @��^  �S��
  */
void DAC_SetChannel2Data(uint32_t DAC_Align, uint16_t Data)
{
  __IO uint32_t tmp = 0;

  /* �ˬd�Ѽ� */
  assert_param(IS_DAC_ALIGN(DAC_Align));
  assert_param(IS_DAC_DATA(Data));
  
  tmp = (uint32_t)DAC_BASE;
  tmp += DHR12R2_Offset + DAC_Align;

  /* �]�m DAC �q�D2 ��w���ƾګO���H�s���� */
  *(__IO uint32_t *)tmp = Data;
}

/**
  * @²�z  �]�m���q�D DAC ���w���ƾګO���H�s����.
  * @�Ѽ�  DAC_Align: ���q�D DAC ���w�ƾڹ��.
  *          �o�ӰѼƥi�H�O�U�C�Ȥ��@:
  *          DAC_Align_8b_R:  ���8��ƾڥk���
  *          DAC_Align_12b_L: ���12��ƾڥ����
  *          DAC_Align_12b_R: ���12��ƾڥk���
  * @�Ѽ�  Data2: DAC�q�D2 �˸����ܪ��ƾګO���H�s�����ƾ�.
  * @�Ѽ�  Data1: DAC�q�D1 �˸����ܪ��ƾګO���H�s�����ƾ�.
  * @��^  �S��
  */
void DAC_SetDualChannelData(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1)
{
  uint32_t data = 0, tmp = 0;
  
  /* �ˬd�Ѽ� */
  assert_param(IS_DAC_ALIGN(DAC_Align));
  assert_param(IS_DAC_DATA(Data1));
  assert_param(IS_DAC_DATA(Data2));
  
  /* �p��ó]�m�� DAC �ƾګO���H�s������ */
  if (DAC_Align == DAC_Align_8b_R)
  {
    data = ((uint32_t)Data2 << 8) | Data1; 
  }
  else
  {
    data = ((uint32_t)Data2 << 16) | Data1;
  }
  
  tmp = (uint32_t)DAC_BASE;
  tmp += DHR12RD_Offset + DAC_Align;

  /* �]�m�� DAC ��ܪ��ƾګO���H�s�� */
  *(__IO uint32_t *)tmp = data;
}

/**
  * @²�z  ��^�̷s�� DAC �q�D�ƾڱH�s����X��.
  * @�Ѽ�  DAC_Channel: ��w�� DAC �q�D. 
  *          �o�ӰѼƥi�H�O�U�C�Ȥ��@:
  *          DAC_Channel_1: ��w DAC �q�D1 
  *          DAC_Channel_2: ��w DAC �q�D2 
  * @��^  ��w�� DAC �ƾڿ�X��.
  */
uint16_t DAC_GetDataOutputValue(uint32_t DAC_Channel)
{
  __IO uint32_t tmp = 0;
  
  /* �ˬd�Ѽ� */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  
  tmp = (uint32_t) DAC_BASE ;
  tmp += DOR_Offset + ((uint32_t)DAC_Channel >> 2);
  
  /* ��^��w�� DAC �ƾڱH�s����X�� */
  return (uint16_t) (*(__IO uint32_t*) tmp);
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
