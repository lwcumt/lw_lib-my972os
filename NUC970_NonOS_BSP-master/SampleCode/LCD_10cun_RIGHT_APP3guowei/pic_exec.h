


#ifndef _PIC_EXEC_H
#define _PIC_EXEC_H

#include"main.h"


#define PAGE_5_LINE 	0
#define PAGE_7_LINE 	1



//----------- ���鱳����ɫ------------
#define TEXT_TAB_BACK_COLOR		0xE71C

#define TEXT_TAB_FRONT_COLOR	0xFFE6//YELLOW_COLOR
#define CURREN_STEP_BACK_COLOR	0xCF5D	//��ǰsize����ɫ
#define CURREN_UNIT_BACK_COLOR	0x3AB0	//��ǰ��λ����ɫ
#define FRONT_KNIFE_BACK_COLOR	CURREN_STEP_BACK_COLOR
#define STEP_BACK_COLOR		  CURREN_STEP_BACK_COLOR//
#define WIN_DOWN_BACK_COLOR		0xCE79//�ײ�����ɫ


#define F1_4_WIDE	48
#define F1_4_HIGH	48

// #define F_KEY_WIDE	56
// #define F_KEY_HIGH	46

#define FORWARD_WIDE	F1_4_WIDE
#define FORWARD_HIGH	F1_4_HIGH

// #define DELETE_WIDE		82
// #define DELETE_HIGH		31
//-------������ ������
#define CALCUL_WIN_X	328//320
#define CALCUL_WIN_Y	160//105
#define CALCUL_WIDE		472//412
#define CALCUL_HIGH		336//280
#define CALCUL_COLOR	0x879e

#define CALCUL_TEXT_X	(CALCUL_WIN_X+5)
#define CALCUL_TEXT_Y	(CALCUL_WIN_Y+5)
#define CALCUL_TEXT_H	30
#define CALCUL_TEXT_W	450//390
#define CALCUL_TEXT_END	(CALCUL_TEXT_X+CALCUL_TEXT_W-12)

#define CALCUL_RESULT_X	(CALCUL_TEXT_X+160)
#define CALCUL_RESULT_Y	(CALCUL_TEXT_Y+CALCUL_TEXT_H+5)
#define CALCUL_RESULT_H	30
#define CALCUL_RESULT_W	275//225
//
#define BUTT_WIDE	75//65
#define BUTT_HIGH	60//55//45
#define BUTT_GAP1	5
#define BUTT_GAP2	5
#define BUTT_X1		(CALCUL_WIN_X+5)
#define BUTT_X2		(BUTT_X1+BUTT_WIDE+BUTT_GAP1)
#define BUTT_X3		(BUTT_X2+BUTT_WIDE+BUTT_GAP1)
#define BUTT_X4		(BUTT_X3+BUTT_WIDE+BUTT_GAP1)
#define BUTT_X5		(BUTT_X4+BUTT_WIDE+BUTT_GAP1)
#define BUTT_X6		(BUTT_X5+BUTT_WIDE+BUTT_GAP1)


#define BUTT_Y1		(CALCUL_RESULT_Y+30+5)
#define BUTT_Y2		(BUTT_Y1+BUTT_HIGH+BUTT_GAP2)
#define BUTT_Y3		(BUTT_Y2+BUTT_HIGH+BUTT_GAP2)
#define BUTT_Y4		(BUTT_Y3+BUTT_HIGH+BUTT_GAP2)
#define BUTT_Y5		(BUTT_Y4+BUTT_HIGH+BUTT_GAP2)
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
// #define BUTT_RUN_KEY	24


//------------ͼ���С����---------------------------
#define	 F1_PIC_SIZE	6968//




//------------�ļ������ַ--------
#define  PIC_DIS_SAVE1		(DOWNFILE_SDRAM_ADD+0x200000)    //0x81680000��ǰ��ʾ���� �ݴ���1
#define  PIC_DIS_SAVE2		(PIC_DIS_SAVE1+0x00100000)//0x8157d000    //��ǰ��ʾ���� �ݴ���2
#define  PIC_DIS_SAVE3		(PIC_DIS_SAVE2+0x00100000)//0x81600000    //��ǰ��ʾ���� �ݴ���3
#define  PIC_DIS_SAVE4		(PIC_DIS_SAVE3+0x00100000)//0x8167d000    //��ǰ��ʾ���� �ݴ���4


#define  df_zk_sdram        (PIC_DIS_SAVE4+0x00100000)// 0x81880000            //0x81700000�ֿ�2M

#define  START_PIC_sdram   (df_zk_sdram+0x200000)  //0xa0800000         //����ͼƬ
#define  WOEK_BACK_dis     (START_PIC_sdram+1440056)        //��������
#define  PEAR_sdram			(WOEK_BACK_dis+1440056)//Ѽ��
//************ ************
#define  SHIFT_BUTT_UP_sdram		(PEAR_sdram+98304)//shift ��ťup
#define  SHIFT_BUTT_DOWN_sdram		(SHIFT_BUTT_UP_sdram+6840)//shift ��ťdown
#define  SCHEDULE_sdram		(SHIFT_BUTT_DOWN_sdram+6840)//������
#define  CURSOR_sdram		(SCHEDULE_sdram+16700)	//���
//------------------��ģʽͼƬ
#define	 FUN_PIC_SIZE	252056
#define	 F1_LABEL_MOD_PIC_sdram		(CURSOR_sdram+3128)//��ǩģʽ ͼƬ
#define	 F2_DIVIDE_MOD_PIC1_sdram	(F1_LABEL_MOD_PIC_sdram+FUN_PIC_SIZE)//�ȷ���ģʽ	ͼƬ
#define	 F3_DIVIDE_MOD_PIC2_sdram	(F2_DIVIDE_MOD_PIC1_sdram+FUN_PIC_SIZE)//�ȷ�ֵģʽ	ͼƬ
#define	 F2_DATAS_MOD_PIC_sdram		(F3_DIVIDE_MOD_PIC2_sdram+FUN_PIC_SIZE)//����ģʽ ͼƬ
#define	 F3_CLOCK_MOD_PIC_sdram		(F2_DATAS_MOD_PIC_sdram+FUN_PIC_SIZE)//ʱ��ģʽ ͼƬ
#define	 PASSWORD_MOD_PIC_sdram		(F3_CLOCK_MOD_PIC_sdram+FUN_PIC_SIZE)//����ģʽ ͼƬ
#define  RULER_SIZE		294616
#define	 F1_RULER_MOD_PIC_sdram		(PASSWORD_MOD_PIC_sdram+FUN_PIC_SIZE)//��׼ģʽ ͼƬ
//***********************************F1,2,3,4...

