/**
  ******************************************************************************
  * @���    stm32f10x_spi.c
  * @�@��    MCD Application Team
  * @����    V3.1.0
  * @���    06/19/2009
  * @²�z    �o�Ӥ�� ���ѩҦ� SPI �T����.
  * @½Ķ    ANSON/sweet1985 Email:airanson110@126.com
  * @���    25/07/2009
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
#include "stm32f10x_spi.h"
#include "stm32f10x_rcc.h"

/* �ۥ����� --------------------------------------------------------------*/
/* �ۥΩw�q --------------------------------------------------------------*/

/* SPI SPE mask */
#define CR1_SPE_Set          ((uint16_t)0x0040)
#define CR1_SPE_Reset        ((uint16_t)0xFFBF)

/* I2S I2SE mask */
#define I2SCFGR_I2SE_Set     ((uint16_t)0x0400)
#define I2SCFGR_I2SE_Reset   ((uint16_t)0xFBFF)

/* SPI CRCNext mask */
#define CR1_CRCNext_Set      ((uint16_t)0x1000)

/* SPI CRCEN mask */
#define CR1_CRCEN_Set        ((uint16_t)0x2000)
#define CR1_CRCEN_Reset      ((uint16_t)0xDFFF)

/* SPI SSOE mask */
#define CR2_SSOE_Set         ((uint16_t)0x0004)
#define CR2_SSOE_Reset       ((uint16_t)0xFFFB)

/* SPI registers Masks */
#define CR1_CLEAR_Mask       ((uint16_t)0x3040)
#define I2SCFGR_CLEAR_Mask   ((uint16_t)0xF040)

/* SPI or I2S mode selection masks */
#define SPI_Mode_Select      ((uint16_t)0xF7FF)
#define I2S_Mode_Select      ((uint16_t)0x0800) 

/* I2S clock source selection masks */
#define I2S2_CLOCK_SRC       ((u32)(0x00020000))
#define I2S3_CLOCK_SRC       ((u32)(0x00040000))
#define I2S_MUL_MASK         ((u32)(0x0000F000))
#define I2S_DIV_MASK         ((u32)(0x000000F0))

/* �ۥΧ� -------------------------------------------------------------*/
/* �ۥ��ܶq -----------------------------------------------------------*/
/* �ۥΨ�ƭ쫬 -------------------------------------------------------*/
/* �ۥΨ�� -----------------------------------------------------------*/

/**
  * @²�z  �N�~�] SPIx �H�s�����]���ʬ٭� (�]�@�� I2Ss).
  * @�Ѽ�  SPIx: x��1�A2��3�Ω��w SPI �~�].
  * @��^  �S��
  */
void SPI_I2S_DeInit(SPI_TypeDef* SPIx)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  if (SPIx == SPI1)
  {
    /* �ϯ� SPI1 �_�쪬�A */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, ENABLE);
    /* ���� SPI1 �q�_�쪬�A */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, DISABLE);
  }
  else if (SPIx == SPI2)
  {
    /* �ϯ� SPI2 �_�쪬�A */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, ENABLE);
    /* ���� SPI2 �q�_�쪬�A */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, DISABLE);
  }
  else
  {
    if (SPIx == SPI3)
    {
      /* �ϯ� SPI3 �_�쪬�A */
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, ENABLE);
      /* ���� SPI3 �q�_�쪬�A */
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, DISABLE);
    }
  }
}

