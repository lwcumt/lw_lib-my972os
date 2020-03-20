
#include <stdio.h>
#include "main.h"
#include "sys.h"

#include "drv_glcd.h"
//#include "pwm.h"
#include "timer.h"
#include "uart.h"
#include "io.h"
#include "spi.h"
#include "hzk.h"
#include"comm.h"
#include"chndot.h"
//#include"realtime.h"
#include"key.h"
//#include"pic.h"
//#include"processbar.h"
#include"i2c.h"
#include"pcf8563.h"


//#include "mcp4921.h"//DA4921

#include"m25pe16.h"
//#include"new_display.h"
#include "pic_exec.h"
#include"touch.h"
#include"download.h"

#include"word_lib.h"

#include "test_io.h"

#include "port.h"

#include"servo.h"
//#include "comm_touch.h"
#include "uart_config.h"
#include "lcd_config.h"
#include "spi_config.h"
#include "nand_config.h"
#include "file.h"
#include "gtp.h"

#include "keyboard.h"

#include "sysiotest.h"

#include "modbus.h"


//	#define TIME_BCOL   0xCE79 //


/*

#include"main.h"
#include "arm926ej_cp15_drv.h"
#include "ttbl.h"
#include"bmp.h"
#include"uart.h"
#include"seor1.c"
#define uchar unsigned char
#define uint unsigned int

*/

//#define TIME_BCOL   0x9CD3 //




Int8U Flash_flag;//��ʾˢ�±�־
Int8U DisInit_flag;//��ʾ��ʼ�����־

Int8U DAchanel;//DA����ѡ��


char hz[]="��";
extern Int8U HanZi[32];
extern  Int32U Rcv_New ;						// Ϊ1ʱ�������յ�������
extern  Int32U    Snd_N   ;						// ��¼����������Ϻ��跢�����ݵĸ���
//extern  Int8U	  Rcv_Buf[0x80];	// �ַ���������	

//extern  unsigned  char    chengxuhaoma   ;
//extern  unsigned  long int  vbcd4,  qianjixian,zhongjixian,houjixian,jizhun ;
 extern unsigned long int   chengxuweizhi[100];
// extern unsigned  char flagbz[200];
  unsigned long int Rswanwei1,Rwanwei1,Rqianwei1,Rbaiwei1,Rshiwei1,Rgewei1,sw1,qb1,sg1;
  
  unsigned long int swanwei3,wanwei3,qianwei3,baiwei3,shiwei3,gewei3;   
  
 unsigned long int daoqiancn,daoqiancn1,xsdaoqiancn;
 unsigned  char tmpdao,tmpdao1,flagcishu,tmpya,tmpya1,flagdao,flagya; 
// unsigned char bcd[3],qbcd[3],hbcd[5];
 unsigned long int fanqqianwei,fanqbaiwei,fanzqianwei,fanzbaiwei,fanhswwei,fanhwwei,fanhqianwei,fanhbaiwei;
 unsigned char tuobanbcd[3];
volatile Int32U Rcv_Num;


 unsigned  char flagcut,flagoneci,flagonly;
 
Int16U BarCou1=0;
Int8U BarCou2=0;

Int32U Cou_press;


Int8U buff[280];

Int8U RBuf[2100];




Int8U Hold_Up_flag;
Int8U Hold_Down_flag;

Int8U OnePress_sign_mod;
Int8U OneKnife_sign_mod;
Int8U NewKnife_sign_mod;

Int32U CutRelease_time;







Int8U Asensor_temp;
Int8U Bsensor_temp;
Int8U ABsensor_temp;


Int8U PressStopDis_flag;



Int16U AutoCutTime;


Int16U orig_wait_time;

Int16U ServoStopTime;

Int16U DisplayFlashTime;


Int8U Z_PulseIN;

unsigned char SecTemp;   


Int16U on_gap,off_gap;  //����ʱ��


Int16U ForceStopTime;
Int32U ForceStopSize;

extern unsigned char BootFolder;
Int8U FrontLimitDis_flag;

/*************************************************************************
 * Function Name: main
 * Parameters: none
 *
 * Return: none
 *
 * Description: main
 *

 *************************************************************************/
 /*
void DrawPic_IntFlash16(const Int16U *pic,int x,int y,int picwidth,int pichigh);

void LoadDataFlashToSDRAM(pInt16U p,int da,  int dlenth);

void DrawPic_SDRAM(long sect,int x,int y,int picwidth,int    pichigh);

void DrawPic_DATAFLASH(long sect,int x,int y,int picwidth,int pichigh);
*/

 
void IOinputTest1_2(void);//IO  �������********1.2  
void IOinputTest1_3(void);//IO  �������********1.3  
void Dis_init(void);//��ʼ��ʾ����

void Time_dis(void);//
Int16U Caluate_Days(void);
void PassCheck_dis(Int16U x, Int16U y); //������ʾ

void RenewOneKnife_data(void);

void OutLimit_check(void); //�ⲿ��λ 
void Joggle_GoFast(void);
void FreqRuningLimit_ctrl(void);  //������  �ⲿ�ź�
void FreqWorkStart_check(void);  //����ģʽǰ  ׼��
Int8U PressStop_check(void);//ѹֽͣ��  �ж�
void CutEnable_Exec(void);  //���� ����
void AutoCutPush_exec(void);  //�Զ�����
void ServoWorkStart_check(void);  //����ģʽǰ  ׼��
void ServoRunning_ctrl(void); //ֱ���ŷ� ���п���
void ACServoWorkStart_check(void);  //�����ŷ�  ����ģʽǰ  ׼��

void BellTwice_exec(void);  //����  ����

void ACMotorGetCurrentSize(void);  // �����ŷ�   �ߴ����
void ACMotorRunning_ctrl(void);//�����ŷ�����  ����
void AC_MotorRuningLimit_ctrl(void);  //������  ���ⲿ�ź� ֹͣ

void NowSizeNum_dis(void);

void ACMotor_GetZpulse(void);
void ACServoAlarm_exec(void);  //�����ŷ�  ����  ����



// #define SDRAM_BASE_ADDR 0x80000000
// #define VECTOR_BASE_ADDR 0x80100000



/* Prototype for external IRQ handler */
void lpc32xx_irq_handler(void);
void workstartexec(void);

////void delay(unsigned int  cnt)
////{
////    unsigned int  i = cnt;
////    while (i != 0) i--;
////    return;
////}


