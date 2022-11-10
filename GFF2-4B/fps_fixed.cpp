#include "DxLib.h"
#include "fps_fixed.h"

Fps::Fps()
{
	timeFps = 0;
	timeStart = 0;
	countFlip = 0;
}

void Fps::Avg()
{
	if (countFlip == 0)
	{
		timeStart = GetNowCount();
	}

	if (countFlip == setFps)
	{
		int a = GetNowCount();
		timeFps = 1000.f / ((a - timeStart) / setFps);
		timeStart = a;
		countFlip = 0;
	}

	countFlip++;
}

void Fps::Draw()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", timeFps);
}

void Fps::Wait()
{
	int b = GetNowCount() - timeStart;
	int a = countFlip * 1000 / setFps - b;

	if (a > 0)
	{
		Sleep(a);
	}
}

