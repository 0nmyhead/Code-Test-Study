#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>

using namespace std;

int N, M, H;
int minV = 987654321;
int board[34][34];

int ret = 987654321;

// i->i �� �������� üũ�ϴ� �Լ�
bool check() {
	// N���� ��
	for (int i = 1; i <= N; i++) {
		int startIdx = i; // startIdx��° �Ա����� ��ٸ�Ÿ�� ����
		
		// H ���̸�ŭ ������ ����.
		for (int j = 1; j <= H; j++) {
			if (board[j][startIdx] == 1) {
				// �� ��ٸ��� Ÿ�� ���������� ������.
				startIdx += 1;
			}
			// ���ʿ� ���μ��� ���� ���
			else if (board[j][startIdx - 1] == 1) {
				startIdx -= 1;
			}
		}

		// ��ٸ�Ÿ�⸦ ��� �Ϸ��ߴµ� �ٸ� �ⱸ�� ���
		// �� ���̶� �ٸ��� ���� �ƴϹǷ� �ٷ� false ��ȯ�ϰ� ����
		if (startIdx != i) {
			return false;
		}
	}
	return true;
}

// dfs �Լ�
void dfs(int line, int cnt) {

	if (cnt > 3) return;
	// i->i�� ��� ������ ���
	if (check() == true) {
		ret = min(ret, cnt);
		if (ret == 1) {
			printf("%d", ret);
			exit(0);
		}
		return;
	}

	for (int i = line; i <= H; i++) {
		for (int j = 1; j <= N; j++) {
			// �̹� ��ġ�Ǿ� ���� ��� �ٸ� ĭ �˾ƺ���
			if (board[i][j - 1] == 1 || board[i][j + 1] == 1 || board[i][j] == 1) {
				continue;
			}
			// �ƴ� ��� �� ĭ�� ��ġ �� ��ġ ���� ������Ű�� ����Լ� ����
			board[i][j] = 1;
			dfs(i, cnt + 1);
			board[i][j] = 0; // ���� - ��ġ ���
		}
	}

}

int main() {

	int a, b;
	scanf("%d %d %d", &N, &M, &H);

	// board[a][b] : b�� b+1 �� ���̿� a��° ���μ��� ��ġ�� ��
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		board[a][b] = 1;
	}

	if (check() == true) {
		cout << 0;
		return 0;
	}

	dfs(1, 0);
	if (ret != 987654321)
		printf("%d", ret);
	else
		printf("-1");

	return 0;
}