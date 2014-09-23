/**
  ******************************************************************************
  * @���    stm32f10x_tim.c
  * @�@��    MCD ���ε{�ǲ�
  * @����    V3.1.0
  * @���    06/19/2009
  * @²�z    �o�Ӥ�� ���ѩҦ� TIM �T����.
  * @½Ķ    ANSON/sweet1985 Email:airanson110@126.com
  * @���    10/07/2009
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
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"

/* �ۥ����� --------------------------------------------------------------*/
/* �ۥΩw�q --------------------------------------------------------------*/

/* ---------------------- TIM registers bit mask ------------------------ */
#define CR1_CEN_Set                 ((uint16_t)0x0001)
#define CR1_CEN_Reset               ((uint16_t)0x03FE)
#define CR1_UDIS_Set                ((uint16_t)0x0002)
#define CR1_UDIS_Reset              ((uint16_t)0x03FD)
#define CR1_URS_Set                 ((uint16_t)0x0004)
#define CR1_URS_Reset               ((uint16_t)0x03FB)
#define CR1_OPM_Reset               ((uint16_t)0x03F7)
#define CR1_CounterMode_Mask        ((uint16_t)0x038F)
#define CR1_ARPE_Set                ((uint16_t)0x0080)
#define CR1_ARPE_Reset              ((uint16_t)0x037F)
#define CR1_CKD_Mask                ((uint16_t)0x00FF)
#define CR2_CCPC_Set                ((uint16_t)0x0001)
#define CR2_CCPC_Reset              ((uint16_t)0xFFFE)
#define CR2_CCUS_Set                ((uint16_t)0x0004)
#define CR2_CCUS_Reset              ((uint16_t)0xFFFB)
#define CR2_CCDS_Set                ((uint16_t)0x0008)
#define CR2_CCDS_Reset              ((uint16_t)0xFFF7)
#define CR2_MMS_Mask                ((uint16_t)0xFF8F)
#define CR2_TI1S_Set                ((uint16_t)0x0080)
#define CR2_TI1S_Reset              ((uint16_t)0xFF7F)
#define CR2_OIS1_Reset              ((uint16_t)0x7EFF)
#define CR2_OIS1N_Reset             ((uint16_t)0x7DFF)
#define CR2_OIS2_Reset              ((uint16_t)0x7BFF)
#define CR2_OIS2N_Reset             ((uint16_t)0x77FF)
#define CR2_OIS3_Reset              ((uint16_t)0x6FFF)
#define CR2_OIS3N_Reset             ((uint16_t)0x5FFF)
#define CR2_OIS4_Reset              ((uint16_t)0x3FFF)
#define SMCR_SMS_Mask               ((uint16_t)0xFFF8)
#define SMCR_ETR_Mask               ((uint16_t)0x00FF)
#define SMCR_TS_Mask                ((uint16_t)0xFF8F)
#define SMCR_MSM_Reset              ((uint16_t)0xFF7F)
#define SMCR_ECE_Set                ((uint16_t)0x4000)
#define CCMR_CC13S_Mask             ((uint16_t)0xFFFC)
#define CCMR_CC24S_Mask             ((uint16_t)0xFCFF)
#define CCMR_TI13Direct_Set         ((uint16_t)0x0001)
#define CCMR_TI24Direct_Set         ((uint16_t)0x0100)
#define CCMR_OC13FE_Reset           ((uint16_t)0xFFFB)
#define CCMR_OC24FE_Reset           ((uint16_t)0xFBFF)
#define CCMR_OC13PE_Reset           ((uint16_t)0xFFF7)
#define CCMR_OC24PE_Reset           ((uint16_t)0xF7FF)
#define CCMR_OC13M_Mask             ((uint16_t)0xFF8F)
#define CCMR_OC24M_Mask             ((uint16_t)0x8FFF) 
#define CCMR_OC13CE_Reset           ((uint16_t)0xFF7F)
#define CCMR_OC24CE_Reset           ((uint16_t)0x7FFF)
#define CCMR_IC13PSC_Mask           ((uint16_t)0xFFF3)
#define CCMR_IC24PSC_Mask           ((uint16_t)0xF3FF)
#define CCMR_IC13F_Mask             ((uint16_t)0xFF0F)
#define CCMR_IC24F_Mask             ((uint16_t)0x0FFF)
#define CCMR_Offset                 ((uint16_t)0x0018)
#define CCER_CCE_Set                ((uint16_t)0x0001)
#define	CCER_CCNE_Set               ((uint16_t)0x0004)
#define CCER_CC1P_Reset             ((uint16_t)0xFFFD)
#define CCER_CC2P_Reset             ((uint16_t)0xFFDF)
#define CCER_CC3P_Reset             ((uint16_t)0xFDFF)
#define CCER_CC4P_Reset             ((uint16_t)0xDFFF)
#define CCER_CC1NP_Reset            ((uint16_t)0xFFF7)
#define CCER_CC2NP_Reset            ((uint16_t)0xFF7F)
#define CCER_CC3NP_Reset            ((uint16_t)0xF7FF)
#define CCER_CC1E_Set               ((uint16_t)0x0001)
#define CCER_CC1E_Reset             ((uint16_t)0xFFFE)
#define CCER_CC1NE_Reset            ((uint16_t)0xFFFB)
#define CCER_CC2E_Set               ((uint16_t)0x0010)
#define CCER_CC2E_Reset             ((uint16_t)0xFFEF)
#define CCER_CC2NE_Reset            ((uint16_t)0xFFBF)
#define CCER_CC3E_Set               ((uint16_t)0x0100)
#define CCER_CC3E_Reset             ((uint16_t)0xFEFF)
#define CCER_CC3NE_Reset            ((uint16_t)0xFBFF)
#define CCER_CC4E_Set               ((uint16_t)0x1000)
#define CCER_CC4E_Reset             ((uint16_t)0xEFFF)
#define BDTR_MOE_Set                ((uint16_t)0x8000)
#define BDTR_MOE_Reset              ((uint16_t)0x7FFF)

/* �ۥΧ� -------------------------------------------------------------*/
/* �ۥ��ܶq -----------------------------------------------------------*/
/* �ۥΨ�ƭ쫬 -------------------------------------------------------*/

static void TI1_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter);
static void TI2_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter);
static void TI3_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter);
static void TI4_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter);

/* �ۥΨ�� -----------------------------------------------------------*/

/**
  * @²�z  �N�~�] TIMx �H�s�����]���ʬ٭�.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1��8�H��ܥ~�].
  * @��^  �S��
  */
void TIM_DeInit(TIM_TypeDef* TIMx)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_ALL_PERIPH(TIMx)); 
 
  if (TIMx == TIM1)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, DISABLE);  
  }     
  else if (TIMx == TIM2)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2, DISABLE);
  }
  else if (TIMx == TIM3)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM3, DISABLE);
  }
  else if (TIMx == TIM4)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4, DISABLE);
  } 
  else if (TIMx == TIM5)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM5, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM5, DISABLE);
  } 
  else if (TIMx == TIM6)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, DISABLE);
  } 
  else if (TIMx == TIM7)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM7, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM7, DISABLE);
  } 
  else
  {
    if (TIMx == TIM8)
    {
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM8, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM8, DISABLE);
    }  
  }
}

/**
  * @²�z  �ھ� TIM_TimeBaseInitStruct �����w���Ѽƪ�l�� TIMx ���ɶ���Ƴ��.
  * @�Ѽ�  TIMx: �o�� x �i�H�O 1, 2, 3, 4, 5 �� 8 �]�w TIM �~�].
  * @�Ѽ�  TIM_TimeBaseInitStruct: ���V�@�ӥ]�t TIM �ɶ���t�m�H���� TIM_BaseInitTypeDef ���c�����w.
  * @��^  �S��
  */
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx)); 
  assert_param(IS_TIM_COUNTER_MODE(TIM_TimeBaseInitStruct->TIM_CounterMode));
  assert_param(IS_TIM_CKD_DIV(TIM_TimeBaseInitStruct->TIM_ClockDivision));
  /* ��ܭp�ƾ��Ҧ� �A�]�m�����W�v */
  TIMx->CR1 &= CR1_CKD_Mask & CR1_CounterMode_Mask;
  TIMx->CR1 |= (uint32_t)TIM_TimeBaseInitStruct->TIM_ClockDivision |
                TIM_TimeBaseInitStruct->TIM_CounterMode;
  
  /* �]�m�۰ʸ˸��� */
  TIMx->ARR = TIM_TimeBaseInitStruct->TIM_Period ;
 
  /* �]�m�w���W���� */
  TIMx->PSC = TIM_TimeBaseInitStruct->TIM_Prescaler;
    
  if ((((uint32_t) TIMx) == TIM1_BASE) || (((uint32_t) TIMx) == TIM8_BASE))  
  {
    /* �]�m���ƭp�ƾ��� */
    TIMx->RCR = TIM_TimeBaseInitStruct->TIM_RepetitionCounter;
  }

  /* ���ͤ@�ӧ�s�ƥ�ߧY���s�˸��w���W���� */
  TIMx->EGR = TIM_PSCReloadMode_Immediate;          
}

/**
  * @²�z  �ھ� TIM_OCInitStruct �����S�w�Ѽƪ�l��TIMx�q�D1.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_OCInitStruct: ���V�@�ӥ]�t�S�wTIMx�~�]���t�m�H���� TIM_OCInitTypeDef ���c�����w.
  * @��^  �S��
  */
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
   
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx)); 
  assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
  assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));   
  /* ����q�D 1: �_�� CC1E �� */
  TIMx->CCER &= CCER_CC1E_Reset;
  
  /* �o�� TIMx CCER(����/����ϯ�) �H�s������ */
  tmpccer = TIMx->CCER;
  /* �o�� TIMx CR2(����H�s��2) �H�s������ */
  tmpcr2 =  TIMx->CR2;
  
  /* �o�� TIMx CCMR1(����/����Ҧ�) �H�s������ */
  tmpccmrx = TIMx->CCMR1;
    
  /* �_���X����Ҧ��� */
  tmpccmrx &= CCMR_OC13M_Mask;
  
  /* ��ܿ�X����Ҧ� */
  tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;
  
  /* �_���X���ʵ��� */
  tmpccer &= CCER_CC1P_Reset;
  /* �]�m��X������� */
  tmpccer |= TIM_OCInitStruct->TIM_OCPolarity;
  
  /* �]�m��X���A */
  tmpccer |= TIM_OCInitStruct->TIM_OutputState;
  
  /* �]�m�������H�s���� */
  TIMx->CCR1 = TIM_OCInitStruct->TIM_Pulse;
  
  if(((uint32_t) TIMx == TIM1_BASE) || ((uint32_t) TIMx == TIM8_BASE))
  {
    assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
    assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
    
    /* �_���X N ���ʵ��� */
    tmpccer &= CCER_CC1NP_Reset;
    /* �]�m��X N ���� */
    tmpccer |= TIM_OCInitStruct->TIM_OCNPolarity;
    /* �_���X N ���A */
    tmpccer &= CCER_CC1NE_Reset;
    
    /* �]�m��X N ���A */
    tmpccer |= TIM_OCInitStruct->TIM_OutputNState;
    /* �_���X����A��X��� N �Ŷ����A */
    tmpcr2 &= CR2_OIS1_Reset;
    tmpcr2 &= CR2_OIS1N_Reset;
    /* �]�m��X�Ŷ����A */
    tmpcr2 |= TIM_OCInitStruct->TIM_OCIdleState;
    /* �]�m��X N �Ŷ����A */
    tmpcr2 |= TIM_OCInitStruct->TIM_OCNIdleState;
  }
  /* �g TIMx CR2(����H�s��2) */
  TIMx->CR2 = tmpcr2;
  
  /* �g TIMx CCMR1(����/����Ҧ��H�s��1) */
  TIMx->CCMR1 = tmpccmrx;
  
  /* �g TIMx CCER(����/����ϯ�H�s��) */
  TIMx->CCER = tmpccer;
}

