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

	//●背景の指定
	int BackImg = LoadGraph(".\\File\\BGI_01.jpg"); //背景のロード

	//●フォント・タグ，およびジョイパッドの設定
	LoadMsgCodeLink(".\\File\\MsgCodeLink.txt"); //フォント，フォント画像，タグの設定のロード
	LoadJoypadLink(".\\File\\JoypadLink.txt"); //ジョイパッドの設定のロード

	//［各エリア・ツールボタン類の初期化］　
	//■メッセージエリアの初期化
	static struct AREACONTROL MessageArea = { 0 };
	MessageArea.BackTransparency = 50;
	MessageArea.BackColor = GetColor(0, 0, 0);
	MessageArea.Width = 600;
	MessageArea.Height = 48;
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

		//●メッセージ，タグ
		const int TagHairetsuMax = 15; //読み込み可能なタグの個数
		static struct Tag Tag[TagHairetsuMax + 1];//プラス１はtag[0]の分
		static char ParsedMsg[300 + 1] = { 0 }; //タグを抜き取った文字列
		static int Msg_TextColorRGB[3] = { 255, 255, 255 }; //文字色
		static int Msg_TextColor = GetColor(Msg_TextColorRGB[0], Msg_TextColorRGB[1], Msg_TextColorRGB[2]); //文字色のハンドル
		if (int Value = DrawMsg(0, 0, "<p>#SetColor(255,204,102)DrawMsg関数#UstColor{}　分数：<math>#frac(2;1)</math></p>", Msg_TextColorRGB, Msg_TextColor, &MessageArea, TagHairetsuMax, Tag, ParsedMsg)) {
			if (Value == -1) {
				//エラー：－１：タグを抜き取った文字列がカラ  －１０１：タグの最大個数を超えている（直後のみ-101で，その後は-1（タグを抜き取った文字列がカラ）となる）
			}
			else {
				//成功時
			}
		}
		//●終了
		if (Joypad[Action[Act_Confirm]] == 1) break;//Joypad[1]を押したら終了
	}
	return 0;
}
//DrawMsg

