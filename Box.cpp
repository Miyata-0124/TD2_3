#include "Box.h"

Box::Box() {
}

Box::~Box() {
	//”jŠü
	delete field;
}

void Box::Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection) {
	field = new GameObject3D();
	field->PreLoadModel("Resources/taitle/taitle.obj");
	field->PreLoadTexture(L"Resources/taitle/taitle.png");
	field->SetViewProjection(viewProjection);
	field->SetMatProjection(matProjection);
	field->Initialize();
	field->worldTransform.rotation = { 0,90,0 };
	field->worldTransform.translation = { 0,0,-45 };
}

void Box::Update() {
	field->Update();
}

void Box::Draw() {
	field->Draw();
}