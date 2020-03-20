/**************************************************************************//**
* @file     main.c
* @version  V1.00
* $Revision: 2 $
* $Date: 15/06/12 9:11a $
* @brief    NUC970 LCD sample source file
*
* @note
* Copyright (C) 2015 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "spi_config.h"
#include "uart_config.h"

#include "comm.h"
#include "chndot.h"
#include "drv_glcd.h"
#include "pic.h"
#include "pic_exec.h"
#include "down_status.h"
#include "download.h"
#include "file.h"
#include "word_lib.h"

#include "servo.h"
#include "bmp.h"
#include "nandflash.h"
#include "timer.h"
#include "port.h"
#include "touch.h"
#include "tsc2046.h"

#include "name_input.h"
#include "pinyin.h"
#include "nand_config.h"
#include "i2c_config.h"
#include "gtp.h"

#include "sdh.h"
#include "ff.h"
#include "diskio.h"

#include "sd_config.h"
#include "sdcopy.h"
#include "gtp_touch.h"

#include "code.h"


#include "comm_touch.h"
#include "keyboard.h"
#include "sysiotest.h"

#include "modbus.h"


Int32U uFlashID;




#define DISPLAY_RGB565
//#define DISPLAY_RGB888



__align(32) uint32_t u32CursorBuf[512];

int32_t main(void)
{
    uint8_t *u8FrameBufPtr, *u8OSDFrameBufPtr, i;
	int n;

    *((volatile unsigned int *)REG_AIC_MDCR)=0xFFFFFFFF;  // disable all interrupt channel
    *((volatile unsigned int *)REG_AIC_MDCRH)=0xFFFFFFFF;  // disable all interrupt channel

    outpw(REG_CLK_HCLKEN, 0x0527);
    outpw(REG_CLK_PCLKEN0, 0);
    outpw(REG_CLK_PCLKEN1, 0);

    sysDisableCache();
    sysFlushCache(I_D_CACHE);
    sysEnableCache(CACHE_WRITE_BACK);
			outpw(REG_CLK_PCLKEN0, 8);
    sysInitializeUART();
	
 n=5000000;
 while(n--);

    
	//	IO_Test();
	//	I2C_Test();
		Sys_DevInit();////ϵͳ��ʼ��

	
	
	
		#ifdef CAP_TOUCH			//touch.h �ﶨ��
		
		Gtp_IO_Init();//���ݴ�������ʼ��
				 
		#else
				Uart8_Init();//-------touchcomm    ����ͨѶ  UART8	
		#endif
			

		

		
		//while(Nand_Config()!=0);//nand ��ʼ��	
		Nand_Config();File_Init();
		 n=1000000;
 while(n--);
				GLCD_Buffer_Fill(BLUE_COLOR);
		//SD_main();
		SDInsert_Check();
		//Nand_Config();
		
		GLCD_Buffer_Fill(BLUE_COLOR);
	//	GLCD_SetWindow_Fill(0,0,C_GLCD_H_SIZE-1,C_GLCD_V_SIZE-1,0xffff,BLUE_COLOR);
		
	
//////		SysIO_Test();//��� IO����
		
//FileRead("�ֿ�_0x20000.FON",(unsigned char *)df_zk_sdram);
 //ASCII_Printf("LoadingOK",ASCII1632_MODE,ASCII1632_WIDTH,ASCII1632_HIGH,ASCII1632,40,180,0xffff,0);
		Process_Main();//////��ת����7����� ����
    while(1)
		{
		CheckOp_IN();
		read_time();
		}
}
/*** (C) COPYRIGHT 2015 Nuvoton Technology Corp. ***/
