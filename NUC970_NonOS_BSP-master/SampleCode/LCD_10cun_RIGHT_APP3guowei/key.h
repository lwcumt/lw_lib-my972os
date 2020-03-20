////////////////////////
//   ���� ��������
////////////////////////

//----------�ռ䣺			2M==2097152
//----------����ռ��Ԥ����	500
//----------ʣ��(2M-����):  2M-500=2096652

//-----------�ܵ����ݣ�		1897500+500*100=1947500
//-----------reserve��		149152



#ifndef __KEY_H

#define __KEY_H

#include "main.h"
//#include "sys.h"
#include "uart.h"
#include"drv_glcd.h"

#include "pcf8563.h"
#include "touch.h"

#define KEYIO_DDR FIO3DIR
#define KEYPUL_IO FIO3PIN

#define KEYIO FIO3PIN  //���̿ڶ���



#define KEY_COL1 31			//��1
#define KEY_COL1_DIR_OUT()  FIO3DIR |= 1ul<<KEY_COL1
#define KEY_COL1_CLR()	FIO3DIR |= 1ul<<KEY_COL1;\
						FIO3CLR |= 1ul<<KEY_COL1

#define KEY_COL1_SET()	FIO3DIR &= ~(1ul<<KEY_COL1);\
						FIO3SET |= 1ul<<KEY_COL1

#define KEY_COL2 30			//��2
#define KEY_COL2_DIR_OUT()  FIO3DIR |= 1ul<<KEY_COL2
#define KEY_COL2_CLR()		FIO3DIR |=1ul<<KEY_COL2;\
							FIO3CLR |= 1ul<<KEY_COL2

#define KEY_COL2_SET()	FIO3DIR &= ~(1ul<<KEY_COL2);\
						FIO3SET |= 1ul<<KEY_COL2

#define KEY_COL3 29			//��3
#define KEY_COL3_DIR_OUT()  FIO3DIR |= 1ul<<KEY_COL3
#define KEY_COL3_CLR()	FIO3DIR |= 1ul<<KEY_COL3;\
						FIO3CLR |= 1ul<<KEY_COL3

#define KEY_COL3_SET()	FIO3DIR &= ~(1ul<<KEY_COL3);\
						FIO3SET |= 1ul<<KEY_COL3

#define KEY_COL4 28			//��4
#define KEY_COL4_DIR_OUT()  FIO3DIR |= 1ul<<KEY_COL4
#define KEY_COL4_CLR()	FIO3DIR |= 1ul<<KEY_COL4;\
						FIO3CLR |= 1ul<<KEY_COL4

#define KEY_COL4_SET()	FIO3DIR &= ~(1ul<<KEY_COL4);\
						FIO3SET |= 1ul<<KEY_COL4

#define KEY_COL5 27			//��5
#define KEY_COL5_DIR_OUT()  FIO3DIR |= 1ul<<KEY_COL5
#define KEY_COL5_CLR()	FIO3DIR |= 1ul<<KEY_COL5;\
						FIO3CLR |= 1ul<<KEY_COL5

#define KEY_COL5_SET()	FIO3DIR &=~( 1ul<<KEY_COL5);\
						FIO3SET |= 1ul<<KEY_COL5


#define KEY_COL6 26			//��6
#define KEY_COL6_DIR_OUT()  FIO3DIR |= 1ul<<KEY_COL6
#define KEY_COL6_CLR()	FIO3DIR |= 1ul<<KEY_COL6;\
						FIO3CLR |= 1ul<<KEY_COL6

#define KEY_COL6_SET()	FIO3DIR &= ~(1ul<<KEY_COL6);\
						FIO3SET |= 1ul<<KEY_COL6

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
#define STOP_KEY_CODE	0xaa55000	//******


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
#define NEXTKNIFE_KEY_CODE	 0x40400000  //��һ������
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

#define KEYLONGDOWNTIMEDATA 2000  // ������ʱ��ֵ   ����Ϊ5S

//--------------8�� ��������

#define MUL_KEY_CODE      MUL_TOUCH_CODE //0xffff0007  // *
#define DIV_KEY_CODE      DIV_TOUCH_CODE//0xffff0008  // /
#define EQUAL_KEY_CODE    EQU_TOUCH_CODE//0xffff0009  //  =
#define HELP_KEY_CODE     0xffff1000  //����
#define PROC_KEY_CODE     0xffff1001 //����
#define JOSTLE_KEY_CODE   0xffff1002 //��ֽ
#define PGUP_KEY_CODE     0xffff1003 //��ҳ
#define PGDOWN_KEY_CODE   0xffff1004 //��ҳ
#define MODIFY_KEY_CODE   0xffff1005 //�޸�
#define F5_KEY_CODE   	  0xffff1006 //F5
#define F6_KEY_CODE       0xffff1007 //F6
#define LEFT_KEY_CODE       0xffff1008 //��
#define RIGHT_KEY_CODE       0xffff1009 //��
#define SHIFT_KEY_CODE       0xffff100a //shift
#define FAST_AHEAD_KEY_CODE       0xffff100b //���
#define FAST_BACK_KEY_CODE       0xffff100c //����
#define SHIFT_1_KEY_CODE       0xffff100d //shift+1
#define SHIFT_8_KEY_CODE       0xffff100e //shift+8
#define SHIFT_0_KEY_CODE       0xffff100f //shift+0
#define SHIFT_F5_KEY_CODE       0xffff1010 //shift+F5

#define DEL_ALL_KEY_CODE       0xffff1011 //ɾ������


//------------ʱ���λ��
#define Tx_1  50
#define Ty_1  2 
#define SpaceX  50
#define SpaceY  50
#define Gap   20

#define Tx_2  (Tx_1+SpaceX+Gap)
#define Ty_2  Ty_1

#define Tx_3  (Tx_2+SpaceX+Gap)
#define Ty_3  Ty_1

#define Tx_4  (Tx_3+SpaceX+Gap*2)
#define Ty_4  Ty_1

#define Tx_5  (Tx_4+SpaceX+Gap)
#define Ty_5  Ty_1

#define LineY  (Ty_1+24)//�����

#define Line1_Y  (Ty_1+20)//ð����
#define Line2_Y  (Line1_Y+15)//ð����
//---------ʱ������λ��
#define TimNum_Y 17

#define Year1_X  (Tx_1+4)//Year   S
#define Year1_Y  (TimNum_Y)

#define Year0_X  (Tx_1+24)//Year   G
#define Year0_Y  (Year1_Y)

#define Month1_X  (Tx_2+4)//Month
#define Month1_Y  (Year1_Y)

#define Month0_X  (Tx_2+24)
#define Month0_Y  (Year1_Y)

#define Date1_X  (Tx_3+4)//Date
#define Date1_Y  (Year1_Y)

#define Date0_X  (Tx_3+24)
#define Date0_Y  (Year1_Y)

#define Hour1_X  (Tx_4+4)//Hour
#define Hour1_Y  (Year1_Y)

#define Hour0_X  (Tx_4+24)
#define Hour0_Y  (Year1_Y)

#define Min1_X  (Tx_5+4)//Min
#define Min1_Y  (Year1_Y)

#define Min0_X  (Tx_5+24)
#define Min0_Y  (Year1_Y)



//-------------------�� ����
#define DATA_SAVE_OFFSET    500//  spi ������ ��ʼ��ַ
#define PRO_NUM_25PEADD		0//  ���� �� ���������ַ
#define ORIGINAL_25PEADD	10//  ԭ�㱣���ַ(�趨����)

//-�ߴ��޶�
//#define SIZE_MIN	 	3000
//#define SIZE_MAIX      145000


//****************���ܲ���  ģʽ------
#define TEST_NO   0
#define TEST_HELP   1
#define TEST_TOUCH  2
#define TEST_ICON   3
#define TEST_BOARD   4
#define TEST_SYS_WORD  5
#define TEST_SYS_TYPE  6
#define TEST_PAGE_LINE  7

// ---------passcode
#define PASS_MOD_CODE		111111//687610 //����ģʽ 
#define PASSCODE_formula(code)  (code*2+2)  //�����㷨

//--------------------------
#define NO_SIGN		0   //   
#define PLUS_SIGN	1   //  +
#define MINUS_SIGN	2   //  -
#define MULT_SIGN	3   //  *
#define DIV_SIGN	4   //  /

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
extern void KeyExec(Int32U keycode);  //������
extern void LongKey_exec(Int32U keycode,Int32U key_temp);  //����������
extern void MultiKey_exec(Int32U keycode);  //��ϼ�����
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
extern   unsigned char step_add,qianjinflag,houtuiflag;      //
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



