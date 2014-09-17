/**
  ******************************************************************************
  * @���    stm32f10x_usart.c
  * @�@��    MCD ���ε{�ǲ�
  * @����    V3.1.0
  * @���    06/19/2009
  * @²�z    �o�Ӥ�� ���ѩҦ� USART �T����.
  * @½Ķ    ANSON/sweet1985 Email:airanson110@126.com
  * @���    14/07/2009
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
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"

/* �ۥ����� --------------------------------------------------------------*/
/* �ۥΩw�q --------------------------------------------------------------*/

#define CR1_UE_Set                ((uint16_t)0x2000)  /*!< USART Enable Mask */
#define CR1_UE_Reset              ((uint16_t)0xDFFF)  /*!< USART Disable Mask */

#define CR1_WAKE_Mask             ((uint16_t)0xF7FF)  /*!< USART WakeUp Method Mask */

#define CR1_RWU_Set               ((uint16_t)0x0002)  /*!< USART mute mode Enable Mask */
#define CR1_RWU_Reset             ((uint16_t)0xFFFD)  /*!< USART mute mode Enable Mask */
#define CR1_SBK_Set               ((uint16_t)0x0001)  /*!< USART Break Character send Mask */
#define CR1_CLEAR_Mask            ((uint16_t)0xE9F3)  /*!< USART CR1 Mask */
#define CR2_Address_Mask          ((uint16_t)0xFFF0)  /*!< USART address Mask */

#define CR2_LINEN_Set              ((uint16_t)0x4000)  /*!< USART LIN Enable Mask */
#define CR2_LINEN_Reset            ((uint16_t)0xBFFF)  /*!< USART LIN Disable Mask */

#define CR2_LBDL_Mask             ((uint16_t)0xFFDF)  /*!< USART LIN Break detection Mask */
#define CR2_STOP_CLEAR_Mask       ((uint16_t)0xCFFF)  /*!< USART CR2 STOP Bits Mask */
#define CR2_CLOCK_CLEAR_Mask      ((uint16_t)0xF0FF)  /*!< USART CR2 Clock Mask */

#define CR3_SCEN_Set              ((uint16_t)0x0020)  /*!< USART SC Enable Mask */
#define CR3_SCEN_Reset            ((uint16_t)0xFFDF)  /*!< USART SC Disable Mask */

#define CR3_NACK_Set              ((uint16_t)0x0010)  /*!< USART SC NACK Enable Mask */
#define CR3_NACK_Reset            ((uint16_t)0xFFEF)  /*!< USART SC NACK Disable Mask */

#define CR3_HDSEL_Set             ((uint16_t)0x0008)  /*!< USART Half-Duplex Enable Mask */
#define CR3_HDSEL_Reset           ((uint16_t)0xFFF7)  /*!< USART Half-Duplex Disable Mask */

#define CR3_IRLP_Mask             ((uint16_t)0xFFFB)  /*!< USART IrDA LowPower mode Mask */
#define CR3_CLEAR_Mask            ((uint16_t)0xFCFF)  /*!< USART CR3 Mask */

#define CR3_IREN_Set              ((uint16_t)0x0002)  /*!< USART IrDA Enable Mask */
#define CR3_IREN_Reset            ((uint16_t)0xFFFD)  /*!< USART IrDA Disable Mask */
#define GTPR_LSB_Mask             ((uint16_t)0x00FF)  /*!< Guard Time Register LSB Mask */
#define GTPR_MSB_Mask             ((uint16_t)0xFF00)  /*!< Guard Time Register MSB Mask */
#define IT_Mask                   ((uint16_t)0x001F)  /*!< USART Interrupt Mask */

/* �ۥΧ� -------------------------------------------------------------*/
/* �ۥ��ܶq -----------------------------------------------------------*/
/* �ۥΨ�ƭ쫬 -------------------------------------------------------*/
/* �ۥΨ�� -----------------------------------------------------------*/

/**
  * @²�z  �N�~�] USARTx �H�s�����]���ʬ٭�.
  * @�Ѽ�  USARTx: ��� USART �~��]��. 
  *                �o�ӰѼƥi�H���U�C�Ȥ��@: USART1, USART2, USART3, UART4 �� UART5.
  * @��^  �S��
  */
void USART_DeInit(USART_TypeDef* USARTx)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_ALL_PERIPH(USARTx));

  if (USARTx == USART1)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, DISABLE);
  }
  else if (USARTx == USART2)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, DISABLE);
  }
  else if (USARTx == USART3)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, DISABLE);
  }    
  else if (USARTx == UART4)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4, DISABLE);
  }    
  else
  {
    if (USARTx == UART5)
    { 
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5, ENABLE);
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5, DISABLE);
    }
  }
}

