#include"DxLib.h"
#include "GameMain.h"
#include"Title.h"

GameMain::GameMain()
{
	map.MapInit();
}

AbstractScene* GameMain::Update()
{
	ui.ScoreMove();
	ui.TimeMove();
	
	player.Movement();

	if (ui.gettimeisup() == TRUE) {
		return new Title();
	}
	return this;
}

void GameMain::Draw() const
{
	map.Draw();
	ui.Draw();
	player.Draw();
}