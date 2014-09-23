/**
  ******************************************************************************
  * @���    stm32f10x_adc.c
  * @�@��    MCD ���ε{�ǲ�
  * @����    V3.1.0
  * @���    06/19/2009
  * @²�z    �o�Ӥ�� ���ѩҦ� ADC �T����.
  * @½Ķ    ANSON/sweet1985 Email:airanson110@126.com
  * @���    17/07/2009
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
#include "stm32f10x_adc.h"
#include "stm32f10x_rcc.h"

/* �ۥ����� --------------------------------------------------------------*/
/* �ۥΩw�q --------------------------------------------------------------*/

/* ADC DISCNUM mask */
#define CR1_DISCNUM_Reset           ((uint32_t)0xFFFF1FFF)

/* ADC DISCEN mask */
#define CR1_DISCEN_Set              ((uint32_t)0x00000800)
#define CR1_DISCEN_Reset            ((uint32_t)0xFFFFF7FF)

/* ADC JAUTO mask */
#define CR1_JAUTO_Set               ((uint32_t)0x00000400)
#define CR1_JAUTO_Reset             ((uint32_t)0xFFFFFBFF)

/* ADC JDISCEN mask */
#define CR1_JDISCEN_Set             ((uint32_t)0x00001000)
#define CR1_JDISCEN_Reset           ((uint32_t)0xFFFFEFFF)

/* ADC AWDCH mask */
#define CR1_AWDCH_Reset             ((uint32_t)0xFFFFFFE0)

/* ADC Analog watchdog enable mode mask */
#define CR1_AWDMode_Reset           ((uint32_t)0xFF3FFDFF)

/* CR1 register Mask */
#define CR1_CLEAR_Mask              ((uint32_t)0xFFF0FEFF)

/* ADC ADON mask */
#define CR2_ADON_Set                ((uint32_t)0x00000001)
#define CR2_ADON_Reset              ((uint32_t)0xFFFFFFFE)

/* ADC DMA mask */
#define CR2_DMA_Set                 ((uint32_t)0x00000100)
#define CR2_DMA_Reset               ((uint32_t)0xFFFFFEFF)

/* ADC RSTCAL mask */
#define CR2_RSTCAL_Set              ((uint32_t)0x00000008)

/* ADC CAL mask */
#define CR2_CAL_Set                 ((uint32_t)0x00000004)

/* ADC SWSTART mask */
#define CR2_SWSTART_Set             ((uint32_t)0x00400000)

/* ADC EXTTRIG mask */
#define CR2_EXTTRIG_Set             ((uint32_t)0x00100000)
#define CR2_EXTTRIG_Reset           ((uint32_t)0xFFEFFFFF)

/* ADC Software start mask */
#define CR2_EXTTRIG_SWSTART_Set     ((uint32_t)0x00500000)
#define CR2_EXTTRIG_SWSTART_Reset   ((uint32_t)0xFFAFFFFF)

/* ADC JEXTSEL mask */
#define CR2_JEXTSEL_Reset           ((uint32_t)0xFFFF8FFF)

/* ADC JEXTTRIG mask */
#define CR2_JEXTTRIG_Set            ((uint32_t)0x00008000)
#define CR2_JEXTTRIG_Reset          ((uint32_t)0xFFFF7FFF)

/* ADC JSWSTART mask */
#define CR2_JSWSTART_Set            ((uint32_t)0x00200000)

/* ADC injected software start mask */
#define CR2_JEXTTRIG_JSWSTART_Set   ((uint32_t)0x00208000)
#define CR2_JEXTTRIG_JSWSTART_Reset ((uint32_t)0xFFDF7FFF)

/* ADC TSPD mask */
#define CR2_TSVREFE_Set             ((uint32_t)0x00800000)
#define CR2_TSVREFE_Reset           ((uint32_t)0xFF7FFFFF)

/* CR2 register Mask */
#define CR2_CLEAR_Mask              ((uint32_t)0xFFF1F7FD)

/* ADC SQx mask */
#define SQR3_SQ_Set                 ((uint32_t)0x0000001F)
#define SQR2_SQ_Set                 ((uint32_t)0x0000001F)
#define SQR1_SQ_Set                 ((uint32_t)0x0000001F)

/* SQR1 register Mask */
#define SQR1_CLEAR_Mask             ((uint32_t)0xFF0FFFFF)

/* ADC JSQx mask */
#define JSQR_JSQ_Set                ((uint32_t)0x0000001F)

/* ADC JL mask */
#define JSQR_JL_Set                 ((uint32_t)0x00300000)
#define JSQR_JL_Reset               ((uint32_t)0xFFCFFFFF)

/* ADC SMPx mask */
#define SMPR1_SMP_Set               ((uint32_t)0x00000007)
#define SMPR2_SMP_Set               ((uint32_t)0x00000007)

/* ADC JDRx registers offset */
#define JDR_Offset                  ((uint8_t)0x28)

/* ADC1 DR register base address */
#define DR_ADDRESS                  ((uint32_t)0x4001244C)

/* �ۥΧ� -------------------------------------------------------------*/
/* �ۥ��ܶq -----------------------------------------------------------*/
/* �ۥΨ�ƭ쫬 -------------------------------------------------------*/
/* �ۥΨ�� -----------------------------------------------------------*/

/**
  * @²�z  �N�~�] ADCx �������H�s�����]���ʬ٭�.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @��^  �S��
  */
void ADC_DeInit(ADC_TypeDef* ADCx)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  
  if (ADCx == ADC1)
  {
    /* �ϯ� ADC1 �_�쪬�A */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);
    /* �q�_�쪬�A���� ADC1  */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);
  }
  else if (ADCx == ADC2)
  {
    /* �ϯ� ADC2 �_�쪬�A */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2, ENABLE);
    /* �q�_�쪬�A���� ADC2 */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2, DISABLE);
  }
  else
  {
    if (ADCx == ADC3)
    {
      /* �ϯ� ADC3 �_�쪬�A */
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3, ENABLE);
      /* �q�_�쪬�A���� ADC3 */
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3, DISABLE);
    }
  }
}

