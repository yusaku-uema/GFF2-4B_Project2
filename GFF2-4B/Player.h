#pragma once
#include"Map.h"

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
private:
	int AX, AY; //�L�[�̒l
	int g_player_x; //�v���C���[���W
	int g_player_y;
	int g_player_flg;
	int g_move_speed_y; //�����X�s�[�h
	int g_hammer_x; //��͂��̍��W
	int g_hammer_y;
	int g_hammer_speed_x; //��͂��̃X�s�[�h
	int g_hammer_speed_y;
	int g_hammer_power; //��͂��̃p���[
	int g_player_image_type; //�v���C���[�̉摜���
	int g_image_time; //�摜�؂�ւ�����
	int g_direction; //����
	int g_hammer_angle; //��͂��̊p�x
	int g_break_block_count; //�u���b�N��j�󂵂���
	int g_block_count; //�u���b�N�̐�
	int g_scroll_x; //�X�N���[��
	int g_cursor_x; //�J�[�\�����W
	int g_cursor_y; //�J�[�\�����W
	bool g_hammer_flg; //��͂����g���Ă��邩
	
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
//�摜
	int g_player_image[4]; //�v���C���[
	int g_hammer_image; //��͂�
	int g_cursor_image; //�J�[�\��
	int g_haikei_image; //�w�i�摜

public:

	Player();
	void Player_Init(); //�ăX�^�[�g������
	void Key(); //�L�[����
	void Player_operation(); //�v���C���[����
	void Hammer(); //�������͂�
	void Jump(); //�v���C���[�W�����v
	void Walk(); //�v���C���[��������
	//int HitBoxPlayer(int px, int py, ITEM* i);
	int Player_Hit_Front(int a, int b);
	int Player_Hit_Back(int a, int b);
	int Player_Hit_Under(int a, int b);
	int Player_Hit_Up(int a, int b);
};