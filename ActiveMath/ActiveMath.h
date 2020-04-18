#pragma once
////////////
namespace ActiveMath {
#define JoypadInputMax 31//０番は使用していない
//■アクション番号の定義
#define ActMax 50//０番は使用していない
/////////////////////////
#define Act_InputText 1
#define Act_BackSpace 2
#define Act_NextPosition 3
#define Act_Delete 4
#define Act_PrevIndex 5
#define Act_NextIndex 6
#define Act_TextCursorLeft 7
#define Act_TextCursorRight 8
#define Act_ButtonCursorDown 15
#define Act_ButtonCursorLeft 16
#define Act_ButtonCursorRight 17
#define Act_ButtonCursorUp 18
#define Act_LeverX 29
#define Act_LeverY 30
#define Act_AreaChangeFirst 33
#define Act_AreaChangeSecond 34
#define Act_ScrollMsg 41
#define Act_Confirm 42

////////　変　数　////////
	//■変数
	extern int MouseX;
	extern int MouseY;
	extern int Key[256];
	extern int Mouse[10];
	extern int JoypadInputMode;
	extern int Joypad[JoypadInputMax];// ジョイパッドのボタンが押されているフレーム数を
	//extern int ChangedJoypadNum[JoypadInputMax];
	extern int ActionNum[ActMax];

	extern int SystemFontSize;
	extern char FilePath_Font[MAX_PATH];//FontSetFile
	extern char FileTitle_Font[MAX_PATH];
	extern char FilePath_FontImg[MAX_PATH];//FontImgSetFile
	extern char FileTitle_FontImg[MAX_PATH];
	extern char FilePath_Tag[MAX_PATH];//TagSetFile
	extern char FileTitle_Tag[MAX_PATH];

	extern char FilePath_JoypadAssignment[MAX_PATH];//TagSetFile
	extern char FileTitle_JoypadAssignment[MAX_PATH];

	extern char AppDir[MAX_PATH];//プログラムの直下のパス
	extern char LocalDir[MAX_PATH];
	extern char MsgDir[MAX_PATH];

	extern const char *CursorOverString_p;

////////　構　造　体　の　定　義　////////
	//■エリア
	struct AREACONTROL {//各コントロールに関連付けられるエリア
		struct AREACONTROL* ParentArea_p = NULL;//親エリア（始点と大きさの情報）のポインター
		int Location[2] = { 0 };//コントロールの座標（[0]左端[1]上端）（-111111：１つ前のエリアの終点にくっつける　-222222：１つ前のエリアの始点にそろえる）
		int Margin[4] = { 0 };//周から線までの距離
		int BorderThickness = 0;//枠線の太さ
		int BorderType = 0;
		int Padding[4] = { 0 };//メッセージボックス内でメッセージまでの距離（[0]左パディング[1]上パディング[2]右パディング[3]下パディング）　　直接MessageArea[0]～[3]を指定するのは値を考えづらいから，パディングとして受け取ってここで計算する。	
		int Width = 0;//コントロールの幅
		int Height = 0;//コントロールの高さ
		int BackTransparency = 0;//背景の透過度（%）
		int BackColor = NULL;//背景色のハンドル
		int BorderColor = NULL;//枠線の色
		int Active = 1;//（-１：非表示　０：使用不可状態（ボタンのタイトルを薄く表示して無反応）　１：待機状態（ボタンの表示・反応）　２：ボタンを表示するが無反応）
		//入力パッド（ジョイパッド用）では，ボタンエリアとベースボタンエリアのActiveのリセット時，一方が１で多方は0にするのを忘れないこと

		int Nest[4] = { 0 };//各コントロールの始点と大きさ（x1, y1, 幅，高さ）
		int BackImg = -1;//
		int Line[4] = { 0 };//補助線の始点と終点（コントロールのボックス左上からの位置）
		int Range[4];

	};
	//■リスト
	struct LISTCONTROL {//各コントロールに関連付けられるエリア
		struct BUTTONCONTROL* ParentButton_p = NULL;//親ボタンのポインター
		int BorderThickness = 0;//枠線の太さ
		int Padding[4] = { 0 };//メッセージボックス内でメッセージまでの距離（[0]左パディング[1]上パディング[2]右パディング[3]下パディング）　　直接MessageArea[0]～[3]を指定するのは値を考えづらいから，パディングとして受け取ってここで計算する。	
		int Width = 0;//コントロールの幅
		int Height = 0;//コントロールの高さ
		int BackTransparency = 0;//背景の透過度（%）
		int BackColor;//背景色のハンドル
		int BorderColor;//枠線の色のハンドル
		int CursorColor;//カーソル色のハンドル
		int Active = -1;//（-１：非表示　０：使用不可状態（ボタンのタイトルを薄く表示して無反応）　１：待機状態（ボタンの表示・反応）　２：ボタンを表示するが無反応）
		int RowKosuu = 1;
		int RowPadding[4] = { 0 };
		int RowWidth = 0;
		int RowHeight = 0;

