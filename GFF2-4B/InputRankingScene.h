#pragma once
#include"Ranking.h"

class InputRanking  {
private:
	RANKING ranking;
	/*UI ui;*/
	int g_score;
	int getvalue(int n);
	int g_InputRankingGameState;
	int i;

public:
	
	InputRanking();

	//�f�X�g���N�^
	virtual~InputRanking() {};

	//�`��ȊO�̍X�V����������
	void  Update();

	//�`��Ɋւ��邱�Ƃ���������
	 void Draw();
	//�V�[���؂�ւ�
	void  ChangeScene();

	
};