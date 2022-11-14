#include"DxLib.h"
#include "GameMain.h"
#include"InputRankingScene.h"
#include"Title.h"

GameMain::GameMain()
{
	map.MapInit();
}

AbstractScene* GameMain::Update()
{
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_B) {
		return new InputRanking(7);
	}
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_Y) {
		//return ゲームクリア移行
	}
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