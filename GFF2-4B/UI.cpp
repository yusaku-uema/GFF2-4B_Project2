#include"DxLib.h"
#include"UI.h"

UI::UI()
{
	g_score = 0;
	g_time = 3600;
}


void UI::ScoreMove()
{
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A)g_score += 50;
}

void UI::TimeMove()
{
	if (--g_time <= 0)
	{
	}


}

void UI::Draw()const
{
	SetFontSize(30);
	DrawFormatString(0, 200, 0xffffff, "スコア::%d", g_score);
	DrawFormatString(0, 250, 0xffffff, "タイム::%d", g_time / 60);
}