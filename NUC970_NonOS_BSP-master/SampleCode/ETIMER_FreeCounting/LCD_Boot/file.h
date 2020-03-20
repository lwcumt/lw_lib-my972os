/*
�ļ�ϵͳͷ





*/





#ifndef _FILE_H
#define _FILE_H


//#include<stdlib.h>
#include "main.h"

#include"nandflash.h"



//#define NAND_FREE 0xffff    //ҳΪ�ձ�־����
/*
#define FILE_INFO_START_SECTOR     32//�źſ����
#define FILE_INFO_START_PAGE      10   //��ʮҳ
#define FILE_INFO_LENGTH          256  //�ļ���Ϣ����

#define FILE_INFO_NUMS_1PAGE          (NF_PAGE_BYTES/FILE_INFO_LENGTH)  //ҳ�ļ���Ϣ ����


//#define FILE_NAME_LENGTH          128

#define FILE_NUMS                 128  //����ļ���
#define FILE_START_SECTOR          10 +FILE_INFO_START_SECTOR//�ӵ�ʮ�鿪ʼд�ļ�
*/
//************sdram �ļ�������
#define NF_SECTOR_SDRAM_BUF      0x80800000//(SDRAM0_BASE_ADDR+0x180000) //nand�� sdram������ 0x81300000//

#define DOWNFILE_SDRAM_ADD       (NF_SECTOR_SDRAM_BUF+0x200000)  //�����ļ���buf��ַ


#define MEM_PAGE_FREE 0xffff    //ҳΪ�ձ�־����

#define FILE_INFO_START_SECTOR  32//�źſ����
// #define FILE_INFO_PAGE_NUM 0   //��ʮҳ
#define FILE_INFO_START_PAGE     0// 10   //��ʮҳ
#define FILE_INFO_LENGTH          256  //�ļ���Ϣ����

#define FILE_INFO_LENGTH          256  //�ļ���Ϣ����
#define FILE_MAXNUM    128  //����ļ���


#define FILE_SAVE_UNUSER_SECTOR (FILE_INFO_START_SECTOR+5)
#define FILE_SAVE_BOOTAPP_SECTOR  (FILE_INFO_START_SECTOR+8)
#define FILE_SAVE_SECTOR  (10+FILE_INFO_START_SECTOR) //�ӵ�ʮ�鿪ʼд�ļ�

#define UNUSER 0xffff

#define INUSER 0

typedef struct 
{
unsigned char FileName[128];
unsigned int FileLength;
unsigned int FileAddress;//
unsigned char FileTempBuf[16];
}FILES;



typedef struct 
{
unsigned short iFileStartSector;
unsigned short iFileInvalidSector[2048];
}FILE_SECTOR_INFO;


typedef struct 
{
unsigned int iFileNameSector;
unsigned int iFileNamePage;
unsigned int iFileNameAddress;
unsigned int iFileNameIndex;
}FILE_NAME;


typedef struct 
{
unsigned int iFileFolderSector;
unsigned int iFileFolderPage;
unsigned int iFileFolderAddress;
unsigned int iFileFolderIndex;
}FOLDER_NAME;


extern FILES iFiles;
extern FILES iFilesTemp;
extern FILE_SECTOR_INFO iFileSectorInfo;

extern FILE_NAME iFileNameAdd;
extern unsigned short FileNum;
extern FILE_NAME iFileName;
extern FOLDER_NAME iFileFolder;

extern unsigned char FolderName[128];//Ŀ¼����
extern unsigned int FileStartSector;

extern unsigned short SectorInUser[2048];
extern unsigned char NameTemp[128];

extern unsigned char BootFolder;

//extern unsigned short sys_tick;


void Nand_Format(void);
//******************************
void Nand_FillPage_SDbuf(unsigned short page,unsigned int length,unsigned char filldata); //��� sdram�鸴�����е�һҳ
void Nand_WritePage_SDbuf(unsigned short page,unsigned int length,unsigned char *wpdata); //��wpdata д�� sdram�鸴������ һҳ

extern unsigned char FileOpen(unsigned char *fname,unsigned char *ramadd);
extern unsigned char FileClose(unsigned char *fhandle);
extern unsigned char FileWrite(unsigned char *fhandle,unsigned int length);
extern unsigned char FileRead(unsigned char *fname,unsigned char *ramadd);
extern unsigned char FileFolderRead(unsigned char *str,unsigned char *buff);
extern unsigned char File_CreateStartSector(void); //����һ����ʼ�����ڱ���ϵͳ����
extern void File_GetStartSector(void); //��ȡ��ʼ��ͻ���

extern unsigned int  File_GetFreeSector_New(void);  //��ȡ���ÿ�//�¸Ķ�������Ŀ¼
extern unsigned int  File_GetFreeSector(void);  //��ȡ���ÿ�

extern unsigned char File_Delete(unsigned char *fname); //ɾ��һ���ļ�

extern unsigned char File_Create(unsigned char *fname);  //����һ���ļ�
extern unsigned char File_CreateFolder(unsigned char *fname);  //����һ���ļ���

extern unsigned int File_Find(unsigned char *fname);  //����һ���ļ��Ƿ���� ����һ����ַ
extern unsigned int File_FindFolder(unsigned char *folder);  //����һ���ļ����Ƿ���� ����һ����ַ

extern void SaveUnUserSector(void);
extern void LoadUnUserSector(void);

extern void FileWirte_Boot(void);
extern unsigned char FileLoadBootApp(void);    //װ������APP  ��������APP˳��
extern void  FileWriteBootApp(unsigned char banum) ;   //װ������APP
extern void ChangeFileName(unsigned char * name);
extern void ChangeFileName1(unsigned char * name);
#endif 
