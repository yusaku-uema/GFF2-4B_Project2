// キーコンフィグ処理のプログラム

#include "KeyConfig.h"
#include "DxLib.h"
#include <string.h>

#define MAX_GAMEPAD_NUM             (16)            // チェックするゲームパッドの数
#define KEY_STATE_BUFFER_SIZE       (256)           // キーボードの入力状態を取得するためのバッファのサイズ
#define DIRECTINPUT_MAX_VALUE       (1000)          // DirectInput から得られる値の最大値

// DirectInput の入力情報タイプ
#define DIRECTINPUT_TYPE_X          (0)             // 方向入力のＸ軸
#define DIRECTINPUT_TYPE_Y          (1)             // 方向入力のＹ軸
#define DIRECTINPUT_TYPE_Z          (2)             // 方向入力のＺ軸
#define DIRECTINPUT_TYPE_RX         (3)             // 方向入力のＸ軸回転
#define DIRECTINPUT_TYPE_RY         (4)             // 方向入力のＹ軸回転
#define DIRECTINPUT_TYPE_RZ         (5)             // 方向入力のＺ軸回転
#define DIRECTINPUT_TYPE_POV        (6)             // 方向コントローラ
#define DIRECTINPUT_TYPE_BUTTON     (7)             // ボタン
#define DIRECTINPUT_TYPE_KEY        (8)             // キーボードのキー



// ゲームでの入力とキーやパッドなどの入力との対応情報
struct KeyConfig::KEYCONFIGINFO
{
    int             PadNo;              // パッド番号
    int             DirectInputType;    // DirectInput の入力情報タイプ( DIRECTINPUT_TYPE_X など )
    int             SubInfo[2];       // サブ情報( DirectInputType によって意味が変わる )
};

// 入力処理用の情報
struct KEYCONFIGSYSTEMDATA
{
    KeyConfig::KEYCONFIGINFO   KeyConfigInfo[KEYCONFIG_INPUT_NUM];           // ゲーム中の入力とキーやパッドなどの入力との対応情報
    DINPUT_JOYSTATE NeutralDirectInputState[MAX_GAMEPAD_NUM];     // DirectInput のパッドの初期入力状態
    DINPUT_JOYSTATE DirectInputState[MAX_GAMEPAD_NUM];            // DirectInput のパッドの入力状態
    char            NeutralKeyInput[KEY_STATE_BUFFER_SIZE];       // キーの初期入力状態
    char            KeyInput[KEY_STATE_BUFFER_SIZE];              // キーの入力状態
    int             ButtonInput;                                    // ボタンの入力状態
    int             ButtonEdgeInput;                                // ボタンの押された瞬間のみの入力状態
    VECTOR          CameraStickInput;                               // カメラ操作用の入力状態
};

// 入力処理用の情報
static KEYCONFIGSYSTEMDATA g_KeyConfSys;

// ゲームでの各入力とキーやパッドなどの入力とのデフォルトの対応設定
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

// パッドの識別子テーブル
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

// キーコンフィグの初期化を行う
void KeyConfig::Initialize(void)
{
    

    
     GetJoypadDirectInputState(g_PadIDTable[0], &g_KeyConfSys.NeutralDirectInputState[0]);
}

// KeyConfig_InputProcess 用の軸入力タイプの処理を行う補助関数
static void KeyConfig_InputProcess_Assist(
    // 処理結果を代入する変数のアドレス
    int* InputState,

    // 軸入力タイプのサブ情報
    //    (  1:InputValue がプラスの値の場合に入力ありとする
    //      -1:InputValue がマイナスの値の場合に入力ありとする )
    int SubInfo,

    // 軸入力の値
    int InputValue
)
{
    // サブ情報が 1 か -1 かで処理を分岐
    switch (SubInfo)
    {
    case 1:     // 1の場合は InputValue がプラスの場合のみ入力ありとする
        if (InputValue > 0)
        {
            *InputState = InputValue;
        }
        break;

    case -1:    // -1の場合は InputValue がプラスの場合のみ入力ありとする
        if (InputValue < 0)
        {
            *InputState = -InputValue;
        }
        break;
    }
}

