#ifndef __MODBUS_H
#define __MODBUS_H


#include"main.h"

#define AC_ERR_Z	1	//Z �������
#define AC_ERR_CODE	2	//������err ����
#define AC_ERR_LINK	3	//ͨѶ����



#define CRC_SEED   0xFFFF   // ��λ��ΪԤ��ֵ��ʹ���˹��㷨����������ʱ ��Ҫ����������ʽ�������ְλ ��� �����ܵõ����ĳ�������ʽ
#define POLY16 0x1021  // ��λΪ��ʽ��д ʵ��Ϊ0x11021

#define CRC_16_POLYNOMIALS 0x8005

#define MODBUS_SERVO_COMMADD 0x01
#define MODBUS_SERVO_ON 0xFF00
#define MODBUS_SERVO_OFF 0x0000
/**
#define RS485_PIN 6 
#define RS485_SEND()  P3_OUTP_SET=(1<<RS485_PIN)
#define RS485_RECV()  P3_OUTP_CLR=(1<<RS485_PIN)
*/




#define RS485_CS_PIN BIT2

//ver1.4 IO==
#define RS485_IO_FUN() (GPIO_OpenBit(GPIOH, RS485_CS_PIN, DIR_OUTPUT, NO_PULL_UP))//P1_MUX_SET_bit.P1_20=1//IO mode
#define RS485_CS_OUT()	 (GPIO_OpenBit(GPIOH, RS485_CS_PIN, DIR_OUTPUT, NO_PULL_UP))//GPIO_ClrBit(GPIOD, LED0)//P1_DIR_SET_bit.P1_20=1//out mode
#define RS485_SEND()  GPIO_SetBit(GPIOH, RS485_CS_PIN)//P1_OUTP_SET_bit.P1_20=1
#define RS485_RECV()  GPIO_ClrBit(GPIOH, RS485_CS_PIN)//P1_OUTP_CLR_bit.P1_20=1
//ver1.4 IO==

#define MODBUS_COMMHEAD1 0xaa
#define MODBUS_COMMHEAD2 0x55
#define MODBUS_COMMD_WRITE_BMP_FLASH 0x1
#define MODBUS_COMMD_WRITE_FILE_FLASH 0x2
#define MODBUS_COMMD_READ_FLASH_SDRAM 0x3
#define MODBUS_COMMD_WRITE_SDRAM_FLASH 0x4
#define MODBUS_COMMD_ERASE_FLASH 0x5
#define MODBUS_COMMD_CLR_SCREEN 0x6
#define MODBUS_COMMD_DISPLAY_BMP 0x7
#define MODBUS_COMMD_WRITE_SPI_FLASH 0x8


#define MODBUS_COMMMODBUS_COMMDADD 2
#define MODBUS_COMMADDERADD 3
#define MODBUS_COMMLENTHADD 6



#define A6_COMMAND_COIL_WRITE 0x05
#define A6_COMMAND_COIL_READ 0x01
#define A6_COMMAND_REGISTER_WRITE 0x06
#define A6_COMMAND_REGISTER_READ 0x03
#define A6_COMMAND_POSITION  0x04 

#define A6_COMMAND_REGISTER_CWRITE 0x10


#define COIL_OFF 0x0000   //SV-OFF,STB_OFF
#define COIL_ON 0xFF00    //SV-ON,STB_ON

#define A6_COIL_ADDRES0 0x0000
#define A6_COIL_ADDRES1 0x0001
#define A6_COIL_ADDRES2 0x0002
#define A6_COIL_ADDRES3 0x0003
#define A6_COIL_ADDRES4 0x0004
#define A6_COIL_ADDRES5 0x0005
#define A6_COIL_ADDRES6 0x0006
#define A6_COIL_ADDRES7 0x0007
#define A6_COIL_ADDRES8 0x0008
#define A6_COIL_ADDRES9 0x0009

#define A6_COIL_ADDRES20 0x0020
#define A6_COIL_ADDRES21 0x0021
#define A6_COIL_ADDRES22 0x0022
#define A6_COIL_ADDRES23 0x0023
#define A6_COIL_ADDRES24 0x0024
#define A6_COIL_ADDRES25 0x0025
#define A6_COIL_ADDRES26 0x0026
#define A6_COIL_ADDRES27 0x0027
#define A6_COIL_ADDRES28 0x0028
#define A6_COIL_ADDRES29 0x0029