/**
  * @²�z  �ھ� TIM_OCInitStruct �����S�w�Ѽƪ�l��TIMx�q�D2.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_OCInitStruct: ���V�@�ӥ]�t�S�wTIMx�~�]���t�m�H���� TIM_OCInitTypeDef ���c�����w.
  * @��^  �S��
  */
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
   
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx)); 
  assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
  assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));   
  /* ����q�D 2: �_�� CC2E �� */
  TIMx->CCER &= CCER_CC2E_Reset;
  
  /* �o�� TIMx CCER(����/����ϯ�) �H�s������ */  
  tmpccer = TIMx->CCER;
  /* �o�� TIMx CR2(����H�s��2) �H�s������ */
  tmpcr2 =  TIMx->CR2;
  
  /* �o�� TIMx CCMR1(����/����Ҧ�) �H�s������ */
  tmpccmrx = TIMx->CCMR1;
    
  /* �_���X����Ҧ��� */
  tmpccmrx &= CCMR_OC24M_Mask;
  
  /* ��ܿ�X����Ҧ� */
  tmpccmrx |= (uint16_t)(TIM_OCInitStruct->TIM_OCMode << 8);
  
  /* �_���X���ʵ��� */
  tmpccer &= CCER_CC2P_Reset;
  /* �]�m��X������� */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCPolarity << 4);
  
  /* �]�m��X���A */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputState << 4);
  
  /* �]�m�������H�s���� */
  TIMx->CCR2 = TIM_OCInitStruct->TIM_Pulse;
  
  if(((uint32_t) TIMx == TIM1_BASE) || ((uint32_t) TIMx == TIM8_BASE))
  {
    assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
    assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
    
    /* �_���X N ���ʵ��� */
    tmpccer &= CCER_CC2NP_Reset;
    /* �]�m��X N ���� */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCNPolarity << 4);
    /* �_���X N ���A */
    tmpccer &= CCER_CC2NE_Reset;
    
    /* �]�m��X N ���A */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputNState << 4);
    /* �_���X����A��X��� N �Ŷ����A */
    tmpcr2 &= CR2_OIS2_Reset;
    tmpcr2 &= CR2_OIS2N_Reset;
    /* �]�m��X�Ŷ����A */
    tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCIdleState << 2);
    /* �]�m��X N �Ŷ����A */
    tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCNIdleState << 2);
  }
  /* �g TIMx CR2(����H�s��2) */
  TIMx->CR2 = tmpcr2;
  
  /* �g TIMx CCMR1(����/����Ҧ��H�s��1) */
  TIMx->CCMR1 = tmpccmrx;
  
  /* �g TIMx CCER(����/����ϯ�H�s��) */
  TIMx->CCER = tmpccer;
}

/**
  * @²�z  �ھ� TIM_OCInitStruct �����S�w�Ѽƪ�l��TIMx�q�D3.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_OCInitStruct: ���V�@�ӥ]�t�S�wTIMx�~�]���t�m�H���� TIM_OCInitTypeDef ���c�����w.
  * @��^  �S��
  */
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
   
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx)); 
  assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
  assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));   
  /* ���� 3: �_�� CC3E �� */
  TIMx->CCER &= CCER_CC3E_Reset;
  
  /* �o�� TIMx CCER(����/����ϯ�) �H�s������ */
  tmpccer = TIMx->CCER;
  /* �o�� TIMx CR2(����H�s��2) �H�s������ */
  tmpcr2 =  TIMx->CR2;
  
  /* �o�� TIMx CCMR2(����/����Ҧ�) �H�s������ */
  tmpccmrx = TIMx->CCMR2;
    
  /* �_���X����Ҧ��� */
  tmpccmrx &= CCMR_OC13M_Mask;
  
  /* ��ܿ�X����Ҧ� */
  tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;
  
  /* �_���X���ʵ��� */
  tmpccer &= CCER_CC3P_Reset;
  /* �]�m��X������� */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCPolarity << 8);
  
  /* �]�m��X���A */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputState << 8);
  
  /* �]�m�������H�s���� */
  TIMx->CCR3 = TIM_OCInitStruct->TIM_Pulse;
  
  if(((uint32_t) TIMx == TIM1_BASE) || ((uint32_t) TIMx == TIM8_BASE))
  {
    assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
    assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
    
    /* �_���X N ���ʵ��� */
    tmpccer &= CCER_CC3NP_Reset;
    /* �]�m��X N ���� */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCNPolarity << 8);
    /* �_���X N ���A */
    tmpccer &= CCER_CC3NE_Reset;
    
    /* �]�m��X N ���A */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputNState << 8);
    /* �_���X����A��X��� N �Ŷ����A */
    tmpcr2 &= CR2_OIS3_Reset;
    tmpcr2 &= CR2_OIS3N_Reset;
    /* �]�m��X�Ŷ����A */
    tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCIdleState << 4);
    /* �]�m��X N �Ŷ����A */
    tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCNIdleState << 4);
  }
  /* �g TIMx CR2(����H�s��2) */
  TIMx->CR2 = tmpcr2;
  
  /* �g TIMx CCMR2(����/����Ҧ��H�s��2) */
  TIMx->CCMR2 = tmpccmrx;
  
  /* �g TIMx CCER(����/����ϯ�H�s��) */
  TIMx->CCER = tmpccer;
}

/**
  * @²�z  �ھ� TIM_OCInitStruct �����S�w�Ѽƪ�l��TIMx�q�D4.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_OCInitStruct: ���V�@�ӥ]�t�S�wTIMx�~�]���t�m�H���� TIM_OCInitTypeDef ���c�����w.
  * @��^  �S��
  */
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
   
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx)); 
  assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
  assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));   
  /* ����q�D 4: �_�� CC4E �� */
  TIMx->CCER &= CCER_CC4E_Reset;
  
  /* �o�� TIMx CCER(����/����ϯ�) �H�s������ */
  tmpccer = TIMx->CCER;
  /* �o�� TIMx CR2(����H�s��2) �H�s������ */
  tmpcr2 =  TIMx->CR2;
  
  /* �o�� TIMx CCMR2(����/����Ҧ�) �H�s������ */
  tmpccmrx = TIMx->CCMR2;
    
  /* �_���X����Ҧ��� */
  tmpccmrx &= CCMR_OC24M_Mask;
  
  /* ��ܿ�X����Ҧ� */
  tmpccmrx |= (uint16_t)(TIM_OCInitStruct->TIM_OCMode << 8);
  
  /* �_���X���ʵ��� */
  tmpccer &= CCER_CC4P_Reset;
  /* �]�m��X������� */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCPolarity << 12);
  
  /* �]�m��X���A */
  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputState << 12);
  
  /* �]�m�������H�s���� */
  TIMx->CCR4 = TIM_OCInitStruct->TIM_Pulse;
  
  if(((uint32_t) TIMx == TIM1_BASE) || ((uint32_t) TIMx == TIM8_BASE))
  {
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
    /* �_���X����Ŷ����A */
    tmpcr2 &= CR2_OIS4_Reset;
    /* �]�m��X�Ŷ����A */
    tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCIdleState << 6);
  }
  /* �g TIMx CR2(����H�s��2) */
  TIMx->CR2 = tmpcr2;
  
  /* �g TIMx CCMR2(����/����Ҧ��H�s��2) */  
  TIMx->CCMR2 = tmpccmrx;
  
  /* �g TIMx CCER(����/����ϯ�H�s��) */
  TIMx->CCER = tmpccer;
}

/**
  * @²�z  �ھ� TIM_ ICInitStruct �����S�w�Ѽƪ�l�� TIMx.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_ICInitStruct: ���V�@�ӥ]�t�S�w TIMx �~�]���t�m�H���� TIM_OCInitTypeDef ���c�����w.
  * @��^  �S��
  */
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_CHANNEL(TIM_ICInitStruct->TIM_Channel));
  assert_param(IS_TIM_IC_POLARITY(TIM_ICInitStruct->TIM_ICPolarity));
  assert_param(IS_TIM_IC_SELECTION(TIM_ICInitStruct->TIM_ICSelection));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICInitStruct->TIM_ICPrescaler));
  assert_param(IS_TIM_IC_FILTER(TIM_ICInitStruct->TIM_ICFilter));
  
  if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_1)
  {
    /* TI1 �t�m */
    TI1_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* �]�m��J�����w���W���� */
    TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
  else if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_2)
  {
    /* TI2 �t�m */
    TI2_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* �]�m��J�����w���W���� */
    TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
  else if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_3)
  {
    /* TI3 �t�m */
    TI3_Config(TIMx,  TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* �]�m��J�����w���W���� */
    TIM_SetIC3Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
  else
  {
    /* TI4 �t�m */
    TI4_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* �]�m��J�����w���W���� */
    TIM_SetIC4Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
}

/**
  * @²�z  �̷�TIM_ICInitStruct���w���ѼƳ]�mTIM�]�ƥh�t�m�~����PWM�H��.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_ICInitStruct: ���V�@�ӥ]�t�S�w TIMx �~�]���t�m�H���� TIM_ICInitTypeDef ���c�����w.
  * @��^  �S��
  */
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct)
{
  uint16_t icoppositepolarity = TIM_ICPolarity_Rising;
  uint16_t icoppositeselection = TIM_ICSelection_DirectTI;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  /* ��ܬۤϪ���J���� */
  if (TIM_ICInitStruct->TIM_ICPolarity == TIM_ICPolarity_Rising)
  {
    icoppositepolarity = TIM_ICPolarity_Falling;
  }
  else
  {
    icoppositepolarity = TIM_ICPolarity_Rising;
  }
  /* ��ܬۤϪ���J */
  if (TIM_ICInitStruct->TIM_ICSelection == TIM_ICSelection_DirectTI)
  {
    icoppositeselection = TIM_ICSelection_IndirectTI;
  }
  else
  {
    icoppositeselection = TIM_ICSelection_DirectTI;
  }
  if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_1)
  {
    /* TI1 �t�m */
    TI1_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity, TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* �]�m��J�����w���W���� */
    TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    /* TI2 �t�m */
    TI2_Config(TIMx, icoppositepolarity, icoppositeselection, TIM_ICInitStruct->TIM_ICFilter);
    /* �]�m��J�����w���W���� */
    TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
  else
  { 
    /* TI2 �t�m */
    TI2_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity, TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);
    /* �]�m��J�����w���W���� */
    TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    /* TI1 �t�m */
    TI1_Config(TIMx, icoppositepolarity, icoppositeselection, TIM_ICInitStruct->TIM_ICFilter);
    /* �]�m��J�����w���W���� */
    TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
}

/**
  * @²�z  �t�m: �]�m�b���S�ʡA���Ϯɶ��A��q���AOSSI�AOSSR���A�MAOE(�۰ʿ�X�ϯ�).
  * @�Ѽ�  TIMx: ���Bx�i�H�O1��8�H��ܥ~�]
  * @�Ѽ�  TIM_BDTRInitStruct: ���V�@�ӥ]�t�S�w TIMx �~�]���t�m�H���� TIM_BDTRInitTypeDef ���c�����w.
  * @��^  �S��
  */
void TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_TIM_OSSR_STATE(TIM_BDTRInitStruct->TIM_OSSRState));
  assert_param(IS_TIM_OSSI_STATE(TIM_BDTRInitStruct->TIM_OSSIState));
  assert_param(IS_TIM_LOCK_LEVEL(TIM_BDTRInitStruct->TIM_LOCKLevel));
  assert_param(IS_TIM_BREAK_STATE(TIM_BDTRInitStruct->TIM_Break));
  assert_param(IS_TIM_BREAK_POLARITY(TIM_BDTRInitStruct->TIM_BreakPolarity));
  assert_param(IS_TIM_AUTOMATIC_OUTPUT_STATE(TIM_BDTRInitStruct->TIM_AutomaticOutput));
  /* �t�m�G��q���ŧO�A���_���\��M���ʡAOSSR���A�AOSSI���A�A����ɶ��M�۰ʿ�X�ϯ�� */
  TIMx->BDTR = (uint32_t)TIM_BDTRInitStruct->TIM_OSSRState | TIM_BDTRInitStruct->TIM_OSSIState |
             TIM_BDTRInitStruct->TIM_LOCKLevel | TIM_BDTRInitStruct->TIM_DeadTime |
             TIM_BDTRInitStruct->TIM_Break | TIM_BDTRInitStruct->TIM_BreakPolarity |
             TIM_BDTRInitStruct->TIM_AutomaticOutput;
}

/**
  * @²�z  �� TIM1_TimeBaseInitStruct �����C�@�ӰѼƫ��ʬ٭ȶ�J.
  * @�Ѽ�  TIM_TimeBaseInitStruct : ���V�@�ӱN�Q��l�ƪ� TIM_TimeBaseInitTypeDef ���c�����w.
  * @��^  �S��
  */
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct)
{
  /* �]�m���q�{�t�m */
  TIM_TimeBaseInitStruct->TIM_Period = 0xFFFF;
  TIM_TimeBaseInitStruct->TIM_Prescaler = 0x0000;
  TIM_TimeBaseInitStruct->TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStruct->TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct->TIM_RepetitionCounter = 0x0000;
}

