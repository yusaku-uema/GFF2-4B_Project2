#include "GameClear.h"
#include"DxLib.h"

void GameClear::Draw()
{
	g_score = ranking.GetRankingScore(5);
	DrawGraph(0, 0, GetArrayImages(GameClear_Images, 0), TRUE);
	SetFontSize(40);
	DrawString(350, 350, "Score", GetColor(255, 0, 0));
	DrawFormatString(500, 350, GetColor(255, 0, 0), "%d", GetScore());
	DrawString(350, 280, "Bボタンでタイトルへ", GetColor(255, 0, 0));
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B) {
		if (GetScore() >= g_score)SetGameState(10);
		else {
			SetGameState(0);
		}
	}
}