		int Nest[2] = { 0 };//各コントロールの始点と大きさ（x1, y1）

		//入力パッド（ジョイパッド用）では，ボタンエリアとベースボタンエリアのActiveのリセット時，一方が１で多方は0にするのを忘れないこと
	};
	//■リスト
	struct LISTROWCTRL {
		struct LISTCONTROL* List_p = NULL;//親ボタンのポインター
		char Title[50 + 1];
		int Active = 1;
	};
	//■ボタンフォーム
	struct BUTTONFORM {//各コントロールに関連付けられるエリア
		////////////////////
		//デザイン類
		int BorderColor = NULL;//
		int WaitingColor = NULL;//背景色のハンドル（指定しない）
		int CursorColor = NULL;//背景色のハンドル（指定しない）
		int PushedColor = NULL;//背景色のハンドル（指定しない）
		int BackTransparency = 0;//背景の透過度（%）
		//Soundからの相対パスまたはファイル名からロードしたハンドル
		int PushSound = -1;//ボタンプッシュ音　　※ハンドルの取得に失敗時はハンドルが-1でLog.txtに書き込まれる。パスが0やNULLならロードしないのでハンドルは-1となるが，Log.txtに書き込まれない。
		int MoveSound = -1;//ボタン移動音　　　　※ハンドルの取得に失敗時はハンドルが-1でLog.txtに書き込まれる。パスが0やNULLならロードしないのでハンドルは-1となるが，Log.txtに書き込まれない。
		//幅類
		int Margin[4] = { 0 };//周から線までの距離
		int BorderThickness = 0;//枠線の太さ
	};

	//■ボタン
	struct BUTTONCONTROL {//各コントロールに関連付けられるエリア
		struct AREACONTROL* ParentArea_p;//エリア（始点と大きさの情報）のポインター（ロード時はエリアの要素番号でポインターを指定）
		char Title[50 + 1];//ボタン表面に表示する文字列
		char String[50 + 1];//マウスポインターが指したときに表示する文字列
		int DialImg = -1;
		int Location[2] = { 0 };//コントロールの座標（[0]左端[1]上端）（-1：１つ前のエリアの始点にそろえる　-2：１つ前のエリアの終点にくっつける）
		int Padding[4] = { 0 };//線から内容物までの距離（[0]左パディング[1]上パディング[2]右パディング[3]下パディング）	（[0]が-1なら左右センタリング，[1]が-1なら上下センタリング）
		int Active = -1;//（-２：使用不可のカーソル状態（薄く表示して無反応）　-１：非表示　０：使用不可状態（薄く表示して無反応）　１：待機状態（ボタンの表示・反応）　２：押された状態　３：カーソル）
		int Up = 0;
		int Down = 0;
		int Left = 0;
		int Right = 0;
		//ロードしないパラメータ
		int Nest[4] = { 0 };//内容物に引き継ぐ座標（アプリケーションのウィンドウベース）ボタンのネストはboxの部分（マージンは含まない。ペアレントエリアのNestを継承。）
		////////////////////
		struct BUTTONFORM* ButtonForm_p;
		//Imgからの相対パスまたはファイル名からロードしたハンドル
		int CursorImg = -1;//　　※ハンドルの取得に失敗時もハンドルは-1でLog.txtに書き込まれる。パスが-1ならロードしないのでハンドルは-1となるが，Log.txtに書き込まれない。
		int WaitingImg = -1;//　　※ハンドルの取得に失敗時もハンドルは-1でLog.txtに書き込まれる。パスが-1ならロードしないのでハンドルは-1となるが，Log.txtに書き込まれない。
		int PushedImg = -1;//　　※ハンドルの取得に失敗時もハンドルは-1でLog.txtに書き込まれる。パスが-1ならロードしないのでハンドルは-1となるが，Log.txtに書き込まれない。
		int Width = 0;//コントロールの幅
		int Height = 0;//コントロールの高さ
	};
#define INPUTTEXTBUTTON_FIELDSIZE 1500//小問正解の書き込み可能サイズ（\0を含まない）

