#pragma once
#include"Title.h"
class UI
{
private:
 int g_score; //�X�R�A
  int g_time; //���Ԑ���
  bool g_timeisup; //���Ԑ؂ꂩ���f�B
  const int fps = 60; //60fps�ň�b
  int count; //�b���J�E���g
public:
    //�R���X�g���N�^
    UI();
    //�f�X�g���N�^
    ~UI() {}
    void TimeMove();//�������ԏ���
    void ScoreMove();//�X�R�A����
    void Draw()const;
    int gettimeisup();
   

  
};