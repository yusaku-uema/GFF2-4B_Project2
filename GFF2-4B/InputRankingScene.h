#pragma once
#include"Ranking.h"
#include"UI.h"

class InputRanking  {
private:
	/*RANKING ranking;
	UI ui;*/
	int g_score;
	int getvalue(int n);
	int g_InputRankingGameState;

public:
	
	InputRanking(int g_GameState,int n);

	//�f�X�g���N�^
	virtual~InputRanking() {};

	//�`��ȊO�̍X�V����������
	void  Update();

	//�`��Ɋւ��邱�Ƃ���������
	 void Draw();
	//�V�[���؂�ւ�
	void  ChangeScene();

	
};