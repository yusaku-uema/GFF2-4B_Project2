#include "Credit.h"
#include"DxLib.h"

void Credit::Draw()
{

DrawString(100, 100, "お借りした音素材", GetColor(0, 255, 0));
DrawString(100, 200, "魔王魂", GetColor(255, 0, 0));
DrawString(100, 300, "ユーフルカ", GetColor(255, 0, 0));
DrawString(100, 400, "イワシロ音楽素材", GetColor(255, 0, 0));
ChangeScen();
}

void Credit::ChangeScen()
{
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B)SetGameState(0);
}
