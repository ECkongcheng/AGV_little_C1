/**
  ******************************************************************************
  * @file    systick.c
  * @author  �Ŷ�
  * @version V1.0.0
  * @date    2019-11-7
  * @brief   systick��ʱ�������ж���ϵͳ����ʱ������ṩ
  ******************************************************************************
  */
/*include file ---------------------------------------------------------------*/
#include "stm32f10x.h"
#include "systick.h"
#include "stdlib.h"
/*Golbal data space ----------------------------------------------------------*/
//ϵͳʱ���
uint32_t g_SysTick = 0;
//ϵͳ�ж������б�
FuncLinkList g_IRQFuncList = {.function = NULL , .next = NULL};

//ϵͳSystick��ʼ��
void Systick_init(void)
{
	if (SysTick_Config(SYS_CLK/1000))     //1ms
	{        
			while (1);
	}
	NVIC_SetPriority(SysTick_IRQn, 0x0);
}

//���ϵͳʱ���
uint32_t Sys_GetTick(void)
{
	return g_SysTick;
}

//ϵͳ����������ʱ
void delay_ms(uint32_t ms)
{
	uint32_t lasttick = Sys_GetTick();
	while((Sys_GetTick() - lasttick) < ms);
}


//�����ж�ִ������
void creatIRQFunc(void (* func)(void))
{
	if(g_IRQFuncList.function == NULL)
	{
		g_IRQFuncList.function = func;
	}
	else
	{
		//ָ��ǰ�ڵ�
		FuncLinkList * node = &g_IRQFuncList;
		//�ҵ���һ��Ϊ�յĽڵ�
		while(node->next != NULL)
		{
			node = node->next;
		}
		//Ϊ���������ڵ����ռ�
		FuncLinkList  * newNode = (FuncLinkList *)malloc(sizeof(FuncLinkList));
		
		//��������
		newNode->function = func;
		newNode->next = NULL;
		node->next = newNode;
	}
}

//�˳��ж�ִ������
void exitIRQFunc(void (* func)(void))
{
	//��һ��������Ҫɾ��������
	if(g_IRQFuncList.function == func)
	{
		//��һ�������nextΪ��
		if(g_IRQFuncList.next == NULL)
		{
			g_IRQFuncList.function = NULL;
		}
		else
		{
			g_IRQFuncList.function = g_IRQFuncList.next->function;
			//ָ��ǰ�����ͷŽڵ����һ���ڵ�
			FuncLinkList * Nextnode = g_IRQFuncList.next->next;
			//�ͷ���һ��
			free(g_IRQFuncList.next);
			//д����һ��
			g_IRQFuncList.next = Nextnode;
		}
	}
	//��һ��������Ҫ���´�������
	else
	{
		//ָ��ǰ�ڵ�
		FuncLinkList * node = &g_IRQFuncList;
		
		//����Ҫ�˳�������
		while(node->next->function != func)//��ǰ�ڵ���Ҫɾ���Ľڵ�
		{
			node = node->next;
			
			//�޷��ҵ�ָ���ķ���
			if(node->next == NULL)
			{
				return;
			}
		}
		//ָ��ǰ�����ͷŽڵ����һ���ڵ�
		FuncLinkList * Nextnode = node->next->next ;
		
		//�ͷŽڵ��ڴ�
		free(node->next);
		//ָ�����
		node->next = Nextnode;
	}
}

//�ж�����ִ����
void runIRQFunc(void)
{
	//ָ��ǰ�ڵ�
	FuncLinkList * node = &g_IRQFuncList;
	
	//ִ�е�����
	while(node->function != NULL)
	{
		//ִ��
		node->function();
		
		//����
		if(node->next == NULL)
		{
			return;
		}
		//�ƶ�
		node = node->next;
	}
}


//systick �ж�
void SysTick_Handler()
{
	//�ж�ִ������
	runIRQFunc();
	//ϵͳʱ���
	g_SysTick++;
}


	
	