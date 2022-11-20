#pragma once
#include "AdstractScene.h"

class Title :public AdstractScene
{
private:
   int g_MenuNumber; //メニューカーソルが今何番なのか。
   int g_MenuY; //カーソルの位置
   int g_KeyFlg; //同じ入力キーか
   int g_OldKey; //前回の入力
   int g_NowKey; //今回の入力キー
   int g_TitleSE; //決定SE
   int g_TitleBGM; //タイトルに流れるBGM
   int g_Titleimage; //タイトル背景

public:
    //コンストラクタ
    Title();
    //描画以外の更新を実行
     void Update() override;
    //描画に関することを実装
    void Draw() const override;
    //シーン切り替え
    AdstractScene* ChangeScene();

};

