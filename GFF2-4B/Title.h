#pragma once
#include "AbstractScene.h"


class Title :
    public AbstractScene
{
private:
   int g_MenuNumber; //���j���[�J�[�\���������ԂȂ̂��B
   int g_MenuY; //�J�[�\���̈ʒu
   int g_KeyFlg; //�������̓L�[��
   int g_OldKey; //�O��̓���
   int g_NowKey; //����̓��̓L�[
public:
    //�R���X�g���N�^
    Title();
    //�f�X�g���N�^
    ~Title()
    {
    }
    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;
    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};

