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
	if ((y >= 0 && MAP_HIGHT >= y) && (x >= 0 && MAP_WIDTH >= x))return MAP_DATA[y][x];
}

/***********************************************
*  ステージ書き換え　　
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
*  アイテムのステージ情報取得　　　
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
*  アイテムのステージ書き換え　　　
************************************************/
void Map::SetItmeMap(int y, int x, int type)
{
	if ((y >= 0 && MAP_HIGHT >= y) && (x >= 0 && MAP_WIDTH >= x))ITEM_DATA[y][x] = type;
}


