#include"InputRankingScene.h"
#include"DrawRankingScene.h"
#include"Ranking.h"
#include"main.h"
#include"DxLib.h"

InputRanking::InputRanking() {
	
}

void InputRanking::Draw() {
	//ranking.InputRankingDraw();
}

void  InputRanking::Update() {
	for ( i ; i < 1; i++)
	{
		ranking.InputRankingInit();
	}
	ranking.InputRankingDraw();
  ranking.InputRanking();
 if (ranking.g_nowfontY == 6 && ranking.g_nowfontX >= 6 && ranking.g_nowfontX <= 7 && GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B)
 {
	SetGameState(6);
 }
	
}

void InputRanking::ChangeScene()
{

}

int InputRanking::getvalue(int n) {
	return g_InputRankingGameState = n;
}