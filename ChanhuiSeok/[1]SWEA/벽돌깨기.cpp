#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>

using namespace std;

#define EXPLODE 100

int N, W, H;
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
int minV = 987654321;

// 0�� �ƴ� ĭ�� ���� �Լ�
int countAll(int board[][20]) {
	int res = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (board[i][j] != 0)
				res++;
		}
	}
	return res;
}

// ��� ĭ�� �Ʒ��� ������ �Լ�
void forced(int board[][20]) {
	for (int j = 0; j < W; j++) { // ��
		for (int i = H - 2; i >= 0; i--) {
			int k = i;
			while (k <= H - 2 && board[k][j] != 0) {
				if (board[k + 1][j] == 0) {
					board[k + 1][j] = board[k][j];
					board[k][j] = 0;
				}
				k++;
			}
		}
	}
}

// EXPLODE�� 0���� �ٲٴ� �Լ�
void blanked(int board[][20]) {
	for (int j = 0; j < W; j++) {
		for (int i = 0; i < H; i++) {
			if (board[i][j] == EXPLODE){
				board[i][j] = 0;
			}
		}
	}
}


// ���߽�Ű�� dfs
void burn(int board[][20], int burn_board[][20], int num, int y, int x) {

	if (burn_board[y][x] != EXPLODE) {
		burn_board[y][x] = EXPLODE;
	}
	if (num == 1) {		
		return;
	}

	//��
	for (int m = y - 1; m >= y - num + 1 && m >= 0; m--) {
		if(burn_board[m][x] != EXPLODE && burn_board[m][x] != 0)
			burn(board, burn_board, board[m][x], m, x);
	}

	//��
	for (int m = y + 1; m <= y + num -1 && m < H; m++) {
		if(burn_board[m][x] != EXPLODE && burn_board[m][x] != 0)
			burn(board, burn_board, board[m][x], m, x);
	}

	//��
	for (int m = x - 1; m >= x - num + 1 && m >= 0; m--) {
		if(burn_board[y][m] != EXPLODE && burn_board[y][m] != 0)
			burn(board, burn_board, board[y][m], y, m);
	}

	//��
	for (int m = x + 1; m <= x + num - 1 && m < W; m++) {
		if(burn_board[y][m] != EXPLODE && burn_board[y][m] != 0)
			burn(board, burn_board, board[y][m], y, m);
	}

}


// ���� dfs
void simulate(int cnt, int origin_board[][20]) {
	int burn_board[20][20];
	int board[20][20];
	int cp_board[20][20];

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			board[i][j] = origin_board[i][j];
			burn_board[i][j] = origin_board[i][j];
		}
	}

	if (cnt == N) {
		//printf("\nN�� ���� �Ϸ�\n");
		int res = countAll(origin_board);
		minV = min(minV, res);
		return;
	}

	// col��°���� ���� ����Ʈ����
	for (int col = 0; col <= W - 1; col++) {
		//printf("%d�� �� ���� ", col);

		for (int row = 0; row <= H - 1; row++) {
			// ó������ 0�� �ƴ� ���� ���� ���
			if (board[row][col] != 0) {
				burn(board, burn_board, board[row][col], row, col);
				break;
			}
		}
		// ó�� �� �迭 ����
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cp_board[i][j] = board[i][j];
			}
		}

		// �̹� �� ��� ó��
		blanked(burn_board);
		forced(burn_board);

		// board�� ����
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				board[i][j] = burn_board[i][j];
			}
		}

		
		// ó�� �� ���
		/*
		printf("ó�� �� \n");
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				printf("%d ", board[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		*/

		simulate(cnt + 1, board);

		// ó�� ������ �ǵ�����
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				board[i][j] = cp_board[i][j];
				burn_board[i][j] = cp_board[i][j];
			}
		}

	}

}

int main() {

	int T;
	int board[20][20];
	scanf("%d", &T);

	for (int t = 0; t < T; t++) {

		scanf("%d %d %d", &N, &W, &H);
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				scanf("%d", &board[i][j]);
			}
		}
		// ������ ���� 1 ~ 9�� ǥ���ȴ�.
		// ������ ��, ��θ� ������ �� �ְ� �׻� �� ���� �ִ� ������ ��Ʈ�� �� �ִ�.
		// ������ N���� �� �� �ִ�.
		simulate(0, board);

		printf("#%d %d\n", t+1, minV);
		minV = 987654321;
	}


	return 0;
}