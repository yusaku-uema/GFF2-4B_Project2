#pragma once
#include "AbstractScene.h"
class GameReward :
	public AbstractScene
{
private:
   
public:
    //コンストラクタ
    GameReward();
    //デストラクタ
    //描画以外の更新を実行
    AbstractScene* Update() override;
    int OpenBox;//宝箱の画像変数
    int OpenBox2;
    int g_MenuX;
    int g_KeyFlg;
    int g_BoxNumber;
    int g_NowKey;
    int g_OldKey;
    //描画に関することを実装
    void Draw() const override;
};

