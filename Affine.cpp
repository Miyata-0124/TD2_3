#include "Affine.h"
#include <cmath>

void Affine::CreateMatIdentity(Matrix4& matrix)
{
	matrix = {
	   1.0f,0,0,0,
	   0,1.0f,0,0,
	   0,0,1.0f,0,
	   0,0,0,1.0f,
	};
}

void Affine::CreateMatScale(Matrix4& matrix, Vector3 scale)
{
	Matrix4 matScale;
	CreateMatIdentity(matScale);
	matScale.m[0][0] = scale.x;
	matScale.m[1][1] = scale.y;
	matScale.m[2][2] = scale.z;
	matrix *= matScale;
}

void Affine::CreateMatRotX(WorldTransform& worldTransform, Vector3 rot) {
	Matrix4 matrotX;
	CreateMatIdentity(matrotX);
	matrotX.m[1][1] = cos(rot.x);
	matrotX.m[1][2] = sin(rot.x);
	matrotX.m[2][1] = -sin(rot.x);
	matrotX.m[2][2] = cos(rot.x);

	worldTransform.matWorld_ *= matrotX;
}
void Affine::CreateMatRotY(Matrix4& matrix, Vector3 rot) {
	Matrix4 matrotY;
	CreateMatIdentity(matrotY);
	matrotY.m[1][1] = cos(rot.y);
	matrotY.m[1][2] = sin(rot.y);
	matrotY.m[2][1] = -sin(rot.y);
	matrotY.m[2][2] = cos(rot.y);

	matrix *= matrotY;
}
void Affine::CreateMatRotZ(WorldTransform& worldTransform, Vector3 rot) {
	Matrix4 matrotZ;
	CreateMatIdentity(matrotZ);
	matrotZ.m[0][0] = cos(rot.z);
	matrotZ.m[0][1] = sin(rot.z);
	matrotZ.m[1][0] = -sin(rot.z);
	matrotZ.m[1][1] = cos(rot.z);

	worldTransform.matWorld_ *= matrotZ;
}


void Affine::CreateMatRot(Matrix4& matrix, Vector3 rot)
{
	Matrix4 matrotX;
	CreateMatIdentity(matrotX);
	matrotX.m[1][1] = cos(rot.x);
	matrotX.m[1][2] = sin(rot.x);
	matrotX.m[2][1] = -sin(rot.x);
	matrotX.m[2][2] = cos(rot.x);

	Matrix4 matrotY;
	CreateMatIdentity(matrotY);
	matrotY.m[0][0] = cos(rot.y);
	matrotY.m[0][2] = -sin(rot.y);
	matrotY.m[2][0] = sin(rot.y);
	matrotY.m[2][2] = cos(rot.y);

	Matrix4 matrotZ;
	CreateMatIdentity(matrotZ);
	matrotZ.m[0][0] = cos(rot.z);
	matrotZ.m[0][1] = sin(rot.z);
	matrotZ.m[1][0] = -sin(rot.z);
	matrotZ.m[1][1] = cos(rot.z);

	Matrix4 matRot;
	CreateMatIdentity(matRot);

	if (face == 0) {
		matRot *= matrotY;
		matRot *= matrotZ;
		matRot *= matrotX;
		matrix *= matRot;
	}
	else {
		matRot *= matrotX;
		matRot *= matrotZ;
		matRot *= matrotY;
		matrix *= matRot;
	}

}

void Affine::CreateMatTrans(WorldTransform& worldTransform, Vector3 trans)
{
	Matrix4  matTrams;
	CreateMatIdentity(matTrams);
	matTrams.m[3][0] = trans.x;
	matTrams.m[3][1] = trans.y;
	matTrams.m[3][2] = trans.z;

	worldTransform.matWorld_ *= matTrams;
}

void Affine::CreateMatTransA(Matrix4& matrix, Vector3 trans)

{
	Matrix4  matTrams;
	CreateMatIdentity(matTrams);
	matTrams.m[3][0] = trans.x;
	matTrams.m[3][1] = trans.y;
	matTrams.m[3][2] = trans.z;

	matrix *= matTrams;
}

void Affine::CreateAffine(WorldTransform& worldTransform, int face)
{
	CreateMatIdentity(worldTransform.matWorld_);
	CreateMatScale(worldTransform.matWorld_, worldTransform.scale_);
	//CreateMatRot(worldTransform.matWorld_, worldTransform.rotation_,face);
	CreateMatTrans(worldTransform.matWorld_, worldTransform.translation_);
}

void Affine::CreateAffineX(WorldTransform& worldTransform)
{
	CreateMatIdentity(worldTransform.matWorld_);
	CreateMatScale(worldTransform.matWorld_, worldTransform.scale_);
	//CreateMatRotZ(worldTransform.matWorld_, worldTransform.rotation_);
	//CreateMatRotX(worldTransform.matWorld_, worldTransform.rotation_);
	CreateMatRotY(worldTransform.matWorld_, worldTransform.rotation_);
	CreateMatTrans(worldTransform.matWorld_, worldTransform.translation_);
}

void Affine::CreateAffineZ(WorldTransform& worldTransform)
{
	CreateMatIdentity(worldTransform.matWorld_);
	CreateMatScale(worldTransform.matWorld_, worldTransform.scale_);

	//CreateMatRot(worldTransform.matWorld_, worldTransform.rotation_);
	CreateMatTransA(worldTransform.matWorld_, worldTransform.translation_);
}

Vector3 Affine::MatVector(Matrix4 matrix, Vector3 vector)
{
	Vector3 matVector = { 0,0,0 };
	matVector.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0];
	matVector.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1];
	matVector.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2];
	return matVector;
}

Vector3 Affine::GetWorldTransform(Matrix4 matrix)
{
	Vector3 matTrans;
	matTrans.x = matrix.m[3][0];
	matTrans.y = matrix.m[3][1];
	matTrans.z = matrix.m[3][2];
	return matTrans;
}
