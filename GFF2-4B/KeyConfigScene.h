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

    //コンストラクタ
    KeyConfigScene(int GameState);
    //デストラクタ
    ~KeyConfigScene() {}
    //描画以外の更新を実行
    AbstractScene* Update() override;
    //描画に関することを実装
    void Draw() const override;

};