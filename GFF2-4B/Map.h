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
//int g_block_quantity;// �u���b�N�̐�
public:
Map();
~Map() {};
void Move();
//�}�b�v�̕`��
void Draw() const;
//�}�b�v�̏����ݒ�
void MapInit();
void Stage();

unsigned int MAP_DATA[MAP_HIGHT][MAP_WIDTH];
};

