#pragma once

//1�u���b�N�̃T�C�Y
static const float blockSize = 1.0f;
//���}�X�̐�
static const int mapWidth = 9;
//�c�}�X�̐�
static const int mapHeight = 9;
//��ʂ̃u���b�N��
static const int oneSideBlockNum = mapWidth * mapHeight;
//���u���b�N��
static const int totalBlockNum = oneSideBlockNum * 6;

//�}�b�v

//��
static const int mapTop[mapWidth][mapHeight] = {
			  /*��*/

		{0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,1,1,0},
		{0,1,1,0,0,0,1,1,0},
		{0,0,0,0,0,0,0,0,0},
/*��*/	{0,0,0,0,0,0,0,0,0},	/*�E*/
		{0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,1,1,0},
		{0,1,1,0,0,0,1,1,0},
		{0,0,0,0,0,0,0,0,0},

			  /*�O*/
};

//�E
static const int mapRight[mapWidth][mapHeight] = {
			  /*��*/

		{0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,1,1,0},
		{0,1,1,0,0,0,1,1,0},
		{0,0,0,0,0,0,0,0,0},
/*��*/  {0,0,0,0,0,0,0,0,0},	/*��*/
		{0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,1,1,0},
		{0,1,1,0,0,0,1,1,0},
		{0,0,0,0,0,0,0,0,0},

			  /*�O*/
};

//��
static const int mapLeft[mapWidth][mapHeight] = {
			  /*��*/

		{0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,1,1,0},
		{0,1,1,0,0,0,1,1,0},
		{0,0,0,0,0,0,0,0,0},
/*��*/  {0,0,0,0,0,0,0,0,0},	/*��*/
		{0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,1,1,0},
		{0,1,1,0,0,0,1,1,0},
		{0,0,0,0,0,0,0,0,0},

			  /*�O*/
};

//�O
static const int mapFront[mapWidth][mapHeight] = {
			  /*��*/

		{0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,1,1,0},
		{0,1,1,0,0,0,1,1,0},
		{0,0,0,0,0,0,0,0,0},
/*��*/  {0,0,0,0,0,0,0,0,0},	/*�E*/
		{0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,1,1,0},
		{0,1,1,0,0,0,1,1,0},
		{0,0,0,0,0,0,0,0,0},

			  /*��*/
};

//��
static const int mapBehind[mapWidth][mapHeight] = {
			  /*��*/

		{0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,1,1,0},
		{0,1,1,0,0,0,1,1,0},
		{0,0,0,0,0,0,0,0,0},
/*�E*/  {0,0,0,0,0,0,0,0,0},	/*��*/
		{0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,1,1,0},
		{0,1,1,0,0,0,1,1,0},
		{0,0,0,0,0,0,0,0,0},

			  /*��*/
};

//��
static const int mapBottom[mapWidth][mapHeight] = {
			    /*��*/

		{0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,1,1,0},
		{0,1,1,0,0,0,1,1,0},
		{0,0,0,0,0,0,0,0,0},
/*��*/  {0,0,0,0,0,0,0,0,0},	/*�E*/
		{0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,1,1,0},
		{0,1,1,0,0,0,1,1,0},
		{0,0,0,0,0,0,0,0,0},

			  /*�O*/
};
