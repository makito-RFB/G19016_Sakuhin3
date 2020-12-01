#include "DxLib.h"
#include "resource.h"

#define GAME_WIDTH     960
#define GAME_HEIGHT    576
#define GAME_COLOR	   32

#define GAME_WINDOW_BAR		0
#define GAME_WINDOW_NAME	"���H�@�E�o"

#define GAME_FPS	60

#define MOUSE_BUTTON_CODE	129

#define PATH_MAX	255
#define NAME_MAX	255

#define FONT_TANU_PATH    TEXT(".\\FONT\\TanukiMagic.ttf")
#define FONT_TANU_NAME    TEXT("���ʂ������}�W�b�N")	

#define FONT_INSTALL_ERR_TITLE	TEXT("�t�H���g�C���X�g�[���G���[")
#define FONT_CREATE_ERR_TITLE	TEXT("�t�H���g�쐬�G���[")

#define IMAGE_LOAD_ERR_TITLE	TEXT("�摜�ǂݍ��݃G���[")

#define IMAGE_BACK_PATH       TEXT(".\\IMAGE\\�w�i1.png")
#define IMAGE_BACK_ENDC_PATH	  TEXT(".\\IMAGE\\�w�iCONP.png")
#define IMAGE_BACK_ENDF_PATH	  TEXT(".\\IMAGE\\�w�iFALL.png")

#define IMAGE_CHAR_PATH       TEXT(".\\IMAGE\\char1.png")
#define IMAGE_CHAR_1_PATH	  TEXT(".\\IMAGE\\char2.png")
#define IMAGE_CHAR_2_PATH	  TEXT(".\\IMAGE\\char3.png")

#define IMAGE_CHAR_NUM			3	

#define IMAGE_PLAYER_PATH	TEXT(".\\IMAGE\\ply1.png")

#define IMAGE_TITLE_BK_PATH		TEXT(".\\IMAGE\\strat�w�i.png")
#define IMAGE_TITLE_ROGO_PATH	TEXT(".\\IMAGE\\titlerogo.png")
#define IMAGE_TITLE_START_PATH	TEXT(".\\IMAGE\\title_start1.png")
#define IMAGE_TITLE_RNK	TEXT(".\\IMAGE\\title_start1.png")

#define IMAGE_TITLE_WORK_CNT   1
#define IMAGE_TITLE_WORK_CNT_MAX   20

#define IMAGE_END_COMP_PATH		TEXT(".\\IMAGE\\����.png")

#define IMAGE_END_FAIL_PATH		TEXT(".\\IMAGE\\���s.png")

#define IMAGE_END_ROGO_PATH	TEXT(".\\IMAGE\\ENRE.png")


#define MUSIC_LOAD_ERR_TITLE	TEXT("���y�ǂݍ��݃G���[")

#define MUSIC_BGM_PATH			TEXT(".\\MUSIC\\PLAY.mp3")
#define MUSIC_PLAYER_SHOT_PATH	TEXT(".\\MUSIC\\�V���b�g��.mp3")

#define MUSIC_BGM_TITLE_PATH	TEXT(".\\MUSIC\\OP.mp3")	//�^�C�g����BGM
#define MUSIC_BGM_COMP_PATH		TEXT(".\\MUSIC\\COMP.mp3")				//�R���v���[�gBGM
#define MUSIC_BGM_FAIL_PATH		TEXT(".\\MUSIC\\FALL.mp3")					//�t�H�[���gBGM

#define GAME_MAP_TATE_MAX	9	//�}�b�v�̏c�̐�
#define GAME_MAP_YOKO_MAX	15	//�}�b�v�̉��̐�
#define GAME_MAP_KIND_MAX	2	//�}�b�v�̎�ނ̐�

#define GAME_MAP_PATH			TEXT(".\\IMAGE\\MAP\\map.png")

#define MAP_DIV_WIDTH		64
#define MAP_DIV_HEIGHT		64
#define MAP_DIV_TATE		10
#define MAP_DIV_YOKO		4
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO

#define MOVE_ERIA 64

#define START_ERR_TITLE		TEXT("�X�^�[�g�ʒu�G���[")
#define START_ERR_CAPTION	TEXT("�X�^�[�g�ʒu�����܂��Ă��܂���")

#define GOAL_ERR_TITLE		TEXT("�S�[���ʒu�G���[")
#define GOAL_ERR_CAPTION	TEXT("�S�[���ʒu�����܂��Ă��܂���")

#define MOUSE_R_CLICK_TITLE		TEXT("�Q�[�����f")
#define MOUSE_R_CLICK_CAPTION	TEXT("�Q�[���𒆒f���A�^�C�g����ʂɖ߂�܂����H")

enum GAME_MAP_KIND
{
	n = -1,	//(NONE)����
	k = 0,	//��
	m = 1,  //�ǂQ
	r = 2,  //�ǂR
	l = 4,  //������
	t = 9,	//�ʘH
	s = 5,	//�X�^�[�g
	g = 3	//�S�[��
};	

enum GAME_MAP_KIND_PR
{
	np = -1,	//(NONE)����
	kp = 0,	//��
	mp = 1,  //�ǂQ
	rp = 2,  //�ǂR
	lp = 4,  //������
	tp = 9,	//�ʘH
	sp = 5,	//�X�^�[�g
	gp = 3	//�S�[��
};

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_EXPO,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};

enum GAME_END {
	GAME_END_COMP,
	GAME_END_FAIL
};

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGH = 3
};

enum CHARA_RELOAD {
	CHARA_RELOAD_LOW = 60,
	CHARA_RELOAD_MIDI = 30,
	CHARA_RELOAD_HIGH = 15
};

typedef struct STRUCT_I_POINT
{
	int x = -1;
	int y = -1;
}iPOINT;

typedef struct STRUCT_MOUSE
{
	int InputValue = 0;	
	iPOINT Point;		//�}�E�X�̍��W������
	iPOINT OldPoint;	//�}�E�X�̍��W(���O)������
	int OldButton[MOUSE_BUTTON_CODE] = { 0 };
	int Button[MOUSE_BUTTON_CODE] = { 0 };
}MOUSE;

typedef struct STRUCT_FONT
{
	char path[PATH_MAX];
	char name[NAME_MAX];
	int handle;
	int size;
	int bold;
	int type;
}FONT;

typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];
	int handle;
	int x;
	int y;
	int width;
	int height;
}IMAGE;

typedef struct STRUCT_MUSIC
{
	char path[PATH_MAX];
	int handle;
}MUSIC;

typedef struct STRUCT_CHARA
{
	IMAGE image;
	int speed;
	int CenterX;
	int CenterY;

	MUSIC musicShot;

	RECT coll;
	iPOINT collBeforePt;

}CHARA;


