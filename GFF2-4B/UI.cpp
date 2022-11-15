#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"UI.h"


UI::UI()
{
	g_score = 0;
	g_time = 200;
	g_timeisup = FALSE;
	count = 0;
	g_stage_item_quantity = 2;
	g_pickaxeimage = LoadGraph("images/pickaxe01.png");
	g_whiteimage = LoadGraph("images/white.png");
	g_bombimage = LoadGraph("images/BomFire.png");
}


void UI::ScoreMove()
{
	//if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A)g_score += 50; //テスト
}

void  UI::TimeMove()
{

	if (count++ % fps == 0) {

		if (--g_time >= 0)
		{
			g_timeisup = FALSE;
		}
		else
		{
			g_timeisup = TRUE;
		}
	}

}

void UI::Draw()const
{
	SetFontSize(60);
	DrawFormatString(0, 30, 0xffffff, "SCORE:%d", g_score);
	DrawFormatString(700, 30, 0xffffff, "TIME:%d", g_time);
	int a = (1280 - (150 * (g_stage_item_quantity - 1))) / 2;

	for (int i = 0; i < 4; i++)
	{
		DrawRotaGraph(a + (150 * i), 660, 1.0, M_PI / 180 * 0, g_whiteimage, TRUE, FALSE);
		if (i == 0) DrawRotaGraph(a + (150 * i), 660, 3.0, M_PI / 180 * 0, g_pickaxeimage, TRUE, FALSE);
		if (i == 1) DrawRotaGraph(a + (150 * i), 660, 3.0, M_PI / 180 * 0, g_bombimage, TRUE, FALSE);
		//if (i == 2) DrawRotaGraph(a + (150 * i), 660, 3.0, M_PI / 180 * 0, g_item_image[1], TRUE, FALSE);
		//if (i == 3)DrawRotaGraph(a + (150 * i), 660, 3.0, M_PI / 180 * 0, g_hammer, TRUE, FALSE);
		//if (i == g_uicursorx)DrawRotaGraph(a + (150 * i), 660, 3.3, M_PI / 180 * 0, g_Cursorimage, TRUE, FALSE); //アイテムカーソル
	}
}

int UI::gettimeisup() {
	return g_timeisup;
}