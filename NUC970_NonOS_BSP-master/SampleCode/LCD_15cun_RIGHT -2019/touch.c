





#include"touch.h"
//#include"tsc2046.h"

#include"key.h"
#include"m25pe16.h"
#include"io.h"
#include "port.h"
#include"keyboard.h"
#include "gtp.h"


Int16U Touch_down_time;
Int16U Touch_release_time;
Int16U Touch_long_time;
Int8U Touch_down_flag; 
Int8U Touch_exec_flag; 
Int8U Touch_long_exec_flag; 
Int8U Touch_start_flag;

TOUCH TouchAD_LU;
TOUCH TouchAD_LD;
TOUCH TouchAD_RU;
TOUCH TouchAD_RD;
TOUCH TouchAD_MID;

TOUCH Touch_Pos;
TOUCH Touch_Pos_save;

Int32U TouchDegree_x;
Int32U TouchDegree_y;

Int32U Touch_code;
Int32U Touch_code_temp;
Int32U TouchLong_code;

//-----touchУ׼ ϵ��
unsigned int A0;
unsigned int A1;
unsigned int A2;
unsigned int A3;
unsigned int A4;
unsigned int A5;
unsigned int A6;
volatile Int16U T_X[5],T_Y[5];

Int8U FlagTouRow_num=0;
Int8U TouchLnie_num=0;

Int8U LongTouchDis_flag;



Int8U CheckTouAxValue(void)//�ж���Χ
{
Int32U add,temp;	
Int8U ok_flag=0;
#ifdef TOU_CALIBRATE_A1_6	//no liner method
	if(A0>A0_PER)
		{
		temp=A0-A0_PER;
		}
	else
		{
		temp=A0_PER-A0;
		}
	if(temp<5500000)	//���֮��
		{
		if(A1>A1_PER)
			{
			temp=A1-A1_PER;
			}
		else
			{
			temp=A1_PER-A1;
			}
		if(temp<50000)	//A1���֮��
			{	
				if(A3>A3_PER)
					{
					temp=A3-A3_PER;
					}
				else
					{
					temp=A3_PER-A3;
					}
				if(temp<2500000)	//A3���֮��	
					{
						if(A4>A4_PER)
							{
							temp=A4-A4_PER;
							}
						else
							{
							temp=A4_PER-A4;
							}		
						if(temp<100000)	//A4���֮��
							{
							ok_flag=1;
							}
						
					}
				
			}
		}
	if(ok_flag==0)	//����Ĭ��ֵ
		{
		A0=A0_PER;
		A1=A1_PER;
		A2=A2_PER;
		A3=A3_PER;
		A4=A4_PER;
		A5=A5_PER;
		A6=A6_PER;
		return 1;//��Ч������Ĭ��
		}
	return	0; // ok

#else
	if((TouchDegree_x<400000)||(TouchDegree_x>600000)
		||(TouchDegree_y<400000)||(TouchDegree_y>500000)
		||(TouchAD_MID.x<800)||(TouchAD_MID.x>1500)
		||(TouchAD_MID.y<800)||(TouchAD_MID.y>1500))       //δУ׼ ֵ
		{
		TouchDegree_x=TOU_DEGREE_X;
		TouchDegree_y=TOU_DEGREE_Y;
		TouchAD_MID.x=TOU_OFFSET_X;
		TouchAD_MID.y=TOU_OFFSET_Y;
		return 1;//��Ч������Ĭ��
		}
	return	0; // ok	
#endif
}

void Read_TouchDatas(void)
{
pInt8U pdata;
Int32U add;
Int8U n;
add=ORIGINAL_25PEADD+80;	//80+4*7	=	80+28
#ifdef TOU_CALIBRATE_A1_6	//no liner method
	pdata=(pInt8U)&A0;
	FastRead_Datas_Start(add);
	for(n=0;n<4;n++)
		{
		*pdata++=ReadFlash_Datas();
		}
	pdata=(pInt8U)&A1;
	for(n=0;n<4;n++)
		{
		*pdata++=ReadFlash_Datas();
		}
	pdata=(pInt8U)&A2;
	for(n=0;n<4;n++)
		{
		*pdata++=ReadFlash_Datas();
		}
	pdata=(pInt8U)&A3;
	for(n=0;n<4;n++)
		{
		*pdata++=ReadFlash_Datas();
		}
	pdata=(pInt8U)&A4;
	for(n=0;n<4;n++)
		{
		*pdata++=ReadFlash_Datas();
		}
	pdata=(pInt8U)&A5;
	for(n=0;n<4;n++)
		{
		*pdata++=ReadFlash_Datas();
		}
	pdata=(pInt8U)&A6;
	for(n=0;n<4;n++)
		{
		*pdata++=ReadFlash_Datas();
		}
	FlashChip_Dis;
#else
	pdata=(pInt8U)&TouchDegree_x;
	FastRead_Datas_Start(add);
	for(n=0;n<4;n++)
		{
		*pdata++=ReadFlash_Datas();
		}
	pdata=(pInt8U)&TouchDegree_y;	
	for(n=0;n<4;n++)
		{
		*pdata++=ReadFlash_Datas();
		}
	pdata=(pInt8U)&TouchAD_MID;
	for(n=0;n<8;n++)
		{
		*pdata++=ReadFlash_Datas();
		}	
	FlashChip_Dis;
#endif
CheckTouAxValue();//�ж���Χ	
}
void Save_TouchDatas(void)
{
pInt8U pdata;
Int32U add;
add=ORIGINAL_25PEADD+80;	//80+4*7	=	80+28
#ifdef TOU_CALIBRATE_A1_6	//no liner method
	pdata=(pInt8U)&A0;
	Write_25pe_data(pdata, add, 4);add+=4;
	pdata=(pInt8U)&A1;
	Write_25pe_data(pdata, add, 4);add+=4;
	pdata=(pInt8U)&A2;
	Write_25pe_data(pdata, add, 4);add+=4;
	pdata=(pInt8U)&A3;
	Write_25pe_data(pdata, add, 4);add+=4;
	pdata=(pInt8U)&A4;
	Write_25pe_data(pdata, add, 4);add+=4;
	pdata=(pInt8U)&A5;
	Write_25pe_data(pdata, add, 4);add+=4;
	pdata=(pInt8U)&A6;
	Write_25pe_data(pdata, add, 4);add+=4;
#else
	pdata=(pInt8U)&TouchDegree_x;
	Write_25pe_data(pdata, add, 4);add+=4;
	pdata=(pInt8U)&TouchDegree_y;
	Write_25pe_data(pdata, add, 4);add+=4;
	pdata=(pInt8U)&TouchAD_MID;
	Write_25pe_data(pdata, add, 8);
#endif

}


void ToucScan(void)
{
if(Touch_down_flag==0)
	{
	if(Touch_start_flag==0)
		{
		if(TOUCH_INT_PIN==0)
		//if(TouchAD_get()==1)//������Ч
			{
			Touch_start_flag=1;
			Touch_down_time=0;
			}
		}
	else
		{
		Touch_down_time++;
		if(Touch_down_time>=30)
			{
			Touch_down_time=0;
			Touch_down_flag=1;
			Touch_start_flag=0;
			}
		}
	}
else
	{
	if(Touch_exec_flag==0)
		{
		//if(TOUCH_INT_PIN==0)
		if(TouchAD_get()==1)//������Ч
			{
			Touch_down_time++;
			if(Touch_down_time>=TOU_SHAKE_TIME)
				{
				Touch_down_time=0;
				Touch_release_time=0;
				LED2_ON;
				Touch_exec_flag=1;
				Touch_long_time=0;
				//if(TouchAD_get()==1)//������Ч
					// {
					// if(Board_TestMod<=TEST_TOUCH)	//�� ���� �˿ڲ���
						TouchKey_exec();  //������  ����
					// }
			
				}
			}	
		else
			{
			Touch_down_flag=0;
			}
		}
	else  //�ȴ��ͷ�
		{
		if(TOUCH_INT_PIN!=0)   //�ж�����  �ͷ�
			{
			Touch_release_time++;
			if(Touch_release_time>TOU_SHAKE_TIME_UP)
				{LED2_OFF;
				Touch_release_time=0;
				Touch_exec_flag=0;
				Touch_down_flag=0;
				Touch_long_exec_flag=0;
				GoFrontEn_flag=0;
				GoBackEn_flag=0;
				//---------------------------������ť�ͷ� ��ʾ
					TouchButton_dis(Touch_code,0);  //������  ��ʾ
				Touch_code=0;//-------�ͷź� �崥����ֵ
				ACMotor_ReleaseStop();
				}
			}
		else  //�����и���ʱ   ɨ��ֵ    �ͷ�
			{
			Touch_release_time=0;
			if(TouchAD_get()!=1)//����
				{
				Touch_down_time++;
				if(Touch_down_time>=TOU_SHAKE_TIME_UP)
					{LED2_OFF;
					Touch_exec_flag=0;
					Touch_down_flag=0;
					Touch_long_exec_flag=0;
					GoFrontEn_flag=0;
					GoBackEn_flag=0;
					//---------------------------
						TouchButton_dis(Touch_code,0);  //������  ��ʾ
					Touch_code=0;//-------�ͷź� �崥����ֵ
					ACMotor_ReleaseStop();
					}
				}
			else
				{
				Touch_down_time=0;
				//----------δ�ͷ�
				// if(TouchAD_get()==1)//������Ч
					// {
					if(Board_TestMod==TEST_BOARD)  //���幦�ܲ���mode-------------------------------
						{
						GetTouch_pos();
						if(Touch_Pos.x>=C_GLCD_H_SIZE)
							Touch_Pos.x=C_GLCD_H_SIZE-1;
						if(Touch_Pos.y>=C_GLCD_V_SIZE)
							Touch_Pos.y=C_GLCD_V_SIZE-1;
						PutPixel(Touch_Pos.x,Touch_Pos.y,RED_COLOR);//��д
						}
					else
						{
						Touch_long_time++;
						if(Touch_long_time>=TOUCH_ERR_TIME)  ////---------------------------����  ����ʱ�������ǿ���ͷ�
							{	
								TouchButton_dis(Touch_code,0);  //������  ��ʾ
							Touch_code=0;//-------�ͷź� �崥����ֵ
							
							Touch_exec_flag=0;
							Touch_down_flag=0;
							Touch_long_exec_flag=0;
							GoFrontEn_flag=0;
							GoBackEn_flag=0;
							}
						}
					//}
				}
			}
		
		}
	}
}


