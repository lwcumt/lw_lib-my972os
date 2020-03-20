/*
�ļ�ϵͳͷ





*/





#ifndef _FILE_NEWSTRUCT_H
#define _FILE_NEWSTRUCT_H


//#include<stdlib.h>
#include "main.h"

#include "file.h"


#include"nandflash.h"


//#define NAND_FREE 0xffff    //ҳΪ�ձ�־����


#define FILE_INFO_START_PAGE      0//10   //��ʮҳ
#define FILE_INFO_LENGTH          256  //�ļ���Ϣ����

#define FILE_INFO_NUMS_1PAGE          (NF_PAGE_BYTES/FILE_INFO_LENGTH)  //ҳ�ļ���Ϣ ����	8


//#define FILE_NAME_LENGTH          128

#define FILE_MAXNUM    128  //����ļ���

// #define FILE_NUMS                 128  //����ļ���
// #define FILE_START_SECTOR          10 +FILE_INFO_START_SECTOR//�ӵ�ʮ�鿪ʼд�ļ�

#define FILE_FOLD_MAX		6//6���ļ���
#define FILE_FOLD_PAGES		((FILE_MAXNUM/FILE_INFO_NUMS_1PAGE)+4)	//=20  1���ļ���20ҳ



#define FILE_SAVE_UNUSER_SECTOR (FILE_INFO_START_SECTOR+5)
#define FILE_SAVE_BOOTAPP_SECTOR  (FILE_INFO_START_SECTOR+8)
#define FILE_SAVE_SECTOR  (10+FILE_INFO_START_SECTOR) //�ӵ�ʮ�鿪ʼд�ļ�

#define UNUSER 0xffff

#define INUSER 0


//************sdram �ļ�������
#define NF_SECTOR_SDRAM_BUF      0x80800000//(SDRAM0_BASE_ADDR+0x180000) //nand�� sdram������ 0x81300000//

#define DOWNFILE_SDRAM_ADD       (NF_SECTOR_SDRAM_BUF+0x100000)  //�����ļ���buf��ַ





//#define FILE_DEBUG_ON 


#define TYPE_INFO 0x01   //��Ϣͷ����
#define TYPE_DIR 0x02    //Ŀ¼����
#define TYPE_FILE 0x03   //�ļ�����

#define SECTOR_USER 0xAAAA    
#define SECTOR_NOUSER 0x5555

#define SECTOR_BAD_USER 0xAA55


#define SECTOR_BAD 0xAAAA
#define SECTOR_OK  0x5555


#define FILE_INFO_START_SECTOR     32//�źſ����
#define FILE_DIR_START_SECTOR      48  //Ŀ¼��ʼ��
#define FILE_FILE_START_SECTOR     64 //�ļ��ӵ�64�鿪ʼ����


#define MAX_BAD_SECTOR_COUNT  16	//������ӻ�������

#define MAX_SECTOR   2048

extern uint32_t NAND_Blocks;
extern uint32_t 	File_Write_Cou;


typedef union 
{
unsigned char fName512[256];
struct 
	{
	uint8_t FileType;		//���� 
	char FileName[128]; //�ļ���
	uint32_t FileLength; //�ļ�����
	uint32_t FileSectorAddr;//�ļ����ڿ��ַ
	};
}FILES_N;



typedef union 
{
unsigned char dirName512[512];
 struct
{
uint8_t FileType;
char DirName[128];
int FileNum;
uint32_t StartSectorAddr;	
uint32_t EndSectorAddr;	
	
};
}FILE_FOLDER;



typedef struct
{
uint8_t FileType;
uint16_t  BadSector[2048];   //�����¼����
uint16_t UserSector[2048];  //ʹ�õĿ��¼����
uint16_t StartSectorAddr;	 //��ʼ���ַ
}SECTOR_INFO;

extern FILES_N nFiles;
extern SECTOR_INFO Sector_Info;

extern FILE_FOLDER File_Folder;




typedef union 
{
unsigned char fName256[256];
struct
	{
	unsigned char FileName[128];
	unsigned int FileLength;
	unsigned int FileAdd_Sector;//
// unsigned char FileTempBuf[16];	
	};
}FILES;



typedef struct 
{
unsigned short iFileSectorTable;
unsigned short iFileStartSector;
unsigned short iFileInvalidSector[1024];
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

extern unsigned char *FolderName;//Ŀ¼����
extern unsigned int FileStartSector;

extern unsigned short SectorInUser[1024];
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
extern unsigned char FileRead(char *fname,unsigned char *ramadd);
extern unsigned char FileFolderRead(unsigned char *str,unsigned char *buff);
extern unsigned char File_CreateStartSector(void); //����һ����ʼ�����ڱ���ϵͳ����
extern void File_GetSectorTable(void); //��ȡ��ʼ��ͻ���

extern unsigned int  File_GetFreeSector_New(void);  //��ȡ���ÿ�//�¸Ķ�������Ŀ¼
extern unsigned int  File_GetFreeSector(void);  //��ȡ���ÿ�

extern unsigned char File_Delete(unsigned char *fname); //ɾ��һ���ļ�

extern unsigned char File_Create( char *fname);  //����һ���ļ�
extern unsigned int File_CreateFolder( char *fname);  //����һ���ļ���

extern unsigned int File_Find(char *fname);  //����һ���ļ��Ƿ���� ����һ����ַ
extern unsigned int File_FindFolder(char *folder);  //����һ���ļ����Ƿ���� ����һ����ַ

extern void SaveUnUserSector(void);
extern void LoadUnUserSector(void);

extern void FileWirte_Boot(void);
extern unsigned char FileLoadBootApp(void);    //װ������APP  ��������APP˳��
extern void  FileWriteBootApp(unsigned char banum) ;   //װ������APP
extern void ChangeFileName(unsigned char * name);
extern void ChangeFileName1(unsigned char * name);


//��ʼ��
void File_Init(void);

void File_Test(void);

//�¼ӵĺ���

//*************************************************
//���� ��Ϣͷ
int  Save_Sector_Info(void);

//*************************************************
//���� ��Ϣͷ
int Load_Sector_Info(void);

 //��ȡFREE SECTOR 
 int File_GetFreeSector_N(unsigned int flen);
void File_Debug(char *str,uint8_t flag);

#endif 
