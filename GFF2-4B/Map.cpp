//#include"DxLib.h"
//#include"Map.h"
//#include"InputData.h"
//#define _USE_MATH_DEFINES
//#include <math.h>
//
//
//Map::Map()
//{
//    g_stage_x = 0;
//    g_block_quantity = 20;// ブロックの数
//	if ((g_haikei_image = LoadGraph("images/stage.png")) == -1);
//	if (LoadDivGraph("images/block3.png", 4, 4, 1, 30, 30, g_block_image) == -1);
//	g_scroll_x = 0;
//}
//
//
//void Map::Sousa()
//{
//	
//
//}
//
//void Map::MapInit()
//{
//    /*for (int i = 0; i < MAP_HIGHT; i++)
//    {
//        for (int j = 0; j < MAP_WIDTH; j++)
//        {
//            MAP_DATA[i][j] = MAP_DATA_INIT[i][j];
//
//        }
//    }*/
//
//	for (int i = 0; i < MAP_HIGHT; i++)
//	{
//		for (int j = 0; j < MAP_WIDTH; j++)
//		{
//			if (ITEM_DATA[i][j] > 0)
//			{
//				g_item[g_item_count].x = j * 30;
//				g_item[g_item_count].y = i * 30;
//				g_item[g_item_count].point = 100;
//				g_item[g_item_count].flg = TRUE;
//				if (ITEM_DATA[i][j] == 1)g_item[g_item_count].type = 1;
//				if (ITEM_DATA[i][j] == 2)g_item[g_item_count].type = 2;
//				g_item_count++;
//			}
//			MAP_DATA[i][j] = MAP_DATA_INIT[i][j];
//			if (MAP_DATA[i][j] == 3)MAP_DATA[i][j] = GetRand(2) + 1;
//			//MAP_DATA[i][j] = 3/*GetRand(2) + 1*/;
//			//if (i > 17) MAP_DATA[i][j] = 4;
//			//else if (j < 5 && j > 2) MAP_DATA[i][j] = 0;
//		}
//	}
//
//}
//
//void Map::Draw() const
//{
//	/*DrawGraph(0, 0, g_haikei_image, TRUE);
//
//    for (int i = 0; i < MAP_HIGHT; i++)
//    {
//       for (int j = 0; j < MAP_WIDTH; j++)
//        {
//           if (MAP_DATA[i][j] != 0)
//           {
//               if (MAP_DATA[i][j] <= g_block_quantity)DrawGraph(30 * j
//                , 0+(30 * i), g_block_image[MAP_DATA[i][j]-1], TRUE);
//
//           }
//        }
//    }*/
//    //SetDrawArea(0, 0, 1280, 600);
//	DrawGraph(0, 0, g_haikei_image, TRUE);
//    
//	for (int i = 0; i < MAP_HIGHT; i++)
//	{
//		for (int j = 0; j < MAP_WIDTH; j++)
//		{
//			if (MAP_DATA[i][j] > 0)
//			{
//				DrawGraph((30 * j) + g_scroll_x, 30 * i, g_block_image[MAP_DATA[i][j]], TRUE);
//			}
//
//			//DrawFormatString(30 * j, 30 * i, 0xffffff, "%d", MAP_DATA[i][j]);
//		}
//	}
// 
//
//
//	//UI
//	//DrawBox(30, 10, 1250, 110, 0x000000, TRUE);
//	//DrawBox(30, 10, 1250, 110, 0xFFFFFF, FALSE);
//	//int g_stage_item_quantity = 3; //表示するアイテムの個数
//	//int a = (1280 - (110 * (g_stage_item_quantity - 1))) / 2;
//	////int a = 1280 / 2;
//	//float size[3];
//	//size[0] = 0.7;
//	//size[1] = 0.7;
//	//size[2] = 0.7;
//
//	//size[g_item_selection] = 1.0;
//
//	////DrawFormatString(100, 0, 0xffffff, "%d = block_count, %d = break block", g_block_count, g_break_block_count);
//
//	//for (int i = 0; i < 3; i++)
//	//{
//	//	DrawRotaGraph(a + (110 * i), 55, size[i], M_PI / 180 * 0, g_item_cursor_image[i], TRUE, FALSE);
//	//}
//
//}
//
