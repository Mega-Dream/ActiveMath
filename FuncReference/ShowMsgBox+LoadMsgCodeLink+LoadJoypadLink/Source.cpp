#include "ActiveMath.h"

//���O���[�o���ϐ�
int FPS = 60;//�t���[�����[�g
int WindowWidth = 1000, WindowHeight = 750, ColorBitNum = 32;//�E�C���h�E�T�C�Y

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//�m�N���ɔ��������n�@
	//��DX���C�u�����̐ݒ�
	SetWaitVSyncFlag(FALSE); //���������M�����I�t
	ChangeWindowMode(true); //�E�B���h�E���[�h�̐؂�ւ�
	if (DxLib_Init() == -1) return -1; //DX���C�u����������
	if (ActiveMath_Init() == -1) return -1; //ActiveMath�̏���������
	SetDrawScreen(DX_SCREEN_BACK); //�`���𗠉�ʂɐݒ�
	SetGraphMode(WindowWidth, WindowHeight, ColorBitNum); //�E�C���h�E�T�C�Y�̎w��

	//���w�i�̎w��
	int BackImg = LoadGraph(".\\File\\BackImg.jpg"); //�w�i�̃��[�h

	//���t�H���g�E�^�O�C����уW���C�p�b�h�̐ݒ�
	LoadMsgCodeLink(".\\File\\MsgCodeLink.txt"); //�t�H���g�C�t�H���g�摜�C�^�O�̐ݒ�̃��[�h
	LoadJoypadLink(".\\File\\JoypadLink.txt"); //�W���C�p�b�h�̐ݒ�̃��[�h

	//�����b�Z�[�W�̎w��
	const int MsgCharMax = 500;//�ǂݍ��݉\�ȕ�����
	char Msg[MsgCharMax + 1] = "<p>#SetColor(255,204,102)ShowMsgBox�֐�#UstColor{}</p><p>���̌����F<math>#frac(2a;�|b�}#sqrt(#sup(b;2)�[4ac))</math></p>\
<p>��ϕ��̕����ϕ��@�F<math>#int(^��^;a;b;#func(f;x)#func(^#diff(#SetFont(17)g#UstFont{};^��^)^;x);dx\
��#primit(#func(f;x)#func(#SetFont(17)g#UstFont{};x);a;b)�|#int(^��^;a;b;#func(^#diff(f;^��^)^;x)#func(#SetFont(17)g#UstFont{};x);dx))</math></p>\
<p>�摜�iae�j�F#img_ae{.\\img_01.png}</p>";
	static struct MsgBoxForm MsgBoxForm; //���b�Z�[�W�{�b�N�X�t�H�[��
	static struct MsgBoxCtrl MsgBox; //���b�Z�[�W�{�b�N�X
	MsgBox.MsgBoxForm_p = &MsgBoxForm; //���b�Z�[�W�{�b�N�X�t�H�[���̃|�C���^�[
	MsgBox.Location[0] = (WindowWidth - MsgBox.OuterWidth) / 2;
	MsgBox.Location[1] = (WindowHeight - MsgBox.OuterHeight) / 2;

	//�m���C�����[�v�n
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !MathgpUpdateJoypad()) {
		//������������ҋ@
		SleepToFitFPS(FPS);
		//���w�i
		DrawGraph(0,0, BackImg, TRUE);
		//�����b�Z�[�W�{�b�N�X
		ShowMsgBox(Msg, &MsgBox);
		//���I��
		if (Joypad[Action[Act_Confirm]] == 1) break;//Joypad[1]����������I��
	}
	return 0;
}
//ShowMsgBox+LoadMsgCodeLink+LoadJoypadLink