/**
  * @²�z  �ھ� ADC_InitStruct �����w���Ѽƪ�l�ƥ~�] ADCx ���H�s��.
  * @�Ѽ�  ADCx: �䤤x �i�H�O1 2��3�A�Ψӿ��ADC �~��Ҷ�.
  * @�Ѽ�  ADC_InitStruct: ���V���c�� ADC_InitTypeDef �����w,�ӵ��c�]�A�F���wADC�~��Ҷ����t�m�H��.
  * @��^  �S��
  */
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct)
{
  uint32_t tmpreg1 = 0;
  uint8_t tmpreg2 = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_MODE(ADC_InitStruct->ADC_Mode));
  assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_ScanConvMode));
  assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_ContinuousConvMode));
  assert_param(IS_ADC_EXT_TRIG(ADC_InitStruct->ADC_ExternalTrigConv));   
  assert_param(IS_ADC_DATA_ALIGN(ADC_InitStruct->ADC_DataAlign)); 
  assert_param(IS_ADC_REGULAR_LENGTH(ADC_InitStruct->ADC_NbrOfChannel));

  /*---------------------------- ADCx CR1 Configuration -----------------*/
  /* �o�� ADCx CR1 ���� */
  tmpreg1 = ADCx->CR1;
  /* �M�� DUALMOD �M SCAN �� */
  tmpreg1 &= CR1_CLEAR_Mask;
  /* �t�m ADCx: �����Ҧ��M�����ഫ�Ҧ� */
  /* �]�m DUALMOD ��A ���� ADC_Mode ���� */
  /* �]�m SCAN ��A���� ADC_ScanConvMode ���� */
  tmpreg1 |= (uint32_t)(ADC_InitStruct->ADC_Mode | ((uint32_t)ADC_InitStruct->ADC_ScanConvMode << 8));
  /* �g ADCx CR1 */
  ADCx->CR1 = tmpreg1;

  /*---------------------------- ADCx CR2 Configuration -----------------*/
  /* �o�� ADCx CR2 ���� */
  tmpreg1 = ADCx->CR2;
  /* �M�� CONT, ALIGN �M EXTSEL �� */
  tmpreg1 &= CR2_CLEAR_Mask;
  /* �t�m ADCx: �~Ĳ�o�ƥ�M�s���ഫ�Ҧ� */
  /* �]�m ALIGN ��A���� ADC_DataAlign ���� */
  /* �]�m EXTSEL ��A���� ADC_ExternalTrigConv ���� */
  /* �]�m CONT ��A���� ADC_ContinuousConvMode ���� */
  tmpreg1 |= (uint32_t)(ADC_InitStruct->ADC_DataAlign | ADC_InitStruct->ADC_ExternalTrigConv |
            ((uint32_t)ADC_InitStruct->ADC_ContinuousConvMode << 1));
  /* �g ADCx CR2 */
  ADCx->CR2 = tmpreg1;

  /*---------------------------- ADCx SQR1 Configuration -----------------*/
  /* �o�� ADCx SQR1 ���� */
  tmpreg1 = ADCx->SQR1;
  /* �M�� L �� */
  tmpreg1 &= SQR1_CLEAR_Mask;
  /* �t�m ADCx: �W�h�H�D���� */
  /* �]�m L ��A���� ADC_NbrOfChannel ���� */
  tmpreg2 |= (uint8_t) (ADC_InitStruct->ADC_NbrOfChannel - (uint8_t)1);
  tmpreg1 |= (uint32_t)tmpreg2 << 20;
  /* �g ADCx SQR1 */
  ADCx->SQR1 = tmpreg1;
}

/**
  * @²�z  �� ADC_InitStruct �����C�@�ӰѼƫ��ʬ٭ȶ�J.
  * @�Ѽ�  ADC_InitStruct : ���V���c�� ADC_InitTypeDef �����w�A�ΨӪ�l��.
  * @��^  �S��
  */
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)
{
  /* �_�� ADC ��l���c�ܶq */
  /* ��l�� ADC_Mode ���� */
  ADC_InitStruct->ADC_Mode = ADC_Mode_Independent;
  /* ��l�� ADC_ScanConvMode ���� */
  ADC_InitStruct->ADC_ScanConvMode = DISABLE;
  /* ��l�� ADC_ContinuousConvMode ���� */
  ADC_InitStruct->ADC_ContinuousConvMode = DISABLE;
  /* ��l�� ADC_ExternalTrigConv ���� */
  ADC_InitStruct->ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  /* ��l�� ADC_DataAlign ���� */
  ADC_InitStruct->ADC_DataAlign = ADC_DataAlign_Right;
  /* ��l�� ADC_NbrOfChannel ���� */
  ADC_InitStruct->ADC_NbrOfChannel = 1;
}

/**
  * @²�z  �ϯ�Ϊ̥�����w�� ADC .
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @�Ѽ�  NewState: ADCx �]�ƪ��s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �]�m ADON ��A�q�ٹq�Ҧ��U���ADC */
    ADCx->CR2 |= CR2_ADON_Set;
  }
  else
  {
    /* ������w�� ADC �]�� */
    ADCx->CR2 &= CR2_ADON_Reset;
  }
}

/**
  * @²�z  �ϯ�Υ�����w�� ADC DMA �ШD.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  *        ����: ADC2 �S�� DMA ��O.
  * @�Ѽ�  NewState: ��w�� ADC DMA �ಾ�����s���A.
  *        �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_DMA_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �ϯ��w�� ADC DMA �ШD */
    ADCx->CR2 |= CR2_DMA_Set;
  }
  else
  {
    /* �����w�� ADC DMA �ШD */
    ADCx->CR2 &= CR2_DMA_Reset;
  }
}

/**
  * @²�z  �ϯ�Ϊ̥�����w��ADC�����_.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @�Ѽ�  ADC_IT: ���w�� ADC ���_��. 
  *          �i�H�ϥΤU�z�Ȫ��@�өΪ̴X�ӭȪ��զX:
  *          ADC_IT_EOC:  ���⵲�����_�̽�
  *          ADC_IT_AWD:  �����ݪ������_�̽�
  *          ADC_IT_JEOC: �`�J�q�D�������_�̽�
  * @�Ѽ�  NewState: ���w�� ADC ���_���s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void ADC_ITConfig(ADC_TypeDef* ADCx, uint16_t ADC_IT, FunctionalState NewState)
{
  uint8_t itmask = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_ADC_IT(ADC_IT));
  /* �o�� ADC IT ���_�� */
  itmask = (uint8_t)ADC_IT;
  if (NewState != DISABLE)
  {
    /* �ϯ��w�� ADC ���_ */
    ADCx->CR1 |= itmask;
  }
  else
  {
    /* ������w�� ADC ���_ */
    ADCx->CR1 &= (~(uint32_t)itmask);
  }
}

