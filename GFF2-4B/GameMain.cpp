#include"DxLib.h"
#include "GameMain.h"
#include"main.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"Player.h"



/***********************************************
*  ゲーム処理
************************************************/
void GameMain::Update()
{
	Key();
	Draw_Item();
	Stage();
	Player_Sousa(); //自機の操作
	Bom();
	Ui();
	//Time();
	//Clear();
}


/***********************************************
*  初期化処理
************************************************/
void GameMain::GameMain_Init()
{

	g_player_x = 30, g_player_y = 550;
	BreakBGM = LoadSoundMem("BGM/Onoma-Pop01-3(Dry).mp3");//破壊音BGM
	g_scroll_x = 0;
	g_block_count = 99;
	g_hukuro_count = 0;
	g_kagi_count = 0;
	g_item_selection = 0;
	g_score = 0;
	g_score2 = 0;
	g_score3 = 0;
	g_score4 = 0;
	fps_cunt = 0;
	TimeLimit = 200;//制限時間
	g_player_image_type = 0;
	g_walk_start_time = 0;
	g_direction = RIGHT;
	g_player_flg = WALK;
	g_break_block_count = 0;
	g_bom_count = 3;
	g_chara_life = 3;


	//ファイル
	FILE* fp = NULL;
	if (fopen_s(&fp, "data/item2.txt", "r") != 0)
	{
		throw "Data/item1.txt";
	}
	//アイテムデータ
	for (int i = 0; i < MAP_HIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			fscanf_s(fp, "%2d", &ITEM_DATA[i][j]);
		}
	}
	fclose(fp);
	fp = NULL;

	if (fopen_s(&fp, "data/map2.txt", "r") != 0)
	{
		throw "Data/map1.txt";
	}
	//アイテムデータ
	for (int i = 0; i < MAP_HIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			fscanf_s(fp, "%2d", &MAP_DATA_INIT[i][j]);
		}
	}
	fclose(fp);
	fp = NULL;

	for (int i = 0; i < 10; i++)
	{
		g_item[i].x = 0;
		g_item[i].y = 0;
		g_item[i].point = 0;
		g_item[i].flg = FALSE;
		g_item[i].type = 0;

		g_bom[i].flg = NONE;
		g_bom[i].x = 0;
		g_bom[i].y = 0;
		g_bom[i].time = 300;
	}

	int g_bom_counnt = 0;
	int g_item_count = 0;

	for (int i = 0; i < MAP_HIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (ITEM_DATA[i][j] > 0)
			{
				if (ITEM_DATA[i][j] == 1 || ITEM_DATA[i][j] == 2)
				{
					g_item[g_item_count].x = j * 30;
					g_item[g_item_count].y = i * 30;
					g_item[g_item_count].point = 100;
					g_item[g_item_count].type = ITEM_DATA[i][j];
					g_item[g_item_count].flg = TRUE;
					g_item_count++;
				}
				else
				{
					g_bom[g_bom_counnt].x = j * 30;
					g_bom[g_bom_counnt].y = i * 30;
					g_bom[g_bom_counnt].flg = NOMAL;
					g_bom_counnt++;
				}
				
			}
			MAP_DATA[i][j] = MAP_DATA_INIT[i][j];
			if (MAP_DATA[i][j] == 3)MAP_DATA[i][j] = GetRand(2) + 1;
		}
	}

	SetGameState(2); //ゲームメイン移行
}





/***********************************************
* 制限時間
************************************************/
void GameMain::Time() 
{
	if (++fps_cunt % 60 == 0) {
		--TimeLimit;
	}
	if (TimeLimit <= 0)
	{
		SetGameState(4);
	}
	/*DrawFormatString(500, 500, 0xffffff, "%d", g_player_x);
	DrawFormatString(570, 500, 0xffffff, "%d", g_player_y);*/
	
}

