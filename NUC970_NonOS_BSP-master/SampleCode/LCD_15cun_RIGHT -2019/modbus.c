
#include"modbus.h"
#include "pic_exec.h"
#include "key.h"
#include "port.h"
#include "timer.h"

/*
#include"chndot.h"

#include"down_status.h"

*/

unsigned char ModBus_Rec_Data[60];
int ModBus_CommCou;
char ModBus_CommHead_Flag;  //����֡ͷ��־λ
char ModBus_CommFrame_Flag; //����֡��־λ
char ModBus_CommModBus_Commd;   //����
int ModBus_CommAdder;   //��ַ
int ModBus_CommFileLenth; //�ļ�����
int ModBus_CommLengthTemp;
char ModBus_CommEnd_Flag;  //֡������־λ

unsigned char ModBus_BackStatus,ModBus_ForwardStatus;


unsigned char ModBus_SendBuf[32];
unsigned char ModsBuf_RecBuf[32];

unsigned char ModBus_Queue_Buf[16][32];//���л���



unsigned char ModBusWaitTime;//�ȴ���ʱ
unsigned char ModBusWaitTime_Flag;//������ʱ;

unsigned int ModBus_CurDesmion;//����ֵλ��
 short ModBus_QuanData;  //��Ȧ����
unsigned int ModBus_TransPulsData; //�ѷ��͵���������

unsigned int ModBus_ACErr;     //��������
unsigned int ModBus_AcErr_HisData[16];//��ʷ�������
unsigned int ModBus_AcErr_Type;//

unsigned char ModBus_Comm_LinkErr;

unsigned char ModBus_CurCommand;   //��ǰ��ͨѶ����
unsigned short ModBus_CurAdder;   //��ǰ��ͨѶ��ַ

unsigned char ModBus_Busy_Flag;  //ͨѶæ��־λ

unsigned char Modbus_A6_LuoJu;	//�ݾ�
unsigned short Modbus_A6_Puls;     //ÿת������
unsigned char Modbus_A6_JianSuBi; //���ٱ�
unsigned int  Modbus_A6_Speed;   //�ٶ�
unsigned int  Modbus_A6_SpeedTemp;   //�ٶ��ݴ�

unsigned char Modbus_A6_Speed_Sel;//�ٶȵ�ѡ����

unsigned short Modbus_A6_AddSpeedTime; //���ٶ�ʱ��
unsigned short Modbus_A6_DecSpeedTime; //����ʱ��
unsigned int   Modbus_A6_PulsSize;//ÿ����ľ���ߴ�

unsigned int Modbus_A6_JiZhunMark;
unsigned int Modbus_A6_JiZhunDesmion;
 short Modbus_A6_JiZhunQuan;

unsigned int Modbus_A6_ManualSpeed;//�ֶ��ٶ�


unsigned short ModBus_Status;

unsigned char ModBus_WaitRun_Flag;

unsigned char ModBus_Run_Flag;//���б�־λ

unsigned int ModBusCommTime;
unsigned int ModBusCommTimeOut;

unsigned char ModBus_QueueLoadCou;
unsigned char ModBus_QueueCurCou;
unsigned char ModBus_QueueCou;

ModBusQueue ModBus_Queue; 


int ShouLunlunSize;//���ֳߴ�
unsigned int ShouLunExecTime;  //����ִ�м�ʱ  0.5��


//pInt16U fPtr;
//unsigned char *dfPtr;


Int8U SendCmdOn_flag;
Int16U SendCmdWaitTime;
Int16U ReadErrorTime;

Int8U ModBus_CodeDataMode;
Int32U CurrentSize_A6Coder;


Int8U A6CoderEqual_flag;//A6��������ֵ���
Int8U A6CoderCorrectMode;//�����ߴ�
Int16U A6CoderCorrectTime;//
Int8U A6CoderCorrectRun_flag;//�������б��

Int32U StartInitSize;	//������ʼ�ߴ�

Int16U A6ReadCoderSizeWaitTime;


void ModBusIO_Init(void)
{
//LCD_LE=0;
//P3_MUX_CLR=(1<<12);
 RS485_IO_FUN();
RS485_CS_OUT();
ModBus_QueueLoadCou=0;
ModBus_QueueCurCou=0;
}

void ModBus_CommExec(Int8U rx_data)
{
int i;
char a;
char stemp[8];
unsigned short crcdata,recvcrcdata;
ModBus_Rec_Data[ModBus_CommCou++]=rx_data;
if(ModBus_CommCou>2)
	{
	if((ModBus_Rec_Data[1]==A6_COMMAND_COIL_WRITE)||(ModBus_Rec_Data[1]==A6_COMMAND_REGISTER_WRITE)||(ModBus_Rec_Data[1]==A6_COMMAND_REGISTER_CWRITE))
		{
		if(ModBus_CommCou>=8)
			{//һ֡�������
			//ModBus_CommEnd_Flag=1;
			crcdata=ModBus_CRC_Code(ModBus_Rec_Data,6);
			recvcrcdata=(unsigned short)ModBus_Rec_Data[7]<<8;
			recvcrcdata+=ModBus_Rec_Data[6];
			if(crcdata==recvcrcdata)
				ModBus_CommEnd_Flag=1;//�ý�����ȷ
			ModBus_CommCou=0;
			}
		}
	else
		{
		if((ModBus_Rec_Data[1]==0x81)||(ModBus_Rec_Data[1]==0x83)||(ModBus_Rec_Data[1]==0x85)||(ModBus_Rec_Data[1]==0x86))
			{//�쳣����
			if(ModBus_CommCou>=5)
				{//һ֡�������
				crcdata=ModBus_CRC_Code(ModBus_Rec_Data,3);
				recvcrcdata=(unsigned short)ModBus_Rec_Data[4]<<8;
				recvcrcdata+=ModBus_Rec_Data[3];
				if(crcdata==recvcrcdata)
					ModBus_CommEnd_Flag=1;//�ý�����ȷ
				ModBus_CommCou=0;
				}
			}
		else
			{
			if(ModBus_CommCou>ModBus_Rec_Data[2]+4)
				{//һ֡�������
				//ModBus_CommEnd_Flag=1;
				crcdata=ModBus_CRC_Code(ModBus_Rec_Data,ModBus_Rec_Data[2]+3);
				recvcrcdata=(unsigned short)ModBus_Rec_Data[ModBus_CommCou-1]<<8;
				recvcrcdata+=ModBus_Rec_Data[ModBus_CommCou-2];
				if(crcdata==recvcrcdata)
					ModBus_CommEnd_Flag=1;//�ý�����ȷ
				ModBus_CommCou=0;
				}
			}
		}
	}

}






unsigned short ModBus_CRC_Code(unsigned char *sbuf,unsigned short length)
{ 
int i;
unsigned short crc=0xffff;

while(length--)
	{
	 crc ^= *sbuf++;
	 for (i = 0; i < 8; ++i)
		{
		 if (crc & 1)
			crc = (crc >> 1) ^ 0xA001;
		 else
			crc = (crc >> 1);
		}
	}
 
 return crc;
}



void ModBus_CRC_DeCode(unsigned char *rbuf)
{


}


void ModBus_SendFrame(unsigned char mid,unsigned char mcommand,unsigned short madder,unsigned short mdata)//
{
int x;
//RS485_SEND();
unsigned short crcdata;
ModBus_SendBuf[0]=mid;
ModBus_SendBuf[1]=mcommand;
ModBus_SendBuf[2]=madder>>8;
ModBus_SendBuf[3]=madder&0xff;
ModBus_SendBuf[4]=mdata>>8;
ModBus_SendBuf[5]=mdata&0xff;
crcdata=ModBus_CRC_Code(ModBus_SendBuf,6);	//����CRC
ModBus_SendBuf[6]=crcdata&0xff;
ModBus_SendBuf[7]=crcdata>>8;

ModBus_Queue_LoadBuf(ModBus_SendBuf,8);//���浽����

//UART0_SendBuf(ModBus_SendBuf,8);

//for(x=0;x<8000;x++);
//RS485_RECV();

}


void ModBus_CrcTest(void)
{
unsigned short crcdata;
ModBus_SendBuf[0]=0x01;
ModBus_SendBuf[1]=0x05;
ModBus_SendBuf[2]=0x00;
ModBus_SendBuf[3]=0x60;
ModBus_SendBuf[4]=0x00;
ModBus_SendBuf[5]=0x00;

crcdata=ModBus_CRC_Code(ModBus_SendBuf,6);	//����CRC
ModBus_SendBuf[6]=crcdata&0xff;
ModBus_SendBuf[7]=crcdata>>8;



ModBus_SendBuf[0]=0x01;
ModBus_SendBuf[1]=0x05;
ModBus_SendBuf[2]=0x00;
ModBus_SendBuf[3]=0x60;
ModBus_SendBuf[4]=0xff;
ModBus_SendBuf[5]=0x00;

crcdata=ModBus_CRC_Code(ModBus_SendBuf,6);	//����CRC
ModBus_SendBuf[6]=crcdata&0xff;
ModBus_SendBuf[7]=crcdata>>8;


ModBus_SendBuf[0]=0x01;
ModBus_SendBuf[1]=0x06;
ModBus_SendBuf[2]=0x44;
ModBus_SendBuf[3]=0x14;
ModBus_SendBuf[4]=0x00;
ModBus_SendBuf[5]=0x00;

crcdata=ModBus_CRC_Code(ModBus_SendBuf,6);	//����CRC
ModBus_SendBuf[6]=crcdata&0xff;
ModBus_SendBuf[7]=crcdata>>8;


ModBus_SendBuf[0]=0x01;
ModBus_SendBuf[1]=0x05;
ModBus_SendBuf[2]=0x01;
ModBus_SendBuf[3]=0x20;
ModBus_SendBuf[4]=0x00;
ModBus_SendBuf[5]=0x00;

crcdata=ModBus_CRC_Code(ModBus_SendBuf,6);	//����CRC
ModBus_SendBuf[6]=crcdata&0xff;
ModBus_SendBuf[7]=crcdata>>8;

}


//�趨�ٶȣ��Ӽ��ٶ�ʱ��   block��Ӧ�Ĳ�����
void ModBus_SetSpeedAndTime(unsigned char block,unsigned short speed,unsigned short addtime,unsigned short dectime)
{
ModBus_WirteBlockSpeed(block,speed);//�趨ת��
//ModBusWaitTime=20;//�ȴ�20mS
//ModBusWaitTime_Flag=1;//������ʱ
//while(ModBusWaitTime_Flag==1);//�ȴ�

ModBus_WirteBlockAddTime(block,addtime);//�趨���ٶ�ʱ��
//ModBusWaitTime=20;//�ȴ�20mS
//ModBusWaitTime_Flag=1;//������ʱ
//while(ModBusWaitTime_Flag==1);//�ȴ�

ModBus_WirteBlockDecTime(block,dectime);//�趨���ٶ�ʱ��
//ModBusWaitTime=20;//�ȴ�20mS
//ModBusWaitTime_Flag=1;//������ʱ
//while(ModBusWaitTime_Flag==1);//�ȴ�



}


