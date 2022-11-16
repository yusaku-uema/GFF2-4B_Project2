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
*変数
************************************************/
bool g_forcedtermination; //強制終了
unsigned int PLAYER_MAP[MAP_HIGHT][MAP_WIDTH];
Fps fps; 

/***********************************************
 * プログラムの開始
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) {

    // タイトルを test に変更
    SetMainWindowText("掘れダンジョン君");
    SetGraphMode(1280, 720, 16);  //画面サイズ
    ChangeWindowMode(TRUE);		// ウィンドウモードで起動

    if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理

    SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする
   
    SceneManager* sceneManager = new SceneManager(new Title()); //最初に呼び出すシーン

        /*最初からクラス化、シーンマネージャーで書きましょう*/
        /*誰が見ても分かるように変数にコメント付けましょう*/

    // ゲームループ
    while (ProcessMessage() == 0 && g_forcedtermination != true) {
         
        //保留&& sceneManager->ChangeScene() != nullptr

        if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_7 ) {
            g_forcedtermination = true;//強制終了
        }

        fps.Avg();

        sceneManager->Update(); //描画以外の処理

        ClearDrawScreen();		// 画面の初期化

        sceneManager->Draw(); //描画のみ

        ScreenFlip();  // 裏画面の内容を表画面に反映

        sceneManager->ChangeScene(); //シーン切り替え

        fps.Wait();
    }

    DxLib_End();	// DXライブラリ使用の終了処理

    return 0;	// ソフトの終了
}