void GameMain::Clear()
{
	if (g_player_x >= 3160 && g_player_y >=255)
	{
		SetGameState(3);
	}
}


void GameMain:: Key()
{
	g_old_BX_flg = BX;
	g_old_BY_flg = BY;
	g_old_AX_flg = AX;
	g_old_AY_flg = AY;
	GetJoypadAnalogInputRight(&BX, &BY, DX_INPUT_PAD1);
	GetJoypadAnalogInput(&AX, &AY, DX_INPUT_PAD1); // 入力状態を取得
	g_old_bkey_flg = g_bkey_flg;
	g_old_akey_flg = g_akey_flg;
	g_old_xkey_flg = g_xkey_flg;
	g_old_lkey_flg = g_lkey_flg;
	g_old_rkey_flg = g_rkey_flg;
	g_old_rightkey_flg = g_rightkey_flg;
	g_old_leftkey_flg = g_leftkey_flg;

	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B))g_bkey_flg = TRUE;
	else g_bkey_flg = FALSE;
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A))g_akey_flg = TRUE;
	else g_akey_flg = FALSE;
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_C))g_xkey_flg = TRUE;
	else g_xkey_flg = FALSE;
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT))g_rightkey_flg = TRUE;
	else g_rightkey_flg = FALSE;
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT))g_leftkey_flg = TRUE;
	else g_leftkey_flg = FALSE;
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP))g_upkey_flg = TRUE;
	else g_upkey_flg = FALSE;
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN))g_downkey_flg = TRUE;
	else g_downkey_flg = FALSE;
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5)g_lkey_flg = TRUE;
	else g_lkey_flg = FALSE;
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_6)g_rkey_flg = TRUE;
	else g_rkey_flg = FALSE;

}

void GameMain::Ui()
{
	DrawBox(0, 630, 1280, 720, 0x000000, TRUE); //UIの枠
	DrawBox(0, 630, 1280, 720, 0xFFFFFF, FALSE);//UIの枠
	DrawBox(0, 0, 1280, 630, 0xFFFFFF, FALSE);//UIの枠
	g_score = (g_break_block_count * 5) + (g_hukuro_count * 300) + (g_kagi_count * 1000);
	g_score2 = (g_break_block_count * 5) + (g_hukuro_count * 300) + (g_kagi_count * 1000) + ((TimeLimit / 10) * 100);
	g_score3 = ((TimeLimit / 10) * 100) + (g_hukuro_count * 300) + (g_kagi_count * 1000);
	g_score4 = (g_break_block_count * 5) + (g_hukuro_count * 300) + (g_kagi_count * 1000);

	DrawFormatString(15, 634, 0xffffff, "Score");
	DrawFormatString(200, 634, 0xffffff, "TimeLimit");
	if (g_chara_life == 3)
	{
		DrawGraph(1000, 630, GetArrayImages(Life_Images, 0), TRUE);
		DrawGraph(1060, 630, GetArrayImages(Life_Images, 0), TRUE);
		DrawGraph(1120, 630, GetArrayImages(Life_Images, 0), TRUE);
	}
	else if(g_chara_life ==2)
	{
		DrawGraph(1000, 630, GetArrayImages(Life_Images, 0), TRUE);
		DrawGraph(1060, 630, GetArrayImages(Life_Images, 0), TRUE);
	}
	else if (g_chara_life == 1)
	{
		DrawGraph(1000, 630, GetArrayImages(Life_Images, 0), TRUE);
	}

	SetFontSize(50);
	DrawFormatString(200, 665, 0xffffff, "%d", TimeLimit);
	DrawFormatString(15, 665, 0xffffff, "%06d", g_score);
	int a = (1280 - (110 * (g_stage_item_quantity - 1))) / 2;
	float size[3];
	DrawFormatString(100, 0, 0xffffff, "%d = block_count, %d = break block", g_block_count, g_break_block_count);
	DrawFormatString(100, 60, 0xffffff, "アイテムとブロック　%d", g_score);
	DrawFormatString(100, 120, 0xffffff, "アイテムとブロックと時間　%d", g_score2);
	DrawFormatString(100, 180, 0xffffff, "アイテムと時間　%d", g_score3);
	DrawFormatString(100, 240, 0xffffff, "アイテムとブロック　%d", g_score4);
	SetFontSize(30);


	for (int i = 0; i < 3; i++)
	{
		size[i] = 0.6;
		if (g_item_selection == i)size[i] = 0.8;
		DrawRotaGraph(a + (110 * i), 675, size[i], M_PI / 180 * 0, GetArrayImages(Item_cursor,i), TRUE, FALSE);
		if ((g_item_selection == 1 && i == 1) || (g_item_selection == 2 && i == 2))
		{
			DrawCircle(a + (110 * i) + 37, 699, 15, 0x000000, TRUE);
			DrawCircle(a + (110 * i) + 37, 699, 15, 0xFFFFFF, FALSE);
			if (g_item_selection == 1 && i == 1)DrawFormatString(a + (110 * i) + 30, 685, 0xffffff, "%d", g_block_count);
			else DrawFormatString(a + (110 * i) + 30, 685, 0xffffff, "%d", g_bom_count);
		}
	}
}