typedef struct STRUCT_IMAGE_BACK
{
	IMAGE image;
	BOOL IsDraw;
}IMAGE_BACK;

typedef struct STRUCT_IMAGE_ROTA
{
	IMAGE image;

}IMAGE_ROTA;

typedef struct STRUCT_IMAGE_WORK
{
	IMAGE image;
	int Cnt;
	int CntMAX;
	BOOL IsDraw;

}IMAGE_WORK;

typedef struct STRUCT_IMAGE_BLINK
{
	IMAGE image;
	BOOL IsDraw;
	double rate;
	double angle;
}IMAGE_BLINK;

typedef struct STRUCT_MAP_IMAGE
{
	char path[PATH_MAX];
	int handle[MAP_DIV_NUM];
	int kind[MAP_DIV_NUM];
	int width;
	int height;
}MAPCHIP;

typedef struct STRUCT_MAP
{
	GAME_MAP_KIND kind;
	GAME_MAP_KIND_PR kind2;
	int x;
	int y;
	int width;
	int height;
}MAP;

int StartTimeFps;
int CountFps;
float CalcFps;
int SampleNumFps = GAME_FPS;

int newX = 0, newY = 0; //�������u���b�N�̍��W

int waitCnt = 0;

int DrCharCnt = 0;

int ExDrawCnt = 1;

char AllKeyState[256] = { '\0' };
char OldAllKeyState[256] = { '\0' };

char direc; //�����̂��

int timeCnt = 0;
double time = 0;
int mintime = 0;

MOUSE mouse;

FONT FontTanu32;

int GameScene;

int GameEndKind;
RECT GoalRect = { -1,-1, -1, -1 };

BOOL MY_KEY_TF = TRUE;

bool Kchoice = TRUE;

BOOL MY_CHAR_MOVE_ST = TRUE;

BOOL MY_MAP_RELOAD = TRUE;

BOOL FALL_RESON = FALSE;

BOOL CLICK_M = TRUE;

IMAGE_BACK ImageBack;
IMAGE_BACK ImageBackEND;
IMAGE_BACK ImageBackENDF;


IMAGE ImageTitleBK;
IMAGE_ROTA ImageTitleROGO;
IMAGE_BLINK ImageTitleSTART;
IMAGE_BLINK ImageTitleRNK;


IMAGE_BLINK ImageEndCOMP;
IMAGE_BLINK ImageEndFAIL;

IMAGE_BLINK ImageEndROGO;

IMAGE_WORK ImageWork;

IMAGE_WORK ImageChar[IMAGE_CHAR_NUM];

CHARA player;

MUSIC BGM;

MUSIC BGM_TITLE;
MUSIC BGM_COMP;
MUSIC BGM_FAIL;

GAME_MAP_KIND mapData[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,3,4
		m,m,m,m,m,m,m,m,m,m,m,m,m,g,m,	// 0
		k,t,t,t,l,t,t,l,t,t,l,k,t,t,k,	// 1
		k,t,t,l,t,l,t,l,t,k,t,t,l,t,k,	// 2
		k,l,t,t,t,k,t,k,t,t,l,t,l,t,k,	// 3
		k,t,t,l,t,k,t,k,l,k,l,l,k,t,k,	// 4
		k,l,l,t,l,t,t,k,t,t,l,t,k,t,k,	// 5
		k,t,t,k,t,l,t,k,l,t,t,t,k,t,k,	// 6
		k,s,t,k,t,k,t,l,t,t,l,t,t,t,k,	// 7
		r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,	// 8
};

//�}�b�v�������p�̃o�b�N�A�b�v
GAME_MAP_KIND_PR mapDataPR[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,
		mp,mp,mp,mp,mp,mp,mp,mp,mp,mp,mp,mp,mp,gp,mp,	// 0
		kp,tp,tp,tp,lp,tp,tp,lp,tp,tp,lp,kp,tp,tp,kp,	// 1
		kp,tp,lp,tp,tp,lp,tp,lp,tp,kp,tp,tp,lp,tp,kp,	// 2
		kp,lp,tp,tp,tp,kp,tp,kp,tp,tp,lp,tp,lp,tp,kp,	// 3
		kp,tp,tp,lp,tp,kp,tp,kp,lp,lp,kp,lp,kp,tp,kp,	// 4
		kp,lp,lp,tp,lp,tp,tp,kp,tp,tp,lp,tp,kp,tp,kp,	// 5
		kp,tp,tp,kp,tp,lp,tp,kp,kp,tp,tp,tp,kp,tp,kp,	// 6
		kp,sp,tp,kp,tp,kp,tp,lp,tp,tp,lp,tp,tp,tp,kp,	// 7
		rp,rp,rp,rp,rp,rp,rp,rp,rp,rp,rp,rp,rp,rp,rp,	// 8
};

GAME_MAP_KIND mapDataInit[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];
MAPCHIP mapChip;
MAP map[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];
iPOINT startPt{ -1,-1 };
RECT mapColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

VOID MY_FPS_UPDATE(VOID);
VOID MY_FPS_WAIT(VOID);

VOID MY_ALL_KEYDOWN_UPDATE(VOID);
BOOL MY_KEY_DOWN(int);
BOOL MY_KEY_UP(int);
BOOL MY_KEYDOWN_KEEP(int, int);

VOID MY_MOUSE_UPDATE(VOID);
BOOL MY_MOUSE_DOWN(int);
BOOL MY_MOUSE_UP(int);
BOOL MY_MOUSEDOWN_KEEP(int, int);

BOOL MY_FONT_INSTALL_ONCE(VOID);
VOID MY_FONT_UNINSTALL_ONCE(VOID);
BOOL MY_FONT_CREATE(VOID);
VOID MY_FONT_DELETE(VOID);

VOID MY_START(VOID);
VOID MY_START_PROC(VOID);
VOID MY_START_DRAW(VOID);

VOID MY_EXPO(VOID);
VOID MY_EXPO_PROC(VOID);
VOID MY_EXPO_DRAW(VOID);

VOID MY_PLAY(VOID);
VOID MY_PLAY_PROC(VOID);
VOID MY_PLAY_DRAW(VOID);

VOID MY_END(VOID);
VOID MY_END_PROC(VOID);
VOID MY_END_DRAW(VOID);

BOOL MY_LOAD_IMAGE(VOID);
VOID MY_DELETE_IMAGE(VOID);

BOOL MY_LOAD_MUSIC(VOID);
VOID MY_DELETE_MUSIC(VOID);

BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT);
BOOL MY_CHECK_RECT_COLL(RECT, RECT);

