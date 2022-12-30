#include"DxLib.h"
#include "GameMain.h"
#include"main.h"
#define _USE_MATH_DEFINES
#include<math.h>


/***********************************************
*  ゲーム処理
************************************************/
void GameMain::Update()
{
	ChangeVolumeSoundMem(255 * 80 / 100, GetSounds(BreakBGM));
	Key();
	switch (g_game_state)
	{
	case 0://ステージ選択画面
		Update_Stage_Select();
		Draw_Stage_Select();
		break;
	case 1:
		if (!g_game_stop)
		{
			Player_Sousa(); //自機の操作
			Item();
			Bom();
			Time();
		}
		Draw();
		Ui();
		break;

	case 2:
		Clear();
		Draw();
		Ui();
		break;
	}
}

/***********************************************
*  初期化処理
************************************************/
void GameMain::Stage_Select_Init()
{
	FILE* fp = NULL;//ステージ１ファイル読み込み

	if (fopen_s(&fp, "data/hiscore.txt", "r") != 0)//ステージごとのハイスコアのデータ
	{
		throw "Data/item1.txt";
	}
	for (int i = 0; i < 3; i++)
	{
		fscanf_s(fp, "%d", &g_hi_score[i]);
	}
	fclose(fp);
	fp = NULL;

	g_stage = 0;
	g_game_state = 0;
	g_stage_select_image = LoadGraph("images/map1.png");
	LoadDivGraph("images/number.png", 10, 10, 1, 45, 110, g_stage_select_number_image);
	StageBGM = LoadSoundMem("BGM/StageBGM.mp3");
	StageBGM1 = LoadSoundMem("BGM/StageBGM1.mp3");
	StageBGM2 = LoadSoundMem("BGM/StageBGM2.mp3");
	SetGameState(2); //ゲームメイン移行
}
void GameMain::Draw_Stage_Select()
{
	DrawGraph(140, 10, g_stage_select_image, TRUE);
	DrawCircle(460, 465, 10, 0xff0000, TRUE);
	DrawCircle(675, 395, 10, 0xff0000, TRUE);
	DrawCircle(900, 265, 10, 0xff0000, TRUE);
	
	DrawRotaGraph(g_player_x, g_player_y, 1.0, M_PI / 180 * 0, GetArrayImages(Player_Images, g_player_image_type), TRUE, FALSE);

	int hi_score = g_hi_score[g_stage]; //スコア保護
	int hiscore_x = 300;//時間の描画位置
	int Calc = 10000;//表示桁数

	while (Calc > 0)
	{
		DrawGraph(hiscore_x, 150, g_stage_select_number_image[hi_score / Calc],TRUE);//すコア表示
		hi_score -= (hi_score / Calc) * Calc;
		Calc /= 10;
		hiscore_x += 45;
	}
	DrawGraph(870,487, g_stage_select_number_image[g_stage + 1], TRUE);//すコア表示
}
void GameMain::Update_Stage_Select()
{
	if (CheckSoundMem(BGMStage) != 1) {
		BGMStage = LoadSoundMem("BGM/BGMStage.mp3");
		ChangeVolumeSoundMem(255 * 25 / 100, BGMStage); //BGM音量調整 
		PlaySoundMem(BGMStage, DX_PLAYTYPE_LOOP, TRUE); //SE再生
	}
	if ((g_rightkey_flg) && (!g_old_rightkey_flg) && (g_stage < 2))g_stage++;
	else if ((g_leftkey_flg) && (!g_old_leftkey_flg) && (g_stage > 0))g_stage--;
	
	if (g_stage == 0)g_player_x = 460, g_player_y = 465;
	else if (g_stage == 1)g_player_x = 675, g_player_y = 395;
	else if (g_stage == 2)g_player_x = 900, g_player_y = 265;
	
	if (g_bkey_flg && !g_old_bkey_flg)
	{
		GameMain_Init();
		StopSoundMem(BGMStage);
		g_game_state = 1;
	}
}