/**
  * @²�z  �� TIM1_OCInitStruct �����C�@�ӰѼƫ��ʬ٭ȶ�J.
  * @�Ѽ�  TIM_OCInitStruct : ���V�@�ӱN�Q��l�ƪ� TIM_OCInitStruct ���c�����w.
  * @��^  �S��
  */
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  /* �]�m���q�{�t�m */
  TIM_OCInitStruct->TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStruct->TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStruct->TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStruct->TIM_Pulse = 0x0000;
  TIM_OCInitStruct->TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStruct->TIM_OCNPolarity = TIM_OCPolarity_High;
  TIM_OCInitStruct->TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStruct->TIM_OCNIdleState = TIM_OCNIdleState_Reset;
}

/**
  * @²�z  �� TIM1_ICInitStruct �����C�@�ӰѼƫ��ʬ٭ȶ�J.
  * @�Ѽ�  TIM_ICInitStruct : ���V�@�ӱN�Q��l�ƪ� TIM_ICInitStruct ���c�����w.
  * @��^  �S��
  */
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct)
{
  /* �]�m���q�{�t�m */
  TIM_ICInitStruct->TIM_Channel = TIM_Channel_1;
  TIM_ICInitStruct->TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStruct->TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStruct->TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStruct->TIM_ICFilter = 0x00;
}

/**
  * @²�z  �� TIM1_BDTRInitStruct �����C�@�ӰѼƫ��ʬ٭ȶ�J.
  * @�Ѽ�  TIM_BDTRInitStruct: ���V�@�ӱN�Q��l�ƪ� TIM1_BDTRInitStruct ���c��.
  * @��^  �S��
  */
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct)
{
  /* �]�m���q�{�t�m */
  TIM_BDTRInitStruct->TIM_OSSRState = TIM_OSSRState_Disable;
  TIM_BDTRInitStruct->TIM_OSSIState = TIM_OSSIState_Disable;
  TIM_BDTRInitStruct->TIM_LOCKLevel = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStruct->TIM_DeadTime = 0x00;
  TIM_BDTRInitStruct->TIM_Break = TIM_Break_Disable;
  TIM_BDTRInitStruct->TIM_BreakPolarity = TIM_BreakPolarity_Low;
  TIM_BDTRInitStruct->TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
}

/**
  * @²�z  �ϯ�Ϊ̥�����w�� TIM �~�].
  * @�Ѽ�  TIMx: ���Bx�i�H�O1��8�H��ܥ~�].
  * @�Ѽ�  NewState: TIMx �~�]���s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* �ϯ� TIM �p�ƾ� */
    TIMx->CR1 |= CR1_CEN_Set;
  }
  else
  {
    /* ���� TIM �p�ƾ� */
    TIMx->CR1 &= CR1_CEN_Reset;
  }
}

/**
  * @²�z  �ϯ�Υ��� TIM �~��D��X.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1��8�H��ܥ~�].
  * @�Ѽ�  NewState: TIM �~��D��X���s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE or DISABLE.
  * @��^  �S��
  */
void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �ϯ� TIM �D��X */
    TIMx->BDTR |= BDTR_MOE_Set;
  }
  else
  {
    /* ���� TIM �D��X */
    TIMx->BDTR &= BDTR_MOE_Reset;
  }  
}

/**
  * @²�z  �ϯ�Υ�����w�� TIM ���_.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1��8�H��ܥ~�].
  * @�Ѽ�  TIM_IT: �N�Q�ϯ�Υ��઺ TIM ���_��.
  *                �o�ӰѼƥi�H���U�C�Ȥ��@:
  *                TIM_IT_Update:  TIM ��s���_��
  *                TIM_IT_CC1:     TIM ��/��� 1 ���_��
  *                TIM_IT_CC2:     TIM ��/��� 2 ���_��
  *                TIM_IT_CC3:     TIM ��/��� 3 ���_��
  *                TIM_IT_CC4:     TIM ��/��� 4 ���_��
  *                TIM_IT_COM:     TIM COM���_��
  *                TIM_IT_Trigger: TIM Ĳ�o���_��
  *                TIM_IT_Break:   TIM �b�����_��
  * @���� 
  *   - TIM6 �M TIM7 �u�ಣ�ͮե����_. 
  *   - TIM_IT_COM �M TIM_IT_Break �u��M TIM1 �M TIM8 �@�_�ϥ�.  
  * @�Ѽ�  NewState: TIM ���_���s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState)
{  
  /* �ˬd�Ѽ�s */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_IT(TIM_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* �ϯत�_�� */
    TIMx->DIER |= TIM_IT;
  }
  else
  {
    /* ���त�_�� */
    TIMx->DIER &= (uint16_t)~TIM_IT;
  }
}

/**
  * @²�z  �t�m�N�ѳn��޵o�� TIM �ƥ�.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1��8�H��ܥ~�].
  * @�Ѽ�  TIM_EventSource: ���w�ƥ�.
  *                         �o�ӰѼƥi�H���U�C�@�өΧ�h����:	   
  *          TIM_EventSource_Update: �w�ɾ���s�ƥ�
  *          TIM_EventSource_CC1:     �w�ɾ�������� 1 �ƥ�
  *          TIM_EventSource_CC2:     �w�ɾ�������� 2 �ƥ�
  *          TIM_EventSource_CC3:     �w�ɾ�������� 3 �ƥ�
  *          TIM_EventSource_CC4:     �w�ɾ�������� 4 �ƥ�
  *          TIM_EventSource_COM:     �w�ɾ� COM �ƥ�  
  *          TIM_EventSource_Trigger: �w�ɾ�Ĳ�o���ƥ�
  *          TIM_EventSource_Break:   �w�ɾ��b���ƥ�
  * @���� 
  *   - TIM6 �M TIM7 �u�ಣ�ͮե����_. 
  *   - TIM_IT_COM �M TIM_IT_Break �u��M TIM1 �M TIM8 �@�_�ϥ�. 
  * @��^  �S��
  */
void TIM_GenerateEvent(TIM_TypeDef* TIMx, uint16_t TIM_EventSource)
{ 
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_EVENT_SOURCE(TIM_EventSource));
  
  /* �]�m�ƥ� */
  TIMx->EGR = TIM_EventSource;
}

/**
  * @²�z  �t�m TIMx ��DMA���f.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_DMABase: DMA ��a�}.
  *                     �o�ӰѼƥi�H���U�����Ȥ��@:
  *   TIM_DMABase_CR, TIM_DMABase_CR2, TIM_DMABase_SMCR,
  *   TIM_DMABase_DIER, TIM1_DMABase_SR, TIM_DMABase_EGR,
  *   TIM_DMABase_CCMR1, TIM_DMABase_CCMR2, TIM_DMABase_CCER,
  *   TIM_DMABase_CNT, TIM_DMABase_PSC, TIM_DMABase_ARR,
  *   TIM_DMABase_RCR, TIM_DMABase_CCR1, TIM_DMABase_CCR2,
  *   TIM_DMABase_CCR3, TIM_DMABase_CCR4, TIM_DMABase_BDTR,
  *   TIM_DMABase_DCR.
  * @�Ѽ�  TIM_DMABurstLength: DMA �߽Ħ����.
  *                            �o�ӰѼƥi�H���U����ӭȤ��@:
  *        TIM_DMABurstLength_1Byte �M TIM_DMABurstLength_18Bytes.
  * @��^  �S��
  */
void TIM_DMAConfig(TIM_TypeDef* TIMx, uint16_t TIM_DMABase, uint16_t TIM_DMABurstLength)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_DMA_BASE(TIM_DMABase));
  assert_param(IS_TIM_DMA_LENGTH(TIM_DMABurstLength));
  /* �]�m DMA ��a�}�M DMA �߽Ħ���� */
  TIMx->DCR = TIM_DMABase | TIM_DMABurstLength;
}

/**
  * @²�z  �ϯ�Υ��� TIMx �� DMA �ШD.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1��8�H��ܥ~�]. 
  * @�Ѽ�  TIM_DMASource: ���w DMA �ШD�ӷ�.
  *                       �o�ӰѼƥi�H�O�U������Ȫ��զX:
  *                       TIM_DMA_Update:  TIM ��s���_��
  *                       TIM_DMA_CC1:     TIM ������ 1 DMA ��
  *                       TIM_DMA_CC2:     TIM ������ 2 DMA ��
  *                       TIM_DMA_CC3:     TIM ������ 3 DMA ��
  *                       TIM_DMA_CC4:     TIM ������ 4 DMA ��
  *                       TIM_DMA_COM:     TIM COM DMA ��
  *                       TIM_DMA_Trigger: TIM Ĳ�o DMA ��
  * @�Ѽ�  NewState: DMA �ШD�s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void TIM_DMACmd(TIM_TypeDef* TIMx, uint16_t TIM_DMASource, FunctionalState NewState)
{ 
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_DMA_SOURCE(TIM_DMASource));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* �ϯ� DMA �� */
    TIMx->DIER |= TIM_DMASource; 
  }
  else
  {
    /* ���� DMA �� */
    TIMx->DIER &= (uint16_t)~TIM_DMASource;
  }
}

/**
  * @²�z  �t�m TIMx ��������
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @��^  �S��
  */
void TIM_InternalClockConfig(TIM_TypeDef* TIMx)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  /* ���ऺ�������w���W���q�Ҧ� */
  TIMx->SMCR &=  SMCR_SMS_Mask;
}

/**
  * @²�z  �t�m TIMx ����Ĳ�o�����~�������Ҧ�
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_ITRSource: Ĳ�o��.
  *                       �o�ӰѼƥi�H���U�����Ȥ��@:
  *                       TIM_TS_ITR0: ����Ĳ�o�� 0
  *                       TIM_TS_ITR1: ����Ĳ�o�� 1
  *                       TIM_TS_ITR2: ����Ĳ�o�� 2
  *                       TIM_TS_ITR3: ����Ĳ�o�� 3
  * @��^  �S��
  */
void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_INTERNAL_TRIGGER_SELECTION(TIM_InputTriggerSource));
  /* ��ܤ���Ĳ�o�� */
  TIM_SelectInputTrigger(TIMx, TIM_InputTriggerSource);
  /* ��ܥ~�������Ҧ�1 */
  TIMx->SMCR |= TIM_SlaveMode_External1;
}

/**
  * @²�z  �]�m TIMx Ĳ�o���~������
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_TIxExternalCLKSource: Ĳ�o��.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_TIxExternalCLK1Source_TI1ED: TI1 ��t�˴���
  *          TIM_TIxExternalCLK1Source_TI1: �w�z�諸�w�ɾ���J 1
  *          TIM_TIxExternalCLK1Source_TI2: �w�z�諸�w�ɾ���J 2
  * @�Ѽ�  TIM_ICPolarity: ���w TIx ����.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_ICPolarity_Rising
  *          TIM_ICPolarity_Falling
  * @�Ѽ�  ICFilter : ���w��J����L�o��.
  *                   �ӰѼƥi�H�O0x0��0xF��������.
  * @��^  �S��
  */
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_TIxExternalCLKSource,
                                uint16_t TIM_ICPolarity, uint16_t ICFilter)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_TIXCLK_SOURCE(TIM_TIxExternalCLKSource));
  assert_param(IS_TIM_IC_POLARITY(TIM_ICPolarity));
  assert_param(IS_TIM_IC_FILTER(ICFilter));
  /* �t�m�w�ɾ���J������ */
  if (TIM_TIxExternalCLKSource == TIM_TIxExternalCLK1Source_TI2)
  {
    TI2_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
  }
  else
  {
    TI1_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
  }
  /* ���Ĳ�o�� */
  TIM_SelectInputTrigger(TIMx, TIM_TIxExternalCLKSource);
  /* ��ܥ~�������Ҧ�1 */
  TIMx->SMCR |= TIM_SlaveMode_External1;
}

