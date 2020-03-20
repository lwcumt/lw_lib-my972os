


#ifndef _FILE_H
#define _FILE_H


#include"nandflash.h"



//#define NAND_FREE 0xffff    //ҳΪ�ձ�־����

#define FILE_INFO_START_SECTOR     0 //�źſ����
#define FILE_INFO_START_PAGE      10   //��ʮҳ
#define FILE_INFO_LENGTH           256 // (128+8)//�ļ���Ϣ����

#define FILE_INFO_NUMS_1PAGE          (NF_PAGE_BYTES/FILE_INFO_LENGTH)  //ҳ�ļ���Ϣ ����


//#define FILE_NAME_LENGTH          128

#define FILE_NUMS                 128  //����ļ���
#define FILE_START_SECTOR          10 //�ӵ�ʮ�鿪ʼд�ļ�

//************sdram �ļ�������
#define NF_SECTOR_SDRAM_BUF       0x80100000//nand�� sdram������

#define DOWNFILE_SDRAM_ADD       0x80200000  //�����ļ���buf��ַ

/***


typedef struct 
{
unsigned char FileName[128];
unsigned int FileLength;
unsigned int FileAdd_Sector;//
}FILES;
**/

typedef union
{
unsigned char fName256[256];
struct 
	{
	unsigned char FileName[128];
	unsigned int FileLength;
	unsigned int FileAdd_Sector;//
	};
} FILES;



typedef struct 
{
unsigned short iFileStartSector;
unsigned short iFileSectorTable[1024];
}FILE_STORE_INFO;


typedef struct 
{
unsigned int iFileNameSector;
unsigned int iFileNamePage;
unsigned int iFileNameAddress;
unsigned int iFileNameIndex;
}FILE_NAME;




extern FILES iFiles;
extern FILES iFilesTemp;
extern FILE_STORE_INFO iFileSectorInfo;

extern FILE_NAME iFileName;
extern unsigned short FileNum;



void Nand_Format(void);
//******************************
void Nand_FillPage_SDbuf(unsigned short page,unsigned int length,unsigned char filldata); //��� sdram�鸴�����е�һҳ
void Nand_WritePage_SDbuf(unsigned short page,unsigned int length,unsigned char *wpdata); //��wpdata д�� sdram�鸴������ һҳ


unsigned char FileWrite(FILES file,  unsigned char *pSDbuf);//fhandle????????????
unsigned char FileRead(unsigned char *fname,unsigned char *buf);
unsigned int  File_GetFreeSector(void);  //��ȡ���ÿ�
unsigned char File_CreateStartSector(void); //����һ����ʼ�����ڱ���ϵͳ����
void File_GetStartSector(void); //��ȡ��ʼ��ͻ���
unsigned char File_Delete(unsigned char *fname); //ɾ��һ���ļ�
unsigned char File_Create(unsigned char *fname);  //����һ���ļ�
unsigned int File_Find(unsigned char *fname);  //����һ���ļ��Ƿ���� ����һ����ַ

extern void ChangeFileName1(unsigned char * name);
extern void ChangeFileName1(unsigned char * name);


#endif