/***********************************************
*  初期化処理
************************************************/
void GameMain::GameMain_Init()
{
	FILE* fp_m = NULL;//ステージ１ファイル読み込み
	FILE* fp_i = NULL;
	ClearTime = FALSE;
	ClearStop = FALSE;

	switch (g_stage)
	{
	case 0://ステージ1初期化
		g_player_x = 30;
		g_player_y = 550;
		g_stage_width = 150;
		g_stage_scroll_x = 3220;
		g_clear_x = 4477;
		g_bom_count = 0;

		ChangeVolumeSoundMem(255 * 25 / 100, StageBGM); //BGM音量調整 
		PlaySoundMem(StageBGM, DX_PLAYTYPE_LOOP, TRUE); //SE再生

		if (fopen_s(&fp_i, "data/item1.txt", "r") != 0)//アイテムデータ
		{
			throw "Data/item1.txt";
		}
		if (fopen_s(&fp_m, "data/map1.txt", "r") != 0)//マップデータ
		{
			throw "Data/map1.txt";
		}
		break;

	case 1://ステージ1初期化
		g_player_x = 30;
		g_player_y = 550;
		g_stage_width = 150;
		g_stage_scroll_x = 3220;
		g_clear_x = 4477;
		g_bom_count = 0;

		ChangeVolumeSoundMem(255 * 25 / 100, StageBGM1); //BGM音量調整 
		PlaySoundMem(StageBGM1, DX_PLAYTYPE_LOOP, TRUE); //SE再生

		if (fopen_s(&fp_i, "data/item2.txt", "r") != 0)//アイテムデータ
		{
			throw "Data/item2.txt";
		}		
		if (fopen_s(&fp_m, "data/map2.txt", "r") != 0)//マップデータ
		{
			throw "Data/map2.txt";
		}
		break;

	case 2://ステージ2初期化
		g_player_x = 30;
		g_player_y = 550;
		g_stage_width = 150;
		g_stage_scroll_x = 3220;
		g_clear_x = 4477;
		g_bom_count = 0;

		ChangeVolumeSoundMem(255 * 25 / 100, StageBGM2); //BGM音量調整 
		PlaySoundMem(StageBGM2, DX_PLAYTYPE_LOOP, TRUE); //SE再生

		if (fopen_s(&fp_i, "data/item3.txt", "r") != 0)//アイテムデータ
		{
			throw "Data/item3.txt";
		}
		if (fopen_s(&fp_m, "data/map3.txt", "r") != 0)//マップデータ
		{
			throw "Data/map3.txt";
		}
		break;
	}

	for (int i = 0; i < MAP_HIGHT; i++)
	{
		for (int j = 0; j < g_stage_width; j++)
		{
			fscanf_s(fp_m, "%d", &MAP_DATA_INIT[i][j]);
		}
	}
	fclose(fp_m);
	fp_m = NULL;

	for (int i = 0; i < MAP_HIGHT; i++)
	{
		for (int j = 0; j < g_stage_width; j++)
		{
			fscanf_s(fp_i, "%d", &ITEM_DATA[i][j]);
		}
	}
	fclose(fp_i);
	fp_i = NULL;
	ClearScore = 0;
	g_scroll_x = 0;
	g_block_count = 0;
	g_break_block_count = 0;
	g_score = 0;
	g_bag_count = 0;
	g_key_count = 0;
	g_item_selection = 0;
	fps_cunt = 0;
	TimeLimit = 200;//制限時間
	ClearStopTime = 1;
	g_player_image_type = 0;
	g_direction = RIGHT;
	g_player_flg = WALK;
	g_chara_life = 3;
	g_checkpoint_flg = FALSE;
	g_hammer_flg = HAMMER_NONE;
	g_hit_hammer_flg = FALSE;
	g_startkey_flg = FALSE;
	g_cursor_key_time = 0;
	g_old_cursor_BX = 1;
	g_cursor_flg = TRUE;
	g_game_stop = FALSE;

	BreakBGM = LoadSoundMem("BGM/breakblock1.mp3");//破壊音BGM
	TimeLimitImages = LoadGraph("images/Timeer.png"); //時間制限文字
	g_blowing_images = LoadGraph("images/fuki.png"); //爆発した時の画像
	ScoreImages = LoadGraph("images/Score.png"); //スコア文字画像
	LoadDivGraph("images/Timemo.png", 10, 10, 1, 20, 30, g_NumberImage);
	LoadDivGraph("images/Timemo1.png", 10, 10, 1, 40, 60, g_NumberImage1);
	LimitImages = LoadGraph("images/Limet.png");

	for(int i = 0; i < 10; i++)//アイテムの初期化
	{
		g_item[i].x = 0;
		g_item[i].y = 0;
		g_item[i].point = 0;
		g_item[i].flg = FALSE;
		g_item[i].type = 0;

		g_bom[i].flg = NONE;//爆弾の初期化
		g_bom[i].x = 0;
		g_bom[i].y = 0;
		g_bom[i].time = 300;
		g_bom[i].angle = 0;
	}

	int g_init_bom_count = 0;
	int g_init_item_count = 0;

	for (int i = 0; i < MAP_HIGHT; i++)
	{
		for (int j = 0; j < g_stage_width; j++)
		{
			if (ITEM_DATA[i][j] == 1 || ITEM_DATA[i][j] == 2)
			{
				g_item[g_init_item_count].x = j * 30;
				g_item[g_init_item_count].y = i * 30;
				g_item[g_init_item_count].point = 100;
				g_item[g_init_item_count].type = ITEM_DATA[i][j];
				g_item[g_init_item_count].flg = TRUE;
				g_init_item_count++;
			}
			
			MAP_DATA[i][j] = MAP_DATA_INIT[i][j];
			if (MAP_DATA[i][j] == 3)MAP_DATA[i][j] = GetRand(2) + 1;//ブロックをランダムに
		}
	}
	Setstage(g_stage);
}

/***********************************************
* 制限時間
************************************************/
void GameMain::Time()
{
	if (g_game_state == 1) {
		if (++fps_cunt % 60 == 0) {
			--TimeLimit;
		}
		if (TimeLimit <= 0)
		{
			StopSoundMem(StageBGM);
			StopSoundMem(StageBGM1);
			StopSoundMem(StageBGM2);
			SetScore(0, FALSE);
			SetGameState(4);
		}
	}

	if (TimeLimit == 200)
	{
		g_bom_count = 2;
	}

	if (g_game_state == 2)
	{
		if (++fps_cunt % 60 == 0) {
			--ClearStopTime;
		}
		if (ClearStopTime <= 0)
		{
			StopSoundMem(StageBGM);
			StopSoundMem(StageBGM1);
			StopSoundMem(StageBGM2);
			Setkagi(g_key_count);
			SetGameState(8);
		}
	}
}

