#pragma once
#include "AdstractScene.h"


class Help :public AdstractScene
{
private:

public:
    //コンストラクタ
    Help();
    //デストラクタ
    ~Help() {}
    //描画以外の更新を実行
    void  Update() override;
    //描画に関することを実装
    void Draw() const override;
    //シーン切り替え
    AdstractScene* ChangeScene();
};

