#pragma once
#include "AdstractScene.h"

class Title :public AdstractScene
{
private:
   int g_MenuNumber; //���j���[�J�[�\���������ԂȂ̂��B
   int g_MenuY; //�J�[�\���̈ʒu
   int g_KeyFlg; //�������̓L�[��
   int g_OldKey; //�O��̓���
   int g_NowKey; //����̓��̓L�[
   int g_TitleSE; //����SE
   int g_TitleBGM; //�^�C�g���ɗ����BGM
   int g_Titleimage; //�^�C�g���w�i

public:
    //�R���X�g���N�^
    Title();
    //�`��ȊO�̍X�V�����s
     void Update() override;
    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
    //�V�[���؂�ւ�
    AdstractScene* ChangeScene();

};

