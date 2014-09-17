/**
  ******************************************************************************
  * @���    stm32f10x_dma.c
  * @�@��    MCD ���ε{�ǲ�
  * @����    V3.1.0
  * @���    06/19/2009
  * @²�z    �o�Ӥ�� ���ѩҦ� DMA �T����.
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
#include "stm32f10x_dma.h"
#include "stm32f10x_rcc.h"

/* �ۥ����� --------------------------------------------------------------*/
/* �ۥΩw�q --------------------------------------------------------------*/

/* DMA ENABLE mask */
#define CCR_ENABLE_Set          ((uint32_t)0x00000001)
#define CCR_ENABLE_Reset        ((uint32_t)0xFFFFFFFE)

/* DMA1 Channelx interrupt pending bit masks */
#define DMA1_Channel1_IT_Mask    ((uint32_t)0x0000000F)
#define DMA1_Channel2_IT_Mask    ((uint32_t)0x000000F0)
#define DMA1_Channel3_IT_Mask    ((uint32_t)0x00000F00)
#define DMA1_Channel4_IT_Mask    ((uint32_t)0x0000F000)
#define DMA1_Channel5_IT_Mask    ((uint32_t)0x000F0000)
#define DMA1_Channel6_IT_Mask    ((uint32_t)0x00F00000)
#define DMA1_Channel7_IT_Mask    ((uint32_t)0x0F000000)

/* DMA2 Channelx interrupt pending bit masks */
#define DMA2_Channel1_IT_Mask    ((uint32_t)0x0000000F)
#define DMA2_Channel2_IT_Mask    ((uint32_t)0x000000F0)
#define DMA2_Channel3_IT_Mask    ((uint32_t)0x00000F00)
#define DMA2_Channel4_IT_Mask    ((uint32_t)0x0000F000)
#define DMA2_Channel5_IT_Mask    ((uint32_t)0x000F0000)

/* DMA2 FLAG mask */
#define FLAG_Mask                ((uint32_t)0x10000000)

/* DMA registers Masks */
#define CCR_CLEAR_Mask           ((uint32_t)0xFFFF800F)

/* �ۥΧ� -------------------------------------------------------------*/
/* �ۥ��ܶq -----------------------------------------------------------*/
/* �ۥΨ�ƭ쫬 -------------------------------------------------------*/
/* �ۥΨ�� -----------------------------------------------------------*/

/**
  * @²�z  �N DM A���q�Dx �H�s�����]���ʬ٭�.
  * @�Ѽ�  DMAy_Channelx: y �i�H�O1 �Ϊ�2�ADMA1��x�i�H�O1 ��7 �M DMA2 ��x �i�H�O1 ��5 �ӿ�ܦU�q�D.
  * @��^  �S��
  */
void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  /* �����w�� DMA y �q�D x */
  DMAy_Channelx->CCR &= CCR_ENABLE_Reset;
  /* �_�� DMA y �q�D x ����H�s�� */
  DMAy_Channelx->CCR  = 0;
  
  /* �_�� DMA y �q�D x �Ѿl�r�`�H�s�� */
  DMAy_Channelx->CNDTR = 0;
  
  /* �_�� DMA y �q�Dx �~��]�Ʀa�}�H�s�� */
  DMAy_Channelx->CPAR  = 0;
  
  /* �_�� DMA y �q�D x ���s�a�}�H�s�� */
  DMAy_Channelx->CMAR = 0;
  
  if (DMAy_Channelx == DMA1_Channel1)
  {
    /* �_�� DMA1 �q�D1 ���_���_�� */
    DMA1->IFCR |= DMA1_Channel1_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel2)
  {
    /* �_�� DMA1 �q�D2 ���_���_�� */
    DMA1->IFCR |= DMA1_Channel2_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel3)
  {
    /* �_�� DMA1 �q�D3 ���_���_�� */
    DMA1->IFCR |= DMA1_Channel3_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel4)
  {
    /* �_�� DMA1 �q�D4 ���_���_�� */
    DMA1->IFCR |= DMA1_Channel4_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel5)
  {
    /* �_�� DMA1 �q�D5 ���_���_�� */
    DMA1->IFCR |= DMA1_Channel5_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel6)
  {
    /* �_�� DMA1 �q�D6 ���_���_�� */
    DMA1->IFCR |= DMA1_Channel6_IT_Mask;
  }
  else if (DMAy_Channelx == DMA1_Channel7)
  {
    /* �_�� DMA1 �q�D7 ���_���_�� */
    DMA1->IFCR |= DMA1_Channel7_IT_Mask;
  }
  else if (DMAy_Channelx == DMA2_Channel1)
  {
    /* �_�� DMA2 �q�D1 ���_���_�� */
    DMA2->IFCR |= DMA2_Channel1_IT_Mask;
  }
  else if (DMAy_Channelx == DMA2_Channel2)
  {
    /* �_�� DMA2 �q�D2 ���_���_�� */
    DMA2->IFCR |= DMA2_Channel2_IT_Mask;
  }
  else if (DMAy_Channelx == DMA2_Channel3)
  {
    /* �_�� DMA2 �q�D3 ���_���_�� */
    DMA2->IFCR |= DMA2_Channel3_IT_Mask;
  }
  else if (DMAy_Channelx == DMA2_Channel4)
  {
    /* �_�� DMA2 �q�D4 ���_���_�� */
    DMA2->IFCR |= DMA2_Channel4_IT_Mask;
  }
  else
  { 
    if (DMAy_Channelx == DMA2_Channel5)
    {
      /* �_�� DMA2 �q�D5 ���_���_�� */
      DMA2->IFCR |= DMA2_Channel5_IT_Mask;
    }
  }
}

