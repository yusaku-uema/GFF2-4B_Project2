#include"DxLib.h"
#include"main.h"
#include"TimeBaseLoopExecuter.h"//FPS�Ǘ�
#include"Title.h" //�^�C�g��
#include"GameMain.h" //
#include"Gameover.h"
#include"Gameclear.h"
#include"Credit.h"
#include"GameReward.h"
#include"Ranking.h"
#include"KeyConfigScene.h"
#include"Help.h"



/***********************************************
*  �ϐ�
************************************************/
int g_GameState; //�Q�[���V�[���Ǘ�
int g_Score = 0; //�X�R�A
bool g_forcedtermination; //�����I��

/***********************************************
*  �摜�ϐ�
************************************************/
int g_hammer_image; //��͂��̉摜
int g_cursor_image; //�J�[�\���̉摜
int g_haikei_image; //�P�X�e�[�W�̔w�i
int g_Title_images; //�^�C�g���摜
int g_GameOver_images; //�Q�[���I�[�o�[�w�i
int g_GameClear_images; //�Q�[���N���A�w�i
int g_white_image; //�����摜
int g_Box_images;//�󔠉摜
int g_Box2_images;//�󔠉摜
int g_HelpImages; //�w���v�摜


int g_block_image[20]; //�u���b�N�摜
int g_player_image[4]; //�v���C���[�摜
int g_item_image[5]; //�A�C�e���摜
int g_item_cursor_image[3]; //�A�C�e���J�[�\���摜
int g_life;

/***********************************************
*  �T�E���h�ϐ�
************************************************/
int g_Title_SE; //�^�C�g��SE


/***********************************************
*  �N���X�H�H
************************************************/

TimeBaseLoopExecuter timebaseloopexecuter; //fps
Title title; //�^�C�g��
GameMain gamemain;
Credit credit;//�N���W�b�g
GameReward gamereward;//���J�����
Gameover gameover;
GameClear gameclear;
RANKING ranking;
KeyConfigScene keyconfigscene;
KeyConfig keyconfig;
Help help;


/***********************************************
 * �v���O�����̊J�n
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	// �^�C�g���� test �ɕύX
	SetMainWindowText("�@��@��_���W�����N");
	SetGraphMode(1280, 720, 16);  //��ʃT�C�Y
	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��

	if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������
	if (LoadImages() == -1) return -1; //�摜�Ǎ���
	if (LoadSounds() == -1) return -1; //�T�E���h�Ǎ���
	 // �L�[�R���t�B�O�����̏��������s��
	keyconfig.Initialize();
	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

		/*�ŏ�����N���X���A�V�[���}�l�[�W���[�ŏ����܂��傤*/
		/*�N�����Ă�������悤�ɕϐ��ɃR�����g�t���܂��傤*/


	// �Q�[�����[�v
	while (ProcessMessage() == 0 && g_forcedtermination != true && g_GameState != 999) {

		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_7) {
			g_forcedtermination = true;//�����I��
		}

		timebaseloopexecuter.TimeAdjustment();// fps�Ǘ�

		ClearDrawScreen();		// ��ʂ̏�����
		switch (g_GameState) {
		case 0:
			title.Update(); //�Q�[���^�C�g���`�揈��
			break;
		case 1:
			gamemain.GameMain_Init(); //���������� case2�Ɏ����ڍs
			break;
		case 2:
			gamemain.Update(); //�Q�[������
			break;
		case 3:
			gameclear.Draw(); //�Q�[���N���A
			break;
		case 4:
			gameover.Draw(); //�Q�[���I�[�o�[
			break;
		case 5:
			credit.Draw(); //�N���W�b�g
			break;
		case 6:
			ranking.DrawRanking(); //�����L���O�\��
			break;
		case 7:
			help.Draw();
		case 8:
			// Pause();
			break;
		case 9:
			keyconfigscene.Update();
		}

		ScreenFlip();  // ����ʂ̓��e��\��ʂɔ��f

	}

	DxLib_End();	// DX���C�u�����g�p�̏I������

	return 0;	// �\�t�g�̏I��
}

