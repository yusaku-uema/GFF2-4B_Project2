#pragma once
#include"KeyConfig.h"

class KeyConfigScene  {
public:
    KeyConfig keyconfig;
public:
    int InputWait;
    int g_KeyCongifGameState;

    //�R���X�g���N�^
    KeyConfigScene();
    //�f�X�g���N�^
    ~KeyConfigScene() {}
    
    void Update() ;
    

};