CHAR MY_DIRECTION(double, double, double, double);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);
	SetWindowStyleMode(GAME_WINDOW_BAR);
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));
	SetAlwaysRunFlag(TRUE);
	SetWindowIconID(IDI_ICON1);

	if (DxLib_Init() == -1) { return -1; }

	if (MY_LOAD_IMAGE() == FALSE) { return -1; }

	if (MY_LOAD_MUSIC() == FALSE) { return -1; }

	if (MY_FONT_INSTALL_ONCE() == FALSE) { return -1; }
	if (MY_FONT_CREATE() == FALSE) { return -1; }

	SetMouseDispFlag(TRUE);

	GameScene = GAME_SCENE_START;

	SetDrawScreen(DX_SCREEN_BACK);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			if (mapData[tate][yoko] == s)
			{
				startPt.x = mapChip.width * yoko + mapChip.width / 2;
				startPt.y = mapChip.height * tate + mapChip.height / 2;
			}

			if (mapData[tate][yoko] == g)
			{
				GoalRect.left = mapChip.width * yoko;
				GoalRect.top = mapChip.height * tate;
				GoalRect.right = mapChip.width * (yoko + 1);
				GoalRect.bottom = mapChip.height * (tate + 1);
			}
		}
	}

	if (startPt.x == -1 && startPt.y == -1)
	{
		MessageBox(GetMainWindowHandle(), START_ERR_CAPTION, START_ERR_TITLE, MB_OK);	return -1;
	}

	if (GoalRect.left == -1)
	{
		MessageBox(GetMainWindowHandle(), GOAL_ERR_CAPTION, GOAL_ERR_TITLE, MB_OK);	return -1;
	}

	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }
		if (ClearDrawScreen() != 0) { break; }

		MY_ALL_KEYDOWN_UPDATE();

		MY_MOUSE_UPDATE();

		MY_FPS_UPDATE();

		switch (GameScene)
		{
		case GAME_SCENE_START:
			MY_START();
			break;
		case GAME_SCENE_EXPO:
			MY_EXPO();
			break;
		case GAME_SCENE_PLAY:
			MY_PLAY();
			break;
		case GAME_SCENE_END:
			MY_END();
			break;
		}

		ScreenFlip();

		MY_FPS_WAIT();
	}

	MY_FONT_DELETE();

	MY_FONT_UNINSTALL_ONCE();

	MY_DELETE_IMAGE();

	MY_DELETE_MUSIC();

	DxLib_End();

	return 0;
}

VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0) 
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == SampleNumFps)
	{
		int now = GetNowCount();
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}

VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;

	if (waitTime > 0)
	{
		WaitTimer(waitTime);
	}
	return;
}

VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{
	char TempKey[256];

	for (int i = 0; i < 256; i++)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}
	GetHitKeyStateAll(TempKey);

	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)
		{
			AllKeyState[i]++;
		}
		else
		{
			AllKeyState[i] = 0;	
		}
	}
	return;
}

BOOL MY_KEY_DOWN(int KEY_INPUT_)
{
	if (AllKeyState[KEY_INPUT_] != 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL MY_KEY_UP(int KEY_INPUT_)
{
	if (OldAllKeyState[KEY_INPUT_] >= 1
		&& AllKeyState[KEY_INPUT_] == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int DownTime)
{

	int UpdateTime = DownTime * GAME_FPS;

	if (AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

VOID MY_MOUSE_UPDATE(VOID)
{
	mouse.OldPoint = mouse.Point;

	for (int i = 0; i < MOUSE_BUTTON_CODE; i++) { mouse.OldButton[i] = mouse.Button[i]; }

	GetMousePoint(&mouse.Point.x, &mouse.Point.y);

	mouse.InputValue = GetMouseInput();

	if ((mouse.InputValue & MOUSE_INPUT_LEFT) == MOUSE_INPUT_LEFT) { mouse.Button[MOUSE_INPUT_LEFT]++; }
	if ((mouse.InputValue & MOUSE_INPUT_LEFT) != MOUSE_INPUT_LEFT) { mouse.Button[MOUSE_INPUT_LEFT] = 0; }

	if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) == MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE]++; }
	if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) != MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE] = 0; }

	if ((mouse.InputValue & MOUSE_INPUT_RIGHT) == MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT]++; }
	if ((mouse.InputValue & MOUSE_INPUT_RIGHT) != MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT] = 0; }

	return;
}