/**
  * @²�z  �ھ� USART_InitStruct �����w���Ѽƪ�l�ƥ~�] USARTx �H�s��.
  * @�Ѽ�  USARTx: ��� USART �~��]��. 
  *                �o�ӰѼƥi�H���U�C�Ȥ��@: USART1, USART2, USART3, UART4 �� UART5.
  * @�Ѽ�  USART_InitStruct: ���V���c USART_InitTypeDef �����w�A�]�t�F�~�] USART ���t�m�H��.
  * @��^  �S��
  */
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct)
{
  uint32_t tmpreg = 0x00, apbclock = 0x00;
  uint32_t integerdivider = 0x00;
  uint32_t fractionaldivider = 0x00;
  uint32_t usartxbase = 0;
  RCC_ClocksTypeDef RCC_ClocksStatus;
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_BAUDRATE(USART_InitStruct->USART_BaudRate));  
  assert_param(IS_USART_WORD_LENGTH(USART_InitStruct->USART_WordLength));
  assert_param(IS_USART_STOPBITS(USART_InitStruct->USART_StopBits));
  assert_param(IS_USART_PARITY(USART_InitStruct->USART_Parity));
  assert_param(IS_USART_MODE(USART_InitStruct->USART_Mode));
  assert_param(IS_USART_HARDWARE_FLOW_CONTROL(USART_InitStruct->USART_HardwareFlowControl));
  /* The hardware flow control is available only for USART1, USART2 and USART3 */
  if (USART_InitStruct->USART_HardwareFlowControl != USART_HardwareFlowControl_None)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  }

  usartxbase = (uint32_t)USARTx;

/*---------------------------- USART CR2 Configuration -----------------------*/
  tmpreg = USARTx->CR2;
  /* �M�� STOP[13:12] �� */
  tmpreg &= CR2_STOP_CLEAR_Mask;
  /* �t�m USART ������, ����, ��������, �����ۦ� �M ���� ------------*/
  /* �]�m STOP[13:12] ��A���� USART_StopBits ���� */
  tmpreg |= (uint32_t)USART_InitStruct->USART_StopBits;
  
  /* �g USART CR2 */
  USARTx->CR2 = (uint16_t)tmpreg;

/*---------------------------- USART CR1 Configuration -----------------------*/
  tmpreg = USARTx->CR1;
  /* �M�� M, PCE, PS, TE �M RE �� */
  tmpreg &= CR1_CLEAR_Mask;
  /* �t�m USART �r��, �_�� �M �Ҧ� ----------------------- */
  /* �]�m M   ��A���� USART_WordLength ���� */
  /* �]�m PCE �M PS ��A���� USART_Parity ���� */
  /* �]�m TE  �M RE ��A���� USART_Mode ���� */
  tmpreg |= (uint32_t)USART_InitStruct->USART_WordLength | USART_InitStruct->USART_Parity |
            USART_InitStruct->USART_Mode;
  /* �g USART CR1 */
  USARTx->CR1 = (uint16_t)tmpreg;

/*---------------------------- USART CR3 Configuration -----------------------*/  
  tmpreg = USARTx->CR3;
  /* �M�� CTSE �M RTSE �� */
  tmpreg &= CR3_CLEAR_Mask;
  /* �t�m USART HFC -------------------------------------------------*/
  /* �]�m CTSE �M RTSE ��A���� USART_HardwareFlowControl ���� */
  tmpreg |= USART_InitStruct->USART_HardwareFlowControl;
  /* �g USART CR3 */
  USARTx->CR3 = (uint16_t)tmpreg;

/*---------------------------- USART BRR Configuration -----------------------*/
  /* �t�m USART �i�S�v -------------------------------------------*/
  RCC_GetClocksFreq(&RCC_ClocksStatus);
  if (usartxbase == USART1_BASE)
  {
    apbclock = RCC_ClocksStatus.PCLK2_Frequency;
  }
  else
  {
    apbclock = RCC_ClocksStatus.PCLK1_Frequency;
  }
  /* �T�w��Ƴ��� */
  integerdivider = ((0x19 * apbclock) / (0x04 * (USART_InitStruct->USART_BaudRate)));
  tmpreg = (integerdivider / 0x64) << 0x04;
  /* �T�w���Ƴ��� */
  fractionaldivider = integerdivider - (0x64 * (tmpreg >> 0x04));
  tmpreg |= ((((fractionaldivider * 0x10) + 0x32) / 0x64)) & ((uint8_t)0x0F);
  /* �g USART BRR */
  USARTx->BRR = (uint16_t)tmpreg;
}

