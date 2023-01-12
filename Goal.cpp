#include "Goal.h"
#include "Affine.h"

Goal::~Goal() {
    delete goalModel;
}

void Goal::Initialize() {
    goalModel = Model::CreateFromOBJ("cube", true);
    goalTransform.Initialize();
    goalTransform.scale_ = { 0.5f,0.5f,0.5f };
    goalTransform.translation_ = { 1.0f,7.5f,1.0f };

    Affine::CreateAffine(goalTransform);
    goalTransform.TransferMatrix();
}

void Goal::Draw(ViewProjection* viewProjection) {
    goalModel->Draw(goalTransform, *viewProjection);
}