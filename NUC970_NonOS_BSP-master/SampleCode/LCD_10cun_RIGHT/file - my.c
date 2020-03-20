//#include "file_newstruct.h"
#include "drv_glcd.h"
#include "comm.h"

#include "pic_exec.h"
#include"download.h"

#include"down_status.h"
#include"m25pe16.h"

#include"word_lib.h"
#include"pic_exec.h"
#include "uart_config.h"


FILES iFiles;
FILES iFilesTemp;
FILE_SECTOR_INFO iFileSectorInfo;
//FILE_NAME iFileName;

FILE_NAME iFileName;
FOLDER_NAME iFileFolder;
FOLDER_NAME iFilesFolderTemp;

unsigned short FileNum;
unsigned char *FolderName;//Ŀ¼����
unsigned int FileStartSector;
unsigned short SectorInUser[NF_BLOCKS];
unsigned char NameTemp[128];

unsigned char BootFolder;

uint32_t 		File_Write_Cou=0;


FILES_N nFiles;//�ļ���Ϣͷ
FILES_N nFiles_Temp;//�ļ���Ϣͷ

//��Ϣͷ
SECTOR_INFO Sector_Info;

FILE_FOLDER File_Folder;
FILE_FOLDER File_Folder_Temp;

uint32_t NAND_Blocks=1024;


//unsigned short sys_tick;


Int8U testBlk(Int16U b)	//��ͬ ��������
{
	volatile Int16U i,p;
	volatile Int8U Wbuf[NF_PAGE_BYTES];
	volatile Int8U Rbuf[NF_PAGE_BYTES];
	//****************ff
	Nand_EraseBlock(b);
	for(i=0;i<NF_PAGE_BYTES;i++)
		{
			Wbuf[i]=0xff;
		}
	for(p=0;p<NF_BLOCK_PAGES;p++)
		{
		Nand_Write_1Page(Wbuf, b*NF_BLOCK_PAGES+p);//дһҳ	
		Nand_Read_1page(Rbuf,b*NF_BLOCK_PAGES+p);//��һҳ
		for(i=0;i<NF_PAGE_BYTES;i++)
			{
				if(Wbuf[i]!=Rbuf[i])	//����
					break;
			}
		if(i<NF_PAGE_BYTES)
			return 1;//����	
		}
	
	
	//****************0
	Nand_EraseBlock(b);
	for(i=0;i<NF_PAGE_BYTES;i++)
		{
			Wbuf[i]=0;
		}
	for(p=0;p<NF_BLOCK_PAGES;p++)
		{
		Nand_Write_1Page(Wbuf, b*NF_BLOCK_PAGES+p);//дһҳ	
		Nand_Read_1page(Rbuf,b*NF_BLOCK_PAGES+p);//��һҳ
		for(i=0;i<NF_PAGE_BYTES;i++)
			{
				if(Wbuf[i]!=Rbuf[i])	//����
					break;
			}
		if(i<NF_PAGE_BYTES)
			return 1;//����	
		}
	
	return 0;//����
}







//******************************
void Nand_FillPage_SDbuf(unsigned short page,unsigned int length,unsigned char filldata)  //��� sdram�鸴�����е�һҳ
{
int i;
unsigned char *pSDbuf;
pSDbuf=(unsigned char *)NF_SECTOR_SDRAM_BUF;
pSDbuf+=(page*FILE_INFO_LENGTH)+2048;

for(i=0;i<length;i++)//���һҳ
	{
	*pSDbuf++=filldata;
	}
}

void Nand_WritePage_SDbuf(unsigned short page,unsigned int length,unsigned char *wpdata) //��wpdata д�� sdram�鸴������ һҳ
{
int i;
unsigned char *pSDbuf;
pSDbuf=(unsigned char *)NF_SECTOR_SDRAM_BUF;
//pSDbuf+=page*FILE_INFO_LENGTH;
pSDbuf+=(page*FILE_INFO_LENGTH)+2048;

for(i=0;i<length;i++)//���һҳ
	{
	*pSDbuf++=*wpdata++;
	}
}




unsigned char FileOpen(unsigned char *fname,unsigned char *ramadd)
{




}



unsigned char FileClose(unsigned char *fhandle)
{





}




unsigned int  File_GetFreeSector_New(void)  //��ȡ���ÿ�//�¸Ķ�������Ŀ¼
{
unsigned int usesector;//���ÿ�
unsigned int sector;
unsigned int needsector;//�ļ���Ҫʹ�õĿ�
unsigned int i;
unsigned char free_flag;

unsigned char *sd;
unsigned int page=0;
unsigned int pagecou;
unsigned int add;
unsigned char filefree_flag=0;
unsigned char *nametemp;

unsigned int oldusesector;
int n;
int fn;


FileNum=0;

//sector=iFileSectorInfo.iFileStartSector;
sector=FileStartSector;

fn=FILE_MAXNUM/(NF_PAGE_BYTES /FILE_INFO_LENGTH);

for(i=0;i<fn;i++)
	{
//	add=sector*NF_BLOCK_BYTES+page*NF_PAGE_BYTES;
          add=sector*NF_BLOCK_BYTES+page*NF_PAGE_BYTES+iFileFolder.iFileFolderPage*2048;
	for(pagecou=0;pagecou< NF_PAGE_BYTES /FILE_INFO_LENGTH;pagecou++)
		{
		sd=(unsigned char*)&iFilesTemp;
		Nand_ReadDates(sd,add,FILE_INFO_LENGTH);
		// Nand_ReadDates(sd,add,128+4+4);
	//	NF_Read(add,FILE_INFO_LENGTH,sd);	
		if(FileNum==0)
			{
			filefree_flag=0;
			}
		else
			{
			filefree_flag=1;
			for(n=0;n<32;n++)
				{
				if(*sd++!=0xff)
					{
					filefree_flag=0;
					break;
					}

				}
			if(filefree_flag==1)
				break;
			}

		FileNum++;
		add+=FILE_INFO_LENGTH;
		}
	if(filefree_flag==1)
		break;
	if(FileNum>=FILE_MAXNUM)
		{
		break;
		}

	page++;
	if(page>=NF_PAGE_BYTES)
		{
		page=0;
		sector++;
		}
	}//for(i=0;i<FILE_MAXNUM;i++) �����ļ���


if(iFiles.FileLength>=NF_BLOCK_BYTES) //ȡ��ǰҪд�ļ�����
	{
	needsector=iFiles.FileLength;
	needsector/=NF_BLOCK_BYTES;
	}
else
	needsector=0;

needsector++;//��Ҫ�Ŀ�

File_GetSectorTable();//��ȡ��ʼ����Ϣ
usesector=FILE_SAVE_SECTOR;
sector=usesector;

//usesector=0;
while(1)
	{
	if(SectorInUser[sector]==UNUSER)
		{
		free_flag=1;
		for(i=0;i<needsector;i++)
			{
			if(SectorInUser[sector+i]!=UNUSER)//������ʹ�õĿ�
				{
				free_flag=0;
				break;
				}
			}
		}

	if(free_flag==1)
		{
		for(i=0;i<needsector;i++)
			{
			if(iFileSectorInfo.iFileInvalidSector[sector+i]!=UNUSER)//��������
				{
				free_flag=0;
				break;
				}
			}

		if(free_flag==1)
			break;
		}

	sector++;
	if(sector>1024)
		{
		break;
		}
	}


if(free_flag==1)
	{
	for(i=0;i<needsector;i++)
			{
			SectorInUser[sector+i]=0;  //ʹ�ÿ�ռ��
			}
	usesector=sector;
	return usesector;
	}
else
	{
	return 0;
	}
}




