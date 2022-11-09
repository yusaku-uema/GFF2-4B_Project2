#include"DxLib.h"
#include"SceneManager.h"

AbstractScene* SceneManager::Update()
{
	AbstractScene* NextScene;
	try
	{
		NextScene = mScene->Update();
	}
	catch (const char* err)
	{
		OutputDebugString(err);
		return nullptr;
	}

	if (NextScene != mScene)
	{
		delete mScene;
		mScene = NextScene;
	}
	return mScene;
}
void SceneManager::Draw() const
{
	mScene->Draw();
}