#define A6_COIL_ADDRES2A 0x002A
#define A6_COIL_ADDRES2C 0x002C
#define A6_COIL_ADDRES2D 0x002D
#define A6_COIL_ADDRES32 0x0032
#define A6_COIL_ADDRES33 0x0033
#define A6_COIL_ADDRES34 0x0034
#define A6_COIL_ADDRES35 0x0035
#define A6_COIL_ADDRES36 0x0036
#define A6_COIL_ADDRES37 0x0037
#define A6_COIL_ADDRES38 0x0038
#define A6_COIL_ADDRES39 0x0039
#define A6_COIL_ADDRES3B 0x003B
#define A6_COIL_ADDRES3C 0x003C

#define A6_COIL_ADDRES60 0x0060		//R/W
#define A6_COIL_ADDRES61 0x0061		//R/W
#define A6_COIL_ADDRES67 0x0067		//R/W
#define A6_COIL_ADDRES69 0x0069		//R/W
#define A6_COIL_ADDRES72 0x0072		//R/W
#define A6_COIL_ADDRES73 0x0073		//R/W
#define A6_COIL_ADDRES75 0x0075		//R/W
#define A6_COIL_ADDRES76 0x0076		//R/W

#define A6_COIL_ADDRES80 0x0080
#define A6_COIL_ADDRES81 0x0081
#define A6_COIL_ADDRES82 0x0082
#define A6_COIL_ADDRES83 0x0083
#define A6_COIL_ADDRES84 0x0084
#define A6_COIL_ADDRES85 0x0085

#define A6_COIL_ADDRESA0 0x00A0
#define A6_COIL_ADDRESA1 0x00A1
#define A6_COIL_ADDRESA2 0x00A2
#define A6_COIL_ADDRESA3 0x00A3
#define A6_COIL_ADDRESA4 0x00A4
#define A6_COIL_ADDRESA5 0x00A5
#define A6_COIL_ADDRESA6 0x00A6
#define A6_COIL_ADDRESA9 0x00A9
#define A6_COIL_ADDRESAD 0x00AD
#define A6_COIL_ADDRESAF 0x00AF
#define A6_COIL_ADDRESB0 0x00B0
#define A6_COIL_ADDRESB1 0x00B1
#define A6_COIL_ADDRESB2 0x00B2
#define A6_COIL_ADDRESB3 0x00B3
#define A6_COIL_ADDRESB4 0x00B4
#define A6_COIL_ADDRESB5 0x00B5
#define A6_COIL_ADDRESB6 0x00B6
#define A6_COIL_ADDRESB7 0x00B7
#define A6_COIL_ADDRES100 0x0100
#define A6_COIL_ADDRES101 0x0101
#define A6_COIL_ADDRESB102 0x0102
#define A6_COIL_ADDRESB103 0x0103

#define A6_COIL_ADDRESB120 0x0120		//R/W
#define A6_COIL_ADDRESB122 0x0122		//R/W
#define A6_COIL_ADDRESB123 0x0123		//R/W
#define A6_COIL_ADDRESB124 0x0124		//R/W

#define A6_COIL_ADDRESB130 0x0130
#define A6_COIL_ADDRESB132 0x0132
#define A6_COIL_ADDRESB133 0x0133
#define A6_COIL_ADDRESB134 0x0134
#define A6_COIL_ADDRESB140 0x0140
#define A6_COIL_ADDRESB141 0x0141
#define A6_COIL_ADDRESB142 0x0142
#define A6_COIL_ADDRESB143 0x0143
#define A6_COIL_ADDRESB144 0x0144
#define A6_COIL_ADDRESB145 0x0145
#define A6_COIL_ADDRESB146 0x0146
#define A6_COIL_ADDRESB147 0x0147


#define A6_REGISTER_ADDRES1000 0x1000
#define A6_REGISTER_ADDRES1008 0x1008
#define A6_REGISTER_ADDRES1010 0x1010
#define A6_REGISTER_ADDRES1020 0x1020
#define A6_REGISTER_ADDRES1030 0x1030
#define A6_REGISTER_ADDRES1031 0x1031
#define A6_REGISTER_ADDRES1032 0x1032
#define A6_REGISTER_ADDRES1038 0x1038
#define A6_REGISTER_ADDRES1040 0x1040
#define A6_REGISTER_ADDRES1048 0x1048
#define A6_REGISTER_ADDRES1050 0x1050
#define A6_REGISTER_ADDRES1058 0x1058
#define A6_REGISTER_ADDRES1060 0x1060
#define A6_REGISTER_ADDRES1068 0x1068
#define A6_REGISTER_ADDRES1070 0x1070
#define A6_REGISTER_ADDRES1078 0x1078
#define A6_REGISTER_ADDRES1080 0x1080
#define A6_REGISTER_ADDRES1088 0x1088
#define A6_REGISTER_ADDRES1090 0x1090
#define A6_REGISTER_ADDRES1098 0x1098
#define A6_REGISTER_ADDRES10A0 0x10A0

