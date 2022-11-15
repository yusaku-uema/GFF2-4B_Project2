#include"DxLib.h"
#include "GameMain.h"
#include"InputRankingScene.h"

GameMain::GameMain()
{
	map.MapInit();
}

AbstractScene* GameMain::Update()
{
	/*ui.ScoreMove();*/
	ui.TimeMove();
	if (ui.g_time <= 0)return new Title;
	player.Player_Sousa(map);
	player.Hammer(map);
	return this;
}

void GameMain::Draw() const
{
	map.Draw();
	ui.Draw();
	player.Draw();
}