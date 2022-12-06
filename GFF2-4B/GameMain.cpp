#include"DxLib.h"
#include "GameMain.h"
#include"main.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"Player.h"



/***********************************************
*  ゲーム処理
************************************************/
void GameMain::Update()
{
	if (CheckSoundMem(g_Stage_BGM) != 1) {   //SEが流れていなかったら再生
		ChangeVolumeSoundMem(255 * 20 / 100, GetSounds(Stage_BGM)); //BGM音量調整 255最大音量から80%再生
		ChangeVolumeSoundMem(255 * 80 / 100, GetSounds(BreakBGM));
		PlaySoundMem(g_Stage_BGM, DX_PLAYTYPE_LOOP, TRUE); //BGM再生
	}
	Key();
	
	Player_Sousa(); //自機の操作
	Draw_Item();
	Draw();
	Ui();
	Time();
	Clear();
}


/***********************************************
*  初期化処理
************************************************/
void GameMain::GameMain_Init()
{
	g_player_move_flg = FALSE;
	g_player_x = 30, g_player_y = 550;
	BreakBGM = LoadSoundMem("BGM/Onoma-Pop01-3(Dry).mp3");//破壊音BGM
	g_Stage_BGM = LoadSoundMem("BGM/iwashiro_tricolour[1].mp3");
	g_scroll_x = 0;
	g_block_count = 0;
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
	g_direction = RIGHT;
	g_player_flg = WALK;
	g_break_block_count = 0;
	g_bom_count = 0;
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
					g_bom[g_bom_counnt].hit_flg = TRUE;
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
		SetScore(g_score4);
		StopSoundMem(Stage_BGM);
		SetGameState(4);
	}
	
}

