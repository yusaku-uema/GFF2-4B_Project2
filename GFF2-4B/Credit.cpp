#include "Credit.h"
#include"DxLib.h"

void Credit::Draw()
{

DrawString(100, 100, "���؂肵�����f��", GetColor(0, 255, 0));
DrawString(100, 200, "������", GetColor(255, 0, 0));
DrawString(100, 300, "���[�t���J", GetColor(255, 0, 0));
DrawString(100, 400, "�C���V�����y�f��", GetColor(255, 0, 0));
ChangeScen();
}

void Credit::ChangeScen()
{
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B)SetGameState(0);
}
