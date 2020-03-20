/*

��ɨ��   1MS����һ��


*/

#include"key.h"
//#include"at45dbnew.h"
#include"m25pe16.h"
#include"chndot.h"
//#include"realtime.h"
#include"io.h"
#include "timer.h" //  ������ָ�

#include "pic_exec.h"

#include "test_io.h"
#include "modbus.h"


#include"port.h"
#include"servo.h"
#include"keyboard.h"

#include"name_input.h"

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


unsigned int Total_size=0;//�ܳ�
unsigned int Label_size=0;//��ǩ��
unsigned int Waste_size=0;//�ϱ�
unsigned int Divide_num=0;//�ȷ���
 

unsigned char cursor_pro;
unsigned long int maichongdangliang,xxmuqiancn;





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
Int32U Z_Pulse_before;
Int8U Z_Pulse_start_flag;
Int8U Z_Pulse_err_flag;
Int32U PulseAB_Z_current;
Int8U PulseAB_Z_save_time=0;

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
Int8U SubLine_flag;

Int16U FirstKnife_num;
Int16U LastKnife_num_temp;

Int8U MainMode_temp;
Int8U F5AllKnifeF_SetFlag;

Int8U PressCircle_mode=0;
Int8U AutoCutDisable_flag=0;


void BellOn_Enb(void)
{
labatime=0;
 BellOUT_ON;flaglaba=1;
}


void KeyScan(void)  //��ɨ��   1MS����һ��
{
unsigned long int j;  

// // Key_Enable(ENABLE);
// // if(KeyDown_Flag==0)
	// // {
// // //	KeyCode=KEYIO;   //�������  ��ͬ�Ķ˿�״̬�޸Ĵ���
	// // if(KeyCheck()!=0)   //�ж��Ƿ��м�����
		// // {
		// // KeyDown_Flag=1;    //�ü����±�־λ
		// // KeyDownTime=0;
		// // }
	// // }
// // else
	// // {
	// // if(KeyExec_Flag==0)
		// // {
	// // //	KeyCode=KEYIO;   //�������  ��ͬ�Ķ˿�״̬�޸Ĵ���
		// // if(KeyCheck()!=0)   //�ж��Ƿ��м�����
			// // {
			// // KeyDownTime++;
			// // if(KeyDownTime>=20)  //���¼� ȥ����10MS
				// // {
				// // KeyDownTime=0;
				// // KeyReadCode();//��ȡ��ֵ 
				// // KeyCode_Temp=KeyCode;

				// // ////////////////////////////
                                  // // flagkeysong=0;
				// // //  ����Ϊ�����´���
				// // ////////////////////////////
				// // switch(Board_TestMod)
					// // {
					// // case 0:
					// // case TEST_TOUCH:
					// // case TEST_ICON:
						// // KeyExec(KeyCode); //��������
							// // break;
					// // case TEST_BOARD://���� ģʽ  3
						// // BellOn_Enb();
						// // KeyDis_sel(KeyCode_Temp,1);  //***************������ʾ 
							// // break;
					// // case TEST_SYS_TYPE://�趨  ��λ4
						// // BellOn_Enb();
						// // ShiftSpeed_SetExec(KeyCode); 
							// // break;
					// // }
				// // KeyExec_Flag=1; //�ü������־λ
				// // }
			// // }
		// // else
			// // {  //���������˳�
			// // KeyDown_Flag=0;
			// // }
		// // }
	// // else
		// // {
// // //		KeyCode=KEYIO;   //�������  ��ͬ�Ķ˿�״̬�޸Ĵ���
		// // if(KeyCheck()==0)   //�ж��Ƿ��м�����		if(KeyCode==0)
			// // {
			// // KeyDownTime++;
			// // if(KeyDownTime>=10)  //------------�ͷż� ȥ����10MS
				// // {
				// // KeyDown_Flag=0;   //�尴�±�־λ
				// // KeyExec_Flag=0;   //��������־λ
				// // KeyLongDownTime=0;  //���������ʱ
				// // //KeyLongDown_Flag=0;
                 // // LongExec_flag=0;  
				// // ////////////////////////////
				// // GoFrontEn_flag=0;
				// // GoBackEn_flag=0;
				// // if(Board_TestMod==TEST_BOARD)
					// // {
					// // KeyDis_sel(KeyCode_Temp,0); //***************������ʾ
					// // MoveStop();
					// // RLOUT1_OFF;    // �������
					// // }
					
				// // //----------------------------------------
				
				
				 // // ACMotor_ReleaseStop();  //-------
				 	
				// // }
			// // }
		// // else
			// // {
			// // KeyDownTime=0;
			
			// // if(LongExec_flag==0)
			    // // {
				  // // KeyReadCode();//��ȡ��ֵ
				  // // MultiKey_exec(KeyCode);  //��ϼ�����
				  // // //if(KeyCode!=KeyCode_Temp)
				   // // //  {
					 
					// // // }
				// // }
			
			// // if(KeyLongDownTime<KEYLONGDOWNTIMEDATA)
				// // {
				// // KeyLongDownTime++;
                // // }             
			// // else//----------��������------------
			   // // {
			   // // if(LongExec_flag==0)
			      // // {
				  // // LongExec_flag=1;
				  // // //KeyReadCode();//��ȡ��ֵ
				  // // LongKey_exec(KeyCode , KeyCode_Temp);  //����������
				  // // }
			   // // }
								
			// // }
		// // }
	// // }
// // Key_Enable(DISABLE);
}

