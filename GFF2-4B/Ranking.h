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
    char kettei[5] = "�폜";
    char enter[5] = "����";
    int fontno ;
    int g_Score;
    
public:
   

    //�R���X�g���N�^
    RANKING();
    //�f�X�g���N�^
    ~RANKING() {}

	void InputRanking();
    void InputRankingDraw()const;
	void DrawRanking()const;
    void SortRanking(void);		//�����L���O���בւ�
    int  SaveRanking(void);		//�����L���O�f�[�^�̕ۑ�
    int  ReadRanking(void);		//�����L���O�f�[�^�ǂݍ���
    void InputRankingInit(void);
};
