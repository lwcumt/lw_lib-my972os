

#include"servo.h"

#include"port.h"
#include"pic_exec.h"
#include"m25pe16.h"
#include"key.h"
#include "io.h"
#include"chndot.h"

//unsigned int const SERVO_SPEED[]={0,0,0,0,0,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1800,1800,1800};
unsigned int const SERVO_SPEED[]={0,0,0,0,0,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000};


//Int8U ServoCommData_Tx[15];
Int8U ServoCommData_Rx[15];


Int8U ServoRx_Cou;
Int8U ServoComm_Mod;


SERVO_CTRL ServoCtrlData;  //������������

Int8U ReturnCommd; //��������
//-----T ����
Int8U Shield_Limit;
Int8U Status_Limit;
Int8U Status_Z;
Int8U Alarm_Error[2];
Int8U PositionBCD[6];
//------F ����
Int8U SpeedRatio;
Int8U SearchZero_flag;
Int8U CurrencyBCD[2];
Int8U SpeedBCD[4];
Int16U SpeedServo;
//------C ����
Int8U Status_IR;
Int8U Wheel_Commd_Active;
Int8U PositRing_GainBCD[2];
Int8U PositRing_Gain;
Int8U PositRing_DiffBCD[2];
Int8U PositRing_Diff;
Int8U PositRing_IntegralBCD[2];
Int8U PositRing_Integral;
//------D ����
Int8U SpeedRing_GainBCD[2];
Int8U SpeedRing_Gain;
Int8U SpeedRing_DiffBCD[2];
Int8U SpeedRing_Diff;
Int8U SpeedRing_IntegralBCD[2];
Int8U SpeedRing_Integral;

//******
Int8U checksum;
Int8U ServoRecvOk_flag;
Int8U ServoConnect_flag;
Int16U ServoLink_Time;

//------
Int8U ServoSpeed_order;
Int8U JogSpeed_order;
Int8U SpeedDown_Ratio;
Int8U Screw_Pitch;


Int8U ServoDrvInit_flag;
Int8U ServoDrvInitOK_flag;
Int8U ServoDisconnect_flag;

Int8U ServoMoving_flag;

Int8U OriginalReset_flag;
Int16U ServoInitTime;
Int16U ServoNow_Speed;
Int16U ServoStartDelayTime;
Int8U ServoSendCou;
Int32U NowSize_last;
Int8U ChangeTarget_flag;
Int8U ServoBack_flag;

Int8U ServoAutoPushFinish_flag;


void DelayTime(Int32U time)
{
while(time--);
}


void ReadMovSpeed(void)
{
Int32U add;
add=ORIGINAL_25PEADD+56;
FastRead_Datas_Start(add);
ServoSpeed_order=ReadFlash_Datas();
FlashChip_Dis;
if(ServoSpeed_order>20)
	ServoSpeed_order=0;  //Ĭ������ �ٶ�
}
void SaveMovSpeed(void)
{
pInt8U pdata;
Int32U add;
pdata=(pInt8U)&ServoSpeed_order;
add=ORIGINAL_25PEADD+56;
Write_25pe_data(pdata, add, 1);
}

void ReadJogSpeed(void)
{
Int32U add;
add=ORIGINAL_25PEADD+57;
FastRead_Datas_Start(add);
JogSpeed_order=ReadFlash_Datas();
FlashChip_Dis;
if(JogSpeed_order>20)
	JogSpeed_order=0;  //Ĭ��jog �ٶ�
}
void SaveJogSpeed(void)
{
pInt8U pdata;
Int32U add;
pdata=(pInt8U)&JogSpeed_order;
add=ORIGINAL_25PEADD+57;
Write_25pe_data(pdata, add, 1);
}