void NumKey_exec(Int8U num)
{
Int8U c_t;
volatile Int16U temp=0;
if(WorkStart_flag==1)
	{
	if(Run_flag==0)
		{
		if(WorkMode==READ_PRO_MESS_MODE)
			{
			ProNameInput_dis(num);	//���뷨
			}
		else
			{
			if(CalcResultDis_flag==1)
				{
				ClrCalcNums_text(CalcInput_Text,CAL_INPUT); //������� �����
				CalcInput_cou=0;
				num_cou=0;
				CalcResultDis_flag=0;  //�����ʾ ��־
				CalcSign_order=0;//�׸������ λ��
				}
			if(num_cou<7)//
				{		
				CalcNoNumInput_flag=0;	
				if(num!='.')
					{
					CalcInput_Text[CalcInput_cou++]=num;
					CalcInputNums_dis(CalcInput_Text);	
					num_cou++;
					}
				else
					{
					if(Dot_flag==0)	
						{
						Dot_flag=1;
						CalcInput_Text[CalcInput_cou++]=num;
						CalcInputNums_dis(CalcInput_Text);	
						num_cou++;
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
	else if(Board_TestMod==TEST_SYS_WORD)//  ϵͳ�汾ѡ��  ����
		{
		if((num_cou<6)&&(num!='.'))
			{
			Size_temp[num_cou++]=num;
			SysBoardNum_dis(Size_temp,num_cou);//����
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
num_cou=0;
}
void CalcuInClear_exec(void)     //��� ������
{
// CurrentArea_recover3(CALCUL_WIN_X,CALCUL_WIN_Y,CALCUL_WIDE,CALCUL_HIGH);
// ButtonTouch_mode=0;
// Dot_flag=0;
// num_cou=0;

// CalcResultDis_flag=0;
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


//------------
void ArithmeticInputSize(void)  //�Ե�ǰ�ߴ� ��������
{
volatile Int32U newsize_temp=0,prev_data;
volatile Int8U Flg_chg=0,flag_now;
if((Knife_order<=MAX_Knife)&&(Knife_order>1))	//������ δ��
	{
	CheckInputNums();
	if(InputSize>0)
		{
		pKnife_data=(pInt8U)&OneKnife_data;
		GetOneKnife_datas(Pro_data.pro_num, Knife_order-1, pKnife_data);// ��ȡ��ǰ�� �ߴ�
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
			GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//�ߴ������
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
				case INDONSIA:	//ӡ��	
						Printf24("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
				case PORTUGAL:	//������
						Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
						break;
				case SPANISH: //������
						Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
						break;
				}
			
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
			RenewModifyDate();	//����ʱ����Ϣ-.-.-.-.-.-.-.-.-.-.-.-.-.-
			//----��������----------------
			GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);// ��ȡ  ��ǰ��
			OneKnife_data.size=newsize_temp;  //�ߴ��޸�
			if((OneKnife_data.k_flag&0xf)==KNIFE_FLAG)
				{
				if(newsize_temp>prev_data)
					{
					OneKnife_data.k_flag&=0xf0; //�� ��־���
					Flg_chg=1;
					flag_now=OneKnife_data.k_flag;
					}
				}
			SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//����һ������
			//************next
			if((Knife_order+1)<=OnePro_head.pro_knifeSUM)
				{
				GetOneKnife_datas(Pro_data.pro_num, Knife_order+1, pKnife_data);// ��ǰ������һ�� ����
				 if((OneKnife_data.k_flag&0xf)==KNIFE_FLAG) //�� ��־
					{
					if(OneKnife_data.size>newsize_temp)
						{
						OneKnife_data.k_flag&=0xf0;	//��� �� ��־
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
			//---------��ʾ----	
			if(Knife_order>OnePro_head.pro_knifeSUM)//���²��� �ܵ���
				{
				OnePro_head.pro_knifeSUM=Knife_order;		//
				SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);
				}
			if(Knife_order<MAX_Knife)	//������ δ��---------------����
				{
				Knife_order++;
				if(cursor_row<(PageKf_Size-1))
					{
					CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
					OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //һ������ ������ʧ
					cursor_row++;
					CursorKnife_dis(cursor_row, 1);//��ɫ���������ʾ
					OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //һ������ ������ʾ
					// // if((ButtonTouch_mode==0)||(ButtonTouch_mode==TOU_MODE_F4)) //	 �� ���������� ��
					if(ButtonTouch_mode==0) //	 �� ���������� ��
						{
						switch(Flg_chg)
							{
							case 1:
								AllFlagPic_dis(cursor_row,flag_now); // ���ͼƬ ��ʾ
								break;
							case 2:
								AllFlagPic_dis(cursor_row+1,OneKnife_data.k_flag); //��괦 ���ͼƬ ��ʾ
								break;
							case 3:
								AllFlagPic_dis(cursor_row,flag_now); // ���ͼƬ ��ʾ
								AllFlagPic_dis(cursor_row+1,OneKnife_data.k_flag); //��괦 ���ͼƬ ��ʾ
								break;
							}
						}
					}
				else   //ҳ��
					{
					Size_1page_dis(Knife_order-(PageKf_Size-1),0);//һҳ�ߴ���ʾ
					}
				}
			StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//�������	
			//--------������ ��ʾ	
			/***
			if(Knife_order<=OnePro_head.pro_knifeSUM)  //���� δ������ 000.00
				{
				Knife_order++;
				GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);// ��ȡ  ��һ��
				OneKnife_data.size=newsize_temp;  //�ߴ��޸�
				if(Knife_order<=OnePro_head.pro_knifeSUM)// δ�������һ��
					{
					if((OneKnife_data.k_flag&0xf)==KNIFE_FLAG)
						{
						if(newsize_temp>prev_data)
							{
							OneKnife_data.k_flag&=0xf0; //�� ��־���
							Flg_chg=1;
							flag_now=OneKnife_data.k_flag;
							}
						}
					}
				SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//����һ������
				if((Knife_order+1)<=OnePro_head.pro_knifeSUM)
					{
					GetOneKnife_datas(Pro_data.pro_num, Knife_order+1, pKnife_data);// ��ǰ������һ�� ����
					 if((OneKnife_data.k_flag&0xf)==KNIFE_FLAG) //�� ��־
						{
						if(OneKnife_data.size>newsize_temp)
							{
							OneKnife_data.k_flag&=0xf0;	//��� �� ��־
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
				if(Knife_order>OnePro_head.pro_knifeSUM)//���²��� �ܵ���
					{
					OnePro_head.pro_knifeSUM=Knife_order;		//
					SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);
					}
				StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//�������	
				//--------������ ��ʾ	
				
				if(cursor_row<(PageKf_Size-1))
					{
					CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
					OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //һ������ ������ʧ
					cursor_row++;
					CursorKnife_dis(cursor_row, 1);//��ɫ���������ʾ
					OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //һ������ ������ʾ
					if((ButtonTouch_mode==0)||(ButtonTouch_mode==TOU_MODE_F4)) //	 �� ���������� ��
						{
						switch(Flg_chg)
							{
							case 1:
								AllFlagPic_dis(cursor_row,flag_now); // ���ͼƬ ��ʾ
								break;
							case 2:
								AllFlagPic_dis(cursor_row+1,OneKnife_data.k_flag); //��괦 ���ͼƬ ��ʾ
								break;
							case 3:
								AllFlagPic_dis(cursor_row,flag_now); // ���ͼƬ ��ʾ
								AllFlagPic_dis(cursor_row+1,OneKnife_data.k_flag); //��괦 ���ͼƬ ��ʾ
								break;
							}
						}
					}
				else   //ҳ��
					{
					Size_1page_dis(Knife_order-(PageKf_Size-1),0);//һҳ�ߴ���ʾ
					}
				}
				**/
				 
			PromptNum_dis();//���뷶Χ ��ʾ
			PromptDis_flag=1;	
			GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//�ߴ������ ����	
			}
			
		}
	}
ClrInput_function();//���� �����
Arithmetic_mode=0;
}


/***
void ShowTouchWind(void)//��������window
{
// ClrInput_function();//���� �����
	//���� ������
CalcNoNumInput_flag=1;
Dot_flag=0;
CalcSign_order=0;//�׸������ λ��
CalcData_temp=0;
CalcResultDis_flag=0;
num_cou=0;
if(Sign_flag==1)//��� ��,����
	{
	// GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//�ߴ������
	Sign_flag=0;
	}

CalcInput_cou=0;
Calculator_Window();  //������ ��ť	
ClrCalcNums_text(CalcInput_Text,CAL_INPUT); //������� �����
ClrCalcNums_text(CalcResult_Text,CAL_RESULT); //������� ����� 
CalcInputNums_dis(CalcInput_Text);  //����� ��ʾ
CalcResultNums_dis(CalcResult_Text);//����� ��ʾ
ButtonTouch_mode=TOU_MODE_CALC;
}**/

void KeyExec(Int32U keycode)  //������....................................
{
Int32U d_temp=0;
Int32U target_temp;
Int32U input_temp,perv_data;
	 
Int16U x,y,gap,back_color,line_color,tx_wide=148;

Int16U g,K_temp;
Int8U knife_set_flag=0,Flg_chg=0,flag_now;
pInt8U pbuf;
Int32U offset;
volatile Int32U current_temp,step_temp;
BellOn_Enb();
switch(keycode)
	{
	case SHIFT_KEY_CODE:	//shift--
			if(ShiftKey_flag==1)
				{//shift------ ��ʾ
				// if(ButtonTouch_mode==TOU_MODE_F4)
					// {
					// GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
					// switch(Language)
							// {
							// case CHN_HAN:
								// Printf16("shift+F5,���/���ȫ�����",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
									// break;
							// case ENGLISH:	
								// Printf16("shift+F5,set/clr all Knife-flag",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
									// break;
							// case INDONSIA:	//ӡ��	
								// Printf16("shift+F5,menambah/menghapus K-flag",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
									// break;
							// case PORTUGAL:	//������
								// Printf16("shift+F5,Modificar todas as tags KNIF",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
									// break;
							// case SPANISH: //������
								// Printf16("shift+F5,Modificar Todos los tags KNIF",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
									// break;
							// }
					// }
				}
				break;
	case SHIFT_0_KEY_CODE:	//shift+0------ ������
			if(WorkStart_flag==1)
			  {
			  if(Run_flag==0)
				 {
				 if(WorkMode==AUTO_MODE)//�Զ�--  ��������
					AllFlagSetExec(AIR_FLAG); //�趨 ������
				 }	
			  }
			  break;		
	case SHIFT_1_KEY_CODE:	//shift+1------ ѹֽ���
			if(WorkStart_flag==1)
			  {
			  if(Run_flag==0)
				 {
				 if(WorkMode==AUTO_MODE)//�Զ�--  ��������
					AllFlagSetExec(PRESS_FLAG); //�趨  ѹֽ���
				 }	
			  }
			  break;	  
	case SHIFT_2_KEY_CODE:	//shift+2------ ��ֽ���
			if(WorkStart_flag==1)
			  {
			  if(Run_flag==0)
				 {
				 if(WorkMode==AUTO_MODE)//�Զ�--  ��������
					AllFlagSetExec(SORT_FLAG); //�趨  ��ֽ���
				 }	
			  }
			  break;	
	case SHIFT_3_KEY_CODE:	//shift+3------ ��ֽ���
			if(WorkStart_flag==1)
			  {
			  if(Run_flag==0)
				 {
				 if(WorkMode==AUTO_MODE)//�Զ�--  ��������
					AllFlagSetExec(PUSH_FLAG); //�趨  ��ֽ���
				 }	
			  }
			  break;	
	case SHIFT_4_KEY_CODE:	//shift+4------ �����
			if(WorkStart_flag==1)
			  {
			  if(Run_flag==0)
				 {
				 if(WorkMode==AUTO_MODE)//�Զ�--  ��������
					AllFlagSetExec(KNIFE_FLAG); //�趨  �����
				 }	
			  }
			  break;
	case SHIFT_5_KEY_CODE:	//shift+5------ ������е����
			if(WorkStart_flag==1)
			  {
			  if(Run_flag==0)
				 {
				 if(WorkMode==AUTO_MODE)//�Զ�--  ��������
					{
					if(F5AllKnifeF_SetFlag==0)
						F5AllKnifeF_SetFlag=1;
					else
						F5AllKnifeF_SetFlag=0;
					// Set_AllFlagWind_Exit(FlagTouRow_num-1);	//�˳���ǿ�
					AllKnifeFlagExec(F5AllKnifeF_SetFlag);	//��ӣ� --���е����
					}
				 }	
			  }
			  break;	
	case SHIFT_6_KEY_CODE:	//shift+6------ �޸�����ƫ����
			if(WorkStart_flag==1)
			  {
			  if(Run_flag==0)
				 {
				 if(WorkMode==AUTO_MODE)//�Զ�--  ��������
					{
					if(ElectricWheelOn_flag==1)	//����  ��Чʱ
						{
						AmendSwitch_flag=!AmendSwitch_flag;
						if(AmendSwitch_flag==0)
							{
							AmendStartRun_flag=0;
							AmendSize=0;
							}
						AmendButtonFlag_dis();	//F6�޸�����ƫ����
						}
					}
				 }	
			  }
			  break;	
	case TEACH_TOUCH_CODE:		//ʾ�� ģʽ 
	case SHIFT_LEFT_KEY_CODE:        //shift+��  == ʾ��ģʽ
			if(WorkStart_flag==1)
			  {
			   if(Run_flag==0)
				 {
					switch(WorkMode)
						{
						case TEACH_LABEL_MODE: //��ǩ
						case TEACH_DIVIDE_MODE: //�ȷ�
						// // case TEACH_PRO_MODE: //����ѡ��
							CurrentArea_recover2(MIDDLE_PAGE_X, MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
						case AUTO_MODE://�Զ� ��ģʽ��************
						case MANUAL_MODE:// �ֶ� ��ģʽ
						case SELF_CUT_MODE://�Ե���������
							WorkMode=TEACH_MODE;  //ʾ��ģʽ
							TeachModePage_dis();//ʾ��ģʽpage
							PromptNum_dis();//���뷶Χ	
							PromptDis_flag=1; 
						case TEACH_MODE: //ʾ����ģʽ	
							//------------���ص�һ��
							PaperCutEnb_signal=1;
							// // ClrInput_function();//���� ����� 
							CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
							cursor_row=0;
							CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
							if(Knife_order<=OnePro_head.pro_knifeSUM)
								StepOrder_dis(Knife_order);//�������
								
							ACServoAlarmExec_flag=0;
								break;
						case TEACH_PLUS_MODE:// F5++
							WorkMode=TEACH_MODE;//����
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F5_plus_dis(0);
							//------------���ص�һ��
							// // ClrInput_function();//���� ����� 
							CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
							cursor_row=0;
							CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
							if(Knife_order<=OnePro_head.pro_knifeSUM)
								StepOrder_dis(Knife_order);//�������
							PromptNum_dis();//���뷶Χ	
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case TEACH_MINUS_MODE:// F6--
							WorkMode=TEACH_MODE;//����
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F6_minus_dis(0);
							//------------���ص�һ��
							// // ClrInput_function();//���� ����� 
							CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
							cursor_row=0;
							CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
							if(Knife_order<=OnePro_head.pro_knifeSUM)
								StepOrder_dis(Knife_order);//�������
							PromptNum_dis();//���뷶Χ	
							PromptDis_flag=1;	
							ACServoAlarmExec_flag=0;
							break;	
						}
				 }
			  else
				 {
				 
				 }
			  }
			  break;
			  break;		  
	case SHIFT_8_KEY_CODE:	//shift+8------ ���� ģʽ
			if(WorkStart_flag==1)
			  {
			  if(Run_flag==0)
				 {
					switch(WorkMode)
						{
						case MANUAL_MODE: //�ֶ�ģʽ
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//�ߴ������
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
			  else
				 {
				 
				 }
			  }
				break;
			  
	case SHIFT_RIGHT_KEY_CODE:        //shift+��  == �Ե�ģʽ
	case AUTOCUT_TOUCH_CODE:	//�Ե� ģʽ
			if(WorkStart_flag==1)
				 {
				 if(Run_flag==0)
					{
						switch(WorkMode)
							{
							
							case AUTO_MODE://  �Զ�ģʽ��
							case MANUAL_MODE:// �ֶ� ģʽ
							case TEACH_MODE://ʾ�� ģʽ
								MainMode_temp=WorkMode;
								WorkMode=AUTO_TO_SELF_MODE;   //�Զ�-->�Ե����� ģʽ
								PaperCutEnb_signal=1;
								SelfEnterPage_dis();
								// // ButtonTouch_mode=TOU_MODE_AUTOCUT_IN;
									break;
							case SELF_CUT_MODE:  //		�Ե��� ģʽ
								//------------���ص�һ��
								// // ClrInput_function();//���� ����� 
								CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
								cursor_row=0;
								CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
								Knife_order=1;//
								Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
								if(Knife_order<=OnePro_head.pro_knifeSUM)
									StepOrder_dis(Knife_order);//������� 
								PromptNum_dis();//���뷶Χ	
								PromptDis_flag=1; 	
									break;
									/****
							case SELF_RULER_MODE://�Ե� ��׼
							case SELF_TOOLS_MODE://�Ե� ����
								PaperCutEnb_signal=1;
								CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
								WorkMode=SELF_CUT_MODE;  //����   ----------�Ե��� ģʽ
								SubModeIcon_dis(WorkMode); //�Ե�ģʽ
								//------------���ص�һ��
								// // ClrInput_function();//���� ����� 
								CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
								cursor_row=0;
								CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
								Knife_order=1;//
								Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
								if(Knife_order<=OnePro_head.pro_knifeSUM)
									StepOrder_dis(Knife_order);//������� 
								PromptNum_dis();//���뷶Χ	
								PromptDis_flag=1; 	
									break;
									****/
							}
					}
				  else
					{
					
					}
				 }
					break;
	case HELP_KEY_CODE:         //����----------
		if(WorkStart_flag==0)
			{
			switch(MotorType)
				{
					case MOTOR_FREQ_5_SPD_RST:
					case MOTOR_FREQ_3_SPD:
					case MOTOR_FREQ_3_SPD_RST:
					case MOTOR_AC_SERVO:
					case MOTOR_AC_SERVO_REV:
					case MOTOR_AC_A6_SERVO:
						if((StartCheck_mode<2)||(StartCheck_mode==4))
							CheckModeOK_flag=1;	
						else
							CheckModeOK_flag=0;
						break;
					// // case MOTOR_DC_SERVO:
					// // case MOTOR_DC670_SERVO:
						// // if(StartCheck_mode<2)
							// // CheckModeOK_flag=1;	
						// // else
							// // CheckModeOK_flag=0;
						// // break;
					// case MOTOR_AC_SERVO:
					// case MOTOR_AC_SERVO_REV:
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
				switch(Board_TestMod)
					{
					case TEST_NO: //�ǰ��� ģʽ-------
						Board_TestMod=TEST_HELP; //���� ģʽ  ����
						StartHelpMode_dis();
						break;
					case TEST_TOUCH:	
					case TEST_ICON:	
					case TEST_BOARD:	
					case TEST_SYS_WORD:	
					case TEST_PAGE_LINE:	
						num_cou=0; //
					case TEST_HELP:  //���� ģʽ��
						Bmp_Decode((Int32U)START_PIC_sdram, 0, 0, (pInt16U)LCD_VRAM_BASE_ADDR); //��ʾ��������
						Board_TestMod=TEST_NO;
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
						KeyLinkDis_flag=0;
						PassCheckDis_flag=0;
						break;
					}
				}
			}
			break;
	case PROC_KEY_CODE:   //���� ѡ��		(����ģʽ)
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)  //
				{
					switch(WorkMode)
						{
						case TEACH_MODE://ʾ�� ģʽ
								
						case AUTO_MODE://�Զ���������	
						case MANUAL_MODE:// �ֶ� ģʽ
								WorkMode=READ_PRO_MODE;	// ���� -----------ѡ�����ģʽ(����ģʽ)
								SearchProgPage_dis(); //���� ѡ�� ������ʾ
								PromptDis_flag=0;
								//prog_order=1;
								TableDis_startcol=PROC_NUM_X;
								cursor_pro=0;
								CursorPro_dis(cursor_pro,1);//pro���
								Prog_1page_dis(prog_order, cursor_pro);//===����---������ʾ
								OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//һ������ ��ʾ
								ClearCalculatorInput(); //��������� ����//ClrInput_function();//���� �����
								ACServoAlarmExec_flag=0;
								break;	
						}
				}
			}	
			break;
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
						// // case MOTOR_DC_SERVO:
						// // case MOTOR_DC670_SERVO:
							// // DCServoStop();  //ֹͣ����
							// // ServoPressStop_flag=0;
							// // DcServoGoTarget_flag=0;
							// // BellStart_flag=0;
								// // break;
						case MOTOR_AC_SERVO:
						case MOTOR_AC_SERVO_REV:
						case MOTOR_AC_A6_SERVO:
							ACServoStop();
								break;
						}
					Run_flag=0;	
					InTargetPosit_flag=0;	//Ŀ��λ��
					AutoPushRun_flag=0; //�Զ���ֽ ����
					AirOffOK_flag=0;
					PressUp_flag=0;
					PressDown_flag=0;
					TargetSize=0;
					// TargetSize_temp=0;
					BeforeKnife_offset_in=0;
					if(ButtonTouch_mode==0)
						// ClrInput_function();//���� �����
					//PaperCutEnb_signal=1;	
					AutoRoute_flag=0;
					if(ACServoDrvErr_flag==0)
						{
						RLOUT1_OFF; RLOUT1_1_OFF;   // �������	
						}
						
					}
				}
			else
				{
				if(MotorType<MOTOR_AC_SERVO)	//(MotorType<MOTOR_DC_SERVO)
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
						// TargetSize_temp=0;
						BeforeKnife_offset_in=0;
						if(ButtonTouch_mode==0)
							// ClrInput_function();//���� �����
						//PaperCutEnb_signal=1;	
						AutoRoute_flag=0;
						if(ACServoDrvErr_flag==0)
							{
							RLOUT1_OFF; RLOUT1_1_OFF;   // �������
							}
						}
					}
					//----
					if(WorkMode==SELF_CUT_MODE) //�Ե���������--------�����Զ�
						{
						if(CutEnBegin_flag==1)
							{
							CutEnBegin_flag=0;
							BellOUT_OFF;
							RLOUT4_ON;
							AutoCutStart_flag=0;
							RunStop_flag=0;
							//Run_flag=0;
							}
						
						LastAutoKnife_order=Knife_order;
						WorkMode=AUTO_MODE;//�Զ���
						AutoModePage_dis(); //���� ----------- �Զ�
						//------------���ص�һ��
						// // ClrInput_function();//���� ����� 
						CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
						cursor_row=0;
						CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
						Knife_order=1;//
						Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
						if(Knife_order<=OnePro_head.pro_knifeSUM)
							StepOrder_dis(Knife_order);//������� 
						}
				}
			}	
			break;
     /**
	case WHEEL_SWITCH_TOUCH_CODE: //0xffff000c ��������  ����
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
							ElectricalWheel_dis();  //��������  ����״̬
								break;
						}
					}
				}
			}
			break; **/
    case   	MUL_KEY_CODE: //MUL_TOUCH_CODE   0xffff0007 �˷�  *
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
				{
				CalculatorValue_exec('*');
				}
			}	
			break;
   	case	DIV_KEY_CODE:  //   DIV_TOUCH_CODE 0xffff0008 ����/
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
				{
				CalculatorValue_exec('/');
				}
			}
			break;
	case	EQUAL_KEY_CODE:  //     EQU_TOUCH_CODE 0xffff0009      ��� =  
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
				{
				if(CalcResultDis_flag==0)
					{
					CalcGetValue_exec();
					}
				}
			}
			break;		
	case INPUT_TOUCH_CODE:	//0xffff0001	 ����� =====���� 
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
				{
				ClrInput_function();//���� �����
				if(ButtonTouch_mode==0)  //���봥�� ����������
					{
					switch(WorkMode)
						{
						case AUTO_TO_SELF_MODE:  //�Զ�-->�Ե����� ģʽ
						// // case PROG_PRO_MESS_MODE:	//��������		 
						// // case TEACH_PRO_MESS_MODE:	
						case PROG_DEL_ALL_SIZE_MODE://	ɾ�����гߴ�
						case TEACH_DEL_ALL_SIZE_MODE://	ɾ�����гߴ�
						// // case PROG_DEL_ALL_PRO_MODE://ɾ������pro
						// // case TEACH_DEL_ALL_PRO_MODE://ɾ������pro
						case MANUAL_IO_TEST_MODE:// IO ����ģʽ--------
							break;
						default:	//���� ������
							// CalcNoNumInput_flag=1;
							// Dot_flag=0;
							// CalcSign_order=0;//�׸������ λ��
							// CalcData_temp=0;
							// CalcResultDis_flag=0;
							// num_cou=0;
							// if(Sign_flag==1)//��� ��,����
								// {
								// GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//�ߴ������
								// Sign_flag=0;
								// }
							
							// CalcInput_cou=0;
							// Calculator_Window();  //������ ��ť	
							// ClrCalcNums_text(CalcInput_Text,CAL_INPUT); //������� �����
							// ClrCalcNums_text(CalcResult_Text,CAL_RESULT); //������� ����� 
							// CalcInputNums_dis(CalcInput_Text);  //����� ��ʾ
							// CalcResultNums_dis(CalcResult_Text);//����� ��ʾ
							// ButtonTouch_mode=TOU_MODE_CALC;
							break;
						}
					}
				else if(ButtonTouch_mode==TOU_MODE_CALC)         //�˳�
					{
					//CalcInput_cou=0;
					CalcuInClear_exec();     //��� ������
					switch(WorkMode)
						{
						// // case AUTO_TOOLS_MODE:
						case MANUAL_TOOLS_MODE:
						// // case SELF_TOOLS_MODE:
							back_color=TEXT_TAB_BACK_COLOR;
							x=PARA_START_X1+PARA_COL_WIDE,y=PARA_START_Y,gap=PARA_ROW_GAP;
							if(PramSel_Page<1)	//page 1
								{
								ParameterPage1_dis(7, 0);
								ParameterPage1_dis(8, 0);
								if(MotorType<MOTOR_AC_SERVO)	
									{
									ParameterPage1_dis(9, 0);
									}
								else 
									{
									ParameterPage1_dis(9, 0);
									ParameterPage1_dis(10, 0);
									}
								ParameterPage1_dis(Para_sel, 1);
								GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
								switch(Language)
									{
									case CHN_HAN:
										Printf24("ѹֽͣ��:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("��������:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										switch(MotorType)
											{
											case MOTOR_FREQ_5_SPD_RST:
											case MOTOR_FREQ_3_SPD:
											case MOTOR_FREQ_3_SPD_RST:
												Printf24("���ѡ��:  ",x,y,BLACK_COLOR,1,back_color);
													break;
											// // case MOTOR_DC_SERVO:
											// // case MOTOR_DC670_SERVO:
												// // Printf24("����ٶ�:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
												// // Printf24("�㶯�ٶ�:  ",x,y,BLACK_COLOR,1,back_color);
													// // break;
											case MOTOR_AC_SERVO:
											case MOTOR_AC_SERVO_REV:
											case MOTOR_AC_A6_SERVO:
												Printf24("�����ٶ�:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
												Printf24("���ѡ��:  ",x,y,BLACK_COLOR,1,back_color);
													break;
											}
											break;
									case ENGLISH:
										Printf24("Press-Stop:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("AirOff-dist:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										switch(MotorType)
											{
											case MOTOR_FREQ_5_SPD_RST:
											case MOTOR_FREQ_3_SPD:
											case MOTOR_FREQ_3_SPD_RST:
												Printf24("IR-Set:  ",x,y,BLACK_COLOR,1,back_color);
													break;
											// // case MOTOR_DC_SERVO:
											// // case MOTOR_DC670_SERVO:
												// // Printf24("Max-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
												// // Printf24("Jog-speed:",x,y,BLACK_COLOR,1,back_color);
													// // break;
											case MOTOR_AC_SERVO:
											case MOTOR_AC_SERVO_REV:
											case MOTOR_AC_A6_SERVO:
												Printf24("Run-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
												Printf24("IR-Set:  ",x,y,BLACK_COLOR,1,back_color);
													break;
											}
											break;
									case INDONSIA:	//ӡ��
										Printf24("Plat-bawah:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Off gas da:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										switch(MotorType)
											{
											case MOTOR_FREQ_5_SPD_RST:
											case MOTOR_FREQ_3_SPD:
											case MOTOR_FREQ_3_SPD_RST:
												Printf24("Set-IR: ",x,y,BLACK_COLOR,1,back_color);
													break;
											// // case MOTOR_DC_SERVO:
											// // case MOTOR_DC670_SERVO:
												// // Printf24("Tercepat:",x,y,BLACK_COLOR,1,back_color);y+=gap;
												// // Printf24("Jog-kecep:",x,y,BLACK_COLOR,1,back_color);
													// // break;
											case MOTOR_AC_SERVO:
											case MOTOR_AC_SERVO_REV:
											case MOTOR_AC_A6_SERVO:
												Printf24("Kecepa-lari:",x,y,BLACK_COLOR,1,back_color);y+=gap;
												Printf24("Set-IR: ",x,y,BLACK_COLOR,1,back_color);
													break;
											}
											break;
									case PORTUGAL:	//������
										Printf24("encerra:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Off Air:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										switch(MotorType)
											{
											case MOTOR_FREQ_5_SPD_RST:
											case MOTOR_FREQ_3_SPD:
											case MOTOR_FREQ_3_SPD_RST:
												Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
													break;
											// // case MOTOR_DC_SERVO:
											// // case MOTOR_DC670_SERVO:
												// // Printf24("Veloci-m��  ",x,y,BLACK_COLOR,1,back_color);
												// // Printf24("          x:",x,y,BLACK_COLOR,0,back_color);y+=gap;
												// // Printf24("Veloci-Jog:",x,y,BLACK_COLOR,1,back_color);
													// // break;
											case MOTOR_AC_SERVO:
											case MOTOR_AC_SERVO_REV:
											case MOTOR_AC_A6_SERVO:
												Printf16("Veloci-corrida:",x,y,BLACK_COLOR,1,back_color);y+=gap;
												Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
													break;
											}
											break;
									case SPANISH: //������
										Printf24("cierre:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Off Air:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										switch(MotorType)
											{
											case MOTOR_FREQ_5_SPD_RST:
											case MOTOR_FREQ_3_SPD:
											case MOTOR_FREQ_3_SPD_RST:
												Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
													break;
											// // case MOTOR_DC_SERVO:
											// // case MOTOR_DC670_SERVO:
												// // Printf24("Veloci-m��  ",x,y,BLACK_COLOR,1,back_color);
												// // Printf24("          x:",x,y,BLACK_COLOR,0,back_color);y+=gap;
												// // Printf24("Veloci-Jog:",x,y,BLACK_COLOR,1,back_color);
													// // break;
											case MOTOR_AC_SERVO:
											case MOTOR_AC_SERVO_REV:
											case MOTOR_AC_A6_SERVO:
												Printf16("Veloci-corrida:",x,y,BLACK_COLOR,1,back_color);y+=gap;
												Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
													break;
											}
											break;
									}		
								}
							break;
						
						case  PROG_MODE://��̻�����
						case AUTO_MODE://�Զ���������
						case AUTO_PLUS_MODE://�Զ�F5++
						case AUTO_MINUS_MODE://�Զ�F6--
						case TEACH_MODE://ʾ�� ģʽ
						//case AUTO_TO_SELF_MODE:   //�Զ�-->�Ե����� ģʽ
						case SELF_CUT_MODE:  //�Ե��� ģʽ
						case TEACH_PLUS_MODE: //�Ե� F5++
						case TEACH_MINUS_MODE://�Ե� F6--
							 if(Knife_order>OnePro_head.pro_knifeSUM)
								 K_temp=Knife_order-1;
							 else
								 K_temp=Knife_order;
							//StepOrder_dis(Knife_order);//�������
							ProgressBar_dis(OnePro_head.pro_knifeSUM,K_temp);  //������ ��ʾ
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
							// CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
							// cursor_row=0;
							// CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
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
	/*****
	case ONE_KEY_CODE:		// F ���ܰ���******************
		if(WorkStart_flag==0)  //δ���빤��״̬
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
						if(StartCheck_mode<2)
							CheckModeOK_flag=1;
						else
							CheckModeOK_flag=0;
						break;
				case MOTOR_AC_SERVO:
						if(StartCheck_mode<3)
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
							MoveStop();
							ForceStop_flag=0;
							BackStop_flag=0;
							Backward_flag=0;
							Forward_flag=0;	
							SelfLockEn_flag=0; //ȡ������
							ToTargetStop_flag=0;
							RunStop_flag=0;
								break;
						case MOTOR_DC_SERVO:
						case MOTOR_DC670_SERVO:
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
					if(ButtonTouch_mode==0)
						ClrInput_function();//���� �����
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
						MoveStop();
						ForceStop_flag=0;
						BackStop_flag=0;
						Backward_flag=0;
						Forward_flag=0;	
						SelfLockEn_flag=0; //ȡ������
						ToTargetStop_flag=0;
						RunStop_flag=0;
						
						InTargetPosit_flag=0;	//Ŀ��λ��
						AutoPushRun_flag=0; //�Զ���ֽ ����
						TargetSize=0;
						TargetSize_temp=0;
						BeforeKnife_offset_in=0;
						if(ButtonTouch_mode==0)
							ClrInput_function();//���� �����
						//PaperCutEnb_signal=1;	
						AutoRoute_flag=0;
						}
					}
				}
			}
  	         break;
			 ****/
	case TWO_KEY_CODE:		//�ֶ�****************
        if(WorkStart_flag==1)  
			{
			if(Run_flag==0)
			    {
				switch(WorkMode)
					{
					// // case PROG_MODE://��� ��ģʽ��********
					case TEACH_MODE://ʾ�� ģʽ
					case AUTO_MODE://�Զ� ��ģʽ��*******
					case SELF_CUT_MODE://�Ե���������
					case READ_PRO_MODE:// ������� ��������
						WorkMode=MANUAL_MODE;  //���� �ֶ�ģʽ
						ManualModePage_dis();
						KnifeSensorMode=0;
						PressSensorMode=0;
						// // ClrInput_function();//���� �����
						PromptNum_dis();//���뷶Χ
						PromptDis_flag=1; 
						PaperCutEnb_signal=1;
						ACServoAlarmExec_flag=0;
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
						SubModeIcon_dis(WorkMode); //�ֶ�mode name
						KnifeSensorMode=0;
						PressSensorMode=0;
					case MANUAL_MODE:   //�ֶ�
						PromptNum_dis();//���뷶Χ
						PromptDis_flag=1;
						// // ClrInput_function();//���� �����
						ACServoAlarmExec_flag=0;
						break;		
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
						// // case MOTOR_DC_SERVO:
						// // case MOTOR_DC670_SERVO:
							// // DCServoStop();  //ֹͣ����
							// // ServoPressStop_flag=0;
							// // DcServoGoTarget_flag=0;
							// // BellStart_flag=0;
							// // //************
							// // Run_flag=0;	
							// // InTargetPosit_flag=0;	//Ŀ��λ��
							// // AutoPushRun_flag=0; //�Զ���ֽ ����
							// // TargetSize=0;
							// // TargetSize_temp=0;
							// // BeforeKnife_offset_in=0;
							// // AutoRoute_flag=0;
								// // break;
						case MOTOR_AC_SERVO:
						case MOTOR_AC_SERVO_REV:
						case MOTOR_AC_A6_SERVO:
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
					
					}
				}
			}
  	     break;   
	case THREE_KEY_CODE:		//�Զ�******************
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
			    {
					switch(WorkMode)
						{
						// // case PROG_MODE://��� ��ģʽ��
						case TEACH_MODE://ʾ�� ģʽ
						case MANUAL_MODE:// �ֶ� ��ģʽ
						case SELF_CUT_MODE://�Ե���������	
						case READ_PRO_MODE:// ������� ��������
							WorkMode=AUTO_MODE;//���� �Զ�ģʽ
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							AutoModePage_dis();
							PromptNum_dis();//���뷶Χ	
							PromptDis_flag=1; 
						case AUTO_MODE://�Զ� ��ģʽ��
							//------------���ص�һ��
							// // ClrInput_function();//���� ����� 
							CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
							cursor_row=0;
							CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
							if(Knife_order<=OnePro_head.pro_knifeSUM)
								StepOrder_dis(Knife_order);//�������
							PromptNum_dis();//���뷶Χ	
							PromptDis_flag=1;  
							ACServoAlarmExec_flag=0;
							break;
						case AUTO_LABEL_MODE: //��ǩ
						case AUTO_DIVIDE_MODE: //�ȷ�
							WorkMode=AUTO_MODE;//����    �Զ� ��ģʽ
							CurrentArea_recover2(MIDDLE_PAGE_X, MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							SubModeIcon_dis(WorkMode);   //�Զ�ģʽname
							PorgSet_sel=0;
							//------------���ص�һ��
							// // ClrInput_function();//���� ����� 
							CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
							cursor_row=0;
							CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
							if(Knife_order<=OnePro_head.pro_knifeSUM)
								StepOrder_dis(Knife_order);//�������
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							ACServoAlarmExec_flag=0;	
							break;
							//�Զ�ģʽ------------------------------------------
						// // case AUTO_RULER_MODE:	//��׼ģʽ
						// // case AUTO_TOOLS_MODE:	 //����ģʽ	
							// // Para_sel=0;
							// // WorkMode=AUTO_MODE;//����    �Զ� ��ģʽ
							// // PaperCutEnb_signal=1;
							// // PressCircle_mode=0;
							// // CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							// // SubModeIcon_dis(WorkMode); //�Զ�
							// // //------------���ص�һ��
							// // ClrInput_function();//���� ����� 
							// // CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
							// // cursor_row=0;
							// // CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
							// // Knife_order=1;//
							// // Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
							// // if(Knife_order<=OnePro_head.pro_knifeSUM)
								// // StepOrder_dis(Knife_order);//�������
							// // PromptNum_dis();//���뷶Χ	
							// // PromptDis_flag=1; 
							// // ACServoAlarmExec_flag=0;
							// // break;
						case AUTO_PLUS_MODE:// F5++
							WorkMode=AUTO_MODE;//����
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F5_plus_dis(0);
							//------------���ص�һ��
							// // ClrInput_function();//���� ����� 
							CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
							cursor_row=0;
							CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
							if(Knife_order<=OnePro_head.pro_knifeSUM)
								StepOrder_dis(Knife_order);//�������
							PromptNum_dis();//���뷶Χ	
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case AUTO_MINUS_MODE:// F6--
							WorkMode=AUTO_MODE;//����
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F6_minus_dis(0);
							//------------���ص�һ��
							// // ClrInput_function();//���� ����� 
							CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
							cursor_row=0;
							CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
							if(Knife_order<=OnePro_head.pro_knifeSUM)
								StepOrder_dis(Knife_order);//�������
							PromptNum_dis();//���뷶Χ	
							PromptDis_flag=1;	
							ACServoAlarmExec_flag=0;
							break;	
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
						// // case MOTOR_DC_SERVO:
						// // case MOTOR_DC670_SERVO:
							// // DCServoStop();  //ֹͣ����
							// // ServoPressStop_flag=0;
							// // DcServoGoTarget_flag=0;
							// // BellStart_flag=0;
							// // //************
							// // Run_flag=0;	
							// // InTargetPosit_flag=0;	//Ŀ��λ��
							// // AutoPushRun_flag=0; //�Զ���ֽ ����
							// // TargetSize=0;
							// // TargetSize_temp=0;
							// // BeforeKnife_offset_in=0;
							// // AutoRoute_flag=0;
								// // break;
						case MOTOR_AC_SERVO:
						case MOTOR_AC_SERVO_REV:
						case MOTOR_AC_A6_SERVO:
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
					}				
				}
			}
  	     break;
		 /****
	case FOUR_KEY_CODE:	//��̰���******************����  ��� ��ģʽ
		if(WorkStart_flag==1)
		   {
		   if(Run_flag==0)
			    {
				if(ButtonTouch_mode==0)
					{
					switch(WorkMode)
						{
						case PROG_LABEL_MODE: //��ǩ
						case PROG_DIVIDE_MODE: //�ȷ�
							WorkMode=PROG_MODE;
							CurrentArea_recover2(MIDDLE_PAGE_X, MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							SubModeIcon_dis(WorkMode);   //���ģʽname
							PorgSet_sel=0;
							//------------���ص�һ��
							ClrInput_function();//���� ����� 
							CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
							cursor_row=0;
							CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
							if(Knife_order<=OnePro_head.pro_knifeSUM)
								StepOrder_dis(Knife_order);//�������
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							PaperCutEnb_signal=1;
							ACServoAlarmExec_flag=0;
							if(Sign_flag==1)//��� ��,����
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								}
								break;
						case AUTO_MODE://�Զ� ��ģʽ��************
						case SELF_CUT_MODE://�Ե���������
						case TEACH_MODE://ʾ�� ģʽ
						case MANUAL_MODE:// �ֶ� ��ģʽ
							if(Sign_flag==1)
								{
								num_cou=0;
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								}
							WorkMode=PROG_MODE;
							ProgModePage_dis();// �ص� ���ģʽ
							 
						case PROG_MODE: //��� ��ģʽ
								//------------���ص�һ��
							ClrInput_function();//���� ����� 
							CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
							cursor_row=0;
							CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
							if(Knife_order<=OnePro_head.pro_knifeSUM)
								StepOrder_dis(Knife_order);//�������
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							PaperCutEnb_signal=1;
							ACServoAlarmExec_flag=0;
							if(Sign_flag==1)//��� ��,����
								{
								GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//�ߴ������
								Sign_flag=0;
								}
								break;
						}		
					}
				else if(ButtonTouch_mode==TOU_MODE_CALC)  //������ ����ģʽ
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
						case MOTOR_AC_SERVO_REV:
						case MOTOR_AC_A6_SERVO:
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
					if(ButtonTouch_mode==0)
						ClrInput_function();//���� ����� 		
					}
				}
		   }
		  break;
		  ****/
    case AUTO_KEY_CODE:       // F1**********************
		if(WorkStart_flag==1)
			{
			if(Run_flag==0)
			    {
				switch(WorkMode)
					{
					case AUTO_MODE://�Զ� ��ģʽ��	
						WorkMode=AUTO_LABEL_MODE; //--------�򿪱�ǩ ҳ
						F1_LabelPage_dis();  
						Total_size=0;//�ܳ�
						Label_size=0;//��ǩ��
						Waste_size=0;//�ϱ�
						PorgSet_sel=0;
						PromptNum_dis();//���뷶Χ
						PromptDis_flag=1;
						ACServoAlarmExec_flag=0;
						break;
					case TEACH_MODE://ʾ�� ģʽ
						WorkMode=TEACH_LABEL_MODE; //--------�򿪱�ǩ ҳ
						F1_LabelPage_dis();  
						Total_size=0;//�ܳ�
						Label_size=0;//��ǩ��
						Waste_size=0;//�ϱ�
						PorgSet_sel=0;
						PromptNum_dis();//���뷶Χ
						PromptDis_flag=1;
						ACServoAlarmExec_flag=0;
						break;
						
					case AUTO_LABEL_MODE://�� ��   ��ǩ********************
						WorkMode=AUTO_MODE;//------------�˳����ص��Զ��� ���� 
						CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH); 
						SubModeIcon_dis(WorkMode);   //�Զ�ģʽname
						PorgSet_sel=0;
						//if(Knife_order<MAX_Knife-2) //�������3��
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
						SubModeIcon_dis(WorkMode);   //ʾ��ģʽname
						PorgSet_sel=0;
						//if(Knife_order<MAX_Knife-2) //�������3��
						//  {
						if((Total_size*Label_size*Waste_size)!=0)//�趨��Ч
							Label_function();          
						// }
						PromptNum_dis();//���뷶Χ
						PromptDis_flag=1;
						ACServoAlarmExec_flag=0;
						break;
					case AUTO_DIVIDE_MODE: //�� ���� �ȷ�ҳ*******************
						WorkMode=AUTO_MODE;//--------------�˳����ص��Զ��� ���� 
						CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
						SubModeIcon_dis(WorkMode);   //�Զ�ģʽname
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
						SubModeIcon_dis(WorkMode);   //ʾ��ģʽname
						PorgSet_sel=0;
						if((Total_size*Divide_num)!=0)//�趨�ȷ���Ч
						  {
						  Divide_function();//
						  }
						PromptNum_dis();//���뷶Χ
						PromptDis_flag=1;  
						ACServoAlarmExec_flag=0;
						break;		
					
					case READ_PRO_MODE:		//	���� ����ѡ����**************	
						WorkMode=READ_PRO_MESS_MODE;//--------------��ʾ������ϸ ��Ϣ
						ProMessageModify_mode(prog_order);	//�������޸� ģʽ
						break;
					case TEACH_PRO_MODE:	//���� ����ѡ����**************	
						// WorkMode=TEACH_PRO_MESS_MODE;//--------------��ʾ������ϸ ��Ϣ
						// ProMessageModify_mode(prog_order);	//�������޸� ģʽ
						break;	
					case READ_PRO_MESS_MODE:
						InputMode=PINYIN_INPUT;
						ProMessIcon_dis();	//���뷨ģʽ icon��ʾ
						InputStus_dis(InputMode);	//���뷨  ѡ��(ƴ��)
						break;
					// // case TEACH_PRO_MESS_MODE:
						// // InputMode=PINYIN_INPUT;
						// // ProMessIcon_dis();	//���뷨ģʽ icon��ʾ
						// // InputStus_dis(InputMode);	//���뷨  ѡ��(ƴ��)
						// // break;	
					// // case AUTO_MODE://�Զ� ��ģʽ��	
						// // WorkMode=AUTO_RULER_MODE; //��׼
						// // F2_RulerPage_dis(); //��׼ ����
						// // PromptNum_dis();//���뷶Χ
						// // PromptDis_flag=1;
						// // ACServoAlarmExec_flag=0;
						// // break;
					// // case AUTO_TOOLS_MODE:// ����  �Զ� -------����ģʽ
						// // WorkMode=AUTO_MODE;//����    ---------�Զ� ��ģʽ
						// // Para_sel=0;
						// // PaperCutEnb_signal=1;
						// // CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
						// // SubModeIcon_dis(WorkMode); //�Զ�mode name
						// // PromptNum_dis();//���뷶Χ
						// // PromptDis_flag=1;
						// // ACServoAlarmExec_flag=0;
						// // break;
						/***
					case SELF_CUT_MODE://�Ե���������	
						WorkMode=SELF_RULER_MODE; //��׼
						F2_RulerPage_dis(); //��׼ ����
						PromptNum_dis();//���뷶Χ
						PromptDis_flag=1;
						ACServoAlarmExec_flag=0;
						ReadCurrentSize_A6Coder();//��ȡ��ǰ A6������ֵ
						break;
					case SELF_TOOLS_MODE:// ���� �Ե�  -------����ģʽ
						WorkMode=SELF_CUT_MODE;//����    ---------�Ե� ��ģʽ
						Para_sel=0;
						CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
						SubModeIcon_dis(WorkMode); //�Ե�ģʽ
						PromptNum_dis();//���뷶Χ
						PromptDis_flag=1;
						ACServoAlarmExec_flag=0;
						break;
						****/
					case MANUAL_MODE:  // �ֶ�ģʽ
						WorkMode=MANUAL_TOOLS_MODE;//����  �ֶ�----����ģʽ*****************
						F1_ToolsPage_dis(); //��������
						Para_sel=0;
						PromptDis_flag=0;
						ACServoAlarmExec_flag=0;
						ReadCurrentSize_A6Coder();//��ȡ��ǰ A6������ֵ
						
						break;
					case MANUAL_PULSE_MODE://�ֶ� �����趨ģʽ
						Pulse_degree=Para_sel;
						Save_degree();
						WorkMode=MANUAL_MODE;//����    ---------�ֶ� ��ģʽ
						Para_sel=0;
						CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
						SubModeIcon_dis(WorkMode);   //�ֶ�ģʽname
						PromptNum_dis();//���뷶Χ
						PromptDis_flag=1;
						ACServoAlarmExec_flag=0;
						break;
					case MANUAL_TOOLS_MODE:// �ֶ� ����ģʽ
					case MANUAL_CLOCK_MODE://�ֶ� ʱ��ģʽ
					case MANUAL_PASS_MODE://�ֶ� ����ģʽ
					case MANUAL_SERVO_C_MODE:   //�ֶ�ֱ���ŷ� C ���� 
						WorkMode=MANUAL_MODE;//����    ---------�ֶ� ��ģʽ
						Para_sel=0;
						CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
						SubModeIcon_dis(WorkMode); //�ֶ�mode name
						PromptNum_dis();//���뷶Χ
						PromptDis_flag=1;
						ACServoAlarmExec_flag=0;
						break;	
					//-------��׼ ��� ����
					// // case AUTO_RULER_MODE://�Զ� ��׼
					// // case SELF_RULER_MODE://�Ե� ��׼
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
									// // case MOTOR_DC_SERVO:
									// // case MOTOR_DC670_SERVO:
										// // DcServoGoTarget_flag=0;
										
										// // OriginalSize=OriginalSize+InputSize-CurrentSize;
										// // CurrentSize=InputSize;
										// // ServoSetCommd(SERVO_COMMD_P,STAT_30H,CurrentSize);
											// // break;
									case MOTOR_AC_SERVO:	
									case MOTOR_AC_SERVO_REV:	
										OriginalSize=OriginalSize+InputSize-CurrentSize;
										CurrentSize=InputSize;
											break;
									case MOTOR_AC_A6_SERVO:
										StartInitSize=StartInitSize+InputSize-CurrentSize;
										OriginalSize=InputSize;
										SaveA6OriginalBenchMark();//A6��׼ ����
											break;	
									}
								SaveOriginalSize();  //����ԭ��ߴ�
								
								
								//-----------------�Զ����� ��ģʽ	
								CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
								// // if(WorkMode==AUTO_RULER_MODE)   //�Զ���
									// // {
									// // WorkMode=AUTO_MODE;//����    �Զ� ��ģʽ
									// // PaperCutEnb_signal=1;
									// // }
								// // else
								if(WorkMode==MANUAL_RULER_MODE)  //�ֶ���
									{
									WorkMode=MANUAL_MODE;//����    �ֶ� ��ģʽ
									}
								// // else if(WorkMode==SELF_RULER_MODE)   //�Ե���	
									// // {
									// // WorkMode=SELF_CUT_MODE;//����    �Ե� ��ģʽ
									// // PaperCutEnb_signal=1;
									// // }
								SubModeIcon_dis(WorkMode); //��ģʽicon
								PromptNum_dis();//���뷶Χ
								PromptDis_flag=1;
								}
							
							}
						else
							{	
							
							}
							 break;						
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
						// // case MOTOR_DC_SERVO:
						// // case MOTOR_DC670_SERVO:
							// // DCServoStop();  //ֹͣ����
							// // ServoPressStop_flag=0;
							// // DcServoGoTarget_flag=0;
							// // BellStart_flag=0;
							// // //************
							// // Run_flag=0;	
							// // InTargetPosit_flag=0;	//Ŀ��λ��
							// // AutoPushRun_flag=0; //�Զ���ֽ ����
							// // AirOffOK_flag=0;
							// // PressUp_flag=0;
							// // PressDown_flag=0;
							// // TargetSize=0;
							// // TargetSize_temp=0;
							// // BeforeKnife_offset_in=0;
							// // AutoRoute_flag=0;
								// // break;
						case MOTOR_AC_SERVO:
						case MOTOR_AC_SERVO_REV:
						case MOTOR_AC_A6_SERVO:
							ACServoStop();
							//************
							Run_flag=0;	
							InTargetPosit_flag=0;	//Ŀ��λ��
							AutoPushRun_flag=0; //�Զ���ֽ ����
							AirOffOK_flag=0;
							PressUp_flag=0;
							PressDown_flag=0;
							TargetSize=0;
							TargetSize_temp=0;
							BeforeKnife_offset_in=0;
							AutoRoute_flag=0;
								break;
						}
					
					}
				}	
			}
		else//--------------------------����У׼
			{
			if(Board_TestMod==TEST_HELP)
				{
				Board_TestMod=TEST_TOUCH; //����У׼ ģʽʹ��
				GLCD_Buffer_Fill(0xffff);
				x=200,y=150,back_color=WHITE_COLOR;
				switch(Language)
					{
					case CHN_HAN:
						Printf24("������ⴥ����ɫ'ʮ'�ֹ������λ��!",x,y,0,1,back_color);
							break;
					case ENGLISH:	
						Printf24("Please touch the red 'cross'!",x,y,0,1,back_color);
							break;
					case INDONSIA:	//ӡ��	
						Printf24("Silakan Sentuh kata merah 'sepuluh' pada",x,y,0,1,back_color);y+=30;
						Printf24(" lokasi kursor",x,y,0,1,back_color);
							break;
					case PORTUGAL:	//������
						Printf24("Por favor,toque a posi??o do cursor vermelho!",x,y,0,1,back_color);
						ASCII_Printf("ca",ASCII24_MODE,12,24,PUTAO_ZK24,x+12*23,y,0,back_color);
							break;
					case SPANISH: //������
						Printf24("Por favor,toque la posici�� ",x,y,0,1,back_color);
						Printf24("                          n del cursor!",x,y,0,0,back_color);
							break;
					}
				TouchCalcu_mode=0;
				Draw_cross(TOUCH_X1,TOUCH_Y1,RED_COLOR);
				}
			else if(Board_TestMod==TEST_TOUCH)
				{
				StartHelpMode_dis();
				Board_TestMod=TEST_HELP;
				}
			}
  	     break;
    case READ_KEY_CODE:       // F2*******************�˳�
		if(WorkStart_flag==1)
		   {
			if(Run_flag==0)
			    {
				// // if(ButtonTouch_mode==0)
					// // {
					switch(WorkMode)
						{
						case TEACH_MODE://ʾ�̻�����
							WorkMode=TEACH_DIVIDE_MODE;//����---------�ȷ�ģʽ  
							F2_DividePage_dis();  
							Total_size=0;//�ܳ�
							Divide_num=0;//�ȷ���
							PorgSet_sel=0;
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case TEACH_LABEL_MODE://���� ��ǩ����	
							cursor_pro=0;		
							WorkMode=TEACH_MODE;//------------------�˳����ص�ʾ���� ����
							PaperCutEnb_signal=1;
							PorgSet_sel=0;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							SubModeIcon_dis(WorkMode);   //ʾ��ģʽname
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;		
						case TEACH_DIVIDE_MODE://���� �ȷֻ��� 
							if(DivideValue_flag==1)	//�ȷ�ֵ ģʽ
								{
								DivideValue_flag=0;//���� �ȷ��� ģʽ
								DivideTypeSelExec();	//�ȷ� ����  ѡ��........
								}
							break;
						case TEACH_PLUS_MODE:// F5++
							WorkMode=TEACH_MODE;//����
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F5_plus_dis(0);
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case TEACH_MINUS_MODE:// F6--
							WorkMode=TEACH_MODE;//����
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F6_minus_dis(0);
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						//*********************************************	
						case READ_PRO_MODE://  ����ģʽ
							ReorderProByDate_dis();	//��ʱ������ �����б�
							break;
						case READ_PRO_MESS_MODE:
							InputMode=CHAR_INPUT;
							ProMessIcon_dis();	//���뷨ģʽ icon��ʾ
							InputStus_dis(InputMode);	//���뷨  ѡ��(��ĸ)
							break;
						
							
						//*********************************************	
						case AUTO_MODE://�Զ� ��ģʽ��		
							// // WorkMode=AUTO_TOOLS_MODE;//����   ----����ģʽ*****************
							// // F1_ToolsPage_dis(); //��������
							// // Para_sel=0;
							// // PromptDis_flag=0;
							// // ACServoAlarmExec_flag=0;
							WorkMode=AUTO_DIVIDE_MODE;//����--------�Զ�-�ȷ�ģʽ  
							F2_DividePage_dis();  
							Total_size=0;//�ܳ�
							Divide_num=0;//�ȷ���
							PorgSet_sel=0;
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;		
						case AUTO_LABEL_MODE://���� ��ǩ����
							cursor_pro=0;		
							WorkMode=AUTO_MODE;//------------------�˳����ص��Զ��� ����
							PorgSet_sel=0;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							SubModeIcon_dis(WorkMode);   //���ģʽname
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							//PaperCutEnb_signal=1;
							ACServoAlarmExec_flag=0;
							break;
						case AUTO_DIVIDE_MODE://���� �ȷֻ��� 
							if(DivideValue_flag==1)	//�ȷ�ֵ ģʽ
								{
								DivideValue_flag=0;//���� �ȷ��� ģʽ
								DivideTypeSelExec();	//�ȷ� ����  ѡ��........
								}
							break;	
						// // case AUTO_RULER_MODE:	//��׼ģʽ		
						// // case AUTO_TOOLS_MODE:// ����  �Զ� -------����ģʽ
							// // WorkMode=AUTO_MODE;//����    ---------�Զ� ��ģʽ
							// // Para_sel=0;
							// // PaperCutEnb_signal=1;
							// // PressCircle_mode=0;
							// // CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							// // SubModeIcon_dis(WorkMode); //�Զ�mode name
							// // PromptNum_dis();//���뷶Χ
							// // PromptDis_flag=1;
							// // ACServoAlarmExec_flag=0;
							// // break;
						case AUTO_PLUS_MODE:// F5++
							WorkMode=AUTO_MODE;//����
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F5_plus_dis(0);
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case AUTO_MINUS_MODE:// F6--
							WorkMode=AUTO_MODE;//����
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F6_minus_dis(0);
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						//****************�Ե�
						/****
						case SELF_CUT_MODE://�Ե� ��ģʽ��		
							WorkMode=SELF_TOOLS_MODE;//���� �Ե�  ----����ģʽ*****************
							F1_ToolsPage_dis(); //��������
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
							SubModeIcon_dis(WorkMode); //�Ե�ģʽ
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
							****/
						//*******************************
						case MANUAL_MODE: //�ֶ�
							WorkMode=MANUAL_RULER_MODE; //��׼
							F2_RulerPage_dis(); //��׼ ����
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
						case MANUAL_IO_TEST_MODE: //IO mode
							WorkMode=MANUAL_MODE;//����    ---------�ֶ� ��ģʽ
							Para_sel=0;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							SubModeIcon_dis(WorkMode); //�ֶ�mode name
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						}
					// // }
				// // else if(ButtonTouch_mode==TOU_MODE_CALC)  //������ ����ģʽ
					// // {
					// // if(WorkMode==PROG_MODE)//���  ��������
						// // {
						// // AllFlagSetExec_Calc(PRESS_FLAG); //������ ����趨	
						// // }
					// // else
						// // {
						// // CalcuInClear_exec();     //��� ������
						// // switch(WorkMode)
							// // {
							// // // // case AUTO_TOOLS_MODE:
							// // case MANUAL_TOOLS_MODE:
							// // // // case SELF_TOOLS_MODE:
								// // back_color=TEXT_TAB_BACK_COLOR;	//0xef9f;
								// // x=PARA_START_X1+PARA_COL_WIDE,y=PARA_START_Y,gap=PARA_ROW_GAP;
								// // if(PramSel_Page<1)	//page 1
									// // {
									// // ParameterPage1_dis(7, 0);
									// // ParameterPage1_dis(8, 0);
									// // if((MotorType==MOTOR_DC_SERVO)||(MotorType==MOTOR_DC670_SERVO))
										// // {
										// // ParameterPage1_dis(9, 0);
										// // ParameterPage1_dis(10, 0);
										// // // ParameterPage1_dis(11, 0);
										// // }
									// // else if(MotorType>=MOTOR_AC_SERVO)	
										// // {
										// // ParameterPage1_dis(9, 0);
										// // ParameterPage1_dis(10, 0);
										// // }
									// // else if(MotorType<MOTOR_DC_SERVO)
										// // {
										// // ParameterPage1_dis(9, 0);
										// // }
									// // ParameterPage1_dis(Para_sel, 1);
									// // GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
									// // switch(Language)
										// // {
										// // case CHN_HAN:
											// // Printf24("ѹֽͣ��:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
											// // Printf24("��������:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
											// // switch(MotorType)
												// // {
												// // case MOTOR_FREQ_5_SPD_RST:
												// // case MOTOR_FREQ_3_SPD:
												// // case MOTOR_FREQ_3_SPD_RST:
													// // Printf24("���ѡ��:  ",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													// // Printf24("����ٶ�:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
													// // Printf24("�㶯�ٶ�:  ",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // case MOTOR_AC_SERVO:
												// // case MOTOR_AC_SERVO_REV:
													// // Printf24("�����ٶ�:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
													// // Printf24("���ѡ��:  ",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // }
												// // break;
										// // case ENGLISH:
											// // Printf24("Press-Stop: ",x,y,BLACK_COLOR,1,back_color);y+=gap;
											// // Printf24("AirOff-dist:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											// // switch(MotorType)
												// // {
												// // case MOTOR_FREQ_5_SPD_RST:
												// // case MOTOR_FREQ_3_SPD:
												// // case MOTOR_FREQ_3_SPD_RST:
													// // Printf24("IR-Set:  ",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													// // Printf24("Max-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													// // Printf24("Jog-speed:",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // case MOTOR_AC_SERVO:
												// // case MOTOR_AC_SERVO_REV:
													// // Printf24("Run-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													// // Printf24("IR-Set:  ",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // }
												// // break;
										// // case INDONSIA:	//ӡ��
											// // Printf24("Plat-bawah:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											// // Printf24("Off gas da: ",x,y,BLACK_COLOR,1,back_color);y+=gap;
											// // switch(MotorType)
												// // {
												// // case MOTOR_FREQ_5_SPD_RST:
												// // case MOTOR_FREQ_3_SPD:
												// // case MOTOR_FREQ_3_SPD_RST:
													// // Printf24("Set-IR: ",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													// // Printf24("Tercepat:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													// // Printf24("Jog-kecep:",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // case MOTOR_AC_SERVO:
												// // case MOTOR_AC_SERVO_REV:
													// // Printf24("Kecepa-lari:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													// // Printf24("Set-IR: ",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // }
												// // break;
										// // case PORTUGAL:	//������
											// // Printf24("encerra:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											// // Printf24("Off Air:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											// // switch(MotorType)
												// // {
												// // case MOTOR_FREQ_5_SPD_RST:
												// // case MOTOR_FREQ_3_SPD:
												// // case MOTOR_FREQ_3_SPD_RST:
													// // Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													// // Printf24("Veloci-m��  ",x,y,BLACK_COLOR,1,back_color);
													// // Printf24("          x:",x,y,BLACK_COLOR,0,back_color);y+=gap;
													// // Printf24("Veloci-Jog:",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // case MOTOR_AC_SERVO:
												// // case MOTOR_AC_SERVO_REV:
													// // Printf16("Veloci-corrida:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													// // Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // }
												// // break;
										// // case SPANISH: //������
											// // Printf24("cierre:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											// // Printf24("Off Air:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											// // switch(MotorType)
												// // {
												// // case MOTOR_FREQ_5_SPD_RST:
												// // case MOTOR_FREQ_3_SPD:
												// // case MOTOR_FREQ_3_SPD_RST:
													// // Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													// // Printf24("Veloci-m��  ",x,y,BLACK_COLOR,1,back_color);
													// // Printf24("          x:",x,y,BLACK_COLOR,0,back_color);y+=gap;
													// // Printf24("Veloci-Jog:",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // case MOTOR_AC_SERVO:
												// // case MOTOR_AC_SERVO_REV:
													// // Printf16("Veloci-corrida:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													// // Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
														// // break;
												// // }
												// // break;		
										// // }	
									// // }
								// // break;
							
							// // case  PROG_MODE://��̻�����
							// // case AUTO_MODE://�Զ���������
							// // case AUTO_PLUS_MODE://�Զ�F5++
							// // case AUTO_MINUS_MODE://�Զ�F6--
							// // case TEACH_MODE://ʾ�� ģʽ
							// // case AUTO_TO_SELF_MODE:   //�Զ�-->�Ե����� ģʽ
							// // case SELF_CUT_MODE:  //�Ե��� ģʽ
							// // case TEACH_PLUS_MODE: //�Ե� F5++
							// // case TEACH_MINUS_MODE://�Ե� F6--
								// // if(Knife_order>OnePro_head.pro_knifeSUM)
									 // // K_temp=Knife_order-1;
								 // // else
									 // // K_temp=Knife_order;
								// // ProgressBar_dis(OnePro_head.pro_knifeSUM,K_temp);  //������ ��ʾ
								// // KnifeUp_flag=0;
								// // KnifeDown_flag=0;
								// // PressUp_flag=0;
								// // PressDown_flag=0;
								// // A_Down_flag=0;
								// // B_Down_flag=0;
								// // A_Up_flag=0;
								// // B_Up_flag=0;
								// // IR_Up_flag=0;
								// // IR_Down_flag=0;
								// // //--------------������ʾ��������ֽ��־
								
								// // Size_1page_dis(Knife_order-cursor_row,0);//һҳ�ߴ���ʾ
								// // break;	
							// // }
						// // }
					// // }
				// // else if(ButtonTouch_mode==TOU_MODE_F4)  // ��� ������
					// // {
					// // AllFlagSetExec(PRESS_FLAG); //�趨 ѹֽ���
					// // }
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
							// // case MOTOR_DC_SERVO:
							// // case MOTOR_DC670_SERVO:
								// // DCServoStop();  //ֹͣ����
								// // ServoPressStop_flag=0;
								// // DcServoGoTarget_flag=0;
								// // BellStart_flag=0;
								// // //************
								// // Run_flag=0;	
								// // InTargetPosit_flag=0;	//Ŀ��λ��
								// // AutoPushRun_flag=0; //�Զ���ֽ ����
								// // TargetSize=0;
								// // TargetSize_temp=0;
								// // BeforeKnife_offset_in=0;
								// // AutoRoute_flag=0;
									// // break;
							case MOTOR_AC_SERVO:
							case MOTOR_AC_SERVO_REV:
							case MOTOR_AC_A6_SERVO:
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
			// // ClrInput_function();//���� �����
		   }
		else  
		   {
			if(Board_TestMod==TEST_HELP)
				{
				Manual_page=0;
				Comment_dis_page(Manual_page);//ע��1
				Board_TestMod=TEST_ICON;
				}
			else if(Board_TestMod==TEST_ICON)
				{
				StartHelpMode_dis();
				Board_TestMod=TEST_HELP;
				Manual_page=0;
				}
		   }
  	     break;
    case RETURN_KEY_CODE:      //F3************
		if(WorkStart_flag==1)
		   {
			if(Run_flag==0)
			    {
					switch(WorkMode)
						{
						
						case AUTO_DIVIDE_MODE://���� �ȷֻ��� 
						case TEACH_DIVIDE_MODE://���� �ȷֻ��� 
							if(DivideValue_flag==0)	//�ȷ��� ģʽ
								{
								DivideValue_flag=1;//���� �ȷ�ֵ ģʽ
								DivideTypeSelExec();	//�ȷ� ����  ѡ��........
								}
							break;
						case READ_PRO_MODE://  ����ѡ�����ģʽ	˳����ʾ	
						// // case TEACH_PRO_MODE:	//����ѡ�����ģʽ	˳����ʾ
							DisAllProgMode=PRO_BY_NUM;
							ProTableIcon_dis();	//�����б�ģʽ�� icon��ʾ
							for(g=1;g<=MAX_PROG;g++)
								ProNumGroup[g]=g;
							prog_order=1;
							CursorPro_dis(cursor_pro,0);//pro���
							cursor_pro=0;
							Prog_1page_dis(prog_order, cursor_pro);//===����---������ʾ
							TableDis_startcol=PROC_NUM_X;
							CursorPro_dis(cursor_pro,1);//pro���
							OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//һ������ ��ʾ
							break;
						case READ_PRO_MESS_MODE:
							InputMode=NUMBER_INPUT;
							ProMessIcon_dis();	//���뷨ģʽ icon��ʾ
							InputStus_dis(InputMode);	//���뷨  ѡ��(����)
							break;
							
						
						case TEACH_MODE:	
						case AUTO_MODE://�Զ� ��ģʽ��************  ����
							//ClrInput_function();//���� �����
							// // WorkMode=AUTO_PLUS_MODE;  //F5++
							// // F5_plus_dis(1);//  ++
							if(num_cou>0)
								{
								if(CheckInputNums()==1)// ���� ��Ч
									{
									if(Knife_order<=OnePro_head.pro_knifeSUM)
										{
										if(OnePro_head.pro_knifeSUM<MAX_Knife)
											{
											OnePro_head.pro_knifeSUM++;
											InsertOneKnife(Pro_data.pro_num, Knife_order);
											pKnife_data=(pInt8U)&OneKnife_data;
											// GetOneKnife_datas(Knife_order, pKnife_data);//
											OneKnife_data.size=InputSize;  //�ߴ��޸�
											OneKnife_data.k_flag=NO_FLAG;  //��� ��־
											SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//����һ������
											//------------------//��һ�� ����� ���
											if((Knife_order+1)<=OnePro_head.pro_knifeSUM)
												{
												GetOneKnife_datas(Pro_data.pro_num, Knife_order+1, pKnife_data);//��һ��
												if((OneKnife_data.k_flag&0xf)==KNIFE_FLAG) //�� ��־
													{
													if(OneKnife_data.size>InputSize)
														{
														OneKnife_data.k_flag&=0xf0;	//����� ���
														SaveOneKnife_datas(Pro_data.pro_num, Knife_order+1 , pKnife_data);//����һ������
														}
													}
												}
											//-----��ʾ
											//KnifeSize_dis(cursor_row,InputSize);//�ߴ�
											StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//�������
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
												case INDONSIA:	//ӡ��
													Printf16("Penuh, tidak dapat dimasukkan",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
													break;
												case PORTUGAL:	//������
													Printf16("Dados est��cheio, n?o pode entrar",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
													ASCII_Printf("a",ASCII16_MODE,8,16,PUTAO_ZK16,REMIND_WINDOW_X+8*19,REMIND_WINDOW_Y+5,RED_COLOR,0xffff);
													break;
												case SPANISH: //������
													Printf16("No puede insertar datos se ha llenado",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
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
											case INDONSIA:	//ӡ��
												Printf16("Tekan tombol OK setelah masukan",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
													break;	
											case PORTUGAL:	//������
												Printf24("Clique no bot?o OK",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												ASCII_Printf("a",ASCII24_MODE,12,24,PUTAO_ZK24,REMIND_WINDOW_X+12*13,REMIND_WINDOW_Y+5,RED_COLOR,0xffff);
													break;	
											case SPANISH: //������
												Printf24("Haga clic en el bot��",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
												Printf24("                    n OK",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
													break;	
											}
										}
									}
								} 		
							break;
							
						case MANUAL_MODE: //�ֶ�-----------------------
							WorkMode=MANUAL_CLOCK_MODE; // ʱ�� ģʽ
							Para_sel=0;PromptDis_flag=0;
							ClockPage_dis();
							Year_before=Year,Month_before=Month,Day_before=Dom; //��ǰʱ�� �ݴ�
							ACServoAlarmExec_flag=0;
							break;
						}
				// // else if(ButtonTouch_mode==TOU_MODE_CALC)  //������ ����ģʽ
					// // {
					// // if(WorkMode==PROG_MODE)//���  ��������
						// // {
						// // AllFlagSetExec_Calc(SORT_FLAG); //������ ����趨	
						// // }
					// // }
				// // else if(ButtonTouch_mode==TOU_MODE_F4)  // ��� ������	
					// // {
					// // AllFlagSetExec(SORT_FLAG); //�趨 ��ֽ���
					// // }
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
						// // case MOTOR_DC_SERVO:
						// // case MOTOR_DC670_SERVO:
							// // DCServoStop();  //ֹͣ����
							// // ServoPressStop_flag=0;
							// // DcServoGoTarget_flag=0;
							// // BellStart_flag=0;
							// // //************
							// // Run_flag=0;	
							// // InTargetPosit_flag=0;	//Ŀ��λ��
							// // AutoPushRun_flag=0; //�Զ���ֽ ����
							// // TargetSize=0;
							// // TargetSize_temp=0;
							// // BeforeKnife_offset_in=0;
							// // AutoRoute_flag=0;
								// // break;
						case MOTOR_AC_SERVO:
						case MOTOR_AC_SERVO_REV:
						case MOTOR_AC_A6_SERVO:
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
		    }
		else
			{
			if(Board_TestMod==TEST_HELP)
				{
				Board_TestMod=TEST_BOARD;     //�������  ģʽ****************************
				GLCD_Buffer_Fill(0xffff);
				IO_InputDisInit();  //Io ����ڳ�ʼֵ
				KeyDis_Init();//������ʾ��ʼ��
				}
			else if(Board_TestMod==TEST_BOARD)
				{
				// StartHelpMode_dis();
				// Board_TestMod=TEST_HELP;
				}
			}
  	     break;    
	case MANUAL_KEY_CODE:   // F4************** 
		if(WorkStart_flag==1)
		   {
		    if(Run_flag==0)
			    {
					switch(WorkMode)
						{
							/***
						case PROG_MODE://��� ��������
							AllFlagSetExec(PUSH_FLAG); //�趨 ��ֽ���// Set_AllFlagWind_In();  //F4 ���λ	ģʽ
							FirstKnife_num=0;
							LastKnife_num_temp=0;
								// // ClrInput_function();//���� �����
							break;**/
						case AUTO_DIVIDE_MODE://���� �ȷֻ��� 
							cursor_pro=0;		
							WorkMode=AUTO_MODE;//------------------�˳����ص��Զ��� ����
							PorgSet_sel=0;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							SubModeIcon_dis(WorkMode);   //���ģʽname
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case TEACH_DIVIDE_MODE://���� �ȷֻ���
							cursor_pro=0;		
							WorkMode=TEACH_MODE;//------------------�˳����ص�ʾ���� ����
							PaperCutEnb_signal=1;
							PorgSet_sel=0;
							CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
							SubModeIcon_dis(WorkMode);   //ʾ��ģʽname
							PromptNum_dis();//���뷶Χ
							PromptDis_flag=1;
							ACServoAlarmExec_flag=0;
							break;
						case READ_PRO_MODE:		// ����ģʽ
						// // case TEACH_PRO_MODE:	//F3�����б� ģʽ
							DeleteOneProg(cursor_pro, prog_order);		//F6--ɾ��һ������
							break;
						case READ_PRO_MESS_MODE: //������Ϣģʽ
						// // case TEACH_PRO_MESS_MODE: //������Ϣģʽ
							F4MessageMode_Exit(); //�˳�  ������Ϣģʽ
							SubModeIcon_dis(WorkMode);   //����ѡ��ģʽ
							break;	
						case TEACH_MODE://ʾ�� ��������
						case AUTO_MODE://�Զ� ��ģʽ��************ɾ��һ��
							// // ClrInput_function();//���� �����
							// // WorkMode=AUTO_MINUS_MODE;// F6--
							// // F6_minus_dis(1);//--
							if(Knife_order<=OnePro_head.pro_knifeSUM)
								{
								DeleteOneKnife(Pro_data.pro_num, Knife_order);      //ɾ��һ��
								if(OnePro_head.pro_knifeSUM>1)
									{
									OnePro_head.pro_knifeSUM--;
									SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);
									StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//�������
									
									if(Knife_order<=OnePro_head.pro_knifeSUM)
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
										if((OneKnife_data.k_flag&0xf)==KNIFE_FLAG) //�� ��־
											{
											if(OneKnife_data.size>perv_data)
												{
												OneKnife_data.k_flag&=0xf0;//��� �� ��־
												Flg_chg=1;
												flag_now=OneKnife_data.k_flag;	//��ǰ��� �ݴ�
												SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//����һ������
												}
											}	
										}
									}
								Size_1page_dis(Knife_order,cursor_row);
								
								if(Flg_chg==1)
									{
									AllFlagPic_dis(cursor_row,flag_now); //��괦  ���ͼƬ ��ʾ
									}
								}
							break;
						
						case MANUAL_MODE: //�������� ����
							if(MotorType>=MOTOR_AC_SERVO)
								{
								ElectricWheelOn_flag=!ElectricWheelOn_flag;
								SaveElectricWheelSwitch();//��������
								ElectricalWheel_dis();  //��������  ����״̬
								}
							break;
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
						// // case MOTOR_DC_SERVO:
						// // case MOTOR_DC670_SERVO:
							// // DCServoStop();  //ֹͣ����
							// // ServoPressStop_flag=0;
							// // DcServoGoTarget_flag=0;
							// // BellStart_flag=0;
							// // //************
							// // Run_flag=0;	
							// // InTargetPosit_flag=0;	//Ŀ��λ��
							// // AutoPushRun_flag=0; //�Զ���ֽ ����
							// // TargetSize=0;
							// // TargetSize_temp=0;
							// // BeforeKnife_offset_in=0;
							// // AutoRoute_flag=0;
								// // break;
						case MOTOR_AC_SERVO:
						case MOTOR_AC_SERVO_REV:
						case MOTOR_AC_A6_SERVO:
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
					}		
				}
		   }
		else
			{
			if(Board_TestMod==TEST_HELP)
				{
				Board_TestMod=TEST_SYS_WORD;   
				SysBoardSelect_dis();  //ϵͳ�汾ѡ�� �������****************************
				}
			else if(Board_TestMod==TEST_SYS_WORD)
				{
				for(num_cou=0;num_cou<8;num_cou++)
					 {
					 Size_temp[num_cou++]=0;
					 }
				num_cou=0; //;  //ϵͳ�汾ѡ��   �˳�
				StartHelpMode_dis();
				Board_TestMod=TEST_HELP;
				}
			}
		
  	     break; 
	case F6_KEY_CODE:	//F6
			F6_KeyExec();//F6  ����
			break;
	case F5_KEY_CODE:	//F5
			F5_KeyExec();//F5  ����
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
					/***
					if(num_cou>0)
						ClrInput_function();//���� �����
					if(ButtonTouch_mode==0)
						{
						switch(WorkMode)
							{
							case AUTO_TO_SELF_MODE:  //�Զ�-->�Ե����� ģʽ
									
									break;
							case PROG_PRO_MESS_MODE: //������Ϣģʽ
							case TEACH_PRO_MESS_MODE: //������Ϣģʽ
									ClrInputName_exec();		//����������	
									break;
							case PROG_DEL_ALL_PRO_MODE://ɾ������pro
							case TEACH_DEL_ALL_PRO_MODE://ɾ������pro
							case PROG_DEL_ALL_SIZE_MODE://	ɾ�����гߴ�
							case TEACH_DEL_ALL_SIZE_MODE://	ɾ�����гߴ�
									DeleteAllExitWind();	//�˳�ȫɾ ��ʾ��	
									break;
							}
						}
					else if(ButtonTouch_mode==TOU_MODE_CALC)
						{
						if(CalcNoNumInput_flag==0)//  �������Ѿ����� ����
							{
							ClearCalculatorInput(); //��������� ����
							}
						}
					else if(ButtonTouch_mode==TOU_MODE_AUTOCUT_IN) //�Զ�-->�Ե�����  	��ʾ
						{
						ButtonTouch_mode=0;
						if(WorkMode==AUTO_TO_SELF_MODE)  //�Զ�-->�Ե����� ģʽ
							{
							if(ReEnterAutoKnife_dis==0) //������ ��ʾ  ��ʾ
								{
								// WorkMode=AUTO_MODE;//���� �Զ���
								WorkMode=MainMode_temp;//���� ֮ǰģʽ
								PaperCutEnb_signal=1;
								PressCircle_mode=0;
								CurrentArea_recover2(SELF_PROMP_X,SELF_PROMP_Y,SELF_PROMP_WIDE,SELF_PROMP_HIGH);
								}
							else   //�ٴ�  ���� ��һ��
								{
								if(ButtonTouch_mode==TOU_MODE_CALC)  //	  ���� ��
									CalcuInClear_exec();     //��� ������
								WorkMode=SELF_CUT_MODE;  //����   ----------�Ե��� ģʽ
								CurrentArea_recover2(SELF_PROMP_X,SELF_PROMP_Y,SELF_PROMP_WIDE,SELF_PROMP_HIGH);
								AutoCutModePage_dis(); //�Ե�ģʽ ���ֻ�����ʾ
								//------------���ص�һ��
								ClrInput_function();//���� ����� 
								CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
								cursor_row=0;
								CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
								Knife_order=1;//
								Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
								if(Knife_order<=OnePro_head.pro_knifeSUM)
									StepOrder_dis(Knife_order);//������� 
									
								LastAutoKnife_order=1;
								ReEnterAutoKnife_dis=0;
								AutoCutDisable_flag=0;
								}
							}
						}
						***/
					switch(WorkMode)
						{
						case AUTO_TO_SELF_MODE:  //�Զ�-->�Ե����� ģʽ
								if(ReEnterAutoKnife_dis==0) //������ ��ʾ  ��ʾ
									{
									// WorkMode=AUTO_MODE;//���� �Զ���
									WorkMode=MainMode_temp;//���� ֮ǰģʽ
									PaperCutEnb_signal=1;
									PressCircle_mode=0;
									CurrentArea_recover2(SELF_PROMP_X,SELF_PROMP_Y,SELF_PROMP_WIDE,SELF_PROMP_HIGH);
									}
								else   //�ٴ�  ���� ��һ��
									{
									WorkMode=SELF_CUT_MODE;  //����   ----------�Ե��� ģʽ
									CurrentArea_recover2(SELF_PROMP_X,SELF_PROMP_Y,SELF_PROMP_WIDE,SELF_PROMP_HIGH);
									AutoCutModePage_dis(); //�Ե�ģʽ ���ֻ�����ʾ
									//------------���ص�һ��
									// // ClrInput_function();//���� ����� 
									CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
									cursor_row=0;
									CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
									Knife_order=1;//
									Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
									if(Knife_order<=OnePro_head.pro_knifeSUM)
										StepOrder_dis(Knife_order);//������� 
										
									LastAutoKnife_order=1;
									ReEnterAutoKnife_dis=0;
									}
								break;
						case READ_PRO_MESS_MODE: //������Ϣģʽ
						// // case TEACH_PRO_MESS_MODE: //������Ϣģʽ
								ClrInputName_exec();		//����������	
								break;
						case READ_DEL_ALL_PRO_MODE://ɾ������pro
						// // case TEACH_DEL_ALL_PRO_MODE://ɾ������pro
						case AUTO_DEL_ALL_SIZE_MODE://	ɾ�����гߴ�
						case TEACH_DEL_ALL_SIZE_MODE://	ɾ�����гߴ�
								DeleteAllExitWind();	//�˳�ȫɾ ��ʾ��	
								break;
						default :
								if(CalcNoNumInput_flag==0)//  �������Ѿ����� ����
								{
								ClearCalculatorInput(); //��������� ����
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
					case MOTOR_AC_SERVO:
					case MOTOR_AC_SERVO_REV:
					case MOTOR_AC_A6_SERVO:
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
					// // case MOTOR_DC_SERVO:
							// // break;
					}
				ClrSysBoardNum_dis(); //��� ϵͳѡ��  ����	>>>>>>>>>>>>>>>>>>>>
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
						// if(Sign_flag==1)
							// {
							// num_cou=0;
							// GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//�ߴ������
							// Sign_flag=0;
							// }
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
				// // case MOTOR_DC_SERVO:
				// // case MOTOR_DC670_SERVO:
					// // if(StartCheck_mode<2)
						// // {
						// // GoFrontEn_flag=1;
						// // GoFast_flag=0;
						// // ManualMoveMode=0;
						// // }
						// // break;
				case MOTOR_AC_SERVO:
				case MOTOR_AC_SERVO_REV:
				case MOTOR_AC_A6_SERVO:
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
	case FAST_AHEAD_KEY_CODE:   //�������***************
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
						       qianjinflag=1;
						GoFrontEn_flag=1;
						GoFast_flag=1;
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
						GoFast_flag=1;
						ManualMoveMode=0;
						}
						break;
				// // case MOTOR_DC_SERVO:
				// // case MOTOR_DC670_SERVO:
					// // if(StartCheck_mode<2)
						// // {
						// // GoFrontEn_flag=1;
						// // GoFast_flag=1;
						// // ManualMoveMode=0;
						// // }
						// // break;
				case MOTOR_AC_SERVO:
				case MOTOR_AC_SERVO_REV:
				case MOTOR_AC_A6_SERVO:
					if(StartCheck_mode<=2)
						{
						GoFrontEn_flag=1;
						GoFast_flag=1;
						ManualMoveMode=0;
						}
						break;
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
				// // case MOTOR_DC_SERVO:
				// // case MOTOR_DC670_SERVO:
					// // if(StartCheck_mode<2)
						// // {
						// // GoBackEn_flag=1;
						// // GoFast_flag=0;
						// // ManualMoveMode=0;
						// // }
						// // break;
				case MOTOR_AC_SERVO:
				case MOTOR_AC_SERVO_REV:
				case MOTOR_AC_A6_SERVO:
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
	case FAST_BACK_KEY_CODE:     //���˰���**************
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
						GoFast_flag=1;
						ManualMoveMode=0;
						}
						break;
				// // case MOTOR_DC_SERVO:
				// // case MOTOR_DC670_SERVO:
					// // if(StartCheck_mode<2)
						// // {
						// // GoBackEn_flag=1;
						// // GoFast_flag=1;
						// // ManualMoveMode=0;
						// // }
						// // break;
				case MOTOR_AC_SERVO:
				case MOTOR_AC_SERVO_REV:
				case MOTOR_AC_A6_SERVO:
					if(StartCheck_mode<=2)
						{
						GoBackEn_flag=1;
						GoFast_flag=1;
						ManualMoveMode=0;
						}
						break;
				}	
			}
  	     break;	 
    case REV_KEY_CODE:   //  ��+��  ***************
        if(WorkStart_flag==1)  
			{
			if(Run_flag==0)
			    {
				CalculatorValue_exec('+');	
				}	
            } 
         break;        
    case OPTION_KEY_CODE:    //����  ��-/����  *************
       if(WorkStart_flag==1)  
			{
			if(Run_flag==0)
			    {
				CalculatorValue_exec('-');	
				// else if(ButtonTouch_mode==TOU_MODE_F4)//���  ģʽ
					// {
					// NumKey_exec('-');
					// }
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
				// // case PROG_MODE://��̻�����
				case TEACH_MODE://ʾ�̻�����
				case AUTO_MODE://�Զ���������
				case SELF_CUT_MODE://�Ե���������
					
							break;
				// // case AUTO_TOOLS_MODE://  ��������
				// // case SELF_TOOLS_MODE://  ��������
				case MANUAL_TOOLS_MODE:// �ֶ� ����ģʽ
					if(PramSel_Page<1)	//page 1
						{
						switch(Para_sel)
							{
							case 3://����
								Language++;
								if(Language>3)
									Language=0;
								//***********�������Ը���
								x=PARA_START_X1,y=PARA_START_Y;back_color=TEXT_TAB_BACK_COLOR,gap=PARA_ROW_GAP;//
								GLCD_SetWindow_Fill(x,y,x+145,y+(PARA_ROW_GAP*7)-20,back_color,back_color);
								GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*7-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
								switch(Language)
									{
									case CHN_HAN:
										x=PARA_START_X1,y=PARA_START_Y,gap=PARA_ROW_GAP;//0xef9f;
										Printf24("ǰ����:    ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("�м���:    ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("����:    ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("����:    ",x,y,BLACK_COLOR,1,back_color);  y+=gap;
										Printf24("��λ:   ",x,y,BLACK_COLOR,1,back_color);  y+=gap;
										Printf24("��ǰ��:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										//Printf24("��׼����:   ",x,y,BLACK_COLOR,1,back_color);
										Printf24("��ֽ����:  ",x,y,BLACK_COLOR,1,back_color);
										if(ButtonTouch_mode==0)  //	 �� ���������� ��
											{
											x+=PARA_COL_WIDE;y=PARA_START_Y;
											GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
											Printf24("ѹֽͣ��: ",x,y,BLACK_COLOR,1,back_color);y+=gap;
											Printf24("��������: ",x,y,BLACK_COLOR,1,back_color);y+=gap;
											ParameterPage1_dis(7, 0);
											
											switch(MotorType)
												{
												case MOTOR_FREQ_5_SPD_RST:
												case MOTOR_FREQ_3_SPD:
												case MOTOR_FREQ_3_SPD_RST:
													Printf24("���ѡ��:  ",x,y,BLACK_COLOR,1,back_color);
													ParameterPage1_dis(9, 0);
														break;
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													// // Printf24("����ٶ�:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
													// // Printf24("�㶯�ٶ�:  ",x,y,BLACK_COLOR,1,back_color);
													// // // ParameterPage1_dis(11, 0);
														// // break;
												case MOTOR_AC_SERVO:
												case MOTOR_AC_SERVO_REV:
												case MOTOR_AC_A6_SERVO:
													Printf24("�����ٶ�:  ",x,y,BLACK_COLOR,1,back_color);y+=gap;
													Printf24("���ѡ��:  ",x,y,BLACK_COLOR,1,back_color);
													ParameterPage1_dis(10, 0);
														break;
												}
											}
										x=PROG_X,y=PROG_Y;back_color=STEP_BACK_COLOR;
										GLCD_SetWindow_Fill( x, y, x+100, y+24, back_color,back_color);//clear text win
										Printf16(" ����  ",x,y,BLACK_COLOR,1,back_color);
										x=STEP_X;//
										GLCD_SetWindow_Fill( x, y, x+100, y+24, back_color,back_color);//clear text win
										Printf16(" ����  ",x,y,BLACK_COLOR,1,back_color);//
										break;
									case ENGLISH:	
										x=PARA_START_X1,y=PARA_START_Y,gap=PARA_ROW_GAP;//back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
										Printf24("Front-limit:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Midd-limit: ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Back-limit: ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Language:   ",x,y,BLACK_COLOR,1,back_color);  y+=gap;
										Printf24("Unit:       ",x,y,BLACK_COLOR,1,back_color);  y+=gap;
										Printf24("Advanced:   ",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Push-distan:",x,y,BLACK_COLOR,1,back_color);
										if(ButtonTouch_mode==0)  //	 �� ���������� ��
											{
											x+=PARA_COL_WIDE;y=PARA_START_Y;
											GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
											Printf24("Press-Stop:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											Printf24("AirOff-dist:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											ParameterPage1_dis(7, 0);
											switch(MotorType)
												{
												case MOTOR_FREQ_5_SPD_RST:
												case MOTOR_FREQ_3_SPD:
												case MOTOR_FREQ_3_SPD_RST:
													Printf24("IR-Set:  ",x,y,BLACK_COLOR,1,back_color);
													ParameterPage1_dis(9, 0);
														break;
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													// // Printf24("Max-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													// // Printf24("Jog-speed:",x,y,BLACK_COLOR,1,back_color);
													// // // ParameterPage1_dis(11, 0);
														// // break;
												case MOTOR_AC_SERVO:
												case MOTOR_AC_SERVO_REV:
												case MOTOR_AC_A6_SERVO:
													Printf24("Run-speed:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													Printf24("IR-Set:  ",x,y,BLACK_COLOR,1,back_color);
													ParameterPage1_dis(10, 0);
														break;
												}
											}
										x=PROG_X,y=PROG_Y;back_color=STEP_BACK_COLOR;
										GLCD_SetWindow_Fill( x, y, x+100, y+24, back_color,back_color);//clear text win
										Printf16("Process",x,y,BLACK_COLOR,1,back_color);
										x=STEP_X;//
										GLCD_SetWindow_Fill( x, y, x+100, y+24, back_color,back_color);//clear text win
										Printf16(" Step  ",x,y,BLACK_COLOR,1,back_color);
										break;
									case INDONSIA:	//ӡ��
										x=PARA_START_X1,y=PARA_START_Y,gap=PARA_ROW_GAP;//back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
										Printf24("Sete-batas:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Dala-batas:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Sebe-batas:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Bahasa:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
										Printf24("Satuan:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
										Printf24("Memajukan:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Doro-jarak:",x,y,BLACK_COLOR,1,back_color);
										if(ButtonTouch_mode==0)  //	 �� ���������� ��
											{
											x+=PARA_COL_WIDE;y=PARA_START_Y;
											GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
											Printf24("Plat-bawah:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											Printf24("Off gas da: ",x,y,BLACK_COLOR,1,back_color);y+=gap;
											ParameterPage1_dis(7, 0);
											switch(MotorType)
												{
												case MOTOR_FREQ_5_SPD_RST:
												case MOTOR_FREQ_3_SPD:
												case MOTOR_FREQ_3_SPD_RST:
													Printf24("Set-IR: ",x,y,BLACK_COLOR,1,back_color);
													ParameterPage1_dis(9, 0);
														break;
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													// // Printf24("Tercepat:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													// // Printf24("Jog-kecep:",x,y,BLACK_COLOR,1,back_color);
													// // // ParameterPage1_dis(11, 0);
														// // break;
												case MOTOR_AC_SERVO:
												case MOTOR_AC_SERVO_REV:
												case MOTOR_AC_A6_SERVO:
													Printf24("Kecepa-lari:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													Printf24("Set-IR: ",x,y,BLACK_COLOR,1,back_color);
													ParameterPage1_dis(10, 0);
														break;
												}
											}
										x=PROG_X,y=PROG_Y;back_color=STEP_BACK_COLOR;
										GLCD_SetWindow_Fill( x, y, x+100, y+24, back_color,back_color);//clear text win
										Printf16("Program",x,y,BLACK_COLOR,1,back_color);
										x=STEP_X;//
										GLCD_SetWindow_Fill( x, y, x+100, y+24, back_color,back_color);//clear text win
										Printf16("Langkah",x,y,BLACK_COLOR,1,back_color);
										break;	
									case PORTUGAL:	//������
										x=PARA_START_X1,y=PARA_START_Y,gap=PARA_ROW_GAP;//back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
										Printf24("O ex-limite:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("Intermedi:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("ap��        ",x,y,BLACK_COLOR,1,back_color);
										Printf24("   s-limite:",x,y,BLACK_COLOR,0,back_color);y+=gap;
										Printf24("l��    ",x,y,BLACK_COLOR,1,back_color); 
										Printf24("  ngua:",x,y,BLACK_COLOR,0,back_color);  y+=gap;
										Printf24("unidade:",x,y,BLACK_COLOR,1,back_color);  y+=gap;
										Printf24("antes:",x,y,BLACK_COLOR,1,back_color);y+=gap;
										Printf24("distancia:",x,y,BLACK_COLOR,1,back_color);
										if(ButtonTouch_mode==0)  //	 �� ���������� ��
											{
											x+=PARA_COL_WIDE;y=PARA_START_Y;
											GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
											Printf24("encerra:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											Printf24("Off Air:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											ParameterPage1_dis(7, 0);
											switch(MotorType)
												{
												case MOTOR_FREQ_5_SPD_RST:
												case MOTOR_FREQ_3_SPD:
												case MOTOR_FREQ_3_SPD_RST:
													Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
													ParameterPage1_dis(9, 0);
														break;
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													// // Printf24("Veloci-m��  ",x,y,BLACK_COLOR,1,back_color);
													// // Printf24("          x:",x,y,BLACK_COLOR,0,back_color);y+=gap;
													// // Printf24("Veloci-Jog:",x,y,BLACK_COLOR,1,back_color);
													// // // ParameterPage1_dis(11, 0);
														// // break;
												case MOTOR_AC_SERVO:
												case MOTOR_AC_SERVO_REV:
												case MOTOR_AC_A6_SERVO:
													Printf16("Veloci-corrida:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
													ParameterPage1_dis(10, 0);
														break;
												}
											}
										x=PROG_X,y=PROG_Y;back_color=STEP_BACK_COLOR;
										GLCD_SetWindow_Fill( x, y, x+100, y+24, back_color,back_color);//clear text win
										Printf16("Programa",x,y,BLACK_COLOR,1,back_color);
										x=STEP_X;//
										GLCD_SetWindow_Fill( x, y, x+100, y+24, back_color,back_color);//clear text win
										Printf16(" Passo ",x,y,BLACK_COLOR,1,back_color);
										break;	
									case SPANISH: //������
										x=PARA_START_X1,y=PARA_START_Y,gap=PARA_ROW_GAP;
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
										if(ButtonTouch_mode==0)  //	 �� ���������� ��
											{
											x+=PARA_COL_WIDE;y=PARA_START_Y;
											GLCD_SetWindow_Fill( x, y, x+tx_wide, y+(gap*4-10), TEXT_TAB_BACK_COLOR, TEXT_TAB_BACK_COLOR);//clear text win
											Printf24("cierre:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											Printf24("Off Air:",x,y,BLACK_COLOR,1,back_color);y+=gap;
											ParameterPage1_dis(7, 0);
											switch(MotorType)
												{
												case MOTOR_FREQ_5_SPD_RST:
												case MOTOR_FREQ_3_SPD:
												case MOTOR_FREQ_3_SPD_RST:
													Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
													ParameterPage1_dis(9, 0);
														break;
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													// // Printf24("Veloci-m��  ",x,y,BLACK_COLOR,1,back_color);
													// // Printf24("          x:",x,y,BLACK_COLOR,0,back_color);y+=gap;
													// // Printf24("Veloci-Jog:",x,y,BLACK_COLOR,1,back_color);
													// // // ParameterPage1_dis(11, 0);
														// // break;
												case MOTOR_AC_SERVO:
												case MOTOR_AC_SERVO_REV:
												case MOTOR_AC_A6_SERVO:
													Printf16("Veloci-corrida:",x,y,BLACK_COLOR,1,back_color);y+=gap;
													Printf24("estado IR:",x,y,BLACK_COLOR,1,back_color);
													ParameterPage1_dis(10, 0);
														break;
												}
											}
										x=PROG_X,y=PROG_Y;back_color=STEP_BACK_COLOR;
										GLCD_SetWindow_Fill( x, y, x+100, y+24, back_color,back_color);//clear text win
										Printf16("Programa",x,y,BLACK_COLOR,1,back_color);
										x=STEP_X;//
										GLCD_SetWindow_Fill( x, y, x+100, y+24, back_color,back_color);//clear text win
										Printf16(" Paso ",x,y,BLACK_COLOR,1,back_color);
										break;	
									}
								ParameterPage1_dis(Para_sel, 1);
								if(ButtonTouch_mode==TOU_MODE_CALC)  //	  ���������� ��
									{
									Button_dis(BUTT_INSERT, 1); //���� ��ť ��ʾ
									Button_dis(BUTT_EXIT, 0); //���� ��ť ��ʾ
									Button_dis(BUTT_ENTER, 0); //���� ��ť ��ʾ
									}
								//.........................���� ��
								ModeName_dis(WorkMode);	
								CursorSizeName();	//��Ƴߴ�
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
								ParameterPage1_dis(0, 0);
								ParameterPage1_dis(1, 0);
								ParameterPage1_dis(2, 0);
								ParameterPage1_dis(5, 0);
								ParameterPage1_dis(6, 0);
								if(ButtonTouch_mode==0)  //	 �� ���������� ��
									{
									ParameterPage1_dis(8, 0);
									if(MotorType>=MOTOR_AC_SERVO)
										{
										ParameterPage1_dis(9, 0);
										}
									}
									
								ParameterPage1_dis(Para_sel, 1);	
								SaveUnit();	
								break;
							case 7:  //ѹֽ ͣ��
								if(PressValid_flag==0)
									PressValid_flag=1;
								else 
									PressValid_flag=0;
								if(ButtonTouch_mode==0)  //	  !���������� ��
									ParameterPage1_dis(Para_sel, 1);	
								SavePressValid_flag();	
								break;
							case 9:
								if(MotorType<MOTOR_AC_SERVO)	//(MotorType<MOTOR_DC_SERVO)
									{
									if(IR_SensorStus==0)
										IR_SensorStus=1;
									else
										IR_SensorStus=0;
									if(ButtonTouch_mode==0)  //	  !���������� ��
										ParameterPage1_dis(Para_sel, 1);	
									SaveIRValidStatus();
									}
								break;
							case 10:
								if(MotorType>=MOTOR_AC_SERVO)
									{
									if(IR_SensorStus==0)
										IR_SensorStus=1;
									else
										IR_SensorStus=0;
									if(ButtonTouch_mode==0)  //	  !���������� ��
										ParameterPage1_dis(Para_sel, 1);	
									SaveIRValidStatus();	
									}
								break;	
								/***
							case 11:
								if((MotorType<MOTOR_AC_SERVO)&&(MotorType>MOTOR_FREQ_3_SPD_RST))
									{
									if(IR_SensorStus==0)
										IR_SensorStus=1;
									else
										IR_SensorStus=0;
									if(ButtonTouch_mode==0)  //	  !���������� ��
										ParameterPage1_dis(Para_sel, 1);	
									SaveIRValidStatus();	
									}
								break;	
								***/
							}
						}
					else	//page 2
						{
						switch(Para2_sel)
							{
							case 2:	//�����л�����ģʽ���
								if(IRChgWorkmodeValid_flag!=0)
									IRChgWorkmodeValid_flag=0;
								else
									IRChgWorkmodeValid_flag=1;
								SaveIRChgWorkmodeValid();
								ParameterPage2_dis(Para2_sel, 1);	
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
				case TEACH_MODE://ʾ�̻�����
				case AUTO_MODE://�Զ���������
				// case SELF_CUT_MODE://�Ե���������
					DeleteAllData_hintWind();	//ɾ����������  ��ʾ��
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
							if(num_cou>0)	
								{
								if(num_cou<8)
									{
									if(CheckInputNums()==1)// ���� ��Ч
										{
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
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													 // // ServoSendCou=0;
													 // // DcServoStartRun_exec(TargetSize);
													// // // SelfLockEn_flag=0;
														// // break;
												case MOTOR_AC_SERVO:
												case MOTOR_AC_SERVO_REV:
												case MOTOR_AC_A6_SERVO:
													 ACMotorRunStart(TargetSize);
													// SelfLockEn_flag=0;
														break;		
												}
											Run_flag=1;
											RunStop_flag=0;
											InTargetPosit_flag=0;	//Ŀ��λ��
											OneCutRoutine_flag=0; // �� ���� ѭ����־
											AutoCutStart_flag=0;
											AirOffOK_flag=0;
											PressUp_flag=0;
											PressDown_flag=0;
											PromptNum_dis();
											}
										}
									else  //��Ч
										{
										ClrInput_function();//���� �����
										}
									ClearCalculatorInput(); //��������� ����	
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
											// // case MOTOR_DC_SERVO:
											// // case MOTOR_DC670_SERVO:
												 // // ServoSendCou=0;
												 // // DcServoStartRun_exec(TargetSize);
												// // // SelfLockEn_flag=0;
													// // break;
											case MOTOR_AC_SERVO:
											case MOTOR_AC_SERVO_REV:
											case MOTOR_AC_A6_SERVO:
												 ACMotorRunStart(TargetSize);
													break;		
											}
										Run_flag=1;
										RunStop_flag=0;
										InTargetPosit_flag=0;	//Ŀ��λ��
										OneCutRoutine_flag=0; // �� ���� ѭ����־
										AutoCutStart_flag=0;
										AirOffOK_flag=0;
										PressUp_flag=0;
										PressDown_flag=0;
										PromptNum_dis();
										}
									}
								}
							else
								{
								//ClrInput_function();//���� �����
								//CheckInputNums();
								}
								
							break;
					case SELF_CUT_MODE://�Ե� ��������
					//case TEACH_MODE://ʾ�̻�����
						OneCutRoutine_flag=0; // �� ���� ѭ����־
						AutoRun_start();   //������ ��괦
							break;
					case TEACH_MODE://ʾ�� ģʽ
					// case AUTO_MODE://�Զ�  �������� 20180831
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
											GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//�ߴ������
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
													case INDONSIA:	//ӡ��
															Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													case PORTUGAL:	//������
															Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													case SPANISH: //������
															Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													}
											if(ButtonTouch_mode==TOU_MODE_CALC)   //������
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
										GLCD_SetWindow_Fill( SIZE_WINDOW_X, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//�ߴ������
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
											case INDONSIA:	//ӡ��
													Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
											case PORTUGAL:	//������
													Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
													break;
											case SPANISH: //������
													Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
													break;
											}
										if(ButtonTouch_mode==TOU_MODE_CALC)   //������
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
										TargetSize_temp=TargetSize;
										if(TargetSize!=CurrentSize)  //-------------����
										//if(1)
											{
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
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													// // ServoSendCou=0;
													 // // DcServoStartRun_exec(TargetSize);
													// // // SelfLockEn_flag=0;
														// // break;
												case MOTOR_AC_SERVO:
												case MOTOR_AC_SERVO_REV:
												case MOTOR_AC_A6_SERVO:
													ACMotorRunStart(TargetSize);
														break;		
												}
											Run_flag=1;
											RunStop_flag=0;
											AutoCutStart_flag=0;
											InTargetPosit_flag=0;	//Ŀ��λ��
											OneCutRoutine_flag=0; // �� ���� ѭ����־
											AutoCutStart_flag=0;
											AirOffOK_flag=0;
											PressUp_flag=0;
											PressDown_flag=0;
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
										if(ButtonTouch_mode==0)  //	 �� ���������� ��
											num_cou=8;
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
										if(InputSize!=CurrentSize)
											{
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
												// // case MOTOR_DC_SERVO:
												// // case MOTOR_DC670_SERVO:
													 // // ServoSendCou=0;
													 // // DcServoStartRun_exec(TargetSize);
													// // // SelfLockEn_flag=0;
														// // break;
												case MOTOR_AC_SERVO:
												case MOTOR_AC_SERVO_REV:
												case MOTOR_AC_A6_SERVO:
													 ACMotorRunStart(TargetSize);
													// SelfLockEn_flag=0;
														break;		
												}
											Run_flag=1;
											RunStop_flag=0;
											InTargetPosit_flag=0;	//Ŀ��λ��
											OneCutRoutine_flag=0; // �� ���� ѭ����־
											AutoCutStart_flag=0;
											AirOffOK_flag=0;
											PressUp_flag=0;
											PressDown_flag=0;
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
											// // case MOTOR_DC_SERVO:
											// // case MOTOR_DC670_SERVO:
												 // // ServoSendCou=0;
												 // // DcServoStartRun_exec(TargetSize);
												// // // SelfLockEn_flag=0;
													// // break;
											case MOTOR_AC_SERVO:
											case MOTOR_AC_SERVO_REV:
											case MOTOR_AC_A6_SERVO:
												 ACMotorRunStart(TargetSize);
													break;		
											}
										Run_flag=1;
										RunStop_flag=0;
										InTargetPosit_flag=0;	//Ŀ��λ��
										OneCutRoutine_flag=0; // �� ���� ѭ����־
										AutoCutStart_flag=0;
										AirOffOK_flag=0;
										PressUp_flag=0;
										PressDown_flag=0;
										PromptNum_dis();
										}
									}
								}
							else
								{
								OneCutRoutine_flag=0; // �� ���� ѭ����־
								AutoRun_start();   //������ ��괦
								}
							}
							break;
					case AUTO_MODE://�Զ�  ��������
						if(num_cou>0)
							{
							ClearCalculatorInput(); //��������� ����
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
					if(Board_TestMod==0)  
						{
						if((StartCheck_mode==4)||(StartCheck_mode==5))    //-------------4: ����ok ����---------5: only�����쳣����
							{
							if(PassCodeEn_flag==0)
								{
								CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2, START_PROM_WIDE, START_PROM_HIGH);
								switch(Language)
									{
									case CHN_HAN:
											Printf24("����....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									case ENGLISH:
											Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									case INDONSIA:	//ӡ��		
											Printf24("Menjalankan....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									case PORTUGAL:	//������	
											Printf24("Motor funcionando....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									case SPANISH: //������
											Printf24("Motor en marcha....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									}
								CodeSensorTime_AB=0;
								MoveSpeed=2;
								SetMotorSpeed(MoveSpeed);//�и���
								//////////////
								if(StartCheck_mode==4) //-------------4: ����ok ����
									{
									StartCheck_mode=9;
									MoveBack(); //����>>>>
									}
								else				//---------5: only�����쳣����
									{
									StartCheck_mode=6;
									MoveForward(); //ǰ��<<<<
									}
								}
							else   //���� ����
								{
								if(PassCheckDis_flag==0) //������ʾ ------��ʾ
									{
									PassCheckDis_flag=1;
									GLCD_SetWindow_Fill(PASSCODE_X,PASSCODE_Y ,PASSCODE_X+500,PASSCODE_Y+24, 0xffff,0xffff);
									switch(Language)
										{
										case CHN_HAN:
												Printf24("��Чʹ��ʱ�䵽�����������룡",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;
										case ENGLISH:
												Printf24("Your hour is up,enter passcode",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;
										case INDONSIA:	//ӡ��
												Printf24("Gunakan waktu untuk,Masukkan sandi Anda",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;	
										case PORTUGAL:	//������	
												Printf24("Use o tempo para digitar a senha",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;		
										}
									PassCheck_dis(PASS_HINT_X,PASS_HINT_Y);
									GLCD_SetWindow_Fill(PASSCODE_INPUT_X, PASSCODE_INPUT_Y, PASSCODE_INPUT_X+100, PASSCODE_INPUT_Y+30, 0xfffff, 0xffff);
									}
								}
							}
						}
						break;
				// // case MOTOR_DC_SERVO:
				// // case MOTOR_DC670_SERVO:
					// // if(StartCheck_mode==1)
						// // {
						// // if(Board_TestMod==0)       //-----
							// // {
							// // if(PassCodeEn_flag==0)
								// // {
								// // CurrentSize=OriginalSize;
								// // //if(SearchZero_flag==0)   //δ��0
									// // ServoSetCommd(SERVO_COMMD_R,STAT_30H,CurrentSize);  //����Ѱ��
								// // CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2, START_PROM_WIDE, START_PROM_HIGH);
								// // switch(Language)
									// // {
									// // case CHN_HAN:
											// // Printf24("����....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												// // break;
									// // case ENGLISH:
											// // Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												// // break;
									// // case INDONSIA:	//ӡ��		
											// // Printf24("Menjalankan....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												// // break;
									// // case PORTUGAL:	//������	
											// // Printf24("Motor funcionando....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												// // break;
									// // }
								// // StartCheck_mode++;
								// // }
							// // else   //���� ����
								// // {
								// // if(PassCheckDis_flag==0) //������ʾ ------��ʾ
									// // {
									// // PassCheckDis_flag=1;
									// // GLCD_SetWindow_Fill(PASSCODE_X,PASSCODE_Y ,PASSCODE_X+500,PASSCODE_Y+24, 0xffff,0xffff);
									// // switch(Language)
										// // {
										// // case CHN_HAN:
												// // Printf24("��Чʹ��ʱ�䵽�����������룡",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													// // break;
										// // case ENGLISH:
												// // Printf24("Your hour is up,enter passcode",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													// // break;
										// // case INDONSIA:	//ӡ��
												// // Printf24("Gunakan waktu untuk,Masukkan sandi Anda",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													// // break;	
										// // case PORTUGAL:	//������	
												// // Printf24("Use o tempo para digitar a senha",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													// // break;	
										// // }
									// // PassCheck_dis(PASS_HINT_X,PASS_HINT_Y);
									// // GLCD_SetWindow_Fill(PASSCODE_INPUT_X, PASSCODE_INPUT_Y, PASSCODE_INPUT_X+100, PASSCODE_INPUT_Y+30, 0xfffff, 0xffff);
									// // }
								// // }
							// // }
						// // }
						// // break;
				case MOTOR_AC_SERVO:
				case MOTOR_AC_SERVO_REV:
				case MOTOR_AC_A6_SERVO:
					if(Board_TestMod==0)  
						{     
						if((StartCheck_mode==4)||(StartCheck_mode==5))    //-------------4: ����ok ����---------5: only�����쳣����
							{
							if(PassCodeEn_flag==0)
								{
								CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2, START_PROM_WIDE, START_PROM_HIGH);
								switch(Language)
									{
									case CHN_HAN:
											Printf24("����....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									case ENGLISH:
											Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									case INDONSIA:	//ӡ��		
											Printf24("Menjalankan....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									case PORTUGAL:	//������	
											Printf24("Motor funcionando....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
												break;
									}
								//////////////
								if(MotorType<MOTOR_AC_A6_SERVO)
									{
									if(StartCheck_mode==4) //-------------4: ����ok ����
										{
										StartCheck_mode=9;
										ACServoMoveBack_MID_SPD();  //�����ŷ�  ���ٺ���>>>>
										}
									else				//---------5: only�����쳣����
										{
										StartCheck_mode=6;
										ACServoMoveFwd_MID_SPD();  //�����ŷ�  ����ǰ��<<<<
										}
									}
								else
									{
									StartCheck_mode	=13;//ֱ�ӽ��빤������---------20171123
									}
								}
							else   //���� ����
								{
								if(PassCheckDis_flag==0) //������ʾ ------��ʾ
									{
									PassCheckDis_flag=1;
									GLCD_SetWindow_Fill(PASSCODE_X,PASSCODE_Y ,PASSCODE_X+500,PASSCODE_Y+24, 0xffff,0xffff);
									switch(Language)
										{
										case CHN_HAN:
												Printf24("��Чʹ��ʱ�䵽�����������룡",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;
										case ENGLISH:
												Printf24("Your hour is up,enter passcode",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;
										case INDONSIA:	//ӡ��
												Printf24("Gunakan waktu untuk,Masukkan sandi Anda",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;	
										case PORTUGAL:	//������	
												Printf24("Use o tempo para digitar a senha",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
													break;	
										}
									PassCheck_dis(PASS_HINT_X,PASS_HINT_Y);
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
					// // case PROG_MODE://��̻�����
					case TEACH_MODE://ʾ�̻�����
					case AUTO_MODE://�Զ���������
					case SELF_CUT_MODE://�Ե���������
					// // case PROG_FLAG_MODE:	//��� ģʽ.........
						if(Sign_flag==0)
							{
							if(num_cou>0)
							  {
							  if(CheckInputNums()==1)// ���� ��Ч
								 {
								 RenewModifyDate();	//����ʱ����Ϣ-.-.-.-.-.-.-.-.-.-.-.-.-.-
								 //----��������----------------
								 if(Knife_order>OnePro_head.pro_knifeSUM)//���²��� �ܵ���
									{
									OnePro_head.pro_knifeSUM=Knife_order;
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
										OneKnife_data.k_flag&=0xf0;//��� �� ��־
										Flg_chg=1;
										flag_now=OneKnife_data.k_flag;	//��ǰ��� �ݴ�
										}
									}
								 SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//����һ������
								 if(Knife_order<OnePro_head.pro_knifeSUM)// �������һ��
									{
									GetOneKnife_datas(Pro_data.pro_num, Knife_order+1, pKnife_data);// ��һ�� ����
									 if((OneKnife_data.k_flag&0xf)==KNIFE_FLAG) //�� ��־
										{
										if(OneKnife_data.size>InputSize)
											{
											OneKnife_data.k_flag&=0xf0;	//��� �� ��־
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
								 if(Knife_order<MAX_Knife)            //�������
									{
									// if((WorkMode==PROG_MODE)||(WorkMode==TEACH_MODE))
										// {
										Knife_order++;
										StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//�������
										if(cursor_row<(PageKf_Size-1))
											{
											CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
											OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //һ������ ������ʾ
											cursor_row++;
											CursorKnife_dis(cursor_row, 1);//��ɫ���������ʾ
											OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //һ������ ������ʾ
												switch(Flg_chg)
													{
													case 1:
														AllFlagPic_dis(cursor_row-1,flag_now); // ���ͼƬ ��ʾ
														break;
													case 2:
														AllFlagPic_dis(cursor_row,OneKnife_data.k_flag); //��괦 ���ͼƬ ��ʾ
														break;
													case 3:
														AllFlagPic_dis(cursor_row-1,flag_now); // ���ͼƬ ��ʾ
														AllFlagPic_dis(cursor_row,OneKnife_data.k_flag); //��괦 ���ͼƬ ��ʾ
														break;
													}
											}
										else   //ҳ��
											{
											Size_1page_dis(Knife_order-(PageKf_Size-1),0);//һҳ�ߴ���ʾ
											}
										// }
									// else
										// {
										// StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//�������
										// KnifeSize_dis(cursor_row,InputSize,RED_COLOR);//�ߴ�
										// if((ButtonTouch_mode==0)||(ButtonTouch_mode==TOU_MODE_F4)) //----�� ����������-���±��
											// {
											// switch(Flg_chg)
												// {
												// case 1:
													// AllFlagPic_dis(cursor_row,flag_now); // ���ͼƬ ��ʾ
													// break;
												// case 2:
													// AllFlagPic_dis(cursor_row+1,OneKnife_data.k_flag); //��괦 ���ͼƬ ��ʾ
													// break;
												// case 3:
													// AllFlagPic_dis(cursor_row,flag_now); // ���ͼƬ ��ʾ
													// AllFlagPic_dis(cursor_row+1,OneKnife_data.k_flag); //��괦 ���ͼƬ ��ʾ
													// break;
												// }
											// }
										// }
									}
								else
									{
									OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //һ������ ������ʾ
										if(Flg_chg==1)
											{
											AllFlagPic_dis(cursor_row,flag_now); //��괦  ���ͼƬ ��ʾ
											}
									}
								 }
								// ClrInput_function();//���� �����
								ClearCalculatorInput(); //��������� ����
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
					case AUTO_LABEL_MODE:		//��ǩ ģʽ**********************************
						if(num_cou>0)
						   {
						   LabelEnter_exec();//��ǩ ���� �����趨ȷ��
						   }  
						else
						   {
						   if((Total_size*Label_size*Waste_size)!=0)//�趨��Ч
								{
									WorkMode=AUTO_MODE;         //------------------�˳����ص��� ���� 
									CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
									//ClrSizeTable_dis();//������ �б�հ�
									SubModeIcon_dis(WorkMode);   //ģʽname
									Label_function();
									PorgSet_sel=0;
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
									WorkMode=TEACH_MODE;         //------------------�˳����ص�ʾ���� ���� 
									PaperCutEnb_signal=1;
									CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
									SubModeIcon_dis(WorkMode);   //ʾ��
									Label_function();
									PorgSet_sel=0;
								}
							} 
						   break;		   
					case AUTO_DIVIDE_MODE:	//�ȷ�ģʽ***************************************	
						if(num_cou>0)
						   {
						   DivideEnter_exec();//�ȷ� �����趨ȷ��
						   }
						else
						   {
						   if((Total_size*Divide_num)!=0)//�趨�ȷ���Ч
								{
									WorkMode=AUTO_MODE;           //------------------�˳����ص��� ����
									CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
									SubModeIcon_dis(WorkMode);   //���ģʽname
									Divide_function();//
									PorgSet_sel=0;
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
									WorkMode=TEACH_MODE;           //------------------�˳����ص�ʾ���� ����
									PaperCutEnb_signal=1;
									CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
									SubModeIcon_dis(WorkMode);   //ʾ��
									Divide_function();//
									PorgSet_sel=0;
								}
						   }
						   break;		   
					case READ_PRO_MODE:	//����ѡ��*****************************	   
						if(num_cou>0)
							{
							  ProEnter_exec();//����ѡ�� ����ȷ��
							}
						else
							{
							 if((prog_order>0)&&(prog_order<=MAX_PROG))// ��Ч  ����һ�����򣬲���ʾ--------------------
								{
									cursor_pro=0;  
									//----------���ر�̻���
									WorkMode=AUTO_MODE; 
									ExportOnePro_dis(prog_order);  //����һ�� ���� 
									//PaperCutEnb_signal=1;
								}
							}	
							break;
					
					case READ_PRO_MESS_MODE: //������Ϣģʽ
					// // case TEACH_PRO_MESS_MODE: //������Ϣģʽ
						if(EnterInput_exec(cursor_pro, prog_order)==1)		//���� ȷ��	
							{
							SubModeIcon_dis(WorkMode);   //����ѡ��ģʽ
							if(Pro_data.pro_num==ProNumGroup[prog_order])	//���µ�ǰ������
								{
								GetPro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head); //��ȡǰ���� ͷ��Ϣ
								OneProNum_dis(Pro_data.pro_num, OnePro_head);// �����
								}
							}
							break;
					case AUTO_PLUS_MODE:  //F5++
						if(num_cou>0)
							{
							if(Knife_order<=OnePro_head.pro_knifeSUM)
							   {
							   if(CheckInputNums()==1)
									{
									F5_AutoAdd_exec(InputSize);  
									ClearCalculatorInput(); //��������� ����
									WorkMode=AUTO_MODE;
									PaperCutEnb_signal=1;
									PressCircle_mode=0;
									F5_plus_dis(0);	
									}	
							   }
							}
							break;
					case AUTO_MINUS_MODE:// F6--
						if(num_cou>0)
							{
							if(Knife_order<=OnePro_head.pro_knifeSUM)
							   {
							   if(CheckInputNums()==1)
									{
									F6_AutoSub_exec(InputSize);  //F6--  �������� �Լ�
									ClearCalculatorInput(); //��������� ����
									WorkMode=AUTO_MODE;//����
									PaperCutEnb_signal=1;
									PressCircle_mode=0;
									F6_minus_dis(0);
									}
							   }
							}
							break;
					case TEACH_PLUS_MODE:  //F5++
						if(num_cou>0)
							{
							if(Knife_order<=OnePro_head.pro_knifeSUM)
							   {
							   if(CheckInputNums()==1)
									{
									F5_AutoAdd_exec(InputSize);  
									ClearCalculatorInput(); //��������� ����
									WorkMode=TEACH_MODE;
									PaperCutEnb_signal=1;
									PressCircle_mode=0;
									F5_plus_dis(0);	
									}	
							   }
							}
							break;
					case TEACH_MINUS_MODE:// F6--
						if(num_cou>0)
							{
							if(Knife_order<=OnePro_head.pro_knifeSUM)
							   {
							   if(CheckInputNums()==1)
									{
									F6_AutoSub_exec(InputSize);  //F6--  �������� �Լ�
									ClearCalculatorInput(); //��������� ����
									WorkMode=TEACH_MODE;//����
									PaperCutEnb_signal=1;
									PressCircle_mode=0;
									F6_minus_dis(0);
									}
							   }
							}
							break;	
					// // case AUTO_RULER_MODE://�Զ� ��׼
					// // case SELF_RULER_MODE://�Ե� ��׼
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
									// // case MOTOR_DC_SERVO:
									// // case MOTOR_DC670_SERVO:
										// // DcServoGoTarget_flag=0;
										
										// // OriginalSize=OriginalSize+InputSize-CurrentSize;
										// // CurrentSize=InputSize;
										// // ServoSetCommd(SERVO_COMMD_P,STAT_30H,CurrentSize);
											// // break;
									case MOTOR_AC_SERVO:	
									case MOTOR_AC_SERVO_REV:	
										OriginalSize=OriginalSize+InputSize-CurrentSize;
										CurrentSize=InputSize;
											break;
									case MOTOR_AC_A6_SERVO:	
										StartInitSize=StartInitSize+InputSize-CurrentSize;
										OriginalSize=InputSize;
										SaveA6OriginalBenchMark();//A6��׼ ����
											break;
									}		
								
								//if(InputSize!=TargetSize_temp)
								//	{
									SaveOriginalSize();  //����ԭ��ߴ�
								//	}
								
								//-----------------�Զ����� ��ģʽ	
								CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
								// // if(WorkMode==AUTO_RULER_MODE)   //�Զ���
									// // {
									// // WorkMode=AUTO_MODE;//����    �Զ� ��ģʽ
									// // PaperCutEnb_signal=1;
									// // PressCircle_mode=0;
									// // }
								// // else
									if(WorkMode==MANUAL_RULER_MODE)  //�ֶ���
									{
									WorkMode=MANUAL_MODE;//����    �ֶ� ��ģʽ
									}
								// // else if(WorkMode==SELF_RULER_MODE)   //�Ե���	
									// // {
									// // WorkMode=SELF_CUT_MODE;//����    �Ե� ��ģʽ
									// // PaperCutEnb_signal=1;
									// // }
								SubModeIcon_dis(WorkMode); //��ģʽicon
								PromptNum_dis();//���뷶Χ
								PromptDis_flag=1;
								}
							ClearCalculatorInput(); //��������� ����  ClrInput_function();//���� �����
							}
						else
							{						 
							}
							 break;
					// // case AUTO_TOOLS_MODE://�Զ�  ��������
					// // case SELF_TOOLS_MODE://�Ե�  ��������
					case MANUAL_TOOLS_MODE:// �ֶ� ����ģʽ
						if(num_cou>0)
							{
							if((CheckInputNums()==1))
								{
								if(PramSel_Page<1)	//page 1
									{
									if(Para_sel<9)
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
													ParameterPage1_dis(Para_sel++, 0);
													ParameterPage1_dis(Para_sel, 1);
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
													case INDONSIA:	//ӡ��
														Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
																break;
													case PORTUGAL:	//������
															Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													case SPANISH: //������
															Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													}
												if(ButtonTouch_mode==TOU_MODE_CALC)   //������
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
													ParameterPage1_dis(Para_sel++, 0);
													ParameterPage1_dis(Para_sel, 1);
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
													case INDONSIA:	//ӡ��
														Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													case PORTUGAL:	//������
															Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;												
													case SPANISH: //������
															Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;

													}
												if(ButtonTouch_mode==TOU_MODE_CALC)   //������
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
													ParameterPage1_dis(Para_sel++, 0);
													ParameterPage1_dis(Para_sel, 1);
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
													case INDONSIA:	//ӡ��
														Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													case PORTUGAL:	//������
															Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;											
													case SPANISH: //������
															Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													}
												if(ButtonTouch_mode==TOU_MODE_CALC)   //������
													{
													ClearCalculatorInput(); //��������� ����
													num_cou=0;
													}	
												}
												break;
										case 5: //��ǰ��
											if(MotorType<MOTOR_AC_SERVO)  //*************��Ƶ
												{
												if((input_temp>=1)&&(input_temp<=100))
													{
													Aheader=input_temp;
													SaveAheader();
													if(Para_sel<6)
														{
														ParameterPage1_dis(Para_sel++, 0);
														ParameterPage1_dis(Para_sel, 1);
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
														case INDONSIA:	//ӡ��
															Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
																break;
														case PORTUGAL:	//������
																Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
																break;											
														case SPANISH: //������
																Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
																break;
														}
													if(ButtonTouch_mode==TOU_MODE_CALC)   //������
														{
														ClearCalculatorInput(); //��������� ����
														num_cou=0;
														}	
													}
												}
												break;	
										case 6:  //�Զ���ֽ  ����
											if(input_temp<=AUTO_PUSH_DISTAN)
												{
												AutoPushDistance=input_temp;
												SavePushDistance();
												ParameterPage1_dis(Para_sel, 1);
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
													case INDONSIA:	//ӡ��
														Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													case PORTUGAL:	//������
															Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;											
													case SPANISH: //������
															Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													}
												if(ButtonTouch_mode==TOU_MODE_CALC)   //������
													{
													ClearCalculatorInput(); //��������� ����
													num_cou=0;
													}	
												}	
												break;
										case 8:	//������ ����
											if(input_temp<1000)
												{
												if(input_temp<100)
													AirOffDistance=0;
												else
													AirOffDistance=input_temp;
												SaveAirOffDistance();	//������ ����
												if(ButtonTouch_mode==0)  //
													ParameterPage1_dis(Para_sel, 1);
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
													case INDONSIA:	//ӡ��
														Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
																break;
													case PORTUGAL:	//������
															Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;											
													case SPANISH: //������
															Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													}
												if(ButtonTouch_mode==TOU_MODE_CALC)   //������
													{
													ClearCalculatorInput(); //��������� ����
													num_cou=0;
													}	
												}	
												break;	
										case 9:		//������� �ٶ�
											// // if((MotorType==MOTOR_DC_SERVO)||(MotorType==MOTOR_DC670_SERVO))   //------------------ֱ��  �ŷ�
												// // {
												// // if((input_temp<=20)&&(input_temp>=13))
													// // {
													// // ServoSpeed_order=input_temp;
													// // SaveMovSpeed();
													// // ServoSetCommd(SERVO_COMMD_S,STAT_30H,SERVO_SPEED[ServoSpeed_order]);  //�趨�ŷ������
													// // if(ButtonTouch_mode==TOU_MODE_CALC)   //������
														// // {
														// // CalcuInClear_exec();     //��� ������
														// // }	
													// // ParameterPage1_dis(Para_sel, 1);
													// // }
												// // else
													// // {
													// // PromptDis_flag=0;
													// // GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
													// // switch(Language)
														// // {
														// // case CHN_HAN:
															// // Printf24("�������ݳ�������!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
																// // break;
														// // case ENGLISH:
															// // Printf24("Data exceeds limit!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
																// // break;
														// // case INDONSIA:	//ӡ��
															// // Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
																// // break;
														// // case PORTUGAL:	//������
															// // Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															// // break;											
														// // case SPANISH: //������
															// // Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															// // break;
														// // }
													// // if(ButtonTouch_mode==TOU_MODE_CALC)   //������
														// // {
														// // ClearCalculatorInput(); //��������� ����
														// // num_cou=0;
														// // }	
													// // }	
												// // }else 
											
											if(MotorType>=MOTOR_AC_SERVO)  //*************���� �ŷ�
												{
												if(input_temp<=32)
													{
													AC_MotorSPD=input_temp;
													SaveACMotorSpeed();   //�����ŷ� �ٶ�
													GetAC_MotorSpeed();  //�����ŷ�  �ٶ��ж�
													if(ButtonTouch_mode==TOU_MODE_CALC)   //������
														{
														CalcuInClear_exec();     //��� ������
														}	
													ParameterPage1_dis(Para_sel, 1);
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
														case INDONSIA:	//ӡ��
															Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
																break;
														case PORTUGAL:	//������
																Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
																break;											
														case SPANISH: //������
																Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
																break;
														}
													if(ButtonTouch_mode==TOU_MODE_CALC)   //������
														{
														ClearCalculatorInput(); //��������� ����
														num_cou=0;
														}	
													}
												}
											
												break;
												/****
										case 10:		//�㶯 �ٶ�
											if((input_temp<=20)&&(input_temp>=10))
												{
												JogSpeed_order=input_temp;
												SaveJogSpeed();
												//ServoSetCommd(SERVO_COMMD_S,STAT_30H,SERVO_SPEED[ServoSpeed_order]);  //�趨�ŷ������
												if(ButtonTouch_mode==TOU_MODE_CALC)   //������
													{
													CalcuInClear_exec();     //��� ������
													}	
												ParameterPage1_dis(Para_sel, 1);
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
													case INDONSIA:	//ӡ��
														Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													case PORTUGAL:	//������
														Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;											
													case SPANISH: //������
														Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
															break;
													}
												if(ButtonTouch_mode==TOU_MODE_CALC)   //������
													{
													ClearCalculatorInput(); //��������� ����
													num_cou=0;
													}	
												}	
												break;		***/
										}
									}
								else	//page 2
									{
									if(Para2_sel<1)
										{
										if(Unit==UNIT_MM)
											{
											input_temp=InputSize/100*100;
											}
										else
											{
											input_temp=InputSize*2.54;
											}
										}
									else
										{
										
										}
									switch(Para2_sel)
										{
										case 0:		// ��������
											if((input_temp<=MAX_STEP_SIZE)&&(input_temp>=0))
												{
												Step_Size=input_temp;
												SaveStepDistance(); // ��������
												ParameterPage2_dis(Para2_sel++, 0);
												ParameterPage2_dis(Para2_sel, 1);
												}
												break;
										case 1://����ڸ�ֵ
											if(MotorType<MOTOR_AC_SERVO)  //*************��Ƶ
												{
												if(Unit==UNIT_MM)
													{
													if((InputSize>=30)&&(InputSize<=100))	//	20171017����
														{
														VirtualTargetSizeGap=InputSize;
														SaveVirtualTargetSizeGap();
														ParameterPage2_dis(Para2_sel, 1);
														}
													}
												}
												break;
										}
									}
								}
							else
								num_cou=0;
							if(ButtonTouch_mode==0)  //	 �� ���������� ��	
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
												case INDONSIA:	//ӡ��
													Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case PORTUGAL:	//������
														Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;											
												case SPANISH: //������
														Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												}
											if(ButtonTouch_mode==TOU_MODE_CALC)   //������
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
												case INDONSIA:	//ӡ��
													Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case PORTUGAL:	//������
														Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;											
												case SPANISH: //������
														Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												}
											if(ButtonTouch_mode==TOU_MODE_CALC)   //������
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
												case INDONSIA:	//ӡ��
													Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case PORTUGAL:	//������
														Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;											
												case SPANISH: //������
														Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												}
											if(ButtonTouch_mode==TOU_MODE_CALC)   //������
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
												case INDONSIA:	//ӡ��
													Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case PORTUGAL:	//������
														Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;											
												case SPANISH: //������
														Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												}
											if(ButtonTouch_mode==TOU_MODE_CALC)   //������
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
												case INDONSIA:	//ӡ��
													Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case PORTUGAL:	//������
														Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;											
												case SPANISH: //������
														Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												}
											if(ButtonTouch_mode==TOU_MODE_CALC)   //������
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
												case INDONSIA:	//ӡ��
													Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case PORTUGAL:	//������
														Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;											
												case SPANISH: //������
														Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												}
											if(ButtonTouch_mode==TOU_MODE_CALC)   //������
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
												case INDONSIA:	//ӡ��
													Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case PORTUGAL:	//������
														Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;											
												case SPANISH: //������
														Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												}
											if(ButtonTouch_mode==TOU_MODE_CALC)   //������
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
											if(ButtonTouch_mode==TOU_MODE_CALC)   //������
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
												case INDONSIA:	//ӡ��
													Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												case PORTUGAL:	//������
														Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;											
												case SPANISH: //������
														Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
														break;
												}
											if(ButtonTouch_mode==TOU_MODE_CALC)   //������
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
							if(ButtonTouch_mode==0)  //	 �� ���������� ��	
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
							ClearCalculatorInput(); //��������� ����	ClrInput_function();//���� ����� 
							}
							break;
					case MANUAL_PULSE_MODE://�ֶ� ���嵱��  �趨����
						 if(num_cou>0)
							{
							if(CheckInputNums()==1)
								{
								if(InputSize<12)
									{
									SelPulseDegree_dis(Para_sel, 0); //�����趨
									Para_sel=InputSize;
									SelPulseDegree_dis(Para_sel,1);
									}
								}
							else
								num_cou=0;
							ClearCalculatorInput(); //��������� ���� ClrInput_function();//���� ����� 
							}
						 else
							{
							if(ButtonTouch_mode==0)  //	��  ���� ��
								{
								Pulse_degree=Para_sel;
								Save_degree();
								WorkMode=MANUAL_MODE;//����    ---------�ֶ� ��ģʽ
								Para_sel=0;
								CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y, M_PAGE_WIDE, M_PAGE_HIGH);
								SubModeIcon_dis(WorkMode);   //�ֶ�ģʽname
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
							ClearCalculatorInput(); //��������� ����  ClrInput_function();//���� �����
							}
							break;
					case AUTO_TO_SELF_MODE:   //�Զ�-->�Ե����� ģʽ
						
						if(LastAutoKnife_order<2)    //--------�״�  ����  ����ʾ
							{
							WorkMode=SELF_CUT_MODE;  //����   ----------�Ե��� ģʽ
							CurrentArea_recover2(SELF_PROMP_X,SELF_PROMP_Y,SELF_PROMP_WIDE,SELF_PROMP_HIGH);
							AutoCutModePage_dis(); //�Ե�ģʽ ���ֻ�����ʾ
							//------------���ص�һ��
							// // ClrInput_function();//���� ����� 
							CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
							cursor_row=0;
							CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
							Knife_order=1;//
							Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
							if(Knife_order<=OnePro_head.pro_knifeSUM)
								StepOrder_dis(Knife_order);//������� 
							AutoCutDisable_flag=0;
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
								// // if(ButtonTouch_mode==TOU_MODE_AUTOCUT_IN) //�Զ�-->�Ե�����  	��ʾ
									// // ButtonTouch_mode=0;
								WorkMode=SELF_CUT_MODE;  //����   ----------�Ե��� ģʽ
								CurrentArea_recover2(SELF_PROMP_X,SELF_PROMP_Y,SELF_PROMP_WIDE,SELF_PROMP_HIGH);
								AutoCutModePage_dis(); //�Ե�ģʽ ���ֻ�����ʾ
								//------------����֮ǰ��
								Knife_order=LastAutoKnife_order;//
								// // ClrInput_function();//���� ����� 
								CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
								cursor_row=0;
								CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
								
								Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
								if(Knife_order<=OnePro_head.pro_knifeSUM)
									StepOrder_dis(Knife_order);//������� 
								LastAutoKnife_order=1;
							AutoCutDisable_flag=0;
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
								case INDONSIA:	//ӡ��
										Printf24("Mode Manual,tekan tombol Run",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
								case PORTUGAL:	//������
										Printf24("Pressione a tecla Run",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
								}
							}
						
							break;
							//---------------ȫɾ ����
					case READ_DEL_ALL_PRO_MODE://ɾ������pro
					// // case TEACH_DEL_ALL_PRO_MODE://ɾ������pro
						//------1
						DeleteAllExitWind();	//�˳�ȫɾ ��ʾ��
						//------2
						DeleteAllProg();		//F5 ɾ�����г���
							break;
					case AUTO_DEL_ALL_SIZE_MODE://	ɾ�����гߴ�
					case TEACH_DEL_ALL_SIZE_MODE://	ɾ�����гߴ�
						//------1
						DeleteAllExitWind();	//�˳�ȫɾ ��ʾ��
						//------2
						Knife_order=1;
						ClrBuf_datas(Pro_data.pro_num, Knife_order, OnePro_head.pro_knifeSUM );//����
						SaveBuf_datas(Pro_data.pro_num, Knife_order, OnePro_head.pro_knifeSUM );//����
						CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
						cursor_row=0;
						CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
						Size_1page_dis(Knife_order,cursor_row);//��ʾһҳ

						OnePro_head.pro_knifeSUM=1;
						SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);//���� ����
						StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//�������
							break;
					}
			ClearCalculatorInput(); //��������� ����20180925
			 }
		  else
			 {
									
			 }
		  }
		else
		  {
		  if(Board_TestMod==TEST_NO)
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
					 else if((StartCheck_mode==4)||(StartCheck_mode==5))
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
											GLCD_SetWindow_Fill(PASSCODE_X,PASSCODE_Y ,PASSCODE_X+500,PASSCODE_Y+24, 0xffff,0xffff);
											switch(Language)
												{
												case CHN_HAN:
															Printf24("����������ȷ����ӭ����ʹ�ã�  ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												case ENGLISH:
															Printf24("Password is correct,Welcome to use!    ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												case INDONSIA:	//ӡ��
															Printf24("Password benar! selamat datang!    ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												case PORTUGAL:	//������
															Printf24("A senha est�� correta! bem-vindo    ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												}
											//////////////////////////////	
											CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2, START_PROM_WIDE, START_PROM_HIGH);
											switch(Language)
												{
												case CHN_HAN:
														Printf24("����....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												case ENGLISH:
														Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												case INDONSIA:	//ӡ��		
														Printf24("Menjalankan....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												case PORTUGAL:	//������	
														Printf24("Motor funcionando....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												}
											MoveSpeed=2;
											SetMotorSpeed(MoveSpeed);//�и���
											if(StartCheck_mode==4)//-------------4: ����ok ����
												{
												MoveBack(); 	//����>>>>
												StartCheck_mode=9;//++;
												}
											else				//---------5: only�����쳣����
												{
												StartCheck_mode=6;
												MoveForward(); //ǰ��<<<<
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
				// // case MOTOR_DC_SERVO:
				// // case MOTOR_DC670_SERVO:
					// // if(StartCheck_mode==1)
						 // // {
						 // // if(PassCheckDis_flag==1) //���� ������
							 // // {
							 // // if(num_cou>0)
								// // {
								// // if(CheckInputNums()==1)
									// // {
									// // if(StartPassInput_flag==0)
										// // {
										// // StartPassInput_flag=1;
										// // if(InputSize==PassCode)//������ȷ   
											// // {
											// // PassCodeEn_flag=0;
											// // //PassCheckDis_flag=0;
											
										// // //-----------ʱ�����
											// // if(FirstDayValid_flag==1) //�״� ʱ������ ��Ч
												// // {
												// // FirstDayValid_flag=0;
												// // SaveFirstDays_flag(); //��� �״���Ч
												// // if(SecondDayValid_flag==1) //�ڶ��� ��ʱ��ʼ
													// // {
													// // Start_days.year=Year;
													// // Start_days.month=Month;
													// // Start_days.day=Dom;
													// // SaveWorkDays();//��ʼ ʱ�䱣��
													// // }
												// // }
											// // else if(SecondDayValid_flag==1)    //�ڶ��� ��Ч
												// // {
												// // SecondDayValid_flag=0;
												// // SaveSecondDays_flag();
												// // }
											// // //---------���� ����
											// // GLCD_SetWindow_Fill(PASSCODE_X,PASSCODE_Y ,PASSCODE_X+500,PASSCODE_Y+24, 0xffff,0xffff);
											// // switch(Language)
												// // {
												// // case CHN_HAN:
															// // Printf24("����������ȷ����ӭ����ʹ�ã�  ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																// // break;
												// // case ENGLISH:
															// // Printf24("Password is correct,Welcome to use!    ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																// // break;
												// // case INDONSIA:	//ӡ��
															// // Printf24("Password benar! selamat datang!   ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																// // break;
												// // case PORTUGAL:	//������
															// // Printf24("A senha est�� correta! bem-vindo   ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																// // break;
												// // }
												
											
											// // CurrentSize=OriginalSize;
											// // //if(SearchZero_flag==0)   //δ��0
											// // ServoSetCommd(SERVO_COMMD_R,STAT_30H,CurrentSize);  //����Ѱ��
											// // CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2, START_PROM_WIDE, START_PROM_HIGH);
											// // switch(Language)
												// // {
												// // case CHN_HAN:
														// // Printf24("����....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															// // break;
												// // case ENGLISH:
														// // Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															// // break;
												// // case INDONSIA:	//ӡ��		
														// // Printf24("Menjalankan....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															// // break;
												// // case PORTUGAL:	//������	
														// // Printf24("Motor funcionando....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															// // break;
												// // }
											// // StartCheck_mode++;	
											// // }
										// // }
								
									// // }
								 // // for(num_cou=0;num_cou<8;num_cou++)
									// // {
									// // Size_temp[num_cou++]=0;
									// // }
								 // // num_cou=0;	
								// // }
							 // // }
						 // // }
						// // break;
				case MOTOR_AC_SERVO:
				case MOTOR_AC_SERVO_REV:
				case MOTOR_AC_A6_SERVO:
					if(StartCheck_mode==1)  //��ֽ�� ��λ����
						{
						ACMotorGoForward();//ǰ��
						// PusherResetTime=0;
						qianjincn=0;
						 CurrentArea_recover3(PUSH_RESET_PROMPT_X1, PUSH_RESET_PROMPT_Y1, PUSH_RESET_PROMPT_WIDE, PUSH_RESET_PROMPT_HIGH);
						 StartCheck_mode++;
						 PushRstKey_flag=1;
						}
					else if((StartCheck_mode==4)||(StartCheck_mode==5))
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
											GLCD_SetWindow_Fill(PASSCODE_X,PASSCODE_Y ,PASSCODE_X+500,PASSCODE_Y+24, 0xffff,0xffff);
											switch(Language)
												{
												case CHN_HAN:
															Printf24("����������ȷ����ӭ����ʹ�ã�  ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												case ENGLISH:
															Printf24("Password is correct,Welcome to use!    ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												case INDONSIA:	//ӡ��
															Printf24("Password benar! selamat datang!    ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												case PORTUGAL:	//������
															Printf24("A senha est�� correta! bem-vindo    ",PASSCODE_X,PASSCODE_Y,RED_COLOR,1,0xffff);
																break;
												}
												///////////////////////////////////////////
											CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2, START_PROM_WIDE, START_PROM_HIGH);
											switch(Language)
												{
												case CHN_HAN:
														Printf24("����....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												case ENGLISH:
														Printf24("Runing....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												case INDONSIA:	//ӡ��		
														Printf24("Menjalankan....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												case PORTUGAL:	//������	
														Printf24("Motor funcionando....",RUN_DIS_X,RUN_DIS_Y,RED_COLOR,1,0xffff);
															break;
												}
											if(MotorType<MOTOR_AC_A6_SERVO)
												{
												if(StartCheck_mode==4) //-------------4: ����ok ����
													{
													StartCheck_mode=9;
													ACServoMoveBack_MID_SPD();  //�����ŷ�  ���ٺ���>>>>
													}
												else				//---------5: only�����쳣����
													{
													StartCheck_mode=6;
													ACServoMoveFwd_MID_SPD();  //�����ŷ�  ����ǰ��<<<<
													}	
												}
											else
												{
												StartCheck_mode	=13;//ֱ�ӽ��빤������---------20171123
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
				}	
			 }
		  else   //if(Board_TestMod==TEST_SYS_WORD)
			 {
			 EnterSysBoardNum(); // ϵͳ ѡ��ģʽ  ����
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
				
				case TEACH_MODE://ʾ�̻�����
				case TEACH_PLUS_MODE:  //�Ե�F5++
				case TEACH_MINUS_MODE://�Ե� F6--
				case AUTO_MODE://�Զ���������
				case AUTO_PLUS_MODE:  //F5++
				case AUTO_MINUS_MODE:// F6--
				case SELF_CUT_MODE://�Ե���������
				case PROG_FLAG_MODE:	//��� ģʽ
				case TEACH_FLAG_MODE:	//��� ģʽ
						if((Knife_order==OnePro_head.pro_knifeSUM)&&(Knife_order==1))
							{
							pKnife_data=(pInt8U)&OneKnife_data;
							GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);//
							if((OneKnife_data.size>=Size_MIN_num)&&(OneKnife_data.size<=Size_MAX_num))
								CursorDown_inTable();//**** ������� ��ʾ ����
							}
						else
							CursorDown_inTable();//**** ������� ��ʾ ����	
						
						   break;
				case AUTO_LABEL_MODE://��ǩ ��--------------------------
				case TEACH_LABEL_MODE://��ǩ ��--------------------------
					 if(PorgSet_sel<2)
						{
						LabelSel_dis(PorgSet_sel,0);PorgSet_sel++;
						LabelSel_dis(PorgSet_sel,1);
						}
							break;
				case AUTO_DIVIDE_MODE://�ȷ� ��--------------------------
				case TEACH_DIVIDE_MODE://�ȷ� ��--------------------------
					 if(PorgSet_sel<1)
						{
						DivideSel_dis(PorgSet_sel,0);PorgSet_sel++;
						DivideSel_dis(PorgSet_sel,1);
						}
							break;
				case READ_PRO_MODE:    //����ѡ��----------------------
				// // case TEACH_PRO_MODE:    //����ѡ��----------------------
						  if(prog_order>=MAX_PROG)//���ص�һ�� pro
							  {
							  // Pro_num111=1;
							  prog_order=1;
							  CursorPro_dis(cursor_pro,0);//���
							  cursor_pro=0;
							  CursorPro_dis(cursor_pro,1);//
							  Prog_1page_dis(prog_order, 0);//===����---������ʾ
							  OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//һ������ ��ʾ1
							  }
						  else
							  {
							  prog_order++;
							  if(cursor_pro<(PROGS_1PAGE-1))
								 {
								 CursorPro_dis(cursor_pro,0);//���
								 OneProgHeadInfo_dis(cursor_pro ,  prog_order-1, 0);	//һ������ ��ʾ0
								 cursor_pro++;
								 CursorPro_dis(cursor_pro,1);//
								 OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//һ������ ��ʾ1
								 }
							  else// ��һҳ
								 {
								 CursorPro_dis(cursor_pro,0);//���
								 cursor_pro=0;
								 CursorPro_dis(cursor_pro,1);//
								 Prog_1page_dis(prog_order, 0);//===����---������ʾ
								 OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//һ������ ��ʾ
								 }
							  }
						     break;
				case READ_PRO_MESS_MODE:			 
				// // case TEACH_PRO_MESS_MODE:	
						DirKeySelInput_exec(KEY_DOWN);
						
							break;
				// // case AUTO_TOOLS_MODE://  ��������  ����
				// // case SELF_TOOLS_MODE://  ��������  ����
				case MANUAL_TOOLS_MODE:// �ֶ� ����ģʽ
					if(ButtonTouch_mode==0)  //	 �� ���������� ��
						{
						switch(MotorType)
							{
							case MOTOR_FREQ_5_SPD_RST:
							case MOTOR_FREQ_3_SPD:
							case MOTOR_FREQ_3_SPD_RST:
								if(PramSel_Page<1)	//page 1
									{
									if(Para_sel<9)
										{
										ParameterPage1_dis(Para_sel++, 0);
										ParameterPage1_dis(Para_sel, 1);
										}
									else
										{
										PramSel_Page++;
										ParamPage2_dis(); //���� page2
										}
									}
								else	//page 2
									{
									if(Para2_sel<2)
										{
										ParameterPage2_dis(Para2_sel++, 0);
										ParameterPage2_dis(Para2_sel, 1);
										}
									}
									
									break;
							// // case MOTOR_DC_SERVO:
							// // case MOTOR_DC670_SERVO:
								// // if(PramSel_Page<1)	//page 1
									// // {
									// // if(Para_sel<10)
										// // {
										// // ParameterPage1_dis(Para_sel++, 0);
										// // ParameterPage1_dis(Para_sel, 1);
										// // }
									// // else
										// // {
										// // PramSel_Page++;
										// // ParamPage2_dis(); //���� page2
										// // }
									// // }
								// // else	//page 2
									// // {
									// // if(Para2_sel<1)
										// // {
										// // ParameterPage2_dis(Para2_sel++, 0);
										// // ParameterPage2_dis(Para2_sel, 1);
										// // }
									// // }
									// // break;
							case MOTOR_AC_SERVO:
							case MOTOR_AC_SERVO_REV:
							case MOTOR_AC_A6_SERVO:
								if(PramSel_Page<1)	//page 1
									{
									if(Para_sel<10)
										{
										ParameterPage1_dis(Para_sel++, 0);
										ParameterPage1_dis(Para_sel, 1);
										}
									else
										{
										PramSel_Page++;
										ParamPage2_dis(); //���� page2
										}
									}
								else	//page 2
									{
									if(Para2_sel<2)
										{
										ParameterPage2_dis(Para2_sel++, 0);
										ParameterPage2_dis(Para2_sel, 1);
										}
									}
								
									break;
							}
						}
					else if(ButtonTouch_mode==TOU_MODE_CALC)
						{
						if(PramSel_Page<1)	//page 1
							{
							if(Para_sel<6)
								{
								ParameterPage1_dis(Para_sel++, 0);
								ParameterPage1_dis(Para_sel, 1);
								}	
							}
						else	//page 2
							{
							if(Para2_sel<2)
								{
								ParameterPage2_dis(Para2_sel++, 0);
								ParameterPage2_dis(Para2_sel, 1);
								}
							}
						}
							break;
				case MANUAL_SERVO_C_MODE:// �ֶ�ֱ���ŷ� C ���� 
					 if(ButtonTouch_mode==0)  //	 �� ���������� ��
						{
						if(Para_sel<7)
							{
							ServoParameter_dis(Para_sel++, 0);
							ServoParameter_dis(Para_sel, 1);
							}
						}
					else if(ButtonTouch_mode==TOU_MODE_CALC)
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
				case MANUAL_MODE: //�ֶ�	+++++++++����
						if(InTargetPosit_flag==1)  //	Ŀ��λ��
							{
							if(Unit==UNIT_MM)//mm
								{
								current_temp=TargetSize_temp;
								}
							else // inch
								{
								current_temp=TargetSize_inch;
								}
							}
						else 
							{
							if(Unit==UNIT_MM)//mm
								{
								current_temp=CurrentSize;
								}
							else // inch
								{
								current_temp=CurrentSize*100/254;
								}
							}
						step_temp = Step_Size;
						if(Unit!=UNIT_MM)//
							step_temp = Step_Size*100/254;
						if((current_temp>step_temp)&&(current_temp-step_temp)>Size_MIN_num)	//���� ��Ч
							{
							if(Unit==UNIT_MM)//mm
								{
								TargetSize = current_temp-step_temp;
								}
							else	//inch
								{
								TargetSize_inch = current_temp-step_temp;
								TargetSize = TargetSize_inch*2.54;
								}
							if(TargetSize!=CurrentSize)  //-------------����
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
									// // case MOTOR_DC_SERVO:
									// // case MOTOR_DC670_SERVO:
										// // ServoSendCou=0;
										 // // DcServoStartRun_exec(TargetSize);
										// // // SelfLockEn_flag=0;
											// // break;
									case MOTOR_AC_SERVO:
									case MOTOR_AC_SERVO_REV:
									case MOTOR_AC_A6_SERVO:
										ACMotorRunStart(TargetSize);
											break;		
									}
								Run_flag=1;
								RunStop_flag=0;
								AutoCutStart_flag=0;
								InTargetPosit_flag=0;	//Ŀ��λ��
								OneCutRoutine_flag=0; // �� ���� ѭ����־
								AutoCutStart_flag=0;
								AirOffOK_flag=0;
								PressUp_flag=0;
								PressDown_flag=0;
								PromptNum_dis();
								ClearCalculatorInput(); //��������� ����
								}	
							}				
						break;
				}			
			 }
		 
		  } 
		else
		  {
		  if(Board_TestMod==TEST_SYS_TYPE)//���� ����ϵͳѡ��
			{
			if(MotorType<5)
				{
				SpeedLevelSel_dis(MotorType++,0);
				SpeedLevelSel_dis(MotorType,1);
				SaveMachineType(); //����  ��������
		 		}
			}
		  else if(Board_TestMod==TEST_PAGE_LINE)//
			{
			if(PageKf_Size_flag<PAGE_7_LINE)
				{
				PageLine_Set(PageKf_Size_flag++, 0);	//ÿҳ������ʾ
				PageLine_Set(PageKf_Size_flag, 1);	//ÿҳ������ʾ
				SavePageKf_Size();
				PageKf_Size_Init();	//ÿҳ ������ʼ��
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
				
				case TEACH_MODE://ʾ�̻�����
				case AUTO_MODE://�Զ���������
				case AUTO_PLUS_MODE:  //F5++
				case AUTO_MINUS_MODE:// F6--
				case SELF_CUT_MODE://�Ե���������
				case TEACH_PLUS_MODE:  //�Ե�F5++
				case TEACH_MINUS_MODE://�Ե� F6--
				case PROG_FLAG_MODE:	//��� ģʽ
				case TEACH_FLAG_MODE:	//��� ģʽ
						if(Knife_order>1)
							{
							Knife_order--;
							if(cursor_row>0)
								{
								CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
								OneKnifeDataSel_dis(Knife_order+1, cursor_row,0);  //һ������ ������ʾ
								cursor_row--;
								CursorKnife_dis(cursor_row, 1);//��ɫ���������ʾ
								OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //һ������ ������ʾ
								}
							else  //ҳü
								{
								Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
								}	
							}
						else     //ָ�� ���һ��
							{
							Knife_order=OnePro_head.pro_knifeSUM;
							if(Knife_order>PageKf_Size)
								{
								Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
								CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
								cursor_row=0;
								CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ  �ڿ�ͷ
								}
							else
								{
								CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
								OneKnifeDataSel_dis(1, cursor_row,0);  //һ������ ������ʾ
								cursor_row=Knife_order-1;
								CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ  �ڿ�ͷ
								OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //һ������ ������ʾ
								}
							}
						if(Knife_order<=OnePro_head.pro_knifeSUM)
							StepOrder_dis(Knife_order);//�������
						switch(WorkMode)
							{
							case AUTO_PLUS_MODE:  //F5++
							case AUTO_MINUS_MODE:// F6--
							case TEACH_PLUS_MODE://�Ե�F5++
							case TEACH_MINUS_MODE://�Ե� F6--
									break;
							default:
								PromptNum_dis();//���뷶Χ
								PromptDis_flag=1;
									break;
							}
						 break;
				case AUTO_LABEL_MODE://��ǩ ��--------------------------
				case TEACH_LABEL_MODE://��ǩ ��--------------------------
					 if(PorgSet_sel>0)
						{
						LabelSel_dis(PorgSet_sel,0);PorgSet_sel--;
						LabelSel_dis(PorgSet_sel,1);
						}
							break;
				case AUTO_DIVIDE_MODE://�ȷ� ��--------------------------
				case TEACH_DIVIDE_MODE://�ȷ� ��--------------------------
					 if(PorgSet_sel>0)
						{
						DivideSel_dis(PorgSet_sel,0);PorgSet_sel--;
						DivideSel_dis(PorgSet_sel,1);
						}
							break;
				case READ_PRO_MODE:    //����ѡ��----------------------
				// // case TEACH_PRO_MODE:    //����ѡ��----------------------
						  if(prog_order<2)//������� pro
							  {
							  prog_order=MAX_PROG;
							  CursorPro_dis(cursor_pro,0);//���
							  cursor_pro=MAX_PROG%PROGS_1PAGE;
							  if(cursor_pro<1)
								 cursor_pro=PROGS_1PAGE;
							  cursor_pro--;
							  CursorPro_dis(cursor_pro,1);//
							  Prog_1page_dis(prog_order-cursor_pro, 0);//===����---������ʾ
							  OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//һ������ ��ʾ1
							  }
						  else
							  {
							  prog_order--;
							  if(cursor_pro>0)//
								 {
								 CursorPro_dis(cursor_pro,0);//���
								 OneProgHeadInfo_dis(cursor_pro ,  prog_order+1, 0);	//һ������ ��ʾ0
								 cursor_pro--;
								 CursorPro_dis(cursor_pro,1);//
								 OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//һ������ ��ʾ1
								 }
							  else//��һҳ
								 {
								 CursorPro_dis(cursor_pro,0);//���
								 cursor_pro=PROGS_1PAGE-1;
								 CursorPro_dis(cursor_pro,1);//
								 Prog_1page_dis(prog_order-(PROGS_1PAGE-1), 0);//===����---������ʾ
								 OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//һ������ ��ʾ1
								 }
							  }
						     break;
				case READ_PRO_MESS_MODE:			 
				// // case TEACH_PRO_MESS_MODE:	
					
						DirKeySelInput_exec(KEY_UP);
							break;
				// // case AUTO_TOOLS_MODE://  ��������  ����
				// // case SELF_TOOLS_MODE://  ��������  ����
				case MANUAL_TOOLS_MODE:// �ֶ� ����ģʽ
					if(PramSel_Page<1)	//page 1
						{
						if(Para_sel>0)
							{
							if(ButtonTouch_mode==0)  //	 �� ���������� ��
								{
								ParameterPage1_dis(Para_sel--, 0);
								ParameterPage1_dis(Para_sel, 1);	
								}
							else if(ButtonTouch_mode==TOU_MODE_CALC)
								{
								if(Para_sel>6)
									Para_sel--;
								else 
									ParameterPage1_dis(Para_sel--, 0);
								if(Para_sel<7)
									ParameterPage1_dis(Para_sel, 1);	
								}
							}
						}
					else	//page 2
						{
						if(Para2_sel>0)
							{
							if(ButtonTouch_mode==0)  //	 �� ���������� ��
								{
								ParameterPage2_dis(Para2_sel--, 0);
								ParameterPage2_dis(Para2_sel, 1);	
								}
							else if(ButtonTouch_mode==TOU_MODE_CALC)
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
							if(ButtonTouch_mode==0)  //	 �� ���������� ��
								{
								PramSel_Page--;	
								ParamPage1_dis(); //���� page1
								}
							}
						}
					
							 break;
				case MANUAL_SERVO_C_MODE:// �ֶ�ֱ���ŷ� C ���� 
					if(Para_sel>0)
						{
						if(ButtonTouch_mode==0)  //	 �� ���������� ��
							{
							ServoParameter_dis(Para_sel--, 0);
							ServoParameter_dis(Para_sel, 1);	
							}
						else if(ButtonTouch_mode==TOU_MODE_CALC)
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
		  if(Board_TestMod==TEST_SYS_TYPE)//���� ����ϵͳѡ��
			{
			if(MotorType>0)
				{
				SpeedLevelSel_dis(MotorType--,0);
				SpeedLevelSel_dis(MotorType,1);
				SaveMachineType(); //����  ��������
		  		}
			}
		  else if(Board_TestMod==TEST_PAGE_LINE)//
			{
			if(PageKf_Size_flag>PAGE_5_LINE)
				{
				PageLine_Set(PageKf_Size_flag--, 0);	//ÿҳ������ʾ
				PageLine_Set(PageKf_Size_flag, 1);	//ÿҳ������ʾ
				SavePageKf_Size();
				PageKf_Size_Init();	//ÿҳ ������ʼ��
				}
			}
		  }
  	     break; 
    case PGUP_KEY_CODE:	//��ҳ   -----------
		if(WorkStart_flag==0)
			{
			if(Board_TestMod==TEST_ICON)
				{
				if(Manual_page>0)        //��һҳ  ����
					{
					Manual_page--;
					Comment_dis_page(Manual_page);
					}
				}
			}
		else
			{
			PageUpExec();	//�Ϸ�ҳ
			}
			break;
	case PGDOWN_KEY_CODE:	//��ҳ   -----------
		if(WorkStart_flag==0)
			{
			if(Board_TestMod==TEST_ICON)
				{
				if(Manual_page<1)        //��һҳ  ����
					{
					Manual_page++;
					Comment_dis_page(Manual_page);
					}
				}
			}
		else
			{
			PageDownExec();	//�·�ҳ
			}
			break;
	case LEFT_KEY_CODE:	// ��
		if(WorkStart_flag==1)
		  {
		  if(Run_flag==0)
			 {
			 switch(WorkMode)
				{
				case READ_PRO_MESS_MODE:			 
				// // case TEACH_PRO_MESS_MODE:	
						DirKeySelInput_exec(KEY_LEFT);
						
						break;
				}
			 }
		  }	 
		
             break; 
	case RIGHT_KEY_CODE:	// ��
		if(WorkStart_flag==1)
		  {
		  if(Run_flag==0)
			 {
			 switch(WorkMode)
				{
				case READ_PRO_MESS_MODE:			 
				// // case TEACH_PRO_MESS_MODE:
						DirKeySelInput_exec(KEY_RIGHT);
						
						break;
				}
			 }
		  }	 	
             break;		 
    case ALL_FLAG_KEY_CODE:       //����趨
		if(WorkStart_flag==1)
		  {
		  if(Run_flag==0)
			 {
			
			 }
		  }	 	
			break;    
     case  ONE_KEY_CODE + YES_KEY_CODE: //F ���ܰ��� +  ����8  **************       
             break;    
    case  ONE_KEY_CODE + OPTION_KEY_CODE: //F ���ܰ��� +  ��-/����  **************
                
           break;       
          
    case ONE_KEY_CODE +  REV_KEY_CODE: //F ���ܰ��� +  ��+/*��  **************
          
          break;
    case ONE_KEY_CODE + ADD_KEY_CODE: //F ���ܰ��� +  ��.��  **************
           
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
		
    }            
	
}

/****
int KeyCheck(void)
{
int i;
int  c;
KEY_COL1_CLR();
KEY_COL2_CLR();
KEY_COL3_CLR();
KEY_COL4_CLR();
KEY_COL5_CLR();
KEY_COL6_CLR();
i=100;
while(i--);
c=(~KEYIO)&KEY_CODE_MASK;
KEY_COL1_SET();
KEY_COL2_SET();
KEY_COL3_SET();
KEY_COL4_SET();
KEY_COL5_SET();
KEY_COL6_SET();
return(c);
}
void KeyReadCode(void)
{
	int i;
int keycodetemp;
KeyCode=0;
KEY_COL1_CLR();
i=500;
while(i--);
keycodetemp=(~KEYIO)&KEY_CODE_MASK;
if(keycodetemp!=0)
	KeyCode=keycodetemp|0x4000000;
KEY_COL1_SET();

KEY_COL2_CLR();
i=500;
while(i--);
keycodetemp=(~KEYIO)&KEY_CODE_MASK;
if(keycodetemp!=0)
	KeyCode+=(keycodetemp|0x8000000);
	//KeyCode=keycodetemp|0x10000000;
KEY_COL2_SET();

KEY_COL3_CLR();
i=500;
while(i--);
keycodetemp=(~KEYIO)&KEY_CODE_MASK;
if(keycodetemp!=0)
	KeyCode+=(keycodetemp|0x10000000);
	//  KeyCode=keycodetemp|0x20000000;
KEY_COL3_SET();

KEY_COL4_CLR();
i=500;
while(i--);
keycodetemp=(~KEYIO)&KEY_CODE_MASK;
if(keycodetemp!=0)
	KeyCode+=(keycodetemp|0x20000000);
//		KeyCode=keycodetemp|0x40000000;
KEY_COL4_SET();

KEY_COL5_CLR();
i=500;
while(i--);
keycodetemp=(~KEYIO)&KEY_CODE_MASK;
if(keycodetemp!=0)
	KeyCode+=(keycodetemp|0x40000000);
//	  KeyCode=keycodetemp|0x80000000;
KEY_COL5_SET();


KEY_COL6_CLR();
i=500;
while(i--);
keycodetemp=(~KEYIO)&KEY_CODE_MASK;
if(keycodetemp!=0)
	KeyCode+=(keycodetemp|0x80000000);
//	  KeyCode=keycodetemp|0x80000000;
KEY_COL6_SET();


}
void Key_Enable(unsigned char enb)
{
}****/
void KeyInit(void)  //���˿ڳ�ʼ��
{
  /*
KEY_COL1_SET();
KEY_COL2_SET();
KEY_COL3_SET();
KEY_COL4_SET();
KEY_COL5_SET();
KEY_COL6_SET();
//KEYIO_DDR&=0xfc1FFFFF;
PINMODE7&=0xffc00ffff;
  */
}






void ClrInput_function(void)//���� �����
{
for(num_cou=0;num_cou<8;num_cou++)
	 {
		Size_temp[num_cou++]=0;
	 }
num_cou=0; //
// CalcTemp_cou=num_cou;
Dot_flag=0;
SubLine_flag=0; //�������-��
// GLCD_SetWindow_Fill( SIZE_WINDOW_X+SIGN_2WIDE, SIZE_WINDOW_Y, SIZE_WINDOW_X+SIZE_WINDOW_WIDE, SIZE_WINDOW_Y+SIZE_WINDOW_HIGH, 0xfffff, 0xffff);//�ߴ������
}
//************************************************************************************
void SaveOneKnife_datas(Int16U prog,Int16U order,pInt8U pdatas)//���浱ǰ����һ������+info
{
pInt8U pbuf,phead;
Int32U add,sd_add,offset,i;
if(prog<=(PROG_GROPU1+1))  //ǰ301��prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//��  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
sd_add=K_SIZE_sdram+offset;//�������� buf����ַ 

pbuf=(pInt8U)sd_add;
add=DATA_SAVE_OFFSET+offset;//������ spi����ַ
phead=(pInt8U)&OnePro_head;
//********************�ܵ������  ��  info ����
if(Knife_sum_before!=OnePro_head.pro_knifeSUM)
	{
	Knife_sum_before=OnePro_head.pro_knifeSUM;
	for(i=0;i<PRO_HEAD_BYTES;i++)
		{
		*(pbuf+i)=*(phead+i);
		}
	Write_25pe_data(phead,     add,     PRO_HEAD_BYTES);	
	}
//********************������ ����
pbuf=(pInt8U)(sd_add+PRO_HEAD_BYTES+(order-1)*5);//������ buf��ַ
add=add+PRO_HEAD_BYTES+(order-1)*5;
for(i=0;i<5;i++)
   {
   *(pbuf+i)=*(pdatas+i);      //���� ����
   }
Write_25pe_data(pdatas,     add,      5);
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
sd_add=K_SIZE_sdram+offset+PRO_HEAD_BYTES;//������ buf����ַ
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
sd_add=K_SIZE_sdram+offset+PRO_HEAD_BYTES;//������ buf����ַ
   
pbuf=(pInt8U)(sd_add+(order-1)*5);//������ buf��ַ
for(i=0;i<5;i++)
   {
   *pbuf++=*pdatas++;      //���� ����
   }
}

void SaveBuf_datas(Int16U prog,Int16U order1, Int16U order2)//���� order1�� order2  buf�������ݵ�spi
{
pInt8U pbuf,psave;
Int32U add,sd_add,offset,i;
if(prog<=(PROG_GROPU1+1))  //ǰ301��prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//��  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
sd_add=K_SIZE_sdram+offset+PRO_HEAD_BYTES;//������ buf����ַ
pbuf=(pInt8U)(sd_add+(order1-1)*5);
add=DATA_SAVE_OFFSET+offset+PRO_HEAD_BYTES;//������ spi����ַ
add=add+(order1-1)*5;
if(order2>=order1)//
   {
   i=(order2-order1+1)*5;
   Write_25pe_data(pbuf,     add,      i);
   }
}

void ClrBuf_datas(Int16U prog,Int16U order1, Int16U order2)//���� order1�� order2  buf��������   
{
pInt8U pbuf;
Int32U i,lenth,sd_add,offset;
if(prog<=(PROG_GROPU1+1))  //ǰ301��prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//��  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
sd_add=K_SIZE_sdram+offset+PRO_HEAD_BYTES;//������ buf����ַ
pbuf=(pInt8U)(sd_add+(order1-1)*5);
lenth=(order2-order1+1)*5;
for(i=0;i<lenth;i++)
   {
   *pbuf++=0;
   }
}


//-----���� ���ִ�ȡ
void ReadPro_perameter(pInt8U pdata)//��ȡ ���� �� ����xxxxxxxxxxx
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

void SavePro_data(pInt8U pdata)//���� ���� �� ����xxxxxxxxxxx
{
Int32U add;
add=PRO_NUM_25PEADD;//��ַ

Write_25pe_data(pdata, add, 4);
}

void GetPro_headInfo(Int16U prog, pInt8U pdata)//sdram ��һ������ͷ(������+ ʱ�� +���� )
{
Int32U offset;
pInt8U pbuf,pProHead;
Int16U max_sum,i;
//Int16U sum_temp;
PROCESS_HEAD head_temp;
pProHead=(pInt8U) &head_temp;
if(prog<=(PROG_GROPU1+1))  //ǰ301��prog
   {
   offset=PROG_BYTES1*(prog-1);
   max_sum=MAX_KNIFE1;
   }
else//��  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   max_sum=MAX_KNIFE2;
   }
pbuf=(pInt8U)(K_SIZE_sdram+offset);//�������ַ
// pdata=(pInt8U)&OnePro_head;
for(i=0;i<PRO_HEAD_BYTES;i++)
	{
	*(pdata+i)=*(pbuf+i);	
	*(pProHead+i)=*(pbuf+i);	//���� ����ͷ
	}
pProHead=(pInt8U) &ProHead_default;
if((head_temp.pro_knifeSUM<1)||(head_temp.pro_knifeSUM>max_sum))	//����ͷ �ж�
   {
   // //-------����
   // OnePro_head.pro_name[0]=0xff;
   // OnePro_head.pro_name[1]=0xff;
   // OnePro_head.pro_name[2]=0xff;
   // OnePro_head.pro_name[3]=0xff;
   // //-------ʱ��
   // OnePro_head.pro_year=0;
   // OnePro_head.pro_month=0;
   // OnePro_head.pro_day=0;
   // //----����
   // OnePro_head.pro_knifeSUM=1;
   
   for(i=0;i<PRO_HEAD_BYTES;i++)		//���»���sdram
		{
		*pbuf++=*pProHead;
		*pdata++=*pProHead++;
		}
   }
else
	{
	
	}
}

void SavePro_headInfo(Int16U prog, pInt8U pdata)//spi����һ������� ͷ(������+ ʱ�� +���� )
{
Int32U offset,add;
pInt8U pbuf;
Int16U i;
if(prog<=(PROG_GROPU1+1))  //ǰ301��prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//��  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
pbuf=(pInt8U)(K_SIZE_sdram+offset);//�������ַ
//pdata=(pInt8U)&OnePro_head;
for(i=0;i<PRO_HEAD_BYTES;i++)		//����buf
	{
	*(pbuf+i)=*(pdata+i);
	}
	
add=DATA_SAVE_OFFSET+offset;
Write_25pe_data((pInt8U)pbuf, add, PRO_HEAD_BYTES);
// Write_25pe_data((pInt8U)pdata, add, PRO_HEAD_BYTES);	//����
}

void ReadOnePro_datas(Int16U prog) //spi��һ�� �������� �� buf
{
pInt8U pbuf;
Int32U i;
Int32U offset,add;
if(prog<=(PROG_GROPU1+1))  //ǰ301��prog
   {
   offset=PROG_BYTES1*(prog-1);
   }
else//��  199
   {
   offset=PROG_BYTES1*PROG_GROPU1+(prog-PROG_GROPU1-1)*PROG_BYTES2;
   }
pbuf=(pInt8U)(K_SIZE_sdram+offset);//һ��pro�� buf����ַ
add=DATA_SAVE_OFFSET+offset;
FastRead_Datas_Start(add);
for(i=0;i<OnePro_head.pro_knifeSUM*5+PRO_HEAD_BYTES;i++)
   {
   *pbuf++=ReadFlash_Datas();
   }
FlashChip_Dis;
}

void ReadAllPro_head_data1(void)// �����г���ͷ+��һ��  �� buf
{
pInt8U pbuf,pdata;
Int32U add,pro_cou,i;
// Int16U k_sum_temp=1;
Int16U max_sum;
Int8U err_flag=0;

PROCESS_HEAD head_temp;
pro_cou=1;

pdata=(pInt8U)&head_temp;
pbuf=(pInt8U)K_SIZE_sdram;

add=DATA_SAVE_OFFSET;
while(pro_cou<=MAX_PROG)
	{
	FastRead_Datas_Start(add);
	for(i=0;i<5+PRO_HEAD_BYTES;i++)
	   {
		*(pbuf+i)=ReadFlash_Datas();
		*(pdata+i)=*(pbuf+i);
	   }
	FlashChip_Dis;
	
	if(pro_cou<=PROG_GROPU1)//ǰ 300��pro
	   {
	   max_sum=MAX_KNIFE1;//999
	   }
	else
	   {
	   max_sum=MAX_KNIFE2;//399
	   } 
	
	pdata=(pInt8U)&ProHead_default;
	if((head_temp.pro_knifeSUM<1)||(head_temp.pro_knifeSUM>max_sum))//δ��ʼ��
		err_flag=1;
		/***
	if(err_flag==0)
		{
		if(((head_temp.pro_year>>4)&0xf)>9)
			err_flag=1;
		}
	if(err_flag==0)
		{
		if((head_temp.pro_year&0xf)>9)
			err_flag=1;
		}
	if(err_flag==0)
		{
		if(((head_temp.pro_month>>4)&0xf)>9)
			err_flag=1;
		}
	if(err_flag==0)
		{
		if((head_temp.pro_month&0xf)>9)
			err_flag=1;
		}	
	if(err_flag==0)
		{
		if(((head_temp.pro_day>>4)&0xf)>9)
			err_flag=1;
		}
	if(err_flag==0)
		{
		if((head_temp.pro_day&0xf)>9)
			err_flag=1;
		}	
		**/
	if(err_flag==1)
	   {
	   for(i=0;i<PRO_HEAD_BYTES;i++)		//���»���sdram
			{
			*(pbuf+i)=*(pdata+i);
			}
	   for(;i<PRO_HEAD_BYTES+5;i++)
	       {
		   *(pbuf+i)=0;
	       }
	   Write_25pe_data(pbuf, add, PRO_HEAD_BYTES+5);
		}
	
	pro_cou++;   
	if(pro_cou>PROG_GROPU1+1)
	   {
	   pbuf=(pInt8U)(K_SIZE_sdram+PROG_BYTES1*PROG_GROPU1+PROG_BYTES2*(pro_cou-PROG_GROPU1-1));
       add=DATA_SAVE_OFFSET+PROG_BYTES1*PROG_GROPU1+PROG_BYTES2*(pro_cou-PROG_GROPU1-1);
	   }
	else
	   {
	   pbuf=(pInt8U)(K_SIZE_sdram+PROG_BYTES1*(pro_cou-1));
       add=DATA_SAVE_OFFSET+PROG_BYTES1*(pro_cou-1);
	   }
	pdata=(pInt8U)&head_temp;
	}
}

void RenewModifyDate(void)	//����ʱ����Ϣ-.-.-.-.-.-.-.-.-.-.-.-.-.-
{
OnePro_head.pro_year=Year;	//(Year>>4)*10+(Year&0x0f);
OnePro_head.pro_month=Month;	//(Month>>4)*10+(Month&0x0f);
OnePro_head.pro_day=Dom;	//(Dom>>4)*10+(Dom&0x0f);
SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);	//����
}


void ReadDatas_to_sdram(void)///�����ݶ���sdram
{
Int32U add,d,sum;
KNIFE_DATA Knife_datas;
pInt8U pdata,pbuf,p_head;
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
   MAX_Knife=MAX_KNIFE1;//999
   }
 else
   {
   MAX_Knife=MAX_KNIFE2;//399
   } 

if((Pro_data.pro_sum<1)||(Pro_data.pro_sum>MAX_PROG))//������ ��Ч�����ʼ��
  {
  Pro_data.pro_num=1;//��ǰ���� ��1
  Pro_data.pro_sum=1;//���� ����
  // OnePro_head.pro_knifeSUM=1;//�� ����
  pdata=(pInt8U)&Pro_data;
  SavePro_data(pdata);
  
  // //-------����
   // OnePro_head.pro_name[0]=0xff;
   // OnePro_head.pro_name[1]=0xff;
   // OnePro_head.pro_name[2]=0xff;
   // OnePro_head.pro_name[3]=0xff;
   // //-------ʱ��
   // OnePro_head.pro_year=0;
   // OnePro_head.pro_month=0;
   // OnePro_head.pro_day=0;
   // //----����
   // OnePro_head.pro_knifeSUM=1;	
   pbuf=(pInt8U)K_SIZE_sdram;
   pdata=(pInt8U)&OnePro_head;
   p_head=(pInt8U)&ProHead_default;
   for(d=0;d<PRO_HEAD_BYTES;d++)
		{
		*pbuf++=*p_head;
		*pdata++=*p_head++;
		}
  ClrBuf_datas(Pro_data.pro_num, 1,MAX_Knife);  //���� ������buf
  
  
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
  //OnePro_head.pro_knifeSUM=1;
  // Pro_data.pro_num=4;
  //Pro_data.pro_sum=2;
  ReadAllPro_head_data1();  ///������ ���� 	head + data1
  GetPro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head); //��ȡǰ���� ͷ��Ϣ
 // ReadOnePro_datas(Pro_data.pro_num);//��ȡ ��ǰpro
  ClrBuf_datas(Pro_data.pro_num, 1,MAX_Knife);  //���� ������buf
  
  //OnePro_head.pro_knifeSUM=100;
  ReadOnePro_datas(Pro_data.pro_num);//��ȡ һ��pro
  
  CheckKnifeSum_exec();  //--------------�ܵ���    �˶�
  Knife_sum_before=OnePro_head.pro_knifeSUM;
	//---------������Ч ����ʱ��
  // GetOneKnife_datas(Pro_data.pro_num, 1 , (pInt8U)&Knife_datas);//ȡ��һ�� ����
  // if(Knife_datas.size>0)
	  // {
	  read_time();
	  RenewModifyDate();	//����ʱ����Ϣ-.-.-.-.-.-.-.-.-.-.-.-.-.-
	  // }
  }
 
 /*
  pdata=(pInt8U)K_SIZE_sdram;
  add=DATA_SAVE_OFFSET;
  if(Pro_data.pro_sum<=PROG_GROPU1)
    {
	sum=PROG_BYTES1*Pro_data.pro_sum;
	}
  else
    {
	sum=PROG_BYTES1*PROG_GROPU1+(Pro_data.pro_sum-PROG_GROPU1)*PROG_BYTES2;
	}
  FastRead_Datas_Start(add);
  for(d=0;d<sum;d++)
    {
     *pdata++=ReadFlash_Datas();
    }
  FlashChip_Dis;   
  } */
  
}




void OneProgHeadInfo_dis(Int8U row, Int16U p_order, Int8U mark_flag)	//һ������ ��ʾ
{
Int16U color;
PROCESS_HEAD Pro_head;
if(mark_flag==0)
	{
	color=BLACK_COLOR;
	}
else
	{
	color=RED_COLOR;
	}
GetPro_headInfo(ProNumGroup[p_order],  (pInt8U)&Pro_head);//sdram ��һ������ͷ(������+ ʱ�� +���� )
ProgOrder_dis(row, ProNumGroup[p_order], color);//--------��ʾһ�� �����
ProgName_dis(row,  Pro_head, color);//-----------------------��ʾһ��������
ProgStep_dis(row, Pro_head, color);//-----------------------��ʾ������
ProgDate_dis(row, Pro_head, color);//-----------------------��ʾ����
}

void Prog_1page_dis(Int16U p_order,Int16U line)//һҳ������ʾ
{
//pInt8U pbuf;
PROCESS_HEAD Pro_head;
Int16U x1,y1,x2,y2,back_color=TEXT_TAB_BACK_COLOR;
x1=PROC_NUM_X; y1=PROC_NUM_Y;
x2=(MIDDLE_PAGE_X+M_PAGE_WIDE)-10; y2=y1+(PROTEXT_HIGH*PROGS_1PAGE);
GLCD_SetWindow_Fill(x1, y1, x2, y2, back_color, back_color);//
while(line<PROGS_1PAGE)
	{
	if(p_order<=MAX_PROG)
		{
		// GetOneKnife_datas(ProNumGroup[prog_order], 1 , (pInt8U)&Knife_datas);//ȡ��һ�� ����
		// KnifeOrder_dis(line, ProNumGroup[prog_order],0);//���
		// KnifeSize_dis(line,Knife_datas.size,0);//�ߴ�
		GetPro_headInfo(ProNumGroup[p_order],  (pInt8U)&Pro_head);//sdram ��һ������ͷ(������+ ʱ�� +���� )
		ProgOrder_dis(line, ProNumGroup[p_order], 0);//--------��ʾһ�� �����
		ProgName_dis(line,  Pro_head, 0);//-----------------------��ʾһ��������
		ProgStep_dis(line, Pro_head, 0);//-----------------------��ʾ������
		ProgDate_dis(line, Pro_head, 0);//-----------------------��ʾ����
		p_order++;
		}
	else//��������
		{
		// x=PROC_NUM_X;
		// y=RIGHT_ARROW_Y+(line%PAGE_KNIFE)*SIZETEXT_HIGH;
	    // GLCD_SetWindow_Fill( x, y, x+500, y+SIZETEXT_HIGH, back_color, back_color);//�ߴ�����
		}
	
	line++;
	}
}

void Size_1page_dis(Int16U start_order,Int16U row)//һҳ�ߴ���ʾ
{
//Int16U n;
//pInt8U pbuf;
KNIFE_DATA Knife_datas;
Int16U x1,y1,x2,y2,back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
//Int8U sel_flag=0;

//pbuf=(pInt8U)(K_SIZE_sdram+(start_order*5));
while(row<PageKf_Size)
   {
   if(start_order<=MAX_Knife)
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
			// if((Knife_datas.size<Size_MIN_num)||(Knife_datas.size>Size_MAX_num))
			if(0)		//*****************************************************************2015--12--31---
				{
				Knife_datas.size=0;
				Knife_datas.k_flag=0;
				if(OnePro_head.pro_knifeSUM>=start_order)
					{
					if(start_order>1)
						OnePro_head.pro_knifeSUM=start_order-1;
					else
						OnePro_head.pro_knifeSUM=1;
					Knife_sum_before=OnePro_head.pro_knifeSUM;
					SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);	//����**
					StepNum_dis(OnePro_head.pro_knifeSUM,start_order);//�������
					}
				}
			if(start_order>OnePro_head.pro_knifeSUM)	//���һ������ ֮���������� �����
				{
				if(Knife_datas.size>0)
					{
					Knife_datas.size=0;
					Knife_datas.k_flag=0;
					}
				}
				
			KnifeSize_dis(row,Knife_datas.size,0);//�ߴ�
			}
      
		if((ButtonTouch_mode==0)||(ButtonTouch_mode==TOU_MODE_F4)) //	 �� ���������� ��
			AllFlagPic_dis(row,Knife_datas.k_flag); // ��ֽ ��־ 
	  }
   else
      {
	  x1=RIGHT_ARROW_X;
      y1=RIGHT_ARROW_Y+row*Kf_Line_HIGH;
	  y2=y1+Kf_Line_HIGH-20;
	  if(ButtonTouch_mode==0)  //	 �� ���������� ��
		  x2=TABLE_END_COL;
	  else if(ButtonTouch_mode==TOU_MODE_CALC)
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
pbuf_k1=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+(knife-1)*5);//��ǰ�� buf����ַ
pbuf_k2=pbuf_k1+5;        //��һ�� 

num=OnePro_head.pro_knifeSUM-knife;
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
	  if((OneKnife_data.k_flag&0x0f)==KNIFE_FLAG)
		 {
		 // OneKnife_data.k_flag=NO_FLAG;  //��� ��־
		 OneKnife_data.k_flag&=0xf0;  //��� ��־
		 SaveOneKnife_datas(prog, knife , pKnife_data);//����һ������
		 }
	  } 
	
   pbuf_k1=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+(knife-1)*5);//��ǰ�� buf����ַ
   add=DATA_SAVE_OFFSET+offset+PRO_HEAD_BYTES+(knife-1)*5;//
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
pbuf_k1=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+(OnePro_head.pro_knifeSUM-1)*5);//���һ�� buf����ַ
pbuf_k2=pbuf_k1+5;        //��һ��

pbuf_k1+=4;
pbuf_k2+=4;
num=OnePro_head.pro_knifeSUM-knife+1;

for(n=0;n<num*5;n++)
   {
   *pbuf_k2--=*pbuf_k1--;
   }   
pbuf_k1=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+(knife)*5);//��ǰ�� buf����ַ
add=DATA_SAVE_OFFSET+offset+PRO_HEAD_BYTES+(knife)*5;//
Write_25pe_data(pbuf_k1,     add,      num*5);   
}

Int8U CheckInputNums(void)  //����ߴ� ����
{
Int8U nn,num_bits;
pInt8U Size;
Int32U temp=0;
nn=0;
Dot_flag=0;
if(WorkStart_flag==0)// if((ButtonTouch_mode==0)||(ButtonTouch_mode==TOU_MODE_F4)) // ��ǿ�ģʽ
	{
	Size=Size_temp;
	num_bits=num_cou;	
	}
else					// else if(ButtonTouch_mode==TOU_MODE_CALC)    //���� ������
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
		 
		 case TEACH_MODE://ʾ�̻�����
		 case AUTO_MODE://�Զ���������
		 // // case SELF_CUT_MODE://�Ե���������
		 case MANUAL_MODE:   //�ֶ�
		 case PROG_FLAG_MODE:		//��� ģʽ
		 case TEACH_FLAG_MODE:		//��� ģʽ
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
						case INDONSIA:	//ӡ��
							Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
						case PORTUGAL:	//������
								Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;											
						case SPANISH: //������
								Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
						}
					// if(ButtonTouch_mode==TOU_MODE_CALC)   //������
						// {
						ClearCalculatorInput(); //��������� ����
						// }
					return 0;
					}
				else   //��ȷ	 
					{
					PromptNum_dis();//���뷶Χ ��ʾ
					PromptDis_flag=1;
					return 1;
					}	
					break;
		case AUTO_LABEL_MODE://	��� ��ǩ	
		case TEACH_LABEL_MODE:// ʾ�� ��ǩ	
		case AUTO_DIVIDE_MODE://��� �ȷ�
		case TEACH_DIVIDE_MODE://ʾ�� �ȷ�
		// // case AUTO_RULER_MODE://�Զ� ��׼
		// // case SELF_RULER_MODE://�Ե� ��׼
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
							case INDONSIA:	//ӡ��
								Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
							case PORTUGAL:	//������
									Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;											
							case SPANISH: //������
									Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
							}
						// if(ButtonTouch_mode==TOU_MODE_CALC)   //������
							// {
							ClearCalculatorInput(); //��������� ����
							// }
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
					if((WorkMode&0x0f)==(AUTO_DIVIDE_MODE&0x0f))//�ȷ�
						{
						InputSize=temp;
						if(DivideValue_flag==0)
							{
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
							if(InputSize<=Size_MAX_num)   //��ȷ
								{
								PromptNum_dis();//���뷶Χ ��ʾ
								PromptDis_flag=1;
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
									case INDONSIA:	//ӡ��
										Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
										break;
									case PORTUGAL:	//������
										Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
										break;											
									case SPANISH: //������
										Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
										break;
									}
								return 0;
								}
							}
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
								case INDONSIA:	//ӡ��
									Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
										break;
								case PORTUGAL:	//������
										Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
										break;											
								case SPANISH: //������
										Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
										break;
								}
							}
						return 0;		
						}
					return 0;		
					}
					break;
		case READ_PRO_MODE:    //����ѡ��----------------------
		// // case TEACH_PRO_MODE:    //����ѡ��----------------------
				if((temp>0)&&(temp<=MAX_PROG))// ��Ч
					{
					InputSize=temp;
					return 1;
					}
				return 0;	
					break;
				
		// // case AUTO_TOOLS_MODE://�Զ�  ��������
		// // case SELF_TOOLS_MODE://�Ե�  ��������
		case MANUAL_TOOLS_MODE:// �ֶ� ����ģʽ
				if(PramSel_Page<1)	//page 1
					{
					if(Para_sel>8)
						{
						InputSize=temp;
						}
					else //if(Para_sel<7)
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
						if(Unit==UNIT_MM)
							{
							InputSize=temp*100;
							}
						else
							{
							InputSize=temp*1000;
							}
						}
					else 
						{
						// InputSize=temp;
						}
					}
				return 1;	
					break;
		case AUTO_PLUS_MODE:  //F5++
		case AUTO_MINUS_MODE:// F6--
		case TEACH_PLUS_MODE:  //F5++
		case TEACH_MINUS_MODE:// F6--
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
		 // // case SELF_CUT_MODE://�Ե��������� 
		 case MANUAL_MODE:   //�ֶ�
		 case PROG_FLAG_MODE:		//��� ģʽ
		 case TEACH_FLAG_MODE:		//��� ģʽ
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
						case INDONSIA:	//ӡ��
							Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
						case PORTUGAL:	//������
								Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;											
						case SPANISH: //������
								Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
						}
					// if(ButtonTouch_mode==TOU_MODE_CALC)   //������
						// {
						ClearCalculatorInput(); //��������� ����
						// }
					return 0;
					}
				else   //��ȷ	 
					{
					PromptNum_dis();//���뷶Χ ��ʾ
					PromptDis_flag=1;
					return 1;
					}	
					break;
		case AUTO_LABEL_MODE://	��� ��ǩ	
		case TEACH_LABEL_MODE:// ʾ�� ��ǩ	
		case AUTO_DIVIDE_MODE://��� �ȷ�
		case TEACH_DIVIDE_MODE://ʾ�� �ȷ�
		// // case AUTO_RULER_MODE://�Զ� ��׼
		// // case SELF_RULER_MODE://�Ե� ��׼
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
							case INDONSIA:	//ӡ��
								Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
							case PORTUGAL:	//������
									Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;											
							case SPANISH: //������
									Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
							}
						// if(ButtonTouch_mode==TOU_MODE_CALC)   //������
							// {
							ClearCalculatorInput(); //��������� ����
							// }	
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
					if((WorkMode&0x0f)==(AUTO_DIVIDE_MODE&0x0f))  //�ȷ�
						{
						if(DivideValue_flag==0)	//�ȷ���
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
							if(InputSize<=Size_MAX_num)   //��ȷ
								{
								PromptNum_dis();//���뷶Χ ��ʾ
								PromptDis_flag=1;
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
									case INDONSIA:	//ӡ��
										Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
									case PORTUGAL:	//������
											Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;											
									case SPANISH: //������
											Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
									}
								return 0;
								}
							}
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
								case INDONSIA:	//ӡ��
									Printf16("Input data melebihi batas",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
										break;
								case PORTUGAL:	//������
										Printf16("Dados de entrada excede o limite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
										break;											
								case SPANISH: //������
										Printf16("Los datos de entrada excede el l��mite",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
										break;
								}
							}
						return 0;	
						}
					return 0;	
					}
				return 0;	
					break;
		case READ_PRO_MODE:    //����ѡ��----------------------
		// // case TEACH_PRO_MODE:    //����ѡ��----------------------
				if(Unit==UNIT_MM)
					{
					InputSize=temp/100;
					}
				else
					{
					InputSize=temp/1000;
					}
				if((InputSize>0)&&(InputSize<=MAX_PROG))// ��Ч
					{
					return 1;
					}
				return 0;	
					break;	
					
		// // case AUTO_TOOLS_MODE://�Զ�  ��������
		// // case SELF_TOOLS_MODE://�Ե�  ��������
		case MANUAL_TOOLS_MODE:// �ֶ� ����ģʽ
				if(PramSel_Page<1)	//page 1
					{
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
					}
				else	//page 2
					{
					
					}
				return 1;	
					break;
		case AUTO_PLUS_MODE:  //F5++
		case AUTO_MINUS_MODE:// F6--
		case TEACH_PLUS_MODE:  //F5++
		case TEACH_MINUS_MODE:// F6--
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

void LabelSel_dis(Int8U sel, Int8U flag) //��ǩҳ  �趨ѡ��
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
			Printf24("0    ",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
			}
			break;
	case 2://�ϱ�	
		ProgSet_dis(Waste_size, WASTE_SIZE_X,  WASTE_SIZE_Y,flag);
		if(flag==1)
			{
			PromptNum_dis();//���뷶Χ
			//PromptDis_flag=1;
			PromptDis_flag=0;
			//GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);
			Printf24("0    ",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
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
pbuf=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+order*5);//�������ַ
add=DATA_SAVE_OFFSET+offset+PRO_HEAD_BYTES+order*5;

OneKnife_data.size=Total_size;  //�ߴ��޸�
OneKnife_data.k_flag=NO_FLAG;  //��� ��־
SaveOneKnife_datas(Pro_data.pro_num, order++ , pKnife_data);//����һ������
data=Total_size;
while(order<=MAX_Knife)
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
RenewModifyDate();	//����ʱ����Ϣ-.-.-.-.-.-.-.-.-.-.-.-.-.-	
//-----��ʾ
//CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  800, 269); //�˳� ��ǩ����
//  ------------���±�� ���� ��ʾ
if(order>=OnePro_head.pro_knifeSUM)
   {
   if(order<=MAX_Knife)
      {
	  OnePro_head.pro_knifeSUM=order-1;
	  }
   else
	  {
	  OnePro_head.pro_knifeSUM=MAX_Knife;
	  }
   }
SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);//���� ����  
StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//�������
Size_1page_dis(Knife_order,cursor_row);	
SaveBuf_datas(Pro_data.pro_num,  Knife_order+1,  order-1); //����
PromptNum_dis();//���뷶Χ ��ʾ
PromptDis_flag=1;
}

void CursorDown_inTable(void) //**** ������� ��ʾ ����
{
if(Knife_order<=MAX_Knife)
	{
	if(Knife_order>OnePro_head.pro_knifeSUM) //�ص� ��һ��ѭ��
		{
		CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
		cursor_row=0;
		CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
		Knife_order=1;//
		Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
		}	
	else
		{
		if(Knife_order==OnePro_head.pro_knifeSUM)
			{
			if(AutoRoute_flag==1) //�Զ� �ص� ��һ��ѭ��
				{
				CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
				cursor_row=0;
				CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
				Knife_order=1;
				Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
				}
			else
				{
				Knife_order++;
				if(Knife_order<=MAX_Knife)   //999 ����
					{
					if(cursor_row<(PageKf_Size-1))
						{
						CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
						OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //һ������ ������ʾ
						cursor_row++;
						CursorKnife_dis(cursor_row, 1);//��ɫ���������ʾ
						OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //һ������ ������ʾ
						}
					else   //ҳ��
						{
						Size_1page_dis(Knife_order-(PageKf_Size-1),0);//һҳ�ߴ���ʾ
						}
					}
				else  //999��  �ص� ��һ��ѭ��
					{
					CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
					cursor_row=0;
					CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
					Knife_order=1;
					Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
					}
				}
			}
		else
			{
			Knife_order++;
			if(Knife_order<=MAX_Knife)   //999 ����
				{
				if(cursor_row<(PageKf_Size-1))
					{
					CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
					OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //һ������ ������ʾ
					cursor_row++;
					CursorKnife_dis(cursor_row, 1);//��ɫ���������ʾ
					OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //һ������ ������ʾ
					}
				else   //ҳ��
					{
					Size_1page_dis(Knife_order-(PageKf_Size-1),0);//һҳ�ߴ���ʾ
					}
				}
			else  //999��  �ص� ��һ��ѭ��
				{
				CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
				cursor_row=0;
				CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
				Knife_order=1;
				Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
				}
			}
		}
	if(Knife_order<=OnePro_head.pro_knifeSUM+1)
		StepOrder_dis(Knife_order);//�������
	// if(ButtonTouch_mode!=TOU_MODE_F4)
		// {
		// switch(WorkMode)
			// {
			// case AUTO_PLUS_MODE:  //F5++
			// case AUTO_MINUS_MODE:// F6--
			// case SELF_PLUS_MODE://�Ե�F5++
			// case SELF_MINUS_MODE://�Ե� F6--
					// break;
			// default:
				PromptNum_dis();//���뷶Χ
				PromptDis_flag=1;
					// break;
			// }
		// }
	}
}

void PageUpExec(void)	//�Ϸ�ҳ
{
Int8U chg_flag=0;
if(Run_flag==0)
	{
	switch(WorkMode)
		{
		
		case TEACH_MODE://ʾ�̻�����
		case AUTO_MODE://�Զ���������
		
		case SELF_CUT_MODE://�Ե���������
		
		case PROG_FLAG_MODE:	//��� ģʽ
		case TEACH_FLAG_MODE:	//��� ģʽ
			if(Knife_order>PageKf_Size)
				{
				CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
				cursor_row=0;
				CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
				Knife_order-=PageKf_Size;
				Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
				chg_flag=1;
				}
			else
				{
				if(Knife_order>1)
					{
					CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
					cursor_row=0;
					CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
					Knife_order=1;
					Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
					chg_flag=1;
					}
				}
					break;
		case READ_PRO_MODE:    //����ѡ��----------------------
		// // case TEACH_PRO_MODE:    //����ѡ��----------------------
				if(prog_order>PROGS_1PAGE)
					{
					prog_order=prog_order-PROGS_1PAGE-cursor_pro;
					CursorPro_dis(cursor_pro,0);//���
					cursor_pro=0;
					CursorPro_dis(cursor_pro,1);//
					Prog_1page_dis(prog_order, 0);//===����---������ʾ
					OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//һ������ ��ʾ1
					}
					 break;
		}
	if(chg_flag==1)
		{
		if(Knife_order<=OnePro_head.pro_knifeSUM+1)
			StepOrder_dis(Knife_order);//�������
		// if(ButtonTouch_mode!=TOU_MODE_F4)
			// {
			PromptNum_dis();//���뷶Χ
			PromptDis_flag=1;
			// }
		}
	}	
}
void PageDownExec(void)	//�·�ҳ
{
Int8U chg_flag=0;
Int16U temp;
if(Run_flag==0)
	{
	switch(WorkMode)
		{
		
		case TEACH_MODE://ʾ�̻�����
		case AUTO_MODE://�Զ���������
		case SELF_CUT_MODE://�Ե���������
		
		case PROG_FLAG_MODE:	//��� ģʽ
		case TEACH_FLAG_MODE:	//��� ģʽ
			temp=PageKf_Size-1-cursor_row;
			temp+=Knife_order;
			if(temp+PageKf_Size<=OnePro_head.pro_knifeSUM)	//���� ʣ��1ҳ δ��ʾ
				{
				CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
				cursor_row=0;
				CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
				Knife_order+=PageKf_Size;
				Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
				chg_flag=1;
				}
			else	//ʣ�²���һҳ
				{
				if(temp<OnePro_head.pro_knifeSUM)
					{
					CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
					cursor_row=0;
					CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
					Knife_order=OnePro_head.pro_knifeSUM;
					Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
					chg_flag=1;
					}
				}
					break;
		case READ_PRO_MODE:    //����ѡ��----------------------
		// // case TEACH_PRO_MODE:    //����ѡ��----------------------
				temp=prog_order+PROGS_1PAGE-cursor_pro;
				if(temp<=MAX_PROG)
					{
					CursorPro_dis(cursor_pro,0);//���
					cursor_pro=0;
					CursorPro_dis(cursor_pro,1);//
					prog_order=temp;
					Prog_1page_dis(prog_order, 0);//===����---������ʾ
					OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//һ������ ��ʾ1
					}
					 break;
		}
	if(chg_flag==1)
		{
		if(Knife_order<=OnePro_head.pro_knifeSUM+1)
			StepOrder_dis(Knife_order);//�������
		// if(ButtonTouch_mode!=TOU_MODE_F4)
			// {
			PromptNum_dis();//���뷶Χ
			PromptDis_flag=1;
			// }
		}	
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
			if(DivideValue_flag==0)
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
					case INDONSIA:	//ӡ��
						Printf24("Rentang nilai      untuk",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
								break;
					case PORTUGAL:	//������
						Printf16("Intervalo de dados           --",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
					}
				Printf24("1         1000",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
				}
			else
				{
				PromptNum_dis();//���뷶Χ
				//PromptDis_flag=1;
				PromptDis_flag=0;
				Printf24("0   ",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
				}
			}
			break;
	}
}

void DivideTypeSelExec(void)	//�ȷ� ����  ѡ��........
{
volatile Int16U x,y,gap;
Int16U back_color=TEXT_TAB_BACK_COLOR; //�ı�ҳ  ����ɫ
x=TOTAL_SIZE_X-150,y=TOTAL_SIZE_Y,gap=ROW_GAP2;
GLCD_SetWindow_Fill(x,y, x+250,y+gap*2, back_color,back_color);
if(DivideValue_flag==1)	//�ȷ�ֵ����
	{
	//���
	switch(Language)
		{
		case CHN_HAN:
			Printf24("�ܳ���",x,y,BLACK_COLOR,1,back_color);y+=gap;
			Printf24("�ȷ�ֵ��",x,y,BLACK_COLOR,1,back_color);
				break;
		case ENGLISH:	
			Printf24("Total size��",x,y,BLACK_COLOR,1,back_color);y+=gap;
			Printf24("Div-Value��",x,y,BLACK_COLOR,1,back_color);
				break;
		case INDONSIA:	//ӡ��
			Printf24("Panjangnya��",x,y,BLACK_COLOR,1,back_color);y+=gap;
			Printf24("Aliquots��",x,y,BLACK_COLOR,1,back_color);
				break;
		case PORTUGAL:	//������
			Printf24("Total��",x,y,BLACK_COLOR,1,back_color);y+=gap;
			Printf24("Al��    ",x,y,BLACK_COLOR,1,back_color);
			Printf24("   quotas:",x,y,BLACK_COLOR,0,back_color);//Al��quotas
				break;
		}
	}
else		//�ȷ���
	{
	//���
	switch(Language)
		{
		case CHN_HAN:
			Printf24("�ܳ���",x,y,BLACK_COLOR,1,back_color);y+=gap;
			Printf24("�ȷ�����",x,y,BLACK_COLOR,1,back_color);
				break;
		case ENGLISH:	
			Printf24("Total size��",x,y,BLACK_COLOR,1,back_color);y+=gap;
			Printf24("Div-Num��",x,y,BLACK_COLOR,1,back_color);
				break;
		case INDONSIA:	//ӡ��
			Printf24("Panjangnya��",x,y,BLACK_COLOR,1,back_color);y+=gap;
			Printf24("Aliquots��",x,y,BLACK_COLOR,1,back_color);
				break;
		case PORTUGAL:	//������
			Printf24("Total��",x,y,BLACK_COLOR,1,back_color);y+=gap;
			Printf24("Al��    ",x,y,BLACK_COLOR,1,back_color);
			Printf24("   quotas:",x,y,BLACK_COLOR,0,back_color);//Al��quotas
				break;
		}
	}
Total_size=0;//�ܳ�
Divide_num=0;//�ȷ���
PorgSet_sel=0;
ProgSet_dis( 0, DIVIDE_TOTAL_X,  DIVIDE_TOTAL_Y,1);//
PorgSet_sel=1;
ProgSet_dis( 0, DIVIDE_NUM_X,  DIVIDE_NUM_Y,0);
PorgSet_sel=0;
PromptNum_dis();//���뷶Χ
PromptDis_flag=1;
SubModeIcon_dis(WorkMode);   //�ȷ�ģʽ
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
								// // CalcuInClear_exec();     //��� ������
							ClearCalculatorInput(); //��������� ����
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
								// // CalcuInClear_exec();     //��� ������
							ClearCalculatorInput(); //��������� ����
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
								// // CalcuInClear_exec();     //��� ������
							ClearCalculatorInput(); //��������� ����
							}
						}
					}
				else
					num_cou=0;
					break; 
	}
	
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
								// // CalcuInClear_exec();     //��� ������
							ClearCalculatorInput(); //��������� ����
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
								// // CalcuInClear_exec();     //��� ������
							ClearCalculatorInput(); //��������� ����	
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
// if(ButtonTouch_mode==0)  //	 �� ���������� ��	
	// ClrInput_function();//���� ����� 		
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
pbuf=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+order*5);//�������ַ
add=DATA_SAVE_OFFSET+offset+PRO_HEAD_BYTES+order*5;

OneKnife_data.size=Total_size;  //�ߴ��޸�
OneKnife_data.k_flag=NO_FLAG;  //��� ��־
SaveOneKnife_datas(Pro_data.pro_num, order++ , pKnife_data);//����һ������
if(DivideValue_flag==0)
	{
	data=Total_size;
	d_size=Total_size/Divide_num;
	}
else
	{
	data=Total_size;
	d_size=Divide_num;
	}
while(order<=MAX_Knife)
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
RenewModifyDate();	//����ʱ����Ϣ-.-.-.-.-.-.-.-.-.-.-.-.-.-
//-----��ʾ
//CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  800, 269); //�˳� ��ǩ����
//  ------------���±�� ���� ��ʾ
if(order>=OnePro_head.pro_knifeSUM)
   {
   if(order<=MAX_Knife)
      {
	  OnePro_head.pro_knifeSUM=order-1;
	  }
   else
	  {
	  OnePro_head.pro_knifeSUM=MAX_Knife;
	  }
   }
SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);//���� ����  
StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//�������
Size_1page_dis(Knife_order,cursor_row);	
SaveBuf_datas(Pro_data.pro_num, Knife_order+1,  order-1); //����
PromptNum_dis();//���뷶Χ ��ʾ
PromptDis_flag=1;
}


void ProEnter_exec(void)  //����ѡ�� ����ȷ��
{
Int32U temp,i;
if(CheckInputNums()==1)// ��Ч
   {
	ClearCalculatorInput(); //��������� ����// // CalcuInClear_exec();     //��� ������
	
	if(ProNumGroup[prog_order]!=InputSize)	//�ж� ���� ����
		{
		for(i=1;i<=MAX_PROG;i++)
			{
			if(ProNumGroup[i]==InputSize)
				{
				prog_order=i;
				break;
				}
			}
		}	
	//----��� ��ת
	//prog_order=InputSize;//��ǰ �����
	temp=prog_order%PROGS_1PAGE;
	CursorPro_dis(cursor_pro,0);//���
	if(temp<1)
	   temp=PROGS_1PAGE;
	cursor_pro=temp-1;
	  
	CursorPro_dis(cursor_pro,1);//
	Prog_1page_dis(prog_order-temp+1, 0);//===����---������ʾ
	OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//һ������ ��ʾ1
   }
else
   {
   num_cou=0;
  // PromptDis_flag=0;
  // GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+360, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
//	Printf24("������ֵ��Χ����!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
   }
// if(ButtonTouch_mode==0)  //	 �� ���������� ��
	// ClrInput_function();//���� �����   
}

void ExportOnePro_dis(Int16U p_order) //���� ��ʾһ������-------------
{
Int16U prog;
Int16U x1,x2,y1,y2,back_color=TEXT_TAB_BACK_COLOR;//0xef9f;
pInt8U pdata;
KNIFE_DATA Knife_datas;

// // CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y, M_PAGE_WIDE, M_PAGE_HIGH);
// // ClrSizeTable_dis();//������ �б�հ�
AutoModePage_dis(); //�Զ�ģʽ ���ֻ�����ʾ
//************��ǰpro ����
prog=ProNumGroup[p_order];
Pro_data.pro_num=prog;
pdata=(pInt8U)&Pro_data;
SavePro_data(pdata);
if(prog<=PROG_GROPU1)//ǰ 300��pro
   {
   MAX_Knife=MAX_KNIFE1;//999
   }
else
   {
   MAX_Knife=MAX_KNIFE2;//399
   } 
//ReadOnePro_datas(prog);//��ȡ ��ǰpro
ClrBuf_datas(prog, 1,MAX_Knife);  //���� ������buf
GetPro_headInfo(prog,(pInt8U)&OnePro_head); //��ȡǰ���� ����
 // OnePro_head.pro_knifeSUM=6;
ReadOnePro_datas(prog);//��ȡ һ��pro

CheckKnifeSum_exec();  //--------------�ܵ���    �˶�
Knife_sum_before=OnePro_head.pro_knifeSUM;
//---------������Ч ����ʱ��
//GetOneKnife_datas(prog, 1 , (pInt8U)&Knife_datas);//ȡ��һ�� ����
// if(Knife_datas.size>0)
	// {
	RenewModifyDate();	//����ʱ����Ϣ-.-.-.-.-.-.-.-.-.-.-.-.-.-
	// }
//-------------���� ��ʾ
cursor_pro=0;
Knife_order=1;
cursor_row=0;     // ������ ��ʾ ��ͷ
Size_1page_dis(Knife_order, 0);  
CursorKnife_dis(cursor_row,1);//��ɫ��ͷ  
OneProNum_dis(prog, OnePro_head);// ����� 
StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);// �����  �ܵ���-���

PromptDis_flag=1;
PromptNum_dis();
LastAutoKnife_order=1;
}

void ReorderProByDate_dis(void)	//(��ʱ������) �����б�
{
Int16U p,	l,t,flag;
volatile Int32U date[MAX_PROG+2],temp;
pInt8U pdata;
PROCESS_HEAD pro_Head;

pdata=(pInt8U)&pro_Head;
DisAllProgMode=PRO_BY_TIME;
ProTableIcon_dis();	//�����б�ģʽ�� icon��ʾ
for(p=1;p<=MAX_PROG;p++)
	{
	GetPro_headInfo(ProNumGroup[p],  pdata);//sdram ��һ������ͷ(������+ ʱ�� +���� )
	date[p]=(pro_Head.pro_year<<16)|(pro_Head.pro_month<<8)|pro_Head.pro_day;
	}
/****	
for(l=1;l<MAX_PROG;l++)
	{
	for(t=l+1;t<=MAX_PROG;t++)		//ѡ��
		{
		if(date[t]>date[l])
			{
			temp=date[t];
			date[t]=date[l];
			date[l]=temp;
			
			temp=ProNumGroup[t];
			ProNumGroup[t]=ProNumGroup[l];
			ProNumGroup[l]=temp;
			}
		}
	}
	***/
for(l=1;l<MAX_PROG;l++)
	{
	flag=0;
	for(t=1;t<=MAX_PROG-l;t++)		//ð�ݷ�
		{
		if(date[t]<date[t+1])
			{
			flag=1;
			temp=date[t];
			date[t]=date[t+1];
			date[t+1]=temp;
			
			temp=ProNumGroup[t];
			ProNumGroup[t]=ProNumGroup[t+1];
			ProNumGroup[t+1]=temp;
			}
		}
	if(flag==0)
		break;
	}

//--------��ʾ
prog_order=1;
CursorPro_dis(cursor_pro,0);//pro���
cursor_pro=0;
Prog_1page_dis(prog_order, cursor_pro);//= һҳ����---������ʾ
TableDis_startcol=PROC_NUM_X;
CursorPro_dis(cursor_pro,1);//pro���
OneProgHeadInfo_dis(cursor_pro ,  prog_order, 1);	//һ������ ��ʾ
//ClrInput_function();//���� �����
}

void DeleteOneProg(Int8U cursor, Int16U p_order)		//F4 ----ɾ��һ������
{
//PROCESS_HEAD pro_head;
// GetPro_headInfo(ProNumGroup[p_order],  (pInt8U)&Pro_head_temp);//sdram ��һ������ͷ(������+ ʱ�� +���� )
//�����Ϣͷ������ head_info=0
SavePro_headInfo(ProNumGroup[p_order], (pInt8U)&ProHead_default);
//���4�����ݲ�����
ClrBuf_datas(ProNumGroup[p_order], 1,4);
SaveBuf_datas(ProNumGroup[p_order], 1,4); 
//���� ��ʾ
OneProgHeadInfo_dis(cursor,  p_order, 1);	//һ������ ��ʾ1
if(ProNumGroup[p_order]==Pro_data.pro_num)	//��ǰ���� �Ѵ�
	{
	//====���µ�ǰ���� ��ϢOnePro_head
	GetPro_headInfo(Pro_data.pro_num,  (pInt8U)&OnePro_head);//sdram ��һ������ͷ(������+ ʱ�� +���� )
	Knife_sum_before=OnePro_head.pro_knifeSUM;	//�������=1
	//-----����--���� ��ʾ
	OneProNum_dis(Pro_data.pro_num, OnePro_head);// ����� 
	Knife_order=1;
	StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);// �����  �ܵ���-���
	}
}
void DeleteAllProg(void)	//(Int8U cursor, Int16U p_order)		//F5--- ɾ�����г���
{
Int16U c=1;
Int8U row=0;
//********************ɾ��ǰ  ��ʾ***********
GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
switch(Language)
		{
		case CHN_HAN:
				Printf24("����ɾ��,��Ҫ6��...",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case ENGLISH:	
				Printf24("Deleting,Please wait",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case INDONSIA:	//ӡ��
				Printf24("Menghapus, silakan tunggu",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		case PORTUGAL:	//������
				Printf24("Apagando, 6 segundo",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
						break;
		}
while(c<=MAX_PROG)	//�����Ϣͷ������ head_info=0
	{
	SavePro_headInfo(c, (pInt8U)&ProHead_default);
	//���4�����ݲ�����
	ClrBuf_datas(c, 1,2);
	SaveBuf_datas(c, 1,2); 
	//-------------------------�����б�
	ProNumGroup[c]=c;
	c++;
	}
//********************ɾ������  ��ʾ***********
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
		}
Printf24("1         500",REMIND_WINDOW_X+180,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);

/**
//������ǰ���� ����µ�ǰ ��ʾ----------------------
// if(Pro_data.pro_num>=ProNumGroup[p_order])
	// {
//====���µ�ǰ���� ��ϢOnePro_head
**/
GetPro_headInfo(Pro_data.pro_num,  (pInt8U)&OnePro_head);//sdram ��һ������ͷ(������+ ʱ�� +���� )
Knife_sum_before=OnePro_head.pro_knifeSUM;	//�������=1
//-----����--���� ��ʾ
OneProNum_dis(Pro_data.pro_num, OnePro_head);// ����� 
Knife_order=1;
StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);// �����  �ܵ���-���

//	�����б� ������ʾ-------------------------
CursorPro_dis(cursor_pro,0);//���0
cursor_pro=0;
CursorPro_dis(cursor_pro,1);//

prog_order=1;
Prog_1page_dis(prog_order, 0);//===����---������ʾ
OneProgHeadInfo_dis(cursor_pro,  prog_order, 1);	//һ������ ��ʾ1
}



void F5_AutoAdd_exec(Int32U add_data)  //F5++  �������� �Լ�
{
Int16U order;
Int32U data;
Int16U ord_temp;

order=Knife_order;
pKnife_data=(pInt8U)&OneKnife_data;
GetOneKnife_datas(Pro_data.pro_num, order, pKnife_data);
data=OneKnife_data.size+add_data;
ord_temp=cursor_row;

if((data<=Size_MAX_num)&&(data>=Size_MIN_num)) //��Χ ��
	{
	PromptNum_dis();//���뷶Χ ��ʾ
	PromptDis_flag=1;
	OneKnife_data.size=data;
	SaveOneKnife_datas(Pro_data.pro_num, order++ , pKnife_data);//����һ������
	
	while(order<=OnePro_head.pro_knifeSUM)
		{
		//pKnife_data=(pInt8U)&OneKnife_data;
		GetOneKnife_datas(Pro_data.pro_num, order-1, pKnife_data);//��һ��
		data=OneKnife_data.size;
		GetOneKnife_datas(Pro_data.pro_num, order, pKnife_data);//��ǰ��
		
		if(OneKnife_data.size>data-add_data)
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
	//SavePro_headInfo(Pro_data.pro_num);//���� ���� 
	StepNum_dis(OnePro_head.pro_knifeSUM,order);//�������
	if(order-Knife_order+cursor_row>(PageKf_Size-1)) //��ҳ
		{
		CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
		cursor_row=0;
		CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
		Size_1page_dis(order,cursor_row);	
		}
	else
		{
		CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
		cursor_row+=order-Knife_order;
		CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ	
		Size_1page_dis(Knife_order,ord_temp);	//
		}	
	SaveBuf_datas(Pro_data.pro_num, Knife_order+1,  order); //����
	Knife_order=order;
	PromptNum_dis();//���뷶Χ ��ʾ	
	PromptDis_flag=1;
	RenewModifyDate();	//����ʱ����Ϣ-.-.-.-.-.-.-.-.-.-.-.-.-.-
	}
}

void F6_AutoSub_exec(Int32U add_data)  //F6--  �������� �Լ�
{
Int16U order;
Int32U data;
Int16U ord_temp;

order=Knife_order;
pKnife_data=(pInt8U)&OneKnife_data;
GetOneKnife_datas(Pro_data.pro_num, order, pKnife_data);
ord_temp=cursor_row;
if(OneKnife_data.size>add_data)
  {
  data=OneKnife_data.size-add_data;
  if((data<=Size_MAX_num)&&(data>=Size_MIN_num)) //��Χ ��
	 {
	 PromptNum_dis();//���뷶Χ ��ʾ
	 PromptDis_flag=1;
	 OneKnife_data.size=data;
	 SaveOneKnife_datas(Pro_data.pro_num, order++ , pKnife_data);//����һ������
	
	 while(order<=OnePro_head.pro_knifeSUM)
		{
		//pKnife_data=(pInt8U)&OneKnife_data;
		GetOneKnife_datas(Pro_data.pro_num, order-1, pKnife_data);//��һ��
		data=OneKnife_data.size;
		GetOneKnife_datas(Pro_data.pro_num, order, pKnife_data);//��ǰ��
		if(OneKnife_data.size>data+add_data)
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
	 //SavePro_headInfo(Pro_data.pro_num);//���� ���� 
	 StepNum_dis(OnePro_head.pro_knifeSUM,order);//�������
	 if(order-Knife_order+cursor_row>(PageKf_Size-1)) //��ҳ
		{
		CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
		cursor_row=0;
		CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
		Size_1page_dis(order,cursor_row);	
		}
	 else
		{
		CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
		cursor_row+=order-Knife_order;
		CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ	
		Size_1page_dis(Knife_order,ord_temp);	
		}	
 	 SaveBuf_datas(Pro_data.pro_num, Knife_order+1,  order); //����
	 Knife_order=order;
	 PromptNum_dis();//���뷶Χ ��ʾ
	 PromptDis_flag=1;
	 RenewModifyDate();	//����ʱ����Ϣ-.-.-.-.-.-.-.-.-.-.-.-.-.-
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
if(Language>3)
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
	AutoPushDistance=0;	//10000;20180917
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
if(MotorType>MOTOR_AC_A6_SERVO)
	MotorType=MOTOR_FREQ_3_SPD_RST;	//0  ------��Ƶ��3��
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
Int32U add;Int16U n;
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

void ReadAirOffDistance(void)	//������ ����
{
Int16U n;
Int32U add;
pInt8U pdata;
add=ORIGINAL_25PEADD+110;
pdata=(pInt8U)&AirOffDistance;
FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*pdata++=ReadFlash_Datas();
	}
FlashChip_Dis;
if((AirOffDistance>1000)||(AirOffDistance<100))
	AirOffDistance=0;
}
void SaveAirOffDistance(void)	//������ ����
{
Int16U n;
Int32U add;
pInt8U pdata;
add=ORIGINAL_25PEADD+110;
pdata=(pInt8U)&AirOffDistance;
Write_25pe_data(pdata, add, 4);
}

void ReadElectricWheelSwitch(void)//��������
{
Int32U add;
// pInt8U pdata;
add=ORIGINAL_25PEADD+115;
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
add=ORIGINAL_25PEADD+115;
pdata=(pInt8U)&ElectricWheelOn_flag;
Write_25pe_data(pdata, add, 1);
}

void ReadIRValidStatus(void)	//IR set
{
Int32U add;
// pInt8U pdata;
add=ORIGINAL_25PEADD+116;
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
add=ORIGINAL_25PEADD+116;
pdata=(pInt8U)&IR_SensorStus;
Write_25pe_data(pdata, add, 1);
}


void ReadPageKf_Size(void)	//ÿҳ ������
{
Int32U add;
add=ORIGINAL_25PEADD+117;
FastRead_Datas_Start(add);
PageKf_Size_flag=ReadFlash_Datas();
FlashChip_Dis;
if(PageKf_Size_flag>1)
	PageKf_Size_flag=0;
}
void SavePageKf_Size(void)
{
Int32U add;
pInt8U pdata;
add=ORIGINAL_25PEADD+117;
pdata=(pInt8U)&PageKf_Size_flag;
Write_25pe_data(pdata, add, 1);
}


void ReadStepDistance(void) // ��������
{
pInt8U pdata;
Int8U n;
Int32U add;
pdata=(pInt8U)&Step_Size;
add=ORIGINAL_25PEADD+118;
FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*pdata++=ReadFlash_Datas();
	}
FlashChip_Dis;
if(Step_Size>MAX_STEP_SIZE)
	Step_Size=1000;
}
void SaveStepDistance(void) // ��������
{
Int32U add;
pInt8U pdata;
add=ORIGINAL_25PEADD+118;
pdata=(pInt8U)&Step_Size;
Write_25pe_data(pdata, add, 4);
}

void ReadCurrentPulseAB(void)		//	��ǰ���� ����
{
pInt8U pdata;	
Int8U n;
Int32U add;
pdata=(pInt8U)&PulseAB_Z_current;
add=ORIGINAL_25PEADD+122;
FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*pdata++=ReadFlash_Datas();
	}
FlashChip_Dis;
if(PulseAB_Z_current>0xffff)
	PulseAB_Z_current=0;
}
void SaveCurrentPulseAB(void)		//	��ǰ���� ����
{
pInt8U pdata;	
Int8U n;
Int32U add;
pdata=(pInt8U)&PulseAB_Z_current;
add=ORIGINAL_25PEADD+122;
Write_25pe_data(pdata, add, 4);
}

void ReadVirtualTargetSizeGap(void)		//����Ŀ��ֵ
{
pInt8U pdata;	
Int8U n;
Int32U add;
pdata=(pInt8U)&VirtualTargetSizeGap;
add=ORIGINAL_25PEADD+126;
FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*pdata++=ReadFlash_Datas();
	}
FlashChip_Dis;
if((VirtualTargetSizeGap>100)||(VirtualTargetSizeGap<30))	//	20171017����
	{
	VirtualTargetSizeGap=40;
	}
// if(MotorType!=MOTOR_FREQ_3_SPD_RST)
	// VirtualTargetSizeGap=40;
}
void SaveVirtualTargetSizeGap(void)
{
pInt8U pdata;	
Int8U n;
Int32U add;
pdata=(pInt8U)&VirtualTargetSizeGap;
add=ORIGINAL_25PEADD+126;
Write_25pe_data(pdata, add, 4);
}

void ReadIRChgWorkmodeValid(void)	//�����л�����ģʽ���
{
pInt8U pdata;	
Int8U n;
Int32U add;
add=ORIGINAL_25PEADD+135;
FastRead_Datas_Start(add);	
IRChgWorkmodeValid_flag=ReadFlash_Datas();
FlashChip_Dis;
if(IRChgWorkmodeValid_flag!=1)
	IRChgWorkmodeValid_flag=0;
}
void SaveIRChgWorkmodeValid(void)	//
{
pInt8U pdata;	
Int8U n;
Int32U add;
pdata=(pInt8U)&IRChgWorkmodeValid_flag;
add=ORIGINAL_25PEADD+135;
Write_25pe_data(pdata, add, 1);	
}
void ReadA6MarkBenchSize(void)//A6 ������ ��׼ֵ(6 Byte)
{
pInt8U pdata;	
Int8U n;
Int32U add;
pdata=(pInt8U)&Modbus_A6_JiZhunDesmion;
add=ORIGINAL_25PEADD+130;
FastRead_Datas_Start(add);
for(n=0;n<4;n++)
	{
	*pdata++=ReadFlash_Datas();
	}
pdata=(pInt8U)&Modbus_A6_JiZhunQuan;	
for(n=0;n<2;n++)
	{
	*pdata++=ReadFlash_Datas();
	}
FlashChip_Dis;
}
void SaveA6MarkBenchSize(void)//A6 ������ ��׼ֵ(6 Byte)
{
pInt8U pdata;	
Int8U n;
Int32U add;
pdata=(pInt8U)&Modbus_A6_JiZhunDesmion;
add=ORIGINAL_25PEADD+130;
Write_25pe_data(pdata, add, 4);	
pdata=(pInt8U)&Modbus_A6_JiZhunQuan;
Write_25pe_data(pdata, add+4, 2);	
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
Int8U go_flag=0;

pKdata=(pInt8U)&OneKnife_data;
GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKdata);//
size_data=OneKnife_data.size;
if((size_data>=Size_MIN_num)&&(size_data<=Size_MAX_num))//������Ч
	{
	//SelfLockEn_flag=0;
	//ToTargetStop_flag=0;
	//if(1)
	if(InTargetPosit_flag==1)
		{
		if(Unit==UNIT_MM)//mm
			{
			if(size_data!=TargetSize)
				{
				go_flag=1;
				}
			else
				{
				go_flag=2;
				}
			}
		else
			{
			if(size_data!=TargetSize_inch)
				{
				go_flag=1;
				}
			else
				{
				go_flag=2;
				}
			}
		}
	else
		{
		if(size_data!=CurrentSize)
			{
			go_flag=1;
			}
		}
	//------
	if(go_flag == 1)
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
		if(((OneKnife_data.k_flag&0x0f)==PUSH_FLAG)&&(Knife_order<OnePro_head.pro_knifeSUM))//��ֽ λ����ǰ10mm ����
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
		//-----------------ƫ�������п���----------
		if(CutPressRoll_flag==1)	//����ѭ�� ģʽ
			{
			if(AmendStartRun_flag==1)
				{
				if(AmendPlus_flag == 1)
					TargetSize +=AmendSize;
				else
					TargetSize-=AmendSize;
				}
			}
		else	//ֱ��key����----ȡ�� ---ƫ���� ���п���
			{	
			if(AmendStartRun_flag==1)
				{
				AmendStartRun_flag=0;
				AmendSize=0;
				//----------���� ��ʾF6
				// AmendSwitch_flag=0;
				// AmendButtonFlag_dis();
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
			// // case MOTOR_DC_SERVO:
			// // case MOTOR_DC670_SERVO:
				 // // ServoSendCou=0;
				 // // DcServoStartRun_exec(TargetSize);
				// // // SelfLockEn_flag=0;
					// // break;
			case MOTOR_AC_SERVO:
			case MOTOR_AC_SERVO_REV:
			case MOTOR_AC_A6_SERVO:
				ACMotorRunStart(TargetSize);
					break;		
			}
		RunStop_flag=0;
		Run_flag=1;
		InTargetPosit_flag=0;	//Ŀ��λ��
		AutoCutStart_flag=0;
		AirOffOK_flag=0;
		PressUp_flag=0;
		PressDown_flag=0;
		PromptNum_dis();
		}
	// else if(go_flag==2)
		// {
		// AutoRun_AutoPush_exec();  // �Զ� ����ѭ������
		// }
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
		AutoRun_AutoPush_exec();  // �Զ� ����ѭ������
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
	CurrentToCalc_input();  //��ǰ-1�ߴ� ���ݸ��µ�������
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
							// // case MOTOR_DC_SERVO:
							// // case MOTOR_DC670_SERVO:
								 // // ServoSendCou=0;
								 // // DcServoStartRun_exec(TargetSize);
								// // // SelfLockEn_flag=0;
									// // break;
							case MOTOR_AC_SERVO:
							case MOTOR_AC_SERVO_REV:
							case MOTOR_AC_A6_SERVO:
								 ACMotorRunStart(TargetSize);
									break;		
							}
						Run_flag=1;
						RunStop_flag=0;
						InTargetPosit_flag=0;	//Ŀ��λ��
						AutoPushRun_flag=1;
						AutoCutStart_flag=0;
						AirOffOK_flag=0;
						PressUp_flag=0;
						PressDown_flag=0;
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
					if(((OneKnife_data.k_flag&0x0f)==PUSH_FLAG)&&(Knife_order<OnePro_head.pro_knifeSUM))// λ����ǰ10mm ����
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
							// // case MOTOR_DC_SERVO:
							// // case MOTOR_DC670_SERVO:
								// // ServoSendCou=0;
								 // // DcServoStartRun_exec(TargetSize);
								// // // SelfLockEn_flag=0;
									// // break;
							case MOTOR_AC_SERVO:
							case MOTOR_AC_SERVO_REV:
							case MOTOR_AC_A6_SERVO:
								ACMotorRunStart(TargetSize);
								// SelfLockEn_flag=0;
									break;
							}
						Run_flag=1;
						RunStop_flag=0;
						InTargetPosit_flag=0;	//Ŀ��λ��
						AutoPushRun_flag=1;
						AutoCutStart_flag=0;
						//AirOffOK_flag=0;
						CursorDown_inTable();//**** ������� ��ʾ ����
						PromptNum_dis();

						}
					}
				}
			}
		else//ֱ��  ���е� ��һ��
			{
			
			//-------------------ƫ���� ���п���------------------------------------------------------11111
			if(CutPressRoll_flag==1)	//����ѭ�� ģʽ
				{
				if(AmendSwitch_flag==1)
					{
					if(AmendOver_flag==0)
						{
						if(size_data>CurrentSize)	//����ƫ��ƫ��������
							{
							AmendPlus_flag=0;
							AmendSize=size_data-CurrentSize;
							}
						else		//����
							{
							AmendPlus_flag=1;
							AmendSize=CurrentSize-size_data;
							}
						AmendStartRun_flag=1;
						}
					else
						{
						AmendSize=0;
						AmendStartRun_flag=0;
						}
					}
				}
			CursorDown_inTable();//**** ������� ��ʾ ����
			RunTo_cursor();//    ���е���һ��
			
			AutoPushRun_flag=0;
			}
		}
	}
