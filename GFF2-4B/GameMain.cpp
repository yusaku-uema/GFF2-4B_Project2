#include"DxLib.h"
#include "GameMain.h"
#include"main.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"Player.h"


/***********************************************
*  ����������
************************************************/
void GameMain::GameMain_Init()
{

	g_player_x = 30, g_player_y = 550;
	g_hammer_power = 0;
	g_scroll_x = 0;
	g_block_count = 0;
	g_item_selection = 0;
	g_score = 0;
	fps_cunt = 0;
	TimeLimit = 200;//��������
	g_player_image_type = 0;


	//�t�@�C��
	FILE* fp = NULL;
	if (fopen_s(&fp, "data/item1.txt", "r") != 0)
	{
		throw "Data/item1.txt";
	}
	//�A�C�e���f�[�^
	for (int i = 0; i < MAP_HIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			fscanf_s(fp, "%2d", &ITEM_DATA[i][j]);
		}
	}
	fclose(fp);
	fp = NULL;

	if (fopen_s(&fp, "data/map1.txt", "r") != 0)
	{
		throw "Data/map1.txt";
	}
	//�A�C�e���f�[�^
	for (int i = 0; i < MAP_HIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			fscanf_s(fp, "%2d", &MAP_DATA_INIT[i][j]);
		}
	}
	fclose(fp);
	fp = NULL;


	g_direction = RIGHT;
	g_bkey_flg = FALSE;
	g_akey_flg = FALSE;
	g_xkey_flg = FALSE;
	g_lkey_flg = FALSE;
	g_rkey_flg = FALSE;
	g_player_flg = WALK;
	g_break_block_count = 0;
	g_bom_count = 0;

	for (int i = 0; i < 5; i++)
	{
		g_item[i].x = 0;
		g_item[i].y = 0;
		g_item[i].point = 0;
		g_item[i].flg = FALSE;
		g_item[i].type = 0;
	}

	int g_item_count = 0;

	for (int i = 0; i < MAP_HIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (ITEM_DATA[i][j] > 0)
			{
				g_item[g_item_count].x = j * 30;
				g_item[g_item_count].y = i * 30;
				g_item[g_item_count].point = 100;
				g_item[g_item_count].flg = TRUE;
				if (ITEM_DATA[i][j] == 1)g_item[g_item_count].type = 1;
				if (ITEM_DATA[i][j] == 2)g_item[g_item_count].type = 2;
				if (ITEM_DATA[i][j] == 3)g_item[g_item_count].type = 3;
				g_item_count++;
			}
			MAP_DATA[i][j] = MAP_DATA_INIT[i][j];
			if (MAP_DATA[i][j] == 3)MAP_DATA[i][j] = GetRand(2) + 1;
			//MAP_DATA[i][j] = 3/*GetRand(2) + 1*/;
			//if (i > 17) MAP_DATA[i][j] = 4;
			//else if (j < 5 && j > 2) MAP_DATA[i][j] = 0;
		}
	}

	SetGameState(2); //�Q�[�����C���ڍs
}


/***********************************************
*  �Q�[������
************************************************/
void GameMain::Update()
{
	Key();
	Draw_Item();
	Stage();
	Player_Sousa(); //���@�̑���
	Ui();
	Draw();
}

/***********************************************
* ��������
************************************************/
void GameMain::Draw() 
{
	if (++fps_cunt % 60 == 0) {
		--TimeLimit;
	}
	if (TimeLimit <= 0)
	{
		SetGameState(4);
	}

}


