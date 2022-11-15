#pragma once
#include"InputData.h"
class Map
{
private:
int g_block_image[4];
int g_block_image2[20];
int g_block_count;
int g_haikei_image;
//int g_stage_x;
//int g_block_quantity;// ブロックの数
public:
Map();
~Map() {};
void Move();
//マップの描画
void Draw() const;
//マップの初期設定
void MapInit();
void Stage();

unsigned int MAP_DATA[MAP_HIGHT][MAP_WIDTH];
};

