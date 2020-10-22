#pragma once
////////////
#define _CRT_SECURE_NO_WARNINGS//strcpy�̃o�b�t�@�I�[�o�[�̌x�����~�߂邽�߂ɂ���B

#include "DxLib.h"
//#include <string.h>//������p
//#include <stdlib.h>//�I������exit()�֐��������Ă��� itoa�֐��iint����char�ւ̕ϊ��j

namespace ActiveMath {
#define JoypadInputMax 31//�O�Ԃ͎g�p���Ă��Ȃ�
//���A�N�V�����ԍ��̒�`
#define ActMax 50//�O�Ԃ͎g�p���Ă��Ȃ�
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

////////�@�ρ@���@////////
	//���ϐ�
	extern int MouseX;
	extern int MouseY;
	extern int Key[256];
	extern int Mouse[10];
	extern int JoypadInputMode;
	extern int Joypad[JoypadInputMax];// �W���C�p�b�h�̃{�^����������Ă���t���[������
	//extern int ChangedJoypadNum[JoypadInputMax];
	extern int Action[ActMax];

	extern int SystemFontSize;

	////////////////////////////

	extern char Dir_FontStyle[MAX_PATH];//�t�H���g�X�^�C���̃f�B���N�g��
	extern char Dir_FontStyle_rw[MAX_PATH];//�t�H���g�X�^�C���̃f�B���N�g��
	extern char Title_FontStyle[MAX_PATH];//�t�H���g�X�^�C���̃t�@�C����
	extern char Title_FontStyle_rw[MAX_PATH];//�t�H���g�X�^�C���̃t�@�C����

	extern char Dir_FontImgStyle[MAX_PATH];//�t�H���g�摜�X�^�C���̃f�B���N�g��
	extern char Dir_FontImgStyle_rw[MAX_PATH];//�t�H���g�摜�X�^�C���̃f�B���N�g��
	extern char Title_FontImgStyle[MAX_PATH];//�t�H���g�摜�X�^�C���̃t�@�C����
	extern char Title_FontImgStyle_rw[MAX_PATH];//�t�H���g�摜�X�^�C���̃t�@�C����

	extern char Dir_TagStyle[MAX_PATH];//�^�O�X�^�C���̃f�B���N�g��
	extern char Dir_TagStyle_rw[MAX_PATH];//�^�O�X�^�C���̃f�B���N�g��
	extern char Title_TagStyle[MAX_PATH];//�^�O�X�^�C���̃t�@�C����
	extern char Title_TagStyle_rw[MAX_PATH];//�^�O�X�^�C���̃t�@�C����

	extern char Dir_AppImg[MAX_PATH];//�A�v�����L�摜�̃f�B���N�g��
	extern char Dir_AppImg_rw[MAX_PATH];//�A�v�����L�摜�̃f�B���N�g��
	extern char Dir_AppSound[MAX_PATH];//�A�v�����L�����̃f�B���N�g��
	extern char Dir_AppSound_rw[MAX_PATH];//�A�v�����L�����̃f�B���N�g��

	/////////////////////////////////////////////////////////////////////

	extern char Dir_JoypadStyle[MAX_PATH];//�W���C�p�b�h�X�^�C���̃f�B���N�g��
	extern char Dir_JoypadStyle_rw[MAX_PATH];//�W���C�p�b�h�X�^�C���̃f�B���N�g��
	extern char Title_JoypadStyle[MAX_PATH];//�W���C�p�b�h�X�^�C���̃t�@�C����
	extern char Title_JoypadStyle_rw[MAX_PATH];//�W���C�p�b�h�X�^�C���̃t�@�C����

	/////////////////////////////////////////////////////////////////////
	extern char AppDir[MAX_PATH];//�v���O�����̒����̃p�X
	extern char LocalDir[MAX_PATH];
	extern char MsgDir[MAX_PATH];

	extern const char *CursorOverString_p;

////////�@�\�@���@�́@�́@��@�`�@////////
	//���G���A
	struct AREA_CTRL {//�e�R���g���[���Ɋ֘A�t������G���A
		struct AREA_CTRL *ParentArea_p = NULL;//�e�G���A�i�n�_�Ƒ傫���̏��j�̃|�C���^�[
		int Location[2] = { 0 };//�R���g���[���̍��W�i[0]���[[1]��[�j�i-111111�F�P�O�̃G���A�̏I�_�ɂ�������@-222222�F�P�O�̃G���A�̎n�_�ɂ��낦��j
		int Margin[4] = { 0 };//��������܂ł̋���
		int BorderThickness = 0;//�g���̑���
		int BorderType = 0;
		int Padding[4] = { 0 };//���b�Z�[�W�{�b�N�X���Ń��b�Z�[�W�܂ł̋����i[0]���p�f�B���O[1]��p�f�B���O[2]�E�p�f�B���O[3]���p�f�B���O�j	
		int Width = 0;//�R���g���[���̕�
		int Height = 0;//�R���g���[���̍���
		int BackTransparency = 0;//�w�i�̓��ߓx�i%�j
		int BackColor = NULL;//�w�i�F�̃n���h��
		int BorderColor = NULL;//�g���̐F
		int Active = 1;//�i-�P�F��\���@�O�F�g�p�s��ԁi�{�^���̃^�C�g���𔖂��\�����Ė������j�@�P�F�ҋ@��ԁi�{�^���̕\���E�����j�@�Q�F�{�^����\�����邪�������j
		//���̓p�b�h�i�W���C�p�b�h�p�j�ł́C�{�^���G���A�ƃx�[�X�{�^���G���A��Active�̃��Z�b�g���C������P�ő�����0�ɂ���̂�Y��Ȃ�����

		int Nest[4] = { 0 };//�e�R���g���[���̎n�_�Ƒ傫���ix1, y1, ���C�����j
		int BackImg = -1;//
		int Line[4] = { 0 };//�⏕���̎n�_�ƏI�_�i�R���g���[���̃{�b�N�X���ォ��̈ʒu�j
		int Range[4];

	};
	//�����X�g
	struct LIST_CTRL {//�e�R���g���[���Ɋ֘A�t������G���A
		struct BTN_CTRL *ParentBtn_p = NULL;//�e�{�^���̃|�C���^�[
		int BorderThickness = 0;//�g���̑���
		int Padding[4] = { 0 };//���b�Z�[�W�{�b�N�X���Ń��b�Z�[�W�܂ł̋����i[0]���p�f�B���O[1]��p�f�B���O[2]�E�p�f�B���O[3]���p�f�B���O�j	
		int Width = 0;//�R���g���[���̕�
		int Height = 0;//�R���g���[���̍���
		int BackTransparency = 0;//�w�i�̓��ߓx�i%�j
		int BackColor;//�w�i�F�̃n���h��
		int BorderColor;//�g���̐F�̃n���h��
		int CursorColor;//�J�[�\���F�̃n���h��
		int Active = -1;//�i-�P�F��\���@�O�F�g�p�s��ԁi�{�^���̃^�C�g���𔖂��\�����Ė������j�@�P�F�ҋ@��ԁi�{�^���̕\���E�����j�@�Q�F�{�^����\�����邪�������j
		int RowKosuu = 1;
		int RowPadding[4] = { 0 };
		int RowWidth = 0;
		int RowHeight = 0;

		int Nest[2] = { 0 };//�e�R���g���[���̎n�_�Ƒ傫���ix1, y1�j

		//���̓p�b�h�i�W���C�p�b�h�p�j�ł́C�{�^���G���A�ƃx�[�X�{�^���G���A��Active�̃��Z�b�g���C������P�ő�����0�ɂ���̂�Y��Ȃ�����
	};
	//�����X�g
	struct LISTROW_CTRL {
		struct LIST_CTRL *List_p = NULL;//�e�{�^���̃|�C���^�[
		char Title[50 + 1];
		int Active = 1;
	};
	//���{�^���t�H�[��
	struct BTN_FORM {//�e�R���g���[���Ɋ֘A�t������G���A
		////////////////////
		//�f�U�C����
		int BorderColor = NULL;//
		int WaitingColor = NULL;//�w�i�F�̃n���h���i�w�肵�Ȃ��j
		int CursorColor = NULL;//�w�i�F�̃n���h���i�w�肵�Ȃ��j
		int PushedColor = NULL;//�w�i�F�̃n���h���i�w�肵�Ȃ��j
		int BackTransparency = 0;//�w�i�̓��ߓx�i%�j
		//Sound����̑��΃p�X�܂��̓t�@�C�������烍�[�h�����n���h��
		int PushSound = -1;//�{�^���v�b�V�����@�@���n���h���̎擾�Ɏ��s���̓n���h����-1��Log.txt�ɏ������܂��B�p�X��0��NULL�Ȃ烍�[�h���Ȃ��̂Ńn���h����-1�ƂȂ邪�CLog.txt�ɏ������܂�Ȃ��B
		int MoveSound = -1;//�{�^���ړ����@�@�@�@���n���h���̎擾�Ɏ��s���̓n���h����-1��Log.txt�ɏ������܂��B�p�X��0��NULL�Ȃ烍�[�h���Ȃ��̂Ńn���h����-1�ƂȂ邪�CLog.txt�ɏ������܂�Ȃ��B
		//����
		int Margin[4] = { 0 };//��������܂ł̋���
		int BorderThickness = 0;//�g���̑���
	};

	//���{�^��
	struct BTN_CTRL {//�e�R���g���[���Ɋ֘A�t������G���A
		struct AREA_CTRL *ParentArea_p;//�G���A�i�n�_�Ƒ傫���̏��j�̃|�C���^�[�i���[�h���̓G���A�̗v�f�ԍ��Ń|�C���^�[���w��j
		char Title[50 + 1];//�{�^���\�ʂɕ\�����镶����
		char String[50 + 1];//�}�E�X�|�C���^�[���w�����Ƃ��ɕ\�����镶����
		int DialImg = -1;
		int Location[2] = { 0 };//�R���g���[���̍��W�i[0]���[[1]��[�j�i-1�F�P�O�̃G���A�̎n�_�ɂ��낦��@-2�F�P�O�̃G���A�̏I�_�ɂ�������j
		int Padding[4] = { 0 };//��������e���܂ł̋����i[0]���p�f�B���O[1]��p�f�B���O[2]�E�p�f�B���O[3]���p�f�B���O�j	�i[0]��-1�Ȃ獶�E�Z���^�����O�C[1]��-1�Ȃ�㉺�Z���^�����O�j
		int Active = -1;//�i-�Q�F�g�p�s�̃J�[�\����ԁi�����\�����Ė������j�@-�P�F��\���@�O�F�g�p�s��ԁi�����\�����Ė������j�@�P�F�ҋ@��ԁi�{�^���̕\���E�����j�@�Q�F�����ꂽ��ԁ@�R�F�J�[�\���j
		int Up = 0;
		int Down = 0;
		int Left = 0;
		int Right = 0;
		//���[�h���Ȃ��p�����[�^
		int Nest[4] = { 0 };//���e���Ɉ����p�����W�i�A�v���P�[�V�����̃E�B���h�E�x�[�X�j�{�^���̃l�X�g��box�̕����i�}�[�W���͊܂܂Ȃ��B�y�A�����g�G���A��Nest���p���B�j
		////////////////////
		struct BTN_FORM *BtnForm_p;
		//Img����̑��΃p�X�܂��̓t�@�C�������烍�[�h�����n���h��
		int CursorImg = -1;//�@�@���n���h���̎擾�Ɏ��s�����n���h����-1��Log.txt�ɏ������܂��B�p�X��-1�Ȃ烍�[�h���Ȃ��̂Ńn���h����-1�ƂȂ邪�CLog.txt�ɏ������܂�Ȃ��B
		int WaitingImg = -1;//�@�@���n���h���̎擾�Ɏ��s�����n���h����-1��Log.txt�ɏ������܂��B�p�X��-1�Ȃ烍�[�h���Ȃ��̂Ńn���h����-1�ƂȂ邪�CLog.txt�ɏ������܂�Ȃ��B
		int PushedImg = -1;//�@�@���n���h���̎擾�Ɏ��s�����n���h����-1��Log.txt�ɏ������܂��B�p�X��-1�Ȃ烍�[�h���Ȃ��̂Ńn���h����-1�ƂȂ邪�CLog.txt�ɏ������܂�Ȃ��B
		int Width = 0;//�R���g���[���̕�
		int Height = 0;//�R���g���[���̍���
	};
#define INPUTTEXTBUTTON_FIELDSIZE 1500//���␳���̏������݉\�T�C�Y�i\0���܂܂Ȃ��j

