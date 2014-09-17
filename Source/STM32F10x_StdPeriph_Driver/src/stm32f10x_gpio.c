/**
  ******************************************************************************
  * @���    stm32f10x_gpio.c
  * @�@��    MCD ���ε{�ǲ�
  * @����    V3.1.0
  * @���    06/19/2009
  * @²�z    �o�Ӥ�� ���ѩҦ� GPIO �T����.
  * @½Ķ    ANSON/sweet1985 Email:airanson110@126.com
  * @���    02/07/2009
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
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

/* �ۥ����� -----------------------------------------------------------*/
/* �ۥΩw�q ------------------------------------------------------------*/

/* ------------ RCC registers bit address in the alias region ----------------*/
#define AFIO_OFFSET                 (AFIO_BASE - PERIPH_BASE)

/* --- EVENTCR Register -----*/

/* Alias word address of EVOE bit */
#define EVCR_OFFSET                 (AFIO_OFFSET + 0x00)
#define EVOE_BitNumber              ((uint8_t)0x07)
#define EVCR_EVOE_BB                (PERIPH_BB_BASE + (EVCR_OFFSET * 32) + (EVOE_BitNumber * 4))


/* ---  MAPR Register ---*/ 
/* Alias word address of MII_RMII_SEL bit */ 
#define MAPR_OFFSET                 (AFIO_OFFSET + 0x04) 
#define MII_RMII_SEL_BitNumber      ((u8)0x17) 
#define MAPR_MII_RMII_SEL_BB        (PERIPH_BB_BASE + (MAPR_OFFSET * 32) + (MII_RMII_SEL_BitNumber * 4))


#define EVCR_PORTPINCONFIG_MASK     ((uint16_t)0xFF80)
#define LSB_MASK                    ((uint16_t)0xFFFF)
#define DBGAFR_POSITION_MASK        ((uint32_t)0x000F0000)
#define DBGAFR_SWJCFG_MASK          ((uint32_t)0xF0FFFFFF)
#define DBGAFR_LOCATION_MASK        ((uint32_t)0x00200000)
#define DBGAFR_NUMBITS_MASK         ((uint32_t)0x00100000)

/* �ۥΧ� -------------------------------------------------------------*/
/* �ۥ��ܶq ---------------------------------------------------------*/
/* �ۥΨ�ƭ쫬 -----------------------------------------------*/
/* �ۥΨ�� ---------------------------------------------------------*/

/**
  * @²�z   �NGPIO���󪺱H�s���_�쬰�q�{��
  * @�Ѽ�   GPIOx�Gx�i��A��G�ӿ�ܯS�w��GPIO�]��
  * @��^   �S��
  */
void GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
  /* �ˬd�ֹ�Ѽ�*/
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  
  if (GPIOx == GPIOA)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA, DISABLE);
  }
  else if (GPIOx == GPIOB)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOB, DISABLE);
  }
  else if (GPIOx == GPIOC)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOC, DISABLE);
  }
  else if (GPIOx == GPIOD)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOD, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOD, DISABLE);
  }    
  else if (GPIOx == GPIOE)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOE, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOE, DISABLE);
  } 
  else if (GPIOx == GPIOF)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOF, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOF, DISABLE);
  }
  else
  {
    if (GPIOx == GPIOG)
    {
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOG, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOG, DISABLE);
    }
  }
}

/**
  * @²�z  �N�ƥΥ\��]���M�g�A�ƥ󱱨��EXTI�t�m�^�H�s���_�쬰�q�{��
  * @�Ѽ�  �S��
  * @��^  �S��
  */
void GPIO_AFIODeInit(void)
{
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_AFIO, DISABLE);
}

/**
  * @²�z  ����GPIO_InitStruct(���c��)���S�w�Ѽƪ�l��GPIO����
  * @�Ѽ�  GPIOx�Gx�i��A��G�ӿ�ܯS�w��GPIO�]�ơA
  *        GPIO_InitStruct: ���VGPIO_InitTypeDef���c�����w�A���]�t�S�wGPIO���󪺰t�m�H��.
  * @��^  �S��
  */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
  uint32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
  uint32_t tmpreg = 0x00, pinmask = 0x00;
  /* �ˬd�Ѽ� */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
  assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));  
  
