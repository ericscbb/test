/**
  ******************************************************************************
  * @���    stm32f10x_rcc.c
  * @�@��    MCD ���ε{�ǲ�
  * @����    V3.1.0
  * @���    06/19/2009
  * @brief   �o�Ӥ�� ���ѩҦ� RCC �T����.
  * @½Ķ    ANSON/sweet1985 Email:airanson110@126.com
  * @���    03/07/2009
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
#include "stm32f10x_rcc.h"

/* �ۥ����� --------------------------------------------------------------*/
/* �ۥΩw�q --------------------------------------------------------------*/

/* ------------ RCC registers bit address in the alias region ----------- */
#define RCC_OFFSET                (RCC_BASE - PERIPH_BASE)

/* --- CR �H�s�� ---*/

/* Alias word address of HSION bit */
#define CR_OFFSET                 (RCC_OFFSET + 0x00)
#define HSION_BitNumber           0x00
#define CR_HSION_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (HSION_BitNumber * 4))

/* Alias word address of PLLON bit */
#define PLLON_BitNumber           0x18
#define CR_PLLON_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PLLON_BitNumber * 4))

#ifdef STM32F10X_CL
 /* Alias word address of PLL2ON bit */
 #define PLL2ON_BitNumber          0x1A
 #define CR_PLL2ON_BB              (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PLL2ON_BitNumber * 4))

 /* Alias word address of PLL3ON bit */
 #define PLL3ON_BitNumber          0x1C
 #define CR_PLL3ON_BB              (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PLL3ON_BitNumber * 4))
#endif /* STM32F10X_CL */ 

/* Alias word address of CSSON bit */
#define CSSON_BitNumber           0x13
#define CR_CSSON_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (CSSON_BitNumber * 4))

/* --- CFGR �H�s�� ---*/

/* Alias word address of USBPRE bit */
#define CFGR_OFFSET               (RCC_OFFSET + 0x04)

#ifndef STM32F10X_CL
 #define USBPRE_BitNumber          0x16
 #define CFGR_USBPRE_BB            (PERIPH_BB_BASE + (CFGR_OFFSET * 32) + (USBPRE_BitNumber * 4))
#else
 #define OTGFSPRE_BitNumber        0x16
 #define CFGR_OTGFSPRE_BB          (PERIPH_BB_BASE + (CFGR_OFFSET * 32) + (OTGFSPRE_BitNumber * 4))
#endif /* STM32F10X_CL */ 

/* --- BDCR �H�s�� ---*/

/* Alias word address of RTCEN bit */
#define BDCR_OFFSET               (RCC_OFFSET + 0x20)
#define RTCEN_BitNumber           0x0F
#define BDCR_RTCEN_BB             (PERIPH_BB_BASE + (BDCR_OFFSET * 32) + (RTCEN_BitNumber * 4))

/* Alias word address of BDRST bit */
#define BDRST_BitNumber           0x10
#define BDCR_BDRST_BB             (PERIPH_BB_BASE + (BDCR_OFFSET * 32) + (BDRST_BitNumber * 4))

/* --- CSR �H�s�� ---*/

/* Alias word address of LSION bit */
#define CSR_OFFSET                (RCC_OFFSET + 0x24)
#define LSION_BitNumber           0x00
#define CSR_LSION_BB              (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (LSION_BitNumber * 4))

#ifdef STM32F10X_CL
/* --- CFGR2 �H�s�� ---*/

 /* Alias word address of I2S2SRC bit */
 #define CFGR2_OFFSET              (RCC_OFFSET + 0x2C)
 #define I2S2SRC_BitNumber         0x11
 #define CFGR2_I2S2SRC_BB          (PERIPH_BB_BASE + (CFGR2_OFFSET * 32) + (I2S2SRC_BitNumber * 4))

 /* Alias word address of I2S3SRC bit */
 #define I2S3SRC_BitNumber         0x12
 #define CFGR2_I2S3SRC_BB          (PERIPH_BB_BASE + (CFGR2_OFFSET * 32) + (I2S3SRC_BitNumber * 4))
#endif /* STM32F10X_CL */

/* ---------------------- RCC �H�s�� bit mask ------------------------ */

/* CR register bit mask */
#define CR_HSEBYP_Reset           ((uint32_t)0xFFFBFFFF)
#define CR_HSEBYP_Set             ((uint32_t)0x00040000)
#define CR_HSEON_Reset            ((uint32_t)0xFFFEFFFF)
#define CR_HSEON_Set              ((uint32_t)0x00010000)
#define CR_HSITRIM_Mask           ((uint32_t)0xFFFFFF07)

/* CFGR register bit mask */
#ifndef STM32F10X_CL
 #define CFGR_PLL_Mask            ((uint32_t)0xFFC0FFFF)
#else
 #define CFGR_PLL_Mask           ((uint32_t)0xFFC2FFFF)
#endif /* STM32F10X_CL */ 

#define CFGR_PLLMull_Mask         ((uint32_t)0x003C0000)
#define CFGR_PLLSRC_Mask          ((uint32_t)0x00010000)
#define CFGR_PLLXTPRE_Mask        ((uint32_t)0x00020000)
#define CFGR_SWS_Mask             ((uint32_t)0x0000000C)
#define CFGR_SW_Mask              ((uint32_t)0xFFFFFFFC)
#define CFGR_HPRE_Reset_Mask      ((uint32_t)0xFFFFFF0F)
#define CFGR_HPRE_Set_Mask        ((uint32_t)0x000000F0)
#define CFGR_PPRE1_Reset_Mask     ((uint32_t)0xFFFFF8FF)
#define CFGR_PPRE1_Set_Mask       ((uint32_t)0x00000700)
#define CFGR_PPRE2_Reset_Mask     ((uint32_t)0xFFFFC7FF)
#define CFGR_PPRE2_Set_Mask       ((uint32_t)0x00003800)
#define CFGR_ADCPRE_Reset_Mask    ((uint32_t)0xFFFF3FFF)
#define CFGR_ADCPRE_Set_Mask      ((uint32_t)0x0000C000)

/* CSR register bit mask */
#define CSR_RMVF_Set              ((uint32_t)0x01000000)

#ifdef STM32F10X_CL
/* CFGR2 register bit mask */
 #define CFGR2_PREDIV1SRC         ((uint32_t)0x00010000)
 #define CFGR2_PREDIV1            ((uint32_t)0x0000000F)
 #define CFGR2_PREDIV2            ((uint32_t)0x000000F0)
 #define CFGR2_PLL2MUL            ((uint32_t)0x00000F00)
 #define CFGR2_PLL3MUL            ((uint32_t)0x0000F000)
#endif /* STM32F10X_CL */ 

/* RCC Flag Mask */
#define FLAG_Mask                 ((uint8_t)0x1F)

#ifndef HSI_Value
/* Typical Value of the HSI in Hz */
 #define HSI_Value                 ((uint32_t)8000000)
#endif /* HSI_Value */

/* CIR register byte 2 (Bits[15:8]) base address */
#define CIR_BYTE2_ADDRESS         ((uint32_t)0x40021009)

/* CIR register byte 3 (Bits[23:16]) base address */
#define CIR_BYTE3_ADDRESS         ((uint32_t)0x4002100A)

/* CFGR register byte 4 (Bits[31:24]) base address */
#define CFGR_BYTE4_ADDRESS        ((uint32_t)0x40021007)

/* BDCR register base address */
#define BDCR_ADDRESS              (PERIPH_BASE + BDCR_OFFSET)

#ifndef HSEStartUp_TimeOut
/* Time out for HSE start up */
 #define HSEStartUp_TimeOut        ((uint16_t)0x0500)
#endif /* HSEStartUp_TimeOut */

