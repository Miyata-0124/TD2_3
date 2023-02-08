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

/*マップ1*/
//上
static const int map1Top[mapWidth][mapHeight] = {

	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},

};

//右
static const int map1Right[mapWidth][mapHeight] = {

	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},

};

//左
static const int map1Left[mapWidth][mapHeight] = {

	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
};

//前
static const int map1Front[mapWidth][mapHeight] = {

	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},

};

//後
static const int map1Behind[mapWidth][mapHeight] = {

	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},

};

//下
static const int map1Bottom[mapWidth][mapHeight] = {

	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},

};

/*マップ2*/
//上
static const int map2Top[mapWidth][mapHeight] = {

	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},

};

//右
static const int map2Right[mapWidth][mapHeight] = {

	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},

};

//左
static const int map2Left[mapWidth][mapHeight] = {

	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
};

//前
static const int map2Front[mapWidth][mapHeight] = {

	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},

};

//後
static const int map2Behind[mapWidth][mapHeight] = {

	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},

};

//下
static const int map2Bottom[mapWidth][mapHeight] = {

	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},

};

/*マップ3*/
//上
static const int map3Top[mapWidth][mapHeight] = {
	
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,0,0,1,1,0,0,0},
	{0,0,0,1,0,0,0,0,1,0,0,0},
	{0,0,0,1,0,0,0,0,1,0,0,0},
	{0,0,0,1,0,0,0,0,1,0,0,0},
	{0,0,0,1,0,0,0,0,1,0,0,0},
	{0,0,0,1,1,1,1,1,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
};

//右
static const int map3Right[mapWidth][mapHeight] = {
	
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
};

//左
static const int map3Left[mapWidth][mapHeight] = {
	
	{1,1,1,1,0,0,0,0,1,1,1,1},
	{1,1,1,1,0,0,0,0,1,1,1,1},
	{1,1,1,1,0,0,0,0,1,1,1,1},
	{1,1,1,1,0,0,0,0,1,1,1,1},
	{1,1,1,1,0,0,0,0,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,0,0,0,0,1,1,1,1},
	{1,1,1,1,0,0,0,0,1,1,1,1},
	{1,1,1,1,0,0,0,0,1,1,1,1},
	{1,1,1,1,0,0,0,0,1,1,1,1},
	{1,1,1,1,0,0,0,0,1,1,1,1},

};

//前
static const int map3Front[mapWidth][mapHeight] = {

	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,1,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},

};

//後
static const int map3Behind[mapWidth][mapHeight] = {

	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
};

//下
static const int map3Bottom[mapWidth][mapHeight] = {
	
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},

};

/*マップ4*/
//上
static const int map4Top[mapWidth][mapHeight] = {

	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,1,1,0,0,1,1,0,0,1,1,0},
	{0,1,0,0,0,0,0,0,0,0,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,0,0,0,0,0,0,0,1,0},
	{0,1,1,0,0,0,0,0,0,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
};

//右
static const int map4Right[mapWidth][mapHeight] = {

	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,0,0,1,1,0,0,1,1,1},
	{1,1,1,0,0,1,1,0,0,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
};

//左
static const int map4Left[mapWidth][mapHeight] = {

	{1,1,1,1,1,0,0,1,1,1,1,1},
	{1,1,1,1,1,0,0,1,1,1,1,1},
	{1,1,1,1,1,0,0,1,1,1,1,1},
	{1,1,1,1,1,0,0,1,1,1,1,1},
	{1,1,1,1,1,0,0,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,0,0,1,1,1,1,1},
	{1,1,1,1,1,0,0,1,1,1,1,1},
	{1,1,1,1,1,0,0,1,1,1,1,1},
	{1,1,1,1,1,0,0,1,1,1,1,1},
	{1,1,1,1,1,0,0,1,1,1,1,1},

};

//前
static const int map4Front[mapWidth][mapHeight] = {

	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},

};

//後
static const int map4Behind[mapWidth][mapHeight] = {

	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,1,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
};

//下
static const int map4Bottom[mapWidth][mapHeight] = {

	{1,0,0,0,0,1,1,0,0,0,0,1},
	{0,1,0,0,0,1,1,0,0,0,1,0},
	{0,0,1,0,0,0,0,0,0,1,0,0},
	{0,0,0,1,0,0,0,0,1,0,0,0},
	{0,0,0,0,1,0,0,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,0,0,1,0,0,0,0},
	{0,0,0,1,0,0,0,0,1,0,0,0},
	{0,0,1,0,0,0,0,0,0,1,0,0},
	{0,1,0,0,0,0,0,0,0,0,1,0},
	{1,0,0,0,0,0,0,0,0,0,0,1},

};

