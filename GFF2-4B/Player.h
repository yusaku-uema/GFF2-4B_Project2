#pragma once
#include"Map.h"

enum PLAYER_STATE
{
	WALK = 0, //歩き状態
	JUMP,    //ジャンプ状態
	FALL, //落下状態
	HAMMER,
};

enum PLAYER_DIRECTION
{
	RIGHT = -1, //歩き状態
	LEFT = 1,
};

class Player
{
private:
	int AX, AY; //キーの値
	int g_player_x; //プレイヤー座標
	int g_player_y;
	int g_player_flg;
	int g_move_speed_y; //動くスピード
	int g_hammer_x; //つるはしの座標
	int g_hammer_y;
	int g_hammer_speed_x; //つるはしのスピード
	int g_hammer_speed_y;
	int g_hammer_power; //つるはしのパワー
	int g_player_image_type; //プレイヤーの画像種類
	int g_image_time; //画像切り替え時間
	int g_direction; //方向
	int g_hammer_angle; //つるはしの角度
	int g_break_block_count; //ブロックを破壊した数
	int g_block_count; //ブロックの数
	int g_scroll_x; //スクロール
	int g_cursor_x; //カーソル座標
	int g_cursor_y; //カーソル座標
	bool g_hammer_flg; //つるはしが使われているか
	
	bool g_bkey_flg;
	bool g_akey_flg;
	bool g_xkey_flg;
	bool g_lkey_flg;
	bool g_rkey_flg;
	bool g_old_akey_flg;
	bool g_old_bkey_flg;
	bool g_old_xkey_flg;
	bool g_old_lkey_flg;
	bool g_old_rkey_flg;
	bool g_upkey_flg;
	bool g_downkey_flg;
	bool g_rightkey_flg;
	bool g_leftkey_flg;
//画像
	int g_player_image[4]; //プレイヤー
	int g_hammer_image; //つるはし
	int g_cursor_image; //カーソル
	int g_haikei_image; //背景画像

public:

	Player();
	void Player_Init(); //再スタート初期化
	void Key(); //キー入力
	void Player_operation(); //プレイヤー操作
	void Hammer(); //投げるつるはし
	void Jump(); //プレイヤージャンプ
	void Walk(); //プレイヤー歩く処理
	//int HitBoxPlayer(int px, int py, ITEM* i);
	int Player_Hit_Front(int a, int b);
	int Player_Hit_Back(int a, int b);
	int Player_Hit_Under(int a, int b);
	int Player_Hit_Up(int a, int b);
};