/**
  * @²�z  �t�m�~�������Ҧ�1
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_ExtTRGPrescaler: �~��Ĳ�o���w���W��.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_ExtTRGPSC_OFF:  ETRP �w���W�� ��.
  *          TIM_ExtTRGPSC_DIV2: ETRP �W�v���H 2.
  *          TIM_ExtTRGPSC_DIV4: ETRP �W�v���H 4.
  *          TIM_ExtTRGPSC_DIV8: ETRP �W�v���H 8.
  * @�Ѽ�  TIM_ExtTRGPolarity: �~��Ĳ�o������.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_ExtTRGPolarity_Inverted:    �C�q���ΤU���u.
  *          TIM_ExtTRGPolarity_NonInverted: ���q���ΤW�ɪu.
  * @�Ѽ�  ExtTRGFilter: �~��Ĳ�o���L�o��.
  *          �ӰѼƥi�H�O0x0��0xF��������
  * @��^  �S��
  */ 
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                             uint16_t ExtTRGFilter)
{
  uint16_t tmpsmcr = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
  assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
  assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));
  /* �t�m ETR ������ */
  TIM_ETRConfig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);
  
  /* �o�� TIMx SMCR(�q�Ҧ�����) �H�s������ */
  tmpsmcr = TIMx->SMCR;
  /* �_�� SMS(�q�Ҧ����) �� */
  tmpsmcr &= SMCR_SMS_Mask;
  /* ��ܥ~�������Ҧ�1 */
  tmpsmcr |= TIM_SlaveMode_External1;
  /* ���Ĳ�o�� �A��� : ETRF */
  tmpsmcr &= SMCR_TS_Mask;
  tmpsmcr |= TIM_TS_ETRF;
  /* �g TIMx SMCR */
  TIMx->SMCR = tmpsmcr;
}

/**
  * @²�z  �t�m�~�������Ҧ�2
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_ExtTRGPrescaler: �~��Ĳ�o���w���W��.
  *          ���i�H�O�U�����Ȥ��@:
  *          TIM_ExtTRGPSC_OFF:  ETRP �w���W�� ��.
  *          TIM_ExtTRGPSC_DIV2: ETRP �W�v���H 2.
  *          TIM_ExtTRGPSC_DIV4: ETRP �W�v���H 4.
  *          TIM_ExtTRGPSC_DIV8: ETRP �W�v���H 8.
  * @�Ѽ�  TIM_ExtTRGPolarity: �~��Ĳ�o������.
  *          ���i�H�O�U�����Ȥ��@:
  *          TIM_ExtTRGPolarity_Inverted:    �C�q���ΤU���u.
  *          TIM_ExtTRGPolarity_NonInverted: ���q���ΤW�ɪu.
  * @�Ѽ�  ExtTRGFilter: �~��Ĳ�o���L�o��.
  *          �ӰѼƥi�H�O0x0��0xF��������
  * @��^  �S��
  */
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, 
                             uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
  assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
  assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));
  /* �t�m ETR ������ */
  TIM_ETRConfig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);
  /* �ϯ�~�������Ҧ�2 */
  TIMx->SMCR |= SMCR_ECE_Set;
}

/**
  * @²�z  �t�m TIMx �~��Ĳ�o (ETR).
  * @²�z  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_ExtTRGPrescaler: �~��Ĳ�o���w���W��.
  *          ���i�H�O�U�����Ȥ��@:
  *          TIM_ExtTRGPSC_OFF:  ETRP �w���W�� ��.
  *          TIM_ExtTRGPSC_DIV2: ETRP �W�v���H 2.
  *          TIM_ExtTRGPSC_DIV4: ETRP �W�v���H 4.
  *          TIM_ExtTRGPSC_DIV8: ETRP �W�v���H 8.
  * @�Ѽ�  TIM_ExtTRGPolarity: �~��Ĳ�o������.
  *          ���i�H�O�U�����Ȥ��@:
  *          TIM_ExtTRGPolarity_Inverted:    �C�q���ΤU���u.
  *          TIM_ExtTRGPolarity_NonInverted: ���q���ΤW�ɪu.
  * @�Ѽ�  ExtTRGFilter: �~��Ĳ�o���L�o��.
  *          �ӰѼƥi�H�O0x0��0xF��������
  * @��^  �S��
  */
void TIM_ETRConfig(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                   uint16_t ExtTRGFilter)
{
  uint16_t tmpsmcr = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
  assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
  assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));
  tmpsmcr = TIMx->SMCR;
  /* �_�� ETR �� */
  tmpsmcr &= SMCR_ETR_Mask;
  /* �]�m�w���W���A�L�o���ȩM���� */
  tmpsmcr |= (uint16_t)(TIM_ExtTRGPrescaler | (uint16_t)(TIM_ExtTRGPolarity | (uint16_t)(ExtTRGFilter << (uint16_t)8)));
  /* �gTIMx SMCR */
  TIMx->SMCR = tmpsmcr;
}

/**
  * @²�z  �t�m TIMx �w���W��.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1��8�H��ܥ~�].
  * @�Ѽ�  Prescaler: ���w�w���W�ƪ��s��
  * @�Ѽ�  TIM_PSCReloadMode: ���w�w���W�ƭ����Ҧ�
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_PSCReloadMode_Update:    TIM �w���W�Ȧb��s�ƥ�ˤJ.
  *          TIM_PSCReloadMode_Immediate: TIM �w���W�ȧY�ɸˤJ.
  * @��^  �S��
  */
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_PRESCALER_RELOAD(TIM_PSCReloadMode));
  /* �]�m�w���W���� */
  TIMx->PSC = Prescaler;
  /* �]�m �� �_�� UG �� */
  TIMx->EGR = TIM_PSCReloadMode;
}

/**
  * @²�z  ���w TIMx �p�ƾ��Ҧ�.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_CounterMode: �ݨϥΪ��p�ƾ��Ҧ�
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_CounterMode_Up:             TIM �V�W�p�ƼҦ�
  *          TIM_CounterMode_Down:           TIM �V�U�p�ƼҦ�
  *          TIM_CounterMode_CenterAligned1: TIM ���߹���Ҧ�1
  *          TIM_CounterMode_CenterAligned2: TIM ���߹���Ҧ�2
  *          TIM_CounterMode_CenterAligned3: TIM ���߹���Ҧ�3
  * @��^  �S��
  */
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint16_t TIM_CounterMode)
{
  uint16_t tmpcr1 = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_COUNTER_MODE(TIM_CounterMode));
  tmpcr1 = TIMx->CR1;
  /* �_�� CMS �M DIR �� */
  tmpcr1 &= CR1_CounterMode_Mask;
  /* �]�m�p�ƼҦ� */
  tmpcr1 |= TIM_CounterMode;
  /* �g TIMx CR1 �H�s�� */
  TIMx->CR1 = tmpcr1;
}

/**
  * @²�z  ��ܿ�JĲ�o��
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_InputTriggerSource: ��JĲ�o��.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_TS_ITR0:    ����Ĳ�o�� 0
  *          TIM_TS_ITR1:    ����Ĳ�o�� 1
  *          TIM_TS_ITR2:    ����Ĳ�o�� 2
  *          TIM_TS_ITR3:    ����Ĳ�o�� 3
  *          TIM_TS_TI1F_ED: TI1 ��t�˴���
  *          TIM_TS_TI1FP1:  �L�o��������J 1
  *          TIM_TS_TI2FP2:  �L�o��������J 2
  *          TIM_TS_ETRF:    �~��Ĳ�o��J
  * @��^  �S��
  */
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource)
{
  uint16_t tmpsmcr = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_TRIGGER_SELECTION(TIM_InputTriggerSource));
  /* �o�� TIMx SMCR �H�s���� */
  tmpsmcr = TIMx->SMCR;
  /* �_�� TS �� */
  tmpsmcr &= SMCR_TS_Mask;
  /* �]�m��JĲ�o�� */
  tmpsmcr |= TIM_InputTriggerSource;
  /* �g TIMx SMCR */
  TIMx->SMCR = tmpsmcr;
}

/**
  * @²�z  �t�m TIMx �s�X���ɭ�.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_EncoderMode: ���w TIMx �s�X���Ҧ�.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_EncoderMode_TI1:  TIM�s�X���ϥμҦ�1.
  *          TIM_EncoderMode_TI2:  TIM�s�X���ϥμҦ�2.
  *          TIM_EncoderMode_TI12: TIM�s�X���ϥμҦ�3.
  * @�Ѽ�  TIM_IC1Polarity: ���w IC1 ����
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_ICPolarity_Falling: IC �U���u.
  *          TIM_ICPolarity_Rising:  IC �W�ɪu.
  * @�Ѽ�  TIM_IC2Polarity: ���w IC2 ����
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_ICPolarity_Falling: IC �U���u.
  *          TIM_ICPolarity_Rising:  IC �W�ɪu.
  * @��^  �S��
  */
void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, uint16_t TIM_EncoderMode,
                                uint16_t TIM_IC1Polarity, uint16_t TIM_IC2Polarity)
{
  uint16_t tmpsmcr = 0;
  uint16_t tmpccmr1 = 0;
  uint16_t tmpccer = 0;
    
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_ENCODER_MODE(TIM_EncoderMode));
  assert_param(IS_TIM_IC_POLARITY(TIM_IC1Polarity));
  assert_param(IS_TIM_IC_POLARITY(TIM_IC2Polarity));

  /* �o�� TIMx SMCR �H�s������ */
  tmpsmcr = TIMx->SMCR;

  /* �o�� TIMx CCMR1 �H�s������ */
  tmpccmr1 = TIMx->CCMR1;

  /* �o�� TIMx CCER �H�s������ */
  tmpccer = TIMx->CCER;

  /* �]�m�s�X���Ҧ� */
  tmpsmcr &= SMCR_SMS_Mask;
  tmpsmcr |= TIM_EncoderMode;

  /* ��ܮ����� 1 �M������ 2 �@����J */
  tmpccmr1 &= CCMR_CC13S_Mask & CCMR_CC24S_Mask;
  tmpccmr1 |= CCMR_TI13Direct_Set | CCMR_TI24Direct_Set;

  /* �]�m TI1 �M TI2 ���� */
  tmpccer &= CCER_CC1P_Reset & CCER_CC2P_Reset;
  tmpccer |= (uint16_t)(TIM_IC1Polarity | (uint16_t)(TIM_IC2Polarity << (uint16_t)4));

  /* �g TIMx SMCR */
  TIMx->SMCR = tmpsmcr;

  /* �g TIMx CCMR1 */
  TIMx->CCMR1 = tmpccmr1;

  /* �g TIMx CCER */
  TIMx->CCER = tmpccer;
}

/**
  * @²�z  �m TIMx ��X1�����ʩΪ̫D���ʹq��.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_ForcedAction: ��X�H�����]�m�ʧ@.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_ForcedAction_Active:   �j��OCxREF�����Ĺq��
  *          TIM_ForcedAction_InActive: �j��OCxREF���L�Ĺq��
  * @��^  �S��
  */
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction)
{
  uint16_t tmpccmr1 = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
  tmpccmr1 = TIMx->CCMR1;
  /* �_�� OC1M �� */
  tmpccmr1 &= CCMR_OC13M_Mask;
  /* �t�m�j���X�Ҧ� */
  tmpccmr1 |= TIM_ForcedAction;
  /* �g TIMx CCMR1 �H�s�� */
  TIMx->CCMR1 = tmpccmr1;
}

/**
  * @²�z  �m TIMx ��X2�����ʩΪ̫D���ʹq��.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_ForcedAction: ��X�H�����]�m�ʧ@.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_ForcedAction_Active:   �j��OCxREF�����Ĺq��
  *          TIM_ForcedAction_InActive: �j��OCxREF���L�Ĺq��
  * @��^  �S��
  */
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction)
{
  uint16_t tmpccmr1 = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
  tmpccmr1 = TIMx->CCMR1;
  /* �_�� OC2M �� */
  tmpccmr1 &= CCMR_OC24M_Mask;
  /* �t�m�j���X�Ҧ� */
  tmpccmr1 |= (uint16_t)(TIM_ForcedAction << 8);
  /* �g TIMx CCMR1 �H�s�� */
  TIMx->CCMR1 = tmpccmr1;
}