#define  F1_LABELS_UP_sdram			(F1_RULER_MOD_PIC_sdram+RULER_SIZE)//F1up
#define  F2_DIVIDE_UP_sdram			(F1_LABELS_UP_sdram+F1_PIC_SIZE)//F1up
#define  F3_SELECT_PRO_UP_sdram			(F2_DIVIDE_UP_sdram+F1_PIC_SIZE)//F1up
// #define  F4_SWITCH_UP_sdram		(F3_SELECT_PRO_UP_sdram+F1_PIC_SIZE)//�л�ѡ��up
// #define  F5_DELETEALL_UP_sdram	(F4_SWITCH_UP_sdram+F1_PIC_SIZE)//ɾ��ȫ��up
#define  F4_PUSH_UP_sdram		(F3_SELECT_PRO_UP_sdram+F1_PIC_SIZE)//F4��ֽ
//-------F1,2,3...�Զ� �ֶ�ģʽ��
#define  F1_RULER_UP_sdram	(F4_PUSH_UP_sdram+F1_PIC_SIZE)//F1����up
#define  F2_PARAMETER_sdram	(F1_RULER_UP_sdram+F1_PIC_SIZE)//F2����up
#define  F3_PLUS_UP_sdram	(F2_PARAMETER_sdram+F1_PIC_SIZE)//F3++up
#define  F3_CLOCK_UP_sdram	(F3_PLUS_UP_sdram+F1_PIC_SIZE)//F3ʱ��up
#define  F4_MINUS_UP_sdram	(F3_CLOCK_UP_sdram+F1_PIC_SIZE)//F4--up
#define	 F4_WHEEL0_sdram		(F4_MINUS_UP_sdram+F1_PIC_SIZE) //�������ֿ���0
#define	 F4_WHEEL1_sdram		(F4_WHEEL0_sdram+F1_PIC_SIZE) //�������ֿ���1
#define	 F5_WHEEL0_sdram		(F4_WHEEL1_sdram+F1_PIC_SIZE) //�������ֿ���0
#define	 F5_WHEEL1_sdram		(F5_WHEEL0_sdram+F1_PIC_SIZE) //�������ֿ���1
#define	 F6_AMEND0_sdram		(F5_WHEEL1_sdram+F1_PIC_SIZE) //--------------�޸�ƫ�Ƴߴ�
#define	 F6_AMEND1_sdram		(F6_AMEND0_sdram+F1_PIC_SIZE) //--------------�޸�ƫ�Ƴߴ�

// #define	 F1_RULER_sdram		(F1_RULER_MOD_PIC_sdram+RULER_SIZE)	//F1��׼
// #define	 F2_PARAMETER_sdram		(F1_RULER_sdram+PROGRAM_PIC_SIZE)	//F2����
// #define	 F3_CLOCK_sdram		(F2_PARAMETER_sdram+PROGRAM_PIC_SIZE)	//F3����ʱ��
// #define	 F3_ADD_UP_sdram		(F3_CLOCK_sdram+PROGRAM_PIC_SIZE)	//F3++up
// #define	 F3_ADD_DOWN_sdram		(F3_ADD_UP_sdram+PROGRAM_PIC_SIZE)	//F3++down
// #define	 F4_SUB_UP_sdram		(F3_ADD_DOWN_sdram+PROGRAM_PIC_SIZE)	//F4--up
// #define	 F4_SUB_DOWN_sdram		(F4_SUB_UP_sdram+PROGRAM_PIC_SIZE)	//F4--down
#define	 F4_PULSE_UP_sdram		(F6_AMEND1_sdram+F1_PIC_SIZE)	//F4���嵱��

#define  F5_CUT_UP_sdram	(F4_PULSE_UP_sdram+F1_PIC_SIZE)//F5��
#define  F0_ALLCUT_UP_sdram	(F5_CUT_UP_sdram+F1_PIC_SIZE)//F0��


#define  F1_OK_UP_sdram		(F0_ALLCUT_UP_sdram+F1_PIC_SIZE)//���
#define  F2_EXIT_UP_sdram	(F1_OK_UP_sdram+F1_PIC_SIZE) //F2�˳�up
#define  L_R_ARROW_sdram	(F2_EXIT_UP_sdram+F1_PIC_SIZE)//���Ҽ�ͷ
#define  F2_DIVNUM_UP_sdram		(L_R_ARROW_sdram+F1_PIC_SIZE)//F2�ȷ���up
#define  F2_DIVNUM_DOWN_sdram		(F2_DIVNUM_UP_sdram+F1_PIC_SIZE)//F2�ȷ���down
#define  F3_DIVDATA_UP_sdram		(F2_DIVNUM_DOWN_sdram+F1_PIC_SIZE)//F3�ȷ�ֵup
#define  F3_DIVDATA_DOWN_sdram		(F3_DIVDATA_UP_sdram+F1_PIC_SIZE)//F3�ȷ�ֵdown
//����ѡ��
#define  F1_LOOK_UP_sdram		(F3_DIVDATA_DOWN_sdram+F1_PIC_SIZE)//F1�鿴 ������Ϣup
#define  F2_BY_TIME_UP_sdram	(F1_LOOK_UP_sdram+F1_PIC_SIZE)//F2 ��ʱ�� ��ʾup
#define  F2_BY_TIME_DOWN_sdram	(F2_BY_TIME_UP_sdram+F1_PIC_SIZE)//F2 ��ʱ�� ��ʾdown
#define  F3_BY_NUM_UP_sdram		(F2_BY_TIME_DOWN_sdram+F1_PIC_SIZE)//F3 ����� ��ʾup
#define  F3_BY_NUM_DOWN_sdram	(F3_BY_NUM_UP_sdram+F1_PIC_SIZE)//F3 ����� ��ʾdown
#define  F4_DELETE_ONE_PRO_UP_sdram	(F3_BY_NUM_DOWN_sdram+F1_PIC_SIZE)//F4ɾ��һ��pro
#define  F5_DELETE_ALL_PRO_UP_sdram	(F4_DELETE_ONE_PRO_UP_sdram+F1_PIC_SIZE)//F5ɾ������pro
//������Ϣ
#define	 F1_PINYIN_UP_sdram		(F5_DELETE_ALL_PRO_UP_sdram+F1_PIC_SIZE)//ƴ������up
#define	 F1_PINYIN_DOWN_sdram		(F1_PINYIN_UP_sdram+F1_PIC_SIZE)//ƴ������down
#define	 F2_CHAR_UP_sdram		(F1_PINYIN_DOWN_sdram+F1_PIC_SIZE)//��ĸ����up
#define	 F2_CHAR_DOWN_sdram		(F2_CHAR_UP_sdram+F1_PIC_SIZE)//��ĸ����down
#define	 F3_NUM_UP_sdram		(F2_CHAR_DOWN_sdram+F1_PIC_SIZE)//��������up
#define	 F3_NUM_DOWN_sdram		(F3_NUM_UP_sdram+F1_PIC_SIZE)//��������down
#define  F4_EXIT_UP_sdram		(F3_NUM_DOWN_sdram+F1_PIC_SIZE)//F4�˳�up
#define	 F6_EXIT_BUTT_sdram		(F4_EXIT_UP_sdram+F1_PIC_SIZE) //F6�˳� ��ť
#define	 ENTER_BUTT_sdram		(F6_EXIT_BUTT_sdram+F1_PIC_SIZE) //ȷ�� ��ť
//---------------------
#define KNIFE_SENSOR_PIC_SIZE	1956

#define  KNIFE_UP_sdram		(ENTER_BUTT_sdram+F1_PIC_SIZE)//����
#define  KNIFE_DOWN_sdram	(KNIFE_UP_sdram+KNIFE_SENSOR_PIC_SIZE)//����
#define  PRESS_UP_sdram		(KNIFE_DOWN_sdram+KNIFE_SENSOR_PIC_SIZE)//ѹ��
#define  PRESS_DOWN_sdram	(PRESS_UP_sdram+KNIFE_SENSOR_PIC_SIZE)//ѹ��
#define  IR_LINE_sdram		(PRESS_DOWN_sdram+KNIFE_SENSOR_PIC_SIZE)   //����
#define  IR_CUT_sdram		(IR_LINE_sdram+KNIFE_SENSOR_PIC_SIZE) //�� ����

#define  FRONT_PAGE_UP_sdram	(IR_CUT_sdram+KNIFE_SENSOR_PIC_SIZE)//ǰ��
#define  BACK_PAGE_UP_sdram		(FRONT_PAGE_UP_sdram+F1_PIC_SIZE)//����up
#define  UP_ARROW_UP_sdram		(BACK_PAGE_UP_sdram+F1_PIC_SIZE)//�ϼ�ͷup
#define  DOWN_ARROW_UP_sdram		(UP_ARROW_UP_sdram+F1_PIC_SIZE)//�¼�ͷup
#define  FAST_FORWD_UP_sdram	(DOWN_ARROW_UP_sdram+F1_PIC_SIZE)	//���up
#define  FAST_BACK_UP_sdram		(FAST_FORWD_UP_sdram+F1_PIC_SIZE) 	//����up
//---------------���  button
#define	 RED_KNIFE_BUTT_sdram	(FAST_BACK_UP_sdram+F1_PIC_SIZE) //�쵶 ��ť
#define	 PUSH_PAPER_BUTT_sdram	(RED_KNIFE_BUTT_sdram+F1_PIC_SIZE) //��ֽ ��ť
#define	 SORT_PAPER_BUTT_sdram	(PUSH_PAPER_BUTT_sdram+F1_PIC_SIZE) //��ֽ ��ť
#define	 CRASH_PAPER_BUTT_sdram	(SORT_PAPER_BUTT_sdram+F1_PIC_SIZE) //ײֽ ��ť
#define	 AIR_BED_BUTT_sdram		(CRASH_PAPER_BUTT_sdram+F1_PIC_SIZE) //���� ��ť
//---------------���  pic
#define  ALL_FLAG_SIZE		5456
#define  RED_KNIFE_F_sdram	(AIR_BED_BUTT_sdram+F1_PIC_SIZE)//�쵶���	ͼ��
#define  PUSH_PAPER_F_sdram (RED_KNIFE_F_sdram+ALL_FLAG_SIZE)//��ֽ���	ͼ��
#define  SORT_PAPER_F_sdram (PUSH_PAPER_F_sdram+ALL_FLAG_SIZE)//��ֽ���	ͼ��
#define  CRASH_PAPER_F_sdram (SORT_PAPER_F_sdram+ALL_FLAG_SIZE)//ײֽ���	ͼ��
#define  AIR_BED_F_sdram 	(CRASH_PAPER_F_sdram+ALL_FLAG_SIZE)//������	ͼ��
//---
#define  STOP_UP_sdram		(AIR_BED_F_sdram+ALL_FLAG_SIZE)		//ֹͣ
#define  RUN_UP_sdram		(STOP_UP_sdram+7256)		//����
#define  DELETE_UP_sdram		(RUN_UP_sdram+7256)//ɾ��up
#define  DELETE_ALL_UP_sdram	(DELETE_UP_sdram+7256)//ȫɾup


