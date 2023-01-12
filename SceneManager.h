#pragma once
#include "Input.h"

//�V�[���Ǘ�
enum Scene
{
	title,
	play,
	clear,
	over
};

class SceneManager
{
public:
	void Initialize();
	void Update(Input* input_);
	void Draw();

	int getScene() { return scene_; }
private:
	int scene_;
};

