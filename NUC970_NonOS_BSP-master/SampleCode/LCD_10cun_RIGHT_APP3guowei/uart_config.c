#include "uart_config.h"
#include "comm.h"
#include "uart.h"
#include "keyboard.h"
#include "comm_touch.h"

 UART_T param;
 Int32U Rcv_New ;						// Ϊ1ʱ�������յ�������
 Int32U    Snd_N   ;						// ��¼����������Ϻ��跢�����ݵĸ���
 Int8U	  Rcv_Buf[0x80];						// �ַ���������	

 
Int8U Uart_mod;

Int8U Uart3_Data;
Int8U Uart9Data;
Int8U Uart8Data;
Int8U Uart6Data;

extern  UART_BUFFER_T UART_DEV[UART_NUM];

 void Uart3_Init(void)
 {
	 int retval;

	    // outpw(REG_SYS_GPE_MFPL, (inpw(REG_SYS_GPE_MFPL) & 0xff0000ff) | (0x9999 << 8));// GPE2, 3, 4, 5 //TX, RX, RTS, CTS
    outpw(REG_CLK_PCLKEN0, inpw(REG_CLK_PCLKEN0) | 0x80000);
	outpw(REG_SYS_GPE_MFPH, (inpw(REG_SYS_GPE_MFPH) & 0xff00ffff) |(0xaa<<16));// GPE2, 3, 4, 5 //TX, RX, RTS, CTS


    UART_DEV[3].bIsUseUARTRxInt = TRUE;
	 
    /* configure UART */
    param.uFreq = 12000000;
    param.uBaudRate = 115200;
    param.ucUartNo = UART3;
    param.ucDataBits = DATA_BITS_8;
    param.ucStopBits = STOP_BITS_1;
    param.ucParity = PARITY_NONE;
    param.ucRxTriggerLevel = UART_FCR_RFITL_1BYTE;

    retval = uartOpen(&param);	 


	    /* set RX interrupt mode */
	 retval = uartIoctl(param.ucUartNo, UART_IOC_SETRXMODE, UARTINTMODE, 0);

    /* set interrupt */
   // retval = uartIoctl(param.ucUartNo, UART_IOC_SETINTERRUPT, UARTINTMODE, (UART_IER_RLS_IEN_Msk|UART_IER_RTO_IEN_Msk));
	 
 }
 
 void UART6IntrHandler(void)
 {
	 
	 
 }
 
 
 void Uart8_Init(void)
 {
	 int retval;

	    // outpw(REG_SYS_GPE_MFPL, (inpw(REG_SYS_GPE_MFPL) & 0xff0000ff) | (0x9999 << 8));// GPE2, 3, 4, 5 //TX, RX, RTS, CTS
    outpw(REG_CLK_PCLKEN0, inpw(REG_CLK_PCLKEN0) | 0x0100000);
	outpw(REG_SYS_GPI_MFPH, (inpw(REG_SYS_GPI_MFPH) & 0xff00ffff) |(0x99<<16));// GPE2, 3, 4, 5 //TX, RX, RTS, CTS


     UART_DEV[8].bIsUseUARTRxInt = TRUE;
	 
    /* configure UART */
    param.uFreq = 12000000;
    param.uBaudRate = 9600;
    param.ucUartNo = UART8;
    param.ucDataBits = DATA_BITS_8;
    param.ucStopBits = STOP_BITS_1;
    param.ucParity = PARITY_NONE;
    param.ucRxTriggerLevel = UART_FCR_RFITL_1BYTE;

    retval = uartOpen(&param);	 


	    /* set RX interrupt mode */
	 retval = uartIoctl(param.ucUartNo, UART_IOC_SETRXMODE, UARTINTMODE, 0);

    /* set interrupt */
   // retval = uartIoctl(param.ucUartNo, UART_IOC_SETINTERRUPT, UARTINTMODE, (UART_IER_RLS_IEN_Msk|UART_IER_RTO_IEN_Msk));
	 
 }
 
 
 
 void Uart9_Init(void)
 {
	 int retval;

	    // outpw(REG_SYS_GPE_MFPL, (inpw(REG_SYS_GPE_MFPL) & 0xff0000ff) | (0x9999 << 8));// GPE2, 3, 4, 5 //TX, RX, RTS, CTS
    outpw(REG_CLK_PCLKEN0, inpw(REG_CLK_PCLKEN0) |(1<<25));
	outpw(REG_SYS_GPD_MFPH, (inpw(REG_SYS_GPD_MFPH) & 0x00ffffff) |(0x99<<24));// GPD.14\15


      UART_DEV[9].bIsUseUARTRxInt = TRUE;
	 
    /* configure UART */
    param.uFreq = 12000000;
    param.uBaudRate = 57600;
    param.ucUartNo = UART9;
    param.ucDataBits = DATA_BITS_8;
    param.ucStopBits = STOP_BITS_1;
    param.ucParity = PARITY_NONE;
    param.ucRxTriggerLevel = UART_FCR_RFITL_1BYTE;

    retval = uartOpen(&param);	 


	    /* set RX interrupt mode */
	 retval = uartIoctl(param.ucUartNo, UART_IOC_SETRXMODE, UARTINTMODE, 0);

    /* set interrupt */
   // retval = uartIoctl(param.ucUartNo, UART_IOC_SETINTERRUPT, UARTINTMODE, (UART_IER_RLS_IEN_Msk|UART_IER_RTO_IEN_Msk));
	 
 }
 
 
 void Uart3_Test(void)
 {
	 Uart3_Init();
	uartWrite(param.ucUartNo, "abcdef\r\n", 8);
 }








