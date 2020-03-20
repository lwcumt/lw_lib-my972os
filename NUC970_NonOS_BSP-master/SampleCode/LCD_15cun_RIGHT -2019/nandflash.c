
#include "nandflash.h"
#include"nand_config.h"



//------------nandflash----
unsigned int NandID;
Int8U NandEccWrite_Flag;

pInt8U pNF_ComdAdd=(pInt8U)NANDFLASH_COMMAND_ADDR;//����
pInt8U pNF_AddrAdd=(pInt8U)NANDFLASH_ADDRESS_ADDR;//��ַ
pInt8U pNF_DataAdd=(pInt8U)NANDFLASH_DATA_ADDR;   //����


// Int16U InvalidBlock[NF_BLOCKS];//����洢
unsigned short Nf_InvalidCou;


//---------------nand ��д-------------
void NF_WriteCOMMD(Int8U cmd)//д ����
{
//MLC->mlc_cmd=cmd;
outpw(REG_NANDCMD, cmd & 0xff);
}

void NF_WriteADDR(Int32U add)//д ��ַ
{
//MLC->mlc_addr =add;
outpw(REG_NANDADDR, add);
}

void NF_WriteDATA(Int8U data)//д ����
{
//MLC->mlc_data[0]=data;
outpw(REG_NANDDATA, data & 0xff);	
}

void NF_WriteBUFF(Int8U data)//д ����
{
//MLC->mlc_buff[0]=data;
outpw(REG_NANDDATA, data & 0xff);	
}


Int8U NF_ReadDATA(void)//�� ����
{
Int8U data;
//data=(Int8U)MLC->mlc_data;//*pNF_DataAdd;

data=inpw(REG_NANDDATA);
	   return (data);

}

void NF_WaitBusy(void)//-------------------æ�ȴ�
{
/*
   while(NAND_RB_PIN==1);//��æ�ź�
   while(NAND_RB_PIN==0);//��æ�ź�

   */

    // while (!(MLC->mlc_isr & MLC_DEV_RDY_STS));
	  while (!(inpw(REG_NANDINTSTS) & READYBUSY));
}
/*
void delay(Int16U d)
{
while(d--);
}
*/


void delay(Int16U d)
{
while(d--);
}


//----------------------nand  ���ݲ���--------------
Int8U Nand_ReadStatus(void)//��״̬0x70
{
	/*
Int8U s;
NF_WriteCOMMD(READ_STATUS_CMMD); 
NF_WaitBusy();
//delay(200);
s=(Int8U)MLC->mlc_data[0];//NF_ReadDATA();
return s;
*/
Int8U s;
NF_WriteCOMMD(READ_STATUS_CMMD); 
//delay(200);
s=NF_ReadDATA();
return s;
}



//-------��λnand-------------
void Nand_Reset(void)
{
NAND_CS_EN();//Ƭѡ
 NF_WriteCOMMD(RESET_CMMD);//��λ���� 0xff
 NF_WaitBusy();
NAND_CS_DIS();//��ֹ
}

//-----------��id--------------
void Nand_ReadID(void)
{
unsigned int idtemp;
NAND_CS_EN();//Ƭѡ

NF_WriteCOMMD(READ_ID_CMMD);//ReadID���� 0x90
NF_WriteADDR(0|ENDADDR);
NF_WaitBusy();

NandID=NF_ReadDATA();
NandID<<=24;
idtemp=NF_ReadDATA();
idtemp<<=16;
NandID|=idtemp;
idtemp=NF_ReadDATA();
idtemp<<=8;
NandID|=idtemp;
idtemp=NF_ReadDATA();
NandID|=idtemp;

NAND_CS_DIS();//��ֹ

}


#if NAND_TYPE==HY27US0856
Int8U Nand_EraseBlock(Int16U block)//�����(A14~A24)
{
unsigned int i;
unsigned char row1,row2,shift;

shift=14-9;  //A14--
row1=(unsigned char)(block<<shift);
row2=(unsigned char)(block>>(8-shift));

//NAND_CS_EN();//Ƭѡ

NF_WriteCOMMD(BLOCK_ERASE_CMMD1);//0x60 �ÿ����
//delay(10);
NF_WriteADDR(row1);
NF_WriteADDR(row2);

NF_WriteCOMMD(BLOCK_ERASE_CMMD2);//�ÿ����   0xD0
//delay(200);
NF_WaitBusy();//æ�ź�
////NAND_CS_DIS();//��ֹ
 
////NAND_CS_EN();//Ƭѡ
i=Nand_ReadStatus();//��״̬0x70
//NAND_CS_DIS();//��ֹ
if(i&0x1)
	return 1;  //����
else
	return 0; //����
}


