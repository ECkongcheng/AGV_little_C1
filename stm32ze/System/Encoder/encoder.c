/**
  ******************************************************************************
  * @file    main.c
  * @author  �Ŷ�
  * @version V1.0.0
  * @date    2019-11-7
  * @brief   �ƶ�ƽ̨��ʱ�����������������������ز���
  ******************************************************************************
  */
/*include file ---------------------------------------------------------------*/
#include "encoder.h"

void TIM1_EncoderMode(u32 prescaler,u32 period)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	/* ����TIM1��ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);	/* ʹ��GPIOBʱ�� */
	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE);  //TIM1��ȫ��ӳ��

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		/* �������� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11;	/* ��3���� */
	GPIO_Init(GPIOE, &GPIO_InitStructure);	/* ��ʼ��GPIOA */

	TIM_DeInit(TIM1);	/* ����ʱ��2�Ĵ�����Ϊ��ʼֵ */

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);	/* ����ȱʡֵ */
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;	/* Ԥ��Ƶֵ */
	TIM_TimeBaseStructure.TIM_Period = period;	/* �Զ�����ֵ */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	/* ʱ�ӷָ� */
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	/* ���ϼ��� */
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);	/* ��ʼ����ʱ��2 */

	TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling ,TIM_ICPolarity_Falling);	/* ���ñ�����ģʽ */

	TIM_ICStructInit(&TIM_ICInitStructure);	/* ����ȱʡֵ */
	TIM_ICInitStructure.TIM_ICFilter = 6;	/* ����Ƚ��˲��� */
	TIM_ICInit(TIM1, &TIM_ICInitStructure);	/* ��ʼ����ʱ��2 */

	TIM_SetCounter(TIM1,0);	/* ��������ʼ�� */
	TIM_Cmd(TIM1, ENABLE);	/* ������ʱ��2 */
}

void TIM2_EncoderMode(u32 prescaler,u32 period)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	/* ����TIM2��ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);	/* ʹ��GPIOAʱ�� */

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		/* �������� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;	/* ��3���� */
	GPIO_Init(GPIOA, &GPIO_InitStructure);	/* ��ʼ��GPIOA */

	TIM_DeInit(TIM2);	/* ����ʱ��2�Ĵ�����Ϊ��ʼֵ */

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);	/* ����ȱʡֵ */
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;	/* Ԥ��Ƶֵ */
	TIM_TimeBaseStructure.TIM_Period = period;	/* �Զ�����ֵ */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	/* ʱ�ӷָ� */
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	/* ���ϼ��� */
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);	/* ��ʼ����ʱ��2 */

	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling ,TIM_ICPolarity_Falling);	/* ���ñ�����ģʽ */

	TIM_ICStructInit(&TIM_ICInitStructure);	/* ����ȱʡֵ */
	TIM_ICInitStructure.TIM_ICFilter = 6;	/* ����Ƚ��˲��� */
	TIM_ICInit(TIM2, &TIM_ICInitStructure);	/* ��ʼ����ʱ��2 */

	TIM_SetCounter(TIM2, 0);	/* ��������ʼ�� */
	TIM_Cmd(TIM2, ENABLE);	/* ������ʱ��2 */
}
void TIM3_EncoderMode(u32 prescaler,u32 period)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	/* ����TIM3��ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);	/* ʹ��GPIOAʱ�� */

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		/* �������� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;	/* ��3���� */
	GPIO_Init(GPIOA, &GPIO_InitStructure);	/* ��ʼ��GPIOA */

	TIM_DeInit(TIM3);	/* ����ʱ��2�Ĵ�����Ϊ��ʼֵ */

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);	/* ����ȱʡֵ */
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;	/* Ԥ��Ƶֵ */
	TIM_TimeBaseStructure.TIM_Period = period;	/* �Զ�����ֵ */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	/* ʱ�ӷָ� */
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	/* ���ϼ��� */
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);	/* ��ʼ����ʱ��2 */

	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling ,TIM_ICPolarity_Falling);	/* ���ñ�����ģʽ */

	TIM_ICStructInit(&TIM_ICInitStructure);	/* ����ȱʡֵ */
	TIM_ICInitStructure.TIM_ICFilter = 6;	/* ����Ƚ��˲��� */
	TIM_ICInit(TIM3, &TIM_ICInitStructure);	/* ��ʼ����ʱ��2 */

	TIM_SetCounter(TIM3, 0);	/* ��������ʼ�� */
	TIM_Cmd(TIM3, ENABLE);	/* ������ʱ��2 */
}
void TIM4_EncoderMode(u32 prescaler,u32 period)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	/* ����TIM4��ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);	/* ʹ��GPIOAʱ�� */

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		/* �������� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;	/* ��3���� */
	GPIO_Init(GPIOB, &GPIO_InitStructure);	/* ��ʼ��GPIOA */

	TIM_DeInit(TIM4);	/* ����ʱ��2�Ĵ�����Ϊ��ʼֵ */

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);	/* ����ȱʡֵ */
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;	/* Ԥ��Ƶֵ */
	TIM_TimeBaseStructure.TIM_Period = period;	/* �Զ�����ֵ */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	/* ʱ�ӷָ� */
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	/* ���ϼ��� */
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);	/* ��ʼ����ʱ��2 */

	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling ,TIM_ICPolarity_Falling);	/* ���ñ�����ģʽ */

	TIM_ICStructInit(&TIM_ICInitStructure);	/* ����ȱʡֵ */
	TIM_ICInitStructure.TIM_ICFilter = 6;	/* ����Ƚ��˲��� */
	TIM_ICInit(TIM4, &TIM_ICInitStructure);	/* ��ʼ����ʱ��2 */

	TIM_SetCounter(TIM4, 0);	/* ��������ʼ�� */
	TIM_Cmd(TIM4, ENABLE);	/* ������ʱ��2 */
}


