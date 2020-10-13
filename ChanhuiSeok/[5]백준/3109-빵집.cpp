#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int R, C;
string arr[10001][501];
int visit[10001][501];

// ������ �� - ������ - ������ �Ʒ� ��
int dy[3] = { -1, 0, 1 };
int dx[3] = { 1, 1, 1 };

bool valid(int y, int x) {
	if (y < 0 || x < 0 || y >= R || x >= C || arr[y][x] == "x") {
		return false;
	}
	return true;
}

bool iterFlag = false;

void simulation(int y, int x) {
	
	// �� ���� �������� ���
	if (x == C - 1) {
		iterFlag = true;
		return;
	}

	for (int i = 0; i < 3; i++) {
		int ty = y + dy[i];
		int tx = x + dx[i];

		// ��ȿ�� ĭ�̰� �湮���� �ʾ��� ���� ��
		if (valid(ty, tx) && !visit[ty][tx]) {
			visit[ty][tx] = 1;
			simulation(ty, tx);
			if (iterFlag)
				break;
		}
	}

}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	
	string tmp;

	cin >> R >> C;

	// .�� �� ĭ, x�� �ǹ���. ó���� ������ ���� �׻� �������.
	for (int i = 0; i < R; i++) {
		cin >> tmp;
		for (int j = 0; j < C; j++) {
			arr[i][j] = tmp[j];
		}
	}

	int cnt = 0;

	// ��� ���� ���� ���ؼ� ����
	for (int row = 0; row < R; row++) {
		simulation(row, 0);
		if (iterFlag) 
			cnt += 1;
		iterFlag = false;
	}

	cout << cnt;

	return 0;
}