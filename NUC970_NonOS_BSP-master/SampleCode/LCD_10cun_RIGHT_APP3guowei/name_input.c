

#include"name_input.h"
#include"pic_exec.h"
#include"word_lib.h"
#include"key.h"




const Int8U CH_1[]={',','.','_',':','?','!',0xaa};
const Int8U CH_ABC[]={'a','b','c','A','B','C',0xaa};
const Int8U CH_DEF[]={'d','e','f','D','E','F',0xaa};
const Int8U CH_GHI[]={'g','h','i','G','H','I',0xaa};
const Int8U CH_JKL[]={'j','k','l','J','K','L',0xaa};
const Int8U CH_MNO[]={'m','n','o','M','N','O',0xaa};
const Int8U CH_PQRS[]={'p','q','r','s','P','Q','R','S',0xaa};
const Int8U CH_TUV[]={'t','u','v','T','U','V',0xaa};
const Int8U CH_WXYZ[]={'w','x','y','z','W','X','Y','Z',0xaa};
const Int8U CH_NOP[]={' ',0xaa};



Int8U InputNum_sel;
Int8U InputLibDisplay_flag;
Int8U InputOK_flag;

pInt8U pbuf_temp;

Int8U InputWord_cou;
Int8U InputNameDisBuf[PRONAME_SIZE+1];

Int8U PY_buf[10];
Int8U PY_temp[10];
Int8U pinyin_cou;
Int8U PY_index_sum;
Int8U PY_index_order;

Int8U PY_hanzi_sum;
Int8U PY_hanzi_order;
pInt8U pHanzi_buf;
Int8U hanzi_temp[3];



void ClrNameWindow(void)	//	��� ������
{
Int16U x1,y1,x2,y2;
Int16U line_color,fill_color;
Int8U i;
line_color=RED_COLOR,fill_color=WHITE_COLOR;
x1=INPUT_NAME_WIN_X;y1=INPUT_NAME_WIN_Y;
x2=x1+INPUT_NAME_WIDE,y2=y1+INPUT_NAME_HIGH;
GLCD_SetWindow_Fill(x1,y1, x2,y2, line_color,fill_color);

//**********
InputWord_cou=0;
for(i=0;i<=PRONAME_SIZE;i++)
	{
	InputNameDisBuf[i]=0;
	}
InputLibDisplay_flag=0;
InputOK_flag=0;
}

void ProNameDis_Window(void) //������ ���� ��ʾ
{
Int8U str[30],i;
Int16U x,y;
Int16U line_color,fill_color;
line_color=BLUE_COLOR,fill_color=WHITE_COLOR;
x=INPUT_NAME_WIN_X+5;y=INPUT_NAME_WIN_Y+5;
for(i=0;i<=PRONAME_SIZE;i++)
	{
	str[i]=InputNameDisBuf[i];
	if(str[i]==0)
		break;
	}
if(i>PRONAME_SIZE)
	{
	str[i]=0;
	}
Printf24(str,x,y,line_color,0,fill_color);
}

void ClrInputLib(void)	//��� ��ʾ��
{
Int16U x1,y1,x2,y2;
Int16U line_color,fill_color;
line_color=fill_color=WHITE_COLOR;
x1=INPUT_NAME_WIN_X;y1=INPUT_SEL_Y;
x2=x1+INPUT_NAME_WIDE,y2=INPUT_LIB_Y+35;
GLCD_SetWindow_Fill(x1,y1, x2,y2, line_color,fill_color);
y1=INPUT_LIB_Y;
y2=y1;
line_color=BLUE_COLOR;
GLCD_DrawLine(x1, y1, x2, y2, line_color);
//**************
pinyin_cou=0;
}


void ProData_dis(pInt8U nums,Int8U row)		//������Ϣ ���� ��ʾ
{
Int16U x,y,cou=0;
Int16U fill_color=PRO_MESS_COLOR1;
Int8U str[30];

if(row<4)
	{
	x=PRO_MESS_X+180;y=PRO_MESS_Y+20+40*row;
	while(cou<15)
		{
		str[cou]=nums[cou];
		if(str[cou]==0)
			break;
		cou++;
		}
	if(cou>=15)		
		str[cou]=0;
	Printf24(str,x,y,BLACK_COLOR,1,fill_color);	
	}
else
	{
	row++;
	x=PRO_MESS_X+10;y=PRO_MESS_Y+20+40*row;
	// while(cou<=PRONAME_SIZE)
		// {
		// str[cou]=nums[cou];
		// if(str[cou]==0)
			// break;
		// cou++;
		// }
	// if(cou>PRONAME_SIZE)		
		// str[cou]=0;
	Printf24(nums,x,y,BLACK_COLOR,1,fill_color);		
	}
}

