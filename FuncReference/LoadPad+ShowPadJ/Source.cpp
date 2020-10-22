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

	//���t�H���g�֌W�̐ݒ�
	SetFontSize(24); //�t�H���g�T�C�Y�̎w��
	ChangeFont("UD �f�W�^�� ���ȏ��� N-R"); //�t�H���g�̎w��
	SetFontThickness(0);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);

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
	static struct INPUTTEXTBUTTONCTRL* ButtonSet_hh[] = { Button0, Button1, Button2, Button3, Button4, Button5	};//�e�V�[�g�����{�^���z��̐擪�A�h���X
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
	int Error = LoadPad(FilePath_Pad, PadAreaSet, &PadAreaKosuu, PadAreaMax, NULL,//�e�G���A�Ȃ��iNULL�j
		ButtonFormSet, &ButtonFormKosuu, ButtonFormMax,
		IndexSet, &IndexKosuu, IndexMax,
		ButtonSet_hh, ButtonKosuu, ButtonMax,
		BaseButtonSet, &BaseButtonKosuu, BaseButtonMax,
		Msg_Pad, MsgCharMax_Pad + 1, 0, &MsgBoxForm_Pad, MsgBoxFormKosuu_Pad, &MsgBox_Pad, MsgBoxKosuu_Pad, 1, 1//�t�H���g�E�^�O�����[�h����i�O�ȊO�j//�W���C�p�b�h�̊��蓖�Ă����[�h����i�O�ȊO�j
	);
	//�i�p�b�h���b�Z�[�W�{�b�N�X�̈ʒu�w��j
	MsgBox_Pad.Location[0] = 100;
	MsgBox_Pad.Location[1] = 100;
	//�i�p�b�h�p�b�h�G���A�̃p�����[�^�̈ʒu�w��j
	PadAreaSet[0].Location[0] += MsgBox_Pad.Location[0];//���b�Z�[�W�{�b�N�X�Ɠ����ʒu���w��
	PadAreaSet[0].Location[1] += MsgBox_Pad.Location[1];//���b�Z�[�W�{�b�N�X�̒������w��

	//�����b�Z�[�W�C���b�Z�[�W�{�b�N�X�̏������p�R�s�[�̎擾
	struct MsgBoxCtrl MsgBox_Pad_Copy = MsgBox_Pad;//
	char Msg_Copy[MsgCharMax_Pad + 1];
	strcpy(Msg_Copy, Msg_Pad);

	//�m���C�����[�v�n
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !MathgpUpdateJoypad()) {
		//������������ҋ@
		SleepToFitFPS(FPS);
		//���w�i
		DrawGraph(0, 0, BackImg, TRUE);
		//���p�b�h�̕\���E���b�Z�[�W�{�b�N�X�̕\���E���b�Z�[�W�̃W���C�p�b�h����
		int ShowMsgBoxFlag = 1;
		if (ShowPadJ(Msg_Pad, &MsgBox_Pad, MsgCharMax_Pad + 1, ShowMsgBoxFlag, IndexSet, IndexKosuu, ButtonSet_hh, ButtonKosuu, BaseButtonSet, BaseButtonKosuu, PadAreaSet, &PadManager) == 1) {//�v�b�V�������������P�̂Ƃ�
			//���m��{�^��
			if (PadManager.PushedNo == 35 && PadAreaSet[2].Active == 1) {//�x�[�X�{�^����35�ԁi�m��{�^���j���N���b�N�����B�@�x�[�X�{�^���F1000�ԑ�
				strcpy(Msg_Pad, Msg_Copy);//���b�Z�[�W���N���A
				Reparse(&MsgBox_Pad);//�^�O�̍ēǂݍ��ݎw���i�����{�b�N�X��\�������邽�߁j
				MsgBox_Pad.Tag[0].PositionP = 0;//ActiveElement��0�Ƀ��Z�b�g���ăJ�[�\���ʒu���Č��o
			}
		}
		//�������Ŋm��
		if (MsgBox_Pad.Condition == 101) {
			MsgBox_Pad.Condition = 1;//���񂱂��ɓ����Ă��Ȃ��悤�ɂP�ɖ߂�
			strcpy(Msg_Pad, Msg_Copy);//���b�Z�[�W���N���A
			Reparse(&MsgBox_Pad);//�^�O�̍ēǂݍ��ݎw���i�����{�b�N�X��\�������邽�߁j
			MsgBox_Pad.Tag[0].PositionP = 0;//ActiveElement��0�Ƀ��Z�b�g���ăJ�[�\���ʒu���Č��o
		}
		//���I��
		static int TextColor = GetColor(0, 0, 0);
		DrawString(PadAreaSet[2].Location[0], PadAreaSet[2].Location[1] + PadAreaSet[2].Height, "�W���C�p�b�h��[10]����������I��", TextColor); //������
		if (Joypad[10] == 1)  break;//Joypad[10]����������I��
	}
	return 0;
}
//LoadPad+ShowPadJ