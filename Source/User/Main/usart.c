/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
**  啟航號開發板
**	串口底層函數驅動
**  版本：Rev1.0 
**  日期：2011-6-20
**	論壇：www.openmcu.com
**	淘寶：http://shop36995246.taobao.com/   
**  技術支持群：153631682     技術QQ：77642732 
**  Copyright(c)@旺寶電子	 Dream_etd@163.com	
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
//頭文件調用
#include "usually.h"
#include "usart.h"

//加入以下代碼,支持printf函數,而不需要選擇use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//標準庫需要的支持函數                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef』 d in stdio.h. */ 
FILE __stdout;       
//定義_sys_exit()以避免使用半主機模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定義fputc函數 
int fputc(int Data, FILE *f)
{   
	while(!USART_GetFlagStatus(USART1,USART_FLAG_TXE));	  //USART_GetFlagStatus：得到發送狀態位
														  //USART_FLAG_TXE:發送寄存器為空 1：為空；0：忙狀態
	USART_SendData(USART1,Data);						  //發送一個字符
	   
	return Data;										  //返回一個值
}
#endif 

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: USART1_Send_Byte
** 功能描述: 串口發送一個字符串
** 參數描述：Data 要發送的數據
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void USART1_Send_Byte(uint16_t Data)
{ 
	while(!USART_GetFlagStatus(USART1,USART_FLAG_TXE));	  //USART_GetFlagStatus：得到發送狀態位
														  //USART_FLAG_TXE:發送寄存器為空 1：為空；0：忙狀態
	USART_SendData(USART1,Data);						  //發送一個字符
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: USART1_Send_Byte
** 功能描述: 串口發送一個字符串
** 參數描述：Data 要發送的數據
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
uint8_t USART1_Receive_Byte(void)
{ 
   	while(!(USART_GetFlagStatus(USART1,USART_FLAG_RXNE))); //USART_GetFlagStatus：得到接收狀態位
														   //USART_FLAG_RXNE:接收數據寄存器非空標誌位 
														   //1：忙狀態  0：空閒(沒收到數據，等待。。。)
	return USART_ReceiveData(USART1);					   //接收一個字符
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: Usart_Init
** 功能描述: 串口引腳初始化
** 參數描述: 無
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Init_Usart(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;					//定義一個GPIO結構體變量

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1,ENABLE);	
															//使能各個端口時鐘，重要！！！

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 				//配置串口接收端口掛接到9端口
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	   		//復用功能輸出開漏
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   	//配置端口速度為50M
  	GPIO_Init(GPIOA, &GPIO_InitStructure);				   	//根據參數初始化GPIOA寄存器	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空輸入(復位狀態);	   				
  	GPIO_Init(GPIOA, &GPIO_InitStructure);				   	//根據參數初始化GPIOA寄存器	
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: Usart_Configuration
** 功能描述: 串口配置函數
** 參數描述: BaudRate設置波特率 
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Usart_Configure(uint32_t BaudRate)
{
	USART_InitTypeDef USART_InitStructure;							    	//定義一個串口結構體

	USART_InitStructure.USART_BaudRate            =BaudRate ;	  			//波特率115200
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b; 	//傳輸過程中使用8位數據
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;	 	//在幀結尾傳輸1位停止位
	USART_InitStructure.USART_Parity              = USART_Parity_No ;	 	//奇偶失能
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//硬件流失能
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx; //接收和發送模式
	USART_Init(USART1, &USART_InitStructure);								//根據參數初始化串口寄存器
//	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);							//使能串口中斷接收
	USART_Cmd(USART1, ENABLE);     											//使能串口外設
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函數名稱: USART1_IRQHandler
** 功能描述: 串口中斷函數
** 參數描述: 無 
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void USART1_IRQHandler()
{
	uint8_t ReceiveDate;								//定義一個變量存放接收的數據
	if(!(USART_GetITStatus(USART1,USART_IT_RXNE))); 	//讀取接收中斷標誌位USART_IT_RXNE 
														//USART_FLAG_RXNE:接收數據寄存器非空標誌位 
														//1：忙狀態  0：空閒(沒收到數據，等待。。。)
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);	//清楚中斷標誌位
		ReceiveDate=USART_ReceiveData(USART1);			//接收字符存入數組
		printf("%d",(char*)ReceiveDate);				//以十進制輸出輸入的值,從這裡我們可以看到鍵盤上所有的鍵值對應的十進制數
														//比如輸入"1"對應的輸出49 、 輸入"A" 對應的值為65
		printf("\n\r");									//換行置頂
		LED3=~LED3;										//輸入一次LED3翻轉一次
	}  
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
End:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
