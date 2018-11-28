#include "bsp.h"

u8 Key_V_temp = 0;     				//取出上次按键值
u8 Key_Value = 0;     				//取出上次按键值
static uint8_t snake_flag = 0;

extern uint8_t game_sel;

struct Fd Food;//果子
struct Se Snake;//蛇

//=================================================================
//函数名称：Trun_On_Point(u8 x,u8 y)
//函数功能：点亮一个点 用于显示蛇的身体
//入口参数：蛇的起点坐标
//出口参数：无
//特别说明：此函数换成其他的就可以兼容其他的液晶
//          比如 8*8 点阵   12864 等
//=================================================================
void Trun_On_Point(u8 x, u8 y)
{
	LCD_Fill((u16)(x * 4), (u16)(y * 4), (u16)(x * 4 + 4), (u16)(y * 4 + 4), RED);
}

//=================================================================
//函数名称：Trun_Off_Point(u8 x,u8 y)
//函数功能：熄灭一个点 用于隐藏蛇的身体
//入口参数：
//出口参数：无
//特别说明：此 Trun_On，函数换成其他的就可以兼容其他的液晶
//          比如 8*8 点阵   12864 等
//=================================================================
void Trun_Off_Point(u8 x, u8 y)
{
	LCD_Fill((u16)(x * 4), (u16)(y * 4), (u16)(x * 4 + 4), (u16)(y * 4 + 4), BLACK);
}

//=================================================================
//函数名称：void Init_SNAKE(void)  
//函数功能：绘制游戏界面，初始化游戏等级等参数
//入口参数：无
//出口参数：无
//=================================================================
void Init_SNAKE(void)
{
	u8 i;
	POINT_COLOR = WHITE;	//画笔颜色
	BACK_COLOR = BLACK;  //背景色 

	//***********绘制游戏界面********************//

	LCD_DrawRect(0, 0, 159, 127, DARKBLUE);
	LCD_DrawLine(0, 11, 159, 11, DARKBLUE);

	LCD_setTextColor(WHITE, BLACK);
	LCD_text("LEVEL:", 4, 3);
	LCD_text("Score:", 80, 3);
	LCD_setTextColor(RED, BLACK);
	display_num_format(40, 3, (u32)Snake.Level, 1, "%d", RED, BLACK);
	display_num_format(116, 3, (u32)Snake.Score, 1, "%d", RED, BLACK);

	//LCD_Fill(0, 0, 8, 280, DARKBLUE);//Rectangle(8,8-1,85,120,0xaa);//绘制一个矩形框, 0-127
	//LCD_Fill(232, 0, 240, 280, DARKBLUE);//
	//LCD_Fill(0, 0, 240, 8, DARKBLUE);//
	//LCD_Fill(0, 272, 240, 280, DARKBLUE);//

	//LCD_ShowString(0, 280, 200, 16, 16, "Score");//Show Score
	//LCD_ShowString(0, 300, 200, 16, 16, "LEVEL");//Show Level
	//LCD_ShowNum(50, 280, (u32)Snake.Score, 4, 16);
	//LCD_ShowNum(50, 300, (u32)Snake.Level, 4, 16);	//LCDShow_u8Number(96,97,Snake.Level,0x00ff,0xBE5F);

	//***********初始化参数********************//
	Snake.Long = 2;	    			//定义初始化蛇的长度
	Snake.Life = 0;	    			//初始化蛇还活着
	Snake.Score = 0;          //分数为0
	Food.Yes = 1;					    //
	Key_Value = 0;
	Key_V_temp = KEY_DOWN_R;//开始往右跑

	for (i = 0; i < Snake.Long; i++)		//将蛇给赋值
	{
		Snake.X[i] = i + 10;//组成蛇的4*4方块的起点坐标 根据长度循环每次增加一个方块的
		Snake.Y[i] = 12;//这里的(12,12)即为蛇的起点坐标
	}
	for (i = 0; i < Snake.Long; i++)		//根据坐标将蛇给画出来
	{
		Trun_On_Point(Snake.X[i], Snake.Y[i]);
	}
	snake_flag = 1;
}