/* �ۥΧ� ------------------------------------------------------------*/
/* �ۥ��ܶq ----------------------------------------------------------*/

static __I uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};
static __I uint8_t ADCPrescTable[4] = {2, 4, 6, 8};

/* �ۥΨ�ƭ쫬 ------------------------------------------------------*/
/* �ۥΨ�� ----------------------------------------------------------*/


/**
  * @²�z  �N�~�]RCC�H�s�����]���ʬ٭�.
  * @�Ѽ�  �S��
  * @��^  �S��
  */
void RCC_DeInit(void)
{
  /* �m��HSION (����<8MHz>���t�����ϯ�) */
  RCC->CR |= (uint32_t)0x00000001;

  /* �_�� SW, HPRE, PPRE1, PPRE2, ADCPRE , MCO �� */
  /* (HIS�Q��@�t�ή����AHSI�������Q�Χ@�t�ή����ASYSCLK���Q���W�AHCLK���Q���W�A
     ADC�w���W��<PLCK2>�Q2���W�AHSI����������/2�Q��@PLL��J����)�A�L����L������X */
#ifndef STM32F10X_CL
  RCC->CFGR &= (uint32_t)0xF8FF0000;   /* ?�b�O�d�ϸm1 */
#else
  RCC->CFGR &= (uint32_t)0xF0FF0000;   /* ?�b�O�d�ϲM0 */
#endif /* STM32F10X_CL */   
  
  /* �_�� HSEON, CSSON, PLLON �� (PLL�T�ΡA�����˴����T�ΡAHSE�������T��) */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* �_�� HSEBYP �� (�~��1~25MHz���������Q�Ǹ�) */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* �_�� PLLSRC, PLLXTPRE, PLLMUL , USBPRE/OTGFSPRE �� */
  /*(USB�w���W����PLL����1.5���W�APLL���W�Ѽ�X2�AHSE���Q���W�@��PLL��J�AHSI����������/2�Q��@PLL��J) */
  RCC->CFGR &= (uint32_t)0xFF80FFFF;

#ifndef STM32F10X_CL
  /* �ϩҦ��������_���� */
  RCC->CIR = 0x009F0000;
#else
  /* �_�� PLL2ON , PLL3ON �� () */
  RCC->CR &= (uint32_t)0xEBFFFFFF;

  /* �ϩҦ��������_����  */
  RCC->CIR = 0x00FF0000;

  /* �_�� CFGR2 �H�s�� */
  RCC->CFGR2 = 0x00000000;
#endif /* STM32F10X_CL */
}

/**
  * @²�z  �t�m�~�����t������ (HSE).
  * @����  �p�G HSE �Q�����ϥΩΪ̳q�L PLL �@���t�ή����A�h�����ఱ��.
  * @�Ѽ�  RCC_HSE: ���w HSE �s�����A.
  *                 �o�ӰѼƥi�H��ܤU�����@��:
  *             RCC_HSE_OFF: HSE ������ OFF
  *             RCC_HSE_ON : HSE ������ ON
  *             RCC_HSE_Bypass: HSE �������Ǹ��ϥΥ~������
  * @��^  �S��
  */
void RCC_HSEConfig(uint32_t RCC_HSE)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_HSE(RCC_HSE));
  /* �_�� HSEON , HSEBYP �� �b�t�m HSE �H�e ------------------*/
  /* Reset HSEON bit (�T�� HSE ������)*/
  RCC->CR &= CR_HSEON_Reset;
  /* Reset HSEBYP bit (�~��1~25MHz���������Q�Ǹ�)*/
  RCC->CR &= CR_HSEBYP_Reset;
  /* �t�m HSE (RCC_HSE_OFF �w�g�Qcode�֤ߥN�X�л\�F) */
  switch(RCC_HSE)
  {
    case RCC_HSE_ON:
      /* Set HSEON bit (���} HSE ������)*/
      RCC->CR |= CR_HSEON_Set;
      break;
      
    case RCC_HSE_Bypass:
      /* Set HSEBYP and HSEON bits (�T�� HSE �������Q�~��1~25MHz�������M�~�������Ǹ�)*/
      RCC->CR |= CR_HSEBYP_Set | CR_HSEON_Set;
      break;
      
    default:
      break;
  }
}

/**
  * @²�z  ���� HSE �Ұ�.
  * @�Ѽ�  �S��
  * @��^  �@��ErrorStatus�T�|��:
  *        SUCCESS: HSE �������w�gí�w�åB�i�H�ϥ�
  *        ERROR  : HSE �������|���ǳƦn
  */
ErrorStatus RCC_WaitForHSEStartUp(void)
{
  __IO uint32_t StartUpCounter = 0;
  ErrorStatus status = ERROR;
  FlagStatus HSEStatus = RESET;
  
  /* ���� HSE �ǳƦn�M�W�ɪ��ɶ���� */
  do
  {
    HSEStatus = RCC_GetFlagStatus(RCC_FLAG_HSERDY);
    StartUpCounter++;  
  } while((StartUpCounter != HSEStartUp_TimeOut) && (HSEStatus == RESET));
  
  if (RCC_GetFlagStatus(RCC_FLAG_HSERDY) != RESET)
  {
    status = SUCCESS;
  }
  else
  {
    status = ERROR;
  }  
  return (status);
}

/**
  * @²�z  �վ㤺�����t������ (HSI) �Ы׭�.
  * @�Ѽ�  HSICalibrationValue: �ե��Ы׭ȡA�o�ӰѼƤ@�w�O�b0��0x1F��������.
  * @��^  �S��
  */
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue)
{
  uint32_t tmpreg = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_CALIBRATION_VALUE(HSICalibrationValue));
  tmpreg = RCC->CR;
  /* �M�� HSITRIM[4:0] �� (�q�{�ȬO16�� HIS �Y��u�@�b8MHz) */
  tmpreg &= CR_HSITRIM_Mask;
  /* �]�m HSITRIM[4:0] ��A�ھ� HSICalibrationValue ���� */
  tmpreg |= (uint32_t)HSICalibrationValue << 3;
  /* �s�x�s���� */
  RCC->CR = tmpreg;
}

/**
  * @²�z  �ϯ�Υ��ऺ�����t������ (HSI).
  * @����  �p�G HSE �Q�����ϥΩΪ̳q�L PLL �@���t�ή����A�h�����ఱ��.
  * @�Ѽ�  NewState: HSI ���s���A. 
  *                 �o�ӰѼƥi��: ENABLE �� DISABLE.
  * @��^  �S��
  */
void RCC_HSICmd(FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CR_HSION_BB = (uint32_t)NewState;
}

/**
  * @²�z  �]�mPLL�������έ��W�Y��.
  * @����  �o�Ө�ƶȶ����Φb PLL �Q�T��ɭ�.
  * @�Ѽ�  RCC_PLLSource: ���w�i�J PLL ��������.
  *                       STM32_���pô�C�L�B�z��, �o�ӰѼƥi���U�C����:
  *                                      RCC_PLLSource_HSI_Div2: PLL ������J���� HSI �����������G���W
  *                                      RCC_PLLSource_PREDIV1: PREDIV1 clock selected as PLL clock entry
  *                       �䥦_STM32_�L�B�z��, �o�ӰѼƥi���U�C����:
  *                                      RCC_PLLSource_HSI_Div2: PLL ������J���� HSI �����������G���W
  *                                      RCC_PLLSource_HSE_Div1: PLL ������J���� HSE ����������
  *                                      RCC_PLLSource_HSE_Div2: PLL ������J���� HSE �����������G���W
  * @�Ѽ�  RCC_PLLMul: ���w PLL ���W�Y��.
  *                    STM32_Connectivity_line_devices, �o�ӰѼƥi�H�O RCC_PLLMul_x x�i�H��{[4,9], 6_5}
  *                    other_STM32_devices, �o�ӰѼƥi�H�O RCC_PLLMul_x x�i�H��:[2,16]
  * @��^  �S��
  */