Int8U Nand_WriteBytes(pInt8U databuf,Int32U nandadd)//����Ե�ַд ���� ------------     nandadd��nand���Ե�ַ           databuf:���ݻ�����
{
unsigned char i;
unsigned int d;
unsigned char colum,row1,row2;
//unsigned int pagebytes;
//coladd=(nandadd&PAGE_MASK);//ҳ�ڵ�ַ
colum=(unsigned char)(nandadd&PAGE_MASK);//ҳ�ڵ�ַ
//rowadd=nandadd/NF_PAGE_BYTES;//
row1=(unsigned char)(nandadd>>9);//
row2=(unsigned char)(nandadd>>17);//

////NAND_CS_EN();//Ƭѡ
i=nandadd&0x100;
if(i==0x100)
   {
    NF_WriteCOMMD(READ1_HIGH_CMMD);//01 ������255~512
   }
else
   {
    NF_WriteCOMMD(READ1_LOW_CMMD);//00 ������0~255
   }
//delay(20);   
NF_WriteCOMMD(PAGE_PROGRAM_CMMD1);  //��ҳд  0x80
delay(50);
NF_WriteADDR(colum);
NF_WriteADDR(row1);
NF_WriteADDR(row2);
//delay(50);
for(d=0;d<(NF_PAGE_BYTES/4);d++)//----������
   {
  // NF_WaitBusy();//æ�ź�
//   NF_WriteDATA(databuf[d]);
	NF_WriteDATA(*((Int32U *)(databuf)));//sNF_WriteDATA(databuf[d]);
	databuf+=4;
   }
//delay(20);
NF_WriteCOMMD(PAGE_PROGRAM_CMMD2);  //��ҳд  0x10

//NandFlash_DIS_CE();
delay(50); //��ҳд���
NF_WaitBusy();//æ�ź�
i=Nand_ReadStatus();//��״̬0x70
//NAND_CS_DIS();//��ֹ
if(i&0x1)
	return 1;  //����
else
	return 0; //����
}




void Nand_Read_1page(pInt8U databuf,Int32U page)//=======****====��һ����ҳ���� -    page:����ҳ(��512 Byte)
{
unsigned char i;
unsigned int d;
unsigned char colum,row1,row2;
/*
i=4;
while(i--);
*pNF_ComdAdd=0x00; //��Ϊ������
i=nandadd;
i&=0xfff;//ȡ����12λ��ַ(��28λ)
*pNF_AddrAdd=(unsigned char)i;//��ַ��8λ
*pNF_AddrAdd=(unsigned char)(i>>8);//��ַ��4λ
i=(nandadd>>12);
i&=0xffff;//��λ��ַ
*pNF_AddrAdd=(unsigned char)i;//��8λ
*pNF_AddrAdd=(unsigned char)(i>>8);//��8λ

*pNF_ComdAdd=0x30;//������

//NAND_CS_DIS();//��ֹ
NF_WaitBusy();//æ�ź�

//i=1000;
//while(i--);
//NAND_CS_EN();//Ƭѡ

for(i=0;i<NF_PAGE_BYTES;i++)
	*databuf++=NF_ReadDATA();
//NAND_CS_DIS();//��ֹ
*/
row1=(unsigned char)page;
row2=(unsigned char)(page>>8);  //ע�⣺============��ַ�� 512 һҳ ����

//NAND_CS_EN();//Ƭѡ
NF_WriteCOMMD(READ1_LOW_CMMD);//00 ������0~255
delay(50);
NF_WriteADDR(0);
NF_WriteADDR(row1);
NF_WriteADDR(row2);
NF_WaitBusy();//æ�ź�
for(d=0;d<NF_PAGE_BYTES;d++)//
   databuf[d]=NF_ReadDATA();
delay(20);  
//NAND_CS_DIS();//��ֹ
}

