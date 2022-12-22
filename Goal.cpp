#include "Goal.h"
#include "Affine.h"

Goal::~Goal() {
    delete goalModel;
}

void Goal::Initialize() {
    goalModel = Model::CreateFromOBJ("goal1", true);
    goalTransform.Initialize();
    goalTransform.scale = { 7.0f,7.0f,7.0f };
    goalTransform.translation = { 0.0f,0.0f,0.0f };

    Affine::CreateAffine(goalTransform);
    goalTransform.TransferMatrix();
}

void Goal::Draw(ViewProjection* viewProjection) {
    goalModel->Draw(goalTransform_, *viewProjection);
}