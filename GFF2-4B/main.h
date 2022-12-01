#pragma once

#define MAP_HIGHT 21
#define MAP_WIDTH 150

#define BLOCK_SIZE  30
#define PLAY_SIZE  25

enum ArrayImages { Title_Images, Player_Images, GameMain_Images, Block_Images, Player_CursorImages, Item_Images,Pickaxe_Images,Item_cursor, Box_images, Box2_images,
    GameOver_Images, GameClear_Images, Life_Images}; //画像呼び出し名

enum Sounds { Title_SE, Stage_BGM}; //BGMなら、○〇_BGM, SEなら


void  SetGameState(int a); //シーン切り替え
int GetArrayImages(int type, int num); //画像呼び出し
int GetSounds(int type); //BGMやSE呼び出し
int GetScore(); //スコア取得
void SetScore(int a); //スコアを変更

int LoadImages(); //画像読込み
int LoadSounds(void); //BGM,SEを読込み