#pragma once
#include "AbstractScene.h"
class GameReward :
	public AbstractScene
{
private:
   
public:
    //�R���X�g���N�^
    GameReward();
    //�f�X�g���N�^
    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;
    int OpenBox;//�󔠂̉摜�ϐ�
    int OpenBox2;
    int g_MenuX;
    int g_KeyFlg;
    int g_BoxNumber;
    int g_NowKey;
    int g_OldKey;
    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};

