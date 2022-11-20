#pragma once
#include "AdstractScene.h"

class End :
	public AdstractScene
{
private:


public:
	End();
	~End() {}
	//描画以外の更新を実行
	void  Update() override;
	//描画に関することを実装
	void Draw() const override;
	AdstractScene* ChangeScene();
};
