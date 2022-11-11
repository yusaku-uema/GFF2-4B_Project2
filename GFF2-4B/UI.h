#pragma once
#include"Title.h"
class UI
{
private:
 int g_score; //スコア
  int g_time; //時間制限
  bool g_timeisup; //時間切れか判断。
  const int fps = 60; //60fpsで一秒
  int count; //秒数カウント
public:
    //コンストラクタ
    UI();
    //デストラクタ
    ~UI() {}
    void TimeMove();//制限時間処理
    void ScoreMove();//スコア処理
    void Draw()const;
    int gettimeisup();
   

  
};