	//����������̓{�^��
	struct INPUT_TEXT_BTN_CTRL {
		struct BTN_CTRL Btn;//�|�C���^�[�ŋ��L����̂ł͂Ȃ��C����BTN_CTRL������
		char PutText[INPUTTEXTBUTTON_FIELDSIZE + 1]; //���͂���镶�� �@�ϕ��Ȃ�<se2>*</se2>��12�����@�^�O��6�@�S�̂�71����
		int Start;
		int BtnType;//�P�F�����@�Q�F���̑�
	};
	//���^�O
	struct TAG {
		int TagStyleNo = 0;//{}�܂���;�`���̂��߂ɒ�`�^�O���L�^����
		int Parent = 0;//�e�^�O�̔ԍ��@��oyatagno

		char Name[10 + 1] = { 0 };//�^�O�v�f��
		int Post = 0;//�|�X�g�i�P�T�F���s�E�ܕԂ��֎~�̃u���b�N�@�R�F���s�֎~�̃u���b�N�@�P�F�����o�[�@�O�F���̑��@�|�P�F�J���̃����o�[�j
		int Control = -1;//TagType�@�@�@Tag[0]��ClickMoji�̑�p������Tag[0]=-1
		int Pattern = 0;//���̑����i�s�N�Z�����j�@�l��0�łȂ��Ƃ��ɐ��̕`�揈�����s��lineH
		int ArgX = 0;//�g�ʒu�܂��͕����ʒu�����X�����̈ʒu�@�����T�C�Y�ɑ΂��銄���i���jlineX
		int ArgY = 0;//�g�ʒu�܂��͕����ʒu����̂������̈ʒu�@�����T�C�Y�ɑ΂��銄���i���jlineY
		int ArgM = 0;//�}���`�ȃv���p�e�BMultiple
		int CharSize = 0;//�����̃T�C�Y�i�������C�e�^�O�̕����T�C�Y�~CharRate/100�Ƃ��ė^������j��mojisize
		int Padding[4] = { 0 };//�����T�C�Y�ɑ΂��銄��
		int ToTheHead = 0;//�����o���̃c���̗L���iToTheHead�̒l�@0�F�e�^�O�̏����I���ʒu�@�P�F�e�^�O�̏����o���ʒu�j
		int ConnectionP = 0;//0�F�e��CharLocY�������i�e���������j�@1�F�e��LocationY�������i�e�g�����j
		int PositionP = 0;//�ʒu�iConnectionP��0�Ȃ�e�^�O��CharSize�ɑ΂��銄���i���j�Ŏw��CConnectionP��1�Ȃ�e�^�O��Height�ɑ΂��銄���i���j�Ŏw��j�@��oyamojiidou
		int ConnectionM = 0;//0�F������CharLocY�������i�q���������j�@1�F������LocationY�������i�q�g�����j
		int PositionM = 0;//�ʒu�iConnectionM��0�Ȃ�CharSize�ɑ΂��銄���i���j�Ŏw��CConnectionM��1�Ȃ�Height�ɑ΂��銄���i���j�Ŏw��j�@��komojiidou

		int LocationX = 0;//�������̃^�O���Ƃɂ��Ă̕��������o���ʒu�@��kakidashi
		int LocationY = 0;//�g�̏㕔�̈ʒu�@��wakuichi
		int CharLocY = 0;//�c�����̕����ʒu�iLocationY����̑��Έʒu�j�@��mojiichi
		int Width = 0;//���@��kakioe����߂ɂ��ĕ��ň������Ƃɂ���
		int Height = 0;//�g�̏c�T�C�Y�i�������i�q�^�O���ł���܂Łj�͕����T�C�Y�Ɠ����l�j�@��wakutate
		int FirstNumInParsedMsg = 0;//�K�p�J�n�ʒu�@��kaishi
		int LastNumInParsedMsg = 0;//�K�p�I���ʒu�@��syuuryou
		int MemberCount = 0; //�����o�[�^�O�̏o�����B�����l�͂O�B�����o�[�����u���b�N�̂ݎg�p�B
		int TagSign = 1;//�Q�̔{���iTagType�Ō��܂�j�F�����i�X�y�[�X�̋֎~�C<math>�̕t���j�@�R�̔{���iPost�Ō��܂�j�F�u���b�N�i���s�̋֎~�C�ܕԂ��̋֎~�j//Tag[0].TagSign��ActiveTagSign�Ƃ��đ�p�i-�P�F�^�O��ǂݍ��܂Ȃ��@�P�F�^�O��ǂݍ��ށ@���̑��̒l�͊e��j
		//ReadMathTag���݂̂Ŏg�p
		int WakukaraKotag;//�q�^�O���e�g�����ł��邱�Ƃ������B�q�^�O����w�肳���iConnectionP==1�̂Ƃ��ɐe�^�O��wakukarakotag�̒l���P�ƂȂ�j�@�P�F�^�[�������i�t�@�C���ւ̓ǂݏ����͕s�v�j�@�ݏ�C���t�������C�ϕ���C���X�g�ށC�e�[�u���ށCnoc�i����E�g�����ށj
	};
	//�����b�Z�[�W�{�b�N�X�t�H�[��
	struct MSG_BOX_FORM {
		int MaxLine = -1;//���͉\�ȍő�s���i�}�C�i�X�i-1�j�Ȃ�s���̐����Ȃ��j
		int Margin[4] = { 0 };//���b�Z�[�W�{�b�N�X�O�̋���
		int Padding[4] = { 10, 10, 10, 10 };//���b�Z�[�W�{�b�N�X���Ń��b�Z�[�W�܂ł̋����i[0]���p�f�B���O[1]��p�f�B���O[2]�E�p�f�B���O[3]���p�f�B���O�j	
					   ////
		int BorderColor = GetColor(255, 255, 255);//�g���̐F
		int BorderThickness = 4;//�g���̑���
		int BorderType = 1;
		int BackColor = GetColor(0, 0, 0);//�w�i�F�̃n���h���i�w�肵�Ȃ��j
		int BackTransparency = 50;//�w�i�̓��ߓx�i%�j
		int ActiveTagColor = GetColor(255, 255, 0);//�A�N�e�B�u�ȃ^�O�̐F�n���h���i�w�肵�Ȃ��j
		int ActiveTagColorTransparency = 70;//�A�N�e�B�u�ȃ^�O�̐F�̓��ߓx�i%�j
		int ActiveMathColor = GetColor(204, 255, 255);//�w�i�F�̃n���h���i�w�肵�Ȃ��j
		int ActiveMathColorTransparency = 80;//�w�i�̓��߁@�A���t�@�u�����f�B���O�̃p�����[�^�i�l���Q�T�T�ɋ߂��قǔw�i���Z���\�������)