/**
  * @²�z  �ھ� SPI_InitStruct �����w���Ѽƪ�l�ƥ~�] SPIx �H�s��.
  * @�Ѽ�  SPIx: x ��1�A2��3�Ω��w SPI �~�].
  * @�Ѽ�  SPI_InitStruct: ���V�@�ӥ]�t�S�w SPI �~�]�t�m�H���� SPI_InitTypeDef ���c�骺���w.
  * @��^  �S��
  */
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct)
{
  uint16_t tmpreg = 0;
  
  /* �ˬd�Ѽ� */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));   
  
  /* �ˬd SPI ���Ѽ� */
  assert_param(IS_SPI_DIRECTION_MODE(SPI_InitStruct->SPI_Direction));
  assert_param(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
  assert_param(IS_SPI_DATASIZE(SPI_InitStruct->SPI_DataSize));
  assert_param(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
  assert_param(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
  assert_param(IS_SPI_NSS(SPI_InitStruct->SPI_NSS));
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_InitStruct->SPI_BaudRatePrescaler));
  assert_param(IS_SPI_FIRST_BIT(SPI_InitStruct->SPI_FirstBit));
  assert_param(IS_SPI_CRC_POLYNOMIAL(SPI_InitStruct->SPI_CRCPolynomial));

/*---------------------------- SPIx CR1 �t�m ------------------------*/
  /* �o�� SPIx CR1 ���� */
  tmpreg = SPIx->CR1;
  /* �M�� BIDIMode, BIDIOE, RxONLY, SSM, SSI, LSBFirst, BR, MSTR, CPOL �M CPHA �� */
  tmpreg &= CR1_CLEAR_Mask;
  /* �t�m SPIx: direction(��V), NSS management(NSS�޲z), first transmitted bit(�Ĥ@�ӵo�e��), BaudRate prescaler(�i�S�v�w���W)
     master/salve mode(�D/�q�Ҧ�), CPOL(��������) �M CPHA(�����ۦ�) */
  /* �]�m BIDImode, BIDIOE �M RxONLY ��A���� SPI_Direction ���� */
  /* �]�m SSM, SSI and MSTR ��A���� SPI_Mode �M SPI_NSS ���� */
  /* �]�m LSBFirst ��A���� SPI_FirstBit ���� */
  /* �]�m BR ��A���� SPI_BaudRatePrescaler ���� */
  /* �]�m CPOL ��A���� SPI_CPOL ���� */
  /* �]�m CPHA ��A���� SPI_CPHA ���� */
  tmpreg |= (uint16_t)((uint32_t)SPI_InitStruct->SPI_Direction | SPI_InitStruct->SPI_Mode |
                  SPI_InitStruct->SPI_DataSize | SPI_InitStruct->SPI_CPOL |  
                  SPI_InitStruct->SPI_CPHA | SPI_InitStruct->SPI_NSS |  
                  SPI_InitStruct->SPI_BaudRatePrescaler | SPI_InitStruct->SPI_FirstBit);
  /* �g SPIx CR1 */
  SPIx->CR1 = tmpreg;
  
  /* �E�� SPI �Ҧ� (�_�� I2SMOD ��A�b I2SCFGR �H�s��) */
  SPIx->I2SCFGR &= SPI_Mode_Select;		

/*---------------------------- SPIx CRCPOLY �t�m --------------------*/
  /* �g SPIx CRCPOLY */
  SPIx->CRCPR = SPI_InitStruct->SPI_CRCPolynomial;
}

/**
  * @²�z  �ھ� SPI_InitStruct �����S�w�Ѽƪ�l�� SPIx �~�].
  * @�Ѽ�  SPIx: x��1�A2��3�Ω��wSPI�~�] (�t�m I2S �Ҧ�).
  * @�Ѽ�  I2S_InitStruct: ���V�@�Ӧb�Ҧ� I2S �]�t�S�w SPI �~�]�t�m�H���� SPI_InitTypeDef ���c�骺���w.
  * @����
  *  The function calculates the optimal prescaler needed to obtain the most 
  *  accurate audio frequency (depending on the I2S clock source, the PLL values 
  *  and the product configuration). But in case the prescaler value is greater 
  *  than 511, the default value (0x02) will be configured instead.  *    
  * @��^  �S��
  */
