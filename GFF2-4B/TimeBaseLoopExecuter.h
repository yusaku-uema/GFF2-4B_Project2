class Fps {
	int mStartTime = 0;         //測定開始時刻
	int mCount = 0;             //カウンタ
	float mFps = 0;             //fps
	static const int N = 60;//平均を取るサンプル数
	static const int FPS = 60;	//設定したFPS

public:
	Fps() {
		mStartTime = 0;
		mCount = 0;
		mFps = 0;
	}

	bool Update();
	void Wait();

};