////////////////////////
//   ���� ��������
////////////////////////



#ifndef __KEY_H

#define __KEY_H

#include "main.h"
#include "sys.h"
#include "uart.h"
#include"drv_glcd.h"

#define KEYIO_DDR FIO3DIR
#define KEYPUL_IO FIO3PIN

#define KEYIO FIO3PIN  //���̿ڶ���




#define KEY_COL1 31			//��1
#define KEY_COL1_DIR_OUT()  FIO3DIR |= 1ul<<KEY_COL1
#define KEY_COL1_CLR()	FIO3CLR |= 1ul<<KEY_COL1
#define KEY_COL1_SET()	FIO3SET |= 1ul<<KEY_COL1

#define KEY_COL2 30			//��2
#define KEY_COL2_DIR_OUT()  FIO3DIR |= 1ul<<KEY_COL2
#define KEY_COL2_CLR()	FIO3CLR |= 1ul<<KEY_COL2
#define KEY_COL2_SET()	FIO3SET |= 1ul<<KEY_COL2

#define KEY_COL3 29			//��3
#define KEY_COL3_DIR_OUT()  FIO3DIR |= 1ul<<KEY_COL3
#define KEY_COL3_CLR()	FIO3CLR |= 1ul<<KEY_COL3
#define KEY_COL3_SET()	FIO3SET |= 1ul<<KEY_COL3

#define KEY_COL4 28			//��4
#define KEY_COL4_DIR_OUT()  FIO3DIR |= 1ul<<KEY_COL4
#define KEY_COL4_CLR()	FIO3CLR |= 1ul<<KEY_COL4
#define KEY_COL4_SET()	FIO3SET |= 1ul<<KEY_COL4

#define KEY_COL5 27			//��5
#define KEY_COL5_DIR_OUT()  FIO3DIR |= 1ul<<KEY_COL5
#define KEY_COL5_CLR()	FIO3CLR |= 1ul<<KEY_COL5
#define KEY_COL5_SET()	FIO3SET |= 1ul<<KEY_COL5


#define KEY_COL6 26			//��6
#define KEY_COL6_DIR_OUT()  FIO3DIR |= 1ul<<KEY_COL6
#define KEY_COL6_CLR()	FIO3CLR |= 1ul<<KEY_COL6
#define KEY_COL6_SET()	FIO3SET |= 1ul<<KEY_COL6

#define KEY_CODE_MASK 0x03e00000



/*
#define ZERO_KEY_CODE	0x8200000	//��ż�
#define ONE_KEY_CODE	0x8400000	//һ�ż�
#define TWO_KEY_CODE	0x8800000	//���ż�
#define THREE_KEY_CODE	0x9000000	//���ż�
#define FOUR_KEY_CODE	0xa000000	//�ĺż�
#define FIVE_KEY_CODE	0xc000000	//��ż�

#define SIX_KEY_CODE	0x10200000	//���ż�
#define SEVEN_KEY_CODE	0x10400000	//�ߺż�
#define EIGHT_KEY_CODE	0x10800000	//�˺ż�
#define NINE_KEY_CODE	0x11000000	//�źż�
#define AUTO_KEY_CODE 0x12000000 // AUTO ����  ��һ�� ��һ�� 
#define PROG_KEY_CODE 0x14000000 // PROGRAM ����  ������ ������

#define YES_KEY_CODE 0x20200000   // yes ���� �ڶ��� ������
#define NO_KEY_CODE 0x20400000     // no ����  ������  ��һ��
#define MOVE_KEY_CODE 0x20800000  // move ���� ������ �ڶ���
#define READ_KEY_CODE 0x21000000    // ���� ����  ������  ������
#define ADD_KEY_CODE 0x22000000  //  +�� ��  ������ ���ļ�
#define SUB_KEY_CODE	0x24000000 // - ����  ������ �����


#define INSERT_KEY_CODE 0x40200000     //�������
#define DELETE_KEY_CODE 0x40400000     //ɾ������
#define RETURN_KEY_CODE 0x40800000     //���ؼ���
#define NEXTKINFE_KEY_CODE 0x41000000  //��һ������
#define ADJUST_KEY_CODE 0x42000000    //��׼����
#define OPTION_KEY_CODE 0x44000000   //OPTION ����

#define REV_KEY_CODE 0x80200000  //  REVIEW ����  ������ ��һ��
#define MANUAL_KEY_CODE 0x80400000  // MANUAL ����  ������ �ڶ���
#define UP_KEY_CODE 0x80800000   // �� ����  ������ ������
#define DOWN_KEY_CODE 0x81000000  // �� ����  ������ ���ļ�   
#define DENGFENG_KEY_CODE 0x82000000 //�ȷּ���
#define DENGJU_KEY_CODE 0x84000000  //�Ⱦ����

*/
#define tst_KEY_CODE	0x4c00000	//******