void InputStus_dis(Int8U stus)	//���뷨  ��ʾ
{
Int16U x,y,line_color,fill_color;
line_color=fill_color=PRO_MESS_COLOR2;
x=PRO_MESS_X+(PRO_MESS_WIDE/2)+80;y=PRO_MESS_Y+5;
GLCD_SetWindow_Fill(x, y, x+220, y+30, line_color, fill_color);
line_color=BLACK_COLOR;
fill_color=BLUE_COLOR;
switch(stus)
	{
	case NUMBER_INPUT:
		switch(Language)
			{
			case CHN_HAN:
				Printf24("��������",x,y,line_color,0,fill_color);
				Printf24("����",x,y,line_color,1,fill_color);
				break;
			case ENGLISH:
			case PORTUGAL:	//������
				Printf24("Number -Input",x,y,line_color,0,fill_color);
				Printf24("Number",x,y,line_color,1,fill_color);
				break;
			case INDONSIA:	//ӡ��
				Printf24("Nomor -Input",x,y,line_color,0,fill_color);
				Printf24("Nomor",x,y,line_color,1,fill_color);
				break;
			}
		break;
	case CHAR_INPUT:
		switch(Language)
			{
			case CHN_HAN:
				Printf24("��ĸ����",x,y,line_color,0,fill_color);
				Printf24("��ĸ",x,y,line_color,1,fill_color);
				break;
			case ENGLISH:
			case PORTUGAL:	//������
				Printf24("Char -Input",x,y,line_color,0,fill_color);
				Printf24("Char ",x,y,line_color,1,fill_color);
				break;
			case INDONSIA:	//ӡ��
				Printf24("alfabet-Input",x,y,line_color,0,fill_color);
				Printf24("alfabet",x,y,line_color,1,fill_color);
				break;
			}
		break;
	case PINYIN_INPUT:
		switch(Language)
			{
			case CHN_HAN:
				Printf24("ƴ������",x,y,line_color,0,fill_color);
				Printf24("ƴ��",x,y,line_color,1,fill_color);
				break;
			case ENGLISH:
			case INDONSIA:	//ӡ��
			case PORTUGAL:	//������
				Printf24("Pinyin -Input",x,y,line_color,0,fill_color);
				Printf24("Pinyin ",x,y,line_color,1,fill_color);
				break;
			}
		break;	
	}
ClrInputLib();	//��� ��ʾ��
}

//***************
void Num_Char_SelDis(Int8U order, pInt8U nums, Int8U sel_flag)	//һ�� ��ĸ��ʾ
{
Int8U str[3];
Int16U x,y;
Int16U line_color,fill_color;
if(sel_flag==0)
	{
	line_color=BLACK_COLOR;fill_color=WHITE_COLOR;
	}
else
	{
	line_color=WHITE_COLOR;fill_color=BLUE_COLOR;
	}
x=INPUT_SEL_X,y=INPUT_SEL_Y+(order%INPUT_SEL_ROW)*INPUT_SEL_GAP;
str[0]=nums[order];
str[1]=0;
Printf24(str,x,y,line_color,1,fill_color);
}
void ClrInputHintText_dis(void)		//��� ����ѡ���� ��ʾ
{
Int16U x1,y1,x2,y2;
Int16U line_color,fill_color;
x1=INPUT_SEL_X,y1=INPUT_SEL_Y;
x2=x1+200,y2=y1+INPUT_SEL_ROW*INPUT_SEL_GAP;
line_color=fill_color=WHITE_COLOR;
GLCD_SetWindow_Fill(x1,y1, x2,y2, line_color,fill_color);
}

void Num_Char_PageDis(Int8U order, pInt8U ptab)	//һҳ ��ʾ
{
Int8U row;
row=0;
ClrInputHintText_dis();//��� ����ѡ���� ��ʾ
while(row<INPUT_SEL_ROW)
	{
	if(*(ptab+order)!=0xaa)
		{
		Num_Char_SelDis(order,ptab,0);
		order++;
		row++;
		}
	else
		break;
	}
}

