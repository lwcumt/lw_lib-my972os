#include"sdcopy.h"
#include "sd_config.h"
#include "ff.h"
#include "file.h"
#include "word_lib.h"
#include "nandflash.h"
#include "chndot.h"
#include "drv_glcd.h"

int Rrca;
int filetotalnum;
int filewritenum;


void SDInsert_Check(void)
{
int i;
int n;
int 	validocr;
int	ocrtries;
unsigned int  buff1[516];
  //SD_CMDRESP_T resp;
  unsigned int sblk;
  sblk=1;

 // if (SD_CD_IN() == FALSE)
// {
//  //Printf24("SD���Ѳ��룬���ڿ����ļ�........",810,50,RED_COLOR,1,0xffff);

 BellOUT_ON;
 i=1000000;
 while(i--);
 i=1000000;
 while(i--);
  i=1000000;
 while(i--);
  i=1000000;
 while(i--);
  i=1000000;
 while(i--);
 BellOUT_OFF;

	SD_PWR_OFF();
	SD_PWR_DIR();

	if(GPIO_ReadBit(GPIOD,BIT6)==0)
	{

	SD_PWR_ON();
	SD_main();

   SD_FileReadAndWriteToNandFlash();//��ȡ�ļ���д��NANDFLASH

		//SD_Close();//�ر�SD��
	SD_PWR_OFF();
	}

//  }
 }




	


Int8U mf_scan_files(Int8U * path) 
{ 
	DIR dir;
	FILINFO fileinfo;

	Int16U ReadValue;
	FATFS fs;            // Work area (file system object) for logical drive
	FIL fsrc;      			// file objects
//	Int8U buffer[2048]; 		// file copy buffer
	UINT br;         		// File R/W count
	Int8U i=0;
	Int8U n;
	char a;
unsigned char pathname[64];
	unsigned char namelength;
	i=0;
	a='X';
	


	while(path[i]!=0)
	{
	pathname[i]=path[i];
  i++;		
	namelength=i;
	}
	filetotalnum=0;
   filewritenum=0;

FRESULT res;	   
    char *fn;   /* This function is assuming non-Unicode cfg. */ 
	
#if _USE_LFN 
 	fileinfo.lfsize = _MAX_LFN * 2 + 1; 
	 char name[255*2+1];//.lfsize];
fileinfo.lfname =( char*)&name; //mymalloc(SRAMIN,fileinfo.lfsize); 
#endif	   

    res = f_opendir(&dir,(const char*)path); //��һ��Ŀ¼ 
    if (res == FR_OK)  
{	

while(1) 
{ 
        res = f_readdir(&dir, &fileinfo);                   //��ȡĿ¼�µ�һ���ļ� 
        if (res != FR_OK || fileinfo.fname[0] == 0) break;  //������/��ĩβ��,�˳� 
        //if (fileinfo.fname[0] == '.') continue;             //�����ϼ�Ŀ¼ 
#if _USE_LFN 
        	fn = *fileinfo.lfname ? fileinfo.lfname: fileinfo.fname; 
#else	    
        	fn = fileinfo.fname; 
#endif	                                              /* It is a file. */ 
	
	filetotalnum++;
	n=namelength;

   pathname[n++]='\\';
	i=0;
   while(fn[i]!=0)
	{

	pathname[n++]=fn[i++];
	}
	pathname[n]=fn[i];

//pathname[0]=pathname[1];
   res = f_open(&file1, (char*)pathname, FA_OPEN_EXISTING | FA_READ);	 //����ͼƬ�ļ���

  if(res==FR_NO_FILE||res==FR_INVALID_NAME){

  }
  else
  {
		//Printf24("��ȡ�ļ�",0,0,0,1,0xf7a2);
	iFiles.FileLength=file1.fsize;
    res = f_read(&file1, (unsigned char *)DOWNFILE_SDRAM_ADD, file1.fsize, &br);
		f_close(&file1);
//Printf24("��ȡ���",0,0,0,1,0xf7a2);
    filewritenum++;
	//ChangeFileName((unsigned char*)fn);
	ChangeFileName1((unsigned char*)pathname);
		//Printf24("�ļ�����",0,0,0,1,0xf7a2);
	 GLCD_SetWindow_Fill(350, 300, 750, 380, BLUE_COLOR, BLUE_COLOR);
	 Printf24(iFiles.FileName,350,300,0,1,0xf7a2);

		//Printf24("д���ļ�",0,0,0,1,0xf7a2);
		
		if(strcmp((char*)fn,"�ֿ�_0x20000.FON")!=0)
			if(strcmp((char*)fn,".")!=0)
				if(strcmp((char*)fn,"..")!=0)
				File_Create(iFiles.FileName);//�����ļ�
//Printf24("д�����",0,0,0,1,0xf7a2);
	  }

   
}  
    }	   
//myfree(SRAMIN,fileinfo.lfname); 

    return res;	   
}


	


