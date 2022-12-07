#pragma once
#include"KeyConfig.h"

class KeyConfigScene  {
public:
    KeyConfig keyconfig;
public:
    int InputWait;
    int g_KeyCongifGameState;

    //コンストラクタ
    KeyConfigScene();
    //デストラクタ
    ~KeyConfigScene() {}
    
    void Update() ;
    

};