#define A6_REGISTER_ADDRES4000 0x4000
#define A6_REGISTER_ADDRES4001 0x4001
#define A6_REGISTER_ADDRES4002 0x4002
#define A6_REGISTER_ADDRES400A 0x400A
#define A6_REGISTER_ADDRES400C 0x400C
#define A6_REGISTER_ADDRES400E 0x400E
#define A6_REGISTER_ADDRES400F 0x400F
#define A6_REGISTER_ADDRES4010 0x4010
#define A6_REGISTER_ADDRES4012 0x4012
#define A6_REGISTER_ADDRES4013 0x4013
#define A6_REGISTER_ADDRES4015 0x4015
#define A6_REGISTER_ADDRES4017 0x4017
#define A6_REGISTER_ADDRES4019 0x4019
#define A6_REGISTER_ADDRES401A 0x401A
#define A6_REGISTER_ADDRES401B 0x401B
#define A6_REGISTER_ADDRES401C 0x401C
#define A6_REGISTER_ADDRES401E 0x401E
#define A6_REGISTER_ADDRES401F 0x401F

#define A6_REGISTER_ADDRES4020 0x4020
#define A6_REGISTER_ADDRES4022 0x4022
#define A6_REGISTER_ADDRES4024 0x4024
#define A6_REGISTER_ADDRES4025 0x4025
#define A6_REGISTER_ADDRES4026 0x4026
#define A6_REGISTER_ADDRES4027 0x4027
#define A6_REGISTER_ADDRES4029 0x4029
#define A6_REGISTER_ADDRES402B 0x402B

#define A6_REGISTER_ADDRES4100 0x4100
#define A6_REGISTER_ADDRES4102 0x4102

#define A6_REGISTER_ADDRES4200 0x4200
#define A6_REGISTER_ADDRES4201 0x4201
#define A6_REGISTER_ADDRES4202 0x4202
#define A6_REGISTER_ADDRES4204 0x4204
#define A6_REGISTER_ADDRES4208 0x4208
#define A6_REGISTER_ADDRES4209 0x4209
#define A6_REGISTER_ADDRES420A 0x420A
#define A6_REGISTER_ADDRES420C 0x420C
#define A6_REGISTER_ADDRES4210 0x4210

#define A6_REGISTER_ADDRES4300 0x4300

#define A6_REGISTER_ADDRES4400 0x4400
#define A6_REGISTER_ADDRES4402 0x4402
#define A6_REGISTER_ADDRES4404 0x4404
#define A6_REGISTER_ADDRES4406 0x4406
#define A6_REGISTER_ADDRES4408 0x4408
#define A6_REGISTER_ADDRES440A 0x440A
#define A6_REGISTER_ADDRES440C 0x440C
#define A6_REGISTER_ADDRES4410 0x4410
#define A6_REGISTER_ADDRES4411 0x4411
#define A6_REGISTER_ADDRES4412 0x4412
#define A6_REGISTER_ADDRES4413 0x4413
#define A6_REGISTER_ADDRES4414 0x4414
#define A6_REGISTER_ADDRES4415 0x4415
#define A6_REGISTER_ADDRES4416 0x4416

#define A6_REGISTER_ADDRES6001 0x6001
#define A6_REGISTER_ADDRES600A 0x600A
#define A6_REGISTER_ADDRES600B 0x600B
#define A6_REGISTER_ADDRES600D 0x600D
#define A6_REGISTER_ADDRES600F 0x600F
#define A6_REGISTER_ADDRES601A 0x601A
#define A6_REGISTER_ADDRES601C 0x601C
#define A6_REGISTER_ADDRES6025 0x6025
#define A6_REGISTER_ADDRES6026 0x6026
#define A6_REGISTER_ADDRES602C 0x602C
#define A6_REGISTER_ADDRES609C 0x609C
#define A6_REGISTER_ADDRES609E 0x609E
#define A6_REGISTER_ADDRES60A0 0x60A0
#define A6_REGISTER_ADDRES60A2 0x60A2