void PY_OneIndex_dis(Int8U order, t9PINYIN_INDEX py_index, Int8U dis_flag)//һ��ƴ�� ��ʾ
{
Int16U x,y;
Int16U line_color,fill_color;
volatile pInt8U str;
if(dis_flag==0)
	{
	line_color=BLACK_COLOR;fill_color=WHITE_COLOR;
	}
else
	{
	line_color=WHITE_COLOR;fill_color=BLUE_COLOR;
	}
x=INPUT_SEL_X,y=INPUT_SEL_Y+(order%INPUT_SEL_ROW)*INPUT_SEL_GAP;
str=(pInt8U)py_index.pinyin_str;
Printf24(str,x,y,line_color,1,fill_color);
}

void PY_PageIndex_dis(Int8U index)		//һҳ ƴ����ʾ	��ʾ
{
Int8U row=0;
ClrInputHintText_dis();//��� ����ѡ���� ��ʾ
while(row<INPUT_SEL_ROW)
	{
	if(index<PY_index_sum)
		{
		PY_OneIndex_dis( row, *(List_match_PY_Mb[index]),  0);
		index++;
		row++;
		}
	else
		break;
	}
}

void HanziOneWord_dis(Int8U order, pInt8U hanzi, Int8U dis_flag)	//һ��������ʾ
{
Int16U x,y;
Int16U line_color,fill_color;
Int8U str[4];
if(dis_flag==0)
	{
	line_color=BLACK_COLOR;fill_color=WHITE_COLOR;
	}
else
	{
	line_color=WHITE_COLOR;fill_color=BLUE_COLOR;
	}
x=INPUT_LIB_X+(order%INPUT_WORD_COL)*INPUT_WORD_GAP, y=INPUT_LIB_Y+5;
str[0]=*hanzi++;
str[1]=*hanzi;
str[2]=0;
Printf24(str,x,y,line_color,1,fill_color);
}

void HanziPageWord_dis(Int8U order)	//һ��(��)������ʾ
{
Int16U x,y;
Int8U col=0,num;
Int16U line_color,fill_color;
line_color=fill_color=PRO_MESS_COLOR2;
x=INPUT_LIB_X, y=INPUT_LIB_Y+5;
GLCD_SetWindow_Fill(x, y, x+300, y+30, line_color, fill_color);//��� ���ֱ� ��ʾ
pHanzi_buf=(pInt8U)(*List_match_PY_Mb[PY_index_order]).t9_mb;
num=order<<1;
while(col<INPUT_WORD_COL)
	{
	if(*(pHanzi_buf+num)!='\0')
		{
		hanzi_temp[0]=*(pHanzi_buf+num);num++;
		hanzi_temp[1]=*(pHanzi_buf+num);num++;
		HanziOneWord_dis(order++, hanzi_temp,  0);
		col++;
		}
	else
		break;
	}
}

