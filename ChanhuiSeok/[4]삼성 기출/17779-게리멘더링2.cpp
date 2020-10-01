#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

#define pii pair<int, int> 

/* 18405�� */
using namespace std;

int N;
int arr[21][21]; // �α� ���� �ִ� ��
int board[21][21]; // 5������ ������ ��
int visit[21][21]; // �湮�迭

int res_min = 987654321;

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

// ��� ���� ���� ���� ����
bool isBoundary(int x, int y, int d1, int d2) {
	if (x + d1 + d2 <= N && y - d1 >= 1 && y + d2 <= N) {
		return true;
	}
	return false;
}

void simulation() {

	for (int i = 1; i <= N - 2; i++) {
		for (int j = 2; j <= N - 1; j++) {

			for (int d1 = 1; d1 <= N - 1; d1++) {
				for (int d2 = 1; d2 <= N - 1; d2++) {

					// ������ ��� �������� �Ǵ� �� ������ �Ǵ� �� 5�� ��輱 �����
					if (isBoundary(i, j, d1, d2)) {
						// ������ �������� ���
						for (int k = 0; k <= d2; k++) {
							board[i + d1 + k][j - d1 + k] = 5;
							board[i + k][j + k] = 5;
						}
						for (int k = 0; k <= d1; k++) {
							board[i + k][j - k] = 5;
							board[i + d2 + k][j + d2 - k] = 5;
						}

						// 5�� �׵θ��� �������� 1,2,3,4 �� BFS �� ����.
						queue<pair<int, int>> q;

						q.push({ 1,1 }); board[1][1] = 1; visit[1][1] = 1;
						q.push({ 1,N }); board[1][N] = 2; visit[1][N] = 1;
						q.push({ N,1 }); board[N][1] = 3; visit[N][1] = 1;
						q.push({ N,N }); board[N][N] = 4; visit[N][N] = 1;

						while (!q.empty()) {
							int r = q.front().first;
							int c = q.front().second;
							q.pop();

							for (int k = 0; k < 4;k++) {
								int tr = r + dy[k];
								int tc = c + dx[k];

								if (tr <= 0 || tc <= 0 || tr > N || tc > N ||
									visit[tr][tc] == 1 || board[tr][tc] == 5) 
									continue;
								
								if (1 <= tr && tr < i + d1 && 1 <= tc && tc <= j) {
										board[tr][tc] = 1;
										visit[tr][tc] = 1;
										q.push({ tr,tc });
								}

								else if (1 <= tr && tr <= i + d2 && j < tc && tc <= N) {
										board[tr][tc] = 2;
										visit[tr][tc] = 1;
										q.push({ tr,tc });
								}

								else if (i + d1 <= tr && tr <= N && 1 <= tc && tc < j - d1 + d2) {
										board[tr][tc] = 3;
										visit[tr][tc] = 1;
										q.push({ tr,tc });
								}

								else if (i + d2 < tr && tr <= N && j - d1 + d2 <= tc && tc <= N) {
										board[tr][tc] = 4;
										visit[tr][tc] = 1;
										q.push({ tr,tc });
								}
							}
						}
						// ������ 5���� ä���.
						for (int i = 1; i <= N; i++) {
							for (int j = 1; j <= N; j++) {
								if (board[i][j] == 0) {
									board[i][j] = 5;
								}
								visit[i][j] = 0;
							}
						}

						// �� ������ �迭�� �α����� ���Ѵ�.
						int sumArr[5] = { 0,0,0,0,0 };
						for (int i = 1; i <= N; i++) {
							for (int j = 1; j <= N; j++) {
								sumArr[board[i][j] - 1] += arr[i][j];
							}
						}
						sort(sumArr, sumArr + 5);
						res_min = min(res_min, sumArr[4]-sumArr[0]);

					// �ٸ� ���̽��� ���� �ʱ�ȭ�Ѵ�.
						for (int i = 1; i <= N; i++) {
							for (int j = 1; j <= N; j++) {
								board[i][j] = 0;
								visit[i][j] = 0;
							}
						}
					}
					// 5�� ���� �� ���� ��� �ٸ� ��輱 ���̷� �Ѿ��
					else {
						continue;
					}
				}
			} // end inner for
		}
	} // end outer for
}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}

	simulation();
	cout << res_min;
	return 0;
}