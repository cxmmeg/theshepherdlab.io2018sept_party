#include "bsp.h"


static uint8_t n_pos = 0;
static uint16_t highsc_temp = 0;
static uint8_t guess[4] = { 0x5f, 0x5f, 0x5f, 0x5f };
static uint8_t rand_num[4] = { 0 };
static uint8_t guess_time = 0;
static uint8_t guess_flag = 0;

extern uint8_t game_sel;

void Init_GUESSNUM(void)
{
	u16 iSeed = 0;
	u8 i, j;
	LCD_Fill(1, 1, 158, 126, BLACK);
	LCD_DrawRect(0, 0, 159, 127, GREEN);

	bsp_ReadCpuFlash(GUESSNUM_ADDR, (uint8_t *)&highsc_temp, 2);


	LCD_DrawLine(0, 32, 159, 32, GREEN);
	LCD_DrawLine(79, 32, 79, 127, GREEN);
	LCD_setTextColor(WHITE, BLACK);
	LCD_text("       Guess Number       ", 1, 12);

	bsp_ReadCpuFlash(GUESSNUM_ADDR, (uint8_t *)&highsc_temp, 2);

	if (highsc_temp == 0xffff)
	{
		highsc_temp = 0;
		bsp_WriteCpuFlash(GUESSNUM_ADDR, (uint8_t *)&highsc_temp, 2);
	}
	LCD_text("Tiptop: ", 83, 48);
	display_num_format(131, 48, highsc_temp, 1, "%04d", RED, BLACK);
	LCD_text("_ _ _ _", 99, 80);

	iSeed = bsp_GetAdc_Average(1);//通过模拟输入获取悬空引脚的电平产生随机种子
	srand(iSeed);
	rand_num[0] = (u8)(rand() % 10);//产生随机数0~3
	for (i = 1; i < 4; i++)
	{
		do
		{
			rand_num[i] = (u8)(rand() % 10);//产生随机数0~3
			for (j = 0; j < i; j++)
			{
				if (rand_num[i] == rand_num[j])
				{
					break;
				}
			}
			if (j == i) break;
		} while (1);
	}
	n_pos = 0;
	guess_time = 0;
	guess[0] = 0x5f;
	guess[1] = 0x5f;
	guess[2] = 0x5f;
	guess[3] = 0x5f;
	guess_flag = 1;
}