// キーコンフィグの入力処理を行う( 毎フレーム実行する )
void KeyConfig::InputProcess(void)
{
    int              i;
    KEYCONFIGINFO* KCInfo;
    int              InputState[KEYCONFIG_INPUT_NUM];
    int              PadNum;
    DINPUT_JOYSTATE* DIJState;
    int              ButtonPrevInput;
    int              Total;

    // パッドの数を取得する
    PadNum = GetJoypadNum();

    // パッドの数がプログラムが対応している数より多い場合は、対応している数に制限する
    if (PadNum > MAX_GAMEPAD_NUM)
    {
        PadNum = MAX_GAMEPAD_NUM;
    }

    // パッドの入力情報を DirectInput から取得する
    for (i = 0; i < PadNum; i++)
    {
        GetJoypadDirectInputState(g_PadIDTable[i], &g_KeyConfSys.DirectInputState[i]);
    }

    

    // ゲームで使用する入力情報を構築する
    KCInfo = g_KeyConfSys.KeyConfigInfo;
    for (i = 0; i < KEYCONFIG_INPUT_NUM; i++, KCInfo++)
    {
        // 『入力なし』状態にしておく
        InputState[i] = 0;

        // 対応する DirectInput の情報タイプによって処理を分岐
        DIJState = KCInfo->PadNo < 0 ? NULL : &g_KeyConfSys.DirectInputState[KCInfo->PadNo];
        switch (KCInfo->DirectInputType)
        {
        case DIRECTINPUT_TYPE_X:    // 方向入力のＸ軸の場合
            KeyConfig_InputProcess_Assist(&InputState[i], KCInfo->SubInfo[0], DIJState->X);
            break;

        case DIRECTINPUT_TYPE_Y:    // 方向入力のＹ軸の場合
            KeyConfig_InputProcess_Assist(&InputState[i], KCInfo->SubInfo[0], DIJState->Y);
            break;

        case DIRECTINPUT_TYPE_Z:    // 方向入力のＺ軸の場合
            KeyConfig_InputProcess_Assist(&InputState[i], KCInfo->SubInfo[0], DIJState->Z);
            break;

        case DIRECTINPUT_TYPE_RX:   // 方向入力のＸ軸回転の場合
            KeyConfig_InputProcess_Assist(&InputState[i], KCInfo->SubInfo[0], DIJState->Rx);
            break;

        case DIRECTINPUT_TYPE_RY:   // 方向入力のＹ軸回転の場合
            KeyConfig_InputProcess_Assist(&InputState[i], KCInfo->SubInfo[0], DIJState->Ry);
            break;

        case DIRECTINPUT_TYPE_RZ:   // 方向入力のＺ軸回転の場合
            KeyConfig_InputProcess_Assist(&InputState[i], KCInfo->SubInfo[0], DIJState->Rz);
            break;

        case DIRECTINPUT_TYPE_POV:  // 方向コントローラの場合
            // 設定されている方向に入力されていたら『入力あり』にする
            if (DIJState->POV[KCInfo->SubInfo[0]] == KCInfo->SubInfo[1])
            {
                InputState[i] = DIRECTINPUT_MAX_VALUE;
            }
            break;

        case DIRECTINPUT_TYPE_BUTTON:   // ボタンの場合
            // 設定されているボタンが押されていたら『入力あり』にする
            if (DIJState->Buttons[KCInfo->SubInfo[0]] == 128)
            {
                InputState[i] = DIRECTINPUT_MAX_VALUE;
            }
            break;

        case DIRECTINPUT_TYPE_KEY:  // キーボードのキーの場合
            // 設定されているキーが押されていたら『入力あり』にする
            if (g_KeyConfSys.KeyInput[KCInfo->SubInfo[0]])
            {
                InputState[i] = DIRECTINPUT_MAX_VALUE;
            }
            break;
        }
    }

    // １フレーム前の入力状態をとっておく
    ButtonPrevInput = g_KeyConfSys.ButtonInput;

    // 入力状態の初期化
    g_KeyConfSys.ButtonInput = 0;

    // 各入力に対応するビットを『入力あり』の場合は立てる
    for (i = 0; i < KEYCONFIG_INPUT_NUM; i++)
    {
        if (InputState[i] > 0)
        {
            g_KeyConfSys.ButtonInput |= 1 << i;
        }
    }

    // 今回のフレームで『入力あり』になり始めたビットを算出する
    g_KeyConfSys.ButtonEdgeInput = g_KeyConfSys.ButtonInput & ~ButtonPrevInput;

    // カメラ操作用の入力状態を算出する
    Total = InputState[KEYCONFIG_INPUT_CAMERA_RIGHT] - InputState[KEYCONFIG_INPUT_CAMERA_LEFT];
    g_KeyConfSys.CameraStickInput.x = Total / (float)DIRECTINPUT_MAX_VALUE;

    Total = InputState[KEYCONFIG_INPUT_CAMERA_DOWN] - InputState[KEYCONFIG_INPUT_CAMERA_UP];
    g_KeyConfSys.CameraStickInput.y = Total / (float)DIRECTINPUT_MAX_VALUE;

    g_KeyConfSys.CameraStickInput.z = 0.0f;
}