else   //ֱ��  ���е� ��һ��
	{
	//-------------------ƫ���� ���п���------------------------------------------------------11111
	GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKdata);//
	size_data=OneKnife_data.size;
	GetOneKnife_datas(Pro_data.pro_num, Knife_order+1, pKdata);//
	if(size_data>OneKnife_data.size)	//��һ��<��ǰ
		{
		if(CutPressRoll_flag==1)	//����ѭ�� ģʽ
			{
			if(AmendSwitch_flag==1)
				{
				if(AmendOver_flag==0)
					{
					if(size_data>CurrentSize)	//����ƫ��ƫ��������
						{
						AmendPlus_flag=0;
						AmendSize=size_data-CurrentSize;
						}
					else		//����
						{
						AmendPlus_flag=1;
						AmendSize=CurrentSize-size_data;
						}
					AmendStartRun_flag=1;
					}
				else
					{
					AmendSize=0;
					AmendStartRun_flag=0;
					}
				}
			}
		}
	else	//��һ��>��ǰ
		{
		if(AmendStartRun_flag==1)	//ȡ�� ---ƫ���� ���п���
			{
			AmendStartRun_flag=0;
			AmendSize=0;
			//----------���� ��ʾF6
			// AmendSwitch_flag=0;
			// AmendButtonFlag_dis();
			}
		}
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
GetOneKnife_datas(Pro_data.pro_num, OnePro_head.pro_knifeSUM, pKdata);//��ȡ ���һ��
size_data=OneKnife_data.size;
if((size_data>=Size_MIN_num)&&(size_data<=Size_MAX_num))  //��ǰ�ߴ�  ��Ч  �����²��ң�-----�������  ��Ӱ��
	{
	knife_temp=OnePro_head.pro_knifeSUM+1;
	while(knife_temp<=MAX_Knife)
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
		
	if(knife_temp>OnePro_head.pro_knifeSUM+1)//��������  ����
		{
		OnePro_head.pro_knifeSUM=knife_temp-1;
		SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);//���� ����  
		if(WorkStart_flag==1)
			StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//�������
		}
	}
