#include"DxLib.h"
#include"Map.h"
#include"InputData.h"

Map::Map()
{
    //g_stage_x = 0;
    //g_block_quantity = 20;// ƒuƒƒbƒN‚Ì”
    g_block_count = 0;
	if ((g_haikei_image = LoadGraph("images/stage.png")) == -1);
	if (LoadDivGraph("images/block2.png", 4, 4, 1, 30, 30, g_block_image) == -1);
    if (LoadDivGraph("images/team/block1.png", 4, 4, 1, 30, 30, g_block_image2) == -1);
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
            MAP_DATA[i][j] = 3/*GetRand(2) + 1*/;
            if (i > 17) MAP_DATA[i][j] = 0;
            else if (j < 5) MAP_DATA[i][j] = 4;
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
            if (MAP_DATA[i][j] < 4)DrawGraph(30 * j, 120+(30 * i), g_block_image[MAP_DATA[i][j]], TRUE);
           /* DrawFormatString(30 * j, 120+(30 * i), 0xffffff, "%d", MAP_DATA[i][j]);*/
        }
    }
   
}
