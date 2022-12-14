#include"InputRankingScene.h"
#include"DrawRankingScene.h"
#include"Ranking.h"
#include"main.h"
#include"DxLib.h"

InputRanking::InputRanking() {
	ranking.InputRankingInit();
}

void InputRanking::Draw() {
	//ranking.InputRankingDraw();
   /* ranking.g_Ranking[4].name[fontno] = '\0';*/
    for (int i = 0; i < 11; i++)
    {
        ranking.g_Ranking[4].name[i] = '\0';
    }
    ranking.fonttime = 0;
    ranking.g_nowfontX = 0;
    ranking.g_nowfontY = 0;
    ranking.fontno = 0;
    SetGameState(10);
}

void  InputRanking::Update() {
	ranking.InputRankingDraw();
  ranking.InputRanking();
 if (ranking.g_nowfontY == 6 && ranking.g_nowfontX >= 6 && ranking.g_nowfontX <= 7 && GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B)
 {
	 if (CheckSoundMem(GetSounds(Title_SE)) != 1) {   //SEが流れていなかったら再生
		 ChangeVolumeSoundMem(255 * 80 / 100, GetSounds(Title_SE)); //SE音量調整 255最大音量から80%再生
		 PlaySoundMem(GetSounds(Title_SE), DX_PLAYTYPE_NORMAL, TRUE); //SE再生
	 }
	SetGameState(6);
 }
	
}

void InputRanking::ChangeScene()
{

}

int InputRanking::getvalue(int n) {
	return g_InputRankingGameState = n;
}