#include"DxLib.h"
#include"Player.h"

Player::Player(){
	g_Movement_speed = 0;
	g_NowKey = 0;
	g_OldKey = 0;
	g_PlayerX = 200;
	g_PlayerY = 200;
	image_number = 0;
	LoadDivGraph("images/Player/human.png", 4, 4, 1, 30, 30, g_Playerimage);
}


void Player::Movement() {
	//g_NowKey=GetJoypadInputState(DX_INPUT_PAD1); //ì¸óÕÉLÅ[ï€ë∂
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) --g_PlayerX; //ç∂
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) ++g_PlayerX; //âE
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) --g_PlayerY; //è„
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) ++g_PlayerY; //â∫
}

void Player::Draw() const
{
	DrawGraph(g_PlayerX, g_PlayerY, g_Playerimage[image_number], TRUE);
}