//=================================================================
//函数名称：void Display_dead(u8 i) 
//函数功能：显示死亡界面
//入口参数：无
//出口参数：无
//=================================================================
void Display_dead(void)
{
	LCD_Clear(BLACK);

	LCD_DrawRect(0, 0, 159, 127, DARKBLUE);
	LCD_DrawLine(0, 11, 159, 11, DARKBLUE);

	LCD_setTextColor(WHITE, BLACK);
	LCD_text("LEVEL:", 4, 3);
	LCD_text("Score:", 80, 3);
	LCD_setTextColor(RED, BLACK);
	display_num_format(40, 3, (u32)Snake.Level, 1, "%d", RED, BLACK);
	display_num_format(116, 3, (u32)Snake.Score, 1, "%d", RED, BLACK);

	LCD_setTextColor(WHITE, BLACK);
	LCD_text("GAME OVER!", 50, 48);
	LCD_text("PRESS ENTER TO RESTART", 14, 72);

	while (Key_Value != KEY_DOWN_A)
	{
		Key_Value = bsp_GetKey();
	}
	LCD_Clear(BLACK);
	Init_SNAKE();//重新初始化设置 等待进入下次游戏
}

//=================================================================
//函数名称：void Display_Pass(void)
//函数功能：显示过关界面
//入口参数：无
//出口参数：无
//=================================================================
void Display_Pass(void)
{
	Snake.Level++;
	if (Snake.Level >= 21)
	{
		while (1)
		{
			LCD_Clear(WHITE);
			LCD_setTextColor(RED, BLACK);
			LCD_text("YOU ARE WIN!", 44, 48);
			//LCD_ShowString(30, 90, 200, 16, 16, "YOU ARE WIN!!!");
		}
	}
	LCD_Clear(BLACK);

	LCD_DrawRect(0, 0, 159, 127, DARKBLUE);
	LCD_DrawLine(0, 11, 159, 11, DARKBLUE);

	LCD_setTextColor(WHITE, BLACK);
	LCD_text("LEVEL:", 4, 3);
	LCD_text("Score:", 80, 3);
	LCD_setTextColor(RED, BLACK);
	display_num_format(40, 3, (u32)Snake.Level, 1, "%d", RED, BLACK);
	display_num_format(116, 3, (u32)Snake.Score, 1, "%d", RED, BLACK);

	LCD_setTextColor(RED, BLACK);
	LCD_text("YOU ARE WIN!", 44, 48);
	LCD_text("PRESS ENTER TO RESTART", 14, 72);

	while (Key_Value != KEY_DOWN_A)
	{
		Key_Value = bsp_GetKey();;
	}
	LCD_Clear(BLACK);
	Init_SNAKE();//重新初始化设置 等待进入下次游戏
}

//=================================================================
//函数名称：void Run_Ahead(void)
//函数功能：直行函数
//入口参数：无
//出口参数：无
//=================================================================
void Run_Ahead(void)
{
	u8 i;

	Trun_Off_Point(Snake.X[0], Snake.Y[0]); 	       //先把蛇尾给熄灭掉 

	if (Key_V_temp == KEY_DOWN_L)//左直行
	{
		for (i = 0; i < Snake.Long - 1; i++)                    //蛇身都是它前一段的蛇身的位置
		{
			Snake.X[i] = Snake.X[i + 1];
			Snake.Y[i] = Snake.Y[i + 1];
		}
		Snake.X[Snake.Long - 1] = Snake.X[Snake.Long - 2] - 1;//补上蛇头
		Snake.Y[Snake.Long - 1] = Snake.Y[Snake.Long - 2] + 0;
	}
	else if (Key_V_temp == KEY_DOWN_R)//右直行
	{
		for (i = 0; i < Snake.Long - 1; i++)                    //蛇身都是它前一段的蛇身的位置
		{
			Snake.X[i] = Snake.X[i + 1];
			Snake.Y[i] = Snake.Y[i + 1];
		}
		Snake.X[Snake.Long - 1] = Snake.X[Snake.Long - 2] + 1;//补上蛇头
		Snake.Y[Snake.Long - 1] = Snake.Y[Snake.Long - 2] + 0;
	}
	else if (Key_V_temp == KEY_DOWN_U)//上直行
	{
		for (i = 0; i < Snake.Long - 1; i++)                    //蛇身都是它前一段的蛇身的位置
		{
			Snake.X[i] = Snake.X[i + 1];
			Snake.Y[i] = Snake.Y[i + 1];
		}
		Snake.X[Snake.Long - 1] = Snake.X[Snake.Long - 2] + 0;//补上蛇头
		Snake.Y[Snake.Long - 1] = Snake.Y[Snake.Long - 2] - 1;
	}
	else if (Key_V_temp == KEY_DOWN_D)//下直行
	{
		for (i = 0; i < Snake.Long - 1; i++)                    //蛇身都是它前一段的蛇身的位置
		{
			Snake.X[i] = Snake.X[i + 1];
			Snake.Y[i] = Snake.Y[i + 1];
		}
		Snake.X[Snake.Long - 1] = Snake.X[Snake.Long - 2] + 0;//补上蛇头
		Snake.Y[Snake.Long - 1] = Snake.Y[Snake.Long - 2] + 1;
	}

	for (i = 0; i < Snake.Long; i++)			            //让蛇显示出来
	{
		Trun_On_Point(Snake.X[i], Snake.Y[i]);
	}
}