void GameMain::Clear()
{
	if (g_player_x >= g_clear_x) //クリア条件
	{
		//SetScore(g_score+(TimeLimit * 100));
		if (GetScore() > g_hi_score[g_stage])
		{
			FILE* fp;
            #pragma warning(disable:4996)

			g_hi_score[g_stage] = GetScore();
			if ((fp = fopen("data/hiscore.txt", "w")) == NULL)printf("Ranking Data Error\n");
			for (int i = 0; i < 3; i++)
			{
				fprintf(fp, "%d ", g_hi_score[i]);
			}
			fclose(fp);
		}
	
	}
}

void GameMain::Key()
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
	g_old_startkey_flg = g_startkey_flg;

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
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_8)g_startkey_flg = TRUE;
	else g_startkey_flg = FALSE;

	if (g_startkey_flg && !g_old_startkey_flg)
	{
		if (g_game_stop)g_game_stop = FALSE;
		else g_game_stop = TRUE;
	}

}

void GameMain::Draw()
{
	if (++Timer == 40)Timer = 0;
	DrawGraph(-(g_scroll_x / 5), 0, GetArrayImages(GameMain_Images, 0), TRUE);

	for (int i = 0; i < 10; i++)
	{
		if (g_item[i].flg)
		{
			DrawGraph(g_item[i].x - g_scroll_x, g_item[i].y, GetArrayImages(Item_Images, g_item[i].type), TRUE);
			DrawGraph(g_item[i].x - g_scroll_x + 4, g_item[i].y + 4, GetArrayImages(KiraKira_Images, Timer / 20), TRUE);
		}
		if (g_bom[i].flg == NOMAL)
		{
			DrawGraph(g_bom[i].x - g_scroll_x, g_bom[i].y, GetArrayImages(Item_Images, 3), TRUE);
			DrawGraph(g_bom[i].x - g_scroll_x, g_bom[i].y, GetArrayImages(KiraKira_Images, Timer / 20), TRUE);
		}
		else if(g_bom[i].flg == ANGRY)DrawGraph(g_bom[i].x - g_scroll_x, g_bom[i].y, GetArrayImages(Item_Images, 4), TRUE);
		else if(g_bom[i].flg == FLY)DrawRotaGraph(g_bom[i].x + 15 - g_scroll_x, g_bom[i].y + 15, 1, M_PI / 180 * g_bom[i].angle, GetArrayImages(Item_Images, 4), TRUE);
	}

	if (g_hammer_flg == HAMMER_FLY)DrawRotaGraph(g_hammer_x - g_scroll_x, g_hammer_y, 0.5, M_PI / 180 * g_hammer_angle, GetArrayImages(Pickaxe_Images, 0), TRUE, FALSE);
	DrawRotaGraph(g_player_x - g_scroll_x, g_player_y, 1.0, M_PI / 180 * 0, GetArrayImages(Player_Images, g_player_image_type), TRUE, g_direction);

	for (int i = 0; i < MAP_HIGHT; i++)
	{
		for (int j = 0; j < g_stage_width; j++)
		{
			if (MAP_DATA[i][j] > 0)
			{
				DrawGraph((30 * j) - g_scroll_x, 30 * i, GetArrayImages(Block_Images, MAP_DATA[i][j]), TRUE);
			}
			//DrawFormatString((30 * j) - g_scroll_x, 30 * i, 0xffffff, "%d", ITEM_DATA[i][j]);
		}
	}

	if (!g_game_stop)
	{
		if (BX != 0 || BY != 0)
		{
			int x = g_player_x, y = g_player_y;
			int g_orbit_x = -(BX / 20), g_orbit_y = -(BY / 18);
			while (y < 720)
			{
				y -= (g_orbit_y / 3);
				x -= (g_orbit_x / 4);
				g_orbit_y -= 1;
				DrawCircle(x - g_scroll_x, y, 3, 0xffffff, false);
			}
		}
		DrawGraph(((g_cursorx / 30) * 30) - g_scroll_x, (g_cursory / 30) * 30, GetArrayImages(Player_CursorImages, 0), TRUE);
	}

	for (int i = 0; i < 10; i++)
	{
		if (g_bom[i].flg == ANGRY || g_bom[i].flg == FLY)
		{
			DrawBox(g_bom[i].x - 90 - g_scroll_x, ((g_bom[i].y - 90) / 30) * 30, g_bom[i].x + 120 - g_scroll_x, ((g_bom[i].y + 120) / 30) * 30, 0xffffff, FALSE);
			if(g_bom[i].flg == ANGRY)DrawFormatString(g_bom[i].x - g_scroll_x, g_bom[i].y - 30, 0xffffff, "%d", (g_bom[i].time / 50));
		}
	}
	if (g_game_state == 1) {
		if (TimeLimit <= 100 && TimeLimit >= 95 || TimeLimit <= 50 && TimeLimit >= 45 || TimeLimit <= 5) //残り時間を大きく表示
		{
			DrawGraph(250, 50, LimitImages, TRUE); //残り時間の文字描画

			TmpTime = TimeLimit; //制限時間保護
			int TimeX = 550;//時間の描画位置
			int Calc = 10000;//表示桁数

			while (Calc > 0)
			{
				if (Calc <= 100)DrawGraph(TimeX, 50, g_NumberImage1[TmpTime / Calc], FALSE);//時間表示
				TmpTime -= (TmpTime / Calc) * Calc;
				Calc /= 10;
				TimeX += 50;
			}
		}
	}
}