void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct)
{
  uint16_t tmpreg = 0, i2sdiv = 2, i2sodd = 0, packetlength = 1;
  uint32_t tmp = 0;
  RCC_ClocksTypeDef RCC_Clocks;
  uint32_t sourceclock = 0;
  
  /* �ˬd I2S �Ѽ� */
  assert_param(IS_SPI_23_PERIPH(SPIx));
  assert_param(IS_I2S_MODE(I2S_InitStruct->I2S_Mode));
  assert_param(IS_I2S_STANDARD(I2S_InitStruct->I2S_Standard));
  assert_param(IS_I2S_DATA_FORMAT(I2S_InitStruct->I2S_DataFormat));
  assert_param(IS_I2S_MCLK_OUTPUT(I2S_InitStruct->I2S_MCLKOutput));
  assert_param(IS_I2S_AUDIO_FREQ(I2S_InitStruct->I2S_AudioFreq));
  assert_param(IS_I2S_CPOL(I2S_InitStruct->I2S_CPOL));  

/*----------------------- SPIx I2SCFGR & I2SPR �t�m -----------------*/
  /* �M�� I2SMOD, I2SE, I2SCFG, PCMSYNC, I2SSTD, CKPOL, DATLEN �M CHLEN �� */
  SPIx->I2SCFGR &= I2SCFGR_CLEAR_Mask; 
  SPIx->I2SPR = 0x0002;
  
  /* �o�� I2SCFGR �H�s������ */
  tmpreg = SPIx->I2SCFGR;
  
  /* �p�G�q�{�Ȥw�g�g�F�A���s��l�� i2sdiv �M i2sodd */
  if(I2S_InitStruct->I2S_AudioFreq == I2S_AudioFreq_Default)
  {
    i2sodd = (uint16_t)0;
    i2sdiv = (uint16_t)2;   
  }
  /* �p�G�ШD�������W���O�q�{�ȡA�p��w���W */
  else
  {
    /* �ˬd�ժ�(�p��w���W��) */
    if(I2S_InitStruct->I2S_DataFormat == I2S_DataFormat_16b)
    {
      /* �]������16�� */
      packetlength = 1;
    }
    else
    {
      /* �]������32�� */
      packetlength = 2;
    }

    /* ���o I2S �t�ή����W�v */
    if(((uint32_t)SPIx) == SPI2_BASE)
    {
      /* I2S2 */
      tmp = I2S2_CLOCK_SRC;
    }
    else 
    {
      /* I2S3 */      
      tmp = I2S3_CLOCK_SRC;
    }

    /* �ˬd I2S �����߽ķ�: �ȶȬO�q�Ωʳ]�Ʀ� PLL3 VCO ���� */
#ifdef STM32F10X_CL
    if((RCC->CFGR2 & tmp) != 0)
    {
      /* �o�� RCC PLL3 ���W�Ȫ��t�m�� */
      tmp = (uint32_t)((RCC->CFGR2 & I2S_MUL_MASK) >> 12);

      /* �o�� PLL3 ���W������ */      
      if((tmp > 5) && (tmp < 15))
      {
        /* ���W�Ȧb 8 �M 14 ���� (�T�� 15 ) */
        tmp += 2;
      }
      else
      {
        if (tmp == 15)
        {
          /* ���W�ƬO 20 */
          tmp = 20;
        }
      }      
      /* �o�� PREDIV2 ���� */
      sourceclock = (uint32_t)(((RCC->CFGR2 & I2S_DIV_MASK) >> 4) + 1);
      
      /* �p������W�v�A�ھ� PLL3 �M PREDIV2 ���� */
      sourceclock = (uint32_t) ((HSE_Value / sourceclock) * tmp * 2); 
    }
    else
    {
      /* I2S �����O�t�ή���: �o��t�ή����W�v */
      RCC_GetClocksFreq(&RCC_Clocks);      
      
      /* �o��ӷ���������: �ھڨt�ή������� */
      sourceclock = RCC_Clocks.SYSCLK_Frequency;
    }        
#else /* STM32F10X_HD */
    /* I2S �������O�t�ή���: �o��t�ή����W�v */
    RCC_GetClocksFreq(&RCC_Clocks);      
      
    /* �o��ӷ���������: �ھڨt�ή������� */
    sourceclock = RCC_Clocks.SYSCLK_Frequency;    
#endif /* STM32F10X_CL */    

    /* �ίB�I���w�ھ�MCLK��X���A�p��u����ξ� */
    if(I2S_InitStruct->I2S_MCLKOutput == I2S_MCLKOutput_Enable)
    {
      /* MCLK��X�ϯ� */
      tmp = (uint16_t)(((((sourceclock / 256) * 10) / I2S_InitStruct->I2S_AudioFreq)) + 5);
    }
    else
    {
      /* MCLK��X���� */
      tmp = (uint16_t)(((((sourceclock / (32 * packetlength)) *10 ) / I2S_InitStruct->I2S_AudioFreq)) + 5);
    }
    
    /* �R���B�I���w */
    tmp = tmp / 10;  
      
    /* �ˬd���ƪ��_�� */
    i2sodd = (uint16_t)(tmp & (u16)0x0001);
   
    /* �p��i2sdiv�w���W�� */
    i2sdiv = (uint16_t)((tmp - i2sodd) / 2);
   
    /* ���o(SPI_I2SPR[8])�H�s���ª��лx�� */
    i2sodd = (uint16_t) (i2sodd << 8);
  }
  
  /* ���հ��ƬO1�٬O0 �Τj�� 0xFF */
  if ((i2sdiv < 2) || (i2sdiv > 0xFF))
  {
    /* �]�m�ʬ٭� */
    i2sdiv = 2;
    i2sodd = 0;
  }

  /* �g SPIx I2SPR �H�s�����p��� */
  SPIx->I2SPR = (uint16_t)(i2sdiv | (uint16_t)(i2sodd | (uint16_t)I2S_InitStruct->I2S_MCLKOutput));  
 
  /* �� SPI_InitStruct ���ȡA�t�m I2S  */
  tmpreg |= (uint16_t)(I2S_Mode_Select | (uint16_t)(I2S_InitStruct->I2S_Mode | \
                  (uint16_t)(I2S_InitStruct->I2S_Standard | (uint16_t)(I2S_InitStruct->I2S_DataFormat | \
                  (uint16_t)I2S_InitStruct->I2S_CPOL))));
 
  /* �g SPIx I2SCFGR */  
  SPIx->I2SCFGR = tmpreg;   
}