void  GameMain::Stage()
{
	for (int i = 0; i < MAP_HIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (MAP_DATA[i][j] != 0)
			{
				DrawGraph((30 * j) - g_scroll_x, 30 * i, GetArrayImages(Block_Images, MAP_DATA[i][j]), TRUE);
			}
			//DrawFormatString(30 * j, 30 * i, 0xffffff, "%d", MAP_DATA[i][j]);
		}
	}
}

void  GameMain::Draw_Item()
{
	DrawGraph(0, 0, GetArrayImages(GameMain_Images, 0), TRUE);
	/*DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);*/
	if (g_player_x >= 600)g_scroll_x = g_player_x - 600;
	else g_scroll_x = 0;

	for (int i = 0; i < 10; i++)
	{
		if (g_item[i].flg == TRUE)
		{
			if (HitBoxPlayer(g_player_x, g_player_y, g_item[i].x, g_item[i].y, PLAYER_SIZE, PLAYER_SIZE, TRUE))
			{
				g_item[i].flg = FALSE;
				if (g_item[i].type == 1)g_kagi_count++;
				if (g_item[i].type == 2)g_hukuro_count++;
			}
			if (MAP_DATA[(g_item[i].y + PLAYER_SIZE) / 30][g_item[i].x / 30] <= 0)
			{
				if (MAP_DATA[g_item[i].y / 30][g_item[i].x / 30] <= 0) g_item[i].y++;
			}
			else g_item[i].y = (g_item[i].y / PLAYER_SIZE) * PLAYER_SIZE;
			DrawGraph(g_item[i].x - g_scroll_x, g_item[i].y, GetArrayImages(Item_Images, g_item[i].type), TRUE);
		}
	}

	//DrawBox(Player_Hit_Back(g_player_x, 5), Player_Hit_Under(g_player_y, 5), Player_Hit_Front(g_player_x, 5), Player_Hit_Up(g_player_y, 5), 0xfffff, false);
}

void  GameMain::Item()
{
	/*if (g_item_selection == 0)
	{

	}*/
	if (g_item_selection == 1)
	{
		if (g_block_count > 0)
		{
			if ((MAP_DATA[g_cursory / 30][g_cursorx / 30] == 0) && ITEM_DATA[g_cursory / 30][g_cursorx / 30] == 0)
			{
				MAP_DATA[g_cursory / 30][g_cursorx / 30] = 4;
				g_block_count--;
			}
		}
	}
	//if (g_item_selection == 2)//アイテム使用（爆弾）
	//{
	//	if (g_bom_count > 0)
	//	{

	//		g_bom_count--;
	//	}
	//}
}