void Process_Main(void)
{
  // Init MMU
//int i;
unsigned char spi_Data[16];
unsigned int temptime;
unsigned char NFBuf[4096];
pInt32U cp1,cp2;

  //int j,n,k;
  int BarCou;
   Int32U i,j;
	Int16U d,Ms100t;   
				 Int16U Cou=0;
          int NumberCou;
				 
pInt16U ptr;//				 
Int32U temp;

//////  disable_irq();
//////  /* Initialize interrupt system */
//////  int_initialize(0xFFFFFFFF);

//////  /* Install standard IRQ dispatcher at ARM IRQ vector */
//////  int_install_arm_vec_handler(IRQ_VEC, (PFV) lpc32xx_irq_handler);

//////  /* Enable IRQ interrupts in the ARM core */
//////  enable_irq();

//////IO_Init();
//////LCD_Init();
//////delay(100000);
//////LCD_6BIT_PIN_SET();

//////GLCD_Buffer_Fill(BLUE_COLOR);
////////P3_OUTP_SET=0x1;
////////UART2_Init();
//////SD_PW_OFF();
////////SD_PW_ON();


//////// pInt8U ps=(pInt8U)malloc(1024);



//////Spi_Init();

//////Read_DevID();

//////Nand_Init();

Nand_Reset();
Nand_ReadID();
// Read_DevID();


////////I2C_Init();
/*
Nand_Format();
iFiles.FileLength=0;
asector=File_GetFreeSector_New();
iFiles.FileLength=10;
asector=File_GetFreeSector_New();
iFiles.FileLength=130*1024;
asector=File_GetFreeSector_New();
iFiles.FileLength=256*1024;
asector=File_GetFreeSector_New();
iFiles.FileLength=830*1024;
asector=File_GetFreeSector_New();
asector=File_GetFreeSector_New();
asector=File_GetFreeSector_New();
asector=File_GetFreeSector_New();
*/
//Nand_Format();//ɾ������ǻ���
//////SDInsert_Check();//����Ƿ���SD������


/*
FileWriteBootApp(1+0x30);//Ӧд��ΪASCII
FileLoadBootApp(); //��������ASCII
*/


BootFolder=FileLoadBootApp()-0x30;
if((BootFolder<1)||(BootFolder>6))//����������1-6��Ӧ����ţ�ǿ�ƴӵ�1����ȡ��Դ�ļ�
	{
	BootFolder=1;
	}
// BootFolder=1;


/*

FileFolderRead("Power.bmp",(unsigned char*)START_PIC_sdram);//����������
BootFolder=2;
FileFolderRead("Power.bmp",(unsigned char*)START_PIC_sdram);//����������
BootFolder=1;
FileFolderRead("Power.bmp",(unsigned char*)START_PIC_sdram);//����������
BootFolder=2;
FileFolderRead("Power.bmp",(unsigned char*)START_PIC_sdram);//����������

*/


/*
for(i=0;i<1024;i++)
	{
	Nand_EraseBlock((i*NF_BLOCK_BYTES)>>11);
	Nand_FillPage_SDbuf(FileNum,128*1024,i); //ɾ��ԭ�е���Ϣ �����ļ��������ȣ���ַ  ����Ŀ¼��
	Nand_WriteBlock(i,(unsigned char *)NF_SECTOR_SDRAM_BUF);
	Nand_ReadBlock(i,(unsigned char *)NF_SECTOR_SDRAM_BUF);//��ȡ �ļ�name��Ϣ
	}
//SDInsert_Check();//����Ƿ���SD������
for(i=0;i<1024;i++)
	{
//	Nand_EraseBlock((startsector*NF_BLOCK_BYTES)>>11);
	//Nand_FillPage_SDbuf(FileNum,128*1024,0xa5); //ɾ��ԭ�е���Ϣ �����ļ��������ȣ���ַ  ����Ŀ¼��
//	Nand_WriteBlock(startsector,(unsigned char *)NF_SECTOR_SDRAM_BUF);
	Nand_ReadBlock(i,(unsigned char *)NF_SECTOR_SDRAM_BUF);//��ȡ �ļ�name��Ϣ
	Nand_EraseBlock((i*NF_BLOCK_BYTES)>>11);
	Nand_ReadBlock(i,(unsigned char *)NF_SECTOR_SDRAM_BUF);//��ȡ �ļ�name��Ϣ
	}
		
		*/
			



//File_Create("\\APP_1\\test.txt");

//Nand_ReadBlock(5,(unsigned char *)NF_SECTOR_SDRAM_BUF);//��ȡ �ļ�name��Ϣ
/*
Nand_Format();//ɾ������ǻ���

File_CreateFolder("APP_1");//"\\APP_1\\test.txt");
File_CreateFolder("APP_2");//"\\APP_1\\test.txt");
File_CreateFolder("APP_3");//"\\APP_1\\test.txt");
File_CreateFolder("APP_4");//"\\APP_1\\test.txt");
File_CreateFolder("APP_5");//"\\APP_1\\test.txt");
File_CreateFolder("APP_6");//"\\APP_1\\test.txt");

File_FindFolder("APP_6");
File_FindFolder("APP_2");
File_FindFolder("APP_4");
File_FindFolder("APP_1");
File_FindFolder("APP_5");
File_FindFolder("APP_3");


File_Create("\\APP_1\\test.txt");
File_FindFolder("test.txt");

FileRead("Boot_App_1.bin",(unsigned char*)DOWNFILE_SDRAM_ADD);
FileRead("\\APP_1\\test.txt",(unsigned char*)DOWNFILE_SDRAM_ADD);
FileRead("Boot_App_1.bin",(unsigned char*)DOWNFILE_SDRAM_ADD);
FileRead("Vector.bin",(unsigned char*)VECTOR_BASE_ADDR);
*/
////////AOUT1_SET();
////////AOUT2_SET();
////////AOUT3_SET();
////////AOUT4_SET();
////////AOUT5_SET();

/*
AOUT1_CLR();
AOUT2_CLR();
AOUT3_CLR();
AOUT4_CLR();
AOUT5_CLR();

*/
/*
RLOUT1_OFF ;
RLOUT2_OFF ;
RLOUT3_OFF ;
RLOUT4_OFF ;
RLOUT5_OFF ;

RLOUT1_ON;
RLOUT2_ON ;
RLOUT3_ON ;
RLOUT4_ON ;
RLOUT5_ON ;



AOUT1_SET();
AOUT2_SET();
AOUT3_SET();
AOUT4_SET();
AOUT5_SET();

AOUT1_CLR();
AOUT2_CLR();
AOUT3_CLR();
AOUT4_CLR();
AOUT5_CLR();

M_DOUT_OFF;
M_POUT_OFF;

M_DOUT_ON;
M_POUT_ON;
*/

unsigned char  OutFlag;
OutFlag=0;


Timer0Init();



//////PWR_CTRL|=(1<<1);
//////PWR_CTRL&=~(Int32U)(1<<5);//PWR_CTRL|=(1<<5);

//******************************************



 Rcv_Num=0;
 CommCou=0;
 //AT45DB_Init(AT45DB161);  //��ʼ��DATAFLASH
 
 BellOUT_ON;
 i=1000000;
 while(i--);
 BellOUT_OFF;
  i=1000000;
 while(i--);
 BellOUT_ON;
  i=1000000;
 while(i--);
 BellOUT_OFF;
 
////////////////////////////////////////////////////////////////

//*****************************************************************************����ͼƬ  ��ʾЧ��
//Dis_init();//��ʼ��ʾ����


//SD_LOAD_DirIn;

GLCD_Buffer_Fill(0);

//KeyDis_Init();//������ʾ��ʼ��	
	
//SPIInit();	
ReadLanguage();
//while(NandflashInit()!=0);//nand ��ʼ��	
/*
if(SD_LOAD_PIN==0)	//sd�����ļ�
{
GLCD_Buffer_Fill(0xffff);
DiskFiles_To_NandFlash();
while(1);
}
*/
#if CODE_APP_SAVE==1		//code save--------------------------------
	CodeAppExec();
	while(1);
#else

// if(DecodeAppExec() == 0)	//�ȴ�����	99999999999999999999999999999999999
// {
// while(1);
// }


//BootFolder=5;
StartPic_dis();//��ʾ��������



ReadMachineType(); //��������
switch(MotorType)
	{
	case MOTOR_FREQ_5_SPD_RST:
	case MOTOR_FREQ_3_SPD:
	case MOTOR_FREQ_3_SPD_RST: 
	Uart_mod=0;
				on_gap=120;
				off_gap=80;
					break;
	// // case MOTOR_DC_SERVO:
	// // case MOTOR_DC670_SERVO:
				// // Uart_mod=1;//�ŷ����� ͨѶ
				// // ReadMovSpeed();
				// // ReadJogSpeed();  //�ٶ�
				// // Read_PitchRatio();  //�ݾ� �ٱ�
				// // on_gap=500;
				// // off_gap=1000;
					// // break;
	case MOTOR_AC_A6_SERVO:
			//------A6---����---
				Uart_mod=2;//����ͨѶ-------------
				ModBusIO_Init();
				ModBus_CommCou=0;
				//ModBus_CrcTest();
				// Modbus_A6_LoadSetData();
				Modbus_A6_LuoJu=10;
				ReadA6MarkBenchSize();//A6 ������ ��׼ֵ(6 Byte)
				// Modbus_A6_LoadErrData();//�����ϴδ������    	-------20171124 ȥ��
				ReadCurrentSize_A6Coder();//��ȡ��ǰ A6������ֵ
	case MOTOR_AC_SERVO:	
	case MOTOR_AC_SERVO_REV:
				//------------ͨ��AC---
				ReadACMotorSpeed();
				GetAC_MotorSpeed();   //�����ŷ�  �ٶ��ж�
				ReadElectricWheelSwitch();//��������
				on_gap=120;
				off_gap=80;
					break;
	}
  //uart0
	
//UART2_Init();//485
//UART1_Init();//key51
//UART5_Init();//----------------------------touchcomm


ReadUnit();
ReadOriginalSize();
ReadFrontLimit();
ReadMiddleLimit();
ReadBackLimit();

Size_MAX=BackLimit;
if(Unit==UNIT_MM)
	Size_MAX_num=Size_MAX;
else
	Size_MAX_num=Size_MAX*100/254;
if(Carrier_IN==0)  //�а� �ź�
	Size_MIN=FrontLimit;
else
	Size_MIN=MiddleLimit;
if(Unit==UNIT_MM)
	Size_MIN_num=Size_MIN;
else
	Size_MIN_num=Size_MIN*100/254;
		


ReadDatas_to_sdram();   //������ ----��ȡ
//ReadStanDistance();

Read_TouchDatas();

ReadAheader();

Read_degree();
SetPulse_degree();
ReadCurrentPulseAB();

ReadFirstDays();
ReadSecondDays();
ReadFirstDays_flag();
ReadSecondDays_flag();
ReadPushDistance();
ReadAirOffDistance();	//������ ����

ReadPressValid_flag();  //ѹֽ ��Ч��־
ReadIRValidStatus();//IR status
ReadStepDistance(); // ��������


DaysTime_check();

CurrentArea_save1(START_PROMPT_X1, START_PROMPT_Y1,   START_PROM_WIDE, START_PROM_HIGH);
CurrentArea_save2(START_PROMPT_X2, START_PROMPT_Y2,   START_PROM_WIDE, START_PROM_HIGH);

Timer0Init();

	
PageKf_Size_Init();	//ÿҳ �����趨
ReadVirtualTargetSizeGap();		//����Ŀ��ֵ
ReadIRChgWorkmodeValid();	//�����л�����ģʽ���


while(1)
   {
   //ACMotor_GetZpulse();
   
   if(Ms_Flag!=0)
	  {
	  Ms_Flag=0;
	  if(Touch_code==0)
		Keyboard_scan();
	  if(KeyboardDown_flag==0)
		 // ToucScan(); 
		TouchScan_Uart(); 
      ShiftKeyExec();//
	  
	  // // if((MotorType<MOTOR_DC_SERVO)||(MotorType>=MOTOR_AC_SERVO)) //��Ƶ�� 3��
		 // // {
		 AllSensor_IN_Get();   //�˿ڼ��
		 // // }
	  // // else
		 // // {
		 // // GetCutSensorIN();   //�˿ڼ��
		 // // }
	  if(MotorType>=MOTOR_AC_SERVO) 
		 {
		 ACServoAlarm_exec();  //�����ŷ�  ����  ����
		 if(MotorType==MOTOR_AC_A6_SERVO)	//A6 ����
			{
			if((Run_flag==0)&&(GoBackEn_flag==0)&&(GoFrontEn_flag==0))
				{
				 ModbusComm_CtrlExec();//--------20170524	
		 		}
			  else
				{
				if(SendCmdOn_flag==1)
					{
					ModBus_Comm_LinkErr=0;//ͨѶ���Ӵ��� ���
					SendCmdOn_flag=0;
					}
				}
			}
		 }
		 
	  if((EncoderErr_flag==1)||(ACServoDrvErr_flag==1))
			{
			Cou++;
			if(Cou>=200)
				{
				Cou=0;
				if(ModBus_Comm_LinkErr==0)
				BellOUT_ANTI;  ///���� ����----
			 //  LED2_ANTI; 
				} 
			}
			
			
			
	  //************************************************************************************************************
	  if(WorkStart_flag==1)  //���빤��״̬
	     {	 
		 BellTwice_exec();  //����  ����
		 
		if(MotorType>=MOTOR_AC_SERVO)
			{
			ACMotorGetCurrentSize();  // �����ŷ�   �ߴ����
			}
	 
	 //************��������ʱ����ʾ
         Ms100t++;
         if(Ms100t>=200)
             {
             Ms100t=0;
		     read_time();
		     Time_dis();
             } 
		//*************
		switch(WorkMode)
			{
			// case  PROG_MODE://��̻�����
			case AUTO_MODE://�Զ���������
			case AUTO_PLUS_MODE://�Զ�F3++
			case AUTO_MINUS_MODE://�Զ�F4--
			case MANUAL_MODE:// �ֶ� ģʽ
			case TEACH_MODE://ʾ�� ģʽ
			case AUTO_TO_SELF_MODE:   //�Զ�-->�Ե����� ģʽ
			case SELF_CUT_MODE:  //�Ե��� ģʽ
			case TEACH_PLUS_MODE: //ʾ�� F3++
			case TEACH_MINUS_MODE://ʾ�� F4--
			
				switch(MotorType)
					{
					case MOTOR_FREQ_5_SPD_RST:	
					case MOTOR_FREQ_3_SPD:	
					case MOTOR_FREQ_3_SPD_RST:
					case MOTOR_AC_SERVO:
					case MOTOR_AC_SERVO_REV:
					case MOTOR_AC_A6_SERVO:
							NewKnife_sign_mod=3;//++++++++++++++++++++++++++
							if(CutPaper_IN1==0) //  �� ��--------------------
								 {
								 AllKnifeUp_flag=0;//----00000
								 CutRelease_time=0;
								 if(KnifeDown_flag==0)
									{
									KnifeDown_flag=1;
									KnifeUp_flag=0;
										Knife_Down_dis( KNIFE_UP_X,  KNIFE_UP_Y);//����
									}
								if(Run_flag==0)
									{
									if(PaperCutEnb_signal==2)
										{
										if(OneKnife_sign_mod==1)
											OneKnife_sign_mod++;
										}
									}
								KnifeSensorInMachine_dis(1);//�� ������λ�� ʾ��
								 }
							 else
								 {
								 AllKnifeUp_flag=1;//----11111
								 if(KnifeUp_flag==0)
									{
									KnifeDown_flag=0;
									KnifeUp_flag=1;
										Knife_Up_dis(KNIFE_UP_X,KNIFE_UP_Y);//����
									if(PressStopDis_flag==1)//ѹֽͣ�� ��ʾ
										{
										PressStopDis_flag=0;
										PromptNum_dis();//���뷶Χ
										PromptDis_flag=1;
										}	
									}
								 if(Run_flag==0)
									{
									if(PaperCutEnb_signal==2)
										{
										if((OneKnife_sign_mod==0)||(OneKnife_sign_mod==2))
											{
											OneKnife_sign_mod++;
											if(OneKnife_sign_mod==3)
												CutRelease_time=0;
											}
										}
									}	
								KnifeSensorInMachine_dis(0);//�� ������λ�� ʾ��
								 }
								 
							 if(PressPaper_IN!=0) //ѹֽ ��--------------------
								 {
								 CutRelease_time=0;
								 AllPressUp_flag=0;//----000
								 if(PressDown_flag==0)
									{
									PressDown_flag=1;
									PressUp_flag=0;
										Press_Down_dis(PRESS_UP_X,PRESS_UP_Y);//ѹֽ ��
									// switch(MotorType)
										// {
										// case MOTOR_FREQ_5_SPD_RST://----5���� 
												// break;
										// case MOTOR_FREQ_3_SPD://----3 ����	
										// case MOTOR_FREQ_3_SPD_RST://----3 ����+��λ
											// RLOUT2_ON;;//�����Ͽ�
												// break;
										// }
									if(MotorType>MOTOR_FREQ_5_SPD_RST)
										RLOUT3_ON;// RLOUT2_ON;//�����Ͽ�
									}
								if(Run_flag==0)
									{
									if(PaperCutEnb_signal==2)
										{
										if(OnePress_sign_mod==1)
											OnePress_sign_mod++;
										}
									if(WorkMode == AUTO_MODE)//�Զ���������
										{
										if(PressCircle_mode == 0)
											PressCircle_mode++;
										}
									}
								PressSensorInMachine_dis(1);//ѹֽ ������λ�� ʾ��
								 }
							 else
								 {
								 AllPressUp_flag=1;//----111
								 if(PressUp_flag==0)
									{
									PressDown_flag=0;
									PressUp_flag=1;
										Press_Up_dis(PRESS_UP_X,PRESS_UP_Y);//ѹ��
									if(PressStopDis_flag==1)//ѹֽͣ�� ��ʾ
										{
										PressStopDis_flag=0;
										PromptNum_dis();//���뷶Χ
										PromptDis_flag=1;
										}
									// switch(MotorType)
										// {
										// case MOTOR_FREQ_5_SPD_RST://----5���� 
												// break;
										// case MOTOR_FREQ_3_SPD://----3 ����	
										// case MOTOR_FREQ_3_SPD_RST://----3 ����+��λ
												// RLOUT2_OFF;//�����պ�
												// break;
										// }
									if(MotorType>MOTOR_FREQ_5_SPD_RST)
										{
										if((WorkMode==TEACH_MODE)||(WorkMode==AUTO_MODE)||(WorkMode==SELF_CUT_MODE))
											{
											if(AirOffOK_flag==0)
												RLOUT3_OFF;// RLOUT2_OFF;//�����պ�
											}
										else
											RLOUT3_OFF;//RLOUT2_OFF;//�����պ�
										}
									}
								if(Run_flag==0)
									{
									if(PaperCutEnb_signal==2)
										{
										if((OnePress_sign_mod==0)||(OnePress_sign_mod==2))
											{
											OnePress_sign_mod++;
											if(OnePress_sign_mod==3)
												CutRelease_time=0;
											}
										}
									if(WorkMode == AUTO_MODE)//�Զ���������
										{
										if(PressCircle_mode == 1)
											PressCircle_mode++;
										}
									}
								PressSensorInMachine_dis(0);//ѹֽ ������λ�� ʾ��
								 }
									
								break;
					// // case MOTOR_DC_SERVO:
							// // NewKnife_sign_mod=3;//++++++++++++++++++++++++++
							// // if(CutPaper_IN2==0) //  �� ��--------------------
								 // // {
								 // // AllKnifeUp_flag=0;//----00000
								 // // CutRelease_time=0;
								 // // if(KnifeDown2_flag==0)
									// // {
									// // KnifeDown2_flag=1;
									// // KnifeUp2_flag=0;
										// // Knife_Down_dis( KNIFE_UP_X,  KNIFE_UP_Y);//����
									// // }
								// // if(Run_flag==0)
									// // {
									// // if(PaperCutEnb_signal==2)
										// // {
										// // if(OneKnife_sign_mod==1)
											// // OneKnife_sign_mod++;
										// // }
									// // }
								// // KnifeSensorInMachine_dis(1);//�� ������λ�� ʾ��
								 // // }
							 // // else
								 // // {
								 // // AllKnifeUp_flag=1;//----11111
								 // // if(KnifeUp2_flag==0)
									// // {
									// // KnifeDown2_flag=0;
									// // KnifeUp2_flag=1;
										// // Knife_Up_dis(KNIFE_UP_X,KNIFE_UP_Y);//����
									// // if(PressStopDis_flag==1)//ѹֽͣ�� ��ʾ
										// // {
										// // PressStopDis_flag=0;
										// // PromptNum_dis();//���뷶Χ
										// // PromptDis_flag=1;
										// // }	
									// // }
								// // if(Run_flag==0)
									// // {
									// // if(PaperCutEnb_signal==2)
										// // {
										// // if((OneKnife_sign_mod==0)||(OneKnife_sign_mod==2))
											// // {
											// // OneKnife_sign_mod++;
											// // if(OneKnife_sign_mod==3)
												// // CutRelease_time=0;
											// // }
										// // }
									// // }
								// // KnifeSensorInMachine_dis(0);//�� ������λ�� ʾ��
								 // // }
								 
							 // // if(PressPaper_IN!=0) //ѹֽ ��--------------------
								 // // {
								 // // AllPressUp_flag=0;//----000
								 // // CutRelease_time=0;
								 // // if(PressDown_flag==0)
									// // {
									// // PressDown_flag=1;
									// // PressUp_flag=0;
										// // Press_Down_dis(PRESS_UP_X,PRESS_UP_Y);//ѹֽ ��
									// // //�����Ͽ�
									// // }
								// // if(Run_flag==0)
									// // {
									// // if(PaperCutEnb_signal==2)
										// // {
										// // if(OnePress_sign_mod==1)
											// // OnePress_sign_mod++;
										// // }
									// // if(WorkMode == AUTO_MODE)//�Զ���������
										// // {
										// // if(PressCircle_mode == 0)
											// // PressCircle_mode++;
										// // }
									// // }
								// // PressSensorInMachine_dis(1);//ѹֽ ������λ�� ʾ��
								 // // }
							 // // else
								 // // {
								 // // AllPressUp_flag=1;//----111
								 // // if(PressUp_flag==0)
									// // {
									// // PressDown_flag=0;
									// // PressUp_flag=1;
										// // Press_Up_dis(PRESS_UP_X,PRESS_UP_Y);//ѹ��
									// // if(PressStopDis_flag==1)//ѹֽͣ�� ��ʾ
										// // {
										// // PressStopDis_flag=0;
										// // PromptNum_dis();//���뷶Χ
										// // PromptDis_flag=1;
										// // }
									// // //�����պ�
									// // }
								 // // if(Run_flag==0)
									// // {
									 // // if(PaperCutEnb_signal==2)
										// // {
										// // if((OnePress_sign_mod==0)||(OnePress_sign_mod==2))
											// // {
											// // OnePress_sign_mod++;
											// // if(OnePress_sign_mod==3)
												// // CutRelease_time=0;
											// // }
										// // }
									// // if(WorkMode == AUTO_MODE)//�Զ���������
										// // {
										// // if(PressCircle_mode == 1)
											// // PressCircle_mode++;
										// // }
									// // }
								// // PressSensorInMachine_dis(0);//ѹֽ ������λ�� ʾ��
								 // // }
										
						 		// // break;
					// // case MOTOR_DC670_SERVO: 
							// // if(CutPaper_IN1!=0) //  �� ��--------------------
								 // // {
								 // // AllKnifeUp_flag=0;//----00000
								 // // CutRelease_time=0;
								 // // if(KnifeDown_flag==0)
									// // {
									// // KnifeDown_flag=1;
									// // KnifeUp_flag=0;
										// // Knife_Down_dis( KNIFE1_UP_X,  KNIFE1_UP_Y);//����
									// // }
								// // if(Run_flag==0)
									// // {
									// // if(PaperCutEnb_signal==2)
										// // {
										// // if(NewKnife_sign_mod==1)
											// // NewKnife_sign_mod++;
										// // }
									// // }
								// // //KnifeSensorInMachine_dis(1);//�� ������λ�� ʾ��
								 // // }
							 // // else
								 // // {
								 // // if(KnifeUp2_flag==1)
									// // AllKnifeUp_flag=1;//----11111
								 // // if(KnifeUp_flag==0)
									// // {
									// // KnifeDown_flag=0;
									// // KnifeUp_flag=1;
										// // Knife_Up_dis(KNIFE1_UP_X,KNIFE1_UP_Y);//����
									// // if(PressStopDis_flag==1)//ѹֽͣ�� ��ʾ
										// // {
										// // PressStopDis_flag=0;
										// // PromptNum_dis();//���뷶Χ
										// // PromptDis_flag=1;
										// // }	
									// // }
								// // if(Run_flag==0)
									// // {
									// // if(PaperCutEnb_signal==2)
										// // {
										// // if((NewKnife_sign_mod==0)||(NewKnife_sign_mod==2))
											// // {
											// // NewKnife_sign_mod++;
											// // if(NewKnife_sign_mod==3)
												// // CutRelease_time=0;
											// // }
										// // }
									// // }
								// // //KnifeSensorInMachine_dis(0);//�� ������λ�� ʾ��
								 // // }
								 
							// // if(CutPaper_IN2==0) //  �� ��--------------------
								 // // {
								 // // AllKnifeUp_flag=0;//----00000
								 // // CutRelease_time=0;
								 // // if(KnifeDown2_flag==0)
									// // {
									// // KnifeDown2_flag=1;
									// // KnifeUp2_flag=0;
										// // Knife_Down_dis( KNIFE_UP_X,  KNIFE_UP_Y);//����
									// // }
								// // if(Run_flag==0)
									// // {
									// // if(PaperCutEnb_signal==2)
										// // {
										// // if(OneKnife_sign_mod==1)
											// // OneKnife_sign_mod++;
										// // }
									// // }
								// // KnifeSensorInMachine_dis(1);//�� ������λ�� ʾ��
								 // // }
							 // // else
								 // // {
								 // // if(KnifeUp_flag==1)
									// // AllKnifeUp_flag=1;//----11111
								 // // if(KnifeUp2_flag==0)
									// // {
									// // KnifeDown2_flag=0;
									// // KnifeUp2_flag=1;
										// // Knife_Up_dis(KNIFE_UP_X,KNIFE_UP_Y);//����
									// // if(PressStopDis_flag==1)//ѹֽͣ�� ��ʾ
										// // {
										// // PressStopDis_flag=0;
										// // PromptNum_dis();//���뷶Χ
										// // PromptDis_flag=1;
										// // }	
									// // }
								// // if(Run_flag==0)
									// // {
									// // if(PaperCutEnb_signal==2)
										// // {
										// // if((OneKnife_sign_mod==0)||(OneKnife_sign_mod==2))
											// // {
											// // OneKnife_sign_mod++;
											// // if(OneKnife_sign_mod==3)
												// // CutRelease_time=0;
											// // }
										// // }
									// // }
								// // KnifeSensorInMachine_dis(0);//�� ������λ�� ʾ��
								 // // }
								 
							 // // if(PressPaper_IN!=0) //ѹֽ ��--------------------
								 // // {
								 // // AllPressUp_flag=0;//----000
								 // // CutRelease_time=0;
								 // // if(PressDown_flag==0)
									// // {
									// // PressDown_flag=1;
									// // PressUp_flag=0;
										// // Press_Down_dis(PRESS_UP_X,PRESS_UP_Y);//ѹֽ ��
									
									// // }
								 // // if(Run_flag==0)
									// // {
									// // if(PaperCutEnb_signal==2)
										// // {
										// // if(OnePress_sign_mod==1)
											// // OnePress_sign_mod++;
										// // }
									// // if(WorkMode == AUTO_MODE)//�Զ���������
										// // {
										// // if(PressCircle_mode == 0)
											// // PressCircle_mode++;
										// // }
									// // }
								// // PressSensorInMachine_dis(1);//ѹֽ ������λ�� ʾ��
								 // // }
							 // // else
								 // // {
								 // // AllPressUp_flag=1;//----111
								 // // if(PressUp_flag==0)
									// // {
									// // PressDown_flag=0;
									// // PressUp_flag=1;
										// // Press_Up_dis(PRESS_UP_X,PRESS_UP_Y);//ѹ��
									// // if(PressStopDis_flag==1)//ѹֽͣ�� ��ʾ
										// // {
										// // PressStopDis_flag=0;
										// // PromptNum_dis();//���뷶Χ
										// // PromptDis_flag=1;
										// // }
									
									// // }
								// // if(Run_flag==0)
									// // {
									// // if(PaperCutEnb_signal==2)
										// // {
										// // if((OnePress_sign_mod==0)||(OnePress_sign_mod==2))
											// // {
											// // OnePress_sign_mod++;
											// // if(OnePress_sign_mod==3)
												// // CutRelease_time=0;
											// // }
										// // }
									// // if(WorkMode == AUTO_MODE)//�Զ���������
										// // {
										// // if(PressCircle_mode == 1)
											// // PressCircle_mode++;
										// // }
									// // }
								// // PressSensorInMachine_dis(0);//ѹֽ ������λ�� ʾ��
								 // // }
										
						 		// // break;
					}
					/****
					 if(Encoder_A_IN==0) //������A ��--------------------
						 {
						 if(A_Down_flag==0)
							{
							A_Down_flag=1;
							A_Up_flag=0;
							// // if(InputTouch_flag==0)
								// // Red_A_dis(RED_A_X,RED_A_Y);//��A
							}
						 }
					 else
						 {
						 if(A_Up_flag==0)
							{
							A_Down_flag=0;
							A_Up_flag=1;
							// // if(InputTouch_flag==0)
								// // Black_A_dis(RED_A_X,RED_A_Y);//��A
							}
						 }
					 if(Encoder_B_IN==0) //������B ��--------------------
						 {
						 if(B_Down_flag==0)
							{
							B_Down_flag=1;
							B_Up_flag=0;
							// // if(InputTouch_flag==0)
								// // Red_B_dis(RED_B_X,RED_B_Y);//��B
							}
						 }
					 else
						 {
						 if(B_Up_flag==0)
							{
							B_Down_flag=0;
							B_Up_flag=1;
							// // if(InputTouch_flag==0)
								// // Black_B_dis(RED_B_X,RED_B_Y);//��B
							}
							}
						 }**/
					 
					 if(IRsensor_IN==0) //����  ��----------------------
						 {
						 if(IR_Down_flag==0)
							{
							IR_Down_flag=1;
							IR_Up_flag=0;
							// if(ButtonTouch_mode==0)
								IR_CUT_dis(IR_X,IR_Y); //�ֺ���
							}
						if(WorkMode==SELF_CUT_MODE)//�Ե���������
							{
							//#if 0  //--------((((((((((
							if(Run_flag==1)  //������
								{
								if(IRChgWorkmodeValid_flag!=0)	//����--�л�����ģʽ20180110
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
													break;
											// // case MOTOR_DC_SERVO:
											// // case MOTOR_DC670_SERVO:
												// // DCServoStop();  //ֹͣ����
													// // break;
											case MOTOR_AC_SERVO:
											case MOTOR_AC_SERVO_REV:
												ACServoStop();
												
													break;
											}
										Run_flag=0;	
										InTargetPosit_flag=0;	//Ŀ��λ��
										AutoPushRun_flag=0; //�Զ���ֽ ����
										TargetSize=0;
										TargetSize_temp=0;
										BeforeKnife_offset_in=0;
										// if(ButtonTouch_mode==0)
											// ClrInput_function();//���� �����
										AutoRoute_flag=0; 
										}
									}
								AutoCutDisable_flag=1;
								}
							else
								{
								if(OneKnife_sign_mod>0)	//	||(OnePress_sign_mod>0)
									AutoCutDisable_flag=1;		
								}
								
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
							if(IRChgWorkmodeValid_flag!=0)	//����--�л�����ģʽ20180110
								{/****20170818***/
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
					 else
						 {
						 if(IR_Up_flag==0)
							{
							IR_Up_flag=1;
							IR_Down_flag=0;
							// if(ButtonTouch_mode==0)
								IR_LINE_dis(IR_X,IR_Y);//����
							}
						 }
					
				
					//************************
					if(PaperCutEnb_signal==1)
						{
						PaperCutEnb_signal++;
						OneKnife_sign_mod=0;
						NewKnife_sign_mod=0;
						OnePress_sign_mod=0;
						}
					else if(PaperCutEnb_signal==2)	
						{
						if((OneKnife_sign_mod==3)&&(OnePress_sign_mod==3)&&(NewKnife_sign_mod==3))  //һ������ѭ��
							{
							PressCircle_mode=0;
							if((AllPressUp_flag==1)&&(AllKnifeUp_flag==1))
								{
								CutPressRoll_flag=1;
							//**************��ǰ �ߴ����
								if(Run_flag==0)
									{
									if(InTargetPosit_flag==1)	//Ŀ��λ��
										{
										if(Unit!=UNIT_MM)//inch
											BeforeKnife_offset_in=TargetSize_inch;
										}
									BeforeKnife_offset=CurrentSize_temp;
									FrontKnifeSize_dis(0);
									BeforeKnifeNo_flag=0;
									BeforeKnifeSize=0;
									}
							//------
								if(WorkMode==TEACH_MODE)//ʾ�� ģʽ--------����һ������
									{
									RenewOneKnife_data();//CurrentSize
									}
								else if((WorkMode==AUTO_MODE)||(WorkMode==SELF_CUT_MODE))  //�Զ� �Ե� ģʽ
									{
									if(Run_flag==0)
										{
										if((GoFrontEn_flag==0)&&(GoBackEn_flag==0))
											{
											if(MotorType<MOTOR_AC_SERVO)
												{
												if(ToTargetStop_flag==1)
													{
													// if(InTargetPosit_flag==1)	//��ͣ�� Ŀ��λ��		20171017����
														AutoRun_AutoPush_exec();  // �Զ� ѭ������
													}
												else   //�� ����
													AutoRun_AutoPush_exec();  // �Զ� ѭ������
												}
											else	
												AutoRun_AutoPush_exec();  // �Զ� ѭ������
											//RunToCusor_flag=1;
											//if(AutoCutStart_flag==0)  //δ���� ���� �� ���һ��ѭ��
												OneCutRoutine_flag=1;
											}
										}
									}
								OneKnife_sign_mod=0;
								NewKnife_sign_mod=0;
								OnePress_sign_mod=0;
								CutPressRoll_flag=0;
								}
							else
								{
								
								}
								
							}
						else
							{
							// // if(MotorType!=MOTOR_DC670_SERVO)
								NewKnife_sign_mod=0;
							if(((OneKnife_sign_mod&0x3)==3)||((OnePress_sign_mod&0x3)==3)||((NewKnife_sign_mod&0x3)==3))
								{
								CutRelease_time++;
								if(CutRelease_time>2000)   //��ʱ �����ź���ʧ
									{
									CutRelease_time=0;
									OneKnife_sign_mod=0;
									NewKnife_sign_mod=0;
									OnePress_sign_mod=0;
									CutPressRoll_flag=0;
									}
								}
							}
						}
					
					//--------------------------------------------ѹֽѭ��
					if(Run_flag==0)
						{
						if(WorkMode == AUTO_MODE)
							{
							if(PressCircle_mode== 2)
								{
								PressCircle_mode=0;
								volatile pInt8U pdata=(pInt8U)&OneKnife_data;
								GetOneKnife_datas(Pro_data.pro_num, Knife_order, pdata);//
								if((OneKnife_data.k_flag&0x0f)==PRESS_FLAG) //ѹֽ ��־  ���Զ��ߵ���һ��
									{
									AutoRun_AutoPush_exec();
									}
								}
							}
						}
						
					//------------
					OutLimit_check(); //�ⲿ��λ	
							break;	
			case MANUAL_IO_TEST_MODE:	//���Զ˿�
					IOinputTest();//IO  �������*******
							break;	
			}	
					 
			
		
		DisplayFlashTime++;
		if(DisplayFlashTime>=2)
			{
			DisplayFlashTime=0;
			NowSizeNum_dis();  // �ߴ�ʵʱ ��ʾ
			}
		 
		if(Carrier_IN==0)  //�а� �ź�
			{
			if(Hold_Down_flag==0)
				{
				Hold_Down_flag=1;
				Hold_Up_flag=0;
				Size_MIN=FrontLimit;
				if(Unit==UNIT_MM)
					Size_MIN_num=Size_MIN;
				else
					Size_MIN_num=Size_MIN*100/254;
				if(PromptDis_flag==1)
					PromptNum_dis();
				}
			}
		else
			{
			if(Hold_Up_flag==0)
				{
				Hold_Up_flag=1;
				Hold_Down_flag=0;
				Size_MIN=MiddleLimit;
				if(Unit==UNIT_MM)
					Size_MIN_num=Size_MIN;
				else
					Size_MIN_num=Size_MIN*100/254;
				if(PromptDis_flag==1)
					PromptNum_dis();
				}
			}  
		
		 
		//******************���п���	
		if(Run_flag==1)
			{
			if(RunStop_flag==0)
				{
				switch(MotorType) 
					{
					case MOTOR_FREQ_5_SPD_RST:
					case MOTOR_FREQ_3_SPD:
					case MOTOR_FREQ_3_SPD_RST:
						if(ForceStop_flag==0)
							{
							if(BackStop_flag==0)
								{
								if((OutMiddle_limit==0))	//20170904
									MoveSpeedCtrl();
								else
									{
									if(Forward_flag==0)
									MoveSpeedCtrl();
								}
								}
							else
								{
								stop_time++;
								if(stop_time>=500)  //���˽��� �ȴ�
									{
									BackStop_flag=0;
									Backward_flag=0;
									}
								}
							FreqRuningLimit_ctrl();  //������  �ⲿ�ź�	
							}
						else  //�ֶ� ����ֹͣ
							{
							stop_time++;
							if(stop_time>300)
								{
								stop_time=0;
								if(MoveSpeed<4)  //����
									{
									MoveSpeed++;
									SetMotorSpeed(MoveSpeed);
									}
								else
									{      //ֹͣ
									//MoveSpeed=5;
									//SetMotorSpeed(MoveSpeed);
									SelfLockEn_flag=0; //ȡ������
									ToTargetStop_flag=0;
									MoveStop();
									ForceStop_flag=0;
									BackStop_flag=0;
									Backward_flag=0;
									Forward_flag=0;
									Run_flag=0;
									InTargetPosit_flag=0;	//Ŀ��λ��
									TargetSize=0;
									TargetSize_temp=0;
									BeforeKnife_offset_in=0;
									AutoPushRun_flag=0; //�Զ���ֽ ����
									AutoRoute_flag=0;
									RunStop_flag=0;
									AirOffOK_flag=0;
									}
								}
							}

								break;
					// // case MOTOR_DC_SERVO:
					// // case MOTOR_DC670_SERVO:
						// // ServoRunning_ctrl(); //ֱ���ŷ� ���п���
								// // break;
					case MOTOR_AC_SERVO:
					case MOTOR_AC_SERVO_REV:
					case MOTOR_AC_A6_SERVO:
						ACMotorRunning_ctrl(); //�����ŷ� ���п���
						AC_MotorRuningLimit_ctrl();  //������  ���ⲿ�ź� ֹͣ
								break;
					}
				}
			
			}	
		else 		
			{
			if(RunStop_flag==1)
				{//�Զ�����ֹͣ��
				//if(AutoCutStart_flag==0)//  �Զ����� δ����
				//	{
				//	stop_time++;
					//if(stop_time>1)
						//{
				
				switch(MotorType)
					{
					case MOTOR_FREQ_5_SPD_RST:
					case MOTOR_FREQ_3_SPD:
					case MOTOR_FREQ_3_SPD_RST:
						if(CurrentSize>TargetSize)
							{
							temp=CurrentSize-TargetSize;
							}
						else
							{
							temp=TargetSize-CurrentSize;
							}
						if(temp<VirtualTargetSizeGap)  //�������Χ  ------����ȷ��
							{
							//Run_flag=0;
							
							if(AutoPushRun_flag==1)   //�Զ�  ��ֽ ������--------------------------------
								{
								//CursorDown_inTable();//**** ������� ��ʾ ����
								RunTo_cursor();//    ���е���һ��
								AutoPushRun_flag=0;
								}
							else   //------------ֹͣ�� Ŀ��λ��
								{/*
								switch(MotorType) //3���ٲ�����λ   ����������
									{
									case MOTOR_FREQ_5_SPD_RST:
									case MOTOR_FREQ_3_SPD_RST:
									//		SelfLockEn_flag=1;
												break;
									}*/
								TargetBell_flag=1;  //������ ����
								TargetBell_mode=0;
								
								RLOUT1_OFF; RLOUT1_1_OFF;   // ������� ����	
								AutoCutPush_exec();  //�Զ�����	
								//OneCutRoutine_flag=0;
								InTargetPosit_flag=1;	//��Ŀ��λ��
								
								}
							}
						RunStop_flag=0;	
							break;
					// // case MOTOR_DC_SERVO:
					// // case MOTOR_DC670_SERVO:
						// // stop_time++;
						// // if(stop_time>300)
							// // {
							// // RunStop_flag=0;
							// // if(CurrentSize>TargetSize)
								// // {
								// // temp=CurrentSize-TargetSize;
								// // }
							// // else
								// // {
								// // temp=TargetSize-CurrentSize;
								// // }
							// // if(temp<DC_VIRTURE_SIZE)  //��Ŀ��λ��
								// // {
								// // if(AutoPushRun_flag==1)   //�Զ�  ��ֽ ������--------------------------------
									// // {
									// // //CursorDown_inTable();//**** ������� ��ʾ ����
									// // RunTo_cursor();//    ���е���һ��
									// // AutoPushRun_flag=0;
									// // }
								// // else   //------------ֹͣ�� Ŀ��λ��
									// // {
									// // if(BellStart_flag==0)
										// // {
										// // TargetBell_flag=1;  //������ ����
										// // TargetBell_mode=0;
										// // }
									// // BellStart_flag=0;
									
									// // RLOUT1_OFF;    // ������� ����	
									// // AutoCutPush_exec();  //�Զ�����	
									// // //OneCutRoutine_flag=0;
									// // InTargetPosit_flag=1;	//��Ŀ��λ��
									// // }
								// // }
							// // else
								// // {
								// // if(ServoAutoPushFinish_flag==1)
									// // {
									// // ServoAutoPushFinish_flag=0;
									// // if(AutoPushRun_flag==1)   //�Զ�  ��ֽ ������--------------------------------
										// // {
										// // //CursorDown_inTable();//**** ������� ��ʾ ����
										// // RunTo_cursor();//    ���е���һ��
										// // AutoPushRun_flag=0;
										// // }
									// // }
								// // else//ֱ���ŷ� ģʽ    ������ֹͣ��
									// // {
									// // Run_flag=0;
									// // InTargetPosit_flag=0;	//Ŀ��λ��
									// // TargetSize=0;
									// // BeforeKnife_offset_in=0;
									// // AutoPushRun_flag=0;
									// // DcServoGoTarget_flag=0;
									// // }
								// // }	
							// // }
							// // break;
					case MOTOR_AC_SERVO:
					case MOTOR_AC_SERVO_REV:
						stop_time++;
						if(stop_time>150)	
							{
							RunStop_flag=0;
							if(AutoPushRun_flag==1)   //�Զ�  ��ֽ ������--------------------------------
								{
								//CursorDown_inTable();//**** ������� ��ʾ ����
								RunTo_cursor();//    ���е���һ��
								AutoPushRun_flag=0;
								}
							else   //------------ֹͣ�� Ŀ��λ��
								{
								TargetBell_flag=1;  //������ ����
								TargetBell_mode=0;
								if(ACServoDrvErr_flag==0)
									{
									RLOUT1_OFF;RLOUT1_1_OFF;    // ������� ����	
									}
								AutoCutPush_exec();  //�Զ�����	
								//OneCutRoutine_flag=0;
								InTargetPosit_flag=1;	//��Ŀ��λ��
								
								//-----------
								if(WorkMode == AUTO_MODE)//�Զ�
									{
									if(Knife_order==OnePro_head.pro_knifeSUM)	//���е� last��
										{
										if(AmendSwitch_flag==1)//ƫ���� ����ģʽ ����-----------------------------------------------
											{
											// AmendSize=0;
											// AmendStartRun_flag=0;
											AmendOver_flag=1;	//ƫ���� ����ģʽ over
											}
										}
									else//(Knife_order==1)	//���е� ��һ��	
										{
										AmendOver_flag=0;
										}
									}
								
								}
							}
							
							break;
					case MOTOR_AC_A6_SERVO:
						stop_time++;
						if(stop_time>=150)	
							{
							stop_time=150;	
							RunStop_flag=0;
							if(AutoPushRun_flag==1)   //�Զ�  ��ֽ ������--------------------------------
								{
								//CursorDown_inTable();//**** ������� ��ʾ ����
								RunTo_cursor();//    ���е���һ��
								AutoPushRun_flag=0;
								}
							else   //------------ֹͣ�� Ŀ��λ��
								{
								if(A6CoderEqual_flag==0)//��ǰ�ߴ�==A6������ֵ
									{
									ACMotorStopCheck();	//���� ��������ʵ�ʳߴ�
									}
								else	//�ߴ���ȷ
									{
									TargetBell_flag=1;  //������ ����
									TargetBell_mode=0;
									if(ACServoDrvErr_flag==0)
										RLOUT1_OFF;    // ������� ����	
									AutoCutPush_exec();  //�Զ�����	
									//OneCutRoutine_flag=0;
									InTargetPosit_flag=1;	//��Ŀ��λ��
									
									//-----------
									if(WorkMode == AUTO_MODE)//�Զ�
										{
										if(Knife_order==OnePro_head.pro_knifeSUM)	//���е� last��
											{
											if(AmendSwitch_flag==1)//ƫ���� ����ģʽ ����-----------------------------------------------
												{
												// AmendSize=0;
												// AmendStartRun_flag=0;
												AmendOver_flag=1;	//ƫ���� ����ģʽ over
												}
											}
										else//(Knife_order==1)	//���е� ��һ��	
											{
											AmendOver_flag=0;
											}
										}	
									}
									
									
								
								
								}
							}
							break;
					}		
					
						
						
						
						//if(AutoCutStart_flag==0)	
						//	RunStop_flag=0;
					//	}
					//}
				//else   //�Զ�����  ��
				//	{
					//AutoCutPush_exec();  //�Զ�����
				//	}
				
				}
			else
				{
				Joggle_GoFast(); //�㶯
				/*
				if(SelfLockEn_flag==1)  
					{
					if(Wheel_limit==1)
						{
						SelfLockEn_flag=0;//���� ȡ��
						ToTargetStop_flag=0;
						TargetSize=0;
						BeforeKnife_offset_in=0;
						InTargetPosit_flag=0;	//��Ŀ��λ��
						}
					}*/
				CutEnable_Exec();  //���� ���� 
				// // if((MotorType==MOTOR_DC_SERVO)||(MotorType==MOTOR_DC670_SERVO))
					// // {
					// // if(DcServoGoTarget_flag==1)
						// // {
						// // if(Wheel_limit==1)   //����
							// // DcServoGoTarget_flag=0;
						// // }
					// // }	
				}
			} 
			
		 }  
	  else              //���빤��ģʽǰ  ׼��-------------------
		 {
		 if(Board_TestMod==0)//�ǹ��ܲ���ģʽ
			{
			switch(MotorType)
				{
				case MOTOR_FREQ_5_SPD_RST:
				case MOTOR_FREQ_3_SPD:
				case MOTOR_FREQ_3_SPD_RST:
					FreqWorkStart_check();
					Joggle_GoFast(); //�㶯
					CutEnable_Exec();  //���� ���� 
						break;
				// // case MOTOR_DC_SERVO:
				// // case MOTOR_DC670_SERVO:
					// // ServoWorkStart_check();  //����ģʽǰ  ׼��
						// // break;
				case MOTOR_AC_SERVO:	
				case MOTOR_AC_SERVO_REV:	
				case MOTOR_AC_A6_SERVO:	
					if(ACServoDrvErr_flag==0)
						ACServoWorkStart_check();  //�����ŷ�  ����ģʽǰ  ׼��
					else	
						{
						/***
						if(KeyLinkDis_flag==0)
							{
							KeyLinkDis_flag=1;
							GLCD_SetWindow_Fill(KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y,KEYBOARD_CHECK_X+START_PROM_WIDE-1, KEYBOARD_CHECK_Y+START_PROM_HIGH-1, 0xfffff, 0xffff);
							if(KeyboardLink_flag==0) //
								{
								switch(Language)
									{
									case CHN_HAN:
											Printf24("����δ����!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
											break;
									case ENGLISH:
											Printf24("Keyboard is off!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
											break;
									case INDONSIA:	//ӡ��
											Printf24("Keyboard tidak terhubung!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
											break;
									case PORTUGAL:	//������
											Printf24("O teclado n?o est�� conectado!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
											ASCII_Printf("a",ASCII24_MODE,12,24,PUTAO_ZK24, KEYBOARD_CHECK_X+(11*12),KEYBOARD_CHECK_Y+5,RED_COLOR,0xffff);
											break;
									}
								}
							else
								{
								switch(Language)
									{
									case CHN_HAN:
											Printf24("������������!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
											break;
									case ENGLISH:
											Printf24("Keyboard is OK!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
											break;
									case INDONSIA:	//ӡ��
											Printf24("Keyboard dihubungkan!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
											break;
									case PORTUGAL:	//������
											Printf24("Teclado conectado corretamente!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
											break;
									}
								}
							}
							**/
						}
						break;
				}
			}
		 }
     
	  //-----------------------------------------------���� ����ģʽ��
	 if(Board_TestMod==TEST_BOARD)	//���� �˿ڲ��� 
	     {
		 /*
		 if(Borard1_2==1)
            IOinputTest1_2();//IO  �������********
	     else
	        IOinputTest1_3();//IO  �������********
			*/
		 IOinputTest();//IO  �������*******	
	     }
	  
	 //-------------------����ͨ��-----����----------------
	 switch(Uart_mod)
		 {
		 case 0:
			DownFile_Exec();  //*******************����  ����
			break;
		 case 1:  //�ŷ�ͨѶ
			ServoRev_Exec(); 
			break;
		 }
      }  
 
   

			
   }

#endif
}
   

   



