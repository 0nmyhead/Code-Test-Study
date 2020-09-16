#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <map>
#include <stack>
#include <string>

using namespace std;

int dy[5] = { 0, -1, 1, 0, 0 };
int dx[5] = { 0, 0, 0, -1, 1 };

int board[21][21];
pair<int, int> smell[21][21];

typedef struct shark {
	int isDead;
	int dir;
	int y;
	int x;
	int rank[5][4];
}Shark;

Shark shark[401];
int N, M, k; // N�� ���� ũ��, M�� ��� ��, k�� �� k�� �̵��ϰ� ���� ������ ������� ��

bool valid(int y, int x) {

	if (y < 0 || x < 0 || y >= N || x >= N) {
		return false;
	}
	return true;
}

// �ϰ������� ��� ĭ�� ������ 1 ���ҽ�Ű�� �Լ�
void remove_smell() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == 0 && smell[i][j].second > 0) {
				smell[i][j].second -= 1;

				if (smell[i][j].second == 0) {
					smell[i][j].first = 0;
				}
			}
		}
	}
}


// ��� �� �����̴� �Լ�
void moving() {
	// 1. �⺻������ ���� ��,��,��,�� �� ������ ĭ���� �̵��Ѵ�. 
	// ��, �̵��ϴ� ������ �������� �ƹ� ������ ���� ĭ���� �̵��Ѵ�.
	// 2. ��,��,��,�� �� �켱������� �ѷ����鼭 ������ ���� ĭ�� ��������
	// ��,��,��,�� �� �ڱ� ������ �ִ� ĭ���� �̵��Ѵ�.

	// ��� �� ���ؼ� �̵���Ű��
	// �� ��� ������ �����ϴ� �� 1�� �ҿ�ȴٰ� ����
	for (int i = 1; i <= M; i++) {
		int dir = shark[i].dir; // i�� ����� ����
		int y = shark[i].y;
		int x = shark[i].x;

		bool isFind = false;

		// ���� ���� ���鿡 ���ؼ��� ����
		if (shark[i].isDead == false) {
			// ���� ���� ���� 4���� �켱������ ������ ĭ�� ���캻��.
			for (int j = 0; j < 4; j++) {
				int f_dir = shark[i].rank[dir][j]; // ���� ���� ���� �켱����
				int ty = y + dy[f_dir];
				int tx = x + dx[f_dir];

				// ��踦 ����� �ʾ��� ��� && ������ ������ ���
				if (valid(ty, tx) && smell[ty][tx].second == 0) {
					// ���� ������ ������ ����, �� �ڸ��� �� �̵����� ����.
					// �� �ڸ��� �� �� �� �� �����Ƿ�

					// �ٸ� �� ���� ���, ��� ��ȣ�� ���Ѵ�.
					if (board[ty][tx] != 0) {

						// ������ �ߴ� �ڸ��� ���� �� ��ȣ�� ���� ���
						// �� ��ȣ�� �� �ڸ��� ġ�� ����.
						// �׸��� ���� �� �ڸ��� �ִ� ���� ���ֹ�����.
						if (board[ty][tx] > i) {
							board[y][x] = 0; // �̵� ���� �� ĭ���� �ٲ�

							board[ty][tx] = i;
							shark[i].y = ty;
							shark[i].x = tx;
							shark[board[ty][tx]].isDead = true;
							isFind = true;

							// �̵��� ����� ���� ������ �ٲ۴�.
							shark[i].dir = f_dir;
						}

						// ������ �ߴ� �ڸ��� ���� �� ��ȣ�� Ŭ ���
						// ��� �� �ڽ��� �װ� �Ѵ�.
						else if (board[ty][tx] < i) {
							board[y][x] = 0;
							shark[i].isDead = true;
							isFind = true;
							break;
						}
					}

					// ������ �ϴ� ĭ�� �ƹ� �� ������ ���
					else {
						board[y][x] = 0; // �̵� ���� �� ĭ���� �ٲ�
						board[ty][tx] = i;
						shark[i].y = ty;
						shark[i].x = tx;
						isFind = true;

						// �̵��� ����� ���� ������ �ٲ۴�.
						shark[i].dir = f_dir;
					}

					break; // �̵��� �����Ƿ� ���� ���� �Ѿ��.
				}
			}


			// ��,��,��,�� ��� �� ĭ�� ������ ���, i�� ����� ������ �ִ� ������ �̵�
			if (!isFind) {
				// �ڽ��� ������ �ִ� ���� �ٽ� ã�´�.
				for (int j = 0; j < 4; j++) {
					int f_dir = shark[i].rank[dir][j]; // ���� ���� ���� �켱����
					int ty = y + dy[f_dir];
					int tx = x + dx[f_dir];

					// �ڽ��� ��ȣ�� ���� ���
					if (valid(ty, tx) && smell[ty][tx].first == i) {
						board[y][x] = 0; // �̵� ���� �� ĭ���� �ٲ�
						board[ty][tx] = i;
						shark[i].y = ty;
						shark[i].x = tx;

						// �̵��� ����� ���� ������ �ٲ۴�.
						shark[i].dir = f_dir;
						break;
					}
				}
			}
		}
	}

	// �̵��� ��� ��������, ���� �̵��� �� �ִ� ������ ������ �����.
	for (int i = 1; i <= M; i++) {
		// ���� ���� ���鿡 ���ؼ��� �����Ѵ�.
		if (shark[i].isDead == false) {
			int y = shark[i].y;
			int x = shark[i].x;

			smell[y][x].first = i;
			smell[y][x].second = k;
		}
	}
}

int simulation() {

	int time = 0; // 0�ʿ� ����

	while (time <= 1000) {

		// ���ڿ� 1�� �� �ִ��� Ȯ��
		bool flag = false;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (board[i][j] != 0 && board[i][j] != 1) {
					flag = true; // �ٸ��� �ִ�
					break;
				}
			}
		}
		if (!flag) break;

		// �� �̵���Ű��, ������ �����.
		moving();

		// �� ���� ���� ��� ���� 1�� ����
		
		remove_smell();

		// ��������� 1�� ���
		time += 1;	
	}

	if (time > 1000)
		return -1;
	
	return time;
}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M >> k;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
			if (board[i][j] != 0) {
				shark[board[i][j]].y = i;
				shark[board[i][j]].x = j;
			}
		}
	}


	// �� ����� �ʱ� ����	

	for (int i = 1; i <= M; i++) {
		int input;
		cin >> input;
		shark[i].dir = input;
	}

	// ����� ��ȣ�� 1������
	for (int i = 1; i <= M; i++) {
		for (int k = 1; k <= 4; k++) {
			for (int j = 0; j < 4; j++) {
				cin >> shark[i].rank[k][j];
			}
		}
	}

	// �ʱ⿡ �� �־����� �� ������ �ִٰ� ����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] != 0) {
				smell[i][j] = make_pair(board[i][j], k);
			}
		}
	}

	int res = simulation();
	cout << res;

	return 0;
}