else	//�ߴ���Ч   �����ϲ��ң�
	{
	knife_temp=OnePro_head.pro_knifeSUM-1;
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
		if(OnePro_head.pro_knifeSUM!=1)
			{
			OnePro_head.pro_knifeSUM=1;
			SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);//���� ����  
			ClrBuf_datas(Pro_data.pro_num, 1,MAX_Knife);  //���� ������buf
			ReadOnePro_datas(Pro_data.pro_num);//��ȡ ��ǰpro
			if(WorkStart_flag==1)
				StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//�������
			}
		}
	else
		{
		OnePro_head.pro_knifeSUM=knife_temp;
		SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);//���� ����
		ClrBuf_datas(Pro_data.pro_num, 1,MAX_Knife);  //���� ������buf
		ReadOnePro_datas(Pro_data.pro_num);//��ȡ ��ǰpro
		if(WorkStart_flag==1)
			StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//�������
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
	//************20180516		fast	
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




void DeleteAllData_hintWind(void)	//ɾ����������  ��ʾ��
{
Int16U line_color,fill_color;
//------------
CurrentArea_save1(DEL_ALL_WIN_X,DEL_ALL_WIN_Y, DEL_ALL_WIN_WIDE,DEL_ALL_WIN_HIGH);
line_color=RED_COLOR,fill_color=PRO_MESS_COLOR1;
GLCD_SetWindow_Fill(DEL_ALL_WIN_X, DEL_ALL_WIN_Y,DEL_ALL_WIN_X+DEL_ALL_WIN_WIDE-1 ,DEL_ALL_WIN_Y+DEL_ALL_WIN_HIGH-1 , line_color, fill_color);
fill_color=BLUE_COLOR;
switch(Language)
	{
	case CHN_HAN:
		Printf24("�Ƿ�ɾ��ȫ������?",DEL_ALL_HINT_X,DEL_ALL_HINT_Y,BLACK_COLOR,0,fill_color);
		Printf24("ȷ��",DEL_ALL_OK_X,DEL_ALL_OK_Y,BLACK_COLOR,1,fill_color);
		Printf24("ȡ��",DEL_ALL_CANCEL_X,DEL_ALL_CANCEL_Y,BLACK_COLOR,1,fill_color);
			break;
	case ENGLISH:	
		Printf24("Delete all the data?",DEL_ALL_HINT_X,DEL_ALL_HINT_Y,BLACK_COLOR,0,fill_color);
		Printf24("OK",DEL_ALL_OK_X,DEL_ALL_OK_Y,BLACK_COLOR,1,fill_color);
		Printf24("Cancel",DEL_ALL_CANCEL_X,DEL_ALL_CANCEL_Y,BLACK_COLOR,1,fill_color);
			break;
	case INDONSIA:	//ӡ��
		Printf16("Apakah akan menghapus semua data",DEL_ALL_HINT_X,DEL_ALL_HINT_Y,BLACK_COLOR,0,fill_color);
		Printf24("Ya",DEL_ALL_OK_X,DEL_ALL_OK_Y,BLACK_COLOR,1,fill_color);
		Printf24("Membatal",DEL_ALL_CANCEL_X,DEL_ALL_CANCEL_Y,BLACK_COLOR,1,fill_color);
			break;
	case PORTUGAL:	//������
		Printf16("Seja para excluir todos os dados",DEL_ALL_HINT_X,DEL_ALL_HINT_Y,BLACK_COLOR,0,fill_color);
		Printf24("OK",DEL_ALL_OK_X,DEL_ALL_OK_Y,BLACK_COLOR,1,fill_color);
		Printf24("Cancelar",DEL_ALL_CANCEL_X,DEL_ALL_CANCEL_Y,BLACK_COLOR,1,fill_color);
			break;
	}
switch(WorkMode)
	{
	case READ_PRO_MODE:
			WorkMode=READ_DEL_ALL_PRO_MODE;
			break;
	case TEACH_PRO_MODE:
			// WorkMode=TEACH_DEL_ALL_PRO_MODE;
			break;
	// case PROG_MODE:
			// WorkMode=PROG_DEL_ALL_SIZE_MODE;
			// break;
	case TEACH_MODE:
			WorkMode=TEACH_DEL_ALL_SIZE_MODE;
			break;		
	case AUTO_MODE:
			WorkMode=AUTO_DEL_ALL_SIZE_MODE; 
				break;
	}	
}
void DeleteAllExitWind(void)	//�˳�ȫɾ ��ʾ��
{
CurrentArea_recover1(DEL_ALL_WIN_X,DEL_ALL_WIN_Y, DEL_ALL_WIN_WIDE,DEL_ALL_WIN_HIGH);
switch(WorkMode)
	{
	case READ_DEL_ALL_PRO_MODE:
			WorkMode=READ_PRO_MODE;
			break;
	// // case TEACH_DEL_ALL_PRO_MODE:
			// // WorkMode=TEACH_PRO_MODE;
			// // break;
	// // case PROG_DEL_ALL_SIZE_MODE:
			// // WorkMode=PROG_MODE;
			// // break;
	case TEACH_DEL_ALL_SIZE_MODE:
			WorkMode=TEACH_MODE;
			break;		
	case AUTO_DEL_ALL_SIZE_MODE:
			WorkMode=AUTO_MODE;
			break;		
	}
}

