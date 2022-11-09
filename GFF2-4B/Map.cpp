#include"DxLib.h"
#include"Map.h"
#include"InputData.h"

Map::Map()
{
	if ((g_haikei_image = LoadGraph("images/stage.png")) == -1);
	if (LoadDivGraph("images/block.png", 4, 4, 1, 30, 30, g_block_image) == -1);
}

void Map::Stage()
{
   

}

void Map::MapInit()
{
    for (int i = 0; i < MAP_HIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            MAP_DATA[i][j] = MAP_DATA_INIT[i][j];
 
        }
    }

}

void Map::Draw() const
{
	DrawGraph(0, 0, g_haikei_image, TRUE);
    SetDrawArea(115, 0, 1165, 600);

 
}