/**
  * @²�z  �ھ� DMA_InitStruct �����w���Ѽƪ�l�� DMA ���q�Dx �H�s��.
  * @�Ѽ�  DMAy_Channelx: y �i�H�O1 �Ϊ�2 �ADMA1 ��x �i�H�O 1�� 7 �MDMA2 ��x �i�H�O1 ��5 �ӿ�ܦU�q�D.
  * @�Ѽ�  DMA_InitStruct: ���V DMA_InitTypeDef �����c��A���]�t�S�w DMA �q�D���t�m�H��.
  * @��^  �S��
  */
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct)
{
  uint32_t tmpreg = 0;

  /* �ˬd�Ѽ� */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  assert_param(IS_DMA_DIR(DMA_InitStruct->DMA_DIR));
  assert_param(IS_DMA_BUFFER_SIZE(DMA_InitStruct->DMA_BufferSize));
  assert_param(IS_DMA_PERIPHERAL_INC_STATE(DMA_InitStruct->DMA_PeripheralInc));
  assert_param(IS_DMA_MEMORY_INC_STATE(DMA_InitStruct->DMA_MemoryInc));   
  assert_param(IS_DMA_PERIPHERAL_DATA_SIZE(DMA_InitStruct->DMA_PeripheralDataSize));
  assert_param(IS_DMA_MEMORY_DATA_SIZE(DMA_InitStruct->DMA_MemoryDataSize));
  assert_param(IS_DMA_MODE(DMA_InitStruct->DMA_Mode));
  assert_param(IS_DMA_PRIORITY(DMA_InitStruct->DMA_Priority));
  assert_param(IS_DMA_M2M_STATE(DMA_InitStruct->DMA_M2M));

/*--------------------------- DMAy Channelx CCR Configuration -----------------*/
  /* Get the DMAy_Channelx CCR value */
  tmpreg = DMAy_Channelx->CCR;
  /* Clear MEM2MEM, PL, MSIZE, PSIZE, MINC, PINC, CIRC and DIR bits */
  tmpreg &= CCR_CLEAR_Mask;
  /* Configure DMAy Channelx: data transfer, data size, priority level and mode */
  /* Set DIR bit according to DMA_DIR value */
  /* Set CIRC bit according to DMA_Mode value */
  /* Set PINC bit according to DMA_PeripheralInc value */
  /* Set MINC bit according to DMA_MemoryInc value */
  /* Set PSIZE bits according to DMA_PeripheralDataSize value */
  /* Set MSIZE bits according to DMA_MemoryDataSize value */
  /* Set PL bits according to DMA_Priority value */
  /* Set the MEM2MEM bit according to DMA_M2M value */
  tmpreg |= DMA_InitStruct->DMA_DIR | DMA_InitStruct->DMA_Mode |
            DMA_InitStruct->DMA_PeripheralInc | DMA_InitStruct->DMA_MemoryInc |
            DMA_InitStruct->DMA_PeripheralDataSize | DMA_InitStruct->DMA_MemoryDataSize |
            DMA_InitStruct->DMA_Priority | DMA_InitStruct->DMA_M2M;

  /* Write to DMAy Channelx CCR */
  DMAy_Channelx->CCR = tmpreg;

/*--------------------------- DMAy Channelx CNDTR Configuration ---------------*/
  /* Write to DMAy Channelx CNDTR */
  DMAy_Channelx->CNDTR = DMA_InitStruct->DMA_BufferSize;

/*--------------------------- DMAy Channelx CPAR Configuration ----------------*/
  /* Write to DMAy Channelx CPAR */
  DMAy_Channelx->CPAR = DMA_InitStruct->DMA_PeripheralBaseAddr;

/*--------------------------- DMAy Channelx CMAR Configuration ----------------*/
  /* Write to DMAy Channelx CMAR */
  DMAy_Channelx->CMAR = DMA_InitStruct->DMA_MemoryBaseAddr;
}

