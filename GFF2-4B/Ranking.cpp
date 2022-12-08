#include"Ranking.h"

char g_name[6][13] = {
    {'a','b','c','d','e','f','g','h','i','j','k','l','m'},
    {'n','o','p','q','r','s','t','u','v','w','x','y','z'},
    {'A','B','C','D','E','F','G','H','I','J','K','L','M'},
    {'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'},
    {'0','1','2','3','4','5','6','7','8','9',},
    {}
};


RANKING::RANKING() {
    fonttime = 0;
    g_nowfontX = 0;
    g_nowfontY = 0;
    red = GetColor(255, 0, 0);
    white = GetColor(255, 255, 255);
    fontno = 0;
    if (g_RankingInputImage = LoadGraph("images/InputRankigImage.png"));
    if (g_DrawRankingImage = LoadGraph("images/rankingnyuuryoku.png"));
    ReadRanking();
}

void RANKING::InputRankingInit(void)
{
    g_Ranking[4].name[fontno] = '\0';
    for (int i = 0; i < 11; i++)
    {
        g_Ranking[4].name[i] = '\0';
    }

}

void RANKING::DrawRanking(void)
{
    //ランキング画像表示
    DrawGraph(0, 0, GetArrayImages(Title_Images,0), FALSE);

    //ランキング一覧を表示
    SetFontSize(65);
    for (int i = 0; i < 5; i++) {
        DrawFormatString(120, 170 + i * 60, 0xffffff, "%2d %10s %10d", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
    }
    SetFontSize(30);
    DrawString(50, 450, "----Bボタン押してタイトルに戻る----", 0xffffff, 0);

    if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B)
    {
        SetGameState(0);
    }

}

void RANKING::InputRanking() {
    // 入力キー取得
    g_OldKey = g_NowKey;
    g_NowKey = GetJoypadAnalogInput(&AX, &AY, DX_INPUT_PAD1);
    g_KeyFlg = g_NowKey & ~g_OldKey;

    if (fonttime >= 7)
    {
        if (AX > 0 || g_KeyFlg & PAD_INPUT_RIGHT)
        {
            if (g_nowfontY == 6 && g_nowfontX >= 6 && g_nowfontX <= 7)g_nowfontY = 4;
            if (g_nowfontY == 4 && g_nowfontX >= 10 && g_nowfontX <= 11)g_nowfontX = 12;
            g_nowfontX++;
            if (g_nowfontX > 12) g_nowfontX = 0;
            fonttime = 0;
        }
        else if (AX < 0 || g_KeyFlg & PAD_INPUT_LEFT)
        {
            if (g_nowfontY == 6 && g_nowfontX >= 6 && g_nowfontX <= 7)g_nowfontY = 4;
            g_nowfontX--;
            if (g_nowfontY == 4 && g_nowfontX <= 11 && g_nowfontX >= 10)g_nowfontX = 9;
            if (g_nowfontX < 0) g_nowfontX = 12;
            fonttime = 0;
        }
        else if (AY > 0 || g_KeyFlg & PAD_INPUT_DOWN)
        {
            g_nowfontY++;
            if(g_nowfontY == 5 && g_nowfontX >= 6 && g_nowfontX <= 7)
            g_nowfontY++;
            else if (g_nowfontY > 4) g_nowfontY = 0;
            fonttime = 0;
        }
        else if (AY < 0 || g_KeyFlg & PAD_INPUT_UP)
        {
            g_nowfontY--;
            if (g_nowfontY == -1 && g_nowfontX >= 6 && g_nowfontX <= 7)
                g_nowfontY = 6;
            else if (g_nowfontY < 0) g_nowfontY = 4;
            fonttime = 0;
        }
    }


    if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B)//決定
    {
        if (g_nowfontY == 4 && g_nowfontX >= 10 && g_nowfontX <= 12) {//消去
            if (fonttime >= 10)
            {
                fontno--;
                g_Ranking[4].name[fontno] = '\0';
                if (fontno < 0)fontno = 0;
                fonttime = 0;
            }
        }
        if (fonttime >= 10)
        {
            if (fontno < 9)
            {
                g_Ranking[4].name[fontno] = g_name[g_nowfontY][g_nowfontX];
                fontno++;
            }

            if (g_nowfontY == 6 && g_nowfontX >= 6 && g_nowfontX <= 7)
            {
                g_Ranking[4].score = g_Score;	// ランキングデータの5番目にスコアを登録
                SortRanking();		// ランキング並べ替え
                SaveRanking();		// ランキングデータの保存
            }

            

            fonttime = 0;
        }

    }

    if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A)//消去
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

    
}

void RANKING::InputRankingDraw(){
    int color=white;
    int g_fontX=190;
    int  g_fontY=140;

    //ランキング画像表示
    DrawGraph(0, 0, g_RankingInputImage, FALSE);

    //フォントサイズの設定
    SetFontSize(20);
   /* DrawBox(FONT_X - 150, FONT_Y - 145, FONT_X + 590, FONT_Y + 315, 0x000000, TRUE);*/
    DrawBox(FONT_X + 25, FONT_Y - 70, FONT_X + 1050, FONT_Y + 380, white, FALSE);

    SetFontSize(65);
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            if (i == g_nowfontY && j == g_nowfontX)
            {
               color = red;
            }
            DrawFormatString(FONT_X + 820, FONT_Y + 215, white, "%s", kettei);
            DrawFormatString(FONT_X + 495, FONT_Y + 290, white, "%s", enter);

            if (g_nowfontY == 4 && g_nowfontX >= 10 && g_nowfontX <= 12)
            {
                DrawFormatString(FONT_X + 820, FONT_Y + 215, red, "%s", kettei);
            }
            if (g_nowfontY == 6 && g_nowfontX >= 6 && g_nowfontX <= 7) {
                DrawFormatString(FONT_X + 495, FONT_Y + 290, red, "%s", enter);
            }
             DrawFormatString(g_fontX, g_fontY, color, "%c", g_name[i][j]);
            color = white;
            g_fontX += 70;
        }
        g_fontX = 190;
        g_fontY += 70;
    }
    g_fontY = 155; 

    DrawFormatString(500, 50, color, "%s", g_Ranking[4].name);
}

void RANKING::SortRanking() {
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

int RANKING::SaveRanking() {
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

int RANKING::ReadRanking() {
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