void GameMain:: Bom()
{
	bool g_bom_count_flg = FALSE;
	if(g_bom_count > 0)g_bom_count_flg = TRUE;

	for (int i = 0; i < 10; i++)
	{
		if (g_bom[i].flg > 750) g_bom[i].flg = NONE;
		if (g_bom[i].flg == NOMAL)
		{
			if (HitBoxPlayer(g_player_x, g_player_y, g_bom[i].x, g_bom[i].y, PLAYER_SIZE, PLAYER_SIZE, TRUE))
			{
				g_bom[i].flg = NONE;
				g_bom_count++;
			}

			if (g_bom[i].flg == NOMAL)DrawGraph(g_bom[i].x - g_scroll_x, g_bom[i].y, GetArrayImages(Item_Images,3), TRUE);
		}
		if (g_bom[i].flg == ANGRY)
		{
			g_bom[i].time--;
			
			if (g_bom[i].time <= 0)
			{
				for (int a = (g_bom[i].y - 90) / 30; a < (g_bom[i].y + 120) / 30; a++)
				{
					for (int j = (g_bom[i].x - 90) / 30; j < (g_bom[i].x + 120) / 30; j++)
					{
						MAP_DATA[a][j] = 0;
						if (((Player_Hit_Back(g_player_x, -5) / 30 == j) || (Player_Hit_Front(g_player_x, -5) / 30 == j)) &&
							((Player_Hit_Under(g_player_y, -5) / 30 == a) || (Player_Hit_Up(g_player_y, -5) / 30 == a)))
						{
							DrawFormatString(g_player_x, g_player_y, 0xffffff, "ghs");
						}
					}
				}
				g_bom[i].time = 300;
				g_bom[i].flg = NONE;
			}

			if (g_bom[i].flg == ANGRY)
			{
				DrawBox(g_bom[i].x - 90 - g_scroll_x, ((g_bom[i].y - 90) / 30) * 30, g_bom[i].x + 120 - g_scroll_x, ((g_bom[i].y + 120) / 30) * 30, 0xffffff, FALSE);
				DrawGraph(g_bom[i].x - g_scroll_x, g_bom[i].y, GetArrayImages(Item_Images, 4), TRUE);
				DrawFormatString(g_bom[i].x - g_scroll_x, g_bom[i].y - 30, 0xffffff, "%d", (g_bom[i].time / 50));
			}
		}
		if (g_bom[i].flg == NONE)
		{
			if ((g_xkey_flg == TRUE) && (g_old_xkey_flg == FALSE))
			{
				if (g_item_selection == 2)
				{
					if (g_bom_count_flg == TRUE)
					{
						if (MAP_DATA[g_cursory / 30][g_cursorx / 30] == 0)
						{
							g_bom[i].x = (g_cursorx / 30) * 30,
							g_bom[i].y = (g_cursory / 30) * 30;
							g_bom[i].flg = ANGRY;
							g_bom_count_flg = FALSE;
							g_bom_count--;
						}
					}
				}
			}
		}
		//DrawFormatString(0 - g_scroll_x,0 + (25* i), 0xffffff, "%d %d", i, g_bom[i].flg);
		if (MAP_DATA[(g_bom[i].y + PLAYER_SIZE) / 30][g_bom[i].x / 30] == 0)
		{
			if (MAP_DATA[g_bom[i].y / 30][g_bom[i].x / 30] == 0) g_bom[i].y++;
		}
		else g_bom[i].y = (g_bom[i].y / PLAYER_SIZE) * PLAYER_SIZE;
		ITEM_DATA[(g_bom[i].y - 1) / 30][g_bom[i].x / 30] = 0;
		ITEM_DATA[g_bom[i].y / 30][g_bom[i].x / 30] = 4;
		ITEM_DATA[(g_bom[i].y + 29) / 30][g_bom[i].x / 30] = 4;
	}
}