/**
  * @²�z  �ϥίʬ٭ȶ�R SPI_InitStruct �C�@�Ӧ���.
  * @�Ѽ�  SPI_InitStruct : ���V�@�ӱN�Q��l�ƪ� SPI_InitTypeDef ���c�����w.
  * @��^  �S��
  */
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)
{
/*--------------- ���m SPI I��l�Ƶ��c�Ѽƭ� -----------------*/
  /* ��l�� SPI_Direction ���� */
  SPI_InitStruct->SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  /* ��l�� SPI_Mode ���� */
  SPI_InitStruct->SPI_Mode = SPI_Mode_Slave;
  /* ��l�� SPI_DataSize ���� */
  SPI_InitStruct->SPI_DataSize = SPI_DataSize_8b;
  /* ��l�� SPI_CPOL ���� */
  SPI_InitStruct->SPI_CPOL = SPI_CPOL_Low;
  /* ��l�� SPI_CPHA ���� */
  SPI_InitStruct->SPI_CPHA = SPI_CPHA_1Edge;
  /* ��l�� SPI_NSS ���� */
  SPI_InitStruct->SPI_NSS = SPI_NSS_Hard;
  /* ��l�� SPI_BaudRatePrescaler ���� */
  SPI_InitStruct->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
  /* ��l�� SPI_FirstBit ���� */
  SPI_InitStruct->SPI_FirstBit = SPI_FirstBit_MSB;
  /* ��l�� SPI_CRCPolynomial ���� */
  SPI_InitStruct->SPI_CRCPolynomial = 7;
}

/**
  * @²�z  ���q�{�ȶ�R�C�� I2S_InitStruct ���c����.
  * @�Ѽ�  I2S_InitStruct : ���V�N�n�Q��l�ƪ�I2S_InitTypeDef ���c���w.
  * @��^  �S��
  */
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct)
{
/*--------------- ���m I2S ��l�Ƶ��c�Ѽƭ� -----------------*/
  /* ��l�� I2S_Mode ���� */
  I2S_InitStruct->I2S_Mode = I2S_Mode_SlaveTx;
  
  /* ��l�� I2S_Standard ���� */
  I2S_InitStruct->I2S_Standard = I2S_Standard_Phillips;
  
  /* ��l�� I2S_DataFormat ���� */
  I2S_InitStruct->I2S_DataFormat = I2S_DataFormat_16b;
  
  /* ��l�� I2S_MCLKOutput ���� */
  I2S_InitStruct->I2S_MCLKOutput = I2S_MCLKOutput_Disable;
  
  /* ��l�� I2S_AudioFreq ���� */
  I2S_InitStruct->I2S_AudioFreq = I2S_AudioFreq_Default;
  
  /* ��l�� I2S_CPOL ���� */
  I2S_InitStruct->I2S_CPOL = I2S_CPOL_Low;
}

/**
  * @²�z  �ϯ�Ϊ̥��� SPI �~�].
  * @�Ѽ�  SPIx: x ��1�A2��3�Ω��w SPI �~�].
  * @�Ѽ�  NewState: SPIx �~��]�ƪ��s���A. 
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �ϯ� SPI �~�] */
    SPIx->CR1 |= CR1_SPE_Set;
  }
  else
  {
    /* ���� SPI �~�] */
    SPIx->CR1 &= CR1_SPE_Reset;
  }
}

