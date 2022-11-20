#pragma once
#include "AdstractScene.h"

// ƒV[ƒ“‚ÌØ‚è‘Ö‚¦’S“–
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