void Read_PitchRatio(void)
{
Int32U add;
add=ORIGINAL_25PEADD+58;
FastRead_Datas_Start(add);
Screw_Pitch=ReadFlash_Datas();
SpeedDown_Ratio=ReadFlash_Datas();
FlashChip_Dis;
if(((Screw_Pitch!=10)&&(Screw_Pitch!=12))||((SpeedDown_Ratio>3)||(SpeedDown_Ratio<1)))
	{
	Screw_Pitch=10;
	SpeedDown_Ratio=3;
	}
}
void Save_PitchRatio(void)
{
pInt8U pdata;
Int32U add;
pdata=(pInt8U)&Screw_Pitch;

add=ORIGINAL_25PEADD+58;
Write_25pe_data(pdata, add, 1);
pdata=(pInt8U)&SpeedDown_Ratio;
add++;
Write_25pe_data(pdata, add, 1);
}
//--------------------------------------

Int32U MotorPositionToHex(void)
{
volatile Int32U posit,t;
for(t=0;t<6;t++)
	PositionBCD[t]=ServoCommData_Rx[5+t];
t=0;					
posit=(PositionBCD[t++]-48)*100000;
posit+=(PositionBCD[t++]-48)*10000;
posit+=(PositionBCD[t++]-48)*1000;
posit+=(PositionBCD[t++]-48)*100;
posit+=(PositionBCD[t++]-48)*10;
posit+=(PositionBCD[t++]-48);
return posit;
}

Int32U ServoSpeedData(void)
{
volatile Int32U spd,t;
for(t=0;t<4;t++)
	SpeedBCD[t]=ServoCommData_Rx[7+t];
t=0;
spd=(SpeedBCD[t++]-48)*1000;
spd+=(SpeedBCD[t++]-48)*100;
spd+=(SpeedBCD[t++]-48)*10;
spd+=(SpeedBCD[t++]-48);
return spd;
}

void ServoPositionRing(void)  //λ�û� ����
{
PositRing_GainBCD[0]=ServoCommData_Rx[4]-48;
PositRing_GainBCD[1]=ServoCommData_Rx[5]-48;
PositRing_DiffBCD[0]=ServoCommData_Rx[6]-48;
PositRing_DiffBCD[1]=ServoCommData_Rx[7]-48;
PositRing_IntegralBCD[0]=ServoCommData_Rx[8]-48;
PositRing_IntegralBCD[1]=ServoCommData_Rx[9]-48;
PositRing_Gain=PositRing_GainBCD[0]*10+PositRing_GainBCD[1]; //����
PositRing_Diff=PositRing_DiffBCD[0]*10+PositRing_DiffBCD[1];  //΢��
PositRing_Integral=PositRing_IntegralBCD[0]*10+PositRing_IntegralBCD[1];//����
}

void ServoSpeedRing(void)//�ٶȻ� ����
{
SpeedRing_GainBCD[0]=ServoCommData_Rx[4]-48;
SpeedRing_GainBCD[1]=ServoCommData_Rx[5]-48;
SpeedRing_DiffBCD[0]=ServoCommData_Rx[6]-48;
SpeedRing_DiffBCD[1]=ServoCommData_Rx[7]-48;
SpeedRing_IntegralBCD[0]=ServoCommData_Rx[8]-48;
SpeedRing_IntegralBCD[1]=ServoCommData_Rx[9]-48;
SpeedRing_Gain=SpeedRing_GainBCD[0]*10+SpeedRing_GainBCD[1]; //����
SpeedRing_Diff=SpeedRing_DiffBCD[0]*10+SpeedRing_DiffBCD[1]; //΢��
SpeedRing_Integral=SpeedRing_IntegralBCD[0]*10+SpeedRing_IntegralBCD[1];
}


//-----------------------------------


void ServoComm_exec(Int8U data) //�ŷ����ݽ���
{
Int8U byte;
byte=data;
Int8U checksum,n;

if(ServoRecvOk_flag==0)
	{
	switch(ServoComm_Mod)
		{
		case 0://head
			if(byte==SERVO_COMMD_HEAD)
				{
				ServoRx_Cou=0;
				ServoCommData_Rx[ServoRx_Cou++]=byte;
				ServoComm_Mod++;
				}
				break;
		case 1:
			ServoCommData_Rx[ServoRx_Cou++]=byte;
			if(ServoRx_Cou>=SERVO_COMM_LENGTH)//һ֡����
				{
				checksum=0;
				for(n=0;n<SERVO_COMM_LENGTH-1;n++)
					checksum^=ServoCommData_Rx[n];
				if(checksum==byte) //У����ȷ
					{
					ServoRecvOk_flag=1;
					ReturnCommd=ServoCommData_Rx[1];
					
					}
				ServoComm_Mod=0;
				}
				break;
		}
	}
}

