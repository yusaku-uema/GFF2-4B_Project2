#pragma once
#pragma warning(disable : 4996)
// キーコンフィグ処理のヘッダファイル

#ifndef KEYCONFIG_H
#define KEYCONFIG_H

#include "DxLib.h"

// 入力情報タイプ
#define KEYCONFIG_INPUT_LEFT            (0)         // 方向入力左
#define KEYCONFIG_INPUT_RIGHT           (1)         // 方向入力右
#define KEYCONFIG_INPUT_UP              (2)         // 方向入力上
#define KEYCONFIG_INPUT_DOWN            (3)         // 方向入力下
#define KEYCONFIG_INPUT_CAMERA_LEFT     (4)         // カメラ用方向入力左
#define KEYCONFIG_INPUT_CAMERA_RIGHT    (5)         // カメラ用方向入力右
#define KEYCONFIG_INPUT_CAMERA_UP       (6)         // カメラ用方向入力上
#define KEYCONFIG_INPUT_CAMERA_DOWN     (7)         // カメラ用方向入力下
#define KEYCONFIG_INPUT_ATTACK          (8)         // 攻撃ボタン
#define KEYCONFIG_INPUT_JUMP            (9)         // ジャンプボタン
#define KEYCONFIG_INPUT_TEST            (10)         // testボタン
#define KEYCONFIG_INPUT_NUM             (11)        // 入力タイプの数


class KeyConfig {
public:
	struct KEYCONFIGINFO;
	KeyConfig();
	void   Initialize(void);             // キーコンフィグの初期化を行う
	void   InputProcess(void);           // キーコンフィグの入力処理を行う( 毎フレーム実行する )
	int    GetInput(void);               // ボタンの入力状態を取得する( 戻り値 : ボタンの入力状態 )
	int    GetEdgeInput(void);           // ボタンの押された瞬間のみの入力状態を取得する( 戻り値 : ボタンの押された瞬間のみの入力状態 )
	VECTOR GetCameraInput(void);         // カメラ操作用の入力状態を取得する( 戻り値 : カメラ操作用の入力状態 )
	int    Save(const char* FilePath);   // キーコンフィグ設定をファイルに保存する( 戻り値 : 保存成功：TRUE   保存失敗：FALSE )
	int    Load(const char* FilePath);   // キーコンフィグ設定をファイルから読み込む( 戻り値 : 読み込み成功：TRUE   読み込み失敗：FALSE )
	void   SetDefault(void);             // キーコンフィグ設定をデフォルトにする
	// 現在押下されているキーやパッドの入力情報をチェックして、入力があった場合は情報更新する( キーコンフィグ画面用 )
//     戻り値 : 入力があったかどうか( TRUE:入力があった  FALSE:入力は無かった )
	int    UpdateInputTypeInfo(int UpdateInputType);

	// パッドかキーの入力があるかどうかを取得する( キーコンフィグ画面用 )
	//     戻り値 : 入力があったかどうか( TRUE:入力があった  FALSE:入力は無かった )
	int    CheckInput(void);

	// 指定の入力情報タイプに割り当てられているパッドやキーの入力の名前を取得する( キーコンフィグ画面用 )
	void   GetInputTypeString(int InputType, char* InputString);
};

#endif