void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul)
{
  uint32_t tmpreg = 0;

  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_PLL_SOURCE(RCC_PLLSource));
  assert_param(IS_RCC_PLL_MUL(RCC_PLLMul));

  tmpreg = RCC->CFGR;
  /* �M PLLSRC, PLLXTPRE , PLLMUL[3:0] �� */
  tmpreg &= CFGR_PLL_Mask;
  /* �]�m PLL �t�m�� */
  tmpreg |= RCC_PLLSource | RCC_PLLMul;
  /* �s�x�s�� */
  RCC->CFGR = tmpreg;
}

/**
  * @²�z  �ϯ�Υ��� PLL.
  * @����  �p�G PLL �@���t�ή����A�h�����ఱ��.
  * @�Ѽ�  NewState: PLL ���s���A. �o�ӰѼƥi�H��: ENABLE �� DISABLE.
  * @��^  �S��
  */
void RCC_PLLCmd(FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) CR_PLLON_BB = (uint32_t)NewState;
}

#ifdef STM32F10X_CL
/**
  * @²�z  �t�m PREDIV1 ���W�Ѽ�.
  * @���� 
  *   - �o�Ө�ƶȶ����Φb PLL �Q�T��ɭ�.
  *   - �o�Ө�ƶȶ����Φb STM32 ���pô�C�L�B�z��.
  * @�Ѽ�  RCC_PREDIV1_Source: ���w PREDIV1 ������.
  *                            �o�ӰѼƥi�H���U�C�Ȥ����@��:
  *                            RCC_PREDIV1_Source_HSE: HSE �@�� PREDIV1 ����
  *                            RCC_PREDIV1_Source_PLL2: PLL2 �@�� PREDIV1 ����
  * @�Ѽ�  RCC_PREDIV1_Div: ��w PREDIV1 ���W�Y��.
  *                         �o�ӰѼ� RCC_PREDIV1_Divx �� x�i�H��:[1,16]
  * @��^  �S��
  */
void RCC_PREDIV1Config(uint32_t RCC_PREDIV1_Source, uint32_t RCC_PREDIV1_Div)
{
  uint32_t tmpreg = 0;
  
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_PREDIV1_SOURCE(RCC_PREDIV1_Source));
  assert_param(IS_RCC_PREDIV1(RCC_PREDIV1_Div));

  tmpreg = RCC->CFGR2;
  /* �M PREDIV1[3:0] �M PREDIV1SRC �� */
  tmpreg &= ~(CFGR2_PREDIV1 | CFGR2_PREDIV1SRC);
  /* Set the PREDIV1 clock source and division factor */
  tmpreg |= RCC_PREDIV1_Source | RCC_PREDIV1_Div ;
  /* �s�x�s�� */
  RCC->CFGR2 = tmpreg;
}


/**
  * @²�z  �t�m PREDIV2 ���W�Ѽ�.
  * @���� 
  *   - �o�Ө�ƶȶ����Φb PLL2,PLL3 �Q�T��ɭ�.
  *   - �o�Ө�ƶȶ����Φb STM32 ���pô�C�L�B�z��.
  * @�Ѽ�  RCC_PREDIV2_Div: ��w PREDIV2 ���W�Y��.
  *                         �o�ӰѼ� RCC_PREDIV2_Divx �� x�i�H��:[1,16]
  * @��^  �S��
  */
void RCC_PREDIV2Config(uint32_t RCC_PREDIV2_Div)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RCC_PREDIV2(RCC_PREDIV2_Div));

  tmpreg = RCC->CFGR2;
  /* Clear PREDIV2[3:0] bits */
  tmpreg &= ~CFGR2_PREDIV2;
  /* Set the PREDIV2 division factor */
  tmpreg |= RCC_PREDIV2_Div;
  /* Store the new value */
  RCC->CFGR2 = tmpreg;
}

/**
  * @²�z  �t�m PLL2 ���W�Y��.
  * @����
  *   - �o�Ө�ƶȶ����Φb PLL2 �Q�T��ɭ�.
  *   - �o�Ө�ƶȶ����Φb STM32 ���pô�C�L�B�z��.
  * @�Ѽ�  RCC_PLL2Mul: ���w PLL2 ���W�Y��.
  *                     �o�ӰѼ� RCC_PLL2Mul_x �� x�i�H��:{[8,14], 16, 20}
  * @��^  �S��
  */
void RCC_PLL2Config(uint32_t RCC_PLL2Mul)
{
  uint32_t tmpreg = 0;

  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_PLL2_MUL(RCC_PLL2Mul));

  tmpreg = RCC->CFGR2;
  /* �M PLL2Mul[3:0] �� */
  tmpreg &= ~CFGR2_PLL2MUL;
  /* �]�m PLL2 �t�m�� */
  tmpreg |= RCC_PLL2Mul;
  /* �s�x�Ѽ� */
  RCC->CFGR2 = tmpreg;
}


/**
  * @²�z  �ϯ�Υ��� PLL2.
  * @���� 
  *   - �p�G PLL2 �Q�ΰ��t�ή����A���N����Q�T��
  *     (i.e.���Q�Χ@ PLL ������J���A�N�O���Q�Χ@�t�ή���).
  *   - �o�Ө�ƶȶ����Φb STM32 ���pô�C�L�B�z��.
  * @�Ѽ�  NewState: PLL2 �s�����A. �o�ӰѼƥi�H��: ENABLE �� DISABLE.
  * @��^  �S��
  */
void RCC_PLL2Cmd(FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) CR_PLL2ON_BB = (uint32_t)NewState;
}


/**
  * @²�z  �t�m PLL3 ���W�Y��.
  * @����
  *   - �o�Ө�ƶȶ����Φb PLL3 �Q�T��ɭ�.
  *   - �o�Ө�ƶȶ����Φb STM32 ���pô�C�L�B�z��.
  * @�Ѽ�  RCC_PLL3Mul: ���w PLL3 ���W�Y��.
  *                     �o�ӰѼ� RCC_PLL3Mul_x �� x�i�H��:{[8,14], 16, 20}
  * @��^  �S��
  */
void RCC_PLL3Config(uint32_t RCC_PLL3Mul)
{
  uint32_t tmpreg = 0;

  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_PLL3_MUL(RCC_PLL3Mul));

  tmpreg = RCC->CFGR2;
  /* �M PLL3Mul[3:0] �� */
  tmpreg &= ~CFGR2_PLL3MUL;
  /* �]�m PLL3 �t�m�� */
  tmpreg |= RCC_PLL3Mul;
  /* �s�x�s�� */
  RCC->CFGR2 = tmpreg;
}


/**
  * @²�z  �ϯ�Υ��� PLL3.
  * @����  �o�Ө�ƶȶ����Φb STM32 ���pô�C�L�B�z��.
  * @�Ѽ�  NewState: PLL3 �s�����A. �o�ӰѼƥi�H��: ENABLE �� DISABLE.
  * @��^  �S��
  */
void RCC_PLL3Cmd(FunctionalState NewState)
{
  /* Check the parameters */

  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CR_PLL3ON_BB = (uint32_t)NewState;
}
#endif /* STM32F10X_CL */

