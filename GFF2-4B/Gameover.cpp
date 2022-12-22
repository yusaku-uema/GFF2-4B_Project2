#include "Gameover.h"
#include"DxLib.h"

void Gameover::Draw()
{
	SetFontSize(40);
	DrawGraph(0, 0, GetArrayImages(GameOver_Images, 0), TRUE);
	DrawString(400, 350, "Score", GetColor(255, 0, 0));
	DrawFormatString(550, 350, GetColor(255, 0, 0), "%d", GetScore());
	DrawString(400, 280, "Bボタンでタイトルへ", GetColor(255, 0, 0));
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B) {
		SetGameState(0);
	}

	DrawGraph(400, 450, GetArrayImages(Item_Images, 1), FALSE); //カギ
	DrawString(435, 450, " = 5000点", GetColor(255, 0, 0));
	DrawGraph(400, 500, GetArrayImages(Item_Images, 2), FALSE); //袋
	DrawString(435, 500, " = 1000点", GetColor(255, 0, 0));
	DrawString(400, 550, "時間 = 1秒100点", GetColor(255, 0, 0));

}