/**
  * @²�z  �� USART_InitStruct �����C�@�ӰѼƫ��ʬ٭ȶ�J.
  * @�Ѽ�  USART_InitStruct: ���V���c USART_InitTypeDef �����w�A�ݪ�l��.
  * @��^  �S��
  */
void USART_StructInit(USART_InitTypeDef* USART_InitStruct)
{
  /* USART_InitStruct ���c�骺�ʬ٭� */
  USART_InitStruct->USART_BaudRate = 9600;
  USART_InitStruct->USART_WordLength = USART_WordLength_8b;
  USART_InitStruct->USART_StopBits = USART_StopBits_1;
  USART_InitStruct->USART_Parity = USART_Parity_No ;
  USART_InitStruct->USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct->USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
}

/**
  * @²�z  ��l�� USARTx �~������A���� USART_ClockInitStruct �����Ѽ�.
  * @�Ѽ�  USARTx: �o��x�i�H�� 1, 2, 3 �ӿ�� USART �~��]��.
  * @�Ѽ�  USART_ClockInitStruct: ���V USART_ClockInitTypeDef �����w�A�]�t�F�~�] USART ���t�m�H��.  
  * @����  �o�Ӵ���d�Ҧ��������Ω� UART4 �M UART5.
  * @��^  �S��
  */
void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct)
{
  uint32_t tmpreg = 0x00;
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_USART_CLOCK(USART_ClockInitStruct->USART_Clock));
  assert_param(IS_USART_CPOL(USART_ClockInitStruct->USART_CPOL));
  assert_param(IS_USART_CPHA(USART_ClockInitStruct->USART_CPHA));
  assert_param(IS_USART_LASTBIT(USART_ClockInitStruct->USART_LastBit));
  
/*---------------------------- USART CR2 Configuration -----------------------*/
  tmpreg = USARTx->CR2;
  /* �M�� CLKEN, CPOL, CPHA �M LBCL �� */
  tmpreg &= CR2_CLOCK_CLEAR_Mask;
  /* �t�m USART Clock, CPOL, CPHA and LastBit ------------*/
  /* �]�m CLKEN ��A���� USART_Clock ���� */
  /* �]�m CPOL  ��A���� USART_CPOL ���� */
  /* �]�m CPHA  ��A���� USART_CPHA ���� */
  /* �]�m LBCL  ��A���� USART_LastBit ���� */
  tmpreg |= (uint32_t)USART_ClockInitStruct->USART_Clock | USART_ClockInitStruct->USART_CPOL | 
                 USART_ClockInitStruct->USART_CPHA | USART_ClockInitStruct->USART_LastBit;
  /* �g USART CR2 */
  USARTx->CR2 = (uint16_t)tmpreg;
}

/**
  * @²�z  ���q�{�ȶ�R�C�@�� USART_ClockInitStruct ������.
  * @�Ѽ�  USART_ClockInitStruct: ���V USART_ClockInitTypeDef ���c�����w�A�Ω��l��.
  * @��^  �S��
  */
void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct)
{
  /* USART_ClockInitStruct ���c�骺�ʬ٭� */
  USART_ClockInitStruct->USART_Clock = USART_Clock_Disable;
  USART_ClockInitStruct->USART_CPOL = USART_CPOL_Low;
  USART_ClockInitStruct->USART_CPHA = USART_CPHA_1Edge;
  USART_ClockInitStruct->USART_LastBit = USART_LastBit_Disable;
}

/**
  * @²�z  �ϯ�Ϊ̥��� USART �~�].
  * @�Ѽ�  USARTx: ��� USART �Ϊ� UART ���~��]��. 
  *                �o�ӰѼƥi�H�O�U�����Ȥ��@ : USART1, USART2, USART3, UART4 �� UART5.
  * @�Ѽ�  NewState: USARTx �~��]�ƪ��s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE or DISABLE.
  * @��^  �S��
  */
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected USART by setting the UE bit in the CR1 register */
    USARTx->CR1 |= CR1_UE_Set;
  }
  else
  {
    /* Disable the selected USART by clearing the UE bit in the CR1 register */
    USARTx->CR1 &= CR1_UE_Reset;
  }
}

