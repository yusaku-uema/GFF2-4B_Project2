#include"DxLib.h"
#include"main.h"
#include"fps_fixed.h" //FPS管理
#include"Title.h" //タイトル
#include"GameMain.h"


#define MAP_HIGHT 20
#define MAP_WIDTH 103

#define DRAW_MAP_HIGHT 20
#define DRAW_MAP_WIDTH 35

#define BLOCK_WIDTH 30

/***********************************************
*  変数
************************************************/
int g_GameState; //ゲームシーン管理
bool g_forcedtermination; //強制終了

/***********************************************
*  画像変数
************************************************/
int g_hammer_image; //つるはしの画像
int g_cursor_image; //カーソルの画像
int g_haikei_image; //１ステージの背景
int g_Title_images; //タイトル画像
int g_white_image; //白い画像

int g_block_image[20]; //ブロック画像
int g_player_image[4]; //プレイヤー画像
int g_item_image[3]; //アイテム画像
int g_item_cursor_image[3]; //アイテムカーソル画像

/***********************************************
*  サウンド変数
************************************************/
int g_Title_SE; //タイトルSE


/***********************************************
*  クラス？？
************************************************/

Fps fps; //FPS管理
Title title; //タイトル
GameMain gamemain;


/***********************************************
 * プログラムの開始
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	// タイトルを test に変更
	SetMainWindowText("掘れ掘れダンジョン君");
	SetGraphMode(1280, 720, 16);  //画面サイズ
	ChangeWindowMode(TRUE);		// ウィンドウモードで起動

	if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理
	if (LoadImages() == -1) return -1; //画像読込み
	if (LoadSounds() == -1) return -1; //サウンド読込み

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

		/*最初からクラス化、シーンマネージャーで書きましょう*/
		/*誰が見ても分かるように変数にコメント付けましょう*/

	// ゲームループ
	while (ProcessMessage() == 0 && g_forcedtermination != true) {

		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_7) {
			g_forcedtermination = true;//強制終了
		}

		fps.Avg(); //FPS

		ClearDrawScreen();		// 画面の初期化
		switch (g_GameState) {
		case 0:
			title.Update(); //ゲームタイトル描画処理
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

		ScreenFlip();  // 裏画面の内容を表画面に反映


		fps.Wait(); //FPSに合わせて待機
	}

	DxLib_End();	// DXライブラリ使用の終了処理

	return 0;	// ソフトの終了
}

/***********************************************
*  シーン切り替えに必要な関数
************************************************/
void  SetGameState(int a)
{
	g_GameState = a; //引数で指定した値をg_GameStateに代入
}


/***********************************************
*  画像読込み
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
*  BGMやSE読込み
************************************************/
int LoadSounds(void)
{
	if ((g_Title_SE = LoadSoundMem("BGM/decision.mp3")) == -1)return -1;
}


/***********************************************
*  画像呼び出し
************************************************/
int GetArrayImages(int type, int num)
{
	switch (type)
	{
	case Title_Images: //タイトル画像
		return g_Title_images;
		break;
	case Player_Images: //プレイヤー画像
		if (0 <= num && num < 4) {
			return g_player_image[num];
		}
		else { return -1; }
		break;

	case GameMain_Images: //１ステージの背景
		return g_haikei_image;
		break;

	case Block_Images: //ブロック画像
		if (0 <= num && num < 20) {
			return g_block_image[num];
		}
		else { return -1; }
		break;

	case Player_CursorImages: //プレイヤーの前にあるカーソル
		return g_cursor_image;
		break;

	case Item_Images: //アイテム画像
		if (0 <= num && num < 3) {
			return g_item_image[num];
		}
		else { return -1; }
		break;

	case  Pickaxe_Images: //つるはし画像
		return g_hammer_image;
		break;

	default:
		return -1;
		break;
	}
}

/***********************************************
* サウンド呼び出し
************************************************/
int GetSounds(int type) {

	if (Title_SE == type)return g_Title_SE;
	return 0;
}