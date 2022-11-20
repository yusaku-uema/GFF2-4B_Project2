#pragma once
#include "AdstractScene.h"

// �V�[���̐؂�ւ��S��
class SceneManager
{
private:
	AdstractScene* m_Scene;

public:
	SceneManager(AdstractScene* scene);

public:
	void Update();
	void Draw()const;
	void ChangeScene();
};
