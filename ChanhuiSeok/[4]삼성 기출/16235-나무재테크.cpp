#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <stack>
#include <string>
#include <deque>

using namespace std;

int N, M, K;

int dy[8] = { -1,-1,-1,0,0,1,1,1 };
int dx[8] = { -1,0,1,-1,1,-1,0,1 };

typedef struct tree {
	int age;
	bool isDead;
}Tree;

int board[12][12];
int A[12][12]; // �߰��Ǵ� ��а�

deque<int> info[12][12];
queue<int> dead[12][12];

bool valid(int y, int x) {

	if (y < 1 || y > N || x < 1 || x > N)
		return false;
	return true;
}

void simulation(int K) {

	while (K > 0) {
		// ��
		// ������ �ڽ��� ���̸�ŭ ����� �԰�, ���� 1 ����, �� ĭ�� �ִ� ��и� �Ա� ����
		// �ϳ��� ĭ�� ���� �� ������ ������, ���̰� � �������� ��� ȹ��
		// ���� ����� �����ؼ� �ڽ��� ���̸�ŭ ��� �� ������ �� ������ ��� ����

		// ���� �ִ� ��� �����鿡 ���Ͽ�
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {

				int size = info[i][j].size();
				// �� ĭ�� ť�� Ȯ���Ѵ�.
				for (int k = 0; k < size; k++) {

					// ���̰� � ��������
					int age = info[i][j].front();
					info[i][j].pop_front();

					// �ڽ��� ���̸�ŭ ��� �Ա�
					if (board[i][j] >= age) {
						board[i][j] -= age;

						// ���� 1 ������Ű��
						info[i][j].push_back(age + 1);
					}
					// �ڽ��� ���̸�ŭ ����� �� ���� ��� ���δ�.
					else {
						// dead ť�� �ִ´�.
						dead[i][j].push(age);
					}
				}
			}
		}


		// ����
		// ���� ���� ������ ������� ���Ѵ�.
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				// �� ĭ�� ���� ť�� Ȯ���Ѵ�.			
				while (!dead[i][j].empty()) {
					int age = dead[i][j].front();
					dead[i][j].pop();
					board[i][j] += age / 2;
				}
			}
		}


		// ����
		// ������ �����Ѵ�. �����ϴ� ������ ���̰� 5������� �ϰ� ���� 8�� ĭ�� ���̰� 1�� ������ �����
		// �� ��� ĭ���� ������ ������ �ʴ´�.
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {

				int size = info[i][j].size();
				for (int k = 0; k < size; k++) {
					// 8���� ����
					int age = info[i][j][k];

					if (age % 5 == 0) {
						for (int m = 0; m < 8; m++) {
							int ty = i + dy[m];
							int tx = j + dx[m];

							if (valid(ty, tx)) {
								info[ty][tx].push_front(1); // ���� 1�� ������ �տ� �߰�
							}
						}
					}
				}
			}
		}


		// �ܿ�
		// �� �� ĭ�� ���ƴٴϸ鼭 A[r][c]��ŭ ����� �߰���Ų��.
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				board[i][j] = board[i][j] + A[i][j];
			}
		}

		K -= 1;
	}

}


int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M >> K;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			board[i][j] = 5;
		}
	}


	for (int i = 0; i < M; i++) {
		int x, y, z;
		cin >> x >> y >> z;

		info[x][y].push_back(z);
	}

	// �������� �Է¹ޱ� �Ϸ�

	simulation(K);


	// ���� ���� �������� ���� ����
	int cnt = 0;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cnt += info[i][j].size();
		}
	}

	cout << cnt;
	return 0;
}