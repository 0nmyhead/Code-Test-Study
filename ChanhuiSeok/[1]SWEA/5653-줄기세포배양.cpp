#include <iostream>
#include <algorithm>
#include <queue>
#include <functional>
#include <cstring>

#define DEAD -1000

using namespace std;

// �ð�, �����, row, col
typedef pair<pair<int, int>, pair<int, int>> Pair;

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

int arr[1001][1001];
bool visit[1001][1001];

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	int N, M, K;
	// �ʱ� ���¿� �ٱ� ���� ������ ����ũ��, ����ũ��, ���ð�

	int T;
	cin >> T;

	int row, col;

	for (int t = 0; t < T; t++) {
		cin >> N >> M >> K;
		priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
		// �ð��� ���� �ּ��� ���� �� ������ ���Բ� �ϴ� �켱���� ť (��������)

		for (int i = 400; i < 400 + N; i++) {
			for (int j = 400; j < 400 + M; j++) {
				cin >> arr[i][j];
				
				if (arr[i][j] > 0) {
					visit[i][j] = true; // �湮 üũ
					pq.push({ {arr[i][j], -arr[i][j]}, {i,j} });
				}
			}
		}

		int time = 1;
		// ��� �ð��� K�� �� ����
		while (time < K) {
			// �켱���� ť�� ������� �ʰ�, �� ���� cell�� ���� �ð��� ���� ���
			while (!pq.empty() && pq.top().first.first == time) {
				int row = pq.top().second.first;
				int col = pq.top().second.second;
				int life = -pq.top().first.second;

				pq.pop(); // Ȱ��ȭ pop

				// �ش� cell�� �Ʒ� ���� �ڵ带 �������� ���ϰ� �Ѵ�.
				if (life == -DEAD)
					continue;

				// Ȱ��ȭ�� cell�� �Ҹ� ������ �����Ѵ�.
				// ��, time + life - 1 �ʿ� ť���� �ƿ� pop �ǰ� time + life �ʿ��� ť�� ���� �Ѵ�.
				// ���� ���, �ʿ� �� ó�� ����� 2�� ������ �־��� ��� time = 2���� �� ���� pop �ȴ�.
				// ���� �� ������ 2�� Ȱ��ȭ ���� �׾�� �Ѵ�. �� time=4���� ���� ť�� ����� �Ѵ�.
				// ���� 3�ʿ� pop�� �ϰ�, 4�ʿ� ������ �Ʒ��� ���� �ڵ带 �ۼ��Ѵ�.

				pq.push({ {time + life - 1, DEAD}, {0,0} });

				for (int i = 0; i < 4; i++) {
					int ty = row + dy[i];
					int tx = col + dx[i];

					if (visit[ty][tx] == false) {
						visit[ty][tx] = true;
						pq.push({ { time+life+1, -life} ,  { ty, tx} });
					}

				}
			}
			time += 1;
		}

		cout << "#" << t+1 << " " << pq.size() << '\n';
		memset(visit, false, sizeof(visit));
		memset(arr, 0, sizeof(arr));
	}

	return 0;
}