		int FontColorRGB[3] = { 255, 255, 255 };//�����FRGB
		int FontColor = GetColor(255, 255, 255);//�����F�n���h��

		int Leading = 5;//�s��[18]
		int BlinkSpeed = 120;//�J�[�\���̓_�ŃX�s�[�h�i�P���Ԃɓ_�ł����)�i[15]�j60000�̖񐔂��悢�B�O�p�J�[�\���̂Ƃ��̓p�f�B���O[3]���v���X���Ă����Ƃ悢
		int OutputSpeed = 50;//�����̏o�̓X�s�[�h�i�v���X�F�P�b�Ԃɐi�ޕ������@�}�C�i�X�F�N���b�N�ɔ�������j1000�̖񐔂��悢
							 //�܂�i�v���X�F�p�J�p�J����B�J�[�\���Ȃ��B�@0�F�p�J�p�J�Ȃ��B�J�[�\���Ȃ��B�@-1�F�p�J�p�J�Ȃ��B�N���b�N�ォ��J�[�\������B�@-2�ȉ��F�p�J�p�J�Ȃ��B������J�[�\������B�j
		int ScrollSpeed = 200;//�X�N���[���̃X�s�[�h�i�P�b�ԂɃX�N���[������s�N�Z���j�i[14]�j1000�̖񐔂��悢
		int Option = 11444;//
		//Sound����̑��΃p�X�܂��̓t�@�C�����i�������G�f�B�^�[�ł͑��΃p�X������d�l�j�ł��烍�[�h�����n���h��
		int MsgSound = -1;//���b�Z�[�W���i�p�J�p�J���C���b�Z�[�W�J�[�\���̃W�����v���C���b�Z�[�W�J�[�\���̈ړ����j
		int ConfirmSound = -1;//�m�艹�i�t���[�Y�����I����ԁC�E�B���h�E�����t�̏�Ԃ̂Ƃ��Ƀ{�^�������������B���͂̊m�艹�j
		int BackDelSound = -1;//�o�b�N�X�y�[�X�E�f���[�g���C�t�H�[�����o�鉹
		/*
		���P���ځ@�O�F������@�P�F���@�Q�F�E����@�R�F����@�T�F�W���C�p�b�h�@����ȊO�i�S�j�F�X�N���[���Ȃ�
		���Q���ځ@�O�F���[�@�P�F��[�@�Q�F�E�[�@�R�F���[�@����ȊO�i�S�j�F�{�b�N�X����
		���R���ځ@�����E����łO�F���񂹁@���܂��͉���łP�F��񂹁@���܂��͉E����łQ�F�E�񂹁@��肩����łR�F���񂹁@�S�F�����@�T�F���[�v�@����ȊO�i6�j�F�ʉ߁i���ō��񂹂��w�肵���ꍇ�Ȃǂ��ʉ߂ƂȂ�j
		���S���ځ@�O�F�܂�Ԃ��Ȃ��iMaxLine�͖����ɂȂ�j�@�P�F�܂�Ԃ�����@�Q�F�܂�Ԃ�����i�킩���j
		���T���ځ@�{�b�N�X���[�@�O�F�w�肵�������@�P�i0���傫��2�C3�������j�F�\����̃��b�Z�[�W���[�@�Q�F�\�����̃��b�Z�[�W���[�@�R�F�\�����̃��b�Z�[�W���[�iHeight�̒l���ω��j���R�̓p�J�p�J�ɂ͂��邪�X�N���[���ɂ͂Ȃ��i�X�N���[���ł͂P�Ɠ����ɂȂ�j
		*/
	};
	//�����b�Z�[�W�{�b�N�X�t�H�[��2�iRGB�C�t�@�C���p�X�j���G�f�B�^�[�Ŏg�p
	struct MSG_BOX_RGB_SOUNDPATH {
		int BorderColorRGB[3] = { 255, 255, 255 };//�g���̐F
		int BackColorRGB[3] = { 0, 0, 0 };//�w�i�F�̃n���h���i�w�肵�Ȃ��j
		int ActiveTagColorRGB[3] = { 255, 255, 0 };//�w�i�F�̃n���h���i�w�肵�Ȃ��j
		int ActiveMathColorRGB[3] = { 204, 255, 255 };//�w�i�F�̃n���h���i�w�肵�Ȃ��j
		//Sound����̑��΃p�X�܂��̓t�@�C�����i�������G�f�B�^�[�ł͑��΃p�X������d�l�j
		char MsgSoundPath[MAX_PATH] = { 0 };//���b�Z�[�W���̃p�X�i�p�J�p�J�̉��@�W�����v���j
		char ConfirmSoundPath[MAX_PATH] = { 0 };//�m�艹�̃p�X�i�t���[�Y�����I����ԁC�E�B���h�E�����t�̏�Ԃ̂Ƃ��Ƀ{�^�������������B���͂̊m�艹�j
		char BackDelSoundPath[MAX_PATH] = { 0 };//�o�b�N�X�y�[�X�E�f���[�g�̉��̃p�X
	};
	//�����b�Z�[�W�{�b�N�X
#define TAG_MAX_for_MSG_BOX_CTRL 300//�i�����o�[��Tag�������Ă��邩��ő�l���`���Ă����K�v������j
	struct MSG_BOX_CTRL {
		struct AREA_CTRL *ParentArea_p = NULL;//�G���A�i�n�_�Ƒ傫���̏��j�̃|�C���^�[
		struct MSG_BOX_FORM *MsgBoxForm_p = NULL;//�t�H�[���i�n�_�Ƒ傫���̏��j�̃|�C���^�[�i���[�h���̓t�H�[���̗v�f�ԍ�MsgBoxFormNumber�Ń|�C���^�[���w��j