	//■文字列入力ボタン
	struct INPUTTEXTBUTTONCTRL {
		struct BUTTONCONTROL ButtonCtrl;//ポインターで共有するのではなく，直接BUTTONCONTROLが入る
		char PutText[INPUTTEXTBUTTON_FIELDSIZE + 1]; //入力される文字 　積分なら<se2>*</se2>で12文字　タグは6個　全体で71文字
		int Start;
		int ButtonType;//１：数式　２：その他
	};
	//■パッドマネージャー
	struct PadManager {
		int Active = 1;//１：インデックスエリアとベースボタンエリアのみアクティブ，ActiveElementを0。－１：全エリアを非アクティブ，ActiveElementを-1。（毎回ではなくインデックスエリアの状態により識別して実行）
		int IndexOn = 0;//オンになっているインデックス番号（インデックス０番をオンにする）190609
		int PushedNo = 0;//最後に押されたボタン番号（カーソルの初期位置の設定は，これではなくボタンCSVのActivを3にする）
		int Duration = 0;//ボタンが押された長さ
		struct INPUTTEXTBUTTONCTRL* InputButton_p;
	};
	//■タグ
	struct Tag {
		int TagStyleNo = 0;//{}または;形式のために定義タグを記録する
		int Parent = 0;//親タグの番号　旧oyatagno

		char Name[10 + 1] = { 0 };//タグ要素名
		int Post = 0;//ポスト（１５：改行・折返し禁止のブロック　３：改行禁止のブロック　１：メンバー　０：その他　－１：カラのメンバー）
		int Control = -1;//TagType　　　Tag[0]はClickMojiの代用だからTag[0]=-1
		int Pattern = 0;//線の太さ（ピクセル数）　値が0でないときに線の描画処理を行うlineH
		int ArgX = 0;//枠位置または文字位置からのX方向の位置　文字サイズに対する割合（％）lineX
		int ArgY = 0;//枠位置または文字位置からのｙ方向の位置　文字サイズに対する割合（％）lineY
		int ArgM = 0;//マルチなプロパティMultiple
		int CharSize = 0;//文字のサイズ（発生時，親タグの文字サイズ×CharRate/100として与えられる）旧mojisize
		int Padding[4] = { 0 };//文字サイズに対する割合
		int ToTheHead = 0;//書き出しのツメの有無（ToTheHeadの値　0：親タグの書き終え位置　１：親タグの書き出し位置）
		int ConnectionP = 0;//0：親のCharLocYが結合（親文字結合）　1：親のLocationYが結合（親枠結合）
		int PositionP = 0;//位置（ConnectionPが0なら親タグのCharSizeに対する割合（％）で指定，ConnectionPが1なら親タグのHeightに対する割合（％）で指定）　旧oyamojiidou
		int ConnectionM = 0;//0：自分のCharLocYが結合（子文字結合）　1：自分のLocationYが結合（子枠結合）
		int PositionM = 0;//位置（ConnectionMが0ならCharSizeに対する割合（％）で指定，ConnectionMが1ならHeightに対する割合（％）で指定）　旧komojiidou

		int LocationX = 0;//横方向のタグごとについての文字書き出し位置　旧kakidashi
		int LocationY = 0;//枠の上部の位置　旧wakuichi
		int CharLocY = 0;//縦方向の文字位置（LocationYからの相対位置）　旧mojiichi
		int Width = 0;//幅　旧kakioeをやめにして幅で扱うことにした
		int Height = 0;//枠の縦サイズ（発生時（子タグができるまで）は文字サイズと同じ値）　旧wakutate
		int FirstNumInParsedMsg = 0;//適用開始位置　旧kaishi
		int LastNumInParsedMsg = 0;//適用終了位置　旧syuuryou
		int MemberCount = 0; //メンバータグの出現数。初期値は０。メンバーをもつブロックのみ使用。
		int TagSign = 1;//２の倍数（TagTypeで決まる）：数式（スペースの禁止，<math>の付加）　３の倍数（Postで決まる）：ブロック（改行の禁止，折返しの禁止）//Tag[0].TagSignはActiveTagSignとして代用（-１：タグを読み込まない　１：タグを読み込む　その他の値は各種）
		
	};
	//■メッセージボックスフォーム
	struct MsgBoxForm {
		int MaxLine = -1;//入力可能な最大行数（マイナス（-1）なら行数の制限なし）
		int Margin[4] = { 0 };//メッセージボックス外の距離
		int Padding[4] = { 10, 10, 10, 10 };//メッセージボックス内でメッセージまでの距離（[0]左パディング[1]上パディング[2]右パディング[3]下パディング）	
					   ////
		int BorderColor = GetColor(255, 255, 255);//枠線の色
		int BorderThickness = 4;//枠線の太さ
		int BorderType = 1;
		int BackColor = GetColor(0, 0, 0);//背景色のハンドル（指定しない）
		int BackTransparency = 50;//背景の透過度（%）
		int ActiveTagColor = GetColor(255, 255, 0);//アクティブなタグの色ハンドル（指定しない）
		int ActiveTagColorTransparency = 70;//アクティブなタグの色の透過度（%）
		int ActiveMathColor = GetColor(204, 255, 255);//背景色のハンドル（指定しない）
		int ActiveMathColorTransparency = 80;//背景の透過　アルファブレンディングのパラメータ（値が２５５に近いほど背景が濃く表示される)

