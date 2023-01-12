#include "SceneManager.h"

void SceneManager::Initialize()
{
	scene_ = 0;
}

void SceneManager::Update(Input* input_)
{
	switch (scene_)
	{
	case Scene::title:
		if (input_->TriggerKey(DIK_SPACE))
		{
			scene_ = Scene::play;
		}
		break;
	case Scene::play:
		break;
	case Scene::clear:
		break;
	case Scene::over:
		break;
	}
}

void SceneManager::Draw()
{
	
}