//װ�ض���
void ModBus_Queue_LoadBuf(unsigned char *buf,unsigned char length)
{
int i;
//if(ModBus_QueueLoadCou==0)
if(ModBus_QueueLoadCou<15)
	{
	ModBus_QueueLoadCou++;
	ModBus_Queue_Buf[ModBus_QueueLoadCou][0]=length;//��һ�ֽ�Ϊ����
	for(i=0;i<length;i++)
		{
		ModBus_Queue_Buf[ModBus_QueueLoadCou][i+1]=buf[i];
		}	
	}
//ModBus_QueueLoadCou++;
}


//����װ�غ�Ķ���
unsigned char  ModBus_Queue_SendBuf(unsigned char queue,unsigned char flag)
{
int i,x;
int length;
if(flag==1)//����ת��
	{
	if(ModBus_Queue_ChangeBuf()==1)//�޶���������˳�
		return 1;
	}

RS485_SEND();
length=ModBus_Queue_Buf[queue][0];
for(i=0;i<length;i++)
	{
	ModBus_SendBuf[i]=ModBus_Queue_Buf[queue][i+1];
	}

//���뵱ǰ��ַ������
//ModBus_SendBuf[0]=MODBUS_SERVO_COMMADD;
ModBus_CurCommand=ModBus_SendBuf[1];//=A6_COMMAND_REGISTER_WRITE;
ModBus_CurAdder=ModBus_SendBuf[2]<<8;//=bsnum>>8;
ModBus_CurAdder+=ModBus_SendBuf[3];//=bsnum&0xff;

UART0_SendBuf(ModBus_SendBuf,length);
for(x=0;x<8000;x++);
RS485_RECV();
return 0;

}

unsigned char ModBus_Queue_ChangeBuf(void)//
{
unsigned int i,n;
if(ModBus_QueueLoadCou>0)
	{//�ж������  //ָ���׸����С�������
	for(i=1;i<ModBus_QueueLoadCou+1;i++)
		{
		for(n=0;n<32;n++)
			{
			ModBus_Queue_Buf[i][n]=ModBus_Queue_Buf[i+1][n];
			}
		}
	ModBus_QueueLoadCou--;//����װ�ؼ�����1
	for(n=0;n<32;n++)
		{
		ModBus_Queue_Buf[ModBus_QueueLoadCou+1][n]=0xff;
		}
	if(ModBus_QueueLoadCou==0)
		return 1;//���п�
	else
		return 0;//���ж���
	}
else
	{
	return 1;
	}
}



void ModBus_WirteBlock(unsigned short block,unsigned char commd,unsigned char v0,unsigned char a0,unsigned char d0, int position)
{
//unsigned int blockdata;
int x;
//RS485_SEND();
unsigned short crcdata;/*
block*=2;//һ��BLOCKռ2����ַλ
block+=0x4800;//BLOCK��ַ
ModBus_SendBuf[0]=0x01;
ModBus_SendBuf[1]=A6_COMMAND_REGISTER_WRITE;
ModBus_SendBuf[2]=block>>8;
ModBus_SendBuf[3]=block&0xff;

ModBus_SendBuf[4]=(d0<<2)+0;//0Ϊ��Ǩ��
ModBus_SendBuf[5]=0x00;//�̶�00
ModBus_SendBuf[6]=commd;//�̶�00
ModBus_SendBuf[7]=(v0<<4)+a0;//�̶�00


crcdata=ModBus_CRC_Code(ModBus_SendBuf,8);	//����CRC
ModBus_SendBuf[8]=crcdata&0xff;
ModBus_SendBuf[9]=crcdata>>8;

ModBus_SendBuf[8]=(position>>8)&0xff;//(v0<<4)+a0;//�̶�00
ModBus_SendBuf[9]=(position&0xff);//(v0<<4)+a0;//�̶�00
ModBus_SendBuf[10]=(position>>24)&0xff;//(v0<<4)+a0;//�̶�00
ModBus_SendBuf[11]=(position>>16)&0xff;//(v0<<4)+a0;//�̶�00

crcdata=ModBus_CRC_Code(ModBus_SendBuf,12);	//����CRC
ModBus_SendBuf[12]=crcdata&0xff;
ModBus_SendBuf[13]=crcdata>>8;

UART0_SendBuf(ModBus_SendBuf,10);
for(x=0;x<8000;x++);
RS485_RECV();
*/
/*

block*=2;//һ��BLOCKռ2����ַλ
block+=0x4800;//BLOCK��ַ
ModBus_SendBuf[0]=0x01;
ModBus_SendBuf[1]=A6_COMMAND_REGISTER_WRITE;
ModBus_SendBuf[2]=block>>8;
ModBus_SendBuf[3]=block&0xff;

ModBus_SendBuf[4]=(d0<<2)+0;//0Ϊ��Ǩ��
ModBus_SendBuf[5]=0x00;//�̶�00
ModBus_SendBuf[6]=commd;//�̶�00
ModBus_SendBuf[7]=(v0<<4)+a0;//�̶�00

ModBus_SendBuf[8]=(position>>8)&0xff;//(v0<<4)+a0;//�̶�00
ModBus_SendBuf[9]=(position&0xff);//(v0<<4)+a0;//�̶�00
ModBus_SendBuf[10]=(position>>24)&0xff;//(v0<<4)+a0;//�̶�00
ModBus_SendBuf[11]=(position>>16)&0xff;//(v0<<4)+a0;//�̶�00

crcdata=ModBus_CRC_Code(ModBus_SendBuf,12);	//����CRC
ModBus_SendBuf[12]=crcdata&0xff;
ModBus_SendBuf[13]=crcdata>>8;
UART0_SendBuf(ModBus_SendBuf,14);
for(x=0;x<8000;x++);
RS485_RECV();
*/


block*=2;//һ��BLOCKռ2����ַλ
block+=0x4800;//BLOCK��ַ
ModBus_SendBuf[0]=0x01;
ModBus_SendBuf[1]=A6_COMMAND_REGISTER_CWRITE;
ModBus_SendBuf[2]=block>>8;
ModBus_SendBuf[3]=block&0xff;
ModBus_SendBuf[4]=0;
ModBus_SendBuf[5]=0x4;
ModBus_SendBuf[6]=0x08;

ModBus_SendBuf[7]=(d0<<2)+0;//0Ϊ��Ǩ��
ModBus_SendBuf[8]=0x00;//�̶�00
ModBus_SendBuf[9]=commd;//block ������
ModBus_SendBuf[10]=(v0<<4)+a0;//�ٶȺͼ��ٶ�ʱ��ϲ�

ModBus_SendBuf[11]=(unsigned char)((position>>8));//&0xff;//��Ի����λ�õ�16λ�ĸ�λ
ModBus_SendBuf[12]=(unsigned char)((position));//;//��Ի����λ�õ�16λ�ĵ�λ
ModBus_SendBuf[13]=(unsigned char)((position>>24));//&0xff;//��Ի����λ�ø�16λ�ĸ�λ
ModBus_SendBuf[14]=(unsigned char)((position>>16));//&0xff;//��Ի����λ�ø�16λ�ĵ�λ

crcdata=ModBus_CRC_Code(ModBus_SendBuf,15);	//����CRC
ModBus_SendBuf[15]=crcdata&0xff;
ModBus_SendBuf[16]=crcdata>>8;
ModBus_Queue_LoadBuf(ModBus_SendBuf,17);
//UART0_SendBuf(ModBus_SendBuf,17);
//for(x=0;x<8000;x++);
//RS485_RECV();
//*/
}


void ModBus_WirteBlockSpeed(unsigned short bsnum,unsigned short speed)//�����ٶ�  0-15����Ӧ�ٶ�����
{
int x;
//RS485_SEND();
unsigned short crcdata;
bsnum+=0x4600;//0x4600 Ϊ0���ٶ�������ʼ��ַ
ModBus_SendBuf[0]=MODBUS_SERVO_COMMADD;
ModBus_SendBuf[1]=A6_COMMAND_REGISTER_WRITE;
ModBus_SendBuf[2]=bsnum>>8;
ModBus_SendBuf[3]=bsnum&0xff;
ModBus_SendBuf[4]=speed>>8;
ModBus_SendBuf[5]=speed&0xff;
crcdata=ModBus_CRC_Code(ModBus_SendBuf,6);	//����CRC
ModBus_SendBuf[6]=crcdata&0xff;
ModBus_SendBuf[7]=crcdata>>8;

ModBus_Queue_LoadBuf(ModBus_SendBuf,8);
//UART0_SendBuf(ModBus_SendBuf,8);
//for(x=0;x<8000;x++);
//RS485_RECV();
}

void ModBus_WirteBlockAddTime(unsigned short bsnum,unsigned short time)//���ü���ʱ��  0-15����Ӧ����ʱ������
{
int x;
//RS485_SEND();
unsigned short crcdata;
bsnum+=0x4610;//0x4610 Ϊ0�ż���ʱ��������ʼ��ַ
ModBus_SendBuf[0]=MODBUS_SERVO_COMMADD;
ModBus_SendBuf[1]=A6_COMMAND_REGISTER_WRITE;
ModBus_SendBuf[2]=bsnum>>8;
ModBus_SendBuf[3]=bsnum&0xff;
ModBus_SendBuf[4]=time>>8;
ModBus_SendBuf[5]=time&0xff;
crcdata=ModBus_CRC_Code(ModBus_SendBuf,6);	//����CRC
ModBus_SendBuf[6]=crcdata&0xff;
ModBus_SendBuf[7]=crcdata>>8;
ModBus_Queue_LoadBuf(ModBus_SendBuf,8);
//UART0_SendBuf(ModBus_SendBuf,8);
//for(x=0;x<8000;x++);
//RS485_RECV();

}