		int FontColorRGB[3] = { 255, 255, 255 };//文字色RGB
		int FontColor = GetColor(255, 255, 255);//文字色ハンドル

		int Leading = 5;//行間[18]
		int BlinkSpeed = 120;//カーソルの点滅スピード（１分間に点滅する回数)（[15]）60000の約数がよい。三角カーソルのときはパディング[3]をプラスしておくとよい
		int OutputSpeed = 50;//文字の出力スピード（プラス：１秒間に進む文字数　マイナス：クリックに反応する）1000の約数がよい
							 //つまり（プラス：パカパカあり。カーソルなし。　0：パカパカなし。カーソルなし。　-1：パカパカなし。クリック後からカーソルあり。　-2以下：パカパカなし。元からカーソルあり。）
		int ScrollSpeed = 200;//スクロールのスピード（１秒間にスクロールするピクセル）（[14]）1000の約数がよい
		int Option = 11444;//
		//Soundからの相対パスまたはファイル名（ただしエディターでは相対パスが入る仕様）でからロードしたハンドル
		int MessageSound = -1;//メッセージ音（パカパカ音，メッセージカーソルのジャンプ音，メッセージカーソルの移動音）
		int ConfirmSound = -1;//確定音（フレーズ書き終え状態，ウィンドウが満杯の状態のときにボタンを押した音。入力の確定音）
		int BackDelSound = -1;//バックスペース・デリート音
		/*
		下１桁目　０：左流れ　１：上り　２：右流れ　３：下り　５：ジョイパッド　それ以外（４）：スクロールなし
		下２桁目　０：左端　１：上端　２：右端　３：下端　それ以外（４）：ボックス左上
		下３桁目　左か右流れで０：左寄せ　上りまたは下りで１：上寄せ　左または右流れで２：右寄せ　上りか下りで３：下寄せ　４：自動　５：ループ　それ以外（6）：通過（上りで左寄せを指定した場合なども通過となる）
		下４桁目　０：折り返しなし（MaxLineは無効になる）　１：折り返しあり　２：折り返しあり（わかち）
		下５桁目　ボックス下端　０：指定した高さ　１（0より大きく2，3を除く）：表示後のメッセージ下端　２：表示中のメッセージ下端　３：表示中のメッセージ下端（Heightの値も変化）※３はパカパカにはあるがスクロールにはない（スクロールでは１と同じになる）
		*/
	};
	//■メッセージボックスフォーム2（RGB，ファイルパス）※エディターで使用
	struct MsgBoxForm_RGB_SoundPath {
		int BorderColorRGB[3] = { 255, 255, 255 };//枠線の色
		int BackColorRGB[3] = { 0, 0, 0 };//背景色のハンドル（指定しない）
		int ActiveTagColorRGB[3] = { 255, 255, 0 };//背景色のハンドル（指定しない）
		int ActiveMathColorRGB[3] = { 204, 255, 255 };//背景色のハンドル（指定しない）
		//Soundからの相対パスまたはファイル名（ただしエディターでは相対パスが入る仕様）
		char MessageSoundPath[MAX_PATH] = { 0 };//メッセージ音のパス（パカパカの音　ジャンプ音）
		char ConfirmSoundPath[MAX_PATH] = { 0 };//確定音のパス（フレーズ書き終え状態，ウィンドウが満杯の状態のときにボタンを押した音。入力の確定音）
		char BackDelSoundPath[MAX_PATH] = { 0 };//バックスペース・デリートの音のパス
	};
	//■メッセージボックス
#define Tag_Max 300//（メンバーにTagを持っているから最大値を定義しておく必要がある）
	struct MsgBoxCtrl {
		struct AREACONTROL* ParentArea_p = NULL;//エリア（始点と大きさの情報）のポインター
		struct MsgBoxForm* MsgBoxForm_p = NULL;//フォーム（始点と大きさの情報）のポインター（ロード時はフォームの要素番号MsgBoxFormNumberでポインターを指定）

		int Location[2] = { 0,0 };//コントロールの座標（[0]左端[1]上端）
		int Width = 800;//コントロールの幅
		int Height = 96;//コントロールの高さ（高さ伸縮タイプではメッセージの高さから算出。ただしタイプ105（スクロールありの高さ伸縮でメッセージボックス下り)のときは領域内のメッセージの高さから算出。）
		int OuterWidth = 0;//マージンを含む幅（指定しない）
		int OuterHeight = 0;//マージンを含む高さ（指定しない）
		int MessWidth = 0;//メッセージの高さ（コントロールの下端までの余ったスペースは含まない）
		int MessHeight = 0;//メッセージの高さ（コントロールの下端までの余ったスペースは含まない）
		int ActiveLetterSize = 0;//入力に関するアクティブな文字のサイズ（[11]）
		int ActiveLetterX = 0;//入力に関するアクティブな文字の位置X（[16]）
		int ActiveLetterY = 0;//入力に関するアクティブな文字の位置Y（[17]）
		struct Tag Tag[Tag_Max];//タグの初期化（ローカル変数） = { 0 }
		char ParsedMsg[2000] = { "\0" };//タグを抜き取った文字列を入れる配列