/**
  * @²�z  �t�m�t�ή��� (SYSCLK).
  * @�Ѽ�  RCC_SYSCLKSource: ���w�@���t�ή�����������.
  *                          �o�ӰѼƥi�H��ܤU�C�����@��:
  *                          RCC_SYSCLKSource_HSI:   ��w HSI �@���t�ή���
  *                          RCC_SYSCLKSource_HSE:   ��w HSE �@���t�ή���
  *                          RCC_SYSCLKSource_PLLCLK:��w PLL �@���t�ή���
  * @��^  �S��
  */
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource)
{
  uint32_t tmpreg = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_SYSCLK_SOURCE(RCC_SYSCLKSource));
  tmpreg = RCC->CFGR;
  /* �M SW[1:0] ��  */
  tmpreg &= CFGR_SW_Mask;
  /* �]�m SW[1:0] �쬰 RCC_SYSCLKSource ���� */
  tmpreg |= RCC_SYSCLKSource;
  /* �s�x�s�� */
  RCC->CFGR = tmpreg;
}

/**
  * @²�z  ��o�Χ@�t�ή�����������.
  * @�Ѽ�  �S��
  * @��^  �@���t�ή�����������. 
  *        �o�Ӫ�^�ȥi�H�O�U�C�������@��:
  *        0x00: HSI �Q�Χ@�t�ή���
  *        0x04: HSE �Q�Χ@�t�ή���
  *        0x08: PLL �Q�Χ@�t�ή���
  */
uint8_t RCC_GetSYSCLKSource(void)
{
  return ((uint8_t)(RCC->CFGR & CFGR_SWS_Mask));
}

/**
  * @²�z  �t�m AHB ���� (HCLK).
  * @�Ѽ�  RCC_SYSCLK: �w�q AHB �������W. �o�Ӯ����ӷ���t�ή���
  *                    �o�ӰѼƥi�H���U�C�Ȥ����@��:
  *                    RCC_SYSCLK_Div1: AHB clock = SYSCLK
  *                    RCC_SYSCLK_Div2: AHB clock = SYSCLK/2
  *                    RCC_SYSCLK_Div4: AHB clock = SYSCLK/4
  *                    RCC_SYSCLK_Div8: AHB clock = SYSCLK/8
  *                    RCC_SYSCLK_Div16: AHB clock = SYSCLK/16
  *                    RCC_SYSCLK_Div64: AHB clock = SYSCLK/64
  *                    RCC_SYSCLK_Div128: AHB clock = SYSCLK/128
  *                    RCC_SYSCLK_Div256: AHB clock = SYSCLK/256
  *                    RCC_SYSCLK_Div512: AHB clock = SYSCLK/512
  * @��^  �S��
  */
void RCC_HCLKConfig(uint32_t RCC_SYSCLK)
{
  uint32_t tmpreg = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_HCLK(RCC_SYSCLK));
  tmpreg = RCC->CFGR;
  /* �M HPRE[3:0] �� */
  tmpreg &= CFGR_HPRE_Reset_Mask;
  /* �]�m HPRE[3:0] �쬰 RCC_SYSCLK ���� */
  tmpreg |= RCC_SYSCLK;
  /* �s�x�s�� */
  RCC->CFGR = tmpreg;
}

/**
  * @²�z  �t�m�C�t APB ���� (PCLK1).
  * @�Ѽ�  RCC_HCLK: �t�m APB1 �������W. �o�Ӯ����ӷ��� AHB ���� (HCLK).
  *                  �o�ӰѼƥi�H���U�C�Ȥ����@��:
  *                  RCC_HCLK_Div1: APB1 clock = HCLK
  *                  RCC_HCLK_Div2: APB1 clock = HCLK/2
  *                  RCC_HCLK_Div4: APB1 clock = HCLK/4
  *                  RCC_HCLK_Div8: APB1 clock = HCLK/8
  *                  RCC_HCLK_Div16: APB1 clock = HCLK/16
  * @��^  �S��
  */
void RCC_PCLK1Config(uint32_t RCC_HCLK)
{
  uint32_t tmpreg = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_PCLK(RCC_HCLK));
  tmpreg = RCC->CFGR;
  /* �M PPRE1[2:0] �� */
  tmpreg &= CFGR_PPRE1_Reset_Mask;
  /* �]�m PPRE1[2:0] �쬰 RCC_HCLK ���� */
  tmpreg |= RCC_HCLK;
  /* �s�x�s�� */
  RCC->CFGR = tmpreg;
}

/**
  * @²�z  �t�m���t APB ���� (PCLK2).
  * @�Ѽ�  RCC_HCLK: �t�m APB2 �������W. �o�Ӯ����ӷ��� AHB ���� (HCLK).
  *                  �o�ӰѼƥi�H���U�C�Ȥ����@��:
  *                  RCC_HCLK_Div1: APB1 clock = HCLK
  *                  RCC_HCLK_Div2: APB1 clock = HCLK/2
  *                  RCC_HCLK_Div4: APB1 clock = HCLK/4
  *                  RCC_HCLK_Div8: APB1 clock = HCLK/8
  *                  RCC_HCLK_Div16: APB1 clock = HCLK/16
  * @��^  �S��
  */
void RCC_PCLK2Config(uint32_t RCC_HCLK)
{
  uint32_t tmpreg = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_PCLK(RCC_HCLK));
  tmpreg = RCC->CFGR;
  /* �M PPRE2[2:0] �� */
  tmpreg &= CFGR_PPRE2_Reset_Mask;
  /* �]�m PPRE2[2:0] �쬰 RCC_HCLK ���� */
  tmpreg |= RCC_HCLK << 3;
  /* �s�x�s�� */
  RCC->CFGR = tmpreg;
}

/**
  * @²�z  �ϯ�Υ�����w�� RCC ���_.
  * @�Ѽ�  RCC_IT: �ݨϯ�Ϊ̥��઺RCC���_��.
  * 
  *                 STM32_���pô�C�L�B�z��, �o�ӰѼƥi�H���U�C�Ȥ����@��:      
  *                                         RCC_IT_LSIRDY: LSI �ǳƤ��_
  *                                         RCC_IT_LSERDY: LSE �ǳƤ��_
  *                                         RCC_IT_HSIRDY: HSI �ǳƤ��_
  *                                         RCC_IT_HSERDY: HSE �ǳƤ��_
  *                                         RCC_IT_PLLRDY: PLL �ǳƤ��_
  *                                         RCC_IT_PLL2RDY: PLL2 �ǳƤ��_
  *                                         RCC_IT_PLL3RDY: PLL3 �ǳƤ��_
  * 
  *                    �䥦_STM32_�L�B�z��, �o�ӰѼƥi�H���U�C�Ȥ����@��:      
  *                                         RCC_IT_LSIRDY: LSI �ǳƤ��_
  *                                         RCC_IT_LSERDY: LSE �ǳƤ��_
  *                                         RCC_IT_HSIRDY: HSI �ǳƤ��_
  *                                         RCC_IT_HSERDY: HSE �ǳƤ��_
  *                                         RCC_IT_PLLRDY: PLL �ǳƤ��_
  *       
  * @�Ѽ�  NewState: RCC ���_�s�����A.
  *                   �o�ӰѼƥi�H��: ENABLE �� DISABLE.
  * @��^  �S��
  */
void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_IT(RCC_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* ����RCC_CIR[12:8]�쪺�r�`�s���Өϯ��ܪ����_s */
    *(__IO uint8_t *) CIR_BYTE2_ADDRESS |= RCC_IT;
  }
  else
  {
    /* ����RCC_CIR[12:8]�쪺�r�`�s���ӸT���ܪ����_ */
    *(__IO uint8_t *) CIR_BYTE2_ADDRESS &= (uint8_t)~RCC_IT;
  }
}

#ifndef STM32F10X_CL
/**
  * @²�z  �t�m USB ���� (USBCLK).
  * @�Ѽ�  RCC_USBCLKSource: ���w USB ��������. �o�Ӯ����ӷ��� PLL ��X.
  *                          �o�ӰѼƥi�H���U�C�Ȥ����@��:
  *                          RCC_USBCLKSource_PLLCLK_1Div5: PLL ������1.5���W�Χ@ USB ������
  *                          RCC_USBCLKSource_PLLCLK_Div1:  PLL �����Χ@ USB ������
  * @��^  �S��
  */