void Time_dis(void)
{
volatile Int16U px,py;
volatile Int16U gap1,gap2,gap3;
Int16U Num_color,Back_color;
     
px=30;
//py=20;
py=0;
gap1=50,gap2=12,gap3=24;
Num_color=WHITE_COLOR;
Back_color=BLACK_COLOR;
if(Sec!=SecTemp)
	{
	SecTemp=Sec;
   Bcd[0]=2+48;
   Bcd[1]=0+48;
   Bcd[2]=(Year>>4)+48;
   Bcd[3]=(Year&0xf)+48;
   Bcd[4]=0;
   Printf24(Bcd,px,py,Num_color,1,Back_color);px+=gap1;
   Printf24("-",px,py,Num_color,1,Back_color);px+=gap2;
   
   Bcd[0]=(Month>>4)+48;
   Bcd[1]=(Month&0xf)+48;
   Bcd[2]=0;
   Bcd[3]=0;
   Bcd[4]=0;
   Printf24(Bcd,px,py,Num_color,1,Back_color);px+=gap3;
   Printf24("-",px,py,Num_color,1,Back_color);px+=gap2;

   Bcd[0]=(Dom>>4)+48;
   Bcd[1]=(Dom&0xf)+48;
   Bcd[2]=0;
   Bcd[3]=0;
   Bcd[4]=0;
   Printf24(Bcd,px,py,Num_color,1,Back_color);px+=gap1;

   Bcd[0]=(Hour>>4)+48;
   Bcd[1]=(Hour&0xf)+48;
   Bcd[2]=0;
   Bcd[3]=0;
   Bcd[4]=0;
   Printf24(Bcd,px,py,Num_color,1,Back_color);px+=gap3;
   Printf24(":",px,py,Num_color,1,Back_color);px+=gap2;

   Bcd[0]=(Min>>4)+48;
   Bcd[1]=(Min&0xf)+48;
   Bcd[2]=0;
   Bcd[3]=0;
   Bcd[4]=0;
   Printf24(Bcd,px,py,Num_color,1,Back_color);px+=gap3;
   Printf24(":",px,py,Num_color,1,Back_color);px+=gap2;
   
   Bcd[0]=(Sec>>4)+48;
   Bcd[1]=(Sec&0xf)+48;
   Printf24(Bcd,px,py,Num_color,1,Back_color);
	}
}

void CutEnable_Exec(void)  //���� �������
{
if(CutPermit_flag==0)//-------------
	{
	if(InTargetPosit_flag==0)
		{
		if((GoFrontEn_flag==0)&&(GoBackEn_flag==0))
			{
			switch(MotorType)
				{
				case MOTOR_FREQ_5_SPD_RST:
				case MOTOR_FREQ_3_SPD:
				case MOTOR_FREQ_3_SPD_RST:
					if(FreqMotorStop_flag==1)  //�Ѿ�ֹͣ  ��
						{
						RLOUT1_OFF; RLOUT1_1_OFF;   // �������
						CutPermit_flag=1;
						}
						break;
				// // case MOTOR_DC_SERVO:	
				// // case MOTOR_DC670_SERVO:
					// // if(ServoMoving_flag==0)
						// // {
						// // RLOUT1_OFF;    // �������
						// // CutPermit_flag=1;
						// // }
						// // break;
				case MOTOR_AC_SERVO:
				case MOTOR_AC_SERVO_REV:
				case MOTOR_AC_A6_SERVO:
					if(ACServoDrvErr_flag==0)
						{
						RLOUT1_OFF; RLOUT1_1_OFF;   // �������
						}
						
					CutPermit_flag=1;
						break;
				}		
			}
		}
	}
	
}

void AutoCutPush_exec(void)  //�Զ����� ����ֽ
{
if((WorkMode==SELF_CUT_MODE)||(WorkMode==AUTO_MODE)||(WorkMode==TEACH_MODE))  //�Ե�,�Զ� ʾ����ģʽ
	{
	if((OneKnife_data.k_flag&0x0f)==PUSH_FLAG) //��ֽ ��־  ���Զ��ߵ���һ��
		{
		AutoRun_AutoPush_exec();
		OneCutRoutine_flag=1;
		}
	else
		{
		if(OneCutRoutine_flag==1) //һ������ѭ�� ��
			{
			if((OneKnife_data.k_flag&0x0f)==KNIFE_FLAG) //�� ��־
				{
				if(WorkMode==SELF_CUT_MODE)
					{
					if(AutoCutDisable_flag==0)//�Ե������Ч
						{
					if(AutoCutStart_flag==0)
						{
							// volatile Int32U tt=5000000;
								volatile Int32U tt=5000;
						while(tt--);
						RLOUT4_OFF;
						AutoCutTime=0;
						AutoCutStart_flag=1;//�Զ� ���� ����
						BellOUT_ON;
						//Run_flag=1;//---------------------------------------------------
						CutEnBegin_flag=1;
						CutDelayTime=0;
						
						TargetBell_flag=0;  //2 bell 
						TargetBell_mode=0;
						}
					
					}
					else
						{
						AutoCutDisable_flag=0;
						}	
					}
				}
			OneCutRoutine_flag=0;
			}
		else
			{
			}
		}
	// // if((MotorType>MOTOR_FREQ_5_SPD_RST)&&(MotorType<MOTOR_DC_SERVO)||(MotorType>=MOTOR_AC_SERVO))
	if(MotorType<=MOTOR_AC_SERVO_REV)	//�����־  ��λ�Ͽ�����
		{
		if((OneKnife_data.k_flag&0xf0)==AIR_FLAG) //���� ��־	��Ͽ�
			{
			RLOUT3_ON;//RLOUT2_ON;//�����Ͽ�
			AirOffOK_flag=1; //����FLAG	������־
			}
		else		//�պ�
			{
			//RLOUT3_OFF;//RLOUT2_OFF;//�����պ�
			AirOffOK_flag=0;
			}	
		PressUp_flag=0;
		PressDown_flag=0;
		}
	}
}

void RenewOneKnife_data(void)
{
pInt8U pKdata;
Int32U data;
//----��������----------------
if(Unit==UNIT_MM)//
	{
	data=CurrentSize_temp;
	}
else	//inch
	{
	data=current_inch;
	}
if(Knife_order>OnePro_head.pro_knifeSUM)//���²��� �ܵ���
	{
	OnePro_head.pro_knifeSUM=Knife_order;
	}
pKdata=(pInt8U)&OneKnife_data;
GetOneKnife_datas(Pro_data.pro_num, Knife_order, pKdata);//
OneKnife_data.size=data;  //�ߴ��޸�
// OneKnife_data.k_flag&=0xf0;  //��� ��־
OneKnife_data.k_flag=NO_FLAG;  //��� ��־
SaveOneKnife_datas(Pro_data.pro_num, Knife_order , pKdata);//����һ������
	//-----��ʾ
KnifeSize_dis(cursor_row,data,0);//�ߴ�
if(Knife_order<MAX_Knife)           //�������
	{
	Knife_order++;
	StepNum_dis(OnePro_head.pro_knifeSUM,Knife_order);//�������
	if(cursor_row<(PageKf_Size-1))
		{
		CursorKnife_dis(cursor_row, 0);//��ɫ�����ʧ
		OneKnifeDataSel_dis(Knife_order-1, cursor_row,0);  //һ������ ---������ʾ
		cursor_row++;
		CursorKnife_dis(cursor_row, 1);//��ɫ���������ʾ
		OneKnifeDataSel_dis(Knife_order, cursor_row,RED_COLOR);  //һ������ ������ʾ
		}
	else   //ҳ��
		{
		Size_1page_dis(Knife_order-(PageKf_Size-1),0);//һҳ�ߴ���ʾ
		}	
	}
						
}

