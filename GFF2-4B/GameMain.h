#pragma once
#include "AdstractScene.h"
#include"Map.h"
#include"UI.h"
#include"Ranking.h"

class GameMain :public AdstractScene
{
private:
   /* Map map;
    UI ui;
    Player player;
    RANKING ranking;*/

public:
    //�R���X�g���N�^
    GameMain();
    //�`��ȊO�̍X�V�����s
   void Update() override;
    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
    //�V�[���؂�ւ�
    AdstractScene* ChangeScene();
};

