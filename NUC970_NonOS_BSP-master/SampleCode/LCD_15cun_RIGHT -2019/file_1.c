
#include "file.h"

#include "timer.h"



FILES iFiles;
FILES iFilesTemp;
FILE_STORE_INFO iFileSectorInfo;
FILE_NAME iFileName;

unsigned short FileNum;


void Nand_Format(void)
{
volatile Int32U block;
Int8U Err_f;
Nf_InvalidCou=0;

for(block=0;block<NF_BLOCKS;block++)
   InvalidBlock[block]=0xffff;

for(block=0;block<NF_BLOCKS;block++)
  {
  Err_f=Nand_EraseBlock(block);
  if(Err_f==1)
    {
	InvalidBlock[Nf_InvalidCou++]=block;
	}
  }   
  
File_CreateStartSector();
}

//******************************
void Nand_FillPage_SDbuf(unsigned short page,unsigned int length,unsigned char filldata)  //��� sdram�鸴�����е�һҳ
{
int i;
unsigned char *pSDbuf;
pSDbuf=(unsigned char *)NF_SECTOR_SDRAM_BUF;
pSDbuf+=page*FILE_INFO_LENGTH;

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
pSDbuf+=page*FILE_INFO_LENGTH;

for(i=0;i<length;i++)//���һҳ
	{
	*pSDbuf++=*wpdata++;
	}
}

//------------99999999999999999999999999999999999999999999
void Nand_FillFileInfo_SDbuf(unsigned short num,unsigned int length,unsigned char filldata)  //��� sdram�鸴�����е�һҳ
{
int i,page,add;
unsigned char *pSDbuf;
Int16U page_offset;
pSDbuf=(unsigned char *)NF_SECTOR_SDRAM_BUF;

page=num/FILE_INFO_NUMS_1PAGE;
page_offset=num%FILE_INFO_NUMS_1PAGE;
add=page*NF_PAGE_BYTES+page_offset*FILE_INFO_LENGTH;
pSDbuf+=add;
for(i=0;i<length;i++)//���һҳ
	{
	*pSDbuf++=filldata;
	}
}
void Nand_WriteFileInfo_SDbuf(unsigned short num,unsigned int length,unsigned char *wpdata) //��wpdata д�� sdram�鸴������ һҳ
{
int i,page,add;
unsigned char *pSDbuf;
Int16U page_offset;
pSDbuf=(unsigned char *)NF_SECTOR_SDRAM_BUF;

page=num/FILE_INFO_NUMS_1PAGE;
page_offset=num%FILE_INFO_NUMS_1PAGE;
add=page*NF_PAGE_BYTES+page_offset*FILE_INFO_LENGTH;
pSDbuf+=add;
for(i=0;i<length;i++)//���һҳ
	{
	*pSDbuf++=*wpdata++;
	}
}



unsigned char FileWrite(FILES file,  unsigned char *pSDbuf)//��  pSDbuf  ���濪ʼд�� nand
{
int b,block_add;
int p,page_add;
int block_sum=0;
int page_sum=0;
int length;
unsigned char s=0;

//***********�ļ���С
length=file.FileLength;
block_sum=length>>NF_BLOCK_BITS;
page_sum=length>>NF_PAGE_BITS;
//*********�ļ���ַ ��ʼ �飬ҳ  
block_add=file.FileAdd_Sector;
page_add=block_add*NF_BLOCK_PAGES;

//***************�Ȳ�����
for(b=0;b<=block_sum;b++)
	{
	s=Nand_EraseBlock(block_add++);//����һ��
	//if(s==1)
	//	break;
	}
//if(s==1) return s;	
//*************��д��ҳ
for(p=0;p<=page_sum;p++)
	{
	s=Nand_Write_1Page(pSDbuf, page_add++);//дһҳ
	pSDbuf+=NF_PAGE_BYTES;
	if(s==1)
		break;
	}	
return s;
}

unsigned char FileRead(unsigned char *fname,unsigned char *buf)//��ȡ�ļ���sdbuf
{
unsigned int fileAdd;
unsigned int filePage;
unsigned int length;
//unsigned char ram[NF_PAGE_BYTES];

if(File_Find(fname)==1)
	{//�Ѵ���
	length=iFilesTemp.FileLength;
	fileAdd=iFilesTemp.FileAdd_Sector<<NF_BLOCK_BITS;
	Nand_ReadDates(buf,fileAdd,length);
	/*
	filePage=iFilesTemp.FileAdd_Sector*NF_BLOCK_PAGES;
	while(length>0)
	   {
	    Nand_Read_1page(ram,filePage++);
	    if(length<NF_PAGE_BYTES)
	      {
		  memcpy(buf,ram,length);
		  length=0;
		  }
	    else
	      {
		  memcpy(buf,ram,NF_PAGE_BYTES);
		  length-=NF_PAGE_BYTES;
		  buf+=NF_PAGE_BYTES;
		  }
	   }*/
	return 1;
	}
else
	{//�ļ������ڴ���
	return 0;
	}
}

