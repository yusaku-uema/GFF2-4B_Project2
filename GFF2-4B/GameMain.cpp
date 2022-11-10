#include"DxLib.h"
#include "GameMain.h"

GameMain::GameMain()
{
	map.MapInit();
}

AbstractScene* GameMain::Update()
{
	ui.ScoreMove();
	ui.TimeMove();
	if (ui.g_time <= 0)return new Title;
	player.Movement();
	return this;
}

void GameMain::Draw() const
{
	map.Draw();
	ui.Draw();
	player.Draw();
}