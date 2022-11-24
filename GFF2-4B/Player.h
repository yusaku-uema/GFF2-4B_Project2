//#pragma once
//
//enum PLAYER_STATE
//{
//	WALK = 0, //歩き状態
//	JUMP,    //ジャンプ状態
//	FALL, //落下状態
//	HAMMER,
//};
//
//enum PLAYER_DIRECTION
//{
//	RIGHT = -1, //歩き状態
//	LEFT = 1,
//};
//
//class Player
//{
//	
//	//神里の別のプロジェクトをこちらのプロジェクトに移行
//	//分からない変数、関数は、神里へお聞きください
//private:
//	int AX, AY; //キーの値
//	int g_player_x, g_player_y; //プレイヤーの座標
//	int g_hammer_x, g_hammer_y;
//	int g_hammer_speed_x, g_hammer_speed_y;
//	int g_image_time = 0;
//	int g_player_image_type;
//	bool g_item_flg;
//	bool g_hammer_flg ;//ハンマーが使われているかどうか
//	int g_hammer_power;
//	int g_direction;
//	int g_hammer_angle;
//	int g_break_block_count;
//	int g_block_count;
//	int g_scroll_x; //スクロール
//	int g_cursorx, g_cursory;
//	int g_move_speed_y;
//	int g_player_flg;
//
//	//キー入力
//	bool g_bkey_flg;
//	bool g_akey_flg;
//	bool g_xkey_flg;
//	bool g_lkey_flg;
//	bool g_rkey_flg;
//	bool g_old_akey_flg;
//	bool g_old_bkey_flg;
//	bool g_old_xkey_flg;
//	bool g_old_lkey_flg;
//	bool g_old_rkey_flg;
//	bool g_upkey_flg;
//	bool g_downkey_flg;
//	bool g_rightkey_flg;
//	bool g_leftkey_flg;
//
//	//プレイヤーUI
//	int g_item_selection;
//
//	struct ITEM {
//		bool flg;
//		int x;
//		int y;
//		int point;
//		int type;
//	};
//	struct ITEM g_item[10];
//
//public:
//	void Player_Init();
//	void Key();
//	void Player_Sousa();
//	void Draw_Item();
//	void Hammer();
//	void Jump();
//	void Walk();
//	void Fall();
//	void Item();
//	void Stage();
//	void UI();
//	int HitBoxPlayer(int px, int py, ITEM* i);
//	int Player_Hit_Front(int a, int b);
//	int Player_Hit_Back(int a, int b);
//	int Player_Hit_Under(int a, int b);
//	int Player_Hit_Up(int a, int b);
//};
