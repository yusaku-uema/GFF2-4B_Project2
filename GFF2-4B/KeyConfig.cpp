// �L�[�R���t�B�O�����̃v���O����

#include "KeyConfig.h"
#include "DxLib.h"
#include <string.h>

#define MAX_GAMEPAD_NUM             (16)            // �`�F�b�N����Q�[���p�b�h�̐�
#define KEY_STATE_BUFFER_SIZE       (256)           // �L�[�{�[�h�̓��͏�Ԃ��擾���邽�߂̃o�b�t�@�̃T�C�Y
#define DIRECTINPUT_MAX_VALUE       (1000)          // DirectInput ���瓾����l�̍ő�l

// DirectInput �̓��͏��^�C�v
#define DIRECTINPUT_TYPE_X          (0)             // �������͂̂w��
#define DIRECTINPUT_TYPE_Y          (1)             // �������͂̂x��
#define DIRECTINPUT_TYPE_Z          (2)             // �������͂̂y��
#define DIRECTINPUT_TYPE_RX         (3)             // �������͂̂w����]
#define DIRECTINPUT_TYPE_RY         (4)             // �������͂̂x����]
#define DIRECTINPUT_TYPE_RZ         (5)             // �������͂̂y����]
#define DIRECTINPUT_TYPE_POV        (6)             // �����R���g���[��
#define DIRECTINPUT_TYPE_BUTTON     (7)             // �{�^��
#define DIRECTINPUT_TYPE_KEY        (8)             // �L�[�{�[�h�̃L�[



// �Q�[���ł̓��͂ƃL�[��p�b�h�Ȃǂ̓��͂Ƃ̑Ή����
struct KeyConfig::KEYCONFIGINFO
{
    int             PadNo;              // �p�b�h�ԍ�
    int             DirectInputType;    // DirectInput �̓��͏��^�C�v( DIRECTINPUT_TYPE_X �Ȃ� )
    int             SubInfo[2];       // �T�u���( DirectInputType �ɂ���ĈӖ����ς�� )
};

// ���͏����p�̏��
struct KEYCONFIGSYSTEMDATA
{
    KeyConfig::KEYCONFIGINFO   KeyConfigInfo[KEYCONFIG_INPUT_NUM];           // �Q�[�����̓��͂ƃL�[��p�b�h�Ȃǂ̓��͂Ƃ̑Ή����
    DINPUT_JOYSTATE NeutralDirectInputState[MAX_GAMEPAD_NUM];     // DirectInput �̃p�b�h�̏������͏��
    DINPUT_JOYSTATE DirectInputState[MAX_GAMEPAD_NUM];            // DirectInput �̃p�b�h�̓��͏��
    char            NeutralKeyInput[KEY_STATE_BUFFER_SIZE];       // �L�[�̏������͏��
    char            KeyInput[KEY_STATE_BUFFER_SIZE];              // �L�[�̓��͏��
    int             ButtonInput;                                    // �{�^���̓��͏��
    int             ButtonEdgeInput;                                // �{�^���̉����ꂽ�u�Ԃ݂̂̓��͏��
    VECTOR          CameraStickInput;                               // �J��������p�̓��͏��
};

// ���͏����p�̏��
static KEYCONFIGSYSTEMDATA g_KeyConfSys;