void RCC_USBCLKConfig(uint32_t RCC_USBCLKSource)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_USBCLK_SOURCE(RCC_USBCLKSource));

  *(__IO uint32_t *) CFGR_USBPRE_BB = RCC_USBCLKSource;
}
#else
/**
  * @²�z  �t�m USB OTG FS ���� (OTGFSCLK).
  *        �o�Ө�ƶȶ����Φb STM32 ���pô�C�L�B�z��.
  * @�Ѽ�  RCC_OTGFSCLKSource: ���w USB OTG FS ������.
  *                            �o�Ӯ����ӷ��� PLL ����X.
  *                            �o�ӰѼƥi�H���U�C�Ȥ����@��:
  *                            RCC_OTGFSCLKSource_PLLVCO_Div3: PLL VCO clock divided by 2 selected as USB OTG FS clock source
  *                            RCC_OTGFSCLKSource_PLLVCO_Div2: PLL VCO clock divided by 2 selected as USB OTG FS clock source
  * @��^  �S��
  */
void RCC_OTGFSCLKConfig(uint32_t RCC_OTGFSCLKSource)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_OTGFSCLK_SOURCE(RCC_OTGFSCLKSource));

  *(__IO uint32_t *) CFGR_OTGFSPRE_BB = RCC_OTGFSCLKSource;
}
#endif /* STM32F10X_CL */ 

/**
  * @²�z  �t�m ADC ���� (ADCCLK).
  * @�Ѽ�  RCC_PCLK2: �w�q ADC �������W. �o�Ӯ����ӷ��� APB2 ���� (PCLK2).
  *                                      �o�ӰѼƥi�H���U�C�Ȥ����@��:
  *                                      RCC_PCLK2_Div2: ADC clock = PCLK2/2
  *                                      RCC_PCLK2_Div4: ADC clock = PCLK2/4
  *                                      RCC_PCLK2_Div6: ADC clock = PCLK2/6
  *                                      RCC_PCLK2_Div8: ADC clock = PCLK2/8
  * @��^  �S��
  */
void RCC_ADCCLKConfig(uint32_t RCC_PCLK2)
{
  uint32_t tmpreg = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_ADCCLK(RCC_PCLK2));
  tmpreg = RCC->CFGR;
  /* �M ADCPRE[1:0] �� */
  tmpreg &= CFGR_ADCPRE_Reset_Mask;
  /* �]�m ADCPRE[1:0] ����M�� RCC_PCLK2 ���� */
  tmpreg |= RCC_PCLK2;
  /* �s�x�s�� */
  RCC->CFGR = tmpreg;
}

#ifdef STM32F10X_CL
/**
  * @²�z  �t�m I2S2 ������(I2S2CLK).
  * @����
  *   - �o�Ө�ƥ����b�ϯ�I2S2 APB�������e�ե�.
  *   - �o�Ө�ƶȶ����Φb STM32 ���pô�C�L�B�z��.
  * @�Ѽ�  RCC_I2S2CLKSource: ���w I2S2 ������.
  *                           �o�ӰѼƥi�H���U�C�Ȥ����@��:
  *                           RCC_I2S2CLKSource_SYSCLK: �t�ή����@�� I2S2 ������
  *                           RCC_I2S2CLKSource_PLL3_VCO: PLL3 VCO �@�� I2S2 ������
  * @��^  �S��
  */
void RCC_I2S2CLKConfig(uint32_t RCC_I2S2CLKSource)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_I2S2CLK_SOURCE(RCC_I2S2CLKSource));

  *(__IO uint32_t *) CFGR2_I2S2SRC_BB = RCC_I2S2CLKSource;
}

/**
  * @²�z  �t�m I2S3 ������(I2S2CLK).
  * @����
  *   - �o�Ө�ƥ����b�ϯ�I2S3 APB�������e�ե�.
  *   - �o�Ө�ƶȶ����Φb STM32 ���pô�C�L�B�z��.
  * @�Ѽ�  RCC_I2S3CLKSource: ���w I2S3 ������.
  *                           �o�ӰѼƥi�H���U�C�Ȥ����@��:
  *                           RCC_I2S2CLKSource_SYSCLK: �t�ή����@�� I2S3 ������
  *                           RCC_I2S2CLKSource_PLL3_VCO: PLL3 VCO �@�� I2S3 ������
  * @��^  �S��
  */
void RCC_I2S3CLKConfig(uint32_t RCC_I2S3CLKSource)
{
  /* ���w�Ѽ� */
  assert_param(IS_RCC_I2S3CLK_SOURCE(RCC_I2S3CLKSource));

  *(__IO uint32_t *) CFGR2_I2S3SRC_BB = RCC_I2S3CLKSource;
}
#endif /* STM32F10X_CL */

/**
  * @²�z  �t�m�~���C�t������ (LSE).
  * @�Ѽ�  RCC_LSE: ���w LSE ���s���A.
  *                 �o�ӰѼƥi�H���U�C�Ȥ����@��:
  *                 RCC_LSE_OFF: LSE ������ OFF
  *                 RCC_LSE_ON: LSE ������ ON
  *                 RCC_LSE_Bypass: LSE �������P�~�������Ǹ�
  * @��^  �S��
  */
void RCC_LSEConfig(uint8_t RCC_LSE)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_LSE(RCC_LSE));
  /* Reset LSEON and LSEBYP bits before configuring the LSE ------------------*/
  /* �_�� LSEON �� */
  *(__IO uint8_t *) BDCR_ADDRESS = RCC_LSE_OFF;
  /* �_�� LSEBYP �� */
  *(__IO uint8_t *) BDCR_ADDRESS = RCC_LSE_OFF;
  /* Configure LSE (RCC_LSE_OFF �w�g�b code �N�X�����Q�л\) */
  switch(RCC_LSE)
  {
    case RCC_LSE_ON:
      /* �]�m LSEON �� */
      *(__IO uint8_t *) BDCR_ADDRESS = RCC_LSE_ON;
      break;
      
    case RCC_LSE_Bypass:
      /* �]�m LSEBYP , LSEON �� */
      *(__IO uint8_t *) BDCR_ADDRESS = RCC_LSE_Bypass | RCC_LSE_ON;
      break;            
      
    default:
      break;      
  }
}

/**
  * @²�z  �ϯ�Υ��ऺ���C�t������ (LSI).
  * @����  �p�G IWDG ���b�B��ALSI �N����Q�T��.
  * @�Ѽ�  NewState: LSI �s�����A. �o�ӰѼƥi�H��: ENABLE �� DISABLE.
  * @��^  �S��
  */
void RCC_LSICmd(FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CSR_LSION_BB = (uint32_t)NewState;
}

/**
  * @²�z  �t�m RTC ���� (RTCCLK).
  * @����  �u�n��ܤF RTC ����,RTC�����N������ܪ���ƥ���_��.
  * @�Ѽ�  RCC_RTCCLKSource: ���w RTC ������.
  *                          �o�ӰѼƥi�H���U�C�Ȥ����@��:
  *                          RCC_RTCCLKSource_LSE: LSE �@�� RTC ����
  *                          RCC_RTCCLKSource_LSI: LSI �@�� RTC ����
  *                          RCC_RTCCLKSource_HSE_Div128: HSE ������ 128 ���W�@�� RTC ����
  * @��^  �S��
  */
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_RTCCLK_SOURCE(RCC_RTCCLKSource));
  /* ���w RTC ������ */
  RCC->BDCR |= RCC_RTCCLKSource;
}

