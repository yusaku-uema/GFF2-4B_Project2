#include"KeyConfigScene.h"
#include"main.h"
#include"DxLib.h"

#define KEYCONFIG_FILE_NAME     "dat/KeyConfig.txt"     // �L�[�R���t�B�O�f�[�^�̃t�@�C����
#define INFO_X                  (10)                // ���̕`��J�n���W
#define INFO_Y                  (10)
#define INFO_SPACE              (24)                // ��s������ɋ󂯂�X�y�[�X
#define INFO_NAME_X             (140)               // ���͖���`�悷��w���W

// �L�[�R���t�B�O�Ώۂ̍���
int TargetIndex;

// �L�[�R���t�B�O�e���ڂ̖��O
static const char* g_KeyConfigMenuTable[KEYCONFIG_INPUT_NUM] =
{
    "�A�C�e���I��(��)",
    "�A�C�e���I��(�E)",
    "�Œ�",
    "�c���n�V",
    "���ړ�",
    "�E�ړ�",
    "��ړ�",
    "���ړ�",
    "����",
    "�W�����v",
    "�u���b�N�z�u",
};

KeyConfigScene::KeyConfigScene() {

   // �L�[�R���t�B�O�t�@�C����ǂݍ���
   if (keyconfig.Load(KEYCONFIG_FILE_NAME) == FALSE)
   {
       // �R���t�B�O�t�@�C�����ǂݍ��߂Ȃ�������f�t�H���g�ݒ�ɂ���
       keyconfig.SetDefault();
   }

    // �u�������͂��������牽�����Ȃ��v�t���O��|��
    InputWait = FALSE;
}

void  KeyConfigScene::Update(){
        // �L�[�R���t�B�O�̓��͏������s��
        keyconfig.InputProcess();

        // �u�������͂��������牽�����Ȃ��v�t���O�������Ă���ꍇ�͏����𕪊�
        if (InputWait == TRUE)
        {
            // �������͂�����������u�������͂��������牽�����Ȃ��v�t���O��|��
            if (keyconfig.CheckInput() == TRUE)
            {
                WaitTimer(250);
                InputWait = FALSE;
            }

        }
        else 
        {
            //// �L�[��p�b�h�̉�����Ԃ��`�F�b�N���āA��������Ă�����L�[�R���t�B�O�ݒ�ɔ��f������
            //if (keyconfig.UpdateInputTypeInfo(TargetIndex))
            //{
            //    // �����{�^���������ꂽ�玟�̍��ڂɈړ�����
            //    TargetIndex++;

            //    // �u�������͂��������牽�����Ȃ��v�t���O�𗧂Ă�
            //    InputWait = TRUE;
            //}
        }

        // ���ڂ̐������J��Ԃ�
        int DrawY = INFO_Y;
        for (int i = 0; i < KEYCONFIG_INPUT_NUM; i++)
        {
            int DrawColor;
            char InputString[256];

            // �ύX�Ώۂ̍��ڂ��ǂ����ŕ`��F��ς���
            DrawColor = TargetIndex == i ? GetColor(255, 0, 0) : GetColor(255, 255, 255);

            // ���ږ��̕`��
            DrawString(INFO_X, DrawY, g_KeyConfigMenuTable[i],  DrawColor);

            // ���͂Ɋ��蓖�Ă��Ă�����͖����擾����
            keyconfig.GetInputTypeString(i, InputString);

            // ���蓖�Ă��Ă�����͖���`�悷��
            DrawString(INFO_NAME_X, DrawY, InputString, DrawColor);

            // ���ڂ̕`��Y���W���P���ڕ����Ɉړ�����
            DrawY += INFO_SPACE;
        }
        // �S�Ă̓��͂̐ݒ肪�I������烋�[�v�𔲂���
        if (TargetIndex == KEYCONFIG_INPUT_NUM)
        {
            g_KeyCongifGameState=2;
        }

    if (g_KeyCongifGameState == 2) {
        // �L�[�R���t�B�O�ݒ��ۑ�����
        keyconfig.Save(KEYCONFIG_FILE_NAME);
        SetGameState(1);
    }

}
