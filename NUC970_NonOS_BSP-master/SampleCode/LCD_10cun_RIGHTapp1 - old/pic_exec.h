


#ifndef _PIC_EXEC_H
#define _PIC_EXEC_H

#include"main.h"
#include "file.h"


#define PAGE_5_LINE 	0
#define PAGE_7_LINE 	1



//----------- ���鱳����ɫ------------
#define TEXT_TAB_BACK_COLOR		0xef7d//0xce79
#define TEXT_TAB_FRONT_COLOR	0xFFE6//YELLOW_COLOR
#define STEP_BACK_COLOR		0x9CD3  //
#define CURREN_STEP_BACK_COLOR	0xe71c//TEXT_TAB_BACK_COLOR	//��ǰsize����ɫ
#define CURREN_UNIT_BACK_COLOR	STEP_BACK_COLOR	//��ǰ��λ����ɫ
#define FRONT_KNIFE_BACK_COLOR	0xf78a
#define F1_6BUTT_BACK_COLOR		0x73ae//0x43bc  //
#define WIN_DOWN_BACK_COLOR		0x73ae//0x22FC//�ײ�����ɫ

#define F1_4_WIDE	40//48
#define F1_4_HIGH	48//48

// #define F_KEY_WIDE	56
// #define F_KEY_HIGH	46

#define FORWARD_WIDE	F1_4_WIDE
#define FORWARD_HIGH	F1_4_HIGH

// #define DELETE_WIDE		82
// #define DELETE_HIGH		31
//-------������ ������
#define CALCUL_WIN_X	580//578
#define CALCUL_WIN_Y	55//55
#define CALCUL_WIDE		182//
#define CALCUL_HIGH		350//330
#define CALCUL_COLOR	0x879e

#define CALCUL_TEXT_X	(CALCUL_WIN_X+10)
#define CALCUL_TEXT_Y	(CALCUL_WIN_Y+15)
#define CALCUL_TEXT_H	70
#define CALCUL_TEXT_W	185//160
#define CALCUL_TEXT_END	(CALCUL_TEXT_X+CALCUL_TEXT_W)//-12)

#define CALCUL_RESULT_X	(CALCUL_TEXT_X)//+10)
#define CALCUL_RESULT_Y	(CALCUL_TEXT_Y+CALCUL_TEXT_H+3)
#define CALCUL_RESULT_H	35//40
#define CALCUL_RESULT_W	(CALCUL_TEXT_W)//-10)
//
#define BUTT_WIDE	45//36
#define BUTT_HIGH	45//38
#define BUTT_GAP_X	3//5
#define BUTT_GAP_Y	2//5
#define BUTT_X1		(CALCUL_WIN_X+10)
#define BUTT_X2		(BUTT_X1+BUTT_WIDE+BUTT_GAP_X)
#define BUTT_X3		(BUTT_X2+BUTT_WIDE+BUTT_GAP_X)
#define BUTT_X4		(BUTT_X3+BUTT_WIDE+BUTT_GAP_X)
#define BUTT_X5		(BUTT_X4+BUTT_WIDE+BUTT_GAP_X)
#define BUTT_X6		(BUTT_X5+BUTT_WIDE+BUTT_GAP_X)


#define BUTT_Y1		(CALCUL_RESULT_Y+CALCUL_RESULT_H+5)
#define BUTT_Y2		(BUTT_Y1+BUTT_HIGH+BUTT_GAP_Y)
#define BUTT_Y3		(BUTT_Y2+BUTT_HIGH+BUTT_GAP_Y)
#define BUTT_Y4		(BUTT_Y3+BUTT_HIGH+BUTT_GAP_Y)
#define BUTT_Y5		(BUTT_Y4+BUTT_HIGH+BUTT_GAP_Y)
//�����ͷ
#define BUTT_WIDE_ARROW	60//50
#define BUTT_HIGH_ARROW	125//95

//--------����� ��ť���붨��
#define BUTT_INSERT	0
#define BUTT_EXIT	1
#define BUTT_EQU	2
#define BUTT_ENTER	3
#define BUTT_RUN	4
#define BUTT_CLEAR	5
#define BUTT_DOT	6
#define BUTT_MUL	7
#define BUTT_DIV	8
#define BUTT_PLUS	9
#define BUTT_0	10
#define BUTT_1	11
#define BUTT_2	12
#define BUTT_3	13
#define BUTT_4	14
#define BUTT_5	15
#define BUTT_6	16
#define BUTT_7	17
#define BUTT_8	18
#define BUTT_9	19
#define BUTT_SUB	20
#define BUTT_UP		21
#define BUTT_DOWN	22

// #define BUTT_SPAC	23
#define BUTT_LEFT	23
#define BUTT_RIGHT	24
//---------------
#define BUTT_SHIFT	30

#define BUTT_F1	31
#define BUTT_F2	32
#define BUTT_F3	33
#define BUTT_F4	34
#define BUTT_F5	35


//------------ͼ���С����---------------------------
//#define	 FX_BUTT_SIZE	10856//6968//


//------------�ļ������ַ--------
#define  PIC_DIS_SAVE1		(DOWNFILE_SDRAM_ADD+0x200000)    //0x81680000��ǰ��ʾ���� �ݴ���1
#define  PIC_DIS_SAVE2		(PIC_DIS_SAVE1+0x00100000)//0x8157d000    //��ǰ��ʾ���� �ݴ���2
#define  PIC_DIS_SAVE3		(PIC_DIS_SAVE2+0x00100000)//0x81600000    //��ǰ��ʾ���� �ݴ���3
#define  PIC_DIS_SAVE4		(PIC_DIS_SAVE3+0x00100000)//0x8167d000    //��ǰ��ʾ���� �ݴ���4


#define  df_zk_sdram        (PIC_DIS_SAVE4+0x00100000)// 0x81880000            //0x81700000�ֿ�2M

#define  START_PIC_sdram   (df_zk_sdram+0x200000)  //0xa0800000         //����ͼƬ
#define  WOEK_BACK_dis     (START_PIC_sdram+2359350)        //��������
#define  PEAR_sdram			(WOEK_BACK_dis+2359350)//Ѽ��
//************
#define  RIGHT_ARROW_sdram	(PEAR_sdram+98304)// �Ҽ�ͷ -->
#define  SCHEDULE_sdram		(RIGHT_ARROW_sdram+3128)//������


//���� �����ź�
#define  POWER_SWITCH_BUTT_SIZE    5832
#define  POWER_ON_UP_sdram   (SCHEDULE_sdram+32768)	//��Դ��up
#define  POWER_ON_DOWN_sdram (POWER_ON_UP_sdram+POWER_SWITCH_BUTT_SIZE)	//��Դ��down
#define  POWER_OFF_UP_sdram    (POWER_ON_DOWN_sdram+POWER_SWITCH_BUTT_SIZE)	//��Դ��up
#define  POWER_OFF_DOWN_sdram  (POWER_OFF_UP_sdram+POWER_SWITCH_BUTT_SIZE)	//��Դ��down
#define  POWER_CTRL_sdram (POWER_OFF_DOWN_sdram+POWER_SWITCH_BUTT_SIZE)	//��Դ
#define  LIGHT_BUTT_SIZE    4160
#define  LIGHT_KNIFE_UP_sdram	(POWER_CTRL_sdram+POWER_SWITCH_BUTT_SIZE)	//�Ե��� up
#define  LIGHT_KNIFE_DOWN_sdram	(LIGHT_KNIFE_UP_sdram+LIGHT_BUTT_SIZE)	//�Ե��� down
#define  LIGHT_CTRL_sdram	(LIGHT_KNIFE_DOWN_sdram+LIGHT_BUTT_SIZE)	//���0 up
#define  LIGHT_LED_UP_sdram	(LIGHT_CTRL_sdram+LIGHT_BUTT_SIZE)	//������  up
#define  LIGHT_LED_DOWN_sdram	(LIGHT_LED_UP_sdram+LIGHT_BUTT_SIZE)	//������ down
#define  AIR_SWITCH_SIZE   8168
#define  PUMP_OFF_UP_sdram	(LIGHT_LED_DOWN_sdram+LIGHT_BUTT_SIZE)	// ��� ��up
#define  PUMP_OFF_DOWN_sdram	(PUMP_OFF_UP_sdram+AIR_SWITCH_SIZE)	// ��� ��down
#define  PUMP_ON_UP_sdram	(PUMP_OFF_DOWN_sdram+AIR_SWITCH_SIZE)	// ��� ��up
#define  PUMP_ON_DOWN_sdram	(PUMP_ON_UP_sdram+AIR_SWITCH_SIZE)	// ��� ��down
//����ģʽ
#define  SENSOR_STUS_SIZE	4160
#define  NORMAL_KNIFE_UP_sdram 	(PUMP_ON_DOWN_sdram+AIR_SWITCH_SIZE)	//��������up
#define  NORMAL_KNIFE_DOWN_sdram 	(NORMAL_KNIFE_UP_sdram+AIR_SWITCH_SIZE)	//��������down
#define  ELECTRIC_KNIFE_UP_sdram 	(NORMAL_KNIFE_DOWN_sdram+SENSOR_STUS_SIZE)	//�綯����up
#define  ELECTRIC_KNIFE_DOWN_sdram 	(ELECTRIC_KNIFE_UP_sdram+SENSOR_STUS_SIZE)	//�綯����down
#define  MANUAL_KNIFE_UP_sdram 	(ELECTRIC_KNIFE_DOWN_sdram+SENSOR_STUS_SIZE)	//�ֶ�����up
#define  MANUAL_KNIFE_DOWN_sdram 	(MANUAL_KNIFE_UP_sdram+SENSOR_STUS_SIZE)	//�ֶ�����down
//
#define  PUSH_BUTT_sdram		(MANUAL_KNIFE_DOWN_sdram+SENSOR_STUS_SIZE)	//��ֽbutton
//
#define  MODE_CHANGE_BUTT_SIZE	5880
#define  TEACH_MOD_BUTT_sdram	(PUSH_BUTT_sdram+8504)	//ʾ��mod��ť
#define  AUTOCUT_MOD_BUTT_sdram	(TEACH_MOD_BUTT_sdram+MODE_CHANGE_BUTT_SIZE)	//�Զ�cut mod��ť

