#pragma once
#include"AbstractScene.h"
#include"Ranking.h"

class DrawRanking :public AbstractScene {
private:
	RANKING ranking;
public:
	DrawRanking(int g_GameState);


	//�f�X�g���N�^
	virtual~DrawRanking() {};

	//�`��ȊO�̍X�V����������
	virtual AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ���������
	virtual void Draw() const override;

	int g_DrawRankingGameState;
};