#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

typedef struct shark {
	int r;
	int c;
	int dir;
	int speed;
	int size;
	bool isDead;
}Shark;

// ����� �����ӿ� ���� ��� ��ȣ�� �����.
int R, C, M;

int board[102][102];
int dy[5] = { 0,-1,1,0,0 };
int dx[5] = { 0,0,0,1,-1 };
// ��,�Ʒ�,������,����

int sum_size = 0;

Shark shark[10001];

// ��踦 �Ѵ��� Ȯ���ϴ� �Լ�
bool valid(int r, int c) {
	if (r > R || r <= 0 || c > C || c <= 0)
		return false;
	return true;
}

// ������ �ݴ�� �ٲ��ִ� �Լ�
int reverseDir(int dir) {
	if (dir == 1) return 2;
	if (dir == 2) return 1;
	if (dir == 3) return 4;
	if (dir == 4) return 3;
}

// �� �����̴� �Լ�
void moving() {
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			board[i][j] = 0;
		}
	}
	// board �迭���� �̵��� ��� ������ ���� ��ü������
	// ���ŵǾ� ���� ���̴�.

	// ��� ���� ���� �� ���ؼ� �����̱�
	for (int i = 1; i <= M; i++) {

		if (shark[i].isDead == false) {
			// ����� �ӷ°� ����		
			int speed = shark[i].speed;
			int rev_speed = 0;

			// ���� ������ ���
			if (shark[i].dir == 1 || shark[i].dir == 2) {
				rev_speed = speed % (2 * (R - 1));
			}
			else if (shark[i].dir == 3 || shark[i].dir == 4) {
				rev_speed = speed % (2 * (C - 1));
			}

			// �ӷ¸�ŭ �ݺ����� ���鼭 1ĭ�� �̵���Ű��
			for (int k = 0; k < rev_speed; k++) {
				int r = shark[i].r;
				int c = shark[i].c;
				int dir = shark[i].dir;

				int ty, tx;

				// ��踦 ���� �ʴ� ���
				if (valid(r + dy[dir], c + dx[dir])) {
					ty = r + dy[dir];
					tx = c + dx[dir];
					// �� ���� �״�� �̵���Ų��.
					shark[i].r = ty;
					shark[i].c = tx;
				}

				// ��踦 �Ѵ� ���
				else {
					// ������ �ٲ۴�.
					dir = reverseDir(dir);
					shark[i].dir = dir;
					ty = r + dy[dir];
					tx = c + dx[dir];

					// �װ����� �̵���Ų��.
					shark[i].r = ty;
					shark[i].c = tx;
				}
			}//end for

			// ���� ��� ��ġ
			int sy = shark[i].r;
			int sx = shark[i].c;

			// board�� �ƹ� �͵� ���� ��
			if (board[sy][sx] == 0) {
				board[sy][sx] = i;
				// ��� ��ȣ�� �����.
			}
			// ���� ������ ĭ�� ������ ũ�Ⱑ ���� �� �־��� ��,
			// �� �� ���̰� ���� �װ����� ����.
			else if (board[sy][sx] != 0 &&
				shark[board[sy][sx]].size < shark[i].size) {
				shark[board[sy][sx]].isDead = true;
				board[sy][sx] = i;
			}
			// ���� ������ ĭ�� ������ ũ�Ⱑ ū �� ���� ��,
			// �� �ڽ��� dead ǥ���Ѵ�.
			else if (board[sy][sx] != 0 &&
				shark[board[sy][sx]].size > shark[i].size) {
				shark[i].isDead = true;
			}
		}
	}
}

// �ùķ��̼� �Լ�
void simulation() {

	// ���ÿ��� ���������� �� ĭ �̵�
	for (int i = 1; i <= C; i++) {

		// ���ÿ��� ���� ����� �� ����
		for (int j = 1; j <= R; j++) {

			if (board[j][i] != 0) {
				int num = board[j][i];
				int shark_size = shark[num].size;
				sum_size += shark_size;
				shark[num].isDead = true;
				board[j][i] = 0;

				break;
			}
		}

		// ��� �̵�
		moving();
	}

}


int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> R >> C >> M;

	int r, c, s, d, z;
	for (int i = 1; i <= M; i++) {
		cin >> r >> c >> s >> d >> z;
		shark[i].r = r;
		shark[i].c = c;
		shark[i].dir = d;
		shark[i].speed = s;
		shark[i].isDead = false;
		shark[i].size = z;
	}

	// ����� ����ŭ board�� ����� ��ȣ�� ǥ���Ѵ�.
	for (int i = 1; i <= M; i++) {
		int r = shark[i].r;
		int c = shark[i].c;
		board[r][c] = i;
	}

	// �ùķ��̼� ����
	simulation();

	cout << sum_size;

	return 0;
}