void ProNameInput_dis(Int8U num)
{
InputNum_sel=0;
volatile Int8U cou;
switch(InputMode)
	{
	case NUMBER_INPUT:	//���� ����
			if((num<=9)&&(num>=0))  //��Ч����
				{
				if(InputWord_cou<PRONAME_SIZE)
					{
					InputNameDisBuf[InputWord_cou++]=num+48;
					InputNameDisBuf[InputWord_cou]=0;
					ProNameDis_Window(); //������ ���� ��ʾ
					InputOK_flag=1;
					}
				}
			break;
	case CHAR_INPUT:	//��ĸ����
			switch(num)
				{
				case 1:
					pbuf_temp=(pInt8U)CH_1;
					InputLibDisplay_flag=1;
					break;
				case 2:
					pbuf_temp=(pInt8U)CH_ABC;
					InputLibDisplay_flag=1;
					break;
				case 3:
					pbuf_temp=(pInt8U)CH_DEF;
					InputLibDisplay_flag=1;
					break;	
				case 4:
					pbuf_temp=(pInt8U)CH_GHI;
					InputLibDisplay_flag=1;
					break;	
				case 5:
					pbuf_temp=(pInt8U)CH_JKL;
					InputLibDisplay_flag=1;
					break;
				case 6:
					pbuf_temp=(pInt8U)CH_MNO;
					InputLibDisplay_flag=1;
					break;	
				case 7:
					pbuf_temp=(pInt8U)CH_PQRS;
					InputLibDisplay_flag=1;
					break;	
				case 8:
					pbuf_temp=(pInt8U)CH_TUV;
					InputLibDisplay_flag=1;
					break;
				case 9:
					pbuf_temp=(pInt8U)CH_WXYZ;
					InputLibDisplay_flag=1;
					break;	
				case 0:
					pbuf_temp=(pInt8U)CH_NOP;
					InputLibDisplay_flag=1;
					break;	
				}
			if(InputLibDisplay_flag==1)// ��ĸ��Ч
				{
				Num_Char_PageDis(InputNum_sel, pbuf_temp);	//һҳ ��ʾ
				Num_Char_SelDis(InputNum_sel,pbuf_temp,1);	//һ�и��� ��ʾ
				}
			break;
	case PINYIN_INPUT:	//ƴ������
			if((num<=9)&&(num>=2))  //��Ч����
				{
				if(pinyin_cou<7)
					{
					PY_temp[pinyin_cou]=num+48;
					PY_temp[pinyin_cou+1]='\0';
					cou=T9PY_Get_Match_PY_MB(PY_temp,  pinyin_cou+1);	//   T9 ƴ����ѯ   ƥ����*********************************
					if(cou>0)
						{
						InputLibDisplay_flag=1;
						
						PY_index_sum=cou;	//  ƥ������
						PY_buf[pinyin_cou]=PY_temp[pinyin_cou];
						PY_buf[pinyin_cou+1]='\0';
						//-------------ƴ�� ��ʾ
						PY_index_order=0;
						PY_PageIndex_dis(PY_index_order);		//һҳ ƴ����ʾ	��ʾ
						PY_OneIndex_dis(PY_index_order, *(List_match_PY_Mb[PY_index_order]),  1);// һ�� ��Чhint
						//-------------������ʾ
						PY_hanzi_order=0;
						HanziPageWord_dis(PY_hanzi_order);	//һ��(��)������ʾ
						hanzi_temp[0]=*(pHanzi_buf+(PY_hanzi_order<<1));
						hanzi_temp[1]=*(pHanzi_buf+(PY_hanzi_order<<1)+1);
						HanziOneWord_dis(PY_hanzi_order,  hanzi_temp,  1);	//һ��������ʾ
						pinyin_cou++;
						}
					}
				}
			
			break;
	}
}