//------------ͼ���С����---------------------------


//---------------------------------
#define  K_SIZE_sdram		(DELETE_ALL_UP_sdram+7256)//0x81e00000       //������ ������


//**************ͼƬ��ʾλ�ö���*******
//�Ҽ�ͷ-->
#define  SIZETEXT_HIGH	55//60 //�ߴ��б� �о�
#define  SIZEWORD_HIGH	(32-1)  //�ߴ��б� �о�
#define  PROTEXT_HIGH	45//35  //�����б� �о�
#define  RIGHT_ARROW_X	45
#define  RIGHT_ARROW_Y	210//190
//�б��ұ�ҳ ��ʼλ��
#define  RIGHT_PAGE_X	400//360  
//������
#define  SCHEDULE_X		390//710
#define  SCHEDULE_Y		230//200
#define  SCHEDULE_WIDE	20
#define  SCHEDULE_HIGH	200//334
//���ȿ�
#define  SCHEDULE_DOT_X	(SCHEDULE_X+4)
#define  SCHEDULE_DOT_Y	(SCHEDULE_Y+35)//143

//ģʽ ���� ��
#define	 MODE_NAME_COLOR	0x1256//����ɫ0x3339
#define  MODE_NAME_X1	330//350
#define  MODE_NAME_Y1	510//409
#define  MODE_NAME_X2	(MODE_NAME_X1+250)
#define  MODE_NAME_Y2	(MODE_NAME_Y1+42)

//�ߴ������
#define  SIZE_WINDOW_X	5//20
#define  SIZE_WINDOW_Y	550//408
#define  SIZE_WINDOW_WIDE	185//120
#define  SIZE_WINDOW_HIGH	45//30
#define  SIGN_2WIDE		30//24
//��ʾ��
#define  REMIND_WINDOW_X	210//SIZE_WINDOW_X
#define  REMIND_WINDOW_Y	560//446
#define  REMIND_LENGTH		380  //��ʾ�򳤶�

//------------------�м��ҳ---------------------------
#define  MIDDLE_PAGE_X	RIGHT_ARROW_X
#define  MIDDLE_PAGE_Y	170//
//----------------��ҳ��С
#define  M_PAGE_WIDE	750
#define  M_PAGE_HIGH	350//260



//������ʾ���С
#define  START_PROM_WIDE	600
#define  START_PROM_HIGH	30
//������һ�й��� ��ʾ
#define	 START_PROMPT_X1	130//REMIND_WINDOW_X
#define	 START_PROMPT_Y1	500//(REMIND_WINDOW_Y-50)
//�����ڶ��й��� ��ʾ
#define	 START_PROMPT_X2	START_PROMPT_X1
#define	 START_PROMPT_Y2	(START_PROMPT_Y1+50)//(REMIND_WINDOW_Y-50)

//**���� ������ʾ-----
#define  KEYBOARD_CHECK_X	START_PROMPT_X1
#define  KEYBOARD_CHECK_Y	450

//ϵͳ�汾ѡ�� ����
#define	 SYSBD_HINT_X	200
#define	 SYSBD_HINT_Y	120
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
#define  PEAR_X		330
#define  PEAR_Y		140
//************************************����ͼ��
//"����"
#define  PROG_X		40
#define  PROG_Y		120//
//"����"
#define  STEP_X		(PROG_X+180)
#define  STEP_Y		PROG_Y
//�����
#define  PROG_NUM_X		(PROG_X+100)
#define  PROG_NUM_Y		PROG_Y
//�����
#define  STEP_NUM_X		(STEP_X+100)
#define  STEP_NUM_Y		PROG_Y
//������
#define  PRO_NAME_DIS_COLOR	CURREN_UNIT_BACK_COLOR//0x12bc
#define  PRO_NAME_DIS_X		35
#define  PRO_NAME_DIS_Y		45
//******************�ߴ���ʾ
//��ǰ�ߴ� 
// #define  FRONT_KNIFE_X	450
// #define  FRONT_KNIFE_Y	100//61
//��ǰ�ߴ� 
#define CURR_SIZE_X		480//490 //��ǰ�ߴ� ��ʾλ��
#define CURR_SIZE_Y		55
#define FRONT_KNIF_X	510//535
#define FRONT_KNIF_Y	110//FRONT_KNIFE_Y
//--------------����ICON--------------------
//��ǩ����
#define	LABEL_FUN_PIC_X		380//400
#define	LABEL_FUN_PIC_Y		185
//�ȷֹ���
#define	DIVIDE_FUN_PIC_X	LABEL_FUN_PIC_X
#define	DIVIDE_FUN_PIC_Y	LABEL_FUN_PIC_Y
//����
// #define  PROCESS_X	  	LABEL_FUN_PIC_X
// #define  PROCESS_Y		LABEL_FUN_PIC_Y
//��������
#define SETDATA_FUN_PIC_X	LABEL_FUN_PIC_X
#define SETDATA_FUN_PIC_Y	(LABEL_FUN_PIC_Y+180)
//��׼����
#define RULER_FUN_PIC_X		150//LABEL_FUN_PIC_X
#define RULER_FUN_PIC_Y		LABEL_FUN_PIC_Y
//��������
#define CLOCK_FUN_PIC_X		LABEL_FUN_PIC_X
#define CLOCK_FUN_PIC_Y		LABEL_FUN_PIC_Y
//���빦��
#define PASSWORD_FUN_PIC_X	LABEL_FUN_PIC_X
#define PASSWORD_FUN_PIC_Y	LABEL_FUN_PIC_Y



