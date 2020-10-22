#include "ActiveMath.h"
#include <io.h> //�t�H���_�[���̃t�@�C�����̎擾�Ɏg�p_finddata_t

//���O���[�o���ϐ�
int FPS = 60;
int WindowWidth = 1000, WindowHeight = 750 - 5, ColorBitNum = 32;

struct PLAYER {
	char Name[10 + 1];
	int Level;
	int Exp;
	int Coin;
};

float TimeLimit(struct PLAYER *Player) {
	//�m�����n�@
	//���w�i�̎w��
	int BackImg = LoadGraph(".\\File\\back_img03.png"); //�w�i�̃��[�h
	//���S�̃G���A
	struct AREACONTROL Entire = { 0 };
	Entire.Width = WindowWidth + 5;
	Entire.Height = WindowHeight + 5;
	//���ҋ@�����X�^�[�G���A
	struct AREACONTROL WaitingArea = { 0 };
	WaitingArea.Width = WindowWidth + 20;
	WaitingArea.Height = 130;
	WaitingArea.BackColor = GetColor(255, 0, 0);
	WaitingArea.BackTransparency = 95;
	WaitingArea.BorderThickness = 4;
	WaitingArea.BorderColor = GetColor(200,200,200);
	WaitingArea.ParentArea_p = &Entire;
	WaitingArea.Padding[0] = 60;

	//�m�p�b�h�֘A�̐錾�Ə������n�@
	//���p�b�h�̃��[�h
	//�i�p�b�h�}�l�[�W���[�j
	struct PadManager PadManager;//�p�b�h�}�l�[�W���[
	//�i�G���A�i[0]�C���f�b�N�X�G���A�C[1]�{�^���G���A�C[2]�x�[�X�{�^���G���A�̌v3�j�j
	const int PadAreaMax = 3;//�G���A�̍ő��
	int PadAreaKosuu;//�G���A�̌��i���[�h���Ɏ擾�j
	struct AREACONTROL PadAreaSet[PadAreaMax] = { 0 };//�G���A
	//�i�{�^���t�H�[���i�ő�10�j�j
	const int ButtonFormMax = 3;//�{�^���t�H�[���̍ő��
	int ButtonFormKosuu;//�{�^���t�H�[���̌��i���[�h���Ɏ擾�j
	struct BUTTONFORM ButtonFormSet[ButtonFormMax] = { 0 };//�{�^���t�H�[��
	//�i���͗p�C���f�b�N�X�j
	const int IndexMax = 6;//�C���f�b�N�X�̍ő��
	int IndexKosuu;//�C���f�b�N�X�̌��i���[�h���Ɏ擾�j
	struct BUTTONCONTROL IndexSet[IndexMax] = { 0 };//�C���f�b�N�X
	//�i���͗p�{�^���j
	const int ButtonMax[IndexMax] = { 36, 36, 36, 18, 18, 18 };//�e�V�[�g�����{�^���̍ő��
	int ButtonKosuu[IndexMax];//�e�V�[�g�����{�^���̌��i���[�h���Ɏ擾�j
	static struct INPUTTEXTBUTTONCTRL Button0[36];//�V�[�g0�����{�^��
	static struct INPUTTEXTBUTTONCTRL Button1[36];//�V�[�g1�����{�^��
	static struct INPUTTEXTBUTTONCTRL Button2[36];//�V�[�g2�����{�^��
	static struct INPUTTEXTBUTTONCTRL Button3[18];//�V�[�g3�����{�^��
	static struct INPUTTEXTBUTTONCTRL Button4[18];//�V�[�g4�����{�^��
	static struct INPUTTEXTBUTTONCTRL Button5[18];//�V�[�g5�����{�^��
	static struct INPUTTEXTBUTTONCTRL* ButtonSet_hh[] = { Button0, Button1, Button2, Button3, Button4, Button5 };//�e�V�[�g�����{�^���z��̐擪�A�h���X
	//�i���͗p�x�[�X�{�^���j
	const int BaseButtonMax = 36;//�x�[�X�{�^���̍ő��
	int BaseButtonKosuu;//�x�[�X�{�^���̌��i���[�h���Ɏ擾�j
	struct INPUTTEXTBUTTONCTRL BaseButtonSet[BaseButtonMax] = { 0 };//�x�[�X�{�^��
	//�i�p�b�h���b�Z�[�W�j
	const int MsgCharMax_Pad = 500;//���b�Z�[�W�̍ő啶����
	char Msg_Pad[MsgCharMax_Pad + 1];//���b�Z�[�W�i�z��T�C�Y�́C���b�Z�[�W�̍ő啶�����{�P�j
	//�i�p�b�h���b�Z�[�W�{�b�N�X�t�H�[���j
	const int MsgBoxFormKosuu_Pad = 1;//���b�Z�[�W�{�b�N�X�t�H�[���̌��i���[�h�O�Ɏw��j
	static struct MsgBoxForm MsgBoxForm_Pad;//���b�Z�[�W���b�Z�[�W�{�b�N�X�t�H�[��
	//�i�p�b�h���b�Z�[�W�{�b�N�X�j
	const int MsgBoxKosuu_Pad = 1;//���b�Z�[�W�{�b�N�X�̌��i���[�h�O�Ɏw��j
	static struct MsgBoxCtrl MsgBox_Pad;//���b�Z�[�W�{�b�N�X
	//�i���[�h�j
	const char FilePath_Pad[MAX_PATH] = ".\\File\\Pad\\Pad01.acp";
	int Error = LoadPad(FilePath_Pad, PadAreaSet, &PadAreaKosuu, PadAreaMax, &Entire,
		ButtonFormSet, &ButtonFormKosuu, ButtonFormMax,
		IndexSet, &IndexKosuu, IndexMax,
		ButtonSet_hh, ButtonKosuu, ButtonMax,
		BaseButtonSet, &BaseButtonKosuu, BaseButtonMax,
		Msg_Pad, MsgCharMax_Pad + 1, 0, &MsgBoxForm_Pad, MsgBoxFormKosuu_Pad, &MsgBox_Pad, MsgBoxKosuu_Pad, 0, 1 //�t�H���g�E�^�O�����[�h���Ȃ��i�O�j//�W���C�p�b�h�̊��蓖�Ă����[�h����i�O�ȊO�j
	);//LoadPad�̏I�����̓f�B���N�g�����p�b�h�T�u�f�B���N�g��
	//�p�b�h�̔�A�N�e�B�u���i��⏑���o����C�{�^���������܂Ńp�b�h���g���Ȃ��悤�Ɂj
	PadManager.Active = 0;

	//�����b�Z�[�W�C���b�Z�[�W�{�b�N�X�̏������p�R�s�[�̎擾
	struct MsgBoxCtrl MsgBox_Pad_Copy = MsgBox_Pad;//
	char Msg_Pad_Copy[MsgCharMax_Pad + 1];
	strcpy(Msg_Pad_Copy, Msg_Pad);
	//�m���֘A�̐錾�Ə������n�@
	//�����̑I��
	//�i���̃t�@�C�������擾�j
	SetCurrentDirectory(AppDir);
	SetCurrentDirectory(".\\File\\Mondai\\Group01");
	const int MondaiFileMax = 20;
	char MsgFilePath[MondaiFileMax][MAX_PATH] = { 0 };//���ׂĂ̖��t�@�C�������擾����z��
	struct _finddata_t fd;
	long fhd;
	fhd = _findfirst("*.ack", &fd);
	if (fhd == -1) return 1;
	strcpy(MsgFilePath[0], fd.name);//�擾�����ŏ��̃t�@�C������z��ɏ����ʂ�
	int MondaiFileKosuu;//���̌�
	for (MondaiFileKosuu = 1; MondaiFileKosuu < MondaiFileMax && !_findnext(fhd, &fd); MondaiFileKosuu++) {
		strcpy(MsgFilePath[MondaiFileKosuu], fd.name);////�擾�����t�@�C������z��ɏ����ʂ��B��������MondaiKosuu�͖��̃J�E���g��
	}
	_findclose(fhd);
	//�i��萔�Ɩ��ԍ��̊m��j
	srand(GetNowCount()); //���݂̎����ŃV�[�h���擾
	const int MondaiMax = 5; //�ő��萔���w��
	int MondaiFileNum[MondaiMax];
	for (int i = 0; i < MondaiMax; i++) MondaiFileNum[i] = -1;
	int MondaiKosuu = rand() % MondaiMax + 1; //��萔�̊m��
	for (int i = 0; i < MondaiKosuu; i++){
		MondaiFileNum[i] = rand() % MondaiFileKosuu; //���ԍ��̊m��
	}
	//�����̃��[�h
	struct Kadai Mondai[MondaiMax] = { 0 }; //���b�Z�[�W������
	int SyoumonKosuu[MondaiMax];
	for (int i = 0; i < MondaiKosuu; i++) {
		//�i���̃��[�h�j
		LoadMondai(MsgFilePath[MondaiFileNum[i]], &Mondai[i], &SyoumonKosuu[i], 0);//�P�FGetDirFlag
		//�i����̕��בւ��j
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
	//�i�ŏ��̖��̎w��j
	int MondaiNum = 0;
	SetLocalDirMsgDirFromMsgPath(MsgFilePath[MondaiFileNum[MondaiNum]]);
	//�����֘A�t�@�C���̃��[�h�i���b�Z�[�W�t�H�[���C���b�Z�[�W�{�b�N�X�C�����X�^�[�C�ݒ�i�t�H���g�C�t�H���g�摜�C�^�O�ݒ�j�j
	//�i���j
	const int MsgBoxFormKosuu = 3;
	static struct MsgBoxForm MsgBoxForm[MsgBoxFormKosuu];//[0]���E����@[1]���␳���@[2]���◚���E���␳�𗚗�
	const int MsgBoxKosuu = 3;
	static struct MsgBoxCtrl MsgBox[MsgBoxKosuu];//[0]���@[1]����@[2]���␳��
	//�i�����X�^�[�j
	const int MonsterMax = 500;
	struct Monster Monster[MonsterMax];
	int MonsterKosuu = 0;//�����X�^�[���i���ۂ̌��j
	static int MonsterImgWidth[MonsterMax];
	static int MonsterImgHeight[MonsterMax];//�����X�^�[�摜�̏c���T�C�Y���擾���邽�߂̕ϐ�
	int  MonsterImgFlag = 1;//�����X�^�[�摜�̕\���t���O�i�O�F��\���@�O�ȊO�F�\���j

	char ColumnTitle[MONSTER_COLUMNMAX][MONSTER_COLUMNTITLEFIELDMAX + 1] = { 0 };
	int ColumnKosuu = 0;
	//�i���[�h�j
	LoadMondaiSet(LocalDir, MsgBoxForm, MsgBoxFormKosuu, MsgBox, MsgBoxKosuu,
		Monster, MonsterMax, &MonsterKosuu, NULL, ColumnTitle, &ColumnKosuu, 1, 0);//���s�ςݍő�ID�iNULL�j//�t�H���g�E�^�O�����[�h����i�O�ȊO�j//�W���C�p�b�h�̊��蓖�Ă����[�h���Ȃ��i�O�j
	for (int i = 0; i < 3; i++) MsgBox[i].ParentArea_p = &Entire;
	//����E���␳���̍��[�́C�R���g���[���̕����O�Ɏw��i�c�͐����X�V�B���̏c�͂��Ƃ�MondaiLine����擾���C���̉������̂Ƃ��Ɏw�肷��B�j
	MsgBox[1].Location[0] = 50;
	MsgBox[2].Location[0] = 50 + MsgBox[1].OuterWidth;
	//������E���␳���R���g���[���̕���
	static struct MsgBoxCtrl MsgBox_Syoumon[3];
	static struct MsgBoxCtrl MsgBox_SyoumonSeikai[3];
	for (int i = 0; i < 3; i++) {
		MsgBox_Syoumon[i] = MsgBox[1];
		MsgBox_SyoumonSeikai[i] = MsgBox[2];
	}
	//�����̎��_�ł́C���t�H�[��[0]�C����t�H�[��[2]�C���␳���t�H�[��[2]�@��[2]�͗���p�̃t�H�[��

	//���ŏ�ʂ̏����[0]�ɁC�ŏ�ʂ̏��␳����[1]�ɏ�������
	MsgBox_Syoumon[0].MsgBoxForm_p = &MsgBoxForm[0];
	MsgBox_SyoumonSeikai[0].MsgBoxForm_p = &MsgBoxForm[1];

	//�������X�^�[�ԍ��̊m��i�Y�����Ȃ����0�̂܂܁j
	int MonsterNum[MondaiMax];//�����X�^�[�̗v�f�ԍ�
	for (int i = 0; i < MondaiMax; i++) MonsterNum[i] = -1;
	for (int d = 0; d < MondaiKosuu; d++) {
		for (int i = 0; i < MonsterKosuu; i++) {
			if (Mondai[d].monsterID == Monster[i].Column[0]) {
				MonsterNum[d] = i; break;
			}
		}
	}
	//�������X�^�[�摜�T�C�Y�̎擾
	for (int i = 0; i < MonsterKosuu; i++) {//�����X�^�[�摜�T�C�Y�̎擾
		GetGraphSize(Monster[i].Img, &MonsterImgWidth[i], &MonsterImgHeight[i]); //�����X�^�[�̉摜�̏c���T�C�Y���擾����MonsterImgWide�CMonsterImgHeight�Ɏ擾
	}
	//���������ԁi�b�j�̎擾
	int ExpEarned = 0;//�o���l�i�|�C���g�j
	int CoinEarned = 0;//�R�C���i�S�[���h�j
	for (int i = 0; i < MondaiKosuu; i++) {
		ExpEarned += Monster[MonsterNum[i]].Column[2];
		CoinEarned += Monster[MonsterNum[i]].Column[3];
	}
	//���\������ԍ��C�V�[���̐؂�ւ�
	int SyoumonNum = 0;//�\�����鏬��ԍ�
	int SeikaiFlag = 0;//�����t���O
	int Scene = -2;//�|�Q�F�@�|�P�F�@�O�F�@�P�F�@�Q�F
	//��
	char TextBuff[20];
	//�����肷�郁�b�Z�[�W
	char Msg_Confirm[INPUTTEXTBUTTON_FIELDSIZE + 1];//���肷�郁�b�Z�[�W
	const int MsgBoxFormKosuu_Confirm = 1;
	static struct MsgBoxForm MsgBoxForm_Confirm;
	const int MsgBoxKosuu_Confirm = 1;
	static struct MsgBoxCtrl MsgBox_Confirm;
	SetCurrentDirectory(AppDir);
	LoadMsgSet(".\\File\\MsgConfirm", &MsgBoxForm_Confirm, MsgBoxFormKosuu_Confirm, &MsgBox_Confirm, MsgBoxKosuu_Confirm, 0, 0);//�t�H���g�^�O�ݒ�����[�h����i�O�ȊO�j
	//�����茋��
	char Msg_Judge[INPUTTEXTBUTTON_FIELDSIZE + 1];
	const int MsgBoxFormKosuu_Judge = 1;
	static struct MsgBoxForm MsgBoxForm_Judge;
	const int MsgBoxKosuu_Judge = 1;
	static struct MsgBoxCtrl MsgBox_Judge;
	SetCurrentDirectory(AppDir);
	LoadMsgSet(".\\File\\MsgJudge", &MsgBoxForm_Judge, MsgBoxFormKosuu_Judge, &MsgBox_Judge, MsgBoxKosuu_Judge, 0, 0);//�t�H���g�^�O�ݒ�����[�h����i�O�ȊO�j
	//���o�g�������b�Z�[�W
	const int MsgCharMax_Battle = 300;//�ǂݍ��݉\�ȕ�����
	char Msg_Battle[MsgCharMax_Battle + 1] = { 0 };//���b�Z�[�W
	//���o�g�������b�Z�[�W�֘A�t�@�C���̃��[�h�i���b�Z�[�W�{�b�N�X�t�H�[���C���b�Z�[�W�{�b�N�X�C�ݒ�i�t�H���g�C�t�H���g�摜�C�^�O�ݒ�j�j
	SetCurrentDirectory(AppDir);
	int MsgBoxFormKosuu_Battle = 1;
	static struct MsgBoxForm MsgBoxForm_Battle;//���b�Z�[�W�{�b�N�X�t�H�[��
	int MsgBoxKosuu_Battle = 1;
	static struct MsgBoxCtrl MsgBox_Battle;//���b�Z�[�W�{�b�N�X
	LoadMsgSet(".\\File\\MsgBattle", &MsgBoxForm_Battle, MsgBoxFormKosuu_Battle, &MsgBox_Battle, MsgBoxKosuu_Battle, 0, 0);//���b�Z�[�W�{�b�N�X�t�H�[���̌��P//���b�Z�[�W�{�b�N�X�̌��P//�t�H���g�^�O�ݒ�����[�h����i�O�ȊO�j
	//�m���b�Z�[�W�֘A�̐錾�Ə������n�@
	//�����b�Z�[�W�̃��[�h
	const int MsgCharMax_End = 300;//�ǂݍ��݉\�ȕ�����
	char Msg_End[MsgCharMax_End + 1] = { 0 };//���b�Z�[�W

	//�����b�Z�[�W�֘A�t�@�C���̃��[�h�i���b�Z�[�W�{�b�N�X�t�H�[���C���b�Z�[�W�{�b�N�X�C�ݒ�i�t�H���g�C�t�H���g�摜�C�^�O�ݒ�j�j
	SetCurrentDirectory(AppDir);
	int MsgBoxFormKosuu_End = 1;
	static struct MsgBoxForm MsgBoxForm_End;//���b�Z�[�W�{�b�N�X�t�H�[��
	int MsgBoxKosuu_End = 1;
	static struct MsgBoxCtrl MsgBox_End;//���b�Z�[�W�{�b�N�X
	LoadMsgSet(".\\File\\MsgEnd", &MsgBoxForm_End, MsgBoxFormKosuu_End, &MsgBox_End, MsgBoxKosuu_End, 0, 0);//���b�Z�[�W�{�b�N�X�t�H�[���̌��P//���b�Z�[�W�{�b�N�X�̌��P//�t�H���g�^�O�ݒ�����[�h����i�O�ȊO�j
	//�������t�@�C���̃��[�h
	SetCurrentDirectory(AppDir);
	int PushSound = LoadSoundMem(".\\File\\poka01.mp3");
	int AtuckSound = LoadSoundMem(".\\File\\MsgJudge\\Sound\\damage7.mp3");
	int MissSound = LoadSoundMem(".\\File\\MsgJudge\\Sound\\swish2.mp3");
	int DamageSound = LoadSoundMem(".\\File\\MsgEnd\\Sound\\attack01.mp3");

	//�����
	int MonsterBaseLine1 = 148;//�ҋ@�����X�^�[�̉�����10���̈ʒu
	int MonsterBaseLine2 = 440;//�����X�^�[���[
	int MonsterBaseLine3 = 700;//�����X�^�[�O�i��
	int MonsterBaseLine4 = 800;//�����X�^�[�ڋߎ�
	int MondaiLine = MonsterBaseLine2 + 10;
	//���ʒu
	WaitingArea.Location[0] = -10;
	WaitingArea.Location[1] = 34;
	MsgBox[0].Location[0] = 50;
	MsgBox[0].Location[1] = MondaiLine;
	//�i�p�b�h�p�b�h�G���A�̃p�����[�^�̈ʒu�w��j
	MsgBox_Pad.Location[0] = 630;
	MsgBox_Pad.Location[1] = MondaiLine - MsgBox_Pad.OuterHeight;
	PadAreaSet[0].Location[0] += MsgBox_Pad.Location[0];//�p�b�h�̉��ʒu���w��i���b�Z�[�W�{�b�N�X�Ɠ����ʒu�j
	PadAreaSet[0].Location[1] += MsgBox_Pad.Location[1];//���b�Z�[�W�{�b�N�X�̒������w��

	MsgBox_Judge.Location[0] = 53 + (MsgBox[0].Width - 130) / 2;//���ʂ̕\���ʒu�i�c�j�̎w��

	MsgBox_Battle.Location[0] = MsgBox[0].Location[0];//�N���A�[���b�Z�[�W�̉��ʒu���w��i���Ɠ����ʒu�j
	MsgBox_Battle.Location[1] = MondaiLine;//�N���A�[���b�Z�[�W�̏c�ʒu���w��i���Ɠ����ʒu�j

	MsgBox_End.Location[0] = MsgBox[0].Location[0];//�N���A�[���b�Z�[�W�̉��ʒu���w��i���Ɠ����ʒu�j
	MsgBox_End.Location[1] = MondaiLine;//�N���A�[���b�Z�[�W�̏c�ʒu���w��i���Ɠ����ʒu�j

	//�^�C���Q�[�W�̉摜�̃��[�h
	int GaugeBackImg = LoadGraph(".\\File\\gauge_back_img.png");
	int GaugeImg = LoadGraph(".\\File\\gauge_img.png");

	//���Ȃ����CStartJoypadVibration�͂Q��ڈȍ~�łȂ��ƐU�����Ȃ����߁C���O�ɂP��ڂ��ς܂��Ă���
	StartJoypadVibration(DX_INPUT_PAD1, 1000, 0);//�i�P��ڂ͐U�����Ȃ����ꉞ�O�b�ɐݒ�j
	//���A���ł͂��߂ŁCWaitTimer(5)������łP��ڂƂQ��ڂ�5�~���b�ȏ゠����ƂQ��ڂŐU������B�����s��
	int MondaiFlag = 0;
	int GaugeFlag = 0;//�Q�[�W�t���O�i�O�F��~�@�P�F�쓮�j���Q�[�W���^���C�Q�[���N���A�̂Ƃ��ɒ�~�ƂȂ�@���J�n�̓���̏I���C�����X�^�[�̍U����C���̑��Ɉڂ�Ƃ��ɍ쓮
	int GaugeFrame = 0;//�Q�[�W�t���[���i���̑��Ɉڂ�Ƃ��Ƀ��Z�b�g�j
	int TimeFlag = 0;//�o�ߎ��ԃt���O�i�O�F��~�@�P�F�쓮�j�������C�Q�[���N���A�̂Ƃ��ɒ�~�ƂȂ�@���J�n�̓��삪�I���ƍ쓮
	int TimeFrame = 0;//�o�߃t���[���i���̑��Ɉڂ��Ă������j
	//�m���C�����[�v�n
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !MathgpUpdateJoypad()) {
		//������������ҋ@
		SleepToFitFPS(FPS);
		//���S�̃G���A
		ShowArea(&Entire, 1);
		//���w�i
		DrawGraph(Entire.Nest[0], Entire.Nest[1], BackImg, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 51);//�A���t�@�u�����h20��
		//���^�C���i�t���[�������犄��o�������ԁj
		static int Time_BackColor = GetColor(0, 0, 0);
		static int Time_TextColor = GetColor(255, 255, 255);
		DrawBox(0, 0, WindowWidth, 34, Time_BackColor, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawFormatString(750, 5, Time_TextColor, "�^�C��:%7.2f�b", TimeFrame / (float)FPS);
		if (TimeFlag != 0) TimeFrame++;//�t���[���̃J�E���g
		//���ҋ@�G���A
		ShowArea(&WaitingArea, 1);


		//���Q�[�W
		static float Time_Elapsed;//�o�ߎ��ԁi�b�j
		static int GaugeRate;//�o�ߗ��i���j
		if (GaugeFlag != 0) {//�Q�[�W�쓮��
			GaugeFrame++;//�Q�[�W��i�߂�
			Time_Elapsed = GaugeFrame / (float)FPS;//�o�ߎ��ԁi�b�j
			GaugeRate = 100 * Time_Elapsed / Monster[MonsterNum[MondaiNum]].Column[1];//�o�ߗ��i���j
		}
		//���Q�[�W���^��
		if (GaugeRate >= 100) {
			GaugeFlag = 0;//����ȏ�TimeRate�𑝂₳�Ȃ�
			if (Scene == 0) {
				Scene = 2;//����V�[���łȂ��C�s�k�V�[���łȂ��Ȃ烂���X�^�[�̍U���V�[���֐i��
				MondaiFlag = 0;//�����\��
				GaugeFrame = 0;//�Q�[�W�̃��Z�b�g
			}
		}
		static int Count_D = 0;
		if (MondaiNum >= 0) {
			//���ҋ@�����X�^�[
			int Rate = 2 / 3;//������2/3�̑傫���ŕ\���i���S���獶�E��1/3�̈ʒu�j
			int ImgX1 = WaitingArea.Nest[0], ImgY1, ImgX2, ImgY2;
			SetDrawArea(WaitingArea.Nest[0], WaitingArea.Nest[1], WaitingArea.Nest[2], WaitingArea.Nest[3]);//�`��\�̈�̎w��
			for (int i = MondaiNum + 1; i < MondaiKosuu; i++) {
				ImgX2 = ImgX1 + MonsterImgWidth[MonsterNum[i]] * 2 / 3;
				ImgY1 = MonsterBaseLine1 - MonsterImgHeight[MonsterNum[i]] * 2 / 3 * 0.9;
				ImgY2 = ImgY1 + MonsterImgHeight[MonsterNum[i]] * 2 / 3;
				if (Monster[MonsterNum[i]].Img != -1) DrawExtendGraph(ImgX1, ImgY1, ImgX2, ImgY2, Monster[MonsterNum[i]].Img, true);  //�ҋ@�����X�^�[�摜��`�悷��
				ImgX1 = ImgX2 + 20;
			}
			SetDrawArea(0, 0, WindowWidth, WindowHeight);//�`��\�̈�̎w�����

			//�������X�^�[
			if (MonsterImgFlag != 0) {
				//�i�����X�^�[�摜�j
				int MonsterX = Entire.Nest[0] + 53 + (MsgBox[0].Width - MonsterImgWidth[MonsterNum[MondaiNum]]) / 2;
				int MonsterY = Entire.Nest[1] + MonsterBaseLine2 - MonsterImgHeight[MonsterNum[MondaiNum]];
				DrawGraph(MonsterX, MonsterY, Monster[MonsterNum[MondaiNum]].Img, TRUE);
				if (GaugeFlag != 0) {//�����X�^�[���\������Ă��Ă��Q�[�W����~���̓Q�[�W��\�����Ȃ�
					//�i�~�Q�[�W�j���Q�[�W���J���ɂȂ�Ύ��Ԑ؂�
					int GaugeX = MonsterX - 10;//�~�Q�[�W�̒��SX
					int GaugeY = MonsterY - 10;//�~�Q�[�W�̒��SY
					DrawCircleGauge(GaugeX, GaugeY, 100, GaugeBackImg, 0);//�~�Q�[�W
					DrawCircleGauge(GaugeX, GaugeY, 100 - GaugeRate, GaugeImg, 0);//�~�Q�[�W
				}
			}
			//���J�n���b�Z�[�W
			if (Scene == -1) {
				static int Count = 0;
				Count++;
				static int i = 0;
				if (Count == FPS / 2 * (i + 1) && MondaiKosuu > i) {
					//�i�J�n���b�Z�[�W�j
					if (i == 0) strcpy(Msg_Battle, "<p>");
					else strcat(Msg_Battle, "<p>");
					strcat(Msg_Battle, Monster[MonsterNum[i]].Name);
					strcat(Msg_Battle, "���@�����ꂽ�I</p>");
					Reparse(&MsgBox_Battle);
					i++;
				}
				if (Count == FPS / 2 * (i + 2) && MondaiKosuu == i) {
					//�i�J�n���b�Z�[�W�j
					GaugeFlag = 1;
					MondaiFlag = 1;
					Count = 0;
					Scene = 0;
					i = 0;
				}
				ShowMsgBox(Msg_Battle, &MsgBox_Battle);
			}
			//�����
			int End = SyoumonNum - 2;
			if (End < 0) End = 0;
			//�i���j
			if (MondaiFlag != 0) {
				if (ShowMsgBox(Mondai[MondaiNum].daimon, &MsgBox[0]) == 6) Count_D++;
				//�i��⏑���o����̃p�b�h�̃A�N�e�B�u���Ə���̕\���j
				if (Count_D > 0) {//�����҂��Ă��珬��̕\��
					if (Count_D == 1) PlaySoundMem(PushSound, DX_PLAYTYPE_BACK, TRUE);//�{�^������������
					else if (Count_D == FPS / 4) {
						PadManager.Active = 1;//�����҂��Ă���p�b�h�̃A�N�e�B�u���i�C���f�b�N�X�G���A�ƃx�[�X�{�^���G���A�̂݃A�N�e�B�u�ƂȂ�j
						GetActiveElement(&MsgBox_Pad);//ActiveElement��0
					}
					for (int i = 0; SyoumonNum - i >= 0 && i < 3; i++) {
						if (i == 0) {
							MsgBox_Syoumon[i].Location[1] = MsgBox[0].Location[1] + MsgBox[0].OuterHeight;//�ŏ�ʂ̏���ȊO�́C�O�̏���̒���
						}
						else if (i > 0) MsgBox_Syoumon[i].Location[1] = MsgBox_Syoumon[i - 1].Location[1] + MsgBox_Syoumon[i - 1].OuterHeight;//�ŏ�ʂ̏���ȊO�́C�O�̏���̒���
						ShowMsgBox(Mondai[MondaiNum].syoumon[SyoumonNum - i], &MsgBox_Syoumon[i]);
					}
					//�i���␳���j
					for (int i = 0; SyoumonNum - i >= 0 && i < 3; i++) {
						MsgBox_SyoumonSeikai[i].Location[1] = MsgBox_Syoumon[i].Location[1];//�c�͏���Ɠ���
						if (i == 0 && SeikaiFlag == 0) ShowMsgBox("<math></math>", &MsgBox_SyoumonSeikai[i]);//�����i�������ȊO�CSyoumonNum�̐����͔�\���j
						else ShowMsgBox(Mondai[MondaiNum].syoumonseikai[SyoumonNum - i], &MsgBox_SyoumonSeikai[i]);//�����i�������ȊO�CSyoumonNum�̐����͔�\���j
						//�i����{�b�N�X�Ə��␳���{�b�N�X�̍��������낦��j
						if (MsgBox_Syoumon[i].Height < MsgBox_SyoumonSeikai[i].Height) MsgBox_Syoumon[i].Height = MsgBox_SyoumonSeikai[i].Height;
						else MsgBox_SyoumonSeikai[i].Height = MsgBox_Syoumon[i].Height;
					}
				}
			}
		}
		else Count_D = 0;//�����l�ɖ߂�
		//���p�b�h�̕\���E���b�Z�[�W�{�b�N�X�̕\���E���b�Z�[�W�̃W���C�p�b�h����
		int ShowMsgBoxFlag = 1;
		if (ShowPadJ(Msg_Pad, &MsgBox_Pad, MsgCharMax_Pad + 1, ShowMsgBoxFlag, IndexSet, IndexKosuu, ButtonSet_hh, ButtonKosuu, BaseButtonSet, BaseButtonKosuu, PadAreaSet, &PadManager) == 1) {//�v�b�V�������������P�̂Ƃ�
			//���m��{�^��
			if (Scene == 0 && PadManager.PushedNo == 35 && PadAreaSet[2].Active == 1) {//�x�[�X�{�^����35�ԁi�m��{�^���j���N���b�N�����B�@�x�[�X�{�^���F1000�ԑ�
				Scene = 1;//�i���۔���ɐi�ށj
			}
		}
		//��������Enter�������Ċm��
		if (Scene == 0 && MsgBox_Pad.Condition == 101) {
			MsgBox_Pad.Condition = 1;//���񂱂��ɓ����Ă��Ȃ��悤�ɂP�ɖ߂�
			Scene = 1;//�i���۔���ɐi�ށj
		}

		//�k���۔���l
		if (Scene == 1) {
			static int CountJ = 0;
			static int Scroll = 0;//���胁�b�Z�[�W�̃X�N���[����
			CountJ++;
			//���p�b�h�̃��Z�b�g�Ɣ���p���b�Z�[�W�̍X�V
			if (CountJ == 1) {
				//�i����p���b�Z�[�W�̍X�V�j
				strcpy(Msg_Confirm, Msg_Pad);//����p���b�Z�[�W���擾����
				Reparse(&MsgBox_Confirm);//�^�O�̍ēǂݍ��ݎw��
				MsgBox_Confirm.Tag[0].ConnectionP = 0;//FlameCounter�̃��Z�b�g�i�ŏ��̏����o���Ƃ�����炷���߁j
				MsgBox_Confirm.Location[1] = MonsterBaseLine2 - (MonsterImgHeight[MonsterNum[MondaiNum]] + MsgBox_Confirm.Height) / 2;//���胁�b�Z�[�W�̕\���ʒu�i�c�j�̎w��@�����������o���܂�MsgBox_Hantei.Height���m�肵�Ȃ�
				//�i�p�b�h�̃��Z�b�g�j
				strcpy(Msg_Pad, Msg_Pad_Copy);//�p�b�h�̃��b�Z�[�W���N���A�i�p�b�h���삩�琳�۔���ɐi�񂾂̂ŁC�^�O�̍ēǂݍ��݂͕s�v�j
				PadManager.Active = 0;//�p�b�h�̔�A�N�e�B�u���i���肪�I���܂Ńp�b�h���g���Ȃ��悤�Ɂj
				EraseActiveElement(&MsgBox_Pad);//ActiveElement��-1
			}
			//������p���b�Z�[�W�̕\��
			else if (FPS < CountJ && CountJ < FPS * 2) {
				MsgBox_Confirm.Location[0] = MsgBox[0].Location[0] + (MsgBox[0].Width - 100) / 2 + FPS - Scroll;//���胁�b�Z�[�W�̕\���ʒu�i���j�̎w��
				ShowMsgBox(Msg_Confirm, &MsgBox_Confirm);
				Scroll += 2;//���胁�b�Z�[�W�̃X�N���[���ʂ̍X�V
			}
			//������i�A�^�b�N���{���ʃ��b�Z�[�W�̍쐬�{�����Ȃ�\�����鐳��ԍ��̍X�V�j
			else if (CountJ == FPS * 2) {
				//�i�����j
				if (!strcmp(Mondai[MondaiNum].syoumonseikai[SyoumonNum], Msg_Confirm)) {
					PlaySoundMem(AtuckSound, DX_PLAYTYPE_BACK, TRUE);//������
					strcpy(Msg_Judge, "<p> Correct! </p>");//����p���b�Z�[�W���擾����
					SeikaiFlag = 1;
					Reparse(&MsgBox_SyoumonSeikai[0]);//�^�O�̍ēǂݍ��ݎw���i�����{�b�N�X��\�������邽�߁j
				}
				//�i�s�����j
				else {
					PlaySoundMem(MissSound, DX_PLAYTYPE_BACK, TRUE);//�s������
					strcpy(Msg_Judge, "<p>Try again.</p>");//����p���b�Z�[�W���擾����
				}
				Reparse(&MsgBox_Judge);//�^�O�̍ēǂݍ��ݎw��
				MsgBox_Judge.Location[1] = MonsterBaseLine2 - (MonsterImgHeight[MonsterNum[MondaiNum]] + MsgBox_Judge.Height) / 2;//���ʂ̕\���ʒu�i�c�j�̎w��
			}
			//�����ʂ̕\��
			else if (FPS * 2 < CountJ && CountJ < FPS * 3) {
				ShowMsgBox(Msg_Judge, &MsgBox_Judge);
				if (SeikaiFlag == 1 && CountJ % (FPS / 5) < FPS / 10) MonsterImgFlag = 0;
				else  MonsterImgFlag = 1;
			}
			//���\��������ԍ��̌���
			else if (CountJ == FPS * 3) {
				//�i���̏���̏����j
				if (SyoumonNum + 1 < SyoumonKosuu[MondaiNum]) {
					//�i�����̂Ƃ��j
					if (SeikaiFlag == 1) {
						//�i����ԍ��E�t���O�̍X�V�j
						SyoumonNum++;//�\��������ԍ��̍X�V
						SeikaiFlag = 0;
						MonsterImgFlag = 1;//�����X�^�[�摜�̕\��
						//�i���⃁�b�Z�[�W�{�b�N�X�̍X�V�j
						for (int i = 0; i < 3; i++) {
							Reparse(&MsgBox_Syoumon[i]);//�^�O�̍ēǂݍ��ݎw��
							Reparse(&MsgBox_SyoumonSeikai[i]);//�^�O�̍ēǂݍ��ݎw��
						}
						MsgBox_Syoumon[0].Tag[0].ConnectionP = 0;//Tag[0].ConnectionP��FlameCounter��\��//�ŏ�ʂ̏��₪�p�J�p�J����悤�Ƀ��Z�b�g�B
						MsgBox_Syoumon[0].Condition = 1;//������悤�Ƀ��Z�b�g�B
					}
					//�i���ۂɊւ�炸�j
					CountJ = 0;//�J�E���^�[�̃��Z�b�g
					Scene = 0;//���۔���𔲂���
					PadManager.Active = 1;//�p�b�h�̃A�N�e�B�u���i�C���f�b�N�X�G���A�ƃx�[�X�{�^���G���A�̂݃A�N�e�B�u�ƂȂ�j
					GetActiveElement(&MsgBox_Pad);//ActiveElement��0
				}
				//�i���̏��₪���݂��Ȃ��j
				else {
					//�i�����̂Ƃ��j
					if (SeikaiFlag == 1) {
						//�i���̑��̏����j
						if (MondaiNum + 1 < MondaiKosuu) {
							//�i���ԍ��E���[�J���f�B���N�g���̕ύX�E�t���O�̍X�V�j
							MondaiNum++;
							SetCurrentDirectory(LocalDir);
							SetLocalDirMsgDirFromMsgPath(MsgFilePath[MondaiFileNum[MondaiNum]]);//���[�J���f�B���N�g���E���b�Z�[�W�f�B���N�g���̕ύX
							Count_D = 0;
							//�i��⃁�b�Z�[�W�{�b�N�X�̍X�V�j
							MsgBox[0].Tag[0].ConnectionP = 0;//Tag[0].ConnectionP��FlameCounter��\��//�ŏ�ʂ̏��₪�p�J�p�J����悤�Ƀ��Z�b�g�B
							MsgBox[0].Condition = 1;
							Reparse(&MsgBox[0]);//�^�O�̍ēǂݍ��ݎw��
							//�i����ԍ��E�t���O�̍X�V�j
							SyoumonNum = 0;
							SeikaiFlag = 0;
							MonsterImgFlag = 1;//�����X�^�[�摜�̕\��
							//�i���⃁�b�Z�[�W�{�b�N�X�̍X�V�j
							for (int i = 0; i < 3; i++) {
								Reparse(&MsgBox_Syoumon[i]);//�^�O�̍ēǂݍ��ݎw��
								Reparse(&MsgBox_SyoumonSeikai[i]);//�^�O�̍ēǂݍ��ݎw��
							}
							MsgBox_Syoumon[0].Tag[0].ConnectionP = 0;//Tag[0].ConnectionP��FlameCounter��\��//�ŏ�ʂ̏��₪�p�J�p�J����悤�Ƀ��Z�b�g�B
							MsgBox_Syoumon[0].Condition = 1;//������悤�Ƀ��Z�b�g�B
							//�i�j
							CountJ = 0;//�J�E���^�[�̃��Z�b�g
							Scene = 0;//���۔���𔲂���
							MondaiFlag = 1;//����\��
							GaugeFlag = 1;//�Q�[�W�̋N��
							GaugeFrame = 0;
						}
						//�i���̑�₪���݂��Ȃ��j
						else {
							MonsterImgFlag = 0;//�����X�^�[�摜�̔�\��
							MondaiNum = -1;
							MondaiFlag = 0;//�����\��
							GaugeFlag = 0;//�Q�[�W�̒�~
							TimeFlag = 0;//�o�ߎ��Ԃ��~�߂�i���̑�₪���݂��Ȃ��Ƃ������j
						}
					}
					//�i�s�����̂Ƃ��j
					else {
						CountJ = 0;//�J�E���^�[�̃��Z�b�g
						Scene = 0;//���۔���𔲂���
						PadManager.Active = 1;//�p�b�h�̃A�N�e�B�u���i�C���f�b�N�X�G���A�ƃx�[�X�{�^���G���A�̂݃A�N�e�B�u�ƂȂ�j
						GetActiveElement(&MsgBox_Pad);//ActiveElement��0
					}
				}
				//�i���ۂɊւ�炸�j
				Scroll = 0;//���胁�b�Z�[�W�̃X�N���[���ʂ����Z�b�g
			}
			//�����̑�₪���݂��Ȃ��i�N���A�[���b�Z�[�W�̕\���j
			else if (CountJ > FPS * 3) {
				static int Finish = 0;
				//�i�o���l�l���̃��b�Z�[�W�̏����j
				if (Finish == 0) {
					Finish++;
					strcpy(LocalDir, AppDir);
					strcat(LocalDir, "\\File\\MsgEnd");
					//�i�o���l�̊l���j
					Player->Exp += ExpEarned;
					strcpy(Msg_End, "<p>#sound_l{.\\one35.mp3}�܂��̂̂ނ���@��������I</p><p><math>");
					_itoa(ExpEarned, TextBuff, 10);
					strcat(Msg_End, TextBuff);
					strcat(Msg_End, "</math>�|�C���g�́@�������񂿂��@�����Ƃ��I</p>");
					ClearMsgBox(&MsgBox_End);
				}
				//�i���x���A�b�v�̃��b�Z�[�W�̏����j
				else if (Finish == 2) {
					Finish++;
					int Level = Player->Exp / 100 + 1;
					if (Level > Player->Level) {//���x���A�b�v������Ƃ�
						Player->Level = Level;
						strcpy(Msg_End, "<p>#sound_l{.\\trumpet1.mp3}#Wait(1)");
						strcat(Msg_End, Player->Name);
						strcat(Msg_End, "�́@���x��<math>");
						_itoa(Player->Level, TextBuff, 10);
						strcat(Msg_End, TextBuff);
						strcat(Msg_End, "</math>�Ɂ@���������I</p>");
						ClearMsgBox(&MsgBox_End);
					}
					else Finish++;//���x���A�b�v���Ȃ��Ƃ��CFinish == 4�ƂȂ�
				}
				//�i�R�C���l���̃��b�Z�[�W�̏����j
				if (Finish == 4) {//������else if �Ƃ��Ȃ����Ɓi���x���A�b�v���Ȃ��Ƃ��C�����ɓ���悤�ɂ��邽�߁j
					Finish++;
					Player->Coin += CoinEarned;
					strcpy(Msg_End, "<p><math>");
					_itoa(CoinEarned, TextBuff, 10);
					strcat(Msg_End, TextBuff);
					strcat(Msg_End, "</math>�S�[���h���@�Ăɂ��ꂽ�I</p>");
					ClearMsgBox(&MsgBox_End);
				}
				//�iTimeLimit�֐��̏I���j
				else if (Finish == 6) {
					CountJ = 0;//�J�E���^�[�̃��Z�b�g
					Finish = 0;//�����l�ɖ߂�
					return TimeFrame / (float)FPS;//�^�C���X�R�A�[��߂�l�Ƃ���
				}
				//�N���A�[���b�Z�[�W�̕\��
				switch (ShowMsgBox(Msg_End, &MsgBox_End)) {
				case 6: Finish++;//���̃��b�Z�[�W�̏����܂���TimeLimit�֐��̏I��
				}
			}
		}
		//�k�^�C���A�b�v�l
		else if (Scene == 2) {
			static int Scroll = 0;//���胁�b�Z�[�W�̃X�N���[����
			static int Count = 0;
			Count++;
			//���^�C���A�b�v���b�Z�[�W�̍쐬
			if (Count == 1) {
				//�i�p�b�h�̔�A�N�e�B�u���j
				PadManager.Active = 0;
				//�i�^�C���A�b�v���b�Z�[�W�̍쐬�j
				PlaySoundMem(DamageSound, DX_PLAYTYPE_BACK, TRUE);
				strcpy(Msg_Judge, "<p> Time up! </p>");//���Ԑ؂ꃁ�b�Z�[�W���擾����
				Reparse(&MsgBox_Judge);//�^�O�̍ēǂݍ��ݎw��
				//�i�^�C���A�b�v���b�Z�[�W�̐F�̕ύX�j
				MsgBoxForm_Judge.FontColor = GetColor(255, 102, 0);
				MsgBoxForm_Judge.BorderColor = GetColor(255, 102, 0);
				//�i�W���C�p�b�h�̐U���J�n�j
				StartJoypadVibration(DX_INPUT_PAD1, 1000, 250);
			}
			//���^�C���A�b�v���b�Z�[�W�̕\��
			else if (1 < Count && Count < FPS) {
				MsgBox_Judge.Location[1] = MonsterBaseLine2 - 50 - Scroll;//���胁�b�Z�[�W�̕\���ʒu�̎w��
				Scroll += 2;//���胁�b�Z�[�W�̃X�N���[���ʂ̍X�V
				//�i��ʂ̐U���j
				if (Count % 2 == 0) Entire.Location[1] = -5;
				else Entire.Location[1] = 0;
			}
			//�i�I���j
			ShowMsgBox(Msg_Judge, &MsgBox_Judge);
			if (Count >= FPS * 2) {
				//�i�s�탁�b�Z�[�W�̏����j
				if (Count == FPS * 2) strcpy(Msg_End, "<p>�����񂬂�ł��B</p>");
				//�iTimeLimit�֐��̏I���j
				static int Finish = 0;
				if (Finish == 1) {
					Scroll = 0;	Count = 0;//�����l�ɖ߂�
					Finish = 0;//�����l�ɖ߂�
					return -1;//TimeLimit�֐��̏I���i-1��߂�l�Ƃ���j
				}
				//�s�탁�b�Z�[�W�̕\��
				switch (ShowMsgBox(Msg_End, &MsgBox_End)) {
				case 6: Finish++;//�֐��̏I��
				}
			}

		}
		//���J�n��
		if (Scene == -2) {
			static int BlindColor = GetColor(0, 0, 0);
			static int Count = 0;
			int Add = Count * 360 / FPS;
			DrawBox(0, 0, WindowWidth, WindowHeight / 2 - Add, BlindColor, true);
			DrawBox(0, WindowHeight / 2 + Add, WindowWidth, WindowHeight, BlindColor, true);
			if (Add >= WindowHeight / 2) { Scene = -1; TimeFlag = 1; Count = 0; }//�o�ߎ��Ԃ�i�߂�
			Count++;
		}
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//�m�N���ɔ��������n�@
	//��DX���C�u�����̐ݒ聫////
	SetWaitVSyncFlag(FALSE);//���������M�����I�t
	ChangeWindowMode(true); //�E�B���h�E���[�h�̐؂�ւ�
	if (DxLib_Init() == -1) return -1; //DX���C�u��������������
	if (ActiveMath_Init() == -1) return -1; //ActiveMath�̏���������
	SetDrawScreen(DX_SCREEN_BACK); //�`���𗠉�ʂɐݒ�
	SetGraphMode(WindowWidth, WindowHeight, ColorBitNum); //�E�C���h�E�T�C�Y�̎w��

	//���t�H���g�֌W�̐ݒ�
	SetFontSize(24); //�t�H���g�T�C�Y�̎w��
	ChangeFont("UD �f�W�^�� ���ȏ��� N-R"); //�t�H���g�̎w��
	SetFontThickness(0);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);

	//�m�^�C���X�R�A�[�G���A�n�m�v���C���[�̃X�e�[�^�X�G���A�n
	struct AREACONTROL StatusArea[2] = { 0 };//[0]�F�^�C���X�R�A�[�G���A�@[1]�F�v���C���[�̏�ԃG���A
	int AreaKosuu;
	LoadAreaSet(".\\File\\StatusArea.csv", StatusArea, &AreaKosuu, 2, NULL);
	StatusArea[0].Location[0] = (WindowWidth - StatusArea[0].Width) / 2;
	StatusArea[0].Location[1] = (WindowHeight - (StatusArea[0].Height + StatusArea[1].Margin[1] + StatusArea[1].Height)) / 2;
	//�m�v���C���[�n
	struct PLAYER Player = { 0 };
	strcpy(Player.Name, "�䂤����");
	Player.Level = 5;
	Player.Exp = 499;
	Player.Coin = 50;

	//�m�^�C���A�^�b�N���[�h�n
	float Time = TimeLimit(&Player);
	//�m�^�C���X�R�A�[�E�v���C���[�̃X�e�[�^�X�̕\�����[�h�n
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !MathgpUpdateJoypad()) {
		//������������ҋ@
		SleepToFitFPS(FPS);
		//���G���A
		ShowArea(StatusArea, AreaKosuu);
		//������
		static int TextColor = GetColor(255, 255, 255);
		//�i�^�C���X�R�A�[�j
		if (Time == -1) DrawString(StatusArea[0].Nest[0] + 0, StatusArea[0].Nest[1] + 0, "�^�C���@���Ԑ؂�", TextColor);
		else DrawFormatString(StatusArea[0].Nest[0] + 0, StatusArea[0].Nest[1] + 0, TextColor, "�^�C���@%6.2f�b", Time);
		//�i�v���C���[�̃X�e�[�^�X�j
		static int NameWidth = GetDrawStringWidth(Player.Name, strlen(Player.Name));
		static int NameX = (StatusArea[1].Nest[2] - StatusArea[1].Nest[0] - NameWidth) / 2;
		DrawFormatString(StatusArea[1].Nest[0] + NameX, StatusArea[1].Nest[1], TextColor, "%s", Player.Name);
		DrawLine(StatusArea[1].Nest[0] - StatusArea[1].Padding[0], StatusArea[1].Nest[1] + 28, StatusArea[1].Nest[2] + StatusArea[1].Padding[2], StatusArea[1].Nest[1] + 28, StatusArea[1].BorderColor, 2);
		DrawFormatString(StatusArea[1].Nest[0], StatusArea[1].Nest[1] + 34, TextColor, "���x�� %9d\n�o���l %9d\n�R�C�� %9d", Player.Level, Player.Exp, Player.Coin);
		//���m��{�^���Ŕ�����
		if (Joypad[Action[Act_Confirm]] == 1) break;
	}
	//�m�I���n
	DxLib_End();// �c�w���C�u�����g�p�̏I������
	return -1;// �\�t�g�̏I��
}
//TimeLimit