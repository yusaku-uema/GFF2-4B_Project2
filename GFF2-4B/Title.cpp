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

    //���j���[�J�[�\���ړ�����
    if (g_KeyFlg & PAD_INPUT_DOWN) {
        if (++g_MenuNumber > 4) g_MenuNumber = 0;
    }
    if (g_KeyFlg & PAD_INPUT_UP) {
        if (--g_MenuNumber < 0) g_MenuNumber = 4;
    }

	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_B&& g_MenuNumber==0)return new GameMain;
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_B && g_MenuNumber == 1)return new Help;
	/*if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_B && g_MenuNumber == 2)return  new Ranking();*/
	//if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_B && g_MenuNumber == 3)return  new �N���W�b�g
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_B && g_MenuNumber == 4)return  nullptr;
    
	//���j���[�J�[�\���i�O�p�`�j�̕\��
    g_MenuY = g_MenuNumber * 60;

	return this;
}

void Title::Draw() const
{
	DrawTriangle(470, 295 + g_MenuY, 490, 310 + g_MenuY, 470, 325 + g_MenuY, GetColor(255, 0, 0), TRUE); //�J�[�\��
	SetFontSize(60);
	DrawString(500, 280,  "Game Start", GetColor(255, 0, 0));
	DrawString(500, 340, "Help", GetColor(255, 0, 0));
	DrawString(500, 400, "Ranking,�����L���O�\�������Ȃ��A�V�[���؂�ւ��m�F�ς�", GetColor(255, 0, 0));
	DrawString(500, 460, "Credit�@�N���W�b�g�\�������Ȃ��A�V�[���؂�ւ��m�F�ς�", GetColor(255, 0, 0));
	DrawString(500, 520, "End", GetColor(255, 0, 0));
}