void OutLimit_check(void) //�ⲿ��λ ����
{
Int16U x,y;
Int32U coce_temp=0;
Int8U dis_buf[5]={0};
if(MotorType>=MOTOR_AC_SERVO)
	Wheel_limit=0;
if(outF_flag==0)//**************�ⲿǰ��λ
	{
	if(FrontLimit_IN!=0)
		{
		outLimF_time=0;
		outF_flag=1;
		}
	}
else
	{
	if(OutFront_limit==0)
		{
		if(FrontLimit_IN!=0)
			{
			outLimF_time++;
			if(outLimF_time>=20)
				{
				OutFront_limit=1;
				PromptDis_flag=0;
				if(WorkStart_flag==1)
					{
					x=REMIND_WINDOW_X,y=REMIND_WINDOW_Y;
					GLCD_SetWindow_Fill( x, y, x+REMIND_LENGTH, y+30, 0xfffff, 0xffff);//��ʾ��
					switch(Language)
						{
						case CHN_HAN:
							Printf24("ǰ��λ�Ͽ�!",x,y+5,RED_COLOR,1,0xffff);
								break;
						case ENGLISH:
							Printf24("Front-Limit is off!",x,y+5,RED_COLOR,1,0xffff);
								break;
						case INDONSIA:	//ӡ��
							Printf24("Lepaskan batas depan!",x,y+5,RED_COLOR,1,0xffff);
								break;
						case PORTUGAL:	//������
							Printf24("A primeira parada ��desconectada",x,y+5,RED_COLOR,1,0xffff);
								break;
						}
					}
				else
					{
					switch(MotorType)
						{
						case MOTOR_FREQ_5_SPD_RST:
						case MOTOR_FREQ_3_SPD:
						case MOTOR_FREQ_3_SPD_RST:
							if(StartCheck_mode<12)		
								{
								if(BackLimit_IN!=0)	//ǰ��ͬʱ
									{
									x=START_PROMPT_X2,y=START_PROMPT_Y2;
									GLCD_SetWindow_Fill( x, y, x-1+START_PROM_WIDE, y-1+30, 0xfffff, 0xffff);//��ʾ
									switch(Language)
										{
										case CHN_HAN:
											Printf24("ǰ��λ�Ͽ�!",x,y+5,RED_COLOR,1,0xffff);
												break;
										case ENGLISH:
											Printf24("Front-Limit is off!",x,y+5,RED_COLOR,1,0xffff);
												break;
										case INDONSIA:	//ӡ��
											Printf24("Lepaskan batas depan!",x,y+5,RED_COLOR,1,0xffff);
												break;
										case PORTUGAL:	//������
											Printf24("A primeira parada ��desconectada",x,y+5,RED_COLOR,1,0xffff);
												break;
										}	
									}
								}
							else
								{
								x=START_PROMPT_X2,y=START_PROMPT_Y2;
								GLCD_SetWindow_Fill( x, y, x-1+START_PROM_WIDE, y-1+30, 0xfffff, 0xffff);//��ʾ
								switch(Language)
									{
									case CHN_HAN:
										Printf24("ǰ��λ�Ͽ�!",x,y+5,RED_COLOR,1,0xffff);
											break;
									case ENGLISH:
										Printf24("Front-Limit is off!",x,y+5,RED_COLOR,1,0xffff);
											break;
									case INDONSIA:	//ӡ��
										Printf24("Lepaskan batas depan!",x,y+5,RED_COLOR,1,0xffff);
											break;
									case PORTUGAL:	//������
										Printf24("A primeira parada ��desconectada",x,y+5,RED_COLOR,1,0xffff);
											break;
									}	
								}
										break;
						// // case MOTOR_DC_SERVO:
						// // case MOTOR_DC670_SERVO:
								// // x=START_PROMPT_X2,y=START_PROMPT_Y2;
								// // GLCD_SetWindow_Fill( x, y, x-1+START_PROM_WIDE, y-1+30, 0xfffff, 0xffff);//��ʾ
								// // switch(Language)
									// // {
									// // case CHN_HAN:
										// // Printf24("ǰ��λ�Ͽ�!",x,y+5,RED_COLOR,1,0xffff);
											// // break;
									// // case ENGLISH:
										// // Printf24("Front-Limit is off!",x,y+5,RED_COLOR,1,0xffff);
											// // break;
									// // case INDONSIA:	//ӡ��
										// // Printf24("Lepaskan batas depan!",x,y+5,RED_COLOR,1,0xffff);
											// // break;
									// // case PORTUGAL:	//������
										// // Printf24("A primeira parada ��desconectada",x,y+5,RED_COLOR,1,0xffff);
											// // break;
									// // }	
										// // break;
						case MOTOR_AC_SERVO:
						case MOTOR_AC_SERVO_REV:	
						case MOTOR_AC_A6_SERVO:	
							if(StartCheck_mode<11)		
								{
								if(BackLimit_IN!=0)	//ǰ��ͬʱ
									{
									x=START_PROMPT_X2,y=START_PROMPT_Y2;
									GLCD_SetWindow_Fill( x, y, x-1+START_PROM_WIDE, y-1+30, 0xfffff, 0xffff);//��ʾ
									switch(Language)
										{
										case CHN_HAN:
											Printf24("ǰ��λ�Ͽ�!",x,y+5,RED_COLOR,1,0xffff);
												break;
										case ENGLISH:
											Printf24("Front-Limit is off!",x,y+5,RED_COLOR,1,0xffff);
												break;
										case INDONSIA:	//ӡ��
											Printf24("Lepaskan batas depan!",x,y+5,RED_COLOR,1,0xffff);
												break;
										case PORTUGAL:	//������
											Printf24("A primeira parada ��desconectada",x,y+5,RED_COLOR,1,0xffff);
												break;
										}	
									}
								}
							else
								{
								x=START_PROMPT_X2,y=START_PROMPT_Y2;
								GLCD_SetWindow_Fill( x, y, x-1+START_PROM_WIDE, y-1+30, 0xfffff, 0xffff);//��ʾ
								switch(Language)
									{
									case CHN_HAN:
										Printf24("ǰ��λ�Ͽ�!",x,y+5,RED_COLOR,1,0xffff);
											break;
									case ENGLISH:
										Printf24("Front-Limit is off!",x,y+5,RED_COLOR,1,0xffff);
											break;
									case INDONSIA:	//ӡ��
										Printf24("Lepaskan batas depan!",x,y+5,RED_COLOR,1,0xffff);
											break;
									case PORTUGAL:	//������
										Printf24("A primeira parada ��desconectada",x,y+5,RED_COLOR,1,0xffff);
											break;
									}	
								}
										break;
						}
					}
				}
			}		
		}
	else
		{
		if(FrontLimit_IN==0)
			{
			OutFront_limit=0;
			outF_flag=0;
			if(WorkStart_flag==1)
				{
				PromptDis_flag=1;
				PromptNum_dis();
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
						if(StartCheck_mode<3)
							{
							if(BackLimit_IN!=0)	//ǰ��ͬʱ
								{
								CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2,    START_PROM_WIDE, START_PROM_HIGH);
								if((Wheel_limit==1)||(OutMiddle_limit==1))  //�м���  ����
									{
									Wheel_limit=0;
									OutMiddle_limit=0;
									outM_flag=0;
									Wheel_flag=0;
									}	
								}
							}
									break;
					// // case MOTOR_DC_SERVO:
					// // case MOTOR_DC670_SERVO:
						// // CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2,    START_PROM_WIDE, START_PROM_HIGH);
						// // if((Wheel_limit==1)||(OutMiddle_limit==1))  //�м���  ����
							// // {
							// // Wheel_limit=0;
							// // OutMiddle_limit=0;
							// // outM_flag=0;
							// // Wheel_flag=0;
							// // }	
									// // break;	
					}
				
				}
			}
		}
	}
if(outM_flag==0)//**************�ⲿ����λ
	{
	if(MiddleLimit_IN!=0)
		{
		outLimM_time=0;
		outM_flag=1;
		}
	}
else
	{
	if(OutMiddle_limit==0)
		{
		if(MiddleLimit_IN!=0)
			{
			outLimM_time++;
			if(outLimM_time>=20)
				{
				OutMiddle_limit=1;
				PromptDis_flag=0;
				if(WorkStart_flag==1)
					{
					x=REMIND_WINDOW_X,y=REMIND_WINDOW_Y;
					GLCD_SetWindow_Fill( x, y, x+REMIND_LENGTH, y+30, 0xfffff, 0xffff);//��ʾ��
					}
				else
					{
					x=START_PROMPT_X2,y=START_PROMPT_Y2;
					GLCD_SetWindow_Fill( x, y, x-1+START_PROM_WIDE, y-1+30, 0xfffff, 0xffff);//��ʾ
					}
					switch(Language)
						{
						case CHN_HAN:
							Printf24("����λ�Ͽ�!",x,y+5,RED_COLOR,1,0xffff);
								break;
						case ENGLISH:
							Printf24("Middle-Limit is off!",x,y+5,RED_COLOR,1,0xffff);
								break;
						case INDONSIA:	//ӡ��
							Printf24("Lepaskan batas!",x,y+5,RED_COLOR,1,0xffff);
								break;
						case PORTUGAL:	//������
							Printf24("Desligue o limite intermedi��",x,y+5,RED_COLOR,1,0xffff);
							Printf24("                            rio!",x,y+5,RED_COLOR,0,0xffff);	//intermedi��rio
								break;
						}
					}
					
				}
			}
	else
		{
		if(MiddleLimit_IN==0)
			{
			OutMiddle_limit=0;
			outM_flag=0;
			if(WorkStart_flag==1)
				{
				PromptDis_flag=1;
				PromptNum_dis();
				}
			else
				{
				CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2,    START_PROM_WIDE, START_PROM_HIGH);
				if((Wheel_limit==1)||(OutFront_limit==1))  //ǰ����  ����
					{
					Wheel_limit=0;
					OutFront_limit=0;
					outF_flag=0;
					Wheel_flag=0;
					}
				}
			}
		}
	}
if(outB_flag==0)//**************�ⲿ����λ
	{
	if(BackLimit_IN!=0)
		{
		outLimB_time=0;
		outB_flag=1;
		}
	}
