#include"DxLib.h"
#include "GameMain.h"
#include"InputRankingScene.h"

GameMain::GameMain()
{
	map.MapInit();
	/*ranking.ReadRanking();*/
}

AbstractScene* GameMain::Update()
{
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_B) {
		return new InputRanking(7,ui.g_score);
	}
	ui.ScoreMove();
	ui.TimeMove();
	if (ui.g_time <= 0)return new Title;
	player.Movement();
	ranking.InputRankingInit();
	return this;
}

void GameMain::Draw() const
{
	map.Draw();
	ui.Draw();
	player.Draw();
}