
#include "keyboard.h"


#include "key.h"
#include "pic_exec.h"
#include "io.h"

#include "uart_config.h"


// -----------����Ӧ�� ���أ��� a k e y b o a r d 0d 55 ��

Int8U KeyboardCheck_flag;
Int8U KeyboardLink_flag;
Int8U SendkeyACK_flag;
Int32U SendKeyACK_time;

Int32U KeyboardLink_time;


Int8U Keyboard_comm_mode;
Int8U rx_cou;
Int8U Rx_buf[12];
Int8U check;


const Int8U send_KEY[6]={0xaa,0x64,0x3f,0x5b,0x55,0};
const Int8U Key_ACK[10]="keyboard";


Int8U KeyLinkDis_flag;
//Int8U SendEnb_flag=1;

//-----------
Int8U KeyCodeFrameOk_flag;

KEY_DATA Key_data;
// KEY_DATA Key_data_ago;

Int8U KeyboardDown_flag;
// Int8U KeyboardExec_flag;

Int16U KeyboardDown_time;
Int32U Keycodesave;
//Int32U Keycodetemp;

Int8U StopKeyRelease_flag;
Int8U ShiftKey_flag;
Int16U shift_time;



void Comm_Keyboard(Int8U data)   //����ͨѶ
{
volatile Int8U ii,ok_flag=0;
if(WorkStart_flag==0)
	{
	}
else   
	{
	}

switch(Keyboard_comm_mode)
	{
	case 0:
		if(data==0xaa)
			{
			rx_cou=0;check=0;
			for(ii=0;ii<12;ii++)
				{
				Rx_buf[ii]=0;
				}
			Rx_buf[rx_cou++]=data;
			Keyboard_comm_mode++;
			
			//KeyboardDown_flag=0;  //�����ͷ�
			
			}
		
		// else if(data==0xf0)  //��ϼ�		
			// {
			// Key_data_ago.keycode=Key_data.keycode;
			// Key_data_ago.keyflag=Key_data.keyflag;
			// }
		break;
	case 1:
		if(data=='k')  //����Ӧ��======================================1
			{
			Rx_buf[rx_cou++]=data;
			check^=data;
			Keyboard_comm_mode++;
			}
		else        //���� ����==================================2
			{
			Rx_buf[rx_cou++]=data;
			check^=data;
			Keyboard_comm_mode=5;  ///keycode------------
			//KeyCodeFrameOk_flag=0;
			}
			break;
	case 2:	//Ӧ�����ݽ���	---------
		if(rx_cou<9)
			{
			Rx_buf[rx_cou++]=data;
			check^=data;
			}
		else
			{
			if(check==data)  //У����ȷ
				{
				for(ii=1;ii<9;ii++)
					{
					if(Rx_buf[ii]==Key_ACK[ii-1])  //ACK=="keyboard"
						ok_flag++;
					else
						break;	
					}
				if(ok_flag>=8)	
					//Rx_buf[rx_cou++]=data;
					Keyboard_comm_mode++;
				else
					{
					Keyboard_comm_mode=0;  //error
					// SendEnb_flag=1;
					}
				}
			else
				{
				Keyboard_comm_mode=0;  //error
				// SendEnb_flag=1;
				}
			}
		break;
	case 3:  
		if(data==0x55)
			{
			if(KeyboardLink_flag==0)
				{
				KeyboardLink_flag=1;  //����������
				KeyLinkDis_flag=0;
				}
			KeyboardLink_time=0;
			}
		Keyboard_comm_mode=0;  //  //���̼�����    --k--e--y--b--o--a--r--d-->>>
		// SendEnb_flag=1;
		break;
	
	//-------------------------���� ��ȡ--------
	case 5:     
		if(rx_cou<3)
			{
			Rx_buf[rx_cou++]=data;
			check^=data;
			}
		else
			{
			if(data==check)
				{
				Rx_buf[rx_cou++]=data;
				Keyboard_comm_mode++;
				}
			else
				{
				Keyboard_comm_mode=0;//error
				// SendEnb_flag=1;
				}
			}
		break;
	case 6://0x55
		if(data==0x55)
			{
			Key_data.keycode=Rx_buf[1];
			Key_data.keyflag=Rx_buf[2];
			KeyCodeFrameOk_flag=1; ////////////////////////////�����ȡ���
			}
		
		Keyboard_comm_mode=0;//	end-----------
		// SendEnb_flag=1;
		break;
	}
		
}


