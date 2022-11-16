#include"DxLib.h"
#include"SceneManager.h"
#include"GameMain.h"
#include"Title.h"
#include"fps_fixed.h"

#define MAP_HIGHT 20
#define MAP_WIDTH 103

#define DRAW_MAP_HIGHT 20
#define DRAW_MAP_WIDTH 35

#define BLOCK_WIDTH 30

/***********************************************
*�ϐ�
************************************************/
bool g_forcedtermination; //�����I��
unsigned int PLAYER_MAP[MAP_HIGHT][MAP_WIDTH];
Fps fps; 

/***********************************************
 * �v���O�����̊J�n
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) {

    // �^�C�g���� test �ɕύX
    SetMainWindowText("�@��_���W�����N");
    SetGraphMode(1280, 720, 16);  //��ʃT�C�Y
    ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��

    if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������


    SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���
    SceneManager* sceneMng;

    try
    {
        sceneMng = new SceneManager((AbstractScene*)new (GameMain));

    }
    catch (const char* err)
    {
        OutputDebugString(err);
        return 0;
    }
        ClearDrawScreen();  //��ʂ̏�����

        /*�ŏ�����N���X���A�V�[���}�l�[�W���[�ŏ����܂��傤*/
        /*�N�����Ă�������悤�ɕϐ��ɃR�����g�t���܂��傤*/

    // �Q�[�����[�v
    while (ProcessMessage() == 0 && sceneMng->Update() != nullptr && g_forcedtermination != true) {
  
        ClearDrawScreen();		// ��ʂ̏�����
        fps.Avg();
        sceneMng->Draw();
        ScreenFlip();
        fps.Wait();
        if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_7) {
            g_forcedtermination = true;
        }
    }

    DxLib_End();	// DX���C�u�����g�p�̏I������

    return 0;	// �\�t�g�̏I��
}