else
	{
	if(OutBack_limit==0)
		{
		if(BackLimit_IN!=0)
			{
			outLimB_time++;
			if(outLimB_time>=20)
				{
				OutBack_limit=1;
				PromptDis_flag=0;
				if(WorkStart_flag==1)
					{
					GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
					switch(Language)
							{
							case CHN_HAN:
									Printf24("����λ�Ͽ�!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									break;
							case ENGLISH:
									Printf24("Back-Limit is off!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									break;
							case INDONSIA:	//ӡ��
									Printf24("Setelah melepaskan batas!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									break;
							case PORTUGAL:	//������
									Printf24("Desligue o limite traseiro!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									break;
							}
					}
				else
					{
					if(senor==1)
						{
							//---------------------------
						GLCD_SetWindow_Fill(START_PROMPT_X1, START_PROMPT_Y1, START_PROMPT_X1+START_PROM_WIDE-1, START_PROMPT_Y1+START_PROM_HIGH-1, 0xfffff, 0xffff);//��ʾ
						switch(Language)
							{
							case CHN_HAN:
									Printf24("����λ�Ͽ�!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case ENGLISH:
									Printf24("Back-Limit is off!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case INDONSIA:	//ӡ��
									Printf24("Setelah melepaskan batas!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case PORTUGAL:	//������
									Printf24("Desligue o limite traseiro!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							}
						}
					}
				}
			}
		}
	else
		{
		if(BackLimit_IN==0)
			{
			OutBack_limit=0;
			outB_flag=0;
			if(WorkStart_flag==1)
				{
				PromptDis_flag=1;
				PromptNum_dis();
				}
			else
				{
				//---------------------------
				if(senor==1)
					CurrentArea_recover1(START_PROMPT_X1, START_PROMPT_Y1,  START_PROM_WIDE, START_PROM_HIGH);
				}
			}
		}
	}

if(MotorType<MOTOR_AC_SERVO)//(MotorType<MOTOR_DC_SERVO)
	{
	if(Wheel_flag==0)//**************����
		{
		if(HandWheel_IN==0)
			{
			handwheel_time=0;
			Wheel_flag=1;
			}
		}
	else
		{
		if(Wheel_limit==0)
			{
			if(HandWheel_IN==0)
				{
				handwheel_time++;
				if(handwheel_time>=20)
					{
					Wheel_limit=1;
					PromptDis_flag=0;
									qianjinflag=1;
					if(WorkStart_flag==1)
						{
						x=REMIND_WINDOW_X,y=REMIND_WINDOW_Y;
						GLCD_SetWindow_Fill( x, y, x+REMIND_LENGTH, y+30, 0xfffff, 0xffff);//��ʾ��
						}
					else
						{
						x=START_PROMPT_X2,y=START_PROMPT_Y2;
						GLCD_SetWindow_Fill( x, y, x-1+START_PROM_WIDE, y-1+30, 0xfffff, 0xffff);//��ʾ
						}
						switch(Language)
							{
							case CHN_HAN:
								Printf24("����״̬!",x,y+5,RED_COLOR,1,0xffff);
									break;
							case ENGLISH:
								Printf24("HandWheel mode!",x,y+5,RED_COLOR,1,0xffff);
									break;
							case INDONSIA:	//ӡ��
								Printf24("Negara Handwheel!",x,y+5,RED_COLOR,1,0xffff);
									break;
							case PORTUGAL:	//������
								Printf24("Estado Volante!",x,y+5,RED_COLOR,1,0xffff);
									break;
							}	
					//************************ɲ���պ�
						switch(MotorType)
								{
								case MOTOR_FREQ_5_SPD_RST:	//----5����
										RLOUT5_OFF;  //   ɲ���պ�
										RLOUT1_ON; RLOUT1_1_ON;   // ������жϿ�
										break;
								case MOTOR_FREQ_3_SPD:	//----3 ����	
								case MOTOR_FREQ_3_SPD_RST:	//----3 ����+��λ	
										RLOUT2_OFF;  //   ɲ���պ�
										RLOUT1_ON;  RLOUT1_1_ON;   // ������жϿ�
										break;
								}
					}
				}
			}
		else
			{
			if(HandWheel_IN!=0)
				{
				Wheel_limit=0;
				Wheel_flag=0;
				if(WorkStart_flag==1)
					{
					PromptDis_flag=1;
					PromptNum_dis();
					}
				else
					{
					CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2,    START_PROM_WIDE, START_PROM_HIGH);
					if((OutMiddle_limit==1)||(OutFront_limit==1))  //ǰ����  ����
						{
						OutMiddle_limit=0;
						OutFront_limit=0;
						outF_flag=0;
						outM_flag=0;
						}
					}
				//***************************ɲ���Ͽ�
				if(MotorRun_flag==0)
					{
						switch(MotorType)
								{
								case MOTOR_FREQ_5_SPD_RST:	//----5����
										RLOUT5_ON;  //   ɲ���Ͽ�
										RLOUT1_OFF; RLOUT1_1_OFF;    // �������
										break;
								case MOTOR_FREQ_3_SPD:	//----3 ����	
								case MOTOR_FREQ_3_SPD_RST:	//----3 ����+��λ	
										RLOUT2_ON;  //   ɲ���Ͽ�
										RLOUT1_OFF;  RLOUT1_1_OFF;  // �������
										break;
								}
					}
				}
			}
		}	
		
	}
// // if((MotorType==MOTOR_DC_SERVO)||(MotorType==MOTOR_DC670_SERVO))//ֱ��˽��
	// // {
	// // if(WorkStart_flag==1)
		// // {
		// // if(Wheel_flag==0)//**************����
			// // {
			// // if(HandWheel_IN==0)
				// // {
				// // handwheel_time=0;
				// // Wheel_flag=1;
				// // }
			// // }
		// // else
			// // {
			// // if(Wheel_limit==0)
				// // {
				// // if(HandWheel_IN==0)
					// // {
					// // handwheel_time++;
					// // if(handwheel_time>=20)
						// // {
						// // Wheel_limit=1;
						// // PromptDis_flag=0;
							// // GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
						// // switch(Language)
							// // {
							// // case CHN_HAN:
									// // Printf24("����״̬!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									// // break;
							// // case ENGLISH:
									// // Printf24("HandWheel mode!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									// // break;
							// // case INDONSIA:	//ӡ��
									// // Printf24("Negara Handwheel!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									// // break;
							// // case PORTUGAL:	//������
									// // Printf24("Estado Volante!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									// // break;
							// // }
// // //------------------------------������� ״̬--
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
						// // }
					// // }
				// // }
			// // else
				// // {
				// // if(HandWheel_IN!=0)
					// // {
					// // Wheel_limit=0;
					// // Wheel_flag=0;
					// // //if(WorkStart_flag==1)
					// // //	{
						// // PromptDis_flag=1;
						// // PromptNum_dis();
					// // //	}
					
					// // }
				// // }
			// // }	
		// // }
	// // }

if(WorkStart_flag==1)	
	{
	if(OutFront_limit==1)
		{
		if(PromptDis_flag==1)
			{
			PromptDis_flag=0;
			GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
			switch(Language)
				{
				case CHN_HAN:
						Printf24("ǰ��λ�Ͽ�!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
							break;
				case ENGLISH:
						Printf24("Front-Limit is off!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
							break;
				case INDONSIA:	//ӡ��
						Printf24("Lepaskan batas depan!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
							break;
				case PORTUGAL:	//������
						Printf24("A primeira parada ��desconectada",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
						break;
				}
			}
		}
	else if(OutMiddle_limit==1)
			{
			if(PromptDis_flag==1)
				{
				PromptDis_flag=0;
				GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
				switch(Language)
					{
					case CHN_HAN:
							Printf24("����λ�Ͽ�!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
							break;
					case ENGLISH:
							Printf24("Middle-Limit is off!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
							break;
					case INDONSIA:	//ӡ��
							Printf24("Lepaskan batas!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
							break;
					case PORTUGAL:	//������
							Printf24("Desligue o limite intermedi��   ",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
							Printf24("                            rio!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);	//intermedi��rio
							break;
					}
				}
			}
	else if(OutBack_limit==1)
			{
			if(PromptDis_flag==1)
				{
				PromptDis_flag=0;
				GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
				switch(Language)
					{
					case CHN_HAN:
							Printf24("����λ�Ͽ�!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
							break;
					case ENGLISH:
							Printf24("Back-Limit is off!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
							break;
					case INDONSIA:	//ӡ��
							Printf24("Setelah melepaskan batas!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
							break;
					case PORTUGAL:	//������
							Printf24("Desligue o limite traseiro!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
							break;
					}	
				}
			}
	else if(Wheel_limit==1)
			{
			if(MotorType<MOTOR_AC_SERVO)
				{
				if(PromptDis_flag==1)
					{
					PromptDis_flag=0;
					GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
					switch(Language)
						{
						case CHN_HAN:
								Printf24("����״̬!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									break;
						case ENGLISH:
								Printf24("HandWheel mode!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									break;
						case INDONSIA:	//ӡ��
								Printf24("Negara Handwheel!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									break;
						case PORTUGAL:	//������
								Printf24("Estado Volante!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
								break;
						}	
					}
				}
			}
	else if(Z_Pulse_err_flag==1)	//----------------������  pule ����
		{
		if(MotorType<MOTOR_AC_SERVO)	//(MotorType<MOTOR_DC_SERVO)
			{
			coce_temp=(Z_code_error+3)/4;
			dis_buf[0]=	(coce_temp/100)+48;
			dis_buf[1]=	(coce_temp/10)%10+48;
			dis_buf[2]=	(coce_temp%10)+48;
			if(coce_temp!=PulseAB_Z_current)
				{
				PulseAB_Z_current=coce_temp;
				if(PulseAB_Z_save_time<10)
					{
					PulseAB_Z_save_time++;
					SaveCurrentPulseAB();	//���浱ǰ  ����������
					}
				}
			
			if(PromptDis_flag==1)
					{
					PromptDis_flag=0;
					GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
					switch(Language)
						{
						case CHN_HAN:
								Printf24("��������ƥ��!:        ��",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
									break;
						case ENGLISH:
						case INDONSIA:	//ӡ��
						case PORTUGAL:	//������
								Printf16("Encoder not match!:",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
								break;
						}	
					Printf24(dis_buf,REMIND_WINDOW_X+200,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
					}
			}
		}
	else if(Z_Pulse_err_flag==0)	//----------------������  pule
		{
		if(PulseAB_Z_current!=(Z_Pulse>>2))
			{
			PulseAB_Z_current=Z_Pulse>>2;
			SaveCurrentPulseAB();	//����set  ����������
			}
		}
	}
else
	{
	/***
	if(KeyLinkDis_flag==0)
		{
		KeyLinkDis_flag=1;
		GLCD_SetWindow_Fill(KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y,KEYBOARD_CHECK_X+START_PROM_WIDE-1, KEYBOARD_CHECK_Y+START_PROM_HIGH-1, 0xfffff, 0xffff);
		if(KeyboardLink_flag==0) //
			{
			switch(Language)
				{
				case CHN_HAN:
						Printf24("����δ����!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case ENGLISH:
						Printf24("Keyboard is off!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case INDONSIA:	//ӡ��
						Printf24("Keyboard tidak terhubung!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case PORTUGAL:	//������
						Printf24("O teclado n?o est�� conectado!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						ASCII_Printf("a",ASCII24_MODE,12,24,PUTAO_ZK24, KEYBOARD_CHECK_X+(11*12),KEYBOARD_CHECK_Y+5,RED_COLOR,0xffff);
						break;
				}
			}
		else
			{
			switch(Language)
				{
				case CHN_HAN:
						Printf24("������������!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case ENGLISH:
						Printf24("Keyboard is OK!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case INDONSIA:	//ӡ��
						Printf24("Keyboard dihubungkan!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case PORTUGAL:	//������
						Printf24("Teclado conectado corretamente!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				}
			}
		}
		**/
	}
}

void Joggle_GoFast(void)
{
Int32U sp_temp;
switch(MotorType)
	{
	case MOTOR_FREQ_5_SPD_RST:
	case MOTOR_FREQ_3_SPD:
	case MOTOR_FREQ_3_SPD_RST:
		switch(JogRunMode)
			{
			case 0:   //ǰ�� ���� ------����
				if(GoFrontEn_flag==1)   //ǰ��-----------
					{
					if(CurrentSize>Size_MIN)
						{
						sp_temp=CurrentSize-Size_MIN;
						if((sp_temp>50)&&(OutFront_limit==0))
							{
							if((sp_temp<5000)||(OutMiddle_limit==1))  //50mm  ����λ
								{
								MoveSpeed=4;// ����
								}
							else
								{
								if(GoFast_flag==1)
									MoveSpeed=1;    //����
								else
									MoveSpeed=3;	//  ����
								}
							SetMotorSpeed(MoveSpeed);
							MoveForward();//ǰ��
							JogRunMode=1;
							//Run_flag=1;
							}
						}
					}
				else if(GoBackEn_flag==1) //����--------
					{
					if(Size_MAX>CurrentSize)
						{
						sp_temp=Size_MAX-CurrentSize;
						if((sp_temp>50)||(OutBack_limit==0))
							{
							if(sp_temp<5000)
								{
								MoveSpeed=4;// ����
								}
							else
								{
								if(GoFast_flag==1)
									MoveSpeed=1;    //����
								else
									MoveSpeed=3;	//  ����
								}
							SetMotorSpeed(MoveSpeed);
							MoveBack(); //����
							JogRunMode=4;
							//Run_flag=1;
							}
						}
					}
					break;
			case 1:  //���� ǰ��
				if(GoFrontEn_flag==1)
					{
					if(Wheel_limit!=1)
						{
						if(PressStop_check()==0)
							{
							sp_temp=CurrentSize-Size_MIN;
							if(OutFront_limit==0)  //
								{
								if(sp_temp>VirtualTargetSizeGap)
									{
									if((sp_temp<5000)||(OutMiddle_limit==1))  //50mm  ����λ
										{
										MoveSpeed=4;// ����
										SetMotorSpeed(MoveSpeed);
										JogRunMode=2;
										}
									}
								else  //����ǰ���� ֹͣ
									{
									MoveStop();
									JogRunMode=3;
									//Run_flag=0;
									}
								}
							else  //�ⲿǰ��λ   ֹͣ
								{
								//MoveSpeed=5;
								//SetMotorSpeed(MoveSpeed);
								MoveStop();//==============================
								JogRunMode=3;
								//ForceStop_flag=1;
								}
							}
						else         //ѹֽ  ͣ��
							{
							MoveStop();
							JogRunMode=3;
							}
						}
					else  //
						{
						MoveStop();
						JogRunMode=3;
						}
					}
				else  //�����ͷ� ֹͣ
					{
					//MoveSpeed=5;
					//SetMotorSpeed(MoveSpeed);
					MoveStop();//==============================
					JogRunMode=3;
					//ForceStop_flag=1;
					}
						break;
			case 2:  //����  ǰ��
				if(GoFrontEn_flag==1)
					{
					if(Wheel_limit!=1)
						{
						if(PressStop_check()==0)
							{
							sp_temp=CurrentSize-Size_MIN;
							if((sp_temp<VirtualTargetSizeGap)||(OutFront_limit==1))//��ǰ��λ    ֹͣ
								{
								MoveStop();
								JogRunMode=3;
								//Run_flag=0;
								}
							}
						else   //ѹֽ  ͣ��
							{
							MoveStop();
							JogRunMode=3;
							//Run_flag=0;
							}
						}
					else
						{
						MoveStop();
						JogRunMode=3;
						//Run_flag=0;
						}
					}
				else  //�����ͷ� ֹͣ
					{
					MoveStop();
					JogRunMode=3;
					//Run_flag=0;
					}
						break;
			case 3:  //ǰ��ֹͣ��
				
						break;
			case 4:  //���� ����
				if(GoBackEn_flag==1)
					{
					if(Wheel_limit!=1)
						{
						sp_temp=Size_MAX-CurrentSize;
						if(OutBack_limit==0)
							{
							if(sp_temp>VirtualTargetSizeGap)
								{
								if(sp_temp<5000)
									{
									MoveSpeed=4;// ����
									SetMotorSpeed(MoveSpeed);
									JogRunMode=5;
									}
								}
							else//���Ӻ��� ֹͣ
								{
								MoveStop();
								JogRunMode=6;
								Run_flag=0;
								}
							}
						else  //�ⲿ ����  ֹͣ
							{
							//MoveSpeed=5;
							//SetMotorSpeed(MoveSpeed);
							MoveStop();//========================
							JogRunMode=6;
							//ForceStop_flag=1;
							}
						}
					else
						{
						MoveStop();//========================
						JogRunMode=6;
						}
					}
				else//�����ͷ� ֹͣ
					{
					//MoveSpeed=5;
					//SetMotorSpeed(MoveSpeed);
					MoveStop();//========================
					JogRunMode=6;
					//ForceStop_flag=1;
					}
						break;			
			case 5: //���� ����
				if(GoBackEn_flag==1)
					{
					if(Wheel_limit!=1)
						{
						sp_temp=Size_MAX-CurrentSize;
						if((sp_temp<VirtualTargetSizeGap)||(OutBack_limit==1))  //ֹͣ
							{
							MoveStop();
							JogRunMode=6;
							Run_flag=0;
							}
						}
					else
						{
						MoveStop();
						JogRunMode=6;
						}
					}
				else//�����ͷ� ֹͣ
					{
					MoveStop();
					JogRunMode=6;
					Run_flag=0;
					}
						break;
			case 6: //����ֹͣ��
				
						break;
			}
			break;
	// // case MOTOR_DC_SERVO:
	// // case MOTOR_DC670_SERVO:
		// // switch(JogRunMode)
			// // {
			// // case 0:
				// // if(ServoMoving_flag==0)
					// // {
					// // if(GoFrontEn_flag==1)   //ǰ��--------
						// // {
						// // sp_temp=Size_MIN;
						// // DCServoMove_To(sp_temp,JOG_MOVE);
						// // JogRunMode++;
						// // }
					// // else if(GoBackEn_flag==1)  //����--------
						// // {
						// // sp_temp=Size_MAX;
						// // DCServoMove_To(sp_temp,JOG_MOVE);
						// // JogRunMode=4;
						// // }
					// // }
					// // break;
			// // case 1:		//ǰ��--------��
				// // if(GoFrontEn_flag==0)   
					// // {
					// // //if(ServoMoving_flag==1)
						// // DCServoStop();  //ֹͣ����
					// // JogRunMode++;	
					// // ServoStopTime=0;
					// // }
				// // else
					// // {
					// // if(PressStop_check()!=0) //ѹֽ ͣ��
						// // {
						// // DCServoStop();  //ֹͣ����
						// // JogRunMode++;	
						// // ServoStopTime=0;
						// // }
					// // }
					// // break;
			// // case 2: //ǰ�� ֹͣ��------
				// // if(ServoMoving_flag==1)
					// // {
					// // ServoStopTime++;
					// // if(ServoStopTime>=1400)
						// // {
						// // DCServoStop();  //ֹͣ����
						// // ServoStopTime=0;
						// // }
					// // }
				// // else
					// // {
					// // JogRunMode++;
					// // }
					// // break;
			// // case 3:
					// // break;
			// // //----------------------------------------------����---------		
			// // case 4:		//����--------��
				// // if(GoBackEn_flag==0)   
					// // {
					// // //if(ServoMoving_flag==1)
						// // DCServoStop();  //ֹͣ����
					// // JogRunMode++;
					// // ServoStopTime=0;	
					// // }
					// // break;
			// // case 5:	//���� ֹͣ��------
				// // if(ServoMoving_flag==1)
					// // {
					// // ServoStopTime++;
					// // if(ServoStopTime>=1400)
						// // {
						// // DCServoStop();  //ֹͣ����
						// // ServoStopTime=0;
						// // }
					// // }
				// // else
					// // {
					// // JogRunMode++;
					// // }
					// // break;
			// // case 6:
					// // break;
			// // }
		
			// // break;
	case MOTOR_AC_SERVO:
	case MOTOR_AC_SERVO_REV:
	case MOTOR_AC_A6_SERVO:
		switch(JogRunMode)
			{
			case 0:
				if(GoFrontEn_flag==1)   //ǰ��-----------
					{
					if(CurrentSize>Size_MIN)
						{
						sp_temp=CurrentSize-Size_MIN;
						if((sp_temp>50)&&(OutFront_limit==0))
							{
							if((sp_temp<5000)||(OutMiddle_limit==1))  //50mm  ����λ
								{
								ACMotorGoForward();	//ǰ��
								}
							else
							{
							if(GoFast_flag==1)
								ACMotorGoFastForward();  // ���
							else
									ACMotorGoForward();	//ǰ��
								}
							JogRunMode=1;
							}
						}
					}
				else if(GoBackEn_flag==1) //����--------
					{
					if(Size_MAX>CurrentSize)
						{
						sp_temp=Size_MAX-CurrentSize;
						if((sp_temp>50)||(OutBack_limit==0))
							{
							if(sp_temp<5000)
								{
								ACMotorGoBack();  //����
								}
							else
							{
							if(GoFast_flag==1)
								ACMotorGoFastBack();  //����
							else
								ACMotorGoBack();  //����
								}
							JogRunMode=4;
							//Run_flag=1;
							}
						}
					}
				break;
			case 1:  //ǰ�� ��
				if(GoFrontEn_flag==1)
					{
					if(PressStop_check()==0)
						{
						if(OutFront_limit==1)//��ǰ��λ    ֹͣ----------------------
							{
							ACServoStop();  //�����ŷ�	ֹͣ
							JogRunMode=3;
							}
						else
							{
							if(OutMiddle_limit==1)  //�� ��λ
								{
								if(Hold_Up_flag==1)  //�а�  ��  ֹͣ-----------------------
									{
									ACServoStop();  //�����ŷ�	ֹͣ
									JogRunMode=3;
									}
								}
							else
								{
								if(CurrentSize<(Size_MIN+4000)&&CurrentSize>Size_MIN)
									{
									AC_ChangeSPD();  //�ٶȸı�
									JogRunMode=2;
									}
								else
									{
									if(CurrentSize<(Size_MIN+1)&&flagqyx==1)  //����  ����--------------------
										{
										ACServoStop();  //�����ŷ�	ֹͣ
										JogRunMode=3;
										}
									}

								}
							}
						}
					else   //ѹֽ  ͣ��
						{
						ACServoStop();  //�����ŷ�	ֹͣ
						JogRunMode=3;
						//Run_flag=0;
						}
					}
				else
					{
					ACServoStop();  //�����ŷ�	ֹͣ
					JogRunMode=3;
					}
				break;
			case 2:  //ǰ��   ����
				if(GoFrontEn_flag==1)
					{
					if(PressStop_check()==0)
						{
						if(OutFront_limit==1)//��ǰ��λ    ֹͣ
							{
							ACServoStop();  //�����ŷ�	ֹͣ
							JogRunMode=3;
							}
						else
							{
							if(OutMiddle_limit==1)  //�� ��λ
								{
								if(Hold_Up_flag==1)  //�а�  ��  ֹͣ-----------------------
									{
									ACServoStop();  //�����ŷ�	ֹͣ
									JogRunMode=3;
									}
								}
							else
								{
								if(CurrentSize<(Size_MIN+1)&&flagqyx==1)  //����  ����
									{
									ACServoStop();  //�����ŷ�	ֹͣ
									JogRunMode=3;
									}
								}
							}
						}
					else   //ѹֽ  ͣ��
						{
						ACServoStop();  //�����ŷ�	ֹͣ
						JogRunMode=3;
						//Run_flag=0;
						}
					}
				else
					{
					ACServoStop();  //�����ŷ�	ֹͣ
					JogRunMode=3;
					}	
				break;
			case 3:   //ǰ��  ֹͣ��
				
				break;
			case 4:  //���� ����
				if(GoBackEn_flag==1)
					{
					if(OutBack_limit==1)  //����λ  ֹͣ
						{
						ACServoStop();  //�����ŷ�	ֹͣ
						JogRunMode=5;
						}
					else
						{
						if(CurrentSize>=Size_MAX&&flagqyx==2)
							{
							ACServoStop();  //�����ŷ�	ֹͣ
							JogRunMode=5;
							}
						}
					}
				else
					{
					ACServoStop();  //�����ŷ�	ֹͣ
					JogRunMode=5;
					}
				break;
			case 5:  //ֹͣ ��
				break;
			}
			break;
	}

}

void FreqRuningLimit_ctrl(void)  //������  ���ⲿ�ź� ֹͣ
{
Int32U tt;
if(Wheel_limit!=1)
	{
	if(Backward_flag==1)  //����
		{
		// tt=Size_MAX-CurrentSize;
		// if((tt<VirtualTargetSizeGap)||(OutBack_limit==1))  //ֹͣ
		if(OutBack_limit==1)  //ֹͣ
			{
			SelfLockEn_flag=0; //ȡ������
			ToTargetStop_flag=0;
			MoveStop();
			ForceStop_flag=0;
			BackStop_flag=0;
			Backward_flag=0;
			Forward_flag=0;
			Run_flag=0;
			InTargetPosit_flag=0;	//Ŀ��λ��
			TargetSize=0;
			BeforeKnife_offset_in=0;
			AutoPushRun_flag=0;
			}
		}
	else //if(Forward_flag==1)    //ǰ��
		{
		if(PressStop_check()==0)
			{
			// tt=CurrentSize-Size_MIN;
			// if((tt<VirtualTargetSizeGap)||(OutFront_limit==1))//��ǰ��λ    ֹͣ
			if(OutFront_limit==1)//��ǰ��λ    ֹͣ
				{
				SelfLockEn_flag=0; //ȡ������
				ToTargetStop_flag=0;
				MoveStop();
				ForceStop_flag=0;
				BackStop_flag=0;
				Backward_flag=0;
				Forward_flag=0;
				Run_flag=0;
				InTargetPosit_flag=0;	//Ŀ��λ��
				TargetSize=0;
				BeforeKnife_offset_in=0;
				AutoPushRun_flag=0;
				}
			else
				{
				// if(TargetSize<Size_MIN)
				if(TargetSize<MiddleLimit)
					{
					// tt=MiddleLimit-TargetSize;
					// if((tt<5000)||(OutMiddle_limit==1))
					if(OutMiddle_limit==1)
						{
						if(MoveSpeed!=4)
							{
							MoveSpeed=4;
							SetMotorSpeed(MoveSpeed);
							}
						}
					}
				}

			}
		else //ѹֽͣ��
			{
			SelfLockEn_flag=0; //ȡ������
			ToTargetStop_flag=0;
			MoveStop();
			ForceStop_flag=0;
			BackStop_flag=0;
			Backward_flag=0;
			Forward_flag=0;
			Run_flag=0;
			InTargetPosit_flag=0;	//Ŀ��λ��
			TargetSize=0;
			BeforeKnife_offset_in=0;
			AutoPushRun_flag=0;
			}
		}
	}
else
	{
	SelfLockEn_flag=0; //ȡ������
	ToTargetStop_flag=0;
	MoveStop();
	ForceStop_flag=0;
	BackStop_flag=0;
	Backward_flag=0;
	Forward_flag=0;
	Run_flag=0;
	InTargetPosit_flag=0;	//Ŀ��λ��
	TargetSize=0;
	BeforeKnife_offset_in=0;
	AutoPushRun_flag=0;
	}
}

void ServoRunning_ctrl(void) //ֱ���ŷ� ���п���
{
Int32U speed_servo;
Int32U temp;
if(ServoStartDelayTime<1000)
	{
	ServoStartDelayTime++;
	if(ServoStartDelayTime>=900)
		{
		if(ServoSendCou<1)
			{
			if(NowSize_last>CurrentSize)
				speed_servo=NowSize_last-CurrentSize;
			else
				speed_servo=CurrentSize-NowSize_last;
			if(speed_servo<1)
				DcServoStartRun_exec(TargetSize);
			ServoSendCou++;
			}
		}
	ForceStopTime=0;
	}
else    //�������� ��
	{
	if(ServoMoving_flag==0)  //  ��ֹͣ---------
		{
		if(CurrentSize==TargetSize)//�Զ�ֹͣ---------
			{
			RunStop_flag=1;
			stop_time=0;
			ServoPressStop_flag=0;
			Run_flag=0;
			}
		else		//��λ ǿ��ֹͣ----------
			{
			if(ForceStopTime<1200)
				ForceStopTime++;
				//--------------
			if(ForceStopTime==800)
				{
				ForceStopSize=CurrentSize;
				}
			else
				{
				if(ForceStopTime==1000)
					{
					if(ForceStopSize==CurrentSize)
						{
						RunStop_flag=1;
						stop_time=0;
						ServoPressStop_flag=0;
						Run_flag=0;
						}
					}
				}
			}
		}
	else
		{
		if(ServoPressStop_flag==0)
			{
			
			
			if(AutoPushRun_flag==1)//�Զ�  ��ֽ --------------------------------
				{
				if(CurrentSize<=TargetSize+300)
					{
					ServoAutoPushFinish_flag=1;
					
					RunStop_flag=1;
					stop_time=200;
					Run_flag=0;
					}
				}
			
			if(CurrentSize>TargetSize) //ǰ����
				{
				if(PressStop_check()!=0) //ѹֽ ͣ��----------
					{
					DCServoStop();  //ֹͣ����
					ServoPressStop_flag=1;
					}
				}
			
			}
		
		}
		
	if(ServoBack_flag==1)   //������
		{
		if(CurrentSize>=(TargetSize+300))
			{
			if(ChangeTarget_flag==0)
				{
				DCServoMove_To(TargetSize,RUN_MOVE);
				ChangeTarget_flag=1;
				ServoBack_flag=0;
				}
			}
		}

	//------------��ǰbell
	if(AutoPushRun_flag==0)
		{
		if(ServoBack_flag==0)   //
			{
			if(BellStart_flag==0)
				{
				if(CurrentSize>TargetSize)
					{
					temp=CurrentSize-TargetSize;
					}
				else
					{
					temp=TargetSize-CurrentSize;
					}
				if(temp<100)  //��ǰλ��
					{
					BellStart_flag=1;
					
					TargetBell_flag=1;  //������ ����
					TargetBell_mode=0;
					}
				}
			}
		
		}
	}
}

void FreqWorkStart_check(void)  //����ģʽǰ  ׼��
{
if(StartCheck_mode!=10)
	OutLimit_check(); //�ⲿ��λ

switch(StartCheck_mode)
	{
	case 0:
			if(senor==1)    //1   ԭ������
				{
				if(OriginalError_flag==1)
					{
					CurrentArea_recover1(START_PROMPT_X1, START_PROMPT_Y1,    START_PROM_WIDE, START_PROM_HIGH);
					OriginalError_flag=0;//ԭ�����  ���
					BackLimitError_flag=0;
					RunDisplay_flag=0;         //��������  �������м�/////////////////
					PushRstKey_flag=0; 
					}
				if(OutBack_limit==1)//����λ�Ͽ�
					{
					if(BackLimitError_flag==0)
						{
						GLCD_SetWindow_Fill(START_PROMPT_X1, START_PROMPT_Y1, START_PROMPT_X1+START_PROM_WIDE-1, START_PROMPT_Y1+START_PROM_HIGH-1, 0xfffff, 0xffff);//��ʾ
						switch(Language)
							{
							case CHN_HAN:
									Printf24("����λ�Ͽ�!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case ENGLISH:
									Printf24("Back-Limit is off!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case INDONSIA:	//ӡ��
									Printf24("Setelah melepaskan batas!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case PORTUGAL:	//������
									Printf24("Desligue o limite traseiro!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							}
						BackLimitError_flag=1;
						}
					if(OutFront_limit==0)
						{
						StartCheck_mode=3;
						RunDisplay_flag=0;         //ǰ��������  �������м�/////////////////
						PushRstKey_flag=0; 
						}
					}
				else  //2   ��������
					{
					// if((BackLimitError_flag|OriginalError_flag)==1)
					if(BackLimitError_flag==1)
						CurrentArea_recover1(START_PROMPT_X1, START_PROMPT_Y1,    START_PROM_WIDE, START_PROM_HIGH);
					BackLimitError_flag=0;//���޹���  ���
					OriginalError_flag=0;//ԭ�����  ���
					StartCheck_mode=3;    
					RunDisplay_flag=0;         //��������  �������м�/////////////////
					PushRstKey_flag=0; 
					}
				FrontLimitDis_flag=0;
				}
			else     //ԭ�����
				{
				if(OriginalError_flag==0)
						{
						GLCD_SetWindow_Fill(START_PROMPT_X1, START_PROMPT_Y1,   START_PROMPT_X1+START_PROM_WIDE-1, START_PROMPT_Y1+START_PROM_HIGH-1, 0xfffff, 0xffff);//��ʾ
						switch(Language)
							{
							case CHN_HAN:
									Printf24("ԭ�����!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case ENGLISH:
									Printf24("Original fault!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case INDONSIA:	//ӡ��
									Printf24("Asal kesalahan!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;	
							case PORTUGAL:	//������
									Printf24("come ando falha!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									ASCII_Printf("c",ASCII24_MODE,12,24,PUTAO_ZK24, START_PROMPT_X1+(4*12),START_PROMPT_Y1+5,RED_COLOR,0xffff);
									break;	
							}	
						OriginalError_flag=1;
						}
				// if((BackLimitError_flag|OriginalError_flag)==1)
						// CurrentArea_recover1(START_PROMPT_X1, START_PROMPT_Y1,    START_PROM_WIDE, START_PROM_HIGH);
				BackLimitError_flag=0;//���޹���  ���
				// OriginalError_flag=0;//ԭ�����  ���	
				// PushResetPrompt_dis();  //���� ��ֽ�� ��λ  ��ʾ
				// StartCheck_mode++;
				// PushRstKey_flag=0;	
				if(RunDisplay_flag==1)	
					{
					CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2,    START_PROM_WIDE, START_PROM_HIGH);
					RunDisplay_flag=0;
					}
				}
				
				break;
	case 1:		//�ȴ� ��ֽ��  ��λ������ȷ������
			// if((OutBack_limit==0)&&(senor==1)) //ԭ�� ���� ��λ����
			if(senor==1) //ԭ��  ��λ����
				{			//��λ ��ʾ  ��ʧ
				CurrentArea_recover3(PUSH_RESET_PROMPT_X1, PUSH_RESET_PROMPT_Y1, PUSH_RESET_PROMPT_WIDE, PUSH_RESET_PROMPT_HIGH);
				StartCheck_mode=0;//3;    
				RunDisplay_flag=0;         //��������  �������м�////////////////////
				PushRstKey_flag=0;
				}
			else
				{
				// // if((OutBack_limit^senor)!=1)
					// // {
					// // CurrentArea_recover3(PUSH_RESET_PROMPT_X1, PUSH_RESET_PROMPT_Y1, PUSH_RESET_PROMPT_WIDE, PUSH_RESET_PROMPT_HIGH);
					// // StartCheck_mode=0;
					// // }
				}
				break;
	case 2:		// ��ֽ��  ��λ��
			PusherResetTime++;
			if(PusherResetTime>=6000) //8s
				{
				MoveStop();
				StartCheck_mode++;
				RunDisplay_flag=0;//��������  �������м�////////////////////
				if((OutBack_limit==0)&&(senor==1)) //ԭ�� ���� ��λ����
					{
					CurrentArea_recover1(START_PROMPT_X1, START_PROMPT_Y1,    START_PROM_WIDE, START_PROM_HIGH);
					OriginalError_flag=0;//ԭ�����  ���
					}
				else
					{
					StartCheck_mode=0; //δ��λ �����¼��
					PushRstKey_flag=0;
					}
				}
				break;	
		//--------------------------------------------------------------------------------------------------
	case 3:			//
			if(OutBack_limit==0)//if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0))//�ȴ����� ��������  ���� (���м�)
				{
				if((OutMiddle_limit==0)&&(Wheel_limit==0))
					{
					if(senor==1)
						{
						if(OutBack_limit==0)
							{
							if(PushRstKey_flag==0)
								{
								if(RunDisplay_flag==0)
									{
									RunDisplay_flag=1;
									GLCD_SetWindow_Fill( START_PROMPT_X2, START_PROMPT_Y2, START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//��ʾ��
									switch(Language)
										{
										case CHN_HAN:
												Printf24("���Լ�����,�밴���м�!>��˴�",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
													break;
										case ENGLISH:
												Printf24("Computer testing OK, press the RUN key!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
													break;
										case INDONSIA:	//ӡ��
												Printf24("Tes komputer lengkap, tekan tombol Run!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
													break;
										case PORTUGAL:	//������
												Printf16("Computador auto-teste estiver conclu��",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
												Printf16("                                     do, pressione o bot o de execu  o!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,0,0xffff);
												ASCII_Printf("a",ASCII16_MODE,8,16,PUTAO_ZK16, START_PROMPT_X2+(56*8),START_PROMPT_Y2+5,RED_COLOR,0xffff);
												ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, START_PROMPT_X2+(67*8),START_PROMPT_Y2+5,RED_COLOR,0xffff);
												break;
										}
									}
								StartCheck_mode++;
								}
							else  //-------------��ֽ���Զ���λ��
								{
								if(PassCodeEn_flag==0)
									{
									MoveSpeed=2;
									SetMotorSpeed(MoveSpeed);//�и���
									MoveBack(); //����
									//CurrentArea_recover2(REMIND_WINDOW_X, REMIND_WINDOW_Y, START_PROM_WIDE, START_PROM_HIGH);
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
									StartCheck_mode=9;//5
									CodeSensorTime_AB=0;
									}
								else   //-------------����  ������ʾ
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
									StartCheck_mode++;
									}
								}
							}
						else
							{
							StartCheck_mode=0;
							}
						//---------20150629
						if(OriginalError_flag==1)
							{
							CurrentArea_recover1(START_PROMPT_X1, START_PROMPT_Y1,    START_PROM_WIDE, START_PROM_HIGH);
							OriginalError_flag=0;//ԭ�����  ���
							}
						}
					}
				else//RunDisplay_flag=0;
					StartCheck_mode=0;
				}
			else	//�����쳣
				{
				if(OutFront_limit==0)//ǰ����ok
					{
					StartCheck_mode	=5;
					}
				else
					{
					StartCheck_mode	=0;
					GLCD_SetWindow_Fill(START_PROMPT_X2 , START_PROMPT_Y2,START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//��ʾ
					switch(Language)
						{
						case CHN_HAN:
							Printf24("ǰ��λ�Ͽ�!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case ENGLISH:
							Printf24("Front-Limit is off!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case INDONSIA:	//ӡ��
							Printf24("Lepaskan batas depan!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case PORTUGAL:	//������
							Printf24("A primeira parada ��desconectada",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						}	
					}
				}
				break;
	case 4:  //�ȴ�   ���м�����   ��-------------------------����ok ����
			if(OutBack_limit==1)// if((OutFront_limit==1)||(OutMiddle_limit==1)||(Wheel_limit==1)||(OutBack_limit==1)||(senor==0))
				{                //�������쳣
				RunDisplay_flag=0;//���������ʾ
				if(senor==0)//if((OutBack_limit==1)||(senor==0))
					{
					if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0))
						{
						CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2,    START_PROM_WIDE, START_PROM_HIGH);	
						}
					}
				StartCheck_mode=0;
				}
				
			if(OutFront_limit==1)//ǰ�����쳣
				{
				if(FrontLimitDis_flag==0)
					{
					FrontLimitDis_flag=1;
					GLCD_SetWindow_Fill(START_PROMPT_X2 , START_PROMPT_Y2,START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//��ʾ
					switch(Language)
						{
						case CHN_HAN:
							Printf24("ǰ��λ�Ͽ�!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case ENGLISH:
							Printf24("Front-Limit is off!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case INDONSIA:	//ӡ��
							Printf24("Lepaskan batas depan!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case PORTUGAL:	//������
							Printf24("A primeira parada ��desconectada",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						}	
					}
				}
			else//
				{
				if(FrontLimitDis_flag==1)	
					{
					FrontLimitDis_flag=0;
					StartCheck_mode=0;
					}
				}
				break;
	case 5:   //�ȴ�   ���м�����   ��-------------------------only�����쳣����	
				if(OutFront_limit==1)//ǰ�����쳣
					{
					StartCheck_mode	=0;
					GLCD_SetWindow_Fill(START_PROMPT_X2 , START_PROMPT_Y2,START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//��ʾ
					switch(Language)
						{
						case CHN_HAN:
							Printf24("ǰ��λ�Ͽ�!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case ENGLISH:
							Printf24("Front-Limit is off!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case INDONSIA:	//ӡ��
							Printf24("Lepaskan batas depan!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case PORTUGAL:	//������
							Printf24("A primeira parada ��desconectada",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						}
					}
				else		//ǰ����---ok �ָ�
					{
					if(RunDisplay_flag==0)
						{
						RunDisplay_flag=1;
						GLCD_SetWindow_Fill( START_PROMPT_X2, START_PROMPT_Y2, START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//��ʾ��
						switch(Language)
							{
							case CHN_HAN:
									Printf24("���Լ�����,�밴���м�!>��˴�",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
										break;
							case ENGLISH:
									Printf24("Computer testing OK, press the RUN key!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
										break;
							case INDONSIA:	//ӡ��
									Printf24("Tes komputer lengkap, tekan tombol Run!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
										break;
							case PORTUGAL:	//������
									Printf16("Computador auto-teste estiver conclu��",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
									Printf16("                                     do, pressione o bot o de execu  o!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,0,0xffff);
									ASCII_Printf("a",ASCII16_MODE,8,16,PUTAO_ZK16, START_PROMPT_X2+(56*8),START_PROMPT_Y2+5,RED_COLOR,0xffff);
									ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, START_PROMPT_X2+(67*8),START_PROMPT_Y2+5,RED_COLOR,0xffff);
									break;
							}
						}
					if(OutBack_limit==0)
						{
						StartCheck_mode--;//ǰ�����޶�����
						}
					}
				break;
				
	case 6:  //ǰ��   ��-----�����쳣 ����			
			if(OutFront_limit==1)//ǰ����
				{
				MoveStop();
				StartCheck_mode=0;
				}
			else
				{
				stop_time=0;
				StartCheck_mode++;
				}
				break;
	case 7:			
			if(OutFront_limit==1)//ǰ����
				{
				MoveStop();
				StartCheck_mode=0;
				}
			else
				{
				stop_time++;
				if(stop_time>=6000)
					{
					stop_time=0;
					MoveStop();
					if(OutBack_limit==0)
						StartCheck_mode++;
					else
						StartCheck_mode=0;
					}
				}
				break;
	case 8:			//ǰ��һ�ξ��룬 ����	�ָ�������----------	��ʼ  ����������������
			stop_time++;
			if(stop_time>=1000)
				{
				stop_time=0;
				if(PassCodeEn_flag==0)
					{
					MoveSpeed=2;
					SetMotorSpeed(MoveSpeed);//�и���
					MoveBack(); //����
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
					StartCheck_mode++;
					CodeSensorTime_AB=0;
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
				break;
							//--------------------------//////////////////////////0000000000000000000000000000000000000000000///////////////////////////
	case 9://5:  //���ٺ���   ��-----����ok ����     
			//if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0)&&(OutBack_limit==0))
			if(OutBack_limit==0)
				{
				if(senor==0)
					{
					StartCheck_mode+=3;
					stop_time=0;
					}
				else
					{
					if(CodeSensorTime_AB==0)
						{
						Asensor_temp=Encoder_A_IN;
						Bsensor_temp=Encoder_B_IN;
						ABsensor_temp=0;
						}
					if(CodeSensorTime_AB<5000)//5s
						{
						CodeSensorTime_AB++;
						if(Asensor_temp!=Encoder_A_IN)
							ABsensor_temp|=1;
						if(Bsensor_temp!=Encoder_B_IN)
							ABsensor_temp|=2;
						}
					else
						{
						if(ABsensor_temp<3)  //����������
							{
							GLCD_SetWindow_Fill( START_PROMPT_X2, START_PROMPT_Y2, START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//��ʾ��
							switch(Language)
								{
								case CHN_HAN:
										Printf24("����������!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
											break;
								case ENGLISH:
										Printf24("Encoder fault!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
											break;
								case INDONSIA:	//ӡ��
										Printf24("Encoder kesalahan!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
											break;
								case PORTUGAL:	//������
										Printf24("Culpa Encoder!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
											break;
								}
							MoveStop();
							StartCheck_mode++;
							//RunDisplay_flag=0;//���������ʾ
							}
						}
					}
				}
			else   //���� �쳣
				{
				stop_time=0;
				// MoveStop();
				StartCheck_mode+=2;
				}
				break;
	case 10://6:  // ����������   ֹͣ----------
			
				break;
				
	case 11:	//----delay---- ���� ����λ&ԭ�� �ж�-----------------20160123
			if(stop_time<2000)
				{
				stop_time++;
				if(senor==0)//������ ԭ��
					{
					StartCheck_mode+=2;
					stop_time=0;
					}	
				}
			else//����ʱ���   
				{
				// if(OutBack_limit==1)// ��Ȼ�쳣
					// {
					stop_time=0;
					MoveStop();
					StartCheck_mode=0;   //ֹͣ
					// }
				}
				break;
	case 12://7:  // ȥ����	
			// if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0)&&(OutBack_limit==0))
			if(senor==0)
				{
				stop_time++;
				if(stop_time>=20)
					{
					stop_time=0;
					MoveStop();
					StartCheck_mode++;
					}
				}
			else
				{
				stop_time=0;
				}
				break;
	case 13://8:  //ֹͣ�� 
			// if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0))
				stop_time++;	
				if(stop_time>=1000)
					{
					MoveSpeed=4;
					SetMotorSpeed(MoveSpeed);  //����
					MoveForward();//ǰ��
					StartCheck_mode++;
					}
				break;	
	case 14://9:  //����ǰ��   ��
			// if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0)&&(OutBack_limit==0))
			if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0))
				{
				if(senor==1)
					{
					stop_time=0;
					StartCheck_mode++;
					}
				}
			else//�����쳣
				{
				MoveStop();
				StartCheck_mode=0;
				}	
				break;
	case 15:  //	  ԭ��Ϊ��
			// if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0)&&(OutBack_limit==0))
			if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0))
				{
				if(senor==1)
					{
					stop_time++;	
					if(stop_time>=20)  // Z ����  ��������
						{
						stop_time=0;
						Zpulse_cou=0;
						StartCheck_mode++;
						}
					}
				else
					{
					stop_time=0;
					}
				}
			else//�����쳣
				{
				MoveStop();
				StartCheck_mode=0;
				}		
				break;
	case 16:  //Z���� Ϊ��
			// if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0)&&(OutBack_limit==0))
			if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0))
				{
				if(xz==1)
					{
					MoveStop();
					stop_time=0;
					StartCheck_mode++;
					if(Zpulse_cou>(Z_Pulse*2))  //������ ����
						{
						EncoderErr_flag=1;
						}
					}
				}
			else//�����쳣
				{
				MoveStop();
				StartCheck_mode=0;
				}	
				break;	
	case 17:	         //ֹͣ��   ���빤������
			stop_time++;	
			if(stop_time>=50)
				{
				WorkStart_flag=1;
				WorkMode=AUTO_MODE;//PROG_MODE;//���� ��������
				PaperCutEnb_signal=1;
				// TableDis_startcol=RIGHT_ARROW_X; //������ʾ��ʼ��
				Knife_order=1;cursor_row=0;     // ������ ��ʾ ��ͷ
				ProcessRatio=0xff;
				WorkPic_dis();  //���� ��������
				PromptDis_flag=1;
				Size_1page_dis(Knife_order, 0);
				CursorKnife_dis(0,1);//��ɫ���
				muqiancn=OriginalSize*1000;
				CurrentSize=OriginalSize;
				//Current_last=CurrentSize;
				if(EncoderErr_flag==1)
					{
					PromptDis_flag=0;
					GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
					switch(Language)
						{
						case CHN_HAN:
							Printf24("�ߴ����,���������!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
						case ENGLISH:	
							Printf24("Error size,check encoder!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
						case INDONSIA:	//ӡ��
							Printf16("Salah ukuran,silahkan cek encoder!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
						case PORTUGAL:	//������
							Printf16("Tamanho errado,verifique o encoder!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
									break;
						}
					}
				}
				break;	
	}
	
//**********************����ֶ� ���� ��λ	
switch(ManualMoveMode)
	{
	case 0:
		if((StartCheck_mode<2)||(StartCheck_mode==4)||(StartCheck_mode==5))
			{
			
			if(GoFrontEn_flag==1)
				{
				if((Wheel_limit==0)&&(OutFront_limit==0))//����
					{
					if(GoFast_flag==1)
						MoveSpeed=1;    //����
					else
						MoveSpeed=3;	//  ����
					SetMotorSpeed(MoveSpeed);
					//--------
					MoveForward();//ǰ��
					ManualMoveMode++;
					}
				}
			else if(GoBackEn_flag==1)
				{
				if((Wheel_limit==0)&&(OutBack_limit==0))//����
					{
					if(GoFast_flag==1)
						MoveSpeed=1;    //����
					else
						MoveSpeed=3;	//  ����
					SetMotorSpeed(MoveSpeed);
					//--------
					MoveBack();//����
					ManualMoveMode=3;
					}
				}
			}
			break;
	case 1://ǰ��---------
		if(GoFrontEn_flag==0)	//jog �ͷ�
			{
			MoveSpeed=0;
			MoveStop();
			ManualMoveMode++;
			}
		else
			{
			if((Wheel_limit==1)||(OutFront_limit==1))// �����쳣
				{
				MoveSpeed=0;
				MoveStop();
				ManualMoveMode++;
				}
			}
			break;
	case 2:
			break;
	case 3:
		if(GoBackEn_flag==0)
			{
			MoveSpeed=0;
			MoveStop();
			ManualMoveMode++;
			}
		else
			{
			if((Wheel_limit==1)||(OutBack_limit==1))// �����쳣
				{
				MoveSpeed=0;
				MoveStop();
				ManualMoveMode++;
				}
			}
			break;
	case 4:
			break;		
	}

}

void NowSizeNum_dis(void)//***************************�ߴ� ��ʾ
{
Int32U size_temp,offset,curr_target;
//------------��ǰ--------------
if(CurrentSize_temp!=CurrentSize)
	{
	if(CurrentSize>TargetSize)
		{
		size_temp=CurrentSize-TargetSize;
		}
	else
		{
		size_temp=TargetSize-CurrentSize;
		}
		
	switch(MotorType)
		{
		case MOTOR_FREQ_5_SPD_RST:
		case MOTOR_FREQ_3_SPD:
		case MOTOR_FREQ_3_SPD_RST:
				if(size_temp>=VirtualTargetSizeGap)
					{
					CurrentSize_temp=CurrentSize;
			/*
					if(SelfLockEn_flag==1)  //���� ����-------------------
						{
						MoveSpeed=0;
						MoveSpeedCtrl();  //�����ٶȿ���
						Run_flag=1;
						RunStop_flag=0;
						InTargetPosit_flag=0;	//��Ŀ��λ��
						}
						*/
					CurrentSize_dis(CurrentSize_temp); //��ǰ�ߴ� ������ʾ
					}
				else 
					{
					if(CurrentSize_temp!=TargetSize)
						{
						CurrentSize_temp=TargetSize;
						CurrentSize_dis(CurrentSize_temp); //��ǰ�ߴ� ������ʾ
						if(MotorType==MOTOR_FREQ_3_SPD)		//20171017
							InTargetPosit_flag=1;	//Ŀ��λ��
						}
					}
					//---------------��������
				if(MotorType>MOTOR_FREQ_5_SPD_RST)
					{
					if(AirOffDistance>0)	//������������Ч
						{
						if(AirOffOK_flag==0)	//�����Ͽ� δ����
							{
							if(Forward_flag==1)	//��ǰ
								{
								if(size_temp<=AirOffDistance)
									{
									if(SelfLockEn_flag==0)
										{
										AirOffOK_flag=1;
										RLOUT3_ON;	//RLOUT2_ON;	//�����Ͽ�
										}
									}
								}
							}
						}
					}
				
				break;
		// // case MOTOR_DC_SERVO:
		// // case MOTOR_DC670_SERVO:
				// // if(DcServoGoTarget_flag==1)
					// // {
					// // if(size_temp>DC_VIRTURE_SIZE)
						// // {
						// // CurrentSize_temp=CurrentSize;
						// // CurrentSize_dis(CurrentSize_temp); //��ǰ�ߴ� ֱ����ʾ
						// // }
					// // else
						// // {
						// // if(ServoBack_flag==0)
							// // {
							// // if(CurrentSize_temp!=TargetSize)
								// // {
								// // CurrentSize_temp=TargetSize;
								// // CurrentSize_dis(CurrentSize_temp); //��ǰ�ߴ� ������ʾ
								// // }
							// // }
						// // else
							// // {
							// // CurrentSize_temp=CurrentSize;
							// // CurrentSize_dis(CurrentSize_temp); //��ǰ�ߴ� ֱ����ʾ
							// // }
						// // }
					// // }
				// // else   //ֱ����ʾ
					// // {
					// // CurrentSize_temp=CurrentSize;
					// // CurrentSize_dis(CurrentSize_temp); //��ǰ�ߴ� ֱ����ʾ
					// // }
				// // break;
		case MOTOR_AC_SERVO:
		case MOTOR_AC_SERVO_REV:
		case MOTOR_AC_A6_SERVO:
				CurrentSize_temp=CurrentSize;
				CurrentSize_dis(CurrentSize_temp); //��ǰ�ߴ� ֱ����ʾ
				
					//---------------��������
				if(AirOffDistance>0)	//������������Ч
					{
					if(AirOffOK_flag==0)	//�����Ͽ� δ����
						{
						if(qianjin==1)//��ǰ
							{
							if(size_temp<=AirOffDistance)
								{
								if(SelfLockEn_flag==0)
									{
									AirOffOK_flag=1;
									RLOUT3_ON;	//RLOUT2_ON;	//�����Ͽ�
									}
								}
							}
						}
					}
					
				break;
		}	
		
	
		
	}
//*****------��ǰ--------------
if(CurrentSize_temp<=BeforeKnife_offset)
	{//LED2_OFF;
	if(Unit==UNIT_MM)
		{
		size_temp=BeforeKnife_offset-CurrentSize_temp;
		}
	else	//inch
		{
		if(BeforeKnife_offset_in>0)
			{
			offset=BeforeKnife_offset_in;
			}
		else
			{
			offset=BeforeKnife_offset*100/254;
			}
		if(CurrentSize_temp==(Int32U)(TargetSize_inch*2.54))
			{
			curr_target=TargetSize_inch;
			}
		else
			{
			curr_target=CurrentSize_temp*100/254;
			}
		size_temp=offset-curr_target;
		}
		
	if(size_temp!=BeforeKnifeSize)
		{
		BeforeKnifeSize=size_temp;
		FrontKnifeSize_dis(BeforeKnifeSize);
		if(BeforeKnifeNo_flag==1)  //��ǰ ��ʾ
			{
			BeforeKnifeNo_flag=0;
			}
		}
	}
else
	{//LED2_ON;
	if(BeforeKnifeNo_flag==0)  //��ǰ ��ʾ ȥ��
		{														//testing---------------------
		BeforeKnifeSize=0xffffffff;
		FrontKnifeSize_NOdis();
		BeforeKnifeNo_flag=1;
		}
	}	
}

Int8U PressStop_check(void)//ѹֽͣ��  �ж�
{
Int8U flag;
if(PressValid_flag==0) //ѹֽ ��Ч
	flag=0;
else
	{
	if((AllPressUp_flag==1)&&(AllKnifeUp_flag==1))
		flag=0;
	else 
		{
		if(AllPressUp_flag==0)
			flag=1;   //ѹֽ����
		else
			flag=2;  //���źŹ���
		}
		
	}
if(flag!=0)
	{
	PromptDis_flag=0;
	GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
		if(flag==1)
			{
			switch(Language)
				{
				case CHN_HAN:
						Printf24("ѹֽ������ߵ�!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
						break;
				case ENGLISH:
						Printf16("Press-Paper isn't in highest!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
						break;
				case INDONSIA:	//ӡ��
						Printf16("Pelat bukanlah titik tertinggi!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
						break;
				case PORTUGAL:	//������
						Printf16("Platen n?o ��o ponto o mais alto!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
						ASCII_Printf("a",ASCII16_MODE,8,16,PUTAO_ZK16,REMIND_WINDOW_X+8*8,REMIND_WINDOW_Y+5,RED_COLOR, 0xffff);
						break;
				}
			}
		else
			{
			switch(Language)
				{
				case CHN_HAN:
						Printf24("���źŹ���!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
						break;
				case ENGLISH:
						Printf24("Knife signal error!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
						break;
				case INDONSIA:	//ӡ��
						Printf24("Kegagalan sinyal Knife!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
						break;
				case PORTUGAL:	//������
						Printf24("Falha de sinal Lamina!",REMIND_WINDOW_X,REMIND_WINDOW_Y+5,RED_COLOR,1,0xffff);
						ASCII_Printf("a",ASCII24_MODE,12,24,PUTAO_ZK24_XOR,REMIND_WINDOW_X+12*16,REMIND_WINDOW_Y+5,RED_COLOR, 0xffff);
						break;
				}
			}
	PressStopDis_flag=1;
	}
return flag;	
}


void ServoWorkStart_check(void)  //ֱ���ŷ�  ����ģʽǰ  ׼��
{
	//ServoDrvInitOK_flag=1;StartCheck_mode=4;
if(ServoDrvInitOK_flag==0)
	{
	ServoDrvSet_Init();//������ ��ʼ��
	StartCheck_mode=0;
	RunDisplay_flag=0;
	BackLimitError_flag=0;
	//--------
	/***
	if(KeyLinkDis_flag==0)
		{
		KeyLinkDis_flag=1;
		GLCD_SetWindow_Fill(KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y,KEYBOARD_CHECK_X+START_PROM_WIDE-1, KEYBOARD_CHECK_Y+START_PROM_HIGH-1, 0xfffff, 0xffff);
		if(KeyboardLink_flag==0) //
			{
			switch(Language)
				{
				case CHN_HAN:
						Printf24("����δ����!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case ENGLISH:
						Printf24("Keyboard is off!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case INDONSIA:	//ӡ��
						Printf24("Keyboard tidak terhubung!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case PORTUGAL:	//������
						Printf24("O teclado n?o est�� conectado!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						ASCII_Printf("a",ASCII24_MODE,12,24,PUTAO_ZK24, KEYBOARD_CHECK_X+(11*12),KEYBOARD_CHECK_Y+5,RED_COLOR,0xffff);
						break;
				}
			}
		else
			{
			switch(Language)
				{
				case CHN_HAN:
						Printf24("������������!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case ENGLISH:
						Printf24("Keyboard is OK!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case INDONSIA:	//ӡ��
						Printf24("Keyboard dihubungkan!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				case PORTUGAL:	//������
						Printf24("Teclado conectado corretamente!",KEYBOARD_CHECK_X,KEYBOARD_CHECK_Y+5,RED_COLOR,1,0xffff);
						break;
				}
			}
		}
		**/
	}
else
	{
	if(StartCheck_mode!=3)
		OutLimit_check(); //�ⲿ��λ
	switch(StartCheck_mode)
		{
		case 0:
			if(OutBack_limit==1)
				{
				if(BackLimitError_flag==0)
					{
					GLCD_SetWindow_Fill(START_PROMPT_X1, START_PROMPT_Y1, START_PROMPT_X1+START_PROM_WIDE-1, START_PROMPT_Y1+START_PROM_HIGH-1, 0xfffff, 0xffff);//��ʾ
					switch(Language)
						{
						case CHN_HAN:
								Printf24("����λ�Ͽ�!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
								break;
						case ENGLISH:
								Printf24("Back-Limit is off!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
								break;
						case INDONSIA:	//ӡ��	
								Printf24("Setelah melepaskan batas!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
								break;
						case PORTUGAL:	//������
								Printf24("Desligue o limite traseiro!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
								break;
						}
					BackLimitError_flag=1;
					}
				if(RunDisplay_flag==1)
					{
					RunDisplay_flag=0;
					if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(Wheel_limit==0))  //������������
						CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2,    START_PROM_WIDE, START_PROM_HIGH);
					}
				}
			else
				{
				if(BackLimitError_flag==1)
					{
					BackLimitError_flag=0;
					CurrentArea_recover1(START_PROMPT_X1, START_PROMPT_Y1,    START_PROM_WIDE, START_PROM_HIGH);
					}
				}
				
			if((OutFront_limit==1)||(OutMiddle_limit==1)||(Wheel_limit==1)||(OutBack_limit==1))  //�����쳣
				{
				RunDisplay_flag=0;
				}
			else
				{
				if(RunDisplay_flag==0)
					{
					RunDisplay_flag=1;
					GLCD_SetWindow_Fill( START_PROMPT_X2, START_PROMPT_Y2, START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//��ʾ��
					switch(Language)
						{
						case CHN_HAN:
								Printf24("���Լ�����,�밴���м�!>��˴�",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
									break;
						case ENGLISH:
								Printf24("Computer testing OK, press the RUN key!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
									break;
						case INDONSIA:	//ӡ��
								Printf24("Tes komputer lengkap, tekan tombol Run!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
									break;
						case PORTUGAL:	//������
								Printf16("Computador auto-teste estiver conclu��",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								Printf16("                                     do, pressione o bot o de execu  o!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,0,0xffff);
								ASCII_Printf("a",ASCII16_MODE,8,16,PUTAO_ZK16, START_PROMPT_X2+(56*8),START_PROMPT_Y2+5,RED_COLOR,0xffff);
								ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, START_PROMPT_X2+(67*8),START_PROMPT_Y2+5,RED_COLOR,0xffff);
								break;
						}
					StartCheck_mode++;	
					orig_wait_time=0;
					}
				}
					break;
		case 1:   //��������  ��ȴ����м�    ����
			if((OutFront_limit==1)||(OutMiddle_limit==1)||(Wheel_limit==1)||(OutBack_limit==1))  //�����쳣
				StartCheck_mode--;
					break;
		case 2: //��ʱ 
			orig_wait_time++;
			if(orig_wait_time>=300)
				{
				StartCheck_mode++;
				}
					break;
			
		case 3:			//��ԭ��	������
			if(SearchZero_flag==1)   //�Ѿ�  ��ԭ��	
				{
				orig_wait_time=0;
				StartCheck_mode++;
				}
			else
				{
				//if((OutFront_limit==1)||(OutMiddle_limit==1)||(Wheel_limit==1)||(OutBack_limit==1))  //�����쳣
				//	{
				//	StartCheck_mode=0;
				//	}
				}	
					break;
		case 4://�ȴ�һ�� ���뿪��
			orig_wait_time++;
			if(orig_wait_time>=500)
				{
				WorkStart_flag=1;
				WorkMode=AUTO_MODE;//���� ��������
				PaperCutEnb_signal=1;
				// TableDis_startcol=RIGHT_ARROW_X; //������ʾ��ʼ��
				Knife_order=1;cursor_row=0;     // ������ ��ʾ ��ͷ
				ProcessRatio=0xff;
				WorkPic_dis();  //���� ��������
				PromptDis_flag=1;
				Size_1page_dis(Knife_order, 0);
				CursorKnife_dis(0,1);//��ɫ���
				
				}
					break;
					
		}
	}
	//------jog-------����ֶ� ���� ��λ	
switch(ManualMoveMode)
	{
	case 0:
		if(StartCheck_mode<2)
			{
			if(GoFrontEn_flag==1)
				{
				if(OutFront_limit==0)//����
					{
					if(ServoMoving_flag==0)
						{
						DCServoMove_To(Size_MIN,JOG_MOVE);//--------//ǰ��
						ManualMoveMode++;
						}
					}
				}
			else if(GoBackEn_flag==1)
				{
				if(OutBack_limit==0)//����
					{
					if(ServoMoving_flag==0)
						{
						DCServoMove_To(Size_MAX,JOG_MOVE);//--------//����
						ManualMoveMode=4;
						}
					}
				}
			}
			break;
	case 1://ǰ��---------
		if(GoFrontEn_flag==0)	//jog �ͷ�
			{
			DCServoStop();  //ֹͣ����
			ServoStopTime=0;
			ManualMoveMode++;
}
		
			break;
	case 2: //ǰ�� ֹͣ��------
		if(ServoMoving_flag==1)
			{
			ServoStopTime++;
			if(ServoStopTime>=1400)
				{
				DCServoStop();  //ֹͣ����
				ServoStopTime=0;
				}
			}
		else
			{
			ManualMoveMode++;
			}
			break;
	case 3:
			break;
	case 4:	//����--
		if(GoBackEn_flag==0)
			{
			DCServoStop();  //ֹͣ����
			ServoStopTime=0;
			ManualMoveMode++;
			}
		
			break;
	case 5://����--ֹͣ��------
		if(ServoMoving_flag==1)
			{
			ServoStopTime++;
			if(ServoStopTime>=1400)
				{
				DCServoStop();  //ֹͣ����
				ServoStopTime=0;
				}
			}
		else
			{
			ManualMoveMode++;
			}
			break;
	case 6:
			break;		
	}
}


void BellTwice_exec(void)  //����  ����
{
if(TargetBell_flag==1)
	{
	switch(TargetBell_mode)
		{
		case 0:
			BellOUT_ON;
			TargetBell_time=0;
			TargetBell_mode++;
				break;
		case 1:
			TargetBell_time++;
			if(TargetBell_time>=on_gap)
				{
				TargetBell_time=0;
				BellOUT_OFF;
				TargetBell_mode++;
				}
				break;
		case 2:
			TargetBell_time++;
			if(TargetBell_time>=off_gap)
				{
				TargetBell_time=0;
				BellOUT_ON;
				TargetBell_mode++;
				}
				break;
		case 3:
			TargetBell_time++;
			if(TargetBell_time>=on_gap)
				{
				TargetBell_time=0;
				BellOUT_OFF;
				TargetBell_flag=0;
				}
				break;		
		}
	}
}
 
void ACServoWorkStart_check(void)  //�����ŷ�  ����ģʽǰ  ׼��
{
Int32U i;
if(StartCheck_mode<11)	//6
	OutLimit_check(); //�ⲿ��λ
if(OIN1_PIN!=0)   //ԭ��    1
	{  
	senor=1;
	}
else   //ԭ��   0
	{
	senor=0;
	} 
switch(StartCheck_mode)
	{
	case 0:
		stop_time=0;
			if(senor==1)    //1   ԭ������
				{
				if(OriginalError_flag==1)
					{
					CurrentArea_recover1(START_PROMPT_X1, START_PROMPT_Y1,    START_PROM_WIDE, START_PROM_HIGH);
					OriginalError_flag=0;//ԭ�����  ���
					BackLimitError_flag=0;
					RunDisplay_flag=0;         //��������  �������м�/////////////////
					PushRstKey_flag=0; 
					}
				if(OutBack_limit==1)//����λ�Ͽ�
					{
					if(BackLimitError_flag==0)
						{
						GLCD_SetWindow_Fill(START_PROMPT_X1, START_PROMPT_Y1, START_PROMPT_X1+START_PROM_WIDE-1, START_PROMPT_Y1+START_PROM_HIGH-1, 0xfffff, 0xffff);//��ʾ
						switch(Language)
							{
							case CHN_HAN:
									Printf24("����λ�Ͽ�!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case ENGLISH:
									Printf24("Back-Limit is off!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case INDONSIA:	//ӡ��
									Printf24("Setelah melepaskan batas!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case PORTUGAL:	//������
									Printf24("Desligue o limite traseiro!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							}
						BackLimitError_flag=1;
						}
					if(OutFront_limit==0)
						{
						StartCheck_mode=3;
						RunDisplay_flag=0;         //ǰ��������  �������м�/////////////////
						PushRstKey_flag=0; 
						}
					}
				else  //2   ��������
					{
					// if((BackLimitError_flag|OriginalError_flag)==1)
					if(BackLimitError_flag==1)
						CurrentArea_recover1(START_PROMPT_X1, START_PROMPT_Y1,    START_PROM_WIDE, START_PROM_HIGH);
					BackLimitError_flag=0;//���޹���  ���
					OriginalError_flag=0;//ԭ�����  ���
					StartCheck_mode=3;    
					// StartCheck_mode++;    
					RunDisplay_flag=0;         //��������  �������м�/////////////////
					PushRstKey_flag=0; 
					}
				FrontLimitDis_flag=0;
				}
			else     //ԭ�����
				{
				if(OriginalError_flag==0)
						{
						GLCD_SetWindow_Fill(START_PROMPT_X1, START_PROMPT_Y1,   START_PROMPT_X1+START_PROM_WIDE-1, START_PROMPT_Y1+START_PROM_HIGH-1, 0xfffff, 0xffff);//��ʾ
						switch(Language)
							{
							case CHN_HAN:
									Printf24("ԭ�����!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case ENGLISH:
									Printf24("Original fault!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case INDONSIA:	//ӡ��
									Printf24("Asal kesalahan!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									break;
							case PORTUGAL:	//������
									Printf24("come ando falha!",START_PROMPT_X1,START_PROMPT_Y1+5,RED_COLOR,1,0xffff);
									ASCII_Printf("c",ASCII24_MODE,12,24,PUTAO_ZK24, START_PROMPT_X1+(4*12),START_PROMPT_Y1+5,RED_COLOR,0xffff);
									break;
							}	
						OriginalError_flag=1;
						}
				BackLimitError_flag=0;//���޹���  ���	
				// PushResetPrompt_dis();  //���� ��ֽ�� ��λ  ��ʾ
				// StartCheck_mode++;
				// PushRstKey_flag=0;
				if(RunDisplay_flag==1)	
					{
					CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2,    START_PROM_WIDE, START_PROM_HIGH);
					RunDisplay_flag=0;
					}
				}	
			break;
	case 1:	//�ȴ� ��ֽ��  ��λ������ȷ������
			if(senor==1) //ԭ�� ���� ��λ����
				{			//��λ ��ʾ  ��ʧ
				CurrentArea_recover3(PUSH_RESET_PROMPT_X1, PUSH_RESET_PROMPT_Y1, PUSH_RESET_PROMPT_WIDE, PUSH_RESET_PROMPT_HIGH);
				StartCheck_mode=0;//3;    
				RunDisplay_flag=0;         //��������  �������м�////////////////////
				PushRstKey_flag=0;
				}
			else
				{
				
				}
				break;
	case 2:		// ��ֽ��  ��λ��
			if(qianjincn>=20000) //8s
				{
				ACServoStop();
				StartCheck_mode++;
				RunDisplay_flag=0;//��������  �������м�////////////////////
				if((OutBack_limit==0)&&(senor==1)) //ԭ�� ���� ��λ����
					{
					CurrentArea_recover1(START_PROMPT_X1, START_PROMPT_Y1,    START_PROM_WIDE, START_PROM_HIGH);
					OriginalError_flag=0;//ԭ�����  ���
					}
				else
					{
					StartCheck_mode=0; //δ��λ �����¼��
					PushRstKey_flag=0;
					}
				}
			break;
	case 3:	//--------------case 1:
			if(OutBack_limit==0)
				{
				if(OutMiddle_limit==0)   //
					{
					if(senor==1)   //�ź�  ����   ��ʾ����
						{
						if(OutBack_limit==0)
							{
							if(PushRstKey_flag==0)
								{
								if(RunDisplay_flag==0)
									{
									RunDisplay_flag=1;
									GLCD_SetWindow_Fill( START_PROMPT_X2, START_PROMPT_Y2, START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//��ʾ��
									switch(Language)
										{
										case CHN_HAN:
												Printf24("���Լ�����,�밴���м�!>��˴�",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
													break;
										case ENGLISH:
												Printf24("Computer testing OK, press the RUN key!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
													break;
										case INDONSIA:	//ӡ��
												Printf24("Tes komputer lengkap, tekan tombol Run!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
													break;
										case PORTUGAL:	//������
												Printf16("Computador auto-teste estiver conclu��",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
												Printf16("                                     do, pressione o bot o de execu  o!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,0,0xffff);
												ASCII_Printf("a",ASCII16_MODE,8,16,PUTAO_ZK16, START_PROMPT_X2+(56*8),START_PROMPT_Y2+5,RED_COLOR,0xffff);
												ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, START_PROMPT_X2+(67*8),START_PROMPT_Y2+5,RED_COLOR,0xffff);
													break;
										}
									StartCheck_mode++;
									}
								}
							else  //-------------��ֽ���Զ���λ��
								{
								if(PassCodeEn_flag==0)
									{
									ACServoMoveBack_MID_SPD();  //�����ŷ�  ���ٺ���
									//CurrentArea_recover2(REMIND_WINDOW_X, REMIND_WINDOW_Y, START_PROM_WIDE, START_PROM_HIGH);
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
									StartCheck_mode=9;//5;
									}
								else   //-------------����  ������ʾ
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
									StartCheck_mode++;
									}
								}
							}
						else
							StartCheck_mode=0;
						//---------20150629
						if(OriginalError_flag==1)
							{
							CurrentArea_recover1(START_PROMPT_X1, START_PROMPT_Y1,    START_PROM_WIDE, START_PROM_HIGH);
							OriginalError_flag=0;//ԭ�����  ���
							}
						}
					else
						{
						// StartCheck_mode=0;
						}	
					}
				else
					StartCheck_mode=0;
				}
			else	//�����쳣
				{
				if(OutFront_limit==0)//ǰ����ok
					{
					StartCheck_mode	=5;
					}
				else
					{
					StartCheck_mode	=0;
					GLCD_SetWindow_Fill(START_PROMPT_X2 , START_PROMPT_Y2,START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//��ʾ
					switch(Language)
						{
						case CHN_HAN:
							Printf24("ǰ��λ�Ͽ�!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case ENGLISH:
							Printf24("Front-Limit is off!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case INDONSIA:	//ӡ��
							Printf24("Lepaskan batas depan!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case PORTUGAL:	//������
							Printf24("A primeira parada ��desconectada",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						}	
					}
				}
			break;
	case 4://2�ȴ�   ���м�����   ��--------------------------------------------------����ok ����
			if(OutBack_limit==1)// if((OutFront_limit==1)||(OutMiddle_limit==1)||(Wheel_limit==1)||(OutBack_limit==1)||(senor==0))
				{                //�������쳣
				RunDisplay_flag=0;//���������ʾ
				if(senor==0)//if((OutBack_limit==1)||(senor==0))
					{
					if((OutFront_limit==0)&&(OutMiddle_limit==0))
						{
						CurrentArea_recover2(START_PROMPT_X2, START_PROMPT_Y2,    START_PROM_WIDE, START_PROM_HIGH);	
						}
					}
				StartCheck_mode=0;
				}
				
			if(OutFront_limit==1)//ǰ�����쳣
				{
				if(FrontLimitDis_flag==0)
					{
					FrontLimitDis_flag=1;
					GLCD_SetWindow_Fill(START_PROMPT_X2 , START_PROMPT_Y2,START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//��ʾ
					switch(Language)
						{
						case CHN_HAN:
							Printf24("ǰ��λ�Ͽ�!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case ENGLISH:
							Printf24("Front-Limit is off!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case INDONSIA:	//ӡ��
							Printf24("Lepaskan batas depan!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						case PORTUGAL:	//������
							Printf24("A primeira parada ��desconectada",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								break;
						}	
					}
				}
			else//
				{
				if(FrontLimitDis_flag==1)	
					{
					FrontLimitDis_flag=0;
					StartCheck_mode=0;
					}
				}
			break;	
	case 5://�ȴ�   ���м�����   ��-------------------------only�����쳣����	
			if(OutFront_limit==1)//ǰ�����쳣
				{
				StartCheck_mode	=0;
				GLCD_SetWindow_Fill(START_PROMPT_X2 , START_PROMPT_Y2,START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//��ʾ
				switch(Language)
					{
					case CHN_HAN:
						Printf24("ǰ��λ�Ͽ�!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
							break;
					case ENGLISH:
						Printf24("Front-Limit is off!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
							break;
					case INDONSIA:	//ӡ��
						Printf24("Lepaskan batas depan!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
							break;
					case PORTUGAL:	//������
						Printf24("A primeira parada ��desconectada",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
							break;
					}
				}
			else		//ǰ����---ok �ָ�
				{
				if(RunDisplay_flag==0)
					{
					RunDisplay_flag=1;
					GLCD_SetWindow_Fill( START_PROMPT_X2, START_PROMPT_Y2, START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//��ʾ��
					switch(Language)
						{
						case CHN_HAN:
								Printf24("���Լ�����,�밴���м�!>��˴�",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
									break;
						case ENGLISH:
								Printf24("Computer testing OK, press the RUN key!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
									break;
						case INDONSIA:	//ӡ��
								Printf24("Tes komputer lengkap, tekan tombol Run!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
									break;
						case PORTUGAL:	//������
								Printf16("Computador auto-teste estiver conclu��",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								Printf16("                                     do, pressione o bot o de execu  o!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,0,0xffff);
								ASCII_Printf("a",ASCII16_MODE,8,16,PUTAO_ZK16, START_PROMPT_X2+(56*8),START_PROMPT_Y2+5,RED_COLOR,0xffff);
								ASCII_Printf("ca",ASCII16_MODE,8,16,PUTAO_ZK16, START_PROMPT_X2+(67*8),START_PROMPT_Y2+5,RED_COLOR,0xffff);
								break;
						}
					}
				if(OutBack_limit==0)
					{
					StartCheck_mode--;//ǰ�����޶�����
					}
				}
			
			break;
	case 6:  //ǰ��   ��-----�����쳣 ����			
			if(OutFront_limit==1)//ǰ����
				{
				ACServoStop();
				StartCheck_mode=0;
				}
			else
				{
				stop_time=0;
				StartCheck_mode++;
				}
				break;
	case 7:			
			if(OutFront_limit==1)//ǰ����
				{
				ACServoStop();
				StartCheck_mode=0;
				}
			else
				{
				stop_time++;
				if(stop_time>=6000)
					{
					stop_time=0;
					ACServoStop();
					if(OutBack_limit==0)
						StartCheck_mode++;
					else
						StartCheck_mode=0;
					}
				}
				break;
	case 8:			//ǰ��һ�ξ��룬 ����	�ָ�������----------	��ʼ  ����������������
			stop_time++;
			if(stop_time>=1000)
				{
				stop_time=0;
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
					ACServoMoveBack_MID_SPD();  //�����ŷ�  ���ٺ���>>>>
					StartCheck_mode++;	
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
				break;
		//--------------------------//////////////////////////0000000000000000000000000000000000000000000///////////////////////////
	case 9://5-----���м�����   ��          -----����ok ����
			if(OutBack_limit==0)  //if((OutFront_limit==0)&&(OutMiddle_limit==0))
				{
				if(senor==0&&status==2)
					{
					ACServoMoveBack_LOW_SPD();  //�����ŷ�  ���ٺ���
					StartCheck_mode++;
					}
				}
			else   //�����쳣
				{
				if(stop_time<2000)
					{
					stop_time++;
					if(senor==0&&status==2)		//ԭ��Ҳ�� ----- �� ����
						{
						ACServoMoveBack_LOW_SPD();  //�����ŷ�  ���ٺ���
						StartCheck_mode++;
						}
					}
				else	//��ʱ  error
					{
					ACServoStop(); 
					StartCheck_mode=0;	
					}
				}
			break;
	case 10://6://-----	 ���ٺ���
			if(OutBack_limit==0)  //if((OutFront_limit==0)&&(OutMiddle_limit==0))
				{
				if(senor==0&&status==8)   //ǰ��
					{
					i=8000000;
					while(i--);
					flagqyx=0;  
					qianjin=1;  
					houtui=0; 
					
					step_add=20;
					 Timer1Init();
				   Timer0Disable(); 
					status=10;   
					
					StartCheck_mode+=2;
					}  
				}
			else   //�����쳣
				{
				stop_time=0;
				StartCheck_mode++;
				}	
			break;
	case 11:	//----delay---- ���� ����λ&ԭ�� �ж�-----------------20160123
			if(stop_time<2000)
				{
				stop_time++;
				if(senor==0&&status==8)   //ǰ��
					{
					i=8000000;
					while(i--);
					flagqyx=0;  
					qianjin=1;  
					houtui=0; 
					
					step_add=20;
					 Timer1Init();
				   Timer0Disable(); 
					status=10;   
					
					StartCheck_mode++;
					}  
				}
			else//����ʱ���   
				{
				// if(OutBack_limit==1)// ��Ȼ�쳣
					// {
					stop_time=0;
					ACServoStop(); 
					StartCheck_mode=0;   //ֹͣ
					// }
				}
			
			break;
	case 12://7:  //ǰ��------��� z  �ź�   ֹͣ
			// if((OutFront_limit==0)&&(OutMiddle_limit==0)&&(OutBack_limit==0))
			if((OutFront_limit==0)&&(OutMiddle_limit==0))
				{
					if(senor==1&&status==10)
						{
						//if(Z_PulseIN==0) //z  �ź�   ֹͣ
						while(M_ZIN_PIN!=0); //z  �ź�   ֹͣ
						//	{
							 Timer1Disable();
							 status=12;
							 poweon_flag=0;
							chushihua=1;
							qianjincn=0;
							 houtuicn=0; 
							 flagtingji8=1; 
							houtui=0;
							qianjin=1;
						//--------------------------------------------
							Timer0Init();
							StartCheck_mode++;
							stop_time=0;
						//	}
						}
					
				}
			else   //�����쳣
				{
				ACServoStop(); 
				StartCheck_mode=0;
				}	
			break;
	case 13://8:
			stop_time++;
			if(stop_time>=100)
				{
				stop_time=100;
				if(MotorType==MOTOR_AC_A6_SERVO)	//A6 ----mode
					{
					if(ModBus_CodeDataMode==0x11)//��ȡ���
						{
						A6_CalCurSize();
						CurrentSize=CurrentSize_A6Coder;
						StartInitSize=CurrentSize;	//������ʼ�ߴ�
						StartCheck_mode++;
						}
					}
                else   
					{
					CurrentSize=OriginalSize;	
					StartCheck_mode++;
					}
				}
			break;	
	case 14://
                    WorkStart_flag=1;
					WorkMode=AUTO_MODE;//���� ��������
					PaperCutEnb_signal=1;
					// TableDis_startcol=RIGHT_ARROW_X; //������ʾ��ʼ��
					Knife_order=1;cursor_row=0;     // ������ ��ʾ ��ͷ
					ProcessRatio=0xff;
					WorkPic_dis();  //���� ��������
					PromptDis_flag=1;
					Size_1page_dis(Knife_order, 0);
					CursorKnife_dis(0,1);//��ɫ���
					CurrentSize=OriginalSize;
					
			break;	
	}
	
	//**********************����ֶ� ���� ��λ	
switch(ManualMoveMode)
	{
	case 0:
		if(StartCheck_mode<=2)
			{
			if(GoFrontEn_flag==1)
				{
				// if((OutMiddle_limit==0)&&(OutFront_limit==0))//ǰ���� ��������
				if(OutFront_limit==0)//ǰ ��������
					{
					ACMotorGoForward();//ǰ��
					//--------
					ManualMoveMode++;
					}
				}
			else if(GoBackEn_flag==1)
				{
				if(OutBack_limit==0)//����
					{
					ACMotorGoBack();  //����
					//--------
					ManualMoveMode=3;
					}
				}
			}
			break;
	case 1://ǰ��---------
		if(GoFrontEn_flag==0)	//jog �ͷ�
			{
			ACServoStop();  //�����ŷ�	ֹͣ
			ManualMoveMode++;
			}
		else
			{
			// if((OutMiddle_limit==1)||(OutFront_limit==1))// ǰ���� �����쳣
			if(OutFront_limit==1)// ǰ �����쳣
				{
				ACServoStop();  //�����ŷ�	ֹͣ
				ManualMoveMode++;
				}
			}
			break;
	case 2:
			break;
	case 3:
		if(GoBackEn_flag==0)
			{
			ACServoStop();  //�����ŷ�	ֹͣ
			ManualMoveMode++;
			}
		else
			{
			if(OutBack_limit==1)// �����쳣
				{
				ACServoStop();  //�����ŷ�	ֹͣ
				ManualMoveMode++;
				}
			}
			break;
	case 4:
			break;		
	}
}

void ACMotorGetCurrentSize(void)  // �����ŷ�   �ߴ����
{
if(MotorType<MOTOR_AC_A6_SERVO)
	{
	if(qianjincn>houtuicn)
		{  
		CurrentSize=OriginalSize-((qianjincn-houtuicn)/2);
		} 
	else
		{  
		CurrentSize=OriginalSize+((houtuicn-qianjincn)/2);
		} 
	}
else
	{
	if(A6CoderCorrectRun_flag==0)
		{
		if(qianjincn>houtuicn)
			{  
			CurrentSize=StartInitSize-((qianjincn-houtuicn)/2);//OriginalSize
			} 
		else
			{  
			CurrentSize=StartInitSize+((houtuicn-qianjincn)/2);
			} 	
		}
	else
		{
		CurrentSize=TargetSize;
		}
	}
	
if(flagtingji8==1)
	{
	if(qianjincn>houtuicn)
		{
		qianjincn=qianjincn-houtuicn;
		houtuicn=0;
		yushu=qianjincn%2;
		}
	else
		{
		houtuicn=houtuicn-qianjincn;
		qianjincn=0;
		yushu=houtuicn%2;
		}
		
	}	
}

void ACMotorRunning_ctrl(void)//�����ŷ�����  ����
{
Int32U i;
if(houtui==1&&flagtingji8==1&&flagyd==0)
    {   
	 i=400000;
	 while(i--);
	 
	   houtui=0;
	   qianjin=1; 
	   flagqyx=0;
	   flagtingji8=0;
	   flagyunxing8=1;
	   
	   rollsteps=2400;
	   step_ground=11; 
  
	  speedup_steps=30;
	   speedup_steps_B=speedup_steps;
	   rollsteps=(rollsteps- speedup_steps*22)+2;
	   status=1;           

	step_add=1; 
	Timer1Init();
	Timer0Disable();
           
    }
   /////////////////////////////////////////////////////////////////// 
if(flagtingji8==1&&qianjin==1&&t0zhongduan==0)
    {  
         Timer0Init();
         t0zhongduan=1;
          /*
		if(flagbeep==1&&qianjin==1)
			{
			  flagbeep=0;
			   BellOUT_ON;
			  flagbeep1=1;	  
			}  
			*/
		
	if(OIN2_PIN)   //�����һ·��ź����Ϊ��?
        {
        if(!OIN3_PIN)   //�����һ·��ź����Ϊ��?
            {     
             flagshoulun=0;
            }
             
        }		
         
    RunStop_flag=1;
	stop_time=0;
	Run_flag=0;	
	A6CoderCorrectMode=0;//�����ߴ�
    }
}

void AC_MotorRuningLimit_ctrl(void)  //������  ���ⲿ�ź� ֹͣ
{
if(houtui==1)   //--------------����
	{
	if(OutBack_limit==1)  //����λ  ֹͣ
		{
		ACServoStop();  //�����ŷ�	ֹͣ
		Run_flag=0;
		InTargetPosit_flag=0;	//Ŀ��λ��
		TargetSize=0;
		BeforeKnife_offset_in=0;
		AutoPushRun_flag=0;
		}
		/*****----------------------------
	else
		{
		if(CurrentSize>=Size_MAX&&flagqyx==2)
			{
			ACServoStop();  //�����ŷ�	ֹͣ
			Run_flag=0;
			InTargetPosit_flag=0;	//
			TargetSize=0;
			BeforeKnife_offset_in=0;
			AutoPushRun_flag=0;
			}
		}
		-----------------------------****/
	}
else
	{
	if(qianjin==1)  //-------------ǰ��  
		{
		if(PressStop_check()==0)
			{
			if(OutFront_limit==1)//��ǰ��λ    ֹͣ----------------------
				{
				ACServoStop();  //�����ŷ�	ֹͣ
				Run_flag=0;
				InTargetPosit_flag=0;	//
				TargetSize=0;
				BeforeKnife_offset_in=0;
				AutoPushRun_flag=0;
				}
			else
				{
				if(OutMiddle_limit==1)  //�� ��λ
					{
					if(Hold_Up_flag==1)  //�а�  ��  ֹͣ-----------------------
						{
						ACServoStop();  //�����ŷ�	ֹͣ
						Run_flag=0;
						InTargetPosit_flag=0;	//
						TargetSize=0;
						BeforeKnife_offset_in=0;
						AutoPushRun_flag=0;
						}
					}
				else
					{
					if(CurrentSize<(Size_MIN+4000)&&CurrentSize>Size_MIN)
						{
						if(LowerAC_SPD_flag==0)
							{
							AC_ChangeSPD();  //�ٶȸı�
							LowerAC_SPD_flag=1;
							}
						}
					else
						{
						if(CurrentSize<(Size_MIN+1)&&flagqyx==1)  //����  ����--------------------
							{
							ACServoStop();  //�����ŷ�	ֹͣ
							Run_flag=0;
							InTargetPosit_flag=0;	//
							TargetSize=0;
							BeforeKnife_offset_in=0;
							AutoPushRun_flag=0;
							}
						}

					}
				}
			}
		else   //ѹֽ  ͣ��
			{
			ACServoStop();  //�����ŷ�	ֹͣ
			Run_flag=0;
			InTargetPosit_flag=0;	//
			TargetSize=0;
			BeforeKnife_offset_in=0;
			AutoPushRun_flag=0;
			}
		}
	}
}


void ACMotor_GetZpulse(void)
{
if(MotorType>=MOTOR_AC_SERVO)
	{
	if(WorkStart_flag==0)
		{
		if(Board_TestMod==0)//
			{
			if(StartCheck_mode==5)
				{
				Ms_Flag=1;
				if(M_ZIN_PIN==0) //z  �ź�
					Z_PulseIN=0;
				else
					Z_PulseIN=1;
				}
			}
		}
	}
}
 
 
void ACServoAlarm_exec(void)  //�����ŷ�  ����  ����
{
pInt8U Err_XXX="XXXXXXX";
Int8U ErrCode[10]=0;
if(Board_TestMod==0)//�ǹ��ܲ���ģʽ
	{
	if(ACServoDrvErr_flag==0)
		{
		if(OIN9_PIN!=0)
			{
			ModBus_AcErr_Type=AC_ERR_Z;
			ACServoDrvErr_flag=1;
			ACServoAlarmExec_flag=0;
			}
		else
			{//ͨѶ�� ������err code
			if(ModBus_ACErr!=0)
				{
				ModBus_AcErr_Type=AC_ERR_CODE;
				ModBus_AcErr_HisData[0]=ModBus_ACErr;
				// Modbus_A6_SaveErrData();	//����������	-------20171124 ȥ��
				ACServoAlarmExec_flag=0;
				ACServoDrvErr_flag=1;
				}
			if(ModBus_Comm_LinkErr==1)
				{
				ModBus_AcErr_Type=AC_ERR_LINK;
				ACServoDrvErr_flag=1;
				ACServoAlarmExec_flag=0;
				}
			}	
		}	
	else
		{        //����  ����
		if(ACServoAlarmExec_flag==0)
			{
			if(WorkStart_flag==0)  
				{
				GLCD_SetWindow_Fill( START_PROMPT_X2, START_PROMPT_Y2, START_PROMPT_X2-1+START_PROM_WIDE, START_PROMPT_Y2-1+30, 0xfffff, 0xffff);//��ʾ��
				switch(ModBus_AcErr_Type)
					{
					case AC_ERR_Z:	//Z_Pulse����
							switch(Language)
								{
								case CHN_HAN:
									Printf24("�����ŷ�����������Z!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
											break;
								case ENGLISH:
								case INDONSIA:	//ӡ��
									Printf24("AC servo drive alarm!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
											break;
								case PORTUGAL:	//������
									Printf24("Alarme Servo drive!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
											break;
								}
								break;
					case AC_ERR_CODE://������err code
								ErrCode[0]='E';
								ErrCode[1]='r';
								ErrCode[2]='r';
								ErrCode[3]=':';
								ErrCode[4]=(ModBus_ACErr>>8)/10+0x30;
								ErrCode[5]=(ModBus_ACErr>>8)%10+0x30;
								ErrCode[6]='.';
								ErrCode[7]=(unsigned char)ModBus_ACErr/10+0x30;
								ErrCode[8]=(unsigned char)ModBus_ACErr%10+0x30;
								ErrCode[9]=0;
								Printf24("Drv alarm",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
								Printf24(ErrCode,START_PROMPT_X2+10*24,START_PROMPT_Y2+5,RED_COLOR,0,0xffff);
								break;
					case AC_ERR_LINK://ͨѶ����
							switch(Language)
								{
								case CHN_HAN:
									Printf24("������ͨѶ����!������",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
											break;
								case ENGLISH:	
								case INDONSIA:	//ӡ��	
								case PORTUGAL:	//������
									Printf24("Driver communication Error!",START_PROMPT_X2,START_PROMPT_Y2+5,RED_COLOR,1,0xffff);
											break;
								}
								break;
					}
				
				ACServoAlarmExec_flag=1;
				if(MotorType<MOTOR_AC_A6_SERVO)
					{
					if(StartCheck_mode>2)
						ACServoStop();  //�����ŷ�	ֹͣ
					}
				StartCheck_mode=0;
				}
			else		//���빤��״̬
				{
				PromptDis_flag=0;
				GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
					switch(ModBus_AcErr_Type)
					{
					case AC_ERR_Z:	//Z_Pulse����
							switch(Language)
								{
								case CHN_HAN:
									Printf24("�����ŷ�����������Z!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
								case ENGLISH:	
								case INDONSIA:	//ӡ��	
									Printf24("AC servo drive alarm!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
								case PORTUGAL:	//������
									Printf24("Alarme Servo drive!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
								}
							Printf32(Err_XXX,CURR_SIZE_X,CURR_SIZE_Y,RED_COLOR,1,CURREN_STEP_BACK_COLOR);
								break;
					case AC_ERR_CODE://������err code
								ErrCode[0]='E';
								ErrCode[1]='r';
								ErrCode[2]='r';
								ErrCode[3]=':';
								ErrCode[4]=(ModBus_ACErr>>8)/10+0x30;
								ErrCode[5]=(ModBus_ACErr>>8)%10+0x30;
								ErrCode[6]='.';
								ErrCode[7]=(unsigned char)ModBus_ACErr/10+0x30;
								ErrCode[8]=(unsigned char)ModBus_ACErr%10+0x30;
								ErrCode[9]=0;
								Printf24("Drv alarm",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								Printf24(ErrCode,REMIND_WINDOW_X+10*24,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
								break;
					case AC_ERR_LINK://ͨѶ����
							switch(Language)
								{
								case CHN_HAN:
									Printf24("������ͨѶ����!������",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
								case ENGLISH:	
								case INDONSIA:	//ӡ��	
								case PORTUGAL:	//������
									Printf24("Driver communication Error!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
											break;
								}
								break;
					}
				ACServoAlarmExec_flag=1;
				if((Run_flag==1)||(GoFrontEn_flag==1)||(GoBackEn_flag==1))
					{
					if(ModBus_AcErr_Type!=AC_ERR_LINK)	
						{
					ACServoStop();  //�����ŷ�	ֹͣ
				//RLOUT1_ON;    // ������жϿ�
						}
					}
				}
			}
		else	//����������---
			{
			if(WorkStart_flag==1)  
				{
				if((OIN9_PIN==0)&&(ModBus_Comm_LinkErr==0)&&(ModBus_ACErr==0))	//�����޸�
					{
					ACServoDrvErr_flag	=0;
					ModBus_AcErr_Type	=0;
					GLCD_SetWindow_Fill( REMIND_WINDOW_X, REMIND_WINDOW_Y, REMIND_WINDOW_X+REMIND_LENGTH, REMIND_WINDOW_Y+30, 0xfffff, 0xffff);//��ʾ��
					Printf24("Driver ok!",REMIND_WINDOW_X+10,REMIND_WINDOW_Y+5,RED_COLOR,0,0xffff);
					BellOUT_OFF;
					}	
				}
			}
		}
	}
else
	{
	if(ACServoDrvErr_flag==1)
		{
		ACServoDrvErr_flag=0;
		ACServoAlarmExec_flag=0;
		}
	}
} 

void ACMotorStopCheck(void)	//����ʵ�ʳߴ�
{
Int32U data_off;
RunStop_flag=1;	
switch(A6CoderCorrectMode)
	{
	case 0:
		A6CoderCorrectTime=0;
		A6CoderCorrectMode++;
			break;
	case 1:		
		A6CoderCorrectTime++;
		if(A6CoderCorrectTime>=200)
			{
			A6CoderCorrectTime=0;
			ReadCurrentSize_A6Coder();//��ȡ��ǰ A6������ֵ
			A6CoderCorrectMode++;
			}
			break;
	case 2://�ȴ� ��ȡ������ֵ
		if(ModBus_CodeDataMode==0x11)//��ȡ���
			{
			A6_CalCurSize();	
			if(CurrentSize_A6Coder>(TargetSize+3))//ʵ��ֵƫ��
				{
				data_off=CurrentSize_A6Coder-TargetSize;
				ACMotorRunStart(TargetSize-data_off);
				A6CoderCorrectRun_flag=1;//��������
				//*****
				RunStop_flag=0;
				Run_flag=1;
				InTargetPosit_flag=0;	//Ŀ��λ��
				AutoCutStart_flag=0;
				AirOffOK_flag=0;
				PressUp_flag=0;
				}
			else if(CurrentSize_A6Coder<(TargetSize-3))//ʵ��ֵƫС
				{
				data_off=TargetSize-CurrentSize_A6Coder;
				ACMotorRunStart(TargetSize+data_off);
				A6CoderCorrectRun_flag=1;//��������
				//*****
				RunStop_flag=0;
				Run_flag=1;
				InTargetPosit_flag=0;	//Ŀ��λ��
				AutoCutStart_flag=0;
				AirOffOK_flag=0;
				PressUp_flag=0;
				}
			else	//���
				{
				A6CoderEqual_flag=1;	
				A6CoderCorrectRun_flag=0;//��������
				}	
			A6CoderCorrectMode=0;
			}
		else	//δ��������
			{
			if(ModBus_Comm_LinkErr==1)	//ͨѶ����--------->Ĭ��ok
				{
				A6CoderEqual_flag=1;	
				A6CoderCorrectRun_flag=0;//��������
				A6CoderCorrectMode=0;
				}
				
			}
			break;	
		
	}	
}


