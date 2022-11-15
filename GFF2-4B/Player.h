#pragma once
#include"AbstractScene.h"
#include"Map.h"

class Player
{
private:
	int g_player_image[4];
	int AX, AY; //キーの値
	int g_playerx, g_playery; //プレイヤーの座標
	int g_ballx, g_bally;
	int g_ball_powerx, g_ball_powery;
	bool g_ball = FALSE;
	int g_hammer_power;
	int g_hammer_power_gauge;
	int g_player_image_type;
	int g_image_time;
	bool g_direction;
	int g_player_hit_front;
	int g_player_hit_back;
	int g_hammer_angle;
public:
	Player(); //コンストラクタ
	void Draw() const;
	int g_block_count;
	void Player_Sousa(Map map);
	void Hammer(Map map);
};

