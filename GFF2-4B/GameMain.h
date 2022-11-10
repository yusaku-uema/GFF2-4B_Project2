#pragma once
#include "AbstractScene.h"
#include"Map.h"

class GameMain :
    public AbstractScene
{
private:
    Map map;

public:
    //�R���X�g���N�^
    GameMain();
    //�f�X�g���N�^
    ~GameMain() {}
    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;
    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};

