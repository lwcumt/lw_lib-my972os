
#ifndef _NANDFLASH_H
#define _NANDFLASH_H

#include "main.h"



//-----------*********nand ���� Ԥ����**************
#define   HY27US0856         0
#define   K9F1G08            1
//------------ID
#define K9FXX_ID			    0xECF10000	/* Byte 3 and 2 only */ 
#define HY27US08561A_ID			0xAD750000	/* 32MB */ 

//#define  NAND_TYPE  HY27US0856
#define  NAND_TYPE  K9F1G08
//------------***********nand �ṹ����**************

#if  NAND_TYPE==HY27US0856//----------HY27US08561A ------- 32MB
	#define NF_PAGE_BYTES      512  //ҳ���ݴ�С   Byte
	#define NF_PAGE_BITS       9  //ҳ��ַλ��   bit
	#define NF_BLOCK_PAGES     32  //һ��32ҳ
	#define NF_BLOCK_BYTES    (NF_PAGE_BYTES*NF_BLOCK_PAGES) //�����ݴ�С  16K
	#define NF_BLOCK_BITS     14 //���ַλ��  bit
	#define NF_BLOCKS          2048   //2048��
	
	//#define NF_PAGE_SIZE      (NF_PAGE_BYTES+16)  //ҳ�ռ��С   528 Byte
	//#define NF_BLOCK_SIZE     (NF_PAGE_SIZE*NF_BLOCK_PAGES) //��ռ��С  16K+16*32
	
	#define PAGE_MASK     (NF_PAGE_BYTES-1)//һҳmask

#elif NAND_TYPE==K9F1G08//----------HY27US08561A ------- 128MB
	#define NF_PAGE_BYTES      2048  //ҳ��С   2K
	#define NF_SECTOR_BYTES      512  //������С   512
	#define NF_PAGE_BITS       11  //ҳ��ַλ��
	#define NF_BLOCK_PAGES     64  //һ��64ҳ
	#define NF_BLOCK_BYTES    (NF_PAGE_BYTES*NF_BLOCK_PAGES) //���С  128K
	#define NF_BLOCK_BITS     17 //���ַλ��  bit
	#define NF_BLOCKS          1024   //���1024��

	#define PAGE_MASK     (NF_PAGE_BYTES-1)//һҳmask

#endif
//******************nand �����******************
#if  NAND_TYPE==HY27US0856//----------HY27US08561A ------- 32MB
	#define   READ1_LOW_CMMD           0x00//��256�ֽ�
	#define   READ1_HIGH_CMMD          0x01//��256�ֽ�
	#define   READ2_CMMD               0x50//
	#define   READ_ID_CMMD             0x90//��id
	#define   RESET_CMMD               0xff//��λ

	#define   PAGE_PROGRAM_CMMD1       0x80//ҳ���1st
	#define   PAGE_PROGRAM_CMMD2       0x10//ҳ���2st

	#define   COPY_BACK_PRG_CMMD1      0x00//1st
	#define   COPY_BACK_PRG_CMMD2      0x8A//2st
	#define   COPY_BACK_PRG_CMMD3      0x10//3st

	#define   BLOCK_ERASE_CMMD1        0x60//1st
	#define   BLOCK_ERASE_CMMD2        0xD0//2st

	#define   READ_STATUS_CMMD         0x70//
	#define   LOCK_BLOCK_CMMD          0x2A//
	#define   LOCK_TIGHT_CMMD          0x2C//
	#define   ULOCK_START_CMMD         0x23//
	#define   ULOCK_END_CMMD           0x24//
	#define   READ_LOCK_CMMD           0x7A//

#elif NAND_TYPE==K9F1G08//----------K9F1G08 ------- 128MB
	#define   READ_CMMD1              0x00
	#define   READ_CMMD2              0x30
	
	#define   READ_COPYBACK_COMMD1     0x00
	#define   READ_COPYBACK_COMMD2     0x35
	
	#define   READ_ID_CMMD             0x90//��id
	#define   RESET_CMMD               0xff//��λ
	
	#define   PAGE_PROGRAM_CMMD1       0x80//ҳ���1st
	#define   PAGE_PROGRAM_CMMD2       0x10//ҳ���2st

	#define   COPY_BACK_PRG_CMMD1      0x85//1st
	#define   COPY_BACK_PRG_CMMD2      0x10//2st
	
	#define   BLOCK_ERASE_CMMD1        0x60//1st
	#define   BLOCK_ERASE_CMMD2        0xD0//2st
	
	#define   READ_STATUS_CMMD         0x70//
	

