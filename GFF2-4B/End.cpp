#include"DxLib.h"
#include"End.h"
#include"GameMain.h"
#include "Title.h"

End::End()
{

}

void  End::Update()
{

}

void End::Draw() 
{
	DrawString(0, 10, "A�Ń^�C�g�����", GetColor(255, 0, 0));
	DrawString(0, 60, "B�ŃQ�[�����C��", GetColor(255, 0, 0));
}