//************��ģʽ************
#define  MAIN_MODE_BUTT_SIZE	6968
//-------------up
#define  FIND_MOD_UP_sdram      (AUTOCUT_MOD_BUTT_sdram+MODE_CHANGE_BUTT_SIZE) //����ģʽup
#define  MANUAL_MOD_UP_sdram		(FIND_MOD_UP_sdram+MAIN_MODE_BUTT_SIZE)   //�ֶ�ģʽup
#define  AUTO_MOD_UP_sdram		    (MANUAL_MOD_UP_sdram+MAIN_MODE_BUTT_SIZE)   //�Զ�ģʽup
// #define  TEACH_MOD_UP_sdram		(AUTO_MOD_UP_sdram+FX_BUTT_SIZE)   //ʾ��ģʽup
// #define  AUTO_CUT_MOD_UP_sdram   (TEACH_MOD_UP_sdram+FX_BUTT_SIZE)   //�Ե�ģʽup

//------------down
#define  FIND_MOD_DOWN_sdram      (AUTO_MOD_UP_sdram+MAIN_MODE_BUTT_SIZE) //����ģʽdown
#define  MANUAL_MOD_DOWN_sdram		(FIND_MOD_DOWN_sdram+MAIN_MODE_BUTT_SIZE)   //�ֶ�ģʽdown
#define  AUTO_MOD_DOWN_sdram		    (MANUAL_MOD_DOWN_sdram+MAIN_MODE_BUTT_SIZE)   //�Զ�ģʽdown

//------------------��ģʽͼ��
#define	 FUN_PIC_SIZE	420056
#define	 F1_LABEL_MOD_PIC_sdram		(AUTO_MOD_DOWN_sdram+MAIN_MODE_BUTT_SIZE)//��ǩģʽ ͼƬ
#define	 F2_DIVIDE_MOD_PIC1_sdram	(F1_LABEL_MOD_PIC_sdram+FUN_PIC_SIZE)//�ȷ���ģʽ	ͼƬ
#define	 F3_DIVIDE_MOD_PIC2_sdram	(F2_DIVIDE_MOD_PIC1_sdram+FUN_PIC_SIZE)//�ȷ�ֵģʽ	ͼƬ
#define	 F2_DATAS_MOD_PIC_sdram		(F3_DIVIDE_MOD_PIC2_sdram+FUN_PIC_SIZE)//����ģʽ ͼƬ
#define	 F3_CLOCK_MOD_PIC_sdram		(F2_DATAS_MOD_PIC_sdram+FUN_PIC_SIZE)//ʱ��ģʽ ͼƬ
#define	 PASSWORD_MOD_PIC_sdram		(F3_CLOCK_MOD_PIC_sdram+FUN_PIC_SIZE)//����ģʽ ͼƬ
#define  RULER_SIZE		384056//294616
#define	 F1_RULER_MOD_PIC_sdram		(PASSWORD_MOD_PIC_sdram+FUN_PIC_SIZE)//��׼ģʽ ͼƬ
#define	 MAIN_TABLE_PIC_sdram		(F1_RULER_MOD_PIC_sdram+RULER_SIZE)	//�б�ģʽͼƬ
//***********************************F1,2,3,4...
//�Զ�ģʽ��
#define  FX_BUTT_SIZE	6088
#define  F1_LABELS_UP_sdram        (MAIN_TABLE_PIC_sdram+82256)//��ǩup
#define  F2_DIVIDE_UP_sdram       (F1_LABELS_UP_sdram+FX_BUTT_SIZE)  //�ȷ�up
#define	 F3_INSERT_UP_sdram		(F2_DIVIDE_UP_sdram+FX_BUTT_SIZE)   //F3����up
#define  F4_DELETE_UP_sdram		(F3_INSERT_UP_sdram+FX_BUTT_SIZE)	//F4ɾ��up
#define	 F5_ADD_UP_sdram		(F4_DELETE_UP_sdram+FX_BUTT_SIZE)//F5++
#define	 F6_SUB_UP_sdram		(F5_ADD_UP_sdram+FX_BUTT_SIZE)//F6--
// #define  F4_SWITCH_UP_sdram		(F3_SELECT_PRO_UP_sdram+FX_BUTT_SIZE)//�л�ѡ��up
// #define  F5_DELETEALL_UP_sdram	(F4_SWITCH_UP_sdram+FX_BUTT_SIZE)//ɾ��ȫ��up

//-------�ֶ�ģʽ��
#define	 F1_PARAMETER_sdram		(F6_SUB_UP_sdram+FX_BUTT_SIZE)	//F1����
#define	 F2_RULER_sdram		(F1_PARAMETER_sdram+FX_BUTT_SIZE)	//F2��׼
#define	 F3_CLOCK_sdram			(F2_RULER_sdram+FX_BUTT_SIZE)	//F3����ʱ��
#define	 F4_WHEEL0_sdram		(F3_CLOCK_sdram+FX_BUTT_SIZE) //�������ֿ���0
#define	 F4_WHEEL1_sdram		(F4_WHEEL0_sdram+FX_BUTT_SIZE) //�������ֿ���1
// #define	 F5_WHEEL0_sdram		(F4_WHEEL1_sdram+FX_BUTT_SIZE) //�������ֿ���0
// #define	 F5_WHEEL1_sdram		(F5_WHEEL0_sdram+FX_BUTT_SIZE) //�������ֿ���1
#define	 F5_PULSE_UP_sdram		(F4_WHEEL1_sdram+FX_BUTT_SIZE)//F5���嵱��
#define  F6_TST_IO_sdram		(F5_PULSE_UP_sdram+FX_BUTT_SIZE)//IO ����

// #define	 F6_AMEND0_sdram		(F6_TST_IO_sdram+FX_BUTT_SIZE) //--------------�޸�ƫ�Ƴߴ�
// #define	 F6_AMEND1_sdram		(F6_AMEND0_sdram+FX_BUTT_SIZE) //--------------�޸�ƫ�Ƴߴ�
// #define	 F4_PULSE_UP_sdram		(F6_AMEND1_sdram+FX_BUTT_SIZE)	//F4���嵱��
//
#define	 MACHINE_PIC_sdram		(F6_TST_IO_sdram+FX_BUTT_SIZE)//----����ͼƬ

#define  F1_OK_UP_sdram		(MACHINE_PIC_sdram+576056)//F1���up
#define  F2_EXIT_UP_sdram		(F1_OK_UP_sdram+FX_BUTT_SIZE)//F2�˳�up
#define  L_R_ARROW_sdram	(F2_EXIT_UP_sdram+FX_BUTT_SIZE)//���Ҽ�ͷ
#define  F2_DIVNUM_UP_sdram		(L_R_ARROW_sdram+FX_BUTT_SIZE)//F2�ȷ���up
#define  F2_DIVNUM_DOWN_sdram		(F2_DIVNUM_UP_sdram+FX_BUTT_SIZE)//F2�ȷ���down
#define  F3_DIVDATA_UP_sdram		(F2_DIVNUM_DOWN_sdram+FX_BUTT_SIZE)//F3�ȷ�ֵup
#define  F3_DIVDATA_DOWN_sdram		(F3_DIVDATA_UP_sdram+FX_BUTT_SIZE)//F3�ȷ�ֵdown
#define  UP_ARROW_UP_sdram		(F3_DIVDATA_DOWN_sdram+FX_BUTT_SIZE)//�ϼ�ͷup
#define  DOWN_ARROW_UP_sdram		(UP_ARROW_UP_sdram+FX_BUTT_SIZE)//�¼�ͷup

//����ѡ��
#define  F1_LOOK_UP_sdram		(DOWN_ARROW_UP_sdram+FX_BUTT_SIZE)//F1�鿴 ������Ϣup
#define  F2_BY_TIME_UP_sdram	(F1_LOOK_UP_sdram+FX_BUTT_SIZE)//F2 ��ʱ�� ��ʾup
#define  F2_BY_TIME_DOWN_sdram	(F2_BY_TIME_UP_sdram+FX_BUTT_SIZE)//F2 ��ʱ�� ��ʾdown
#define  F3_BY_NUM_UP_sdram		(F2_BY_TIME_DOWN_sdram+FX_BUTT_SIZE)//F3 ����� ��ʾup
#define  F3_BY_NUM_DOWN_sdram	(F3_BY_NUM_UP_sdram+FX_BUTT_SIZE)//F3 ����� ��ʾdown
#define  F4_DELETE_ONE_PRO_UP_sdram	(F3_BY_NUM_DOWN_sdram+FX_BUTT_SIZE)//F4ɾ��һ��pro
#define  F5_DELETE_ALL_PRO_UP_sdram	(F4_DELETE_ONE_PRO_UP_sdram+FX_BUTT_SIZE)//F5ɾ������pro
//������Ϣ
#define	 F1_PINYIN_UP_sdram		(F5_DELETE_ALL_PRO_UP_sdram+FX_BUTT_SIZE)//ƴ������up
#define	 F1_PINYIN_DOWN_sdram		(F1_PINYIN_UP_sdram+FX_BUTT_SIZE)//ƴ������down
#define	 F2_CHAR_UP_sdram		(F1_PINYIN_DOWN_sdram+FX_BUTT_SIZE)//��ĸ����up
#define	 F2_CHAR_DOWN_sdram		(F2_CHAR_UP_sdram+FX_BUTT_SIZE)//��ĸ����down
#define	 F3_NUM_UP_sdram		(F2_CHAR_DOWN_sdram+FX_BUTT_SIZE)//��������up
#define	 F3_NUM_DOWN_sdram		(F3_NUM_UP_sdram+FX_BUTT_SIZE)//��������down
#define  F4_EXIT_UP_sdram		(F3_NUM_DOWN_sdram+FX_BUTT_SIZE)//F4�˳�up
// #define	 F6_EXIT_BUTT_sdram		(F4_EXIT_UP_sdram+FX_BUTT_SIZE) //F6�˳� ��ť
#define	 ENTER_BUTT_sdram		(F4_EXIT_UP_sdram+FX_BUTT_SIZE) //ȷ�� ��ť