		//以下は，ClearMsgBox関数でリセットされるもの（※Tag[0].TagSign，Tag[0].ConnectionPもClearMsgBox関数でリセットされる）
		int Condition = 1;//
		int StartingPointX = 0;//メッセージの全体の位置（ウィンドウベースの位置。縦スクロールを含まない）
		int StartingPointY = 0;//メッセージの全体の位置（ウィンドウベースの位置。横スクロールを含まない）




		int MessX = 0;//メッセージ全体の書き出し位置（ウィンドウベースの位置。横スクロールを含む）（StartingPointX + 横スクロール累積値）
		int MessY = 0;//メッセージ全体の書き出し位置（ウィンドウベースの位置。縦スクロールを含む）（StartingPointY + 縦スクロール累積値）
		int Stale = 0;//古くなってScrollTankに渡すことができる高さ
		int ScrollTank = 0;//スクロールできる総量
		int ScrollOne = 0;//１回のスクロール量の端数の累積（この値で１回のスクロール量と次の端数を算出）
		int PhraseOn = 0;//書き出し可能フレーズ番号（フレーズ書き終え後のボタンを押した数）（[8]）


		int WaitTank = 0;//残りの待機フレーム数[20]
		//int RemainWaitTime = 0;//残りの待機ミリ秒数
		int WaitedFlame = 0;//待機したフレーム数[21]
		int KakidashiLineMax = 0;//最大行番号（[7]）　　誤って指定したら途中からパカパカが始まるのかな？？？
		int KakidashiTagMax = 0;//出てきたｉの現時点での最大タグ番号

		int Switch = 0;//スイッチ（[22]）

		int NonEnterable = 0;
		//int Time = -1;
		//int ElapsedTime = 0;

		/*状態 Condition
		//↓Conditionの0番は，文字書き出しループの条件が（Condition != 0）になっているだけだから不要？？？
		0:書き出し不可																//ElapsedTimeが進む（10より小さい）//スクロールする（3以下）
		1:書き出し可（初めて書き出す行の先頭）										//ElapsedTimeが進む（10より小さい）//スクロールする（3以下）
		2:書き出し可（初めて書き出す行の先頭ではない）								//ElapsedTimeが進む（10より小さい）//スクロールする（3以下）
		3:終端文字まで進んだ//旧8													//ElapsedTimeが進む（10より小さい）//スクロールする（3以下）

		4:最終位置までスクロールした（ただし終端文字まで書き出し済みのとき）//旧6	//ElapsedTimeが進む（10より小さい）
		5:終端文字まで書き出した後にボタン押した//旧7								//ElapsedTimeが進む（10より小さい）

		11:フレーズ書き終え//旧3
		12:ウィンドーが満杯//旧4
		13:書く文字数だけ止める//旧5
		/////////////////////
		101：確定したことを示す（入力時のカーソルが最後まですすんだとき。確定ボタンを押したときは関係ないと思う）
		102：次のカーソル位置に進んだとき
		103：次のカーソル位置に進んだとき
		*/
	};

	//■課題
//#define Kadai_MonsterIdSize 5//大問の書き込み可能サイズ（\0を含まない）
//#define KADAI_SYOUMONSEIKAIMAX 50//小問数の最大
#define DAIMON_FIELDSIZE 1000//大問の書き込み可能サイズ（\0を含まない）
#define DAIMONSEIKAI_FIELDSIZE 200//大問正解の書き込み可能サイズ（\0を含まない）
#define SYOUMON_MAX 50//小問数の最大
#define SYOUMON_FIELDSIZE 1000//小問の書き込み可能サイズ（\0を含まない）
#define SYOUMONSEIKAI_FIELDSIZE 200//小問正解の書き込み可能サイズ（\0を含まない）
	struct Kadai {
		int monsterID = 0;//5桁＋終端
		char daimon[DAIMON_FIELDSIZE + 1] = { "<p></p>" }; //大問文が入る
		char daimonseikai[DAIMONSEIKAI_FIELDSIZE + 1] = { "<math></math>" }; //大問正解が入る
		char syoumon[SYOUMON_MAX + 1][SYOUMON_FIELDSIZE + 1] = { 0 }; //小問文が入る　[小問数50　（＋１はコピー用バッファ）] [1バイト文字1000字まで]
		char syoumonseikai[SYOUMON_MAX + 1][SYOUMONSEIKAI_FIELDSIZE + 1] = { 0 }; //小問正解が入る　[小問正解数50　（＋１はコピー用バッファ　使っているかどうか不明] [1バイト文字200字まで]
	};

