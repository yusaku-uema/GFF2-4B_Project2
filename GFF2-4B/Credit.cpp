#include "Credit.h"
#include"DxLib.h"
#include"title.h"
//Credit::Credit()
//{
//}

AbstractScene* Credit::Update() {
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B) {
		return new Title;
	}
	return this;
}

void Credit::Draw() const
{
	DrawString(100, 200, "魔王魂", GetColor(255, 0, 0));
	DrawString(100, 300, "ユーフルカ", GetColor(255, 0, 0));
	DrawString(100, 400, "イワシロ音楽素材", GetColor(255, 0, 0));

}
