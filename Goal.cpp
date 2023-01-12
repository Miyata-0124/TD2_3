#include "Goal.h"
#include "Affine.h"

Goal::~Goal() {
    delete goalModel;
}

void Goal::Initialize() {
    goalModel = Model::CreateFromOBJ("goal1", true);
    goalTransform.Initialize();
    goalTransform.scale_ = { 7.0f,7.0f,7.0f };
    goalTransform.translation_ = { 0.0f,0.0f,0.0f };

    Affine::CreateAffine(goalTransform);
    goalTransform.TransferMatrix();
}

void Goal::Update()
{

}

void Goal::Draw(ViewProjection* viewProjection) {
    goalModel->Draw(goalTransform, *viewProjection);
}

void Goal::SetWorldTransform(WorldTransform worldTransform)
{
    Affine::CreateMatRotZ(goalTransform, worldTransform.rotation_);
	Affine::CreateMatRotX(goalTransform, worldTransform.rotation_);
	goalTransform.TransferMatrix();
}
