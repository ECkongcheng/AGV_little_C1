#ifndef __USART_H
#define __USART_H
#include "stm32f10x.h"
typedef struct
{
	uint8_t Buf[100];	//���ڽ��ջ�����
	uint8_t Over;			//���ڽ��ռ��
	uint8_t Len;			//���ڽ��ճ���
}UartBufTypedef;


//��ʼ��
void USART1_Initialise(u32 bound);
void USART2_Initialise(u32 bound);
void USART3_Initialise(u32 bound);
void USART4_Initialise(u32 bound);
//���ڽ��պ�������
void USART_RxFuncConfig(void (* func)(uint8_t data,USART_TypeDef* USARTx));
//�ж�
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
//����
void USART_SendString(USART_TypeDef* USARTx,uint8_t * Send);
#endif

