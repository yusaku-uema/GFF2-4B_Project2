#include"DxLib.h"
#include "Help.h"
#include"Title.h"

Help::Help()
{

}

AbstractScene* Help::Update()
{
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A) {
		return new Title;
	}
	return this;
}

void Help::Draw() const
{
	DrawString(100, 200, "‚±‚±‚Íƒwƒ‹ƒv‰æ–Ê‚Å‚·", GetColor(255, 0, 0));
}