#include"InputRankingScene.h"
#include"Ranking.h"

InputRanking::InputRanking(int g_GameState) {
	g_InputRankingGameState = g_GameState;
}

AbstractScene* InputRanking::Update() {
	if (g_InputRankingGameState == 7) {
		ranking.InputRanking();
		return this;
	}
	return nullptr;
}

void InputRanking::Draw() const{
	ranking.InputRanking();
}