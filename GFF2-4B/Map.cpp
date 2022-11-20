#include "Map.h"



/***********************************************
*  ステージ情報取得　　　
************************************************/
int Map::GetMap(int x, int y)
{
	if ((x >= 0 && MAP_HIGHT >= x) && (y >= 0 && MAP_WIDTH >= y))return MAP_DATA[x][y];
}

/***********************************************
*  ステージ書き換え　　
************************************************/

void Map::SetMap(int x, int y, int  type,bool)
{
	if (false) {
		if ((x >= 0 && MAP_HIGHT >= x) && (y >= 0 && MAP_WIDTH >= y))MAP_DATA[y][x] = type;
	}
	else
	{
		if ((x >= 0 && MAP_HIGHT >= x) && (y >= 0 && MAP_WIDTH >= y))MAP_DATA[y][x] - type;
	}
}

int Map::GetItemMap(int x, int y)
{
	if ((x >= 0 && MAP_HIGHT >= x) && (y >= 0 && MAP_WIDTH >= y))return ITEM_DATA_INIT[y][x];
}

void Map::SetItmeMap(int x, int y, int type)
{
	if ((x >= 0 && MAP_HIGHT >= x) && (y >= 0 && MAP_WIDTH >= y))ITEM_DATA_INIT[y][x] = type;
}