void GameMain::Ui()
{
	DrawBox(0, 630, 1280, 720, 0x000000, TRUE); //UIの枠
	DrawBox(0, 630, 1280, 720, 0xFFFFFF, FALSE);//UIの枠
	DrawBox(0, 0, 1280, 630, 0xFFFFFF, FALSE);//UIの枠
	DrawGraph(5, 634, ScoreImages, FALSE);
	DrawGraph(250, 634, TimeLimitImages, FALSE); //残り時間の文字描画

	for (int i = 0; i < g_chara_life; i++)
	{
		DrawGraph(1000 + (60 * (i + 1)), 630, GetArrayImages(Life_Images, 0), TRUE);
	}

	TmpTime = TimeLimit; //制限時間保護
	TmpScore = GetScore(); //スコア保護
	int TimeX = 250;//時間の描画位置
	int ScoreX = 35;//スコアの描画位置
	int Calc = 10000;//表示桁数
	
		while (Calc > 0)
		{
			if (Calc <= 100)DrawGraph(TimeX, 675, g_NumberImage[TmpTime / Calc], TRUE);//時間表示
			DrawGraph(ScoreX, 675, g_NumberImage[TmpScore / Calc], FALSE);//すコア表示
			TmpTime -= (TmpTime / Calc) * Calc;
			TmpScore -= (TmpScore / Calc) * Calc;
			Calc /= 10;
			TimeX += 30;
			ScoreX += 30;
		}
	
		if (ClearTime == FALSE && g_game_state == 2)
		{
			ClearScore = ((g_break_block_count * 5) + (g_bag_count * 300) + (g_key_count * 1000)) + (TimeLimit * 100);
			ClearTime = TRUE;
		}

		if (ClearTime == TRUE && GetScore() < ClearScore)SetScore(101, TRUE);
			
		if (GetScore() >= ClearScore && g_game_state == 2)
		{
			SetScore(ClearScore, FALSE);
			ClearStop = TRUE;
			Time();
		}
		if (TimeLimit != 0 && g_game_state == 2)--TimeLimit;
		//SetScore(20,FALSE);
	if (g_game_state == 1) {
		SetScore((g_break_block_count * 5) + (g_bag_count * 300) + (g_key_count * 1000), FALSE);
	}
	float size[3];

	for (int i = 0; i < 3; i++)
	{
		size[i] = 0.6; //アイテム画像の大きさを0.6倍にする
		if (g_item_selection == i)size[i] = 0.8;//アイテムが選択されているアイテムなら画像の大きさを0.8倍する
		DrawRotaGraph(530 + (110 * i), 675, size[i], 0, GetArrayImages(Item_cursor, i), TRUE, FALSE);//アイテム画像の表示
		if ((g_item_selection == 1 && i == 1) || (g_item_selection == 2 && i == 2))
		{
			DrawCircle(530 + (110 * i) + 37, 699, 15, 0x000000, TRUE);
			DrawCircle(530 + (110 * i) + 37, 699, 15, 0xFFFFFF, FALSE);
			if (g_item_selection == 1 && i == 1)
			{
				DrawFormatString(670, 685, 0xffffff, "%d", g_block_count);
				DrawFormatString(624, 642, 0xffffff, "%02d", g_break_block_count % 50);
				DrawString(624, 680, "50", 0xffffff);
				DrawBox(610, 675, 670, 678, 0xffffff, TRUE);
			}
			else DrawFormatString(530 + (110 * i) + 30, 685, 0xffffff, "%d", g_bom_count);
		}
	}

	if (g_game_stop == TRUE)
	{
		if (g_bkey_flg && !g_old_bkey_flg)
		{
			SetGameState(1);
		}
		if (g_akey_flg && !g_old_bkey_flg)
		{
			GameMain_Init();
		}
		DrawFormatString(400, 300, GetColor(255, 255, 255), "Aボタンでステージやり直し\nBボタンでステージ選択\nSTARTボタンでポーズ解除");
	}
}

