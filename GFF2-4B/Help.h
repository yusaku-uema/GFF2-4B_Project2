#pragma once
#include "AdstractScene.h"


class Help :public AdstractScene
{
private:

public:
    //�R���X�g���N�^
    Help();
    //�f�X�g���N�^
    ~Help() {}
    //�`��ȊO�̍X�V�����s
    void  Update() override;
    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
    //�V�[���؂�ւ�
    AdstractScene* ChangeScene();
};

