#include "TimeBaseLoopExecuter.h"

double TimeBaseLoopExecuter::TimeAdjustment()
{
	// 今の時間を取得
	QueryPerformanceCounter(&mTimeEnd);
	// (今の時間 - 前フレームの時間) / 周波数 = 経過時間(秒単位)
	double frameTime = static_cast<double>(mTimeEnd.QuadPart - mTimeStart.QuadPart) / static_cast<double>(mTimeFreq.QuadPart);
	double fps = 0.0;
	//処理時間に余裕がある場合はその分待つ
	if (frameTime < FRAME_TIME)
	{
		//Sleepの時間を計算
		DWORD sleepTime = static_cast<DWORD>((FRAME_TIME - frameTime) * 1000);
		timeBeginPeriod(1);
		//寝る
		Sleep(sleepTime);
		timeEndPeriod(1);
	}
	fps = 1 / frameTime;

	//FPSを出力窓に出す
#ifdef _DEBUG
#ifdef UNICODE
	std::wstringstream stream;
#else
	std::stringstream stream;
#endif
	mFrameCount++;
	if (mFrameCount % mDebugCount == 0)
	{
		stream << std::to_string(fps).c_str() << " FPS" << std::endl;
		OutputDebugString(stream.str().c_str());
	}
#endif // _DEBUG
	mTimeStart = mTimeEnd;
	return fps;
}