/**
  * @brief  Fills each DMA_InitStruct member with its default value.
  * @param  DMA_InitStruct : pointer to a DMA_InitTypeDef structure which will
  *   be initialized.
  * @retval None
  */
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct)
{
/*-------------- Reset DMA init structure parameters values ------------------*/
  /* ��l�� DMA_PeripheralBaseAddr ���� */
  DMA_InitStruct->DMA_PeripheralBaseAddr = 0;
  /* ��l�� DMA_MemoryBaseAddr ���� */
  DMA_InitStruct->DMA_MemoryBaseAddr = 0;
  /* ��l�� DMA_DIR ���� */
  DMA_InitStruct->DMA_DIR = DMA_DIR_PeripheralSRC;
  /* ��l�� DMA_BufferSize ���� */
  DMA_InitStruct->DMA_BufferSize = 0;
  /* ��l�� DMA_PeripheralInc ���� */
  DMA_InitStruct->DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  /* ��l�� DMA_MemoryInc ���� */
  DMA_InitStruct->DMA_MemoryInc = DMA_MemoryInc_Disable;
  /* ��l�� DMA_PeripheralDataSize ���� */
  DMA_InitStruct->DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  /* ��l�� DMA_MemoryDataSize ���� */
  DMA_InitStruct->DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  /* ��l�� DMA_Mode ���� */
  DMA_InitStruct->DMA_Mode = DMA_Mode_Normal;
  /* ��l�� DMA_Priority ���� */
  DMA_InitStruct->DMA_Priority = DMA_Priority_Low;
  /* ��l�� DMA_M2M ���� */
  DMA_InitStruct->DMA_M2M = DMA_M2M_Disable;
}

/**
  * @²�z  �ϯ�Υ�����w�� DMA y �q�D x.
  * @�Ѽ�  DMAy_Channelx: y �i�H�O1 �Ϊ�2 �ADMA1 ��x �i�H�O1 ��7 �MDMA2 ��x �i�H�O1 ��5 �ӿ�ܦU�q�D.
  * @�Ѽ�  NewState: DMA y �q�Dx ���s���A. 
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* �ϯ���w�� DMA y �q�D x */
    DMAy_Channelx->CCR |= CCR_ENABLE_Set;
  }
  else
  {
    /* ������w�� DMA y �q�D x */
    DMAy_Channelx->CCR &= CCR_ENABLE_Reset;
  }
}

/**
  * @²�z  �ϯ�Υ�����w�� DMA y �q�D x ���_.
  * @�Ѽ�  DMAy_Channelx: y �i�H�O1 �Ϊ�2 �ADMA1 ��x �i�H�O1 ��7 �MDMA2 ��x �i�H�O1 ��5 �ӿ�ܦU�q�D.
  * @�Ѽ�  DMA_IT: ���w DMA �����_. 
  *            �o�ӰѼƥi�H�O�U���Ȫ����N�զX:
  *            DMA_IT_TC:  �ǿ駹�����_�̽�
  *            DMA_IT_HT:  �ǿ�L�b���_�̽�
  *            DMA_IT_TE:  �ǿ���~���_�̽�
  * @�Ѽ�  NewState: ���w�� DMA ���_���s���A.
  *                  �o�ӰѼƥi�H�O: ENABLE �� DISABLE.
  * @��^  �S��
  */
void DMA_ITConfig(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t DMA_IT, FunctionalState NewState)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  assert_param(IS_DMA_CONFIG_IT(DMA_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* �ϯ���w�� DMA ���_ */
    DMAy_Channelx->CCR |= DMA_IT;
  }
  else
  {
    /* ������w�� DMA ���_ */
    DMAy_Channelx->CCR &= ~DMA_IT;
  }
}