/*********************************************************************************************************
** �������� ��UART0_SendByte
** �������� ���Բ�ѯ��ʽ����һ�ֽ�����
** ��ڲ��� ��dat	Ҫ���͵�����
** ���ڲ��� ����
*********************************************************************************************************/
void UART0_SendByte(char dat)
{  
  UINT32 uOffset;
	uOffset = 3 * UARTOFFSET;
	Int32U Uart_Fsr;
	Int32U u32Reg;
    //u32Reg = inpw(REG_UART0_FCR+uOffset);
   // outpw(REG_UART0_FCR+uOffset, (u32Reg | (0x02 << 1)) );
	/*
	while(1)
	{
		Uart_Fsr=inpw(REG_UART0_FSR+uOffset) & UART_FSR_TE_FLAG_Msk;
		if(Uart_Fsr!=0)
			break;
		
	}*/
	          while(!(inpw(REG_UART0_FSR+uOffset) & UART_FSR_TE_FLAG_Msk));
            outpw(REG_UART0_THR+uOffset, dat);
	
//uartWrite(3, &dat, 1);
}

/**********************************************************************************************************
** �������� ��UART0_SendStr
** �������� ���򴮿ڷ���һ�ַ���
** ��ڲ��� ��str	Ҫ���͵��ַ�����ָ��
** ���ڲ��� ����
**********************************************************************************************************/
void UART0_SendStr(char *str)
{
volatile Int16U  tt=10;
while (*str != '\0')// �������������˳�
	{
	UART0_SendByte(*str++);			
	}
while(tt--);
}

/*********************************************************************************************************
** �������� ��UART0_SendBuf
** �������� ���򴮿ڷ�������
** ��ڲ��� ��uint32  snd_n��  �������ݵĸ�����snd_n С��8
**			  uint8* RcvBufPt�������ַ  
** ���ڲ��� ����
**********************************************************************************************************/
void UART0_SendBuf(pInt8U RcvBufPt, Int32U snd_n)
{
	Int32U i;

    
	for (i = 0; i < snd_n; i++)				// ʹ�÷���FIFO��������
	{
		uartWrite(param.ucUartNo, &RcvBufPt[i], 1);
		//U0THR     = RcvBufPt[i];
	}
	//while ((U0LSR & 0x40) == 0);			// �ȴ����ݷ������
	// VICINTENABLE |= 1 << UART0_INT;		

}

/*********************************************************************************************************
** �������� ��IRQ_UART0
** �������� ������0�����жϷ������
** ��ڲ��� ����
** ���ڲ��� ����
*******************************************************************************************************/
void UART0IntrHandler(void)
{
	Int32U i   = 0;
	Int32U IIR = 0;
   //GLCD_ClearBuffer(0xa0000000);

			switch(Uart_mod)
				{
				case 0: //download mode
					CommExec(Uart3_Data);
					break;
				case 1://���ŷ� ͨѶ
					ServoComm_exec(Uart3_Data);
					break;
				}						
}
/*********************************************************************************************************
** �������� ��UART0_Init
** �������� �����0���ȫ����ʼ������
** ��ڲ��� ����
** ���ڲ��� ����
*********************************************************************************************************/
void UART0_Init(void)
{
Uart3_Init();
}



