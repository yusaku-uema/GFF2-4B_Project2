#include"DxLib.h"
#include "Help.h"
#include"Title.h"

Help::Help()
{

	/*g_Titleimage = LoadGraph("images/�R���g���[���[�摜2.png");*/
}

void  Help::Update()
{

}

void Help::Draw()
{
	DrawExtendGraph(0, 0, 1280, 720, GetArrayImages(Help_Images, 0), TRUE); //�^�C�g���摜�\��;
	ChangeScene();
}

void Help::ChangeScene()
{
	DrawString(0, 685, "A�{�^���Ŗ߂�", GetColor(255, 0, 0));
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A)SetGameState(0);
}