/**
  * @²�z  ��^��e DMA y �q�Dx �Ѿl���ݶǿ�ƾڼƥ�.
  * @�Ѽ�  DMAy_Channelx: y �i�H�O1 �Ϊ�2 �ADMA1 ��x �i�H�O1 ��7 �MDMA2 ��x �i�H�O1 ��5 �ӿ�ܦU�q�D.
  * @��^  ��e DMA y �q�Dx �ǿ餤�Ѿl���ƾڳ椸���ƶq.
  */
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  /* ��^ DMA y �q�Dx �ǿ餤�Ѿl���ƾڳ椸���ƶq */
  return ((uint16_t)(DMAy_Channelx->CNDTR));
}

/**
  * @²�z  �ˬd���w�� DMA y �q�D x �лx��]�m�P�_.
  * @�Ѽ�  DMA_FLAG: ���w���лx.
  *          �o�ӰѼƥi�H�O�U�����Ȥ��@:
*            DMA1_FLAG_GL1: DMA1�q�D1�����лx
*            DMA1_FLAG_TC1: DMA1�q�D1�ǿ鵲���лx
*            DMA1_FLAG_HT1: DMA1�q�D1�b�ǿ�лx
*            DMA1_FLAG_TE1: DMA1�q�D1�ǿ���~�лx
*            DMA1_FLAG_GL2: DMA1 �q�D2 �����лx.
*            DMA1_FLAG_TC2: DMA1 �q�D2 �ǿ鵲���лx.
*            DMA1_FLAG_HT2: DMA1 �q�D2 �b�ǿ�лx.
*            DMA1_FLAG_TE2: DMA1 �q�D2 �ǿ���~�лx.
*            DMA1_FLAG_GL3: DMA1 �q�D3 �����лx.
*            DMA1_FLAG_TC3: DMA1 �q�D3 �ǿ鵲���лx.
*            DMA1_FLAG_HT3: DMA1 �q�D3 �b�ǿ�лx.
*            DMA1_FLAG_TE3: DMA1 �q�D3 �ǿ���~�лx.
*            DMA1_FLAG_GL4: DMA1 �q�D4 �����лx.
*            DMA1_FLAG_TC4: DMA1 �q�D4 �ǿ鵲���лx.
*            DMA1_FLAG_HT4: DMA1 �q�D4 �b�ǿ�лx.
*            DMA1_FLAG_TE4: DMA1 �q�D4 �ǿ���~�лx.
*            DMA1_FLAG_GL5: DMA1 �q�D5 �����лx.
*            DMA1_FLAG_TC5: DMA1 �q�D5 �ǿ鵲���лx.
*            DMA1_FLAG_HT5: DMA1 �q�D5 �b�ǿ�лx.
*            DMA1_FLAG_TE5: DMA1 �q�D5 �ǿ���~�лx.
*            DMA1_FLAG_GL6: DMA1 �q�D6 �����лx.
*            DMA1_FLAG_TC6: DMA1 �q�D6 �ǿ鵲���лx.
*            DMA1_FLAG_HT6: DMA1 �q�D6 �b�ǿ�лx.
*            DMA1_FLAG_TE6: DMA1 �q�D6 �ǿ���~�лx.
*            DMA1_FLAG_GL7: DMA1 �q�D7 �����лx.
*            DMA1_FLAG_TC7: DMA1 �q�D7 �ǿ鵲���лx.
*            DMA1_FLAG_HT7: DMA1 �q�D7 �b�ǿ�лx.
*            DMA1_FLAG_TE7: DMA1 �q�D7 �ǿ���~�лx.
*            DMA2_FLAG_GL1: DMA2 �q�D1 �����лx.
*            DMA2_FLAG_TC1: DMA2 �q�D1 �ǿ鵲���лx.
*            DMA2_FLAG_HT1: DMA2 �q�D1 �b�ǿ�лx.
*            DMA2_FLAG_TE1: DMA2 �q�D1 �ǿ���~�лx.
*            DMA2_FLAG_GL2: DMA2 �q�D2 �����лx.
*            DMA2_FLAG_TC2: DMA2 �q�D2 �ǿ鵲���лx.
*            DMA2_FLAG_HT2: DMA2 �q�D2 �b�ǿ�лx.
*            DMA2_FLAG_TE2: DMA2 �q�D2 �ǿ���~�лx.
*            DMA2_FLAG_GL3: DMA2 �q�D3 �����лx.
*            DMA2_FLAG_TC3: DMA2 �q�D3 �ǿ鵲���лx.
*            DMA2_FLAG_HT3: DMA2 �q�D3 �b�ǿ�лx.
*            DMA2_FLAG_TE3: DMA2 �q�D3 �ǿ���~�лx.
*            DMA2_FLAG_GL4: DMA2 �q�D4 �����лx.
*            DMA2_FLAG_TC4: DMA2 �q�D4 �ǿ鵲���лx.
*            DMA2_FLAG_HT4: DMA2 �q�D4 �b�ǿ�лx.
*            DMA2_FLAG_TE4: DMA2 �q�D4 �ǿ���~�лx.
*            DMA2_FLAG_GL5: DMA2 �q�D5 �����лx.
*            DMA2_FLAG_TC5: DMA2 �q�D5 �ǿ鵲���лx.
*            DMA2_FLAG_HT5: DMA2 �q�D5 �b�ǿ�лx.
*            DMA2_FLAG_TE5: DMA2 �q�D5 �ǿ���~�лx.
  * @��^  DMA_FLAG ���s���A (SET �� RESET).
  */