unsigned int  File_GetFreeSector(void)  //��ȡ���ÿ�
{
int i;
unsigned char *sd;
unsigned int sector;
unsigned int page=0;
unsigned int pagecou;
unsigned int add;
unsigned char filefree_flag=0;
unsigned char *nametemp;

unsigned int oldusesector;
unsigned int usesector;
int n;
int fn;

FileNum=0;

File_GetSectorTable();//��ȡ��ʼ����Ϣ

usesector=FILE_SAVE_SECTOR;

//sector=iFileSectorInfo.iFileStartSector;
sector=FileStartSector;

fn=FILE_MAXNUM/(NF_PAGE_BYTES /FILE_INFO_LENGTH);

for(i=0;i<fn;i++)
	{
	add=sector*NF_BLOCK_BYTES+page*NF_PAGE_BYTES;
	for(pagecou=0;pagecou< NF_PAGE_BYTES /FILE_INFO_LENGTH;pagecou++)
		{
		sd=(unsigned char*)&iFilesTemp;
		Nand_ReadDates(sd,add,FILE_INFO_LENGTH);
		// Nand_ReadDates(sd,add,128+4+4);
	//	NF_Read(add,FILE_INFO_LENGTH,sd);	
		if(FileNum==0)
			{
			filefree_flag=0;
			}
		else
			{
			filefree_flag=1;
			for(n=0;n<32;n++)
				{
				if(*sd++!=0xff)
					{
					filefree_flag=0;
					break;
					}

				}
			if(filefree_flag==1)
				break;
			}

		FileNum++;
		add+=FILE_INFO_LENGTH;
		}
	if(filefree_flag==1)
		break;
	if(FileNum>=FILE_MAXNUM)
		{
		break;
		}

	page++;
	if(page>=NF_PAGE_BYTES)
		{
		page=0;
		sector++;
		}
	}//for(i=0;i<FILE_MAXNUM;i++) �����ļ���



Nf_InvalidCou=0;
while(1)
	{//��⻵��
	if(iFileSectorInfo.iFileInvalidSector[Nf_InvalidCou]==0xffff)
		break;
	Nf_InvalidCou++;
	}


//sector=iFileSectorInfo.iFileStartSector;
sector=FileStartSector;

page=0;
int filenum=FileNum;
if(filefree_flag==1)
	{//�пռ�
	if(filenum>0)
		{
        filenum--;
		add=sector*NF_BLOCK_BYTES+page*NF_PAGE_BYTES+filenum*FILE_INFO_LENGTH; //����һ������
		sd=(unsigned char*)&iFilesTemp;
		Nand_ReadDates(sd,add,128+4+4);
//		Nand_ReadDates(sd,add,FILE_INFO_LENGTH);

		if(filenum==0)
			{
			iFilesTemp.FileLength=1024;
			iFilesTemp.FileAdd_Sector=42;
			}

		if(iFilesTemp.FileLength>=NF_BLOCK_BYTES)
			{
			oldusesector=iFilesTemp.FileLength;
			oldusesector/=NF_BLOCK_BYTES;
//			oldusesector=(iFilesTemp.FileLength/NF_BLOCK_BYTES);//������һ���ļ���ռ�õĿ�
			}
		else
			oldusesector=0;

		oldusesector++;

		usesector=iFilesTemp.FileAdd_Sector+oldusesector;//�õ���ǰһ����


		if(iFiles.FileLength>=NF_BLOCK_BYTES) //ȡ��ǰҪд�ļ�����
			{
			sector=iFiles.FileLength;
			sector/=NF_BLOCK_BYTES;
//			sector=(iFiles.FileLength/NF_BLOCK_BYTES);//���㵱ǰҪд�ļ�ռ�õĿ�
			}
		else
			sector=0;

		sector++;

		if(Nf_InvalidCou>0)
			{
			while(1)
				{
				for(i=0;i<Nf_InvalidCou;i++)
					{
					if(usesector<=iFileSectorInfo.iFileInvalidSector[i])
						{
						usesector=iFileSectorInfo.iFileInvalidSector[i]+1;
						if(usesector==iFileSectorInfo.iFileStartSector) //������ʼ��
							usesector++;
						if((usesector+sector)<iFileSectorInfo.iFileInvalidSector[i+1])
							{
							return usesector; //���ص�ǰ���ÿ�	
							}

						}
					else
						{
						if(usesector==iFileSectorInfo.iFileStartSector)//������ʼ��
							usesector++;
						if((usesector+sector)<iFileSectorInfo.iFileInvalidSector[i+1])
							{
							return usesector; //���ص�ǰ���ÿ�	
							}
						}
					}			
				}
			}
		else
			return usesector;//���ص�ǰ���ÿ�
			
		}
	else
		{//��һ���ļ�
		usesector=FILE_SAVE_SECTOR;
		if(iFiles.FileLength>=NF_BLOCK_BYTES) //ȡ��ǰҪд�ļ�����
			{
			sector=iFiles.FileLength;
			sector/=NF_BLOCK_BYTES;
//			sector=(iFiles.FileLength/NF_BLOCK_BYTES);//���㵱ǰҪд�ļ�ռ�õĿ�
			}
		else
			sector=0;

		sector++;
                
		if(Nf_InvalidCou>0)
			{
			while(1)
				{
				for(i=0;i<Nf_InvalidCou;i++)
					{
					if(usesector<=iFileSectorInfo.iFileInvalidSector[i])
						{
						usesector=iFileSectorInfo.iFileInvalidSector[i]+1;
						if(usesector==iFileSectorInfo.iFileStartSector)
							usesector++;
						if((usesector+sector)<iFileSectorInfo.iFileInvalidSector[i+1])
							{
							return usesector; //���ص�ǰ���ÿ�	
							}

						}
					else
						{
						if(usesector==iFileSectorInfo.iFileStartSector)
							usesector++;
						if((usesector+sector)<iFileSectorInfo.iFileInvalidSector[i+1])
							{
							return usesector; //���ص�ǰ���ÿ�	
							}
						}
					}			
				}
			}
		else
			return usesector;//���ص�ǰ���ÿ�


		}
	}
else
	{//�޿ռ�



	}

}




unsigned int  File_GetFreeFolder(void)  //��ȡ�����ļ��п�
{
int i;
unsigned char *in_buf;
unsigned int sector;
unsigned int page=0;
unsigned int pagecou;
unsigned int n_add;
unsigned char filefree_flag=0;
unsigned char *nametemp;

unsigned int oldusesector;
unsigned int usesector;
int n;

FileNum=0;

File_GetSectorTable();//��ȡ��ʼ����Ϣ



//usesector=FILE_SAVE_SECTOR;

sector=iFileSectorInfo.iFileStartSector;

//fn=FILE_MAXNUM/(NF_PAGE_BYTES /FILE_INFO_LENGTH);

for(i=0;i<FILE_FOLD_MAX;i++)	//6
	{
	n_add=sector*NF_BLOCK_BYTES+page*NF_PAGE_BYTES;
	//for(pagecou=0;pagecou< NF_PAGE_BYTES /FILE_INFO_LENGTH;pagecou++)
		//{
		in_buf=(unsigned char*)&iFilesTemp;
		Nand_ReadDates(in_buf,n_add,FILE_INFO_LENGTH);
			
		filefree_flag=1;
		for(n=0;n<32;n++)
			{
			if(*in_buf++!=0xff)
				{
				filefree_flag=0;
				break;
				}

			}
	//	if(filefree_flag==1)
	//		break;

	//	FileNum++;
	//	add+=FILE_INFO_LENGTH;
	//	}
	if(filefree_flag==1)
		break;
	//if(FileNum>=FILE_MAXNUM)
	//	{
	//	break;
	//	}

	page+=FILE_FOLD_PAGES;
	if(page>=NF_BLOCK_PAGES)//60
		{
		page=0;
		sector++;
		}

		/*
	page++;
	if(page>=NF_PAGE_BYTES)
		{
		page=0;
		sector++;
		}*/
	}//for(i=0;i<FILE_MAXNUM;i++) �����ļ���


if(filefree_flag==1)
	{


iFileFolder.iFileFolderSector=sector;//ȡ��Ӧ��
iFileFolder.iFileFolderPage=page;  //ȡ��Ӧҳ
	iFileFolder.iFileFolderAddress=n_add; //ȡ��Ӧ��ַ
iFileFolder.iFileFolderIndex=i;  //�ļ�����λ��

	return 1;  //�ҵ��ļ�
	}
else
	{
	return 0; //�Ҳ�����Ӧ�ļ�
	}
}



//*************************************************
//���� ��Ϣͷ
unsigned char File_CreateStartSector(void) //����һ����ʼ�����ڱ���ϵͳ����
{
unsigned short s_sector;
//unsigned int *sd;
unsigned short *nfiv;
int i;
unsigned int x;
x=FILE_INFO_START_SECTOR;
	
while(1)
	{
	if(Sector_Info.BadSector[x]!=SECTOR_NOUSER)
		x++;
	else
		break;
	}//while(1)


iFileSectorInfo.iFileStartSector=s_sector;


unsigned char *sd=(unsigned char*)&Sector_Info.FileType;

i=Nand_Write_1Page(sd,x*NF_BLOCK_PAGES); //д�����Ϣͷ
sd+=NF_PAGE_BYTES;
i=Nand_Write_1Page(sd,x*NF_BLOCK_PAGES+1); //д�����Ϣͷ

sd+=NF_PAGE_BYTES;
i=Nand_Write_1Page(sd,x*NF_BLOCK_PAGES+2); //д�����Ϣͷ
	
//SaveUnUserSector();  //����δʹ�ÿ�

//i=Nand_Write_1Page(sd,(FILE_INFO_START_SECTOR*NF_BLOCK_BYTES+FILE_INFO_PAGE_NUM*NF_PAGE_BYTES)); //д�����Ϣͷ

File_GetSectorTable();
if(i==1)
	return 1; //дͷ����
else
	return 0;//��ȷ

}





//************************
//ԭ������Ϣͷ    ������
void SaveUnUserSector(void)
{
	unsigned int x;
x=FILE_SAVE_UNUSER_SECTOR;

Nand_EraseBlock((x));//*NF_BLOCK_BYTES)>>11);
// Nand_EraseBlock((x*NF_BLOCK_BYTES)>>11);
unsigned char *sd=(unsigned char*)&SectorInUser;
Nand_Write_1Page(sd,x*NF_BLOCK_PAGES); //д�����Ϣͷ

}