/**
  * @²�z  �ϯ�θT����w�� I2S �~�] (�b I2S �Ҧ�).
  * @�Ѽ�  SPIx: x��1�A2��3�Ω��w SPI �~�].
  * @�Ѽ�  NewState: SPIx �~��]�ƪ��s���A. 
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_SPI_23_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �ϯ��w�� SPI �~�] (�b I2S �Ҧ�) */
    SPIx->I2SCFGR |= I2SCFGR_I2SE_Set;
  }
  else
  {
    /* �����w�� SPI �~�] (�b I2S �Ҧ�) */
    SPIx->I2SCFGR &= I2SCFGR_I2SE_Reset;
  }
}

/**
  * @²�z  �ϯ�Ϊ̥�����w�� SPI/I2S ���_.
  * @�Ѽ�  SPIx: x �i�H�O
  *            - 1, 2 �� 3 �b SPI �Ҧ� 
  *            - 2 �� 3 �b I2S �Ҧ�
  * @�Ѽ�  SPI_I2S_IT: ���w�����_��. 
  *          �o�ӰѼƥi�H�O�U�����Ȥ��@:
  *          SPI_I2S_IT_TXE:  �o�e�w�s�Ť��_
  *          SPI_I2S_IT_RXNE: �����w�s�D�Ť��_
  *          SPI_I2S_IT_ERR:  ���~���_
  * @�Ѽ�  NewState: ���w�� SPI/I2S ���_���s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @retval None
  */
void SPI_I2S_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState)
{
  uint16_t itpos = 0, itmask = 0 ;
  /* �ˬd�Ѽ� */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_SPI_I2S_CONFIG_IT(SPI_I2S_IT));

  /* �o�� SPI/I2S ���_���� */
  itpos = SPI_I2S_IT >> 4;

  /* �]�m IT */
  itmask = (uint16_t)1 << (uint16_t)itpos;

  if (NewState != DISABLE)
  {
    /* �ϯ� SPI/I2S ���_ */
    SPIx->CR2 |= itmask;
  }
  else
  {
    /* ���� SPI/I2S ���_ */
    SPIx->CR2 &= (uint16_t)~itmask;
  }
}

/**
  * @²�z  �ϯ�Ϊ̥�����w SPIx/I2Sx ��DMA�ШD.
  * @�Ѽ�  SPIx: x �i�H�O
  *             - 1, 2 �� 3 �b SPI �Ҧ� 
  *             - 2 �� 3 �b I2S �Ҧ�
  * @�Ѽ�  SPI_I2S_DMAReq: ���w�� SPI/I2S DMA �ШD. 
  *          �o�ӰѼƥi�H�O�U�����N�Ȫ��զX:
  *          SPI_I2S_DMAReq_Tx: �o�e�w�� DMA �ǿ�ШD
  *          SPI_I2S_DMAReq_Rx: �����w�� DMA �ǿ�ШD
  * @�Ѽ�  NewState: ��w�� SPI/I2S DMA �ШD���s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @retval None
  */
void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_SPI_I2S_DMAREQ(SPI_I2S_DMAReq));
  if (NewState != DISABLE)
  {
    /* �ϯ��w�� SPI/I2S DMA �ШD */
    SPIx->CR2 |= SPI_I2S_DMAReq;
  }
  else
  {
    /* �����w�� SPI/I2S DMA �ШD */
    SPIx->CR2 &= (uint16_t)~SPI_I2S_DMAReq;
  }
}

/**
  * @²�z  �q�L SPIx/I2Sx �~�]�o�e�ƾ�.
  * @�Ѽ�  SPIx: x �i�H�O
  *            - 1, 2 �� 3 �b SPI �Ҧ� 
  *            - 2 or 3 �b I2S �Ҧ�
  * @�Ѽ�  Data : �ݵo�e���ƾ�.
  * @��^  �S��
  */
void SPI_I2S_SendData(SPI_TypeDef* SPIx, uint16_t Data)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  
  /* ��ƾڼg�J DR �H�s���o�e */
  SPIx->DR = Data;
}

/**
  * @²�z  ��^�̪�q SPIx/I2Sx �~���]�Ʊ������ƾ�. 
  * @�Ѽ�  SPIx: x �i�H�O
  *            - 1, 2 �� 3 �b SPI �Ҧ� 
  *            - 2 �� 3 �b I2S �Ҧ�
  * @��^  �������ƾ�.
  */
