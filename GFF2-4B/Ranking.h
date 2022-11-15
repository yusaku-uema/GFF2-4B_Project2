#pragma once
#include"DxLib.h"

const int FONT_X = 100;
const int FONT_Y = 200;

struct	RankingData {
    int		no;
    char	name[11];
    long	score;
};

class RANKING
{
private:
    
public:
    FILE* fp;
    RankingData g_Ranking[5];

    int g_RankingInputImage;
    int g_DrawRankingImage;
    int fonttime;
    int g_KeyFlg;
    int  g_OldKey;
    int g_NowKey;
    int AX, AY;
    int g_nowfontX;
    int g_nowfontY;
    int red;
    int white;
    int color;
    char kettei[5] = "削除";
    char enter[5] = "決定";
    int fontno ;
    int g_Score;
    
public:
   

    //コンストラクタ
    RANKING();
    //デストラクタ
    ~RANKING() {}

	void InputRanking();
    void InputRankingDraw()const;
	void DrawRanking()const;
    void SortRanking(void);		//ランキング並べ替え
    int  SaveRanking(void);		//ランキングデータの保存
    int  ReadRanking(void);		//ランキングデータ読み込み
    void InputRankingInit(void);
};
