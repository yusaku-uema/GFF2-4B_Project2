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
	 if (CheckSoundMem(GetSounds(Title_SE)) != 1) {   //SE‚ª—¬‚ê‚Ä‚¢‚È‚©‚Á‚½‚çÄ¶
		 ChangeVolumeSoundMem(255 * 80 / 100, GetSounds(Title_SE)); //SE‰¹—Ê’²® 255Å‘å‰¹—Ê‚©‚ç80%Ä¶
		 PlaySoundMem(GetSounds(Title_SE), DX_PLAYTYPE_NORMAL, TRUE); //SEÄ¶
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