/**
  * @²�z  �ϯ�Υ��� RTC ����.
  * @����  �ȷ�ϥ� RCC_RTCCLKConfig ��ƿ�� RTC ������,�~�ϥγo�Ө��.
  * @�Ѽ�  NewState: RTC �������s���A. �o�ӰѼƥi�H��: ENABLE �� DISABLE.
  * @��^  �S��
  */
void RCC_RTCCLKCmd(FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) BDCR_RTCEN_BB = (uint32_t)NewState;
}

/**
  * @²�z  ��^���W���������P�W�v.
  * @�Ѽ�  RCC_Clocks: ���V�]�A�����W�v�� RCC_ClocksTypeDef ���c�����w.
  * @��^  �S��
  */
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks)
{
  uint32_t tmp = 0, pllmull = 0, pllsource = 0, presc = 0;

#ifdef  STM32F10X_CL
  uint32_t prediv1source = 0, prediv1factor = 0, prediv2factor = 0, pll2mull = 0;
#endif /* STM32F10X_CL */
    
  /* �o��t�ή����� -------------------------------------------------------*/
  tmp = RCC->CFGR & CFGR_SWS_Mask;
  
  switch (tmp)
  {
    case 0x00:  /* HSI used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSI_Value;
      break;
    case 0x04:  /* HSE used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSE_Value;
      break;
    case 0x08:  /* PLL used as system clock */

      /* �o�� PLL �������M���W�]�� ----------------------*/
      pllmull = RCC->CFGR & CFGR_PLLMull_Mask;
      pllsource = RCC->CFGR & CFGR_PLLSRC_Mask;
      
#ifndef STM32F10X_CL      
      pllmull = ( pllmull >> 18) + 2;
      
      if (pllsource == 0x00)
      {/* HSI ����������2���W�@�� PLL ������ */
        RCC_Clocks->SYSCLK_Frequency = (HSI_Value >> 1) * pllmull;
      }
      else
      {/* HSE �@�� PLL ������ */
        if ((RCC->CFGR & CFGR_PLLXTPRE_Mask) != (uint32_t)RESET)
        {/* HSE ���������Q2���W */
          RCC_Clocks->SYSCLK_Frequency = (HSE_Value >> 1) * pllmull;
        }
        else
        {
          RCC_Clocks->SYSCLK_Frequency = HSE_Value * pllmull;
        }
      }
#else
      pllmull = pllmull >> 18;
      
      if (pllmull != 0x0D)
      {
         pllmull += 2;
      }
      else
      { /* PLL ���W�]�� = PLL ��J���� * 6.5 */
        pllmull = 13 / 2; 
      }
            
      if (pllsource == 0x00)
      {/* HSI ���������Q2���W�@�� PLL ������ */
        RCC_Clocks->SYSCLK_Frequency = (HSI_Value >> 1) * pllmull;
      }
      else
      {/* PREDIV1 �@�� PLL ������ */
        
        /* ���w PREDIV1 �������M���W�Y�� */
        prediv1source = RCC->CFGR2 & CFGR2_PREDIV1SRC;
        prediv1factor = (RCC->CFGR2 & CFGR2_PREDIV1) + 1;
        
        if (prediv1source == 0)
        { /* HSE ���������Q��w�@�� PREDIV1 ������ */
          RCC_Clocks->SYSCLK_Frequency = (HSE_Value / prediv1factor) * pllmull;          
        }
        else
        {/* PLL2 �����@�� PREDIV1 ������ */
          
          /* ���w PREDIV2 ���W�Y�� �M PLL2 ���W�Y�� */
          prediv2factor = ((RCC->CFGR2 & CFGR2_PREDIV2) >> 4) + 1;
          pll2mull = ((RCC->CFGR2 & CFGR2_PLL2MUL) >> 8 ) + 2; 
          RCC_Clocks->SYSCLK_Frequency = (((HSE_Value / prediv2factor) * pll2mull) / prediv1factor) * pllmull;                         
        }
      }
#endif /* STM32F10X_CL */ 
      break;

    default:
      RCC_Clocks->SYSCLK_Frequency = HSI_Value;
      break;
  }

  /* �p�� HCLK, PCLK1, PCLK2 , ADCCLK �����W�v ----------------*/
  /* �o�� HCLK �w���W�� */
  tmp = RCC->CFGR & CFGR_HPRE_Set_Mask;
  tmp = tmp >> 4;
  presc = APBAHBPrescTable[tmp];
  /* HCLK �����W�v */
  RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> presc;
  /* �o�� PCLK1 �w���W�� */
  tmp = RCC->CFGR & CFGR_PPRE1_Set_Mask;
  tmp = tmp >> 8;
  presc = APBAHBPrescTable[tmp];
  /* PCLK1 �����W�v */
  RCC_Clocks->PCLK1_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
  /* �o�� PCLK2 �w���W�� */
  tmp = RCC->CFGR & CFGR_PPRE2_Set_Mask;
  tmp = tmp >> 11;
  presc = APBAHBPrescTable[tmp];
  /* PCLK2 �����W�v */
  RCC_Clocks->PCLK2_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
  /* �o�� ADCCLK �w���W�� */
  tmp = RCC->CFGR & CFGR_ADCPRE_Set_Mask;
  tmp = tmp >> 14;
  presc = ADCPrescTable[tmp];
  /* ADCCLK �����W�v */
  RCC_Clocks->ADCCLK_Frequency = RCC_Clocks->PCLK2_Frequency / presc;
}

/**
  * @²�z  �ϯ�Υ��� AHB �~��]�Ʈ���.
  * @�Ѽ�  RCC_AHBPeriph: �Ω���������� AHB �~��]��.
  *   
  *        STM32_���pô�C�L�B�z��, �o�ӰѼƥi�H���U�C�Ȥ����@��:      
  *                                RCC_AHBPeriph_DMA1
  *                                RCC_AHBPeriph_DMA2
  *                                RCC_AHBPeriph_SRAM
  *                                RCC_AHBPeriph_FLITF
  *                                RCC_AHBPeriph_CRC
  *                                RCC_AHBPeriph_OTG_FS    
  *                                RCC_AHBPeriph_ETH_MAC   
  *                                RCC_AHBPeriph_ETH_MAC_Tx
  *                                RCC_AHBPeriph_ETH_MAC_Rx
  * 
  *           �䥦_STM32_�L�B�z��, �o�ӰѼƥi�H���U�C�Ȥ����@��:         
  *                                RCC_AHBPeriph_DMA1
  *                                RCC_AHBPeriph_DMA2
  *                                RCC_AHBPeriph_SRAM
  *                                RCC_AHBPeriph_FLITF
  *                                RCC_AHBPeriph_CRC
  *                                RCC_AHBPeriph_FSMC
  *                                RCC_AHBPeriph_SDIO
  *   
  * @����  SRAM �M FLITF �����u���b�ίv���Ҧ��U�i�H�L��.
  * @�Ѽ�  NewState: ���w�~��]�Ʈ����s�����A.
  *                  �o�ӰѼƥi�H��: ENABLE �� DISABLE.
  * @��^  �S��
  */
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_AHB_PERIPH(RCC_AHBPeriph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->AHBENR |= RCC_AHBPeriph;
  }
  else
  {
    RCC->AHBENR &= ~RCC_AHBPeriph;
  }
}