FlagStatus DMA_GetFlagStatus(uint32_t DMA_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint32_t tmpreg = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_DMA_GET_FLAG(DMA_FLAG));

  /* �p��ϥΪ� DMA */
  if ((DMA_FLAG & FLAG_Mask) != (uint32_t)RESET)
  {
    /* �o�� DMA2 ISR �H�s������ */
    tmpreg = DMA2->ISR ;
  }
  else
  {
    /* �o�� DMA1 ISR �H�s������ */
    tmpreg = DMA1->ISR ;
  }

  /* �ˬd���w�� DMA �лx���s���A */
  if ((tmpreg & DMA_FLAG) != (uint32_t)RESET)
  {
    /* �]�m DMA_FLAG */
    bitstatus = SET;
  }
  else
  {
    /* �_�� DMA_FLAG */
    bitstatus = RESET;
  }
  
  /* ��^ DMA_FLAG ���A */
  return  bitstatus;
}

/**
  * @²�z  �M���w�� DMA y �q�D x �ݳB�z�лx��.
  * @�Ѽ�  DMA_FLAG: ���w���ݳB�z�лx��.
  *          �o�ӰѼƥi�H�O�U���Ȫ����N�զX (���P�@�� DMA) :
*            DMA1_FLAG_GL1: DMA1�q�D1�����лx
*            DMA1_FLAG_TC1: DMA1�q�D1�ǿ鵲���лx
*            DMA1_FLAG_HT1: DMA1�q�D1�b�ǿ�лx
*            DMA1_FLAG_TE1: DMA1�q�D1�ǿ���~�лx
*            DMA1_FLAG_GL2: DMA1 �q�D2 �����лx.
*            DMA1_FLAG_TC2: DMA1 �q�D2 �ǿ鵲���лx.
*            DMA1_FLAG_HT2: DMA1 �q�D2 �b�ǿ�лx.
*            DMA1_FLAG_TE2: DMA1 �q�D2 �ǿ���~�лx.
*            DMA1_FLAG_GL3: DMA1 �q�D3 �����лx.
*            DMA1_FLAG_TC3: DMA1 �q�D3 �ǿ鵲���лx.
*            DMA1_FLAG_HT3: DMA1 �q�D3 �b�ǿ�лx.
*            DMA1_FLAG_TE3: DMA1 �q�D3 �ǿ���~�лx.
*            DMA1_FLAG_GL4: DMA1 �q�D4 �����лx.
*            DMA1_FLAG_TC4: DMA1 �q�D4 �ǿ鵲���лx.
*            DMA1_FLAG_HT4: DMA1 �q�D4 �b�ǿ�лx.
*            DMA1_FLAG_TE4: DMA1 �q�D4 �ǿ���~�лx.
*            DMA1_FLAG_GL5: DMA1 �q�D5 �����лx.
*            DMA1_FLAG_TC5: DMA1 �q�D5 �ǿ鵲���лx.
*            DMA1_FLAG_HT5: DMA1 �q�D5 �b�ǿ�лx.
*            DMA1_FLAG_TE5: DMA1 �q�D5 �ǿ���~�лx.
*            DMA1_FLAG_GL6: DMA1 �q�D6 �����лx.
*            DMA1_FLAG_TC6: DMA1 �q�D6 �ǿ鵲���лx.
*            DMA1_FLAG_HT6: DMA1 �q�D6 �b�ǿ�лx.
*            DMA1_FLAG_TE6: DMA1 �q�D6 �ǿ���~�лx.
*            DMA1_FLAG_GL7: DMA1 �q�D7 �����лx.
*            DMA1_FLAG_TC7: DMA1 �q�D7 �ǿ鵲���лx.
*            DMA1_FLAG_HT7: DMA1 �q�D7 �b�ǿ�лx.
*            DMA1_FLAG_TE7: DMA1 �q�D7 �ǿ���~�лx.
*            DMA2_FLAG_GL1: DMA2 �q�D1 �����лx.
*            DMA2_FLAG_TC1: DMA2 �q�D1 �ǿ鵲���лx.
*            DMA2_FLAG_HT1: DMA2 �q�D1 �b�ǿ�лx.
*            DMA2_FLAG_TE1: DMA2 �q�D1 �ǿ���~�лx.
*            DMA2_FLAG_GL2: DMA2 �q�D2 �����лx.
*            DMA2_FLAG_TC2: DMA2 �q�D2 �ǿ鵲���лx.
*            DMA2_FLAG_HT2: DMA2 �q�D2 �b�ǿ�лx.
*            DMA2_FLAG_TE2: DMA2 �q�D2 �ǿ���~�лx.
*            DMA2_FLAG_GL3: DMA2 �q�D3 �����лx.
*            DMA2_FLAG_TC3: DMA2 �q�D3 �ǿ鵲���лx.
*            DMA2_FLAG_HT3: DMA2 �q�D3 �b�ǿ�лx.
*            DMA2_FLAG_TE3: DMA2 �q�D3 �ǿ���~�лx.
*            DMA2_FLAG_GL4: DMA2 �q�D4 �����лx.
*            DMA2_FLAG_TC4: DMA2 �q�D4 �ǿ鵲���лx.
*            DMA2_FLAG_HT4: DMA2 �q�D4 �b�ǿ�лx.
*            DMA2_FLAG_TE4: DMA2 �q�D4 �ǿ���~�лx.
*            DMA2_FLAG_GL5: DMA2 �q�D5 �����лx.
*            DMA2_FLAG_TC5: DMA2 �q�D5 �ǿ鵲���лx.
*            DMA2_FLAG_HT5: DMA2 �q�D5 �b�ǿ�лx.
*            DMA2_FLAG_TE5: DMA2 �q�D5 �ǿ���~�лx.
  * @��^  �S��
  */
