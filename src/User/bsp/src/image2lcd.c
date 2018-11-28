#include "bsp.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK Mini STM32开发板
//FLASH图片显示		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2014/3/26
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//从8位数据获得16位颜色
//mode:0,低位在前,高位在后.
//     1,高位在前,低位在后.
//str:数据
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
//在液晶上画图（仅支持：从左到右，从上到下 or 从上到下，从左到右 的扫描方式！）	   
//xsta,ysta,width,height:画图区域
//scan:见image2lcd V2.9的说明.
//*p:图像数据
void image_show(u16 xsta, u16 ysta, u16 xend, u16 yend, u8 scan, u8 *p)
{
	u32 i;
	u32 len = 0;
	lcd_set_window(xsta, ysta, xend, yend);
	lcd_cursor(xsta, ysta); 
	len = (xend - xsta + 1)*(yend - ysta + 1);			//写入的数据长度
	for (i = 0; i < len; i++)
	{
		LCD_WR_16Bit(image_getcolor(scan&(1 << 4), p));
		p += 2;
	}
}

//在指定的位置显示一个图片
//此函数可以显示image2lcd软件生成的任意16位真彩色图片.
//限制:1,尺寸不能超过屏幕的区域.
//     2,生成数据时不能勾选:高位在前(MSB First)
//     3,必须包含图片信息头数据
//x,y:指定位置
//imgx:图片数据(必须包含图片信息头,"4096色/16位真彩色/18位真彩色/24位真彩色/32位真彩色”的图像数据头)
//注意:针对STM32,不能选择image2lcd的"高位在前(MSB First)"选项,否则imginfo的数据将不正确!!
void image_display(u16 x, u16 y, u8 * imgx)
{
	HEADCOLOR *imginfo;
	u8 ifosize = sizeof(HEADCOLOR);//得到HEADCOLOR结构体的大小
	imginfo = (HEADCOLOR*)imgx;
	image_show(x, y, imginfo->w-1, imginfo->h-1, imginfo->scan, imgx + ifosize);
}















