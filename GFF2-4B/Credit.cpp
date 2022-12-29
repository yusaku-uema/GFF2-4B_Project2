#include "Credit.h"
#include"DxLib.h"

void Credit::Draw()
{
	DrawGraph(0, 0, GetArrayImages(Title_Images, 0), FALSE);
	g_OldKey = g_NowKey;
	g_NowKey = GetJoypadInputState(DX_INPUT_PAD1);
	g_KeyFlg = g_NowKey & ~g_OldKey;

DrawString(100, 100, "お借りした音素材", GetColor(0, 255, 0));
DrawString(100, 200, "魔王魂", GetColor(255, 0, 0));
DrawString(100, 300, "ユーフルカ", GetColor(255, 0, 0));
DrawString(100, 400, "イワシロ音楽素材", GetColor(255, 0, 0));
ChangeScen();

DrawString(530, 600, "Aボタンで戻る", GetColor(255, 0, 0));
}

void Credit::ChangeScen()
{
	if (g_KeyFlg & PAD_INPUT_A)SetGameState(0);
}
