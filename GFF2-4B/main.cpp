#include"DxLib.h"
#include"main.h"
#include"fps_fixed.h" //FPS�Ǘ�
#include"Title.h" //�^�C�g��
#include"GameMain.h"


#define MAP_HIGHT 20
#define MAP_WIDTH 103

#define DRAW_MAP_HIGHT 20
#define DRAW_MAP_WIDTH 35

#define BLOCK_WIDTH 30

/***********************************************
*  �ϐ�
************************************************/
int g_GameState; //�Q�[���V�[���Ǘ�
bool g_forcedtermination; //�����I��

/***********************************************
*  �摜�ϐ�
************************************************/
int g_hammer_image; //��͂��̉摜
int g_cursor_image; //�J�[�\���̉摜
int g_haikei_image; //�P�X�e�[�W�̔w�i
int g_Title_images; //�^�C�g���摜
int g_white_image; //�����摜

int g_block_image[20]; //�u���b�N�摜
int g_player_image[4]; //�v���C���[�摜
int g_item_image[3]; //�A�C�e���摜
int g_item_cursor_image[3]; //�A�C�e���J�[�\���摜

/***********************************************
*  �T�E���h�ϐ�
************************************************/
int g_Title_SE; //�^�C�g��SE


/***********************************************
*  �N���X�H�H
************************************************/

Fps fps; //FPS�Ǘ�
Title title; //�^�C�g��
GameMain gamemain;


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

	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

		/*�ŏ�����N���X���A�V�[���}�l�[�W���[�ŏ����܂��傤*/
		/*�N�����Ă�������悤�ɕϐ��ɃR�����g�t���܂��傤*/

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && g_forcedtermination != true) {

		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_7) {
			g_forcedtermination = true;//�����I��
		}

		fps.Avg(); //FPS

		ClearDrawScreen();		// ��ʂ̏�����
		switch (g_GameState) {
		case 0:
			title.Update(); //�Q�[���^�C�g���`�揈��
			break;
		case 1:
			gamemain.GameMain_Init();
			break;
		case 2:
			gamemain.Update();
			break;
		case 3:
			// DrawHelp();
			break;
		case 4:
			//DrawEnd();
			break;
		case 5:
			//GameMain();
			break;
		case 6:
			// InputRanking();
			break;
		case 7:
			// Pause();
			break;
		}

		ScreenFlip();  // ����ʂ̓��e��\��ʂɔ��f


		fps.Wait(); //FPS�ɍ��킹�đҋ@
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


/***********************************************
*  �摜�Ǎ���
************************************************/
int LoadImages()
{
	if ((g_hammer_image = LoadGraph("images/team/hammer.png")) == -1)return -1;
	if ((g_cursor_image = LoadGraph("images/team/kasoru.png")) == -1)return -1;
	if ((g_haikei_image = LoadGraph("images/team/haikei.png")) == -1)return -1;
	if ((g_white_image = LoadGraph("images/team/white.png")) == -1)return -1;
	if ((g_Title_images = LoadGraph("images/taitle2.png")) == -1)return -1;

	if (LoadDivGraph("images/team/block3.png", 6, 6, 1, 30, 30, g_block_image) == -1) return -1;
	if (LoadDivGraph("images/team/human.png", 4, 4, 1, 30, 30, g_player_image) == -1) return -1;
	if (LoadDivGraph("images/team/item.png", 3, 3, 1, 30, 30, g_item_image) == -1) return -1;
	if (LoadDivGraph("images/team/item_cursor.png", 3, 3, 1, 100, 100, g_item_cursor_image) == -1) return -1;
}

/***********************************************
*  BGM��SE�Ǎ���
************************************************/
int LoadSounds(void)
{
	if ((g_Title_SE = LoadSoundMem("BGM/decision.mp3")) == -1)return -1;
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
	case Player_Images: //�v���C���[�摜
		if (0 <= num && num < 4) {
			return g_player_image[num];
		}
		else { return -1; }
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
		if (0 <= num && num < 3) {
			return g_item_image[num];
		}
		else { return -1; }
		break;

	case  Pickaxe_Images: //��͂��摜
		return g_hammer_image;
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