/**
  * @²�z  ���m���w��ADC���շǱH�s��.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @��^  �S��
  */
void ADC_ResetCalibration(ADC_TypeDef* ADCx)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* ���m���w��ADC���շǱH�s�� */  
  ADCx->CR2 |= CR2_RSTCAL_Set;
}

/**
  * @²�z  ���ADC���m�շǱH�s�������A.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @��^  ADC���m�շǱH�s�����s���A (SET �� RESET).
  */
FlagStatus ADC_GetResetCalibrationStatus(ADC_TypeDef* ADCx)
{
  FlagStatus bitstatus = RESET;
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* �ˬd RSTCAL �쪺���A */
  if ((ADCx->CR2 & CR2_RSTCAL_Set) != (uint32_t)RESET)
  {
    /* �]�m RSTCAL �� */
    bitstatus = SET;
  }
  else
  {
    /* �_�� RSTCAL �� */
    bitstatus = RESET;
  }
  /* ��^ RSTCAL �쪺���A */
  return  bitstatus;
}

/**
  * @²�z  �}�l���wADC���շǪ��A.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @��^  �S��
  */
void ADC_StartCalibration(ADC_TypeDef* ADCx)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* �ϯ��w�� ADC �շǳB�z */  
  ADCx->CR2 |= CR2_CAL_Set;
}

/**
  * @²�z  ������wADC���շǪ��A.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @��^  ���wADC���շǪ��s���A (SET �� RESET).
  */
FlagStatus ADC_GetCalibrationStatus(ADC_TypeDef* ADCx)
{
  FlagStatus bitstatus = RESET;
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* �ˬd CAL �쪺���A */
  if ((ADCx->CR2 & CR2_CAL_Set) != (uint32_t)RESET)
  {
    /* �]�m CAL ��: ���Ƕi�椤 */
    bitstatus = SET;
  }
  else
  {
    /* �_�� CAL ��: �շǵ��� */
    bitstatus = RESET;
  }
  /* ��^ CAL �쪺���A */
  return  bitstatus;
}

/**
  * @²�z  �ϯ�Ϊ̥�����w��ADC���n���ഫ�Ұʥ\��.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @�Ѽ�  NewState: �襤���ѳn��o�X�}�l�H����ADC���s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void ADC_SoftwareStartConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* ���\��ܪ�ADC�ഫ�~���ƥ�M�Ұʿ�ܪ�ADC�ഫ */
    ADCx->CR2 |= CR2_EXTTRIG_SWSTART_Set;
  }
  else
  {
    /* �T���ܪ�ADC�ഫ�~���ƥ�M�����ܪ�ADC�ഫ */
    ADCx->CR2 &= CR2_EXTTRIG_SWSTART_Reset;
  }
}

/**
  * @²�z  ���ADC�n���ഫ�Ұʪ��A.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @��^  ADC�n��}�l�ഫ���s���A (SET �� RESET).
  */
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef* ADCx)
{
  FlagStatus bitstatus = RESET;
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* �ˬd SWSTART �쪺�s���A */
  if ((ADCx->CR2 & CR2_SWSTART_Set) != (uint32_t)RESET)
  {
    /* �]�m SWSTART �� */
    bitstatus = SET;
  }
  else
  {
    /* �_�� SWSTART �� */
    bitstatus = RESET;
  }
  /* ��^ SWSTART �쪺���A */
  return  bitstatus;
}

/**
  * @²�z  ��ADC�W�h�ճq�D�t�m���_�Ҧ�.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @�Ѽ�  Number: �Ҧ��U�`�W�H�D�p�ƭȡA�ӭȽd��1��8. 
  * @��^  �S��
  */
void ADC_DiscModeChannelCountConfig(ADC_TypeDef* ADCx, uint8_t Number)
{
  uint32_t tmpreg1 = 0;
  uint32_t tmpreg2 = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_REGULAR_DISC_NUMBER(Number));
  /* �o��L�h���H�s���� */
  tmpreg1 = ADCx->CR1;
  /* �M���L�h�������_�Ҧ��q�D�p�ƾ� */
  tmpreg1 &= CR1_DISCNUM_Reset;
  /* �]�m���_�Ҧ��q�D�p�ƾ� */
  tmpreg2 = Number - 1;
  tmpreg1 |= tmpreg2 << 13;
  /* �s�x�H�s�����s�� */
  ADCx->CR1 = tmpreg1;
}

/**
  * @²�z  �ϯ�Ϊ̥�����w��ADC�W�h�ճq�D�����_�Ҧ�.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @�Ѽ�  NewState: ���w��ADC�W�h�ճq�D�����_�Ҧ����s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void ADC_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �ϯ���w��ADC�W�h�ճq�D�����_�Ҧ� */
    ADCx->CR1 |= CR1_DISCEN_Set;
  }
  else
  {
    /* ������w��ADC�W�h�ճq�D�����_�Ҧ� */
    ADCx->CR1 &= CR1_DISCEN_Reset;
  }
}