void DirKeySelInput_exec(Int8U key_flag)		//���¼�ͷѡ��	:SEL_UP==0 ,SEL_DOWN==1
{
Int8U disok_flag=0;
Int8U tempHanzi;
if(InputLibDisplay_flag==1)// ������Ч	
	{
	switch(key_flag)
		{
		case KEY_DOWN: //����
			switch(InputMode)
				{
				case CHAR_INPUT:	//��ĸ����
					if(pbuf_temp[InputNum_sel+1]!=0xaa)
						{
						if((InputNum_sel+1)%INPUT_SEL_ROW==0) //----------��ҳ
							{
							InputNum_sel++;
							Num_Char_PageDis(InputNum_sel, pbuf_temp);	//һҳ ��ʾ
							disok_flag=1;
							}
						else
							{
							Num_Char_SelDis(InputNum_sel,pbuf_temp,0);	//ȥ�� ����
							InputNum_sel++;
							disok_flag=1;
							}
						if(disok_flag==1)
							Num_Char_SelDis(InputNum_sel,pbuf_temp,1);	//����	
						}
						break;
				case PINYIN_INPUT:	//ƴ������
					if((PY_index_order+1)<PY_index_sum)
						{
						if((PY_index_order+1)%INPUT_SEL_ROW==0) //----------��ҳ
							{
							PY_index_order++;
							PY_PageIndex_dis(PY_index_order);		//һҳ ƴ����ʾ	��ʾ
							disok_flag=1;
							}
						else
							{
							PY_OneIndex_dis(PY_index_order, *(List_match_PY_Mb[PY_index_order]),  0);// һ��ƴ��
							PY_index_order++;
							disok_flag=1;
							}
						if(disok_flag==1)
							{
							PY_OneIndex_dis(PY_index_order, *(List_match_PY_Mb[PY_index_order]),  1);// һ��ƴ��	����
							//-------------������ʾ
							PY_hanzi_order=0;
							HanziPageWord_dis(PY_hanzi_order);	//һ��(��)������ʾ
							hanzi_temp[0]=*(pHanzi_buf+(PY_hanzi_order<<1));
							hanzi_temp[1]=*(pHanzi_buf+(PY_hanzi_order<<1)+1);
							HanziOneWord_dis(PY_hanzi_order,  hanzi_temp,  1);	//һ��������ʾ
							}
						}
						break;
				}		
				break;
		case KEY_UP:		//����
			switch(InputMode)
				{
				case CHAR_INPUT:	//��ĸ����
					if(InputNum_sel>0)
						{
						if(InputNum_sel%INPUT_SEL_ROW==0) //----------��ҳ
							{
							Num_Char_PageDis(InputNum_sel-INPUT_SEL_ROW, pbuf_temp);	//һҳ ��ʾ
							}
						else
							{
							Num_Char_SelDis(InputNum_sel,pbuf_temp,0);	//ȥ�� ����
							}
						InputNum_sel--;
						Num_Char_SelDis(InputNum_sel,pbuf_temp,1);	//����
						}
						break;
				case PINYIN_INPUT:	//ƴ������
					if(PY_index_order>0)
						{
						if(PY_index_order%INPUT_SEL_ROW==0) //----------ƴ����ҳ
							{
							PY_PageIndex_dis(PY_index_order-INPUT_SEL_ROW);		//һҳ ƴ����ʾ	��ʾ
							disok_flag=1;
							}
						else
							{
							PY_OneIndex_dis(PY_index_order, *(List_match_PY_Mb[PY_index_order]),  0);// һ��ƴ��
							disok_flag=1;
							}
						if(disok_flag==1)
							{
							PY_index_order--;
							PY_OneIndex_dis(PY_index_order, *(List_match_PY_Mb[PY_index_order]),  1);// һ��ƴ��	����
							//-------------������ʾ
							PY_hanzi_order=0;
							HanziPageWord_dis(PY_hanzi_order);	//һ��(��)������ʾ
							hanzi_temp[0]=*(pHanzi_buf+(PY_hanzi_order<<1));
							hanzi_temp[1]=*(pHanzi_buf+(PY_hanzi_order<<1)+1);
							HanziOneWord_dis(PY_hanzi_order,  hanzi_temp,  1);	//һ��������ʾ
							}
						}
						break;
				}
				break;
		case KEY_LEFT:	//��
			switch(InputMode)
				{
				case PINYIN_INPUT:	//ƴ������
					if(PY_hanzi_order>0)
						{
						if(PY_hanzi_order%INPUT_WORD_COL==0)	//-���ַ�ҳ
							{
							HanziPageWord_dis(PY_hanzi_order-INPUT_WORD_COL);	//һ��(��)������ʾ
							disok_flag=1;
							}
						else
							{
							hanzi_temp[0]=*(pHanzi_buf+(PY_hanzi_order<<1));
							hanzi_temp[1]=*(pHanzi_buf+(PY_hanzi_order<<1)+1);
							HanziOneWord_dis(PY_hanzi_order,  hanzi_temp,  0);	//һ��������ʾ
							disok_flag=1;
							}
						if(disok_flag==1)
							{
							PY_hanzi_order--;
							hanzi_temp[0]=*(pHanzi_buf+(PY_hanzi_order<<1));
							hanzi_temp[1]=*(pHanzi_buf+(PY_hanzi_order<<1)+1);
							HanziOneWord_dis(PY_hanzi_order,  hanzi_temp,  1);	//һ��������ʾ	����
							}
						}
						break;
				}
				break;
		case KEY_RIGHT:	//��
			switch(InputMode)
				{
				case PINYIN_INPUT:	//ƴ������
					tempHanzi=pHanzi_buf[(PY_hanzi_order+1)<<1];
					if(tempHanzi!='\0')
						{
						if((PY_hanzi_order+1)%INPUT_WORD_COL==0)	//-���ַ�ҳ
							{
							PY_hanzi_order++;
							HanziPageWord_dis(PY_hanzi_order);	//һ��(��)������ʾ
							disok_flag=1;
							}
						else
							{
							hanzi_temp[0]=*(pHanzi_buf+(PY_hanzi_order<<1));
							hanzi_temp[1]=*(pHanzi_buf+(PY_hanzi_order<<1)+1);
							HanziOneWord_dis(PY_hanzi_order,  hanzi_temp,  0);	//һ��������ʾ
							PY_hanzi_order++;
							disok_flag=1;
							}
						if(disok_flag==1)
							{
							hanzi_temp[0]=*(pHanzi_buf+(PY_hanzi_order<<1));
							hanzi_temp[1]=*(pHanzi_buf+(PY_hanzi_order<<1)+1);
							HanziOneWord_dis(PY_hanzi_order,  hanzi_temp,  1);	//һ��������ʾ	����
							}
						}
						break;
				}	
				break;		
		}
	}
}

