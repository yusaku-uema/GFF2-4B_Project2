#pragma once

class Fps
{
private:
	double timeFps;
	int timeStart;
	int countFlip;
	const double setFps = 60;
public:
	Fps(); //���������̂�
	void Avg(); //fps�̕��ς��Z�o
	void Draw(); //fps��\��
	void Wait(); //60fps�ɂȂ�悤�ҋ@
};