uint16_t SPI_I2S_ReceiveData(SPI_TypeDef* SPIx)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  
  /* ��^ DR �H�s�����ƾ� */
  return SPIx->DR;
}

/**
  * @²�z  ����w�� SPI �n��t�m���� NSS �޸}.
  * @�Ѽ�  SPIx: x ��1�A2��3�Ω��wSPI�~�].
  * @�Ѽ�  SPI_NSSInternalSoft: ���w�� SPI NSS �������A.
  *          �o�ӰѼƥi�H�O�U�����Ȥ��@:
  *          SPI_NSSInternalSoft_Set:   �]�m NSS �����޸}
  *          SPI_NSSInternalSoft_Reset: �_�� NSS �����޸}
  * @��^  �S��
  */
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_NSS_INTERNAL(SPI_NSSInternalSoft));
  if (SPI_NSSInternalSoft != SPI_NSSInternalSoft_Reset)
  {
    /* �n��]�m NSS �����޸} */
    SPIx->CR1 |= SPI_NSSInternalSoft_Set;
  }
  else
  {
    /* �n��_�� NSS �����޸} */
    SPIx->CR1 &= SPI_NSSInternalSoft_Reset;
  }
}

/**
  * @²�z  �ϯ�Ϊ̥�����w�� SPI SS ��X.
  * @�Ѽ�  SPIx: x ��1�A2��3�Ω��w SPI �~�].
  * @�Ѽ�  NewState: ��w�� SPI SS ��X���s���A. 
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �ϯ���w�� SPI SS ��X */
    SPIx->CR2 |= CR2_SSOE_Set;
  }
  else
  {
    /* ������w�� SPI SS ��X */
    SPIx->CR2 &= CR2_SSOE_Reset;
  }
}

/**
  * @²�z  �]�m��w�� SPI �ƾڤj�p.
  * @�Ѽ�  SPIx: x ��1�A2��3�Ω��w SPI �~�].
  * @�Ѽ�  SPI_DataSize: ���w�� SPI �ƾڤj�p.
  *          �o�ӰѼƥi�H�O�U�����Ȥ��@:
  *          SPI_DataSize_16b: �]�m�ƾڤj�p��16��
  *          SPI_DataSize_8b:  �]�m�ƾڤj�p�� 8��
  * @��^  �S��
  */
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_DATASIZE(SPI_DataSize));
  /* �M�� DFF �� */
  SPIx->CR1 &= (uint16_t)~SPI_DataSize_16b;
  /* �]�m�s�� DFF �쪺�� */
  SPIx->CR1 |= SPI_DataSize;
}

/**
  * @²�z  �ǰe�Y�� SPI �� CRC �����.
  * @�Ѽ�  SPIx: x ��1�A2��3�Ω��wSPI�~�].
  * @��^  �S��
  */
void SPI_TransmitCRC(SPI_TypeDef* SPIx)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  
  /* �ϯ�襤�� SPI CRC �o�e */
  SPIx->CR1 |= CR1_CRCNext_Set;
}

/**
  * @²�z  �ϯ�Ϊ̥�����w SPI ���ǿ�r CRC �ȭp��.
  * @�Ѽ�  SPIx: x ��1�A2��3�Ω��wSPI�~�].
  * @�Ѽ�  NewState: ��w SPI ���f�� CRC �p�⪺�s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �ϯ��w�� SPI CRC �p�� */
    SPIx->CR1 |= CR1_CRCEN_Set;
  }
  else
  {
    /* �����w�� SPI CRC �p�� */
    SPIx->CR1 &= CR1_CRCEN_Reset;
  }
}

/**
  * @²�z  ��^���w SPI �o�e�α����� CRC ��.
  * @�Ѽ�  SPIx: x ��1�A2��3�Ω��w SPI �~�].
  * @�Ѽ�  SPI_CRC: �N�QŪ���� CRC �H�s��.
  *          �o�ӰѼƥi�H�O�U�����Ȥ��@:
  *          SPI_CRC_Tx: ��� Tx CRC �H�s��
  *          SPI_CRC_Rx: ��� Rx CRC �H�s��
  * @��^  ��w�� CRC �H�s������.
  */
uint16_t SPI_GetCRC(SPI_TypeDef* SPIx, uint8_t SPI_CRC)
{
  uint16_t crcreg = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_CRC(SPI_CRC));
  if (SPI_CRC != SPI_CRC_Rx)
  {
    /* �o�� Tx CRC �H�s������ */
    crcreg = SPIx->TXCRCR;
  }
  else
  {
    /* �o�� Rx CRC �H�s������ */
    crcreg = SPIx->RXCRCR;
  }
  /* ��^���w�� CRC �H�s������ */
  return crcreg;
}

