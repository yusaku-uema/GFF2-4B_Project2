#include"DxLib.h"
#include "Title.h"
#include"Credit.h"

Title::Title()
{
	g_MenuNumber = 0;
	g_MenuY = 160;
	g_OldKey = 0;
	g_NowKey = 0;
	g_KeyFlg = 0;
}


void Title::Update()
{

	g_OldKey = g_NowKey;
	g_NowKey = GetJoypadInputState(DX_INPUT_PAD1);
	g_KeyFlg = g_NowKey & ~g_OldKey;

	//メニューカーソル移動処理
	if (g_KeyFlg & PAD_INPUT_DOWN) {
		if (++g_MenuNumber > 4) g_MenuNumber = 0; //下十字キー押されたら　MenuNumberを+1する。
	}
	if (g_KeyFlg & PAD_INPUT_UP) {
		if (--g_MenuNumber < 0) g_MenuNumber = 4; //上十字キー押されたら、MenuNumberを-1する。
	}


	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_B) {   //SE再生
		if (CheckSoundMem(GetSounds(Title_SE)) != 1) {   //SEが流れていなかったら再生
			ChangeVolumeSoundMem(255 * 80 / 100, GetSounds(Title_SE)); //SE音量調整 255最大音量から80%再生
			PlaySoundMem(GetSounds(Title_SE), DX_PLAYTYPE_NORMAL, TRUE); //SE再生
		}
	}
	g_MenuY = g_MenuNumber * 60; //　カーソル位置60

	Draw(); //描画
	ChangeScen(); //シーン切り替え
}

void Title::Draw()
{
	DrawGraph(0, 0, GetArrayImages(Title_Images,0), TRUE);
	DrawTriangle(470, 295 + g_MenuY, 490, 310 + g_MenuY, 470, 325 + g_MenuY, GetColor(255, 0, 0), TRUE); //カーソル
	SetFontSize(60); //文字のサイズ
	DrawString(350, 200,"掘れ掘れダンジョン君",GetColor(255,255,0));
	DrawString(500, 280, "GameStart", GetColor(255, 0, 0));
	DrawString(500, 340, "Help", GetColor(255, 0, 0));
	DrawString(500, 400, "Ranking", GetColor(255, 0, 0));
	DrawString(500, 460, "Credit　", GetColor(255, 0, 0));
	DrawString(500, 520, "End", GetColor(255, 0, 0));
	SetFontSize(30); 
	DrawString(100, 650, "ヘルプ表示処理なし", GetColor(255, 0, 0));
}


void Title::ChangeScen()
{
	if (g_KeyFlg & PAD_INPUT_B && g_MenuNumber == 0) SetGameState(1); //ゲームメイン移行
	//if (g_KeyFlg & PAD_INPUT_B && g_MenuNumber == 1)return new Help; //ヘルプ画面に移行
	if (g_KeyFlg & PAD_INPUT_B && g_MenuNumber == 2) SetGameState(6);
	if (g_KeyFlg & PAD_INPUT_B && g_MenuNumber == 3) SetGameState(5);
	if (g_KeyFlg & PAD_INPUT_B && g_MenuNumber == 4)SetGameState(999); //強制終了

}