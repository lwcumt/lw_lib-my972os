/*

��ɨ��   1MS����һ��


*/

#include"key.h"

#include"m25pe16.h"
#include"chndot.h"

#include"io.h"
#include "timer.h"

#include "pic_exec.h"

#include  "test_io.h"

#include "port.h"
#include "servo.h"
#include "name_input.h"
#include "file.h"

//#define WHITE_COLOR 0xffff



#define BLACK_COLOR 0
#define WHITE_COLOR 0xffff
#define RED_COLOR 0xf800
#define BLUE_COLOR 0x001f
#define GREEN_COLOR 0x7e0
#define VIOLET_COLOR 0xf81f
#define YELLOW_COLOR 0xffe0
#define QINGSE_COLOR 0x07ff


#define DOT32  32  //����32*32����  
#define DOT32MODE 128+2


Int8U SetTime_flag;//ʱ���趨ʹ��
Int8U LongExec_flag;//������־

Int16U Year_temp;//ʱ��
Int8U  Month_temp;
Int8U  Date_temp;
Int8U  Hour_temp;
Int8U  Min_temp;

Int8U TimeBit[10];
Int8U TimeBit_Sel;
Int8U TimeBit_Last;

const Int16U DisPosX[10]={Year1_X,Year0_X,Month1_X,Month0_X,Date1_X,Date0_X,Hour1_X,Hour0_X,Min1_X,Min0_X};
const Int16U DisPosY[10]={Year1_Y,Year0_Y,Month1_Y,Month0_Y,Date1_Y,Date0_Y,Hour1_Y,Hour0_Y,Min1_Y,Min0_Y};


//unsigned  long int  yuandiancn ;
int nian;
unsigned char yue,ri,shi,feng;
 int KeyCode;  //������
int KeyCode_Temp;
 int KeyDownTime;  //��ɨ�¼�ʱ
 int KeyLongDownTime;  //����ʱ�䰴�¼�ʱ
 char KeyDown_Flag;   //�����±�־λ
 char KeyExec_Flag;   //�������־λ
 char KeyLongDown_Flag;
 unsigned char InputBuf[30];
 unsigned char InputCou,flagdaobiaoji,flaghsd,flagqsd;
unsigned long int lcdchicun[6],lcdchengxuhaoma[2],ymuqiancn;
 unsigned char flagdot,program4,daohao,flagyici;
  unsigned long int weizhicn[200];
  unsigned long int   yvbcd4,yhoujixian,chengxuweizhi[100];
 unsigned long int I,lcdnumber,zongchang,biaoqian,dengfeng,feibian,dzongchang,fengshu,dfshu;
  unsigned long int Rswanwei,Rwanwei,Rqianwei,Rbaiwei,Rshiwei,Rgewei,sw,qb,sg,mubiao;
   unsigned char bcd[3],qbcd[3],hbcd[5];
  unsigned long int swanwei1,wanwei1,qianwei1,baiwei1,shiwei1,gewei1,sw2,qb2,sg2;
   unsigned  char flagyd,flagqyx, poweon_flag,flagshanchu;
  unsigned char flagchengxu;
	Int16U n;
 unsigned  char   chengxuhaoma, huamian,zhishi,flagrun,flagkeysong,flagdanwei;
 unsigned  char flagjia,flagjian,flagcheng,flagchu;
  unsigned long int qianjixian,zhongjixian,houjixian,jizhun,vbcd4,zongshu,dfchangdu,mada;
   unsigned  char flagbz[200],flagzhiyou;
unsigned long int vbcd;
   unsigned  char flaggong,qianjinflag,houtuiflag;
//**************���巢�ͱ���**********************//
unsigned char status,flagyunxing8;         //
unsigned char step_ground;   //
unsigned char step_add;      //
unsigned char qianjin,houtui;
unsigned char   flagqyx,  t0zhongduan;



unsigned long int yushu;
unsigned long int speedup_steps;
unsigned long int speedup_steps_B;
unsigned long int rollsteps;     
unsigned char flagtingji7,flagtingji8;

unsigned long int qianjincn,houtuicn;
unsigned long int  tempqianjin1, temphoutui1; 


 
 void lcdweizhicn( unsigned long int x0, unsigned long int y0,unsigned long int chicun);
 void lcdweizhicnH( unsigned long int x0, unsigned long int y0,unsigned long int chicun);
void lcdNUMBER( unsigned long int x0, unsigned long int y0,unsigned char chicun);
void lcdNUMBERH( unsigned long int x0, unsigned long int y0,unsigned char chicun);
void lcdhaoma( unsigned long int x0, unsigned long int y0,unsigned char chicun);
void chengxudu();
 void lcdzhishi();
void lcdnian( unsigned long int x0, unsigned long int y0,unsigned int  chicun); 
 void lcdpage1();
 
 
Int8U CalcNoNumInput_flag; 
 
unsigned char num_cou=0;
unsigned char Size_temp[8];
unsigned char CalcInput_Text[24];
unsigned char CalcResult_Text[24];
unsigned char CalcInput_cou;

unsigned char CalcSign_order;
unsigned char CalcTemp_cou;
Int32U CalcData_temp;
unsigned long int InputSize=0;

Int8U Dot_flag;

unsigned char WorkStart_flag;
unsigned char Comment_flag;
unsigned char flagyunxing;


pInt8U  pKnife_data;

KNIFE_DATA OneKnife_data;
START_DAY Start_days;

unsigned int Total_size=0;//�ܳ�
unsigned int Label_size=0;//��ǩ��
unsigned int Waste_size=0;//�ϱ�
unsigned int Divide_num=0;//�ȷ���
 

unsigned char cursor_temp;
unsigned long int maichongdangliang,xxmuqiancn;

Int16U Pro_num;



Int8U PromptDis_flag;
Int8U StartPassInput_flag=0;

Int32U PassCode;
Int32U PassCheck;

Int8U PassCheckDis_flag;

Int8U Year_before,Month_before,Day_before;
Int8U TimeAhead_flag; //ʱ����ǰ ��־

Int8U PaperCutEnb_signal;
Int16U Past_days;

Int8U Sign_flag;
Int8U Minus_flag;
Int8U Arithmetic_mode; //����ģʽ
Int8U StartCheck_mode;
Int8U OutSensorOK_flag;
//Int8U RunToCusor_flag;
Int32U Zpulse_cou;
Int32U Z_Pulse;

Int8U Board_TestMod;
Int8U TouchCalcu_mode;


Int8U CalcResultDis_flag;
Int8U AutoRoute_flag;
Int8U Manual_page;

Int8U CheckModeOK_flag;


Int8U ManualMoveMode;


Int8U Stop_F_Remind_flag;

Int8U BellStart_flag;
Int8U TargetBell_flag;
Int16U TargetBell_time;
Int8U TargetBell_mode;

Int8U AllKnifeSet_flag;

unsigned  char flagyd;
unsigned char flagchengxu,flagkey,flagtime1;

Int8U AC_MotorSPD; //AC  motor  speed
Int8U PressCircle_mode=0;


void BellOn_Enb(void)
{
labatime=0;
BellOUT_ON;flaglaba=1;
}


void KeyScan(void)  //��ɨ��   1MS����һ��
{
unsigned long int j;  

Key_Enable(ENABLE);
if(KeyDown_Flag==0)
	{
//	KeyCode=KEYIO;   //�������  ��ͬ�Ķ˿�״̬�޸Ĵ���
	if(KeyCheck()!=0)   //�ж��Ƿ��м�����
		{
		KeyDown_Flag=1;    //�ü����±�־λ
		KeyDownTime=0;
		}
	}
else
	{
	if(KeyExec_Flag==0)
		{
	//	KeyCode=KEYIO;   //�������  ��ͬ�Ķ˿�״̬�޸Ĵ���
		if(KeyCheck()!=0)   //�ж��Ƿ��м�����
			{
			KeyDownTime++;
			if(KeyDownTime>=50)  //���¼� ȥ����10MS
				{
				KeyDownTime=0;
				KeyReadCode();//��ȡ��ֵ 
				KeyCode_Temp=KeyCode;

				////////////////////////////
                                  flagkeysong=0;
				//  ����Ϊ�����´���
				////////////////////////////
				switch(Board_TestMod)
					{
					case 0:
					case TEST_TOUCH:
					case TEST_HELP:
						KeyExec(KeyCode); //��������
							break;
					case TEST_BOARD://���� ģʽ  3
						BellOn_Enb();
						KeyDis_sel(KeyCode_Temp,1);  //***************������ʾ 
							break;
					case TEST_MOTOR_TYPE://�趨  ��λ4
						BellOn_Enb();
						ShiftSpeed_SetExec(KeyCode); 
							break;
					}
				KeyExec_Flag=1; //�ü������־λ
				}
			}
		else
			{  //���������˳�
			KeyDown_Flag=0;
			}
		}
	else
		{
//		KeyCode=KEYIO;   //�������  ��ͬ�Ķ˿�״̬�޸Ĵ���
		if(KeyCheck()==0)   //�ж��Ƿ��м�����		if(KeyCode==0)
			{
			KeyDownTime++;
			if(KeyDownTime>=50)  //------------�ͷż� ȥ����10MS
				{
				KeyDown_Flag=0;   //�尴�±�־λ
				KeyExec_Flag=0;   //��������־λ
				KeyLongDownTime=0;  //���������ʱ
				KeyCode=0;
				//KeyLongDown_Flag=0;
                 LongExec_flag=0;  
				////////////////////////////
				GoFrontEn_flag=0;
				GoBackEn_flag=0;
				GoFast_flag=0;
				if(Board_TestMod==TEST_BOARD)
					{
					KeyDis_sel(KeyCode_Temp,0); //***************������ʾ
					MoveStop();
					RLOUT1_OFF; RLOUT1_1_OFF;   // �������
					}
					
				//----------------------------------------
				
				
				 ACMotor_ReleaseStop();  //-------
				 	
				}
			}
		else
			{
			KeyDownTime=0;
			
			if(LongExec_flag==0)
			    {
				  KeyReadCode();//��ȡ��ֵ
				  MultiKey_exec(KeyCode);  //��ϼ�����
				  //if(KeyCode!=KeyCode_Temp)
				   //  {
					 
					// }
				}
			
			if(KeyLongDownTime<KEYLONGDOWNTIMEDATA)
				{
				KeyLongDownTime++;
                }             
			else//----------��������------------
			   {
			   if(LongExec_flag==0)
			      {
				  LongExec_flag=1;
				  //KeyReadCode();//��ȡ��ֵ
				  LongKey_exec(KeyCode , KeyCode_Temp);  //����������
				  }
			   }
								
			}
		}
	}
Key_Enable(DISABLE);
}


void NumKey_exec(Int8U num)
{
if(WorkStart_flag==1)
	{
	if(Run_flag==0)
		{
		if(CalcResultDis_flag==1)
			{
			ClrCalcNums_text(CalcInput_Text,CAL_INPUT); //������� �����
			CalcInput_cou=0;
			num_cou=0;
			CalcResultDis_flag=0;  //�����ʾ ��־
			CalcSign_order=0;//�׸������ λ��
			}
		if(num_cou>7)num_cou=0;
		if(num_cou<7)
			{
			if(num_cou==0)
				GLCD_SetWindow_Fill( SIZE_WINDOW_X+24, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
			//if(CalcNoNumInput_flag==1)
				CalcNoNumInput_flag=0;	
			if(num!='.')
				{
				Size_temp[num_cou++]=num;
				if(InputTouch_flag==0)
					{
					InputNum_dis(Size_temp,num_cou);
					}
				else//--------------------������
					{
					CalcInput_Text[CalcInput_cou++]=num;
					CalcInputNums_dis(CalcInput_Text);	
					}
				}
			else
				{
				if(Dot_flag==0)	
					{
					Dot_flag=1;
					Size_temp[num_cou++]=num;
					if(InputTouch_flag==0)
						{
						InputNum_dis(Size_temp,num_cou);
						}
					else//--------------------������
						{
						CalcInput_Text[CalcInput_cou++]=num;
						CalcInputNums_dis(CalcInput_Text);	
						}
					}
				}
			}
		
		}
	else
		{
						
		}
	}
else
	{
	if(PassCheckDis_flag==1) 
		{
		if(num_cou<6)
			{
			Size_temp[num_cou++]=num;
			PassWord_dis(Size_temp,num_cou);//����
			}	
		}
	}		
}

void ClearCalculatorInput(void) //��������� ����
{
CalcNoNumInput_flag=1;
//num_cou=0;
Dot_flag=0;
CalcSign_order=0;//�׸������ λ��
CalcData_temp=0;
CalcResultDis_flag=0;
ClrCalcNums_text(CalcInput_Text,CAL_INPUT); //������� �����
ClrCalcNums_text(CalcResult_Text,CAL_RESULT); //������� �����
CalcInputNums_dis(CalcInput_Text);  //����� ��ʾ
CalcInput_cou=0;
CalcResultNums_dis(CalcResult_Text);//����� ��ʾ
}
void CalcuInClear_exec(void)     //��� ������
{
CurrentArea_recover3(CALCUL_WIN_X,CALCUL_WIN_Y,CALCUL_WIDE,CALCUL_HIGH);
InputTouch_flag=0;
Dot_flag=0;
num_cou=0;
//CalcSign_order=0;//�׸������ λ��
//CalcData_temp=0;
CalcResultDis_flag=0;
}

void CurrentToCalc_input(void)  //��ǰ�ߴ�  ת��Ϊ ��������ʾ����
{
volatile Int32U valu_temp;
Int8U current_flag;//dot;
KNIFE_DATA Knife_datas;
if((WorkMode==MANUAL_MODE)||(WorkMode==TEACH_MODE))  // �ֶ�|ʾ�� ģʽ	Ĭ�ϵ�ǰ�ߴ�
	{
	current_flag =1;
	}
else		//�б�� �ߴ�
	{
	if(Knife_order>1)
		{
		GetOneKnife_datas(Pro_data.pro_num, Knife_order-1, (pInt8U)&Knife_datas);//ȡ��һ�� ����
		if((Knife_datas.size>=Size_MIN_num)&&(Knife_datas.size<=Size_MAX_num))  //��ǰ�ߴ�  ��Ч
			{
			current_flag =0;	
			if(Unit==UNIT_MM)//mm
				{
				valu_temp=Knife_datas.size*10;
				}
			else //inch
				{
				valu_temp=Knife_datas.size;
				}
			}
		else
			{
			current_flag =1;	//valu_temp==0;
			}
		}
	else
		{
		current_flag =1;	//valu_temp==0;
		}	
	}
if(current_flag ==1)		//��ǰ�ߴ�
	{
	if(Unit==UNIT_MM)//mm
		{
		if(InTargetPosit_flag==1) 	//Ŀ��λ��
			valu_temp=TargetSize_temp;
		else	
			valu_temp=CurrentSize;
		
		valu_temp*=10;
		}
	else  //inch
		{
		if(InTargetPosit_flag==1)  	//Ŀ��λ��
			valu_temp=TargetSize_inch;
		else	
			valu_temp=CurrentSize*100/254;
		}
	}
//if(valu_temp!=0)
	DataConvert_to_Text(valu_temp,CalcInput_Text); //ת��Ϊ ��ʾ����
}


void ShowTouchWind(void)//��������window
{
ClrInput_function();//���� �����
	//���� ������
CalcNoNumInput_flag=1;
Dot_flag=0;
CalcSign_order=0;//�׸������ λ��
CalcData_temp=0;
CalcResultDis_flag=0;
num_cou=0;
if(Sign_flag==1)//��� ��,����
	{
	GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
	Sign_flag=0;
	}

CalcInput_cou=0;
Calculator_Window();  //������ ��ť	
ClrCalcNums_text(CalcInput_Text,CAL_INPUT); //������� �����
ClrCalcNums_text(CalcResult_Text,CAL_RESULT); //������� ����� 
CalcInputNums_dis(CalcInput_Text);  //����� ��ʾ
CalcResultNums_dis(CalcResult_Text);//����� ��ʾ
InputTouch_flag=1;
}
//------------
void ArithmeticInputSize(void)  //�Ե�ǰ�ߴ� ��������
{
volatile Int32U newsize_temp=0,prev_data;
volatile Int8U Flg_chg=0,flag_now;
if(Knife_order<MAIX_Knife)	//������ δ��
	{
	CheckInputNums();
	if(InputSize>0)
		{
		pKnife_data=(pInt8U)&OneKnife_data;
		GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);// ��ȡ��ǰ�� �ߴ�
		prev_data=OneKnife_data.size;
		switch(Arithmetic_mode)
			{
			case 0:
					break;
			case PLUS_SIGN: //  +
				newsize_temp=prev_data+InputSize;
					break;
			case MINUS_SIGN: //  -	
				if(prev_data>InputSize)
					newsize_temp=prev_data-InputSize;
				else
					newsize_temp=0;
					break;
			case MULT_SIGN: //*	
				newsize_temp=prev_data*InputSize;
				if(Unit!=UNIT_MM)
					{
					newsize_temp/=1000;
					}	
				else
					{
					newsize_temp/=100;
					}
					break;
			case DIV_SIGN:  //  ��/
				if(Unit!=UNIT_MM)
					{
					newsize_temp=prev_data*1000;
					}	
				else
					{
					newsize_temp=prev_data*100;
					}
				newsize_temp=newsize_temp/InputSize;
					break;
			}
			
		if((newsize_temp<Size_MIN_num)||(newsize_temp>Size_MAX_num))//������Χ
			{
			//num_cou=0;
			GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
			PromptDis_flag=0;
			GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
			switch(Language)
				{
				case CHN_HAN:
						Printf24("����ߴ糬������!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
				case ENGLISH:
						Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
				}
			// // if(InputTouch_flag==1)   //������
				// // {
				// // ClearCalculatorInput(); //��������� ����
				// // }	
			}
		else   //������Ч		
			{
			// // if(Unit==UNIT_MM)//mm
				// // {
				// // TargetSize=d_temp;
				// // NewInput_dis(TargetSize);
				// // }
			// // else
				// // {
				// // TargetSize_inch=d_temp;
				// // TargetSize=TargetSize_inch*2.54;
				// // NewInput_dis(TargetSize_inch);
				// // }

			
			//----��������----------------
			if(Knife_order<=Knife_sum)  //���� ���һ�� 000.00
				{
				Knife_order++;
				GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);// ��ȡ  ��һ��
				OneKnife_data.size=newsize_temp;  //�ߴ��޸�
				//SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//����һ������
				if(Knife_order<=Knife_sum)// δ�������һ��
					{
					if(OneKnife_data.k_flag==KNIFE_FLAG)
						{
						if(newsize_temp>prev_data)
							{
							OneKnife_data.k_flag=0; //�� ��־���
							Flg_chg=1;
							flag_now=OneKnife_data.k_flag;
							}
						}
					}
				SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//����һ������
				if((Knife_order+1)<=Knife_sum)
					{
					GetOneKnife_datas(Pro_data.pro_num, Knife_order+1, pKnife_data);// ��ǰ������һ�� ����
					 if(OneKnife_data.k_flag==KNIFE_FLAG) //�� ��־
						{
						if(OneKnife_data.size>newsize_temp)
							{
							OneKnife_data.k_flag=0;	//��� �� ��־
							if(Flg_chg==1)
								{
								Flg_chg=3;
								}
							else
								{
								Flg_chg=2;
								}
							SaveOneKnife_datas(Pro_data.pro_num, Knife_order+1 , pKnife_data);//������һ��	
							}
						}
					}
				else
					{
					
					}
					
				//---------��ʾ----
				if(Knife_order>Knife_sum)//���²��� �ܵ���
					{
					Knife_sum=Knife_order;
									SaveKnife_sum(Pro_data.pro_num);//���� ����
					}
				StepNum_dis(Knife_sum,Knife_order);//�������	
				//--------������ ��ʾ
				if(cursor_row<(PAGE_KNIFE-1))
					{
					CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
					OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //һ������ ������ʾ
					cursor_row++;
					CursorMov_dis(cursor_row, 1);//��ɫ���������ʾ
					OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //һ������ ������ʾ
					if(InputTouch_flag==0) //	 �� ���������� ��
						{
						switch(Flg_chg)
							{
							case 1:
								PushFlag_dis(cursor_row,flag_now); // ���ͼƬ ��ʾ
								break;
							case 2:
								PushFlag_dis(cursor_row+1,OneKnife_data.k_flag); //��괦 ���ͼƬ ��ʾ
								break;
							case 3:
								PushFlag_dis(cursor_row,flag_now); // ���ͼƬ ��ʾ
								PushFlag_dis(cursor_row+1,OneKnife_data.k_flag); //��괦 ���ͼƬ ��ʾ
								break;
							}
						}
					}
				else   //ҳ��
					{
					Size_1page_dis(Knife_order-(PAGE_KNIFE-1),0);//һҳ�ߴ���ʾ
					}
				}
				
				 
			PromptNum_dis();//���뷶Χ ��ʾ
			PromptDis_flag=1;	
			GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������ ����	
			}
			
		ClrInput_function();//���� �����
		Arithmetic_mode=0;
		}
	}
}


void ShiftSpeed_SetExec(Int32U keycode)  //�������ͣ������趨������
{
switch(keycode)
	{
	case DENGJU_KEY_CODE:       //���ϼ�ͷ
		if(MotorType>0)
			{
			SpeedLevelSel_dis(MotorType--,0);
			SpeedLevelSel_dis(MotorType,1);
			SaveMachineType(); //����  ��������
			}
		break;
	case DENGFENG_KEY_CODE:   //���¼�ͷ	
		if(MotorType<6)
			{
			SpeedLevelSel_dis(MotorType++,0);
			SpeedLevelSel_dis(MotorType,1);
			SaveMachineType(); //����  ��������
			}
		break;
	case DOWN_KEY_CODE:   // ȷ��	
		break;
	}
}
void LongKey_exec(Int32U keycode,Int32U key_temp)  //����������
{
if(keycode==key_temp)
	 {
	 switch(keycode)
		 {
		 case FIVE_KEY_CODE:  //ɾ��
			  BellOn_Enb();
			  if(WorkStart_flag==1)
				 {
				 if(Run_flag==0)
					{
					if(InputTouch_flag==0)
						{
						if((WorkMode==PROG_MODE)||(WorkMode==TEACH_MODE)||(WorkMode==AUTO_MODE))//���,ʾ�̻�����
						  {
						  if(Knife_order<=Knife_sum)
							 {
							  ClrBuf_datas(Pro_data.pro_num, Knife_order, Knife_sum );//����
							  SaveBuf_datas(Pro_data.pro_num, Knife_order, Knife_sum );//����
							  Size_1page_dis(Knife_order,cursor_row);//��ʾһҳ

							  if(Knife_order>1)
								{
								Knife_sum=Knife_order-1;
								}
							  else
								{
								Knife_sum=1;
								}
							  SaveKnife_sum(Pro_data.pro_num);//���� ����
							  StepNum_dis(Knife_sum,Knife_order);//�������
							 }
						  }
						}
					}
				  else
					{
					
					}
				 }
					  break;
		 case ONE_KEY_CODE:		// F ���ܰ���
			  BellOn_Enb();
			  if(WorkStart_flag==1)
				 {
				 if(Run_flag==0)
					{
					if(InputTouch_flag==0)
						{
						switch(WorkMode)
							{
							case AUTO_MODE://  �Զ�ģʽ��
								WorkMode=AUTO_TO_SELF_MODE;   //�Զ�-->�Ե����� ģʽ
								PaperCutEnb_signal=1;
								SelfEnterPage_dis();
									break;
							case SELF_CUT_MODE:  //		�Ե��� ģʽ
								//------------���ص�һ��
								ClrInput_function();//���� ����� 
								CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
								cursor_row=0;
								CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
								Knife_order=1;//
								Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
								if(Knife_order<=Knife_sum)
									StepOrder_dis(Knife_order);//������� 
								PromptNum_dis();//���뷶Χ	
								PromptDis_flag=1; 	
									break;
							case SELF_RULER_MODE://�Ե� ��׼
							case SELF_TOOLS_MODE://�Ե� ����
								PaperCutEnb_signal=1;
								CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
								WorkMode=SELF_CUT_MODE;  //����   ----------�Ե��� ģʽ
								AutoKnife_dis(SELF_KNIFE_X,SELF_KNIFE_Y);//�Ե�
								//------------���ص�һ��
								ClrInput_function();//���� ����� 
								CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
								cursor_row=0;
								CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
								Knife_order=1;//
								Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
								if(Knife_order<=Knife_sum)
									StepOrder_dis(Knife_order);//������� 
								PromptNum_dis();//���뷶Χ	
								PromptDis_flag=1; 	
									break;
							case SELF_PLUS_MODE: //�Ե� F3++
								PaperCutEnb_signal=1;
								F3_plus_dis(0);
								WorkMode=SELF_CUT_MODE;
								//------------���ص�һ��
								ClrInput_function();//���� ����� 
								CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
								cursor_row=0;
								CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
								Knife_order=1;//
								Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
								if(Knife_order<=Knife_sum)
									StepOrder_dis(Knife_order);//������� 
								PromptNum_dis();//���뷶Χ	
								PromptDis_flag=1; 	
									break;
							case SELF_MINUS_MODE://�Ե� F4--
								PaperCutEnb_signal=1;
								F4_minus_dis(0);
								WorkMode=SELF_CUT_MODE;
								//------------���ص�һ��
								ClrInput_function();//���� ����� 
								CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
								cursor_row=0;
								CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
								Knife_order=1;//
								Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
								if(Knife_order<=Knife_sum)
									StepOrder_dis(Knife_order);//������� 
								PromptNum_dis();//���뷶Χ	
								PromptDis_flag=1; 	
									break;
							}
						}
					}
				  else
					{
					
					}
				 }
					break;
		 }
	 }
}

void MultiKey_exec(Int32U keycode)  //��ϼ�����
{
Int16U knife;
Int8U knife_set_flag=0;
pInt8U pbuf;
Int32U offset;
Int16U j;
switch (keycode)
	 {
	 case ONE_KEY_CODE+NINE_KEY_CODE:		//F ���ܰ��� + 1 ***********
			LongExec_flag=1;	
			KeyExec(AUTO_KEY_CODE);	//F1  code
				break;
	 case ONE_KEY_CODE+MOVE_KEY_CODE:		// F ���ܰ��� +2************
			LongExec_flag=1;	
			KeyExec(READ_KEY_CODE);	//F2  code
				break;
	 case ONE_KEY_CODE+DELETE_KEY_CODE:		//F ���ܰ��� + 3 ***********
			LongExec_flag=1;	
			KeyExec(RETURN_KEY_CODE);	//F3  code
				break;
	 case ONE_KEY_CODE+EIGHT_KEY_CODE:		// F ���ܰ��� +4************
			LongExec_flag=1;	
			KeyExec(MANUAL_KEY_CODE);	//F4  code
				break;
				
	 case ONE_KEY_CODE+NO_KEY_CODE:		  //F ���ܰ��� + 5 ***********����־
			BellOn_Enb();
			LongExec_flag=1;	
			if(WorkStart_flag==1)
				{
				if(Run_flag==0)
				  {
				  if(InputTouch_flag==0)
					 {
					  switch(WorkMode)
						  {
						  case PROG_MODE://��̻�����
						  case TEACH_MODE://ʾ�̻�����
							//----��������----------------
							 if(Knife_order>1)
								{
								 pKnife_data=(pInt8U)&OneKnife_data;
								 GetOneKnife_datas(Pro_data.pro_num, Knife_order-1, pKnife_data);//
								 InputSize=OneKnife_data.size;
								 GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);//
								 if((OneKnife_data.size<InputSize)&&(OneKnife_data.size>0))//С�� ǰһ��
									{
									if(OneKnife_data.k_flag!=KNIFE_FLAG) //
										{
										OneKnife_data.k_flag=KNIFE_FLAG;//  �趨 ����־
										}
									else
										{
										OneKnife_data.k_flag=0;// ��� ��־
										}
									PushFlag_dis(cursor_row,OneKnife_data.k_flag); //��ʾ----
									SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//����һ������
									PromptNum_dis();//���뷶Χ
									PromptDis_flag=1;
									}
								 else
									{
									PromptDis_flag=0;
									GLCD_SetWindow_Fill(REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
									switch(Language)
										{
										case CHN_HAN:
											Printf24("�˵���־�趨��Ч!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
										case ENGLISH:
											Printf24("Invalid Mark!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
										}
									}
									
								}
							 else
								{
								PromptDis_flag=0;
								GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
								switch(Language)
										{
										case CHN_HAN:
											Printf24("�˵���־�趨��Ч!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
										case ENGLISH:
											Printf24("Invalid Mark!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
										}
								}
								break;
						  case AUTO_MODE://�Զ� ��ģʽ��
								pKnife_data=(pInt8U)&OneKnife_data;
								GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);//
								if(OneKnife_data.size>0)
									{
									if(OneKnife_data.k_flag!=PRE_AUTO_FLAG)  //�Զ�ѭ��ͼ��
										{
										OneKnife_data.k_flag=PRE_AUTO_FLAG;//  �趨 ��־
										}
									else
										{
										OneKnife_data.k_flag=0;// ��� ��־
										}
									PushFlag_dis(cursor_row,OneKnife_data.k_flag); //��ʾ----
									// RenewModifyDate();	//����ʱ����Ϣ-.-.-.-.-.-.-.-.-.-.-.-.-.-
									SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//����һ������
									PromptNum_dis();//���뷶Χ
									PromptDis_flag=1;
									}
						  		break;
						  }
					 }
				  }
				else//������
				  {
				  
				  }
				}
				break;
	 case ONE_KEY_CODE+ PROG_KEY_CODE: //F ���ܰ��� +  ����0************ ���� ����־
			BellOn_Enb();
			LongExec_flag=1;
			if(WorkStart_flag==1)
				{
				if(Run_flag==0)
				  {
				  if(InputTouch_flag==0)
					 {
					  switch(WorkMode)
						  {
						  case PROG_MODE://��̻�����
						  case TEACH_MODE://ʾ�̻�����
								knife=2;
								
								if(Pro_data.pro_num<=(PROG_GROPU1+1))  //ǰ301��prog
								   {
								   offset=PROG_BYTES1*(Pro_data.pro_num-1);
								   }
								else//��  199
								   {
								   offset=PROG_BYTES1*PROG_GROPU1+(Pro_data.pro_num-PROG_GROPU1-1)*PROG_BYTES2;
								   }
								pbuf=(pInt8U)(K_SIZE_sdram+offset+2+(knife-1)*5+4);//�������ַ
								
							//----  �������е�  ��־-------------
								pKnife_data=(pInt8U)&OneKnife_data;
								
								GetOneKnife_datas(Pro_data.pro_num, knife-1, pKnife_data);//
								while(knife<=Knife_sum)
									{
									
									if(AllKnifeSet_flag==0)//�趨 ���е���־
										{
										
										InputSize=OneKnife_data.size;
										GetOneKnife_datas(Pro_data.pro_num, knife, pKnife_data);//
										if((OneKnife_data.size<InputSize)&&(OneKnife_data.size>0))//С�� ǰһ��
											{
											if(OneKnife_data.k_flag!=KNIFE_FLAG) 
												{
												//OneKnife_data.k_flag=KNIFE_FLAG;  
												//SaveOneKnife_datas(Pro_data.pro_num,knife , pKnife_data);//����һ������
												//*pbuf=*(pKnife_data+4);
												*pbuf=KNIFE_FLAG;
												}
											}
										pbuf+=5;
										}
									else	 //���  ���е���־
										{
										GetOneKnife_datas(Pro_data.pro_num, knife, pKnife_data);//
										if(OneKnife_data.k_flag==KNIFE_FLAG) 
											{
											//OneKnife_data.k_flag=0;// ��� ��־
											//SaveOneKnife_datas(Pro_data.pro_num,knife , pKnife_data);//����һ������
											*pbuf=0;
											}
										pbuf+=5;	
										}
									knife_set_flag=1;	
											
									knife++;	
									}
									
									
									
									
									
									if(AllKnifeSet_flag==0)
										AllKnifeSet_flag=1;
									else
										AllKnifeSet_flag=0;
										
								if(knife_set_flag==1)   //����  ��ʾ---------
									{
									SaveBuf_datas(Pro_data.pro_num, 1, Knife_sum );//����
									//------------���ص�һ��
									ClrInput_function();//���� ����� 
									CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
									cursor_row=0;
									CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
									Knife_order=1;//
									Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
									if(Knife_order<=Knife_sum)
										StepOrder_dis(Knife_order);//�������	
									//PromptNum_dis();//���뷶Χ
									//PromptDis_flag=1;	
									}
									break;
						  }
					 }
				  }
				}
				break;
	 case DENGJU_KEY_CODE+MOVE_KEY_CODE:	//���ϼ�ͷ+2  ���嵱�� �趨
			BellOn_Enb();
			LongExec_flag=1;
			if(WorkStart_flag==1)
			  {
			   if(MotorType<MOTOR_DC_SERVO)    //��Ƶ��--
				  {
				  if(Run_flag==0)
					 {
					 if(InputTouch_flag==0)
						{
						 switch(WorkMode)
							{
							case MANUAL_MODE: //�ֶ�ģʽ
								if(Sign_flag==1)
									{
									num_cou=0;
									GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
									Sign_flag=0;
									}
								 WorkMode=MANUAL_PULSE_MODE;
								 PulseDegreePage_dis();
								 PromptDis_flag=0;
								 ClrInput_function();//���� �����
								 Para_sel=Pulse_degree;
									break;
							}
						}	
					 }
				   else	//������
					 {
					 }
				  }
			  }
				break;
	 case DENGFENG_KEY_CODE+YES_KEY_CODE://���¼�ͷ+8 ����ģʽ
			BellOn_Enb();
			LongExec_flag=1;
			if(WorkStart_flag==1)
			  {
			  if(Run_flag==0)
				 {
				 if(InputTouch_flag==0)
					{
					switch(WorkMode)
						{
						case MANUAL_MODE: //�ֶ�ģʽ
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								}
							 WorkMode=MANUAL_PASS_MODE;
							 PassCodePage_dis();
							 PromptDis_flag=0;
							 ClrInput_function();//���� �����
							 ACServoAlarmExec_flag=0;
							 break;
						}
					}	
				 }
			  else
				 {
				 
				 }
			  }
				break; 
	 case ONE_KEY_CODE+INSERT_KEY_CODE:   //        F���ܰ���+6 ----------ʾ��ģʽ
			BellOn_Enb();
			LongExec_flag=1;
			if(WorkStart_flag==1)
			  {
			  if(Run_flag==0)
				 {
				 if(InputTouch_flag==0)
					{
					switch(WorkMode)
						{
						case TEACH_LABEL_MODE: //��ǩ
						case TEACH_DIVIDE_MODE: //�ȷ�
						case TEACH_PRO_MODE: //����ѡ��
							CurrentArea_recover2(MIDDLE_PAGE_X, MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							
						case AUTO_MODE://�Զ� ��ģʽ��************
						case SELF_CUT_MODE://�Ե���������
						case MANUAL_MODE:// �ֶ� ��ģʽ
							
						case PROG_MODE://��� ��ģʽ��
							WorkMode=TEACH_MODE;  //ʾ��ģʽ
							TeachPage_dis();
							PromptNum_dis();//���뷶Χ	
							PromptDis_flag=1; 
						case TEACH_MODE: //ʾ����ģʽ	
							//------------���ص�һ��
							PaperCutEnb_signal=1;
							ClrInput_function();//���� ����� 
							CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
							cursor_row=0;
							CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
							if(Knife_order<=Knife_sum)
								StepOrder_dis(Knife_order);//�������
								
							ACServoAlarmExec_flag=0;	
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								}
								break;
						}	
					}
				 }
			  else
				 {
				 
				 }
			  }
				break;
	 case DENGJU_KEY_CODE+DELETE_KEY_CODE:  //	���ϼ�ͷ+3  ��λѡ��
			BellOn_Enb();
			LongExec_flag=1;	
			if(WorkStart_flag==0)  //δ���빤��״̬
				{
				switch(MotorType)
					{
					case MOTOR_FREQ_5_SPD_RST:
					case MOTOR_FREQ_3_SPD:
					case MOTOR_FREQ_3_SPD_RST:
					case MOTOR_AC_SERVO:
						if((StartCheck_mode<2)||(StartCheck_mode==4))
							CheckModeOK_flag=1;
						else	
							CheckModeOK_flag=0;
							break;
					case MOTOR_DC_SERVO:
					case MOTOR_DC670_SERVO:
					case MOTOR_DC670_SERVO_ZHU:
					// case MOTOR_AC_SERVO:
						if(StartCheck_mode<5)	
							CheckModeOK_flag=1;
						else	
							CheckModeOK_flag=0;
							break;
					default:
							CheckModeOK_flag=0;
							break;
					}	
				if(CheckModeOK_flag==1)
					{
					if(Board_TestMod==0)
						{
						Board_TestMod=TEST_MOTOR_TYPE;     //��������趨  ģʽ
						GLCD_Buffer_Fill(0xffff);
						SpeedLevelSel_dis(0,0);    //������� ��ʾ
						SpeedLevelSel_dis(1,0);    //������� ��ʾ
						SpeedLevelSel_dis(2,0);    //������� ��ʾ
						SpeedLevelSel_dis(3,0);    //������� ��ʾ
						SpeedLevelSel_dis(4,0);    //������� ��ʾ
						SpeedLevelSel_dis(5,0);    //������� ��ʾ
						SpeedLevelSel_dis(6,0);    //������� ��ʾ
						SpeedLevelSel_dis(MotorType,1);
						}
					}	
				}
				break;
	case DENGJU_KEY_CODE+NINE_KEY_CODE:			//���ϼ�ͷ+1  ���嵱�� �趨
			BellOn_Enb();
			LongExec_flag=1;
			if(WorkStart_flag==1)
			  {
			   if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))    //DC�ŷ�--
				  {
				  if(Run_flag==0)
					 {
					 if(InputTouch_flag==0)
						{
						 switch(WorkMode)
							{
							case MANUAL_MODE: //�ֶ�ģʽ
								if(Sign_flag==1)
									{
									num_cou=0;
									GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
									Sign_flag=0;
									}
								 WorkMode=MANUAL_SERVO_C_MODE;   //ֱ���ŷ� C ����
								 Servo_C_DataPage();//ֱ���ŷ� ��C������
								 PromptDis_flag=0;
								 Para_sel=0;
								 ClrInput_function();//���� �����
									break;
							}
						}	
					 }
				   else	//������
					 {
					 }
				  }
			  }
			else
			  {//--------------------------����У׼
				KeyExec(AUTO_KEY_CODE);	//F1  code
			  }
				break;
	case ONE_KEY_CODE+REV_KEY_CODE:   //    ***************F���ܰ���+ ��+/*��
			BellOn_Enb();
			LongExec_flag=1;
			if(WorkStart_flag==1)  
				{
				if(Run_flag==0)
					{
					if(InputTouch_flag==0)
						{
						switch(WorkMode)
							{
							//case MANUAL_MODE:   //�ֶ�
							case PROG_MODE:	//���ģʽ
							case TEACH_MODE:   //ʾ��ģʽ
								if(Sign_flag==0)         //* ��
									{
									ClrInput_function();//���� �����
									Printf24(" *",SIZE_WINDOW_X,SIZE_WINDOW_Y,RED_COLOR,1,0xffff);
									Sign_flag=1;
									Minus_flag=0;
									Arithmetic_mode=MULT_SIGN;//  "*"
									} 
								else               //��� *��
									{
									num_cou=0;
									GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
									Sign_flag=0;
									Arithmetic_mode=NO_SIGN;//---0
									}
									break;
							}
						}
					else    //������ ����ģʽ
						{
						CalculatorValue_exec('*');	
						}
					
					}	
				} 	
				break;
	case ONE_KEY_CODE+OPTION_KEY_CODE:   //    ***************F���ܰ���+ ��-/����
			BellOn_Enb();
			LongExec_flag=1;
			if(WorkStart_flag==1)  
				{
				if(Run_flag==0)
					{
					if(InputTouch_flag==0)
						{
						switch(WorkMode)
							{
							//case MANUAL_MODE:   //�ֶ�
							case PROG_MODE:	//���ģʽ
							case TEACH_MODE:   //ʾ��ģʽ
								if(Sign_flag==0)         //�� ��
									{
									ClrInput_function();//���� �����
									Printf24(" /",SIZE_WINDOW_X,SIZE_WINDOW_Y,RED_COLOR,1,0xffff);
									Sign_flag=1;
									Minus_flag=0;
									Arithmetic_mode=DIV_SIGN;//  "/"
									} 
								else               //��� *��
									{
									num_cou=0;
									GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
									Sign_flag=0;
									Arithmetic_mode=NO_SIGN;//---0
									}
									break;
							}
						}
					else    //������ ����ģʽ
						{
						CalculatorValue_exec('/');	
						}
					
					}	
				} 	
				break;			
	 }
}