/**
  * @²�z  ��^���w SPI �� CRC �h�����H�s����.
  * @�Ѽ�  SPIx: x ��1�A2��3�Ω��wSPI�~�].
  * @��^  ���w�� CRC �h�����H�s����.
  */
uint16_t SPI_GetCRCPolynomial(SPI_TypeDef* SPIx)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  
  /* ��^���w CRC �h�����H�s���� */
  return SPIx->CRCPR;
}

/**
  * @²�z  ��ܫ��w SPI �b���V�Ҧ��U���ƾڶǿ��V.
  * @�Ѽ�  SPIx: x ��1�A2��3�Ω��wSPI�~�].
  * @�Ѽ�  SPI_Direction: �b���V�Ҧ������ƾڶǿ��V. 
  *          �o�ӰѼƥi�H�O�U�����Ȥ��@:
  *          SPI_Direction_Tx: ��� Tx �ǰe��V
  *          SPI_Direction_Rx: ��� Rx ������V
  * @��^  �S��
  */
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_DIRECTION(SPI_Direction));
  if (SPI_Direction == SPI_Direction_Tx)
  {
    /* �]�m�u�o�e�Ҧ� */
    SPIx->CR1 |= SPI_Direction_Tx;
  }
  else
  {
    /* �]�m�u�����Ҧ� */
    SPIx->CR1 &= SPI_Direction_Rx;
  }
}

/**
  * @²�z  �ˬd���w�� SPI/I2S �аO�O�_�Q�m��.
  * @�Ѽ�  SPIx: x �i�H�O
  *            - 1, 2 �� 3 �b SPI �Ҧ� 
  *            - 2 �� 3 �b I2S �Ҧ�
  * @�Ѽ�  SPI_I2S_FLAG: ���w�� SPI/I2S �лx. 
  *          �o�ӰѼƥi�H�O�U�����Ȥ��@:
  *          SPI_I2S_FLAG_TXE:  �ǿ�w�Ĭ��żлx.
  *          SPI_I2S_FLAG_RXNE: �����w�Ĥ��żлx.
  *          SPI_I2S_FLAG_BSY:  ���лx.
  *          SPI_I2S_FLAG_OVR:  ���X�лx.
  *          SPI_FLAG_MODF:     �Ҧ����~�лx.
  *          SPI_FLAG_CRCERR:   CRC ������~�лx.
  *          I2S_FLAG_UDR:      �Ŵ�Ū�X���лx.
  *          I2S_FLAG_CHSIDE:   �q�D��ɼлx.
  * @��^  SPI_I2S_FLAG ���s���A (SET �� RESET).
  */
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* �ˬd�Ѽ� */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_I2S_GET_FLAG(SPI_I2S_FLAG));
  /* �ˬd���w�� SPI/I2S �лx���A */
  if ((SPIx->SR & SPI_I2S_FLAG) != (uint16_t)RESET)
  {
    /* �]�m SPI_I2S_FLAG */
    bitstatus = SET;
  }
  else
  {
    /* �_�� SPI_I2S_FLAG */
    bitstatus = RESET;
  }
  /* ��^ SPI_I2S_FLAG ���A */
  return  bitstatus;
}

/**
  * @²�z  �M�� SPIx CRC ���~ (CRCERR) �лx.
  * @�Ѽ�  SPIx: x �i�H�O
  *            - 1, 2 �� 3 �b SPI �Ҧ� 
  * @�Ѽ�  SPI_I2S_FLAG: ���w�n�M���� SPI �лx. 
  *           �o�Ө�ƶȶȥΩ�M�� CRCERR �лx.
  * @����
*        - OVR (�L�t���~)���_���_��i�H�Q�n������ǲM��: �@��Ū  
*          SPI_DR�H�s���ާ@ (SPI_I2S_ReceiveData()) ��ۤ@��Ū  
*          SPI_SR�H�s���ާ@ (SPI_I2S_GetITStatus()).
*        - UDR (�Ŵ�Ū���~) ���_���_��i�H�Q�@��ŪSPI_SR�H�s����
*          �@�M��(SPI_I2S_GetITStatus())�C
*        - MODF (�Ҧ����~) ���_���_��Q�n������ǲM��:�@��Ū/�g 
*          SPI_SR�H�s���ާ@(SPI_I2S_GetITStatus())��ۤ@�ӼgSPI_CR1 
*          �H�s���ާ@ (SPI_Cmd() �ϯ� SPI).  
  * @��^  �S��
  */
