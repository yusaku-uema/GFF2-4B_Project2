#pragma once
#include"Title.h"
class UI
{
public:
    //コンストラクタ
    UI();
    //デストラクタ
    ~UI() {}
    void TimeMove();//制限時間処理
    void ScoreMove();//スコア処理
    void Draw()const;
    int g_score;
private:
    int g_time;
};