void Nand_ReadBytes(pInt8U databuf,Int32U nandadd,Int32U size)//��<=1page���� -------------- nandadd:���Ե�ַ
{
unsigned int i;
unsigned int d;
unsigned char colum,row1,row2;
Int32U j;
colum=(unsigned char)nandadd;
row1=(unsigned char)(nandadd>>9);
row2=(unsigned char)(nandadd>>17);

//NAND_CS_EN();//Ƭѡ
i=nandadd&0x100;
if(i==0x100)
   {
    NF_WriteCOMMD(READ1_HIGH_CMMD);//01 ������255~512
   }
else
   {
    NF_WriteCOMMD(READ1_LOW_CMMD);//00 ������0~255
   }
delay(50);
 NF_WriteADDR(colum);
 NF_WriteADDR(row1);
 NF_WriteADDR(row2);
 NF_WaitBusy();//æ�ź�
for(d=0;d<size;d++)////��С��size����
   *databuf++=NF_ReadDATA();

delay(50);  
//NAND_CS_DIS();//��ֹ
}

void Nand_ReadDates(pInt8U databuf,Int32U nandadd,Int32U size)// �������ַ�����ⳤ�� ����#############################
{
Int32U page,offset;
Int32U p,cou;

page=size>>9;
offset=size&PAGE_MASK;
if(page>0)
  {
  for(p=0;p<page;p++)
    {
	Nand_ReadBytes(databuf, nandadd, NF_PAGE_BYTES);
	nandadd+=NF_PAGE_BYTES;
	databuf+=NF_PAGE_BYTES;
	}
  }
if(offset>0)
    Nand_ReadBytes(databuf, nandadd, offset); 

}


/*
void Nand_FillPageOfBlock(unsigned short page,unsigned int bytes,unsigned char filldata)  //���sdram���һҳ
{
int i;
unsigned char *pSdbuf;
pSdbuf=(unsigned char *)NF_COPY_SDRAM_ADD;
pSdbuf+=page*FILE_INFO_NUM;

for(i=0;i<bytes;i++)//���һҳ
	{
	*pSdbuf++=filldata;
	}
}*/
#elif NAND_TYPE==K9F1G08//----------K9F1G08 ------- 128MB
Int8U Nand_EraseBlock(Int32U block)//�����(A18~A27)***********��
{
	/*
unsigned int i;
unsigned char row1,row2,shift;

shift=18-12;  //A14--
//row1=(unsigned char)(block<<shift);
//row2=(unsigned char)(block>>(8-shift));
row1=(unsigned char)block;
row2=(unsigned char)(block>>8);

////NAND_CS_EN();//Ƭѡ

NF_WriteCOMMD(BLOCK_ERASE_CMMD1);//0x60 �ÿ����
delay(100);
NF_WriteADDR(row1);
NF_WriteADDR(row2);

NF_WriteCOMMD(BLOCK_ERASE_CMMD2);//�ÿ����   0xD0
delay(500);
NF_WaitBusy();//æ�ź�

i=Nand_ReadStatus();//��״̬0x70
//while((i&0xE0)!=0xE0);
////NAND_CS_DIS();//��ֹ
if(i&0x1)
	return 1;  //����
else
	return 0; //����
*/

unsigned int i;
unsigned char row1,row2,shift;

shift=18-12;  //A14--
row1=(unsigned char)(block<<shift);
row2=(unsigned char)(block>>(8-shift));
// row1=(unsigned char)block;
// row2=(unsigned char)(block>>8);

/*
shift=18-12;  //A14--
row1=(unsigned char)(block<<shift);
row2=(unsigned char)(block>>(8-shift));
//row1=(unsigned char)block;
//row2=(unsigned char)(block>>8);
*/
NAND_CS_EN();//Ƭѡ

NF_WriteCOMMD(BLOCK_ERASE_CMMD1);//0x60 �ÿ����
delay(5);
NF_WriteADDR(row1);
NF_WriteADDR((Int32U)row2|ENDADDR);

NF_WriteCOMMD(BLOCK_ERASE_CMMD2);//�ÿ����   0xD0
delay(1000);
NF_WaitBusy();//æ�ź�

i=Nand_ReadStatus();//��״̬0x70
//while((i&0xE0)!=0xE0);
NAND_CS_DIS();//��ֹ
if(i&0x1)
	return 1;  //����
else
	return 0; //����

}


