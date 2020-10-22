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
	GetCurrentDirectory(MAX_PATH, AppDir);

	//●背景の指定
	int BackImg = LoadGraph(".\\File\\BackImg.jpg"); //背景のロード
	//●ジョイパッドの設定
	LoadJoypadLink(".\\File\\JoypadLink.txt"); //ジョイパッドの設定のロード

	//［ファイルのロード］
	//●モンスターのロード
	const int MonsterMax = 500;
	struct Monster Monster[MonsterMax];
	int MonsterKosuu = 0;//モンスター数（実際の個数）
	char ColumnTitle[MONSTER_COLUMNMAX][MONSTER_COLUMNTITLEFIELDMAX + 1] = { 0 };
	int ColumnKosuu = 0;
	LoadMonster(".\\File\\Monster\\Monster.csv", Monster, MonsterMax, &MonsterKosuu, NULL, ColumnTitle, &ColumnKosuu);
	//●モンスター画像サイズの取得
	int MonsterImgWide[MonsterMax];
	int MonsterImgHeight[MonsterMax];//モンスターの画像の縦横サイズを取得するための変数
	for (int i = 0; i < MonsterKosuu; i++) {//モンスター画像サイズの取得
		GetGraphSize(Monster[i].Img, &MonsterImgWide[i], &MonsterImgHeight[i]); //モンスターの画像の縦横サイズを取得してMonsterImgWide，MonsterImgHeightに取得
	}
	//●モンスター画像パスのロード
	SetCurrentDirectory(AppDir);
	char MonsterImgTitle[MonsterMax][MAX_PATH] = { 0 }; //全モンスターの画像ファイル名が入る配列
	LoadMonsterImgTitle(".\\File\\Monster\\Monster.csv", MonsterImgTitle, MonsterMax);

	//［メインループ］
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !MathgpUpdateJoypad()) {
		//●早すぎたら待機
		SleepToFitFPS(FPS);
		//●背景
		DrawGraph(0,0, BackImg, TRUE);
		//●モンスター
		for (int Num = 0; Num < MonsterKosuu; Num++) {
			//////モンスター画像
			int Rate = 3;//縮小率の半分（rate = 3で縮小率は2/3）
			int CenterX = 250 * Num + 100;//画像の左右の中心
			int CenterY = 150;//画像の下端
			DrawExtendGraph(CenterX - MonsterImgWide[Num] / Rate, CenterY - MonsterImgHeight[Num] * 2 / Rate,
				CenterX + MonsterImgWide[Num] / Rate, CenterY, Monster[Num].Img, TRUE);
			//////モンスター名，モンスターのカラム（モンスターID（0番）を除く）
			static int TextColor = GetColor(0, 0, 0); //文字色の指定
			DrawFormatString(250 * Num + 20, 160, TextColor, "名前:%s", Monster[Num].Name);
			for (int k = 0; k < ColumnKosuu; k++) {
				DrawFormatString(250 * Num + 20, 190 + 30 * k, TextColor, "%s:%d", ColumnTitle[k], Monster[Num].Column[k]);
			}
			DrawFormatString(250 * Num + 20, 200 + 30 * ColumnKosuu, TextColor, "画像:%s", MonsterImgTitle[Num]);
		}
		//●終了
		if (Joypad[Action[Act_Confirm]] == 1) break;//確定ボタンを押したら終了
	}
	return 0;
}
//LoadMonster+LoadMonsterImgPath