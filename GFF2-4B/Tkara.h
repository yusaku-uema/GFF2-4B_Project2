#pragma once
class Takara
{
private:
	int treasure; //��摜
	int g_stage;
	int BGM;
	
	int treasure1;
	int backgroundimage; //�w�i�摜
	int yagirusi;
	int g_MenuNumber; //���j���[�J�[�\���������ԂȂ̂��B
	int g_MenuX; //�J�[�\���̈ʒu
	int g_KeyFlg; //�������̓L�[��
	int g_OldKey; //�O��̓���
	int g_NowKey; //����̓��̓L�[
	int takaranum;
	int takaraX;
	int takaraOpen;
	int takaraNotopen;
	int FPS;
	int TimeLimet;
	bool sousa;
	bool takaraflg; //�󂢂Ă���̂�

	//�󔠂̍\����
	struct TAKARA {
		int flg; //�g�p�t���O
		int type; //�^�C�v
		int x, y; //���Wx,y
		int point; //��̓��_	
	};
	//�G�@
	struct TAKARA g_treasurebox[6];

	//���̍\����
	struct ARROW
	{
		int x, y;      //���Wx,y
		int no;
		int oldkey;
	};
	//���
	struct ARROW g_arrow;

public:
	void Draw();
	void init();
	void ArrowControl();
};
