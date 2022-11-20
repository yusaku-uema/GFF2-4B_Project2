#pragma once

enum PLAYER_STATE
{
	WALK = 0, //�������
	JUMP,    //�W�����v���
	FALL, //�������
	HAMMER,
};

enum PLAYER_DIRECTION
{
	RIGHT = -1, //�������
	LEFT = 1,
};

class Player
{
	
	//�_���̕ʂ̃v���W�F�N�g��������̃v���W�F�N�g�Ɉڍs
	//������Ȃ��ϐ��A�֐��́A�_���ւ�������������
private:
	int AX, AY; //�L�[�̒l
	int g_player_x, g_player_y; //�v���C���[�̍��W
	int g_hammer_x, g_hammer_y;
	int g_hammer_speed_x, g_hammer_speed_y;
	bool g_hammer_flg ;//�n���}�[���g���Ă��邩�ǂ���
	int g_hammer_power;
	int g_direction;
	int g_hammer_angle;
	int g_break_block_count;
	int g_block_count;
	int g_scroll_x; //�X�N���[��
	int g_cursorx, g_cursory;
	int g_move_speed_y;
	int g_player_flg;

	//�L�[����
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

public:
	void Player_Init();
	void Key();
	void Player_Sousa();
	void Hammer();
	void Jump();
	void Walk();
	void Fall();
	//int HitBoxPlayer(int px, int py, ITEM* i);
	int Player_Hit_Front(int a, int b);
	int Player_Hit_Back(int a, int b);
	int Player_Hit_Under(int a, int b);
	int Player_Hit_Up(int a, int b);
};
