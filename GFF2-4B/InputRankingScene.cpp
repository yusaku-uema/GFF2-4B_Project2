#include"InputRankingScene.h"
#include"DrawRankingScene.h"
#include"Ranking.h"
#include"DxLib.h"

InputRanking::InputRanking(int g_GameState,int n) {
	g_InputRankingGameState = g_GameState;
	g_score = n;
}

void InputRanking::Draw() const{
	//ranking.InputRankingDraw();
}

void  InputRanking::Update() {
	//if (g_InputRankingGameState == 7) {
	//	//ranking.InputRankingInit();
	//	//ranking.g_Score += g_score;
	//	g_InputRankingGameState = 2;
	//}
	//if (g_InputRankingGameState == 2) {
	//	//ranking.InputRanking();
	//	if (ranking.g_nowfontY == 6 && ranking.g_nowfontX >= 6 && ranking.g_nowfontX <= 7 && GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B)
	//	{
	//		g_InputRankingGameState = 3;
	//	}
	//	return this;
	//}
	//if (g_InputRankingGameState == 3) {
	//	return new DrawRanking(1);
	//}
	//return nullptr;
}

AdstractScene* InputRanking::ChangeScene()
{
	return this;
}

int InputRanking::getvalue(int n) {
	return g_InputRankingGameState = n;
}