//************************
//ԭ������Ϣͷ    ������
void LoadUnUserSector(void)
{
unsigned int x;
x=FILE_SAVE_UNUSER_SECTOR;
unsigned char *sd=(unsigned char*)&SectorInUser;
Nand_ReadDates(sd,x*128*1024,2048);

}




void File_GetSectorTable(void) //��ȡ��ʼ��ͻ���
{
unsigned char *sd=(unsigned char*)&iFileSectorInfo.iFileStartSector;
unsigned int x;
////Printf24("Ŀ¼����_��ȡ��ʼ��",0,0,0,1,0xf7a2);
x=FILE_INFO_START_SECTOR;
Nand_ReadDates(sd,x*128*1024,2000);
////Printf24("Ŀ¼����_װ��δʹ�ÿ�",0,0,0,1,0xf7a2);
LoadUnUserSector();
////Printf24("Ŀ¼����_���",0,0,0,1,0xf7a2);

//Nand_ReadDates(sd,FILE_INFO_START_SECTOR*NF_BLOCK_BYTES+FILE_INFO_PAGE_NUM*NF_PAGE_BYTES,2000);

//NF_Read(FILE_INFO_START_SECTOR*NF_BLOCK_BYTES+FILE_INFO_PAGE_NUM*NF_PAGE_BYTES,2048,sd);//��ȡ�ֿ�

}


unsigned char File_Delete(unsigned char *fname) //ɾ��һ���ļ�
{
FILE_NAME *fnd;
if(File_Find(fname)==1)//�Ȳ����ļ��Ƿ����
	{//�Ѵ���

	return 1;
	}
else
	{//�ļ������ڷ���
	return 0;

	}
}





////////unsigned char File_CreateFolder(unsigned char *fname)  //����һ���ļ���
////////{

////////unsigned char *nametemp;
////////unsigned char *fnametemp=(unsigned char *)&iFiles.FileName;
////////unsigned int sector,wsector;
////////int i=0;
////////int n=0;
/////////*
////////if(fname[i++]=='\\')
////////	{//��Ŀ¼����
////////	while(fname[i++]!='\\')
////////		{
////////		FolderName[i-1]=fname[i-1];
////////		}
////////	FolderName[i-1]=0;

////////	while(fname[i++]!=0)
////////		{
////////		fname[n++]=fname[i-1];
////////		}
////////	fname[n]=0;
////////	ChangeFileName(fname);
////////	}
////////*/
////////ChangeFileName(fname);


////////fnametemp=(unsigned char *)&iFiles.FileName;

////////if(File_FindFolder(fname)==1)
////////	{//�Ѵ��ڸ���
////////	/*
////////	Nand_ReadBlock(iFileName.iFileNameSector,(unsigned char *)NF_SECTOR_SDRAM_BUF);//��ȡ �ļ�name��Ϣ
////////	sector=iFileName.iFileNameSector;
////////	Nand_EraseBlock((sector*NF_BLOCK_BYTES)>>11);
////////	Nand_FillPage_SDbuf(FileNum,FILE_INFO_LENGTH,0xff); //ɾ��ԭ�е���Ϣ �����ļ��������ȣ���ַ
////////	iFiles.FileAdd_Sector=iFilesTemp.FileAdd_Sector;//��ȡ���ÿ�
////////	Nand_WritePage_SDbuf(FileNum,FILE_INFO_LENGTH,fnametemp);
////////	Nand_WriteBlock(iFileName.iFileNameSector,(unsigned char *)NF_SECTOR_SDRAM_BUF);
////////	if(iFilesTemp.FileLength>=NF_BLOCK_BYTES)
////////		{
////////		sector=iFilesTemp.FileLength;
////////		sector/=NF_BLOCK_BYTES;
////////		}
////////	else
////////		sector=0;
////////	sector++;
////////	wsector=iFiles.FileAdd_Sector;
////////	for(i=0;i<sector;i++)
////////		{
////////		Nand_EraseBlock(((wsector+i)*NF_BLOCK_BYTES)>>11);
////////		}
////////	FileWrite(0,iFiles.FileLength);*/
////////	}
////////else
////////	{//�ļ��в����ڴ���
////////	File_GetSectorTable();//��ȡ��ʼ����Ϣ
////////	if(File_GetFreeFolder()==1)//�пռ�
////////		{
////////		Nand_ReadBlock(iFileFolder.iFileFolderSector,(unsigned char *)NF_SECTOR_SDRAM_BUF);//��ȡ �ļ�name��Ϣ
////////		//
////////		sector=iFileFolder.iFileFolderSector;
////////		
////////		Nand_EraseBlock((sector));//*NF_BLOCK_BYTES)>>11);
////////		// Nand_EraseBlock((sector*NF_BLOCK_BYTES)>>11);
////////		Nand_FillPage_SDbuf(0,FILE_INFO_LENGTH,0xff); //ɾ��ԭ�е���Ϣ �����ļ��������ȣ���ַ
////////		Nand_WritePage_SDbuf(0,FILE_INFO_LENGTH,fnametemp);


////////		Nand_WriteBlock(iFileFolder.iFileFolderSector,(unsigned char *)NF_SECTOR_SDRAM_BUF);     
////////		Nand_ReadBlock(iFileFolder.iFileFolderSector,(unsigned char *)NF_SECTOR_SDRAM_BUF);//��ȡ �ļ�name��Ϣ
////////		}     
////////	}
////////}






////////unsigned int File_FindFolder(unsigned char *folder)  //����һ���ļ����Ƿ���� ����һ����ַ
////////{
////////int i;
////////unsigned char *sd;
////////unsigned short sector;
////////unsigned short page=0;
////////unsigned short pagecou;
////////unsigned int add;
////////unsigned char namematch_flag=0;
//////// unsigned char *nametemp;
////////int fn;
//////////int FileNum=0;

////////File_GetSectorTable();//��ȡ��ʼ����Ϣ

////////FileNum=0;//�ļ���������

////////sector=iFileSectorInfo.iFileStartSector;

////////fn=FILE_MAXNUM/(NF_PAGE_BYTES /FILE_INFO_LENGTH);
////////fn=2;//���ɽ�6��Ŀ¼�����Թ�6��APP 
////////for(i=0;i<fn*3;i++)
////////	{
////////	add=sector*NF_BLOCK_BYTES+page*NF_PAGE_BYTES;
////////	//for(pagecou=0;pagecou< NF_PAGE_BYTES /FILE_INFO_LENGTH;pagecou++)
////////	//	{
////////		sd=(unsigned char*)&iFilesTemp;
////////		// Nand_ReadDates(sd,add,128+4+4);
////////		Nand_ReadDates(sd,add,FILE_INFO_LENGTH);
////////		nametemp=(unsigned char *)folder;
////////		namematch_flag = 1; 
////////		while(*nametemp!=0)
////////			{
////////			if(*nametemp++ != *sd++)
////////				{
////////				namematch_flag = 0; 
////////				break;
////////				}
////////			}
////////		if(namematch_flag==1)
////////			break;
////////	//	FileNum++;
////////	//	add+=FILE_INFO_LENGTH;
////////	//		}

////////	if(namematch_flag==1)
////////		break;

////////	//if(FileNum>=FILE_MAXNUM)
////////		//{
////////	//	break;
////////	//	}
////////	
////////	page+=20; //ÿ��Ŀ¼ռ��20ҳ  3��Ŀ¼ռ��һ���� 
////////	if(page>=60)
////////		{
////////		page=0;
////////		sector++;
////////		}

////////	/*
////////	page++;
////////	if(page>=NF_PAGE_BYTES)
////////		{
////////		page=0;
////////		sector++;
////////		}
////////		*/
////////	}//for(i=0;i<FILE_MAXNUM;i++) �����ļ���

////////iFileFolder.iFileFolderSector=sector;//ȡ��Ӧ��
////////iFileFolder.iFileFolderPage=page;  //ȡ��Ӧҳ
////////iFileFolder.iFileFolderAddress=add; //ȡ��Ӧ��ַ
////////iFileFolder.iFileFolderIndex=i;  //�ļ�����λ��
////////	//Printf24("                     ",0,0,0,1,0xf7a2);
//////////Printf24("Ŀ¼�������",0,0,0,1,0xf7a2);
////////if(namematch_flag==1)
////////	{
////////	return 1;  //�ҵ��ļ�
////////	}
////////else
////////	{
////////	return 0; //�Ҳ�����Ӧ�ļ�
////////	}
////////}



