#include"DxLib.h"
#include"Player.h"
#include"InputData.h"
#define _USE_MATH_DEFINES
#include <math.h>

Player::Player(){
	g_playerx = 10, g_playery = 400;
	g_hammer_power_gauge = 0;
	g_player_image_type = 0;
	g_block_count = 0;
	g_direction = FALSE;
	if (LoadDivGraph("images/team/human.png", 4, 4, 1, 30, 30, g_player_image) == -1) ;
}


void Player::Hammer(Map map) {
	if (AX != 0 || AY != 0) //左スティックで角度を調整しているとき
	{
		if ((g_ball == FALSE) && (AY >= 0)) //つるはしを投げることのできる状態の時
		{
			g_ball_powerx = (AX / 5);
			g_ball_powery = (AY / 5);
			g_ballx = g_playerx;
			g_bally = g_playery;

			if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B) //角度を調整してBボタンが押されたとき
			{
				g_ball = TRUE; // bボタンが押されたら
				g_hammer_power = (g_hammer_power_gauge / (50 / 3)) + 1;
				if (g_hammer_power == 4)g_hammer_power = 3;
				g_hammer_power_gauge = 0;
				g_hammer_angle = 0;
			}
			else //左スティックで角度を調整しているときつるはしの軌道が描かれる
			{
				while (g_bally < 600)
				{
					g_bally -= (g_ball_powery / 10);
					g_ballx -= (g_ball_powerx / 10);

					g_ball_powery -= 3;

					DrawCircle(g_ballx, g_bally, 3, 0xffffff, false);
				}

				if (g_hammer_power_gauge < 48)g_hammer_power_gauge++; //パワーゲージを動かす
				else g_hammer_power_gauge = 0; //パワーゲージが50たまったら0にする

				DrawBox(g_playerx - 25, g_playery + 20, (g_playerx - 25) + g_hammer_power_gauge, (g_playery + 20) + 20, 0xf00fff, TRUE);
				DrawBox(g_playerx - 25, g_playery + 20, (g_playerx - 25) + 50, (g_playery + 20) + 20, 0xffffff, FALSE);
			}
		}
	}

	if (g_ball == TRUE)
	{
		if ((g_bally / 30) < MAP_HIGHT && (g_bally / 30) >= 0)
		{
			if ((g_ballx / 30) < MAP_WIDTH - 2 && (g_ballx / 30) >= 0)
			{
				if (map.MAP_DATA[g_bally / 30][g_ballx / 30] < 4)
				{
					if (map.MAP_DATA[g_bally / 30][g_ballx / 30] <= 0)map.MAP_DATA[g_bally / 30][g_ballx / 30] = 4;
					else map.MAP_DATA[g_bally / 30][g_ballx / 30] -= g_hammer_power;

					if (map.MAP_DATA[g_bally / 30][g_ballx / 30] < 1)map.MAP_DATA[g_bally / 30][g_ballx / 30] = 4;
					if (map.MAP_DATA[g_bally / 30][g_ballx / 30] <= -1)map.MAP_DATA[g_bally / 30][g_ballx / 30] = 4;
					if (map.MAP_DATA[g_bally / 30][g_ballx / 30] <= -2)map.MAP_DATA[g_bally / 30][g_ballx / 30] = 4;
					if (map.MAP_DATA[g_bally / 30][g_ballx / 30] <= -3)map.MAP_DATA[g_bally / 30][g_ballx / 30] = 4;

					g_block_count++;
				}
			}
		}

		g_bally -= (g_ball_powery / 10); //ボールのy軸の移動する速さ
		g_ballx -= (g_ball_powerx / 10);
		g_ball_powery -= 3;

		g_hammer_angle += 10;
		if (g_hammer_angle > 360)g_hammer_angle = 0;

		if (g_bally > 700)g_ball = FALSE;

	}
}
void Player::Player_Sousa(Map map)
{

	GetJoypadAnalogInput(&AX, &AY, DX_INPUT_PAD1); // 入力状態を取得

	DrawFormatString(0, 30, 0xffffff, "ハンマーパワー %d", g_hammer_power);

	if (AX == 0 && AY == 0)
	{
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT))
		{
			if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT)
			{
				g_direction = FALSE;
				g_player_hit_front = g_playerx + 15;
				g_player_hit_back = g_playerx - 15;

				if (map.MAP_DATA[g_playery / 30][g_player_hit_front / 30] == 4)g_playerx += 2;
				else  g_playerx = ((g_playerx / 30) * 30) + 15;
			}
			if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT)
			{
				g_direction = TRUE;
				g_player_hit_front = g_playerx - 15;
				g_player_hit_back = g_playerx + 15;
				if (map.MAP_DATA[g_playery / 30][g_player_hit_front / 30] == 4)g_playerx -= 2;
				else  g_playerx = ((g_playerx / 30) * 30) + 15;
			}

			g_image_time++;
			if (g_image_time >= 5)
			{
				g_player_image_type++;
				if (g_player_image_type > 3)g_player_image_type = 0;
				g_image_time = 0;
			}
		}
	}

	if (map.MAP_DATA[(g_playery + 15) / 30][g_playerx / 30] == 4)g_playery += 4, DrawFormatString(0, 300, 0xffffff, "aaaa");
	else g_playery = ((g_playery / 30) * 30) + 15;
	//DrawFormatString(0, 45, 0xffffff, "BALLflg = %d", g_ball);
	//DrawRotaGraph(g_playerx, g_playery, 1.0, M_PI / 180 * 0, g_player_image[g_player_image_type], TRUE, g_direction);
	//DrawCircle(g_playerx + (AX / 5), g_playery + (AY / 5), 5, 0xffffff, true);
	//DrawLine(g_playerx, g_playery, g_playerx + (AX / 5), g_playery + (AY / 5), 0xffffff, TRUE);
}

void Player::Draw() const
{
	DrawFormatString(0, 45, 0xffffff, "BALLflg = %d", g_ball);
	DrawRotaGraph(g_playerx, g_playery+120, 1.0, M_PI / 180 * 0, g_player_image[g_player_image_type], TRUE, g_direction);
	DrawCircle(g_playerx + (AX / 5), g_playery + (AY / 5), 5, 0xffffff, true);
	DrawLine(g_playerx, g_playery, g_playerx + (AX / 5), g_playery + (AY / 5), 0xffffff, TRUE);
}