void DMA_ClearFlag(uint32_t DMA_FLAG)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_DMA_CLEAR_FLAG(DMA_FLAG));
  /* �p��ϥΪ� DMA */

  if ((DMA_FLAG & FLAG_Mask) != (uint32_t)RESET)
  {
    /* �M����w�� DMA �лx */
    DMA2->IFCR = DMA_FLAG;
  }
  else
  {
    /* �M����w�� DMA �лx */
    DMA1->IFCR = DMA_FLAG;
  }
}

/**
  * @²�z  �ˬd���w�� DMA y �q�D x ���_�o�ͻP�_.
  * @�Ѽ�  DMA_IT: ���w�� DMA ���_��. 
*             �o�ӰѼƥi�H�O�U�����Ȥ��@:
*             DMA1_IT_GL1: DMA1 �q�D1 �������_.
*             DMA1_IT_TC1: DMA1 �q�D1 �ǿ駹�����_.
*             DMA1_IT_HT1: DMA1 �q�D1 �b�ǿ餤�_.
*             DMA1_IT_TE1: DMA1 �q�D1 �ǿ���~���_.
*             DMA1_IT_GL2: DMA1 �q�D2 �������_.
*             DMA1_IT_TC2: DMA1 �q�D2 �ǿ駹�����_.
*             DMA1_IT_HT2: DMA1 �q�D2 �b�ǿ餤�_.
*             DMA1_IT_TE2: DMA1 �q�D2 �ǿ���~���_.
*             DMA1_IT_GL3: DMA1 �q�D3 �������_.
*             DMA1_IT_TC3: DMA1 �q�D3 �ǿ駹�����_.
*             DMA1_IT_HT3: DMA1 �q�D3 �b�ǿ餤�_.
*             DMA1_IT_TE3: DMA1 �q�D3 �ǿ���~���_.
*             DMA1_IT_GL4: DMA1 �q�D4 �������_.
*             DMA1_IT_TC4: DMA1 �q�D4 �ǿ駹�����_.
*             DMA1_IT_HT4: DMA1 �q�D4 �b�ǿ餤�_.
*             DMA1_IT_TE4: DMA1 �q�D4 �ǿ���~���_.
*             DMA1_IT_GL5: DMA1 �q�D5 �������_.
*             DMA1_IT_TC5: DMA1 �q�D5 �ǿ駹�����_.
*             DMA1_IT_HT5: DMA1 �q�D5 �b�ǿ餤�_.
*             DMA1_IT_TE5: DMA1 �q�D5 �ǿ���~���_.
*             DMA1_IT_GL6: DMA1 �q�D6 �������_.
*             DMA1_IT_TC6: DMA1 �q�D6 �ǿ駹�����_.
*             DMA1_IT_HT6: DMA1 �q�D6 �b�ǿ餤�_.
*             DMA1_IT_TE6: DMA1 �q�D6 �ǿ���~���_.
*             DMA1_IT_GL7: DMA1 �q�D7 �������_.
*             DMA1_IT_TC7: DMA1 �q�D7 �ǿ駹�����_.
*             DMA1_IT_HT7: DMA1 �q�D7 �b�ǿ餤�_.
*             DMA1_IT_TE7: DMA1 �q�D7 �ǿ���~���_.
*             DMA2_IT_GL1: DMA2 �q�D1 �������_.
*             DMA2_IT_TC1: DMA2 �q�D1 �ǿ駹�����_.
*             DMA2_IT_HT1: DMA2 �q�D1 �b�ǿ餤�_.
*             DMA2_IT_TE1: DMA2 �q�D1 �ǿ���~���_.
*             DMA2_IT_GL2: DMA2 �q�D2 �������_.
*             DMA2_IT_TC2: DMA2 �q�D2 �ǿ駹�����_.
*             DMA2_IT_HT2: DMA2 �q�D2 �b�ǿ餤�_.
*             DMA2_IT_TE2: DMA2 �q�D2 �ǿ���~���_.
*             DMA2_IT_GL3: DMA2 �q�D3 �������_.
*             DMA2_IT_TC3: DMA2 �q�D3 �ǿ駹�����_.
*             DMA2_IT_HT3: DMA2 �q�D3 �b�ǿ餤�_.
*             DMA2_IT_TE3: DMA2 �q�D3 �ǿ���~���_.
*             DMA2_IT_GL4: DMA2 �q�D4 �������_.
*             DMA2_IT_TC4: DMA2 �q�D4 �ǿ駹�����_.
*             DMA2_IT_HT4: DMA2 �q�D4 �b�ǿ餤�_.
*             DMA2_IT_TE4: DMA2 �q�D4 �ǿ���~���_.
*             DMA2_IT_GL5: DMA2 �q�D5 �������_.
*             DMA2_IT_TC5: DMA2 �q�D5 �ǿ駹�����_.
*             DMA2_IT_HT5: DMA2 �q�D5 �b�ǿ餤�_.
*             DMA2_IT_TE5: DMA2 �q�D5 �ǿ���~���_.
  * @��^  DMA_IT ���s���A (SET �� RESET).
  */
