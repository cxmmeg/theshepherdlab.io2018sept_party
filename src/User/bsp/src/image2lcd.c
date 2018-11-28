#include "bsp.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//FLASHͼƬ��ʾ		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/3/26
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//��8λ���ݻ��16λ��ɫ
//mode:0,��λ��ǰ,��λ�ں�.
//     1,��λ��ǰ,��λ�ں�.
//str:����
u16 image_getcolor(u8 mode, u8 *str)
{
	u16 color;
	if (mode)
	{
		color = ((u16)*str++) << 8;
		color |= *str;
	}
	else
	{
		color = *str++;
		color |= ((u16)*str) << 8;
	}
	return color;
}
//��Һ���ϻ�ͼ����֧�֣������ң����ϵ��� or ���ϵ��£������� ��ɨ�跽ʽ����	   
//xsta,ysta,width,height:��ͼ����
//scan:��image2lcd V2.9��˵��.
//*p:ͼ������
void image_show(u16 xsta, u16 ysta, u16 xend, u16 yend, u8 scan, u8 *p)
{
	u32 i;
	u32 len = 0;
	lcd_set_window(xsta, ysta, xend, yend);
	lcd_cursor(xsta, ysta); 
	len = (xend - xsta + 1)*(yend - ysta + 1);			//д������ݳ���
	for (i = 0; i < len; i++)
	{
		LCD_WR_16Bit(image_getcolor(scan&(1 << 4), p));
		p += 2;
	}
}

//��ָ����λ����ʾһ��ͼƬ
//�˺���������ʾimage2lcd������ɵ�����16λ���ɫͼƬ.
//����:1,�ߴ粻�ܳ�����Ļ������.
//     2,��������ʱ���ܹ�ѡ:��λ��ǰ(MSB First)
//     3,�������ͼƬ��Ϣͷ����
//x,y:ָ��λ��
//imgx:ͼƬ����(�������ͼƬ��Ϣͷ,"4096ɫ/16λ���ɫ/18λ���ɫ/24λ���ɫ/32λ���ɫ����ͼ������ͷ)
//ע��:���STM32,����ѡ��image2lcd��"��λ��ǰ(MSB First)"ѡ��,����imginfo�����ݽ�����ȷ!!
void image_display(u16 x, u16 y, u8 * imgx)
{
	HEADCOLOR *imginfo;
	u8 ifosize = sizeof(HEADCOLOR);//�õ�HEADCOLOR�ṹ��Ĵ�С
	imginfo = (HEADCOLOR*)imgx;
	image_show(x, y, imginfo->w-1, imginfo->h-1, imginfo->scan, imgx + ifosize);
}















