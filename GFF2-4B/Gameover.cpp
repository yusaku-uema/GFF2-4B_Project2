#include "Gameover.h"
#include"DxLib.h"

void Gameover::Draw()
{
	DrawGraph(0, 0, GetArrayImages(GameOver_Images, 0), TRUE);

	DrawString(500, 280, "B�{�^���Ń^�C�g����", GetColor(255, 0, 0));
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B) {
		SetGameState(0);
	}
}