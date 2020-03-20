#ifndef _UART_CONFIG_H
#define _UART_CONFIG_H

#include "main.h"
#include "uart.h"

#define   UART0_INT		6 
#define   UART2_INT		VIC_UART2//28 

#define   UART0_PRIORITY    4//6
#define   UART2_PRIORITY    6

#define   Baud1        115200//57600//
#define   Baud2        19200//57600//

#define   Baud02        9600//



extern   UART_T param;
extern Int8U Uart3_Data;
extern Int8U Uart9Data;
extern Int8U Uart8Data;
extern Int8U Uart6Data;
extern Int8U Uart_mod;


extern void Uart3_Init(void);
extern void Uart8_Init(void);
extern void Uart9_Init(void);
extern  void Uart3_Test(void);


/*********************************************************************************************************
** �������� ��UART0_SendByte
** �������� ���Բ�ѯ��ʽ����һ�ֽ�����
** ��ڲ��� ��dat	Ҫ���͵�����
** ���ڲ��� ����
*********************************************************************************************************/
void UART0_SendByte(char dat);

/**********************************************************************************************************
** �������� ��UART0_SendStr
** �������� ���򴮿ڷ���һ�ַ���
** ��ڲ��� ��str	Ҫ���͵��ַ�����ָ��
** ���ڲ��� ����
**********************************************************************************************************/
void UART0_SendStr(char *str);

/*********************************************************************************************************
** �������� ��UART0_SendBuf
** �������� ���򴮿ڷ�������
** ��ڲ��� ��uint32  snd_n��  �������ݵĸ�����snd_n С��8
**			  uint8* RcvBufPt�������ַ  
** ���ڲ��� ����
**********************************************************************************************************/
void UART0_SendBuf(pInt8U RcvBufPt, Int32U snd_n);

/*********************************************************************************************************
** �������� ��IRQ_UART0
** �������� ������0�����жϷ������
** ��ڲ��� ����
** ���ڲ��� ����
*******************************************************************************************************/
void UART0IntrHandler(void);
/*********************************************************************************************************
** �������� ��UART0_Init
** �������� �����0���ȫ����ʼ������
** ��ڲ��� ����
** ���ڲ��� ����
*********************************************************************************************************/
void UART0_Init(void);
void UART3_Init(void);

extern void UART8_SendByte(char dat);
extern void UART8_SendStr(char *str);
extern void UART8_SendBuf(pInt8U RcvBufPt, Int32U snd_n);
extern void UART8IntrHandler(void);

extern void UART9_SendByte(char dat);
extern void UART9_SendStr(char *str);
extern void UART9_SendBuf(pInt8U RcvBufPt, Int32U snd_n);
extern void UART9IntrHandler(void);

////extern void UART3_SendStr(char *str);//Ϊ����ԭ��UART ��ӳ�䵽UART9 



#endif