void F4MessageMode_Exit(void) //�˳�  ������Ϣģʽ
{
CurrentArea_recover1(PRO_MESS_X,PRO_MESS_Y, PRO_MESS_WIDE,PRO_MESS_HIGH);
if(WorkMode==PROG_PRO_MESS_MODE)
	WorkMode=PROG_PRO_MODE;
else
	WorkMode=TEACH_PRO_MODE;
	//********************��ʾ
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
}

Int8U EnterInput_exec(Int8U cursor_pro,Int16U p_order)		//���� ȷ��
{
volatile Int8U buf=0,save_flag=0,k=0;
pInt8U pName=Pro_head_temp.pro_name_flag;
switch(InputMode)
	{
	case NUMBER_INPUT:	//���� ����
		
		save_flag=1;
			break;
	case CHAR_INPUT:	//��ĸ����
		if(InputLibDisplay_flag==1)// ��ĸ��Ч
			{
			InputLibDisplay_flag=0;
			InputOK_flag=1;
			if(InputWord_cou<PRONAME_SIZE)
				{
				InputNameDisBuf[InputWord_cou++]=pbuf_temp[InputNum_sel];
				InputNameDisBuf[InputWord_cou]=0;
				ProNameDis_Window(); //������ ���� ��ʾ
				ClrInputLib();	//��� ��ʾ��
				}
			}
		else
			{
			save_flag=1;
			/****
			if(InputWord_cou>0)	//������ ��� �򱣴�
				{
				while(buf<=InputWord_cou)
					{
					*pName++=InputNameDisBuf[buf++];
					}
				SavePro_headInfo(ProNumGroup[p_order], (pInt8U)&Pro_head_temp);	//����**************
				}	
				//����
			F4MessageMode_Exit(); //�˳�  ������Ϣģʽ	
			
			if(InputOK_flag==1)		//���� ��ʾ�б�-----------------
				{
				InputOK_flag=0;
				OneProgHeadInfo_dis(cursor_pro ,  p_order, 1);	//һ������ ��ʾ0
				}
				***/
			}
			break;
	case PINYIN_INPUT:	//ƴ�� ����
		if(InputLibDisplay_flag==1)// ƴ����Ч
			{
			InputLibDisplay_flag=0;
			InputOK_flag=1;
			if(InputWord_cou+1<PRONAME_SIZE)
				{
				InputNameDisBuf[InputWord_cou++]=hanzi_temp[0];
				InputNameDisBuf[InputWord_cou++]=hanzi_temp[1];
				InputNameDisBuf[InputWord_cou]=0;
				ProNameDis_Window(); //������ ���� ��ʾ
				ClrInputLib();	//��� ��ʾ��
				}
			}
		else
			{
			save_flag=1;
			//*******������ ��� �򱣴�
			}
			break;
	}	
	//****************************���洦��*************************
	
	// if(InputLibDisplay_flag==0)
	if(save_flag==1)
		{
		if(InputWord_cou>0)	//������ ��� �򱣴�
			{
			while(*(NAME_flag+k)!='\0')
				{
				*pName++=*(NAME_flag+k);
				k++;
				}
			*pName++='\0';	
			pName=Pro_head_temp.pro_name;
			while(buf<=InputWord_cou)
				{
				*pName++=InputNameDisBuf[buf++];
				}
			SavePro_headInfo(ProNumGroup[p_order], (pInt8U)&Pro_head_temp);	//����**************
			}	
			//����
		F4MessageMode_Exit(); //�˳�  ������Ϣģʽ	
		
		if(InputOK_flag==1)		//���� ��ʾ�б�-----------------
			{
			InputOK_flag=0;
			OneProgHeadInfo_dis(cursor_pro ,  p_order, 1);	//һ������ ��ʾ0
			}
		//*************************��ʾ	
		/***********
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
		************/
		}
return 	save_flag;
}

void ClrInputName_exec(void)		//����������
{
switch(InputMode)
	{
	case NUMBER_INPUT:	//���� ����
			if(InputOK_flag==1)	//������ ���
				ClrNameWindow();	//	��� ������
			break;
	case CHAR_INPUT:	//��ĸ����
	case PINYIN_INPUT:	//ƴ������
			if(InputLibDisplay_flag==1)
				{
				InputLibDisplay_flag=0;
				ClrInputLib();	//��� ��ʾ��
				}
			else
				{
				if(InputOK_flag==1)	//������ ���
					ClrNameWindow();	//	��� ������
				}
			
			break;
	}	
}



