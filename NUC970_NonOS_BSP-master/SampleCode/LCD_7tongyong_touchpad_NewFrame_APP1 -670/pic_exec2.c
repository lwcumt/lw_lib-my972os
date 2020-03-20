
#include "pic_exec.h"


//#include"realtime.h"

#include"bmp.h"
#include"file.h"
#include"word_lib.h"

#include"servo.h"
#include"chndot.h"
#include"key.h"
#include"port.h"
#include"name_input.h"

Int16U cursor_row;//��� λ��(��)
Int16U  TableDis_startcol;//��ʼ��

Int16U Knife_order; //��ǰ����
Int16U Knife_sum;//�ܵ���
Int16U Knife_sum_before;//�ܵ���  У��
Int16U MAIX_Knife;//��൶��

//Int16U Process_num;//��ǰ���� ��
//Int16U MaixProcess_num;//��� �����

PROG_SEG Pro_data;//���� �� ��


unsigned char PorgSet_sel;

unsigned char BeforeKnifeNo_flag;

unsigned short WorkMode;

Int32U CurrentSize;
Int32U BeforeKnifeSize;
Int32U BeforeKnife_offset;
Int32U BeforeKnife_offset_in;
Int32U OriginalSize;//ԭ��
Int32U CurrentSize_temp;

Int8U Unit;//��λ
Int8U Language;//����
Int8U PressValid_flag;//

Int32U FrontLimit;
Int32U MiddleLimit;
Int32U BackLimit;
Int32U Aheader;
Int32U StanDistance;

Int8U Pulse_degree;
Int8U PassModeIn_flag=0;
Int8U PassModeOk_flag=0;

Int32U Size_MIN;
Int32U Size_MAX;
Int32U Size_MIN_num;
Int32U Size_MAX_num;
Int32U FirstDays;
Int32U SecondDays;
Int32U AutoPushDistance;
Int8U FirstDayValid_flag;
Int8U SecondDayValid_flag;

Int8U PassCodeEn_flag;
//Int8U SelfCutEnter_flag;

const Int8U PulseDegree[12][3]={"0","1","2","3","4","5","6","7","8","9","10","11"};
const Int8U PulseResolut[12][4]={"50","50","50","50","60","60","60","60","100","100","120","120"};
const Int8U ScrowResolut[12][3]={"10","12","8","18","12","10","8","18","10","12","10","12"};

Int32U TargetSize;
Int32U TargetSize_temp;
Int32U TargetSize_inch;

Int8U Forward_flag;
Int8U Backward_flag;

Int8U Run_flag;
Int8U BackStop_flag;
Int8U ForceStop_flag;
Int8U RunStop_flag;

Int8U MoveSpeed;
Int8U SelfLockEn_flag;
Int8U InTargetPosit_flag;

Int8U GoFrontEn_flag;
Int8U GoBackEn_flag;
Int8U GoFast_flag;
Int8U JogRunMode;
Int8U EncoderErr_flag;

Int8U RunDisplay_flag;
Int8U AutoPushRun_flag;
Int8U AutoCutExec_flag;
Int8U AutoCutStart_flag;
Int8U OneCutRoutine_flag;

Int8U PusherResetMove_flag;
Int16U PusherResetTime;


Int32U stop_time;


Int8U MotorType;

Int8U PushRstKey_flag;
Int8U ProcessRatio;

Int8U InputTouch_flag;
Int16U CodeSensorTime_AB;
Int8U CutPermit_flag;

Int8U ServoPressStop_flag;//�ŷ�ѹֽ ͣ��

Int8U DcServoGoTarget_flag;

Int16U LastAutoKnife_order;//  �Ե� ��ǰһ��
Int8U ReEnterAutoKnife_dis;  //�ٴν����Ե�  ��ʾ

Int8U ACServoDrvErr_flag;
Int8U ACServoAlarmExec_flag;

Int8U ElectricWheelOn_flag; //��������

Int32U current_inch;
Int8U MotorRun_flag;

Int8U GoDirMode=0;

//*****************��ȡ�ļ�
void ReadFiles(void)
{
//FileRead("��������.bmp",(unsigned char*)START_PIC_sdram);//����������
FileRead("Power.bmp",(unsigned char*)START_PIC_sdram);//����������

//GLCD_SetWindow_Fill(30,450,600,479,BLACK_COLOR,BLACK_COLOR);//*******************************

FileRead("����.bmp",(unsigned char*)WOEK_BACK_dis);//������
GLCD_SetWindow_Fill(0,0,799,479,BLACK_COLOR,BLACK_COLOR);//*******************************

FileRead("���.bmp",(unsigned char*)PROGRAM_sdram);//
FileRead("��ǩ.bmp",(unsigned char*)LABELS_sdram);//
FileRead("����.bmp",(unsigned char*)PARAMETER_sdram);//
FileRead("��.bmp",(unsigned char*)RULER_sdram);//
FileRead("�ȷ�.bmp",(unsigned char*)DIVIDE_sdram);//
FileRead("ʱ��.bmp",(unsigned char*)WATCH_sdram);//
FileRead("ʾ��.bmp",(unsigned char*)TEACH_sdram);//
FileRead("�ֶ�.bmp",(unsigned char*)MANUAL_sdram);//
FileRead("�Զ�.bmp",(unsigned char*)AUTO_sdram);//
FileRead("ѡ�����.bmp",(unsigned char*)SELECT_PRO_sdram);//
FileRead("�Ե�.bmp",(unsigned char*)AUTO_KNIFE_sdram);//

FileRead("��ǩ����.bmp",(unsigned char*)LABEL_FUN_sdram);//
FileRead("����.bmp",(unsigned char*)PROCESS_sdram);//
FileRead("����.bmp",(unsigned char*)TOOLS_sdram);//
FileRead("�ȷֹ���.bmp",(unsigned char*)DIVIDE_FUN_sdram);//
FileRead("��׼����.bmp",(unsigned char*)RULER_FUN_sdram);//
FileRead("����.bmp",(unsigned char*)CALENDAR_sdram);//
FileRead("F1up.bmp",(unsigned char*)F1UP_sdram);//
FileRead("F2up.bmp",(unsigned char*)F2UP_sdram);//
FileRead("F3up.bmp",(unsigned char*)F3UP_sdram);//
FileRead("F4up.bmp",(unsigned char*)F4UP_sdram);//
FileRead("F2�˳�up.bmp",(unsigned char*)F2_OUT_UP_sdram);//
FileRead("F1����up.bmp",(unsigned char*)F1_RULER_UP_sdram);//
FileRead("F2����up.bmp",(unsigned char*)F2_TOOLS_UP_sdram);//
FileRead("���.bmp",(unsigned char*)FINISHED_sdram);//
//FileRead("ʾ��ģʽ.bmp",(unsigned char*)TEACH_MOD_sdram);//
//FileRead("�Ե�ģʽ.bmp",(unsigned char*)AUTO_KNIFE_MOD_sdram);//
FileRead("����.bmp",(unsigned char*)KNIFE_UP_sdram);//
FileRead("����.bmp",(unsigned char*)KNIFE_DOWN_sdram);//
FileRead("ѹ��.bmp",(unsigned char*)PRESS_UP_sdram);//
FileRead("ѹ��.bmp",(unsigned char*)PRESS_DOWN_sdram);//
FileRead("��ɫA.bmp",(unsigned char*)RED_A_sdram);//
FileRead("��ɫB.bmp",(unsigned char*)RED_B_sdram);//
FileRead("��ɫA.bmp",(unsigned char*)BLACK_A_sdram);//
FileRead("��ɫB.bmp",(unsigned char*)BLACK_B_sdram);//
FileRead("����.bmp",(unsigned char*)RED_LINE_sdram);//
FileRead("�ֺ���.bmp",(unsigned char*)HAND_IR_sdram);//
FileRead("��ǰ.bmp",(unsigned char*)FRONT_KNIFE_sdram);//
FileRead("�쵶.bmp",(unsigned char*)RED_KNIFE_F_sdram);//
FileRead("��ֽ.bmp",(unsigned char*)PUSH_PAPER_F_sdram);//
FileRead("ѹֽѭ�����.bmp",(unsigned char*)PRE_AUTO_F_sdram);//
FileRead("����.bmp",(unsigned char*)SCHEDULE_sdram);//
FileRead("����λ��.bmp",(unsigned char*)SCHEDULE_DOT_sdram);//
FileRead("�Ҽ�ͷ.bmp",(unsigned char*)RIGHT_ARROW_sdram);//
FileRead("ʱ����.bmp",(unsigned char*)TIME_COL_sdram);//
FileRead("��ֽ��.bmp",(unsigned char*)PUSH_PAPER_TOOL_sdram);//
//FileRead("ȡ��up.bmp",(unsigned char*)CANCEL_UP_sdram);//
//FileRead("ȡ��down.bmp",(unsigned char*)CANCEL_DOWN_sdram);//
//FileRead("ȷ��up.bmp",(unsigned char*)ENTER_UP_sdram);//
//FileRead("ȷ��down.bmp",(unsigned char*)ENTER_DOWN_sdram);//
FileRead("ֹͣup.bmp",(unsigned char*)STOP_UP_sdram);//
//FileRead("ֹͣdown.bmp",(unsigned char*)STOP_DOWN_sdram);//
FileRead("����up.bmp",(unsigned char*)RUN_UP_sdram);//
//FileRead("����down.bmp",(unsigned char*)RUN_DOWN_sdram);//
FileRead("����ߴ�.bmp",(unsigned char*)INPUT_SIZE_sdram);//
FileRead("��ʾ��.bmp",(unsigned char*)REMIND_sdram);//
FileRead("��ֽ_��.bmp",(unsigned char*)PUSH_KNIFE_sdram);//
FileRead("λ��.bmp",(unsigned char*)POSITION_sdram);//
FileRead("���.bmp",(unsigned char*)ORDER_sdram);//
FileRead("�м��ҳ.bmp",(unsigned char*)MIDDLE_PAGE_sdram);//
FileRead("��߻�ҳ.bmp",(unsigned char*)LEFT_PAGE_sdram);//
FileRead("ɾ��up.bmp",(unsigned char*)DELETE_UP_sdram);//
FileRead("ȫɾup.bmp",(unsigned char*)DELETE_ALL_UP_sdram);//
FileRead("Ѽ��.bmp",(unsigned char*)PEAR_sdram);//
FileRead("F��up.bmp",(unsigned char*)F_KEY_UP_sdram);//
FileRead("����up.bmp",(unsigned char*)BACK_PAGE_UP_sdram);//
FileRead("ǰ��up.bmp",(unsigned char*)FRONT_PAGE_UP_sdram);//
FileRead("�ϼ�ͷup.bmp",(unsigned char*)UP_ARROW_UP_sdram);//
FileRead("�¼�ͷup.bmp",(unsigned char*)DOWN_ARROW_UP_sdram);//
FileRead("F3++up.bmp",(unsigned char*)F3_PLUS_UP_sdram);//
FileRead("F3ʱ��up.bmp",(unsigned char*)F3_CLOCK_UP_sdram);//
FileRead("F4--up.bmp",(unsigned char*)F4_MINUS_UP_sdram);//
//FileRead("F5��up.bmp",(unsigned char*)F5_CUT_UP_sdram);//
FileRead("���嵱��.bmp",(unsigned char*)PULSE_DEGREE_sdram);//
FileRead("��.bmp",(unsigned char*)LOCK_sdram);//
FileRead("�� Կ��.bmp",(unsigned char*)LOCK_KEY_sdram);//
FileRead("���Ҽ�ͷ.bmp",(unsigned char*)L_R_ARROW_sdram);//
FileRead("F5ѹֽѭ��up.bmp",(unsigned char*)F5_PRE_FLG_BUTT_UP_sdram);//

FileRead("wheel0.bmp",(unsigned char*)WHEEL0_sdram);//
FileRead("wheel1.bmp",(unsigned char*)WHEEL1_sdram);//
FileRead("F4_0.bmp",(unsigned char*)F4_WHEEL0_sdram);//
FileRead("F4_1.bmp",(unsigned char*)F4_WHEEL1_sdram);//
//FileRead("clock.bmp",(unsigned char*)test_sdram);//
FileRead("F5_YES.bmp",(unsigned char*)F5_YESCUT_sdram);//
FileRead("F5_NO.bmp",(unsigned char*)F5_NOCUT_sdram);//
FileRead("F0ALL_YES.bmp",(unsigned char*)F0_YESALLCUT_sdram);//
FileRead("F0ALL_NO.bmp",(unsigned char*)F0_NOALLCUT_sdram);//

FileRead("���up.bmp",(unsigned char*)FAST_FORWD_UP_sdram);
FileRead("����up.bmp",(unsigned char*)FAST_BACK_UP_sdram);
}

void StartPic_dis(void)//����������ʾ
{
pInt32U source_Ptr=(pInt32U)malloc(1024);
for(volatile Int32U i=0;i<256;i++)	//1k
	{
	source_Ptr[i]=0xffffffff;
	}
for(volatile Int32U i=0;i<24*1024;i++)//24k
	{
	pInt32U dest_Ptr=(pInt32U)(df_zk_sdram+i*1024);//           0xa0600000  //�ֿ�2M
	memcpy(dest_Ptr,source_Ptr,1024);
	}
free(source_Ptr);

FileRead("�ֿ�_0x20000.FON",(unsigned char *)df_zk_sdram);//
FileRead("Ѽ��.bmp",(unsigned char*)PEAR_sdram);//
switch(Language)
	{
	case CHN_HAN:
		Printf24("�����Լ죬���ݼ���.....��Ҫ6�룬���Եȣ�",40,450,RED_COLOR,1,0xffff);
			break;
	case ENGLISH:	
		Printf24("Computer is self-checking,loading data....",40,420,RED_COLOR,1,0xffff);
		Printf24("Please wait 6 seconds!",40,450,RED_COLOR,1,0xffff);
			break;
	}

//FileRead("��������.bmp",(unsigned char*)START_PIC_sdram);//����������
Pear_dis(PEAR_X, PEAR_Y);//Ѽ��
ReadFiles();  //��ȡ ͼ���ļ�
Bmp_Decode((Int32U)START_PIC_sdram, 0, 0, (pInt16U)SDRAM0_BASE_ADDR); //��ʾ��������

RLOUT1_OFF;    // �������

}

//************************��ʾͼƬ  Сͼ�궨��
void FirstBack_dis(void)//���� ����
{
Bmp_Decode((Int32U)WOEK_BACK_dis, 0, 0, (pInt16U)SDRAM0_BASE_ADDR);
//pInt16U pbuf,pdis;
//pbuf=(pInt16U)(WOEK_BACK_dis+4);
//pdis=(pInt16U)SDRAM0_BASE_ADDR;
//memcpy(pdis,pbuf,800*480*2); 
}

