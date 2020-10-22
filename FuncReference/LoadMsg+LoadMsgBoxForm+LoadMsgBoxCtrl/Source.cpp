#include "ActiveMath.h"
//���O���[�o���ϐ�
int FPS = 60;
int WindowWidth = 1000, WindowHeight = 750, ColorBitNum = 32;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//�m�N���ɔ��������n�@
	//��DX���C�u�����̐ݒ聫////
	SetWaitVSyncFlag(FALSE);//���������M�����I�t
	ChangeWindowMode(true); //�E�B���h�E���[�h�̐؂�ւ�
	if (DxLib_Init() == -1) return -1; //DX���C�u��������������
	if (ActiveMath_Init() == -1) return -1; //ActiveMath�̏���������
	SetDrawScreen(DX_SCREEN_BACK); //�`���𗠉�ʂɐݒ�
	SetGraphMode(WindowWidth, WindowHeight, ColorBitNum); //�E�C���h�E�T�C�Y�̎w��

	//���w�i�̎w��
	int BackImg = LoadGraph(".\\File\\BackImg.jpg"); //�w�i�̃��[�h
	//���t�H���g�E�^�O�C����уW���C�p�b�h�̐ݒ�
	LoadMsgCodeLink(".\\File\\Msg\\MsgCodeLink.txt"); //�t�H���g�C�t�H���g�摜�C�^�O�̐ݒ�̃��[�h
	LoadJoypadLink(".\\File\\Msg\\JoypadLink.txt"); //�W���C�p�b�h�̐ݒ�̃��[�h

	//�m���b�Z�[�W�֘A�̐錾�Ə������n�@
	//�����b�Z�[�W�̃��[�h
	const int MsgCharMax = 2000;//�ǂݍ��݉\�ȕ�����
	char Msg[MsgCharMax + 1] = { 0 };//���b�Z�[�W
	LoadMsg(".\\File\\Msg\\Msg01.acm", Msg, MsgCharMax + 1, 1);
	//�����b�Z�[�W�t�H�[���̃��[�h
	static struct MsgBoxForm MsgBoxForm;
	LoadMsgBoxForm(".\\File\\Msg\\MsgBoxForm.txt", &MsgBoxForm, 1);
	//�����b�Z�[�W�{�b�N�X�̃��[�h
	static struct MsgBoxCtrl MsgBox;
	LoadMsgBoxCtrl(".\\File\\Msg\\MsgBoxCtrl.txt", &MsgBox, 1, &MsgBoxForm, 1);
	MsgBox.Location[0] = (WindowWidth - MsgBox.OuterWidth) / 2;
	MsgBox.Location[1] = (WindowHeight - MsgBox.OuterHeight) / 2;


	//�m���C�����[�v�n
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !MathgpUpdateJoypad()) {
		//������������ҋ@
		SleepToFitFPS(FPS);
		//���w�i
		DrawGraph(0,0, BackImg, TRUE);
		//�����b�Z�[�W�{�b�N�X
		if (ShowMsgBox(Msg, &MsgBox) == 6) break;//���b�Z�[�W�̕\���ƃv���O�����̏I��
	}
	return 0;
}
//LoadMsg + LoadMsgBoxForm + LoadMsgBoxCtrl