//---------------------
#define KNIFE_SENSOR_PIC_SIZE	5456
#define  KNIFE_UP_sdram		(ENTER_BUTT_sdram+FX_BUTT_SIZE)//����
#define  KNIFE_DOWN_sdram	(KNIFE_UP_sdram+KNIFE_SENSOR_PIC_SIZE)//����
#define  PRESS_UP_sdram		(KNIFE_DOWN_sdram+KNIFE_SENSOR_PIC_SIZE)//ѹ��
#define  PRESS_DOWN_sdram	(PRESS_UP_sdram+KNIFE_SENSOR_PIC_SIZE)//ѹ��
#define  IR_LINE_sdram		(PRESS_DOWN_sdram+KNIFE_SENSOR_PIC_SIZE)   //����
#define  IR_CUT_sdram		(IR_LINE_sdram+KNIFE_SENSOR_PIC_SIZE) //�� ����

#define  FRONT_PAGE_UP_sdram	(IR_CUT_sdram+KNIFE_SENSOR_PIC_SIZE)//ǰ��
#define  BACK_PAGE_UP_sdram		(FRONT_PAGE_UP_sdram+9656)//����up

// #define  FAST_FORWD_UP_sdram	(DOWN_ARROW_UP_sdram+FX_BUTT_SIZE)	//���up
// #define  FAST_BACK_UP_sdram		(FAST_FORWD_UP_sdram+FX_BUTT_SIZE) 	//����up




//---------------���  button
#define  FLAG_BUTT_SIZE		4088
#define	 RED_KNIFE_BUTT_sdram	(BACK_PAGE_UP_sdram+9656) //�쵶 ��ť
#define	 PUSH_PAPER_BUTT_sdram	(RED_KNIFE_BUTT_sdram+FLAG_BUTT_SIZE) //��ֽ ��ť
#define	 SORT_PAPER_BUTT_sdram	(PUSH_PAPER_BUTT_sdram+FLAG_BUTT_SIZE) //��ֽ ��ť
#define	 PRE_PAPER_BUTT_sdram	(SORT_PAPER_BUTT_sdram+FLAG_BUTT_SIZE) //ѹֽ ��ť
#define	 AIR_BED_BUTT_sdram		(PRE_PAPER_BUTT_sdram+FLAG_BUTT_SIZE) //���� ��ť
#define  ALL_KNIFE_BUTT_sdram	(AIR_BED_BUTT_sdram+FLAG_BUTT_SIZE)//ȫ���� +++++++++++++++
//---------------���  pic
#define  ALL_FLAG_SIZE		4616
#define  RED_KNIFE_F_sdram	(ALL_KNIFE_BUTT_sdram+FLAG_BUTT_SIZE)//�쵶���	ͼ��
#define  PUSH_PAPER_F_sdram (RED_KNIFE_F_sdram+ALL_FLAG_SIZE)//��ֽ���	ͼ��
#define  SORT_PAPER_F_sdram (PUSH_PAPER_F_sdram+ALL_FLAG_SIZE)//��ֽ���	ͼ��
#define  PRE_PAPER_F_sdram (SORT_PAPER_F_sdram+ALL_FLAG_SIZE)//ѹֽ���	ͼ��
#define  AIR_BED_F_sdram 	(PRE_PAPER_F_sdram+ALL_FLAG_SIZE)//������	ͼ��

//--------
#define  RUN_BUTT_SIZE		5456
#define  RUN_BUTT_sdram		(AIR_BED_F_sdram+ALL_FLAG_SIZE)//���� ��ť
#define  STOP_UP_sdram		(RUN_BUTT_sdram+RUN_BUTT_SIZE)	//stop
// #define  SHIFT_BUTT_UP_sdram		(STOP_UP_sdram+RUN_BUTT_SIZE)//shift ��ťup
// #define  SHIFT_BUTT_DOWN_sdram		(SHIFT_BUTT_UP_sdram+RUN_BUTT_SIZE)//shift ��ťdown



#define  DELETE_ALL_SIZE 	7256
#define  DELETE_ALL_UP_sdram		(STOP_UP_sdram+RUN_BUTT_SIZE)//delete 
#define  DATA_AMEND0_sdram		(DELETE_ALL_UP_sdram+DELETE_ALL_SIZE) //--------------�޸�ƫ�Ƴߴ�
#define	 DATA_AMEND1_sdram		(DATA_AMEND0_sdram+DELETE_ALL_SIZE) //--------------�޸�ƫ�Ƴߴ�



//---������--
#define CAL_BUT_SIZE	6176//4856
#define CAL_WIND_sdram 	(DATA_AMEND1_sdram+DELETE_ALL_SIZE)
//number
#define CAL_0_UP_sdram		(CAL_WIND_sdram+230934)
#define CAL_0_DOWN_sdram		(CAL_0_UP_sdram+CAL_BUT_SIZE)
#define CAL_1_UP_sdram		(CAL_0_DOWN_sdram+CAL_BUT_SIZE)
#define CAL_1_DOWN_sdram		(CAL_1_UP_sdram+CAL_BUT_SIZE)
#define CAL_2_UP_sdram		(CAL_1_DOWN_sdram+CAL_BUT_SIZE)
#define CAL_2_DOWN_sdram		(CAL_2_UP_sdram+CAL_BUT_SIZE)
#define CAL_3_UP_sdram		(CAL_2_DOWN_sdram+CAL_BUT_SIZE)
#define CAL_3_DOWN_sdram		(CAL_3_UP_sdram+CAL_BUT_SIZE)
#define CAL_4_UP_sdram		(CAL_3_DOWN_sdram+CAL_BUT_SIZE)
#define CAL_4_DOWN_sdram		(CAL_4_UP_sdram+CAL_BUT_SIZE)
#define CAL_5_UP_sdram		(CAL_4_DOWN_sdram+CAL_BUT_SIZE)
#define CAL_5_DOWN_sdram		(CAL_5_UP_sdram+CAL_BUT_SIZE)
#define CAL_6_UP_sdram		(CAL_5_DOWN_sdram+CAL_BUT_SIZE)
#define CAL_6_DOWN_sdram		(CAL_6_UP_sdram+CAL_BUT_SIZE)
#define CAL_7_UP_sdram		(CAL_6_DOWN_sdram+CAL_BUT_SIZE)
#define CAL_7_DOWN_sdram		(CAL_7_UP_sdram+CAL_BUT_SIZE)
#define CAL_8_UP_sdram		(CAL_7_DOWN_sdram+CAL_BUT_SIZE)
#define CAL_8_DOWN_sdram		(CAL_8_UP_sdram+CAL_BUT_SIZE)
#define CAL_9_UP_sdram		(CAL_8_DOWN_sdram+CAL_BUT_SIZE)
#define CAL_9_DOWN_sdram		(CAL_9_UP_sdram+CAL_BUT_SIZE)
#define CAL_CLR_UP_sdram		(CAL_9_DOWN_sdram+CAL_BUT_SIZE)
#define CAL_CLR_DOWN_sdram		(CAL_CLR_UP_sdram+CAL_BUT_SIZE)
#define CAL_DOT_UP_sdram		(CAL_CLR_DOWN_sdram+CAL_BUT_SIZE)
#define CAL_DOT_DOWN_sdram		(CAL_DOT_UP_sdram+CAL_BUT_SIZE)
#define CAL_ADD_UP_sdram		(CAL_DOT_DOWN_sdram+CAL_BUT_SIZE)
#define CAL_ADD_DOWN_sdram		(CAL_ADD_UP_sdram+CAL_BUT_SIZE)
#define CAL_SUB_UP_sdram		(CAL_ADD_DOWN_sdram+CAL_BUT_SIZE)
#define CAL_SUB_DOWN_sdram		(CAL_SUB_UP_sdram+CAL_BUT_SIZE)
#define CAL_MUL_UP_sdram		(CAL_SUB_DOWN_sdram+CAL_BUT_SIZE)
#define CAL_MUL_DOWN_sdram		(CAL_MUL_UP_sdram+CAL_BUT_SIZE)
#define CAL_DIV_UP_sdram		(CAL_MUL_DOWN_sdram+CAL_BUT_SIZE)
#define CAL_DIV_DOWN_sdram		(CAL_DIV_UP_sdram+CAL_BUT_SIZE)
//--== ok
#define CAL_EQU_SIZE 13016
#define CAL_EQU_UP_sdram		(CAL_DIV_DOWN_sdram+CAL_BUT_SIZE)
#define CAL_EQU_DOWN_sdram		(CAL_EQU_UP_sdram+CAL_EQU_SIZE)
#define CAL_OK_UP_sdram		(CAL_EQU_DOWN_sdram+CAL_EQU_SIZE)
#define CAL_OK_DOWN_sdram		(CAL_OK_UP_sdram+CAL_EQU_SIZE)

//---------------------------------
#define  K_SIZE_sdram		(CAL_OK_DOWN_sdram+CAL_EQU_SIZE)//0x82e00000       //������ ������




//**************ͼƬ��ʾλ�ö���*******
//---�����Լ���ʾ--
#define COMPUTER_TEST_HINT_X	40
#define COMPUTER_TEST_HINT_Y	520//650

