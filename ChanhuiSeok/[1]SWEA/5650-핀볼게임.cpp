#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

using namespace std;

int board[104][104];
vector <pair<int, int>> worm[11];

int direction[4] = { UP,DOWN,LEFT,RIGHT };

typedef struct {
	int dir;
	int y;
	int x;
}pinball;
pinball pin;


pair<int, int> getWorm(int num, int y, int x) {

	int ty, tx;
	if (worm[num][0].first != y || worm[num][0].second != x) {
		ty = worm[num][0].first;
		tx = worm[num][0].second;
	}
	else {
		ty = worm[num][1].first;
		tx = worm[num][1].second;
	}

	return make_pair(ty, tx);
}

int changeDir(int target, int myDir) {

	int retDir = myDir;

	switch (target) {
	case 1:
		if (myDir == UP) retDir = DOWN;
		else if (myDir == DOWN) retDir = RIGHT;
		else if (myDir == LEFT) retDir = UP;
		else if (myDir == RIGHT) retDir = LEFT;
		break;
	case 2:
		if (myDir == UP) retDir = RIGHT;
		else if (myDir == DOWN) retDir = UP;
		else if (myDir == LEFT) retDir = DOWN;
		else if (myDir == RIGHT) retDir = LEFT;
		break;
	case 3:
		if (myDir == UP) retDir = LEFT;
		else if (myDir == DOWN) retDir = UP;
		else if (myDir == LEFT) retDir = RIGHT;
		else if (myDir == RIGHT) retDir = DOWN;
		break;
	case 4:
		if (myDir == UP) retDir = DOWN;
		else if (myDir == DOWN) retDir = LEFT;
		else if (myDir == LEFT) retDir = RIGHT;
		else if (myDir == RIGHT) retDir = UP;
		break;
	case 5:
		if (myDir == UP) retDir = DOWN;
		else if (myDir == DOWN) retDir = UP;
		else if (myDir == LEFT) retDir = RIGHT;
		else if (myDir == RIGHT) retDir = LEFT;
		break;
	default:
		retDir = myDir;
	}

	return retDir;
}

int game(int i, int j, int dir) {

	/* �ɺ� ���� ���� */
	int curScore = 0;
	pin.y = i; pin.x = j; pin.dir = dir;

	int startY = i, startX = j;

	/* �ɺ� �����̱� */
	while (1) {
		// �����̱�
		if (pin.dir == UP) pin.y -= 1;		
		else if (pin.dir == DOWN) pin.y += 1;		
		else if (pin.dir == LEFT) pin.x -= 1;		
		else if (pin.dir == RIGHT) pin.x += 1;
		
		// �ɺ��� ó�� ��ġ�� ��� �ݺ����� �������´�.
		if (pin.y == startY && pin.x == startX)
			break;

		// ���� �� ���� ��Ȧ�̾��� ���, �ݺ����� �������´�.
		if (board[pin.y][pin.x] == -1) {
			break;
		}

		// ���� �� ���� 1~5 ����̾��� ���, ������ �ٲ��ش�.
		// ����, ��Ͽ� �ε������Ƿ� ������ �����ȴ�.
		if (board[pin.y][pin.x] >= 1 && board[pin.y][pin.x] <= 5) {
			pin.dir = changeDir(board[pin.y][pin.x], pin.dir);
			curScore += 1;
		}

		// ���� �� ���� ��Ȧ�̾��� ���, �ɺ��� ��ġ�� �ٸ� ��Ȧ�� �ִ� ������ �ٲ��ش�.
		else if (board[pin.y][pin.x] >= 6 && board[pin.y][pin.x] <= 10) {
			pair<int, int> temp;
			temp = getWorm(board[pin.y][pin.x], pin.y, pin.x);
			pin.y = temp.first;
			pin.x = temp.second;
		}			
	}

	return curScore;
}


int main() {
	
	ios::sync_with_stdio(0);
	cin.tie(0);

	int maxScore = 0;
	int T, N;
	cin >> T;

	// -1�� ��Ȧ, 0�� �����, 1~5�� ���, 6~10�� ��Ȧ
	// ��Ȧ�̳� ó�� ��ġ�� �����ϸ� ���� ����, ������ ���̳� ��Ͽ� �ε��� ȸ��

	for (int t = 0; t < T; t++) {
		cin >> N; // N * N ������
		int score = 0;

		// ���� ������� ó��
		for (int i = 0; i <= N + 1; i++) {
			for (int j = 0; j <= N + 1; j++) {
				board[i][j] = 5;
			}
		}

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				cin >> board[i][j];
				// ��Ȧ�� ��� ���� �˾ƾ� �ϹǷ� ���� ����
				if (board[i][j] >= 6 && board[i][j] <= 10) {
					worm[board[i][j]].push_back({ i,j });
				}
			}
		}
	
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				// �� ������ ��� ���
				if (board[i][j] == 0) {

					for (int k = 0; k < 4; k++) {
						score = game(i, j, direction[k]);
						maxScore = max(maxScore, score);
					}
				}
			}
		}
		cout << "#" << t + 1 << " " << maxScore << '\n';
		maxScore = -100;
		
		for (int i = 6; i <= 10; i++) 
			worm[i].clear();		
	}

	return 0;
}