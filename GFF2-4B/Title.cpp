#include"DxLib.h"
#include"GameMain.h"
#include"Help.h"
#include "Title.h"
#include"Credit.h"

Title::Title()
{

}

AbstractScene* Title::Update()
{

	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_A) {
		return new GameMain;
	}
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_B) {
		return new Help;
	}
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_X) {
		return new Credit;
	}
	return this;
}

void Title::Draw() const
{
	DrawString(0, 10,  "Aでゲーム", GetColor(255, 0, 0));
	DrawString(0, 60, "Bでヘルプ", GetColor(255, 0, 0));
	DrawString(0, 80, "Yでクレジット", GetColor(255, 0, 0));
}