void FileWirte_Boot(void)
{
// unsigned short*wrbuff16;
unsigned short tmp16,tmp16i;
unsigned short wrbuff16[1024]={0};
unsigned char *dptr;

Int32U ptw,p;

Nand_EraseBlock(0);//����0��
Nand_EraseBlock(1);//����1��

/* Setup FLASH config See UM10326 section 2.2.3.2 */

  // tmp16 = 0x00; /* 16-Bit NAND still not supported */

    tmp16 = 1 << 2;
  tmp16 |= (~tmp16 & 0x0F) << 4;//1011 0100
  tmp16i = 0xFF - tmp16;
  wrbuff16[0] = tmp16;
  wrbuff16[2] = tmp16;
  wrbuff16[4] = tmp16;
  wrbuff16[6] = tmp16;

  ptw = CommFileLenth / NF_PAGE_BYTES;
  if ((ptw *NF_PAGE_BYTES) < CommFileLenth)
  {
	ptw++;
  }
  ptw++; /* Include non-used sector */

  tmp16 = (Int16U) ptw;
  tmp16i = 0x00FF - tmp16;
  wrbuff16[8] = tmp16;
  wrbuff16[10] = tmp16i;
  wrbuff16[12] = tmp16;
  wrbuff16[14] = tmp16i;
  wrbuff16[16] = tmp16;
  wrbuff16[18] = tmp16i;
  wrbuff16[20] = tmp16;
  wrbuff16[22] = tmp16i;
  wrbuff16[24] = 0x00AA; /* Good block marker for page #0 ICR only */

  
//----------д���0��nand----
Nand_Write_1Page((unsigned char*)wrbuff16,0); //д��ICR

dfPtr=(unsigned char *)(DOWNFILE_SDRAM_ADD);
for(p=1;p<ptw;p++)
	{
	Nand_Write_1Page(dfPtr, p);//д��BOOT
	dfPtr+=NF_PAGE_BYTES;
	}	


//-------д���1��nand-----copy---
Nand_Write_1Page((unsigned char*)wrbuff16, 1*NF_BLOCK_PAGES);//д��ICR

dfPtr=(unsigned char *)(DOWNFILE_SDRAM_ADD);
for(p=1;p<ptw;p++)
	{
	Nand_Write_1Page(dfPtr, 1*NF_BLOCK_PAGES+p);//д��BOOT
	dfPtr+=NF_PAGE_BYTES;
	}	


//block_inf=(unsigned char*)&wbbuf;//iFileSectorInfo.iFileInvalidSector;

//Nand_Read_1page(block_inf, 1+64);//��һҳ ����Ϣ
}



unsigned char FileLoadBootApp(void)    //װ������APP  ��������APP˳��
{

unsigned char *bap;
bap=(unsigned char*)DOWNFILE_SDRAM_ADD;
 FileRead("AppStartFile.ini",bap);
return bap[0];
}

void  FileWriteBootApp(unsigned char banum)    //װ������APP
{
unsigned char *bap;
bap=(unsigned char *)DOWNFILE_SDRAM_ADD;
*bap=banum;

	iFiles.FileLength=1;
	ChangeFileName("AppStartFile.ini");
	NandEccWrite_Flag=0;
	File_Create(iFiles.FileName);//�����ļ�
}



void ChangeFileName(unsigned char * name)
{
		//		dfPtr=(unsigned char *)DOWNFILE_SDRAM_ADD;
				unsigned char *ifiles=(unsigned char *)iFiles.FileName;

				//GLCD_Buffer_Fill(BLUE_COLOR);
                               // int n;
                              //  for(n=0;n<CommFileLenth;n++)
                             //   {
                            //     *ifiles++=*dfPtr++; 
                             //   }

				while(*name!=0)
					{
					*ifiles++=*name++;
					}//*/
				 *ifiles=0;
				

		//		FileRead("�ֿ�_0x20000.FON",(unsigned char *)df_zk_sdram);
		//		//Printf24("����....",400,350,0,1,0xf7a2);
		//		Printf24(iFiles.FileName,350,300,0,1,0xf7a2);

}

void ChangeFileName1(unsigned char * name)
{
		//		dfPtr=(unsigned char *)DOWNFILE_SDRAM_ADD;
				unsigned char *ifiles=(unsigned char *)iFiles.FileName;

				//GLCD_Buffer_Fill(BLUE_COLOR);
                               // int n;
                              //  for(n=0;n<CommFileLenth;n++)
                             //   {
                            //     *ifiles++=*dfPtr++; 
                             //   }
				
				name++;
				name++;
				//*name='\\';
				while(*name!=0)
					{
					*ifiles++=*name++;
					}//*/
				 *ifiles=0;
                 ifiles=(unsigned char *)iFiles.FileName;
                                *ifiles='\\';

		//		FileRead("�ֿ�_0x20000.FON",(unsigned char *)df_zk_sdram);
		//		//Printf24("����....",400,350,0,1,0xf7a2);
		//		Printf24(iFiles.FileName,350,300,0,1,0xf7a2);

}


//*************************************************
//*************************************************
//*************************************************
//*************************************************
//*************************************************
//*************************************************
//*************************************************
//*************************************************
//*************************************************

//       �¼ӣ��ģ�  ����

//*************************************************
//*************************************************
//*************************************************
//*************************************************
//*************************************************
//*************************************************
//*************************************************

char ascbuf[16];


char File_FileName[128];
int FindFileNum=0;


//��ʼ��
void File_Init(void)
{
int i;
int dircou=0;
int filenumcou=0;

FILE_FOLDER *foldertemp;

Load_Sector_Info();//װ�ػ��鼰 ʹ�ÿ�״̬
File_Write_Cou=0;

for(i=FILE_DIR_START_SECTOR;i<FILE_FILE_START_SECTOR;i++)
	{
	Nand_ReadBlock(i,(unsigned char *)NF_SECTOR_SDRAM_BUF);//��ȡ Ŀ¼ָ��Ŀ� ��Ϣ�ļ�name��Ϣ
	foldertemp=NF_SECTOR_SDRAM_BUF;
	if(foldertemp->FileType==TYPE_DIR)
		{
		File_Debug("�ҵ�Ŀ¼��\"",0);
		File_Debug(foldertemp->DirName,0);
		File_Debug("\"",1);


		File_Debug("��Ŀ¼��һ����: ",0);
		sprintf(ascbuf,"%d",foldertemp->FileNum);
		File_Debug(ascbuf,0);	
		File_Debug(" ���ļ�...,",1);
		}
	}
}