// �Q�[���ł̊e���͂ƃL�[��p�b�h�Ȃǂ̓��͂Ƃ̃f�t�H���g�̑Ή��ݒ�
static  KeyConfig::KEYCONFIGINFO g_DefaultInputTypeInfo[KEYCONFIG_INPUT_NUM] =
{
    0, DIRECTINPUT_TYPE_X,      -1, 0,      // KEYCONFIG_INPUT_LEFT
    0, DIRECTINPUT_TYPE_X,       1, 0,      // KEYCONFIG_INPUT_RIGHT
    0, DIRECTINPUT_TYPE_Y,      -1, 0,      // KEYCONFIG_INPUT_UP 
    0, DIRECTINPUT_TYPE_Y,       1, 0,      // KEYCONFIG_INPUT_DOWN 
    0, DIRECTINPUT_TYPE_RX,     -1, 0,      // KEYCONFIG_INPUT_CAMERA_LEFT
    0, DIRECTINPUT_TYPE_RX,      1, 0,      // KEYCONFIG_INPUT_CAMERA_RIGHT
    0, DIRECTINPUT_TYPE_RY,     -1, 0,      // KEYCONFIG_INPUT_CAMERA_UP
    0, DIRECTINPUT_TYPE_RY,      1, 0,      // KEYCONFIG_INPUT_CAMERA_DOWN
    0, DIRECTINPUT_TYPE_BUTTON,  0, 0,      // KEYCONFIG_INPUT_ATTACK
    0, DIRECTINPUT_TYPE_BUTTON,  2, 0,      // KEYCONFIG_INPUT_JUMP
    0, DIRECTINPUT_TYPE_BUTTON,  3, 0,      // KEYCONFIG_INPUT_TEST
};

// �p�b�h�̎��ʎq�e�[�u��
static int g_PadIDTable[MAX_GAMEPAD_NUM] =
{
    DX_INPUT_PAD1,
    DX_INPUT_PAD2,
    DX_INPUT_PAD3,
    DX_INPUT_PAD4,
    DX_INPUT_PAD5,
    DX_INPUT_PAD6,
    DX_INPUT_PAD7,
    DX_INPUT_PAD8,
    DX_INPUT_PAD9,
    DX_INPUT_PAD10,
    DX_INPUT_PAD11,
    DX_INPUT_PAD12,
    DX_INPUT_PAD13,
    DX_INPUT_PAD14,
    DX_INPUT_PAD15,
    DX_INPUT_PAD16,
};



KeyConfig::KeyConfig() {
   
}

// �L�[�R���t�B�O�̏��������s��
void KeyConfig::Initialize(void)
{
    

    
     GetJoypadDirectInputState(g_PadIDTable[0], &g_KeyConfSys.NeutralDirectInputState[0]);
}

// KeyConfig_InputProcess �p�̎����̓^�C�v�̏������s���⏕�֐�
static void KeyConfig_InputProcess_Assist(
    // �������ʂ�������ϐ��̃A�h���X
    int* InputState,

    // �����̓^�C�v�̃T�u���
    //    (  1:InputValue ���v���X�̒l�̏ꍇ�ɓ��͂���Ƃ���
    //      -1:InputValue ���}�C�i�X�̒l�̏ꍇ�ɓ��͂���Ƃ��� )
    int SubInfo,

    // �����͂̒l
    int InputValue
)
{
    // �T�u��� 1 �� -1 ���ŏ����𕪊�
    switch (SubInfo)
    {
    case 1:     // 1�̏ꍇ�� InputValue ���v���X�̏ꍇ�̂ݓ��͂���Ƃ���
        if (InputValue > 0)
        {
            *InputState = InputValue;
        }
        break;

    case -1:    // -1�̏ꍇ�� InputValue ���v���X�̏ꍇ�̂ݓ��͂���Ƃ���
        if (InputValue < 0)
        {
            *InputState = -InputValue;
        }
        break;
    }
}

