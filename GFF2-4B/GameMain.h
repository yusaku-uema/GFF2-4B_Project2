#pragma once
#include"main.h"
#include"KeyConfig.h"


class GameMain
{
private:
	KeyConfig keyconfig;

	int TimeLimit;
	int fps_cunt;
	int BreakBGM;
	bool g_player_move_flg;

	int AX, AY; //�L�[�̒l
	int BX, BY;
	int g_old_BX_flg, g_old_BY_flg;
	int g_old_AX_flg, g_old_AY_flg;

	int g_player_x, g_player_y; //�v���C���[�̍��W

	int g_hammer_x, g_hammer_y;
	int g_hammer_orbit_x, g_hammer_orbit_y;

	bool g_hammer_flg = FALSE;//�n���}�[���g���Ă��邩�ǂ���
	bool g_item_flg = FALSE;

	int g_player_image_type;
	int g_image_time;

	int g_direction;

	int g_hammer_angle;
	int g_break_block_count;
	int g_block_count;

	int g_scroll_x;

	int g_cursorx, g_cursory;

	int g_item_selection;

	int g_hukuro_count;
	int g_kagi_count;
	int g_score;
	int g_score2;
	int g_score3;
	int g_score4;

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
	bool g_upkey_flg;
	bool g_downkey_flg;
	bool g_rightkey_flg;
	bool g_leftkey_flg;
	bool g_titen_flg;
	int g_move_speed_y;

	int g_player_flg;


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

	int Player_Hit_Front(int a, int b);
	int Player_Hit_Back(int a, int b);
	int Player_Hit_Under(int a, int b);
	int Player_Hit_Up(int a, int b);
	void GameMain_Init(); //������
	void Update(); //�`��ȊO�̍X�V�����s
	void Time(); //��������
	void Clear(); //�Q�[���N���A
	int Get_MapData(int y, int x);

	unsigned int ITEM_DATA[MAP_HIGHT][MAP_WIDTH];
	unsigned int MAP_DATA_INIT[MAP_HIGHT][MAP_WIDTH];
	unsigned int MAP_DATA[MAP_HIGHT][MAP_WIDTH];
	unsigned int ITEM_DATA_INIT[MAP_HIGHT][MAP_WIDTH];

};