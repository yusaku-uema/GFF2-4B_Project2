#include"DxLib.h"
#include "GameMain.h"
#include"main.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"Player.h"

Player player;

/***********************************************
*  初期化処理
************************************************/
void GameMain::GameMain_Init()
{
	player.Player_Init();
	SetGameState(2); //ゲームメイン移行
}


/***********************************************
*  ゲーム処理
************************************************/
void GameMain::Update()
{
	player.Key();
	player.Draw_Item();
	player.Stage();
	player.Player_Sousa(); //自機の操作
	player.UI();
}

/***********************************************
* シーン切り替え
************************************************/
void GameMain::Draw() 
{
	
}
