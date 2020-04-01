#ifndef __PIDCTRLLER_H
#define __PIDCTRLLER_H

#include "stm32f10x.h"

/* Structure type definition -------------------------------------------------*/
typedef struct
{
	float			de ;					//���������ǰ���ֵ difference error
	float			fe ;					//�������������
	float			de1;					//���������ʷ���1
	float			de2;					//���������ʷ���2
	int				out;					//����ͨ������PWM���
	
}PIDDateBaseTypedef;			//pid���ݽṹ����

typedef struct
{
	float			kp;						//����Ȩ��
	float			ki;						//����Ȩ��
	float			kd;						//΢��Ȩ��
	
}PIDParamBaseTypedef;			//pid�����ṹ����




//�趨Ŀ���ٶ�
void SetTargetSpeed(int16_t s1,int16_t s2,int16_t s3,int16_t s4);

//pid������ִ�����ڷ�Ƶ��
void PID_Divider(void);

#endif /*__PIDCTRLLER_H*/