void ServoRev_Exec(void)
{
volatile Int8U n;
if(ServoRecvOk_flag==1)
	{
	ServoRecvOk_flag=0;	
	ServoConnect_flag=1;
	ServoLink_Time=0;
	switch(ReturnCommd)//�������� ����
		{
		case 'T':		//============T���ݸ�ʽ����%Txyz080000X��
			if(ServoCommData_Rx[3]<'L')//�Ǿ���
				{
				Alarm_Error[0]=0;
				Alarm_Error[1]=0;
				Shield_Limit=ServoCommData_Rx[2];
				Status_Limit=ServoCommData_Rx[3];
				Status_Z=ServoCommData_Rx[4];
				
				if(WorkStart_flag==1)
					CurrentSize=MotorPositionToHex();	//�õ�� λ��
				switch(Shield_Limit)//  �г̿�������״̬ 
					{
					case '0':
						break;
					}
				switch(Status_Limit)  //�г̿���״̬ (���ޡ��м��ޡ�ǰ����)
					{
					case '0'://
						FrontLimit_IN=0;
						MiddleLimit_IN=0;
						BackLimit_IN=0;
						break;
					case '1'://
						FrontLimit_IN=1;
						MiddleLimit_IN=0;
						BackLimit_IN=0;
						break;	
					case '2'://
						FrontLimit_IN=0;
						MiddleLimit_IN=1;
						BackLimit_IN=0;
						break;
					case '3'://
						FrontLimit_IN=1;
						MiddleLimit_IN=1;
						BackLimit_IN=0;
						break;
					case '4'://
						FrontLimit_IN=0;
						MiddleLimit_IN=0;
						BackLimit_IN=1;
						break;
					case '5'://
						FrontLimit_IN=1;
						MiddleLimit_IN=0;
						BackLimit_IN=1;
						break;	
					case '6'://
						FrontLimit_IN=0;
						MiddleLimit_IN=1;
						BackLimit_IN=1;
						break;
					case '7'://
						FrontLimit_IN=1;
						MiddleLimit_IN=1;
						BackLimit_IN=1;
						break;
					}
				switch(Status_Z)  //(�а塢�е���ѹֽ)
					{
					case '0':
						PressPaper_IN=0;
						if(MotorType!=MOTOR_DC670_SERVO_ZHU)
							CutPaper_IN2=0;
						Carrier_IN=0;
						break;
					case '1':
						PressPaper_IN=1;
						if(MotorType!=MOTOR_DC670_SERVO_ZHU)
							CutPaper_IN2=0;
						Carrier_IN=0;
						break;	
					case '2':
						PressPaper_IN=0;
						if(MotorType!=MOTOR_DC670_SERVO_ZHU)
							CutPaper_IN2=1;
						Carrier_IN=0;
						break;
					case '3':
						PressPaper_IN=1;
						if(MotorType!=MOTOR_DC670_SERVO_ZHU)
							CutPaper_IN2=1;
						Carrier_IN=0;
						break;	
					case '4':
						PressPaper_IN=0;
						if(MotorType!=MOTOR_DC670_SERVO_ZHU)
							CutPaper_IN2=0;
						Carrier_IN=1;
						break;
					case '5':
						PressPaper_IN=1;
						if(MotorType!=MOTOR_DC670_SERVO_ZHU)
							CutPaper_IN2=0;
						Carrier_IN=1;
						break;	
					case '6':
						PressPaper_IN=0;
						if(MotorType!=MOTOR_DC670_SERVO_ZHU)
							CutPaper_IN2=1;
						Carrier_IN=1;
						break;
					case '7':
						PressPaper_IN=1;
						if(MotorType!=MOTOR_DC670_SERVO_ZHU)
							CutPaper_IN2=1;
						Carrier_IN=1;
						break;		
					}
				}
			else  //����
				{
				Alarm_Error[0]=ServoCommData_Rx[3];
				Alarm_Error[1]=ServoCommData_Rx[4];
				}
			break;
		case 'F':    //============F���ݸ�ʽ����%FABii+xxxxX��
			SpeedRatio=ServoCommData_Rx[2];
			switch(ServoCommData_Rx[3])
				{
				case 'N':  //δ��ԭ��
					SearchZero_flag=0;
					ServoMoving_flag=0;
					break;
				case 'D':  //ԭ��
					SearchZero_flag=1;
					ServoMoving_flag=0;
					break;
				case 'R':	//������
					SearchZero_flag=0;
					ServoMoving_flag=1;  //motor running
					break;
				}
			CurrencyBCD[0]=ServoCommData_Rx[4];
			CurrencyBCD[1]=ServoCommData_Rx[5];
			SpeedServo=ServoSpeedData();   //��� �ŷ��ٶ�
			
			break;
		case 'C':		//============C--��%C7X262645XP��λ�û�
			Status_IR=ServoCommData_Rx[2];
			Wheel_Commd_Active=ServoCommData_Rx[3];
			ServoPositionRing(); //λ�û� ����
			
			switch(Status_IR)
				{
				case '2':
				case '3':
					IRsensor_IN=0; //���� ��
					break;
				case '6':
				case '7':
					IRsensor_IN=1; //���� ��
					break;	
				}
			switch(Wheel_Commd_Active)
				{
				case 'X':  //ͨѶ����
					HandWheel_IN=1;
					break;
				case 'S':	//���ֶ���
					HandWheel_IN=0;
					break;
				}
			break;
		case 'D':		//============D--��%D7X262645XP���ٶȻ�
			Status_IR=ServoCommData_Rx[2];
			Wheel_Commd_Active=ServoCommData_Rx[3];
			ServoSpeedRing();//�ٶȻ� ����
			
			switch(Status_IR)
				{
				case '2':
				case '3':
					IRsensor_IN=0; //���� ��
					break;
				case '6':
				case '7':
					IRsensor_IN=1; //���� ��
					break;	
				}
				/*
			switch(Wheel_Commd_Active)
				{
				case 'X':  //ͨѶ����
					HandWheel_IN=1;
					break;
				case 'S':	//���ֶ���
					HandWheel_IN=0;
					break;
				}
				*/
			break;	
		}
	
	if(ServoDisconnect_flag==1)
		{
		CurrentArea_recover2(REMIND_WINDOW_X, REMIND_WINDOW_Y,    START_PROM_WIDE, START_PROM_HIGH);  //�� �������Ͽ�   ��ʾ
		ServoDisconnect_flag=0;
		}
	}
else
	{
	ServoLink_Time++;
	if(ServoLink_Time>2000)  //���ӳ�ʱ
		{
		ServoDrvInit_flag=0;
		ServoConnect_flag=0;
		ServoDrvInitOK_flag=0;
		}
	}
}

