#ifndef __SNAKE_H__
#define __SNAKE_H__

#ifdef __cplusplus
extern "C" {
#endif 

#define SNAKE_Max_Long 10   //�ߵ���󳤶�

	//=================================================================
	//    ʹ�ýṹ�嶨�����   ʹ��������Ƹ��ӵ����
	//=================================================================
	struct Fd
	{
		u8 X;
		u8 Y;
		u8 Yes;
	};	//ʳ��ṹ��

	struct Se
	{
		u8 X[SNAKE_Max_Long];
		u8 Y[SNAKE_Max_Long];
		u8 Long;          //�ߵĳ���
		u8 Life;
		u8 Score;					//�ߵķ���
		u8 Level;					//�ߵĵȼ�              
	};	//�߽ṹ��

	extern u8 Key_V_temp;     			//ȡ���ϴΰ���ֵ
	extern u8 Key_Value;     				//ȡ���ϴΰ���ֵ

	void Init_SNAKE(void);
	void Run_Ahead(void);
	void Run_SNAKE(void);
	void Display_Pass(void);
	void Display_dead(void);
	void Trun_On_Point(u8 x, u8 y);
	void Trun_Off_Point(u8 x, u8 y);
	void RUN_SNK(void);

	//extern void Trun_On_Point (uchar x,uchar y,uchar color);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