void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_I2S_CLEAR_FLAG(SPI_I2S_FLAG));
    
    /* �M����ܪ� SPI CRC ���~ (CRCERR) �лx */
    SPIx->SR = (uint16_t)~SPI_I2S_FLAG;
}

/**
  * @²�z  �ˬd���w���� SPI/I2S ���_�O�_�o�ͤF.
  * @�Ѽ�  SPIx: x �i�H�O
  *            - 1, 2 �� 3 �b SPI �Ҧ� 
  *            - 2 �� 3 �b I2S �Ҧ�
  * @�Ѽ�  SPI_I2S_IT: ���ˬd�� SPI/I2S ���_��. 
  *          �o�ӰѼƥi�H�O�U�����Ȥ��@:
  *          SPI_I2S_IT_TXE:  �ǿ�w�Ĭ��Ť��_.
  *          SPI_I2S_IT_RXNE: �����w�Ĥ��Ť��_.
  *          SPI_I2S_IT_OVR:  ���X���_.
  *          SPI_IT_MODF:     �Ҧ����~���_.
  *          SPI_IT_CRCERR:   CRC ������~���_.
  *          I2S_IT_UDR:      �Ŵ�Ū���~���_.
  * @��^  SPI_I2S_IT ���s���A (SET �� RESET).
  */
ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT)
{
  ITStatus bitstatus = RESET;
  uint16_t itpos = 0, itmask = 0, enablestatus = 0;

  /* �ˬd�Ѽ� */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_I2S_GET_IT(SPI_I2S_IT));

  /* �o�� SPI/I2S ���_���� */
  itpos = 0x01 << (SPI_I2S_IT & 0x0F);

  /* �o�� SPI/I2S ���_�� */
  itmask = SPI_I2S_IT >> 4;

  /* �]�m���_�� */
  itmask = 0x01 << itmask;

  /* ���o SPI_I2S_IT �ϯબ�A�� */
  enablestatus = (SPIx->CR2 & itmask) ;

  /* �ˬd���w�� SPI/I2S ���_���A */
  if (((SPIx->SR & itpos) != (uint16_t)RESET) && enablestatus)
  {
    /* �]�m SPI_I2S_IT */
    bitstatus = SET;
  }
  else
  {
    /* �_�� SPI_I2S_IT */
    bitstatus = RESET;
  }
  /* ��^ SPI_I2S_IT ���A */
  return bitstatus;
}

/**
  * @²�z  �M�����w�� SPI CRC ���~ (CRCERR) ���_���_��.
  * @�Ѽ�  SPIx: x �i�H�O
  *            - 1, 2 �� 3 �b SPI �Ҧ� 
  * @�Ѽ�  SPI_I2S_IT: �M�����w�����_���_��.
  *           �o�Ө�ƥu�M�� CRCERR ���_���_��.   
  * @note
*          - OVR (�L�t���~)���_���_��i�H�Q�n������ǲM��: �@��Ū  
*            SPI_DR�H�s���ާ@ (SPI_I2S_ReceiveData()) ��ۤ@��Ū  
*            SPI_SR�H�s���ާ@ (SPI_I2S_GetITStatus()).
*          - UDR (�Ŵ�Ū���~) ���_���_��i�H�Q�@��ŪSPI_SR�H�s����
*            �@�M��(SPI_I2S_GetITStatus())�C
*          - MODF (�Ҧ����~) ���_���_��Q�n������ǲM��:�@��Ū/�g 
*            SPI_SR�H�s���ާ@(SPI_I2S_GetITStatus())��ۤ@�ӼgSPI_CR1 
*            �H�s���ާ@ (SPI_Cmd() �ϯ� SPI).  
  * @��^  �S��
  */
void SPI_I2S_ClearITPendingBit(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT)
{
  uint16_t itpos = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_I2S_CLEAR_IT(SPI_I2S_IT));

  /* �o�� SPI ���_���� */
  itpos = 0x01 << (SPI_I2S_IT & 0x0F);

  /* �M�����w�� SPI CRC ���~ (CRCERR) ���_���_�� */
  SPIx->SR = (uint16_t)~itpos;
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