#endif
//----------***********nand������ַ*****************
#define NANDFLASH_COMMAND_ADDR  (Int32U)0x82200000
/// Address for transferring address bytes to the nandflash.
#define NANDFLASH_ADDRESS_ADDR  (Int32U)0x82400000
/// Address for transferring data bytes to the nandflash.
#define NANDFLASH_DATA_ADDR     (Int32U)0x82000000
//#define NANDFLASH_READ_ADDR     (Int32U)0x80000000





//-----------************nand�ܽŶ���*********************
#define NAND_CS2  (1<<25)//     (1<<14)//p2.14  Ƭѡ
//#define NAND_CS_DIROUT  FIO2DIR |=NAND_CS2
#define NAND_CS_EN()  outpw(REG_NANDCTL, (inpw(REG_NANDCTL)&(~0x06000000))|0x00000000);
//outpw(REG_NANDCTL,~NAND_CS2)    // FIO2CLR = NAND_CS2
#define NAND_CS_DIS()   outpw(REG_NANDCTL, (inpw(REG_NANDCTL)&(~0x06000000))|0x02000000);
//outpw(REG_NANDCTL,NAND_CS2)  //FIO2SET = NAND_CS2

//////#define NAND_RB         15//p2.15       æ
//////#define NAND_RB_DIRIN   FIO2DIR &=~(1ul<<NAND_RB)
//////#define NAND_RB_PIN     (FIO2PIN &(1ul<<NAND_RB))







extern unsigned int NandID;//nand id

extern pInt8U pNF_ComdAdd;   //����
extern pInt8U pNF_AddrAdd;  //��ַ
extern pInt8U pNF_DataAdd;   //����

extern Int8U NandEccWrite_Flag;


extern Int16U InvalidBlock[NF_BLOCKS];//����洢
extern unsigned short Nf_InvalidCou;

//---------------nand ��д-------------
void NF_WriteCOMMD(Int8U cmd);//д ����
void NF_WriteADDR(Int32U add);//д ��ַ
void NF_WriteDATA(Int8U data);//д ���� DATA
void NF_WriteBUFF(Int8U data);//д ����BUFF
Int8U NF_ReadDATA(void);//д ����
void NF_WaitBusy(void);//-------------------æ�ȴ�

//----------------------nand  ���ݲ���--------------
Int8U Nand_ReadStatus(void);//��״̬0x70
void Nand_ReadID(void);//��id
void Nand_Reset(void);//��λnand



Int8U Nand_EraseBlock(Int32U block);//�����
Int8U Nand_WriteBytes(pInt8U databuf,Int32U nandadd);//����Ե�ַд ���� ------------     nandadd��nand���Ե�ַ           databuf:���ݻ�����
extern Int8U Nand_Write_1Page_1(pInt8U databuf,Int32U page);//=====***=====дһ����ҳ ���� -    page����ҳ��ַ           databuf:���ݻ�����
Int8U Nand_Write_1Page(pInt8U databuf,Int32U page);//=====***=====дһ����ҳ ���� -    page����ҳ��ַ           databuf:���ݻ�����

void Nand_Read_1page(pInt8U databuf,Int32U page);//=======****====��һ����ҳ���� -    page:����ҳ(��2k Byte)
void Nand_ReadBytes(pInt8U databuf,Int32U nandadd,Int32U size);//��<=1page���� -------------- nandadd:���Ե�ַ
void Nand_ReadDates(pInt8U databuf,Int32U nandadd,Int32U size);// �������ַ�����ⳤ�� ����#############################

void Nand_ReadBlock(unsigned int block,unsigned char *pSDbuf); //��ȡһ�� ��sdram ������
void Nand_WriteBlock(unsigned int block,unsigned char *pSDbuf);//sdram���ݻ�д��nandһ��
//void Nand_Format(void);

//******************************
//void Nand_FillPage_SDbuf(unsigned short page,unsigned int length,unsigned char filldata); //��� sdram�鸴�����е�һҳ
//void Nand_WritePage_SDbuf(unsigned short page,unsigned int length,unsigned char *wpdata); //��wpdata д�� sdram�鸴������ һҳ


#endif
