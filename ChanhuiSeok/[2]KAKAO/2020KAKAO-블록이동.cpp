
#include <string>
#include <vector>
#include <queue>

using namespace std;

enum states { garo, sero };
int N;
vector <vector<int>> map;

typedef struct robots {
	int y, x, state, time;
}Robot;

bool visit[102][102][2];

bool isRanged(int y, int x) {
	if (y < 0 || x < 0 || y >= N || x >= N)
		return false;
	if (map[y][x] == 1)
		return false;
	return true;
}

vector<Robot> isPossible(Robot& robot) {
	// ���� �� �κ��� ��,��,��,��� ȸ������ ����� ĭ���� ��� ���� �̵� �����ϸ� ť�� �ִ´�.
	// �κ��� �������� ��
	vector<Robot> temp;
	if (robot.state == garo) {
		// 1. �������� �����ϰų� ���� ȸ���ϸ鼭 �κ��� [����]���� �� �� �ֳ�?
		if (isRanged(robot.y - 1, robot.x) && isRanged(robot.y - 1, robot.x + 1)) {
			// �����ϸ�, ť�� �ֱ� ���� �غ� �Ѵ�.
			temp.push_back({ robot.y - 1, robot.x, sero, robot.time + 1 });
			temp.push_back({ robot.y - 1, robot.x + 1, sero, robot.time + 1 });
			temp.push_back({ robot.y - 1, robot.x, garo, robot.time + 1 });
		}
		// 2. �������� �����ϰų� �Ʒ��� ȸ���ϸ鼭 �κ��� [�Ʒ���]���� �� �� �ֳ�?
		if (isRanged(robot.y + 1, robot.x) && isRanged(robot.y + 1, robot.x + 1)) {
			// �����ϸ�, ť�� �ִ´�.
			temp.push_back({ robot.y, robot.x, sero, robot.time + 1 });
			temp.push_back({ robot.y, robot.x + 1, sero, robot.time + 1 });
			temp.push_back({ robot.y + 1, robot.x, garo, robot.time + 1 });
		}
		// 3. �������� �����ϸ鼭 [������]���� �� �� �ֳ�?
		if (isRanged(robot.y, robot.x + 2)) {
			temp.push_back({ robot.y, robot.x + 1, garo, robot.time + 1 });
		}
		// 4. �������� �����ϸ鼭 [����]���� �� �� �ֳ�?
		if (isRanged(robot.y, robot.x - 1)) {
			temp.push_back({ robot.y, robot.x - 1, garo, robot.time + 1 });
		}
	}
	else if (robot.state == sero) {
		// 1. �������� �����ϰų� ���������� ȸ���ϸ鼭 [������]���� �� �� �ֳ�?
		if (isRanged(robot.y, robot.x + 1) && isRanged(robot.y + 1, robot.x + 1)) {
			// �����ϸ�, ť�� �ֱ� ���� �غ� �Ѵ�.
			temp.push_back({ robot.y, robot.x, garo, robot.time + 1 });
			temp.push_back({ robot.y + 1, robot.x, garo, robot.time + 1 });
			temp.push_back({ robot.y, robot.x + 1, sero, robot.time + 1 });
		}
		// 2. �������� �����ϰų� �������� ȸ���ϸ鼭 [����]���� �� �� �ֳ�?
		if (isRanged(robot.y, robot.x - 1) && isRanged(robot.y + 1, robot.x - 1)) {
			// �����ϸ�, ť�� �ֱ� ���� �غ� �Ѵ�.
			temp.push_back({ robot.y + 1, robot.x - 1, garo, robot.time + 1 });
			temp.push_back({ robot.y, robot.x - 1, garo, robot.time + 1 });
			temp.push_back({ robot.y, robot.x - 1, sero, robot.time + 1 });
		}
		// 3. �������� �����ϸ鼭 [����]���� �� �� �ֳ�?
		if (isRanged(robot.y - 1, robot.x)) {
			temp.push_back({ robot.y - 1, robot.x, sero, robot.time + 1 });
		}
		// 4. �������� �����ϸ鼭 [�Ʒ���]���� �� �� �ֳ�?
		if (isRanged(robot.y + 2, robot.x)) {
			temp.push_back({ robot.y + 1, robot.x, sero, robot.time + 1 });
		}
	}

	return temp;
}

int solution(vector<vector<int>> board) {
	int answer = 0;
	map = board;
	N = board.size();

	// (1) Robot Init
	queue<Robot> que;
	/////////////////////////////////////////////////
	// (2) start BFS
	que.push({ 0, 0, garo, 0 });

	while (!que.empty()) {
		Robot robot = que.front();
		que.pop();

		// �湮 ǥ��
		// �̹� N, N ��ǥ�� ���� ���
		if ((robot.y == N - 1 && robot.x == N - 2 && robot.state == garo) ||
			(robot.y == N - 2 && robot.x == N - 1 && robot.state == sero)) {
			return robot.time;
		}

		bool v = visit[robot.y][robot.x][robot.state];
		if (v) continue;
		else {
			visit[robot.y][robot.x][robot.state] = true;
		}

		auto temp = isPossible(robot);
		for (auto& newTemp : temp) {
			que.push(newTemp);
		}
	}
	return 0;
}