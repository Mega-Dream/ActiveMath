#pragma once
////////////
#define _CRT_SECURE_NO_WARNINGS//strcpyのバッファオーバーの警告を止めるためにある。

#include "DxLib.h"
//#include <string.h>//文字列用
//#include <stdlib.h>//終了時のexit()関数が入っている itoa関数（intからcharへの変換）

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
#define Act_BtnCursorDown 15
#define Act_BtnCursorLeft 16
#define Act_BtnCursorRight 17
#define Act_BtnCursorUp 18
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
	extern int Action[ActMax];

	extern int SystemFontSize;

	////////////////////////////

	extern char Dir_FontStyle[MAX_PATH];//フォントスタイルのディレクトリ
	extern char Dir_FontStyle_rw[MAX_PATH];//フォントスタイルのディレクトリ
	extern char Title_FontStyle[MAX_PATH];//フォントスタイルのファイル名
	extern char Title_FontStyle_rw[MAX_PATH];//フォントスタイルのファイル名

	extern char Dir_FontImgStyle[MAX_PATH];//フォント画像スタイルのディレクトリ
	extern char Dir_FontImgStyle_rw[MAX_PATH];//フォント画像スタイルのディレクトリ
	extern char Title_FontImgStyle[MAX_PATH];//フォント画像スタイルのファイル名
	extern char Title_FontImgStyle_rw[MAX_PATH];//フォント画像スタイルのファイル名

	extern char Dir_TagStyle[MAX_PATH];//タグスタイルのディレクトリ
	extern char Dir_TagStyle_rw[MAX_PATH];//タグスタイルのディレクトリ
	extern char Title_TagStyle[MAX_PATH];//タグスタイルのファイル名
	extern char Title_TagStyle_rw[MAX_PATH];//タグスタイルのファイル名

	extern char Dir_AppImg[MAX_PATH];//アプリ共有画像のディレクトリ
	extern char Dir_AppImg_rw[MAX_PATH];//アプリ共有画像のディレクトリ
	extern char Dir_AppSound[MAX_PATH];//アプリ共有音声のディレクトリ
	extern char Dir_AppSound_rw[MAX_PATH];//アプリ共有音声のディレクトリ

	/////////////////////////////////////////////////////////////////////

	extern char Dir_JoypadStyle[MAX_PATH];//ジョイパッドスタイルのディレクトリ
	extern char Dir_JoypadStyle_rw[MAX_PATH];//ジョイパッドスタイルのディレクトリ
	extern char Title_JoypadStyle[MAX_PATH];//ジョイパッドスタイルのファイル名
	extern char Title_JoypadStyle_rw[MAX_PATH];//ジョイパッドスタイルのファイル名

	/////////////////////////////////////////////////////////////////////
	extern char AppDir[MAX_PATH];//プログラムの直下のパス
	extern char LocalDir[MAX_PATH];
	extern char MsgDir[MAX_PATH];

	extern const char *CursorOverString_p;