void GameMain::Bom()
{
	bool g_bom_count_flg = FALSE;
	if (g_bom_count > 0)g_bom_count_flg = TRUE; //手持ち爆弾が１個でもあればg_bom_count_flgをTRUEにする

	for (int i = 0; i < 10; i++)
	{
		if (g_bom[i].y > 700) g_bom[i].flg = NONE; //爆弾が画面外に落ちたらNONEにする

		if (g_bom[i].flg == NOMAL)//NOMAL状態の時
		{
			if (HitBoxPlayer(g_player_x, g_player_y, g_bom[i].x, g_bom[i].y, BLOCK_SIZE, BLOCK_SIZE, TRUE))//爆弾がプレイヤーに当たると取ると
			{
				g_bom[i].flg = NONE;//状態がNONE（消える）になる
				g_bom_count++;//使用できるボム数が増える
			}
		}
		if ((g_bom[i].flg == ANGRY) || (g_bom[i].flg == FLY))//爆弾がANGRY状態の時
		{
			if(g_bom[i].flg == ANGRY)g_bom[i].time--;//カウントダウンが始まる
			else
			{
				g_bom[i].y -= (g_bom[i].orbit_y / 3);//y座標の変更
				g_bom[i].x -= (g_bom[i].orbit_x / 4);//x座標の変更
				g_bom[i].orbit_y -= 1;//ｙ座標の変更量を減らす
				g_bom[i].angle -= (10 * g_bom[i].angle_direction);
				if (g_bom[i].angle >= 360)g_bom[i].angle = 0; //爆弾が一回転したら角度を0にする
				else if (g_bom[i].angle <= 0)g_bom[i].angle = 360;//爆弾が一回転したら角度を360にする
				if (Get_MapData(g_bom[i].y, g_bom[i].x) > 0)g_bom[i].time = 0;
			}
			if (g_bom[i].time <= 0)//カウントダウンが0になったら
			{
				for (int a = (g_bom[i].y - 90) / 30; a < (g_bom[i].y + 120) / 30; a++)//縦7マス
				{
					for (int j = (g_bom[i].x - 90) / 30; j < (g_bom[i].x + 120) / 30; j++)//横7マスの
					{
						if ((a < MAP_HIGHT && a >= 0) && (j < g_stage_width && j >= 0))//マップ内の
						{
							if (MAP_DATA[a][j] != 6 && MAP_DATA[a][j] > 0)
							{
								MAP_DATA[a][j] = 0;//６番以外のブロックを消す
								g_break_block_count++;
								if ((g_break_block_count % 50) == 0) g_block_count++;
							}
						}
						if (((Player_Hit_Back(g_player_x, -5) / 30 == j) || (Player_Hit_Front(g_player_x, -5) / 30 == j)) &&
							((Player_Hit_Under(g_player_y, -5) / 30 == a) || (Player_Hit_Up(g_player_y, -5) / 30 == a)))
						{
							g_player_flg = DIE;//爆発の範囲にプレイヤーがいたら死ぬ
						}
					}
				}
				g_bom[i].time = 300;//タイムを300にする
				g_bom[i].flg = NONE;//爆弾の状態をNONE(なし)にする
			}
		}
		if(g_bom[i].flg != NONE && g_bom[i].flg != FLY)//爆弾の状態がNONE以外の時
		{
			if (Get_MapData(g_bom[i].y + BLOCK_SIZE, g_bom[i].x) <= 0)//爆弾の下にブロックがなかったら
			{
				if (Get_MapData(g_bom[i].y, g_bom[i].x) <= 0)g_bom[i].y++; //爆弾が埋まってなければ爆弾を落とす
			}
			else g_bom[i].y = (g_bom[i].y / BLOCK_SIZE) * BLOCK_SIZE; //爆弾の下にブロックがあったら爆弾のy軸を整える

			if ((g_bom[i].y - 1) / 30 < MAP_HIGHT)ITEM_DATA[(g_bom[i].y - 1) / 30][g_bom[i].x / 30] = 0;//爆弾が落ちた後のITEM_DATAを0にする（0じゃないとプレイヤーがブロックをおけない）
			if (g_bom[i].y / 30 < MAP_HIGHT)ITEM_DATA[g_bom[i].y / 30][g_bom[i].x / 30] = 4;//爆弾がある位置のITEM_DATAに数字を入れる（アイテムの上にブロックを重ねないように）
			if ((g_bom[i].y + 29) / 30 < MAP_HIGHT)ITEM_DATA[(g_bom[i].y + 29) / 30][g_bom[i].x / 30] = 4;//爆弾がある位置のITEM_DATAに数字を入れる（アイテムの上にブロックを重ねないように）
		}
	}
}

void  GameMain::Item()
{
	if (g_player_x >= 600)//プレイヤーのx座標が600以上なら
	{
		if(g_player_x >= g_stage_scroll_x + 600)g_scroll_x = g_stage_scroll_x;//プレイヤーのx座標が3820以上なら画面スクロールのx座標を3220に固定する（ステージ端に来たため）
		else g_scroll_x = g_player_x - 600;//プレイヤーのx座標が3820未満なら画面をスクロールさせる
	}
	else g_scroll_x = 0;//プレイヤーのx座標が600未満なら画面スクロールしない

	
	for (int i = 0; i < 10; i++)
	{
		if (g_item[i].flg)//アイテムがステージ上にあるなら
		{
			if (HitBoxPlayer(g_player_x, g_player_y, g_item[i].x, g_item[i].y, BLOCK_SIZE, BLOCK_SIZE, TRUE))//アイテムがプレイヤーに当たったなら
			{
				g_item[i].flg = FALSE;//アイテムをステージ上から消す
				if (g_item[i].type == 1)g_key_count++;//アイテムタイプが１なら鍵のカウントを増やす
				if (g_item[i].type == 2)g_bag_count++;//アイテムタイプが２なら袋のカウントを増やす
			}
			if (MAP_DATA[(g_item[i].y + BLOCK_SIZE) / 30][g_item[i].x / 30] <= 0)//アイテムの真下にブロックがなければ
			{
				if (MAP_DATA[g_item[i].y / 30][g_item[i].x / 30] <= 0) g_item[i].y++;//アイテムがブロックなどに埋まってなければアイテムのy座標を＋する
			}
			else g_item[i].y = (g_item[i].y / BLOCK_SIZE) * BLOCK_SIZE;//アイテムの真下にブロックがあるならアイテムのy座標を整える

			if ((g_item[i].y - 1) / 30 < MAP_HIGHT)ITEM_DATA[(g_item[i].y - 1) / 30][g_item[i].x / 30] = 0;//アイテムが落ちた後のITEM_DATAを0にする（0じゃないとプレイヤーがブロックをおけない）
			if (g_item[i].y / 30 < MAP_HIGHT)ITEM_DATA[g_item[i].y / 30][g_item[i].x / 30] = g_item[i].type;//アイテムがある位置のITEM_DATAに数字を入れる（アイテムの上にブロックを重ねないように）
			if ((g_item[i].y + 29) / 30 < MAP_HIGHT)ITEM_DATA[(g_item[i].y + 29) / 30][g_item[i].x / 30] = g_item[i].type;//アイテムがある位置のITEM_DATAに数字を入れる（アイテムの上にブロックを重ねないように）
		}
	}
}

