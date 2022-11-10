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
    //コンストラクタ
    GameMain();
    //デストラクタ
    ~GameMain() {}
    //描画以外の更新を実行
    AbstractScene* Update() override;
    //描画に関することを実装
    void Draw() const override;
};