	//■モンスター
#define MONSTERNAME_FIELDSISE 30//モンスター名の最大バイト数（配列サイズは＋１）
#define MONSTER_COLUMNMAX 20//カラム（属性）の個数
#define MONSTER_COLUMNTITLEFIELDMAX 8//コラムタイトルの文字数（配列サイズは＋１）
	struct Monster {
		char Name[MONSTERNAME_FIELDSISE + 1] = { 0 };//モンスター名
		int Img = -1;//モンスターの画像ハンドル
		int Column[MONSTER_COLUMNMAX] = { 0 };//カラム（//モンスターID//攻撃力//攻撃周期//魔力スピード//問題の制限フレーム数//魔法ID//魔法数値（魔法のタイミングに使う変数）//獲得可能経験値//獲得可能コイン）
	};

////////　関　数　////////
	//■フレームレートの変更
	int ChangeFPS(int Rate);
	//■早すぎたら待機
	int SleepToFitFPS(int FPS);
	//■瞬間フレームレートの測定（Nフレームごとの瞬間）
	float MeasureInstantFPS(int N);
	//■平均フレームレートの測定（Nフレームの平均値）
	float MeasureAverageFPS(int N);
	//■マウスの入力状態
	int MathgpUpdateMouse();
	//■全てのキーの入力状態（押されたフレーム数）を更新する関数
	int MathgpUpdateKey();
	//■ジョイパッドの入力状態を更新
	int MathgpUpdateJoypad();
	//int UpdateMath(int Number);
	//■エリアセットのロードと設定（ロードした値を元に各パラメータの値を決定する）
	int LoadAreaSet(const char *FilePath_h, struct AREACONTROL *AreaSet_h, int *AreaKosuu_p, int AreaMax, struct AREACONTROL *ParentArea_p);
	//■フォントセットのロードとフォントハンドルの作成
	int LoadFontSet(const char* FilePath_h);
	//■画像セットのロードと画像ハンドルの作成
	int LoadFontImgSet(const char* FilePath_h);
	//■タグセットのロード
	int LoadTagSet(const char* FilePath_h);
	//■ジョイパッドの設定のロード
	int LoadJoypadSettings(const char* FilePath_h);

	//■設定のロード（フォント，フォント画像，タグ設定のロード）（0：成功　-1：失敗）//※終了時はルートディレクトリ
	int LoadFontTagSettings(const char* FilePath_h);
	//■メッセージボックスフォームのロード
	int LoadMsgBoxForm(const char* FilePath_h, struct MsgBoxForm* MsgBoxForm_p, const int MsgBoxForm_Kosuu);
	//■メッセージボックスフォームの画像パス，RGBのロード
	int LoadMsgBoxForm_RGB_SoundPath(const char* FilePath_h, struct MsgBoxForm_RGB_SoundPath *MsgBoxForm_RGB_SoundPath_p, const int MsgBoxForm_Kosuu);
	//■メッセージボックスコントロールのロード
	int LoadMsgBoxCtrl(const char* FilePath_h, struct MsgBoxCtrl* MsgBoxCtrl_p, const int MsgBoxCtrl_Kosuu, struct MsgBoxForm* MsgBoxForm_p, const int MsgBoxForm_Kosuu);
	//■メッセージのロード
	int LoadMsg(const char* FilePath_h, char *Msg_h, int MsgSize, int GetDirFlag);
	//■メッセージ付属ファイルのロード（LocalDirからの相対パスで，フォーム，コントロール，フォント・タグ設定をまとめてロード）
	int LoadMsgSet(const char *Directry_h, struct MsgBoxForm* MsgBoxForm_p, int MsgBoxForm_Kosuu, struct MsgBoxCtrl* MsgBoxCtrl_p, int MsgBoxCtrl_Kosuu, int FontTagSettingsFlag, int JoypadSettingsFlag);

