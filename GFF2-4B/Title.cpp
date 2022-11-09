#include"DxLib.h"
#include"GameMain.h"
#include"Help.h"
#include "Title.h"

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
	return this;
}

void Title::Draw() const
{
	DrawString(0, 0,  "Aでゲーム", GetColor(255, 0, 0));
	DrawString(0, 40, "Bでヘルプ", GetColor(255, 0, 0));
}
