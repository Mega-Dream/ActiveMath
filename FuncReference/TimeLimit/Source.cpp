#include "ActiveMath.h"
#include <io.h> //フォルダー内のファイル名の取得に使用_finddata_t

//●グローバル変数
int FPS = 60;
int WindowWidth = 1000, WindowHeight = 750 - 5, ColorBitNum = 32;

struct PLAYER {
	char Name[10 + 1];
	int Level;
	int Exp;
	int Coin;
};

float TimeLimit(struct PLAYER *Player) {
	//［準備］　
	//●背景の指定
	int BackImg = LoadGraph(".\\File\\back_img03.png"); //背景のロード
	//●全体エリア
	struct AREACONTROL Entire = { 0 };
	Entire.Width = WindowWidth + 5;
	Entire.Height = WindowHeight + 5;
	//●待機モンスターエリア
	struct AREACONTROL WaitingArea = { 0 };
	WaitingArea.Width = WindowWidth + 20;
	WaitingArea.Height = 130;
	WaitingArea.BackColor = GetColor(255, 0, 0);
	WaitingArea.BackTransparency = 95;
	WaitingArea.BorderThickness = 4;
	WaitingArea.BorderColor = GetColor(200,200,200);
	WaitingArea.ParentArea_p = &Entire;
	WaitingArea.Padding[0] = 60;

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
	static struct INPUTTEXTBUTTONCTRL* ButtonSet_hh[] = { Button0, Button1, Button2, Button3, Button4, Button5 };//各シートが持つボタン配列の先頭アドレス
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
	int Error = LoadPad(FilePath_Pad, PadAreaSet, &PadAreaKosuu, PadAreaMax, &Entire,
		ButtonFormSet, &ButtonFormKosuu, ButtonFormMax,
		IndexSet, &IndexKosuu, IndexMax,
		ButtonSet_hh, ButtonKosuu, ButtonMax,
		BaseButtonSet, &BaseButtonKosuu, BaseButtonMax,
		Msg_Pad, MsgCharMax_Pad + 1, 0, &MsgBoxForm_Pad, MsgBoxFormKosuu_Pad, &MsgBox_Pad, MsgBoxKosuu_Pad, 0, 1 //フォント・タグをロードしない（０）//ジョイパッドの割り当てをロードする（０以外）
	);//LoadPadの終了時はディレクトリがパッドサブディレクトリ
	//パッドの非アクティブ化（大問書き出し後，ボタンを押すまでパッドが使えないように）
	PadManager.Active = 0;

	//●メッセージ，メッセージボックスの初期化用コピーの取得
	struct MsgBoxCtrl MsgBox_Pad_Copy = MsgBox_Pad;//
	char Msg_Pad_Copy[MsgCharMax_Pad + 1];
	strcpy(Msg_Pad_Copy, Msg_Pad);
	//［問題関連の宣言と初期化］　
	//●問題の選定
	//（問題のファイル名を取得）
	SetCurrentDirectory(AppDir);
	SetCurrentDirectory(".\\File\\Mondai\\Group01");
	const int MondaiFileMax = 20;
	char MsgFilePath[MondaiFileMax][MAX_PATH] = { 0 };//すべての問題ファイル名を取得する配列
	struct _finddata_t fd;
	long fhd;
	fhd = _findfirst("*.ack", &fd);
	if (fhd == -1) return 1;
	strcpy(MsgFilePath[0], fd.name);//取得した最初のファイル名を配列に書き写す
	int MondaiFileKosuu;//問題の個数
	for (MondaiFileKosuu = 1; MondaiFileKosuu < MondaiFileMax && !_findnext(fhd, &fd); MondaiFileKosuu++) {
		strcpy(MsgFilePath[MondaiFileKosuu], fd.name);////取得したファイル名を配列に書き写す。処理中はMondaiKosuuは問題のカウント数
	}
	_findclose(fhd);
	//（問題数と問題番号の確定）
	srand(GetNowCount()); //現在の時刻でシードを取得
	const int MondaiMax = 5; //最大問題数を指定
	int MondaiFileNum[MondaiMax];
	for (int i = 0; i < MondaiMax; i++) MondaiFileNum[i] = -1;
	int MondaiKosuu = rand() % MondaiMax + 1; //問題数の確定
	for (int i = 0; i < MondaiKosuu; i++){
		MondaiFileNum[i] = rand() % MondaiFileKosuu; //問題番号の確定
	}
	//●問題のロード
	struct Kadai Mondai[MondaiMax] = { 0 }; //メッセージを入れる
	int SyoumonKosuu[MondaiMax];
	for (int i = 0; i < MondaiKosuu; i++) {
		//（問題のロード）
		LoadMondai(MsgFilePath[MondaiFileNum[i]], &Mondai[i], &SyoumonKosuu[i], 0);//１：GetDirFlag
		//（小問の並べ替え）
		char syoumon_buff[SYOUMON_MAX][SYOUMON_FIELDSIZE + 1] = { 0 };
		char syoumonseikai_buff[SYOUMON_MAX][SYOUMONSEIKAI_FIELDSIZE + 1];
		int Kosuu = SyoumonKosuu[i];
		for (int s = 0; s < Kosuu; s++) {
			int no = rand() % (Kosuu - s);
			int t;
			int n = 0;
			for (t = 0; n <= no; t++) {
				if (syoumon_buff[t][0] =='\0') n++;
			}
			t--;
			strcpy(syoumon_buff[t], Mondai[i].syoumon[s]);
			strcpy(syoumonseikai_buff[t], Mondai[i].syoumonseikai[s]);
		}
		for (int u = 0; u < Kosuu; u++) {
			strcpy(Mondai[i].syoumon[u], syoumon_buff[u]);
			strcpy(Mondai[i].syoumonseikai[u], syoumonseikai_buff[u]);
		}
	}
	//（最初の問題の指定）
	int MondaiNum = 0;
	SetLocalDirMsgDirFromMsgPath(MsgFilePath[MondaiFileNum[MondaiNum]]);
	//●問題関連ファイルのロード（メッセージフォーム，メッセージボックス，モンスター，設定（フォント，フォント画像，タグ設定））
	//（問題）
	const int MsgBoxFormKosuu = 3;
	static struct MsgBoxForm MsgBoxForm[MsgBoxFormKosuu];//[0]大問・小問　[1]小問正解　[2]小問履歴・小問正解履歴
	const int MsgBoxKosuu = 3;
	static struct MsgBoxCtrl MsgBox[MsgBoxKosuu];//[0]大問　[1]小問　[2]小問正解
	//（モンスター）
	const int MonsterMax = 500;
	struct Monster Monster[MonsterMax];
	int MonsterKosuu = 0;//モンスター数（実際の個数）
	static int MonsterImgWidth[MonsterMax];
	static int MonsterImgHeight[MonsterMax];//モンスター画像の縦横サイズを取得するための変数
	int  MonsterImgFlag = 1;//モンスター画像の表示フラグ（０：非表示　０以外：表示）

	char ColumnTitle[MONSTER_COLUMNMAX][MONSTER_COLUMNTITLEFIELDMAX + 1] = { 0 };
	int ColumnKosuu = 0;
	//（ロード）
	LoadMondaiSet(LocalDir, MsgBoxForm, MsgBoxFormKosuu, MsgBox, MsgBoxKosuu,
		Monster, MonsterMax, &MonsterKosuu, NULL, ColumnTitle, &ColumnKosuu, 1, 0);//発行済み最大ID（NULL）//フォント・タグをロードする（０以外）//ジョイパッドの割り当てをロードしない（０）
	for (int i = 0; i < 3; i++) MsgBox[i].ParentArea_p = &Entire;
	//小問・小問正解の左端は，コントロールの複製前に指定（縦は随時更新。大問の縦はあとでMondaiLineから取得し，大問の横もそのときに指定する。）
	MsgBox[1].Location[0] = 50;
	MsgBox[2].Location[0] = 50 + MsgBox[1].OuterWidth;
	//●小問・小問正解コントロールの複製
	static struct MsgBoxCtrl MsgBox_Syoumon[3];
	static struct MsgBoxCtrl MsgBox_SyoumonSeikai[3];
	for (int i = 0; i < 3; i++) {
		MsgBox_Syoumon[i] = MsgBox[1];
		MsgBox_SyoumonSeikai[i] = MsgBox[2];
	}
	//※この時点では，大問フォーム[0]，小問フォーム[2]，小問正解フォーム[2]　※[2]は履歴用のフォーム

	//●最上位の小問は[0]に，最上位の小問正解は[1]に書き換え
	MsgBox_Syoumon[0].MsgBoxForm_p = &MsgBoxForm[0];
	MsgBox_SyoumonSeikai[0].MsgBoxForm_p = &MsgBoxForm[1];

	//●モンスター番号の確定（該当がなければ0のまま）
	int MonsterNum[MondaiMax];//モンスターの要素番号
	for (int i = 0; i < MondaiMax; i++) MonsterNum[i] = -1;
	for (int d = 0; d < MondaiKosuu; d++) {
		for (int i = 0; i < MonsterKosuu; i++) {
			if (Mondai[d].monsterID == Monster[i].Column[0]) {
				MonsterNum[d] = i; break;
			}
		}
	}
	//■モンスター画像サイズの取得
	for (int i = 0; i < MonsterKosuu; i++) {//モンスター画像サイズの取得
		GetGraphSize(Monster[i].Img, &MonsterImgWidth[i], &MonsterImgHeight[i]); //モンスターの画像の縦横サイズを取得してMonsterImgWide，MonsterImgHeightに取得
	}
	//■制限時間（秒）の取得
	int ExpEarned = 0;//経験値（ポイント）
	int CoinEarned = 0;//コイン（ゴールド）
	for (int i = 0; i < MondaiKosuu; i++) {
		ExpEarned += Monster[MonsterNum[i]].Column[2];
		CoinEarned += Monster[MonsterNum[i]].Column[3];
	}
	//●表示する番号，シーンの切り替え
	int SyoumonNum = 0;//表示する小問番号
	int SeikaiFlag = 0;//正解フラグ
	int Scene = -2;//－２：　－１：　０：　１：　２：
	//●
	char TextBuff[20];
	//●判定するメッセージ
	char Msg_Confirm[INPUTTEXTBUTTON_FIELDSIZE + 1];//判定するメッセージ
	const int MsgBoxFormKosuu_Confirm = 1;
	static struct MsgBoxForm MsgBoxForm_Confirm;
	const int MsgBoxKosuu_Confirm = 1;
	static struct MsgBoxCtrl MsgBox_Confirm;
	SetCurrentDirectory(AppDir);
	LoadMsgSet(".\\File\\MsgConfirm", &MsgBoxForm_Confirm, MsgBoxFormKosuu_Confirm, &MsgBox_Confirm, MsgBoxKosuu_Confirm, 0, 0);//フォントタグ設定をロードする（０以外）
	//●判定結果
	char Msg_Judge[INPUTTEXTBUTTON_FIELDSIZE + 1];
	const int MsgBoxFormKosuu_Judge = 1;
	static struct MsgBoxForm MsgBoxForm_Judge;
	const int MsgBoxKosuu_Judge = 1;
	static struct MsgBoxCtrl MsgBox_Judge;
	SetCurrentDirectory(AppDir);
	LoadMsgSet(".\\File\\MsgJudge", &MsgBoxForm_Judge, MsgBoxFormKosuu_Judge, &MsgBox_Judge, MsgBoxKosuu_Judge, 0, 0);//フォントタグ設定をロードする（０以外）
	//●バトル中メッセージ
	const int MsgCharMax_Battle = 300;//読み込み可能な文字数
	char Msg_Battle[MsgCharMax_Battle + 1] = { 0 };//メッセージ
	//●バトル中メッセージ関連ファイルのロード（メッセージボックスフォーム，メッセージボックス，設定（フォント，フォント画像，タグ設定））
	SetCurrentDirectory(AppDir);
	int MsgBoxFormKosuu_Battle = 1;
	static struct MsgBoxForm MsgBoxForm_Battle;//メッセージボックスフォーム
	int MsgBoxKosuu_Battle = 1;
	static struct MsgBoxCtrl MsgBox_Battle;//メッセージボックス
	LoadMsgSet(".\\File\\MsgBattle", &MsgBoxForm_Battle, MsgBoxFormKosuu_Battle, &MsgBox_Battle, MsgBoxKosuu_Battle, 0, 0);//メッセージボックスフォームの個数１//メッセージボックスの個数１//フォントタグ設定をロードする（０以外）
	//［メッセージ関連の宣言と初期化］　
	//●メッセージのロード
	const int MsgCharMax_End = 300;//読み込み可能な文字数
	char Msg_End[MsgCharMax_End + 1] = { 0 };//メッセージ

	//●メッセージ関連ファイルのロード（メッセージボックスフォーム，メッセージボックス，設定（フォント，フォント画像，タグ設定））
	SetCurrentDirectory(AppDir);
	int MsgBoxFormKosuu_End = 1;
	static struct MsgBoxForm MsgBoxForm_End;//メッセージボックスフォーム
	int MsgBoxKosuu_End = 1;
	static struct MsgBoxCtrl MsgBox_End;//メッセージボックス
	LoadMsgSet(".\\File\\MsgEnd", &MsgBoxForm_End, MsgBoxFormKosuu_End, &MsgBox_End, MsgBoxKosuu_End, 0, 0);//メッセージボックスフォームの個数１//メッセージボックスの個数１//フォントタグ設定をロードする（０以外）
	//●音声ファイルのロード
	SetCurrentDirectory(AppDir);
	int PushSound = LoadSoundMem(".\\File\\poka01.mp3");
	int AtuckSound = LoadSoundMem(".\\File\\MsgJudge\\Sound\\damage7.mp3");
	int MissSound = LoadSoundMem(".\\File\\MsgJudge\\Sound\\swish2.mp3");
	int DamageSound = LoadSoundMem(".\\File\\MsgEnd\\Sound\\attack01.mp3");

	//●基準線
	int MonsterBaseLine1 = 148;//待機モンスターの下から10％の位置
	int MonsterBaseLine2 = 440;//モンスター下端
	int MonsterBaseLine3 = 700;//モンスター前進時
	int MonsterBaseLine4 = 800;//モンスター接近時
	int MondaiLine = MonsterBaseLine2 + 10;
	//●位置
	WaitingArea.Location[0] = -10;
	WaitingArea.Location[1] = 34;
	MsgBox[0].Location[0] = 50;
	MsgBox[0].Location[1] = MondaiLine;
	//（パッドパッドエリアのパラメータの位置指定）
	MsgBox_Pad.Location[0] = 630;
	MsgBox_Pad.Location[1] = MondaiLine - MsgBox_Pad.OuterHeight;
	PadAreaSet[0].Location[0] += MsgBox_Pad.Location[0];//パッドの横位置を指定（メッセージボックスと同じ位置）
	PadAreaSet[0].Location[1] += MsgBox_Pad.Location[1];//メッセージボックスの直下を指定

	MsgBox_Judge.Location[0] = 53 + (MsgBox[0].Width - 130) / 2;//結果の表示位置（縦）の指定

	MsgBox_Battle.Location[0] = MsgBox[0].Location[0];//クリアーメッセージの横位置を指定（大問と同じ位置）
	MsgBox_Battle.Location[1] = MondaiLine;//クリアーメッセージの縦位置を指定（大問と同じ位置）

	MsgBox_End.Location[0] = MsgBox[0].Location[0];//クリアーメッセージの横位置を指定（大問と同じ位置）
	MsgBox_End.Location[1] = MondaiLine;//クリアーメッセージの縦位置を指定（大問と同じ位置）

	//タイムゲージの画像のロード
	int GaugeBackImg = LoadGraph(".\\File\\gauge_back_img.png");
	int GaugeImg = LoadGraph(".\\File\\gauge_img.png");

	//↓なぜか，StartJoypadVibrationは２回目以降でないと振動しないため，事前に１回目を済ませておく
	StartJoypadVibration(DX_INPUT_PAD1, 1000, 0);//（１回目は振動しないが一応０秒に設定）
	//↑連続ではだめで，WaitTimer(5)を挟んで１回目と２回目を5ミリ秒以上あけると２回目で振動する。原因不明
	int MondaiFlag = 0;
	int GaugeFlag = 0;//ゲージフラグ（０：停止　１：作動）※ゲージ満タン，ゲームクリアのときに停止となる　※開始の動作の終わり，モンスターの攻撃後，次の大問に移るときに作動
	int GaugeFrame = 0;//ゲージフレーム（次の大問に移るときにリセット）
	int TimeFlag = 0;//経過時間フラグ（０：停止　１：作動）※初期，ゲームクリアのときに停止となる　※開始の動作が終わると作動
	int TimeFrame = 0;//経過フレーム（次の大問に移っても持続）
	//［メインループ］
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !MathgpUpdateJoypad()) {
		//●早すぎたら待機
		SleepToFitFPS(FPS);
		//●全体エリア
		ShowArea(&Entire, 1);
		//●背景
		DrawGraph(Entire.Nest[0], Entire.Nest[1], BackImg, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 51);//アルファブレンド20％
		//●タイム（フレーム数から割り出した時間）
		static int Time_BackColor = GetColor(0, 0, 0);
		static int Time_TextColor = GetColor(255, 255, 255);
		DrawBox(0, 0, WindowWidth, 34, Time_BackColor, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawFormatString(750, 5, Time_TextColor, "タイム:%7.2f秒", TimeFrame / (float)FPS);
		if (TimeFlag != 0) TimeFrame++;//フレームのカウント
		//●待機エリア
		ShowArea(&WaitingArea, 1);


		//●ゲージ
		static float Time_Elapsed;//経過時間（秒）
		static int GaugeRate;//経過率（％）
		if (GaugeFlag != 0) {//ゲージ作動時
			GaugeFrame++;//ゲージを進める
			Time_Elapsed = GaugeFrame / (float)FPS;//経過時間（秒）
			GaugeRate = 100 * Time_Elapsed / Monster[MonsterNum[MondaiNum]].Column[1];//経過率（％）
		}
		//●ゲージ満タン
		if (GaugeRate >= 100) {
			GaugeFlag = 0;//これ以上TimeRateを増やさない
			if (Scene == 0) {
				Scene = 2;//判定シーンでない，敗北シーンでないならモンスターの攻撃シーンへ進む
				MondaiFlag = 0;//問題を非表示
				GaugeFrame = 0;//ゲージのリセット
			}
		}
		static int Count_D = 0;
		if (MondaiNum >= 0) {
			//●待機モンスター
			int Rate = 2 / 3;//実寸の2/3の大きさで表示（中心から左右に1/3の位置）
			int ImgX1 = WaitingArea.Nest[0], ImgY1, ImgX2, ImgY2;
			SetDrawArea(WaitingArea.Nest[0], WaitingArea.Nest[1], WaitingArea.Nest[2], WaitingArea.Nest[3]);//描画可能領域の指定
			for (int i = MondaiNum + 1; i < MondaiKosuu; i++) {
				ImgX2 = ImgX1 + MonsterImgWidth[MonsterNum[i]] * 2 / 3;
				ImgY1 = MonsterBaseLine1 - MonsterImgHeight[MonsterNum[i]] * 2 / 3 * 0.9;
				ImgY2 = ImgY1 + MonsterImgHeight[MonsterNum[i]] * 2 / 3;
				if (Monster[MonsterNum[i]].Img != -1) DrawExtendGraph(ImgX1, ImgY1, ImgX2, ImgY2, Monster[MonsterNum[i]].Img, true);  //待機モンスター画像を描画する
				ImgX1 = ImgX2 + 20;
			}
			SetDrawArea(0, 0, WindowWidth, WindowHeight);//描画可能領域の指定解除

			//●モンスター
			if (MonsterImgFlag != 0) {
				//（モンスター画像）
				int MonsterX = Entire.Nest[0] + 53 + (MsgBox[0].Width - MonsterImgWidth[MonsterNum[MondaiNum]]) / 2;
				int MonsterY = Entire.Nest[1] + MonsterBaseLine2 - MonsterImgHeight[MonsterNum[MondaiNum]];
				DrawGraph(MonsterX, MonsterY, Monster[MonsterNum[MondaiNum]].Img, TRUE);
				if (GaugeFlag != 0) {//モンスターが表示されていてもゲージが停止時はゲージを表示しない
					//（円ゲージ）※ゲージがカラになれば時間切れ
					int GaugeX = MonsterX - 10;//円ゲージの中心X
					int GaugeY = MonsterY - 10;//円ゲージの中心Y
					DrawCircleGauge(GaugeX, GaugeY, 100, GaugeBackImg, 0);//円ゲージ
					DrawCircleGauge(GaugeX, GaugeY, 100 - GaugeRate, GaugeImg, 0);//円ゲージ
				}
			}
			//●開始メッセージ
			if (Scene == -1) {
				static int Count = 0;
				Count++;
				static int i = 0;
				if (Count == FPS / 2 * (i + 1) && MondaiKosuu > i) {
					//（開始メッセージ）
					if (i == 0) strcpy(Msg_Battle, "<p>");
					else strcat(Msg_Battle, "<p>");
					strcat(Msg_Battle, Monster[MonsterNum[i]].Name);
					strcat(Msg_Battle, "が　あらわれた！</p>");
					Reparse(&MsgBox_Battle);
					i++;
				}
				if (Count == FPS / 2 * (i + 2) && MondaiKosuu == i) {
					//（開始メッセージ）
					GaugeFlag = 1;
					MondaiFlag = 1;
					Count = 0;
					Scene = 0;
					i = 0;
				}
				ShowMsgBox(Msg_Battle, &MsgBox_Battle);
			}
			//●問題
			int End = SyoumonNum - 2;
			if (End < 0) End = 0;
			//（大問）
			if (MondaiFlag != 0) {
				if (ShowMsgBox(Mondai[MondaiNum].daimon, &MsgBox[0]) == 6) Count_D++;
				//（大問書き出し後のパッドのアクティブ化と小問の表示）
				if (Count_D > 0) {//少し待ってから小問の表示
					if (Count_D == 1) PlaySoundMem(PushSound, DX_PLAYTYPE_BACK, TRUE);//ボタンを押した音
					else if (Count_D == FPS / 4) {
						PadManager.Active = 1;//少し待ってからパッドのアクティブ化（インデックスエリアとベースボタンエリアのみアクティブとなる）
						GetActiveElement(&MsgBox_Pad);//ActiveElementを0
					}
					for (int i = 0; SyoumonNum - i >= 0 && i < 3; i++) {
						if (i == 0) {
							MsgBox_Syoumon[i].Location[1] = MsgBox[0].Location[1] + MsgBox[0].OuterHeight;//最上位の小問以外は，前の小問の直下
						}
						else if (i > 0) MsgBox_Syoumon[i].Location[1] = MsgBox_Syoumon[i - 1].Location[1] + MsgBox_Syoumon[i - 1].OuterHeight;//最上位の小問以外は，前の小問の直下
						ShowMsgBox(Mondai[MondaiNum].syoumon[SyoumonNum - i], &MsgBox_Syoumon[i]);
					}
					//（小問正解）
					for (int i = 0; SyoumonNum - i >= 0 && i < 3; i++) {
						MsgBox_SyoumonSeikai[i].Location[1] = MsgBox_Syoumon[i].Location[1];//縦は小問と同じ
						if (i == 0 && SeikaiFlag == 0) ShowMsgBox("<math></math>", &MsgBox_SyoumonSeikai[i]);//正解（正解時以外，SyoumonNumの正解は非表示）
						else ShowMsgBox(Mondai[MondaiNum].syoumonseikai[SyoumonNum - i], &MsgBox_SyoumonSeikai[i]);//正解（正解時以外，SyoumonNumの正解は非表示）
						//（小問ボックスと小問正解ボックスの高さをそろえる）
						if (MsgBox_Syoumon[i].Height < MsgBox_SyoumonSeikai[i].Height) MsgBox_Syoumon[i].Height = MsgBox_SyoumonSeikai[i].Height;
						else MsgBox_SyoumonSeikai[i].Height = MsgBox_Syoumon[i].Height;
					}
				}
			}
		}
		else Count_D = 0;//初期値に戻す
		//●パッドの表示・メッセージボックスの表示・メッセージのジョイパッド操作
		int ShowMsgBoxFlag = 1;
		if (ShowPadJ(Msg_Pad, &MsgBox_Pad, MsgCharMax_Pad + 1, ShowMsgBoxFlag, IndexSet, IndexKosuu, ButtonSet_hh, ButtonKosuu, BaseButtonSet, BaseButtonKosuu, PadAreaSet, &PadManager) == 1) {//プッシュした長さが１のとき
			//●確定ボタン
			if (Scene == 0 && PadManager.PushedNo == 35 && PadAreaSet[2].Active == 1) {//ベースボタンの35番（確定ボタン）をクリックした。　ベースボタン：1000番代
				Scene = 1;//（正否判定に進む）
			}
		}
		//●文末でEnterを押して確定
		if (Scene == 0 && MsgBox_Pad.Condition == 101) {
			MsgBox_Pad.Condition = 1;//毎回ここに入ってこないように１に戻す
			Scene = 1;//（正否判定に進む）
		}

		//〔正否判定〕
		if (Scene == 1) {
			static int CountJ = 0;
			static int Scroll = 0;//判定メッセージのスクロール量
			CountJ++;
			//●パッドのリセットと判定用メッセージの更新
			if (CountJ == 1) {
				//（判定用メッセージの更新）
				strcpy(Msg_Confirm, Msg_Pad);//判定用メッセージを取得する
				Reparse(&MsgBox_Confirm);//タグの再読み込み指示
				MsgBox_Confirm.Tag[0].ConnectionP = 0;//FlameCounterのリセット（最初の書き出しとし音を鳴らすため）
				MsgBox_Confirm.Location[1] = MonsterBaseLine2 - (MonsterImgHeight[MonsterNum[MondaiNum]] + MsgBox_Confirm.Height) / 2;//判定メッセージの表示位置（縦）の指定　★★★書き出すまでMsgBox_Hantei.Heightが確定しない
				//（パッドのリセット）
				strcpy(Msg_Pad, Msg_Pad_Copy);//パッドのメッセージをクリア（パッド操作から正否判定に進んだので，タグの再読み込みは不要）
				PadManager.Active = 0;//パッドの非アクティブ化（判定が終わるまでパッドが使えないように）
				EraseActiveElement(&MsgBox_Pad);//ActiveElementを-1
			}
			//●判定用メッセージの表示
			else if (FPS < CountJ && CountJ < FPS * 2) {
				MsgBox_Confirm.Location[0] = MsgBox[0].Location[0] + (MsgBox[0].Width - 100) / 2 + FPS - Scroll;//判定メッセージの表示位置（横）の指定
				ShowMsgBox(Msg_Confirm, &MsgBox_Confirm);
				Scroll += 2;//判定メッセージのスクロール量の更新
			}
			//●判定（アタック音＋結果メッセージの作成＋正解なら表示する正解番号の更新）
			else if (CountJ == FPS * 2) {
				//（正解）
				if (!strcmp(Mondai[MondaiNum].syoumonseikai[SyoumonNum], Msg_Confirm)) {
					PlaySoundMem(AtuckSound, DX_PLAYTYPE_BACK, TRUE);//正解音
					strcpy(Msg_Judge, "<p> Correct! </p>");//判定用メッセージを取得する
					SeikaiFlag = 1;
					Reparse(&MsgBox_SyoumonSeikai[0]);//タグの再読み込み指示（正解ボックスを表示させるため）
				}
				//（不正解）
				else {
					PlaySoundMem(MissSound, DX_PLAYTYPE_BACK, TRUE);//不正解音
					strcpy(Msg_Judge, "<p>Try again.</p>");//判定用メッセージを取得する
				}
				Reparse(&MsgBox_Judge);//タグの再読み込み指示
				MsgBox_Judge.Location[1] = MonsterBaseLine2 - (MonsterImgHeight[MonsterNum[MondaiNum]] + MsgBox_Judge.Height) / 2;//結果の表示位置（縦）の指定
			}
			//●結果の表示
			else if (FPS * 2 < CountJ && CountJ < FPS * 3) {
				ShowMsgBox(Msg_Judge, &MsgBox_Judge);
				if (SeikaiFlag == 1 && CountJ % (FPS / 5) < FPS / 10) MonsterImgFlag = 0;
				else  MonsterImgFlag = 1;
			}
			//●表示する問題番号の決定
			else if (CountJ == FPS * 3) {
				//（次の小問の準備）
				if (SyoumonNum + 1 < SyoumonKosuu[MondaiNum]) {
					//（正解のとき）
					if (SeikaiFlag == 1) {
						//（小問番号・フラグの更新）
						SyoumonNum++;//表示する問題番号の更新
						SeikaiFlag = 0;
						MonsterImgFlag = 1;//モンスター画像の表示
						//（小問メッセージボックスの更新）
						for (int i = 0; i < 3; i++) {
							Reparse(&MsgBox_Syoumon[i]);//タグの再読み込み指示
							Reparse(&MsgBox_SyoumonSeikai[i]);//タグの再読み込み指示
						}
						MsgBox_Syoumon[0].Tag[0].ConnectionP = 0;//Tag[0].ConnectionPはFlameCounterを表す//最上位の小問がパカパカするようにリセット。
						MsgBox_Syoumon[0].Condition = 1;//音が鳴るようにリセット。
					}
					//（正否に関わらず）
					CountJ = 0;//カウンターのリセット
					Scene = 0;//正否判定を抜ける
					PadManager.Active = 1;//パッドのアクティブ化（インデックスエリアとベースボタンエリアのみアクティブとなる）
					GetActiveElement(&MsgBox_Pad);//ActiveElementを0
				}
				//（次の小問が存在しない）
				else {
					//（正解のとき）
					if (SeikaiFlag == 1) {
						//（次の大問の準備）
						if (MondaiNum + 1 < MondaiKosuu) {
							//（大問番号・ローカルディレクトリの変更・フラグの更新）
							MondaiNum++;
							SetCurrentDirectory(LocalDir);
							SetLocalDirMsgDirFromMsgPath(MsgFilePath[MondaiFileNum[MondaiNum]]);//ローカルディレクトリ・メッセージディレクトリの変更
							Count_D = 0;
							//（大問メッセージボックスの更新）
							MsgBox[0].Tag[0].ConnectionP = 0;//Tag[0].ConnectionPはFlameCounterを表す//最上位の小問がパカパカするようにリセット。
							MsgBox[0].Condition = 1;
							Reparse(&MsgBox[0]);//タグの再読み込み指示
							//（小問番号・フラグの更新）
							SyoumonNum = 0;
							SeikaiFlag = 0;
							MonsterImgFlag = 1;//モンスター画像の表示
							//（小問メッセージボックスの更新）
							for (int i = 0; i < 3; i++) {
								Reparse(&MsgBox_Syoumon[i]);//タグの再読み込み指示
								Reparse(&MsgBox_SyoumonSeikai[i]);//タグの再読み込み指示
							}
							MsgBox_Syoumon[0].Tag[0].ConnectionP = 0;//Tag[0].ConnectionPはFlameCounterを表す//最上位の小問がパカパカするようにリセット。
							MsgBox_Syoumon[0].Condition = 1;//音が鳴るようにリセット。
							//（）
							CountJ = 0;//カウンターのリセット
							Scene = 0;//正否判定を抜ける
							MondaiFlag = 1;//問題を表示
							GaugeFlag = 1;//ゲージの起動
							GaugeFrame = 0;
						}
						//（次の大問が存在しない）
						else {
							MonsterImgFlag = 0;//モンスター画像の非表示
							MondaiNum = -1;
							MondaiFlag = 0;//問題を非表示
							GaugeFlag = 0;//ゲージの停止
							TimeFlag = 0;//経過時間を止める（次の大問が存在しないときだけ）
						}
					}
					//（不正解のとき）
					else {
						CountJ = 0;//カウンターのリセット
						Scene = 0;//正否判定を抜ける
						PadManager.Active = 1;//パッドのアクティブ化（インデックスエリアとベースボタンエリアのみアクティブとなる）
						GetActiveElement(&MsgBox_Pad);//ActiveElementを0
					}
				}
				//（正否に関わらず）
				Scroll = 0;//判定メッセージのスクロール量をリセット
			}
			//●次の大問が存在しない（クリアーメッセージの表示）
			else if (CountJ > FPS * 3) {
				static int Finish = 0;
				//（経験値獲得のメッセージの準備）
				if (Finish == 0) {
					Finish++;
					strcpy(LocalDir, AppDir);
					strcat(LocalDir, "\\File\\MsgEnd");
					//（経験値の獲得）
					Player->Exp += ExpEarned;
					strcpy(Msg_End, "<p>#sound_l{.\\one35.mp3}まもののむれを　やっつけた！</p><p><math>");
					_itoa(ExpEarned, TextBuff, 10);
					strcat(Msg_End, TextBuff);
					strcat(Msg_End, "</math>ポイントの　けいけんちを　かくとく！</p>");
					ClearMsgBox(&MsgBox_End);
				}
				//（レベルアップのメッセージの準備）
				else if (Finish == 2) {
					Finish++;
					int Level = Player->Exp / 100 + 1;
					if (Level > Player->Level) {//レベルアップがあるとき
						Player->Level = Level;
						strcpy(Msg_End, "<p>#sound_l{.\\trumpet1.mp3}#Wait(1)");
						strcat(Msg_End, Player->Name);
						strcat(Msg_End, "は　レベル<math>");
						_itoa(Player->Level, TextBuff, 10);
						strcat(Msg_End, TextBuff);
						strcat(Msg_End, "</math>に　あがった！</p>");
						ClearMsgBox(&MsgBox_End);
					}
					else Finish++;//レベルアップがないとき，Finish == 4となる
				}
				//（コイン獲得のメッセージの準備）
				if (Finish == 4) {//ここはelse if としないこと（レベルアップがないとき，ここに入るようにするため）
					Finish++;
					Player->Coin += CoinEarned;
					strcpy(Msg_End, "<p><math>");
					_itoa(CoinEarned, TextBuff, 10);
					strcat(Msg_End, TextBuff);
					strcat(Msg_End, "</math>ゴールドを　てにいれた！</p>");
					ClearMsgBox(&MsgBox_End);
				}
				//（TimeLimit関数の終了）
				else if (Finish == 6) {
					CountJ = 0;//カウンターのリセット
					Finish = 0;//初期値に戻す
					return TimeFrame / (float)FPS;//タイムスコアーを戻り値とする
				}
				//クリアーメッセージの表示
				switch (ShowMsgBox(Msg_End, &MsgBox_End)) {
				case 6: Finish++;//次のメッセージの準備またはTimeLimit関数の終了
				}
			}
		}
		//〔タイムアップ〕
		else if (Scene == 2) {
			static int Scroll = 0;//判定メッセージのスクロール量
			static int Count = 0;
			Count++;
			//●タイムアップメッセージの作成
			if (Count == 1) {
				//（パッドの非アクティブ化）
				PadManager.Active = 0;
				//（タイムアップメッセージの作成）
				PlaySoundMem(DamageSound, DX_PLAYTYPE_BACK, TRUE);
				strcpy(Msg_Judge, "<p> Time up! </p>");//時間切れメッセージを取得する
				Reparse(&MsgBox_Judge);//タグの再読み込み指示
				//（タイムアップメッセージの色の変更）
				MsgBoxForm_Judge.FontColor = GetColor(255, 102, 0);
				MsgBoxForm_Judge.BorderColor = GetColor(255, 102, 0);
				//（ジョイパッドの振動開始）
				StartJoypadVibration(DX_INPUT_PAD1, 1000, 250);
			}
			//●タイムアップメッセージの表示
			else if (1 < Count && Count < FPS) {
				MsgBox_Judge.Location[1] = MonsterBaseLine2 - 50 - Scroll;//判定メッセージの表示位置の指定
				Scroll += 2;//判定メッセージのスクロール量の更新
				//（画面の振動）
				if (Count % 2 == 0) Entire.Location[1] = -5;
				else Entire.Location[1] = 0;
			}
			//（終了）
			ShowMsgBox(Msg_Judge, &MsgBox_Judge);
			if (Count >= FPS * 2) {
				//（敗戦メッセージの準備）
				if (Count == FPS * 2) strcpy(Msg_End, "<p>じかんぎれです。</p>");
				//（TimeLimit関数の終了）
				static int Finish = 0;
				if (Finish == 1) {
					Scroll = 0;	Count = 0;//初期値に戻す
					Finish = 0;//初期値に戻す
					return -1;//TimeLimit関数の終了（-1を戻り値とする）
				}
				//敗戦メッセージの表示
				switch (ShowMsgBox(Msg_End, &MsgBox_End)) {
				case 6: Finish++;//関数の終了
				}
			}

		}
		//●開始時
		if (Scene == -2) {
			static int BlindColor = GetColor(0, 0, 0);
			static int Count = 0;
			int Add = Count * 360 / FPS;
			DrawBox(0, 0, WindowWidth, WindowHeight / 2 - Add, BlindColor, true);
			DrawBox(0, WindowHeight / 2 + Add, WindowWidth, WindowHeight, BlindColor, true);
			if (Add >= WindowHeight / 2) { Scene = -1; TimeFlag = 1; Count = 0; }//経過時間を進める
			Count++;
		}
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//［起動に伴う処理］　
	//●DXライブラリの設定↓////
	SetWaitVSyncFlag(FALSE);//垂直同期信号をオフ
	ChangeWindowMode(true); //ウィンドウモードの切り替え
	if (DxLib_Init() == -1) return -1; //DXライブラリ初期化処理
	if (ActiveMath_Init() == -1) return -1; //ActiveMathの初期化処理
	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定
	SetGraphMode(WindowWidth, WindowHeight, ColorBitNum); //ウインドウサイズの指定

	//●フォント関係の設定
	SetFontSize(24); //フォントサイズの指定
	ChangeFont("UD デジタル 教科書体 N-R"); //フォントの指定
	SetFontThickness(0);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);

	//［タイムスコアーエリア］［プレイヤーのステータスエリア］
	struct AREACONTROL StatusArea[2] = { 0 };//[0]：タイムスコアーエリア　[1]：プレイヤーの状態エリア
	int AreaKosuu;
	LoadAreaSet(".\\File\\StatusArea.csv", StatusArea, &AreaKosuu, 2, NULL);
	StatusArea[0].Location[0] = (WindowWidth - StatusArea[0].Width) / 2;
	StatusArea[0].Location[1] = (WindowHeight - (StatusArea[0].Height + StatusArea[1].Margin[1] + StatusArea[1].Height)) / 2;
	//［プレイヤー］
	struct PLAYER Player = { 0 };
	strcpy(Player.Name, "ゆうしゃ");
	Player.Level = 5;
	Player.Exp = 499;
	Player.Coin = 50;

	//［タイムアタックモード］
	float Time = TimeLimit(&Player);
	//［タイムスコアー・プレイヤーのステータスの表示モード］
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !MathgpUpdateJoypad()) {
		//●早すぎたら待機
		SleepToFitFPS(FPS);
		//●エリア
		ShowArea(StatusArea, AreaKosuu);
		//●結果
		static int TextColor = GetColor(255, 255, 255);
		//（タイムスコアー）
		if (Time == -1) DrawString(StatusArea[0].Nest[0] + 0, StatusArea[0].Nest[1] + 0, "タイム　時間切れ", TextColor);
		else DrawFormatString(StatusArea[0].Nest[0] + 0, StatusArea[0].Nest[1] + 0, TextColor, "タイム　%6.2f秒", Time);
		//（プレイヤーのステータス）
		static int NameWidth = GetDrawStringWidth(Player.Name, strlen(Player.Name));
		static int NameX = (StatusArea[1].Nest[2] - StatusArea[1].Nest[0] - NameWidth) / 2;
		DrawFormatString(StatusArea[1].Nest[0] + NameX, StatusArea[1].Nest[1], TextColor, "%s", Player.Name);
		DrawLine(StatusArea[1].Nest[0] - StatusArea[1].Padding[0], StatusArea[1].Nest[1] + 28, StatusArea[1].Nest[2] + StatusArea[1].Padding[2], StatusArea[1].Nest[1] + 28, StatusArea[1].BorderColor, 2);
		DrawFormatString(StatusArea[1].Nest[0], StatusArea[1].Nest[1] + 34, TextColor, "レベル %9d\n経験値 %9d\nコイン %9d", Player.Level, Player.Exp, Player.Coin);
		//●確定ボタンで抜ける
		if (Joypad[Action[Act_Confirm]] == 1) break;
	}
	//［終了］
	DxLib_End();// ＤＸライブラリ使用の終了処理
	return -1;// ソフトの終了
}
//TimeLimit