void TouchKey_exec(void)
{
Int8U n;Int8U m1,m2;
	//-----Tslib ---
volatile double  x, y, x2, y2, xy, z, zx, zy;
volatile double det, a, b, c, e, f, i;

volatile double scaling = 65536.0;//500.0;//65536.0;
	
//----my  liner----
volatile Int16U tAD,gap;

if(Board_TestMod==TEST_TOUCH)//У׼����
	{
	#ifdef TOU_CALIBRATE_A1_6	//no liner method
		//--------------Nonlinear-----
		switch(TouchCalcu_mode)
			{
			case 0://����
				for(n=0;n<5;n++)
					{
					T_X[n] = T_Y[n] = 0;
					}
				Draw_cross(TOUCH_X1,TOUCH_Y1,WHITE_COLOR);
				Draw_cross(TOUCH_X2,TOUCH_Y2,RED_COLOR);
					break;
			case 1://����
				
				Draw_cross(TOUCH_X2,TOUCH_Y2,WHITE_COLOR);
				Draw_cross(TOUCH_X3,TOUCH_Y3,RED_COLOR);
					break;
			case 2://����
				Draw_cross(TOUCH_X3,TOUCH_Y3,WHITE_COLOR);
				Draw_cross(TOUCH_X4,TOUCH_Y4,RED_COLOR);
					break;
			case 3://����
				Draw_cross(TOUCH_X4,TOUCH_Y4,WHITE_COLOR);
				Draw_cross(TOUCH_X_MID,TOUCH_Y_MID,RED_COLOR);
				
					break;
			case 4://����
				Draw_cross(TOUCH_X_MID,TOUCH_Y_MID,WHITE_COLOR);
				
					break;
			}
		if(TouchCalcu_mode<5)
			{
			T_X[TouchCalcu_mode]=TouchAD.x;
			T_Y[TouchCalcu_mode]=TouchAD.y;
			TouchCalcu_mode++;
			}
			
			//------------touch screen  5 point У׼-------�㷨------
		if(TouchCalcu_mode>=5)
			{
			x = y = x2 = y2 = xy = 0;
			for(n=0;n<5;n++)
				{
				x += (double)T_X[n];
				y += (double)T_Y[n];
				x2 += (double)(T_X[n]*T_X[n]);
				y2 += (double)(T_Y[n]*T_Y[n]);
				xy += (double)(T_X[n]*T_Y[n]);
				}
			det = (5*((x2*y2) - (xy*xy))) + (x*((xy*y) - (x*y2))) + (y*(x*xy - y*x2));
						
			a = ((x2*y2) - (xy*xy))/det;
			b = ((xy*y) - (x*y2))/det;
			c = ((x*xy) - (y*x2))/det;
			e = ((5*y2) - (y*y))/det;
			f = ((x*y) - (5*xy))/det;
			i = ((5*x2) - (x*x))/det;
			
			z = zx = zy = 0;//-------------------------------------
			z += (double)(TOUCH_X1+TOUCH_X2+TOUCH_X3+TOUCH_X4+TOUCH_X_MID);
			zx += (double)(TOUCH_X1*T_X[0]);
			zy += (double)(TOUCH_X1*T_Y[0]);
			
			zx += (double)(TOUCH_X2*T_X[1]);
			zy += (double)(TOUCH_X2*T_Y[1]);
			
			zx += (double)(TOUCH_X3*T_X[2]);
			zy += (double)(TOUCH_X3*T_Y[2]);
			
			zx += (double)(TOUCH_X4*T_X[3]);
			zy += (double)(TOUCH_X4*T_Y[3]);
			
			zx += (double)(TOUCH_X_MID*T_X[4]);
			zy += (double)(TOUCH_X_MID*T_Y[4]);
			
			A0 = (int)(((a*z) + (b*zx) + (c*zy))*(scaling));
			A1 = (int)(((b*z) + (e*zx) + (f*zy))*(scaling));
			A2 = (int)(((c*z) + (f*zx) + (i*zy))*(scaling));
			
			z = zx = zy = 0;//-------------------------------------
			z += (double)(TOUCH_Y1+TOUCH_Y2+TOUCH_Y3+TOUCH_Y4+TOUCH_Y_MID);
			zx += (double)(TOUCH_Y1*T_X[0]);
			zy += (double)(TOUCH_Y1*T_Y[0]);

			zx += (double)(TOUCH_Y2*T_X[1]);
			zy += (double)(TOUCH_Y2*T_Y[1]);

			zx += (double)(TOUCH_Y3*T_X[2]);
			zy += (double)(TOUCH_Y3*T_Y[2]);

			zx += (double)(TOUCH_Y4*T_X[3]);
			zy += (double)(TOUCH_Y4*T_Y[3]);

			zx += (double)(TOUCH_Y_MID*T_X[4]);
			zy += (double)(TOUCH_Y_MID*T_Y[4]);
			
			A3 = (int)(((a*z) + (b*zx) + (c*zy))*(scaling));
			A4 = (int)(((b*z) + (e*zx) + (f*zy))*(scaling));
			A5 = (int)(((c*z) + (f*zx) + (i*zy))*(scaling));
			
			A6 = (int)scaling; 
			
			//--------���� �˳�-----------------------------
			if(CheckTouAxValue()==0)//�ж���Χ
				{
				GLCD_SetWindow_Fill( 200, 120, 600, 200, 0xfffff, 0xffff);//
			Printf32("Touch set OK��",200,100,RED_COLOR,0,0xffff);
				volatile int wait=5000000;
				while(wait--);
				}
			Save_TouchDatas();//-------------------����У׼ֵ
			StartHelpMode_dis();
			Board_TestMod=TEST_HELP;
			}
	#else		
	switch(TouchCalcu_mode)
		{
		case 0://����
			TouchAD_LU.x=TouchAD.x;
			TouchAD_LU.y=TouchAD.y;
			Draw_cross(TOUCH_X1,TOUCH_Y1,WHITE_COLOR);
			Draw_cross(TOUCH_X2,TOUCH_Y2,RED_COLOR);
			TouchCalcu_mode++;
				break;
		case 1://����
			TouchAD_LD.x=TouchAD.x;
			TouchAD_LD.y=TouchAD.y;
			Draw_cross(TOUCH_X2,TOUCH_Y2,WHITE_COLOR);
			Draw_cross(TOUCH_X3,TOUCH_Y3,RED_COLOR);
			TouchCalcu_mode++;
			
				break;
		case 2://����
			TouchAD_RD.x=TouchAD.x;
			TouchAD_RD.y=TouchAD.y;
			Draw_cross(TOUCH_X3,TOUCH_Y3,WHITE_COLOR);
			Draw_cross(TOUCH_X4,TOUCH_Y4,RED_COLOR);
			TouchCalcu_mode++;	
				break;
		case 3://����
			TouchAD_RU.x=TouchAD.x;
			TouchAD_RU.y=TouchAD.y;
			Draw_cross(TOUCH_X4,TOUCH_Y4,WHITE_COLOR);
			Draw_cross(TOUCH_X_MID,TOUCH_Y_MID,RED_COLOR);
			#ifdef	LCD_TOUCH_REVERSE
			//tAD=((TouchAD_LU.x+TouchAD_LD.x)>>1)-((TouchAD_RU.x+TouchAD_RD.x)>>1);
				tAD=((TouchAD_RU.x+TouchAD_RD.x)>>1)-((TouchAD_LU.x+TouchAD_LD.x)>>1);
			#else
				tAD=((TouchAD_LU.x+TouchAD_LD.x)>>1)-((TouchAD_RU.x+TouchAD_RD.x)>>1);
			#endif	
			gap=TOUCH_X3-TOUCH_X1;
			TouchDegree_x=gap*1000000/tAD;
			#ifdef	LCD_TOUCH_REVERSE
			//tAD=((TouchAD_LU.y+TouchAD_RU.y)>>1)-((TouchAD_LD.y+TouchAD_RD.y)>>1);
				tAD=((TouchAD_LD.y+TouchAD_RD.y)>>1)-((TouchAD_LU.y+TouchAD_RU.y)>>1);
			#else
				tAD=((TouchAD_LU.y+TouchAD_RU.y)>>1)-((TouchAD_LD.y+TouchAD_RD.y)>>1);
			#endif	
			gap=TOUCH_Y2-TOUCH_Y1;
			TouchDegree_y=gap*1000000/tAD;
			TouchCalcu_mode++;
				break;
		case 4://����
			TouchAD_MID.x=TouchAD.x;
			TouchAD_MID.y=TouchAD.y;
			Draw_cross(TOUCH_X_MID,TOUCH_Y_MID,WHITE_COLOR);
			
			//--------���� �˳�-----------------------------
			if(CheckTouAxValue()==0)//�ж���Χ
				{
				GLCD_SetWindow_Fill( 200, 120, 600, 200, 0xfffff, 0xffff);//
				Printf32("У׼��ɣ�",200,100,RED_COLOR,0,0xffff);
				volatile int wait=10000000;
				while(wait--);
				}
			Save_TouchDatas();//-------------------����У׼ֵ
			
			StartHelpMode_dis();
			Board_TestMod=TEST_HELP;
				break;
		}
	#endif	
	}
else
	{
	GetTouchKeyCode();// ��ô��� ��ֵ
	//************************************������ť ������ʾ ����*********
	TouchButton_dis(Touch_code,1);  //������  ��ʾ
	//************************������ ���ܴ���**********************
	if(Touch_code!=0)
		{
		//���빦�� �л�----------
		switch(Touch_code)
			{
			// // case SHIFT_KEY_CODE:    //shift *********
					// // switch(WorkMode)
						// // {
						// // // // case  PROG_MODE://��̻�����
								// // // // Touch_code_temp=TEACH_TOUCH_CODE;		//ʾ�� ģʽ
								// // // // break;
						// // case TEACH_MODE://ʾ�� ģʽ
								// // Touch_code_temp=FOUR_KEY_CODE;	//���mode
								// // break;		
						// // case AUTO_MODE://�Զ��������� 
								// // Touch_code_temp=AUTOCUT_TOUCH_CODE;	//�Ե� ģʽ
								// // break;
						// // case SELF_CUT_MODE:  //�Ե��� ģʽ 
								// // Touch_code_temp=THREE_KEY_CODE;	//�Զ�mode
								// // break;		
						// // default:
								// // Touch_code_temp=SHIFT_KEY_CODE;    //shift *********
								// // ShiftKey_flag=1;
								// // shift_time=0;
								// // BellOn_Enb();
								// // break;
						// // }
						// // break;
			default:
					Touch_code_temp=Touch_code;    //*********����key ����
						break;
			}
		KeyExec(Touch_code_temp); //��������------------
		}
	}
}

void GetTouch_pos(void) //�õ����� ����
{

volatile Int32U offset,temp;
#ifdef TOU_CALIBRATE_A1_6	//no liner method
	#ifdef CAP_TOUCH
	if(TOUCH_ORIGIN==LEFT)
		{
		Touch_Pos.x=TouchAD.x;//(A0 + A1*TouchAD.x + A2*TouchAD.y ) / A6;
		Touch_Pos.y=TouchAD.y;//(A3 + A4*TouchAD.x + A5*TouchAD.y ) / A6;
		//////	Touch_Pos.x+=TOUCH_SHIFT_X;
		//////Touch_Pos.y+=TOUCH_SHIFT_Y;
		}
	else
		{
		Touch_Pos.x=C_GLCD_H_SIZE-TouchAD.x;//(A0 + A1*TouchAD.x + A2*TouchAD.y ) / A6;
		Touch_Pos.y=C_GLCD_V_SIZE-TouchAD.y;//(A3 + A4*TouchAD.x + A5*TouchAD.y ) / A6;
		}
		Touch_Pos.x-=TOUCH_SHIFT_X;
		Touch_Pos.y-=TOUCH_SHIFT_Y;
		
	#else
	Touch_Pos.x=(A0 + A1*TouchAD.x + A2*TouchAD.y ) / A6;
	Touch_Pos.y=(A3 + A4*TouchAD.x + A5*TouchAD.y ) / A6;

	#endif
#else
	//---------------------x
	if(TouchAD.x>TouchAD_MID.x)
		{
		offset=(TouchAD.x-TouchAD_MID.x)*TouchDegree_x;
		temp=offset/1000000;
		if(temp>TOUCH_X_MID)
			Touch_Pos.x=0;
		else
			{
			#ifdef	LCD_TOUCH_REVERSE
			//Touch_Pos.x=TOUCH_X_MID-temp;
				Touch_Pos.x=TOUCH_X_MID+temp;
			#else
				Touch_Pos.x=TOUCH_X_MID-temp;
			#endif	
			}
		}
	else
		{
		offset=(TouchAD_MID.x-TouchAD.x)*TouchDegree_x;
		temp=offset/1000000;
		#ifdef	LCD_TOUCH_REVERSE
		//Touch_Pos.x=TOUCH_X_MID+temp;
			Touch_Pos.x=TOUCH_X_MID-temp;
		#else
			Touch_Pos.x=TOUCH_X_MID+temp;
		#endif	
		if(Touch_Pos.x>C_GLCD_H_SIZE)
			Touch_Pos.x=C_GLCD_H_SIZE;
		}	
	//----------------------y	
	if(TouchAD.y>TouchAD_MID.y)
		{
		offset=(TouchAD.y-TouchAD_MID.y)*TouchDegree_y;
		temp=offset/1000000;
		if(temp>TOUCH_Y_MID)
			Touch_Pos.y=0;
		else
			{
			#ifdef	LCD_TOUCH_REVERSE
			//Touch_Pos.y=TOUCH_Y_MID-temp;
				Touch_Pos.y=TOUCH_Y_MID+temp;
			#else
				Touch_Pos.y=TOUCH_Y_MID-temp;
			#endif	
			}
		}
	else
		{
		offset=(TouchAD_MID.y-TouchAD.y)*TouchDegree_y;
		temp=offset/1000000;
		#ifdef	LCD_TOUCH_REVERSE
		//Touch_Pos.y=TOUCH_Y_MID+temp;
			Touch_Pos.y=TOUCH_Y_MID-temp;
		#else
			Touch_Pos.y=TOUCH_Y_MID+temp;
		#endif	
		if(Touch_Pos.y>C_GLCD_V_SIZE)
			Touch_Pos.y=C_GLCD_V_SIZE;
		}	
	if(Touch_Pos.x>=C_GLCD_H_SIZE)
		Touch_Pos.x=C_GLCD_H_SIZE-1;
	if(Touch_Pos.y>=C_GLCD_V_SIZE)
		Touch_Pos.y=C_GLCD_V_SIZE-1;
#endif	
	
}


