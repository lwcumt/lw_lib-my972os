







#ifndef __CHNDOT_H
#define __CHNDOT_H


#include"main.h"
/*
#include "board.h"
#include "sys.h"
#include "string.h"
#include "drv_glcd.h"

*/

//���󳤶�   ����Ϣͷ
#define DOT16  16   //����16*16����
#define DOT16MODE 32+2

#define DOT24  24  //����24*24����
#define DOT24MODE 72+2

#define DOT32  32  //����32*32����  
#define DOT32MODE 128+2

#define DOT48  48   //����48*48����
#define DOT48MODE 288+2

#define DOT56  56   //����56*56����
#define DOT56MODE 392+2

#define DOT64  64   //����64*64����
#define DOT64MODE 512+2


#define ASCII1632_MODE 64+1
#define ASCII1632_WIDTH 16
#define ASCII1632_HIGH 32

#define ASCII16_MODE	16+1
#define ASCII24_MODE	48+1
#define ASCII32_MODE	64+1




extern unsigned char const HZDOT24[]; 
extern unsigned char const HZDOT32[];
extern unsigned char const HZDOT48[];
extern unsigned char const ASCII1632[];

extern unsigned char const ASCII_28x56[];
extern unsigned char const ASCII_32x48[];
extern unsigned char const ASCII_20x36[];
extern unsigned char const ASCII_bold24x40[];
extern unsigned char const ASCII_bold18x38[];
extern unsigned char const ASCII_bold16x32[];


extern unsigned char const PUTAO_ZK16[];
extern unsigned char const PUTAO_ZK24[];
extern unsigned char const PUTAO_ZK32[];





extern unsigned char const PUTAO_ZK16_XOR[];
extern unsigned char const PUTAO_ZK24_XOR[];
extern unsigned char const PUTAO_ZK32_XOR[];











/*
#ifndef __CHNDOT_H
#define __CHNDOT_H


#include "board.h"
#include "sys.h"
#include "string.h"
#include "drv_glcd.h"


//���󳤶�   ����Ϣͷ
#define DOT16  16   //����16*16����
#define DOT16MODE 32+2

#define DOT24  24  //����24*24����
#define DOT24MODE 72+2

#define DOT32  32  //����32*32����  
#define DOT32MODE 128+2

#define DOT48  48   //����48*48����
#define DOT48MODE 288+2

#define DOT56  56   //����56*56����
#define DOT56MODE 392+2

#define DOT64  64   //����64*64����
#define DOT64MODE 512+2








extern unsigned char const HZDOT48[];
extern unsigned char const HZDOT24[]; 
extern unsigned char const HZDOT32[];

*/
//��Ļ���ָ����С����ĺ��ִ�  
//extern void HZ_Printf(unsigned char *chn,int  dotmode,int  dotnum,unsigned char const *dot,int x,int y, int color);



//��Ļ���ָ����С����ĺ��ִ�  
extern void HZ_Printf(unsigned char *chn,int  dotmode,int  dotnum,unsigned char const *dot,int x,int y, int color);
//��Ļ���ָ����С�����ASCII�ַ���
extern void ASCII_Printf(unsigned char *asc,int dotmode,int dotwidth,int dothigh,unsigned char const *dot,int x,int y, int color,int FillColor);
extern void ASCII_Printf_OneChar(unsigned char *asc,int dotmode,int dotwidth,int dothigh,unsigned char const *dot,int x,int y, int color,int FillColor);
extern void ASCII_Printf_OneChar_NoFill(unsigned char *asc,int dotmode,int dotwidth,int dothigh,unsigned char const *dot,int x,int y, int color);




#endif