// �L�[�R���t�B�O�̓��͏������s��( ���t���[�����s���� )
void KeyConfig::InputProcess(void)
{
    int              i;
    KEYCONFIGINFO* KCInfo;
    int              InputState[KEYCONFIG_INPUT_NUM];
    int              PadNum;
    DINPUT_JOYSTATE* DIJState;
    int              ButtonPrevInput;
    int              Total;

    // �p�b�h�̐����擾����
    PadNum = GetJoypadNum();

    // �p�b�h�̐����v���O�������Ή����Ă��鐔��葽���ꍇ�́A�Ή����Ă��鐔�ɐ�������
    if (PadNum > MAX_GAMEPAD_NUM)
    {
        PadNum = MAX_GAMEPAD_NUM;
    }

    // �p�b�h�̓��͏��� DirectInput ����擾����
    for (i = 0; i < PadNum; i++)
    {
        GetJoypadDirectInputState(g_PadIDTable[i], &g_KeyConfSys.DirectInputState[i]);
    }

    

    // �Q�[���Ŏg�p������͏����\�z����
    KCInfo = g_KeyConfSys.KeyConfigInfo;
    for (i = 0; i < KEYCONFIG_INPUT_NUM; i++, KCInfo++)
    {
        // �w���͂Ȃ��x��Ԃɂ��Ă���
        InputState[i] = 0;

        // �Ή����� DirectInput �̏��^�C�v�ɂ���ď����𕪊�
        DIJState = KCInfo->PadNo < 0 ? NULL : &g_KeyConfSys.DirectInputState[KCInfo->PadNo];
        switch (KCInfo->DirectInputType)
        {
        case DIRECTINPUT_TYPE_X:    // �������͂̂w���̏ꍇ
            KeyConfig_InputProcess_Assist(&InputState[i], KCInfo->SubInfo[0], DIJState->X);
            break;

        case DIRECTINPUT_TYPE_Y:    // �������͂̂x���̏ꍇ
            KeyConfig_InputProcess_Assist(&InputState[i], KCInfo->SubInfo[0], DIJState->Y);
            break;

        case DIRECTINPUT_TYPE_Z:    // �������͂̂y���̏ꍇ
            KeyConfig_InputProcess_Assist(&InputState[i], KCInfo->SubInfo[0], DIJState->Z);
            break;

        case DIRECTINPUT_TYPE_RX:   // �������͂̂w����]�̏ꍇ
            KeyConfig_InputProcess_Assist(&InputState[i], KCInfo->SubInfo[0], DIJState->Rx);
            break;

        case DIRECTINPUT_TYPE_RY:   // �������͂̂x����]�̏ꍇ
            KeyConfig_InputProcess_Assist(&InputState[i], KCInfo->SubInfo[0], DIJState->Ry);
            break;

        case DIRECTINPUT_TYPE_RZ:   // �������͂̂y����]�̏ꍇ
            KeyConfig_InputProcess_Assist(&InputState[i], KCInfo->SubInfo[0], DIJState->Rz);
            break;

        case DIRECTINPUT_TYPE_POV:  // �����R���g���[���̏ꍇ
            // �ݒ肳��Ă�������ɓ��͂���Ă�����w���͂���x�ɂ���
            if (DIJState->POV[KCInfo->SubInfo[0]] == KCInfo->SubInfo[1])
            {
                InputState[i] = DIRECTINPUT_MAX_VALUE;
            }
            break;

        case DIRECTINPUT_TYPE_BUTTON:   // �{�^���̏ꍇ
            // �ݒ肳��Ă���{�^����������Ă�����w���͂���x�ɂ���
            if (DIJState->Buttons[KCInfo->SubInfo[0]] == 128)
            {
                InputState[i] = DIRECTINPUT_MAX_VALUE;
            }
            break;

        case DIRECTINPUT_TYPE_KEY:  // �L�[�{�[�h�̃L�[�̏ꍇ
            // �ݒ肳��Ă���L�[��������Ă�����w���͂���x�ɂ���
            if (g_KeyConfSys.KeyInput[KCInfo->SubInfo[0]])
            {
                InputState[i] = DIRECTINPUT_MAX_VALUE;
            }
            break;
        }
    }

    // �P�t���[���O�̓��͏�Ԃ��Ƃ��Ă���
    ButtonPrevInput = g_KeyConfSys.ButtonInput;

    // ���͏�Ԃ̏�����
    g_KeyConfSys.ButtonInput = 0;

    // �e���͂ɑΉ�����r�b�g���w���͂���x�̏ꍇ�͗��Ă�
    for (i = 0; i < KEYCONFIG_INPUT_NUM; i++)
    {
        if (InputState[i] > 0)
        {
            g_KeyConfSys.ButtonInput |= 1 << i;
        }
    }

    // ����̃t���[���Łw���͂���x�ɂȂ�n�߂��r�b�g���Z�o����
    g_KeyConfSys.ButtonEdgeInput = g_KeyConfSys.ButtonInput & ~ButtonPrevInput;

    // �J��������p�̓��͏�Ԃ��Z�o����
    Total = InputState[KEYCONFIG_INPUT_CAMERA_RIGHT] - InputState[KEYCONFIG_INPUT_CAMERA_LEFT];
    g_KeyConfSys.CameraStickInput.x = Total / (float)DIRECTINPUT_MAX_VALUE;

    Total = InputState[KEYCONFIG_INPUT_CAMERA_DOWN] - InputState[KEYCONFIG_INPUT_CAMERA_UP];
    g_KeyConfSys.CameraStickInput.y = Total / (float)DIRECTINPUT_MAX_VALUE;

    g_KeyConfSys.CameraStickInput.z = 0.0f;
}