void guessnum(void)
{
	uint8_t countA = 0;
	uint8_t countB = 0;
	uint8_t i, j;

	if (guess_flag == 1)
	{
		Key_Value = bsp_GetKey();
		if (Key_Value > 0) // check if any button is pressed (enter, up, down, left, right)
		{
			if (Key_Value == KEY_DOWN_L) // check if button left is pressed
			{
				if (n_pos > 0)
				{
					guess[n_pos] = 0x5f;
					LCD_DrawChar(99 + n_pos * 12, 80, guess[n_pos], WHITE, BLACK, 1);
					n_pos--;
					LCD_DrawChar(99 + n_pos * 12, 80, guess[n_pos], RED, BLACK, 1);
					//if (n_pos == 0)
					//{
					//	LCD_DrawChar(14 + n_pos * 6, 80, pwd[n_pos], RED, BLACK, 1);
					//}
				}
				Key_V_temp = KEY_DOWN_L;

				Key_Value = 0;
			}
			else if (Key_Value == KEY_DOWN_R) // check if button left is pressed
			{
				if (n_pos < 4)
				{
					//if (n_pos == 0)
					//{
					//	LCD_DrawChar(14 + n_pos * 6, 80, pwd[n_pos], RED, BLACK, 1);
					//}
					LCD_DrawChar(99 + n_pos * 12, 80, guess[n_pos], WHITE, BLACK, 1);
					n_pos++;
					LCD_DrawChar(99 + n_pos * 12, 80, guess[n_pos], RED, BLACK, 1);
				}
				Key_V_temp = KEY_DOWN_R;

				Key_Value = 0;
			}
			else if (Key_Value == KEY_DOWN_U)
			{
				if ((guess[n_pos] > 0x39) || (guess[n_pos] < 0x30))
				{
					guess[n_pos] = 0x3A;
				}
				else if (guess[n_pos] == 0x30)
				{
					guess[n_pos] = 0x3A;
				}
				guess[n_pos]--;

				LCD_DrawChar(99 + n_pos * 12, 80, guess[n_pos], RED, BLACK, 1);
				Key_V_temp = KEY_DOWN_U;

				Key_Value = 0;
			}
			else if (Key_Value == KEY_DOWN_D)
			{
				if ((guess[n_pos] > 0x39) || (guess[n_pos] < 0x30))
				{
					guess[n_pos] = 0x2F;
				}
				else if (guess[n_pos] == 0x39)
				{
					guess[n_pos] = 0x2F;
				}
				guess[n_pos]++;

				LCD_DrawChar(99 + n_pos * 12, 80, guess[n_pos], RED, BLACK, 1);
				Key_V_temp = KEY_DOWN_D;

				Key_Value = 0;
			}
			else if (Key_Value == KEY_DOWN_A)
			{
				u8 t_flag = 0;

				for (i = 0; i < 4; i++)
				{
					for (j = i + 1; j < 4; j++)
					{
						if (guess[i] == guess[j])
						{
							t_flag = 1;
							break;
						}
					}
				}
				if (t_flag == 0)
				{

					for (i = 0; i < 4; i++)
					{
						for (j = 0; j < 4; j++)
						{
							if (guess[j] == rand_num[i] + 0x30)
							{
								if (j == i)
								{
									countA++;
								}
								else
								{
									countB++;
								}
							}
						}
					}

					if (guess_time < 8)
					{
						if (countA == 4)
						{
							LCD_Fill(1, 33, 158, 126, BLACK);
							LCD_setTextColor(WHITE, BLACK);
							LCD_text("     Congratulation!      ", 1, 48);
							highsc_temp++;
							bsp_WriteCpuFlash(GUESSNUM_ADDR, (uint8_t *)&highsc_temp, 2);
							LCD_text("     Tiptop: ", 11, 80);
							display_num_format(89, 80, highsc_temp, 1, "%04d", RED, BLACK);
							bsp_DelayMS(3000);
							guess_flag = 0;
							//LCDML.OTHER_jumpToFunc(mFunc_guess_num);
						}
						else
						{
							LCD_text("  A   B", 16, 40 + 10 * guess_time);
							LCD_DrawChar(16, 40 + 10 * guess_time, countA + 0x30, RED, BLACK, 1);
							LCD_DrawChar(16 + 24, 40 + 10 * guess_time, countB + 0x30, RED, BLACK, 1);
							guess_time++;
						}

					}
					else
					{
						LCD_Fill(1, 33, 158, 126, BLACK);
						LCD_setTextColor(WHITE, BLACK);
						LCD_text("       Game Over !        ", 1, 48);
						LCD_text("     Tiptop: ", 11, 80);
						display_num_format(89, 80, highsc_temp, 1, "%04d", RED, BLACK);
						bsp_DelayMS(3000);
						guess_flag = 0;
						//LCDML.FUNC_goBackToMenu();
					}
				}
				Key_V_temp = KEY_DOWN_A;

				Key_Value = 0;
			}
			else if (Key_Value == KEY_DOWN_B) // check if button left is pressed
			{
				LCD_Clear(BLACK);
				game_sel = 0;
				guess_flag = 0;
				Key_V_temp = KEY_DOWN_B;
				Key_Value = 0;
			}
		}
	}
}

void RUN_GUESS(void)
{
	if (guess_flag == 0)
	{
		Init_GUESSNUM();
	}
	else
	{
		guessnum();
	}
}

