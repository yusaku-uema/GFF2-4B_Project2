#include "Map.h"



/***********************************************
*  �X�e�[�W���擾�@�@�@
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
*  �X�e�[�W���������@�@
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
*  �A�C�e���̃X�e�[�W���擾�@�@�@
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
*  �A�C�e���̃X�e�[�W���������@�@�@
************************************************/
void Map::SetItmeMap(int x, int y, int type)
{
	if ((x >= 0 && MAP_HIGHT >= x) && (y >= 0 && MAP_WIDTH >= y))ITEM_DATA[x][y] = type;
}


