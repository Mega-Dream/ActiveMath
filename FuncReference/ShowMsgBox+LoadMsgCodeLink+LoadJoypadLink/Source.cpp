#include "ActiveMath.h"

//●グローバル変数
int FPS = 60;//フレームレート
int WindowWidth = 1000, WindowHeight = 750, ColorBitNum = 32;//ウインドウサイズ

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//［起動に伴う処理］　
	//●DXライブラリの設定
	SetWaitVSyncFlag(FALSE); //垂直同期信号をオフ
	ChangeWindowMode(true); //ウィンドウモードの切り替え
	if (DxLib_Init() == -1) return -1; //DXライブラリ初期化
	if (ActiveMath_Init() == -1) return -1; //ActiveMathの初期化処理
	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定
	SetGraphMode(WindowWidth, WindowHeight, ColorBitNum); //ウインドウサイズの指定

	//●背景の指定
	int BackImg = LoadGraph(".\\File\\BackImg.jpg"); //背景のロード

	//●フォント・タグ，およびジョイパッドの設定
	LoadMsgCodeLink(".\\File\\MsgCodeLink.txt"); //フォント，フォント画像，タグの設定のロード
	LoadJoypadLink(".\\File\\JoypadLink.txt"); //ジョイパッドの設定のロード

	//●メッセージの指定
	const int MsgCharMax = 500;//読み込み可能な文字数
	char Msg[MsgCharMax + 1] = "<p>#SetColor(255,204,102)ShowMsgBox関数#UstColor{}</p><p>解の公式：<math>#frac(2a;－b±#sqrt(#sup(b;2)ー4ac))</math></p>\
<p>定積分の部分積分法：<math>#int(^∫^;a;b;#func(f;x)#func(^#diff(#SetFont(17)g#UstFont{};^′^)^;x);dx\
＝#primit(#func(f;x)#func(#SetFont(17)g#UstFont{};x);a;b)－#int(^∫^;a;b;#func(^#diff(f;^′^)^;x)#func(#SetFont(17)g#UstFont{};x);dx))</math></p>\
<p>画像（ae）：#img_ae{.\\img_01.png}</p>";
	static struct MsgBoxForm MsgBoxForm; //メッセージボックスフォーム
	static struct MsgBoxCtrl MsgBox; //メッセージボックス
	MsgBox.MsgBoxForm_p = &MsgBoxForm; //メッセージボックスフォームのポインター
	MsgBox.Location[0] = (WindowWidth - MsgBox.OuterWidth) / 2;
	MsgBox.Location[1] = (WindowHeight - MsgBox.OuterHeight) / 2;

	//［メインループ］
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !MathgpUpdateJoypad()) {
		//●早すぎたら待機
		SleepToFitFPS(FPS);
		//●背景
		DrawGraph(0,0, BackImg, TRUE);
		//●メッセージボックス
		ShowMsgBox(Msg, &MsgBox);
		//●終了
		if (Joypad[Action[Act_Confirm]] == 1) break;//Joypad[1]を押したら終了
	}
	return 0;
}
//ShowMsgBox+LoadMsgCodeLink+LoadJoypadLink
