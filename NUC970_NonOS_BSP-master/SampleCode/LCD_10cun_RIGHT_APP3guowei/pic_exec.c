
#include "pic_exec.h"
//#include"realtime.h"

#include"bmp.h"
//#include"file.h"
#include"word_lib.h"

#include"servo.h"
#include"chndot.h"
#include"key.h"
#include"port.h"
#include"name_input.h"


Int16U cursor_row;//��� λ��(��)
Int16U  TableDis_startcol;//��ʼ��

Int16U Knife_order; //��ǰ����
Int16U Knife_sum_before;//�ܵ���
Int16U MAX_Knife;//��൶��

//Int16U Process_num;//��ǰ���� ��
//Int16U MaixProcess_num;//��� �����

PROG_SEG Pro_data;//���� �� ��

PROCESS_HEAD OnePro_head;//
PROCESS_HEAD Pro_head_temp;//
KNIFE_DATA OneKnife_data;
START_DAY Start_days;

Int16U ProNumGroup[MAX_PROG+2];
Int16U prog_order;

unsigned char PorgSet_sel;

unsigned char BeforeKnifeNo_flag;

unsigned short WorkMode;
unsigned short WorkMode_temp;

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

const PROCESS_HEAD ProHead_default={{0}, {0}, 0,0,0, 1};
const pInt8U NAME_flag={"name"};

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

Int8U ButtonTouch_mode;
Int16U CodeSensorTime_AB;
Int8U CutPermit_flag;

Int8U ServoPressStop_flag;//�ŷ�ѹֽ ͣ��

Int8U DcServoGoTarget_flag;

Int16U LastAutoKnife_order;//  �Ե� ��ǰһ��
Int8U ReEnterAutoKnife_dis;  //�ٴν����Ե�  ��ʾ

Int8U ACServoDrvErr_flag;
Int8U ACServoAlarmExec_flag;

Int8U ElectricWheelOn_flag; //��������

// Int8U F4Mode_flag;
Int32U current_inch;
Int8U MotorRun_flag;

Int8U InputMode;

Int8U DivideValue_flag;
Int8U DisAllProgMode;

Int8U KnifeSensorMode;//knife press sensor 
Int8U PressSensorMode;

Int32U AirOffDistance;//����������

Int8U AirOffOK_flag;//

Int8U AirOffStart_flag;

Int8U IR_SensorStus;
//-----------------------ƫ�������� ģʽ
Int8U AmendSwitch_flag;
// Int8U AmendModeEnb_flag;
Int8U AmendStartRun_flag;
Int32U AmendSize;
Int8U AmendPlus_flag;

Int8U CutPressRoll_flag;


Int8U PageKf_Size_flag;//ÿҳ����flag
Int8U PageKf_Size;//ÿҳ����
Int8U Kf_Line_HIGH;//�и�

Int8U AmendOver_flag;
Int32U VirtualTargetSizeGap;




//*****************��ȡ�ļ�
void ReadFiles(void)
{
//FileFolderRead("��������.bmp",(unsigned char*)START_PIC_sdram);//����������
FileFolderRead("Power.bmp",(unsigned char*)START_PIC_sdram);//����������

//GLCD_SetWindow_Fill(30,450,600,479,BLACK_COLOR,BLACK_COLOR);//*******************************

FileFolderRead("����.bmp",(unsigned char*)WOEK_BACK_dis);//������
//GLCD_SetWindow_Fill(0,0,799,479,BLACK_COLOR,BLACK_COLOR);//*******************************
//GLCD_Buffer_Fill(0);

FileFolderRead("������.bmp",(unsigned char*)SCHEDULE_sdram);//
FileFolderRead("arrow.bmp",(unsigned char*)CURSOR_sdram);//

FileFolderRead("F1��ǩup.bmp",(unsigned char*)F1_LABELS_UP_sdram);//
FileFolderRead("F2�ȷ�up.bmp",(unsigned char*)F2_DIVIDE_UP_sdram);//
FileFolderRead("F3����up.bmp",(unsigned char*)F3_SELECT_PRO_UP_sdram);//
// FileFolderRead("F4���.bmp",(unsigned char*)F4_SWITCH_UP_sdram);
// FileFolderRead("F5ɾ�����е�up.bmp",(unsigned char*)F5_DELETEALL_UP_sdram);
FileFolderRead("F4��ֽup.bmp",(unsigned char*)F4_PUSH_UP_sdram);//
FileFolderRead("F5��up.bmp",(unsigned char*)F5_CUT_UP_sdram);//
FileFolderRead("F0ȫ��up.bmp",(unsigned char*)F0_ALLCUT_UP_sdram);//

FileFolderRead("ǰ��up.bmp",(unsigned char*)FRONT_PAGE_UP_sdram);//
FileFolderRead("����up.bmp",(unsigned char*)BACK_PAGE_UP_sdram);//
FileFolderRead("�ϼ�ͷup.bmp",(unsigned char*)UP_ARROW_UP_sdram);//
FileFolderRead("�¼�ͷup.bmp",(unsigned char*)DOWN_ARROW_UP_sdram);//
FileFolderRead("ɾ��up.bmp",(unsigned char*)DELETE_UP_sdram);//
FileFolderRead("ȫɾup.bmp",(unsigned char*)DELETE_ALL_UP_sdram);//

FileFolderRead("F1���up.bmp",(unsigned char*)F1_OK_UP_sdram);//
FileFolderRead("F2�˳�up.bmp",(unsigned char*)F2_EXIT_UP_sdram);//
FileFolderRead("���Ҽ�ͷup.bmp",(unsigned char*)L_R_ARROW_sdram);//
FileFolderRead("F2�ȷ���up.bmp",(unsigned char*)F2_DIVNUM_UP_sdram);
FileFolderRead("F2�ȷ���down.bmp",(unsigned char*)F2_DIVNUM_DOWN_sdram);
FileFolderRead("F3�ȷ�ֵup.bmp",(unsigned char*)F3_DIVDATA_UP_sdram);
FileFolderRead("F3�ȷ�ֵdown.bmp",(unsigned char*)F3_DIVDATA_DOWN_sdram);
FileFolderRead("F4�˳�.bmp",(unsigned char*)F4_EXIT_UP_sdram);

FileFolderRead("F1�鿴.bmp",(unsigned char*)F1_LOOK_UP_sdram);
FileFolderRead("F2ʱ������up.bmp",(unsigned char*)F2_BY_TIME_UP_sdram);
FileFolderRead("F2ʱ������down.bmp",(unsigned char*)F2_BY_TIME_DOWN_sdram);
FileFolderRead("F3��������up.bmp",(unsigned char*)F3_BY_NUM_UP_sdram);
FileFolderRead("F3��������down.bmp",(unsigned char*)F3_BY_NUM_DOWN_sdram);
FileFolderRead("F4ɾ��һ������up.bmp",(unsigned char*)F4_DELETE_ONE_PRO_UP_sdram);
FileFolderRead("F5ɾ�����г���up.bmp",(unsigned char*)F5_DELETE_ALL_PRO_UP_sdram);
FileFolderRead("F1��������up.bmp",(unsigned char*)F1_PINYIN_UP_sdram);
FileFolderRead("F1��������down.bmp",(unsigned char*)F1_PINYIN_DOWN_sdram);
FileFolderRead("F2��ĸ����up.bmp",(unsigned char*)F2_CHAR_UP_sdram);
FileFolderRead("F2��ĸ����down.bmp",(unsigned char*)F2_CHAR_DOWN_sdram);
FileFolderRead("F3��������up.bmp",(unsigned char*)F3_NUM_UP_sdram);
FileFolderRead("F3��������down.bmp",(unsigned char*)F3_NUM_DOWN_sdram);
// FileFolderRead("F4�˳�.bmp",(unsigned char*)F4_EXIT_UP_sdram);
FileFolderRead("F6�˳�.bmp",(unsigned char*)F6_EXIT_BUTT_sdram);//
FileFolderRead("ȷ��up.bmp",(unsigned char*)ENTER_BUTT_sdram);	//ok

//------------------------------flag button
// FileFolderRead("F1���水ť.bmp",(unsigned char*)AIR_BED_BUTT_sdram);//
// FileFolderRead("F2��ֽ��ť.bmp",(unsigned char*)SORT_PAPER_BUTT_sdram);//
// FileFolderRead("F3ײֽ��ť.bmp",(unsigned char*)CRASH_PAPER_BUTT_sdram);//
// FileFolderRead("F4��ֽ��ť.bmp",(unsigned char*)PUSH_PAPER_BUTT_sdram);//
// FileFolderRead("F5�쵶��ť.bmp",(unsigned char*)RED_KNIFE_BUTT_sdram);//
// FileFolderRead("F6�˳�.bmp",(unsigned char*)F6_EXIT_BUTT_sdram);//
//------------------------------flag pic
FileFolderRead("�쵶ͼ��.bmp",(unsigned char*)RED_KNIFE_F_sdram);//
FileFolderRead("��ֽͼ��.bmp",(unsigned char*)PUSH_PAPER_F_sdram);//
// FileFolderRead("��ֽflag.bmp",(unsigned char*)SORT_PAPER_F_sdram);//
// FileFolderRead("ײֽflag.bmp",(unsigned char*)CRASH_PAPER_F_sdram);//
// FileFolderRead("����flag.bmp",(unsigned char*)AIR_BED_F_sdram);//

FileFolderRead("F1��׼up.bmp",(unsigned char*)F1_RULER_UP_sdram);//
FileFolderRead("F2����up.bmp",(unsigned char*)F2_PARAMETER_sdram);//
FileFolderRead("F3ʱ��up.bmp",(unsigned char*)F3_CLOCK_UP_sdram);//
FileFolderRead("F3++up.bmp",(unsigned char*)F3_PLUS_UP_sdram);//
FileFolderRead("F4--up.bmp",(unsigned char*)F4_MINUS_UP_sdram);//
FileFolderRead("F4���嵱��up.bmp",(unsigned char*)F4_PULSE_UP_sdram);
FileFolderRead("F4wheel0.bmp",(unsigned char*)F4_WHEEL0_sdram);//
FileFolderRead("F4wheel1.bmp",(unsigned char*)F4_WHEEL1_sdram);//
FileFolderRead("F5wheel0.bmp",(unsigned char*)F5_WHEEL0_sdram);//
FileFolderRead("F5wheel1.bmp",(unsigned char*)F5_WHEEL1_sdram);//
FileFolderRead("F6amend_off.bmp",(unsigned char*)F6_AMEND0_sdram);//
FileFolderRead("F6amend_on.bmp",(unsigned char*)F6_AMEND1_sdram);//
// // // FileFolderRead("���嵱��.bmp",(unsigned char*)PULSE_DEGREE_sdram);//
// // // FileFolderRead("��.bmp",(unsigned char*)LOCK_sdram);//
FileFolderRead("���up.bmp",(unsigned char*)FAST_FORWD_UP_sdram);
FileFolderRead("����up.bmp",(unsigned char*)FAST_BACK_UP_sdram);





// // FileFolderRead("F3��ǩ����up.bmp",(unsigned char*)LABEL_TIME_F3_UP_sdram);//
// // FileFolderRead("F3��ǩ����down.bmp",(unsigned char*)LABEL_TIME_F3_DOWN_sdram);//
// // FileFolderRead("F4��ǩ�ϱ�up.bmp",(unsigned char*)LABEL_DESERT_F4_UP_sdram);//
// // FileFolderRead("F4��ǩ�ϱ�down.bmp",(unsigned char*)LABEL_DESERT_F4_DOWN_sdram);//
// // FileFolderRead("����BIGup.bmp",(unsigned char*)RUN_BIG_BUTT_UP_sdram);
// // FileFolderRead("ֹͣBIGup.bmp",(unsigned char*)STOP_BIG_BUTT_UP_sdram);

FileFolderRead("����.bmp",(unsigned char*)KNIFE_UP_sdram);//
FileFolderRead("����.bmp",(unsigned char*)KNIFE_DOWN_sdram);//


FileFolderRead("ѹ��.bmp",(unsigned char*)PRESS_UP_sdram);//
FileFolderRead("ѹ��.bmp",(unsigned char*)PRESS_DOWN_sdram);//
FileFolderRead("����.bmp",(unsigned char*)IR_LINE_sdram);//
FileFolderRead("�ֺ���.bmp",(unsigned char*)IR_CUT_sdram);//
//--------
FileFolderRead("����BIGup.bmp",(unsigned char*)RUN_UP_sdram);//
FileFolderRead("ֹͣBIGup.bmp",(unsigned char*)STOP_UP_sdram);
FileFolderRead("�ϵ���up.bmp",(unsigned char*)SHIFT_BUTT_UP_sdram);//
FileFolderRead("�ϵ���down.bmp",(unsigned char*)SHIFT_BUTT_DOWN_sdram);//
//------------------------------F1,2,3...sub-mode pic
FileFolderRead("��ǩģʽpic.bmp",(unsigned char*)F1_LABEL_MOD_PIC_sdram);
FileFolderRead("�ȷ���ģʽpic.bmp",(unsigned char*)F2_DIVIDE_MOD_PIC1_sdram);
FileFolderRead("�ȷ�ֵģʽpic.bmp",(unsigned char*)F3_DIVIDE_MOD_PIC2_sdram);
FileFolderRead("��׼ģʽpic.bmp",(unsigned char*)F1_RULER_MOD_PIC_sdram);
FileFolderRead("����ģʽpic.bmp",(unsigned char*)F2_DATAS_MOD_PIC_sdram);
FileFolderRead("ʱ��ģʽpic.bmp",(unsigned char*)F3_CLOCK_MOD_PIC_sdram);
FileFolderRead("����ģʽpic.bmp",(unsigned char*)PASSWORD_MOD_PIC_sdram);

}

void StartPic_dis(void)//����������ʾ
{
  
/*
pInt32U source_Ptr=(pInt32U)malloc(1024);
for(volatile Int32U i=0;i<256;i++)	//1k
	{
	source_Ptr[i]=0xffffffff;
	}
for(volatile Int32U i=0;i<10*1024;i++)//10k//24k
	{
	pInt32U dest_Ptr=(pInt32U)(df_zk_sdram+i*1024);//           0xa0600000  //�ֿ�2M
	memcpy(dest_Ptr,source_Ptr,1024);
	}
free(source_Ptr);
*/

pInt32U dest_Ptr=(pInt32U)df_zk_sdram;//           0xa0600000  //�ֿ�2M
for(volatile Int32U i=0;i<10*1024*256;i++)//10k
	{
	*dest_Ptr++=0xffffffff;
	}

FileRead("�ֿ�_0x20000.FON",(unsigned char *)df_zk_sdram);//
Printf16("Copyright(c)lwcumt-201811,All Rights Reserved.",10,10,RED_COLOR,0,0xffff);

FileFolderRead("Ѽ��.bmp",(unsigned char*)PEAR_sdram);//
switch(Language)
	{
	case CHN_HAN:
		Printf24("�����Լ죬���ݼ���.....��Ҫ6�룬���Եȣ�",40,550,RED_COLOR,1,0xffff);
			break;
	case ENGLISH:	
		Printf24("Computer is self-checking,loading data....",40,430,RED_COLOR,1,0xffff);
		Printf24("Please wait 6 seconds!",40,550,RED_COLOR,1,0xffff);
			break;
	case INDONSIA:	//ӡ��
		Printf24("Self test komputer, loading data....",40,430,RED_COLOR,1,0xffff);
		Printf24("Silahkan tunggu 6 detik!",40,550,RED_COLOR,1,0xffff);
			break;
	case PORTUGAL:	//������
		Printf24("computador de autoteste,carregamento....",40,430,RED_COLOR,1,0xffff);
		Printf24("Por favor, aguarde seis segundo!",40,550,RED_COLOR,1,0xffff);
			break;
	case SPANISH: //������
		Printf24("Computer autotest,los datos se cargan....",40,430,RED_COLOR,1,0xffff);
		Printf24("Por favor, espere 6 segundos!",40,550,RED_COLOR,1,0xffff);
			break;
	}

//FileFolderRead("��������.bmp",(unsigned char*)START_PIC_sdram);//����������
Pear_dis(PEAR_X, PEAR_Y);//Ѽ��
ReadFiles();  //��ȡ ͼ���ļ�
Bmp_Decode((Int32U)START_PIC_sdram, 0, 0, (pInt16U)LCD_VRAM_BASE_ADDR); //��ʾ��������

RLOUT1_OFF;  RLOUT1_1_OFF;    // �������
}

//************************��ʾͼƬ  Сͼ�궨��
void FirstBack_dis(void)//���� ����
{
Bmp_Decode((Int32U)WOEK_BACK_dis, 0, 0, (pInt16U)LCD_VRAM_BASE_ADDR);
//pInt16U pbuf,pdis;
//pbuf=(pInt16U)(WOEK_BACK_dis+4);
//pdis=(pInt16U)LCD_VRAM_BASE_ADDR;
//memcpy(pdis,pbuf,800*480*2); 
}

