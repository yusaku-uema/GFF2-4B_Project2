#pragma once
#include"AbstractScene.h"

class Player
{
private:
	int g_OldKey; //�O��̓��̓L�[
	int g_NowKey; //����̓��̓L�[
	int g_PlayerX; //�v���C���[���WX
	int g_PlayerY; //�v���C���[���WY
	int g_PlayerVX; //�v���C���[�W�����v���WX
	float g_PlayerVY; //�v���C���[�W�����v���WY
	int g_Movement_speed; //�v���C���[�ړ��X�s�[�h
	int g_Playerimage[4]; //�v���C���[�摜
	int image_number; //�v���C���[�摜�؂�ւ��J�E���g
	int image_Type; //�v���C���[�摜�v�f���w��
	bool g_direction; //���������Ă���̂��̃t���O
	bool g_PlayerJump; //�v���C���[���W�����v���Ȃ̂�
	bool g_twostagejump; //��i�W�����v�h�~�t���O
public:
	Player(); //�R���X�g���N�^
	void Draw() const;
	void Movement(); //�v���C���[�ړ�����
	void jump(); //�v���C���[�̃W�����v����
};

