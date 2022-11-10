#include"Ranking.h"
#include"UI.h"
#include"DxLib.h"

char g_name[5][13] = {
    {'a','b','c','d','e','f','g','h','i','j','k','l','m'},
    {'n','o','p','q','r','s','t','u','v','w','x','y','z'},
    {'A','B','C','D','E','F','G','H','I','J','K','L','M'},
    {'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'},
    {'0','1','2','3','4','5','6','7','8','9',}
};

Ranking ranking;

Ranking::Ranking() {
    fonttime = 0;
    g_nowfontX = 0;
    g_nowfontY = 0;
    red = GetColor(255, 0, 0);
    white = GetColor(255, 255, 255);
    g_fontX = FONT_X;
    g_fontY = FONT_Y;
    fontno = 0;
    if (g_RankingInputImage = LoadGraph("images/rankingnyuuryoku.png"));
}

void Ranking::InputRanking() {
    // 入力キー取得
    g_OldKey = g_NowKey;
    g_NowKey = GetJoypadAnalogInput(&AX, &AY, DX_INPUT_PAD1);
    g_KeyFlg = g_NowKey & ~g_OldKey;

    // //ランキング画像表示
    DrawGraph(0, 0, g_RankingInputImage, FALSE);

    //フォントサイズの設定
    SetFontSize(20);
    DrawBox(FONT_X - 10, FONT_Y - 5, FONT_X + 450, FONT_Y + 175, 0x000000, TRUE);
    DrawBox(FONT_X - 10, FONT_Y - 5, FONT_X + 450, FONT_Y + 175, white, FALSE);

    if (fonttime >= 7)
    {
        if (AX > 0 || g_KeyFlg & PAD_INPUT_RIGHT)
        {
            if (g_nowfontY == 4 && g_nowfontX >= 10 && g_nowfontX <= 11)g_nowfontX = 12;
            g_nowfontX++;
            if (g_nowfontX > 12) g_nowfontX = 0;
            fonttime = 0;
        }
        else if (AX < 0 || g_KeyFlg & PAD_INPUT_LEFT)
        {
            g_nowfontX--;
            if (g_nowfontY == 4 && g_nowfontX <= 11 && g_nowfontX >= 10)g_nowfontX = 9;
            if (g_nowfontX < 0) g_nowfontX = 12;
            fonttime = 0;
        }
        else if (AY > 0 || g_KeyFlg & PAD_INPUT_DOWN)
        {
            g_nowfontY++;
            if (g_nowfontY > 4) g_nowfontY = 0;
            fonttime = 0;
        }
        else if (AY < 0 || g_KeyFlg & PAD_INPUT_UP)
        {
            g_nowfontY--;
            if (g_nowfontY < 0) g_nowfontY = 4;
            fonttime = 0;
        }
    }

    SetFontSize(30);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            if (i == g_nowfontY && j == g_nowfontX)
            {
                color = red;
            }
            DrawFormatString(FONT_X + 365, FONT_Y + 140, white, "%s", kettei);

            if (g_nowfontY == 4 && g_nowfontX >= 10 && g_nowfontX <= 12)
            {
                DrawFormatString(FONT_X + 365, FONT_Y + 140, red, "%s", kettei);
            }

            DrawFormatString(g_fontX, g_fontY, color, "%c", g_name[i][j]);
            color = white;
            g_fontX += 35;
        }
        g_fontX = FONT_X;
        g_fontY += 35;
    }
    g_fontY = FONT_Y;


    if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A)//決定
    {

        if (fonttime >= 10)
        {
            if (fontno < 9)
            {
                g_Ranking[4].name[fontno] = g_name[g_nowfontY][g_nowfontX];
                fontno++;
            }

            if (g_nowfontY == 4 && g_nowfontX >= 10 && g_nowfontX <= 12)
            {
                g_Ranking[4].score = g_Score;	// ランキングデータの5番目にスコアを登録
                SortRanking();		// ランキング並べ替え
                SaveRanking();		// ランキングデータの保存
            }

            fonttime = 0;
        }

    }

    if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B)//消去
    {
        if (fonttime >= 10)
        {
            fontno--;
            g_Ranking[4].name[fontno] = '\0';
            if (fontno < 0)fontno = 0;
            fonttime = 0;
        }

    }

    fonttime++;

    DrawFormatString(210, 165, color, "%s", g_Ranking[4].name);
}

void Ranking::SortRanking() {
    int i, j;
    RankingData work;

    // 選択法ソート
    for (i = 0; i < 4; i++) {
        for (j = i + 1; j < 5; j++) {
            if (g_Ranking[i].score <= g_Ranking[j].score) {
                work = g_Ranking[i];
                g_Ranking[i] = g_Ranking[j];
                g_Ranking[j] = work;
            }
        }
    }

    //順位付け
    for (i = 0; i < 5; i++) {
        g_Ranking[i].no = 1;
    }
    //得点が同じ場合は、同じ順位とする
    //同順位があった場合の次の順位はデータ個数が加算された順位とする
    for (i = 0; i < 4; i++) {
        for (j = i + 1; j < 5; j++) {
            if (g_Ranking[i].score > g_Ranking[j].score) {
                g_Ranking[j].no++;
            }
        }
    }
}

int Ranking::SaveRanking() {
    FILE* fp;
#pragma warning(disable:4996)


    if ((fp = fopen("dat/rankingdata.txt", "w")) == NULL) {
        /* エラー処理 */
        printf("Ranking Data Error\n");
        return -1;
    }

    //ランキングデータ分配列データを書き込む
    for (int i = 0; i < 5; i++) {
        fprintf(fp, "%2d %10s %10d\n", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
    }

    //ファイルクローズ
    fclose(fp);

    return 0;
}

int Ranking::ReadRanking() {
    FILE* fp;
#pragma warning(disable:4996)

    //ファイルオープン
    if ((fp = fopen("dat/rankingdata.txt", "r")) == NULL) {
        //エラー処理
        printf("Ranking Data Error\n");
        return -1;
    }

    //ランキングデータ配分列データを読み込む
    for (int i = 0; i < 5; i++) {
        fscanf(fp, "%2d %10s %10d\n", &g_Ranking[i].no, g_Ranking[i].name, &g_Ranking[i].score);//あやしい
    }

    //ファイルクローズ
    fclose(fp);

    return 0;
}

int Ranking::getvalue(int g_score) {
    return g_Score=g_score;
}