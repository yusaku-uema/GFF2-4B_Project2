#pragma once
#include"main.h"
class GameReward
{
private:
    bool takara;
    bool takara1;
    bool takara2;
public:
    //コンストラクタ
    GameReward();
    //デストラクタ
    //描画以外の更新を実行
    void Update();
    int test=2; //あとで消す
    int OpenBox;//宝箱の画像変数
    int OpenBox2;
    int g_MenuX;
    int g_KeyFlg;
    int g_BoxNumber;
    int g_NowKey;
    int g_OldKey;
    //描画に関することを実装
    void Draw();
};

};

