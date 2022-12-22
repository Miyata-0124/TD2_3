#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class Goal
{
public:
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Goal();

    void Initialize();

    void Update();

    void Draw(ViewProjection* viewProjection);

    void SetWorldTransform(WorldTransform goalTransform);

private:

    Model* goalModel = nullptr;
    WorldTransform goalTransform;
    ViewProjection viewProjection_;
};