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
	int g_item_selection; //�A�C�e���I��
	int g_item_image[3];	
	int g_item_cursor_image[3];

public:
	void Draw_Item(); //�A�C�e���`��
	void Item1(); //�悤�킩���A�_���֕����Ă���
}; 