/*マップ5*/
//上
static const int map5Top[mapWidth][mapHeight] = {

	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
};

//右
static const int map5Right[mapWidth][mapHeight] = {

	{0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,1,1,1,1},
	{0,0,0,0,0,1,0,0,1,0,0,0},
	{0,0,0,0,0,1,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0},
	{1,1,1,1,1,1,1,1,1,0,0,0},
};

//左
static const int map5Left[mapWidth][mapHeight] = {

	{0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0},

};

//前
static const int map5Front[mapWidth][mapHeight] = {

	{1,1,1,1,1,0,0,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,0,0,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},

};

//後
static const int map5Behind[mapWidth][mapHeight] = {

	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0},
};

//下
static const int map5Bottom[mapWidth][mapHeight] = {

	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,0,0,1,1,1,1,1},
	{1,0,0,0,1,0,0,1,0,0,0,1},
	{1,0,0,0,1,0,0,1,0,0,0,1},
	{1,0,0,0,1,0,0,1,0,0,0,1},
	{1,0,0,0,1,0,0,1,0,0,0,1},
	{1,0,0,0,1,0,0,1,0,0,0,1},
	{1,0,0,0,1,0,0,1,0,0,0,1},
	{1,0,0,0,1,0,0,1,0,0,0,1},
	{1,1,1,1,1,0,0,1,1,1,1,1},

};

/*マップ6*/
//上
static const int map6Top[mapWidth][mapHeight] = {

	{0,0,1,1,1,1,1,1,1,1,1,0},
	{0,0,1,1,1,1,1,1,1,1,1,0},
	{0,0,1,0,0,0,0,0,0,0,1,0},
	{0,0,1,0,0,0,0,0,0,0,1,0},
	{0,0,1,0,0,0,0,0,0,0,1,0},
	{0,0,1,0,0,0,0,0,0,0,1,0},
	{1,1,1,0,0,0,0,0,0,0,1,0},
	{1,1,0,0,0,0,0,0,0,0,0,0},
	{1,1,0,0,0,0,0,0,0,0,0,0},
	{1,1,0,0,0,1,1,1,1,0,0,0},
	{1,1,0,0,0,1,1,1,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
};

//右
static const int map6Right[mapWidth][mapHeight] = {

	{1,0,0,0,1,1,1,1,0,0,0,1},
	{1,0,0,0,1,0,0,1,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,1,0,0,0,1},
	{1,0,0,0,1,0,0,1,0,0,0,1},
	{1,0,0,0,1,0,0,1,0,0,0,1},
	{1,0,0,0,1,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,1,0,0,0,0},
	{1,0,0,0,1,0,0,1,0,0,0,0},
	{1,0,0,0,1,0,0,1,0,0,0,1},
};

//左
static const int map6Left[mapWidth][mapHeight] = {

	{1,0,0,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,0,0,1,0,0,0},
	{0,0,0,1,0,0,0,0,1,0,0,0},
	{0,0,0,1,0,0,0,0,1,0,0,0},
	{0,0,0,1,0,0,0,0,1,0,0,0},
	{0,0,0,1,0,0,0,0,1,0,0,0},
	{0,0,0,1,0,0,1,1,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,0,0,0,0,1,1,1,1},

};

//前
static const int map6Front[mapWidth][mapHeight] = {

	{0,0,0,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0,0,0},
	{0,0,0,1,0,0,1,1,1,0,0,0},
	{0,0,0,1,0,0,1,1,1,0,0,0},
	{0,0,0,1,0,0,1,1,1,0,0,0},
	{0,0,0,1,0,0,1,1,1,0,0,0},
	{1,1,1,1,0,0,1,1,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0},

};

//後
static const int map6Behind[mapWidth][mapHeight] = {

	{0,0,0,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0},
	{1,1,1,1,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,0,0,1,1,1,1,1},
	{0,0,0,0,0,0,0,1,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0},
};

//下
static const int map6Bottom[mapWidth][mapHeight] = {

	{1,1,1,1,1,0,0,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1},

};

