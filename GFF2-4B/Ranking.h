#pragma once
const int FONT_X = 100;
const int FONT_Y = 200;

struct	RankingData {
    int		no;
    char	name[11];
    long	score;
};

class Ranking
{
private:
    int g_RankingInputImage;
    int fonttime;
    int g_KeyFlg;
    int  g_OldKey;
    int g_NowKey;
    int AX, AY;
    int g_nowfontX;
    int g_nowfontY;
    int Cr;
    int red;
    int white;
    int color;
    char kettei[5] = "削除";
    int g_fontX ;
    int g_fontY ;
    int fontno ;
    int g_Score;
    RankingData g_Ranking[10];
public:
    Ranking();


	void InputRanking();
	void DrawRanking();
    void SortRanking(void);		//ランキング並べ替え
    int  SaveRanking(void);		//ランキングデータの保存
    int  ReadRanking(void);		//ランキングデータ読み込み
    int getvalue(int g_score); //scoreなどの値を取得する
};

extern Ranking ranking;