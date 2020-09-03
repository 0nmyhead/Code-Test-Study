#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

/* 2048(Easy) ���� */

int N;
int maxValue;
vector<string> seq;

int arr[25][25];

// �����ǿ��� ���� ū ����� ã�� �Լ�
int maxBlock() {
	int temp = -1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (temp < arr[i][j])
				temp = arr[i][j];
		}
	}
	return temp;
}

// �׽�Ʈ�� ��� �Լ�
void printArr() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << arr[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}

void simul(int cnt) {

	if (cnt == 5) {
		maxValue = max(maxValue, maxBlock());
		return;
	}

	// ���� �� ������ �α�
	int cpArr[25][25];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cpArr[i][j] = arr[i][j];
		}
	}

	//4���� ����
	for (int dir = 0; dir < 4; dir++) {

		// ��
		if (dir == 0) {
			// ���� ���� �� �Űܳ���
			for (int col = 0; col < N; col++) {
				for (int row = 1; row < N; row++) {
					int tRow = row;
					while (tRow - 1 >= 0 && arr[tRow - 1][col] == 0) {
						arr[tRow - 1][col] = arr[tRow][col];
						arr[tRow][col] = 0;
						tRow -= 1;
					}
				}
			}

			// ��ĥ �� �ִ� �� �������� ��ġ�� �ٸ� ���� 0���� �ٲٱ�
			for (int col = 0; col < N; col++) {
				for (int row = 0; row < N; row++) {
					if (arr[row][col] == arr[row + 1][col]) {
						arr[row][col] *= 2;
						arr[row + 1][col] = 0;
					}
				}
			}

			// �ٽ� ���� �� �ű��
			for (int col = 0; col < N; col++) {
				for (int row = 1; row < N; row++) {
					int tRow = row;
					while (tRow - 1 >= 0 && arr[tRow - 1][col] == 0) {
						arr[tRow - 1][col] = arr[tRow][col];
						arr[tRow][col] = 0;
						tRow -= 1;
					}
				}
			}

			maxValue = max(maxValue, maxBlock());
			// simul ��� ����
			simul(cnt + 1);

			// ������ �� �ٲٱ�
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					arr[i][j] = cpArr[i][j];
				}
			}
		}

		// �Ʒ�
		else if (dir == 1) {
			// ���� �Ʒ��� �� �Űܳ���
			for (int col = 0; col < N; col++) {
				for (int row = N - 2; row >= 0; row--) {
					int tRow = row;
					while (tRow + 1 < N && arr[tRow + 1][col] == 0) {
						arr[tRow + 1][col] = arr[tRow][col];
						arr[tRow][col] = 0;
						tRow += 1;
					}
				}
			}

			// ��ĥ �� �ִ� �� �Ʒ������� ��ġ�� �ٸ� ���� 0���� �ٲٱ�
			for (int col = 0; col < N; col++) {
				for (int row = N - 1; row > 0; row--) {
					if (arr[row][col] == arr[row - 1][col]) {
						arr[row][col] *= 2;
						arr[row - 1][col] = 0;
					}
				}
			}

			// �ٽ� �Ʒ��� �� �ű��
			for (int col = 0; col < N; col++) {
				for (int row = N - 2; row >= 0; row--) {
					int tRow = row;
					while (tRow + 1 < N && arr[tRow + 1][col] == 0) {
						arr[tRow + 1][col] = arr[tRow][col];
						arr[tRow][col] = 0;
						tRow += 1;
					}
				}
			}

			maxValue = max(maxValue, maxBlock());
			simul(cnt + 1);

			// ������ �� �ٲٱ�
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					arr[i][j] = cpArr[i][j];
				}
			}

		}
		// ����
		else if (dir == 2) {
			// ���� �������� �� �Űܳ���
			for (int row = 0; row < N; row++) {
				for (int col = 1; col < N; col++) {
					int tCol = col;
					while (tCol - 1 >= 0 && arr[row][tCol - 1] == 0) {
						arr[row][tCol - 1] = arr[row][tCol];
						arr[row][tCol] = 0;
						tCol -= 1;
					}
				}
			}

			// ��ĥ �� �ִ°� �������� ��ġ��
			for (int row = 0; row < N; row++) {
				for (int col = 0; col < N; col++) {
					if (arr[row][col] == arr[row][col + 1]) {
						arr[row][col] *= 2;
						arr[row][col + 1] = 0;
					}
				}
			}

			for (int row = 0; row < N; row++) {
				for (int col = 1; col < N; col++) {
					int tCol = col;
					while (tCol - 1 >= 0 && arr[row][tCol - 1] == 0) {
						arr[row][tCol - 1] = arr[row][tCol];
						arr[row][tCol] = 0;
						tCol -= 1;
					}
				}
			}

			maxValue = max(maxValue, maxBlock());
			simul(cnt + 1);

			// ������ �� �ٲٱ�
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					arr[i][j] = cpArr[i][j];
				}
			}
		}
		// ������
		else if (dir == 3) {

			// ���� ���������� �� �Űܳ���
			for (int row = 0; row < N; row++) {
				for (int col = N-2; col >= 0; col--) {
					int tCol = col;
					while (tCol + 1 < N && arr[row][tCol + 1] == 0) {
						arr[row][tCol + 1] = arr[row][tCol];
						arr[row][tCol] = 0;
						tCol += 1;
					}
				}
			}

			// ��ĥ �� �ִ°� ���������� ��ġ��
			for (int row = 0; row < N; row++) {
				for (int col = N-1; col > 0; col--) {
					if (arr[row][col] == arr[row][col - 1]) {
						arr[row][col] *= 2;
						arr[row][col - 1] = 0;
					}
				}
			}

			for (int row = 0; row < N; row++) {
				for (int col = N - 2; col >= 0; col--) {
					int tCol = col;
					while (tCol + 1 < N && arr[row][tCol + 1] == 0) {
						arr[row][tCol + 1] = arr[row][tCol];
						arr[row][tCol] = 0;
						tCol += 1;
					}
				}
			}
			
			maxValue = max(maxValue, maxBlock());
			simul(cnt + 1);

			// ������ �� �ٲٱ�
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					arr[i][j] = cpArr[i][j];
				}
			}
		}
	}
}


int main() {

	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}

	//�ִ� 5���� �̵�
	simul(0);

	cout << maxValue;

	return 0;
}