#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <deque>

using namespace std;

int N;
int W[10001];
int dp[10001][2];
bool visit[10001];

vector< vector<int> > v;

/* �������� ���⼺�� ���� �׷��� ������ �ֱ� ������
dfs Ž���ϸ鼭 �� ���̶� �湮�� ���� �ٽô� ���� �ʰ� �Ѵٸ�
Ʈ������ �θ� - �ڽ����� ���� ���¸� ���� �� �ֽ��ϴ�. */

void dfs(int cur) {

	// �̹� �湮�� ���� ���� �� �ȴ�.
	if (visit[cur]) return;

	// ó�� ���� cur ��忡 ���� �Ϲ� ������ ��� ������ �� �α����� �ʱ�ȭ
	// ��� ������ ���ϴ� ���̹Ƿ� �α����� ��������� ���� �����Ѵ�.
	visit[cur] = true;
	dp[cur][0] = 0;
	dp[cur][1] = W[cur];

	// cur�� ������ �ڽ� ���鿡 ���Ͽ�
	for (auto next : v[cur]) {
		if (visit[next]) continue; // �湮 �� �� ������ ����.

		dfs(next); // ������ Ÿ�� ����.

		// �Ϲ� ������ �ڽ� ������ ����ų�, �ڽ� ������ �Ϲ� �����̴�.
		// �� ū ���� �����Ѵ�. 3�� ������ ���⼭ �ذ��� �ȴ�.
		dp[cur][0] = dp[cur][0] + max(dp[next][0], dp[next][1]);

		// ���� ������ ��� �����̸�, �ڽ��� �ݵ�� �Ϲ� �����̾�� �Ѵ�.
		dp[cur][1] = dp[cur][1] + dp[next][0];
	}

}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N;

	for (int i = 1; i <= N; i++) {
		int input;
		cin >> input;
		W[i] = input;
	}

	v.resize(N + 1);

	for (int i = 0; i < N - 1; i++) {
		int a, b;
		cin >> a >> b;
		v[a].push_back(b);
		v[b].push_back(a);
	}

	dfs(1);

	cout << max(dp[1][0], dp[1][1]);

	return 0;
}