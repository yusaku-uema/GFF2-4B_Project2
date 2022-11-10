#pragma once
#include"SceneManager.h"
#include"Ranking.h"

class InputRanking :public AbstractScene {
private:
	RANKING ranking;
public:
	InputRanking(int g_GameState);

	//デストラクタ
	~InputRanking() {};

	//描画以外の更新を実装する
 AbstractScene* Update() override;

	//描画に関することを実装する
	void Draw() const override;

	int g_InputRankingGameState;
};