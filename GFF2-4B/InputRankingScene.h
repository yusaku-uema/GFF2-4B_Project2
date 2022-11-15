#pragma once
#include"SceneManager.h"
#include"Ranking.h"
#include"UI.h"

class InputRanking :public AbstractScene {
private:
	RANKING ranking;
	UI ui;
public:
	int g_score;

	InputRanking(int g_GameState,int n);


	//デストラクタ
	virtual~InputRanking() {};

	//描画以外の更新を実装する
	virtual AbstractScene* Update() override;

	//描画に関することを実装する
	virtual void Draw() const override;

	int getvalue(int n);

	int g_InputRankingGameState;
};