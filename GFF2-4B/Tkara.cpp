#include"Tkara.h"
#include"DxLib.h"
#include"main.h"

void Takara::Draw()
{
	if (CheckSoundMem(BGM) != 1) {   //SEが流れていなかったら再生
		ChangeVolumeSoundMem(255 * 25 / 100, BGM); //SE音量調整 255最大音量から80%再生
		PlaySoundMem(BGM, DX_PLAYTYPE_LOOP, TRUE); //SE再生
	}
	DrawGraph(0,0, backgroundimage, TRUE); //宝箱の表示
	if (sousa == FALSE) {
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;
	}
	switch (g_stage)
	{
	case 0:
		
		for (int i = 0; i < 4; i++)
		{
			g_treasurebox[i].x = 400;
			g_MenuX = 400;
			g_treasurebox[i].x = g_treasurebox[i].x +(i * 120);
			if (g_treasurebox[i].type == 0) {
				DrawGraph(g_treasurebox[i].x, g_treasurebox[i].y, treasure, TRUE); //宝箱の表示
			}
			else
			{
				DrawGraph(g_treasurebox[i].x, g_treasurebox[i].y, treasure1, TRUE); //宝箱の表示
				DrawFormatString(g_treasurebox[i].x, 220, GetColor(255, 0, 0), "%+d", g_treasurebox[i].point);
			}
		}


		//メニューカーソル移動処理
		if (g_KeyFlg & PAD_INPUT_RIGHT) {
			if (++g_MenuNumber > 3) g_MenuNumber = 0; //下十字キー押されたら　MenuNumberを+1する。
		}
		if (g_KeyFlg & PAD_INPUT_LEFT) {
			if (--g_MenuNumber < 0) g_MenuNumber = 3; //上十字キー押されたら、MenuNumberを-1する。
		}

		break;
	case 1:
		for (int i = 0; i < 3; i++)
		{
			g_treasurebox[i].x = 500;
			g_MenuX = 500;
			g_treasurebox[i].x = g_treasurebox[i].x + (i * 120);
			if (g_treasurebox[i].type == 0) {
				DrawGraph(g_treasurebox[i].x, g_treasurebox[i].y, treasure, TRUE); //宝箱の表示
			}
			else
			{
				DrawGraph(g_treasurebox[i].x, g_treasurebox[i].y, treasure1, TRUE); //宝箱の表示
				DrawFormatString(g_treasurebox[i].x, 220, GetColor(255, 0, 0), "%+d", g_treasurebox[i].point);
			}
		}

		if (g_KeyFlg & PAD_INPUT_RIGHT) {
			if (++g_MenuNumber > 2) g_MenuNumber = 0; //下十字キー押されたら　MenuNumberを+1する。
		}
		if (g_KeyFlg & PAD_INPUT_LEFT) {
			if (--g_MenuNumber < 0) g_MenuNumber = 2; //上十字キー押されたら、MenuNumberを-1する。
		}

		break;

	case 2:
		for (int i = 0; i < 6; i++)
		{
			g_treasurebox[i].x = 300;
			g_MenuX = 300;
			g_treasurebox[i].x = g_treasurebox[i].x + (i * 120);
			if (g_treasurebox[i].type == 0) {
				DrawGraph(g_treasurebox[i].x, g_treasurebox[i].y, treasure, TRUE); //宝箱の表示
			}
			else
			{
				DrawGraph(g_treasurebox[i].x, g_treasurebox[i].y, treasure1, TRUE); //宝箱の表示
				DrawFormatString(g_treasurebox[i].x, 220, GetColor(255, 0, 0), "%+d", g_treasurebox[i].point);
			}
		}

		//メニューカーソル移動処理
		if (g_KeyFlg & PAD_INPUT_RIGHT) {
			if (++g_MenuNumber > 5) g_MenuNumber = 0; //下十字キー押されたら　MenuNumberを+1する。
		}
		if (g_KeyFlg & PAD_INPUT_LEFT) {
			if (--g_MenuNumber < 0) g_MenuNumber = 5; //上十字キー押されたら、MenuNumberを-1する。
		}

		break;
	}

	ArrowControl();

}


/***********************************************
 * 矢印の処理
 * 引  数:なし
 * 戻り値:なし
 ***********************************************/
void Takara::ArrowControl()
{
	DrawFormatString(500, 50, GetColor(255, 0, 0), "Bボタンで宝箱をあける");
	g_MenuX = g_MenuX+(g_MenuNumber * 120); //　カーソル位置60
	if (g_KeyFlg & PAD_INPUT_B && g_treasurebox[g_MenuNumber].type == 0 && takaranum > 0)
	{
		g_treasurebox[g_MenuNumber].type = 1;
		SetScore(g_treasurebox[g_MenuNumber].point, TRUE);
		--takaranum;
		++takaraOpen;
	}
	DrawGraph(g_MenuX, 420, yagirusi, TRUE);

	if (takaranum == 0 && takaraNotopen > takaraOpen)
	{
		DrawFormatString(250, 600, GetColor(255, 0, 0), "カギを持っていない、ステージのどこかにあるはずだ！");
		sousa = TRUE;
		if (++FPS % 60 == 0)
		{
			--TimeLimet;
		}

		if (TimeLimet == 0)
		{
			StopSoundMem(BGM);
			SetGameState(3);
		}
	}

	if (takaranum == 0 && takaraNotopen <= takaraOpen)
	{
		sousa = TRUE;
		if (++FPS % 60 == 0)
		{
			--TimeLimet;
		}

		if (TimeLimet == 0)
		{
			StopSoundMem(BGM);
			SetGameState(3);
		}
	}
}



void Takara::init()
{
	BGM = LoadSoundMem("BGM/takara.mp3");//破壊音BGM
	sousa = FALSE;
	FPS = 0;
	TimeLimet = 4;
	takaranum = Getkagi();
	takaraOpen = 0;
	takaraNotopen = 0;
	g_stage = Getstage();
	treasure = LoadGraph("images/宝箱１_transparent.png");
	treasure1 = LoadGraph("images/宝箱２_transparent.png");
	yagirusi= LoadGraph("images/arrowt.png");
	backgroundimage = LoadGraph("images/InputRankigImage.png");
	switch (g_stage)
	{
	case 0:
		takaraNotopen = 4;
		for (int i = 0; i < 4; i++)
		{
			g_treasurebox[i].point = GetRand(10000);
			g_treasurebox[i].y = 300;
			g_treasurebox[i].type = 0;
		}
		break;
	case 1:
		takaraNotopen = 3;
		for (int i = 0; i < 3; i++)
		{
			g_treasurebox[i].point = GetRand(10000);
			g_treasurebox[i].y = 300;
			g_treasurebox[i].type = 0;
		}
		break;
	case 2:
		takaraNotopen = 6;
		for (int i = 0; i < 6; i++)
		{
			g_treasurebox[i].point = GetRand(10000);
			g_treasurebox[i].y = 300;
			g_treasurebox[i].type = 0;
		}
		break;

	}
	SetGameState(9);
}