/*---------------------------- GPIO �Ҧ��t�m --------------------------------*/
  currentmode = ((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x0F);
  if ((((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x10)) != 0x00)
  { 
    /* Check the parameters */
    assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));
    /* Output mode */
    currentmode |= (uint32_t)GPIO_InitStruct->GPIO_Speed;
  }
/*-------------------- GPIO CRL(�ݤf����H�s���C�r�`) �t�m -------------------*/
  /* �t�m�C8��ݤf�޸} */
  if (((uint32_t)GPIO_InitStruct->GPIO_Pin & ((uint32_t)0x00FF)) != 0x00)
  {
    tmpreg = GPIOx->CRL;
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = ((uint32_t)0x01) << pinpos;
      /* ���o�ݤf�޸}����m */
      currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
      if (currentpin == pos)
      {
        pos = pinpos << 2;
        /* �M�Ŭ������C�챱��H�s�� */
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        /* �g�������Ҧ��t�m�� */
        tmpreg |= (currentmode << pos);
        /* �_���������X�ƾڱH�s�� (ODR) �� */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          GPIOx->BRR = (((uint32_t)0x01) << pinpos);
        }
        else
        {
          /* �m���������X�ƾڱH�s�� (ODR) �� */
          if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
          {
            GPIOx->BSRR = (((uint32_t)0x01) << pinpos);
          }
        }
      }
    }
    GPIOx->CRL = tmpreg;
  }
/*-------------------- GPIO CRH(�ݤf����H�s�����r�`) �t�m -------------------*/
  /* �t�m��8��ݤf�޸} */
  if (GPIO_InitStruct->GPIO_Pin > 0x00FF)
  {
    tmpreg = GPIOx->CRH;
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = (((uint32_t)0x01) << (pinpos + 0x08));
      /* ���o�ݤf�޸}����m */
      currentpin = ((GPIO_InitStruct->GPIO_Pin) & pos);
      if (currentpin == pos)
      {
        pos = pinpos << 2;
        /* �M�Ŭ������C�챱��H�s�� */
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        /* �g�������Ҧ��t�m�� */
        tmpreg |= (currentmode << pos);
        /* �_���������X�ƾڱH�s�� (ODR) �� */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          GPIOx->BRR = (((uint32_t)0x01) << (pinpos + 0x08));
        }
        /* �m���������X�ƾڱH�s�� (ODR) �� */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
        {
          GPIOx->BSRR = (((uint32_t)0x01) << (pinpos + 0x08));
        }
      }
    }
    GPIOx->CRH = tmpreg;
  }
}

/**
  * @²�z  ��GPIO_InitStruct�����C�@�ӰѼƫ��ʬ٭ȶ�J.
  * @�Ѽ�  GPIO_InitStruct : ���VGPIO_InitTypeDef���c�A�ӵ��c�N�Q��l��
  * @��^  �S��
  */
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
  /* �_��GPIO��l�Ƶ��c�Ѽƭ� */
  GPIO_InitStruct->GPIO_Pin  = GPIO_Pin_All;
  GPIO_InitStruct->GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN_FLOATING;
}

/**
  * @²�z  Ū�����w�ݤf�޸}����J.
  * @�Ѽ�  GPIOx: x�i��A��G�ӿ�ܯS�w��GPIO�]��.
  *        GPIO_Pin:  �QŪ�����޸}��.
  *                   �o�ӰѼ�GPIO_Pin_x�i�H���0��15.
  * @��^  ���w�ݤf�޸}����J��.
  */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;
  
  /* �ˬd�Ѽ� */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin)); 
  
  if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