	//●モンスターのロード
	int LoadMonster(const char* FilePath_h, struct Monster *Monster_p, int Monster_Max, int *Monster_Kosuu, int *IssuedMoonsterID_p, char(*columntitle)[MONSTER_COLUMNTITLEFIELDMAX + 1], int* Column_Kosuu);//char(*MonsterImgPath_h)[MAX_PATH], 
	//●モンスター画像パスのロード
	int LoadMonsterImgPath(const char* FilePath_h, char(*MonsterImgPath_h)[MAX_PATH], int Monster_Max);
	//●問題のロード
	int LoadMondai(const char* FilePath_h, struct Kadai* mondai, int *Syoumonkosuu_p, int GetDirFlag);
	//●問題付属ファイルのロード（LocalDirからの相対パスで，フォーム，コントロール，フォント・タグ設定，モンスターをまとめてロード）
	int LoadMondaiSet(const char *Dir_h, struct MsgBoxForm* MsgBoxForm_p, int MsgBoxForm_Kosuu, struct MsgBoxCtrl* MsgBoxCtrl_p, int MsgBoxCtrl_Kosuu,
		struct Monster *Monster_p, int Monster_Max, int *Monster_Kosuu, int *IssuedMoonsterID_p, char(*ColumnTitle)[MONSTER_COLUMNTITLEFIELDMAX + 1], int* Column_Kosuu, int FontTagSettingsFlag, int JoypadSettingsFlag
	);//int *IssuedMoonsterID_pは発行済み最大ID（エディターで使用）
	//■ジョイパッドの割り当てのロード
	int LoadJoypadAssignment(const char *FilePath_JoypadAssignment_h, int *FromActionToJoypad);
	//■ボタンフォームセットのロード
	int LoadButtonFormSet(const char *FilePath_h, struct BUTTONFORM *ButtonFormSet_p, int *ButtonFormKosuu_p, int ButtonFormMax);
	//■ボタンセット（１グループ）のロード（0：成功　-1：失敗（ファイル名が存在しない，引数のポインターがNULL）　-2：ボタンの配列要素数が足りない）
	//int LoadButtonSet(const char *FilePath_h, struct BUTTONCONTROL *ButtonSet_h, int *ButtonKosuu_p, int ButtonMax, struct AREACONTROL *ButtonAreaSet_h, struct BUTTONFORM *ButtonFormSet_h);
	//■ボタンセット（複数グループ）のロード（0：成功　-1：失敗（ファイル名が存在しない，引数のポインターがNULL）　-2：ボタンの配列要素数が足りない）
	int LoadButtonSetEx(const char *FilePath_h, struct BUTTONCONTROL **ButtonSet_ph, int *ButtonKosuu_p, const int *ButtonMax_h, int ButtonSetKosuu, struct AREACONTROL *ButtonAreaSet_h, struct BUTTONFORM *ButtonFormSet_h);
	//■テキスト入力ボタンセットのロード（１グループ）のロード（0：成功　-1：失敗（ファイル名が存在しない，引数のポインターがNULL）　-2：ボタンの配列要素数が足りない）
//	int LoadInputTextButtonSet(const char *FilePath_h, struct INPUTTEXTBUTTONCTRL *ButtonSet_h, int *ButtonKosuu_p, int ButtonMax, struct AREACONTROL *ButtonAreaSet_h, struct BUTTONFORM *ButtonFormSet_h);
	//■テキスト入力ボタンセットのロード（複数グループ）のロード（0：成功　-1：失敗（ファイル名が存在しない，引数のポインターがNULL）　-2：ボタンの配列要素数が足りない）
	int LoadInputTextButtonSetEx(const char *FilePath_h, struct INPUTTEXTBUTTONCTRL **ButtonSet_ph, int *ButtonKosuu_h, const int *ButtonMax_h, int IndexKosuu, struct AREACONTROL *ButtonAreaSet_h, struct BUTTONFORM *ButtonFormSet_h);
	//■パッド・パッド付属ファイルのロード
	int LoadPad(const char *FilePath_AreaSet_h, struct AREACONTROL *PadAreaSet_h, int* PadAreaKosuu_p, int PadAreaMax, struct AREACONTROL *ParentArea_p,
		struct BUTTONFORM *ButtonFormSet_h, int *ButtonFormKosuu_p, int ButtonFormMax,
		struct BUTTONCONTROL *IndexSet_h, int *IndexKosuu_p, int IndexMax,
		struct INPUTTEXTBUTTONCTRL **ButtonSet_ph, int *ButtonKosuu_h, const int *ButtonMax_h,
		struct INPUTTEXTBUTTONCTRL *BaseButtonSet_h, int *BaseButtonKosuu_p, int BaseButtonMax,
		char *Msg_h, int MsgSize, int GetDirFlag, struct MsgBoxForm *MsgBoxForm_p, int MsgBoxFormKosuu, struct MsgBoxCtrl *MsgBoxCtrl_p, int MsgBoxCtrlKosuu, int FontTagSettingsFlag, int JoypadSettingsFlag
	);
	//■ファイルパスからファイル名を取得
	int GetTitleFromPath(char* path_h, char* title_h);
	//■ファイルパスからディレクトリを取得（エディターでは現状使っていない）
	int GetDirFromPath(char* dir_h, const char* path_h);
	//■ローカルディレクトリ，メッセージディレクトリのパスの取得
	int SetLocalDirMsgDirFromMsgPath(const char *FilePath_h);

