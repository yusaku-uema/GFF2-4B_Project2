#pragma once
#include"AbstractScene.h"
class Credit:
	public AbstractScene
{
public:
	////�R���X�g���N�^
	//Credit();
	////�f�X�g���N�^
	//~Credit();
	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;
	//�`��Ɋւ��邱�Ƃ�����
	void Draw()const override;
};

