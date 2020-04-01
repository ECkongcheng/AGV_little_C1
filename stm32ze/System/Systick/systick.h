#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"

//ϵͳ��Ƶ
#define SYS_CLK   72000000

#define NULL 			0

//�ж���������
typedef struct func{
	
	void (* function)(void);
	struct func *next;
	
} FuncLinkList;





//ϵͳSystick��ʼ��
void Systick_init(void);
//ϵͳ����������ʱ
void delay_ms(uint32_t ms);
//���ϵͳʱ���
uint32_t Sys_GetTick(void);
//�����ж�ִ������
void creatIRQFunc(void (* func)(void));
//�˳��ж�ִ������
void exitIRQFunc(void (* func)(void));

#endif /*__SYSTICK_H*/