// ボタンの入力状態を取得する( 戻り値 : ボタンの入力状態 )
int KeyConfig::GetInput(void)
{
    return g_KeyConfSys.ButtonInput;
}

// ボタンの押された瞬間のみの入力状態を取得する( 戻り値 : ボタンの押された瞬間のみの入力状態 )
int KeyConfig::GetEdgeInput(void)
{
    return g_KeyConfSys.ButtonEdgeInput;
}

// カメラ操作用の入力状態を取得する( 戻り値 : カメラ操作用の入力状態 )
VECTOR KeyConfig::GetCameraInput(void)
{
    return g_KeyConfSys.CameraStickInput;
}

// キーコンフィグ設定をファイルに保存する( 戻り値 : 保存成功：TRUE   保存失敗：FALSE )
int KeyConfig::Save(const char* FilePath)
{
    FILE* fp;
    KEYCONFIGINFO* KCInfo;
    int            i;

    // 対応情報を保存するファイルを開く
    fp = fopen(FilePath, "wt");
    if (fp == NULL)
    {
        // 開けなかったら何もせずに終了
        return FALSE;
    }

    // ゲームの各入力とキーやパッドなどの入力との対応情報をファイルに書き出す
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

    // ファイルを閉じる
    fclose(fp);

    // 成功終了
    return TRUE;
}

// キーコンフィグ設定をファイルから読み込む( 戻り値 : 読み込み成功：TRUE   読み込み失敗：FALSE )
int KeyConfig::Load(const char* FilePath)
{
    FILE* fp;
    KEYCONFIGINFO* KCInfo;
    int            i;

    // 対応情報を保存したファイルを開く
    fp = fopen(FilePath, "rt");
    if (fp == NULL)
    {
        // 開けなかった場合は何もせずに終了
        return FALSE;
    }

    // ゲームの各入力とキーやパッドなどの入力との対応情報をファイルから読み込む
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

    // ファイルを閉じる
    fclose(fp);

    // 成功終了
    return TRUE;
}

// キーコンフィグ設定をデフォルトにする
void  KeyConfig::SetDefault(void)
{
    int i;

    // デフォルト設定の情報をコピーする
    for (i = 0; i < KEYCONFIG_INPUT_NUM; i++)
    {
        g_KeyConfSys.KeyConfigInfo[i] = g_DefaultInputTypeInfo[i];
    }
}