/***********************************************
*  �V�[���؂�ւ��ɕK�v�Ȋ֐�
************************************************/
void  SetGameState(int a)
{
	g_GameState = a; //�����Ŏw�肵���l��g_GameState�ɑ��
}

//�X�R�A��ǂރR��
int GetScore()
{
	return g_Score;
}

void SetScore(int a)
{
	g_Score = a;
}

/***********************************************
*  �摜�Ǎ���
************************************************/
int LoadImages()
{
	if ((g_hammer_image = LoadGraph("images/team/hammer1.png")) == -1)return -1;
	if ((g_cursor_image = LoadGraph("images/team/kasoru.png")) == -1)return -1;
	if ((g_haikei_image = LoadGraph("images/abcde.png")) == -1)return -1;
	if ((g_white_image = LoadGraph("images/team/white.png")) == -1)return -1;
	if ((g_Title_images = LoadGraph("images/TitleImage.png")) == -1)return -1;
	if ((g_GameOver_images = LoadGraph("images/GameOver3.png")) == -1)return -1;
	if ((g_GameClear_images = LoadGraph("images/GameClear2.png")) == -1)return -1;
	if ((g_life = LoadGraph("images/BomFire.png")) == -1)return -1;
	if ((g_Box_images = LoadGraph("images/�󔠂P_transparent.png")) == -1)return-1;
	if ((g_Box2_images = LoadGraph("images/�󔠂Q_transparent.png")) == -1)return -1;
	if ((g_HelpImages = LoadGraph("images/�R���g���[���[�V�摜.png")) == -1)return -1;

	if (LoadDivGraph("images/team/block222.png", 7, 7, 1, 30, 30, g_block_image) == -1) return -1;
	if (LoadDivGraph("images/Player/player.png", 4, 4, 1, 25, 25, g_player_image) == -1) return -1;
	if (LoadDivGraph("images/team/item_cursor1.png", 3, 3, 1, 100, 100, g_item_cursor_image) == -1) return -1;
	if (LoadDivGraph("images/team/item22.png", 5, 5, 1, 30, 30, g_item_image) == -1) return -1;
}

/***********************************************
*  BGM��SE�Ǎ���
************************************************/
int LoadSounds(void)
{
	if ((g_Title_SE = LoadSoundMem("BGM/Title.mp3")) == -1)return -1; //	�^�C�g��SE
}


/***********************************************
*  �摜�Ăяo��
************************************************/
int GetArrayImages(int type, int num)
{
	switch (type)
	{
	case Title_Images: //�^�C�g���摜
		return g_Title_images;
		break;

	case GameOver_Images: //�Q�[���I�[�o�[�摜
		return g_GameOver_images;
		break;

	case GameClear_Images: //�Q�[���N���A�w�i
		return g_GameClear_images;
		break;
	case  Life_Images:
		return g_life;
		break;

	case Player_Images: //�v���C���[�摜
		return g_player_image[num];
		break;

	case GameMain_Images: //�P�X�e�[�W�̔w�i
		return g_haikei_image;
		break;

	case Block_Images: //�u���b�N�摜
		if (0 <= num && num < 20) {
			return g_block_image[num];
		}
		else { return -1; }
		break;

	case Player_CursorImages: //�v���C���[�̑O�ɂ���J�[�\��
		return g_cursor_image;
		break;

	case Item_Images: //�A�C�e���摜
		if (0 <= num && num < 5) {
			return g_item_image[num];
		}
		else { return -1; }
		break;

	case  Pickaxe_Images: //��͂��摜
		return g_hammer_image;
		break;

	case Box_images:
		return g_Box_images;
		break;
	case Box2_images:
		return g_Box2_images;
		break;

	case Item_cursor: //�A�C�e���J�[�\��
		if (0 <= num && num < 3) {
			return g_item_cursor_image[num];
		}
		else { return -1; }
		break;
	case Help_Images:
		return g_HelpImages;
		break;
	default:
		return -1;
		break;
	}
}

/***********************************************
* �T�E���h�Ăяo��
************************************************/
int GetSounds(int type) {

	if (Title_SE == type)return g_Title_SE;
	return 0;

}