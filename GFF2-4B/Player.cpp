#include"DxLib.h"
#include"Player.h"
#define _USE_MATH_DEFINES
#include <math.h>

Player::Player(){
	g_Movement_speed = 1;
	g_NowKey = 0;
	g_OldKey = 0;
	g_PlayerX = 200;
	g_PlayerY = 200;
	g_PlayerVX = 0;
	g_PlayerVY = 0;
	image_number = 0;
	image_Type = 1;
	g_direction = FALSE;
	g_PlayerJump = FALSE;
	g_twostagejump = FALSE;
	LoadDivGraph("images/Player/human.png", 4, 4, 1, 30, 30, g_Playerimage);
}


void Player::Movement() {
	//g_NowKey=GetJoypadInputState(DX_INPUT_PAD1); //入力キー保存
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) g_PlayerX = g_PlayerX - g_Movement_speed, ++image_number , g_direction = TRUE; //左
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) g_PlayerX = g_PlayerX + g_Movement_speed, ++image_number, g_direction = FALSE; //右
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A) g_PlayerJump = TRUE, Player::jump();
	if (image_number > 11) {
		if (image_number % 9 == 0)++image_Type;
	}
	if (image_Type >= 4) image_Type = 0, image_number = 0;
	
		Player::jump();
}

void Player::Draw() const
{
	//DrawGraph(g_PlayerX, g_PlayerY, g_Playerimage[image_Type], TRUE);
	DrawRotaGraph(200 + (g_PlayerX + 15), g_PlayerY + 30, 1.0, M_PI / 180 * 0, g_Playerimage[image_Type], TRUE, g_direction);
}

void Player::jump() {
	if (g_twostagejump == FALSE) {
		g_PlayerVY = -5; //↑にジャンプ速度
		g_twostagejump = TRUE;
	}
	if (g_PlayerJump == TRUE && g_PlayerVY < 25) {
		g_PlayerY = g_PlayerY + g_PlayerVY;
		g_PlayerVY = g_PlayerVY + 0.1;  //重力加速
	}
	if (g_PlayerVY == 0) {
		g_PlayerJump = FALSE;
		g_twostagejump = FALSE;
		g_PlayerVY = 0;
	}

}