void GameMain::Hammer()
{
	if (g_hammer_flg == HAMMER_FLY)//つるはしが投げられている時
	{
		g_old_hammer_x = g_hammer_x;//直前のつるはしのx座標を入れる
		g_old_hammer_y = g_hammer_y;//直前のつるはしのy座標を入れる

		g_hammer_y -= (g_hammer_orbit_y / 3);//y座標の変更
		g_hammer_x -= (g_hammer_orbit_x / 4);//x座標の変更
		g_hammer_orbit_y -= 1;//ｙ座標の変更量を減らす

		int g_old_break_block_count = g_break_block_count;
		//つるはしの周りを壊す
		Block_Collision(g_hammer_y - 7, g_hammer_x, TRUE);
		Block_Collision(g_hammer_y - 7, g_hammer_x + 7, TRUE);
		Block_Collision(g_hammer_y, g_hammer_x + 7, TRUE);
		Block_Collision(g_hammer_y + 7, g_hammer_x + 7, TRUE);
		Block_Collision(g_hammer_y + 7, g_hammer_x, TRUE);
		Block_Collision(g_hammer_y + 7, g_hammer_x - 7, TRUE);
		Block_Collision(g_hammer_y, g_hammer_x - 7, TRUE);
		Block_Collision(g_hammer_y - 7, g_hammer_x - 7, TRUE);

		if(g_old_break_block_count != g_break_block_count)PlaySoundMem(BreakBGM, DX_PLAYTYPE_BACK, TRUE);

		if (!g_hit_hammer_flg)g_hammer_angle -= (10 * g_hammer_angle_direction);//つるはしが壊れないブロックに当たっていないならつるはしを投げた方向に回転させる
		else g_hammer_angle += (5 * g_hammer_angle_direction);//つるはしが壊れないブロックに当たった時つるはしを投げた方向と逆方向に回転する

		if (g_hammer_angle >= 360)g_hammer_angle = 0; //つるはしが一回転したら角度を0にする
		else if (g_hammer_angle <= 0)g_hammer_angle = 360;//つるはしが一回転したら角度を360にする

		if (g_hammer_y >= 800)//つるはしのｙ座標が800以上になったら
		{
			g_hammer_flg = HAMMER_NONE;//つるはしを消す
			for (int i = 0; i < 10; i++)
			{
				g_bom[i].hit_flg = TRUE; //g_bom[i].hit_flgをTRUEにする（FALSEだとつるはしで爆弾を攻撃しても起動しない）
			}
		}
	}
	else if (g_hammer_flg == HAMMER_CURSOR)
	{
		Block_Collision(g_cursory, g_cursorx, FALSE);//カーソルのブロックを攻撃する
		g_hammer_flg = HAMMER_NONE;
	}
}

void GameMain::Block_Collision(int a, int b, bool c)
{
	if ((a / 30) < MAP_HIGHT && (a / 30) >= 0) //マップの範囲内の
	{
		if ((b / 30) < g_stage_width && (b / 30) >= 0)//マップの範囲内の
		{
			if (MAP_DATA[a / 30][b / 30] >= 1 && MAP_DATA[a / 30][b / 30] <= 4)//ブロックに当たった時
			{
				if (c)//つるはしが投げられているとき
				{
					MAP_DATA[a / 30][b / 30] = 0, g_break_block_count++;//ブロックを一撃で壊し、ブロックのカウントをプラスする
					for (int i = 0; i < 10; i++)
					{ //↓ブロックに埋もれている爆弾に当たったら起動しないようにg_bom[i].hit_flgをFALSEにする（FALSEにすると攻撃しても爆弾が起動しない）
						if ((g_bom[i].y / 30 == a / 30) && (g_bom[i].x / 30 == b / 30) && (g_bom[i].flg == NOMAL))g_bom[i].hit_flg = FALSE;
					}
					
				}
				else if(g_cursor_flg)//つるはしが投げられていない（カーソル内のブロックに攻撃してる）とき
				{
					if (MAP_DATA[a / 30][b / 30] == 4)MAP_DATA[a / 30][b / 30] = 0, g_break_block_count++;//地面ブロックなら一撃で壊し、ブロックのカウントをプラスする
					else //地面ブロック以外なら
					{
						MAP_DATA[a / 30][b / 30]--;//一ずつダメージを与える
						if (MAP_DATA[a / 30][b / 30] == 0)g_break_block_count++;//ブロックが壊れたならブロックのカウントを増やす
					}
				}
				if ((g_break_block_count % 50) == 0) g_block_count++;//壊したブロック÷50の余りが0ならプレイヤーが使えるブロックの数が増える
			}
			else if(MAP_DATA[a / 30][b / 30] == 0 || MAP_DATA[a / 30][b / 30] == -1)//ブロックに当たってないとき
			{
				for (int i = 0; i < 10; i++)
				{   //↓爆弾に当たったら起動させる
					if ((g_bom[i].y / 30 == a / 30) && (g_bom[i].x / 30 == b / 30) && (g_bom[i].flg == NOMAL) && (g_bom[i].hit_flg == TRUE))g_bom[i].flg = ANGRY;
				}
			}
			else//壊せないブロックに当たった時
			{
				if (!g_hit_hammer_flg)//壊せないブロックに当たったのが初めてなら
				{
					g_hammer_orbit_y = 0, g_hammer_orbit_x = 0;//xの移動量もyの移動量も0にする
					g_hammer_x = g_old_hammer_x;//ｘをひとつ前の座標に戻す
					g_hammer_y = g_old_hammer_y;//ｙをひとつ前の座標に戻す
					g_hit_hammer_flg = TRUE;//壊せないブロックに当たったことにする
				}
				else g_hammer_flg = HAMMER_NONE; //壊せないブロックに当たったのが２度目なら、つるはしを消す
			}
		}
	}
}