void GetTouchKeyCode(void) //��ȡ ���䴥����ֵ
{
Touch_code=0,TouchLong_code=0;
volatile Int8U row_cou=0;
GetTouch_pos();	     //-----------------��� ��������λֵ-------------------------
if(WorkStart_flag==0)  //δ���빤��״̬
	{
	// // else if((Touch_Pos.y>=PUSH_RESET_OK_Y1)&&(Touch_Pos.y<=PUSH_RESET_OK_Y2))//��ֽ�� ��λ ��ʾ
		// // {
		// // if((Touch_Pos.x>=PUSH_RESET_OK_X1)&&(Touch_Pos.x<=PUSH_RESET_OK_X2))
			// // Touch_code=DOWN_KEY_CODE;   // ȷ��	
		// // else if((Touch_Pos.x>=PUSH_RESET_CANCEL_X1)&&(Touch_Pos.x<=PUSH_RESET_CANCEL_X2))
			// // Touch_code=SIX_KEY_CODE;		// clear ����C
		// // }
	switch(Board_TestMod)
		{
		case 0:// start
			if((Touch_Pos.y>=START_HELP_TOU_Y1)&&(Touch_Pos.y<=START_HELP_TOU_Y2))//
				{
				if((Touch_Pos.x>=START_HELP_TOU_X1)&&(Touch_Pos.x<=START_HELP_TOU_X2))
					{
					if(TouchCommLongdownExec_flag==1)	//20180913 touch longdown
						Touch_code=HELP_KEY_CODE;	//����----------
					}
					
				// else if((Touch_Pos.x>=START_F1_TOU_X1)&&(Touch_Pos.x<=START_F1_TOU_X2))
					// Touch_code=AUTO_KEY_CODE;       // F1
				}
			else if((Touch_Pos.y>=START_Y1)&&(Touch_Pos.y<=START_Y2))
				{
				if((Touch_Pos.x>=START_X1)&&(Touch_Pos.x<=START_X2))
					Touch_code=UP_KEY_CODE;   ///////////   //���� ����
				}
			// else if((Touch_Pos.y>=START_JOG_BACK_Y1)&&(Touch_Pos.y<=START_JOG_BACK_Y2))//------------Jog��ť
				// {
				// if(OutBack_limit==1)
					// {
					// if((Touch_Pos.x>=START_JOG_BACK_X1)&&(Touch_Pos.x<=START_JOG_BACK_X2))
						// Touch_code=ADJUST_KEY_CODE;    //���˰���
					// else if((Touch_Pos.x>=START_JOG_FORW_X1)&&(Touch_Pos.x<=START_JOG_FORW_X2))
						// Touch_code=NEXTKNIFE_KEY_CODE;  //ǰ������
					// }
				// }
				break;
		case TEST_HELP:	//help
			if((Touch_Pos.y>=START_HELP_TOU_Y1)&&(Touch_Pos.y<=START_HELP_TOU_Y2))//
				{
				if((Touch_Pos.x>=START_HELP_TOU_X1)&&(Touch_Pos.x<=START_HELP_TOU_X2))
					Touch_code=HELP_KEY_CODE;	//����----------
				else if((Touch_Pos.x>=START_F1_TOU_X1)&&(Touch_Pos.x<=START_F1_TOU_X2))
					Touch_code=AUTO_KEY_CODE;       // F1
				}
				//---------------
			if((Touch_Pos.x>=HELP_F1_X1)&&(Touch_Pos.x<=HELP_F1_X2))
				{
				if((Touch_Pos.y>=HELP_F1_Y1)&&(Touch_Pos.y<=HELP_F1_Y2))
					Touch_code=AUTO_KEY_CODE;       // F1
				/***201909
				else if((Touch_Pos.y>=HELP_F2_Y1)&&(Touch_Pos.y<=HELP_F2_Y2))
					Touch_code=READ_KEY_CODE;       // F2
				else if((Touch_Pos.y>=HELP_F3_Y1)&&(Touch_Pos.y<=HELP_F3_Y2))
					Touch_code=RETURN_KEY_CODE;     //F3
				else if((Touch_Pos.y>=HELP_F4_Y1)&&(Touch_Pos.y<=HELP_F4_Y2))
					Touch_code=MANUAL_KEY_CODE;   // F4
				else if((Touch_Pos.y>=HELP_F5_Y1)&&(Touch_Pos.y<=HELP_F5_Y2))
					Touch_code=F5_KEY_CODE;	//F5
				***/
				else if((Touch_Pos.y>=HELP_F2_Y1)&&(Touch_Pos.y<=HELP_F2_Y2))
					Touch_code=RETURN_KEY_CODE;       // F3    xxxREAD_KEY_CODE
				else if((Touch_Pos.y>=HELP_F3_Y1)&&(Touch_Pos.y<=HELP_F3_Y2))
					Touch_code=MANUAL_KEY_CODE;     //F4
				}
				break;
		case TEST_ICON:	//F2
			if((Touch_Pos.y>=START_HELP_TOU_Y1)&&(Touch_Pos.y<=START_HELP_TOU_Y2))//
				{
				if((Touch_Pos.x>=START_HELP_TOU_X1)&&(Touch_Pos.x<=START_HELP_TOU_X2))
					Touch_code=HELP_KEY_CODE;	//����----------
				}
			else if((Touch_Pos.y>=F2_PAGE_UP_Y1)&&(Touch_Pos.y<=F2_PAGE_UP_Y2))//
				{
				if((Touch_Pos.x>=F2_PAGE_UP_X1)&&(Touch_Pos.x<=F2_PAGE_UP_X2))
					Touch_code=PGUP_KEY_CODE;	//��ҳ
				else if((Touch_Pos.x>=F2_PAGE_DOWN_X1)&&(Touch_Pos.x<=F2_PAGE_DOWN_X2))
					Touch_code=PGDOWN_KEY_CODE;	//��ҳ
				else if((Touch_Pos.x>=F2_RET_HELP_X1)&&(Touch_Pos.x<=F2_RET_HELP_X2))
					Touch_code=READ_KEY_CODE;       // F2 ����
				}	
				break;
		case TEST_BOARD://���� ����ģʽ	F3	
			if((Touch_Pos.y>=START_HELP_TOU_Y1)&&(Touch_Pos.y<=START_HELP_TOU_Y2))//
				{
				if((Touch_Pos.x>=START_HELP_TOU_X1)&&(Touch_Pos.x<=START_HELP_TOU_X2))
					Touch_code=HELP_KEY_CODE;	//����----------
				}
				break;
		case TEST_SYS_WORD:	// F4	--password  sys ver��
			if((Touch_Pos.y>=START_HELP_TOU_Y1)&&(Touch_Pos.y<=START_HELP_TOU_Y2))//
				{
				if((Touch_Pos.x>=START_HELP_TOU_X1)&&(Touch_Pos.x<=START_HELP_TOU_X2))
					Touch_code=MANUAL_KEY_CODE;   // F4//HELP_KEY_CODE;	//����----------
				}
				//  ����  key  ------------
			else if((Touch_Pos.y>=KEY_BUTT_1_Y1)&&(Touch_Pos.y<=KEY_BUTT_1_Y2))
				{
				if((Touch_Pos.x>=KEY_BUTT_1_X1)&&(Touch_Pos.x<=KEY_BUTT_1_X2))//1
					Touch_code=NINE_KEY_CODE;		// 1
				else if((Touch_Pos.x>=KEY_BUTT_2_X1)&&(Touch_Pos.x<=KEY_BUTT_2_X2))//2
					Touch_code=MOVE_KEY_CODE;		// 2
				else if((Touch_Pos.x>=KEY_BUTT_3_X1)&&(Touch_Pos.x<=KEY_BUTT_3_X2))//3
					Touch_code=DELETE_KEY_CODE;      //3
				}
			else if((Touch_Pos.y>=KEY_BUTT_4_Y1)&&(Touch_Pos.y<=KEY_BUTT_4_Y2))
				{
				if((Touch_Pos.x>=KEY_BUTT_4_X1)&&(Touch_Pos.x<=KEY_BUTT_4_X2))//4
					Touch_code=EIGHT_KEY_CODE;		//4
				else if((Touch_Pos.x>=KEY_BUTT_5_X1)&&(Touch_Pos.x<=KEY_BUTT_5_X2))//5
					Touch_code=NO_KEY_CODE;      // 5
				else if((Touch_Pos.x>=KEY_BUTT_6_X1)&&(Touch_Pos.x<=KEY_BUTT_6_X2))//6
					Touch_code=INSERT_KEY_CODE;      //6
				}
			else if((Touch_Pos.y>=KEY_BUTT_7_Y1)&&(Touch_Pos.y<=KEY_BUTT_7_Y2))
				{
				if((Touch_Pos.x>=KEY_BUTT_7_X1)&&(Touch_Pos.x<=KEY_BUTT_7_X2))//7
					Touch_code=SEVEN_KEY_CODE;	//7
				else if((Touch_Pos.x>=KEY_BUTT_8_X1)&&(Touch_Pos.x<=KEY_BUTT_8_X2))//8
					Touch_code=YES_KEY_CODE;    // 8
				else if((Touch_Pos.x>=KEY_BUTT_9_X1)&&(Touch_Pos.x<=KEY_BUTT_9_X2))//9
					Touch_code=SUB_KEY_CODE;   // 9
				}
			else if((Touch_Pos.y>=KEY_BUTT_C_Y1)&&(Touch_Pos.y<=KEY_BUTT_C_Y2))
				{
				if((Touch_Pos.x>=KEY_BUTT_C_X1)&&(Touch_Pos.x<=KEY_BUTT_C_X2))//C
					Touch_code=SIX_KEY_CODE;		// clear ����C
				else if((Touch_Pos.x>=KEY_BUTT_8_X1)&&(Touch_Pos.x<=KEY_BUTT_8_X2))//0
					Touch_code=PROG_KEY_CODE;     // 0
				else if((Touch_Pos.x>=KEY_BUTT_9_X1)&&(Touch_Pos.x<=KEY_BUTT_9_X2))//ok
					Touch_code=DOWN_KEY_CODE;   // ȷ��	
				}
				break;
		case TEST_SYS_TYPE://���� ����ϵͳѡ��
		case TEST_PAGE_LINE://ÿҳ���� ѡ��
			if((Touch_Pos.y>=START_HELP_TOU_Y1)&&(Touch_Pos.y<=START_HELP_TOU_Y2))//
				{
				if((Touch_Pos.x>=START_HELP_TOU_X1)&&(Touch_Pos.x<=START_HELP_TOU_X2))
					Touch_code=F5_KEY_CODE;   // F5 ����----------
				}
			else 
				{
				if((Touch_Pos.x>=VER_SEL_UP_X1)&&(Touch_Pos.x<=VER_SEL_UP_X2))//	
					{
					if((Touch_Pos.y>=VER_SEL_UP_Y1)&&(Touch_Pos.y<=VER_SEL_UP_Y2))
						Touch_code=DENGJU_KEY_CODE;  //���ϼ�ͷ����
					else if((Touch_Pos.y>=VER_SEL_DOWN_Y1)&&(Touch_Pos.y<=VER_SEL_DOWN_Y2))
						Touch_code=DENGFENG_KEY_CODE; //���¼�ͷ
					}
				}
				break;
		}
	
	}
else
	{
	
	if(Touch_code==0)
		{		
		if((Touch_Pos.y>=AUTO_MOD_TOU_Y1)&&(Touch_Pos.y<=AUTO_MOD_TOU_Y2))  //��ģʽ
			{
			if((Touch_Pos.x>=AUTO_MOD_TOU_X1)&&(Touch_Pos.x<=AUTO_MOD_TOU_X2))
				Touch_code=THREE_KEY_CODE;	//�Զ�mode
			else if((Touch_Pos.x>=MANUAL_MOD_TOU_X1)&&(Touch_Pos.x<=MANUAL_MOD_TOU_X2))
				Touch_code=TWO_KEY_CODE;	//�ֶ�mode
			else if((Touch_Pos.x>=TEACH_MOD_TOU_X1)&&(Touch_Pos.x<=TEACH_MOD_TOU_X2))
				Touch_code=TEACH_TOUCH_CODE;//ʾ��mode
			else if((Touch_Pos.x>=AUTOCUT_MOD_TOU_X1)&&(Touch_Pos.x<=AUTOCUT_MOD_TOU_X2))
				Touch_code=AUTOCUT_TOUCH_CODE;//�Ե�mode	
			// else if((Touch_Pos.x>=FIND_MOD_TOU_X1)&&(Touch_Pos.x<=FIND_MOD_TOU_X2))
				// Touch_code=PROC_KEY_CODE;   //���� ѡ��		(����ģʽ)
			}
		if(Touch_code==0)
			{
			switch(WorkMode)
				{	
				case AUTO_MODE://�Զ���������
				case TEACH_MODE://ʾ�� ģʽ
				case SELF_CUT_MODE:  //�Ե��� ģʽ
				case AUTO_BATCH_MODE://�Զ�F5++--	
				case TEACH_BATCH_MODE:  //
				// case AUTO_PLUS_MODE://�Զ�F3++
				// case AUTO_MINUS_MODE://�Զ�F4--
				// case TEACH_PLUS_MODE: //�Ե� F3++
				// case TEACH_MINUS_MODE://�Ե� F4--
					if(Touch_Pos.y>RUN_BUTTON_Y1)
						{
						if((Touch_Pos.y>=BACK_BUTT_Y1)&&(Touch_Pos.y<=BACK_BUTT_Y2))
							{
							if((Touch_Pos.x>=BACK_BUTT_X1)&&(Touch_Pos.x<=BACK_BUTT_X2))
								Touch_code=ADJUST_KEY_CODE;    //���˰���
							else if((Touch_Pos.x>=FWD_BUTT_X1)&&(Touch_Pos.x<=FWD_BUTT_X2))
								Touch_code=NEXTKNIFE_KEY_CODE;  //ǰ������
							else if((Touch_Pos.x>=FAST_BACK_BUTT_X1)&&(Touch_Pos.x<=FAST_BACK_BUTT_X2))
								Touch_code=FAST_BACK_KEY_CODE;     //����-----------------------....
							else if((Touch_Pos.x>=FAST_FWD_BUTT_X1)&&(Touch_Pos.x<=FAST_FWD_BUTT_X2))
								Touch_code=FAST_AHEAD_KEY_CODE;   //���-----
							//**************shortcut--------------
							else if((Touch_Pos.x>=FIND_MOD_TOU_X1)&&(Touch_Pos.x<=FIND_MOD_TOU_X2))
								Touch_code=FIND_TOUCH_CODE;    // ����
							else if((Touch_Pos.x>=PARAMETER_TOU_X1)&&(Touch_Pos.x<=PARAMETER_TOU_X2))
								Touch_code=PATAMETER_TOUCH_CODE;    // ����
							else if((Touch_Pos.x>=IO_TEST_TOU_X1)&&(Touch_Pos.x<=IO_TEST_TOU_X2))
								Touch_code=IO_TEST_TOUCH_CODE;    // IO
							// else if((Touch_Pos.x>=DELETE_ALL_X1)&&(Touch_Pos.x<=DELETE_ALL_X2))
								// Touch_code=FIVE_KEY_CODE;   //ɾ��
							// else if((Touch_Pos.x>=S6_AMEND_BUTT_X1)&&(Touch_Pos.x<=S6_AMEND_BUTT_X2))
								// Touch_code=SHIFT_6_KEY_CODE;	//shift+6------ �޸�����ƫ����
							}
						else if((Touch_Pos.y>=RUN_BUTTON_Y1)&&(Touch_Pos.y<=RUN_BUTTON_Y2))
							{
							if((Touch_Pos.x>=RUN_BUTTON_X1)&&(Touch_Pos.x<=RUN_BUTTON_X2))
							{}//Touch_code=UP_KEY_CODE;   ///////////���а���
							else if((Touch_Pos.x>=STOP_BUTTON_X1)&&(Touch_Pos.x<=STOP_BUTTON_X2))
								Touch_code=STOP_KEY_CODE; //ֹͣ ������
							}
						}
					else
						{
						if((Touch_Pos.x>=F1_BUTTON_X1)&&(Touch_Pos.x<=F1_BUTTON_X2))  //F1,2,3,4��ģʽ
							{
							if((Touch_Pos.y>=F1_BUTTON_Y1)&&(Touch_Pos.y<=F1_BUTTON_Y2))
								Touch_code=AUTO_KEY_CODE;       // F1*******
							else if((Touch_Pos.y>=F2_BUTTON_Y1)&&(Touch_Pos.y<=F2_BUTTON_Y2))
								Touch_code=READ_KEY_CODE;       // F2******
							else if((Touch_Pos.y>=F3_BUTTON_Y1)&&(Touch_Pos.y<=F3_BUTTON_Y2))
								Touch_code=RETURN_KEY_CODE;       // F3******
							else if((Touch_Pos.y>=F4_BUTTON_Y1)&&(Touch_Pos.y<=F4_BUTTON_Y2))
								Touch_code=MANUAL_KEY_CODE;       // F4******switch	
							else if((Touch_Pos.y>=F5_BUTTON_Y1)&&(Touch_Pos.y<=F5_BUTTON_Y2))
								Touch_code=F5_KEY_CODE;		//F5
							else if((Touch_Pos.y>=F6_BUTTON_Y1)&&(Touch_Pos.y<=F6_BUTTON_Y2))
								Touch_code=F6_KEY_CODE;		//F6	
							}
						else if((Touch_Pos.x>=CALC_ONE_X1)&&(Touch_Pos.x<=CALC_PLUS_X2))//-----------������
							{	
							if((Touch_Pos.y>=CALC_ONE_Y1)&&(Touch_Pos.y<=CALC_ONE_Y2)) //row1
								{
								if((Touch_Pos.x>=CALC_ONE_X1)&&(Touch_Pos.x<=CALC_ONE_X2))
									{
									Touch_code=NINE_KEY_CODE;		// 1
									}
								else if((Touch_Pos.x>=CALC_TWO_X1)&&(Touch_Pos.x<=CALC_TWO_X2))
									{
									Touch_code=MOVE_KEY_CODE;		// 2
									}
								else if((Touch_Pos.x>=CALC_THREE_X1)&&(Touch_Pos.x<=CALC_THREE_X2))
									{
									Touch_code=DELETE_KEY_CODE;      //3
									}
								else if((Touch_Pos.x>=CALC_PLUS_X1)&&(Touch_Pos.x<=CALC_PLUS_X2))
									{
									Touch_code=REV_KEY_CODE;   //  +
									}	
								}
							else if((Touch_Pos.y>=CALC_FOUR_Y1)&&(Touch_Pos.y<=CALC_FOUR_Y2))  //row2
								{
								if((Touch_Pos.x>=CALC_FOUR_X1)&&(Touch_Pos.x<=CALC_FOUR_X2))
									{
									Touch_code=EIGHT_KEY_CODE;		//4
									}
								else if((Touch_Pos.x>=CALC_FIVE_X1)&&(Touch_Pos.x<=CALC_FIVE_X2))	
									{
									Touch_code=NO_KEY_CODE;      // 5
									}
								else if((Touch_Pos.x>=CALC_SIX_X1)&&(Touch_Pos.x<=CALC_SIX_X2))	
									{
									Touch_code=INSERT_KEY_CODE;      //6
									}
								else if((Touch_Pos.x>=CALC_SUB_X1)&&(Touch_Pos.x<=CALC_SUB_X2))	
									{
									Touch_code=OPTION_KEY_CODE;    //����  -
									}
								}
							else if((Touch_Pos.y>=CALC_SEVEN_Y1)&&(Touch_Pos.y<=CALC_SEVEN_Y2))  //row3
								{
								if((Touch_Pos.x>=CALC_SEVEN_X1)&&(Touch_Pos.x<=CALC_SEVEN_X2))
									{
									Touch_code=SEVEN_KEY_CODE;	//7
									}
								else if((Touch_Pos.x>=CALC_EIGHT_X1)&&(Touch_Pos.x<=CALC_EIGHT_X2))	
									{
									Touch_code=YES_KEY_CODE;    // 8
									}
								else if((Touch_Pos.x>=CALC_NINE_X1)&&(Touch_Pos.x<=CALC_NINE_X2))	
									{
									Touch_code=SUB_KEY_CODE;   // 9
									}
								else if((Touch_Pos.x>=CALC_MUL_X1)&&(Touch_Pos.x<=CALC_MUL_X2))	
									{
									Touch_code=MUL_TOUCH_CODE;  // *
									}
								}	
							else if((Touch_Pos.y>=CALC_C_Y1)&&(Touch_Pos.y<=CALC_C_Y2))  //row4
								{
								if((Touch_Pos.x>=CALC_C_X1)&&(Touch_Pos.x<=CALC_C_X2))
									{
									Touch_code=SIX_KEY_CODE;		// clear ����C
									}
								else if((Touch_Pos.x>=CALC_ZERO_X1)&&(Touch_Pos.x<=CALC_ZERO_X2))	
									{
									if(ShiftKey_flag==1)
										Touch_code=SHIFT_0_KEY_CODE;//shift+0
									else	
										Touch_code=PROG_KEY_CODE;     // 0  **********
									}
								else if((Touch_Pos.x>=CALC_DOT_X1)&&(Touch_Pos.x<=CALC_DOT_X2))	
									{
									Touch_code=ADD_KEY_CODE;   //  �㡰.��
									}
								else if((Touch_Pos.x>=CALC_DIV_X1)&&(Touch_Pos.x<=CALC_DIV_X2))	
									{
									Touch_code=DIV_TOUCH_CODE;  // �� /
									}
								}
							else if((Touch_Pos.y>=CALC_EQU_Y1)&&(Touch_Pos.y<=CALC_EQU_Y2))  //row5
								{
								if((Touch_Pos.x>=CALC_EQU_X1)&&(Touch_Pos.x<=CALC_EQU_X2))	
									{
									Touch_code=EQU_TOUCH_CODE;  //==
									}
								else if((Touch_Pos.x>=CALC_ENTER_X1)&&(Touch_Pos.x<=CALC_ENTER_X2))	
									{
									Touch_code=DOWN_KEY_CODE;   // ȷ��	
									// if(WorkMode==MANUAL_MODE)// �ֶ� ģʽ
										// Touch_code=UP_KEY_CODE;   ///////////����
									}	
								}
							}
						else if((Touch_Pos.x>=MAIN_UP_BUTTON_X1)&&(Touch_Pos.x<=MAIN_UP_BUTTON_X2)) //���� ��ͷ
							{
							if((Touch_Pos.y>=MAIN_UP_BUTTON_Y1)&&(Touch_Pos.y<=MAIN_UP_BUTTON_Y2))
								Touch_code=DENGJU_KEY_CODE;  //���ϼ�ͷ
							else if((Touch_Pos.y>=MAIN_DOWN_BUTTON_Y1)&&(Touch_Pos.y<=MAIN_DOWN_BUTTON_Y2))
								Touch_code=DENGFENG_KEY_CODE;  //���¼�ͷ
							else if((Touch_Pos.y>=PAGE_UP_BUTTON_Y1)&&(Touch_Pos.y<=PAGE_UP_BUTTON_Y2))
								Touch_code=PGUP_KEY_CODE;	//��ҳ
							else if((Touch_Pos.y>=PAGE_DOWN_BUTTON_Y1)&&(Touch_Pos.y<=PAGE_DOWN_BUTTON_Y2))
								Touch_code=PGDOWN_KEY_CODE;	//��ҳ
							}
						else		
							{
							if(WorkMode==AUTO_MODE)//�Զ�������  -------flags
								{
								if((Touch_Pos.x>=LINE_SEL_BASE_BUTT_X1)&&(Touch_Pos.x<=LINE_SEL_BASE_BUTT_X2))//�д���
									{
									FlagTouRow_num=0;
									row_cou=0;
									while(row_cou<PageKf_Size)	
										{
										if((Touch_Pos.y>(LINE_SEL_BASE_BUTT_Y1+(row_cou*Kf_Line_HIGH)))
										&&(Touch_Pos.y<(LINE_SEL_BASE_BUTT_Y2+(row_cou*Kf_Line_HIGH))))
											{
											if((Touch_Pos.x>=AIR_FLAG_BUTT_X1)&&(Touch_Pos.x<=AIR_FLAG_BUTT_X2))		//	�����Ǵ�--------1	
												{
												Touch_code=	SHIFT_0_KEY_CODE;	//shift+0------ ������
												}
											else if((Touch_Pos.x>=OTHER_FLAG_BUTT_X1)&&(Touch_Pos.x<=OTHER_FLAG_BUTT_X2))// �������-------2
												{
												Touch_code=	SHIFT_8_KEY_CODE;	//shift+8------�������
												}
											else
												{
												Touch_code=	LINE_SEL_KEY_CODE;	//������ѡ��
												}
											FlagTouRow_num=row_cou+1;
											}
										row_cou++;
										}	
									}
								}
							}
							
						}
						break;
				case AUTO_FLAG_MODE:	//�������wind ģʽ+++++++++++++++++++201903
					if((Touch_Pos.x>=PUSH_FLAG_BUTT_X1)&&(Touch_Pos.x<=PUSH_FLAG_BUTT_X2))
						{
						if((Touch_Pos.y>=PUSH_FLAG_BUTT_Y1)&&(Touch_Pos.y<=PUSH_FLAG_BUTT_Y2))	
							{
							Touch_code=	SHIFT_1_KEY_CODE;	//shift+1------��ֽ���
							}
						else if((Touch_Pos.y>=SORT_FLAG_BUTT_Y1)&&(Touch_Pos.y<=SORT_FLAG_BUTT_Y2))	
							{
							Touch_code=	SHIFT_2_KEY_CODE;	//shift+2------��ֽ���
							}
						else if((Touch_Pos.y>=PRESS_FLAG_BUTT_Y1)&&(Touch_Pos.y<=PRESS_FLAG_BUTT_Y2))	
							{
							Touch_code=	SHIFT_3_KEY_CODE;	//shift+3------ѹֽ���
							}
						else if((Touch_Pos.y>=KNIFE_FLAG_BUTT_Y1)&&(Touch_Pos.y<=KNIFE_FLAG_BUTT_Y2))	
							{
							Touch_code=	SHIFT_4_KEY_CODE;	//shift+4------�����
							}
						else if((Touch_Pos.y>=KNIFES_FLAG_BUTT_Y1)&&(Touch_Pos.y<=KNIFES_FLAG_BUTT_Y2))	
							{
							Touch_code=	SHIFT_5_KEY_CODE;	//shift+5------�൶���
							}
						else if((Touch_Pos.y>=CLR_FLG_BUTT_Y1)&&(Touch_Pos.y<=CLR_FLG_BUTT_Y2))	
							{
							Touch_code=	SHIFT_6_KEY_CODE;	//shift+6------������
							}
						else if((Touch_Pos.y>=EXIT_FLAG_BUTT_Y1)&&(Touch_Pos.y<=EXIT_FLAG_BUTT_Y2))	
							{
							Touch_code=	READ_KEY_CODE;       // F2******
							}
						}
						break;	
				case MANUAL_MODE:// �ֶ� ģʽ
					if(Touch_Pos.y>RUN_BUTTON_Y1)
						{
						if((Touch_Pos.y>=BACK_BUTT_Y1)&&(Touch_Pos.y<=BACK_BUTT_Y2))
							{
							if((Touch_Pos.x>=BACK_BUTT_X1)&&(Touch_Pos.x<=BACK_BUTT_X2))
								Touch_code=ADJUST_KEY_CODE;    //���˰���
							else if((Touch_Pos.x>=FWD_BUTT_X1)&&(Touch_Pos.x<=FWD_BUTT_X2))
								Touch_code=NEXTKNIFE_KEY_CODE;  //ǰ������
							else if((Touch_Pos.x>=FAST_BACK_BUTT_X1)&&(Touch_Pos.x<=FAST_BACK_BUTT_X2))
								Touch_code=FAST_BACK_KEY_CODE;     //����-----------------------....
							else if((Touch_Pos.x>=FAST_FWD_BUTT_X1)&&(Touch_Pos.x<=FAST_FWD_BUTT_X2))
								Touch_code=FAST_AHEAD_KEY_CODE;   //���-----
							//**************shortcut--------------
							else if((Touch_Pos.x>=FIND_MOD_TOU_X1)&&(Touch_Pos.x<=FIND_MOD_TOU_X2))
								Touch_code=FIND_TOUCH_CODE;    // ����
							else if((Touch_Pos.x>=PARAMETER_TOU_X1)&&(Touch_Pos.x<=PARAMETER_TOU_X2))
								Touch_code=PATAMETER_TOUCH_CODE;    // ����
							else if((Touch_Pos.x>=IO_TEST_TOU_X1)&&(Touch_Pos.x<=IO_TEST_TOU_X2))
								Touch_code=IO_TEST_TOUCH_CODE;    // IO
							}
						else if((Touch_Pos.y>=RUN_BUTTON_Y1)&&(Touch_Pos.y<=RUN_BUTTON_Y2))
							{
							if((Touch_Pos.x>=RUN_BUTTON_X1)&&(Touch_Pos.x<=RUN_BUTTON_X2))
								{}// Touch_code=UP_KEY_CODE;   ///////////���а���
							else if((Touch_Pos.x>=STOP_BUTTON_X1)&&(Touch_Pos.x<=STOP_BUTTON_X2))
								Touch_code=STOP_KEY_CODE; //ֹͣ ������
							}
						}
					else
						{
						if((Touch_Pos.x>=F1_BUTTON_X1)&&(Touch_Pos.x<=F1_BUTTON_X2))  //F1,2,3,4��ģʽ
							{
							if((Touch_Pos.y>=F1_BUTTON_Y1)&&(Touch_Pos.y<=F1_BUTTON_Y2))
								Touch_code=AUTO_KEY_CODE;       // F1*******
							else if((Touch_Pos.y>=F2_BUTTON_Y1)&&(Touch_Pos.y<=F2_BUTTON_Y2))
								Touch_code=READ_KEY_CODE;       // F2******
							else if((Touch_Pos.y>=F3_BUTTON_Y1)&&(Touch_Pos.y<=F3_BUTTON_Y2))
								Touch_code=RETURN_KEY_CODE;       // F3******
							else if((Touch_Pos.y>=F4_BUTTON_Y1)&&(Touch_Pos.y<=F4_BUTTON_Y2))
								Touch_code=MANUAL_KEY_CODE;       // F4******
							else if((Touch_Pos.y>=F5_BUTTON_Y1)&&(Touch_Pos.y<=F5_BUTTON_Y2))
								Touch_code=SHIFT_8_KEY_CODE;	//F5_KEY_CODE;		//F5 20191209
							else if((Touch_Pos.y>=F6_BUTTON_Y1)&&(Touch_Pos.y<=F6_BUTTON_Y2))
								Touch_code=F6_KEY_CODE;		//F6	
							}
						else if((Touch_Pos.x>=CALC_ONE_X1)&&(Touch_Pos.x<=CALC_PLUS_X2))//-----------������
							{	
							if((Touch_Pos.y>=CALC_ONE_Y1)&&(Touch_Pos.y<=CALC_ONE_Y2)) //row1
								{
								if((Touch_Pos.x>=CALC_ONE_X1)&&(Touch_Pos.x<=CALC_ONE_X2))
									{
									Touch_code=NINE_KEY_CODE;		// 1
									}
								else if((Touch_Pos.x>=CALC_TWO_X1)&&(Touch_Pos.x<=CALC_TWO_X2))
									{
									Touch_code=MOVE_KEY_CODE;		// 2
									}
								else if((Touch_Pos.x>=CALC_THREE_X1)&&(Touch_Pos.x<=CALC_THREE_X2))
									{
									Touch_code=DELETE_KEY_CODE;      //3
									}
								else if((Touch_Pos.x>=CALC_PLUS_X1)&&(Touch_Pos.x<=CALC_PLUS_X2))
									{
									Touch_code=REV_KEY_CODE;   //  +
									}	
								}
							else if((Touch_Pos.y>=CALC_FOUR_Y1)&&(Touch_Pos.y<=CALC_FOUR_Y2))  //row2
								{
								if((Touch_Pos.x>=CALC_FOUR_X1)&&(Touch_Pos.x<=CALC_FOUR_X2))
									{
									Touch_code=EIGHT_KEY_CODE;		//4
									}
								else if((Touch_Pos.x>=CALC_FIVE_X1)&&(Touch_Pos.x<=CALC_FIVE_X2))	
									{
									Touch_code=NO_KEY_CODE;      // 5
									}
								else if((Touch_Pos.x>=CALC_SIX_X1)&&(Touch_Pos.x<=CALC_SIX_X2))	
									{
									Touch_code=INSERT_KEY_CODE;      //6
									}
								else if((Touch_Pos.x>=CALC_SUB_X1)&&(Touch_Pos.x<=CALC_SUB_X2))	
									{
									Touch_code=OPTION_KEY_CODE;    //����  -
									}
								}
							else if((Touch_Pos.y>=CALC_SEVEN_Y1)&&(Touch_Pos.y<=CALC_SEVEN_Y2))  //row3
								{
								if((Touch_Pos.x>=CALC_SEVEN_X1)&&(Touch_Pos.x<=CALC_SEVEN_X2))
									{
									Touch_code=SEVEN_KEY_CODE;	//7
									}
								else if((Touch_Pos.x>=CALC_EIGHT_X1)&&(Touch_Pos.x<=CALC_EIGHT_X2))	
									{
									Touch_code=YES_KEY_CODE;    // 8
									}
								else if((Touch_Pos.x>=CALC_NINE_X1)&&(Touch_Pos.x<=CALC_NINE_X2))	
									{
									Touch_code=SUB_KEY_CODE;   // 9
									}
								else if((Touch_Pos.x>=CALC_MUL_X1)&&(Touch_Pos.x<=CALC_MUL_X2))	
									{
									Touch_code=MUL_TOUCH_CODE;  // *
									}
								}	
							else if((Touch_Pos.y>=CALC_C_Y1)&&(Touch_Pos.y<=CALC_C_Y2))  //row4
								{
								if((Touch_Pos.x>=CALC_C_X1)&&(Touch_Pos.x<=CALC_C_X2))
									{
									Touch_code=SIX_KEY_CODE;		// clear ����C
									}
								else if((Touch_Pos.x>=CALC_ZERO_X1)&&(Touch_Pos.x<=CALC_ZERO_X2))	
									{
									if(ShiftKey_flag==1)
										Touch_code=SHIFT_0_KEY_CODE;//shift+0
									else	
										Touch_code=PROG_KEY_CODE;     // 0  **********
									}
								else if((Touch_Pos.x>=CALC_DOT_X1)&&(Touch_Pos.x<=CALC_DOT_X2))	
									{
									Touch_code=ADD_KEY_CODE;   //  �㡰.��
									}
								else if((Touch_Pos.x>=CALC_DIV_X1)&&(Touch_Pos.x<=CALC_DIV_X2))	
									{
									Touch_code=DIV_TOUCH_CODE;  // �� /
									}
								}
							else if((Touch_Pos.y>=CALC_EQU_Y1)&&(Touch_Pos.y<=CALC_EQU_Y2))  //row5
								{
								if((Touch_Pos.x>=CALC_EQU_X1)&&(Touch_Pos.x<=CALC_EQU_X2))	
									{
									Touch_code=EQU_TOUCH_CODE;  //==
									}
								else if((Touch_Pos.x>=CALC_ENTER_X1)&&(Touch_Pos.x<=CALC_ENTER_X2))	
									{
									Touch_code=DOWN_KEY_CODE;   // ȷ��	
									// if(WorkMode==MANUAL_MODE)// �ֶ� ģʽ
										// Touch_code=UP_KEY_CODE;   ///////////����
									}	
								}
							}
						else if((Touch_Pos.x>=STEP_MOV_BUTT_X1)&&(Touch_Pos.x<=STEP_MOV_BUTT_X2))//ƫ��������
							{
							if((Touch_Pos.y>=STEP_MOV_BUTT_Y1)&&(Touch_Pos.y<=STEP_MOV_BUTT_Y2))
									{
									Touch_code=DENGFENG_KEY_CODE;  //���¼�ͷ		//F5
									}
							}
						}
						break;
				// case READ_PRO_MODE:		//����ģʽ......����ѡ��
				case AUTO_FIND_MODE://
				case MANUAL_FIND_MODE://
				case TEACH_FIND_MODE://
				case SELF_FIND_MODE://
					if(Touch_Pos.y<=RUN_BUTTON_Y1)
						{
						if((Touch_Pos.x>=F1_BUTTON_X1)&&(Touch_Pos.x<=F1_BUTTON_X2))  //F1,2,3,4��ģʽ
							{
							if((Touch_Pos.y>=F1_BUTTON_Y1)&&(Touch_Pos.y<=F1_BUTTON_Y2))
								Touch_code=AUTO_KEY_CODE;       // F1*******
							else if((Touch_Pos.y>=F2_BUTTON_Y1)&&(Touch_Pos.y<=F2_BUTTON_Y2))
								Touch_code=READ_KEY_CODE;       // F2******
							else if((Touch_Pos.y>=F3_BUTTON_Y1)&&(Touch_Pos.y<=F3_BUTTON_Y2))
								Touch_code=RETURN_KEY_CODE;       // F3******
							else if((Touch_Pos.y>=F4_BUTTON_Y1)&&(Touch_Pos.y<=F4_BUTTON_Y2))
								Touch_code=MANUAL_KEY_CODE;       // F4******
							else if((Touch_Pos.y>=F5_BUTTON_Y1)&&(Touch_Pos.y<=F5_BUTTON_Y2))
								Touch_code=F5_KEY_CODE;		//F5
							else if((Touch_Pos.y>=F6_BUTTON_Y1)&&(Touch_Pos.y<=F6_BUTTON_Y2))
								Touch_code=F6_KEY_CODE;		//F6	
							}
						else if((Touch_Pos.x>=CALC_ONE_X1)&&(Touch_Pos.x<=CALC_PLUS_X2))//-----------������
							{	
							if((Touch_Pos.y>=CALC_ONE_Y1)&&(Touch_Pos.y<=CALC_ONE_Y2)) //row1
								{
								if((Touch_Pos.x>=CALC_ONE_X1)&&(Touch_Pos.x<=CALC_ONE_X2))
									{
									Touch_code=NINE_KEY_CODE;		// 1
									}
								else if((Touch_Pos.x>=CALC_TWO_X1)&&(Touch_Pos.x<=CALC_TWO_X2))
									{
									Touch_code=MOVE_KEY_CODE;		// 2
									}
								else if((Touch_Pos.x>=CALC_THREE_X1)&&(Touch_Pos.x<=CALC_THREE_X2))
									{
									Touch_code=DELETE_KEY_CODE;      //3
									}
								else if((Touch_Pos.x>=CALC_PLUS_X1)&&(Touch_Pos.x<=CALC_PLUS_X2))
									{
									Touch_code=REV_KEY_CODE;   //  +
									}	
								}
							else if((Touch_Pos.y>=CALC_FOUR_Y1)&&(Touch_Pos.y<=CALC_FOUR_Y2))  //row2
								{
								if((Touch_Pos.x>=CALC_FOUR_X1)&&(Touch_Pos.x<=CALC_FOUR_X2))
									{
									Touch_code=EIGHT_KEY_CODE;		//4
									}
								else if((Touch_Pos.x>=CALC_FIVE_X1)&&(Touch_Pos.x<=CALC_FIVE_X2))	
									{
									Touch_code=NO_KEY_CODE;      // 5
									}
								else if((Touch_Pos.x>=CALC_SIX_X1)&&(Touch_Pos.x<=CALC_SIX_X2))	
									{
									Touch_code=INSERT_KEY_CODE;      //6
									}
								else if((Touch_Pos.x>=CALC_SUB_X1)&&(Touch_Pos.x<=CALC_SUB_X2))	
									{
									Touch_code=OPTION_KEY_CODE;    //����  -
									}
								}
							else if((Touch_Pos.y>=CALC_SEVEN_Y1)&&(Touch_Pos.y<=CALC_SEVEN_Y2))  //row3
								{
								if((Touch_Pos.x>=CALC_SEVEN_X1)&&(Touch_Pos.x<=CALC_SEVEN_X2))
									{
									Touch_code=SEVEN_KEY_CODE;	//7
									}
								else if((Touch_Pos.x>=CALC_EIGHT_X1)&&(Touch_Pos.x<=CALC_EIGHT_X2))	
									{
									Touch_code=YES_KEY_CODE;    // 8
									}
								else if((Touch_Pos.x>=CALC_NINE_X1)&&(Touch_Pos.x<=CALC_NINE_X2))	
									{
									Touch_code=SUB_KEY_CODE;   // 9
									}
								else if((Touch_Pos.x>=CALC_MUL_X1)&&(Touch_Pos.x<=CALC_MUL_X2))	
									{
									Touch_code=MUL_TOUCH_CODE;  // *
									}
								}	
							else if((Touch_Pos.y>=CALC_C_Y1)&&(Touch_Pos.y<=CALC_C_Y2))  //row4
								{
								if((Touch_Pos.x>=CALC_C_X1)&&(Touch_Pos.x<=CALC_C_X2))
									{
									Touch_code=SIX_KEY_CODE;		// clear ����C
									}
								else if((Touch_Pos.x>=CALC_ZERO_X1)&&(Touch_Pos.x<=CALC_ZERO_X2))	
									{
									if(ShiftKey_flag==1)
										Touch_code=SHIFT_0_KEY_CODE;//shift+0
									else	
										Touch_code=PROG_KEY_CODE;     // 0  **********
									}
								else if((Touch_Pos.x>=CALC_DOT_X1)&&(Touch_Pos.x<=CALC_DOT_X2))	
									{
									Touch_code=ADD_KEY_CODE;   //  �㡰.��
									}
								else if((Touch_Pos.x>=CALC_DIV_X1)&&(Touch_Pos.x<=CALC_DIV_X2))	
									{
									Touch_code=DIV_TOUCH_CODE;  // �� /
									}
								}
							else if((Touch_Pos.y>=CALC_EQU_Y1)&&(Touch_Pos.y<=CALC_EQU_Y2))  //row5
								{
								if((Touch_Pos.x>=CALC_EQU_X1)&&(Touch_Pos.x<=CALC_EQU_X2))	
									{
									Touch_code=EQU_TOUCH_CODE;  //==
									}
								else if((Touch_Pos.x>=CALC_ENTER_X1)&&(Touch_Pos.x<=CALC_ENTER_X2))	
									{
									Touch_code=DOWN_KEY_CODE;   // ȷ��	
									// if(WorkMode==MANUAL_MODE)// �ֶ� ģʽ
										// Touch_code=UP_KEY_CODE;   ///////////����
									}	
								}
							}
						//else if((Touch_Pos.x>=PRO_UP_TO_X1)&&(Touch_Pos.x<=ENTER_OK_BUTT_X2))  //up,down ,ok
						else if((Touch_Pos.x>=PRO_NUM_TABLE_X1)&&(Touch_Pos.x<=PRO_NUM_TABLE_X2 ))//middle table
							{
							if((Touch_Pos.y>=PRO_UP_TO_Y1)&&(Touch_Pos.y<=PRO_UP_TO_Y2))
								{
								if((Touch_Pos.x>=PRO_UP_TO_X1)&&(Touch_Pos.x<=PRO_UP_TO_X2))
									// Touch_code=DENGJU_KEY_CODE;  //���ϼ�ͷ
									Touch_code=PGUP_KEY_CODE;	//��ҳ
								else if((Touch_Pos.x>=PRO_DOWN_TO_X1)&&(Touch_Pos.x<=PRO_DOWN_TO_X2))
									// Touch_code=DENGFENG_KEY_CODE;  //���¼�ͷ
									Touch_code=PGDOWN_KEY_CODE;	//��ҳ
								else if((Touch_Pos.x>=ENTER_OK_BUTT_X1)&&(Touch_Pos.x<=ENTER_OK_BUTT_X2))
									Touch_code=DOWN_KEY_CODE;   // ȷ��
								}
							else 
								{
								TouchLnie_num=0;
								row_cou=0;
								while(row_cou<PROGS_1PAGE)	
									{
									if((Touch_Pos.y>(PRO_NUM_TABLE_Y1+(row_cou*PROTEXT_HIGH)))
									&&(Touch_Pos.y<(PRO_NUM_TABLE_Y2+(row_cou*PROTEXT_HIGH))))
										{
										Touch_code=	LINE_SEL_KEY_CODE;	//������ѡ��
										TouchLnie_num=row_cou+1;
										}
									row_cou++;
									}
								}
							}
						}
						break;
				case AUTO_TO_SELF_MODE:   //�Զ�-->�Ե����� ģʽ
					if((Touch_Pos.y>=SELF_OK_Y1)&&(Touch_Pos.y<=SELF_OK_Y2))
						{
						if((Touch_Pos.x>=SELF_OK_X1)&&(Touch_Pos.x<=SELF_OK_X2))
							Touch_code=DOWN_KEY_CODE;   // ȷ��
						else if((Touch_Pos.x>=SELF_CANCEL_X1)&&(Touch_Pos.x<=SELF_CANCEL_X2))	
							Touch_code=SIX_KEY_CODE;	// clear ����  ȡ��
						}	
						break;
				case AUTO_LABEL_MODE: //��ǩ
				case TEACH_LABEL_MODE://ʾ�� ��ǩ
					if(Touch_Pos.y<=RUN_BUTTON_Y1)
						{
						if((Touch_Pos.x>=F1_BUTTON_X1)&&(Touch_Pos.x<=F1_BUTTON_X2))  //F1,2,3,4��ģʽ
							{
							if((Touch_Pos.y>=F1_BUTTON_Y1)&&(Touch_Pos.y<=F1_BUTTON_Y2))
								Touch_code=AUTO_KEY_CODE;       // F1*******
							else if((Touch_Pos.y>=F2_BUTTON_Y1)&&(Touch_Pos.y<=F2_BUTTON_Y2))
								Touch_code=READ_KEY_CODE;       // F2******
							else if((Touch_Pos.y>=LAB_UP_TO_Y1)&&(Touch_Pos.y<=LAB_UP_TO_Y2))
								Touch_code=DENGJU_KEY_CODE;  //���ϼ�ͷ
							else if((Touch_Pos.y>=LAB_DOWN_TO_Y1)&&(Touch_Pos.y<=LAB_DOWN_TO_Y2))
								Touch_code=DENGFENG_KEY_CODE;  //���¼�ͷ
							}
						else if((Touch_Pos.x>=CALC_ONE_X1)&&(Touch_Pos.x<=CALC_PLUS_X2))//-----------������
							{	
							if((Touch_Pos.y>=CALC_ONE_Y1)&&(Touch_Pos.y<=CALC_ONE_Y2)) //row1
								{
								if((Touch_Pos.x>=CALC_ONE_X1)&&(Touch_Pos.x<=CALC_ONE_X2))
									{
									Touch_code=NINE_KEY_CODE;		// 1
									}
								else if((Touch_Pos.x>=CALC_TWO_X1)&&(Touch_Pos.x<=CALC_TWO_X2))
									{
									Touch_code=MOVE_KEY_CODE;		// 2
									}
								else if((Touch_Pos.x>=CALC_THREE_X1)&&(Touch_Pos.x<=CALC_THREE_X2))
									{
									Touch_code=DELETE_KEY_CODE;      //3
									}
								else if((Touch_Pos.x>=CALC_PLUS_X1)&&(Touch_Pos.x<=CALC_PLUS_X2))
									{
									Touch_code=REV_KEY_CODE;   //  +
									}	
								}
							else if((Touch_Pos.y>=CALC_FOUR_Y1)&&(Touch_Pos.y<=CALC_FOUR_Y2))  //row2
								{
								if((Touch_Pos.x>=CALC_FOUR_X1)&&(Touch_Pos.x<=CALC_FOUR_X2))
									{
									Touch_code=EIGHT_KEY_CODE;		//4
									}
								else if((Touch_Pos.x>=CALC_FIVE_X1)&&(Touch_Pos.x<=CALC_FIVE_X2))	
									{
									Touch_code=NO_KEY_CODE;      // 5
									}
								else if((Touch_Pos.x>=CALC_SIX_X1)&&(Touch_Pos.x<=CALC_SIX_X2))	
									{
									Touch_code=INSERT_KEY_CODE;      //6
									}
								else if((Touch_Pos.x>=CALC_SUB_X1)&&(Touch_Pos.x<=CALC_SUB_X2))	
									{
									Touch_code=OPTION_KEY_CODE;    //����  -
									}
								}
							else if((Touch_Pos.y>=CALC_SEVEN_Y1)&&(Touch_Pos.y<=CALC_SEVEN_Y2))  //row3
								{
								if((Touch_Pos.x>=CALC_SEVEN_X1)&&(Touch_Pos.x<=CALC_SEVEN_X2))
									{
									Touch_code=SEVEN_KEY_CODE;	//7
									}
								else if((Touch_Pos.x>=CALC_EIGHT_X1)&&(Touch_Pos.x<=CALC_EIGHT_X2))	
									{
									Touch_code=YES_KEY_CODE;    // 8
									}
								else if((Touch_Pos.x>=CALC_NINE_X1)&&(Touch_Pos.x<=CALC_NINE_X2))	
									{
									Touch_code=SUB_KEY_CODE;   // 9
									}
								else if((Touch_Pos.x>=CALC_MUL_X1)&&(Touch_Pos.x<=CALC_MUL_X2))	
									{
									Touch_code=MUL_TOUCH_CODE;  // *
									}
								}	
							else if((Touch_Pos.y>=CALC_C_Y1)&&(Touch_Pos.y<=CALC_C_Y2))  //row4
								{
								if((Touch_Pos.x>=CALC_C_X1)&&(Touch_Pos.x<=CALC_C_X2))
									{
									Touch_code=SIX_KEY_CODE;		// clear ����C
									}
								else if((Touch_Pos.x>=CALC_ZERO_X1)&&(Touch_Pos.x<=CALC_ZERO_X2))	
									{
									if(ShiftKey_flag==1)
										Touch_code=SHIFT_0_KEY_CODE;//shift+0
									else	
										Touch_code=PROG_KEY_CODE;     // 0  **********
									}
								else if((Touch_Pos.x>=CALC_DOT_X1)&&(Touch_Pos.x<=CALC_DOT_X2))	
									{
									Touch_code=ADD_KEY_CODE;   //  �㡰.��
									}
								else if((Touch_Pos.x>=CALC_DIV_X1)&&(Touch_Pos.x<=CALC_DIV_X2))	
									{
									Touch_code=DIV_TOUCH_CODE;  // �� /
									}
								}
							else if((Touch_Pos.y>=CALC_EQU_Y1)&&(Touch_Pos.y<=CALC_EQU_Y2))  //row5
								{
								if((Touch_Pos.x>=CALC_EQU_X1)&&(Touch_Pos.x<=CALC_EQU_X2))	
									{
									Touch_code=EQU_TOUCH_CODE;  //==
									}
								else if((Touch_Pos.x>=CALC_ENTER_X1)&&(Touch_Pos.x<=CALC_ENTER_X2))	
									{
									Touch_code=DOWN_KEY_CODE;   // ȷ��	
									// if(WorkMode==MANUAL_MODE)// �ֶ� ģʽ
										// Touch_code=UP_KEY_CODE;   ///////////����
									}	
								}
							}
						}
						break;
				case AUTO_DIVIDE_MODE://�ȷ�
				case TEACH_DIVIDE_MODE://ʾ�� �ȷ�
					if(Touch_Pos.y<=RUN_BUTTON_Y1)
						{
						if((Touch_Pos.x>=F1_BUTTON_X1)&&(Touch_Pos.x<=F1_BUTTON_X2))  //F1,2,3,4��ģʽ
							{
							if((Touch_Pos.y>=F1_BUTTON_Y1)&&(Touch_Pos.y<=F1_BUTTON_Y2))
								Touch_code=AUTO_KEY_CODE;       // F1*******
							else if((Touch_Pos.y>=F2_BUTTON_Y1)&&(Touch_Pos.y<=F2_BUTTON_Y2))
								Touch_code=READ_KEY_CODE;       // F2******
							else if((Touch_Pos.y>=F3_BUTTON_Y1)&&(Touch_Pos.y<=F3_BUTTON_Y2))
								Touch_code=RETURN_KEY_CODE;       // F3******
							else if((Touch_Pos.y>=F4_BUTTON_Y1)&&(Touch_Pos.y<=F4_BUTTON_Y2))
								Touch_code=MANUAL_KEY_CODE;       // F4******
							else if((Touch_Pos.y>=F5_BUTTON_Y1)&&(Touch_Pos.y<=F5_BUTTON_Y2))
								Touch_code=DENGJU_KEY_CODE;  //���ϼ�ͷ
							else if((Touch_Pos.y>=F6_BUTTON_Y1)&&(Touch_Pos.y<=F6_BUTTON_Y2))
								Touch_code=DENGFENG_KEY_CODE;  //���¼�ͷ
							}
						else if((Touch_Pos.x>=CALC_ONE_X1)&&(Touch_Pos.x<=CALC_PLUS_X2))//-----------������
							{	
							if((Touch_Pos.y>=CALC_ONE_Y1)&&(Touch_Pos.y<=CALC_ONE_Y2)) //row1
								{
								if((Touch_Pos.x>=CALC_ONE_X1)&&(Touch_Pos.x<=CALC_ONE_X2))
									{
									Touch_code=NINE_KEY_CODE;		// 1
									}
								else if((Touch_Pos.x>=CALC_TWO_X1)&&(Touch_Pos.x<=CALC_TWO_X2))
									{
									Touch_code=MOVE_KEY_CODE;		// 2
									}
								else if((Touch_Pos.x>=CALC_THREE_X1)&&(Touch_Pos.x<=CALC_THREE_X2))
									{
									Touch_code=DELETE_KEY_CODE;      //3
									}
								else if((Touch_Pos.x>=CALC_PLUS_X1)&&(Touch_Pos.x<=CALC_PLUS_X2))
									{
									Touch_code=REV_KEY_CODE;   //  +
									}	
								}
							else if((Touch_Pos.y>=CALC_FOUR_Y1)&&(Touch_Pos.y<=CALC_FOUR_Y2))  //row2
								{
								if((Touch_Pos.x>=CALC_FOUR_X1)&&(Touch_Pos.x<=CALC_FOUR_X2))
									{
									Touch_code=EIGHT_KEY_CODE;		//4
									}
								else if((Touch_Pos.x>=CALC_FIVE_X1)&&(Touch_Pos.x<=CALC_FIVE_X2))	
									{
									Touch_code=NO_KEY_CODE;      // 5
									}
								else if((Touch_Pos.x>=CALC_SIX_X1)&&(Touch_Pos.x<=CALC_SIX_X2))	
									{
									Touch_code=INSERT_KEY_CODE;      //6
									}
								else if((Touch_Pos.x>=CALC_SUB_X1)&&(Touch_Pos.x<=CALC_SUB_X2))	
									{
									Touch_code=OPTION_KEY_CODE;    //����  -
									}
								}
							else if((Touch_Pos.y>=CALC_SEVEN_Y1)&&(Touch_Pos.y<=CALC_SEVEN_Y2))  //row3
								{
								if((Touch_Pos.x>=CALC_SEVEN_X1)&&(Touch_Pos.x<=CALC_SEVEN_X2))
									{
									Touch_code=SEVEN_KEY_CODE;	//7
									}
								else if((Touch_Pos.x>=CALC_EIGHT_X1)&&(Touch_Pos.x<=CALC_EIGHT_X2))	
									{
									Touch_code=YES_KEY_CODE;    // 8
									}
								else if((Touch_Pos.x>=CALC_NINE_X1)&&(Touch_Pos.x<=CALC_NINE_X2))	
									{
									Touch_code=SUB_KEY_CODE;   // 9
									}
								else if((Touch_Pos.x>=CALC_MUL_X1)&&(Touch_Pos.x<=CALC_MUL_X2))	
									{
									Touch_code=MUL_TOUCH_CODE;  // *
									}
								}	
							else if((Touch_Pos.y>=CALC_C_Y1)&&(Touch_Pos.y<=CALC_C_Y2))  //row4
								{
								if((Touch_Pos.x>=CALC_C_X1)&&(Touch_Pos.x<=CALC_C_X2))
									{
									Touch_code=SIX_KEY_CODE;		// clear ����C
									}
								else if((Touch_Pos.x>=CALC_ZERO_X1)&&(Touch_Pos.x<=CALC_ZERO_X2))	
									{
									if(ShiftKey_flag==1)
										Touch_code=SHIFT_0_KEY_CODE;//shift+0
									else	
										Touch_code=PROG_KEY_CODE;     // 0  **********
									}
								else if((Touch_Pos.x>=CALC_DOT_X1)&&(Touch_Pos.x<=CALC_DOT_X2))	
									{
									Touch_code=ADD_KEY_CODE;   //  �㡰.��
									}
								else if((Touch_Pos.x>=CALC_DIV_X1)&&(Touch_Pos.x<=CALC_DIV_X2))	
									{
									Touch_code=DIV_TOUCH_CODE;  // �� /
									}
								}
							else if((Touch_Pos.y>=CALC_EQU_Y1)&&(Touch_Pos.y<=CALC_EQU_Y2))  //row5
								{
								if((Touch_Pos.x>=CALC_EQU_X1)&&(Touch_Pos.x<=CALC_EQU_X2))	
									{
									Touch_code=EQU_TOUCH_CODE;  //==
									}
								else if((Touch_Pos.x>=CALC_ENTER_X1)&&(Touch_Pos.x<=CALC_ENTER_X2))	
									{
									Touch_code=DOWN_KEY_CODE;   // ȷ��	
									// if(WorkMode==MANUAL_MODE)// �ֶ� ģʽ
										// Touch_code=UP_KEY_CODE;   ///////////����
									}	
								}
							}
						}
						break;
				// case READ_PRO_MESS_MODE:			 		//������  ģʽ
				case AUTO_FIND_NAME_MODE:
				case MANUAL_FIND_NAME_MODE:
				case TEACH_FIND_NAME_MODE:
				case SELF_FIND_NAME_MODE:
					if(Touch_Pos.y<=RUN_BUTTON_Y1)
						{
						if((Touch_Pos.x>=F1_BUTTON_X1)&&(Touch_Pos.x<=F1_BUTTON_X2))  //F1,2,3,4��ģʽ
							{
							if((Touch_Pos.y>=F1_BUTTON_Y1)&&(Touch_Pos.y<=F1_BUTTON_Y2))
								Touch_code=AUTO_KEY_CODE;       // F1*******
							else if((Touch_Pos.y>=F2_BUTTON_Y1)&&(Touch_Pos.y<=F2_BUTTON_Y2))
								Touch_code=READ_KEY_CODE;       // F2******
							else if((Touch_Pos.y>=F3_BUTTON_Y1)&&(Touch_Pos.y<=F3_BUTTON_Y2))
								Touch_code=RETURN_KEY_CODE;       // F3******
							else if((Touch_Pos.y>=F4_BUTTON_Y1)&&(Touch_Pos.y<=F4_BUTTON_Y2))
								Touch_code=MANUAL_KEY_CODE;       // F4****
							}
						else 
							{
							//keyboard button------------
							if((Touch_Pos.x>=TOU_BUTT_ONE_X1)&&(Touch_Pos.x<=TOU_BUTT_ONE_X2))
								{
								if((Touch_Pos.y>=TOU_BUTT_ONE_Y1)&&(Touch_Pos.y<=TOU_BUTT_ONE_Y2))
									Touch_code=NINE_KEY_CODE;		// 1
								else if((Touch_Pos.y>=TOU_BUTT_FOUR_Y1)&&(Touch_Pos.y<=TOU_BUTT_FOUR_Y2))
									Touch_code=EIGHT_KEY_CODE;		//4
								else if((Touch_Pos.y>=TOU_BUTT_SEVEN_Y1)&&(Touch_Pos.y<=TOU_BUTT_SEVEN_Y2))
									Touch_code=SEVEN_KEY_CODE;	//7
								else if((Touch_Pos.y>=TOU_BUTT_CLR_Y1)&&(Touch_Pos.y<=TOU_BUTT_CLR_Y2))
									Touch_code=SIX_KEY_CODE;		// clear
								}
							else if((Touch_Pos.x>=TOU_BUTT_TWO_X1)&&(Touch_Pos.x<=TOU_BUTT_TWO_X2))
								{
								if((Touch_Pos.y>=TOU_BUTT_TWO_Y1)&&(Touch_Pos.y<=TOU_BUTT_TWO_Y2))
									Touch_code=MOVE_KEY_CODE;     // 2
								else if((Touch_Pos.y>=TOU_BUTT_FIVE_Y1)&&(Touch_Pos.y<=TOU_BUTT_FIVE_Y2))
									Touch_code=NO_KEY_CODE;     // 5
								else if((Touch_Pos.y>=TOU_BUTT_EIGHT_Y1)&&(Touch_Pos.y<=TOU_BUTT_EIGHT_Y2))
									Touch_code=YES_KEY_CODE;    // 8
								else if((Touch_Pos.y>=TOU_BUTT_ZERO_Y1)&&(Touch_Pos.y<=TOU_BUTT_ZERO_Y2))
									Touch_code=PROG_KEY_CODE;    // 0
								}
							else if((Touch_Pos.x>=TOU_BUTT_THREE_X1)&&(Touch_Pos.x<=TOU_BUTT_THREE_X2))
								{
								if((Touch_Pos.y>=TOU_BUTT_THREE_Y1)&&(Touch_Pos.y<=TOU_BUTT_THREE_Y2))
									Touch_code=DELETE_KEY_CODE;      //3
								else if((Touch_Pos.y>=TOU_BUTT_SIX_Y1)&&(Touch_Pos.y<=TOU_BUTT_SIX_Y2))
									Touch_code=INSERT_KEY_CODE;      //6
								else if((Touch_Pos.y>=TOU_BUTT_NINE_Y1)&&(Touch_Pos.y<=TOU_BUTT_NINE_Y2))
									Touch_code=SUB_KEY_CODE;  // 9
								else if((Touch_Pos.y>=TOU_BUTT_OK_Y1)&&(Touch_Pos.y<=TOU_BUTT_OK_Y2))
									Touch_code=DOWN_KEY_CODE;  // ȷ��
								}
							else if((Touch_Pos.x>=TOU_BUTT_UP_X1)&&(Touch_Pos.x<=TOU_BUTT_UP_X2))
								{
								if((Touch_Pos.y>=TOU_BUTT_UP_Y1)&&(Touch_Pos.y<=TOU_BUTT_UP_Y2))
									Touch_code=DENGJU_KEY_CODE;  //���ϼ�ͷ
								else if((Touch_Pos.y>=TOU_BUTT_DOWN_Y1)&&(Touch_Pos.y<=TOU_BUTT_DOWN_Y2))
									Touch_code=DENGFENG_KEY_CODE;  //���¼�ͷ
								else if((Touch_Pos.y>=TOU_BUTT_LEFT_Y1)&&(Touch_Pos.y<=TOU_BUTT_LEFT_Y2))
									Touch_code=LEFT_KEY_CODE;      //��---------------------------------
								else if((Touch_Pos.y>=TOU_BUTT_RIGHT_Y1)&&(Touch_Pos.y<=TOU_BUTT_RIGHT_Y2))
									Touch_code=RIGHT_KEY_CODE;      //��-------------------------------
								}
							}
						}
						break;
				// case READ_DEL_ALL_PRO_MODE://ɾ������pro  ģʽ
				case AUTO_FIND_DEL_ALL_MODE://
				case MANUAL_FIND_DEL_ALL_MODE://
				case TEACH_FIND_DEL_ALL_MODE://
				case SELF_FIND_DEL_ALL_MODE://
				case TEACH_DEL_ALL_SIZE_MODE://	ɾ�����гߴ�
				case AUTO_DEL_ALL_SIZE_MODE://	ɾ�����гߴ�
					if((Touch_Pos.y>=DEL_ALL_OK_Y1)&&(Touch_Pos.y<=DEL_ALL_OK_Y2))
						{
						if((Touch_Pos.x>=DEL_ALL_OK_X1)&&(Touch_Pos.x<=DEL_ALL_OK_X2)) 
							Touch_code=DOWN_KEY_CODE;   // ȷ��
						else if((Touch_Pos.x>=DEL_ALL_CANCEL_X1)&&(Touch_Pos.x<=DEL_ALL_CANCEL_X2))
							Touch_code=SIX_KEY_CODE;		// clear
						}		
						break;
				case MANUAL_RULER_MODE://�ֶ� ��׼
				// case MANUAL_TOOLS_MODE://�ֶ� ����
				case MANUAL_SET_MODE:
				case AUTO_SET_MODE:
				case TEACH_SET_MODE:
				case SELF_SET_MODE:
				case MANUAL_CLOCK_MODE://�ֶ� ʱ��
				case MANUAL_PULSE_MODE://�ֶ� ���嵱��
				case MANUAL_PASS_MODE://�ֶ� �����趨
				// // case MANUAL_SERVO_C_MODE:// �ֶ�ֱ���ŷ� C ���� 
				// // case SELF_RULER_MODE://�Ե� ��׼
				// // case SELF_TOOLS_MODE://�Ե� ����
				// case MANUAL_IO_TEST_MODE:// IO ����ģʽ--------
				case MANUAL_IO_MODE:  //io����ģʽ
				case AUTO_IO_MODE:  //io����ģʽ
				case TEACH_IO_MODE:  //io����ģʽ
				case SELF_IO_MODE:  //io����ģʽ
					if(Touch_Pos.y<=RUN_BUTTON_Y1)
						{
						if((Touch_Pos.x>=F1_BUTTON_X1)&&(Touch_Pos.x<=F1_BUTTON_X2))  //F1,2,3,4��ģʽ
							{
							if((Touch_Pos.y>=F1_BUTTON_Y1)&&(Touch_Pos.y<=F1_BUTTON_Y2))
								Touch_code=AUTO_KEY_CODE;       // F1
							else if((Touch_Pos.y>=F2_BUTTON_Y1)&&(Touch_Pos.y<=F2_BUTTON_Y2))
								Touch_code=READ_KEY_CODE;       // F2
							else if((Touch_Pos.y>=F3_BUTTON_Y1)&&(Touch_Pos.y<=F3_BUTTON_Y2))
								Touch_code=DENGJU_KEY_CODE;  //���ϼ�ͷ      //F3
							else if((Touch_Pos.y>=F4_BUTTON_Y1)&&(Touch_Pos.y<=F4_BUTTON_Y2))
								Touch_code=DENGFENG_KEY_CODE;  //���¼�ͷ    // F4
							else if((Touch_Pos.y>=F5_BUTTON_Y1)&&(Touch_Pos.y<=F5_BUTTON_Y2))
								Touch_code=ZERO_KEY_CODE;	//����  	// F5
							}
						else if((Touch_Pos.x>=CALC_ONE_X1)&&(Touch_Pos.x<=CALC_PLUS_X2))//-----------������
							{	
							if((Touch_Pos.y>=CALC_ONE_Y1)&&(Touch_Pos.y<=CALC_ONE_Y2)) //row1
								{
								if((Touch_Pos.x>=CALC_ONE_X1)&&(Touch_Pos.x<=CALC_ONE_X2))
									{
									Touch_code=NINE_KEY_CODE;		// 1
									}
								else if((Touch_Pos.x>=CALC_TWO_X1)&&(Touch_Pos.x<=CALC_TWO_X2))
									{
									Touch_code=MOVE_KEY_CODE;		// 2
									}
								else if((Touch_Pos.x>=CALC_THREE_X1)&&(Touch_Pos.x<=CALC_THREE_X2))
									{
									Touch_code=DELETE_KEY_CODE;      //3
									}
								else if((Touch_Pos.x>=CALC_PLUS_X1)&&(Touch_Pos.x<=CALC_PLUS_X2))
									{
									Touch_code=REV_KEY_CODE;   //  +
									}	
								}
							else if((Touch_Pos.y>=CALC_FOUR_Y1)&&(Touch_Pos.y<=CALC_FOUR_Y2))  //row2
								{
								if((Touch_Pos.x>=CALC_FOUR_X1)&&(Touch_Pos.x<=CALC_FOUR_X2))
									{
									Touch_code=EIGHT_KEY_CODE;		//4
									}
								else if((Touch_Pos.x>=CALC_FIVE_X1)&&(Touch_Pos.x<=CALC_FIVE_X2))	
									{
									Touch_code=NO_KEY_CODE;      // 5
									}
								else if((Touch_Pos.x>=CALC_SIX_X1)&&(Touch_Pos.x<=CALC_SIX_X2))	
									{
									Touch_code=INSERT_KEY_CODE;      //6
									}
								else if((Touch_Pos.x>=CALC_SUB_X1)&&(Touch_Pos.x<=CALC_SUB_X2))	
									{
									Touch_code=OPTION_KEY_CODE;    //����  -
									}
								}
							else if((Touch_Pos.y>=CALC_SEVEN_Y1)&&(Touch_Pos.y<=CALC_SEVEN_Y2))  //row3
								{
								if((Touch_Pos.x>=CALC_SEVEN_X1)&&(Touch_Pos.x<=CALC_SEVEN_X2))
									{
									Touch_code=SEVEN_KEY_CODE;	//7
									}
								else if((Touch_Pos.x>=CALC_EIGHT_X1)&&(Touch_Pos.x<=CALC_EIGHT_X2))	
									{
									Touch_code=YES_KEY_CODE;    // 8
									}
								else if((Touch_Pos.x>=CALC_NINE_X1)&&(Touch_Pos.x<=CALC_NINE_X2))	
									{
									Touch_code=SUB_KEY_CODE;   // 9
									}
								else if((Touch_Pos.x>=CALC_MUL_X1)&&(Touch_Pos.x<=CALC_MUL_X2))	
									{
									Touch_code=MUL_TOUCH_CODE;  // *
									}
								}	
							else if((Touch_Pos.y>=CALC_C_Y1)&&(Touch_Pos.y<=CALC_C_Y2))  //row4
								{
								if((Touch_Pos.x>=CALC_C_X1)&&(Touch_Pos.x<=CALC_C_X2))
									{
									Touch_code=SIX_KEY_CODE;		// clear ����C
									}
								else if((Touch_Pos.x>=CALC_ZERO_X1)&&(Touch_Pos.x<=CALC_ZERO_X2))	
									{
									if(ShiftKey_flag==1)
										Touch_code=SHIFT_0_KEY_CODE;//shift+0
									else	
										Touch_code=PROG_KEY_CODE;     // 0  **********
									}
								else if((Touch_Pos.x>=CALC_DOT_X1)&&(Touch_Pos.x<=CALC_DOT_X2))	
									{
									Touch_code=ADD_KEY_CODE;   //  �㡰.��
									}
								else if((Touch_Pos.x>=CALC_DIV_X1)&&(Touch_Pos.x<=CALC_DIV_X2))	
									{
									Touch_code=DIV_TOUCH_CODE;  // �� /
									}
								}
							else if((Touch_Pos.y>=CALC_EQU_Y1)&&(Touch_Pos.y<=CALC_EQU_Y2))  //row5
								{
								if((Touch_Pos.x>=CALC_EQU_X1)&&(Touch_Pos.x<=CALC_EQU_X2))	
									{
									Touch_code=EQU_TOUCH_CODE;  //==
									}
								else if((Touch_Pos.x>=CALC_ENTER_X1)&&(Touch_Pos.x<=CALC_ENTER_X2))	
									{
									Touch_code=DOWN_KEY_CODE;   // ȷ��	
									// if(WorkMode==MANUAL_MODE)// �ֶ� ģʽ
										// Touch_code=UP_KEY_CODE;   ///////////����
									}	
								}
							}
						}
					
						break;
						
				}
			}	
			
		}
	}
//*************************************************	���� ��ֵת��
// if(Touch_code!=0)
	// {
	// if((Touch_code&0xffff0000)==0xffff0000)  //�� ������(����)-----------------------------��תΪ���̶�Ӧ��
		// {
		
		// }
	// }	
}

