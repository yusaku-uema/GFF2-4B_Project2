#pragma once
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
    RankingData g_Ranking[10];

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
    char kettei[5] = "�폜";
    int g_fontX ;
    int g_fontY ;
    int fontno ;
    int g_Score;

    //�R���X�g���N�^
    RANKING();
    //�f�X�g���N�^
    ~RANKING() {}

	void InputRanking();
    void InputRankingDraw()const;
	void DrawRanking();
    void SortRanking(void);		//�����L���O���בւ�
    int  SaveRanking(void);		//�����L���O�f�[�^�̕ۑ�
    int  ReadRanking(void);		//�����L���O�f�[�^�ǂݍ���
    int getvalue(int g_score); //score�Ȃǂ̒l���擾����
};

//extern Ranking ranking;