void ModBus_WirteBlockDecTime(unsigned short bsnum,unsigned short time)//���ü���ʱ��  0-15����Ӧ����ʱ������
{
int x;
//RS485_SEND();
unsigned short crcdata;
bsnum+=0x4620;//0x4600 Ϊ0���ٶ�������ʼ��ַ
ModBus_SendBuf[0]=MODBUS_SERVO_COMMADD;
ModBus_SendBuf[1]=A6_COMMAND_REGISTER_WRITE;
ModBus_SendBuf[2]=bsnum>>8;
ModBus_SendBuf[3]=bsnum&0xff;
ModBus_SendBuf[4]=time>>8;
ModBus_SendBuf[5]=time&0xff;
crcdata=ModBus_CRC_Code(ModBus_SendBuf,6);	//����CRC
ModBus_SendBuf[6]=crcdata&0xff;
ModBus_SendBuf[7]=crcdata>>8;
ModBus_Queue_LoadBuf(ModBus_SendBuf,8);
//UART0_SendBuf(ModBus_SendBuf,8);
//for(x=0;x<8000;x++);
//RS485_RECV();
}



void ModBus_Queue_StartBuf(void)//�������л�����
{
ModBusCommTime++;
switch(ModBusCommTime)
		  {
		  case 1:		
			    if(ModBus_QueueLoadCou>0)
				  {
				  ModBus_CommCou=0;
				  ModBus_CommEnd_Flag=0;
				  if(ACServoDrvErr_flag==0)
				  ModBus_Queue_SendBuf(1,0);//����
				  }
				//��Զ��ֻ�ǵ�һ�������ȷ���			
			    //ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4202,0x02);//������λ��  ����ֵ
				//ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES600F,0x02);//��ȡ��ǰֵ
			  break;
		  case 25://ͨѶ��ʱ
				if(ModBus_CommEnd_Flag==1)
					{
					if(ModBus_CurCommand==A6_COMMAND_REGISTER_READ)
						{
						switch(ModBus_CurAdder)
							{
							case A6_REGISTER_ADDRES4202://������λ��
								ModBus_CurDesmion=(unsigned int)ModBus_Rec_Data[5]<<24;
								ModBus_CurDesmion+=(unsigned int)ModBus_Rec_Data[6]<<16;
								ModBus_CurDesmion+=(unsigned int)ModBus_Rec_Data[3]<<8;
								ModBus_CurDesmion+=(unsigned int)ModBus_Rec_Data[4];
								break;
							case A6_REGISTER_ADDRES4204://��Ȧ����
								ModBus_QuanData=(unsigned int)ModBus_Rec_Data[5]<<24;
								ModBus_QuanData+=(unsigned int)ModBus_Rec_Data[6]<<16;
								ModBus_QuanData+=(unsigned int)ModBus_Rec_Data[3]<<8;
								ModBus_QuanData+=(unsigned int)ModBus_Rec_Data[4];

								if(Run_flag==1)
									{
								//	if((ModBus_BackStatus==0)&&(ModBus_ForwardStatus==0))
									//	{
										 if(houtui==1)
											{
											 if(((CurrentSize>TargetSize+500-5))&&((CurrentSize<TargetSize+500+5)))
												{
												 Modbus_ACServoStop();
												 ModBus_WaitRun_Flag=1;

												 Modbus_ACMotorRunStart(TargetSize);//����+5   ���ǰ��
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
											// Run_flag=1;//�����У����м����ܰ���
											//Modbus_ACMotorRunStart(TargetSize);
											// Modbus_ACMotorRunStart(CurrentSize-500);// vbcd)
											}
										else
											{
											if(ModBus_WaitRun_Flag==1)
												ModBus_WaitRun_Flag=0;
											if(((CurrentSize>TargetSize-5))&&((CurrentSize<TargetSize+5)))
												{
												 Modbus_ACServoStop();
												}
											}
									//	 }

									ShouLunlunSize=0;
									ShouLunExecTime=0;
									}
								else
									{//�ж��Ƿ����������Ч
									if((ElectricWheelOn_flag==1))
											{//�������ִ���
											ShouLunExecTime++;
											if(ShouLunExecTime>=10)
												{
												ShouLunExecTime=0;
												if(ShouLunlunSize!=0)
													{
													Modbus_ACMotorShouLun();//����ת��  0.5��
													ShouLunlunSize=0;
													}
												}
											}
									else
										{
										ShouLunlunSize=0;
										ShouLunExecTime=0;

										}
									}


								//if(ModBus_WaitRun_Flag==1)
								//{
								//	ModBus_WaitRun_Flag=0;
								//	Modbus_ACMotorRunStart(TargetSize);//����+5   ���ǰ��

								//}
								break;
							case A6_REGISTER_ADDRES4001://�������
							ModBus_ACErr=(unsigned int)ModBus_Rec_Data[3]<<8;
							ModBus_ACErr+=(unsigned int)ModBus_Rec_Data[4];

								break;
							case A6_REGISTER_ADDRES4000://������״̬
								//ModBus_Status=(unsigned int)ModBus_Rec_Data[3]<<8;
							//	ModBus_Status+=(unsigned int)ModBus_Rec_Data[4];

								break;
							case 0x00a2:
								ModBus_Status=(unsigned int)ModBus_Rec_Data[3]<<8;
								ModBus_Status+=(unsigned int)ModBus_Rec_Data[4];
								//if(ModBus_Status&0x0001)
							//		 Modbus_ACServoStop();
								break;
														
							}
						}
					else
						{
						if(ModBus_CurCommand==A6_COMMAND_COIL_READ)
							{
							switch(ModBus_CurAdder)
							{
							case 0x0102:
								ModBus_BackStatus=ModBus_Rec_Data[3];
							//	unsigned char ModBus_BackStatus,ModBus_ForwardStatus;
								break;
							case 0x0103:
								ModBus_ForwardStatus=ModBus_Rec_Data[3];
								if(Run_flag==1)
									{
									if((ModBus_BackStatus==0)&&(ModBus_ForwardStatus==0))
										{
										 if(houtui==1)
											{
											 if(((CurrentSize>TargetSize+500-5))&&((CurrentSize<TargetSize+500+5)))
												{
												 Modbus_ACServoStop();
												 ModBus_WaitRun_Flag=1;
												}
											// Run_flag=1;//�����У����м����ܰ���
											//Modbus_ACMotorRunStart(TargetSize);
											// Modbus_ACMotorRunStart(CurrentSize-500);// vbcd)
											}
										else
											{
											if(((CurrentSize>TargetSize-5))&&((CurrentSize<TargetSize+5)))
												{
												 Modbus_ACServoStop();
												}
											}
										 }
									}
								break;	
							}


							}
						}
					

					if(ModBus_Queue_ChangeBuf()==1)
						{//����н����������ѯ��ǰ�ߴ�ȶ���
						ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4202,0x02);//������λ��
						ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4204,0x02);//��Ȧ����
						ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4001,1);//���������
					//	ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4000,1);//��������״̬
					//	if(Run_flag==1)
					//		{
					//		ModBus_SendFrame(0x1,A6_COMMAND_COIL_READ,0x0102,1);//��ѯ�Ƿ��ڷ�ת�Ƿ����
					//		ModBus_SendFrame(0x1,A6_COMMAND_COIL_READ,0x0103,1);//��ѯ�Ƿ�����ת
					//		}
						//	ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,0x00a2,1);//��ѯ��λ�Ƿ����
						}				
					ModBus_CommEnd_Flag=0;
					ModBusCommTime=0;//�յ���Ч���ݣ����·���
					ModBusCommTimeOut=0;
					ModBus_Comm_LinkErr=0;
					}
				else
					{
					 ModBusCommTime=0;
					 ModBusCommTimeOut++;
					 if(ModBusCommTimeOut>3)
						{ //��ʱ����
						  ModBusCommTimeOut=0;
						  ModBus_Comm_LinkErr=1;//ͨѶ���Ӵ���
						  if(Run_flag==1)
								{
									Modbus_ACServoStop();
								}
						}
					}

			  break;
		  }
if(ModBusCommTime>100)
	{//���س�ʱ
		ModBus_CommEnd_Flag=0;
					ModBusCommTime=0;//�յ���Ч���ݣ����·���
					ModBusCommTimeOut=0;
					ModBus_Comm_LinkErr=1;//ͨѶ���Ӵ���
					if(Run_flag==1)
							{
					Modbus_ACServoStop();
							}

	}
}