#define ZERO_KEY_CODE	0x4200000	//��ż�
#define ONE_KEY_CODE	0x4400000	//һ�ż�
#define TWO_KEY_CODE	0x4800000	//���ż�
#define THREE_KEY_CODE	0x5000000	//���ż�
#define FOUR_KEY_CODE	0x6000000	//�ĺż�

#define FIVE_KEY_CODE	0x8200000	//��ż�
#define SIX_KEY_CODE	0x8400000	//���ż�
#define SEVEN_KEY_CODE	0x8800000	//�ߺż�
#define EIGHT_KEY_CODE	0x9000000	//�˺ż�
#define NINE_KEY_CODE	0xa000000	//�źż�

#define AUTO_KEY_CODE 0x10200000 // AUTO ����  ��һ�� ��һ�� 
#define PROG_KEY_CODE 0x10400000 // PROGRAM ����  ������ ������
#define YES_KEY_CODE  0x10800000   // yes ���� �ڶ��� ������
#define NO_KEY_CODE   0x11000000     // no ����  ������  ��һ��
#define MOVE_KEY_CODE 0x12000000  // move ���� ������ �ڶ���

#define READ_KEY_CODE   0x20200000    // ���� ����  ������  ������
#define ADD_KEY_CODE    0x20400000  //  +�� ��  ������ ���ļ�
#define SUB_KEY_CODE	0x20800000 // - ����  ������ �����
#define INSERT_KEY_CODE 0x21000000     //�������
#define DELETE_KEY_CODE 0x22000000     //ɾ������

#define RETURN_KEY_CODE		 0x40200000     //���ؼ���
#define NEXTKINFE_KEY_CODE	 0x40400000  //��һ������
#define ADJUST_KEY_CODE		 0x40800000    //��׼����
#define OPTION_KEY_CODE		 0x41000000   //OPTION ����
#define REV_KEY_CODE		 0x42000000  //  REVIEW ����  ������ ��һ��

#define MANUAL_KEY_CODE		 0x80200000  // MANUAL ����  ������ �ڶ���
#define UP_KEY_CODE			 0x80400000   // �� ����  ������ ������
#define DOWN_KEY_CODE		 0x80800000  // �� ����  ������ ���ļ�   
#define DENGFENG_KEY_CODE	 0x81000000 //�ȷּ���
#define DENGJU_KEY_CODE		 0x82000000  //�Ⱦ����

#define ENABLE 1
#define DISABLE 0

#define KEYLONGDOWNTIMEDATA 800  // ������ʱ��ֵ   ����Ϊ0.8S

extern int KeyCode;  //������
extern int KeyDownTime;  //��ɨ�¼�ʱ
extern int KeyLongDownTime;  //����ʱ�䰴�¼�ʱ
extern char KeyDown_Flag;   //�����±�־λ
extern char KeyExec_Flag;   //�������־λ
extern char KeyLongDown_Flag;
extern unsigned char InputBuf[30];
extern unsigned char InputCou;
extern int KeyCode_Temp;
extern unsigned long int vbcd;
extern void KeyScan(void);  //��ɨ��  1MS����һ��
extern void KeyExec(void);  //������
extern int KeyCheck(void);
extern void KeyReadCode(void);
extern void Key_Enable(unsigned char enb);
extern void KeyInit(void);  //���˿ڳ�ʼ��
 extern void lcdpage1(void);
extern  void lcdnian( unsigned long int x0, unsigned long int y0,unsigned int  chicun); 
extern  void lcdhaoma( unsigned long int x0, unsigned long int y0,unsigned char chicun);
extern  void chengxudu(void);
extern  void lcdweizhicn( unsigned long int x0, unsigned long int y0,unsigned long int chicun);
extern  void lcdweizhicnH( unsigned long int x0, unsigned long int y0,unsigned long int chicun);
 extern void lcdzhishi(void);

extern  unsigned  long int  vbcd4,  qianjixian,zhongjixian,houjixian,jizhun,mubiao ;
extern  unsigned char bcd[3],qbcd[3],hbcd[5];
extern   unsigned char status,flagyunxing8,flagrun,huamian,flagshanchu;         //
extern   unsigned char step_ground;   //
extern   unsigned char step_add;      //
extern   unsigned char qianjin,houtui,huamian,daohao,flagdanwei;
extern   unsigned char   flagqyx,  t0zhongduan, poweon_flag,senor;
extern    unsigned  char flaggong,flaghsd,flagqsd;
extern    unsigned char flagchengxu,flagkeysong,flagzhiyou;
extern     unsigned  char flagjia,flagjian,flagcheng,flagchu;
extern    unsigned long int yushu,mada;
extern    unsigned long int speedup_steps;
extern    unsigned long int speedup_steps_B;
extern    unsigned long int rollsteps;     
extern    unsigned char flagtingji7,flagtingji8,flagbz[200],chengxuhaoma;

extern    unsigned long int qianjincn,houtuicn,weizhicn[200],ymuqiancn;
extern    unsigned long int  tempqianjin1, temphoutui1; 












#endif