/**
  * @²�z  �ϯ�Ϊ̥�����w�� USART ���_.
  * @�Ѽ�  USARTx: ��� USART �Ϊ� UART ���~��]��. 
  *                �o�ӰѼƥi�H�O�U�����Ȥ��@ : USART1, USART2, USART3, UART4 or UART5.
  * @�Ѽ�  USART_IT: ���w�n�ϯ�Υ��઺ USART ���_��.
  *          �o�ӰѼƥi�H�O�U�����Ȥ��@ :
  *          USART_IT_CTS:  CTS ���ܤ��_ (�������Ω� UART4 �M UART5)
  *          USART_IT_LBD:  LIN ���j�������_
  *          USART_IT_TXE:  �ǿ�ƾڱH�s���Ť��_
  *          USART_IT_TC:   �ǿ駹�����_
  *          USART_IT_RXNE: �����ƾڱH�s�������Ť��_
  *          USART_IT_IDLE: �Ŷ��`�u���_
  *          USART_IT_PE:   �_�����~���_
  *          USART_IT_ERR:  ���~���_(�����~, ���n���~, ���X���~)
  * @�Ѽ�  NewState: ���w�� USARTx ���_���s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState)
{
  uint32_t usartreg = 0x00, itpos = 0x00, itmask = 0x00;
  uint32_t usartxbase = 0x00;
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CONFIG_IT(USART_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  /* CTS ���_�������Ω� UART4 �M UART5 */
  if (USART_IT == USART_IT_CTS)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  }   
  
  usartxbase = (uint32_t)USARTx;

  /* �o�� USART �H�s���ܧ} */
  usartreg = (((uint8_t)USART_IT) >> 0x05);

  /* �o�줤�_��m */
  itpos = USART_IT & IT_Mask;
  itmask = (((uint32_t)0x01) << itpos);
    
  if (usartreg == 0x01) /* The IT is in CR1 register */
  {
    usartxbase += 0x0C;
  }
  else if (usartreg == 0x02) /* The IT is in CR2 register */
  {
    usartxbase += 0x10;
  }
  else /* The IT is in CR3 register */
  {
    usartxbase += 0x14; 
  }
  if (NewState != DISABLE)
  {
    *(__IO uint32_t*)usartxbase  |= itmask;
  }
  else
  {
    *(__IO uint32_t*)usartxbase &= ~itmask;
  }
}

/**
  * @²�z  �ϯ�Ϊ̥�����w USART �� DMA �ШD.
  * @�Ѽ�  USARTx: ��� USART �Ϊ� UART ���~��]��. 
  *                �o�ӰѼƥi�H�O�U�����Ȥ��@ : USART1, USART2, USART3 or UART4.  
  * @�Ѽ�  USART_DMAReq:���w DMA �ШD.
  *          �o�ӰѼƥi�H�O�U�����N�Ȫ��զX:
  *          USART_DMAReq_Tx: USART DMA �ǿ�ШD
  *          USART_DMAReq_Rx: USART DMA �����ШD
  * @�Ѽ�  NewState: DMA �ШD�����s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @����  DMA �Ҧ��������Ω� UART5.  
  * @��^  �S��
  */
void USART_DMACmd(USART_TypeDef* USARTx, uint16_t USART_DMAReq, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_1234_PERIPH(USARTx));
  assert_param(IS_USART_DMAREQ(USART_DMAReq));  
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 
  if (NewState != DISABLE)
  {
    /* �q�L�]�mUSART CR3 �H�s����DMAT�BDMAT��զX,�Өϯ���DMA�ǿ�ШD */
    USARTx->CR3 |= USART_DMAReq;
  }
  else
  {
    /* �q�L�]�mUSART CR3 �H�s����DMAT�BDMAT��զX,�ӥ�����DMA�ǿ�ШD */
    USARTx->CR3 &= (uint16_t)~USART_DMAReq;
  }
}

/**
  * @²�z  �]�m USART �`�I���a�}.
  * @�Ѽ�  USARTx: ��� USART �Ϊ� UART ���~��]��. 
  *                �o�ӰѼƥi�H�O�U�����Ȥ��@ : USART1, USART2, USART3, UART4 or UART5.
  * @�Ѽ�  USART_Address: �]�m USART �`�I���a�}.
  * @��^  �S��
  */ 
void USART_SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_ADDRESS(USART_Address)); 
    
  /* �M�� USART �a�} */
  USARTx->CR2 &= CR2_Address_Mask;
  /* �]�m USART �`�I���a�} */
  USARTx->CR2 |= USART_Address;
}

/**
  * @²�z  ��� USART ������覡.
  * @�Ѽ�  USARTx: ��� USART �Ϊ� UART ���~��]��. 
  *                �o�ӰѼƥi�H�O�U�����Ȥ��@ : USART1, USART2, USART3, UART4 or UART5.
  * @�Ѽ�  USART_WakeUp: ���w USART ������覡.
  *          �o�ӰѼƥi�H�O�U�����Ȥ��@ :
  *          USART_WakeUp_IdleLine:    �Ŷ��`�u���
  *          USART_WakeUp_AddressMark: �a�}�аO���
  * @��^  �S��
  */
