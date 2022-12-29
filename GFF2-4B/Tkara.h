#pragma once
class Takara
{
private:
	int treasure; //宝画像
	int g_stage;
	int BGM;
	
	int treasure1;
	int backgroundimage; //背景画像
	int yagirusi;
	int g_MenuNumber; //メニューカーソルが今何番なのか。
	int g_MenuX; //カーソルの位置
	int g_KeyFlg; //同じ入力キーか
	int g_OldKey; //前回の入力
	int g_NowKey; //今回の入力キー
	int takaranum;
	int takaraX;
	int takaraOpen;
	int takaraNotopen;
	int FPS;
	int TimeLimet;
	bool sousa;
	bool takaraflg; //空いているのか

	//宝箱の構造体
	struct TAKARA {
		int flg; //使用フラグ
		int type; //タイプ
		int x, y; //座標x,y
		int point; //宝の得点	
	};
	//敵機
	struct TAKARA g_treasurebox[6];

	//矢印の構造体
	struct ARROW
	{
		int x, y;      //座標x,y
		int no;
		int oldkey;
	};
	//矢印
	struct ARROW g_arrow;

public:
	void Draw();
	void init();
	void ArrowControl();
};
