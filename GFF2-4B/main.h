#pragma once

#define MAP_HIGHT 21
#define MAP_WIDTH 106

#define PLAYER_SIZE  30

enum ArrayImages { Title_Images, Player_Images, GameMain_Images, Block_Images, Player_CursorImages, Item_Images,Pickaxe_Images,Item_cursor,
    GameOver_Images, GameClear_Images, Life_Images}; //�摜�Ăяo����
enum Sounds { Title_SE}; //BGM�Ȃ�A���Z_BGM, SE�Ȃ�


void  SetGameState(int a); //�V�[���؂�ւ�
int GetArrayImages(int type, int num); //�摜�Ăяo��
int GetSounds(int type); //BGM��SE�Ăяo��

int LoadImages(); //�摜�Ǎ���
int LoadSounds(void); //BGM,SE��Ǎ���