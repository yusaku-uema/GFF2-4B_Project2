#include"KeyConfigScene.h"
#include"main.h"
#include"DxLib.h"

#define KEYCONFIG_FILE_NAME     "dat/KeyConfig.txt"     // キーコンフィグデータのファイル名
#define INFO_X                  (10)                // 情報の描画開始座標
#define INFO_Y                  (10)
#define INFO_SPACE              (24)                // 一行あたりに空けるスペース
#define INFO_NAME_X             (140)               // 入力名を描画するＸ座標

// キーコンフィグ対象の項目
int TargetIndex;

// キーコンフィグ各項目の名前
static const char* g_KeyConfigMenuTable[KEYCONFIG_INPUT_NUM] =
{
    "アイテム選択(左)",
    "アイテム選択(右)",
    "固定",
    "ツルハシ",
    "左移動",
    "右移動",
    "上移動",
    "下移動",
    "決定",
    "ジャンプ",
    "ブロック配置",
};

KeyConfigScene::KeyConfigScene() {

   // キーコンフィグファイルを読み込む
   if (keyconfig.Load(KEYCONFIG_FILE_NAME) == FALSE)
   {
       // コンフィグファイルが読み込めなかったらデフォルト設定にする
       keyconfig.SetDefault();
   }

    // 「何か入力があったら何もしない」フラグを倒す
    InputWait = FALSE;
}

void  KeyConfigScene::Update(){
        // キーコンフィグの入力処理を行う
        keyconfig.InputProcess();

        // 「何か入力があったら何もしない」フラグが立っている場合は処理を分岐
        if (InputWait == TRUE)
        {
            // 何も入力が無かったら「何か入力があったら何もしない」フラグを倒す
            if (keyconfig.CheckInput() == TRUE)
            {
                WaitTimer(250);
                InputWait = FALSE;
            }

        }
        else 
        {
            // キーやパッドの押下状態をチェックして、押下されていたらキーコンフィグ設定に反映させる
            if (keyconfig.UpdateInputTypeInfo(TargetIndex))
            {
                // 何かボタンが押されたら次の項目に移動する
                TargetIndex++;

                // 「何か入力があったら何もしない」フラグを立てる
                InputWait = TRUE;
            }
        }

        // 項目の数だけ繰り返し
        int DrawY = INFO_Y;
        for (int i = 0; i < KEYCONFIG_INPUT_NUM; i++)
        {
            int DrawColor;
            char InputString[256];

            // 変更対象の項目かどうかで描画色を変える
            DrawColor = TargetIndex == i ? GetColor(255, 0, 0) : GetColor(255, 255, 255);

            // 項目名の描画
            DrawString(INFO_X, DrawY, g_KeyConfigMenuTable[i],  DrawColor);

            // 入力に割り当てられている入力名を取得する
            keyconfig.GetInputTypeString(i, InputString);

            // 割り当てられている入力名を描画する
            DrawString(INFO_NAME_X, DrawY, InputString, DrawColor);

            // 項目の描画Y座標を１項目分下に移動する
            DrawY += INFO_SPACE;
        }
        // 全ての入力の設定が終わったらループを抜ける
        if (TargetIndex == KEYCONFIG_INPUT_NUM)
        {
            g_KeyCongifGameState=2;
        }

    if (g_KeyCongifGameState == 2) {
        // キーコンフィグ設定を保存する
        keyconfig.Save(KEYCONFIG_FILE_NAME);
        SetGameState(1);
    }

}