// ��ģʽ  5��ť-------
// #define	 PROGRAM_BUTT_X		8
// #define  PROGRAM_BUTT_Y		170    //���mod��ť
// #define	 MANUAL_BUTT_X		PROGRAM_BUTT_X
// #define	 MANUAL_BUTT_Y		(PROGRAM_BUTT_Y+ICONBUTT_GAP_V)  //�ֶ�mod��ť
// #define	 AUTO_BUTT_X		PROGRAM_BUTT_X
// #define	 AUTO_BUTT_Y		(MANUAL_BUTT_Y+ICONBUTT_GAP_V)//�Զ�mod��ť
// #define	 TEACH_BUTT_X		PROGRAM_BUTT_X
// #define	 TEACH_BUTT_Y		(AUTO_BUTT_Y+ICONBUTT_GAP_V)//ʾ��mod��ť
// #define	 AUTOCUT_BUTT_X		PROGRAM_BUTT_X
// #define	 AUTOCUT_BUTT_Y		(TEACH_BUTT_Y+ICONBUTT_GAP_V)//�Ե�mod��ť
//-----F1,F2,F3,...
#define	 ICONBUTT_GAP_V		65//58
#define	 ICONBUTT_WIDE		65

#define  F1LABEL_BUTT_X		705//745
#define  F1LABEL_BUTT_Y		180//PROGRAM_BUTT_Y  //F1��ǩ��ť
#define  F2DIVIDE_BUTT_X	F1LABEL_BUTT_X
#define  F2DIVIDE_BUTT_Y	(F1LABEL_BUTT_Y+ICONBUTT_GAP_V)  //F2�ȷְ�ť
#define  F3PROJECT_BUTT_X	F1LABEL_BUTT_X
#define  F3PROJECT_BUTT_Y	(F2DIVIDE_BUTT_Y+ICONBUTT_GAP_V)  //F3����ť
#define  F4SWITCH_BUTT_X		F1LABEL_BUTT_X
#define  F4SWITCH_BUTT_Y		(F3PROJECT_BUTT_Y+ICONBUTT_GAP_V)  //F4�л���ť
//����up
#define	 BACK_PAGE_X	440
#define	 BACK_PAGE_Y	(F4SWITCH_BUTT_Y)
//ǰ��
#define	 FRONT_PAGE_X	(BACK_PAGE_X+ICONBUTT_WIDE)
#define	 FRONT_PAGE_Y	BACK_PAGE_Y
//����
#define	 FAST_BACK_X	BACK_PAGE_X
#define	 FAST_BACK_Y	(BACK_PAGE_Y+ICONBUTT_GAP_V)
//���
#define	 FAST_FWD_X		FRONT_PAGE_X
#define	 FAST_FWD_Y		FAST_BACK_Y

//F5����
#define  F5_CUT_X		(FRONT_PAGE_X+ICONBUTT_WIDE)//450
#define  F5_CUT_Y		FAST_BACK_Y//210
//F0���е�
#define  F0_ALL_CUT_X	(F5_CUT_X+ICONBUTT_WIDE)
#define  F0_ALL_CUT_Y	FAST_BACK_Y
//F6
#define  F6EXIT_BUTT_X		F1LABEL_BUTT_X
#define  F6EXIT_BUTT_Y		 FAST_BACK_Y //F6
//F3��   F5��ok
#define  F5DELETE_BUTT_X		(FRONT_PAGE_X+ICONBUTT_WIDE)
#define  F5DELETE_BUTT_Y		  FAST_BACK_Y//F5  ��ť
#define  ENTER_OK_BUTT_X	F0_ALL_CUT_X//ȷ��
#define  ENTER_OK_BUTT_Y	F0_ALL_CUT_Y
//---------------------------



//F1����up
#define  F1_RULER_X	 F1LABEL_BUTT_X
#define  F1_RULER_Y	 F1LABEL_BUTT_Y
//F2����up
#define  F2_TOOLS_X	 F2DIVIDE_BUTT_X
#define  F2_TOOLS_Y	 F2DIVIDE_BUTT_Y
//F3++up
#define  F3_PLUS_X	 F3PROJECT_BUTT_X
#define  F3_PLUS_Y	 F3PROJECT_BUTT_Y
//F4--up
#define  F4_MINUS_X	 F4PUSHFLAG_BUTT_X
#define  F4_MINUS_Y	 F4PUSHFLAG_BUTT_Y
//F3ʱ��up
#define  F3_CLOCK_X	 F3PROJECT_BUTT_X
#define  F3_CLOCK_Y	 F3PROJECT_BUTT_Y
 //F4��������  
#define	 F4_WHEEL_BUTT_X		F1LABEL_BUTT_X 
#define	 F4_WHEEL_BUTT_Y		F4PUSHFLAG_BUTT_Y

#define	 F5_WHEEL_BUTT_X		F5_CUT_X//F1LABEL_BUTT_X  //F5��������  
#define	 F5_WHEEL_BUTT_Y		F5_CUT_Y
#define	 F6_AMEND_BUTT_X	F6EXIT_BUTT_X	//�޸�ƫ����
#define	 F6_AMEND_BUTT_Y	F6EXIT_BUTT_Y
#define  F4PUSHFLAG_BUTT_X	F4SWITCH_BUTT_X
#define  F4PUSHFLAG_BUTT_Y	F4SWITCH_BUTT_Y


//------- ��  &ѹֽ  pic
//����
#define  KNIFE_UP_X		20//
#define  KNIFE_UP_Y		510
//����
#define  KNIFE_DOWN_X		KNIFE_UP_X
#define  KNIFE_DOWN_Y		KNIFE_UP_Y

