#include"DrawRankingScene.h"
#include"GameMain.h"
#include"Title.h"

DrawRanking::DrawRanking(int g_GameState) {
	g_DrawRankingGameState = g_GameState;
}

AbstractScene* DrawRanking::Update() {
	if (g_DrawRankingGameState == 1) {
		//Bボタンでタイトルに戻る
		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A) {
			return new Title;
		}
		return this;
	}
	return nullptr;
}

void DrawRanking::Draw() const {
	ranking.DrawRanking();
}