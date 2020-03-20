#ifndef __M25PE16_H
#define __M25PE16_H

#include "main.h"
#include "spi_config.h"


//-----����
#define WRITE_EN_COMM          0x06  //дʹ��
#define WRITE_DIS_COMM         0x04   //д��ֹ

#define READ_CHIP_ID_COMM      0x9F//��id  24bytes
#define READ_STATUS_COMM       0x05//��״̬�Ĵ���
#define WRITE_STATUS_COMM      0x01//д״̬�Ĵ���
#define WRITE_LOCK_REG_COMM    0xE5//
#define READ_LOCK_REG_COMM     0xE8
#define READ_DATA_COMM         0x03//������
#define FAST_READ_DATA_COMM    0x0B//���ٶ�����

#define PAGE_WRITE_COMM        0x0A//ҳд
#define PAGE_PROGRAM_COMM      0x02//ҳ���
#define PAGE_ERASE_COMM        0xDB//ҳ����
#define BLOCK_ERASE_COMM       0xD8//�����
#define SECTOR_ERASE_COMM      0x20//��������
#define CHIP_ERASE_COMM        0xC7//��Ƭ����

#define DEEP_POWER_DOWN_COMM   0xB9
#define DEEP_POWER_UP_COMM    0xAB


#define FlashChip_En   SPI0_SEL_EN  //ѡͨоƬ
#define FlashChip_Dis  SPI0_SEL_DIS  //�ͷ�

//-------------flashоƬ����
#define PAGE_SIZE      256//ҳ��С
#define SECTOR_SIZE   (PAGE_SIZE*16)//������С=16ҳ    4k
#define BLOCK_SIZE     (SECTOR_SIZE*16)//���С=16����  64k

extern Int8U Chip_id[20];//��оƬid��       ��20 80 15 10 ������ͷ��


//��****************������**********************��
void Read_DevID(void);
Int8U Read_Status(void);//---��״̬
Int8U Wait_Busy(void);//æ�ж�  1:æ

void Read_Datas_Start(Int32U  add);//������   ��add:�ֽڵ�ַ��
void FastRead_Datas_Start(Int32U  add);//�������   ��add:�ֽڵ�ַ��
Int8U ReadFlash_Datas(void);//������

//��***************д����**********************��
void Write_En(void);//ʹ�� д
void Write_Dis(void);//��ֹ д


//*****ҳ��̣����һҳ��
void Page_Program(pInt8U   wbuf,   Int32U   page,   Int16U   length);//wbuf����д���ݻ�������page����ʼҳ��ַ��length�����ݳ���<=256
//*****ҳд��д��һҳ��
void Page_Write(pInt8U   wbuf,   Int32U   page,   Int16U   length);//wbuf����д���ݻ�������page����ʼҳ��ַ��length�����ݳ���<=256
//*****�ֽ�д���������ַд�������ֽڣ�����С��һҳ��
void Bytes_Write(pInt8U   wbuf,   Int32U  add,   Int16U   length);//wbuf����д���ݻ�������add����ʼ�ֽڵ�ַ��length�����ݳ���<=256


//��************��������***********************��
void Chip_Erase(void);//*****��Ƭ����
void Page_Erase(Int32U   page);//*****ҳ����       page��ҳ��ַ
void Sector_Erase(Int32U   sector);//*****��������
void Block_Erase(Int32U   block);//*****�����
#endif
