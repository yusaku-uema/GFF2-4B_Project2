#include"DxLib.h"
#include"Player.h"
#define _USE_MATH_DEFINES
#include <math.h>

Player::Player(){
	g_Movement_speed = 0;
	g_NowKey = 0;
	g_OldKey = 0;
	g_PlayerX = 200;
	g_PlayerY = 200;
	image_number = 0;
	image_Type = 0;
	g_direction = FALSE;
	LoadDivGraph("images/Player/human.png", 4, 4, 1, 30, 30, g_Playerimage);
}


void Player::Movement() {
	//g_NowKey=GetJoypadInputState(DX_INPUT_PAD1); //“ü—ÍƒL[•Û‘¶
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) --g_PlayerX, ++image_number , g_direction = TRUE; //¶
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) ++g_PlayerX, ++image_number, g_direction = FALSE; //‰E

	if (image_number > 11) {
		if (image_number % 7 == 0)image_Type++;
	}
	if (image_Type >= 4) image_Type = 0, image_number = 0;
}

void Player::Draw() const
{
	//DrawGraph(g_PlayerX, g_PlayerY, g_Playerimage[image_Type], TRUE);
	DrawRotaGraph(200 + (g_PlayerX + 15), g_PlayerY + 30, 1.0, M_PI / 180 * 0, g_Playerimage[image_Type], TRUE, g_direction);
}