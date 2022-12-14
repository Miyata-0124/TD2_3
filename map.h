#pragma once

//横マスの数
static const int mapWidth = 7;
//縦マスの数
static const int mapHeight = 7;
//総ブロック数
static const int blockNum = mapWidth * mapHeight;

//マップ
static const int map[mapWidth][mapHeight] = {
	{0,0,0,0,0,0,0},
	{0,1,1,0,1,1,0},
	{0,1,0,0,0,1,0},
	{0,1,0,0,0,1,0},
	{0,1,0,0,0,1,0},
	{0,1,1,1,1,1,0},
	{0,0,0,0,0,0,0}
};