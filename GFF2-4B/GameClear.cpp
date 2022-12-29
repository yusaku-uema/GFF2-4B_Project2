#include "GameClear.h"
#include"DxLib.h"

void GameClear::Draw()
{
	g_Rankingscore = ranking.GetRankingScore(4);
	g_score = GetScore();
	ranking.InputRankingInit();

	DrawGraph(0, 0, GetArrayImages(GameClear_Images, 0), TRUE);
	SetFontSize(40);
	
	if (CheckSoundMem(BGM) != 1) {   //SE������Ă��Ȃ�������Đ�
		BGM = LoadSoundMem("BGM/gameclear.mp3");
		ChangeVolumeSoundMem(255 * 40 / 100, BGM); //SE���ʒ��� 255�ő剹�ʂ���80%�Đ�
		PlaySoundMem(BGM, DX_PLAYTYPE_LOOP, TRUE); //SE�Đ�
	}


	DrawGraph(450, 450, GetArrayImages(Item_Images, 1),FALSE); //�J�M
	DrawString(485, 450, " = 5000�_", GetColor(255, 0, 0));
	DrawGraph(450, 500, GetArrayImages(Item_Images, 2), FALSE); //��
	DrawString(485, 500, " = 1000�_", GetColor(255, 0, 0));
	DrawString(450, 550, "���� = 1�b100�_", GetColor(255, 0, 0));


	DrawString(350, 350, "Score", GetColor(255, 0, 0));
	DrawFormatString(500, 350, GetColor(255, 0, 0), "%d", GetScore());
	DrawString(350, 280, "B�{�^���Ń^�C�g����", GetColor(255, 0, 0));
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B) {
		if (g_score >= g_Rankingscore)SetGameState(11);
		else {
			StopSoundMem(BGM);
			SetGameState(0);
		}
	}
}
