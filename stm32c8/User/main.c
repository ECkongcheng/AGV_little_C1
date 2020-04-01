/**
  ******************************************************************************
  * @file    main.c
  * @author  �Ŷ�
  * @version V1.0.0
  * @date    2019-11-5
  * @brief   �ƶ�ƽ̨���������������
  ******************************************************************************
  */
/*include file ---------------------------------------------------------------*/
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "pulser.h"
#include "quantity.h"
#include "stdio.h"

/*Golbal data space ----------------------------------------------------------*/

#define UART_COM_STAT   '<'	//����ͨ�ſ�ʼ�ֽ�
#define UART_COM_END		'>'	//����ͨ�Ž����ֽ�

UartBufTypedef g_uartComData = {.Over = 0 ,.Len = 0};//���ڽ��ջ�����

//�����ֽ���д�뵽������
void UsartRxToBuf(uint8_t data)
{
	//��һ����Ϣ�������
	if(g_uartComData.Over == 0)
	{
		//��ʼ
		if(data == UART_COM_STAT )
		{
			//��������
			g_uartComData.Len = 0;
		}
		//����
		else if(data == UART_COM_END)
		{
			//���ս���
			g_uartComData.Over = 1;
		}
		//����
		else
		{
			//д������
			g_uartComData.Buf[g_uartComData.Len] = data;
			//�ƶ����
			g_uartComData.Len = (g_uartComData.Len + 1) % 100;
		}
	}
}


//��õ�����ѹ 0 ������������ 1 ����ϵͳ�����
float getBatteryPackVoltage(uint8_t ch)
{
	switch (ch)
	{
		case 0:
		{
			//��ȡADCͨ��ֵ
			uint16_t adcval = get_adc(ADC_Channel_5);
			//����ADCͨ����ѹ
			float vol = 3.3 * adcval / 4096;
			//��ѹ�ȼ��������ѹ
			vol = vol * 13.1 / 1.1;
			//��������
			vol = vol * 1.0152;
			return vol;
			break;
		}
		case 1:
		{
			//��ȡADCͨ��ֵ
			uint16_t adcval = get_adc(ADC_Channel_4);
			//����ADCͨ����ѹ
			float vol = 3.3 * adcval / 4096;
			//��ѹ�ȼ��������ѹ
			vol = vol * 13.1 / 1.1;
			//��������
			vol = vol * 1.0067;
			return vol; 
			break;
		}
	}
	return 0;
}

//��������������
void Pwm_MotorCtrl(uint8_t * cmd)
{
	//��������ģʽ
	uint8_t ms1 = cmd[1];
	uint8_t ms2 = cmd[5];
	uint8_t ms3 = cmd[9];
	uint8_t ms4 = cmd[13];
		
	//������������
	uint16_t pwm1 = (cmd[2] - 0x30) * 100+ 
									(cmd[3] - 0x30) * 10+ 
									(cmd[4] - 0x30);
	
	uint16_t pwm2 = (cmd[6] - 0x30) * 100+ 
									(cmd[7] - 0x30) * 10+ 
									(cmd[8] - 0x30);
	
	uint16_t pwm3 = (cmd[10] - 0x30) * 100+ 
									(cmd[11] - 0x30) * 10+ 
									(cmd[12] - 0x30);
	
	uint16_t pwm4 = (cmd[14] - 0x30) * 100+ 
									(cmd[15] - 0x30) * 10+ 
									(cmd[16] - 0x30);
									
	//����PWM�Ĵ���
	TIM2->CCR1 = (ms1 == 'A') ? pwm1 : 0;
	TIM2->CCR2 = (ms1 == 'B') ? pwm1 : 0;
	
	TIM2->CCR3 = (ms2 == 'A') ? pwm2 : 0;
	TIM2->CCR4 = (ms2 == 'B') ? pwm2 : 0;
	
	TIM3->CCR1 = (ms3 == 'B') ? pwm3 : 0;
	TIM3->CCR2 = (ms3 == 'A') ? pwm3 : 0;
	
	TIM3->CCR3 = (ms4 == 'B') ? pwm4 : 0;
	TIM3->CCR4 = (ms4 == 'A') ? pwm4 : 0;
	
}

//���ص�ѹֵ
void Adc_BatteryVoltage(uint8_t * cmd)
{
	uint8_t str[50];
	
	//��ʼ
	str[0] = '<';
	
	//��ʶ
	str[1] = 'V';
	
	//���Ƶ�����ѹ
	float ctr = getBatteryPackVoltage(0);
	
	str[2] = (uint8_t)(ctr / 10  ) % 10 + 0x30;
	str[3] = (uint8_t)(ctr       ) % 10 + 0x30;
	str[4] = (uint8_t)(ctr * 10  ) % 10 + 0x30;
	str[5] = (uint8_t)(ctr * 100 ) % 10 + 0x30;
	
	//����������ѹ
	float mtr = getBatteryPackVoltage(1);
	
	str[6] = (uint8_t)(mtr / 10  ) % 10 + 0x30;
	str[7] = (uint8_t)(mtr       ) % 10 + 0x30;
	str[8] = (uint8_t)(mtr * 10  ) % 10 + 0x30;
	str[9] = (uint8_t)(mtr * 100 ) % 10 + 0x30;
	
	//����
	str[10] = '>';
	
	str[11] = 0;
	
	USART_SendString(USART3,str);
	
}

//��Ϣ���ս���
void RxBufAnalysis(UartBufTypedef * buf)
{
	//С�����Ա�ʹ��
	if(buf->Over == 1)
	{	
		//ͨ��Э��
		//��ʼ ��<�� ���� '>'
		//[0] ��ʶ [n] ����
		switch(buf->Buf[0])
		{
			case 'M'://���������ʿ��� <MSXXXSXXXSXXXSXXX> S���� A��B  XXX���ʿ���0-1000 
			{
				Pwm_MotorCtrl(buf->Buf);
				break;
			}
			case 'V'://��ȡ���������
			{
				Adc_BatteryVoltage(buf->Buf);
				break;
			}
		}
		//���δ��ɱ�־λ
		buf->Over = 0;
	}
}
void led_init(void)
{
	GPIO_InitTypeDef gpio;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	gpio.GPIO_Pin = GPIO_Pin_13;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Speed  = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC,&gpio);
}



void led_running(void)
{
	static uint16_t ph,div;
	static _Bool flag;
	div++;
	GPIOC->BSRR = GPIO_Pin_13 << 16 * (ph<div);
	if(div==500)
	{
		div = RESET;
		ph += !flag;
		ph -= flag;
		flag += (ph==500);
		flag *= !(ph==0);
	}
}

/*main function -------------------------------------------------------*/
int main(void)
{		
	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	//��ʱ��ʼ��
	delay_init();

	//PWMͨ����ʼ��
	TIM2_PWM_Init(1000-1,2-1);
	TIM3_PWM_Init(1000-1,2-1); 
	//����ͨ�ų�ʼ��
	USART3_Initialise(115200);  
	//���ô��ڽ��պ���
	USART_RxFuncConfig(USART3,UsartRxToBuf);
	//LED��ʼ��
	led_init(); 
	//ADCת����ʼ��
	ADC_Init_quantity();

	while (1)
	{
		//������Ϣ����
		RxBufAnalysis(&g_uartComData);
		//LED������
		led_running();
	}	 
	return 0;
}