//�Ҽ�ͷ-->
#define  RIGHT_ARROW_X	75//90
#define  RIGHT_ARROW_Y	180//230
#define  RIGHT_ARROW_WIDE	32//30
#define  RIGHT_ARROW_HIGH	32
#define  TEXT_LINE_H	(32-1)
//�б��ұ�ҳ ��ʼλ��
#define  RIGHT_PAGE_X	400//510
//������
#define  SCHEDULE_X		540//700
#define  SCHEDULE_Y		165//215
#define  SCHEDULE_WIDE	26//30
#define  SCHEDULE_HIGH	250//302
//���ȿ�
#define  SCHEDULE_DOT_X1	(SCHEDULE_X+6)
#define  SCHEDULE_DOT_X2	(SCHEDULE_DOT_X1+14)
#define  SCHEDULE_DOT_Y	(SCHEDULE_Y+60)//


//******************�����ʾ  ͼ��
#define FLAG_PIC_WIDE	40//60
#define FLAG_PIC_HIGH	25//35
//�쵶	��־pic
#define  RED_KNIFE_PIC_X	295//350
#define  RED_KNIFE_PIC_Y	(RIGHT_ARROW_Y+3)//160
//��ֽ���pic
#define  PUSH_FLAG_PIC_X	RED_KNIFE_PIC_X	
#define  PUSH_FLAG_PIC_Y	RED_KNIFE_PIC_Y
//ѹֽpic
#define	 PRE_FLAG_PIC_X		RED_KNIFE_PIC_X	
#define  PRE_FLAG_PIC_Y	 	RED_KNIFE_PIC_Y
//��ֽpic
#define	 SORT_FLAG_PIC_X	RED_KNIFE_PIC_X	
#define  SORT_FLAG_PIC_Y	RED_KNIFE_PIC_Y
//����pic
#define  AIR_FLAG_PIC_X		(RED_KNIFE_PIC_X+45)
#define  AIR_FLAG_PIC_Y		RED_KNIFE_PIC_Y
#define  TABLE_END_COL		(AIR_FLAG_PIC_X+FLAG_PIC_WIDE)


//�ߴ������
#define  SIZE_WINDOW_X	5//
#define  SIZE_WINDOW_Y	555//710//560//
#define  SIZE_WINDOW_WIDE	185//120
#define  SIZE_WINDOW_HIGH	40//50//30
#define  SIGN_2WIDE	32

//��ʾ��
#define  REMIND_WINDOW_X	260
#define  REMIND_WINDOW_Y	560
#define  REMIND_LENGTH		400  //��ʾ�򳤶�
//------------------�м��ҳ---------------------------
#define  MIDDLE_PAGE_X	RIGHT_ARROW_X//60
#define  MIDDLE_PAGE_Y	(RIGHT_ARROW_Y-15)//235
//----------------��ҳ��С
#define  M_PAGE_WIDE	493//650
#define  M_PAGE_HIGH	250//305

//������ʾ���С
#define  START_PROM_WIDE	400//600
#define  START_PROM_HIGH	30
//������һ�й��� ��ʾ
#define	 START_PROMPT_X1	130//REMIND_WINDOW_X
#define	 START_PROMPT_Y1	500
//�����ڶ��й��� ��ʾ
#define	 START_PROMPT_X2	START_PROMPT_X1
#define	 START_PROMPT_Y2	(START_PROMPT_Y1+50)//(REMIND_WINDOW_Y-50)

//**���� ������ʾ-----
// // #define  KEYBOARD_CHECK_X	START_PROMPT_X1
// // #define  KEYBOARD_CHECK_Y	450

//ϵͳ�汾ѡ�� ����
#define	 SYSBD_HINT_X	200
#define	 SYSBD_HINT_Y	120//120
//ϵͳ�汾ѡ�� ����  ���ֿ�
#define	 SYSBD_WORD_X	(SYSBD_HINT_X+100)
#define	 SYSBD_WORD_Y	(SYSBD_HINT_Y+50)
#define  SYSBD_PASSWORD		687610//123456// sys����

//��ֽ����λ ��ʾ
#define  PUSH_RESET_PROMPT_X1	200
#define  PUSH_RESET_PROMPT_Y1	50
#define  PUSH_RESET_PROMPT_WIDE	450
#define  PUSH_RESET_PROMPT_HIGH	80
#define  PUSH_RESET_OK_X		(PUSH_RESET_PROMPT_X1+50)
#define  PUSH_RESET_OK_Y		(PUSH_RESET_PROMPT_Y1+50)
#define  PUSH_RESET_CANCEL_X	(PUSH_RESET_OK_X+200)
#define  PUSH_RESET_CANCEL_Y	PUSH_RESET_OK_Y
//Ѽ��
#define  PEAR_X		320//430
#define  PEAR_Y		150//240
//****************************������ť
//------------��ť��С
#define  MAIN_PWR_BUTT_W	40
#define  MAIN_PWR_BUTT_H	32
#define  MAIN_PWR_CTRL_H	20 //0
#define  LED_BUTT_W		30
#define  LED_BUTT_H		32
#define  LED_CTRL_BUTT_H		32
//����Դ ��
#define  MAIN_PWR_ON_X	600
#define  MAIN_PWR_ON_Y	55
//0
#define  MAIN_PWR_CTRL_X	MAIN_PWR_ON_X
#define  MAIN_PWR_CTRL_Y	(MAIN_PWR_ON_Y+MAIN_PWR_BUTT_H)
//����Դ ��
#define  MAIN_PWR_OFF_X		MAIN_PWR_ON_X
#define  MAIN_PWR_OFF_Y		(MAIN_PWR_CTRL_Y+MAIN_PWR_CTRL_H)
//----------�Ե���
#define  LED_KNIFE_X	(MAIN_PWR_ON_X+60)
#define  LED_KNIFE_Y	MAIN_PWR_ON_Y
//----------��0
#define  LED_CTRL_X		LED_KNIFE_X
#define  LED_CTRL_Y		(LED_KNIFE_Y+LED_BUTT_H)
//----------������
#define  LED_LED_X		LED_KNIFE_X
#define  LED_LED_Y		(LED_CTRL_Y+LED_CTRL_BUTT_H)
//��� ��
#define	 PUMP_ON_X		(LED_KNIFE_X+50)
#define	 PUMP_ON_Y		MAIN_PWR_ON_Y
//��� ��
#define	 PUMP_OFF_X		PUMP_ON_X
#define	 PUMP_OFF_Y		(PUMP_ON_Y+50)
//��������  
#define	 CHG_KNIFE_NORMAL_X	MAIN_PWR_ON_X	
#define	 CHG_KNIFE_NORMAL_Y	15	
//�綯����  
#define	 CHG_KNIFE_ELECT_X	(CHG_KNIFE_NORMAL_X+60)
#define	 CHG_KNIFE_ELECT_Y	CHG_KNIFE_NORMAL_Y	
//�ֶ�����  
#define	 CHG_KNIFE_MANUAL_X	(CHG_KNIFE_ELECT_X+60)
#define	 CHG_KNIFE_MANUAL_Y	CHG_KNIFE_NORMAL_Y

//************************************����ͼ��
//"����"
#define  PROG_X		93//120
#define  PROG_Y		120//110
//"����"
#define  STEP_X		(PROG_X+140)//(PROG_X+180)
#define  STEP_Y		PROG_Y
//�����
#define  PROG_NUM_X		(PROG_X+100)//120
#define  PROG_NUM_Y		PROG_Y
//�����
#define  STEP_NUM_X		(STEP_X+100)//120
#define  STEP_NUM_Y		PROG_Y
//������
#define  PRO_NAME_DIS_COLOR	0x080f 
#define  PRO_NAME_DIS_X		78//105
#define  PRO_NAME_DIS_Y		58//75
//******************�ߴ���ʾ
//��ǰ�ߴ� ��ʾλ��
#define CURR_SIZE_X		400//530
#define CURR_SIZE_Y		60
//��ǰ ��ʾλ��
#define  FRONT_KNIFE_X	(CURR_SIZE_X+10)//540
#define  FRONT_KNIFE_Y	110//135

//���λ��
#define  MARK_LABEL_X	60//80
#define  MARK_LABEL_Y	445//560
#define  MARK_LABEL_DATA_X	MARK_LABEL_X
#define  MARK_LABEL_DATA_Y	(MARK_LABEL_Y+40)
//��ֽbutton
#define  PUSH_BUTT_X	(MARK_LABEL_X+105)
#define  PUSH_BUTT_Y	(MARK_LABEL_Y-5)
//ʾ��button
#define  TEACH_BUTT_X	(PUSH_BUTT_X+60)
#define  TEACH_BUTT_Y	MARK_LABEL_Y
//ģʽ ���� ��
#define	 MODE_NAME_COLOR	0xf100//����ɫ
#define  MODE_NAME_X1	(TEACH_BUTT_X+65)//550
#define  MODE_NAME_Y1	MARK_LABEL_Y//660
#define  MODE_NAME_X2	(MODE_NAME_X1+230)
#define  MODE_NAME_Y2	(MODE_NAME_Y1+25)
//�Ե�button
#define  AUTOCUT_BUTT_X	(MODE_NAME_X2+8)
#define  AUTOCUT_BUTT_Y	 MARK_LABEL_Y
//-------------------------shift button
// #define SHIFT_BUTT_WIDE	60
// #define SHIFT_BUTT_HIGH	30
// #define SHIFT_BUTT_X	TEACH_BUTT_X
// #define SHIFT_BUTT_Y	620
//------- ��  &ѹֽ  pic
//����
#define  KNIFE_UP_X		380
#define  KNIFE_UP_Y		480//490
//����
#define  KNIFE_DOWN_X		KNIFE_UP_X
#define  KNIFE_DOWN_Y		KNIFE_UP_Y

