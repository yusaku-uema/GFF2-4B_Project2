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
	return this;
}

void GameMain::Draw() const
{
	map.Draw();
	ui.Draw();
}