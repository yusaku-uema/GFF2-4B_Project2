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
	DrawString(100, 200, "������", GetColor(255, 0, 0));
	DrawString(100, 300, "���[�t���J", GetColor(255, 0, 0));
	DrawString(100, 400, "�C���V�����y�f��", GetColor(255, 0, 0));

}