// //����1
// #define  KNIFE1_UP_X		(KNIFE_UP_X+70)
// #define  KNIFE1_UP_Y		KNIFE_UP_Y//515
// //����1
// #define  KNIFE1_DOWN_X		KNIFE1_UP_X
// #define  KNIFE1_DOWN_Y		KNIFE1_UP_Y

//ѹ��
#define  PRESS_UP_X		(KNIFE_UP_X+70)//(KNIFE1_UP_X+70)
#define  PRESS_UP_Y		KNIFE_UP_Y
//ѹ��
#define  PRESS_DOWN_X		PRESS_UP_X
#define  PRESS_DOWN_Y		PRESS_UP_Y

//����
#define	IR_X	(PRESS_UP_X+70)
#define	IR_Y	KNIFE_UP_Y//F6_BUTTON_Y


//--------------����ICON--------------------
//��ǩ����
#define	LABEL_FUN_PIC_X		400//480
#define	LABEL_FUN_PIC_Y		(MIDDLE_PAGE_Y+10)//180
//�ȷֹ���
#define	DIVIDE_FUN_PIC_X	LABEL_FUN_PIC_X
#define	DIVIDE_FUN_PIC_Y	LABEL_FUN_PIC_Y
//����
// #define  PROCESS_X	  	LABEL_FUN_PIC_X
// #define  PROCESS_Y		LABEL_FUN_PIC_Y
//��������
#define SETDATA_FUN_PIC_X	LABEL_FUN_PIC_X
#define SETDATA_FUN_PIC_Y	(LABEL_FUN_PIC_Y+30)
//��׼����
#define RULER_FUN_PIC_X		150//LABEL_FUN_PIC_X
#define RULER_FUN_PIC_Y		LABEL_FUN_PIC_Y
//��������
#define CLOCK_FUN_PIC_X		LABEL_FUN_PIC_X
#define CLOCK_FUN_PIC_Y		LABEL_FUN_PIC_Y
//���빦��
#define PASSWORD_FUN_PIC_X	LABEL_FUN_PIC_X
#define PASSWORD_FUN_PIC_Y	LABEL_FUN_PIC_Y
//�б��ܡ�
#define TABLE_FUN_PIC_X		380//480
#define TABLE_FUN_PIC_Y		230//290
//����ͼƬ
#define MACHINE_PIC_X	MIDDLE_PAGE_X//60
#define MACHINE_PIC_Y	MIDDLE_PAGE_Y//220

// ��ģʽ  ��ť-------
#define	 MAINICONBUTT_GAP_X		60//85
#define	 MAINICONBUTT_WIDE		35
#define	 MAINICONBUTT_HIGH		60
#define	 AUTO_BUTT_X		MARK_LABEL_X
#define	 AUTO_BUTT_Y		535//670//�Զ�mod��ť
#define	 MANUAL_BUTT_X		(AUTO_BUTT_X+MAINICONBUTT_GAP_X)
#define	 MANUAL_BUTT_Y		  AUTO_BUTT_Y//�ֶ�mod��ť
#define	 FIND_BUTT_X		(MANUAL_BUTT_X+MAINICONBUTT_GAP_X)
#define	 FIND_BUTT_Y		  AUTO_BUTT_Y//����mod��ť

//-----F1,F2,F3,...
#define	 FICONBUTT_GAP_V		46//80
#define	 FICONBUTT_WIDE		35//40
#define  F1_BUTTON_X		20//30
#define  F1_BUTTON_Y		153//200  //F1��ǩ��ť
#define  F2_BUTTON_X	F1_BUTTON_X
#define  F2_BUTTON_Y	(F1_BUTTON_Y+FICONBUTT_GAP_V)  //F2�ȷְ�ť
#define  F3_BUTTON_X	F1_BUTTON_X
#define  F3_BUTTON_Y	(F2_BUTTON_Y+FICONBUTT_GAP_V)  //F3
#define  F4_BUTTON_X		F1_BUTTON_X
#define  F4_BUTTON_Y		(F3_BUTTON_Y+FICONBUTT_GAP_V)  //F4
#define  F5_BUTTON_X		F1_BUTTON_X
#define  F5_BUTTON_Y		(F4_BUTTON_Y+FICONBUTT_GAP_V)  //F5  ��ť
#define  F6_BUTTON_X		F1_BUTTON_X
#define  F6_BUTTON_Y		(F5_BUTTON_Y+FICONBUTT_GAP_V)  //F6
#define	 F4_WHEEL_BUTT_X		F1_BUTTON_X  //F4��������  
#define	 F4_WHEEL_BUTT_Y		F4_BUTTON_Y
#define	 F5_WHEEL_BUTT_X		F1_BUTTON_X  //F4��������  
#define	 F5_WHEEL_BUTT_Y		F5_BUTTON_Y


//---------------------------------
//F4---��� �趨��ť
#define ALL_FLAG_WIN_BASE_X		380//755
#define ALL_FLAG_WIN_BASE_Y		520//160
#define FLAG_WIDE		26//32
#define FLAG_HIGH		34//42
#define FLAG_BUTT_GAPX		(FLAG_WIDE+12)//70
#define FLAG_BUTT_GAPY		0//(FLAG_HIGH+12)
#define ALL_FLAG_WIN_WIDE	(FLAG_BUTT_GAPX*6)//FLAG_WIDE
#define ALL_FLAG_WIN_HIGH	FLAG_HIGH//(FLAG_BUTT_GAPY*6)
//F1 ���� ��ť
#define F1_AIR_BED_X	(ALL_FLAG_WIN_BASE_X+0)
#define F1_AIR_BED_Y	(ALL_FLAG_WIN_BASE_Y+0)
// F2 ѹֽ ��ť
#define	 F2_PRE_PAPER_X	(F1_AIR_BED_X+FLAG_BUTT_GAPX)
#define  F2_PRE_PAPER_Y	(F1_AIR_BED_Y+FLAG_BUTT_GAPY)
// F3 ��ֽ ��ť
#define	 F3_SORT_PAPER_X	(F2_PRE_PAPER_X+FLAG_BUTT_GAPX)
#define  F3_SORT_PAPER_Y	(F2_PRE_PAPER_Y+FLAG_BUTT_GAPY)
// F4��ֽ��־ ��ť
#define  F4_PUSH_PAPER_X	(F3_SORT_PAPER_X+FLAG_BUTT_GAPX)
#define	 F4_PUSH_PAPER_Y	(F3_SORT_PAPER_Y+FLAG_BUTT_GAPY)
// F5 �쵶  ��ť
#define	 F5_RED_KNIFE_X		(F4_PUSH_PAPER_X+FLAG_BUTT_GAPX)
#define	 F5_RED_KNIFE_Y		(F4_PUSH_PAPER_Y+FLAG_BUTT_GAPY)
// S5 ���е�  ��ť
#define	 S5_ALL_KNIFE_X		(F5_RED_KNIFE_X+FLAG_BUTT_GAPX)
#define	 S5_ALL_KNIFE_Y		(F5_RED_KNIFE_Y+FLAG_BUTT_GAPY)

//------------------------------
//---���� ��ť
#define RUN_BUTT_WIDE	60
#define RUN_BUTT_HIGH	26//30
#define RUN_BUTT_X		(AUTOCUT_BUTT_X+85)
#define RUN_BUTT_Y		AUTOCUT_BUTT_Y
//ֹͣup
#define  STOP_X		(RUN_BUTT_X+95)
#define  STOP_Y		RUN_BUTT_Y

#define JOG_BUTT_WIDE	75//80
#define JOG_BUTT_HIGH	35//40
//����up
#define	 BACK_PAGE_X	RUN_BUTT_X//500
#define	 BACK_PAGE_Y	KNIFE_UP_Y//
//����
#define	 FAST_BACK_X	(BACK_PAGE_X+40)
#define	 FAST_BACK_Y	BACK_PAGE_Y
//ǰ��
#define	 FRONT_PAGE_X	STOP_X
#define	 FRONT_PAGE_Y	BACK_PAGE_Y
//���
#define	 FAST_FWD_X		(FRONT_PAGE_X+40)
#define	 FAST_FWD_Y		BACK_PAGE_Y


//����
#define STEP_MOV_BUTT_X	460//600
#define STEP_MOV_BUTT_Y	380//400
#define STEP_MOV_BUTT_HIGH	32
#define STEP_MOV_BUTT_WIDE	90


/****
//�ֶ�ģʽ��      ���˼�
#define  MAN_BACK_PAGE_X	650//520 
#define  MAN_BACK_PAGE_Y	320//260//300
//�ֶ�ģʽ��       ǰ��
#define  MAN_FRONT_PAGE_X	(MAN_BACK_PAGE_X+120)
#define  MAN_FRONT_PAGE_Y	MAN_BACK_PAGE_Y
//����
#define	MAN_FAST_BACK_X MAN_BACK_PAGE_X
#define MAN_FAST_BACK_Y (MAN_BACK_PAGE_Y+100)
//���up
#define	MAN_FAST_FWD_X	MAN_FRONT_PAGE_X
#define	MAN_FAST_FWD_Y	MAN_FAST_BACK_Y
**/


// ɾ��up
#define  DELETE_ALL_BUT_WIDE	60
#define  DELETE_ALL_BUT_HIGH	40
#define  DELETE_ALL_X		TEACH_BUTT_X//620
#define  DELETE_ALL_Y		BACK_PAGE_Y//410
//ƫ��������
#define	 S6_AMEND_BUTT_X	(DELETE_ALL_X+80)	//�޸�ƫ����
#define	 S6_AMEND_BUTT_Y	DELETE_ALL_Y