void SD_FileReadAndWriteToNandFlash(void)
{
	Int16U ReadValue;
	FATFS fs;            // Work area (file system object) for logical drive
	FIL fsrc;      			// file objects
//	Int8U buffer[2048]; 		// file copy buffer
	FRESULT res;         // FatFs function common result code
	UINT br;         		// File R/W count
	Int16U r_data,g_data,b_data;	
	Int32U	 tx,ty;//temp;
//	Int8U bmp[1024];


	unsigned char BootAppFileCou;

/*

   BootAppFileCou=0;
  f_mount(0, &fs);
  res = f_open(&fsrc, "Boot.bin", FA_OPEN_EXISTING | FA_READ);	 //����ͼƬ�ļ���
  if(res==FR_NO_FILE||res==FR_INVALID_NAME){
     f_mount(0, NULL);
  }
  else
  {
	BootAppFileCou++;
		f_close(&fsrc);
	f_mount(0, NULL);
   }
*/



	//if(BootAppFileCou==1)
	//{//������ʽ��
	  GLCD_SetWindow_Fill(350, 300, 750, 380, BLUE_COLOR, BLUE_COLOR);
	 ASCII_Printf("Formating", ASCII1632_MODE, ASCII1632_WIDTH, ASCII1632_HIGH, ASCII1632, 350, 300, 0xffff, 0);
	Nand_Format();//ɾ������ǻ���
	//}

 	

  GLCD_SetWindow_Fill(350, 300, 750, 380, BLUE_COLOR, BLUE_COLOR);
 ASCII_Printf("Now Starting Copy File", ASCII1632_MODE, ASCII1632_WIDTH, ASCII1632_HIGH, ASCII1632, 350, 300, 0xffff, 0);


res = f_open(&file1, "0:/�ֿ�_0x20000.FON", FA_OPEN_EXISTING | FA_READ);
	 
  if(res==FR_NO_FILE||res==FR_INVALID_NAME){
   //f_mount(fs,sd_path, 0);
  }
  else
  {
	iFiles.FileLength=file1.fsize;
    res = f_read(&file1, (unsigned char *)DOWNFILE_SDRAM_ADD, file1.fsize, &br);
	f_close(&file1);

	ChangeFileName("�ֿ�_0x20000.FON");
	//NandEccWrite_Flag=0;
	File_Create(iFiles.FileName);//�����ļ�
	  }
/*
   res = f_open(&file1, "Power.bmp", FA_OPEN_EXISTING | FA_READ);
	 
  if(res==FR_NO_FILE||res==FR_INVALID_NAME){
   //f_mount(fs,sd_path, 0);
  }
  else
  {
	iFiles.FileLength=file1.fsize;
    res = f_read(&file1, (unsigned char *)DOWNFILE_SDRAM_ADD, file1.fsize, &br);
	f_close(&file1);

	ChangeFileName("Power.bmp");
	//NandEccWrite_Flag=0;
	File_Create(iFiles.FileName);//�����ļ�
	  }

return;

*/


/*
   f_mount(0, &fs);
   res = f_open(&fsrc, "AppStartFile.ini", FA_OPEN_EXISTING | FA_READ);	 //����ͼƬ�ļ���
  if(res==FR_NO_FILE||res==FR_INVALID_NAME){
     f_mount(0, NULL);
  }
  else
  {
	iFiles.FileLength=fsrc.fsize;
    res = f_read(&fsrc, (unsigned char *)DOWNFILE_SDRAM_ADD, fsrc.fsize, &br);
	f_close(&fsrc);
	f_mount(0, NULL);
 
	ChangeFileName("AppStartFile.ini");
	NandEccWrite_Flag=0;
	File_Create(iFiles.FileName);//�����ļ�
	  }

*/

 FileRead("�ֿ�_0x20000.FON",(unsigned char *)df_zk_sdram);


//f_mount(0, &fs);

//mf_scan_files("0:");
mf_scan_files("0:/APP1");
//mf_scan_files("0:/APP2");
//mf_scan_files("0:/APP3");
//mf_scan_files("0:/APP4");
//mf_scan_files("0:/APP5");
//mf_scan_files("0:/APP6");
//f_mount(0, NULL);

///*
/*
    f_mount(0, &fs);
  res = f_open(&fsrc, "Boot.bin", FA_OPEN_EXISTING | FA_READ);	 //����ͼƬ�ļ���
  if(res==FR_NO_FILE||res==FR_INVALID_NAME){
     f_mount(0, NULL);
  }
  else
  {
	CommFileLenth=iFiles.FileLength=fsrc.fsize;

    res = f_read(&fsrc, (unsigned char *)DOWNFILE_SDRAM_ADD, fsrc.fsize, &br);
	f_close(&fsrc);
	f_mount(0, NULL);
 

      NandEccWrite_Flag=1;
				FileWirte_Boot();
 NandEccWrite_Flag=0;
*/
 delay(10000);


// */

  GLCD_SetWindow_Fill(350, 300, 750, 380, BLUE_COLOR, BLUE_COLOR);
 //Printf24("�ļ�������ɣ����Ƴ�SD��������",350,300,0,1,0xf7a2);
//................. 
// һ��92���ļ�
}




