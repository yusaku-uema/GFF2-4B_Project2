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

	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_B&& g_MenuNumber==0)return new GameMain;
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_B && g_MenuNumber == 1)return new Help;
	/*if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_B && g_MenuNumber == 2)return  new Ranking();*/
	//if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_B && g_MenuNumber == 3)return  new クレジット
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_B && g_MenuNumber == 4)return  nullptr;
    
	//メニューカーソル（三角形）の表示
    g_MenuY = g_MenuNumber * 60;

	return this;
}

void Title::Draw() const
{
	DrawTriangle(470, 295 + g_MenuY, 490, 310 + g_MenuY, 470, 325 + g_MenuY, GetColor(255, 0, 0), TRUE); //カーソル
	SetFontSize(60);
	DrawString(500, 280,  "Game Start", GetColor(255, 0, 0));
	DrawString(500, 340, "Help", GetColor(255, 0, 0));
	DrawString(500, 400, "Ranking,ランキング表示処理なし、シーン切り替え確認済み", GetColor(255, 0, 0));
	DrawString(500, 460, "Credit　クレジット表示処理なし、シーン切り替え確認済み", GetColor(255, 0, 0));
	DrawString(500, 520, "End", GetColor(255, 0, 0));
}
