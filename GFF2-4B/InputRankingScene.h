#pragma once
#include"Ranking.h"
#include"UI.h"

class InputRanking  {
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
	void  Update();

	//描画に関することを実装する
	 void Draw();
	//シーン切り替え
	void  ChangeScene();

	
};