void GameMain::Hammer()
{

	

	if (g_hammer_flg == TRUE)
	{
		Block_Collision(g_hammer_y - 7, g_hammer_x, TRUE);
		Block_Collision(g_hammer_y - 7, g_hammer_x + 7, TRUE);
		Block_Collision(g_hammer_y, g_hammer_x + 7, TRUE);
		Block_Collision(g_hammer_y + 7, g_hammer_x + 7, TRUE);
		Block_Collision(g_hammer_y + 7, g_hammer_x, TRUE);
		Block_Collision(g_hammer_y + 7, g_hammer_x - 7, TRUE);
		Block_Collision(g_hammer_y, g_hammer_x - 7, TRUE);
		Block_Collision(g_hammer_y - 7, g_hammer_x - 7, TRUE);

		g_hammer_y -= (g_hammer_orbit_y / 3); 
		g_hammer_x -= (g_hammer_orbit_x / 3);
		g_hammer_orbit_y -= 1;

		g_hammer_angle += 10;
		if (g_hammer_angle > 360)g_hammer_angle = 0;
		if (g_hammer_y > 800)g_hammer_flg = FALSE;

		DrawRotaGraph(g_hammer_x - g_scroll_x, g_hammer_y, 1.0, M_PI / 180 * g_hammer_angle, GetArrayImages(Pickaxe_Images, 0), TRUE, FALSE);
	}
	else
	{
		if ((g_lkey_flg == TRUE) && (g_old_lkey_flg == FALSE))
		{
			Block_Collision(g_cursory, g_cursorx, FALSE);
		}
	}
}

void GameMain::Block_Collision(int a, int b, bool c)
{
	if ((a / 30) < MAP_HIGHT && (a / 30) >= 0) //マップの範囲内の
	{
		if ((b / 30) < MAP_WIDTH && (b / 30) >= 0)//マップの範囲内の
		{
			if (MAP_DATA[a / 30][b / 30] > 0 && MAP_DATA[a / 30][b / 30] < 5)//ブロックに当たった時
			{
				if (c == TRUE)MAP_DATA[a / 30][b / 30] = 0, g_break_block_count++ , PlaySoundMem(BreakBGM, DX_PLAYTYPE_BACK, TRUE);
				else
				{
					if (MAP_DATA[g_cursory / 30][g_cursorx / 30] == 4)MAP_DATA[g_cursory / 30][g_cursorx / 30] = 0, g_break_block_count++;
					else
					{
						MAP_DATA[g_cursory / 30][g_cursorx / 30]--;
						if (MAP_DATA[g_cursory / 30][g_cursorx / 30] == 0)g_break_block_count++;
					}
					
				}
				if ((g_break_block_count % 50) == 0) g_block_count++;
			
			}
			for (int i = 0; i < 10; i++)
			{
				if ((g_bom[i].y / 30 == a / 30) && (g_bom[i].x / 30 == b / 30) && (g_bom[i].flg == NOMAL))g_bom[i].flg = ANGRY;
			}
		}
	}
}