/*********************************************************************************************************
** �������� ��UART9_Init
** �������� �����0���ȫ����ʼ������
** ��ڲ��� ����
** ���ڲ��� ����
*********************************************************************************************************/
void UART3_Init(void)
{
Uart9_Init();
}


//--------------------------------------------UART2---------------------------------------------------------------------//

/*********************************************************************************************************
** �������� ��UART2_SendByte
** �������� ���Բ�ѯ��ʽ����һ�ֽ�����
** ��ڲ��� ��dat	Ҫ���͵�����
** ���ڲ��� ����
*********************************************************************************************************/
void UART2_SendByte(char dat)
{
uartWrite(param.ucUartNo, &dat, 1);
}

/**********************************************************************************************************
** �������� ��UART2_SendStr
** �������� ���򴮿ڷ���һ�ַ���
** ��ڲ��� ��str	Ҫ���͵��ַ�����ָ��
** ���ڲ��� ����
**********************************************************************************************************/
void UART2_SendStr(char *str)
{
volatile Int16U  tt=10;
while (*str != '\0')// �������������˳�
	{
	UART0_SendByte(*str++);			
	}
while(tt--);
}

/*********************************************************************************************************
** �������� ��IRQ_UART2
** �������� ������2�����жϷ������
** ��ڲ��� ����
** ���ڲ��� ����
*******************************************************************************************************/
void UART2IntrHandler(void)
{
//tempR=U2RBR;
//Comm_TouchScr(tempR);

					
}
/*********************************************************************************************************
** �������� ��UART2_Init
** �������� �����0���ȫ����ʼ������
** ��ڲ��� ����
** ���ڲ��� ����
*********************************************************************************************************/
void UART2_Init(void)
{

Uart3_Init();
}



















/*********************************************************************************************************
** �������� ��UART0_SendByte
** �������� ���Բ�ѯ��ʽ����һ�ֽ�����
** ��ڲ��� ��dat	Ҫ���͵�����
** ���ڲ��� ����
*********************************************************************************************************/
void UART8_SendByte(char dat)
{  
  UINT32 uOffset;
	uOffset = 8 * UARTOFFSET;
	Int32U Uart_Fsr;
	Int32U u32Reg;
    //u32Reg = inpw(REG_UART0_FCR+uOffset);
   // outpw(REG_UART0_FCR+uOffset, (u32Reg | (0x02 << 1)) );
	/*
	while(1)
	{
		Uart_Fsr=inpw(REG_UART0_FSR+uOffset) & UART_FSR_TE_FLAG_Msk;
		if(Uart_Fsr!=0)
			break;
		
	}*/
	          while(!(inpw(REG_UART0_FSR+uOffset) & UART_FSR_TE_FLAG_Msk));
            outpw(REG_UART0_THR+uOffset, dat);
	
//uartWrite(3, &dat, 1);
}




/**********************************************************************************************************
** �������� ��UART0_SendStr
** �������� ���򴮿ڷ���һ�ַ���
** ��ڲ��� ��str	Ҫ���͵��ַ�����ָ��
** ���ڲ��� ����
**********************************************************************************************************/
void UART8_SendStr(char *str)
{
volatile Int16U  tt=10;
while (*str != '\0')// �������������˳�
	{
	UART8_SendByte(*str++);			
	}
while(tt--);
}

/*********************************************************************************************************
** �������� ��UART0_SendBuf
** �������� ���򴮿ڷ�������
** ��ڲ��� ��uint32  snd_n��  �������ݵĸ�����snd_n С��8
**			  uint8* RcvBufPt�������ַ  
** ���ڲ��� ����
**********************************************************************************************************/
void UART8_SendBuf(pInt8U RcvBufPt, Int32U snd_n)
{
	Int32U i;

    
	for (i = 0; i < snd_n; i++)				// ʹ�÷���FIFO��������
	{
	UART8_SendByte(*RcvBufPt++);	//uartWrite(param.ucUartNo, &RcvBufPt[i], 1);
		//U0THR     = RcvBufPt[i];
	}
	//while ((U0LSR & 0x40) == 0);			// �ȴ����ݷ������
	// VICINTENABLE |= 1 << UART0_INT;		

}

