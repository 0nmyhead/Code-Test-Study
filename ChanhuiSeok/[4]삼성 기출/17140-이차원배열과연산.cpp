#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define R 0
#define C 1

int arr[101][101];
int r, c, k;
int max_row = 3, max_col = 3;
int cntarr[101];

// ���� pair�� �����ϴ� ����
bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
	if (a.second < b.second) {
		return true;
	}
	else if (a.second == b.second) {
		if (a.first < b.first)
			return true;
	}
	return false;
}

// �� �Ǵ� ������ �ش� ���ڰ� �� ������ ��ȯ�ϴ� �Լ� - logN ����Ž�� ���
int func_count(int mode, int row, int col, int target) {

	// ������ ���� ���� ����
	vector<int> v;

	// R������ ��� �� ����
	if (mode == R) {
		for (int i = 0; i < col; i++) 
			v.push_back(arr[row][i]);

		sort(v.begin(), v.end());
		int right = upper_bound(v.begin(), v.end(), target) - v.begin();
		int left = lower_bound(v.begin(), v.end(), target) - v.begin();
		return right - left;
	}

	else {
		for (int i = 0; i < row; i++) 
			v.push_back(arr[i][col]);
		
		sort(v.begin(), v.end());
		int right = upper_bound(v.begin(), v.end(), target) - v.begin();
		int left = lower_bound(v.begin(), v.end(), target) - v.begin();
		return right - left;
	}
}

void simulation() {

	int maxRow, maxCol;
	vector<pair<int, int>> temp;
	int cnt = 0;

	//R ����
	if (max_row >= max_col) {
		for (int i = 0; i < max_row; i++) {
			for (int j = 0; j < max_col; j++) {
				// ���� Ƚ���� ���� ���� ������ ��� ���� Ƚ���� ����.
				if (arr[i][j] != 0 && cntarr[arr[i][j]] == 0) {
					cnt = func_count(R, i, max_col, arr[i][j]);
					temp.push_back({ arr[i][j], cnt });
					cntarr[arr[i][j]] = 1;
				}
			}
			// ������ ��� ������ �ϴ� �� ���� 0���� ����� ���´�.
			for (int j = 0; j < max_col; j++) {
				arr[i][j] = 0;
			}

			// i��° �࿡�� ��� ���� ��� �� ����
			sort(temp.begin(), temp.end(), cmp);

			// ���� temp data�� arr �迭�� ������, �ִ� col ����� ������ ���´�.
			max_col = max(max_col, (int)temp.size() * 2);

			vector<int> t;
			for (int k = 0; k < temp.size(); k++) {
				t.push_back(temp[k].first);
				t.push_back(temp[k].second);
			}
			for (int k = 0; k < t.size(); k++) {
				arr[i][k] = t[k];
				if (k == 100) break;
			}
			temp.clear();

			//cntarr �迭 �ʱ�ȭ
			for (int i = 0; i < 101; i++)
				cntarr[i] = 0;		
		}
	}

	// C ����
	else {
		// �迭�� ��� ���� ���Ͽ� ���� ����
		for (int j = 0; j < max_col; j++) {
			for (int i = 0; i < max_row; i++) {
				// ���� Ƚ���� ���� ���� ������ ��� ���� Ƚ���� ����.
				if (arr[i][j] != 0 && cntarr[arr[i][j]] == 0) {
					cnt = func_count(C, max_row, j, arr[i][j]);
					temp.push_back({ arr[i][j], cnt });
					cntarr[arr[i][j]] = 1;
				}
			}
			// ������ ��� ������ �ϴ� �� ���� 0���� ����� ���´�.
			for (int i = 0; i < max_row; i++) {
				arr[i][j] = 0;
			}
			
			// i��° ������ ��� ���� ��� �� ����
			sort(temp.begin(), temp.end(), cmp);

			// ���� temp data�� arr �迭�� ������, �ִ� row ����� ������ ���´�.
			max_row = max(max_row, (int)temp.size() * 2);

			vector<int> t;
			for (int k = 0; k < temp.size(); k++) {
				t.push_back(temp[k].first);
				t.push_back(temp[k].second);
			}
			for (int k = 0; k < t.size(); k++) {
				arr[k][j] = t[k];
				if (k == 100) break;
			}
			temp.clear();

			//cntarr �迭 �ʱ�ȭ
			for (int i = 0; i < 101; i++)
				cntarr[i] = 0;
		}
	}

}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> r >> c >> k;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> arr[i][j];
		}
	}

	int time = 0;

	while (time<=100) {
		if (arr[r - 1][c - 1] == k)
			break;
		simulation();
		time++;
	}

	if (time <= 100)
		cout << time;
	else
		cout << -1;

	return 0;
}