void GameMain::Player_Sousa()
{
	if (g_player_x >= g_clear_x) g_game_state = 2;
	if (g_player_y >= 680)g_player_flg = DIE;
	if (g_player_flg == DIE)
	{
		if (--g_chara_life > 0)
		{
			if (g_player_x >= 2490)g_checkpoint_flg = TRUE;
			if(g_checkpoint_flg)g_player_x = 2230, g_player_y = 587;
			else g_player_x = 30, g_player_y = 550;
			g_player_flg = WALK;
		}
		else {
			StopSoundMem(StageBGM);
			StopSoundMem(StageBGM1);
			StopSoundMem(StageBGM2);
			SetScore(0, FALSE);
			SetGameState(4); //ゲームオーバーは、時間を加算しない
		}
	}

	if (AX < 0)g_direction = LEFT;
	else if (AX > 0)g_direction = RIGHT;

	if (BY != 0 || BX != 0)
	{
		g_old_cursor_BX = BX;
		g_old_cursor_BY = BY;
	}
	
	if (g_old_cursor_BY != 0)
	{
		if (g_old_cursor_BY < 0)g_cursory = Player_Hit_Up(g_player_y, 0) - BLOCK_SIZE;//上なら
		else g_cursory = Player_Hit_Under(g_player_y, 0) + BLOCK_SIZE;//下なら

		if (g_old_cursor_BX < 0)g_cursorx = g_player_x - BLOCK_SIZE;//左なら
		else if (g_old_cursor_BX > 0)g_cursorx = g_player_x + BLOCK_SIZE;//右なら
		else g_cursorx = g_player_x;//どこも向いてなかったら
	}
	else
	{
		g_cursory = g_player_y;
		if (g_old_cursor_BX > 0)g_cursorx = g_player_x + (PLAY_WIDTH_SIZE / 2) + BLOCK_SIZE;
		if (g_old_cursor_BX < 0)g_cursorx = g_player_x - (PLAY_WIDTH_SIZE / 2) - BLOCK_SIZE;
	}

	g_cursor_flg = TRUE;
	if ((g_cursory / 30 >= MAP_HIGHT) || (g_cursory < 0) || (g_cursorx / 30 >= g_stage_width) || (g_cursorx < 0))
	{
		g_cursor_flg = FALSE;
	}

	if (AX == 0 && AY == 0)//アイテム選択
	{
		if ((g_leftkey_flg) && (!g_old_leftkey_flg))
		{
			if (g_item_selection == 0)g_item_selection = 2;
			else g_item_selection--;
		}
		else if ((g_rightkey_flg) && (!g_old_rightkey_flg))
		{
			if (g_item_selection == 2)g_item_selection = 0;
			else g_item_selection++;
		}
	}
	
	if (BX != 0 || BY != 0)
	{
		if ((g_lkey_flg) && (!g_old_lkey_flg) && (g_hammer_flg == HAMMER_NONE))
		{
			if (BX <= 0)g_hammer_angle_direction = LEFT;
			else g_hammer_angle_direction = RIGHT;
			g_hammer_flg = HAMMER_FLY;
			g_hit_hammer_flg = FALSE;
			g_hammer_x = g_player_x, g_hammer_y = g_player_y;
			g_hammer_orbit_x = -(BX / 20), g_hammer_orbit_y = -(BY / 18);
			for (int i = 0; i < 10; i++)g_bom[i].hit_flg = TRUE;
		}
		else if ((g_rkey_flg) && (!g_old_rkey_flg) &&(g_item_selection == 2) && (g_bom_count > 0))
		{
			bool g_bom_count_flg = TRUE;
			for (int i = 0; i < 10; i++)
			{
				if ((g_bom[i].flg == NONE) && (g_bom_count_flg))
				{
					if (BX <= 0)g_bom[i].angle_direction = LEFT;
					else g_bom[i].angle_direction = RIGHT;
					g_bom[i].flg = FLY;
					g_bom[i].x = g_player_x, g_bom[i].y = g_player_y;
					g_bom[i].orbit_x = -(BX / 20), g_bom[i].orbit_y = -(BY / 18);
					g_bom_count--;
					g_bom_count_flg = FALSE;
				}
			}
		}
	}
	else if(g_cursor_flg)
	{
		if ((g_lkey_flg) && (!g_old_lkey_flg) && (g_hammer_flg == HAMMER_NONE))g_hammer_flg = HAMMER_CURSOR;
		else if ((g_rkey_flg) && (!g_old_rkey_flg) && (g_item_selection == 2) && (g_bom_count > 0))
		{
			bool g_bom_count_flg = FALSE;
			for (int i = 0; i < 10; i++)
			{
				if ((g_bom[i].flg == NONE) && (g_bom_count_flg))
				{
					if ((Get_MapData(g_cursory, g_cursorx) == 0) && (ITEM_DATA[g_cursory / 30][g_cursorx / 30] == 0))//ブロックもアイテムもなければ
					{
						g_bom[i].x = (g_cursorx / 30) * 30, g_bom[i].y = (g_cursory / 30) * 30; //爆弾を配置
						g_bom[i].flg = ANGRY;
						g_bom_count_flg = FALSE;
						g_bom_count--;
					}
				}
			}
		}
	}

	if ((g_rkey_flg) && (!g_old_rkey_flg))
	{
		if (g_item_selection == 1)
		{
			if ((g_block_count > 0) && (g_cursor_flg))
			{
				if ((MAP_DATA[g_cursory / 30][g_cursorx / 30] == 0) && (ITEM_DATA[g_cursory / 30][g_cursorx / 30] == 0))
				{
					MAP_DATA[g_cursory / 30][g_cursorx / 30] = 4;
					g_block_count--;
				}
			}
		}
	}
	if (g_hammer_flg  != HAMMER_NONE)Hammer();

	if (g_player_flg == WALK)Walk();
	else if (g_player_flg == JUMP)Jump();
	else Fall();
}