void Program_dis(Int16U x, Int16U y)//���
{
Bmp_Decode((Int32U)PROGRAM_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Label_dis(Int16U x, Int16U y)//��ǩ
{
Bmp_Decode((Int32U)LABELS_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Parameter_dis(Int16U x, Int16U y)//����
{
Bmp_Decode((Int32U)PARAMETER_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Ruler_dis(Int16U x, Int16U y)//��
{
Bmp_Decode((Int32U)RULER_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Divide_dis(Int16U x, Int16U y)//�ȷ�
{
Bmp_Decode((Int32U)DIVIDE_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Watch_dis(Int16U x, Int16U y)//ʱ��
{
Bmp_Decode((Int32U)WATCH_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Teach_dis(Int16U x, Int16U y)//ʾ��
{
Bmp_Decode((Int32U)TEACH_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Manual_dis(Int16U x, Int16U y)//�ֶ�
{
Bmp_Decode((Int32U)MANUAL_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Auto_dis(Int16U x, Int16U y)//�Զ�
{
Bmp_Decode((Int32U)AUTO_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void SelectPro_dis(Int16U x, Int16U y)//ѡ�����
{
Bmp_Decode((Int32U)SELECT_PRO_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void AutoKnife_dis(Int16U x, Int16U y)//�Ե�
{
Bmp_Decode((Int32U)AUTO_KNIFE_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void LabelFun_dis(Int16U x, Int16U y)//��ǩ����
{
Bmp_Decode((Int32U)LABEL_FUN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Process_dis(Int16U x, Int16U y)//����
{
Bmp_Decode((Int32U)PROCESS_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Tools_dis(Int16U x, Int16U y)//����
{
Bmp_Decode((Int32U)TOOLS_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void DivideFun_dis(Int16U x, Int16U y)//�ȷֹ���
{
Bmp_Decode((Int32U)DIVIDE_FUN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void RulerFun_dis(Int16U x, Int16U y)//��׼����
{
Bmp_Decode((Int32U)RULER_FUN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Calendar_dis(Int16U x, Int16U y)//����
{
Bmp_Decode((Int32U)CALENDAR_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F1up_dis(Int16U x, Int16U y)//F1up
{
Bmp_Decode((Int32U)F1UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F2up_dis(Int16U x, Int16U y)//F2up
{
Bmp_Decode((Int32U)F2UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F3up_dis(Int16U x, Int16U y)//F3up
{
Bmp_Decode((Int32U)F3UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F4up_dis(Int16U x, Int16U y)//F4up
{
Bmp_Decode((Int32U)F4UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Finish_dis(Int16U x, Int16U y)//���
{
Bmp_Decode((Int32U)FINISHED_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F1Ruler_Up_dis(Int16U x, Int16U y)//F1����up
{
Bmp_Decode((Int32U)F1_RULER_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F2Tools_Up_dis(Int16U x, Int16U y)//F2����up
{
Bmp_Decode((Int32U)F2_TOOLS_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F2out_Up_dis(Int16U x, Int16U y)//F2�˳�up
{
Bmp_Decode((Int32U)F2_OUT_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void TeachMode_dis(Int16U x, Int16U y)//ʾ��ģʽ
{
Bmp_Decode((Int32U)TEACH_MOD_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void AutoKnifeMode_dis(Int16U x, Int16U y)//�Ե�ģʽ
{
Bmp_Decode((Int32U)AUTO_KNIFE_MOD_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Knife_Up_dis(Int16U x, Int16U y)//����
{
Bmp_Decode((Int32U)KNIFE_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Knife_Down_dis(Int16U x, Int16U y)//����
{
Bmp_Decode((Int32U)KNIFE_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Press_Up_dis(Int16U x, Int16U y)//ѹ��
{
Bmp_Decode((Int32U)PRESS_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Press_Down_dis(Int16U x, Int16U y)//ѹ��
{
Bmp_Decode((Int32U)PRESS_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}



void Red_A_dis(Int16U x, Int16U y)//��ɫA
{
// Bmp_Decode((Int32U)RED_A_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Red_B_dis(Int16U x, Int16U y)//��ɫB
{
// Bmp_Decode((Int32U)RED_B_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Black_A_dis(Int16U x, Int16U y)//��ɫA
{
// Bmp_Decode((Int32U)BLACK_A_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Black_B_dis(Int16U x, Int16U y)//��ɫB
{
// Bmp_Decode((Int32U)BLACK_B_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void RedLine_dis(Int16U x, Int16U y)//����
{
Bmp_Decode((Int32U)RED_LINE_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Hand_IR_dis(Int16U x, Int16U y)//�� ����
{
Bmp_Decode((Int32U)HAND_IR_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void FrontKnife_dis(Int16U x, Int16U y)//��ǰ
{
Bmp_Decode((Int32U)FRONT_KNIFE_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void RedKnifeF_dis(Int16U x, Int16U y)//�쵶 ��־
{
Bmp_Decode((Int32U)RED_KNIFE_F_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void PushPaperF_dis(Int16U x, Int16U y)//��ֽ ��־
{
Bmp_Decode((Int32U)PUSH_PAPER_F_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void AutoRoutePRE_dis(Int16U x, Int16U y)//k�Զ�ѭ�� ��־
{
Bmp_Decode((Int32U)PRE_AUTO_F_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void Schedule_dis(Int16U x, Int16U y)//����
{
Bmp_Decode((Int32U)SCHEDULE_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void SchedulePot_dis(Int16U x, Int16U y)//����λ��
{
Bmp_Decode((Int32U)SCHEDULE_DOT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void RightArrow_dis(Int16U x, Int16U y)//�Ҽ�ͷ -->
{
Bmp_Decode((Int32U)RIGHT_ARROW_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void TimeCol_dis(Int16U x, Int16U y)//ʱ����
{
Bmp_Decode((Int32U)TIME_COL_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void PushPaperTool_dis(Int16U x, Int16U y)//��ֽ��
{
Bmp_Decode((Int32U)PUSH_PAPER_TOOL_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void Cancel_Up_dis(Int16U x, Int16U y)//ȡ��up
{
Bmp_Decode((Int32U)CANCEL_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Cancel_Down_dis(Int16U x, Int16U y)//ȡ��down
{
Bmp_Decode((Int32U)CANCEL_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Enter_Up_dis(Int16U x, Int16U y)//ȷ��up
{
Bmp_Decode((Int32U)ENTER_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Enter_Down_dis(Int16U x, Int16U y)//ȷ��down
{
Bmp_Decode((Int32U)ENTER_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Stop_Up_dis(Int16U x, Int16U y)//ֹͣup
{
Bmp_Decode((Int32U)STOP_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Stop_Down_dis(Int16U x, Int16U y)//ֹͣdown
{
Bmp_Decode((Int32U)STOP_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Run_Up_dis(Int16U x, Int16U y)//����up
{
Bmp_Decode((Int32U)RUN_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Run_Down_dis(Int16U x, Int16U y)//����down
{
Bmp_Decode((Int32U)RUN_DOWN_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void InputSize_dis(Int16U x, Int16U y)//����ߴ�
{
Bmp_Decode((Int32U)INPUT_SIZE_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Remind_dis(Int16U x, Int16U y)//��ʾ��
{
Bmp_Decode((Int32U)REMIND_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void PushKnife_dis(Int16U x, Int16U y)//��ֽ/��
{
Bmp_Decode((Int32U)PUSH_KNIFE_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Position_dis(Int16U x, Int16U y)//λ��
{
Bmp_Decode((Int32U)POSITION_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Order_dis(Int16U x, Int16U y)//���
{
Bmp_Decode((Int32U)ORDER_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void MiddlePage_dis(Int16U x, Int16U y)//�м��ҳ
{
Bmp_Decode((Int32U)MIDDLE_PAGE_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void LeftPage_dis(Int16U x, Int16U y)//��߻�ҳ
{
Bmp_Decode((Int32U)LEFT_PAGE_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void Delete_Up_dis(Int16U x, Int16U y)//ɾ��up
{
Bmp_Decode((Int32U)DELETE_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void DeleteAll_Up_dis(Int16U x, Int16U y)//ȫɾup
{
Bmp_Decode((Int32U)DELETE_ALL_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Pear_dis(Int16U x, Int16U y)//Ѽ��
{
Bmp_Decode((Int32U)PEAR_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Fkey_Up_dis(Int16U x, Int16U y)//F��up
{
Bmp_Decode((Int32U)F_KEY_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void FrontPage_Up_dis(Int16U x, Int16U y)//ǰ��up
{
Bmp_Decode((Int32U)FRONT_PAGE_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void BackPage_Up_dis(Int16U x, Int16U y)//����up
{
Bmp_Decode((Int32U)BACK_PAGE_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void UpArrow_Up_dis(Int16U x, Int16U y)//�ϼ�ͷup
{
Bmp_Decode((Int32U)UP_ARROW_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void DownArrow_Up_dis(Int16U x, Int16U y)//�¼�ͷup
{
Bmp_Decode((Int32U)DOWN_ARROW_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F3plus_Up_dis(Int16U x, Int16U y)//F3++up
{
Bmp_Decode((Int32U)F3_PLUS_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F3clock_Up_dis(Int16U x, Int16U y)//F3ʱ��up
{
Bmp_Decode((Int32U)F3_CLOCK_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F4minus_Up_dis(Int16U x, Int16U y)//F4--up
{
Bmp_Decode((Int32U)F4_MINUS_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F5cut_Up_dis(Int16U x, Int16U y)//F5��up
{
Bmp_Decode((Int32U)F5_CUT_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void PulseDegree_dis(Int16U x, Int16U y)//���嵱��
{
Bmp_Decode((Int32U)PULSE_DEGREE_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void Lock_dis(Int16U x, Int16U y)//��
{
Bmp_Decode((Int32U)LOCK_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void LockKey_dis(Int16U x, Int16U y)//�� Կ��
{
Bmp_Decode((Int32U)LOCK_KEY_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void L_R_Arrow_dis(Int16U x, Int16U y)//���Ҽ�ͷ
{
Bmp_Decode((Int32U)L_R_ARROW_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void FastFWD_Up_dis(Int16U x, Int16U y)//���up
{
Bmp_Decode((Int32U)FAST_FORWD_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void FastBACK_Up_dis(Int16U x, Int16U y)//����up
{
Bmp_Decode((Int32U)FAST_BACK_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F4Wheel0_dis(Int16U x, Int16U y)//F4 �������ֹ�0
{
Bmp_Decode((Int32U)F4_WHEEL0_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void F4Wheel1_dis(Int16U x, Int16U y)//F4 �������ֿ�1
{
Bmp_Decode((Int32U)F4_WHEEL1_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void Wheel0_dis(Int16U x, Int16U y)//���ֹ�0 ָʾ
{
Bmp_Decode((Int32U)WHEEL0_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void Wheel1_dis(Int16U x, Int16U y)//���ֿ�1 ָʾ
{
Bmp_Decode((Int32U)WHEEL1_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void F0ALLCUT_YES_dis(Int16U x, Int16U y)//F0 ������е� ���
{
Bmp_Decode((Int32U)F0_YESALLCUT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F0ALLCUT_NO_dis(Int16U x, Int16U y)//F0 ȡ�����е� ���XXXXXXXXXXX
{
Bmp_Decode((Int32U)F0_NOALLCUT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void F5CUT_YES_dis(Int16U x, Int16U y)//F5 ���һ�� �� ���
{
Bmp_Decode((Int32U)F5_YESCUT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F5CUT_NO_dis(Int16U x, Int16U y)//F5 ȡ��һ�� �� ���XXXXXXXXXXX
{
Bmp_Decode((Int32U)F5_NOCUT_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}
void F5PreCircleButt_Up_dis(Int16U x, Int16U y)//F5ѹֽѭ��button up
{
Bmp_Decode((Int32U)F5_PRE_FLG_BUTT_UP_sdram, x, y, (pInt16U)SDRAM0_BASE_ADDR);
}

void F5Button_dis(Int8U flag)  //F5 һ�� �� ��� ��ť/
{
if((WorkMode==AUTO_MODE)||(WorkMode==PROG_MODE))//�Զ���������
	{
	if(InputTouch_flag==0) //�Ǵ�����
		{
		if(flag==KNIFE_FLAG) //�� ��־
			{
			F5CUT_NO_dis(F5_CUTYES_X, F5_CUTYES_Y);//F5 ȡ��һ�� �� ���
			}
		else
			{
			F5CUT_YES_dis(F5_CUTYES_X, F5_CUTYES_Y);//F5 ���һ�� �� ���
			}
		}
	}
}

void F0Button_dis(Int8U flag)  //F0 ���� �� ��� ��ť//////////////
{
if(WorkMode==AUTO_MODE)//�Զ���������
	{
	if(InputTouch_flag==0) //�Ǵ�����
		{
		if(flag==1) //�� ��־
			{
			F0ALLCUT_NO_dis(F0_CUTYES_X, F0_CUTYES_Y);//F0 ȡ�� ���е� ���
			}
		else
			{
			F0ALLCUT_YES_dis(F0_CUTYES_X, F0_CUTYES_Y);//F0 ��� ���е� ���
			}
		}
	}
}

void CancelCutflagButton_dis(void)  //ȡ����ʾ  �� ��� ��ť
{
Int16U x,y,back_color=0xef9f;
x=F5_CUTYES_X;
y=F5_CUTYES_Y;
GLCD_SetWindow_Fill( x, y, x+215, y+31, back_color, back_color);//ͼ����ʧ
}



void ElectricalWheel_dis(void)  //��������  ����״̬
{
if(MotorType==MOTOR_AC_SERVO)
	{
	if(ElectricWheelOn_flag==0)
		{
		Wheel0_dis(WHEEL_STA_X, WHEEL_STA_Y);
		if(WorkMode==MANUAL_MODE)
			F4Wheel0_dis(F4_WHEEL_X,F4_WHEEL_Y);
		}
	else	
		{
		Wheel1_dis(WHEEL_STA_X, WHEEL_STA_Y);
		if(WorkMode==MANUAL_MODE)
			F4Wheel1_dis(F4_WHEEL_X,F4_WHEEL_Y);
		}
	}
}
void DeleteWheelStus(void)	//��������  ȡ����ʾ
{
Int16U x,y;
Int16U color=0xef9f;
x=WHEEL_STA_X,y=WHEEL_STA_Y;
GLCD_SetWindow_Fill(x,y,x+64,y+64,color,color);//
}

//-----------���� ģʽ�� ��������page  ��ʾ************************
void ProgModePage_dis(void)  //���ģʽ ���ֻ������
{
Int16U x1,y1,x2,y2,color;
color=0xef9f;
x1=RIGHT_ARROW_X,y1=RIGHT_ARROW_Y;
x2=RED_KNIFE_X+25,y2=RIGHT_ARROW_Y+225;
GLCD_SetWindow_Fill(x1,y1,x2,y2,color,color);//�հ��б�
GLCD_SetWindow_Fill(F5_PRE_FLG_X,F5_PRE_FLG_Y,F5_PRE_FLG_X+48,F5_PRE_FLG_Y+48,color,color);//�հ�F5 flag
F1up_dis(F1_X,F1_Y);//F1
F2up_dis(F2_X,F2_Y);
F3up_dis(F3_X,F3_Y);
F4up_dis(F4_X,F4_Y);
Program_dis(PROGRAM_X,PROGRAM_Y);   //���

FrontPage_Up_dis( FRONT_PAGE_X,  FRONT_PAGE_Y);//ǰһҳup
BackPage_Up_dis( BACK_PAGE_X,  BACK_PAGE_Y);//��һҳup
UpArrow_Up_dis( UP_ARROW_X,  UP_ARROW_Y);//�ϼ�ͷup
DownArrow_Up_dis( DOWN_ARROW_X,  DOWN_ARROW_Y);//�¼�ͷup
//color=0x2e3b;
color=0xce79;
GLCD_SetWindow_Fill(STOP_X,STOP_Y,STOP_X+82,STOP_Y+32,color,color);
Delete_Up_dis( DELETE_X, DELETE_Y );//ɾ��up
DeleteAll_Up_dis( DELETE_ALL_X, DELETE_ALL_Y);//ȫɾup
CancelCutflagButton_dis(); //ȡ����ʾ  �� ��� ��ť
DeleteWheelStus();	//��������  ȡ����ʾ
}
void AutoModePage_dis(void) //�Զ�ģʽ ���ֻ�����ʾ
{
Int16U x1,y1,x2,y2,color;
color=0xef9f;
x1=RIGHT_ARROW_X,y1=RIGHT_ARROW_Y;
x2=RED_KNIFE_X+25,y2=RIGHT_ARROW_Y+225;
GLCD_SetWindow_Fill(x1,y1,x2,y2,color,color);//�հ��б�

Auto_dis(AUTO_X, AUTO_Y); //�Զ�ģʽ
F1Ruler_Up_dis(F1_RULER_X, F1_RULER_Y);//F1 ����
F2Tools_Up_dis(F2_TOOLS_X, F2_TOOLS_Y);//F2 ����
F3plus_Up_dis(F3_PLUS_X, F3_PLUS_Y);//F3++
F4minus_Up_dis(F4_MINUS_X, F4_MINUS_Y);//F4--

FrontPage_Up_dis( FRONT_PAGE_X,  FRONT_PAGE_Y);//ǰһҳup
BackPage_Up_dis( BACK_PAGE_X,  BACK_PAGE_Y);//��һҳup
UpArrow_Up_dis( UP_ARROW_X,  UP_ARROW_Y);//�ϼ�ͷup
DownArrow_Up_dis( DOWN_ARROW_X,  DOWN_ARROW_Y);//�¼�ͷup
F5PreCircleButt_Up_dis(F5_PRE_FLG_X,F5_PRE_FLG_Y);
//color=0x2e3b;
color=0xce79;
GLCD_SetWindow_Fill(DELETE_X,DELETE_Y,DELETE_X+180,DELETE_Y+32,color,color);
//Delete_Up_dis( DELETE_X, DELETE_Y );//ɾ��up
//DeleteAll_Up_dis( DELETE_ALL_X, DELETE_ALL_Y);//ȫɾup
Run_Up_dis(RUN_X,RUN_Y);//����up
Stop_Up_dis(STOP_X,STOP_Y);//ֹͣup
ElectricalWheel_dis();  //��������  ����״̬
}

void ManualModePage_dis(void)  //�ֶ�ģʽ
{
Int16U x1,y1,x2,y2,color;
color=0xef9f;
x1=RIGHT_ARROW_X,y1=RIGHT_ARROW_Y;
x2=RED_KNIFE_X+25,y2=RIGHT_ARROW_Y+225;
GLCD_SetWindow_Fill(x1,y1,x2,y2,color,color);//�հ��б�
GLCD_SetWindow_Fill(F5_PRE_FLG_X,F5_PRE_FLG_Y,F5_PRE_FLG_X+48,F5_PRE_FLG_Y+48,color,color);//�հ�F5 flag
x1=FRONT_PAGE_X,y1=UP_ARROW_Y;
x2=DOWN_ARROW_X+50,y2=DOWN_ARROW_Y+50;
GLCD_SetWindow_Fill(x1,y1,x2,y2,color,color);  //���ط����ͷ
FrontPage_Up_dis( MAN_FRONT_PAGE_X,  MAN_FRONT_PAGE_Y);//ǰһҳup
BackPage_Up_dis( MAN_BACK_PAGE_X,  MAN_BACK_PAGE_Y);//��һҳup
FastFWD_Up_dis(MAN_FAST_FWD_X, MAN_FAST_FWD_Y);//���up
FastBACK_Up_dis(MAN_FAST_BACK_X, MAN_FAST_BACK_Y);//����up
Stop_Up_dis(MAN_STOP_X,MAN_STOP_Y);//ֹͣup

//color=0x1b1b;
color=0x9cd3;
F1Ruler_Up_dis(F1_RULER_X, F1_RULER_Y);//F1 ����
F2Tools_Up_dis(F2_TOOLS_X, F2_TOOLS_Y);//F2 ����
F3clock_Up_dis(F3_CLOCK_X,F3_CLOCK_Y);  //F3ʱ��

GLCD_SetWindow_Fill(F4_X,F4_Y,F4_X+48,F4_Y+48,color,color);
//color=0x2e3b;
color=0xce79;
GLCD_SetWindow_Fill(DELETE_X,DELETE_Y,DELETE_X+272,DELETE_Y+32,color,color);
//Stop_Up_dis(STOP_X,STOP_Y);//ֹͣup
ElectricalWheel_dis();  //��������  ����״̬
Manual_dis(MANUAL_X,MANUAL_Y);
CancelCutflagButton_dis(); //ȡ����ʾ  �� ��� ��ť
}

void TeachPage_dis(void)   //ʾ��ģʽ  ҳ��
{
Int16U x1,y1,x2,y2,color;
color=0xef9f;
x1=RIGHT_ARROW_X,y1=RIGHT_ARROW_Y;
x2=RED_KNIFE_X+25,y2=RIGHT_ARROW_Y+225;
GLCD_SetWindow_Fill(x1,y1,x2,y2,color,color);//�հ��б�
GLCD_SetWindow_Fill(F5_PRE_FLG_X,F5_PRE_FLG_Y,F5_PRE_FLG_X+48,F5_PRE_FLG_Y+48,color,color);//�հ�F5 flag

F1up_dis(F1_X,F1_Y);//F1
F2up_dis(F2_X,F2_Y);
F3up_dis(F3_X,F3_Y);
F4up_dis(F4_X,F4_Y);
Teach_dis(TEACH_X,TEACH_Y);   //ʾ��

FrontPage_Up_dis( FRONT_PAGE_X,  FRONT_PAGE_Y);//ǰһҳup
BackPage_Up_dis( BACK_PAGE_X,  BACK_PAGE_Y);//��һҳup
UpArrow_Up_dis( UP_ARROW_X,  UP_ARROW_Y);//�ϼ�ͷup
DownArrow_Up_dis( DOWN_ARROW_X,  DOWN_ARROW_Y);//�¼�ͷup
//color=0x2e3b;
color=0xce79;
GLCD_SetWindow_Fill(STOP_X,STOP_Y,STOP_X+82,STOP_Y+32,color,color);
Delete_Up_dis( DELETE_X, DELETE_Y );//ɾ��up
DeleteAll_Up_dis( DELETE_ALL_X, DELETE_ALL_Y);//ȫɾup
CancelCutflagButton_dis(); //ȡ����ʾ  �� ��� ��ť
DeleteWheelStus();	//��������  ȡ����ʾ
}


//**************************************��� ��
void ProgSet_dis(Int32U size, Int16U x, Int16U y, Int8U set_flag)// �����趨ҳ�� �ߴ���ʾ
{
Int8U num[8],k,int_flag=0;
Int16U back_color=0xef9f;
switch(WorkMode)
	{
	case PROG_LABEL_MODE://���� ��ǩ����		
	case TEACH_LABEL_MODE://���� ��ǩ����		
	case PROG_DIVIDE_MODE://���� �ȷֻ��� 		
	case TEACH_DIVIDE_MODE://���� �ȷֻ��� 		
	//case PROG_PRO_MODE://����  ����ѡ����
	//case AUTO_RULER_MODE:	//��׼ģʽ		
	case AUTO_TOOLS_MODE:// ����  �Զ� -------����ģʽ
	case SELF_TOOLS_MODE:// ����  �Ե� -------����ģʽ
	case MANUAL_TOOLS_MODE:// �ֶ� ����ģʽ
			
		if(((WorkMode==PROG_DIVIDE_MODE)||(WorkMode==TEACH_DIVIDE_MODE))&&(PorgSet_sel==1)) //�ȷ���
			{
			if(PorgSet_sel==1)
				{
				num[0]=size/1000+48;
				num[1]=(size/100)%10+48;
				num[2]=(size/10)%10+48;
				num[3]=size%10+48;
				num[4]=0;
				int_flag=1;
				}
			else
				int_flag=0;
			}	
		else
			{
			int_flag=0;
			}
			//------------------------
		if(int_flag==0)	// ��С��
			{
			num[0]=size/100000;
			num[1]=(size/10000)%10;
			num[2]=(size/1000)%10;
			num[3]=(size/100)%10;
			num[4]='.';
			num[5]=(size/10)%10;
			num[6]=size%10;
			num[7]=0;
			if(Unit!=UNIT_MM)//mm
				{
				num[4]=num[3];
				num[3]='.';
				}
			for(k=0;k<7;k++)
				{
				if(num[k]!='.')
					num[k]+=48;
				}
			}
			break;
	case MANUAL_CLOCK_MODE: //�ֶ� ʱ�� ģʽ
			num[0]=((size>>4)&0x0F)+48;
			num[1]=(size&0x0F)+48;
			num[2]=0;
			break;
	case MANUAL_PASS_MODE://����ģʽ
			num[0]=size/100+48;
			num[1]=(size/10)%10+48;
			num[2]=size%10+48;
			num[3]=0;
			break;
	case MANUAL_SERVO_C_MODE:			//ֱ���ŷ� C ����
			num[0]=size/1000+48;
			num[1]=(size/100)%10+48;
			num[2]=(size/10)%10+48;
			num[3]=size%10+48;
			num[4]=0;
			break;
	}

if(set_flag==1)
   {
   Printf24(num,x,y,back_color,1,BLACK_COLOR);//
   }
else
   {
   Printf24(num,x,y,BLACK_COLOR,1,back_color);//
   }
}

void LabelPage_dis(void)  //��ǩģʽ ������ʾ
{
volatile Int16U x,y,gap;
 x=80,y=200,gap=50;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis(MIDDLE_PAGE_X,MIDDLE_PAGE_Y);//�м��ҳ
PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//��ֽ��
FrontKnife_dis(FRONT_KNIFE_X,FRONT_KNIFE_Y);//��ǰ
CurrentSize_dis(CurrentSize_temp); //��ǰ�ߴ� ������ʾ
CurrUint_dis(Unit);  //��ǰ�ߴ� ��λ
if(BeforeKnifeNo_flag==0)
	FrontKnifeSize_dis(BeforeKnifeSize);

LabelFun_dis(LABEL_FUN_X,LABEL_FUN_Y);//��ǩ����
Label_dis(LABELS_X,LABELS_Y);//��ǩ
Finish_dis(FINISHED_X,FINISHED_Y);//���
F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up�˳�
UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//�ϼ�ͷup
DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//�¼�ͷup
				//���
switch(Language)
	{
	case CHN_HAN:
		Printf24("�ܳ���",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("��ǩ��",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("�ϱߣ�",x,y,BLACK_COLOR,0,0xffff);
			break;
	case ENGLISH:
		Printf24("Total len:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Label��",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Waste��",x,y,BLACK_COLOR,0,0xffff);
			break;
	}	
ProgSet_dis( 0, TOTAL_SIZE_X,  TOTAL_SIZE_Y,1);//
ProgSet_dis( 0, LABEL_SIZE_X,  LABEL_SIZE_Y,0);
ProgSet_dis( 0, WASTE_SIZE_X,  WASTE_SIZE_Y,0);
}

void DividePage_dis(void)  //�ȷ�ģʽ ������ʾ
{
volatile Int16U x,y,gap;
 x=80,y=200,gap=60;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis(MIDDLE_PAGE_X,MIDDLE_PAGE_Y);//�м��ҳ
PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//��ֽ��
FrontKnife_dis(FRONT_KNIFE_X,FRONT_KNIFE_Y);//��ǰ
CurrentSize_dis(CurrentSize_temp); //��ǰ�ߴ� ������ʾ
CurrUint_dis(Unit);  //��ǰ�ߴ� ��λ
if(BeforeKnifeNo_flag==0)
	FrontKnifeSize_dis(BeforeKnifeSize);

DivideFun_dis(DIVIDE_FUN_X,DIVIDE_FUN_Y);//�ȷֹ���
Divide_dis(DIVIDE_X,DIVIDE_Y);//�ȷ�
Finish_dis(FINISHED_X,FINISHED_Y);//���
F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up�˳�
UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//�ϼ�ͷup
DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//�¼�ͷup
//���
switch(Language)
	{
	case CHN_HAN:
		Printf24("�ܳ���",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("�ȷ�����",x,y,BLACK_COLOR,0,0xffff);
			break;
	case ENGLISH:	
		Printf24("Total len��",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Divider��",x,y,BLACK_COLOR,0,0xffff);
			break;
	}


ProgSet_dis( 0, DIVIDE_TOTAL_X,  DIVIDE_TOTAL_Y,1);//
PorgSet_sel=1;
ProgSet_dis( 0, DIVIDE_NUM_X,  DIVIDE_NUM_Y,0);
PorgSet_sel=0;
}

void SelProgPage_dis(void) //���� ѡ�� ������ʾ
{
volatile Int16U x,y;
 x=90,y=115;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis(MIDDLE_PAGE_X,MIDDLE_PAGE_Y);//�м��ҳ
PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//��ֽ��
FrontKnife_dis(FRONT_KNIFE_X,FRONT_KNIFE_Y);//��ǰ
CurrentSize_dis(CurrentSize_temp); //��ǰ�ߴ� ������ʾ
CurrUint_dis(Unit);  //��ǰ�ߴ� ��λ
if(BeforeKnifeNo_flag==0)
	FrontKnifeSize_dis(BeforeKnifeSize);

SelectPro_dis(SELECT_PRO_X,SELECT_PRO_Y); //ѡ�����
Finish_dis(FINISHED_X,FINISHED_Y);//���
F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up�˳�
UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//�ϼ�ͷup
DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//�¼�ͷup
//���
switch(Language)
	{
	case CHN_HAN:
		Printf16("�������      ��һ������",x,y,YELLOW_COLOR,0,0xffff);
			break;
	case ENGLISH:	
		Printf16("Process      First data",x,y,YELLOW_COLOR,0,0xffff);
			break;
	}
GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
switch(Language)
		{
		case CHN_HAN:
				Printf24("������ֵ��Χ        ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case ENGLISH:	
				Printf24("Data range          to",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		}
Printf24("1        500",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
}

//******************************************�� ���Զ� ���Ե� ��
void ParameterPage_dis(Int8U sel, Int8U flag) //���� ������ʾ
{
volatile Int16U x,y,gap;
Int16U front_color,back_color;
gap=30;x=PARA_START_X2+(sel/7)*PARA_COL_WIDE;
Int32U temp;
if(flag==1)
    {
	front_color=0xef9f;
	back_color=BLACK_COLOR;
	}
else
	{
	front_color=BLACK_COLOR;
	back_color=0xef9f;
	}
y=PARA_START_Y+gap*(sel%7);
GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��

switch(sel)
	{
	case 0:
		if(Unit==UNIT_MM)
			{
			temp=FrontLimit;
			}
		else
			{
			temp=FrontLimit*100/254;
			}
		ProgSet_dis(temp,  x,  y,  flag); //ǰ����
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("������ֵ��Χ        ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case ENGLISH:	
					Printf24("Data range          to",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			if(Unit==UNIT_MM)
				Printf24("15       80",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			else
				Printf24("0.6      3.15",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
		break;
	case 1:
		if(Unit==UNIT_MM)
			temp=MiddleLimit;
		else
			temp=MiddleLimit*100/254;
		ProgSet_dis(temp,  x,  y,  flag); //�м���
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("������ֵ��Χ        ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case ENGLISH:	
					Printf24("Data range          to",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			if(Unit==UNIT_MM)
				Printf24("30     	150",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			else
				Printf24("1.19      5.9",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
		break;
	case 2:
		if(Unit==UNIT_MM)
			temp=BackLimit;
		else
			temp=BackLimit*100/254;
		ProgSet_dis(temp,  x,  y,  flag); //����
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("��������ͺ�        ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case ENGLISH:	
					Printf24("Machine type        to",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			if(Unit==UNIT_MM)	
				Printf24("600      2200",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			else
				Printf24("23.63    86.61",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
		break;
	case 3:
		switch(Language)
			{
			case CHN_HAN:
				Printf24("����   ",x,y,front_color,1,back_color); //����
					break;
			case ENGLISH:
				Printf24("English",x,y,front_color,1,back_color); //����
					break;
			}
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("�������,�л�����!           ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Press INSERT,change language!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}	
			}	
		break;
	case 4:
		if(Unit==UNIT_MM)//mm  ��λ
			{
			//GLCD_SetWindow_Fill(x,y,front_color,1,back_color);
			Printf24("mm",x,y,front_color,1,back_color); //
			}
		else
			{
			Printf24("in",x,y,front_color,1,back_color); //
			}
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("�������,�л���Ӣ��!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Press INSERT,change unit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			}	
		break;
	case 5:  //��ǰ��
		if(Unit==UNIT_MM)//mm  ��λ
			temp=Aheader;
		else
			temp=Aheader*100/254;
		ProgSet_dis(temp,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("�������ݷ�Χ        ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range          to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			if(Unit==UNIT_MM)
				Printf24("0       1",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			else
				Printf24("0      0.038",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
		break;
		/*
	case 6://��׼����
		ProgSet_dis(StanDistance,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("ԭ�㿪�ؾ���z�������     ",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Distance from orignal to Z",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			}
		break;*/
	case 6://�Զ���ֽ����
		if(Unit==UNIT_MM)//mm  ��λ
			temp=AutoPushDistance;
		else
			temp=AutoPushDistance*100/254;
		ProgSet_dis(temp,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("��Ч(     -     ),��Ч(0-     )",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Valid(    -   ),Invalid(0-    )",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			if(Unit==UNIT_MM)
				Printf24("11   500            10",REMIND_WINDOW_X+85,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			else
				Printf24("0.44  19            0.4",REMIND_WINDOW_X+82,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);	
			}
		break;
	case 7:  //ѹֽ��Ч ��־
		if(PressValid_flag==0)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("��Ч   ",x,y,front_color,1,back_color); //
						break;
				case ENGLISH:
					Printf24("Invalid",x,y,front_color,1,back_color); //
						break;
				}		
			}
		else 
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("��Ч   ",x,y,front_color,1,back_color); //
						break;
				case ENGLISH:
					Printf24("Valid  ",x,y,front_color,1,back_color); //
						break;
				}	
			}
		if(flag==1)	
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("�������,�л�ѹֽͣ������!     ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Press INSERT,change Press-Stop!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			}
		break;	
		//--------------------------------ֱ���ŷ��趨�ٶ�
	case 8: //	����ٶ�
		if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
			{
			if(Unit==UNIT_MM)//mm  ��λ
				temp=ServoSpeed_order*100;
			else
				temp=ServoSpeed_order*1000;
			ProgSet_dis(temp,  x,  y,  flag);
			}
		else if(MotorType==MOTOR_AC_SERVO)
			{
			if(Unit==UNIT_MM)//mm  ��λ
				temp=AC_MotorSPD*100;
			else
				temp=AC_MotorSPD*1000;
			ProgSet_dis(temp,  x,  y,  flag);
			}
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("�������ݷ�Χ        ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range          to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
				{
				if(MotorType==MOTOR_DC670_SERVO_ZHU)
					Printf24("5     20",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
				else
					Printf24("13     20",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
				}
			else if(MotorType==MOTOR_AC_SERVO)	
				Printf24("0      20",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}	
		break;
	case 9: //	�㶯�ٶ�
		ProgSet_dis(JogSpeed_order*100,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("�������ݷ�Χ        ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range          to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("10     20",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}	
		break;	
	}
}

void ToolsPage_dis(void) //���� ����
{
volatile Int16U x,y,gap,n;
Int16U back_color=0xef9f;
 x=PARA_START_X1,y=PARA_START_Y,gap=30;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis(MIDDLE_PAGE_X,MIDDLE_PAGE_Y);//�м��ҳ
PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//��ֽ��
FrontKnife_dis(FRONT_KNIFE_X,FRONT_KNIFE_Y);//��ǰ
CurrentSize_dis(CurrentSize_temp); //��ǰ�ߴ� ������ʾ
CurrUint_dis(Unit);  //��ǰ�ߴ� ��λ
if(BeforeKnifeNo_flag==0)
	FrontKnifeSize_dis(BeforeKnifeSize);
	
Tools_dis(TOOLS_X, TOOLS_Y);//����
Parameter_dis(PARAMETER_X,PARAMETER_Y);//����
F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up�˳�
L_R_Arrow_dis(L_R_ARROW_X, L_R_ARROW_Y);//���Ҽ�ͷ
UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//�ϼ�ͷup
DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//�¼�ͷup
switch(Language)
	{
	case CHN_HAN:
		Printf24("ǰ����:     ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("�м���:    ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("����:    ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("����:    ",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf24("��λ:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf24("��ǰ��:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		//Printf24("��׼����:   ",x,y,BLACK_COLOR,1,back_color);
		Printf24("��ֽ����:   ",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		Printf24("ѹֽͣ��:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
			{
			Printf24("����ٶ�:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
			Printf24("�㶯�ٶ�:   ",x,y,BLACK_COLOR,1,back_color);
			}
		else if(MotorType==MOTOR_AC_SERVO)
			{
			Printf24("�����ٶ�:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
			}
			break;
	case ENGLISH:	
		Printf24("Front-limit:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Midd-limit:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Back-limit:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Language:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf24("Unit:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf24("Advanced:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Push-distan:",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		Printf24("Press-Stop:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
			{
			Printf24("Max-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
			Printf24("Jog-speed:",x,y,BLACK_COLOR,1,back_color);
			}
		else if(MotorType==MOTOR_AC_SERVO)
			{
			Printf24("Run-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
			}
			break;
	}
switch(MotorType)
	{
	case MOTOR_FREQ_5_SPD_RST:
	case MOTOR_FREQ_3_SPD:
	case MOTOR_FREQ_3_SPD_RST:
			for(n=1;n<=7;n++)
				ParameterPage_dis(n, 0);
			break;
	case MOTOR_DC_SERVO:
	case MOTOR_DC670_SERVO:
	case MOTOR_DC670_SERVO_ZHU:
			for(n=1;n<=9;n++)
				ParameterPage_dis(n, 0);
			break;
	case MOTOR_AC_SERVO:	
			for(n=1;n<=8;n++)
				ParameterPage_dis(n, 0);
			break;
	}		 

ParameterPage_dis(0, 1);
}

void RulerPage_dis(void) //��׼ ����
{
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis(MIDDLE_PAGE_X,MIDDLE_PAGE_Y);//�м��ҳ
PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//��ֽ��
FrontKnife_dis(FRONT_KNIFE_X,FRONT_KNIFE_Y);//��ǰ
CurrentSize_dis(CurrentSize_temp); //��ǰ�ߴ� ������ʾ
CurrUint_dis(Unit);  //��ǰ�ߴ� ��λ
if(BeforeKnifeNo_flag==0)
	FrontKnifeSize_dis(BeforeKnifeSize);
	
Ruler_dis(RULER_X,RULER_Y);//��
F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up�˳�
RulerFun_dis(RULER_FUN_X, RULER_FUN_Y);//��׼����
}

void F3_plus_dis(Int8U flag)
{
if(flag==1)
	Printf24("++",SIZE_WINDOW_X,SIZE_WINDOW_Y,RED_COLOR,1,0xffff);
else
	Printf24("++",SIZE_WINDOW_X,SIZE_WINDOW_Y,0xffff,1,0xffff);
}
void F4_minus_dis(Int8U flag)
{
if(flag==1)
	Printf24("--",SIZE_WINDOW_X,SIZE_WINDOW_Y,RED_COLOR,1,0xffff);
else
	Printf24("--",SIZE_WINDOW_X,SIZE_WINDOW_Y,0xffff,1,0xffff);
}

//�ֶ�********************
void TimeSetSel_dis(Int8U sel, Int8U flag) //ʱ�� �趨 ��ʾ
{
volatile Int16U x,y,gap;
Int16U front_color,back_color;
gap=35;x=PARA_START_X2+20;
if(flag==1)
    {
	front_color=0xef9f;
	back_color=BLACK_COLOR;
	}
else
	{
	front_color=BLACK_COLOR;
	back_color=0xef9f;
	}
y=PARA_START_Y+20+gap*sel;
GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��

switch(sel)
	{
	case 0://��		
		ProgSet_dis(Year,  x,  y,  flag); //
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("������ֵ��Χ        ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range          to",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("0      99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
		break;
	case 1://��
		ProgSet_dis(Month,  x,  y,  flag); //
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("������ֵ��Χ        ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range          to",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("1      12",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
		break;
	case 2://��
		ProgSet_dis(Dom,  x,  y,  flag); //
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("������ֵ��Χ        ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range          to",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("1      31",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
		break;
	case 3://Сʱ
		ProgSet_dis(Hour,  x,  y,  flag); //
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("������ֵ��Χ        ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range          to",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("0      23",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
		break;
	case 4://����
		ProgSet_dis(Min,  x,  y,  flag); //
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("������ֵ��Χ        ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range          to",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("0      59",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
		break;
	
	}
}

void ClockPage_dis(void)  //�ֶ� ʱ��
{
volatile Int16U x,y,gap,n;
 x=130,y=170,gap=35;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis(MIDDLE_PAGE_X,MIDDLE_PAGE_Y);//�м��ҳ
PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//��ֽ��
FrontKnife_dis(FRONT_KNIFE_X,FRONT_KNIFE_Y);//��ǰ
CurrentSize_dis(CurrentSize_temp); //��ǰ�ߴ� ������ʾ
CurrUint_dis(Unit);  //��ǰ�ߴ� ��λ
if(BeforeKnifeNo_flag==0)
	FrontKnifeSize_dis(BeforeKnifeSize);

F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up�˳�
UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//�ϼ�ͷup
DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//�¼�ͷup
Calendar_dis(CALENDA_X,CALENDA_Y); //����
Watch_dis(WATCH_X,WATCH_Y);
switch(Language)
	{
	case CHN_HAN:
		Printf24("��:   20",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("��:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("��:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Сʱ:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("����:",x,y,BLACK_COLOR,0,0xffff);
			break;
	case ENGLISH:	
		Printf24("Year:  20",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Month:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Day:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Hour:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Min:",x,y,BLACK_COLOR,0,0xffff);
			break;
	}
for(n=1;n<5;n++)
	{
	TimeSetSel_dis(n, 0);
	}
TimeSetSel_dis(0, 1);	
}

void PulseDegreePage_dis(void)  //���嵱�� ����ҳ��
{
volatile Int16U x,y,n;
pInt8U pStr;
 x=PULSE_SET_X1,y=PULSE_SET_Y;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis(MIDDLE_PAGE_X,MIDDLE_PAGE_Y);//�м��ҳ
PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//��ֽ��
FrontKnife_dis(FRONT_KNIFE_X,FRONT_KNIFE_Y);//��ǰ
CurrentSize_dis(CurrentSize_temp); //��ǰ�ߴ� ������ʾ
CurrUint_dis(Unit);  //��ǰ�ߴ� ��λ
if(BeforeKnifeNo_flag==0)
	FrontKnifeSize_dis(BeforeKnifeSize);

F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up�˳�
Finish_dis(FINISHED_X,FINISHED_Y);//���
UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//�ϼ�ͷup
DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//�¼�ͷup
PulseDegree_dis(PULSE_DEG_X,  PULSE_DEG_Y);//���嵱��
//���
switch(Language)
	{
	case CHN_HAN:
		Printf16("���嵱��  �������ֱ���  ˿���ݾ�",x,y,0xFc00,0,0xffff);
			break;
	case ENGLISH:	
		Printf16("Pulse-Equ  Resolution   Distance",x,y,0xFc00,0,0xffff);
			break;
	}
x=PULSE_SET_X2;
switch(Language)
	{
	case CHN_HAN:
		Printf16("���嵱��  �������ֱ���  ˿���ݾ�",x,y,0xFc00,0,0xffff);
			break;
	case ENGLISH:	
		Printf16("Pulse-Equ  Resolution   Distance",x,y,0xFc00,0,0xffff);
			break;
	}
x=PULSE_SET_X1+20;
y=PULSE_SET_Y;
for(n=0;n<12;n++)
	{
	if(n==6)
	   {
	   x=PULSE_SET_X2+20;
	   y=PULSE_SET_Y+30;
	   }
	else
	   {
	   y+=30;
	   }   
	Printf24((pInt8U)PulseDegree[n],x,y,0,0,0xffff);
	Printf24((pInt8U)PulseResolut[n],x+80,y,0,0,0xffff);
	Printf24((pInt8U)ScrowResolut[n],x+180,y,0,0,0xffff);
	}
SelPulseDegree_dis(Pulse_degree, 1); //�����趨
GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
switch(Language)
	{
	case CHN_HAN:
		Printf24("���������嵱��!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);	
			break;
	case ENGLISH:	
		Printf24("Enter pulse equivalent!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
			break;
	}
}

void SelPulseDegree_dis(Int8U sel,Int8U flag)
{
volatile Int16U x,y,HH,WW;
Int16U front_color;
HH=26,WW=220;x=PULSE_SET_X1+10;
if(flag==1)
    {
	front_color=RED_COLOR;
	}
else
	{
	front_color=0xef9f;
	}
if(sel>5)
	{
	x=PULSE_SET_X2+10;
	}
sel%=6;
y=PULSE_SET_Y+30*(sel+1);
GLCD_SetWindow( x, y, x+WW, y+HH, front_color);
}

//------------�Ե�
void SelfEnterPage_dis(void)//�Ե�ģʽ ���� ��ʾ
{
Int16U x,y;
Int16U front_color,back_color;
x=SELF_PROMP_X,y=SELF_PROMP_Y;
front_color=RED_COLOR,back_color=0xffff;
CurrentArea_save2(x , y,  x+300, y+120);
GLCD_SetWindow_Fill( x, y, x+300, y+120, BLUE_COLOR, 0xfffff);x+=20,y+=5;
GLCD_SetWindow(SELF_OK_X,SELF_OK_Y,SELF_OK_X+SELF_OK_WIDE, SELF_OK_Y+SELF_OK_HIGH, 0x0);//ȷ�� ��ť
GLCD_SetWindow(SELF_CANCEL_X,SELF_CANCEL_Y,SELF_CANCEL_X+SELF_OK_WIDE, SELF_CANCEL_Y+SELF_OK_HIGH, 0x0);//ȡ�� ��ť
switch(Language)
	{
	case CHN_HAN:
		Printf24("�Ե�ģʽ�߶�Σ�գ���",x,y,front_color,1,back_color);y+=30;
		Printf24("����ȷ���������룡",x,y,front_color,1,back_color);x+=40,y+=50;
		Printf24("ȷ��",x,y,front_color,1,back_color);x+=120;
		Printf24("ȡ��",x,y,front_color,1,back_color);
			break;
	case ENGLISH:	
		Printf24("Auto-Cut mode is so",x,y,front_color,1,back_color);y+=30;
		Printf24("dangerous, press ENTER!",x,y,front_color,1,back_color);x+=40,y+=50;
		Printf24("OK",x,y,front_color,1,back_color);x+=120;
		Printf24("Cancel",x,y,front_color,1,back_color);
			break;
	}

}

void AutoCutLastKnifeLoad_dis(void)  //�Ե�ģʽ �ٴν��� �ָ�֮ǰ ����
{
Int16U x,y;
Int16U front_color,back_color;
x=SELF_PROMP_X,y=SELF_PROMP_Y;
front_color=RED_COLOR,back_color=0xffff;
//CurrentArea_save2(x , y,  x+300, y+120);
GLCD_SetWindow_Fill( x, y, x+300, y+120, BLUE_COLOR, 0xfffff);x+=20,y+=5;
GLCD_SetWindow(SELF_OK_X,SELF_OK_Y,SELF_OK_X+SELF_OK_WIDE, SELF_OK_Y+SELF_OK_HIGH, 0x0);//ȷ�� ��ť
GLCD_SetWindow(SELF_CANCEL_X,SELF_CANCEL_Y,SELF_CANCEL_X+SELF_OK_WIDE, SELF_CANCEL_Y+SELF_OK_HIGH, 0x0);//ȡ�� ��ť
switch(Language)
	{
	case CHN_HAN:
		Printf24("�Ƿ����ִ��֮ǰ��",x,y,front_color,1,back_color);y+=30;
		Printf24("�Ե����裿",x,y,front_color,1,back_color);x+=40,y+=50;
		Printf24("ȷ��",x,y,front_color,1,back_color);x+=120;
		Printf24("ȡ��",x,y,front_color,1,back_color);
			break;
	case ENGLISH:	
		Printf24("Do you continue to last",x,y,front_color,1,back_color);y+=30;
		Printf24("Auto-Cut step?",x,y,front_color,1,back_color);x+=40,y+=50;
		Printf24("OK",x,y,front_color,1,back_color);x+=120;
		Printf24("Cancel",x,y,front_color,1,back_color);
			break;
	}

}

//---------�ŷ� ��������  --
void ServoParameter_dis(Int8U sel, Int8U flag) //���� ������ʾ
{
volatile Int16U x,y,gap;
Int16U front_color,back_color;
gap=30;x=PARA_START_X2+(sel/7)*PARA_COL_WIDE;
Int32U temp;
if(flag==1)
    {
	front_color=0xef9f;
	back_color=BLACK_COLOR;
	}
else
	{
	front_color=BLACK_COLOR;
	back_color=0xef9f;
	}
y=PARA_START_Y+gap*(sel%7);
GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��

switch(sel)
	{
	case 0:  //λ�û�����
		ProgSet_dis(PositRing_Gain,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("�������ݷ�Χ       ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range         to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("1     99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}	
		break;
	case 1://λ�û�΢��
		ProgSet_dis(PositRing_Diff,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("�������ݷ�Χ       ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range         to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("1     99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}	
		break;
	case 2://λ�û�����
		ProgSet_dis(PositRing_Integral,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("�������ݷ�Χ       ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range         to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("1     99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}	
		break;	
	case 3:  //�ٶȻ�����
		ProgSet_dis(SpeedRing_Gain,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("�������ݷ�Χ       ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range         to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("1     99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}	
		break;
	case 4://�ٶȻ�΢��
		ProgSet_dis(SpeedRing_Diff,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("�������ݷ�Χ       ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range         to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("1     99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}	
		break;
	case 5://�ٶȻ�����
		ProgSet_dis(SpeedRing_Integral,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("�������ݷ�Χ       ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range         to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("1     99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}	
		break;	
	case 6://���ٱ�
		ProgSet_dis(SpeedDown_Ratio,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("�������ݷ�Χ       ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data range         to ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("1     3",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}	
		break;		
	case 7://�ݾ�
		ProgSet_dis(Screw_Pitch,  x,  y,  flag);
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("��������ѡ��(           )",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case ENGLISH:	
					Printf24("Data select(            )",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			Printf24("10  ,  12",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}	
		break;		
	}
}	
void Servo_C_DataPage(void)   //ֱ���ŷ� ��C������
{
volatile Int16U x,y,gap,n;
Int16U back_color=0xef9f;;
 x=PARA_START_X1,y=PARA_START_Y,gap=30;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis(MIDDLE_PAGE_X,MIDDLE_PAGE_Y);//�м��ҳ
PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//��ֽ��
FrontKnife_dis(FRONT_KNIFE_X,FRONT_KNIFE_Y);//��ǰ
CurrentSize_dis(CurrentSize_temp); //��ǰ�ߴ� ������ʾ
CurrUint_dis(Unit);  //��ǰ�ߴ� ��λ
if(BeforeKnifeNo_flag==0)
	FrontKnifeSize_dis(BeforeKnifeSize);
	
Tools_dis(TOOLS_X, TOOLS_Y);//����
Parameter_dis(PARAMETER_X,PARAMETER_Y);//����
F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up�˳�
//L_R_Arrow_dis(L_R_ARROW_X, L_R_ARROW_Y);//���Ҽ�ͷ
UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//�ϼ�ͷup
DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//�¼�ͷup
switch(Language)
	{
	case CHN_HAN:
		Printf24("λ������:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("λ��΢��:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("λ�û���:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("�ٶ�����:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("�ٶ�΢��:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("�ٶȻ���:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		
		Printf24("���ٱ�:      ",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		Printf24("�ݾ� :      ",x,y,BLACK_COLOR,1,back_color);
			break;
	case ENGLISH:	
		Printf24("Posit-gain:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Posit-diff:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Posit-inte:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Speed-gain:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Posit-diff:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Posit-inte:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		
		Printf24("Reduc-ratio:",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		Printf24("Screw_Pitch:",x,y,BLACK_COLOR,1,back_color);
			break;
	}
	 
for(n=1;n<8;n++)
	ServoParameter_dis(n, 0);
ServoParameter_dis(0, 1);
}

void PassCodePage_dis(void)  //����ģʽ ��������
{
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis(MIDDLE_PAGE_X,MIDDLE_PAGE_Y);//�м��ҳ
PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//��ֽ��
FrontKnife_dis(FRONT_KNIFE_X,FRONT_KNIFE_Y);//��ǰ
CurrentSize_dis(CurrentSize_temp); //��ǰ�ߴ� ������ʾ
CurrUint_dis(Unit);  //��ǰ�ߴ� ��λ
if(BeforeKnifeNo_flag==0)
	FrontKnifeSize_dis(BeforeKnifeSize);

F2out_Up_dis(F2OUT_X,F2OUT_Y);//F2up�˳�
L_R_Arrow_dis(L_R_ARROW_X, L_R_ARROW_Y);//���Ҽ�ͷ
UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//�ϼ�ͷup
DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//�¼�ͷup
Lock_dis(LOCK_X, LOCK_Y); //��
GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
switch(Language)
	{
	case CHN_HAN:
		Printf24("����������!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case ENGLISH:	
		Printf24("Enter passcode!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	}
	
//Printf24(")",REMIND_WINDOW_X+240,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);	
}
void PassSet_dis(void) //���� ���ý���
{
Int16U x,y,gap;
x=80,y=200,gap=80;
LockKey_dis(LOCK_KEY_X, LOCK_KEY_Y); //�� Կ��
switch(Language)
	{
	case CHN_HAN:
		Printf24("��һ�ιػ�����:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
			break;
	case ENGLISH:	
		Printf24("First valid days:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
			break;
	}
switch(Language)
	{
	case CHN_HAN:
		Printf24("�ڶ��ιػ�����:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
			break;
	case ENGLISH:	
		Printf24("Second valid days:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
			break;
	}
PassDaysSet_dis( 1, 0);
PassDaysSet_dis( 0, 1);
}

void PassDaysSet_dis(Int8U sel,Int8U flag)//�����趨
{
volatile Int16U x,y,gap;
Int16U front_color,back_color;
gap=80;x=150;
if(flag==1)
    {
	front_color=0xef9f;
	back_color=BLACK_COLOR;
	}
else
	{
	front_color=BLACK_COLOR;
	back_color=0xef9f;
	}
y=230+gap*sel;
GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��

switch(sel)
	{
	case 0://��һ�� ����		
		ProgSet_dis(FirstDays,  x,  y,  flag); //
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("��������,���������Ч!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case ENGLISH:	
					Printf24("Enter days,press INSERT",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			}
		x+=36;
		if(FirstDayValid_flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("(��Ч)",x,y,front_color,1,back_color); 
						break;
				case ENGLISH:	
					Printf24("(Valid)  ",x,y,front_color,1,back_color); 
						break;
				}
			}
		else
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("(��Ч)",x,y,front_color,1,back_color); 
						break;
				case ENGLISH:	
					Printf24("(Invalid)",x,y,front_color,1,back_color); 
						break;
				}
			}
		break;
	case 1://�ڶ��� ����
		ProgSet_dis(SecondDays,  x,  y,  flag); //
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("��������,���������Ч!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case ENGLISH:	
					Printf24("Enter days,press INSERT",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			}
		x+=36;
		if(SecondDayValid_flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("(��Ч)",x,y,front_color,1,back_color); 
						break;
				case ENGLISH:	
					Printf24("(Valid)  ",x,y,front_color,1,back_color); 
						break;
				}
			}
		else
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("(��Ч)",x,y,front_color,1,back_color); 
						break;
				case ENGLISH:	
					Printf24("(Invalid)",x,y,front_color,1,back_color); 
						break;
				}
			}
		break;
	}
}

void  PassWord_dis(pInt8U nums,Int8U cou) //����������ʾ
{
Int8U num_temp[8],n=0;

for(n=0;n<cou;n++)
   {
   num_temp[n]=nums[n];
   if(num_temp[n]!='.')
     {
	 num_temp[n]+=48;
	 }
   }
num_temp[cou]=0;
//GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ�����
Printf24(num_temp,PASSCODE_INPUT_X+10,PASSCODE_INPUT_Y+5,BLACK_COLOR,1,0xffff);
}


//*************************ͼƬƴ�� ��ʾ
void WorkPic_dis(void)  //����������ʾ
{
volatile Int16U xp,yp,back_color;
back_color=0xce79;
FirstBack_dis();//�ײ㱳��

TimeCol_dis(TIME_COL_X,TIME_COL_Y);//ʱ����

Schedule_dis(SCHEDULE_X,SCHEDULE_Y);//����
//SchedulePot_dis(SCHEDULE_DOT_X,SCHEDULE_DOT_Y);//���ȿ�
ProgressBar_dis(Knife_sum,Knife_order);  //������ ��ʾ
xp=PROG_X,yp=PROG_Y;
switch(Language)
	{
	case CHN_HAN:
		Printf24(" ����  ",xp,yp,BLACK_COLOR,1,back_color);
			break;
	case ENGLISH:	
		Printf24("Process",xp,yp,BLACK_COLOR,1,back_color);
			break;
	}
xp=STEP_X;//
switch(Language)
	{
	case CHN_HAN:
		Printf24("����",xp,yp,BLACK_COLOR,1,back_color);//
			break;
	case ENGLISH:	
		Printf24("Step",xp,yp,BLACK_COLOR,1,back_color);
			break;
	}
ProNum_dis(Pro_data.pro_num);// �����
StepNum_dis(Knife_sum,Knife_order);// �����  �ܵ���-���

Order_dis(ORDER_X,ORDER_Y);//���
Position_dis(POSITION_X,POSITION_Y);//λ��
PushKnife_dis(PUSH_KNIFE_X,PUSH_KNIFE_Y);//��ֽ������

PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//��ֽ��
CurrentSize_dis(CurrentSize); //��ǰ�ߴ� ������ʾ
CurrUint_dis(Unit);  //��ǰ�ߴ� ��λ

FrontKnife_dis(FRONT_KNIFE_X,FRONT_KNIFE_Y);//��ǰ
/*
RightArrow_dis(RIGHT_ARROW_X,RIGHT_ARROW_Y);//�Ҽ�ͷ

RedKnifeF_dis(RED_KNIFE_X,RED_KNIFE_Y); yp=RED_KNIFE_Y+30; //�쵶

*/
Knife_Up_dis(KNIFE_X,KNIFE_Y);//����
Press_Up_dis(PRESS_X,PRESS_Y);//ѹ��

Red_A_dis(RED_A_X,RED_A_Y);//��A
Red_B_dis(RED_B_X,RED_B_Y);//��B
Hand_IR_dis(HAND_IR_X,HAND_IR_Y);//�ֺ���
//RedLine_dis(RED_LINE_X,RED_LINE_Y);//����
// ElectricalWheel_dis();  //��������  ����״̬

FrontPage_Up_dis( FRONT_PAGE_X,  FRONT_PAGE_Y);//ǰһҳup
BackPage_Up_dis( BACK_PAGE_X,  BACK_PAGE_Y);//��һҳup
UpArrow_Up_dis( UP_ARROW_X,  UP_ARROW_Y);//�ϼ�ͷup
DownArrow_Up_dis( DOWN_ARROW_X,  DOWN_ARROW_Y);//�¼�ͷup

F1up_dis(F1_X,F1_Y);//F1
F2up_dis(F2_X,F2_Y);
F3up_dis(F3_X,F3_Y);
F4up_dis(F4_X,F4_Y);

InputSize_dis(INPUT_SIZE_X,INPUT_SIZE_Y);//����ߴ�
Remind_dis(REMIND_X,REMIND_Y); //��ʾ��
TextWindow_dis();   //��ɫ�ı���
//MiddlePage_dis(MIDDLE_PAGE_X,MIDDLE_PAGE_Y);//�м��ҳ
//LeftPage_dis(LEFT_PAGE_X,LEFT_PAGE_Y);//��߻�ҳ

//Cancel_Up_dis(CANCEL_X,CANCEL_Y);//ȡ��up
//Enter_Up_dis(ENTER_X,ENTER_Y);//ȷ��up
//Run_Up_dis(RUN_X,RUN_Y);//����up
//Stop_Up_dis(STOP_X,STOP_Y);//ֹͣup
Delete_Up_dis( DELETE_X, DELETE_Y );//ɾ��up
DeleteAll_Up_dis( DELETE_ALL_X, DELETE_ALL_Y);//ȫɾup
Fkey_Up_dis( F_KEY_X, F_KEY_Y);//F��up

Program_dis(PROGRAM_X,PROGRAM_Y);   //���
}

void PromptNum_dis(void)  //�������ݷ�Χ ��ʾ
{
Int8U num[15],str1[8],str2[8],i,j;
Int16U x,y;
i=0;
Int32U max,min;
if(Run_flag==1)
	{
	if((WorkMode==AUTO_MODE)||(WorkMode==SELF_CUT_MODE)||(WorkMode==TEACH_MODE))  //�Զ� �Ե� ģʽ
		{
		GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
		switch(Language)
			{
			case CHN_HAN:
				Printf24("������F��ֹͣ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
			case ENGLISH:	
				Printf24("Press 'F' key can stop!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
			}
		}
	}
else
	{
	if(Unit==UNIT_MM)
		{
		num[i++]=Size_MIN/100000;
		num[i++]=(Size_MIN/10000)%10;
		num[i++]=(Size_MIN/1000)%10;
		num[i++]=(Size_MIN/100)%10;

		num[i++]=Size_MAX/100000;
		num[i++]=(Size_MAX/10000)%10;
		num[i++]=(Size_MAX/1000)%10;
		num[i++]=(Size_MAX/100)%10;

		i=0;j=0;
		while(num[i]==0) 
			{
			i++;
			}
		while(i<4)
			{
			str1[j++]=num[i++]+48;
			}
		str1[j]=0;	
		i=4;j=0;	
		while(num[i]==0) 
			{
			i++;
			}
		while(i<8)
			{
			str2[j++]=num[i++]+48;
			}
		str2[j]=0;
		}
	else
		{
		min=Size_MIN*100/254;
		max=Size_MAX*100/254;
		num[i++]=min/100000;
		num[i++]=(min/10000)%10;
		num[i++]=(min/1000)%10;
		num[i++]='.';
		num[i++]=(min/100)%10;
		num[i++]=(min/10)%10;
		num[i++]=min%10;
		
		num[i++]=max/100000;
		num[i++]=(max/10000)%10;
		num[i++]=(max/1000)%10;
		num[i++]='.';
		num[i++]=(max/100)%10;
		num[i++]=(max/10)%10;
		num[i++]=max%10;
		i=0;j=0;
		while(num[i]==0) 
			{
			i++;
			}
		if(i>2)i=2;	
		while(i<7)
			{
			if(i!=3)
				str1[j++]=num[i++]+48;
			else
				str1[j++]=num[i++];
			}
		str1[j]=0;	
		i=7;j=0;	
		while(num[i]==0) 
			{
			i++;
			}
		if(i>9)i=9;		
		while(i<14)
			{
			if(i!=10)
				str2[j++]=num[i++]+48;
			else
				str2[j++]=num[i++];
			}
		str2[j]=0;
		}

	GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
	switch(Language)
		{
		case CHN_HAN:
			Printf24("������ֵ��Χ        ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
				break;
		case ENGLISH:	
			Printf24("Data range          to",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
				break;
		}

	x=REMIND_WINDOW_X+180,y=REMIND_WINDOW_Y+5;
	Printf24(str1,x,y,RED_COLOR,0,0xffff);
	Printf24(str2,x+100,y,RED_COLOR,0,0xffff);
	}

}


void TextWindow_dis(void)  //�ı������
{
GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ�����
PromptNum_dis();
}



void Comment_dis_page(Int8U page)//ע��
{
GLCD_Buffer_Fill(0xffff);
volatile Int16U x,y,gap=10,gap1,gap2;
Int8U start_x=0,start_y=0;
switch(page)
	{
	case 0:
		x=start_x+gap,y=start_y+gap;
		gap1=50,gap2=110;
		F1up_dis(x,y);//F1
		x+=gap1;
		Printf24("��ǩ",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		F2up_dis(x,y);
		x+=gap1;
		Printf24("�ȷ�",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		F3up_dis(x,y);
		x+=gap1;
		Printf24("����",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		F4up_dis(x,y);
		x+=gap1;
		Printf24("��ֽ����",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Finish_dis(x,y);
		x+=gap1;
		Printf24("���",x,y+20,BLACK_COLOR,0,0xffff);
		
		//*********************�ڶ���
		x=start_x+gap;y+=70;
		gap1=50,gap2=110;
		F1Ruler_Up_dis(x,y);
		x+=gap1;
		Printf24("��׼",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		F2Tools_Up_dis(x,y);
		x+=gap1;
		Printf24("����",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		F3clock_Up_dis(x,y);
		x+=gap1;
		Printf24("ʱ��",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		F3plus_Up_dis(x,y);
		x+=gap1;
		Printf24("�Լ�",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		F4minus_Up_dis(x,y);
		x+=gap1;
		Printf24("�Լ�",x,y+20,BLACK_COLOR,0,0xffff);
		
		//*********************������
		x=start_x+gap;y+=70;
		gap1=50,gap2=110;
		F2out_Up_dis(x,y);
		x+=gap1;
		Printf24("�˳�",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		UpArrow_Up_dis(x,y);
		x+=gap1;
		Printf24("����",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		DownArrow_Up_dis(x,y);
		x+=gap1;
		Printf24("����",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		BackPage_Up_dis(x,y);
		x+=gap1;
		Printf24("ǰ��",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		FrontPage_Up_dis(x,y);
		x+=gap1;
		Printf24("����",x,y+20,BLACK_COLOR,0,0xffff);
		
		//*********************������
		x=start_x+gap;y+=70;
		gap1=50,gap2=110;
		L_R_Arrow_dis(x,y);
		x+=gap1;
		Printf24("����",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		Fkey_Up_dis(x,y);
		x+=gap1;
		Printf24("F��",x+20,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		Hand_IR_dis(x,y);
		x+=gap1;
		Printf24("����",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		FrontKnife_dis(x,y);
		x+=gap1;
		Printf24("��ǰ",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		RedKnifeF_dis(x,y);
		x+=gap1;
		Printf24("����־",x,y+20,BLACK_COLOR,0,0xffff);
		
		//*********************������
		x=start_x+gap;y+=70;
		gap1=50,gap2=110;
		Red_A_dis(x,y);
		x+=gap1;
		Printf24("A�ź�",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		Red_B_dis(x,y);
		x+=gap1;
		Printf24("B�ź�",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		PushPaperF_dis(x,y);
		x+=gap1-10;
		Printf24("��ֽ��־",x,y+20,BLACK_COLOR,0,0xffff);
		
		gap1=90,gap2=130;
		x+=gap2;
		Delete_Up_dis(x,y);
		x+=gap1;
		Printf24("ɾ��",x,y+5,BLACK_COLOR,0,0xffff);
		
		gap1=50,gap2=90;
		x+=gap2;
		F4Wheel0_dis(x,y);
		x+=gap1;
		Printf24("���ֹ�",x,y+5,BLACK_COLOR,0,0xffff);
		
		//*********************������
		x=start_x+gap;y+=70;
		gap1=90,gap2=80;
		DeleteAll_Up_dis(x,y);
		x+=gap1;
		Printf24("ȫɾ",x,y+5,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		Run_Up_dis(x,y);
		x+=gap1;
		Printf24("����",x,y+5,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Stop_Up_dis(x,y);
		x+=gap1;
		Printf24("ֹͣ",x,y+5,BLACK_COLOR,0,0xffff);
		
		gap1=140;
		x+=gap2;
		PulseDegree_dis(x,y);
		x+=gap1;
		Printf24("���嵱��",x,y+5,BLACK_COLOR,0,0xffff);
		
		//*********************������
		x=start_x+gap;y+=50;
		gap1=90,gap2=80;
		Wheel0_dis(x,y);
		x+=gap1;
		Printf24("���ֹ�",x,y+5,BLACK_COLOR,0,0xffff);
		/*
		Printf24("���",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Label_dis(x,y);
		x+=gap1;
		Printf24("��ǩ",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;//*********************������
		x=start_x+gap;y+=80;
		Parameter_dis(x,y);
		x+=gap1;
		Printf24("����",x,y+35,BLACK_COLOR,0,0xffff);

		//*********************������
		x=start_x+gap;y+=80;
		Divide_dis(x,y);
		x+=gap1;
		Printf24("�ȷ�",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Teach_dis(x,y);
		x+=gap1;
		Printf24("ʾ��",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Watch_dis(x,y);
		x+=gap1;
		Printf24("ʱ��",x,y+35,BLACK_COLOR,0,0xffff);

		//*********************������
		x=start_x+gap;y+=80;
		Ruler_dis(x,y);
		x+=gap1;
		Printf24("����",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Auto_dis(x,y);
		x+=gap1;
		Printf24("�Զ�",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Manual_dis(x,y);
		x+=gap1;
		Printf24("�ֶ�",x,y+35,BLACK_COLOR,0,0xffff);

		//*********************������
		x=start_x+gap;y+=80;
		AutoKnife_dis(x,y);
		x+=gap1;
		Printf24("�Ե�",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		SelectPro_dis(x,y);
		x+=gap1;
		Printf24("ѡ�����",x,y+35,BLACK_COLOR,0,0xffff);
*/
		//------------ҳ��
		Printf24("1/2 ҳ",350,450,BLACK_COLOR,1,0xffff);

		break;
	case 1:
		x=start_x+gap,y=start_y+gap;
		gap1=50,gap2=110;
		Knife_Up_dis(x,y);//
		x+=gap1;
		Printf24("����",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Knife_Down_dis(x,y);
		x+=gap1;
		Printf24("����",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Press_Up_dis(x,y);
		x+=gap1;
		Printf24("ѹ��",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Press_Down_dis(x,y);
		x+=gap1;
		Printf24("ѹ��",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		F4Wheel1_dis(x,y);
		x+=gap1;
		Printf24("���ֿ�",x,y+5,BLACK_COLOR,0,0xffff);
		//*********************�ڶ���
		x=start_x+gap;y+=70;
		gap1=140,gap2=120;
		Program_dis(x,y);
		x+=gap1;
		Printf24("���ģʽ",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Label_dis(x,y);
		x+=gap1;
		Printf24("��ǩģʽ",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Parameter_dis(x,y);
		x+=gap1;
		Printf24("����ģʽ",x,y+35,BLACK_COLOR,0,0xffff);

		//*********************������
		x=start_x+gap;y+=80;
		Divide_dis(x,y);
		x+=gap1;
		Printf24("�ȷ�ģʽ",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Teach_dis(x,y);
		x+=gap1;
		Printf24("ʾ��ģʽ",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Watch_dis(x,y);
		x+=gap1;
		Printf24("ʱ��ģʽ",x,y+35,BLACK_COLOR,0,0xffff);

		//*********************������
		x=start_x+gap;y+=80;
		Ruler_dis(x,y);
		x+=gap1;
		Printf24("��׼ģʽ",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Auto_dis(x,y);
		x+=gap1;
		Printf24("�Զ�ģʽ",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Manual_dis(x,y);
		x+=gap1;
		Printf24("�ֶ�ģʽ",x,y+35,BLACK_COLOR,0,0xffff);

		//*********************������
		x=start_x+gap;y+=80;
		AutoKnife_dis(x,y);
		x+=gap1;
		Printf24("�Ե�ģʽ",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		SelectPro_dis(x,y);
		x+=gap1;
		Printf24("ѡ�����",x,y+35,BLACK_COLOR,0,0xffff);

		x+=gap2;
		Lock_dis(x,y);
		x+=gap1;
		Printf24("����ģʽ",x,y+35,BLACK_COLOR,0,0xffff);		
		
		//*********************������
		x=start_x+gap;y+=80;
		gap1=90,gap2=80;
		Wheel1_dis(x,y);
		x+=gap1;
		Printf24("���ֿ�",x,y+5,BLACK_COLOR,0,0xffff);

		
		
		//*********************������
		x=start_x+gap;y+=70;
		
		//------------ҳ��
		Printf24("2/2 ҳ",350,450,BLACK_COLOR,1,0xffff);

		break;	
	}

}


void CurrentArea_save1(Int16U x,Int16U y, Int16U Wide,Int16U High)//�ݴ�  ��ǰ���� ����1
{
pInt16U pDis,pBuf;
volatile Int16U h,w;
pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
pBuf=(pInt16U)PIC_DIS_SAVE1;
for(h=0;h<High;h++)
  {
  for(w=0;w<Wide;w++)
    {
	*pBuf++=*pDis++;
	}
	y++;
	pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
  }
}
void CurrentArea_recover1(Int16U x, Int16U y, Int16U Wide,Int16U High)//�ָ�  ��ǰ���� ����1
{
pInt16U pDis,pBuf;
volatile Int16U h,w;
pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
pBuf=(pInt16U)PIC_DIS_SAVE1;
for(h=0;h<High;h++)
  {
  for(w=0;w<Wide;w++)
    {
	*pDis++=*pBuf++;
	}
	y++;
	pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
  }
}

void CurrentArea_save2(Int16U x,Int16U y, Int16U Wide,Int16U High)//�ݴ�  ��ǰ���� ����2
{
pInt16U pDis,pBuf;
volatile Int16U h,w;
pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
pBuf=(pInt16U)PIC_DIS_SAVE2;
for(h=0;h<High;h++)
  {
  for(w=0;w<Wide;w++)
    {
	*pBuf++=*pDis++;
	}
	y++;
	pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
  }
}
void CurrentArea_recover2(Int16U x, Int16U y, Int16U Wide,Int16U High)//�ָ�  ��ǰ���� ����2
{
pInt16U pDis,pBuf;
volatile Int16U h,w;
pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
pBuf=(pInt16U)PIC_DIS_SAVE2;
for(h=0;h<High;h++)
  {
  for(w=0;w<Wide;w++)
    {
	*pDis++=*pBuf++;
	}
	y++;
	pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
  }
}

void CurrentArea_save3(Int16U x,Int16U y, Int16U Wide,Int16U High)//�ݴ�  ��ǰ���� ����3
{
pInt16U pDis,pBuf;
volatile Int16U h,w;
pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
pBuf=(pInt16U)PIC_DIS_SAVE3;
for(h=0;h<High;h++)
  {
  for(w=0;w<Wide;w++)
    {
	*pBuf++=*pDis++;
	}
	y++;
	pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
  }
}
void CurrentArea_recover3(Int16U x, Int16U y, Int16U Wide,Int16U High)//�ָ�  ��ǰ���� ����3
{
pInt16U pDis,pBuf;
volatile Int16U h,w;
pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
pBuf=(pInt16U)PIC_DIS_SAVE3;
for(h=0;h<High;h++)
  {
  for(w=0;w<Wide;w++)
    {
	*pDis++=*pBuf++;
	}
	y++;
	pDis=(pInt16U)(SDRAM0_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
  }
}
//**************************
void CurrentSize_dis(Int32U size)//��ǰ�ߴ�---------------
{
Int8U num[8],k;
Int16U x,y,back_color=0x02FB;
Int8U Virture_size;

x=CURR_SIZE_X;
y=CURR_SIZE_Y;
back_color=0x9CD3;
if(Unit!=UNIT_MM)//inch
	{
	//if(SelfLockEn_flag==1)  //����
		//{
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST:
			case MOTOR_FREQ_3_SPD:
			case MOTOR_FREQ_3_SPD_RST:
				 Virture_size=MARGIN_SIZE;
					break;
			case MOTOR_DC_SERVO:
			case MOTOR_DC670_SERVO:
			case MOTOR_DC670_SERVO_ZHU:
				 Virture_size=DC_VIRTURE_SIZE;
					break;
			}
		if(DcServoGoTarget_flag==0)
			{
			if(CurrentSize>TargetSize)
				{
				if(CurrentSize-TargetSize<Virture_size)
					size=TargetSize_inch;
				else
					size=size*100/254;
				}
			else
				{
				if(TargetSize-CurrentSize<Virture_size)
					size=TargetSize_inch;
				else
					size=size*100/254;	
				}
			}
		else
			{
			size=size*100/254;
			}
		//}
	current_inch=size;
	}

if(size>1000000)
	{
	size=0;  //���-->0
	}
num[0]=size/100000;
num[1]=(size/10000)%10;
num[2]=(size/1000)%10;
num[3]=(size/100)%10;
num[4]='.';
num[5]=(size/10)%10;
num[6]=size%10;
num[7]=0;
if(Unit!=UNIT_MM)//inch
	{
	num[4]=num[3];
	num[3]='.';
	}
for(k=0;k<7;k++)
  {
  if(num[k]!='.')
     num[k]+=48;
  }
//Printf32(num,x,y,0xffff,1,back_color);
//ASCII_Printf(num,224+1,28,56,ASCII_28x56, x,y,0xffff,back_color);
ASCII_Printf(num,192+1,32,48,ASCII_32x48, x,y,0,back_color);
}


void FrontKnifeUint_dis(Int8U unit)  //��ǰ�ߴ� ��λ--------------
{
Int16U x,y,back_color=0x9CD3;
x=FRONT_KNIF_X+160;
y=FRONT_KNIF_Y+5;
GLCD_SetWindow_Fill(x, y, x+40, y+25, back_color, back_color);
if(unit==UNIT_MM)//mm
   {
   Printf24("mm",x,y,BLACK_COLOR,1,back_color);
   }
else
   {
   Printf24("in",x,y,BLACK_COLOR,1,back_color);
   }
}
void CurrUint_dis(Int8U unit)  //��ǰ�ߴ� ��λ-----------------
{/*
Int16U x,y,back_color=0x02FB;
x=CURR_SIZE_X+180;
y=CURR_SIZE_Y+10;
back_color=BLUE_COLOR;
//GLCD_SetWindow_Fill(x, y, x+40, y+25, back_color, back_color);
if(unit==UNIT_MM)//mm
   {
   Printf24("mm",x,y,0xffff,1,back_color);
   }
else
   {
   Printf24("in",x,y,0xffff,1,back_color);
   }*/
FrontKnifeUint_dis(unit);//��ǰ�ߴ� ��λ
GoDirMode=0;
}

void FrontKnifeSize_dis(Int32U size)//��ǰ�ߴ�-----------------
{
Int8U num[8],k;
Int16U x,y,back_color=0xf78a;
x=FRONT_KNIF_X;
y=FRONT_KNIF_Y;
//if(Unit!=UNIT_MM)//inch
//	{
//	if(BeforeKnife_offset_in<1)
//		size=size*100/254;
//	}
num[0]=size/100000;
num[1]=(size/10000)%10;
num[2]=(size/1000)%10;
num[3]=(size/100)%10;
num[4]='.';
num[5]=(size/10)%10;
num[6]=size%10;
num[7]=0;
if(Unit!=UNIT_MM)//inch
	{
	num[4]=num[3];
	num[3]='.';
	}
for(k=0;k<7;k++)
  {
  if(num[k]!='.')
     num[k]+=48;
  }
//Printf24(num,x,y,BLACK_COLOR,1,back_color);
ASCII_Printf(num,108+1,20,36,ASCII_20x36, x,y,0,back_color);
}
void FrontKnifeSize_NOdis(void)
{
Int16U x,y,back_color=0xf78a;
x=FRONT_KNIF_X;
y=FRONT_KNIF_Y;
GLCD_SetWindow_Fill(x-1, y, x+140, y+36, back_color, back_color);
}


void InputNum_dis(pInt8U nums,Int8U cou) //�������  �ߴ�������ʾ
{
Int8U num_temp[8],n=0;

for(n=0;n<cou;n++)
   {
   num_temp[n]=nums[n];
   if((num_temp[n]!='.')&&(num_temp[n]!='-'))
     {
	 num_temp[n]+=48;
	 }
   }
num_temp[cou]=0;
//GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ�����
Printf24(num_temp,SIZE_WINDOW_X+25,SIZE_WINDOW_Y+5,BLACK_COLOR,1,0xffff);
}

void CursorMov_dis(Int8U row, Int8U show_flag)//��ɫ���
{
Int16U x,y,back_color=0xef9f;
if(row>(PAGE_KNIFE-1))
   {
   TableDis_startcol=RIGHT_PAGE_X;
   }
else
   {
   TableDis_startcol=RIGHT_ARROW_X;
   }
x=TableDis_startcol;
y=RIGHT_ARROW_Y+15+(row%PAGE_KNIFE)*45;
if(show_flag==1)//��ʾ
   {
   RightArrow_dis(x,y);
   }
else
   {
   GLCD_SetWindow_Fill( x, y, x+15, y+15, back_color, back_color);//��ʧ
   }
}


void KnifeOrder_dis(Int16U row, Int16U order,Int16U num_color)//-----------------------��ʾһ�����
{
Int8U num[5],k;
Int16U x,y,back_color=0xef9f;
if(row>(PAGE_KNIFE-1))
   {
   TableDis_startcol=RIGHT_PAGE_X;
   }
else
   {
   TableDis_startcol=RIGHT_ARROW_X;
   }
x=TableDis_startcol+18;
y=RIGHT_ARROW_Y+(row%PAGE_KNIFE)*45;

num[0]=order/100;
num[1]=(order/10)%10;
num[2]=order%10;
num[3]=0;
for(k=0;k<3;k++)
  {
  num[k]+=48;
  }
//Printf32(num,x,y,num_color,1,back_color);//���
ASCII_Printf(num,114+1,18,38,ASCII_bold18x38, x,y,num_color,back_color);
}

void KnifeSize_dis(Int16U row,  Int32U Knife_size,Int16U num_color)//--------------��ʾһ���ߴ�
{
Int8U num[8],k;
Int16U x,y,back_color=0xef9f;
Int32U size_inc;
if(row>(PAGE_KNIFE-1))
   {
   TableDis_startcol=RIGHT_PAGE_X;
   }
else
   {
   TableDis_startcol=RIGHT_ARROW_X;
   }  
x=TableDis_startcol+95;
y=RIGHT_ARROW_Y+(row%PAGE_KNIFE)*45;

num[0]=Knife_size/100000;
num[1]=(Knife_size/10000)%10;
num[2]=(Knife_size/1000)%10;
num[3]=(Knife_size/100)%10;
num[4]='.';
num[5]=(Knife_size/10)%10;
num[6]=Knife_size%10;
num[7]=0;
if(Unit!=UNIT_MM)
	{
	num[4]=num[3];
	num[3]='.';
	}
for(k=0;k<7;k++)
	{
	if(num[k]!='.')
		num[k]+=48;
	}
//Printf32(num,x,y,BLACK_COLOR,1,back_color);//�ߴ���ʾ
ASCII_Printf(num,120+1,24,40,ASCII_bold24x40, x,y,num_color,back_color);
}

void PushFlag_dis(Int8U row,  Int8U Knife_flag)//-------һ�� ��ֽ ��־��ʾ
{
Int16U x,y,back_color=0xef9f;
x=RED_KNIFE_X;
y=RIGHT_ARROW_Y+10+row*45;
GLCD_SetWindow_Fill( x, y, x+25, y+25, back_color, back_color);//ͼ����ʧ
switch(Knife_flag)
	{
	case PUSH_FLAG:  //��ֽͼ����ʾ
			PushPaperF_dis(x,y);
			break;
	case KNIFE_FLAG:  //��ͼ��		
			RedKnifeF_dis(x,y);
			break;
	case PRE_AUTO_FLAG:  //�Զ�ѭ��ͼ��		
			AutoRoutePRE_dis(x,y);//k�Զ�ѭ�� ��־
			break;
	}
}

Int8U OneKnifeDataSel_dis(Int16U knife,Int8U row,Int16U num_color)  //һ������ ������ʾ
{
KNIFE_DATA Knife_datas;
GetOneKnife_datas(Pro_data.pro_num, knife , (pInt8U)&Knife_datas);//ȡ��һ�� ����
KnifeOrder_dis(row, knife,num_color);//���
//-----------------����(�ߴ�)���� �ж� 
if((Knife_datas.size<Size_MIN_num)||(Knife_datas.size>Size_MAX_num))
	{
	Knife_datas.size=0;
	Knife_datas.k_flag=0;
	if(Knife_sum>=knife)
		{
		if(knife>1)
			Knife_sum=knife-1;
		else
			Knife_sum=1;
		Knife_sum_before=Knife_sum;
		SaveKnife_sum(Pro_data.pro_num);//���� ���� 
		StepNum_dis(Knife_sum, knife);//�������
		}
	}
if(knife>Knife_sum)	//���һ������ ֮���������� �����
	{
	if(Knife_datas.size>0)
		{
		Knife_datas.size=0;
		Knife_datas.k_flag=0;
		}
	}	
KnifeSize_dis(row,  Knife_datas.size, num_color);//--------------��ʾһ���ߴ�
if(num_color==RED_COLOR)
	F5Button_dis(Knife_datas.k_flag);  //F5 һ�� �� ��� ��ť
return Knife_datas.k_flag;
}

void ProNum_dis(Int16U pro_order) //���������ʾ
{
Int16U x,y,back_color=0x2E3B;
Int8U num[4],k;
back_color=0xce79;//----------
x=PROG_NUM_X,y=PROG_NUM_Y;
num[0]=pro_order/100;
num[1]=(pro_order/10)%10;
num[2]=pro_order%10;
num[3]=0;
for(k=0;k<3;k++)
   {
   num[k]+=48;
   }
Printf24(num,x,y,BLACK_COLOR,1,back_color);//����
}

void StepNum_dis(Int16U step_sum,Int16U step_order) //���������ʾ(�ܵ���-����)
{
Int16U x,y,back_color=0x2E3B;
Int8U num[8],k;
back_color=0xce79;//----------
x=STEP_NUM_X,y=STEP_NUM_Y;
num[0]=step_sum/100;
num[1]=(step_sum/10)%10;
num[2]=step_sum%10;
num[3]='-';
num[4]=step_order/100;
num[5]=(step_order/10)%10;
num[6]=step_order%10;
num[7]=0;
for(k=0;k<7;k++)
   {
   if(k!=3)
     num[k]+=48;
   }
Printf24(num,x,y,BLACK_COLOR,1,back_color);// ����
if(InputTouch_flag==0)  //	 �� ���������� ��
	{
	switch(WorkMode)
		{
		case  PROG_MODE://��̻�����
		case AUTO_MODE://�Զ���������
		case AUTO_PLUS_MODE://�Զ�F3++
		case AUTO_MINUS_MODE://�Զ�F4--
		
		case TEACH_MODE://ʾ�� ģʽ
		case AUTO_TO_SELF_MODE:   //�Զ�-->�Ե����� ģʽ
		case SELF_CUT_MODE:  //�Ե��� ģʽ
		case SELF_PLUS_MODE: //�Ե� F3++
		case SELF_MINUS_MODE://�Ե� F4--
			ProgressBar_dis(step_sum, step_order);//������ ��ʾ
			break;
		}	
	}
}

void StepOrder_dis(Int16U step_order)//(-����)  ������ʾ
{
Int16U x,y,back_color=0x2E3B;
Int8U num[4],k;
back_color=0xce79;//----------
x=STEP_NUM_X+48,y=STEP_NUM_Y;
num[0]=step_order/100;
num[1]=(step_order/10)%10;
num[2]=step_order%10;
num[3]=0;
for(k=0;k<3;k++)
   {
   num[k]+=48;
   }
Printf24(num,x,y,BLACK_COLOR,1,back_color);// ����
if(InputTouch_flag==0)  //	 �� ���������� ��
	{
	switch(WorkMode)
		{
		case  PROG_MODE://��̻�����
		case AUTO_MODE://�Զ���������
		case AUTO_PLUS_MODE://�Զ�F3++
		case AUTO_MINUS_MODE://�Զ�F4--
		
		case TEACH_MODE://ʾ�� ģʽ
		case AUTO_TO_SELF_MODE:   //�Զ�-->�Ե����� ģʽ
		case SELF_CUT_MODE:  //�Ե��� ģʽ
		case SELF_PLUS_MODE: //�Ե� F3++
		case SELF_MINUS_MODE://�Ե� F4--
			ProgressBar_dis(Knife_sum,Knife_order);  //������ ��ʾ
			break;
		}	
	}
}


void MoveForward(void)//ǰ��
{
MotorRun_flag=1;
switch(MotorType)
	{
	case MOTOR_FREQ_5_SPD_RST://----5���� 
		RLOUT3_ON;   //   ���˶Ͽ�
		RLOUT2_OFF;  //   ǰ���պ�
		
		RLOUT5_OFF;  //   ɲ���պ�------------5��
		break;
	case MOTOR_FREQ_3_SPD://----3 ����	
	case MOTOR_FREQ_3_SPD_RST://----3 ����+��λ	
		RLOUT3_OFF;  //   ɲ���պ�
		OOUT2_OFF;  //	ǰ�� �պ�
		OOUT1_ON;  //  ���� �Ͽ�
		
		break;
	}
if(SelfLockEn_flag == 0) //  δ��λ--
	RLOUT1_ON;    // ������жϿ�
else
	{
	if(PressDown_flag == 0)// ѹֽ δ��
		RLOUT1_ON;    // ������жϿ�
	}
CutPermit_flag=0;	
}
void MoveBack(void) //����
{
MotorRun_flag=1;
switch(MotorType)
	{
	case MOTOR_FREQ_5_SPD_RST://----5����
		RLOUT3_OFF;//   ���˱պ�
		RLOUT2_ON;

		RLOUT5_OFF;  //   ɲ���պ�------------5��
		break;
	case MOTOR_FREQ_3_SPD://----3 ����	
	case MOTOR_FREQ_3_SPD_RST://----3 ����+��λ	
		RLOUT3_OFF;  //   ɲ���պ�
		OOUT1_OFF;  //	���� �պ�
		OOUT2_ON;  //  ǰ�� �Ͽ�
		
		break;
	}
if(SelfLockEn_flag == 0) //  δ��λ--
	RLOUT1_ON;    // ������жϿ�
else
	{
	if(PressDown_flag == 0)// ѹֽ δ��
		RLOUT1_ON;    // ������жϿ�
	}
CutPermit_flag=0;		
}

void MoveStop(void)
{
MotorRun_flag=0;
switch(MotorType)
	{
	case MOTOR_FREQ_5_SPD_RST: //----5����
		OOUT1_ON;
		OOUT3_ON;
		OOUT4_ON; 

		RLOUT2_ON;  //   ǰ��
		RLOUT3_ON;//   ����
		if(Wheel_limit==0)
			{
			RLOUT5_ON;  //   ɲ���Ͽ�------------5��
			RLOUT1_OFF;    // �������	
			}
		break;
	case MOTOR_FREQ_3_SPD: //----3 ����	
	case MOTOR_FREQ_3_SPD_RST: //----3 ����+��λ
		if(Wheel_limit==0)
			{
			RLOUT3_ON;  //   ɲ���Ͽ�
			RLOUT1_OFF;    // �������	
			}
		OOUT1_ON;  //	���� �Ͽ�
		OOUT2_ON;  //  ǰ�� �Ͽ�
		
		OOUT3_ON;
		OOUT4_ON;//�ٶȹ���
		break;
	}
// RLOUT1_OFF;    // �������	
MoveSpeed=0;
}

void SetMotorSpeed(Int8U speed_sel)//�趨�ٶ�
{
switch(speed_sel)
	{
	case 1: //����ٶ�
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST://----5 ����
				OOUT1_ON;
				OOUT3_ON;
				OOUT4_OFF;  
					break;
			case MOTOR_FREQ_3_SPD://----3 ����	
			case MOTOR_FREQ_3_SPD_RST://----3 ����+��λ		
				OOUT3_ON;
				OOUT4_OFF; 
					break;
			}
		//RLOUT1_ON;    // ������жϿ�
			break;
	case 2: //�и���
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST://----5 ����
				OOUT1_ON;
				OOUT3_OFF;
				OOUT4_OFF;  
					break;
			case MOTOR_FREQ_3_SPD://----3 ����	
			case MOTOR_FREQ_3_SPD_RST://----3 ����+��λ		
				OOUT3_OFF;
				OOUT4_OFF; 
					break;
			}
		//RLOUT1_ON;    // ������жϿ�
			break;	
	case 3: //����
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST://----5 ����
				OOUT1_OFF;
				OOUT3_OFF;
				OOUT4_ON;  
					break;
			case MOTOR_FREQ_3_SPD://----3 ����	
			case MOTOR_FREQ_3_SPD_RST://----3 ����+��λ		
				OOUT3_OFF;
				OOUT4_OFF; 
				//OOUT3_OFF;
				// OOUT4_ON;
					break;
			}
		//RLOUT1_ON;    // ������жϿ�
			break;
	case 4: //����
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST://----5 ����
				OOUT1_ON;
				OOUT3_OFF;
				OOUT4_ON;  
					break;
			case MOTOR_FREQ_3_SPD://----3 ����	
			case MOTOR_FREQ_3_SPD_RST://----3 ����+��λ		
				OOUT3_OFF;
				OOUT4_ON; 
					break;
			}
		//RLOUT1_ON;    // ������жϿ�
			break;
	case 5://��λ
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST://----5 ����
				OOUT1_OFF;
				OOUT3_ON;
				OOUT4_ON; 
					break;
			//case 1://----3 ����	
			case MOTOR_FREQ_3_SPD_RST://----3 ����+��λ		
				OOUT3_ON;
				OOUT4_ON; 
					break;
			}
		//RLOUT1_ON;    // ������жϿ�
			break;
	}
}

void MoveSpeedCtrl(void)    //
{
Int32U temp;
if(TargetSize>=CurrentSize)
	{  
	temp=TargetSize-CurrentSize;
	if(temp<2500)  //���ٺ���	//���ٺ���
		{
		if(MoveSpeed!=3)
			{
			MoveSpeed=3;//1;
			SetMotorSpeed(MoveSpeed);
			}
		}
	else	// ���ٺ���
	    {
		if(MoveSpeed!=1)
			{
			MoveSpeed=1;
			SetMotorSpeed(MoveSpeed);
			}
		}
	if(Backward_flag==0)
		{
		Forward_flag=0;
		Backward_flag=1;
		MoveBack();  //����
		}
	}
else if(TargetSize<CurrentSize)
	{
	if(TargetSize>=Size_MIN)
		{
		temp=CurrentSize-TargetSize;
		if(Backward_flag==0)
			{
			if(temp>8000)  //80-  ���� ǰ��
				{
				if(MoveSpeed!=1)
					{
					MoveSpeed=1;
					SetMotorSpeed(MoveSpeed);
					}
				if(Forward_flag==0)
					{
					MoveForward();//ǰ��
					Forward_flag=1;
					}
				}
			else
				{
				if(temp>2000) //12-80  �и���
					{
					if(MoveSpeed!=2)
						{
						MoveSpeed=2;
						SetMotorSpeed(MoveSpeed);
						}
					if(Forward_flag==0)
						{
						MoveForward();//ǰ��
						Forward_flag=1;
						}
					}
				else
					{
					if(temp>600) //6-12  ����
						{
						if(MoveSpeed!=3)
							{
							MoveSpeed=3;
							SetMotorSpeed(MoveSpeed);
							}
						if(Forward_flag==0)
							{
							MoveForward();//ǰ��
							Forward_flag=1;
							}
						}
					else
						{
						if(temp>50)//0.5-6 ����
							{
							if(MoveSpeed!=4)
								{
								MoveSpeed=4;
								SetMotorSpeed(MoveSpeed);
								}
							if(Forward_flag==0)
								{
								MoveForward();//ǰ��
								Forward_flag=1;
								}
							}
						else
							{
							if(Run_flag==0)
								{
								if(MoveSpeed!=3)
									{
									MoveSpeed=3;
									SetMotorSpeed(MoveSpeed);
									}
									MoveBack();  //����
									Forward_flag=0;
									Backward_flag=1;
								}
							else
								{
						
								}
							}
						}
					}
				}
			}
		}
	else    //ǰ����  12//50mm�� ����
		{
		temp=CurrentSize-Size_MIN;
		if(temp<1200)
			{
			if(Backward_flag==0)
				{
				if(MoveSpeed<4)
					{
					MoveSpeed=4;
					SetMotorSpeed(MoveSpeed);
					}
				if(Forward_flag==0)
					{
					MoveForward();//ǰ��
					Forward_flag=1;
					}	
				}
			}
		}
	}
}



void SpeedLevelSel_dis(Int8U motor,Int8U set_flag)    //������� ��ʾ
{
Int16U F_color,B_color,x,y,gap;
if(set_flag==1)
	{
	F_color=WHITE_COLOR;
	B_color=BLUE_COLOR;
	}
else
	{
	F_color=BLUE_COLOR;
	B_color=WHITE_COLOR;
	}
x=200,y=150;gap=40;
switch(motor)
	{
	case MOTOR_FREQ_5_SPD_RST://�嵵�ٴ���λ
		switch(Language)
			{
			case CHN_HAN:
				Printf24("1------�嵵�ٴ���λ",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
				Printf24("1------5 gears and rest",x,y,F_color,1,B_color);
				break;
			}	
		break;
	case MOTOR_FREQ_3_SPD://������
		y+=gap;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("2------������",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
				Printf24("2------3 gears",x,y,F_color,1,B_color);
				break;
			}		
		break;
	case MOTOR_FREQ_3_SPD_RST://�����ٴ���λ	
		y+=gap*2;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("3------�����ٴ���λ",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
				Printf24("3------3 gears and rest",x,y,F_color,1,B_color);
				break;
			}
		break;
	case MOTOR_DC_SERVO:	 		//ֱ���ŷ�	
		y+=gap*3;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("4------ֱ���ŷ�",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
				Printf24("4------DC servo",x,y,F_color,1,B_color);
				break;
			}
		break;
	case MOTOR_DC670_SERVO:	 		//ֱ���ŷ�	670
		y+=gap*4;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("5------ֱ���ŷ�670",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
				Printf24("5------DC servo 670",x,y,F_color,1,B_color);
				break;
			}
		break;
	case MOTOR_DC670_SERVO_ZHU:	 		//ֱ���ŷ�	670��
		y+=gap*5;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("6------ֱ���ŷ�670��",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
				Printf24("6------DC servo 670 ZHU",x,y,F_color,1,B_color);
				break;
			}
		break;	
	case MOTOR_AC_SERVO:	 		//�����ŷ�	
		y+=gap*6;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("7------�����ŷ�",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
				Printf24("7------AC servo",x,y,F_color,1,B_color);
				break;
			}
		break;	
	}
}

void NewInput_dis(Int32U size)
{
Int8U num[8],n=0;
num[n++]=size/100000;
num[n++]=(size/10000)%10;
num[n++]=(size/1000)%10;
num[n++]=(size/100)%10;
num[n++]='.';
num[n++]=(size/10)%10;
num[n]=size%10;
if(Unit!=UNIT_MM)//mm
	{
	num[4]=num[3];
	num[3]='.';
	}
for(n=0;n<7;n++)
	{
	if(num[n]!='.')
		{
		num[n]+=48;
		}
	}
num[n]=0;
GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ�����
Printf24(num,SIZE_WINDOW_X+25,SIZE_WINDOW_Y+5,BLACK_COLOR,1,0xffff);
}

void Draw_cross(Int16U x,Int16U y,Int16U color)
{
Int16U x1,y1,len=30,ww=2;
x1=x-15;y1=y;
GLCD_SetWindow_Fill(x1, y1, x1+len, y1+ww, color, color);
x1=x;y1=y-15;
GLCD_SetWindow_Fill(x1, y1, x1+ww, y1+len, color, color);
}

void Button_dis(Int8U b_num,Int8U down_flag) //���� ��ť ��ʾ
{
Int16U butt_color,num_color;
Int16U x,y,gap1,gap2,gap3;
gap1=10,gap2=20,gap3=25;
if(down_flag==1)  //���º�
	{
	butt_color=GREEN_COLOR;
	num_color=RED_COLOR;
	}
else
	{
	butt_color=0x9fff;
	num_color=0;
	}
switch(b_num)
	{
	 case BUTT_INSERT:
			x=BUTT_X5;
			y=BUTT_Y1;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			y+=gap2;
			switch(Language)
				{
				case CHN_HAN:
						x+=gap1;
						Printf24("����",x,y,num_color,0,0xffff);
						break;
				case ENGLISH:
						Printf24(" INSE",x,y,num_color,0,0xffff);
						break;
				}
			break;
	 case BUTT_EXIT:
			x=BUTT_X5;
			y=BUTT_Y2;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			y+=gap2;
			switch(Language)
				{
				case CHN_HAN:
						x+=gap1;
						Printf24("�˳�",x,y,num_color,0,0xffff);
						break;
				case ENGLISH:
						Printf24(" EXIT",x,y,num_color,0,0xffff);
						break;
				}
			break;
	 case BUTT_EQU:
			x=BUTT_X5;
			y=BUTT_Y3;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("=",x,y,num_color,0,0xffff);
			break;
	 case BUTT_ENTER:
			x=BUTT_X5;
			y=BUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			y+=gap2;
			switch(Language)
				{
				case CHN_HAN:
						x+=gap1;
						Printf24("ȷ��",x,y,num_color,0,0xffff);
						break;
				case ENGLISH:
						Printf24(" ENT",x,y,num_color,0,0xffff);
						break;
				}
			break;
	 case BUTT_RUN:
			x=BUTT_X5;
			y=BUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap1;y+=gap2;
			switch(Language)
				{
				case CHN_HAN:
						Printf24("����",x,y,num_color,0,0xffff);
						break;
				case ENGLISH:
						Printf24(" RUN",x,y,num_color,0,0xffff);
						break;
				}
			break;
	 case BUTT_CLEAR:
			x=BUTT_X1;
			y=BUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("C",x,y,num_color,0,0xffff);
			break;
	 case BUTT_DOT:
			x=BUTT_X3;
			y=BUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24(".",x,y,num_color,0,0xffff);
			break;
	 case BUTT_MUL:
			x=BUTT_X4;
			y=BUTT_Y3;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("*",x,y,num_color,0,0xffff);
			break;
	 case BUTT_DIV:
			x=BUTT_X4;
			y=BUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("/",x,y,num_color,0,0xffff);
			break;
	 case BUTT_PLUS:
			x=BUTT_X4;
			y=BUTT_Y1;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("+",x,y,num_color,0,0xffff);
			break;
	 case BUTT_SUB:
			x=BUTT_X4;
			y=BUTT_Y2;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("-",x,y,num_color,0,0xffff);
			break;		
	 case BUTT_0:
			x=BUTT_X2;
			y=BUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("0",x,y,num_color,0,0xffff);
			break;		
	 case BUTT_1:
			x=BUTT_X1;
			y=BUTT_Y1;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("1",x,y,num_color,0,0xffff);
			break;		
	 case BUTT_2:
			x=BUTT_X2;
			y=BUTT_Y1;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("2",x,y,num_color,0,0xffff);
			break;		
	 case BUTT_3:
			x=BUTT_X3;
			y=BUTT_Y1;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("3",x,y,num_color,0,0xffff);
			break;		
	 case BUTT_4:
			x=BUTT_X1;
			y=BUTT_Y2;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("4",x,y,num_color,0,0xffff);
			break;		
	 case BUTT_5:
			x=BUTT_X2;
			y=BUTT_Y2;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("5",x,y,num_color,0,0xffff);
			break;		
	 case BUTT_6:
			x=BUTT_X3;
			y=BUTT_Y2;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("6",x,y,num_color,0,0xffff);
			break;		
	 case BUTT_7:
			x=BUTT_X1;
			y=BUTT_Y3;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("7",x,y,num_color,0,0xffff);
			break;		
	 case BUTT_8:
			x=BUTT_X2;
			y=BUTT_Y3;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("8",x,y,num_color,0,0xffff);
			break;		
	 case BUTT_9:
			x=BUTT_X3;
			y=BUTT_Y3;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE,y+BUTT_HIGH,butt_color,butt_color);
			x+=gap3;y+=gap2;
			Printf24("9",x,y,num_color,0,0xffff);
			break;	
	case BUTT_UP:
			x=BUTT_X6;
			y=BUTT_Y1;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE_ARROW,y+BUTT_HIGH_ARROW,butt_color,butt_color);
			x+=15;y+=BUTT_HIGH+15;
			//Printf24("<",x,y,num_color,0,0xffff);
			GLCD_Triangle_Fill(x,y, x+10,y-15, x+20,y ,num_color,num_color);
			break;	
	case BUTT_DOWN:
			x=BUTT_X6;
			y=BUTT_Y3;
			GLCD_SetWindow_Fill(x,y,x+BUTT_WIDE_ARROW,y+BUTT_HIGH_ARROW,butt_color,butt_color);
			x+=15;y+=BUTT_HIGH-5;
			//Printf24(">",x,y,num_color,0,0xffff);
			GLCD_Triangle_Fill(x,y, x+10,y+15, x+20,y ,num_color,num_color);
			break;		
	}
}

void CalcInputNums_dis(pInt8U nums)//���㹫ʽ  �ı���
{
Int16U x,y,num_color=0;
Int8U i,n;
Int8U Num[24];
i=0;
while((*nums!=0xff)&&(i<24))
	{
	if(*nums<'*')  //  '*'==42(ascii)
		Num[i++]=*nums+48;
	else
		Num[i++]=*nums;
	nums++;
	}
Num[i]=0;
x=CALCUL_TEXT_END-(12*i),y=CALCUL_TEXT_Y+5;
Printf24(Num,x,y,num_color,1,0xffff);	
}

void CalcResultNums_dis(pInt8U nums)//���  �ı���
{
Int16U x,y,num_color=0;
Int8U i,n;
Int8U Num[24];
i=0;
while((*nums!=0xff)&&(i<24))
	{
	if(*nums<'*')  //  '*'==42(ascii)
		Num[i++]=*nums+48;
	else
		Num[i++]=*nums;
	nums++;
	}
Num[i]=0;
x=CALCUL_TEXT_END-10-(12*i),y=CALCUL_RESULT_Y+5;
Printf24(Num,x,y,num_color,1,0xffff);	
}

void ClrCalcNums_text(pInt8U pText,Int8U text_sel) //���������� ���
{
Int8U i;
Int16U L_color=BLUE_COLOR,Fill_color=0xffff;
*pText++=0;
for(i=1;i<24;i++)
	{
	*pText++=0xff;
	}
if(text_sel==CAL_INPUT) //������ �����
	{
	GLCD_SetWindow_Fill(CALCUL_TEXT_X,CALCUL_TEXT_Y,CALCUL_TEXT_X+CALCUL_TEXT_W,CALCUL_TEXT_Y+CALCUL_TEXT_H,L_color,Fill_color);//����������
	}
else   //��� ��
	{
	GLCD_SetWindow_Fill(CALCUL_RESULT_X,CALCUL_RESULT_Y,CALCUL_RESULT_X+CALCUL_RESULT_W,CALCUL_RESULT_Y+CALCUL_RESULT_H,L_color,Fill_color);//�����ʾ��
	}	
}

void Calculator_Window(void)  //������
{
Int8U n=0;
Int16U L_color=BLUE_COLOR,Fill_color=CALCUL_COLOR;
CurrentArea_save3(CALCUL_WIN_X , CALCUL_WIN_Y,  CALCUL_WIDE, CALCUL_HIGH);
GLCD_SetWindow_Fill(CALCUL_WIN_X,CALCUL_WIN_Y,CALCUL_WIN_X+CALCUL_WIDE-1,CALCUL_WIN_Y+CALCUL_HIGH-1 ,L_color,Fill_color);

//��ť��ʾ
while(n<=22)
	{
	if(WorkMode==MANUAL_MODE)  // �ֶ�ģʽ
		{
		if(n==BUTT_ENTER)
			n++;
		}
	else
		{
		if(n==BUTT_RUN)
			n++;
		}
	Button_dis(n++, 0); //���� ��ť ��ʾ
	}
}

void PushResetPrompt_dis(void)  //���� ��ֽ�� ��λ  ��ʾ
{
Int16U L_color,Fill_color;
L_color=BLUE_COLOR,Fill_color=0xffff;
CurrentArea_save3(PUSH_RESET_PROMPT_X1, PUSH_RESET_PROMPT_Y1, PUSH_RESET_PROMPT_WIDE, PUSH_RESET_PROMPT_WIDE);
GLCD_SetWindow_Fill(PUSH_RESET_PROMPT_X1, PUSH_RESET_PROMPT_Y1, PUSH_RESET_PROMPT_X1+PUSH_RESET_PROMPT_WIDE-1, 
					PUSH_RESET_PROMPT_Y1+PUSH_RESET_PROMPT_HIGH-1,L_color,Fill_color);//
switch(Language)
	{
	case CHN_HAN:
		Printf24("��ֽ���Ƿ������!",PUSH_RESET_PROMPT_X1+80,PUSH_RESET_PROMPT_Y1+5,BLACK_COLOR,1,0xffff);
		Printf24("ȷ��",PUSH_RESET_OK_X,PUSH_RESET_OK_Y,BLACK_COLOR,1,0xffff);
		Printf24("ȡ��",PUSH_RESET_CANCEL_X,PUSH_RESET_CANCEL_Y,BLACK_COLOR,1,0xffff);
		break;
	case ENGLISH:	
		Printf24("Whether Paper-Pusher is in the end!",PUSH_RESET_PROMPT_X1+1,PUSH_RESET_PROMPT_Y1+5,BLACK_COLOR,1,0xffff);
		Printf24("OK",PUSH_RESET_OK_X,PUSH_RESET_OK_Y,BLACK_COLOR,1,0xffff);
		Printf24("Cancel",PUSH_RESET_CANCEL_X,PUSH_RESET_CANCEL_Y,BLACK_COLOR,1,0xffff);
		break;
	}	
}

void ProgressBar_dis(Int16U total, Int16U now)  //������ ��ʾ
{
Int8U ratio;
Int16U x1,x2,y1,y2;
Int16U color;
if(now<=total)
	{
	ratio=now*200/total;
	x1=SCHEDULE_DOT_X,x2=x1+12;
	if(1)//(ratio!=ProcessRatio)
		{
		if(ProcessRatio!=0xff)    //���� ��ʼ
			{
			color=0xf78a;
			y1=SCHEDULE_DOT_Y+ProcessRatio;
			y2=y1+12;
			GLCD_SetWindow_Fill(x1,y1, x2,y2 ,color,color);//��� ���ȿ�
			
			}
		//**************
		ProcessRatio=ratio;
		color=0;
		y1=SCHEDULE_DOT_Y+ProcessRatio;
		y2=y1+12;
		GLCD_SetWindow_Fill(x1,y1, x2,y2 ,color,color);//���� ���ȿ�
		}
	}

}

void MoveDirArrow_dis(Int8U dir)
{
Int16U x,y,f_color,b_color;
f_color=RED_COLOR,b_color=0x9CD3;
x=MOV_DIR_X,y=MOV_DIR_Y;
if(dir == 0)//ǰ��
	{
	if(GoDirMode != 1)
		{
		GoDirMode=1;
		GLCD_SetWindow_Fill(x,y,x+20,y+20,b_color,b_color);
		GLCD_Triangle_Fill(x,y, x+19,y, x+10,y+15,f_color,f_color);
		}
	}
else
	{
	if(GoDirMode != 2)
		{
		GoDirMode=2;
		GLCD_SetWindow_Fill(x,y,x+20,y+20,b_color,b_color);
		GLCD_Triangle_Fill(x,y+15, x+19,y+15, x+10,y,f_color,f_color);
		}
	}
}