void File_Test(void)
{
int n;
int sector;
int nedd_sector;
Nand_Format();
File_CreateFolder("\\");	//������Ŀ¼



//File_Create("\\APP1\\APP.bin");
//File_Find("123.bmp");
//File_Find("\\APP1\\APP.bin");


//File_CreateFolder("APP1");
File_Debug("\\APP1\\APP1.bin",1);
File_Debug("\\APP1\\APP1.bin",1);
File_Debug("\\APP1\\APP2.bin",1);
File_Debug("\\APP1\\APP2.bin",1);
File_Debug("\\APP1\\APP3.bin",1);
File_Debug("\\APP1\\APP3.bin",1);
File_Debug("\\APP1\\APP4.bin",1);
File_Debug("\\APP1\\APP4.bin",1);


File_Debug("***********************************************************",1);
iFiles.FileLength=1024;

File_Create("\\APP1\\APP.bin");
File_Debug("***********************************************************",1);
iFiles.FileLength=4906;
File_Create("\\APP1\\APP1.bin");
FileRead("\\APP1\\APP1.bin",(unsigned char*)START_PIC_sdram);
File_Debug("***********************************************************",1);
iFiles.FileLength=65535;
File_Create("\\APP1\\APP.bin");
File_Debug("***********************************************************",1);
iFiles.FileLength=102588;
File_Create("\\APP1\\APP.bin");
File_Debug("***********************************************************",1);
iFiles.FileLength=846546;
File_Create("\\APP1\\APP.bin");

File_Debug("***********************************************************",1);
iFiles.FileLength=28;
File_Create("APP.bin");
FileRead("APP.bin",(unsigned char*)START_PIC_sdram);
File_Debug("***********************************************************",1);
iFiles.FileLength=68;
File_Create("\\APP2\\APP.bin");
File_Debug("***********************************************************",1);
iFiles.FileLength=4444;
File_Create("\\APP3\\APP.bin");
File_Debug("***********************************************************",1);
iFiles.FileLength=8888;
File_Create("\\APP4\\APP.bin");
File_Debug("***********************************************************",1);
iFiles.FileLength=4275;
File_Create("\\APP5\\APP.bin");
File_Debug("***********************************************************",1);
iFiles.FileLength=1877454;
File_Create("\\APP6\\APP.bin");


/*

//File_Find("\\APP1\\APP.bin");


//FileFolderRead("Power.bmp",(unsigned char*)START_PIC_sdram);//����������

FileRead("\\APP1\\APP.bin",(unsigned char*)START_PIC_sdram);


File_Debug("***********************************************************",1);

iFiles.FileLength=2048;

File_Create("\\APP1\\APP0.bin");

//File_Find("\\APP1\\APP.bin");


//FileFolderRead("Power.bmp",(unsigned char*)START_PIC_sdram);//����������

FileRead("\\APP1\\APP0.bin",(unsigned char*)START_PIC_sdram);





//File_Debug("***********************************************************",1);

iFiles.FileLength=18;

File_Create("\\APP1\\APP1.bin");

//File_Find("\\APP1\\APP.bin");


//FileFolderRead("Power.bmp",(unsigned char*)START_PIC_sdram);//����������

FileRead("\\APP1\\APP1.bin",(unsigned char*)START_PIC_sdram);



//File_Debug("***********************************************************",1);

iFiles.FileLength=18;
File_Debug("\\APP1\\APP1.bin",1);
File_Create("\\APP1\\APP1.bin");


FileRead("\\APP1\\APP1.bin",(unsigned char*)START_PIC_sdram);



//File_Debug("***********************************************************",1);

iFiles.FileLength=4096;
File_Debug("\\APP1\\APP0.bin",1);
File_Create("\\APP1\\APP8.bin");



FileRead("\\APP1\\APP0.bin",(unsigned char*)START_PIC_sdram);
*/

while(1);	

/*
File_CreateFolder("/");
File_CreateFolder("/APP1");
File_CreateFolder("/APP2");
File_CreateFolder("/APP3");
File_CreateFolder("/APP4");
File_CreateFolder("/APP5");
File_CreateFolder("/APP6");
	*/
File_Debug("\r\n",1);	
/*

nedd_sector=30;
sector=File_GetFreeSector_N(nedd_sector);
for(n=sector;n<=nedd_sector+sector;n++)
	{
		Sector_Info.UserSector[n]=SECTOR_USER;
	}


nedd_sector=15;
sector=File_GetFreeSector_N(nedd_sector);
for(n=sector;n<nedd_sector+sector;n++)
	{
		Sector_Info.UserSector[n]=SECTOR_USER;
	}

nedd_sector=60;
sector=File_GetFreeSector_N(nedd_sector);
for(n=sector;n<nedd_sector+sector;n++)
	{
		Sector_Info.UserSector[n]=SECTOR_USER;
	}



nedd_sector=1;
sector=File_GetFreeSector_N(nedd_sector);
for(n=sector;n<nedd_sector+sector;n++)
	{
		Sector_Info.UserSector[n]=SECTOR_USER;
	}

nedd_sector=1;
sector=File_GetFreeSector_N(nedd_sector);
for(n=sector;n<nedd_sector+sector;n++)
	{
		Sector_Info.UserSector[n]=SECTOR_USER;
	}


nedd_sector=300;
sector=File_GetFreeSector_N(nedd_sector);
for(n=sector;n<nedd_sector+sector;n++)
	{
		Sector_Info.UserSector[n]=SECTOR_USER;
	}

	nedd_sector=10;
sector=File_GetFreeSector_N(nedd_sector);
if(sector>0)
	{
for(n=sector;n<nedd_sector+sector;n++)
	{
		Sector_Info.UserSector[n]=SECTOR_USER;
	}
	}

		nedd_sector=10;
sector=File_GetFreeSector_N(nedd_sector);
if(sector>0)
	{
for(n=sector;n<nedd_sector+sector;n++)
	{
		Sector_Info.UserSector[n]=SECTOR_USER;
	}
	}

		nedd_sector=158;
sector=File_GetFreeSector_N(nedd_sector);
if(sector>0)
	{
for(n=sector;n<nedd_sector+sector;n++)
	{
		Sector_Info.UserSector[n]=SECTOR_USER;
	}
	}

		nedd_sector=10;
sector=File_GetFreeSector_N(nedd_sector);
if(sector>0)
	{
for(n=sector;n<nedd_sector+sector;n++)
	{
		Sector_Info.UserSector[n]=SECTOR_USER;
	}
	}

	*/

	/*
File_FindFolder("\\APP1\\");
File_FindFolder("APP1");
File_FindFolder("APP2");
File_FindFolder("APP3");
File_FindFolder("APP4");
File_FindFolder("APP5");
File_FindFolder("APP6");
File_FindFolder("app");
File_FindFolder("app1");
File_FindFolder("app2");
File_FindFolder("app3");
File_FindFolder("app4");
File_FindFolder("app5");*/


}


//************************************************
//��ʽ��    
void Nand_Format(void)
{
volatile Int32U block;
Int8U Err_f;
Nf_InvalidCou=0;

	File_Debug("Now Format Data Block ... ",1);
	
Sector_Info.FileType=TYPE_INFO;//��Ϣ����
	
for(block=0;block<NAND_Blocks;block++)
	{
	Sector_Info.BadSector[block]=SECTOR_OK;//����Ϣ  �����¼
	Sector_Info.UserSector[block]=SECTOR_NOUSER;		//����Ϣ  ʹ�ü�¼
	}
	
for(block=FILE_INFO_START_SECTOR;block<NAND_Blocks;block++)
  {
	Err_f=Nand_EraseBlock((block));//*NF_BLOCK_BYTES)>>11);
  if(Err_f==1)
    {		
		Sector_Info.BadSector[block]=SECTOR_BAD;//��־Ϊ����
		Sector_Info.UserSector[block]=SECTOR_BAD_USER;//��Ӧ�Ļ����־Ϊʹ��
			Nf_InvalidCou++;
		}
  } 
	
File_Debug("Total Bad Sector: ",0);
sprintf(ascbuf,"%d",Nf_InvalidCou);
File_Debug(ascbuf,1);

if(Nf_InvalidCou>0)
		{
		for(block=0;block<NAND_Blocks;block++)
			{			
			if(Sector_Info.BadSector[block]==SECTOR_BAD)
				{
			//	File_Debug("Total Bad Sector: ",0);
				sprintf(ascbuf,"%d",block);
				File_Debug(ascbuf,0);	
				File_Debug(",",0);
				}
			}	
		File_Debug("",1);			
		}
File_Debug("",1);		


Save_Sector_Info();//���滵����Ϣͷ
		
//ASCII_Printf(ascbuf,ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,40,180,0xffff,0);
//while(1);
//File_CreateStartSector();//������������Ϣ��	
}





//*************************************************
//���� ��Ϣͷ
int  Save_Sector_Info(void)
{
unsigned short s_sector;
//unsigned int *sd;
unsigned short *nfiv;
int i;
unsigned int x;

x=FILE_INFO_START_SECTOR;	
while(1)
	{
	if(Sector_Info.BadSector[x]!=SECTOR_NOUSER)
		x++;
	else
		break;
	}//while(1)


	if(x>FILE_INFO_START_SECTOR+MAX_BAD_SECTOR_COUNT)
	return -1;//���鳬����¼����
	

//�Ȳ�����ǰ�� 
Nand_EraseBlock((x));//*NF_BLOCK_BYTES)>>11);

unsigned char *sd=(unsigned char*)&Sector_Info.FileType;

i=Nand_Write_1Page(sd,x*NF_BLOCK_PAGES); //д�����Ϣͷ
sd+=NF_PAGE_BYTES;
i=Nand_Write_1Page(sd,x*NF_BLOCK_PAGES+1); //д�����Ϣͷ
sd+=NF_PAGE_BYTES;
i=Nand_Write_1Page(sd,x*NF_BLOCK_PAGES+2); //д�����Ϣͷ	
return 0;	
}



//*************************************************
//���� ��Ϣͷ
int Load_Sector_Info(void)
{
unsigned int x;
x=FILE_INFO_START_SECTOR;	
while(1)
	{
	if(Sector_Info.BadSector[x]!=SECTOR_NOUSER)
		x++;
	else
		break;
	}//while(1)
	
if(x>FILE_INFO_START_SECTOR+MAX_BAD_SECTOR_COUNT)
	return -1;//���鳬����¼����
	
unsigned char *sd=(unsigned char*)&Sector_Info.FileType;
Nand_ReadDates(sd,x*128*1024,sizeof(Sector_Info));	

return 0;//��ȷ
}