Int8U Nand_WriteBytes(pInt8U databuf,Int32U nandadd)//����Ե�ַд ���� ------------     nandadd��nand���Ե�ַ           databuf:���ݻ�����
{

	/*
unsigned char i;
unsigned int d;
unsigned char colum1,colum2,row1,row2;
//unsigned int pagebytes;
//coladd=(nandadd&PAGE_MASK);//ҳ�ڵ�ַ
colum1=(unsigned char)(nandadd);//ҳ�ڵ�ַ
colum2=(unsigned char)((nandadd&PAGE_MASK)>>8);//ҳ�ڵ�ַ
//rowadd=nandadd/NF_PAGE_BYTES;//
row1=(unsigned char)(nandadd>>11);//
row2=(unsigned char)(nandadd>>19);//
////NAND_CS_EN();//Ƭѡ
//delay(20);   
NF_WriteCOMMD(PAGE_PROGRAM_CMMD1);  //��ҳд  0x80
delay(30);
NF_WriteADDR(colum1);
NF_WriteADDR(colum2);
NF_WriteADDR(row1);
NF_WriteADDR(row2);
delay(50);
for(d=0;d<(NF_PAGE_BYTES/4);d++)//----������
   {
	NF_WriteDATA(*((Int32U *)(databuf)));//sNF_WriteDATA(databuf[d]);
	databuf+=4;
   //NF_WriteDATA(databuf[d]);
   }

//delay(20);
NF_WriteCOMMD(PAGE_PROGRAM_CMMD2);  //��ҳд  0x10

//NandFlash_DIS_CE();
delay(50); //��ҳд���
NF_WaitBusy();//æ�ź�
i=Nand_ReadStatus();//��״̬0x70
//while((i&0xE0)!=0xE0);
////NAND_CS_DIS();//��ֹ
if(i&0x1)
	return 1;  //����
else
	return 0; //����

	*/

unsigned char i;
unsigned int d;
unsigned char colum1,colum2,row1,row2;
//unsigned int pagebytes;
//coladd=(nandadd&PAGE_MASK);//ҳ�ڵ�ַ
colum1=(unsigned char)(nandadd);//ҳ�ڵ�ַ
colum2=(unsigned char)((nandadd&PAGE_MASK)>>8);//ҳ�ڵ�ַ
//rowadd=nandadd/NF_PAGE_BYTES;//
row1=(unsigned char)(nandadd>>11);//
row2=(unsigned char)(nandadd>>19);//

NAND_CS_EN();//Ƭѡ

//delay(20);   
NF_WriteCOMMD(PAGE_PROGRAM_CMMD1);  //��ҳд  0x80
delay(5);
NF_WriteADDR(colum1);
NF_WriteADDR(colum2);
NF_WriteADDR(row1);
NF_WriteADDR((Int32U)row2|ENDADDR);
delay(10);
for(d=0;d<NF_PAGE_BYTES;d++)//----������
   {
   NF_WriteDATA(*databuf++);
   }
//delay(20);
NF_WriteCOMMD(PAGE_PROGRAM_CMMD2);  //��ҳд  0x10

//NandFlash_DIS_CE();
delay(20); //��ҳд���
NF_WaitBusy();//æ�ź�
i=Nand_ReadStatus();//��״̬0x70
//while((i&0xE0)!=0xE0);
NAND_CS_DIS();//��ֹ
if(i&0x1)
	return 1;  //����
else
	return 0; //����
}