// �{�^���̓��͏�Ԃ��擾����( �߂�l : �{�^���̓��͏�� )
int KeyConfig::GetInput(void)
{
    return g_KeyConfSys.ButtonInput;
}

// �{�^���̉����ꂽ�u�Ԃ݂̂̓��͏�Ԃ��擾����( �߂�l : �{�^���̉����ꂽ�u�Ԃ݂̂̓��͏�� )
int KeyConfig::GetEdgeInput(void)
{
    return g_KeyConfSys.ButtonEdgeInput;
}

// �J��������p�̓��͏�Ԃ��擾����( �߂�l : �J��������p�̓��͏�� )
VECTOR KeyConfig::GetCameraInput(void)
{
    return g_KeyConfSys.CameraStickInput;
}

// �L�[�R���t�B�O�ݒ���t�@�C���ɕۑ�����( �߂�l : �ۑ������FTRUE   �ۑ����s�FFALSE )
int KeyConfig::Save(const char* FilePath)
{
    FILE* fp;
    KEYCONFIGINFO* KCInfo;
    int            i;

    // �Ή�����ۑ�����t�@�C�����J��
    fp = fopen(FilePath, "wt");
    if (fp == NULL)
    {
        // �J���Ȃ������牽�������ɏI��
        return FALSE;
    }

    // �Q�[���̊e���͂ƃL�[��p�b�h�Ȃǂ̓��͂Ƃ̑Ή������t�@�C���ɏ����o��
    KCInfo = g_KeyConfSys.KeyConfigInfo;
    for (i = 0; i < KEYCONFIG_INPUT_NUM; i++, KCInfo++)
    {
        fprintf(fp, "PadNo = %d  DirectInputType = %d  SubInfo0 = %d  SubInfo1 = %d \n",
            KCInfo->PadNo,
            KCInfo->DirectInputType,
            KCInfo->SubInfo[0],
            KCInfo->SubInfo[1]
        );
    }

    // �t�@�C�������
    fclose(fp);

    // �����I��
    return TRUE;
}

// �L�[�R���t�B�O�ݒ���t�@�C������ǂݍ���( �߂�l : �ǂݍ��ݐ����FTRUE   �ǂݍ��ݎ��s�FFALSE )
int KeyConfig::Load(const char* FilePath)
{
    FILE* fp;
    KEYCONFIGINFO* KCInfo;
    int            i;

    // �Ή�����ۑ������t�@�C�����J��
    fp = fopen(FilePath, "rt");
    if (fp == NULL)
    {
        // �J���Ȃ������ꍇ�͉��������ɏI��
        return FALSE;
    }

    // �Q�[���̊e���͂ƃL�[��p�b�h�Ȃǂ̓��͂Ƃ̑Ή������t�@�C������ǂݍ���
    KCInfo = g_KeyConfSys.KeyConfigInfo;
    for (i = 0; i < KEYCONFIG_INPUT_NUM; i++, KCInfo++)
    {
        fscanf_s(fp, "PadNo = %d  DirectInputType = %d  SubInfo0 = %d  SubInfo1 = %d \n",
            &KCInfo->PadNo,
            &KCInfo->DirectInputType,
            &KCInfo->SubInfo[0],
            &KCInfo->SubInfo[1]
        );
    }

    // �t�@�C�������
    fclose(fp);

    // �����I��
    return TRUE;
}

