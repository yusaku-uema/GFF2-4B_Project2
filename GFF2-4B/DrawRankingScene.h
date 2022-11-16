#pragma once
#include"AdstractScene.h"
#include"Ranking.h"

class DrawRanking :public AdstractScene {
private:
	//RANKING ranking;
	int g_DrawRankingGameState;
public:
	DrawRanking(int g_GameState);

	DrawRanking(); //コンストラクタ
	//デストラクタ
	virtual~DrawRanking() {};

	//描画以外の更新を実装する
	void  Update() override;

	//描画に関することを実装する
	virtual void Draw() const override;
	//シーン切り替え
	AdstractScene* ChangeScene();
};