void F5_KeyExec(void)//F5  ���� 
{
if(WorkStart_flag==1)
    {
	if(Run_flag==0)
		{
		// if(ButtonTouch_mode==0)//δ��  ����ҳ
			// {
			switch(WorkMode)
				{
				
				case READ_PRO_MODE:
				// // case TEACH_PRO_MODE:	//�����б� ģʽ
						DeleteAllData_hintWind();	//ɾ����������  ��ʾ��
							break;
				case AUTO_MODE:
						WorkMode=AUTO_PLUS_MODE;  //F5++
						F5_plus_dis(1);//  ++	
							break;
				case AUTO_PLUS_MODE:  //F5++		
						WorkMode=AUTO_MODE;//����
						PaperCutEnb_signal=1;
						PressCircle_mode=0;
						F5_plus_dis(0);
							break;
				case TEACH_MODE:
						WorkMode=TEACH_PLUS_MODE;  //F5++
						F5_plus_dis(1);//  ++	
							break;
				case TEACH_PLUS_MODE:  //F5++		
						WorkMode=TEACH_MODE;//����
						PaperCutEnb_signal=1;
						PressCircle_mode=0;
						F5_plus_dis(0);
							break;
				case MANUAL_MODE:
						if(MotorType<MOTOR_AC_SERVO)    //��Ƶ��--
							{
							 WorkMode=MANUAL_PULSE_MODE;
							 PulseDegreePage_dis();
							 PromptDis_flag=0;
							 // // ClrInput_function();//���� �����
							 Para_sel=Pulse_degree;	//���嵱�� �趨
							 }
							break;
							
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
				// // case MOTOR_DC_SERVO:
				// // case MOTOR_DC670_SERVO:
					// // DCServoStop();  //ֹͣ����
					// // ServoPressStop_flag=0;
					// // DcServoGoTarget_flag=0;
					// // BellStart_flag=0;
					// // //************
					// // Run_flag=0;	
					// // InTargetPosit_flag=0;	//Ŀ��λ��
					// // AutoPushRun_flag=0; //�Զ���ֽ ����
					// // TargetSize=0;
					// // TargetSize_temp=0;
					// // BeforeKnife_offset_in=0;
					// // AutoRoute_flag=0;
						// // break;
				case MOTOR_AC_SERVO:
				case MOTOR_AC_SERVO_REV:
				case MOTOR_AC_A6_SERVO:
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
			
			// if(ButtonTouch_mode==0)
				// ClrInput_function();//���� �����	
			}		
		}
    }
else 
	{
	if(Board_TestMod==TEST_HELP)
		{
		PageLineSet_dis();  //ÿҳ���� ****************************
		Board_TestMod=TEST_PAGE_LINE;   
		}
	else if(Board_TestMod==TEST_PAGE_LINE)
		{
		StartHelpMode_dis();
		Board_TestMod=TEST_HELP;
		}
	}
}