void USART_WakeUpConfig(USART_TypeDef* USARTx, uint16_t USART_WakeUp)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_WAKEUP(USART_WakeUp));
  
  USARTx->CR1 &= CR1_WAKE_Mask;
  USARTx->CR1 |= USART_WakeUp;
}

/**
  * @²�z  �ˬd USART �O�_�B���R�q�Ҧ�.
  * @�Ѽ�  USARTx: ��� USART �Ϊ� UART ���~��]��. 
  *                �o�ӰѼƥi�H�O�U�����Ȥ��@ : USART1, USART2, USART3, UART4 or UART5.
  * @�Ѽ�  NewState: USART �R�q�Ҧ����s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void USART_ReceiverWakeUpCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 
  
  if (NewState != DISABLE)
  {
    /* �q�L�m��CR1�H�s����RWU��ϯ�USART�R���Ҧ� */
    USARTx->CR1 |= CR1_RWU_Set;
  }
  else
  {
    /* �q�L�M�sCR1�H�s����RWU�쥢��USART�R���Ҧ� */
    USARTx->CR1 &= CR1_RWU_Reset;
  }
}

/**
  * @²�z  �]�m USART LIN ���_�˴�����.
  * @�Ѽ�  USARTx: ��� USART �Ϊ� UART ���~��]��. 
  *                �o�ӰѼƥi�H�O�U�����Ȥ��@ : USART1, USART2, USART3, UART4 �� UART5.
  * @�Ѽ�  USART_LINBreakDetectLength: LIN ���_�˴�����.
  *          �o�ӰѼƥi�H�O�U�����Ȥ��@ :
  *          USART_LINBreakDetectLength_10b: 10�춡�_�˴�
  *          USART_LINBreakDetectLength_11b: 11�춡�_�˴�
  * @��^  �S��
  */
void USART_LINBreakDetectLengthConfig(USART_TypeDef* USARTx, uint16_t USART_LINBreakDetectLength)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_LIN_BREAK_DETECT_LENGTH(USART_LINBreakDetectLength));
  
  USARTx->CR2 &= CR2_LBDL_Mask;
  USARTx->CR2 |= USART_LINBreakDetectLength;  
}

/**
  * @²�z  �ϯ�Ϊ̥��� USARTx �� LIN �Ҧ�.
  * @�Ѽ�  USARTx: ��� USART �Ϊ� UART ���~��]��. 
  *                �o�ӰѼƥi�H�O�U�����Ȥ��@ : USART1, USART2, USART3, UART4 or UART5.
  * @�Ѽ�  NewState: USART LIN �Ҧ����s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE or DISABLE.
  * @��^  �S��
  */
void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* �q�L�m��CR2�H�s����LINEN��ϯ�LIN�Ҧ� */
    USARTx->CR2 |= CR2_LINEN_Set;
  }
  else
  {
    /* �q�L�M�sCR2�H�s����LINEN�쥢��LIN�Ҧ� */
    USARTx->CR2 &= CR2_LINEN_Reset;
  }
}

/**
  * @²�z  �q�L�~�] USARTx �o�e��Ӽƾ�.
  * @�Ѽ�  USARTx: ��� USART �Ϊ� UART ���~��]��.
  *                �o�ӰѼƥi�H�O�U�����Ȥ��@ : USART1, USART2, USART3, UART4 �� UART5.
  * @�Ѽ�  Data: �n�o�e���ƾ�.
  * @��^  �S��
  */
void USART_SendData(USART_TypeDef* USARTx, uint16_t Data)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DATA(Data)); 
    
  /* �o�e�ƾ� */
  USARTx->DR = (Data & (uint16_t)0x01FF);
}

/**
  * @²�z  ��^ USARTx �̪񱵦��쪺�ƾ�.
  * @�Ѽ�  USARTx: ��� USART �Ϊ� UART ���~��]��.
  *                �o�ӰѼƥi�H�O�U�����Ȥ��@ : USART1, USART2, USART3, UART4 �� UART5.
  * @��^  �����ƾ�.
  */
uint16_t USART_ReceiveData(USART_TypeDef* USARTx)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  
  /* �����ƾ� */
  return (uint16_t)(USARTx->DR & (uint16_t)0x01FF);
}

/**
  * @²�z  �o�e���_�r.
  * @�Ѽ�  USARTx: ��� USART �Ϊ� UART ���~��]��. 
  *                �o�ӰѼƥi�H�O�U�����Ȥ��@ : USART1, USART2, USART3, UART4 �� UART5.
  * @��^  �S��
  */
void USART_SendBreak(USART_TypeDef* USARTx)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  
  /* �o�e���_�r */
  USARTx->CR1 |= CR1_SBK_Set;
}

