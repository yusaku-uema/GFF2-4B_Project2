#include"DxLib.h"
#include "GameMain.h"

GameMain::GameMain()
{
	map.MapInit();
}

AbstractScene* GameMain::Update()
{
	player.Movement();
	return this;
}

void GameMain::Draw() const
{
	map.Draw();
	player.Draw();
}