/**
  * @²�z  �m TIMx ��X3�����ʩΪ̫D���ʹq��.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_ForcedAction: ��X�H�����]�m�ʧ@.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_ForcedAction_Active:   �j��OCxREF�����Ĺq��
  *          TIM_ForcedAction_InActive: �j��OCxREF���L�Ĺq��
  * @��^  �S��
  */
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction)
{
  uint16_t tmpccmr2 = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
  tmpccmr2 = TIMx->CCMR2;
  /* �_�� OC1M �� */
  tmpccmr2 &= CCMR_OC13M_Mask;
  /* �t�m�j���X�Ҧ� */
  tmpccmr2 |= TIM_ForcedAction;
  /* �g TIMx CCMR2 �H�s�� */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @²�z  �m TIMx ��X4�����ʩΪ̫D���ʹq��.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_ForcedAction: ��X�H�����]�m�ʧ@.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_ForcedAction_Active:   �j��OCxREF�����Ĺq��
  *          TIM_ForcedAction_InActive: �j��OCxREF���L�Ĺq��
  * @��^  �S��
  */
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction)
{
  uint16_t tmpccmr2 = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
  tmpccmr2 = TIMx->CCMR2;
  /* �_�� OC2M �� */
  tmpccmr2 &= CCMR_OC24M_Mask;
  /* �t�m�j���X�Ҧ� */
  tmpccmr2 |= (uint16_t)(TIM_ForcedAction << 8);
  /* �g TIMx CCMR2 �H�s�� */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @²�z  �ϯ�Ϊ̥��� TIMx �b ARR �W���w�˸��H�s��.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  NewState: �bTIM1_CR1�H�s������ARPE�쪺�s���A
  *                  �o�ӰѼƥi�H�O: ENABLE or DISABLE.
  * @��^  �S��
  */
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �]�m ARR ���w�˸��� */
    TIMx->CR1 |= CR1_ARPE_Set;
  }
  else
  {
    /* �_�� ARR ���w�˸��� */
    TIMx->CR1 &= CR1_ARPE_Reset;
  }
}

/**
  * @²�z  ��� TIM �~�]���q�T�ƥ�.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1��8�H��ܥ~�]
  * @�Ѽ�  NewState: �q�T�ƥ󪺷s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void TIM_SelectCOM(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �]�m COM �� */
    TIMx->CR2 |= CR2_CCUS_Set;
  }
  else
  {
    /* �_�� COM �� */
    TIMx->CR2 &= CR2_CCUS_Reset;
  }
}

/**
  * @²�z  ��� TIMx �~�]�������� DMA ��.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  NewState: ������ DMA �����s���A
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void TIM_SelectCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �]�m CCDS �� */
    TIMx->CR2 |= CR2_CCDS_Set;
  }
  else
  {
    /* �_�� CCDS �� */
    TIMx->CR2 &= CR2_CCDS_Reset;
  }
}

/**
  * @²�z  �]�m�Ϊ̴_�� TIMx �����������.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1��8�H��ܥ~�]
  * @�Ѽ�  NewState: �������w������쪺�s���A
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void TIM_CCPreloadControl(TIM_TypeDef* TIMx, FunctionalState NewState)
{ 
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �]�m CCPC �� */
    TIMx->CR2 |= CR2_CCPC_Set;
  }
  else
  {
    /* �_�� CCPC �� */
    TIMx->CR2 &= CR2_CCPC_Reset;
  }
}

/**
  * @²�z  �ϯ�Ϊ̥��� TIMx �b CCR1 �W���w�˸��H�s��.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_OCPreload: ��X����w�˸����A
  *                       �o�ӰѼƥi�H���U�����Ȥ��@:
  *                       TIM_OCPreload_Enable
  *                       TIM_OCPreload_Disable
  * @��^  �S��
  */
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload)
{
  uint16_t tmpccmr1 = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));
  tmpccmr1 = TIMx->CCMR1;
  /* �_�� OC1PE �� */
  tmpccmr1 &= CCMR_OC13PE_Reset;
  /* �ϯ�Ϊ̥���w�˸��H�s�� */
  tmpccmr1 |= TIM_OCPreload;
  /* �g TIMx CCMR1 �H�s�� */
  TIMx->CCMR1 = tmpccmr1;
}

/**
  * @²�z  �ϯ�Ϊ̥��� TIMx �b CCR2 �W���w�˸��H�s��.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_OCPreload: ��X����w�˸����A
  *                       �o�ӰѼƥi�H���U�����Ȥ��@:
  *                       TIM_OCPreload_Enable
  *                       TIM_OCPreload_Disable
  * @��^  �S��
  */
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload)
{
  uint16_t tmpccmr1 = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));
  tmpccmr1 = TIMx->CCMR1;
  /* �_�� OC2PE �� */
  tmpccmr1 &= CCMR_OC24PE_Reset;
  /* �ϯ�Ϊ̥���w�˸��H�s�� */
  tmpccmr1 |= (uint16_t)(TIM_OCPreload << 8);
  /* �g TIMx CCMR1 �H�s�� */
  TIMx->CCMR1 = tmpccmr1;
}

/**
  * @²�z  �ϯ�Ϊ̥��� TIMx �b CCR3 �W���w�˸��H�s��.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_OCPreload: ��X����w�˸����A
  *                       �o�ӰѼƥi�H���U�����Ȥ��@:
  *                       TIM_OCPreload_Enable
  *                       TIM_OCPreload_Disable
  * @��^  �S��
  */
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload)
{
  uint16_t tmpccmr2 = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));
  tmpccmr2 = TIMx->CCMR2;
  /* �_�� OC3PE �� */
  tmpccmr2 &= CCMR_OC13PE_Reset;
  /* �ϯ�Ϊ̥���w�˸��H�s�� */
  tmpccmr2 |= TIM_OCPreload;
  /* �g TIMx CCMR2 �H�s�� */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @²�z  �ϯ�Ϊ̥��� TIMx �b CCR4 �W���w�˸��H�s��.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_OCPreload: ��X����w�˸����A
  *                       �o�ӰѼƥi�H���U�����Ȥ��@:
  *                       TIM_OCPreload_Enable
  *                       TIM_OCPreload_Disable
  * @��^  �S��
  */
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload)
{
  uint16_t tmpccmr2 = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));
  tmpccmr2 = TIMx->CCMR2;
  /* �_�� OC4PE �� */
  tmpccmr2 &= CCMR_OC24PE_Reset;
  /* �ϯ�Ϊ̥���w�˸��H�s�� */
  tmpccmr2 |= (uint16_t)(TIM_OCPreload << 8);
  /* �g TIMx CCMR2 �H�s�� */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @²�z  �]�m TIMx ������1�ֳt�S�x.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_OCFast: ��X����ֳt�S�ʷs���A.
  *                    �o�ӰѼƥi�H���U�����Ȥ��@:
  *                    TIM_OCFast_Enable:  TIM ��X����ֳt�ʯ�ϯ�
  *                    TIM_OCFast_Disable: TIM ��X����ֳt�ʯॢ��
  * @��^  �S��
  */
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast)
{
  uint16_t tmpccmr1 = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));
  /* �o�� TIMx CCMR1 �H�s������ */
  tmpccmr1 = TIMx->CCMR1;
  /* �_�� OC1FE �� */
  tmpccmr1 &= CCMR_OC13FE_Reset;
  /* �ϯ�Υ��ஷ�����ֳt�S�x */
  tmpccmr1 |= TIM_OCFast;
  /* �g TIMx CCMR1 */
  TIMx->CCMR1 = tmpccmr1;
}

/**
  * @²�z  �]�m TIMx ������2�ֳt�S�x.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_OCFast: ��X����ֳt�S�ʷs���A.
  *                    �o�ӰѼƥi�H���U�����Ȥ��@:
  *                    TIM_OCFast_Enable:  TIM ��X����ֳt�ʯ�ϯ�
  *                    TIM_OCFast_Disable: TIM ��X����ֳt�ʯॢ��
  * @��^  �S��
  */
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast)
{
  uint16_t tmpccmr1 = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));
  /* �o�� TIMx CCMR1 �H�s������ */
  tmpccmr1 = TIMx->CCMR1;
  /* �_�� OC2FE �� */
  tmpccmr1 &= CCMR_OC24FE_Reset;
  /* �ϯ�Υ��ஷ�����ֳt�S�x */
  tmpccmr1 |= (uint16_t)(TIM_OCFast << 8);
  /* �g TIMx CCMR1 */
  TIMx->CCMR1 = tmpccmr1;
}

/**
  * @²�z  �]�m TIMx ������3�ֳt�S�x.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_OCFast: ��X����ֳt�S�ʷs���A.
  *                    �o�ӰѼƥi�H���U�����Ȥ��@:
  *                    TIM_OCFast_Enable:  TIM ��X����ֳt�ʯ�ϯ�
  *                    TIM_OCFast_Disable: TIM ��X����ֳt�ʯॢ��
  * @��^  �S��
  */
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast)
{
  uint16_t tmpccmr2 = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));
  /* �o�� TIMx CCMR2 �H�s������ */
  tmpccmr2 = TIMx->CCMR2;
  /* �_�� OC3FE �� */
  tmpccmr2 &= CCMR_OC13FE_Reset;
  /* �ϯ�Υ��ஷ�����ֳt�S�x */
  tmpccmr2 |= TIM_OCFast;
  /* �g TIMx CCMR2 */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @²�z  �]�m TIMx ������4�ֳt�S�x.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_OCFast: ��X����ֳt�S�ʷs���A.
  *                    �o�ӰѼƥi�H���U�����Ȥ��@:
  *                    TIM_OCFast_Enable:  TIM ��X����ֳt�ʯ�ϯ�
  *                    TIM_OCFast_Disable: TIM ��X����ֳt�ʯॢ��
  * @��^  �S��
  */
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast)
{
  uint16_t tmpccmr2 = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));
  /* �o�� TIMx CCMR2 �H�s������ */
  tmpccmr2 = TIMx->CCMR2;
  /* �_�� OC4FE �� */
  tmpccmr2 &= CCMR_OC24FE_Reset;
  /* �ϯ�Υ��ஷ�����ֳt�S�x */
  tmpccmr2 |= (uint16_t)(TIM_OCFast << 8);
  /* �g TIMx CCMR2 */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @²�z  �b�@�ӥ~���ƥ�ɲM���Ϊ̫O�� OCREF1 �H��
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_OCClear: ��X����M���ϯ�쪺�s���A.
  *                     �o�ӰѼƥi�H���U�����Ȥ��@:
  *                     TIM_OCClear_Enable:  TIM ��X����M���ϯ�
  *                     TIM_OCClear_Disable: TIM ��X����M������
  * @��^  �S��
  */
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear)
{
  uint16_t tmpccmr1 = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));
  tmpccmr1 = TIMx->CCMR1;
  /* �_�� OC1CE �� */
  tmpccmr1 &= CCMR_OC13CE_Reset;
  /* �ϯ�Υ����X����M���� */
  tmpccmr1 |= TIM_OCClear;
  /* �g TIMx CCMR1 �H�s�� */
  TIMx->CCMR1 = tmpccmr1;
}

/**
  * @²�z  �b�@�ӥ~���ƥ�ɲM���Ϊ̫O�� OCREF2 �H��
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_OCClear: ��X����M���ϯ�쪺�s���A.
  *                     �o�ӰѼƥi�H���U�����Ȥ��@:
  *                     TIM_OCClear_Enable:  TIM ��X����M���ϯ�
  *                     TIM_OCClear_Disable: TIM ��X����M������
  * @��^  �S��
  */
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear)
{
  uint16_t tmpccmr1 = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));
  tmpccmr1 = TIMx->CCMR1;
  /* �_�� OC2CE �� */
  tmpccmr1 &= CCMR_OC24CE_Reset;
  /* �ϯ�Υ����X����M���� */
  tmpccmr1 |= (uint16_t)(TIM_OCClear << 8);
  /* �g TIMx CCMR1 �H�s�� */
  TIMx->CCMR1 = tmpccmr1;
}

/**
  * @²�z  �b�@�ӥ~���ƥ�ɲM���Ϊ̫O�� OCREF3 �H��
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_OCClear: ��X����M���ϯ�쪺�s���A.
  *                     �o�ӰѼƥi�H���U�����Ȥ��@:
  *                     TIM_OCClear_Enable:  TIM ��X����M���ϯ�
  *                     TIM_OCClear_Disable: TIM ��X����M������
  * @��^  �S��
  */
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear)
{
  uint16_t tmpccmr2 = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));
  tmpccmr2 = TIMx->CCMR2;
  /* �_�� OC3CE �� */
  tmpccmr2 &= CCMR_OC13CE_Reset;
  /* �ϯ�Υ����X����M���� */
  tmpccmr2 |= TIM_OCClear;
  /* �g TIMx CCMR2 �H�s�� */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @²�z  �b�@�ӥ~���ƥ�ɲM���Ϊ̫O�� OCREF4 �H��
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_OCClear: ��X����M���ϯ�쪺�s���A.
  *                     �o�ӰѼƥi�H���U�����Ȥ��@:
  *                     TIM_OCClear_Enable:  TIM ��X����M���ϯ�
  *                     TIM_OCClear_Disable: TIM ��X����M������
  * @��^  �S��
  */
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear)
{
  uint16_t tmpccmr2 = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));
  tmpccmr2 = TIMx->CCMR2;
  /* �_�� OC4CE �� */
  tmpccmr2 &= CCMR_OC24CE_Reset;
  /* �ϯ�Υ����X����M���� */
  tmpccmr2 |= (uint16_t)(TIM_OCClear << 8);
  /* �g TIMx CCMR2 �H�s�� */
  TIMx->CCMR2 = tmpccmr2;
}