void GameMain::Clear()
{

	if (g_player_x >= 4477 && g_player_y >=586)
	{
		SetScore(g_score4);
		StopSoundMem(Stage_BGM);
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

void GameMain::Draw()
{
	DrawGraph(-(g_scroll_x / 5), 0, GetArrayImages(GameMain_Images, 0), TRUE);

	for (int i = 0; i < 10; i++)
	{
		if (g_item[i].flg == TRUE)DrawGraph(g_item[i].x - g_scroll_x, g_item[i].y, GetArrayImages(Item_Images, g_item[i].type), TRUE);
		if (g_bom[i].flg == NOMAL)DrawGraph(g_bom[i].x - g_scroll_x, g_bom[i].y, GetArrayImages(Item_Images, 3), TRUE);
		if (g_bom[i].flg == ANGRY)DrawGraph(g_bom[i].x - g_scroll_x, g_bom[i].y, GetArrayImages(Item_Images, 4), TRUE);
	}

	if (g_hammer_flg == TRUE)DrawRotaGraph(g_hammer_x - g_scroll_x, g_hammer_y, 0.8, M_PI / 180 * g_hammer_angle, GetArrayImages(Pickaxe_Images, 0), TRUE, FALSE);
	DrawRotaGraph(g_player_x - g_scroll_x, g_player_y, 1.0, M_PI / 180 * 0, GetArrayImages(Player_Images, g_player_image_type), TRUE, g_direction);

	//Stage(); //ステージ描画
	for (int i = 0; i < MAP_HIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (MAP_DATA[i][j] != 0)
			{
				DrawGraph((30 * j) - g_scroll_x, 30 * i, GetArrayImages(Block_Images, MAP_DATA[i][j]), TRUE);
			}
		}
	}

	DrawGraph(((g_cursorx / 30) * 30) - g_scroll_x, (g_cursory / 30) * 30, GetArrayImages(Player_CursorImages, 0), TRUE);
	
	if (BX != 0 || BY != 0)
	{
		int x = g_player_x, y = g_player_y;
		int g_orbit_x = -(BX / 20), g_orbit_y = -(BY / 18);
		while (y < 720)
		{
			y -= (g_orbit_y / 3);
			x -= (g_orbit_x / 3);
			g_orbit_y -= 1;
			DrawCircle(x - g_scroll_x, y, 3, 0xffffff, false);
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (g_bom[i].flg == ANGRY)
		{
			DrawBox(g_bom[i].x - 90 - g_scroll_x, ((g_bom[i].y - 90) / 30) * 30, g_bom[i].x + 120 - g_scroll_x, ((g_bom[i].y + 120) / 30) * 30, 0xffffff, FALSE);
			DrawFormatString(g_bom[i].x - g_scroll_x, g_bom[i].y - 30, 0xffffff, "%d", (g_bom[i].time / 50));
		}
	}
}

void GameMain::Ui()
{
	DrawBox(0, 630, 1280, 720, 0x000000, TRUE); //UIの枠
	DrawBox(0, 630, 1280, 720, 0xFFFFFF, FALSE);//UIの枠
	DrawBox(0, 0, 1280, 630, 0xFFFFFF, FALSE);//UIの枠
	

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
	
	float size[3];
	//g_score = (g_break_block_count * 5) + (g_hukuro_count * 300) + (g_kagi_count * 1000);
	//g_score2 = (g_break_block_count * 5) + (g_hukuro_count * 300) + (g_kagi_count * 1000) + ((TimeLimit / 10) * 100);
	//g_score3 = (g_hukuro_count * 300) + (g_kagi_count * 1000) + ((TimeLimit / 10) * 100);
	//g_score4 = (g_break_block_count * 5) + (g_hukuro_count * 300) + (g_kagi_count * 1000);
	DrawFormatString(100, 0, 0xffffff, "%d = block_count, %d = break block", g_block_count, g_break_block_count);
	SetFontSize(30);
	DrawFormatString(100, 60, 0xffffff, "壊したブロック5点×%d+袋300点×%d+鍵1000点×%d        =            %d", g_break_block_count, g_hukuro_count, g_kagi_count, g_score);
	DrawFormatString(100, 90, 0xffffff, "壊したブロック5点×%d+袋300点×%d+鍵1000点×%d+残り時間10秒100点 = %d", g_break_block_count, g_hukuro_count, g_kagi_count, g_score2);
	DrawFormatString(100, 120, 0xffffff, "袋300点×%d+鍵1000点×%d+残り時間10秒100点           =            %d", g_hukuro_count, g_kagi_count, g_score3);
	DrawFormatString(100, 150, 0xffffff, "壊したブロック5点×%d+袋300点×%d+鍵1000点×%d       =            %d", g_break_block_count, g_hukuro_count, g_kagi_count, g_score4);
	SetFontSize(30);


	for (int i = 0; i < 3; i++)
	{
		size[i] = 0.6;
		if (g_item_selection == i)size[i] = 0.8;
		DrawRotaGraph(530 + (110 * i), 675, size[i], M_PI / 180 * 0, GetArrayImages(Item_cursor,i), TRUE, FALSE);
		if ((g_item_selection == 1 && i == 1) || (g_item_selection == 2 && i == 2))
		{
			DrawCircle(530 + (110 * i) + 37, 699, 15, 0x000000, TRUE);
			DrawCircle(530 + (110 * i) + 37, 699, 15, 0xFFFFFF, FALSE);
			if (g_item_selection == 1 && i == 1)DrawFormatString(530 + (110 * i) + 30, 685, 0xffffff, "%d", g_block_count);
			else DrawFormatString(530 + (110 * i) + 30, 685, 0xffffff, "%d", g_bom_count);
		}
	}
}

void  GameMain::Draw_Item()
{
	if (g_player_x >= 600)g_scroll_x = g_player_x - 600;
	else g_scroll_x = 0;

	for (int i = 0; i < 10; i++)
	{
		if (g_item[i].flg == TRUE)
		{
			if (HitBoxPlayer(g_player_x, g_player_y, g_item[i].x, g_item[i].y, BLOCK_SIZE, BLOCK_SIZE, TRUE))
			{
				g_item[i].flg = FALSE;
				if (g_item[i].type == 1)g_kagi_count++;
				if (g_item[i].type == 2)g_hukuro_count++;
			}
			if (MAP_DATA[(g_item[i].y + BLOCK_SIZE) / 30][g_item[i].x / 30] <= 0)
			{
				if (MAP_DATA[g_item[i].y / 30][g_item[i].x / 30] <= 0) g_item[i].y++;
			}
			else g_item[i].y = (g_item[i].y / BLOCK_SIZE) * BLOCK_SIZE;
		}

		bool g_bom_count_flg = FALSE;
		if (g_bom_count > 0)g_bom_count_flg = TRUE;
		if (g_bom[i].y > 700) g_bom[i].flg = NONE; //爆弾が画面外に落ちたらNONEにする

		if (g_bom[i].flg == NOMAL)//NOMAL状態の時
		{
			if (HitBoxPlayer(g_player_x, g_player_y, g_bom[i].x, g_bom[i].y, BLOCK_SIZE, BLOCK_SIZE, TRUE))//プレイヤーが取ると
			{
				g_bom[i].flg = NONE;//状態がNONE（消える）になる
				g_bom_count++;//使用できるボム数が増える
			}
		}
		if (g_bom[i].flg == ANGRY)//爆弾がANGRY状態の時
		{
			g_bom[i].time--;//カウントダウンが始まる
			if (g_bom[i].time <= 0)//カウントダウンが0になったら
			{
				for (int a = (g_bom[i].y - 90) / 30; a < (g_bom[i].y + 120) / 30; a++)//縦7マス
				{
					for (int j = (g_bom[i].x - 90) / 30; j < (g_bom[i].x + 120) / 30; j++)//横7マスの
					{
						if ((a < MAP_HIGHT && a >= 0) && (j < MAP_WIDTH && j >= 0))
						{
							if (MAP_DATA[a][j] != 6)MAP_DATA[a][j] = 0;//ブロックを消す
						}
						if (((Player_Hit_Back(g_player_x, -5) / 30 == j) || (Player_Hit_Front(g_player_x, -5) / 30 == j)) &&
							((Player_Hit_Under(g_player_y, -5) / 30 == a) || (Player_Hit_Up(g_player_y, -5) / 30 == a)))
						{
							g_player_flg = DIE;//爆発の範囲にプレイヤーがいたら
						}
					}
				}
				g_bom[i].time = 300;//タイムを300にする
				g_bom[i].flg = NONE;//爆弾の状態をNONEにする
			}
		}
		if (g_bom[i].flg == NONE)//爆弾の状態がNONEの時
		{
			if ((g_xkey_flg == TRUE) && (g_old_xkey_flg == FALSE) && (g_item_selection == 2))//Xキーが押されたら
			{
				if (g_bom_count_flg == TRUE)//手持ちの爆弾があったら
				{
					if (MAP_DATA[g_cursory / 30][g_cursorx / 30] == 0)//そこに何もなければ
					{
						g_bom[i].x = (g_cursorx / 30) * 30; //爆弾を配置
						g_bom[i].y = (g_cursory / 30) * 30;
						g_bom[i].flg = ANGRY; //状態はANGRY
						g_bom_count_flg = FALSE;
						g_bom_count--;//手持ち爆弾を一つ減らす
					}
				}
			}
		}
		else
		{
			if ((Get_MapData(g_bom[i].y + BLOCK_SIZE, g_bom[i].x) == 0) && (Get_MapData(g_bom[i].y, g_bom[i].x) == 0))
			{
				g_bom[i].y++; //爆弾が埋まってなくて、下にブロックがなかったら爆弾を落とす
			}
			else g_bom[i].y = (g_bom[i].y / BLOCK_SIZE) * BLOCK_SIZE; //爆弾が埋まっているか、下にブロックがあったら爆弾の縦軸を整える
			if((g_bom[i].y - 1) / 30 < MAP_HIGHT)ITEM_DATA[(g_bom[i].y - 1) / 30][g_bom[i].x / 30] = 0;
			if (g_bom[i].y / 30 < MAP_HIGHT)ITEM_DATA[g_bom[i].y / 30][g_bom[i].x / 30] = 4;
			if ((g_bom[i].y + 29) / 30 < MAP_HIGHT)ITEM_DATA[(g_bom[i].y + 29) / 30][g_bom[i].x / 30] = 4;
		}
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
	}
	else Block_Collision(g_cursory, g_cursorx, FALSE);
}

void GameMain::Block_Collision(int a, int b, bool c)
{
	if ((a / 30) < MAP_HIGHT && (a / 30) >= 0) //マップの範囲内の
	{
		if ((b / 30) < MAP_WIDTH && (b / 30) >= 0)//マップの範囲内の
		{
			if (MAP_DATA[a / 30][b / 30] > 0 && MAP_DATA[a / 30][b / 30] < 5)//ブロックに当たった時
			{
				if (c == TRUE)
				{
					MAP_DATA[a / 30][b / 30] = 0, g_break_block_count++;
					for (int i = 0; i < 10; i++)
					{
						if ((g_bom[i].y / 30 == a / 30) && (g_bom[i].x / 30 == b / 30) && (g_bom[i].flg == NOMAL))g_bom[i].hit_flg = FALSE;
					}
					PlaySoundMem(BreakBGM, DX_PLAYTYPE_BACK, TRUE);
				}
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
			else if (MAP_DATA[a / 30][b / 30] == 0)
			{
				for (int i = 0; i < 10; i++)
				{
					if ((g_bom[i].y / 30 == a / 30) && (g_bom[i].x / 30 == b / 30) && (g_bom[i].flg == NOMAL) && (g_bom[i].hit_flg == TRUE))g_bom[i].flg = ANGRY;
				}
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
		else SetScore(g_score4),StopSoundMem(Stage_BGM),SetGameState(4);
	}

	if (AX < 0)g_direction = LEFT;
	else if(AX > 0)g_direction = RIGHT;
	g_cursory = g_player_y;
	g_cursorx = Player_Hit_Front(g_player_x, 0) - (BLOCK_SIZE * g_direction);
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
	else if (AY != 0)
	{
		if (AY < 0)g_cursory = Player_Hit_Up(g_player_y, 0) - BLOCK_SIZE;
		else g_cursory = Player_Hit_Under(g_player_y, 0) + BLOCK_SIZE;

		if (AX < 0)g_cursorx = g_player_x - BLOCK_SIZE;
		else if (AX > 0)g_cursorx = g_player_x + BLOCK_SIZE;
		else g_cursorx = g_player_x;
	}

	if (BX != 0 || BY != 0)
	{
		if ((g_lkey_flg) && (g_hammer_flg == FALSE))
		{
			g_hammer_flg = TRUE;
			g_hammer_x = g_player_x, g_hammer_y = g_player_y;
			g_hammer_orbit_x = -(BX / 20), g_hammer_orbit_y = -(BY / 18);
			for (int i = 0; i < 10; i++)
			{
				g_bom[i].hit_flg = TRUE;
			}
		}	
	}

	if ((g_xkey_flg == TRUE) && (g_old_xkey_flg == FALSE))
	{
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
	}

	if (((g_lkey_flg == TRUE) && (g_old_lkey_flg == FALSE)) || (g_hammer_flg == TRUE))Hammer();

	if (g_player_flg == WALK)Walk();
	else if (g_player_flg == JUMP)Jump();
	else Fall();
}

void  GameMain::Walk()
{
	if ((AX != 0) && (g_rkey_flg == FALSE))
	{
		if (g_direction == RIGHT)g_player_x += 2;
		else g_player_x -= 2;
		if (Get_MapData(g_player_y, Player_Hit_Front(g_player_x, 0)) > 0)g_player_x = ((g_player_x / BLOCK_SIZE) * BLOCK_SIZE) + (15 - (2 * g_direction));
		if (++g_image_time >= 7)
		{
			g_player_image_type++;
			if (g_player_image_type > 3)g_player_image_type = 0;
			g_image_time = 0;
		}
	}
	if ((Get_MapData(Player_Hit_Under(g_player_y, 1), Player_Hit_Front(g_player_x, 0)) == 0) &&
		(Get_MapData(Player_Hit_Under(g_player_y, 1), Player_Hit_Back(g_player_x, 0)) == 0) || (g_player_y > 600))
	{
		g_player_flg = FALL; //足元が空白なら状態をFALLにする
	}
	else if ((g_akey_flg) && !(g_old_akey_flg))
	{
		if ((Get_MapData(Player_Hit_Up(g_player_y, 1), Player_Hit_Front(g_player_x, 0)) == 0) &&
			(Get_MapData(Player_Hit_Up(g_player_y, 1), Player_Hit_Back(g_player_x, 0)) == 0))
		{
			g_move_speed_y = 50, g_player_flg = JUMP; //Bキーが押されたとき、足元が空白じゃなく、頭上が空白なら状態をJUMPにする
		}
	}

	//DrawFormatString(100, 100, 0xffffff, "walk");
}

void GameMain::Jump()
{
	if (g_akey_flg == FALSE && g_move_speed_y > 10)g_move_speed_y = 10;
	
	g_player_y -= (g_move_speed_y / 6); //プレイヤーのY軸を引く
	g_move_speed_y -= 2;

	if ((Get_MapData(Player_Hit_Up(g_player_y, 0), Player_Hit_Front(g_player_x, 0)) > 0) ||
		(Get_MapData(Player_Hit_Up(g_player_y, 0), Player_Hit_Back(g_player_x, 0)) > 0))
	{
		g_player_y = ((g_player_y / BLOCK_SIZE) * BLOCK_SIZE) + 12;
		g_move_speed_y = -5;
	}
	
	if (AX > 0)g_player_x += 1;
	else if (AX < 0)g_player_x -= 1;

	if ((Get_MapData(Player_Hit_Up(g_player_y, 0), Player_Hit_Front(g_player_x, 0)) > 0)||
	    (Get_MapData(Player_Hit_Under(g_player_y, 0), Player_Hit_Front(g_player_x, 0)) > 0)||
	    (Get_MapData(Player_Hit_Up(g_player_y, 0), Player_Hit_Back(g_player_x, 0)) > 0)||
	    (Get_MapData(Player_Hit_Under(g_player_y, 0), Player_Hit_Back(g_player_x, 0)) > 0)) g_player_x = ((g_player_x / BLOCK_SIZE) * BLOCK_SIZE) + (15 - (2 * g_direction));

	if (g_move_speed_y < 0) g_player_flg = FALL;

	/*DrawFormatString(100, 100, 0xffffff, "jump");*/
}

void GameMain::Fall()
{
	g_player_y -= (g_move_speed_y / 6); //プレイヤーを落とす
	if (g_move_speed_y >= -35)g_move_speed_y -= 2;

	if ((Get_MapData(Player_Hit_Under(g_player_y, 0), Player_Hit_Front(g_player_x, 0)) > 0) ||
		(Get_MapData(Player_Hit_Under(g_player_y, 0), Player_Hit_Back(g_player_x, 0)) > 0)) //地面に当たったら
	{
		if (g_player_y <= 600)//画面内なら
		{
			g_player_y = ((g_player_y / BLOCK_SIZE) * BLOCK_SIZE) + 17;//プレイヤーのy軸を整える
			g_move_speed_y = 0;
			g_player_flg = WALK;//プレイヤーのflgをWAKLにする
		}
	}
	if (AX > 0)g_player_x += 1;
	else if (AX < 0)g_player_x -= 1;

	if ((Get_MapData(Player_Hit_Up(g_player_y, 0), Player_Hit_Front(g_player_x, 0)) > 0) ||
		(Get_MapData(Player_Hit_Under(g_player_y, 0), Player_Hit_Front(g_player_x, 0)) > 0) ||
		(Get_MapData(Player_Hit_Up(g_player_y, 0), Player_Hit_Back(g_player_x, 0)) > 0) ||
		(Get_MapData(Player_Hit_Under(g_player_y, 0), Player_Hit_Back(g_player_x, 0)) > 0)) g_player_x = ((g_player_x / BLOCK_SIZE) * BLOCK_SIZE) + (15 - (2 * g_direction));

	/*DrawFormatString(100, 100, 0xffffff, "fall");*/
}

int GameMain::Get_MapData(int y, int x)
{
	return MAP_DATA[y / BLOCK_SIZE][x / BLOCK_SIZE];
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

	//矩形が重なっていれば当たり
	if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2) return TRUE;

	return FALSE;
}

int GameMain::Player_Hit_Front(int a, int b)
{
	if (g_direction == RIGHT) return (a + (PLAY_SIZE / 2) + b);
	else return (a - ((PLAY_SIZE / 2)+ 1) - b);
}

int GameMain::Player_Hit_Back(int a, int b)
{
	if (g_direction == RIGHT) return (a - ((PLAY_SIZE / 2) + 1) - b);
	else return (a + (PLAY_SIZE / 2) + b);
}

int GameMain::Player_Hit_Under(int a, int b)
{
	return (a + (PLAY_SIZE / 2) + b);
}

int GameMain::Player_Hit_Up(int a, int b)
{
	return (a - (PLAY_SIZE / 2) - b);
}

