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
	GetCurrentDirectory(MAX_PATH, AppDir);

	//���w�i�̎w��
	int BackImg = LoadGraph(".\\File\\BackImg.jpg"); //�w�i�̃��[�h
	//���W���C�p�b�h�̐ݒ�
	LoadJoypadLink(".\\File\\JoypadLink.txt"); //�W���C�p�b�h�̐ݒ�̃��[�h

	//�m�t�@�C���̃��[�h�n
	//�������X�^�[�̃��[�h
	const int MonsterMax = 500;
	struct Monster Monster[MonsterMax];
	int MonsterKosuu = 0;//�����X�^�[���i���ۂ̌��j
	char ColumnTitle[MONSTER_COLUMNMAX][MONSTER_COLUMNTITLEFIELDMAX + 1] = { 0 };
	int ColumnKosuu = 0;
	LoadMonster(".\\File\\Monster\\Monster.csv", Monster, MonsterMax, &MonsterKosuu, NULL, ColumnTitle, &ColumnKosuu);
	//�������X�^�[�摜�T�C�Y�̎擾
	int MonsterImgWide[MonsterMax];
	int MonsterImgHeight[MonsterMax];//�����X�^�[�̉摜�̏c���T�C�Y���擾���邽�߂̕ϐ�
	for (int i = 0; i < MonsterKosuu; i++) {//�����X�^�[�摜�T�C�Y�̎擾
		GetGraphSize(Monster[i].Img, &MonsterImgWide[i], &MonsterImgHeight[i]); //�����X�^�[�̉摜�̏c���T�C�Y���擾����MonsterImgWide�CMonsterImgHeight�Ɏ擾
	}
	//�������X�^�[�摜�p�X�̃��[�h
	SetCurrentDirectory(AppDir);
	char MonsterImgTitle[MonsterMax][MAX_PATH] = { 0 }; //�S�����X�^�[�̉摜�t�@�C����������z��
	LoadMonsterImgTitle(".\\File\\Monster\\Monster.csv", MonsterImgTitle, MonsterMax);

	//�m���C�����[�v�n
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !MathgpUpdateJoypad()) {
		//������������ҋ@
		SleepToFitFPS(FPS);
		//���w�i
		DrawGraph(0,0, BackImg, TRUE);
		//�������X�^�[
		for (int Num = 0; Num < MonsterKosuu; Num++) {
			//////�����X�^�[�摜
			int Rate = 3;//�k�����̔����irate = 3�ŏk������2/3�j
			int CenterX = 250 * Num + 100;//�摜�̍��E�̒��S
			int CenterY = 150;//�摜�̉��[
			DrawExtendGraph(CenterX - MonsterImgWide[Num] / Rate, CenterY - MonsterImgHeight[Num] * 2 / Rate,
				CenterX + MonsterImgWide[Num] / Rate, CenterY, Monster[Num].Img, TRUE);
			//////�����X�^�[���C�����X�^�[�̃J�����i�����X�^�[ID�i0�ԁj�������j
			static int TextColor = GetColor(0, 0, 0); //�����F�̎w��
			DrawFormatString(250 * Num + 20, 160, TextColor, "���O:%s", Monster[Num].Name);
			for (int k = 0; k < ColumnKosuu; k++) {
				DrawFormatString(250 * Num + 20, 190 + 30 * k, TextColor, "%s:%d", ColumnTitle[k], Monster[Num].Column[k]);
			}
			DrawFormatString(250 * Num + 20, 200 + 30 * ColumnKosuu, TextColor, "�摜:%s", MonsterImgTitle[Num]);
		}
		//���I��
		if (Joypad[Action[Act_Confirm]] == 1) break;//�m��{�^������������I��
	}
	return 0;
}
//LoadMonster+LoadMonsterImgPath