/***
void ModBus_Queue_Start(void)//��������
{

ModBusCommTime++;
switch(ModBusCommTime)
		  {
		  case 1:
			  	ModBus_CommCou=0;
				ModBus_CommEnd_Flag=0;
				//��Զ��ֻ�ǵ�һ�������ȷ���
				ModBus_SendFrame(ModBus_Queue.MB_Id[1],ModBus_Queue.MB_Command[1],ModBus_Queue.MB_Adder[1],ModBus_Queue.MB_Data[1]);
				ModBus_CurCommand=ModBus_Queue.MB_Command[1];
				ModBus_CurAdder=ModBus_Queue.MB_Adder[1];
			    //ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4202,0x02);//������λ��  ����ֵ
				//ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES600F,0x02);//��ȡ��ǰֵ
			  break;
		  case 20://ͨѶ��ʱ
			  ModBusCommTime=0;
			  break;
		  }

if(ModBusCommTime>100)
	{//�������س�ʱ
	 ModBusCommTime=0;
	}
else
	{
	if(ModBusCommTime>5)
		{//�ж��Ƿ��з���
	    if(ModBus_CommEnd_Flag==1)
					{
					ModBus_CurDesmion=(unsigned int)ModBus_Rec_Data[5]<<24;
					ModBus_CurDesmion+=(unsigned int)ModBus_Rec_Data[6]<<16;
					ModBus_CurDesmion+=(unsigned int)ModBus_Rec_Data[3]<<8;
					ModBus_CurDesmion+=(unsigned int)ModBus_Rec_Data[4];

					if(ModBus_ChangeQueue()==1)
						{//����н����������ѯ��ǰ�ߴ�ȶ���
						ModBus_LoadQueue(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4202,0x02);//������λ��
						ModBus_LoadQueue(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4204,0x02);//��Ȧ����
						ModBus_LoadQueue(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4001,0x02);//���������

						}				
					ModBus_CommEnd_Flag=0;
					ModBusCommTime=0;//�յ���Ч���ݣ����·���
					}
		}
	}
}


void ModBus_Queue_Test(void)
{
	unsigned char x,i;
	ModBus_QueueLoadCou=0;
	ModBus_QueueCurCou=0;
ModBus_LoadQueue(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4202,0x02);//������λ��
ModBus_LoadQueue(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4204,0x02);//��Ȧ����
ModBus_LoadQueue(0x1,A6_COMMAND_REGISTER_READ,0x4800,0x0004);

i=ModBus_ChangeQueue();
i=ModBus_ChangeQueue();
i=ModBus_ChangeQueue();
i=ModBus_ChangeQueue();
x=i+ModBus_ChangeQueue();
}



//װ�ض���
unsigned char  ModBus_LoadQueue(unsigned char mid,unsigned char mcommand,unsigned short madder,unsigned short mdata)
{


if(ModBus_QueueLoadCou<10)
	{
	if(ModBus_QueueLoadCou==ModBus_QueueCurCou)
		{
		ModBus_QueueLoadCou++;//��ǰ�������ڴ��ͣ�ָ����һ���л���
		}
	ModBus_Queue.MB_Id[ModBus_QueueLoadCou]=mid;
	ModBus_Queue.MB_Command[ModBus_QueueLoadCou]=mcommand;
	ModBus_Queue.MB_Adder[ModBus_QueueLoadCou]=madder;
	ModBus_Queue.MB_Data[ModBus_QueueLoadCou]=mdata;
	ModBus_QueueLoadCou++;
	return 0;
	}
else
	{
	return 1;//������������
	}
}


//ת������
unsigned char ModBus_ChangeQueue(void)//����2��������Ч������ʼ�մ��͵�һ������
{
unsigned int i;
if(ModBus_QueueLoadCou>1)
	{//�ж������  //ָ���׸����С�������
	for(i=1;i<ModBus_QueueLoadCou;i++)
		{
		ModBus_Queue.MB_Id[i]=ModBus_Queue.MB_Id[i+1];		
		ModBus_Queue.MB_Command[i]=ModBus_Queue.MB_Command[i+1];		
		ModBus_Queue.MB_Adder[i]=ModBus_Queue.MB_Adder[i+1];		
		ModBus_Queue.MB_Data[i]=ModBus_Queue.MB_Data[i+1];		
		}
	ModBus_QueueLoadCou--;//����װ�ؼ�����1
	ModBus_Queue.MB_Id[ModBus_QueueLoadCou]=0xFF;
	ModBus_Queue.MB_Command[ModBus_QueueLoadCou]=0xFF;
	ModBus_Queue.MB_Adder[ModBus_QueueLoadCou]=0xFFFF;
	ModBus_Queue.MB_Data[ModBus_QueueLoadCou]=0xFFFF;
	return 0; //����ת�����
	}
else
	{//ֻ��һ������
	return 1;//ֻ��1������
	}
}


//ɾ������
unsigned char ModBus_DeletQueue(unsigned char queue)// �βΣ�1��ɾ����һ������  16:ɾ�� �������ִ�к���ĵ����ж���
{
	// /*
// if(ModBus_QueueLoadCou<10)
	// {
	// ModBus_Queue.MB_Id[ModBus_QueueLoadCou]=mid;
	// ModBus_Queue.MB_Command[ModBus_QueueLoadCou]=mcommand;
	// ModBus_Queue.MB_Adder[ModBus_QueueLoadCou]=madder;
	// ModBus_Queue.MB_Data[ModBus_QueueLoadCou]=mdata;
	// ModBus_QueueLoadCou++;
	// return 0;
	// }
// else
	// {
	// return 1;//������������
	// }
	// 
	return 0;
}
****/






void Modbus_MoveStop(void)
{



}

void Modbus_AC_ChangeSPD(void)  
{
if(flagqyx==1)
	{
	 step_add=10;      
	  step_ground=11; 

	  speedup_steps=30;
	  status=1;      
	  houtui=0; 
	}    
}


void  A6_CalPulsSize(void)   //����һ����ľ���
{
Modbus_A6_PulsSize=Modbus_A6_LuoJu*10000/Modbus_A6_Puls;
}

void  A6_CalCurSize(void)//���㵱ǰλ��
{
  long long int  A6_CurDesmionSize;
 long long int  JiZhunDesmionSize;
unsigned  long long  LuoJuPuls;
unsigned  long long  LuoJuSize;


 long long int ModBus_CurDesmionTemp;
 long long int Modbus_A6_JiZhunDesmionTemp;

 long long int ModBus_QuanDataTemp;
 long long  int Modbus_A6_JiZhunQuanTemp;
 long long int Modbus_A6_JiZhunTemp;
 long long int CurrentSizeTemp;

int quandata;
//��ǰȦ����
ModBus_CurDesmionTemp=ModBus_CurDesmion;
ModBus_QuanDataTemp=(int)ModBus_QuanData;
//��׼Ȧ����
Modbus_A6_JiZhunDesmionTemp=Modbus_A6_JiZhunDesmion;
//ModBus_QuanDataTemp=(long long int)ModBus_QuanData;
Modbus_A6_JiZhunQuanTemp=(long long int)Modbus_A6_JiZhunQuan;

//��׼ֵ
Modbus_A6_JiZhunTemp=OriginalSize;	//Modbus_A6_JiZhunMark;
Modbus_A6_JiZhunTemp*=10;

/**
// LuoJuPuls=838860700/((unsigned  long long )(Modbus_A6_LuoJu)*1000);
LuoJuPuls=838860800/((unsigned  long long )(Modbus_A6_LuoJu)*1000);

ModBus_CurDesmionTemp*=100;
ModBus_CurDesmionTemp/=(unsigned  long long )(LuoJuPuls);

Modbus_A6_JiZhunDesmionTemp*=100;
Modbus_A6_JiZhunDesmionTemp/=(unsigned  long long )(LuoJuPuls);
***/

//LuoJuSize=((unsigned  long long )(Modbus_A6_LuoJu)*1000*1000)/8388608;

ModBus_CurDesmionTemp=ModBus_CurDesmionTemp*((unsigned  long long )(Modbus_A6_LuoJu)*1000)/8388608;
Modbus_A6_JiZhunDesmionTemp=Modbus_A6_JiZhunDesmionTemp*((unsigned  long long )(Modbus_A6_LuoJu)*1000)/8388608;


A6_CurDesmionSize=((ModBus_QuanDataTemp*Modbus_A6_LuoJu)*1000)+ModBus_CurDesmionTemp;//(ModBus_CurDesmionTemp)*100000/LuoJuPuls;
JiZhunDesmionSize=((Modbus_A6_JiZhunQuanTemp*Modbus_A6_LuoJu)*1000)+Modbus_A6_JiZhunDesmionTemp;//(Modbus_A6_JiZhunDesmionTemp)*100000/LuoJuPuls;
if(A6_CurDesmionSize>JiZhunDesmionSize)
	{
	A6_CurDesmionSize-=JiZhunDesmionSize;
	CurrentSizeTemp=Modbus_A6_JiZhunTemp-A6_CurDesmionSize;
	}
else
	{
	if(A6_CurDesmionSize<JiZhunDesmionSize)
		{
		JiZhunDesmionSize-=A6_CurDesmionSize;
		CurrentSizeTemp=Modbus_A6_JiZhunTemp+JiZhunDesmionSize;
		}
	else
		{
		CurrentSizeTemp=Modbus_A6_JiZhunTemp;
		}
	}


//CurrentSizeTemp/=100;
unsigned int a;

a=CurrentSizeTemp%10;

if((a)>4)
	{//4��5��
	CurrentSizeTemp/=10;
	CurrentSizeTemp++;
	}
else
	{
	CurrentSizeTemp/=10;
	}

CurrentSize_A6Coder=CurrentSizeTemp;

ModBus_CodeDataMode=0;//��ȡ���
			
// //CurrentSize=CurrentSizeTemp;

// // if((ElectricWheelOn_flag==0)&&(Run_flag==0))
	// // {
	// // if(TargetSize!=CurrentSize)
		// // {
		// // if((TargetSize>(CurrentSize-5))&&(TargetSize<(CurrentSize+5)))
			// // {
			// // CurrentSize=TargetSize;

			// // }
		// // }
	// // }


/*

//A6_CurDesmionSize=0x7fffff*1000;

//LuoJuPuls=0x7fffff*1000/(Modbus_A6_LuoJu);//*1000);
LuoJuPuls=8388607000/(unsigned  long long )(Modbus_A6_LuoJu);//*1000);

ModBus_CurDesmionTemp*=20000000;
ModBus_CurDesmionTemp/=(unsigned  long long )(LuoJuPuls);
//ModBus_CurDesmionTemp*=10;


Modbus_A6_JiZhunDesmionTemp*=20000000;
Modbus_A6_JiZhunDesmionTemp/=(unsigned  long long )(LuoJuPuls);
//Modbus_A6_JiZhunDesmionTemp*=10;



A6_CurDesmionSize=((ModBus_QuanDataTemp*Modbus_A6_LuoJu)*100000)+ModBus_CurDesmionTemp;//(ModBus_CurDesmionTemp)*100000/LuoJuPuls;
JiZhunDesmionSize=((Modbus_A6_JiZhunQuanTemp*Modbus_A6_LuoJu)*100000)+Modbus_A6_JiZhunDesmionTemp;//(Modbus_A6_JiZhunDesmionTemp)*100000/LuoJuPuls;
if(A6_CurDesmionSize>JiZhunDesmionSize)
	{
	A6_CurDesmionSize-=JiZhunDesmionSize;
	CurrentSizeTemp=Modbus_A6_JiZhunTemp-A6_CurDesmionSize;
	}
else
	{
	if(A6_CurDesmionSize<JiZhunDesmionSize)
		{
		JiZhunDesmionSize-=A6_CurDesmionSize;
		CurrentSizeTemp=Modbus_A6_JiZhunTemp+JiZhunDesmionSize;
		}
	else
		{
		CurrentSizeTemp=Modbus_A6_JiZhunTemp;
		}
	}


CurrentSizeTemp/=100;
unsigned int a;

a=CurrentSizeTemp%10;

if((a%10)>3)
	{//4��5��
	CurrentSizeTemp/=10;
	CurrentSizeTemp++;
	}
else
	{
	CurrentSizeTemp/=10;
	}

CurrentSize=CurrentSizeTemp;
*/

}


void A6_LoadSpeed(void)
{
switch(Modbus_A6_Speed_Sel)
	{
	case 0:
		Modbus_A6_Speed=100;
		break;
	case 1:
		Modbus_A6_Speed=200;
		break;
	case 2:
		Modbus_A6_Speed=400;
		break;
	case 3:
		Modbus_A6_Speed=600;
		break;
	case 4:
		Modbus_A6_Speed=800;
		break;
	case 5:
		Modbus_A6_Speed=1000;
		break;
	case 6:
		Modbus_A6_Speed=1200;
		break;
	case 7:
		Modbus_A6_Speed=1400;
		break;
	case 8:
		Modbus_A6_Speed=1500;
		break;
	case 9:
		Modbus_A6_Speed=1600;
		break;
	case 10:
		Modbus_A6_Speed=1800;
		break;
	case 11:
		Modbus_A6_Speed=2000;
		break;
	case 12:
		Modbus_A6_Speed=2200;
		break;
	case 13:
		Modbus_A6_Speed=2500;
		break;
	case 14:
		Modbus_A6_Speed=2800;
		break;
	case 15:
		Modbus_A6_Speed=3000;
		break;
	}
}


