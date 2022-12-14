#pragma once
#include"main.h"

class GameMain
{
private:

	int g_game_state;
	int g_stage;

	int g_stage_select_image;
	int g_blowing_images; //�����o���摜
	int g_NumberImage[10]; //�����摜
	int g_NumberImage1[10]; //
	int TmpScore; //�X�R�A�ی�
	int TimeLimitImages; //����
	int LimitImages; //��������
	int ScoreImages; //�X�R�A����
	int TimeLimit; //�c�莞��
	int TmpTime; //�c�莞�ԕی�
	int fps_cunt;
	int BreakBGM;

	int AX, AY; //�L�[�̒l
	int BX, BY;
	int g_old_BX_flg, g_old_BY_flg;
	int g_old_AX_flg, g_old_AY_flg;

	int g_player_x, g_player_y; //�v���C���[�̍��W
	int g_hammer_angle_direction;
	int g_hammer_x, g_hammer_y;
	int g_old_hammer_x, g_old_hammer_y;
	int g_hammer_orbit_x, g_hammer_orbit_y;
	bool g_hit_hammer_flg;
	int g_hammer_flg;//�n���}�[���g���Ă��邩�ǂ���
	
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
		WALK = 0, //�������
		JUMP,    //�W�����v���
		FALL, //�������
		DIE, //���S
	};

	enum BOM_STATE
	{
		NONE = 0, //�Ȃ�
		NOMAL,    //���ʏ��
		ANGRY, //�{����
		FLY, //�����Ă���
	};

	enum PLAYER_DIRECTION
	{
		RIGHT = -1, //�������
		LEFT = 1,
	};

	enum HAMMER_STATE
	{
		HAMMER_NONE = 0, //�g���ĂȂ�
		HAMMER_CURSOR,    //�J�[�\���̃u���b�N���@��
		HAMMER_FLY, //�����Ă�
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
	void Block_Collision(int a, int b, bool c); //��͂��𓊂������̓����蔻��
	void Draw();
	void Bom();

	int Player_Hit_Front(int a, int b);
	int Player_Hit_Back(int a, int b);
	int Player_Hit_Under(int a, int b);
	int Player_Hit_Up(int a, int b);
	void GameMain_Init(); //������
	void Update(); //�`��ȊO�̍X�V�����s
	void Time(); //��������
	void Clear(); //�Q�[���N���A
	int Get_MapData(int y, int x);

	void Draw_Stage_Select();
	void Update_Stage_Select();
	void Stage_Select_Init();

	unsigned int ITEM_DATA[MAP_HIGHT][MAP_WIDTH];
	unsigned int MAP_DATA_INIT[MAP_HIGHT][MAP_WIDTH];
	unsigned int MAP_DATA[MAP_HIGHT][MAP_WIDTH];
	unsigned int ITEM_DATA_INIT[MAP_HIGHT][MAP_WIDTH];
};