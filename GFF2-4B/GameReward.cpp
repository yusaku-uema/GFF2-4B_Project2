#include "GameReward.h"
#include"DxLib.h"
#include"InputRankingScene.h"

GameReward::GameReward()
{
	g_MenuX = 160;
	g_BoxNumber = 0;
	g_NowKey = 0;
	g_KeyFlg = 0;
	g_OldKey = 0;
}
void GameReward::Update()
{
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
		if (++g_BoxNumber > 2) g_BoxNumber = 0;
	}
	if (g_KeyFlg & PAD_INPUT_LEFT)
	{
		if (--g_BoxNumber < 0) g_BoxNumber = 2;
	}
	//メニューカーソル（三角形）の表示
	g_MenuX = g_BoxNumber * 120;
	//if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_B && g_BoxNumber == 0)DrawGraph(120, 300, (Box2_images,0), TRUE); //ここまで作業中
	
	Draw();
}
void GameReward::Draw()
{
	DrawTriangle(g_MenuX + 95, 370, g_MenuX + 110, 390, g_MenuX + 125, 370, GetColor(255, 0, 0), TRUE); //カーソル
	//DrawTriangle(295, 470 + g_MenuX, 310, 490 + g_MenuX, 325, 470 + g_MenuX, GetColor(255, 0, 0), TRUE); //カーソル
	if (takara == false)
	{
		DrawRotaGraph(120, 300, 2.0, 0.0, GetArrayImages(Box_images, 0), TRUE);
	}
	if (takara1 == false)
	{
		DrawRotaGraph(240, 300, 2.0, 0.0, GetArrayImages(Box_images, 0), TRUE);
	}
	if (takara2 == false)
	{
		DrawRotaGraph(360, 300, 2.0, 0.0, GetArrayImages(Box_images, 0), TRUE);
	}
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_B && g_BoxNumber == 0)takara=TRUE, --test;
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_B && g_BoxNumber == 1)takara1 = TRUE, --test;
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_B && g_BoxNumber == 2)takara2 = TRUE, --test;

	if (takara == TRUE && test > 0)
	{
		/*DrawGraph(120, 300, GetArrayImages(Box2_images, 0), TRUE);*/
		DrawRotaGraph(120, 300, 2.0, 0.0, GetArrayImages(Box2_images, 0), TRUE);
		
	}
	if (takara1 == TRUE && test > 0)
	{
		/*DrawGraph(120, 300, GetArrayImages(Box2_images, 0), TRUE);*/
		DrawRotaGraph(240, 300, 2.0, 0.0, GetArrayImages(Box2_images, 0), TRUE);
		
	}
	if (takara2 == TRUE && test > 0)
	{
		/*DrawGraph(120, 300, GetArrayImages(Box2_images, 0), TRUE);*/
		DrawRotaGraph(360, 300, 2.0, 0.0, GetArrayImages(Box2_images, 0), TRUE);
		
	}
}
