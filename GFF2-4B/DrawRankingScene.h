#pragma once
#include"Ranking.h"
#include"main.h"

class DrawRanking {
private:
	//RANKING ranking;
	int g_DrawRankingGameState;
public:
	DrawRanking(int g_GameState);

	DrawRanking(); //コンストラクタ
	//デストラクタ
	virtual~DrawRanking() {};

	//描画以外の更新を実装する
	void  Update();

	//描画に関することを実装する
	 void Draw() const;
	//シーン切り替え
	void ChangeScene();
};