Int8U Nand_Write_1Page(pInt8U databuf,Int32U page)//=====***=====дһ����ҳ ���� -    page����ҳ��ַ           databuf:���ݻ�����
{
///*
unsigned char i;
unsigned int d,n;
unsigned char row1,row2;
Int8U *pd;
Int32U ddd;
// if(NandEccWrite_Flag==0)
	// {
	// return(Nand_Write_1Page_1(databuf,page));//=====***=====дһ����ҳ ���� -    page����ҳ��ַ           databuf:���ݻ�����
	// }
// else
	// {
row1=(unsigned char)page;//
row2=(unsigned char)(page>>8);     //ע�⣺===========��ַ�� 2K һҳ ����

NAND_CS_EN();//Ƭѡ

NF_WriteCOMMD(PAGE_PROGRAM_CMMD1);  //��ҳд  0x80
delay(5);
NF_WriteADDR(0);
NF_WriteADDR(0);
NF_WriteADDR(row1);
NF_WriteADDR((Int32U)row2|ENDADDR);//NF_WriteADDR(row2);
delay(10);
for(d=0;d<NF_PAGE_BYTES;d++)//----������
	NF_WriteDATA(*databuf++);
/*

for(n=0;n<(NF_PAGE_BYTES/512);n++)
	{
	    MLC->mlc_enc_ecc = 0;

for(d=0;d<(512/4);d++)//----������
	{
	//NF_WriteDATA(databuf[d]);
//	MLC->mlc_buff=*((Int32U *)(databuf));
	NF_WriteBUFF(*((Int32U *)(databuf)));//sNF_WriteDATA(databuf[d]);
//	ddd=*((Int32U *)(databuf));
	databuf+=4;
	}

		 pd=(Int8U *)MLC->mlc_buff;
    	*pd=0xFF;// *pNF_DataAdd;
        *pd=0xFF;// *pNF_DataAdd;
        *pd=0xFF;// *pNF_DataAdd;
        *pd=0xFF;// *pNF_DataAdd;
        *pd=0xFF;// *pNF_DataAdd;
        *pd=0xFF;// *pNF_DataAdd;
    //    * /

 //   / * ECC Auto Encode * /
    MLC->mlc_autoenc_enc = 0;
 //   / * Wait for Device to ready * /
	  while (!(MLC->mlc_isr & MLC_CNTRLLR_RDY_STS));
	  //NF_WaitBusy();//æ�ź�
	
  }

*/
delay(10);
NF_WriteCOMMD(PAGE_PROGRAM_CMMD2);  //��ҳд  0x10
//NandFlash_DIS_CE();
delay(20); //��ҳд���
NF_WaitBusy();//æ�ź�
i=Nand_ReadStatus();//��״̬0x70
//while((i&0xE0)!=0xE0);
NAND_CS_DIS();//��ֹ
if(i&0x1)
	return 1;  //����
else
	return 0; //����
	// }

}


Int8U Nand_Write_1Page_1(pInt8U databuf,Int32U page)//=====***=====дһ����ҳ ���� -    page����ҳ��ַ           databuf:���ݻ�����
{
/*
unsigned char i;
unsigned int d;
unsigned char col1,col2,row1,row2;

//rowadd=nandadd/NF_PAGE_BYTES;//ҳ��
col1=(unsigned char)page&0x7ff;
col2=(unsigned char)((page&0x7ff)>>8);
page/=2048;
row1=(unsigned char)page;//
row2=(unsigned char)(page>>8);     //ע�⣺===========��ַ�� 512 һҳ ����

////NAND_CS_EN();//Ƭѡ

NF_WriteCOMMD(PAGE_PROGRAM_CMMD1);  //��ҳд  0x80
delay(30);
NF_WriteADDR(col1);
NF_WriteADDR(col2);
NF_WriteADDR(row1);
NF_WriteADDR(row2);
delay(50);

for(d=0;d<(NF_PAGE_BYTES/4);d++)//----������
	{
	//NF_WriteDATA(databuf[d]);
	NF_WriteDATA(*((UNS_32 *)(databuf)));//sNF_WriteDATA(databuf[d]);
//	ddd=*((UNS_32 *)(databuf));
	databuf+=4;
	}
delay(100);
NF_WriteCOMMD(PAGE_PROGRAM_CMMD2);  //��ҳд  0x10

//NandFlash_DIS_CE();
delay(200); //��ҳд���
NF_WaitBusy();//æ�ź�
i=Nand_ReadStatus();//��״̬0x70
//NAND_CS_DIS();//��ֹ
if(i&0x1)
	return 1;  //����
else
	return 0; //����

*/

	unsigned char i;
unsigned int d;
unsigned char col1,col2,row1,row2;

//rowadd=nandadd/NF_PAGE_BYTES;//ҳ��
col1=(unsigned char)page&0x7ff;
col2=(unsigned char)((page&0x7ff)>>8);
page/=2048;
row1=(unsigned char)page;//
row2=(unsigned char)(page>>8);     //ע�⣺===========��ַ�� 512 һҳ ����

NAND_CS_EN();//Ƭѡ

NF_WriteCOMMD(PAGE_PROGRAM_CMMD1);  //��ҳд  0x80
delay(5);
NF_WriteADDR(col1);
NF_WriteADDR(col2);
NF_WriteADDR(row1);
NF_WriteADDR((Int32U)row2|ENDADDR);

delay(10);
for(d=0;d<NF_PAGE_BYTES;d++)//----������
	NF_WriteDATA(*databuf++);

delay(10);
NF_WriteCOMMD(PAGE_PROGRAM_CMMD2);  //��ҳд  0x10

//NandFlash_DIS_CE();
delay(20); //��ҳд���
NF_WaitBusy();//æ�ź�
i=Nand_ReadStatus();//��״̬0x70
//while((i&0xE0)!=0xE0);
NAND_CS_DIS();//��ֹ
if(i&0x1)
	return 1;  //����
else
	return 0; //����

}


