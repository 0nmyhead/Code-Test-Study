#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;

#define REAL_BLANK 3
#define CHEESE 1
#define BLANK 0
#define MELT 5

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
int N, M;
int time;

int arr[101][101];
int visit[101][101];

// ġ�� ���� �� ĭ�� ������ ��� �� ĭ�� REAL_BLANK�� ä��� �Լ�
void fill_blank() {
	// visit �ʱ�ȭ
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			visit[i][j] = 0;
		}
	}

	queue<pair<int, int>>q;
	q.push({ 0,0 });
	visit[0][0] = 1;

	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int ty = y + dy[i];
			int tx = x + dx[i];

			if (ty >= 0 && tx >= 0 && ty < N && tx < M &&
				visit[ty][tx] == 0 && arr[ty][tx] != CHEESE) {
				visit[ty][tx] = 1;
				arr[ty][tx] = REAL_BLANK;
				q.push({ ty,tx });
			}
		}
	}
}

void simulation() {

	bool flag = false;
	// ��� ĭ�� �� ���캻��.
	while (1) {

		fill_blank(); // ġ�� ���� �� ĭ�� ������ ��� �� ĭ���� REAL_BLANK�� ä���.

		flag = false;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				// �ش� ĭ�� ġ���� ���
				if (arr[i][j] == CHEESE) {
					int cnt = 0;
					// �� ĭ�� ��,��,��,�츦 ���캸�� �ּ� 2ĭ�� REAL_BLANK���� Ȯ��
					for (int k = 0; k < 4; k++) {
						int ty = i + dy[k];
						int tx = j + dx[k];
						if (ty >= 0 && tx >= 0 && ty < N && tx < M &&
							arr[ty][tx] == REAL_BLANK) {
							flag = true;
							cnt++;
						}
					}
					if (cnt >= 2) arr[i][j] = MELT; // ��� ������� ǥ��
				}
			}
		}

		// ��� ������� ǥ��� ġ� ���� ��� �� ĭ���� �����.
		if (flag) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					if (arr[i][j] == MELT) {
						arr[i][j] = REAL_BLANK;
					}
				}
			}
		}
		time++; // �ð� ����

		flag = false;
		// ���� ġ� �ִ��� ��˻�
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (arr[i][j] == CHEESE) {
					flag = true;
				}
			}
		}
		if (!flag) break;
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {			
			cin >> arr[i][j];
		}
	}

	simulation();

	cout << time;

	return 0;
}