void F6_KeyExec(void)//F6  ����
{
if(WorkStart_flag==1)
   {
	if(Run_flag==0)
		{
		// if(ButtonTouch_mode==0)//δ��  ����ҳ
			// {
			switch(WorkMode)
				{
				// case PROG_PRO_MODE:		//F3 ����ģʽ
						// WorkMode=PROG_MODE;//------------------�˳����ص������ ����
						// //PorgSet_sel=0;
						// CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
						// SubModeIcon_dis(WorkMode);   //��� ģʽname
						// if(Knife_order==1)// ----�����ѱ�ɾ��---------
							// {
							// //------------���ص�һ��
							// ClrInput_function();//���� ����� 
							// CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
							// cursor_row=0;
							// CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
							// Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
							// }
							
						// PromptNum_dis();//���뷶Χ
						// PromptDis_flag=1;
						// PaperCutEnb_signal=1;
						// ACServoAlarmExec_flag=0;
						// break;
				case TEACH_PRO_MODE:		//F3 ����ģʽ
						WorkMode=TEACH_MODE;//------------------�˳����ص�ʾ���� ����
						//PorgSet_sel=0;
						CurrentArea_recover2(MIDDLE_PAGE_X , MIDDLE_PAGE_Y,  M_PAGE_WIDE, M_PAGE_HIGH);
						SubModeIcon_dis(WorkMode);   //ģʽname
						if(Knife_order==1)// ----�����ѱ�ɾ��---------
							{
							//------------���ص�һ��
							ClrInput_function();//���� ����� 
							CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
							cursor_row=0;
							CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
							Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
							}
							
						PromptNum_dis();//���뷶Χ
						PromptDis_flag=1;
						PaperCutEnb_signal=1;
						ACServoAlarmExec_flag=0;
						break;	
				case AUTO_MODE:
						// // if(MotorType>=MOTOR_AC_SERVO)
							// // {
							// // if(ElectricWheelOn_flag==1)	//����  ��Чʱ
								// // {
								// // AmendSwitch_flag=!AmendSwitch_flag;
								// // if(AmendSwitch_flag==0)
									// // {
									// // AmendStartRun_flag=0;
									// // AmendSize=0;
									// // }
								// // AmendButtonFlag_dis();	//F6�޸�����ƫ����
								// // }
							// // }
							WorkMode=AUTO_MINUS_MODE;// F6--
							F6_minus_dis(1);//--
						break;	
				case AUTO_MINUS_MODE:// F6--		 
							WorkMode=AUTO_MODE;//����
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F6_minus_dis(0);
							break;	
				case TEACH_MODE:
							WorkMode=TEACH_MINUS_MODE;// F6--
							F6_minus_dis(1);//--
						break;	
				case TEACH_MINUS_MODE:// F6--		 
							WorkMode=TEACH_MODE;//����
							PaperCutEnb_signal=1;
							PressCircle_mode=0;
							F6_minus_dis(0);
							break;
				case MANUAL_MODE:
						Para_sel=0;
						PromptDis_flag=0;
						ACServoAlarmExec_flag=0;
						
						WorkMode=MANUAL_IO_TEST_MODE;//---------------io����ģʽ
						SubModeIcon_dis(WorkMode); //IO mode name
						F6_TestIO_dis();
						break;	
				}	
			// }
		// else if(ButtonTouch_mode==TOU_MODE_CALC)  //������ ����ģʽ
			// {
			
			// }
		// else if(ButtonTouch_mode==TOU_MODE_F4)  // ��� ������		F6  �˳���� ��ʾ
			// {
			// Set_AllFlagWind_Exit(FlagTouRow_num-1);	//�˳����  ��ʾ
			// ClrInput_function();//���� �����	
			// }
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
				// // case MOTOR_DC_SERVO:
				// // case MOTOR_DC670_SERVO:
					// // DCServoStop();  //ֹͣ����
					// // ServoPressStop_flag=0;
					// // DcServoGoTarget_flag=0;
					// // BellStart_flag=0;
					// // //************
					// // Run_flag=0;	
					// // InTargetPosit_flag=0;	//Ŀ��λ��
					// // AutoPushRun_flag=0; //�Զ���ֽ ����
					// // TargetSize=0;
					// // TargetSize_temp=0;
					// // BeforeKnife_offset_in=0;
					// // AutoRoute_flag=0;
						// // break;
				case MOTOR_AC_SERVO:
				case MOTOR_AC_SERVO_REV:
				case MOTOR_AC_A6_SERVO:
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
			
			// if(ButtonTouch_mode==0)
				// ClrInput_function();//���� �����	
			}		
		}
   }

}

