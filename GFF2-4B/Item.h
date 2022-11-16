#pragma once

struct ITEM {
	bool flg;
	int x;
	int y;
	int point;
	int type;
};
struct ITEM g_item[10];

class Item
{
private:
	bool g_itme_flg;
	int g_item_selection; //アイテム選択
	int g_item_image[3];	
	int g_item_cursor_image[3];

public:
	void Draw_Item(); //アイテム描画
	void Item1(); //ようわからん、神里へ聞いてちょ
}; 


