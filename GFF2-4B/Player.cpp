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
	//g_NowKey=GetJoypadInputState(DX_INPUT_PAD1); //入力キー保存
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) --g_PlayerX; //左
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) ++g_PlayerX; //右
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) --g_PlayerY; //上
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) ++g_PlayerY; //下
}

void Player::Draw() const
{
	DrawGraph(g_PlayerX, g_PlayerY, g_Playerimage[image_number], TRUE);
}