BOOL MY_MOUSE_DOWN(int MOUSE_INPUT_)
{
	if (mouse.Button[MOUSE_INPUT_] != 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL MY_MOUSE_UP(int MOUSE_INPUT_)
{
	if (mouse.OldButton[MOUSE_INPUT_] >= 1
		&& mouse.Button[MOUSE_INPUT_] == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL MY_MOUSEDOWN_KEEP(int MOUSE_INPUT_, int DownTime)
{
	int UpdateTime = DownTime * GAME_FPS;

	if (mouse.Button[MOUSE_INPUT_] > UpdateTime)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL MY_FONT_INSTALL_ONCE(VOID)
{
	if (AddFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL) == 0)
	{
		MessageBox(GetMainWindowHandle(), FONT_TANU_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

VOID MY_FONT_UNINSTALL_ONCE(VOID)
{
	RemoveFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL);

	return;
}

BOOL MY_FONT_CREATE(VOID)
{
	strcpy_s(FontTanu32.path, sizeof(FontTanu32.path), FONT_TANU_PATH);
	strcpy_s(FontTanu32.name, sizeof(FontTanu32.name), FONT_TANU_NAME);
	FontTanu32.handle = -1;
	FontTanu32.size = 32;
	FontTanu32.bold = 1;
	FontTanu32.type = DX_FONTTYPE_ANTIALIASING_EDGE;

	FontTanu32.handle = CreateFontToHandle(FontTanu32.name, FontTanu32.size, FontTanu32.bold, FontTanu32.type);

	if (FontTanu32.handle == -1) { MessageBox(GetMainWindowHandle(), FONT_TANU_NAME, FONT_CREATE_ERR_TITLE, MB_OK); return FALSE; }

	return TRUE;
}

VOID MY_FONT_DELETE(VOID)
{
	DeleteFontToHandle(FontTanu32.handle);

	return;
}

VOID MY_START(VOID)
{
	MY_START_PROC();
	MY_START_DRAW();

	return;
}

VOID MY_START_PROC(VOID)
{
	static BOOL MusicPass = TRUE; 
	static BOOL check = TRUE;

	if (CheckSoundMem(BGM_TITLE.handle) == 0 && MusicPass == TRUE)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, BGM_TITLE.handle);
		PlaySoundMem(BGM_TITLE.handle, DX_PLAYTYPE_LOOP);
	}


	if (check == TRUE) {
		if (MY_KEY_DOWN(KEY_INPUT_DOWN) == TRUE || MY_KEY_DOWN(KEY_INPUT_UP) == TRUE) {
			Kchoice = !Kchoice;
			check = FALSE;
		}
	}
	if (MY_KEY_UP(KEY_INPUT_DOWN) == TRUE || MY_KEY_UP(KEY_INPUT_UP) == TRUE)
		check = TRUE;


	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE && Kchoice == TRUE)
	{
		if (CLICK_M == TRUE)
		{
			PlaySoundMem(player.musicShot.handle, DX_PLAYTYPE_BACK);
			CLICK_M = FALSE;
		}
		if (CheckSoundMem(BGM_TITLE.handle) != 0)
		{
			StopSoundMem(BGM_TITLE.handle);
			MusicPass = FALSE;
		}
		SetMouseDispFlag(FALSE);

		player.CenterX = startPt.x;
		player.CenterY = startPt.y;

		player.image.x = player.CenterX;
		player.image.y = player.CenterY;

		player.collBeforePt.x = player.CenterX;
		player.collBeforePt.y = player.CenterY;

		SetMousePoint(player.image.x, player.image.y);

		GameEndKind = GAME_END_FAIL;
	}

	if (MY_KEY_UP(KEY_INPUT_RETURN) == TRUE && Kchoice == TRUE) {
		CLICK_M = TRUE;
		//GameScene = GAME_SCENE_PLAY;
		GameScene = GAME_SCENE_EXPO;
		MusicPass = TRUE;
		MY_MAP_RELOAD = TRUE;
	}


	//����������
	if (ImageChar[1].IsDraw == FALSE && MY_CHAR_MOVE_ST == TRUE) {
		ImageChar[1].IsDraw = TRUE;
		MY_CHAR_MOVE_ST = FALSE;
	}

	if (ImageWork.Cnt < ImageWork.CntMAX)
	{
		ImageWork.Cnt += IMAGE_TITLE_WORK_CNT;
	}
	else
	{
		if (ImageChar[1].IsDraw == TRUE)
		{
			ImageChar[1].IsDraw = FALSE;

			switch (DrCharCnt)
			{
			case 0: 
				ImageChar[0].IsDraw = TRUE;
				DrCharCnt = 1;
				break;
			case 1:
				ImageChar[2].IsDraw = TRUE;
				DrCharCnt = 0;
				break;
			default:
				break;
			}
		}
		else if (ImageChar[0].IsDraw == TRUE || ImageChar[2].IsDraw == TRUE)//1
		{
			if (DrCharCnt == 1)
			ImageChar[0].IsDraw = FALSE;

			if (DrCharCnt == 0)
				ImageChar[2].IsDraw = FALSE;

			ImageChar[1].IsDraw = TRUE;
		}
		
		for (int num = 0; num < IMAGE_CHAR_NUM; num++) {
			ImageChar[num].image.x += 16;

			if (ImageChar[num].image.x > GAME_WIDTH) {
				ImageChar[num].image.x -= GAME_WIDTH + player.image.width;
			}
		}
		ImageWork.Cnt = 0;

	}

	//�^�C�}������
	timeCnt = 0;
	time = 0;
	mintime = 0;

	return;
}

VOID MY_START_DRAW(VOID)
{
	DrawGraph(ImageTitleBK.x, ImageTitleBK.y, ImageTitleBK.handle, TRUE);

	for (int num = 0; num < IMAGE_CHAR_NUM; num++)
	{
		if (ImageChar[num].IsDraw == TRUE)
		{
			DrawGraph(ImageChar[num].image.x, ImageChar[num].image.y, ImageChar[num].image.handle, TRUE);
		}
	}

	DrawGraph(ImageTitleROGO.image.x, ImageTitleROGO.image.y, ImageTitleROGO.image.handle, TRUE);
	
	DrawRotaGraph(
		ImageTitleSTART.image.x, ImageTitleSTART.image.y,
		ImageTitleSTART.rate,
		ImageTitleSTART.angle,
		ImageTitleSTART.image.handle, TRUE);

	DrawRotaGraph(
		ImageTitleRNK.image.x, ImageTitleRNK.image.y,
		ImageTitleRNK.rate,
		ImageTitleRNK.angle,
		ImageTitleRNK.image.handle, TRUE);


	if (Kchoice == TRUE) {
		ImageTitleSTART.rate = 1.2;
		ImageTitleRNK.rate = 1.0;
	}
	else {
		ImageTitleSTART.rate = 1.0;
		ImageTitleRNK.rate = 1.2;
	}

	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE) {
		if (Kchoice == TRUE) 
			ImageTitleSTART.rate = 0.8;
		else 
			ImageTitleRNK.rate = 0.8;
	}
	if (MY_KEY_UP(KEY_INPUT_RETURN) == TRUE) {
		ImageTitleSTART.rate = 1.0;
		ImageTitleRNK.rate = 1.0;
	}
	//DrawString(0, 0, "�X�^�[�g���(�G���^�[�L�[�������ĉ�����)", GetColor(255, 255, 255));
	return;
}

VOID MY_EXPO(VOID)
{
	MY_EXPO_PROC();
	MY_EXPO_DRAW();

	return;
}

VOID MY_EXPO_PROC(VOID) {
	if (CheckSoundMem(BGM_TITLE.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, BGM_TITLE.handle);
		PlaySoundMem(BGM_TITLE.handle, DX_PLAYTYPE_LOOP);
	}

	if (MY_KEY_DOWN(KEY_INPUT_RETURN)) {
		if (CLICK_M == TRUE)
		{
			PlaySoundMem(player.musicShot.handle, DX_PLAYTYPE_BACK);
			CLICK_M = FALSE;
		}
	}

	switch (ExDrawCnt)
	{
	case 1:
		if (MY_KEY_UP(KEY_INPUT_RETURN)) {
			ExDrawCnt = 2;
			CLICK_M = TRUE;
		}
		break;
	case 2:
		if (MY_KEY_UP(KEY_INPUT_RETURN)) {
			ExDrawCnt = 3;
			CLICK_M = TRUE;
		}
		break;
	case 3:
		if (MY_KEY_UP(KEY_INPUT_RETURN)) {
			ExDrawCnt = 1;
			CLICK_M = TRUE;

			if (CheckSoundMem(BGM_TITLE.handle) != 0)
			{
				StopSoundMem(BGM_TITLE.handle);
			}
			GameScene = GAME_SCENE_PLAY;
		}
		break;
	}

	return;
}

VOID MY_EXPO_DRAW(VOID) {
	switch (ExDrawCnt)
	{
	case 1:
		DrawGraph(ImageBackEND.image.x, ImageBackEND.image.y, ImageBackEND.image.handle, TRUE);
		break;
	case 2:
		DrawGraph(ImageBackENDF.image.x, ImageBackENDF.image.y, ImageBackENDF.image.handle, TRUE);
		break;
	case 3:
		DrawGraph(ImageBackEND.image.x, ImageBackEND.image.y, ImageBackEND.image.handle, TRUE);
		break;
	}
	DrawRotaGraph(
		ImageEndROGO.image.x, ImageEndROGO.image.y,
		ImageEndROGO.rate,
		ImageEndROGO.angle,
		ImageEndROGO.image.handle, TRUE);

	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
		ImageEndROGO.rate = 0.8;

	if (MY_KEY_UP(KEY_INPUT_RETURN) == TRUE) {
		FALL_RESON = FALSE;
		ImageEndROGO.rate = 1.0;
	}
	return;
}

VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();
	MY_PLAY_DRAW();

	return;
}

VOID MY_PLAY_PROC(VOID)
{
	if (CheckSoundMem(BGM.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, BGM.handle);

		PlaySoundMem(BGM.handle, DX_PLAYTYPE_LOOP);
	}

	//�^�C�}����
	if (timeCnt >= 60)
	{
		time = time - 0.016 * timeCnt;
		timeCnt = 0;
		time++;
	}
	if (time >= 60)
	{
		time = 0;
		mintime++;
	}
	time += 0.016;
	timeCnt++;

	//�}�b�v������
	if (MY_MAP_RELOAD == TRUE) {
		for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
			{
				if (mapDataPR[tate][yoko] == lp) {
					mapData[tate][yoko] = l;
					map[tate][yoko].kind = l;
				}
				else if (mapDataPR[tate][yoko] == tp) {
					mapData[tate][yoko] = t;
					map[tate][yoko].kind = t;
				}
			}
		}
		MY_MAP_RELOAD = FALSE;
	}

	if (mouse.Button[MOUSE_INPUT_RIGHT] == TRUE)
	{
		iPOINT R_ClickPt = mouse.Point;

		SetMouseDispFlag(TRUE);

		int Ret = MessageBox(GetMainWindowHandle(), MOUSE_R_CLICK_CAPTION, MOUSE_R_CLICK_TITLE, MB_YESNO);

		if (Ret == IDYES)
		{
			if (CheckSoundMem(BGM.handle) != 0)
			{
				StopSoundMem(BGM.handle);
			}

			SetMouseDispFlag(TRUE);

			GameScene = GAME_SCENE_START;
			return;

		}
		else if (Ret == IDNO)
		{
			SetMousePoint(R_ClickPt.x, R_ClickPt.y);

			SetMouseDispFlag(FALSE);
		}
	}



	//���̓��͔���i�������ƂƂ��j
	if (MY_KEY_TF == TRUE) {
		if (MY_KEY_DOWN(KEY_INPUT_W)) {
			player.CenterY -= MOVE_ERIA;
			MY_KEY_TF = FALSE;
		}

		if (MY_KEY_DOWN(KEY_INPUT_A)) {
			player.CenterX -= MOVE_ERIA;
			MY_KEY_TF = FALSE;
		}

		if (MY_KEY_DOWN(KEY_INPUT_S)) {
			player.CenterY += MOVE_ERIA;
			MY_KEY_TF = FALSE;
		}

		if (MY_KEY_DOWN(KEY_INPUT_D)) {
			player.CenterX += MOVE_ERIA;
			MY_KEY_TF = FALSE;
		}

	}

	//���̓��͔���i�������Ƃ��j
	if (MY_KEY_TF == FALSE) {
		if (MY_KEY_UP(KEY_INPUT_W) || MY_KEY_UP(KEY_INPUT_A) || MY_KEY_UP(KEY_INPUT_S) || MY_KEY_UP(KEY_INPUT_D)) {
			MY_KEY_TF = TRUE;
		}
	}

	player.coll.left = player.CenterX - mapChip.width / 2 + 5;
	player.coll.top = player.CenterY - mapChip.height / 2 + 5;
	player.coll.right = player.CenterX + mapChip.width / 2 - 5;
	player.coll.bottom = player.CenterY + mapChip.height / 2 - 5;

	//����������
	direc = MY_DIRECTION(player.CenterX, player.CenterY, player.collBeforePt.x, player.collBeforePt.y);

	BOOL IsMove = TRUE;


	if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
	{
		IsMove = FALSE;

		newX = (player.CenterX - MAP_DIV_WIDTH / 2) / MAP_DIV_WIDTH;
		newY = (player.CenterY - MAP_DIV_WIDTH / 2) / MAP_DIV_WIDTH;

		if (mapData[newY][newX] == l || map[newY][newX].kind == l)
		{
			//�}�b�v�̍X�V
			BOOL IsReMove = FALSE;

			if (IsReMove == FALSE)
			{
				int reN = 0;
				switch (direc)
				{
				case 'W':
					reN = newY - 1;
					if (mapData[reN][newX] == t)
					{
						mapData[reN][newX] = mapData[newY][newX];
						map[reN][newX].kind = map[newY][newX].kind;
						IsReMove = TRUE;
					}
					break;
				case 'S':
					reN = newY + 1;
					if (mapData[reN][newX] == t)
					{
						mapData[reN][newX] = mapData[newY][newX];
						map[reN][newX].kind = map[newY][newX].kind;
						IsReMove = TRUE;
					}
					break;
				case 'A':
					reN = newX - 1;
					if (mapData[newY][reN] == t)
					{
						mapData[newY][reN] = mapData[newY][newX];
						map[newY][reN].kind = map[newY][newX].kind;
						IsReMove = TRUE;
					}
					break;
				case 'D':
					reN = newX + 1;
					if (mapData[newY][reN] == t)
					{
						mapData[newY][reN] = mapData[newY][newX];
						map[newY][reN].kind = map[newY][newX].kind;
						IsReMove = TRUE;
					}
					break;
				default:
					break;

				}
				for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
				{
					for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
					{
						if (mapData[tate][yoko] == g) {
							if (mapData[tate + 1][yoko] == l) {
								if (CheckSoundMem(BGM.handle) != 0)
								{
									StopSoundMem(BGM.handle);
								}

								FALL_RESON = TRUE;

								SetMouseDispFlag(TRUE);

								GameEndKind = GAME_END_FAIL;

								GameScene = GAME_SCENE_END;

								return;
							}
						}
					}
				}

			}
			if (IsReMove == TRUE)
			{
				//�����蔻��X�V���摜�폜
				mapData[newY][newX] = t;
				map[newY][newX].kind = t;
				IsReMove = FALSE;
			}//�}�b�v�X�V�����܂�
		}

		//���̈ʒu�ɖ߂�
		player.CenterX = player.collBeforePt.x;
		player.CenterY = player.collBeforePt.y;
	}

	if (IsMove == TRUE)
	{
		player.image.x = player.CenterX - player.image.width / 2;
		player.image.y = player.CenterY - player.image.height / 2;

		player.collBeforePt.x = player.CenterX;
		player.collBeforePt.y = player.CenterY;
	}

	RECT PlayerRect;
	int CollRange = 5;
	PlayerRect.left = player.image.x + player.image.width / 2 - CollRange;
	PlayerRect.top = player.image.y + player.image.height / 2 - CollRange;
	PlayerRect.right = player.image.x + player.image.width / 2 + CollRange;
	PlayerRect.bottom = player.image.y + player.image.height / 2 + CollRange;

	if (MY_CHECK_RECT_COLL(PlayerRect, GoalRect) == TRUE)
	{
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);
		}

		SetMouseDispFlag(TRUE);

		GameEndKind = GAME_END_COMP;

		GameScene = GAME_SCENE_END;

		return;
	}

	if (player.image.x > GAME_WIDTH || player.image.y > GAME_HEIGHT
		|| player.image.x + player.image.width < 0 || player.image.y + player.image.height < 0)
	{

		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);
		}

		SetMouseDispFlag(TRUE);

		GameEndKind = GAME_END_FAIL;

		GameScene = GAME_SCENE_END;

		return;
	}

	return;
}

