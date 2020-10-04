#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <unordered_set>

using namespace std;

int board[9][9];

// ���� �� �˻��ϴ� �Լ�
bool rowCheck(int rowNum) {
	int cnt[10];
	for (int i = 0; i < 10; i++) 
		cnt[i] = 0;
	
	for (int i = 0; i < 9; i++) {
		if (board[rowNum][i] != 0)
			cnt[board[rowNum][i]] += 1;
		if (cnt[board[rowNum][i]] >= 2) return false;
	}
	return true;
}

// ���� �� �˻��ϴ� �Լ�
bool colCheck(int colNum) {
	int cnt[10];
	for (int i = 0; i < 10; i++) 
		cnt[i] = 0;
	
	for (int i = 0; i < 9; i++) {
		if (board[i][colNum] != 0)
			cnt[board[i][colNum]] += 1;
		if (cnt[board[i][colNum]] >= 2) return false;
	}
	return true;
}

// Ư�� ĭ�� �� ��° �������簢���� ���ԵǴ��� ��ȯ
pair<int,int> squNum(int rowNum, int colNum) {
	if (rowNum >= 0 && rowNum <= 2) {
		if (0 <= colNum && colNum <= 2) {
			return { 0,0 };
		}
		else if (3 <= colNum && colNum <= 5) {
			return { 0,3 };
		}
		else if (6 <= colNum && colNum <= 8) {
			return { 0,6 };
		}
	}
	else if (rowNum >= 3 && rowNum <= 5) {
		if (0 <= colNum && colNum <= 2) {
			return { 3,0 };
		}
		else if (3 <= colNum && colNum <= 5) {
			return { 3,3 };
		}
		else if (6 <= colNum && colNum <= 8) {
			return { 3,6 };
		}
	}
	else if (rowNum >= 6 && rowNum <= 8) {
		if (0 <= colNum && colNum <= 2) {
			return { 6,0 };
		}
		else if (3 <= colNum && colNum <= 5) {
			return { 6,3 };
		}
		else if (6 <= colNum && colNum <= 8) {
			return { 6,6 };
		}
	}
}

// Ư�� ĭ�� ���� ���簢�� 9ĭ�� �˻��ϴ� �Լ�
bool squCheck(int rowNum, int colNum) {
	int cnt[10];
	for (int i = 0; i < 10; i++)
		cnt[i] = 0;

	pair<int, int> square_num = squNum(rowNum, colNum);
	int row = square_num.first;
	int col = square_num.second;

	for (int i = row; i < row + 3; i++) {
		for (int j = col; j < col + 3; j++) {
			if(board[i][j] != 0)
				cnt[board[i][j]] += 1;
			if (cnt[board[i][j]] >= 2) return false;
		}
	}
	return true;
}

void simulation(int row, int col) {

	// ĭ�� �� ä���� ��� ��� �� ����
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			// �� ĭ�� ���ؼ� �˻�
			if (board[i][j] == 0) {

				//1���� 9���� �� ĭ�� ������ ����.
				for (int k = 1; k <= 9; k++) {
					board[i][j] = k;
					// ��� üũ�� ��� ��
					if (rowCheck(i) && colCheck(j) && squCheck(i, j)) {
						simulation(i, j);
					}
					board[i][j] = 0;
				}
				return;
			}

			if (i == 8 && j == 8) {
				for (int i = 0; i < 9; i++) {
					for (int j = 0; j < 9; j++) {
						if (board[i][j] == 0) {
							return;
						}
					}
				}
				for (int i = 0; i < 9; i++) {
					for (int j = 0; j < 9; j++) {
						cout << board[i][j] << ' ';
					}
					cout << '\n';
				}
				exit(0);
			}
		}
	}
}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> board[i][j];
		}
	}
	simulation(0,0);
	return 0;
}