#pragma once
#include"AbstractScene.h"
#include"Ranking.h"

class DrawRanking :public AbstractScene {
private:
	RANKING ranking;
public:
	DrawRanking(int g_GameState);


	//デストラクタ
	virtual~DrawRanking() {};

	//描画以外の更新を実装する
	virtual AbstractScene* Update() override;

	//描画に関することを実装する
	virtual void Draw() const override;

	int g_DrawRankingGameState;
};