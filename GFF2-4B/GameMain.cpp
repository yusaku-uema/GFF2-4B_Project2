#include"DxLib.h"
#include "GameMain.h"
#include"main.h"
#define _USE_MATH_DEFINES
#include<math.h>


/***********************************************
*  �Q�[������
************************************************/
void GameMain::Update()
{
	ChangeVolumeSoundMem(255 * 80 / 100, GetSounds(BreakBGM));
	Key();
	switch (g_game_state)
	{
	case 0://�X�e�[�W�I�����
		Update_Stage_Select();
		Draw_Stage_Select();
		break;
	case 1:
		if (!g_game_stop)
		{
			Player_Sousa(); //���@�̑���
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
*  ����������
************************************************/
void GameMain::Stage_Select_Init()
{
	FILE* fp = NULL;//�X�e�[�W�P�t�@�C���ǂݍ���

	if (fopen_s(&fp, "data/hiscore.txt", "r") != 0)//�X�e�[�W���Ƃ̃n�C�X�R�A�̃f�[�^
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
	SetGameState(2); //�Q�[�����C���ڍs
}
void GameMain::Draw_Stage_Select()
{
	DrawGraph(140, 10, g_stage_select_image, TRUE);
	DrawCircle(460, 465, 10, 0xff0000, TRUE);
	DrawCircle(675, 395, 10, 0xff0000, TRUE);
	DrawCircle(900, 265, 10, 0xff0000, TRUE);
	
	DrawRotaGraph(g_player_x, g_player_y, 1.0, M_PI / 180 * 0, GetArrayImages(Player_Images, g_player_image_type), TRUE, FALSE);

	int hi_score = g_hi_score[g_stage]; //�X�R�A�ی�
	int hiscore_x = 300;//���Ԃ̕`��ʒu
	int Calc = 10000;//�\������

	while (Calc > 0)
	{
		DrawGraph(hiscore_x, 150, g_stage_select_number_image[hi_score / Calc],TRUE);//���R�A�\��
		hi_score -= (hi_score / Calc) * Calc;
		Calc /= 10;
		hiscore_x += 45;
	}
	DrawGraph(870,487, g_stage_select_number_image[g_stage + 1], TRUE);//���R�A�\��
}
void GameMain::Update_Stage_Select()
{
	if (CheckSoundMem(BGMStage) != 1) {
		BGMStage = LoadSoundMem("BGM/BGMStage.mp3");
		ChangeVolumeSoundMem(255 * 25 / 100, BGMStage); //BGM���ʒ��� 
		PlaySoundMem(BGMStage, DX_PLAYTYPE_LOOP, TRUE); //SE�Đ�
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
*  ����������
************************************************/
void GameMain::GameMain_Init()
{
	FILE* fp_m = NULL;//�X�e�[�W�P�t�@�C���ǂݍ���
	FILE* fp_i = NULL;
	ClearTime = FALSE;
	ClearStop = FALSE;

	switch (g_stage)
	{
	case 0://�X�e�[�W1������
		g_player_x = 30;
		g_player_y = 550;
		g_stage_width = 150;
		g_stage_scroll_x = 3220;
		g_clear_x = 4477;
		g_bom_count = 0;

		ChangeVolumeSoundMem(255 * 25 / 100, StageBGM); //BGM���ʒ��� 
		PlaySoundMem(StageBGM, DX_PLAYTYPE_LOOP, TRUE); //SE�Đ�

		if (fopen_s(&fp_i, "data/item1.txt", "r") != 0)//�A�C�e���f�[�^
		{
			throw "Data/item1.txt";
		}
		if (fopen_s(&fp_m, "data/map1.txt", "r") != 0)//�}�b�v�f�[�^
		{
			throw "Data/map1.txt";
		}
		break;

	case 1://�X�e�[�W1������
		g_player_x = 30;
		g_player_y = 550;
		g_stage_width = 150;
		g_stage_scroll_x = 3220;
		g_clear_x = 4477;
		g_bom_count = 0;

		ChangeVolumeSoundMem(255 * 25 / 100, StageBGM1); //BGM���ʒ��� 
		PlaySoundMem(StageBGM1, DX_PLAYTYPE_LOOP, TRUE); //SE�Đ�

		if (fopen_s(&fp_i, "data/item2.txt", "r") != 0)//�A�C�e���f�[�^
		{
			throw "Data/item2.txt";
		}		
		if (fopen_s(&fp_m, "data/map2.txt", "r") != 0)//�}�b�v�f�[�^
		{
			throw "Data/map2.txt";
		}
		break;

	case 2://�X�e�[�W2������
		g_player_x = 30;
		g_player_y = 550;
		g_stage_width = 150;
		g_stage_scroll_x = 3220;
		g_clear_x = 4477;
		g_bom_count = 0;

		ChangeVolumeSoundMem(255 * 25 / 100, StageBGM2); //BGM���ʒ��� 
		PlaySoundMem(StageBGM2, DX_PLAYTYPE_LOOP, TRUE); //SE�Đ�

		if (fopen_s(&fp_i, "data/item3.txt", "r") != 0)//�A�C�e���f�[�^
		{
			throw "Data/item3.txt";
		}
		if (fopen_s(&fp_m, "data/map3.txt", "r") != 0)//�}�b�v�f�[�^
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
	TimeLimit = 200;//��������
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

	BreakBGM = LoadSoundMem("BGM/breakblock1.mp3");//�j��BGM
	TimeLimitImages = LoadGraph("images/Timeer.png"); //���Ԑ�������
	g_blowing_images = LoadGraph("images/fuki.png"); //�����������̉摜
	ScoreImages = LoadGraph("images/Score.png"); //�X�R�A�����摜
	LoadDivGraph("images/Timemo.png", 10, 10, 1, 20, 30, g_NumberImage);
	LoadDivGraph("images/Timemo1.png", 10, 10, 1, 40, 60, g_NumberImage1);
	LimitImages = LoadGraph("images/Limet.png");

	for(int i = 0; i < 10; i++)//�A�C�e���̏�����
	{
		g_item[i].x = 0;
		g_item[i].y = 0;
		g_item[i].point = 0;
		g_item[i].flg = FALSE;
		g_item[i].type = 0;

		g_bom[i].flg = NONE;//���e�̏�����
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
			if (MAP_DATA[i][j] == 3)MAP_DATA[i][j] = GetRand(2) + 1;//�u���b�N�������_����
		}
	}
	Setstage(g_stage);
}

/***********************************************
* ��������
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
	if (g_player_x >= g_clear_x) //�N���A����
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
	GetJoypadAnalogInput(&AX, &AY, DX_INPUT_PAD1); // ���͏�Ԃ��擾
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
		if (TimeLimit <= 100 && TimeLimit >= 95 || TimeLimit <= 50 && TimeLimit >= 45 || TimeLimit <= 5) //�c�莞�Ԃ�傫���\��
		{
			DrawGraph(250, 50, LimitImages, TRUE); //�c�莞�Ԃ̕����`��

			TmpTime = TimeLimit; //�������ԕی�
			int TimeX = 550;//���Ԃ̕`��ʒu
			int Calc = 10000;//�\������

			while (Calc > 0)
			{
				if (Calc <= 100)DrawGraph(TimeX, 50, g_NumberImage1[TmpTime / Calc], FALSE);//���ԕ\��
				TmpTime -= (TmpTime / Calc) * Calc;
				Calc /= 10;
				TimeX += 50;
			}
		}
	}
}

void GameMain::Ui()
{
	DrawBox(0, 630, 1280, 720, 0x000000, TRUE); //UI�̘g
	DrawBox(0, 630, 1280, 720, 0xFFFFFF, FALSE);//UI�̘g
	DrawBox(0, 0, 1280, 630, 0xFFFFFF, FALSE);//UI�̘g
	DrawGraph(5, 634, ScoreImages, FALSE);
	DrawGraph(250, 634, TimeLimitImages, FALSE); //�c�莞�Ԃ̕����`��

	for (int i = 0; i < g_chara_life; i++)
	{
		DrawGraph(1000 + (60 * (i + 1)), 630, GetArrayImages(Life_Images, 0), TRUE);
	}

	TmpTime = TimeLimit; //�������ԕی�
	TmpScore = GetScore(); //�X�R�A�ی�
	int TimeX = 250;//���Ԃ̕`��ʒu
	int ScoreX = 35;//�X�R�A�̕`��ʒu
	int Calc = 10000;//�\������
	
		while (Calc > 0)
		{
			if (Calc <= 100)DrawGraph(TimeX, 675, g_NumberImage[TmpTime / Calc], TRUE);//���ԕ\��
			DrawGraph(ScoreX, 675, g_NumberImage[TmpScore / Calc], FALSE);//���R�A�\��
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
		size[i] = 0.6; //�A�C�e���摜�̑傫����0.6�{�ɂ���
		if (g_item_selection == i)size[i] = 0.8;//�A�C�e�����I������Ă���A�C�e���Ȃ�摜�̑傫����0.8�{����
		DrawRotaGraph(530 + (110 * i), 675, size[i], 0, GetArrayImages(Item_cursor, i), TRUE, FALSE);//�A�C�e���摜�̕\��
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
		DrawFormatString(400, 300, GetColor(255, 255, 255), "A�{�^���ŃX�e�[�W��蒼��\nB�{�^���ŃX�e�[�W�I��\nSTART�{�^���Ń|�[�Y����");
	}
}

void GameMain::Bom()
{
	bool g_bom_count_flg = FALSE;
	if (g_bom_count > 0)g_bom_count_flg = TRUE; //�莝�����e���P�ł������g_bom_count_flg��TRUE�ɂ���

	for (int i = 0; i < 10; i++)
	{
		if (g_bom[i].y > 700) g_bom[i].flg = NONE; //���e����ʊO�ɗ�������NONE�ɂ���

		if (g_bom[i].flg == NOMAL)//NOMAL��Ԃ̎�
		{
			if (HitBoxPlayer(g_player_x, g_player_y, g_bom[i].x, g_bom[i].y, BLOCK_SIZE, BLOCK_SIZE, TRUE))//���e���v���C���[�ɓ�����Ǝ���
			{
				g_bom[i].flg = NONE;//��Ԃ�NONE�i������j�ɂȂ�
				g_bom_count++;//�g�p�ł���{������������
			}
		}
		if ((g_bom[i].flg == ANGRY) || (g_bom[i].flg == FLY))//���e��ANGRY��Ԃ̎�
		{
			if(g_bom[i].flg == ANGRY)g_bom[i].time--;//�J�E���g�_�E�����n�܂�
			else
			{
				g_bom[i].y -= (g_bom[i].orbit_y / 3);//y���W�̕ύX
				g_bom[i].x -= (g_bom[i].orbit_x / 4);//x���W�̕ύX
				g_bom[i].orbit_y -= 1;//�����W�̕ύX�ʂ����炷
				g_bom[i].angle -= (10 * g_bom[i].angle_direction);
				if (g_bom[i].angle >= 360)g_bom[i].angle = 0; //���e�����]������p�x��0�ɂ���
				else if (g_bom[i].angle <= 0)g_bom[i].angle = 360;//���e�����]������p�x��360�ɂ���
				if (Get_MapData(g_bom[i].y, g_bom[i].x) > 0)g_bom[i].time = 0;
			}
			if (g_bom[i].time <= 0)//�J�E���g�_�E����0�ɂȂ�����
			{
				for (int a = (g_bom[i].y - 90) / 30; a < (g_bom[i].y + 120) / 30; a++)//�c7�}�X
				{
					for (int j = (g_bom[i].x - 90) / 30; j < (g_bom[i].x + 120) / 30; j++)//��7�}�X��
					{
						if ((a < MAP_HIGHT && a >= 0) && (j < g_stage_width && j >= 0))//�}�b�v����
						{
							if (MAP_DATA[a][j] != 6 && MAP_DATA[a][j] > 0)
							{
								MAP_DATA[a][j] = 0;//�U�ԈȊO�̃u���b�N������
								g_break_block_count++;
								if ((g_break_block_count % 50) == 0) g_block_count++;
							}
						}
						if (((Player_Hit_Back(g_player_x, -5) / 30 == j) || (Player_Hit_Front(g_player_x, -5) / 30 == j)) &&
							((Player_Hit_Under(g_player_y, -5) / 30 == a) || (Player_Hit_Up(g_player_y, -5) / 30 == a)))
						{
							g_player_flg = DIE;//�����͈̔͂Ƀv���C���[�������玀��
						}
					}
				}
				g_bom[i].time = 300;//�^�C����300�ɂ���
				g_bom[i].flg = NONE;//���e�̏�Ԃ�NONE(�Ȃ�)�ɂ���
			}
		}
		if(g_bom[i].flg != NONE && g_bom[i].flg != FLY)//���e�̏�Ԃ�NONE�ȊO�̎�
		{
			if (Get_MapData(g_bom[i].y + BLOCK_SIZE, g_bom[i].x) <= 0)//���e�̉��Ƀu���b�N���Ȃ�������
			{
				if (Get_MapData(g_bom[i].y, g_bom[i].x) <= 0)g_bom[i].y++; //���e�����܂��ĂȂ���Δ��e�𗎂Ƃ�
			}
			else g_bom[i].y = (g_bom[i].y / BLOCK_SIZE) * BLOCK_SIZE; //���e�̉��Ƀu���b�N���������甚�e��y���𐮂���

			if ((g_bom[i].y - 1) / 30 < MAP_HIGHT)ITEM_DATA[(g_bom[i].y - 1) / 30][g_bom[i].x / 30] = 0;//���e�����������ITEM_DATA��0�ɂ���i0����Ȃ��ƃv���C���[���u���b�N�������Ȃ��j
			if (g_bom[i].y / 30 < MAP_HIGHT)ITEM_DATA[g_bom[i].y / 30][g_bom[i].x / 30] = 4;//���e������ʒu��ITEM_DATA�ɐ���������i�A�C�e���̏�Ƀu���b�N���d�˂Ȃ��悤�Ɂj
			if ((g_bom[i].y + 29) / 30 < MAP_HIGHT)ITEM_DATA[(g_bom[i].y + 29) / 30][g_bom[i].x / 30] = 4;//���e������ʒu��ITEM_DATA�ɐ���������i�A�C�e���̏�Ƀu���b�N���d�˂Ȃ��悤�Ɂj
		}
	}
}

void  GameMain::Item()
{
	if (g_player_x >= 600)//�v���C���[��x���W��600�ȏ�Ȃ�
	{
		if(g_player_x >= g_stage_scroll_x + 600)g_scroll_x = g_stage_scroll_x;//�v���C���[��x���W��3820�ȏ�Ȃ��ʃX�N���[����x���W��3220�ɌŒ肷��i�X�e�[�W�[�ɗ������߁j
		else g_scroll_x = g_player_x - 600;//�v���C���[��x���W��3820�����Ȃ��ʂ��X�N���[��������
	}
	else g_scroll_x = 0;//�v���C���[��x���W��600�����Ȃ��ʃX�N���[�����Ȃ�

	
	for (int i = 0; i < 10; i++)
	{
		if (g_item[i].flg)//�A�C�e�����X�e�[�W��ɂ���Ȃ�
		{
			if (HitBoxPlayer(g_player_x, g_player_y, g_item[i].x, g_item[i].y, BLOCK_SIZE, BLOCK_SIZE, TRUE))//�A�C�e�����v���C���[�ɓ��������Ȃ�
			{
				g_item[i].flg = FALSE;//�A�C�e�����X�e�[�W�ォ�����
				if (g_item[i].type == 1)g_key_count++;//�A�C�e���^�C�v���P�Ȃ献�̃J�E���g�𑝂₷
				if (g_item[i].type == 2)g_bag_count++;//�A�C�e���^�C�v���Q�Ȃ�܂̃J�E���g�𑝂₷
			}
			if (MAP_DATA[(g_item[i].y + BLOCK_SIZE) / 30][g_item[i].x / 30] <= 0)//�A�C�e���̐^���Ƀu���b�N���Ȃ����
			{
				if (MAP_DATA[g_item[i].y / 30][g_item[i].x / 30] <= 0) g_item[i].y++;//�A�C�e�����u���b�N�Ȃǂɖ��܂��ĂȂ���΃A�C�e����y���W���{����
			}
			else g_item[i].y = (g_item[i].y / BLOCK_SIZE) * BLOCK_SIZE;//�A�C�e���̐^���Ƀu���b�N������Ȃ�A�C�e����y���W�𐮂���

			if ((g_item[i].y - 1) / 30 < MAP_HIGHT)ITEM_DATA[(g_item[i].y - 1) / 30][g_item[i].x / 30] = 0;//�A�C�e�������������ITEM_DATA��0�ɂ���i0����Ȃ��ƃv���C���[���u���b�N�������Ȃ��j
			if (g_item[i].y / 30 < MAP_HIGHT)ITEM_DATA[g_item[i].y / 30][g_item[i].x / 30] = g_item[i].type;//�A�C�e��������ʒu��ITEM_DATA�ɐ���������i�A�C�e���̏�Ƀu���b�N���d�˂Ȃ��悤�Ɂj
			if ((g_item[i].y + 29) / 30 < MAP_HIGHT)ITEM_DATA[(g_item[i].y + 29) / 30][g_item[i].x / 30] = g_item[i].type;//�A�C�e��������ʒu��ITEM_DATA�ɐ���������i�A�C�e���̏�Ƀu���b�N���d�˂Ȃ��悤�Ɂj
		}
	}
}

void GameMain::Hammer()
{
	if (g_hammer_flg == HAMMER_FLY)//��͂����������Ă��鎞
	{
		g_old_hammer_x = g_hammer_x;//���O�̂�͂���x���W������
		g_old_hammer_y = g_hammer_y;//���O�̂�͂���y���W������

		g_hammer_y -= (g_hammer_orbit_y / 3);//y���W�̕ύX
		g_hammer_x -= (g_hammer_orbit_x / 4);//x���W�̕ύX
		g_hammer_orbit_y -= 1;//�����W�̕ύX�ʂ����炷

		int g_old_break_block_count = g_break_block_count;
		//��͂��̎������
		Block_Collision(g_hammer_y - 7, g_hammer_x, TRUE);
		Block_Collision(g_hammer_y - 7, g_hammer_x + 7, TRUE);
		Block_Collision(g_hammer_y, g_hammer_x + 7, TRUE);
		Block_Collision(g_hammer_y + 7, g_hammer_x + 7, TRUE);
		Block_Collision(g_hammer_y + 7, g_hammer_x, TRUE);
		Block_Collision(g_hammer_y + 7, g_hammer_x - 7, TRUE);
		Block_Collision(g_hammer_y, g_hammer_x - 7, TRUE);
		Block_Collision(g_hammer_y - 7, g_hammer_x - 7, TRUE);

		if(g_old_break_block_count != g_break_block_count)PlaySoundMem(BreakBGM, DX_PLAYTYPE_BACK, TRUE);

		if (!g_hit_hammer_flg)g_hammer_angle -= (10 * g_hammer_angle_direction);//��͂������Ȃ��u���b�N�ɓ������Ă��Ȃ��Ȃ��͂��𓊂��������ɉ�]������
		else g_hammer_angle += (5 * g_hammer_angle_direction);//��͂������Ȃ��u���b�N�ɓ�����������͂��𓊂��������Ƌt�����ɉ�]����

		if (g_hammer_angle >= 360)g_hammer_angle = 0; //��͂������]������p�x��0�ɂ���
		else if (g_hammer_angle <= 0)g_hammer_angle = 360;//��͂������]������p�x��360�ɂ���

		if (g_hammer_y >= 800)//��͂��̂����W��800�ȏ�ɂȂ�����
		{
			g_hammer_flg = HAMMER_NONE;//��͂�������
			for (int i = 0; i < 10; i++)
			{
				g_bom[i].hit_flg = TRUE; //g_bom[i].hit_flg��TRUE�ɂ���iFALSE���Ƃ�͂��Ŕ��e���U�����Ă��N�����Ȃ��j
			}
		}
	}
	else if (g_hammer_flg == HAMMER_CURSOR)
	{
		Block_Collision(g_cursory, g_cursorx, FALSE);//�J�[�\���̃u���b�N���U������
		g_hammer_flg = HAMMER_NONE;
	}
}

void GameMain::Block_Collision(int a, int b, bool c)
{
	if ((a / 30) < MAP_HIGHT && (a / 30) >= 0) //�}�b�v�͈͓̔���
	{
		if ((b / 30) < g_stage_width && (b / 30) >= 0)//�}�b�v�͈͓̔���
		{
			if (MAP_DATA[a / 30][b / 30] >= 1 && MAP_DATA[a / 30][b / 30] <= 4)//�u���b�N�ɓ���������
			{
				if (c)//��͂����������Ă���Ƃ�
				{
					MAP_DATA[a / 30][b / 30] = 0, g_break_block_count++;//�u���b�N���ꌂ�ŉ󂵁A�u���b�N�̃J�E���g���v���X����
					for (int i = 0; i < 10; i++)
					{ //���u���b�N�ɖ�����Ă��锚�e�ɓ���������N�����Ȃ��悤��g_bom[i].hit_flg��FALSE�ɂ���iFALSE�ɂ���ƍU�����Ă����e���N�����Ȃ��j
						if ((g_bom[i].y / 30 == a / 30) && (g_bom[i].x / 30 == b / 30) && (g_bom[i].flg == NOMAL))g_bom[i].hit_flg = FALSE;
					}
					
				}
				else if(g_cursor_flg)//��͂����������Ă��Ȃ��i�J�[�\�����̃u���b�N�ɍU�����Ă�j�Ƃ�
				{
					if (MAP_DATA[a / 30][b / 30] == 4)MAP_DATA[a / 30][b / 30] = 0, g_break_block_count++;//�n�ʃu���b�N�Ȃ�ꌂ�ŉ󂵁A�u���b�N�̃J�E���g���v���X����
					else //�n�ʃu���b�N�ȊO�Ȃ�
					{
						MAP_DATA[a / 30][b / 30]--;//�ꂸ�_���[�W��^����
						if (MAP_DATA[a / 30][b / 30] == 0)g_break_block_count++;//�u���b�N����ꂽ�Ȃ�u���b�N�̃J�E���g�𑝂₷
					}
				}
				if ((g_break_block_count % 50) == 0) g_block_count++;//�󂵂��u���b�N��50�̗]�肪0�Ȃ�v���C���[���g����u���b�N�̐���������
			}
			else if(MAP_DATA[a / 30][b / 30] == 0 || MAP_DATA[a / 30][b / 30] == -1)//�u���b�N�ɓ������ĂȂ��Ƃ�
			{
				for (int i = 0; i < 10; i++)
				{   //�����e�ɓ���������N��������
					if ((g_bom[i].y / 30 == a / 30) && (g_bom[i].x / 30 == b / 30) && (g_bom[i].flg == NOMAL) && (g_bom[i].hit_flg == TRUE))g_bom[i].flg = ANGRY;
				}
			}
			else//�󂹂Ȃ��u���b�N�ɓ���������
			{
				if (!g_hit_hammer_flg)//�󂹂Ȃ��u���b�N�ɓ��������̂����߂ĂȂ�
				{
					g_hammer_orbit_y = 0, g_hammer_orbit_x = 0;//x�̈ړ��ʂ�y�̈ړ��ʂ�0�ɂ���
					g_hammer_x = g_old_hammer_x;//�����ЂƂO�̍��W�ɖ߂�
					g_hammer_y = g_old_hammer_y;//�����ЂƂO�̍��W�ɖ߂�
					g_hit_hammer_flg = TRUE;//�󂹂Ȃ��u���b�N�ɓ����������Ƃɂ���
				}
				else g_hammer_flg = HAMMER_NONE; //�󂹂Ȃ��u���b�N�ɓ��������̂��Q�x�ڂȂ�A��͂�������
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
			SetGameState(4); //�Q�[���I�[�o�[�́A���Ԃ����Z���Ȃ�
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
		if (g_old_cursor_BY < 0)g_cursory = Player_Hit_Up(g_player_y, 0) - BLOCK_SIZE;//��Ȃ�
		else g_cursory = Player_Hit_Under(g_player_y, 0) + BLOCK_SIZE;//���Ȃ�

		if (g_old_cursor_BX < 0)g_cursorx = g_player_x - BLOCK_SIZE;//���Ȃ�
		else if (g_old_cursor_BX > 0)g_cursorx = g_player_x + BLOCK_SIZE;//�E�Ȃ�
		else g_cursorx = g_player_x;//�ǂ��������ĂȂ�������
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

	if (AX == 0 && AY == 0)//�A�C�e���I��
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
					if ((Get_MapData(g_cursory, g_cursorx) == 0) && (ITEM_DATA[g_cursory / 30][g_cursorx / 30] == 0))//�u���b�N���A�C�e�����Ȃ����
					{
						g_bom[i].x = (g_cursorx / 30) * 30, g_bom[i].y = (g_cursory / 30) * 30; //���e��z�u
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
		g_player_flg = FALL; //�������󔒂Ȃ��Ԃ�FALL�ɂ���
	}
	else if ((g_akey_flg) && !(g_old_akey_flg))
	{
		if ((Get_MapData(Player_Hit_Up(g_player_y, 1), Player_Hit_Front(g_player_x, 0)) <= 0) &&
			(Get_MapData(Player_Hit_Up(g_player_y, 1), Player_Hit_Back(g_player_x, 0)) <= 0))
		{
			g_move_speed_y = 50, g_player_flg = JUMP; //B�L�[�������ꂽ�Ƃ��A�������󔒂���Ȃ��A���オ�󔒂Ȃ��Ԃ�JUMP�ɂ���
		}
	}
	//DrawFormatString(100, 100, 0xffffff, "walk");
}

void GameMain::Jump()
{
	if (!g_akey_flg && g_move_speed_y > 10)g_move_speed_y = 10;

	g_player_y -= (g_move_speed_y / 6); //�v���C���[��Y��������
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
	g_player_y -= (g_move_speed_y / 6); //�v���C���[�𗎂Ƃ�
	if (g_move_speed_y >= -35)g_move_speed_y -= 2;

	if ((Get_MapData(Player_Hit_Under(g_player_y, 0), Player_Hit_Front(g_player_x, 0)) > 0) ||
		(Get_MapData(Player_Hit_Under(g_player_y, 0), Player_Hit_Back(g_player_x, 0)) > 0)) //�n�ʂɓ���������
	{
		if (g_player_y <= 600)//��ʓ��Ȃ�
		{
			g_player_y = ((g_player_y / BLOCK_SIZE) * BLOCK_SIZE) + 17;//�v���C���[��y���𐮂���
			g_move_speed_y = 0;
			g_player_flg = WALK;//�v���C���[��flg��WAKL�ɂ���
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

	//��`���d�Ȃ��Ă���Γ�����
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