void GameMain::Player_Sousa()
{
	if (g_player_y >= 720)g_player_flg = DIE;
	if (g_player_flg == DIE)
	{
		if (--g_chara_life > 0)
		{
			g_player_x = 30, g_player_y = 550;
			g_player_flg = WALK;
		}
		else SetGameState(4);
	}

	if (g_player_flg != DIE)
	{
		if (AX == 0 && AY == 0)
		{
			if ((g_leftkey_flg == TRUE) && (g_old_leftkey_flg == FALSE))
			{
				if (g_item_selection == 0)g_item_selection = 2;
				else g_item_selection--;
			}
			else if ((g_rightkey_flg == TRUE) && (g_old_rightkey_flg == FALSE))
			{
				if (g_item_selection == 2)g_item_selection = 0;
				else g_item_selection++;
			}
		}
		else if(AY != 0)
		{
			if (AY < 0)g_cursory = Player_Hit_Up(g_player_y, 0) - PLAYER_SIZE;
			else g_cursory = Player_Hit_Up(g_player_y, 0) + PLAYER_SIZE;

			if (AX < 0)g_cursorx = g_player_x - PLAYER_SIZE, g_direction = LEFT;
			else if(AX > 0)g_cursorx = g_player_x + PLAYER_SIZE, g_direction = RIGHT;
			else g_cursorx = g_player_x;
		}
		else
		{
			g_cursory = g_player_y;
			g_cursorx = Player_Hit_Front(g_player_x, 0) - (PLAYER_SIZE * g_direction);
		}

		if (BX != 0 || BY != 0)
		{
			DrawFormatString(0, 0, 0xffffff, "%d = y", BY);
			DrawFormatString(0, 25, 0xffffff, "%d = x", BX);

			if (BY <= 0)
			{
				int x = g_player_x, y = g_player_y;
				int g_orbit_y = -1 * (BY / 18), g_orbit_x = -1 * (BX / 20);

				while (y < 720)
				{
					y -= (g_orbit_y / 3);
					x -= (g_orbit_x / 3);
					g_orbit_y -= 1;
					DrawCircle(x - g_scroll_x, y, 3, 0xffffff, false);
				}
				if ((g_lkey_flg) && (g_hammer_flg == FALSE)) 
				{
					g_hammer_flg = TRUE; 
					g_hammer_x = g_player_x, g_hammer_y = g_player_y;
					g_hammer_orbit_x = -1 * (BX / 20), g_hammer_orbit_y = -1 * (BY / 18);
				}
			}
		}

		if ((g_item_flg == TRUE) || (g_xkey_flg == TRUE) && (g_old_xkey_flg == FALSE))Item();
		Hammer();
		
		if (g_player_flg == WALK)Walk();
		else if (g_player_flg == JUMP)Jump();
		else Fall();

	}

	DrawGraph(((g_cursorx / 30) * 30) - g_scroll_x, (g_cursory / 30) * 30, GetArrayImages(Player_CursorImages,0), TRUE);

	DrawRotaGraph(g_player_x - g_scroll_x, g_player_y, 1.0, M_PI / 180 * 0, GetArrayImages(Player_Images, g_player_image_type), TRUE, g_direction);

	//DrawLine(g_player_x - g_scroll_x, g_player_y, g_player_x + (AX / 5) - g_scroll_x, g_player_y + (AY / 5), 0xffffff, TRUE);
}

void  GameMain::Walk()
{
	if (AX > 0 || AX < 0)
	{
		if (AX > 0)
		{
				g_direction = RIGHT;
				if (g_rkey_flg == FALSE)
				{ 
					g_player_x += 2;
					if (MAP_DATA[g_player_y / PLAYER_SIZE][Player_Hit_Front(g_player_x, 0) / PLAYER_SIZE] > 0)g_player_x = ((g_player_x / PLAYER_SIZE) * PLAYER_SIZE) + ((PLAYER_SIZE / 2));
				}
		}
		else if (AX < 0)
		{
			g_direction = LEFT;
			if (g_rkey_flg == FALSE)
			{
				g_player_x -= 2;
				if (MAP_DATA[g_player_y / PLAYER_SIZE][Player_Hit_Front(g_player_x, 0) / PLAYER_SIZE] > 0)g_player_x = ((g_player_x / PLAYER_SIZE) * PLAYER_SIZE) + ((PLAYER_SIZE / 2));
			}
		}

		if ((++g_image_time >= 5) && (g_rkey_flg == FALSE))
		{
			g_player_image_type++;
			if (g_player_image_type > 3)g_player_image_type = 0;
			g_image_time = 0;

		}
	}

	if (((MAP_DATA[Player_Hit_Under(g_player_y, 1) / PLAYER_SIZE][Player_Hit_Front(g_player_x, -3) / PLAYER_SIZE] <= 0) &&
		(MAP_DATA[Player_Hit_Under(g_player_y, 1) / PLAYER_SIZE][Player_Hit_Back(g_player_x, -3) / PLAYER_SIZE] <= 0)) || (g_player_y > 600))
	{
		g_player_flg = FALL;
	}
	else if ((g_akey_flg) && !(g_old_akey_flg))
	{
		if ((MAP_DATA[Player_Hit_Up(g_player_y, 1) / PLAYER_SIZE][Player_Hit_Front(g_player_x, -5) / PLAYER_SIZE] <= 0) &&
			(MAP_DATA[Player_Hit_Up(g_player_y, 1) / PLAYER_SIZE][Player_Hit_Back(g_player_x, -5) / PLAYER_SIZE] <= 0)) //プレイヤーの上になにもなえれば
		{
			g_move_speed_y = 50, g_player_flg = JUMP;
		}
	}

	DrawFormatString(100, 100, 0xffffff, "walk");
}

