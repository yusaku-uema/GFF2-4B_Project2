#pragma once

#define MAP_HIGHT 24
#define MAP_WIDTH 86
#define PLAYER_SIZE  30

enum ArrayImages { Title_Images, Player_Images, GameMain_Images, Block_Images, Player_CursorImages, Item_Images,Pickaxe_Images,Box_images,Box2_images}; //�摜�Ăяo����
enum Sounds { Title_SE}; //BGM�Ȃ�A���Z_BGM, SE�Ȃ�


void  SetGameState(int a); //�V�[���؂�ւ�
int GetArrayImages(int type, int num); //�摜�Ăяo��
int GetSounds(int type); //BGM��SE�Ăяo��

int LoadImages(); //�摜�Ǎ���
int LoadSounds(void); //BGM,SE��Ǎ���