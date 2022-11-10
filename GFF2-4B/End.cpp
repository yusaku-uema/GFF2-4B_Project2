#include"DxLib.h"
#include"End.h"
#include"GameMain.h"
#include "Title.h"

End::End()
{

}

AbstractScene* Title::Update()
{

	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_A) {
		return new Title;
	}
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_B) {
		return new GameMain;
	}
	return this;
}

void Title::Draw() const
{
	DrawString(0, 10, "Aでタイトル画面", GetColor(255, 0, 0));
	DrawString(0, 60, "Bでゲームメイン", GetColor(255, 0, 0));
}