/*********************************************************************************************************
** �������� ��IRQ_UART0
** �������� ������0�����жϷ������
** ��ڲ��� ����
** ���ڲ��� ����
*******************************************************************************************************/
void UART8IntrHandler(void)
{
	Int32U i   = 0;
	Int32U IIR = 0;
	
	#ifdef CAP_TOUCH
	
	#else	
	Comm_TouchScr(Uart8Data);
	#endif
	
   //GLCD_ClearBuffer(0xa0000000);

//////			switch(Uart_mod)
//////				{
//////				case 0: //download mode
//////					CommExec();
//////					break;
//////				case 1://���ŷ� ͨѶ
//////					ServoComm_exec(Uart3_Data);
//////					break;
//////				}						
}






/*********************************************************************************************************
** �������� ��UART0_SendByte
** �������� ���Բ�ѯ��ʽ����һ�ֽ�����
** ��ڲ��� ��dat	Ҫ���͵�����
** ���ڲ��� ����
*********************************************************************************************************/
void UART9_SendByte(char dat)
{  
  UINT32 uOffset;
	uOffset = 9 * UARTOFFSET;
	Int32U Uart_Fsr;
	Int32U u32Reg;
    //u32Reg = inpw(REG_UART0_FCR+uOffset);
   // outpw(REG_UART0_FCR+uOffset, (u32Reg | (0x02 << 1)) );
	/*
	while(1)
	{
		Uart_Fsr=inpw(REG_UART0_FSR+uOffset) & UART_FSR_TE_FLAG_Msk;
		if(Uart_Fsr!=0)
			break;
		
	}*/
	          while(!(inpw(REG_UART0_FSR+uOffset) & UART_FSR_TE_FLAG_Msk));
            outpw(REG_UART0_THR+uOffset, dat);
	
//uartWrite(3, &dat, 1);
}

/**********************************************************************************************************
** �������� ��UART0_SendStr
** �������� ���򴮿ڷ���һ�ַ���
** ��ڲ��� ��str	Ҫ���͵��ַ�����ָ��
** ���ڲ��� ����
**********************************************************************************************************/
void UART9_SendStr(char *str)
{
volatile Int16U  tt=10;
while (*str != '\0')// �������������˳�
	{
	UART9_SendByte(*str++);			
	}
while(tt--);
}

/*********************************************************************************************************
** �������� ��UART0_SendBuf
** �������� ���򴮿ڷ�������
** ��ڲ��� ��uint32  snd_n��  �������ݵĸ�����snd_n С��8
**			  uint8* RcvBufPt�������ַ  
** ���ڲ��� ����
**********************************************************************************************************/
void UART9_SendBuf(pInt8U RcvBufPt, Int32U snd_n)
{
	Int32U i;

    
	for (i = 0; i < snd_n; i++)				// ʹ�÷���FIFO��������
	{
		uartWrite(UART9, &RcvBufPt[i], 1);
		//U0THR     = RcvBufPt[i];
	}
	//while ((U0LSR & 0x40) == 0);			// �ȴ����ݷ������
	// VICINTENABLE |= 1 << UART0_INT;		

}

/*********************************************************************************************************
** �������� ��IRQ_UART0
** �������� ������0�����жϷ������
** ��ڲ��� ����
** ���ڲ��� ����
*******************************************************************************************************/
void UART9IntrHandler(void)
{
	Int32U i   = 0;
	Int32U IIR = 0;
   //GLCD_ClearBuffer(0xa0000000);

	
////////		                  tempR=(UNS_8)UART1->txrx_fifo;
				Comm_Keyboard(Uart9Data);
	
//////			switch(Uart_mod)
//////				{
//////				case 0: //download mode
//////					CommExec();
//////					break;
//////				case 1://���ŷ� ͨѶ
//////					ServoComm_exec(Uart3_Data);
//////					break;
//////				}						
}