//����1
#define  KNIFE1_UP_X		KNIFE_UP_X+30
#define  KNIFE1_UP_Y		KNIFE_UP_Y
//����1
#define  KNIFE1_DOWN_X		KNIFE1_UP_X
#define  KNIFE1_DOWN_Y		KNIFE1_UP_Y
//ѹ��
#define  PRESS_UP_X		(KNIFE1_UP_X+30)
#define  PRESS_UP_Y		KNIFE_UP_Y
//ѹ��
#define  PRESS_DOWN_X		(PRESS_UP_X)
#define  PRESS_DOWN_Y		(PRESS_UP_Y)

//����
#define	IR_X	(PRESS_UP_X+30)
#define	IR_Y	KNIFE_UP_Y//F6EXIT_BUTT_Y



//�ֶ�ģʽ��      ���˼�
#define  MAN_BACK_PAGE_X	100 
#define  MAN_BACK_PAGE_Y	220//200 
//�ֶ�ģʽ��       ǰ��
#define  MAN_FRONT_PAGE_X	(MAN_BACK_PAGE_X+120)
#define  MAN_FRONT_PAGE_Y	MAN_BACK_PAGE_Y


//����
#define	MAN_FAST_BACK_X MAN_BACK_PAGE_X
#define MAN_FAST_BACK_Y (MAN_BACK_PAGE_Y+120)
//���up
#define	MAN_FAST_FWD_X	MAN_FRONT_PAGE_X
#define	MAN_FAST_FWD_Y	MAN_FAST_BACK_Y


//---shift button
#define SHIFT_BUTT_WIDE	70
#define SHIFT_BUTT_HIGH	32
#define SHIFT_BUTT_X	210
#define SHIFT_BUTT_Y	510
//����up
#define  RUN_BIG_WIDE	60
#define  RUN_BIG_HIGH	40
#define  RUN_X		610//DELETE_X
#define  RUN_Y		530//
//ֹͣup
#define  STOP_X		(RUN_X+90)
#define  STOP_Y		RUN_Y

//ɾ��up
#define  DELETE_X		RUN_X//620
#define  DELETE_Y		RUN_Y//410
//ȫɾup
#define  DELETE_ALL_X	(DELETE_X+80)
#define  DELETE_ALL_Y	DELETE_Y

//�쵶flag
//#define  RED_KNIFE_X	340//350
//#define  RED_KNIFE_Y	170
//��ֽflag
//#define  PUSH_FLAG_X	RED_KNIFE_X
//#define  PUSH_FLAG_Y	RED_KNIFE_Y

//F4---��� �趨��ť
#define F4_FLAG_WIN_X		520
#define F4_FLAG_WIN_Y		250
#define F4_FLAG_WIN_WIDE	250//270
#define F4_FLAG_WIN_HIGH	180
#define FLAG_BUTT_GAP1		80
#define FLAG_BUTT_GAP2		80
#define FLAG_WIDE		60
#define FLAG_HIGH		60
//F1 ���� ��ť
#define F1_AIR_BED_X	(F4_FLAG_WIN_X+20)
#define F1_AIR_BED_Y	(F4_FLAG_WIN_Y+20)
//F2 ��ֽ ��ť
#define	 F2_SORT_PAPER_X	(F1_AIR_BED_X+FLAG_BUTT_GAP1)
#define  F2_SORT_PAPER_Y	F1_AIR_BED_Y
//F3 ײֽ ��ť
#define	 F3_CRASH_PAPER_X	(F2_SORT_PAPER_X+FLAG_BUTT_GAP1)
#define  F3_CRASH_PAPER_Y	F1_AIR_BED_Y
//F4��ֽ��־ ��ť
#define  F4_PUSH_PAPER_X	F1_AIR_BED_X
#define	 F4_PUSH_PAPER_Y	(F1_AIR_BED_Y+FLAG_BUTT_GAP2)
//F5 �쵶  ��ť
#define	 F5_RED_KNIFE_X		(F4_PUSH_PAPER_X+FLAG_BUTT_GAP1)
#define	 F5_RED_KNIFE_Y		F4_PUSH_PAPER_Y
//F6 �˳� ��ť
#define  F6_FLAG_EXIT_X		(F5_RED_KNIFE_X+FLAG_BUTT_GAP1)
#define  F6_FLAG_EXIT_Y		F4_PUSH_PAPER_Y

//******************�����ʾ  ͼ��
//�쵶	��־pic
#define  RED_KNIFE_PIC_X	300//320
#define  RED_KNIFE_PIC_Y	150
//��ֽ���pic
#define  PUSH_FLAG_PIC_X	RED_KNIFE_PIC_X	
#define  PUSH_FLAG_PIC_Y	RED_KNIFE_PIC_Y
//ײֽpic
#define	 CRASH_FLAG_PIC_X	RED_KNIFE_PIC_X	
#define  CRASH_FLAG_PIC_Y	RED_KNIFE_PIC_Y
//��ֽpic
#define	 SORT_FLAG_PIC_X	RED_KNIFE_PIC_X	
#define  SORT_FLAG_PIC_Y	RED_KNIFE_PIC_Y
//����pic
#define  AIR_FLAG_PIC_X		(RED_KNIFE_PIC_X+40)
#define  AIR_FLAG_PIC_Y		RED_KNIFE_PIC_Y

//#define  TABLE_END_COL		(AIR_FLAG_PIC_X+60)
#define  TABLE_END_COL		(AIR_FLAG_PIC_X+30)