void Nand_Read_1page(pInt8U databuf,Int32U page)//=======****====��һ����ҳ���� -    page:����ҳ(��2k Byte)
{

	/*
unsigned char i;
unsigned int d;
unsigned char row1,row2;
Int32U d_temp;
Int32U *ndata;
ndata=(Int32U*)MLC->mlc_data;

row1=(unsigned char)page;//
row2=(unsigned char)(page>>8);     //ע�⣺===========��ַ�� 2K һҳ ����

////NAND_CS_EN();//Ƭѡ
NF_WriteCOMMD(READ_CMMD1);//00 ������
//delay(5);
NF_WriteADDR(0);
NF_WriteADDR(0);
NF_WriteADDR(row1);
NF_WriteADDR(row2);
NF_WriteCOMMD(READ_CMMD2);//30 ������
delay(50);
NF_WaitBusy();//æ�ź�
i=0;
for(d=0;d<=(NF_PAGE_BYTES/4);d++)//
	{

   d_temp=*ndata++;
   *(databuf+i)=(Int8U)d_temp;
   i++;
   if(i>=NF_PAGE_BYTES)
	   break;
   *(databuf+i)=(Int8U)(d_temp>>8);
   i++;
   if(i>=NF_PAGE_BYTES)
	   break;
   *(databuf+i)=(Int8U)(d_temp>>16);
   i++;
   if(i>=NF_PAGE_BYTES)
	   break;
   *(databuf+i)=(Int8U)(d_temp>>24);
   i++;
   if(i>=NF_PAGE_BYTES)
	   break;
	}
//delay(20);  
////NAND_CS_DIS();//��ֹ

*/



unsigned char i;
unsigned int d;
unsigned char row1,row2;

row1=(unsigned char)page;//
row2=(unsigned char)(page>>8);     //ע�⣺===========��ַ�� 2K һҳ ����

NAND_CS_EN();//Ƭѡ
NF_WriteCOMMD(READ_CMMD1);//00 ������
//delay(5);
NF_WriteADDR(0);
NF_WriteADDR(0);
NF_WriteADDR(row1);
NF_WriteADDR((Int32U)row2|ENDADDR);
NF_WriteCOMMD(READ_CMMD2);//30 ������
delay(10);
NF_WaitBusy();//æ�ź�
for(d=0;d<NF_PAGE_BYTES;d++)//
   *databuf++=NF_ReadDATA();
//delay(20);  
NAND_CS_DIS();//��ֹ


}

void Nand_ReadBytes(pInt8U databuf,Int32U nandadd,Int32U size)//��<=1page���� -------------- nandadd:���Ե�ַ
{

	/*
unsigned int i;
unsigned int d;
unsigned char colum1,colum2,row1,row2;
Int32U d_temp;
Int32U *ndata;
ndata=(Int32U*)MLC->mlc_data;

colum1=(unsigned char)(nandadd);//ҳ�ڵ�ַ
colum2=(unsigned char)((nandadd&PAGE_MASK)>>8);//ҳ�ڵ�ַ
row1=(unsigned char)(nandadd>>11);//
row2=(unsigned char)(nandadd>>19);//
////NAND_CS_EN();//Ƭѡ
NF_WriteCOMMD(READ_CMMD1);//00 ������
//delay(15);
NF_WriteADDR(colum1);
NF_WriteADDR(colum2);
NF_WriteADDR(row1);
NF_WriteADDR(row2);
NF_WriteCOMMD(READ_CMMD2);//30 ������
delay(50);
NF_WaitBusy();//æ�ź�
i=0;
for(d=0;d<=(size/4);d++)////��С��size����
	{
   // *((Int32U *)(databuf))=*ndata++;//NF_ReadDATA();
   d_temp=*ndata++;
   *(databuf+i)=(Int8U)d_temp;
   i++;
   if(i>=size)
	   break;
   *(databuf+i)=(Int8U)(d_temp>>8);
   i++;
   if(i>=size)
	   break;
   *(databuf+i)=(Int8U)(d_temp>>16);
   i++;
   if(i>=size)
	   break;
   *(databuf+i)=(Int8U)(d_temp>>24);
   i++;
   if(i>=size)
	   break;
	}
//delay(10);  
////NAND_CS_DIS();//��ֹ


*/


unsigned int i;
unsigned int d;
unsigned char colum1,colum2,row1,row2;
Int32U j;
colum1=(unsigned char)(nandadd);//ҳ�ڵ�ַ
colum2=(unsigned char)((nandadd&PAGE_MASK)>>8);//ҳ�ڵ�ַ
row1=(unsigned char)(nandadd>>11);//
row2=(unsigned char)(nandadd>>19);//
NAND_CS_EN();//Ƭѡ
NF_WriteCOMMD(READ_CMMD1);//00 ������
//delay(15);
NF_WriteADDR(colum1);
NF_WriteADDR(colum2);
NF_WriteADDR(row1);
NF_WriteADDR((Int32U)row2|ENDADDR);
NF_WriteCOMMD(READ_CMMD2);//30 ������
delay(10);
NF_WaitBusy();//æ�ź�
for(d=0;d<size;d++)////��С��size����
   *databuf++=NF_ReadDATA();
//delay(10);  
NAND_CS_DIS();//��ֹ


}

