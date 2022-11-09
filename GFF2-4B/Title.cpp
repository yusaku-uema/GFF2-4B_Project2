#include"DxLib.h"
#include "Title.h"

Title::Title()
{

}

AbstractScene* Title::Update()
{

	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_A) {
		return nullptr;
	}
	return this;
}

void Title::Draw() const
{
	DrawString(0, 0, "AÇ≈ÉQÅ[ÉÄ", GetColor(255, 0, 0));
}