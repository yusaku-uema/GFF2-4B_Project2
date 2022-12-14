#pragma once

#define MAP_HIGHT 21
#define MAP_WIDTH 150

#define BLOCK_SIZE  30
#define PLAY_HIGHT_SIZE  25
#define PLAY_WIDTH_SIZE  21

enum ArrayImages { Title_Images, Player_Images, GameMain_Images, Block_Images, Player_CursorImages, Item_Images,Pickaxe_Images,Item_cursor, Box_images, Box2_images,
    GameOver_Images, GameClear_Images, Life_Images,KiraKira_Images, Help_Images}; //画像呼び出し名

enum Sounds { Title_SE,Title_BGM}; //BGMなら、○〇_BGM, SEなら


void  SetGameState(int a); //シーン切り替え
int GetArrayImages(int type, int num); //画像呼び出し
int GetSounds(int type); //BGMやSE呼び出し
int Getkagi();
void Setkagi(int a);
void Setstage(int a);
int Getstage();
int GetScore(); //スコア取得
void SetScore(float a,bool b); //スコアを変更

int LoadImages(); //画像読込み
int LoadSounds(void); //BGM,SEを読込み