// �L�[�R���t�B�O�ݒ���f�t�H���g�ɂ���
void  KeyConfig::SetDefault(void)
{
    int i;

    // �f�t�H���g�ݒ�̏����R�s�[����
    for (i = 0; i < KEYCONFIG_INPUT_NUM; i++)
    {
        g_KeyConfSys.KeyConfigInfo[i] = g_DefaultInputTypeInfo[i];
    }
}

// UpdateInputTypeInfo �p�̎����̓^�C�v�̏������s���⏕�֐�
static void UpdateInputTypeInfo_Assist(
    KeyConfig::KEYCONFIGINFO* KCInfo,                  // �L�[��p�b�h�Ȃǂ̓��͏��
    int* ValidMaxDInput,          // MaxInput �ɗL���Ȓl�������Ă��邩�ǂ�����ۑ����Ă���ϐ��̃A�h���X
    int* MaxDInput,               // �L���ȓ��͒l�̍ő�l��ۑ����Ă���ϐ��̃A�h���X
    int            PadNo,                   // �p�b�h�ԍ�
    int            DirectInputType,         // DirectInput �̓��͏��^�C�v
    int            DirectInputValue,        // DirectInput �̓��͒l
    int            NeutralDirectInputValue  // ������Ԃ� DirectInput �̓��͒l
)
{
    // ������Ԃƒl�������ꍇ�͉������Ȃ�
    if (DirectInputValue == NeutralDirectInputValue)
    {
        return;
    }

    // DirectInput �̓��͒l���}�C�i�X���v���X���ŏ����𕪊�
    if (DirectInputValue < 0)
    {
        // MaxDirectInputValue �ɂ܂��L���Ȓl�������Ă��Ȃ���
        // ���� MaxDirectInputValue �̒l���� DirectInputValue �̒l���傫�������`�F�b�N
        if (*ValidMaxDInput == FALSE || *MaxDInput < -DirectInputValue)
        {
            // ����ۑ�����
            KCInfo->PadNo = PadNo;
            KCInfo->DirectInputType = DirectInputType;
            KCInfo->SubInfo[0] = -1;
            KCInfo->SubInfo[1] = 0;

            *ValidMaxDInput = TRUE;
            *MaxDInput = -DirectInputValue;
        }
    }
    else
        if (DirectInputValue > 0)
        {
            // MaxDirectInputValue �ɂ܂��L���Ȓl�������Ă��Ȃ���
            // ���� MaxDirectInputValue �̒l���� DirectInputValue �̒l���傫�������`�F�b�N
            if (*ValidMaxDInput == FALSE || *MaxDInput < DirectInputValue)
            {
                // ����ۑ�����
                KCInfo->PadNo = PadNo;
                KCInfo->DirectInputType = DirectInputType;
                KCInfo->SubInfo[0] = 1;
                KCInfo->SubInfo[1] = 0;

                *ValidMaxDInput = TRUE;
                *MaxDInput = DirectInputValue;
            }
        }
}