void TouchButton_dis(Int32U code,Int8U down_flag)  //����  ��ť��ʾ
{
Int8U key_num=0xff;
Int8U t_butt_flag=0;
if(code!=0)
	{	
	if(WorkStart_flag==1)
		{
		switch(WorkMode)
			{
			// case READ_PRO_MESS_MODE:
			case AUTO_FIND_NAME_MODE:
			case MANUAL_FIND_NAME_MODE:
			case TEACH_FIND_NAME_MODE:
			case SELF_FIND_NAME_MODE:
					t_butt_flag=2;
					break;
			default:
					t_butt_flag=1;
					break;
			}	
		}
	if(Board_TestMod==TEST_SYS_WORD)
		t_butt_flag=3;
		
	if(t_butt_flag>0)		//����
		{
		switch(code)
			{
			case NINE_KEY_CODE:		// 1
					key_num=BUTT_1;
					break;
			case MOVE_KEY_CODE:		// 2
					key_num=BUTT_2;
					break;
			case DELETE_KEY_CODE:      //3		
					key_num=BUTT_3;
					break;
			case EIGHT_KEY_CODE:		//4	
					key_num=BUTT_4;
					break;
			case NO_KEY_CODE:		//5	
					key_num=BUTT_5;
					break;	
			case INSERT_KEY_CODE:      //6
					key_num=BUTT_6;
					break;	
			case SEVEN_KEY_CODE:	//7
					key_num=BUTT_7;
					break;
			case YES_KEY_CODE:    // 8	
					key_num=BUTT_8;
					break;	
			case SUB_KEY_CODE:   // 9
					key_num=BUTT_9;
					break;	
			case PROG_KEY_CODE:     // 0 
					key_num=BUTT_0;
					break;
			case ADD_KEY_CODE:   //  �㡰.��
					key_num=BUTT_DOT;
					break;
			case SIX_KEY_CODE:		// clear ����C
					key_num=BUTT_CLEAR;
					break;
			case REV_KEY_CODE:   //  +		
					key_num=BUTT_PLUS;
					break;
			case OPTION_KEY_CODE:    //����  -
					key_num=BUTT_SUB;
					break;
			case MUL_TOUCH_CODE:  // *
					key_num=BUTT_MUL;
					break;	
			case DIV_TOUCH_CODE:  // �� /
					key_num=BUTT_DIV;
					break;	
			case ZERO_KEY_CODE:	//C����
					key_num=BUTT_INSERT;
					break;
			// // case READ_KEY_CODE:       // F2*******************�˳�	
					// // if(down_flag==1)
						// // key_num=BUTT_EXIT;
					// // break;	
			case EQU_TOUCH_CODE:  //=
					key_num=BUTT_EQU;
					break;	
			case DOWN_KEY_CODE:   // ȷ��
						key_num=BUTT_ENTER;
					break;
			// // case UP_KEY_CODE:    ///////////����
					// // if(WorkMode==MANUAL_MODE)// �ֶ� ģʽ
						// // key_num=BUTT_RUN;
					// // break;
			case DENGJU_KEY_CODE:  //���ϼ�ͷ����
			case NEXTKNIFE_KEY_CODE:   //ǰ��
					key_num=BUTT_UP;
					break;
			case DENGFENG_KEY_CODE: //���¼�ͷ		
			case ADJUST_KEY_CODE:     //����		
					key_num=BUTT_DOWN;
					break;
			case LEFT_KEY_CODE:	// ��	
					key_num=BUTT_LEFT;
					break;
			case RIGHT_KEY_CODE:	// ��
					key_num=BUTT_RIGHT;
					break;
			// // case SHIFT_KEY_CODE:
					// // key_num=BUTT_SHIFT;	//shift *********
					// // break;
			}
		if(key_num!=0xff)
			{
			switch(t_butt_flag)
				{
				case 1:
				// // case 2:
					Button_dis(key_num, down_flag); //���� ��ť ��ʾ
					break;
				case 2://���뷨 
					InputKEY_BUTT_dis(key_num, down_flag); //���� key ��ʾ--------���뷨
					break;
				case 3:	//  ���� �汾key 
					Num_Keyboard_Tou_dis(key_num, down_flag); //���� key ��ʾ password
					break;
				}
			}
		}
	}
}


