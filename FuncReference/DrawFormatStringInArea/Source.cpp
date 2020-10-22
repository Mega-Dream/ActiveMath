#include "ActiveMath.h"
//●グローバル変数
int FPS = 60;
int WindowWidth = 1000, WindowHeight = 750, ColorBitNum = 32;
/////↓トップ画面↓////////////↓トップ画面↓////////////↓トップ画面↓////////////↓トップ画面↓//////
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//［起動に伴う処理］　
	//●DXライブラリの設定↓////
	SetWaitVSyncFlag(FALSE);//垂直同期信号をオフ
	ChangeWindowMode(true); //ウィンドウモードの切り替え
	if (DxLib_Init() == -1) return -1; //DXライブラリ初期化処理
	if (ActiveMath_Init() == -1) return -1; //ActiveMathの初期化処理
	SetDrawScreen(DX_SCREEN_BACK); // 描画先を裏画面に設定
	SetGraphMode(WindowWidth, WindowHeight, ColorBitNum); //ウインドウサイズの指定

	//●フォント関係の設定
	SetFontSize(24); //フォントサイズの指定
	ChangeFont("UD デジタル 教科書体 N-R"); //フォントの指定
	SetFontThickness(0);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);

	//●背景の指定
	int BackImg = LoadGraph(".\\File\\BGI_01.jpg"); //背景のロード
	//●ジョイパッドの設定
	LoadJoypadLink(".\\File\\JoypadLink.txt"); //ジョイパッドの設定のロード

	//■メッセージエリアの初期化
	static struct AREACONTROL MessageArea = { 0 };
	MessageArea.BackTransparency = 50;
	MessageArea.BackColor = GetColor(0, 0, 0);
	MessageArea.Width = 647;
	MessageArea.Height = 400;
	MessageArea.Location[0] = (WindowWidth - MessageArea.Width) / 2;
	MessageArea.Location[1] = (WindowHeight - MessageArea.Height) / 2;

	//［メインループ］
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !MathgpUpdateJoypad()) {
		//●早すぎたら待機
		SleepToFitFPS(FPS);
		//●背景
		DrawGraph(0,0, BackImg, TRUE);
		//●メッセージエリア
		ShowArea(&MessageArea,1);
		//●メッセージ
		static int TextColor = GetColor(255, 255, 255);
		DrawFormatStringInArea(0, 0, &MessageArea, TextColor, "DrawFormatStringInArea関数\n現在，%sのＨＰは%dです。", "ゆうしゃ", 273);
		//●終了
		if (Joypad[Action[Act_Confirm]] == 1) break;//Joypad[1]を押したら終了
	}
	return 0;
}
//DrawFormatStringInArea

