#pragma once
#include"SceneManager.h"
#include"Ranking.h"
#include"UI.h"

class InputRanking :public AdstractScene {
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
	void  Update() override;

	//�`��Ɋւ��邱�Ƃ���������
	virtual void Draw() const override;
	//�V�[���؂�ւ�
	AdstractScene* ChangeScene();

	
};