void Modbus_ACMotorRunStart(Int32U vbcd)//  AC�ŷ�  ��������
{
Int32U tempqianjin1;    
Int32U temphoutui1;    
Int32U tragsize;
int rollsteps1;
/*
ModBus_SetSpeedAndTime(0,800,1000,1000);
ModBus_WirteBlock(0,0x1,0,0,0,-20000); // д�����Ŀ��ֵ
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //������ת  ����STB  STB����ON
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //�ر�STB STB����OFF

return;
*/
TargetSize=vbcd;
A6_CalPulsSize();//����һ�������
if(vbcd<CurrentSize)
	{ 
	//tempqianjin1=(CurrentSize-vbcd)*2;
	//rollsteps1=tempqianjin1-yushu;
	tempqianjin1=(CurrentSize-vbcd);

    rollsteps1=tempqianjin1*100/Modbus_A6_PulsSize;//-yushu;

	if(rollsteps1>1)
		{
	tragsize=rollsteps1*Modbus_A6_PulsSize/100;
	tragsize=CurrentSize-tragsize;
	if(tragsize>TargetSize)
		{
		rollsteps1++;
		}
	else
		{
		if(tragsize<TargetSize)
			{
			rollsteps1--;
			}
		}
		}
	
    qianjin=1;
    houtui=0;  
	
	RLOUT1_ON;    // ������жϿ�
	CutPermit_flag=0;
	}  
else if(vbcd>CurrentSize)
    {
	// temphoutui1=(vbcd-CurrentSize)*2;
		//rollsteps1=temphoutui1+yushu;
	 vbcd+=500;
	// TargetSize+=500;
	 temphoutui1=(vbcd-CurrentSize);

	 rollsteps1=temphoutui1*100/Modbus_A6_PulsSize;//+yushu;

	 if(rollsteps1>1)
		{

	 tragsize=rollsteps1*Modbus_A6_PulsSize/100;
	 tragsize+=CurrentSize;
	 if(tragsize>vbcd)
		{
		rollsteps1--;
		}
	else
		{
		if(tragsize<vbcd)
			{
			rollsteps1++;
			}
		}
		}
	 houtui=1;
	 qianjin=0;
	 
	 
	RLOUT1_ON;    // ������жϿ�
	CutPermit_flag=0; 
    }  
else
    {
	qianjin=0;
    houtui=0;
	ModBus_Run_Flag=0;
	}   
          
if(houtui==1)
    {     
	step_ground=11; 
//	rollsteps1=rollsteps1+50000/Modbus_A6_PulsSize;    
	//
        
	if(rollsteps1>3000)
		{
	   speedup_steps=100;  
	   Modbus_A6_SpeedTemp=Modbus_A6_Speed;
	  // speedup_steps_B=speedup_steps;
	 //  rollsteps1=(rollsteps1- speedup_steps*22)+2;
	   status=1;      
		
		}
	else if(rollsteps1>2000&&rollsteps1<3001)
		{  
		speedup_steps=45; 
		Modbus_A6_SpeedTemp=Modbus_A6_Speed*80/100;
		//speedup_steps_B=speedup_steps;
		//rollsteps1=(rollsteps1- speedup_steps*22)+2;
		status=1;  
		  
		
		}                                                               
	else if(rollsteps1>1000&&rollsteps1<2001)
		{
	   speedup_steps=30; 
	   Modbus_A6_SpeedTemp=Modbus_A6_Speed*60/100;
	  // speedup_steps_B=speedup_steps;
	  // rollsteps1=(rollsteps1- speedup_steps*22)+2;
	   status=1;  
						
		} 
	else if(rollsteps1>500&&rollsteps1<1001)
		{
	   speedup_steps=20;
	   Modbus_A6_SpeedTemp=Modbus_A6_Speed*40/100;
	 //  speedup_steps_B=speedup_steps;
	  // rollsteps1=(rollsteps1- speedup_steps*22)+2;
	   status=1;  
					
		}   
	else  if(rollsteps1>100&&rollsteps1<501)
		{
		speedup_steps=4;   
		Modbus_A6_SpeedTemp=Modbus_A6_Speed*30/100;
		//speedup_steps_B=speedup_steps;
		//rollsteps1=(rollsteps1- speedup_steps*22)+2;
		status=1;  
			
		}
	else
		{  
		   status=9;    
		   step_add=1;  
		   Modbus_A6_SpeedTemp=Modbus_A6_Speed*20/100;
		   
	 //       speedup_steps=1;
		}
          
	flagtingji8=0;
	flagyunxing8=1;
	step_add=1;     
	
	ModBus_Run_Flag=1;

	ModBus_SetSpeedAndTime(0,Modbus_A6_SpeedTemp,Modbus_A6_AddSpeedTime,Modbus_A6_DecSpeedTime);
	ModBus_WirteBlock(0,0x1,0,0,0,0-rollsteps1); // д�����Ŀ��ֵ
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //������ת  ����STB  STB����ON
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //�ر�STB STB����OFF

	//Timer1Init();
	//Timer0Disable();
    }  
            
            
if(qianjin==1)//----------------------------------------------------------
    {
     step_ground=11;  
  
	if(rollsteps1>3000)
		{
	   speedup_steps=100;  
	   Modbus_A6_SpeedTemp=Modbus_A6_Speed;
	  // speedup_steps_B=speedup_steps;
	  // rollsteps1=(rollsteps1- speedup_steps*22)+2;
	   status=1;  
	  
		}
	else if(rollsteps1>2000&&rollsteps1<3001)
		{
		speedup_steps=45;
		 Modbus_A6_SpeedTemp=Modbus_A6_Speed*80/100;
	//	speedup_steps_B=speedup_steps;
	//	rollsteps1=(rollsteps1- speedup_steps*22)+2;
		status=1;   
	   
		}
	else if(rollsteps1>1000&&rollsteps1<2001)
		{
	   speedup_steps=30;
	    Modbus_A6_SpeedTemp=Modbus_A6_Speed*60/100;
	 //  speedup_steps_B=speedup_steps;
	 //  rollsteps1=(rollsteps1- speedup_steps*22)+2;
	   status=1;   
				
		} 
	else if(rollsteps1>500&&rollsteps1<1001)
		{
	   speedup_steps=20;
	    Modbus_A6_SpeedTemp=Modbus_A6_Speed*40/100;
	 //  speedup_steps_B=speedup_steps;
	 //  rollsteps1=(rollsteps1- speedup_steps*22)+2;
	   status=1;   
				  
		}   
	else  if(rollsteps1>100&&rollsteps1<501)
		{
		speedup_steps=4;  
		 Modbus_A6_SpeedTemp=Modbus_A6_Speed*30/100;
	//	speedup_steps_B=speedup_steps;
	//	rollsteps1=(rollsteps1- speedup_steps*22)+2;
		status=1;  
		 
		}
	else
		{    
		status=9; 
		step_add=1;  
		Modbus_A6_SpeedTemp=Modbus_A6_Speed*20/100;
	 //       speedup_steps=1;
		}
	
	 flagtingji8=0;     
	 flagyunxing8=1;
	 step_add=1;  
	 
	 ModBus_Run_Flag=1;

	//Timer1Init();
	//Timer0Disable();
	ModBus_SetSpeedAndTime(0,Modbus_A6_SpeedTemp,Modbus_A6_AddSpeedTime,Modbus_A6_DecSpeedTime);
	ModBus_WirteBlock(0,0x1,0,0,0,rollsteps1); // д�����Ŀ��ֵ
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //������ת  ����STB  STB����ON
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //�ر�STB STB����OFF
	
	}

}



//�ŷ�����
void Modbus_ACServoOn(void)
{
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRES60,MODBUS_SERVO_ON);
}



//�ŷ��ر�
void Modbus_ACServoOff(void)
{
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRES60,MODBUS_SERVO_OFF);
}


void Modbus_ACServoStop(void)
{
//��ʱֹͣ
flagtingji8=1;     
flagyunxing8=0; 
t0zhongduan=1;//0;
flagone=0;
flagqyx=0;



//װ�ض���
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB123,MODBUS_SERVO_ON); //��ʱֹͣ�� H_STOP-ON    H_STOP���͹���Ҫ����ִ�С� ���HSTOP һֱ����ON�������������ת
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB123,MODBUS_SERVO_OFF); //��ʱֹͣ��  H_STOP����OFF

//Timer1Disable();
//Timer0Init(); 
if(flagyd==1)
	{
	 flagyd=0;
	}
	
RunStop_flag=0;
LowerAC_SPD_flag=0;

stop_time=0;
Run_flag=0;	
if(ACServoDrvErr_flag==0)
	RLOUT1_OFF;    // �������------------------++++++++++++++


/*
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB123,MODBUS_SERVO_ON); //��ʱֹͣ�� H_STOP-ON    H_STOP���͹���Ҫ����ִ�С� ���HSTOP һֱ����ON�������������ת
ModBusWaitTime=20;//�ȴ�20mS
ModBusWaitTime_Flag=1;//������ʱ
while(ModBusWaitTime_Flag==1);//�ȴ�
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB123,MODBUS_SERVO_OFF); //��ʱֹͣ��  H_STOP����OFF
ModBusWaitTime=20;//�ȴ�20mS
ModBusWaitTime_Flag=1;//������ʱ
while(ModBusWaitTime_Flag==1);//�ȴ�
*/

}



void Modbus_ACServoMoveBack_MID_SPD(void)    //�����ŷ�  ���ٺ���
{

houtui=1;
qianjin=0;   

step_add=10;   

step_ground=11; 

speedup_steps=40;
status=1;
flagqyx=2;
 

ModBus_SetSpeedAndTime(0,800,1000,1000);
ModBus_WirteBlock(0,0x1,0,0,0,-10000000); // д�����Ŀ��ֵ
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //������ת  ����STB  STB����ON
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //�ر�STB STB����OFF

//Timer1Init();
//Timer0Disable(); 
//BellOUT_OFF;

RLOUT1_ON;    // ������жϿ�
CutPermit_flag=0;
}



void Modbus_ACServoMoveFwd_MID_SPD(void)  //�����ŷ�  ����ǰ��
{

	 houtui=0;
qianjin=1;   

step_add=10;   

step_ground=11; 

speedup_steps=40;
status=1;
 flagqyx=2;
 
ModBus_SetSpeedAndTime(0,800,1000,1000);
ModBus_WirteBlock(0,0x1,0,0,0,10000000); // д�����Ŀ��ֵ
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //������ת  ����STB  STB����ON
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //�ر�STB STB����OFF

//Timer1Init();
//Timer0Disable(); 
//BellOUT_OFF;

RLOUT1_ON;    // ������жϿ�
CutPermit_flag=0;

}