void ServoSetCommd(Int8U commd,pInt8U stu,Int32U data)
{
volatile Int8U n,check;
pInt8U pdata;
//while(ServoRecvOk_flag==1);
ServoCtrlData.head=SERVO_COMMD_HEAD;
ServoCtrlData.commd=commd;
ServoCtrlData.stus[0]=*stu++;
ServoCtrlData.stus[1]=*stu;
n=0;
ServoCtrlData.data[n++]=(data/100000)+48;
ServoCtrlData.data[n++]=((data/10000)%10)+48;
ServoCtrlData.data[n++]=((data/1000)%10)+48;
ServoCtrlData.data[n++]=((data/100)%10)+48;
ServoCtrlData.data[n++]=((data/10)%10)+48;
ServoCtrlData.data[n++]=(data%10)+48;
check=0;
pdata=(pInt8U)&ServoCtrlData;
for(n=0;n<10;n++)
	check^=*(pdata+n);
ServoCtrlData.check=check;
ServoCtrlData.end=SERVO_COMMD_END;
ServoCtrlData.end_mark='\0';  //������
//--��������
UART0_SendStr(pdata);
}

void ServoSetScrew(Int8U pitch,Int8U ratio)  //�ݾ��趨
{
switch(pitch)//�ݾ�
	{
	case 10:
		switch(ratio) //���ٱ�
			{
			case 1:
				ServoSetCommd('Z',STAT_30H,1400);
				break;
			case 2:
				ServoSetCommd('Z',STAT_30H,1000);
				break;
			case 3:
				ServoSetCommd('Z',STAT_30H,1200);  //----------Ĭ��ֵ
				break;	
			}
			break;
	case 12:
		switch(ratio) //���ٱ�
			{
			case 1:
				ServoSetCommd('Z',STAT_30H,1500);
				break;
			case 2:
				ServoSetCommd('Z',STAT_30H,1100);
				break;
			case 3:
				ServoSetCommd('Z',STAT_30H,1300);
				break;	
			}
			break;		
	}
}