void  GameMain::Walk()
{
	if (AX != 0)
	{
		if (g_direction == RIGHT)g_player_x += 2;
		else g_player_x -= 2;
		if ((Get_MapData(g_player_y, Player_Hit_Front(g_player_x, 0)) > 0) || Player_Hit_Front(g_player_x, 0) < 0)g_player_x = ((g_player_x / BLOCK_SIZE) * BLOCK_SIZE) + (15 - (4 * g_direction));
		if (++g_image_time >= 7)
		{
			g_player_image_type++;
			if (g_player_image_type > 3)g_player_image_type = 0;
			g_image_time = 0;
		}
	}
	if ((Get_MapData(Player_Hit_Under(g_player_y, 1), Player_Hit_Front(g_player_x, 0)) <= 0) &&
		(Get_MapData(Player_Hit_Under(g_player_y, 1), Player_Hit_Back(g_player_x, 0)) <= 0) || (g_player_y > 600))
	{
		g_player_flg = FALL; //足元が空白なら状態をFALLにする
	}
	else if ((g_akey_flg) && !(g_old_akey_flg))
	{
		if ((Get_MapData(Player_Hit_Up(g_player_y, 1), Player_Hit_Front(g_player_x, 0)) <= 0) &&
			(Get_MapData(Player_Hit_Up(g_player_y, 1), Player_Hit_Back(g_player_x, 0)) <= 0))
		{
			g_move_speed_y = 50, g_player_flg = JUMP; //Bキーが押されたとき、足元が空白じゃなく、頭上が空白なら状態をJUMPにする
		}
	}
	//DrawFormatString(100, 100, 0xffffff, "walk");
}

void GameMain::Jump()
{
	if (!g_akey_flg && g_move_speed_y > 10)g_move_speed_y = 10;

	g_player_y -= (g_move_speed_y / 6); //プレイヤーのY軸を引く
	g_move_speed_y -= 2;

	if ((Get_MapData(Player_Hit_Up(g_player_y, 0), Player_Hit_Front(g_player_x, 0)) > 0) ||
		(Get_MapData(Player_Hit_Up(g_player_y, 0), Player_Hit_Back(g_player_x, 0)) > 0))
	{
		g_player_y = ((g_player_y / BLOCK_SIZE) * BLOCK_SIZE) + 12;
		g_move_speed_y = -5;
	}

	if (AX != 0)
	{
		if (g_direction == RIGHT)g_player_x += 1;
		else g_player_x -= 1;
	}

	if ((Get_MapData(Player_Hit_Up(g_player_y, 0), Player_Hit_Front(g_player_x, 0)) > 0) ||
		(Get_MapData(Player_Hit_Under(g_player_y, 0), Player_Hit_Front(g_player_x, 0)) > 0) ||
		(Get_MapData(Player_Hit_Up(g_player_y, 0), Player_Hit_Back(g_player_x, 0)) > 0) ||
		(Get_MapData(Player_Hit_Under(g_player_y, 0), Player_Hit_Back(g_player_x, 0)) > 0) ||
		(Player_Hit_Front(g_player_x, 0) < 0)) g_player_x = ((g_player_x / BLOCK_SIZE) * BLOCK_SIZE) + (15 - (4 * g_direction));

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
		(Get_MapData(Player_Hit_Under(g_player_y, 0), Player_Hit_Back(g_player_x, 0)) > 0) ||
		Player_Hit_Front(g_player_x, 0) < 0) g_player_x = ((g_player_x / BLOCK_SIZE) * BLOCK_SIZE) + (15 - (4 * g_direction));

	/*DrawFormatString(100, 100, 0xffffff, "fall");*/
}

int GameMain::Get_MapData(int y, int x)
{
	return MAP_DATA[y / BLOCK_SIZE][x / BLOCK_SIZE];
}

int GameMain::HitBoxPlayer(int px, int py, int ex, int ey, int psize, int esize, bool a)
{
	int sx1 = px - ((psize / 2) - 10);
	int sx2 = px + ((psize / 2) - 10);
	int sy1 = py - ((psize / 2) - 10);
	int sy2 = py + ((psize / 2) - 10);

	if (!a)
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
	if (g_direction == RIGHT) return (a + ((PLAY_WIDTH_SIZE / 2)) + b);
	else return (a - ((PLAY_WIDTH_SIZE / 2) + 1) - b);
}

int GameMain::Player_Hit_Back(int a, int b)
{
	if (g_direction == RIGHT) return (a - ((PLAY_WIDTH_SIZE / 2) + 1) - b);
	else return (a + ((PLAY_WIDTH_SIZE / 2)) + b);
}

int GameMain::Player_Hit_Under(int a, int b)
{
	return (a + (PLAY_HIGHT_SIZE / 2) + b);
}

int GameMain::Player_Hit_Up(int a, int b)
{
	return (a - (PLAY_HIGHT_SIZE / 2) - b);
}