void Modbus_ACMotorShouLun(void)//���ִ���
{
unsigned int targ;
unsigned int tempqianjin1;
unsigned int rollsteps1;
if(ModBus_QueueLoadCou<11)
	{
targ=BackLimit;
A6_CalPulsSize();//����һ�������
if(targ>CurrentSize)
	{
	tempqianjin1=(targ-CurrentSize);

    rollsteps1=tempqianjin1*100/Modbus_A6_PulsSize;//-yushu;

	ModBus_SetSpeedAndTime(0,Modbus_A6_ManualSpeed*40/100,100,100);
	ModBus_WirteBlock(0,0x1,0,0,0,ShouLunlunSize); // д�����Ŀ��ֵ
	//ModBus_WirteBlock(0,0x1,0,0,0,0-rollsteps1); // д�����Ŀ��ֵ
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //������ת  ����STB  STB����ON
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //�ر�STB STB����OFF

	}
	}
}


void Modbus_ACMotorDDBack(void)//�������ֵ㶯  ����
{

unsigned int targ;
unsigned int tempqianjin1;
unsigned int rollsteps1;
if(ModBus_QueueLoadCou<11)
	{
targ=BackLimit;
A6_CalPulsSize();//����һ�������
if(targ>CurrentSize)
	{
	tempqianjin1=(targ-CurrentSize);

    rollsteps1=tempqianjin1*100/Modbus_A6_PulsSize;//-yushu;

	ModBus_SetSpeedAndTime(0,Modbus_A6_ManualSpeed*40/100,100,100);
	ModBus_WirteBlock(0,0x1,0,0,0,-1); // д�����Ŀ��ֵ
	//ModBus_WirteBlock(0,0x1,0,0,0,0-rollsteps1); // д�����Ŀ��ֵ
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //������ת  ����STB  STB����ON
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //�ر�STB STB����OFF

	}
	}
}

void Modbus_ACMotorDDForward(void)//ǰ��
{
unsigned int targ;
unsigned int tempqianjin1;
unsigned int rollsteps1;
if(ModBus_QueueLoadCou<11)
	{
if(OIN4_PIN!=0)  //�а� �ź�
	{	
	targ=MiddleLimit;
	}
else
		targ=FrontLimit;//Modbus_ACMotorRunStart(FrontLimit);

A6_CalPulsSize();//����һ�������
if(targ<CurrentSize)
	{
	tempqianjin1=(CurrentSize-targ);
    rollsteps1=tempqianjin1*100/Modbus_A6_PulsSize;//-yushu;   

	ModBus_SetSpeedAndTime(0,Modbus_A6_ManualSpeed*40/100,100,100);
	ModBus_WirteBlock(0,0x1,0,0,0,1); // д�����Ŀ��ֵ
	//ModBus_WirteBlock(0,0x1,0,0,0,rollsteps1); // д�����Ŀ��ֵ
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //������ת  ����STB  STB����ON
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //�ر�STB STB����OFF

	}
	}
}



void Modbus_ACMotorGoBack(void)//����
{

	
unsigned int targ;
unsigned int tempqianjin1;
unsigned int rollsteps1;
/*
if(OIN4_PIN!=0)  //�а� �ź�
	{	
	targ=MiddleLimit;
	//Modbus_ACMotorRunStart(MiddleLimit);
	}
else
		targ=FrontLimit;//Modbus_ACMotorRunStart(FrontLimit);
		*/
targ=BackLimit;
A6_CalPulsSize();//����һ�������
if(targ>CurrentSize)
	{

	//tempqianjin1=(CurrentSize-vbcd)*2;
	//rollsteps1=tempqianjin1-yushu;
	tempqianjin1=(targ-CurrentSize);

    rollsteps1=tempqianjin1*100/Modbus_A6_PulsSize;//-yushu;


qianjin=0;
flagqyx=2;
 flagyd=1;

step_add=60;   
step_ground=11; 

speedup_steps=30;
houtui=1; 
status=1;

flagtingji8=0;
flagyunxing8=1;  


	ModBus_SetSpeedAndTime(0,Modbus_A6_ManualSpeed*40/100,1000,1000);
	ModBus_WirteBlock(0,0x1,0,0,0,0-rollsteps1); // д�����Ŀ��ֵ
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //������ת  ����STB  STB����ON
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //�ر�STB STB����OFF

	/*
ModBus_SetSpeedAndTime(0,1000,1000,1000);
ModBus_WirteBlock(0,0x1,0,0,0,-10000000); // д�����Ŀ��ֵ
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //������ת  ����STB  STB����ON
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //�ر�STB STB����OFF
*/

//Timer1Init();
//Timer0Disable();

RLOUT1_ON;    // ������жϿ�
CutPermit_flag=0;
	}


	/*
qianjin=0;
flagqyx=2;
flagyd=1;

step_add=25;   
step_ground=11; 

speedup_steps=30;
houtui=1; 
status=1;

flagtingji8=0;
flagyunxing8=1;  

//Timer1Init();
//Timer0Disable();

ModBus_SetSpeedAndTime(0,500,1000,1000);
ModBus_WirteBlock(0,0x1,0,0,0,-10000000); // д�����Ŀ��ֵ
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //������ת  ����STB  STB����ON
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //�ر�STB STB����OFF


RLOUT1_ON;    // ������жϿ�
CutPermit_flag=0;
*/
}

void Modbus_ACMotorGoFastBack(void)//���ٺ���
{

unsigned int targ;
unsigned int tempqianjin1;
unsigned int rollsteps1;
/*
if(OIN4_PIN!=0)  //�а� �ź�
	{	
	targ=MiddleLimit;
	//Modbus_ACMotorRunStart(MiddleLimit);


}

else
		targ=FrontLimit;//Modbus_ACMotorRunStart(FrontLimit);
		*/
targ=BackLimit;
A6_CalPulsSize();//����һ�������
if(targ>CurrentSize)
{

	//tempqianjin1=(CurrentSize-vbcd)*2;
	//rollsteps1=tempqianjin1-yushu;
	tempqianjin1=(targ-CurrentSize);

    rollsteps1=tempqianjin1*100/Modbus_A6_PulsSize;//-yushu;


qianjin=0;
flagqyx=2;
 flagyd=1;

step_add=60;   
step_ground=11; 

speedup_steps=30;
houtui=1; 
status=1;

flagtingji8=0;
flagyunxing8=1;  


	ModBus_SetSpeedAndTime(0,Modbus_A6_ManualSpeed,1000,1000);
	ModBus_WirteBlock(0,0x1,0,0,0,0-rollsteps1); // д�����Ŀ��ֵ
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //������ת  ����STB  STB����ON
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //�ر�STB STB����OFF

	/*

ModBus_SetSpeedAndTime(0,1000,1000,1000);
ModBus_WirteBlock(0,0x1,0,0,0,-10000000); // д�����Ŀ��ֵ
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //������ת  ����STB  STB����ON
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //�ر�STB STB����OFF
*/

//Timer1Init();
//Timer0Disable();

RLOUT1_ON;    // ������жϿ�
CutPermit_flag=0;
	}

}


void Modbus_ACMotorGoForward(void)//ǰ��
{
unsigned int targ;
unsigned int tempqianjin1;
unsigned int rollsteps1;

if(OIN4_PIN!=0)  //�а� �ź�
	{	
	targ=MiddleLimit;
	//Modbus_ACMotorRunStart(MiddleLimit);
	}
else
		targ=FrontLimit;//Modbus_ACMotorRunStart(FrontLimit);

A6_CalPulsSize();//����һ�������
if(targ<CurrentSize)
	{

	//tempqianjin1=(CurrentSize-vbcd)*2;
	//rollsteps1=tempqianjin1-yushu;
	tempqianjin1=(CurrentSize-targ);

    rollsteps1=tempqianjin1*100/Modbus_A6_PulsSize;//-yushu;


	flagyd=1;       
	flagqyx=1;
	
	qianjin=1;

	step_add=60;      
	step_ground=11; 

	speedup_steps=30;
	status=1;      
	houtui=0; 
 
	flagtingji8=0;
	flagyunxing8=1;      


	ModBus_SetSpeedAndTime(0,Modbus_A6_ManualSpeed*40/100,1000,1000);
	ModBus_WirteBlock(0,0x1,0,0,0,rollsteps1); // д�����Ŀ��ֵ
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //������ת  ����STB  STB����ON
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //�ر�STB STB����OFF




/*
ModBus_SetSpeedAndTime(0,1000,1000,1000);
ModBus_WirteBlock(0,0x1,0,0,0,10000000); // д�����Ŀ��ֵ
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //������ת  ����STB  STB����ON
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //�ر�STB STB����OFF
*/


//Timer1Init();
//Timer0Disable();

	RLOUT1_ON;    // ������жϿ�
	CutPermit_flag=0;
	}

	/*

	flagyd=1;       
flagqyx=1;

qianjin=1;

step_add=25;      
step_ground=11; 

speedup_steps=30;
status=1;      
houtui=0; 
 
flagtingji8=0;
flagyunxing8=1;      




ModBus_SetSpeedAndTime(0,500,1000,1000);
ModBus_WirteBlock(0,0x1,0,0,0,10000000); // д�����Ŀ��ֵ
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //������ת  ����STB  STB����ON
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //�ر�STB STB����OFF

//Timer1Init();
//Timer0Disable();
RLOUT1_ON;    // ������жϿ�
CutPermit_flag=0;
*/


}

void Modbus_ACMotorGoFastForward(void)//����ǰ��
{
unsigned int targ;
unsigned int tempqianjin1;
unsigned int rollsteps1;

if(OIN4_PIN!=0)  //�а� �ź�
	{	
	targ=MiddleLimit;
	//Modbus_ACMotorRunStart(MiddleLimit);
	}
else
		targ=FrontLimit;//Modbus_ACMotorRunStart(FrontLimit);

A6_CalPulsSize();//����һ�������
if(targ<CurrentSize)
	{

	//tempqianjin1=(CurrentSize-vbcd)*2;
	//rollsteps1=tempqianjin1-yushu;
	tempqianjin1=(CurrentSize-targ);

    rollsteps1=tempqianjin1*100/Modbus_A6_PulsSize;//-yushu;


	flagyd=1;       
	flagqyx=1;
	
	qianjin=1;

	step_add=60;      
	step_ground=11; 

	speedup_steps=30;
	status=1;      
	houtui=0; 
 
	flagtingji8=0;
	flagyunxing8=1;      


	ModBus_SetSpeedAndTime(0,Modbus_A6_ManualSpeed,1000,1000);
	ModBus_WirteBlock(0,0x1,0,0,0,rollsteps1); // д�����Ŀ��ֵ
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //������ת  ����STB  STB����ON
	ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //�ر�STB STB����OFF




/*

ModBus_SetSpeedAndTime(0,1000,1000,1000);
ModBus_WirteBlock(0,0x1,0,0,0,10000000); // д�����Ŀ��ֵ
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //������ת  ����STB  STB����ON
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //�ر�STB STB����OFF
*/


//Timer1Init();
//Timer0Disable();

	RLOUT1_ON;    // ������жϿ�
	CutPermit_flag=0;
	}
}