void GameMain::Jump()
{
	if (g_akey_flg == FALSE)
	{
		if (g_old_akey_flg && g_move_speed_y > 10)g_move_speed_y = 10;
	}
	g_player_y -= (g_move_speed_y / 6); //プレイヤーのY軸を引く
	g_move_speed_y -= 2;
	if ((MAP_DATA[Player_Hit_Up(g_player_y, 0) / PLAYER_SIZE][Player_Hit_Front(g_player_x, -5) / PLAYER_SIZE] > 0) ||
		(MAP_DATA[Player_Hit_Up(g_player_y, 0) / PLAYER_SIZE][Player_Hit_Back(g_player_x, -5) / PLAYER_SIZE] > 0))
	{
		g_player_y = ((g_player_y / PLAYER_SIZE) * PLAYER_SIZE) + (PLAYER_SIZE / 2);
		g_move_speed_y = -5;
	}
	
	if (AX > 0)g_player_x += 1, g_direction = RIGHT;
	if (AX < 0)g_player_x -= 1, g_direction = LEFT;
	if (MAP_DATA[Player_Hit_Up(g_player_y, 0) / PLAYER_SIZE][Player_Hit_Front(g_player_x, 0) / PLAYER_SIZE] > 0)g_player_x = ((g_player_x / PLAYER_SIZE) * PLAYER_SIZE) + (PLAYER_SIZE / 2);
	if (MAP_DATA[Player_Hit_Under(g_player_y, -5) / PLAYER_SIZE][Player_Hit_Front(g_player_x, 0) / PLAYER_SIZE] > 0)g_player_x = ((g_player_x / PLAYER_SIZE) * PLAYER_SIZE) + (PLAYER_SIZE / 2);
	if (MAP_DATA[Player_Hit_Up(g_player_y, 0) / PLAYER_SIZE][Player_Hit_Back(g_player_x, 0) / PLAYER_SIZE] > 0)g_player_x = ((g_player_x / PLAYER_SIZE) * PLAYER_SIZE) + (PLAYER_SIZE / 2);
	if (MAP_DATA[Player_Hit_Under(g_player_y, -5) / PLAYER_SIZE][Player_Hit_Back(g_player_x, 0) / PLAYER_SIZE] > 0)g_player_x = ((g_player_x / PLAYER_SIZE) * PLAYER_SIZE) + (PLAYER_SIZE / 2);

	if (g_move_speed_y < 0) g_player_flg = FALL;

	DrawFormatString(100, 100, 0xffffff, "jump");
}

