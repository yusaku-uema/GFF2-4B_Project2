#include "Gameover.h"
#include"DxLib.h"

void Gameover::Draw()
{
	SetFontSize(40);
	DrawGraph(0, 0, GetArrayImages(GameOver_Images, 0), TRUE);
	DrawString(400, 350, "Score", GetColor(255, 0, 0));
	DrawFormatString(600, 350, GetColor(255, 0, 0), "%d", GetScore());
	DrawString(400, 280, "Bボタンでタイトルへ", GetColor(255, 0, 0));
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B) {
		StopSoundMem(BGM);
		SetGameState(0);
	}

	if (CheckSoundMem(BGM) != 1) {   //SEが流れていなかったら再生
		BGM = LoadSoundMem("BGM/gameover.mp3");
		ChangeVolumeSoundMem(255 * 40 / 100, BGM); //SE音量調整 255最大音量から80%再生
		PlaySoundMem(BGM, DX_PLAYTYPE_LOOP, TRUE); //SE再生
	}
	DrawGraph(400, 450, GetArrayImages(Item_Images, 1), FALSE); //カギ
	DrawString(435, 450, " = 5000点", GetColor(255, 0, 0));
	DrawGraph(400, 500, GetArrayImages(Item_Images, 2), FALSE); //袋
	DrawString(435, 500, " = 1000点", GetColor(255, 0, 0));
	DrawString(400, 550, "時間 = 1秒100点", GetColor(255, 0, 0));

}