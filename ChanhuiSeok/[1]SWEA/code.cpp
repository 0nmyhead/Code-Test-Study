#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <map>
#include <stack>
#include <string>

#define UP 1
#define LEFT_UP 2
#define LEFT 3
#define LEFT_DOWN 4
#define DOWN 5
#define RIGHT_DOWN 6
#define RIGHT 7
#define RIGHT_UP 8
#define EMPTY -1
#define SHARK_NUM 30

using namespace std;

int dy[] = {0, -1,-1,0,1,1,1,0,-1 };
int dx[] = {0, 0,-1,-1,-1,0,1,1,1 };

typedef struct fish {
	int y;
	int x;
	int dir;
	bool isDead;
}Fish;

int dfs(int origin_board[][4], Fish origin_fish[17], int y, int x, int dir) {

	// ������ ������
	int board[4][4];
	Fish fish[17];

	int total = 0;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			board[i][j] = origin_board[i][j];

	for (int i = 0; i <= 16; i++)
		fish[i] = origin_fish[i];

	// �� (y, x)�� ���� ���̸� �̿� �ش��ϴ� (����) ��ȣ �� ����
	// ���� ���� ����� ��ġ�� y, x �̴�.
	total = board[y][x];

	// ������ ���� �� �ڸ��� �ִ� ������� ������ �״�� ������.
	dir = fish[board[y][x]].dir;

	// (y, x) �ڸ��� �ִ� ������ �״´�.
	fish[board[y][x]].isDead = true;
	fish[board[y][x]].y = -1;
	fish[board[y][x]].x = -1;

	// board���� ���� ĭ�� �����.
	board[y][x] = 0;

	// ��� ����⿡ ���ؼ� �̵��� ���Ѻ���.
	for (int i = 1; i <= 16; i++) {

		bool flag = false;
		// ���� ���� ����⿡ ���ؼ��� �̵��� ���Ѻ���.
		if (fish[i].isDead == false) {
			int ay, ax;
			// ������ �� �� ���� ������ ������ 8���� ��� ���ƺ���.
			for (int k = 0; k < 8; k++) {
				ay = fish[i].y + dy[fish[i].dir];
				ax = fish[i].x + dx[fish[i].dir];

				// ����Ⱑ ������ �ϴ� ���� ����� ���
				if (ay == y && ax == x) {
					// ���� �������� ������.
					fish[i].dir = (fish[i].dir) % 8 + 1;
					continue;
				}

				// ���� �ٱ��� ���
				if (ay >= 4 || ay < 0 || ax >= 4 || ax < 0) {
					// ���� �������� ������.
					fish[i].dir = (fish[i].dir) % 8 + 1;
					continue;
				}

				// �� �� ���� ���
				flag = true;
				break;
			}

			// 8���� ��� ���ƺ��� �� �� �ִ� ���� �־��� ���
			if (flag) {

				// ������ �ϴ� ���� �� ĭ�̾��� ���
				// �׳� �� �ڸ��� ����⸦ ������ �ȴ�.
				if (board[ay][ax] == 0) {
					board[fish[i].y][fish[i].x] = 0;
					fish[i].y = ay;
					fish[i].x = ax;
					board[ay][ax] = i;
				}

				// ������ �ϴ� ��(ay, ax)�� ����Ⱑ �־��� ���
				// ���� �ڸ��� �ٲ� �ش�.
				else if (board[ay][ax] != 0) {
					int ty, tx, tDir, tmp;
					tx = fish[i].x;
					ty = fish[i].y;
					//tDir = fish[i].dir;

					fish[i].x = ax;
					fish[i].y = ay;

					fish[board[ay][ax]].x = tx;
					fish[board[ay][ax]].y = ty;
					//fish[board[ay][ax]].dir = tDir;

					board[ty][tx] = board[ay][ax];
					board[ay][ax] = i;

				}
			}
		}
	}

	// ��� �̵��� ���� �� �̵����� ����.
	int sy = y + dy[dir];
	int sx = x + dx[dir];

	int ans = 0;

	// �� �������� �� �̵� ������ ������
	while (!(sy < 0 || sy >= 4 || sx < 0 || sx >= 4)) {
		// �� �̵��� ���� ĭ�� �� ĭ�� �ƴ� ���
		if (board[sy][sx] != 0) {
			ans = max(ans, dfs(board, fish, sy, sx, dir));
		}
		sy = sy + dy[dir];
		sx = sx + dx[dir];
	}

	return total + ans;
}


int main() {
	
	ios::sync_with_stdio(0);
	cin.tie(0);

	Fish fish[17];
	int board[4][4];
	int a, b;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> a >> b; // a�� ��ȣ, b�� ����
			fish[a].dir = b;
			fish[a].y = i;
			fish[a].x = j;
			fish[a].isDead = false;
			board[i][j] = a;
		}
	}
	// ����� ���� �Ϸ�

	int ans = dfs(board, fish, 0, 0, 0);

	cout << ans;

	return 0;
}