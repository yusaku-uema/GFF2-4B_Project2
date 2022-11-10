#pragma once
#include"AbstractScene.h"

class Player
{
private:
	int g_OldKey; //前回の入力キー
	int g_NowKey; //今回の入力キー
	int g_PlayerX; //プレイヤー座標X
	int g_PlayerY; //プレイヤー座標Y
	int g_Movement_speed; //プレイヤー移動スピード
	int g_Playerimage[4]; //プレイヤー画像
	int image_number; //プレイヤー画像切り替えカウント
	int image_Type; //プレイヤー画像要素数指定
	bool g_direction; //左を向いているのかのフラグ

public:
	Player(); //コンストラクタ
	void Draw() const;
	void Movement(); //プレイヤー移動処理
	void jump(); //プレイヤーのジャンプ処理
};

