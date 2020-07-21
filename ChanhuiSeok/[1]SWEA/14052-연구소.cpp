#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
queue<pair<int, int>> q;
queue<pair<int, int>> virus_q;

int arr[10][10];
int visit[10][10];
int copy_arr[10][10]; // �ʱ� �迭 ���¸� ����

int MaxSafeZone = -1;

int N, M;

// ��ȿ�� ĭ���� �Ǵ��ϴ� �Լ�
bool isValid(int y, int x) {
	if (y < 0 || x < 0 || y >= N || x >= M || arr[y][x] == 1)
		return false;
	if (visit[y][x] == 1) return false;
	return true;
}


// ���̷����� �۶߸��� �Լ�
void bfs() {
	// ��, ��, ��, �� �˻��ؼ� ��ĭ�̸� ť�� �ְ� �湮�ϸ� 2�� �����.
	q = virus_q;

	while (!q.empty()) {
		int fy = q.front().first;
		int fx = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ty = fy + dy[i];
			int tx = fx + dx[i];

			// ��ȿ�� ĭ�� ���ؼ��� ť�� �ִ´�.
			if (isValid(ty, tx)) {
				q.push({ ty,tx });
				visit[ty][tx] = 1;
				arr[ty][tx] = 2; // ���̷��� �����ϱ�
			}
		}	
	}

	// ���̷��� ���� �Ϸ�
	// �� ĭ�� ���� ����
	int zeroCnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (arr[i][j] == 0) {
				zeroCnt += 1;
			}
		}
	}
	MaxSafeZone = max(MaxSafeZone, zeroCnt);
}

// ���� ����� �Լ�
void createWall(int cnt) {

	if (cnt == 3) // 3���� ������ ���
	{
		// ����
		memcpy(copy_arr, arr, sizeof(arr));
		bfs(); // ���̷����� �۶߸���.
				
		// �ǵ�����
		memcpy(arr, copy_arr, sizeof(arr));
		memset(visit, 0, sizeof(visit));

		cnt -= 1;
		return;
	}

	// ���� �����.
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (arr[i][j] == 0) {
				arr[i][j] = 1;
				createWall(cnt + 1);
				arr[i][j] = 0; // �ٽ� �� ĭ���� �����.
			}
		}
	}
}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 2) {
				virus_q.push({ i,j });
			}
		}
	}

	// ���� ���� ���� -> ���̷��� �۶߸��� -> 0�� ���� ����
	// �ٽ� ���ο� ���� ����� -> ... �ݺ�
	createWall(0);

	cout << MaxSafeZone;

	return 0;
}