void GameMain:: Key()
{
	GetJoypadAnalogInput(&AX, &AY, DX_INPUT_PAD1); // ���͏�Ԃ��擾
	g_old_bkey_flg = g_bkey_flg;
	g_old_akey_flg = g_akey_flg;
	g_old_xkey_flg = g_xkey_flg;
	g_old_lkey_flg = g_lkey_flg;
	g_old_rkey_flg = g_rkey_flg;
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
	DrawBox(0, 630, 1280, 720, 0x000000, TRUE); //UI�̘g
	DrawBox(0, 630, 1280, 720, 0xFFFFFF, FALSE);//UI�̘g
	DrawBox(0, 0, 1280, 630, 0xFFFFFF, FALSE);//UI�̘g

	DrawFormatString(15, 634, 0xffffff, "Score");
	DrawFormatString(200, 634, 0xffffff, "TimeLimit");
	SetFontSize(50);
	DrawFormatString(15, 665, 0xffffff, "%06d", g_score);
	DrawFormatString(200, 665, 0xffffff, "%d", TimeLimit);

	int a = (1280 - (110 * (g_stage_item_quantity - 1))) / 2;
	float size[3];
	DrawFormatString(100, 0, 0xffffff, "%d = block_count, %d = break block", g_block_count, g_break_block_count);
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
	//DrawGraph(g_scroll_x / -7, 0, g_haikei_image, TRUE);
	DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
	if (g_player_x >= 600)g_scroll_x = g_player_x - 600;
	else g_scroll_x = 0;

	for (int i = 0; i < 10; i++)
	{
		if (g_item[i].flg == TRUE)
		{
			if (HitBoxPlayer(g_player_x, g_player_y, &g_item[i]))
			{
				g_item[i].flg = FALSE;
				if (g_item[i].type == 3)g_bom_count++;
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
			if (MAP_DATA[g_cursory / 30][g_cursorx / 30] == 0)
			{
				MAP_DATA[g_cursory / 30][g_cursorx / 30] = 4;
				g_block_count--;
			}
		}
	}
	if (g_item_selection == 2)//�A�C�e���g�p�i���e�j
	{
		/*if (g_bom_count > 0)
		{*/
		for (int i = 0; i < MAP_HIGHT; i++)//��ʓ���
		{
			for (int j = g_scroll_x / 30; j < (g_scroll_x / 30) + (1280 / 30); j++)//��ʓ���
			{
				if (MAP_DATA[i][j] <= 3 && MAP_DATA[i][j] > 0)//�󂹂�u���b�N��
				{
					MAP_DATA[i][j] --;//�_���[�W����^����
					if (MAP_DATA[i][j] == 0)//�u���b�N����ꂽ��
					{
						//g_score += 5;
						g_break_block_count++;
						if ((g_break_block_count % 50) == 0) g_block_count++;
					}
				}

			}
		}
		//g_bom_count--;
	//}
	}
}

void GameMain::Hammer()
{
	if (g_hammer_flg == FALSE)//�n���}�[���g���ĂȂ��Ƃ�
	{
		if (AX != 0 || AY != 0)//�X�e�B�b�N�����삳��Ă���
		{
			if (AY >= 0)
			{
				g_hammer_speed_x = (AX / 20);
				g_hammer_speed_y = (AY / 18);
				g_hammer_x = g_player_x;
				g_hammer_y = g_player_y;

				if (g_bkey_flg) //�p�x�𒲐�����B�{�^���������ꂽ�Ƃ�
				{
					g_hammer_flg = TRUE; // b�{�^���������ꂽ��
					g_hammer_power = (g_hammer_power / (50 / 3)) + 1;
					if (g_hammer_power == 4)g_hammer_power = 3;
					g_hammer_angle = 0;
				}
				else //���X�e�B�b�N�Ŋp�x�𒲐����Ă���Ƃ���͂��̋O�����`�����
				{
					while (g_hammer_y < 720)
					{
						g_hammer_y -= (g_hammer_speed_y / 3);
						g_hammer_x -= (g_hammer_speed_x / 3);

						g_hammer_speed_y -= 1;

						DrawCircle(g_hammer_x - g_scroll_x, g_hammer_y, 3, 0xffffff, false);
					}

					if (g_hammer_power < 50)g_hammer_power++; //�p���[�Q�[�W�𓮂���
					else g_hammer_power = 0; //�p���[�Q�[�W��50���܂�����0�ɂ���

					DrawBox((g_player_x - 25) - g_scroll_x, g_player_y + 20, ((g_player_x - 25) + g_hammer_power) - g_scroll_x, (g_player_y + 20) + 20, 0xf00fff, TRUE);
					DrawBox((g_player_x - 25) - g_scroll_x, g_player_y + 20, ((g_player_x - 25) + 50) - g_scroll_x, (g_player_y + 20) + 20, 0xffffff, FALSE);
				}
			}
		}
		else //�X�e�B�b�N�𓮂����ĂȂ��Ƃ�
		{
			if ((g_bkey_flg == TRUE) && (g_old_bkey_flg == FALSE))//B�{�^���������ꂽ��
			{
				if (MAP_DATA[g_cursory / 30][g_cursorx / 30] == 4)
				{
					MAP_DATA[g_cursory / 30][g_cursorx / 30] = 0;
					//g_score += 5;
					g_break_block_count++;//�J�[�\���̃u���b�N���󂷁i�n�ʃu���b�N�Ȃ�ꔭ�ŉ󂷁j
					if ((g_break_block_count % 50) == 0) g_block_count++;
				}
				else if (MAP_DATA[g_cursory / 30][g_cursorx / 30] > 0 && MAP_DATA[g_cursory / 30][g_cursorx / 30] < 5)
				{
					MAP_DATA[g_cursory / 30][g_cursorx / 30]--;//���̑��̃u���b�N�Ȃ�_���[�W���ꂸ������
					if (MAP_DATA[g_cursory / 30][g_cursorx / 30] == 0)
					{
						//g_score += 5;
						g_break_block_count++;
						if ((g_break_block_count % 50) == 0) g_block_count++;
					}
				}
			}
		}
	}
	else// ��͂��𓊂��Ă���Ƃ�
	{


		//Block_Collision(g_hammer_y, g_hammer_x);
		Block_Collision(g_hammer_y - 7, g_hammer_x);
		Block_Collision(g_hammer_y - 7, g_hammer_x + 7);
		Block_Collision(g_hammer_y, g_hammer_x + 7);
		Block_Collision(g_hammer_y + 7, g_hammer_x + 7);
		Block_Collision(g_hammer_y + 7, g_hammer_x);
		Block_Collision(g_hammer_y + 7, g_hammer_x - 7);
		Block_Collision(g_hammer_y, g_hammer_x - 7);
		Block_Collision(g_hammer_y - 7, g_hammer_x - 7);

		g_hammer_y -= (g_hammer_speed_y / 3); //�{�[����y���̈ړ����鑬��
		g_hammer_x -= (g_hammer_speed_x / 3);
		g_hammer_speed_y -= 1;

		g_hammer_angle += 10;
		if (g_hammer_angle > 360)g_hammer_angle = 0;
		if (g_hammer_y > 800)g_hammer_flg = FALSE;
	}
	DrawRotaGraph(g_hammer_x - g_scroll_x, g_hammer_y, 1.0, M_PI / 180 * g_hammer_angle, GetArrayImages(Pickaxe_Images,0), TRUE, false);
}

void GameMain::Block_Collision(int a, int b)
{
	if ((a / 30) < MAP_HIGHT && (b / 30) >= 0) //�}�b�v�͈͓̔���
	{
		if ((a / 30) < MAP_WIDTH - 2 && (b / 30) >= 0)//�}�b�v�͈͓̔���
		{
			if (MAP_DATA[a / 30][b / 30] > 0 && MAP_DATA[a / 30][b / 30] < 5)//�u���b�N�ɓ���������
			{
				MAP_DATA[a / 30][b / 30] = 0;
				g_break_block_count++;//�u���b�N���󂵂��J�E���g�𑫂�
				if ((g_break_block_count % 50) == 0) g_block_count++;
			}
		}
	}
}



void GameMain::Player_Sousa()
{
	if (g_player_y >= 720)g_player_flg = DIE;
	if (g_player_flg == DIE)
	{
		/*g_player_x = 30, g_player_y = 550;
		g_player_flg = WALK;*/
		SetGameState(4);
	}

	if (g_player_flg != DIE)
	{
		if ((g_lkey_flg == TRUE) && (g_old_lkey_flg == FALSE))
		{
			if (g_item_selection == 0)g_item_selection = 2;
			else g_item_selection--;
		}
		if ((g_rkey_flg == TRUE) && (g_old_rkey_flg == FALSE))
		{
			if (g_item_selection == 2)g_item_selection = 0;
			else g_item_selection++;
		}

		if (g_upkey_flg || g_downkey_flg)
		{
			g_cursorx = g_player_x;
			if (g_upkey_flg)g_cursory = Player_Hit_Up(g_player_y, 0) - PLAYER_SIZE;
			else if (g_downkey_flg) g_cursory = Player_Hit_Under(g_player_y, 0) + PLAYER_SIZE;
		}
		else
		{
			g_cursory = g_player_y;
			if (g_direction == RIGHT)g_cursorx = Player_Hit_Front(g_player_x, 0) + PLAYER_SIZE;
			else g_cursorx = Player_Hit_Front(g_player_x, 0) - PLAYER_SIZE;
		}

		if (g_player_flg == WALK)Walk();
		else if (g_player_flg == JUMP) Jump();
		else if (g_player_flg == FALL) Fall();

		if ((g_hammer_flg == TRUE) ||
			(g_bkey_flg == TRUE) && (g_old_bkey_flg == FALSE) ||
			(AX != 0 || AY != 0))
		{
			Hammer();
		}

		if ((g_item_flg == TRUE) ||
			(g_xkey_flg == TRUE) && (g_old_xkey_flg == FALSE))
		{
			Item();
		}
	}

	DrawGraph(((g_cursorx / 30) * 30) - g_scroll_x, (g_cursory / 30) * 30, GetArrayImages(Player_CursorImages,0), TRUE);

	DrawRotaGraph(g_player_x - g_scroll_x, g_player_y, 1.0, M_PI / 180 * 0, GetArrayImages(Player_Images, g_player_image_type), TRUE, g_direction);

	//DrawLine(g_player_x - g_scroll_x, g_player_y, g_player_x + (AX / 5) - g_scroll_x, g_player_y + (AY / 5), 0xffffff, TRUE);
}

void  GameMain::Walk()
{
	if (AX == 0 && AY == 0)
	{
		if (g_rightkey_flg || g_leftkey_flg)
		{
			if (g_rightkey_flg)
			{
				g_direction = RIGHT;
				g_player_x += 2;
				if (MAP_DATA[g_player_y / PLAYER_SIZE][Player_Hit_Front(g_player_x, 0) / PLAYER_SIZE] > 0)g_player_x = ((g_player_x / PLAYER_SIZE) * PLAYER_SIZE) + ((PLAYER_SIZE / 2));
			}
			else if (g_leftkey_flg)
			{
				g_direction = LEFT;
				g_player_x -= 2;
				if (MAP_DATA[g_player_y / PLAYER_SIZE][Player_Hit_Front(g_player_x, 0) / PLAYER_SIZE] > 0)g_player_x = ((g_player_x / PLAYER_SIZE) * PLAYER_SIZE) + ((PLAYER_SIZE / 2));
			}

			if (++g_image_time >= 5)
			{
				g_player_image_type++;
				if (g_player_image_type > 3)g_player_image_type = 0;
				g_image_time = 0;
			}
		}
	}

	if (((MAP_DATA[Player_Hit_Under(g_player_y, 1) / PLAYER_SIZE][Player_Hit_Front(g_player_x, -5) / PLAYER_SIZE] <= 0) &&
		(MAP_DATA[Player_Hit_Under(g_player_y, 1) / PLAYER_SIZE][Player_Hit_Back(g_player_x, -5) / PLAYER_SIZE] <= 0)) || (g_player_y > 600))
	{
		g_player_flg = FALL;
	}
	else if ((g_akey_flg) && !(g_old_akey_flg))
	{
		if ((MAP_DATA[Player_Hit_Up(g_player_y, 1) / PLAYER_SIZE][Player_Hit_Front(g_player_x, -5) / PLAYER_SIZE] <= 0) &&
			(MAP_DATA[Player_Hit_Up(g_player_y, 1) / PLAYER_SIZE][Player_Hit_Back(g_player_x, -5) / PLAYER_SIZE] <= 0)) //�v���C���[�̏�ɂȂɂ��Ȃ����
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
	g_player_y -= (g_move_speed_y / 6); //�v���C���[��Y��������
	g_move_speed_y -= 2;
	if ((MAP_DATA[Player_Hit_Up(g_player_y, 0) / PLAYER_SIZE][Player_Hit_Front(g_player_x, -5) / PLAYER_SIZE] > 0) ||
		(MAP_DATA[Player_Hit_Up(g_player_y, 0) / PLAYER_SIZE][Player_Hit_Back(g_player_x, -5) / PLAYER_SIZE] > 0))
	{
		g_player_y = ((g_player_y / PLAYER_SIZE) * PLAYER_SIZE) + (PLAYER_SIZE / 2);
		g_move_speed_y = -5;
	}
	if (AX == 0 && AY == 0)
	{
		if (g_rightkey_flg)g_player_x += 1, g_direction = RIGHT;
		if (g_leftkey_flg)g_player_x -= 1, g_direction = LEFT;
		if (MAP_DATA[Player_Hit_Up(g_player_y, 0) / PLAYER_SIZE][Player_Hit_Front(g_player_x, 0) / PLAYER_SIZE] > 0)g_player_x = ((g_player_x / PLAYER_SIZE) * PLAYER_SIZE) + (PLAYER_SIZE / 2);
		if (MAP_DATA[Player_Hit_Under(g_player_y, -5) / PLAYER_SIZE][Player_Hit_Front(g_player_x, 0) / PLAYER_SIZE] > 0)g_player_x = ((g_player_x / PLAYER_SIZE) * PLAYER_SIZE) + (PLAYER_SIZE / 2);
		if (MAP_DATA[Player_Hit_Up(g_player_y, 0) / PLAYER_SIZE][Player_Hit_Back(g_player_x, 0) / PLAYER_SIZE] > 0)g_player_x = ((g_player_x / PLAYER_SIZE) * PLAYER_SIZE) + (PLAYER_SIZE / 2);
		if (MAP_DATA[Player_Hit_Under(g_player_y, -5) / PLAYER_SIZE][Player_Hit_Back(g_player_x, 0) / PLAYER_SIZE] > 0)g_player_x = ((g_player_x / PLAYER_SIZE) * PLAYER_SIZE) + (PLAYER_SIZE / 2);
	}

	if (g_move_speed_y < 0) g_player_flg = FALL;

	DrawFormatString(100, 100, 0xffffff, "jump");
}

void GameMain::Fall()
{
	g_player_y -= (g_move_speed_y / 6); //�v���C���[�𗎂Ƃ�
	if (g_move_speed_y >= -35)g_move_speed_y -= 2;
	if ((MAP_DATA[Player_Hit_Under(g_player_y, 0) / PLAYER_SIZE][Player_Hit_Front(g_player_x, -5) / PLAYER_SIZE] > 0) ||
		(MAP_DATA[Player_Hit_Under(g_player_y, 0) / PLAYER_SIZE][Player_Hit_Back(g_player_x, -5) / PLAYER_SIZE] > 0)) //�n�ʂɗ�������
	{
		if (g_player_y <= 600)
		{
			g_player_y = ((g_player_y / PLAYER_SIZE) * PLAYER_SIZE) + (PLAYER_SIZE / 2);//�v���C���[��y���𐮂���
			g_move_speed_y = 0;
			g_player_flg = WALK;//�v���C���[��flg��WAKL�ɂ���
		}
	}
	if (AX == 0 && AY == 0)
	{
		if (g_rightkey_flg)g_player_x += 1, g_direction = RIGHT;//�������ɉE�{�^���������ꂽ��E�ɐi�ށi�ړ��ʂ͕����Ă���Ƃ��̔����j
		if (g_leftkey_flg)g_player_x -= 1, g_direction = LEFT;//�������ɍ��{�^���������ꂽ��E�ɐi�ށi�ړ��ʂ͕����Ă���Ƃ��̔����j
		if (MAP_DATA[(Player_Hit_Up(g_player_y, -5)) / PLAYER_SIZE][Player_Hit_Front(g_player_x, 0) / PLAYER_SIZE] > 0)g_player_x = ((g_player_x / PLAYER_SIZE) * PLAYER_SIZE) + (PLAYER_SIZE / 2);
		if (MAP_DATA[(Player_Hit_Under(g_player_y, -5)) / PLAYER_SIZE][Player_Hit_Front(g_player_x, 0) / PLAYER_SIZE] > 0)g_player_x = ((g_player_x / PLAYER_SIZE) * PLAYER_SIZE) + (PLAYER_SIZE / 2);
		if (MAP_DATA[Player_Hit_Up(g_player_y, -5) / PLAYER_SIZE][Player_Hit_Back(g_player_x, 0) / PLAYER_SIZE] > 0)g_player_x = ((g_player_x / PLAYER_SIZE) * PLAYER_SIZE) + (PLAYER_SIZE / 2);
		if (MAP_DATA[Player_Hit_Under(g_player_y, -5) / PLAYER_SIZE][Player_Hit_Back(g_player_x, 0) / PLAYER_SIZE] > 0)g_player_x = ((g_player_x / PLAYER_SIZE) * PLAYER_SIZE) + (PLAYER_SIZE / 2);
	}

	DrawFormatString(100, 100, 0xffffff, "fall");
}

int GameMain::HitBoxPlayer(int px, int py, ITEM* i)
{
	int sx1 = px - ((PLAYER_SIZE / 2) - 10);
	int sx2 = px + ((PLAYER_SIZE / 2) - 10);
	int sy1 = py - ((PLAYER_SIZE / 2) - 10);
	int sy2 = py + ((PLAYER_SIZE / 2) - 10);

	int dx1 = i->x + 10;
	int dx2 = i->x + (PLAYER_SIZE - 10);
	int dy1 = i->y + 10;
	int dy2 = i->y + (PLAYER_SIZE - 10);

	//DrawBox(dx1, dy1, dx2, dy2, 0xfffff, false);
	//DrawBox(sx1, sy1, sx2, sy2, 0xfffff, false);

	//��`���d�Ȃ��Ă���Γ�����
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

