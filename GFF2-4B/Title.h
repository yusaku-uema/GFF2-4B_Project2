#pragma once
#include "AbstractScene.h"
#include"Ranking.h"

class Title :
    public AbstractScene
{
private:
   int g_MenuNumber; //メニューカーソルが今何番なのか。
   int g_MenuY; //カーソルの位置
   int g_KeyFlg; //同じ入力キーか
   int g_OldKey; //前回の入力
   int g_NowKey; //今回の入力キー
   int g_TitleSE; //決定SE
   int g_TitleBGM; //タイトルに流れるBGM

   //Ranking ranking; //後で消す

public:
    //コンストラクタ
    Title();
    //デストラクタ
    //描画以外の更新を実行
    AbstractScene* Update() override;
    //描画に関することを実装
    void Draw() const override;
};

