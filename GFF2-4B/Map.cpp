#include"DxLib.h"
#include"Map.h"
#include"InputData.h"

Map::Map()
{
    g_stage_x = 0;
    g_block_quantity = 20;// ƒuƒƒbƒN‚Ì”
	if ((g_haikei_image = LoadGraph("images/stage.png")) == -1);
	if (LoadDivGraph("images/block2.png", 4, 4, 1, 30, 30, g_block_image) == -1);
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
	DrawGraph(0, 120, g_haikei_image, TRUE);

    for (int i = 0; i < MAP_HIGHT; i++)
    {
       for (int j = 0; j < MAP_WIDTH; j++)
        {
           if (MAP_DATA[i][j] != 0)
           {
               if (MAP_DATA[i][j] <= g_block_quantity)DrawGraph(30 * j
                , 120+(30 * i), g_block_image[MAP_DATA[i][j]-1], TRUE);

           }
        }
    }
  

 
}