void Nand_ReadDates(pInt8U databuf,Int32U nandadd,Int32U size)// �������ַ�����ⳤ�� ����#############################
{

Int32U offset;
Int32U length;
offset=nandadd&PAGE_MASK;
length=NF_PAGE_BYTES-offset;
if(size<=length)//����һҳ
  {
	//	Printf24("����һҳ",0,0,0,1,0xf7a2);
  Nand_ReadBytes(databuf, nandadd, size);
  }
else
  {
	//	Printf24("����һҳ",0,0,0,1,0xf7a2);
  Nand_ReadBytes(databuf, nandadd, length);
  size-=length;
  databuf+=length;
  nandadd+=length;
  while(size>0)
     {
	 if(size>=NF_PAGE_BYTES)
	   {
		// Printf24("���� ѭ��",0,0,0,1,0xf7a2);
	   Nand_ReadBytes(databuf, nandadd, NF_PAGE_BYTES);
			 // Printf24("���� ѭ�� ���",0,0,0,1,0xf7a2);
	   size-=NF_PAGE_BYTES;
	   databuf+=NF_PAGE_BYTES;
	   nandadd+=NF_PAGE_BYTES;
	   }
	 else
	   {
	   Nand_ReadBytes(databuf, nandadd, size);
	   size=0;
	   }
	 }
  }


}

#endif



void Nand_ReadBlock(unsigned int block,unsigned char *pSDbuf) //��ȡһ�� ��sdram ������    (nand ----> sdram)
{
	
unsigned int pcou,padd;
padd=block*NF_BLOCK_PAGES;//��ͷ  ҳ��ַ
  
// padd=block*128*1024;//��ͷ  ҳ��ַ
  // Nand_ReadDates(pSDbuf,padd,128*2048);
 
 /*
  unsigned int pcou,padd;
 padd=block*NF_BLOCK_BYTES;//��ͷ  ҳ��ַ

 Nand_ReadDates(pSDbuf,padd,128*2048);
*/
 for(pcou=0;pcou<NF_BLOCK_PAGES;pcou++)
	{
	Nand_Read_1page(pSDbuf, padd++);  //����һҳ
	pSDbuf+=NF_PAGE_BYTES;//��һҳ��ַ
	}
}

void Nand_WriteBlock(unsigned int block,unsigned char *pSDbuf)//sdram���ݻ�д��nandһ��  (sdram ---> nand)
{

unsigned int pcou,padd;
padd=block*NF_BLOCK_PAGES;//��ͷ  ҳ��ַ
 // padd=block*128*1024;
for(pcou=0;pcou<NF_BLOCK_PAGES;pcou++)
	{
	Nand_Write_1Page(pSDbuf, padd++);//дһҳ
	pSDbuf+=NF_PAGE_BYTES;//��һҳ��ַ
	}
	
/*
unsigned int pcou,padd;
 padd=block*128*1024;//��ͷ  ҳ��ַ
for(pcou=0;pcou<NF_BLOCK_PAGES;pcou++)
	{
	Nand_Write_1Page(pSDbuf, padd+pcou*2048);//дһҳ
	pSDbuf+=NF_PAGE_BYTES;//��һҳ��ַ
	}*/
}