//*************************************************
//����һ���ļ���
unsigned int File_CreateFolder(char *dirname)  //����һ���ļ���  //����0  �޴���Ŀ¼�ռ�
{
unsigned int x;
unsigned char *sd;
x=FILE_DIR_START_SECTOR;		
unsigned int 	foldersector;
uint8_t Err_f;
int i;
	
File_Debug("Create A Dir and Find Dir frist: ",0);	
File_Debug(dirname,1);	
File_Debug("",1);	
	
foldersector=File_FindFolder(dirname);
	
if(foldersector==0)
		{//��Ŀ¼�����д���
		for(x=FILE_DIR_START_SECTOR;x<FILE_FILE_START_SECTOR;x++)
					{
					if(Sector_Info.UserSector[x]==SECTOR_NOUSER)
							{
							File_Folder.FileType=TYPE_DIR;
							i=strlen(dirname);
							memcpy(File_Folder.DirName,(char*)dirname,i);
							File_Folder.DirName[i]=0;
							File_Folder.FileNum=0;//���ļ���
								
							Err_f=Nand_EraseBlock((x));//*NF_BLOCK_BYTES)>>11);// �����ǰ��
								
							if(Err_f==1)
								{		
								Sector_Info.BadSector[x]=SECTOR_BAD;//��־Ϊ����
								Sector_Info.UserSector[x]=SECTOR_BAD_USER;//��Ӧ�Ļ����־Ϊʹ��
								}		
								
							sd=(unsigned char*)&File_Folder.FileType;
							Nand_Write_1Page(sd,x*NF_BLOCK_PAGES); //д��Ŀ¼��Ϣͷ
								
						//	for(i=0;i<10000000;i++);
								
							Sector_Info.UserSector[x]=SECTOR_USER;//��־������ʹ��
								
							File_Debug("\r\nDir :\" ",0);	
							File_Debug(dirname,0);	
							File_Debug(" \"is Created...\r\n",1);	
								
							//	sprintf(ascbuf,"%d",x);
							//ASCII_Printf(ascbuf,ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,40,180,0xffff,0);

							foldersector=x;
							break;								
							}											
					}				
		}
if(x>=FILE_FILE_START_SECTOR)
	return 0;
else
	return foldersector;
}

 //��ȡFREE SECTOR 
 int File_GetFreeSector_N(unsigned int flen)
{
int startsector;
int n;
for(startsector=FILE_FILE_START_SECTOR;startsector<(MAX_SECTOR);startsector++)
	{
	if(startsector>=(MAX_SECTOR-flen))
		{
		File_Debug("No Free Block......\r\n:",1);		
		return -1;//�޿ռ�
		}
	for(n=0;n<flen;n++)
		{
		if(Sector_Info.UserSector[startsector+n]!=SECTOR_NOUSER)
			break;
		}
	if(n>=flen)
		{//�ҵ�����sector;
				
		File_Debug("Free Block Add is:",0);		
		sprintf(ascbuf,"%d",startsector);
		File_Debug(ascbuf,1);	
		return startsector;
		}
	}

File_Debug("No Free Block......\r\n:",1);		
return -1;//�޿���
}



//*************************************************
//����һ���ļ����Ƿ���� ����һ����ַ

unsigned int File_FindFolder(char *folder)  //����һ���ļ����Ƿ���� ����һ����ַ
{
unsigned int x;
unsigned char *sd;
int i;
x=FILE_DIR_START_SECTOR;	
	
i=sizeof(File_Folder);

//////File_Debug("ReadBuf Size :",0);		
//////sprintf(ascbuf,"%d",i);
//////File_Debug(ascbuf,1);		

	
for(x=FILE_DIR_START_SECTOR;x<FILE_FILE_START_SECTOR;x++)
	{
	sd=(unsigned char*)&File_Folder.FileType;
	Nand_ReadDates(sd,x*128*1024,i);		

	if(File_Folder.FileType==TYPE_DIR)//��Ŀ¼
			{
//////			File_Folder.DirName[127]=0;				
//////			File_Debug(File_Folder.DirName,1);
			if(strcmp(folder,File_Folder.DirName)==0)
					{					
					File_Debug("Find Dir:",0);
					File_Debug(folder,0);						
					File_Debug(" ......Block Add As:",0);		
					sprintf(ascbuf,"%d",x);
					File_Debug(ascbuf,1);					
					return x;						//�ҵ�Ŀ¼�����ص�ǰ�Ŀ��ַ
					}							
			}		
	}	
	File_Debug("Not find Dir:",0);
	File_Debug(folder,1);
return 0;   //û���ҵ�Ŀ¼			
}


void File_Debug(char *str,uint8_t flag)
{
#ifdef FILE_DEBUG
UART0_SendStr(str);
	
if(flag!=0)
	UART0_SendStr("\r\n");	
#endif

}



//***************************************************
// ����һ���ļ�

unsigned char File_Create(char *fname)  //����һ���ļ�
{
 unsigned char nametemp[64];
unsigned char *fnametemp=(unsigned char *)&iFiles.FileName;
unsigned int sector,wsector;
unsigned int startsector;
unsigned int dirsector;

int i=0;
int n=0;
int filenumtemp;
unsigned char *sd;
unsigned int length;
int nedd_sector=0;

File_Debug("Now Create files is:",0);
File_Debug(fname,1);

File_Debug("File Length : ",0);
sprintf(ascbuf,"%d",iFiles.FileLength);
File_Debug(ascbuf,1);
File_Debug("\r\n",0);


File_Write_Cou++;
File_Debug("\r\n",0);
File_Debug("File Write Cou Is : ",0);
sprintf(ascbuf,"%d",File_Write_Cou);
File_Debug(ascbuf,1);
File_Debug("\r\n",0);


while(fname[i]!=0)
{
  nametemp[i]=fname[i];
  i++;
}
  nametemp[i]=fname[i];

i=0;
FolderName[0];
if(fname[i++]=='\\')
	{//��Ŀ¼����
	while(fname[i++]!='\\')
		{
		FolderName[n++]=fname[i-1];
		}
	FolderName[n]=0;
        n=0;

	while(fname[i++]!=0)
		{
		NameTemp[n++]=fname[i-1];
		}
	NameTemp[n]=0;

	length=iFiles.FileLength;


	dirsector=File_CreateFolder(FolderName);//���Ҳ�����Ŀ¼  ����Ŀ¼����Ŀ¼��
	if(dirsector==0)
		return 0;


	startsector=iFileFolder.iFileFolderSector;//��ȡĿ¼���ַ
	FileStartSector=startsector;
	iFiles.FileLength=length;
		
	//Printf24("�ļ�����",0,0,0,1,0xf7a2);
	n=0;
	while(NameTemp[n]!=0)
		{
		nFiles.FileName[n]=NameTemp[n];
		n++;
		}
	nFiles.FileName[n]=NameTemp[n];
	
	}
else
	{//	 ����Ŀ¼����

	dirsector=File_CreateFolder("\\");//���Ҳ�����Ŀ¼  ����Ŀ¼����Ŀ¼��
	if(dirsector==0)
		return 0;
    length=iFiles.FileLength;

	}


//Printf24("�Ƿ�����",0,0,0,1,0xf7a2);
fnametemp=(unsigned char *)&iFiles.FileName;

if(File_Find((unsigned char *)&nametemp)==1)
	{//�Ѵ��ڸ���

	 //�ָ�ԭ���ļ�  ʹ�õĿ� 
	 if(nFiles_Temp.FileLength>=NF_BLOCK_BYTES)
			{
			nedd_sector=nFiles_Temp.FileLength/NF_BLOCK_BYTES;
			}
	else
		nedd_sector=0;
	nedd_sector++;

	 //��ԭ��ʼ���� ��ռ�� ���  ������ ʹ�õĿ�

	 for(i=0;i<nedd_sector;i++)
			{
			 Sector_Info.UserSector[i+nFiles_Temp.FileSectorAddr]=SECTOR_NOUSER;
		//	SectorInUser[i+nFiles_Temp.FileSectorAddr]=UNUSER;  //�����ռ��
			}


		//Save_Sector_Info();//�����ʹ����Ϣ



	   //��ȡ�ռ�   ��д����ļ� ���п�
		if(iFiles.FileLength>=NF_BLOCK_BYTES)
			{
			nedd_sector=iFiles.FileLength/NF_BLOCK_BYTES;
			}
		else
			nedd_sector=0;
		nedd_sector++;

	   //��ȡ�ռ�
		sector=File_GetFreeSector_N(nedd_sector);
		if(sector>0)
				{
				for(n=sector;n<nedd_sector+sector;n++)
					{
					Sector_Info.UserSector[n]=SECTOR_USER;
					Nand_EraseBlock(n);//*NF_BLOCK_BYTES)>>11);
					}
				}
		else
				{
				File_Debug("Find _Create failed...",1);
				return 0;//�޿��ÿռ䣬����ʧ��
				}
sector=nFiles_Temp.FileSectorAddr;
		Save_Sector_Info();//�����ʹ����Ϣ


		FileNum=FindFileNum;//�ҵ���λ��//File_Folder_Temp.FileNum;

		File_Folder_Temp.DirName[127]=0;
		File_Debug(File_Folder_Temp.DirName,1);

		Nand_ReadBlock(File_Folder_Temp.StartSectorAddr,(unsigned char *)NF_SECTOR_SDRAM_BUF);//��ȡ �ļ�name��Ϣ
		
		File_Debug("Now Erase Block for Dir sector block is :",0);
		sprintf(ascbuf,"%d",File_Folder_Temp.StartSectorAddr);
		File_Debug(ascbuf,1);

		Nand_EraseBlock(File_Folder_Temp.StartSectorAddr);
		Nand_FillPage_SDbuf(FileNum,FILE_INFO_LENGTH,0xff); //ɾ��ԭ�е���Ϣ �����ļ��������ȣ���ַ  ����Ŀ¼��

		
		fnametemp=(uint8_t *)&nFiles;//.FileType;
		nFiles.FileSectorAddr=sector;
		nFiles.FileLength=iFiles.FileLength;

		// 
        Nand_WritePage_SDbuf(FileNum,FILE_INFO_LENGTH,fnametemp);
		Nand_WriteBlock(File_Folder_Temp.StartSectorAddr,(unsigned char *)NF_SECTOR_SDRAM_BUF);	
		

		wsector=sector;
		for(i=0;i<nedd_sector;i++)
			{
			Nand_EraseBlock(((wsector+i)));//*NF_BLOCK_BYTES)>>11);
			}


		FileWrite(0,nFiles.FileLength);
			
		File_Debug("Find _Create Ok.... The File Save start block is :",0);
		sprintf(ascbuf,"%d",sector);
		File_Debug(ascbuf,1);

		File_Debug("This Dir FileNum is :",0);
		sprintf(ascbuf,"%d",FileNum);
		File_Debug(ascbuf,1);
		File_Debug("\r\n",0);
		//SaveUnUserSector();
	}
else
	{//�ļ������ڴ���
		//Printf24("�½��ļ�",0,0,0,1,0xf7a2);

		if(FolderName[0]!=0)
			{
			dirsector=File_CreateFolder(FolderName);
			if(dirsector==0)
				{// �޷�����Ŀ¼
				File_Debug("Not Free space Create DIR...",1);
				}
			else
				{//���ҵ�Ŀ¼
				File_Folder_Temp.StartSectorAddr=dirsector;

				File_Debug("Cur Dir block is :",0);
				sprintf(ascbuf,"%d",dirsector);
				File_Debug(ascbuf,1);
				}
			}
//		File_FindFolder("APP1");

		nFiles.FileLength=length;

      

	   //��ȡ�ռ�
		if(nFiles.FileLength>=NF_BLOCK_BYTES)
			{
			nedd_sector=nFiles.FileLength/NF_BLOCK_BYTES;
			}
		else
			nedd_sector=0;
		nedd_sector++;

	   //��ȡ�ռ�
		sector=File_GetFreeSector_N(nedd_sector);
		if(sector>0)
				{
				for(n=sector;n<nedd_sector+sector;n++)
					{
					Sector_Info.UserSector[n]=SECTOR_USER;
					Nand_EraseBlock(n);//*NF_BLOCK_BYTES)>>11);
					}
				}
		else
				{
				File_Debug("Find _Create failed...",1);
				return 0;//�޿��ÿռ䣬����ʧ��
				}


		Save_Sector_Info();//�����ʹ����Ϣ


		

		File_Folder_Temp.FileNum++;
		FileNum=File_Folder_Temp.FileNum;

		File_Folder_Temp.DirName[127]=0;
		File_Debug(File_Folder_Temp.DirName,1);

		Nand_ReadBlock(File_Folder_Temp.StartSectorAddr,(unsigned char *)NF_SECTOR_SDRAM_BUF);//��ȡ �ļ�name��Ϣ

		File_Debug("Now Erase Block for Dir sector block is :",0);
		sprintf(ascbuf,"%d",File_Folder_Temp.StartSectorAddr);
		File_Debug(ascbuf,1);

		Nand_EraseBlock(File_Folder_Temp.StartSectorAddr);

		Nand_FillPage_SDbuf(FileNum,FILE_INFO_LENGTH,0xff); //ɾ��ԭ�е���Ϣ �����ļ��������ȣ���ַ  ����Ŀ¼��



		fnametemp=(uint8_t *)&nFiles;//.FileType;
		nFiles.FileSectorAddr=sector;

		i=0;
		while(nametemp[i]!=0)
		{
		nFiles.FileName[i]=nametemp[i];
		i++;
		}
		nFiles.FileName[i]=0;
		nFiles.FileLength=iFiles.FileLength;
		nFiles.FileType=TYPE_FILE;


		File_Folder_Temp.FileType=TYPE_DIR;

		memcpy((uint8_t *)NF_SECTOR_SDRAM_BUF,(uint8_t *)&File_Folder_Temp,512);//  �����ļ���
		
		Nand_WritePage_SDbuf(FileNum,FILE_INFO_LENGTH,fnametemp);
		Nand_WriteBlock(File_Folder_Temp.StartSectorAddr,(unsigned char *)NF_SECTOR_SDRAM_BUF);	
		

		wsector=sector;
		for(i=0;i<nedd_sector;i++)
			{
			Nand_EraseBlock(((wsector+i)));//*NF_BLOCK_BYTES)>>11);
			}

		FileWrite(0,nFiles.FileLength);		

		File_Debug("Find _Create Ok.... The File Save start block is :",0);
		sprintf(ascbuf,"%d",sector);
		File_Debug(ascbuf,1);

		File_Debug("This Dir FileNum is :",0);
		sprintf(ascbuf,"%d",FileNum);
		File_Debug(ascbuf,1);

		File_Debug("\r\n",0);

	}
}