/**
  * @²�z  �q�S�w��GPIO��J�ƾںݤfŪ��.
  * @�Ѽ�  GPIOx: x�i��A��G�ӿ�ܯS�w��GPIO�]��.
  * @��^  ���w�� GPIO �ݤf�޸}����J��.
  */
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  
  return ((uint16_t)GPIOx->IDR);
}

/**
  * @²�z  Ū�����w�ݤf�޸}����X(��).
  * @�Ѽ�  GPIOx: x�i��A��G�ӿ�ܯS�w��GPIO�]��.
  *        GPIO_Pin: �ݭnŪ�����ݤf��.
  *                  �o�ӰѼ�GPIO_Pin_x�i�H���0��15.
  * @��^  ��X�ݤf����X��.
  */
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;
  /* �ˬd�Ѽ� */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin)); 
  
  if ((GPIOx->ODR & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

/**
  * @²�z  Ū�����w��GPIO�ݤf��X.
  * @�Ѽ�  GPIOx: x�i��A��G�ӿ�ܯS�w��GPIO�]��.
  * @��^  ���w GPIO ��X�ƾںݤf��.
  */
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    
  return ((uint16_t)GPIOx->ODR);
}

/**
  * @²�z  �]�m���w���ƾںݤf��.
  * @�Ѽ�  x�i��A��G�ӿ�ܯS�w��GPIO�]��.
  *        GPIO_Pin: �T�w�ݤf��.
  *                  �ӰѼƥi��GPIO_Pin_x�����N�զX,�䤤x��0��15.
  * @��^  �S��
  */
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  
  GPIOx->BSRR = GPIO_Pin;
}

/**
  * @²�z  �M�����w���ƾںݤf��.
  * @�Ѽ�  x�i��A��G�ӿ�ܯS�w��GPIO�]��.
  *        GPIO_Pin: �T�w�ݤf��.
  *                  �ӰѼƥi��GPIO_Pin_x�����N�զX,�䤤x��0��15.
  * @��^  �S��
  */
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  
  GPIOx->BRR = GPIO_Pin;
}

/**
  * @²�z  �]�m�Ϊ̲M�����w���ƾںݤf��.
  * @�Ѽ�  GPIOx: x�i��A��G�ӿ�ܯS�w��GPIO�]��.
  *        GPIO_Pin: ���w�Q�g�J���ݤf��.
  *                  �ӰѼƥi��GPIO_Pin_x�����N�զX,�䤤x��0��15.
  *        BitVal:   �ӰѼƫ��w�Q�g�J���w��.
  *                  BitVal������BitAction�T�|������: 
  *                  @arg Bit_RESET:�M���ݤf�޸}�A
  *                  @arg Bit_SET:�m��ݤf�޸}
  * @��^  �S��
  */
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_BIT_ACTION(BitVal)); 
  
  if (BitVal != Bit_RESET)
  {
    GPIOx->BSRR = GPIO_Pin;
  }
  else
  {
    GPIOx->BRR = GPIO_Pin;
  }
}

/**
  * @²�z  �V���wGPIO�ƾںݤf�g�J�ƾ�.
  * @�Ѽ�  GPIOx: x�i��A��G�ӿ�ܯS�w��GPIO�]��.
  *        PortVal: �g�J��ƾںݤf�H�s������.
  * @��^  �S��
  */
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  
  GPIOx->ODR = PortVal;
}

/**
  * @²�z  ��wGPIO�޸}�t�m�H�s��.
  * @�Ѽ�  GPIOx: x�i��A��G�ӿ�ܯS�w��GPIO�]��.
  *        GPIO_Pin:���w�Q�g�J���ݤf��.
  *                 �ӰѼƥi��GPIO_Pin_x�����N�զX,�䤤x��0��15.
  * @��^  �S��
  */
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint32_t tmp = 0x00010000;
  
  /* �ˬd�Ѽ� */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  
  tmp |= GPIO_Pin;
  /* Set LCKK bit */
  GPIOx->LCKR = tmp;
  /* Reset LCKK bit */
  GPIOx->LCKR =  GPIO_Pin;
  /* Set LCKK bit */
  GPIOx->LCKR = tmp;
  /* Read LCKK bit*/
  tmp = GPIOx->LCKR;
  /* Read LCKK bit*/
  tmp = GPIOx->LCKR;
}