// UpdateInputTypeInfo 用の軸入力タイプの処理を行う補助関数
static void UpdateInputTypeInfo_Assist(
    KeyConfig::KEYCONFIGINFO* KCInfo,                  // キーやパッドなどの入力情報
    int* ValidMaxDInput,          // MaxInput に有効な値が入っているかどうかを保存している変数のアドレス
    int* MaxDInput,               // 有効な入力値の最大値を保存している変数のアドレス
    int            PadNo,                   // パッド番号
    int            DirectInputType,         // DirectInput の入力情報タイプ
    int            DirectInputValue,        // DirectInput の入力値
    int            NeutralDirectInputValue  // 初期状態の DirectInput の入力値
)
{
    // 初期状態と値が同じ場合は何もしない
    if (DirectInputValue == NeutralDirectInputValue)
    {
        return;
    }

    // DirectInput の入力値がマイナスかプラスかで処理を分岐
    if (DirectInputValue < 0)
    {
        // MaxDirectInputValue にまだ有効な値が入っていないか
        // 又は MaxDirectInputValue の値よりも DirectInputValue の値が大きいかをチェック
        if (*ValidMaxDInput == FALSE || *MaxDInput < -DirectInputValue)
        {
            // 情報を保存する
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
            // MaxDirectInputValue にまだ有効な値が入っていないか
            // 又は MaxDirectInputValue の値よりも DirectInputValue の値が大きいかをチェック
            if (*ValidMaxDInput == FALSE || *MaxDInput < DirectInputValue)
            {
                // 情報を保存する
                KCInfo->PadNo = PadNo;
                KCInfo->DirectInputType = DirectInputType;
                KCInfo->SubInfo[0] = 1;
                KCInfo->SubInfo[1] = 0;

                *ValidMaxDInput = TRUE;
                *MaxDInput = DirectInputValue;
            }
        }
}

// 現在押下されているキーやパッドの入力情報をチェックして、入力があった場合は情報更新する( キーコンフィグ画面用 )
//     戻り値 : 入力があったかどうか( TRUE:入力があった  FALSE:入力は無かった )
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

    // 戻り値は『入力が無かった』にしておく
    Result = FALSE;

    // 接続されているパッドの数を取得する
    PadNum = GetJoypadNum();

    // パッドの数がプログラムが対応している数より多い場合は、対応している数に制限する
    if (PadNum > MAX_GAMEPAD_NUM)
    {
        PadNum = MAX_GAMEPAD_NUM;
    }

    // 『MaxDInput に有効な値が入っているかどうか』のフラグを倒し、
    // MaxDInput の値も初期化しておく
    ValidMaxDInput = FALSE;
    MaxDInput = 0;

    // 全てのパッドの入力状態をチェック
    DIJState = g_KeyConfSys.DirectInputState;
    NDIJState = g_KeyConfSys.NeutralDirectInputState;
    for (i = 0; i < PadNum; i++, DIJState++, NDIJState++)
    {
        // 方向入力状態をチェック
        UpdateInputTypeInfo_Assist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_X, DIJState->X, NDIJState->X);
        UpdateInputTypeInfo_Assist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_Y, DIJState->Y, NDIJState->Y);
        UpdateInputTypeInfo_Assist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_Z, DIJState->Z, NDIJState->Z);
        UpdateInputTypeInfo_Assist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_RX, DIJState->Rx, NDIJState->Rx);
        UpdateInputTypeInfo_Assist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_RY, DIJState->Ry, NDIJState->Ry);
        UpdateInputTypeInfo_Assist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_RZ, DIJState->Rz, NDIJState->Rz);

        // 方向コントローラの入力状態をチェック
        for (j = 0; j < 4; j++)
        {
            // POV が有効な値( -1 以外の値 )で、且つ初期状態と異なるかをチェック
            if (DIJState->POV[j] != -1 &&
                DIJState->POV[j] != NDIJState->POV[j])
            {
                // 情報を保存する
                KCInfo->PadNo = i;
                KCInfo->DirectInputType = DIRECTINPUT_TYPE_POV;
                KCInfo->SubInfo[0] = j;
                KCInfo->SubInfo[1] = DIJState->POV[j];

                // 戻り値を『入力があった』にする
                Result = TRUE;
            }
        }

        // ボタンの入力状態をチェック
        for (j = 0; j < 32; j++)
        {
            // ボタンが押されていて、且つ初期状態と異なるかをチェック
            if (DIJState->Buttons[j] == 128 &&
                DIJState->Buttons[j] != NDIJState->Buttons[j])
            {
                // 情報を保存する
                KCInfo->PadNo = i;
                KCInfo->DirectInputType = DIRECTINPUT_TYPE_BUTTON;
                KCInfo->SubInfo[0] = j;
                KCInfo->SubInfo[1] = 0;

                // 戻り値を『入力があった』にする
                Result = TRUE;
            }
        }
    }

    // ValidMaxDirectInputValue が true の場合は、有効な入力があったということなので戻り値を『入力があった』にする
    if (ValidMaxDInput)
    {
        Result = TRUE;
    }

    

    // 入力があったかどうかを返す
    return Result;
}

