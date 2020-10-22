#include "ActiveMath.h"
//●グローバル変数
int FPS = 60;
int WindowWidth = 1000, WindowHeight = 750, ColorBitNum = 32;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//［起動に伴う処理］　
	//●DXライブラリの設定
	SetWaitVSyncFlag(FALSE);//垂直同期信号をオフ
	ChangeWindowMode(true); //ウィンドウモードの切り替え
	if (DxLib_Init() == -1) return -1; //DXライブラリ初期化処理
	if (ActiveMath_Init() == -1) return -1; //ActiveMathの初期化処理
	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定
	SetGraphMode(WindowWidth, WindowHeight, ColorBitNum); //ウインドウサイズの指定

	//●背景の指定
	int BackImg = LoadGraph(".\\File\\BackImg.jpg"); //背景のロード

	//●フォント関係の設定
	SetFontSize(24); //フォントサイズの指定
	ChangeFont("UD デジタル 教科書体 N-R"); //フォントの指定
	SetFontThickness(0);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);

	//［パッド関連の宣言と初期化］　
	//●パッドのロード
	//（パッドマネージャー）
	struct PadManager PadManager;//パッドマネージャー
	//（エリア（[0]インデックスエリア，[1]ボタンエリア，[2]ベースボタンエリアの計3つ））
	const int PadAreaMax = 3;//エリアの最大個数
	int PadAreaKosuu;//エリアの個数（ロード時に取得）
	struct AREACONTROL PadAreaSet[PadAreaMax] = { 0 };//エリア
	//（ボタンフォーム（最大10個））
	const int ButtonFormMax = 3;//ボタンフォームの最大個数
	int ButtonFormKosuu;//ボタンフォームの個数（ロード時に取得）
	struct BUTTONFORM ButtonFormSet[ButtonFormMax] = { 0 };//ボタンフォーム
	//（入力用インデックス）
	const int IndexMax = 6;//インデックスの最大個数
	int IndexKosuu;//インデックスの個数（ロード時に取得）
	struct BUTTONCONTROL IndexSet[IndexMax] = { 0 };//インデックス
	//（入力用ボタン）
	const int ButtonMax[IndexMax] = { 36, 36, 36, 18, 18, 18 };//各シートが持つボタンの最大個数
	int ButtonKosuu[IndexMax];//各シートが持つボタンの個数（ロード時に取得）
	static struct INPUTTEXTBUTTONCTRL Button0[36];//シート0が持つボタン
	static struct INPUTTEXTBUTTONCTRL Button1[36];//シート1が持つボタン
	static struct INPUTTEXTBUTTONCTRL Button2[36];//シート2が持つボタン
	static struct INPUTTEXTBUTTONCTRL Button3[18];//シート3が持つボタン
	static struct INPUTTEXTBUTTONCTRL Button4[18];//シート4が持つボタン
	static struct INPUTTEXTBUTTONCTRL Button5[18];//シート5が持つボタン
	static struct INPUTTEXTBUTTONCTRL* ButtonSet_hh[] = { Button0, Button1, Button2, Button3, Button4, Button5	};//各シートが持つボタン配列の先頭アドレス
	//（入力用ベースボタン）
	const int BaseButtonMax = 36;//ベースボタンの最大個数
	int BaseButtonKosuu;//ベースボタンの個数（ロード時に取得）
	struct INPUTTEXTBUTTONCTRL BaseButtonSet[BaseButtonMax] = { 0 };//ベースボタン
	//（パッドメッセージ）
	const int MsgCharMax_Pad = 500;//メッセージの最大文字数
	char Msg_Pad[MsgCharMax_Pad + 1];//メッセージ（配列サイズは，メッセージの最大文字数＋１）
	//（パッドメッセージボックスフォーム）
	const int MsgBoxFormKosuu_Pad = 1;//メッセージボックスフォームの個数（ロード前に指定）
	static struct MsgBoxForm MsgBoxForm_Pad;//メッセージメッセージボックスフォーム
	//（パッドメッセージボックス）
	const int MsgBoxKosuu_Pad = 1;//メッセージボックスの個数（ロード前に指定）
	static struct MsgBoxCtrl MsgBox_Pad;//メッセージボックス
	//（ロード）
	const char FilePath_Pad[MAX_PATH] = ".\\File\\Pad\\Pad01.acp";
	int Error = LoadPad(FilePath_Pad, PadAreaSet, &PadAreaKosuu, PadAreaMax, NULL,//親エリアなし（NULL）
		ButtonFormSet, &ButtonFormKosuu, ButtonFormMax,
		IndexSet, &IndexKosuu, IndexMax,
		ButtonSet_hh, ButtonKosuu, ButtonMax,
		BaseButtonSet, &BaseButtonKosuu, BaseButtonMax,
		Msg_Pad, MsgCharMax_Pad + 1, 0, &MsgBoxForm_Pad, MsgBoxFormKosuu_Pad, &MsgBox_Pad, MsgBoxKosuu_Pad, 1, 1//フォント・タグをロードする（０以外）//ジョイパッドの割り当てをロードする（０以外）
	);
	//（パッドメッセージボックスの位置指定）
	MsgBox_Pad.Location[0] = 100;
	MsgBox_Pad.Location[1] = 100;
	//（パッドパッドエリアのパラメータの位置指定）
	PadAreaSet[0].Location[0] += MsgBox_Pad.Location[0];//メッセージボックスと同じ位置を指定
	PadAreaSet[0].Location[1] += MsgBox_Pad.Location[1];//メッセージボックスの直下を指定

	//●メッセージ，メッセージボックスの初期化用コピーの取得
	struct MsgBoxCtrl MsgBox_Pad_Copy = MsgBox_Pad;//
	char Msg_Copy[MsgCharMax_Pad + 1];
	strcpy(Msg_Copy, Msg_Pad);

	//［メインループ］
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !MathgpUpdateJoypad()) {
		//●早すぎたら待機
		SleepToFitFPS(FPS);
		//●背景
		DrawGraph(0, 0, BackImg, TRUE);
		//●パッドの表示・メッセージボックスの表示・メッセージのジョイパッド操作
		int ShowMsgBoxFlag = 1;
		if (ShowPadJ(Msg_Pad, &MsgBox_Pad, MsgCharMax_Pad + 1, ShowMsgBoxFlag, IndexSet, IndexKosuu, ButtonSet_hh, ButtonKosuu, BaseButtonSet, BaseButtonKosuu, PadAreaSet, &PadManager) == 1) {//プッシュした長さが１のとき
			//●確定ボタン
			if (PadManager.PushedNo == 35 && PadAreaSet[2].Active == 1) {//ベースボタンの35番（確定ボタン）をクリックした。　ベースボタン：1000番代
				strcpy(Msg_Pad, Msg_Copy);//メッセージをクリア
				Reparse(&MsgBox_Pad);//タグの再読み込み指示（正解ボックスを表示させるため）
				MsgBox_Pad.Tag[0].PositionP = 0;//ActiveElementを0にリセットしてカーソル位置を再検出
			}
		}
		//●文末で確定
		if (MsgBox_Pad.Condition == 101) {
			MsgBox_Pad.Condition = 1;//毎回ここに入ってこないように１に戻す
			strcpy(Msg_Pad, Msg_Copy);//メッセージをクリア
			Reparse(&MsgBox_Pad);//タグの再読み込み指示（正解ボックスを表示させるため）
			MsgBox_Pad.Tag[0].PositionP = 0;//ActiveElementを0にリセットしてカーソル位置を再検出
		}
		//●終了
		static int TextColor = GetColor(0, 0, 0);
		DrawString(PadAreaSet[2].Location[0], PadAreaSet[2].Location[1] + PadAreaSet[2].Height, "ジョイパッドの[10]を押したら終了", TextColor); //文字列
		if (Joypad[10] == 1)  break;//Joypad[10]を押したら終了
	}
	return 0;
}
//LoadPad+ShowPadJ