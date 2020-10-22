#include "ActiveMath.h"
//���O���[�o���ϐ�
int FPS = 60;
int WindowWidth = 1000, WindowHeight = 750, ColorBitNum = 32;
/////���g�b�v��ʁ�////////////���g�b�v��ʁ�////////////���g�b�v��ʁ�////////////���g�b�v��ʁ�//////
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//�m�N���ɔ��������n�@
	//��DX���C�u�����̐ݒ聫////
	SetWaitVSyncFlag(FALSE);//���������M�����I�t
	ChangeWindowMode(true); //�E�B���h�E���[�h�̐؂�ւ�
	if (DxLib_Init() == -1) return -1; //DX���C�u��������������
	if (ActiveMath_Init() == -1) return -1; //ActiveMath�̏���������
	SetDrawScreen(DX_SCREEN_BACK); // �`���𗠉�ʂɐݒ�
	SetGraphMode(WindowWidth, WindowHeight, ColorBitNum); //�E�C���h�E�T�C�Y�̎w��

	//���t�H���g�֌W�̐ݒ�
	SetFontSize(24); //�t�H���g�T�C�Y�̎w��
	ChangeFont("UD �f�W�^�� ���ȏ��� N-R"); //�t�H���g�̎w��
	SetFontThickness(0);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);

	//���w�i�̎w��
	int BackImg = LoadGraph(".\\File\\BGI_01.jpg"); //�w�i�̃��[�h
	//���W���C�p�b�h�̐ݒ�
	LoadJoypadLink(".\\File\\JoypadLink.txt"); //�W���C�p�b�h�̐ݒ�̃��[�h

	//�����b�Z�[�W�G���A�̏�����
	static struct AREACONTROL MessageArea = { 0 };
	MessageArea.BackTransparency = 50;
	MessageArea.BackColor = GetColor(0, 0, 0);
	MessageArea.Width = 647;
	MessageArea.Height = 400;
	MessageArea.Location[0] = (WindowWidth - MessageArea.Width) / 2;
	MessageArea.Location[1] = (WindowHeight - MessageArea.Height) / 2;

	//�m���C�����[�v�n
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !MathgpUpdateJoypad()) {
		//������������ҋ@
		SleepToFitFPS(FPS);
		//���w�i
		DrawGraph(0,0, BackImg, TRUE);
		//�����b�Z�[�W�G���A
		ShowArea(&MessageArea,1);
		//�����b�Z�[�W
		static int TextColor = GetColor(255, 255, 255);
		DrawFormatStringInArea(0, 0, &MessageArea, TextColor, "DrawFormatStringInArea�֐�\n���݁C%s�̂g�o��%d�ł��B", "�䂤����", 273);
		//���I��
		if (Joypad[Action[Act_Confirm]] == 1) break;//Joypad[1]����������I��
	}
	return 0;
}
//DrawFormatStringInArea

