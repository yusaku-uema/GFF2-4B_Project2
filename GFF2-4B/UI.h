#pragma once
#include"Title.h"
class UI
{
private:
  int g_time; //時間制限
  bool g_timeisup; //時間切れか判断。
  const int fps = 60; //60fpsで一秒
  int count; //秒数カウント
  int g_pickaxeimage; //ピッケルの画像
  int g_bombimage; //爆弾画像
  int g_Cursorimage; //カーソル画像
  int g_whiteimage; //白い画像
  int g_stage_item_quantity; //アイテムの量
public:
    int g_score; //スコア

    //コンストラクタ
    UI();
    //デストラクタ
    ~UI() {}
    void TimeMove();//制限時間処理
    void ScoreMove();//スコア処理
    void Draw()const;
    int gettimeisup();
   

  
};