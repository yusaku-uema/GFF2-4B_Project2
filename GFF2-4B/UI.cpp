#include"DxLib.h"
#include"UI.h"

UI::UI()
{
	g_score = 0;
	g_time = 200;
	g_timeisup = FALSE;
	count = 0;
}


void UI::ScoreMove()
{
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A)g_score += 50; //ƒeƒXƒg
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
}

int UI::gettimeisup() {
	return g_timeisup;
}
