#pragma once
#include"AbstractScene.h"
class Credit:
	public AbstractScene
{
public:
	////コンストラクタ
	//Credit();
	////デストラクタ
	//~Credit();
	//描画以外の更新を実行
	AbstractScene* Update() override;
	//描画に関することを実装
	void Draw()const override;
};