void AllFlagSetExec(Int8U flag) //F4 ����趨  ����................
{
volatile Int16U first_num,last_num;
Int16U knife_begin,knife_end;
pInt8U pbuf;
Int32U offset;
Int32U size_temp,size_now,knife_temp=0;
Int8U renew_flag=0;
// // if(ButtonTouch_mode==TOU_MODE_F4)  // ��� ������
	// // Set_AllFlagWind_Exit(FlagTouRow_num-1);	//�˳���ǿ�  

pKnife_data=(pInt8U)&OneKnife_data;
if((LastKnife_num_temp!=FirstKnife_num)&&(LastKnife_num_temp>0))		//  ��������
	{
	if(LastKnife_num_temp>FirstKnife_num)
		{
		first_num=FirstKnife_num;
		last_num=LastKnife_num_temp;
		}
	else
		{
		first_num=LastKnife_num_temp;
		last_num=FirstKnife_num;
		}
		
	if(first_num<=OnePro_head.pro_knifeSUM)//��Χ��Ч
		{
		knife_begin=first_num;
		if(last_num<OnePro_head.pro_knifeSUM)
			knife_end=last_num;
		else
			knife_end=OnePro_head.pro_knifeSUM;
		if(Pro_data.pro_num<=(PROG_GROPU1+1))  //ǰ301��prog
		   {
		   offset=PROG_BYTES1*(Pro_data.pro_num-1);
		   }
		else//��  199
		   {
		   offset=PROG_BYTES1*PROG_GROPU1+(Pro_data.pro_num-PROG_GROPU1-1)*PROG_BYTES2;
		   }
		pbuf=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+(knife_begin-1)*5+4);//�������ַ
		
		GetOneKnife_datas(Pro_data.pro_num, knife_begin, pKnife_data);//
		// // if(OneKnife_data.size>0)
			// // {
			// // }
		//-----------------���жϵ�ǰ�Ƿ� ���б��
		switch(flag)
			{
			case PUSH_FLAG:		//��ֽ ��־
			case SORT_FLAG:	  // ��ֽ
			case PRESS_FLAG:    // ѹֽ
				if((OneKnife_data.k_flag&0x0f)!=flag) //�趨 ��־
					{
					while(knife_begin<=knife_end)
						{
						*pbuf&=0xf0;
						*pbuf|=flag;
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}		
					}
				else	// ��� ��־
					{
					while(knife_begin<=knife_end)
						{
						*pbuf&=0xf0;
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}
					}
					break;
			case AIR_FLAG:      //����
				if((OneKnife_data.k_flag&0xf0)!=flag) //
					{
					while(knife_begin<=knife_end)
						{
						*pbuf&=0x0f;
						*pbuf|=flag;
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}	
					}
				else
					{
					while(knife_begin<=knife_end)
						{
						*pbuf&=0x0f;
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}
					}
					break;
			case  KNIFE_FLAG:     //��  ��־
				if(knife_begin<2)	//����---- ʹ�ӵڶ��� ��ʼ
					{
					//pbuf=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+knife_begin*5+4);//�������ַ
					GetOneKnife_datas(Pro_data.pro_num, 2, pKnife_data);//  ----�ӵ�2���ж�
					}
				if((OneKnife_data.k_flag&0x0f)!=flag) //�趨 ��־
					{
					if(knife_begin<2)	//����---- ʹ�ӵڶ��� ��ʼ
						{
						 knife_begin=2;
						 pbuf=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+(knife_begin-1)*5+4);//�������ַ
						size_now=0xffffffff;
						}
					else
						{
						GetOneKnife_datas(Pro_data.pro_num, knife_begin-1, pKnife_data);//ǰ һ��
						size_now=OneKnife_data.size;
						}
					//------------
					while(knife_begin<=knife_end)
						{
						size_temp=size_now;
						GetOneKnife_datas(Pro_data.pro_num, knife_begin, pKnife_data);//��ǰ ��
						size_now=OneKnife_data.size;
						if(size_now<size_temp)//С�� ǰһ��
							{
							*pbuf&=0xf0;
							*pbuf|=flag;	//KNIFE_FLAG;
							//OneKnife_data.k_flag=KNIFE_FLAG;  
							//SaveOneKnife_datas(Pro_data.pro_num,knife , pKnife_data);//����һ������
							//*pbuf=*(pKnife_data+4);
							}
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}
					}
				else	//ȥ�� ���е� ���
					{
					//------------
					while(knife_begin<=knife_end)
						{
						GetOneKnife_datas(Pro_data.pro_num, knife_begin, pKnife_data);//��ǰ ��
						if((OneKnife_data.k_flag&0x0f)==flag) //
							{
							*pbuf&=0xf0;
							}
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}
					}
					break;
			}
		
		//****************����  ��ʾ��
		if(renew_flag==1)
			{
			RenewModifyDate();	//����ʱ����Ϣ-.-.-.-.-.-.-.-.-.-.-.-.-.-
			// SaveBuf_datas(Pro_data.pro_num, 1, OnePro_head.pro_knifeSUM );//����
			SaveBuf_datas(Pro_data.pro_num, first_num, knife_end);//����
			//------------���ص�һ��
			//ClrInput_function();//���� ����� 
			CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
			cursor_row=0;
			CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
			Knife_order=1;//
			Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
			if(Knife_order<=OnePro_head.pro_knifeSUM)
				StepOrder_dis(Knife_order);//�������	
			// if((WorkMode==PROG_FLAG_MODE)||(WorkMode==TEACH_FLAG_MODE))//��� ģʽ
				// AllFlagRemind();	//F4 ���ģʽ��ʾ	
			}
		}
	}