/**
  * @²�z  �]�m TIMx �q�D1����.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_OCPolarity: ���w�� OC1 ����
  *                        �o�ӰѼƥi�H���U�����Ȥ��@:
  *                        TIM_OCPolarity_High: ��X������ʰ�
  *                        TIM_OCPolarity_Low:  ��X������ʧC
  * @��^  �S��
  */
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity)
{
  uint16_t tmpccer = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));
  tmpccer = TIMx->CCER;
  /* �]�m�δ_�� CC1P �� */
  tmpccer &= CCER_CC1P_Reset;
  tmpccer |= TIM_OCPolarity;
  /* �g TIMx CCER �H�s�� */
  TIMx->CCER = tmpccer;
}

/**
  * @²�z  �t�m TIMx �q�D 1N ����.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_OCNPolarity: ���w OC1N ����
  *                         �o�ӰѼƥi�H���U�����Ȥ��@:
  *                         TIM_OCNPolarity_High: ��X������ʰ�
  *                         TIM_OCNPolarity_Low:  ��X������ʧC
  * @��^  �S��
  */
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity)
{
  uint16_t tmpccer = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));
   
  tmpccer = TIMx->CCER;
  /* �]�m�δ_�� CC1NP �� */
  tmpccer &= CCER_CC1NP_Reset;
  tmpccer |= TIM_OCNPolarity;
  /* �g TIMx CCER �H�s�� */
  TIMx->CCER = tmpccer;
}

/**
  * @²�z  �]�m TIMx �q�D2����.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_OCPolarity: ���w�� OC2 ����
  *                        �o�ӰѼƥi�H���U�����Ȥ��@:
  *                        TIM_OCPolarity_High: ��X������ʰ�
  *                        TIM_OCPolarity_Low:  ��X������ʧC
  * @��^  �S��
  */
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity)
{
  uint16_t tmpccer = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));
  tmpccer = TIMx->CCER;
  /* �]�m�δ_�� CC2P �� */
  tmpccer &= CCER_CC2P_Reset;
  tmpccer |= (uint16_t)(TIM_OCPolarity << 4);
  /* �g TIMx CCER �H�s�� */
  TIMx->CCER = tmpccer;
}

/**
  * @²�z  �t�m TIMx �q�D 2N ����.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_OCNPolarity: ���w OC2N ����
  *                         �o�ӰѼƥi�H���U�����Ȥ��@:
  *                         TIM_OCNPolarity_High: ��X������ʰ�
  *                         TIM_OCNPolarity_Low:  ��X������ʧC
  * @��^  �S��
  */
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity)
{
  uint16_t tmpccer = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));
  
  tmpccer = TIMx->CCER;
  /* �]�m�δ_�� CC2NP �� */
  tmpccer &= CCER_CC2NP_Reset;
  tmpccer |= (uint16_t)(TIM_OCNPolarity << 4);
  /* �g TIMx CCER �H�s�� */
  TIMx->CCER = tmpccer;
}

/**
  * @²�z  �]�m TIMx �q�D3����.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_OCPolarity: ���w�� OC3 ����
  *                        �o�ӰѼƥi�H���U�����Ȥ��@:
  *                        TIM_OCPolarity_High: ��X������ʰ�
  *                        TIM_OCPolarity_Low:  ��X������ʧC
  * @��^  �S��
  */
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity)
{
  uint16_t tmpccer = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));
  tmpccer = TIMx->CCER;
  /* �]�m�δ_�� CC3P �� */
  tmpccer &= CCER_CC3P_Reset;
  tmpccer |= (uint16_t)(TIM_OCPolarity << 8);
  /* �g TIMx CCER �H�s�� */
  TIMx->CCER = tmpccer;
}

/**
  * @²�z  �t�m TIMx �q�D 3N ����.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_OCNPolarity: ���w OC3N ����
  *                         �o�ӰѼƥi�H���U�����Ȥ��@:
  *                         TIM_OCNPolarity_High: ��X������ʰ�
  *                         TIM_OCNPolarity_Low:  ��X������ʧC
  * @��^  �S��
  */
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity)
{
  uint16_t tmpccer = 0;
 
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));
    
  tmpccer = TIMx->CCER;
  /* �]�m�δ_�� CC3NP �� */
  tmpccer &= CCER_CC3NP_Reset;
  tmpccer |= (uint16_t)(TIM_OCNPolarity << 8);
  /* �g TIMx CCER �H�s�� */
  TIMx->CCER = tmpccer;
}

/**
  * @²�z  �]�m TIMx �q�D4����.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_OCPolarity: ���w�� OC4 ����
  *                        �o�ӰѼƥi�H���U�����Ȥ��@:
  *                        TIM_OCPolarity_High: ��X������ʰ�
  *                        TIM_OCPolarity_Low:  ��X������ʧC
  * @��^  �S��
  */
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity)
{
  uint16_t tmpccer = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));
  tmpccer = TIMx->CCER;
  /* �]�m�δ_�� CC4P �� */
  tmpccer &= CCER_CC4P_Reset;
  tmpccer |= (uint16_t)(TIM_OCPolarity << 12);
  /* �g TIMx CCER �H�s�� */
  TIMx->CCER = tmpccer;
}

/**
  * @²�z  �ϯ�Υ��� TIM �������q�D x.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_Channel: ���w�� TIM �q�D
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_Channel_1: TIM �q�D 1
  *          TIM_Channel_2: TIM �q�D 2
  *          TIM_Channel_3: TIM �q�D 3
  *          TIM_Channel_4: TIM �q�D 4
  * @�Ѽ�  TIM_CCx: ���w TIM �q�D CCxE �쪺�s���A.
  *                 �o�ӰѼƥi�H�O: TIM_CCx_Enable �� TIM_CCx_Disable. 
  * @��^  �S��
  */
void TIM_CCxCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCx)
{
  uint16_t tmp = 0;

  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_CHANNEL(TIM_Channel));
  assert_param(IS_TIM_CCX(TIM_CCx));

  tmp = CCER_CCE_Set << TIM_Channel;

  /* �_�� CCxE �� */
  TIMx->CCER &= (uint16_t)~ tmp;

  /* �]�m�δ_�� CCxE �� */ 
  TIMx->CCER |=  (uint16_t)(TIM_CCx << TIM_Channel);
}

/**
  * @²�z  �ϯ�Υ��� TIM �������q�D xN.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1��8�H��ܥ~�].
  * @�Ѽ�  TIM_Channel: ���w TIM �q�D
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_Channel_1: TIM �q�D 1
  *          TIM_Channel_2: TIM �q�D 2
  *          TIM_Channel_3: TIM �q�D 3
  * @�Ѽ�  TIM_CCxN: ���w TIM �q�D CCxNE �쪺�s���A.
  *                  �o�ӰѼƥi�H�O: TIM_CCxN_Enable �� TIM_CCxN_Disable. 
  * @��^  �S��
  */
void TIM_CCxNCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCxN)
{
  uint16_t tmp = 0;

  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_TIM_COMPLEMENTARY_CHANNEL(TIM_Channel));
  assert_param(IS_TIM_CCXN(TIM_CCxN));

  tmp = CCER_CCNE_Set << TIM_Channel;

  /* �_�� CCxNE �� */
  TIMx->CCER &= (uint16_t) ~tmp;

  /* �]�m�δ_�� CCxNE �� */ 
  TIMx->CCER |=  (uint16_t)(TIM_CCxN << TIM_Channel);
}

/**
  * @²�z  ��� TIM ��X����Ҧ�.
  * @����   �b���ܿ�X����Ҧ����e�A�Ө�ƥ����ܪ��q�D.
  *         �Τ�ݭn�ϥ� TIM1_CCxCmd �M TIM1_CCxNCmd ��ƨϯ�q�D.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_Channel: ���w�� TIM �q�D
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_Channel_1: TIM �q�D 1
  *          TIM_Channel_2: TIM �q�D 2
  *          TIM_Channel_3: TIM �q�D 3
  *          TIM_Channel_4: TIM �q�D 4
  * @�Ѽ�  TIM_OCMode: ���w TIM ��X����Ҧ�.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_OCMode_Timing
  *          TIM_OCMode_Active
  *          TIM_OCMode_Toggle
  *          TIM_OCMode_PWM1
  *          TIM_OCMode_PWM2
  *          TIM_ForcedAction_Active
  *          TIM_ForcedAction_InActive
  * @��^  �S��
  */
void TIM_SelectOCxM(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_OCMode)
{
  uint32_t tmp = 0;
  uint16_t tmp1 = 0;

  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_CHANNEL(TIM_Channel));
  assert_param(IS_TIM_OCM(TIM_OCMode));

  tmp = (uint32_t) TIMx;
  tmp += CCMR_Offset;

  tmp1 = CCER_CCE_Set << (uint16_t)TIM_Channel;

  /* ����q�D: �_�� CCxE �� */
  TIMx->CCER &= (uint16_t) ~tmp1;

  if((TIM_Channel == TIM_Channel_1) ||(TIM_Channel == TIM_Channel_3))
  {
    tmp += (TIM_Channel>>1);

    /* �_�� OCxM ��A�b CCMRx �H�s���� */
    *(__IO uint32_t *) tmp &= CCMR_OC13M_Mask;
   
    /* �t�m OCxM ��A�b CCMRx �H�s���� */
    *(__IO uint32_t *) tmp |= TIM_OCMode;
  }
  else
  {
    tmp += (uint16_t)(TIM_Channel - (uint16_t)4)>> (uint16_t)1;

    /* �_�� OCxM ��A�b CCMRx �H�s���� */
    *(__IO uint32_t *) tmp &= CCMR_OC24M_Mask;
    
    /* �t�m OCxM ��A�b CCMRx �H�s���� */
    *(__IO uint32_t *) tmp |= (uint16_t)(TIM_OCMode << 8);
  }
}

/**
  * @²�z  �ϯ�Ϊ̥��� TIM ��s�ƥ�.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1��8�H��ܥ~�].
  * @�Ѽ�  NewState: TIM1_CR1�H�s��UDIS�쪺�s���A
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void TIM_UpdateDisableConfig(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �]�m��s����� */
    TIMx->CR1 |= CR1_UDIS_Set;
  }
  else
  {
    /* �_���s����� */
    TIMx->CR1 &= CR1_UDIS_Reset;
  }
}

/**
  * @²�z  �t�m TIMx ��s�ШD��.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1��8�H��ܥ~�].
  * @�Ѽ�  TIM_UpdateSource: ���w��s�ӷ�.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_UpdateSource_Regular: �ͦ����ƪ��߽ġG�b��s�ƥ�ɭp�ƾ�������.
  *          TIM_UpdateSource_Global:  �ͦ���@���߽ġG�p�ƾ��b�U�@�ӧ�s�ƥ󰱤�.
  * @��^  �S��
  */
void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, uint16_t TIM_UpdateSource)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_UPDATE_SOURCE(TIM_UpdateSource));
  if (TIM_UpdateSource != TIM_UpdateSource_Global)
  {
    /* �]�m URS �� */
    TIMx->CR1 |= CR1_URS_Set;
  }
  else
  {
    /* �_�� URS �� */
    TIMx->CR1 &= CR1_URS_Reset;
  }
}

/**
  * @²�z  �ϯ�Ϊ̥��� TIM �N���ǷP�����f.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  NewState: �N���P�������s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �]�m TI1S �� */
    TIMx->CR2 |= CR2_TI1S_Set;
  }
  else
  {
    /* �_�� TI1S �� */
    TIMx->CR2 &= CR2_TI1S_Reset;
  }
}

