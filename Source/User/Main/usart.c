/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
**  �ү踹�}�o�O
**	��f���h����X��
**  �����GRev1.0 
**  ����G2011-6-20
**	�׾¡Gwww.openmcu.com
**	�^�_�Ghttp://shop36995246.taobao.com/   
**  �޳N����s�G153631682     �޳NQQ�G77642732 
**  Copyright(c)@���_�q�l	 Dream_etd@163.com	
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
//�Y���ե�
#include "usually.h"
#include "usart.h"

//�[�J�H�U�N�X,���printf���,�Ӥ��ݭn���use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//�зǮw�ݭn��������                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef�z d in stdio.h. */ 
FILE __stdout;       
//�w�q_sys_exit()�H�קK�ϥΥb�D���Ҧ�    
_sys_exit(int x) 
{ 
	x = x; 
} 
//���w�qfputc��� 
int fputc(int Data, FILE *f)
{   
	while(!USART_GetFlagStatus(USART1,USART_FLAG_TXE));	  //USART_GetFlagStatus�G�o��o�e���A��
														  //USART_FLAG_TXE:�o�e�H�s������ 1�G���šF0�G�����A
	USART_SendData(USART1,Data);						  //�o�e�@�Ӧr��
	   
	return Data;										  //��^�@�ӭ�
}
#endif 

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��ƦW��: USART1_Send_Byte
** �\��y�z: ��f�o�e�@�Ӧr�Ŧ�
** �Ѽƴy�z�GData �n�o�e���ƾ�
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void USART1_Send_Byte(uint16_t Data)
{ 
	while(!USART_GetFlagStatus(USART1,USART_FLAG_TXE));	  //USART_GetFlagStatus�G�o��o�e���A��
														  //USART_FLAG_TXE:�o�e�H�s������ 1�G���šF0�G�����A
	USART_SendData(USART1,Data);						  //�o�e�@�Ӧr��
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��ƦW��: USART1_Send_Byte
** �\��y�z: ��f�o�e�@�Ӧr�Ŧ�
** �Ѽƴy�z�GData �n�o�e���ƾ�
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
uint8_t USART1_Receive_Byte(void)
{ 
   	while(!(USART_GetFlagStatus(USART1,USART_FLAG_RXNE))); //USART_GetFlagStatus�G�o�챵�����A��
														   //USART_FLAG_RXNE:�����ƾڱH�s���D�żлx�� 
														   //1�G�����A  0�G�Ŷ�(�S����ƾڡA���ݡC�C�C)
	return USART_ReceiveData(USART1);					   //�����@�Ӧr��
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��ƦW��: Usart_Init
** �\��y�z: ��f�޸}��l��
** �Ѽƴy�z: �L
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Init_Usart(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;					//�w�q�@��GPIO���c���ܶq

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1,ENABLE);	
															//�ϯ�U�Ӻݤf�����A���n�I�I�I

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 				//�t�m��f�����ݤf������9�ݤf
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	   		//�_�Υ\���X�}�|
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   	//�t�m�ݤf�t�׬�50M
  	GPIO_Init(GPIOA, &GPIO_InitStructure);				   	//�ھڰѼƪ�l��GPIOA�H�s��	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//�B�ſ�J(�_�쪬�A);	   				
  	GPIO_Init(GPIOA, &GPIO_InitStructure);				   	//�ھڰѼƪ�l��GPIOA�H�s��	
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��ƦW��: Usart_Configuration
** �\��y�z: ��f�t�m���
** �Ѽƴy�z: BaudRate�]�m�i�S�v 
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Usart_Configure(uint32_t BaudRate)
{
	USART_InitTypeDef USART_InitStructure;							    	//�w�q�@�Ӧ�f���c��

	USART_InitStructure.USART_BaudRate            =BaudRate ;	  			//�i�S�v115200
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b; 	//�ǿ�L�{���ϥ�8��ƾ�
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;	 	//�b�V�����ǿ�1�찱���
	USART_InitStructure.USART_Parity              = USART_Parity_No ;	 	//�_������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//�w��y����
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx; //�����M�o�e�Ҧ�
	USART_Init(USART1, &USART_InitStructure);								//�ھڰѼƪ�l�Ʀ�f�H�s��
//	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);							//�ϯ��f���_����
	USART_Cmd(USART1, ENABLE);     											//�ϯ��f�~�]
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��ƦW��: USART1_IRQHandler
** �\��y�z: ��f���_���
** �Ѽƴy�z: �L 
** �@  �@��: Dream
** ��@  ��: 2011�~6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void USART1_IRQHandler()
{
	uint8_t ReceiveDate;								//�w�q�@���ܶq�s�񱵦����ƾ�
	if(!(USART_GetITStatus(USART1,USART_IT_RXNE))); 	//Ū���������_�лx��USART_IT_RXNE 
														//USART_FLAG_RXNE:�����ƾڱH�s���D�żлx�� 
														//1�G�����A  0�G�Ŷ�(�S����ƾڡA���ݡC�C�C)
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);	//�M�����_�лx��
		ReceiveDate=USART_ReceiveData(USART1);			//�����r�Ŧs�J�Ʋ�
		printf("%d",(char*)ReceiveDate);				//�H�Q�i���X��J����,�q�o�̧ڭ̥i�H�ݨ���L�W�Ҧ�����ȹ������Q�i���
														//��p��J"1"��������X49 �B ��J"A" �������Ȭ�65
		printf("\n\r");									//����m��
		LED3=~LED3;										//��J�@��LED3½��@��
	}  
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
End:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
