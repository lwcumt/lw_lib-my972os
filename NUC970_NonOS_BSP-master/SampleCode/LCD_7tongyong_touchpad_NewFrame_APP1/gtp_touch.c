#include "gtp_touch.h"

#include "io.h"
#include "tsc2046.h"
#include"key.h"

#include "gtp.h"
#include "comm_touch.h"
#include "touchevent.h"

Int8U Gtp_Touch_DownTime=0;
Int8U Gtp_Touch_Down_Flag=0;
Int8U Gtp_Touch_Exec_Flag=0;
//Int16U TouDownLongTime=0;

void Gtp_Touch_Scan(void)
{
	Int32U xytemp;
	GT911_Scan();
//GT911_Scan();
if(Gtp_Touch_Down_Flag==0)
	{
	if((tp_dev.sta&TP_PRES_DOWN)==TP_PRES_DOWN)	//֮ǰ�Ǳ����µ�
		{
			Gtp_Touch_DownTime=0;
			Gtp_Touch_Down_Flag=1;
		}
	}
else
	{
	if(Gtp_Touch_Exec_Flag==0)
		{
		if((tp_dev.sta&TP_PRES_DOWN)==TP_PRES_DOWN)	//֮ǰ�Ǳ����µ�
			{
			Gtp_Touch_DownTime++;
			if(Gtp_Touch_DownTime>=2)
				{
				Gtp_Touch_DownTime=0;
				Gtp_Touch_Exec_Flag=1;

						LED2_ON;
							xytemp=((Int32U)tp_dev.x[0]*((C_GLCD_H_SIZE*100000)/TOUCH_H_SIZE))/100000;

					TouchAD.x =xytemp;
						

							xytemp=((Int32U)tp_dev.y[0]*((C_GLCD_V_SIZE*100000)/TOUCH_V_SIZE))/100000;

						TouchAD.y =xytemp;	//��ȡ x,y ֵ			
					
						TouchAD.status=TOUCH_DOWN;
					
//////						LED2_ON;
//////						TouchAD.x =TouComm_X;
//////						TouchAD.y =TouComm_Y;	//?? x,y ?
//////						TouDown_Comm_flag=1;
					//	Printf24("TouchEvent(TouchAD_DOWN)",200,400,BLACK_COLOR,1,BLUE_COLOR);

					#ifdef USER_NEW_FRAME
						TouchEvent(TouchAD);
					#else 
					//	Printf24("TouchEvent(RETURN_DOWN)",200,400,BLACK_COLOR,1,BLUE_COLOR);
				
						TouchKey_exec();  //````````````````???  ??``````````
					#endif
						TouDownLongTime=0;
						
						TouDownLongTime=0;
				}
			}
		else
			{
			Gtp_Touch_DownTime=0;
			Gtp_Touch_Down_Flag=0;
			}
		}
	else
		{
		if((tp_dev.sta&TP_PRES_DOWN)==0)	//���ͷ��ж�
			{
				Gtp_Touch_DownTime++;
				if(Gtp_Touch_DownTime>=2)
				{
				Gtp_Touch_DownTime=0;
				Gtp_Touch_Down_Flag=0;
				Gtp_Touch_Exec_Flag=0;

						//�ͷ�  ����

				//��������������������
				GoFrontEn_flag=0;
				GoBackEn_flag=0;
				// ---------------------------
				TouchAD.status=TOUCH_UP;
			//	Printf24("TouchEvent(TouchAD_UP)",200,400,BLACK_COLOR,1,BLUE_COLOR);

			#ifdef USER_NEW_FRAME
				TouchEvent(TouchAD);
			#else 
				TouchButton_dis(Touch_code,0);  //������  ��ʾ
			#endif
				Touch_code=0;//-------�ͷź� �崥����ֵ
			//	ACMotor_ReleaseStop();
				}
			}
		else
			{
			Gtp_Touch_DownTime=0;

			if(Board_TestMod==TEST_BOARD)  //���幦�ܲ���mode-------------------------------
					{
							xytemp=((Int32U)tp_dev.x[0]*((C_GLCD_H_SIZE*100000)/TOUCH_H_SIZE))/100000;

					TouchAD.x =xytemp;
						

							xytemp=((Int32U)tp_dev.y[0]*((C_GLCD_V_SIZE*100000)/TOUCH_V_SIZE))/100000;

						TouchAD.y =xytemp;	//��ȡ x,y ֵ			
						
								//`````````````````````
								GetTouch_pos();
								if(Touch_Pos.x>=C_GLCD_H_SIZE)
									Touch_Pos.x=C_GLCD_H_SIZE-1;
								if(Touch_Pos.y>=C_GLCD_V_SIZE)
									Touch_Pos.y=C_GLCD_V_SIZE-1;
								PutPixel(Touch_Pos.x,Touch_Pos.y,RED_COLOR);//��д
					}
				else
					{
					TouDownLongTime++;
					if(TouDownLongTime>=TOUCH_ERR_TIME)  ////---------------------------����  ����ʱ�������ǿ���ͷ�
						{	
						//��������������������
						GoFrontEn_flag=0;
						GoBackEn_flag=0;	
						TouchButton_dis(Touch_code,0);  //������  ��ʾ
						Touch_code=0;//-------�ͷź� �崥����ֵ
						ACMotor_ReleaseStop();
						}
					}
			}
		}
	}


/*
	if(TouchReady_flag == 0)
		{
		TouchConnectWaitTime++;
		if(TouchConnectWaitTime>=500) //��� ����
			{
			TouchConnectWaitTime=0;
			TouchReady_flag=1;
			LED2_OFF;
			}	
		}
	else		//���� λ�ô���
		{
		if(TouDown_Comm_flag == 0)
			{
			if(TouCommPosGet_flag == 1)		//======��ȡ��������
				{
				if(TouchCommCMD_Down_flag == 1)// ----���µ�����
					{
					if((TouComm_X>TOU_AD_MIN)&&(TouComm_X<TOU_AD_MAX)&&(TouComm_Y>TOU_AD_MIN)&&(TouComm_Y<TOU_AD_MAX))	//��������  ��Ч
						{
						LED2_ON;
						TouchAD.x =TouComm_X;
						TouchAD.y =TouComm_Y;	//��ȡ x,y ֵ
						TouDown_Comm_flag=1;
						TouchKey_exec();  //````````````````������  ����``````````
						TouDownLongTime=0;
						}
					TouchCommCMD_Down_flag=0;
					}
				TouCommPosGet_flag = 0;
				}
			}
		else	//�ȴ� �ͷ�
			{
			if(TouchCommCMD_Up_flag == 1)	//=====�ͷŵ�����
				{
				LED2_OFF;
						//�ͷ�  ����
				TouchCommCMD_Up_flag =0;TouchCommCMD_Down_flag=0;
				TouDown_Comm_flag=0;
				TouCommPosGet_flag = 0;
				//��������������������
				GoFrontEn_flag=0;
				GoBackEn_flag=0;
				// ---------------------------
					TouchButton_dis(Touch_code,0);  //������  ��ʾ
				Touch_code=0;//-------�ͷź� �崥����ֵ
				ACMotor_ReleaseStop();
				}
			else	//δ�ͷ�---
				{
				if(Board_TestMod==TEST_BOARD)  //���幦�ܲ���mode-------------------------------
					{
					if(TouCommPosGet_flag == 1)		//======��ȡ��������
						{
						if(TouchCommCMD_Down_flag == 1)// ----���µ�����
							{
							if((TouComm_X>TOU_AD_MIN)&&(TouComm_X<TOU_AD_MAX)&&(TouComm_Y>TOU_AD_MIN)&&(TouComm_Y<TOU_AD_MAX))	//��������  ��Ч
								{
								TouchAD.x =TouComm_X;
								TouchAD.y =TouComm_Y;	//��ȡ x,y ֵ
								//`````````````````````
								GetTouch_pos();
								if(Touch_Pos.x>=C_GLCD_H_SIZE)
									Touch_Pos.x=C_GLCD_H_SIZE-1;
								if(Touch_Pos.y>=C_GLCD_V_SIZE)
									Touch_Pos.y=C_GLCD_V_SIZE-1;
								PutPixel(Touch_Pos.x,Touch_Pos.y,RED_COLOR);//��д
								}
							TouchCommCMD_Down_flag=0;
							}
						TouCommPosGet_flag = 0;
						}
					
					}
				else
					{
					TouDownLongTime++;
					if(TouDownLongTime>=TOUCH_ERR_TIME)  ////---------------------------����  ����ʱ�������ǿ���ͷ�
						{	
						TouDown_Comm_flag=0;
						TouCommPosGet_flag = 0;TouchCommCMD_Down_flag=0;
						//��������������������
						GoFrontEn_flag=0;
						GoBackEn_flag=0;	
						TouchButton_dis(Touch_code,0);  //������  ��ʾ
						Touch_code=0;//-------�ͷź� �崥����ֵ
						ACMotor_ReleaseStop();
						}
					}
				}
			}
		}


*/

}