/**
  * @²�z  �]�m TIM ��߽ļҦ�.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1��8�H��ܥ~�].
  * @�Ѽ�  TIM_OPMode: ���w OPM �Ҧ�.
  *                    �o�ӰѼƥi�H���U�����Ȥ��@:
  *                    TIM_OPMode_Single
  *                    TIM_OPMode_Repetitive
  * @��^  �S��
  */
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, uint16_t TIM_OPMode)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_OPM_MODE(TIM_OPMode));
  /* �_�� OPM �� */
  TIMx->CR1 &= CR1_OPM_Reset;
  /* �t�m OPM �Ҧ� */
  TIMx->CR1 |= TIM_OPMode;
}

/**
  * @²�z  ��� TIM Ĳ�o��X�Ҧ�.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1��8�H��ܥ~�].
  * @�Ѽ�  TIM_TRGOSource: ���w��Ĳ�o��X�Ҧ�.
  *                        �o�ӰѼƥi�H�O�U������:
  *
  *  - ���Ҧ��� TIMx
  *          TIM_TRGOSource_Reset:  �ϥαH�s��TIM1_EGR��UG��@��Ĳ�o��X (TRGO).
  *          TIM_TRGOSource_Enable: �ϥέp�ƾ��ϯ�CEN�@��Ĳ�o��X (TRGO).
  *          TIM_TRGOSource_Update: �ϥΧ�s�ƥ�@��Ĳ�o��X (TRGO).
  *
  *  - ���Ҧ��� TIMx ���F TIM6 �M TIM7
  *          TIM_TRGOSource_OC1:    �@������Ϊ̤���ǰt�o�͡A��лx��CC1F�Q�]�m��Ĳ�o��X�o�e�@�Ӫ֩w�߽� (TRGO).
  *          TIM_TRGOSource_OC1Ref: �ϥ� OC1REF �@��Ĳ�o��X (TRGO).
  *          TIM_TRGOSource_OC2Ref: �ϥ� OC2REF �@��Ĳ�o��X (TRGO).
  *          TIM_TRGOSource_OC3Ref: �ϥ� OC3REF �@��Ĳ�o��X (TRGO).
  *          TIM_TRGOSource_OC4Ref: �ϥ� OC4REF �@��Ĳ�o��X (TRGO).
  *
  * @��^  �S��
  */
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_TRGOSource)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_TRGO_SOURCE(TIM_TRGOSource));
  /* �_�� MMS �� */
  TIMx->CR2 &= CR2_MMS_Mask;
  /* ��� TRGO ���ӷ� */
  TIMx->CR2 |=  TIM_TRGOSource;
}

/**
  * @²�z  ��� TIMx �q�Ҧ�.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_SlaveMode: ���w�w�ɾ��q�Ҧ�.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_SlaveMode_Reset:     �襤Ĳ�o�H�� (TRGI) ���W�ɪu����l�ƭp�ƾ���Ĳ�o�H�s������s.
  *          TIM_SlaveMode_Gated:     ��Ĳ�o�H�� (TRGI) �����q���p�ƾ������ϯ�.
  *          TIM_SlaveMode_Trigger:   �p�ƾ��bĲ�o (TRGI) ���W�ɪu�}�l.
  *          TIM_SlaveMode_External1: �襤Ĳ�o (TRGI) ���W�ɪu�@���p�ƾ�����.
  * @��^  �S��
  */
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_SlaveMode)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_SLAVE_MODE(TIM_SlaveMode));
  /* �_�� SMS �� */
  TIMx->SMCR &= SMCR_SMS_Mask;
  /* ��ܱq�Ҧ� */
  TIMx->SMCR |= TIM_SlaveMode;
}

/**
  * @²�z  �]�m�δ_�� TIMx �D/�q�Ҧ�.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_MasterSlaveMode: �w�ɾ��D/�q�Ҧ�.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_MasterSlaveMode_Enable:  �D/�q�Ҧ��ϯ�.
  *          TIM_MasterSlaveMode_Disable: �D/�q�Ҧ�����
  * @��^  �S��
  */
void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_MasterSlaveMode)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_MSM_STATE(TIM_MasterSlaveMode));
  /* �_�� MSM �� */
  TIMx->SMCR &= SMCR_MSM_Reset;
  
  /* �]�m�δ_�� MSM �� */
  TIMx->SMCR |= TIM_MasterSlaveMode;
}

/**
  * @²�z  �]�m TIMx �p�ƱH�s������
  * @�Ѽ�  TIMx: ���Bx�i�H�O1��8�H��ܥ~�].
  * @�Ѽ�  Counter: ���w�p�ƱH�s�����s��.
  * @��^  �S��
  */
void TIM_SetCounter(TIM_TypeDef* TIMx, uint16_t Counter)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  /* �]�m�p�ƱH�s������ */
  TIMx->CNT = Counter;
}

/**
  * @²�z  �]�m TIMx �۰ʭ��˸��H�s����
  * @�Ѽ�  TIMx: ���Bx�i�H�O1��8�H��ܥ~�].
  * @�Ѽ�  Autoreload: ���w�۰ʭ��˸��H�s���s��.
  * @��^  �S��
  */
void TIM_SetAutoreload(TIM_TypeDef* TIMx, uint16_t Autoreload)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  /* �]�m�۰ʭ��˸��H�s���� */
  TIMx->ARR = Autoreload;
}

/**
  * @²�z  �]�m TIMx ������1�H�s����
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  Compare1: ������1�H�s���s��.
  * @��^  �S��
  */
void TIM_SetCompare1(TIM_TypeDef* TIMx, uint16_t Compare1)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  /* �]�m������1�H�s���� */
  TIMx->CCR1 = Compare1;
}

/**
  * @²�z  �]�m TIMx ������2�H�s����
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  Compare2: ������2�H�s���s��.
  * @��^  �S��
  */
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint16_t Compare2)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  /* �]�m������2�H�s���� */
  TIMx->CCR2 = Compare2;
}

/**
  * @²�z  �]�m TIMx ������3�H�s����
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  Compare3: ������3�H�s���s��.
  * @��^  �S��
  */
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint16_t Compare3)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  /* �]�m������3�H�s���� */
  TIMx->CCR3 = Compare3;
}

/**
  * @²�z  �]�m TIMx ������4�H�s����
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  Compare4: ������4�H�s���s��.
  * @��^  �S��
  */
void TIM_SetCompare4(TIM_TypeDef* TIMx, uint16_t Compare4)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  /* �]�m������4�H�s���� */
  TIMx->CCR4 = Compare4;
}

/**
  * @²�z  �]�m TIMx ��J����1�w���W.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_ICPSC: ��J����1�w���W���s��.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_ICPSC_DIV1: �S���w���W��
  *          TIM_ICPSC_DIV2: �C2���ƥ�TIM�������@��
  *          TIM_ICPSC_DIV4: �C4���ƥ�TIM�������@��
  *          TIM_ICPSC_DIV8: �C8���ƥ�TIM�������@��
  * @��^  �S��
  */
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));
  /* �_�� IC1PSC �� */
  TIMx->CCMR1 &= CCMR_IC13PSC_Mask;
  /* �]�m IC1PSC ���� */
  TIMx->CCMR1 |= TIM_ICPSC;
}

/**
  * @²�z  �]�m TIMx ��J����2�w���W.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_ICPSC: ��J����2�w���W���s��.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_ICPSC_DIV1: �S���w���W��
  *          TIM_ICPSC_DIV2: �C2���ƥ�TIM�������@��
  *          TIM_ICPSC_DIV4: �C4���ƥ�TIM�������@��
  *          TIM_ICPSC_DIV8: �C8���ƥ�TIM�������@��
  * @��^  �S��
  */
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));
  /* �_�� IC2PSC �� */
  TIMx->CCMR1 &= CCMR_IC24PSC_Mask;
  /* �]�m IC2PSC ���� */
  TIMx->CCMR1 |= (uint16_t)(TIM_ICPSC << 8);
}

/**
  * @²�z  �]�m TIMx ��J����3�w���W.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_ICPSC: ��J����3�w���W���s��.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_ICPSC_DIV1: �S���w���W��
  *          TIM_ICPSC_DIV2: �C2���ƥ�TIM�������@��
  *          TIM_ICPSC_DIV4: �C4���ƥ�TIM�������@��
  *          TIM_ICPSC_DIV8: �C8���ƥ�TIM�������@��
  * @��^  �S��
  */
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));
  /* �_�� IC3PSC �� */
  TIMx->CCMR2 &= CCMR_IC13PSC_Mask;
  /* �]�m IC3PSC ���� */
  TIMx->CCMR2 |= TIM_ICPSC;
}

/**
  * @²�z  �]�m TIMx ��J����4�w���W.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_ICPSC: ��J����4�w���W���s��.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_ICPSC_DIV1: �S���w���W��
  *          TIM_ICPSC_DIV2: �C2���ƥ�TIM�������@��
  *          TIM_ICPSC_DIV4: �C4���ƥ�TIM�������@��
  *          TIM_ICPSC_DIV8: �C8���ƥ�TIM�������@��
  * @��^  �S��
  */
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC)
{  
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));
  /* �_�� IC4PSC �� */
  TIMx->CCMR2 &= CCMR_IC24PSC_Mask;
  /* �]�m IC4PSC ���� */
  TIMx->CCMR2 |= (uint16_t)(TIM_ICPSC << 8);
}

/**
  * @²�z  �]�m TIMx ���������έ�.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_CKD: �������έ�.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_CKD_DIV1: TDTS = Tck_tim
  *          TIM_CKD_DIV2: TDTS = 2*Tck_tim
  *          TIM_CKD_DIV4: TDTS = 4*Tck_tim
  * @��^  �S��
  */
void TIM_SetClockDivision(TIM_TypeDef* TIMx, uint16_t TIM_CKD)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_CKD_DIV(TIM_CKD));
  /* �_�� CKD �� */
  TIMx->CR1 &= CR1_CKD_Mask;
  /* �]�m CKD ���� */
  TIMx->CR1 |= TIM_CKD;
}

/**
  * @²�z  ��o TIMx ��J����1����.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @��^  ��o��J����1����.
  */
uint16_t TIM_GetCapture1(TIM_TypeDef* TIMx)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  /* ��o��J����1���� */
  return TIMx->CCR1;
}

/**
  * @²�z  ��o TIMx ��J����2����.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @��^  ��o��J����2����.
  */
uint16_t TIM_GetCapture2(TIM_TypeDef* TIMx)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  /* ��o��J����2���� */
  return TIMx->CCR2;
}

/**
  * @²�z  ��o TIMx ��J����3����.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @��^  ��o��J����3����.
  */
uint16_t TIM_GetCapture3(TIM_TypeDef* TIMx)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx)); 
  /* ��o��J����3���� */
  return TIMx->CCR3;
}

/**
  * @²�z  ��o TIMx ��J����4����.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @��^  ��o��J����4����.
  */
uint16_t TIM_GetCapture4(TIM_TypeDef* TIMx)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  /* ��o��J����4���� */
  return TIMx->CCR4;
}

/**
  * @²�z  ��o TIMx �p�ƾ�����.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1��8�H��ܥ~�].
  * @��^  �p�ƾ�����.
  */
uint16_t TIM_GetCounter(TIM_TypeDef* TIMx)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  /* ��o�p�ƾ����� */
  return TIMx->CNT;
}

/**
  * @²�z  ��o TIMx �w���W��.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1��8�H��ܥ~�].
  * @��^  �w���W����.
  */
uint16_t TIM_GetPrescaler(TIM_TypeDef* TIMx)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  /* ��o�w���W���� */
  return TIMx->PSC;
}