//--------------------��ģʽF1,2.....
//���up
#define  FINISHED_X	  	F1LABEL_BUTT_X
#define  FINISHED_Y		F1LABEL_BUTT_Y
//F2�˳�up
#define  F2OUT_X		F2DIVIDE_BUTT_X
#define  F2OUT_Y		F2DIVIDE_BUTT_Y
//���Ҽ�ͷ
#define  L_R_ARROW_X	F6EXIT_BUTT_X//FINISHED_X
#define  L_R_ARROW_Y	F6EXIT_BUTT_Y//(F2OUT_Y+58)
//�Ӳ˵� ����
#define  SUB_UP_ARROW_X	 BACK_PAGE_X
#define  SUB_UP_ARROW_Y	 FAST_BACK_Y
//�Ӳ˵� ����
#define  SUB_DOWN_ARROW_X	FRONT_PAGE_X
#define  SUB_DOWN_ARROW_Y	SUB_UP_ARROW_Y
//�Ӳ˵� F3��ǩ����
#define  F3_LABEL_TIME_X	F3PROJECT_BUTT_X
#define  F3_LABEL_TIME_Y	F3PROJECT_BUTT_Y
//�Ӳ˵� F4��ǩ�ϱ�
#define  F4_LABEL_DESERT_X	F4SWITCH_BUTT_X
#define  F4_LABEL_DESERT_Y	F4SWITCH_BUTT_Y











//--------F1��ǩҳ
#define TOTAL_SIZE_X 	220
#define TOTAL_SIZE_Y 	250
#define ROW_GAP1		50
#define ROW_GAP2		60
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
#define ARROW_WIDE	32
#define PROC_NUM_X	(RIGHT_ARROW_X+ARROW_WIDE)
#define PROC_NUM_Y	(RIGHT_ARROW_Y+10)
#define PROC_NAME_X	(PROC_NUM_X+60)
#define PROC_NAME_Y	PROC_NUM_Y
#define PROC_STEP_X	(PROC_NAME_X+320)
#define PROC_STEP_Y	PROC_NUM_Y
#define PROC_DATE_X (PROC_STEP_X+70)
#define PROC_DATE_Y	PROC_NUM_Y
// ���� ��Ϣ ��ʾ
#define PRO_MESS_COLOR1 0xFF5b
#define PRO_MESS_COLOR2 0xFFff

#define PRO_MESS_X		45//70
#define PRO_MESS_Y		(PROC_NUM_Y-35)
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
#define PARA_START_X1		80
#define PARA_START_X2		230
#define PARA_START_Y		210
#define PARA_COL_WIDE		350
#define PARA_ROW_GAP		40

//----------F3ʱ�� ����ҳ
#define CLOCK_DATA_X	120
#define CLOCK_DATA_Y	240	
#define CLOCK_GAP_Y		PARA_ROW_GAP	//40
//����ͼƬ
#define MACHINE_PIC_X	100
#define MACHINE_PIC_Y	220
//�б�� �ұ߽�
#define  DATA_TABLE_END_X	(MACHINE_PIC_X+500)


//-------------���� ���� ��ʾҳ��
#define PULSE_SET_X1		100
#define PULSE_SET_X2		400
#define PULSE_SET_Y		 200
#define PULSE_GAP_Y		 PARA_ROW_GAP	//40
//--------����ģʽ ����

#define PASS_TIME1_X	100		//����λ��
#define PASS_TIME1_Y	200
#define PASS_TIME_GAP	100//80
//------passcode ����
#define PASSCODE_X		100//220
#define PASSCODE_Y		240
#define PASS_HINT_X		(PASSCODE_X+550)
#define PASS_HINT_Y		PASSCODE_Y

#define PASSCODE_INPUT_X	(PASSCODE_X+200)
#define PASSCODE_INPUT_Y	(PASSCODE_Y+50)

//����ѹֽsensor λ��ʾ��
#define KNIFE_SENSOR_X	220
#define KNIFE_SENSOR_Y	323
#define PRESS_SENSOR_X	458
#define PRESS_SENSOR_Y	275
//******�Ե���ʾ
#define SELF_PROMP_X	100
#define SELF_PROMP_Y	200
#define SELF_PROMP_WIDE 350
#define SELF_PROMP_HIGH 150
//�Ե�OK
#define SELF_OK_X		(SELF_PROMP_X+20)
#define SELF_OK_Y		(SELF_PROMP_Y+75)
#define SELF_OK_WIDE	130//110
#define SELF_OK_HIGH	40
//�Ե� ȡ��
#define SELF_CANCEL_X	(SELF_OK_X+140)
#define SELF_CANCEL_Y	SELF_OK_Y
//--���� run ��ʾ
#define RUN_DIS_X		400//550
#define RUN_DIS_Y		START_PROMPT_Y2//REMIND_WINDOW_Y


//-----------start jog  ���� Jog����
#define START_JOG_WIDE		130
#define START_JOG_HIGH		50

#define START_JOG_BACK_X	650
#define START_JOG_BACK_Y	400

#define START_JOG_FORW_X	(START_JOG_BACK_X+80)
#define START_JOG_FORW_Y	START_JOG_BACK_Y

//---���� ��ť

// #define RUN_BUTT_X		210
// #define RUN_BUTT_Y		520

//----ɾ��ȫ�� ��ʾ��
#define DEL_ALL_WIN_X	420//400
#define DEL_ALL_WIN_Y	250//300
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
#define	HELP_RET_X	550
#define	HELP_RET_Y	50
//
#define	HELP_CORRECT_X 20
#define	HELP_CORRECT_Y HELP_RET_Y
//���� F1У׼����
#define HELP_GAP_Y	60
#define HELP_F1_X	200
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
#define F2_PAGE_UP_Y	540
//��ҳ
#define F2_PAGE_DOWN_X	500
#define F2_PAGE_DOWN_Y	F2_PAGE_UP_Y
//F2����
#define F2_RET_HELP_X	680
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
#define VER_SEL_UP_Y	200//160
//�¼�ͷ
#define VER_SEL_DOWN_X	VER_SEL_UP_X
#define VER_SEL_DOWN_Y	(VER_SEL_UP_Y+180)



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