VOID MY_PLAY_DRAW(VOID)
{
	DrawGraph(ImageBack.image.x, ImageBack.image.y, ImageBack.image.handle, TRUE);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			DrawGraph(
				map[tate][yoko].x,
				map[tate][yoko].y,
				mapChip.handle[map[tate][yoko].kind],
				TRUE);
		}
	}


	if (time >= 60 || mintime >= 1) {
		DrawFormatString(0, 10, GetColor(255, 255, 255), "TIME:%d��%.2f�b", mintime, time);
	}
	else
	{
		DrawFormatString(0, 10, GetColor(255, 255, 255), "TIME:%.2f�b", time);

	}

	////�����蔻��̕`��i�f�o�b�O�p�j
	//for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	//{
	//	for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
	//	{
	//		//�ǂȂ��
	//		if (mapData[tate][yoko] == k || mapData[tate][yoko] == l)
	//		{
	//			DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(0, 0, 255), FALSE);
	//		}

	//		//�ʘH�Ȃ��
	//		if (mapData[tate][yoko] == t)
	//		{
	//			DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(255, 255, 0), FALSE);
	//		}
	//	}
	//}

	////�S�[���̕`��i�f�o�b�O�p�j
	//DrawBox(GoalRect.left, GoalRect.top, GoalRect.right, GoalRect.bottom, GetColor(255, 255, 0), TRUE);

	//�v���C���[�̂�`�悷��
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);

	//�����蔻��̕`��i�f�o�b�O�p�j
	//DrawBox(player.coll.left, player.coll.top, player.coll.right, player.coll.bottom, GetColor(255, 0, 0), FALSE);

	SetFontSize(20);
	DrawString(68, GAME_HEIGHT - 32, "! �ړ��L�[�FW�y���zA�y���zS�y���zD�y���z|�@�^�C�g���ɖ߂�y�E�N���b�N�z!", GetColor(255, 255, 255));
	SetFontSize(16.5);
	return;
}

