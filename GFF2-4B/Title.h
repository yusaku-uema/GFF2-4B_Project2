#pragma once
#include"main.h"

class Title 
{
private:
   int g_MenuNumber; //���j���[�J�[�\���������ԂȂ̂��B
   int g_MenuY; //�J�[�\���̈ʒu
   int g_KeyFlg; //�������̓L�[��
   int g_OldKey; //�O��̓���
   int g_NowKey; //����̓��̓L�[
   int BGM;

public:
    //�R���X�g���N�^
    Title();
    void Update(); //�`��ȊO
    void Draw(); //�`��
    void ChangeScen(); //�V�[���؂�ւ�


};