else//���� ���	+====��ǰ��괦
	{
	if(SubLine_flag==0)
		{
		if(num_cou>0)
			{
			if(CheckInputNums()==1)// ���� ��Ч	
				knife_temp=InputSize;  //�ߴ��޸�
			num_cou=0;
			}
		}
	
	GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);
	if(knife_temp>0)
		{
		OneKnife_data.size=knife_temp;
		renew_flag=1;
		}
	if(OneKnife_data.size>0)
		{
		switch(flag)
			{
			case PUSH_FLAG:		//��ֽ ��־
			case SORT_FLAG:	  // ��ֽ
			case PRESS_FLAG:    // ѹֽ
				if((OneKnife_data.k_flag&0x0f)!=flag) //
					{
					OneKnife_data.k_flag&=0xf0;
					OneKnife_data.k_flag|=flag;//  �趨 ��־
					}
				else
					{
					OneKnife_data.k_flag&=0xf0;// ��� ��־
					}
				renew_flag=1;
					break;
			case AIR_FLAG:      //����
				if((OneKnife_data.k_flag&0xf0)!=flag) //
					{
					OneKnife_data.k_flag&=0x0f;
					OneKnife_data.k_flag|=flag;//  �趨 ��־
					}
				else
					{
					OneKnife_data.k_flag&=0x0f;// ��� ��־
					}
				renew_flag=1;
					break;
			case  KNIFE_FLAG:     //��  ��־	
				if(Knife_order>1)
					{
					GetOneKnife_datas(Pro_data.pro_num, Knife_order-1, pKnife_data);//ǰ һ��
					size_temp=OneKnife_data.size;
					GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);//��ǰ �ߴ�
					if(knife_temp>0)
						{
						OneKnife_data.size=knife_temp;
						renew_flag=1;
						}
					if(OneKnife_data.size<size_temp)
						{
						if((OneKnife_data.k_flag&0x0f)!=flag) //
							{
							OneKnife_data.k_flag&=0xf0;
							OneKnife_data.k_flag|=flag;//  �趨 ��־
							}
						else
							{
							OneKnife_data.k_flag&=0xf0;// ��� ��־
							}
						renew_flag=1;
						}
					}
					break;
			}
		if(renew_flag==1)
			{
			RenewModifyDate();	//����ʱ����Ϣ-.-.-.-.-.-.-.-.-.-.-.-.-.-
			AllFlagPic_dis(cursor_row,OneKnife_data.k_flag); //��ʾ----
			if(knife_temp>0)
				{
				if(Knife_order>OnePro_head.pro_knifeSUM)//���²��� �ܵ���
					{
					OnePro_head.pro_knifeSUM=Knife_order;		//
					//SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);
					}
				KnifeSize_dis(cursor_row, knife_temp, RED_COLOR);//-------------- ������ʾһ���ߴ�
				}
			SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//����һ������
			// OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //һ������ ������ʾ
			// PromptNum_dis();//���뷶Χ
			// PromptDis_flag=1;
			
			//---------��ʾ----	
			if(Knife_order<MAX_Knife)	//������ δ��---------------����
				{
				Knife_order++;
				if(cursor_row<(PageKf_Size-1))
					{
					CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
					OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //һ������ ������ʧ
					cursor_row++;
					CursorKnife_dis(cursor_row, 1);//��ɫ���������ʾ
					OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //һ������ ������ʾ
					}
				else   //ҳ��
					{
					Size_1page_dis(Knife_order-(PageKf_Size-1),0);//һҳ�ߴ���ʾ
					}
				}
			StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//�������
			
			// if((WorkMode==PROG_FLAG_MODE)||(WorkMode==TEACH_FLAG_MODE))//��� ģʽ
				// AllFlagRemind();	//F4 ���ģʽ��ʾ
			}
		}
	}
// // ClrInput_function();//���� �����	
LastKnife_num_temp=FirstKnife_num=0;
}

void AllKnifeFlagExec(Int8U dis)	//��ӣ���� --���е����
{
Int16U knife;
pInt8U pbuf;
Int32U offset,size_temp;
Int8U chg_flag=0;
//-----------
pKnife_data=(pInt8U)&OneKnife_data;
if(dis==1)//��� �����
	{
	if(OnePro_head.pro_knifeSUM>1)
		{
		knife=2;
		if(Pro_data.pro_num<=(PROG_GROPU1+1))  //ǰ301��prog
		   {
		   offset=PROG_BYTES1*(Pro_data.pro_num-1);
		   }
		else//��  199
		   {
		   offset=PROG_BYTES1*PROG_GROPU1+(Pro_data.pro_num-PROG_GROPU1-1)*PROG_BYTES2;
		   }
		pbuf=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+(knife-1)*5+4);//�������ַ
		//***********
		GetOneKnife_datas(Pro_data.pro_num, knife-1, pKnife_data);//ǰ 1��
		while(knife<=OnePro_head.pro_knifeSUM)
			{
			size_temp=OneKnife_data.size;
			GetOneKnife_datas(Pro_data.pro_num, knife, pKnife_data);//��ǰ ��
			if(OneKnife_data.size<size_temp)
				{
				*pbuf&=0xf0;
				*pbuf|=KNIFE_FLAG;     //��  ��־
				chg_flag=1;
				}
			pbuf+=5;	
			knife++;
			}
		}
	}
else	//��� �����
	{
	knife=1;
	if(Pro_data.pro_num<=(PROG_GROPU1+1))  //ǰ301��prog
	   {
	   offset=PROG_BYTES1*(Pro_data.pro_num-1);
	   }
	else//��  199
	   {
	   offset=PROG_BYTES1*PROG_GROPU1+(Pro_data.pro_num-PROG_GROPU1-1)*PROG_BYTES2;
	   }
	pbuf=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+(knife-1)*5+4);//�������ַ
	//**************
	while(knife<=OnePro_head.pro_knifeSUM)
		{
		GetOneKnife_datas(Pro_data.pro_num, knife, pKnife_data);//��ǰ ��
		if((OneKnife_data.k_flag&0x0f)==KNIFE_FLAG)   //��  ��־
			{
			*pbuf&=0xf0;
			chg_flag=1;
			}
		pbuf+=5;	
		knife++;	
		}
	}
if(chg_flag==1)
	{
	chg_flag=0;
	RenewModifyDate();	//����ʱ����Ϣ-.-.-.-.-.-.-.-.-.-.-.-.-.-
	//****************����  ��ʾ��
	SaveBuf_datas(Pro_data.pro_num, 1, OnePro_head.pro_knifeSUM );//����
	//------------���ص�һ�� 
	CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
	cursor_row=0;
	CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
	Knife_order=1;//
	Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
	if(Knife_order<=OnePro_head.pro_knifeSUM)
		StepOrder_dis(Knife_order);//�������	
	// AllFlagRemind();	//F4 ���ģʽ��ʾ
	}
}


void ProMessageModify_mode(Int16U p_order)	//������Ϣ�޸� ģʽ
{
Int16U x1,y1,x2,y2,gap_x=40,gap_y=180;
Int16U line_color,fill_color;
Int8U nums[45],n=0,check=0;
pInt8U pName;

InputMode=PINYIN_INPUT;
SubModeIcon_dis(WorkMode);   //���뷨 ģʽ
//------------
CurrentArea_save1(PRO_MESS_X,PRO_MESS_Y, PRO_MESS_WIDE,PRO_MESS_HIGH);
//-----------��ҳ
line_color=fill_color=PRO_MESS_COLOR1;
x1=PRO_MESS_X,y1=PRO_MESS_Y;
x2=x1+(PRO_MESS_WIDE/2),y2=y1+PRO_MESS_HIGH-1;
GLCD_SetWindow_Fill(x1, y1, x2, y2, line_color, fill_color);
//-----------��ҳ
line_color=fill_color=PRO_MESS_COLOR2;
x1=x2;
x2=PRO_MESS_X+PRO_MESS_WIDE-1;
GLCD_SetWindow_Fill(x1, y1, x2, y2, line_color, fill_color);
//------------���
x2=x1;
line_color=0;
GLCD_DrawLine(x1, y1+30, x2, y2-30, line_color);
//-------------���
line_color=BLUE_COLOR;
x1=PRO_MESS_X,y1=PRO_MESS_Y;
x2=x1+PRO_MESS_WIDE-1,y2=y1+PRO_MESS_HIGH-1;
GLCD_SetWindow(x1,y1,x2,y2,line_color);
GetPro_headInfo(ProNumGroup[p_order],  (pInt8U)&Pro_head_temp);//sdram ��һ������ͷ(������+ ʱ�� +���� )
	//****************************************
// InputMode=CHAR_INPUT;
InputStus_dis(InputMode);	//���뷨  ѡ��
ClrNameWindow();
//-----------TOUCH KEY
for(n=0;n<=24;n++)
	{
	InputKEY_BUTT_dis(n, 0); //���� ��ť ��ʾ
	}

//---------------------------��ʾ���������-----------
GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
switch(Language)
	{
	case CHN_HAN:
		Printf24("��������,���ĳ�����",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
		break;
	case ENGLISH:	
		Printf24("Modify the program name",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
		break;
	case INDONSIA:	//ӡ��
		Printf24("Memodifikasi nama program",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
		break;
	case PORTUGAL:	//������
		Printf24("Digite o texto, muda o nome",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,BLACK_COLOR,0,0xffff);
		break;
	}
}




void PageKf_Size_Init(void)	//ÿҳ ������ʼ��
{
ReadPageKf_Size();
switch(PageKf_Size_flag)
	{
	case PAGE_5_LINE: //5 line 
			PageKf_Size=5;
			Kf_Line_HIGH=60;//75//�и�
			break;
	case PAGE_7_LINE: //5 line 
			PageKf_Size=7;
			Kf_Line_HIGH=40;//45;//�и�
			break;
	}
}


void AllFlagSetExec_Calc(Int8U flag) //������ ����趨  ����................
{
volatile Int16U first_num,last_num;
Int16U knife_begin,knife_end;
pInt8U pbuf;
Int32U offset;
Int32U size_temp,size_now,knife_temp=0;
Int8U renew_flag=0;


pKnife_data=(pInt8U)&OneKnife_data;
if((LastKnife_num_temp!=FirstKnife_num)&&(LastKnife_num_temp>0))		//  ��������
	{
	if(LastKnife_num_temp>FirstKnife_num)
		{
		first_num=FirstKnife_num;
		last_num=LastKnife_num_temp;
		}
	else
		{
		first_num=LastKnife_num_temp;
		last_num=FirstKnife_num;
		}
		
	if(first_num<=OnePro_head.pro_knifeSUM)//��Χ��Ч
		{
		knife_begin=first_num;
		if(last_num<OnePro_head.pro_knifeSUM)
			knife_end=last_num;
		else
			knife_end=OnePro_head.pro_knifeSUM;
		if(Pro_data.pro_num<=(PROG_GROPU1+1))  //ǰ301��prog
		   {
		   offset=PROG_BYTES1*(Pro_data.pro_num-1);
		   }
		else//��  199
		   {
		   offset=PROG_BYTES1*PROG_GROPU1+(Pro_data.pro_num-PROG_GROPU1-1)*PROG_BYTES2;
		   }
		pbuf=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+(knife_begin-1)*5+4);//�������ַ
		
		GetOneKnife_datas(Pro_data.pro_num, knife_begin, pKnife_data);//
		// // if(OneKnife_data.size>0)
			// // {
			// // }
		//-----------------���жϵ�ǰ�Ƿ� ���б��
		switch(flag)
			{
			case PUSH_FLAG:		//��ֽ ��־
			case SORT_FLAG:	  // ��ֽ
			case PRESS_FLAG:    // ѹֽ
				if((OneKnife_data.k_flag&0x0f)!=flag) //�趨 ��־
					{
					while(knife_begin<=knife_end)
						{
						*pbuf&=0xf0;
						*pbuf|=flag;
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}		
					}
				else	// ��� ��־
					{
					while(knife_begin<=knife_end)
						{
						*pbuf&=0xf0;
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}
					}
					break;
			case AIR_FLAG:      //����
				if((OneKnife_data.k_flag&0xf0)!=flag) //
					{
					while(knife_begin<=knife_end)
						{
						*pbuf&=0x0f;
						*pbuf|=flag;
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}	
					}
				else
					{
					while(knife_begin<=knife_end)
						{
						*pbuf&=0x0f;
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}
					}
					break;
			case  KNIFE_FLAG:     //��  ��־
				if(knife_begin<2)	//����---- ʹ�ӵڶ��� ��ʼ
					{
					//pbuf=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+knife_begin*5+4);//�������ַ
					GetOneKnife_datas(Pro_data.pro_num, 2, pKnife_data);//  ----�ӵ�2���ж�
					}
				if((OneKnife_data.k_flag&0x0f)!=flag) //�趨 ��־
					{
					if(knife_begin<2)	//����---- ʹ�ӵڶ��� ��ʼ
						{
						 knife_begin=2;
						 pbuf=(pInt8U)(K_SIZE_sdram+offset+PRO_HEAD_BYTES+(knife_begin-1)*5+4);//�������ַ
						size_now=0xffffffff;
						}
					else
						{
						GetOneKnife_datas(Pro_data.pro_num, knife_begin-1, pKnife_data);//ǰ һ��
						size_now=OneKnife_data.size;
						}
					//------------
					while(knife_begin<=knife_end)
						{
						size_temp=size_now;
						GetOneKnife_datas(Pro_data.pro_num, knife_begin, pKnife_data);//��ǰ ��
						size_now=OneKnife_data.size;
						if(size_now<size_temp)//С�� ǰһ��
							{
							*pbuf&=0xf0;
							*pbuf|=flag;	//KNIFE_FLAG;
							//OneKnife_data.k_flag=KNIFE_FLAG;  
							//SaveOneKnife_datas(Pro_data.pro_num,knife , pKnife_data);//����һ������
							//*pbuf=*(pKnife_data+4);
							}
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}
					}
				else	//ȥ�� ���е� ���
					{
					//------------
					while(knife_begin<=knife_end)
						{
						GetOneKnife_datas(Pro_data.pro_num, knife_begin, pKnife_data);//��ǰ ��
						if((OneKnife_data.k_flag&0x0f)==flag) //
							{
							*pbuf&=0xf0;
							}
						pbuf+=5;
						knife_begin++;
						renew_flag=1;
						}
					}
					break;
			}
		
		//****************����  ��ʾ��
		if(renew_flag==1)
			{
			RenewModifyDate();	//����ʱ����Ϣ-.-.-.-.-.-.-.-.-.-.-.-.-.-
			// SaveBuf_datas(Pro_data.pro_num, 1, OnePro_head.pro_knifeSUM );//����
			SaveBuf_datas(Pro_data.pro_num, first_num, knife_end);//����
			//------------���ص�һ��
			//ClrInput_function();//���� ����� 
			CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
			cursor_row=0;
			CursorKnife_dis(cursor_row, 1);//��ɫ�����ʾ
			Knife_order=1;//
			Size_1page_dis(Knife_order,0);//һҳ�ߴ���ʾ
			if(Knife_order<=OnePro_head.pro_knifeSUM)
				StepOrder_dis(Knife_order);//�������	
			// if((WorkMode==PROG_FLAG_MODE)||(WorkMode==TEACH_FLAG_MODE))//��� ģʽ
			// AllFlagRemind();	//F4 ���ģʽ��ʾ	
			}
		}
	}
else//���� ���	+====��ǰ��괦
	{
	if(SubLine_flag==0)
		{
		if(num_cou>0)
			{
			if(CheckInputNums()==1)// ���� ��Ч	
				knife_temp=InputSize;  //�ߴ��޸�
			num_cou=0;
			}
		}
		
	//--------������ ��ʧ--
	// CalcuInClear_exec();     //��� ������	180917
	
	GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);
	if(knife_temp>0)
		{
		OneKnife_data.size=knife_temp;
		renew_flag=1;
		}
	if(OneKnife_data.size>0)
		{
		switch(flag)
			{
			case PUSH_FLAG:		//��ֽ ��־
			case SORT_FLAG:	  // ��ֽ
			case PRESS_FLAG:    // ѹֽ
				if((OneKnife_data.k_flag&0x0f)!=flag) //
					{
					OneKnife_data.k_flag&=0xf0;
					OneKnife_data.k_flag|=flag;//  �趨 ��־
					}
				else
					{
					OneKnife_data.k_flag&=0xf0;// ��� ��־
					}
				renew_flag=1;
					break;
			case AIR_FLAG:      //����
				if((OneKnife_data.k_flag&0xf0)!=flag) //
					{
					OneKnife_data.k_flag&=0x0f;
					OneKnife_data.k_flag|=flag;//  �趨 ��־
					}
				else
					{
					OneKnife_data.k_flag&=0x0f;// ��� ��־
					}
				renew_flag=1;
					break;
			case  KNIFE_FLAG:     //��  ��־	
				if(Knife_order>1)
					{
					GetOneKnife_datas(Pro_data.pro_num, Knife_order-1, pKnife_data);//ǰ һ��
					size_temp=OneKnife_data.size;
					GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKnife_data);//��ǰ �ߴ�
					if(knife_temp>0)
						{
						OneKnife_data.size=knife_temp;
						renew_flag=1;
						}
					if(OneKnife_data.size<size_temp)
						{
						if((OneKnife_data.k_flag&0x0f)!=flag) //
							{
							OneKnife_data.k_flag&=0xf0;
							OneKnife_data.k_flag|=flag;//  �趨 ��־
							}
						else
							{
							OneKnife_data.k_flag&=0xf0;// ��� ��־
							}
						renew_flag=1;
						}
					}
					break;
			}
		if(renew_flag==1)
			{
			RenewModifyDate();	//����ʱ����Ϣ-.-.-.-.-.-.-.-.-.-.-.-.-.-
			AllFlagPic_dis(cursor_row,OneKnife_data.k_flag); //��ʾ----
			if(knife_temp>0)
				{
				if(Knife_order>OnePro_head.pro_knifeSUM)//���²��� �ܵ���
					{
					OnePro_head.pro_knifeSUM=Knife_order;		//
					//SavePro_headInfo(Pro_data.pro_num, (pInt8U)&OnePro_head);
					}
				KnifeSize_dis(cursor_row, knife_temp, RED_COLOR);//-------------- ������ʾһ���ߴ�
				}
			SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKnife_data);//����һ������
			// OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //һ������ ������ʾ
			// PromptNum_dis();//���뷶Χ
			// PromptDis_flag=1;
			
			//---------��ʾ----	
			if(Knife_order<MAX_Knife)	//������ δ��---------------����
				{
				Knife_order++;
				if(cursor_row<(PageKf_Size-1))
					{
					CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
					OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //һ������ ������ʧ
					cursor_row++;
					CursorKnife_dis(cursor_row, 1);//��ɫ���������ʾ
					OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //һ������ ������ʾ
					}
				else   //ҳ��
					{
					Size_1page_dis(Knife_order-(PageKf_Size-1),0);//һҳ�ߴ���ʾ
					}
				}
			StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//�������
			
			// if((WorkMode==PROG_FLAG_MODE)||(WorkMode==TEACH_FLAG_MODE))//��� ģʽ
				// AllFlagRemind();	//F4 ���ģʽ��ʾ
			}
		}
	}
// // ClrInput_function();//���� �����	
LastKnife_num_temp=FirstKnife_num=0;
}