VOID MY_END(VOID)
{
	MY_END_PROC();
	MY_END_DRAW();
	return;
}

VOID MY_END_PROC(VOID)
{
	static BOOL MusicPass1 = TRUE;
	if (MY_KEY_DOWN(KEY_INPUT_BACK) == TRUE)
	{
		if (CLICK_M == TRUE)
		{
			PlaySoundMem(player.musicShot.handle, DX_PLAYTYPE_BACK);
			CLICK_M = FALSE;
		}
		if (CheckSoundMem(BGM_COMP.handle) != 0)
		{
			StopSoundMem(BGM_COMP.handle);
		}

		if (CheckSoundMem(BGM_FAIL.handle) != 0)
		{
			StopSoundMem(BGM_FAIL.handle);
		}

		MusicPass1 = FALSE;
	}
	
	if (MY_KEY_UP(KEY_INPUT_BACK) == TRUE) {
		CLICK_M = TRUE;

		SetMouseDispFlag(TRUE);

		GameScene = GAME_SCENE_START;

		MusicPass1 = TRUE;

		return;
	}

	switch (GameEndKind)
	{
	case GAME_END_COMP:

		if (CheckSoundMem(BGM_COMP.handle) == 0 && MusicPass1 == TRUE)
		{
			ChangeVolumeSoundMem(255 * 50 / 100, BGM_COMP.handle);
			PlaySoundMem(BGM_COMP.handle, DX_PLAYTYPE_LOOP);
		}
		break;

	case GAME_END_FAIL:

		if (CheckSoundMem(BGM_FAIL.handle) == 0 && MusicPass1 == TRUE)
		{
			ChangeVolumeSoundMem(255 * 50 / 100, BGM_FAIL.handle);
			PlaySoundMem(BGM_FAIL.handle, DX_PLAYTYPE_LOOP);
		}

		break;
	}

	return;
}

VOID MY_END_DRAW(VOID)
{
	MY_PLAY_DRAW();

	switch (GameEndKind)
	{
	case GAME_END_COMP:
		DrawGraph(ImageBackEND.image.x, ImageBackEND.image.y, ImageBackEND.image.handle, TRUE);

		DrawGraph(ImageEndCOMP.image.x, ImageEndCOMP.image.y, ImageEndCOMP.image.handle, TRUE);
		
		SetFontSize(64);

		if (mintime >= 1)
			DrawFormatString(GAME_WIDTH / 4 - 64, GAME_HEIGHT / 4 * 3, GetColor(255, 255, 255), "�E%d��%.2f�b", mintime, time);
		else
			DrawFormatString(GAME_WIDTH / 4 - 64, GAME_HEIGHT / 4 * 3, GetColor(255, 255, 255), "�E%.2f�b", time);

		SetFontSize(16.5);

		break;

	case GAME_END_FAIL:
		DrawGraph(ImageBackENDF.image.x, ImageBackENDF.image.y, ImageBackENDF.image.handle, TRUE);

		DrawGraph(ImageEndFAIL.image.x, ImageEndFAIL.image.y, ImageEndFAIL.image.handle, TRUE);
	
		if (FALL_RESON == TRUE) {
			SetFontSize(64);

			DrawString(GAME_WIDTH / 2 - 320, GAME_HEIGHT / 4 * 3, "�S�[�����ǂ���܂���", GetColor(255, 0, 0));
			SetFontSize(16.5);

		}
		break;
	}

	DrawRotaGraph(
		ImageEndROGO.image.x, ImageEndROGO.image.y,
		ImageEndROGO.rate,
		ImageEndROGO.angle,
		ImageEndROGO.image.handle, TRUE);

	if (MY_KEY_DOWN(KEY_INPUT_BACK) == TRUE)
		ImageEndROGO.rate = 0.8;

	if (MY_KEY_UP(KEY_INPUT_BACK) == TRUE) {
		FALL_RESON = FALSE;
		ImageEndROGO.rate = 1.0;
	}
	return;
}