//=================================================================
//函数名称：void Run_SNAKE(void)
//函数功能：蛇运动函数 （游戏精华）
//入口参数：无
//出口参数：无
//=================================================================
void Run_SNAKE(void)
{
	u8 i = 0;
	u16 iSeed = 0;

	iSeed = bsp_GetAdc_Average(1);//通过模拟输入获取悬空引脚的电平产生随机种子
	srand(iSeed);

	/*********************根据按键选择蛇的运动方向*******************/
  //右转
	if (Key_Value == KEY_DOWN_R && Key_V_temp != KEY_DOWN_L)
	{
		Trun_Off_Point(Snake.X[0], Snake.Y[0]); 	       //先把蛇尾给熄灭掉 

		for (i = 0; i < Snake.Long - 1; i++)                    //蛇身都是它前一段的蛇身的位置
		{
			Snake.X[i] = Snake.X[i + 1];
			Snake.Y[i] = Snake.Y[i + 1];
		}

		Snake.X[Snake.Long - 1] = Snake.X[Snake.Long - 2] + 1;
		Snake.Y[Snake.Long - 1] = Snake.Y[Snake.Long - 2] + 0; //蛇头向你要求的方向移动

		for (i = 0; i < Snake.Long; i++)			            //这个让蛇显示出来的函数
		{
			Trun_On_Point(Snake.X[i], Snake.Y[i]);
		}
		Key_V_temp = KEY_DOWN_R;

		Key_Value = 0;
		//while(RmtCnt!=0);//松手检测
	}

	//左转
	if (Key_Value == KEY_DOWN_L && Key_V_temp != KEY_DOWN_R)
	{
		Trun_Off_Point(Snake.X[0], Snake.Y[0]); 		   //先把蛇尾给熄灭掉 

		for (i = 0; i < Snake.Long - 1; i++)                     //蛇身都是它前一段的蛇身的位置
		{
			Snake.X[i] = Snake.X[i + 1];
			Snake.Y[i] = Snake.Y[i + 1];
		}

		Snake.X[Snake.Long - 1] = Snake.X[Snake.Long - 2] - 1;
		Snake.Y[Snake.Long - 1] = Snake.Y[Snake.Long - 2] + 0; //蛇头向你要求的方向移动

		for (i = 0; i < Snake.Long; i++)			            //这个让蛇显示出来的函数
		{
			Trun_On_Point(Snake.X[i], Snake.Y[i]);
		}
		Key_V_temp = KEY_DOWN_L;

		Key_Value = 0;
		//while(RmtCnt!=0);//松手检测    
	}

	//向上
	if (Key_Value == KEY_DOWN_U && Key_V_temp != KEY_DOWN_D)
	{

		Trun_Off_Point(Snake.X[0], Snake.Y[0]); 		  //先把蛇尾给熄灭掉 

		for (i = 0; i < Snake.Long - 1; i++)                   //蛇身都是它前一段的蛇身的位置
		{
			Snake.X[i] = Snake.X[i + 1];
			Snake.Y[i] = Snake.Y[i + 1];
		}

		Snake.X[Snake.Long - 1] = Snake.X[Snake.Long - 2] + 0;
		Snake.Y[Snake.Long - 1] = Snake.Y[Snake.Long - 2] - 1; //蛇头向你要求的方向移动

		for (i = 0; i < Snake.Long; i++)			           //这个让蛇显示出来的函数
		{
			Trun_On_Point(Snake.X[i], Snake.Y[i]);
		}
		Key_V_temp = KEY_DOWN_U;

		Key_Value = 0;
		//while(RmtCnt!=0);//松手检测    
	}

	//向下
	if (Key_Value == KEY_DOWN_D && Key_V_temp != KEY_DOWN_U)
	{

		Trun_Off_Point(Snake.X[0], Snake.Y[0]); 		 //先把蛇尾给熄灭掉 

		for (i = 0; i < Snake.Long - 1; i++)                  //蛇身都是它前一段的蛇身的位置
		{
			Snake.X[i] = Snake.X[i + 1];
			Snake.Y[i] = Snake.Y[i + 1];
		}

		Snake.X[Snake.Long - 1] = Snake.X[Snake.Long - 2] + 0;
		Snake.Y[Snake.Long - 1] = Snake.Y[Snake.Long - 2] + 1; //蛇头向你要求的方向移动

		for (i = 0; i < Snake.Long; i++)			           //这个让蛇显示出来的函数
		{
			Trun_On_Point(Snake.X[i], Snake.Y[i]);
		}
		Key_V_temp = KEY_DOWN_D;

		Key_Value = 0;
		//while(RmtCnt!=0);//松手检测    
	}
	if (Key_Value == KEY_DOWN_B) // check if button left is pressed
	{
		LCD_Clear(BLACK);
		game_sel = 0;
		snake_flag = 0;
		Key_V_temp = KEY_DOWN_B;
		Key_Value = 0;
	}

	/****************根据按键选择蛇的运动程序结束*******************/
	/////////////////////////////////////////////////////////////////

	/************************判断蛇是否死亡***********************/

  //判蛇头是否撞到墙壁
	if (Snake.X[Snake.Long - 1] <= 0 || Snake.X[Snake.Long - 1] >= 39 || Snake.Y[Snake.Long - 1] <= 3 || Snake.Y[Snake.Long - 1] >= 31)
	{
		Snake.Life = 1;//死亡
	}

	for (i = 3; i < Snake.Long; i++)//从第三节开始判断蛇头是否咬到自己
	{
		if (Snake.X[i] == Snake.X[0] && Snake.Y[i] == Snake.Y[0])
		{
			Snake.Life = 1;//死亡
		}
	}

	if (Snake.Life == 1)//死亡
	{
		Display_dead();//GAME OVER
	}
	/******************判断蛇是否死亡程序结束***********************/
	/////////////////////////////////////////////////////////////////


	/************************判断蛇是否最长了**********************/
	if (Snake.Long == SNAKE_Max_Long)
	{
		Display_Pass();//过关
	}
	/////////////////////////////////////////////////////////////////										   

	/*************************判蛇是否吃到食物**********************/
	if (Snake.X[Snake.Long - 1] == Food.X && Snake.Y[Snake.Long - 1] == Food.Y)//
	{
		//Trun_Off_Point(Food.X,Food.Y); 		 //消隐食物
		Snake.Long++;//蛇节数加1
		Snake.X[Snake.Long - 1] = Food.X;
		Snake.Y[Snake.Long - 1] = Food.Y;
		Snake.Score += 10;
		display_num_format(116, 3, (u32)Snake.Score, 1, "%d", RED, BLACK);
		//LCD_ShowNum(50, 280, (u32)Snake.Score, 4, 16);
		Food.Yes = 1;  //食物标志置1
	}
	/////////////////////////////////////////////////////////////////

	/***************************放果子程序*************************/
	if (Food.Yes == 0)
	{
		Trun_On_Point(Food.X, Food.Y);
	}
	if (Food.Yes == 1)
	{
		while (1)
		{
			Food.X = rand() % 28 + 1;      			//获得随机数
			Food.Y = rand() % 28 + 3;

			for (i = 0; i < Snake.Long; i++)				//判断产生的食物坐标是否和蛇身重合
			{
				if ((Food.X == Snake.X[i]) && (Food.X == Snake.Y[i])) break;
			}
			if (i == Snake.Long)
			{
				Food.Yes = 0;
				break;								//产生有效的食物坐标
			}
		}
	}

	Run_Ahead();//直走

	/**************************调整游戏速度************************/
	bsp_DelayMS(201 - Snake.Level * 10);
	/////////////////////////////////////////////////////////////////			
}

void RUN_SNK(void)
{
	if (snake_flag == 0)
	{
		Init_SNAKE();
	}
	else
	{
		Key_Value = bsp_GetKey();
		Run_SNAKE();
	}
}