ITStatus DMA_GetITStatus(uint32_t DMA_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t tmpreg = 0;
  /* �ˬd�Ѽ� */
  assert_param(IS_DMA_GET_IT(DMA_IT));

  /* �p��ϥΪ� DMA */
  if ((DMA_IT & FLAG_Mask) != (uint32_t)RESET)
  {
    /* �o�� DMA2 ISR �H�s������ */
    tmpreg = DMA2->ISR ;
  }
  else
  {
    /* �o�� DMA1 ISR �H�s������ */
    tmpreg = DMA1->ISR ;
  }

  /* �ˬd���w�� DMA ���_ */
  if ((tmpreg & DMA_IT) != (uint32_t)RESET)
  {
    /* �]�m DMA_IT */
    bitstatus = SET;
  }
  else
  {
    /* �_�� DMA_IT */
    bitstatus = RESET;
  }
  /* ��^ DMA_IT ���A */
  return  bitstatus;
}

/**
  * @²�z  �M�� DMA y �q�D x ���_�ݳB�z�лx��.
  * @�Ѽ�  DMA_IT: ���w�� DMA ���_���_��.
*             �o�ӰѼƥi�H�O�U�����Ȥ��@:
*             DMA1_IT_GL1: DMA1 �q�D1 �������_.
*             DMA1_IT_TC1: DMA1 �q�D1 �ǿ駹�����_.
*             DMA1_IT_HT1: DMA1 �q�D1 �b�ǿ餤�_.
*             DMA1_IT_TE1: DMA1 �q�D1 �ǿ���~���_.
*             DMA1_IT_GL2: DMA1 �q�D2 �������_.
*             DMA1_IT_TC2: DMA1 �q�D2 �ǿ駹�����_.
*             DMA1_IT_HT2: DMA1 �q�D2 �b�ǿ餤�_.
*             DMA1_IT_TE2: DMA1 �q�D2 �ǿ���~���_.
*             DMA1_IT_GL3: DMA1 �q�D3 �������_.
*             DMA1_IT_TC3: DMA1 �q�D3 �ǿ駹�����_.
*             DMA1_IT_HT3: DMA1 �q�D3 �b�ǿ餤�_.
*             DMA1_IT_TE3: DMA1 �q�D3 �ǿ���~���_.
*             DMA1_IT_GL4: DMA1 �q�D4 �������_.
*             DMA1_IT_TC4: DMA1 �q�D4 �ǿ駹�����_.
*             DMA1_IT_HT4: DMA1 �q�D4 �b�ǿ餤�_.
*             DMA1_IT_TE4: DMA1 �q�D4 �ǿ���~���_.
*             DMA1_IT_GL5: DMA1 �q�D5 �������_.
*             DMA1_IT_TC5: DMA1 �q�D5 �ǿ駹�����_.
*             DMA1_IT_HT5: DMA1 �q�D5 �b�ǿ餤�_.
*             DMA1_IT_TE5: DMA1 �q�D5 �ǿ���~���_.
*             DMA1_IT_GL6: DMA1 �q�D6 �������_.
*             DMA1_IT_TC6: DMA1 �q�D6 �ǿ駹�����_.
*             DMA1_IT_HT6: DMA1 �q�D6 �b�ǿ餤�_.
*             DMA1_IT_TE6: DMA1 �q�D6 �ǿ���~���_.
*             DMA1_IT_GL7: DMA1 �q�D7 �������_.
*             DMA1_IT_TC7: DMA1 �q�D7 �ǿ駹�����_.
*             DMA1_IT_HT7: DMA1 �q�D7 �b�ǿ餤�_.
*             DMA1_IT_TE7: DMA1 �q�D7 �ǿ���~���_.
*             DMA2_IT_GL1: DMA2 �q�D1 �������_.
*             DMA2_IT_TC1: DMA2 �q�D1 �ǿ駹�����_.
*             DMA2_IT_HT1: DMA2 �q�D1 �b�ǿ餤�_.
*             DMA2_IT_TE1: DMA2 �q�D1 �ǿ���~���_.
*             DMA2_IT_GL2: DMA2 �q�D2 �������_.
*             DMA2_IT_TC2: DMA2 �q�D2 �ǿ駹�����_.
*             DMA2_IT_HT2: DMA2 �q�D2 �b�ǿ餤�_.
*             DMA2_IT_TE2: DMA2 �q�D2 �ǿ���~���_.
*             DMA2_IT_GL3: DMA2 �q�D3 �������_.
*             DMA2_IT_TC3: DMA2 �q�D3 �ǿ駹�����_.
*             DMA2_IT_HT3: DMA2 �q�D3 �b�ǿ餤�_.
*             DMA2_IT_TE3: DMA2 �q�D3 �ǿ���~���_.
*             DMA2_IT_GL4: DMA2 �q�D4 �������_.
*             DMA2_IT_TC4: DMA2 �q�D4 �ǿ駹�����_.
*             DMA2_IT_HT4: DMA2 �q�D4 �b�ǿ餤�_.
*             DMA2_IT_TE4: DMA2 �q�D4 �ǿ���~���_.
*             DMA2_IT_GL5: DMA2 �q�D5 �������_.
*             DMA2_IT_TC5: DMA2 �q�D5 �ǿ駹�����_.
*             DMA2_IT_HT5: DMA2 �q�D5 �b�ǿ餤�_.
*             DMA2_IT_TE5: DMA2 �q�D5 �ǿ���~���_.
  * @��^  �S��
  */
void DMA_ClearITPendingBit(uint32_t DMA_IT)
{
  /* �ˬd�Ѽ� */
  assert_param(IS_DMA_CLEAR_IT(DMA_IT));

  /* �p��ϥΪ� DMA */
  if ((DMA_IT & FLAG_Mask) != (uint32_t)RESET)
  {
    /* �M����ܪ�DMA���_���_�� */
    DMA2->IFCR = DMA_IT;
  }
  else
  {
    /* �M����ܪ�DMA���_���_�� */
    DMA1->IFCR = DMA_IT;
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