BOOL MY_LOAD_IMAGE(VOID)
{
//�^�C�g���w�i
	strcpy_s(ImageTitleBK.path, IMAGE_TITLE_BK_PATH);
	ImageTitleBK.handle = LoadGraph(ImageTitleBK.path);
	if (ImageTitleBK.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleBK.handle, &ImageTitleBK.width, &ImageTitleBK.height);
	ImageTitleBK.x = GAME_WIDTH / 2 - ImageTitleBK.width / 2;
	ImageTitleBK.y = GAME_HEIGHT / 2 - ImageTitleBK.height / 2;

//�^�C�g�����S
	strcpy_s(ImageTitleROGO.image.path, IMAGE_TITLE_ROGO_PATH);
	ImageTitleROGO.image.handle = LoadGraph(ImageTitleROGO.image.path);
	if (ImageTitleROGO.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleROGO.image.handle, &ImageTitleROGO.image.width, &ImageTitleROGO.image.height);
	ImageTitleROGO.image.x = GAME_WIDTH / 2 - ImageTitleROGO.image.width / 2;
	ImageTitleROGO.image.y = GAME_HEIGHT / 2 - ImageTitleROGO.image.height / 2;

//�^�C�g���X�^�[�g
	strcpy_s(ImageTitleSTART.image.path, IMAGE_TITLE_START_PATH);
	ImageTitleSTART.image.handle = LoadGraph(ImageTitleSTART.image.path);
	if (ImageTitleSTART.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_START_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleSTART.image.handle, &ImageTitleSTART.image.width, &ImageTitleSTART.image.height);
	ImageTitleSTART.image.x = GAME_WIDTH / 2;
	ImageTitleSTART.image.y = ImageTitleROGO.image.y + ImageTitleROGO.image.height + 32;
	ImageTitleSTART.angle = 0;
	ImageTitleSTART.rate = 1.0;

//�����L���O�I��
	strcpy_s(ImageTitleRNK.image.path, IMAGE_TITLE_START_PATH);
	ImageTitleRNK.image.handle = LoadGraph(ImageTitleRNK.image.path);
	if (ImageTitleRNK.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_START_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleRNK.image.handle, &ImageTitleRNK.image.width, &ImageTitleRNK.image.height);
	ImageTitleRNK.image.x = GAME_WIDTH / 2;
	ImageTitleRNK.image.y = ImageTitleROGO.image.y + ImageTitleROGO.image.height + 64;
	ImageTitleRNK.angle = 0;
	ImageTitleRNK.rate = 1.0;

//�����摜�i�^�C�g���j
	strcpy_s(ImageChar[0].image.path, IMAGE_CHAR_PATH);			//�p�X�̐ݒ�
	strcpy_s(ImageChar[1].image.path, IMAGE_CHAR_1_PATH);		//�p�X�̐ݒ�(�w�i�摜���])
	strcpy_s(ImageChar[2].image.path, IMAGE_CHAR_2_PATH);			//�p�X�̐ݒ�

	for (int num = 0; num < IMAGE_CHAR_NUM; num++)
	{
		ImageChar[num].image.handle = LoadGraph(ImageChar[num].image.path);	//�ǂݍ���
		if (ImageChar[num].image.handle == -1)
		{
			//�G���[���b�Z�[�W�\��
			MessageBox(GetMainWindowHandle(), IMAGE_CHAR_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
			return FALSE;
		}
		//�摜�̕��ƍ������擾
		GetGraphSize(ImageChar[num].image.handle, &ImageChar[num].image.width, &ImageChar[num].image.height);
		ImageWork.Cnt = 0.0;
		ImageWork.CntMAX = IMAGE_TITLE_WORK_CNT_MAX;

	}
//�L�����̐ݒ�
	ImageChar[0].image.x = GAME_WIDTH / 2 - ImageChar[0].image.width / 2;	//���E��������
	ImageChar[0].image.y = GAME_HEIGHT - ImageChar[0].image.height;			//y�͌��_����
	ImageChar[0].IsDraw = FALSE;

	ImageChar[1].image.x = GAME_WIDTH / 2 - ImageChar[1].image.width / 2;	//���E��������
	ImageChar[1].image.y = GAME_HEIGHT - ImageChar[1].image.height;			//y�͌��_����
	ImageChar[1].IsDraw = FALSE;

	ImageChar[2].image.x = GAME_WIDTH / 2 - ImageChar[2].image.width / 2;	//���E��������
	ImageChar[2].image.y = GAME_HEIGHT - ImageChar[2].image.height;			//y�͌��_����
	ImageChar[2].IsDraw = FALSE;

//�G���h�R���v
	strcpy_s(ImageEndCOMP.image.path, IMAGE_END_COMP_PATH);
	ImageEndCOMP.image.handle = LoadGraph(ImageEndCOMP.image.path);
	if (ImageEndCOMP.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_END_COMP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageEndCOMP.image.handle, &ImageEndCOMP.image.width, &ImageEndCOMP.image.height);
	ImageEndCOMP.image.x = GAME_WIDTH / 2 - ImageEndCOMP.image.width / 2;
	ImageEndCOMP.image.y = GAME_HEIGHT / 2 - ImageEndCOMP.image.height / 2 - 32;

//�G���h�t�H�[��
	strcpy_s(ImageEndFAIL.image.path, IMAGE_END_FAIL_PATH);
	ImageEndFAIL.image.handle = LoadGraph(ImageEndFAIL.image.path);
	if (ImageEndFAIL.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_END_FAIL_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageEndFAIL.image.handle, &ImageEndFAIL.image.width, &ImageEndFAIL.image.height);
	ImageEndFAIL.image.x = GAME_WIDTH / 2 - ImageEndFAIL.image.width / 2;
	ImageEndFAIL.image.y = GAME_HEIGHT / 2 - ImageEndFAIL.image.height / 2 - 32;

//�G�X�P�[�v�v�b�V��
	strcpy_s(ImageEndROGO.image.path, IMAGE_END_ROGO_PATH);
	ImageEndROGO.image.handle = LoadGraph(ImageEndROGO.image.path);
	if (ImageEndROGO.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_END_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageEndROGO.image.handle, &ImageEndROGO.image.width, &ImageEndROGO.image.height);
	ImageEndROGO.image.x = GAME_WIDTH - 70;
	ImageEndROGO.image.y = GAME_HEIGHT - 50;
	ImageEndROGO.angle = 0; 
	ImageEndROGO.rate = 1.0;


//�w�i�摜
	strcpy_s(ImageBack.image.path, IMAGE_BACK_PATH);
	ImageBack.image.handle = LoadGraph(ImageBack.image.path);
	if (ImageBack.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_BACK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageBack.image.handle, &ImageBack.image.width, &ImageBack.image.height);
	ImageBack.image.x = GAME_WIDTH / 2 - ImageBack.image.width / 2;
	ImageBack.image.y = 0 - ImageBack.image.height * 0;
	ImageBack.IsDraw = FALSE;

//�w�i�摜END
	strcpy_s(ImageBackEND.image.path, IMAGE_BACK_ENDC_PATH);
	ImageBackEND.image.handle = LoadGraph(ImageBackEND.image.path);
	if (ImageBackEND.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_BACK_ENDC_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageBackEND.image.handle, &ImageBackEND.image.width, &ImageBackEND.image.height);
	ImageBackEND.image.x = GAME_WIDTH / 2 - ImageBackEND.image.width / 2;
	ImageBackEND.image.y = 0 - ImageBackEND.image.height * 0;
	ImageBackEND.IsDraw = FALSE;

//�w�i�摜ENDF
	strcpy_s(ImageBackENDF.image.path, IMAGE_BACK_ENDF_PATH);
	ImageBackENDF.image.handle = LoadGraph(ImageBackENDF.image.path);
	if (ImageBackENDF.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_BACK_ENDF_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageBackENDF.image.handle, &ImageBackENDF.image.width, &ImageBackENDF.image.height);
	ImageBackENDF.image.x = GAME_WIDTH / 2 - ImageBackENDF.image.width / 2;
	ImageBackENDF.image.y = 0 - ImageBackENDF.image.height * 0;
	ImageBackENDF.IsDraw = FALSE;


//�v���C���[�̉摜
	strcpy_s(player.image.path, IMAGE_PLAYER_PATH);
	player.image.handle = LoadGraph(player.image.path);
	if (player.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.image.handle, &player.image.width, &player.image.height);
	player.image.x = GAME_WIDTH / 2 - player.image.width / 2;
	player.image.y = GAME_HEIGHT / 2 - player.image.height / 2;
	player.CenterX = player.image.x + player.image.width / 2;
	player.CenterY = player.image.y + player.image.height / 2;
	player.speed = CHARA_SPEED_LOW;

//�}�b�v�̉摜�𕪊�����
	int mapRes = LoadDivGraph(
		GAME_MAP_PATH,
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,
		&mapChip.handle[0]);

	if (mapRes == -1)
	{
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			mapDataInit[tate][yoko] = mapData[tate][yoko];

			map[tate][yoko].kind = mapData[tate][yoko];

			map[tate][yoko].width = mapChip.width;
			map[tate][yoko].height = mapChip.height;

			map[tate][yoko].x = yoko * map[tate][yoko].width;
			map[tate][yoko].y = tate * map[tate][yoko].height;
		}
	}

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
			mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
			mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
		}
	}

	return TRUE;
}

