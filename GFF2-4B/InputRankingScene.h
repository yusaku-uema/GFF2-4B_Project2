#pragma once
#include"SceneManager.h"
#include"Ranking.h"

class InputRanking :public AbstractScene {
private:
	RANKING ranking;
public:
	InputRanking(int g_GameState);

	//�f�X�g���N�^
	~InputRanking() {};

	//�`��ȊO�̍X�V����������
 AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ���������
	void Draw() const override;

	int g_InputRankingGameState;
};