/**
  * @²�z  ��� GPIO �޸}�Χ@�ƥ��X.
  * @�Ѽ�  GPIO_PortSource: ��ܥΧ@�ƥ��X��GPIO�ݤf
  *                         GPIOx:x�i��A��E�ӿ�ܯS�w��GPIO�]��.
  *        GPIO_PinSource: �ƥ��X���޸}.
  *                        �ӰѼƥi��GPIO_PinSourcex,�o��x�i��0��15.
  * @��^  �S��
  */
void GPIO_EventOutputConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource)
{
  uint32_t tmpreg = 0x00;
  /* �ˬd�Ѽ� */
  assert_param(IS_GPIO_EVENTOUT_PORT_SOURCE(GPIO_PortSource));
  assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));
    
  tmpreg = AFIO->EVCR;
  /* Clear the PORT[6:4] and PIN[3:0] bits */
  tmpreg &= EVCR_PORTPINCONFIG_MASK;
  tmpreg |= (uint32_t)GPIO_PortSource << 0x04;
  tmpreg |= GPIO_PinSource;
  AFIO->EVCR = tmpreg;
}

/**
  * @²�z  �ϯ�Ϊ̥���ƥ��X.
  * @�Ѽ�  NewState: �ƥ��X���s���A.
  *                  �o�ӰѼƥi�H���GENABLE�Ϊ�DISABLE.
  * @��^  �S��
  */
void GPIO_EventOutputCmd(FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  *(__IO uint32_t *) EVCR_EVOE_BB = (uint32_t)NewState;
}

/**
  * @²�z  ���ܫ��w�޸}���M�g.
  * @�Ѽ�  GPIO_Remap: ��ܭ��M�g���޸}.
  *                    GPIO_Remap �Ψӧ��ܳƥΥ\��M�g,�����i�έ�:
  *     @arg GPIO_Remap_SPI1
  *     @arg GPIO_Remap_I2C1
  *     @arg GPIO_Remap_USART1
  *     @arg GPIO_Remap_USART2
  *     @arg GPIO_PartialRemap_USART3
  *     @arg GPIO_FullRemap_USART3
  *     @arg GPIO_PartialRemap_TIM1
  *     @arg GPIO_FullRemap_TIM1
  *     @arg GPIO_PartialRemap1_TIM2
  *     @arg GPIO_PartialRemap2_TIM2
  *     @arg GPIO_FullRemap_TIM2
  *     @arg GPIO_PartialRemap_TIM3
  *     @arg GPIO_FullRemap_TIM3
  *     @arg GPIO_Remap_TIM4
  *     @arg GPIO_Remap1_CAN1
  *     @arg GPIO_Remap2_CAN1
  *     @arg GPIO_Remap_PD01
  *     @arg GPIO_Remap_TIM5CH4_LSI
  *     @arg GPIO_Remap_ADC1_ETRGINJ
  *     @arg GPIO_Remap_ADC1_ETRGREG
  *     @arg GPIO_Remap_ADC2_ETRGINJ
  *     @arg GPIO_Remap_ADC2_ETRGREG
  *     @arg GPIO_Remap_ETH
  *     @arg GPIO_Remap_CAN2  
  *     @arg GPIO_Remap_SWJ_NoJTRST
  *     @arg GPIO_Remap_SWJ_JTAGDisable
  *     @arg GPIO_Remap_SWJ_Disable
  *     @arg GPIO_Remap_SPI3
  *     @arg GPIO_Remap_TIM2ITR1_PTP_SOF
  *     @arg GPIO_Remap_PTP_PPS  
  * @����  �p�G GPIO_Remap_TIM2ITR1_PTP_SOF �Q�E��  TIM2 ITR1 �s����H�Ӻ� PTP ��X
  *        ��_�쪺�ɭ� TIM2 ITR1 �s���� USB OTG SOF ��X.       
  * @�Ѽ�  NewState: �ݤf�޸}���M�g���s���A.
  *                  �ӰѼƥi���GENABLE��DISABLE.
  * @��^  �S��
  */