void ShiftKeyExec(void)//
{
if(ShiftKey_flag==1)
	{
	shift_time++;
	if(shift_time>=3000)
		{
		shift_time=0;
		ShiftKey_flag=0;
		}
	}
}

void Keyboard_scan(void)
{
Int8U k;
if(WorkStart_flag==0)
	{
	if(SendkeyACK_flag==0)
		{
		if(Keyboard_comm_mode==0)
			{
			SendkeyACK_flag=1;  //���ͼ��� �������	
			SendKeyACK_time=0;
			//--��������
		//	UART9_SendStr(send_KEY);
			//Keyboard_comm_mode=0;
			}
		}
	else
		{
		SendKeyACK_time++;
		if(SendKeyACK_time>=300)
			{
			SendkeyACK_flag=0;
			}
		}
	
	if(KeyboardLink_time<500)
		{
		KeyboardLink_time++;
		}
	else//keyboard --------���� δ����
		{
		if(KeyboardLink_flag==1)
			{
			KeyboardLink_flag=0;
			KeyLinkDis_flag=0;
			}
		}
	
	}
else
	{
	}
// if(KeyboardLink_flag==1)
	KeyboardCode_exec();//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}


void KeyboardCode_exec(void)
{
Int32U keycode_now=0xaaaa5555;
if(KeyboardDown_flag==0)
	{
	if(KeyCodeFrameOk_flag==1) //���� ��Ч
		{
		KeyCodeFrameOk_flag=0;
		if(Key_data.keyflag==K_DOWN)
			{
				switch(Key_data.keycode)  //����ת�� ����
					{
					case k_1:
						if(ShiftKey_flag==1)
							keycode_now=SHIFT_1_KEY_CODE;//shift+1
						else	
							keycode_now=NINE_KEY_CODE;		// 1**************
						break;
					case k_2:
						if(ShiftKey_flag==1)
							keycode_now=SHIFT_2_KEY_CODE;//shift+2
						else	
							keycode_now=MOVE_KEY_CODE;     // 2**************
						break;
					case k_3:
						if(ShiftKey_flag==1)
							keycode_now=SHIFT_3_KEY_CODE;//shift+3
						else	
							keycode_now=DELETE_KEY_CODE;      //3*************
						break;
					case k_4:
						if(ShiftKey_flag==1)
							keycode_now=SHIFT_4_KEY_CODE;//shift+4
						else	
							keycode_now=EIGHT_KEY_CODE;		//4***********
						break;
					case k_5:
						if(ShiftKey_flag==1)
							keycode_now=SHIFT_5_KEY_CODE;//shift+5
						else	
							keycode_now=NO_KEY_CODE;      // 5******************
						break;
					case k_6:
						if(ShiftKey_flag==1)
							keycode_now=SHIFT_6_KEY_CODE;//shift+6
						else	
							keycode_now=INSERT_KEY_CODE;      //6****************
						break;
					case k_7:
						keycode_now=SEVEN_KEY_CODE;	//7 **************
						break;
					case k_8:
						if(ShiftKey_flag==1)
							keycode_now=SHIFT_8_KEY_CODE;//shift+8
						else	
							keycode_now=YES_KEY_CODE;    // 8*************  
						break;
					case k_9:
						keycode_now=SUB_KEY_CODE;   // 9************
						break;
					case k_0:
						if(ShiftKey_flag==1)
							keycode_now=SHIFT_0_KEY_CODE;//shift+0
						else	
							keycode_now=PROG_KEY_CODE;     // 0  **************  
						break;
					case k_dot:
						keycode_now=ADD_KEY_CODE;   //  �㡰.��*************
						break;	
					case k_cancel:
						keycode_now=SIX_KEY_CODE;		// clear ����C********
						break;		
					case k_program:
						if(ShiftKey_flag==1)
							keycode_now=TEACH_TOUCH_CODE;		//ʾ�� ģʽ
						else
							keycode_now=FOUR_KEY_CODE;	//��̰���******************����  ��� ��ģʽ
						break;
					case k_manual:
						keycode_now=TWO_KEY_CODE;		//�ֶ�****************
						break;
					case k_auto:
						if(ShiftKey_flag==1)
							keycode_now=AUTOCUT_TOUCH_CODE;	//�Ե� ģʽ
						else
							keycode_now=THREE_KEY_CODE;		//�Զ�******************
						break;
					case k_procedure:
						keycode_now=PROC_KEY_CODE;		//����******************
						break;	
					
					case k_f1:
						keycode_now=AUTO_KEY_CODE;       // F1**********************
						break;
					case k_f2:
						keycode_now=READ_KEY_CODE;       // F2*******************�˳�
						break;
					case k_f3:
						keycode_now=RETURN_KEY_CODE;      //F3************ѡ�� �����
						break;
					case k_f4:
						keycode_now=MANUAL_KEY_CODE;   // F4************** ��ֽ/��  ��־
						break;	
					case k_f5:
						if(ShiftKey_flag==1)
							keycode_now=SHIFT_F5_KEY_CODE;	//shift+F5
						else
							keycode_now=F5_KEY_CODE;		//F5*****
						break;
					case k_f6:
						keycode_now=F6_KEY_CODE;		//F6*****
						break;
					case k_help:
						keycode_now=HELP_KEY_CODE;		//����*****
						break;	
					case k_ahead:
						keycode_now=NEXTKNIFE_KEY_CODE;   //ǰ��***************
						break;
					case k_fast_ahead:
						keycode_now=FAST_AHEAD_KEY_CODE;   //�������***************>>
						break;	
					case k_back:
						keycode_now=ADJUST_KEY_CODE;     //����**************
						break;
					case k_fast_back:
						keycode_now=FAST_BACK_KEY_CODE;     //���˰���*****************<<
						break;
					case k_add:
						keycode_now=REV_KEY_CODE;   //  ��+/*��  ***************
						break;
					case k_sub:
						keycode_now=OPTION_KEY_CODE;    //����  ��-/����  *************
						break;
					case k_mul:
						keycode_now=MUL_KEY_CODE;   //  ��*��  ***************
						break;
					case k_div:
						keycode_now=DIV_KEY_CODE;    //  ������  *************
						break;	
					case k_equal:
						keycode_now=EQUAL_KEY_CODE;    //  ��=��  *************
						break;	
					case k_delete:
						if(ShiftKey_flag==1)
							keycode_now=F5_KEY_CODE;		//F5*****ȫɾ
						else
							keycode_now=FIVE_KEY_CODE;		//ɾ������*************
						break;
					case k_modify:
						keycode_now=MODIFY_KEY_CODE;    //  �޸� *************
						break;	
					case k_pgup:
						keycode_now=PGUP_KEY_CODE;		//��ҳ*************
						break;
					case k_pgdown:
						keycode_now=PGDOWN_KEY_CODE;    // ��ҳ*******************
						break;
					case k_run:
						keycode_now=UP_KEY_CODE;    ///////////����*******************
						break;	
					case k_stop:
						if(StopKeyRelease_flag==1)	//  JOG �Ѿ����� ��ֹͣ��key �� ��һ��������
							StopKeyRelease_flag=0;	
						else
							keycode_now=STOP_KEY_CODE;    ///////////ֹͣ*******************
						break;	
					case k_enter:
						keycode_now=DOWN_KEY_CODE;   // ȷ��**************
						break;
					case k_down:
						keycode_now=DENGFENG_KEY_CODE;  //���¼�ͷ����**************��
						break;
					case k_up:
						keycode_now=DENGJU_KEY_CODE;  //���ϼ�ͷ����**************��
						break;
					case k_left:
						if(ShiftKey_flag==1)	//+++++++++++15inch++++
							keycode_now=SHIFT_LEFT_KEY_CODE;       //  shift+��
						else
							keycode_now=LEFT_KEY_CODE;    //�� **********
						break;
					case k_right:
						if(ShiftKey_flag==1)	//+++++++++++15inch++++
							keycode_now=SHIFT_RIGHT_KEY_CODE;       //  shift+��
						else
							keycode_now=RIGHT_KEY_CODE;    //�� **********
						break;
					case k_shift:
						keycode_now=SHIFT_KEY_CODE;    //shift **********
						/***
						switch(WorkMode)
							{
							case  PROG_MODE://��̻�����
									keycode_now=TEACH_TOUCH_CODE;		//ʾ�� ģʽ
									break;
							case AUTO_MODE://�Զ��������� 
									keycode_now=AUTOCUT_TOUCH_CODE;	//�Ե� ģʽ
									break;
							default:
									ShiftKey_flag=1;
									shift_time=0;
									BellOn_Enb();
									break;
							}**/
							ShiftKey_flag=1;
							shift_time=0;
							BellOn_Enb();
						break;	
					case k_pushpap:
						keycode_now=JOSTLE_KEY_CODE;    //��ֽ **********
						break;	
					case k_insert:
						keycode_now=ZERO_KEY_CODE;		//����********
						break;
					//----------	
					case k_fun_program:			//fun+���==ʾ��
						keycode_now=TEACH_TOUCH_CODE;		//ʾ�� ģʽ
						break;	
					case k_fun_auto:			//fun+�Զ�==�Ե�
						keycode_now=AUTOCUT_TOUCH_CODE;	//�Ե� ģʽ
						break;	
					case k_fun_0:			//fun+0==
						keycode_now=SHIFT_0_KEY_CODE;//fun+0
						break;	
					case k_fun_1:			//fun+1==
						keycode_now=SHIFT_1_KEY_CODE;//fun+1
						break;	
					case k_fun_f5:			//fun+f5==
						keycode_now=SHIFT_F5_KEY_CODE;//fun+F5
						break;	
					case k_fun_8:			//fun+8==
						keycode_now=SHIFT_8_KEY_CODE;//fun+8
						break;	
					case k_fun_ahead:			//fun+ǰ��==���
						keycode_now=FAST_AHEAD_KEY_CODE;   //�������***************>>
						break;	
					case k_fun_back:			//fun+����==����
						keycode_now=FAST_BACK_KEY_CODE;     //���˰���*****************<<
						break;
					// case k_fun_right:
						// keycode_now=RIGHT_KEY_CODE;    // fun+��**********��
						// break;
					}
				
				if(Key_data.keycode!=k_shift)	//�� �ϵ�key ��־
					{
					ShiftKey_flag=0;
					shift_time=0;
					}
				 ////////////////////���� ����//////////////
				 if(keycode_now!=0xaaaa5555)
					Keycodesave=Key_data.keycode;
				else
					Keycodesave=0;
			////////////////////////////
				switch(Board_TestMod)
					{
					case 0:
						if(WorkStart_flag==0)
							{
							KeyExec(keycode_now); //��ֵ ���ܴ���	
							}
						else
							{
							if(WorkMode==MANUAL_IO_TEST_MODE)	//���Զ˿� mode
								{
								if(keycode_now!=READ_KEY_CODE)	//F2
									{
									BellOn_Enb();
									KeyDis_sel(Keycodesave,1);  //***************������ʾ
									}
								else
									KeyExec(keycode_now); //��ֵ ���ܴ���	
								}
							else
								KeyExec(keycode_now); //��ֵ ���ܴ���	
							}
							break;
					case TEST_HELP:
					case TEST_TOUCH:
					case TEST_ICON:
					case TEST_SYS_WORD:
					case TEST_SYS_TYPE://���� ����ϵͳѡ��
					case TEST_PAGE_LINE://ÿҳ���� ѡ��
						if(keycode_now!=0xaaaa5555)
							{
							KeyExec(keycode_now); //��ֵ ���ܴ���
							}
							break;
					case TEST_BOARD://���� ����ģʽ  3
						BellOn_Enb();
						KeyDis_sel(Keycodesave,1);  //***************������ʾ
							break;
					}	
			/***
			if(StopKeyRelease_flag==1)	//  �ظ����� ��ֹͣ��key 	��
				{
				if(Key_data.keycode!=k_stop)
					{
					LED2_ON;  //   ########################
					KeyboardDown_flag=1;
					StopKeyRelease_flag=0;	//�ظ� ����
					}
				}
			else	//  ���� ���ظ�
				{
				LED2_ON;  //   ########################
				KeyboardDown_flag=1;
				// KeyboardDown_time=0;
				}
				***/
			if(Key_data.keycode!=k_stop)	//   20161114  ���� ���ظ�
				{
				LED2_ON;  
				KeyboardDown_flag=1;
				}
			else
				{
				if(keycode_now!=0xaaaa5555)
					{
					LED2_ON;  
					KeyboardDown_flag=1;
					}
				}
			}
		}
	}
else
	{
	if(KeyCodeFrameOk_flag==1) //������Ч
		{
		KeyCodeFrameOk_flag=0;
		if(Key_data.keyflag==K_UP)
			{
			KeyboardDown_flag=0;  //�����ͷ� ****************
			Key_data.keyflag=0;
			
			LED2_OFF;  //
				
			if(Board_TestMod==TEST_BOARD)
				{
				KeyDis_sel(Keycodesave,0);  //***************������ʾ 
				}
			else if(Board_TestMod==0)
				{
				if(WorkMode==MANUAL_IO_TEST_MODE)	//���Զ˿� mode
					{
					if(keycode_now!=READ_KEY_CODE)	//F2
						{
						KeyDis_sel(Keycodesave,0);  //***************������ʾ
						}
					}
				}
			////////////////////////////
			if(Key_data.keycode==k_stop)
				{
				GoFrontEn_flag=0;
				GoBackEn_flag=0;
				// StopKeyRelease_flag=1;//+++++20171103		
				//----------------------------------------
				MoveStop();
				RLOUT1_OFF; RLOUT1_1_OFF;   // // �������
				ACMotor_ReleaseStop();  //-------
				}
			// Key_data.keycode=0;//+++++20171103
			}
		else  //-------------jog stop key 
			{
			if(Key_data.keycode==k_stop)
				{
				KeyboardDown_flag=0;  //�����ͷ� ****************
				// Key_data.keycode=0;//+++++20171103
				Key_data.keyflag=0;
				
				LED2_OFF;  //	
				//----------------------------------------
				if(Board_TestMod==TEST_BOARD)
					{
					KeyDis_sel(Keycodesave,0);  //***************������ʾ 
					}
				else if(Board_TestMod==0)
					{
					if(WorkMode==MANUAL_IO_TEST_MODE)	//���Զ˿� mode
						{
						if(keycode_now!=READ_KEY_CODE)	//F2
							{
							KeyDis_sel(Keycodesave,0);  //***************������ʾ
							}
						}
					}
				////////////////////////////
				GoFrontEn_flag=0;
				GoBackEn_flag=0;
				StopKeyRelease_flag=1;	
				//----------------------------------------
				MoveStop();
				RLOUT1_OFF; RLOUT1_1_OFF;    // // �������
				ACMotor_ReleaseStop();  //-------
				}
			}
		}
	else
		{
		// if((Key_data.keycode!=k_ahead)&&(Key_data.keycode!=k_back)
		// &&(Key_data.keycode!=k_fast_ahead)&&(Key_data.keycode!=k_fast_back))
			// {
			// KeyboardDown_time++;
			// if(KeyboardDown_time>=500)
				// {
				// KeyboardDown_time=0;
				// KeyboardDown_flag=0;  //�����ͷ� ****************
				// Key_data.keycode=0;
				// Key_data.keyflag=0;
					
				// ////////////////////////////
				// GoFrontEn_flag=0;
				// GoBackEn_flag=0;
				// if(Board_TestMod==TEST_BOARD)
					// {
					// KeyDis_sel(Keycodesave,0);  //***************������ʾ 
					// MoveStop();
					// RLOUT1_OFF;    // // �������
					// }
					
				// //----------------------------------------
				// ACMotor_ReleaseStop();  //-------
				// }
			// }
		
		}
	}
	
}