/**
  * @²�z  �]�m���w�� USART �O�@�ɶ�.
  * @�Ѽ�  USARTx: x�i�H��1,2��3�H���USART���~��]��.
  * @�Ѽ�  USART_GuardTime: ���w���O�@�ɶ�.
  * @����  �o�ӫO�@�ɶ��줣�����Ω� UART4 �M UART5.   
  * @��^  �S��
  */
void USART_SetGuardTime(USART_TypeDef* USARTx, uint8_t USART_GuardTime)
{    
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_123_PERIPH(USARTx));
  
  /* �M�� USART �O�@�ɶ� */
  USARTx->GTPR &= GTPR_LSB_Mask;
  /* �]�m USART �O�@�ɶ� */
  USARTx->GTPR |= (uint16_t)((uint16_t)USART_GuardTime << 0x08);
}

/**
  * @²�z  �]�m USART �����w���W.
  * @�Ѽ�  USARTx: ��� USART �Ϊ� UART ���~��]��. 
  *                �o�ӰѼƥi�H�O�U�����Ȥ��@ : USART1, USART2, USART3, UART4 or UART5.
  * @�Ѽ�  USART_Prescaler: ���w�w���W��.  
  * @����  �o�Ө�ƬO�Ω� UART4 �M UART5 �� IrDA �Ҧ�.
  * @��^  �S��
  */
void USART_SetPrescaler(USART_TypeDef* USARTx, uint8_t USART_Prescaler)
{ 
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  
  /* �M�� USART �w���W�� */
  USARTx->GTPR &= GTPR_MSB_Mask;
  /* �]�m USART �w���W�� */
  USARTx->GTPR |= USART_Prescaler;
}

/**
  * @²�z  �ϯ�Ϊ̥�����w USART ������d�Ҧ�.
  * @�Ѽ�  USARTx: x�i�H��1,2��3�H���USART���~��]��.
  * @�Ѽ�  NewState: USART ����d�Ҧ����s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.     
  * @����  �o�Ӵ���d�Ҧ��������Ω� UART4 �M UART5 . 
  * @��^  �S��
  */
void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �q�L�m��CR3�H�s����SCEN��ϯ�SC�Ҧ� */
    USARTx->CR3 |= CR3_SCEN_Set;
  }
  else
  {
    /* �q�L�M�sCR3�H�s����SCEN�쥢��SC�Ҧ� */
    USARTx->CR3 &= CR3_SCEN_Reset;
  }
}

/**
  * @²�z  �ϯ�Ϊ̥��� NACK �ǿ�.
  * @�Ѽ�  USARTx: x�i�H��1,2��3�H���USART���~��]��. 
  * @�Ѽ�  NewState: NACK �ǿ骺�s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.  
  * @����  �o�Ӵ���d�Ҧ��������Ω� UART4 �M UART5 .
  * @��^  �S��
  */
void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_123_PERIPH(USARTx));  
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �q�L�m��CR3�H�s����NACK��ϯ�NACK�ǿ� */
    USARTx->CR3 |= CR3_NACK_Set;
  }
  else
  {
    /* �q�L�M�sCR3�H�s����NACK�쥢��NACK�ǿ� */
    USARTx->CR3 &= CR3_NACK_Reset;
  }
}

/**
  * @²�z  �ϯ�Ϊ̥��� USART �b���u�Ҧ�.
  * @�Ѽ�  USARTx: ��� USART �Ϊ� UART ���~��]��. 
  *                �o�ӰѼƥi�H�O�U�����Ȥ��@ : USART1, USART2, USART3, UART4 or UART5.
  * @�Ѽ�  NewState: USART �b���u�Ҧ����s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* �q�L�m��CR3�H�s����HDSEL��ϯ�Half-Duplex�Ҧ� */
    USARTx->CR3 |= CR3_HDSEL_Set;
  }
  else
  {
    /* �q�L�M�sCR3�H�s����HDSEL�쥢��Half-Duplex�Ҧ� */
    USARTx->CR3 &= CR3_HDSEL_Reset;
  }
}

/**
  * @²�z  �]�m USART IrDA �Ҧ�.
  * @�Ѽ�  USARTx: ��� USART �Ϊ� UART ���~��]��. 
  *                �o�ӰѼƥi�H�O�U�����Ȥ��@ : USART1, USART2, USART3, UART4 �� UART5.
  * @�Ѽ�  USART_IrDAMode: ���w IrDA �Ҧ�.
  *                        �o�ӰѼƥi�H�O�U�����Ȥ��@ :
  *                        USART_IrDAMode_LowPower: �C�\�ӼҦ�
  *                        USART_IrDAMode_Normal  : ���`�Ҧ�
  * @��^  �S��
  */