/**
  * @²�z  �ϯ�Υ��ప�t APB (APB2) �~��]�Ʈ���.
  * @�Ѽ�  RCC_APB2Periph: �Ω���������� AHB2 �~��]��.
  *                        �o�ӰѼƥi�H�O�U�����N�Ȫ��զX:
  *          RCC_APB2Periph_AFIO, RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB,
  *          RCC_APB2Periph_GPIOC, RCC_APB2Periph_GPIOD, RCC_APB2Periph_GPIOE,
  *          RCC_APB2Periph_GPIOF, RCC_APB2Periph_GPIOG, RCC_APB2Periph_ADC1,
  *          RCC_APB2Periph_ADC2, RCC_APB2Periph_TIM1, RCC_APB2Periph_SPI1,
  *          RCC_APB2Periph_TIM8, RCC_APB2Periph_USART1, RCC_APB2Periph_ADC3
  * @�Ѽ�  NewState: ���w�~��]�Ʈ������s���A.
  *                  �o�ӰѼƥi�H��: ENABLE �� DISABLE.
  * @��^  �S��
  */
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    RCC->APB2ENR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2ENR &= ~RCC_APB2Periph;
  }
}

/**
  * @²�z  �ϯ�Υ���C�t APB (APB1) �~��]�Ʈ���.
  * @�Ѽ�  RCC_APB1Periph: �Ω���������� APB1 �~��]��.
  *                        �o�ӰѼƥi�H�O�U�����N�Ȫ��զX:
  *          RCC_APB1Periph_TIM2, RCC_APB1Periph_TIM3, RCC_APB1Periph_TIM4,
  *          RCC_APB1Periph_TIM5, RCC_APB1Periph_TIM6, RCC_APB1Periph_TIM7,
  *          RCC_APB1Periph_WWDG, RCC_APB1Periph_SPI2, RCC_APB1Periph_SPI3,
  *          RCC_APB1Periph_USART2, RCC_APB1Periph_USART3, RCC_APB1Periph_USART4, 
  *          RCC_APB1Periph_USART5, RCC_APB1Periph_I2C1, RCC_APB1Periph_I2C2,
  *          RCC_APB1Periph_USB, RCC_APB1Periph_CAN1, RCC_APB1Periph_BKP,
  *          RCC_APB1Periph_PWR, RCC_APB1Periph_DAC
  * @�Ѽ�  NewState: ���w�~��]�Ʈ������s���A.
  *                  �o�ӰѼƥi�H��: ENABLE �� DISABLE.
  * @��^  �S��
  */
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    RCC->APB1ENR |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1ENR &= ~RCC_APB1Periph;
  }
}

#ifdef STM32F10X_CL
/**
  * @²�z  ��������� AHB �~��]�ƴ_��.
  * @����  �o�Ө�ƶȶ����Φb STM32 ���pô�C�L�B�z��.
  * @�Ѽ�  RCC_AHBPeriph: ���w�_�쪺�~��]��.
  *                       �o�ӰѼƥi�H�O�U�����N�Ȫ��զX:
  *                       RCC_AHBPeriph_OTG_FS 
  *                       RCC_AHBPeriph_ETH_MAC
  * @�Ѽ�  NewState: ���w�~��]�ƴ_�쪺�s���A.
  *                  �o�ӰѼƥi�H��: ENABLE �� DISABLE.
  * @��^  �S��
  */
void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_AHB_PERIPH_RESET(RCC_AHBPeriph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->AHBRSTR |= RCC_AHBPeriph;
  }
  else
  {
    RCC->AHBRSTR &= ~RCC_AHBPeriph;
  }
}
#endif /* STM32F10X_CL */ 

/**
  * @²�z  ��������񰪳t APB(APB2) �~��]�ƴ_��.
  * @�Ѽ�  RCC_APB2Periph: ���w�_�쪺 APB2 �~��]��.
  *                        �o�ӰѼƥi�H�O�U�����N�Ȫ��զX:
  *          RCC_APB2Periph_AFIO, RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB,
  *          RCC_APB2Periph_GPIOC, RCC_APB2Periph_GPIOD, RCC_APB2Periph_GPIOE,
  *          RCC_APB2Periph_GPIOF, RCC_APB2Periph_GPIOG, RCC_APB2Periph_ADC1,
  *          RCC_APB2Periph_ADC2, RCC_APB2Periph_TIM1, RCC_APB2Periph_SPI1,
  *          RCC_APB2Periph_TIM8, RCC_APB2Periph_USART1, RCC_APB2Periph_ADC3
  * @�Ѽ�  NewState: ���w�~��]�ƴ_�쪺�s���A.
  *                  �o�ӰѼƥi�H��: ENABLE �� DISABLE.
  * @��^  �S��
  */
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    RCC->APB2RSTR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2RSTR &= ~RCC_APB2Periph;
  }
}

/**
  * @²�z  ���������C�t APB(APB1) �~��]�ƴ_��.
  * @�Ѽ�  RCC_APB1Periph: ���w�_�쪺 APB1 �~��]��.
  *                        �o�ӰѼƥi�H�O�U�����N�Ȫ��զX:
  *          RCC_APB1Periph_TIM2, RCC_APB1Periph_TIM3, RCC_APB1Periph_TIM4,
  *          RCC_APB1Periph_TIM5, RCC_APB1Periph_TIM6, RCC_APB1Periph_TIM7,
  *          RCC_APB1Periph_WWDG, RCC_APB1Periph_SPI2, RCC_APB1Periph_SPI3,
  *          RCC_APB1Periph_USART2, RCC_APB1Periph_USART3, RCC_APB1Periph_USART4, 
  *          RCC_APB1Periph_USART5, RCC_APB1Periph_I2C1, RCC_APB1Periph_I2C2,
  *          RCC_APB1Periph_USB, RCC_APB1Periph_CAN1, RCC_APB1Periph_BKP,
  *          RCC_APB1Periph_PWR, RCC_APB1Periph_DAC
  * @�Ѽ�  NewState: ���w�~��]�ƴ_�쪺�s���A.
  *                  �o�ӰѼƥi�H��: ENABLE �� DISABLE.
  * @��^  �S��
  */
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    RCC->APB1RSTR |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1RSTR &= ~RCC_APB1Periph;
  }
}

/**
  * @²�z  ���������ƥ���_��.
  * @�Ѽ�  NewState: �ƥ���_�쪺�s���A.
  *                  �o�ӰѼƥi�H��: ENABLE �� DISABLE.
  * @��^  �S��
  */
void RCC_BackupResetCmd(FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) BDCR_BDRST_BB = (uint32_t)NewState;
}

/**
  * @²�z  �ϯ�Υ�������w���t��.
  * @�Ѽ�  NewState: �����w���t�Ϊ��s���A.
  *                  �o�ӰѼƥi�H��: ENABLE �� DISABLE.
  * @��^  �S��
  */
void RCC_ClockSecuritySystemCmd(FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CR_CSSON_BB = (uint32_t)NewState;
}

/**
  * @²�z  ��� MCO �޸}�W����X������.
  * @�Ѽ�  RCC_MCO: ���w�n��X��������.
  *   
  *        STM32_���pô�C�L�B�z��, �o�ӰѼƥi�H���U�C�Ȥ����@��:      
  *                                RCC_MCO_NoClock:      �S����ܮ���
  *                                RCC_MCO_SYSCLK:       ��ܨt�ή���
  *                                RCC_MCO_HSI:          ���HIS��������
  *                                RCC_MCO_HSE:          ���HSE��������
  *                                RCC_MCO_PLLCLK_Div2:  ���PLL��������W
  *                                RCC_MCO_PLL2CLK:      ���PLL2��������                    
  *                                RCC_MCO_PLL3CLK_Div2: ���PLL3��������W   
  *                                RCC_MCO_XT1:          ��ܥ~�� 3-25 MHz ��������  
  *                                RCC_MCO_PLL3CLK:      ���PLL3�������� 
  * 
  *           �䥦_STM32_�L�B�z��, �o�ӰѼƥi�H���U�C�Ȥ����@��:        
  *                                RCC_MCO_NoClock:      �S����ܮ���
  *                                RCC_MCO_SYSCLK:       ��ܨt�ή���
  *                                RCC_MCO_HSI:          ���HIS��������
  *                                RCC_MCO_HSE:          ���HSE��������
  *                                RCC_MCO_PLLCLK_Div2:  ���PLL��������W
  *   
  * @��^  �S��
  */
