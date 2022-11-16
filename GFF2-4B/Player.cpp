#include"Player.h"
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"stdlib.h"

Player::Player()
{
	g_player_x = 30, g_player_y = 670;
	g_hammer_power = 0;
	g_scroll_x = 0;
	g_block_count = 0;
	g_item_selection = 0;

	g_player_image_type = 0;

	g_direction = RIGHT;
	g_bkey_flg = FALSE;
	g_akey_flg = FALSE;
	g_xkey_flg = FALSE;
	g_lkey_flg = FALSE;
	g_rkey_flg = FALSE;
	g_player_flg = WALK;
	g_break_block_count = 0;

}