		int Location[2] = { 0,0 };//�R���g���[���̍��W�i[0]���[[1]��[�j
		int Width = 600;//�R���g���[���̕�
		int Height = 250;//�R���g���[���̍����i�����L�k�^�C�v�ł̓��b�Z�[�W�̍�������Z�o�B�������^�C�v105�i�X�N���[������̍����L�k�Ń��b�Z�[�W�{�b�N�X����)�̂Ƃ��͗̈���̃��b�Z�[�W�̍�������Z�o�B�j
		int OuterWidth = 600;//�}�[�W�����܂ޕ��i�w�肵�Ȃ��j
		int OuterHeight = 250;//�}�[�W�����܂ލ����i�w�肵�Ȃ��j
		int MsgWidth = 0;//���b�Z�[�W�̍����i�R���g���[���̉��[�܂ł̗]�����X�y�[�X�͊܂܂Ȃ��j
		int MsgHeight = 0;//���b�Z�[�W�̍����i�R���g���[���̉��[�܂ł̗]�����X�y�[�X�͊܂܂Ȃ��j
		int ActiveLetterSize = 0;//���͂Ɋւ���A�N�e�B�u�ȕ����̃T�C�Y�i[11]�j
		int ActiveLetterX = 0;//���͂Ɋւ���A�N�e�B�u�ȕ����̈ʒuX�i[16]�j
		int ActiveLetterY = 0;//���͂Ɋւ���A�N�e�B�u�ȕ����̈ʒuY�i[17]�j
		struct TAG Tag[TAG_MAX_for_MSG_BOX_CTRL + 1];//�^�O�̏������i���[�J���ϐ��j = { 0 }//�v���X�P��Tag[0]�̕�
		char ParsedMsg[2000] = { "\0" };//�^�O�𔲂�����������������z��

		//�ȉ��́CClearMsgBox�֐��Ń��Z�b�g�������́i��Tag[0].TagSign�CTag[0].ConnectionP��ClearMsgBox�֐��Ń��Z�b�g�����j
		int Condition = 1;//
		int StartingPointX = 0;//���b�Z�[�W�̑S�̂̈ʒu�i�E�B���h�E�x�[�X�̈ʒu�B�c�X�N���[�����܂܂Ȃ��j
		int StartingPointY = 0;//���b�Z�[�W�̑S�̂̈ʒu�i�E�B���h�E�x�[�X�̈ʒu�B���X�N���[�����܂܂Ȃ��j




		int MsgX = 0;//���b�Z�[�W�S�̂̏����o���ʒu�i�E�B���h�E�x�[�X�̈ʒu�B���X�N���[�����܂ށj�iStartingPointX + ���X�N���[���ݐϒl�j
		int MsgY = 0;//���b�Z�[�W�S�̂̏����o���ʒu�i�E�B���h�E�x�[�X�̈ʒu�B�c�X�N���[�����܂ށj�iStartingPointY + �c�X�N���[���ݐϒl�j
		int Stale = 0;//�Â��Ȃ���ScrollTank�ɓn�����Ƃ��ł��鍂��
		int ScrollTank = 0;//�X�N���[���ł��鑍��
		int ScrollOne = 0;//�P��̃X�N���[���ʂ̒[���̗ݐρi���̒l�łP��̃X�N���[���ʂƎ��̒[�����Z�o�j
		int PhraseOn = 0;//�����o���\�t���[�Y�ԍ��i�t���[�Y�����I����̃{�^�������������j�i[8]�j


		int WaitTank = 0;//�c��̑ҋ@�t���[����[20]
		//int RemainWaitTime = 0;//�c��̑ҋ@�~���b��
		int WaitedFlame = 0;//�ҋ@�����t���[����[21]
		int KakidashiLineMax = 0;//�ő�s�ԍ��i[7]�j�@�@����Ďw�肵����r������p�J�p�J���n�܂�̂��ȁH�H�H
		int KakidashiTagMax = 0;//�o�Ă������̌����_�ł̍ő�^�O�ԍ�

		int Switch = 0;//�X�C�b�`�i[22]�j
		int ShowMsgBoxFlag = 1;//�O���b�Z�[�W�{�b�N�X�������o���Ȃ��@�P�F���b�Z�[�W�{�b�N�X�������o��
		int NonEnterable = 0;
		//int Time = -1;
		//int ElapsedTime = 0;