//--------------------��ģʽF1,2.....
//���up
#define  FINISHED_X	  	F1_BUTTON_X
#define  FINISHED_Y		F1_BUTTON_Y
//F2�˳�up
#define  F2OUT_X		F2_BUTTON_X
#define  F2OUT_Y		F2_BUTTON_Y
//���Ҽ�ͷ
#define  L_R_ARROW_X	F6_BUTTON_X//FINISHED_X
#define  L_R_ARROW_Y	F6_BUTTON_Y//(F2OUT_Y+58)
//�Ӳ˵� ����
#define  LAB_UP_ARROW_X	 F1_BUTTON_X		//F1  ��ǩ��
#define  LAB_UP_ARROW_Y	 F3_BUTTON_Y
#define  DIV_UP_ARROW_X	 F1_BUTTON_X		//F2 �ȷ���
#define  DIV_UP_ARROW_Y	 F5_BUTTON_Y	
#define  PRO_UP_ARROW_X	 320//450				//F3 ������
#define  PRO_UP_ARROW_Y	 (MIDDLE_PAGE_Y+M_PAGE_HIGH-50)//(BACK_PAGE_Y+20)
//�Ӳ˵� ����
#define  LAB_DOWN_ARROW_X	LAB_UP_ARROW_X
#define  LAB_DOWN_ARROW_Y	F4_BUTTON_Y
#define  DIV_DOWN_ARROW_X	LAB_UP_ARROW_X
#define  DIV_DOWN_ARROW_Y	F6_BUTTON_Y
#define  PRO_DOWN_ARROW_X	(PRO_UP_ARROW_X+80)
#define  PRO_DOWN_ARROW_Y	PRO_UP_ARROW_Y
// // //�Ӳ˵� F3��ǩ����
// // #define  F3_LABEL_TIME_X	F3_BUTTON_X
// // #define  F3_LABEL_TIME_Y	F3_BUTTON_Y
// // //�Ӳ˵� F4��ǩ�ϱ�
// // #define  F4_LABEL_DESERT_X	F4_BUTTON_X
// // #define  F4_LABEL_DESERT_Y	F4_BUTTON_Y

#define  ENTER_OK_BUTT_X	(PRO_DOWN_ARROW_X+80)//ȷ��
#define  ENTER_OK_BUTT_Y	PRO_UP_ARROW_Y









//--------F1��ǩҳ
#define TOTAL_SIZE_X 	(MIDDLE_PAGE_X+160)//220
#define TOTAL_SIZE_Y 	(MIDDLE_PAGE_Y+30)//250
#define ROW_GAP1		60//50
#define ROW_GAP2		70//60
//label
#define LABEL_SIZE_X 	TOTAL_SIZE_X
#define LABEL_SIZE_Y 	(TOTAL_SIZE_Y+ROW_GAP1)
#define WASTE_SIZE_X 	TOTAL_SIZE_X
#define WASTE_SIZE_Y 	(LABEL_SIZE_Y+ROW_GAP1)

//F2---�ȷ�ҳ��
#define DIVIDE_TOTAL_X	TOTAL_SIZE_X
#define DIVIDE_TOTAL_Y	TOTAL_SIZE_Y
#define DIVIDE_NUM_X	DIVIDE_TOTAL_X//�ȷ���
#define DIVIDE_NUM_Y	(DIVIDE_TOTAL_Y+ROW_GAP2)

//F3 �����б�------ ��ʾ
#define F3_PRO_CAPTION_X	MIDDLE_PAGE_X//F3ҳü
#define F3_PRO_CAPTION_Y	MIDDLE_PAGE_Y//F3ҳü

#define  PROTEXT_HIGH	32//60//45 //�����б� �о�
#define PRO_ARROW_WIDE	32
#define PRO_ARROW_HIGH	32
#define PRO_RIGHT_ARROW_X 	F3_PRO_CAPTION_X
#define PRO_RIGHT_ARROW_Y 	(F3_PRO_CAPTION_Y+20)
#define PROC_NUM_X	(PRO_RIGHT_ARROW_X+PRO_ARROW_WIDE+2)
#define PROC_NUM_Y	(PRO_RIGHT_ARROW_Y+10)
#define PROC_NAME_X	(PROC_NUM_X+50)
#define PROC_NAME_Y	PROC_NUM_Y
#define PROC_STEP_X	(PROC_NAME_X+240)
#define PROC_STEP_Y	PROC_NUM_Y
#define PROC_DATE_X (PROC_STEP_X+50)
#define PROC_DATE_Y	PROC_NUM_Y
// ���� ��Ϣ ��ʾ
#define PRO_MESS_COLOR1 0xFF5b
#define PRO_MESS_COLOR2 0xFFff

#define PRO_MESS_X		80//70
#define PRO_MESS_Y		PROC_NUM_Y
#define PRO_MESS_WIDE	650
#define PRO_MESS_HIGH	270

#define INPUT_NAME_WIN_X	(PRO_MESS_X+330)
#define INPUT_NAME_WIN_Y	(PRO_MESS_Y+40)
#define INPUT_NAME_WIDE		315
#define INPUT_NAME_HIGH		50

#define INPUT_SEL_X		(INPUT_NAME_WIN_X+10)
#define INPUT_SEL_Y		(INPUT_NAME_WIN_Y+INPUT_NAME_HIGH+5)
#define INPUT_SEL_GAP	30
#define INPUT_SEL_ROW	4

#define INPUT_WORD_COL	10
#define INPUT_WORD_GAP	30
#define INPUT_LIB_X		INPUT_SEL_X
#define INPUT_LIB_Y		(INPUT_SEL_Y+INPUT_SEL_GAP*4+5)

//---------���뷨 touch����key
#define TOUBUTT_WIDE	75//65
#define TOUBUTT_HIGH	58
#define TOUBUTT_GAPX	5
#define TOUBUTT_GAPY	5
#define TOUBUTT_X1		(PRO_MESS_X+5)
#define TOUBUTT_X2		(TOUBUTT_X1+TOUBUTT_WIDE+TOUBUTT_GAPX)
#define TOUBUTT_X3		(TOUBUTT_X2+TOUBUTT_WIDE+TOUBUTT_GAPX)
#define TOUBUTT_X4		(TOUBUTT_X3+TOUBUTT_WIDE+TOUBUTT_GAPX)

#define TOUBUTT_Y1		(PRO_MESS_Y+10)
#define TOUBUTT_Y2		(TOUBUTT_Y1+TOUBUTT_HIGH+TOUBUTT_GAPY)
#define TOUBUTT_Y3		(TOUBUTT_Y2+TOUBUTT_HIGH+TOUBUTT_GAPY)
#define TOUBUTT_Y4		(TOUBUTT_Y3+TOUBUTT_HIGH+TOUBUTT_GAPY)



//F2------------����ҳ
#define PARA_START_X1		MIDDLE_PAGE_X //80
#define PARA_START_X2		200//240
#define PARA_START_Y		MIDDLE_PAGE_Y//210
#define PARA_COL_WIDE		260//350
#define PARA_ROW_GAP		35//40

//----------F3ʱ�� ����ҳ
#define CLOCK_DATA_X	(MIDDLE_PAGE_X+35)//120
#define CLOCK_DATA_Y	(MIDDLE_PAGE_Y+20)//240	
#define CLOCK_GAP_Y		PARA_ROW_GAP	//40

//�б�� �ұ߽�
#define  DATA_TABLE_END_X	(MACHINE_PIC_X+500)

//-------------���� ���� ��ʾҳ��
#define PULSE_SET_X1		MIDDLE_PAGE_X//100
#define PULSE_SET_X2		330//400
#define PULSE_SET_Y		 MIDDLE_PAGE_Y//230//200
#define PULSE_GAP_Y		 PARA_ROW_GAP	//40
//--------����ģʽ ����
#define PASS_TIME1_X	100		//����λ��
#define PASS_TIME1_Y	200
#define PASS_TIME_GAP	100
//------passcode ��������
#define PASSCODE_X		100//220
#define PASSCODE_Y		240
#define PASS_HINT_X		(PASSCODE_X+550)
#define PASS_HINT_Y		PASSCODE_Y

#define PASSCODE_INPUT_X	(PASSCODE_X+200)
#define PASSCODE_INPUT_Y	(PASSCODE_Y+50)
//����ѹֽsensor λ��ʾ��
#define KNIFE_SENSOR_X	190//235
#define KNIFE_SENSOR_Y	262//365
#define PRESS_SENSOR_X	410//520
#define PRESS_SENSOR_Y	220//307
//******�Ե���ʾ
#define SELF_PROMP_X	100
#define SELF_PROMP_Y	200
#define SELF_PROMP_WIDE 350
#define SELF_PROMP_HIGH 150
//�Ե�OK
#define SELF_OK_X		(SELF_PROMP_X+10)
#define SELF_OK_Y		(SELF_PROMP_Y+75)
#define SELF_OK_WIDE	130
#define SELF_OK_HIGH	40
//�Ե� ȡ��
#define SELF_CANCEL_X	(SELF_OK_X+150)
#define SELF_CANCEL_Y	SELF_OK_Y
//--���� run ��ʾ
#define RUN_DIS_X		400
#define RUN_DIS_Y		START_PROMPT_Y2//REMIND_WINDOW_Y


//----ɾ��ȫ�� ��ʾ��
#define DEL_ALL_WIN_X	400
#define DEL_ALL_WIN_Y	300
#define DEL_ALL_WIN_WIDE	300
#define DEL_ALL_WIN_HIGH	100
//delete all ��ʾ
#define DEL_ALL_HINT_X	(DEL_ALL_WIN_X+10)
#define DEL_ALL_HINT_Y	(DEL_ALL_WIN_Y+10)
//ɾ�� ok
#define DEL_ALL_OK_X	(DEL_ALL_WIN_X+50)
#define DEL_ALL_OK_Y	(DEL_ALL_HINT_Y+40)
//ɾ�� cancel
#define DEL_ALL_CANCEL_X	(DEL_ALL_OK_X+120)
#define DEL_ALL_CANCEL_Y	DEL_ALL_OK_Y


