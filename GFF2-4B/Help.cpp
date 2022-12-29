#include"DxLib.h"
#include "Help.h"
#include"Title.h"

Help::Help()
{

	/*g_Titleimage = LoadGraph("images/コントローラー画像2.png");*/
}

void  Help::Update()
{

}

void Help::Draw()
{
	DrawExtendGraph(0, 0, 1280, 720, GetArrayImages(Help_Images, 0), TRUE); //タイトル画像表示;
	ChangeScene();
}

void Help::ChangeScene()
{
	DrawString(0, 685, "Aボタンで戻る", GetColor(255, 0, 0));
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A)SetGameState(0);
}