// ���݉�������Ă���L�[��p�b�h�̓��͏����`�F�b�N���āA���͂��������ꍇ�͏��X�V����( �L�[�R���t�B�O��ʗp )
//     �߂�l : ���͂����������ǂ���( TRUE:���͂�������  FALSE:���͖͂������� )
int KeyConfig::UpdateInputTypeInfo(int UpdateInputType)
{
    int              i;
    int              j;
    int              ValidMaxDInput;
    int              MaxDInput;
    int              PadNum;
    DINPUT_JOYSTATE* DIJState;
    DINPUT_JOYSTATE* NDIJState;
    KEYCONFIGINFO* KCInfo = &g_KeyConfSys.KeyConfigInfo[UpdateInputType];
    int              Result;

    // �߂�l�́w���͂����������x�ɂ��Ă���
    Result = FALSE;

    // �ڑ�����Ă���p�b�h�̐����擾����
    PadNum = GetJoypadNum();

    // �p�b�h�̐����v���O�������Ή����Ă��鐔��葽���ꍇ�́A�Ή����Ă��鐔�ɐ�������
    if (PadNum > MAX_GAMEPAD_NUM)
    {
        PadNum = MAX_GAMEPAD_NUM;
    }

    // �wMaxDInput �ɗL���Ȓl�������Ă��邩�ǂ����x�̃t���O��|���A
    // MaxDInput �̒l�����������Ă���
    ValidMaxDInput = FALSE;
    MaxDInput = 0;

    // �S�Ẵp�b�h�̓��͏�Ԃ��`�F�b�N
    DIJState = g_KeyConfSys.DirectInputState;
    NDIJState = g_KeyConfSys.NeutralDirectInputState;
    for (i = 0; i < PadNum; i++, DIJState++, NDIJState++)
    {
        // �������͏�Ԃ��`�F�b�N
        UpdateInputTypeInfo_Assist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_X, DIJState->X, NDIJState->X);
        UpdateInputTypeInfo_Assist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_Y, DIJState->Y, NDIJState->Y);
        UpdateInputTypeInfo_Assist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_Z, DIJState->Z, NDIJState->Z);
        UpdateInputTypeInfo_Assist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_RX, DIJState->Rx, NDIJState->Rx);
        UpdateInputTypeInfo_Assist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_RY, DIJState->Ry, NDIJState->Ry);
        UpdateInputTypeInfo_Assist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_RZ, DIJState->Rz, NDIJState->Rz);

        // �����R���g���[���̓��͏�Ԃ��`�F�b�N
        for (j = 0; j < 4; j++)
        {
            // POV ���L���Ȓl( -1 �ȊO�̒l )�ŁA��������ԂƈقȂ邩���`�F�b�N
            if (DIJState->POV[j] != -1 &&
                DIJState->POV[j] != NDIJState->POV[j])
            {
                // ����ۑ�����
                KCInfo->PadNo = i;
                KCInfo->DirectInputType = DIRECTINPUT_TYPE_POV;
                KCInfo->SubInfo[0] = j;
                KCInfo->SubInfo[1] = DIJState->POV[j];

                // �߂�l���w���͂��������x�ɂ���
                Result = TRUE;
            }
        }

        // �{�^���̓��͏�Ԃ��`�F�b�N
        for (j = 0; j < 32; j++)
        {
            // �{�^����������Ă��āA��������ԂƈقȂ邩���`�F�b�N
            if (DIJState->Buttons[j] == 128 &&
                DIJState->Buttons[j] != NDIJState->Buttons[j])
            {
                // ����ۑ�����
                KCInfo->PadNo = i;
                KCInfo->DirectInputType = DIRECTINPUT_TYPE_BUTTON;
                KCInfo->SubInfo[0] = j;
                KCInfo->SubInfo[1] = 0;

                // �߂�l���w���͂��������x�ɂ���
                Result = TRUE;
            }
        }
    }

    // ValidMaxDirectInputValue �� true �̏ꍇ�́A�L���ȓ��͂��������Ƃ������ƂȂ̂Ŗ߂�l���w���͂��������x�ɂ���
    if (ValidMaxDInput)
    {
        Result = TRUE;
    }

    

    // ���͂����������ǂ�����Ԃ�
    return Result;
}

// �p�b�h���L�[�̓��͂����邩�ǂ������擾����( �L�[�R���t�B�O��ʗp )
//     �߂�l : ���͂����������ǂ���( TRUE:���͂�������  FALSE:���͖͂������� )
int KeyConfig::CheckInput(void)
{
    int              i;
    int              PadNum;

    // �ڑ�����Ă���p�b�h�̐����擾����
    PadNum = GetJoypadNum();

    // �p�b�h�̐����v���O�������Ή����Ă��鐔��葽���ꍇ�́A�Ή����Ă��鐔�ɐ�������
    if (PadNum > MAX_GAMEPAD_NUM)
    {
        PadNum = MAX_GAMEPAD_NUM;
    }

    // �S�Ẵp�b�h�̓��͏�Ԃ��`�F�b�N
    for (i = 0; i < PadNum; i++)
    {
        // ������ԂƏ�񂪈قȂ�ꍇ�͉���������͂�����Ƃ������ƂȂ̂ŁATRUE ��Ԃ�
        if (memcmp(&g_KeyConfSys.DirectInputState[i],
            &g_KeyConfSys.NeutralDirectInputState[i], sizeof(DINPUT_JOYSTATE)) != 0)
        {
            return TRUE;
        }
    }

   

    // �����ɗ����Ƃ������Ƃ͉������͂����������Ƃ������ƂȂ̂� FALSE ��Ԃ�
    return FALSE;
}

