#include"DxLib.h"
#include"GameMain.h"
#include"Help.h"
#include "Title.h"

Title::Title()
{
	g_MenuNumber = 0;
	g_MenuY = 160;
	g_OldKey = 0;
	g_NowKey = 0;
	g_KeyFlg = 0;
	g_TitleSE = LoadSoundMem("BGM/decision.mp3");
}

AbstractScene* Title::Update()
{

	g_OldKey = g_NowKey;
	g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	g_KeyFlg = g_NowKey & ~g_OldKey;

	//メニューカーソル移動処理
	if (g_KeyFlg & PAD_INPUT_DOWN) {
		if (++g_MenuNumber > 4) g_MenuNumber = 0;
	}
	if (g_KeyFlg & PAD_INPUT_UP) {
		if (--g_MenuNumber < 0) g_MenuNumber = 4;
	}


	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_B) {   //SE再生
		if (CheckSoundMem(g_TitleSE) != 1) {   //SEが流れていなかったら再生
			ChangeVolumeSoundMem(255 * 80 / 100, g_TitleSE); //SE音量調整 255最大音量から80%再生
			PlaySoundMem(g_TitleSE, DX_PLAYTYPE_NORMAL, TRUE); //SE再生
		}
	}

	if (g_KeyFlg &  PAD_INPUT_B && g_MenuNumber == 0)return new GameMain;
	if (g_KeyFlg &  PAD_INPUT_B && g_MenuNumber == 1)return new Help;
	/*if (g_KeyFlg & PAD_INPUT_B && g_MenuNumber == 2)return  new Ranking();*/
	//if (g_KeyFlg &  PAD_INPUT_B && g_MenuNumber == 3)return  new クレジット
	if (g_KeyFlg & PAD_INPUT_B && g_MenuNumber == 4)return  nullptr;

	
	g_MenuY = g_MenuNumber * 60; //　カーソル

	return this;
}

void Title::Draw() const
{
	DrawTriangle(470, 295 + g_MenuY, 490, 310 + g_MenuY, 470, 325 + g_MenuY, GetColor(255, 0, 0), TRUE); //カーソル
	SetFontSize(60);
	DrawString(500, 280, "Game Start", GetColor(255, 0, 0));
	DrawString(500, 340, "Help", GetColor(255, 0, 0));
	DrawString(500, 400, "Ranking,", GetColor(255, 0, 0));
	DrawString(500, 460, "Credit　", GetColor(255, 0, 0));
	DrawString(500, 520, "End", GetColor(255, 0, 0));
	SetFontSize(30);
	DrawString(100, 650, "ヘルプ表示処理なし、ランキング表示処理なし、クレジット表示処理なし、\nシーン切り替え確認済み", GetColor(255, 0, 0));
}
