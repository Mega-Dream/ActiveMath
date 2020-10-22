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

	//���w�i�̎w��
	int BackImg = LoadGraph(".\\File\\BGI_01.jpg"); //�w�i�̃��[�h

	//���t�H���g�E�^�O�C����уW���C�p�b�h�̐ݒ�
	LoadMsgCodeLink(".\\File\\MsgCodeLink.txt"); //�t�H���g�C�t�H���g�摜�C�^�O�̐ݒ�̃��[�h
	LoadJoypadLink(".\\File\\JoypadLink.txt"); //�W���C�p�b�h�̐ݒ�̃��[�h

	//�m�e�G���A�E�c�[���{�^���ނ̏������n�@
	//�����b�Z�[�W�G���A�̏�����
	static struct AREACONTROL MessageArea = { 0 };
	MessageArea.BackTransparency = 50;
	MessageArea.BackColor = GetColor(0, 0, 0);
	MessageArea.Width = 600;
	MessageArea.Height = 48;
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

		//�����b�Z�[�W�C�^�O
		const int TagHairetsuMax = 15; //�ǂݍ��݉\�ȃ^�O�̌�
		static struct Tag Tag[TagHairetsuMax + 1];//�v���X�P��tag[0]�̕�
		static char ParsedMsg[300 + 1] = { 0 }; //�^�O�𔲂������������
		static int Msg_TextColorRGB[3] = { 255, 255, 255 }; //�����F
		static int Msg_TextColor = GetColor(Msg_TextColorRGB[0], Msg_TextColorRGB[1], Msg_TextColorRGB[2]); //�����F�̃n���h��
		if (int Value = DrawMsg(0, 0, "<p>#SetColor(255,204,102)DrawMsg�֐�#UstColor{}�@�����F<math>#frac(2;1)</math></p>", Msg_TextColorRGB, Msg_TextColor, &MessageArea, TagHairetsuMax, Tag, ParsedMsg)) {
			if (Value == -1) {
				//�G���[�F�|�P�F�^�O�𔲂�����������񂪃J��  �|�P�O�P�F�^�O�̍ő���𒴂��Ă���i����̂�-101�ŁC���̌��-1�i�^�O�𔲂�����������񂪃J���j�ƂȂ�j
			}
			else {
				//������
			}
		}
		//���I��
		if (Joypad[Action[Act_Confirm]] == 1) break;//Joypad[1]����������I��
	}
	return 0;
}
//DrawMsg

