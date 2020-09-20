#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <stack>
#include <string>
#include <cstring>

#define FULL 8

using namespace std;

int N, M;
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

int minV = 987654321;

bool valid(int y, int x, int board[][10]) {
	if (y <= 0 || x <= 0 || y > N || x > M || board[y][x] == 6) {
		return false;
	}
	return true;
}

void retarr(int target_boar[][10], int origin_board[][10]) {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			target_boar[i][j] = origin_board[i][j];
		}
	}
}

void UP(int board[][10], int i, int j) {
	int ty = i - 1;
	int tx = j;
	while (valid(ty, tx, board) && ty > 0) {
		// 0�̳� 6�� �ƴ� �ٸ� ���ڿ��� ��� - �ٸ� CCTV
		if (board[ty][tx] != 0 && board[ty][tx] != 6) {
			ty -= 1;
			continue;
		}
		// �� ĭ�̾��� ���
		else if (board[ty][tx] == 0) {
			board[ty][tx] = FULL;
			ty -= 1;
		}
	}
}

void DOWN(int board[][10], int i, int j) {
	int ty = i + 1, tx = j;
	while (valid(ty, tx, board) && ty <= N) {
		// 0�̳� 6�� �ƴ� �ٸ� ���ڿ��� ��� - �ٸ� CCTV
		if (board[ty][tx] != 0 && board[ty][tx] != 6) {
			ty += 1;
			continue;
		}
		// �� ĭ�̾��� ���
		else if (board[ty][tx] == 0) {
			board[ty][tx] = FULL;
			ty += 1;
		}
	}
}

void LEFT(int board[][10], int i, int j) {
	int ty = i, tx = j - 1;
	while (valid(ty, tx, board) && tx > 0) {
		// 0�̳� 6�� �ƴ� �ٸ� ���ڿ��� ��� - �ٸ� CCTV
		if (board[ty][tx] != 0 && board[ty][tx] != 6) {
			tx -= 1;
			continue;
		}
		// �� ĭ�̾��� ���
		else if (board[ty][tx] == 0) {
			board[ty][tx] = FULL;
			tx -= 1;
		}
	}
}

void RIGHT(int board[][10], int i, int j) {
	int ty = i, tx = j + 1;
	while (valid(ty, tx, board) && tx <= M) {
		// 0�̳� 6�� �ƴ� �ٸ� ���ڿ��� ��� - �ٸ� CCTV
		if (board[ty][tx] != 0 && board[ty][tx] != 6) {
			tx += 1;
			continue;
		}
		// �� ĭ�̾��� ���
		else if (board[ty][tx] == 0) {
			board[ty][tx] = FULL;
			tx += 1;
		}
	}
}

void dfs(int origin_board[][10], int origin_visit[][10]) {

	int cp_board[10][10];
	int board[10][10];
	int visit[10][10];

	// ������ �迭 ī��
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cp_board[i][j] = origin_board[i][j];
			board[i][j] = origin_board[i][j];
			visit[i][j] = origin_visit[i][j];
		}
	}

	// ������ ���鼭 0�� 6�� �ƴ� ������ ���ڿ� ���� ���� ���ĺ���.
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {

			// �湮 �� �� CCTV�� ���
			if (board[i][j] != 0 && board[i][j] != 6
				&& board[i][j] != FULL && visit[i][j] != 1) {

				visit[i][j] = 1;

				if (board[i][j] == 1) {
					// ���� ���⸸, �� 90�� ȸ�� 4�� ����
					// ���θ� �� ��
					UP(board, i, j);
					dfs(board, visit);
					// ����
					retarr(board, cp_board);

					// �Ʒ��θ� �� ��
					DOWN(board, i, j);
					dfs(board, visit);
					retarr(board, cp_board);

					// �������θ� �� ��
					LEFT(board, i, j);
					dfs(board, visit);
					retarr(board, cp_board);

					// ���������θ� �� ��
					RIGHT(board, i, j);
					dfs(board, visit);
					retarr(board, cp_board);

				}
				else if (board[i][j] == 2) {
					// ����� ����, ��-�� Ȥ�� ��-��
					// ���� �������� ��, �״��� ���������� ��
					LEFT(board, i, j); RIGHT(board, i, j);
					dfs(board, visit);
					retarr(board, cp_board);

					// �ٽ� ���� ��, �Ʒ��� ��
					UP(board, i, j); DOWN(board, i, j);
					dfs(board, visit);
					retarr(board, cp_board);

				}
				else if (board[i][j] == 3) {

					// ��-������ Ȥ�� ������-�Ʒ� Ȥ�� �Ʒ�-���� Ȥ�� ����-�� ����
					UP(board, i, j); RIGHT(board, i, j);
					dfs(board, visit);
					retarr(board, cp_board);

					RIGHT(board, i, j); DOWN(board, i, j);
					dfs(board, visit);
					retarr(board, cp_board);

					DOWN(board, i, j); LEFT(board, i, j);
					dfs(board, visit);
					retarr(board, cp_board);

					LEFT(board, i, j); UP(board, i, j);
					dfs(board, visit);
					retarr(board, cp_board);

				}
				else if (board[i][j] == 4) {

					// ��-��-�� , ��-��-�Ʒ�, ��,�Ʒ�,��, ��-��,�� ����
					UP(board, i, j); LEFT(board, i, j); RIGHT(board, i, j);
					dfs(board, visit);
					retarr(board, cp_board);

					UP(board, i, j); RIGHT(board, i, j); DOWN(board, i, j);
					dfs(board, visit);
					retarr(board, cp_board);

					LEFT(board, i, j); DOWN(board, i, j); RIGHT(board, i, j);
					dfs(board, visit);
					retarr(board, cp_board);

					UP(board, i, j); LEFT(board, i, j); DOWN(board, i, j);
					dfs(board, visit);
					retarr(board, cp_board);
				}
				else if (board[i][j] == 5) {
					// �� �� �� �� �ѹ��� ����
					UP(board, i, j); RIGHT(board, i, j);
					DOWN(board, i, j); LEFT(board, i, j);
					dfs(board, visit);
					retarr(board, cp_board);
				}
			}
		}
	}

	// �� ĭ�� �� ����
	int cnt = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (board[i][j] == 0) {
				cnt += 1;
			}
		}
	}
	minV = min(minV, cnt);
	return;

}


int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	int board[10][10];
	int visit[10][10];

	cin >> N >> M;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> board[i][j];
			visit[i][j] = 0;
		}
	}

	dfs(board, visit);

	cout << minV;

	return 0;
}