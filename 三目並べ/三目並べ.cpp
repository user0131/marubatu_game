#include<stdio.h>
#include<conio.h>
#include<windows.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_SPACE 32


//マップデータ
#define MAP_H 5
#define MAP_W 6
char map[MAP_H][MAP_W] = {
	" | | ",
	"-----",
	" | | ",
	"-----",
	" | | "
};

//変数
int px = 0, py = 0;
int BLOCK[3][3];

//カーソル設置
void cursor(int y, int x) { printf("\x1b[%d;%dH", y + 1, x + 1); }

//色を指定する
enum { BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};
void color(int col) { printf("\x1b[3%dm", col); }

//ゲーム画面を描く
void drawMap(void) {
	for (int y = 0; y < MAP_H; y++) {
		for (int x = 0; x < MAP_W - 1; x++) {
			color(WHITE);
			cursor(y, x);
			printf("%c", map[y][x]);
		}
	}
}

void enemyTurn(void)
{
	Sleep(200);
	while (1)
	{
		int x = rand() % 3;
		int y = rand() % 3;
		if (BLOCK[y][x] == 0) continue;
		cursor(y * 2, x * 2);
		color(RED);
		map[y * 2][x * 2] = '*';
		BLOCK[y][x] = 0;
		break;
	}

}

//キーを押したときの処理
void keyMove(void)
{
	int key = 0;
	if (_kbhit()) key = _getch();
	if (key == KEY_UP)	py -= 2;
	if (key == KEY_DOWN) py+=2;
	if (key == KEY_LEFT ) px-=2;
	if (key == KEY_RIGHT ) px+=2;
	if (py < 0)  py = 0;
	if (py > MAP_H) py = MAP_H;
	if (px < 0)  px = 0;
	if (px > MAP_W - 1) px = MAP_W - 1;
	if (key == KEY_SPACE )
	{
		if (BLOCK[py / 2][px / 2] = 1)
		{
			color(BLUE);
			cursor(py, px);
			map[py][px] = 'o';
			BLOCK[py / 2][px / 2] = 0;
			enemyTurn();
		}
	}
}


int main(void)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			BLOCK[i][j] = 1;
		}
	}
	printf("\x1b[2J");
	while (1) 
	{
		keyMove();
		drawMap();
		color(MAGENTA);
		cursor(py, px);
		printf("o");
		for (int i = 0; i < 5; i+=2)
		{
			if (map[i][0] == 'o' && map[i][2] == 'o' && map[i][4] == 'o'||
				map[i][0] == '*' && map[i][2] == '*' && map[i][4] == '*') return -1;
		}
		for (int j = 0; j < 5; j += 2)
		{
			if (map[0][j] == 'o' && map[2][j] == 'o' && map[4][j] == 'o'||
				map[0][j] == '*' && map[2][j] == '*' && map[4][j] == '*') return -1;
		}
		if ((map[0][0] == 'o' && map[2][2] == 'o' && map[4][4] == 'o')||
			(map[0][4] == 'o' && map[2][2] == 'o' && map[4][0] == 'o')||
			(map[0][0] == '*' && map[2][2] == '*' && map[4][4] == '*')||
			(map[0][4] == '*' && map[2][2] == '*' && map[4][0] == '*'))  return -1;

		Sleep(50);
	}
}