/**
  * @²�z  �]�m���wADC���W�h�ճq�D�A�]�m���̪���ƶ��ǩM�ļˮɶ�.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @�Ѽ�  ADC_Channel: �t�m ADC �q�D. 
  *          �o�ӰѼƥi�H�ϥΤU�z�Ȫ��@��:
  *          ADC_Channel_0:  ���ADC�q�D0  
  *          ADC_Channel_1:  ���ADC�q�D1  
  *          ADC_Channel_2:  ���ADC�q�D2  
  *          ADC_Channel_3:  ���ADC�q�D3  
  *          ADC_Channel_4:  ���ADC�q�D4  
  *          ADC_Channel_5:  ���ADC�q�D5  
  *          ADC_Channel_6:  ���ADC�q�D6  
  *          ADC_Channel_7:  ���ADC�q�D7  
  *          ADC_Channel_8:  ���ADC�q�D8  
  *          ADC_Channel_9:  ���ADC�q�D9  
  *          ADC_Channel_10: ���ADC�q�D10  
  *          ADC_Channel_11: ���ADC�q�D11  
  *          ADC_Channel_12: ���ADC�q�D12  
  *          ADC_Channel_13: ���ADC�q�D13  
  *          ADC_Channel_14: ���ADC�q�D14  
  *          ADC_Channel_15: ���ADC�q�D15  
  *          ADC_Channel_16: ���ADC�q�D16  
  *          ADC_Channel_17: ���ADC�q�D17  
  * @�Ѽ�  Rank: �W�h�ձļ˶���. ���Ƚd��1��16.
  * @�Ѽ�  ADC_SampleTime: ���wADC�q�D���ļˮɶ���. 
  *          �o�ӰѼƥi�H�ϥΤU�z�Ȫ��@��:
  *          ADC_SampleTime_1Cycles5:   �ļˮɶ����� 1.5   �g��
  *          ADC_SampleTime_7Cycles5:   �ļˮɶ����� 7.5   �g��
  *          ADC_SampleTime_13Cycles5:  �ļˮɶ����� 13.5  �g��
  *          ADC_SampleTime_28Cycles5:  �ļˮɶ����� 28.5  �g��	
  *          ADC_SampleTime_41Cycles5:  �ļˮɶ����� 41.5  �g��	
  *          ADC_SampleTime_55Cycles5:  �ļˮɶ����� 55.5  �g��	
  *          ADC_SampleTime_71Cycles5:  �ļˮɶ����� 71.5  �g��	
  *          ADC_SampleTime_239Cycles5: �ļˮɶ����� 239.5 �g��	
  * @��^  �S��
  */
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
{
  uint32_t tmpreg1 = 0, tmpreg2 = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  assert_param(IS_ADC_REGULAR_RANK(Rank));
  assert_param(IS_ADC_SAMPLE_TIME(ADC_SampleTime));
  /* �p�G��w ADC_Channel_10 ... ADC_Channel_17 */
  if (ADC_Channel > ADC_Channel_9)
  {
    /* �o���ª��H�s������ */
    tmpreg1 = ADCx->SMPR1;
    /* �p��ݭn�M�����лx */
    tmpreg2 = SMPR1_SMP_Set << (3 * (ADC_Channel - 10));
    /* �M���ª��q�D�ļˮɶ� */
    tmpreg1 &= ~tmpreg2;
    /* �p��ݭn�m�쪺�лx */
    tmpreg2 = (uint32_t)ADC_SampleTime << (3 * (ADC_Channel - 10));
    /* �]�m�s���q�D�ļˮɶ� */
    tmpreg1 |= tmpreg2;
    /* �s�x�s���H�s������ */
    ADCx->SMPR1 = tmpreg1;
  }
  else /* ADC_Channel include in ADC_Channel_[0..9] */
  {
    /* �o���ª��H�s������ */
    tmpreg1 = ADCx->SMPR2;
    /* �p��ݭn�M�����лx */
    tmpreg2 = SMPR2_SMP_Set << (3 * ADC_Channel);
    /* �M���ª��q�D�ļˮɶ� */
    tmpreg1 &= ~tmpreg2;
    /* �p��ݭn�m�쪺�лx */
    tmpreg2 = (uint32_t)ADC_SampleTime << (3 * ADC_Channel);
    /* �]�m�s���q�D�ļˮɶ� */
    tmpreg1 |= tmpreg2;
    /* �s�x�s���H�s������ */
    ADCx->SMPR2 = tmpreg1;
  }
  /* For Rank 1 to 6 */
  if (Rank < 7)
  {
    /* �o���ª��H�s������ */
    tmpreg1 = ADCx->SQR3;
    /* �p��ݭn�M�����лx */
    tmpreg2 = SQR3_SQ_Set << (5 * (Rank - 1));
    /* �ھڿ�ܪ��ǦC�M���ª� SQx �� */
    tmpreg1 &= ~tmpreg2;
    /* �p��ݭn�m�쪺�лx */
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 1));
    /* �ھڿ�ܪ��ǦC�]�m�s�� SQx �� */
    tmpreg1 |= tmpreg2;
    /* �s�x�s���H�s������ */
    ADCx->SQR3 = tmpreg1;
  }
  /* For Rank 7 to 12 */
  else if (Rank < 13)
  {
    /* �o���ª��H�s������ */
    tmpreg1 = ADCx->SQR2;
    /* �p��ݭn�M�����лx */
    tmpreg2 = SQR2_SQ_Set << (5 * (Rank - 7));
    /* �ھڿ�ܪ��ǦC�M���ª� SQx �� */
    tmpreg1 &= ~tmpreg2;
    /* �p��ݭn�m�쪺�лx */
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 7));
    /* �ھڿ�ܪ��ǦC�]�m�s�� SQx �� */
    tmpreg1 |= tmpreg2;
    /* �s�x�s���H�s������ */
    ADCx->SQR2 = tmpreg1;
  }
  /* For Rank 13 to 16 */
  else
  {
    /* �o���ª��H�s������ */
    tmpreg1 = ADCx->SQR1;
    /* �p��ݭn�M�����лx */
    tmpreg2 = SQR1_SQ_Set << (5 * (Rank - 13));
    /* �ھڿ�ܪ��ǦC�M���ª� SQx �� */
    tmpreg1 &= ~tmpreg2;
    /* �p��ݭn�m�쪺�лx */
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 13));
    /* �ھڿ�ܪ��ǦC�]�m�s�� SQx �� */
    tmpreg1 |= tmpreg2;
    /* �s�x�s���H�s������ */
    ADCx->SQR1 = tmpreg1;
  }
}

/**
  * @²�z  �ϯ�Ϊ̥��� ADCx ���g�~��Ĳ�o�Ұ��ഫ�\��.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @�Ѽ�  NewState: ��w�� ADCx ���g�~��Ĳ�o�Ұ��ഫ�\�઺�s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void ADC_ExternalTrigConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �ϯ� ADCx ���g�~��Ĳ�o�Ұ��ഫ�\�� */
    ADCx->CR2 |= CR2_EXTTRIG_Set;
  }
  else
  {
    /* ���� ADCx ���g�~��Ĳ�o�Ұ��ഫ�\�� */
    ADCx->CR2 &= CR2_EXTTRIG_Reset;
  }
}

/**
  * @²�z  ��^�̪�@�� ADCx �W�h�ժ��ഫ���G.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @��^  �ഫ���G.
  */
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* ��^�̪�@�� ADCx �W�h�ժ��ഫ���G */
  return (uint16_t) ADCx->DR;
}

/**
  * @²�z  ��^�̪�@���� ADC �Ҧ��U�� ADC1 �M ADC2 �ഫ���G.
  * @retval �ഫ���G.
  */
