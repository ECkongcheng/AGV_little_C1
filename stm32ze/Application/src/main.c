/**
  ******************************************************************************
  * @file    main.c
  * @author  �Ŷ�
  * @version V1.0.0
  * @date    2019-11-7
  * @brief   �ƶ�ƽ̨��λ������
  ******************************************************************************
  */

/*include file ---------------------------------------------------------------*/
#include "stm32f10x.h"
#include "encoder.h"
#include "systick.h"
#include "usart.h"
#include "LED.h"
#include "pidctrller.h"
#include "comHandle.h"
#include "syn7318.h"
/*Golbal data space ----------------------------------------------------------*/
uint16_t g_ledflashfreq = 100;


int main(void)
{  
	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	
	//ϵͳSystick��ʼ��
	Systick_init();
	
	//״̬LED��ʼ��
	LED_Init();
	
	//��ʱ����������ʼ��
	TIM1_EncoderMode(0,65535);
	TIM2_EncoderMode(0,65535);
	TIM3_EncoderMode(0,65535);
	TIM4_EncoderMode(0,65535);
	
	//���ڳ�ʼ��
	USART1_Initialise(115200);
	USART2_Initialise(115200);
	USART3_Initialise(115200);
	USART4_Initialise(115200);
	
	//�����ж�ִ������
	creatIRQFunc(PID_Divider);
	
	//ͨ�Ŵ����ʼ��
	comHandleSetup();
	
	/*����*/
	syntest();
	
	while(1)
	{
		//ͨ�����ݴ���
		comHandleLoop();
		//LED״̬��˸
		LED_Flash(g_ledflashfreq);
		//��Ƶ���
		SoundLoop();
	}
	return 0;
}