//�����ģʽ
#define PROG_LABEL_MODE		0x11//��ǩ
#define PROG_DIVIDE_MODE	0x12//�ȷ�
#define PROG_PRO_MODE		0x13//����ѡ��
#define PROG_PRO_MESS_MODE	0x131//���� ��Ϣ
#define PROG_DEL_ALL_PRO_MODE	0x132//	ɾ������pro
#define PROG_DEL_ALL_SIZE_MODE	0x133//	ɾ�����гߴ�

#define PROG_FLAG_MODE		0x14//��� ģʽ
//�Զ���ģʽ
#define AUTO_RULER_MODE  0x21//��׼
#define AUTO_TOOLS_MODE  0x22 //����
#define AUTO_PLUS_MODE   0x23//F3++
#define AUTO_MINUS_MODE  0x24//F4--
#define AUTO_TO_SELF_MODE 0x25
//�ֶ���ģʽ
#define MANUAL_RULER_MODE  0x31//��׼
#define MANUAL_TOOLS_MODE  0x32//
#define MANUAL_CLOCK_MODE  0x33
#define MANUAL_PULSE_MODE  0x34//�趨���嵱��
#define MANUAL_PASS_MODE   0x35//����
#define MANUAL_SERVO_C_MODE   0x36//ֱ���ŷ� C ����
//ʾ����ģʽ
#define TEACH_LABEL_MODE	0x41//��ǩ
#define TEACH_DIVIDE_MODE	0x42//�ȷ�
#define TEACH_PRO_MODE		0x43//����ѡ��
#define TEACH_PRO_MESS_MODE	0x431//���� ��Ϣ
#define TEACH_DEL_ALL_PRO_MODE	0x432//	ɾ������pro
#define TEACH_DEL_ALL_SIZE_MODE	0x433//	ɾ�����гߴ�

#define TEACH_FLAG_MODE		0x44//��� ģʽ
//�Ե���ģʽ
#define SELF_RULER_MODE  0x51//��׼
#define SELF_TOOLS_MODE  0x52 //����
#define SELF_PLUS_MODE   0x53//F3++
#define SELF_MINUS_MODE  0x54//F4--

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
#define FRONT_LIM_MAX		(80*100)
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

#define MARGIN_SIZE		45//25
#define DC_VIRTURE_SIZE 1500

//---------------------���� ʮ��
#define TOUCH_X1	50
#define TOUCH_Y1	50

#define TOUCH_X2	TOUCH_X1
#define TOUCH_Y2	550//440

#define TOUCH_X3	750
#define TOUCH_Y3	TOUCH_Y2

#define TOUCH_X4	TOUCH_X3
#define TOUCH_Y4	TOUCH_Y1

#define TOUCH_X_MID	(C_GLCD_H_SIZE>>1)
#define TOUCH_Y_MID	(C_GLCD_V_SIZE>>1)

//---������ text
#define CAL_INPUT	0  //���������
#define CAL_RESULT	1   //�����


//-----------�����������
#define  MOTOR_FREQ_5_SPD_RST	0  //��Ƶ�� 5����+��λ
#define  MOTOR_FREQ_3_SPD		1  //��Ƶ�� 3����
#define  MOTOR_FREQ_3_SPD_RST	2  //��Ƶ�� 3����+��λ
#define	 MOTOR_DC_SERVO	 		3//ֱ���ŷ�
#define	 MOTOR_DC670_SERVO	 	4//ֱ���ŷ�670
#define	 MOTOR_AC_SERVO	 		5//�����ŷ�
#define	 MOTOR_AC_SERVO_REV	 	6//�����ŷ�����

#define  MOTOR_AC_A6_SERVO      7//7//����A6  MODBUSͨ��

//����
#define MAX_KNIFE1		999  //�ܵ���1-999
#define MAX_KNIFE2		399  //�ܵ���1-399

#define PRO_HEAD_BYTES    100
//ÿ�����򳤶�
#define PROG_BYTES1		((MAX_KNIFE1*5)+PRO_HEAD_BYTES)//MAX_KNIFE1 ������ +2byte����
#define PROG_BYTES2		((MAX_KNIFE2*5)+PRO_HEAD_BYTES)

#define PROG_GROPU1		300  //ǰ300������
#define MAX_PROG		500//��500������

//*************************************************
// #define	PAGE_KNIFE	5		//ÿҳ����
// #define	PAGE2_KNIFE	(PAGE_KNIFE*2)		//2ҳ����
#define	PROGS_1PAGE	5		//ÿҳ ����
//*****************************************
//------*********��ʶ�� Ԥ����
#define NO_FLAG		0
#define PUSH_FLAG   1   //��ֽ ��־λ����
#define SORT_FLAG   2   // ��ֽ  ��־λ����
#define CRASH_FLAG  3   // ײֽ  ��־λ����
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

extern Int32U AirOffDistance;//����������
extern Int8U AirOffOK_flag;//
extern Int8U AirOffStart_flag;

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
extern Int32U VirtualTargetSizeGap;
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
void ParameterPage_dis(Int8U sel, Int8U flag); //���� ������ʾ
void TimeSetSel_dis(Int8U sel, Int8U flag); //ʱ�� �趨 ��ʾ

void PromptNum_dis(void);  //�������ݷ�Χ ��ʾ
void SelPulseDegree_dis(Int8U sel,Int8U flag); //�����趨
void PassDaysSet_dis(Int8U sel,Int8U flag);//�����趨

void SetMotorSpeed(Int8U speed_sel);//�趨�ٶ�
void Draw_cross(Int16U x,Int16U y,Int16U color);

void ProgressBar_dis(Int16U total, Int16U now);  //������ ��ʾ
void Knife_Down_dis(Int16U x, Int16U y);//����

#endif