//*************************ģʽ  ��  ��ʾ***************
void ModeName_dis(Int16U mode)//��ģʽ name+++++++++++
{
//Bmp_Decode((Int32U)PROGRAM_MOD_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
Int16U x,y,back_color,line_color;
//.........................���� ��
back_color=MODE_NAME_COLOR,	line_color=WHITE_COLOR;  //ģʽ���� ��
GLCD_SetWindow_Fill(MODE_NAME_X1,MODE_NAME_Y1,MODE_NAME_X2,MODE_NAME_Y2,back_color,back_color);
x=MODE_NAME_X1+10;y=MODE_NAME_Y1+4;
switch(mode)
	{
	case PROG_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;
				Printf24("���ģʽ",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
				x+=12*5;
				Printf24("Edit mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//ӡ��
				Printf24("Mode pemrograman",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//������
				Printf24("modo de edi??o",x,y,line_color,1,back_color);
				ASCII_Printf("ca",ASCII24_MODE,12,24,PUTAO_ZK24, x+(11*12),y,line_color,back_color);
					break;
			case SPANISH: //������
				Printf24("el modo de edici��",x,y,line_color,1,back_color);
				Printf24("                 n",x,y,line_color,0,back_color);
					break;
			}
			break;
	case AUTO_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;
				Printf24("�Զ�ģʽ",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
				x+=12*5;
				Printf24("Auto mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//ӡ��
				x+=12*2;
				Printf24("Mode otomatis",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//������
				// x+=12*2;
				Printf24("O modo autom��   ",x,y,line_color,1,back_color);
				Printf24("             tico",x,y,line_color,0,back_color);//autom��tico
					break;
			case SPANISH: //������
				Printf24("El modo autom��   ",x,y,line_color,1,back_color);
				Printf24("              tico",x,y,line_color,0,back_color);//autom��tico
					break;
			}
			break;	
	case MANUAL_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;
				Printf24("�ֶ�ģʽ",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
				x+=12*3;	
				Printf24("Manual mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//ӡ��
				x+=12*3;		
				Printf24("Mode manual",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//������
				x+=12*2;		
				Printf24("modo manual",x,y,line_color,1,back_color);
					break;
			case SPANISH: //������
				// x+=12*2;		
				Printf24("El modo manual",x,y,line_color,1,back_color);
					break;
			}	
			break;	
	case TEACH_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;
				Printf24("ʾ��ģʽ",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
				x+=12*5;
				Printf24("Teach mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//ӡ��	
				x+=12*2;
				Printf24("Mode ajarkan",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//������
				x+=12*2;		
				Printf24("Modo Teach",x,y,line_color,1,back_color);
					break;
			case SPANISH: //������
				x+=12*2;		
				Printf24("Modo Teach",x,y,line_color,1,back_color);
					break;
			}
			break;
	case SELF_CUT_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;
				Printf24("�Ե�ģʽ",x,y,line_color,1,back_color);
					break;
			case ENGLISH:	
				x+=12*3;
				Printf24("Auto-Cut mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//ӡ��		
				Printf24("Mode Pemoton-Otomat",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//������
				// x+=12*2;		
				Printf24("Modo Cortar Auto",x,y,line_color,1,back_color);
					break;
			case SPANISH: //������	
				Printf24("corte autom�� ",x,y,line_color,1,back_color);
				Printf24("            tico",x,y,line_color,0,back_color);//autom��tico
					break;
			}	
			break;
	case HELP_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;
				Printf24("����ģʽ",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
				x+=12*5;	
				Printf24("Help mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//ӡ��
				x+=12*2;
				Printf24("Bantuan Mode",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//������
				x+=12*2;		
				Printf24("Modo de Ajuda",x,y,line_color,1,back_color);
					break;
			case SPANISH: //������
				//x+=12*2;		
				Printf24("el modo de ayuda",x,y,line_color,1,back_color);
					break;	
			}	
			break;
	//--------------------------------------------------------------------		
	case PROG_LABEL_MODE:
	case TEACH_LABEL_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;
				Printf24("��ǩģʽ",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
				x+=12*4;	
				Printf24("Label mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//ӡ��	
				x+=12*5;
				Printf24("Tag Modus",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//������
				// x+=12*2;		
				Printf24("O modo etiqueta",x,y,line_color,1,back_color);
					break;
			case SPANISH: //������	
				Printf24("modo de Label",x,y,line_color,1,back_color);
					break;
			}	
			break;
	case PROG_DIVIDE_MODE:
	case TEACH_DIVIDE_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;
				Printf24("�ȷ�ģʽ",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
				x+=12*4;	
				Printf24("Divide mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//ӡ��
				x+=12*2;	
				Printf24("Modus aliquots",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//������
				// x+=12*2;		
				Printf24("modo de Al��",x,y,line_color,1,back_color); // Al��quotas
				Printf24("quotas",x+(11*12),y,line_color,1,back_color);
					break;
			case SPANISH: //������
				Printf24("modo de al��cuotas",x,y,line_color,1,back_color);
					break;
			}	
			break;
	case PROG_PRO_MODE:
	case TEACH_PRO_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;
				Printf24("����ģʽ",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
				x+=12*3;	
				Printf24("Procedure mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//ӡ��	
				x+=12*3;	
				Printf24("Mode Program",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//������
				// x+=12*2;		
				Printf24("Modo de Programa",x,y,line_color,1,back_color);
					break;
			case SPANISH: //������	
				x+=12*3;	
				Printf24("Modo Programa",x,y,line_color,1,back_color);
					break;
			}	
			break;
	case PROG_PRO_MESS_MODE:
	case TEACH_PRO_MESS_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*3;	
				Printf24("������ģʽ",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
				x+=12*3;		
				Printf24("Pro-Name mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//ӡ��	
				Printf24("Mode nama-Program",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//������
				// x+=12*2;		
				Printf24("nome do programa",x,y,line_color,1,back_color);
					break;
			case SPANISH: //������	
				Printf24("nombre del programa",x,y,line_color,1,back_color);
					break;	
			}	
			break;
	case PROG_FLAG_MODE:
	case TEACH_FLAG_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*2;	
				Printf24("����趨ģʽ",x,y,line_color,1,back_color);
					break;
			case ENGLISH:	
				x+=12*2;	
				Printf24("Set Marker mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//ӡ��	
				Printf24("Tandai-Pengatu mode",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//������
				// x+=12*2;		
				Printf24("Modo Mark Set",x,y,line_color,1,back_color);
					break;
			case SPANISH: //������	
				Printf24("Modo Marcos Set",x,y,line_color,1,back_color);
					break;
			}	
			break;
	case AUTO_RULER_MODE:
	case MANUAL_RULER_MODE:
	case SELF_RULER_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;	
				Printf24("��׼ģʽ",x,y,line_color,1,back_color);
					break;
			case ENGLISH:	
				x+=12*2;	
				Printf24("Reference mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//ӡ��
				// x+=12*2;		
				Printf24("Modus referensi",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//������
				// x+=12*2;		
				Printf24("modo Refer��   ",x,y,line_color,1,back_color);	//Refer��ncia
				Printf24("           ncia",x,y,line_color,0,back_color);
					break;
			case SPANISH: //������	
				Printf24("Referencia Modo",x,y,line_color,1,back_color);
					break;
			}
			break;
	case AUTO_TOOLS_MODE:
	case MANUAL_TOOLS_MODE:
	case SELF_TOOLS_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;	
				Printf24("����ģʽ",x,y,line_color,1,back_color);
					break;
			case ENGLISH:	
				x+=12*2;	
				Printf24("Parameter mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//ӡ��	
				// x+=12*2;	
				Printf24("Modus parameter",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//������
				// x+=12*2;		
				Printf24("modo Par metros",x,y,line_color,1,back_color);	//Parametros
				ASCII_Printf("a",ASCII24_MODE,12,24,PUTAO_ZK24_XOR, x+(8*12),y,line_color,back_color);
					break;
			case SPANISH: //������
				Printf24("modo de Par��  ",x,y,line_color,1,back_color);
				Printf24("            metros",x,y,line_color,0,back_color);//Par��metros
					break;
			}	
			break;
	case AUTO_PLUS_MODE:
	case SELF_PLUS_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;	
				Printf24("�Լ�ģʽ",x,y,line_color,1,back_color);
					break;
			case ENGLISH:	
				x+=12*3;	
				Printf24("Auto-Add mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//ӡ��
				x+=12*2;		
				Printf24("Modus meningkat",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//������
				x+=12*2;		
				Printf24("modo add Batch",x,y,line_color,1,back_color);	//
					break;
			case SPANISH: //������
				x+=12*2;		
				Printf24("modo por lotes",x,y,line_color,1,back_color);	//
					break;
			}	
			break;
	case AUTO_MINUS_MODE:
	case SELF_MINUS_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;	
				Printf24("�Լ�ģʽ",x,y,line_color,1,back_color);
					break;
			case ENGLISH:	
				x+=12*3;	
				Printf24("Auto-Sub mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//ӡ��	
				x+=12*3;	
				Printf24("Modus kurang",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//������
				x+=12*2;		
				Printf24("modo Batch Menos",x,y,line_color,1,back_color);	//
					break;
			case SPANISH: //������
				// x+=12*2;		
				Printf24("modo Menos lotes",x,y,line_color,1,back_color);	//
					break;
			}	
			break;
	case MANUAL_CLOCK_MODE:
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;	
				Printf24("ʱ��ģʽ",x,y,line_color,1,back_color);
					break;
			case ENGLISH:	
				x+=12*2;	
				Printf24("Calendar mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//ӡ��
				x+=12*2;		
				Printf24("Kalender Modus",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//������
				x+=12*2;		
				Printf24("Modo tempo",x,y,line_color,1,back_color);	//
					break;
			case SPANISH: //������
				x+=12*2;		
				Printf24("modo de hora",x,y,line_color,1,back_color);	//
					break;
			}	
			break;
	case MANUAL_PULSE_MODE:  //�趨���嵱��
		switch(Language)
			{
			case CHN_HAN:
				x+=12*2;	
				Printf24("���嵱��ģʽ",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
				x+=12*2;		
				Printf24("Pulse-Equ mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//ӡ��	
				Printf24("Mode Pulse setara",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//������
				// x+=12*2;		
				Printf24("pulso equivalente",x,y,line_color,1,back_color);	//
					break;
			case SPANISH: //������
				// x+=12*2;		
				Printf24("equivalente pulso",x,y,line_color,1,back_color);	//
					break;
			}		
			break;
	case MANUAL_SERVO_C_MODE:	//ֱ���ŷ� C ����
		switch(Language)
			{
			case CHN_HAN:
				x+=12*2;	
				Printf24("��C������ģʽ",x,y,line_color,1,back_color);
					break;
			case ENGLISH:	
				x+=12*2;	
				Printf24("Servo 'C' data ",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//ӡ��	
				Printf24("Mode 'C' parameter",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//������
				// x+=12*2;		
				Printf24("par metros Servo",x,y,line_color,1,back_color);	// Parametros
				ASCII_Printf("a",ASCII24_MODE,12,24,PUTAO_ZK24_XOR, x+(3*12),y,line_color,back_color);
					break;
			case SPANISH: //������
				Printf24("par�� ",x,y,line_color,1,back_color);
				Printf24("    metros servo C",x,y,line_color,0,back_color);//par��metros
					break;
			}	
			break;
	case MANUAL_PASS_MODE:  //����
		switch(Language)
			{
			case CHN_HAN:
				x+=12*5;	
				Printf24("����ģʽ",x,y,line_color,1,back_color);
					break;
			case ENGLISH:
				x+=12*3;		
				Printf24("Password mode",x,y,line_color,1,back_color);
					break;
			case INDONSIA:	//ӡ��
				x+=12*2;		
				Printf24("Modus cipher",x,y,line_color,1,back_color);
					break;
			case PORTUGAL:	//������
				// x+=12*2;		
				Printf24("modo de senha",x,y,line_color,1,back_color);	
					break;
			case SPANISH: //������	
				Printf24("modo de contrase?a",x,y,line_color,1,back_color);
				ASCII_Printf("n",ASCII24_MODE,12,24,PUTAO_ZK24_XOR, x+(16*12),y,line_color,back_color);
					break;
			}	
			break;		
	}
}


//==================================ͼƬ����============================================
void Pear_dis(Int16U x, Int16U y)//Ѽ��
{
Bmp_Decode((Int32U)PEAR_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void MiddlePage_dis(void)//�м��ҳ
{
Int16U x1,y1,x2,y2;
Int16U fill_color=TEXT_TAB_BACK_COLOR;
//Bmp_Decode((Int32U)MIDDLE_PAGE_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
x1=MIDDLE_PAGE_X,y1=MIDDLE_PAGE_Y+20;
x2=x1+M_PAGE_WIDE-100,y2=MIDDLE_PAGE_Y+320;
GLCD_SetWindow_Fill(x1,y1,x2,y2, fill_color,fill_color);
// GLCD_SetWindow_Fill(SCHEDULE_X,SCHEDULE_Y,SCHEDULE_X+SCHEDULE_WIDE+0,SCHEDULE_Y+SCHEDULE_HIGH,fill_color,fill_color);  //���� ������
}
//-------------F1,2,3...mode fun pic
void F1LabelFunPic_dis(Int16U x, Int16U y)//F1��ǩģʽpic
{
Bmp_Decode((Int32U)F1_LABEL_MOD_PIC_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F2DivideNumPic_dis(Int16U x, Int16U y)//F2�ȷ���ģʽpic
{
Bmp_Decode((Int32U)F2_DIVIDE_MOD_PIC1_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F3DivideValuePic_dis(Int16U x, Int16U y)//F3�ȷ�ֵģʽpic
{
Bmp_Decode((Int32U)F3_DIVIDE_MOD_PIC2_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}

void F1RulerFunPic_dis(Int16U x, Int16U y)//F1��׼ģʽpic
{
Bmp_Decode((Int32U)F1_RULER_MOD_PIC_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F2DatasFunPic_dis(Int16U x, Int16U y)//F2����ģʽpic
{
Bmp_Decode((Int32U)F2_DATAS_MOD_PIC_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F3ClockFunPic_dis(Int16U x, Int16U y)//F3����ģʽpic
{
Bmp_Decode((Int32U)F3_CLOCK_MOD_PIC_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void PsswordFunPic_dis(Int16U x,Int16U y)//���빦��ģʽpic
{
Bmp_Decode((Int32U)PASSWORD_MOD_PIC_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}










//-----***************��ģʽ 5
// void ProgramIconUp_dis(Int16U x,Int16U y)//���up
// {
// Bmp_Decode((Int32U)PROGRAM_MOD_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
// }
// void ProgramIconDown_dis(Int16U x,Int16U y)//���down
// {
// Bmp_Decode((Int32U)PROGRAM_MOD_DOWN_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
// }
// void ManualIconUp_dis(Int16U x,Int16U y)//�ֶ�up
// {
// Bmp_Decode((Int32U)MANUAL_MOD_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
// }
// void ManualIconDown_dis(Int16U x,Int16U y)//�ֶ�down
// {
// Bmp_Decode((Int32U)MANUAL_MOD_DOWN_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
// }
// void AutoIconUp_dis(Int16U x,Int16U y)//�Զ�up
// {
// Bmp_Decode((Int32U)AUTO_MOD_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
// }
// void AutoIconDown_dis(Int16U x,Int16U y)//�Զ�down
// {
// Bmp_Decode((Int32U)AUTO_MOD_DOWN_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
// }
// void AutoCutIconUp_dis(Int16U x,Int16U y)//�Ե�up
// {
// Bmp_Decode((Int32U)AUTO_CUT_MOD_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
// }
// void AutoCutIconDown_dis(Int16U x,Int16U y)//�Ե�down
// {
// Bmp_Decode((Int32U)AUTO_CUT_MOD_DOWN_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
// }
// void TeachIconUp_dis(Int16U x,Int16U y)//ʾ��up
// {
// Bmp_Decode((Int32U)TEACH_MOD_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
// }
// void TeachIconDown_dis(Int16U x,Int16U y)//ʾ��down
// {
// Bmp_Decode((Int32U)TEACH_MOD_DOWN_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
// }
//*****************F1,F2,F3,....Icon
void F1LabelIconUp_dis(Int16U x,Int16U y)//F1��ǩup
{
Bmp_Decode((Int32U)F1_LABELS_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F2DivideIconUp_dis(Int16U x,Int16U y)//F2�ȷ�up
{
Bmp_Decode((Int32U)F2_DIVIDE_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F3ProjectIconUp_dis(Int16U x,Int16U y)//F3����up
{
Bmp_Decode((Int32U)F3_SELECT_PRO_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
// void F4SwitchIconUp_dis(Int16U x,Int16U y)//�л���ťup
// {
// Bmp_Decode((Int32U)F4_SWITCH_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
// }
// void F5DeleteAllKnifeIconUp_dis(Int16U x,Int16U y)//ɾ�����е� ����F5
// {
// Bmp_Decode((Int32U)F5_DELETEALL_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
// }
void F4PushIconUp_dis(Int16U x, Int16U y)//F4up
{
Bmp_Decode((Int32U)F4_PUSH_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F1OkIconUp_dis(Int16U x,Int16U y)//F1���
{
Bmp_Decode((Int32U)F1_OK_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F2ExitIconUp_dis(Int16U x,Int16U y)//F2�˳�up
{
Bmp_Decode((Int32U)F2_EXIT_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void L_R_Arrow_dis(Int16U x, Int16U y)//���Ҽ�ͷ
{
Bmp_Decode((Int32U)L_R_ARROW_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F2DivNumIconUp_dis(Int16U x,Int16U y)//F2�ȷ���up
{
Bmp_Decode((Int32U)F2_DIVNUM_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F2DivNumIconDown_dis(Int16U x,Int16U y)//F2�ȷ���down
{
Bmp_Decode((Int32U)F2_DIVNUM_DOWN_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F3DivDataIconUp_dis(Int16U x,Int16U y)//F3�ȷ�ֵup
{
Bmp_Decode((Int32U)F3_DIVDATA_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F3DivDataIconDown_dis(Int16U x,Int16U y)//F3�ȷ�ֵdown
{
Bmp_Decode((Int32U)F3_DIVDATA_DOWN_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}

//--------pinyin--
void F1ShowMessIconUp_dis(Int16U x,Int16U y)//F1 �鿴mess
{
Bmp_Decode((Int32U)F1_LOOK_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F2ByTimeIconUp_dis(Int16U x,Int16U y)//F2 ��ʱ������up
{
Bmp_Decode((Int32U)F2_BY_TIME_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F2ByTimeIconDown_dis(Int16U x,Int16U y)//F2 ��ʱ������down
{
Bmp_Decode((Int32U)F2_BY_TIME_DOWN_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F3ByNumIconUp_dis(Int16U x,Int16U y)//F3 ���������up
{
Bmp_Decode((Int32U)F3_BY_NUM_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F3ByNumIconDown_dis(Int16U x,Int16U y)//F3 ���������down
{
Bmp_Decode((Int32U)F3_BY_NUM_DOWN_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F4DeleteOneProIconUp_dis(Int16U x,Int16U y)//F4ɾ��һ��pro
{
Bmp_Decode((Int32U)F4_DELETE_ONE_PRO_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F5DeleteAllProIconUp_dis(Int16U x,Int16U y)//F5ɾ������pro
{
Bmp_Decode((Int32U)F5_DELETE_ALL_PRO_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F1PinyinIconUp_dis(Int16U x,Int16U y)//F1ƴ������up
{
Bmp_Decode((Int32U)F1_PINYIN_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F1PinyinIconDown_dis(Int16U x,Int16U y)//F1ƴ������down
{
Bmp_Decode((Int32U)F1_PINYIN_DOWN_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F2CharIconUp_dis(Int16U x,Int16U y)//F2��ĸ����up
{
Bmp_Decode((Int32U)F2_CHAR_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F2CharIconDown_dis(Int16U x,Int16U y)//F2��ĸ����down
{
Bmp_Decode((Int32U)F2_CHAR_DOWN_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F3NumIconUp_dis(Int16U x,Int16U y)//F3��������up
{
Bmp_Decode((Int32U)F3_NUM_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F3NumIconDown_dis(Int16U x,Int16U y)//F3��������down
{
Bmp_Decode((Int32U)F3_NUM_DOWN_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F4ExitIconUp_dis(Int16U x,Int16U y)//F4�˳�
{
Bmp_Decode((Int32U)F4_EXIT_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F6ExitButtUp_dis(Int16U x, Int16U y)//F6Exit butt 
{
Bmp_Decode((Int32U)F6_EXIT_BUTT_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void EnterButtUp_dis(Int16U x, Int16U y)//OK butt ȷ��
{
Bmp_Decode((Int32U)ENTER_BUTT_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
//--------------------
void F1RulerIconUp_dis(Int16U x,Int16U y)//��׼F1
{
Bmp_Decode((Int32U)F1_RULER_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F2ParamaterIconUp_dis(Int16U x,Int16U y)//F2����
{
Bmp_Decode((Int32U)F2_PARAMETER_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F3ClockIconUp_dis(Int16U x,Int16U y)//F3ʱ��
{
Bmp_Decode((Int32U)F3_CLOCK_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F3AddIconUp_dis(Int16U x,Int16U y)//F3++up
{
Bmp_Decode((Int32U)F3_PLUS_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F4SubIconUp_dis(Int16U x,Int16U y)//F4--up
{
Bmp_Decode((Int32U)F4_MINUS_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F4PulseSetIconUp_dis(Int16U x,Int16U y)//F4���嵱��
{
Bmp_Decode((Int32U)F4_PULSE_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F5CutIcon_Up_dis(Int16U x, Int16U y)//F5��up
{
Bmp_Decode((Int32U)F5_CUT_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F0CutAllIcon_Up_dis(Int16U x, Int16U y)//F0ȫ��up
{
Bmp_Decode((Int32U)F0_ALLCUT_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
//**********
void Knife_Up_dis(Int16U x, Int16U y)//����
{
Bmp_Decode((Int32U)KNIFE_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void Knife_Down_dis(Int16U x, Int16U y)//����
{
Bmp_Decode((Int32U)KNIFE_DOWN_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void Press_Up_dis(Int16U x, Int16U y)//ѹ��
{
Bmp_Decode((Int32U)PRESS_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void Press_Down_dis(Int16U x, Int16U y)//ѹ��
{
Bmp_Decode((Int32U)PRESS_DOWN_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}

void IR_LINE_dis(Int16U x, Int16U y)//������
{
Bmp_Decode((Int32U)IR_LINE_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void IR_CUT_dis(Int16U x, Int16U y)//����Ͽ�
{
Bmp_Decode((Int32U)IR_CUT_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void RightArrow_dis(Int16U x,Int16U y)//�Ҽ�ͷ -->
{
Bmp_Decode((Int32U)CURSOR_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void Schedule_dis(Int16U x, Int16U y)//����
{
Bmp_Decode((Int32U)SCHEDULE_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}

//---------------------��� ͼƬ
void RedKnifeF_dis(Int16U x, Int16U y)//�쵶 ��־
{
Bmp_Decode((Int32U)RED_KNIFE_F_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void PushPaperF_dis(Int16U x, Int16U y)//��ֽ ��־
{
Bmp_Decode((Int32U)PUSH_PAPER_F_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
// void SortPaperF_dis(Int16U x, Int16U y)//��ֽ ��־
// {
// Bmp_Decode((Int32U)SORT_PAPER_F_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
// }
// void CrashPaperF_dis(Int16U x, Int16U y)//ײֽ ��־
// {
// Bmp_Decode((Int32U)CRASH_PAPER_F_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
// }
// void AirBedF_dis(Int16U x, Int16U y)//���� ��־
// {
// Bmp_Decode((Int32U)AIR_BED_F_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
// }
//---------button
// void F5RedKnifeButt_dis(Int16U x, Int16U y)//F5�쵶butt ��־
// {
// Bmp_Decode((Int32U)RED_KNIFE_BUTT_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
// }
// void F4PushPaperButt_dis(Int16U x, Int16U y)//F4��ֽbutt ��־
// {
// Bmp_Decode((Int32U)PUSH_PAPER_BUTT_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
// }
// void F2SortPaperButt_dis(Int16U x, Int16U y)//F2��ֽbutt ��־
// {
// Bmp_Decode((Int32U)SORT_PAPER_BUTT_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
// }
// void F3CrashPaperButt_dis(Int16U x, Int16U y)//F3ײֽbutt ��־
// {
// Bmp_Decode((Int32U)CRASH_PAPER_BUTT_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
// }
// void F1AirBedButt_dis(Int16U x, Int16U y)//F1����butt ��־
// {
// Bmp_Decode((Int32U)AIR_BED_BUTT_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
// }




//---����ͼƬ
void MachinePic_dis(Int16U x, Int16U y)//�ֶ�ģʽ�� ����ͼƬ
{
//Bmp_Decode((Int32U)MACHINE_PIC_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}


// void RunBIG_Up_dis(Int16U x, Int16U y)//����1up
// {
// // Bmp_Decode((Int32U)RUN_BIG_BUTT_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
// }

void Delete_Up_dis(Int16U x, Int16U y)//ɾ��up
{
Bmp_Decode((Int32U)DELETE_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void DeleteAll_Up_dis(Int16U x, Int16U y)//ȫɾup
{
Bmp_Decode((Int32U)DELETE_ALL_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}

void ShiftButtonUp_dis(Int16U x, Int16U y)//�ϵ���ťshift
{
Bmp_Decode((Int32U)SHIFT_BUTT_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void ShiftButtonDown_dis(Int16U x, Int16U y)//�ϵ���ťshift
{
Bmp_Decode((Int32U)SHIFT_BUTT_DOWN_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
//-------
void FrontPage_Up_dis(Int16U x, Int16U y)//ǰ��up
{
Bmp_Decode((Int32U)FRONT_PAGE_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void BackPage_Up_dis(Int16U x, Int16U y)//����up
{
Bmp_Decode((Int32U)BACK_PAGE_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void UpArrow_Up_dis(Int16U x, Int16U y)//�ϼ�ͷup
{
Bmp_Decode((Int32U)UP_ARROW_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void DownArrow_Up_dis(Int16U x, Int16U y)//�¼�ͷup
{
Bmp_Decode((Int32U)DOWN_ARROW_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void FastFWD_Up_dis(Int16U x, Int16U y)//���up
{
Bmp_Decode((Int32U)FAST_FORWD_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void FastBACK_Up_dis(Int16U x, Int16U y)//����up
{
Bmp_Decode((Int32U)FAST_BACK_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}


void Stop_Up_dis(Int16U x, Int16U y)//ֹͣup
{
Bmp_Decode((Int32U)STOP_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void Run_Up_dis(Int16U x, Int16U y)//����up
{
Bmp_Decode((Int32U)RUN_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
// void StopBIG_Up_dis(Int16U x, Int16U y)//ֹͣup
// {
// Bmp_Decode((Int32U)STOP_BIG_BUTT_UP_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
// }
//------------

void F4Wheel0_dis(Int16U x, Int16U y)//F4 �������ֹ�0
{
Bmp_Decode((Int32U)F4_WHEEL0_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F4Wheel1_dis(Int16U x, Int16U y)//F4 �������ֹ�1
{
Bmp_Decode((Int32U)F4_WHEEL1_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F5Wheel0_dis(Int16U x, Int16U y)//F5 �������ֿ�0
{
Bmp_Decode((Int32U)F5_WHEEL0_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void F5Wheel1_dis(Int16U x, Int16U y)//F5 �������ֿ�1
{
Bmp_Decode((Int32U)F5_WHEEL1_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
} 

void ElectricalWheel_dis(void)  //��������  ����״̬
{
/****
if(MotorType>=MOTOR_AC_SERVO)
	{
	if(ElectricWheelOn_flag==0)
		{
		if(WorkMode==MANUAL_MODE)
			F4Wheel0_dis(F4_WHEEL_BUTT_X,F4_WHEEL_BUTT_Y);
		else if(WorkMode==AUTO_MODE)
			F5Wheel0_dis(F5_WHEEL_BUTT_X,F5_WHEEL_BUTT_Y);
		}
	else	
		{
		if(WorkMode==MANUAL_MODE)
			F4Wheel1_dis(F4_WHEEL_BUTT_X,F4_WHEEL_BUTT_Y);
		else if(WorkMode==AUTO_MODE) 
			F5Wheel1_dis(F5_WHEEL_BUTT_X,F5_WHEEL_BUTT_Y);
		}
	}
	****/
}
void F6Amend0_dis(Int16U x, Int16U y)//�޸�ƫ����----------------------
{
Bmp_Decode((Int32U)F6_AMEND0_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
} 
void F6Amend1_dis(Int16U x, Int16U y)//�޸�ƫ����----------------------
{
Bmp_Decode((Int32U)F6_AMEND1_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
} 
void AmendButtonFlag_dis(void)	//F6�޸�����ƫ����
{
if(MotorType>=MOTOR_AC_SERVO)
	{
	if(WorkMode==AUTO_MODE)
		{
		if(AmendSwitch_flag==0)
			F6Amend0_dis( F6_AMEND_BUTT_X,  F6_AMEND_BUTT_Y);//�޸�ƫ����
		else
			F6Amend1_dis( F6_AMEND_BUTT_X,  F6_AMEND_BUTT_Y);//�޸�ƫ����
		}
	}
}

//-------------*****ģʽicon�� �л� ��ʾ******------------------(icon+name)
void ProTableIcon_dis(void)	//�����б�ģʽ�� icon��ʾ
{
F1ShowMessIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1 �鿴mess
switch(DisAllProgMode)
	{
	case PRO_BY_NUM://�����
			F2ByTimeIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2 ��ʱ������up
			F3ByNumIconDown_dis(F3PROJECT_BUTT_X,F3PROJECT_BUTT_Y);//F3 ���������down
			break;
	case PRO_BY_TIME://��ʱ��
			F2ByTimeIconDown_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2 ��ʱ������down
			F3ByNumIconUp_dis(F3PROJECT_BUTT_X,F3PROJECT_BUTT_Y);//F3 ���������up
			break;	
	}
F4DeleteOneProIconUp_dis(F4SWITCH_BUTT_X,F4SWITCH_BUTT_Y);//F4ɾ��һ��pro
F5DeleteAllProIconUp_dis(F5DELETE_BUTT_X,F5DELETE_BUTT_Y);//F5ɾ������pro
EnterButtUp_dis(ENTER_OK_BUTT_X, ENTER_OK_BUTT_Y);//OK butt ȷ��
F6ExitButtUp_dis(F6EXIT_BUTT_X,F6EXIT_BUTT_Y);//F6Exit butt ��־
}
void ProMessIcon_dis(void)	//���뷨ģʽ icon��ʾ
{
switch(InputMode)
	{
	case PINYIN_INPUT:	//ƴ������
			F1PinyinIconDown_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1ƴ������down---------
			F2CharIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2��ĸ����up
			F3NumIconUp_dis(F3PROJECT_BUTT_X,F3PROJECT_BUTT_Y);//F3��������up
			F4ExitIconUp_dis(F4SWITCH_BUTT_X,F4SWITCH_BUTT_Y);//F4up�˳�
			break;
	case CHAR_INPUT:	//��ĸ����
			F1PinyinIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1ƴ������up
			F2CharIconDown_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2��ĸ����down---------
			F3NumIconUp_dis(F3PROJECT_BUTT_X,F3PROJECT_BUTT_Y);//F3��������up
			F4ExitIconUp_dis(F4SWITCH_BUTT_X,F4SWITCH_BUTT_Y);//F4up�˳�
			break;	
	case NUMBER_INPUT:	//���� ����
			F1PinyinIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1ƴ������up
			F2CharIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2��ĸ����up
			F3NumIconDown_dis(F3PROJECT_BUTT_X,F3PROJECT_BUTT_Y);//F3��������down---------
			F4ExitIconUp_dis(F4SWITCH_BUTT_X,F4SWITCH_BUTT_Y);//F4up�˳�
			break;		
	}
}
void SubModeIcon_dis(Int16U mode)//================��ģʽ  icon��ʾ
{
Int16U x1,y1,x2,y2,back_color;
//���F1-F6 button ��ʾ*****************
back_color=TEXT_TAB_BACK_COLOR;
x1=F1LABEL_BUTT_X,y1=F1LABEL_BUTT_Y;
x2=x1+50,y2=y1+ICONBUTT_GAP_V*5-15;
GLCD_SetWindow_Fill(x1,y1,x2,y2,back_color,back_color);//�հ�F1,2,3...
//--------------��������,F0,F5
if((mode!=PROG_PRO_MODE)&&(mode!=TEACH_PRO_MODE)
	&&(mode!=PROG_PRO_MESS_MODE)&&(mode!=TEACH_PRO_MESS_MODE))	//���� ��Ϣ
	{
	x1=BACK_PAGE_X,y1=BACK_PAGE_Y;
	x2=F6EXIT_BUTT_X-10,y2=FAST_BACK_Y+50;
	GLCD_SetWindow_Fill(x1,y1,x2,y2,back_color,back_color);  //���ط����ͷ,F0,F5 .....
	}
//--------------���shift
back_color=WIN_DOWN_BACK_COLOR;
x1=SHIFT_BUTT_X,y1=SHIFT_BUTT_Y;
x2=SHIFT_BUTT_X+70,y2=SHIFT_BUTT_Y+35;
GLCD_SetWindow_Fill(x1,y1,x2,y2,back_color,back_color);  //shift.....
//--------------������.......
x1=RUN_X,y1=RUN_Y;
x2=STOP_X+RUN_BIG_WIDE,y2=STOP_Y+RUN_BIG_HIGH;
GLCD_SetWindow_Fill(x1,y1,x2,y2,back_color,back_color);  //������..
//-----work mode
switch(mode)
	{
	case PROG_MODE://���ģʽ..............
	case TEACH_MODE:		//ʾ��ģʽ..............
			//----------F
			ShiftButtonUp_dis(SHIFT_BUTT_X,SHIFT_BUTT_Y);	//shift�ϵ� ��ť
			//����----------
			FrontPage_Up_dis( FRONT_PAGE_X,  FRONT_PAGE_Y);//ǰ��up
			BackPage_Up_dis( BACK_PAGE_X,  BACK_PAGE_Y);//����up
			if((MotorType<MOTOR_DC_SERVO)||(MotorType>=MOTOR_AC_SERVO))
				{
				FastFWD_Up_dis(FAST_FWD_X, FAST_FWD_Y);//���up
				FastBACK_Up_dis(FAST_BACK_X, FAST_BACK_Y);//����up
				}
			F5CutIcon_Up_dis(F5_CUT_X,F5_CUT_Y); //F5һ��up
			F0CutAllIcon_Up_dis(F0_ALL_CUT_X,F0_ALL_CUT_Y); //ȫ��up
			// F5DeleteAllKnifeIconUp_dis(F5DELETE_BUTT_X,F5DELETE_BUTT_Y);//	ɾ�����е�����
			//F1,2,3,4......
			F1LabelIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1��ǩup
			F2DivideIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2�ȷ�up
			F3ProjectIconUp_dis(F3PROJECT_BUTT_X,F3PROJECT_BUTT_Y);//F3����up
			F4PushIconUp_dis(F4SWITCH_BUTT_X,F4SWITCH_BUTT_Y);//�л���ťup
			//------------
			if(mode==TEACH_MODE)//ʾ��ģʽ.
				{
				Run_Up_dis(RUN_X,RUN_Y);//����up
				Stop_Up_dis(STOP_X,STOP_Y);//ֹͣup
				}
			else
				{
				Delete_Up_dis(DELETE_X,DELETE_Y);
				DeleteAll_Up_dis(DELETE_ALL_X,DELETE_ALL_Y);
				}
			break;
	case MANUAL_MODE:	//�ֶ�ģʽ..............
			//----------F
			ShiftButtonUp_dis(SHIFT_BUTT_X,SHIFT_BUTT_Y);	//shift�ϵ� ��ť
			//����----------�ֶ��µ���ʾ������������
			FrontPage_Up_dis( MAN_FRONT_PAGE_X,  MAN_FRONT_PAGE_Y);//ǰ��up--------------
			BackPage_Up_dis( MAN_BACK_PAGE_X,  MAN_BACK_PAGE_Y);//����up-------------------
			if((MotorType<MOTOR_DC_SERVO)||(MotorType>=MOTOR_AC_SERVO))
				{
				FastFWD_Up_dis(MAN_FAST_FWD_X, MAN_FAST_FWD_Y);//���up
				FastBACK_Up_dis(MAN_FAST_BACK_X, MAN_FAST_BACK_Y);//����up
				}
			//F1,2,3,4......
			F1RulerIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1��׼butt
			F2ParamaterIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2����
			F3ClockIconUp_dis(F3PROJECT_BUTT_X,F3PROJECT_BUTT_Y);//F3ʱ��
			if(MotorType<MOTOR_DC_SERVO)    //��Ƶ��--
				F4PulseSetIconUp_dis(F4SWITCH_BUTT_X,F4SWITCH_BUTT_Y);//F4���嵱��
			else
				ElectricalWheel_dis();  //��������  ����״̬
			//----------------
			Run_Up_dis(RUN_X,RUN_Y);//����up
			Stop_Up_dis(STOP_X,STOP_Y);//ֹͣup
			break;	
	case AUTO_MODE://�Զ�ģʽ..............
	case SELF_CUT_MODE:		//�Ե�ģʽ..............
			//----------F
			ShiftButtonUp_dis(SHIFT_BUTT_X,SHIFT_BUTT_Y);	//shift�ϵ� ��ť
			//����----------
			FrontPage_Up_dis( FRONT_PAGE_X,  FRONT_PAGE_Y);//ǰ��up
			BackPage_Up_dis( BACK_PAGE_X,  BACK_PAGE_Y);//����up
			if((MotorType<MOTOR_DC_SERVO)||(MotorType>=MOTOR_AC_SERVO))
				{
				FastFWD_Up_dis(FAST_FWD_X, FAST_FWD_Y);//���up
				FastBACK_Up_dis(FAST_BACK_X, FAST_BACK_Y);//����up
				}
			//F1,2,3,4......
			F1RulerIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1��׼butt
			F2ParamaterIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2����
			F3AddIconUp_dis(F3PROJECT_BUTT_X,F3PROJECT_BUTT_Y);//F3++
			F4SubIconUp_dis(F4SWITCH_BUTT_X,F4SWITCH_BUTT_Y);//F4--
			ElectricalWheel_dis();  //��������  ����״̬
			AmendButtonFlag_dis();	//F6�޸�����ƫ����
			//----------------
			Run_Up_dis(RUN_X,RUN_Y);//����up
			Stop_Up_dis(STOP_X,STOP_Y);//ֹͣup
			break;
	//---��� ʾ��..............
	case PROG_LABEL_MODE:		 //��ǩ
	case TEACH_LABEL_MODE:		 //��ǩ
			F1OkIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1���
			F2ExitIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2up�˳�
			UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//�ϼ�ͷup
			DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//�¼�ͷup
			//---------
			F1LabelFunPic_dis(LABEL_FUN_PIC_X,LABEL_FUN_PIC_Y);//��ǩ����pic
			break;
	case PROG_DIVIDE_MODE:	 //�ȷ�
	case TEACH_DIVIDE_MODE:	 //�ȷ�
			UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//�ϼ�ͷup
			DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//�¼�ͷup
			//---------
			if(DivideValue_flag==0) //�ȷ�������
				{
				F1OkIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1���
				F2DivNumIconDown_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2�ȷ���down------
				F3DivDataIconUp_dis(F3PROJECT_BUTT_X,F3PROJECT_BUTT_Y);//F3�ȷ�ֵup
				F4ExitIconUp_dis(F4SWITCH_BUTT_X,F4SWITCH_BUTT_Y);//F4up�˳�
				//------------
				F2DivideNumPic_dis(DIVIDE_FUN_PIC_X,DIVIDE_FUN_PIC_Y);//�ȷ������� pic
				}
			else	//�ȷ�ֵ
				{
				F1OkIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//���
				F2DivNumIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2�ȷ���up
				F3DivDataIconDown_dis(F3PROJECT_BUTT_X,F3PROJECT_BUTT_Y);//F3�ȷ�ֵdown---
				F4ExitIconUp_dis(F4SWITCH_BUTT_X,F4SWITCH_BUTT_Y);//F4up�˳�
				//------------
				F3DivideValuePic_dis(DIVIDE_FUN_PIC_X,DIVIDE_FUN_PIC_Y);//�ȷ�ֵ���� pic
				}
			break;
	case PROG_PRO_MODE:	//����ѡ��
	case TEACH_PRO_MODE:	//����ѡ��
			// F1ShowMessIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1 �鿴mess
			// F2ByTimeIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2 ��ʱ������up
			// F3ByNumIconDown_dis(F3PROJECT_BUTT_X,F3PROJECT_BUTT_Y);//F3 ���������down
			// F4DeleteOneProIconUp_dis(F4SWITCH_BUTT_X,F4SWITCH_BUTT_Y);//F4ɾ��һ��pro
			// F5DeleteAllProIconUp_dis(F5DELETE_BUTT_X,F5DELETE_BUTT_Y);//F5ɾ������pro
			// F6ExitButtUp_dis(F6EXIT_BUTT_X,F6EXIT_BUTT_Y);//F6Exit butt ��־
			UpArrow_Up_dis( SUB_UP_ARROW_X,  SUB_UP_ARROW_Y);//�ϼ�ͷup
			DownArrow_Up_dis( SUB_DOWN_ARROW_X,  SUB_DOWN_ARROW_Y);//�¼�ͷup
			ProTableIcon_dis();	//�����б�ģʽ�� icon��ʾ
			break;
	case PROG_PRO_MESS_MODE:	 //���� ��Ϣ
	case TEACH_PRO_MESS_MODE:	//���� ��Ϣ
			ProMessIcon_dis();	//���뷨ģʽ icon��ʾ
				
			break;	
	//--�Զ��� �ֶ�
	case AUTO_RULER_MODE:  //��׼
	case MANUAL_RULER_MODE:  //��׼
	case SELF_RULER_MODE:  //��׼
			F1OkIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1���
			F2ExitIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2up�˳�
			//---------
			F1RulerFunPic_dis(RULER_FUN_PIC_X,RULER_FUN_PIC_Y);//��׼����pic	
			break;	
	case AUTO_TOOLS_MODE:    //����
	case MANUAL_TOOLS_MODE:    //����
	case SELF_TOOLS_MODE:    //����
			F1OkIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1���
			F2ExitIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2up�˳�
			UpArrow_Up_dis(F3PROJECT_BUTT_X ,  F3PROJECT_BUTT_Y);//�ϼ�ͷup
			DownArrow_Up_dis(F4SWITCH_BUTT_X ,  F4SWITCH_BUTT_Y);//�¼�ͷup
			L_R_Arrow_dis(L_R_ARROW_X, L_R_ARROW_Y);//���Ҽ�ͷ
			//---------
			F2DatasFunPic_dis(SETDATA_FUN_PIC_X,SETDATA_FUN_PIC_Y);//��������pic
			break;	
	case MANUAL_CLOCK_MODE://ʱ��ģʽ
			F1OkIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1���
			F2ExitIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2up�˳�
			UpArrow_Up_dis(F3PROJECT_BUTT_X ,  F3PROJECT_BUTT_Y);//�ϼ�ͷup
			DownArrow_Up_dis(F4SWITCH_BUTT_X ,  F4SWITCH_BUTT_Y);//�¼�ͷup
			//---------
			F3ClockFunPic_dis(CLOCK_FUN_PIC_X,CLOCK_FUN_PIC_Y);//F3ʱ��ģʽpic	
			break;
	case MANUAL_PULSE_MODE:  //�趨���嵱��
			F1OkIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1���
			F2ExitIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2up�˳�
			UpArrow_Up_dis(F3PROJECT_BUTT_X ,  F3PROJECT_BUTT_Y);//�ϼ�ͷup
			DownArrow_Up_dis(F4SWITCH_BUTT_X ,  F4SWITCH_BUTT_Y);//�¼�ͷup
			break;
	case MANUAL_SERVO_C_MODE:	//ֱ���ŷ� C ����
			F1OkIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1���
			F2ExitIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2up�˳�
			UpArrow_Up_dis(F3PROJECT_BUTT_X ,  F3PROJECT_BUTT_Y);//�ϼ�ͷup
			DownArrow_Up_dis(F4SWITCH_BUTT_X ,  F4SWITCH_BUTT_Y);//�¼�ͷup
			break;	
	case MANUAL_PASS_MODE:   //����
			F1OkIconUp_dis(F1LABEL_BUTT_X,F1LABEL_BUTT_Y);//F1���
			F2ExitIconUp_dis(F2DIVIDE_BUTT_X,F2DIVIDE_BUTT_Y);//F2up�˳�
			UpArrow_Up_dis(F3PROJECT_BUTT_X ,  F3PROJECT_BUTT_Y);//�ϼ�ͷup
			DownArrow_Up_dis(F4SWITCH_BUTT_X ,  F4SWITCH_BUTT_Y);//�¼�ͷup
			L_R_Arrow_dis(L_R_ARROW_X, L_R_ARROW_Y);//���Ҽ�ͷ
			//---------
			//PsswordFunPic_dis(PASSWORD_FUN_PIC_X,PASSWORD_FUN_PIC_Y);//���빦��ģʽpic
			break;		
	}
//.........................���� ��
if(WorkMode_temp!=mode)
	{
	WorkMode_temp=mode;
	ModeName_dis(mode);
	//-------------����----
	IR_Up_flag=0;
	IR_Down_flag=0;
	}
}
void MainModeIcon_dis(Int16U mode)	// ------------��ģʽ icon��ʾ PragramModeIcon_dis
{
Int16U x,y,back_color;
switch(mode)
	{
	case PROG_MODE://���ģʽ..............
			//-------main mode
			break;
	case MANUAL_MODE:	//�ֶ�ģʽ..............
			break;
	case AUTO_MODE://�Զ�ģʽ..............
			break;
	case SELF_CUT_MODE:		//�Ե�ģʽ..............
			break;
	case TEACH_MODE:		//ʾ��ģʽ..............
			break;
	}
// // RunButtonDisExec();	//���� ��ť ��ʾ����
//-----sub mode
SubModeIcon_dis(mode);//--------��ģʽ  icon��ʾ
}


//-----------���� ģʽ�� ��������page  ��ʾ************************
void ClrSizeTable_dis(void)	//��� �������б�
{
Int16U x1,y1,x2,y2,back_color;
back_color=TEXT_TAB_BACK_COLOR;
x1=RIGHT_ARROW_X,y1=RIGHT_ARROW_Y;
x2=TABLE_END_COL,y2=RIGHT_ARROW_Y+Kf_Line_HIGH*PageKf_Size-10;
GLCD_SetWindow_Fill(x1,y1,x2,y2,back_color,back_color);//�հ��б�
}
void ProgModePage_dis(void)  //���ģʽ ���ֻ������++++++++++
{
ClrSizeTable_dis();//������ �б�հ�
//��ģʽ......
MainModeIcon_dis(WorkMode);//���ģʽ..............
//---------------Schedule
Schedule_dis(SCHEDULE_X,SCHEDULE_Y);//����
ProgressBar_dis(OnePro_head.pro_knifeSUM,Knife_order);  //������ ��ʾ
}
void AutoModePage_dis(void) //�Զ�ģʽ ���ֻ�����ʾ++++++++++++
{
ClrSizeTable_dis();//������ �б�հ�
//��ģʽ......
MainModeIcon_dis(WorkMode);//�Զ�ģʽ.........
//---------------Schedule
Schedule_dis(SCHEDULE_X,SCHEDULE_Y);//����
ProgressBar_dis(OnePro_head.pro_knifeSUM,Knife_order);  //������ ��ʾ
}
void AutoCutModePage_dis(void) //�Ե�ģʽ ���ֻ�����ʾ+++++++++++
{
ClrSizeTable_dis();//������ �б�հ�
//��ģʽ......
MainModeIcon_dis(WorkMode);//�Ե�ģʽ...........
//---------------Schedule
Schedule_dis(SCHEDULE_X,SCHEDULE_Y);//����
ProgressBar_dis(OnePro_head.pro_knifeSUM,Knife_order);  //������ ��ʾ
}
void ManualModePage_dis(void)  //�ֶ�ģʽ ���ֻ���++++++++++++
{
Int16U x1,y1,x2,y2,color;
color=TEXT_TAB_BACK_COLOR;
ClrSizeTable_dis();//������ �б�հ�
GLCD_SetWindow_Fill(SCHEDULE_X,SCHEDULE_Y,SCHEDULE_X+SCHEDULE_WIDE+0,SCHEDULE_Y+SCHEDULE_HIGH,color,color);  //���� ������
// MiddlePage_dis();//�հ�
//��ģʽ......
MachinePic_dis(MACHINE_PIC_X,MACHINE_PIC_Y);//�ֶ�ģʽ�� ����ͼƬ
MainModeIcon_dis(WorkMode);//�ֶ�ģʽ........


// color=0x9cd3;
// GLCD_SetWindow_Fill(F4_X,F4_Y,F4_X+48,F4_Y+48,color,color);  //����F4
// color=0xce79;
// GLCD_SetWindow_Fill(DELETE_X,DELETE_Y,DELETE_X+272,DELETE_Y+32,color,color);//����DELETE

// ElectricalWheel_dis();  //��������  ����״̬
// Manual_dis(MANUAL_X,MANUAL_Y);
}
void TeachModePage_dis(void)   //ʾ��ģʽ  ����ҳ��++++++++++++
{
ClrSizeTable_dis();//������ �б�հ�
//��ģʽ......
MainModeIcon_dis(WorkMode);//ʾ��ģʽ...........
// FrontPage_Up_dis( FRONT_PAGE_X,  FRONT_PAGE_Y);//ǰһҳup
// BackPage_Up_dis( BACK_PAGE_X,  BACK_PAGE_Y);//��һҳup
// UpArrow_Up_dis( UP_ARROW_X,  UP_ARROW_Y);//�ϼ�ͷup
// DownArrow_Up_dis( DOWN_ARROW_X,  DOWN_ARROW_Y);//�¼�ͷup

// color=0xce79;
// GLCD_SetWindow_Fill(STOP_X,STOP_Y,STOP_X+82,STOP_Y+32,color,color);
// Delete_Up_dis( DELETE_X, DELETE_Y );//ɾ��up
// DeleteAll_Up_dis( DELETE_ALL_X, DELETE_ALL_Y);//ȫɾup
//---------------Schedule
Schedule_dis(SCHEDULE_X,SCHEDULE_Y);//����
ProgressBar_dis(OnePro_head.pro_knifeSUM,Knife_order);  //������ ��ʾ
}



//**************************************��� ��
void ProgSet_dis(Int32U size, Int16U x, Int16U y, Int8U set_flag)// �����趨ҳ�� ѡ��������ʾ
{
Int8U num[8],k,int_flag=0;//0xef9f;
Int16U back_color=TEXT_TAB_BACK_COLOR; //�ı�ҳ  ����ɫ
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
			
		if((WorkMode==PROG_DIVIDE_MODE)||(WorkMode==TEACH_DIVIDE_MODE)) //�ȷ�
			{
			if(DivideValue_flag==0)//�ȷ���
				{
				if(PorgSet_sel==1)
					{
					num[0]=size/1000+48;
					num[1]=(size/100)%10+48;
					num[2]=(size/10)%10+48;
					num[3]=size%10+48;
					// num[4]=' ';
					// num[5]=' ';
					// num[6]=' ';
					num[4]=0;
					int_flag=1;
					}
				else
					int_flag=0;
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
   Printf24(num,x,y,WHITE_COLOR,1,BLUE_COLOR);//
   }
else
   {
   Printf24(num,x,y,BLACK_COLOR,1,back_color);//
   }
}

void F1_LabelPage_dis(void)  //F1--��ǩģʽ ������ʾ.........................
{
volatile Int16U x,y,gap;
Int16U back_color;
x=TOTAL_SIZE_X-150,y=TOTAL_SIZE_Y,gap=ROW_GAP1;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis();//�м��ҳ

SubModeIcon_dis(WorkMode);   //��ǩģʽ

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
	case INDONSIA:	//ӡ��
		Printf24("Total-Panja:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Label��",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Memangkas��",x,y,BLACK_COLOR,0,0xffff);
			break;
	case PORTUGAL:	//������
		Printf24("Total:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("etiqueta:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("descartar:",x,y,BLACK_COLOR,0,0xffff);
			break;
	case SPANISH: //������
		Printf24("longitud:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("etiqueta:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("descartar:",x,y,BLACK_COLOR,0,0xffff);
			break;
	}	
ProgSet_dis( 0, TOTAL_SIZE_X,  TOTAL_SIZE_Y,1);//
ProgSet_dis( 0, LABEL_SIZE_X,  LABEL_SIZE_Y,0);
ProgSet_dis( 0, WASTE_SIZE_X,  WASTE_SIZE_Y,0);
}

void F2_DividePage_dis(void)  //F2--�ȷ�ģʽ ������ʾ
{
// volatile Int16U x,y,gap;
// Int16U back_color;
// x=TOTAL_SIZE_X-150,y=TOTAL_SIZE_Y,gap=ROW_GAP2;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis();//�м��ҳ

DivideValue_flag=0;
DivideTypeSelExec();	//�ȷ� ����  ѡ��........

}

void F3_SelProgPage_dis(void) //F3--����ѡ�� ������ʾ
{
volatile Int16U x,y,i;
Int16U line_color=BLACK_COLOR,back_color=TEXT_TAB_BACK_COLOR;
x=90,y=190;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis();//�м��ҳ
DisAllProgMode=PRO_BY_NUM;
SubModeIcon_dis(WorkMode);   //����ѡ��ģʽ
switch(Language)
	{
	case CHN_HAN:
		Printf16("���        ����",x,y,line_color,0,back_color);	x+=380;
		Printf16("����        �޸�����",x,y,line_color,0,back_color);
			break;
	case ENGLISH:	
		Printf16("Order       Name",x,y,line_color,0,back_color);	x+=380;
		Printf16("Step        Modified",x,y,line_color,0,back_color);
			break;
	case INDONSIA:	//ӡ��	
		Printf16("Tidak.      Nama",x,y,line_color,0,back_color);	x+=380;
		Printf16("Langkah     Modifikasi",x,y,line_color,0,back_color);
			break;
	case PORTUGAL:	//������
		Printf16("N?o.        Nome",x,y,line_color,0,back_color);	
		ASCII_Printf("a",ASCII16_MODE,8,16,PUTAO_ZK16,x+8,y,line_color,back_color);
		x+=380;
		Printf16("Passo    	  Data",x,y,line_color,0,back_color);
			break;
	case SPANISH: //������
		Printf16("No.        Nombre",x,y,line_color,0,back_color);	
		x+=380;
		Printf16("Paso    	  Fecha",x,y,line_color,0,back_color);
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
		case INDONSIA:	//ӡ��
				Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case PORTUGAL:	//������
				Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case SPANISH: //������
				Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		}
Printf24("1          500",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);

//-------------------------�����б�
for(i=1;i<=MAX_PROG;i++)
	ProNumGroup[i]=i;
prog_order=1;
}

//F4 ��ӱ�� ����
void AllFlagRemind(void)	//F4 ���ģʽ��ʾ
{
// GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
// switch(Language)
		// {
		// case CHN_HAN:
			// Printf16("F1-����,F2-��ֽ,F3-ײֽ,F4-��ֽ,F5-��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
				// break;
		// case ENGLISH:	
		// case PORTUGAL:	//������
		// case SPANISH: //������
			// Printf16("F1-AIR,F2-SORT,F3-CRASH,F4-PUSH,F5-KNIFE",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
				// break;
		// case INDONSIA:	//ӡ��
			// Printf16("F1-udara,F2-mengat,F3-memukul,F4-Dorong,F5-pisau",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
				// break;
		// }
}
//F4���ģʽ����
void F4_FlagMode_In(void)
{
volatile Int16U x,y;
Int16U back_color;
Int16U fill_color,line_color;
fill_color=0xFF5b,line_color=BLUE_COLOR;
ButtonTouch_mode=TOU_MODE_F4;
CurrentArea_save1(F4_FLAG_WIN_X,F4_FLAG_WIN_Y, F4_FLAG_WIN_WIDE,F4_FLAG_WIN_HIGH);
GLCD_SetWindow_Fill(F4_FLAG_WIN_X, F4_FLAG_WIN_Y, F4_FLAG_WIN_X+F4_FLAG_WIN_WIDE-1, F4_FLAG_WIN_Y+F4_FLAG_WIN_HIGH-1, line_color, fill_color);
// F1AirBedButt_dis(F1_AIR_BED_X, F1_AIR_BED_Y);//F1����butt ��־
// F2SortPaperButt_dis(F2_SORT_PAPER_X, F2_SORT_PAPER_Y);//F2��ֽbutt ��־
// F3CrashPaperButt_dis(F3_CRASH_PAPER_X, F3_CRASH_PAPER_Y);//F3ײֽbutt ��־
// F4PushPaperButt_dis(F4_PUSH_PAPER_X, F4_PUSH_PAPER_Y);//F4��ֽbutt ��־
// F5RedKnifeButt_dis(F5_RED_KNIFE_X, F5_RED_KNIFE_Y);//F5�쵶butt ��־
// F6ExitButtUp_dis(F6_FLAG_EXIT_X, F6_FLAG_EXIT_Y);//F6Exit butt ��־
if(WorkMode==PROG_MODE)
	WorkMode=PROG_FLAG_MODE;	//��� ģʽ
else
	WorkMode=TEACH_FLAG_MODE;	//��� ģʽ
//SubModeIcon_dis(WorkMode);   //ģʽ
ModeName_dis(WorkMode);//mode name
AllFlagRemind();	//F4 ���ģʽ��ʾ
}
void F4FlagMode_Exit(void)
{
ButtonTouch_mode=0;
CurrentArea_recover1(F4_FLAG_WIN_X,F4_FLAG_WIN_Y, F4_FLAG_WIN_WIDE,F4_FLAG_WIN_HIGH);
if(WorkMode==PROG_FLAG_MODE)
	{
	WorkMode=PROG_MODE;		//��� ģʽ
	}
else
	{
	WorkMode=TEACH_MODE;	//ʾ�� ģʽ
	}
ProgressBar_dis(OnePro_head.pro_knifeSUM,Knife_order);  //������ ��ʾ
ModeName_dis(WorkMode);//mode name
PromptNum_dis();//���뷶Χ
PromptDis_flag=1;
}


//******************************************�� ���Զ� ���Ե� ��
void ParameterPage_dis(Int8U sel, Int8U flag) //���� ������ʾ
{
volatile Int16U x,y,gap,tx_wide=88;
Int16U front_color,back_color;
gap=PARA_ROW_GAP;x=PARA_START_X2+(sel/7)*PARA_COL_WIDE;
Int32U temp;
if(flag==1)
    {
	front_color=WHITE_COLOR;//;
	back_color=BLUE_COLOR;
	}
else
	{
	front_color=BLACK_COLOR;
	back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
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
				case INDONSIA:	//ӡ��
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case PORTUGAL:	//������
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case SPANISH: //������
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			if(Unit==UNIT_MM)
				Printf24("15         80",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			else
				Printf24("0.6        3.15",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//ӡ��
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case PORTUGAL:	//������
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case SPANISH: //������
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			if(Unit==UNIT_MM)
				Printf24("30     	   150",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			else
				Printf24("1.19        5.9",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
					Printf24("������ֵ��Χ        ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case ENGLISH:	
					Printf24("Data range          to",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case INDONSIA:	//ӡ��
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case PORTUGAL:	//������
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case SPANISH: //������
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			if(Unit==UNIT_MM)	
				Printf24("500        2200",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			else
				Printf24("23.63      86.61",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
		break;
	case 3:
		GLCD_SetWindow_Fill( x, y, x+tx_wide, y+24, TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		switch(Language)
			{
			case CHN_HAN:
				Printf24(" ����",x,y,front_color,1,back_color); //����
					break;
			case ENGLISH:
				Printf24("English",x,y,front_color,1,back_color); //����
					break;
			case INDONSIA:
				Printf24("Indones",x,y,front_color,1,back_color); //����
					break;		
			case PORTUGAL:	//������
				Printf24("Portuga",x,y,front_color,1,back_color); //����
				// Printf16("portugu��",x,y,front_color,1,back_color); //����
				// Printf16("        s",x,y,front_color,0,back_color); //����
					break;
			case SPANISH: //������
				Printf24("Espa?a",x,y,front_color,1,back_color); //����
				ASCII_Printf("n",ASCII24_MODE,12,24,PUTAO_ZK24,x+12*4,y,front_color, back_color);
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
				case INDONSIA:	//ӡ��
					Printf16("Tekan tombol Insert untuk beralih bahasa",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;	
				case PORTUGAL:	//������
					Printf16("Pressione a tecla Insert para alternar idiomas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;	
				case SPANISH: //������
					Printf16("Pulse la tecla Insertar para interruptor",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
				case INDONSIA:	//ӡ��
					Printf16("Tekan tombol Insert untuk beralih unit",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;	
				case PORTUGAL:	//������
					Printf16("Pressione a tecla Insert para comutar a unidade",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;	
				case SPANISH: //������	
					Printf16("Pulse la tecla Insert para cambiar la unidad",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
				case INDONSIA:	//ӡ��
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case PORTUGAL:	//������
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case SPANISH: //������
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			if(Unit==UNIT_MM)
				Printf24("0         1",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			else
				Printf24("0        0.038",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//ӡ��
					Printf24("Efekti    -    ,cacat  0-    ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case PORTUGAL:	//������
				case SPANISH: //������
					Printf24("eficaz    -   ,inv��            ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					Printf24("                   li",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);//inv��lido
					Printf24("                     do(0-     )",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);//inv��lido
						break;
				}
			if(Unit==UNIT_MM)
				Printf24("11   500            10",REMIND_WINDOW_X+85,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			else
				Printf24("0.44  19            0.4",REMIND_WINDOW_X+82,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);	
			}
		break;
	case 7:  //ѹֽ��Ч ��־
		GLCD_SetWindow_Fill( x, y, x+tx_wide+16, y+24, TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		if(PressValid_flag==0)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24(" ��Ч  ",x,y,front_color,1,back_color); //
						break;
				case ENGLISH:
					Printf24("Invalid",x,y,front_color,1,back_color); //
						break;
				case INDONSIA:	//ӡ��
					Printf24(" Cacat ",x,y,front_color,1,back_color); //
						break;
				case PORTUGAL:	//������
				case SPANISH: //������
					Printf24("inv��   ",x,y,front_color,1,back_color); //
					Printf24("    li",x,y,front_color,0,back_color); //inv��lido
					Printf24("      do",x,y,front_color,0,back_color); //
						break;
				}		
			}
		else 
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24(" ��Ч ",x,y,front_color,1,back_color); //
						break;
				case ENGLISH:
					Printf24("Valid ",x,y,front_color,1,back_color); //
						break;
				case INDONSIA:	//ӡ��
					Printf24("Efekti",x,y,front_color,1,back_color); //
						break;
				case PORTUGAL:	//������
				case SPANISH: //������
					Printf24("eficaz",x,y,front_color,1,back_color); //
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
				case INDONSIA:	//ӡ��	
					Printf16("Tekan tombol Insert,Platen berhenti",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//������
					Printf16("Pressione a tecla Insert, a fun??o comuta??o",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, REMIND_WINDOW_X+10+(31*8),REMIND_WINDOW_Y+5,BLACK_COLOR,0xffff);
					ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, REMIND_WINDOW_X+10+(41*8),REMIND_WINDOW_Y+5,BLACK_COLOR,0xffff);
					break;
				case SPANISH: //������
					Printf16("Pulse la tecla Insert cambiar stop",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				}
			}
		break;	
	case 8: //	����������-------
		if(Unit==UNIT_MM)//mm  ��λ
			temp=AirOffDistance;
		else
			temp=AirOffDistance*100/254;
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
				case INDONSIA:	//ӡ��
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//������
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case SPANISH: //������
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			if(Unit==UNIT_MM)
				Printf24("0           10",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			else
				Printf24("0           0.4",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);	
			}
		break;	
		//--------------------------------ֱ���ŷ��趨�ٶ�
	case 9: //	����ٶ�+������Ч
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST:
			case MOTOR_FREQ_3_SPD:
			case MOTOR_FREQ_3_SPD_RST:	//��Ƶ
				GLCD_SetWindow_Fill( x, y, x+tx_wide, y+24, TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
				if(IR_SensorStus==1)		//����  ��Ч��ƽ
					{
					switch(Language)
						{
						case CHN_HAN:
							Printf24("����Ч",x,y,front_color,1,back_color); //
								break;
						case ENGLISH:
							Printf24("High ",x,y,front_color,1,back_color); //
								break;
						case INDONSIA:	//ӡ��
							Printf24("Tinggi",x,y,front_color,1,back_color); //
								break;
						case PORTUGAL:	//������
						case SPANISH: //������
							Printf24("alto",x,y,front_color,1,back_color); //
								break;
						}		
					}
				else
					{
					switch(Language)
						{
						case CHN_HAN:
							Printf24("����Ч",x,y,front_color,1,back_color); //
								break;
						case ENGLISH:
							Printf24("Low  ",x,y,front_color,1,back_color); //
								break;
						case INDONSIA:	//ӡ��
							Printf24("Rendah",x,y,front_color,1,back_color); //
								break;
						case PORTUGAL:	//������
							Printf24("baixo",x,y,front_color,1,back_color); //
								break;
						case SPANISH: //������
							Printf24("bajo",x,y,front_color,1,back_color); //
								break;
						}		
					}
				if(flag==1)	
					{
					switch(Language)
						{
						case CHN_HAN:
							Printf24("�������,�л������Ч��ƽ!     ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case ENGLISH:	
							Printf24("Press INSERT,change IR status!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case INDONSIA:	//ӡ��	
							Printf16("Tekan tombol Insert,Switching Status IR",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case PORTUGAL:	//������
							Printf16("Pressione a tecla Insert para ligar o sinal IR",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case SPANISH: //������
							Printf16("Pulse la tecla Insert para cambiar IR",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						}
					}
					break;
			case MOTOR_DC_SERVO:
			case MOTOR_DC670_SERVO:
				if(Unit==UNIT_MM)//mm  ��λ
					temp=ServoSpeed_order*100;
				else
					temp=ServoSpeed_order*1000;
				ProgSet_dis(temp,  x,  y,  flag);
				//-----------------------------��ʾ
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
						case INDONSIA:	//ӡ��
							Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case PORTUGAL:	//������
							Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case SPANISH: //������
							Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						}
					Printf24("13       20",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);	
					}	
					break;
			case MOTOR_AC_SERVO:
			case MOTOR_AC_SERVO_REV:
				if(Unit==UNIT_MM)//mm  ��λ
					temp=AC_MotorSPD*100;
				else
					temp=AC_MotorSPD*1000;
				ProgSet_dis(temp,  x,  y,  flag);
				//-----------------------------��ʾ
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
						case INDONSIA:	//ӡ��
							Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case PORTUGAL:	//������
							Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case SPANISH: //������
							Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						}
					Printf24("0        32",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);	
					}
					break;
			}		
		break;
	case 10: //	�㶯�ٶ�
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST:
			case MOTOR_FREQ_3_SPD:
			case MOTOR_FREQ_3_SPD_RST:	//��Ƶ
				
					break;
			case MOTOR_DC_SERVO:
			case MOTOR_DC670_SERVO:
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
						case INDONSIA:	//ӡ��
							Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case PORTUGAL:	//������
							Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case SPANISH: //������
							Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						}
					Printf24("10       20",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
					}	
					break;
			case MOTOR_AC_SERVO:
			case MOTOR_AC_SERVO_REV:
				GLCD_SetWindow_Fill( x, y, x+tx_wide, y+24, TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
				if(IR_SensorStus==1)		//����  ��Ч��ƽ
					{
					switch(Language)
						{
						case CHN_HAN:
							Printf24("����Ч",x,y,front_color,1,back_color); //
								break;
						case ENGLISH:
							Printf24("High  ",x,y,front_color,1,back_color); //
								break;
						case INDONSIA:	//ӡ��
							Printf24("Tinggi",x,y,front_color,1,back_color); //
								break;
						case PORTUGAL:	//������
						case SPANISH: //������
							Printf24("alto",x,y,front_color,1,back_color); //
								break;
						}		
					}
				else
					{
					switch(Language)
						{
						case CHN_HAN:
							Printf24("����Ч",x,y,front_color,1,back_color); //
								break;
						case ENGLISH:
							Printf24("Low  ",x,y,front_color,1,back_color); //
								break;
						case INDONSIA:	//ӡ��
							Printf24("Rendah",x,y,front_color,1,back_color); //
								break;
						case PORTUGAL:	//������
							Printf24("baixo",x,y,front_color,1,back_color); //
								break;
						case SPANISH: //������
							Printf24("bajo",x,y,front_color,1,back_color); //
								break;
						}		
					}
				if(flag==1)	
					{
					switch(Language)
						{
						case CHN_HAN:
							Printf24("�������,�л������Ч��ƽ!     ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case ENGLISH:	
							Printf24("Press INSERT,change IR status!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case INDONSIA:	//ӡ��	
							Printf16("Tekan tombol Insert,Switching Status IR",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case PORTUGAL:	//������
							Printf16("Pressione a tecla Insert para ligar o sinal IR",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case SPANISH: //������
							Printf16("Pulse la tecla Insert para cambiar IR",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						}
					}
					break;
			}	
		break;	
		/***
	case 11: //	//����  ��Ч��ƽ
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST:
			case MOTOR_FREQ_3_SPD:
			case MOTOR_FREQ_3_SPD_RST:	//��Ƶ
				
					break;
			case MOTOR_DC_SERVO:
			case MOTOR_DC670_SERVO:
				y+=gap*2;
				if(IR_SensorStus==1)		//����  ��Ч��ƽ
					{
					switch(Language)
						{
						case CHN_HAN:
							Printf24("����Ч",x,y,front_color,1,back_color); //
								break;
						case ENGLISH:
							Printf24("High  ",x,y,front_color,1,back_color); //
								break;
						case INDONSIA:	//ӡ��
							Printf24("Tinggi",x,y,front_color,1,back_color); //
								break;
						}		
					}
				else
					{
					switch(Language)
						{
						case CHN_HAN:
							Printf24("����Ч",x,y,front_color,1,back_color); //
								break;
						case ENGLISH:
							Printf24("Low   ",x,y,front_color,1,back_color); //
								break;
						case INDONSIA:	//ӡ��
							Printf24("Rendah",x,y,front_color,1,back_color); //
								break;
						}		
					}
				if(flag==1)	
					{
					switch(Language)
						{
						case CHN_HAN:
							Printf24("�������,�л������Ч��ƽ!     ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case ENGLISH:	
							Printf24("Press INSERT,change IR status!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						case INDONSIA:	//ӡ��	
							Printf16("Tekan tombol Insert,Switching Status IR",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
							break;
						}
					}
					
				break;
			case MOTOR_AC_SERVO:
				break;
			}	
		break;	***/
	}
}

void F2_ToolsPage_dis(void) //���� ����
{
volatile Int16U x,y,gap,n,tx_wide=148;
Int16U back_color=TEXT_TAB_BACK_COLOR;	//0xef9f;
x=PARA_START_X1,y=PARA_START_Y,gap=PARA_ROW_GAP;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis();//�м��ҳ
SubModeIcon_dis(WorkMode);   //����ģʽ
GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*7-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
switch(Language)
	{
	case CHN_HAN:
		Printf24("ǰ����:    ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("�м���:    ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("����:    ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("����:    ",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf24("��λ:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf24("��ǰ��:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		//Printf24("��׼����:   ",x,y,BLACK_COLOR,1,back_color);
		Printf24("��ֽ����:   ",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		Printf24("ѹֽͣ��:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("��������:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST:
			case MOTOR_FREQ_3_SPD:
			case MOTOR_FREQ_3_SPD_RST:
				Printf24("���ѡ��:   ",x,y,BLACK_COLOR,1,back_color);
					break;
			case MOTOR_DC_SERVO:
			case MOTOR_DC670_SERVO:
				Printf24("����ٶ�:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
				Printf24("�㶯�ٶ�:   ",x,y,BLACK_COLOR,1,back_color);
					break;
			case MOTOR_AC_SERVO:
			case MOTOR_AC_SERVO_REV:
				Printf24("�����ٶ�:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
				Printf24("���ѡ��:   ",x,y,BLACK_COLOR,1,back_color);
					break;
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
		GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		Printf24("Press-Stop:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("AirOff-dist:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST:
			case MOTOR_FREQ_3_SPD:
			case MOTOR_FREQ_3_SPD_RST:
				Printf24("IR-Set:   ",x,y,BLACK_COLOR,1,back_color);
					break;
			case MOTOR_DC_SERVO:
			case MOTOR_DC670_SERVO:
				Printf24("Max-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
				Printf24("Jog-speed:",x,y,BLACK_COLOR,1,back_color);
					break;
			case MOTOR_AC_SERVO:
			case MOTOR_AC_SERVO_REV:
				Printf24("Run-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
				Printf24("IR-Set:   ",x,y,BLACK_COLOR,1,back_color);
					break;
			}
			break;
	case INDONSIA:	//ӡ��
		Printf24("Sete-batas:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Dala-batas:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Sebe-batas:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Bahasa:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf24("Satuan:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf24("Memajukan:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Doro-jarak:",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		Printf24("Plat-bawah:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Off gas da: ",x,y,BLACK_COLOR,1,back_color);y+=gap;
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST:
			case MOTOR_FREQ_3_SPD:
			case MOTOR_FREQ_3_SPD_RST:
				Printf24("Set-IR:  ",x,y,BLACK_COLOR,1,back_color);
					break;
			case MOTOR_DC_SERVO:
			case MOTOR_DC670_SERVO:
				Printf24("Tercepat:",x,y,BLACK_COLOR,1,back_color);y+=gap;
				Printf24("Jog-kecep:",x,y,BLACK_COLOR,1,back_color);
					break;
			case MOTOR_AC_SERVO:
			case MOTOR_AC_SERVO_REV:
				Printf24("Kecepa-lari:",x,y,BLACK_COLOR,1,back_color);y+=gap;
				Printf24("Set-IR:  ",x,y,BLACK_COLOR,1,back_color);
					break;
			}
			break;	
	case PORTUGAL:	//������
		Printf24("O ex-limite:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Intermedi:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("ap��        ",x,y,BLACK_COLOR,1,back_color);
		Printf24("   s-limite:",x,y,BLACK_COLOR,0,back_color);y+=gap;
		Printf24("l��    ",x,y,BLACK_COLOR,1,back_color); 
		Printf24("  ngua:",x,y,BLACK_COLOR,0,back_color);  y+=gap;
		Printf24("unidade:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf24("antes:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		//Printf24("��׼����:   ",x,y,BLACK_COLOR,1,back_color);
		Printf24("distancia:",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		Printf24("encerra:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Off Air:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST:
			case MOTOR_FREQ_3_SPD:
			case MOTOR_FREQ_3_SPD_RST:
				Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
					break;
			case MOTOR_DC_SERVO:
			case MOTOR_DC670_SERVO:
				Printf24("Veloci-m��  ",x,y,BLACK_COLOR,1,back_color);
				Printf24("          x:",x,y,BLACK_COLOR,0,back_color);y+=gap;
				Printf24("Veloci-Jog:",x,y,BLACK_COLOR,1,back_color);
					break;
			case MOTOR_AC_SERVO:
			case MOTOR_AC_SERVO_REV:
				Printf16("Veloci-corrida:",x,y,BLACK_COLOR,1,back_color);y+=gap;
				Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
					break;
			}
			break;	
	case SPANISH: //������
		Printf24("l��      ",x,y,BLACK_COLOR,1,back_color);//l��mite
		Printf24("  mite ex:",x,y,BLACK_COLOR,0,back_color);y+=gap;
		Printf24("l��      ",x,y,BLACK_COLOR,1,back_color);//l��mite
		Printf24("  mite Medio:",x,y,BLACK_COLOR,0,back_color);y+=gap;
		Printf24("Tras el l��",x,y,BLACK_COLOR,1,back_color);//l��mite
		Printf24("          m",x,y,BLACK_COLOR,0,back_color);y+=gap;
		Printf24("idioma",x,y,BLACK_COLOR,1,back_color); 
		y+=gap;
		Printf24("unidad:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
		Printf24("avanzar:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		//Printf24("��׼����:   ",x,y,BLACK_COLOR,1,back_color);
		Printf24("distancia:",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		Printf24("cierre:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Off Air:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST:
			case MOTOR_FREQ_3_SPD:
			case MOTOR_FREQ_3_SPD_RST:
				Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
					break;
			case MOTOR_DC_SERVO:
			case MOTOR_DC670_SERVO:
				Printf24("Veloci-m��  ",x,y,BLACK_COLOR,1,back_color);
				Printf24("          x:",x,y,BLACK_COLOR,0,back_color);y+=gap;
				Printf24("Veloci-Jog:",x,y,BLACK_COLOR,1,back_color);
					break;
			case MOTOR_AC_SERVO:
			case MOTOR_AC_SERVO_REV:
				Printf16("Veloci-corrida:",x,y,BLACK_COLOR,1,back_color);y+=gap;
				Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
					break;
			}
			break;	
	}
switch(MotorType)
	{
	case MOTOR_FREQ_5_SPD_RST:
	case MOTOR_FREQ_3_SPD:
	case MOTOR_FREQ_3_SPD_RST:
			for(n=1;n<=9;n++)
				ParameterPage_dis(n, 0);
			break;
	case MOTOR_DC_SERVO:
	case MOTOR_DC670_SERVO:
			// for(n=1;n<=11;n++)
			for(n=1;n<=10;n++)
				ParameterPage_dis(n, 0);
			break;
	case MOTOR_AC_SERVO:	
	case MOTOR_AC_SERVO_REV:	
			for(n=1;n<=10;n++)
				ParameterPage_dis(n, 0);
			break;
	}		 
ParameterPage_dis(0, 1);
}

void F1_RulerPage_dis(void) //��׼ ����
{
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis();//�м��ҳ
SubModeIcon_dis(WorkMode);   //��׼ģʽ

}

void F3_plus_dis(Int8U flag)	//F3++
{
if(flag==1)
	{
	Printf32("++",SIZE_WINDOW_X,SIZE_WINDOW_Y,RED_COLOR,1,0xffff);
	GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
	switch(Language)
		{
		case CHN_HAN:
				Printf24("�ٰ�F3++,�˳�",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case ENGLISH:	
				Printf24("Press F3++ to exit",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case INDONSIA:	//ӡ��	
				Printf24("Tekan F3++ untuk keluar",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case PORTUGAL:	//������
				Printf24("imprensa F3++,desistir",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case SPANISH: //������
				Printf24("prensa F3++,dejar de",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		}
	//.........................���� ��
	ModeName_dis(WorkMode);	
	}
else
	{
	Printf32("++",SIZE_WINDOW_X,SIZE_WINDOW_Y,0xffff,1,0xffff);
	PromptNum_dis();//���뷶Χ
	PromptDis_flag=1;
	//.........................���� ��
	ModeName_dis(WorkMode);	
	}
}
void F4_minus_dis(Int8U flag)	//F4--
{
if(flag==1)
	{
	Printf32("--",SIZE_WINDOW_X,SIZE_WINDOW_Y,RED_COLOR,1,0xffff);
	GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
	switch(Language)
		{
		case CHN_HAN:
				Printf24("�ٰ�F4--,�˳�",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case ENGLISH:	
				Printf24("Press F4-- to exit",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case INDONSIA:	//ӡ��	
				Printf24("Tekan F4-- untuk keluar",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case PORTUGAL:	//������
				Printf24("imprensa F4--,desistir",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case SPANISH: //������
				Printf24("prensa F4--,dejar de",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		}
	//.........................���� ��
	ModeName_dis(WorkMode);	
	}
else
	{
	Printf32("--",SIZE_WINDOW_X,SIZE_WINDOW_Y,0xffff,1,0xffff);
	PromptNum_dis();//���뷶Χ
	PromptDis_flag=1;
	//.........................���� ��
	ModeName_dis(WorkMode);	
	}
}

//�ֶ�********************
void TimeSetSel_dis(Int8U sel, Int8U flag) //ʱ�� �趨 ��ʾ
{
volatile Int16U x,y,gap;
Int16U front_color,back_color;
gap=CLOCK_GAP_Y;x=CLOCK_DATA_X+120;
if(flag==1)
    {
	front_color=WHITE_COLOR;//;
	back_color=BLUE_COLOR;
	}
else
	{
	front_color=BLACK_COLOR;
	back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
	}
y=CLOCK_DATA_Y+gap*sel;
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
				case INDONSIA:	//ӡ��
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//������
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //������
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("0        99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//ӡ��
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//������
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //������
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("1        12",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//ӡ��
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//������
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //������
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("1        31",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//ӡ��
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//������
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //������
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("0        23",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//ӡ��
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//������
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //������
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("0        59",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
		break;
	
	}
}

void ClockPage_dis(void)  //F3�ֶ� ʱ��	
{
volatile Int16U x,y,gap,n;
 x=CLOCK_DATA_X,y=CLOCK_DATA_Y,gap=CLOCK_GAP_Y;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis();//�м��ҳ
SubModeIcon_dis(WorkMode);   //ʱ��ģʽ
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
	case INDONSIA:	//ӡ��
		Printf24("Tahun:  20",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Bulan:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("hari:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Jam:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("Menit:",x,y,BLACK_COLOR,0,0xffff);
			break;
	case PORTUGAL:	//������
		Printf24("ano:   20",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("m�� ",x,y,BLACK_COLOR,0,0xffff);
		Printf24("  s:",x,y,BLACK_COLOR,0,0xffff);y+=gap;//m��s
		Printf24("dia:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("tempo:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("minuto:",x,y,BLACK_COLOR,0,0xffff);
			break;
	case SPANISH: //������
		Printf24("ano:   20",x,y,BLACK_COLOR,0,0xffff);
		ASCII_Printf("n",ASCII24_MODE,12,24,PUTAO_ZK24,x+12,y,BLACK_COLOR,0xffff);y+=gap;
		Printf24("mes:",x,y,BLACK_COLOR,0,0xffff);y+=gap;//m��s
		Printf24("dia:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("hora:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
		Printf24("minuto:",x,y,BLACK_COLOR,0,0xffff);
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
MiddlePage_dis();//�м��ҳ
SubModeIcon_dis(WorkMode);   //����ģʽ
//���
switch(Language)
	{
	case CHN_HAN:
		Printf16("���嵱��  �������ֱ���  ˿���ݾ�",x,y,0xFc00,0,0xffff);
			break;
	case ENGLISH:	
		Printf16("Pulse-Equ  Resolution   Distance",x,y,0xFc00,0,0xffff);
			break;
	case INDONSIA:	//ӡ��
		Printf16("Pulse-setara Resolusi Screw-jarak",x-25,y,0xFc00,0,0xffff);
			break;
	case PORTUGAL:	//������	
		Printf16("Pulso-Equ  resolu??o    passo",x,y,0xFc00,0,0xffff);
		ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, x+8*17,y,0xFc00,0xffff);
			break;
	case SPANISH: //������	
		Printf16("Pulso-Equ  resoluci    paso",x,y,0xFc00,0,0xffff);
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
	case INDONSIA:	//ӡ��
		Printf16("Pulse-setara Resolusi Screw-jarak",x,y,0xFc00,0,0xffff);
			break;
	case PORTUGAL:	//������	
		Printf16("Pulso-Equ  resolu??o    passo",x,y,0xFc00,0,0xffff);
		ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, x+8*17,y,0xFc00,0xffff);
			break;
	case SPANISH: //������	
		Printf16("Pulso-Equ  resoluci    paso",x,y,0xFc00,0,0xffff);
			break;
	}
x=PULSE_SET_X1+20;
y=PULSE_SET_Y;
for(n=0;n<12;n++)
	{
	if(n==6)
	   {
	   x=PULSE_SET_X2+20;
	   y=PULSE_SET_Y+PULSE_GAP_Y;
	   }
	else
	   {
	   y+=PULSE_GAP_Y;
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
	case INDONSIA:	//ӡ��
		Printf24("Masuk Pulse setara!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
			break;
	case PORTUGAL:	//������
		Printf24("Entrada de pulso equivalente!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
			break;
	case SPANISH: //������
		Printf24("Entrada de pulsos equivalente!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
			break;
	}
x=PULSE_SET_X2-30,y=PULSE_SET_Y+20;
GLCD_DrawLine( x, y, x, y+250, BLUE_COLOR);
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
	front_color=TEXT_TAB_BACK_COLOR;
	}
if(sel>5)
	{
	x=PULSE_SET_X2+10;
	}
sel%=6;
y=PULSE_SET_Y+PULSE_GAP_Y*(sel+1);
GLCD_SetWindow( x, y, x+WW, y+HH, front_color);
}

//------------�Ե�
void SelfEnterPage_dis(void)//�Ե�ģʽ ���� ---------��ʾ
{
Int16U x,y;
Int16U front_color,back_color;
x=SELF_PROMP_X,y=SELF_PROMP_Y;
front_color=RED_COLOR,back_color=0xffff;
CurrentArea_save2(x , y,  SELF_PROMP_WIDE, SELF_PROMP_HIGH);
GLCD_SetWindow_Fill( x, y, x+SELF_PROMP_WIDE-1, y+SELF_PROMP_HIGH-1, BLUE_COLOR, 0xfffff);x+=10,y+=5;
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
	case INDONSIA:	//ӡ��
		Printf24("Modus pemotongan otomatis",x,y,front_color,1,back_color);y+=30;
		Printf24("sangat berbahaya!",x,y,front_color,1,back_color);x+=20,y+=50;
		Printf24("Ya",x,y,front_color,1,back_color);x+=130;
		Printf24("Membatal",x,y,front_color,1,back_color);
			break;
	case PORTUGAL:	//������
		Printf16("Este modo �� muito perigoso",x,y,front_color,1,back_color);y+=30;
		Printf16("Pressione o bot?o OK para entrar",x,y,front_color,1,back_color);
		ASCII_Printf("a",ASCII16_MODE,8,16,PUTAO_ZK16, x+8*15,y,front_color,back_color);x+=20,y+=50;
		Printf24("OK",x,y,front_color,1,back_color);x+=130;
		Printf24("Cancelar",x,y,front_color,1,back_color);
			break;
	case SPANISH: //������
		Printf16("Este modo es muy peligroso",x,y,front_color,1,back_color);y+=30;
		Printf16("Pulse el bot��n OK para entrar",x,y,front_color,1,back_color);x+=20,y+=50;
		Printf24("OK",x,y,front_color,1,back_color);x+=130;
		Printf24("Cancelar",x,y,front_color,1,back_color);
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
GLCD_SetWindow_Fill( x, y, x+SELF_PROMP_WIDE-1, y+SELF_PROMP_HIGH-1, BLUE_COLOR, 0xfffff);x+=20,y+=5;
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
		Printf24("Continue the last",x,y,front_color,1,back_color);y+=30;
		Printf24("Auto-Cut step?",x,y,front_color,1,back_color);x+=40,y+=50;
		Printf24("OK",x,y,front_color,1,back_color);x+=120;
		Printf24("Cancel",x,y,front_color,1,back_color);
			break;
	case INDONSIA:	//ӡ��
		Printf24("Apakah akan melanjutkan ",x,y,front_color,1,back_color);y+=30;
		Printf24("langkah-langkah sebelumnya?",x,y,front_color,1,back_color);x+=40,y+=50;
		Printf24("Ya",x,y,front_color,1,back_color);x+=130;
		Printf24("Membatal",x,y,front_color,1,back_color);
			break;
	case PORTUGAL:	//������
		Printf24("Se continuar a opera??o",x,y,front_color,1,back_color);
		ASCII_Printf("ca",ASCII24_MODE,12,24,PUTAO_ZK24, x+12*20,y,front_color,back_color);y+=30;
		Printf24("anterior?",x,y,front_color,1,back_color);x+=20,y+=50;
		Printf24("OK",x,y,front_color,1,back_color);x+=130;
		Printf24("Cancelar",x,y,front_color,1,back_color);
			break;
	case SPANISH: //������
		Printf24("Ya sea para continuar",x,y,front_color,1,back_color);//Ya sea para continuar la ejecuci��n
		y+=30;
		Printf24("la ejecuci��",x,y,front_color,1,back_color);//ejecuci��n
		Printf24("           n?",x,y,front_color,0,back_color);x+=20,y+=50;
		Printf24("OK",x,y,front_color,1,back_color);x+=130;
		Printf24("Cancelar",x,y,front_color,1,back_color);
			break;
	}

}

//---------�ŷ� ��������  --
void ServoParameter_dis(Int8U sel, Int8U flag) //���� ������ʾ
{
volatile Int16U x,y,gap;
Int16U front_color,back_color;
gap=PARA_ROW_GAP;x=PARA_START_X2+(sel/7)*PARA_COL_WIDE;
Int32U temp;
if(flag==1)
    {
	front_color=WHITE_COLOR;
	back_color=BLUE_COLOR;
	}
else
	{
	front_color=BLACK_COLOR;
	back_color=TEXT_TAB_BACK_COLOR;
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
				case INDONSIA:	//ӡ��
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//������
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //������
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("1       99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//ӡ��
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//������
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //������
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("1       99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//ӡ��
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//������
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //������
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("1       99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//ӡ��
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//������
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //������
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("1       99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//ӡ��
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//������
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //������
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("1       99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//ӡ��
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//������
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //������
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("1       99",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//ӡ��
					Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//������
					Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //������
					Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			Printf24("1       3",REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
				case INDONSIA:	//ӡ��
					Printf24("Input data (            )",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case PORTUGAL:	//������
					Printf24("Input data (            )",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
				case SPANISH: //������
					Printf24("datos Input(            )",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
Int16U back_color=TEXT_TAB_BACK_COLOR;;
 x=PARA_START_X1,y=PARA_START_Y,gap=PARA_ROW_GAP;
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis();//�м��ҳ
SubModeIcon_dis(WorkMode);   // ��C������ģʽ
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
		Printf24("Speed-diff:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Speed-inte:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		
		Printf24("Reduc-ratio:",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		Printf24("Screw_Pitch:",x,y,BLACK_COLOR,1,back_color);
			break;
	case INDONSIA:	//ӡ��
		Printf24("Lokasi-gain:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Lokasi-difer:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Lokasi-integ:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Kecepa-gain:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Kecepa-diff:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Kecepa-inte:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		
		Printf24("Rasio reduksi:",x,y,BLACK_COLOR,1,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		Printf24("Screw-jarak:",x,y,BLACK_COLOR,1,back_color);
			break;
	case PORTUGAL:	//������
		Printf24("Posi??o Gain:",x,y,BLACK_COLOR,1,back_color);
		ASCII_Printf("ca",ASCII24_MODE,12,24,PUTAO_ZK24, x+12*4,y,BLACK_COLOR,back_color);y+=gap;
		Printf24("Posi??o difer:",x,y,BLACK_COLOR,1,back_color);
		ASCII_Printf("ca",ASCII24_MODE,12,24,PUTAO_ZK24, x+12*4,y,BLACK_COLOR,back_color);y+=gap;
		Printf24("Posi??o Pontos:",x,y,BLACK_COLOR,1,back_color);
		ASCII_Printf("ca",ASCII24_MODE,12,24,PUTAO_ZK24, x+12*4,y,BLACK_COLOR,back_color);y+=gap;
		Printf24("Veloc-gain:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Veloc-diff:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Veloc-inte:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		
		Printf16("r��              ",x,y,BLACK_COLOR,1,back_color);
		Printf16("  cio de redu??o:",x,y,BLACK_COLOR,0,back_color);//r��cio
		ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, x+8*13,y,BLACK_COLOR,back_color);
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		Printf24("Screw-jarak:",x,y,BLACK_COLOR,1,back_color);
			break;
	case SPANISH: //������
		Printf24("Posici- Gain:",x,y,BLACK_COLOR,1,back_color);	//posici��n
		y+=gap;
		Printf24("Posici-Difer:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Posici-Integ:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Veloc-Gain:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Veloc-Difer:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		Printf24("Veloc-Integ:",x,y,BLACK_COLOR,1,back_color);y+=gap;
		
		Printf16("Ratio de reducci��",x,y,BLACK_COLOR,1,back_color);
		Printf16("                 n",x,y,BLACK_COLOR,0,back_color);//reducci��n
		x+=PARA_COL_WIDE;y=PARA_START_Y;
		Printf24("Screw-brea:",x,y,BLACK_COLOR,1,back_color);
			break;
	}
	 
for(n=1;n<8;n++)
	ServoParameter_dis(n, 0);
ServoParameter_dis(0, 1);
}

void PassCodePage_dis(void)  //����ģʽ ��������
{
CurrentArea_save2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
MiddlePage_dis();//�м��ҳ
SubModeIcon_dis(WorkMode);   //����ģʽ
GLCD_SetWindow_Fill(REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
switch(Language)
	{
	case CHN_HAN:
		Printf24("����������!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case ENGLISH:	
		Printf24("Enter passcode!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case INDONSIA:	//ӡ��
		Printf24("Masukkan sandi Anda",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case PORTUGAL:	//������
		Printf24("Por favor, digite uma senha",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			break;
	case SPANISH: //������
		Printf24("Introduzca la contrase?a",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
		ASCII_Printf("n",ASCII24_MODE,12,24,PUTAO_ZK24,REMIND_WINDOW_X+12*22,REMIND_WINDOW_Y+5,RED_COLOR,0xffff);
			break;
	}
	
}
void PassSet_dis(void) //���� ���ý���
{
Int16U x,y,gap;
x=PASS_TIME1_X,y=PASS_TIME1_Y,gap=PASS_TIME_GAP;

PsswordFunPic_dis(PASSWORD_FUN_PIC_X,PASSWORD_FUN_PIC_Y);//���빦��ģʽpic
switch(Language)
	{
	case CHN_HAN:
		Printf24("��һ�ιػ�����:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
			break;
	case ENGLISH:	
		Printf24("First valid days:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
			break;
	case INDONSIA:	//ӡ��
		Printf24("pertama kalinya hari:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
			break;
	case PORTUGAL:	//������
		Printf24("O n��                     ",x,y,BLACK_COLOR,0,0xffff);
		Printf24("    mero de dias eficaz 1:",x,y,BLACK_COLOR,0,0xffff);y+=gap; //n��mero
			break;
	case SPANISH: //������
		Printf24("N��              ",x,y,BLACK_COLOR,0,0xffff);//N��mero de d��as
		Printf24("  mero de d��    ",x,y,BLACK_COLOR,0,0xffff); //
		Printf24("            as 1:",x,y,BLACK_COLOR,0,0xffff);y+=gap; //
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
	case INDONSIA:	//ӡ��
		Printf24("Kedua hari:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
			break;
	case PORTUGAL:	//������
		Printf24("O n��                     ",x,y,BLACK_COLOR,0,0xffff);
		Printf24("    mero de dias eficaz 2:",x,y,BLACK_COLOR,0,0xffff);y+=gap;
			break;
	case SPANISH: //������
		Printf24("N��              ",x,y,BLACK_COLOR,0,0xffff);//N��mero de d��as
		Printf24("  mero de d��    ",x,y,BLACK_COLOR,0,0xffff); //
		Printf24("            as 2:",x,y,BLACK_COLOR,0,0xffff);y+=gap; //
			break;
	}
PassDaysSet_dis( 1, 0);
PassDaysSet_dis( 0, 1);
}

void PassDaysSet_dis(Int8U sel,Int8U flag)//�����趨
{
volatile Int16U x,y,gap;
Int16U front_color,back_color;
gap=PASS_TIME_GAP;x=PASS_TIME1_X+20;
if(flag==1)
    {
	front_color=WHITE_COLOR;
	back_color=BLUE_COLOR;
	}
else
	{
	front_color=BLACK_COLOR;
	back_color=TEXT_TAB_BACK_COLOR;
	}
y=PASS_TIME1_Y+40+gap*sel;
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
				case INDONSIA:	//ӡ��
					Printf24("Input Data,Tekan tombol Insert",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case PORTUGAL:	//������
					Printf16("Os dados de entrada, pressione a tecla Insert",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case SPANISH: //������
					Printf16("ngrese el n�� ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					Printf16("            mero de d�� ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					Printf16("                      as, pulse la tecla Insert",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			}
		x+=36;
		GLCD_SetWindow_Fill( x, y, x+144, y+24, TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
		if(FirstDayValid_flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
					Printf24("(��Ч)",x,y,front_color,1,back_color); 
						break;
				case ENGLISH:	
					Printf24("(Valid) ",x,y,front_color,1,back_color); 
						break;
				case INDONSIA:	//ӡ��
					Printf24("(Efekti) ",x,y,front_color,1,back_color); 
						break;
				case PORTUGAL:	//������ 
				case SPANISH: //������
					Printf24("(eficaz)",x,y,front_color,1,back_color); 
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
				case INDONSIA:	//ӡ��
					Printf24("(Cacat)",x,y,front_color,1,back_color); 
						break;
				case PORTUGAL:	//������
				case SPANISH: //������
					Printf24("(inv��    ",x,y,front_color,1,back_color); //inv��lido
					Printf24("     lido)",x,y,front_color,0,back_color); //inv��lido
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
				case INDONSIA:	//ӡ��
					Printf24("Input Data,Tekan tombol Insert",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case PORTUGAL:	//������
					Printf16("Os dados de entrada, pressione a tecla Insert",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				case SPANISH: //������
					Printf16("ngrese el n�� ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					Printf16("            mero de d�� ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					Printf16("                      as, pulse la tecla Insert",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
				}
			}
		x+=36;
		GLCD_SetWindow_Fill( x, y, x+144, y+24, TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
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
				case INDONSIA:	//ӡ��
					Printf24("(Efekti)  ",x,y,front_color,1,back_color); 
						break;  
				case PORTUGAL:	//������
				case SPANISH: //������
					Printf24("(eficaz)",x,y,front_color,1,back_color); 
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
				case INDONSIA:	//ӡ��
					Printf24("(Cacat)",x,y,front_color,1,back_color); 
						break;
				case PORTUGAL:	//������
				case SPANISH: //������
					Printf24("(inv��    ",x,y,front_color,1,back_color); //inv��lido
					Printf24("     lido)",x,y,front_color,0,back_color); //inv��lido
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











void Red_A_dis(Int16U x, Int16U y)//��ɫA
{
//Bmp_Decode((Int32U)RED_A_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void Red_B_dis(Int16U x, Int16U y)//��ɫB
{
//Bmp_Decode((Int32U)RED_B_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void Black_A_dis(Int16U x, Int16U y)//��ɫA
{
//Bmp_Decode((Int32U)BLACK_A_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}
void Black_B_dis(Int16U x, Int16U y)//��ɫB
{
//Bmp_Decode((Int32U)BLACK_B_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}











void Wheel0_dis(Int16U x, Int16U y)//���ֹ�0 ָʾ
{
//Bmp_Decode((Int32U)WHEEL0_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}

void Wheel1_dis(Int16U x, Int16U y)//���ֿ�1 ָʾ
{
//Bmp_Decode((Int32U)WHEEL1_sdram, x, y, (pInt16U)LCD_VRAM_BASE_ADDR);
}





//*************************ͼƬƴ�� ��ʾ
void WorkPic_dis(void)  //����������ʾ
{
volatile Int16U xp,yp,back_color;
back_color=STEP_BACK_COLOR;
FirstBack_dis();//�ײ㱳��

//TimeCol_dis(TIME_COL_X,TIME_COL_Y);//ʱ����

Schedule_dis(SCHEDULE_X,SCHEDULE_Y);//����
ProgressBar_dis(OnePro_head.pro_knifeSUM,Knife_order);  //������ ��ʾ
xp=PROG_X,yp=PROG_Y;
switch(Language)
	{
	case CHN_HAN:
		Printf24(" ����  ",xp,yp,BLACK_COLOR,1,back_color);
			break;
	case ENGLISH:	
		Printf24("Process",xp,yp,BLACK_COLOR,1,back_color);
			break;
	case INDONSIA:	//ӡ����
		Printf24("Program",xp,yp,BLACK_COLOR,1,back_color);
			break;	
	case PORTUGAL:	//������
	case SPANISH: //������
		Printf24("Programa",xp,yp,BLACK_COLOR,1,back_color);
			break;		
	}
xp=STEP_X;//
switch(Language)
	{
	case CHN_HAN:
		Printf24(" ����  ",xp,yp,BLACK_COLOR,1,back_color);//
			break;
	case ENGLISH:	
		Printf24(" Step  ",xp,yp,BLACK_COLOR,1,back_color);
			break;
	case INDONSIA:	//ӡ����
		Printf24("Langkah",xp,yp,BLACK_COLOR,1,back_color);
			break;
	case PORTUGAL:	//������
		Printf24("Passo",xp,yp,BLACK_COLOR,1,back_color);
			break;	
	case SPANISH: //������
		Printf24("Paso",xp,yp,BLACK_COLOR,1,back_color);
			break;	
	}
OneProNum_dis(Pro_data.pro_num, OnePro_head);// �����
StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);// �����  �ܵ���-���

//Order_dis(ORDER_X,ORDER_Y);//���
//Position_dis(POSITION_X,POSITION_Y);//λ��
//PushKnife_dis(PUSH_KNIFE_X,PUSH_KNIFE_Y);//��ֽ������

//PushPaperTool_dis(PUSH_PAPER_TOOL_X,PUSH_PAPER_TOOL_Y);//��ֽ��
CurrentSize_dis(CurrentSize); //��ǰ�ߴ� ������ʾ
CurrUint_dis(Unit);  //��ǰ�ߴ� ��λ


//Knife_Up_dis(KNIFE_X,KNIFE_Y);//����
//Press_Up_dis(PRESS_UP_X,PRESS_UP_Y);//ѹ��

//Red_A_dis(RED_A_X,RED_A_Y);//��A
//Red_B_dis(RED_B_X,RED_B_Y);//��B
//Hand_IR_dis(HAND_IR_X,HAND_IR_Y);//�ֺ���

//ElectricalWheel_dis();  //��������  ����״̬

//FrontPage_Up_dis( FRONT_PAGE_X,  FRONT_PAGE_Y);//ǰһҳup
//BackPage_Up_dis( BACK_PAGE_X,  BACK_PAGE_Y);//��һҳup
//UpArrow_Up_dis( UP_ARROW_X,  UP_ARROW_Y);//�ϼ�ͷup
//DownArrow_Up_dis( DOWN_ARROW_X,  DOWN_ARROW_Y);//�¼�ͷup
//��ģʽ ---
MainModeIcon_dis(WorkMode);//���ģʽ..............

//InputSize_dis(INPUT_SIZE_X,INPUT_SIZE_Y);//����ߴ�
//Remind_dis(REMIND_X,REMIND_Y); //��ʾ��
TextWindow_dis();   //��ɫ�ı���

//Cancel_Up_dis(CANCEL_X,CANCEL_Y);//ȡ��up
//Enter_Up_dis(ENTER_X,ENTER_Y);//ȷ��up
//Run_Up_dis(RUN_X,RUN_Y);//����up
//Stop_Up_dis(STOP_X,STOP_Y);//ֹͣup
//Delete_Up_dis( DELETE_X, DELETE_Y );//ɾ��up
//DeleteAll_Up_dis( DELETE_ALL_X, DELETE_ALL_Y);//ȫɾup
//ShiftButtonUp_dis(SHIFT_BUTT_X,SHIFT_BUTT_Y);	//shift�ϵ� ��ť
}

void PromptNum_dis(void)  //�������ݷ�Χ ��ʾ
{
Int8U num[15],str1[8],str2[8],i,j;
Int16U x,y;
i=0;
Int32U max,min;
if(Run_flag==1)
	{
	if((WorkMode==AUTO_MODE)||(WorkMode==SELF_CUT_MODE))  //�Զ� �Ե� ģʽ
		{
		GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
		switch(Language)
			{
			case CHN_HAN:
				Printf24("��'ֹͣ��'ֹͣ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
			case ENGLISH:	
				Printf24("Press 'STOP' to stop it!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
			case INDONSIA:	//ӡ����
				Printf24("Tekan 'berhenti tombol' Berhenti",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
					break;
			case PORTUGAL:	//������
				Printf16("Pressione 'bot?o de parada de' Stop!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
				ASCII_Printf("a",ASCII16_MODE,8,16,PUTAO_ZK16, REMIND_WINDOW_X+10+8*14,REMIND_WINDOW_Y+5,BLACK_COLOR,0xffff);
					break;
			case SPANISH: //������
				Printf16("Pulse el bot�� ",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
				Printf16("             n de parada!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
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
		case INDONSIA:	//ӡ��
			Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
				break;
		case PORTUGAL:	//������
			Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
			break;
		case SPANISH: //������
			Printf16("Rango de datos               --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
				break;
		}

	x=REMIND_WINDOW_X+180,y=REMIND_WINDOW_Y+5;
	Printf24(str1,x,y,RED_COLOR,0,0xffff);
	Printf24(str2,x+120,y,RED_COLOR,0,0xffff);
	}

}


void TextWindow_dis(void)  //�ı������
{
// GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ�����
GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//�ߴ�����
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
		gap1=55,gap2=120;
		F1LabelIconUp_dis(x,y);//F1
		x+=gap1;
		Printf24("��ǩ",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		F2DivideIconUp_dis(x,y);
		x+=gap1;
		Printf24("�ȷ�",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		F3ProjectIconUp_dis(x,y);
		x+=gap1;
		Printf24("����",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		PushPaperF_dis(x,y);//�л���ťup
		x+=gap1;
		Printf24("��ֽ���",x,y+20,BLACK_COLOR,0,0xffff);

		// x+=gap2;
		
		
		//*********************�ڶ���
		x=start_x+gap;y+=70;
		gap1=55,gap2=120;
		
		F1RulerIconUp_dis(x,y);
		x+=gap1;
		Printf24("��׼",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		F2ParamaterIconUp_dis(x,y);
		x+=gap1;
		Printf24("����",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		F3ClockIconUp_dis(x,y);
		x+=gap1;
		Printf24("ʱ��",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		F3AddIconUp_dis(x,y);
		x+=gap1;
		Printf24("�Լ�",x,y+20,BLACK_COLOR,0,0xffff);
		
		
		
		//*********************������
		x=start_x+gap;y+=70;
		gap1=50,gap2=110;
		F4SubIconUp_dis(x,y);
		x+=gap1;
		Printf24("�Լ�",x,y+20,BLACK_COLOR,0,0xffff);
		
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
		Printf24("����",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		FrontPage_Up_dis(x,y);
		x+=gap1;
		Printf24("ǰ��",x,y+20,BLACK_COLOR,0,0xffff);
		
		//*********************������
		x=start_x+gap;y+=70;
		gap1=50,gap2=110;
		L_R_Arrow_dis(x,y);
		x+=gap1;
		Printf24("�л�",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
	//	Fkey_Up_dis(x,y);
		ShiftButtonUp_dis(x,y);	//shift�ϵ�
		x+=gap1;
		Printf24("shift��",x+20,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		IR_CUT_dis(x,y);
		x+=gap1;
		Printf24("�����",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		IR_LINE_dis(x,y);// FrontKnife_dis(x,y);
		x+=gap1;
		// Printf24("��ǰ",x,y+20,BLACK_COLOR,0,0xffff);
		Printf24("����ͨ",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		RedKnifeF_dis(x,y);
		x+=gap1;
		Printf24("����־",x,y+20,BLACK_COLOR,0,0xffff);
		
		//*********************������
		x=start_x+gap;y+=70;
		gap1=50,gap2=110;
		// Red_A_dis(x,y);
		F5CutIcon_Up_dis(x,y);
		x+=gap1;
		// Printf24("A�ź�",x,y+20,BLACK_COLOR,0,0xffff);
		Printf24("F5�����",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		// Red_B_dis(x,y);
		F0CutAllIcon_Up_dis(x,y);
		x+=gap1;
		// Printf24("B�ź�",x,y+20,BLACK_COLOR,0,0xffff);
		Printf24("F0ȫ���",x,y+20,BLACK_COLOR,0,0xffff);
		
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
		
		// gap1=140;
		
		// PulseDegree_dis(x,y);
	//	F4LabelDesert_Up_dis(x,y);
		// x+=gap1;
		// Printf24("��ǩ�ϱ�",x,y+5,BLACK_COLOR,0,0xffff);
		x+=gap2;
		F4Wheel1_dis(x,y);
		x+=gap1;
		Printf24("���ֿ�",x,y+20,BLACK_COLOR,0,0xffff);
		
		//*********************������
		x=start_x+gap;y+=50;
		gap1=90,gap2=80;
		// // Wheel0_dis(x,y);
	//	F3LabelTime_Up_dis(x,y);
		// x+=gap1;
		// Printf24("��ǩ����",x,y+5,BLACK_COLOR,0,0xffff);
		F1OkIconUp_dis(x,y);
		x+=gap1;
		Printf24("���",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		F2ExitIconUp_dis(x,y);
		x+=gap1;
		Printf24("�˳�",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		FastFWD_Up_dis(x,y);
		x+=gap1;
		Printf24("���",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		FastBACK_Up_dis(x,y);
		x+=gap1;
		Printf24("����",x,y+20,BLACK_COLOR,0,0xffff);
		
		//------------ҳ��
		Printf24("1/2 ҳ",350,550,BLACK_COLOR,1,0xffff);
		Printf24("��һҳ",F2_PAGE_UP_X,F2_PAGE_UP_Y,BLUE_COLOR,1,0xffff);
		Printf24("��һҳ",F2_PAGE_DOWN_X,F2_PAGE_DOWN_Y,BLUE_COLOR,1,0xffff);
		Printf24("���ء�",F2_RET_HELP_X,F2_RET_HELP_Y,BLUE_COLOR,1,0xffff);
		break;
	 case 1:
		x=start_x+gap,y=start_y+gap;
		gap1=55,gap2=100;
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
		RightArrow_dis(x,y);
		x+=gap1;
		Printf24("���",x,y+20,BLACK_COLOR,0,0xffff);
		//*********************�ڶ���
		x=start_x+gap;y+=70;
		gap1=60,gap2=110;
		// Program_dis(x,y);
		F4DeleteOneProIconUp_dis(x,y);
		x+=gap1;
		Printf24("ɾ������",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		F5DeleteAllProIconUp_dis(x,y);
		x+=gap1;
		Printf24("ɾ������",x,y+20,BLACK_COLOR,0,0xffff);
		
		
		x+=gap2;
		F6Amend1_dis(x,y);
		x+=gap1;
		Printf24("ƫ����Ч",x,y+20,BLACK_COLOR,0,0xffff);
				
		x+=gap2;
		F6Amend0_dis(x,y);
		x+=gap1;
		Printf24("ƫ����Ч",x,y+20,BLACK_COLOR,0,0xffff);

		//*********************������
		x=start_x+gap;y+=80;
		F1ShowMessIconUp_dis(x,y);
		x+=gap1;
		Printf24("���뷨",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		F1PinyinIconUp_dis(x,y);
		x+=gap1;
		Printf24("ƴ������",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		F2CharIconUp_dis(x,y);
		x+=gap1;
		Printf24("��ĸ����",x,y+20,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		F3NumIconUp_dis(x,y);
		x+=gap1;
		Printf24("��������",x,y+20,BLACK_COLOR,0,0xffff);

		//*********************������
		x=start_x+gap;y+=80;
		F3ByNumIconUp_dis(x,y);
		x+=gap1;
		Printf24("˳������",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		F2ByTimeIconUp_dis(x,y);
		x+=gap1;
		Printf24("��������",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		EnterButtUp_dis(x,y);
		x+=gap1;
		Printf24("ȷ��",x,y+20,BLACK_COLOR,0,0xffff);

		x+=gap2;
		F6ExitButtUp_dis(x,y);
		x+=gap1;
		Printf24("�˳�",x,y+20,BLACK_COLOR,0,0xffff);

		//*********************������
		x=start_x+gap;y+=80;
		F4PulseSetIconUp_dis(x,y);
		x+=gap1;
		Printf24("���嵱��",x,y+20,BLACK_COLOR,0,0xffff);
/****
		x+=gap2;
		// // SelectPro_dis(x,y);
		x+=gap1;
		Printf24("ѡ�����",x,y+35,BLACK_COLOR,0,0xffff);
		
		x+=gap2;
		// // Lock_dis(x,y);
		x+=gap1;
		Printf24("����ģʽ",x,y+35,BLACK_COLOR,0,0xffff);		
		
		//*********************������
		x=start_x+gap;y+=80;
		gap1=90,gap2=80;
		// // Wheel1_dis(x,y);
		x+=gap1;
		Printf24("���ֿ�",x,y+5,BLACK_COLOR,0,0xffff);

		**/
		
		
		//*********************������
		x=start_x+gap;y+=70;
		
		//------------ҳ��
		Printf24("2/2 ҳ",350,550,BLACK_COLOR,1,0xffff);
		Printf24("��һҳ",F2_PAGE_UP_X,F2_PAGE_UP_Y,BLUE_COLOR,1,0xffff);
		Printf24("��һҳ",F2_PAGE_DOWN_X,F2_PAGE_DOWN_Y,BLUE_COLOR,1,0xffff);
		Printf24("���ء�",F2_RET_HELP_X,F2_RET_HELP_Y,BLUE_COLOR,1,0xffff);

		 break;	
	 }

}


void CurrentArea_save1(Int16U x,Int16U y, Int16U Wide,Int16U High)//�ݴ�  ��ǰ���� ����1
{
pInt16U pDis,pBuf;
volatile Int16U h,w;
pDis=(pInt16U)(LCD_VRAM_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
pBuf=(pInt16U)PIC_DIS_SAVE1;
for(h=0;h<High;h++)
  {
  for(w=0;w<Wide;w++)
    {
	*pBuf++=*pDis++;
	}
	y++;
	pDis=(pInt16U)(LCD_VRAM_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
  }
}
void CurrentArea_recover1(Int16U x, Int16U y, Int16U Wide,Int16U High)//�ָ�  ��ǰ���� ����1
{
pInt16U pDis,pBuf;
volatile Int16U h,w;
pDis=(pInt16U)(LCD_VRAM_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
pBuf=(pInt16U)PIC_DIS_SAVE1;
for(h=0;h<High;h++)
  {
  for(w=0;w<Wide;w++)
    {
	*pDis++=*pBuf++;
	}
	y++;
	pDis=(pInt16U)(LCD_VRAM_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
  }
}

void CurrentArea_save2(Int16U x,Int16U y, Int16U Wide,Int16U High)//�ݴ�  ��ǰ���� ����2
{
pInt16U pDis,pBuf;
volatile Int16U h,w;
pDis=(pInt16U)(LCD_VRAM_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
pBuf=(pInt16U)PIC_DIS_SAVE2;
for(h=0;h<High;h++)
  {
  for(w=0;w<Wide;w++)
    {
	*pBuf++=*pDis++;
	}
	y++;
	pDis=(pInt16U)(LCD_VRAM_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
  }
}
void CurrentArea_recover2(Int16U x, Int16U y, Int16U Wide,Int16U High)//�ָ�  ��ǰ���� ����2
{
pInt16U pDis,pBuf;
volatile Int16U h,w;
pDis=(pInt16U)(LCD_VRAM_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
pBuf=(pInt16U)PIC_DIS_SAVE2;
for(h=0;h<High;h++)
  {
  for(w=0;w<Wide;w++)
    {
	*pDis++=*pBuf++;
	}
	y++;
	pDis=(pInt16U)(LCD_VRAM_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
  }
}

void CurrentArea_save3(Int16U x,Int16U y, Int16U Wide,Int16U High)//�ݴ�  ��ǰ���� ����3
{
pInt16U pDis,pBuf;
volatile Int16U h,w;
pDis=(pInt16U)(LCD_VRAM_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
pBuf=(pInt16U)PIC_DIS_SAVE3;
for(h=0;h<High;h++)
  {
  for(w=0;w<Wide;w++)
    {
	*pBuf++=*pDis++;
	}
	y++;
	pDis=(pInt16U)(LCD_VRAM_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
  }
}
void CurrentArea_recover3(Int16U x, Int16U y, Int16U Wide,Int16U High)//�ָ�  ��ǰ���� ����3
{
pInt16U pDis,pBuf;
volatile Int16U h,w;
pDis=(pInt16U)(LCD_VRAM_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
pBuf=(pInt16U)PIC_DIS_SAVE3;
for(h=0;h<High;h++)
  {
  for(w=0;w<Wide;w++)
    {
	*pDis++=*pBuf++;
	}
	y++;
	pDis=(pInt16U)(LCD_VRAM_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
  }
}

void CurrentArea_save4(Int16U x,Int16U y, Int16U Wide,Int16U High)//�ݴ�  ��ǰ���� ����4
{
pInt16U pDis,pBuf;
volatile Int16U h,w;
pDis=(pInt16U)(LCD_VRAM_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
pBuf=(pInt16U)PIC_DIS_SAVE4;
for(h=0;h<High;h++)
  {
  for(w=0;w<Wide;w++)
    {
	*pBuf++=*pDis++;
	}
	y++;
	pDis=(pInt16U)(LCD_VRAM_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
  }
}
void CurrentArea_recover4(Int16U x, Int16U y, Int16U Wide,Int16U High)//�ָ�  ��ǰ���� ����4
{
pInt16U pDis,pBuf;
volatile Int16U h,w;
pDis=(pInt16U)(LCD_VRAM_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
pBuf=(pInt16U)PIC_DIS_SAVE4;
for(h=0;h<High;h++)
  {
  for(w=0;w<Wide;w++)
    {
	*pDis++=*pBuf++;
	}
	y++;
	pDis=(pInt16U)(LCD_VRAM_BASE_ADDR+(y*C_GLCD_H_SIZE+x)*2);
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
back_color=CURREN_STEP_BACK_COLOR;
if(Unit!=UNIT_MM)//inch
	{
	//if(SelfLockEn_flag==1)  //����
		//{
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST:
			case MOTOR_FREQ_3_SPD:
			case MOTOR_FREQ_3_SPD_RST:
					 Virture_size=VirtualTargetSizeGap;
					break;
			case MOTOR_DC_SERVO:
			case MOTOR_DC670_SERVO:
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
// Printf32(num,x,y,0,1,back_color);
//ASCII_Printf(num,224+1,28,56,ASCII_28x56, x,y,0xffff,back_color);
//ASCII_Printf(num,192+1,32,48,ASCII_32x48, x,y,0,back_color);
// ASCII_Printf(num,64+1,16,32,ASCII_bold16x32, x,y,0,back_color);
ASCII_Printf(num,120+1,24,40,ASCII_bold24x40, x,y,0,back_color);

}


void FrontKnifeUint_dis(Int8U unit)  //��ǰ�ߴ� ��λ--------------
{
Int16U x,y,back_color=CURREN_UNIT_BACK_COLOR;
x=FRONT_KNIF_X+200;
y=45;//FRONT_KNIF_Y+5;
GLCD_SetWindow_Fill(x, y, x+40, y+25, back_color, back_color);
if(unit==UNIT_MM)//mm
   {
   Printf24("mm",x,y,WHITE_COLOR,1,back_color);
   }
else
   {
   Printf24("in",x,y,WHITE_COLOR,1,back_color);
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
}

void FrontKnifeSize_dis(Int32U size)//��ǰ�ߴ�-----------------
{
Int8U num[8],k;
Int16U x,y,back_color=FRONT_KNIFE_BACK_COLOR;
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
Printf32(num,x,y,BLACK_COLOR,1,back_color);
//ASCII_Printf(num,108+1,20,36,ASCII_20x36, x,y,0,back_color);
}
void FrontKnifeSize_NOdis(void)
{
Int16U x,y,back_color=FRONT_KNIFE_BACK_COLOR;
x=FRONT_KNIF_X;
y=FRONT_KNIF_Y;
GLCD_SetWindow_Fill(x-1, y, x+140, y+36, back_color, back_color);
}


void InputNum_dis(pInt8U nums,Int8U cou) //�������  �ߴ�������ʾ
{
Int8U num_temp[8],n=0;
Int16U x,y,back_color,f_color;
back_color=WHITE_COLOR;f_color=0;
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
// Printf24(num_temp,SIZE_WINDOW_X+25,SIZE_WINDOW_Y+5,BLACK_COLOR,1,0xffff);
x=SIZE_WINDOW_X+SIGN_2WIDE;	y=SIZE_WINDOW_Y+5;
ASCII_Printf(num_temp,108+1,20,36,ASCII_20x36, x,y,f_color,back_color);
}

void CursorPro_dis(Int8U row, Int8U show_flag)// ����� ��ɫ��ͷ ���
{
Int16U x,y,back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
if(row<PROGS_1PAGE)
   {
   TableDis_startcol=RIGHT_ARROW_X;
   }
else
   {
   TableDis_startcol=RIGHT_PAGE_X;
   }
x=TableDis_startcol;
y=RIGHT_ARROW_Y+(row%PROGS_1PAGE)*PROTEXT_HIGH+10;
if(show_flag==1)//��ʾ
   {
   RightArrow_dis(x,y);
   }
else
   {
   GLCD_SetWindow_Fill( x, y, x+32, y+32, back_color, back_color);//��ʧ
   }
}

void ProgOrder_dis(Int16U row, Int16U order,Int16U num_color)//һ�� �����--------��ʾ
{
Int8U num[5],k;
Int16U x,y,back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
if(row<PROGS_1PAGE)
   {
   TableDis_startcol=PROC_NUM_X;
   }
else
   {
   TableDis_startcol=RIGHT_PAGE_X+25;	//xxxxxxxxxxxx
   }
x=TableDis_startcol;
y=PROC_NUM_Y+(row%PROGS_1PAGE)*PROTEXT_HIGH;

num[0]=order/100;
num[1]=(order/10)%10;
num[2]=order%10;
num[3]=0;
for(k=0;k<3;k++)
  {
  num[k]+=48;
  }
Printf32(num,x,y,num_color,1,back_color);//���
//ASCII_Printf(num,114+1,18,38,ASCII_bold18x38, x,y,num_color,back_color);
}
void ProgName_dis(Int16U row, PROCESS_HEAD pro_head,Int16U num_color)//-----------------------��ʾһ��������
{
Int8U k=0,check=0;
Int16U x,y,back_color=TEXT_TAB_BACK_COLOR,x2;//0xef9f;
pInt8U pName;
pName=pro_head.pro_name_flag;
if(row<PROGS_1PAGE)
   {
   TableDis_startcol=PROC_NAME_X;
   }
else
   {
   TableDis_startcol=RIGHT_PAGE_X+25;	//xxxxxxxxxxxx
   }
x=TableDis_startcol;
y=PROC_NAME_Y+(row%PROGS_1PAGE)*PROTEXT_HIGH;
while(*(NAME_flag+k)!='\0')
	{
	if(*(NAME_flag+k)==*(pName+k))
		check++;
	else
		break;
	k++;
	}
x2=PROC_STEP_X-80;
//***********��ʾ ��������
pName=pro_head.pro_name;
GLCD_SetWindow_Fill(x, y, x2, y+PROTEXT_HIGH, back_color, back_color);//�������
if(check>=4)	//if(*pName!=0)//������
	{
	//���Ƴ���-----
	k=0;
	while(*(pName+k)!='\0')
		{
		k++;
		if(k>20)
			{
			*(pName+k)='\0';
			*(pName+k-1)='.';
			*(pName+k-2)='.';
			*(pName+k-3)='.';
			break;
			}
		}
	Printf24(pName,x,y,num_color,1,back_color);//��ʾ����
	}
}
void ProgStep_dis(Int16U row, PROCESS_HEAD pro_head,Int16U num_color)//-----------------------��ʾ������
{
Int8U num[5],k;
Int16U x,y,back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
Int16U step;
step=pro_head.pro_knifeSUM;
if(row<PROGS_1PAGE)
   {
   TableDis_startcol=PROC_STEP_X;
   }
else
   {
   TableDis_startcol=RIGHT_PAGE_X+25;	//xxxxxxxxxxxx
   }
x=TableDis_startcol;
y=PROC_STEP_Y+(row%PROGS_1PAGE)*PROTEXT_HIGH;

num[0]=step/100;
num[1]=(step/10)%10;
num[2]=step%10;
num[3]=0;
for(k=0;k<3;k++)
  {
  num[k]+=48;
  }
Printf32(num,x,y,num_color,1,back_color);//
}
void ProgDate_dis(Int16U row, PROCESS_HEAD pro_head,Int16U num_color)//-----------------------��ʾ����
{
Int8U num[12],k;
Int8U year,month,day;
Int16U x,y,back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
if(row<PROGS_1PAGE)
   {
   TableDis_startcol=PROC_DATE_X;
   }
else
   {
   TableDis_startcol=RIGHT_PAGE_X+25;	//xxxxxxxxxxxx
   }
x=TableDis_startcol;
y=PROC_DATE_Y+(row%PROGS_1PAGE)*PROTEXT_HIGH;

year=pro_head.pro_year;
month=pro_head.pro_month;
day=pro_head.pro_day;
k=0;
if(year==0&&month==0&&day==0)
	{
	num[k++]='0';
	}
else
	{
	num[k++]='2';
	}
num[k++]='0';
num[k++]=((year>>4)&0xf)+48;
num[k++]=(year&0xf)+48;
num[k++]='-';
num[k++]=((month>>4)&0xf)+48;
num[k++]=(month&0xf)+48;
num[k++]='-';
num[k++]=((day>>4)&0xf)+48;
num[k++]=(day&0xf)+48;
num[k++]=0;
Printf32(num,x,y,num_color,1,back_color);//
}

void CursorKnife_dis(Int8U row, Int8U show_flag)// ������ ��ɫ��ͷ ���
{
Int16U x,y,back_color=TEXT_TAB_BACK_COLOR;
if(row>(PageKf_Size-1))
   {
   TableDis_startcol=RIGHT_PAGE_X;
   }
else
   {
   TableDis_startcol=RIGHT_ARROW_X;
   }
x=TableDis_startcol;
y=RIGHT_ARROW_Y+(row%PageKf_Size)*Kf_Line_HIGH;
if(show_flag==1)//��ʾ
   {
   RightArrow_dis(x,y);
   }
else
   {
   // GLCD_SetWindow_Fill( x, y, x+15, y+15, back_color, back_color);//��ʧ
   GLCD_SetWindow_Fill( x, y, x+32, y+SIZEWORD_HIGH, back_color, back_color);//��ʧ
   }
}

void KnifeOrder_dis(Int16U row, Int16U order,Int16U num_color)//-----------------------��ʾһ�����
{
Int8U num[5],k;
Int16U x,y,back_color=TEXT_TAB_BACK_COLOR;
if(row>(PageKf_Size-1))
   {
   TableDis_startcol=RIGHT_PAGE_X;
   }
else
   {
   TableDis_startcol=RIGHT_ARROW_X;
   }
x=TableDis_startcol+ARROW_WIDE;
y=RIGHT_ARROW_Y+(row%PageKf_Size)*Kf_Line_HIGH;

num[0]=order/100;
num[1]=(order/10)%10;
num[2]=order%10;
num[3]=0;
for(k=0;k<3;k++)
  {
  num[k]+=48;
  }
//Printf32(num,x,y,num_color,1,back_color);//���
//===============
if(num_color==RED_COLOR)
	{
	back_color=TEXT_TAB_FRONT_COLOR;
	num_color=0;
	}
else
	{
	GLCD_SetWindow_Fill( x, y, x+100, y+SIZEWORD_HIGH, TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);
	}
// ASCII_Printf(num,114+1,18,38,ASCII_bold18x38, x,y,num_color,back_color);
ASCII_Printf(num,64+1,16,32,ASCII_bold16x32, x,y,num_color,back_color);
}

void KnifeSize_dis(Int16U row,  Int32U Knife_size,Int16U num_color)//--------------��ʾһ���ߴ�
{
Int8U num[8],k;
Int16U x,y,back_color=TEXT_TAB_BACK_COLOR;
Int32U size_inc;
if(row>(PageKf_Size-1))
   {
   TableDis_startcol=RIGHT_PAGE_X;
   }
else
   {
   TableDis_startcol=RIGHT_ARROW_X;
   }  
x=TableDis_startcol+120;//95;
y=RIGHT_ARROW_Y+(row%PageKf_Size)*Kf_Line_HIGH;

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

//===============
if(num_color==RED_COLOR)
	{
	back_color=TEXT_TAB_FRONT_COLOR;
	num_color=0;
	}

//Printf32(num,x,y,BLACK_COLOR,1,back_color);//�ߴ���ʾ
// ASCII_Printf(num,120+1,24,40,ASCII_bold24x40, x,y,num_color,back_color);
ASCII_Printf(num,64+1,16,32,ASCII_bold16x32, x,y,num_color,back_color);
}

void AllFlagPic_dis(Int8U row,  Int8U Knife_flag)//-------(2��)  ��־��ʾ
{
Int16U x1,y1,x2,y2,back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
x1=RED_KNIFE_PIC_X;
y1=RIGHT_ARROW_Y+10+row*Kf_Line_HIGH;
x2=TABLE_END_COL;
y2=y1+30;
GLCD_SetWindow_Fill(x1, y1, x2, y2, back_color, back_color);//ͼ����ʧ

switch(Knife_flag&0x0F)
	{
	case PUSH_FLAG:  //��ֽͼ����ʾ
		PushPaperF_dis(x1,y1);
			break;
	case SORT_FLAG:   // ��ֽ
		//SortPaperF_dis(x1,y1);
			break;
	case CRASH_FLAG:   // ײֽ
		//CrashPaperF_dis(x1,y1);
			break;		
	case KNIFE_FLAG:  //��ͼ��		
		RedKnifeF_dis(x1,y1);
			break;		
	}
	
if((Knife_flag&0xF0)==AIR_FLAG)  //����  ��־λ
	{
	x1=AIR_FLAG_PIC_X;
	//AirBedF_dis(x1,y1);
	}
}

Int8U OneKnifeDataSel_dis(Int16U knife,Int8U row,Int16U num_color)  //һ������ ������ʾ
{
KNIFE_DATA Knife_datas;
Int16U x,y,back_color=TEXT_TAB_BACK_COLOR;
GetOneKnife_datas(Pro_data.pro_num, knife , (pInt8U)&Knife_datas);//ȡ��һ�� ����
//===============
if(row>(PageKf_Size-1))
   {
   TableDis_startcol=RIGHT_PAGE_X;
   }
else
   {
   TableDis_startcol=RIGHT_ARROW_X;
   }
x=TableDis_startcol+ARROW_WIDE;
y=RIGHT_ARROW_Y+(row%PageKf_Size)*Kf_Line_HIGH;
if(num_color==RED_COLOR)
	back_color=TEXT_TAB_FRONT_COLOR;
GLCD_SetWindow_Fill( x, y, x+100, y+SIZEWORD_HIGH, back_color, back_color);
//===============
KnifeOrder_dis(row, knife,num_color);//���
//-----------------����(�ߴ�)���� �ж� 
// if((Knife_datas.size<Size_MIN_num)||(Knife_datas.size>Size_MAX_num))
if(0)		//*****************************************************************2015--12--31---
	{
	Knife_datas.size=0;
	Knife_datas.k_flag=0;
	if(OnePro_head.pro_knifeSUM>=knife)
		{
		if(knife>1)
			OnePro_head.pro_knifeSUM=knife-1;
		else
			OnePro_head.pro_knifeSUM=1;
		Knife_sum_before=OnePro_head.pro_knifeSUM;
		SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);	//����**
		StepNum_dis(OnePro_head.pro_knifeSUM, knife);//�������
		}
	}
if(knife>OnePro_head.pro_knifeSUM)	//���һ������ ֮���������� �����
	{
	if(Knife_datas.size>0)
		{
		Knife_datas.size=0;
		Knife_datas.k_flag=0;
		}
	}	
KnifeSize_dis(row,  Knife_datas.size, num_color);//--------------��ʾһ���ߴ�
return Knife_datas.k_flag;
}

void OneProNum_dis(Int16U pro_order, PROCESS_HEAD pro_head) //���������ʾ
{
Int16U x,y,back_color,line_color;//=0x2E3B;
Int8U num[4],k=0,check=0;
pInt8U pName=pro_head.pro_name_flag;
back_color=STEP_BACK_COLOR;
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
x=PRO_NAME_DIS_X, y=PRO_NAME_DIS_Y;
line_color=back_color=PRO_NAME_DIS_COLOR;
//***********��ʾ ��������
k=0;
while(*(NAME_flag+k)!='\0')
	{
	if(*(NAME_flag+k)==*(pName+k))
		check++;
	else
		break;
	k++;
	}
GLCD_SetWindow_Fill(x, y, x+(PRONAME_SIZE*12), y+32, line_color, back_color);//�������
if(check>=4)//������
	{
	pName=pro_head.pro_name;
	line_color=GREEN_COLOR;
	Printf24(pName,x,y,line_color,1,back_color);//��ʾ����
	}
}

void StepNum_dis(Int16U step_sum,Int16U step_order) //���������ʾ(�ܵ���-����)
{
Int16U x,y,back_color;//=0x2E3B;
Int8U num[8],k;
back_color=STEP_BACK_COLOR;//----------
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
if(ButtonTouch_mode==0)  //	 �� ���������� ��
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
Int16U x,y,back_color;//=0x2E3B;
Int8U num[4],k;
back_color=STEP_BACK_COLOR;//----------
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
if(ButtonTouch_mode==0)  //	 �� ���������� ��
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
			ProgressBar_dis(OnePro_head.pro_knifeSUM,Knife_order);  //������ ��ʾ
			break;
		}	
	}
}










void MoveForward(void)//ǰ��
{
MotorRun_flag=1;
switch(MotorType)
	{
	case MOTOR_FREQ_5_SPD_RST: //----5���� 
		RLOUT3_ON;   //   ���˶Ͽ�
		RLOUT2_OFF;  //   ǰ���պ�
		
		RLOUT5_OFF;  //   ɲ���պ�------------5��
		break;
	case MOTOR_FREQ_3_SPD: //----3 ����	
	case MOTOR_FREQ_3_SPD_RST: //----3 ����+��λ	
		RLOUT2_OFF; // RLOUT3_OFF; //   ɲ���պ�
		OOUT2_OFF;  //	ǰ�� �պ�
		OOUT1_ON;  //  ���� �Ͽ�
		
		break;
	}

if(SelfLockEn_flag == 0) //  δ��λ--
	RLOUT1_ON;    // ������жϿ�
else
	{
	// if(PressDown_flag == 0)// ѹֽ δ��			20170927
		// RLOUT1_ON;    // ������жϿ�
	}
CutPermit_flag=0;	
}
void MoveBack(void) //����
{
MotorRun_flag=1;
switch(MotorType)
	{
	case MOTOR_FREQ_5_SPD_RST: //----5����
		RLOUT3_OFF;//   ���˱պ�
		RLOUT2_ON;

		RLOUT5_OFF;  //   ɲ���պ�------------5��
		break;
	case MOTOR_FREQ_3_SPD: //----3 ����	
	case MOTOR_FREQ_3_SPD_RST: //----3 ����+��λ	
		RLOUT2_OFF; // RLOUT3_OFF; //   ɲ���պ�
		OOUT1_OFF;  //	���� �պ�
		OOUT2_ON;  //  ǰ�� �Ͽ�
		
		break;
	}	

if(SelfLockEn_flag == 0) //  δ��λ--
	RLOUT1_ON;    // ������жϿ�
else
	{
	// if(PressDown_flag == 0)// ѹֽ δ��			20170927
		// RLOUT1_ON;    // ������жϿ�
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
			RLOUT1_OFF; RLOUT1_1_OFF;   // �������	
			}
		break;
	case MOTOR_FREQ_3_SPD: //----3 ����	
	case MOTOR_FREQ_3_SPD_RST: //----3 ����+��λ
		if(Wheel_limit==0)
			{
			RLOUT2_ON;  //RLOUT3_ON;  //   ɲ���Ͽ�
			RLOUT1_OFF; RLOUT1_1_OFF;   // �������	
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
			case MOTOR_FREQ_5_SPD_RST: //----5 ����
				OOUT1_ON;
				OOUT3_ON;
				OOUT4_OFF;  
					break;
			case MOTOR_FREQ_3_SPD: //----3 ����	
			case MOTOR_FREQ_3_SPD_RST: //----3 ����+��λ		
				OOUT3_ON;
				OOUT4_OFF; 
					break;
			}
		//RLOUT1_ON;    // ������жϿ�
			break;
	case 2: //�и���
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST: //----5 ����
				OOUT1_ON;
				OOUT3_OFF;
				OOUT4_OFF;  
					break;
			case MOTOR_FREQ_3_SPD: //----3 ����	
			case MOTOR_FREQ_3_SPD_RST: //----3 ����+��λ		
				OOUT3_OFF;
				OOUT4_OFF; 
					break;
			}
		//RLOUT1_ON;    // ������жϿ�
			break;	
	case 3: //����
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST: //----5 ����
				OOUT1_OFF;
				OOUT3_OFF;
				OOUT4_ON;  
					break;
			case MOTOR_FREQ_3_SPD: //----3 ����	
			case MOTOR_FREQ_3_SPD_RST: //----3 ����+��λ		
				//OOUT3_OFF;
				//OOUT4_OFF; 
				OOUT3_OFF;
				OOUT4_ON;
					break;
			}
		//RLOUT1_ON;    // ������жϿ�
			break;
	case 4: //����
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST: //----5 ����
				OOUT1_ON;
				OOUT3_OFF;
				OOUT4_ON;  
					break;
			case MOTOR_FREQ_3_SPD: //----3 ����	
			case MOTOR_FREQ_3_SPD_RST: //----3 ����+��λ		
				OOUT3_OFF;
				OOUT4_ON; 
					break;
			}
		//RLOUT1_ON;    // ������жϿ�
			break;
	case 5://��λ
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST: //----5 ����
				OOUT1_OFF;
				OOUT3_ON;
				OOUT4_ON; 
					break;
			//case 1://----3 ����	
			case MOTOR_FREQ_3_SPD_RST: //----3 ����+��λ		
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
				if(temp>1200) //12-80  �и���
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
						// if(temp>50)//0.5-6 ����	20170927
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
						// else
							// {
							// if(Run_flag==0)
								// {
								// if(MoveSpeed!=3)
									// {
									// MoveSpeed=3;
									// SetMotorSpeed(MoveSpeed);
									// }
									// MoveBack();  //����
									// Forward_flag=0;
									// Backward_flag=1;
								// }
							// else
								// {
						
								// }
							// }
						
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
			case INDONSIA:	//ӡ��
			case PORTUGAL:	//������
			case SPANISH: //������
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
			case INDONSIA:	//ӡ��
			case PORTUGAL:	//������
			case SPANISH: //������
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
			case INDONSIA:	//ӡ��
			case PORTUGAL:	//������
			case SPANISH: //������
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
			case INDONSIA:	//ӡ��
			case PORTUGAL:	//������
			case SPANISH: //������
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
			case INDONSIA:	//ӡ��
			case PORTUGAL:	//������
			case SPANISH: //������
				Printf24("5------DC servo 670",x,y,F_color,1,B_color);
				break;
			}
		break;	
	case MOTOR_AC_SERVO:	 		//�����ŷ�	
		y+=gap*5;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("6------�����ŷ�����",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
			case INDONSIA:	//ӡ��
			case PORTUGAL:	//������
			case SPANISH: //������
				Printf24("6------AC servo Forward",x,y,F_color,1,B_color);
				break;
			}
		break;	
	case MOTOR_AC_SERVO_REV:	 		//�����ŷ�	
		y+=gap*6;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("7------�����ŷ�����",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
			case INDONSIA:	//ӡ��
			case PORTUGAL:	//������
			case SPANISH: //������
				Printf24("7------AC servo Reverse",x,y,F_color,1,B_color);
				break;
			}
		break;	
	}
}

void NewInput_dis(Int32U size)
{
Int8U num[8],n=0;
Int16U x,y,back_color,f_color;
back_color=WHITE_COLOR;f_color=0;

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
GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//�ߴ�����
// Printf24(num,SIZE_WINDOW_X+25,SIZE_WINDOW_Y+5,BLACK_COLOR,1,0xffff);
x=SIZE_WINDOW_X+SIGN_2WIDE;	y=SIZE_WINDOW_Y+5;
ASCII_Printf(num,108+1,20,36,ASCII_20x36, x,y,f_color,back_color);
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
				case PORTUGAL:	//������
				case SPANISH: //������
						Printf24(" INSE",x,y,num_color,0,0xffff);
						break;
				case INDONSIA:	//ӡ��
						Printf24("Menyi",x,y,num_color,0,0xffff);
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
				case PORTUGAL:	//������
				case SPANISH: //������
						Printf24(" EXIT",x,y,num_color,0,0xffff);
						break;
				case INDONSIA:	//ӡ��
						Printf24("Berhe",x,y,num_color,0,0xffff);
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
				case PORTUGAL:	//������
				case SPANISH: //������
						Printf24(" OK",x,y,num_color,0,0xffff);
						break;
				case INDONSIA:	//ӡ��
						Printf24(" Ya",x,y,num_color,0,0xffff);
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
				case PORTUGAL:	//������
				case SPANISH: //������
						Printf24(" RUN",x,y,num_color,0,0xffff);
						break;
				case INDONSIA:	//ӡ��
						Printf24("RUN",x,y,num_color,0,0xffff);
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
	//----------------------------		
	case BUTT_SHIFT:	
			if(down_flag==1)  //���º�
				ShiftButtonDown_dis(SHIFT_BUTT_X,SHIFT_BUTT_Y);	//shift�ϵ�
			else
				ShiftButtonUp_dis(SHIFT_BUTT_X,SHIFT_BUTT_Y);	//shift�ϵ� up
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
	case PORTUGAL:	//������
	case SPANISH: //������
		Printf24("Whether Paper-Pusher is in the end!",PUSH_RESET_PROMPT_X1+1,PUSH_RESET_PROMPT_Y1+5,BLACK_COLOR,1,0xffff);
		Printf24("OK",PUSH_RESET_OK_X,PUSH_RESET_OK_Y,BLACK_COLOR,1,0xffff);
		Printf24("Cancel",PUSH_RESET_CANCEL_X,PUSH_RESET_CANCEL_Y,BLACK_COLOR,1,0xffff);
		break;
	case INDONSIA:	//ӡ��	
		Printf24("Apakah mendorong kertas di final!",PUSH_RESET_PROMPT_X1+1,PUSH_RESET_PROMPT_Y1+5,BLACK_COLOR,1,0xffff);
		Printf24("Ya",PUSH_RESET_OK_X,PUSH_RESET_OK_Y,BLACK_COLOR,1,0xffff);
		Printf24("Membatal",PUSH_RESET_CANCEL_X,PUSH_RESET_CANCEL_Y,BLACK_COLOR,1,0xffff);
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
	ratio=now*100/total;
	x1=SCHEDULE_DOT_X,x2=x1+12;
	if(1)//(ratio!=ProcessRatio)
		{
		if(ProcessRatio!=0xff)    //���� ��ʼ
			{/*
			color=0xf78a;
			y1=SCHEDULE_DOT_Y+ProcessRatio;
			y2=y1+12;
			GLCD_SetWindow_Fill(x1,y1, x2,y2 ,color,color);//��� ���ȿ�
			*/
			color=TEXT_TAB_BACK_COLOR;
			y1=SCHEDULE_DOT_Y+ProcessRatio;
			y2=y1+25;
			GLCD_SetWindow_Fill(x1,y1, x2,y2 ,color,color);//��� ���ȿ�
			// DrawLine( SCHEDULE_DOT_X+5, y1, SCHEDULE_DOT_X+5, y2, 0);
			color=0x0193;
			GLCD_SetWindow_Fill(SCHEDULE_DOT_X+5, y1, SCHEDULE_DOT_X+5+2, y2, color,color);
			}
		//**************
		ProcessRatio=ratio;
		color=0x0193;
		y1=SCHEDULE_DOT_Y+ProcessRatio;
		y2=y1+25;
		GLCD_SetWindow_Fill(x1,y1, x2,y2 ,color,color);//���� ���ȿ�
		}
	}

}


void InputKEY_BUTT_dis(Int8U b_num,Int8U down_flag) //���� key ��ʾ--------���뷨
{
Int16U butt_color,num_color;
Int16U x,y,gap_x,gap_y,gap_x1,gap_y1;
gap_x=25,gap_x1=20,gap_y=8,gap_y1=24;
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
	case BUTT_1:	//
			x=TOUBUTT_X1;
			y=TOUBUTT_Y1;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			y+=gap_y;
			Printf24("1",x+gap_x,y,num_color,0,0xffff);
			y+=gap_y1;
			Printf16(",",x+gap_x1,y,num_color,0,0xffff);
			break;		
	case BUTT_2:	//
			x=TOUBUTT_X2;
			y=TOUBUTT_Y1;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			y+=gap_y;
			Printf24("2",x+gap_x,y,num_color,0,0xffff);
			y+=gap_y1;
			Printf16("abc",x+gap_x1,y,num_color,0,0xffff);
			break;		
	case BUTT_3:	//
			x=TOUBUTT_X3;
			y=TOUBUTT_Y1;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			y+=gap_y;
			Printf24("3",x+gap_x,y,num_color,0,0xffff);
			y+=gap_y1;
			Printf16("def",x+gap_x1,y,num_color,0,0xffff);
			break;		
	case BUTT_UP:	//  up
			x=TOUBUTT_X4;
			y=TOUBUTT_Y1;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			x+=gap_x;y+=30;
			GLCD_Triangle_Fill(x,y, x+10,y-15, x+20,y ,num_color,num_color);
			break;	
			//--------------------------------2  line
	case BUTT_4:	//
			x=TOUBUTT_X1;
			y=TOUBUTT_Y2;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			y+=gap_y;
			Printf24("4",x+gap_x,y,num_color,0,0xffff);
			y+=gap_y1;
			Printf16("ghi",x+gap_x1,y,num_color,0,0xffff);
			break;		
	case BUTT_5:	//
			x=TOUBUTT_X2;
			y=TOUBUTT_Y2;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			y+=gap_y;
			Printf24("5",x+gap_x,y,num_color,0,0xffff);
			y+=gap_y1;
			Printf16("jkl",x+gap_x1,y,num_color,0,0xffff);
			break;		
	case BUTT_6:	//
			x=TOUBUTT_X3;
			y=TOUBUTT_Y2;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			y+=gap_y;
			Printf24("6",x+gap_x,y,num_color,0,0xffff);
			y+=gap_y1;
			Printf16("mno",x+gap_x1,y,num_color,0,0xffff);
			break;		
	case BUTT_DOWN:	//   down
			x=TOUBUTT_X4;
			y=TOUBUTT_Y2;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			x+=gap_x;y+=30;
			GLCD_Triangle_Fill(x,y, x+10,y+15, x+20,y ,num_color,num_color);
			break;	
			//--------------------------------3  line
	case BUTT_7:	//
			x=TOUBUTT_X1;
			y=TOUBUTT_Y3;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			y+=gap_y;
			Printf24("7",x+gap_x,y,num_color,0,0xffff);
			y+=gap_y1;
			Printf16("pqrs",x+gap_x1,y,num_color,0,0xffff);
			break;		
	case BUTT_8:	//
			x=TOUBUTT_X2;
			y=TOUBUTT_Y3;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			y+=gap_y;
			Printf24("8",x+gap_x,y,num_color,0,0xffff);
			y+=gap_y1;
			Printf16("tuv",x+gap_x1,y,num_color,0,0xffff);
			break;		
	case BUTT_9:	//
			x=TOUBUTT_X3;
			y=TOUBUTT_Y3;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			y+=gap_y;
			Printf24("9",x+gap_x,y,num_color,0,0xffff);
			y+=gap_y1;
			Printf16("wxyz",x+gap_x1,y,num_color,0,0xffff);
			break;		
	case BUTT_LEFT:	//  <--��
			x=TOUBUTT_X4;
			y=TOUBUTT_Y3;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			x+=gap_x;y+=30;
			GLCD_Triangle_Fill(x,y, x+15,y-10, x+15,y+10 ,num_color,num_color);
			break;	
			//--------------------------------4  line
	case BUTT_CLEAR:	//clear
			x=TOUBUTT_X1;
			y=TOUBUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			x+=gap_x;y+=gap_y;
			Printf24("C",x,y,num_color,0,0xffff);
			break;		
	// case BUTT_SPAC:	//�ո�
	case BUTT_0:	//�ո�
			x=TOUBUTT_X2;
			y=TOUBUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			y+=gap_y;
			Printf24("0",x+gap_x,y,num_color,0,0xffff);
			x+=gap_x,y+=gap_y1;
			GLCD_SetWindow_Fill(x,y,x+20,y+8,  num_color,num_color);
			GLCD_SetWindow_Fill(x+3,y,x+20-3,y+8-3,  butt_color,butt_color);
			break;		
	case BUTT_ENTER:	//ȷ��
			x=TOUBUTT_X3;
			y=TOUBUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			x+=15;y+=30;
			// Printf24("OK",x,y,num_color,0,0xffff);
			GLCD_Triangle_Fill(x,y, x+15,y-10, x+15,y+10 ,num_color,num_color);
			x+=15,y-=1;
			GLCD_SetWindow_Fill(x,y, x+20,y+3 ,num_color,num_color);
			x+=20;y+=3;
			GLCD_SetWindow_Fill(x,y, x+3,y-10 ,num_color,num_color);
			break;		
	case BUTT_RIGHT:	//  -->��
			x=TOUBUTT_X4;
			y=TOUBUTT_Y4;
			GLCD_SetWindow_Fill(x,y,x+TOUBUTT_WIDE,y+TOUBUTT_HIGH,butt_color,butt_color);
			x+=gap_x;y+=30;
			GLCD_Triangle_Fill(x,y-10, x,y+10, x+15,y ,num_color,num_color);
			break;	
	default:
			break;
	}
}


void StartHelpMenu_sel(Int8U sel, Int8U dis_flag)//����ϵͳ  ��������
{
Int16U F_color,B_color,x,y,gap;
F_color=RED_COLOR;
B_color=WHITE_COLOR;
Printf24("����У׼+",HELP_CORRECT_X,HELP_CORRECT_Y,F_color,1,B_color);
Printf24("���ء�",HELP_RET_X,HELP_RET_Y,F_color,1,B_color);
if(dis_flag==1)
	{
	F_color=WHITE_COLOR;
	B_color=BLUE_COLOR;
	}
else
	{
	F_color=BLUE_COLOR;
	B_color=WHITE_COLOR;
	}
x=HELP_F1_X,y=HELP_F1_Y;gap=HELP_GAP_Y;
switch(sel)
	{
	case 1://F1  ����У׼
		switch(Language)
			{
			case CHN_HAN:
				Printf24("F1------����У׼",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
				Printf24("F1------Touch calibration",x,y,F_color,1,B_color);
				break;
			case INDONSIA:	//ӡ��
				Printf24("F1------sentuh Kalibrasi",x,y,F_color,1,B_color);
				break;
			case PORTUGAL:	//������
				Printf24("F1------Toque em Calibra??o",x,y,F_color,1,B_color);
				ASCII_Printf("ca",ASCII24_MODE,12,24,PUTAO_ZK24, x+12*24,y,F_color,B_color);
				break;
			case SPANISH: //������
				Printf24("F1------Calibraci�� ",x,y,F_color,1,B_color);
				Printf24("                  n Pantalla tactil",x,y,F_color,0,B_color);
				break;
			}	
		break;
	case 2://F2		ͼ��ע��
		y+=gap;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("F2------ͼ��ע��",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
				Printf24("F2------Icon Comment",x,y,F_color,1,B_color);
				break;
			case INDONSIA:	//ӡ��
				Printf24("F2------gambar komentar",x,y,F_color,1,B_color);
				break;
			case PORTUGAL:	//������
				Printf24("F2------��	             ",x,y,F_color,1,B_color);
				Printf24("         cone coment��",x,y,F_color,0,B_color);	//��cone coment��rio
				Printf24("                     rio",x,y,F_color,0,B_color);	//��cone coment��rio
				break;
			case SPANISH: //������
				Printf24("F2------Picture Notes",x,y,F_color,1,B_color);
				break;
			}		
		break;
	case 3://	F3	�˿ڲ���---
		y+=gap*2;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("F3------Ӳ������",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
				Printf24("F3------Board test",x,y,F_color,1,B_color);
				break;
			case INDONSIA:	//ӡ��
				Printf24("F3------uji Dewan",x,y,F_color,1,B_color);
				break;
			case PORTUGAL:	//������
			case SPANISH: //������
				Printf24("F3------port Test",x,y,F_color,1,B_color);
				break;
			}
		break;
	case 4://	F4	ϵͳѡ��---
		y+=gap*3;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("F4------ϵͳѡ��(���棺��רҵ��Ա,��ֹ����!)",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
				Printf24("F4------System select(Warning:Non-professionals,",x,y,F_color,1,B_color);
				Printf24("prohibited actions)",x+150,y+50,F_color,1,B_color);
				break;
			case INDONSIA:	//ӡ��
				Printf24("F4----Seleksi sistem(Peringatan: non-profesional,",x,y,F_color,1,B_color);
				Printf24("dilarang tindakan)",x+150,y+50,F_color,1,B_color);
				break;
			case PORTUGAL:	//������
				Printf24("F4----Selec??o do sistema(Aviso: n?o-profissionais",x,y,F_color,1,B_color);
				ASCII_Printf("ca",ASCII24_MODE,12,24,PUTAO_ZK24, x+12*11,y,F_color,B_color);
				ASCII_Printf("a",ASCII24_MODE,12,24,PUTAO_ZK24, x+12*34,y,F_color,B_color);
				Printf24(",para proibir a opera??o!)",x+150,y+50,F_color,1,B_color);
				ASCII_Printf("ca",ASCII24_MODE,12,24,PUTAO_ZK24, x+150+12*21,y+50,F_color,B_color);
				break;
			case SPANISH: //������
				Printf24("F4----sistema Selecci�� ",x,y,F_color,1,B_color);
				Printf24("                      n(Aviso: Los no ",x,y,F_color,0,B_color);
				
				Printf24("profesionales, para prohibir la operaci��",x+50,y+50,F_color,1,B_color);
				Printf24("                                        n)",x+50,y+50,F_color,0,B_color);
				break;
			}
		break;
	case 5://	F5	ÿҳ�б�����---
		y+=gap*4;
		switch(Language)
			{
			case CHN_HAN:
				Printf24("F5------ÿҳ�б�����",x,y,F_color,1,B_color);
				break;
			case ENGLISH:
			case INDONSIA:	//ӡ��
			case PORTUGAL:	//������
			case SPANISH: //������
				Printf24("F5------Page sizes,",x,y,F_color,1,B_color);
				
				break;
			}
		break;
	}
}

void StartHelpMode_dis(void)
{
Int8U p;
GLCD_Buffer_Fill(WHITE_COLOR);//
for(p=1;p<6;p++)
	StartHelpMenu_sel(p,0);
}

void Num_Keyboard_Tou_dis(Int8U b_num,Int8U down_flag) //���� key ��ʾ
{
Int16U butt_color,num_color;
Int16U x,y,gap_word_x,gap_word_y;
if(down_flag==1)  //���º�
	{
	butt_color=GREEN_COLOR;
	num_color=RED_COLOR;
	}
else
	{
	butt_color=0x9fff;
	num_color=0;
	}gap_word_x=30,gap_word_y=20;
switch(b_num)
	{
	case BUTT_1:
			x=KEY_BUT_X1;
			y=KEY_BUT_Y1;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("1",x,y,num_color,0,0xffff);
			break;	
	case BUTT_2:
			x=KEY_BUT_X2;
			y=KEY_BUT_Y1;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("2",x,y,num_color,0,0xffff);
			break;		
	case BUTT_3:
			x=KEY_BUT_X3;
			y=KEY_BUT_Y1;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("3",x,y,num_color,0,0xffff);
			break;		
//--------			
	case BUTT_4:
			x=KEY_BUT_X1;
			y=KEY_BUT_Y2;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("4",x,y,num_color,0,0xffff);
			break;	
	case BUTT_5:
			x=KEY_BUT_X2;
			y=KEY_BUT_Y2;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("5",x,y,num_color,0,0xffff);
			break;		
	case BUTT_6:
			x=KEY_BUT_X3;
			y=KEY_BUT_Y2;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("6",x,y,num_color,0,0xffff);
			break;				
//--------			
	case BUTT_7:
			x=KEY_BUT_X1;
			y=KEY_BUT_Y3;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("7",x,y,num_color,0,0xffff);
			break;	
	case BUTT_8:
			x=KEY_BUT_X2;
			y=KEY_BUT_Y3;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("8",x,y,num_color,0,0xffff);
			break;		
	case BUTT_9:
			x=KEY_BUT_X3;
			y=KEY_BUT_Y3;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("9",x,y,num_color,0,0xffff);
			break;						
//--------			
	case BUTT_CLEAR:
			x=KEY_BUT_X1;
			y=KEY_BUT_Y4;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("C",x,y,num_color,0,0xffff);
			break;	
	case BUTT_0:
			x=KEY_BUT_X2;
			y=KEY_BUT_Y4;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("0",x,y,num_color,0,0xffff);
			break;		
	case BUTT_ENTER:
			x=KEY_BUT_X3;
			y=KEY_BUT_Y4;
			GLCD_SetWindow_Fill(x,y,x+KEY_BUT_WIDE,y+KEY_BUT_HIGH,butt_color,butt_color);
			x+=gap_word_x;y+=gap_word_y;
			Printf24("OK",x,y,num_color,0,0xffff);
			break;			
	}
}

void SysBoardSelect_dis(void)  //ϵͳ�汾 ����
{
Int16U x,y;
Int8U n=0;
x=SYSBD_HINT_X,y=SYSBD_HINT_Y;
GLCD_Buffer_Fill(0xffff);
switch(Language)
	{
	case CHN_HAN:
		Printf24("���������룺",x,y,BLACK_COLOR,0,0xffff);
			break;
	case ENGLISH:	
		Printf24("Enter password,please:",x,y,BLACK_COLOR,0,0xffff);
			break;
	case INDONSIA:	//ӡ��
		Printf24("Masukkan sandi Anda:",x,y,BLACK_COLOR,0,0xffff);
			break;
	case PORTUGAL:	//������
		Printf24("Por favor, digite uma senha:",x,y,BLACK_COLOR,0,0xffff);
			break;
	case SPANISH: //������
		Printf24("Introduzca la contrase?a",x,y,BLACK_COLOR,0,0xffff);
		ASCII_Printf("n",ASCII24_MODE,12,24,PUTAO_ZK24,x+12*22,y,BLACK_COLOR,0xffff);
			break;
	}
GLCD_SetWindow_Fill(SYSBD_WORD_X, SYSBD_WORD_Y, SYSBD_WORD_X+120, SYSBD_WORD_Y+30, RED_COLOR, 0xffff);	
Printf24("���ء�",HELP_RET_X,HELP_RET_Y,RED_COLOR,1,0xffff);
while(n<22)
	{
	Num_Keyboard_Tou_dis( n++, 0); //���� key ��ʾ
	}
}	

void SysBoardNum_dis(pInt8U p_num,Int8U cou)
{
Int8U passnums[8],n=0;
for(n=0;n<cou;n++)
	{
	if(*p_num!='.')
		{
		passnums[n]=*p_num+48;
		}
	p_num++;
	}
passnums[n]=0;
Printf24(passnums,SYSBD_WORD_X+10,SYSBD_WORD_Y+5,BLACK_COLOR,1,0xffff);
}

void ClrSysBoardNum_dis(void)
{
if(num_cou>0)
	{
	for(num_cou=0;num_cou<8;num_cou++)
		 {
		 Size_temp[num_cou++]=0;
		 }
	num_cou=0; //
	GLCD_SetWindow_Fill(SYSBD_WORD_X, SYSBD_WORD_Y, SYSBD_WORD_X+120, SYSBD_WORD_Y+30, RED_COLOR, 0xffff);	
	}
}

void EnterSysBoardNum(void)
{
Int32U code_temp=0,n;
if(Board_TestMod==TEST_SYS_WORD)
	{
	if(num_cou>0)
		{
		for(n=0;n<num_cou;n++)
			{
			code_temp=code_temp*10+Size_temp[n];
			}
		if(code_temp==SYSBD_PASSWORD)	 //����  ��ȷ�������ϵͳ�汾ѡ��
			{
			Board_TestMod=TEST_SYS_TYPE;
			GLCD_Buffer_Fill(0xffff);
			SpeedLevelSel_dis(0,0);    //������� ��ʾ
			SpeedLevelSel_dis(1,0);    //������� ��ʾ
			SpeedLevelSel_dis(2,0);    //������� ��ʾ
			SpeedLevelSel_dis(3,0);    //������� ��ʾ
			SpeedLevelSel_dis(4,0);    //������� ��ʾ
			SpeedLevelSel_dis(5,0);    //������� ��ʾ
			SpeedLevelSel_dis(6,0);    //������� ��ʾ
			SpeedLevelSel_dis(MotorType,1);
			UpArrow_Up_dis( VER_SEL_UP_X,  VER_SEL_UP_Y);//�ϼ�ͷup
			DownArrow_Up_dis( VER_SEL_DOWN_X,  VER_SEL_DOWN_Y);//�¼�ͷup
			}
		else   //error
			{
			GLCD_SetWindow_Fill(SYSBD_WORD_X, SYSBD_WORD_Y, SYSBD_WORD_X+120, SYSBD_WORD_Y+30, RED_COLOR, 0xffff);	
			}
		for(num_cou=0;num_cou<8;num_cou++)
			 {
			 Size_temp[num_cou++]=0;
			 }
		num_cou=0; //	
		}

	}
}

void KnifeSensorInMachine_dis(Int8U down_flag)//�� ������λ�� ʾ��
{
Int16U x,y,color;
Int8U r=3;
x=KNIFE_SENSOR_X,y=KNIFE_SENSOR_Y;
if(ButtonTouch_mode==0)
	{
	if(WorkMode==MANUAL_MODE)// �ֶ� ģʽ
		{
		if(down_flag==0)//��
			{
			if(KnifeSensorMode!=1)
				{
				KnifeSensorMode=1;
				color=TEXT_TAB_BACK_COLOR;
				GLCD_Circle_Fill( x, y, r, color, color);
				}
			}
		else		//��
			{
			if(KnifeSensorMode!=2)
				{
				KnifeSensorMode=2;
				color=RED_COLOR;
				GLCD_Circle_Fill( x, y, r, color, color);
				}
			}
		}
	}	
}
void PressSensorInMachine_dis(Int8U down_flag)//ѹֽ ������λ�� ʾ��
{
/***
Int16U x,y,color;
Int8U r=3;
x=PRESS_SENSOR_X,y=PRESS_SENSOR_Y;
if(ButtonTouch_mode==0)
	{
	if(WorkMode==MANUAL_MODE)// �ֶ� ģʽ
		{
		if(down_flag==0)//��
			{
			if(PressSensorMode!=1)
				{
				PressSensorMode=1;
				color=TEXT_TAB_BACK_COLOR;
				GLCD_Circle_Fill( x, y, r, color, color);
				}
			}
		else		//��
			{
			if(PressSensorMode!=2)
				{
				PressSensorMode=2;
				color=RED_COLOR;
				GLCD_Circle_Fill( x, y, r, color, color);
				}
			}
		}
	}
	***/
}

void PageLine_Set(Int8U line_set,Int8U set_flag)	//ÿҳ������ʾ
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
x=200,y=200;gap=40;
switch(line_set)
	{
	case PAGE_5_LINE: //5 line 
			switch(Language)
				{
				case CHN_HAN:
					Printf24("ÿҳ��ʾ5��",x,y,F_color,1,B_color);
						break;
				case ENGLISH:	
				case INDONSIA:	//ӡ��
				case PORTUGAL:	//������
				case SPANISH: //������
					Printf24("5 lines a page",x,y,F_color,1,B_color);
						break;
				}
			break;
	case PAGE_7_LINE: //7 line  
			y+=gap;
			switch(Language)
				{
				case CHN_HAN:
					Printf24("ÿҳ��ʾ7��",x,y,F_color,1,B_color);
						break;
				case ENGLISH:	
				case INDONSIA:	//ӡ��
				case PORTUGAL:	//������
				case SPANISH: //������
					Printf24("7 lines a page",x,y,F_color,1,B_color);
						break;
				}
			break;
	}
}
void PageLineSet_dis(void)	//ÿҳ���� ����  -------����
{
Int16U x,y;

GLCD_Buffer_Fill(0xffff);
Printf24("���ء�",HELP_RET_X,HELP_RET_Y,RED_COLOR,1,0xffff);
PageLine_Set(PAGE_5_LINE, 0);	//ÿҳ������ʾ
PageLine_Set(PAGE_7_LINE, 0);	//ÿҳ������ʾ

PageLine_Set(PageKf_Size_flag, 1);	// 
UpArrow_Up_dis( LINE_SET_UP_X,  LINE_SET_UP_Y);//�ϼ�ͷup
DownArrow_Up_dis( LINE_SET_DOWN_X,  LINE_SET_DOWN_Y);//�¼�ͷup
}


