#include "Credit.h"
#include"DxLib.h"

void Credit::Draw()
{
	DrawGraph(0, 0, GetArrayImages(Title_Images, 0), FALSE);
	g_OldKey = g_NowKey;
	g_NowKey = GetJoypadInputState(DX_INPUT_PAD1);
	g_KeyFlg = g_NowKey & ~g_OldKey;

DrawString(100, 100, "���؂肵�����f��", GetColor(0, 255, 0));
DrawString(100, 200, "������", GetColor(255, 0, 0));
DrawString(100, 300, "���[�t���J", GetColor(255, 0, 0));
DrawString(100, 400, "�C���V�����y�f��", GetColor(255, 0, 0));
ChangeScen();

DrawString(530, 600, "A�{�^���Ŗ߂�", GetColor(255, 0, 0));
}

void Credit::ChangeScen()
{
	if (g_KeyFlg & PAD_INPUT_A)SetGameState(0);
}