void RCC_MCOConfig(uint8_t RCC_MCO)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_MCO(RCC_MCO));

  /* ����MCO[2:0]�쪺�r�`�s���ӿ��MCO�� */
  *(__IO uint8_t *) CFGR_BYTE4_ADDRESS = RCC_MCO;
}

/**
  * @²�z  �ˬd���w�� RCC �лx�]�m�P�_.
  * @�Ѽ�  RCC_FLAG: ���w�n�ˬd���лx.
  *   
  *        STM32_���pô�C�L�B�z��, �o�ӰѼƥi�H���U�C�Ȥ����@��: 
  *                                RCC_FLAG_HSIRDY:  HSI ���������N��
  *                                RCC_FLAG_HSERDY:  HSE ���������N��
  *                                RCC_FLAG_PLLRDY:  PLL �����N��
  *                                RCC_FLAG_PLL2RDY: PLL2 �����N��    
  *                                RCC_FLAG_PLL3RDY: PLL3 �����N��                          
  *                                RCC_FLAG_LSERDY:  LSE ���������N��
  *                                RCC_FLAG_LSIRDY:  LSI ���������N��
  *                                RCC_FLAG_PINRST:  �޸}�_��
  *                                RCC_FLAG_PORRST:  POR/PDR�_��
  *                                RCC_FLAG_SFTRST:  �n��_��
  *                                RCC_FLAG_IWDGRST: �W�߬ݪ����_��
  *                                RCC_FLAG_WWDGRST: ���f�ݪ����_��
  *                                RCC_FLAG_LPWRRST: �C�q�q�_��
  * 
  *           �䥦_STM32_�L�B�z��, �o�ӰѼƥi�H���U�C�Ȥ����@��:            
  *                                RCC_FLAG_HSIRDY:  HSI ���������N��
  *                                RCC_FLAG_HSERDY:  HSE ���������N��
  *                                RCC_FLAG_PLLRDY:  PLL �����N��
  *                                RCC_FLAG_LSERDY:  LSE ���������N��
  *                                RCC_FLAG_LSIRDY:  LSI ���������N��
  *                                RCC_FLAG_PINRST:  �޸}�_��
  *                                RCC_FLAG_PORRST:  POR/PDR�_��
  *                                RCC_FLAG_SFTRST:  �n��_��
  *                                RCC_FLAG_IWDGRST: �W�߬ݪ����_��
  *                                RCC_FLAG_WWDGRST: ���f�ݪ����_��
  *                                RCC_FLAG_LPWRRST: �C�q�q�_��
  *   
  * @��^  RCC_FLAG ���s���A(SET��RESET).
  */
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG)
{
  uint32_t tmp = 0;
  uint32_t statusreg = 0;
  FlagStatus bitstatus = RESET;
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_FLAG(RCC_FLAG));

  /* ���o RCC �H�s���ޯ� */
  tmp = RCC_FLAG >> 5;
  if (tmp == 1)               /* CR �H�s�������ˬd�лx */
  {
    statusreg = RCC->CR;
  }
  else if (tmp == 2)          /* BDCR �H�s�������ˬd�лx */
  {
    statusreg = RCC->BDCR;
  }
  else                       /* CSR �H�s�������ˬd�лx */
  {
    statusreg = RCC->CSR;
  }

  /* ���o�лx����m */
  tmp = RCC_FLAG & FLAG_Mask;
  if ((statusreg & ((uint32_t)1 << tmp)) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  /* ��^�лx�����A */
  return bitstatus;
}

/**
  * @²�z  �M�� RCC �_��лx.
  * @����   �o�Ǵ_��лx�O: RCC_FLAG_PINRST, RCC_FLAG_PORRST, RCC_FLAG_SFTRST,
  *                         RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST, RCC_FLAG_LPWRRST
  * @�Ѽ�  �S��
  * @��^  �S��
  */
void RCC_ClearFlag(void)
{
  /* �q�L�m�� RMVF ��ӲM���_��лx */
  RCC->CSR |= CSR_RMVF_Set;
}

/**
  * @²�z  �ˬd���w�� RCC ���_�O�_�o��.
  * @�Ѽ�  RCC_IT: ���w�ˬd RCC ���_��.
  *   
  *        STM32_���pô�C�L�B�z��, �o�ӰѼƥi�H���U�C�Ȥ����@��: 
  *                                RCC_IT_LSIRDY:  LSI �N�����_
  *                                RCC_IT_LSERDY:  LSE �N�����_
  *                                RCC_IT_HSIRDY:  HSI �N�����_
  *                                RCC_IT_HSERDY:  HSE �N�����_
  *                                RCC_IT_PLLRDY:  PLL �N�����_
  *                                RCC_IT_PLL2RDY: PLL2 �N�����_ 
  *                                RCC_IT_PLL3RDY: PLL3 �N�����_                    
  *                                RCC_IT_CSS:     �����w���t�Τ��_
  * 
  *           �䥦_STM32_�L�B�z��, �o�ӰѼƥi�H���U�C�Ȥ����@��:      
  *                                RCC_IT_LSIRDY: LSI �N�����_
  *                                RCC_IT_LSERDY: LSE �N�����_
  *                                RCC_IT_HSIRDY: HSI �N�����_
  *                                RCC_IT_HSERDY: HSE �N�����_
  *                                RCC_IT_PLLRDY: PLL �N�����_
  *                                RCC_IT_CSS:    �����w���t�Τ��_
  *   
  * @��^  RCC_IT ���s���A(SETorRESET).
  */
ITStatus RCC_GetITStatus(uint8_t RCC_IT)
{
  ITStatus bitstatus = RESET;
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_GET_IT(RCC_IT));

  /* �ˬd���w�� RCC ���_���A */
  if ((RCC->CIR & RCC_IT) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  /* ��^ RCC_IT ���A */
  return  bitstatus;
}

/**
  * @²�z  �M�� RCC ���_���_��.
  * @�Ѽ�  RCC_IT: ���w�n�M�������_���_��.
  *   
  *        STM32_���pô�C�L�B�z��, �o�ӰѼƥi�H���U�C�Ȥ����@��: 
  *                                RCC_IT_LSIRDY:  LSI �N�����_
  *                                RCC_IT_LSERDY:  LSE �N�����_
  *                                RCC_IT_HSIRDY:  HSI �N�����_
  *                                RCC_IT_HSERDY:  HSE �N�����_
  *                                RCC_IT_PLLRDY:  PLL �N�����_
  *                                RCC_IT_PLL2RDY: PLL2 �N�����_
  *                                RCC_IT_PLL3RDY: PLL3 �N�����_                      
  *                                RCC_IT_CSS:     �����w���t�Τ��_
  * 
  *           �䥦_STM32_�L�B�z��, �o�ӰѼƥi�H���U�C�Ȥ����@��:           
  *                                RCC_IT_LSIRDY:  LSI �N�����_
  *                                RCC_IT_LSERDY:  LSE �N�����_
  *                                RCC_IT_HSIRDY:  HSI �N�����_
  *                                RCC_IT_HSERDY:  HSE �N�����_
  *                                RCC_IT_PLLRDY:  PLL �N�����_
  *                                RCC_IT_CSS:     �����w���t�Τ��_
  * @��^  �S��
  */
void RCC_ClearITPendingBit(uint8_t RCC_IT)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_RCC_CLEAR_IT(RCC_IT));

  /* ���� RCC_CIR[23:16] �쪺�r�`�s���ӲM����ܪ����_���_��*/
  *(__IO uint8_t *) CIR_BYTE3_ADDRESS = RCC_IT;
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
