#include "ActiveMath.h"

//●グローバル変数
int FPS = 60;
int WindowWidth = 1000, WindowHeight = 750, ColorBitNum = 32;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//［起動に伴う処理］　
	//●DXライブラリの設定
	SetWaitVSyncFlag(FALSE);//垂直同期信号をオフ
	ChangeWindowMode(true); //ウィンドウモードの切り替え
	if (DxLib_Init() == -1) return -1; //DXライブラリ初期化
	if (ActiveMath_Init() == -1) return -1; //ActiveMathの初期化処理
	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定
	SetGraphMode(WindowWidth, WindowHeight, ColorBitNum); //ウインドウサイズの指定

	//●背景の指定
	int BackImg = LoadGraph(".\\File\\BackImg.jpg"); //背景のロード

	//●メッセージのロード
	const int MsgCharMax = 2000;//読み込み可能な文字数
	char Msg[MsgCharMax + 1] = { 0 };//メッセージ
	LoadMsg(".\\File\\Msg\\Msg01.acm", Msg, MsgCharMax + 1, 1);

	//●メッセージ関連ファイルのロード（メッセージボックスフォーム，メッセージボックス，設定（フォント，フォント画像，タグ設定））
	static struct MsgBoxForm MsgBoxForm; //メッセージボックスフォーム
	static struct MsgBoxCtrl MsgBox; //メッセージボックス
	LoadMsgSet(LocalDir, &MsgBoxForm, 1, &MsgBox, 1, 1, 1);//メッセージボックスフォームの個数１//メッセージボックスの個数１//フォント・タグをロードする（０以外）//ジョイパッドの割り当てをロードする（０以外）
	MsgBox.Location[0] = (WindowWidth - MsgBox.OuterWidth) / 2;
	MsgBox.Location[1] = (WindowHeight - MsgBox.OuterHeight) / 2;

	//［メインループ］
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !MathgpUpdateJoypad()) {

		//●早すぎたら待機
		SleepToFitFPS(FPS);
		//●背景
		DrawGraph(0, 0, BackImg, TRUE);
		//●メッセージボックス
		if (ShowMsgBox(Msg, &MsgBox) == 6) break;//メッセージの表示とプログラムの終了
	}
	return 0;
}
//LoadMsg+LoadMsgSet