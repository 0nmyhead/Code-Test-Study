#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <deque>

using namespace std;

#define WHITE 0
#define RED 1
#define BLUE 2

int N, K;
int board[14][14];

int dy[5] = { 0, 0, 0,-1,1 };
int dx[5] = { 0, 1,-1,0,0 };

typedef struct chess {
	int row;
	int col;
	int dir;
}Chess;

// �ٸ� ������ ���� ���� ����� deque 2���� �迭
deque<int> arr[14][14];

// ü���� ��ġ �� ���� ������ �����ϴ� 1���� ���� �迭
Chess chess[12];

// ü�� ���� �ٲ��ִ� �Լ�
int change(int dir) {
	if (dir == 1) return 2;
	if (dir == 2) return 1;
	if (dir == 3) return 4;
	if (dir == 4) return 3;
}

bool simulation() {

	// ��� ������ ���ʴ�� ���캸��
	for (int i = 1; i <= K; i++) {
		int c_row = chess[i].row;
		int c_col = chess[i].col;
		int c_dir = chess[i].dir;

		// cur_dir ������ ������ ����
		int next_row = c_row + dy[c_dir];
		int next_col = c_col + dx[c_dir];

		// ��� ĭ�̾��� ���
		if (board[next_row][next_col] == WHITE) {
			// ���� i��° �� ���� �� ���� ������� �� ĭ���� �̵�
			// i��° ���� ���� ĭ�� ������ Ȯ��
			deque<int> tmp; // �̵��� �� ���� ���
			
			// ���� �� �տ������� i�� ���� ������ Ȯ��
			int idx = 0;
			for (idx = 0; idx < arr[c_row][c_col].size(); idx++) {
				if (arr[c_row][c_col][idx] == i)
					break;
			}
			// idx���� ������ ��´�.
			int size = arr[c_row][c_col].size() - idx;
			for (int j = 0; j < size; j++) {
				tmp.push_front(arr[c_row][c_col].back());
				arr[c_row][c_col].pop_back();
			}

			// tmp�� ��� ������ ���� �̵��� ĭ�� back���� �ִ´�.
			for (int m = 0; m < tmp.size(); m++) {
				arr[next_row][next_col].push_back(tmp[m]);
				chess[tmp[m]].row = next_row;
				chess[tmp[m]].col = next_col;
			}
			if (arr[next_row][next_col].size() >= 4) {
				// ���� ����
				return true;
			}
		}
		else if (board[next_row][next_col] == RED) {
			// �̵��� �ϴµ� ������ �ݴ�� �ٲپ �״´�.
			deque<int> tmp; // �̵��� �� ���� ���

			// ���� �� �տ������� i�� ���� ������ Ȯ��
			int idx = 0;
			for (idx = 0; idx < arr[c_row][c_col].size(); idx++) {
				if (arr[c_row][c_col][idx] == i)
					break;
			}
			// idx���� ������ ��´�.
			int size = arr[c_row][c_col].size() - idx;
			for (int j = 0; j < size; j++) {
				tmp.push_back(arr[c_row][c_col].back());
				arr[c_row][c_col].pop_back();
			}

			// tmp�� ��� ������ ���� �̵��� ĭ�� back���� �ִ´�.
			for (int m = 0; m < tmp.size(); m++) {
				arr[next_row][next_col].push_back(tmp[m]);
				chess[tmp[m]].row = next_row;
				chess[tmp[m]].col = next_col;
			}

			if (arr[next_row][next_col].size() >= 4) {
				// ���� ����
				return true;
			}
		}
		else if (board[next_row][next_col] == BLUE) {
			// ���� ���� ������ �ٲ۴�.
			chess[i].dir = change(chess[i].dir);
			int n_row = c_row + dy[chess[i].dir];
			int n_col = c_col + dx[chess[i].dir];

			// BLUE�� �ƴ� ��� �ٲ� �������� �� ĭ �̵��Ѵ�. �� ���� �̵��� ���� ���� �÷���
			// ���� �ݵ�� �Բ� �̵��ϴ� ������ ��������.
			if (board[n_row][n_col] == WHITE) {
				deque<int> tmp; // �̵��� �� ���� ���

				// ���� �� �տ������� i�� ���� ������ Ȯ��
				int idx = 0;
				for (idx = 0; idx < arr[c_row][c_col].size(); idx++) {
					if (arr[c_row][c_col][idx] == i)
						break;
				}
				// idx���� ������ ��´�.
				int size = arr[c_row][c_col].size() - idx;
				for (int j = 0; j < size; j++) {
					tmp.push_front(arr[c_row][c_col].back());
					arr[c_row][c_col].pop_back();
				}
				// tmp�� ��� ������ ���� �̵��� ĭ�� back���� �ִ´�.
				for (int m = 0; m < tmp.size(); m++) {
					arr[n_row][n_col].push_back(tmp[m]);
					chess[tmp[m]].row = n_row;
					chess[tmp[m]].col = n_col;
				}

				if (arr[n_row][n_col].size() >= 4) {
					// ���� ����
					return true;
				}
			}
			else if (board[n_row][n_col] == RED) {
				// �̵��� �ϴµ� ������ �ݴ�� �ٲپ �״´�.
				deque<int> tmp; // �̵��� �� ���� ���

				// ���� �� �տ������� i�� ���� ������ Ȯ��
				int idx = 0;
				for (idx = 0; idx < arr[c_row][c_col].size(); idx++) {
					if (arr[c_row][c_col][idx] == i)
						break;
				}
				// idx���� ������ ��´�.
				int size = arr[c_row][c_col].size() - idx;
				for (int j = 0; j < size; j++) {
					tmp.push_back(arr[c_row][c_col].back());
					arr[c_row][c_col].pop_back();
				}

				// tmp�� ��� ������ ���� �̵��� ĭ�� back���� �ִ´�.
				for (int m = 0; m < tmp.size(); m++) {
					arr[n_row][n_col].push_back(tmp[m]);
					chess[tmp[m]].row = n_row;
					chess[tmp[m]].col = n_col;
				}

				if (arr[n_row][n_col].size() >= 4) {
					// ���� ����
					return true;
				}
			}
		} // end if
	}//end for

	return false;
}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> K;

	// �� �ٱ��� BLUE�� ä�����´�.
	for (int i = 0; i <= N+1; i++) {
		board[0][i] = BLUE;
		board[N + 1][i] = BLUE;
		board[i][0] = BLUE;
		board[i][N + 1] = BLUE;
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
		}
	}
	for (int i = 0; i < K; i++) {
		int row, col, dir;
		cin >> row >> col >> dir;
		arr[row][col].push_back(i + 1);
		chess[i + 1].row = row;
		chess[i + 1].col = col;
		chess[i + 1].dir = dir;
	}

	bool flag = false;
	int i = 1;
	for (i = 1; i <= 1000; i++) {
		flag = simulation();
		if (flag) break;
	}

	if (flag == true)
		cout << i;
	else if (flag == false || i > 1000)
		cout << -1;

	return 0;
}