extern  unsigned char Comment_flag;
extern unsigned char WorkStart_flag;
extern unsigned char flagyunxing;



extern Int8U PromptDis_flag;
extern unsigned long int maichongdangliang,xxmuqiancn;
extern Int32U PassCode;
extern Int8U PaperCutEnb_signal;
extern Int8U StartCheck_mode;
extern Int8U OutSensorOK_flag;
extern Int32U Zpulse_cou;
extern Int32U Z_Pulse;
extern Int32U Z_Pulse_before;
extern Int8U Z_Pulse_start_flag;
extern Int8U Z_Pulse_err_flag;
extern Int32U PulseAB_Z_current;
extern Int8U PulseAB_Z_save_time;
//extern Int8U RunToCusor_flag;

extern unsigned char num_cou;
extern unsigned char Size_temp[8];

extern Int8U BellStart_flag;
extern Int8U Board_TestMod;
extern Int8U TouchCalcu_mode;
extern Int8U InputTouch_flag;

extern Int8U PassCheckDis_flag;

extern Int8U AutoRoute_flag;

extern Int8U ManualMoveMode;
extern Int8U Stop_F_Remind_flag;

extern Int8U TargetBell_flag;
extern Int16U TargetBell_time;
extern Int8U TargetBell_mode;

extern unsigned  char flagyd;
extern unsigned char flagchengxu,flagkey,flagtime1;
extern Int8U AC_MotorSPD; //AC  motor  speed

extern Int8U RunEnb_flag;
extern Int8U AutoCutDisable_flag;


//******************************************
void ClrInput_function(void);//���� �����

void SaveOneKnife_datas(Int16U prog,Int16U order ,pInt8U pdatas);//����һ������
void GetOneKnife_datas(Int16U prog,Int16U order ,pInt8U pdatas);//��sdram��ȡһ������
void SaveBuf_datas(Int16U prog,Int16U order1, Int16U order2);//���� order1�� order2  buf�������ݵ�spi
void ClrBuf_datas(Int16U prog,Int16U order1, Int16U order2);//���� order1�� order2  buf��������

void GetPro_headInfo(Int16U prog, pInt8U pdata);//sdram ��һ������ͷ(������+ ʱ�� +���� )
void OneProgHeadInfo_dis(Int8U row, Int16U p_order, Int8U mark_flag);	//һ������ ��ʾ
void Size_1page_dis(Int16U start_order,Int16U row);//һҳ�ߴ���ʾ

void DeleteOneKnife(Int16U prog,Int16U knife);      //ɾ��һ��
void InsertOneKnife(Int16U prog,Int16U knife);       //����һ��
void SavePro_headInfo(Int16U prog, pInt8U pdata);//spi����һ������� ͷ(������+ ʱ�� +���� )

Int8U CheckInputNums(void);  //����ߴ� ����

void LabelSel_dis(Int8U sel, Int8U flag);
void DivideSel_dis(Int8U sel, Int8U flag);
void CursorDown_inTable(void); //**** ������� ��ʾ ����
void PageUpExec(void);	//�Ϸ�ҳ
void PageDownExec(void);	//�·�ҳ

void DivideTypeSelExec(void);	//�ȷ� ����  ѡ��........
void Label_function(void);  //��ǩ����
void Divide_function(void);  //�ȷֹ���
void LabelEnter_exec(void); //��ǩ ���� �����趨ȷ��
void DivideEnter_exec(void); //�ȷ� �����趨ȷ��

void Prog_1page_dis(Int16U prog,Int16U line);//һҳ������ʾ
void ProEnter_exec(void);  //����ѡ�� ����ȷ��

void ExportOnePro_dis(Int16U p_order); //���� ��ʾһ������-------------
void ReorderProByDate_dis(void);	//��ʱ������ �����б�
void DeleteOneProg(Int8U cursor, Int16U p_order);		//F4 ----ɾ��һ������
void DeleteAllProg(void);		//F5--- ɾ�����г���

