#include"DxLib.h"
#include "GameMain.h"
#include"main.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"Player.h"

Player player;

/***********************************************
*  ����������
************************************************/
void GameMain::GameMain_Init()
{
	player.Player_Init();
	SetGameState(2); //�Q�[�����C���ڍs
}


/***********************************************
*  �Q�[������
************************************************/
void GameMain::Update()
{
	player.Key();
	player.Draw_Item();
	player.Stage();
	player.Player_Sousa(); //���@�̑���
	player.UI();
}

/***********************************************
* �V�[���؂�ւ�
************************************************/
void GameMain::Draw() 
{
	
}