void KeyExec(Int32U keycode)  //������
{
Int32U d_temp=0;
Int32U target_temp;
Int32U input_temp,perv_data;
	 
Int16U x,y,gap,back_color,line_color;

Int16U knife,K_temp;
Int8U knife_set_flag=0,Flg_chg=0,flag_now;
pInt8U pbuf;
Int32U offset;
Int16U ServMaxSpd1,ServMaxSpd2;

BellOn_Enb();
switch(keycode)
	{
	//case tst_KEY_CODE: //ֹͣ
	case STOP_KEY_CODE: //ֹͣ
		if(WorkStart_flag==1)
			{
			if(Run_flag==1)  //������
				{
				if(AutoCutStart_flag==0)
					{
					switch(MotorType)
						{
						case MOTOR_FREQ_5_SPD_RST:
						case MOTOR_FREQ_3_SPD:
						case MOTOR_FREQ_3_SPD_RST:
							SelfLockEn_flag=0; //ȡ������
							ToTargetStop_flag=0;
							MoveStop();
							ForceStop_flag=0;
							BackStop_flag=0;
							Backward_flag=0;
							Forward_flag=0;	
							RunStop_flag=0;
								break;
						case MOTOR_DC_SERVO:
						case MOTOR_DC670_SERVO:
						case MOTOR_DC670_SERVO_ZHU:
							DCServoStop();  //ֹͣ����
							ServoPressStop_flag=0;
							DcServoGoTarget_flag=0;
							BellStart_flag=0;
								break;
						case MOTOR_AC_SERVO:
							ACServoStop();
								break;
						}
					Run_flag=0;	
					InTargetPosit_flag=0;	//Ŀ��λ��
					AutoPushRun_flag=0; //�Զ���ֽ ����
					TargetSize=0;
					TargetSize_temp=0;
					BeforeKnife_offset_in=0;
					if(InputTouch_flag==0)
						ClrInput_function();//���� �����
					//PaperCutEnb_signal=1;	
					AutoRoute_flag=0;
					RLOUT1_OFF;    // �������
					}
				}
			else
				{
				if(MotorType<MOTOR_DC_SERVO)
					{
					if(FreqMotorStop_flag==0)  //ǿ��  ֹͣ
						{
						SelfLockEn_flag=0; //ȡ������
						ToTargetStop_flag=0;
						MoveStop();
						ForceStop_flag=0;
						BackStop_flag=0;
						Backward_flag=0;
						Forward_flag=0;	
						RunStop_flag=0;
						
						InTargetPosit_flag=0;	//Ŀ��λ��
						AutoPushRun_flag=0; //�Զ���ֽ ����
						TargetSize=0;
						TargetSize_temp=0;
						BeforeKnife_offset_in=0;
						if(InputTouch_flag==0)
							ClrInput_function();//���� �����
						//PaperCutEnb_signal=1;	
						AutoRoute_flag=0;
						RLOUT1_OFF; RLOUT1_1_OFF;   // �������
						}
					}
				}
			}	
			break;
    case NINE_KEY_CODE+MOVE_KEY_CODE:
			break; 
	case   	0xffff000c: //��������  ����
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
				{
				if(MotorType==MOTOR_AC_SERVO)
					{
					switch(WorkMode)
						{
						case AUTO_MODE://�Զ�
						case MANUAL_MODE:   //�ֶ�
							ElectricWheelOn_flag=!ElectricWheelOn_flag;
							SaveElectricWheelSwitch();//��������
							ElectricalWheel_dis();  //��������  ����״̬
								break;
						}
					}
				}
			}
			break; 
    case   	0xffff0007://MUL_TOUCH_CODE    �˷�  *
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
				{
				if(InputTouch_flag==1)
					{
					CalculatorValue_exec('*');
					}
				}
			}	
			break;
   	case	0xffff0008:  //   DIV_TOUCH_CODE  ����/
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
				{
				if(InputTouch_flag==1)
					{
					CalculatorValue_exec('/');
					}
				}
			}
			break;
	case	0xffff0009:  //     EQU_TOUCH_CODE       ��� =  
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
				{
				if(InputTouch_flag==1)
					{
					if(WorkMode == TEACH_MODE)	//=======ʾ�� ģʽ========  ���е���ǰ ֵ
						{
						if(CheckInputNums()==1)// ���� ��Ч
							{
							if(InputSize!=CurrentSize)
								{
								if(Unit==UNIT_MM)//mm
									{
									TargetSize=InputSize;
									}
								else
									{
									TargetSize_inch=InputSize;
									TargetSize=TargetSize_inch*2.54;
									}
								TargetSize_temp=TargetSize;
								switch(MotorType)
									{
									case MOTOR_FREQ_5_SPD_RST:
									case MOTOR_FREQ_3_SPD:
									case MOTOR_FREQ_3_SPD_RST:
										 SelfLockEn_flag=0;
										 ToTargetStop_flag=0;
										 MoveSpeed=0;
										 MoveSpeedCtrl();  //�����ٶȿ���
											break;
									case MOTOR_DC_SERVO:
									case MOTOR_DC670_SERVO:
									case MOTOR_DC670_SERVO_ZHU:
										 ServoSendCou=0;
										 DcServoStartRun_exec(TargetSize);
										// SelfLockEn_flag=0;
											break;
									case MOTOR_AC_SERVO:
										 ACMotorRunStart(TargetSize);
										// SelfLockEn_flag=0;
											break;		
									}
								Run_flag=1;
								RunStop_flag=0;
								InTargetPosit_flag=0;	//Ŀ��λ��
								OneCutRoutine_flag=0; // �� ���� ѭ����־
								AutoCutStart_flag=0;
								PromptNum_dis();
								}
							}				
						}
					else
						{
						if(CalcResultDis_flag==0)
							{
							CalcGetValue_exec();
							}	
						}
					}
				}
			}
			break;		
	case 0xffff0001:	//INPUT_TOUCH_CODE	 ����� ���� 
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
				{
				ClrInput_function();//���� �����
				if(InputTouch_flag==0)  //���봥�� ����������
					{
					CalcNoNumInput_flag=1;
					Dot_flag=0;
					CalcSign_order=0;//�׸������ λ��
					CalcData_temp=0;
					CalcResultDis_flag=0;
					num_cou=0;
					if(Sign_flag==1)//��� ��,����
						{
						GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
						Sign_flag=0;
						}
					
					CalcInput_cou=0;
					Calculator_Window();  //������ ��ť	
					ClrCalcNums_text(CalcInput_Text,CAL_INPUT); //������� �����
					ClrCalcNums_text(CalcResult_Text,CAL_RESULT); //������� ����� 
					CalcInputNums_dis(CalcInput_Text);  //����� ��ʾ
					CalcResultNums_dis(CalcResult_Text);//����� ��ʾ
					InputTouch_flag=1;
					}
				else         //�˳�
					{
					//CalcInput_cou=0;
					CalcuInClear_exec();     //��� ������
					switch(WorkMode)
						{
						case AUTO_TOOLS_MODE:
						case MANUAL_TOOLS_MODE:
						case SELF_TOOLS_MODE:
							back_color=0xef9f;
							x=PARA_START_X1+PARA_COL_WIDE,y=PARA_START_Y,gap=30;
							if(PramSel_Page<1)	//page 1
								{
								//if(Para_sel<7)
								//	{
									ParameterPage_dis(7, 0);
									if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
										{
										ParameterPage_dis(8, 0);
										ParameterPage_dis(9, 0);
										}
									else if(MotorType==MOTOR_AC_SERVO)	
										{
										ParameterPage_dis(8, 0);
										}
									ParameterPage_dis(Para_sel, 1);
								//	}
								switch(Language)
									{
									case CHN_HAN:
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
								}
							else	//page 2
								{
									
								}
							
							break;
						
						case  PROG_MODE://��̻�����
						case AUTO_MODE://�Զ���������
						case AUTO_PLUS_MODE://�Զ�F3++
						case AUTO_MINUS_MODE://�Զ�F4--
						case TEACH_MODE://ʾ�� ģʽ
						case AUTO_TO_SELF_MODE:   //�Զ�-->�Ե����� ģʽ
						case SELF_CUT_MODE:  //�Ե��� ģʽ
						case SELF_PLUS_MODE: //�Ե� F3++
						case SELF_MINUS_MODE://�Ե� F4--
							if(Knife_order>Knife_sum)
								 K_temp=Knife_order-1;
							 else
								 K_temp=Knife_order;
							ProgressBar_dis(Knife_sum,K_temp);  //������ ��ʾ
							KnifeUp_flag=0;
							KnifeDown_flag=0;
							PressUp_flag=0;
							PressDown_flag=0;
							A_Down_flag=0;
							B_Down_flag=0;
							A_Up_flag=0;
							B_Up_flag=0;
							IR_Up_flag=0;
							IR_Down_flag=0;
							//--------------������ʾ��������ֽ��־
							// CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
							// cursor_row=0;
							// CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
							//Knife_order=1;//
							Size_1page_dis(Knife_order-cursor_row,0);//һҳ�ߴ���ʾ
							break;
						}
					}
				}
			else   //������
				{
				
				}
		    }
        	break;      
	case ONE_KEY_CODE:		// F ���ܰ���******************
		if(WorkStart_flag==0)  //δ���빤��״̬
			{
			switch(MotorType)
				{
				case MOTOR_FREQ_5_SPD_RST:
				case MOTOR_FREQ_3_SPD:
				case MOTOR_FREQ_3_SPD_RST:
				case MOTOR_AC_SERVO:
						if((StartCheck_mode<2)||(StartCheck_mode==4))
							CheckModeOK_flag=1;
						else
							CheckModeOK_flag=0;
						break;
				case MOTOR_DC_SERVO:
				case MOTOR_DC670_SERVO:
				case MOTOR_DC670_SERVO_ZHU:
						if(StartCheck_mode<2)
							CheckModeOK_flag=1;
						else
							CheckModeOK_flag=0;
						break;
				// case MOTOR_AC_SERVO:
						// if(StartCheck_mode<3)
							// CheckModeOK_flag=1;
						// else
							// CheckModeOK_flag=0;
						// break;		
				default:
						CheckModeOK_flag=0;
						break;
				}
			if(CheckModeOK_flag==1)
				{
				if(Board_TestMod==0)
					{
					Board_TestMod=TEST_BOARD;     //�������  ģʽ
					GLCD_Buffer_Fill(0xffff);
					IO_InputDisInit();  //Io ����ڳ�ʼֵ
					KeyDis_Init();//������ʾ��ʼ��
					}
				else if(Board_TestMod==TEST_BOARD)
					{
					
					}
				}
			}
		else
			{
			if(Run_flag==1)  //������
				{
				if(AutoCutStart_flag==0)
					{
					switch(MotorType)
						{
						case MOTOR_FREQ_5_SPD_RST:
						case MOTOR_FREQ_3_SPD:
						case MOTOR_FREQ_3_SPD_RST:
							SelfLockEn_flag=0; //ȡ������
							ToTargetStop_flag=0;
							MoveStop();
							ForceStop_flag=0;
							BackStop_flag=0;
							Backward_flag=0;
							Forward_flag=0;	
							RunStop_flag=0;
								break;
						case MOTOR_DC_SERVO:
						case MOTOR_DC670_SERVO:
						case MOTOR_DC670_SERVO_ZHU:
							DCServoStop();  //ֹͣ����
							ServoPressStop_flag=0;
							DcServoGoTarget_flag=0;
							BellStart_flag=0;
								break;
						case MOTOR_AC_SERVO:
							ACServoStop();
								break;		
						}
					Run_flag=0;	
					InTargetPosit_flag=0;	//Ŀ��λ��
					AutoPushRun_flag=0; //�Զ���ֽ ����
					TargetSize=0;
					TargetSize_temp=0;
					BeforeKnife_offset_in=0;
					if(InputTouch_flag==0)
						ClrInput_function();//���� �����
					AutoRoute_flag=0;	
					RLOUT1_OFF; RLOUT1_1_OFF;   // �������
					}
				}
			else
				{
				if(MotorType<MOTOR_DC_SERVO)
					{
					if(FreqMotorStop_flag==0)  //ǿ��  ֹͣ
						{
						SelfLockEn_flag=0; //ȡ������
						ToTargetStop_flag=0;
						MoveStop();
						ForceStop_flag=0;
						BackStop_flag=0;
						Backward_flag=0;
						Forward_flag=0;	
						RunStop_flag=0;
						
						InTargetPosit_flag=0;	//Ŀ��λ��
						AutoPushRun_flag=0; //�Զ���ֽ ����
						TargetSize=0;
						TargetSize_temp=0;
						BeforeKnife_offset_in=0;
						if(InputTouch_flag==0)
							ClrInput_function();//���� �����
						//PaperCutEnb_signal=1;	
						AutoRoute_flag=0;
						}
					}
				}
			}
  	         break;
	case TWO_KEY_CODE:		//�ֶ�****************
        if(WorkStart_flag==1)  
			{
			if(Run_flag==0)
			    {
				if(InputTouch_flag==0)
					{
					switch(WorkMode)
						{
						case PROG_MODE://��� ��ģʽ��********
						case TEACH_MODE://ʾ�� ģʽ
						case AUTO_MODE://�Զ� ��ģʽ��*******
						case SELF_CUT_MODE://�Ե���������
							WorkMode=MANUAL_MODE;  //���� �ֶ�ģʽ
							ManualModePage_dis();
							ClrInput_function();//���� �����
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1; 
							PaperCutEnb_signal=1;
							ACServoAlarmExec_flag=0;
							if(Sign_flag==1)//��� ��,����
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								}
							break;
						case MANUAL_TOOLS_MODE:// �ֶ� ����ģʽ
						case MANUAL_RULER_MODE://�ֶ� ��׼ģʽ
						case MANUAL_CLOCK_MODE://�ֶ� ʱ��ģʽ
						case MANUAL_PULSE_MODE://�ֶ� �����趨ģʽ
						case MANUAL_PASS_MODE://�ֶ� ����ģʽ
						case MANUAL_SERVO_C_MODE://�ֶ�ֱ���ŷ� C ���� 
							WorkMode=MANUAL_MODE;//����    ---------�ֶ� ��ģʽ
							Para_sel=0;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y, M_PAGE_WIDE, M_PAGE_HIGH);
							Manual_dis(MANUAL_X,MANUAL_Y);//�ֶ�
						case MANUAL_MODE:   //�ֶ�	
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								}	
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ClrInput_function();//���� �����
							ACServoAlarmExec_flag=0;
							break;		
						}		
					}
				else   //������
					{
					
					}
			    }
			else //������
			    {
				if(AutoCutStart_flag==0)
					{
					switch(MotorType)
						{
						case MOTOR_FREQ_5_SPD_RST:
						case MOTOR_FREQ_3_SPD:
						case MOTOR_FREQ_3_SPD_RST:
							ForceStop_flag=1;
							stop_time=0;
								break;
						case MOTOR_DC_SERVO:
						case MOTOR_DC670_SERVO:
						case MOTOR_DC670_SERVO_ZHU:
							DCServoStop();  //ֹͣ����
							ServoPressStop_flag=0;
							DcServoGoTarget_flag=0;
							BellStart_flag=0;
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//Ŀ��λ��
							AutoPushRun_flag=0; //�Զ���ֽ ����
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
								break;
						case MOTOR_AC_SERVO:
							ACServoStop();
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//Ŀ��λ��
							AutoPushRun_flag=0; //�Զ���ֽ ����
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
								break;
						}
					// TargetSize=0;
					// TargetSize_temp=0;
					// BeforeKnife_offset_in=0;
					if(InputTouch_flag==0)
						ClrInput_function();//���� �����
					}
				}
			}
  	     break;   
	case THREE_KEY_CODE:		//�Զ�******************
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
			    {
				if(InputTouch_flag==0)
					{
					switch(WorkMode)
						{
						case PROG_MODE://��� ��ģʽ��
						case TEACH_MODE://ʾ�� ģʽ
						case MANUAL_MODE:// �ֶ� ��ģʽ
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								}
						case SELF_CUT_MODE://�Ե���������
							WorkMode=AUTO_MODE;//���� �Զ�ģʽ
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							AutoModePage_dis();
							PromptNum_dis();//���뷶Χ	
							PromptDis_flag=1; 
						case AUTO_MODE://�Զ� ��ģʽ��
							//------------���ص�һ��
							ClrInput_function();//���� ����� 
							CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
							cursor_row=0;
							CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
							if(Knife_order<=Knife_sum)
								StepOrder_dis(Knife_order);//�������
							PromptNum_dis();//���뷶Χ	
							PromptDis_flag=1;  
							ACServoAlarmExec_flag=0;
							
							F0Button_dis(AllKnifeSet_flag);  //F0 ���� �� ��� ��ť/
							break;
							//�Զ�ģʽ------------------------------------------
						case AUTO_RULER_MODE:	//��׼ģʽ
						case AUTO_TOOLS_MODE:	 //����ģʽ	
							Para_sel=0;
							WorkMode=AUTO_MODE;//����    �Զ� ��ģʽ
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							Auto_dis(AUTO_X, AUTO_Y); //�Զ�
							//------------���ص�һ��
							ClrInput_function();//���� ����� 
							CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
							cursor_row=0;
							CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
							if(Knife_order<=Knife_sum)
								StepOrder_dis(Knife_order);//�������
							PromptNum_dis();//���뷶Χ	
							PromptDis_flag=1; 
							ACServoAlarmExec_flag=0;
							break;
						case AUTO_PLUS_MODE:// F3++
							WorkMode=AUTO_MODE;//����
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F3_plus_dis(0);
							//------------���ص�һ��
							ClrInput_function();//���� ����� 
							CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
							cursor_row=0;
							CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
							if(Knife_order<=Knife_sum)
								StepOrder_dis(Knife_order);//�������
							PromptNum_dis();//���뷶Χ	
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case AUTO_MINUS_MODE:// F4--
							WorkMode=AUTO_MODE;//����
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F4_minus_dis(0);
							//------------���ص�һ��
							ClrInput_function();//���� ����� 
							CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
							cursor_row=0;
							CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
							if(Knife_order<=Knife_sum)
								StepOrder_dis(Knife_order);//�������
							PromptNum_dis();//���뷶Χ	
							PromptDis_flag=1;	
							ACServoAlarmExec_flag=0;
							break;	
						}		
					}
				else  //������
					{
					
					}
				}
			else //������
			    {
				if(AutoCutStart_flag==0)
					{
					switch(MotorType)
						{
						case MOTOR_FREQ_5_SPD_RST:
						case MOTOR_FREQ_3_SPD:
						case MOTOR_FREQ_3_SPD_RST:
							ForceStop_flag=1;
							stop_time=0;
								break;
						case MOTOR_DC_SERVO:
						case MOTOR_DC670_SERVO:
						case MOTOR_DC670_SERVO_ZHU:
							DCServoStop();  //ֹͣ����
							ServoPressStop_flag=0;
							DcServoGoTarget_flag=0;
							BellStart_flag=0;
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//Ŀ��λ��
							AutoPushRun_flag=0; //�Զ���ֽ ����
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
								break;
						case MOTOR_AC_SERVO:
							ACServoStop();
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//Ŀ��λ��
							AutoPushRun_flag=0; //�Զ���ֽ ����
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
								break;
						}
					// TargetSize=0;
					// TargetSize_temp=0;
					// BeforeKnife_offset_in=0;
					if(InputTouch_flag==0)
						ClrInput_function();//���� ����� 
					}				
				}
			}
  	     break;
	case FOUR_KEY_CODE:	//��̰���******************����  ��� ��ģʽ
		if(WorkStart_flag==1)
		   {
		   if(Run_flag==0)
			    {
				if(InputTouch_flag==0)
					{
					switch(WorkMode)
						{
						case PROG_LABEL_MODE: //��ǩ
						case PROG_DIVIDE_MODE: //�ȷ�
						case PROG_PRO_MODE: //����ѡ��
							WorkMode=PROG_MODE;
							CurrentArea_recover2(MIDDLE_PAGE_X, MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							PorgSet_sel=0;
							//------------���ص�һ��
							ClrInput_function();//���� ����� 
							CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
							cursor_row=0;
							CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
							if(Knife_order<=Knife_sum)
								StepOrder_dis(Knife_order);//�������
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							PaperCutEnb_signal=1;
							ACServoAlarmExec_flag=0;
							if(Sign_flag==1)//��� ��,����
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								}
							Program_dis(PROGRAM_X,PROGRAM_Y);   //����3��
								break;
						case AUTO_MODE://�Զ� ��ģʽ��************
						case SELF_CUT_MODE://�Ե���������
						case TEACH_MODE://ʾ�� ģʽ
						case MANUAL_MODE:// �ֶ� ��ģʽ
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								}
							WorkMode=PROG_MODE;
							ProgModePage_dis();// �ص� ���ģʽ
							 
						case PROG_MODE: //��� ��ģʽ
								//------------���ص�һ��
							ClrInput_function();//���� ����� 
							CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
							cursor_row=0;
							CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
							if(Knife_order<=Knife_sum)
								StepOrder_dis(Knife_order);//�������
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							PaperCutEnb_signal=1;
							ACServoAlarmExec_flag=0;
							if(Sign_flag==1)//��� ��,����
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								}
								break;
						}		
					}
				else  //������ ����ģʽ
					{
					
					}
					 
			    }
			else
			    {
				if(AutoCutStart_flag==0)
					{
					switch(MotorType)
						{
						case MOTOR_FREQ_5_SPD_RST:
						case MOTOR_FREQ_3_SPD:
						case MOTOR_FREQ_3_SPD_RST:
							ForceStop_flag=1;
							stop_time=0;
								break;
						case MOTOR_DC_SERVO:
						case MOTOR_DC670_SERVO:
						case MOTOR_DC670_SERVO_ZHU:
							DCServoStop();  //ֹͣ����
							ServoPressStop_flag=0;
							DcServoGoTarget_flag=0;
							BellStart_flag=0;
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//Ŀ��λ��
							AutoPushRun_flag=0; //�Զ���ֽ ����
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
								break;
						case MOTOR_AC_SERVO:
							ACServoStop();
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//Ŀ��λ��
							AutoPushRun_flag=0; //�Զ���ֽ ����
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
								break;
						}
					//TargetSize=0;
					//TargetSize_temp=0;
					//BeforeKnife_offset_in=0;
					if(InputTouch_flag==0)
						ClrInput_function();//���� ����� 		
					}
				}
		   }
		  break;
    case AUTO_KEY_CODE:       // F1**********************
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
			    {
				if(InputTouch_flag==0)
					{
					switch(WorkMode)
						{
						case PROG_MODE://���  ��������
							if(Sign_flag==1)//��� ��,����
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								}
							WorkMode=PROG_LABEL_MODE; //--------�򿪱�ǩ ҳ
							LabelPage_dis();  
							Total_size=0;//�ܳ�
							Label_size=0;//��ǩ��
							Waste_size=0;//�ϱ�
							PorgSet_sel=0;
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case TEACH_MODE://ʾ�� ģʽ
							if(Sign_flag==1)//��� ��,����
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								}
							WorkMode=TEACH_LABEL_MODE; //--------�򿪱�ǩ ҳ
							LabelPage_dis();  
							Total_size=0;//�ܳ�
							Label_size=0;//��ǩ��
							Waste_size=0;//�ϱ�
							PorgSet_sel=0;
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case PROG_LABEL_MODE://�� ��   ��ǩ********************
							WorkMode=PROG_MODE;//------------�˳����ص������ ���� 
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH); 
							Program_dis(PROGRAM_X,PROGRAM_Y);   //���
							PorgSet_sel=0;
							//if(Knife_order<MAIX_Knife-2) //�������3��
							//  {
							if((Total_size*Label_size*Waste_size)!=0)//�趨��Ч
								Label_function();          
							// }
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							//PaperCutEnb_signal=1;
							ACServoAlarmExec_flag=0;
							break;
						case TEACH_LABEL_MODE://�� ��   ��ǩ********************
							WorkMode=TEACH_MODE;//------------�˳����ص�ʾ���� ���� 
							PaperCutEnb_signal=1;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH); 
							Teach_dis(TEACH_X,TEACH_Y);   //ʾ��
							PorgSet_sel=0;
							//if(Knife_order<MAIX_Knife-2) //�������3��
							//  {
							if((Total_size*Label_size*Waste_size)!=0)//�趨��Ч
								Label_function();          
							// }
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case PROG_DIVIDE_MODE: //�� ���� �ȷ�ҳ*******************
							WorkMode=PROG_MODE;//--------------�˳����ص������ ���� 
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							Program_dis(PROGRAM_X,PROGRAM_Y);   //���
							PorgSet_sel=0;
							if((Total_size*Divide_num)!=0)//�趨�ȷ���Ч
							  {
							  Divide_function();//
							  }
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;  
							//PaperCutEnb_signal=1;
							ACServoAlarmExec_flag=0;
							break;
						case TEACH_DIVIDE_MODE: //�� ���� �ȷ�ҳ*******************
							WorkMode=TEACH_MODE;//--------------�˳����ص�ʾ���� ���� 
							PaperCutEnb_signal=1;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							Teach_dis(TEACH_X,TEACH_Y);   //ʾ��
							PorgSet_sel=0;
							if((Total_size*Divide_num)!=0)//�趨�ȷ���Ч
							  {
							  Divide_function();//
							  }
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;  
							ACServoAlarmExec_flag=0;
							break;		
						case PROG_PRO_MODE:	//���� ����ѡ����**************	
							WorkMode=PROG_MODE;//--------------�˳����ص������ ���� 
							if((Pro_num>0)&&(Pro_num<=MAIX_PROG))// ��Ч  ����һ�����򣬲���ʾ 
								{
								 cursor_temp=0;
								 ExportOnePro_dis(Pro_num);  //����һ�� ���� 
								 Program_dis(PROGRAM_X,PROGRAM_Y);   //���
								}
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							//PaperCutEnb_signal=1;
							ACServoAlarmExec_flag=0;
							break;
						case TEACH_PRO_MODE:	//���� ����ѡ����**************	
							WorkMode=TEACH_MODE;//--------------�˳����ص�ʾ���� ���� 
							PaperCutEnb_signal=1;
							if((Pro_num>0)&&(Pro_num<=MAIX_PROG))// ��Ч  ����һ�����򣬲���ʾ 
								{
								 cursor_temp=0;
								 ExportOnePro_dis(Pro_num);  //����һ�� ���� 
								 Teach_dis(TEACH_X,TEACH_Y);   //ʾ��
								}
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;	
							ACServoAlarmExec_flag=0;
							break;		
						case AUTO_MODE://�Զ� ��ģʽ��	
							WorkMode=AUTO_RULER_MODE; //��׼
							RulerPage_dis(); //��׼ ����
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case SELF_CUT_MODE://�Ե���������	
							WorkMode=SELF_RULER_MODE; //��׼
							RulerPage_dis(); //��׼ ����
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case MANUAL_MODE:  // �ֶ�ģʽ
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								}
							WorkMode=MANUAL_TOOLS_MODE;//����  �ֶ�----����ģʽ*****************
							ToolsPage_dis(); //��������
							Para_sel=0;
							PromptDis_flag=0;
							ACServoAlarmExec_flag=0;							
							break;
						case MANUAL_PULSE_MODE://�ֶ� �����趨ģʽ
							Pulse_degree=Para_sel;
							Save_degree();
							WorkMode=MANUAL_MODE;//����    ---------�ֶ� ��ģʽ
							Para_sel=0;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							Manual_dis(MANUAL_X,MANUAL_Y);//�ֶ�
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						}
					}
				else  //������ ����ģʽ
					{
					
					}
				
				}
			else  //������
			    {
				if(AutoCutStart_flag==0)
					{
					switch(MotorType)
						{
						case MOTOR_FREQ_5_SPD_RST:
						case MOTOR_FREQ_3_SPD:
						case MOTOR_FREQ_3_SPD_RST:
							ForceStop_flag=1;
							stop_time=0;
								break;
						case MOTOR_DC_SERVO:
						case MOTOR_DC670_SERVO:
						case MOTOR_DC670_SERVO_ZHU:
							DCServoStop();  //ֹͣ����
							ServoPressStop_flag=0;
							DcServoGoTarget_flag=0;
							BellStart_flag=0;
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//Ŀ��λ��
							AutoPushRun_flag=0; //�Զ���ֽ ����
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
								break;
						case MOTOR_AC_SERVO:
							ACServoStop();
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//Ŀ��λ��
							AutoPushRun_flag=0; //�Զ���ֽ ����
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
								break;
						}
					// TargetSize=0;
					// TargetSize_temp=0;
					// BeforeKnife_offset_in=0;
					}
				}	
			if(InputTouch_flag==0)	
				ClrInput_function();//���� �����  
			}
		else//--------------------------����У׼
			{
			switch(MotorType)
				{
				case MOTOR_FREQ_5_SPD_RST:
				case MOTOR_FREQ_3_SPD:
				case MOTOR_FREQ_3_SPD_RST:
						if((StartCheck_mode<2)||(StartCheck_mode==4))
							CheckModeOK_flag=1;
						else
							CheckModeOK_flag=0;
						break;
				case MOTOR_DC_SERVO:
				case MOTOR_DC670_SERVO:
				case MOTOR_DC670_SERVO_ZHU:
						if(StartCheck_mode<2)
							CheckModeOK_flag=1;
						else
							CheckModeOK_flag=0;
						break;
				case MOTOR_AC_SERVO:
						if(StartCheck_mode<5)
							CheckModeOK_flag=1;
						else
							CheckModeOK_flag=0;
						break;		
				default:
							CheckModeOK_flag=0;
						break;
				}	
			if(CheckModeOK_flag==1)
				{
				if(Board_TestMod==0) //�ǲ��� ģʽ-------
					{
					Board_TestMod=TEST_TOUCH; //����У׼ ģʽʹ��
					GLCD_Buffer_Fill(0xffff);
					x=200,y=150,back_color=WHITE_COLOR;
					switch(Language)
						{
						case CHN_HAN:
							Printf24("�봥����ɫ'ʮ'�ֹ������λ��!",x,y,0,1,back_color);
								break;
						case ENGLISH:	
							Printf24("Please touch the red 'cross'!",x,y,0,1,back_color);
								break;
						}
					TouchCalcu_mode=0;
					Draw_cross(TOUCH_X1,TOUCH_Y1,RED_COLOR);
					}
				else if(Board_TestMod==TEST_TOUCH)
					{
					Bmp_Decode((Int32U)START_PIC_sdram, 0, 0, (pInt16U)SDRAM0_BASE_ADDR); //��ʾ��������
					Board_TestMod=0;
					RunDisplay_flag=0;
					outF_flag=0;
					outM_flag=0;
					outB_flag=0;
					Wheel_flag=0;
					OutFront_limit=0;
					OutMiddle_limit=0;
					OutBack_limit=0;
					Wheel_limit=0;
					OriginalError_flag=0;
					BackLimitError_flag=0;StartCheck_mode=0;
					ServoDisconnect_flag=0;
					}
				}
			}
  	     break;
    case READ_KEY_CODE:       // F2*******************�˳�
		if(WorkStart_flag==1)
		   {
			if(Run_flag==0)
			    {
				if(InputTouch_flag==0)
					{
					switch(WorkMode)
						{
						case PROG_MODE://��̻�����
							if(Sign_flag==1)//��� ��,����
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								}
							WorkMode=PROG_DIVIDE_MODE;//����---------�ȷ�ģʽ  
							DividePage_dis();  
							Total_size=0;//�ܳ�
							Divide_num=0;//�ȷ���
							PorgSet_sel=0;
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case TEACH_MODE://ʾ�̻�����
							if(Sign_flag==1)//��� ��,����
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								}
							WorkMode=TEACH_DIVIDE_MODE;//����---------�ȷ�ģʽ  
							DividePage_dis();  
							Total_size=0;//�ܳ�
							Divide_num=0;//�ȷ���
							PorgSet_sel=0;
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;		
						case PROG_LABEL_MODE://���� ��ǩ����		
						case PROG_DIVIDE_MODE://���� �ȷֻ��� 		
						case PROG_PRO_MODE://����  ����ѡ����
							cursor_temp=0;		
							WorkMode=PROG_MODE;//------------------�˳����ص������ ����
							PorgSet_sel=0;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							Program_dis(PROGRAM_X,PROGRAM_Y);   //���
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							//PaperCutEnb_signal=1;
							ACServoAlarmExec_flag=0;
							break;
						case TEACH_LABEL_MODE://���� ��ǩ����		
						case TEACH_DIVIDE_MODE://���� �ȷֻ��� 		
						case TEACH_PRO_MODE://����  ����ѡ����
							cursor_temp=0;		
							WorkMode=TEACH_MODE;//------------------�˳����ص�ʾ���� ����
							PaperCutEnb_signal=1;
							PorgSet_sel=0;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							Teach_dis(TEACH_X,TEACH_Y);   //ʾ��
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;		
						//*********************************************	
						case AUTO_MODE://�Զ� ��ģʽ��		
							WorkMode=AUTO_TOOLS_MODE;//����  �Զ� ----����ģʽ*****************
							ToolsPage_dis(); //��������
							Para_sel=0;
							PromptDis_flag=0;
							ACServoAlarmExec_flag=0;
							break;
						case AUTO_RULER_MODE:	//��׼ģʽ		
						case AUTO_TOOLS_MODE:// ����  �Զ� -------����ģʽ
							WorkMode=AUTO_MODE;//����    ---------�Զ� ��ģʽ
							Para_sel=0;
							PaperCutEnb_signal=1;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							Auto_dis(AUTO_X, AUTO_Y); //�Զ�
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case AUTO_PLUS_MODE:// F3++
							WorkMode=AUTO_MODE;//����
							PaperCutEnb_signal=1;
							F3_plus_dis(0);
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case AUTO_MINUS_MODE:// F4--
							WorkMode=AUTO_MODE;//����
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F4_minus_dis(0);
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						//****************�Ե�
						case SELF_CUT_MODE://�Ե� ��ģʽ��		
							WorkMode=SELF_TOOLS_MODE;//���� �Ե�  ----����ģʽ*****************
							ToolsPage_dis(); //��������
							Para_sel=0;
							PromptDis_flag=0;
							ACServoAlarmExec_flag=0;
							break;
						case SELF_RULER_MODE:	//��׼ģʽ		
						case SELF_TOOLS_MODE:// ���� �Ե�  -------����ģʽ
							WorkMode=SELF_CUT_MODE;//����    ---------�Ե� ��ģʽ
							Para_sel=0;
							PaperCutEnb_signal=1;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							AutoKnife_dis(SELF_KNIFE_X, SELF_KNIFE_Y); //�Ե�
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case SELF_PLUS_MODE:// F3++
							WorkMode=SELF_CUT_MODE;//����
							PaperCutEnb_signal=1;
							F3_plus_dis(0);
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case SELF_MINUS_MODE:// F4--
							WorkMode=SELF_CUT_MODE;//����
							PaperCutEnb_signal=1;
							F4_minus_dis(0);
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;	
						//*******************************
						case MANUAL_MODE: //�ֶ�
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								}
							WorkMode=MANUAL_RULER_MODE; //��׼
							RulerPage_dis(); //��׼ ����
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case MANUAL_TOOLS_MODE:// �ֶ� ����ģʽ
						case MANUAL_RULER_MODE://�ֶ� ��׼ģʽ
						case MANUAL_CLOCK_MODE://�ֶ� ʱ��ģʽ
						case MANUAL_PULSE_MODE://�ֶ� �����趨ģʽ
						case MANUAL_PASS_MODE://�ֶ� ����ģʽ
						case MANUAL_SERVO_C_MODE:   //�ֶ�ֱ���ŷ� C ���� 
							WorkMode=MANUAL_MODE;//����    ---------�ֶ� ��ģʽ
							Para_sel=0;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							Manual_dis(MANUAL_X,MANUAL_Y);//�ֶ�
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						}
					}
				else  //������ ����ģʽ
					{
					CalcuInClear_exec();     //��� ������
					switch(WorkMode)
						{
						case AUTO_TOOLS_MODE:
						case MANUAL_TOOLS_MODE:
						case SELF_TOOLS_MODE:
							back_color=0xef9f;
							x=PARA_START_X1+PARA_COL_WIDE,y=PARA_START_Y,gap=30;
							if(PramSel_Page<1)	//page 1
								{
							//if(Para_sel<7)
							//	{
								ParameterPage_dis(7, 0);
								if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
									{
									ParameterPage_dis(8, 0);
									ParameterPage_dis(9, 0);
									}
								else if(MotorType==MOTOR_AC_SERVO)	
									{
									ParameterPage_dis(8, 0);
									}
								ParameterPage_dis(Para_sel, 1);
							//	}
							switch(Language)
								{
								case CHN_HAN:
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
								}
							else	//page 2
								{
									
								}
							break;
						
						case  PROG_MODE://��̻�����
						case AUTO_MODE://�Զ���������
						case AUTO_PLUS_MODE://�Զ�F3++
						case AUTO_MINUS_MODE://�Զ�F4--
						case TEACH_MODE://ʾ�� ģʽ
						case AUTO_TO_SELF_MODE:   //�Զ�-->�Ե����� ģʽ
						case SELF_CUT_MODE:  //�Ե��� ģʽ
						case SELF_PLUS_MODE: //�Ե� F3++
						case SELF_MINUS_MODE://�Ե� F4--
							if(Knife_order>Knife_sum)
								 K_temp=Knife_order-1;
							 else
								 K_temp=Knife_order;
							ProgressBar_dis(Knife_sum,K_temp);  //������ ��ʾ
							KnifeUp_flag=0;
							KnifeDown_flag=0;
							PressUp_flag=0;
							PressDown_flag=0;
							A_Down_flag=0;
							B_Down_flag=0;
							A_Up_flag=0;
							B_Up_flag=0;
							IR_Up_flag=0;
							IR_Down_flag=0;
							//--------------������ʾ��������ֽ��־
							// CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
							// cursor_row=0;
							// CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
							//Knife_order=1;//
							Size_1page_dis(Knife_order-cursor_row,0);//һҳ�ߴ���ʾ
							break;	
						}
					}
				}
			else  //������
			    {
				if(InputTouch_flag==0)
					{
					if(AutoCutStart_flag==0)
						{
						switch(MotorType)
							{
							case MOTOR_FREQ_5_SPD_RST:
							case MOTOR_FREQ_3_SPD:
							case MOTOR_FREQ_3_SPD_RST:
								ForceStop_flag=1;
								stop_time=0;
									break;
							case MOTOR_DC_SERVO:
							case MOTOR_DC670_SERVO:
							case MOTOR_DC670_SERVO_ZHU:
								DCServoStop();  //ֹͣ����
								ServoPressStop_flag=0;
								DcServoGoTarget_flag=0;
								BellStart_flag=0;
								//************
								Run_flag=0;	
								InTargetPosit_flag=0;	//Ŀ��λ��
								AutoPushRun_flag=0; //�Զ���ֽ ����
								TargetSize=0;
								TargetSize_temp=0;
								BeforeKnife_offset_in=0;
								AutoRoute_flag=0;
									break;
							case MOTOR_AC_SERVO:
								ACServoStop();
								//************
								Run_flag=0;	
								InTargetPosit_flag=0;	//Ŀ��λ��
								AutoPushRun_flag=0; //�Զ���ֽ ����
								TargetSize=0;
								TargetSize_temp=0;
								BeforeKnife_offset_in=0;
								AutoRoute_flag=0;
									break;
							}	
						// TargetSize=0;
						// TargetSize_temp=0;
						// BeforeKnife_offset_in=0;
						}
					}
				else
					CalcuInClear_exec();     //��� ������
				}		
			ClrInput_function();//���� �����
		   }
		else  
		   {
		   switch(MotorType)
				{
					case MOTOR_FREQ_5_SPD_RST:
					case MOTOR_FREQ_3_SPD:
					case MOTOR_FREQ_3_SPD_RST:
						if((StartCheck_mode<2)||(StartCheck_mode==4))
							CheckModeOK_flag=1;	
						else
							CheckModeOK_flag=0;
						break;
					case MOTOR_DC_SERVO:
					case MOTOR_DC670_SERVO:
					case MOTOR_DC670_SERVO_ZHU:
						if(StartCheck_mode<2)
							CheckModeOK_flag=1;	
						else
							CheckModeOK_flag=0;
						break;
					case MOTOR_AC_SERVO:
						if(StartCheck_mode<5)
							CheckModeOK_flag=1;	
						else
							CheckModeOK_flag=0;
						break;	
					default:
							CheckModeOK_flag=0;
						break;
				}	
			if(CheckModeOK_flag==1)
				{
				if(Board_TestMod==0)       //-------------����ģʽ---
					{
					Manual_page=0;
					Comment_dis_page(Manual_page);//ע��1
					Board_TestMod=TEST_HELP;
					}
				else if(Board_TestMod==TEST_HELP)
					{
					Bmp_Decode((Int32U)START_PIC_sdram, 0, 0, (pInt16U)SDRAM0_BASE_ADDR); //��ʾ��������
					RunDisplay_flag=0;
					outF_flag=0;
					outM_flag=0;
					outB_flag=0;
					Wheel_flag=0;
					OutFront_limit=0;
					OutMiddle_limit=0;
					OutBack_limit=0;
					Wheel_limit=0;
					OriginalError_flag=0;
					BackLimitError_flag=0;StartCheck_mode=0;
					
					Board_TestMod=0;Manual_page=0;
					ServoDisconnect_flag=0;
					}
				}
		   }
  	     break;
    case RETURN_KEY_CODE:      //F3************ѡ�� �����
		if(WorkStart_flag==1)
		   {
			if(Run_flag==0)
			    {
				if(InputTouch_flag==0)
					{
					switch(WorkMode)
						{
						case PROG_MODE:
							if(Sign_flag==1)//��� ��,����
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								}
							WorkMode=PROG_PRO_MODE;//���� -----------ѡ�����ģʽ
							SelProgPage_dis(); //���� ѡ�� ������ʾ
							PromptDis_flag=0;
							Pro_num=1;
							cursor_temp=0;
							Prog_1page_dis(Pro_num, 0);//===����---������ʾ
							TableDis_startcol=RIGHT_ARROW_X;
							CursorMov_dis(cursor_temp,1);//��ɫ���
							//ClrInput_function();//���� �����
							ACServoAlarmExec_flag=0;
							break;
						case TEACH_MODE:
							if(Sign_flag==1)//��� ��,����
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								}
							WorkMode=TEACH_PRO_MODE;//���� -----------ѡ�����ģʽ
							SelProgPage_dis(); //���� ѡ�� ������ʾ
							PromptDis_flag=0;
							Pro_num=1;
							cursor_temp=0;
							Prog_1page_dis(Pro_num, 0);//===����---������ʾ
							TableDis_startcol=RIGHT_ARROW_X;
							CursorMov_dis(cursor_temp,1);//��ɫ���
							//ClrInput_function();//���� �����
							ACServoAlarmExec_flag=0;
							break;		
						case AUTO_MODE://�Զ� ��ģʽ��************
							//ClrInput_function();//���� �����
							WorkMode=AUTO_PLUS_MODE;  //F3++
							F3_plus_dis(1);//  ++
							break;
						case AUTO_PLUS_MODE:  //F3++		
							WorkMode=AUTO_MODE;//����
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F3_plus_dis(0);
							break;
						case SELF_CUT_MODE://�Ե� ��ģʽ��************
							WorkMode=SELF_PLUS_MODE;  //F3++
							F3_plus_dis(1);//  ++
							break;
						case SELF_PLUS_MODE:  //F3++		
							WorkMode=SELF_CUT_MODE;//����
							PaperCutEnb_signal=1;
							F3_plus_dis(0);
							break;		
						case MANUAL_MODE: //�ֶ�-----------------------
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								}
							WorkMode=MANUAL_CLOCK_MODE; // ʱ�� ģʽ
							Para_sel=0;PromptDis_flag=0;
							ClockPage_dis();
							Year_before=Year,Month_before=Month,Day_before=Dom; //��ǰʱ�� �ݴ�
							ACServoAlarmExec_flag=0;
							break;
						}
					}
				else  //������ ����ģʽ
					{
					
					}
						
			    }
			else  //������
			    {
				if(AutoCutStart_flag==0)
					{
					switch(MotorType)
						{
						case MOTOR_FREQ_5_SPD_RST:
						case MOTOR_FREQ_3_SPD:
						case MOTOR_FREQ_3_SPD_RST:
							ForceStop_flag=1;
							stop_time=0;
								break;
						case MOTOR_DC_SERVO:
						case MOTOR_DC670_SERVO:
						case MOTOR_DC670_SERVO_ZHU:
							DCServoStop();  //ֹͣ����
							ServoPressStop_flag=0;
							DcServoGoTarget_flag=0;
							BellStart_flag=0;
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//Ŀ��λ��
							AutoPushRun_flag=0; //�Զ���ֽ ����
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
								break;
						case MOTOR_AC_SERVO:
								ACServoStop();
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//Ŀ��λ��
							AutoPushRun_flag=0; //�Զ���ֽ ����
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
									break;
						}
					// TargetSize=0;
					// TargetSize_temp=0;
					// BeforeKnife_offset_in=0;
					}
				}
			if(InputTouch_flag==0)
				ClrInput_function();//���� �����
		   }
  	     break;    
	case MANUAL_KEY_CODE:   // F4************** ��ֽ/��  ��־
		if(WorkStart_flag==1)
		   {
		    if(Run_flag==0)
			    {
				if(InputTouch_flag==0)
					{
					switch(WorkMode)
						{
						case PROG_MODE://��� ��������
						case TEACH_MODE://ʾ�� ��������
							if(Sign_flag==1)//��� ��,����
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								}
								
							if(num_cou>0)
								{
								if(CheckInputNums()==1)// ���� ��Ч
									{
									//----��������----------------
									if(Knife_order>Knife_sum)//���²��� �ܵ���
										{
										Knife_sum=Knife_order;
										}
									pKnife_data=(pInt8U)&OneKnife_data;
									GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);//
									OneKnife_data.size=InputSize;  //�ߴ��޸�
									if(OneKnife_data.k_flag!=PUSH_FLAG) //
										{
										OneKnife_data.k_flag=PUSH_FLAG;//  �趨 ��־
										}
									else
										{
										OneKnife_data.k_flag=0;// ��� ��־
										}
									SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//����һ������
									//-----��ʾ
									PushFlag_dis(cursor_row,OneKnife_data.k_flag); //��ʾ----
									KnifeSize_dis(cursor_row,InputSize,0);//�ߴ�
									StepNum_dis(Knife_sum,Knife_order);//�������
									if(Knife_order<MAIX_Knife)            //�������
										{
										Knife_order++;
										if(cursor_row<(PAGE_KNIFE-1))
											{
											CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
											OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //һ������ ������ʾ
											cursor_row++;
											CursorMov_dis(cursor_row, 1);//��ɫ���������ʾ
											OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //һ������ ������ʾ
											}
										else   //ҳ��
											{
											Size_1page_dis(Knife_order-(PAGE_KNIFE-1),0);//һҳ�ߴ���ʾ
											}	
										}
									else
										{
										OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //һ������ ������ʾ
										}
									}
								ClrInput_function();//���� �����
								}
							else  //�� ��������
								{
								pKnife_data=(pInt8U)&OneKnife_data;
								GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);//
								if(OneKnife_data.size>0)
									{
									if(OneKnife_data.k_flag!=PUSH_FLAG) //
										{
										OneKnife_data.k_flag=PUSH_FLAG;//  �趨 ��־
										}
									else
										{
										OneKnife_data.k_flag=0;// ��� ��־
										}
									PushFlag_dis(cursor_row,OneKnife_data.k_flag); //��ʾ----
									SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//����һ������
									PromptNum_dis();//���뷶Χ
									PromptDis_flag=1;
									}
								else
									{
						//GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+360, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
						//Printf24("������ֵ��Χ    ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									}
								}	
							break;
						case AUTO_MODE://�Զ� ��ģʽ��************
							ClrInput_function();//���� �����
							WorkMode=AUTO_MINUS_MODE;// F4--
							F4_minus_dis(1);//--
							break;
						case AUTO_MINUS_MODE:// F4--		 
							WorkMode=AUTO_MODE;//����
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F4_minus_dis(0);
							ClrInput_function();//���� �����
							break;
						case SELF_CUT_MODE://�Ե� ��ģʽ��************
							ClrInput_function();//���� �����
							WorkMode=SELF_MINUS_MODE;// F4--
							F4_minus_dis(1);//--
							break;
						case SELF_MINUS_MODE:// F4--		 
							WorkMode=SELF_CUT_MODE;//����
							PaperCutEnb_signal=1;
							F4_minus_dis(0);
							ClrInput_function();//���� �����
							break;
						case MANUAL_MODE: //�������� ����
							if(MotorType==MOTOR_AC_SERVO)
								{
								ElectricWheelOn_flag=!ElectricWheelOn_flag;
								SaveElectricWheelSwitch();//��������
								ElectricalWheel_dis();  //��������  ����״̬
								}
							
							break;
						}		

					}
				else  //������ ����ģʽ
					{
					
					}
			    }
			else  //������
			    {
				if(AutoCutStart_flag==0)
					{
					switch(MotorType)
						{
						case MOTOR_FREQ_5_SPD_RST:
						case MOTOR_FREQ_3_SPD:
						case MOTOR_FREQ_3_SPD_RST:
							ForceStop_flag=1;
							stop_time=0;
								break;
						case MOTOR_DC_SERVO:
						case MOTOR_DC670_SERVO:
						case MOTOR_DC670_SERVO_ZHU:
							DCServoStop();  //ֹͣ����
							ServoPressStop_flag=0;
							DcServoGoTarget_flag=0;
							BellStart_flag=0;
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//Ŀ��λ��
							AutoPushRun_flag=0; //�Զ���ֽ ����
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
								break;
						case MOTOR_AC_SERVO:
								ACServoStop();
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//Ŀ��λ��
							AutoPushRun_flag=0; //�Զ���ֽ ����
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
									break;
						}
					// TargetSize=0;
					// TargetSize_temp=0;
					//BeforeKnife_offset_in=0;
					if(InputTouch_flag==0)
						ClrInput_function();//���� �����	
					}		
				}
		   }
  	     break;  
    case PROG_KEY_CODE:     // 0  **************
			NumKey_exec(0);
			break;
    case NINE_KEY_CODE:		// 1**************
			NumKey_exec(1);
			break;
	case MOVE_KEY_CODE:     // 2**************
			NumKey_exec(2);
			break;
	case DELETE_KEY_CODE:      //3*************
			NumKey_exec(3);
			break;
	case EIGHT_KEY_CODE:		//4***********
			NumKey_exec(4);
			break;
	case NO_KEY_CODE:      // 5******************
			NumKey_exec(5);
			break;   
	case INSERT_KEY_CODE:      //6****************
			NumKey_exec(6);
			break;
	case SEVEN_KEY_CODE:	//7 **************
			NumKey_exec(7);
			break;         
    case YES_KEY_CODE:    // 8*************          
			NumKey_exec(8);
			break;
	case SUB_KEY_CODE:   // 9************
			NumKey_exec(9);
			break;
    case ADD_KEY_CODE:   //  �㡰.��***************
			NumKey_exec('.');
			 break;   
	case SIX_KEY_CODE:		// clear ����C********
        if(WorkStart_flag==1)
				{
				if(Run_flag==0)
					{
					Dot_flag=0;
					if(num_cou>0)
						ClrInput_function();//���� �����
					if(InputTouch_flag==0)
						{
						if(WorkMode==AUTO_TO_SELF_MODE)  //�Զ�-->�Ե����� ģʽ
							{
							if(ReEnterAutoKnife_dis==0) //������ ��ʾ  ��ʾ
								{
								WorkMode=AUTO_MODE;//���� �Զ���
								PaperCutEnb_signal=1;
								PressCircle_mode=0;
								CurrentArea_recover2(SELF_PROMP_X,SELF_PROMP_Y,SELF_PROMP_X+300,SELF_PROMP_Y+120);
								}
							else   //�ٴ�  ���� ��һ��
								{
								if(InputTouch_flag==1)  //	  ���� ��
									CalcuInClear_exec();     //��� ������
								WorkMode=SELF_CUT_MODE;  //����   ----------�Ե��� ģʽ
								CurrentArea_recover2(SELF_PROMP_X,SELF_PROMP_Y,SELF_PROMP_X+300,SELF_PROMP_Y+120);
								AutoKnife_dis(SELF_KNIFE_X,SELF_KNIFE_Y);//�Ե�
								//------------���ص�һ��
								ClrInput_function();//���� ����� 
								CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
								cursor_row=0;
								CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
								Knife_order=1;//
								Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
								if(Knife_order<=Knife_sum)
									StepOrder_dis(Knife_order);//������� 
									
								LastAutoKnife_order=1;
								ReEnterAutoKnife_dis=0;
								}
							}
						}
					else
						{
						if(CalcNoNumInput_flag==0)//  �������Ѿ����� ����
							{
							ClearCalculatorInput(); //��������� ����
							}
						}
					}
				else
					{
									
					}
				} 
		else
				{
				switch(MotorType)
					{
					case MOTOR_FREQ_5_SPD_RST:
					case MOTOR_FREQ_3_SPD:
					case MOTOR_FREQ_3_SPD_RST:
					case MOTOR_AC_SERVO:
		//			case MOTOR_AC_SERVO670:
						if(StartCheck_mode==1)  //��ֽ�� ��λ����
							{
							CurrentArea_recover3(PUSH_RESET_PROMPT_X1, PUSH_RESET_PROMPT_Y1, PUSH_RESET_PROMPT_WIDE, PUSH_RESET_PROMPT_HIGH);
							StartCheck_mode=3;//2;
							PusherResetTime=0;
							}
						else if(StartCheck_mode==4)
							{
							 if(PassCheckDis_flag==1)//����
								{
								GLCD_SetWindow_Fill(PASSCODE_INPUT_X, PASSCODE_INPUT_Y, PASSCODE_INPUT_X+100, PASSCODE_INPUT_Y+30, 0xfffff, 0xffff);
								for(num_cou=0;num_cou<8;num_cou++)
									{
									Size_temp[num_cou++]=0;
									}
								num_cou=0;
								}
							}
							break;
					case MOTOR_DC_SERVO:
							break;
					}	
				}
  	     break;   
	case NEXTKNIFE_KEY_CODE:   //ǰ������***************
        if(WorkStart_flag==1)  
			{
			if(Run_flag==0)
				{
				switch(WorkMode)
					{
					case PROG_MODE://��̻�����
					case TEACH_MODE://ʾ�̻�����
					case AUTO_MODE://�Զ���������
					case SELF_CUT_MODE://�Ե���������
					case MANUAL_MODE:   //�ֶ�
						if(Sign_flag==1)
							{
							num_cou=0;
							GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
							Sign_flag=0;
							}
                                                qianjinflag=1;
						GoFrontEn_flag=1;
						GoFast_flag=0;
						SelfLockEn_flag=0; //ȡ������
						InTargetPosit_flag=0;	//Ŀ��λ��
						JogRunMode=0;
						ForceStop_flag=0;
						TargetSize=0;
						DcServoGoTarget_flag=0;
						//ClrInput_function();//���� �����
							break;
					}
				}
			}
		else
			{
			switch(MotorType)
				{
				case MOTOR_FREQ_5_SPD_RST:
				case MOTOR_FREQ_3_SPD:
				case MOTOR_FREQ_3_SPD_RST:
					if((StartCheck_mode<2)||(StartCheck_mode==3)||(StartCheck_mode==4))
						{
						GoFrontEn_flag=1;
						GoFast_flag=0;
						ManualMoveMode=0;
						}
						break;
				case MOTOR_DC_SERVO:
						break;
				case MOTOR_AC_SERVO:
//				case MOTOR_AC_SERVO670:
					if(StartCheck_mode<=2)
						{
						GoFrontEn_flag=1;
						GoFast_flag=0;
						ManualMoveMode=0;
						}
						break;
				}		
			}
  	     break;
	case FAST_FWD_TOUCH_CODE:	//���
		if(WorkStart_flag==1)  
			{
			if(Run_flag==0)
				{
				switch(WorkMode)
					{
					// case PROG_MODE://��̻�����
					// case TEACH_MODE://ʾ�̻�����
					// case AUTO_MODE://�Զ���������
					// case SELF_CUT_MODE://�Ե���������
					case MANUAL_MODE:   //�ֶ�
						if((MotorType<MOTOR_DC_SERVO)||(MotorType>=MOTOR_AC_SERVO))
							{
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								}
													qianjinflag=1;
							GoFrontEn_flag=1;
							GoFast_flag=1;
							SelfLockEn_flag=0; //ȡ������
							InTargetPosit_flag=0;	//Ŀ��λ��
							JogRunMode=0;
							ForceStop_flag=0;
							TargetSize=0;
							DcServoGoTarget_flag=0;
							}
						//ClrInput_function();//���� �����
							break;
					}
				}
			}
			break;
	case ADJUST_KEY_CODE:     //���˰���**************
        if(WorkStart_flag==1)  
			{
			if(Run_flag==0)
				{
				switch(WorkMode)
					{
					case PROG_MODE://��̻�����
					case TEACH_MODE://ʾ�̻�����
					case AUTO_MODE://�Զ���������
					case SELF_CUT_MODE://�Ե���������
					case MANUAL_MODE:   //�ֶ�
						if(Sign_flag==1)
							{
							num_cou=0;
							GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
							Sign_flag=0;
							}
                                                houtuiflag=1;
						GoBackEn_flag=1;
						GoFast_flag=0;
						SelfLockEn_flag=0; //ȡ������
						ToTargetStop_flag=0;
						InTargetPosit_flag=0;	//Ŀ��λ��
						JogRunMode=0;
						ForceStop_flag=0;
						TargetSize=0;
						DcServoGoTarget_flag=0;
						//ClrInput_function();//���� �����
							break;
					}
				}
			} 
		else
			{
			switch(MotorType)
				{
				case MOTOR_FREQ_5_SPD_RST:
				case MOTOR_FREQ_3_SPD:
				case MOTOR_FREQ_3_SPD_RST:
					if((StartCheck_mode<2)||(StartCheck_mode==3)||(StartCheck_mode==4))
						{
						GoBackEn_flag=1;
						GoFast_flag=0;
						ManualMoveMode=0;
						}
						break;
				case MOTOR_DC_SERVO:
						break;
				case MOTOR_AC_SERVO:
	//			case MOTOR_AC_SERVO670:
					if(StartCheck_mode<=2)
						{
						GoBackEn_flag=1;
						GoFast_flag=0;
						ManualMoveMode=0;
						}	
						break;
				}	
			}
  	     break;
	case FAST_BACK_TOUCH_CODE:	//����
		if(WorkStart_flag==1)  
			{
			if(Run_flag==0)
				{
				switch(WorkMode)
					{
					// case PROG_MODE://��̻�����
					// case TEACH_MODE://ʾ�̻�����
					// case AUTO_MODE://�Զ���������
					// case SELF_CUT_MODE://�Ե���������
					case MANUAL_MODE:   //�ֶ�
						if((MotorType<MOTOR_DC_SERVO)||(MotorType>=MOTOR_AC_SERVO))
							{
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								}
													houtuiflag=1;
							GoBackEn_flag=1;
							GoFast_flag=1;
							SelfLockEn_flag=0; //ȡ������
							ToTargetStop_flag=0;
							InTargetPosit_flag=0;	//Ŀ��λ��
							JogRunMode=0;
							ForceStop_flag=0;
							TargetSize=0;
							DcServoGoTarget_flag=0;
							}
						//ClrInput_function();//���� �����
							break;
					}
				}
			}
  	     break;
    case REV_KEY_CODE:   //  ��+/*��  ***************
        if(WorkStart_flag==1)  
			{
			if(Run_flag==0)
			    {
				if(InputTouch_flag==0)
					{
					switch(WorkMode)
						{
						case MANUAL_MODE:   //�ֶ�
						case PROG_MODE:	//���ģʽ
							if(Sign_flag==0)         //�� ��
								{
								ClrInput_function();//���� �����
								Printf24(" +",SIZE_WINDOW_X,SIZE_WINDOW_Y,RED_COLOR,1,0xffff);
								Sign_flag=1;
								Minus_flag=0;
								Arithmetic_mode=PLUS_SIGN;//  "+"
								} 
							else               //��� �Ӻ�
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								Arithmetic_mode=NO_SIGN;//---0
								}
								break;
						case TEACH_MODE:   //ʾ��ģʽ
							ShowTouchWind();//��������window
							CalculatorValue_exec('+');
								break;
						}
					}
				else    //������ ����ģʽ
					{
					CalculatorValue_exec('+');	
					}
				
				}	
            } 
         break;        
    case OPTION_KEY_CODE:    //����  ��-/����  *************
       if(WorkStart_flag==1)  
			{
			if(Run_flag==0)
			    {
				if(InputTouch_flag==0)
					{
					switch(WorkMode)
						{
						case MANUAL_MODE:   //�ֶ�
						case PROG_MODE:	//���ģʽ
							if(Sign_flag==0)         //"-" ��
								{
								ClrInput_function();//���� �����
								Printf24(" -",SIZE_WINDOW_X,SIZE_WINDOW_Y,RED_COLOR,1,0xffff);
								Sign_flag=1;
								Minus_flag=1;
								Arithmetic_mode=MINUS_SIGN;//  "-"
								} 
							else               //��� "-"
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								Arithmetic_mode=NO_SIGN;//---0
								}
								break;
						case TEACH_MODE:   //ʾ��ģʽ
							ShowTouchWind();//��������window
							CalculatorValue_exec('-');
								break;
						}
					}	
				else    //������ ����ģʽ
					{
					CalculatorValue_exec('-');	
					}		
				}	
            }       
  	     break;
    case ZERO_KEY_CODE:	//C���빦��************
		if(WorkStart_flag==1)
		  {
		   if(Run_flag==0)
			 {
			 switch(WorkMode)
				{
				case PROG_MODE://��̻�����
				case TEACH_MODE://ʾ�̻�����
				case AUTO_MODE://�Զ���������
				case SELF_CUT_MODE://�Ե���������
					if(num_cou>0)
						{
						if(CheckInputNums()==1)// ���� ��Ч
							{
							if(Knife_order<=Knife_sum)
								{
								if(Knife_sum<MAIX_Knife)
									{
									Knife_sum++;
									InsertOneKnife(Pro_data.pro_num, Knife_order);
									pKnife_data=(pInt8U)&OneKnife_data;
									// GetOneKnife_datas(Knife_order, pKnife_data);//
									OneKnife_data.size=InputSize;  //�ߴ��޸�
									OneKnife_data.k_flag=NO_FLAG;  //��� ��־
									SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//����һ������
										//------------------//��һ�� ����� ���
									if((Knife_order+1)<=Knife_sum)
										{
										GetOneKnife_datas(Pro_data.pro_num, Knife_order+1, pKnife_data);//��һ��
										if(OneKnife_data.k_flag==KNIFE_FLAG) //�� ��־
											{
											if(OneKnife_data.size>InputSize)
												{
												OneKnife_data.k_flag=0;	//����� ���
												SaveOneKnife_datas(Pro_data.pro_num, Knife_order+1 , pKnife_data);//����һ������
												}
											}
										}
									//-----��ʾ
									//KnifeSize_dis(cursor_row,InputSize);//�ߴ�
									StepNum_dis(Knife_sum,Knife_order);//�������
									Size_1page_dis(Knife_order,cursor_row);
									}
								else  //�����������������ɲ���
									{
									PromptDis_flag=0;
									GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
									switch(Language)
										{
										case CHN_HAN:
											Printf24("����������,���ɲ���!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
										case ENGLISH:
											Printf24("Data full,no inserting!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
										}
									}
								}
							else
								{
								PromptDis_flag=0;
								GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
								switch(Language)
									{
									case CHN_HAN:
										Printf24("������밴ȷ����!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
									case ENGLISH:
										Printf24("Press ENTER,please!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
									}
								}
							}
						if(InputTouch_flag==0)  //	 �� ���������� ��
							ClrInput_function();//���� �����
						} 		
							break;
				case AUTO_TOOLS_MODE://  ��������
				case SELF_TOOLS_MODE://  ��������
				case MANUAL_TOOLS_MODE:// �ֶ� ����ģʽ
					if(PramSel_Page<1)	//page 1
						{
						switch(Para_sel)
							{
							case 3://����
								Language++;
								if(Language>1)
									Language=0;
								//***********�������Ը���
								switch(Language)
									{
									case CHN_HAN:
										x=PARA_START_X1,y=PARA_START_Y,gap=30;back_color=0xef9f;
										Printf24("ǰ����:     ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("�м���:    ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("����:    ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("����:    ",x,y,BLACK_COLOR,1,back_color);  y+=gap;
										Printf24("��λ:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
										Printf24("��ǰ��:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										//Printf24("��׼����:   ",x,y,BLACK_COLOR,1,back_color);
										Printf24("��ֽ����:   ",x,y,BLACK_COLOR,1,back_color);
										if(InputTouch_flag==0)  //	 �� ���������� ��
											{
											x+=PARA_COL_WIDE;y=PARA_START_Y;
											Printf24("ѹֽͣ��:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
											ParameterPage_dis(7, 0);
											if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
												{
												Printf24("����ٶ�:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
												Printf24("�㶯�ٶ�:   ",x,y,BLACK_COLOR,1,back_color);
												}
											else if(MotorType==MOTOR_AC_SERVO)
												{
												Printf24("�����ٶ�:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
												}
											else
												{
												Printf24("��Χ:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
												}
											}
										x=PROG_X,y=PROG_Y;back_color=0xce79;
										Printf24(" ����  ",x,y,BLACK_COLOR,1,back_color);
										x=STEP_X;//
										Printf24("����",x,y,BLACK_COLOR,1,back_color);//
										break;
									case ENGLISH:	
										x=PARA_START_X1,y=PARA_START_Y,gap=30;back_color=0xef9f;
										Printf24("Front-limit:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Midd-limit:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Back-limit:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Language:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
										Printf24("Unit:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
										Printf24("Advanced:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Push-distan:",x,y,BLACK_COLOR,1,back_color);
										if(InputTouch_flag==0)  //	 �� ���������� ��
											{
											x+=PARA_COL_WIDE;y=PARA_START_Y;
											Printf24("Press-Stop:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											ParameterPage_dis(7, 0);
											if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
												{
												Printf24("Max-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
												Printf24("Jog-speed:",x,y,BLACK_COLOR,1,back_color);
												}
											else if(MotorType==MOTOR_AC_SERVO)
												{
												Printf24("Run-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
												}
											else
												{
												Printf24("err range:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
												}
											}
										x=PROG_X,y=PROG_Y;back_color=0xce79;
										Printf24("Process",x,y,BLACK_COLOR,1,back_color);
										x=STEP_X;//
										Printf24("Step",x,y,BLACK_COLOR,1,back_color);
										break;
									}
								ParameterPage_dis(Para_sel, 1);
								if(InputTouch_flag==1)  //	  ���������� ��
									{
									Button_dis(BUTT_INSERT, 1); //���� ��ť ��ʾ
									Button_dis(BUTT_EXIT, 0); //���� ��ť ��ʾ
									Button_dis(BUTT_ENTER, 0); //���� ��ť ��ʾ
									}
								SaveLanguage();
								break;
							case 4: //��λ
								Unit++;
								if(Unit>1)//mm
									{
									Unit=0;
									Size_MIN_num=Size_MIN;
									Size_MAX_num=Size_MAX;	
									if(InTargetPosit_flag==1)  //Ŀ��λ��
										{
										TargetSize=CurrentSize_temp;
										}
									}
								else
									{
									Size_MIN_num=Size_MIN*100/254;
									Size_MAX_num=Size_MAX*100/254;	
									if(InTargetPosit_flag==1)  //	Ŀ��λ��
										{
										TargetSize_inch=CurrentSize*100/254;
										}
									}
								CurrentSize_dis(CurrentSize); //��ǰ�ߴ� ������ʾ
								CurrUint_dis(Unit);  //��ǰ�ߴ� ��λ
								FrontKnifeUint_dis(Unit);  //��ǰ�ߴ� ��λ
								if(BeforeKnifeNo_flag==0)
									FrontKnifeSize_dis(BeforeKnifeSize);
								ParameterPage_dis(0, 0);
								ParameterPage_dis(1, 0);
								ParameterPage_dis(2, 0);
								ParameterPage_dis(5, 0);
								ParameterPage_dis(6, 0);
								
								ParameterPage_dis(Para_sel, 1);	
								SaveUnit();	
								break;
							case 7:  //ѹֽ ͣ��
								if(PressValid_flag==0)
									PressValid_flag=1;
								else 
									PressValid_flag=0;
								if(InputTouch_flag==0)  //	  ���������� ��
									ParameterPage_dis(Para_sel, 1);	
								SavePressValid_flag();	
								break;
							}	
						}
					else	//page 2
						{
						switch(Para2_sel)	
							{
							case 0://���ѡ
								if(IR_SensorStus==0)
										IR_SensorStus=1;
									else
										IR_SensorStus=0;
									if(InputTouch_flag==0)  //	  !���������� ��
										ParameterPage2_dis(Para2_sel, 1);	
									SaveIRValidStatus();	
								break;
							case 2://	ǰ����
								if(Front_LimitValid_flag==0)
									Front_LimitValid_flag=1;//��Ч
								else
									Front_LimitValid_flag=0;
								if(InputTouch_flag==0)  //	  !���������� ��
									ParameterPage2_dis(Para2_sel, 1);	
								SaveFrontValidStatus();	
								break;
							case 3://	�м���
								if(Middle_LimitValid_flag==0)
									Middle_LimitValid_flag=1;//��Ч
								else
									Middle_LimitValid_flag=0;
								if(InputTouch_flag==0)  //	  !���������� ��
									ParameterPage2_dis(Para2_sel, 1);	
								SaveMiddleValidStatus();	
								break;
							case 4://	����
								if(Back_LimitValid_flag==0)
									Back_LimitValid_flag=1;//��Ч
								else
									Back_LimitValid_flag=0;
								if(InputTouch_flag==0)  //	  !���������� ��
									ParameterPage2_dis(Para2_sel, 1);	
								SaveBackValidStatus();	
								break;
							}
						}
							break;
				case MANUAL_PASS_MODE: //�ֶ� ��������
					if(PassModeOk_flag==1)
						{
						if(Para_sel==0)
							{
							if(FirstDayValid_flag==1)
								{
								FirstDayValid_flag=0;
								if(SecondDayValid_flag==1)  //���� ���μ�ʱ
									{
									Start_days.year=Year;
									Start_days.month=Month;
									Start_days.day=Dom;
									SaveWorkDays(); //��ʼ ʱ�䱣��
									}
								}
							else  //---------ʱ����Ч
								{
								FirstDayValid_flag=1;
								Start_days.year=Year;
								Start_days.month=Month;
								Start_days.day=Dom;
								SaveWorkDays(); //��ʼ ʱ�䱣��
								}
							SaveFirstDays_flag();	
							}
						else
							{
							if(SecondDayValid_flag==1)
								SecondDayValid_flag=0;
							else if(FirstDayValid_flag==1) //ǰһ�� ���趨��Ч
								SecondDayValid_flag=1;
							SaveSecondDays_flag();	
							}
						PassDaysSet_dis(Para_sel, 1);//�����趨
						}
				}			
			 }
		   else
			 {
									
			 }
		  }
  	        break;
    case FIVE_KEY_CODE:		//ɾ������*************
        if(WorkStart_flag==1)
		  {
		  if(Run_flag==0)
			 {
			 switch(WorkMode)
				{
				case PROG_MODE://��̻�����
				case TEACH_MODE://ʾ�̻�����
				case AUTO_MODE://�Զ���������
				case SELF_CUT_MODE://�Ե���������
					if(Knife_order<=Knife_sum)
						{
						DeleteOneKnife(Pro_data.pro_num, Knife_order);      //ɾ��һ��
						//Size_1page_dis(Knife_order,cursor_row);
						if(Knife_sum>1)
							{
							Knife_sum--;
							SaveKnife_sum(Pro_data.pro_num);
							StepNum_dis(Knife_sum,Knife_order);//�������
							PromptDis_flag=0;
							GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
							switch(Language)
								{
								case CHN_HAN:
									Printf24("��������5�룬ɾ��ȫ��!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
										break;
								case ENGLISH:
									Printf24("Long-press 5 sec,deleate all!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
										break;
								}
								
							if(Knife_order<=Knife_sum)
								{
								pKnife_data=(pInt8U)&OneKnife_data;
								if(Knife_order>1)
									{
									GetOneKnife_datas(Pro_data.pro_num, Knife_order-1, pKnife_data);//ǰһ��
									perv_data=OneKnife_data.size;
									}
								else
									{
									perv_data=0;
									}
								GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);// ��ǰ��
								Flg_chg=0;
								if(OneKnife_data.k_flag==KNIFE_FLAG) //�� ��־
									{
									if(OneKnife_data.size>perv_data)
										{
										OneKnife_data.k_flag=0;//��� �� ��־
										Flg_chg=1;
										flag_now=OneKnife_data.k_flag;	//��ǰ��� �ݴ�
										SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//����һ������
										}
									}	
								}
							}
						Size_1page_dis(Knife_order,cursor_row);
						if(InputTouch_flag==0) //----�� ����������-���±��
							{
							if(Flg_chg==1)
								{
								PushFlag_dis(cursor_row,flag_now); //��괦  ���ͼƬ ��ʾ
								}
							}
						}
							break;
				}	
			 }
		   else
			 {
									
			 }
		  }
  	     break;	  
    case UP_KEY_CODE:    ///////////���а���*******************  
      qianjinflag=0;
        houtuiflag=0;
        if(WorkStart_flag==1)  
			{
			if(Run_flag==0)
			    {
				switch(WorkMode)
					{
					case MANUAL_MODE:   //�ֶ�
						if(Sign_flag==1)  //��� ����
							{
							if(num_cou>0)	
								{
								if(num_cou<8)
									{
									CheckInputNums();
									if(Unit==UNIT_MM)//mm
										{
										if(InTargetPosit_flag==1)  //	Ŀ��λ��
											target_temp=TargetSize_temp;
										else	
											target_temp=CurrentSize;
										}
									else  //inch
										{
										if(InTargetPosit_flag==1)  //	Ŀ��λ��
											target_temp=TargetSize_inch;
										else	
											target_temp=CurrentSize*100/254;
										}
									
									if(Minus_flag==1) //����-��
										{
										if(target_temp>InputSize)
											{
											d_temp=target_temp-InputSize;
											}
										else//������Χ
											{
											num_cou=0;
											GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
											switch(Language)
													{
													case CHN_HAN:
															Printf24("����ߴ糬������!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													case ENGLISH:
															Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													}
											if(InputTouch_flag==1)   //������
												{
												ClearCalculatorInput(); //��������� ����
												}		
											}
										}	
									else     //��  ��+��
										{
										d_temp=target_temp+InputSize;
										}	
									
									if((d_temp<Size_MIN_num)||(d_temp>Size_MAX_num))//������Χ
										{
										num_cou=0;
										GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
										PromptDis_flag=0;
										GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
										switch(Language)
											{
											case CHN_HAN:
													Printf24("����ߴ糬������!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
											case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
											}
										if(InputTouch_flag==1)   //������
											{
											ClearCalculatorInput(); //��������� ����
											}	
										}
									else   //������Ч	 
										{
										if(Unit==UNIT_MM)//mm
											{
											TargetSize=d_temp;
											NewInput_dis(TargetSize);
											}
										else
											{
											TargetSize_inch=d_temp;
											TargetSize=TargetSize_inch*2.54;
											NewInput_dis(TargetSize_inch);
											}
									
										PromptNum_dis();//���뷶Χ ��ʾ
										PromptDis_flag=1;
										num_cou=8;
										if(TargetSize!=CurrentSize)  //-------------����
										//if(1)
											{
											TargetSize_temp=TargetSize;
											switch(MotorType)
												{
												case MOTOR_FREQ_5_SPD_RST:
												case MOTOR_FREQ_3_SPD:
												case MOTOR_FREQ_3_SPD_RST:
													 SelfLockEn_flag=0;
													 ToTargetStop_flag=0;
													 MoveSpeed=0;
													 MoveSpeedCtrl();  //�����ٶȿ���
														break;
												case MOTOR_DC_SERVO:
												case MOTOR_DC670_SERVO:
												case MOTOR_DC670_SERVO_ZHU:
													ServoSendCou=0;
													 DcServoStartRun_exec(TargetSize);
													// SelfLockEn_flag=0;
														break;
												case MOTOR_AC_SERVO:
													ACMotorRunStart(TargetSize);
														break;		
												}
											Run_flag=1;
											RunStop_flag=0;
											AutoCutStart_flag=0;
											InTargetPosit_flag=0;	//Ŀ��λ��
											OneCutRoutine_flag=0; // �� ���� ѭ����־
											AutoCutStart_flag=0;
											PromptNum_dis();
											}
										}
									Sign_flag=0;
									}
									
								}
							}
						else
							{
							if(num_cou>0)	
								{
								if(num_cou<8)
									{
									if(CheckInputNums()==1)// ���� ��Ч
										{
										if(InputTouch_flag==0)  //	 �� ���������� ��
											num_cou=8;
										if(InputSize!=CurrentSize)
										//if(1)
											{
											if(Unit==UNIT_MM)//mm
												{
												TargetSize=InputSize;
												}
											else
												{
												TargetSize_inch=InputSize;
												TargetSize=TargetSize_inch*2.54;
												}
											TargetSize_temp=TargetSize;
											switch(MotorType)
												{
												case MOTOR_FREQ_5_SPD_RST:
												case MOTOR_FREQ_3_SPD:
												case MOTOR_FREQ_3_SPD_RST:
													 SelfLockEn_flag=0;
													 ToTargetStop_flag=0;
													 MoveSpeed=0;
													 MoveSpeedCtrl();  //�����ٶȿ���
														break;
												case MOTOR_DC_SERVO:
												case MOTOR_DC670_SERVO:
												case MOTOR_DC670_SERVO_ZHU:
													 ServoSendCou=0;
													 DcServoStartRun_exec(TargetSize);
													// SelfLockEn_flag=0;
														break;
												case MOTOR_AC_SERVO:
													 ACMotorRunStart(TargetSize);
													// SelfLockEn_flag=0;
														break;		
												}
											Run_flag=1;
											RunStop_flag=0;
											InTargetPosit_flag=0;	//Ŀ��λ��
											OneCutRoutine_flag=0; // �� ���� ѭ����־
											AutoCutStart_flag=0;
											PromptNum_dis();
											}
										}
									else  //��Ч
										{
										ClrInput_function();//���� �����
										}
									}
								else          //�� ��������  ֱ������
									{
									if(TargetSize_temp!=CurrentSize)
									//if(1)
										{
										TargetSize=TargetSize_temp;
										switch(MotorType)
											{
											case MOTOR_FREQ_5_SPD_RST:
											case MOTOR_FREQ_3_SPD:
											case MOTOR_FREQ_3_SPD_RST:
												 SelfLockEn_flag=0;
												 ToTargetStop_flag=0;
												 MoveSpeed=0;
												 MoveSpeedCtrl();  //�����ٶȿ���
													break;
											case MOTOR_DC_SERVO:
											case MOTOR_DC670_SERVO:
											case MOTOR_DC670_SERVO_ZHU:
												 ServoSendCou=0;
												 DcServoStartRun_exec(TargetSize);
												// SelfLockEn_flag=0;
													break;
											case MOTOR_AC_SERVO:
												 ACMotorRunStart(TargetSize);
													break;		
											}
										Run_flag=1;
										RunStop_flag=0;
										InTargetPosit_flag=0;	//Ŀ��λ��
										OneCutRoutine_flag=0; // �� ���� ѭ����־
										AutoCutStart_flag=0;
										PromptNum_dis();
										}
									}
								}
							else
								{
								//ClrInput_function();//���� �����
								//CheckInputNums();
								}
							}	
							break;
					case AUTO_MODE://�Զ�  ��������
					case SELF_CUT_MODE://�Ե� ��������
					//case TEACH_MODE://ʾ�̻�����
						OneCutRoutine_flag=0; // �� ���� ѭ����־
						AutoRun_start();   //������ ��괦
							break;
					case TEACH_MODE://ʾ�� ģʽ
						if(num_cou>0)	
							{
							if(num_cou<8)
								{
								if(CheckInputNums()==1)// ���� ��Ч
									{
									if(InputTouch_flag==0)  //	 �� ���������� ��
										num_cou=8;
									if(InputSize!=CurrentSize)
									//if(1)
										{
										if(Unit==UNIT_MM)//mm
											{
											TargetSize=InputSize;
											}
										else
											{
											TargetSize_inch=InputSize;
											TargetSize=TargetSize_inch*2.54;
											}
										TargetSize_temp=TargetSize;
										switch(MotorType)
											{
											case MOTOR_FREQ_5_SPD_RST:
											case MOTOR_FREQ_3_SPD:
											case MOTOR_FREQ_3_SPD_RST:
												 SelfLockEn_flag=0;
												 ToTargetStop_flag=0;
												 MoveSpeed=0;
												 MoveSpeedCtrl();  //�����ٶȿ���
													break;
											case MOTOR_DC_SERVO:
											case MOTOR_DC670_SERVO:
											case MOTOR_DC670_SERVO_ZHU:
												 ServoSendCou=0;
												 DcServoStartRun_exec(TargetSize);
												// SelfLockEn_flag=0;
													break;
											case MOTOR_AC_SERVO:
												 ACMotorRunStart(TargetSize);
												// SelfLockEn_flag=0;
													break;		
											}
										Run_flag=1;
										RunStop_flag=0;
										InTargetPosit_flag=0;	//Ŀ��λ��
										OneCutRoutine_flag=0; // �� ���� ѭ����־
										AutoCutStart_flag=0;
										PromptNum_dis();
										}
									}
								else  //��Ч
									{
									ClrInput_function();//���� �����
									}
								}
							else          //�� ��������  ֱ������
								{
								if(TargetSize_temp!=CurrentSize)
								//if(1)
									{
									TargetSize=TargetSize_temp;
									switch(MotorType)
										{
										case MOTOR_FREQ_5_SPD_RST:
										case MOTOR_FREQ_3_SPD:
										case MOTOR_FREQ_3_SPD_RST:
											 SelfLockEn_flag=0;
											 ToTargetStop_flag=0;
											 MoveSpeed=0;
											 MoveSpeedCtrl();  //�����ٶȿ���
												break;
										case MOTOR_DC_SERVO:
										case MOTOR_DC670_SERVO:
										case MOTOR_DC670_SERVO_ZHU:
											 ServoSendCou=0;
											 DcServoStartRun_exec(TargetSize);
											// SelfLockEn_flag=0;
												break;
										case MOTOR_AC_SERVO:
											 ACMotorRunStart(TargetSize);
												break;		
										}
									Run_flag=1;
									RunStop_flag=0;
									InTargetPosit_flag=0;	//Ŀ��λ��
									OneCutRoutine_flag=0; // �� ���� ѭ����־
									AutoCutStart_flag=0;
									PromptNum_dis();
									}
								}
							}
						else
							{
							OneCutRoutine_flag=0; // �� ���� ѭ����־
							AutoRun_start();   //������ ��괦
							}
							break;
					}
				}	
            else
				{
				
				}
			}
		else
			{
			switch(MotorType)
				{
				case MOTOR_FREQ_5_SPD_RST:
				case MOTOR_FREQ_3_SPD:
				case MOTOR_FREQ_3_SPD_RST:
					if(StartCheck_mode==4)
						{
						if(Board_TestMod==0)       //-----
							{
							if(PassCodeEn_flag==0)
								{
								MoveSpeed=2;
								SetMotorSpeed(MoveSpeed);//�и���
								MoveBack(); //����
								CurrentArea_recover2(REMIND_WINDOW_X, REMIND_WINDOW_Y, START_PROM_WIDE, START_PROM_HIGH);
								switch(Language)
									{
									case CHN_HAN:
											Printf24("����....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									case ENGLISH:
											Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									}
								StartCheck_mode++;
								CodeSensorTime_AB=0;
								}
							else   //���� ����
								{
								if(PassCheckDis_flag==0) //������ʾ ------��ʾ
									{
									PassCheckDis_flag=1;
									switch(Language)
										{
										case CHN_HAN:
												Printf24("��Чʹ��ʱ�䵽�����������룡",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;
										case ENGLISH:
												Printf24("Your hour is up,enter passcode",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;
										}
									PassCheck_dis(PASSCODE_X+400,PASSCODE_Y);
									GLCD_SetWindow_Fill(PASSCODE_INPUT_X, PASSCODE_INPUT_Y, PASSCODE_INPUT_X+100, PASSCODE_INPUT_Y+30, 0xfffff, 0xffff);
									}
								}
							}
						}
						break;
				case MOTOR_DC_SERVO:
				case MOTOR_DC670_SERVO:
				case MOTOR_DC670_SERVO_ZHU:
					if(StartCheck_mode==1)
						{
						if(Board_TestMod==0)       //-----
							{
							if(PassCodeEn_flag==0)
								{
								CurrentSize=OriginalSize;
								//if(SearchZero_flag==0)   //δ��0
									ServoSetCommd(SERVO_COMMD_R,STAT_30H,CurrentSize);  //����Ѱ��
								CurrentArea_recover2(REMIND_WINDOW_X, REMIND_WINDOW_Y, START_PROM_WIDE, START_PROM_HIGH);
								switch(Language)
									{
									case CHN_HAN:
											Printf24("����....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									case ENGLISH:
											Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									}
								StartCheck_mode++;
								}
							else   //���� ����
								{
								if(PassCheckDis_flag==0) //������ʾ ------��ʾ
									{
									PassCheckDis_flag=1;
									switch(Language)
										{
										case CHN_HAN:
												Printf24("��Чʹ��ʱ�䵽�����������룡",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;
										case ENGLISH:
												Printf24("Your hour is up,enter passcode",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;
										}
									PassCheck_dis(PASSCODE_X+400,PASSCODE_Y);
									GLCD_SetWindow_Fill(PASSCODE_INPUT_X, PASSCODE_INPUT_Y, PASSCODE_INPUT_X+100, PASSCODE_INPUT_Y+30, 0xfffff, 0xffff);
									}
								}
							}
						}
						break;
				case MOTOR_AC_SERVO:
					if(StartCheck_mode==4)
						{
						if(Board_TestMod==0)       //-----
							{
							if(PassCodeEn_flag==0)
								{
								ACServoMoveBack_MID_SPD();  //�����ŷ�  ���ٺ���
								CurrentArea_recover2(REMIND_WINDOW_X, REMIND_WINDOW_Y, START_PROM_WIDE, START_PROM_HIGH);
								switch(Language)
									{
									case CHN_HAN:
											Printf24("����....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									case ENGLISH:
											Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									}
								StartCheck_mode++;
								CodeSensorTime_AB=0;
								}
							else   //���� ����
								{
								if(PassCheckDis_flag==0) //������ʾ ------��ʾ
									{
									PassCheckDis_flag=1;
									switch(Language)
										{
										case CHN_HAN:
												Printf24("��Чʹ��ʱ�䵽�����������룡",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;
										case ENGLISH:
												Printf24("Your hour is up,enter passcode",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;
										}
									PassCheck_dis(PASSCODE_X+400,PASSCODE_Y);
									GLCD_SetWindow_Fill(PASSCODE_INPUT_X, PASSCODE_INPUT_Y, PASSCODE_INPUT_X+100, PASSCODE_INPUT_Y+30, 0xfffff, 0xffff);
									}
								}
							}
						}
						break;
				}	
			}
			
  	     break;  
	case DOWN_KEY_CODE:   // ȷ��************** 
		if(WorkStart_flag==1)
		  {
		  if(Run_flag==0)
			 {
			 switch(WorkMode)
					{
					case PROG_MODE://��̻�����
					case TEACH_MODE://ʾ�̻�����
					case AUTO_MODE://�Զ���������
					case SELF_CUT_MODE://�Ե���������
						if(Sign_flag==0)
							{
							if(num_cou>0)
							  {
							  if(CheckInputNums()==1)// ���� ��Ч
								 {
								 //----��������----------------
								 if(Knife_order>Knife_sum)//���²��� �ܵ���
									{
									Knife_sum=Knife_order;
									}
								 pKnife_data=(pInt8U)&OneKnife_data;
								 if(Knife_order>1)
									{
									GetOneKnife_datas(Pro_data.pro_num, Knife_order-1, pKnife_data);//ǰһ��
									perv_data=OneKnife_data.size;
									}
								 else
									{
									perv_data=0;
									}
								 GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);//
								 OneKnife_data.size=InputSize;  //�ߴ��޸�
								 Flg_chg=0;
								 if((OneKnife_data.k_flag&0xf)==KNIFE_FLAG) //�� ��־
									{
									if(InputSize>perv_data)
										{
										OneKnife_data.k_flag=0;//��� �� ��־
										Flg_chg=1;
										flag_now=OneKnife_data.k_flag;	//��ǰ��� �ݴ�
										}
									}
								 SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//����һ������
								 if(Knife_order<Knife_sum)// �������һ��
									{
									GetOneKnife_datas(Pro_data.pro_num, Knife_order+1, pKnife_data);// ��һ�� ����
									 if(OneKnife_data.k_flag==KNIFE_FLAG) //�� ��־
										{
										if(OneKnife_data.size>InputSize)
											{
											OneKnife_data.k_flag=0;	//��� �� ��־
											if(Flg_chg==1)
												{
												Flg_chg=3;
												}
											else
												{
												Flg_chg=2;
												}
											SaveOneKnife_datas(Pro_data.pro_num, Knife_order+1 , pKnife_data);//������һ��	
											}
										}
									}
									
									//-----��ʾ
								 KnifeSize_dis(cursor_row,InputSize,0);//�ߴ�
								 if(Knife_order<MAIX_Knife)            //�������
									{
									if((WorkMode==PROG_MODE)||(WorkMode==TEACH_MODE))
										{
										Knife_order++;
										StepNum_dis(Knife_sum,Knife_order);//�������
										if(cursor_row<(PAGE_KNIFE-1))
											{
											CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
											OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //һ������ ������ʾ
											cursor_row++;
											CursorMov_dis(cursor_row, 1);//��ɫ���������ʾ
											OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //һ������ ������ʾ
											if(InputTouch_flag==0) //---�� ����������-���±�� 
												{
												switch(Flg_chg)
													{
													case 1:
														PushFlag_dis(cursor_row-1,flag_now); // ���ͼƬ ��ʾ
														break;
													case 2:
														PushFlag_dis(cursor_row,OneKnife_data.k_flag); //��괦 ���ͼƬ ��ʾ
														break;
													case 3:
														PushFlag_dis(cursor_row-1,flag_now); // ���ͼƬ ��ʾ
														PushFlag_dis(cursor_row,OneKnife_data.k_flag); //��괦 ���ͼƬ ��ʾ
														break;
													}
												}
											}
										else   //ҳ��
											{
											Size_1page_dis(Knife_order-(PAGE_KNIFE-1),0);//һҳ�ߴ���ʾ
											}
										}
									else
										{
										StepNum_dis(Knife_sum,Knife_order);//�������
										KnifeSize_dis(cursor_row,InputSize,RED_COLOR);//�ߴ�
										if(InputTouch_flag==0) //----�� ����������-���±��
											{
											switch(Flg_chg)
												{
												case 1:
													PushFlag_dis(cursor_row,flag_now); // ���ͼƬ ��ʾ
													break;
												case 2:
													PushFlag_dis(cursor_row+1,OneKnife_data.k_flag); //��괦 ���ͼƬ ��ʾ
													break;
												case 3:
													PushFlag_dis(cursor_row,flag_now); // ���ͼƬ ��ʾ
													PushFlag_dis(cursor_row+1,OneKnife_data.k_flag); //��괦 ���ͼƬ ��ʾ
													break;
												}
											}
										}
									}
								else
									{
									OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //һ������ ������ʾ
									if(InputTouch_flag==0) //----�� ����������-���±��
										{
										if(Flg_chg==1)
											{
											PushFlag_dis(cursor_row,flag_now); //��괦  ���ͼƬ ��ʾ
											}
										}
									}
								 }
							//if(InputTouch_flag==0)  //	 �� ���������� ��	 
								ClrInput_function();//���� �����
							 }
							}
						else
							{
							if(num_cou>0)
								{
								ArithmeticInputSize(); //�Ե�ǰ�ߴ� ��������
								Sign_flag=0;
								}
							}
						   break;
					case PROG_LABEL_MODE:		//��ǩ ģʽ**********************************
						if(num_cou>0)
						   {
						   LabelEnter_exec();//��ǩ ���� �����趨ȷ��
						   }  
						else
						   {
						   if((Total_size*Label_size*Waste_size)!=0)//�趨��Ч
								{
								if(InputTouch_flag==0)    //�� ���������� ��
									{
									WorkMode=PROG_MODE;         //------------------�˳����ص������ ���� 
									CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
									Program_dis(PROGRAM_X,PROGRAM_Y);   //���
									Label_function();
									PorgSet_sel=0;
									//PaperCutEnb_signal=1;
									}
								else
									CalcuInClear_exec();     //��� ������
								}
						   } 
						   break;
					case TEACH_LABEL_MODE:		//��ǩ ģʽ**********************************
						if(num_cou>0)
							{
							LabelEnter_exec();//��ǩ ���� �����趨ȷ��
							}  
						else
							{
							if((Total_size*Label_size*Waste_size)!=0)//�趨��Ч
								{
								if(InputTouch_flag==0)    //�� ���������� ��
									{
									WorkMode=TEACH_MODE;         //------------------�˳����ص�ʾ���� ���� 
									PaperCutEnb_signal=1;
									CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
									Teach_dis(TEACH_X,TEACH_Y);   //ʾ��
									Label_function();
									PorgSet_sel=0;
									}
								else
									CalcuInClear_exec();     //��� ������	
								}
							} 
						   break;		   
					case PROG_DIVIDE_MODE:	//�ȷ�ģʽ***************************************	
						if(num_cou>0)
						   {
						   DivideEnter_exec();//�ȷ� �����趨ȷ��
						   }
						else
						   {
						   if((Total_size*Divide_num)!=0)//�趨�ȷ���Ч
								{
								if(InputTouch_flag==0)    //�� ���������� ��
									{
									WorkMode=PROG_MODE;           //------------------�˳����ص������ ����
									CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
									Program_dis(PROGRAM_X,PROGRAM_Y);   //���
									Divide_function();//
									PorgSet_sel=0;
									//PaperCutEnb_signal=1;
									}
								else
									CalcuInClear_exec();     //��� ������	
								}
						   }
						   break;
					case TEACH_DIVIDE_MODE:	//�ȷ�ģʽ***************************************	
						if(num_cou>0)
						   {
						   DivideEnter_exec();//�ȷ� �����趨ȷ��
						   }
						else
						   {
						   if((Total_size*Divide_num)!=0)//�趨�ȷ���Ч
								{
								if(InputTouch_flag==0)    //�� ���������� ��
									{
									WorkMode=TEACH_MODE;           //------------------�˳����ص�ʾ���� ����
									PaperCutEnb_signal=1;
									CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
									Teach_dis(TEACH_X,TEACH_Y);   //ʾ��
									Divide_function();//
									PorgSet_sel=0;
									}
								else
									CalcuInClear_exec();     //��� ������		
								}
						   }
						   break;		   
					case PROG_PRO_MODE:	//����ѡ��*****************************	   
						if(num_cou>0)
							{
							  ProEnter_exec();//����ѡ�� ����ȷ��
							}
						else
							{
							 if((Pro_num>0)&&(Pro_num<=MAIX_PROG))// ��Ч  ����һ�����򣬲���ʾ--------------------
								{
								if(InputTouch_flag==0)    //�� ���������� ��
									{
									cursor_temp=0;
									ExportOnePro_dis(Pro_num);  //����һ�� ����   
									//----------���ر�̻���
									WorkMode=PROG_MODE; 
									Program_dis(PROGRAM_X,PROGRAM_Y);   //���
									//PaperCutEnb_signal=1;
									}
								else
									CalcuInClear_exec();     //��� ������
								}
							}	
							break;
					case TEACH_PRO_MODE:	//����ѡ��*****************************	   
						if(num_cou>0)
							{
							  ProEnter_exec();//����ѡ�� ����ȷ��
							}
						else
							{
							 if((Pro_num>0)&&(Pro_num<=MAIX_PROG))// ��Ч  ����һ�����򣬲���ʾ--------------------
								{
								if(InputTouch_flag==0)    //�� ���������� ��
									{
									cursor_temp=0;
									ExportOnePro_dis(Pro_num);  //����һ�� ����   
									//----------����ʾ��
									WorkMode=TEACH_MODE; 
									PaperCutEnb_signal=1;
									Teach_dis(TEACH_X,TEACH_Y);   //ʾ��
									}
								else
									CalcuInClear_exec();     //��� ������
								}
							}	
							break;			
					case AUTO_PLUS_MODE:  //F3++
						if(num_cou>0)
							{
							if(Knife_order<=Knife_sum)
							   {
							   if(CheckInputNums()==1)
									{
									F3_AutoAdd_exec(InputSize);  
									if(InputTouch_flag==0)  //	 �� ���������� ��
										ClrInput_function();//���� �����
									else	//���� ��
										CalcuInClear_exec();     //��� ������
									WorkMode=AUTO_MODE;
									PaperCutEnb_signal=1;
									PressCircle_mode=0;
									F3_plus_dis(0);	
									}	
							   }
							}
							break;
					case AUTO_MINUS_MODE:// F4--
						if(num_cou>0)
							{
							if(Knife_order<=Knife_sum)
							   {
							   if(CheckInputNums()==1)
									{
									F4_AutoSub_exec(InputSize);  //F4--  �������� �Լ�
									if(InputTouch_flag==0)  //	 �� ���������� ��
										ClrInput_function();//���� �����
									else	//���� ��
										CalcuInClear_exec();     //��� ������	
									WorkMode=AUTO_MODE;//����
									PaperCutEnb_signal=1;
									PressCircle_mode=0;
									F4_minus_dis(0);
									}
							   }
							}
							break;
					case SELF_PLUS_MODE:  //F3++
						if(num_cou>0)
							{
							if(Knife_order<=Knife_sum)
							   {
							   if(CheckInputNums()==1)
									{
									F3_AutoAdd_exec(InputSize);  
									F3_plus_dis(0);	
									if(InputTouch_flag==0)  //	 �� ���������� ��
										ClrInput_function();//���� �����
									else	//���� ��
										CalcuInClear_exec();     //��� ������	
									WorkMode=SELF_CUT_MODE;
									}
							   }
							}
							break;
					case SELF_MINUS_MODE:// F4--
						if(num_cou>0)
							{
							if(Knife_order<=Knife_sum)
							   {
							   if(CheckInputNums()==1)
									{
									F4_AutoSub_exec(InputSize);  //F4--  �������� �Լ�
									if(InputTouch_flag==0)  //	 �� ���������� �� 
										ClrInput_function();//���� �����
									else	//���� ��
										CalcuInClear_exec();     //��� ������	
									WorkMode=SELF_CUT_MODE;//����
									F4_minus_dis(0);
									}
							   }
							}
							break;			
					case AUTO_RULER_MODE://�Զ� ��׼
					case SELF_RULER_MODE://�Ե� ��׼
					case MANUAL_RULER_MODE://�ֶ� ��׼ģʽ
						if(num_cou>0)
							{
							if(CheckInputNums()==1)
								{
								if(Unit!=UNIT_MM)//mm
									InputSize*=2.54;
									
									//********************************=============
									SelfLockEn_flag=0;
									ToTargetStop_flag=0;
									InTargetPosit_flag=0;	//Ŀ��λ��
									//OneCutRoutine_flag=0; // �� ���� ѭ����־
								switch(MotorType)
									{
									case MOTOR_FREQ_5_SPD_RST:
									case MOTOR_FREQ_3_SPD:
									case MOTOR_FREQ_3_SPD_RST:
									//****************************==============
										MoveStop();
										TargetSize=0;
										TargetSize_temp=0;
										BeforeKnife_offset_in=0;
										Run_flag=0;
										
										OriginalSize=OriginalSize+InputSize-(muqiancn/1000);
										muqiancn=InputSize*1000;
										CurrentSize=InputSize;
											break;
									case MOTOR_DC_SERVO:
									case MOTOR_DC670_SERVO:
									case MOTOR_DC670_SERVO_ZHU:
										DcServoGoTarget_flag=0;
										
										OriginalSize=OriginalSize+InputSize-CurrentSize;
										CurrentSize=InputSize;
										ServoSetCommd(SERVO_COMMD_P,STAT_30H,CurrentSize);
											break;
									case MOTOR_AC_SERVO:	
										OriginalSize=OriginalSize+InputSize-CurrentSize;
										CurrentSize=InputSize;
											break;
									}		
								
								//if(InputSize!=TargetSize_temp)
								//	{
									SaveOriginalSize();  //����ԭ��ߴ�
								//	}
								
								if(InputTouch_flag==1)  //	  ���� ��
									CalcuInClear_exec();     //��� ������
								//-----------------�Զ����� ��ģʽ	
								CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
								if(WorkMode==AUTO_RULER_MODE)   //�Զ���
									{
									WorkMode=AUTO_MODE;//����    �Զ� ��ģʽ
									PaperCutEnb_signal=1;
									PressCircle_mode=0;
									Auto_dis(AUTO_X, AUTO_Y); //�Զ�
									//PromptNum_dis();//���뷶Χ
									//PromptDis_flag=1;
									}
								else if(WorkMode==MANUAL_RULER_MODE)  //�ֶ���
									{
									WorkMode=MANUAL_MODE;//����    �ֶ� ��ģʽ
									Manual_dis(MANUAL_X,MANUAL_Y);//�ֶ�
									// PromptDis_flag=0;
									// GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
									}
								else if(WorkMode==SELF_RULER_MODE)   //�Ե���	
									{
									WorkMode=SELF_CUT_MODE;//����    �Ե� ��ģʽ
									PaperCutEnb_signal=1;
									AutoKnife_dis(SELF_KNIFE_X,SELF_KNIFE_Y); //�Ե�
									}
								PromptNum_dis();//���뷶Χ
								PromptDis_flag=1;
								}
							ClrInput_function();//���� �����
							}
						else
							{						 
							}
							 break;
					case AUTO_TOOLS_MODE://�Զ�  ��������
					case SELF_TOOLS_MODE://�Ե�  ��������
					case MANUAL_TOOLS_MODE:// �ֶ� ����ģʽ
						if(num_cou>0)
							{
							if((CheckInputNums()==1))
								{
								if(PramSel_Page<1)	//page 1
									{
								if(Para_sel<8)
									{
									if(Unit==UNIT_MM)
										{
										if(Para_sel!=5)
											input_temp=InputSize/100*100;
										else
											input_temp=InputSize;
										}
									else
										{
										input_temp=InputSize*2.54;
										}
									}
								else	
									input_temp=InputSize;
								switch(Para_sel)
									{
									case 0: //ǰ����		
										if((input_temp>=FRONT_LIM_MIN)&&(input_temp<=FRONT_LIM_MAX))
											{
											FrontLimit=input_temp;
											SaveFrontLimit();
											if(OIN4_PIN==0)  //�а� �ź�
												{
												Size_MIN=FrontLimit;
												if(Unit==UNIT_MM)
													Size_MIN_num=Size_MIN;
												else
													Size_MIN_num=Size_MIN*100/254;
												}
											if(Para_sel<6)
												{
												ParameterPage_dis(Para_sel++, 0);
												ParameterPage_dis(Para_sel, 1);
												}
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
											switch(Language)
												{
												case CHN_HAN:
													Printf24("����ߴ糬������!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //������
												{
												ClearCalculatorInput(); //��������� ����
												num_cou=0;
												}	
											}
											break;
									case 1: //�м���
										if((input_temp>=MIDD_LIM_MIN)&&(input_temp<=MIDD_LIM_MAX))
											{
											MiddleLimit=input_temp;
											SaveMiddleLimit();
											if(OIN4_PIN!=0)  //�а� �ź�
												{
												Size_MIN=MiddleLimit;
												if(Unit==UNIT_MM)
													Size_MIN_num=Size_MIN;
												else
													Size_MIN_num=Size_MIN*100/254;
												}
											if(Para_sel<6)
												{
												ParameterPage_dis(Para_sel++, 0);
												ParameterPage_dis(Para_sel, 1);
												}
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
											switch(Language)
												{
												case CHN_HAN:
													Printf24("����ߴ糬������!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //������
												{
												ClearCalculatorInput(); //��������� ����
												num_cou=0;
												}	
											}	
											break;	
									case 2: //����
										if((input_temp>=BACK_LIM_MIN)&&(input_temp<=BACK_LIM_MAX))
											{
											BackLimit=input_temp;
											SaveBackLimit();
											Size_MAX=BackLimit;
											if(Unit==UNIT_MM)
												Size_MAX_num=Size_MAX;
											else
												Size_MAX_num=Size_MAX*100/254;
											if(Para_sel<6)
												{
												ParameterPage_dis(Para_sel++, 0);
												ParameterPage_dis(Para_sel, 1);
												}
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
											 switch(Language)
												{
												case CHN_HAN:
													Printf24("����ߴ糬������!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //������
												{
												ClearCalculatorInput(); //��������� ����
												num_cou=0;
												}	
											}
											break;
									case 5: //��ǰ��
										if((input_temp>=1)&&(input_temp<=100))
											{
											Aheader=input_temp;
											SaveAheader();
											if(Para_sel<6)
												{
												ParameterPage_dis(Para_sel++, 0);
												ParameterPage_dis(Para_sel, 1);
												}
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
											switch(Language)
												{
												case CHN_HAN:
													Printf24("����ߴ糬������!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //������
												{
												ClearCalculatorInput(); //��������� ����
												num_cou=0;
												}	
											}
											break;	
									case 6:  //�Զ���ֽ  ����
										if(input_temp<=AUTO_PUSH_DISTAN)
											{
											AutoPushDistance=input_temp;
											SavePushDistance();
											ParameterPage_dis(Para_sel, 1);
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
											switch(Language)
												{
												case CHN_HAN:
													Printf24("����ߴ糬������!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //������
												{
												ClearCalculatorInput(); //��������� ����
												num_cou=0;
												}	
											}	
											break;	
									case 8:		//������� �ٶ�
										if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))   //------------------ֱ��  �ŷ�
											{
											if(MotorType==MOTOR_DC670_SERVO_ZHU)
												{
												ServMaxSpd1=5;ServMaxSpd2=20;
												}
											else
												{
												ServMaxSpd1=13;ServMaxSpd2=20;
												}
											if((input_temp>=ServMaxSpd1)&&(input_temp<=ServMaxSpd2))
												{
												ServoSpeed_order=input_temp;
												SaveMovSpeed();
												ServoSetCommd(SERVO_COMMD_S,STAT_30H,SERVO_SPEED[ServoSpeed_order]);  //�趨�ŷ������
												if(InputTouch_flag==1)   //������
													{
													CalcuInClear_exec();     //��� ������
													}	
												ParameterPage_dis(Para_sel, 1);
												}
											else
												{
												PromptDis_flag=0;
												GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
												switch(Language)
													{
													case CHN_HAN:
														Printf24("�������ݳ�������!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													case ENGLISH:
														Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
													break;
													}
												if(InputTouch_flag==1)   //������
													{
													ClearCalculatorInput(); //��������� ����
													num_cou=0;
													}	
												}	
											}
										else if(MotorType==MOTOR_AC_SERVO)  //*************���� �ŷ�
											{
												if(input_temp<=32)
												{
												AC_MotorSPD=input_temp;
												SaveACMotorSpeed();   //�����ŷ� �ٶ�
												GetAC_MotorSpeed();  //�����ŷ�  �ٶ��ж�
												if(InputTouch_flag==1)   //������
													{
													CalcuInClear_exec();     //��� ������
													}	
												ParameterPage_dis(Para_sel, 1);
												}
											else
												{
												PromptDis_flag=0;
												GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
												switch(Language)
													{
													case CHN_HAN:
														Printf24("�������ݳ�������!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													case ENGLISH:
														Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
													break;
													}
												if(InputTouch_flag==1)   //������
													{
													ClearCalculatorInput(); //��������� ����
													num_cou=0;
													}	
												}
											}
										else
										{//�¼� ��Χ
										if((input_temp>=20)&&(input_temp<=100))
											{
											DisWuCha=input_temp;
											SaveDisWuCha();
											ParameterPage_dis(Para_sel, 0);
											ParameterPage_dis(Para_sel, 1);

											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
											switch(Language)
												{
												case CHN_HAN:
													Printf24("����ߴ糬������!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //������
												{
												ClearCalculatorInput(); //��������� ����
												num_cou=0;
												}	
											}											
											
										}
										
											break;
									case 9:		//�㶯 �ٶ�
										if((input_temp<=20)&&(input_temp>=10))
											{
											JogSpeed_order=input_temp;
											SaveJogSpeed();
											//ServoSetCommd(SERVO_COMMD_S,STAT_30H,SERVO_SPEED[ServoSpeed_order]);  //�趨�ŷ������
											if(InputTouch_flag==1)   //������
												{
												CalcuInClear_exec();     //��� ������
												}	
											ParameterPage_dis(Para_sel, 1);
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
											switch(Language)
												{
												case CHN_HAN:
													Printf24("�������ݳ�������!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //������
												{
												ClearCalculatorInput(); //��������� ����
												num_cou=0;
												}	
											}	
											break;		
									}
								}
								else//page 2
									{
									input_temp=InputSize;	
									switch(Para2_sel)
										{
										case 0:
											
											break;
										case 1:	//Jog-speed
											if((input_temp>0)&&(input_temp<=5))//
												{
												JogLevel=input_temp;
												SaveACJogLevel();
												ParameterPage2_dis(Para2_sel, 1);
												}
											break;	
										}
									}
								}
							else
								num_cou=0;
							if(InputTouch_flag==0)  //	 �� ���������� ��	
								ClrInput_function();//���� �����	
							}
							break;
					case MANUAL_SERVO_C_MODE:// �ֶ�ֱ���ŷ� C ���� 
						if(num_cou>0)
							{
							if((CheckInputNums()==1))
								{
								input_temp=InputSize;
								switch(Para_sel)
									{
									case 0: //λ�û�����	
										if((input_temp>=1)&&(input_temp<=99))
											{
											if(PositRing_Gain!=input_temp)
												{
												PositRing_Gain=input_temp;
												ServoSetCommd(SERVO_COMMD_C,STAT_11H,PositRing_Gain);
												}
											
											if(Para_sel<6)
												{
												ServoParameter_dis(Para_sel++, 0);
												ServoParameter_dis(Para_sel, 1);
												}
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
											switch(Language)
												{
												case CHN_HAN:
													Printf24("�������ݳ�������!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //������
												{
												ClearCalculatorInput(); //��������� ����
												num_cou=0;
												}	
											}
											break;
									case 1: //λ�û�΢��
										if((input_temp>=1)&&(input_temp<=99))
											{
											if(PositRing_Diff!=input_temp)
												{
												PositRing_Diff=input_temp;
												ServoSetCommd(SERVO_COMMD_C,STAT_21H,PositRing_Diff);
												}
											
											if(Para_sel<6)
												{
												ServoParameter_dis(Para_sel++, 0);
												ServoParameter_dis(Para_sel, 1);
												}
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
											switch(Language)
												{
												case CHN_HAN:
													Printf24("�������ݳ�������!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //������
												{
												ClearCalculatorInput(); //��������� ����
												num_cou=0;
												}	
											}	
											break;	
									case 2: //λ�û�����
										if((input_temp>=1)&&(input_temp<=99))
											{
											if(PositRing_Integral!=input_temp)
												{
												PositRing_Integral=input_temp;
												ServoSetCommd(SERVO_COMMD_C,STAT_31H,PositRing_Integral);
												}
												
											if(Para_sel<6)
												{
												ServoParameter_dis(Para_sel++, 0);
												ServoParameter_dis(Para_sel, 1);
												}
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
											 switch(Language)
												{
												case CHN_HAN:
													Printf24("�������ݳ�������!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //������
												{
												ClearCalculatorInput(); //��������� ����
												num_cou=0;
												}	
											}
											break;
									case 3: //�ٶȻ�����
										if((input_temp>=1)&&(input_temp<=99))
											{
											if(SpeedRing_Gain!=input_temp)
												{
												SpeedRing_Gain=input_temp;
												ServoSetCommd(SERVO_COMMD_C,STAT_41H,SpeedRing_Gain);
												}
												
											if(Para_sel<6)
												{
												ServoParameter_dis(Para_sel++, 0);
												ServoParameter_dis(Para_sel, 1);
												}
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
											switch(Language)
												{
												case CHN_HAN:
													Printf24("�������ݳ�������!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //������
												{
												ClearCalculatorInput(); //��������� ����
												num_cou=0;
												}	
											}
											break;	
									case 4:  //�ٶȻ�΢��
										if((input_temp>=1)&&(input_temp<=99))
											{
											if(SpeedRing_Diff!=input_temp)
												{
												SpeedRing_Diff=input_temp;
												ServoSetCommd(SERVO_COMMD_C,STAT_51H,SpeedRing_Diff);
												}
												
											if(Para_sel<6)
												{
												ServoParameter_dis(Para_sel++, 0);
												ServoParameter_dis(Para_sel, 1);
												}
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
											switch(Language)
												{
												case CHN_HAN:
													Printf24("�������ݳ�������!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //������
												{
												ClearCalculatorInput(); //��������� ����
												num_cou=0;
												}	
											}	
											break;	
									case 5:		//�ٶȻ�����
										if((input_temp>=1)&&(input_temp<=99))
											{
											if(SpeedRing_Integral!=input_temp)
												{
												SpeedRing_Integral=input_temp;
												ServoSetCommd(SERVO_COMMD_C,STAT_61H,SpeedRing_Integral);
												}
												
											if(Para_sel<6)
												{
												ServoParameter_dis(Para_sel++, 0);
												ServoParameter_dis(Para_sel, 1);
												}
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
											switch(Language)
												{
												case CHN_HAN:
													Printf24("�������ݳ�������!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //������
												{
												ClearCalculatorInput(); //��������� ����
												num_cou=0;
												}	
											}	
											break;
									case 6:		//���ٱ�
										if((input_temp>=1)&&(input_temp<=3))
											{
											if(SpeedDown_Ratio!=input_temp)
												{
												SpeedDown_Ratio=input_temp;
												ServoSetScrew(Screw_Pitch ,SpeedDown_Ratio);  //�ݾ��趨
												Save_PitchRatio();
												}
											ServoParameter_dis(Para_sel, 1);
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
											switch(Language)
												{
												case CHN_HAN:
													Printf24("�������ݳ�������!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //������
												{
												ClearCalculatorInput(); //��������� ����
												num_cou=0;
												}	
											}	
											break;	
									case 7:		//�ݾ�
										if((input_temp==10)||(input_temp==12))
											{
											if(Screw_Pitch!=input_temp)
												{
												Screw_Pitch=input_temp;
												ServoSetScrew(Screw_Pitch ,SpeedDown_Ratio);  //�ݾ��趨
												Save_PitchRatio();
												}
											if(InputTouch_flag==1)   //������
												{
												CalcuInClear_exec();     //��� ������
												}	
											ServoParameter_dis(Para_sel, 1);
											}
										else
											{
											PromptDis_flag=0;
											GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
											switch(Language)
												{
												case CHN_HAN:
													Printf24("�������ݳ�������!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case ENGLISH:
													Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
												}
											if(InputTouch_flag==1)   //������
												{
												ClearCalculatorInput(); //��������� ����
												num_cou=0;
												}	
											}	
											break;			
									}
								}
							else
								num_cou=0;
							if(InputTouch_flag==0)  //	 �� ���������� ��	
								ClrInput_function();//���� �����	
							}
							break;
					case MANUAL_CLOCK_MODE: //�ֶ� ʱ��ģʽ
						if(num_cou>0)
							{
							if((CheckInputNums()==1))
								{
								switch(Para_sel)
									{
									case 0:  //��
										if(InputSize<100)
											{
											Year=(Int8U)((InputSize/10)<<4|(InputSize%10));
											write_time();//-------------ʱ���趨ֵ����д��
											TimeSetSel_dis(Para_sel++, 0);
											TimeSetSel_dis(Para_sel, 1);
											}	
											break;
									case 1: //��
										if((InputSize<13)&&(InputSize>0))
											{
											Month=(Int8U)((InputSize/10)<<4|(InputSize%10));
											write_time();//-------------ʱ���趨ֵ����д��
											TimeSetSel_dis(Para_sel++, 0);
											TimeSetSel_dis(Para_sel, 1);
											}
											break;
									case 2:  //��
										if((InputSize<32)&&(InputSize>0))
											{
											Dom=(Int8U)((InputSize/10)<<4|(InputSize%10));
											write_time();//-------------ʱ���趨ֵ����д��
											TimeSetSel_dis(Para_sel++, 0);
											TimeSetSel_dis(Para_sel, 1);
											}
											break;
									case 3: //Сʱ
										if(InputSize<24)
											{
											Hour=(Int8U)((InputSize/10)<<4|(InputSize%10));
											write_time();//-------------ʱ���趨ֵ����д��
											TimeSetSel_dis(Para_sel++, 0);
											TimeSetSel_dis(Para_sel, 1);
											}	
											break;
									case 4: //����
										if(InputSize<60)
											{
											Min=(Int8U)((InputSize/10)<<4|(InputSize%10));
											write_time();//-------------ʱ���趨ֵ����д��
											TimeSetSel_dis(Para_sel, 1);
											}
										
											break;		
									}
								if(Year<Year_before)//ʱ�� ��ǰ �ж�------------------
									TimeAhead_flag=1;	
								else if(Year==Year_before)
									{
									if(Month<Month_before)
										{
										TimeAhead_flag=1;
										}
									else if(Month==Month_before)	
										{
										if(Dom<Day_before)
											TimeAhead_flag=1;
										else
											TimeAhead_flag=0;
										}
									else
										TimeAhead_flag=0;
									}
								else
									{
									TimeAhead_flag=0;
									}
									
								if(TimeAhead_flag==1) //ʱ�� ��ǰ
									{
									Start_days.year=Year;
									Start_days.month=Month;
									Start_days.day=Dom;
									SaveWorkDays();//��ʼ ʱ�䱣��
									
									if(FirstDayValid_flag==1)// ʣ�������޸�
										{		 
										if(FirstDays>Past_days)
											{
											Past_days++;
											FirstDays-=Past_days;
											}
										else
											{
											FirstDays=0;
											}
										SaveFirstDays();	
										}
									else if(SecondDayValid_flag==1)
										{	
										if(SecondDays>Past_days)
											{
											Past_days++;
											SecondDays-=Past_days;
											}
										else
											SecondDays=0;
										SaveSecondDays();
										}
									}
								}
							else
								num_cou=0;
							if(InputTouch_flag==0)  //	 �� ���������� ��	
								ClrInput_function();//���� ����� 
							}
							break;
					case MANUAL_PULSE_MODE://�ֶ� ���嵱��  �趨����
						 if(num_cou>0)
							{
							if(CheckInputNums()==1)
								{
								if(InputSize<12)
									{
									if(InputTouch_flag==1)  //	  ���� ��
										CalcuInClear_exec();     //��� ������
									SelPulseDegree_dis(Para_sel, 0); //�����趨
									Para_sel=InputSize;
									SelPulseDegree_dis(Para_sel,1);
									}
								}
							else
								num_cou=0;
							if(InputTouch_flag==0)  //	 �� ���������� ��	
								ClrInput_function();//���� ����� 
							}
						 else
							{
							if(InputTouch_flag==0)  //	��  ���� ��
								{
								Pulse_degree=Para_sel;
								Save_degree();
								WorkMode=MANUAL_MODE;//����    ---------�ֶ� ��ģʽ
								Para_sel=0;
								CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y, M_PAGE_WIDE, M_PAGE_HIGH);
								Manual_dis(MANUAL_X,MANUAL_Y);//�ֶ�
								PromptNum_dis();//���뷶Χ
								PromptDis_flag=1;
								}
							}
							break;
					case MANUAL_PASS_MODE: //�ֶ� ��������
						 if(num_cou>0)
							{
							if(PassModeIn_flag==0)  //����ȷ��
								{
								PassModeIn_flag=1;
								if(CheckInputNums()==1)
									{
									if(InputSize==PASS_MOD_CODE) //������ȷ
										{
										if(InputTouch_flag==1)  //	  ���� ��
											CalcuInClear_exec();     //��� ������
										PassSet_dis(); //���� ���ý���
										Para_sel=0;
										PassModeOk_flag=1;
										}
									}
								}
							else            //���� �趨
								{
								if(PassModeOk_flag==1)  //�ѽ���  ����ģʽ
									{
									if(CheckInputNums()==1)
										{
										if((InputSize>0)&&(InputSize<=300)) //������Ч ����
											{
											if(Para_sel==0)  //��һ�� ʱ��
												{
												FirstDays=InputSize;
												SaveFirstDays();
												if(FirstDayValid_flag==1)
													{
													Start_days.year=Year;
													Start_days.month=Month;
													Start_days.day=Dom;
													SaveWorkDays();//��ʼ ʱ�䱣��
													}
												}
											else   //�ڶ���ʱ��
												{
												SecondDays=InputSize;
												SaveSecondDays();
												}
											PassDaysSet_dis(Para_sel, 1);
											}
										}
									}	
								}
							if(InputTouch_flag==0)  //	 �� ���������� ��	
								ClrInput_function();//���� �����
							}
							break;
					case AUTO_TO_SELF_MODE:   //�Զ�-->�Ե����� ģʽ
						if(InputTouch_flag==1)  //	  ���� ��
							CalcuInClear_exec();     //��� ������
						Int16U color=0xef9f;
						if(LastAutoKnife_order<2)    //--------�״�  ����  ����ʾ
							{
							WorkMode=SELF_CUT_MODE;  //����   ----------�Ե��� ģʽ
							CurrentArea_recover2(SELF_PROMP_X,SELF_PROMP_Y,SELF_PROMP_X+300,SELF_PROMP_Y+120);
							AutoKnife_dis(SELF_KNIFE_X,SELF_KNIFE_Y);//�Ե�
							//------------���ص�һ��
							ClrInput_function();//���� ����� 
							CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
							cursor_row=0;
							CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
							if(Knife_order<=Knife_sum)
								StepOrder_dis(Knife_order);//������� 
							CancelCutflagButton_dis(); //ȡ����ʾ  �� ��� ��ť
							GLCD_SetWindow_Fill(F5_PRE_FLG_X,F5_PRE_FLG_Y,F5_PRE_FLG_X+48,F5_PRE_FLG_Y+48,color,color);//�հ�F5 flag
							}
						else  //���� �����Ե�ģʽ
							{
							if(ReEnterAutoKnife_dis==0) //��ʾ  ��ʾ
								{
								ReEnterAutoKnife_dis=1;
								AutoCutLastKnifeLoad_dis();
								}
							else
								{
								ReEnterAutoKnife_dis=0;
								
								WorkMode=SELF_CUT_MODE;  //����   ----------�Ե��� ģʽ
								CurrentArea_recover2(SELF_PROMP_X,SELF_PROMP_Y,SELF_PROMP_X+300,SELF_PROMP_Y+120);
								AutoKnife_dis(SELF_KNIFE_X,SELF_KNIFE_Y);//�Ե�
								//------------����֮ǰ��
								Knife_order=LastAutoKnife_order;//
								ClrInput_function();//���� ����� 
								CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
								cursor_row=0;
								CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
								
								Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
								if(Knife_order<=Knife_sum)
									StepOrder_dis(Knife_order);//������� 
								LastAutoKnife_order=1;
								CancelCutflagButton_dis(); //ȡ����ʾ  �� ��� ��ť
								GLCD_SetWindow_Fill(F5_PRE_FLG_X,F5_PRE_FLG_Y,F5_PRE_FLG_X+48,F5_PRE_FLG_Y+48,color,color);//�հ�F5 flag
								}
							}
							break;
					case MANUAL_MODE:   //�ֶ���ģʽ  ȷ����Ч
						if(num_cou>0)
							{
							PromptDis_flag=0;
							GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
							switch(Language)
								{
								case CHN_HAN:
										Printf24("�ֶ�ģʽ��,�밴���м�!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
								case ENGLISH:
										Printf24("On this mode,press RUN key!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
								}
							}
						
							break;
					}			
			 }
		  else
			 {
									
			 }
		  }
		else
		  {
		  switch(MotorType)
				{
				case MOTOR_FREQ_5_SPD_RST:
				case MOTOR_FREQ_3_SPD:
				case MOTOR_FREQ_3_SPD_RST:
					 if(StartCheck_mode==1)  //��ֽ�� ��λ����
						 {
						 MoveSpeed=3;
						 SetMotorSpeed(MoveSpeed);//����
						 MoveForward();//ǰ��
						 PusherResetTime=0;
						 CurrentArea_recover3(PUSH_RESET_PROMPT_X1, PUSH_RESET_PROMPT_Y1, PUSH_RESET_PROMPT_WIDE, PUSH_RESET_PROMPT_HIGH);
						 StartCheck_mode++;
						 PushRstKey_flag=1;
						 }
					 else if(StartCheck_mode==4)
						 {
						 if(PassCheckDis_flag==1) //���� ������
							 {
							 if(num_cou>0)
								{
								if(CheckInputNums()==1)
									{
									if(StartPassInput_flag==0)
										{
										StartPassInput_flag=1;
										if(InputSize==PassCode)//������ȷ   
											{
											PassCodeEn_flag=0;
											//PassCheckDis_flag=0;
											
										//-----------ʱ�����
											if(FirstDayValid_flag==1) //�״� ʱ������ ��Ч
												{
												FirstDayValid_flag=0;
												SaveFirstDays_flag(); //��� �״���Ч
												if(SecondDayValid_flag==1) //�ڶ��� ��ʱ��ʼ
													{
													Start_days.year=Year;
													Start_days.month=Month;
													Start_days.day=Dom;
													SaveWorkDays();//��ʼ ʱ�䱣��
													}
												}
											else if(SecondDayValid_flag==1)    //�ڶ��� ��Ч
												{
												SecondDayValid_flag=0;
												SaveSecondDays_flag();
												}
											//---------���� ����
											switch(Language)
												{
												case CHN_HAN:
															Printf24("����������ȷ����ӭ����ʹ�ã�  ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												case ENGLISH:
															Printf24("Password is correct,Welcome to use!    ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												}
											if(StartCheck_mode==4)
												{
												MoveSpeed=2;
												SetMotorSpeed(MoveSpeed);//�и���
												MoveBack(); //����
												CurrentArea_recover2(REMIND_WINDOW_X, REMIND_WINDOW_Y, START_PROM_WIDE, START_PROM_HIGH);
												switch(Language)
													{
													case CHN_HAN:
															Printf24("����....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
																break;
													case ENGLISH:
															Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
																break;
													}
												StartCheck_mode++;
												}
											}
										}
								
									}
								 for(num_cou=0;num_cou<8;num_cou++)
									{
									Size_temp[num_cou++]=0;
									}
								 num_cou=0;	
								}
							 }
						 }
						break;
				case MOTOR_DC_SERVO:
				case MOTOR_DC670_SERVO:
				case MOTOR_DC670_SERVO_ZHU:
					if(StartCheck_mode==1)
						 {
						 if(PassCheckDis_flag==1) //���� ������
							 {
							 if(num_cou>0)
								{
								if(CheckInputNums()==1)
									{
									if(StartPassInput_flag==0)
										{
										StartPassInput_flag=1;
										if(InputSize==PassCode)//������ȷ   
											{
											PassCodeEn_flag=0;
											//PassCheckDis_flag=0;
											
										//-----------ʱ�����
											if(FirstDayValid_flag==1) //�״� ʱ������ ��Ч
												{
												FirstDayValid_flag=0;
												SaveFirstDays_flag(); //��� �״���Ч
												if(SecondDayValid_flag==1) //�ڶ��� ��ʱ��ʼ
													{
													Start_days.year=Year;
													Start_days.month=Month;
													Start_days.day=Dom;
													SaveWorkDays();//��ʼ ʱ�䱣��
													}
												}
											else if(SecondDayValid_flag==1)    //�ڶ��� ��Ч
												{
												SecondDayValid_flag=0;
												SaveSecondDays_flag();
												}
											//---------���� ����
											switch(Language)
												{
												case CHN_HAN:
															Printf24("����������ȷ����ӭ����ʹ�ã�  ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												case ENGLISH:
															Printf24("Password is correct,Welcome to use!    ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												}
												
											
											CurrentSize=OriginalSize;
											//if(SearchZero_flag==0)   //δ��0
											ServoSetCommd(SERVO_COMMD_R,STAT_30H,CurrentSize);  //����Ѱ��
											CurrentArea_recover2(REMIND_WINDOW_X, REMIND_WINDOW_Y, START_PROM_WIDE, START_PROM_HIGH);
											switch(Language)
												{
												case CHN_HAN:
														Printf24("����....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												case ENGLISH:
														Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												}
											StartCheck_mode++;	
											}
										}
								
									}
								 for(num_cou=0;num_cou<8;num_cou++)
									{
									Size_temp[num_cou++]=0;
									}
								 num_cou=0;	
								}
							 }
						 }
						break;
				case MOTOR_AC_SERVO:
					if(StartCheck_mode==1)  //��ֽ�� ��λ����
						{
						ACMotorGoForward();//ǰ��
						// PusherResetTime=0;
						qianjincn=0;
						 CurrentArea_recover3(PUSH_RESET_PROMPT_X1, PUSH_RESET_PROMPT_Y1, PUSH_RESET_PROMPT_WIDE, PUSH_RESET_PROMPT_HIGH);
						 StartCheck_mode++;
						 PushRstKey_flag=1;
						}
					else if(StartCheck_mode==4)//if(StartCheck_mode==2)
						 {
						 if(PassCheckDis_flag==1) //���� ������
							 {
							 if(num_cou>0)
								{
								if(CheckInputNums()==1)
									{
									if(StartPassInput_flag==0)
										{
										StartPassInput_flag=1;
										if(InputSize==PassCode)//������ȷ   
											{
											PassCodeEn_flag=0;
											//PassCheckDis_flag=0;
											
										//-----------ʱ�����
											if(FirstDayValid_flag==1) //�״� ʱ������ ��Ч
												{
												FirstDayValid_flag=0;
												SaveFirstDays_flag(); //��� �״���Ч
												if(SecondDayValid_flag==1) //�ڶ��� ��ʱ��ʼ
													{
													Start_days.year=Year;
													Start_days.month=Month;
													Start_days.day=Dom;
													SaveWorkDays();//��ʼ ʱ�䱣��
													}
												}
											else if(SecondDayValid_flag==1)    //�ڶ��� ��Ч
												{
												SecondDayValid_flag=0;
												SaveSecondDays_flag();
												}
											//---------���� ����
											switch(Language)
												{
												case CHN_HAN:
															Printf24("����������ȷ����ӭ����ʹ�ã�  ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												case ENGLISH:
															Printf24("Password is correct,Welcome to use!    ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												}
												
											
											ACServoMoveBack_MID_SPD();  //�����ŷ�  ���ٺ���
											CurrentArea_recover2(REMIND_WINDOW_X, REMIND_WINDOW_Y, START_PROM_WIDE, START_PROM_HIGH);
											switch(Language)
												{
												case CHN_HAN:
														Printf24("����....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												case ENGLISH:
														Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												}
											StartCheck_mode++;	
											}
										}
								
									}
								 for(num_cou=0;num_cou<8;num_cou++)
									{
									Size_temp[num_cou++]=0;
									}
								 num_cou=0;	
								}
							 }
						 }
						break;
				}	
		 
		  }	
  	     break;          
    case DENGFENG_KEY_CODE:  //���¼�ͷ����**************�·�ҳ
		if(WorkStart_flag==1)
		  {
		  if(Run_flag==0)
			 {
			 switch(WorkMode)
				{
				case PROG_MODE://��̻�����
				case TEACH_MODE://ʾ�̻�����
				case AUTO_MODE://�Զ���������
				case AUTO_PLUS_MODE:  //F3++
				case AUTO_MINUS_MODE:// F4--
				case SELF_CUT_MODE://�Ե���������
				case SELF_PLUS_MODE:  //�Ե�F3++
				case SELF_MINUS_MODE://�Ե� F4--
					if((Knife_order==Knife_sum)&&(Knife_order==1))
						{
						pKnife_data=(pInt8U)&OneKnife_data;
						GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);//
						if((OneKnife_data.size>=Size_MIN_num)&&(OneKnife_data.size<=Size_MAX_num))
							CursorDown_inTable();//**** ������� ��ʾ ����
						}
					else
						CursorDown_inTable();//**** ������� ��ʾ ����
						   break;
				case PROG_LABEL_MODE://��ǩ ��--------------------------
				case TEACH_LABEL_MODE://��ǩ ��--------------------------
					 if(PorgSet_sel<2)
						{
						LabelSel_dis(PorgSet_sel,0);PorgSet_sel++;
						LabelSel_dis(PorgSet_sel,1);
						}
							break;
				case PROG_DIVIDE_MODE://�ȷ� ��--------------------------
				case TEACH_DIVIDE_MODE://�ȷ� ��--------------------------
					 if(PorgSet_sel<1)
						{
						DivideSel_dis(PorgSet_sel,0);PorgSet_sel++;
						DivideSel_dis(PorgSet_sel,1);
						}
							break;
				case PROG_PRO_MODE:    //����ѡ��----------------------
				case TEACH_PRO_MODE:    //����ѡ��----------------------
					if(InputTouch_flag==0)  //	 �� ���������� ��
						{
						  if(Pro_num>=MAIX_PROG)//���ص�һ�� pro
							  {
							  Pro_num=1;
							  CursorMov_dis(cursor_temp,0);//���
							  cursor_temp=0;
							  CursorMov_dis(cursor_temp,1);//
							  Prog_1page_dis(Pro_num, 0);//===����---������ʾ
							  }
						  else
							  {
							  Pro_num++;
							  if(cursor_temp<(PAGE2_KNIFE-1))
								 {
								 CursorMov_dis(cursor_temp,0);//���
								 cursor_temp++;
								 CursorMov_dis(cursor_temp,1);//
								 }
							  else// ��һҳ
								 {
								 CursorMov_dis(cursor_temp,0);//���
								 cursor_temp=0;
								 CursorMov_dis(cursor_temp,1);//
								 Prog_1page_dis(Pro_num, 0);//===����---������ʾ
								 }
							  }
						}
						     break;
				case AUTO_TOOLS_MODE://  ��������  ����
				case SELF_TOOLS_MODE://  ��������  ����
				case MANUAL_TOOLS_MODE:// �ֶ� ����ģʽ
					if(InputTouch_flag==0)  //	 �� ���������� ��
						{
						if((MotorType>=MOTOR_DC_SERVO)&&(MotorType<=MOTOR_DC670_SERVO_ZHU))
							{
							if(PramSel_Page<1)	//page 1
								{
								if(Para_sel<9)
									{
									ParameterPage_dis(Para_sel++, 0);
									ParameterPage_dis(Para_sel, 1);
									}
								else
									{
									PramSel_Page++;
									ToolsPage2_dis(); //���� page2
									}
								}
							else	//page 2
								{
								if(Para2_sel<4)
									{
									ParameterPage2_dis(Para2_sel++, 0);
									ParameterPage2_dis(Para2_sel, 1);
									}
								}
							}
						else if(MotorType==MOTOR_AC_SERVO)
							{
							if(PramSel_Page<1)	//page 1
								{
								if(Para_sel<8)
									{
									ParameterPage_dis(Para_sel++, 0);
									ParameterPage_dis(Para_sel, 1);
									}
								else
									{
									PramSel_Page++;
									ToolsPage2_dis(); //���� page2
									}
								}
							else	//page 2
								{
								if(Para2_sel<4)
									{
									ParameterPage2_dis(Para2_sel++, 0);
									ParameterPage2_dis(Para2_sel, 1);
									}
								
								}
							}
						else
							{
							if(PramSel_Page<1)	//page 1
								{
								if(Para_sel<8)
									{
									ParameterPage_dis(Para_sel++, 0);
									ParameterPage_dis(Para_sel, 1);
									}
								else
									{
									PramSel_Page++;
									ToolsPage2_dis(); //���� page2
									}
								}
							else	//page 2
								{
								if(Para2_sel<4)
									{
									ParameterPage2_dis(Para2_sel++, 0);
									ParameterPage2_dis(Para2_sel, 1);
									}
								
								}
							}
						}
					else
						{
						if(Para_sel<6)
							{
							ParameterPage_dis(Para_sel++, 0);
							ParameterPage_dis(Para_sel, 1);
							}
						}
							break;
				case MANUAL_SERVO_C_MODE:// �ֶ�ֱ���ŷ� C ���� 
					 if(InputTouch_flag==0)  //	 �� ���������� ��
						{
						if(Para_sel<7)
							{
							ServoParameter_dis(Para_sel++, 0);
							ServoParameter_dis(Para_sel, 1);
							}
						}
					else
						{
						if(Para_sel<6)
							{
							ServoParameter_dis(Para_sel++, 0);
							ServoParameter_dis(Para_sel, 1);
							}
						}
						     break;
				case MANUAL_CLOCK_MODE: //�ֶ� ʱ��ģʽ	
					 if(Para_sel<4)
						{
						TimeSetSel_dis(Para_sel++, 0);
						TimeSetSel_dis(Para_sel, 1);
						}
						     break;
				case MANUAL_PULSE_MODE://�ֶ� ���嵱��	
					 if(Para_sel<11)
						{
						SelPulseDegree_dis(Para_sel++, 0); //�����趨
						SelPulseDegree_dis(Para_sel, 1);
						}
							break;
				case MANUAL_PASS_MODE: //�ֶ� ��������
					 if(PassModeOk_flag==1)
						{
						if(Para_sel<1)
							{
							PassDaysSet_dis(Para_sel++, 0); //����
							PassDaysSet_dis(Para_sel, 1); //����
							}
						}
						break;
				}			
			 }
		 
		  } 
		else
		  {
		  if(Board_TestMod==TEST_HELP)
			 {
			 if(Manual_page<1)        //��һҳ  ����
				{
				Manual_page++;
				Comment_dis_page(Manual_page);
				}
			 }
		  }
  	     break;         
	case DENGJU_KEY_CODE:  //���ϼ�ͷ����**************�Ϸ�ҳ
		if(WorkStart_flag==1)
		  {
		  if(Run_flag==0)
			 {
			switch(WorkMode)
				{
				case PROG_MODE://��̻�����
				case TEACH_MODE://ʾ�̻�����
				case AUTO_MODE://�Զ���������
				case AUTO_PLUS_MODE:  //F3++
				case AUTO_MINUS_MODE:// F4--
				case SELF_CUT_MODE://�Ե���������
				case SELF_PLUS_MODE:  //�Ե�F3++
				case SELF_MINUS_MODE://�Ե� F4--
					if(Knife_order>1)
						{
						Knife_order--;
						if(cursor_row>0)
							{
							CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
							OneKnifeDataSel_dis(Knife_order+1, cursor_row,0);  //һ������ ������ʾ
							cursor_row--;
							CursorMov_dis(cursor_row, 1);//��ɫ���������ʾ
							OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //һ������ ������ʾ
							}
						else  //ҳü
							{
							Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
							}	
						}
					else     //ָ�� ���һ��
						{
						Knife_order=Knife_sum;
						if(Knife_order>PAGE_KNIFE)
							{
							Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
							CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
							cursor_row=0;
							CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ  �ڿ�ͷ
							}
						else
							{
							CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
							OneKnifeDataSel_dis(1, cursor_row,0);  //һ������ ������ʾ
							cursor_row=Knife_order-1;
							CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ  �ڿ�ͷ
							OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //һ������ ������ʾ
							}
						}
					if(Knife_order<=Knife_sum)
						StepOrder_dis(Knife_order);//�������
					PromptNum_dis();//���뷶Χ
					PromptDis_flag=1;
						 break;
				case PROG_LABEL_MODE://��ǩ ��--------------------------
				case TEACH_LABEL_MODE://��ǩ ��--------------------------
					 if(PorgSet_sel>0)
						{
						LabelSel_dis(PorgSet_sel,0);PorgSet_sel--;
						LabelSel_dis(PorgSet_sel,1);
						}
							break;
				case PROG_DIVIDE_MODE://�ȷ� ��--------------------------
				case TEACH_DIVIDE_MODE://�ȷ� ��--------------------------
					 if(PorgSet_sel>0)
						{
						DivideSel_dis(PorgSet_sel,0);PorgSet_sel--;
						DivideSel_dis(PorgSet_sel,1);
						}
							break;
				case PROG_PRO_MODE:    //����ѡ��----------------------
				case TEACH_PRO_MODE:    //����ѡ��----------------------
					if(InputTouch_flag==0)  //	 �� ���������� ��
						{
						  if(Pro_num<2)//������� pro
							  {
							  Pro_num=MAIX_PROG;
							  CursorMov_dis(cursor_temp,0);//���
							  cursor_temp=MAIX_PROG%PAGE2_KNIFE;
							  if(cursor_temp<1)
								 cursor_temp=PAGE2_KNIFE;
							  cursor_temp--;
							  CursorMov_dis(cursor_temp,1);//
							  Prog_1page_dis(Pro_num-cursor_temp, 0);//===����---������ʾ
							  }
						  else
							  {
							  Pro_num--;
							  if(cursor_temp>0)//
								 {
								 CursorMov_dis(cursor_temp,0);//���
								 cursor_temp--;
								 CursorMov_dis(cursor_temp,1);//
								 }
							  else//��һҳ
								 {
								 CursorMov_dis(cursor_temp,0);//���
								 cursor_temp=PAGE2_KNIFE-1;
								 CursorMov_dis(cursor_temp,1);//
								 Prog_1page_dis(Pro_num-(PAGE2_KNIFE-1), 0);//===����---������ʾ
								 }
							  }
						}	  
						     break;
				case AUTO_TOOLS_MODE://  ��������  ����
				case SELF_TOOLS_MODE://  ��������  ����
				case MANUAL_TOOLS_MODE:// �ֶ� ����ģʽ
					if(PramSel_Page<1)	//page 1
						{
						if(Para_sel>0)
							{
							if(InputTouch_flag==0)  //	 �� ���������� ��
								{
								ParameterPage_dis(Para_sel--, 0);
								ParameterPage_dis(Para_sel, 1);	
								}
							else
								{
								if(Para_sel>6)
									Para_sel--;
								else 
									ParameterPage_dis(Para_sel--, 0);
								if(Para_sel<7)
									ParameterPage_dis(Para_sel, 1);	
								}
							}	
						}
					else	//page 2
						{
						if(Para2_sel>0)
							{
							if(InputTouch_flag==0)  //	 �� ���������� ��
								{
								ParameterPage2_dis(Para2_sel--, 0);
								ParameterPage2_dis(Para2_sel, 1);	
								}
							else
								{
								if(Para2_sel>6)
									Para2_sel--;
								else 
									ParameterPage2_dis(Para2_sel--, 0);
								if(Para2_sel<7)
									ParameterPage2_dis(Para2_sel, 1);	
								}
							}
						else 
							{
							if(InputTouch_flag==0)  //	 �� ���������� ��
								{
								PramSel_Page--;	
								ToolsPage1_dis(); //���� page1
								}
							}
						}
							 break;
				case MANUAL_SERVO_C_MODE:// �ֶ�ֱ���ŷ� C ���� 
					if(Para_sel>0)
						{
						if(InputTouch_flag==0)  //	 �� ���������� ��
							{
							ServoParameter_dis(Para_sel--, 0);
							ServoParameter_dis(Para_sel, 1);	
							}
						else
							{
							if(Para_sel>6)
								Para_sel--;
							else 
								ServoParameter_dis(Para_sel--, 0);
							if(Para_sel<7)
								ServoParameter_dis(Para_sel, 1);	
							}
						}
						     break;
				case MANUAL_CLOCK_MODE: //�ֶ� ʱ��ģʽ	
					if(Para_sel>0)
						{
						TimeSetSel_dis(Para_sel--, 0);
						TimeSetSel_dis(Para_sel, 1);
						}
							break;
				case MANUAL_PULSE_MODE://�ֶ� ���嵱��	
					if(Para_sel>0)
						{
						SelPulseDegree_dis(Para_sel--, 0); //�����趨
						SelPulseDegree_dis(Para_sel, 1);
						}
							break;
				case MANUAL_PASS_MODE: //�ֶ� ��������
					if(PassModeOk_flag==1)
						{
						if(Para_sel>0)
							{
							PassDaysSet_dis(Para_sel--, 0); //����
							PassDaysSet_dis(Para_sel, 1); //����
							}
						}
						break;				
				}			
			 }
		   else
			 {
									
			 }
		  }        
		else
		  {
		  if(Board_TestMod==TEST_HELP)
			 {
			 if(Manual_page>0)        //��һҳ  ����
				{
				Manual_page--;
				Comment_dis_page(Manual_page);
				}
			 }
		  }
  	     break; 
	
             
    case  ONE_KEY_CODE + YES_KEY_CODE://F ���ܰ��� +  ����8  **************
        
           
             break;    
    case  ONE_KEY_CODE + OPTION_KEY_CODE://F ���ܰ��� +  ��-/����  **************
                
           break;       
          
    case ONE_KEY_CODE +  REV_KEY_CODE://F ���ܰ��� +  ��+/*��  **************
          
          break;
    case ONE_KEY_CODE + ADD_KEY_CODE://F ���ܰ��� +  ��.��  **************
           
          break;  
	case ONE_KEY_CODE+MOVE_KEY_CODE:		// F ���ܰ��� +2******************ע��ͼ��
          
  	         break;     
    case ONE_KEY_CODE +DELETE_KEY_CODE:		//F ���ܰ��� + 3   ѡ��һ������***************** 
           
             break;
    case     ONE_KEY_CODE+NINE_KEY_CODE:		//F ���ܰ��� +  ����1************
               
             break;
	case     ONE_KEY_CODE+ SUB_KEY_CODE:    //F ���ܰ��� +  ����9************
             
             break;   
    case     ONE_KEY_CODE+EIGHT_KEY_CODE :   //F ���ܰ��� +  ����4************
             
          
            break;
    case     ONE_KEY_CODE+ PROG_KEY_CODE: //F ���ܰ��� +  ����0************
          
            break;
    case     ONE_KEY_CODE+NO_KEY_CODE :   //F ���ܰ��� +  ����5  **************
            
          break;
    case     ONE_KEY_CODE+ SEVEN_KEY_CODE:  //F ���ܰ��� +  ����7  **************
           
          break;
	case DENGJU_KEY_CODE+NINE_KEY_CODE://���ϼ�ͷ + 1  ************
		
		break; 
    case DENGJU_KEY_CODE+INSERT_KEY_CODE://���ϼ�ͷ + 6  ************    
                
		break;
	case 0xffff000d:  //F0CUT_TOUCH_CODE		F0 ���� ����־ ��ť
			if(WorkStart_flag==1)
				{
				if(Run_flag==0)
				  {
				  if(InputTouch_flag==0)
					 {
					  switch(WorkMode)
						  {
						  // case PROG_MODE://��̻�����
						  // case TEACH_MODE://ʾ�̻�����
							case  AUTO_MODE://�Զ���������
								knife=2;
								
								if(Pro_data.pro_num<=(PROG_GROPU1+1))  //ǰ301��prog
								   {
								   offset=PROG_BYTES1*(Pro_data.pro_num-1);
								   }
								else//��  199
								   {
								   offset=PROG_BYTES1*PROG_GROPU1+(Pro_data.pro_num-PROG_GROPU1-1)*PROG_BYTES2;
								   }
								pbuf=(pInt8U)(K_SIZE_sdram+offset+2+(knife-1)*5+4);//�������ַ
								
							//----  �������е�  ��־-------------
								pKnife_data=(pInt8U)&OneKnife_data;
								
								GetOneKnife_datas(Pro_data.pro_num, knife-1, pKnife_data);//
								while(knife<=Knife_sum)
									{
									if(AllKnifeSet_flag==0)//�趨 ���е���־
										{
										
										InputSize=OneKnife_data.size;
										GetOneKnife_datas(Pro_data.pro_num, knife, pKnife_data);//
										if((OneKnife_data.size<InputSize)&&(OneKnife_data.size>0))//С�� ǰһ��
											{
											if(OneKnife_data.k_flag!=KNIFE_FLAG) 
												{
												//OneKnife_data.k_flag=KNIFE_FLAG;  
												//SaveOneKnife_datas(Pro_data.pro_num,knife , pKnife_data);//����һ������
												//*pbuf=*(pKnife_data+4);
												*pbuf=KNIFE_FLAG;
												}
											}
										pbuf+=5;
										}
									else	 //���  ���е���־
										{
										GetOneKnife_datas(Pro_data.pro_num, knife, pKnife_data);//
										if(OneKnife_data.k_flag==KNIFE_FLAG) 
											{
											//OneKnife_data.k_flag=0;// ��� ��־
											//SaveOneKnife_datas(Pro_data.pro_num,knife , pKnife_data);//����һ������
											*pbuf=0;
											}
										pbuf+=5;	
										}
									knife_set_flag=1;	
											
									knife++;	
									}
									
									
									
									if(AllKnifeSet_flag==0)
										AllKnifeSet_flag=1;
									else
										AllKnifeSet_flag=0;
										
								if(knife_set_flag==1)   //����  ��ʾ---------
									{
									SaveBuf_datas(Pro_data.pro_num, 1, Knife_sum );//����
									//------------���ص�һ��
									ClrInput_function();//���� ����� 
									CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
									cursor_row=0;
									CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
									Knife_order=1;//
									Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
									if(Knife_order<=Knife_sum)
										StepOrder_dis(Knife_order);//�������	
									//PromptNum_dis();//���뷶Χ
									//PromptDis_flag=1;	
									}
								// F5Button_dis( );  //F5 һ�� �� ��� ��ť
								F0Button_dis(AllKnifeSet_flag);  //F0 ���� �� ��� ��ť/
									break;
						  }
					 }
				  }
				}
		break;
	case 0xffff000e:  //F5CUT_TOUCH_CODE		F5 1��  ����־ ��ť	
			if(WorkStart_flag==1)
				{
				if(Run_flag==0)
				  {
				  if(InputTouch_flag==0)
					 {
					  switch(WorkMode)
						  {
						  case PROG_MODE://��̻�����
						  // case TEACH_MODE://ʾ�̻�����
						  case AUTO_MODE://�Զ���������
							//----��������----------------
							 if(Knife_order>1)
								{
								 pKnife_data=(pInt8U)&OneKnife_data;
								 GetOneKnife_datas(Pro_data.pro_num, Knife_order-1, pKnife_data);//
								 InputSize=OneKnife_data.size;
								 GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);//
								 if((OneKnife_data.size<InputSize)&&(OneKnife_data.size>0))//С�� ǰһ��
									{
									if(OneKnife_data.k_flag!=KNIFE_FLAG) //
										{
										OneKnife_data.k_flag=KNIFE_FLAG;//  �趨 ����־
										}
									else
										{
										OneKnife_data.k_flag=0;// ��� ��־
										}
									PushFlag_dis(cursor_row,OneKnife_data.k_flag); //��ʾ----
									SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//����һ������
									PromptNum_dis();//���뷶Χ
									PromptDis_flag=1;
									F5Button_dis(OneKnife_data.k_flag);  //F5 һ�� �� ��� ��ť
									}
								 else
									{
									PromptDis_flag=0;
									GLCD_SetWindow_Fill(REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
									switch(Language)
										{
										case CHN_HAN:
											Printf24("�˵���־�趨��Ч!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
										case ENGLISH:
											Printf24("Invalid Mark!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
										}
									}
									
								}
							 else
								{
								PromptDis_flag=0;
								GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
								switch(Language)
										{
										case CHN_HAN:
											Printf24("�˵���־�趨��Ч!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
										case ENGLISH:
											Printf24("Invalid Mark!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												break;
										}
								}
								break;
						  }
					 }
				  }
				else//������
				  {
				  
				  }
				}
		break;
    }            
	
}

int KeyCheck(void)
{
int i;
int  c;

KEY_COL1_CLR();
KEY_COL2_CLR();
KEY_COL3_CLR();
KEY_COL4_CLR();
KEY_COL5_CLR();
//KEY_COL6_CLR();
i=500;
while(i--);
	// // GPIO_SetBit(GPIOI, KEY_COL6);
			// // GPIO_SetBit(GPIOH, BIT11);
	// // GPIO_SetBit(GPIOH, BIT12);
	// // GPIO_SetBit(GPIOH, BIT13);
	// // GPIO_SetBit(GPIOH, BIT14);
	// // GPIO_SetBit(GPIOH, BIT15);
	
c=(~GPIO_ReadPort(KEYIO))&KEY_CODE_MASK;
if(KEY_COL6_IN()==0)
	c|=0x1;
KEY_COL1_SET();
KEY_COL2_SET();
KEY_COL3_SET();
KEY_COL4_SET();
KEY_COL5_SET();
//KEY_COL6_SET();
return(c);
}

void KeyReadCode(void)
{
	int i;
int keycodetemp;
KeyCode=0;
	i=500;
while(i--);
KEY_COL1_CLR();
i=500;
while(i--);
keycodetemp=(~GPIO_ReadPort(KEYIO))&KEY_CODE_MASK;
if(KEY_COL6_IN()==0)
	keycodetemp|=0x1;
if(keycodetemp!=0)
	KeyCode=keycodetemp|0x4000000;
KEY_COL1_SET();
i=500;
while(i--);
KEY_COL2_CLR();
i=500;
while(i--);
keycodetemp=(~GPIO_ReadPort(KEYIO))&KEY_CODE_MASK;
if(KEY_COL6_IN()==0)
	keycodetemp|=0x1;
if(keycodetemp!=0)
	KeyCode+=(keycodetemp|0x8000000);
	//KeyCode=keycodetemp|0x10000000;
KEY_COL2_SET();
i=500;
while(i--);
KEY_COL3_CLR();
i=500;
while(i--);
keycodetemp=(~GPIO_ReadPort(KEYIO))&KEY_CODE_MASK;
if(KEY_COL6_IN()==0)
	keycodetemp|=0x1;
if(keycodetemp!=0)
	KeyCode+=(keycodetemp|0x10000000);
	//  KeyCode=keycodetemp|0x20000000;
KEY_COL3_SET();
i=500;
while(i--);
KEY_COL4_CLR();
i=500;
while(i--);
keycodetemp=(~GPIO_ReadPort(KEYIO))&KEY_CODE_MASK;
if(KEY_COL6_IN()==0)
	keycodetemp|=0x1;
if(keycodetemp!=0)
	KeyCode+=(keycodetemp|0x20000000);
//		KeyCode=keycodetemp|0x40000000;
KEY_COL4_SET();
i=500;
while(i--);
KEY_COL5_CLR();
i=500;
while(i--);
keycodetemp=(~GPIO_ReadPort(KEYIO))&KEY_CODE_MASK;
if(KEY_COL6_IN()==0)
	keycodetemp|=0x1;
if(keycodetemp!=0)
	KeyCode+=(keycodetemp|0x40000000);
//	  KeyCode=keycodetemp|0x80000000;
KEY_COL5_SET();
i=500;
while(i--);
/*
KEY_COL6_CLR();
i=500;
while(i--);
keycodetemp=(~GPIO_ReadPort(KEYIO))&KEY_CODE_MASK;
if(keycodetemp!=0)
	KeyCode+=(keycodetemp|0x80000000);
//	  KeyCode=keycodetemp|0x80000000;
KEY_COL6_SET();
*/
keyChangeCode();
}


void keyChangeCode(void)
{
Int32U ktemp;
Int16U kctemp;

Int32U kbuf;

ktemp=KeyCode&0xff000000;
kctemp=KeyCode&0xF801;

KeyCode=0;
/*
	if(ktemp&0x04000000)
	{
	//case 0x04000000:	//��һ��

				if(kctemp&0x8000)
				KeyCode+=RETURN_KEY_CODE;
				else

				if(kctemp& 0x4000)//://�ڶ���
				KeyCode+=READ_KEY_CODE;
				else
				if(kctemp& 0x2000)//://������
					KeyCode+=AUTO_KEY_CODE;
					else
				if(kctemp& 0x1000)//://������
				KeyCode+=FIVE_KEY_CODE;
				else

				if(kctemp& 0x0800)//://������
				KeyCode+=ZERO_KEY_CODE;
				else

				if(kctemp& 0x0001)//:	//������
				KeyCode+=MANUAL_KEY_CODE;

	}

		if(ktemp&0x08000000)
	{
	//case 0x08000000:	//�ڶ���

				if(kctemp&0x8000)////��һ��
				KeyCode+=NEXTKNIFE_KEY_CODE;
				else
				
				if(kctemp&0x4000)////�ڶ���
				KeyCode+=ADD_KEY_CODE;
				else
					
				if(kctemp&0x2000)////������
					KeyCode+=PROG_KEY_CODE;
					else
					
				if(kctemp&0x1000)////������
				KeyCode+=SIX_KEY_CODE;
				else
					
				if(kctemp&0x0800)////������
				KeyCode+=ONE_KEY_CODE;
					else
				if(kctemp&0x0001)//	//������
				KeyCode+=UP_KEY_CODE;

	//	break;
	}

			if(ktemp&0x10000000)
	{
	//case 0x10000000:	//������

				if(kctemp&0x8000)////��һ��
				KeyCode+=ADJUST_KEY_CODE;
				else

				if(kctemp&0x4000)////�ڶ���
				KeyCode+=SUB_KEY_CODE;
				else

				if(kctemp&0x2000)////������
					KeyCode+=YES_KEY_CODE;
					else

				if(kctemp&0x1000)////������
				KeyCode+=SEVEN_KEY_CODE;
				else

				if(kctemp&0x0800)////������
				KeyCode+=TWO_KEY_CODE;
				else

				if(kctemp&0x0001)//	//������
				KeyCode+=DOWN_KEY_CODE;


		//break;
	}

				if(ktemp&0x20000000)
	{
	//case 0x20000000:	//������

				if(kctemp&0x8000)////��һ��
				KeyCode+=OPTION_KEY_CODE;
				else

				if(kctemp&0x4000)////�ڶ���
				KeyCode+=INSERT_KEY_CODE;
				else

				if(kctemp&0x2000)////������
					KeyCode+=NO_KEY_CODE;
					else

				if(kctemp&0x1000)////������
				KeyCode+=EIGHT_KEY_CODE;
				else

				if(kctemp&0x0800)////������
				KeyCode+=THREE_KEY_CODE;
				else

				if(kctemp&0x0001)//	//������
				KeyCode+=DENGFENG_KEY_CODE;

	//	break;
	}

				if(ktemp&0x40000000)
	{
					//case 0x40000000:	//������

				if(kctemp&0x8000)////��һ��
				KeyCode+=REV_KEY_CODE;
				else
				if(kctemp&0x4000)////�ڶ���
				KeyCode+=DELETE_KEY_CODE;
				else

				if(kctemp&0x2000)////������
					KeyCode+=MOVE_KEY_CODE;
					else

				if(kctemp&0x1000)////������
				KeyCode+=NINE_KEY_CODE;
				else

				if(kctemp&0x0800)////������
				KeyCode+=FOUR_KEY_CODE;
				else

				if(kctemp&0x0001)//	//������
				KeyCode+=DENGJU_KEY_CODE;

//		break;
	}

	*/


switch(ktemp)
	{
	case 0x04000000:	//��һ��
		switch(kctemp)
				{
				case 0x8000://��һ��
				KeyCode=RETURN_KEY_CODE;
					break;
				case 0x4000://�ڶ���
				KeyCode=READ_KEY_CODE;
					break;
				case 0x2000://������
					KeyCode=AUTO_KEY_CODE;
					break;
				case 0x1000://������
				KeyCode=FIVE_KEY_CODE;
					break;
				case 0x0800://������
				KeyCode=ZERO_KEY_CODE;
					break;
				case 0x0001:	//������
				KeyCode=MANUAL_KEY_CODE;
					break;				
				}
		break;

	case 0x08000000:	//�ڶ���
		switch(kctemp)
				{
				case 0x8000://��һ��
				KeyCode=NEXTKNIFE_KEY_CODE;
					break;
				case 0x4000://�ڶ���
				KeyCode=ADD_KEY_CODE;
					break;
				case 0x2000://������
					KeyCode=PROG_KEY_CODE;
					break;
				case 0x1000://������
				KeyCode=SIX_KEY_CODE;
					break;
				case 0x0800://������
				KeyCode=ONE_KEY_CODE;
					break;
				case 0x0001:	//������
				KeyCode=UP_KEY_CODE;
					break;		
					
				case 0x0800+0x2000://��ϼ�
					KeyCode=ONE_KEY_CODE+ PROG_KEY_CODE; //F ���ܰ��� +  ����0************ ���� ����־
				break;
				}
		break;

	case 0x10000000:	//������
		switch(kctemp)
				{
				case 0x8000://��һ��
				KeyCode=ADJUST_KEY_CODE;
					break;
				case 0x4000://�ڶ���
				KeyCode=SUB_KEY_CODE;
					break;
				case 0x2000://������
					KeyCode=YES_KEY_CODE;
					break;
				case 0x1000://������
				KeyCode=SEVEN_KEY_CODE;
					break;
				case 0x0800://������
				KeyCode=TWO_KEY_CODE;
					break;
				case 0x0001:	//������
				KeyCode=DOWN_KEY_CODE;
					break;				
				}
		break;

	case 0x20000000:	//������
		switch(kctemp)
				{
				case 0x8000://��һ��
				KeyCode=OPTION_KEY_CODE;
					break;
				case 0x4000://�ڶ���
				KeyCode=INSERT_KEY_CODE;
					break;
				case 0x2000://������
					KeyCode=NO_KEY_CODE;
					break;
				case 0x1000://������
				KeyCode=EIGHT_KEY_CODE;
					break;
				case 0x0800://������
				KeyCode=THREE_KEY_CODE;
					break;
				case 0x0001:	//������
				KeyCode=DENGFENG_KEY_CODE;
					break;				
				}
		break;

	case 0x40000000:	//������
		switch(kctemp)
				{
				case 0x8000://��һ��
				KeyCode=REV_KEY_CODE;
					break;
				case 0x4000://�ڶ���
				KeyCode=DELETE_KEY_CODE;
					break;
				case 0x2000://������
					KeyCode=MOVE_KEY_CODE;
					break;
				case 0x1000://������
				KeyCode=NINE_KEY_CODE;
					break;
				case 0x0800://������
				KeyCode=FOUR_KEY_CODE;
					break;
				case 0x0001:	//������
				KeyCode=DENGJU_KEY_CODE;
					break;		
				case 0x0001+0x2000://��ϼ�
				KeyCode=DENGJU_KEY_CODE+MOVE_KEY_CODE;	//���ϼ�ͷ+2  ���嵱�� �趨	 
				break;

				case 0x0001+0x4000://��ϼ�
					KeyCode=DENGJU_KEY_CODE+DELETE_KEY_CODE;  //	���ϼ�ͷ+3  ��λѡ��
					break;
				case 0x0001+0x1000://��ϼ�
					KeyCode=DENGJU_KEY_CODE+NINE_KEY_CODE;			//���ϼ�ͷ+1  ���嵱�� �趨
				break;
				}
		break;

	case 0x30000000:	//��ϼ�
		switch(kctemp)
				{
				case 0x2001:
					KeyCode=DENGFENG_KEY_CODE+YES_KEY_CODE;//���¼�ͷ+8 ����ģʽ
					break;

				}
		break;
	case 0x08000000+0x40000000:
		switch(kctemp)
				{
				case 0x0800+0x1000:
					 KeyCode=ONE_KEY_CODE+NINE_KEY_CODE;		//F ���ܰ��� + 1 ***********
				break;

				case 0x0800+0x2000:
					  KeyCode=ONE_KEY_CODE+MOVE_KEY_CODE;		// F ���ܰ��� +2************
				break;

				case 0x0800+0x4000:
					KeyCode=ONE_KEY_CODE+DELETE_KEY_CODE;		//F ���ܰ��� + 3 ***********
				break;
			case 0x0800+0x8000:
					KeyCode=ONE_KEY_CODE+REV_KEY_CODE;   //    ***************F���ܰ���+ ��+/*��
			break;

						case 0x0800+0x0001:
					KeyCode=ONE_KEY_CODE+DENGJU_KEY_CODE;  //F+���ϼ�ͷ		----��
			break;				
				}
		break;

	case 0x08000000+0x20000000:
		switch(kctemp)
				{
				case 0x0800+0x1000:
					KeyCode=ONE_KEY_CODE+EIGHT_KEY_CODE;		// F ���ܰ��� +4************	
				break;

				case 0x0800+0x2000:
					  KeyCode=ONE_KEY_CODE+NO_KEY_CODE;		  //F ���ܰ��� + 5 ***********����־
				break;

				case 0x0800+0x4000:
					KeyCode=ONE_KEY_CODE+INSERT_KEY_CODE;   //        F���ܰ���+6 ----------ʾ��ģʽ
				break;
				

				case 0x0800+0x8000:
					KeyCode=ONE_KEY_CODE+OPTION_KEY_CODE;   //    ***************F���ܰ���+ ��-/����
					break;
				
			case 0x0800+0x0001:
				KeyCode=ONE_KEY_CODE+DENGFENG_KEY_CODE;  //F+���¼�ͷ		----��
			break;
				
				}
		break;
/*
		case 0x08000000+0x40000000:
		switch(kctemp)
				{
			case 0x0800+0x8000:
					KeyCode=ONE_KEY_CODE+REV_KEY_CODE;   //    ***************F���ܰ���+ ��+/ *��
			break;

						case 0x0800+0x0001:
					KeyCode=ONE_KEY_CODE+DENGJU_KEY_CODE;  //F+���ϼ�ͷ		----��
			break;
				}

			break;

		case 0x08000000+0x20000000:
		switch(kctemp)
				{
			case 0x0800+0x0001:
				KeyCode=ONE_KEY_CODE+DENGFENG_KEY_CODE;  //F+���¼�ͷ		----��
			break;


				}

			break;
*/
		/*
	
	
	 
	 		
	 
	 
	 
	 
	 
 	

	
	
	
	*/
	}


}


void Key_Enable(unsigned char enb)
{
}

void KeyInit(void)  //���˿ڳ�ʼ��
{
/*
KEY_COL1_DIR_OUT();
KEY_COL2_DIR_OUT();
KEY_COL3_DIR_OUT();
KEY_COL4_DIR_OUT();
KEY_COL5_DIR_OUT();
KEY_COL6_DIR_OUT();
*/
	/***
		GPIO_CloseBit(GPIOI, KEY_COL6);
	GPIO_CloseBit(GPIOH, BIT11);
	GPIO_CloseBit(GPIOH, BIT12);
		GPIO_CloseBit(GPIOH, BIT13);
	GPIO_CloseBit(GPIOH, BIT14);
		GPIO_CloseBit(GPIOH, BIT15);

KEY_COL1_SET();
KEY_COL2_SET();
KEY_COL3_SET();
KEY_COL4_SET();
KEY_COL5_SET();
//KEY_COL6_SET();
	
	GPIO_OpenBit(GPIOI, KEY_COL6, DIR_INPUT, PULL_UP);
	GPIO_SetBit(GPIOI, KEY_COL6);

			GPIO_SetBit(GPIOH, BIT11);
	GPIO_OpenBit(GPIOH, BIT11, DIR_INPUT, PULL_UP);

		GPIO_SetBit(GPIOH, BIT12);
	GPIO_OpenBit(GPIOH, BIT12, DIR_INPUT, PULL_UP);

		GPIO_SetBit(GPIOH, BIT13);
	GPIO_OpenBit(GPIOH, BIT13, DIR_INPUT, PULL_UP);

		GPIO_SetBit(GPIOH, BIT14);
	GPIO_OpenBit(GPIOH, BIT14, DIR_INPUT, PULL_UP);

		GPIO_SetBit(GPIOH, BIT15);
	GPIO_OpenBit(GPIOH, BIT15, DIR_INPUT, PULL_UP);
**/
GPIO_CloseBit(GPIOI, 1);
	GPIO_CloseBit(GPIOI,2);
	GPIO_CloseBit(GPIOI, 3);
	GPIO_CloseBit(GPIOI, 4);
	GPIO_CloseBit(GPIOI, 5);
	GPIO_CloseBit(GPIOI, 6);
	
		GPIO_CloseBit(GPIOI, KEY_COL6);
	
	GPIO_CloseBit(GPIOH, BIT11);
	GPIO_CloseBit(GPIOH, BIT12);
		GPIO_CloseBit(GPIOH, BIT13);
	GPIO_CloseBit(GPIOH, BIT14);
		GPIO_CloseBit(GPIOH, BIT15);

	
KEY_COL1_DIR_OUT();
KEY_COL2_DIR_OUT();
KEY_COL3_DIR_OUT();
KEY_COL4_DIR_OUT();
KEY_COL5_DIR_OUT();
	
////////KEY_COL1_SET();
////////KEY_COL2_SET();
////////KEY_COL3_SET();
////////KEY_COL4_SET();
////////KEY_COL5_SET();
//KEY_COL6_SET();
	
	GPIO_SetBit(GPIOI, KEY_COL6);
	GPIO_OpenBit(GPIOI, KEY_COL6, DIR_INPUT, PULL_UP);
	GPIO_SetBit(GPIOI, KEY_COL6);


	GPIO_SetBit(GPIOH, BIT11);
	GPIO_OpenBit(GPIOH, BIT11, DIR_INPUT, PULL_UP);
	GPIO_SetBit(GPIOH, BIT11);	

		GPIO_SetBit(GPIOH, BIT12);
	GPIO_OpenBit(GPIOH, BIT12, DIR_INPUT, PULL_UP);
	GPIO_SetBit(GPIOH, BIT12);	

		GPIO_SetBit(GPIOH, BIT13);
	GPIO_OpenBit(GPIOH, BIT13, DIR_INPUT, PULL_UP);
	GPIO_SetBit(GPIOH, BIT13);	

		GPIO_SetBit(GPIOH, BIT14);
	GPIO_OpenBit(GPIOH, BIT14, DIR_INPUT, PULL_UP);
	GPIO_SetBit(GPIOH, BIT14);	

		GPIO_SetBit(GPIOH, BIT15);
	GPIO_OpenBit(GPIOH, BIT15, DIR_INPUT, PULL_UP);
	GPIO_SetBit(GPIOH, BIT15);	

	
//KEYIO_DDR&=0xfc1FFFFF;
//PINMODE7&=0xffc00ffff;
}






void ClrInput_function(void)//���� �����
{
for(num_cou=0;num_cou<8;num_cou++)
	 {
		Size_temp[num_cou++]=0;
	 }
num_cou=0; // nn=0;temp=0;
CalcTemp_cou=num_cou;
Dot_flag=0;
GLCD_SetWindow_Fill( SIZE_WINDOW_X+24, SIZE_WINDOW_Y, SIZE_WINDOW_X+120, SIZE_WINDOW_Y+30, 0xfffff, 0xffff);//�ߴ������
}
//************************************************************************************
void SaveOneKnife_datas(Int16U prog,Int16U order,pInt8U pdatas)//����һ������
{
pInt8U pbuf;
Int32U add,sd_add,offset,i;
if(prog<=(PROG_GROPU1+1))  //ǰ301��prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//��  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
sd_add=K_SIZE_sdram+offset+2;//������ buf����ַ
   
pbuf=(pInt8U)&Knife_sum;
add=DATA_SAVE_OFFSET+offset;//������ spi����ַ
//********************�ܵ������  ��  Knife_sum ����
if(Knife_sum_before!=Knife_sum)
	{
	Knife_sum_before=Knife_sum;
	Write_25pe_data(pbuf,     add,      2);
	}
//********************������ ����
pbuf=(pInt8U)(sd_add+(order-1)*5);//������ buf��ַ
add=add+2+(order-1)*5;
for(i=0;i<5;i++)
   {
   *(pbuf+i)=*(pdatas+i);      //���� ����
   }
Write_25pe_data(pbuf,     add,      5);
}

void GetOneKnife_datas(Int16U prog,Int16U order ,pInt8U pdatas)//��sdram����һ������
{
pInt8U pbuf;
Int8U i;
Int32U sd_add,offset;
if(prog<=(PROG_GROPU1+1))  //ǰ301��prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//��  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
sd_add=K_SIZE_sdram+offset+2;//������ buf����ַ
pbuf=(pInt8U)(sd_add+(order-1)*5); //������ buf��ַ
for(i=0;i<5;i++)
   {
   *pdatas++=*pbuf++;
   }
}
void PutOneKnife_datas(Int16U prog,Int16U order ,pInt8U pdatas)//��sdram����һ������
{
pInt8U pbuf;
Int32U add,sd_add,offset,i;
if(prog<=(PROG_GROPU1+1))  //ǰ301��prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//��  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
sd_add=K_SIZE_sdram+offset+2;//������ buf����ַ
   
pbuf=(pInt8U)(sd_add+(order-1)*5);//������ buf��ַ
for(i=0;i<5;i++)
   {
   *pbuf++=*pdatas++;      //���� ����
   }
}

void SaveBuf_datas(Int16U prog,Int16U order1, Int16U order2)//���� order1�� order2  buf�������ݵ�spi
{
pInt8U pbuf,psave;
Int32U add,sd_add,offset,n;
if(prog<=(PROG_GROPU1+1))  //ǰ301��prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//��  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
sd_add=K_SIZE_sdram+offset+2;//������ buf����ַ
pbuf=(pInt8U)(sd_add+(order1-1)*5);
add=DATA_SAVE_OFFSET+offset+2;//������ spi����ַ
add=add+(order1-1)*5;
if(order2>=order1)//
   {
   n=(order2-order1+1)*5;
   Write_25pe_data(pbuf,     add,      n);
   }
}

void ClrBuf_datas(Int16U prog,Int16U order1, Int16U order2)//���� order1�� order2  buf��������   
{
pInt8U pbuf;
Int32U n,lenth,sd_add,offset;
if(prog<=(PROG_GROPU1+1))  //ǰ301��prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//��  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
sd_add=K_SIZE_sdram+offset+2;//������ buf����ַ
pbuf=(pInt8U)(sd_add+(order1-1)*5);
lenth=(order2-order1+1)*5;
for(n=0;n<lenth;n++)
   {
   *pbuf++=0;
   }
}


//-----���� ���ִ�ȡ
void ReadPro_perameter(pInt8U pdata)//��ȡ ���� �� ����
{
Int8U d;
Int32U add;
add=PRO_NUM_25PEADD;//��ַ

FastRead_Datas_Start(add);
for(d=0;d<4;d++)
   {
   *pdata++=ReadFlash_Datas();
   }
FlashChip_Dis;
}

void SavePro_data(pInt8U pdata)//���� ���� �� ����
{
Int32U add;
add=PRO_NUM_25PEADD;//��ַ

Write_25pe_data(pdata, add, 4);
}

void GetKnife_sum(Int16U prog)//��һ������� ����
{
Int32U offset;
pInt8U pbuf,pdata;
Int16U max_sum;
Int16U sum_temp;
if(prog<=(PROG_GROPU1+1))  //ǰ301��prog
   {
   offset=PROG_BYTES1*(prog-1);
   max_sum=MAIX_KNIFE1;
   }
else//��  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   max_sum=MAIX_KNIFE2;
   }
pbuf=(pInt8U)(K_SIZE_sdram+offset);//�������ַ
pdata=(pInt8U)&sum_temp;
*pdata=*pbuf;
*(pdata+1)=*(pbuf+1);
if((sum_temp<1)||(sum_temp>max_sum))
   {
   Knife_sum=1;
   *pbuf++=*pdata++;
   *pbuf=*pdata;
   }
else
	{
	*pdata++=*pbuf++;
	*pdata=*pbuf;
	Knife_sum=sum_temp;
	}
   
}

void SaveKnife_sum(Int16U prog)//����һ������� ����
{
Int32U offset,add;
pInt8U pbuf,pdata;
if(prog<=(PROG_GROPU1+1))  //ǰ301��prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//��  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
pbuf=(pInt8U)(K_SIZE_sdram+offset);//�������ַ
pdata=(pInt8U)&Knife_sum;
*pbuf=*pdata++;
*(pbuf+1)=*pdata;
add=DATA_SAVE_OFFSET+offset;

Write_25pe_data((pInt8U)pbuf, add, 2);
}

void ReadOnePro_datas(Int16U pro_order) //spi��һ�� �������� �� buf
{
pInt8U pbuf;
Int32U i;
Int32U offset,add;
if(pro_order<=(PROG_GROPU1+1))  //ǰ301��prog
   {
   offset=PROG_BYTES1*(pro_order-1);
   }
else//��  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(pro_order-PROG_GROPU1-1)*PROG_BYTES2;
   }
pbuf=(pInt8U)(K_SIZE_sdram+offset);//һ��pro�� buf����ַ
add=DATA_SAVE_OFFSET+offset;
FastRead_Datas_Start(add);
for(i=0;i<Knife_sum*5+2;i++)
   {
   *pbuf++=ReadFlash_Datas();
   }
FlashChip_Dis;
}

void ReadAllPro_head(void)// �����г���ͷ+��һ��  �� buf
{
pInt8U pbuf,pdata;
Int32U add,cou,i;
Int16U k_sum_temp=1;
Int16U max_sum;
cou=1;

pdata=(pInt8U)&k_sum_temp;
pbuf=(pInt8U)K_SIZE_sdram;

add=DATA_SAVE_OFFSET;
while(cou<=MAIX_PROG)
	{
	FastRead_Datas_Start(add);
	for(i=0;i<5+2;i++)
	   {
		*(pbuf+i)=ReadFlash_Datas();
	   }
	FlashChip_Dis;
	
	if(cou<=PROG_GROPU1)//ǰ 300��pro
	   {
	   max_sum=MAIX_KNIFE1;//999
	   }
	else
	   {
	   max_sum=MAIX_KNIFE2;//399
	   } 
	
	*pdata=*pbuf;
	*(pdata+1)=*(pbuf+1);
	if((k_sum_temp<1)||(k_sum_temp>max_sum))//δ��ʼ��
	   {
	   k_sum_temp=1;
	   *pbuf=*pdata;
	   *(pbuf+1)=*(pdata+1);
	   for(i=2;i<7;i++)
	      {
		  *(pbuf+i)=0;
	      }
	   Write_25pe_data(pbuf, add, 7);
	   }
	
	cou++;   
	if(cou>PROG_GROPU1+1)
	   {
	   pbuf=(pInt8U)(K_SIZE_sdram+PROG_BYTES1*PROG_GROPU1+PROG_BYTES2*(cou-PROG_GROPU1-1));
       add=DATA_SAVE_OFFSET+PROG_BYTES1*PROG_GROPU1+PROG_BYTES2*(cou-PROG_GROPU1-1);
	   }
	else
	   {
	   pbuf=(pInt8U)(K_SIZE_sdram+PROG_BYTES1*(cou-1));
       add=DATA_SAVE_OFFSET+PROG_BYTES1*(cou-1);
	   }
	 
	}
}


void ReadDatas_to_sdram(void)///�����ݶ���sdram
{
Int32U add,d,sum;
KNIFE_DATA Knife_datas;
pInt8U pdata;
//pdata=(pInt8U)K_SIZE_sdram;
add=DATA_SAVE_OFFSET;
/*
FastRead_Datas_Start(add);
for(d=0;d<20;d++)
   {
   *pdata++=ReadFlash_Datas();
   }
FlashChip_Dis;
//-------------------------------------��ʼ�� �ж�
Pro_data.pro_num=1;//��ǰ���� ��1
pdata=(pInt8U)&Knife_datas;
GetOneKnife_datas( 1 , pdata);//ȡ����һ�� 
*/
pdata=(pInt8U)&Pro_data;
ReadPro_perameter(pdata);  //��ȡ ���� 
//************��ǰpro ����
 if(Pro_data.pro_num<=PROG_GROPU1)//ǰ 300��pro
   {
   MAIX_Knife=MAIX_KNIFE1;//999
   }
 else
   {
   MAIX_Knife=MAIX_KNIFE2;//399
   } 

if((Pro_data.pro_sum<1)||(Pro_data.pro_sum>500))//������ ��Ч�����ʼ��
  {
  Pro_data.pro_num=1;//��ǰ���� ��1
  Pro_data.pro_sum=1;//���� ����
  Knife_sum=1;//�� ����
  pdata=(pInt8U)&Pro_data;
  SavePro_data(pdata);
  
  ClrBuf_datas(Pro_data.pro_num, 1,MAIX_Knife);  //���� ������buf
  pdata=(pInt8U)K_SIZE_sdram;
  *pdata++=1;            //���� 1
  *pdata++=0;
  /*
  for(d=0;d<400;d++)          //�������� ����
     {
     pdata=(pInt8U)K_SIZE_sdram;
	 Write_25pe_data(pdata, add, PROG_BYTES1);
	 add+=PROG_BYTES1;
	 }*/
  
  /*
  Chip_Erase();
  volatile Int32U tt=10000;
  while(tt--);*/
  }
else //  ��Ч ��ȡpro
  {
  //Knife_sum=1;
  // Pro_data.pro_num=4;
  //Pro_data.pro_sum=2;
  ReadAllPro_head();  ///������ ���� ��head
  GetKnife_sum(Pro_data.pro_num); //��ȡǰ���� ����
 // ReadOnePro_datas(Pro_data.pro_num);//��ȡ ��ǰpro
  ClrBuf_datas(Pro_data.pro_num, 1,MAIX_Knife);  //���� ������buf
  
  //Knife_sum=100;
  ReadOnePro_datas(Pro_data.pro_num);//��ȡ һ��pro
  
  CheckKnifeSum_exec();  //--------------�ܵ���    �˶�
  Knife_sum_before=Knife_sum;
  }
 
   
}





void Prog_1page_dis(Int16U prog,Int16U line)//һҳ������ʾ
{
//pInt8U pbuf;
KNIFE_DATA Knife_datas;
Int16U x,y,back_color=0xef9f;

while(line<PAGE2_KNIFE)
	{
	if(prog<=MAIX_PROG)
		{
		GetOneKnife_datas(prog, 1 , (pInt8U)&Knife_datas);//ȡ��һ�� ����
		KnifeOrder_dis(line, prog,0);//���
		KnifeSize_dis(line,Knife_datas.size,0);//�ߴ�
		prog++;
		}
	else//��������
		{
		x=TableDis_startcol;
		y=RIGHT_ARROW_Y+(line%PAGE_KNIFE)*45;
	    GLCD_SetWindow_Fill( x, y, x+243, y+45, back_color, back_color);//�ߴ�����
		}
	
	line++;
	}
}

void Size_1page_dis(Int16U start_order,Int16U row)//һҳ�ߴ���ʾ
{
//Int16U n;
//pInt8U pbuf;
KNIFE_DATA Knife_datas;
Int16U x1,y1,x2,y2,back_color=0xef9f;
//Int8U sel_flag=0;

//pbuf=(pInt8U)(K_SIZE_sdram+(start_order*5));
while(row<PAGE_KNIFE)
   {
   if(start_order<=MAIX_Knife)
      {
		if(row==cursor_row)  //��괦
			{
			Knife_datas.k_flag=OneKnifeDataSel_dis(start_order, row,RED_COLOR);  //һ������ ������ʾ
			//sel_flag=1;
			}
		else
			{
			GetOneKnife_datas(Pro_data.pro_num, start_order , (pInt8U)&Knife_datas);//ȡ��һ�� ����
			 KnifeOrder_dis(row, start_order,0);//���
			//-----------------����(�ߴ�)���� �ж� 
			if((Knife_datas.size<Size_MIN_num)||(Knife_datas.size>Size_MAX_num))
				{
				Knife_datas.size=0;
				Knife_datas.k_flag=0;
				if(Knife_sum>=start_order)
					{
					if(start_order>1)
						Knife_sum=start_order-1;
					else
						Knife_sum=1;
					Knife_sum_before=Knife_sum;
					SaveKnife_sum(Pro_data.pro_num);//���� ���� 
					StepNum_dis(Knife_sum,start_order);//�������
					}
				}
			if(start_order>Knife_sum)	//���һ������ ֮���������� �����
				{
				if(Knife_datas.size>0)
					{
					Knife_datas.size=0;
					Knife_datas.k_flag=0;
					}
				}
				
			KnifeSize_dis(row,Knife_datas.size,0);//�ߴ�
			}
      
		if(InputTouch_flag==0)  //	 �� ���������� ��
			PushFlag_dis(row,Knife_datas.k_flag); // ��ֽ ��־ 
	  }
   else
      {
	  x1=RIGHT_ARROW_X;
      y1=RIGHT_ARROW_Y+row*45;
	  y2=y1+45;
	  if(InputTouch_flag==0)  //	 �� ���������� ��
		  x2=RED_KNIFE_X+25;
	  else
		  x2=CALCUL_WIN_X-3;
	  GLCD_SetWindow_Fill( x1, y1, x2, y2, back_color, back_color);//
	  }
   start_order++;
   row++;
   }
}

void DeleteOneKnife(Int16U prog,Int16U knife)       //ɾ��һ��
{
pInt8U pbuf_k1,pbuf_k2;
Int32U offset,add,n,num;
if(prog<=(PROG_GROPU1+1))  //ǰ301��prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//��  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
pbuf_k1=(pInt8U)(K_SIZE_sdram+offset+2+(knife-1)*5);//��ǰ�� buf����ַ
pbuf_k2=pbuf_k1+5;        //��һ�� 

num=Knife_sum-knife;
if(num>0)
   {
   for(n=0;n<num*5;n++)
     {
     *pbuf_k1++=*pbuf_k2++;
     }
	*pbuf_k1++=0;// ���һ��
	*pbuf_k1++=0;
	*pbuf_k1++=0;
	*pbuf_k1++=0;
	*pbuf_k1=0;
   if(knife==1)  //��һ��
	  {
	  pKnife_data=(pInt8U)&OneKnife_data;
	  GetOneKnife_datas(prog, knife, pKnife_data);
	  if(OneKnife_data.k_flag==KNIFE_FLAG)
		 {
		 OneKnife_data.k_flag=NO_FLAG;  //��� ��־
		 SaveOneKnife_datas(prog, knife , pKnife_data);//����һ������
		 }
	  } 
	
   pbuf_k1=(pInt8U)(K_SIZE_sdram+offset+2+(knife-1)*5);//��ǰ�� buf����ַ
   add=DATA_SAVE_OFFSET+offset+2+(knife-1)*5;//
   Write_25pe_data(pbuf_k1,     add,      (num+1)*5);
   }
else// ���һ��
   {
   *(pbuf_k1+0)=0;
   *(pbuf_k1+1)=0;
   *(pbuf_k1+2)=0;
   *(pbuf_k1+3)=0;
   *(pbuf_k1+4)=0;
   SaveOneKnife_datas(prog, knife,pbuf_k1);
   }
}

void InsertOneKnife(Int16U prog,Int16U knife)       //����һ��
{
pInt8U pbuf_k1,pbuf_k2;
Int32U offset,add,n,num;
if(prog<=(PROG_GROPU1+1))  //ǰ301��prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//��  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
pbuf_k1=(pInt8U)(K_SIZE_sdram+offset+2+(Knife_sum-1)*5);//���һ�� buf����ַ
pbuf_k2=pbuf_k1+5;        //��һ��

pbuf_k1+=4;
pbuf_k2+=4;
num=Knife_sum-knife+1;

for(n=0;n<num*5;n++)
   {
   *pbuf_k2--=*pbuf_k1--;
   }   
pbuf_k1=(pInt8U)(K_SIZE_sdram+offset+2+(knife)*5);//��ǰ�� buf����ַ
add=DATA_SAVE_OFFSET+offset+2+(knife)*5;//
Write_25pe_data(pbuf_k1,     add,      num*5);   
}

Int8U CheckInputNums(void)  //����ߴ� ����
{
Int8U nn,num_bits;
pInt8U Size;
Int32U temp=0;
nn=0;
Dot_flag=0;
if(InputTouch_flag==0)
	{
	Size=Size_temp;
	num_bits=num_cou;
	}
else    //���� ������
	{
	if(CalcResultDis_flag==0) //  δ����
		{
		CalcGetValue_exec();  //��������
		}
	if(CalcResultDis_flag==1)  //�ѵõ�  ���
		{
		Size=CalcResult_Text;
		num_bits=CalcInput_cou;
		}
	else
		return 0;
	}
while(nn<num_bits)
	{
	  if(Size[nn]!='.')
		{
		 temp=temp*10+Size[nn];
		 nn++;
		}
	  else//.
	    {
		nn++;
		break;
		}
	}
//----
if(nn>=num_bits)//��С������
	{
	 switch(WorkMode)
		 {
		 case PROG_MODE://��̻�����
		 case TEACH_MODE://ʾ�̻�����
		 
		 case AUTO_MODE://�Զ���������
		 case SELF_CUT_MODE://�Ե���������
		 case MANUAL_MODE:   //�ֶ�
				if(Unit==UNIT_MM)
					{
					InputSize=temp*100;
					}
				else
					{
					InputSize=temp*1000;
					}
				if((InputSize<Size_MIN_num)||(InputSize>Size_MAX_num))//������Χ
					{
					PromptDis_flag=0;
					GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
					switch(Language)
						{
						case CHN_HAN:
							Printf24("����ߴ糬�����ޣ�",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
						case ENGLISH:
							Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
						}
					if(InputTouch_flag==1)   //������
						{
						ClearCalculatorInput(); //��������� ����
						}
					return 0;
					}
				else   //��ȷ	 
					{
					PromptNum_dis();//���뷶Χ ��ʾ
					PromptDis_flag=1;
					return 1;
					}	
					break;
		case PROG_LABEL_MODE://	��� ��ǩ	
		case TEACH_LABEL_MODE:// ʾ�� ��ǩ	
		case PROG_DIVIDE_MODE://��� �ȷ�
		case TEACH_DIVIDE_MODE://ʾ�� �ȷ�
		case AUTO_RULER_MODE://�Զ� ��׼
		case SELF_RULER_MODE://�Ե� ��׼
		case MANUAL_RULER_MODE://�ֶ� ��׼ģʽ	
				if(PorgSet_sel<1)
					{
					if(Unit==UNIT_MM)
						{
						InputSize=temp*100;
						}
					else
						{
						InputSize=temp*1000;
						}
					if((InputSize<Size_MIN_num)||(InputSize>Size_MAX_num))//������Χ
						{
						PromptDis_flag=0;
						GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
						switch(Language)
							{
							case CHN_HAN:
								Printf24("����ߴ糬�����ޣ�",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
							case ENGLISH:
								Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
							}
						if(InputTouch_flag==1)   //������
							{
							ClearCalculatorInput(); //��������� ����
							}
						return 0;
						}
					else   //��ȷ	 
						{
						PromptNum_dis();//���뷶Χ ��ʾ
						PromptDis_flag=1;
						return 1;
						}	
					}
				else
					{
					if((WorkMode&0x0f)==(PROG_DIVIDE_MODE&0x0f))//�ȷ�
						{
						InputSize=temp;
						if((InputSize>0)&&(InputSize<=1000))
							return 1;
						return 0;	
						}
					else
						{
						if(Unit==UNIT_MM)
							{
							InputSize=temp*100;
							}
						else
							{
							InputSize=temp*1000;
							}
						if((InputSize>0)&&(InputSize<=Size_MAX_num))   //��ȷ
							{
							return 1;
							}
						else
							{
							PromptDis_flag=0;
							GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
							switch(Language)
								{
								case CHN_HAN:
									Printf24("����ߴ糬�����ޣ�",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
								case ENGLISH:
									Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
								}
							}
						return 0;		
						}
					return 0;		
					}
					break;
		case PROG_PRO_MODE:    //����ѡ��----------------------
		case TEACH_PRO_MODE:    //����ѡ��----------------------
				if((temp>0)&&(temp<=MAIX_PROG))// ��Ч
					{
					InputSize=temp;
					return 1;
					}
				return 0;	
					break;
				
		case AUTO_TOOLS_MODE://�Զ�  ��������
		case SELF_TOOLS_MODE://�Ե�  ��������
		case MANUAL_TOOLS_MODE:// �ֶ� ����ģʽ
				if(PramSel_Page<1)	//page 1
					{
				if(Para_sel>7)
					{
					InputSize=temp;
					}
				else if(Para_sel<7)
					{
					if(Unit==UNIT_MM)
						{
						InputSize=temp*100;
						}
					else
						{
						InputSize=temp*1000;
						}
					}
					}
				else	//page 2
					{
					if(Para2_sel<2)
						{
						InputSize=temp; 
						}
					else 
						{
						//if(Unit==UNIT_MM)
							// {
							// InputSize=temp*100;
							// }
						// else
							// {
							// InputSize=temp*1000;
							// }
						}
					}
				return 1;	
					break;
		case AUTO_PLUS_MODE:  //F3++
		case AUTO_MINUS_MODE:// F4--
		case SELF_PLUS_MODE:  //F3++
		case SELF_MINUS_MODE:// F4--
				if(Unit==UNIT_MM)
					{
					InputSize=temp*100;
					}
				else
					{
					InputSize=temp*1000;
					}
				return 1;	
				 	break;
		case MANUAL_CLOCK_MODE: //�ֶ� ʱ��ģʽ			
		case MANUAL_PASS_MODE: //����ģʽ
		case MANUAL_PULSE_MODE://�ֶ� ���嵱��
		case MANUAL_SERVO_C_MODE:// �ֶ�ֱ���ŷ� C ���� 
				 InputSize=temp;
				 return 1;
					break;
		 }
	if(PassCheckDis_flag==1)	
		{
		InputSize=temp;
		return 1;
		}
	return 0; 
	}
else   //��С������
    {
	temp=temp*10+Size[nn];
	nn++;
	temp*=10;
	if(nn<num_bits)
	    temp+=Size[nn++];
	if(Unit!=UNIT_MM)
	   {
	    temp*=10;
		if(nn<num_bits)
			temp+=Size[nn];
	   } 
		
	InputSize=temp;
	 switch(WorkMode)
		 {
		 case PROG_MODE://��̻�����
		 case TEACH_MODE://ʾ�̻�����
		 case AUTO_MODE://�Զ���������
		 case SELF_CUT_MODE://�Ե��������� 
		 case MANUAL_MODE:   //�ֶ�
				if((InputSize<Size_MIN_num)||(InputSize>Size_MAX_num))//������Χ
					{
					PromptDis_flag=0;
					GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
					switch(Language)
						{
						case CHN_HAN:
							Printf24("����ߴ糬�����ޣ�",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
						case ENGLISH:
							Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
						}
					if(InputTouch_flag==1)   //������
						{
						ClearCalculatorInput(); //��������� ����
						}
					return 0;
					}
				else   //��ȷ	 
					{
					PromptNum_dis();//���뷶Χ ��ʾ
					PromptDis_flag=1;
					return 1;
					}	
					break;
		case PROG_LABEL_MODE://	��� ��ǩ	
		case TEACH_LABEL_MODE:// ʾ�� ��ǩ	
		case PROG_DIVIDE_MODE://��� �ȷ�
		case TEACH_DIVIDE_MODE://ʾ�� �ȷ�
		case AUTO_RULER_MODE://�Զ� ��׼
		case SELF_RULER_MODE://�Ե� ��׼
		case MANUAL_RULER_MODE://�ֶ� ��׼ģʽ
				if(PorgSet_sel<1)
					{
					if((InputSize<Size_MIN_num)||(InputSize>Size_MAX_num))//������Χ
						{
						PromptDis_flag=0;
						GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
						switch(Language)
							{
							case CHN_HAN:
								Printf24("����ߴ糬�����ޣ�",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
							case ENGLISH:
								Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
							}
						if(InputTouch_flag==1)   //������
							{
							ClearCalculatorInput(); //��������� ����
							}	
						return 0;
						}
					else   //��ȷ	 
						{
						PromptNum_dis();//���뷶Χ ��ʾ
						PromptDis_flag=1;
						return 1;
						}	
					}
				else
					{
					if((WorkMode&0x0f)==(PROG_DIVIDE_MODE&0x0f))  //�ȷ�
						{
						if(Unit==UNIT_MM)
							{
							InputSize=temp/100;
							}
						else
							{
							InputSize=temp/1000;
							}
						if((InputSize>0)&&(InputSize<=1000))
							return 1;
						return 0;	
						}
					else
						{
						InputSize=temp;
						if((InputSize>0)&&(InputSize<=Size_MAX_num))   //��ȷ
							return 1;
						else
							{
							PromptDis_flag=0;
							GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
							switch(Language)
								{
								case CHN_HAN:
									Printf24("����ߴ糬�����ޣ�",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
								case ENGLISH:
									Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
								}
							}
						return 0;	
						}
					return 0;	
					}
				return 0;	
					break;
		case PROG_PRO_MODE:    //����ѡ��----------------------
		case TEACH_PRO_MODE:    //����ѡ��----------------------
				if(Unit==UNIT_MM)
					{
					InputSize=temp/100;
					}
				else
					{
					InputSize=temp/1000;
					}
				if((InputSize>0)&&(InputSize<=MAIX_PROG))// ��Ч
					{
					return 1;
					}
				return 0;	
					break;	
					
		case AUTO_TOOLS_MODE://�Զ�  ��������
		case SELF_TOOLS_MODE://�Ե�  ��������
		case MANUAL_TOOLS_MODE:// �ֶ� ����ģʽ
				if(Para_sel>8)
					{
					if(Unit==UNIT_MM)
						{
						InputSize=temp/100;
						}
					else
						{
						InputSize=temp/1000;
						}
					}
				return 1;	
					break;
		case AUTO_PLUS_MODE:  //F3++
		case AUTO_MINUS_MODE:// F4--
		case SELF_PLUS_MODE:  //F3++
		case SELF_MINUS_MODE:// F4--
				return 1;	
					break;
		case MANUAL_CLOCK_MODE: //�ֶ� ʱ��ģʽ
		case MANUAL_PASS_MODE: //����ģʽ	
		case MANUAL_PULSE_MODE://�ֶ� ���嵱��
		case MANUAL_SERVO_C_MODE:// �ֶ�ֱ���ŷ� C ���� 
				if(Unit==UNIT_MM)
					{
					InputSize=temp/100;
					}
				else
					{
					InputSize=temp/1000;
					}
				return 1;	
					break;
		 }
	return 0; 
	}
}

void LabelSel_dis(Int8U sel, Int8U flag)
{
switch(sel)
	{
	case 0://�ܳ�
		ProgSet_dis(Total_size, TOTAL_SIZE_X,  TOTAL_SIZE_Y,flag);
		if(flag==1)
			{
			PromptNum_dis();//���뷶Χ
			PromptDis_flag=1;
			}
			break;
	case 1:	//��ǩ��
		ProgSet_dis(Label_size, LABEL_SIZE_X,  LABEL_SIZE_Y,flag);
		if(flag==1)
			{
			PromptNum_dis();//���뷶Χ
			// PromptDis_flag=1;
			PromptDis_flag=0;
			Printf24("0   ",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
			}
			break;
	case 2://�ϱ�	
		ProgSet_dis(Waste_size, WASTE_SIZE_X,  WASTE_SIZE_Y,flag);
		if(flag==1)
			{
			PromptNum_dis();//���뷶Χ
			// PromptDis_flag=1;
			PromptDis_flag=0;
			Printf24("0   ",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
			}
			break;
	}
}

void Label_function(void)  //��ǩ����
{
Int16U order;
Int32U data,offset,add;
pInt8U pbuf;
Int8U j;

order=Knife_order;
pKnife_data=(pInt8U)&OneKnife_data;
//GetOneKnife_datas(order, pKnife_data);
if(Pro_data.pro_num<=(PROG_GROPU1+1))  //ǰ301��prog
   {
   offset=PROG_BYTES1*(Pro_data.pro_num-1);
   }
else//��  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(Pro_data.pro_num-PROG_GROPU1-1)*PROG_BYTES2;
   }
pbuf=(pInt8U)(K_SIZE_sdram+offset+2+order*5);//�������ַ
add=DATA_SAVE_OFFSET+offset+2+order*5;

OneKnife_data.size=Total_size;  //�ߴ��޸�
OneKnife_data.k_flag=NO_FLAG;  //��� ��־
SaveOneKnife_datas(Pro_data.pro_num, order++ , pKnife_data);//����һ������
data=Total_size;
while(order<=MAIX_Knife)
	{
	if(data>Label_size)
	   {
	    data-=Label_size;
		if((data>=Size_MIN_num)&&(data<=Size_MAX_num))//������Ч
		  {
	      OneKnife_data.size=data;
		 // SaveOneKnife_datas(order++ , pKnife_data);//����
		  for(j=0;j<5;j++)
			 {
			 *pbuf++=*(pKnife_data+j);
			 }
		  order++;
		  if(data>Waste_size)
		     {
			 data-=Waste_size;
			 if((data>=Size_MIN_num)&&(data<=Size_MAX_num))//������Ч
				{
				OneKnife_data.size=data;
				//SaveOneKnife_datas(order++ , pKnife_data);//����
				for(j=0;j<5;j++)
					{
					*pbuf++=*(pKnife_data+j);
					}
			    order++;
				}
		     else
				break;
			 }
		  else
			 {
			 break;
			 }
	      }
		else
		  break;
	   }
	else
	   {
	   break;
	   }
	}
	
//-----��ʾ
//CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  800, 269); //�˳� ��ǩ����
//  ------------���±�� ���� ��ʾ
if(order>=Knife_sum)
   {
   if(order<=MAIX_Knife)
      {
	  Knife_sum=order-1;
	  }
   else
	  {
	  Knife_sum=MAIX_Knife;
	  }
   }
SaveKnife_sum(Pro_data.pro_num);//���� ����  
StepNum_dis(Knife_sum,Knife_order);//�������
Size_1page_dis(Knife_order,cursor_row);	
SaveBuf_datas(Pro_data.pro_num,  Knife_order+1,  order-1); //����
PromptNum_dis();//���뷶Χ ��ʾ
PromptDis_flag=1;
}

void CursorDown_inTable(void) //**** ������� ��ʾ ����
{
if(Knife_order<=MAIX_Knife)
	{
	if(Knife_order>Knife_sum) //�ص� ��һ��ѭ��
		{
		CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
		cursor_row=0;
		CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
		Knife_order=1;//
		Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
		}	
	else
		{
		if(Knife_order==Knife_sum)
			{
			if(AutoRoute_flag==1) //�Զ� �ص� ��һ��ѭ��
				{
				CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
				cursor_row=0;
				CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
				Knife_order=1;
				Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
				}
			else
				{
				Knife_order++;
				if(Knife_order<=MAIX_Knife)   //999 ����
					{
					if(cursor_row<(PAGE_KNIFE-1))
						{
						CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
						OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //һ������ ������ʾ
						cursor_row++;
						CursorMov_dis(cursor_row, 1);//��ɫ���������ʾ
						OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //һ������ ������ʾ
						}
					else   //ҳ��
						{
						Size_1page_dis(Knife_order-(PAGE_KNIFE-1),0);//һҳ�ߴ���ʾ
						}
					}
				else  //999��  �ص� ��һ��ѭ��
					{
					CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
					cursor_row=0;
					CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
					Knife_order=1;
					Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
					}
				}
			}
		else
			{
			Knife_order++;
			if(Knife_order<=MAIX_Knife)   //999 ����
				{
				if(cursor_row<(PAGE_KNIFE-1))
					{
					CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
					OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //һ������ ������ʾ
					cursor_row++;
					CursorMov_dis(cursor_row, 1);//��ɫ���������ʾ
					OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //һ������ ������ʾ
					}
				else   //ҳ��
					{
					Size_1page_dis(Knife_order-(PAGE_KNIFE-1),0);//һҳ�ߴ���ʾ
					}
				}
			else  //999��  �ص� ��һ��ѭ��
				{
				CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
				cursor_row=0;
				CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
				Knife_order=1;
				Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
				}
			}
		}
	if(Knife_order<=Knife_sum+1)
		StepOrder_dis(Knife_order);//�������
	PromptNum_dis();//���뷶Χ
	PromptDis_flag=1;
	}
}




void DivideSel_dis(Int8U sel, Int8U flag)
{
switch(sel)
	{
	case 0://�ܳ�
		ProgSet_dis(Total_size, DIVIDE_TOTAL_X,  DIVIDE_TOTAL_Y,flag);//
		if(flag==1)
			{
			PromptNum_dis();//���뷶Χ
			PromptDis_flag=1;
			}
			break;
	case 1: //�ȷ���
		ProgSet_dis(Divide_num, DIVIDE_NUM_X,  DIVIDE_NUM_Y,flag);
		if(flag==1)
			{
			PromptDis_flag=0;
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
			Printf24("1        1000",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
			}
			break;
	}
}



void LabelEnter_exec(void) //��ǩ ���� �����趨ȷ��
{
switch(PorgSet_sel)
	{
		case 0://�ܳ�
				if(CheckInputNums()==1)//������Ч
					{
					if(Total_size!=InputSize)
						{
						Total_size=InputSize;
						LabelSel_dis(PorgSet_sel++,0);
						LabelSel_dis(PorgSet_sel,1);
						}
					else
						{
						if(Label_size*Waste_size>=0) //���� �Ѿ��������
							{
							if(InputTouch_flag==1)   //������  ������ ��������ʧ
								{
								CalcuInClear_exec();     //��� ������
								}
							}
						}
					}
				else
					num_cou=0;
					break;
		case 1://��ǩ
				if(CheckInputNums()==1)//������Ч
					{
					if(Label_size!=InputSize)
						{
						Label_size=InputSize;//
						LabelSel_dis(PorgSet_sel++,0);
						LabelSel_dis(PorgSet_sel,1);
						}
					else
						{
						if(Total_size*Waste_size>0)
							{
							if(InputTouch_flag==1)   //������  ������ ��������ʧ
								{
								CalcuInClear_exec();     //��� ������
								}
							}
						}
					}
				else
					num_cou=0;
					break;
		case 2://
				if(CheckInputNums()==1)//������Ч
					{
					if(Waste_size!=InputSize)
						{
						Waste_size=InputSize;//
						LabelSel_dis(PorgSet_sel,1);
						}
					else
						{
						if(Total_size*Label_size>0)
							{
							if(InputTouch_flag==1)   //������  ������ ��������ʧ
								{
								CalcuInClear_exec();     //��� ������
								}
							}
						}
					}
				else
					num_cou=0;
					break; 
	}
if(InputTouch_flag==0)  //	 �� ���������� ��	
	ClrInput_function();//���� ����� 		
}

void DivideEnter_exec(void) //�ȷ� �����趨ȷ��
{
Int32U d_num;
switch(PorgSet_sel)
	{
		case 0://�ܳ�
				if(CheckInputNums()==1)//������Ч
					{
					if(Total_size!=InputSize)
						{
						Total_size=InputSize;
						DivideSel_dis(PorgSet_sel,0);PorgSet_sel++;
						DivideSel_dis(PorgSet_sel,1);
						}
					else
						{
						if(Divide_num>0)
							{
							if(InputTouch_flag==1)   //������  ������ ��������ʧ
								{
								CalcuInClear_exec();     //��� ������
								}
							}
						}
					}
				else
					num_cou=0;
					break;
		case 1://�ȷ���
				if(CheckInputNums()==1)//������Ч
					{
					if(Divide_num!=InputSize)
						{
						Divide_num=InputSize;
						DivideSel_dis(PorgSet_sel,1);
						}
					else
						{
						if(Total_size>0)
							{
							if(InputTouch_flag==1)   //������  ������ ��������ʧ
								{
								CalcuInClear_exec();     //��� ������
								}
							}
						}
					}
				else
					{
					num_cou=0;
					//GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+360, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
					//Printf24("������ֵ��Χ����!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
					}
					break;
		
	}
if(InputTouch_flag==0)  //	 �� ���������� ��	
	ClrInput_function();//���� ����� 		
}


void Divide_function(void)  //�ȷֹ���
{
Int16U order;
Int32U data,offset,add,d_size;
pInt8U pbuf;
Int8U j;

order=Knife_order;
pKnife_data=(pInt8U)&OneKnife_data;
//GetOneKnife_datas(order, pKnife_data);
if(Pro_data.pro_num<=(PROG_GROPU1+1))  //ǰ301��prog
   {
   offset=PROG_BYTES1*(Pro_data.pro_num-1);
   }
else//��  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(Pro_data.pro_num-PROG_GROPU1-1)*PROG_BYTES2;
   }
pbuf=(pInt8U)(K_SIZE_sdram+offset+2+order*5);//�������ַ
add=DATA_SAVE_OFFSET+offset+2+order*5;

OneKnife_data.size=Total_size;  //�ߴ��޸�
OneKnife_data.k_flag=NO_FLAG;  //��� ��־
SaveOneKnife_datas(Pro_data.pro_num, order++ , pKnife_data);//����һ������
data=Total_size;
d_size=Total_size/Divide_num;
while(order<=MAIX_Knife)
	{
	if(data>d_size)
	   {
	    data-=d_size;
		if((data>=Size_MIN_num)&&(data<=Size_MAX_num))//������Ч
		  {
	      OneKnife_data.size=data;
		 // SaveOneKnife_datas(order++ , pKnife_data);//����
		  for(j=0;j<5;j++)
			 {
			 *pbuf++=*(pKnife_data+j);
			 }
		  order++;
	      }
		else
		  break;
	   }
	else
	   {
	   break;
	   }
	}
	
//-----��ʾ
//CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  800, 269); //�˳� ��ǩ����
//  ------------���±�� ���� ��ʾ
if(order>=Knife_sum)
   {
   if(order<=MAIX_Knife)
      {
	  Knife_sum=order-1;
	  }
   else
	  {
	  Knife_sum=MAIX_Knife;
	  }
   }
SaveKnife_sum(Pro_data.pro_num);//���� ����  
StepNum_dis(Knife_sum,Knife_order);//�������
Size_1page_dis(Knife_order,cursor_row);	
SaveBuf_datas(Pro_data.pro_num, Knife_order+1,  order-1); //����
PromptNum_dis();//���뷶Χ ��ʾ
PromptDis_flag=1;
}

void ProEnter_exec(void)  //����ѡ�� ����ȷ��
{
Int32U temp;
if(CheckInputNums()==1)// ��Ч
   {
    //GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+360, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
	//Printf24("������ֵ��Χ    ��",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
	//Printf24("1    500",REMIND_WINDOW_X+165,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
	if(InputTouch_flag==1)   //������  ������ ��������ʧ
		{
		CalcuInClear_exec();     //��� ������
		}
	//----��� ��ת
	Pro_num=InputSize;//��ǰ �����
	temp=InputSize%PAGE2_KNIFE;
	CursorMov_dis(cursor_temp,0);//���
	if(temp<1)
	   temp=PAGE2_KNIFE;
	cursor_temp=temp-1;
	  
	CursorMov_dis(cursor_temp,1);//
	Prog_1page_dis(Pro_num-temp+1, 0);//===����---������ʾ
   }
else
   {
   num_cou=0;
  // PromptDis_flag=0;
  // GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+360, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
//	Printf24("������ֵ��Χ����!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
   }
if(InputTouch_flag==0)  //	 �� ���������� ��
	ClrInput_function();//���� �����   
}

void ExportOnePro_dis(Int16U prog) //���� ��ʾһ������-------------
{
Int16U x1,x2,y,back_color=0xef9f;
pInt8U pdata;

CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y, M_PAGE_WIDE, M_PAGE_HIGH);
x1=RIGHT_ARROW_X;
y=RIGHT_ARROW_Y;
x2=RED_KNIFE_X+25;
GLCD_SetWindow_Fill( x1, y, x2, y+225, back_color, back_color);//
//************��ǰpro ����
Pro_data.pro_num=prog;
pdata=(pInt8U)&Pro_data;
SavePro_data(pdata);
if(prog<=PROG_GROPU1)//ǰ 300��pro
   {
   MAIX_Knife=MAIX_KNIFE1;//999
   }
else
   {
   MAIX_Knife=MAIX_KNIFE2;//399
   } 
ReadOnePro_datas(prog);//��ȡ ��ǰpro
ClrBuf_datas(prog, 1,MAIX_Knife);  //���� ������buf
GetKnife_sum(prog); //��ȡǰ���� ����
 // Knife_sum=6;
ReadOnePro_datas(prog);//��ȡ һ��pro

CheckKnifeSum_exec();  //--------------�ܵ���    �˶�
Knife_sum_before=Knife_sum;
//-------------���� ��ʾ
cursor_temp=0;
Knife_order=1;
cursor_row=0;     // ������ ��ʾ ��ͷ
Size_1page_dis(Knife_order, 0);  
CursorMov_dis(cursor_row,1);//��ɫ��ͷ  
ProNum_dis(prog);// ����� 
StepNum_dis(Knife_sum,Knife_order);// �����  �ܵ���-���

PromptDis_flag=1;
PromptNum_dis();
LastAutoKnife_order=1;
}

void F3_AutoAdd_exec(Int32U add_data)  //F3++  �������� �Լ�
{
Int16U order;
Int32U data;

order=Knife_order;
pKnife_data=(pInt8U)&OneKnife_data;
GetOneKnife_datas(Pro_data.pro_num, order, pKnife_data);
data=OneKnife_data.size+add_data;

if((data<=Size_MAX_num)&&(data>=Size_MIN_num)) //��Χ ��
	{
	PromptNum_dis();//���뷶Χ ��ʾ
	PromptDis_flag=1;
	OneKnife_data.size=data;
	SaveOneKnife_datas(Pro_data.pro_num, order++ , pKnife_data);//����һ������
	
	while(order<=Knife_sum)
		{
		//pKnife_data=(pInt8U)&OneKnife_data;
		GetOneKnife_datas(Pro_data.pro_num, order-1, pKnife_data);//��һ��
		data=OneKnife_data.size;
		GetOneKnife_datas(Pro_data.pro_num, order, pKnife_data);//��ǰ��
		
		if(OneKnife_data.size>data)
			{
			//order++;
			break;
			}
		else
			{
			data=OneKnife_data.size+add_data;
			if((data>Size_MAX_num)||(data<Size_MIN_num)) //������Χ
			   {
			   order++;
			   break;
			   }
			else
			   {
			   OneKnife_data.size=data;
			   PutOneKnife_datas(Pro_data.pro_num, order, pKnife_data); //���� һ������
			   }
			}
		order++;
		}
	order--;
	//SaveKnife_sum(Pro_data.pro_num);//���� ���� 
	StepNum_dis(Knife_sum,order);//�������
	if(order-Knife_order+cursor_row>(PAGE_KNIFE-1)) //��ҳ
		{
		CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
		cursor_row=0;
		CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
		Size_1page_dis(order,cursor_row);	
		}
	else
		{
		Size_1page_dis(Knife_order,cursor_row);
		CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
		cursor_row+=order-Knife_order;
		CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ	
		}	
	SaveBuf_datas(Pro_data.pro_num, Knife_order+1,  order); //����
	Knife_order=order;
	PromptNum_dis();//���뷶Χ ��ʾ	
	PromptDis_flag=1;
	}
}

void F4_AutoSub_exec(Int32U add_data)  //F4--  �������� �Լ�
{
Int16U order;
Int32U data;

order=Knife_order;
pKnife_data=(pInt8U)&OneKnife_data;
GetOneKnife_datas(Pro_data.pro_num, order, pKnife_data);
if(OneKnife_data.size>add_data)
  {
  data=OneKnife_data.size-add_data;
  if((data<=Size_MAX_num)&&(data>=Size_MIN_num)) //��Χ ��
	 {
	 PromptNum_dis();//���뷶Χ ��ʾ
	 PromptDis_flag=1;
	 OneKnife_data.size=data;
	 SaveOneKnife_datas(Pro_data.pro_num, order++ , pKnife_data);//����һ������
	
	 while(order<=Knife_sum)
		{
		//pKnife_data=(pInt8U)&OneKnife_data;
		GetOneKnife_datas(Pro_data.pro_num, order-1, pKnife_data);//��һ��
		data=OneKnife_data.size;
		GetOneKnife_datas(Pro_data.pro_num, order, pKnife_data);//��ǰ��
		if(OneKnife_data.size>data)
			{
			//order++;
			break;
			}
		else
			{
			if(OneKnife_data.size>add_data)
				{
				data=OneKnife_data.size-add_data;
				if((data>Size_MAX_num)||(data<Size_MIN_num)) //������Χ
					{
					order++;
					break;
					}
				else
					{
					OneKnife_data.size=data;
					PutOneKnife_datas(Pro_data.pro_num, order, pKnife_data); //���� һ������
					}
				}
			else
				break;
			}
		order++;
		}
	 order--;
	 //SaveKnife_sum(Pro_data.pro_num);//���� ���� 
	 StepNum_dis(Knife_sum,order);//�������
	 if(order-Knife_order+cursor_row>(PAGE_KNIFE-1)) //��ҳ
		{
		CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
		cursor_row=0;
		CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ
		Size_1page_dis(order,cursor_row);	
		}
	 else
		{
		Size_1page_dis(Knife_order,cursor_row);
		CursorMov_dis(cursor_row, 0);//��ɫ�����ʧ
		cursor_row+=order-Knife_order;
		CursorMov_dis(cursor_row, 1);//��ɫ�����ʾ	
		}	
 	 SaveBuf_datas(Pro_data.pro_num, Knife_order+1,  order); //����
	 Knife_order=order;
	 PromptNum_dis();//���뷶Χ ��ʾ
	 PromptDis_flag=1;
	 }
  } 
   
}

void ReadOriginalSize(void)  //��ȡԭ��ߴ�
{
pInt8U psize;
Int32U add;
Int16U n;
psize=(pInt8U)&OriginalSize;
add=ORIGINAL_25PEADD;

FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
if(OriginalSize>999999)
	OriginalSize=123450;
}
void SaveOriginalSize(void)  //����ԭ��ߴ�
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&OriginalSize;
add=ORIGINAL_25PEADD;
Write_25pe_data(psize, add, 4);
}


void ReadFrontLimit(void)  //��ȡǰ����
{
pInt8U psize;
Int32U add,temp;
Int16U n;
psize=(pInt8U)&FrontLimit;
add=ORIGINAL_25PEADD+4;

FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
temp=FrontLimit;
if((temp<FRONT_LIM_MIN)||(temp>FRONT_LIM_MAX))
	{
	FrontLimit=3000;
	}
}
void SaveFrontLimit(void)  //����ǰ����
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&FrontLimit;
add=ORIGINAL_25PEADD+4;
Write_25pe_data(psize, add, 4);
}

void ReadMiddleLimit(void)  //��ȡ�м���
{
pInt8U psize;
Int32U add,temp;
Int16U n;
psize=(pInt8U)&MiddleLimit;
add=ORIGINAL_25PEADD+8;

FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
if((MiddleLimit<MIDD_LIM_MIN)||(MiddleLimit>MIDD_LIM_MAX))
	{
	MiddleLimit=8000;
	}
}
void SaveMiddleLimit(void)  //�����м���
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&MiddleLimit;
add=ORIGINAL_25PEADD+8;
Write_25pe_data(psize, add, 4);
}

void ReadBackLimit(void)  //��ȡ����
{
pInt8U psize;
Int32U add,temp;
Int16U n;
psize=(pInt8U)&BackLimit;
add=ORIGINAL_25PEADD+12;

FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
if((BackLimit<BACK_LIM_MIN)||(BackLimit>BACK_LIM_MAX))
	{
	BackLimit=138000;
	}
}
void SaveBackLimit(void)  //�������
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&BackLimit;
add=ORIGINAL_25PEADD+12;
Write_25pe_data(psize, add, 4);
}

void ReadLanguage(void)//��ȡ����
{
pInt8U psize;
Int32U add;
Int16U n;
psize=(pInt8U)&Language;
add=ORIGINAL_25PEADD+16;

FastRead_Datas_Start(add);

*psize=ReadFlash_Datas();
FlashChip_Dis;
if(Language>1)
	Language=0;
}
void SaveLanguage(void)  //��������
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&Language;
add=ORIGINAL_25PEADD+16;
Write_25pe_data(psize, add, 1);
}

void ReadUnit(void)//��ȡ��λ
{
pInt8U psize;
Int32U add;
Int16U n;
psize=(pInt8U)&Unit;
add=ORIGINAL_25PEADD+18;

FastRead_Datas_Start(add);
*psize=ReadFlash_Datas();
FlashChip_Dis;	
if(Unit>UNIT_MIL)
	Unit=UNIT_MM;
}
void SaveUnit(void)  //���浥λ
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&Unit;
add=ORIGINAL_25PEADD+18;
Write_25pe_data(psize, add, 1);
}

void ReadAheader(void)//��ȡ��ǰ��
{
pInt8U psize;
Int32U add;
Int16U n;
psize=(pInt8U)&Aheader;
add=ORIGINAL_25PEADD+20;

FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
if((Aheader<1)||(Aheader>100))
	{
	Aheader=25;
	}
}

void SaveAheader(void)  //������ǰ��
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&Aheader;
add=ORIGINAL_25PEADD+20;
Write_25pe_data(psize, add, 4);
}



void ReadDisWuCha(void)//����Χ
{
pInt8U psize;
Int32U add;
Int16U n;
psize=(pInt8U)&DisWuCha;
add=ORIGINAL_25PEADD+24;

FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
if((DisWuCha<20)||(DisWuCha>100))
	{
	DisWuCha=20;
	}
}

void SaveDisWuCha(void)//������Χ
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&DisWuCha;
add=ORIGINAL_25PEADD+24;
Write_25pe_data(psize, add, 4);
	
}

/*
void ReadStanDistance(void)//��ȡ��׼����
{
pInt8U psize;
Int32U add;
Int16U n;
psize=(pInt8U)&StanDistance;
add=ORIGINAL_25PEADD+24;

FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
}
void SaveStanDistance(void)  //�����׼����
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&StanDistance;
add=ORIGINAL_25PEADD+24;
Write_25pe_data(psize, add, 4);
}*/

void Read_degree(void)
{
Int32U add;
add=ORIGINAL_25PEADD+30;

FastRead_Datas_Start(add);
Pulse_degree=ReadFlash_Datas();
FlashChip_Dis;
}
void Save_degree(void)
{
Int32U add;
pInt8U psize;
add=ORIGINAL_25PEADD+30;
psize=(pInt8U)&Pulse_degree;
Write_25pe_data(psize, add, 1);
}

void SetPulse_degree(void)  //�趨���嵱��
{
if(Pulse_degree>11)
	Pulse_degree=0;
switch(Pulse_degree)
	{
	case 0:
		maichongdangliang=5000;
		Z_Pulse=50;
		break;
	case 1:
		maichongdangliang=6000;
		Z_Pulse=50;
		break;	
	case 2:
		maichongdangliang=4000;
		Z_Pulse=50;
		break;
	case 3:
		maichongdangliang=9000;
		Z_Pulse=50;
		break;	
	case 4:
		maichongdangliang=5000;
		Z_Pulse=60;
		break;
	case 5:
		maichongdangliang=4166;
		Z_Pulse=60;
		break;	
	case 6:
		maichongdangliang=3333;
		Z_Pulse=60;
		break;
	case 7:
		maichongdangliang=7500;
		Z_Pulse=60;
		break;		
	case 8:
		maichongdangliang=2500;
		Z_Pulse=100;
		break;
	case 9:
		maichongdangliang=3000;
		Z_Pulse=100;
		break;	
	case 10:
		maichongdangliang=2083;
		Z_Pulse=120;
		break;		
	case 11:
		maichongdangliang=2500;
		Z_Pulse=120;
		break;	
	}	
	Z_Pulse*=4;
}



void SaveFirstDays(void)
{
Int32U add;
pInt8U psize;
add=ORIGINAL_25PEADD+32;
psize=(pInt8U)&FirstDays;
Write_25pe_data(psize, add, 4);
}
void ReadFirstDays(void)
{
Int32U add;
pInt8U psize;
add=ORIGINAL_25PEADD+32;
psize=(pInt8U)&FirstDays;

FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
if(FirstDays>300)
	FirstDays=0;
}

void SaveSecondDays(void)
{
Int32U add;
pInt8U psize;
add=ORIGINAL_25PEADD+36;
psize=(pInt8U)&SecondDays;
Write_25pe_data(psize, add, 4);
}
void ReadSecondDays(void)
{
Int32U add;
pInt8U psize;
add=ORIGINAL_25PEADD+36;
psize=(pInt8U)&SecondDays;

FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
if(SecondDays>300)
	SecondDays=0;
}

void SaveFirstDays_flag(void)
{
Int32U add;
pInt8U psize;
add=ORIGINAL_25PEADD+40;
psize=(pInt8U)&FirstDayValid_flag;
Write_25pe_data(psize, add, 1);
}
void ReadFirstDays_flag(void)
{
Int32U add;
pInt8U psize;
add=ORIGINAL_25PEADD+40;
psize=(pInt8U)&FirstDayValid_flag;

FastRead_Datas_Start(add);
for(n=0;n<1;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
if(FirstDayValid_flag>1)
	FirstDayValid_flag=0;
}

void SaveSecondDays_flag(void)
{
Int32U add;
pInt8U psize;
add=ORIGINAL_25PEADD+41;
psize=(pInt8U)&SecondDayValid_flag;
Write_25pe_data(psize, add, 1);
}
void ReadSecondDays_flag(void)
{
Int32U add;
pInt8U psize;
add=ORIGINAL_25PEADD+41;
psize=(pInt8U)&SecondDayValid_flag;

FastRead_Datas_Start(add);
for(n=0;n<1;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
if(SecondDayValid_flag>1)
	SecondDayValid_flag=0;
}

void ReadWorkDays(void)
{
Int32U add;
pInt8U psize;
add=ORIGINAL_25PEADD+42;
psize=(pInt8U)&Start_days;

FastRead_Datas_Start(add);
for(n=0;n<6;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
}
void SaveWorkDays(void)
{
Int32U add;
pInt8U psize;
add=ORIGINAL_25PEADD+42;
psize=(pInt8U)&Start_days;
Write_25pe_data(psize, add, 6);
}

void ReadPushDistance(void)//��ȡ�Զ���ֽ����
{
pInt8U psize;
Int32U add;
Int16U n;
psize=(pInt8U)&AutoPushDistance;
add=ORIGINAL_25PEADD+50;

FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*psize++=ReadFlash_Datas();
	}
FlashChip_Dis;
if(AutoPushDistance>AUTO_PUSH_DISTAN)
	AutoPushDistance=10000;
}
void SavePushDistance(void)  //�����Զ���ֽ����
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&AutoPushDistance;
add=ORIGINAL_25PEADD+50;
Write_25pe_data(psize, add, 4);
}
/*
void ReadSpeedLevel(void)  //��ȡ �ٶȵ�λ��
{
Int32U add;
add=ORIGINAL_25PEADD+54;
FastRead_Datas_Start(add);
MotorSpeed_level=ReadFlash_Datas();
FlashChip_Dis;
if(MotorSpeed_level>2)
	MotorSpeed_level=0;
}
void SaveSpeedLevel(void)  //���� �ٶȵ�λ��
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&MotorSpeed_level;
add=ORIGINAL_25PEADD+54;
Write_25pe_data(psize, add, 1);
}*/
void ReadMachineType(void)  //��������
{
Int32U add;
add=ORIGINAL_25PEADD+54;
FastRead_Datas_Start(add);
MotorType=ReadFlash_Datas();
FlashChip_Dis;
if(MotorType>MOTOR_AC_SERVO)
	MotorType=MOTOR_FREQ_5_SPD_RST;	//0  ------��Ƶ��5��
}
void SaveMachineType(void)  //��������
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&MotorType;
add=ORIGINAL_25PEADD+54;
Write_25pe_data(psize, add, 1);
}

void ReadPressValid_flag(void)  //ѹֽ ��Ч��־
{
Int32U add;
add=ORIGINAL_25PEADD+55;
FastRead_Datas_Start(add);
PressValid_flag=ReadFlash_Datas();
FlashChip_Dis;
if(PressValid_flag>1)
	PressValid_flag=0;
}
void SavePressValid_flag(void)
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&PressValid_flag;
add=ORIGINAL_25PEADD+55;
Write_25pe_data(psize, add, 1);
}


void ReadACMotorSpeed(void)   //�����ŷ� �ٶ�
{
Int32U add;
add=ORIGINAL_25PEADD+60;
FastRead_Datas_Start(add);
AC_MotorSPD=ReadFlash_Datas();
FlashChip_Dis;
if(AC_MotorSPD>32)//
	AC_MotorSPD=0;
}

void SaveACMotorSpeed(void)   //�����ŷ� �ٶ�
{
pInt8U psize;
Int32U add;
psize=(pInt8U)&AC_MotorSPD;
add=ORIGINAL_25PEADD+60;
Write_25pe_data(psize, add, 1);
}

void ReadElectricWheelSwitch(void)//��������
{
Int32U add;
// pInt8U pdata;
add=ORIGINAL_25PEADD+61;
FastRead_Datas_Start(add);
ElectricWheelOn_flag=ReadFlash_Datas();
FlashChip_Dis;
if(ElectricWheelOn_flag>1)
	ElectricWheelOn_flag=0;
}
void SaveElectricWheelSwitch(void)//��������
{
Int32U add;
pInt8U pdata;
add=ORIGINAL_25PEADD+61;
pdata=(pInt8U)&ElectricWheelOn_flag;
Write_25pe_data(pdata, add, 1);
}

void ReadIRValidStatus(void)	//IR set
{
Int32U add;
// pInt8U pdata;
add=ORIGINAL_25PEADD+62;
FastRead_Datas_Start(add);
IR_SensorStus=ReadFlash_Datas();
FlashChip_Dis;
if(IR_SensorStus>1)
	IR_SensorStus=0;
}
void SaveIRValidStatus(void)
{
Int32U add;
pInt8U pdata;
add=ORIGINAL_25PEADD+62;
pdata=(pInt8U)&IR_SensorStus;
Write_25pe_data(pdata, add, 1);
}

void ReadACJogLevel(void)//ACJog
{
Int32U add;
// pInt8U pdata;
add=ORIGINAL_25PEADD+63;
FastRead_Datas_Start(add);
JogLevel=ReadFlash_Datas();
FlashChip_Dis;
if((JogLevel>5)||(JogLevel<1))
	JogLevel=1;
}
void SaveACJogLevel(void)//ACJog 
{
Int32U add;
pInt8U pdata;
add=ORIGINAL_25PEADD+63;
pdata=(pInt8U)&JogLevel;
Write_25pe_data(pdata, add, 1);
}

void ReadFrontValidStatus(void)//ǰ����valid
{
Int32U add;
// pInt8U pdata;
add=ORIGINAL_25PEADD+64;
FastRead_Datas_Start(add);
Front_LimitValid_flag=ReadFlash_Datas();
FlashChip_Dis;
}
void SaveFrontValidStatus(void)//
{
Int32U add;
pInt8U pdata;
add=ORIGINAL_25PEADD+64;
pdata=(pInt8U)&Front_LimitValid_flag;
Write_25pe_data(pdata, add, 1);	
}
void ReadMiddleValidStatus(void)//ǰ����valid
{
Int32U add;
// pInt8U pdata;
add=ORIGINAL_25PEADD+65;
FastRead_Datas_Start(add);
Middle_LimitValid_flag=ReadFlash_Datas();
FlashChip_Dis;
}
void SaveMiddleValidStatus(void)//
{
Int32U add;
pInt8U pdata;
add=ORIGINAL_25PEADD+65;
pdata=(pInt8U)&Middle_LimitValid_flag;
Write_25pe_data(pdata, add, 1);	
}
void ReadBackValidStatus(void)//ǰ����valid
{
Int32U add;
// pInt8U pdata;
add=ORIGINAL_25PEADD+66;
FastRead_Datas_Start(add);
Back_LimitValid_flag=ReadFlash_Datas();
FlashChip_Dis;
}
void SaveBackValidStatus(void)//
{
Int32U add;
pInt8U pdata;
add=ORIGINAL_25PEADD+66;
pdata=(pInt8U)&Back_LimitValid_flag;
Write_25pe_data(pdata, add, 1);	
}

//*******
void GeneratePassCode(void) //��������
{
Int32U temp;
srand(sys_tick);
temp=rand();
while(temp>100000)
	{
	temp=rand();
	}
	
//PassCheck=temp%100000;
PassCheck=temp;
PassCode=PASSCODE_formula(PassCheck);
}

void PassCheck_dis(Int16U x, Int16U y) //������ʾ
{
Int8U num[6],n=0;
Int16U color=0xfc00;
GeneratePassCode();//��������
num[n++]=PassCheck/10000;
num[n++]=(PassCheck/1000)%10;
num[n++]=(PassCheck/100)%10;
num[n++]=(PassCheck/10)%10;
num[n++]=PassCheck%10;
for(n=0;n<5;n++)
	{
	num[n]+=48;
	}
num[n]=0;
Printf24(num,x,y,color,1,0xffff);//
}

Int16U Caluate_Days(void)
{
Int16U y1,m1,d1;
Int16U y2,m2,d2,time,days=0;
ReadWorkDays();
read_time();
y1=((Year>>4)&0x0f)*10+(Year&0x0f);
m1=((Month>>4)&0x0f)*10+(Month&0x0f);
d1=((Dom>>4)&0x0f)*10+(Dom&0x0f);
y2=((Start_days.year>>4)&0x0f)*10+(Start_days.year&0x0f);
m2=((Start_days.month>>4)&0x0f)*10+(Start_days.month&0x0f);
d2=((Start_days.day>>4)&0x0f)*10+(Start_days.day&0x0f);
if(y1>=y2)//ʱ����ȷ
	{
	time=y1-y2;
	if(time>1)
		days=400; //ʱ�䵽
	else
		{
		if(time>0)
		   {
		   days=(12-m2+1)*30-d2;//��ǰ ʣ������
		   days+=(m1-1)*30+d1;
		   }
		else //����
		   {
		   if(m1>=m2)
			   {
			   time=m1-m2;
			   if(time>0)
				   {
					days=time*30+d1-d2;
				   }
			   else	
				   {
				   if(d1>=d2)
				      days=d1-d2;
				   }
			   }
		   }
		}
	}
return days;	
}

void DaysTime_check(void)
{
Int16U days;
//x=PASSCODE_X,y=PASSCODE_Y;
if(FirstDayValid_flag==1) //�״� ʱ������ ��Ч
	{
	days=Caluate_Days();
	Past_days=days; 
	if(Past_days>=FirstDays)// ʱ�� ��
		{
		PassCodeEn_flag=1;
		}
	}
else
	{
	if(SecondDayValid_flag==1)
		{
		days=Caluate_Days();
		Past_days=days;  
		if(Past_days>=SecondDays)// ʱ�� ��
			{
			PassCodeEn_flag=1;
			}
		}
	}
}

void RunTo_cursor(void) //������ ��괦
{
pInt8U pKdata;
Int32U size_data;

pKdata=(pInt8U)&OneKnife_data;
GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKdata);//
size_data=OneKnife_data.size;
if((size_data>=Size_MIN_num)&&(size_data<=Size_MAX_num))//������Ч
	{
	
	//SelfLockEn_flag=0;
	//ToTargetStop_flag=0;
	//if(1)
	if(size_data!=CurrentSize)
		{
		if(Unit==UNIT_MM)//mm
			{
			TargetSize=size_data;
			}
		else
			{
			TargetSize_inch=size_data;
			TargetSize=TargetSize_inch*2.54;
			}
			/////////////////////////////ǰ10mm ����///��ֽ////////////////////////////
		if((OneKnife_data.k_flag==PUSH_FLAG)&&(Knife_order<Knife_sum))//��ֽ λ����ǰ10mm ����
			{
			if(CurrentSize>TargetSize)
				{
				if(CurrentSize-TargetSize>=1000)
					{
					TargetSize+=1000;
					}
				}
			else
				{
				if(TargetSize-CurrentSize>=1000)
					{
					TargetSize-=1000;
					}
				}
			}	
		TargetSize_temp=TargetSize;
		switch(MotorType)
			{
			case MOTOR_FREQ_5_SPD_RST:
			case MOTOR_FREQ_3_SPD:
			case MOTOR_FREQ_3_SPD_RST:
				 SelfLockEn_flag=0;
				 ToTargetStop_flag=0;
				 MoveSpeed=0;
				 MoveSpeedCtrl();  //�����ٶȿ���
					break;
			case MOTOR_DC_SERVO:
			case MOTOR_DC670_SERVO:
			case MOTOR_DC670_SERVO_ZHU:
				 ServoSendCou=0;
				 DcServoStartRun_exec(TargetSize);
				// SelfLockEn_flag=0;
					break;
			case MOTOR_AC_SERVO:
				 ACMotorRunStart(TargetSize);
					break;		
			}
		RunStop_flag=0;
		Run_flag=1;
		InTargetPosit_flag=0;	//Ŀ��λ��
		AutoCutStart_flag=0;
		PromptNum_dis();
		}
	}
}
void AutoRun_start(void)
{
pInt8U pKdata;
Int32U size_data,size_now;

pKdata=(pInt8U)&OneKnife_data;
GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKdata);//
size_data=OneKnife_data.size;
if(Unit==UNIT_MM)//mm
	{
	if(InTargetPosit_flag==1) 	//Ŀ��λ��
		size_now=TargetSize_temp;
	else	
		size_now=CurrentSize;
	}
else
	{
	if(InTargetPosit_flag==1) 	//Ŀ��λ��
		size_now=TargetSize_inch;
	else	
		size_now=CurrentSize*100/254;
	}
if((size_data>=Size_MIN_num)&&(size_data<=Size_MAX_num))//������Ч
	{
	if(size_now==size_data)
		AutoRun_AutoPush_exec();  // �Զ� ѭ������
	else 
		RunTo_cursor();//    ���е���ǰ��
	}
}



//===================================������===========================
void Calcul_Nums(Int8U a_n1,Int8U a_n2,Int8U b_n1,Int8U b_n2, Int8U sign)  //�����������  ���㣨3λС����*1000�� �ý������CalcData_temp
{
Int8U i,j,num_a[8],num_b[8];
Int64U d_temp1,d_temp2;
Int32U data;
d_temp1=0;
i=a_n1;
while(i<=a_n2)
	{
	if(CalcInput_Text[i]!='.')
		{
		d_temp1=d_temp1*10+CalcInput_Text[i];
		i++;
		}
	else
		{
		i++;
		break;
		}
	}
j=0;	
while(j<3)
	{
	if(i<=a_n2)
		{
		d_temp1=d_temp1*10+CalcInput_Text[i];
		i++;
		}
	else
		{
		d_temp1*=10;
		}
	j++;
	}	
//----------
d_temp2=0;
i=b_n1;
while(i<=b_n2)
	{
	if(CalcInput_Text[i]!='.')
		{
		d_temp2=d_temp2*10+CalcInput_Text[i];
		i++;
		}
	else
		{
		i++;
		break;
		}
	}
j=0;	
while(j<3)
	{
	if(i<=b_n2)
		{
		d_temp2=d_temp2*10+CalcInput_Text[i];
		i++;
		}
	else
		{
		d_temp2*=10;
		}
	j++;
	}	
switch(sign)
	{
	case '+':
		data=d_temp1+d_temp2;
		break;
	case '-':
		if(d_temp1>=d_temp2)         //�޷��� ��ֹ���
			data=d_temp1-d_temp2;   
		else
			data=0;
		break;
	case '*':
		data=(d_temp1*d_temp2)/1000;
		break;
	case '/':
		data=d_temp1*1000/d_temp2;
		break;	
	}
CalcData_temp=data;
}

void DataConvert_to_Text(Int32U data_temp,pInt8U str_text)  //data_temp ת����bcd �ַ�
{
Int8U i=0,j,n;
Int8U nums[12];
nums[i++]=data_temp/100000000;
nums[i++]=(data_temp/10000000)%10;
nums[i++]=(data_temp/1000000)%10;
nums[i++]=(data_temp/100000)%10;
nums[i++]=(data_temp/10000)%10;
nums[i++]=(data_temp/1000)%10;
nums[i++]='.';
nums[i++]=(data_temp/100)%10;
nums[i++]=(data_temp/10)%10;
nums[i++]=data_temp%10;
//nums[i]=0xff;
j=0;i=7;
while(j<6)
	{
	if(nums[j]==0)
		j++;
	else
		break;
	}
while(i<10)
	{
	if(nums[i]==0)
		i++;
	else
		break;	
	}	
//****	
n=0;CalcInput_cou=0;
if(i>=10)  //��С������
	{
	if(j>5)   //  �������� ȫΪ 0
		{
		str_text[n++]=0;
		CalcInput_cou=1;
		while(n<24)
			str_text[n++]=0xff;
		}
	else
		{    //��������  ��0
		while(n<24)
			{
			if(j<6)
				{
				str_text[n++]=nums[j];
				CalcInput_cou++;
				j++;
				}
			else
				{
				str_text[n++]=0xff;
				}
			}
		}
	}	
else
	{
	if(j>5)//  �������� ȫΪ 0
		{
		j=5;
		}
	while(n<24)
		{
		if(j<10)
			{
			str_text[n++]=nums[j];
			CalcInput_cou++;
			j++;
			}
		else
			{
			str_text[n++]=0xff;
			}
		}
	}	
}

void CalculatorValue_exec(Int8U sign)  //���� ���ż���ֵ ����
{
Int8U sign_temp;
Int32U datas;
Int8U last_num;
num_cou=0;
Dot_flag=0;
if(CalcResultDis_flag==1)   //   �ѵõ�  ������ 
	{
	last_num=CalcResult_Text[CalcInput_cou-1];   //����� ���һ���ַ�
	}
else
	{
	last_num=CalcInput_Text[CalcInput_cou-1];   //�����  ���һ���ַ�
	}
	
if(CalcNoNumInput_flag==1)         //����ĸ  Ϊ����
	{
	CalcNoNumInput_flag=0;
	CurrentToCalc_input();  //��ǰ�ߴ� ���ݸ��µ�������
	CalcSign_order=CalcInput_cou; //���� λ��
	CalcInput_Text[CalcInput_cou++]=sign;
	CalcInputNums_dis(CalcInput_Text);
	}
else
	{
	if(last_num<42)  // ����Ϊ ����
		{
		if(CalcSign_order<1)  //-----------�׸������  ֻ��ʾ
			{
			if(CalcResultDis_flag==1)   //   �ѵõ�  ������        
				{
				CalcResultDis_flag=0;  //�����ʾ ��־
				ClrCalcNums_text(CalcInput_Text,CAL_INPUT); 
				DataConvert_to_Text(CalcData_temp,CalcInput_Text);  //������ ���µ�  �����
				}
			CalcSign_order=CalcInput_cou; //���� λ��
			CalcInput_Text[CalcInput_cou++]=sign;
			CalcInputNums_dis(CalcInput_Text);
			}
		else            //-------------��������  
			{
			if(CalcResultDis_flag==1)   //   �ѵõ�  ������        
				{
				CalcResultDis_flag=0;  //�����ʾ ��־
				}
			else
				{
				sign_temp=CalcInput_Text[CalcSign_order];   //��ȡ�����
				Calcul_Nums(0,CalcSign_order-1  ,CalcSign_order+1,CalcInput_cou-1,sign_temp);//���� �������ݽ�� CalcData_temp
				}
			ClrCalcNums_text(CalcInput_Text,CAL_INPUT); //������� �����
			DataConvert_to_Text(CalcData_temp,CalcInput_Text);  //������ ���µ�  �����
			if(CalcInput_cou==0)
				CalcInput_cou++;
			CalcSign_order=CalcInput_cou; //�׸�������� λ��
			CalcInput_Text[CalcInput_cou++]=sign;
			CalcInputNums_dis(CalcInput_Text);
			}
		}
	}	

}

void CalcGetValue_exec(void)             //= ���� ���ý��
{
Int8U signal;
Dot_flag=0;
if((CalcInput_Text[CalcInput_cou-1]<42)&&(CalcInput_cou>0))  //�����Ϊ���� �������
	{
	if(CalcSign_order>0)  //���� ���� ���
		{
		signal=CalcInput_Text[CalcSign_order];  //����� 
		Calcul_Nums(0,CalcSign_order-1  ,CalcSign_order+1,CalcInput_cou-1,signal);//���� �������ݽ�� CalcData_temp
		}
	else  // ֱ����ʾ �� �����
		{
		CalcInput_Text[CalcInput_cou]=0;
		Calcul_Nums(0,CalcInput_cou-1,CalcInput_cou,CalcInput_cou,'+');//���� ����������+0����� CalcData_temp
		}
	//-------------��������ʾ
	ClrCalcNums_text(CalcResult_Text,CAL_RESULT); //������� �����
	DataConvert_to_Text(CalcData_temp,CalcResult_Text);  //������	 ת��Ϊ�ַ�	
	CalcResultNums_dis(CalcResult_Text);//����� ��ʾ	
	
	CalcResultDis_flag=1;
	}
}
//===================================������===========================

void AutoRun_AutoPush_exec(void)  // �Զ� ѭ������
{
pInt8U pKdata;
Int32U size_data;
Int32U size_dd,data,AutoPush_num;
pKdata=(pInt8U)&OneKnife_data;
AutoRoute_flag=1;
if((AutoPushDistance>AUTO_PUSH_NO)&&(AutoPushDistance<=AUTO_PUSH_DISTAN))  //�Զ���ֽ ��Ч
	{
	if(AutoPushRun_flag==0)   //δ���е� �Զ���ֽ ����
		{
		GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKdata);//
		size_data=OneKnife_data.size;
		GetOneKnife_datas(Pro_data.pro_num, Knife_order+1, pKdata);//
		
		if(size_data<OneKnife_data.size)  //��ǰ<��һ��      
			{
			if((size_data>=Size_MIN_num)&&(size_data<=Size_MAX_num))  //��ǰ�ߴ�  ��Ч
				{
				if(Unit==UNIT_MM)//mm
					AutoPush_num=AutoPushDistance;
				else	
					AutoPush_num=AutoPushDistance*100/254;
				if(size_data>AutoPush_num)
					{
					size_dd=size_data-AutoPush_num;
					if(size_dd>Size_MIN_num)
						data=size_dd;
					else
						data=Size_MIN_num;
					
					if(Unit==UNIT_MM)//mm
						{
						TargetSize=data;
						}
					else
						{
						TargetSize_inch=data;
						TargetSize=TargetSize_inch*2.54;
						}
					if(CurrentSize!=TargetSize)
						{
						TargetSize_temp=TargetSize;
						switch(MotorType)
							{
							case MOTOR_FREQ_5_SPD_RST:
							case MOTOR_FREQ_3_SPD:
							case MOTOR_FREQ_3_SPD_RST:
								 SelfLockEn_flag=0;
								 ToTargetStop_flag=0;
								 MoveSpeed=0;
								 MoveSpeedCtrl();  //�����ٶȿ���
									break;
							case MOTOR_DC_SERVO:
							case MOTOR_DC670_SERVO:
							case MOTOR_DC670_SERVO_ZHU:
								 ServoSendCou=0;
								 DcServoStartRun_exec(TargetSize);
								// SelfLockEn_flag=0;
									break;
							case MOTOR_AC_SERVO:
								 ACMotorRunStart(TargetSize);
									break;		
							}
						Run_flag=1;
						RunStop_flag=0;
						InTargetPosit_flag=0;	//Ŀ��λ��
						AutoPushRun_flag=1;
						AutoCutStart_flag=0;
						CursorDown_inTable();//**** ������� ��ʾ ����
						PromptNum_dis();
						}
					
					}
				else
					{
					if(Unit==UNIT_MM)//mm
						{
						TargetSize=Size_MIN_num;
						}
					else
						{
						TargetSize_inch=Size_MIN_num;
						TargetSize=TargetSize_inch*2.54;
						}
						/////////////////////////////ǰ10mm ����///��ֽ////////////////////////////
					if((OneKnife_data.k_flag==PUSH_FLAG)&&(Knife_order<Knife_sum))// λ����ǰ10mm ����
						{
						if(CurrentSize>TargetSize)
							{
							if(CurrentSize-TargetSize>=1000)
								{
								TargetSize+=1000;
								}
							}
						else
							{
							if(TargetSize-CurrentSize>=1000)
								{
								TargetSize-=1000;
								}
							}
						}
					if(CurrentSize!=TargetSize)	
						{
						TargetSize_temp=TargetSize;	
						switch(MotorType)
							{
							case MOTOR_FREQ_5_SPD_RST:
							case MOTOR_FREQ_3_SPD:
							case MOTOR_FREQ_3_SPD_RST:
								 SelfLockEn_flag=0;
								 ToTargetStop_flag=0;
								 MoveSpeed=0;
								 MoveSpeedCtrl();  //�����ٶȿ���
									break;
							case MOTOR_DC_SERVO:
							case MOTOR_DC670_SERVO:
							case MOTOR_DC670_SERVO_ZHU:
								ServoSendCou=0;
								 DcServoStartRun_exec(TargetSize);
								// SelfLockEn_flag=0;
									break;
							case MOTOR_AC_SERVO:
								ACMotorRunStart(TargetSize);
								// SelfLockEn_flag=0;
									break;
							}
						Run_flag=1;
						RunStop_flag=0;
						InTargetPosit_flag=0;	//Ŀ��λ��
						AutoPushRun_flag=1;
						AutoCutStart_flag=0;
						CursorDown_inTable();//**** ������� ��ʾ ����
						PromptNum_dis();

						}
					}
				}
			}
		else//ֱ��  ���е� ��һ��
			{
			CursorDown_inTable();//**** ������� ��ʾ ����
			RunTo_cursor();//    ���е���һ��
			AutoPushRun_flag=0;
			}
		}
	}
else   //ֱ��  ���е� ��һ��
	{
	CursorDown_inTable();//**** ������� ��ʾ ����
	RunTo_cursor();//    ���е���һ��
	AutoPushRun_flag=0;
	}	
AutoRoute_flag=0;	
}

void StopMotorExec(void)  //��Ƶ  motorֹͣ
{
ForceStop_flag=0;
BackStop_flag=0;
Backward_flag=0;
Forward_flag=0;	
//SelfLockEn_flag=0; //ȡ������


Run_flag=0;	
InTargetPosit_flag=0;	//Ŀ��λ��
//AutoPushRun_flag=0; //�Զ���ֽ ����
//TargetSize=0;
//TargetSize_temp=0;
//BeforeKnife_offset_in=0;
if(InputTouch_flag==0)
	{
//	ClrInput_function();//���� �����
	}
//PaperCutEnb_signal=1;	
//AutoRoute_flag=0;                                                        
}



void CheckKnifeSum_exec(void)  //--------------�ܵ���    �˶�
{
pInt8U pKdata;
Int32U size_data;
Int32U size_temp;
Int16U knife_temp;

pKdata=(pInt8U)&OneKnife_data;
GetOneKnife_datas(Pro_data.pro_num, Knife_sum, pKdata);//��ȡ ���һ��
size_data=OneKnife_data.size;
if((size_data>=Size_MIN_num)&&(size_data<=Size_MAX_num))  //��ǰ�ߴ�  ��Ч  �����²��ң�-----�������  ��Ӱ��
	{
	knife_temp=Knife_sum+1;
	while(knife_temp<=MAIX_Knife)
		{
		GetOneKnife_datas(Pro_data.pro_num,knife_temp , pKdata);//��ȡ ��һ��  (��ȷӦΪ0)
		size_temp=OneKnife_data.size;
		if((size_temp>=Size_MIN_num)&&(size_temp<=Size_MAX_num))  //��ǰ�ߴ�  ��Ч
			{
			knife_temp++;
			}
		else
			{
			break;
			}
		}
		
	if(knife_temp>Knife_sum+1)//��������  ����
		{
		Knife_sum=knife_temp-1;
		SaveKnife_sum(Pro_data.pro_num);//���� ����  
		if(WorkStart_flag==1)
			StepNum_dis(Knife_sum,Knife_order);//�������
		}
	}
else	//�ߴ���Ч   �����ϲ��ң�
	{
	knife_temp=Knife_sum-1;
	while(knife_temp>1)
		{
		GetOneKnife_datas(Pro_data.pro_num,knife_temp , pKdata);//��ȡ ǰһ��  (��ȷӦ�ڼ��޷�Χ)
		size_temp=OneKnife_data.size;
		if((size_temp>=Size_MIN_num)&&(size_temp<=Size_MAX_num))  //��ǰ�ߴ�  ��Ч
			{
			break;
			}
		else
			{
			knife_temp--;
			}
		}
	if(knife_temp<1)
		{
		if(Knife_sum!=1)
			{
			Knife_sum=1;
			SaveKnife_sum(Pro_data.pro_num);//���� ����  
			ClrBuf_datas(Pro_data.pro_num, 1,MAIX_Knife);  //���� ������buf
			ReadOnePro_datas(Pro_data.pro_num);//��ȡ ��ǰpro
			if(WorkStart_flag==1)
				StepNum_dis(Knife_sum,Knife_order);//�������
			}
		}
	else
		{
		Knife_sum=knife_temp;
		SaveKnife_sum(Pro_data.pro_num);//���� ����
		ClrBuf_datas(Pro_data.pro_num, 1,MAIX_Knife);  //���� ������buf
		ReadOnePro_datas(Pro_data.pro_num);//��ȡ ��ǰpro
		if(WorkStart_flag==1)
			StepNum_dis(Knife_sum,Knife_order);//�������
		}
	}
}



void GetAC_MotorSpeed(void)  //�����ŷ�  �ٶ��ж�
{
Int16U j;
//ReadACMotorSpeed();
switch(AC_MotorSPD)
	{
	case 0:   //0--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb1[j];
			break;
	case 1:   //1--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb2[j];
			break;	
	case 2:   //2--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb3[j];
			break;
	case 3:   //3--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb4[j];
			break;	
	case 4:   //4--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb5[j];
			break;
	case 5:   //5--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb6[j];
			break;	
	case 6:   //6--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb7[j];
			break;	
	case 7:   //7--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb8[j];
			break;	
	case 8:   //8--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb9[j];
			break;
	case 9:   //9--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb10[j];
			break;	
	case 10:   //10--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb11[j];
			break;
	case 11:   //11--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb12[j];
			break;		
	//******************************++++++++++++++++++++++++++++++++++			
	case 12:   //2--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb13[j];
			break;
	case 13:   //3--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb14[j];
			break;	
	case 14:   //4--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb15[j];
			break;
	case 15:   //5--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb16[j];
			break;	
	case 16:   //6--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb17[j];
			break;	
	case 17:   //7--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb18[j];
			break;	
	case 18:   //8--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb19[j];
			break;
	case 19:   //9--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb20[j];
			break;	
	case 20:   //10--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb21[j];
			break;
	case 21:   //11--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb22[j];
			break;				
	case 22:   //10--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb23[j];
			break;
	case 23:   //11--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb24[j];
			break;			
//************20180516			
	case 24:   //11--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb25[j];
			break;				
	case 25:   //10--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb26[j];
			break;
	case 26:   //11--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb27[j];
			break;					
	case 27:   //10--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb28[j];
			break;
	case 28:   //11--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb29[j];
			break;			
	case 29:   //11--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb30[j];
			break;				
	case 30:   //10--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb31[j];
			break;
	case 31:   //11--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb32[j];
			break;	
	case 32:   //11--�ٶ�
			for(j=0;j<120;j++)
				waitTemp[j]=waitTb33[j];
			break;	
	}
}

