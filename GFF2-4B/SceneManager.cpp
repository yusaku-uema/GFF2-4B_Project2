#include"DxLib.h"
#include"SceneManager.h"

SceneManager::SceneManager(AdstractScene* scene)
{
	m_Scene = scene; 
}


void SceneManager::Update()
{
	m_Scene->Update(); 
}


void SceneManager::Draw()const
{
	m_Scene->Draw(); 
}


void SceneManager::ChangeScene() //“¯‚¶ƒV[ƒ“‚È‚Ì‚©H
{
	AdstractScene* next = m_Scene->ChangeScene();
	if (next != m_Scene) 
	{
		delete m_Scene; 
		m_Scene = next;
	}

}
