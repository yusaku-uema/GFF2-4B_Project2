#include"DxLib.h"
#include"main.h"
#include"TimeBaseLoopExecuter.h"//FPS管理
#include"Title.h" //タイトル
#include"GameMain.h" //
#include"Gameover.h"
#include"Gameclear.h"
#include"Credit.h"
#include"GameReward.h"
#include"Ranking.h"
#include"Help.h"
#include"InputRankingScene.h"
#include"DrawRankingScene.h"
#include"Tkara.h"



/***********************************************
*  変数
************************************************/
int g_GameState; //ゲームシーン管理
int Score1 = 0; //スコア
int kagi; //カギ
bool g_forcedtermination; //強制終了
int stage = 0;

/***********************************************
*  画像変数
************************************************/
int g_hammer_image; //つるはしの画像
int g_cursor_image; //カーソルの画像
int g_haikei_image; //１ステージの背景
int g_Title_images; //タイトル画像
int g_GameOver_images; //ゲームオーバー背景
int g_GameClear_images; //ゲームクリア背景
int g_Box_images;//宝箱画像
int g_Box2_images;//宝箱画像
int g_HelpImages; //ヘルプ画像


int g_block_image[20]; //ブロック画像
int g_player_image[4]; //プレイヤー画像
int g_item_image[5]; //アイテム画像
int g_item_cursor_image[3]; //アイテムカーソル画像
int g_KiraKira_image[2]; //アイテムを光らせる用
int g_life;


/***********************************************
*  サウンド変数
************************************************/
int g_Title_SE; //タイトルSE
int g_Title_BGM;

/***********************************************
*  クラス？？
************************************************/

Fps fps; //fps
Title title; //タイトル
GameMain gamemain;
Credit credit;//クレジット
GameReward gamereward;//ご褒美画面
Gameover gameover;
GameClear gameclear;
RANKING ranking;
Help help;
InputRanking inputranking;
DrawRanking drawranking;
Takara takara;


/***********************************************
 * プログラムの開始
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	// タイトルを test に変更
	SetMainWindowText("掘れ掘れダンジョン君");
	SetGraphMode(1280, 720, 16);  //画面サイズ
	ChangeWindowMode(TRUE);		// ウィンドウモードで起動

	if (ranking.ReadRanking() == -1)  return  -1;    //ランキングデータの読み込み

	if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理
	if (LoadImages() == -1) return -1; //画像読込み
	if (LoadSounds() == -1) return -1; //サウンド読込み

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

		/*最初からクラス化、シーンマネージャーで書きましょう*/
		/*誰が見ても分かるように変数にコメント付けましょう*/


	// ゲームループ
	while (ProcessMessage() == 0 && g_forcedtermination != true && g_GameState != 999) {

		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_7) {
			g_forcedtermination = true;//強制終了
		}

		
		fps.Update(); //FPS管理
		ClearDrawScreen();		// 画面の初期化
		switch (g_GameState) {
		case 0:
			title.Update(); //ゲームタイトル描画処理
			break;
		case 1:
			gamemain.Stage_Select_Init(); //初期化して case2に自動移行
			break;
		case 2:
			gamemain.Update(); //ゲーム処理
			break;
		case 3:
			gameclear.Draw(); //ゲームクリア
			break;
		case 4:
			gameover.Draw(); //ゲームオーバー
			break;
		case 5:
			credit.Draw(); //クレジット
			break;
		case 6:
			ranking.DrawRanking(); //ランキング表示
			break;
		case 7:
			help.Draw(); //ヘルプ
			break;
		case 8:
			takara.init();
			break;
		case 9:
			takara.Draw();
			break;
		case 10:
			inputranking.Update();
			break;
		case 11:
			inputranking.Draw();
			break;
		}

		ScreenFlip();  // 裏画面の内容を表画面に反映
		fps.Wait(); //FPS管理（待機）
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

//スコアを読むコム
int GetScore()
{
	return Score1;
}

int Getkagi()
{
	return kagi;
}

void Setkagi(int a)
{
	kagi = a;
}

void Setstage(int a)
{
	stage = a;
}
int Getstage()
{
	return stage;
}

void SetScore(float a,bool b)
{
	if (b == FALSE) {
		Score1 = a;
	}
	else
	{
		Score1 = Score1 + a;
	}
}

/***********************************************
*  画像読込み
************************************************/
int LoadImages()
{
	if ((g_hammer_image = LoadGraph("images/team/hammer1.png")) == -1)return -1;
	if ((g_cursor_image = LoadGraph("images/team/kasoru.png")) == -1)return -1;
	if ((g_haikei_image = LoadGraph("images/abcde.png")) == -1)return -1;
	if ((g_Title_images = LoadGraph("images/TitleImage.png")) == -1)return -1;
	if ((g_GameOver_images = LoadGraph("images/GameOver3.png")) == -1)return -1;
	if ((g_GameClear_images = LoadGraph("images/GameClear2.png")) == -1)return -1;
	if ((g_life = LoadGraph("images/PlayerLife.png")) == -1)return -1;
	if ((g_Box_images = LoadGraph("images/宝箱１_transparent.png")) == -1)return-1;
	if ((g_Box2_images = LoadGraph("images/宝箱２_transparent.png")) == -1)return -1;
	if ((g_HelpImages = LoadGraph("images/HeipImage.png")) == -1)return -1;
	if (LoadDivGraph("images/team/block222.png", 7, 7, 1, 30, 30, g_block_image) == -1) return -1;
	if (LoadDivGraph("images/player3.png", 4, 4, 1, 20, 25, g_player_image) == -1) return -1;
	if (LoadDivGraph("images/team/item_cursor1.png", 3, 3, 1, 100, 100, g_item_cursor_image) == -1) return -1;
	if (LoadDivGraph("images/team/item22.png", 5, 5, 1, 30, 30, g_item_image) == -1) return -1;
	if (LoadDivGraph("images/team/kirakira2.png", 2, 2, 1, 30, 30, g_KiraKira_image) == -1) return -1;
}

/***********************************************
*  BGMやSE読込み
************************************************/
int LoadSounds(void)
{
	if ((g_Title_SE = LoadSoundMem("BGM/Title.mp3")) == -1)return -1; //	タイトルSE
	if ((g_Title_BGM = LoadSoundMem("BGM/ldtyl-isrvf.mp3")) == -1)return -1;//破壊音BGM
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

	case GameOver_Images: //ゲームオーバー画像
		return g_GameOver_images;
		break;

	case GameClear_Images: //ゲームクリア背景
		return g_GameClear_images;
		break;
	case  Life_Images:
		return g_life;
		break;

	case Player_Images: //プレイヤー画像
		return g_player_image[num];
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
		if (0 <= num && num < 5) {
			return g_item_image[num];
		}
		else { return -1; }
		break;

	case  Pickaxe_Images: //つるはし画像
		return g_hammer_image;
		break;

	case Box_images:
		return g_Box_images;
		break;
	case Box2_images:
		return g_Box2_images;
		break;

	case Item_cursor: //アイテムカーソル
		if (0 <= num && num < 3) {
			return g_item_cursor_image[num];
		}
		else { return -1; }
		break;
	case Help_Images:
		return g_HelpImages;
		break;

	case KiraKira_Images:
		if (0 <= num && num < 2) {
			return g_KiraKira_image[num];
		}
		else { return -1; }
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
	switch (type)
	{
	case Title_SE:
		return g_Title_SE;
		break;
	case Title_BGM:
		return g_Title_BGM;
		break;
	}
	
}