VOID MY_DELETE_IMAGE(VOID)
{

	DeleteGraph(ImageBack.image.handle);

	for (int num = 0; num < IMAGE_CHAR_NUM; num++)
	{
		DeleteGraph(ImageChar[0].image.handle);
	}

	DeleteGraph(player.image.handle);

	DeleteGraph(ImageTitleBK.handle);
	DeleteGraph(ImageTitleROGO.image.handle);
	DeleteGraph(ImageTitleSTART.image.handle);
	DeleteGraph(ImageTitleRNK.image.handle);
	DeleteGraph(ImageEndCOMP.image.handle);
	DeleteGraph(ImageEndFAIL.image.handle);
	DeleteGraph(ImageEndROGO.image.handle);


	for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++) { DeleteGraph(mapChip.handle[i_num]); }

	return;
}

BOOL MY_LOAD_MUSIC(VOID)
{
	strcpy_s(BGM.path, MUSIC_BGM_PATH);
	BGM.handle = LoadSoundMem(BGM.path);
	if (BGM.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	strcpy_s(player.musicShot.path, MUSIC_PLAYER_SHOT_PATH);
	player.musicShot.handle = LoadSoundMem(player.musicShot.path);
	if (player.musicShot.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_PLAYER_SHOT_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	strcpy_s(BGM_TITLE.path, MUSIC_BGM_TITLE_PATH);
	BGM_TITLE.handle = LoadSoundMem(BGM_TITLE.path);
	if (BGM_TITLE.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_TITLE_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	strcpy_s(BGM_COMP.path, MUSIC_BGM_COMP_PATH);
	BGM_COMP.handle = LoadSoundMem(BGM_COMP.path);
	if (BGM_COMP.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_COMP_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	strcpy_s(BGM_FAIL.path, MUSIC_BGM_FAIL_PATH);
	BGM_FAIL.handle = LoadSoundMem(BGM_FAIL.path);
	if (BGM_FAIL.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_FAIL_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(BGM.handle);
	DeleteSoundMem(player.musicShot.handle);
	DeleteSoundMem(BGM_TITLE.handle);
	DeleteSoundMem(BGM_COMP.handle);
	DeleteSoundMem(BGM_FAIL.handle);

	return;
}

BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT player)
{
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
			{
				if (map[tate][yoko].kind == k) { return TRUE; }
				if (map[tate][yoko].kind == l) { return TRUE; }
				if (map[tate][yoko].kind == m) { return TRUE; }
				if (map[tate][yoko].kind == r) { return TRUE; }

			}
		}
	}

	return FALSE;
}

BOOL MY_CHECK_RECT_COLL(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top
		)
	{
		return TRUE;
	}

	return FALSE;
}

//�������������Ƃ�
CHAR MY_DIRECTION(double x, double y, double oldx, double oldy)
{
	if (x != oldx) {
		if (x < oldx)
			return 'A';
		else
			return 'D';
	}
	if (y != oldy) {
		if (y < oldy)
			return 'W';
		else
			return 'S';
	}
}