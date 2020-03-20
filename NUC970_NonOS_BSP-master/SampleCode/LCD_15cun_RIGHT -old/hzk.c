#include "main.h"
#include "hzk.h"
#include "spi.h"

Int8U HanZi[32];
Int8U AT45db161[8];
void HZK_Read( char *hzp,unsigned char distype)  //��ȡ���ֿ��к��ֵ��� distype 0:���� 1:����
{
unsigned char i,hzk_temp[2];
int LowPointer,HighPointer;
int Pointer;
//unsigned int templ,temph;
hzk_temp[0]=hzp[0];
hzk_temp[1]=hzp[1];

if(hzk_temp[0]>0xa0&&hzk_temp[1]>0xa0)
	{
    hzk_temp[0]=hzk_temp[0]-0xa1;      //���㺺�ֵ������ֿ��е���ʼ��ַ
    hzk_temp[1]=hzk_temp[1]-0xa1;
    LowPointer=(int)hzk_temp[0]*94+(int)hzk_temp[1];
    Pointer=LowPointer*32;
    HighPointer=Pointer>>8;
//SpiChipSelect(1);  //ѡͨоƬ
    //    FIO0CLR = SPI0_SEL;
AT45DB_ArrayRead_Start(Pointer);
/*
SpiTranserByte(0xE8);
//	SpiTranserByte(AT45db041_ContArray_Read_Commd);
    //    AT45db161[0] = AT45db041_ContArray_Read_Commd;
	SpiTranserByte((unsigned char)(HighPointer>>8));
    //    AT45db161[1] = (unsigned char)(HighPointer>>8);
	SpiTranserByte((unsigned char)HighPointer);
    //    AT45db161[2] = (unsigned char)HighPointer;
	SpiTranserByte((unsigned char)Pointer);
    //    AT45db161[3] = (unsigned char)Pointer;
	SpiTranserByte(0);
    //    AT45db161[4] = 0x00;
	SpiTranserByte(0);
    //    AT45db161[5] = 0x00;
	SpiTranserByte(0);
    //    AT45db161[6] = 0x00;
	SpiTranserByte(0);
    //    AT45db161[7] = 0x00;
      //  SPISend(AT45db161,8);*/
    for(i=0;i<32;i++)               //��ȡ������Ϣ
         {
		 HanZi[i]=AT45DB_Read();
          }
       // SPIReceive( HanZi, 32);
	AT45DB_End();//(void)  //Ƭ�ͷ�
    //FIO0SET = SPI0_SEL;
   if(distype) for(i=0;i<32;i++) HanZi[i]=~HanZi[i];  //������ʾ
	}
else
    {
        Pointer=(unsigned long)hzk_temp[0]*16+ASCIIADD;
    HighPointer=Pointer>>8;
	SpiChipSelect(1);  //ѡͨоƬ
    //FIO0CLR = SPI0_SEL;
	SpiTranserByte(AT45db041_ContArray_Read_Commd);
    //    AT45db161[0] = AT45db041_ContArray_Read_Commd;
	SpiTranserByte((unsigned char)(HighPointer>>8));
    //    AT45db161[1] = (unsigned char)(HighPointer>>8);
	SpiTranserByte((unsigned char)HighPointer);
    //    AT45db161[2] = (unsigned char)HighPointer;
	SpiTranserByte((unsigned char)Pointer);
    //    AT45db161[3] = (unsigned char)Pointer;
	SpiTranserByte(0);
    //    AT45db161[4] = 0x00;
	SpiTranserByte(0);
    //    AT45db161[5] = 0x00;
	SpiTranserByte(0);
    //    AT45db161[6] = 0x00;
	SpiTranserByte(0);
    //    AT45db161[7] = 0x00;
      //  SPISend(AT45db161,8);
    for(i=0;i<32;i++)               //��ȡ������Ϣ
         {
		 HanZi[i]=SpiTranserByte(0);
          }
       // SPIReceive( HanZi, 16);
		SpiChipSelect(0);  //�ͷ�оƬ
//        FIO0SET = SPI0_SEL;
        if(distype) for(i=0;i<16;i++) HanZi[i]=~HanZi[i];  //������ʾ
	}
}