unsigned int File_Find(char *fname)  //����һ���ļ��Ƿ���� ����һ����ַ
{
int i;
unsigned char *sd;
unsigned short sector;
unsigned short page=0;
unsigned short pagecou;
unsigned int add;
unsigned char namematch_flag=0;
 unsigned char *nametemp;
int fn;
FILES_N *pFiles;
FILE_FOLDER *pFileFolder;
//int FileNum=0;
//unsigned char *nametemp;
unsigned char *fnametemp=(unsigned char *)&iFiles.FileName;
unsigned int wsector;
unsigned int startsector;
unsigned int length;
int x;
int filenum;
//int i=0;
int n=0;
i=0;
File_Debug("Now find files is:",0);
File_Debug(fname,1);
FolderName[0]=0;
if(fname[i++]=='\\')
	{//��Ŀ¼����
	while(fname[i++]!='\\')
		{
		FolderName[n++]=fname[i-1];
		}
	FolderName[n]=0;

   n=0;
	while(fname[i++]!=0)
		{
		fname[n++]=fname[i-1];
		}
	fname[n]=0;

	length=iFiles.FileLength;

	ChangeFileName(fname); //ת������
	

	startsector=File_FindFolder(FolderName);

	File_Debug("\r\n",0);

//	File_Debug(FolderName,0);
//	File_Debug("Now find dir block is:",0);
//	sprintf(ascbuf,"%d",startsector);
//	File_Debug(ascbuf,1);

	if(startsector!=0)
		{
		Nand_ReadBlock(startsector,(unsigned char *)NF_SECTOR_SDRAM_BUF);//��ȡ Ŀ¼ָ��Ŀ� ��Ϣ�ļ�name��Ϣ

		memcpy(&File_Folder_Temp,(uint8_t*)NF_SECTOR_SDRAM_BUF,512);
		File_Folder_Temp.StartSectorAddr=startsector;

		
		wsector=NF_SECTOR_SDRAM_BUF+2048;		

		for(filenum=0;filenum<8*63;filenum++)
				{
				pFiles=(FILES_N *)wsector;
				if(strcmp(fname,pFiles->FileName)==0)
					{
					//�������ļ���Ϣ�ݴ�
					memcpy((uint8_t*)&nFiles_Temp,(uint8_t*)pFiles,256);
					
					File_Debug("Find the file name is:",0);
					File_Debug(pFiles->FileName,1);


					File_Debug("Find the file with dir \"\\",0);
					File_Debug(FolderName,0);
					File_Debug(" \\",0);
					File_Debug(fname,0);
					File_Debug(" \"on :  ",0);
					sprintf(ascbuf,"%d",nFiles_Temp.FileSectorAddr);
					File_Debug(ascbuf,1);


					FindFileNum=filenum;

					File_Debug("File Num is...: ",0);
					sprintf(ascbuf,"%d",filenum);
					File_Debug(ascbuf,1);

					File_Debug("File Length : ",0);
					sprintf(ascbuf,"%d",nFiles_Temp.FileLength);
					File_Debug(ascbuf,1);
					File_Debug("\r\n",0);

					return 1;//�ҵ��ļ�
					}
//		sprintf(ascbuf,"%x",pFiles);
//		File_Debug(ascbuf,1);
				wsector+=256;
				}


		File_Debug("not  find  file...\r\n",1);
		return 0; //�Ҳ����ļ�
		}
	else
		{
		//Printf24("û��Ŀ¼",0,0,0,1,0xf7a2);
		iFiles.FileLength=length;
		File_Debug("not  find  dir & file...\r\n",1);
		return 0;//�Ҳ����ļ�
		}
	}
else
	{//	  ��Ŀ¼����������Ŀ¼������

	//dirsector=File_CreateFolder("\\");//���Ҳ�����Ŀ¼  ����Ŀ¼����Ŀ¼��

	length=iFiles.FileLength;

	ChangeFileName(fname); //ת������
	

	startsector=File_FindFolder("\\");

	File_Debug("\r\n",0);


	if(startsector!=0)
		{
		Nand_ReadBlock(startsector,(unsigned char *)NF_SECTOR_SDRAM_BUF);//��ȡ Ŀ¼ָ��Ŀ� ��Ϣ�ļ�name��Ϣ

		memcpy(&File_Folder_Temp,(uint8_t*)NF_SECTOR_SDRAM_BUF,512);
		File_Folder_Temp.StartSectorAddr=startsector;
					File_Debug("File Num is...: ",0);
					sprintf(ascbuf,"%d",File_Folder_Temp.FileNum);
					File_Debug(ascbuf,1);
		
		wsector=NF_SECTOR_SDRAM_BUF+2048;		

		for(filenum=0;filenum<8*63;filenum++)
				{
				pFiles=(FILES_N *)wsector;
				if(strcmp(fname,pFiles->FileName)==0)
					{
					//�������ļ���Ϣ�ݴ�
					memcpy((uint8_t*)&nFiles_Temp,(uint8_t*)pFiles,256);
					
					File_Debug("Find the file name is:",0);
					File_Debug(pFiles->FileName,1);


					File_Debug("Find the file with no dir \"\\",0);
					File_Debug(FolderName,0);
					File_Debug(" \\",0);
					File_Debug(fname,0);
					File_Debug(" \"on :  ",0);
					sprintf(ascbuf,"%d",nFiles_Temp.FileSectorAddr);
					File_Debug(ascbuf,1);


					FindFileNum=filenum;

					File_Debug("File Num is...: ",0);
					sprintf(ascbuf,"%d",filenum);
					File_Debug(ascbuf,1);

					File_Debug("File Length : ",0);
					sprintf(ascbuf,"%d",nFiles_Temp.FileLength);
					File_Debug(ascbuf,1);
					File_Debug("\r\n",0);

					return 1;//�ҵ��ļ�
					}
//		sprintf(ascbuf,"%x",pFiles);
//		File_Debug(ascbuf,1);
				wsector+=256;
				}


		File_Debug("not  find  file...\r\n",1);
		return 0; //�Ҳ����ļ�
		}
	else
		{
		//Printf24("û��Ŀ¼",0,0,0,1,0xf7a2);
		iFiles.FileLength=length;
		File_Debug("not  find  dir & file...\r\n",1);
		return 0;//�Ҳ����ļ�
		}

		/*
		for(x=FILE_DIR_START_SECTOR;x<FILE_FILE_START_SECTOR;x++)
					{
					File_Debug("Find the file with No dir \"   ",0);
					File_Debug(fname,0);
					File_Debug(" \"on :  ",0);
					sprintf(ascbuf,"%d",x);
					File_Debug(ascbuf,1);

					Nand_ReadBlock(x,(unsigned char *)NF_SECTOR_SDRAM_BUF);//��ȡ Ŀ¼ָ��Ŀ� ��Ϣ�ļ�name��Ϣ

					memcpy(&File_Folder_Temp,(uint8_t*)NF_SECTOR_SDRAM_BUF,512);
					File_Folder_Temp.StartSectorAddr=x;

					wsector=NF_SECTOR_SDRAM_BUF+2048;

					pFileFolder=NF_SECTOR_SDRAM_BUF;
					if(pFileFolder->DirName[0]!=0)
						{//ָ����һ��Ŀ¼��

						}
					else
						{
						for(filenum=0;filenum<8*63;filenum++)
							{
							pFiles=wsector;
							if(strcmp(fname,pFiles->FileName)==0)
								{
							//	if(pFiles->DirName[0]==0)
							//		{
									//�������ļ���Ϣ�ݴ�
								//�������ļ���Ϣ�ݴ�
								memcpy(&nFiles_Temp,(uint8_t*)pFiles,256);
					
								File_Debug("Find the file name is:",0);
								File_Debug(pFiles->FileName,1);


								File_Debug("Find the file with dir \"\\",0);
								File_Debug(FolderName,0);
								File_Debug(" \\",0);
								File_Debug(fname,0);
								File_Debug(" \"on :  ",0);
								sprintf(ascbuf,"%d",nFiles_Temp.FileSectorAddr);
								File_Debug(ascbuf,1);


								FindFileNum=filenum;

								File_Debug("File Num is...: ",0);
								sprintf(ascbuf,"%d",filenum);
								File_Debug(ascbuf,1);

								File_Debug("File Length : ",0);
								sprintf(ascbuf,"%d",nFiles_Temp.FileLength);
								File_Debug(ascbuf,1);
								File_Debug("\r\n",0);
									return 1;//�ҵ��ļ�
								//	}
								}
							wsector+=256;
							}
						}
					}
		File_Debug("not  find  file...\r\n",1);
		return 0; //�Ҳ����ļ�

		*/
	}
}




