#pragma once
#include"AdstractScene.h"
#include"Ranking.h"

class DrawRanking :public AdstractScene {
private:
	//RANKING ranking;
	int g_DrawRankingGameState;
public:
	DrawRanking(int g_GameState);

	DrawRanking(); //�R���X�g���N�^
	//�f�X�g���N�^
	virtual~DrawRanking() {};

	//�`��ȊO�̍X�V����������
	void  Update() override;

	//�`��Ɋւ��邱�Ƃ���������
	virtual void Draw() const override;
	//�V�[���؂�ւ�
	AdstractScene* ChangeScene();
};