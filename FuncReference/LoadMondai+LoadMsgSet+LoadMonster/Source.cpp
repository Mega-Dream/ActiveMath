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

	//［問題関連の宣言と初期化］　
	//●問題のロード
	struct Kadai Mondai = { 0 };
	int SyoumonKosuu;
	LoadMondai(".\\File\\Mondai\\Mondai01.ack", &Mondai, &SyoumonKosuu, 1);
	//●メッセージ関連ファイルのロード（メッセージフォーム，メッセージボックス，設定（フォント，フォント画像，タグ設定））
	const int MsgBoxFormKosuu = 2;
	static struct MsgBoxForm MsgBoxForm[MsgBoxFormKosuu];
	const int MsgBoxKosuu = 4;
	static struct MsgBoxCtrl MsgBox[MsgBoxKosuu];
	LoadMsgSet(LocalDir, MsgBoxForm, MsgBoxFormKosuu, MsgBox, MsgBoxKosuu, 1, 1);//フォント・タグをロードする（０以外）//ジョイパッドの割り当てをロードする（０以外）
	for (int i = 0; i < MsgBoxKosuu; i++) MsgBox[i].Location[0] = 80;
	MsgBox[0].Location[1] = 200;
	MsgBox[2].Location[1] = 400;
	//●小問・小問正解コントロールの複製
	static struct MsgBoxCtrl MsgBox_Syoumon[SYOUMON_MAX];
	static struct MsgBoxCtrl MsgBox_SyoumonSeikai[SYOUMON_MAX];
	for (int Num = 0; Num < SyoumonKosuu; Num++) {
		MsgBox_Syoumon[Num] = MsgBox[2];
		MsgBox_SyoumonSeikai[Num] = MsgBox[3];
	}
	//●モンスターのロード
	const int MonsterMax = 500;
	struct Monster Monster[MonsterMax];
	int MonsterKosuu = 0;//モンスター数（実際の個数）
	char ColumnTitle[MONSTER_COLUMNMAX][MONSTER_COLUMNTITLEFIELDMAX + 1] = { 0 };
	int ColumnKosuu = 0;
	LoadMonster(".\\Monster\\Monster.csv", Monster, MonsterMax, &MonsterKosuu, NULL, ColumnTitle, &ColumnKosuu);
	//●モンスター番号の確定（該当がなければ0のまま）
	int MonsterNum = 0;//モンスターの要素番号
	for (int i = 0; i < MonsterKosuu; i++) {
		if (Mondai.monsterID == Monster[i].Column[0]) {
			MonsterNum = i; break;
		}
	}

	//［メインループ］
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !MathgpUpdateJoypad()) {
		//●早すぎたら待機
		SleepToFitFPS(FPS);
		//●背景
		DrawGraph(0,0, BackImg, TRUE);
		//●モンスター
		static int TextColor = GetColor(255, 255, 255); //文字色の指定
		DrawGraph(80, 50, Monster[MonsterNum].Img, TRUE);//モンスター画像
		DrawFormatString(700, 50, TextColor, "%s:%d", ColumnTitle[0], Mondai.monsterID);//モンスターID
		DrawFormatString(700, 80, TextColor, "名前:%s", Monster[MonsterNum].Name);//モンスター名

		for (int k = 1; k < ColumnKosuu; k++) {
			DrawFormatString(700, 80 + 30 * k, TextColor, "%s:%d", ColumnTitle[k], Monster[MonsterNum].Column[k]);//モンスターのカラム（モンスターID（0番）を除く）
		}
		//●問題
		//フラグ
		static int KakioeChecker = 0;//Condition（4：メッセージの最後まで書き出し済み）
		static int PushCounter = 0;//Enterキーを押した回数
		//（大問）
		KakioeChecker = ShowMsgBox(Mondai.daimon, &MsgBox[0]);//大問の書き出し
		//（大問正解）
		if (0 < PushCounter) {
			MsgBox[1].Location[0] = MsgBox[0].Location[0] + MsgBox[0].OuterWidth;//大問の右
			MsgBox[1].Location[1] = MsgBox[0].Location[1];//縦は大問と同じ
			ShowMsgBox(Mondai.daimonseikai, &MsgBox[1]);//大問正解の書き出し
		}
		for (int Num = 0; KakioeChecker >= 4 && Num < SyoumonKosuu; Num++) {//Num：小問番号
			//（小問）
			if (Num > 0) MsgBox_Syoumon[Num].Location[1] = MsgBox_Syoumon[Num - 1].Location[1] + MsgBox_Syoumon[Num - 1].OuterHeight;//0番の小問以外は，前の小問の直下
			KakioeChecker = ShowMsgBox(Mondai.syoumon[Num], &MsgBox_Syoumon[Num]);//小問の書き出し
			//（小問正解）
			if (Num < PushCounter - 1) {
				MsgBox_SyoumonSeikai[Num].Location[0] = MsgBox_Syoumon[Num].Location[0] + MsgBox_Syoumon[Num].OuterWidth;//小問の右
				MsgBox_SyoumonSeikai[Num].Location[1] = MsgBox_Syoumon[Num].Location[1];//縦は小問と同じ
				ShowMsgBox(Mondai.syoumonseikai[Num], &MsgBox_SyoumonSeikai[Num]);//小問正解の書き出し
			}
		}
		//●確定ボタンを押した回数を記録
		if (Joypad[Action[Act_Confirm]] == 1 && KakioeChecker >= 4) PushCounter++;//すべての小問を書き終え済みならPushCounterの値を増やす
		//●終了
		if (PushCounter > SyoumonKosuu + 1) break;//確定ボタンを押した回数が４回を超えたら終了
	}
	return 0;
}
//LoadMondai+LoadMsgSet+LoadMonster