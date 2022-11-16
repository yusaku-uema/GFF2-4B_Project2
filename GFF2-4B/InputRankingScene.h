#pragma once
#include"SceneManager.h"
#include"Ranking.h"
#include"UI.h"

class InputRanking :public AdstractScene {
private:
	/*RANKING ranking;
	UI ui;*/
	int g_score;
	int getvalue(int n);
	int g_InputRankingGameState;

public:
	
	InputRanking(int g_GameState,int n);

	//デストラクタ
	virtual~InputRanking() {};

	//描画以外の更新を実装する
	void  Update() override;

	//描画に関することを実装する
	virtual void Draw() const override;
	//シーン切り替え
	AdstractScene* ChangeScene();

	
};