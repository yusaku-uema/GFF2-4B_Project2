#pragma once
#include"Ranking.h"
#include"main.h"

class DrawRanking {
private:
	//RANKING ranking;
	int g_DrawRankingGameState;
public:
	DrawRanking(int g_GameState);

	DrawRanking(); //�R���X�g���N�^
	//�f�X�g���N�^
	virtual~DrawRanking() {};

	//�`��ȊO�̍X�V����������
	void  Update();

	//�`��Ɋւ��邱�Ƃ���������
	 void Draw() const;
	//�V�[���؂�ւ�
	void ChangeScene();
};