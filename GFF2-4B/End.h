#pragma once
#include "AbstractScene.h"

class End :
	public AbstractScene
{
private:


public:
	End();
	~End() {}
	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;
	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;
};
