/*
*********************************************************************************************************
*
*	ģ������ : ���������
*	�ļ����� : main.c
*	��    �� : V1.0
*	˵    �� : ����ͨ�����ӣ���PC�������ն�������н���
*	�޸ļ�¼ :
*		�汾��  ����       ����    ˵��
*		V1.0    2015-08-30 armfly  �׷�
*
*	Copyright (C), 2015-2016, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#include "bsp.h"				/* �ײ�Ӳ������ */
#include "bsp_menu.h"
/*
*********************************************************************************************************
*	�� �� ��: main
*	����˵��: c�������
*	��    �Σ���
*	�� �� ֵ: �������(���账��)
*********************************************************************************************************
*/

uint8_t game_sel = 0;

int main(void)
{
	//uint8_t ucKeyCode;	
	//uint16_t i,j;

	/*
		ST�̼����е������ļ��Ѿ�ִ���� SystemInit() �������ú����� system_stm32f4xx.c �ļ�����Ҫ������
	����CPUϵͳ��ʱ�ӣ��ڲ�Flash����ʱ������FSMC�����ⲿSRAM
	*/
	
	bsp_Init();		/* Ӳ����ʼ�� */
	shephardlabparty_start();
	
	LCD_Clear(BLACK);
	Init_SNAKE();
	Init_GUESSNUM();
	
	bsp_StartAutoTimer(0, 500);	/* ����1��1000ms���Զ���װ�Ķ�ʱ�� */

//******************************* Menu *********************************//

	/* �������ѭ�� */
	while (1)
	{
		bsp_Idle();		/* CPU����ʱִ�еĺ������� bsp.c */
		//Menu_Loop();
		
		//if (bsp_CheckTimer(0))	/* �ж϶�ʱ����ʱʱ�� */
		//{
		//	//printf("time ok\r\n");
		//	//Menu_UpdateFrame();

		//	//uint16_t adc;

		//	//adc = bsp_GetAdc_Average(1);

		//	///* ע�⣺ ĩβֻ�� \r�س�, û��\n���У�����ʹPC�����ն˽����ȶ���1����ʾ */
		//	//{
		//	//	/* �����ն˽����ϻ���ʾһ��������ת���ַ�
		//	//	����������ܣ���Ϊ�˱�����������ļ�����ΪADC����ֵ���ȶ�
		//	//	*/
		//	//	static uint8_t pos = 0;

		//	//	if (pos == 0)
		//	//		printf("|");
		//	//	else if (pos == 1)
		//	//		printf("/");
		//	//	else if (pos == 2)
		//	//		printf("-");
		//	//	else if (pos == 3)
		//	//		printf("\\");		/* ע�⣺��������ַ���Ҫת�� */

		//	//	if (++pos >= 4)
		//	//	{
		//	//		pos = 0;
		//	//	}

		//	//	printf(" PC4����ADC����ֵ = %5d , ��ѹ = %4dmV\r",
		//	//		adc, ((uint32_t)adc * 2500) / 4095);
		//	//}
		//}

		//Key_Value = bsp_GetKey();
		//if (Key_Value > 0)
		//{
		//	if (Key_Value == KEY_DOWN_U)
		//	{
		//		flag = 1;
		//		LCD_Clear(BLACK);
		//		Init_SNAKE();
		//		break;
		//	}
		//	else if (Key_Value == KEY_DOWN_D)
		//	{
		//		flag = 2;
		//		break;
		//	}
		//}
		//if (flag == 1)
		//{
		//	Run_SNAKE();
		//}

		//Run_SNAKE();
		//RUN_GUESS();
		if (game_sel == 0)
		{
			LCD_Clear(BLACK);
			LCD_setTextColor(WHITE, BLACK);
			LCD_text("Press Up, Play Snake!", 16, 32);
			LCD_text("Press Down, Play GuessNum!", 2, 72);
			game_sel = 1;
		}
		else if (game_sel == 1)
		{
			Key_Value = bsp_GetKey();
			if (Key_Value > 0)
			{
				if (Key_Value == KEY_DOWN_D)
				{
					LCD_Clear(BLACK);
					game_sel = 3;
					Key_Value = 0;
				}
				else if (Key_Value == KEY_DOWN_U)
				{
					LCD_Clear(BLACK);
					game_sel = 2;
					Key_Value = 0;
				}
			}
		}
		else if(game_sel == 2)
		{
			RUN_SNK();
		}
		else if (game_sel == 3)
		{
			RUN_GUESS();
		}
		

		//bsp_DelayMS(100);
		/* �������¼� */
		//ucKeyCode = bsp_GetKey();
		//if (ucKeyCode > 0)
		//{
		//	/* �м����� */
		//	switch (ucKeyCode)
		//	{
		//		case KEY_DOWN_L:		/* ҡ��LEFT������, ����LED��ʾ���� */
		//			printf("KEY_L\n");
		//			break;		
		//		
		//		case KEY_DOWN_R:		/* ҡ��RIGHT������ */
		//			printf("KEY_R\n");
		//			break;

		//		case KEY_DOWN_U:		/* ҡ��UP������ */
		//			printf("KEY_U\n");
		//			break;				
		//		
		//		case KEY_DOWN_D:		/* ҡ��DOWN������ */
		//			printf("KEY_D\n");
		//			break;	
		//		
		//		case KEY_DOWN_A:		/* ҡ��LEFT������, ����LED��ʾ���� */
		//			printf("KEY_A\n");
		//			break;		
		//		
		//		case KEY_DOWN_B:		/* ҡ��RIGHT������ */
		//			printf("KEY_B\n");
		//			break;

		//		case KEY_DOWN_X:		/* ҡ��UP������ */
		//			printf("KEY_X\n");
		//			break;				
		//		
		//		case KEY_DOWN_Y:		/* ҡ��DOWN������ */
		//			printf("KEY_Y\n");
		//			break;	
		//		
		//		default:
		//			break;
		//	}
		//}
	}
}

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