void USART_IrDAConfig(USART_TypeDef* USARTx, uint16_t USART_IrDAMode)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_IRDA_MODE(USART_IrDAMode));
    
  USARTx->CR3 &= CR3_IRLP_Mask;
  USARTx->CR3 |= USART_IrDAMode;
}

/**
  * @²�z  �ϯ�Ϊ̥��� USART IrDA �Ҧ�.
  * @�Ѽ�  USARTx: ��� USART �Ϊ� UART ���~��]��.
  *                �o�ӰѼƥi�H�O�U�����Ȥ��@ : USART1, USART2, USART3, UART4 �� UART5.
  * @�Ѽ�  NewState: IrDA �Ҧ����s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
    
  if (NewState != DISABLE)
  {
    /* �q�L�m��CR3�H�s����IREN��ϯ�IrDA�Ҧ� */
    USARTx->CR3 |= CR3_IREN_Set;
  }
  else
  {
    /* �q�L�M�sCR3�H�s����IREN�쥢��IrDA�Ҧ� */
    USARTx->CR3 &= CR3_IREN_Reset;
  }
}

/**
  * @²�z  �ˬd���w�� USART �лx��]�m�P�_.
  * @�Ѽ�  USARTx: ��� USART �Ϊ� UART ���~��]��. 
  *                �o�ӰѼƥi�H�O�U�����Ȥ��@ : USART1, USART2, USART3, UART4 or UART5.
  * @�Ѽ�  USART_FLAG: ���w�n�˴����аO.
  *          �o�ӰѼƥi�H�O�U�����Ȥ��@ :
  *          USART_FLAG_CTS:  CTS ���ܼлx (�������Ω� UART4 �M UART5)
  *          USART_FLAG_LBD:  LIN ���j�����лx
  *          USART_FLAG_TXE:  �o�e�ƾڱH�s�����żлx
  *          USART_FLAG_TC:   �ǿ駹���лx
  *          USART_FLAG_RXNE: �����ƾڱH�s�������żлx
  *          USART_FLAG_IDLE: �Ŷ��`�u�лx
  *          USART_FLAG_ORE:  ���X���~�лx
  *          USART_FLAG_NE:   ���n���~�лx
  *          USART_FLAG_FE:   �V���~�лx
  *          USART_FLAG_PE:   �_�����~�лx
  * @retval  USART_FLAG ���s���A(SET �� RESET).
  */
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_FLAG(USART_FLAG));
  /* CTS �лx�������Ω� UART4 �M UART5 */
  if (USART_FLAG == USART_FLAG_CTS)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  }  
  
  if ((USARTx->SR & USART_FLAG) != (uint16_t)RESET)
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
  * @²�z  �M�� USARTx ���ݳB�z�лx��.
  * @�Ѽ�  USARTx: ��� USART �Ϊ� UART ���~��]��.
  *                �o�ӰѼƥi�H�O�U�����Ȥ��@ : USART1, USART2, USART3, UART4 or UART5.
  * @�Ѽ�  USART_FLAG: ���w�n�Q�M�����аO.
  *          �o�ӰѼƥi�H�O�U�����Ȫ����N�զX:
  *          USART_FLAG_CTS:  CTS ���ܼлx (�������Ω� UART4 �M UART5).
  *          USART_FLAG_LBD:  LIN ���j�����лx.
  *          USART_FLAG_TC:   �ǿ駹���лx.
  *          USART_FLAG_RXNE: �����ƾڱH�s�������żлx.
  *   
  * @����
*          - PE (�_��������~), FE (�����~), NE (���n���~),
*            ORE (�L�t���~) �M IDLE (���Ŷ��u) �лx�лx�Q�n������ǲM��:
*            �@��ŪUSART_SR�H�s���ާ@�]USART_GetFlagStatus()�^
*            ���ۤ@��ŪUSART_DR�H�s���ާ@(USART_ReceiveData()).
*          - RXNE�лx�]�i�H�Q�@��ŪUSART_DR�H�s���ާ@�M��(USART_ReceiveData()).
*          - TC�лx�лx�Q�n������ǲM��: �@��ŪUSART_SR�H�s���ާ@�]USART_GetFlagStatus()�^
*            ���ۤ@��ŪUSART_DR�H�s���ާ@(USART_ReceiveData()).                                                      
*          - TXE�лx�u��a�gUSART_DR�H�s���M��(USART_SendData()).     
  * @��^  �S��
  */
void USART_ClearFlag(USART_TypeDef* USARTx, uint16_t USART_FLAG)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CLEAR_FLAG(USART_FLAG));
  /* CTS �лx�������Ω� UART4 �M UART5 */
  if ((USART_FLAG & USART_FLAG_CTS) == USART_FLAG_CTS)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  } 
   
  USARTx->SR = (uint16_t)~USART_FLAG;
}

