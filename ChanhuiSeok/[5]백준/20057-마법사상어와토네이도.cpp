#include <iostream>
#include <sstream>
#include <queue>
#include <algorithm>

using namespace std;

int arr[550][550];
int visit[550][550];
int N;
int outSand;

int dy[4] = { 0,1,0,-1 };
int dx[4] = { -1,0,1,0 };

bool valid(int y, int x) {
	if (y <= 0 || x <= 0 || y > N || x > N) {
		return false;
	}
	return true;
}

void sandBlow(int cy, int cx, int dir) {

	// arr[cy][cx] => 'x'

	// �� 9ĭ�� �ĺ�ĭ�� �ִ´�.
	vector<pair<int, pair<int,int>>> candidate;

	// (cy, cx)���� �� ĭ �ش� �������� �̵���Ų��. -> yBlock
	cy = cy + dy[dir % 4];
	cx = cx + dx[dir % 4];

	// yBlock
	int yBlock = arr[cy][cx];

	// 7%
	candidate.push_back({ (int)(yBlock * 0.07), {cy + dy[(dir + 3) % 4], cx + dx[(dir + 3) % 4]} });
	candidate.push_back({ (int)(yBlock * 0.07), {cy + dy[(dir + 1) % 4], cx + dx[(dir + 1) % 4]} });

	// 10%
	int y_10 = cy + dy[dir % 4]; // ��ĭ �� ����
	int x_10 = cx + dx[dir % 4]; // ��ĭ �� ����
	candidate.push_back({ (int)(yBlock * 0.1), {y_10 + dy[(dir + 3) % 4], x_10 + dx[(dir + 3) % 4]} });
	candidate.push_back({ (int)(yBlock * 0.1), {y_10 + dy[(dir + 1) % 4], x_10 + dx[(dir + 1) % 4]} });

	// 1%
	int y_1 = cy + dy[(dir + 2) % 4]; // �̵� ��
	int x_1 = cx + dx[(dir + 2) % 4];
	candidate.push_back({ (int)(yBlock * 0.01), {y_1 + dy[(dir + 3) % 4], x_1 + dx[(dir + 3) % 4]} });
	candidate.push_back({ (int)(yBlock * 0.01), {y_1 + dy[(dir + 1) % 4], x_1 + dx[(dir + 1) % 4]} });

	// 5%
	int y_5 = cy + dy[dir % 4]; // ��ĭ �� ����
	int x_5 = cx + dx[dir % 4]; // ��ĭ �� ����
	candidate.push_back({ (int)(yBlock * 0.05), {y_5 + dy[dir % 4], x_5 + dx[dir % 4]} });

	// 2%
	int y_2 = cy + dy[(dir + 3) % 4];
	int x_2 = cx + dx[(dir + 3) % 4];
	candidate.push_back({ (int)(yBlock * 0.02), {y_2 + dy[(dir + 3) % 4], x_2 + dx[(dir+3)%4]} });

	int y_2_2 = cy + dy[(dir + 1) % 4];
	int x_2_2 = cx + dx[(dir + 1) % 4];
	candidate.push_back({ (int)(yBlock * 0.02), {y_2_2 + dy[(dir + 1) % 4], x_2_2 + dx[(dir+1)%4]} });

	int sum = 0; // �̵��� ���� ��

	// candidate�� ��� ĭ���� ���鼭 Ȯ���Ѵ�.
	for (int i = 0; i < candidate.size(); i++) {
		int sy = candidate[i].second.first;
		int sx = candidate[i].second.second;

		sum += candidate[i].first;

		// (sy, sx)�� ���� ���� ���
		if (valid(sy, sx)) {
			arr[sy][sx] += candidate[i].first;
		}
		// (sy, sx)�� ���� �ٱ��� ���
		else {
			outSand += candidate[i].first;
		}
	}
	// alpha ĭ���� yBlock - �̵��� ���� ���� �����Ѵ�.
	int a_y = cy + dy[dir % 4];
	int a_x = cx + dx[dir % 4];
	if (valid(a_y, a_x)) {
		arr[a_y][a_x] += (yBlock - sum);
	}
	else {
		outSand += (yBlock - sum);
	}
	arr[cy][cx] = 0;
}

void simulation(int sy, int sx) {

	// 1 1 2 2 3 3 4 4 5 5 . . . 
	// �� �� �� �� / �� �� �� �� . . .
	int dir = 0;
	int idx = 1;
	int loopCnt = 0;

	int cy = sy;
	int cx = sx;

	while (1) {
		// �̵��ϴ� ĭ ����
		for (int p = 0; p < idx; p++) {
			// ���� ĭ���� �� �𳯸��� ����
			if (cy == 1 && cx == 1) {

				visit[cy][cx] = 1;
				sandBlow(cy, cx, dir);
				break;
			}

			visit[cy][cx] = 1;
			sandBlow(cy, cx, dir);

			dir = dir % 4;
			cy = cy + dy[dir];
			cx = cx + dx[dir];
		}

		// (1,1)���� �� �𳯸��� ������ ����
		if (cy == 1 && cx == 1) break;
		
		// ���� ��ȯ
		dir++;
		loopCnt++;

		// �̵��ϴ� ĭ�� ���� 2�� loop���� 1 ����
		if (loopCnt % 2 == 0) idx++;
	}
}


int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	for (int i = 1; i <= N ; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}
	simulation(N / 2 + 1, N / 2 + 1);

	cout << outSand;
	return 0;
}