void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState)
{
  uint32_t tmp = 0x00, tmp1 = 0x00, tmpreg = 0x00, tmpmask = 0x00;

  /* �ˬd�Ѽ� */
  assert_param(IS_GPIO_REMAP(GPIO_Remap));
  assert_param(IS_FUNCTIONAL_STATE(NewState));  
  
  tmpreg = AFIO->MAPR;

  tmpmask = (GPIO_Remap & DBGAFR_POSITION_MASK) >> 0x10;
  tmp = GPIO_Remap & LSB_MASK;

  if ((GPIO_Remap & (DBGAFR_LOCATION_MASK | DBGAFR_NUMBITS_MASK)) == (DBGAFR_LOCATION_MASK | DBGAFR_NUMBITS_MASK))
  {
    tmpreg &= DBGAFR_SWJCFG_MASK;
    AFIO->MAPR &= DBGAFR_SWJCFG_MASK;
  }
  else if ((GPIO_Remap & DBGAFR_NUMBITS_MASK) == DBGAFR_NUMBITS_MASK)
  {
    tmp1 = ((uint32_t)0x03) << tmpmask;
    tmpreg &= ~tmp1;
    tmpreg |= ~DBGAFR_SWJCFG_MASK;
  }
  else
  {
    tmpreg &= ~(tmp << ((GPIO_Remap >> 0x15)*0x10));
    tmpreg |= ~DBGAFR_SWJCFG_MASK;
  }

  if (NewState != DISABLE)
  {
    tmpreg |= (tmp << ((GPIO_Remap >> 0x15)*0x10));
  }

  AFIO->MAPR = tmpreg;
}

/**
  * @²�z  ���GPIO�޸}�@�� EXTI �u.
  * @�Ѽ�  GPIO_PortSource: ��ܱN�n�Χ@ EXTI �u������ GPIO �f.
  *                         GPIOx:x�i��A��G�ӿ�ܯS�w��GPIO�]��.
  *        GPIO_PinSource:  ���w�ݭn�t�m��EXTI�u.
  *                         �o�ӰѼƥi�H�OGPIO_PinSourcex,�䤤x��0��15.
  * @��^  �S��
  */
void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource)
{
  uint32_t tmp = 0x00;
  /* �ˬd�Ѽ� */
  assert_param(IS_GPIO_EXTI_PORT_SOURCE(GPIO_PortSource));
  assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));
  
  tmp = ((uint32_t)0x0F) << (0x04 * (GPIO_PinSource & (uint8_t)0x03));
  AFIO->EXTICR[GPIO_PinSource >> 0x02] &= ~tmp;
  AFIO->EXTICR[GPIO_PinSource >> 0x02] |= (((uint32_t)GPIO_PortSource) << (0x04 * (GPIO_PinSource & (uint8_t)0x03)));
}

/**
  * @²�z  ���w�H�Ӻ����f.
  * @����  ���\��ȾA�Ω�STM32�s���u�t�m.  
  * @�Ѽ�  GPIO_ETH_MediaInterface: ���w���f�Ҧ�.
  *                                 �o�ӰѼƥi�H���:
  *                                 GPIO_ETH_MediaInterface_MII: MII mode    ->�W�߱��f
  *                                 GPIO_ETH_MediaInterface_RMII: RMII mode  ->��²�W�߱��f  
  * @��^  �S��
  */
void GPIO_ETH_MediaInterfaceConfig(uint32_t GPIO_ETH_MediaInterface) 
{ 
  assert_param(IS_GPIO_ETH_MEDIA_INTERFACE(GPIO_ETH_MediaInterface)); 

  /* �t�m MII_RMII ��ܦ� */ 
  *(__IO uint32_t *) MAPR_MII_RMII_SEL_BB = GPIO_ETH_MediaInterface; 
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
