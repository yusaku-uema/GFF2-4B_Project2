#pragma once
#include"main.h"
class GameReward
{
private:
    bool takara;
    bool takara1;
    bool takara2;
public:
    //�R���X�g���N�^
    GameReward();
    //�f�X�g���N�^
    //�`��ȊO�̍X�V�����s
    void Update();
    int test=2; //���Ƃŏ���
    int OpenBox;//�󔠂̉摜�ϐ�
    int OpenBox2;
    int g_MenuX;
    int g_KeyFlg;
    int g_BoxNumber;
    int g_NowKey;
    int g_OldKey;
    //�`��Ɋւ��邱�Ƃ�����
    void Draw();
};

};

