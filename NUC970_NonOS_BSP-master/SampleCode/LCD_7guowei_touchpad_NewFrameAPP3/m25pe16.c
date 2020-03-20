#include"m25pe16.h"

Int8U Chip_id[20];

//--------------------������---------------------
void Read_DevID(void)//��id
{
Int8U i;
FlashChip_En;
SpiTranserByte(READ_CHIP_ID_COMM);
Chip_id[0]=SpiTranserByte(0);
Chip_id[1]=SpiTranserByte(0);
Chip_id[2]=SpiTranserByte(0);

for(i=3;i<20;i++)
Chip_id[i]=SpiTranserByte(0);

FlashChip_Dis;
}

Int8U Read_Status(void)//---��״̬
{
Int8U reg;
FlashChip_En;
SpiTranserByte(READ_STATUS_COMM);
reg=SpiTranserByte(0);
FlashChip_Dis;
return reg;
}

Int8U Wait_Busy(void)//æ�ж�  1:æ
{
Int8U st;Int16U i=0;

while(i<0x1fff)
  {
   st=Read_Status();
   if((st&0x01)!=0)//æ
     {
     i++;
     }
   else 
     break;
  }
if(i>=0x1fff) 
   return 1;
else
   return 0;
}


void Read_Datas_Start(Int32U  add)//������   ��add:�ֽڵ�ַ��
{
//Spi0_start();  
Wait_Busy();////æ�ж�

FlashChip_En;

SpiTranserByte(READ_DATA_COMM);//��ʹ��
SpiTranserByte((add>>16)&0xff);//��ʼ��ַ
SpiTranserByte((add>>8)&0xff);
SpiTranserByte(add&0xff);

}

void FastRead_Datas_Start(Int32U  add)//�������   ��add:�ֽڵ�ַ��
{
//Spi0_start();   
Wait_Busy();////æ�ж�

FlashChip_En;

SpiTranserByte(FAST_READ_DATA_COMM);//��ʹ��
SpiTranserByte((add>>16)&0xff);//��ʼ��ַ
SpiTranserByte((add>>8)&0xff);
SpiTranserByte(add&0xff);
SpiTranserByte(0);
}

Int8U ReadFlash_Datas(void)//������
{
return(SpiTranserByte(0));
}

//----------------------��������-----------
void Page_Erase(Int32U   page)//*****ҳ����
{
Wait_Busy();
Write_En();//дʹ��

FlashChip_En;
SpiTranserByte(PAGE_ERASE_COMM);//����
SpiTranserByte((page>>8)&0xff);//
SpiTranserByte(page&0xff);
SpiTranserByte(0);
FlashChip_Dis;
}

void Sector_Erase(Int32U   sector)//*****��������
{
Wait_Busy();
Write_En();//дʹ��

FlashChip_En;
SpiTranserByte(SECTOR_ERASE_COMM);//����
sector<<=4;
SpiTranserByte((sector>>8)&0xff);//
SpiTranserByte(sector&0xff);
SpiTranserByte(0);
FlashChip_Dis;
}

void Block_Erase(Int32U   block)//*****�����
{
Wait_Busy();
Write_En();//дʹ��

FlashChip_En;
SpiTranserByte(BLOCK_ERASE_COMM);//����
SpiTranserByte(block&0xff);//
SpiTranserByte(0);
SpiTranserByte(0);
FlashChip_Dis;
}

void Chip_Erase(void)//*****��Ƭ����
{
Wait_Busy();
Write_En();//дʹ��

FlashChip_En;
SpiTranserByte(CHIP_ERASE_COMM);//����
FlashChip_Dis;
}

//--------------------д����----------------------

void Write_En(void)//дʹ��
{
FlashChip_En;
SpiTranserByte(WRITE_EN_COMM);
FlashChip_Dis;
}

void Write_Dis(void)//д��ֹ
{
FlashChip_En;
SpiTranserByte(WRITE_DIS_COMM);
FlashChip_Dis;
}

void Page_Program(pInt8U   wbuf,   Int32U   page,   Int16U   length)//*****ҳ���
{
Int16U n;
Page_Erase(page);//�Ȳ���
Wait_Busy();
Wait_Busy();
Write_En();//дʹ��

FlashChip_En;
SpiTranserByte(PAGE_PROGRAM_COMM);//�������
SpiTranserByte((page>>8)&0xff);//
SpiTranserByte(page&0xff);
SpiTranserByte(0);

for(n=0;n<length;n++)
  {
   SpiTranserByte(*wbuf);
   wbuf++;
  }

FlashChip_Dis;
//Write_Dis();//д��ֹ
}


void Page_Write(pInt8U   wbuf,   Int32U   page,   Int16U   length)//*****ҳд
{
Int16U n;
Wait_Busy();
Write_En();//дʹ��

FlashChip_En;
SpiTranserByte(PAGE_WRITE_COMM);//д����
SpiTranserByte((page>>8)&0xff);//
SpiTranserByte(page&0xff);
SpiTranserByte(0);

for(n=0;n<length;n++)
  {
   SpiTranserByte(*wbuf);
   wbuf++;
  }

FlashChip_Dis;
//Write_Dis();//д��ֹ
}

void Bytes_Write(pInt8U   wbuf,   Int32U  add,   Int16U   length)//*****�ֽ�д
{
Int16U n;
Wait_Busy();
Write_En();//дʹ��
FlashChip_En;
SpiTranserByte(PAGE_WRITE_COMM);//д����
SpiTranserByte((add>>16)&0xff);//
SpiTranserByte((add>>8)&0xff);
SpiTranserByte(add&0xff);

for(n=0;n<length;n++)
  {
   SpiTranserByte(*wbuf);
   wbuf++;
  }

FlashChip_Dis;
//Write_Dis();//д��ֹ
}


//***************************д���ⳤ������*****
void Write_25pe_data(pInt8U   wbuf,   Int32U  add,   Int32U   size)//*****�ֽ�д
{
Int32U offset;
Int32U reamin;
//Spi0_start(); 
offset=add&0xff;
reamin=PAGE_SIZE-offset;

if(size<=reamin)//����һҳ
  {
  Bytes_Write(wbuf, add, size);
  }
else
  {         //����һҳ
  Bytes_Write(wbuf, add, reamin);
  size-=reamin;
  wbuf+=reamin;
  add+=reamin;
  while(size>0)
     {
	 if(size>=PAGE_SIZE)
	   {
	   Bytes_Write(wbuf, add, PAGE_SIZE);
	   size-=PAGE_SIZE;
	   wbuf+=PAGE_SIZE;
	   add+=PAGE_SIZE;
	   }
	 else
	   {
	   Bytes_Write(wbuf, add, size);
	   size=0;
	   }
	 }
  }  
}
