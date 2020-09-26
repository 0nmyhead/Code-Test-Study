#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <deque>
#include <cstring>

using namespace std;

int N;
int W[200001];
int dp[200001][2];
bool visit[200001];

vector< vector<int> > node;

// dp[X][hasMento] = X�� X�� ����� ���丱 ���� ��, Ȥ��
// ���� ���� �� X�� ����Ʈ�������� �ó��� ���� �ִ�

int dfs(int cur, int hasMentor) {

	int& ret = dp[cur][hasMentor];

	// �̹� �湮�� ���� ���� ��� �ٷ� ��ȯ
	if (ret != -1) return ret;

	// �湮���� �ʾ��� ��� ��� ����
	int sum = 0;
	ret = 0;

	// dp[X][1] �� ������ X�� �ڽ� ��� c1, c2, .. �� ���� dp[c1][0] + dp[c2][0] +..�� ���Ѵ�.
	// ��, X�� �ڽĳ�� c1�� ����� X�� ���丵�� ���� �ʾ����Ƿ� = dp[c1][0]
	for (auto next : node[cur]) {
		sum = sum + dfs(next, 0);
	}
	ret = sum;
	if (hasMentor == 1) return sum;

	// hasMentor
	for (auto next : node[cur]) {
		// cur�� �� �ڽĳ�� next�� ���丵���� ������ ���
		ret = max(ret, sum - dfs(next, 0) + dfs(next, 1) + W[cur] * W[next]);
	}
	return ret;
}


int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N;
	node.resize(N + 1);

	for (int i = 2; i <= N; i++) {
		int input;
		cin >> input;
		node[input].push_back(i); // ���⼺�� ����
	}

	memset(dp, -1, sizeof(dp));

	for (int i = 1; i <= N; i++) {
		cin >> W[i];
	}

	cout << dfs(1, 0);

	return 0;
}