// �w��̓��͏��^�C�v�Ɋ��蓖�Ă��Ă���p�b�h��L�[�̓��̖͂��O���擾����( �L�[�R���t�B�O��ʗp )
void KeyConfig::GetInputTypeString(int InputType, char* InputString)
{
    KEYCONFIGINFO* KCInfo = &g_KeyConfSys.KeyConfigInfo[InputType];

    char           String[256];

   
        // �p�b�h�̓��͖��͐擪�Ƀp�b�h�̔ԍ���t����
        sprintf(String, "Pad No.%d", KCInfo->PadNo);

        // �Ή����Ă���p�b�h�� DirectInput �̏��^�C�v�ɂ���ĕ���
        switch (KCInfo->DirectInputType)
        {
        case DIRECTINPUT_TYPE_X:        // X�����͂̏ꍇ�̓v���X�̏ꍇ�� RIGHT�A�}�C�i�X�̏ꍇ�� LEFT ��t����
            sprintf(InputString, "%s %s", String, KCInfo->SubInfo[0] > 0 ? "RIGHT" : "LEFT");
            break;

        case DIRECTINPUT_TYPE_Y:        // Y�����͂̏ꍇ�̓v���X�̏ꍇ�� DOWN�A�}�C�i�X�̏ꍇ�� UP ��t����
            sprintf(InputString, "%s %s", String, KCInfo->SubInfo[0] > 0 ? "DOWN" : "UP");
            break;

        case DIRECTINPUT_TYPE_Z:        // Z�����͂̏ꍇ�̓v���X�̏ꍇ�� +�A�}�C�i�X�̏ꍇ�� - ��t����
            sprintf(InputString, "%s %sZ", String, KCInfo->SubInfo[0] > 0 ? "+" : "-");
            break;

        case DIRECTINPUT_TYPE_RX:       // X����]���͂̏ꍇ�̓v���X�̏ꍇ�� +�A�}�C�i�X�̏ꍇ�� - ��t����
            sprintf(InputString, "%s %sRx", String, KCInfo->SubInfo[0] > 0 ? "+" : "-");
            break;

        case DIRECTINPUT_TYPE_RY:       // Y����]���͂̏ꍇ�̓v���X�̏ꍇ�� +�A�}�C�i�X�̏ꍇ�� - ��t����
            sprintf(InputString, "%s %sRy", String, KCInfo->SubInfo[0] > 0 ? "+" : "-");
            break;

        case DIRECTINPUT_TYPE_RZ:       // Z����]���͂̏ꍇ�̓v���X�̏ꍇ�� +�A�}�C�i�X�̏ꍇ�� - ��t����
            sprintf(InputString, "%s %sRz", String, KCInfo->SubInfo[0] > 0 ? "+" : "-");
            break;

        case DIRECTINPUT_TYPE_POV:      // �����R���g���[�����͂̏ꍇ�� POV �ł��邱�ƂƁAPOV�̏��ԍ��Ɠ��͊p�x��t����
            sprintf(InputString, "%s POV %d Angle %d��", String, KCInfo->SubInfo[0], KCInfo->SubInfo[1] / 100);
            break;

        case DIRECTINPUT_TYPE_BUTTON:   // �{�^�����͂̏ꍇ�� BUTTON �ƃ{�^���ԍ���t����
            sprintf(InputString, "%s BUTTON %d", String, KCInfo->SubInfo[0]);
            break;
        }
    
}

