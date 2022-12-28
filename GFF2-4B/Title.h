#pragma once
#include"main.h"

class Title 
{
private:
   int g_MenuNumber; //メニューカーソルが今何番なのか。
   int g_MenuY; //カーソルの位置
   int g_KeyFlg; //同じ入力キーか
   int g_OldKey; //前回の入力
   int g_NowKey; //今回の入力キー
   int BGM;

public:
    //コンストラクタ
    Title();
    void Update(); //描画以外
    void Draw(); //描画
    void ChangeScen(); //シーン切り替え


};

