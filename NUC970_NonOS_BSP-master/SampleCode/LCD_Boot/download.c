
#include"download.h"

#include"down_status.h"
#include"m25pe16.h"

#include"word_lib.h"
#include"pic_exec.h"
#include "uart_config.h"

Int16U tt;

Int32U Page=0; 

void DownFile_Exec(void)	//�ļ����ش���
{
	char stemp[8];
	pInt16U ptr;

if(CommFrame_Flag==1)
	{/*
	stemp[0]=CommLengthTemp/1000000+0x30;
	stemp[1]=(CommLengthTemp%1000000)/100000+0x30;
	stemp[2]=(CommLengthTemp%1000000)%100000/10000+0x30;
	stemp[3]=(CommLengthTemp%1000000)%100000%10000/1000+0x30;
	stemp[4]=(CommLengthTemp%1000000)%100000%10000%1000/100+0x30;
	stemp[5]=(CommLengthTemp%1000000)%100000%10000%1000%100/10+0x30;
	stemp[6]=(CommLengthTemp%1000000)%100000%10000%1000%100%10+0x30;
	stemp[7]=0;
	Printf24(stemp,100+24*18,66,0,1,0xf7a2);*/
	tt++;
	if(tt>=200)
	  {
	  tt=0;
	  GLCD_SetWindow_Fill(610,185,738,215,0xffff,0xffff);
	  Datas_dis( CommLengthTemp, 610,185);
	  }
	
	}


//����Ϊͨ�Ŵ����Ȳ�����ᡣ
   if(CommEnd_Flag==1)
	  {//֡���� 
	  CommEnd_Flag=0;
      
	//Datas_dis( CommLengthTemp, 610,185);
     GLCD_SetWindow_Fill(610,185,738,215,0xffff,0xffff);
	  Datas_dis( CommLengthTemp, 610,185);
	  switch(CommCommd)
		  {
		  case COMMD_WRITE_BMP_FLASH:	

				  break;
		  case COMMD_WRITE_FILE_FLASH:

				  break;
		  case COMMD_READ_FLASH_SDRAM:	//ֱ�ӷ���   ��FLASH����SDRAM

				  break;
		  case COMMD_WRITE_SDRAM_FLASH:	//ֱ�ӷ���   ��SDRAMд��FLASH

				  break;
		  case COMMD_ERASE_FLASH:	//ֱ�ӷ���		����FLASH

				  break;
		  case COMMD_CLR_SCREEN:	//ֱ�ӷ���     ����

				  break;
		  case COMMD_DISPLAY_BMP:    //ֱ�ӷ���   ��ʾͼƬ

				  break;
		  case COMMD_WRITE_SPI_FLASH: //����������� 
				fPtr=(pInt16U)0xa0100000;
		         Page=CommAdder;
				 Page*=528;
				 Page>>=8;
				 
			LED2_ON; 
			    GLCD_SetWindow_Fill(20,175,300,220,0x1f,0x1f);
				ASCII_Printf("LoadingSpiFlash",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,30,180,0xffff,0);  
				volatile Int32U i,d;
				Int8U Rx_buf[300];
				 //-------------------------flash�����޸�-------------------
				  for(i=0;i<=CommFileLenth/256;i++)
					  {
					   for(d=0;d<256;d++)
						  {
						   Rx_buf[d]=(Int8U)((Int16U)*fPtr&0xff);
//						   RBuf[d1]=(Int8U)(Int16U)*fPtr&0xff;
						   fPtr++;
						  }
					   Page_Write(Rx_buf,   Page++,   256);
					  
					  //---------------------��ʾ����
					   GLCD_SetWindow_Fill(610,185,738,215,0xffff,0xffff);
                       Datas_dis(Page<<8, 610 , 185  ); 
					  }	  
			LED2_OFF;		  
				GLCD_SetWindow_Fill(20,175,300,220,0x07e0,0x07e0);
			  ASCII_Printf("LoadingOK",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,40,180,0xffff,0);
				  break;

		  //*****************************************************
		  //���������ļ�����
		  case DOWNFILE_FILE_DELETE   ://  0x20 //ɾ��һ���ļ�  
				break;
		  case DOWNFILE_FILE_CREATE   ://0x21 //����һ���ļ�  
				break;
		  case DOWNFILE_FILE_CREATE_DIR:// 0x22 //����һ��Ŀ    
				break;
		  case DOWNFILE_FILE_SEND      :// 0x23 //����һ���ļ� 		

				iFiles.FileLength=CommFileLenth;//��ȡ�ļ�����	
				File_Create(iFiles.FileName);//�����ļ�
				FileRead("�ֿ�_0x20000.FON",(unsigned char *)df_zk_sdram);
				Printf24("�������!",400,350,0,1,0xf7a2);
		  		stemp[0]=0xaa;
				stemp[1]=0;
				UART0_SendStr(stemp);	
				break;
		  case DOWNFILE_FILE_SEND_NAME :// 0x24 //����һ���ļ���
				dfPtr=(unsigned char *)DOWNFILE_SDRAM_ADD;
				unsigned char *ifiles=(unsigned char *)iFiles.FileName;

				//GLCD_Buffer_Fill(BLUE_COLOR);

				while(*dfPtr!=0)
					{
					*ifiles++=*dfPtr++;
					}
				 *ifiles=0;
				
				Printf24("����....",400,350,0,1,0xf7a2);
				Printf24(iFiles.FileName,350,300,0,1,0xf7a2);
					stemp[0]=0xaa;
					stemp[1]=0;
					UART0_SendStr(stemp);
				break;

		  case DOWNFILE_FILE_FORMAT: //ϵͳ��ʽ��
				Nand_Format();//ɾ������ǻ���
			//	uartWrite(3, "FormatOK\r\n", 10);
			//	uartWrite(3, "FormatOK\r\n", 10);
			//UART0_SendStr("Format OK");
			UART0_SendStr("Format OKahjdjdhfhahl**************************************\r\n");
				stemp[0]=0xaa;
				stemp[1]=0;
				UART0_SendStr(stemp);    
//				File_Create("����.bmp");
//			    File_GetStartSector();//  
				break;
		  case DOWNFILE_FILE_BOOT://д��BOOT
				break;
		  case DOWNFILE_FILE_APP:  //д��APP
/*
				FileWriteToSPI(CommAdder);
				Printf24("�������:",100,66,0,1,0xf7a2);
				stemp[0]=0xaa;
				stemp[1]=0;
				UART0_SendStr(stemp); */
//				FileWriteToSPI(CommAdder);
				break;
		  }
	  }



//���Ͽ�������ͼƬ
//**************************************

}

