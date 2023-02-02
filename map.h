#pragma once

//1ブロックのサイズ
static const float blockSize = 1.0f;
//横マスの数
static const int mapWidth = 12;
//縦マスの数
static const int mapHeight = 12;
//一面のブロック数
static const int oneSideBlockNum = mapWidth * mapHeight;
//総ブロック数
static const int totalBlockNum = oneSideBlockNum * 6;

//マップ
static int mapTop[mapWidth][mapHeight];		//上
static int mapRight[mapWidth][mapHeight];	//右
static int mapLeft[mapWidth][mapHeight];	//左
static int mapFront[mapWidth][mapHeight];	//前
static int mapBehind[mapWidth][mapHeight];	//後
static int mapBottom[mapWidth][mapHeight];	//下

//上
static const int map1Top[mapWidth][mapHeight] = {
	/*             /*後*/

	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*左*/{0,0,0,0,0,0,0,0,0,0,0,0},	/*右*/
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,1,1,1,0,0,0,0},
	/*  */{0,0,0,0,0,1,1,1,0,0,0,0},
	/*  */{0,0,0,0,0,1,1,1,0,0,0,0},

	/*             /*前*/
};

//右
static const int map1Right[mapWidth][mapHeight] = {
	/*             /*後*/

	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*上*/{0,0,0,0,0,0,0,0,0,0,0,0},	/*下*/
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},

	/*             /*前*/
};

//左
static const int map1Left[mapWidth][mapHeight] = {
	/*             /*後*/

	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*下*/{0,0,0,0,0,0,0,0,0,0,0,0},	/*上*/
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},

	/*             /*前*/
};

//前
static const int map1Front[mapWidth][mapHeight] = {
	/*             /*上*/

	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*左*/{0,0,0,0,0,0,0,0,0,0,0,0},	/*右*/
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},

	/*             /*下*/
};

//後
static const int map1Behind[mapWidth][mapHeight] = {
	/*             /*下*/

	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*左*/{0,0,0,0,0,0,0,0,0,0,0,0},	/*右*/
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},

	/*             /*上*/
};

//下
static const int map1Bottom[mapWidth][mapHeight] = {
	/*             /*後*/

	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*左*/{0,0,0,0,0,0,0,0,0,0,0,0},	/*右*/
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},
	/*  */{0,0,0,0,0,0,0,0,0,0,0,0},

	/*             /*前*/
};