#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>

using namespace std;

vector<int> floors[101]; // 1~100�� ���������Ϳ� ����� ���� ǥ��
vector<int> elevator[100001]; // 1~100000������ �� �� �ִ� ���������� ��ȣ�� ǥ��
priority_queue<pair<int, int>> pq;

int ele_cnt[101];
int ele_parent[101];

int A, B, N, M; // N��, M���� ����������

void dijkstra() {

	// ���� ���� ����� ��� ���������ʹ� ź Ƚ���� 1�� �ʱ�ȭ��Ų��. (1���� Ÿ�� �� �� �ִٴ� �ǹ�)
	for (int i = 0; i < elevator[A].size(); i++) {
		ele_cnt[elevator[A][i]] = 1;
		pq.push({ -1, elevator[A][i] });
	}

	while (!pq.empty()) {
		int eleNum = pq.top().second;
		int tempC = pq.top().first * -1;
		pq.pop();

		if (tempC <= ele_cnt[eleNum]) {
			// ť���� ���� ���������� ��ȣ�� ����� ��� ���� ���캻��.
			for (int i = 0; i < floors[eleNum].size(); i++) {
				int tempFloor = floors[eleNum][i];
				for (int j = 0; j < elevator[tempFloor].size(); j++) {
					int nextEle = elevator[tempFloor][j];
					// ����� ������ Ż �� �ִ� ���� ���������� ��ȣ

					// ���� ���������Ϳ� ź Ƚ���� �� ���� ���ų�,
					// ���� ���������͸� ź Ƚ������ tempC + 1�� �� ���� ���
					// ���� �װ����� ������ �ش�.
					if (ele_cnt[nextEle] == 0 || tempC + 1 < ele_cnt[nextEle]) {
						ele_cnt[nextEle] = tempC + 1;
						ele_parent[nextEle] = eleNum; // ���� ���������� ���� ź ���� eleNum���� ǥ��
						pq.push({ (tempC + 1) * -1, nextEle });
					}
				}
			}

		}
	}
}

void print(int num) {
	if (num == 0) return;
	print(ele_parent[num]);
	printf("%d\n", num);
}


int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;
	for (int i = 1; i <= M; i++) { // ���������� ������ŭ �ݺ�
		int X, Y;
		cin >> X >> Y;

		while (X <= N) {
			// 4, 3�� �Է¹��� ��� 4��, 7��, 10��, .. �� floor[i] �� ����
			floors[i].push_back(X);
			elevator[X].push_back(i);
			X += Y;
		}
	}
	cin >> A >> B;

	dijkstra();

	int ans = 987654321;
	int last = 0;

	// B���� ����� ���������͵� ���� �ּڰ� ã��
	for (int i = 0; i < elevator[B].size(); i++) {
		if (ele_cnt[elevator[B][i]] < ans) {
			ans = ele_cnt[elevator[B][i]];
			last = elevator[B][i];
		}
	}

	if (ans == 987654321 || ans == 0) printf("-1\n");
	else {
		printf("%d\n", ans);
		print(last);
	}



	return 0;
}