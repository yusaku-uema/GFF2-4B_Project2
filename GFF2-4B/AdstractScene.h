#pragma once
class AdstractScene
{
public:
    //�`��ȊO�̍X�V�����s
	virtual void Update() = 0;
	//�`��Ɋւ��邱�Ƃ�����
	virtual void Draw() const = 0;
	//�V�[����؂�ւ��邩�B
	virtual AdstractScene* ChangeScene() = 0;

};