uint32_t ADC_GetDualModeConversionValue(void)
{
  /* ��^���ഫ�U���ഫ���G */
  return (*(__IO uint32_t *) DR_ADDRESS);
}

/**
  * @²�z  �ϯ�Ϊ̥�����w ADC �b�W�h����ƫ�۰ʶ}�l�`�J���ഫ.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @�Ѽ�  NewState: �襤���i��۰ʪ`�J�ഫ��ADC�s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void ADC_AutoInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �ϯ���w ADC �b�W�h����ƫ�۰ʶ}�l�`�J���ഫ */
    ADCx->CR1 |= CR1_JAUTO_Set;
  }
  else
  {
    /* ������w ADC �b�W�h����ƫ�۰ʶ}�l�`�J���ഫ */
    ADCx->CR1 &= CR1_JAUTO_Reset;
  }
}

/**
  * @²�z  �ϯ�Ϊ̥�����w ADC ���`�J�ն��_�Ҧ�
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @�Ѽ�  NewState: ADC �`�J�ճq�D�W���_�Ҧ����s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void ADC_InjectedDiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* ������w ADC ���`�J�ն��_�Ҧ� */
    ADCx->CR1 |= CR1_JDISCEN_Set;
  }
  else
  {
    /* ������w ADC ���`�J�ն��_�Ҧ� */
    ADCx->CR1 &= CR1_JDISCEN_Reset;
  }
}

/**
  * @²�z  �t�m ADCx ���~��Ĳ�o�Ұʪ`�J���ഫ�\��.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @�Ѽ�  ADC_ExternalTrigInjecConv: �}�l�`�J�ഫ��ADCĲ�o��. 
  *          �o�ӰѼƥi�H���U�C�Ȥ��@:
  *          ADC_ExternalTrigInjecConv_T1_TRGO: ��ܩw�ɾ�1��TRGO�@���`�J�ഫ�~��Ĳ�o (for ADC1, ADC2 and ADC3)
  *          ADC_ExternalTrigInjecConv_T1_CC4:  ��ܩw�ɾ�1��������4�@���`�J�ഫ�~��Ĳ�o (for ADC1, ADC2 and ADC3)
  *          ADC_ExternalTrigInjecConv_T2_TRGO: ��ܩw�ɾ�2�� TRGO �@���`�J�ഫ�~��Ĳ�o (for ADC1 and ADC2)
  *          ADC_ExternalTrigInjecConv_T2_CC1:  ��ܩw�ɾ�2��������1�@���`�J�ഫ�~��Ĳ�o (for ADC1 and ADC2)
  *          ADC_ExternalTrigInjecConv_T3_CC4:  ��ܩw�ɾ�3��������4�@���`�J�ഫ�~��Ĳ�o (for ADC1 and ADC2)
  *          ADC_ExternalTrigInjecConv_T4_TRGO: ��ܩw�ɾ�4��TRGO�@���`�J�ഫ�~��Ĳ�o (for ADC1 and ADC2)
  *          ADC_ExternalTrigInjecConv_Ext_IT15_TIM8_CC4: �~�����_15�Ϊ�timer8����ƥ�@���`�J�ഫ���~��Ĳ�o�� (for ADC1 and ADC2)                       
  *          ADC_ExternalTrigInjecConv_T4_CC3:  ��ܩw�ɾ�4������3 (for ADC3 only)
  *          ADC_ExternalTrigInjecConv_T8_CC2:  ��ܩw�ɾ�8������2 (for ADC3 only)                         
  *          ADC_ExternalTrigInjecConv_T8_CC4:  ��ܩw�ɾ�8������4 (for ADC3 only)
  *          ADC_ExternalTrigInjecConv_T5_TRGO: ��ܩw�ɾ�5Ĳ�o�ƥ� (for ADC3 only)                         
  *          ADC_ExternalTrigInjecConv_T5_CC4:  ��ܩw�ɾ�5������4 (for ADC3 only)                        
  *          ADC_ExternalTrigInjecConv_None:    �`�J�ഫ�ѳn��ҰʡA�Ӥ��O�ѥ~��Ĳ�o���Ұ� (for ADC1, ADC2 and ADC3)
  * @��^  �S��
  */
void ADC_ExternalTrigInjectedConvConfig(ADC_TypeDef* ADCx, uint32_t ADC_ExternalTrigInjecConv)
{
  uint32_t tmpreg = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_EXT_INJEC_TRIG(ADC_ExternalTrigInjecConv));
  /* �o���ª��H�s������ */
  tmpreg = ADCx->CR2;
  /* �M����ܪ��`�J�q�D�s���~��Ĳ�o�ƥ� */
  tmpreg &= CR2_JEXTSEL_Reset;
  /* �]�m��ܪ��`�J�q�D�s���~��Ĳ�o�ƥ� */
  tmpreg |= ADC_ExternalTrigInjecConv;
  /* �s�x�s���H�s������ */
  ADCx->CR2 = tmpreg;
}

/**
  * @²�z  �ϯ�Ϊ̥��� ADCx ���g�~��Ĳ�o�Ұʪ`�J���ഫ�\��.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @�Ѽ�  NewState: ���wADC�~��Ĳ�o�Ұʪ`�J�ഫ���s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void ADC_ExternalTrigInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �ϯ� ADCx ���g�~��Ĳ�o�Ұʪ`�J���ഫ�\�� */
    ADCx->CR2 |= CR2_JEXTTRIG_Set;
  }
  else
  {
    /* ���� ADCx ���g�~��Ĳ�o�Ұʪ`�J���ഫ�\�� */
    ADCx->CR2 &= CR2_JEXTTRIG_Reset;
  }
}

/**
  * @²�z  �ϯ�Ϊ̥��� ADCx �n��Ұʪ`�J���ഫ�\��.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @�Ѽ�  NewState: ���w ADC �n��Ĳ�o�Ұʪ`�J�ഫ���s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void ADC_SoftwareStartInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �ϯ� ADCx �n��Ұʪ`�J���ഫ�\��åB�Ұʪ`�J��� */
    ADCx->CR2 |= CR2_JEXTTRIG_JSWSTART_Set;
  }
  else
  {
    /* ���� ADCx �n��Ұʪ`�J���ഫ�\��åB�Ұʪ`�J��� */
    ADCx->CR2 &= CR2_JEXTTRIG_JSWSTART_Reset;
  }
}