//==============================================
//help
#define	HELP_RET_X	550//550
#define	HELP_RET_Y	50
//
#define	HELP_CORRECT_X 20
#define	HELP_CORRECT_Y HELP_RET_Y
//���� F1У׼����
#define HELP_GAP_Y	60
#define HELP_F1_X	150//200
#define HELP_F1_Y	150
//F2	ע��
#define HELP_F2_X	HELP_F1_X
#define HELP_F2_Y	(HELP_F1_Y+HELP_GAP_Y)
//F3	IO����
#define HELP_F3_X	HELP_F1_X
#define HELP_F3_Y	(HELP_F2_Y+HELP_GAP_Y)
//F4	ϵͳ�汾
#define HELP_F4_X	HELP_F1_X
#define HELP_F4_Y	(HELP_F3_Y+HELP_GAP_Y)
//F5 ÿҳ��������
#define HELP_F5_X	HELP_F1_X
#define HELP_F5_Y	(HELP_F4_Y+HELP_GAP_Y)
//F2 ͼ��ע�� ��ҳ
#define F2_PAGE_UP_X	200
#define F2_PAGE_UP_Y	(C_GLCD_V_SIZE-60)//540
//��ҳ
#define F2_PAGE_DOWN_X	500
#define F2_PAGE_DOWN_Y	F2_PAGE_UP_Y
//F2����
#define F2_RET_HELP_X	680//680
#define F2_RET_HELP_Y	F2_PAGE_UP_Y

//---------touch key   �汾���� ����  key------------------------------------------------
#define KEY_BUT_WIDE	80
#define KEY_BUT_HIGH	60
#define KEY_GAP_X	30
#define KEY_GAP_Y	20
#define KEY_BUT_X1	230
#define KEY_BUT_X2	(KEY_BUT_X1+KEY_BUT_WIDE+KEY_GAP_X)
#define KEY_BUT_X3	(KEY_BUT_X2+KEY_BUT_WIDE+KEY_GAP_X)
//y--
#define KEY_BUT_Y1	230
#define KEY_BUT_Y2	(KEY_BUT_Y1+KEY_BUT_HIGH+KEY_GAP_Y)
#define KEY_BUT_Y3	(KEY_BUT_Y2+KEY_BUT_HIGH+KEY_GAP_Y)
#define KEY_BUT_Y4	(KEY_BUT_Y3+KEY_BUT_HIGH+KEY_GAP_Y)
#define KEY_BUT_Y5	(KEY_BUT_Y4+KEY_BUT_HIGH+KEY_GAP_Y)

//--�汾ѡ�� �ϼ�ͷ
#define VER_SEL_UP_X	600
#define VER_SEL_UP_Y	250
//�¼�ͷ
#define VER_SEL_DOWN_X	VER_SEL_UP_X
#define VER_SEL_DOWN_Y	(VER_SEL_UP_Y+150)



//-----��������  ��ͷ
#define LINE_SET_UP_X	VER_SEL_UP_X
#define LINE_SET_UP_Y	VER_SEL_UP_Y
//�¼�ͷ
#define LINE_SET_DOWN_X	VER_SEL_DOWN_X
#define LINE_SET_DOWN_Y	VER_SEL_DOWN_Y




//===========================================================
















//ģʽ-----------------------
#define PROG_MODE		0x10//���ģʽ
#define AUTO_MODE		0x20//
#define MANUAL_MODE		0x30
#define TEACH_MODE		0x40
#define SELF_CUT_MODE	0x50
#define HELP_MODE		0x60

#define READ_PRO_MODE		0x70//�鿴ģʽ


//�����ģʽ
// #define PROG_LABEL_MODE		0x11//��ǩ
// #define PROG_DIVIDE_MODE	0x12//�ȷ�
// // #define PROG_PRO_MODE		0x13//����ѡ��
// // #define PROG_PRO_MESS_MODE	0x131//���� ��Ϣ
// // #define PROG_DEL_ALL_PRO_MODE	0x132//	ɾ������pro
#define PROG_DEL_ALL_SIZE_MODE	0x133//	ɾ�����гߴ�

#define PROG_FLAG_MODE		0x14//��� ģʽ
//�Զ���ģʽ
// #define AUTO_RULER_MODE  0x21//��׼
// #define AUTO_TOOLS_MODE  0x22 //
#define AUTO_LABEL_MODE		0x21//��ǩ
#define AUTO_DIVIDE_MODE	0x22//�ȷ�
// #define AUTO_INSERT_MODE	0x23//����
// #define AUTO_DELETE_MODE	0x24//ɾ��
#define AUTO_PLUS_MODE   0x25//F5++
#define AUTO_MINUS_MODE  0x26//F6--
#define AUTO_TO_SELF_MODE 0x27
#define AUTO_DEL_ALL_SIZE_MODE	0x211//	ɾ�����гߴ�
//�ֶ���ģʽ
#define MANUAL_RULER_MODE  0x31//��׼
#define MANUAL_TOOLS_MODE  0x32//����
#define MANUAL_CLOCK_MODE  0x33
#define MANUAL_PULSE_MODE  0x34//�趨���嵱��
#define MANUAL_PASS_MODE   0x35//����
#define MANUAL_SERVO_C_MODE   0x36//ֱ���ŷ� C ����
#define MANUAL_IO_TEST_MODE	0x37//���Զ˿�
//���������ģʽ
#define READ_PRO_MESS_MODE		0x71//���� ��Ϣ
#define READ_DEL_ALL_PRO_MODE	0x72//	ɾ������pro
//ʾ����ģʽ
#define TEACH_LABEL_MODE	0x41//��ǩ
#define TEACH_DIVIDE_MODE	0x42//�ȷ�
#define TEACH_PRO_MODE		0x43//����ѡ��
#define TEACH_PLUS_MODE   0x45//F5++
#define TEACH_MINUS_MODE  0x46//F6--
// // #define TEACH_PRO_MESS_MODE	0x431//���� ��Ϣ
// // #define TEACH_DEL_ALL_PRO_MODE	0x432//	ɾ������pro
#define TEACH_DEL_ALL_SIZE_MODE	0x411//	ɾ�����гߴ�

#define TEACH_FLAG_MODE		0x44//��� ģʽ
//�Ե���ģʽ
// // #define SELF_RULER_MODE  0x51//��׼
// // #define SELF_TOOLS_MODE  0x52 //����
// // #define SELF_PLUS_MODE   0x53//F3++
// // #define SELF_MINUS_MODE  0x54//F4--
// #define SELF_COME_IN_MODE  0x55//�Ե���ʾ

//��λ
#define UNIT_MM		0//��
#define UNIT_MIL	1//Ӣ
//����
#define CHN_HAN    0
#define ENGLISH    1
#define INDONSIA   2
#define PORTUGAL   3
#define SPANISH	   4
//����
#define FRONT_LIM_MIN		(15*100)
#define FRONT_LIM_MAX		(120*100)	//(80*100)
//#define FRONT_LIM_MIN_in	(590)
//#define FRONT_LIM_MAX_in	(3149)

#define MIDD_LIM_MIN		(30*100)
#define MIDD_LIM_MAX		(150*100)
//#define MIDD_LIM_MIN_in		(1181)
//#define MIDD_LIM_MAX_in		(5905)

#define BACK_LIM_MIN		(500*100)
#define BACK_LIM_MAX		(2200*100)
//#define BACK_LIM_MIN_in		(23622)
//#define BACK_LIM_MAX_in		(86614)
#define AUTO_PUSH_DISTAN	(500*100)
#define AUTO_PUSH_NO		(10*100)

// #define MARGIN_SIZE		30//25
#define DC_VIRTURE_SIZE 1500

//---------------------���� ʮ��
#define TOUCH_X1	50
#define TOUCH_Y1	50

#define TOUCH_X2	TOUCH_X1
#define TOUCH_Y2	(C_GLCD_V_SIZE-50)//550

#define TOUCH_X3	(C_GLCD_H_SIZE-50)//750
#define TOUCH_Y3	TOUCH_Y2

#define TOUCH_X4	TOUCH_X3
#define TOUCH_Y4	TOUCH_Y1

#define TOUCH_X_MID	(C_GLCD_H_SIZE>>1)
#define TOUCH_Y_MID	(C_GLCD_V_SIZE>>1)

//---������ text
#define CAL_INPUT	0  //���������
#define CAL_RESULT	1   //�����


//-----------�����������
// // #define	 MOTOR_DC_SERVO	 		30//ֱ���ŷ�
// // #define	 MOTOR_DC670_SERVO	 	40//ֱ���ŷ�670
#define  MOTOR_FREQ_5_SPD_RST	0  //��Ƶ�� 5����+��λ
#define  MOTOR_FREQ_3_SPD		1  //��Ƶ�� 3����
#define  MOTOR_FREQ_3_SPD_RST	2  //��Ƶ�� 3����+��λ
#define	 MOTOR_AC_SERVO	 		3//5//�����ŷ�
#define	 MOTOR_AC_SERVO_REV	 	4//6//�����ŷ�����

//����
#define MAX_KNIFE1		999  //�ܵ���1-999
#define MAX_KNIFE2		399  //�ܵ���1-399

#define PRO_HEAD_BYTES    100
//ÿ�����򳤶�
#define PROG_BYTES1		((MAX_KNIFE1*5)+PRO_HEAD_BYTES)//MAX_KNIFE1 ������ +2byte����
#define PROG_BYTES2		((MAX_KNIFE2*5)+PRO_HEAD_BYTES)

#define PROG_GROPU1		300  //ǰ300������
#define MAX_PROG		500//��500������

#define MAX_STEP_SIZE	90000