unsigned char FileWrite(unsigned char *fhandle,unsigned int length)
{
int page;
int wpage;
unsigned char *copyptr;
int cblock;

if(length>=NF_PAGE_BYTES)
	wpage=length/NF_PAGE_BYTES;
else 
 wpage=0;

copyptr=(unsigned char *)DOWNFILE_SDRAM_ADD;
cblock=nFiles.FileSectorAddr;

for(page=0;page<=wpage;page++)
	{
	Nand_Write_1Page(copyptr, cblock*NF_BLOCK_PAGES+page);//дһҳ
	copyptr+=NF_PAGE_BYTES;
	}	
}




unsigned char FileRead(char *fname,unsigned char *sdbuf)//��ȡ�ļ���sdbuf
{
unsigned int fileAdd;
unsigned int length;

File_Debug("Now Read files is:",0);
File_Debug(fname,1);

if(File_Find(fname)==1)//�����ļ����Ƿ����
	{//�Ѵ���  ��ȡ�ļ����ڴ� buf
	length=nFiles_Temp.FileLength;
	fileAdd=nFiles_Temp.FileSectorAddr<<NF_BLOCK_BITS;
	Nand_ReadDates(sdbuf,fileAdd,length);

	File_Debug("Read the file with dir \"\\",0);
	File_Debug(FolderName,0);
	File_Debug(" \\",0);
	File_Debug(fname,0);
	File_Debug(" \"on :  ",0);
	sprintf(ascbuf,"%d",nFiles_Temp.FileSectorAddr);
	File_Debug(ascbuf,1);


	File_Debug("Read File Num is...: ",0);
	sprintf(ascbuf,"%d",File_Folder_Temp.FileNum);
	File_Debug(ascbuf,1);

	File_Debug("Read File Length : ",0);
	sprintf(ascbuf,"%d",nFiles_Temp.FileLength);
	File_Debug(ascbuf,1);
	File_Debug("\r\n",0);

	return 1;
	}
else
	{//�ļ������ڴ���	
	return 0;
	}
}


unsigned char  FileFolderRead(unsigned char *str,unsigned char *buff)
{
unsigned char fname[128];
int i;
i=0;
if(*str=='\\')   //��Ŀ¼��
	{
	return FileRead(str,buff);
	}
else
	{
	switch(BootFolder)
		{
		case 1:
			fname[i++]='\\';
			fname[i++]='A';
			fname[i++]='P';
			fname[i++]='P';
			fname[i++]='1';
			fname[i++]='\\';
			while(*str!=0)
			{
			fname[i++]=*str++;
			}
			fname[i]=*str;
			return FileRead(fname,buff);
			break;
		case 2:
			fname[i++]='\\';
			fname[i++]='A';
			fname[i++]='P';
			fname[i++]='P';
			fname[i++]='2';
			fname[i++]='\\';
			while(*str!=0)
			{
			fname[i++]=*str++;
			}
			fname[i]=*str;
			return FileRead(fname,buff);
			break;
		case 3:
			fname[i++]='\\';
			fname[i++]='A';
			fname[i++]='P';
			fname[i++]='P';
			fname[i++]='3';
			fname[i++]='\\';
			while(*str!=0)
			{
			fname[i++]=*str++;
			}
			fname[i]=*str;
			return FileRead(fname,buff);
			break;
		case 4:
			fname[i++]='\\';
			fname[i++]='A';
			fname[i++]='P';
			fname[i++]='P';
			fname[i++]='4';
			fname[i++]='\\';
			while(*str!=0)
			{
			fname[i++]=*str++;
			}
			fname[i]=*str;
			return FileRead(fname,buff);
			break;
		case 5:
			fname[i++]='\\';
			fname[i++]='A';
			fname[i++]='P';
			fname[i++]='P';
			fname[i++]='5';
			fname[i++]='\\';
			while(*str!=0)
			{
			fname[i++]=*str++;
			}
			fname[i]=*str;
			return FileRead(fname,buff);
			break;
		case 6:
			fname[i++]='\\';
			fname[i++]='A';
			fname[i++]='P';
			fname[i++]='P';
			fname[i++]='6';
			fname[i++]='\\';
			while(*str!=0)
			{
			fname[i++]=*str++;
			}
			fname[i]=*str;
			return FileRead(fname,buff);
			break;
		default:
			fname[i++]='\\';
			fname[i++]='A';
			fname[i++]='P';
			fname[i++]='P';
			fname[i++]='1';
			fname[i++]='\\';
			while(*str!=0)
			{
			fname[i++]=*str++;
			}
			fname[i]=*str;
			return FileRead(fname,buff);
			break;
		}
	}
}