	//■カーソルオーバー
	int Math_CursorOver(const int LocationX, const int LocationY, const int Padding, const int StringColor, const int BackColor, const int Type);
	//■マルチガイド
	int MultiGuide();
	//■オーバーラップ　追加する領域を受け取って，元の描画可能領域および，元の描画可能領域と重複した領域を取得する（重複した領域NewRange　追加する領域AddRange）
	int Overlap(int *NewRange, const int *AddRange);
	//■画像の上下位置の変更
	int ChangeImgAlign(char *Msg_h, struct MsgBoxCtrl *MsgBoxCtrl_p);
	//■メッセージボックスの高さの初期値表示
	int ShowHeightGauge(struct MsgBoxCtrl* MsgBoxCtrl, int MasterHeight, int Color);

	//■エリアの表示
	int ShowArea(struct AREACONTROL *AreaSet_h, int AreaKosuu);
	//■タグを読み取る関数
	int ReadMathTag(const char *Msg_h, struct Tag *Tag, int TagMax, char *ParsedMsg_h, const int *FontColorRGB);
	//■タグの再読み込み指示（DrawMsg用）
	int ReparseTag(struct Tag *Tag);
	//■タグの再読み込み指示
	int Reparse(struct MsgBoxCtrl *MsgBoxCtrl_p);
	//■アクティブ要素の非アクティブ化（ActiveElementを-1）
	int EraseActiveElement(struct MsgBoxCtrl *MsgBox_p);
	//■アクティブ要素の取得（ActiveElementを0）
	int GetActiveElement(struct MsgBoxCtrl *MsgBox_p);

	//■メッセージボックスのリセット
	int ClearMsgBox(struct MsgBoxCtrl *MsgBox_p);

	//■メッセージボックスの表示
	int ShowMsgBox(const char *Msg_h, struct MsgBoxCtrl *MsgBoxCtrl_p);
	//■ボタン
	int ShowButton(struct BUTTONCONTROL *Button_h, int ButtonKosuu, int *PushedNo_p, int PushType, int Prev, int Next);
	//■テキストボタン
	int ShowTextButton(char *Msg_h, struct MsgBoxCtrl *MsgBoxCtrl_p, int MsgSize, struct INPUTTEXTBUTTONCTRL *TextButton_h, int ButtonKosuu, int *PushedNo_p, int PushType, int Prev, int Next);
	//■リストの表示
	int ShowList(struct LISTCONTROL *ListCtrl_p);

	//■メッセージのキーボード入力（キーボードから数式を入力するための関数）
	int InputMsgKey(char *Msg_p, struct MsgBoxCtrl *MsgBoxCtrl_p, int MsgSize, int *InputHandle);
	//■メッセージのジョイパッド操作
	int OperateMsgJoypad(char *Msg_h, struct MsgBoxCtrl *MsgBoxCtrl_p, int MsgSize);
	//■パッド（マウス操作）
	int ShowPadM(char *Msg_h, struct MsgBoxCtrl *MsgBoxCtrl_p, int MsgSize, int *InputHandle_p, int ShowMsgBoxFlag,
		struct BUTTONCONTROL *Index_h, int IndexKosuu,
		struct INPUTTEXTBUTTONCTRL **Button_ph, const int *ButtonKosuu_h,
		struct INPUTTEXTBUTTONCTRL *BaseButton_h, int BaseButtonKosuu,
		struct AREACONTROL *AreaSet_h, struct PadManager *PadManager_p
	);
	//■パッド（ジョイパッド操作）
	int ShowPadJ(char *Msg_h, struct MsgBoxCtrl *MsgBoxCtrl_p, int MsgSize, int ShowMsgBoxFlag,
		struct BUTTONCONTROL *IndexSet_h, int IndexKosuu,
		struct INPUTTEXTBUTTONCTRL **ButtonSet_ph, const int *ButtonKosuu_h,
		struct INPUTTEXTBUTTONCTRL *BaseButtonSet_h, int BaseButtonKosuu,
		struct AREACONTROL *PadAreaSet_h, struct PadManager *PadManager_p
	);


	//■シンプル出力（数式＋フレームワーク）　（メッセージボックスコントロール不要）
	int DrawMsg(int LocationX, int LocationY, const char *Msg_p, int *FontColorRGB, int FontColorHandle, const struct AREACONTROL *ParentArea_p, int TagHairetsuMax, struct Tag *Tag, char *ParsedMsg_p);//シンプルモード
	//■幅の取得
	int GetWidthForDrawMsg_S(const char *Msg_p, int *Width, int *Height, int *TagMax);
	//■DrawString＋フレームワーク
	int DrawStringInArea(int LocationX, int LocationY, const struct AREACONTROL *ParentArea_p, const char *String_p, int Color);
	//■DrawFormatString＋フレームワーク
	int DrawFormatStringInArea(int LocationX, int LocationY, const struct AREACONTROL *ParentArea_p, int Color, const char *String_p, ...);

	//int ActiveMath_Init();
}//namespace ActiveMathの終了

using namespace ActiveMath;


