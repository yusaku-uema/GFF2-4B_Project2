#include "Map.h"

void Map::InitMap(int y, int x)
{
	MAP_DATA[y][x] = MAP_DATA_INIT[y][x];
}

/***********************************************
*  �X�e�[�W���擾�@�@�@
************************************************/
int Map::GetMap(int y, int x)
{
	if ((y >= 0 && MAP_HIGHT >= y) && (x >= 0 && MAP_WIDTH >= x))return MAP_DATA[y][x];
}

/***********************************************
*  �X�e�[�W���������@�@
************************************************/

void Map::SetMap(int y, int x, int  type, bool a)
{
	if (false == a ) {
		if ((y >= 0 && MAP_HIGHT >= y) && (x >= 0 && MAP_WIDTH >= x))MAP_DATA[y][x] =type;
	}
	else
	{
		if ((y >= 0 && MAP_HIGHT >= y) && (x >= 0 && MAP_WIDTH >= x))MAP_DATA[y][x] =- type;
	}
}

/***********************************************
*  �A�C�e���̃X�e�[�W���擾�@�@�@
************************************************/

int Map::GetItemMap(int y, int x, bool a)
{
	if (false) {
		if ((y >= 0 && MAP_HIGHT >= y) && (x >= 0 && MAP_WIDTH >= x))return ITEM_DATA[y][x];
	}
	else
	{
		if ((y >= 0 && MAP_HIGHT >= y) && (x >= 0 && MAP_WIDTH >= x))return ITEM_DATA_INIT[y][x];
	}

}

/***********************************************
*  �A�C�e���̃X�e�[�W���������@�@�@
************************************************/
void Map::SetItmeMap(int y, int x, int type)
{
	if ((y >= 0 && MAP_HIGHT >= y) && (x >= 0 && MAP_WIDTH >= x))ITEM_DATA[y][x] = type;
}