//*************************************************
// #define	PAGE_KNIFE	5		//ÿҳ����
// #define	PAGE2_KNIFE	(PAGE_KNIFE*2)		//2ҳ����
#define	PROGS_1PAGE	5		//ÿҳ ����
//*****************************************
//------*********��ʶ�� Ԥ����
#define NO_FLAG		0
#define PUSH_FLAG   1   //��ֽ ��־λ����
#define SORT_FLAG   2   // ��ֽ  ��־λ����
#define PRESS_FLAG  3   //  ѹֽ  ��־λ����
#define KNIFE_FLAG  4   //��  ��־λ����
#define AIR_FLAG    0x80  //����  ��־λ����

//----���뷨 ����
#define NUMBER_INPUT	0
#define CHAR_INPUT		1
#define PINYIN_INPUT	2
//*****************************************
#define NAME_BYTE	90

//---�����б� ˳��
#define PRO_BY_NUM	0//�����
#define PRO_BY_TIME	1//��ʱ��

typedef struct
{
Int8U pro_name_flag[5];
Int8U pro_name[NAME_BYTE];//������90B
Int8U pro_year;	//����ʱ��
Int8U pro_month;//����ʱ��
Int8U pro_day;	//����ʱ��
Int16U pro_knifeSUM;//����
} PROCESS_HEAD;		//����ͷ��ʽ(100B)

typedef struct 
{
Int32U size;
Int8U  k_flag;
} KNIFE_DATA;

typedef struct
{
Int16U year;
Int16U month;
Int16U day;
} START_DAY;


extern PROCESS_HEAD OnePro_head;//
extern PROCESS_HEAD Pro_head_temp;//
extern KNIFE_DATA OneKnife_data;
extern START_DAY Start_days;
extern const PROCESS_HEAD ProHead_default;

extern const pInt8U NAME_flag;

typedef struct
{
Int16U pro_num;//�����
Int16U pro_sum;//��������
//Int8U step_num;// 
//Int8U seg_sum;// 
} PROG_SEG;    //���� �� ����

extern Int16U cursor_row;////��� λ��(��)
extern Int16U  TableDis_startcol;//��ʼ��

extern Int16U ProNumGroup[MAX_PROG+2];
extern Int16U prog_order;


extern Int16U Knife_order;//��ǰ����
extern Int16U Knife_sum_before;//�ܵ���
extern Int16U MAX_Knife;//��൶��

//extern Int16U Process_num;//��ǰ���� ��
//extern Int16U MaixProcess_num;//��� �����
extern PROG_SEG Pro_data;//���� �� ��


extern unsigned char PorgSet_sel;

//extern unsigned char cursor_temp;
extern unsigned short WorkMode;

extern unsigned char BeforeKnifeNo_flag;

extern Int32U CurrentSize;
extern Int32U BeforeKnifeSize;
extern Int32U BeforeKnife_offset;
extern Int32U BeforeKnife_offset_in;
extern Int32U OriginalSize;//ԭ��
extern Int32U CurrentSize_temp;

extern Int8U Unit;//��λ
extern Int8U Language;//����
extern Int8U PressValid_flag;//

extern Int32U FrontLimit;
extern Int32U MiddleLimit;
extern Int32U BackLimit;
extern Int32U Aheader;
extern Int32U StanDistance;
extern Int8U Pulse_degree;
extern Int8U PassModeIn_flag;
extern Int8U PassModeOk_flag;

extern Int32U Size_MIN;
extern Int32U Size_MAX;
extern Int32U Size_MIN_num;
extern Int32U Size_MAX_num;
extern Int32U FirstDays;
extern Int32U SecondDays;
extern Int32U AutoPushDistance;

extern Int8U FirstDayValid_flag;
extern Int8U SecondDayValid_flag;

extern Int8U PassCodeEn_flag;
//extern Int8U SelfCutEnter_flag;
extern Int32U TargetSize;
extern Int32U TargetSize_temp;
extern Int32U TargetSize_inch;

extern Int8U Forward_flag;
extern Int8U Backward_flag;

extern Int8U Run_flag;
extern Int8U BackStop_flag;
extern Int8U ForceStop_flag;
extern Int8U RunStop_flag;
extern Int32U stop_time;

extern Int8U MoveSpeed;
extern Int8U SelfLockEn_flag;
extern Int8U InTargetPosit_flag;

extern Int8U GoFrontEn_flag;
extern Int8U GoBackEn_flag;
extern Int8U GoFast_flag;
extern Int8U JogRunMode;
extern Int8U EncoderErr_flag;

extern Int8U RunDisplay_flag;
extern Int8U AutoPushRun_flag;


extern Int8U AutoCutExec_flag;
extern Int8U AutoCutStart_flag;
extern Int8U OneCutRoutine_flag;

extern Int8U PusherResetMove_flag;
extern Int16U PusherResetTime;


extern Int8U MotorType;
extern Int8U PushRstKey_flag;

extern Int8U ButtonTouch_mode;
extern Int8U ProcessRatio;
extern Int16U CodeSensorTime_AB;
extern Int8U CutPermit_flag;

extern Int8U ServoPressStop_flag;
extern Int8U DcServoGoTarget_flag;

extern Int16U LastAutoKnife_order;//  �Ե� ��ǰһ��
extern Int8U ReEnterAutoKnife_dis;  //�ٴν����Ե�  ��ʾ

extern Int8U ACServoDrvErr_flag;
extern Int8U ACServoAlarmExec_flag;

extern Int8U ElectricWheelOn_flag; //��������
extern Int8U MotorRun_flag;
extern Int8U InputMode;

extern Int32U current_inch;
extern Int8U DivideValue_flag;
extern Int8U DisAllProgMode;

extern Int8U KnifeSensorMode;//knife press sensor 
extern Int8U PressSensorMode;

extern Int32U AirOffDistance;//�ط�þ���
extern Int8U AirOffOK_flag;//
//extern Int8U AirOffStart_flag;

extern Int8U IR_SensorStus;
//-----------------------ƫ�������� ģʽ
extern Int8U AmendSwitch_flag;
// extern Int8U AmendModeEnb_flag;
extern Int8U AmendStartRun_flag;
extern Int32U AmendSize;
extern Int8U AmendPlus_flag;


extern Int8U CutPressRoll_flag;


extern Int8U PageKf_Size_flag;//ÿҳ����flag
extern Int8U PageKf_Size;//ÿҳ����
extern Int8U Kf_Line_HIGH;//�и�

extern Int8U AmendOver_flag;

extern Int8U Para_sel;
extern Int8U PramSel_Page;//���� �б�ҳ
extern Int8U Para2_sel;//2 �б���
extern Int32U Step_Size; //��������

extern Int32U VirtualTargetSizeGap;
extern Int8U IRChgWorkmodeValid_flag;//�����л�����ģʽ���

//****************


void StartPic_dis(void);//����������ʾ

void WorkPic_dis(void);  //����������ʾ
void TextWindow_dis(void); //�ı������
void Pear_dis(Int16U x, Int16U y);//Ѽ��


void CurrentArea_save1(Int16U x,Int16U y, Int16U Wide,Int16U High);//�ݴ�  ��ǰ���� ����1
void CurrentArea_save2(Int16U x,Int16U y, Int16U Wide,Int16U High);//�ݴ�  ��ǰ���� ����2
void CurrentArea_save3(Int16U x,Int16U y, Int16U Wide,Int16U High);//�ݴ�  ��ǰ���� ����3
void CurrentArea_recover1(Int16U x, Int16U y, Int16U Wide,Int16U High);//�ָ�  ��ǰ���� ����1
void CurrentArea_recover2(Int16U x, Int16U y, Int16U Wide,Int16U High);//�ָ�  ��ǰ���� ����2
void CurrentArea_recover3(Int16U x, Int16U y, Int16U Wide,Int16U High);//�ָ�  ��ǰ���� ����3

void InputNum_dis(pInt8U nums,Int8U cou); //�ߴ�������ʾ

void OneProNum_dis(Int16U pro_order, PROCESS_HEAD pro_head); //���������ʾ
void StepNum_dis(Int16U step_sum,Int16U step_order); //���������ʾ
void KnifeOrder_dis(Int16U row, Int16U order,Int16U num_color);//-----------------------��ʾһ�����
void KnifeSize_dis(Int16U row,  Int32U Knife_size,Int16U num_color);//--------------��ʾһ���ߴ�
void PushFlag_dis(Int8U row,  Int8U Knife_flag);//-------һ�� ��ֽ ��־��ʾ

Int8U OneKnifeDataSel_dis(Int16U knife,Int8U row,Int16U num_color);  //һ������ ������ʾ

void ProgSet_dis(Int32U size, Int16U x, Int16U y, Int8U set_flag);// ��ǩҳ�� �ߴ���ʾ
void LabelSel_dis(Int8U sel, Int8U flag);
void DivideSel_dis(Int8U sel, Int8U flag);

void CurrentSize_dis(Int32U size);//��ǰ�ߴ�
void FrontKnifeSize_dis(Int32U size);//��ǰ�ߴ�
void CurrUint_dis(Int8U unit);  //��ǰ�ߴ� ��λ
void FrontKnifeUint_dis(Int8U unit);  //��ǰ�ߴ� ��λ
void ParameterPage1_dis(Int8U sel, Int8U flag); //���� ������ʾ
void TimeSetSel_dis(Int8U sel, Int8U flag); //ʱ�� �趨 ��ʾ

void PromptNum_dis(void);  //�������ݷ�Χ ��ʾ
void SelPulseDegree_dis(Int8U sel,Int8U flag); //�����趨
void PassDaysSet_dis(Int8U sel,Int8U flag);//�����趨

void SetMotorSpeed(Int8U speed_sel);//�趨�ٶ�
void Draw_cross(Int16U x,Int16U y,Int16U color);

void ProgressBar_dis(Int16U total, Int16U now);  //������ ��ʾ
void Calculator_Window(void);  //������


#endif