#define A6_COIL_REGISTER_EXTADDRES400C 0x400C  //0x400C-0x400D  32bit
#define A6_COIL_REGISTER_EXTADDRES4201 0x4201  //0x4201 16bit
#define A6_COIL_REGISTER_EXTADDRES4400 0x4400  //0x4400-0x4401  32bit
#define A6_COIL_REGISTER_EXTADDRES4402 0x4402  //0x4402-0x4403  32bit
#define A6_COIL_REGISTER_EXTADDRES4404 0x4404  //0x4404-0x4405  32bit
#define A6_COIL_REGISTER_EXTADDRES4406 0x4406  //0x4406-0x4407  32bit
#define A6_COIL_REGISTER_EXTADDRES4408 0x4408  //0x4408-0x4409  32bit
#define A6_COIL_REGISTER_EXTADDRES440A 0x440A  //0x440A-0x440B  32bit
#define A6_COIL_REGISTER_EXTADDRES440C 0x440C  //0x440C-0x440D  32bit
#define A6_COIL_REGISTER_EXTADDRES4410 0x4410  //0x4410 16bit


extern unsigned char ModBus_Rec_Data[60];
extern int ModBus_CommCou;
extern char ModBus_CommHead_Flag;  //����֡ͷ��־λ
extern char ModBus_CommFrame_Flag; //����֡��־λ
extern char ModBus_CommModBus_Commd;   //����
extern int ModBus_CommAdder;   //��ַ
extern int ModBus_CommFileLenth; //�ļ�����
extern int ModBus_CommLengthTemp;
extern char ModBus_CommEnd_Flag;  //֡������־λ


extern unsigned char ModBus_SendBuf[32];
extern unsigned char ModsBuf_RecBuf[32];

extern unsigned char ModBus_Queue_Buf[16][32];


extern unsigned char ModBus_Run_Flag;//���б�־λ



extern unsigned char ModBusWaitTime;//�ȴ���ʱ
extern unsigned char ModBusWaitTime_Flag;//������ʱ;

extern unsigned int ModBus_CurDesmion;//����ֵλ��
extern short ModBus_QuanData;  //��Ȧ����
extern unsigned int ModBus_TransPulsData; //�ѷ��͵���������

extern unsigned int ModBus_ACErr;     //��������

extern unsigned int ModBus_AcErr_HisData[16];//��ʷ�������
extern unsigned int ModBus_AcErr_Type;//

extern unsigned char ModBus_Comm_LinkErr;

extern unsigned char ModBus_CurCommand;   //��ǰ��ͨѶ����
extern unsigned short ModBus_CurAdder;   //��ǰ��ͨѶ��ַ

extern unsigned char ModBus_Busy_Flag;  //ͨѶæ��־λ

extern unsigned char Modbus_A6_LuoJu;	//�ݾ�
extern unsigned short Modbus_A6_Puls;     //ÿת������
extern unsigned char Modbus_A6_JianSuBi; //���ٱ�
extern unsigned int  Modbus_A6_Speed;   //�ٶ�
extern unsigned int  Modbus_A6_SpeedTemp;   //�ٶ��ݴ�
extern unsigned char Modbus_A6_Speed_Sel;//�ٶȵ�ѡ����
extern unsigned short Modbus_A6_AddSpeedTime; //���ٶ�ʱ��
extern unsigned short Modbus_A6_DecSpeedTime; //����ʱ��
extern unsigned int   Modbus_A6_PulsSize;//ÿ����ľ���ߴ�

extern unsigned int Modbus_A6_JiZhunMark;
extern unsigned int Modbus_A6_JiZhunDesmion;
extern  short Modbus_A6_JiZhunQuan;

extern unsigned int Modbus_A6_ManualSpeed;//�ֶ��ٶ�

extern unsigned short ModBus_Status;
extern unsigned char ModBus_BackStatus,ModBus_ForwardStatus;


extern unsigned char ModBus_WaitRun_Flag;


extern int ShouLunlunSize;//���ֳߴ�
extern unsigned int ShouLunExecTime;  //����ִ�м�ʱ  0.5��

extern unsigned int ModBusCommTime;
extern unsigned int ModBusCommTimeOut;

extern unsigned char ModBus_QueueLoadCou;
extern unsigned char ModBus_QueueCurCou;
extern unsigned char ModBus_QueueCou;

