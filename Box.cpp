#include "Box.h"

Box::Box() {
}

Box::~Box() {
	//”jŠü
	delete field;
}

void Box::Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection) {
	field = new GameObject3D();
	field->PreLoadModel("Resources/cube/cube.obj");
	field->PreLoadTexture(L"Resources/cube/cube.jpg");
	field->SetViewProjection(viewProjection);
	field->SetMatProjection(matProjection);
	field->Initialize();
}

void Box::Update() {
	field->Update();
}

void Box::Draw() {
	field->Draw();
}