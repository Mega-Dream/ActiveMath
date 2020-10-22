#include "ActiveMath.h"
//���O���[�o���ϐ�
int FPS = 60;
int WindowWidth = 1000, WindowHeight = 750, ColorBitNum = 32;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//�m�N���ɔ��������n�@
	//��DX���C�u�����̐ݒ�
	SetWaitVSyncFlag(FALSE);//���������M�����I�t
	ChangeWindowMode(true); //�E�B���h�E���[�h�̐؂�ւ�
	if (DxLib_Init() == -1) return -1; //DX���C�u��������������
	if (ActiveMath_Init() == -1) return -1; //ActiveMath�̏���������
	SetDrawScreen(DX_SCREEN_BACK); //�`���𗠉�ʂɐݒ�
	SetGraphMode(WindowWidth, WindowHeight, ColorBitNum); //�E�C���h�E�T�C�Y�̎w��

	//���w�i�̎w��
	int BackImg = LoadGraph(".\\File\\BackImg.jpg"); //�w�i�̃��[�h

	//�m���֘A�̐錾�Ə������n�@
	//�����̃��[�h
	struct Kadai Mondai = { 0 };
	int SyoumonKosuu;
	LoadMondai(".\\File\\Mondai\\Mondai01.ack", &Mondai, &SyoumonKosuu, 1);
	//�����b�Z�[�W�֘A�t�@�C���̃��[�h�i���b�Z�[�W�t�H�[���C���b�Z�[�W�{�b�N�X�C�ݒ�i�t�H���g�C�t�H���g�摜�C�^�O�ݒ�j�j
	const int MsgBoxFormKosuu = 2;
	static struct MsgBoxForm MsgBoxForm[MsgBoxFormKosuu];
	const int MsgBoxKosuu = 4;
	static struct MsgBoxCtrl MsgBox[MsgBoxKosuu];
	LoadMsgSet(LocalDir, MsgBoxForm, MsgBoxFormKosuu, MsgBox, MsgBoxKosuu, 1, 1);//�t�H���g�E�^�O�����[�h����i�O�ȊO�j//�W���C�p�b�h�̊��蓖�Ă����[�h����i�O�ȊO�j
	for (int i = 0; i < MsgBoxKosuu; i++) MsgBox[i].Location[0] = 80;
	MsgBox[0].Location[1] = 200;
	MsgBox[2].Location[1] = 400;
	//������E���␳���R���g���[���̕���
	static struct MsgBoxCtrl MsgBox_Syoumon[SYOUMON_MAX];
	static struct MsgBoxCtrl MsgBox_SyoumonSeikai[SYOUMON_MAX];
	for (int Num = 0; Num < SyoumonKosuu; Num++) {
		MsgBox_Syoumon[Num] = MsgBox[2];
		MsgBox_SyoumonSeikai[Num] = MsgBox[3];
	}
	//�������X�^�[�̃��[�h
	const int MonsterMax = 500;
	struct Monster Monster[MonsterMax];
	int MonsterKosuu = 0;//�����X�^�[���i���ۂ̌��j
	char ColumnTitle[MONSTER_COLUMNMAX][MONSTER_COLUMNTITLEFIELDMAX + 1] = { 0 };
	int ColumnKosuu = 0;
	LoadMonster(".\\Monster\\Monster.csv", Monster, MonsterMax, &MonsterKosuu, NULL, ColumnTitle, &ColumnKosuu);
	//�������X�^�[�ԍ��̊m��i�Y�����Ȃ����0�̂܂܁j
	int MonsterNum = 0;//�����X�^�[�̗v�f�ԍ�
	for (int i = 0; i < MonsterKosuu; i++) {
		if (Mondai.monsterID == Monster[i].Column[0]) {
			MonsterNum = i; break;
		}
	}

	//�m���C�����[�v�n
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !MathgpUpdateJoypad()) {
		//������������ҋ@
		SleepToFitFPS(FPS);
		//���w�i
		DrawGraph(0,0, BackImg, TRUE);
		//�������X�^�[
		static int TextColor = GetColor(255, 255, 255); //�����F�̎w��
		DrawGraph(80, 50, Monster[MonsterNum].Img, TRUE);//�����X�^�[�摜
		DrawFormatString(700, 50, TextColor, "%s:%d", ColumnTitle[0], Mondai.monsterID);//�����X�^�[ID
		DrawFormatString(700, 80, TextColor, "���O:%s", Monster[MonsterNum].Name);//�����X�^�[��

		for (int k = 1; k < ColumnKosuu; k++) {
			DrawFormatString(700, 80 + 30 * k, TextColor, "%s:%d", ColumnTitle[k], Monster[MonsterNum].Column[k]);//�����X�^�[�̃J�����i�����X�^�[ID�i0�ԁj�������j
		}
		//�����
		//�t���O
		static int KakioeChecker = 0;//Condition�i4�F���b�Z�[�W�̍Ō�܂ŏ����o���ς݁j
		static int PushCounter = 0;//Enter�L�[����������
		//�i���j
		KakioeChecker = ShowMsgBox(Mondai.daimon, &MsgBox[0]);//���̏����o��
		//�i��␳���j
		if (0 < PushCounter) {
			MsgBox[1].Location[0] = MsgBox[0].Location[0] + MsgBox[0].OuterWidth;//���̉E
			MsgBox[1].Location[1] = MsgBox[0].Location[1];//�c�͑��Ɠ���
			ShowMsgBox(Mondai.daimonseikai, &MsgBox[1]);//��␳���̏����o��
		}
		for (int Num = 0; KakioeChecker >= 4 && Num < SyoumonKosuu; Num++) {//Num�F����ԍ�
			//�i����j
			if (Num > 0) MsgBox_Syoumon[Num].Location[1] = MsgBox_Syoumon[Num - 1].Location[1] + MsgBox_Syoumon[Num - 1].OuterHeight;//0�Ԃ̏���ȊO�́C�O�̏���̒���
			KakioeChecker = ShowMsgBox(Mondai.syoumon[Num], &MsgBox_Syoumon[Num]);//����̏����o��
			//�i���␳���j
			if (Num < PushCounter - 1) {
				MsgBox_SyoumonSeikai[Num].Location[0] = MsgBox_Syoumon[Num].Location[0] + MsgBox_Syoumon[Num].OuterWidth;//����̉E
				MsgBox_SyoumonSeikai[Num].Location[1] = MsgBox_Syoumon[Num].Location[1];//�c�͏���Ɠ���
				ShowMsgBox(Mondai.syoumonseikai[Num], &MsgBox_SyoumonSeikai[Num]);//���␳���̏����o��
			}
		}
		//���m��{�^�����������񐔂��L�^
		if (Joypad[Action[Act_Confirm]] == 1 && KakioeChecker >= 4) PushCounter++;//���ׂĂ̏���������I���ς݂Ȃ�PushCounter�̒l�𑝂₷
		//���I��
		if (PushCounter > SyoumonKosuu + 1) break;//�m��{�^�����������񐔂��S��𒴂�����I��
	}
	return 0;
}
//LoadMondai+LoadMsgSet+LoadMonster