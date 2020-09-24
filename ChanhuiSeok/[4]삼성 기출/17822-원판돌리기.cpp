#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <deque>

using namespace std;

#define blank 0

int N, M, T;
deque<int> circle[51];
deque<int> cp_circle[51];
vector<int> cmd[51];

void rotate(int x_i, int d_i, int k_i) {
	int tmp;

	for (int i = 1; i <= N; i++) {
		if (i % x_i == 0) {

			if (d_i == 0) {
				for (int k = 0; k < k_i; k++) {
					/* 1ȸ �ð���� ȸ�� */
					tmp = circle[i].back();
					circle[i].pop_back();
					circle[i].push_front(tmp);
				}
			}
			else if (d_i == 1) {
				for (int k = 0; k < k_i; k++) {
					/* 1ȸ �ݽð���� ȸ�� */
					tmp = circle[i].front();
					circle[i].pop_front();
					circle[i].push_back(tmp);
				}
			}

		}
	}
}

void eraser() {

	for (int i = 1; i <= 50; i++)
		cp_circle[i] = circle[i];

	bool flag = false;

	// ���� ������ ���鼭...
	for (int i = 1; i <= N; i++) {

		if (circle[i][0] != blank && circle[i][0] == circle[i][1]) {
			cp_circle[i][0] = blank;
			cp_circle[i][1] = blank;
			flag = true;
		}
		if (circle[i][0] != blank && circle[i][0] == circle[i][M - 1]) {
			cp_circle[i][0] = blank;
			cp_circle[i][M - 1] = blank;
			flag = true;
		}
		if (circle[i][M - 1] != blank && circle[i][M - 1] == circle[i][M - 2]) {
			cp_circle[i][M - 1] = blank;
			cp_circle[i][M - 2] = blank;
			flag = true;
		}
		if (circle[i][M - 1] != blank && circle[i][M - 1] == circle[i][0]) {
			cp_circle[i][M - 1] = blank;
			cp_circle[i][0] = blank;
			flag = true;
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M - 2; j++) {
			if (circle[i][j] != blank && circle[i][j] == circle[i][j - 1]) {
				cp_circle[i][j] = blank;
				cp_circle[i][j - 1] = blank;
				flag = true;
			}
			if (circle[i][j] != blank && circle[i][j] == circle[i][j + 1]) {
				cp_circle[i][j] = blank;
				cp_circle[i][j + 1] = blank;
				flag = true;
			}
		}
	}

	for (int j = 0; j < M; j++) {
		if (circle[1][j] != blank && circle[1][j] == circle[2][j]) {
			cp_circle[1][j] = blank;
			cp_circle[2][j] = blank;
			flag = true;
		}
	}

	for (int j = 0; j < M; j++) {
		if (circle[N][j] != blank && circle[N][j] == circle[N - 1][j]) {
			cp_circle[N][j] = blank;
			cp_circle[N - 1][j] = blank;
			flag = true;
		}
	}

	for (int i = 2; i <= N-1; i++){
		for (int j = 0; j < M; j++) {
			if (circle[i][j] != blank && circle[i][j] == circle[i - 1][j]) {
				cp_circle[i][j] = blank;
				cp_circle[i - 1][j] = blank;
				flag = true;
			}
			if (circle[i][j] != blank && circle[i][j] == circle[i + 1][j]) {
				cp_circle[i][j] = blank;
				cp_circle[i + 1][j] = blank;
				flag = true;
			}
		}
	}

	// ����� �Ϸ�, cp_circle�� ����
	for (int i = 1; i <= 50; i++)
		circle[i] = cp_circle[i];

	int sum = 0;
	// �� �̸� ���ϱ�
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			sum += circle[i][j];
		}
	}

	if (!flag) {
		// ���ǿ� ���� ���� ����� ���ϰ�, ��պ��� ū ���� 1�� ����, ���� ���� 1�� ���Ѵ�.
		// ��, ��� ���� 0�̾��� ������ ����� ������ �ʵ��� �Ѵ�.
		double ave = 0;
		int cnt = 0;
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < M; j++) {
				if (circle[i][j] > blank) {
					cnt += 1;
				}
			}
		}
		// ���� sum ���ϱ� �Ϸ�
		ave = (double)sum / cnt;

		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < M; j++) {
				if (circle[i][j] > blank && circle[i][j] < ave) {
					circle[i][j] += 1;
				}
				else if (circle[i][j] > blank && circle[i][j] > ave) {
					circle[i][j] -= 1;
				}
			}
		}
	}
}


int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M >> T;

	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			int input;
			cin >> input;
			circle[i].push_back(input);
		}
	}

	for (int i = 0; i < T; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		cmd[i] = { a,b,c };
	}

	// ���� ��ɴ�� ȸ������ ����.
	for (int i = 0; i < T; i++) {
		rotate(cmd[i][0], cmd[i][1], cmd[i][2]);
		eraser();
	}

	// ������ ��� ���� �� ���
	int res = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			if (circle[i][j] != blank)
				res += circle[i][j];
		}
	}

	cout << res;

	return 0;
}