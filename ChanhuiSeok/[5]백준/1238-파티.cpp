#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

#define INF 987654321
#define pii pair<int, int>

using namespace std;
vector<pii>vec[1001];
priority_queue<pii, vector<pii>, greater<pii>> pq;

/* ���ͽ�Ʈ�� - (Ư�� ����) ���� ��� ���������� �ִܰŸ� */

vector<int> dijkstra(int N, int start) {

	// �ʱ� dist�� INF
	vector<int> dist(N + 1, INF);

	// �ʱ� start ������ �Ÿ��� 0���� �ʱ�ȭ
	dist[start] = 0;
	pq.push({ dist[start], start }); // �ʱ� ������ push

	while (!pq.empty()) {
		int cur = pq.top().second; // ���� ���� ��ȣ
		int distance = pq.top().first; // ���� ������ �Ÿ���
		pq.pop();

		// �̹�, ��� �ִ� �ͺ��� distance�� Ŭ ��� �Ѿ��.
		if (dist[cur] < distance) continue;

		// ���� ������ ������ �������� ��� ���캻��.
		for (int i = 0; i < vec[cur].size(); i++) {

			int next = vec[cur][i].first; // ������ ���� ������ ��ȣ
			int nextDistance = vec[cur][i].second; // ���� ������ �Ÿ���

			if (distance + nextDistance < dist[next]) {
				dist[next] = distance + nextDistance;
				pq.push({ (distance + nextDistance), next });
			}
		}
	}
	return dist;
}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	int N, M, X;
	cin >> N >> M >> X;
	// N�� ����, M�� ������ ��
	// X�� �������� ����

	int maxValue = -1;

	for (int i = 0; i < M; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		vec[u].push_back({ v,w });
	}

	vector<int> Xtoi = dijkstra(N, X); // X���� i���� ���� �Ÿ� ���ϱ� ����

	for (int i = 1; i <= N; i++) {

		vector<int> itoX = dijkstra(N, i); // i���� X���� ���� �Ÿ� ���ϱ� ����
		int result_itoX = itoX[X]; // i�� �л��� X���� ���� �ִܰŸ�
		int result_Xtoi = Xtoi[i]; // i�� �л��� X���� i������ ���� �ִܰŸ�

		maxValue = max(maxValue, result_itoX + result_Xtoi);
	}

	cout << maxValue;
	return 0;
}