/**
  * @²�z  ������w ADC ���n��Ұʪ`�J���ഫ���A.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @��^  ���w�� ADC �n��Ĳ�o�Ұʪ`�J�ഫ���s���A (SET �� RESET).
  */
FlagStatus ADC_GetSoftwareStartInjectedConvCmdStatus(ADC_TypeDef* ADCx)
{
  FlagStatus bitstatus = RESET;
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* �ˬd JSWSTART �쪺���A */
  if ((ADCx->CR2 & CR2_JSWSTART_Set) != (uint32_t)RESET)
  {
    /* �]�m JSWSTART �� */
    bitstatus = SET;
  }
  else
  {
    /* �_�� JSWSTART �� */
    bitstatus = RESET;
  }
  /* ��^ JSWSTART �쪺���A */
  return  bitstatus;
}

/**
  * @²�z  �]�m���w ADC ���`�J�ճq�D�A�]�m���̪���ƶ��ǩM�ļˮɶ�.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @�Ѽ�  ADC_Channel: �Q�]�m��ADC�q�D. 
  *          �o�ӰѼƥi�H���U�C�Ȥ��@:
  *          ADC_Channel_0:  ���ADC�q�D0  
  *          ADC_Channel_1:  ���ADC�q�D1  
  *          ADC_Channel_2:  ���ADC�q�D2  
  *          ADC_Channel_3:  ���ADC�q�D3  
  *          ADC_Channel_4:  ���ADC�q�D4  
  *          ADC_Channel_5:  ���ADC�q�D5  
  *          ADC_Channel_6:  ���ADC�q�D6  
  *          ADC_Channel_7:  ���ADC�q�D7  
  *          ADC_Channel_8:  ���ADC�q�D8  
  *          ADC_Channel_9:  ���ADC�q�D9  
  *          ADC_Channel_10: ���ADC�q�D10  
  *          ADC_Channel_11: ���ADC�q�D11  
  *          ADC_Channel_12: ���ADC�q�D12  
  *          ADC_Channel_13: ���ADC�q�D13  
  *          ADC_Channel_14: ���ADC�q�D14  
  *          ADC_Channel_15: ���ADC�q�D15  
  *          ADC_Channel_16: ���ADC�q�D16  
  *          ADC_Channel_17: ���ADC�q�D17 
  * @�Ѽ�  Rank: �W�h�ձļ˶���.���Ƚd��1��4.
  * @�Ѽ�  ADC_SampleTime: ���wADC�q�D���ļˮɶ���. 
  *          �o�ӰѼƥi�H�ϥΤU�z�Ȫ��@��:
  *          ADC_SampleTime_1Cycles5:   �ļˮɶ����� 1.5   �g��
  *          ADC_SampleTime_7Cycles5:   �ļˮɶ����� 7.5   �g��
  *          ADC_SampleTime_13Cycles5:  �ļˮɶ����� 13.5  �g��
  *          ADC_SampleTime_28Cycles5:  �ļˮɶ����� 28.5  �g��	
  *          ADC_SampleTime_41Cycles5:  �ļˮɶ����� 41.5  �g��	
  *          ADC_SampleTime_55Cycles5:  �ļˮɶ����� 55.5  �g��	
  *          ADC_SampleTime_71Cycles5:  �ļˮɶ����� 71.5  �g��	
  *          ADC_SampleTime_239Cycles5: �ļˮɶ����� 239.5 �g��		
  * @��^  �S��
  */
void ADC_InjectedChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
{
  uint32_t tmpreg1 = 0, tmpreg2 = 0, tmpreg3 = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  assert_param(IS_ADC_INJECTED_RANK(Rank));
  assert_param(IS_ADC_SAMPLE_TIME(ADC_SampleTime));
  /* �p�G��� ADC_Channel_10 ... ADC_Channel_17 */
  if (ADC_Channel > ADC_Channel_9)
  {
    /* �o���ª��H�s������ */
    tmpreg1 = ADCx->SMPR1;
    /* �p��ݭn�M�����лx */
    tmpreg2 = SMPR1_SMP_Set << (3*(ADC_Channel - 10));
    /* �M���ª��q�D�ļˮɶ� */
    tmpreg1 &= ~tmpreg2;
    /* �p��ݭn�m�쪺�лx */
    tmpreg2 = (uint32_t)ADC_SampleTime << (3*(ADC_Channel - 10));
    /* �]�m�s���q�D�ļˮɶ� */
    tmpreg1 |= tmpreg2;
    /* �s�x�s���H�s������ */
    ADCx->SMPR1 = tmpreg1;
  }
  else /* ADC_Channel include in ADC_Channel_[0..9] */
  {
    /* �o���ª��H�s������ */
    tmpreg1 = ADCx->SMPR2;
    /* �p��ݭn�M�����лx */
    tmpreg2 = SMPR2_SMP_Set << (3 * ADC_Channel);
    /* �M���ª��q�D�ļˮɶ� */
    tmpreg1 &= ~tmpreg2;
    /* �p��ݭn�m�쪺�лx */
    tmpreg2 = (uint32_t)ADC_SampleTime << (3 * ADC_Channel);
    /* �]�m�s���q�D�ļˮɶ� */
    tmpreg1 |= tmpreg2;
    /* �s�x�s���H�s������ */
    ADCx->SMPR2 = tmpreg1;
  }
  /* �t�m Rank �W�h�ձļ˶��� */
  /* �o���ª��H�s������ */
  tmpreg1 = ADCx->JSQR;
  /* �o�� JL ����: Number = JL+1 */
  tmpreg3 =  (tmpreg1 & JSQR_JL_Set)>> 20;
  /* �p��ݭn�M�����лx: ((Rank-1)+(4-JL-1)) */
  tmpreg2 = JSQR_JSQ_Set << (5 * (uint8_t)((Rank + 3) - (tmpreg3 + 1)));
  /* �M���襤�ǦC JSQx �� */
  tmpreg1 &= ~tmpreg2;
  /* �p��ݭn�m�쪺�лx: ((Rank-1)+(4-JL-1)) */
  tmpreg2 = (uint32_t)ADC_Channel << (5 * (uint8_t)((Rank + 3) - (tmpreg3 + 1)));
  /* �m��襤�ǦC�ª� JSQx �� */
  tmpreg1 |= tmpreg2;
  /* �s�x�s���H�s������ */
  ADCx->JSQR = tmpreg1;
}