////////　構　造　体　の　定　義　////////
	//■エリア
	struct AREA_CTRL {//各コントロールに関連付けられるエリア
		struct AREA_CTRL *ParentArea_p = NULL;//親エリア（始点と大きさの情報）のポインター
		int Location[2] = { 0 };//コントロールの座標（[0]左端[1]上端）（-111111：１つ前のエリアの終点にくっつける　-222222：１つ前のエリアの始点にそろえる）
		int Margin[4] = { 0 };//周から線までの距離
		int BorderThickness = 0;//枠線の太さ
		int BorderType = 0;
		int Padding[4] = { 0 };//メッセージボックス内でメッセージまでの距離（[0]左パディング[1]上パディング[2]右パディング[3]下パディング）	
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
	struct LIST_CTRL {//各コントロールに関連付けられるエリア
		struct BTN_CTRL *ParentBtn_p = NULL;//親ボタンのポインター
		int BorderThickness = 0;//枠線の太さ
		int Padding[4] = { 0 };//メッセージボックス内でメッセージまでの距離（[0]左パディング[1]上パディング[2]右パディング[3]下パディング）	
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
	struct LISTROW_CTRL {
		struct LIST_CTRL *List_p = NULL;//親ボタンのポインター
		char Title[50 + 1];
		int Active = 1;
	};
	//■ボタンフォーム
	struct BTN_FORM {//各コントロールに関連付けられるエリア
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
	struct BTN_CTRL {//各コントロールに関連付けられるエリア
		struct AREA_CTRL *ParentArea_p;//エリア（始点と大きさの情報）のポインター（ロード時はエリアの要素番号でポインターを指定）
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
		struct BTN_FORM *BtnForm_p;
		//Imgからの相対パスまたはファイル名からロードしたハンドル
		int CursorImg = -1;//　　※ハンドルの取得に失敗時もハンドルは-1でLog.txtに書き込まれる。パスが-1ならロードしないのでハンドルは-1となるが，Log.txtに書き込まれない。
		int WaitingImg = -1;//　　※ハンドルの取得に失敗時もハンドルは-1でLog.txtに書き込まれる。パスが-1ならロードしないのでハンドルは-1となるが，Log.txtに書き込まれない。
		int PushedImg = -1;//　　※ハンドルの取得に失敗時もハンドルは-1でLog.txtに書き込まれる。パスが-1ならロードしないのでハンドルは-1となるが，Log.txtに書き込まれない。
		int Width = 0;//コントロールの幅
		int Height = 0;//コントロールの高さ
	};
#define INPUTTEXTBUTTON_FIELDSIZE 1500//小問正解の書き込み可能サイズ（\0を含まない）

	//■文字列入力ボタン
	struct INPUT_TEXT_BTN_CTRL {
		struct BTN_CTRL Btn;//ポインターで共有するのではなく，直接BTN_CTRLが入る
		char PutText[INPUTTEXTBUTTON_FIELDSIZE + 1]; //入力される文字 　積分なら<se2>*</se2>で12文字　タグは6個　全体で71文字
		int Start;
		int BtnType;//１：数式　２：その他
	};
	//■タグ
	struct TAG {
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
		//ReadMathTag内のみで使用
		int WakukaraKotag;//子タグが親枠結合であることを示す。子タグから指定される（ConnectionP==1のときに親タグのwakukarakotagの値が１となる）　１：ターン処理（ファイルへの読み書きは不要）　累乗，下付き文字，積分後，リスト類，テーブル類，noc（順列・組合せ類）
	};
	//■メッセージボックスフォーム
	struct MSG_BOX_FORM {
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
		int MsgSound = -1;//メッセージ音（パカパカ音，メッセージカーソルのジャンプ音，メッセージカーソルの移動音）
		int ConfirmSound = -1;//確定音（フレーズ書き終え状態，ウィンドウが満杯の状態のときにボタンを押した音。入力の確定音）
		int BackDelSound = -1;//バックスペース・デリート音，フォームが出る音
		/*
		下１桁目　０：左流れ　１：上り　２：右流れ　３：下り　５：ジョイパッド　それ以外（４）：スクロールなし
		下２桁目　０：左端　１：上端　２：右端　３：下端　それ以外（４）：ボックス左上
		下３桁目　左か右流れで０：左寄せ　上りまたは下りで１：上寄せ　左または右流れで２：右寄せ　上りか下りで３：下寄せ　４：自動　５：ループ　それ以外（6）：通過（上りで左寄せを指定した場合なども通過となる）
		下４桁目　０：折り返しなし（MaxLineは無効になる）　１：折り返しあり　２：折り返しあり（わかち）
		下５桁目　ボックス下端　０：指定した高さ　１（0より大きく2，3を除く）：表示後のメッセージ下端　２：表示中のメッセージ下端　３：表示中のメッセージ下端（Heightの値も変化）※３はパカパカにはあるがスクロールにはない（スクロールでは１と同じになる）
		*/
	};
	//■メッセージボックスフォーム2（RGB，ファイルパス）※エディターで使用
	struct MSG_BOX_RGB_SOUNDPATH {
		int BorderColorRGB[3] = { 255, 255, 255 };//枠線の色
		int BackColorRGB[3] = { 0, 0, 0 };//背景色のハンドル（指定しない）
		int ActiveTagColorRGB[3] = { 255, 255, 0 };//背景色のハンドル（指定しない）
		int ActiveMathColorRGB[3] = { 204, 255, 255 };//背景色のハンドル（指定しない）
		//Soundからの相対パスまたはファイル名（ただしエディターでは相対パスが入る仕様）
		char MsgSoundPath[MAX_PATH] = { 0 };//メッセージ音のパス（パカパカの音　ジャンプ音）
		char ConfirmSoundPath[MAX_PATH] = { 0 };//確定音のパス（フレーズ書き終え状態，ウィンドウが満杯の状態のときにボタンを押した音。入力の確定音）
		char BackDelSoundPath[MAX_PATH] = { 0 };//バックスペース・デリートの音のパス
	};
	//■メッセージボックス
#define TAG_MAX_for_MSG_BOX_CTRL 300//（メンバーにTagを持っているから最大値を定義しておく必要がある）
	struct MSG_BOX_CTRL {
		struct AREA_CTRL *ParentArea_p = NULL;//エリア（始点と大きさの情報）のポインター
		struct MSG_BOX_FORM *MsgBoxForm_p = NULL;//フォーム（始点と大きさの情報）のポインター（ロード時はフォームの要素番号MsgBoxFormNumberでポインターを指定）

		int Location[2] = { 0,0 };//コントロールの座標（[0]左端[1]上端）
		int Width = 600;//コントロールの幅
		int Height = 250;//コントロールの高さ（高さ伸縮タイプではメッセージの高さから算出。ただしタイプ105（スクロールありの高さ伸縮でメッセージボックス下り)のときは領域内のメッセージの高さから算出。）
		int OuterWidth = 600;//マージンを含む幅（指定しない）
		int OuterHeight = 250;//マージンを含む高さ（指定しない）
		int MsgWidth = 0;//メッセージの高さ（コントロールの下端までの余ったスペースは含まない）
		int MsgHeight = 0;//メッセージの高さ（コントロールの下端までの余ったスペースは含まない）
		int ActiveLetterSize = 0;//入力に関するアクティブな文字のサイズ（[11]）
		int ActiveLetterX = 0;//入力に関するアクティブな文字の位置X（[16]）
		int ActiveLetterY = 0;//入力に関するアクティブな文字の位置Y（[17]）
		struct TAG Tag[TAG_MAX_for_MSG_BOX_CTRL + 1];//タグの初期化（ローカル変数） = { 0 }//プラス１はTag[0]の分
		char ParsedMsg[2000] = { "\0" };//タグを抜き取った文字列を入れる配列

		//以下は，ClearMsgBox関数でリセットされるもの（※Tag[0].TagSign，Tag[0].ConnectionPもClearMsgBox関数でリセットされる）
		int Condition = 1;//
		int StartingPointX = 0;//メッセージの全体の位置（ウィンドウベースの位置。縦スクロールを含まない）
		int StartingPointY = 0;//メッセージの全体の位置（ウィンドウベースの位置。横スクロールを含まない）




		int MsgX = 0;//メッセージ全体の書き出し位置（ウィンドウベースの位置。横スクロールを含む）（StartingPointX + 横スクロール累積値）
		int MsgY = 0;//メッセージ全体の書き出し位置（ウィンドウベースの位置。縦スクロールを含む）（StartingPointY + 縦スクロール累積値）
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
		int ShowMsgBoxFlag = 1;//０メッセージボックスを書き出さない　１：メッセージボックスを書き出す
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
	//■課題
	struct MONDAI_CTRL {
		int monsterID = 0;//5桁＋終端
		char daimon[DAIMON_FIELDSIZE + 1] = { "<p></p>" }; //大問文が入る
		char daimonseikai[DAIMONSEIKAI_FIELDSIZE + 1] = { "<math></math>" }; //大問正解が入る
		char syoumon[SYOUMON_MAX + 1][SYOUMON_FIELDSIZE + 1] = { 0 }; //小問文が入る　[小問数50　（＋１はコピー用バッファ）] [1バイト文字1000字まで]
		char syoumonseikai[SYOUMON_MAX + 1][SYOUMONSEIKAI_FIELDSIZE + 1] = { 0 }; //小問正解が入る　[小問正解数50　（＋１はコピー用バッファ　使っているかどうか不明] [1バイト文字200字まで]
	};
	//■ディスプレイパッド
	struct DISPLAY_PAD_CTRL {
		int Area_Kosuu;//
		struct AREA_CTRL *Area_h;
		int BtnForm_Kosuu;//
		struct BTN_FORM *BtnForm_h;
		int Index_Kosuu;
		struct BTN_CTRL *Index_h;
		int *Btn_Kosuu_h;
		struct INPUT_TEXT_BTN_CTRL **Btn_hh;
		int BaseBtn_Kosuu;
		struct INPUT_TEXT_BTN_CTRL *BaseBtn_h;
		int MsgSize;
		char *Msg_h;
		struct MSG_BOX_FORM *MsgBoxForm_p;
		struct MSG_BOX_CTRL *MsgBox_p;
		int InputHandle;
		int Active = 1;//１：インデックスエリアとベースボタンエリアのみアクティブ，ActiveElementを0。－１：全エリアを非アクティブ，ActiveElementを-1。（毎回ではなくインデックスエリアの状態により識別して実行）
		int IndexOn = 0;//オンになっているインデックス番号（インデックス０番をオンにする）190609
		int PushedNo = 0;//最後に押されたボタン番号（カーソルの初期位置の設定は，これではなくボタンCSVのActivを3にする）
		int Duration = 0;//ボタンが押された長さ
		struct INPUT_TEXT_BTN_CTRL *ActiveBtn_h;
	};
	//■モンスター
#define MONSTERNAME_FIELDSISE 30//モンスター名の最大バイト数（配列サイズは＋１）
#define MONSTER_COLUMNMAX 20//カラム（属性）の個数
#define MONSTER_COLUMNTITLEFIELDMAX 8//コラムタイトルの文字数（配列サイズは＋１）
	struct MONSTER_CTRL {
		char Name[MONSTERNAME_FIELDSISE + 1] = { 0 };//モンスター名
		int Img = -1;//モンスターの画像ハンドル
		int Column[MONSTER_COLUMNMAX] = { 0 };//カラム（//モンスターID//攻撃力//攻撃周期//魔力スピード//問題の制限フレーム数//魔法ID//魔法数値（魔法のタイミングに使う変数）//獲得可能経験値//獲得可能コイン）
	};
	//■メッセージのロード用変数
	struct LOAD_MSG_SP {
		const char *FilePath_h = NULL;
		char *Msg_h = NULL;
		int MsgSize = 10000;
		const char *Dir_h = NULL;
		struct MSG_BOX_FORM *MsgBoxForm_p;
		struct MSG_BOX_CTRL *MsgBox_p;
		int GetDirFlag = 1;//LoadMsgでMsgDir，LoadMsgBoxSetでLocalDirを取得
		int MsgCodeLinkFlag = 1;
		int JoypadLinkFlag = 1;
	};
	//■問題のロード用変数
	struct LOAD_MONDAI_SP {
		const char *FilePath_h = NULL;
		struct MONDAI_CTRL *Mondai_h = NULL;
		int *Syoumon_Kosuu_p;
		const char *Dir_h = NULL;
		int MsgBoxForm_Max = 1;
		struct MSG_BOX_FORM *MsgBoxForm_p;
		int MsgBox_Max = 1;
		struct MSG_BOX_CTRL *MsgBox_p;
		int Monster_Max = 1;
		int *Monster_Kosuu_p;
		struct MONSTER_CTRL *Monster_p;
		int *Column_Kosuu_p;
		char(*ColumnTitle_p)[MONSTER_COLUMNTITLEFIELDMAX + 1];
		int GetDirFlag = 1;//LoadMondaiでMsgDir，LoadMsgBoxSetでLocalDirを取得
		int MsgCodeLinkFlag = 1;
		int JoypadLinkFlag = 1;
	};
	//■パッドののロード用変数
	struct LOAD_DISPLAY_PAD_SP {
		const char *FilePath_AreaSet_h = NULL;
		struct AREA_CTRL *ParentArea_p = NULL;
		struct DISPLAY_PAD_CTRL *DisplayPad_p;
		int Area_Max = 1;
		int BtnForm_Max = 1;
		int Index_Max = 1;
		const int *Btn_Max_h;
		int BaseBtn_Max = 1;
		//フラグ
		int GetDirFlag = 1;
		int MsgCodeLinkFlag = 1;
		int JoypadLinkFlag = 1;
	};










////////　関　数　////////
	//■AppDirの取得
	int ActiveMath_Init();
	//■フレームレートの変更
	int ChangeFPS(int FPS);
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
	//■エリアセットのロードと設定（ロードした値を元に各パラメータの値を決定する）
	int LoadAreaSet(const char *FilePath, struct AREA_CTRL *Area_h, int *Area_Kosuu_p, int Area_Max, struct AREA_CTRL *ParentArea_p);
	//■フォントスタイルのロードとフォントハンドルの作成
	int LoadFontStyle(const char *FilePath);
	//■画像スタイルのロードと画像ハンドルの作成
	int LoadFontImgStyle(const char *FilePath);
	//■タグスタイルのロード
	int LoadTagStyle(const char *FilePath);
	//■ジョイパッドスタイルのロード
	int LoadJoypadStyle(const char *FilePath);
	//■フォント・タグスタイルのリンクのロード（フォント，フォント画像，タグ設定のロード）（0：成功　-1：失敗）//※終了時はルートディレクトリ
	int LoadMsgCodeLink(const char *FilePath);
	//■ジョイパッドスタイルのリンクのロード
	int LoadJoypadLink(const char *FilePath);
	//■メッセージボックスフォームのロード
	int LoadMsgBoxFormSet(const char *FilePath, struct MSG_BOX_FORM *MsgBoxForm_h, int MsgBoxForm_Max);
	//■メッセージボックスフォームの画像パス，RGBのロード
	int LoadMsgBoxRgbSoundPathSet(const char *FilePath, struct MSG_BOX_RGB_SOUNDPATH *MsgBox_RGB_SoundPath_h, int MsgBoxForm_Max);
	//■メッセージボックスコントロールのロード
	int LoadMsgBoxSet(const char *FilePath, struct MSG_BOX_FORM *MsgBoxForm_h, struct MSG_BOX_CTRL *MsgBox_h, int MsgBoxForm_Max, int MsgBox_Max, int GetDirFlag);
	//■メッセージのロード
	int LoadMsg(const char *FilePath, char *Msg, int MsgSize, int GetDirFlag);
	//■メッセージとその関連ファイルのロード
	int LoadMsgSP(struct LOAD_MSG_SP *m);
	//●モンスターのロード
	int LoadMonster(const char* FilePath, struct MONSTER_CTRL *Monster_h, int Monster_Max, int *Monster_Kosuu, char(*ColumnTitle_h)[MONSTER_COLUMNTITLEFIELDMAX + 1], int *Column_Kosuu);
	//●モンスター画像パスのロード
	int LoadMonsterImgTitle(const char *FilePath, char(*MonsterImgTitle_h)[MAX_PATH], int Monster_Max, int *IssuedMoonsterID_p);//int *IssuedMoonsterID_pは発行済み最大ID（エディターで使用）
	//●問題のロード
	int LoadMondai(const char *FilePath, struct MONDAI_CTRL *Mondai, int *Syoumon_Kosuu_p, int GetDirFlag);
	//●問題とその関連ファイルのロード
	int LoadMondaiSP(struct LOAD_MONDAI_SP *m_p);
	//■ボタンフォームセットのロード
	int LoadBtnFormSet(const char *FilePath, struct BTN_FORM *BtnForm_h, int *BtnForm_Kosuu_p, int BtnForm_Max);
	//■ボタンセット（複数グループ）のロード（0：成功　-1：失敗（ファイル名が存在しない，引数のポインターがNULL）　-2：ボタンの配列要素数が足りない）
	int LoadBtnSetEx(const char *FilePath, struct BTN_CTRL **Btn_hh, int *Btn_Kosuu_h, const int *Btn_Max_h, int BtnSet_Kosuu, struct AREA_CTRL *BtnArea_h, struct BTN_FORM *BtnForm_h);
	//■テキスト入力ボタンセットのロード（複数グループ）のロード（0：成功　-1：失敗（ファイル名が存在しない，引数のポインターがNULL）　-2：ボタンの配列要素数が足りない）
	int LoadInputTextBtnSetEx(const char *FilePath, struct INPUT_TEXT_BTN_CTRL **Btn_hh, int *Btn_Kosuu_h, const int *Btn_Max_h, int BtnSet_Kosuu, struct AREA_CTRL *BtnArea_h, struct BTN_FORM *BtnForm_h);
	//■パッド・パッド付属ファイルのロード
	int LoadDisplayPadSP(struct LOAD_DISPLAY_PAD_SP *p_p);
	//■ファイルパスからファイル名を取得
	int GetTitleFromPath(char *FileTitle, char *FilePath);
	//■ファイルパスからディレクトリを取得（エディターでは現状使っていない）
	int GetDirFromPath(char *Dir, const char *FilePath);
	//■ローカルディレクトリ，メッセージディレクトリのパスの取得
	int SetLocalDirMsgDirFromMsgPath(const char *FilePath);

	//■カーソルオーバー
	int Math_CursorOver(int LocationX1, int LocationY1, int Padding, int StringColor, int BackColor, int Type);
	//■マルチガイド
	int MultiGuide();
	//■オーバーラップ　追加する領域を受け取って，元の描画可能領域および，元の描画可能領域と重複した領域を取得する（重複した領域NewRange　追加する領域AddRange）
	int Overlap(int *NewRange, const int *AddRange);
	//■画像の上下位置の変更
	int ChangeImgAlign(char *Msg, struct MSG_BOX_CTRL *MsgBox_p);
	//■メッセージボックスの高さの初期値表示
	int ShowHeightGauge(struct MSG_BOX_CTRL *MsgBox, int MasterHeight, int Color);

	//■エリアの表示
	int ShowArea(struct AREA_CTRL *Area_h, int Area_Kosuu);
	//■タグを読み取る関数
	int ReadMathTag(const char *Msg, struct TAG *Tag, int TagSaidai, char *ParsedMsg, const int *FontColorRGB);
	//■タグの再読み込み指示（DrawMsg用）
	int ReparseTag(struct TAG *Tag_h);
	//■タグの再読み込み指示
	int Reparse(struct MSG_BOX_CTRL *MsgBox_p);
	//■アクティブ要素の非アクティブ化（ActiveElementを-1）
	int EraseActiveElement(struct MSG_BOX_CTRL *MsgBox_p);
	//■アクティブ要素の取得（ActiveElementを0）
	int GetActiveElement(struct MSG_BOX_CTRL *MsgBox_p);

	//■メッセージボックスのリセット
	int ClearMsgBox(struct MSG_BOX_CTRL *MsgBox_p);

	//■メッセージボックスの表示
	int ShowMsgBox(const char *Msg, struct MSG_BOX_CTRL *MsgBox_p);
	//■ボタン
	int ShowBtnSet(struct BTN_CTRL *Btn_h, int Btn_Kosuu, int *PushedNo_p, int PushType, int Prev, int Next);
	//■テキストボタン
	int ShowTextBtnSet(char *Msg, struct MSG_BOX_CTRL *MsgBox_p, int MsgSize, struct INPUT_TEXT_BTN_CTRL *InputTextBtn_h, int Btn_Kosuu, int *PushedNo_p, int PushType, int Prev, int Next);
	//■リストの表示
	int ShowList(struct LIST_CTRL *List_p);

	//■メッセージのキーボード入力（キーボードから数式を入力するための関数）
	int InputMsgKey(char *Msg, struct MSG_BOX_CTRL *MsgBox_p, int MsgSize, int *InputHandle);
	//■メッセージのジョイパッド操作
	int OperateMsgJoypad(char *Msg, struct MSG_BOX_CTRL *MsgBox_p, int MsgSize);
	//■パッド（マウス操作）
	int ShowDisplayPadM(struct DISPLAY_PAD_CTRL *DisplayPad_p);
	//■パッド（ジョイパッド操作）
	int ShowDisplayPadJ(struct DISPLAY_PAD_CTRL *DisplayPad_p);
	//■パッドのリセット
	int ResetDisplayPad(struct DISPLAY_PAD_CTRL *DisplayPad_p, int OnIndexNumber);

	//■シンプル出力（数式＋フレームワーク）　（メッセージボックスコントロール不要）
	int DrawMsg(int LocationX, int LocationY, const char *Msg, int *FontColorRGB, int FontColorHandle, const struct AREA_CTRL *ParentArea_p, int Tag_Saidai, struct TAG *Tag_h, char *ParsedMsg_p);//シンプルモード
	//■幅の取得
	#define TAG_MAX_for_GetWidthForDrawMsg 1000//GetWidthForDrawMsgで読み込み可能なタグ1000個
	int GetWidthForDrawMsg(const char *Msg, int *Width, int *Height, int *Tag_Kosuu);
	//■DrawString＋フレームワーク
	int DrawStringInArea(int LocationX, int LocationY, const struct AREA_CTRL *ParentArea_p, const char *String_p, int Color);
	//■DrawFormatString＋フレームワーク
	int DrawFormatStringInArea(int LocationX, int LocationY, const struct AREA_CTRL *ParentArea_p, int Color, const char *String_p, ...);
	int SetLocalDirFromMsgPath(const char *FilePath);
	int SetMsgDirFromMsgPath(const char *FilePath);

	//int ActiveMath_Init();
}//namespace ActiveMathの終了

using namespace ActiveMath;


