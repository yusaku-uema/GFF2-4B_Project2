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
	g_TitleSE = LoadSoundMem("BGM/decision.mp3");
	g_Titleimage = LoadGraph("images/taitle2.png");
}

void Title::Update()
{


	g_OldKey = g_NowKey;
	g_NowKey = GetJoypadInputState(DX_INPUT_PAD1);
	g_KeyFlg = g_NowKey & ~g_OldKey;

	//���j���[�J�[�\���ړ�����
	if (g_KeyFlg & PAD_INPUT_DOWN) {
		if (++g_MenuNumber > 4) g_MenuNumber = 0; //���\���L�[�����ꂽ��@MenuNumber��+1����B
	}
	if (g_KeyFlg & PAD_INPUT_UP) {
		if (--g_MenuNumber < 0) g_MenuNumber = 4; //��\���L�[�����ꂽ��AMenuNumber��-1����B
	}


	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_B) {   //SE�Đ�
		if (CheckSoundMem(g_TitleSE) != 1) {   //SE������Ă��Ȃ�������Đ�
			ChangeVolumeSoundMem(255 * 80 / 100, g_TitleSE); //SE���ʒ��� 255�ő剹�ʂ���80%�Đ�
			PlaySoundMem(g_TitleSE, DX_PLAYTYPE_NORMAL, TRUE); //SE�Đ�
		}
	}
	g_MenuY = g_MenuNumber * 60; //�@�J�[�\���ʒu60

}

void Title::Draw() const
{
	DrawGraph(0, 0, g_Titleimage, TRUE);
	DrawTriangle(470, 295 + g_MenuY, 490, 310 + g_MenuY, 470, 325 + g_MenuY, GetColor(255, 0, 0), TRUE); //�J�[�\��
	SetFontSize(60);
	DrawString(500, 280, "Game Start", GetColor(255, 0, 0));
	DrawString(500, 340, "Help", GetColor(255, 0, 0));
	DrawString(500, 400, "Ranking,", GetColor(255, 0, 0));
	DrawString(500, 460, "Credit�@", GetColor(255, 0, 0));
	DrawString(500, 520, "End", GetColor(255, 0, 0));
	SetFontSize(30);
	DrawString(100, 650, "�w���v�\�������Ȃ��A�����L���O�\�������Ȃ��A�N���W�b�g�\�������Ȃ�", GetColor(255, 0, 0));
}


AdstractScene* Title::ChangeScene()
{
	if (g_KeyFlg & PAD_INPUT_B && g_MenuNumber == 0)return new GameMain(); //�Q�[�����C���ڍs
	//if (g_KeyFlg & PAD_INPUT_B && g_MenuNumber == 1)return new Help; //�w���v��ʂɈڍs
	///*if (g_KeyFlg & PAD_INPUT_B && g_MenuNumber == 2)return  new Ranking();*/
	////if (g_KeyFlg &  PAD_INPUT_B && g_MenuNumber == 3)return  new �N���W�b�g
	if (g_KeyFlg & PAD_INPUT_B && g_MenuNumber == 4)return  nullptr(); //�����I��

	return this;
}