void Modbus_ACMotor_ReleaseStop(void)
{
flagkey=0;
flagkeysong=1;
// flagyici=0;
 flagtime1=0;
flagyunxing8=0;

/*
if(flagyd==1)
	{
	 flagyd=0;
	 
	   flagzhiyou=0;
	   flagtingji8=1;
	   flagyunxing8=0;
	  // keytingji=0;
	   flagqyx=0;
  
	  flagtingji8=1;
   
	 Timer1Disable();
	 Timer0Init();
	}
	*/

}

void Modbus_ACServoMoveBack_LOW_SPD(void)
{

step_add=50;
step_ground=11; 
speedup_steps=40;  

status=4;   


ModBus_SetSpeedAndTime(0,200,1000,1000);
ModBus_WirteBlock(0,0x1,0,0,0,-10000000); // д�����Ŀ��ֵ
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //������ת  ����STB  STB����ON
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //�ر�STB STB����OFF

//Timer1Init();
//Timer0Disable(); 
//BellOUT_OFF;

RLOUT1_ON;    // ������жϿ�
CutPermit_flag=0;

}





void ModBus_Test(void)
{
int i;
	ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4202,0x02);//������λ��

	// ModBusWaitTime=20;//�ȴ�20mS
	// ModBusWaitTime_Flag=1;//������ʱ
	// while(ModBusWaitTime_Flag==1);//�ȴ�

	ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4204,0x02);//��Ȧ����
	// ModBusWaitTime=20;//�ȴ�20mS
	// ModBusWaitTime_Flag=1;//������ʱ
	// while(ModBusWaitTime_Flag==1);//�ȴ�


ModBus_WirteBlockSpeed(0,1500);//�趨ת��
// ModBusWaitTime=20;//�ȴ�20mS
// ModBusWaitTime_Flag=1;//������ʱ
// while(ModBusWaitTime_Flag==1);//�ȴ�

ModBus_WirteBlockAddTime(0,1000);//�趨���ٶ�ʱ��
// ModBusWaitTime=20;//�ȴ�20mS
// ModBusWaitTime_Flag=1;//������ʱ
// while(ModBusWaitTime_Flag==1);//�ȴ�

ModBus_WirteBlockDecTime(0,1000);//�趨���ٶ�ʱ��
// ModBusWaitTime=20;//�ȴ�20mS
// ModBusWaitTime_Flag=1;//������ʱ
// while(ModBusWaitTime_Flag==1);//�ȴ�

ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRES60,MODBUS_SERVO_OFF);
// ModBusWaitTime=100;//�ȴ�20mS
// ModBusWaitTime_Flag=1;//������ʱ
// while(ModBusWaitTime_Flag==1);//�ȴ�

ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRES60,MODBUS_SERVO_ON);
// ModBusWaitTime=200;//�ȴ�20mS
// ModBusWaitTime_Flag=1;//������ʱ
// while(ModBusWaitTime_Flag==1);//�ȴ�

// ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_WRITE,0x4300,0x0055);//��Ȩ��

ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES600F,0x02);//��ȡ��ǰֵ
// ModBusWaitTime=20;//�ȴ�20mS
// ModBusWaitTime_Flag=1;//������ʱ
// while(ModBusWaitTime_Flag==1);//�ȴ�


/*
ModBus_WirteBlock(0,0x1,0,0,0,50000); // д�����Ŀ��ֵ
ModBusWaitTime=20;//�ȴ�20mS
ModBusWaitTime_Flag=1;//������ʱ
while(ModBusWaitTime_Flag==1);//�ȴ�

ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_WRITE,A6_REGISTER_ADDRES4414,0);  //ָ��ҪBlock 0����
ModBusWaitTime=20;//�ȴ�20mS
ModBusWaitTime_Flag=1;//������ʱ
while(ModBusWaitTime_Flag==1);//�ȴ�


ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //������ת  ����STB  STB����ON
ModBusWaitTime=20;//�ȴ�20mS
ModBusWaitTime_Flag=1;//������ʱ
while(ModBusWaitTime_Flag==1);//�ȴ�
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //�ر�STB STB����OFF
ModBusWaitTime=20;//�ȴ�20mS
ModBusWaitTime_Flag=1;//������ʱ
while(ModBusWaitTime_Flag==1);//�ȴ�

ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES600F,0x2);//��ȡ��ǰֵ
ModBusWaitTime=20;//�ȴ�20mS
ModBusWaitTime_Flag=1;//������ʱ
while(ModBusWaitTime_Flag==1);//�ȴ�


ModBus_WirteBlock(0,0x1,0,0,0,80000); // д�����Ŀ��ֵ
ModBusWaitTime=100;//�ȴ�20mS
ModBusWaitTime_Flag=1;//������ʱ
while(ModBusWaitTime_Flag==1);//�ȴ�



//**************************************
//���²��Լ�ʱֹͣ

//����ת���

ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //������ת  ����STB  STB����ON
ModBusWaitTime=20;//�ȴ�20mS
ModBusWaitTime_Flag=1;//������ʱ
while(ModBusWaitTime_Flag==1);//�ȴ�
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //�ر�STB STB����OFF
ModBusWaitTime=20;//�ȴ�20mS
ModBusWaitTime_Flag=1;//������ʱ
while(ModBusWaitTime_Flag==1);//�ȴ�

*/

/*
//��ʱֹͣ
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB123,MODBUS_SERVO_ON); //��ʱֹͣ�� H_STOP-ON    H_STOP���͹���Ҫ����ִ�С� ���HSTOP һֱ����ON�������������ת
ModBusWaitTime=20;//�ȴ�20mS
ModBusWaitTime_Flag=1;//������ʱ
while(ModBusWaitTime_Flag==1);//�ȴ�
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB123,MODBUS_SERVO_OFF); //��ʱֹͣ��  H_STOP����OFF
ModBusWaitTime=20;//�ȴ�20mS
ModBusWaitTime_Flag=1;//������ʱ
while(ModBusWaitTime_Flag==1);//�ȴ�


//**************************************
//���²��Լ���ֹͣ

//����ת���

ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_ON);  //������ת  ����STB  STB����ON
ModBusWaitTime=20;//�ȴ�20mS
ModBusWaitTime_Flag=1;//������ʱ
while(ModBusWaitTime_Flag==1);//�ȴ�
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB120,MODBUS_SERVO_OFF); //�ر�STB STB����OFF
ModBusWaitTime=20;//�ȴ�20mS
ModBusWaitTime_Flag=1;//������ʱ
while(ModBusWaitTime_Flag==1);//�ȴ�

*/
/*
//����ֹͣ
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB124,MODBUS_SERVO_ON); //����ֹͣ�� S_STOP-ON    S_STOP���͹���Ҫ����ִ�С� ���S-STOP һֱ����ON�������������ת
ModBusWaitTime=20;//�ȴ�20mS
ModBusWaitTime_Flag=1;//������ʱ
while(ModBusWaitTime_Flag==1);//�ȴ�
ModBus_SendFrame(0x1,A6_COMMAND_COIL_WRITE,A6_COIL_ADDRESB124,MODBUS_SERVO_OFF); //����ֹͣ��  S_STOP����OFF
ModBusWaitTime=20;//�ȴ�20mS
ModBusWaitTime_Flag=1;//������ʱ
while(ModBusWaitTime_Flag==1);//�ȴ�

*/


}



void Modbus_A6_SaveSetData(void)
{
unsigned char *ptr;

ptr=(unsigned char *)(DOWNFILE_SDRAM_ADD); //���صĵ�ַ

//�ݾ�
*ptr++=Modbus_A6_LuoJu;

Modbus_A6_Puls=2000;//�̶���2000����/ת
//��������
*ptr++=(unsigned char)(Modbus_A6_Puls>>8);
*ptr++=(unsigned char)Modbus_A6_Puls;


//���ٱ�
*ptr++=Modbus_A6_JianSuBi;


//����ٶ�
*ptr++=(unsigned char)(Modbus_A6_Speed>>8);
*ptr++=(unsigned char)Modbus_A6_Speed;



//�ֶ��ٶ�
*ptr++=(unsigned char)(Modbus_A6_ManualSpeed>>8);
*ptr++=(unsigned char)Modbus_A6_ManualSpeed;



//����ʱ��
*ptr++=(unsigned char)(Modbus_A6_AddSpeedTime>>8);
*ptr++=(unsigned char)Modbus_A6_AddSpeedTime;


//����ʱ��
*ptr++=(unsigned char)(Modbus_A6_DecSpeedTime>>8);
*ptr++=(unsigned char)Modbus_A6_DecSpeedTime;


//��׼
*ptr++=(unsigned char)(Modbus_A6_JiZhunMark>>24);
*ptr++=(unsigned char)(Modbus_A6_JiZhunMark>>16);
*ptr++=(unsigned char)(Modbus_A6_JiZhunMark>>8);
*ptr++=(unsigned char)Modbus_A6_JiZhunMark;


//��׼ ������ֵ
*ptr++=(unsigned char)(Modbus_A6_JiZhunDesmion>>24);
*ptr++=(unsigned char)(Modbus_A6_JiZhunDesmion>>16);
*ptr++=(unsigned char)(Modbus_A6_JiZhunDesmion>>8);
*ptr++=(unsigned char)Modbus_A6_JiZhunDesmion;

//��׼  Ȧ��
//*ptr++=(unsigned char)(Modbus_A6_JiZhunQuan>>24);
//*ptr++=(unsigned char)(Modbus_A6_JiZhunQuan>>16);
*ptr++=(unsigned char)(Modbus_A6_JiZhunQuan>>8);
*ptr++=(unsigned char)Modbus_A6_JiZhunQuan;



NandEccWrite_Flag=0;
iFiles.FileLength=64;//��ȡ�ļ�����	
ChangeFileName("ModbusA6.ini");
File_Create(iFiles.FileName);//�����ļ�

}