/**
  * @²�z  �ˬd���w�� TIM �лx��]�m�P�_.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1��8�H��ܥ~�].
  * @�Ѽ�  TIM_FLAG: ���ˬd�� TIM �лx��.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_FLAG_Update: TIM ��s�лx
  *          TIM_FLAG_CC1: TIM ����/��� 1 �лx��
  *          TIM_FLAG_CC2: TIM ����/��� 2 �лx��
  *          TIM_FLAG_CC3: TIM ����/��� 3 �лx��
  *          TIM_FLAG_CC4: TIM ����/��� 4 �лx��
  *          TIM_FLAG_COM: TIM Com�лx
  *          TIM_FLAG_Trigger: TIM Ĳ�o�лx��
  *          TIM_FLAG_Break: TIM �𮧼лx
  *          TIM_FLAG_CC1OF: TIM ����/��� 1 ���X�лx��
  *          TIM_FLAG_CC2OF: TIM ����/��� 2 ���X�лx��
  *          TIM_FLAG_CC3OF: TIM ����/��� 3 ���X�лx��
  *          TIM_FLAG_CC4OF: TIM ����/��� 4 ���X�лx��
  * @����
  *   - TIM6 �M TIM7 �ȶȦ��@�ӧ�s���_. 
  *   - TIM_FLAG_COM �M TIM_FLAG_Break �ȶȥi�H�M TIM1 �M TIM8 �@�_�ϥ�.    
  * @��^  TIM_FLAG ���s���A(SET �� RESET).
  */
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, uint16_t TIM_FLAG)
{ 
  ITStatus bitstatus = RESET;  
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_GET_FLAG(TIM_FLAG));
  
  if ((TIMx->SR & TIM_FLAG) != (uint16_t)RESET)
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
  * @²�z  �M�� TIMx ���ݳB�z�лx��.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1��8�H��ܥ~�].
  * @�Ѽ�  TIM_FLAG: �Ω�M�����аO.
  *          �o�ӰѼƥi�H�O�U���Ȫ����N�զX:
  *          TIM_FLAG_Update: TIM ��s�лx
  *          TIM_FLAG_CC1: TIM ����/��� 1 �лx��
  *          TIM_FLAG_CC2: TIM ����/��� 2 �лx��
  *          TIM_FLAG_CC3: TIM ����/��� 3 �лx��
  *          TIM_FLAG_CC4: TIM ����/��� 4 �лx��
  *          TIM_FLAG_COM: TIM Com�лx
  *          TIM_FLAG_Trigger: TIM Ĳ�o�лx��
  *          TIM_FLAG_Break: TIM ���_�лx
  *          TIM_FLAG_CC1OF: TIM ����/��� 1 ���X�лx��
  *          TIM_FLAG_CC2OF: TIM ����/��� 2 ���X�лx��
  *          TIM_FLAG_CC3OF: TIM ����/��� 3 ���X�лx��
  *          TIM_FLAG_CC4OF: TIM ����/��� 4 ���X�лx��
  * @����
  *   - TIM6 �M TIM7 �ȶȦ��@�ӧ�s���_. 
  *   - TIM_FLAG_COM �M TIM_FLAG_Break �ȶȥi�H�M TIM1 �M TIM8 �@�_�ϥ�.    
  * @��^  �S��.
  */
void TIM_ClearFlag(TIM_TypeDef* TIMx, uint16_t TIM_FLAG)
{  
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_CLEAR_FLAG(TIM_FLAG));
   
  /* �M���лx�� */
  TIMx->SR = (uint16_t)~TIM_FLAG;
}

/**
  * @²�z  �ˬd���w�� TIM ���_�o�ͻP�_.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1��8�H��ܥ~�].
  * @�Ѽ�  TIM_IT: ���ˬd�� TIM ���_��.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_IT_Update: TIM ��s���_��
  *          TIM_IT_CC1: TIM ����/��� 1 ���_��
  *          TIM_IT_CC2: TIM ����/��� 2 ���_��
  *          TIM_IT_CC3: TIM ����/��� 3 ���_��
  *          TIM_IT_CC4: TIM ����/��� 4 ���_��
  *          TIM_IT_COM: TIM Com ���_��
  *          TIM_IT_Trigger: TIM Ĳ�o���_��
  *          TIM_IT_Break: TIM �𮧤��_��
  * @����
  *   - TIM6 �M TIM7 �ȶȦ��@�ӧ�s���_. 
  *   - TIM_FLAG_COM �M TIM_FLAG_Break �ȶȥi�H�M TIM1 �M TIM8 �@�_�ϥ�.   
  * @��^  TIM_IT ���s���A(SET �� RESET).
  */
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint16_t TIM_IT)
{
  ITStatus bitstatus = RESET;  
  uint16_t itstatus = 0x0, itenable = 0x0;
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_GET_IT(TIM_IT));
   
  itstatus = TIMx->SR & TIM_IT;
  
  itenable = TIMx->DIER & TIM_IT;
  if ((itstatus != (uint16_t)RESET) && (itenable != (uint16_t)RESET))
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
  * @²�z  �M�� TIMx �����_�ݳB�z��.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1��8�H��ܥ~�].
  * @�Ѽ�  TIM_IT: ���w���_�ݳB�z��.
  *          �o�ӰѼƥi�H�O�U���Ȫ����N�զX:
  *          TIM_IT_Update: TIM ��s���_��
  *          TIM_IT_CC1: TIM ����/��� 1 ���_��
  *          TIM_IT_CC2: TIM ����/��� 2 ���_��
  *          TIM_IT_CC3: TIM ����/��� 3 ���_��
  *          TIM_IT_CC4: TIM ����/��� 4 ���_��
  *          TIM_IT_COM: TIM Com ���_��
  *          TIM_IT_Trigger: TIM Ĳ�o���_��
  *          TIM_IT_Break: TIM �𮧤��_��
  * @����
  *   - TIM6 �M TIM7 �ȶȦ��@�ӧ�s���_. 
  *   - TIM_FLAG_COM �M TIM_FLAG_Break �ȶȥi�H�M TIM1 �M TIM8 �@�_�ϥ�.  
  * @��^  �S��
  */
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_IT(TIM_IT));
  /* �M�� TIMx �����_�ݳB�z�� */
  TIMx->SR = (uint16_t)~TIM_IT;
}

/**
  * @²�z  �t�m TI1 �@����J.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_ICPolarity : ��J����.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_ICPolarity_Rising
  *          TIM_ICPolarity_Falling
  * @�Ѽ�  TIM_ICSelection: �ϥΫ��w����J.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_ICSelection_DirectTI:   ���TIM ��J1�s��IC1.
  *          TIM_ICSelection_IndirectTI: ���TIM ��J1�s��IC2.
  *          TIM_ICSelection_TRC:        ���TIM ��J1�s��TRC.
  * @�Ѽ�  TIM_ICFilter: ���w����J�����o�i��.
  *                      �o�ӰѼƪ��ȥ����b 0x00 �M 0x0F����.
  * @��^  �S��
  */
static void TI1_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter)
{
  uint16_t tmpccmr1 = 0, tmpccer = 0;
  /* ����q�D 1: �_�� CC1E �� */
  TIMx->CCER &= CCER_CC1E_Reset;
  tmpccmr1 = TIMx->CCMR1;
  tmpccer = TIMx->CCER;
  /* ��ܿ�J�M�o�i�� */
  tmpccmr1 &= CCMR_CC13S_Mask & CCMR_IC13F_Mask;
  tmpccmr1 |= (uint16_t)(TIM_ICSelection | (uint16_t)(TIM_ICFilter << (uint16_t)4));
  /* ��ܷ��ʩM�m��CC1E */
  tmpccer &= CCER_CC1P_Reset;
  tmpccer |= (uint16_t)(TIM_ICPolarity | (uint16_t)CCER_CC1E_Set);
  /* �gTIMx CCMR1�MCCER�H�s�� */
  TIMx->CCMR1 = tmpccmr1;
  TIMx->CCER = tmpccer;
}

/**
  * @²�z  �t�m TI2 �@����J.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_ICPolarity : ��J����.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_ICPolarity_Rising
  *          TIM_ICPolarity_Falling
  * @�Ѽ�  TIM_ICSelection: �ϥΫ��w����J.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_ICSelection_DirectTI:   ���TIM ��J2�s��IC2.
  *          TIM_ICSelection_IndirectTI: ���TIM ��J2�s��IC1.
  *          TIM_ICSelection_TRC:        ���TIM ��J2�s��TRC.
  * @�Ѽ�  TIM_ICFilter: ���w����J�����o�i��.
  *                      �o�ӰѼƪ��ȥ����b 0x00 �M 0x0F����.
  * @��^  �S��
  */
static void TI2_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter)
{
  uint16_t tmpccmr1 = 0, tmpccer = 0, tmp = 0;
  /* ����q�D 2: �_�� CC2E �� */
  TIMx->CCER &= CCER_CC2E_Reset;
  tmpccmr1 = TIMx->CCMR1;
  tmpccer = TIMx->CCER;
  tmp = (uint16_t)(TIM_ICPolarity << 4);
  /* ��ܿ�J�M�o�i�� */
  tmpccmr1 &= CCMR_CC24S_Mask & CCMR_IC24F_Mask;
  tmpccmr1 |= (uint16_t)(TIM_ICFilter << 12);
  tmpccmr1 |= (uint16_t)(TIM_ICSelection << 8);
  /* ��ܷ��ʩM�m��CC2E */
  tmpccer &= CCER_CC2P_Reset;
  tmpccer |=  (uint16_t)(tmp | (uint16_t)CCER_CC2E_Set);
  /* �gTIMx CCMR1�MCCER�H�s�� */
  TIMx->CCMR1 = tmpccmr1 ;
  TIMx->CCER = tmpccer;
}

/**
  * @²�z  �t�m TI3 �@����J.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_ICPolarity : ��J����.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_ICPolarity_Rising
  *          TIM_ICPolarity_Falling
  * @�Ѽ�  TIM_ICSelection: �ϥΫ��w����J.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_ICSelection_DirectTI:   ���TIM ��J3�s��IC3.
  *          TIM_ICSelection_IndirectTI: ���TIM ��J3�s��IC4.
  *          TIM_ICSelection_TRC:        ���TIM ��J3�s��TRC.
  * @�Ѽ�  TIM_ICFilter: ���w����J�����o�i��.
  *                      �o�ӰѼƪ��ȥ����b 0x00 �M 0x0F����.
  * @��^  �S��
  */
static void TI3_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter)
{
  uint16_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;
  /* ����q�D 3: �_�� CC3E �� */
  TIMx->CCER &= CCER_CC3E_Reset;
  tmpccmr2 = TIMx->CCMR2;
  tmpccer = TIMx->CCER;
  tmp = (uint16_t)(TIM_ICPolarity << 8);
  /* ��ܿ�J�M�o�i�� */
  tmpccmr2 &= CCMR_CC13S_Mask & CCMR_IC13F_Mask;
  tmpccmr2 |= (uint16_t)(TIM_ICSelection | (uint16_t)(TIM_ICFilter << (uint16_t)4));
  /* ��ܷ��ʩM�m��CC3E */
  tmpccer &= CCER_CC3P_Reset;
  tmpccer |= (uint16_t)(tmp | (uint16_t)CCER_CC3E_Set);
  /* �gTIMx CCMR2�MCCER�H�s�� */
  TIMx->CCMR2 = tmpccmr2;
  TIMx->CCER = tmpccer;
}

/**
  * @²�z  �t�m TI4 �@����J.
  * @�Ѽ�  TIMx: ���Bx�i�H�O1,2,3,4,5��8�H��ܥ~�].
  * @�Ѽ�  TIM_ICPolarity : ��J����.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_ICPolarity_Rising
  *          TIM_ICPolarity_Falling
  * @�Ѽ�  TIM_ICSelection: �ϥΫ��w����J.
  *          �o�ӰѼƥi�H���U�����Ȥ��@:
  *          TIM_ICSelection_DirectTI:   ���TIM ��J3�s��IC4.
  *          TIM_ICSelection_IndirectTI: ���TIM ��J3�s��IC3.
  *          TIM_ICSelection_TRC:        ���TIM ��J3�s��TRC.
  * @�Ѽ�  TIM_ICFilter: ���w����J�����o�i��.
  *                      �o�ӰѼƪ��ȥ����b 0x00 �M 0x0F����.
  * @��^  �S��
  */
static void TI4_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter)
{
  uint16_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;

  /* ����q�D 4: �_�� CC4E �� */
  TIMx->CCER &= CCER_CC4E_Reset;
  tmpccmr2 = TIMx->CCMR2;
  tmpccer = TIMx->CCER;
  tmp = (uint16_t)(TIM_ICPolarity << 12);

  /* ��ܿ�J�M�]�m�L�o�� */
  tmpccmr2 &= CCMR_CC24S_Mask & CCMR_IC24F_Mask;
  tmpccmr2 |= (uint16_t)(TIM_ICSelection << 8);
  tmpccmr2 |= (uint16_t)(TIM_ICFilter << 12);

  /* ��ܷ��ʩM�m��CC4E */
  tmpccer &= CCER_CC4P_Reset;
  tmpccer |= (uint16_t)(tmp | (uint16_t)CCER_CC4E_Set);
  /* �gTIMx CCMR2�MCCER�H�s�� */
  TIMx->CCMR2 = tmpccmr2;
  TIMx->CCER = tmpccer ;
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