/**
  * @²�z  �]�m�`�J�ճq�D���ഫ�ǦC����
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @�Ѽ�  Length: �ഫ�ǦC����. 
  *                �o�ӰѼƥ����O 1 �� 4 ��������.
  * @��^  �S��
  */
void ADC_InjectedSequencerLengthConfig(ADC_TypeDef* ADCx, uint8_t Length)
{
  uint32_t tmpreg1 = 0;
  uint32_t tmpreg2 = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_INJECTED_LENGTH(Length));
  
  /* �o���ª��H�s������ */
  tmpreg1 = ADCx->JSQR;
  /* �M���`�J�H�D���Ǿ������� JL �� */
  tmpreg1 &= JSQR_JL_Reset;
  /* �m��`�J�H�D���Ǿ������� JL �� */
  tmpreg2 = Length - 1; 
  tmpreg1 |= tmpreg2 << 20;
  /* �s�x�s���H�s������ */
  ADCx->JSQR = tmpreg1;
}

/**
  * @²�z  �]�m�`�J�ճq�D���ഫ������
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @�Ѽ�  ADC_InjectedChannel: �ݭn�]�m�����Ȫ�ADC�`�J�H�D. 
  *          �o�ӰѼƥi�H�ϥΤU�z�Ȫ��@��:
  *          ADC_InjectedChannel_1: ��ܪ`�J�q�D1 
  *          ADC_InjectedChannel_2: ��ܪ`�J�q�D2 
  *          ADC_InjectedChannel_3: ��ܪ`�J�q�D3 
  *          ADC_InjectedChannel_4: ��ܪ`�J�q�D4 
  * @�Ѽ�  Offset: �襤��ADC�`�J�H�D�������ȡA�ӰѼƬO�@��12���.
  * @��^  �S��
  */
void ADC_SetInjectedOffset(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel, uint16_t Offset)
{
  __IO uint32_t tmp = 0;
  
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_INJECTED_CHANNEL(ADC_InjectedChannel));
  assert_param(IS_ADC_OFFSET(Offset));  
  
  tmp = (uint32_t)ADCx;
  tmp += ADC_InjectedChannel;
  
  /* �]�m��w���`�J�q�D���ƾڰ����q */
  *(__IO uint32_t *) tmp = (uint32_t)Offset;
}

/**
  * @²�z  ��^ ADC ���w�`�J�q�D���ഫ���G
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @�Ѽ�  ADC_InjectedChannel: ���w�`�J�q�D.
  *          �o�ӰѼƥi�H�ϥΤU�z�Ȫ��@��:
  *          ADC_InjectedChannel_1: ��w�`�J�q�D1 
  *          ADC_InjectedChannel_2: ��w�`�J�q�D2
  *          ADC_InjectedChannel_3: ��w�`�J�q�D3
  *          ADC_InjectedChannel_4: ��w�`�J�q�D4
  * @��^  �ഫ���G.
  */
uint16_t ADC_GetInjectedConversionValue(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel)
{
  __IO uint32_t tmp = 0;
  
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_INJECTED_CHANNEL(ADC_InjectedChannel));

  tmp = (uint32_t)ADCx;
  tmp += ADC_InjectedChannel + JDR_Offset;
  
  /* ��^ ADC ���w�`�J�q�D���ഫ���G */
  return (uint16_t) (*(__IO uint32_t*)  tmp);   
}

/**
  * @²�z  �ϯ�Ϊ̥�����w���/����A�W�h/�`�J�ճq�D�W�������ݪ���
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @�Ѽ�  ADC_AnalogWatchdog: ADC�����ݪ����t�m.
  *          �o�ӰѼƥi�H�ϥΤU�z�Ȫ��@��:
  *          ADC_AnalogWatchdog_SingleRegEnable:        ��ӳW�h�q�D�W�]�m�����ݪ���
  *          ADC_AnalogWatchdog_SingleInjecEnable:      ��Ӫ`�J�q�D�W�]�m�����ݪ���
  *          ADC_AnalogWatchdog_SingleRegOrInjecEnable: ��ӳW�h�q�D�Ϊ̪`�J�q�D�W�]�m�����ݪ���
  *          ADC_AnalogWatchdog_AllRegEnable:           �Ҧ��W�h�q�D�W�]�m�����ݪ���
  *          ADC_AnalogWatchdog_AllInjecEnable:         �Ҧ��`�J�q�D�W�]�m�����ݪ���
  *          ADC_AnalogWatchdog_AllRegAllInjecEnable:   �Ҧ��W�h�q�D�M�Ҧ��`�J�q�D�W�W�]�m�����ݪ���
  *          ADC_AnalogWatchdog_None:                   ���]�m�����ݪ���
  * @��^  �S��	  
  */
void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, uint32_t ADC_AnalogWatchdog)
{
  uint32_t tmpreg = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_ANALOG_WATCHDOG(ADC_AnalogWatchdog));
  /* �o���ª��H�s������ */
  tmpreg = ADCx->CR1;
  /* �M�� AWDEN, AWDENJ �M AWDSGL �� */
  tmpreg &= CR1_AWDMode_Reset;
  /* �]�m�����ݪ������\�Ҧ� */
  tmpreg |= ADC_AnalogWatchdog;
  /* �s�x�s���H�s������ */
  ADCx->CR1 = tmpreg;
}

/**
  * @²�z  �]�m�����ݪ�������/�C�H��.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @�Ѽ�  HighThreshold: �����ݪ��������H��.
  *                       �o�ӰѼƬO�@��12�쪺��.
  * @�Ѽ�  LowThreshold:  �����ݪ������C�H��.
  *                       �o�ӰѼƬO�@��12�쪺��.
  * @��^  �S��
  */
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* ADCx, uint16_t HighThreshold,
                                        uint16_t LowThreshold)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_THRESHOLD(HighThreshold));
  assert_param(IS_ADC_THRESHOLD(LowThreshold));
  /* �]�m�����ݪ��������H�� */
  ADCx->HTR = HighThreshold;
  /* �]�m�����ݪ������C�H�� */
  ADCx->LTR = LowThreshold;
}