void Modbus_A6_LoadSetData(void)
{

unsigned char *ptr;

ptr=(unsigned char *)(DOWNFILE_SDRAM_ADD); //���صĵ�ַ


FileRead("ModbusA6.ini",(unsigned char*)DOWNFILE_SDRAM_ADD);


//�ݾ�
Modbus_A6_LuoJu=*ptr++;


//��������
Modbus_A6_Puls=(unsigned short)(*ptr++<<8);
Modbus_A6_Puls+=*ptr++;

Modbus_A6_Puls=2000;//�̶���2000����/ת

//���ٱ�
Modbus_A6_JianSuBi=*ptr++;


//����ٶ�


Modbus_A6_Speed=(unsigned short)(*ptr++<<8);
Modbus_A6_Speed+=*ptr++;



//�ֶ��ٶ�
Modbus_A6_ManualSpeed=(unsigned short)(*ptr++<<8);
Modbus_A6_ManualSpeed+=*ptr++;




//����ʱ��

Modbus_A6_AddSpeedTime=(unsigned short)(*ptr++<<8);
Modbus_A6_AddSpeedTime+=*ptr++;



//����ʱ��

Modbus_A6_DecSpeedTime=(unsigned short)(*ptr++<<8);
Modbus_A6_DecSpeedTime+=*ptr++;


//��׼
Modbus_A6_JiZhunMark=(unsigned int)(*ptr++<<24);//=(unsigned char)(Modbus_A6_JiZhunMark>>24);
Modbus_A6_JiZhunMark+=(unsigned int)(*ptr++<<16);//*ptr++=(unsigned char)(Modbus_A6_JiZhunMark>>16);
Modbus_A6_JiZhunMark+=(unsigned int)(*ptr++<<8);//*ptr++=(unsigned char)(Modbus_A6_JiZhunMark>>8);
Modbus_A6_JiZhunMark+=(unsigned int)(*ptr++);//*ptr++=(unsigned char)Modbus_A6_JiZhunMark;


//��׼ ������ֵ

Modbus_A6_JiZhunDesmion=(unsigned int)(*ptr++<<24);//=(unsigned char)(Modbus_A6_JiZhunMark>>24);
Modbus_A6_JiZhunDesmion+=(unsigned int)(*ptr++<<16);//*ptr++=(unsigned char)(Modbus_A6_JiZhunMark>>16);
Modbus_A6_JiZhunDesmion+=(unsigned int)(*ptr++<<8);//*ptr++=(unsigned char)(Modbus_A6_JiZhunMark>>8);
Modbus_A6_JiZhunDesmion+=(unsigned int)(*ptr++);//*ptr++=(unsigned char)Modbus_A6_JiZhunMark;



//��׼  Ȧ��


//Modbus_A6_JiZhunQuan=(unsigned int)(*ptr++<<24);//=(unsigned char)(Modbus_A6_JiZhunMark>>24);
//Modbus_A6_JiZhunQuan+=(unsigned int)(*ptr++<<16);//*ptr++=(unsigned char)(Modbus_A6_JiZhunMark>>16);
Modbus_A6_JiZhunQuan=(unsigned short)(*ptr++<<8);//*ptr++=(unsigned char)(Modbus_A6_JiZhunMark>>8);
Modbus_A6_JiZhunQuan+=(unsigned short)(*ptr++);//*ptr++=(unsigned char)Modbus_A6_JiZhunMark;


/***
if(((Modbus_A6_LuoJu<1)||(Modbus_A6_LuoJu>20))||
	((Modbus_A6_Puls<500)||(Modbus_A6_Puls>10000))||
	((Modbus_A6_JianSuBi<1)||(Modbus_A6_JianSuBi>5))||
	((Modbus_A6_Speed<200)||(Modbus_A6_Speed>3000))||
	((Modbus_A6_AddSpeedTime<100)||(Modbus_A6_AddSpeedTime>2000))||
	((Modbus_A6_DecSpeedTime<100)||(Modbus_A6_DecSpeedTime>2000))||
	((Modbus_A6_JiZhunMark<1000)||(Modbus_A6_JiZhunMark>300000))||
	((Modbus_A6_ManualSpeed<200)||(Modbus_A6_ManualSpeed>3000)))
	{//���ݲ��ڷ�Χ�ڣ����³�ʼ��
	Modbus_A6_LuoJu=12;
	Modbus_A6_Puls=2000;
	Modbus_A6_JianSuBi=1;
	Modbus_A6_Speed=1800;
	Modbus_A6_ManualSpeed=1000;
	Modbus_A6_AddSpeedTime=500;
	Modbus_A6_DecSpeedTime=500;
	Modbus_A6_JiZhunMark=50000;
	Modbus_A6_SaveSetData();
	}
	**/
	Modbus_A6_LuoJu=10;
	// Modbus_A6_JiZhunMark=123450;
	Modbus_A6_SaveSetData();
}

void Modbus_A6_SaveErrData(void)//����������
{
unsigned int *ptr;
int i;

ptr=(unsigned int *)(DOWNFILE_SDRAM_ADD); //���صĵ�ַ
for(i=0;i<16;i++)
	{
	*ptr++=ModBus_AcErr_HisData[i];
	}

NandEccWrite_Flag=0;
iFiles.FileLength=64;//��ȡ�ļ�����	
ChangeFileName("ModbusA6Err.ini");
File_Create(iFiles.FileName);//�����ļ�

}
void Modbus_A6_LoadErrData(void) //����������
{

unsigned int *ptr;
int i;

ptr=(unsigned int *)(DOWNFILE_SDRAM_ADD); //���صĵ�ַ


FileRead("ModbusA6Err.ini",(unsigned char*)DOWNFILE_SDRAM_ADD);

for(i=0;i<16;i++)
	{
	ModBus_AcErr_HisData[i]=*ptr++;
	}
}
















//--------------
void ModbusComm_CtrlExec(void)
{
if(SendCmdOn_flag==0)	//����------------->>>>>>
	{
	if(ModBus_QueueLoadCou>0)
		{
		ModBus_CommCou=0;
		ModBus_CommEnd_Flag=0;
		// if(ACServoDrvErr_flag==0)
			{
			ModBus_Queue_SendBuf(1,0);//
			SendCmdOn_flag=1;
			SendCmdWaitTime=0;
			}
		}
	}


if(ModBus_CommEnd_Flag==1)		//����----------<<<<<
	{
	switch(ModBus_CurCommand)
		{
		case A6_COMMAND_REGISTER_READ://��ȡ �Ĵ���
				switch(ModBus_CurAdder)
					{
					case A6_REGISTER_ADDRES4202://������λ��
						ModBus_CurDesmion=(unsigned int)ModBus_Rec_Data[5]<<24;
						ModBus_CurDesmion+=(unsigned int)ModBus_Rec_Data[6]<<16;
						ModBus_CurDesmion+=(unsigned int)ModBus_Rec_Data[3]<<8;
						ModBus_CurDesmion+=(unsigned int)ModBus_Rec_Data[4];
						ModBus_CodeDataMode|=0x01;
						break;
					case A6_REGISTER_ADDRES4204://��Ȧ����
						ModBus_QuanData=(unsigned int)ModBus_Rec_Data[5]<<24;
						ModBus_QuanData+=(unsigned int)ModBus_Rec_Data[6]<<16;
						ModBus_QuanData+=(unsigned int)ModBus_Rec_Data[3]<<8;
						ModBus_QuanData+=(unsigned int)ModBus_Rec_Data[4];
						ModBus_CodeDataMode|=0x10;
						break;
					case A6_REGISTER_ADDRES4001://�������
						ModBus_ACErr=(unsigned int)ModBus_Rec_Data[3]<<8;
						ModBus_ACErr+=(unsigned int)ModBus_Rec_Data[4];
						break;
					}
					break;
		case A6_COMMAND_COIL_READ:
				switch(ModBus_CurAdder)
					{
					case 0x0102:
						ModBus_BackStatus=ModBus_Rec_Data[3];
					//	unsigned char ModBus_BackStatus,ModBus_ForwardStatus;
						break;
					case 0x0103:
						ModBus_ForwardStatus=ModBus_Rec_Data[3];
						if(Run_flag==1)
							{
							if((ModBus_BackStatus==0)&&(ModBus_ForwardStatus==0))
								{
								 // if(houtui==1)
									// {
									 // if(((CurrentSize>TargetSize+500-5))&&((CurrentSize<TargetSize+500+5)))
										// {
										 // Modbus_ACServoStop();
										 // ModBus_WaitRun_Flag=1;
										// }
									// }
								// else
									// {
									// if(((CurrentSize>TargetSize-5))&&((CurrentSize<TargetSize+5)))
										// {
										 // Modbus_ACServoStop();
										// }
									// }
								 }
							}
						break;	
					}
				break;
		}
	ModBus_CommEnd_Flag=0;
	ModBus_Queue_ChangeBuf();	//������λ
	SendCmdOn_flag=0;	
	SendCmdWaitTime=0;
	ModBus_Comm_LinkErr=0;
	}
else		//------δ���յ�����-----
	{
	if(SendCmdOn_flag==1)	//����  �ѷ���
		{
		SendCmdWaitTime++;
		if(SendCmdWaitTime>=500)	//���ݷ��س�ʱ ����
			{
			SendCmdWaitTime=0;
			SendCmdOn_flag=0;
			ModBus_Comm_LinkErr=1;//ͨѶ���Ӵ���
			ModBus_QueueLoadCou=0;
			}
		}
	else
		{
		ReadErrorTime++;
		if(ReadErrorTime>=2000)//���  2000ms
			{
			ReadErrorTime=0;
			if(A6ReadCoderSizeWaitTime>=5000)//5s ���ٱ�������
				ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4001,1);//���������
			}
		}
	}
if(A6ReadCoderSizeWaitTime<5000)//5s
	A6ReadCoderSizeWaitTime++;	
	
}


void ReadCurrentSize_A6Coder(void)//��ȡ��ǰ ������ֵ
{
if(MotorType>=MOTOR_AC_A6_SERVO)
	{
	ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4202,0x02);//������λ��
	ModBus_SendFrame(0x1,A6_COMMAND_REGISTER_READ,A6_REGISTER_ADDRES4204,0x02);//��Ȧ����
	ModBus_CodeDataMode=0;
	ReadErrorTime=0;
	A6ReadCoderSizeWaitTime=0;
	}
}

void SaveA6OriginalBenchMark(void)//A6��׼ ����
{
	Modbus_A6_JiZhunDesmion=ModBus_CurDesmion;
	Modbus_A6_JiZhunQuan=ModBus_QuanData;
	
	// Modbus_A6_SaveSetData();
	SaveA6MarkBenchSize();//A6 ������ ��׼ֵ(6 Byte)
	ModBus_AcErr_HisData[0]=0;
	Modbus_A6_SaveErrData();
}
