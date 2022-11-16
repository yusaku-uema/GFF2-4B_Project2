#pragma once
#include "AdstractScene.h"
#include"Map.h"
#include"UI.h"
#include"Ranking.h"

class GameMain :public AdstractScene
{
private:
   /* Map map;
    UI ui;
    Player player;
    RANKING ranking;*/

public:
    //コンストラクタ
    GameMain();
    //描画以外の更新を実行
   void Update() override;
    //描画に関することを実装
    void Draw() const override;
    //シーン切り替え
    AdstractScene* ChangeScene();
};

