#include "Gameover.h"
#include"DxLib.h"

void Gameover::Draw()
{
	SetFontSize(40);
	DrawGraph(0, 0, GetArrayImages(GameOver_Images, 0), TRUE);
	DrawString(400, 350, "Score", GetColor(255, 0, 0));
	DrawFormatString(550, 350, GetColor(255, 0, 0), "%d", GetScore());
	DrawString(400, 280, "B�{�^���Ń^�C�g����", GetColor(255, 0, 0));
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B) {
		SetGameState(0);
	}

	DrawGraph(400, 450, GetArrayImages(Item_Images, 1), FALSE); //�J�M
	DrawString(435, 450, " = 5000�_", GetColor(255, 0, 0));
	DrawGraph(400, 500, GetArrayImages(Item_Images, 2), FALSE); //��
	DrawString(435, 500, " = 1000�_", GetColor(255, 0, 0));
	DrawString(400, 550, "���� = 1�b100�_", GetColor(255, 0, 0));

}