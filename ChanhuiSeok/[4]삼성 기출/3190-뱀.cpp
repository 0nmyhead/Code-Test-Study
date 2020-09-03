#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define EMPTY 0
#define APPLE 1
#define SNAKE 2
#define WALL 5

#define UP 10
#define DOWN 11
#define LEFT 12
#define RIGHT 13

using namespace std;

typedef struct{
	int dir;
	int y;
	int x;
}snake;

int arr[102][102];

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

string info[10001];
queue<snake> q;

bool moving(int dir) {
	snake temp;
	int ty = q.back().y;
	int tx = q.back().x;

	if (dir == UP) { ty += dy[0]; tx += dx[0]; }
	else if (dir == DOWN) { ty += dy[1]; tx += dx[1]; }
	else if (dir == LEFT) { ty += dy[2]; tx += dx[2]; }
	else if (dir == RIGHT) { ty += dy[3]; tx += dx[3]; }

	// ���� ĭ�� ���̰ų� �ڱ� �ڽ��� ��� �ٷ� �����ϱ�
	if (arr[ty][tx] == WALL || arr[ty][tx] == SNAKE) {
		return false;
	}

	// ���� ĭ�� ����� ���
	if (arr[ty][tx] == APPLE) {
		temp.y = ty; temp.x = tx; temp.dir = dir;
		q.push(temp);
		arr[ty][tx] = SNAKE; // ������ ä���
	}

	// ���� ĭ�� ����� �ƴ� ���
	else {
		temp.y = ty; temp.x = tx; temp.dir = dir;
		q.push(temp);
		arr[ty][tx] = SNAKE; // �� �������� ä���

		// ���� ���� �κ��� ��ǥ�� ���
		int tail_y = q.front().y;
		int tail_x = q.front().x;
		arr[tail_y][tail_x] = EMPTY; // �����ǿ��� ���� �κ� �����ϱ�
		q.pop(); // ���� ����
	}

	return true;
}

int changeDir_func(int originDir, string change) {

	int changedDir;

	if (change == "D") {
		if (originDir == UP) changedDir = RIGHT;
		else if (originDir == DOWN) changedDir = LEFT;
		else if (originDir == LEFT) changedDir = UP;
		else if (originDir == RIGHT) changedDir = DOWN;
	}

	else if (change == "L") {
		if (originDir == UP) changedDir = LEFT;
		else if (originDir == DOWN) changedDir = RIGHT;
		else if (originDir == LEFT) changedDir = DOWN;
		else if (originDir == RIGHT) changedDir = UP;
	}

	return changedDir;
}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	int N, K;
	cin >> N >> K;

	int row, col;
	int L, sec;
	string dir;

	// �� �ʱ�ȭ
	snake sna;
	sna.y = 1;  sna.x = 1; sna.dir = RIGHT;
	q.push(sna);

	// ������ �ʱ�ȭ
	for (int i = 0; i < N + 2; i++) 
		for (int j = 0; j < N + 2; j++) 
			arr[i][j] = WALL;		
	
	for (int i = 1; i <= N; i++) 
		for (int j = 1; j <= N; j++) 
			arr[i][j] = EMPTY;		
	
	for (int i = 0; i < K; i++) {
		cin >> row >> col;
		arr[row][col] = APPLE; // 1�� ���
	}

	// ���� �������� �Է�
	cin >> L;
	for (int i = 0; i < L; i++) {
		cin >> sec >> dir;
		info[sec] = dir;
	}

	// (1,1) ���� ����. ���� ó���� �������� ���Ѵ�.
	int time = 0;

	while (1) {
		// �� �Ӹ��� ���Ⱚ �ӽ� ����
		int headDir = q.back().dir;
		int changeDir;

		// �� �ʸ��� �̵�, ���� �Ӹ��� �ѱ��
		if (!moving(headDir)) 
			break;
			
		time += 1; // �ð� �帧

		// �� �ʰ� ���� �� ���� ��ȯ ���� �ľ�
		if (info[time] == "D" || info[time] == "L") {

			// �Ӹ� �κ��� ������ �ٲٱ�
			changeDir = changeDir_func(headDir, info[time]);
			q.back().dir = changeDir;
		}

		/* ��Ȳ ��� */
		/*
		for (int i = 0; i <= N+2; i++) {
			for (int j = 0; j <= N+2; j++) {
				cout << arr[i][j] << " ";
			}
			cout << "\n";
		}
		cout << "\n";
		*/
	}
	
	cout << time + 1;

	return 0;
}