#pragma once
#include "main.h"

class Credit
{
private:
	int g_KeyFlg; //同じ入力キーか
	int g_OldKey; //前回の入力
	int g_NowKey; //今回の入力キー
public:
	void Draw(); //描画
	void ChangeScen(); //シーン切り替え

};

