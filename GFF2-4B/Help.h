#pragma once
#include"main.h"

class Help
{
private:
public:
    //コンストラクタ
    Help();
    //デストラクタ
    ~Help() {}
    //描画以外の更新を実行
    void  Update();
    //描画に関することを実装
    void Draw();
    //シーン切り替え
    void  ChangeScene();
    /* int g_image;*/
};

