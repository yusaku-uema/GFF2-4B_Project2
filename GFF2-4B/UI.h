#pragma once
#include"Title.h"
class UI
{
private:
  int g_time; //���Ԑ���
  bool g_timeisup; //���Ԑ؂ꂩ���f�B
  const int fps = 60; //60fps�ň�b
  int count; //�b���J�E���g
  int g_pickaxeimage; //�s�b�P���̉摜
  int g_bombimage; //���e�摜
  int g_Cursorimage; //�J�[�\���摜
  int g_whiteimage; //�����摜
  int g_stage_item_quantity; //�A�C�e���̗�
public:
    int g_score; //�X�R�A

    //�R���X�g���N�^
    UI();
    //�f�X�g���N�^
    ~UI() {}
    void TimeMove();//�������ԏ���
    void ScoreMove();//�X�R�A����
    void Draw()const;
    int gettimeisup();
   

  
};