void ServoDrvSet_Init(void)//������ ��ʼ��
{
volatile Int32U d;
if(ServoConnect_flag==1)
	{
	if(ServoDrvInit_flag==0)
		{
		ServoDrvInit_flag=1;
		ServoDrvInitOK_flag=0;
		ServoNow_Speed=SERVO_SPEED[ServoSpeed_order];
		ServoSetCommd('S',STAT_30H,ServoNow_Speed);
		d=2000000;
		while(d--);
		ServoInitTime=0;
		ServoSetScrew(Screw_Pitch ,SpeedDown_Ratio);  //�ݾ��趨
		
		}
	else  //----------������ ��ʼ����
		{
		if(ServoDrvInitOK_flag==0)
			{
			ServoInitTime++;
			if(ServoInitTime>=1000)
				{
				ServoDrvInitOK_flag=1;
				}
			}
		}
	}
else    //������δ����
	{
	if(ServoDisconnect_flag==0)
		{
		GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X-1+600, REMIND_WINDOW_Y-1+30, 0xfffff, 0xffff);//��ʾ
		switch(Language)
			{
			case CHN_HAN:
					Printf24("������δ����!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
					break;
			case ENGLISH:
					Printf24("The driver is off!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
					break;
			case PORTUGAL:	//������
					Printf24("A unidade n?o est��conectado",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
					ASCII_Printf("a",ASCII24_MODE,12,24,PUTAO_ZK24,REMIND_WINDOW_X+12*11,REMIND_WINDOW_Y+5,RED_COLOR,0xffff);
					break;
			}
		ServoDisconnect_flag=1;
		}
	}
}


void DCServoStop(void)  //ֹͣ����
{
//ServoSetCommd(SERVO_COMMD_S,STAT_30H,SERVO_SPEED[0]);//�ٶ��趨
//DelayTime(200000);
ServoSetCommd(SERVO_COMMD_J,STAT_30H,0);
}

void DCServoMove_To(Int32U position,Int8U jog_flag)  //���� Ŀ��ֵ
{
Int8U speed_sel;

if(jog_flag==JOG_MOVE)//  1  :�㶯
	{
	speed_sel=JogSpeed_order;
	}
else     //����
	{
	ServoStartDelayTime=0;
	speed_sel=ServoSpeed_order;
	DcServoGoTarget_flag=1;
	NowSize_last=CurrentSize;
	ServoAutoPushFinish_flag=0;
	}
if(ServoNow_Speed!=SERVO_SPEED[speed_sel])
	{
	ServoNow_Speed=SERVO_SPEED[speed_sel];
	ServoSetCommd(SERVO_COMMD_S,STAT_30H,ServoNow_Speed);//�ٶ��趨
	DelayTime(2000000);
	}
ServoSetCommd(SERVO_COMMD_G,STAT_30H,position);  //���� Ŀ��
RLOUT1_ON;    // ������жϿ�
CutPermit_flag=0;
}

void DcServoStartRun_exec(Int32U target_pos)  
{
if(CurrentSize<=target_pos)  //���� ����
	{
	target_pos+=600;
	ChangeTarget_flag=0;
	ServoBack_flag=1;
	}
else
	{
	ServoBack_flag=0;
	}
DCServoMove_To(target_pos,RUN_MOVE);
}

