#pragma once
#include"main.h"

class Help 
{
private:
    int g_Titleimage;
public:
    //�R���X�g���N�^
    Help();
    //�f�X�g���N�^
    ~Help() {}
    //�`��ȊO�̍X�V�����s
    void  Update() ;
    //�`��Ɋւ��邱�Ƃ�����
    void Draw() ;
    //�V�[���؂�ւ�
    void  ChangeScene();
   /* int g_image;*/
};