		/*��� Condition
		//��Condition��0�Ԃ́C���������o�����[�v�̏������iCondition != 0�j�ɂȂ��Ă��邾��������s�v�H�H�H
		0:�����o���s��																//ElapsedTime���i�ށi10��菬�����j//�X�N���[������i3�ȉ��j
		1:�����o���i���߂ď����o���s�̐擪�j										//ElapsedTime���i�ށi10��菬�����j//�X�N���[������i3�ȉ��j
		2:�����o���i���߂ď����o���s�̐擪�ł͂Ȃ��j								//ElapsedTime���i�ށi10��菬�����j//�X�N���[������i3�ȉ��j
		3:�I�[�����܂Ői��//��8													//ElapsedTime���i�ށi10��菬�����j//�X�N���[������i3�ȉ��j

		4:�ŏI�ʒu�܂ŃX�N���[�������i�������I�[�����܂ŏ����o���ς݂̂Ƃ��j//��6	//ElapsedTime���i�ށi10��菬�����j
		5:�I�[�����܂ŏ����o������Ƀ{�^��������//��7								//ElapsedTime���i�ށi10��菬�����j

		11:�t���[�Y�����I��//��3
		12:�E�B���h�[�����t//��4
		13:���������������~�߂�//��5
		/////////////////////
		101�F�m�肵�����Ƃ������i���͎��̃J�[�\�����Ō�܂ł����񂾂Ƃ��B�m��{�^�����������Ƃ��͊֌W�Ȃ��Ǝv���j
		102�F���̃J�[�\���ʒu�ɐi�񂾂Ƃ�
		103�F���̃J�[�\���ʒu�ɐi�񂾂Ƃ�
		*/
	};
	//���ۑ�
//#define Kadai_MonsterIdSize 5//���̏������݉\�T�C�Y�i\0���܂܂Ȃ��j
//#define KADAI_SYOUMONSEIKAIMAX 50//���␔�̍ő�
#define DAIMON_FIELDSIZE 1000//���̏������݉\�T�C�Y�i\0���܂܂Ȃ��j
#define DAIMONSEIKAI_FIELDSIZE 200//��␳���̏������݉\�T�C�Y�i\0���܂܂Ȃ��j
#define SYOUMON_MAX 50//���␔�̍ő�
#define SYOUMON_FIELDSIZE 1000//����̏������݉\�T�C�Y�i\0���܂܂Ȃ��j
#define SYOUMONSEIKAI_FIELDSIZE 200//���␳���̏������݉\�T�C�Y�i\0���܂܂Ȃ��j
	//���ۑ�
	struct MONDAI_CTRL {
		int monsterID = 0;//5���{�I�[
		char daimon[DAIMON_FIELDSIZE + 1] = { "<p></p>" }; //��╶������
		char daimonseikai[DAIMONSEIKAI_FIELDSIZE + 1] = { "<math></math>" }; //��␳��������
		char syoumon[SYOUMON_MAX + 1][SYOUMON_FIELDSIZE + 1] = { 0 }; //���╶������@[���␔50�@�i�{�P�̓R�s�[�p�o�b�t�@�j] [1�o�C�g����1000���܂�]
		char syoumonseikai[SYOUMON_MAX + 1][SYOUMONSEIKAI_FIELDSIZE + 1] = { 0 }; //���␳��������@[���␳��50�@�i�{�P�̓R�s�[�p�o�b�t�@�@�g���Ă��邩�ǂ����s��] [1�o�C�g����200���܂�]
	};
	//���f�B�X�v���C�p�b�h
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
		int Active = 1;//�P�F�C���f�b�N�X�G���A�ƃx�[�X�{�^���G���A�̂݃A�N�e�B�u�CActiveElement��0�B�|�P�F�S�G���A���A�N�e�B�u�CActiveElement��-1�B�i����ł͂Ȃ��C���f�b�N�X�G���A�̏�Ԃɂ�莯�ʂ��Ď��s�j
		int IndexOn = 0;//�I���ɂȂ��Ă���C���f�b�N�X�ԍ��i�C���f�b�N�X�O�Ԃ��I���ɂ���j190609
		int PushedNo = 0;//�Ō�ɉ����ꂽ�{�^���ԍ��i�J�[�\���̏����ʒu�̐ݒ�́C����ł͂Ȃ��{�^��CSV��Activ��3�ɂ���j
		int Duration = 0;//�{�^���������ꂽ����
		struct INPUT_TEXT_BTN_CTRL *ActiveBtn_h;
	};
	//�������X�^�[
#define MONSTERNAME_FIELDSISE 30//�����X�^�[���̍ő�o�C�g���i�z��T�C�Y�́{�P�j
#define MONSTER_COLUMNMAX 20//�J�����i�����j�̌�
#define MONSTER_COLUMNTITLEFIELDMAX 8//�R�����^�C�g���̕������i�z��T�C�Y�́{�P�j
	struct MONSTER_CTRL {
		char Name[MONSTERNAME_FIELDSISE + 1] = { 0 };//�����X�^�[��
		int Img = -1;//�����X�^�[�̉摜�n���h��
		int Column[MONSTER_COLUMNMAX] = { 0 };//�J�����i//�����X�^�[ID//�U����//�U������//���̓X�s�[�h//���̐����t���[����//���@ID//���@���l�i���@�̃^�C�~���O�Ɏg���ϐ��j//�l���\�o���l//�l���\�R�C���j
	};
	//�����b�Z�[�W�̃��[�h�p�ϐ�
	struct LOAD_MSG_SP {
		const char *FilePath_h = NULL;
		char *Msg_h = NULL;
		int MsgSize = 10000;
		const char *Dir_h = NULL;
		struct MSG_BOX_FORM *MsgBoxForm_p;
		struct MSG_BOX_CTRL *MsgBox_p;
		int GetDirFlag = 1;//LoadMsg��MsgDir�CLoadMsgBoxSet��LocalDir���擾
		int MsgCodeLinkFlag = 1;
		int JoypadLinkFlag = 1;
	};
	//�����̃��[�h�p�ϐ�
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
		int GetDirFlag = 1;//LoadMondai��MsgDir�CLoadMsgBoxSet��LocalDir���擾
		int MsgCodeLinkFlag = 1;
		int JoypadLinkFlag = 1;
	};
	//���p�b�h�̂̃��[�h�p�ϐ�
	struct LOAD_DISPLAY_PAD_SP {
		const char *FilePath_AreaSet_h = NULL;
		struct AREA_CTRL *ParentArea_p = NULL;
		struct DISPLAY_PAD_CTRL *DisplayPad_p;
		int Area_Max = 1;
		int BtnForm_Max = 1;
		int Index_Max = 1;
		const int *Btn_Max_h;
		int BaseBtn_Max = 1;
		//�t���O
		int GetDirFlag = 1;
		int MsgCodeLinkFlag = 1;
		int JoypadLinkFlag = 1;
	};










