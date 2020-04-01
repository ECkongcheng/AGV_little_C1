/**
  ******************************************************************************
  * @file    syn7318.c
  * @author  �Ŷ�
  * @version V1.0.0
  * @date    2019-11-7
  * @brief   ������������ʾ��
  ******************************************************************************
  */
#include "syn7318.h"
#include "usart.h"
#include "string.h"
#include "systick.h"



//����4�жϽ���
void UART4_IRQHandler(void)
{
	
}	


//����4����һ���ַ�
int U4SendChar(int ch) 
{
	 while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET);  //�ȴ����ͽ���
   USART_SendData(UART4,ch); 
}
/*********************************************************************
���� �� ������SYN7318_Put_Char----����һ���ֽں���
������˵������txd---�����͵��ֽڣ�8λ��
����    ������SYN7318_Put_Char('d');  ���͡�d��
*********************************************************************/
void SYN7318_Put_Char(uint8_t txd)
{
	U4SendChar(txd);
}
/*********************************************************************
���� �� ������SYN7318_Put_String----�����ַ�������
������˵������Pst������ַ�����������
              Length���ַ�������
����    ������uchar d[4] = {0x00,0x01,0x02,0x03};
              SYN7318_Put_String(d,4); ---��������d�е�Ԫ��
*********************************************************************/
void SYN7318_Put_String(uint8_t* Pst,uint8_t Length)
{ 
  uint8_t i;
	for(i = 0; i < Length; i++)
	{
		SYN7318_Put_Char(Pst[i]);
	}
}
/*********************************************************************
���� �� ������SYN_TTS----�����ϳɲ��ź���
������˵������Pst�����Ҫ�ϳɲ��ŵ��ı���������
����    ������uchar Data[] = {"��������"};
              SYN_TTS(Data); -----�ϳɲ��ű�������
*********************************************************************/
void SYN_TTS(uint8_t *Pst)
{
	uint8_t Length;
	uint8_t Frame[5];   //���淢�����������
	uint32_t max_tim = 0;
	
	Length = strlen((char *)Pst);
	Frame[0] = 0xFD;      //֡ͷ
	Frame[1] = 0x00;
	Frame[2] = Length+2;
	Frame[3] = 0x01;      //�����ϳɲ�������
	Frame[4] = 0x00;      //���ű����ʽΪ��GB2312��
	
	SYN7318_Put_String(Frame, 5);	
	SYN7318_Put_String(Pst, Length);
	
//	SYN7318_Get_String(Back,4);
//    max_tim = gt_get() + 2000;
//	//���ճɹ�
//	while(!(Back[3] == 0x41) && gt_get_sub(max_tim))
//	{
//		SYN7318_Get_String(Back,4);
//	}
//	
//	max_tim = gt_get() + 2000;	
//	//���м��
//	SYN7318_Get_String(Back,4);
//	while(!(Back[3] == 0x4f) && gt_get_sub(max_tim))
//	{
//		SYN7318_Get_String(Back,4);
//	}
}


//��Ƶ�ļ�����
void SoundFilePlayer(const char * fn)
{
	//ָ��
	uint8_t cmd[100];
	//�ļ���������
	uint16_t fn_len = strlen((const char *)fn);
	
	//֡ͷ
	cmd[0] = 0xfd;
	
	//��Ϣ����
	cmd[1] = ((fn_len + 2) & 0xff00) >> 8;
	cmd[2] = ((fn_len + 2) & 0x00ff);
	
	//������
	cmd[3] = 0x61;
	
	//�������
	cmd[4] = 0x01;
	
	//�������ݶ�
	for(int i = 0;i < fn_len;i++)
	{
		cmd[5 + i] = fn[i];
	}
	//��������
	SYN7318_Put_String(cmd,fn_len + 5);
}



/*����*/
void syntest(void)
{
	delay_ms(4000);
	SoundFilePlayer("E:\\mailkida\\06 msg15.mp3");
	
}


void SoundLoop(void)
{
	
}





