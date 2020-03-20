
/*****************************************����  ����-----------------------------

��Z���ݾ�����	��30��	��1200����1000��	
��R������Ѱ��	��30��	ָ��Ѱ���ĳ�ʼλ��	
��P�����¶�λ	��30��	���¶��嵱ǰ��λ����ֵ	
��G�������˶�	��30��	ָ���˶���Ŀ��λ��	

��J��JOG�˶�	��30��	�������ݣ���ֹ�˶�	
			��31��	��ǰ�˶�����λRPM��ȡֵ400~1600	
			��32��	����˶�����λRPM��ȡֵ400~1600	
��M����ֹģʽ	��31��	λ��ģʽ��ֹ	
			��32��	�ٶ�ģʽ��ֹ	
��K���̵����	��30��	��00xxxx����ʾ�ĸ��̵���	
			
��S����ֽ�ٶ�	��30��	����ת�ٸ�������λRPM��ȡֵ1000~1600	
		-------------------------------------	
��Q����������� ��30��	����������˶�ֹͣ
			  ��31��	����������˶�����
��L����λ����	  ��30��	ʹ��������λ����
			  ��31��	���κ���
			  ��32��	�����м���
			  ��33��	����ǰ����
			  ��34��	�����а�				  
		--------------------------------------
��C����������	��10��	λ�û�����������ͣ�ȡֵ��Χ0~9��	
			��11��	λ�û������������	
			��20��	λ�û�΢�ֲ�������	
			��21��	λ�û�΢�ֲ�������	
			��30��	λ�û����ֲ�������	
			��31��	λ�û����ֲ�������	
			��40��	�ٶȻ�����������ͣ�ȡֵ��Χ0~9��	
			��41��	�ٶȻ������������	
			��50��	�ٶȻ�΢�ֲ�������	
			��51��	�ٶȻ�΢�ֲ�������	
			��60��	�ٶȻ����ֲ�������	
			��61��	�ٶȻ����ֲ�������
		--------------------------------------
 Z�����ݾ��趨	 31	 1201�����һȦ�ľ���		
******************************************/

/************��������--------------------------------------------------------
T���ݸ�ʽ����%Txyz080000X��
		*x  ���������г̿�������״̬�Ķ�����(���ޡ��м��ޡ�ǰ����)
		*y  ���������г̿���״̬�Ķ����Ʊ���(���ޡ��м��ޡ�ǰ����)
		*z	���������г̿���״̬�Ķ����Ʊ���(�а塢�е���ѹֽ)
		*080000 �����ǰλ��
		*X 	���ֵ
F���ݸ�ʽ����%FABii+xxxxX��
		*A����ʾ�趨���ݾ��ٱȣ�0��5�����趨��һ�£�
		*B��Ѱ����ɱ�־��N��ʾδ���Ѱ�㣬D��ʾ�����Ѱ�㣻R��ʾ������
		*ii����λ��������ֵ����10����ʾ10A
		*+xxxx����ǰ�ٶ�ֵ��һ�ֽڱ�ʾ���ţ�����Ϊ�����ٶ���ֵ��
		*X��ǰ11λ���ݵ����ֵ
C/D���ݸ�ʽ��  C--��%C7X262645XP��		D--��%D7X262645XP��
		*7 ��2��io״̬	������Ϊ�� 7	����Ϊ���� 3
		*X ��ͨѶ�������S �����ֶ���
		*C����ʱ:
					26  λ�û�����
					26  λ�û�΢��
					45  λ�û�����
		*D����ʱ:
					26  �ٶȻ�����
					26  �ٶȻ�΢��
					45  �ٶȻ�����	
		*X	�̶���ĸ
		*P 	У���			
**********************************************/

#ifndef _SERVO_H
#define _SERVO_H

#include"main.h"


#define SERVO_COMMD_HEAD 	'%'
#define SERVO_COMMD_END 	'B'

#define SERVO_COMMD_Z 		'Z' //�ݾ�����
#define SERVO_COMMD_R 		'R' //����¼��
#define SERVO_COMMD_P 		'P' //���¶�λ
#define SERVO_COMMD_G		'G' //�����˶�
#define SERVO_COMMD_J 		'J' //JOG�˶�

#define SERVO_COMMD_M 		'M' //��ֹģʽ

#define SERVO_COMMD_K 		'K' //�̵����
#define SERVO_COMMD_S 		'S' //��ֽ�ٶ�

#define SERVO_COMMD_C		'C' //��������
//----------------
#define SERVO_COMMD_Q		'Q' //���������
#define SERVO_COMMD_L		'L' //��λ���ο���


#define SERVO_COMM_LENGTH 	12   //֡����

//------------
#define STAT_10H	"10"
#define STAT_11H	"11"
#define STAT_20H	"20"
#define STAT_21H	"21"
#define STAT_30H	"30"
#define STAT_31H	"31"
#define STAT_32H	"32"
#define STAT_33H	"33"
#define STAT_34H	"34"
#define STAT_40H	"40"
#define STAT_41H	"41"
#define STAT_50H	"50"
#define STAT_51H	"51"
#define STAT_60H	"60"
#define STAT_61H	"61"



//��������  �趨-----------------------
#define	RUN_MOVE	0
#define	JOG_MOVE	1

extern unsigned int const SERVO_SPEED[];


//extern Int8U ServoCommData_Tx[15];
extern Int8U ServoCommData_Rx[15];


typedef struct
{
Int8U head;
Int8U commd;
Int8U stus[2];
//Int8U stus_2;
Int8U data[6];
Int8U check;
Int8U end;
Int8U end_mark;
} SERVO_CTRL;


extern Int8U ServoSpeed_order;  //�����ٶ�
extern Int8U JogSpeed_order;  //�㶯�ٶ�
extern Int8U SpeedDown_Ratio;//���ٱ�
extern Int8U Screw_Pitch;  //�ݾ�
//------C
extern Int8U PositRing_Gain;
extern Int8U PositRing_Diff;
extern Int8U PositRing_Integral;
//------D ����
extern Int8U SpeedRing_Gain;
extern Int8U SpeedRing_Diff;
extern Int8U SpeedRing_Integral;

//---------------------------------
extern Int8U ServoRecvOk_flag;
extern Int8U ServoDisconnect_flag;
extern Int8U ServoDrvInit_flag;
extern Int8U ServoDrvInitOK_flag;
extern Int8U ServoMoving_flag;


//-------F ����----
extern Int8U SearchZero_flag;
extern Int8U OriginalReset_flag;


extern Int16U ServoNow_Speed;

extern Int16U ServoStartDelayTime;

extern Int8U ServoSendCou;

extern Int32U NowSize_last;
extern Int8U ChangeTarget_flag;
extern Int8U ServoBack_flag;
extern Int8U ServoAutoPushFinish_flag;










#endif


