#include "GameClear.h"
#include"DxLib.h"

void GameClear::Draw()
{
	g_Rankingscore = ranking.GetRankingScore(4);
	g_score = GetScore();
	ranking.InputRankingInit();

	DrawGraph(0, 0, GetArrayImages(GameClear_Images, 0), TRUE);
	SetFontSize(40);
	



	DrawGraph(450, 450, GetArrayImages(Item_Images, 1),FALSE); //カギ
	DrawString(485, 450, " = 5000点", GetColor(255, 0, 0));
	DrawGraph(450, 500, GetArrayImages(Item_Images, 2), FALSE); //袋
	DrawString(485, 500, " = 1000点", GetColor(255, 0, 0));
	DrawString(450, 550, "時間 = 1秒100点", GetColor(255, 0, 0));

}
	DrawString(350, 350, "Score", GetColor(255, 0, 0));
	DrawFormatString(500, 350, GetColor(255, 0, 0), "%d", GetScore());
	DrawString(350, 280, "Bボタンでタイトルへ", GetColor(255, 0, 0));
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B) {
		if (g_score >= g_Rankingscore)SetGameState(11);
		else {
			SetGameState(0);
		}
	}
}
