#pragma once
#include "AdstractScene.h"

class End :
	public AdstractScene
{
private:


public:
	End();
	~End() {}
	//�`��ȊO�̍X�V�����s
	void  Update() override;
	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;
	AdstractScene* ChangeScene();
};