/**
  * @²�z  ����ADC�q�D�]�m�����ݪ���
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @�Ѽ�  ADC_Channel: �N�n����t�m�����ݪ������H�D. 
  *          �o�ӰѼƥi�H�ϥΤU�z�Ȫ��@��:
  *          ADC_Channel_0:  ���ADC�q�D0  
  *          ADC_Channel_1:  ���ADC�q�D1  
  *          ADC_Channel_2:  ���ADC�q�D2  
  *          ADC_Channel_3:  ���ADC�q�D3  
  *          ADC_Channel_4:  ���ADC�q�D4  
  *          ADC_Channel_5:  ���ADC�q�D5  
  *          ADC_Channel_6:  ���ADC�q�D6  
  *          ADC_Channel_7:  ���ADC�q�D7  
  *          ADC_Channel_8:  ���ADC�q�D8  
  *          ADC_Channel_9:  ���ADC�q�D9  
  *          ADC_Channel_10: ���ADC�q�D10  
  *          ADC_Channel_11: ���ADC�q�D11  
  *          ADC_Channel_12: ���ADC�q�D12  
  *          ADC_Channel_13: ���ADC�q�D13  
  *          ADC_Channel_14: ���ADC�q�D14  
  *          ADC_Channel_15: ���ADC�q�D15  
  *          ADC_Channel_16: ���ADC�q�D16  
  *          ADC_Channel_17: ���ADC�q�D17 
  * @��^  �S��
  */
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel)
{
  uint32_t tmpreg = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  /* �o���ª��H�s������ */
  tmpreg = ADCx->CR1;
  /* �M�������ݪ����q�D��ܦ� */
  tmpreg &= CR1_AWDCH_Reset;
  /* �]�m�����ݪ����q�D��ܦ� */
  tmpreg |= ADC_Channel;
  /* �s�x�H�s�����s�� */
  ADCx->CR1 = tmpreg;
}

/**
  * @²�z  �ϯ�Ϊ̥���ū׶ǷP���M�����Ѧҹq���q�D.
  * @�Ѽ�  NewState: �ū׶ǷP���M�����Ѧҹq���q�D���s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void ADC_TempSensorVrefintCmd(FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �ϯ�ū׶ǷP���M�����Ѧҹq���q�D */
    ADC1->CR2 |= CR2_TSVREFE_Set;
  }
  else
  {
    /* ����ū׶ǷP���M�����Ѧҹq���q�D */
    ADC1->CR2 &= CR2_TSVREFE_Reset;
  }
}

/**
  * @²�z  �ˬd��w ADC �лx��m1�P�_.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @�Ѽ�  ADC_FLAG: ���w�ݭn�ˬd���лx. 
  *          �o�ӰѼƥi�H�ϥΤU�z�Ȫ��@��:
  *          ADC_FLAG_AWD:   �����ݪ����лx��
  *          ADC_FLAG_EOC:   �ഫ�����лx��
  *          ADC_FLAG_JEOC:  �`�J���ഫ�����лx��
  *          ADC_FLAG_JSTRT: �`�J���ഫ�}�l�лx��
  *          ADC_FLAG_STRT:  �W�h���ഫ�}�l�лx��
  * @��^  ADC_FLAG ���s���A (SET �� RESET).
  */
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint8_t ADC_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_GET_FLAG(ADC_FLAG));
  /* �ˬd���wADC���A�� */
  if ((ADCx->SR & ADC_FLAG) != (uint8_t)RESET)
  {
    /* �]�m ADC_FLAG �� */
    bitstatus = SET;
  }
  else
  {
    /* �_�� ADC_FLAG �� */
    bitstatus = RESET;
  }
  /* ��^ ADC_FLAG �����A */
  return  bitstatus;
}

/**
  * @²�z  �M�� ADCx ���ݳB�z�лx��.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @�Ѽ�  ADC_FLAG: �ݳB�z���лx��. 
  *          �o�ӰѼƥi�H�O�U�C�Ȫ��զX:
  *          ADC_FLAG_AWD:   �����ݪ����лx��
  *          ADC_FLAG_EOC:   �ഫ�����лx��
  *          ADC_FLAG_JEOC:  �`�J���ഫ�����лx��
  *          ADC_FLAG_JSTRT: �`�J���ഫ�}�l�лx��
  *          ADC_FLAG_STRT:  �W�h���ഫ�}�l�лx��
  * @��^  �S��
  */
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint8_t ADC_FLAG)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CLEAR_FLAG(ADC_FLAG));
  /* �M�����w�� ADC �лx */
  ADCx->SR = ~(uint32_t)ADC_FLAG;
}

/**
  * @²�z  �ˬd���w��ADC���_�O�_�o��.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @�Ѽ�  ADC_IT: �ݭn�ˬd��ADC���_��. 
  *          �o�ӰѼƥi�H�ϥΤU�z�Ȫ��@��:
  *          ADC_IT_EOC:  �ഫ�������_�̽�
  *          ADC_IT_AWD:  �����ݪ������_�̽�
  *          ADC_IT_JEOC: �`�J���ഫ�������_�̽�
  * @��^  ADC_IT ���s���A (SET �� RESET).
  */
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint16_t ADC_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t itmask = 0, enablestatus = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_GET_IT(ADC_IT));
  /* �o�� ADC IT ���_�� */
  itmask = ADC_IT >> 8;
  /* �]�m ADC_IT ���\�쪬�A */
  enablestatus = (ADCx->CR1 & (uint8_t)ADC_IT) ;
  /* �ˬd���w�� ADC ���_ */
  if (((ADCx->SR & itmask) != (uint32_t)RESET) && enablestatus)
  {
    /* �]�m ADC_IT */
    bitstatus = SET;
  }
  else
  {
    /* �_�� ADC_IT */
    bitstatus = RESET;
  }
  /* ��^ ADC_IT �����A */
  return  bitstatus;
}

/**
  * @²�z  �M�� ADCx �����_�ݳB�z��.
  * @�Ѽ�  ADCx: �䤤x�i�H�O1�B2��3�A�Ψӿ��ADC�~��Ҷ�.
  * @�Ѽ�  ADC_IT: �a�M���� ADC ���_�ݳB�z��.
  *          �i�H�ϥΤU�z�Ȫ��@�өΪ̴X�ӭȪ��զX:
  *          ADC_IT_EOC:  �ഫ�������_
  *          ADC_IT_AWD:  �����ݪ������_
  *          ADC_IT_JEOC: �`�J���ഫ�������_
  * @��^  �S��
  */
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint16_t ADC_IT)
{
  uint8_t itmask = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_IT(ADC_IT));
  /* �o�� ADC IT ���_�� */
  itmask = (uint8_t)(ADC_IT >> 8);
  /* �M����ܪ�ADC���_���_�� */
  ADCx->SR = ~(uint32_t)itmask;
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