typedef struct 
{
unsigned char MB_Id[16];
unsigned char MB_Command[16];
unsigned short MB_Adder[16];
unsigned short MB_Data[16];
}ModBusQueue;

extern ModBusQueue ModBus_Queue;



extern Int8U ModBus_CodeDataMode;

extern Int32U CurrentSize_A6Coder;
extern Int8U A6CoderEqual_flag;//A6��������ֵ���
extern Int8U A6CoderCorrectMode;//�����ߴ�
extern Int16U A6CoderCorrectTime;//
extern Int8U A6CoderCorrectRun_flag;//�������б��
extern Int32U StartInitSize;	//������ʼ�ߴ�
extern Int8U SendCmdOn_flag;

//extern unsigned short *fPtr;

//extern unsigned char *dfPtr;
extern void ModBusIO_Init(void);
extern void ModBus_CommExec(unsigned char rx_data);
extern unsigned short ModBus_CRC_Code(unsigned char *sbuf,unsigned short length);
extern void ModBus_CRC_DeCode(unsigned char *rbuf);
extern void ModBus_SendFrame(unsigned char mid,unsigned char mcommand,unsigned short madder,unsigned short mdata);
extern void ModBus_CrcTest(void);
extern void ModBus_WirteBlock(unsigned short block,unsigned char commd,unsigned char v0,unsigned char a0,unsigned char d0, int position);
extern void ModBus_WirteBlockSpeed(unsigned short bsnum,unsigned short speed);//�����ٶ�  0-15����Ӧ�ٶ�����
extern void ModBus_WirteBlockAddTime(unsigned short bsnum,unsigned short time);//���ü���ʱ��  0-15����Ӧ����ʱ������
extern void ModBus_WirteBlockDecTime(unsigned short bsnum,unsigned short time);//���ü���ʱ��  0-15����Ӧ����ʱ������
extern void ModBus_SetSpeedAndTime(unsigned char block,unsigned short speed,unsigned short addtime,unsigned short dectime);
extern void ModBus_Test(void);

extern void ModBus_Queue_Test(void);



//װ�ض���   ��������
extern void ModBus_Queue_LoadBuf(unsigned char *buf,unsigned char length);

//����װ�غ�Ķ���   ������
extern unsigned char  ModBus_Queue_SendBuf(unsigned char queue,unsigned char flag);
//ת������  ������
extern unsigned char ModBus_Queue_ChangeBuf(void);

extern void ModBus_Queue_StartBuf(void);//�������л�����



//װ�ض���
extern unsigned char  ModBus_LoadQueue(unsigned char mid,unsigned char mcommand,unsigned short madder,unsigned short mdata);

//ת������
extern unsigned char ModBus_ChangeQueue(void);// �βΣ�

//ɾ������
extern unsigned char ModBus_DeletQueue(unsigned char queue);// �βΣ�1��ɾ����һ������  16:ɾ�� �������ִ�к���ĵ����ж���


extern void  A6_CalPulsSize(void);   //����һ����ľ���
extern void  A6_CalCurSize(void);//���㵱ǰλ��
extern void  A6_LoadSpeed(void);


extern void Modbus_AC_ChangeSPD(void);
extern void Modbus_ACMotorRunStart(Int32U vbcd);//  AC�ŷ�  ��������





//�ŷ�����
extern void Modbus_ACServoOn(void);

//�ŷ��ر�
extern void Modbus_ACServoOff(void);
extern void Modbus_ACServoStop();
extern void Modbus_ACServoMoveBack_MID_SPD(void);    //�����ŷ�  ���ٺ���
extern void Modbus_ACServoMoveFwd_MID_SPD(void);  //�����ŷ�  ����ǰ��

extern void Modbus_ACMotorGoBack(void);
extern void Modbus_ACMotorGoFastBack(void);
extern void Modbus_ACMotorGoForward(void);
extern void Modbus_ACMotorGoFastForward(void);
extern void Modbus_ACMotor_ReleaseStop(void);
extern void Modbus_ACServoMoveBack_LOW_SPD(void);
extern void Modbus_A6_SaveSetData(void);
extern void Modbus_A6_LoadSetData(void);

extern void Modbus_ACMotorDDBack(void);//�������ֵ㶯  ����
extern void Modbus_ACMotorDDForward(void);//ǰ��
extern void Modbus_ACMotorShouLun(void);//���ִ���

extern void Modbus_A6_SaveErrData(void);//����������
extern void Modbus_A6_LoadErrData(void); //����������




#endif
