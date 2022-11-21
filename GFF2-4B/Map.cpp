#include "Map.h"



/***********************************************
*  ステージ情報取得　　　
************************************************/
int Map::GetMap(int x, int y,bool a)
{
	if (false == a) {
		if ((x >= 0 && MAP_HIGHT >= x) && (y >= 0 && MAP_WIDTH >= y))return MAP_DATA[x][y];
	}
	else
	{
		if ((x >= 0 && MAP_HIGHT >= x) && (y >= 0 && MAP_WIDTH >= y))return MAP_DATA_INIT[x][y];
	}
}

/***********************************************
*  ステージ書き換え　　
************************************************/

void Map::SetMap(int x, int y, int  type, bool a)
{
	if (false == a ) {
		if ((x >= 0 && MAP_HIGHT >= x) && (y >= 0 && MAP_WIDTH >= y))MAP_DATA[x][y] =type;
	}
	else
	{
		if ((x >= 0 && MAP_HIGHT >= x) && (y >= 0 && MAP_WIDTH >= y))MAP_DATA[x][y] =- type;
	}
}

/***********************************************
*  アイテムのステージ情報取得　　　
************************************************/

int Map::GetItemMap(int x, int y, bool a)
{
	if (false) {
		if ((x >= 0 && MAP_HIGHT >= x) && (y >= 0 && MAP_WIDTH >= y))return ITEM_DATA[x][y];
	}
	else
	{
		if ((x >= 0 && MAP_HIGHT >= x) && (y >= 0 && MAP_WIDTH >= y))return ITEM_DATA_INIT[x][y];
	}

}

/***********************************************
*  アイテムのステージ書き換え　　　
************************************************/
void Map::SetItmeMap(int x, int y, int type)
{
	if ((x >= 0 && MAP_HIGHT >= x) && (y >= 0 && MAP_WIDTH >= y))ITEM_DATA[x][y] = type;
}


