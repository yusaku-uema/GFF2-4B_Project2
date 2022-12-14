#pragma once
#include"main.h"

class GameMain
{
private:

	int g_game_state;
	int g_stage;

	int g_stage_select_image;
	int g_blowing_images; //吹き出し画像
	int g_NumberImage[10]; //数字画像
	int g_NumberImage1[10]; //
	int TmpScore; //スコア保護
	int TimeLimitImages; //文字
	int LimitImages; //制限時間
	int ScoreImages; //スコア文字
	int TimeLimit; //残り時間
	int TmpTime; //残り時間保護
	int fps_cunt;
	int BreakBGM;

	int AX, AY; //キーの値
	int BX, BY;
	int g_old_BX_flg, g_old_BY_flg;
	int g_old_AX_flg, g_old_AY_flg;

	int g_player_x, g_player_y; //プレイヤーの座標
	int g_hammer_angle_direction;
	int g_hammer_x, g_hammer_y;
	int g_old_hammer_x, g_old_hammer_y;
	int g_hammer_orbit_x, g_hammer_orbit_y;
	bool g_hit_hammer_flg;
	int g_hammer_flg;//ハンマーが使われているかどうか
	
	int g_player_image_type;
	int g_image_time;

	int g_direction;

	int g_hammer_angle;
	int g_break_block_count;
	int g_block_count;

	int g_scroll_x;

	int g_cursorx, g_cursory;
	int g_old_cursor_BX, g_old_cursor_BY;
	bool g_cursor_flg;
	int g_cursor_key_time;

	int g_item_selection;

	int g_bag_count;
	int g_key_count;
	int g_score;

	int g_chara_life;

	int g_bom_count;

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
	bool g_old_rightkey_flg;
	bool g_old_leftkey_flg;
	bool g_old_startkey_flg;
	bool g_upkey_flg;
	bool g_downkey_flg;
	bool g_rightkey_flg;
	bool g_leftkey_flg;
	bool g_startkey_flg;

	bool g_checkpoint_flg;
	bool g_game_stop;

	int g_move_speed_y;

	int g_player_flg;

	int Timer;
	int AnimKira[3];
	int num;
	bool Animflg;

	enum PLAYER_STATE
	{
		WALK = 0, //歩き状態
		JUMP,    //ジャンプ状態
		FALL, //落下状態
		DIE, //死亡
	};

	enum BOM_STATE
	{
		NONE = 0, //ない
		NOMAL,    //普通状態
		ANGRY, //怒り状態
		FLY, //投げてる状態
	};

	enum PLAYER_DIRECTION
	{
		RIGHT = -1, //歩き状態
		LEFT = 1,
	};

	enum HAMMER_STATE
	{
		HAMMER_NONE = 0, //使ってない
		HAMMER_CURSOR,    //カーソルのブロックを掘る
		HAMMER_FLY, //投げてる
	};

	struct ITEM {
		bool flg;
		int x;
		int y;
		int point;
		int type;
	};
	struct ITEM g_item[10];

	struct BOM {
		int flg;
		int x;
		int y;
		int time;
		bool hit_flg;
		int orbit_x;
		int orbit_y;
		int angle_direction;
		int angle;
	};
	struct BOM g_bom[10];



public:

	void Key();
	void Player_Sousa();
	void Game_Init();
	void Stage();
	void Hammer();
	void Jump();
	void Walk();
	void Fall();
	void Item();
	int HitBoxPlayer(int px, int py, int ex, int ey, int psize,int esize, bool a);
	void Ui();
	void Block_Collision(int a, int b, bool c); //つるはしを投げた時の当たり判定
	void Draw();
	void Bom();

	int Player_Hit_Front(int a, int b);
	int Player_Hit_Back(int a, int b);
	int Player_Hit_Under(int a, int b);
	int Player_Hit_Up(int a, int b);
	void GameMain_Init(); //初期化
	void Update(); //描画以外の更新を実行
	void Time(); //制限時間
	void Clear(); //ゲームクリア
	int Get_MapData(int y, int x);

	void Draw_Stage_Select();
	void Update_Stage_Select();
	void Stage_Select_Init();

	unsigned int ITEM_DATA[MAP_HIGHT][MAP_WIDTH];
	unsigned int MAP_DATA_INIT[MAP_HIGHT][MAP_WIDTH];
	unsigned int MAP_DATA[MAP_HIGHT][MAP_WIDTH];
	unsigned int ITEM_DATA_INIT[MAP_HIGHT][MAP_WIDTH];
};