unsigned int  File_GetFreeSector(void)  //��ȡ���ÿ����� �׵�ַsector
{
int i;
unsigned char *f_buf;
unsigned int sector;
unsigned int page=0;
unsigned int f_num;
unsigned int n_add;
unsigned char filefree_flag=0;
unsigned char *nametemp;

unsigned int oldusesector=0;
unsigned int usesector;
int n;
int info_pages;

FileNum=0;

File_GetStartSector();//��ȡ��ʼ����Ϣ

//usesector=FILE_START_SECTOR;
usesector=0;//+++++++++++++++++++++

sector=iFileSectorInfo.iFileStartSector;

info_pages=FILE_NUMS/FILE_INFO_NUMS_1PAGE;

for(i=0;i<info_pages;i++)     //�������ļ���Ϣ
	{
	n_add=sector*NF_BLOCK_BYTES+page*NF_PAGE_BYTES;
	for(f_num=0;f_num< FILE_INFO_NUMS_1PAGE;f_num++)//��һҳ�ļ���Ϣ
		{
		f_buf=(unsigned char*)&iFilesTemp;
		//NF_Read(n_add,FILE_INFO_LENGTH,f_buf);	
		Nand_ReadDates(f_buf,n_add,FILE_INFO_LENGTH);//��ȡһ���ļ���Ϣ
		filefree_flag=1;
		for(n=0;n<32;n++)
			{
			if(*f_buf++!=0xff)            //��Ϣ�������ļ����ǿգ�    ....��������
				{
				filefree_flag=0;
				break;
				}
			}
		if(filefree_flag==1)
			break;

		FileNum++;
		n_add+=FILE_INFO_LENGTH;
		}
	if(filefree_flag==1)
		break;
	if(FileNum>=FILE_NUMS)
		{
		break;
		}
	page++;
	if(page>=NF_BLOCK_PAGES)//ִ�в���------------�ļ�����Ϣֻ��16 page������һ��
		{
		page=0;
		sector++;
		}
	}

Nf_InvalidCou=0;
while(1)
	{//��⻵��
	if(iFileSectorInfo.iFileSectorTable[Nf_InvalidCou]==0xffff)  //���㻵�����
		break;
	Nf_InvalidCou++;
	}

sector=iFileSectorInfo.iFileStartSector;
page=0;
int filenum=FileNum;
if(filefree_flag==1)
	{//�пռ�
	if(filenum>0)
		{
        filenum--;
		n_add=sector*NF_BLOCK_BYTES+page*NF_PAGE_BYTES+filenum*FILE_INFO_LENGTH; //����һ���ļ� ��Ϣ
		f_buf=(unsigned char*)&iFilesTemp;
		Nand_ReadDates(f_buf,n_add,FILE_INFO_LENGTH);

		oldusesector=iFilesTemp.FileLength>>NF_BLOCK_BITS;//  ������һ���ļ���ռ�õĿ� FileLength/NF_BLOCK_BYTES
		oldusesector++;
		usesector=iFilesTemp.FileAdd_Sector+oldusesector;//�� ��ǰ�ļ��Ŀ�

		sector=iFiles.FileLength>>NF_BLOCK_BITS;//���㵱ǰҪд�ļ�ռ�õĿ�  FileLength/NF_BLOCK_BYTES
		sector++;

		if(Nf_InvalidCou>0)
			{
			while(1)
				{
				for(i=0;i<Nf_InvalidCou;i++)
					{
					if(usesector<=iFileSectorInfo.iFileSectorTable[i])
						{
						usesector=iFileSectorInfo.iFileSectorTable[i]+1;
						if(usesector==iFileSectorInfo.iFileStartSector) //������ʼ��
							usesector++;
						if((usesector+sector)<iFileSectorInfo.iFileSectorTable[i+1])
							{
							return usesector; //���ص�ǰ���ÿ�	
							}
						}
					else
						{
						if(usesector==iFileSectorInfo.iFileStartSector)//������ʼ��
							usesector++;
						if((usesector+sector)<iFileSectorInfo.iFileSectorTable[i+1])
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
		usesector=FILE_START_SECTOR;//++++++++++++++++++++++++++++
		sector=iFiles.FileLength>>NF_BLOCK_BITS;//���㵱ǰҪд�ļ�ռ�õĿ�
		sector++;
                
		if(Nf_InvalidCou>0)
			{
			while(1)
				{
				for(i=0;i<Nf_InvalidCou;i++)
					{
					if(usesector<=iFileSectorInfo.iFileSectorTable[i])
						{
						usesector=iFileSectorInfo.iFileSectorTable[i]+1;
						if(usesector==iFileSectorInfo.iFileStartSector)
							usesector++;
						//��ʼ���������ã����жϺ�������---
						if((usesector+sector)<iFileSectorInfo.iFileSectorTable[i+1])//�������ÿ� �ռ����
							{
							return usesector; //���ص�ǰ���ÿ�	
							}
						}
					else
						{
						if(usesector==iFileSectorInfo.iFileStartSector)
							usesector++;
						if((usesector+sector)<iFileSectorInfo.iFileSectorTable[i+1])//�������ÿ� �ռ����
							{
							return usesector; //���ص�ǰ���ÿ�	
							}
						}
					}			
				}
			}
		else
			return usesector;//�޻��� ���ص�ǰ���ÿ�
		}
	}
else
	{//�޿ռ�
	return 0;//++++++++++++++
	}

}

unsigned char File_CreateStartSector(void) //���� ������ ϵͳ����Ϣ 
{
unsigned short s_sector;
//unsigned int *f_buf;
unsigned short *nfiv;
int i;

srand(sys_tick);
while(1)
	{
	s_sector=rand();
	s_sector/=NF_BLOCK_PAGES;
	if((s_sector<NF_BLOCKS)&&(s_sector>0)) //�ж��Ƿ�Ϊ���������ݿ� �����뻵���ж�		99999999999999999
		{
		if(Nf_InvalidCou>0)
			{
			for(i=0;i<Nf_InvalidCou;i++)
				{
				if(s_sector==InvalidBlock[i])
					break;
				}
			if(i==Nf_InvalidCou)//�뻵�鲻��ȣ���¼��ʼ���ַ
				break;
			}
		else
			break;//�޻��顣ֱ�Ӽ�¼��ʼ���ַ
		}
	}
//s_sector=0;
iFileSectorInfo.iFileStartSector=s_sector;

nfiv=(unsigned short *)iFileSectorInfo.iFileSectorTable;   //------�����ļ�����Ϣ
for(i=0;i<NF_BLOCKS;i++)
	{
	*nfiv++=InvalidBlock[i];
	}

unsigned char *f_buf=(unsigned char*)&iFileSectorInfo.iFileStartSector;
unsigned int p_add;
p_add=FILE_INFO_START_SECTOR*NF_BLOCK_PAGES;
p_add+=FILE_INFO_START_PAGE;//  ����ҳ��ַ
i=Nand_Write_1Page(f_buf,p_add);//дһҳ ����Ϣ
//i=Nand_WriteBytes(f_buf,FILE_INFO_START_SECTOR*NF_BLOCK_BYTES+FILE_INFO_START_PAGE*NF_PAGE_BYTES); //д�����Ϣͷ
if(i==1)
	return 1; //дͷ����
else
	return 0;//��ȷ
}

void File_GetStartSector(void) //��ȡһҳ ϵͳ����Ϣ
{
unsigned char *block_inf=(unsigned char*)&iFileSectorInfo.iFileStartSector;
unsigned int p_add;
p_add=FILE_INFO_START_SECTOR*NF_BLOCK_PAGES;
p_add+=FILE_INFO_START_PAGE;//  ����ҳ��ַ
Nand_Read_1page(block_inf, p_add);//��һҳ ����Ϣ
//Nand_ReadDates(block_inf,FILE_INFO_START_SECTOR*NF_BLOCK_BYTES+FILE_INFO_START_PAGE*NF_PAGE_BYTES,NF_PAGE_BYTES);
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

unsigned char File_Create(unsigned char *fname)  //����һ���ļ�
{
unsigned char *nametemp;
unsigned char *fnametemp;
unsigned int sector,wsector;
int i;

fnametemp=(unsigned char *)&iFiles.FileName;

if(File_Find(fname)==1)
	{//�Ѵ��ڸ���
	Nand_ReadBlock(iFileName.iFileNameSector,(unsigned char *)NF_SECTOR_SDRAM_BUF);//��ȡ �ļ�name��Ϣ
	sector=iFileName.iFileNameSector;
	Nand_EraseBlock(sector);
	Nand_FillFileInfo_SDbuf(FileNum,FILE_INFO_LENGTH,0xff); //ɾ��ԭ�е���Ϣ �����ļ��������ȣ���ַ
	iFiles.FileAdd_Sector=iFilesTemp.FileAdd_Sector;//��ȡ���ÿ�

	Nand_WriteFileInfo_SDbuf(FileNum,FILE_INFO_LENGTH,fnametemp);
	Nand_WriteBlock(iFileName.iFileNameSector,(unsigned char *)NF_SECTOR_SDRAM_BUF);

	FileWrite(iFilesTemp, (unsigned char *)DOWNFILE_SDRAM_ADD);
	}
else
	{//�ļ������ڴ���
	Nand_ReadBlock(iFileName.iFileNameSector,(unsigned char *)NF_SECTOR_SDRAM_BUF);//��ȡ �ļ�name��Ϣ
	sector=File_GetFreeSector();//��ȡ���ÿ�
	if(sector!=0)//�пռ�
	  {
	  iFiles.FileAdd_Sector=sector;
	  Nand_EraseBlock(iFileName.iFileNameSector);

	  //Nand_FillPage_SDbuf(FileNum,FILE_INFO_LENGTH,0xff); //ɾ��ԭ�е���Ϣ �����ļ��������ȣ���ַ
	  Nand_WriteFileInfo_SDbuf(FileNum,FILE_INFO_LENGTH,fnametemp);
	//  File_GetStartSector();//��ȡ��ʼ����Ϣ
      Nand_WriteBlock(iFileName.iFileNameSector,(unsigned char *)NF_SECTOR_SDRAM_BUF);
	//  File_GetStartSector();//��ȡ��ʼ����Ϣ
	
	  FileWrite(iFiles, (unsigned char *)DOWNFILE_SDRAM_ADD);
	 // File_GetStartSector();//��ȡ��ʼ����Ϣ
	  }
	}
}


unsigned int File_Find(unsigned char *fname)  //����һ���ļ��Ƿ����    ������ �ļ��� ��ַ
{
int p;
unsigned char *f_buf;
unsigned short sector;
unsigned short page=0;
unsigned short f_num;
unsigned int n_add;
unsigned char namematch_flag=0;
unsigned char *nametemp;
int info_pages;
//int FileNum=0;

File_GetStartSector();//��ȡ��ʼ����Ϣ

FileNum=0;//�ļ���������

sector=iFileSectorInfo.iFileStartSector;

info_pages=FILE_NUMS/FILE_INFO_NUMS_1PAGE;  //�ļ���Ϣռ�� ��ҳ��

for(p=0;p<info_pages;p++)
	{
	n_add=sector*NF_BLOCK_BYTES+page*NF_PAGE_BYTES;  //�ļ�����Ϣ ��ʼ��ַ
	for(f_num=0;f_num< FILE_INFO_NUMS_1PAGE;f_num++)//�ж�һҳ���ļ���
		{
		f_buf=(unsigned char*)&iFilesTemp;	
		Nand_ReadDates(f_buf,n_add,FILE_INFO_LENGTH);
//		f_buf=(unsigned char*)&filetemp->FileName;
		nametemp=(unsigned char *)fname;
		namematch_flag = 1; 
		while(*nametemp!=0)
			{
			if(*nametemp++ != *f_buf++)
				{
				namematch_flag = 0; 
				break;
				}
			}
		if(namematch_flag==1)
			break;
		FileNum++;
		n_add+=FILE_INFO_LENGTH;
		}

	if(namematch_flag==1)  //�ҵ��ļ�
		break;

	if(FileNum>=FILE_NUMS) //������ ȫ���ļ�
		break;

	page++;
	if(page>=NF_BLOCK_PAGES)	//ִ�в���------------�ļ�����Ϣֻ��16 page������һ��
		{
		page=0;
		sector++;
		}
	}

iFileName.iFileNameSector=sector;//nand�� ���ַ
/* //9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999 */
// iFileName.iFileNamePage=page;  //���� ҳƫ��
// iFileName.iFileNameAddress=n_add; //nand�� ���Ե�ַ
// iFileName.iFileNameIndex=p;  //�ļ�����λ��(�ļ�����Ϣ �ڵ�ҳ��)

if(namematch_flag==1)
	{
	return 1;  //�ҵ��ļ�
	}
else
	{
	return 0; //�Ҳ�����Ӧ�ļ�
	}
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
		//		Printf24("����....",400,350,0,1,0xf7a2);
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
		//		Printf24("����....",400,350,0,1,0xf7a2);
		//		Printf24(iFiles.FileName,350,300,0,1,0xf7a2);

}
