#include "Map.h"

void Map::InitMap(int y, int x)
{
	MAP_DATA[y][x] = MAP_DATA_INIT[y][x];
}

/***********************************************
*  ステージ情報取得　　　
************************************************/
int Map::GetMap(int y, int x)
{
	if ((x >= 0 && MAP_HIGHT >= x) && (y >= 0 && MAP_WIDTH >= y))return MAP_DATA[y][x];
}

/***********************************************
*  ステージ書き換え　　
************************************************/

void Map::SetMap(int y, int x, int  type, bool a)
{
	if (false == a ) {
		if ((x >= 0 && MAP_HIGHT >= x) && (y >= 0 && MAP_WIDTH >= y))MAP_DATA[y][x] =type;
	}
	else
	{
		if ((x >= 0 && MAP_HIGHT >= x) && (y >= 0 && MAP_WIDTH >= y))MAP_DATA[y][x] =- type;
	}
}

/***********************************************
*  アイテムのステージ情報取得　　　
************************************************/

int Map::GetItemMap(int y, int x, bool a)
{
	if (false) {
		if ((x >= 0 && MAP_HIGHT >= x) && (y >= 0 && MAP_WIDTH >= y))return ITEM_DATA[y][x];
	}
	else
	{
		if ((x >= 0 && MAP_HIGHT >= x) && (y >= 0 && MAP_WIDTH >= y))return ITEM_DATA_INIT[y][x];
	}

}

/***********************************************
*  アイテムのステージ書き換え　　　
************************************************/
void Map::SetItmeMap(int y, int x, int type)
{
	if ((x >= 0 && MAP_HIGHT >= x) && (y >= 0 && MAP_WIDTH >= y))ITEM_DATA[y][x] = type;
}