/**
  * @²�z  �ˬd���w�� USART ���_�o�ͻP�_.
  * @�Ѽ�  USARTx: ��� USART �Ϊ� UART ���~��]��. 
  *                �o�ӰѼƥi�H�O�U�����Ȥ��@ : USART1, USART2, USART3, UART4 or UART5.
  * @�Ѽ�  USART_IT: ���w�n�˴���USART���_��.
  *          �o�ӰѼƥi�H�O�U�����Ȥ��@ :
  *          USART_IT_CTS:  CTS ���ܤ��_ (�������Ω� UART4 �M UART5)
  *          USART_IT_LBD:  LIN ���j�������_
  *          USART_IT_TXE:  �o�e�ƾڱH�s�����Ť��_
  *          USART_IT_TC:   �ǿ駹�����_
  *          USART_IT_RXNE: �����ƾڱH�s�������Ť��_
  *          USART_IT_IDLE: �Ŷ��`�u���_
  *          USART_IT_ORE:  ���X���~���_
  *          USART_IT_NE:   ���n���~���_
  *          USART_IT_FE:   �V���~���_
  *          USART_IT_PE:   �_�����~���_
  * @��^  USART_IT ���s���A (SET �� RESET).
  */
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint16_t USART_IT)
{
  uint32_t bitpos = 0x00, itmask = 0x00, usartreg = 0x00;
  ITStatus bitstatus = RESET;
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_GET_IT(USART_IT));
  /* CTS ���_�������Ω� UART4 �M UART5 */ 
  if (USART_IT == USART_IT_CTS)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  }   
  
  /* �o�� USART �H�s���ޯ� */
  usartreg = (((uint8_t)USART_IT) >> 0x05);
  /*�o�줤�_��m */
  itmask = USART_IT & IT_Mask;
  itmask = (uint32_t)0x01 << itmask;
  
  if (usartreg == 0x01) /* The IT  is in CR1 register */
  {
    itmask &= USARTx->CR1;
  }
  else if (usartreg == 0x02) /* The IT  is in CR2 register */
  {
    itmask &= USARTx->CR2;
  }
  else /* The IT  is in CR3 register */
  {
    itmask &= USARTx->CR3;
  }
  
  bitpos = USART_IT >> 0x08;
  bitpos = (uint32_t)0x01 << bitpos;
  bitpos &= USARTx->SR;
  if ((itmask != (uint16_t)RESET)&&(bitpos != (uint16_t)RESET))
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
  * @²�z  �M�� USARTx �����_�ݳB�z��.
  * @��^  USARTx: ��� USART �Ϊ� UART ���~��]��. 
  *                �o�ӰѼƥi�H�O�U�����Ȥ��@ : USART1, USART2, USART3, UART4 or UART5.
  * @�Ѽ�  USART_IT: ���w�n�Q�M�������_���_��.
  *          �o�ӰѼƥi�H�O�U�����Ȥ��@:
  *          USART_IT_CTS:  CTS ���ܤ��_ (�������Ω� UART4 �M UART5)
  *          USART_IT_LBD:  LIN ���j�������_
  *          USART_IT_TC:   �o�e�������_
  *          USART_IT_RXNE: �����ƾڱH�s�������Ť��_
  *   
  * @����
*          - PE (�_��������~), FE (�����~), NE (���n���~),
*            ORE (�L�t���~) �M IDLE (���Ŷ��u)���_�� 
*            �Q�n������ǲM��: �@��ŪUSART_SR�H�s���ާ@�]USART_GetFlagStatus()�^
*            ���ۤ@��ŪUSART_DR�H�s���ާ@(USART_ReceiveData()).
*          - RXNE���_��]�i�H�Q�@��ŪUSART_DR�H�s���ާ@�M��(USART_ReceiveData()).
*          - TC���_��]�i�H�Q�n������ǲM��: �@��ŪUSART_SR�H�s���ާ@�]USART_GetFlagStatus()�^
*            ���ۤ@��ŪUSART_DR�H�s���ާ@(USART_ReceiveData()).                                                      
*          - TXE���_��m�i�H�Q�@�ӼgUSART_DR�H�s���M��(USART_SendData()).  
  * @��^  �S��
  */
void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT)
{
  uint16_t bitpos = 0x00, itmask = 0x00;
  /* �ˬd�Ѽ� */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CLEAR_IT(USART_IT));
  /* CTS ���_�������Ω� UART4 �M UART5 */
  if (USART_IT == USART_IT_CTS)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  }   
  
  bitpos = USART_IT >> 0x08;
  itmask = ((uint16_t)0x01 << (uint16_t)bitpos);
  USARTx->SR = (uint16_t)~itmask;
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
