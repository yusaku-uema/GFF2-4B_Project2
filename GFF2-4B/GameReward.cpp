#include "GameReward.h"
#include"DxLib.h"
#include"InputRankingScene.h"

GameReward::GameReward(){
	OpenBox = LoadGraph("images/宝箱２_transparent.png");
	OpenBox2 = LoadGraph("images/宝箱1_transparent.png");
	g_MenuX = 160;
	g_BoxNumber = 0;
	g_NowKey = 0;
	g_KeyFlg = 0;
	g_OldKey = 0;
}
AbstractScene* GameReward::Update(){
	/*if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_B)
	{
		return new InputRanking(7);
	}*/
	g_OldKey = g_NowKey;
	g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	g_KeyFlg = g_NowKey & ~g_OldKey;
	g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (g_KeyFlg & PAD_INPUT_RIGHT)
	{
		if (++g_BoxNumber > 4) g_BoxNumber = 0;
	}
	if (g_KeyFlg & PAD_INPUT_LEFT)
	{
		if (--g_BoxNumber < 0) g_BoxNumber = 4;
	}
	//メニューカーソル（三角形）の表示
	g_MenuX = g_BoxNumber * 120;
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_B && g_BoxNumber == 0)DrawGraph(100,200, OpenBox2,TRUE); //ここまで作業中
	return this;
}
void GameReward::Draw()const {
	DrawTriangle(g_MenuX + 95, 370, g_MenuX + 110, 390 , g_MenuX + 125,370, GetColor(255, 0, 0), TRUE); //カーソル
	//DrawTriangle(295, 470 + g_MenuX, 310, 490 + g_MenuX, 325, 470 + g_MenuX, GetColor(255, 0, 0), TRUE); //カーソル
	DrawRotaGraph(160, 200,2.0 ,0.0, OpenBox, TRUE);
	DrawRotaGraph(280, 200,2.0 ,0.0, OpenBox, TRUE);
	DrawRotaGraph(400, 200,2.0 ,0.0,OpenBox, TRUE);
	
}