// パッドかキーの入力があるかどうかを取得する( キーコンフィグ画面用 )
//     戻り値 : 入力があったかどうか( TRUE:入力があった  FALSE:入力は無かった )
int KeyConfig::CheckInput(void)
{
    int              i;
    int              PadNum;

    // 接続されているパッドの数を取得する
    PadNum = GetJoypadNum();

    // パッドの数がプログラムが対応している数より多い場合は、対応している数に制限する
    if (PadNum > MAX_GAMEPAD_NUM)
    {
        PadNum = MAX_GAMEPAD_NUM;
    }

    // 全てのパッドの入力状態をチェック
    for (i = 0; i < PadNum; i++)
    {
        // 初期状態と情報が異なる場合は何かしら入力があるということなので、TRUE を返す
        if (memcmp(&g_KeyConfSys.DirectInputState[i],
            &g_KeyConfSys.NeutralDirectInputState[i], sizeof(DINPUT_JOYSTATE)) != 0)
        {
            return TRUE;
        }
    }

   

    // ここに来たということは何も入力が無かったということなので FALSE を返す
    return FALSE;
}

// 指定の入力情報タイプに割り当てられているパッドやキーの入力の名前を取得する( キーコンフィグ画面用 )
void KeyConfig::GetInputTypeString(int InputType, char* InputString)
{
    KEYCONFIGINFO* KCInfo = &g_KeyConfSys.KeyConfigInfo[InputType];

    char           String[256];

   
        // パッドの入力名は先頭にパッドの番号を付ける
        sprintf(String, "Pad No.%d", KCInfo->PadNo);

        // 対応しているパッドの DirectInput の情報タイプによって分岐
        switch (KCInfo->DirectInputType)
        {
        case DIRECTINPUT_TYPE_X:        // X軸入力の場合はプラスの場合は RIGHT、マイナスの場合は LEFT を付ける
            sprintf(InputString, "%s %s", String, KCInfo->SubInfo[0] > 0 ? "RIGHT" : "LEFT");
            break;

        case DIRECTINPUT_TYPE_Y:        // Y軸入力の場合はプラスの場合は DOWN、マイナスの場合は UP を付ける
            sprintf(InputString, "%s %s", String, KCInfo->SubInfo[0] > 0 ? "DOWN" : "UP");
            break;

        case DIRECTINPUT_TYPE_Z:        // Z軸入力の場合はプラスの場合は +、マイナスの場合は - を付ける
            sprintf(InputString, "%s %sZ", String, KCInfo->SubInfo[0] > 0 ? "+" : "-");
            break;

        case DIRECTINPUT_TYPE_RX:       // X軸回転入力の場合はプラスの場合は +、マイナスの場合は - を付ける
            sprintf(InputString, "%s %sRx", String, KCInfo->SubInfo[0] > 0 ? "+" : "-");
            break;

        case DIRECTINPUT_TYPE_RY:       // Y軸回転入力の場合はプラスの場合は +、マイナスの場合は - を付ける
            sprintf(InputString, "%s %sRy", String, KCInfo->SubInfo[0] > 0 ? "+" : "-");
            break;

        case DIRECTINPUT_TYPE_RZ:       // Z軸回転入力の場合はプラスの場合は +、マイナスの場合は - を付ける
            sprintf(InputString, "%s %sRz", String, KCInfo->SubInfo[0] > 0 ? "+" : "-");
            break;

        case DIRECTINPUT_TYPE_POV:      // 方向コントローラ入力の場合は POV であることと、POVの情報番号と入力角度を付ける
            sprintf(InputString, "%s POV %d Angle %d°", String, KCInfo->SubInfo[0], KCInfo->SubInfo[1] / 100);
            break;

        case DIRECTINPUT_TYPE_BUTTON:   // ボタン入力の場合は BUTTON とボタン番号を付ける
            sprintf(InputString, "%s BUTTON %d", String, KCInfo->SubInfo[0]);
            break;
        }
    
}

