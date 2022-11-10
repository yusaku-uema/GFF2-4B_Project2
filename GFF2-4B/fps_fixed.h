#pragma once

class Fps
{
private:
	double timeFps;
	int timeStart;
	int countFlip;
	const double setFps = 60;
public:
	Fps(); //‰Šú‰»ˆê‰ñ‚Ì‚İ
	void Avg(); //fps‚Ì•½‹Ï‚ğZo
	void Draw(); //fps‚ğ•\¦
	void Wait(); //60fps‚É‚È‚é‚æ‚¤‘Ò‹@
};
