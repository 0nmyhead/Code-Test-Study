#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int V;
vector< vector< pair<int, int> >> node;
bool visit[100001];

int leafNode;
int maxLength = -1;

// Ư���� ��Ʈ ��忡�� ���� �ָ� ������ ��� ã��
void dfs(int cur, int sum) {	
	visit[cur] = true;

	for (auto next : node[cur]) {
		int nextNum = next.first;
		int nextLength = next.second;
		if (visit[nextNum]) continue;
		
		if (maxLength < sum + nextLength) {
			leafNode = next.first;
			maxLength = sum + nextLength;
		}
		dfs(next.first, sum + nextLength);
	}
}


int main() {
	
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int v, w, cur;

	cin >> V;
	node.resize(V + 1);

	for (int i = 0; i < V; i++) {
		cin >> cur;
		while (1) {		
			cin >> v;
			if (v == -1) break;
			cin >> w;
			node[cur].push_back({ v, w });
		}
	}

	// 1 ã��
	dfs(1, 0);

	// �ʱ�ȭ
	maxLength = -1;
	for (int i = 0; i < V + 1; i++)
		visit[i] = false;

	// 2 ã��
	dfs(leafNode, 0);

	cout << maxLength;
	return 0;
}