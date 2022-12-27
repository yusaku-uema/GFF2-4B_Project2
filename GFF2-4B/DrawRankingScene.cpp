#include"DrawRankingScene.h"
#include"GameMain.h"
#include"Title.h"
#include"main.h"

DrawRanking::DrawRanking() {
	
}

void  DrawRanking::Update() {
	ranking.DrawRanking();
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B)
	{
		SetGameState(0);
	}
}

void DrawRanking::Draw() const {
	
}

void DrawRanking::ChangeScene()
{
	//if (g_DrawRankingGameState == 1) {
	//	//Bボタンでタイトルに戻る
	//	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A) {
	//	}
	//}
	//return nullptr;
}