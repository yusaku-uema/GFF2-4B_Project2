#pragma once
#include"AbstractScene.h"
#include"KeyConfig.h"

class KeyConfigScene :public AbstractScene {
private:
    KeyConfig keyconfig;
public:
    int i;
    int DrawY;
    int InputWait;
    int g_KeyCongifGameState;

    //�R���X�g���N�^
    KeyConfigScene(int GameState);
    //�f�X�g���N�^
    ~KeyConfigScene() {}
    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;
    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

};