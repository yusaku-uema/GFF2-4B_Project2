class Fps {
	int mStartTime = 0;         //����J�n����
	int mCount = 0;             //�J�E���^
	float mFps = 0;             //fps
	static const int N = 60;//���ς����T���v����
	static const int FPS = 60;	//�ݒ肵��FPS

public:
	Fps() {
		mStartTime = 0;
		mCount = 0;
		mFps = 0;
	}

	bool Update();
	void Wait();

};