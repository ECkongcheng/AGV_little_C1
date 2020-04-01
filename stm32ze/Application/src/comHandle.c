/**
  ******************************************************************************
  * @file    conHandle.c
  * @author  �Ŷ�
  * @version V1.0.0
  * @date    2019-11-7
  * @brief   ͨ�Ŵ���
  ******************************************************************************
  */
/*include file ---------------------------------------------------------------*/
#include "comHandle.h"
#include "usart.h"
#include "pidctrller.h"
#include "stdio.h"


/*Golbal data space ----------------------------------------------------------*/
#define UART_COM_STAT   	'<'				//����ͨ�ſ�ʼ�ֽ�
#define UART_COM_END			'>'				//����ͨ�Ž����ֽ�


UartBufTypedef g_ComData[3];				//���ڽ��ջ�����

/* Receive -------------------------------------------------------------------*/

//�����ֽ���д�뵽������
void USART_RxToBuf(uint8_t data,USART_TypeDef* USARTx)
{
	uint8_t cur = 0;
	
	//��ȡͨ�Ŷ˿�ѡ�񻺳���
	if(USARTx == USART1)
	{
		cur = 0;
	}
	else if(USARTx == USART2)
	{
		cur = 1;
	}
	else if(USARTx == USART3)
	{
		cur = 2;
	}
	//������д��
	
	//��һ����Ϣ�������
	if(g_ComData[cur].Over == 0)
	{
		//��ʼ
		if(data == UART_COM_STAT )
		{
			//��������
			g_ComData[cur].Len = 0;
		}
		//����
		else if(data == UART_COM_END)
		{
			//���ս���
			g_ComData[cur].Over = 1;
		}
		//����
		else
		{
			//д������
			g_ComData[cur].Buf[g_ComData[cur].Len] = data;
			//�ƶ����
			g_ComData[cur].Len = (g_ComData[cur].Len + 1) % 100;
		}
	}
}

/* Handle --------------------------------------------------------------------*/

//�趨����ٶ�
void setMotoSpeed(uint8_t * cmd)
{
	//�����ݶ�Э�� <MSXXXSXXX> S�ٶȷ��� XXX�ٶ�ֵ ����ÿ��
	
	int16_t speed[2] = {0,0};
	
	//����ٶ�
	speed[0] = (cmd[2] - 0x30) * 100
						+(cmd[3] - 0x30) * 10
						+(cmd[4] - 0x30);
	
	speed[0] = (cmd[1] == 'A') ? speed[0] : -speed[0];
	
	//�Ҳ��ٶ�
	speed[1] = (cmd[6] - 0x30) * 100
						+(cmd[7] - 0x30) * 10
						+(cmd[8] - 0x30);
	
	speed[1] = (cmd[5] == 'A') ? speed[1] : -speed[1];
	
	//�����ٶ�
	SetTargetSpeed(speed[0],speed[0],speed[1],speed[1]);
	
}

//ROS�ٶ�ָ��������ٶȷ���
void ROS_SpeedDataSubscribe(uint8_t * cmd)
{
	//ͨ��Э��
	//<RSXXXSRRRR> R ��ʶ S����+- XXX���ٶ� mm/s RRR���ٶ� rad/s * 100
	
	//�ٶȵķֽ���ϳ����ͼ��
	
	//���ٶ�
	float vx =  (cmd[2] - 0x30) * 100
	           +(cmd[3] - 0x30) * 10
	           +(cmd[4] - 0x30);
	
	vx = (cmd[1] == 'A') ? vx : -vx;
	
	//���ٶ�
	float w =  (cmd[6] - 0x30) 
	           +(cmd[7] - 0x30) * 0.1
						 +(cmd[8] - 0x30) * 0.01
						 +(cmd[9] - 0x30) * 0.001;
	
	w = (cmd[5] == 'A') ? w : -w;
	
	//��ֵ��̺��ٶȸ����ٶȵ�ĵ��ٶȷֽ�
	float va = (w * 187.833)/0.891749586;
	
	int16_t speed[4];
	
	speed[0] = vx + va;
	speed[1] = vx + va;
	speed[2] = vx - va;
	speed[3] = vx - va;
	
	SetTargetSpeed(speed[1],speed[0],speed[3],speed[2]);

}

//���͵�����Ϣ
void sendBatteryVoltage(uint8_t * cmd)
{
	uint8_t str[50];
	
	float ctv = (cmd[1] - 0x30) * 10 		+ 
							(cmd[2] - 0x30) 				+
							(cmd[3] - 0x30) * 0.1 	+
							(cmd[4] - 0x30) * 0.01	;
	
	float mtv = (cmd[5] - 0x30) * 10 		+ 
							(cmd[6] - 0x30) 				+
							(cmd[7] - 0x30) * 0.1 	+
							(cmd[8] - 0x30) * 0.01	;
	
	sprintf((char*)str,"<V%c%c%c%c%c%c%c%c>",
		cmd[1],cmd[2],cmd[3],cmd[4],cmd[5],cmd[6],cmd[7],cmd[8]);
	
	USART_SendString(USART3,str);
}

//���ͼ������
void sendBatteryVoltageMeasure(uint8_t * cmd)
{
	USART_SendString(USART2,(uint8_t *)"<V>");
}

/* Analysis ------------------------------------------------------------------*/

//ROS���ݽ��մ���
void ROS_RxBufAnalysis(UartBufTypedef * buf)
{
	//�����Ա�ʹ��
	if(buf->Over == 1)
	{	
		//ͨ��Э��
		//��ʼ ��<�� ���� '>'
		//[0] ��ʶ [n] ����
		switch(buf->Buf[0])
		{
			case 'M'://�ƶ��ٶȿ��� 
			{
				setMotoSpeed(buf->Buf);
				break;
			}
			case 'R'://���ٶȽ��ٶȿ���ģʽ
			{
				ROS_SpeedDataSubscribe(buf->Buf);
				break;
			}
			case 'V'://��������������
			{
				sendBatteryVoltageMeasure(buf->Buf);
				break;
			}
		}
		//���δ��ɱ�־λ
		buf->Over = 0;
	}
}

//���������ݽ��մ���
void Ctrller_RxBufAnalysis(UartBufTypedef * buf)
{
	//�����Ա�ʹ��
	if(buf->Over == 1)
	{	
		//ͨ��Э��
		//��ʼ ��<�� ���� '>'
		//[0] ��ʶ [n] ����
		switch(buf->Buf[0])
		{
			case 'V'://���������
			{
				sendBatteryVoltage(buf->Buf);
				break;
			}
		}
		//���δ��ɱ�־λ
		buf->Over = 0;
	}
}

/*Setup and Loop function ----------------------------------------------------*/

//ͨ�Ŵ����ʼ��
void comHandleSetup(void)
{
	//���ô��ڽ��պ���
	USART_RxFuncConfig(USART_RxToBuf);
}

//ͨ�Ŵ���ѭ��
void comHandleLoop(void)
{
	//���ջ��������ݽ���
	ROS_RxBufAnalysis(&g_ComData[2]);
	ROS_RxBufAnalysis(&g_ComData[0]);
	Ctrller_RxBufAnalysis(&g_ComData[1]);
}