void F3_AutoAdd_exec(Int32U add_data);  //F3++  �������� �Լ�
void F4_AutoSub_exec(Int32U add_data); //F4--  �������� �Լ�

void ReadFrontLimit(void);  //��ȡǰ����
void SaveFrontLimit(void);  //����ǰ����
void ReadMiddleLimit(void);  //��ȡ�м���
void SaveMiddleLimit(void);  //�����м���
void ReadBackLimit(void);  //��ȡ����
void SaveBackLimit(void);  //�������
void ReadLanguage(void);//��ȡ����
void SaveLanguage(void); //��������
void ReadUnit(void);//��ȡ��λ
void SaveUnit(void);  //���浥λ
void ReadAheader(void);//��ȡ��ǰ��
void SaveAheader(void);  //������ǰ��
void Read_degree(void);
void Save_degree(void);
void ReadPushDistance(void);//��ȡ�Զ���ֽ����
void SavePushDistance(void);  //�����Զ���ֽ����
void ReadSpeedLevel(void);  //��ȡ �ٶȵ�λ��
void SaveSpeedLevel(void);  //���� �ٶȵ�λ��
void ReadPressValid_flag(void);  //ѹֽ ��Ч��־
void SavePressValid_flag(void);
void ReadMachineType(void);  //��������
void SaveMachineType(void);  //��������

void SaveOriginalSize(void);  //����ԭ��ߴ�
void SetPulse_degree(void);  //�趨���嵱��
void GeneratePassCode(void);
void PassCheck_dis(Int16U x, Int16U y); //������ʾ

void SaveFirstDays(void);
void ReadFirstDays(void);
void SaveSecondDays(void);
void ReadSecondDays(void);
void SaveFirstDays_flag(void);
void ReadFirstDays_flag(void);
void SaveSecondDays_flag(void);
void ReadSecondDays_flag(void);
void SaveWorkDays(void);


void ReadACMotorSpeed(void);   //�����ŷ� �ٶ�
void SaveACMotorSpeed(void);   //�����ŷ� �ٶ�
void ReadAirOffDistance(void);	//������ ����
void SaveAirOffDistance(void);	//������ ����
void ReadElectricWheelSwitch(void);//��������
void SaveElectricWheelSwitch(void);//��������
void ReadIRValidStatus(void);	//IR set
void SaveIRValidStatus(void);
void ReadPageKf_Size(void);	//ÿҳ ������
void SavePageKf_Size(void);
void PageKf_Size_Init(void);	//ÿҳ ������ʼ��

void DaysTime_check(void);

void RunTo_cursor(void); //������ ��괦
void AutoRun_start(void);


void CalcData_input_to_text(Int32U data_temp,pInt8U str_text);  //ת����bcd ��

void CalculatorValue_exec(Int8U sign);  //����ֵ ����
void Calcul_Nums(Int8U a_n1,Int8U a_n2,Int8U b_n1,Int8U b_n2, Int8U sign);  //�����������  ���� �ý������CalcData_temp
void DataConvert_to_Text(Int32U data_temp,pInt8U str_text);  //���������� ת����bcd ��

void CalcGetValue_exec(void);             //= ���� ���ý��

//void ShiftSpeed_SetExec(Int32U keycode);  //�����趨������
void AutoRun_AutoPush_exec(void);  // �Զ� ѭ������

void StopMotorExec(void);


void CheckKnifeSum_exec(void);  //--------------�ܵ���    �˶�

void GetAC_MotorSpeed(void);  //�����ŷ�  �ٶ��ж�


void F5_KeyExec(void);//F5  ����
void F6_KeyExec(void);//F6  ����
void AllFlagSetExec(Int8U flag); //F4 ����趨  ����................
void AllKnifeFlagExec(Int8U dis);	//��ӣ���� --���е����
void F4MessageMode_Exit(void); //�˳�  ������Ϣģʽ
void ProMessageModify_mode(Int16U p_order);	//������Ϣ�޸� ģʽ

void PulseDegreeSet_exec(void);	//���嵱�� �趨
void DeleteAllExitWind(void);	//�˳�ȫɾ ��ʾ��
void RenewModifyDate(void);	//����ʱ����Ϣ-.-.-.-.-.-.-.-.-.-.-.-.-.-

void DeleteAllData_hintWind(void);	//ɾ����������  ��ʾ��


#endif