void LongTouchDown_Exec(void)//��������
{
Int8U jog=0;
GetTouchKeyCode();// ��ô��� ��ֵ
Touch_Pos_save=Touch_Pos;
LongTouchDis_flag = 0;
switch(Touch_code)
	{
	case MANUAL_KEY_CODE:      // F4**** 
		switch(WorkMode)
				{	
				case AUTO_MODE://�Զ���������
				case TEACH_MODE://ʾ�� ģʽ
				// case SELF_CUT_MODE:  //�Ե��� ģʽ
					Touch_code=FIVE_KEY_CODE;   //ɾ��  delete all 
						break;
				}
				break;
	case ADJUST_KEY_CODE://���˰���	
	case NEXTKNIFE_KEY_CODE://ǰ������
	case FAST_BACK_KEY_CODE://  ����
	case FAST_AHEAD_KEY_CODE://��� 
			jog=1;
			LongTouchDis_flag = 1;
				break;
	default:
			jog=0;
			LongTouchDis_flag = 1;
				break;
	}

if(LongTouchDis_flag!=1)      // key exec
	{
	Touch_code_temp=Touch_code;
	KeyExec(Touch_code_temp); //��������---
	}
else
	{
	// LongTouchZoneDis(Touch_Pos.x,Touch_Pos.y ,24*3,24, jog);
	}

}

void LongTouchUp_Exec(void)//�����ͷ�
{
if(LongTouchDis_flag==1)
	{
	LongTouchDis_flag=0;
	// CurrentArea_recover4(Touch_Pos_save.x,Touch_Pos_save.y ,24*3,24);
	}
}