////////�@�ց@���@////////
	//��AppDir�̎擾
	int ActiveMath_Init();
	//���t���[�����[�g�̕ύX
	int ChangeFPS(int FPS);
	//������������ҋ@
	int SleepToFitFPS(int FPS);
	//���u�ԃt���[�����[�g�̑���iN�t���[�����Ƃ̏u�ԁj
	float MeasureInstantFPS(int N);
	//�����σt���[�����[�g�̑���iN�t���[���̕��ϒl�j
	float MeasureAverageFPS(int N);
	//���}�E�X�̓��͏��
	int MathgpUpdateMouse();
	//���S�ẴL�[�̓��͏�ԁi�����ꂽ�t���[�����j���X�V����֐�
	int MathgpUpdateKey();
	//���W���C�p�b�h�̓��͏�Ԃ��X�V
	int MathgpUpdateJoypad();
	//���G���A�Z�b�g�̃��[�h�Ɛݒ�i���[�h�����l�����Ɋe�p�����[�^�̒l�����肷��j
	int LoadAreaSet(const char *FilePath, struct AREA_CTRL *Area_h, int *Area_Kosuu_p, int Area_Max, struct AREA_CTRL *ParentArea_p);
	//���t�H���g�X�^�C���̃��[�h�ƃt�H���g�n���h���̍쐬
	int LoadFontStyle(const char *FilePath);
	//���摜�X�^�C���̃��[�h�Ɖ摜�n���h���̍쐬
	int LoadFontImgStyle(const char *FilePath);
	//���^�O�X�^�C���̃��[�h
	int LoadTagStyle(const char *FilePath);
	//���W���C�p�b�h�X�^�C���̃��[�h
	int LoadJoypadStyle(const char *FilePath);
	//���t�H���g�E�^�O�X�^�C���̃����N�̃��[�h�i�t�H���g�C�t�H���g�摜�C�^�O�ݒ�̃��[�h�j�i0�F�����@-1�F���s�j//���I�����̓��[�g�f�B���N�g��
	int LoadMsgCodeLink(const char *FilePath);
	//���W���C�p�b�h�X�^�C���̃����N�̃��[�h
	int LoadJoypadLink(const char *FilePath);
	//�����b�Z�[�W�{�b�N�X�t�H�[���̃��[�h
	int LoadMsgBoxFormSet(const char *FilePath, struct MSG_BOX_FORM *MsgBoxForm_h, int MsgBoxForm_Max);
	//�����b�Z�[�W�{�b�N�X�t�H�[���̉摜�p�X�CRGB�̃��[�h
	int LoadMsgBoxRgbSoundPathSet(const char *FilePath, struct MSG_BOX_RGB_SOUNDPATH *MsgBox_RGB_SoundPath_h, int MsgBoxForm_Max);
	//�����b�Z�[�W�{�b�N�X�R���g���[���̃��[�h
	int LoadMsgBoxSet(const char *FilePath, struct MSG_BOX_FORM *MsgBoxForm_h, struct MSG_BOX_CTRL *MsgBox_h, int MsgBoxForm_Max, int MsgBox_Max, int GetDirFlag);
	//�����b�Z�[�W�̃��[�h
	int LoadMsg(const char *FilePath, char *Msg, int MsgSize, int GetDirFlag);
	//�����b�Z�[�W�Ƃ��̊֘A�t�@�C���̃��[�h
	int LoadMsgSP(struct LOAD_MSG_SP *m);
	//�������X�^�[�̃��[�h
	int LoadMonster(const char* FilePath, struct MONSTER_CTRL *Monster_h, int Monster_Max, int *Monster_Kosuu, char(*ColumnTitle_h)[MONSTER_COLUMNTITLEFIELDMAX + 1], int *Column_Kosuu);
	//�������X�^�[�摜�p�X�̃��[�h
	int LoadMonsterImgTitle(const char *FilePath, char(*MonsterImgTitle_h)[MAX_PATH], int Monster_Max, int *IssuedMoonsterID_p);//int *IssuedMoonsterID_p�͔��s�ςݍő�ID�i�G�f�B�^�[�Ŏg�p�j
	//�����̃��[�h
	int LoadMondai(const char *FilePath, struct MONDAI_CTRL *Mondai, int *Syoumon_Kosuu_p, int GetDirFlag);
	//�����Ƃ��̊֘A�t�@�C���̃��[�h
	int LoadMondaiSP(struct LOAD_MONDAI_SP *m_p);
	//���{�^���t�H�[���Z�b�g�̃��[�h
	int LoadBtnFormSet(const char *FilePath, struct BTN_FORM *BtnForm_h, int *BtnForm_Kosuu_p, int BtnForm_Max);
	//���{�^���Z�b�g�i�����O���[�v�j�̃��[�h�i0�F�����@-1�F���s�i�t�@�C���������݂��Ȃ��C�����̃|�C���^�[��NULL�j�@-2�F�{�^���̔z��v�f��������Ȃ��j
	int LoadBtnSetEx(const char *FilePath, struct BTN_CTRL **Btn_hh, int *Btn_Kosuu_h, const int *Btn_Max_h, int BtnSet_Kosuu, struct AREA_CTRL *BtnArea_h, struct BTN_FORM *BtnForm_h);
	//���e�L�X�g���̓{�^���Z�b�g�̃��[�h�i�����O���[�v�j�̃��[�h�i0�F�����@-1�F���s�i�t�@�C���������݂��Ȃ��C�����̃|�C���^�[��NULL�j�@-2�F�{�^���̔z��v�f��������Ȃ��j
	int LoadInputTextBtnSetEx(const char *FilePath, struct INPUT_TEXT_BTN_CTRL **Btn_hh, int *Btn_Kosuu_h, const int *Btn_Max_h, int BtnSet_Kosuu, struct AREA_CTRL *BtnArea_h, struct BTN_FORM *BtnForm_h);
	//���p�b�h�E�p�b�h�t���t�@�C���̃��[�h
	int LoadDisplayPadSP(struct LOAD_DISPLAY_PAD_SP *p_p);
	//���t�@�C���p�X����t�@�C�������擾
	int GetTitleFromPath(char *FileTitle, char *FilePath);
	//���t�@�C���p�X����f�B���N�g�����擾�i�G�f�B�^�[�ł͌���g���Ă��Ȃ��j
	int GetDirFromPath(char *Dir, const char *FilePath);
	//�����[�J���f�B���N�g���C���b�Z�[�W�f�B���N�g���̃p�X�̎擾
	int SetLocalDirMsgDirFromMsgPath(const char *FilePath);

	//���J�[�\���I�[�o�[
	int Math_CursorOver(int LocationX1, int LocationY1, int Padding, int StringColor, int BackColor, int Type);
	//���}���`�K�C�h
	int MultiGuide();
	//���I�[�o�[���b�v�@�ǉ�����̈���󂯎���āC���̕`��\�̈您��сC���̕`��\�̈�Əd�������̈���擾����i�d�������̈�NewRange�@�ǉ�����̈�AddRange�j
	int Overlap(int *NewRange, const int *AddRange);
	//���摜�̏㉺�ʒu�̕ύX
	int ChangeImgAlign(char *Msg, struct MSG_BOX_CTRL *MsgBox_p);
	//�����b�Z�[�W�{�b�N�X�̍����̏����l�\��
	int ShowHeightGauge(struct MSG_BOX_CTRL *MsgBox, int MasterHeight, int Color);

	//���G���A�̕\��
	int ShowArea(struct AREA_CTRL *Area_h, int Area_Kosuu);
	//���^�O��ǂݎ��֐�
	int ReadMathTag(const char *Msg, struct TAG *Tag, int TagSaidai, char *ParsedMsg, const int *FontColorRGB);
	//���^�O�̍ēǂݍ��ݎw���iDrawMsg�p�j
	int ReparseTag(struct TAG *Tag_h);
	//���^�O�̍ēǂݍ��ݎw��
	int Reparse(struct MSG_BOX_CTRL *MsgBox_p);
	//���A�N�e�B�u�v�f�̔�A�N�e�B�u���iActiveElement��-1�j
	int EraseActiveElement(struct MSG_BOX_CTRL *MsgBox_p);
	//���A�N�e�B�u�v�f�̎擾�iActiveElement��0�j
	int GetActiveElement(struct MSG_BOX_CTRL *MsgBox_p);

	//�����b�Z�[�W�{�b�N�X�̃��Z�b�g
	int ClearMsgBox(struct MSG_BOX_CTRL *MsgBox_p);

	//�����b�Z�[�W�{�b�N�X�̕\��
	int ShowMsgBox(const char *Msg, struct MSG_BOX_CTRL *MsgBox_p);
	//���{�^��
	int ShowBtnSet(struct BTN_CTRL *Btn_h, int Btn_Kosuu, int *PushedNo_p, int PushType, int Prev, int Next);
	//���e�L�X�g�{�^��
	int ShowTextBtnSet(char *Msg, struct MSG_BOX_CTRL *MsgBox_p, int MsgSize, struct INPUT_TEXT_BTN_CTRL *InputTextBtn_h, int Btn_Kosuu, int *PushedNo_p, int PushType, int Prev, int Next);
	//�����X�g�̕\��
	int ShowList(struct LIST_CTRL *List_p);

	//�����b�Z�[�W�̃L�[�{�[�h���́i�L�[�{�[�h���琔������͂��邽�߂̊֐��j
	int InputMsgKey(char *Msg, struct MSG_BOX_CTRL *MsgBox_p, int MsgSize, int *InputHandle);
	//�����b�Z�[�W�̃W���C�p�b�h����
	int OperateMsgJoypad(char *Msg, struct MSG_BOX_CTRL *MsgBox_p, int MsgSize);
	//���p�b�h�i�}�E�X����j
	int ShowDisplayPadM(struct DISPLAY_PAD_CTRL *DisplayPad_p);
	//���p�b�h�i�W���C�p�b�h����j
	int ShowDisplayPadJ(struct DISPLAY_PAD_CTRL *DisplayPad_p);
	//���p�b�h�̃��Z�b�g
	int ResetDisplayPad(struct DISPLAY_PAD_CTRL *DisplayPad_p, int OnIndexNumber);

	//���V���v���o�́i�����{�t���[�����[�N�j�@�i���b�Z�[�W�{�b�N�X�R���g���[���s�v�j
	int DrawMsg(int LocationX, int LocationY, const char *Msg, int *FontColorRGB, int FontColorHandle, const struct AREA_CTRL *ParentArea_p, int Tag_Saidai, struct TAG *Tag_h, char *ParsedMsg_p);//�V���v�����[�h
	//�����̎擾
	#define TAG_MAX_for_GetWidthForDrawMsg 1000//GetWidthForDrawMsg�œǂݍ��݉\�ȃ^�O1000��
	int GetWidthForDrawMsg(const char *Msg, int *Width, int *Height, int *Tag_Kosuu);
	//��DrawString�{�t���[�����[�N
	int DrawStringInArea(int LocationX, int LocationY, const struct AREA_CTRL *ParentArea_p, const char *String_p, int Color);
	//��DrawFormatString�{�t���[�����[�N
	int DrawFormatStringInArea(int LocationX, int LocationY, const struct AREA_CTRL *ParentArea_p, int Color, const char *String_p, ...);
	int SetLocalDirFromMsgPath(const char *FilePath);
	int SetMsgDirFromMsgPath(const char *FilePath);

	//int ActiveMath_Init();
}//namespace ActiveMath�̏I��

using namespace ActiveMath;


