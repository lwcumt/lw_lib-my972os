//unsigned char AsciiChar[16];
#define ASCIIADD 0x40000
#define AT45db041_ContArray_Read_Commd 0xE8 //���������� SPIģʽ3
#define AT45db041_MMPage_Read_Commd 0xD2  //���洢ҳ������ SPIģʽ3
#define AT45db041_Buf1_Read_Commd 0xD4  //��������1��������  SPIģʽ3
#define AT45db041_Buf2_Read_Commd 0xD6  //��������2��������  SPIģʽ3
#define AT45db041_Status_Read_Commd 0xD7   //��״̬�Ĵ�������   SPIģʽ3

#define AT45db041_Buf1_Write_Commd 0x84  //�򻺳���1д��������
#define AT45db041_Buf2_Write_Commd 0x87  //�򻺳���2д��������

#define AT45db041_Buf1MM_ProErase_Commd 0x83  //������1д���ݵ����洢ҳ�����������洢ҳ����
#define AT45db041_Buf2MM_ProErase_Commd 0x86  //������2д���ݵ����洢ҳ�����������洢ҳ����
#define AT45db041_Buf1ToMM_Pro_Commd 0x88  //������1д���ݵ����洢ҳ����
#define AT45db041_Buf2ToMM_Pro_Commd 0x89  //������2д���ݵ����洢ҳ����
#define AT45db041_Page_Erase_Commd 0x81  //ҳ��������
#define AT45db041_Block_Erase_commd 0x50  //���������

#define AT45db041_Buf1WriteAndMM_Commd 0x82  //�򻺳���1�����洢ҳд���ݲ����������洢ҳ����
#define AT45db041_Buf2WriteAndMM_Commd 0x85  //�򻺳���2�����洢ҳд���ݲ����������洢ҳ����


#define AT45db041_MMToBuf1_Tran_Commd 0x53  //ָ��ҳ��BUFFER1����ת������
#define AT45db041_MMToBuf2_Tran_Commd 0x55  //ָ��ҳ��BUFFER2����ת������

#define AT45db041_MMToBuf1_Comp_Commd 0x60  //ָ��ҳ��BUFFER1���ݱȽ�����
#define AT45db041_MMToBuf2_Comp_Commd 0x61  //ָ��ҳ��BUFFER2���ݱȽ�����

#define AT45db041_APageBuff1_Rewr_Commd 0x58  //��ָ��ҳ��BUFFER1����д����
#define AT45db041_APageBuff2_Rewr_Commd 0x59  //��ָ��ҳ��BUFFER2����д����

void HZK_Read( char *hzp,unsigned char distype);  //��ȡ���ֿ��к��ֵ��� distype 0:���� 1:����