void GameMain::Fall()
{
	g_player_y -= (g_move_speed_y / 6); //プレイヤーを落とす
	if (g_move_speed_y >= -35)g_move_speed_y -= 2;
	if ((MAP_DATA[Player_Hit_Under(g_player_y, 0) / PLAYER_SIZE][Player_Hit_Front(g_player_x, -5) / PLAYER_SIZE] > 0) ||
		(MAP_DATA[Player_Hit_Under(g_player_y, 0) / PLAYER_SIZE][Player_Hit_Back(g_player_x, -5) / PLAYER_SIZE] > 0)) //地面に落ちたら
	{
		if (g_player_y <= 600)
		{
			g_player_y = ((g_player_y / PLAYER_SIZE) * PLAYER_SIZE) + (PLAYER_SIZE / 2);//プレイヤーのy軸を整える
			g_move_speed_y = 0;
			g_player_flg = WALK;//プレイヤーのflgをWAKLにする
		}
	}
	if (AX > 0)g_player_x += 1, g_direction = RIGHT;
	if (AX < 0)g_player_x -= 1, g_direction = LEFT;
	if (MAP_DATA[(Player_Hit_Up(g_player_y, -5)) / PLAYER_SIZE][Player_Hit_Front(g_player_x, 0) / PLAYER_SIZE] > 0)g_player_x = ((g_player_x / PLAYER_SIZE) * PLAYER_SIZE) + (PLAYER_SIZE / 2);
	if (MAP_DATA[(Player_Hit_Under(g_player_y, -5)) / PLAYER_SIZE][Player_Hit_Front(g_player_x, 0) / PLAYER_SIZE] > 0)g_player_x = ((g_player_x / PLAYER_SIZE) * PLAYER_SIZE) + (PLAYER_SIZE / 2);
	if (MAP_DATA[Player_Hit_Up(g_player_y, -5) / PLAYER_SIZE][Player_Hit_Back(g_player_x, 0) / PLAYER_SIZE] > 0)g_player_x = ((g_player_x / PLAYER_SIZE) * PLAYER_SIZE) + (PLAYER_SIZE / 2);
	if (MAP_DATA[Player_Hit_Under(g_player_y, -5) / PLAYER_SIZE][Player_Hit_Back(g_player_x, 0) / PLAYER_SIZE] > 0)g_player_x = ((g_player_x / PLAYER_SIZE) * PLAYER_SIZE) + (PLAYER_SIZE / 2);

	DrawFormatString(100, 100, 0xffffff, "fall");
}

int GameMain::HitBoxPlayer(int px, int py, int ex, int ey, int psize,int esize, bool a)
{
	int sx1 = px - ((psize / 2) - 10);
	int sx2 = px + ((psize / 2) - 10);
	int sy1 = py - ((psize / 2) - 10);
	int sy2 = py + ((psize / 2) - 10);

	if(a == FALSE)
	{
		int sx1 = ex + 10;
		int sx2 = ex + (psize - 10);
		int sy1 = ey + 10;
		int sy2 = ey + (psize - 10);
	}

	int dx1 = ex + 10;
	int dx2 = ex + (esize - 10);
	int dy1 = ey + 10;
	int dy2 = ey + (esize - 10);

	//DrawBox(dx1, dy1, dx2, dy2, 0xfffff, false);
	//DrawBox(sx1, sy1, sx2, sy2, 0xfffff, false);

	//矩形が重なっていれば当たり
	if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2)
	{
		return TRUE;
	}

	return FALSE;
}

int GameMain::Player_Hit_Front(int a, int b)
{
	if (g_direction == RIGHT) return (a + ((PLAYER_SIZE / 2) - 1) + b);
	else return (a - ((PLAYER_SIZE / 2)) - b);
}

int GameMain::Player_Hit_Back(int a, int b)
{
	if (g_direction == RIGHT) return (a - (PLAYER_SIZE / 2) - b);
	else return (a + ((PLAYER_SIZE / 2) - 1) + b);
}

int GameMain::Player_Hit_Under(int a, int b)
{
	return (a + ((PLAYER_SIZE / 2) - 1) + b);
}

int GameMain::Player_Hit_Up(int a, int b)
{
	return (a - (PLAYER_SIZE / 2) - b);
}

