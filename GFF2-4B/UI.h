#pragma once
#include"Title.h"
class UI
{
public:
    //�R���X�g���N�^
    UI();
    //�f�X�g���N�^
    ~UI() {}
    void TimeMove();//�������ԏ���
    void ScoreMove();//�X�R�A����
    void Draw()const;
    int g_score;
private:
    int g_time;
};