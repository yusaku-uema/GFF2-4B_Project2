#pragma once
#include "AbstractScene.h"
#include"Map.h"
#include"UI.h"

class GameMain :
    public AbstractScene
{
private:
    Map map;
    UI ui;

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

